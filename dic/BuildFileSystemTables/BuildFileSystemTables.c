/*C_HEADER_FILE****************************************************************
FILE			:	BuildFileSystemTables.cpp
DESC			:	
TABS			:	3
OWNER			:	
DATE CREATED	:	

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
//#include <stdlib.h> //moved to port.h for each platform mlt 02/23/06
//#include <stdio.h> //moved to port.h for each platform mlt 02/23/06
//#include <string.h> //moved to port.h for each platform mlt 02/23/06
#include "port.h"
#include "FileSystemData.h"

#ifndef bool
#define bool char
#endif

typedef struct _tagTableData
{
	char	*sTableName;		// Data array name for later identification
	unsigned short
			wBitFlag;
	unsigned int		
			nValues,			// Number of values in array
			offset;				// offset of file system table, used for testing
	int		nElementSize;		// size of each element in the array
	bool	bSigned;			// flag to indicate signed or unsigned
	bool	bGTrieNode;			// flag to indicate that array type is a GTrieNode
	void	*pValues;			// pointer to array of data
	struct _tagTableData *pNext;// pointer to next table

}TABLE_DATA;

/*FUNCTION_HEADER**********************
 * NAME:    ;ByteSwap32
 * DESC:    Swap the bytes in a 4-byte integer
 * IN:      i - 32-bit (4-byte) integer to swap bytes in
 * OUT:     n/a
 * RETURN:  i with bytes swapped
 * NOTES:   Unlike big/little-to-little/big-Endian routines,
              this one swaps the bytes without checking to make
              sure it needs to be done.  (This is about 15% faster)
 *END_HEADER***************************/
static unsigned int ByteSwap32(unsigned int i)
{
   return (0x000000FF & i >> 24) | (0x00FF0000 & i << 8) | (0x0000FF00 & i >> 8) | (0xFF000000 & i << 24);
}

/*FUNCTION_HEADER**********************
 * NAME:    ;ByteSwap16
 * DESC:    Swap the bytes in a 2-byte integer
 * IN:      i - 16-bit (2-byte) integer to swap bytes in
 * OUT:     n/a
 * RETURN:  i with bytes swapped
 * NOTES:   Unlike big/little-to-little/big-Endian routines,
              this one swaps the bytes without checking to make
              sure it needs to be done.  (This is about 15% faster)
 *END_HEADER***************************/
static unsigned short ByteSwap16(unsigned short i)
{
   return ((unsigned short) 0x00FFU & i >> 8) | ((unsigned short) 0xFF00U & i << 8);
}


