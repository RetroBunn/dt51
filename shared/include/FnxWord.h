/*H_HEADER_FILE***************************************************************
FILE        : word.h
DESC        : Word Graph Structure and functions
TABS        : 3
OWNER       : 
DATE CREATED: 29 April 1999

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/26/03 4:12p $
  $Revision: 7 $

*END_HEADER******************************************************************/
#ifndef WORD_H
#define WORD_H

#include "FnxPlatform.h"
#include "FnxNetwork.h"
#include "FnxDesc.h"

/*** NOTE: A wordT structure is now (as of 7/22/2002) allocated as a
     single block of memory that includes all of its nodes, prev/next
     indices, init/final indices, its name, and its nodes' names.
     So freeing or modifying any of its sub-pointers is highly dangerous.
     (But now wordT structures build faster, free much faster, and
     use less memory). ***/

/* Values for 'type' field of wstate: Types of nodes in a word pronunciation graph. */
enum {PH_ENTER, PH_EXIT, PH_INIT, PH_NORMAL, PH_FINAL, PH_INITFINAL};
/* Values for 'part' field of wstate:  Types of phone categories. */
enum {CONTEXT_INDEPENDENT, LEFT_DEPENDENT, RIGHT_DEPENDENT, TRIPHONE};

typedef struct
{
  SWORDPTR next;          /* Array of indices in the word's nodes[] array of following nodes */
  SWORDPTR prev;          /* Array of indices in the word's nodes[] array of preceding nodes */
  char  *phoneme;         /* Name of base phoneme for this node (e.g., "oU"),
                             (even if it represents a category like "$sil<oU") */
  SWORD mindur;           /* Min & max duration for this basephone or category */
  SWORD maxdur;           
  SWORD cat;              /* Index of this node's context-dependent phone category in the neural net outputs*/
  SWORD numnext;          /* Number of elements in next[] */
  SWORD numprev;          /* Number of elements in prev[] */
  SWORD tag;              /* index (cost nothing) due to aligment */

  char  part;             /* What kind of phone category: LEFT_DEPENDENT (e.g., $sil<oU),
                             RIGHT_DEPENDENT (e.g., oU>$sil), CONTEXT_INDEPENDENT (e.g., <oU>), 
                             TRIPHONE (e.g., $sil<oU>$den) */
  char  phone_len;        /* Number of bytes allocated for 'phoneme' */
  char  type;             /* Type of node: PH_ENTER/EXIT/INIT/NORMAL/FINAL/INITFINAL */
//  char  stress;           /* Stress level.  0=>default. Set in .vocab file by using 
//                             "<phoneme>#<stress>", e.g., "oU#2"*/
} wstateT, xhuge *wstateTPtr;
#define SIZE_WSTATET sizeof(wstateT)

typedef struct _WORDT
{
  wstateTPtr nodes;       /* Array of phoneme (or category) nodes in the word's pronunciation graph */
  SWORDPTR   initnodes;   /* Array of (numinit) indices into nodes[] of the initial nodes */
  SWORDPTR   finalnodes;  /* Array of (numfinal) indices into nodes[] of the final nodes */
  char       *name;       /* Name of the word (e.g., "seven") */

  SWORD      numnodes;    /* Number of nodes in 'nodes[]'             */
  SWORD      numinit;     /* Number of initial nodes in 'initnodes[]' */
  SWORD      numfinal;    /* Number of final nodes in 'finalnodes[]'  */
  SWORD      length;
} wordT, xhuge *wordTPtr;
#define SIZE_WORDT   sizeof(wordT)

#if defined(__cplusplus)
extern "C" {
#endif

FNX_EXPORT(wordTPtr,buildWord(char *sPronunciation, char *sWordName, DescPtr pDesc) );
wordTPtr buildWordFP(FILE *fp, char *sWordName, DescPtr pDesc, char *sFirstToken);
#define freeWord FreeWord
FNX_EXPORT(void, FreeWord(wordTPtr w) );
#define freeWords FreeWords
void FreeWords(wordTPtr *ppWordList, SDWORD iNumWords);
void printWord(wordTPtr w, DescPtr pDesc); 

#ifndef USE_SEARCH_GRAPH
SDWORD ExpandWord(DescPtr pDesc, NetworkPtr pNetwork);
#endif

void PrintPronun(wordTPtr w, SDWORD iNode, char *sPrefix, DescPtr pDesc,
                 char *sSeparator, BOOL bEnd, FILE *fp);
#if defined(__cplusplus)
}
#endif


#endif
