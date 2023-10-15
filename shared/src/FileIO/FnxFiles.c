// FnxFiles.c

#include <stdarg.h>

#include "port.h"
#include "FnxFiles.h"
#include "GlobalCommon.h"

// Defining USE_MEM_FILEIO means exclusive memory file io.
// Not defining USE_MEM_FILEIO causes support for both memory
// and file io to be compiled. If a memfile is registered and
// found in the memory table, it is treated in memory; otherwise
// it is accessed via normal file io calls.

#define  InMemory(p) ((p->_flag & MEM_STRUCT) == MEM_STRUCT)

#define FNX_MF_STATIC       (0x0001)
#define FNX_MF_WRITING      (0x0002)
#define FNX_MF_MAXFILES     64

#ifndef FNX_OVERRIDE_FILE_CALLS

/***************************************************
 *  NAME:	mfSetAccess
 *  DESC:	Converts a string to access flags
 *  IN:		pFlags	- type of access requested
 *  OUT:	<none>
 *  RETURN:	access flags
 *  NOTES:	
 ***************************************************/
static int mfSetAccess(const char *pFlags)
{
	int		mode = 0;
	char	*ptr;

	if (pFlags)
	{
		ptr = FNX_STRCHR(pFlags, '+');
		switch (*pFlags)
		{
		case 'r':
			mode = (ptr) ? MF_IORW : MF_IOREAD;
			break;
		case 'w':
			mode = (ptr) ? MF_IORW : MF_IOWRT;
			break;
		case 'a':
			mode = MF_IOAPPEND;
			break;
		default:
			break;
		}
	}

	return mode;
}

/***************************************************
 *  NAME:	mfInitialize
 *  DESC:	Allocates and initializes a FILE pointer
 *  IN:		pMap - pointer to memfile entry
 *          fileNum	- index into the memory file map
 *			   mode	- access mode to be used
 *  OUT:	<none>
 *  RETURN:	FILE pointer 
 *  NOTES:	(Dependencies, Algorithms, Technical References)
 ***************************************************/
static FILE * mfInitialize(FnxMemFileMapping * pMap,
						   int fileNum,
						   int mode)
{
	MF_FILE * pStream = NULL;

	if( !(pMap->flags & FNX_MF_WRITING) && (!(pMap->flags & FNX_MF_STATIC) || mode & MF_IOREAD) )
	{
		pStream = (MF_FILE *)FNX_CALLOC( 1, sizeof(MF_FILE) );
		if( pStream )
		{
			pStream->_IsMfPtr = FNXG_MEMF_VERIFY;
			pStream->_base = pStream->_ptr = pMap->pAddr;
			pStream->_cnt = 0;
			pStream->_flag = mode | MEM_STRUCT;
			pStream->_file = fileNum;
			pStream->_bufsiz = pMap->len;

			if( mode & MF_WRITE )
			{
				pMap->flags |= FNX_MF_WRITING;
				pStream->_charbuf = pStream->_bufsiz;
			}
		}
	}

	return (FILE *)pStream;
}

/***************************************************
 *  NAME:	MemFileOpenPrivate
 *  DESC:	Opens the file specified by filename using 
 *          the given memfile table and associate data.
 *  IN:		pName	- file name
 *			   pFlags	- type of access requested
 *  OUT:	   <none>
 *  RETURN:	FILE pointer if successful, NULL otherwise
 *  NOTES:	Supports "r", "r+"
 ***************************************************/
FILE * MemFileOpenPrivate(const void * pMemFileTable,
						  const char * pName,
						  const char * pFlags)
{
	int		fileNum, mode;
	MF_FILE	* pStream = NULL;
	FnxMemFileMapping * map = (FnxMemFileMapping *)pMemFileTable;

	if( !map || !pName || !pFlags )
		return NULL;

	mode = mfSetAccess( pFlags );

	for( fileNum = 0; fileNum < FNX_MF_MAXFILES; fileNum++ )
	{
		if( !map[ fileNum ].pName )
			break;

		if( !FNX_STRICMP( pName, map[ fileNum ].pName ) )
		{
			pStream = (MF_FILE *)mfInitialize( &map[ fileNum ], fileNum, mode );
				 pStream->_privateMap = &map[ fileNum ];
			break;
		}
	}

	return (FILE *)pStream;
}

#endif  // not FNX_OVERRIDE_FILE_CALLS

long MemFileFindFirstPrivate(const void * pMemFileTable,
							 struct FNXA_FINDDATA_T * lpaFindFileData)
{
	FnxMemFileMapping * map = (FnxMemFileMapping *)pMemFileTable;
	
