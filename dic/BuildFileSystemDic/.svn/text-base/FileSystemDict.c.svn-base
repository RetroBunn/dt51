/*C_HEADER_FILE****************************************************************
FILE			:	FileSystemDict.c
DESC			:	Functions to handle letter tree pronunciation lookups from a
					file based system.
TABS			:	3
OWNER			:	Fonix
DATE CREATED	:	18 Oct 2005

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
#include <string.h>
#include "FileSystemDict.h"
#ifdef _BIGENDIAN_
#define fread fnxfread
#define fseek fnxfseek
#endif

/******************************************************************************  
	A letter tree is stored as a bunch of BRANCH structures with the
	pronunciations at the end of the letter tree file.

	Each branch is stored in the following format:
	<N symbols><Symbols><Branch offset 1><Data offset 1>....<Branch offset N><Data offset N>

	where: 

	<N Symbols> - The number of symbols used in this branch (unsigned char).
	<Symbols> - All of the symbols used in this branch.  No more than 255 allowed
	<Branch offset 1> - file offset to the branch for symbol 1 (or 0 if refering to the index)
	<Data offset 1> - file offset to the pronunciation data for the word that ends at symbol 1 of this branch.

	The pronunciations are stored as:

	<size of Data><Data>

	Currently <Data> has the format
	<pronunciation>,<hex bit flag>
	or
	<pronunciation>,<hex bit flag>,<pronunciation>,<hex bit flag>
	if there is a homograph

	Example: xb'Ys,0x80000400,xb'Yz,0x82020000
*******************************************************************************/


/*FUNCTION_HEADER**********************
 * NAME:	;GetSymbolIndex
 * DESC: 	Find the index of a symbol in a string
 * IN:		sSymbols - the symbol string
			nSym - the number of symbols in sSymbols
			cSym - the symbol to find
 * OUT:		none
 * RETURN:	symbol index on success, -1 on failure
 * NOTES:	
 *END_HEADER***************************/
static int GetSymbolIndex(char *sSymbols, int nSym, char cSym)
{
	int i=0;

	for(i=0; i<nSym; i++)
	{
		if( sSymbols[i] == cSym )
			return i;
	}

	return -1;
}