bool ParseString(char *sBuf, char *sString, int nMax)
{
	char *pc1, *pc2;

	if( (pc1 = FNX_STRCHR(sBuf, '"')) != NULL )
	{
		pc1++;
		if( (pc2 = FNX_STRCHR(pc1, '"')) != NULL )
		{
			*pc2 = 0x00;
			if( pc2-pc1 < nMax )
			{
				FNX_STRCPY(sString, pc1);
			}
			else
			{
				FNX_STRNCPY(sString, pc1, nMax-2);
				sString[nMax-1] = 0x00;
			}

			// Check to see if there are any other strings in sBuf
			pc2++;
			if( (pc1 = FNX_STRCHR(pc2, '"')) != NULL )
				sBuf = pc1;

			return 1;
		}
	}

	return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;ReadGTrieNode
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	Sample data lines

	{0x0000,    0,    1,   53,   14,   10,    0,    0,    0,  128 }, 
	{"s/s/",    0,    0,   54,   15,   21,    0,    0,    0,    0 }, 

 *END_HEADER***************************/
bool ReadGTrieNode(char *sBuf, GTRIENODE *pGTrieNode)
{
	char *pc, *pc2;
	int	 ret;

	if( (pc = FNX_STRSTR(sBuf, "{0x0000,")) != NULL )
	{
		pGTrieNode->sName[0] = 0x00;
	}
	else if( (pc = FNX_STRSTR(sBuf, "{\"")) != NULL )
	{
		pc += 2;
		pc2 = pc;
		while( *pc2 != '\"' )
			pc2++;
		*pc2 = 0x00;
		FNX_STRCPY(pGTrieNode->sName, FNX_STRDUP(pc));
		*pc2 = '\"';
	}

	while( *pc != ' ' )
		pc++;
	while( *pc == ' ' )
		pc++;

	ret = sscanf(pc, "%d, %d, %d, %d, %d, %d, %d, %d, %d",
		&pGTrieNode->alt,
		&pGTrieNode->what,
		&pGTrieNode->right,
		&pGTrieNode->index,
		&pGTrieNode->typeinfo,
		&pGTrieNode->info.status,
		&pGTrieNode->info.counter,
		&pGTrieNode->info.counterB,
		&pGTrieNode->info.parameter);

	if( ret == 9 )
		return 1;
	else
	{
		FNX_PRINTF("Error: Didn't read all values in GTrieNode!\n");
		return 0;
	}

}

/*FUNCTION_HEADER**********************
 * NAME:	;WriteGTrieNode
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void WriteGTrieNode(FILE *fp, GTRIENODE *pGTrieNode, unsigned int *piOffset, bool bBigEndian)
{
	char c=0x00;
	unsigned short wValue;
	unsigned int curpos,
				 offset=0;

	if( pGTrieNode->sName[0] == 0x00 )
	{
		offset = 0;
		FNX_FWRITE(&offset, sizeof(int), 1, fp);
	}
	else
	{
		offset = *piOffset;
		if( bBigEndian )	
			offset = ByteSwap32(offset);
		FNX_FWRITE(&offset, sizeof(int), 1, fp);			// write offset to data
		curpos = FNX_FTELL(fp);								// save current file location
		FNX_FSEEK(fp, *piOffset, SEEK_SET);					// seek to data location
		FNX_FWRITE(pGTrieNode->sName, sizeof(char), FNX_STRLEN(pGTrieNode->sName), fp);	// write data
		FNX_FWRITE(&c, sizeof(char), 1, fp);				// write null terminating character
		*piOffset += FNX_STRLEN(pGTrieNode->sName) + 1;		// update offset for next data string
		FNX_FSEEK(fp, curpos, SEEK_SET);					// seek back to table data
	}

	wValue = pGTrieNode->alt;
	if( bBigEndian )	wValue = ByteSwap16(wValue);
	FNX_FWRITE(&wValue, sizeof(U16), 1, fp);
	
	wValue = pGTrieNode->what;
	if( bBigEndian )	wValue = ByteSwap16(wValue);
	FNX_FWRITE(&wValue, sizeof(U16), 1, fp);
	
	wValue = pGTrieNode->right;
	if( bBigEndian )	wValue = ByteSwap16(wValue);
	FNX_FWRITE(&wValue, sizeof(U16), 1, fp);
	
	wValue = pGTrieNode->index;
	if( bBigEndian )	wValue = ByteSwap16(wValue);
	FNX_FWRITE(&wValue, sizeof(U16), 1, fp);
	
	wValue = pGTrieNode->typeinfo;
	FNX_FWRITE(&wValue, sizeof(char), 1, fp);
	
	wValue = pGTrieNode->info.status;
	if( bBigEndian )	wValue = ByteSwap16(wValue);
	FNX_FWRITE(&wValue, sizeof(U16), 1, fp);
	
	wValue = pGTrieNode->info.counter;
	if( bBigEndian )	wValue = ByteSwap16(wValue);
	FNX_FWRITE(&wValue, sizeof(U16), 1, fp);
	
	wValue = pGTrieNode->info.counterB;
	if( bBigEndian )	wValue = ByteSwap16(wValue);
	FNX_FWRITE(&wValue, sizeof(U16), 1, fp);
	
	wValue = pGTrieNode->info.parameter;
	if( bBigEndian )	wValue = ByteSwap16(wValue);
	FNX_FWRITE(&wValue, sizeof(U16), 1, fp);

}

/*FUNCTION_HEADER**********************
 * NAME:	;StripLeadingStuff
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
char *StripLeadingStuff(char *sBuf)
{
	char *pc;

	for( pc=sBuf; pc && *pc && *pc == ' '; pc++ )	// Skip leading spaces
		;

	if( FNX_STRSTR(pc, "/*") == pc )					// Look for a leading comment 
	{
		if( (pc = FNX_STRSTR(pc, "*/")) )				// Find closing comment characters
		{
			pc += 2;
			while( pc && *pc && *pc == ' ' )		// Skip leading spaces after comment
				pc++;
		}
	}

	return pc;

}