	if( !map || !lpaFindFileData )
		return -1;

	lpaFindFileData->_IsMfFfPtr = 0;
	lpaFindFileData->pMap = NULL;
	lpaFindFileData->_flag = 0;
	lpaFindFileData->attrib = 0;
	lpaFindFileData->nOSRet = -1;
	lpaFindFileData->input[0] = '\0';
	lpaFindFileData->name[0] = '\0';

	if( !map[ 0 ].pName || !map[ 0 ].pName[0] )
		return -1;

	lpaFindFileData->_IsMfFfPtr = FNXG_MEMFFF_VERIFY;
	lpaFindFileData->pMap = map;
	lpaFindFileData->_flag = MEM_STRUCT;
	lpaFindFileData->attrib = 0;
	lpaFindFileData->nOSRet = 1;
	lpaFindFileData->input[0] = '\0';
	FNX_STRCPY( lpaFindFileData->name, map[ 0 ].pName );

	return (long)lpaFindFileData;
}


#ifndef FNX_OVERRIDE_FILE_CALLS


/***************************************************
 *  NAME:	fStreamDestroy
 *  DESC:	Deletes am MF_FILE without closing the file.
 *  IN:		fp	- FILE pointer
 *  OUT:	   <none>
 *  RETURN:	MF_FILE pointer if successful, NULL otherwise
 *  NOTES:	
 ***************************************************/
void MemStreamDestroy(FILE *fp)
{
//	int		i, mode;
	MF_FILE	*pStream = NULL;

   if( fp )
	{
		FNX_FREE(fp);
	}
}


/***************************************************
 *  NAME:	fStreamCreate
 *  DESC:	Creates a MF_FILE from a system file pointer
 *  IN:		fp	- FILE pointer
 *  OUT:	   <none>
 *  RETURN:	MF_FILE pointer if successful, NULL otherwise
 *  NOTES:	Supports "r", "r+", "w", "w+",
 *			and "a". Ignores "b", "t", "c" and "n".
 *			Only FNX_MF_MAXFILES (64) files can be created
 *			since they are still in memory after being
 *			closed.  Files that are STATIC can only be
 *			opened for reading.
 ***************************************************/
FILE * MemStreamCreate(FILE *fp)
{
	MF_FILE	*pStream = NULL;

   if( fp )
	{
		pStream = FNX_CALLOC(1, sizeof(MF_FILE));
      if (pStream)
      {
		   pStream->_IsMfPtr = FNXG_MEMF_VERIFY;
		   pStream->_fp = fp;
      }
	}
	return (FILE *)pStream;
}


/***************************************************
 *  NAME:	MemFileOpen
 *  DESC:	Opens the file specified by filename
 *  IN:		pName	- file name
 *			   pFlags	- type of access requested
 *  OUT:	   <none>
 *  RETURN:	FILE pointer if successful, NULL otherwise
 *  NOTES:	Supports "r", "r+", "w", "w+",
 *			and "a". Ignores "b", "t", "c" and "n".
 *			Only FNX_MF_MAXFILES (64) files can be created
 *			since they are still in memory after being
 *			closed.  Files that are STATIC can only be
 *			opened for reading.
 ***************************************************/
FILE * MemFileOpen(const char *pName,
				   const char *pFlags)
{
	GlobalCommonPtr	gp = GetGlobalCommonPtr();
	int		i, mode;
	int	   found = 0;
	MF_FILE	*pStream = NULL;

	if ( !pName || !pFlags )
		return NULL;

	mode = mfSetAccess(pFlags);

	// See if the file already exists
	for ( i = 0; i < gp->NumMemFiles; i++ )
	{
		if( !FNX_STRICMP(pName, gp->pFileMap[i].pName) )
		{
			pStream = (MF_FILE *)mfInitialize( &gp->pFileMap[ i ], i, mode );
			found = 1;
			break;
		}
	}

#ifdef USE_MEM_FILEIO
	if ( !found && (mode & MF_CREATE) && gp->NumMemFiles < FNX_MF_MAXFILES )
	{
		FnxMemFileMapping	*pMap = &gp->pFileMap[gp->NumMemFiles];

		pMap->flags = 0;
		pMap->len = 0;
		pMap->pName = FNX_STRDUP( pName );
		pMap->pAddr = NULL;

		pStream = (MF_FILE*)mfInitialize( &gp->pFileMap[ gp->NumMemFiles ], gp->NumMemFiles, mode);
		if (pStream)
		{
			gp->NumMemFiles++;
		}
	}
#else
	if ( !found )
	{
		FILE * fp = FNX_MF_FOPEN( pName, pFlags ); // USE FNX_MF
		if( fp )
		{
			pStream = FNX_CALLOC(1, sizeof(MF_FILE));
			pStream->_IsMfPtr = FNXG_MEMF_VERIFY;
			pStream->_fp = fp;
		}
	}
#endif

	return (FILE *)pStream;
}