/*FUNCTION_HEADER**********************
 * NAME:	;FindWordInFileSystemDict
 * DESC: 	Find a word in a file system based dictionary
 * IN:		sWord - the word to find
			fp - file pointer to dictionary
			offset - offset into multi-dictionary.  This value should be 0
				for most dictionaries and an offset value for German and Italian
				multi-dictionaries.
 * OUT:		sPron - Pronunciation for sWord
			piBitFlag - Bit Flag for word
			sHomo _ Pronunciation for secondary Homograph of word
			piHomoFlag - Bit Flag for secondary Homograph
 * RETURN:	1 on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int FindWordInFileSystemDict(char *sWord, char *sPron, int *piBitFlag, 
#ifdef _BIGENDIAN_
							 char *sHomo, int *piHomoFlag, void *fp, 
#else
							 char *sHomo, int *piHomoFlag, FILE *fp, 
#endif
							 unsigned int offset)
						 
{
	char	*pc =NULL,					// Current character in sWord
			sSymbols[MAX_SYMBOLS]="";	// Symbol set per branch
	unsigned char cnSym;			// number of symbols
	unsigned int  
			uiBitFlag=0;				// Bit Flag for word pronunciation
	int		i=0,
			iSym=0;					// symbol array index
	FILESYS_SYMBOL
			tSym[MAX_SYMBOLS];		// branch and data offset values

	if( sWord == NULL || sPron == NULL || fp == NULL )
		return 0;

	memset(sSymbols, 0, MAX_SYMBOLS*sizeof(char));
	memset(tSym, 0, MAX_SYMBOLS*sizeof(FILESYS_SYMBOL));
	
	fseek(fp, offset, SEEK_SET);
	if( fread(&cnSym, sizeof(char), 1, fp) != 1 )			// Read the number of symbols used in this branch
		return 0;
	if( fread(sSymbols, sizeof(char), cnSym, fp) != (unsigned int)cnSym )
		return 0;
	if( fread(tSym, sizeof(FILESYS_SYMBOL), cnSym, fp) != (unsigned int)cnSym )
		return 0;

	for( pc=sWord; *pc; pc++ )
	{
		if( (iSym = GetSymbolIndex(sSymbols, cnSym, *pc)) >= 0)	// Calc the word symbol index
		{
			if( *(pc+1) == 0x00 )						// end of word
			{
				if( tSym[iSym].iData == 1 )				// have end-of-word marker only
					return 1;							// return 1 to show that word was found
				else if( tSym[iSym].iData == 0 )		// end-of-word reached but no marker found
					return 0;							// return 0 to show that word was NOT found

				// End-of-Word reached and iData > 1 so there must be pronunciation data
				fseek(fp, tSym[iSym].iData+offset, SEEK_SET);	// get the data
				fread(&uiBitFlag, sizeof(int), 1, fp);
				if( piBitFlag )
					*piBitFlag = uiBitFlag;
				for(i=0; i<MAX_SYMBOLS; i++)
				{
					fread(&sPron[i], sizeof(char), 1, fp);
					if( sPron[i] == 0x00 )
						break;
				}

				if( (uiBitFlag & FC_M_HOMOGRAPH) && sHomo)
				{
					fread(&uiBitFlag, sizeof(int), 1, fp);
					if( piHomoFlag )
						*piHomoFlag = uiBitFlag;
					for(i=0; i<MAX_SYMBOLS; i++)
					{
						fread(&sHomo[i], sizeof(char), 1, fp);
						if( sHomo[i] == 0x00 )
							break;
					}
				}
				return 1;
			}
			else if( tSym[iSym].iNext > 0 )					// get offset to next branch if not end of word
			{
				fseek(fp, tSym[iSym].iNext+offset, SEEK_SET);		// seek to the next branch

				if( fread(&cnSym, sizeof(char), 1, fp) != 1 )	// Read the number of symbols used in this branch
					return 0;
				if( fread(sSymbols, sizeof(char), cnSym, fp) != (unsigned int)cnSym )
					return 0;
				if( fread(tSym, sizeof(FILESYS_SYMBOL), cnSym, fp) != (unsigned int)cnSym )	// Read data for this branch
					return 0;
			}
			else
				return 0;								// Sorry this word is not in the dictionary
		}
		else
			return 0;
	}

	return 0;
}


/*FUNCTION_HEADER**********************
 * NAME:	;FindWordSegsInFileSystemDict
 * DESC: 	Find the pronunciation for a word or word fragment.  Do it all 
			assuming a strictly file based system with limited memory and no
			memory allocations allowed.  Only 1 letter branch needs to be in 
			memory at a time.
 * IN:		sWord - pointer to a word or word fragment (prefix, suffix etc.)
			piLtrsUsed - number of letters in sWord that have already been used.
			iInitOffset - initial offset into the letter tree data so that we can 
				continue looking up other words with the same beginning.
			fp - file pointer to the letter tree data
			iDictOffset - offset into a multi-dictionary.  For most dictionaries this 
				value should be 0, but for German and Italian multi-dictionaries this
				should be the offset to the specific dictionary in a multi-dictionary file.
 * OUT:		sPron - memory to hold pronunciation data
			piBitFlag - bit flag for sPron
			sHomo - optional pronunciation for secondary homograph
			piHomoFlag - bit flag for sHomo
			piLtrsUsed - number of letters used in this search
 * RETURN:	1 on success, 0 on failure
 * NOTES:	sData must be large enough to hold any pronunciation data 

			Based on the following information: 

			NAND flash ROMize: 2MB
			File opening time: 2.5ms
			Number of files that can be opened: 4 files
			Seek time: .02ms/128K Byte
			data reading speed: 2MByte/sec

			For a 25 letter word (long), it would take about 
			(0.02ms * 25 = 0.5ms) + (208 bytes / 2MB/sec = 2.6ms) = 3.1ms

			This doesn't include the seek time into the pronunciation data nor
			the read time for the pronunciation; however, they should be, worst case, 
			less than 0.5ms for a 2MB dictionary

  Example Word: unaussergewoehnlich
  To find the first word:		iOffset = LetterTreePronunciation(sWord, sData, &iLtrsUsed, 0, fp);
  To find a word continuation:	iOffset = LetterTreePronunciation(sWord, sData, &iLtrsUsed, iOffset, fp);
	There are no more word continuations if return value iOffset == 0
  To find the next word fragment: iOffset = LetterTreePronunciation(&sWord[iLtrsUsed], sData, &iLtrsUsed, 0, fp);

 *END_HEADER***************************/