/*FUNCTION_HEADER**********************
 * NAME:	;ReadValuesFromBuf
 * DESC: 	Read a hand full of values from a line of text
 * IN:		sBuf - the line of text
			pValue - pointer to an array to hold the data
			iSize - the number of bytes per element in the array
			nMax - the maximum number of elements that the array can hold
			bSigned - flag for signed/unsigned data
 * OUT:		data in pValue
 * RETURN:	number of data values read
 * NOTES:	
 *END_HEADER***************************/
int ReadValuesFromBuf(char *sBuf, void *pValue, int iSize, int nMax, bool bSigned)
{
	char *pc;
	int	 iBase=10;
	int	 i;

	if( (pc = StripLeadingStuff(sBuf)) == NULL )
		return 0;

	if( FNX_STRSTR(sBuf, "0x") )
		iBase = 16;

	for( i=0; pc && *pc != 0x00 && *pc != '\n' && *pc != '\r' && i<nMax; i++ )
	{
		if( bSigned )
		{
			switch(iSize)
			{
				case 1:	((char *)pValue)[i]		= (char)strtol(pc, &pc, iBase);		break;
				case 2: ((short *)pValue)[i]	= (short)strtol(pc, &pc, iBase);	break;
				case 4: ((int *)pValue)[i]		= (int)strtol(pc, &pc, iBase);		break;
			}
		}
		else
		{
			switch(iSize)
			{
				case 1:	((unsigned char *)pValue)[i]	= (unsigned char)strtol(pc, &pc, iBase);	break;
				case 2: ((unsigned short *)pValue)[i]	= (unsigned short)strtol(pc, &pc, iBase);	break;
				case 4: ((unsigned int *)pValue)[i]		= (unsigned int)strtol(pc, &pc, iBase);		break;
			}
		}

		if( *pc == 0x00 || *pc == '\n' )
		{
			i++;									// Increment to a count instead of an index
			break;
		}

		pc++;										// Move past the stop character

		while( *pc == ' ' )							// Skip spaces
			pc++;
	}

	return i;

}