/***************************************************
 *  NAME:	MemFileClose
 *  DESC:	Closes the specified stream
 *  IN:		pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns 0 if successful
 *  NOTES:	(8/18/98) If the stream was open for writing
			the memory location and len are updated in the
			file map.
 ***************************************************/
SDWORD MemFileClose(FILE *pStreamIn)
{                         
	GlobalCommonPtr	gp = GetGlobalCommonPtr();
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
	FnxMemFileMapping	*pMap;

	FNX_ASSERT( pStreamIn );
	if( !pStreamIn )
		return 0;

	if( InMemory( pStream ) )
	{
		if( pStream->_privateMap )
			pMap = pStream->_privateMap;
		else
			pMap = &gp->pFileMap[ pStream->_file ];
		if( pMap->flags & FNX_MF_WRITING )
		{
			pMap->flags &= ~FNX_MF_WRITING;
			pMap->len = pStream->_charbuf;
			pMap->pAddr = pStream->_base;
		}
		pStream->_IsMfPtr = 0;
		FNX_FREE( pStream );
	}
	else
	{
#ifndef USE_MEM_FILEIO
		FNX_MF_FCLOSE( pStream->_fp ); // USE FNX_MF
		pStream->_fp = NULL;
		pStream->_IsMfPtr = 0;
		FNX_FREE( pStream );
#endif
	}

	return 0;
}

SDWORD MemFileUngetc(SDWORD c,
					 FILE * pStreamIn)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	

	FNX_ASSERT( pStreamIn );
	if( !pStreamIn )
		return c;

	if( InMemory( pStream ) )
	{
		if (pStream->_cnt > 0 )
		{
			pStream->_ptr--;
			pStream->_cnt--;
			*(pStream->_ptr) = (char)c;
		}
		else
		{
			c = MF_EOF;
			pStream->_flag |= MF_IOEOF;
		}
	}
	else
	{
#ifndef USE_MEM_FILEIO
		c = FNX_MF_UNGETC( c, pStream->_fp ); // USE FNX_MF
#endif
	}

	return c;
}

/***************************************************
 *  NAME:	MemFileGetc
 *  DESC:	Reads a character from a stream
 *  IN:		pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns character or EOF 
 ***************************************************/
SDWORD MemFileGetc(FILE *pStreamIn)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;
	int		c;

	FNX_ASSERT( pStreamIn );
	if( !pStreamIn )
		return 0;

	if( InMemory( pStream ) )
	{
		if (pStream->_cnt < pStream->_bufsiz)
		{
			c = *(pStream->_ptr);
			pStream->_cnt++;
			pStream->_ptr++;
		}
		else
		{
			c = MF_EOF;
			pStream->_flag |= MF_IOEOF;
		}
	}
	else
	{
#ifndef USE_MEM_FILEIO
		c = FNX_MF_GETC( pStream->_fp ); // USE FNX_MF
#endif
	}

	return c;
}

/***************************************************
 *  NAME:    MemFileGetwc
 *  DESC:    Reads a character from a stream
 *  IN:        pStream    - pointer to FILE structure
 *  OUT:    <none>
 *  RETURN:    returns character or EOF 
 ***************************************************/
wchar_t MemFileGetwc(FILE *pStreamIn)
{
    MF_FILE * pStream = (MF_FILE *)pStreamIn;
    wchar_t        c;

    FNX_ASSERT( pStreamIn );
    if( !pStreamIn )
        return 0;

    if( InMemory( pStream ) )
    {
        if (pStream->_cnt < pStream->_bufsiz)
        {
            c = *((wchar_t*)pStream->_ptr);
            pStream->_cnt++;
            pStream->_ptr+= sizeof(wchar_t);
        }
        else
        {
            c = MF_EOF;
            pStream->_flag |= MF_IOEOF;
        }
    }
    else
    {
#ifndef USE_MEM_FILEIO_ONLY
        c = FNXW_FGETC( pStream->_fp ); // USE FNX_MF
#endif
    }

    return c;
}


