/*H_HEADER_FILE***************************************************************
FILE        : desc.h
DESC        : 
TABS        : 3
OWNER       : 
DATE CREATED: 

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/26/03 4:12p $
  $Revision: 6 $

*END_HEADER******************************************************************/
#ifndef DESC_H
#define DESC_H

#include "FnxPlatform.h"
#include "FnxHash.h"


typedef struct
{
   char  *sContext;           // name of context
   SDWORD   iNumPhones;          // number of phones lumped together in this context
   char  **psPhones;          // array of names of the phones in this context
} CONTEXTNODE, xhuge *CONTEXTNODEPTR;

typedef struct
{
   char  *sCategory;          // name of category
   SDWORD   iMinDur;          // shortest possible duration (in frames) for this category
   SDWORD   iMaxDur;          // longest possible duration (in frames) for this category
} DURNODE, xhuge *DURNODEPTR;

typedef struct
{
   char  *sSource;            // one or more (delimited by white space) categories to tie to the source category (they are treated as the same output by the neural network
   char  *sTarget;            // name of category to use in place of one or more others (because they do not have enough training data
} TIENODE, xhuge *TIENODEPTR;

typedef struct
{
   char  *sSource;            // one or more (delimited by white space) phones to be replaced by the target phone
   char  *sTarget;            // name of phone to use to replace one or more others (because, for example, the others are not standard phone symbols)
} MAPNODE, xhuge *MAPNODEPTR;

typedef struct
{
   char  *sName;              /* Name of category */
   SDWORD   iMinDur;          /* Minimum duration of this category */
   SDWORD   iMaxDur;          /* Maximum duration of this category */
   SWORD iTie;             /* Index of category to tie to (-1 => not tied) */
   SWORD iBasephone;          /* Index of which basephone this category uses. */
} Category, xhuge *CategoryPtr;

/* Basephone information.  piLeft[0..nBasephones-1] has the index of
   which context-dependent phoneme category covers "LeftPhone<Basephone"
   or "$left<Basephone", where $left is a context that contains basephone LeftPhone. */
typedef struct
{
   char  *sName;              /* Name of basephone */
   SWORD *piLeft;          /* Array [iLeftPhone] of category index covering $iLeftPhone<basephone. 
                              NULL=>no left contexts. -1=>no category defined for that particular left phone.*/
   SWORD *piRight;            /* Array [iRightPhone]of category index covering basephone>$iRightPhone*/
   SWORD iCenter;          /* Index of category "<basephone>", or -1 if there is no center category for this basephone*/
   SWORD iNumTriphones;       /* Number of triphones for this basephone (0=>none, of course), i.e. size of piTriphone */
   SWORD *piTriphones;        /* Array of indices of triphone categories that have this basephone (NULL=>none) */
} Basephone, xhuge *BasephonePtr;

typedef struct
{
   /* Core information */
   SWORD       iNumCategories;         // Number of real categories to train on
   SWORD       iNumTotalCategories; // total number of categories, including <.garbage>, <.any> and tied categories 
   CategoryPtr    pCategories;         // Array of [iNumTotalCategories] category structures.
   SWORD       iNumBasephones;         // Number of basephone structures.
   BasephonePtr   pBasephones;         // Array of basephone structures.
   BOOL        bTriphone;           // Flag for whether there are triphones in this structure.
   H_HashTable    PhoneHash;           /* Hashing table to speed up retrieval of index of a base phone. 
                                    Mapped basephones return the same index as the phoneme they're mapped to.
                                    The returned value is the index into the pBasephone[] array.*/
   /* left/right context lists used in triphones only: */
   SWORDPTR    *ppiLeftContext;     /* Array [iNumCategories] of lists[#left] of base phone indices for triphone left context (terminated by -1) */
   SWORDPTR    *ppiRightContext;    /* Array [iNumCategories] of lists[#right] of base phone indices for triphone right context (terminated by -1) */
   /* Extra stuff only needed temporarily, unless you're going to write a description file back out. */
   /* Use TrimDesc() to deallocate these arrays after ReadDesc() if you're sure you don't need them. */
   SDWORD         iNumContexts;        // number of unique contexts   
   CONTEXTNODE    **ppContexts;        // the contexts (see CONTEXTNODE definition)
   SDWORD         iNumMappings;        // number of different mappings
   MAPNODE        **ppMappings;        // the mappings (see MAPNODE definition)
   SDWORD         iNumTies;            // number of different ties
   TIENODE        **ppTies;            // the ties (see TIENODE definition)
   SDWORD         iNumDurations;       // number of categories with duration information (should typically be the same as iNumTotalCategories)
   DURNODE        **ppDurations;       // the duration information (see DURNODE definition)
} Desc, xhuge *DescPtr;