int FindWordSegsInFileSystemDict( char *sWord,
								  char *sPron, int *piPronOffset, int *piBitFlag, 
								  char *sHomo, int *piHomoFlag, 
								  int *piLtrsUsed, unsigned int *puiInitOffset, 
#ifdef _BIGENDIAN_
								  void *fp, unsigned int iDictOffset)
#else
								  FILE *fp, unsigned int iDictOffset)
#endif
{
	char	*pc="",					// Current character in sWord
			sSymbols[MAX_SYMBOLS]="";	// Symbol set per branch
	unsigned char cnSym;			// number of symbols
	unsigned int  uiBitFlag=0;		// Bit flag					// size of data to read
	int ret=0;
	int		i,
			iSym;					// symbol array index
	FILESYS_SYMBOL
			tSym[MAX_SYMBOLS];		// branch and data offset values

	if( sWord == NULL || fp == NULL || puiInitOffset == NULL )
		return 0;

	memset(sSymbols, 0, MAX_SYMBOLS*sizeof(char));
	memset(tSym, 0, MAX_SYMBOLS*sizeof(FILESYS_SYMBOL));

	// Initialize data
	if( *puiInitOffset == 0 )			// reset piLtrsUsed
		*piLtrsUsed = 0;

	fseek(fp, iDictOffset + (*puiInitOffset), SEEK_SET);			// Seek to a branch in the the Letter tree
	if( fread(&cnSym, sizeof(char), 1, fp) != 1 )			// Read the number of symbols used in this branch
		return 0;
	if( fread(sSymbols, sizeof(char), cnSym, fp) != (unsigned int)cnSym )
		return 0;
	if( fread(tSym, sizeof(FILESYS_SYMBOL), cnSym, fp) != (unsigned int)cnSym )
		return 0;

	for( pc=&sWord[*piLtrsUsed]; *pc; pc++)							// Walk through the whole word one letter at a time
	{
		if( (iSym = GetSymbolIndex(sSymbols, cnSym, *pc)) >= 0)		// Calc the word symbol index
		{
			if( tSym[iSym].iData > 0 )								// Check to see if this is the end of a word/word segment
			{
				(*piLtrsUsed)++;								// Keep track of the number of letters used in this word

				if( *(pc+1) != 0x00 )
				{
					*puiInitOffset = tSym[iSym].iNext;			// Get the offset to the next letter branch
				}
				else
				{
					*puiInitOffset = 0;							// Indicate that we are done searching
				}

				if( tSym[iSym].iData == 1 )						// End-of-Word marker only
				{
					return 1;									// Return 1 to indicate end of word was found
				}

				// Seek to the data and pronunciation
				fseek(fp, iDictOffset+tSym[iSym].iData, SEEK_SET);				// get the data

				ret=fread(&uiBitFlag, sizeof(int), 1, fp);
				if (ret!=1)
				{
					uiBitFlag=0;
				}
				if( piBitFlag )
					*piBitFlag = uiBitFlag;

				if( sPron )
				{
					for(i=0; i<MAX_SYMBOLS; i++)
					{
						fread(&sPron[i], sizeof(char), 1, fp);
						if( sPron[i] == 0x00 )
							break;
					}
				}

				if( piPronOffset )
				{
					*piPronOffset = tSym[iSym].iData+iDictOffset;
				}

				if( (uiBitFlag & FC_M_HOMOGRAPH) && sHomo && sPron)
				{
					fread(&uiBitFlag, sizeof(int), 1, fp);
					if( piHomoFlag )
						*piHomoFlag = uiBitFlag;
					for(i=0; i<MAX_SYMBOLS; i++)
					{
						fread(&sHomo[i], sizeof(char), 1, fp);
						if( sHomo[i] == 0x00 )
							break;
					}
				}

				return 1;
			}
			else if( tSym[iSym].iNext > 0 )							// Get the next letter branch
			{
				(*piLtrsUsed)++;
				fseek(fp, iDictOffset+tSym[iSym].iNext, SEEK_SET);	// seek to the next branch

				if( fread(&cnSym, sizeof(char), 1, fp) != 1 )		// Read the number of symbols used in this branch
					return 0;
				if( fread(sSymbols, sizeof(char), cnSym, fp) != (unsigned int)cnSym )
					return 0;
				if( fread(tSym, sizeof(FILESYS_SYMBOL), cnSym, fp) != (unsigned int)cnSym )	// Read data for this branch
					return 0;
			}
			else
			{
				*piLtrsUsed = strlen(sWord);
				return 0;
			}
		}
		else
		{
			*piLtrsUsed = strlen(sWord);
			return 0;
		}
	}

	return 0;	// Didn't find a match
}