/***************************************************
 *  NAME:	MemFileGets
 *  DESC:	Reads a string from a stream
 *  IN:		pString	- storage location for data
 *			maxChars- maximum number of characters to read
 *			pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns a string. NULL is returned on error or end
 *			of file condition
 ***************************************************/
char *MemFileGets(char *pString,
				  SDWORD maxChars,
				  FILE *pStreamIn)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
	int		c, count;
	char	*pBuf = NULL;

	FNX_ASSERT( pStreamIn );
	if( !pStreamIn )
		return "";

	if( InMemory( pStream ) )
	{
		if (pStream->_flag & MF_READ && !MemFileEof((FILE*)pStream))
		{
			if (pString && maxChars > 0)
			{
				pBuf = pString;
				for (count = 0;
					count < maxChars-1 && (c = MemFileGetc((FILE *)pStream)) != MF_EOF;
					count++)
				{
					*pBuf++ = c;
					if (c == '\n')
						break;
				}
				*pBuf = '\0';
				pBuf = pString;
			}
		}
	}
	else
	{
#ifndef USE_MEM_FILEIO
		pBuf = FNX_MF_FGETS( pString, maxChars, pStream->_fp ); // USE FNX_MF
#endif
	}

	return pBuf;
}

/***************************************************
 *  NAME:    MemFileGetws
 *  DESC:    Reads a string from a stream
 *  IN:        pString    - storage location for data
 *            maxChars- maximum number of characters to read
 *            pStream    - pointer to FILE structure
 *  OUT:    <none>
 *  RETURN:    returns a string. NULL is returned on error or end
 *            of file condition
 ***************************************************/
wchar_t *MemFileGetws(wchar_t *pString,
                  SDWORD maxChars,
                  FILE *pStreamIn)
{
    MF_FILE * pStream = (MF_FILE *)pStreamIn;    
    wchar_t        c;
    int        count;
    wchar_t    *pBuf = NULL;

    FNX_ASSERT( pStreamIn );
    if( !pStreamIn )
        return L"";

    if( InMemory( pStream ) )
    {
        if (pStream->_flag & MF_READ && !MemFileEof((FILE*)pStream))
        {
            if (pString && maxChars > 0)
            {
                pBuf = pString;
                for (count = 0;
                    count < maxChars-1 && (c = MemFileGetwc((FILE *)pStream)) != MF_EOF;
                    count++)
                {
                    *pBuf++ = c;
                    if (c == '\n')
                        break;
                }
                *pBuf = '\0';
                pBuf = pString;
            }
        }
    }
    else
    {
#ifndef USE_MEM_FILEIO_ONLY
        pBuf = FNXW_FGETS( pString, maxChars, pStream->_fp ); // USE FNX_MF
#endif
    }

    return pBuf;
}


/***************************************************
 *  NAME:	MemFileRead
 *  DESC:	Reads data from a stream
 *  IN:		pBuf	- storage location for data
 *			size	- item size in bytes
 *			count	- maximum number of items to be read
 *			pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns the number of full items actually read
 ***************************************************/
usize MemFileRead(voidPtr pBuf,
				  usize size,
				  usize count,
				  FILE *pStreamIn)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
#ifdef BESTA
 long		numBytes, bytesLeft;
 long		itemsRead = 0;
#else
	int		numBytes, bytesLeft;
	int		itemsRead = 0;
#endif

	FNX_ASSERT( pStreamIn );
	if( !pStreamIn )
		return 0;

	if( InMemory( pStream ) )
	{
		if (pStream->_flag & MF_READ && !MemFileEof((FILE*)pStream))
		{
			numBytes = size * count;
			bytesLeft = pStream->_bufsiz - pStream->_cnt;
			if (numBytes)
			{
				if (bytesLeft > 0)
				{
					itemsRead = count;
					if (numBytes > bytesLeft)
					{
						numBytes = bytesLeft;
						itemsRead = numBytes / size;
						pStream->_flag |= MF_IOEOF;
					}
					memcpy(pBuf, pStream->_ptr, numBytes);
					pStream->_cnt += numBytes;
					pStream->_ptr += numBytes;
				}
				else
				{
				   pStream->_flag |= MF_IOEOF;
				}
			}
		}
	}
	else
	{
#ifndef USE_MEM_FILEIO
		itemsRead = FNX_MF_FREAD( pBuf, size, count, pStream->_fp ); // USE FNX_MF
#endif
	}

	return itemsRead;
}

