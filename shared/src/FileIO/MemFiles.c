// MemFiles.c

#include "port.h"
#include "FnxFiles.h"
#include "MemFiles.h"

#include "GlobalCommon.h"

#ifndef FNX_OVERRIDE_FILE_CALLS

void FnxCallType FnxTTSDtSimpleMemFileRegister( FnxMemFileMapping * mapIn )
{
	GlobalCommonPtr	gp = GetGlobalCommonPtr();
	FnxMemFileMapping * map = (FnxMemFileMapping *)mapIn;
	FnxMemFileMapping * mapItem;

	gp->pFileMap = map;
	gp->NumMemFiles = 0;

	if( !map )
		return;

	mapItem = &map[ 0 ];

	while( mapItem->pName )
	{
		gp->NumMemFiles++;
		mapItem = &map[ gp->NumMemFiles ];
	}
}

void FnxCallType FnxTTSDtSimpleCombineMemFileMaps(FnxMemFileMapping **ppMapsIn, 
						   int nMapsInCnt,
						   FnxMemFileMapping *pMapOut)
{
	int inCnt = 0;
	int outCnt = 0;
	int mapCnt = 0;

	for (mapCnt = 0; mapCnt < nMapsInCnt; mapCnt++)
	{
		inCnt = 0;
		while (ppMapsIn[mapCnt][inCnt].pName != NULL)
		{
			pMapOut[outCnt].flags = ppMapsIn[mapCnt][inCnt].flags;
			pMapOut[outCnt].len = ppMapsIn[mapCnt][inCnt].len;
			pMapOut[outCnt].pName = ppMapsIn[mapCnt][inCnt].pName;
			pMapOut[outCnt++].pAddr = ppMapsIn[mapCnt][inCnt++].pAddr;
		}
	}
	pMapOut[outCnt].flags = 0;
	pMapOut[outCnt].len = 0;
	pMapOut[outCnt].pName = NULL;
	pMapOut[outCnt++].pAddr = NULL;
}

#ifndef NO_SYSFILE_WRITES

#define	READ_BUFFER_SIZE	8192
#define  ENTRIES_PER_LINE	32

/***************************************************
 *  NAME:	OutputHexData
 *  DESC:	Converts the contents of a file to an array
 *			within another file
 *  IN:		pIn		- pointer to input FILE structure
 *			pOut	- pointer to output FILE structure
 *			pName	- name pointer to be used as array name
 *			fileSize- size of file to be written
 *  OUT:	<none>
 *  RETURN:	TRUE for cancel
 *  NOTES:	
 ***************************************************/
static BOOL OutputHexData(FILE *pIn,
						  FILE *pOut,
						  char *pName,
						  int fileSize,
						  YieldFunction pYieldFunction,
						  void * pData)
{
	int				bytesRead, linePos, filePos;
	unsigned char	*pBuf, buffer[READ_BUFFER_SIZE];

	if (fileSize != 0)
	{
		FNX_FPRINTF(pOut, "static const unsigned char %s[%d] =", pName, fileSize);
		FNX_FPRINTF(pOut, "\n{\n  ");

		linePos = filePos = 0;
		while( !FNX_FEOF( pIn ) )
		{
			if( pYieldFunction )
			{
				if( pYieldFunction( pData, pName ) )
					return TRUE;
			}
			bytesRead = FNX_FREAD(buffer, sizeof(char), READ_BUFFER_SIZE, pIn);
			pBuf = buffer;
			while (bytesRead--)
			{
				if (filePos < fileSize - 1)
				{
					FNX_FPRINTF(pOut, "%d,", *pBuf);
					if( linePos < ENTRIES_PER_LINE - 1 )
					{
						linePos++;
					}
					else
					{
						FNX_FPRINTF(pOut, "\n  ");
						linePos = 0;
					}
				}
				else
				{
					FNX_FPRINTF(pOut, "%d\n};\n", *pBuf);
				}
				filePos++;
				pBuf++;
			}
		}
		FNX_ASSERT(filePos == fileSize);
	}

   return FALSE;
}

/***************************************************
 *  NAME:	ConvertName
 *  DESC:	Replaces '.', '\', '^', ' ', and ':' with '_' in a 
 *			filename
 *  IN:		pFileName	- file name
 *			pFileSize	- pointer to size of this file
 *  OUT:	
 *  RETURN:	
 *  NOTES:	
 ***************************************************/
void ConvertName(char *pName)
{
	char	*chPtr;

	// replace '.', ':', and '\" with '_'
	while ((chPtr = FNX_STRCHR(pName, '.')) ||
			(chPtr = FNX_STRCHR(pName, ':')) ||
			(chPtr = FNX_STRCHR(pName, '^')) ||
			(chPtr = FNX_STRCHR(pName, ' ')) ||
			(chPtr = FNX_STRCHR(pName, '\\')))
	{
		*chPtr ='_';
	}
}

/***************************************************
 *  NAME:	OutputFile
 *  DESC:	Writes a file as an array in a generated include file
 *  IN:		pOut		- pointer to output FILE structure
 *			pFileName	- file name
 *			pFileSize	- pointer to size of this file
 *  OUT:	pFileSize is updated to the actual file size
 *  RETURN:	returns 0 if successful
 *  NOTES:	
 ***************************************************/
