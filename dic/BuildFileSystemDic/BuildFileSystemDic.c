/*C_HEADER_FILE****************************************************************
FILE			:	BuildFileSystemDic.c
DESC			:	
TABS			:	3
OWNER			:	
DATE CREATED	:	19 Oct 2005

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
#include <stdlib.h>
#include <string.h>
#include "BuildFileSystemDic.h"
#include "FileSystemDict.h"

// The following is a sample text dictionary entry
// account,N,xk'Wnt,00000000001000000100000000000,150

int gnBranches = 0;				// This is just a debug tool

// =====================================================================
//	The following functions are used to load a raw text dictionary into
//  memory, sort it so that you can find words by doing a binary search
// =====================================================================

/*FUNCTION_HEADER**********************
 * NAME:	;FreeDictionary
 * DESC: 	Free memory used by a dictionary
 * IN:		pDict - pointer to dictionary data
			nEntries - number of entries in pDict
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void FreeDictionary(DICT *pDict, int nEntries)
{
	int i;

	if( pDict == NULL )
		return;

	for(i=0; i<nEntries; i++)
	{
		if( pDict[i].sPron )	free(pDict[i].sPron);
		if( pDict[i].sWord )	free(pDict[i].sWord);
	}

	free(pDict);
}

/*FUNCTION_HEADER**********************
 * NAME:	;DictWordCmp
 * DESC: 	Compare two words in the dictionary
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int DictWordCmp( const void *arg1, const void *arg2 )
{
	DICT p1 = *(DICT *)arg1,
		 p2 = *(DICT *)arg2;

   /* Compare all of both strings: */
   return _stricmp( p1.sWord, p2.sWord );
}


/*FUNCTION_HEADER**********************
 * NAME:	;SortDictionary
 * DESC: 	Sort the in-memory dictionary
 * IN:		pDict, nEntries
 * OUT:		data in pDict is sorted so we can do bsearch on it
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void SortDictionary(DICT *pDict, int nEntries)
{
	qsort(pDict, nEntries, sizeof(DICT), DictWordCmp);
}


/*FUNCTION_HEADER**********************
 * NAME:	;ReverseOrder
 * DESC: 	Reverse the order of a string
 * IN:		sStr - the string
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void ReverseOrder(char *sStr)
{
	char *pc1, *pc2, cTmp;

	for(pc1=sStr, pc2=sStr+strlen(sStr)-1; pc2 > pc1; pc1++, pc2--)
	{	
		// Swap characters
		cTmp = *pc1;
		*pc1 = *pc2;
		*pc2 = cTmp;
	}
}

unsigned int DigestBitFlags(char *sStr)
{
	char *pc;
	unsigned int i, uiFlags;
	unsigned int puiMask[] = {
		FC_M_ADJ,
		FC_M_ADV,
		FC_M_ART,
		FC_M_AUX,
		FC_M_BE,
		FC_M_BEV,
		FC_M_CONJ,
		FC_M_ED,
		FC_M_HAVE,
		FC_M_ING,
		FC_M_NOUN,
		FC_M_POS,
		FC_M_PREP,
		FC_M_PRON,
		FC_M_SUBCONJ,
		FC_M_THAT,
		FC_M_TO,
		FC_M_VERB,
		FC_M_WHO,
		FC_M_NEG,
		FC_M_INTER,
		FC_M_REF,
		FC_M_PART,
		FC_M_FUNC,
		FC_M_CONTRACTION,		// dic_comm.c uses FC_M_CONTRACTION here instead of FC_M_CONT
		FC_M_PRIMHOMO,
		FC_M_REFR,
		FC_M_UNKN,
		FC_M_NAME,
		FC_M_FC_MARKER,
		FC_M_CONTRACTION,
		FC_M_HOMOGRAPH,
		0
	};


	uiFlags = 0;
	for(pc = sStr, i=0; *pc && puiMask[i] != 0; pc++, i++)
	{
		if( *pc == '1' )
			uiFlags |= puiMask[i];
	}
	
	return uiFlags;

}

/*FUNCTION_HEADER**********************
 * NAME:	;ParseDictEntry
 * DESC: 	Parse a dictionary entry
 * IN:		sBuf - the raw data to parse
 * OUT:		parsed data is put in pDict
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void ParseDictEntry(char *sBuf, DICT *pDict)
{
	char	*sTok;

	if( (sTok = strtok(sBuf, ",")) )
		pDict->sWord = strdup(sTok);
	else	
		return;

	if( (sTok = strtok(NULL, ",")) )
		pDict->cHomo = sTok[0];
	else
		return;

	if( (sTok = strtok(NULL, ",")) )
		pDict->sPron = strdup(sTok);
	else
		return;

	if( (sTok = strtok(NULL, ",")) )
	{
		pDict->iBitFlags = DigestBitFlags(sTok);
		if( pDict->cHomo == 'P' )
		{
			pDict->iBitFlags |= (FC_M_PRIMHOMO | FC_M_HOMOGRAPH);
		}
		else if( pDict->cHomo == 'S' )
		{
			pDict->iBitFlags |= FC_M_HOMOGRAPH;
		}
	}
	else
		return;

	if( (sTok = strtok(NULL, ",\n\r")) )
		pDict->iPriority = atol(sTok);

}

/*FUNCTION_HEADER**********************
 * NAME:	;LoadDictionary
 * DESC: 	Load a dictionary from file
 * IN:		sInFile - dictionary filename
 * OUT:		pnEntries - number of entires in the dictionary
 * RETURN:	pointer to the dictionary on success, NULL on failure
 * NOTES:	
 *END_HEADER***************************/
