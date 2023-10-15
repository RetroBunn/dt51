/*H_HEADER_FILE***************************************************************
FILE        : phonetic.h
DESC        : 
TABS        : 3
OWNER       : fonix
DATE CREATED: 

(C) Copyright 2000 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/
#ifndef  __PHONETIC_H__
#define  __PHONETIC_H__

//moved to port.h for each platform mlt
//#ifdef HAVE_STDIO_H
//#include <stdio.h>
//#elif defined OS_PALM
//#include "StdIOPalm.h"
//#endif
//#ifndef OS_PALM
//#include <stdlib.h>
//#endif
//#include <string.h>
//#include <ctype.h>
#include "port.h"

//#include "FnxPlatform.h"
#include "FnxLlist.h"

typedef char *PhoneticRule[ 4 ]; /* PhoneticRule is an array of 4 character pointers */

#define MAX_LINE  512
#define MAX_WORD  128

#if defined(__cplusplus)
extern "C" {
#endif

/* Context definitions */
extern const char Anything[];
extern const char Nothing[];

/* Phoneme definitions */
extern const char Pause[];
extern const char Silent[];

/* defines used with the graph2phon program */
//#define DEBUG_GRAPH2PHON

typedef struct _GRAPH2PHON
{
   PhoneticRule **ppPhoneticRules; // Array[#RuleSets][#RulesInSet][4] of strings with rule definitions
   char  *pRuleIndex;     // String containing one letter for each rule set, except for the punctuation rule.
   char  *sLetters;       // List of valid (i.e., handled) letters for this language
   char  *sNumbers;       // List of digits this letter handles
   char  *sVowels;        // List of vowel characters for this language
   char  *sVowels_f;      // List of "front vowels" for this language
   char  *sConsonants;    // List of consonants for this language
   char  *sConsonants_v;  // List of voiced consonants for this language
   char  *sNasals;        // List of nasals for this language
   char **psEndingsList; // Array of strings containing standard word endings for this languages
   SDWORD nEndingsList;    // Number of elements in psEndingsList[]
   char **psOutputList;  // Array of strings containing valid phonemes for this language's current description file.
   SDWORD nOutputList;     // Number of elements in psOutputList[]
   char **psSuffixList;  // Array of strings containing user-defined suffixes for this dictionary
   SDWORD nSuffixList;     // Number of elements in psSuffixList[] (usually 0).
   LinkPoolPtr pLinkPool;// Pool of linked list elements to use to avoid extra allocations.
} GRAPH2PHON, *Graph2PhonPtr;

// Prototypes for functions in Graph2Phon.c:
FNX_EXPORT( int, translate(Graph2PhonPtr pGraph2Phon, char *sWord, char *sPron));
FNX_EXPORT( int, SymbolsToString(llistPtr pSymbols, LinkPoolPtr pLinkPool, char *sWord));
FNX_EXPORT( void,   SurroundSymbols(llistPtr *ppList, char *sLeft, char *sRight, LinkPoolPtr pLinkPool));
FNX_EXPORT( BOOL,   HasDelimeter(char *s, BOOL bRight));

// Prototypes for functions in LoadRules.c:

   // text I/O:
//FNX_EXPORT( int,         LoadSuffixFile(char *sSuffixFile, char ***psSuffixList) );
FNX_EXPORT( Graph2PhonPtr, LoadRules(char *sFile) ); 
FNX_EXPORT( SDWORD,        WriteRules(char *sRulesFile, Graph2PhonPtr pGraph2Phon) );

   // binary I/O:
FNX_EXPORT( Graph2PhonPtr, LoadBinaryRules(FILE *fp) );
FNX_EXPORT( SDWORD,        WriteBinaryRules(FILE *fp, Graph2PhonPtr pGraph2Phon, BOOL bCompressRules) );

   // deallocation:
FNX_EXPORT( void,          FreeRules(Graph2PhonPtr pGraph2Phon) );

#if defined(__cplusplus)
}
#endif

#ifdef DEBUG_GRAPH2PHON
extern int **gppiRuleCount;
extern int giShowRules;
#endif

FNX_EXPORT( int, BSearch( char **psList, int iNumInList, char *sKey ));

#define HEADER_COUNT 10

//#define FOREIGNCHARSET "ÅåÄäÁáàêèëÉéîïìÍíîôöÓóÖÚúùÜüûçÇñÑÿñœŒß…@~-_" /* foreign language change */
//#define FOREIGNVOWELS "ÅåÄäÁáàêèëÉéîïìÍíîôöÓóÖÚúùÜüû" /* foreign language change */




#ifdef STAGE2
// Not used yet.  Eventually something like this could be used to allow more flexible symbol
//  usage in Graph2Phon rules...
//typedef struct
//{
//   char *sLeft;
//   char *sCenter;
//   char *sRight;
//   char *sOutput;
//} PhoneticRule, *PhoneticRulePtr; /* PhoneticRule is an array of 4 character pointers */

typedef struct
{
   char *sLetters; // Set of letters represented by this symbol (e.g,. "aeiouy")
   int  iMinCount; // Minimum number of letters in this set that must match
   int  iMaxCount; // Maximum number of letters that can match.  -1 => infinity.
   char cSymbol;   // Symbol used to represent this list (e.g., '#')
} SpecialSymbol, *SpecialSymbolPtr;

typedef struct _GRAPH2PHON
{
...
   char            *sSpecialSymbols;   //Array of special symbols, beginning with STANDARD_SYMBOLS, used to get the index of a special symbol.
   int              iNumSpecialSymbols;// Number of letters in sSpecialSymbols (=# strings in psSymbolLetters[])
   SpecialSymbolPtr *ppSpecialSymbols; // Array of structures containing information about each symbol.
...
} Graph2PhonT, *Graph2PhonPtr;

#endif // STAGE2

#endif