int OutputFile(FILE *pOut,
			   const char *pPath,
			   char *pFileName,
			   int *pFileSize,
			   char *pMode,
			   int write,
			   YieldFunction pYieldFunction,
			   void * pData )
{
	FILE	*pIn;
	int		bytes, error = -1;
	char	name[256];
	char	buf[READ_BUFFER_SIZE];

	if( pPath )
	{
		FNX_STRCPY( name, pPath );
		if( *pPath )
		{
			if( *(pPath + FNX_STRLEN( pPath ) - 1) != '\\' && *(pPath + FNX_STRLEN( pPath ) - 1) != '/' )
			{
				FNX_STRCAT( name, "\\" );
			}
		}
		FNX_STRCAT( name, pFileName );
	}
	else
	{
		FNX_STRCPY( name, pFileName );
	}

	pIn = FNX_FOPEN(name, pMode);
	if (pIn)
	{
		*pFileSize = 0;
		while (bytes = FNX_FREAD(buf, 1, READ_BUFFER_SIZE, pIn))
		{
			*pFileSize += bytes;
		}
		FNX_REWIND( pIn );

		if (write)
		{
			FNX_FPRINTF(pOut, "\n// %s\n\n", name);
			FNX_STRCPY(name, pFileName);
			ConvertName(name);
			// Output file as Hex data
			if( OutputHexData(pIn, pOut, name, *pFileSize, pYieldFunction, pData ) )
			{
      			FNX_FCLOSE(pIn);
				return -1;
			}
		}

		FNX_FCLOSE(pIn);
		error = 0;
	}

	return error;
}

/***************************************************
 *  NAME:	OutputSpecificMap
 *  DESC:	Writes a mapping between file names and their
 *			length and location in memory without including the core stuff.
 *  IN:		pMapName  - name to be used for MemFileMap array
 *			pOut	  - pointer to output FILE structure
 *			argv	  - list of pointers to file name
 *			len		  - pointer to array of file lengths
 *			count	  - number of files converted to arrays
 *  OUT:	<none>
 *  RETURN:	<none>
 *  NOTES:	
 ***************************************************/
static void OutputSpecificMap(char *pMapName,
					  FILE *pOut,
					  char **ppFiles,
					  int *len,
					  int count)
{
	int		i, j;
	char	*pName;
	char	name[256];

	FNX_FPRINTF(pOut, "\nFnxMemFileMapping %s[ FNX_MF_MAXFILES ] =", pMapName);
	FNX_FPRINTF(pOut, "\n{\n  ");

	for( i = 0; i < count; i++)
	{
		pName = ppFiles[i];
		for (j = 0; (name[j] = *pName) != '\0'; j++, pName++)
		{
			// replace '.', ':', '^', ' ', and '\" with '_'
			if (*pName == '\\')
			{
				*pName = '_';
				name[++j] = '\\';
			}
			else if (*pName == ':' || *pName == '.' || *pName == '^' || *pName == ' ' )
			{
				*pName = '_';
			}
		}
		FNX_FPRINTF(pOut, "\t{FNX_MF_STATIC, %d, \"%s\", (char *)%s}", len[i], name, ppFiles[i]);
		FNX_FPRINTF(pOut, ",\n");
	}

	FNX_FPRINTF(pOut, "\t{0, 0, NULL, NULL}");
	FNX_FPRINTF(pOut, "\n};\n  ");
}

/***************************************************
 *  NAME:	OutputGenericMap
 *  DESC:	Writes a mapping between file names and their
 *			length and location in memory without including the core stuff.
 *  IN:		pOut	- pointer to output FILE structure
 *			argv	- list of pointers to file name
 *			len		- pointer to array of file lengths
 *			count	- number of files converted to arrays
 *  OUT:	<none>
 *  RETURN:	<none>
 *  NOTES:	
 ***************************************************/
static void OutputGenericMap(FILE *pOut,
					  char **ppFiles,
					  int *len,
					  int count)
{
	OutputSpecificMap("FNX_MEMFILE_MAP", pOut, ppFiles, len, count);
}

/***************************************************
 *  NAME:	WriteArbitraryMemFileEx
 *  DESC:	Write a mem file with given arbitrary files
 *          and a specific MemFileMap name.
 *  NOTES:	Max number of files is NUM_STATIC_FILES.
 ***************************************************/
int WriteArbitraryMemFileEx( 
	char * outputFile, 
	int numInputFiles, 
	char ** ppInputFiles, 
	char ** ppInputDirectories,
	YieldFunction pYieldFunction,
	void * pData,
	char * pMapName)
{
	int		i, error = 0;
	FILE	* pOut;
	int		fileLenArray[ 256 ];

	pOut = FNX_FOPEN( outputFile, "wb" );
	if( pOut )
	{
		for( i = 0; i < numInputFiles && !error; i++ )
		{
			error = OutputFile( 
				pOut, 
				ppInputDirectories ? ppInputDirectories[ i ] : NULL, 
				ppInputFiles[ i ], 
				&fileLenArray[ i ], 
				"rb", 
				TRUE,
				pYieldFunction,
				pData );
		}
		if( !error )
		{
			if (pMapName == NULL)
				OutputGenericMap( pOut, ppInputFiles, fileLenArray, numInputFiles );
			else
				OutputSpecificMap( pMapName, pOut, ppInputFiles, fileLenArray, numInputFiles );
		}

		FNX_FCLOSE(pOut);
	}

	return error;
}

/***************************************************
 *  NAME:	WriteArbitraryMemFile
 *  DESC:	Write a mem file with given arbitrary files
 *  NOTES:	Max number of files is NUM_STATIC_FILES.
 ***************************************************/
int WriteArbitraryMemFile( 
	char * outputFile, 
	int numInputFiles, 
	char ** ppInputFiles, 
	char ** ppInputDirectories,
	YieldFunction pYieldFunction,
	void * pData )
{
	return (WriteArbitraryMemFileEx( outputFile, numInputFiles, ppInputFiles, 
							  ppInputDirectories, pYieldFunction, pData, NULL));
}

#endif  // not NO_SYSFILE_WRITES

#endif  // not FNX_OVERRIDE_FILE_CALLS