/***************************************************
 *  NAME:	MemFileWrite
 *  DESC:	Writes data to a stream
 *  IN:		pBuf	- pointer to data to be written
 *			size	- item size in bytes
 *			count	- maximum number of items to be written
 *			pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns the number of full items actually written
 ***************************************************/
usize MemFileWrite(const voidPtr pBuf,
				   usize size,
				   usize count,
				   FILE *pStreamIn)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
	int		numBytes, newSize;
	usize	itemsWritten = 0;
	char	*ptr;

	FNX_ASSERT( pStreamIn );
	if( !pStreamIn )
		return 0;

	if( InMemory( pStream ) )
	{
		if (pStream->_flag & MF_WRITE)
		{
			numBytes = size * count;
			if (numBytes)
			{
				itemsWritten = count;
				if (pStream->_flag & MF_IOAPPEND)
				{
					pStream->_cnt = pStream->_charbuf;
				}
				if (pStream->_cnt + numBytes > pStream->_bufsiz)
				{
				   // keep memory file size a multiple of MAX_WBUF_SIZE
					newSize = (pStream->_cnt + numBytes + MAX_WBUF_SIZE - 1) /
							   MAX_WBUF_SIZE * MAX_WBUF_SIZE;
					ptr = (char *)FNX_REALLOC(pStream->_base, newSize);
					if (ptr)
					{
						pStream->_base = ptr;
						pStream->_ptr = ptr + pStream->_cnt;
						pStream->_bufsiz = newSize;
					}
					else
					{
						itemsWritten = 0;
					}
				}
				if (itemsWritten)
				{
					memcpy(pStream->_ptr, pBuf, numBytes);
					pStream->_cnt += numBytes;
					pStream->_ptr += numBytes;
					if (pStream->_charbuf < pStream->_cnt)
					{
						pStream->_charbuf = pStream->_cnt;
					}
				}
			}
		}
	}
	else
	{
#ifndef USE_MEM_FILEIO
		itemsWritten = FNX_MF_FWRITE( pBuf, size, count, pStream->_fp ); // USE FNX_MF
#endif
	}

	return itemsWritten;
}

/***************************************************
 *  NAME:	MemFileSeek
 *  DESC:	Moves the file pointer to a specified location
 *  IN:		pStream	- pointer to FILE structure
 *			offset	- number of bytes from origin
 *			origin	- initial position
 *  OUT:	<none>
 *  RETURN:	returns 0 if successful
 ***************************************************/
SDWORD MemFileSeek(FILE *pStreamIn,
				   SDWORD offset,
				   int origin)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	

	FNX_ASSERT( pStreamIn );
	if( !pStreamIn )
		return -1;
   
	if( InMemory( pStream ) )
	{
		switch (origin)
		{
			case MF_SEEK_CUR:
				pStream->_cnt += offset;
				break;
			case MF_SEEK_END:
				pStream->_cnt = pStream->_bufsiz + offset;
				break;
			case MF_SEEK_SET:
				pStream->_cnt = offset;
				break;
		}
		pStream->_ptr = pStream->_base + pStream->_cnt;
		pStream->_flag &= ~MF_IOEOF;
	}
	else
	{
#ifndef USE_MEM_FILEIO
		FNX_MF_FSEEK( pStream->_fp, offset, origin ); // USE FNX_MF
#endif
	}

	return 0;
}

/***************************************************
 *  NAME:	MemFileTell
 *  DESC:	Gets the current position of a file pointer
 *  IN:		pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns the current file position
 ***************************************************/
SDWORD MemFileTell(FILE *pStreamIn)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
   
	FNX_ASSERT( pStreamIn );
	if( !pStreamIn )
		return 0;

	if( InMemory( pStream ) )
	{
		return pStream->_cnt;
	}
	else
	{
#ifndef USE_MEM_FILEIO
		return FNX_MF_FTELL( pStream->_fp ); // USE FNX_MF
#endif
	}
	return 0;
}

/***************************************************
 *  NAME:	mRewind
 *  DESC:	Repositions the file pointer to the beginning of a file
 *  IN:		pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	<none>
 ***************************************************/
void MemFileRewind(FILE *pStreamIn)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	

	FNX_ASSERT( pStreamIn );
	if( !pStreamIn )
		return;
   
	if( InMemory( pStream ) )
	{
		pStream->_cnt = 0;
		pStream->_ptr = pStream->_base;
		pStream->_flag &= ~MF_IOEOF;
	}
	else
	{
#ifndef USE_MEM_FILEIO
		// some platforms do not have a rewind
		FNX_MF_FSEEK( pStream->_fp, 0, MF_SEEK_SET ); // USE FNX_MF
		FNX_MF_CLEARERR( pStream->_fp );            // USE FNX_MF
#endif
	}
}

