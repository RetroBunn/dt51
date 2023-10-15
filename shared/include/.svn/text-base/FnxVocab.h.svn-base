/*H_HEADER_FILE***************************************************************
FILE        : FnxVocab.h
DESC        : 
TABS        : 3
OWNER       : Fonix
DATE CREATED: 

(C) Copyright 1999,2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/26/03 4:12p $
  $Revision: 4 $

*END_HEADER******************************************************************/
#ifndef  VOCABULARY_H
#define  VOCABULARY_H

#include "FnxPlatform.h"
#include "FnxDesc.h"
//#include "FnxMisc.h"
//#include "FnxLlist.h"
#include "FnxWord.h"


typedef struct _vocab
{
   SDWORD      iNumWords;        /* number of unique words in the vocabulary */
   wordTPtr *ppWords;         /* Array of pointers to (possibly expanded) wordT structures */
   SDWORD      iNumGrammarRules; /* number of grammar rule definitions.  0=>word-spotting mode, else finite state. */
   char     **psGrammar;      /* array of strings, where each string is a grammar rule */
   BOOL     bSorted;          /* flag for whether the vocabulary has been sorted or not. */
   BOOL     bBasephone;       /* flag to indicate that ppWords[] actually contains BASEPHONE
                              pronunciation graphs instead of expanded context-dependent ones. */
   BOOL     bManualPause;     /* flag to indicate that the vocabulary will put in any pauses it
                                 needs MANUALLY, instead of using automatic optional pauses between
                                 words (i.e., 0=>insert optional pauses; 1=>don't insert optional pauses) */
} VOCABULARY, xhuge *VocabTPtr;
#define SIZE_VOCABULARY sizeof(VOCABULARY)


#if defined(__cplusplus)
extern "C" {
#endif

SDWORD      InVocab(char *sWord, VocabTPtr pVocab);
SDWORD      GetVocabIndex(char *sWord, VocabTPtr pVocab);
#ifdef OS_WIN32
void __cdecl   SortVocab(VocabTPtr pVocab);
int __cdecl CmpWordT(const void *a, const void *b);
int __cdecl CaseCmpWordT(const void *a, const void *b);
#else
void     SortVocab(VocabTPtr pVocab);
int         CmpWordT(const void *a, const void *b);
int         CaseCmpWordT(const void *a, const void *b);
#endif
FNX_EXPORT( VocabTPtr,  ReadVocab(char *sVocabFileName, DescPtr pDesc) );
FNX_EXPORT(void,     FreeVocab(VocabTPtr pVocab) );
SDWORD      WriteVocab(VocabTPtr pVocab, char *sVocabFileName);
VocabTPtr   MakeVocab(char **psWordNames, char **psPronunciations, 
                     SDWORD iNumWords, char *sGrammar, DescPtr pDesc);
#if defined(__cplusplus)
}
#endif

#endif