#define MAX_VALUES 128
/*FUNCTION_HEADER**********************
 * NAME:	;ReadTablesInFile
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
TABLE_DATA *ReadTablesInFile(char *sFile)
{
	bool	bReading=0,
			bDebug=0;
	char	sBuf[MAX_VALUES];
	char	*pc1, *pc2;
	unsigned short 
			wBitFlag;
	int		i, j, 
			nValues,
			nElementSize;
	char	pValues[MAX_VALUES];
	
	FILE	*fp;
	TABLE_DATA 
			*pTableHead=NULL, *pTbl=NULL;
	
	if( sFile == NULL ||
		(fp = FNX_FOPEN(sFile, "rt")) == NULL )
	{
		FNX_PRINTF("Error: Can't open file %s\n", sFile);
		return NULL;
	}

	while( FNX_FGETS(sBuf, 128, fp) )
	{
		if( sBuf[0] == 0x00 || 
			sBuf[0] == '\n' ||
			sBuf[0] == '\r' ||
			sBuf[0] == ';' ||
			(sBuf[0] == '/' && sBuf[1] == '/') )
			continue;

		if( !bDebug && !bReading &&
			((pc2 = FNX_STRSTR(sBuf, "[] = {")) != NULL ||
			 (pc2 = FNX_STRSTR(sBuf, "] = {")) != NULL ||
			 (pc2 = FNX_STRSTR(sBuf, "[]={")) != NULL ||
			 (pc2 = FNX_STRSTR(sBuf, "[]= {")) ) &&
			 FNX_STRCHR(sBuf, '}') == NULL )
		{												// Found the start of a table
			nElementSize = 0;			// Initialize to 0 so we can tell later if a known type was found
			wBitFlag = 0;

			// Check for a known type
			if( FNX_STRSTR(sBuf, "U8") ||
				FNX_STRSTR(sBuf, "GERLETTER") )
			{
				wBitFlag |= FSD_BYTES1;
				nElementSize = sizeof(char);
			}
			else if( FNX_STRSTR(sBuf, "U16") )
			{
				wBitFlag |= FSD_BYTES2;
				nElementSize = sizeof(short);
			}
			else if( FNX_STRSTR(sBuf, "U32") )
			{
				wBitFlag |= FSD_BYTES4;
				nElementSize = sizeof(int);
			}
			else if( FNX_STRSTR(sBuf, "const char *") )
			{
				wBitFlag |= FSD_SIGNED;
				wBitFlag |= FSD_STRING;
				nElementSize = FSD_MAXSTRING;
			}
			else if( FNX_STRSTR(sBuf, "CONST listtable") )
			{
				wBitFlag |= FSD_SIGNED;
				wBitFlag |= FSD_ITLIST;
				nElementSize = 3 * sizeof(char);
			}
			else if( FNX_STRSTR(sBuf, "CONST ruletable") )
			{
				wBitFlag |= FSD_SIGNED;
				wBitFlag |= FSD_ITRULE;
				nElementSize = 4 * sizeof(char);
			}
			else if( FNX_STRSTR(sBuf, "char") )
			{
				if( FNX_STRSTR(sBuf, "unsigned") == NULL )
				{
					wBitFlag |= FSD_SIGNED;
				}

				wBitFlag |= FSD_BYTES1;
				nElementSize = sizeof(char);
			}
			else if( FNX_STRSTR(sBuf, "short") )
			{
				if( FNX_STRSTR(sBuf, "unsigned") == NULL )
					wBitFlag |= FSD_SIGNED;
				wBitFlag |= FSD_BYTES2;
				nElementSize = sizeof(short);
			}
			else if( FNX_STRSTR(sBuf, "int") )
			{
				if( FNX_STRSTR(sBuf, "unsigned") == NULL )
					wBitFlag |= FSD_SIGNED;
				wBitFlag |= FSD_BYTES4;
				nElementSize = sizeof(int);
			}
			else if( FNX_STRSTR(sBuf, "GTrieNode") )
			{
				wBitFlag |= FSD_GTRIE;
				nElementSize = sizeof(GTRIENODE);
			}

			if( nElementSize > 0 )
			{
				bReading=1;									// Set state to bReading == true

				if( pTableHead == NULL )
				{
					pTableHead = pTbl = (TABLE_DATA *)calloc(1, sizeof(TABLE_DATA));
				}
				else
				{
					pTbl->pNext = (TABLE_DATA *)calloc(1, sizeof(TABLE_DATA));
					pTbl = pTbl->pNext;
				}

				if( wBitFlag & FSD_SIGNED )
					pTbl->bSigned = 1;
				pTbl->nElementSize = nElementSize;
				pTbl->wBitFlag = wBitFlag;

				// Get the table name
				while( *pc2 != '[' )						// Backup to the beginning array character '['
					pc2--;
				while( *(pc2-1) == ' ' && pc2 > sBuf )		// Skip any trailing spaces as we start backing up.
					pc2--;
				pc1 = pc2-1;								// Find the beginning of the table name
				while( *pc1 != ' ' && pc1 >= sBuf)			// Backup until we find the beginning of the name
					pc1--;
				if( pc1 > sBuf )
				{
					char c = *pc2;

					pc1++;									// advance from the space before the name to the beginning of the name
					*pc2 = 0x00;							// null terminate the name
					pTbl->sTableName = FNX_STRDUP(pc1);			// copy the name
					*pc2 = c;

					for( pc1=pTbl->sTableName; *pc1; pc1++ )
						*pc1 = FNX_TOUPPER(*pc1);

					FNX_PRINTF("\tFound Table: %s\n", pTbl->sTableName);
				}
			}
			else
			{
				bReading = 0;
			}

		}
		else if( FNX_STRSTR(sBuf, "#ifdef DEB") ||				// Don't include these sections
				 FNX_STRSTR(sBuf, "#if 0") )
		{
			bDebug = 1;
			bReading = 0;
		}
		else if( FNX_STRSTR(sBuf, "};") ||
				 FNX_STRSTR(sBuf, "} ;") )
		{
			bReading = 0;
		}
		else if( FNX_STRSTR(sBuf, "#endif") )
		{
			bDebug = 0;
			bReading = 0;
		}
		else if( bReading )
		{

			if( pTbl->wBitFlag & FSD_GTRIE )
			{
				GTRIENODE GTrieNode;
				if( ReadGTrieNode(sBuf, &GTrieNode) )
				{
					pTbl->pValues = (void *)realloc(pTbl->pValues, (pTbl->nValues+1)*pTbl->nElementSize);
					((GTRIENODE *)pTbl->pValues)[pTbl->nValues] = GTrieNode;
					pTbl->nValues++;
				}

			}
			else if( pTbl->wBitFlag & FSD_STRING )
			{
				char sString[FSD_MAXSTRING],
					 *pc=sBuf;

				while( ParseString(pc, sString, FSD_MAXSTRING) )
				{
					pTbl->pValues = (char *)realloc(pTbl->pValues, (pTbl->nValues+1)*pTbl->nElementSize);

					FNX_STRCPY( (((char *)pTbl->pValues) + (pTbl->nValues*pTbl->nElementSize)), sString);
					pTbl->nValues++;
				}
			}
			else if( pTbl->wBitFlag & FSD_ITLIST )
			{

			}
			else if( pTbl->wBitFlag & FSD_ITRULE )
			{

			}
			else
			{
				nValues = ReadValuesFromBuf(sBuf, pValues, pTbl->nElementSize, 
						MAX_VALUES/pTbl->nElementSize, pTbl->bSigned);

				if( nValues > 0 )
				{
					pTbl->pValues = (void *)realloc(pTbl->pValues, (pTbl->nValues+nValues)*pTbl->nElementSize);
					switch(pTbl->nElementSize)
					{
						case 1:
							for(i=pTbl->nValues, j=0; j < nValues; i++, j++)
							{
								if( pTbl->bSigned )
									((char *)pTbl->pValues)[i] = ((char *)pValues)[j];
								else
									((unsigned char *)pTbl->pValues)[i] = ((unsigned char *)pValues)[j];
							}
							break;
						case 2:
							for(i=pTbl->nValues, j=0; j < nValues; i++, j++)
							{
								if( pTbl->bSigned )
									((short *)pTbl->pValues)[i] = ((short *)pValues)[j];
								else
									((unsigned short *)pTbl->pValues)[i] = ((unsigned short *)pValues)[j];
							}
							break;
						case 4:
							for(i=pTbl->nValues, j=0; j < nValues; i++, j++)
							{
								if( pTbl->bSigned )
									((int *)pTbl->pValues)[i] = ((int *)pValues)[j];
								else
									((unsigned int *)pTbl->pValues)[i] = ((unsigned int *)pValues)[j];

							}
							break;

					}
					pTbl->nValues += nValues;
				}

			}	// if !bGTrieNode

		}	// if bReading
	}

	FNX_FCLOSE(fp);

	return pTableHead;
}

/*FUNCTION_HEADER**********************
 * NAME:	;WriteCompositeTable
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void WriteCompositeTable(char *sOutFile, char *sListName, TABLE_DATA *pTable, bool bBigEndian)
{
	char		sHeader[_MAX_PATH],
				sSrc[_MAX_PATH],
				*pc;
	char		Byte1;
	short		Byte2;
	int			Byte4;
	unsigned char
				uByte1;
	unsigned short
				uByte2;
	unsigned int
				i,
				uByte4,
				offset,
				uiDataOffset;
	void		*pValue;
	FILE		*fp,
				*fpHeader,
				*fpSrc;
	TABLE_DATA	*pTbl;

	if( sOutFile == NULL || pTable == NULL )
		return;

	if( (fp = FNX_FOPEN(sOutFile, "wb")) == NULL )
	{
		FNX_PRINTF("Error: Can't open file %s\n", sOutFile);
		return;
	}

	// Create the filename for the header file where the offsets will be stored
	if( (pc = FNX_STRRCHR(sOutFile, '\\')) != NULL )
	{
		char c = *pc;
		*pc = 0x00;
		FNX_SPRINTF(sHeader, "%s\\%sFileSystemTable.h", sOutFile, sListName);
		FNX_SPRINTF(sSrc, "%s\\%sFileSystemTable.c", sOutFile, sListName);
		*pc = c;
	}
	else
	{
		FNX_SPRINTF(sHeader, "%sFileSystemTable.h", sListName);
		FNX_SPRINTF(sSrc, "%sFileSystemTable.c", sListName);
	}
	if( (fpHeader = FNX_FOPEN(sHeader, "wt")) == NULL )
	{
		FNX_FCLOSE(fp);
		FNX_PRINTF("Error: Couldn't open header file %s\n", sHeader);
		return;
	}

	// Write out the file header
	FNX_FPRINTF(fpHeader, 
		"/*H_HEADER_FILE***************************************************************\n"
		"FILE			: %sFileSystemTable.h\n"
		"DESC			: \n"
		"TABS			: 4\n"
		"OWNER			: Fonix\n"
		"DATE CREATED	: \n\n"
		"(C) Copyright 2005 All rights reserved.\n"
		"This is an unpublished work, and is confidential and proprietary: \n"
		"technology and information of fonix corporation.  No part of this\n"
		"code may be reproduced, used or disclosed without written consent of\n" 
		"fonix corporation in each and every instance.\n"
		"*END_HEADER******************************************************************/\n"
		"#ifndef	%sFILESYSTEMDATA_H\n"
		"#define	%sFILESYSTEMDATA_H\n\n", 
		sListName,
		sListName,
		sListName);

	// Write the Table enums used to access the array of offsets
	FNX_FPRINTF(fpHeader, "\t// The following enum provides a method for accessing the data array.\n");
	FNX_FPRINTF(fpHeader, "\ttypedef enum {\n");
	for(pTbl=pTable; pTbl; pTbl=pTbl->pNext)
	{
		if( pTbl == pTable )
			FNX_FPRINTF(fpHeader, "\t\t%s = 0,\n", pTbl->sTableName);	// Write out table name enums (1st)
		else
			FNX_FPRINTF(fpHeader, "\t\t%s,\n", pTbl->sTableName);		// (all others)
	}
	FNX_FPRINTF(fpHeader, "\t\t%s_NUM_TABLES\n\t}%s_FS_TABLES;\n", 
		sListName, sListName);
	FNX_FPRINTF(fpHeader, "\n#endif\n");
	FNX_FCLOSE(fpHeader);


	// Write out the offsets array
	if( (fpSrc = FNX_FOPEN(sSrc, "wt")) == NULL )
	{
		FNX_FCLOSE(fp);
		FNX_PRINTF("Error: Couldn't open source file %s\n", sSrc);
		return;
	}

	FNX_FPRINTF(fpSrc, 
		"/*C_HEADER_FILE****************************************************************\n"
		"FILE			:	%sFileSystemTable.c\n"
		"DESC			:	This file includes an array of offsets to the German File System dictionary.\n"
		"					See %sFileSystemDataTable.h for the table name enumeration.\n"
		"TABS			:	4\n"
		"OWNER			:	Fonix\n"
		"DATE CREATED	:	\n\n"
		"(C) Copyright 2005 All rights reserved.\n"
		"This is an unpublished work, and is confidential and proprietary: \n"
		"technology and information of fonix corporation.  No part of this\n"
		"code may be reproduced, used or disclosed without written consent of\n" 
		"fonix corporation in each and every instance.\n\n"
		"*END_HEADER*******************************************************************/\n"
		"#include \"%sFileSystemTable.h\"\n\n",
		sListName, 
		sListName, 
		sListName);

	FNX_FPRINTF(fpSrc, "\n\n//  This is an array of offsets into the File System tables.\n");
	FNX_FPRINTF(fpSrc, "const unsigned int ui%sTableOffsets[] = {\n", sListName);

	offset = 0;
	for(pTbl=pTable; pTbl; pTbl=pTbl->pNext)
	{
		pTbl->offset = offset;										// Store for later testing
		if( pTbl->pNext == NULL )
			FNX_FPRINTF(fpSrc, "\t%d\n};\n", offset);					// Write offsets to header file
		else
			FNX_FPRINTF(fpSrc, "\t%d,\n", offset);


		// Write the number of values in this table
		uByte4 = pTbl->nValues;
		if( bBigEndian )
			uByte4 = ByteSwap32(uByte4);
		FNX_FWRITE(&uByte4, sizeof(unsigned int), 1, fp);				// Write number of values in table

		// Write bit flag with nBytes and Signed bits set
		uByte2 = pTbl->wBitFlag;
		if( bBigEndian )
			uByte2 = ByteSwap16(uByte2);
		FNX_FWRITE(&uByte2, sizeof(short), 1, fp);

		// Write the values
		for(i=0; i<pTbl->nValues; i++)
		{
			switch(pTbl->nElementSize)
			{
				case 1:	
					if( pTbl->bSigned )
					{
						Byte1 = ((char *)pTbl->pValues)[i];
						pValue = &Byte1;
					}
					else
					{
						uByte1 = ((unsigned char *)pTbl->pValues)[i];
						pValue = &uByte1;
					}
					FNX_FWRITE(pValue, pTbl->nElementSize, 1, fp);
					break;

				case 2:
					if( pTbl->bSigned )
					{
						Byte2 = ((short *)pTbl->pValues)[i];
						if( bBigEndian )
							Byte2 = ByteSwap16(Byte2);
						pValue = &Byte2;
					}
					else
					{
						uByte2 = ((unsigned short *)pTbl->pValues)[i];
						if( bBigEndian ) 
							uByte2 = ByteSwap16(uByte2);
						pValue = &uByte2;
					}
					FNX_FWRITE(pValue, pTbl->nElementSize, 1, fp);
					break;
				
				case 4:
					if( pTbl->bSigned )
					{
						Byte4 = ((int *)pTbl->pValues)[i];
						if( bBigEndian ) 
							Byte4 = ByteSwap32(Byte4);
						pValue = &Byte4;
					}
					else
					{
						uByte4 = ((unsigned int *)pTbl->pValues)[i];
						if( bBigEndian ) 
							uByte4 = ByteSwap32(uByte4);
						pValue = &uByte4;
					}
					FNX_FWRITE(pValue, pTbl->nElementSize, 1, fp);
					break;

				default:
					if( pTbl->wBitFlag & FSD_GTRIE )
					{
						if( i == 0 )
						{
							// structure size on disk = sizeof(uiDataOffset) + sizeof(U16)*8 values + sizeof(typeinfo)
							unsigned int uiSzOnDisk = sizeof(int) + sizeof(U16)*8 + sizeof(char);
							// Beginning of string data
							uiDataOffset = offset + sizeof(int) + sizeof(char) + pTbl->nValues*uiSzOnDisk;
						}
						WriteGTrieNode(fp, &((GTRIENODE *)pTbl->pValues)[i], &uiDataOffset, bBigEndian);
					}
					else if( pTbl->wBitFlag & FSD_STRING )
					{

					}
					break;

			}	// switch


		}	// for all values in table

		// Get the offset to the next table
		offset = FNX_FTELL(fp);

	}	// for all tables

	FNX_FCLOSE(fp);
	FNX_FCLOSE(fpSrc);

}	// WriteCompositeTable