/***************************************************
 *  NAME:	MemFileFlush
 *  DESC:	Flushes a stream
 *  IN:		pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	<none>
 *  NOTES:
***************************************************/
SDWORD MemFileFlush(FILE *pStreamIn)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	

	FNX_ASSERT( pStreamIn );
	if( !pStreamIn )
		return 0;

	if( InMemory( pStream ) )
	{
      // do nothing with the memory files
	}
	else
	{
#ifndef USE_MEM_FILEIO
		return FNX_MF_FLUSH( pStream->_fp );  // USE FNX_MF
#endif
	}

   return 0;
}

/***************************************************
 *  NAME:	MemFileEof
 *  DESC:	Tests for end-of-file on a stream
 *  IN:		pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns a nonzero value after the first read operation
 *			that attempts to read past the end of the file,
 *			returns 0 if the current position is not end of file
 ***************************************************/
SDWORD MemFileEof(FILE *pStreamIn)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
   
	FNX_ASSERT( pStreamIn );
	if( !pStreamIn )
		return 0;

	if( InMemory( pStream ) )
	{
   		return pStream->_flag & MF_IOEOF;
	}
	else
	{
#ifndef USE_MEM_FILEIO
		return FNX_MF_FEOF( pStream->_fp ); // USE FNX_MF
#endif
	}
	return 0;
}

int MemFilePutc(int c,
				FILE *pStreamIn)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
   
	FNX_ASSERT( pStream );
	if( !pStream )
		return 0;

	if( InMemory( pStream ) )
	{
   		FNX_ASSERT( 0 ); // not implemented for memory files
	}
	else
	{
#ifndef USE_MEM_FILEIO
		return FNX_MF_FPUTC( c, pStream->_fp ); // USE FNX_MF
#endif
	}

	return 0;
}

int MemFilePuts(const char * s,
				FILE *pStreamIn)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
   
	FNX_ASSERT( pStream );
	if( !pStream )
		return 0;
   
	if( InMemory( pStream ) )
	{
   		FNX_ASSERT( 0 ); // not implemented for memory files
	}
	else
	{
#ifndef USE_MEM_FILEIO
		return FNX_MF_FPUTS( s, pStream->_fp ); // USE FNX_MF
#endif
	}

	return 0;
}

int MemFileSetpos(FILE *pStreamIn,
				  fpos_t * pos)
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
   
	FNX_ASSERT( pStream );
	if( !pStream )
		return 0;
   
	if( InMemory( pStream ) )
	{
   		FNX_ASSERT( 0 ); // not implemented for memory files
	}
	else
	{
#ifndef USE_MEM_FILEIO
		return FNX_MF_FSETPOS( pStream->_fp, pos ); // USE FNX_MF
#endif
	}

	return 0;
}

int MemFileError( FILE * pStreamIn )
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
   
	FNX_ASSERT( pStream );
	if( !pStream )
		return 0;
   
	if( InMemory( pStream ) )
	{
//   		FNX_ASSERT( 0 ); // not implemented for memory files
   		return 0;
	}
	else
	{
#ifndef USE_MEM_FILEIO
		return FNX_MF_FERROR( pStream->_fp ); // USE FNX_MF
#endif
	}

	return 0;
}

void MemFileClearerr( FILE * pStreamIn )
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
   
	FNX_ASSERT( pStream );
	if( !pStream )
		return;
   
	if( InMemory( pStream ) )
	{
   		FNX_ASSERT( 0 ); // not implemented for memory files
	}
	else
	{
#ifndef USE_MEM_FILEIO
		FNX_MF_CLEARERR( pStream->_fp ); // USE FNX_MF
#endif
	}
}

int MemFilePrintf( FILE * pStreamIn, const char * pFormat, ... )
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
   
	FNX_ASSERT( pStream );
	if( !pStream )
		return 0;
   
	if( InMemory( pStream ) )
	{
   		FNX_ASSERT( 0 ); // not implemented for memory files
	}
	else
	{
#ifndef USE_MEM_FILEIO
		va_list argptr;
		int ret;

		va_start( argptr, pFormat );
		ret = FNX_MF_VFPRINTF( pStream->_fp, pFormat, argptr );   // USE FNX_MF
		va_end( argptr );
		return ret;
#endif
	}

	return 0;
}