#ifndef MAXBUF
#define MAXBUF 2048
#endif


#if defined(__cplusplus)
extern "C" {
#endif

/** Prototypes to functions in fileio.c */
/* String functions */
SDWORD   StringInList(char *sString, char *sList);
void     RemoveBackSlash(char *s);

/* Category functions */
void     SplitCategory(char *sCat, char *sLeft, char *sBase, char *sRight);

H_HashTable *BuildCategoryHashTable(DescPtr pDesc);
SWORD GetCategoryIndex(char *sCategory, H_HashTable *pCategoryHash);
void FreeCategoryHashTable(H_HashTable *pCategoryHash);

SDWORD   FindCategory(char **psCategory, SDWORD iNumCategories, char *sCategory);
char   **BuildPhoneList(char *psCategories[], SDWORD iNumCategories, SDWORD *piNumPhones);
SDWORD   FindContext(char *sContext, CONTEXTNODE **ppContexts, SDWORD iNumContexts);
SWORDPTR MakeContextList(char *sContext, DescPtr pDesc);
BOOL     SetDurations(DescPtr pDesc, BOOL *pbHasLeft, BOOL *pbHasCenter, BOOL *pbHasRight);

void     FreeMappings(MAPNODE **ppMappings, SDWORD iNumMappings);
void     FreeTies(TIENODE *ppTies[], SDWORD iNumTies);
void     FreeDurations(DURNODE *ppDurations[], SDWORD iNumDurations);
FNX_EXPORT(void, FreeDesc(DescPtr pDesc) );
void     FreeContexts(CONTEXTNODE **ppContexts, SDWORD iNumContexts);
void     FreeCategories(CategoryPtr pCategories, SWORD iNumCategories);

// Description functions
void     HashMappedBasephones(DescPtr pDesc, H_HashTable *pPhoneHash);
DescPtr  BuildDesc(char **psCategories, DescPtr pDesc);
DescPtr  ReadDesc(char *sDescFileName);
void     TrimDesc(DescPtr pDesc);
FNX_EXPORT(void,     CreateCategoryNames(DescPtr pDesc));
void     WriteDesc(char *sDescFileName, DescPtr pDesc);

DescPtr  ReadBinaryDescText(FILE *fp, UWORD uwVersionMajor, UWORD uwVersionMinor);
SDWORD   WriteBinaryDescText(FILE *fp, DescPtr pDesc, UWORD uwVersionMajor, UWORD uwVersionMinor);
DescPtr  ReadBinaryDescStruct(FILE *fp, UWORD uwVersionMajor, UWORD uwVersionMinor);
SDWORD   WriteBinaryDescStruct(FILE *fp, DescPtr pDesc, UWORD uwVersionMajor, UWORD uwVersionMinor);


void      FreeDesc(DescPtr pDesc);
MAPNODE **ReadMappings(char *sMapFile, SDWORD *piNumMaps);
FNX_EXPORT( char *, ReadEntireTextFile(char *sTextFile) );
void      FreeBasephones(BasephonePtr pBasephones, SWORD iNumBasephones);

#if defined(__cplusplus)
}
#endif

#endif
