/*H_HEADER_FILE***************************************************************
FILE			: FileSystemDict.h
DESC			: 
TABS			: 3
OWNER			: 
DATE CREATED	: 

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER******************************************************************/
#ifndef	FILESYSTEMDICT_H
#define	FILESYSTEMDICT_H

#include "port.h"

#define MAX_SYMBOLS	0xFF

typedef struct _tagWordSegList
{
	char iLettersUsed;
	char iRule;
	int	 iPronOffset;
}WORD_SEG_LIST;

#ifdef _BIGENDIAN_
/* Seek method constants */

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

#define MAX_SYMBOLS	0xFF
#endif

typedef struct _tagFSSymbol		// File System Symbol structure 
{
	unsigned int iNext;
	unsigned int iData;
}FILESYS_SYMBOL;

// Bit Masks for the bit flag
#define FC_M_ADJ			0x00000001
#define FC_M_ADV			0x00000002
#define FC_M_ART			0x00000004
#define FC_M_AUX			0x00000008
#define FC_M_BE				0x00000010
#define FC_M_BEV			0x00000020
#define FC_M_CONJ			0x00000040
#define FC_M_ED				0x00000080
#define FC_M_HAVE			0x00000100
#define FC_M_ING			0x00000200
#define FC_M_NOUN			0x00000400
#define FC_M_POS			0x00000800
#define FC_M_PREP			0x00001000
#define FC_M_PRON			0x00002000
#define FC_M_SUBCONJ		0x00004000
#define FC_M_THAT			0x00008000
#define FC_M_TO				0x00010000
#define FC_M_VERB			0x00020000
#define FC_M_WHO			0x00040000
#define FC_M_NEG			0x00080000
#define FC_M_INTER			0x00100000
#define FC_M_REF			0x00200000
#define FC_M_PART			0x00400000
#define FC_M_FUNC			0x00800000
#define FC_M_CONT			0x01000000
#define FC_M_PRIMHOMO		0x02000000		// Used to identiry a primary homograph
#define FC_M_REFR			0x04000000
#define FC_M_UNKN			0x08000000
#define FC_M_NAME			0x10000000
#define FC_M_FC_MARKER		0x20000000
#define FC_M_CONTRACTION	0x40000000
#define FC_M_HOMOGRAPH		0x80000000		// Used to identify a homograph

extern int FindWordWithOffset(char *sWord, char *sPron, int *piBitFlag, 
#ifdef _BIGENDIAN_
							  char *sHomo, int *piHomoFlag, void *fp,
#else
							  char *sHomo, int *piHomoFlag, FILE *fp,
#endif							   
							  unsigned int offset);

// Try several permutations to find the word before giving up
extern int FindWord(char *sWord, char *sPron, int *piBitFlag, 
#ifdef _BIGENDIAN_
					char *sHomo, int *piHomoFlag, void *fp);
#else
					char *sHomo, int *piHomoFlag, FILE *fp);
#endif


// Find a word in a file system based dictionary
extern int FindWordInFileSystemDict(char *sWord, char *sPron, int *piBitFlag,
#ifdef _BIGENDIAN_ 
									char *sHomo, int *piHomoFlag, void *fp, 
#else
									char *sHomo, int *piHomoFlag, FILE *fp, 
#endif
									unsigned int offset);

// Find the pronunciation for a word or word fragment.
extern int FindWordSegsInFileSystemDict(char *sWord,
										char *sPron, int *piPronOffset, int *piBitFlag, 
										char *sHomo, int *piHomoFlag, 
										int *piLtrsUsed, unsigned int *puiInitOffset, 
#ifdef _BIGENDIAN_
										void *fp, unsigned int iDictOffset);
#else
										FILE *fp, unsigned int iDictOffset);
#endif

extern int FindAllWordSegments(char *sWord, WORD_SEG_LIST *pWordSegList, 
#ifdef _BIGENDIAN_
							   int nMaxWordSegs, void *fp, unsigned int iDictOffset);
#else
							   int nMaxWordSegs, FILE *fp, unsigned int iDictOffset);
#endif

#ifdef _BIGENDIAN_
extern int ReadPronData(void *fp, unsigned int offset,
#else
extern int ReadPronData(FILE *fp, unsigned int offset,
#endif 
						char *sPron, int nMaxPron, int *piData);

// Parse out the bit flag and then return the value of it
extern unsigned int GetBitFlag(char *sData);

// Find out if the primary pronunciation is a homograph.
// If it is then parse out the secondary pronunciation and return it.
extern char *GetHomograph(char *sData);

// Given a pronunciation data field, parse out the pronunciation
// and copy it to sPron.  Then get the bit flag and return it.
extern unsigned int ParsePronAndBitFlag(char *sData, char *sPron);


#endif