/*FUNCTION_HEADER**********************
 * NAME:	;HexStrToul
 * DESC: 	Convert a string like "0x08004001" to the actual value
 * IN:		sHex - hex string
 * OUT:		none
 * RETURN:	value of sHex on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
unsigned int HexStrToul(char *sHex)
{
	char *pc=sHex;
	unsigned int iHex=0;

	if( sHex == NULL )						// idiot check
		return 0;

	if( *pc == '0' && *(pc+1) == 'x' )		// skip the 0x prefix
		pc += 2;

	for( ; *pc && *pc != ','; pc++ )		// for each character in sHex after the prefix
	{
		if( iHex > 0 )						// Shift to the left if we are going to add more into the value
			iHex <<= 4;

		if( '0' <= *pc && *pc <= '9' )		// Add the appropriate amount into the value
		{
			iHex += *pc - '0';
		}
		else if( 'a' <= *pc && *pc <= 'f' )	// Handle lower case hex values
		{
			iHex += (10 + (*pc - 'a'));
		}
		else if( 'A' <= *pc && *pc <= 'F' )	// Handle upper case hex values
		{
			iHex += (10 + (*pc - 'A'));
		}
	}

	return iHex;
}

/*FUNCTION_HEADER**********************
 * NAME:	;GetBitFlag
 * DESC: 	Parse out the bit flag and then return the value of it
 * IN:		sData - pronunciation data include the string representation of the bit flag
 * OUT:		none
 * RETURN:	the bit flag value on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
unsigned int GetBitFlag(char *sData)
{
	char sHex[12]="";
	char *pc=NULL;
	int	 i=0;


	if( (pc = strchr(sData, ',')) == NULL )		// Find the start of the hex string
		return 0;

	pc++;

	if( *pc != '0' || *(pc+1) != 'x' )			// Bail if we don't find the 0x prefix
		return 0;

	for(i=0; i<10; i++)							// copy all 10 characters of 0x12345678
	{
		sHex[i] = *pc;
		pc++;
	}
	sHex[10] = 0x00;							// Null terminate
	
	return HexStrToul(sHex);					// Convert to hex value

}

/*FUNCTION_HEADER**********************
 * NAME:	;ParsePronAndBitFlag
 * DESC: 	Given a pronunciation data field, parse out the pronunciation
			and copy it to sPron.  Then get the bit flag and return it.
 * IN:		sData - pronunciation data 
 * OUT:		sPron - pronunciation part of sData
 * RETURN:	bit flag on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
unsigned int ParsePronAndBitFlag(char *sData, char *sPron)
{
	char *pc="\0";

	if( sData == NULL || sPron == NULL )		// idiot check
		return 0;

	if( (pc = strchr(sData, ',')) == NULL )		// find separator between pronunciation and bit flag
		return 0;

	*pc = 0x00;									// temporarily null terminate the pronunciation 

	strcpy(sPron, sData);						// copy the pronunciation

	*pc = ',';									// put the separator back

	pc++;										// point to the hex string

	return HexStrToul(pc);						// return the hex value

}

/*FUNCTION_HEADER**********************
 * NAME:	;GetHomograph
 * DESC: 	Find out if the primary pronunciation is a homograph.
			If it is then parse out the secondary pronunciation and return it.
 * IN:		sData - pronunciation data
 * OUT:		none
 * RETURN:	secondary pronunciation data on success, NULL on failure 
			or if not a homograph
 * NOTES:	
 *END_HEADER***************************/
