/*C_HEADER_FILE****************************************************************
FILE			:	FileSystemDataHandler.c
DESC			:	Functions to handle file system data.  Originally built for Casio
					dictionary products
TABS			:	3
OWNER			:	Fonix
DATE CREATED	:	8 Nov 2005

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
//#ifndef _BIGENDIAN_ //moved to port.h mlt 02/09/06
//#include <stdio.h> //moved to port.h mlt 02/09/06
//#endif //moved to port.h mlt 02/09/06
//#include <string.h> //moved to port.h mlt 02/09/06
#include "port.h"
#include "FileSystemData.h"

/*FUNCTION_HEADER**********************
 * NAME:	;GetBytesPerValue
 * DESC: 	Get some information about a specific table
 * IN:		fp - file pointer to the tables file
			iTblOffset - offset to the specific table we are interested in
 * OUT:		pbSigned - 1 if data is signed, 0 if not
 * RETURN:	Number of bytes per value (1,2 or 4) on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int GetBytesPerValue(FILE *fp, int *pbSigned, unsigned int iTblOffset)
{
	char	cBitFlag;
	unsigned int
			nMax = 0;

	if( fp == NULL )
		return 0;

	if( FNX_FSEEK(fp, iTblOffset, SEEK_SET) != 0 )				// Seek to the beginning of the table
		return 0;

	if( FNX_FREAD(&nMax, sizeof(int), 1, fp) != 1 )				// Read the number of values in table
		return 0;

	if( FNX_FREAD(&cBitFlag, sizeof(char), 1, fp) == 1 )		// Read the bit flag
	{
		if( pbSigned && cBitFlag & FSD_SIGNED )				// Is signed?
			*pbSigned = 1;

		if( cBitFlag & FSD_BYTES1 )							// 1 Byte per value?
			return 1;
		else if( cBitFlag & FSD_BYTES2 )					// 2 bytes per value?
			return 2;
		else if( cBitFlag & FSD_BYTES4 )					// 4 bytes per value?
			return 4;
		else
			return 0;
	}
	else
		return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int GetTableHeaderInfo(FILE *fp, unsigned int *pnMax, short *pwBitFlag, unsigned int *pnSize, 
					   int *pbSigned, unsigned int iTblOffset)
{
	short	wBitFlag = 0;
	int		bSigned = 0;
	unsigned int 
			nMax = 0,
			nSize = 0;

	if( fp == NULL )
		return 0;

	if( FNX_FSEEK(fp, iTblOffset, SEEK_SET) != 0 )			// Seek to start of table
		return 0;

	if( FNX_FREAD(&nMax, sizeof(int), 1, fp) != 1 )			// Read the number of values in table
		return 0;
	else if( pnMax )
		*pnMax = nMax;

	if( FNX_FREAD(&wBitFlag, sizeof(short), 1, fp) != 1 )	// Read the bit flag
		return 0;
	else if( pwBitFlag )
		*pwBitFlag = wBitFlag;

	if( wBitFlag & FSD_BYTES1 )							// Find out how many bytes per value in this table
		nSize = 1;
	else if( wBitFlag & FSD_BYTES2 )
		nSize = 2;
	else if( wBitFlag & FSD_BYTES4 )
		nSize = 4;
	else 
		return 0;

	if( pnSize )
		*pnSize = nSize;

	if( pbSigned )
	{
		if( wBitFlag & FSD_SIGNED )							// Find out if the values are signed or unsigned
			*pbSigned = 1;
		else
			*pbSigned = 0;
	}

	return 1;

}

/*FUNCTION_HEADER**********************
 * NAME:	;GetTableValue
 * DESC: 	Get a value from an array stored on the file system
 * IN:		fp - file pointer to the data 
			index - index used as if it were an array in memory
			iTblOffset - offset to the table of interest
 * OUT:		pValue - value at index location
 * RETURN:	nSize on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int GetTableValue(FILE *fp, void *pValue, unsigned int index, unsigned int iTblOffset)
{
	short	wBitFlag = 0;
	int		bSigned = 0;
	unsigned char
			cValue;
	unsigned short
			wValue = 0;
	unsigned int 
			iValue = 0,
			nMax=0,
			nSize=0,
			offset = 0;

	if( fp == NULL || pValue == NULL )
		return 0;

	if( FNX_FSEEK(fp, iTblOffset, SEEK_SET) != 0 )			// Seek to start of table
		return 0;

	if( FNX_FREAD(&nMax, sizeof(int), 1, fp) != 1 )			// Read the number of values in table
		return 0;

	if( index >= nMax )									// Make sure we have a valid index
		return 0;

	if( FNX_FREAD(&wBitFlag, sizeof(short), 1, fp) != 1 )	// Read the bit flag
		return 0;

	if( wBitFlag & FSD_BYTES1 )							// Find out how many bytes per value in this table
		nSize = 1;
	else if( wBitFlag & FSD_BYTES2 )
		nSize = 2;
	else if( wBitFlag & FSD_BYTES4 )
		nSize = 4;
	else 
		return 0;

	if( wBitFlag & FSD_SIGNED )							// Find out if the values are signed or unsigned
		bSigned = 1;
	else
		bSigned = 0;

	// Calculate the offset to the value we want to read
	offset = iTblOffset + sizeof(int) + sizeof(short) + (index * nSize);

	if( FNX_FSEEK(fp, offset, SEEK_SET) != 0 )				// Seek to the value
		return 0;

	switch(nSize)
	{
		case 1:	
			if( FNX_FREAD(&cValue, nSize, 1, fp) != 1 )				// Read the value
				return 0;
			if( bSigned )
				*((char *)pValue) = (char)cValue;
			else
				*((unsigned char *)pValue) = (unsigned char)cValue;
			break;
		case 2:	
			if( FNX_FREAD(&wValue, nSize, 1, fp) != 1 )				// Read the value
				return 0;
			if( bSigned )
				*((short *)pValue) = (short)wValue;
			else
				*((unsigned short *)pValue) = (unsigned short)wValue;
			break;
		case 4:	
			if( FNX_FREAD(&iValue, nSize, 1, fp) != 1 )				// Read the value
				return 0;

			if( bSigned )
				*((int *)pValue) = (int)iValue;
			else
				*((unsigned int *)pValue) = (unsigned int)iValue;
			break;
	}

	return nSize;
}

/*FUNCTION_HEADER**********************
 * NAME:	;GetTableUChar
 * DESC: 	Get a value from an array stored on the file system
 * IN:		fp - file pointer to the data 
			index - index used as if it were an array in memory
			iTblOffset - offset to the table of interest
 * OUT:		pValue - value at index location
 * RETURN:	nSize on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int GetTableUChar(FILE *fp, unsigned char *pValue, unsigned int index, unsigned int iTblOffset)
{
	short	wBitFlag = 0;
	int		bSigned = 0;
	unsigned char
			wValue;
	unsigned int 
			nMax=0,
			nSize=0,
			offset=0;

	if( fp == NULL || pValue == NULL )
		return 0;

	if( GetTableHeaderInfo(fp, &nMax, &wBitFlag, &nSize, &bSigned, iTblOffset) == 0 )
		return 0;

	if( index >= nMax ||		// Make sure we have a valid index
		nSize != 1 ||			// Make sure we are reading shorts
		bSigned != 0 )			// Make sure we are unsigned
		return 0;

	// Calculate the offset to the value we want to read
	offset = iTblOffset + sizeof(int) + sizeof(short) + (index * nSize);

	if( FNX_FSEEK(fp, offset, SEEK_SET) != 0 )				// Seek to the value
		return 0;

	if( FNX_FREAD(&wValue, nSize, 1, fp) != 1 )				// Read the value
		return 0;

	*pValue = wValue;

	return nSize;
}

/*FUNCTION_HEADER**********************
 * NAME:	;GetTableChar
 * DESC: 	Get a value from an array stored on the file system
 * IN:		fp - file pointer to the data 
			index - index used as if it were an array in memory
			iTblOffset - offset to the table of interest
 * OUT:		pValue - value at index location
 * RETURN:	nSize on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int GetTableChar(FILE *fp, char *pValue, unsigned int index, unsigned int iTblOffset)
{
	short	wBitFlag =0;
	int		bSigned=0;
	char	wValue;
	unsigned int 
			nMax=0,
			nSize=0,
			offset=0;

	if( fp == NULL || pValue == NULL )
		return 0;

	if( GetTableHeaderInfo(fp, &nMax, &wBitFlag, &nSize, &bSigned, iTblOffset) == 0 )
		return 0;

	if( index >= nMax ||		// Make sure we have a valid index
		nSize != 1 ||			// Make sure we are reading char
		bSigned != 1 )			// Make sure we are signed
		return 0;

	// Calculate the offset to the value we want to read
	offset = iTblOffset + sizeof(int) + sizeof(short) + (index * nSize);

	if( FNX_FSEEK(fp, offset, SEEK_SET) != 0 )				// Seek to the value
		return 0;

	if( FNX_FREAD(&wValue, nSize, 1, fp) != 1 )				// Read the value
		return 0;

	*pValue = wValue;

	return nSize;
}


/*FUNCTION_HEADER**********************
 * NAME:	;GetTableUShort
 * DESC: 	Get a value from an array stored on the file system
 * IN:		fp - file pointer to the data 
			index - index used as if it were an array in memory
			iTblOffset - offset to the table of interest
 * OUT:		pValue - value at index location
 * RETURN:	nSize on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int GetTableUShort(FILE *fp, unsigned short *pValue, unsigned int index, unsigned int iTblOffset)
{
	short	wBitFlag=0;
	int		bSigned=0;
	unsigned short
			wValue=0;
	unsigned int 
			nMax=0,
			nSize=0,
			offset=0;

	if( fp == NULL || pValue == NULL )
		return 0;

	if( GetTableHeaderInfo(fp, &nMax, &wBitFlag, &nSize, &bSigned, iTblOffset) == 0 )
		return 0;

	if( index >= nMax ||		// Make sure we have a valid index
		nSize != 2 ||			// Make sure we are reading shorts
		bSigned != 0 )			// Make sure we are unsigned
		return 0;

	// Calculate the offset to the value we want to read
	offset = iTblOffset + sizeof(int) + sizeof(short) + (index * nSize);

	if( FNX_FSEEK(fp, offset, SEEK_SET) != 0 )				// Seek to the value
		return 0;

	if( FNX_FREAD(&wValue, nSize, 1, fp) != 1 )				// Read the value
		return 0;

	*pValue = wValue;

	return nSize;
}

/*FUNCTION_HEADER**********************
 * NAME:	;GetTableShort
 * DESC: 	Get a value from an array stored on the file system
 * IN:		fp - file pointer to the data 
			index - index used as if it were an array in memory
			iTblOffset - offset to the table of interest
 * OUT:		pValue - value at index location
 * RETURN:	nSize on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int GetTableShort(FILE *fp, short *pValue, unsigned int index, unsigned int iTblOffset)
{
	short	wBitFlag=0;
	int		bSigned=0;
	short	wValue=0;
	unsigned int 
			nMax=0,
			nSize=0,
			offset=0;

	if( fp == NULL || pValue == NULL )
		return 0;

	if( GetTableHeaderInfo(fp, &nMax, &wBitFlag, &nSize, &bSigned, iTblOffset) == 0 )
		return 0;

	if( index >= nMax ||		// Make sure we have a valid index
		nSize != 2 ||			// Make sure we are reading shorts
		bSigned != 1 )			// Make sure we are unsigned
		return 0;

	// Calculate the offset to the value we want to read
	offset = iTblOffset + sizeof(int) + sizeof(short) + (index * nSize);

	if( FNX_FSEEK(fp, offset, SEEK_SET) != 0 )				// Seek to the value
		return 0;

	if( FNX_FREAD(&wValue, nSize, 1, fp) != 1 )				// Read the value
		return 0;

	*pValue = wValue;

	return nSize;
}


/*FUNCTION_HEADER**********************
 * NAME:	;GetGTrieNode
 * DESC: 	
 * IN:		fp - file pointer to the data 
			index - index used as if it were an array in memory
			iTblOffset - offset to the table of interest
 * OUT:		pValue - value at index location
 * RETURN:	1 on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int GetGTrieNode(FILE *fp, GTRIENODE *pGTrieNode, unsigned int index, unsigned int iTblOffset)
{
	char	cBitFlag=0,
			cType=0;
	unsigned int 
			nMax=0,
			offset=0,
			iDataOffset=0,
			uiSzOnDisk=0;


	if( fp == NULL || pGTrieNode == NULL )
		return 0;

	if( FNX_FSEEK(fp, iTblOffset, SEEK_SET) != 0 )			// Seek to start of table
		return 0;

	if( FNX_FREAD(&nMax, sizeof(int), 1, fp) != 1 )			// Read the number of values in table
		return 0;

	if( index >= nMax )									// Make sure we have a valid index
		return 0;

	if( FNX_FREAD(&cBitFlag, sizeof(char), 1, fp) != 1 )	// Read the bit flag
		return 0;

	if( !(cBitFlag & FSD_GTRIE) )
		return 0;

	// Calculate the offset to the value we want to read
	uiSzOnDisk = sizeof(int) + sizeof(char) + sizeof(short)*8;
	offset = iTblOffset + sizeof(int) + sizeof(char) + (index * uiSzOnDisk);

	if( FNX_FSEEK(fp, offset, SEEK_SET) != 0 )				// Seek to the value
		return 0;

	if( FNX_FREAD(&iDataOffset, sizeof(int), 1, fp) != 1 )
		return 0;
	if( FNX_FREAD(&pGTrieNode->alt, sizeof(short), 1, fp) != 1 )
		return 0;
	if( FNX_FREAD(&pGTrieNode->what, sizeof(short), 1, fp) != 1 )
		return 0;
	if( FNX_FREAD(&pGTrieNode->right, sizeof(short), 1, fp) != 1 )
		return 0;
	if( FNX_FREAD(&pGTrieNode->index, sizeof(short), 1, fp) != 1 )
		return 0;
	
	if( FNX_FREAD(&cType, sizeof(char), 1, fp) != 1 )
		return 0;
	pGTrieNode->typeinfo = cType;
	
	if( FNX_FREAD(&pGTrieNode->info.status, sizeof(short), 1, fp) != 1 )
		return 0;
	
	if( FNX_FREAD(&pGTrieNode->info.counter, sizeof(short), 1, fp) != 1 )
		return 0;
	
	if( FNX_FREAD(&pGTrieNode->info.counterB, sizeof(short), 1, fp) != 1 )
		return 0;
	
	if( FNX_FREAD(&pGTrieNode->info.parameter, sizeof(short), 1, fp) != 1 )
		return 0;

	if( iDataOffset > 0 )
	{
		char *pc=&pGTrieNode->sName[0];
		FNX_FSEEK(fp, iDataOffset, SEEK_SET);
		do{
			if( FNX_FREAD(&cType, sizeof(char), 1, fp) != 1 )
				break;
			*pc = cType;
			pc++;
		}while( cType!= 0x00);
	}
	else
	{
		pGTrieNode->sName[0] = 0x00;
	}

	return 1;
}