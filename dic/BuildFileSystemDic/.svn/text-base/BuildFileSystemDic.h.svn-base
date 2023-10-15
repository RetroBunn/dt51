/*H_HEADER_FILE***************************************************************
FILE			: BuildFileSystemDic.h
DESC			: 
TABS			: 3
OWNER			: Fonix
DATE CREATED	: 3 November 2005

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER******************************************************************/
#ifndef	BUILDFILESYSTEMDIC_H
#define	BUILDFILESYSTEMDIC_H

#ifndef bool
#define bool unsigned char
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

typedef struct _tagDict
{
	char *sWord;				// dictionary word
	char cHomo;					// homograph flag N - normal, P - primary, S - secondary
	char *sPron;				// pronunciation string
	unsigned int iBitFlags;		// bit flags
	unsigned int iPriority;		// priority numbers
} DICT;

typedef struct _tagBranch;
typedef struct _tagSymbol
{
	char cSym;
	struct _tagBranch *pNext;
	char *sData;

}SYMBOL;

// Branch structure using variable length pointers
typedef struct _tagBranch		
{
	int nSym;
	SYMBOL *pSyms;
}BRANCH;

void FreeDictionary(DICT *pDict, int nEntries);
void SortDictionary(DICT *pDict, int nEntries);

BRANCH *BuildLetterTree(DICT *pDict, int nEntries, bool bLowerCase);
void FreeLTree(BRANCH *pLTree);
int GetLTreeSize(BRANCH *pLTree);
int GetLTreeSizeWithoutData(BRANCH *pLTree);
unsigned int GetDataSizeInLTree(BRANCH *pLTree);
char *FindWordInLTree(char *sWord, BRANCH *pLTree);

void BuildFileSystemDict(char *sOutFile, BRANCH *pLTree, bool bBigEndian);

bool BuildGermanCompositeDict(char *sFileList, char *sOutFile, 
							  bool bTestDict, bool bLowerCase, bool bBigEndian);
bool BuildItalianCompositeDict(char *sFileList, char *sOutFile, 
							   bool bTestDict, bool bLowerCase, bool bBigEndian);

#endif