char *GetHomograph(char *sData)
{
	char *pc="\0";
	unsigned int iBitFlag=0;

	iBitFlag = GetBitFlag(sData);					// Get the bit flag for the first pronunciation

	if( iBitFlag & FC_M_HOMOGRAPH )					// Is first pronunciation a homograph
	{
		if( (pc = strchr(sData, ',')) != NULL )		// Parse to the second pronunciation
		{
			pc++;
			if( (pc = strchr(pc, ',')) != NULL )
			{
				pc++;
				return pc;							// Return pointer to the second pronunciation
			}
		}
	}
	return NULL;
}

/*FUNCTION_HEADER**********************
 * NAME:	;IsAllUpperCase
 * DESC: 	check to see if a word is all upper case
 * IN:		sWord
 * OUT:		none
 * RETURN:	1 if all upper case, 0 if not
 * NOTES:	
 *END_HEADER***************************/
static int IsAllUpperCase(char *sWord)
{
	char *pc="\0";

	for(pc=sWord; *pc; pc++)
	{
		if( !('A' <= *pc && *pc <= 'Z') )
			return 0;
	}

	return 1;
}

/*FUNCTION_HEADER**********************
 * NAME:	;LowerString
 * DESC: 	Convert a string to all lower case
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void LowerString(char *sWord)
{
	char *pc="\0";

	for(pc=sWord; *pc; pc++)
	{
		if( 'A' <= *pc && *pc <= 'Z' )
			*pc = 'a' + (*pc - 'A');
	}

}

/*FUNCTION_HEADER**********************
 * NAME:	;FindWordWithOffset
 * DESC: 	Try several permutations to find the word before giving up
 * IN:		sWord - word to lookup
 * OUT:		sPron - pronunciation of sWord
			piBitFlag - bit flag for sWord
			sHomo - optional pronunciation of homograph
			piHomoFlag - optional bit flag of homograph
			offset - offset into dictionary (0 for standard dictionaries, offset for multi-dictionaries)
 * RETURN:	pronunciation data on success, NULL on failure
 * NOTES:	
 *END_HEADER***************************/