int MemFileScanf( FILE * pStreamIn, const char * pFormat, ... )
{
	MF_FILE * pStream = (MF_FILE *)pStreamIn;	
   
	FNX_ASSERT( pStream );
	if( !pStream )
		return 0;
   
	if( InMemory( pStream ) )
	{
   		FNX_ASSERT( 0 ); // not implemented for memory files
	}
	else
	{
#ifndef USE_MEM_FILEIO
		// Do our best here since vscanf does not exist. 
		// Simple cases are handled by parsing the % delimiter which separates the variables.
		va_list argptr;
		int ret;
		char * pPos;
		char subFormat[ 256 ];

		va_start( argptr, pFormat );
		pPos = (char *)pFormat;
		while( *pPos )
		{
			*subFormat = 0;
			memset( subFormat, 0, 256 );
			while( *pPos )
			{
				int subLen = FNX_STRLEN( subFormat );
				if( *pPos == '%' && subLen )
					break;
				*(subFormat + subLen) = *pPos;
				pPos++;
			}
			if( FNX_STRSTR( subFormat, "%d" ) )
			{
				int * arg = va_arg( argptr, int * );
				ret = FNX_MF_FSCANF( pStream->_fp, subFormat, arg );   // USE FNX_MF
			}
			else if( FNX_STRSTR( subFormat, "%ld" ) )
			{
				long * arg = va_arg( argptr, long * );
				ret = FNX_MF_FSCANF( pStream->_fp, subFormat, arg );   // USE FNX_MF
			}
			else if( FNX_STRSTR( subFormat, "%s" ) )
			{
				char * arg = va_arg( argptr, char * );
				ret = FNX_MF_FSCANF( pStream->_fp, subFormat, arg );   // USE FNX_MF
			}
			else
			{
				// unsupported format, must be written or code changed
				FNX_ASSERT( 0 );
			}
		}
		va_end( argptr );
		return ret;
#endif
	}

	return 0;
}

int MemFileRemove( const char * file )
{
	GlobalCommonPtr	gp = GetGlobalCommonPtr();
	BOOL inMemory = FALSE;
	int ix;

	for( ix = 0; ix < gp->NumMemFiles; ix++ )
	{
		if( FNX_STRICMP( file, gp->pFileMap[ix].pName ) == 0 )
		{
			inMemory = TRUE;
			break;
		}
	}

	if( inMemory )
	{
		FNX_ASSERT( 0 ); // not implemented for memory files
	}
	else
	{
#ifndef USE_MEM_FILEIO
		return FNX_MF_REMOVE( file ); // USE FNX_MF
#endif
	}

	return 0;
}

int MemFileRename( const char * oldname, const char * newname )
{
	GlobalCommonPtr	gp = GetGlobalCommonPtr();
	BOOL inMemory = FALSE;
	int ix;

	for( ix = 0; ix < gp->NumMemFiles; ix++ )
	{
		if( FNX_STRICMP( oldname, gp->pFileMap[ix].pName ) == 0 )
		{
			inMemory = TRUE;
			break;
		}
	}

	if( inMemory )
	{
		FNX_ASSERT( 0 ); // not implemented for memory files
	}
	else
	{
#ifndef USE_MEM_FILEIO
		return FNX_MF_RENAME( oldname, newname ); // USE FNX_MF
#endif
	}

	return 0;
}

#endif  // not FNX_OVERRIDE_FILE_CALLS


long MemFileFindFirst( const char *lpaRootName, struct FNXA_FINDDATA_T * lpaFindFileData )
{
	GlobalCommonPtr	gp = GetGlobalCommonPtr();

	if( !lpaRootName || !lpaFindFileData )
		return -1;

	lpaFindFileData->_IsMfFfPtr = 0;
	lpaFindFileData->pMap = NULL;
	lpaFindFileData->_flag = 0;
	lpaFindFileData->attrib = 0;
	lpaFindFileData->nOSRet = -1;
	lpaFindFileData->input[0] = '\0';
	lpaFindFileData->name[0] = '\0';

	if( gp->NumMemFiles && gp->pFileMap )
	{
		int nRet=0;

		lpaFindFileData->_IsMfFfPtr = FNXG_MEMFFF_VERIFY;
		lpaFindFileData->pMap = gp->pFileMap;
		lpaFindFileData->_flag = MEM_STRUCT;
		FNX_STRCPY( lpaFindFileData->input, lpaRootName );
		lpaFindFileData->nOSRet = 0;	// set for next subscript to return
		nRet = MemFileFindNext( -1, lpaFindFileData );
		if( -1 == nRet )
			MemFileFindClose( (long)lpaFindFileData );
		else
			return (long)lpaFindFileData;
	}

#ifndef USE_MEM_FILEIO
	{
		struct FNX_MF_FINDDATA_T FndData;

		lpaFindFileData->nOSRet = FNX_MF_FINDFIRST((char*)lpaRootName, &FndData); // USE FNX_MF
		if (-1 == lpaFindFileData->nOSRet)
		{
			return -1L;
		}
		lpaFindFileData->attrib = FndData.attrib;
		FNX_STRCPY(lpaFindFileData->name, FndData.name);
#	ifdef OS_UNIX
		lpaFindFileData->glob = FndData.glob;
		lpaFindFileData->next = FndData.next;
		lpaFindFileData->nOSRet = lpaFindFileData;
#	endif
	}
	return (long)lpaFindFileData;
#else  // USE_MEM_FILEIO
	return -1;
#endif  // USE_MEM_FILEIO
}

