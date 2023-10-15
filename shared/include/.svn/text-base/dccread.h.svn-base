/*H_HEADER_FILE***************************************************************
FILE        : dccread.h
DESC        : Types and function prototypes needed to read .dcc dictionary files.
TABS        : 3
OWNER       : Fonix
DATE CREATED: 

(C) Copyright 1999,2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/
#ifndef __DCCREAD_H
#define __DCCREAD_H

#include "phonetic.h"   // Graph2Phon definitions
#include "FnxHuffman.h" // HuffmanPtr definition

#define DCC_VER    112 // uses STAGE1 graph2phon rules, including header information.
// Version 111 did huffman compression and included graph2phon rules
// Version 110 was the original version.

typedef struct
{
   char sAlphaTriple[4];
   UDWORD ulOffset;
} AlphaTriple, *AlphaTriplePtr;

typedef struct
{
   FILE *pDccFile;           // pointer to the dcc file (NULL => not available, i.e., just use Graph2Phon)

   AlphaTriple *pAlphaTriple;// pointer to the alphaTriple table in memory
   HuffmanPtr   pPhoneHuffman; // Huffman table for decoding pronunciations
   HuffmanPtr   pSpellingHuffman;// Huffman table for decoding spellings (NULL=>words spelled out)
   UDWORD       ulWordEndOffset;   // Offset in file just after the end of the last word.
   UDWORD       ulTrailerOffset;   // Offset in file where the trailer ("END") begins.
   Graph2PhonPtr pGraph2Phon;
    char *pPhonemes;          // [version 110 only:] pointer to the table of phonemes
#ifdef BESTA
	long numWords;             // number of words in the dictionary
   long largestWord;          // length in #chars of longest word
   long largestPhonemeString; // longest pronunciation string of any word in dictionary (once decoded)
   long numAlphaTriples;      // number of alphaTriples in the alphaTriple table
   long numPhonemes;          // [version 110 only:] number of unique phonemes used by the word list
   long largestPhoneme;       // [version 110 only:] length in chars of longest phonemes
#else
   int numWords;             // number of words in the dictionary
   int largestWord;          // length in #chars of longest word
   int largestPhonemeString; // longest pronunciation string of any word in dictionary (once decoded)
   int numAlphaTriples;      // number of alphaTriples in the alphaTriple table
   int numPhonemes;          // [version 110 only:] number of unique phonemes used by the word list
   int largestPhoneme;       // [version 110 only:] length in chars of longest phonemes
#endif
} dccParams;

#define SIZE_DCCSTRUCT  sizeof( dccParams )
typedef dccParams  * DccPtr;

#if defined(__cplusplus)
extern "C" {
#endif

FNX_EXPORT( int,    initDccFile(char *sFilename, DccPtr *pDccInfo) );
FNX_EXPORT( int,    initDccFileW(wchar_t *wsFilename, DccPtr *ppDccInfo) );
FNX_EXPORT( int,    closeDccFile(DccPtr dccInfo) );
FNX_EXPORT( int,    decompWord(DccPtr dccInfo, char *word, char *pronunciation) );
FNX_EXPORT( char *, decompMultiWord(DccPtr pDccInfo, char *sString) );
FNX_EXPORT( char *, Pronunciation(DccPtr pDccInfo, char *sInWord, BOOL *pbGraph2Phon) );
FNX_EXPORT( SDWORD, MapCharacters(DccPtr pDccInfo, char *sWord) );

#if defined(__cplusplus)
}
#endif

#endif