DICT *LoadDictionary(char *sInFile, int *pnEntries)
{
	char sBuf[512];
	int	 i,
		 nEntries=0;
	DICT *pDict;
	FILE *fp;

	// Open the text dictionary for read
	if( (fp = fopen(sInFile, "rt")) == NULL )
	{
		printf("Error: Can't open dictionary %s\n", sInFile);
		return NULL;
	}

	// Count the number of entries in the dictionary
	while( fgets(sBuf, 512, fp) )
	{
		if( sBuf[0] != ';' )
			nEntries++;
	}

	// Allocate memory to hold all entries
	if( (pDict = (DICT *)calloc(nEntries, sizeof(DICT))) == NULL )
	{
		printf("Error: Out of memory in LoadDictionary\n");
		return NULL;
	}

	// Reset back to the beginning of the file
	fseek(fp, 0L, SEEK_SET);

	// Read the dictionary
	for( i=0; i<nEntries && fgets(sBuf, 512, fp); )
	{
		if( sBuf[0] != ';' )
		{
			ParseDictEntry(sBuf, &pDict[i++]);
		}
	}

	if( pnEntries )
		*pnEntries = nEntries;

	fclose(fp);
	return pDict;
}

/* ========================================================================
	
	  These functions are used to determine what the unique set of symbols
	  are in a dictionary and to read/write them.

   ======================================================================== */

/*FUNCTION_HEADER**********************
 * NAME:	;SymbolCmp
 * DESC: 	compare 2 characters
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	this function is used to sort a character string
 *END_HEADER***************************/