int MemFileFindNext( long nFFRtn, struct FNXA_FINDDATA_T * lpaFindFileData )
{
	FnxMemFileMapping * pFildMap=NULL;

	if ( ! nFFRtn || ! lpaFindFileData)
	{
		return -1;
	}
	pFildMap =(FnxMemFileMapping*)lpaFindFileData->pMap;
	if (InMemory(lpaFindFileData) && lpaFindFileData->pMap)
	{
		for(;;)
		{
			char * pMfStr=pFildMap[ lpaFindFileData->nOSRet ].pName;
			if ( ! pMfStr || ! pMfStr[0])
			{
				return -1;
			}
			{
				int nMfLen=FNX_STRLEN( pMfStr );
				int nInLen=FNX_STRLEN( lpaFindFileData->input );
				char * pWildCard = FNX_STRCHR( lpaFindFileData->input, '*' );	// find wildcard ("*") in input string

				if (( ! FNX_STRNICMP( lpaFindFileData->input, pMfStr, nInLen ))	// if string matches exactly
						||                                                      // OR
						(
							pWildCard &&										// there is a wild card  AND
							( ! FNX_STRNICMP(lpaFindFileData->input, pMfStr, pWildCard-lpaFindFileData->input)) && // before the wild card matches AND
							( ! FNX_STRICMP(&lpaFindFileData->input[pWildCard-lpaFindFileData->input+1], &pMfStr[nMfLen-FNX_STRLEN(&lpaFindFileData->input[pWildCard-lpaFindFileData->input+1])]))  // after the wildcard matches the end of the string
						)
				)	 // THEN
				{
					lpaFindFileData->_IsMfFfPtr = FNXG_MEMFFF_VERIFY;
					FNX_STRCPY( lpaFindFileData->name, pMfStr );
					lpaFindFileData->nOSRet++;	// set for next subscript to return
					break;
				}
				lpaFindFileData->nOSRet++;
			}
		}
		return 0;
	}
	else
	{
#ifndef USE_MEM_FILEIO
		struct FNX_MF_FINDDATA_T FndData;
		int nRet = FNX_MF_FINDNEXT(lpaFindFileData->nOSRet, &FndData); // USE FNX_MF
		if ( -1 == nRet )
		{
			return -1;
		}
		lpaFindFileData->attrib = FndData.attrib;
		FNX_STRCPY(lpaFindFileData->name, FndData.name);
#	ifdef OS_UNIX
		lpaFindFileData->glob = FndData.glob;
		lpaFindFileData->next = FndData.next;
		lpaFindFileData->nOSRet = lpaFindFileData;
#	endif
#else  // USE_MEM_FILEIO
		return -1;
#endif  // USE_MEM_FILEIO
	}
	return 0;
}

int MemFileFindClose( long nFFRtn )
{
	int		rtn;
	struct FNXA_FINDDATA_T* FndData = (struct FNXA_FINDDATA_T *)nFFRtn;

	if ( ! nFFRtn || (-1 == nFFRtn))
	{
		rtn = -1;
	}
	if (FNXG_MEMFFF_VERIFY == FndData->_IsMfFfPtr)
	{
		FndData->_IsMfFfPtr = 0;
		rtn = 0;
	}
	else
	{
#ifndef USE_MEM_FILEIO
		rtn = FNX_MF_FINDCLOSE( FndData->nOSRet ); // USE FNX_MF
#endif
		rtn = -1;
	}
	return rtn;
}