#ifdef _BIGENDIAN_
int FindWordWithOffset(char *sWord, char *sPron, int *piBitFlag, char *sHomo, int *piHomoFlag, void *fp, unsigned int offset)
#else
int FindWordWithOffset(char *sWord, char *sPron, int *piBitFlag, char *sHomo, int *piHomoFlag, FILE *fp, unsigned int offset)
#endif
{
	char sTmp[MAX_SYMBOLS]="";
	int	 ret=0;

	if( sWord == NULL )
		return 0;

	strcpy(sTmp, sWord);

	// Try the word as it was entered
	if( (ret = FindWordInFileSystemDict(sTmp, sPron, piBitFlag, sHomo, piHomoFlag, fp, offset)) > 0 )
		return ret;

	if( 'a' <= sWord[0] && sWord[0] <= 'z' )
	{
		// Try it with the first letter CAPITALIZED if it's not already
		sTmp[0] = 'A' + (sWord[0] - 'a');
		if( (ret = FindWordInFileSystemDict(sTmp, sPron, piBitFlag, sHomo, piHomoFlag, fp, offset)) > 0 )
			return ret;

		// If entire word is now upper-case try lowering the case (original word was aBCDEF)
		if( IsAllUpperCase(sTmp) )
		{
			// First for the entire word
			LowerString(sTmp);
			if( (ret = FindWordInFileSystemDict(sTmp, sPron, piBitFlag, sHomo, piHomoFlag, fp, offset)) > 0 )
				return ret;

			// Next with just first letter capitalization
			sTmp[0] = 'A' + (sWord[0] - 'a');
			if( (ret = FindWordInFileSystemDict(sTmp, sPron, piBitFlag, sHomo, piHomoFlag, fp, offset)) > 0 )
				return ret;
		}


	}
	else if( 'A' <= sWord[0] && sWord[0] <= 'Z' )
	{
		// Try it with the first letter NOT CAPITALIZED if it is (Abcdef -> abcdef)
		sTmp[0] = 'a' + (sWord[0] - 'A');
		if( (ret = FindWordInFileSystemDict(sTmp, sPron, piBitFlag, sHomo, piHomoFlag, fp, offset)) > 0 )
			return ret;

		// If entire word is in upper-case try lowering the case
		if( IsAllUpperCase(sWord) )
		{
			// First for the entire word
			LowerString(sTmp);
			if( (ret = FindWordInFileSystemDict(sTmp, sPron, piBitFlag, sHomo, piHomoFlag, fp, offset)) > 0 )
				return ret;

			// Next with just first letter capitalization
			sTmp[0] = 'A' + (sTmp[0] - 'a');
			if( (ret = FindWordInFileSystemDict(sTmp, sPron, piBitFlag, sHomo, piHomoFlag, fp, offset)) > 0 )
				return ret;
		}
	}

	return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;FindWord
 * DESC: 	Try several permutations to find the word before giving up
 * IN:		sWord - word to lookup
 * OUT:		sPron - pronunciation of sWord
			piBitFlag - bit flag for sWord
			sHomo - optional pronunciation of homograph
			piHomoFlag - optional bit flag of homograph
 * RETURN:	pronunciation data on success, NULL on failure
 * NOTES:	
 *END_HEADER***************************/
#ifdef _BIGENDIAN_
int FindWord(char *sWord, char *sPron, int *piBitFlag, char *sHomo, int *piHomoFlag, void *fp)
#else
int FindWord(char *sWord, char *sPron, int *piBitFlag, char *sHomo, int *piHomoFlag, FILE *fp)
#endif
{
	return FindWordWithOffset(sWord, sPron, piBitFlag, sHomo, piHomoFlag, fp, 0);

}


/*FUNCTION_HEADER**********************
 * NAME:	;ReadPronData
 * DESC: 	Read the pronunciation and associated data
 * IN:		fp - file pointer to dictionary
			offset - offset to pronunciation data
			iDictOffset - offset to Dictionary in multi-dictionary file
			nMaxPron - maximum length of sPron
 * OUT:		sPron - pronunciation data
			piData - associated data (bitflag or rule)
 * RETURN:	1 on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
#ifdef _BIGENDIAN_
int ReadPronData(void *fp, unsigned int offset, 
				 char *sPron, int nMaxPron, int *piData)
#else
int ReadPronData(FILE *fp, unsigned int offset, 
				 char *sPron, int nMaxPron, int *piData)
#endif
{
	int i=0;
	unsigned int uiData=0;

	// Seek to the pronunciation data
	if( fseek(fp, offset, SEEK_SET) != 0 )
		return 0;
	
	// Read the numeric data (bitflag or rule)
	if( fread(&uiData, sizeof(int), 1, fp) != 1 )
		return 0;

	if( piData )
		*piData = uiData;
	
	if( sPron )
	{
		for(i=0; i<nMaxPron; i++)
		{
			if( fread(&sPron[i], sizeof(char), 1, fp) != 1 )
				return 0;

			if( sPron[i] == 0x00 )
				break;
		}
	}

	return 1;

}

/*FUNCTION_HEADER**********************
 * NAME:	;FindAllWordSegments
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	number of word segments found
 * NOTES:	
 *END_HEADER***************************/
#ifdef _BIGENDIAN_
int FindAllWordSegments(char *sWord, WORD_SEG_LIST *pWordSegList, int nMaxWordSegs, void *fp, 
						unsigned int uiDictOffset)
#else
int FindAllWordSegments(char *sWord, WORD_SEG_LIST *pWordSegList, int nMaxWordSegs, FILE *fp, 
						unsigned int uiDictOffset)
#endif
{
	int i=0, 
		iLtrsUsed = 0,
		iData=0;
	unsigned int
		uiOffset = 0;

	for(i=0; i<nMaxWordSegs && FindWordSegsInFileSystemDict(sWord, NULL, 
			&(pWordSegList[i].iPronOffset), 
			&iData, NULL, NULL, 
			&iLtrsUsed, &uiOffset, fp, uiDictOffset) > 0; 
		i++ )
	{
		pWordSegList[i].iLettersUsed = (char)iLtrsUsed;
		pWordSegList[i].iRule = (char)iData;

		if( iLtrsUsed == (int)strlen(sWord) ||		// Found the whole word, we're done
			uiOffset == 0 )							// We found portions of the word but not the whole word
		{
			return i+1;
		}
	}

	return i;

}