/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void TestGTrieTable(char *sFile)
{
	int		Value;
	char	sBuf[128];
	unsigned int
			uiIndex;
	FILE	*fp;
	GTRIENODE GTrieNode;

	if( (fp = FNX_FOPEN(sFile, "rb")) == NULL )
		return;

	FNX_PRINTF("\nEnter an index value: ");
	while( gets(sBuf) )		// Test the newly built LTree
	{
		if( !sBuf[0] )		// get out if nothing was entered
			break;
		uiIndex = atoi(sBuf);
		Value = 0;
		if( GetGTrieNode(fp, &GTrieNode, uiIndex, 0) == 1 )
		{
			FNX_PRINTF("Found GTrieNode: Name %s, alt %d, what %d, right %d, index %d, typeinfo %d\n",
				GTrieNode.sName[0]==0x00 ? "none" : GTrieNode.sName,
				GTrieNode.alt,
				GTrieNode.what,
				GTrieNode.right,
				GTrieNode.index,
				(int)GTrieNode.typeinfo);
		}
		else
		{
			FNX_PRINTF("Error: reading value\n");
		}

		FNX_PRINTF("Enter index: ");
	}


}


/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
bool FindTableOffset(char *sTable, TABLE_DATA *pTable, unsigned int *puiTableOffset)
{
	TABLE_DATA *pTbl;

	for(pTbl=pTable; pTbl; pTbl=pTbl->pNext)
	{
		if( FNX_STRICMP(sTable, pTbl->sTableName) == 0 )
		{
			*puiTableOffset = pTbl->offset;
			return 1;
		}
	}

	return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;TestCompositeTable
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void TestCompositeTable(char *sFile, TABLE_DATA *pTable)
{
	char	sTable[_MAX_PATH];
	int		nSize,
			Value,
			bSigned;
	char	sBuf[128];
	unsigned int
			uiTableOffset,
			uiIndex;
	FILE	*fp;

	if( (fp = FNX_FOPEN(sFile, "rb")) == NULL )
		return;

	FNX_PRINTF("\nEnter the name of a table to test: ");
	while( gets(sTable) )
	{
		if( !sTable[0] )
			break;

		if( FindTableOffset(sTable, pTable, &uiTableOffset) == 0 )
		{
			FNX_PRINTF("Warning: Unknown table %s\n", sTable);
			continue;
		}

		nSize = GetBytesPerValue(fp, &bSigned, uiTableOffset);

		FNX_PRINTF("\nEnter an index value: ");
		while( gets(sBuf) )		// Test the newly built LTree
		{
			if( !sBuf[0] )		// get out if nothing was entered
				break;
			uiIndex = atoi(sBuf);
			Value = 0;
			if( GetTableValue(fp, &Value, uiIndex, uiTableOffset) == 1 )
			{
				FNX_PRINTF("Value: %d (Hex: %x)\n", 
					bSigned?Value:(unsigned int)Value, 
					bSigned?Value:(unsigned int)Value);
			}
			else
			{
				FNX_PRINTF("Error: reading value\n");
			}

			FNX_PRINTF("Enter index: ");
		}

		FNX_PRINTF("\nEnter the name of a table to test: ");

	}

}


/*FUNCTION_HEADER**********************
 * NAME:	;BuildCompositeTable
 * DESC: 	
 * IN:		sFileList - file containing a list of filenames
			sOutFile - filename for the output file
			bTest - flag to test dictionaries along the way
			bBigEndian - flag to write out all multi-byte items in big-endian format
 * OUT:		
 * RETURN:	1 on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int BuildCompositeTable(char *sFileList, char *sOutFile, bool bTest, bool bBigEndian)
{
	char sInFile[_MAX_PATH],
		 sListName[_MAX_PATH],
		 *pc;
	int	 nTables=0;
	FILE *fp;
	TABLE_DATA *pTable;
	
	if( (fp = FNX_FOPEN(sFileList, "rt")) == NULL )
	{
		FNX_PRINTF("Error: Can't open file %s\n", sFileList);
		return 0;
	}

	// Create a list name that will be used in creating the output files
	if( (pc = FNX_STRRCHR(sFileList, '\\')) != NULL )
	{
		pc++;
		FNX_STRCPY(sListName, pc);
	}
	else
	{
		FNX_STRCPY(sListName, sFileList);
	}
	if( (pc = FNX_STRRCHR(sListName, '.')) != NULL )
		*pc = 0x00;

	while( FNX_FGETS(sInFile, _MAX_PATH, fp) )					// Iterate through all files in the list
	{
		if( *sInFile == 0x00 || *sInFile == ';' )			// Make sure we have a filename
			continue;

		if( (pc = FNX_STRCHR(sInFile, '\n')) != NULL )			// Strip any \n ending characters
			*pc = 0x00;

		FNX_PRINTF("Loading %s\n", sInFile);
		if( (pTable = ReadTablesInFile(sInFile)) != NULL )
		{
			WriteCompositeTable(sOutFile, sListName, pTable, bBigEndian);

			if( bTest )
			{
				if( pTable->bGTrieNode )
					TestGTrieTable(sOutFile);
				else
					TestCompositeTable(sOutFile, pTable);
			}
		}

	}	// while more files in the list


	FNX_FCLOSE(fp);

	return 1;
}


/*FUNCTION_HEADER**********************
 * NAME:	;main
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int main(int argc, char* argv[])
{
	char *sInFile=NULL,
		 *sOutFile=NULL;
	bool bTest=0,
		 bItalianRules=0;
	bool bBigEndian=0;
	int	 i;

	// Parse the command line arguments to get the input and output filenames
	for( i=1; i<argc; i++)
	{
		if( argv[i][0] == '-' )
		{
			switch( argv[i][1] )
			{
				case 'B':
				case 'b':
					bBigEndian = 1;
					break;

				case 'i':	
					sInFile = argv[++i];		// Get the input (raw text dictionary) filename
					break;

				case 'I':
					bItalianRules = 1;
					break;

				case 'O':
				case 'o':	
					sOutFile = argv[++i];		// Get the output (file system letter tree) filename
					break;

				case 'T':
				case 't':
					bTest = 1;
					break;

			}
		}
	}

	if( sInFile == NULL || sOutFile == NULL )
	{
		FNX_PRINTF("Usage: %s -i <infile> -o <outfile> [-T] [-B]\n", argv[0]);
		FNX_PRINTF("\t<infile> - input file\n");
		FNX_PRINTF("\t<output> - output file system file\n");
		FNX_PRINTF("\t-T - test\n");
		FNX_PRINTF("\t-B - output in big-endian format\n");
		exit(0);
	}

	// Read the raw text dictionary file
	FNX_PRINTF("Reading: %s ...\n", sInFile);
	BuildCompositeTable(sInFile, sOutFile, bTest, bBigEndian);

	return 1;
}