int SymbolCmp( const void *arg1, const void *arg2 )
{
	char c1 = *(char *)arg1,
		 c2 = *(char *)arg2;

	if( c1 > c2 ) 
		return 1;
	else if( c1 < c2 )
		return -1;
	else 
		return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;SortSymbolList
 * DESC: 	sort the characters in a string
 * IN:		sSymbols - the character string
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void SortSymbolList(char *sSymbols)
{
	qsort(sSymbols, strlen(sSymbols), sizeof(char), SymbolCmp);
}

/*FUNCTION_HEADER**********************
 * NAME:	;BuildSymbolList
 * DESC: 	Find all of the unique symbols in a dictionary
 * IN:		pDict - pointer to a dictionary
			nEntries - number of entries in the dictionary
 * OUT:		
 * RETURN:	sSymbols - a list of symbols used in pDict on success
			NULL on failure
 * NOTES:	
 *END_HEADER***************************/
char *BuildSymbolList(DICT *pDict, int nEntries)
{
	char sSymbols[512],
		 *pc;
	int	 i;

	memset(sSymbols, 0, 512*sizeof(char));

	for(i=0; i<nEntries; i++)									// for all entries in dictionary
	{
		for(pc=pDict[i].sWord; *pc; pc++)						// for all characthers in word
		{
			if( strchr(sSymbols, *pc) == NULL )
			{
				*(sSymbols + strlen(sSymbols)) = *pc;
			}
		}
	}

	SortSymbolList(sSymbols);		// Sort symbols by alphabetical order

	if( strlen(sSymbols) > 0 )
		return strdup(sSymbols);
	else
		return NULL;
}

/*FUNCTION_HEADER**********************
 * NAME:	;ReadSymbolList
 * DESC: 	Read the allowable symbol list from a file
 * IN:		sSymbolFile - symbol list filename
 * OUT:		
 * RETURN:	list of symbols
 * NOTES:	
 *END_HEADER***************************/
char *ReadSymbolList(char *sSymbolFile)
{
	char sBuf[512];
	FILE *fp;

	if( (fp = fopen(sSymbolFile, "rt")) == NULL )
		return NULL;

	sBuf[0] = 0x00;
	fgets(sBuf, 512, fp);

	fclose(fp);

	if( strlen(sBuf) > 0 )
		return strdup(sBuf);
	else
		return NULL;
}


/*FUNCTION_HEADER**********************
 * NAME:	;WriteSymbolList
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void WriteSymbolList(char *sSymbolFile, char *sSymbols)
{
	FILE *fp;

	if( (fp = fopen(sSymbolFile, "wt")) == NULL )
		return;

	fprintf(fp, "%s", sSymbols);

	fclose(fp);

}


/* ================================================================

	Functions to build and use an in-memory Letter-Tree dictionary

   ================================================================ */

/*FUNCTION_HEADER**********************
 * NAME:	;GetNewBranch
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
BRANCH *GetNewBranch(void)
{
	BRANCH *pBranch;

	if( (pBranch = (BRANCH *)calloc(1, sizeof(BRANCH))) == NULL )
		return NULL;

	gnBranches++;

	return pBranch;
}

/*FUNCTION_HEADER**********************
 * NAME:	;SymbolStructCmp
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int SymbolStructCmp(const void *arg1, const void *arg2)
{
	SYMBOL s1 = *(SYMBOL *)arg1,
		   s2 = *(SYMBOL *)arg2;

	if( s1.cSym > s1.cSym ) 
		return 1;
	else if( s1.cSym < s2.cSym )
		return -1;
	else 
		return 0;

}

/*FUNCTION_HEADER**********************
 * NAME:	;SortBranchBySymbolStruct
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void SortBranchBySymbolStruct(BRANCH *pBr)
{
	qsort(pBr->pSyms, pBr->nSym, sizeof(SYMBOL), SymbolStructCmp);
}

/*FUNCTION_HEADER**********************
 * NAME:	;GetBranchSymbolIndex
 * DESC: 	Get the index of a symbol on a branch
 * IN:		pBr - pointer to the branch
			cSym - the symbol to find
 * OUT:		none
 * RETURN:	index of symbol on success, -1 on failure
 * NOTES:	
 *END_HEADER***************************/
int GetBranchSymbolIndex(BRANCH *pBr, char cSym)
{
	int i;
	for(i=0; i<pBr->nSym; i++)
	{
		if( pBr->pSyms[i].cSym == cSym )
			return i;
	}
	return -1;
}

/*FUNCTION_HEADER**********************
 * NAME:	;AddSymbolStructToBranch
 * DESC: 	Add a new symbol to a branch of the LTree
 * IN:		pBr - pointer to the branch where the symbol is to be added
			cSym - the new symbol
 * OUT:		none
 * RETURN:	index to symbol on success, -1 on failure
 * NOTES:	
 *END_HEADER***************************/
int AddSymbolStructToBranch(BRANCH *pBr, char cSym)
{
	int nSym;

	if( pBr == NULL )
		return -1;

	pBr->nSym++;
	nSym = pBr->nSym;
	
	if( (pBr->pSyms = (SYMBOL *)realloc(pBr->pSyms, nSym*sizeof(SYMBOL))) == NULL )
		return -1;

	pBr->pSyms[nSym-1].cSym = cSym;
	pBr->pSyms[nSym-1].pNext = NULL;
	pBr->pSyms[nSym-1].sData = NULL;

//	SortBranchBySymbolStruct(pBr);

	return GetBranchSymbolIndex(pBr, cSym);
}

/*FUNCTION_HEADER**********************
 * NAME:	;AddWordToLTree
 * DESC: 	Add a new word to the letter-tree
 * IN:		sWord - the new word
			sData - output data for sWord, typically the pronunciation
			pLTree - pointer to the LTree being built
			bLowerCase - flag to build dictionary with lower case letters only
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void AddWordToLTree(char *sWord, char *sData, BRANCH *pLTree, bool bLowerCase)
{
	char *pc;
	int	 iSym;
	BRANCH *pBr;

	if( sWord == NULL )
		return;

	for(pc=sWord, pBr=pLTree; *pc; pc++)
	{
		if( bLowerCase &&
			'A' <= *pc && *pc <= 'Z' )
		{
			*pc = 'a' + (*pc - 'A');							// Build LTree with all lower case
		}

		if( (iSym = GetBranchSymbolIndex(pBr, *pc)) < 0)		// get the symbol index
		{
			iSym = AddSymbolStructToBranch(pBr, *pc);			// add a new symbol to this branch
		}

		if( *(pc+1) == 0x00 )									// this is the last symbol of the word
		{
			if( !pBr->pSyms[iSym].sData )
				pBr->pSyms[iSym].sData = strdup(sData);			// add data at last symbol
			return;
		}
		else if( pBr->pSyms[iSym].pNext == NULL )				// add a new branch for the next symbol
		{
			pBr->pSyms[iSym].pNext = GetNewBranch();
		}
		pBr = pBr->pSyms[iSym].pNext;							// Follow the branch to next symbol
	}
}


/*FUNCTION_HEADER**********************
 * NAME:	;BuildLetterTree
 * DESC: 	Build in-memory Letter-Tree version of dictionary
 * IN:		pDict - in-memory dictionary sorted alphabetically
			nEntries - number of entries in dictionary
			bLowerCase - flag to create dictionary with lower case letters only
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
BRANCH *BuildLetterTree(DICT *pDict, int nEntries, bool bLowerCase)
{
	char sPronData[512];
	int	i;
	BRANCH *pLTree;

	if( !pDict || nEntries <= 0 )
		return NULL;

	pLTree = GetNewBranch();

	for( i=0; i<nEntries; i++ )
	{
		if( (pDict[i].iBitFlags & FC_M_HOMOGRAPH) )						// Found a homograph
		{

			if( pDict[i].iBitFlags & FC_M_PRIMHOMO )					// It's a primary homograph
			{
				if( i < nEntries-1 && 
					strcmp(pDict[i].sWord, pDict[i+1].sWord) == 0 &&	// Make sure the secondary homograph is next
					!(pDict[i+1].iBitFlags & FC_M_PRIMHOMO) )
				{
					sprintf(sPronData, "0x%08x,%s,0x%08x,%s",			// Create pronunciation data with primary homograph first
						pDict[i].iBitFlags, pDict[i].sPron, 
						pDict[i+1].iBitFlags , pDict[i+1].sPron);
					i++;												// Skip next word since it has already been used
				}
				else
				{
					sprintf(sPronData, "0x%08x,%s", pDict[i].iBitFlags, pDict[i].sPron);
					printf("Warning: Found a problem with homograph %s\n", pDict[i].sWord);
				}

			}
			else														// It's a secondary homograph
			{
				if( i < nEntries-1 && 
					strcmp(pDict[i].sWord, pDict[i+1].sWord) == 0 &&	// Make sure that the primary homograph is next
					(pDict[i+1].iBitFlags & FC_M_PRIMHOMO) )
				{
					sprintf(sPronData, "0x%08x,%s,0x%08x,%s",			// Create pronunciation data with primary homograph first
						pDict[i+1].iBitFlags, pDict[i+1].sPron, 
						pDict[i].iBitFlags , pDict[i].sPron);
					i++;												// Skip next word since it has already been used
				}
				else
				{
					sprintf(sPronData, "0x%08x,%s", pDict[i].iBitFlags, pDict[i].sPron);
					printf("Warning: Found a problem with homograph %s\n", pDict[i].sWord);
				}

			}
		}
		else if( pDict[i].sPron )
		{
			sprintf(sPronData, "0x%08x,%s", pDict[i].iBitFlags, pDict[i].sPron);
		}
		else
		{
			sprintf(sPronData, "%d", pDict[i].iBitFlags);		// End-of-Word marker only
		}
		AddWordToLTree(pDict[i].sWord, sPronData, pLTree, bLowerCase);
	}

	return pLTree;
}

/*FUNCTION_HEADER**********************
 * NAME:	;FreeLTree
 * DESC: 	Release memory used by LTree
 * IN:		pLTree - pointer to head of LTree
 * OUT:		none
 * RETURN:	none
 * NOTES:	This function is recursive
 *END_HEADER***************************/
void FreeLTree(BRANCH *pLTree)
{
	int i;

	for( i=0; i<pLTree->nSym; i++)
	{
		if( pLTree->pSyms[i].pNext )				// Make sure that all of the next pointers are free
		{
			FreeLTree(pLTree->pSyms[i].pNext);		// Recurse down into the tree
		}

		if( pLTree->pSyms[i].sData )				// Make sure that all of the data space is free
		{
			free(pLTree->pSyms[i].sData);
			pLTree->pSyms[i].sData = NULL;
		}
	}
	free(pLTree->pSyms);
	free(pLTree);									// Free this branch
}

/*FUNCTION_HEADER**********************
 * NAME:	;SizeOfData
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
unsigned int SizeOfData(char *sData)
{
	char *pc1, *pc2;
	unsigned int nSize = 0;

	if( sData && 
		*sData != '1')									// End-of-word marker doesn't use any Data space
	{
		nSize += sizeof(long);							// Bit Flag 1
		if( (pc1 = strchr(sData, ',')) != NULL )
		{
			pc1++;
			if( (pc2 = strchr(pc1, ',')) != NULL )
			{
				*pc2 = 0x00;
				nSize += strlen(pc1) + 1;				// Pronunciation 1 + NULL
				*pc2 = ',';
				
				pc2 += 12;								// Skip bit flag
				nSize += sizeof(long);					// Bit Flag 2
				nSize += strlen(pc2) + 1;				// Pronunciation 2 + NULL
			}
			else
			{
				nSize += strlen(pc1) + 1;				// Pronunciation 1 + NULL
			}
		}
	}

	return nSize;
}

/*FUNCTION_HEADER**********************
 * NAME:	;GetLTreeSize
 * DESC: 	Recursively sum the size of the LTree
 * IN:		pLTree - pointer to head of LTree
 * OUT:		none
 * RETURN:	size of LTree
 * NOTES:	
 *END_HEADER***************************/
int GetLTreeSize(BRANCH *pLTree)
{
	int i,
		nSize=0;

	for( i=0; i<pLTree->nSym; i++)
	{
		if( pLTree->pSyms[i].pNext )
			nSize += GetLTreeSize(pLTree->pSyms[i].pNext);	// Recurse down into the tree

		if( pLTree->pSyms[i].sData )						// Get data size
		{
			if( strcmp(pLTree->pSyms[i].sData, "1") != 0 )
				nSize += SizeOfData(pLTree->pSyms[i].sData);
		}
	}

	// Size of this branch on disk		nSym + (nSym * (cSym+iNext+iData))
	nSize += sizeof(char) + pLTree->nSym * (sizeof(char) + sizeof(int) + sizeof(int));

	gnBranches++;

	return nSize;
}

/*FUNCTION_HEADER**********************
 * NAME:	;GetLTreeSizeWithoutData
 * DESC: 	Calculate the size of the LTree without
			the output data or in other words where is
			the end of the LTree and beginning of where I
			can start to store data in the File System version
 * IN:		pLTree
 * OUT:		none
 * RETURN:	size of LTree minus the data
 * NOTES:	This function is recursive
 *END_HEADER***************************/
int GetLTreeSizeWithoutData(BRANCH *pLTree)
{
	int i,
		nSize=0;

	for( i=0; i<pLTree->nSym; i++)
	{
		if( pLTree->pSyms[i].pNext )
			nSize += GetLTreeSizeWithoutData(pLTree->pSyms[i].pNext);	// Recurse down into the tree
	}

	// Size of this branch on disk		nSym + (nSym * (cSym+iNext+iData))
	nSize += sizeof(char) + pLTree->nSym * (sizeof(char) + sizeof(int) + sizeof(int));

	gnBranches++;

	return nSize;
}

/*FUNCTION_HEADER**********************
 * NAME:	;GetDataSizeInLTree
 * DESC: 	Calculate how much output data is stored in the LTree
 * IN:		pLTree - pointer to a branch in the pLTree.  This should be 
			the head branch for the first call.
 * OUT:		none
 * RETURN:	size of data stored in LTree
 * NOTES:	This function is recursive
 *END_HEADER***************************/
unsigned int GetDataSizeInLTree(BRANCH *pLTree)
{
	int i,
		nSize=0;

	for( i=0; i<pLTree->nSym; i++)
	{
		if( pLTree->pSyms[i].pNext )
			nSize += GetDataSizeInLTree(pLTree->pSyms[i].pNext);	// Recurse down into the tree

		if( pLTree->pSyms[i].sData )						// Get data size
		{
			if( strcmp(pLTree->pSyms[i].sData, "1") != 0 )
				nSize += SizeOfData(pLTree->pSyms[i].sData);
		}
	}

	gnBranches++;

	return nSize;
}

/*FUNCTION_HEADER**********************
 * NAME:	;FindWordInLTree
 * DESC: 	Traverse the LTree to find a word
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
char *FindWordInLTree(char *sWord, BRANCH *pLTree)
{
	char *pc;
	int	 iSym;
	BRANCH *pBr;

	for(pc=sWord, pBr=pLTree; *pc && pBr; pc++)
	{
		if( (iSym = GetBranchSymbolIndex(pBr, *pc)) >= 0)	// get the symbol index
		{
			if( *(pc+1) == 0x00 )					// last symbol of word
				return pBr->pSyms[iSym].sData;		// return data
			else
				pBr = pBr->pSyms[iSym].pNext;		// Follow the branch
		}
	}

	return NULL;
}

/* ==========================================================================

		The following functions are used to build a File System based dictionary from
		an in-memory LTREE type dictionary

   ========================================================================== */

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
unsigned int ByteSwap32(unsigned int i)
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
unsigned short ByteSwap16(unsigned short i)
{
   return ((unsigned short) 0x00FFU & i >> 8) | ((unsigned short) 0xFF00U & i << 8);
}


/*FUNCTION_HEADER**********************
 * NAME:	;WriteBranchesInLTree
 * DESC: 	Write out the file system based dictionary
 * IN:		pLTree - pointer to a branch of the in-memory LTREE type dictionary
			iBrOff - offset to where this branch is to be written
			*piBrOff - offset to where next branch is to be written
			*piDtOff - offset to where the next output data is to be written
			*fp -file pointer to output file
 * OUT:		piBrOff - updated by this function
			piDtOff - updated by this function
 * RETURN:	none
 * NOTES:	This function is recursive
 *END_HEADER***************************/
void WriteBranchesInLTree(BRANCH *pLTree,
						  unsigned int iBrOff,
						  unsigned int *piBrOff, 
						  unsigned int *piDtOff,
						  bool bBigEndian,
						  FILE *fp)
{
	int	i;
	char 
		cnSym,
		sSymbols[MAX_SYMBOLS],
		*stopscan,
		*pc,
		cNull=0x00;
	FILESYS_SYMBOL	
		tSym[MAX_SYMBOLS];
	unsigned short	
		nSym, 
		iBrSz;
	unsigned int
		uiBitFlag;
	BRANCH	
		*pBr=pLTree;

	if( pLTree == NULL )
		return;

	nSym = pBr->nSym;
	for( i=0; i<nSym; i++)
	{
		sSymbols[i] = pBr->pSyms[i].cSym;

		if(	pBr->pSyms[i].pNext )
		{
			tSym[i].iNext = *piBrOff;				// Store the branch file offset
			iBrSz = sizeof(char) + pBr->pSyms[i].pNext->nSym * (sizeof(char) + sizeof(int) + sizeof(int));
			*piBrOff += iBrSz;						// Update the branch offset to the next location to write a branch
		}
		else
		{
			tSym[i].iNext = 0;
		}

		if( pBr->pSyms[i].sData )
		{
			if( strstr(pBr->pSyms[i].sData, "0x") )
			{
				tSym[i].iData = *piDtOff;						// Store the data file offset
				*piDtOff += SizeOfData(pBr->pSyms[i].sData);	// update for next data offset
			}
			else
			{
				tSym[i].iData = atoi(pBr->pSyms[i].sData);		// End-of-Word marker only
			}
		}
		else
		{
			tSym[i].iData = 0;
		}
	}

	sSymbols[nSym] = 0x00;

	// Write this branch
	i = sizeof(FILESYS_SYMBOL);
	fseek(fp, iBrOff, SEEK_SET);						// Seek to where we are going to write this branch
	cnSym = (unsigned char)nSym;
	fwrite(&cnSym, sizeof(char), 1, fp);				// Write the number of symbols in this branch
	fwrite(sSymbols, sizeof(char), nSym, fp);
	if( bBigEndian )
	{
		for(i=0; i<nSym; i++)
		{
			tSym[i].iNext = ByteSwap32(tSym[i].iNext);
			tSym[i].iData = ByteSwap32(tSym[i].iData);
		}
	}
	fwrite(tSym, sizeof(FILESYS_SYMBOL), nSym, fp);			// Write the symbol array
	if( bBigEndian )
	{
		for(i=0; i<nSym; i++)
		{
			tSym[i].iNext = ByteSwap32(tSym[i].iNext);
			tSym[i].iData = ByteSwap32(tSym[i].iData);
		}
	}

	// Write data for each end of word
	for( i=0; i<nSym; i++)
	{
		if( tSym[i].iData > 1 )									// Write data only if there is more than an end-of-word marker
		{
			fseek(fp, tSym[i].iData, SEEK_SET);

			uiBitFlag = strtoul(pBr->pSyms[i].sData, &stopscan, 16);

			if( bBigEndian )
				uiBitFlag = ByteSwap32(uiBitFlag);

			fwrite(&uiBitFlag, sizeof(int), 1, fp);				// Write Bit Flag #1

			pc = ++stopscan;									// Find beginning of Pronunciation
			if( (stopscan = strchr(pc, ',')) == NULL )			// Check for homograph 
			{
				fwrite(pc, sizeof(char), strlen(pc), fp);		// Write pronunciation #1
				fwrite(&cNull, sizeof(char), 1, fp);			// Write null termination character
			}
			else
			{
				*stopscan = 0x00;								// Null terminate pronunction #1
				fwrite(pc, sizeof(char), strlen(pc), fp);		// Write pronunctiation #1
				fwrite(&cNull, sizeof(char), 1, fp);			// Write null termination chaaracter
				*stopscan = ',';
				pc = ++stopscan;
				uiBitFlag = strtoul(pc, &stopscan, 16);			// Get Bit Flag #2

				if( bBigEndian )
					uiBitFlag = ByteSwap32(uiBitFlag);

				fwrite(&uiBitFlag, sizeof(int), 1, fp);			// Write Bit Flag #2

				pc = ++stopscan;
				fwrite(pc, sizeof(char), strlen(pc), fp);		// Write pronunciation #2
				fwrite(&cNull, sizeof(char), 1, fp);			// Write null termination chaaracter
			}

		}
	}

	// Recurse down the tree
	for( i=0; i<nSym; i++)
	{
		if( pLTree->pSyms[i].pNext )
		{
			WriteBranchesInLTree(pLTree->pSyms[i].pNext, tSym[i].iNext, piBrOff, piDtOff, bBigEndian, fp);
		}
	}
}


/*FUNCTION_HEADER**********************
 * NAME:	;BuildFileSystemDict
 * DESC: 	Build and write a file system dictionary
 * IN:		sOutFile - filename of the output dictionary
			pLTree - pointer to the in-memory LTREE type dictionary
 * OUT:		output file
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void BuildFileSystemDict(char *sOutFile, BRANCH *pLTree, bool bBigEndian)
{
	char	sString[MAX_SYMBOLS];
	int		i; 
	unsigned int 
			iBrOff,		// Branch offset
			iDtOff,		// Data offset
			iDt,		// Size of data in LTree
			nLtreeSz;	// Size of LTree in bytes
	FILE	*fp;

	if( sOutFile == NULL || pLTree == NULL )
		return;

	if( (fp = fopen(sOutFile, "wb")) == NULL )
		return;

	gnBranches = 0;										// gnBranches is just a debug tool
	nLtreeSz = GetLTreeSize(pLTree);					// Get the size of the LTree on disk
	
	memset(sString, 0, MAX_SYMBOLS*sizeof(char));		// Create an empty file
	for(i=nLtreeSz; i > 0; i-=MAX_SYMBOLS)
	{
		if( i < MAX_SYMBOLS )
			fwrite(sString, sizeof(char), i, fp);
		else
			fwrite(sString, sizeof(char), MAX_SYMBOLS, fp);
	}

	gnBranches = 0;
	iDt = GetDataSizeInLTree(pLTree);					// Not really used

	gnBranches = 0;
	iDtOff = GetLTreeSizeWithoutData(pLTree);			// Get start of data section

	gnBranches = 0;

	// Get the offset to the first branch after the head branch
	iBrOff = sizeof(char) + pLTree->nSym * (sizeof(char) + sizeof(int) + sizeof(int));
	WriteBranchesInLTree(pLTree, 0, &iBrOff, &iDtOff, bBigEndian, fp);

	fclose(fp);
}


/*FUNCTION_HEADER**********************
 * NAME:	;TestFileSystemDict
 * DESC: 	Test a filesystem dictionary
 * IN:		sFile - dictionary filename
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void TestFileSystemDict(char *sFile)
{
	char sBuf[MAX_SYMBOLS],
		 sPron[MAX_SYMBOLS],
		 sHomo[MAX_SYMBOLS],
		 sWord[MAX_SYMBOLS];
	int	 iLtrsUsed;
	unsigned int 
		 uiBitFlag, 
		 uiHomoFlag,
		 uiOffset;
	FILE *fp;

	if( (fp = fopen(sFile, "rb")) == NULL )
		return;

	printf("\nEnter a word to test it: ");
	while( gets(sBuf) )		// Test the newly built LTree
	{
		if( !sBuf[0] )		// get out if nothing was entered
			break;
			
		if( FindWord(sBuf, sPron, &uiBitFlag, sHomo, &uiHomoFlag, fp) )
		{
			printf("Found: %s, Pron: %s, Bit Flag: 0x%08x\n", sBuf, sPron, uiBitFlag);

			if( uiBitFlag & FC_M_HOMOGRAPH )
			{
				printf("\tHomograph: %s, Bit Flag: 0x%08x\n", sHomo, uiHomoFlag);
			}
		}
		else
			printf("%s not found\n", sBuf);

		printf("\n---------------------\nFinding by parts.\n---------------------\n");

		iLtrsUsed = 0;
		uiOffset = 0;
		while( FindWordSegsInFileSystemDict(sBuf, sPron, NULL, &uiBitFlag, 
			sHomo, &uiHomoFlag, &iLtrsUsed, &uiOffset, fp, 0) > 0 )
		{
			strncpy(sWord, sBuf, iLtrsUsed);
			sWord[iLtrsUsed] = 0x00;
			printf("Found %s, Data %s\n", sWord, sPron);
		}


		printf("\n=====================\nWord: ");
	}

}


/*FUNCTION_HEADER**********************
 * NAME:	;main
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int main(int argc, char **argv)
{
	char sBuf[128];
	char *sInFile=NULL,
		 *sOutFile=NULL,
		 *sSymbolFile=NULL,
		 *sSymbols=NULL,
		 *sData;
	bool bTestDict=false;
	bool bBigEndian=false;
	bool bLowerCase=false;
	bool bGerman=false;
	bool bItalian=false;
	int	 i, nEntries;
	DICT *pDict;
	BRANCH *pLTree;

	// Parse the command line arguments to get the input and output filenames
	for( i=1; i<argc; i++)
	{
		if( argv[i][0] == '-' )
		{
			switch( argv[i][1] )
			{
				case 'B':
				case 'b':
					bBigEndian = true;
					break;

				case 'G':
				case'g':
					bGerman = true;
					break;

				case 'I':
					bItalian = true;
					break;

				case 'i':	
					sInFile = argv[++i];		// Get the input (raw text dictionary) filename
					break;

				case 'L':						// Build the letter tree with all lower case letters
				case 'l':
					bLowerCase = true;
					break;

				case 'O':
				case 'o':	
					sOutFile = argv[++i];		// Get the output (file system letter tree) filename
					break;

				case 'S':
				case 's':	
					sSymbolFile = argv[++i];	// Optional output file for list of symbols in dictionary
					break;

				case 'T':
				case 't':
					bTestDict = true;
					break;

			}
		}
	}

	if( sInFile == NULL || sOutFile == NULL )
	{
		printf("Usage: %s -i <infile> -o <outfile> [-s <symbol file>] [-t] [-b] [-g|-I] [-l]\n", argv[0]);
		printf("\t<infile> - input raw text dictionary file\n");
		printf("\t<output> - output file system letter-tree format dictionary\n");
		printf("\t-s <symbol file> - optional output file for all unique symbols used in dictionary\n");
		printf("\t-t - test dictionary\n");
		printf("\t-b - output dictionary in big-endian format\n");
		printf("\t-g - dictionary is German\n");
		printf("\t-I - dicitionary is Italian\n");
		printf("\t-l - create dictionary in lower-case letters only\n");
		exit(0);
	}

	// Read the raw text dictionary file
	printf("Reading: %s ...", sInFile);
	if( bGerman )
	{
		BuildGermanCompositeDict(sInFile, sOutFile, bTestDict, bLowerCase, bBigEndian);
		exit(0);
	}
	else if( bItalian )
	{
		BuildItalianCompositeDict(sInFile, sOutFile, bTestDict, bLowerCase, bBigEndian);

		exit(0);
	}
	else if( (pDict = LoadDictionary(sInFile, &nEntries)) == NULL )
	{
		exit(0);
	}

	// Sort the in-memory dictionary
	SortDictionary(pDict, nEntries);

	printf(" Done. %d entries read\n", nEntries);

	// Create a list of all symbols used in this dictionary
	if( sSymbolFile && (sSymbols = BuildSymbolList(pDict, nEntries)) != NULL)
	{
		WriteSymbolList(sSymbolFile, sSymbols);		// Save symbols to file

		printf("Symbols(%d): %s\n", strlen(sSymbols), sSymbols);

		free(sSymbols);
	}

	// Build an in-memory letter-tree version of the dictionary
	printf("Building LTree in memory.\n");
	if( (pLTree = BuildLetterTree(pDict, nEntries, bLowerCase)) != NULL )
	{
		if( bTestDict )
		{
			printf("Enter a word to test it: ");
			while( gets(sBuf) )		// Test the newly built LTree
			{
				if( !sBuf[0] )		// get out if nothing was entered
					break;
					
				if( (sData = FindWordInLTree(sBuf, pLTree)) != NULL )
					printf("Found %s, Data %s\n", sBuf, sData);
				else
					printf("%s not found\n", sBuf);

				printf("\nWord: ");
			}
		}
	}

	// Build a File system letter-tree version of the dictionary
	if( sOutFile )
	{
		printf("\n***************************************\nBuilding File System based dictionary.\n");

		BuildFileSystemDict(sOutFile, pLTree, bBigEndian);

		if( bTestDict )
			TestFileSystemDict(sOutFile);
	}

	if( pLTree )
		FreeLTree(pLTree);

	FreeDictionary(pDict, nEntries);

}

