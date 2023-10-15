/*C_HEADER_FILE****************************************************************
FILE        :  BuildHuffman.c
DESC        :  Functions for creating a huffman-encoded binary dictionary file.
TABS        :  3
OWNER       :  Randy Wilson
DATE CREATED:  14 Sept 2001

(C) Copyright 2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/21/05 3:23p $
  $Revision: 32 $

*END_HEADER*******************************************************************/

#ifdef USE_WINDOWS
#include "use_windows.h"
#endif

#ifdef OS_PALM
#include "StdIOPalm.h"
#else
//#include <stdio.h>
#endif
#ifndef OS_PALM
#include <stdlib.h>
#endif
#include <math.h>
#include "FnxPlatform.h"
#include "FnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxNetwork.h"
#include "FnxNames.h"
#include "FnxDesc.h"
#include "FnxFileIO.h"
#include "FnxVocab.h"
//#include "SearchGraph.h"
#include "FnxPool.h"
#include "FnxByteOrderIO.h"
#include "FnxHuffman.h"
#include "FnxFiles.h"


/* Define DEBUG_HUFFMAN if you want various output throughout encoding process. */
//#define DEBUG_HUFFMAN
#ifdef DEBUG_HUFFMAN
/* Also define DUMP_ENCODING if you want a dump of the entire huffman table structure when finished */
//#define DUMP_ENCODING
#endif

#define MAX_PHONE_LEN 20
#define log2(x) (log10((double)(x))/log10(2.0))

extern void ShortenPronunciation(char **psPronunciation, LinkPoolPtr pLinkPool);
extern llistPtr CopyList(llistPtr pList, LinkPoolPtr pLinkPool);
extern char *SymbolsToString(llistPtr pSymbols, LinkPoolPtr pLinkPool);
extern char *GetPronunciation(wordTPtr pWord, llistPtr *ppSymbolList, LinkPoolPtr pLinkPool);

/*FUNCTION_HEADER**********************
   NAME:    ;HashMappedBasephones
   DESC:    Add "source" basephones of mappings into the basephone hash table.
   IN:      pDesc - Description structure to be updated
   OUT:     pDesc->PhoneHash has all of the "source" basephones of all of its mappings
              mapped to the index of their target basephones.
   RETURN:  n/a
   NOTES:   pDesc->PhoneHash must already have the real basephones in it.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
void HashMappedBasephones(DescPtr pDesc, H_HashTable *pPhoneHash)
{
   SDWORD iMap, iTarget, iSource;
   H_HashEntry *pHashEntry;
   char        *pcSource, sSource[MAX_PHONE_LEN]; /* Current position in source string of mapping */
   SDWORD       isnew;                             /* Flag that the hash stuff needs */
   
   /*** Add mapped phonemes to the hash table */
   for (iMap = 0; iMap < pDesc->iNumMappings; iMap++)
   {
      pHashEntry = H_FindHashEntry(pPhoneHash, pDesc->ppMappings[iMap]->sTarget);
      if (pHashEntry)
         iTarget = (SWORD)((SDWORD)H_GetHashValue(pHashEntry));
      else
      {
         Message(NULL, "Warning: Destination basephone '%s' of mapped phoneme(s) '%s' not found.\n",
            pDesc->ppMappings[iMap]->sTarget, pDesc->ppMappings[iMap]->sSource);
         continue;
      }
      /* Get the first source category. */
      pcSource = GrabField(sSource, pDesc->ppMappings[iMap]->sSource);
      while (sSource[0])
      {
         pHashEntry = H_FindHashEntry(pPhoneHash, sSource);
         if (pHashEntry)
         {
            /* Get the index of the basephone sSource is mapped to and
               make sure it is still mapped to the same one. */
            iSource = (SWORD)((SDWORD)H_GetHashValue(pHashEntry));
            if (iSource != iTarget)
            {
               Message(NULL, "Warning: Base phoneme '%s' maps to both '%s' and '%s'\n",
                  sSource, pDesc->pBasephones[iSource].sName, pDesc->pBasephones[iTarget].sName);
            }
         }
         else
         {
            /* This mapped phoneme not yet in the hash table, so add it. */
            pHashEntry = H_CreateHashEntry(pPhoneHash, sSource, &isnew);
            /* Set the ID to the index of the mapped basephone. */
            H_SetHashValue(pHashEntry, (char *)((SDWORD)iTarget));
            /* (Don't bother adding the mapped basephone to the list of basephones,
               since it shouldn't be needed later). */
         }  /* if found source */
         /* Get the next target in the pDesc->ppMappings[iMap]->sSource string (if any) */
         pcSource = GrabField(sSource, pcSource);
      }  /* while there are source categories */
   }  /* for iMap */
}  /* HashMappedBasephones */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;CmpNGramCount
 * DESC:    Compare two NGrams to see which should be first in a list of used NGrams.
 * IN:      pNGram1, pNGram2 - Two NGrams.
 * OUT:     n/a
 * RETURN:  -1 if pNGram1 < pNGram2; 0 if ==; 1 if pNGram1 > pNGram2
 * NOTES:   Compares NGrams' counts, and, if equal, their symbols, so that
            the list of active NGrams can be sorted starting with least frequent,
            and sorted by symbol index within same frequency.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
SDWORD CmpNGramCount(NGramNodePtr pNGram1, NGramNodePtr pNGram2)
{
   FNX_ASSERT(pNGram1 && pNGram2);
   if (pNGram1==pNGram2)
      return 0;
   if (pNGram1->iCount < pNGram2->iCount)
      return -1;
   if (pNGram1->iCount > pNGram2->iCount)
      return 1;
   if (pNGram1->wSymbol < pNGram2->wSymbol)
      return -1;
   if (pNGram1->wSymbol > pNGram2->wSymbol)
      return 1;
   return 0; /* Same count, same symbol.  This shouldn't happen in used NGrams */
}  /* CmpNGramCount */
#endif


/*** Opposite of CmpNGramCount, and usable by qsort() (i.e., sorts from largest
     count to smallest count) */
#ifndef FNX_LEAN_AND_MEAN
#ifdef OS_WIN32
int __cdecl CmpNGramCount2(const void *a, const void *b)
#else
int CmpNGramCount2(const void *a, const void *b)
#endif
{
   NGramNodePtr *ppA, *ppB;
   ppA = (NGramNodePtr *)a;
   ppB = (NGramNodePtr *)b;
   return -CmpNGramCount(*ppA, *ppB);
}
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;SwapNGrams
 * DESC:    Swap two NGrams in an array of NGram pointers.
 * IN:      ppNGrams - Array of pointers to NGrams
            iPosition1, iPosition2 - Position in ppNGrams[] of the two NGrams to be swapped.
 * OUT:     ppNGrams[iPosition1] and ppNGrams[iPosition2] are swapped,
              and the two NGrams' ->iPosition field is set to their new locations.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
void SwapNGrams(NGramNodePtr *ppNGrams, SDWORD iPosition1, SDWORD iPosition2)
{
   NGramNodePtr pTemp;
   if (iPosition1==iPosition2)
      return; /* Don't bother swapping if they're the same NGram. */
   pTemp = ppNGrams[iPosition1];
   ppNGrams[iPosition1] = ppNGrams[iPosition2];
   ppNGrams[iPosition1]->iPosition = iPosition1;
   ppNGrams[iPosition2] = pTemp;
   ppNGrams[iPosition2]->iPosition = iPosition2;
}  /* SwapNGrams */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;CheckNGramTree
 * DESC:    Make sure an NGram tree is not broken.
 * IN:      pNGramTree - Tree to check.
 * OUT:     n/a
 * RETURN:  -1 if there is a problem.  0 if OK.
 * NOTES:   Checks to make sure that every node's list of children all point to it as a parent,
            that the sum of a node's children's "iCount" field is equal to its iCount field,
            etc.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
SDWORD CheckNGramTree(NGramTreePtr  pNGramTree)
{
   SDWORD i, j, iSum;
   NGramNodePtr pNGram, pChild;
   char *sHasParent; /* Array of characters containing an 'x' if the corresponding node
                 is in its parent's list of children, or an 0x00 (null character) otherwise. */
   /* Allocate sHasParent to have one more character than there are NGrams.  That way,
      if all of the NGrams get an "x", then strlen(sHasParent)=iNumNGrams, and there's a 
      zero at the end to terminate the "string" */
   sHasParent = (char *)FNX_CALLOC(pNGramTree->iNumNGrams + 1, sizeof(char));
   
   for (i=0; i<pNGramTree->iNumNGrams; i++)
   {
      pNGram = pNGramTree->ppNGrams[i];
      /* All NGrams should know where they are in the list */
      FNX_ASSERT((SDWORD)pNGram->iPosition == i); 
      /* No empty symbols should be left in the main list */
      FNX_ASSERT(pNGram->iCount>0); 
      /* Make sure only the first iNumUsed NGrams don't have parents */
      if (i<pNGramTree->iNumUsed)
      {
         /* This is a top-level symbol.  Make sure it doesn't have a parent */
         FNX_ASSERT(pNGram->pParent==NULL);
         sHasParent[i]='x'; /* No parent, so doesn't need to be in its parent's list of children. */
         /* Make sure its symbol points to it */
         FNX_ASSERT(pNGramTree->ppSymbolNGrams[pNGram->wSymbol] == pNGram);
         /* Make sure the symbols in ppNGrams[] are sorted by iCount OR by bit length (in reverse order)*/
         FNX_ASSERT(i==0 || pNGramTree->ppNGrams[i-1]->iCount <= pNGramTree->ppNGrams[i]->iCount ||
                pNGramTree->ppNGrams[i-1]->wBitLength >= pNGramTree->ppNGrams[i]->wBitLength);
      }
      else /* Not a top-level symbol */
      {
         FNX_ASSERT(pNGram->pParent);
      }
      /* Make sure all of an NGram's children point to it */
      iSum=0;
      for (pChild=pNGram->pChildren; pChild; pChild=pChild->pNext)
      {
         FNX_ASSERT(pChild->pParent==pNGram);
         sHasParent[pChild->iPosition] = 'x';
         iSum += pChild->iCount;
      }
      /* Make sure that the counts of the children sum up to the NGram's count */
      FNX_ASSERT(iSum == pNGram->iCount || pNGram->pChildren==NULL);
   }
   for (i=pNGramTree->iNumNGrams; i< pNGramTree->iTotalNGrams; i++)
   {
      FNX_ASSERT(pNGramTree->ppNGrams[i]->iCount==0);
   }
   /* Make sure all nodes have a parent (that should have one) */
   FNX_ASSERT((SDWORD)FNX_STRLEN(sHasParent) == pNGramTree->iNumNGrams);

   /* Make sure all of the symbols are where they belong, i.e., any
      symbols whose NGram has dropped to a count of 0 should have been
      moved out of the list of symbols. */
   iSum=0; /* Count number of unused symbols */
   for (i=0; i<pNGramTree->wNumSymbols; i++)
   {
      if (pNGramTree->ppSymbolNGrams[i]->iCount>0)
         FNX_ASSERT(pNGramTree->ppSymbolNGrams[i]->iPosition < pNGramTree->iNumUsed);
      else 
      {
         iSum++;
         FNX_ASSERT(pNGramTree->ppSymbolNGrams[i]->iPosition >= pNGramTree->iNumNGrams);
      }
   }
   FNX_ASSERT(pNGramTree->wNumSymbols - iSum == pNGramTree->iNumUsed);
   
   /* Make sure the supersymbols all point to things less than themselves */
   for (i=pNGramTree->wNumLiterals; i < pNGramTree->wNumSymbols; i++)
   {
      FNX_ASSERT(pNGramTree->ppwNGrams[i-pNGramTree->wNumLiterals]);
      for (j=1; j<=pNGramTree->ppwNGrams[i-pNGramTree->wNumLiterals][0]; j++)
         FNX_ASSERT(pNGramTree->ppwNGrams[i-pNGramTree->wNumLiterals][j] < i); 
   }
   return 0; /* ok */
}  /* CheckNGramTree */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;SortNGramsByCount
 * DESC:    Sort the "potential" NGrams by count (from largest to smallest)
 * IN:      pNGramTree - Tree to sort
 * OUT:     pNGramTree->ppNGrams[pNGramTree->iNumUsed..pNGramTree->iNumPotential-1]
              are sorted by count.
 * RETURN:  Index (in pNGramTree->ppNGrams[]) of where the symbols with counts no
              greater than 1 begin.
 * NOTES:   A qsort() took over 5 minutes on 500,000 NGrams, so I wrote this routine,
              which takes less than a second on the same data.  It does the sort
              in O(3N+2M) time, where N=#NGrams (iNumPotential-iNumUsed), and
              M=100 (#bins).
            Can use pNGramTree->iNumPotential = SortNGramsByCount(pNGramTree) in order
              to avoid having to check any singleton NGrams.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
SDWORD SortNGramsByCount(NGramTreePtr pNGramTree)
{
   SDWORD piCount[101]; /* Number of NGrams with iCount=0..99, and #>=100 */
   SDWORD piStart[101]; /* Position in array where NGrams with given count start */
   SDWORD iBin, iNGram, iCount, iIndex;
   SDWORD iCount100;    /* Copy of piCount[100] */
   NGramNodePtr *ppNGrams;

#ifdef USE_WINDOWS
   int cnt = 0;
   SetupProgressIndicator( g_hDlg, pNGramTree->iNumPotential );
   SetDlgItemText( g_hDlg, IDC_STATIC_PROGRESS, (LPCTSTR)"Sorting NGrams by count..." );
#endif

   ppNGrams = pNGramTree->ppNGrams;

   /* Initialize 'piCount[]' to all 0 */
   for (iBin=0; iBin<=100; iBin++)
      piCount[iBin]=0;
   /* Count how many NGrams there are with counts of 0..99, and how many have counts >= 100 */
   for (iNGram=pNGramTree->iNumUsed; iNGram < pNGramTree->iNumPotential; iNGram++)
   {
#ifdef USE_WINDOWS
      MoveProgressIndicator( g_hDlg, &cnt );
#endif
      if (ppNGrams[iNGram]->iCount < 100)
         piCount[ppNGrams[iNGram]->iCount]++;
      else piCount[100]++; /* Lump all large counts together */
   }
   /* Figure out where NGrams of each count will start in the sorted array
      (Start at 'iNumUsed', since the first iNumUsed NGrams are already
      sorted at the beginning.  Put the NGrams in there from largest count to smallest.
      All NGrams with count>=100 go in first bin and will be qsort-ed below.) */
   piStart[100]=pNGramTree->iNumUsed;
   for (iBin=99; iBin>=0; iBin--)
      piStart[iBin] = piStart[iBin+1] + piCount[iBin+1];
   iCount100 = piCount[100];
   /* Now actually move each NGram into the 'bin' where it goes */
   /* For each bin, continually swap all NGrams out of that bin into
      the bin it belongs in, until the one it swaps with belongs in
      the current bin.  Continue until the only thing left in the bin
      is NGrams that belong there (for empty bins, that means move on immediately).
      At the end, anything not in the first 100 bins (count=0..99)
      will be left in the "long" bin, where we will do a qsort
      on the much-reduced number of popular NGrams there.  This operation
      causes each NGram to be moved at most twice. */
   for (iBin=0; iBin<100; iBin++)
   {
      while (piCount[iBin]>0)
      {
         iIndex = piStart[iBin]+piCount[iBin]-1;
         iCount = ppNGrams[iIndex]->iCount;
         if (iCount==iBin)
            piCount[iBin]--;
         else
         {
            if (iCount>=100)
               iCount=100;
            SwapNGrams(ppNGrams, iIndex, piStart[iCount]+(--piCount[iCount]));
         }
      }
   }  /* for iBin */
   /* Do a qsort on the (much smaller) group of NGrams with count>=100 */
   qsort(&pNGramTree->ppNGrams[pNGramTree->iNumUsed], iCount100, sizeof(NGramNode *), CmpNGramCount2);
   /* Set the position of the qsort-ed NGrams */
   for (iNGram=pNGramTree->iNumUsed; iNGram < pNGramTree->iNumUsed + iCount100; iNGram++)
      ppNGrams[iNGram]->iPosition = iNGram;
   /* Return the index in pNGramTree->ppNGrams[] where the NGrams with count <=1 begin. */
   return piStart[1];
}  /* SortNGramsByCount */
#endif


#ifdef DEBUG_HUFFMAN
/* Dump the index and either name of a symbol, or recursively
   the index and names of the symbols the NGram is made up of. */
void DumpSymbolName(NGramTreePtr pNGramTree, SWORD wSymbol)
{
   SWORD w, *pwNGramDef;

   if (wSymbol < pNGramTree->wNumLiterals)
      //printf("%d:%s", (SDWORD)wSymbol,pNGramTree->psSymbolNames[wSymbol]);
      printf("%s", pNGramTree->psSymbolNames[wSymbol]);
   else /* This is an NGram, so print its sub-symbols */
   {
      //printf("%d:<",(SDWORD)wSymbol);
      //printf("<");
      pwNGramDef = pNGramTree->ppwNGrams[wSymbol - pNGramTree->wNumLiterals];
      for (w=1; w <= pwNGramDef[0]; w++)
      {
         DumpSymbolName(pNGramTree, pwNGramDef[w]);
         if (w<pwNGramDef[0])
            printf(" ");
      }
      //printf(">");
      printf(" ");
   }
}  /* DumpSymbolName */

void DumpNGramName(NGramTreePtr pNGramTree, NGramNodePtr pNGram)
{
   if (pNGram->pParent)
   {
      DumpNGramName(pNGramTree, pNGram->pParent);
      printf(", ");
   }
   DumpSymbolName(pNGramTree, pNGram->wSymbol);
}

void DumpNGramTree(NGramTreePtr pNGramTree)
{
   SDWORD i, iRow, iRows, iColumn, iColumns, iIndex, iChildren;
   NGramNodePtr pNGram, pChild;

   printf("%d phones + %d delimeters = %d literals. (end symbol=%d(%s))\n", (SDWORD)pNGramTree->wNumPhones,
      (SDWORD)pNGramTree->wNumDelim, (SDWORD)pNGramTree->wNumLiterals, (SDWORD)pNGramTree->wEndSymbol,
      pNGramTree->psSymbolNames[pNGramTree->wEndSymbol]);
   
   for (i=0; i<pNGramTree->iNumPotential; i++)
      FNX_ASSERT(pNGramTree->ppNGrams[i]->iPosition == i);

   /* Print the names of the literal symbols */
   iColumns=4;
   iRows = 1+(pNGramTree->wNumLiterals-1)/iColumns;
   for (iRow=0; iRow<iRows; iRow++)
   {
      for (iColumn=0; iColumn<iColumns; iColumn++)
      {
         iIndex = iRow+iRows*iColumn;
         if (iIndex < pNGramTree->wNumLiterals)
            printf("  %2d) %-8s", iIndex, pNGramTree->psSymbolNames[iIndex]);
      }
      printf("\n");
   }
   /* Print NGram array (excluding non-potential ones). */
   for (i=0; i<pNGramTree->iTotalNGrams && i<2000; i++)
   {
      if (i==0)
         printf("NGram List:\n  Current symbols:\n");
      if (i==pNGramTree->iNumUsed)
         printf("  Need to be checked (potential):\n");
      if (i==pNGramTree->iNumPotential)
         printf("  Ruled out (NGrams that don't help):\n");
      if (i==pNGramTree->iNumNGrams)
         printf("  Deleted (count==0):\n");
      pNGram = pNGramTree->ppNGrams[i];
      FNX_ASSERT(pNGram->iPosition == i);
      printf("    %3d) cnt:%4d, len:%3d", i, pNGram->iCount, (SDWORD)pNGram->wBitLength);
      printf(", par:%6d, children: ",pNGram->pParent ? pNGram->pParent->iPosition : -1);
      iChildren=0;
      for (pChild=pNGram->pChildren; pChild; pChild=pChild->pNext)
      {
         printf("%d%s", pChild->iPosition, pChild->pNext?", " : "");
         iChildren++;
      }
      printf("=%3d, ", iChildren);
      if (pNGram->pParent)
      {
         printf("NGram:  ");
         DumpNGramName(pNGramTree, pNGram);
      }
      else 
      {
         printf("Symbol: ");
         DumpSymbolName(pNGramTree, pNGram->wSymbol);
      }
      printf("\n");
   }

   CheckNGramTree(pNGramTree);
   printf("\n");
}  /* DumpNGramTree */

/*FUNCTION_HEADER**********************
 * NAME:    ;DumpHSymbolName
 * DESC:    Print the name of a symbol (or NGram) in a Huffman structure.
 * IN:      pHuffman - Structure with info on symbol names and NGram definitions
            wSymbol  - Index of symbol to print out.
 * OUT:     Name of symbol (or definition of NGram) dumped to screen.
 * RETURN:  n/a
 * NOTES:   Calls itself recursively to expand NGrams.
 *END_HEADER***************************/
void DumpHSymbolName(HuffmanPtr pHuffman, SWORD wSymbol)
{
   if (wSymbol < pHuffman->wNumLiterals)
      printf("%s", pHuffman->psLiterals[wSymbol]);
   else
   {
      SWORD wIndex;
      SWORD *pwNGramDef;
      //printf("<");
      pwNGramDef = pHuffman->ppwNGrams[wSymbol-pHuffman->wNumLiterals];
      for (wIndex=1; wIndex <= pwNGramDef[0]; wIndex++)
      {
         DumpHSymbolName(pHuffman, pwNGramDef[wIndex]);
         if (wIndex < pwNGramDef[0])
            printf(" ");
      }
      //printf(">");
      printf(" ");
   }
}  /* DumpHSymbolName */

/* Print a 32-bit word in binary */
void DumpBits(UDWORD uiPattern)
{
   SDWORD i;
   for (i=0; i<32; i++)
   {
      if (uiPattern & 0x80000000)
         printf("1");
      else printf("0");
      if ((i+1)%8==0 && i<31)
         printf("_");
      uiPattern <<= 1;
   }
}

/*FUNCTION_HEADER**********************
 * NAME:    ;DumpHuffman
 * DESC:    Dump the contents of a Huffman structure to stdout.
 * IN:      pHuffman - Structure to dump
 * OUT:     Contents of pHuffman dumped to screen.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
void DumpHuffman(HuffmanPtr pHuffman)
{
   SWORD w, wSymbol;
   printf("Huffman table.\n");
   printf("  %d symbols (%d literals; end symbol=%d '", (SDWORD)pHuffman->wNumSymbols, 
          (SDWORD)pHuffman->wNumLiterals, (SDWORD)pHuffman->wEndSymbol);
   DumpHSymbolName(pHuffman, pHuffman->wEndSymbol);
   printf("'). Max code length=%d bits\n", (SDWORD)pHuffman->cMaxCodeLength);

   if (pHuffman->psCodeStrings == NULL)
      BuildHuffmanCodeStrings(pHuffman);
   printf("--All %d symbols:\n", pHuffman->wNumSymbols);
   for (w=0; w<pHuffman->wNumSymbols; w++)
   {
      printf("    %3d) %2d bits: %-*s ", w, pHuffman->pcCodeLengths[w], (SDWORD)pHuffman->cMaxCodeLength,
         pHuffman->psCodeStrings[w] ? pHuffman->psCodeStrings[w] : "-");
      DumpHSymbolName(pHuffman, w);
      printf("\n");
   }

   printf("\n");
   printf("--Used %d symbols (in canonical order):\n", pHuffman->wNumUsed);
   for (w=0; w<pHuffman->wNumUsed; w++)
   {
      wSymbol = pHuffman->pwSymbolIndices[w];
      printf("    %3d->%3d) %2d bits: %-*s ", w, wSymbol, pHuffman->pcCodeLengths[wSymbol], (SDWORD)pHuffman->cMaxCodeLength,
         pHuffman->psCodeStrings[wSymbol] ? pHuffman->psCodeStrings[wSymbol] : "-");
      DumpHSymbolName(pHuffman, wSymbol);
      printf("\n");
   }
   printf("--%d Tables:\n", pHuffman->iNumTables);
   for (w=0; w<pHuffman->iNumTables; w++)
   {
      printf("    %2d) First=%3d; CodeLen=%2d; Start=", w, pHuffman->pTables[w].uiFirstSymbol,
         pHuffman->pTables[w].uiCodeLength);
      DumpBits(pHuffman->pTables[w].uiStart);
      printf("; Mask=");
      DumpBits(pHuffman->pTables[w].uiPatternMask);
      printf("\n");
   }
}  /* DumpHuffman */

#endif

/*FUNCTION_HEADER*******************
 * NAME:    ;FreePointerList
 * DESC:    Free a linked list and the things it points to.
 * IN:      ppLink - Address of head of list to free
            pLinkPool  - Pool of links to return links to (NULL=>FNX_FREE() individually)
 * OUT:     The pointers in the entire list are freed, entire list is freed up, and *ppLink is set to NULL.
 * RETURN:  n/a
 * NOTES:   If pLinkPool is NULL then the links are individually freed using FNX_FREE().
            Otherwise, the links are returned to the free list of pLinkPool.
            In any case, all the things pointed to by the links are freed using FNX_FREE().
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
void FreePointerList(llistPtr *ppLink, LinkPoolPtr pLinkPool)
{
   llistPtr pNext;

   if (pLinkPool)
   {
      while (*ppLink)
      {
         /* Remove the first link in the list and return it to pLinkPool's free list. */
         if ((*ppLink)->p)
            FNX_FREE((*ppLink)->p);
         /* (*ppLink is advanced to the next link in the list) */
         RemoveLink(ppLink, pLinkPool);
      }
   }
   else /* No pool of links, so deallocate each one. */
   {
      while(*ppLink)
      {
         if ((*ppLink)->p)
            FNX_FREE((*ppLink)->p);
         pNext = (*ppLink)->pNext;
         FNX_FREE(*ppLink);
         *ppLink=pNext;
      }
   }
}  /* FreePointerList */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;CalculateCodeLengths
 * DESC:    Calculated the number of bits needed for each symbol in a Canonical Huffman encoding
 * IN:      piArray[]    - Array containing the sorted (non-decreasing) symbol frequencies (counts),
                          into which the bit length of each symbol will be placed.
            iNumSymbols - Number of symbols (i.e., entries in pCodeLengths[])
 * OUT:     piArray[0..iNumSymbols-1] contains the number of bits needed for each symbol.
 * RETURN:  Maximum number of bits needed for any symbol (=piArray[iNumSymbols-1]), or -1 on error.
 * NOTES:   Thanks to Alistair Moffat, alistair@cs.mu.oz.au and Jyrki Katajainen, jyrki@diku.dk
            for sharing this code.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
SDWORD CalculateCodeLengths(SDWORD piArray[], SDWORD iNumSymbols) 
{
   SDWORD root;        /* next root node to be used */
   SDWORD leaf;        /* next leaf to be used */
   SDWORD next;        /* next value to be assigned */
   SDWORD avbl;        /* number of available nodes */
   SDWORD used;        /* number of internal nodes */
   SDWORD dpth;        /* current depth of leaves */

   /* Check for pathological cases */
   if (piArray==NULL)
      return -1; /* Error */
   if (iNumSymbols==0) 
      return 0; /* No symbols => no bits needed at all */
   if (iNumSymbols==1) 
   {
      piArray[0] = 0; /* Only one symbol => no bits needed to know which one it is */
      return 0; 
   }

   /* Make sure first element is not 0.  A 0 => never occured => shouldn't be in the list */
   FNX_ASSERT(piArray[0]!=0);

   /* First pass, left to right, setting parent pointers */
   /* (drw - At each point, 'leaf' is the index in piArray[] of the
      next leaf node to use, and piArray[leaf] is its frequency;
      'root' is the index in piArray[] of the root of the tree so far,
      and piArray[root] has the sum of all leaf nodes below it.
      All piArray[0..root-1] contain INDICES in piArray[] of their 'parent' node.
      'next' is the index in piArray[] of where the next sum goes. */
   /* At the end of this loop, piArray[0..iNumSymbols-3] contain indices of their
      parent nodes, piArray[iNumSymbols-2] contains the sum of all of the frequencies,
      and piArray[iNumSymbols-1] has leftover info. */
   piArray[0] += piArray[1]; 
   root = 0; 
   leaf = 2;
   for (next=1; next < iNumSymbols-1; next++) 
   {
      /* select first item for a pairing */
      if (leaf>=iNumSymbols || piArray[root]<piArray[leaf])
      {
         piArray[next] = piArray[root]; 
         piArray[root++] = next;
      }
      else
         piArray[next] = piArray[leaf++];

      /* add on the second item */
      if (leaf>=iNumSymbols || (root<next && piArray[root]<piArray[leaf]))
      {
         piArray[next] += piArray[root]; 
         piArray[root++] = next;
      }
      else
         piArray[next] += piArray[leaf++];
   }
   
   /* second pass, right to left, setting internal depths */
   /* drw - In this pass, piArray[iNumSymbols-2] is 0 (since it was the root),
      and all elements piArray[0..iNumSymbols-3] are set to their depth in the tree. */
   piArray[iNumSymbols-2] = 0;
   for (next=iNumSymbols-3; next>=0; next--)
      piArray[next] = piArray[piArray[next]]+1;

   /* third pass, right to left, setting leaf depths */
   avbl = 1; 
   used = dpth = 0; 
   root = iNumSymbols-2; 
   next = iNumSymbols-1;
   while (avbl>0) 
   {
      while (root>=0 && piArray[root]==dpth) 
      {
         used++; 
         root--;
      }
      while (avbl>used) 
      {
         piArray[next--] = dpth; 
         avbl--;
      }
      avbl = 2*used; 
      dpth++; 
      used = 0;
   }
   return dpth;
}  /* CalculateCodeLengths */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;FreeNGramTree
 * DESC:    Free up an NGramTree and all its structures.
 * IN:      pNGramTree - Structure to be freed.
 * OUT:     pNGramTree and all its structures are freed.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
void FreeNGramTree(NGramTreePtr pNGramTree)
{
   if (pNGramTree)
   {
#ifdef USE_WINDOWS
      SetupProgressIndicator( g_hDlg, 1000 );
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
      if (pNGramTree->psSymbolNames)
         FreePointerArray((char **)pNGramTree->psSymbolNames, pNGramTree->wNumLiterals);
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
      if (pNGramTree->pFirstLevel)
         FNX_FREE(pNGramTree->pFirstLevel);
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
      if (pNGramTree->pSymbolHash)
      {
         H_DeleteHashTable(pNGramTree->pSymbolHash);
         FNX_FREE(pNGramTree->pSymbolHash);
      }
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
      if (pNGramTree->pwSymbolMap)
         FNX_FREE(pNGramTree->pwSymbolMap);
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
      if (pNGramTree->ppNGrams)
         FNX_FREE(pNGramTree->ppNGrams);
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
      if (pNGramTree->ppwNGrams)
         FreePointerArray((char **)pNGramTree->ppwNGrams, pNGramTree->wNumSymbols - pNGramTree->wNumLiterals);
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
      if (pNGramTree->ppSymbolNGrams)
         FNX_FREE(pNGramTree->ppSymbolNGrams);
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
      FreePool(pNGramTree->pNGramPool);
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
      FreeLinkPool(pNGramTree->pLinkPool);
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
      FNX_FREE(pNGramTree);
   }
}  /* FreeNGramTree */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;InitNGrams
 * DESC:    Initialize a structure to hold NGram information
 * IN:      psPhones - Array of strings containing the names of the phonemes.
            iNumPhones - Number of names in psPhones[]
            sDelimeters - String containing delimeter characters (e.g., "()[]{}|")
            cEndOfString - End of string character (e.g., ";");
            bNeedSpaces  - Flag indicating whether phonemes need to be separated by spaces
 * OUT:     An NGramTree structure is built, and its fields are all initialized.
 * RETURN:  Pointer to the new NGramTree structure.
 * NOTES:   Delimeters are assumed to NOT need spaces on either side of them.
            Upon decoding, two adjacent elements from psPhones[] will be separated
              by a space iff bNeedSpaces is TRUE.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
NGramTreePtr InitNGrams(char **psPhones, SDWORD iNumPhones, char *sDelimeters, char cEndOfString, BOOL bNeedSpaces)
{
   SDWORD isnew;
   SWORD w, wSymbol;
   NGramTreePtr pNGramTree;
   H_HashEntry *pHashEntry;
   char sDelim[2];
   
   /* Allocate structure and calculate number of symbols */
   pNGramTree = (NGramTreePtr) FNX_CALLOC(1, sizeof(NGramTree));
   pNGramTree->wNumPhones   = (SWORD)iNumPhones;
   if (sDelimeters && sDelimeters[0])
      pNGramTree->wNumDelim    = (SWORD)FNX_STRLEN(sDelimeters) + 1;
   else pNGramTree->wNumDelim = 1; /* End of string */
   pNGramTree->wNumLiterals = pNGramTree->wNumPhones + pNGramTree->wNumDelim;
   pNGramTree->wNumSymbols  = pNGramTree->wNumLiterals;  /* Since no higher-level NGrams have been selected yet */
   pNGramTree->bNeedSpaces  = bNeedSpaces;

   /* Allocate the first level of NGram nodes */
   pNGramTree->pFirstLevel = (NGramNodePtr) FNX_CALLOC(pNGramTree->wNumLiterals, sizeof(NGramNode));

   /* Allocate and fill the array of symbol names */
   pNGramTree->psSymbolNames = (unsigned char **)FNX_CALLOC(pNGramTree->wNumLiterals, sizeof(char *));
   for (w=wSymbol=0; w < (SWORD)iNumPhones; w++)
      pNGramTree->psSymbolNames[wSymbol++] = (unsigned char *)FNX_STRDUP(psPhones[w]);
   sDelim[1]=0x00;
   for (w=0; w < pNGramTree->wNumDelim - 1; w++)
   {
      sDelim[0]=sDelimeters[w];
      pNGramTree->psSymbolNames[wSymbol++] = (unsigned char *)FNX_STRDUP(sDelim);
   }
   sDelim[0]=cEndOfString;
   pNGramTree->wEndSymbol = wSymbol;
   pNGramTree->psSymbolNames[wSymbol++] = (unsigned char *)FNX_STRDUP(sDelim);
   
   /* Build a hash table to look up each symbol name */
   pNGramTree->pSymbolHash = (H_HashTable *)FNX_CALLOC(1,sizeof(H_HashTable));
   H_InitHashTable(pNGramTree->pSymbolHash, H_STRING_KEYS);
   /* Add all of the categories to the hash table (including <.garbage> and <.any>) */
   for (wSymbol=0; wSymbol < pNGramTree->wNumLiterals; wSymbol++)
   {
      if (pNGramTree->psSymbolNames[wSymbol][0]) /* Don't try to hash "\0": Doesn't work. */
      {
         pHashEntry = H_CreateHashEntry(pNGramTree->pSymbolHash, (char *)pNGramTree->psSymbolNames[wSymbol], &isnew);
         FNX_ASSERT(isnew); // Shouldn't have two phones with the same names */
         H_SetHashValue(pHashEntry, (char *)(SDWORD)wSymbol); /* Remember index of symbol (stored as a char *) */
      }
      pNGramTree->pFirstLevel[wSymbol].wSymbol = wSymbol;
   }  /* for wSymbol */

   /* Set the maximum NGram length.  This should eventually be a parameter,
      but so far there are still bugs in how it works if there is a limit
      to the NGram size, so we'll just use "unlimited" as the size, and
      you'd better just hope you have enough memory.  */
   pNGramTree->iMaxNGramLength = 0; // => no limit

   /* Initialize pools */
   pNGramTree->pNGramPool = NewPool(100, sizeof(NGramNode));
   pNGramTree->pLinkPool  = NewLinkPool(200);
   return pNGramTree;
}  /* InitNGrams */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;AddNGrams
 * DESC:    Add NGrams to an NGram tree.
 * IN:      pNGramTree - NGram tree (which has already been initialized and possibly partially filled)
            pwSymbols - Array of (indices of) symbols to be added to the NGram tree
            iNumIndices - Number of symbols in pwSymbols[]
 * OUT:     pNGramTree has all of the NGrams in pwSymbols[] added to the tree (or counters incremented,
              when some are already there).
 * RETURN:  n/a
 * NOTES:   e.g., if "aba;" (index 5, 7, 5, 13 15) comes in, then the NGrams
              "a", "ab", "aba", "aba;",  "b", "ba", "ba;",  "a" (again), "a;",  and ";" are added
              to the NGram tree.
            If pwSymbols[] does not end with the end symbol (i.e., pNGramTree->wEndSymbol),
              then the array is treated as though wEndSymbol was appended to the end of the array.
              (e.g., if ';' was the end symbol, then "aba" and "aba;" would do the same thing).
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
void AddNGrams(NGramTreePtr pNGramTree, SWORD *pwSymbols, SDWORD iNumIndices)
{
   SDWORD iStart;  /* Position in pwSymbols[] of the first symbol of the current NGram */
   SDWORD iCurrent;/* Position in pwSymbols[] of the last symbol of the current NGram */
   NGramNodePtr pNGram, pChild, pNewNode, *ppPrev;
   SWORD  wSymbol;
   SDWORD iMaxNGramDepth;
   
   if (pNGramTree==NULL || pwSymbols==NULL || iNumIndices<=0)
      return;

   /* Store NGrams up to twice as long as the ones we want to end up with so that
      we have the necessary context needed to know whether sub-NGrams need to
      be decremented. */
   if (pNGramTree->iMaxNGramLength > 0)
      iMaxNGramDepth = pNGramTree->iMaxNGramLength*2-1;
   else iMaxNGramDepth=0; /* => infinite */

   /* Use "<=" in case last symbol is not the end symbol */
   for (iStart=0; iStart<=iNumIndices; iStart++)
   {
      if (iStart==iNumIndices)
      {
         if (pwSymbols[iNumIndices-1]==pNGramTree->wEndSymbol)
            break; /* Don't bother: We already had an end symbol */
         wSymbol = pNGramTree->wEndSymbol;
      }
      else wSymbol = pwSymbols[iStart];

      /* Add all NGrams beginning at pwSymbols[iStart] to the tree */
      if (wSymbol<0 || wSymbol >= pNGramTree->wNumLiterals)
      {
         Message(FNX_STDERR,"Error: Symbol index (%d) out of bounds in AddNGrams\n", (SDWORD)pwSymbols[iStart]);
         return;
      }
      pNGram = &(pNGramTree->pFirstLevel[wSymbol]);
      
      /* Increment counters (and add nodes if not yet there) for all NGrams
         pwSymbols[iStart..iCurrent] as iCurrent goes from iStart to iNumIndices-1.
         Also, let iCurrent=iNumIndices if the last element in pwSymbols[] is not
         the end-of-string symbol (thus the "<="). */
      for (iCurrent=iStart; iCurrent<=iNumIndices && pNGram && 
           (iMaxNGramDepth==0 || iCurrent-iStart<iMaxNGramDepth); iCurrent++)
      {
         FNX_ASSERT((iCurrent == iNumIndices && pNGram->wSymbol == pNGramTree->wEndSymbol)
                     || pNGram->wSymbol == pwSymbols[iCurrent]);
         pNGram->iCount++;
         if (pNGram->wSymbol == pNGramTree->wEndSymbol) // This is the End-of-string symbol, so stop.
            pNGram=NULL; // terminate loop.
         /* Not the end-of-string symbol, so move on to all following symbols */
         else if (iMaxNGramDepth==0 || (iCurrent-iStart) + 1 < iMaxNGramDepth)
         {
            FNX_ASSERT(iCurrent < iNumIndices); // if ==, should have been the end-of-string symbol done the 'if' above.
            if (iCurrent == iNumIndices-1) //There is no End-of-string symbol, so add one anyway.
               wSymbol = pNGramTree->wEndSymbol;
            else wSymbol = pwSymbols[iCurrent+1];
            /* Look to see if wSymbol already exists as a child node of pNGram */
            ppPrev = &pNGram->pChildren; /* Start with ppPrev=head of list */
            /* Search linked list until a match is found, 
               or until we go beyond where a match SHOULD have been found */
            while ((pChild=*ppPrev)!=NULL && pChild->wSymbol < wSymbol)
               ppPrev = &(pChild->pNext);
            if (pChild==NULL || pChild->wSymbol > wSymbol)
            {
               /* There isn't a child node with wSymbol, so insert it in the place where it goes */
               pNewNode = GetFromPool(pNGramTree->pNGramPool);
               /* Turn the pointer of the parent to its child, and the pointer of the child towards its parent (Malachi 4)*/
               pNewNode->pParent = pNGram; /* Point the new child back at its parent */
               pNewNode->pNext   = pChild; /* whether NULL or not */
               *ppPrev           = pNewNode; /* whether ppNode is the parent's 'pChildren' pointer, or a siblings 'pNext' pointer */
               pNewNode->wSymbol = wSymbol;
               pNewNode->iCount  = 0; /* This will get incremented during the next pass through the 'for' loop */
               pNGram            = pNewNode; /* Advance pNGram to the N+1-gram */
            }
            else pNGram = pChild; /* Advance pNGram to the N+1-gram */
         }  /* else not end-of-string */
      }  /* for iCurrent */
   }  /* for iStart */
}  /* AddNGrams */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;ReadWord
 * DESC:    Read a word from a vocab file.
 * IN:      sWord     - string into which the name of the word should be put.
            psPronunciation - Address into which the pronunciation will be put (NULL=>don't return it).
            sKey      - Buffer into which "ReadField" will read symbols. Contains first symbol (i.e., start of word name)
            ppList    - Address in which to return a linked list of the symbols in the pronunciation (NULL=>don't bother)
            pLinkPool - Pool of links to use.
            fp - File to read from.
 * OUT:     sWord[] is filled with the name of the word.
            *psPronunciation points to a newly-allocated string containing the (shortened) pronunciation (unless NULL)
            sKey has ';' in it (unless EOF was hit)
            *ppList has a linked list of symbols in it (unless NULL)
            pLinkPool is probably a bit modified
            fp is advanced past the ending ';' of the pronunciation
 * RETURN:  0 on success, -1 on error (like fp ending before ';' found)
 * NOTES:   *ppList has a linked list of newly-allocated strings, so the strings
               will need to be freed up with the list is.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
static SDWORD ReadWord(char *sWord, char **psPronunciation, char *sKey, llistPtr *ppList, LinkPoolPtr pLinkPool, FILE *fp)
{
   BOOL bDone;
   llistPtr pSymbolList, pOldCopy, pLink;
   char *sPronunciation, *sNewPronunciation;
   llistPtr pNewCopy;
   wordTPtr pWord;

   /* Copy sKey into the temporary word name */
   FNX_STRCPY(sWord, sKey);
   /* Append any other strings before '{' or '(' to sWord to handle
      words with spaces in them (like "Los Angeles"), and skip the
      '(' or '{'. */
   bDone = FALSE;
   do
   {
      if (!ReadField(sKey, "{(;", fp) || sKey[0] == ';')
         bDone = TRUE; /* Hit end-of-file or end of word, so we'll skip all the next loop, too. */
      else if (!FNX_STRSTR("{(;", sKey))
      {
         FNX_STRCAT(sWord, " ");
         FNX_STRCAT(sWord, sKey);
      }
   } while (!bDone && !FNX_STRSTR("{(;", sKey));

   if (bDone)
   {
      Message(FNX_STDERR, "Warning: No pronunciations for word '%s'\n", sWord);
      return -1; /* error */
   }

   /* Assume there is one extraneous "(" or "{" at the beginning and end of the pronunciation.
      Skip first token and read others until ";" is found. */
   pSymbolList=NULL;
   do
   {
      /* Add this symbol to the linked list of symbols for this pronunciation */
      InsertLink(FNX_STRDUP(sKey), &pSymbolList, pLinkPool);
      if (!ReadField(sKey, "(){}[]|;", fp) || sKey[0] == ';')
         bDone = TRUE; /* Hit end-of-file or end of word, so we'll skip all the next loop, too. */
   } while (!bDone);
   
   if (sKey[0] != ';')
   {
      Message(FNX_STDERR, "Warning: No ';' at the end of pronunciation of word '%s'\n", sWord);
      return -1; /* error */
   }
   /* Make a copy of the list, since SymbolsToString frees up the list */
   pOldCopy = CopyList(pSymbolList, pLinkPool);

   /* Convert the linked list of phonemes and delimeters into a string (and free up 'pSymbols') */
   sPronunciation = SymbolsToString(pSymbolList, pLinkPool);

   /* Build a word structure with a collapsed pronunciation graph */
   pWord = buildWord(sPronunciation, "word", NULL);
   
   /* Convert the collapsed pronunciation graph into a (hopefully shorter) string */
   sNewPronunciation = GetPronunciation(pWord, &pNewCopy, pLinkPool);

   if (ListSize(pNewCopy) < ListSize(pOldCopy))
   {
      /* new pronunciation is shorter, so free up the old one */
      FreePointerList(&pOldCopy, pLinkPool);
      FNX_FREE(sPronunciation);
      sPronunciation = sNewPronunciation;
      if (ppList)
      {
         *ppList = pNewCopy;
         /* pNewCopy's links point at strings within pWord, so allocate a copy of 
            each string so we won't break when we free up pWord. */
         for (pLink=*ppList; pLink; pLink=pLink->pNext)
            pLink->p = (void *)FNX_STRDUP((char *)pLink->p);
      }
      else FreeList(&pNewCopy, pLinkPool);
   }
   else /* original string was at least as short, so free up new string and its list */
   {
      FreeList(&pNewCopy, pLinkPool);
      FNX_FREE(sNewPronunciation);
      if (ppList)
         *ppList = pOldCopy;
      else FreePointerList(&pOldCopy, pLinkPool);
   }
   freeWord(pWord);
   if (psPronunciation)
      *psPronunciation = sPronunciation;
   else FNX_FREE(sPronunciation);
   return 0; /* ok */
}  /* ReadWord */
#endif


/*FUNCTION_HEADER**********************
 * NAME:   ;GetVocabPhonemes
 * DESC:   Get a list of base phonemes from a vocabulary.
 * IN:     pVocab - Vocabulary to get phonemes from
           piNumPhonemes - Address in which to return the number of base phonemes.
 * OUT:    *piNumPhonemes contains the number of base phonemes.
 * RETURN: Array of unique base phoneme names.
 * NOTES:  
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
char **GetVocabPhonemes(VocabTPtr pVocab, SDWORDPTR piNumPhonemes)
{
   H_HashTable PhonemeHash;
   H_HashEntry *pHashEntry;
   SDWORD iNumPhones, iWord, iNode;
   wordTPtr pWord;
   SDWORD isnew;
   char **psPhones;
   llistPtr pPhoneList=NULL; /* Linked list of unique phoneme names */

   H_InitHashTable(&PhonemeHash, H_STRING_KEYS);
   iNumPhones=0;
   for (iWord=0; iWord < pVocab->iNumWords; iWord++)
   {
      pWord = pVocab->ppWords[iWord];
      for (iNode=0; iNode<pWord->numnodes; iNode++)
      {
         /* See if the phoneme is already in the hash table */
         pHashEntry = H_FindHashEntry(&PhonemeHash, pWord->nodes[iNode].phoneme);
         if (pHashEntry==NULL)
         {
            /* This phoneme is not yet in the hash table, so add it,
               and let its index be its return value.  Also add the
               name of the phoneme to the linked list. */
            pHashEntry = H_CreateHashEntry(&PhonemeHash, pWord->nodes[iNode].phoneme, &isnew);
            H_SetHashValue(pHashEntry, (char *)(SDWORD)iNumPhones++); /* Remember index of duration (stored as a char *) */
            InsertLink(FNX_STRDUP(pWord->nodes[iNode].phoneme), &pPhoneList, NULL);
         }
      }  /* for each node */
   }  /* for each word */

   if (iNumPhones==0)
      psPhones = NULL;
   else psPhones = ListToArray(&pPhoneList, iNumPhones, NULL);

   /* Free up the phoneme hash table built above */
   H_DeleteHashTable(&PhonemeHash);

   *piNumPhonemes = iNumPhones;
   return psPhones;
}  /* GetVocabPhonemes */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;BuildVocabNGrams
 * DESC:    Build a tree of NGrams from a vocab structure (and optionally a tokenized vocab structure)
 * IN:      pVocab - Vocabulary structure
            ppTokenVocab - Address in which to put a pointer to the tokenized vocabulary (NULL=>don't create one)
 * OUT:     An NGram tree is built, and ppTokenVocab, if not NULL, points to a new tokenized vocabulary.
 * RETURN:  Pointer to the new NGram tree.
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
NGramTreePtr BuildVocabNGrams(VocabTPtr pVocab, TokenVocabPtr *ppTokenVocab)
{
#ifdef USE_WINDOWS
   int cnt = 0;
#endif
   NGramTreePtr pNGramTree;
   char **psPhones, *sPronunciation;
   llistPtr pSymbolList;
   SDWORD iNumIndices, iSymbolPos, iIndexPos;
   H_HashEntry *pHashEntry;
   char **psSymbols;
   SWORD *pwSymbols, wSymbolIndex;
   llistPtr pTokenWords=NULL;
   TokenWordPtr pTokenWord;
   SDWORD   iNumPhones, iWord;
   wordTPtr pWord;
#ifdef BUILD_DCC_PROJECT
   SDWORD iLastLen=1; // Length of last word name
#endif

   if (pVocab==NULL)
      return NULL;

   if (ppTokenVocab)
      *ppTokenVocab = (TokenVocabPtr) FNX_CALLOC(1, sizeof(TokenVocab));

   /* Get a list of the unique phonemes occuring in the vocabulary */
   psPhones = GetVocabPhonemes(pVocab, &iNumPhones);

   pNGramTree = InitNGrams(psPhones, iNumPhones, "()[]{}|", ';', TRUE/*need spaces between phones*/);

   FreePointerArray(psPhones, iNumPhones);

#ifdef USE_WINDOWS
   SetupProgressIndicator( g_hDlg, pVocab->iNumWords );
#endif
   /* Get the pronunciation symbols for each word, and add them to the NGram tree. */
   for (iWord=0; iWord < pVocab->iNumWords; iWord++)
   {
#ifdef USE_WINDOWS
   MoveProgressIndicator( g_hDlg, &cnt );
#endif
      pWord = pVocab->ppWords[iWord];
#ifdef BUILD_DCC_PROJECT
      if (iWord==pVocab->iNumWords-1 || iWord%100==0)
         printf("  %d/%d: %-*s\r", iWord+1, pVocab->iNumWords, iLastLen, pWord->name);
      iLastLen = FNX_STRLEN(pWord->name);
#endif
      pSymbolList=NULL;
      sPronunciation = GetPronunciation(pWord, &pSymbolList, pNGramTree->pLinkPool);
      if (sPronunciation)
         FNX_FREE(sPronunciation); // don't actually need complete string, just symbol list.

      /* Convert the list of tokens to an array of symbol indices */
      iNumIndices = ListSize(pSymbolList);
      FNX_ASSERT(iNumIndices>0);
      psSymbols   = ListToArray(&pSymbolList, iNumIndices, pNGramTree->pLinkPool);
      pwSymbols   = (SWORD *)FNX_CALLOC(iNumIndices-1, sizeof(SWORD));
      
      /* There are "()" around the pronunciation, but no ';' at the end,
         so skip initial "(" (or "{") and replace final one with ';' */
      if (psSymbols[0][0]!='(' && psSymbols[0][0]!='{')
      {
         Message(FNX_STDERR,"Warning: No opening '(' or '{' on pronunciation for word %s (skipping word)\n", pWord->name);
         FNX_FREE(psSymbols);
         FNX_FREE(pwSymbols);
         continue; /* Skip this word */
      }
      else iSymbolPos=1; /* Skip first symbol */
      
      /* Get the index of each symbol */
      iIndexPos=0;
      while (iSymbolPos<iNumIndices)
      {
         if (iSymbolPos==iNumIndices-1) /* Last symbol */
         {
            if (psSymbols[iSymbolPos][0]!=')' && psSymbols[iSymbolPos][0]!='}')
            {
               Message(FNX_STDERR,"Warning: No closing ')' or '}' on pronununciation for word %s (skipping word)\n", pWord->name);
               break; /* break out of while loop */
            }
            wSymbolIndex = pNGramTree->wEndSymbol;
         }
         else /* Not 'end' symbol, so look the phoneme or delimeter up */
         {
            pHashEntry = H_FindHashEntry(pNGramTree->pSymbolHash, psSymbols[iSymbolPos]);
            if (pHashEntry)
               wSymbolIndex = (SWORD)((SDWORD)H_GetHashValue(pHashEntry));
            else wSymbolIndex = -1;
         }
         if (wSymbolIndex<0 || wSymbolIndex >= pNGramTree->wNumLiterals)
            Message(FNX_STDERR,"Error: Unknown symbol '%s' in pronunciation of word '%s' (skipping, but that's bad!)\n", psSymbols[iSymbolPos], pWord->name);
         else pwSymbols[iIndexPos++] = wSymbolIndex;
         iSymbolPos++;
      }
      FNX_FREE(psSymbols);
      if (iSymbolPos<iNumIndices)
         continue; /* Error, so skip this word (warning: memory leak) */
      /* Update the NGrams with this string of tokens */
      FNX_ASSERT(iIndexPos==iNumIndices-1);
      AddNGrams(pNGramTree, pwSymbols, iIndexPos);
      if (ppTokenVocab)
      {
         /* Create a tokenized word to go in the tokenized vocab */
         pTokenWord = (TokenWordPtr)FNX_MALLOC(sizeof(TokenWord));
         pTokenWord->sWord = FNX_STRDUP(pWord->name);
         pTokenWord->wNumIndices = (SWORD)iIndexPos;
         pTokenWord->pwSymbolIndices = pwSymbols;
         /* Insert the tokenized word into the linked list of them. */
         InsertLink(pTokenWord, &pTokenWords, pNGramTree->pLinkPool);
         (*ppTokenVocab)->iNumWords++;
      }
      else FNX_FREE(pwSymbols);
   }  /* for each word */

   if (ppTokenVocab)
   {
      /* Convert the linked list of tokenized words into an array of pointers */
      (*ppTokenVocab)->ppTokenWords = (TokenWordPtr *)ListToArray(&pTokenWords, (*ppTokenVocab)->iNumWords, pNGramTree->pLinkPool);
   }

   return pNGramTree;
}  /* InitVocabNGrams */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;BuildFileVocabNGrams
 * DESC:    Read a vocab file and build a tree of NGrams from it (and optionally a tokenized vocab structure)
 * IN:      sVocabFile - Vocabulary file
            pDesc      - Description structure with names of base phonemes
            ppTokenVocab - Address in which to put a pointer to the tokenized vocabulary (NULL=>don't create one)
 * OUT:     An NGram tree is built, and ppTokenVocab, if not NULL, points to a new tokenized vocabulary.
 * RETURN:  Pointer to the new NGram tree.
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
NGramTreePtr BuildFileVocabNGrams(char *sVocabFileName, DescPtr pDesc, TokenVocabPtr *ppTokenVocab)
{
   FILE *fp;
   NGramTreePtr pNGramTree;
   char sValue[MAXBUF], sKey[MAXBUF], sWord[MAXBUF], sComment[MAXBUF];
   char **psPhones, *sPronunciation;
   llistPtr pSymbolList;
   SDWORD i, iNumIndices, iSymbolPos, iIndexPos;
   H_HashEntry *pHashEntry;
   char **psSymbols;
   SWORD *pwSymbols, wSymbolIndex;
   llistPtr pTokenWords=NULL;
   TokenWordPtr pTokenWord;
   SDWORD   iNumWords;
   
   if (ppTokenVocab)
      *ppTokenVocab = (TokenVocabPtr) FNX_CALLOC(1, sizeof(TokenVocab));

   /* Create an empty NGram tree */
   psPhones = (char **)FNX_CALLOC(pDesc->iNumBasephones, sizeof(char *));
   for (i=0; i<pDesc->iNumBasephones; i++)
      psPhones[i] = pDesc->pBasephones[i].sName;
   pNGramTree = InitNGrams(psPhones, pDesc->iNumBasephones, "()[]{}|", ';', TRUE);
   /* Add mapped phonemes to the ngram's hash table (so they will return the same index as the
      phone to which they are mapped). */
   HashMappedBasephones(pDesc, pNGramTree->pSymbolHash);
   FNX_FREE(psPhones);

   /* Now read through the vocab file one word at a time, building NGram information */
   fp = FNX_FOPEN((const char *)sVocabFileName, "r");
   if (!fp)
   {
      Message(FNX_STDERR, "Error opening vocab file %s in ReadVocab()\n", sVocabFileName);
      return NULL;
   }
   iNumWords=0;
   /* Read & handle each vocabulary word or grammar rule */
   while (ReadField(sKey, "=({;#", fp))
   {
      if (!sKey[0])
         continue; /* Skip comments and empty lines (which shouldn't happen) */
      if (sKey[0] == '#')
      {
         FNX_FGETS(sComment,MAXBUF,fp);
         continue;
      }
      if (sKey[0] == '$')
      {
         /** Grammar rule: Skip [will we want to include these at some point?]. */
         while (ReadField(sValue, ";", fp) && sValue[0] != ';')
            ;
      }
      else /* Vocabulary word */
      {
         /* Read a word and its pronunciation up to the ending ';' from fp. 
            Get the name of the word in 'sWord', the pronunciation string in 'sPronunciation',
            and the list of symbols in the pronunciation string in 'pSymbolList' */
         pSymbolList=NULL;
         if (ReadWord(sWord, &sPronunciation, sKey, &pSymbolList, pNGramTree->pLinkPool, fp)!=0)
            return NULL; /* hit end of file in the middle of a word */
#ifdef DEBUG_HUFFMAN
         if ((iNumWords++)%10==0)
            printf("%s       \r", sWord);
#endif
         /* Convert the list of tokens to an array of symbol indices */
         iNumIndices = ListSize(pSymbolList);
         FNX_ASSERT(iNumIndices>0);
         psSymbols   = ListToArray(&pSymbolList, iNumIndices, pNGramTree->pLinkPool);
         pwSymbols   = (SWORD *)FNX_CALLOC(iNumIndices-1, sizeof(SWORD));
         /* There are "()" around the pronunciation, but no ';' at the end,
            so skip initial "(" (or "{") and replace final one with ';' */
         if (psSymbols[0][0]!='(' && psSymbols[0][0]!='{')
         {
            Message(FNX_STDERR,"Warning: No opening '(' or '{' on pronunciation for word %s (skipping word)\n", sWord);
            continue; /* Skip this word (warning: memory leak) */
         }
         else iSymbolPos=1; /* Skip first symbol */
         iIndexPos=0;
         while (iSymbolPos<iNumIndices)
         {
            if (iSymbolPos==iNumIndices-1) /* Last symbol */
            {
               if (psSymbols[iSymbolPos][0]!=')' && psSymbols[iSymbolPos][0]!='}')
               {
                  Message(FNX_STDERR,"Warning: No closing ')' or '}' on pronununciation for word %s (skipping word)\n", sWord);
                  break; /* break out of while loop */
               }
               /* Replace final ")" or "}" with ";" to signal the end-of-string */
               psSymbols[iSymbolPos][0]=';';
               psSymbols[iSymbolPos][1]=0x00;
            }
            pHashEntry = H_FindHashEntry(pNGramTree->pSymbolHash, psSymbols[iSymbolPos]);
            if (pHashEntry)
               wSymbolIndex = (SWORD)((SDWORD)H_GetHashValue(pHashEntry));
            else wSymbolIndex = -1;
            if (wSymbolIndex<0 || wSymbolIndex >= pNGramTree->wNumLiterals)
               Message(FNX_STDERR,"Error: Unknown symbol '%s' in pronunciation of word '%s' (skipping, but that's bad!)\n", psSymbols[i], sWord);
            else pwSymbols[iIndexPos++] = wSymbolIndex;
            iSymbolPos++;
         }
         if (iSymbolPos<iNumIndices)
            continue; /* Error, so skip this word (warning: memory leak) */
         /* Update the NGrams with this string of tokens */
         FNX_ASSERT(iIndexPos==iNumIndices-1);
         AddNGrams(pNGramTree, pwSymbols, iIndexPos);
         if (ppTokenVocab)
         {
            /* Create a tokenized word to go in the tokenized vocab */
            pTokenWord = (TokenWordPtr)FNX_MALLOC(sizeof(TokenWord));
            pTokenWord->sWord = FNX_STRDUP(sWord);
            pTokenWord->wNumIndices = (SWORD)iIndexPos;
            pTokenWord->pwSymbolIndices = pwSymbols;
            /* Insert the tokenized word into the linked list of them. */
            InsertLink(pTokenWord, &pTokenWords, pNGramTree->pLinkPool);
            (*ppTokenVocab)->iNumWords++;
         }
      }  /* else this is a word */
   }  /* while not end of file */
   FNX_FCLOSE(fp);

   if (ppTokenVocab)
   {
      /* Convert the linked list of tokenized words into an array of pointers */
      (*ppTokenVocab)->ppTokenWords = (TokenWordPtr *)ListToArray(&pTokenWords, (*ppTokenVocab)->iNumWords, pNGramTree->pLinkPool);
   }

   return pNGramTree;
}  /* BuildFileVocabNGrams */
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadSymbolList
 * DESC:    Read a text file and return a list of its whitespace-separated words.
 * IN:      sFilename - Filename of a .txt file.
            piNumWords - Address in which to return the number of words in the text file.
 * OUT:     An array of *piNumWords pointers is allocated, each of which points
              to a newly-allocated string containing one word from the text file.  Also,
              the number of words in the array is put into *piNumWords.
 * RETURN:  Pointer to the array of word strings.
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
char **ReadSymbolList(char *sFilename, SDWORD *piNumWords)
{
   FILE *fp;
   LLIST *pWordList;
   char **psWords = NULL, *sWord, sBuf[MAXBUF];
   SDWORD iNumWords;

   fp = FNX_FOPEN(sFilename, "r");
   if (!fp)
   {
      Message(FNX_STDERR,"Couldn't open '%s' for reading in ReadTxt.\n", sFilename);
      *piNumWords = 0;
      return NULL;
   }

   iNumWords=0;
   pWordList=NULL;
   
   /* Grab the next word */
   while (ReadField(sBuf,"",fp))
   {
     sWord = FNX_STRDUP(sBuf);
     InsertLink(sWord, &pWordList, NULL);
     iNumWords++;
   }
   FNX_FCLOSE(fp);

   if (iNumWords > 0)
      psWords = ListToArray(&pWordList, iNumWords, NULL);
   else psWords = NULL;

   *piNumWords = iNumWords;

   return psWords;
}  /* ReadSymbolList */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;ExtractTTSSymbols
 * DESC:    Split a TTS pronunciation string up into its individual symbols and get their indices.
 * IN:      sPronunciation - String containing TTS pronunciation (like "02Dbri%tn'/" for "britain").
            pSymbolHash    - Hash table for looking up each symbol.
            pLinkPool      - Pool of links to use.
 * OUT:     A linked list of symbol indices is allocated.
 * RETURN:  Pointer to the new linked list of symbol indices.
 * NOTES:   Assumes that TTS symbols are either 1- or 2-characters each.
            Assumes that if a 2-character symbol matches, then it should be used
              (e.g., if "rau%" is encountered, the "au" is treated as a symbol
              rather than as "a" or "u", since "a", "u", and "au" are all symbols.)
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
llistPtr ExtractTTSSymbols(char *sPronunciation, H_HashTable *pSymbolHash, LinkPoolPtr pLinkPool)
{
   char *pc; /* Current position in sPronunciation */
   char sSymbol[3];
   SDWORD iSymbolIndex;
   llistPtr pList=NULL;
   H_HashEntry *pHashEntry;

   sSymbol[2]=0; /* Permanetly null-terminate the string of length 2. */

   for (pc=sPronunciation; *pc; pc++)
   {
      /* Make a string of length 2, consisting of the current symbol and the
         next one, to see if it matches any of the symbols. */
      sSymbol[0]=*pc;
      sSymbol[1]=*(pc+1); /* (May be the null char if *pc is the last character) */
      pHashEntry = H_FindHashEntry(pSymbolHash, sSymbol);
      if (pHashEntry)
      {
         iSymbolIndex = (SDWORD)H_GetHashValue(pHashEntry);
         if (sSymbol[1]) /* If this is the last character, then pc+1 may be the null terminator, and we don't want to skip that */
            pc++; /* Skip an extra character, since we used two */
      }
      else
      {
         /* No symbol of length 2 matches the string, so try just the first character */
         sSymbol[1]=0; /* Null terminate after the first character */
         pHashEntry = H_FindHashEntry(pSymbolHash, sSymbol);
         if (pHashEntry)
            iSymbolIndex = (SDWORD)H_GetHashValue(pHashEntry);
         else
         {
            Message(NULL,"Error: Undefined symbol '%s' in pronunciation", sSymbol);
            return NULL;
         }
      }
      InsertLink((voidPtr)iSymbolIndex, &pList, pLinkPool);
   }
   return pList;
}  /* ExtractTTSSymbols */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;BuildTTSNGrams
 * DESC:    Read a TTS vocab file and build a tree of NGrams from it (and optionally a tokenized vocab structure)
 * IN:      sVocabFile - Vocabulary file
            pDesc      - Description structure with names of base phonemes
            ppTokenVocab - Address in which to put a pointer to the tokenized vocabulary (NULL=>don't create one)
 * OUT:     An NGram tree is built, and ppTokenVocab, if not NULL, points to a new tokenized vocabulary.
 * RETURN:  Pointer to the new NGram tree.
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
NGramTreePtr BuildTTSNGrams(char *sVocabFileName, char **psSymbols, SDWORD iNumSymbols, TokenVocabPtr *ppTokenVocab)
{
   FILE *fp;
   NGramTreePtr pNGramTree;
   char sLine[MAXBUF], sWord[MAXBUF];
   char *sPronunciation;
   llistPtr pSymbolList;
   SDWORD i, iNumIndices, iSymbolPos;
   SWORD  *pwSymbols;
   SDWORD *piSymbols;
   llistPtr pTokenWords=NULL;
   TokenWordPtr pTokenWord;
   SDWORD   iNumWords;
   char *pc;
   
   sWord[0]=0;
   if (ppTokenVocab)
      *ppTokenVocab = (TokenVocabPtr) FNX_CALLOC(1, sizeof(TokenVocab));

   /* Create an empty NGram tree */
   pNGramTree = InitNGrams(psSymbols, iNumSymbols, "", ';', FALSE);

   /* Now read through the vocab file one word at a time, building NGram information */
   fp = FNX_FOPEN((const char *)sVocabFileName, "r");
   if (!fp)
   {
      Message(FNX_STDERR, "Error opening vocab file %s in ReadVocab()\n", sVocabFileName);
      return NULL;
   }
   iNumWords=0;
   /* Read & handle each vocabulary word or grammar rule */
   while (FNX_FGETS(sLine, MAXBUF, fp))
   {
      Strip(sLine);
      if (!sLine[0])
         continue; /* Skip empty lines */

      for (i=0, pc=sLine; *pc && *pc!='\t'; pc++)
         sWord[i++]=*pc;
      sWord[i]=0;
      Strip(sWord);
      if (*pc!='\t')
         Message(NULL,"Error: No tab in TTS dictionary entry:\n  %s\n", sLine);
      /* Skip the tab and any additional whitespace after the tab */
      while (*pc>0 && *pc<=' ')
         pc++;
      sPronunciation = pc;

      /* Extract a list of symbol indices from the pronunciation */
      pSymbolList = ExtractTTSSymbols(sPronunciation, pNGramTree->pSymbolHash, pNGramTree->pLinkPool);
      if (pSymbolList==NULL)
      {
         Message(NULL,"Couldn't get pronunciation for word '%s'.  Skipping.\n", sWord);
         continue;
      }
#ifdef DEBUG_HUFFMAN
      if ((iNumWords++)%10==0)
         printf("%s       \r", sWord);
#endif
      /* Convert the list of tokens to an array of symbol indices */
      iNumIndices = ListSize(pSymbolList);
      FNX_ASSERT(iNumIndices>0);
      piSymbols   = (SDWORD *)ListToArray(&pSymbolList, iNumIndices, pNGramTree->pLinkPool);
      pwSymbols   = (SWORD *)FNX_CALLOC(iNumIndices+1, sizeof(SWORD));
      /* Convert the 4-byte indices into 2-byte indices */
      for (iSymbolPos=0; iSymbolPos < iNumIndices; iSymbolPos++)
         pwSymbols[iSymbolPos] = (SWORD)piSymbols[iSymbolPos];

      /* Add the "end symbol" (';') to the end of the array of symbol indices */
      pwSymbols[iNumIndices++] = pNGramTree->wEndSymbol;

      /* Update the NGrams with this string of tokens */
      AddNGrams(pNGramTree, pwSymbols, iNumIndices);
      if (ppTokenVocab)
      {
         /* Create a tokenized word to go in the tokenized vocab */
         pTokenWord = (TokenWordPtr)FNX_MALLOC(sizeof(TokenWord));
         pTokenWord->sWord = FNX_STRDUP(sWord);
         pTokenWord->wNumIndices = (SWORD)iNumIndices;
         pTokenWord->pwSymbolIndices = pwSymbols;
         /* Insert the tokenized word into the linked list of them. */
         InsertLink(pTokenWord, &pTokenWords, pNGramTree->pLinkPool);
         (*ppTokenVocab)->iNumWords++;
      }
   }  /* while not end of file */
#ifdef DEBUG_HUFFMAN
   printf("%s         \n", sWord); /* Print the last word's name */
#endif

   FNX_FCLOSE(fp);

   if (ppTokenVocab)
   {
      /* Convert the linked list of tokenized words into an array of pointers */
      (*ppTokenVocab)->ppTokenWords = (TokenWordPtr *)ListToArray(&pTokenWords, (*ppTokenVocab)->iNumWords, pNGramTree->pLinkPool);
   }

   return pNGramTree;
}  /* BuildTTSNGrams */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;GetNGramList
 * DESC:    Recursively build a linked list of an NGram and all its "descendants"
 * IN:      pNGram - A node to be added to the list, along with its "descendants"
            ppList - Address of list to be modified.
            pLinkPool - Pool of links to use.
 * OUT:     *ppList points to the new head of the list, which has pNGram on it,
            preceded by all of its descendants.  pLinkPool has links taken from it.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
void GetNGramList(NGramNodePtr pNGram, llistPtr *ppList, LinkPoolPtr pLinkPool)
{
   NGramNodePtr pChild;
   if (pNGram)
   {
      InsertLink((voidPtr) pNGram, ppList, pLinkPool);
      for (pChild=pNGram->pChildren; pChild; pChild=pChild->pNext)
         GetNGramList(pChild, ppList, pLinkPool);
   }
}  /* ListNGrams */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;InsertNGram
 * DESC:    Insert an NGram into a sorted list of currently-used (top-level) NGrams
 * IN:      pNGramTree - Tree of NGrams to modify.
            pNGram     - Pointer to NGram to be inserted into "Used" list.
 * OUT:     pNGramTree->iNumUsed is likely incremented, pointers in its ->ppNGrams[] array
              are slid around, and pNGram is inserted into that list.  Something else is
              moved into NGram's spot.
 * RETURN:  Lowest index of any NGram affected by the operation.
 * NOTES:   pNGram->iPosition is used to find its position in ppNGrams (so ppNGrams[pNGram->iPosition]==pNGram)
            If iPosition>=*piNumUsed (i.e., if not already in the sorted list),
              then *piNumUsed is incremented, and ppNGram[*piNumUsed] is moved up into pNGram's old position.
            The calling routine needs to worry about the pParent, pChild, and pNext pointers of pNGram
              and nodes around it.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
SDWORD InsertNGram(NGramTreePtr pNGramTree, NGramNodePtr pNGram)
{
   SDWORD   iMinPosition, iPosition;
   NGramNodePtr *ppNGrams;
   FNX_ASSERT(pNGramTree && pNGram);
   FNX_ASSERT(pNGramTree->ppNGrams[pNGram->iPosition]==pNGram);
   FNX_ASSERT(pNGram->iCount>0); /* There shouldn't be any NGrams being added that don't occur. */
   FNX_ASSERT(pNGram->iPosition < pNGramTree->iNumPotential);

   ppNGrams = pNGramTree->ppNGrams;
   iMinPosition = pNGram->iPosition;

   if (pNGram->iPosition < pNGramTree->iNumUsed)
   {
      /* pNGram is already in the list of used NGrams, so just move it to where it goes. */
      iPosition = pNGram->iPosition;
      /* First see if it needs to be slid down...*/
      while (iPosition>0 && CmpNGramCount(pNGram, ppNGrams[iPosition-1]) < 0)
      {
         ppNGrams[iPosition] = ppNGrams[iPosition-1];
         ppNGrams[iPosition]->iPosition = iPosition--;
      }
      /* ...Then see if (instead) it needs to be slid up higher in the array. */
      while (iPosition+1 < pNGramTree->iNumUsed && CmpNGramCount(pNGram, ppNGrams[iPosition+1]) > 0)
      {
         ppNGrams[iPosition] = ppNGrams[iPosition+1];
         ppNGrams[iPosition]->iPosition = iPosition++;
      }
   }
   else /* pNGram not yet in list */
   {
      FNX_ASSERT(pNGram->iPosition < pNGramTree->iNumPotential); // It shouldn't become a symbol if it was already ruled out
      /* pNGram is not yet in the list of used NGrams, so insert it in there. */
      /* Make room for the new NGram */
      iPosition=pNGramTree->iNumUsed++;
      /* Move the (new) last element up into pNGram's position */
      ppNGrams[pNGram->iPosition] = ppNGrams[iPosition];
      ppNGrams[pNGram->iPosition]->iPosition = pNGram->iPosition;
      /* Move the (old) last elements up until we've found where pNGram goes. */
      while (iPosition>0 && CmpNGramCount(pNGram, ppNGrams[iPosition-1]) < 0)
      {
         ppNGrams[iPosition] = ppNGrams[iPosition-1];
         ppNGrams[iPosition]->iPosition = iPosition--;
      }
   }  /* else pNGram not in list */
   /* Now put pNGram back into the empty position */
   ppNGrams[iPosition] = pNGram;
   ppNGrams[iPosition]->iPosition = iPosition;
   if (iPosition < iMinPosition)
      iMinPosition = iPosition;
   return iMinPosition;
}  /* InsertNGram */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;InsertionSort
 * DESC:    Do an insertion sort.
 * IN:      piArray - An array of integers to be sorted (preferably partially sorted)
            iNumElements - Number of elements in piArray[].
 * OUT:     piArray[0..iNumElements-1] is sorted from lowest to highest.
 * RETURN:  n/a
 * NOTES:   Should be faster than a qsort() if the list is small and/or partially sorted.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
void InsertionSort(SDWORD *piArray, SDWORD iNumElements)
{
   SDWORD i, j, iValue;

   for (i=1; i<iNumElements; i++)
   {
      j=i;
      iValue=piArray[i];
      while ((j>0) && (piArray[j-1] > iValue))
      {
         piArray[j] = piArray[j-1];
         j--;
      }
      piArray[j] = iValue;
   }  /* for i */
}  /* InsertionSort */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;IntegerVectorMultiply
 * DESC:    Get a dot product of two integer vectors.
 * IN:      piArray1/2 - Two arrays of integers
            iNumElements - Number of elements in piArray1/2
 * OUT:     n/a
 * RETURN:  Sum(i==0..iNumElements-1) of piArray1[i]*piArray2[i].
 * NOTES:   Duh.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
SDWORD IntegerVectorMultiply(SDWORD *piArray1, SDWORD *piArray2, SDWORD iNumElements)
{
   SDWORD i, iSum=0;
   for (i=0; i<iNumElements; i++)
   {
      iSum += piArray1[i] * piArray2[i];
   }
   return iSum;
}  /* IntegerVectorMultiply */
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;UnlinkChildNGram
 * DESC:    Remove an NGram from its parent's list of children.
 * IN:      pNGram  - NGram.
 * OUT:     pNGram's parent's list of children no longer includes pNGram.
            pNGram->pParent is NULL.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
void UnlinkChildNGram(NGramNodePtr pNGram)
{
   NGramNodePtr pParent, *ppPrev;

   pParent = pNGram->pParent;
   if (pParent==NULL)
      return; /* Has no parent, so no need to do anything */
   /* Point the parent's child pointer or one of its children's 'pNext' pointer
      to whatever pNGram's pNext pointer points to. */
   for (ppPrev = &pParent->pChildren; *ppPrev; ppPrev = &(*ppPrev)->pNext)
   {
      if (*ppPrev == pNGram)
      {
         *ppPrev = pNGram->pNext;
         break;
      }
   }  /* for each child of pParent (i.e., sibling of pNGram) */

   /* Remove pNGram's parent pointer, since it is now going to be a top-level node */
   pNGram->pParent = NULL;
   pNGram->pNext   = NULL; /* As a top-level node, this NGram no longer has siblings. */
}  /* UnlinkChildNGram */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;RemoveNGramSubtree
 * DESC:    Recursively remove an NGram and its descendants from an NGram tree.
 * IN:      pNGramTree - Tree of NGrams to be modified
            pNGram - NGram to remove, along with its descendants
 * OUT:     pNGram and its descendants are moved to the end of ppNGrams[], and pNGramTree->iNumNGrams
            is decremented by how many are moved there.  If pNGram is a top-level NGram,
            then other top-level NGrams may be slid down, and pNGram->iNumUsed will be decremented.
 * RETURN:  The lowest index of any (remaining) node affected by the operation.
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
SDWORD RemoveNGramSubtree(NGramTreePtr pNGramTree, NGramNodePtr pNGram)
{
   NGramNodePtr pChild, pNextChild, *ppNGrams;
   SDWORD iMinPosition, iTempMinPosition, i;
   
   FNX_ASSERT(pNGramTree);
   FNX_ASSERT(pNGram);

   ppNGrams = pNGramTree->ppNGrams;
   iMinPosition = pNGram->iPosition;

   if (pNGram==NULL)
      return iMinPosition;
   /* Recursively remove all descendants of pNGram */
   for (pChild=pNGram->pChildren; pChild; pChild=pNextChild)
   {
      pNextChild = pChild->pNext;
      iTempMinPosition = RemoveNGramSubtree(pNGramTree, pChild);
      if (iTempMinPosition < iMinPosition)
         iMinPosition = iTempMinPosition;
   }
   /* If pNGram is a symbol, move it out of the list of symbols */
   if (pNGram->iPosition < pNGramTree->iNumUsed)
   {
      /* This is a top-level NGram, so we first have to slide all of the top-level NGrams down one */
      for (i=pNGram->iPosition; i < pNGramTree->iNumUsed - 1; i++)
      {
         ppNGrams[i] = ppNGrams[i+1];
         ppNGrams[i]->iPosition = i;
      }
      /* There is one less top-level NGram now. */
      pNGramTree->iNumUsed--;
      /* Put pNGram into the first (currently "empty") (now non-top-level) position */
      ppNGrams[pNGramTree->iNumUsed] = pNGram;
      pNGram->iPosition = pNGramTree->iNumUsed;
   }
   /* At this point, pNGram is somewhere between pNGramTree->iNumUsed and ->iNumNNGrams */
   FNX_ASSERT(pNGram->iPosition >= pNGramTree->iNumUsed && pNGram->iPosition < pNGramTree->iNumNGrams);
   /* If the NGram is a "potential" one, move it beyond the potential ones */
   if (pNGram->iPosition < pNGramTree->iNumPotential)
   {
      /* This is an NGram that hadn't been checked for use as a symbol yet,
         so move it to the end of those that are in that category, so we don't
         swap it for one that has already been checked */
      pNGramTree->iNumPotential--;
      SwapNGrams(ppNGrams, pNGram->iPosition, pNGramTree->iNumPotential);
   }
   FNX_ASSERT(pNGram->iPosition >= pNGramTree->iNumPotential && pNGram->iPosition < pNGramTree->iNumNGrams);
   /* Swap it with the last NGram in the list */
   pNGramTree->iNumNGrams--;
   /* Set NGram's count to 0. */
   pNGram->iCount=0;
   SwapNGrams(ppNGrams, pNGram->iPosition, pNGramTree->iNumNGrams);

   return iMinPosition;
}  /* RemoveNGramSubtree */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;SubtractCount
 * DESC:    Subtract a given amount from the count of an NGram node, and delete it if it reaches 0.
 * IN:      pNGramTree   - Tree of NGrams to modify.
            pNGram       - Node to decrement
            iCount       - Amount to decrement pNGram->iCount by.
            ppPrev       - Address of pointer to pNGram (from parent or sibling)
 * OUT:     pNGram->iCount-=iCount, and if it reaches 0, then pNGram (and its descendants)
              are removed from pNGramTree (by moving them to the end).  In that case,
              pNGramTree->iNumNGrams and possibly pNGramTree->iNumPotential and ->iNumUsed
              may be decremented.  If pNGram is a symbol (i.e., its position is < ->iNumUsed),
              then it is re-inserted into the list to make sure it is still sorted.
            if pNGram->iCount drops to 0, then *ppPrev=pNGram->pNext (if ppPrev is non-NULL)
              or, if ppPrev is NULL, then pNGram is "Unlinked" from its parent (if any).
 * RETURN:  Lowest position in pNGramTree->ppNGrams[] that any NGram was moved to during this operation.
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
SDWORD SubtractCount(NGramTreePtr pNGramTree, NGramNodePtr pNGram, SDWORD iCount, NGramNodePtr *ppPrev)
{
   SDWORD iTempMinPosition, iMinPosition=pNGram->iPosition;

   pNGram->iCount -= iCount;
   FNX_ASSERT(pNGram->iCount>=0);
   if (pNGram->iCount==0)
   {
      /* Remove pointer to pOtherNGram from its parent (possibly via a sibling's "pNext" pointer), if any */
      if (ppPrev)
      {
         // Make sure ppPrev is really what points to pNGram
         FNX_ASSERT(*ppPrev == pNGram);
         (*ppPrev) = pNGram->pNext;
      }
      else if (pNGram->pParent)
         UnlinkChildNGram(pNGram);
      iTempMinPosition = RemoveNGramSubtree(pNGramTree, pNGram);
      if (iTempMinPosition < iMinPosition)
         iMinPosition = iTempMinPosition;
   }
   else if (pNGram->iPosition < pNGramTree->iNumUsed)
   {
      /* pNGram is a top-level symbol whose count just changed, so re-insert
         it into the list of symbols so that the list will remain sorted by 'iCount' */
      InsertNGram(pNGramTree, pNGram);
   }
   return iMinPosition;
}  /* SubtractCount */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;PromoteNGram
 * DESC:    Replace an NGram ebedded in an NGram tree with a new symbol.
            pNGramTree      - NGram tree which may be modified.
            pNGramToPromote - NGram node which will be promoted to be a sibling to its N-th ancestor
            pNGram  - The NGram node which represents the actual NGram (e.g., "abcd") 
                              being replaced by the new symbol.
            wSymbol         - Index of the new symbol to be used.
 * OUT:     pNGramToPromote's symbol=wSymbol; its count and the counts of its N closest
              ancestors are decremented by pNGram->iCount (where N=length of original NGram);
              any ancestors whose counts become 0 are removed.
 * RETURN:  Index of earliest element in pNGramTree->ppNGrams[] that was modified.
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
SDWORD PromoteNGram(NGramTreePtr pNGramTree, NGramNodePtr pNGramToPromote, NGramNodePtr pNGram, SWORD wSymbol)
{
   NGramNodePtr pPromoteParent, pNGramParent, pTemp;
   SDWORD iMinPosition; /* Lowest-indexed position where something was moved to
                           that might require re-checking that index for the occurance of pNGram */
   SDWORD iTempMinPosition;

   iMinPosition = pNGramToPromote->iPosition;

   FNX_ASSERT(pNGramToPromote && pNGram);
   
   /* Get a pointer to the two nodes' parents before unlinking pNGramToPromote from its parent */
   pPromoteParent = pNGramToPromote->pParent;
   pNGramParent = pNGram->pParent;
   FNX_ASSERT(pPromoteParent && pNGramParent); // Make sure this isn't a 1-gram, which shouldn't need promoting

   /* 1. Remove pNGramToPromote from its parent */
   UnlinkChildNGram(pNGramToPromote);

   /* 2. Subtract NGram's count from promote->parent back to last common ancestor a (but not from g itself) */
   while (pNGramParent)
   {
      //Make sure we are following a matching NGram.  If not, we shouldn't have called this routine.
      FNX_ASSERT(pPromoteParent && pNGramParent->wSymbol==pPromoteParent->wSymbol);
      
      /* Remember the node in case we need to delete it */
      pTemp = pPromoteParent;
      
      /* Advance to the next set of parents */
      pNGramParent   = pNGramParent->pParent;
      pPromoteParent = pPromoteParent->pParent;
      
      /* Subtract the NGram's count from this node */
      iTempMinPosition = SubtractCount(pNGramTree, pTemp, pNGramToPromote->iCount, NULL /* => do UnlinkChildNGram() */);
      if (iTempMinPosition < iMinPosition)
         iMinPosition = iTempMinPosition;
   }  /* while NGramParent */
   
   /* 3. Insert pNGramToPromote into the siblings of its ancestor
         (which will be the top-level symbols iff pNGramToPromote==pNGram) */
   if (pPromoteParent)
   {
      /* Insert pNGramToPromote into its ancestor's list of children */
      pNGramToPromote->pNext = pPromoteParent->pChildren;
      pPromoteParent->pChildren = pNGramToPromote;
      pNGramToPromote->pParent = pPromoteParent;
   }
   else
   {
      /* pPromoteParent==NULL, and so is pNGramParent, so pNGramToPromote
         is actually pNGram itself.  So add it as a top-level symbol. */
      FNX_ASSERT(pNGramToPromote==pNGram);
      FNX_ASSERT(pNGram->iPosition >= pNGramTree->iNumUsed); // Make sure NGram isn't already a symbol!
      FNX_ASSERT(pNGram->iPosition < pNGramTree->iNumPotential); // Make sure NGram hasn't been discarded
      /* Add 'wSymbol' as a new symbol */
      FNX_ASSERT(wSymbol == pNGramTree->wNumSymbols);
      pNGramTree->ppSymbolNGrams[pNGramTree->wNumSymbols] = pNGram;
      /* Insert the NGram where it goes according to its count */
      iTempMinPosition = InsertNGram(pNGramTree, pNGram);
      if (iTempMinPosition < iMinPosition)
         iMinPosition = iTempMinPosition;
   }
   /* Set the symbol of the promoted NGram to the new one that replaces the NGram. */
   pNGramToPromote->wSymbol = wSymbol;

   return iMinPosition;
}  /* PromoteNGram */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;SubtractDescendants
 * DESC:    Recursively subtract the counts of one subtree from the corresponding nodes in another.
 * IN:      pNGramTree   - Tree of NGrams to modify.
            pNGram       - Root of the tree with the counts used for subtraction
            pOtherNGram  - Root of the tree from which counts are to be subtracted
 * OUT:     The Counts of the descendants of pOtherNGram that correspond to nodes in pNGram
              are decremented.  If any counts drop to 0, then the node and its descendants
              are removed from the tree (by being moved to the end of ppNGrams[] and 
              decrementing *piNumNGrams).  *piNumUsed could be decremented if a top-level
              node is deleted, but that won't happen here, since pOtherNGram's count is
              not ITSELF modified, but only the counts of its descendants, none of which
              can be top-level nodes.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
void SubtractDescendants(NGramTreePtr pNGramTree, NGramNodePtr pNGram, NGramNodePtr pOtherNGram)
{
   NGramNodePtr pChild, pOtherChild, *ppPrev;
   if (pNGram==NULL || pOtherNGram==NULL)
      return; /* Reached the end of a corresponding branch */
   /* Visit all children and recurse to each */
   for (pChild=pNGram->pChildren; pChild; pChild=pChild->pNext)
   {
      ppPrev = &(pOtherNGram->pChildren);
      for (pOtherChild=pOtherNGram->pChildren; pOtherChild; pOtherChild=pOtherChild->pNext)
      {
         if (pOtherChild->wSymbol==pChild->wSymbol)
            break;
         else ppPrev = &(pOtherChild->pNext);
      }
      if (pOtherChild)/* Should find a corresponding node in the suffix's NGram tree, unless limiting NGram length */
      {
         SubtractCount(pNGramTree, pOtherChild, pChild->iCount, ppPrev);
         if (pOtherChild->iCount>0) /* If it didn't get completely subtracted away, then do descendants */
            SubtractDescendants(pNGramTree, pChild, pOtherChild);
      }
   }  /* for each child of pNGram */
}  /* SubtractDescendants */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;FreeHuffman
 * DESC:    Free a Huffman decoding table
 * IN:      pHuffman - Huffman table structure to free.
 * OUT:     pHuffman and all of its fields are freed up.
 * RETURN:  
 * NOTES:   
 *END_HEADER***************************/
void FreeHuffman(HuffmanPtr pHuffman)
{
   if (pHuffman)
   {
      if (pHuffman->pwSymbolIndices)
         FNX_FREE(pHuffman->pwSymbolIndices);
      if (pHuffman->psLiterals)
         FNX_FREE(pHuffman->psLiterals); /* Allocated as a single block containing pointers and all strings */
      if (pHuffman->ppwNGrams)
         FNX_FREE(pHuffman->ppwNGrams); /* Allocated as a single block containing pointers and all arrays */
      if (pHuffman->pcCodeLengths)
         FNX_FREE(pHuffman->pcCodeLengths);
      if (pHuffman->psCodeStrings)
         FreePointerArray(pHuffman->psCodeStrings, pHuffman->wNumSymbols);
      if (pHuffman->pTables)
         FNX_FREE(pHuffman->pTables);
      if (pHuffman->pLinkPool)
         FreeLinkPool(pHuffman->pLinkPool);
      FNX_FREE(pHuffman);
   }
}  /* FreeHuffman */

/*FUNCTION_HEADER**********************
 * NAME:    ;BuildHuffmanTable
 * DESC:    Build a Huffman decoding table
 * IN:      wNumSymbols  - Number of symbols (literals, ending with delimeters; then NGrams)
            wNumLiterals - Number of literal symbols (including delimeters)
            wNumDelim    - Number of delimeters (i.e., last 'wNumDelim' literals are delimeters).
            wEndSymbol   - Which symbol is the "end-of-string" symbol.
            psLiterals   - Array of strings containing the name of each symbol
            ppwNGrams    - Array[wNumSymbols-wNumLiterals] of NGram definitions. [0]=N, [1..N-1]=symbols in NGram
            wNumUsed        - Number of symbols actually used in Huffman coding
            pwSymbolIndices - Array of 'wNumUsed' symbol numbers, sorted from longest code length to shortest
            pcCodeLengths   - Code length of each symbol
            cMaxCodeLength  - Maximum length of any symbol (-1 => search array to see).
 * OUT:     
 * RETURN:  
 * NOTES:   If some symbols are referenced in ppwNGrams but are never actually used
              in the Huffman coding, then their code length in pcCodeLengths[] is 0,
              and they are not included in pwSymbolIndices[].
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
HuffmanPtr BuildHuffmanTable(SWORD wNumSymbols, SWORD wNumLiterals, SWORD wNumDelim, SWORD wEndSymbol,  
                             char **psLiterals, SWORD **ppwNGrams, SWORD wNumUsed, SWORD *pwSymbolIndices,
                             SBYTE *pcCodeLengths, SBYTE cMaxCodeLength, BOOL bNeedSpaces)
{
   HuffmanPtr pHuffman;
   SWORD      wIndex; /* Index into pwSymbolIndices[] (which in turn contains actual wSymbol) */
   SDWORD     iNumCodeLengths; /* Number of different code lengths */
   SDWORD     iTable, iBits;
   UDWORD     uiPattern;
   if (cMaxCodeLength<0)
   {
      /* Find the maximum symbol length if it is not supplied. */
      for (wIndex=0; wIndex<wNumSymbols; wIndex++)
      {
         if (pcCodeLengths[wIndex] > cMaxCodeLength)
            cMaxCodeLength = pcCodeLengths[wIndex];
      }
   }
   if (cMaxCodeLength > 32)
   {
      Message(NULL,"Code length exceeded 32.  You'll need to cut down the number of symbols or modify the program\n");
      return NULL; /* Error: Our implementation doesn't currently handle more than 4-byte code lengths. */
   }

   pHuffman = (HuffmanPtr) FNX_CALLOC(1, sizeof(Huffman));

   pHuffman->wNumLiterals    = wNumLiterals;
   if (bNeedSpaces)
      pHuffman->wNumSeparate    = wNumLiterals - wNumDelim; /* => first 'wNumSeparate' literals must be separated from each other by a space */
   else pHuffman->wNumSeparate  = 0; /* No symbols need to be separated with spaces, so treat them all as "delimeters" */
   pHuffman->wNumSymbols     = wNumSymbols;
   pHuffman->psLiterals      = psLiterals;
   pHuffman->ppwNGrams       = ppwNGrams;
   pHuffman->wNumUsed        = wNumUsed;
   pHuffman->pwSymbolIndices = pwSymbolIndices;
   pHuffman->cMaxCodeLength  = cMaxCodeLength;
   pHuffman->pcCodeLengths   = pcCodeLengths;
   pHuffman->pLinkPool       = NewLinkPool(100);
   pHuffman->wEndSymbol      = wEndSymbol;

   /* See how many DIFFERENT code lengths there are in the list of symbols */
   FNX_ASSERT(wNumSymbols>0);
   iNumCodeLengths=1;
   for (wIndex=1; wIndex < wNumUsed; wIndex++)
   {
      /* Since pcCodeLengths[pwSymbolIndices[wIndex]] is sorted by code length, all symbols with the
         same length are adjacent within it.  Thus, when it changes, we know we
         have an additional code length to handle */
      FNX_ASSERT(pcCodeLengths[pwSymbolIndices[wIndex-1]]>=pcCodeLengths[pwSymbolIndices[wIndex]]);
      if (pcCodeLengths[pwSymbolIndices[wIndex-1]]!=pcCodeLengths[pwSymbolIndices[wIndex]])
         iNumCodeLengths++;
   }
   /* Build lookup tables */
   pHuffman->pTables = (CodeLengthTablePtr) FNX_CALLOC(iNumCodeLengths, sizeof(CodeLengthTable));
   wIndex=0;
   /* Build tables in order so that longer bitlengths are done before shorter
      ones, which allows us to build the uiStart value based on the previous lengths' info. */
   for (iTable=0; iTable < iNumCodeLengths; iTable++)
   {
      if (iTable>0)
      {
         /* Increment wIndex to the first symbol with the next code length */
         do
         {
            wIndex++;
         } while (wIndex < pHuffman->wNumSymbols && pcCodeLengths[pwSymbolIndices[wIndex]]==pcCodeLengths[pwSymbolIndices[wIndex-1]]);
      }

      /* Set the code length of this table */
      pHuffman->pTables[iTable].uiCodeLength = (UDWORD)pcCodeLengths[pwSymbolIndices[wIndex]];
      
      /* Set the index (in pHuffman->pwSymbolIndices[]) of the first symbol in this table */
      pHuffman->pTables[iTable].uiFirstSymbol = (UDWORD)wIndex;

      /* Create a mask with MaxCodeLength-uiCodeLength ones on the right */
      uiPattern=0;
      for (iBits=(SDWORD)(cMaxCodeLength-pcCodeLengths[pwSymbolIndices[wIndex]]); iBits>0; iBits--)
      {
         uiPattern <<= 1; /* Slide bits left one bit */
         uiPattern |= 1; /* Set the rightmost bit to 1 */
      }
      pHuffman->pTables[iTable].uiPatternMask = uiPattern;
      
      /* Create a pattern containing the starting code of the first element
         in this table, padded on the right with 0's to make it cMaxCodeLength. */
      if (iTable>0)
      {
         /* uiStart for each table after the first one is:
              (uiStart of previous table) + (#symbols in previous table) * 1<<(maxCodeLength - previous Table's code length) */
         uiPattern = pHuffman->pTables[iTable-1].uiStart + 
                     ((UDWORD)wIndex - pHuffman->pTables[iTable-1].uiFirstSymbol) *
                     (1 << ((UDWORD)cMaxCodeLength - pHuffman->pTables[iTable-1].uiCodeLength));
      }
      else uiPattern=0; /* Maximum bit length is in first table, and its starting pattern is all 0. */
      pHuffman->pTables[iTable].uiStart = uiPattern;
   }  /* for each table */
   pHuffman->iNumTables = iNumCodeLengths;
   return pHuffman;
}  /* BuildHuffmanTable */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;CmpNGram
 * DESC:    Compare two pointers to NGram pointers.
 * IN:      a, b - Void pointers to NGram pointers to be compared
 * OUT:     n/a
 * RETURN:  -1 if a<b, 0 if a==b, 1 if a>b (see notes)
 * NOTES:   Compares two NGram pointers such that they will be sorted
            LONGEST TO SHORTEST by bit length.  For symbols of the same
            bit length, they are sorted by wSymbol value (lowest to highest).
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
#ifdef OS_WIN32
int __cdecl CmpNGramBitLength(const void *a, const void *b)
#else
int CmpNGramBitLength(const void *a, const void *b)
#endif
{
   NGramNodePtr *ppA, *ppB;
   NGramNodePtr pA, pB;
   ppA = (NGramNodePtr *)a;
   ppB = (NGramNodePtr *)b;
   pA = *ppA;
   pB = *ppB;
   if (pA->wBitLength > pB->wBitLength) /* Sorting longest to shortest ! */
      return -1;
   else if (pA->wBitLength < pB->wBitLength)
      return 1;
   else if (pA->wSymbol < pB->wSymbol) /* Bit lengths are the same, so sort lowest wSymbol to highest */
      return -1;
   else if (pA->wSymbol > pB->wSymbol)
      return 1;
   else return 0;
}  /* CmpNGram */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;NGramToHuffman
 * DESC:    Create a Huffman table from an NGram tree
 * IN:      pNGramTree - NGram Tree which has had NGrams entered into it, and has selected NGrams to use.
 * OUT:     A Huffman table is built.
 * RETURN:  Pointer to a newly-allocated Huffman table.
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
HuffmanPtr NGramToHuffman(NGramTreePtr pNGramTree)
{
   HuffmanPtr pHuffman;
   SWORD **ppwNGrams;
   SWORD  wNumNGrams, w, i;
   SDWORD iSize;
   SWORD *pwPosition;
   SWORD *pwSymbolIndices;
   SBYTE *pcCodeLengths;
   char **psLiterals;
   NGramNodePtr *ppNGrams; /* Copy of first 'pNGramTree->iNumUsed' NGram pointers, 
                              so we can sort them without modifying pNGramTree. */

   /*** Prepare information to pass into BuildHuffmanTable */
   /* Make a copy of the first 'iNumUsed' NGram pointers so we can sort them without
      modifying pNGramTree. */
   ppNGrams = (NGramNodePtr *)FNX_MALLOC(pNGramTree->iNumUsed * sizeof(NGramNodePtr));
   memcpy(ppNGrams, pNGramTree->ppNGrams, pNGramTree->iNumUsed * sizeof(NGramNodePtr));
   /* Sort the first 'iNumUsed' NGrams first by code length (longest first), and
      then by wSymbol within the same code length. */
   qsort(ppNGrams, pNGramTree->iNumUsed, sizeof(NGramNodePtr), CmpNGramBitLength);

   /** Allocate the array(s) of NGram symbol counts and indices. */
   /* First, calculate the amount of storage needed for the whole table */
   wNumNGrams = (SWORD)(pNGramTree->wNumSymbols - pNGramTree->wNumLiterals);
   if (wNumNGrams > 0)
   {
      iSize = wNumNGrams * sizeof(SWORD *);
      for (w=0; w < wNumNGrams; w++)
         iSize += (pNGramTree->ppwNGrams[w][0]+1) * sizeof(SWORD);

      /* Allocate a single buffer large enough to hold the pointer for each
         array plus the words within the pointer */
      ppwNGrams  = (SWORD **)FNX_MALLOC( iSize );
      /* Use 'pwPosition' to point at where each NGram's array of SWORDs starts */
      pwPosition = (SWORD *)&(ppwNGrams[wNumNGrams]); /* Start out just beyond the array of pointers */
      /* Copy the count and indices over from pNGramTre->ppwNGrams into ppwNGrams */
      for (w=0; w < wNumNGrams; w++)
      {
         ppwNGrams[w] = pwPosition;
         for (i=0; i < pNGramTree->ppwNGrams[w][0]+1; i++)
            *(pwPosition++) = (SWORD)pNGramTree->ppwNGrams[w][i];
      }
   }  /* if there were NGrams */
   else ppwNGrams = NULL;

   /** Allocate an array of bytes containing the symbol lengths */
   pcCodeLengths = (SBYTE *)FNX_MALLOC(sizeof(UBYTE) * pNGramTree->wNumSymbols);
   for (i=0; i<pNGramTree->wNumSymbols; i++)
   {
      if (pNGramTree->ppSymbolNGrams[i]->iPosition < pNGramTree->iNumUsed)
         pcCodeLengths[i] = (SBYTE)pNGramTree->ppSymbolNGrams[i]->wBitLength;
      else pcCodeLengths[i] = 0; /* => not used */
   }

   /** Create a copy of the list of literals */
   psLiterals = BuildStringList((char **)pNGramTree->psSymbolNames, (SDWORD)pNGramTree->wNumLiterals);

   /** Create an array of indices of the symbols, sorted first by code length
       and then, within the same code length, by symbol index.  This array
       is meant for use in a Huffman table lookup scheme, and does NOT include
       symbols that are not used in the Huffman decoding (i.e., those that are
       only referenced by other NGrams rather than occuring in the dictionary itself). */
   pwSymbolIndices = (SWORD *)FNX_MALLOC(pNGramTree->iNumUsed * sizeof(SWORD));
   for (i=0; i < pNGramTree->iNumUsed; i++)
      pwSymbolIndices[i] = ppNGrams[i]->wSymbol;
   
   /** Now put all of that information into a huffman table */
   pHuffman = BuildHuffmanTable(pNGramTree->wNumSymbols,  pNGramTree->wNumLiterals, 
                                pNGramTree->wNumDelim, pNGramTree->wEndSymbol, psLiterals, 
                                ppwNGrams, (SWORD)pNGramTree->iNumUsed, pwSymbolIndices, 
                                pcCodeLengths, (SBYTE) -1, pNGramTree->bNeedSpaces);
   if (ppNGrams)
      FNX_FREE(ppNGrams);
   return pHuffman;
}  /* NGramToHuffman */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;RemoveLengthyNGrams
 * DESC:    Slide NGrams that are too long out where they won't get used.
 * IN:      pNGramTree - Tree of NGrams
            ppNGrams   - Array of pointers to all NGrams (as used in SelectNGrams)
            iRootIndex - Index (in ppNGrams[]) of the NGram to use.
            iDepth     - Depth in the NGram tree that iRootIndex is at (where top level is 1).
 * OUT:     ppNGrams[iRootIndex] or any of its children that are deeper than
              pNGramTree->iMaxNGramLength are slide beyond pNGram->iNumPotential
              in ppNGrams[], so that they will not be considered for use
              as a real N-Gram symbol.
 * RETURN:  n/a
 * NOTES:   Should only be called if pNGramTree->iMaxNGramLength>0 (otherwise,
              ALL N-grams should be considered for use as a symbol).
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
void RemoveLengthyNGrams(NGramTreePtr pNGramTree, NGramNodePtr *ppNGrams, 
                         SDWORD iRootIndex, SDWORD iDepth)
{
   NGramNodePtr pChild, pNGram;
   FNX_ASSERT(pNGramTree->iMaxNGramLength > 0); // or else we shouldn't call this routine at all.
   
   /* Don't bother with nodes that have already been moved above 'iNumPotential'
      and thus are not considered for use.  (The children of any such nodes
      should also already be out of consideration, since their count will
      be at least as low (i.e., 1) as their parent.) */
   if (iRootIndex < pNGramTree->iNumPotential)
   {
      pNGram = ppNGrams[iRootIndex];
      FNX_ASSERT(pNGram->iPosition == iRootIndex);
      if (iDepth > pNGramTree->iMaxNGramLength)
      {
         SwapNGrams(ppNGrams, iRootIndex, --pNGramTree->iNumPotential);
         FNX_ASSERT(pNGram->iPosition == pNGramTree->iNumPotential);
      }
      for (pChild=pNGram->pChildren; pChild; pChild=pChild->pNext)
         RemoveLengthyNGrams(pNGramTree, ppNGrams, pChild->iPosition, iDepth+1);
   }
}  /* RemoveLengthyNGrams */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;SelectNGrams
 * DESC:    Choose which NGrams to include as symbols in a Huffman encoding scheme
 * IN:      pNGramTree - Tree of NGrams with counts as to how often each occurred.
 * OUT:     pNGramTree->wNumSymbols = # of symbols (terminals + NGrams (including only indirectly used)) decided upon
            pNGramTree->ppwNGrams contain arrays of integers with count & indices of subsymbols
                each nonterminal symbol uses.
 * RETURN:  Pointer to the Huffman tree built from the best set of NGrams found.
 * NOTES:   If the returned Huffman->wNumSymbols <= 255, then it was chosen based on
              using 8-bit references to symbols in NGram definitions.  Otherwise, it
              was chosen based on using 16-bit references.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
HuffmanPtr SelectNGrams(NGramTreePtr pNGramTree)
{
#ifdef USE_WINDOWS
   int cnt = 0;
   char szMsg[LARGE_BUFFER];
#endif
   NGramNodePtr *ppNGrams;      /* =pNGramTree->ppNGrams */
   SDWORD *piCount;     /* Count of first 'iNumUsed' symbols in ppNGrams[] array */
   SDWORD *piBitLength; /* Bit length of each symbol in piCount[] */
   NGramNodePtr pNGram, pSuffixStart, pOtherNGram, *ppPrev, pFollow, pChild, pParent;
   llistPtr pNGramList, pSuffixList, pLink;
   SDWORD i, iBitsUsed, iBestBitLength;
   SDWORD iBitsSaved, iMaxBitsSaved=0, iBestNGram = 0, iN;
   SWORD  *pwNGramDef; /* Shorthand pointer to the current definition of a new NGram. */
   SWORD  wMap, wLastPhone;
   SDWORD iMinPosition, iTempMinPosition;
   SDWORD iMaxBitLength;
   SDWORD iNumSymbolReferences=0; /* Total number of symbol indices in NGram definitions */
   SDWORD iNumZero; /* Number of counts that dropped to 0 */
   SDWORD i8BitSize=0; /* Number of bits needed for a Huffman encoding with up to 255 symbols. */
   HuffmanPtr pHuffman=NULL; /* Best Huffman table (8- or 16-bit) */
   SDWORD iLastMaxBitsSaved;
   BOOL   bDone;

#ifdef USE_WINDOWS
   SetupProgressIndicator( g_hDlg, 800 );
#endif
   if (pNGramTree==NULL)
      return NULL;

   /** Get a list of all of the NGrams */
   pNGramList = NULL;
   pNGramTree->pwSymbolMap=(SWORD *)FNX_CALLOC(pNGramTree->wNumLiterals, sizeof(SWORD));
   wMap=0;
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
   for (i=0; i<pNGramTree->wNumLiterals; i++)
   {
      if (pNGramTree->pFirstLevel[i].iCount > 0)
      {
         GetNGramList(&(pNGramTree->pFirstLevel[i]), &pNGramList, pNGramTree->pLinkPool);
         pNGramTree->pwSymbolMap[i] = wMap++;
      }
      else pNGramTree->pwSymbolMap[i] = -1; /* => unused */
   }
   pNGramTree->iTotalNGrams = ListSize(pNGramList);
#ifdef BUILD_DCC_PROJECT
   printf("    %d NGrams total to begin with\n", pNGramTree->iTotalNGrams);
#endif

   pNGramTree->iNumNGrams = pNGramTree->iTotalNGrams; /* We haven't deleted any NGrams with iCount==0 yet */
   ppNGrams = pNGramTree->ppNGrams = (NGramNodePtr *)ListToArray(&pNGramList, pNGramTree->iNumNGrams, pNGramTree->pLinkPool);
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
   for (i=0; i<pNGramTree->iNumNGrams; i++)
      ppNGrams[i]->iPosition = i; /* Let each NGram know where it is in the list */
   if (wMap < pNGramTree->wNumLiterals)
   {
      /* Some literals were never used, so we need to remove them from the tree. */
      /* Map all symbol indices to the symbol index with unused symbols removed */
      for (i=0; i<pNGramTree->iNumNGrams; i++)
      {
         //FNX_ASSERT(ppNGrams[i]->iCount > 0);
         ppNGrams[i]->wSymbol = pNGramTree->pwSymbolMap[ppNGrams[i]->wSymbol];
      }

      /* Slide symbol names and "FirstLevel" records down */
      wLastPhone=-1;
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
      for (i=0; i<pNGramTree->wNumLiterals; i++)
      {
         if (pNGramTree->pwSymbolMap[i] == -1)
            FreeAndClear((void **)&pNGramTree->psSymbolNames[i]);
         else 
         {
            if (i<pNGramTree->wNumPhones)
               wLastPhone=pNGramTree->pwSymbolMap[i]; /* Keep track of the last basephone seen so we know how many there are */
            if (i!= pNGramTree->pwSymbolMap[i])
            {
               /* Slide symbol name down */
               FNX_ASSERT(pNGramTree->psSymbolNames[pNGramTree->pwSymbolMap[i]]==NULL);
               pNGramTree->psSymbolNames[pNGramTree->pwSymbolMap[i]] = pNGramTree->psSymbolNames[i];
               pNGramTree->psSymbolNames[i]=NULL; // to avoid FNX_ASSERT() above
               /* Slide "pFirstLevel" NGram down */
               memmove(&pNGramTree->pFirstLevel[pNGramTree->pwSymbolMap[i]], &pNGramTree->pFirstLevel[i], sizeof(NGramNode));
               pParent = ppNGrams[pNGramTree->pFirstLevel[pNGramTree->pwSymbolMap[i]].iPosition] = &pNGramTree->pFirstLevel[pNGramTree->pwSymbolMap[i]];
               /* Update pointers from first level NGrams' children back to their parent, which has moved */
               for (pChild=pParent->pChildren; pChild; pChild=pChild->pNext)
                  pChild->pParent = pParent;
            }
         }
      }  /* for each literal */
      pNGramTree->wEndSymbol = pNGramTree->pwSymbolMap[pNGramTree->wEndSymbol];
      FNX_ASSERT(pNGramTree->wEndSymbol >= 0);
      pNGramTree->wNumLiterals = wMap;
      pNGramTree->wNumSymbols  = pNGramTree->wNumLiterals;
      pNGramTree->wNumPhones   = wLastPhone+1;
      pNGramTree->wNumDelim    = pNGramTree->wNumLiterals - pNGramTree->wNumPhones;
   }  /* if unused literals */
   /* Indicate that all NGrams are currently potential symbols */
   pNGramTree->iNumPotential = pNGramTree->iNumNGrams;

   /* Slide the original 1-grams up to the beginning of the array. */
   pNGramTree->iNumUsed=0;
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
   for (i=0; i<pNGramTree->wNumLiterals; i++)
   {
      FNX_ASSERT(pNGramTree->pFirstLevel[i].iCount > 0); /* Should have slid these up already */
      InsertNGram(pNGramTree, &(pNGramTree->pFirstLevel[i]));
   }
   
   /* Remove all NGrams with a count of no more than 1 out of the "potential" list,
      since creating an NGram for a sequence that only occurs once won't help. */
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
   for (i=pNGramTree->iNumUsed; i<pNGramTree->iNumPotential; i++)
   {
      if (ppNGrams[i]->iCount<=1)
         SwapNGrams(ppNGrams, i, --pNGramTree->iNumPotential);
   }
#ifdef BUILD_DCC_PROJECT
   printf("    %d NGrams that can potentially be kept\n", pNGramTree->iNumPotential);
#endif
   /* Remove all NGrams with a length longer than iMaxNGramLength
      since they are included only to provide enough context to know
      when their ancestors have been matched by sub-portions of a
      new NGram. */
   if (pNGramTree->iMaxNGramLength > 0)
   {
      for (i=0; i<pNGramTree->iNumUsed; i++)
         RemoveLengthyNGrams(pNGramTree, ppNGrams, i, 1);
   }
   /* Allocate an array of pointers to the NGrams representing each of the
      symbols (originally just literals, but later the super-symbols, too).
      This allows us to do "pNGram=ppSymbolNGrams[wSymbol]" and get the top-level
      NGram for each (original or created) symbol. */
   pNGramTree->ppSymbolNGrams = (NGramNodePtr *)FNX_CALLOC(pNGramTree->iNumNGrams, sizeof(NGramNodePtr));
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
   for (i=0; i<pNGramTree->wNumLiterals; i++)
      pNGramTree->ppSymbolNGrams[i] = &(pNGramTree->pFirstLevel[i]);

   /* Allocate an empty array of pointers to put NGram definitions into when needed */
   pNGramTree->ppwNGrams = (SWORD **)FNX_CALLOC(pNGramTree->iTotalNGrams - pNGramTree->wNumLiterals, sizeof(SWORD *));

   /* Allocate arrays to hold the count and bit length of each (potential) symbol */
   piCount     = (SDWORD *)FNX_MALLOC(pNGramTree->iNumNGrams * sizeof(SDWORD));
   piBitLength = (SDWORD *)FNX_MALLOC(pNGramTree->iNumNGrams * sizeof(SDWORD));
   /* Calculate the code lengths of the currently-used symbols */
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
   for (i=0; i<pNGramTree->iNumUsed; i++)
      piCount[i] = piBitLength[i] = ppNGrams[i]->iCount;
   CalculateCodeLengths(piBitLength, (SDWORD)pNGramTree->iNumUsed);
#ifdef USE_WINDOWS
      SendMessage( GetDlgItem( g_hDlg, IDC_PROGRESS1 ), PBM_STEPIT, 1, 0 );
#endif
   for (i=0; i<pNGramTree->iNumUsed; i++)
      ppNGrams[i]->wBitLength = (SWORD)piBitLength[i];

   /* Calculate total bit length, and, since this is the first pass, let this be the best so far. */
   iBestBitLength = IntegerVectorMultiply(piCount, piBitLength, pNGramTree->iNumUsed);
   
   /* Any NGrams that don't pan out are moved to end.  
      iNumPotentialNGrams is how many there are that have not been checked (plus those that are used). */
   //pNGramTree->iNumPotential = pNGramTree->iNumNGrams; 

   /* Sort the "potential" NGrams by count, with largest first.
      Set iNumPotential to the position of the first NGram with count==1,
      since no NGrams with a count of 1 can help. */
#ifdef BUILD_DCC_PROJECT
   printf("    Sorting NGrams by count...\n");
#endif
   pNGramTree->iNumPotential = SortNGramsByCount(pNGramTree);

#ifdef DEBUG_HUFFMAN
   printf("Before we start selecting:\n");
   DumpNGramTree(pNGramTree);//
#endif
   iLastMaxBitsSaved=-1; /* => Don't use this */
   bDone=FALSE;
#ifdef BUILD_DCC_PROJECT
   printf("    Deciding which NGrams are best to use (while used<potential)...\n");
#endif
#ifdef USE_WINDOWS
   ClearProgressIndicator( g_hDlg );
   SetDlgItemText( g_hDlg, IDC_STATIC_PROGRESS, (LPCTSTR)"Deciding which NGrams to use..." );
	EnableWindow( GetDlgItem( g_hDlg, IDSTOP ), TRUE );
#endif

   while (pNGramTree->iNumUsed < pNGramTree->iNumPotential && !bDone)
   {
      /* There are still NGrams to check, so find the one that would remove
         the most bits (without yet worrying about how many more will be added by 
         putting the NGram's symbol back in). */
#ifdef BUILD_DCC_PROJECT
      printf("      %d < %d... \r", pNGramTree->iNumUsed, pNGramTree->iNumPotential);
#endif
#ifdef USE_WINDOWS
   wsprintf( szMsg, "%d used < %ld potential", pNGramTree->iNumUsed, pNGramTree->iNumPotential );
   SetDlgItemText( g_hDlg, IDC_STATIC_EVALUATION, (LPCTSTR)szMsg );
	if( ButtonClicked( GetDlgItem( g_hDlg, IDSTOP )))
	{
		EnableWindow( GetDlgItem( g_hDlg, IDSTOP ), FALSE );
		break;
	}
#endif

      for (i=pNGramTree->iNumUsed; i<pNGramTree->iNumPotential; i++)
      {
         /* Calculate how many bits would be saved by using ppNGrams[i] as a symbol */
         iBitsSaved = 0;
         for (pNGram=ppNGrams[i]; pNGram; pNGram=pNGram->pParent)
         {
            /* See how many bits are saved from this symbol in the NGram */
            FNX_ASSERT(pNGram->wSymbol >= 0 && pNGram->wSymbol < pNGramTree->wNumSymbols);
            iBitsSaved += ppNGrams[i]->iCount * (SDWORD)pNGramTree->ppSymbolNGrams[pNGram->wSymbol]->wBitLength;
         } /* For ppNGrams[i] and its ancestors */

         if (iBitsSaved==iLastMaxBitsSaved && iLastMaxBitsSaved>0)
         {
            /* If we already found iMaxBitsSaved last time around, and
               then the "best" NGram didn't help, then the bit lengths
               of the symbol's codes didn't change, so we know there is
               nothing better than "iMaxBitsSaved", so once we find one
               that matches it, break immediately instead of wasting time
               going through the whole "for i" loop.  (This sped the search 
               in 16-bit mode up by about 12 times for one vocab file). */
            FNX_ASSERT(iBitsSaved==iLastMaxBitsSaved); // Shouldn't be greater or we would have chosen it last time.
            iBestNGram = i;
            break;
         }
         /* See if we have found a new best NGram (or if this is the first one) */
         if (i==pNGramTree->iNumUsed/*first one*/ || iBitsSaved > iMaxBitsSaved/*improvement*/)
         {
            iMaxBitsSaved= iBitsSaved;
            iBestNGram = i;
         }
      }  /* for i */

      if (iMaxBitsSaved < ((pNGramTree->wNumSymbols+1 > 255)?16:8)*3 + 32) /* i.e., a count and two indices and a pointer */
      {
         /* An NGram requires at least a 4-byte (32-bit) pointer and three 8-bit indices
            (16-bit if wNumSymbols>255).  So if the most bits that can be removed (without
            yet even taking into account the additional bits added in their place) is
            not even that much, then no further progress will be possible. */
#ifdef DEBUG_HUFFMAN
         printf("Max total bit length of any NGram is %d bits, which is less than the %d bit\n",iMaxBitsSaved,
            ((pNGramTree->wNumSymbols+1 > 255)?16:8)*3 + 32);
         printf("  overhead for adding any NGram, so we've run out of possibilities.\n");
#endif
         bDone=TRUE;
         break;
      }
      /* Now, more carefully calculate how much storage will be used by
         employing the best NGram.  This is done by building the array piCount[]
         of counts of each of the current symbol AFTER the NGram's symbols
         have their counts decremented by NGram's count. */
      /* First initialize piCount[] with the counts of the current symbols. */
      for (i=0; i<pNGramTree->iNumUsed; i++)
         piCount[i] = ppNGrams[i]->iCount;
      /* Next, subtract the NGram's count from all of its subsymbols.
         e.g., if an NGram "aba" happens 10 times, subtract 10 from "a", then "b", then "a"
         again, since this NGram will replace 20 occurances of "a" and 10 occurances of "b". */
      for (pNGram=ppNGrams[iBestNGram], iN=0; pNGram; pNGram=pNGram->pParent, iN++)
      {
         /* See how many bits are saved from this symbol in the NGram */
         FNX_ASSERT(pNGram->wSymbol >= 0 && pNGram->wSymbol < pNGramTree->wNumSymbols);
         FNX_ASSERT(pNGramTree->ppSymbolNGrams[pNGram->wSymbol]->iPosition>=0 && pNGramTree->ppSymbolNGrams[pNGram->wSymbol]->iPosition < pNGramTree->iNumUsed);
         /* pNGram->wSymbol is one of the symbols that make up the NGram */
         /* ppSymbolNGrams[pNGram->wSymbol] is the NGram for that symbol. */
         /* ...->wIndex is where in the sorted ppNGrams list that symbol's count is copied. */
         /* ppNGrams[iBestNGram]->iCount is how many times the NGram containing pNGram->wSymbol occured,
            so decrement the former by the latter's count. */
         piCount[pNGramTree->ppSymbolNGrams[pNGram->wSymbol]->iPosition] -= ppNGrams[iBestNGram]->iCount;
      } /* For ppNGrams[i] and its ancestors */
      piCount[pNGramTree->iNumUsed] = ppNGrams[iBestNGram]->iCount;
      /* Do an insertion sort on the counts, since they are mostly in the right order
         except for a few that have changed. */
      InsertionSort(piCount, pNGramTree->iNumUsed+1);
      for (iNumZero=0; iNumZero<pNGramTree->iNumUsed+1 && piCount[iNumZero]==0; iNumZero++)
         ;

      /* Copy the list into piBitLength so it can be altered */
      memcpy(piBitLength, &(piCount[iNumZero]), sizeof(SDWORD) * (pNGramTree->iNumUsed+1-iNumZero));
      /* Calculate the number of bits each symbol will take in the Huffman encoding */
      iMaxBitLength = CalculateCodeLengths(piBitLength, (SDWORD)(pNGramTree->iNumUsed+1-iNumZero));
      /* Calculate the total number of bits all symbols will take in the Huffman encoding */
      iBitsUsed = IntegerVectorMultiply(&(piCount[iNumZero]), piBitLength, pNGramTree->iNumUsed+1-iNumZero);
      /* Add in the amount of storage required for the NGram definitions.  If there will be
         > 255 symbols (with the addition of a new one), then we must use two bytes to
         reference each symbol.  Otherwise, we can get away with one byte per symbol.
         So we need #bits used + (1 or 2)bytes for each NGram index (and 'n' of each NGram)
         plus 4 bytes for each NGram for the table that shows where each NGram begins.
         Either way, we need an additional 4 bytes for the pointer to the array of NGrams.*/
      iBitsUsed += (iNumSymbolReferences + iN + 1) * // Total (proposed) number of NGram indices
         ((pNGramTree->wNumSymbols+1 > 255)?16:8) +  // Number of bits per NGram index
         32 * (pNGramTree->wNumSymbols+1-pNGramTree->wNumLiterals); // bits for pointers to all NGrams.
      //printf("%d bits used with NGram; %d bits used without\n", iBitsUsed, iBestBitLength);
      /* See if this NGram would improve storage.  But don't use any NGrams that would result
         in a symbol with > 32 bits in its code.  And don't use any NGram with N>=255, since
         we may need to use a single byte to say how long the NGram is. */
      if (iBitsUsed < iBestBitLength && iMaxBitLength <= 32 && iN<255)
      {
         /* We will use less bits if we employ this NGram, so now actually add it.
            If an NGram "abb" happens 10 times (5 as "abb." and 5 as "abba."), then
            it will replace 10 occurances each of its 'ancestors', "ab" and "a"; as
            well as 10 occurances each of its 'descendants', "bb" and "b".  If the
            new symbol "c" is defined as "c=abb", then in essence we are removing
            5 of "abb." and "abba." from the NGram tree, and inserting 5 of "c." and "ca."
            back into it.  We could proceed by doing those removals (removing any NGrams
            that reach a count of 0) and then insert the new NGrams (or vice-versa),
            but we can be a bit more efficient, since the NGram subtree beginning at
            this NGram's node is identical to the top-level subtree we need for the
            new NGram.  Also, the subtree beginning at the end of the NGram is the
            same as is needed for the new one.*/
         pNGram = ppNGrams[iBestNGram]; /* pNGram is the NGram which is going to become a new top-level symbol */
         
         /* 1. Record this NGram's information, i.e., its "N" and its list of sub-symbols. */
         /* Now allocate an array to hold the number and indices of symbols in this NGram. */
         pwNGramDef = pNGramTree->ppwNGrams[pNGramTree->wNumSymbols - pNGramTree->wNumLiterals] = (SWORD *)FNX_MALLOC((iN+1)*sizeof(SWORD));
         pwNGramDef[0] = (SWORD)iN; /* First element holds size of array */
         for(pNGram=ppNGrams[iBestNGram]; pNGram; pNGram=pNGram->pParent) /* Copy symbol indices into array */
         {
            FNX_ASSERT(iN>=1);
            pwNGramDef[iN--] = pNGram->wSymbol;
         }
         /* Keep track of how many symbol references have been stored total (and include the [0] element)*/
         iNumSymbolReferences += pwNGramDef[0]+1;
         
         /* 2. To remove all suffixes of the NGram (e.g., for "abcd", to remove "bcd", "cd" and "d" due to the NGram):
               From the NGram up to all of its ancestors except the top-level one, (e.g., for "abc", do "c" and "b")
                a) Start at the ancestor's symbol's top-level NGram tree
                b) Subtract the NGram's count from symbols as you follow the tree down the NGram's symbols.
                c) When you reach the NGram's last symbol, recursively traverse
                   all corresponding descendants in both trees, subtracting the count
                   of the NGram's descendant from the other one's corresponding descendant.
                d) Remove any subtrees whose counts become 0. */
         pNGram = ppNGrams[iBestNGram];
         pSuffixList=NULL; /* List of symbols you have to follow to reach the end of the NGram 
                              (for step 'b').  e.g., for "abcd", as pSuffixStart=d, c, b; 
                              pSuffixList will contain "d", "c->d", "b->c->d", 
                              respectively (so at "b" you have to follow "c" and "d" before
                              recursively following all descendants). (First element is skipped, though)*/
         for (pSuffixStart=pNGram; pSuffixStart && pSuffixStart->pParent; pSuffixStart=pSuffixStart->pParent)
         {
            /* Add a pointer to the current part of the NGram to a list 
               so that we know which links to follow when doing part (b). */
            InsertLink(pSuffixStart, &pSuffixList, pNGramTree->pLinkPool);
            /* Find the top-level NGram tree for the symbol at pSuffix->wSymbol */
            pOtherNGram = pNGramTree->ppSymbolNGrams[pSuffixStart->wSymbol]; /* ==((NGramNodePtr)(pSuffixList->p))->wSymbol */
            ppPrev = NULL; /* No parent or sibling to pOtherNGram yet */
            for (pLink=pSuffixList; pLink; pLink=pLink->pNext)
            {
               /* pOtherNGram has already been set, either by initialization or
                  by the previous loop */
               /* Subtract the NGram's count from the corresponding node in the suffix's tree 
                  (because if the NGram "abcd" happened M times, so did the suffix "bcd" ) */
               SubtractCount(pNGramTree, pOtherNGram, pNGram->iCount, ppPrev);
               if (pOtherNGram->iCount==0)
               {
                  pOtherNGram = NULL;
                  break; /* Break out of pLink loop, since we have removed all following
                            nodes that we were going to visit. */
               }
               else if (pLink->pNext)
               {
                  /* This is not the end of the NGram yet, so go to pOtherNGram's child
                     corresponding to the next node in the NGram itself */
                  pFollow = (NGramNodePtr)pLink->pNext->p;
                  ppPrev = &pOtherNGram->pChildren;
                  for (pChild = pOtherNGram->pChildren; pChild; pChild=pChild->pNext)
                  {
                     if (pChild->wSymbol == pFollow->wSymbol)
                        break;
                     ppPrev = &pChild->pNext;
                  }
                  FNX_ASSERT(pChild); /* Make sure we found the symbol of the NGram in pOtherNGram's list of children. */
                  pOtherNGram = pChild;
                  /* ppPrev now contains the address of the pointer that points at pOtherNGram */
                  FNX_ASSERT(*ppPrev == pOtherNGram);
               }
               //else break; // This will happen naturally as pLink=pLink->pNext(==NULL) terminates the loop
            }  /* for pLink */
            /* At this point, pOtherNGram points at the symbol in the other tree corresponding to NGram 
               (i.e., its ending symbol).  Now recursively follow all descendants and subtract the
               count of each of NGram's descendants from pOtherNGram's corresponding descendants. */
            if (pOtherNGram)
               SubtractDescendants(pNGramTree, pNGram, pOtherNGram);
         }  /* for each 'suffix' of the NGram (e.g., "bcd", "cd", "d" of "abcd") */

         /* 3. To remove all occurances of the NGram and its prefixes (e.g., for "abcd",
               to remove all occurances of "abcd" as well as "abc", "ab" and "a" due to "abcd"...)
               For each NGram g in the entire tree, if g->symbol==NGram's (last) symbol,
                a) Follow NGram's ancestors and g's ancestors until NGram's ancestors run out.
                   (let g's ancestor at that point be 'a'.  a's symbol is the first symbol of the NGram.)
                b) If we matched ancestors all the way back to a, then g represents the end
                   of either the original NGram (i.e., g=NGram) or the NGram embedded in another tree, 
                   so:
                   i) Remove g from its parent's list of children
                   ii) Subtract NGram's count from g->parent back to a (but not from g itself)
                   iii) Insert g into the siblings of a (which will be the top-level symbols if g==NGram)
               However, don't do this until the end when g==NGram, because we need to keep
               NGram around for comparisons until then. */
         do
         {
            iMinPosition = pNGramTree->iNumNGrams;
            for (i=0; i<pNGramTree->iNumNGrams; i++)
            {
               if (i!=pNGram->iPosition) /* Don't promote pNGram itself until done with others */
               {
                  NGramNodePtr pNGramParent, pOtherParent;
                  /* See if ppNGrams[i] ends with pNGram (by seeing if they have the same
                     symbols all the way up to where pNGram's parents run out) */
                  pNGramParent=pNGram;
                  pOtherParent=ppNGrams[i];
                  while (pNGramParent && pOtherParent && pNGramParent->wSymbol==pOtherParent->wSymbol)
                  {
                     pNGramParent = pNGramParent->pParent;
                     pOtherParent = pOtherParent->pParent;
                  }
                  if (pNGramParent==NULL)
                  {
                     /* We matched along the entire NGram, so ppNGrams[i] is an NGram
                        that ends with pNGram's symbols, so do (i)-(iii) above.
                        Flag the fact that we made a change so we know we probably need
                        to check the NGrams again. */
                     iTempMinPosition = PromoteNGram(pNGramTree, ppNGrams[i], pNGram, pNGramTree->wNumSymbols);
                     if (iTempMinPosition < i && iTempMinPosition < iMinPosition)
                        iMinPosition = iTempMinPosition;
                     else i--; /* Recheck the current position in case something moved into its spot */
                  }
               }  /* if not pNGram itself */
            }  /* for each NGram node i */
         } while(iMinPosition < pNGramTree->iNumNGrams);

         /* We have now examined all other NGram nodes to see if pNGram is a subset of any of them,
            and all such occurances have been replaced. */
         /* Now promote pNGram itself, and add it as a new symbol */
         PromoteNGram(pNGramTree, pNGram, pNGram, pNGramTree->wNumSymbols);
         pNGramTree->wNumSymbols++;

         /* Calculate the new code lengths of the currently-used symbols */
         for (i=0; i<pNGramTree->iNumUsed; i++)
            piCount[i] = piBitLength[i] = ppNGrams[i]->iCount;
         CalculateCodeLengths(piBitLength, (SDWORD)pNGramTree->iNumUsed);
         for (i=0; i<pNGramTree->iNumUsed; i++)
            ppNGrams[i]->wBitLength = (SWORD)piBitLength[i];
         
         /* Make sure that the true bit length is what we already calculated. */
         FNX_ASSERT(iBitsUsed == (i=IntegerVectorMultiply(piCount, piBitLength, pNGramTree->iNumUsed)
                             + iNumSymbolReferences * ((pNGramTree->wNumSymbols > 255)?16:8)
                             + 32 * (pNGramTree->wNumSymbols-pNGramTree->wNumLiterals)));
#ifdef DEBUG_HUFFMAN
         // Dump the tree while we debug.
         printf("\n\n[%d symbols, %d potential:]\n", (SDWORD)pNGramTree->wNumSymbols, pNGramTree->iNumPotential);
         DumpNGramTree(pNGramTree);//

         /* Print info about our new symbol */
         printf("%d/%d; New symbol #%d.  %4d occurances. %d bits -> %d bits: ", pNGramTree->iNumUsed,
            pNGramTree->iNumPotential, pNGramTree->wNumSymbols-1, pNGramTree->ppSymbolNGrams[pNGramTree->wNumSymbols-1]->iCount,
            iBestBitLength, iBitsUsed);
         DumpSymbolName(pNGramTree, (SWORD)(pNGramTree->wNumSymbols-1));
         printf("\n");         
#endif
         /* Update the best bit length */
         iBestBitLength = iBitsUsed;

         if (pNGramTree->wNumSymbols==255)
         {
            /* We've used all the symbols we can for 8-bit indexing, so create a Huffman
               table structure based on the current state of things in case we cannot
               improve on things using 16-bit indexing (i.e., if the further gains from
               using additional NGrams are offset by the larger indexing storage) */
            pHuffman = NGramToHuffman(pNGramTree);
            i8BitSize = iBitsUsed;
#ifdef DEBUG_HUFFMAN
            DumpNGramTree(pNGramTree);//
            printf("===========\nBest Huffman encoding up to 8 bits: %d bits\n", i8BitSize);
            /* Now change "iBestBitLength" so that it is the size it would be if
               16-bit indices were used.  That way incremental improvements are still
               allowed without any single NGram having to overcome the large "hit" we
               take when we go from 8 to 16 bits. */
            iBestBitLength += iNumSymbolReferences * 8;
            printf("  Moving best bit length from %d to %d to reflect 16-bit indexing\n", iBitsUsed, iBestBitLength);
            printf("------------\n\n");
#endif
         }
         iLastMaxBitsSaved = -1; /* We just recomputed bit lengths, so we don't know what the max is anymore. */
      }
      else
      {
         /* We don't save memory by using this NGram, so put it at the end of the
            list so we won't check it again. */
         llistPtr pTempList;///
#ifdef DEBUG_HUFFMAN
         pTempList=NULL;
         printf("%d<%d; [%d>",pNGramTree->iNumUsed, pNGramTree->iNumPotential, iBitsUsed);
         if (pNGramTree->wNumSymbols>=255)
         {
            printf("8:%d/16:%d]", i8BitSize, iBestBitLength);
         }
         else printf("%d]", iBestBitLength);
         printf("; NGram no help: cnt=%d, pos=d: ",pNGramTree->ppNGrams[iBestNGram]->iCount, iBestNGram);
#endif
         for (pNGram=ppNGrams[iBestNGram]; pNGram; pNGram=pNGram->pParent) // build list of symbols in NGram
            InsertLink((voidPtr)((SDWORD)pNGram->wSymbol), &pTempList, pNGramTree->pLinkPool);
#ifdef DEBUG_HUFFMAN
         while (pTempList) // print symbols in correct order
         {
            FNX_ASSERT(pTempList);
            DumpSymbolName(pNGramTree,(SWORD)((SDWORD)pTempList->p));
            if (pTempList->pNext)
               printf(" ");
            RemoveLink(&pTempList, pNGramTree->pLinkPool);
         }
         printf("\n");///
#endif
         FNX_ASSERT(ppNGrams[iBestNGram]->iPosition >= pNGramTree->iNumUsed && ppNGrams[iBestNGram]->iPosition < pNGramTree->iNumPotential);//or we shouldn't have checked.
         FNX_ASSERT(pNGramTree->iNumPotential > pNGramTree->iNumUsed);
         SwapNGrams(ppNGrams, iBestNGram, --pNGramTree->iNumPotential);
         /* We didn't change the bit lengths, and no NGram covered more bits than 'iMaxBitsSaved',
            so if we find one in the list that matches that, go ahead and use it. */
         iLastMaxBitsSaved = iMaxBitsSaved;
      }

   }  /* while there are NGrams to check*/

#ifdef DEBUG_HUFFMAN
   printf("Done checking NGrams.\n");
   DumpNGramTree(pNGramTree);//
#endif
#ifdef USE_WINDOWS
   SetDlgItemText( g_hDlg, IDC_STATIC_EVALUATION, (LPCTSTR)"" );
	EnableWindow( GetDlgItem( g_hDlg, IDSTOP ), FALSE );
#endif

   if (pNGramTree->wNumSymbols >= 255)
   {
      /* Had at least 255 symbols, so we already built pHuffman for 8-bit indices. */
#ifdef DEBUG_HUFFMAN
      printf("Best 8-bit size:  %d bits\n", i8BitSize);
      printf("Best 16-bit size: %d bits\n", iBestBitLength);
      printf("  => using %d-bit Huffman table\n", i8BitSize<=iBestBitLength ? 8 : 16);
#endif
      if (iBestBitLength < i8BitSize)
      {
         /* We were able to use less bits by using longer indices and more NGrams,
            so free up the 8-bit Huffman table and create a 16-bit one. */
         FreeHuffman(pHuffman);
         pHuffman = NGramToHuffman(pNGramTree);
      }
   }
   else
   {
      /* Didn't get up to 255 symbols yet, so 8-bit pHuffman was not yet built */
      pHuffman = NGramToHuffman(pNGramTree);
   }
   FreeAndClear((void **)&piCount);
   FreeAndClear((void **)&piBitLength);

   return pHuffman;
}  /* SelectNGrams */
#endif

         
/*FUNCTION_HEADER**********************
 * NAME:    ;InsertNGramIndices
 * DESC:    Recursively expand an NGram and insert its symbol indices into a linked list.
 * IN:      wSymbol  - Index of NGram symbol to expand
            ppList   - Linked list to add literal symbol indices to
            pHuffman - Structure containing information about NGrams, etc.
            pbDone   - Address of flag to set if the end symbol is encountered.
 * OUT:     *ppList has all of the literal symbols (except wEndSymbol) in uiIndex's NGram added to it.
            *pbDone is set to TRUE if wEndSymbol is encountered.
 * RETURN:  n/a
 * NOTES:   Calls itself recursively if an NGram has a list of symbols that includes another NGram.
 *END_HEADER***************************/
void InsertNGramIndices(SWORD wSymbol, llistPtr *ppList, HuffmanPtr pHuffman, BOOL *pbDone)
{
   SWORD w, wCount, *pwNGrams;
   FNX_ASSERT(wSymbol >= pHuffman->wNumLiterals);

   pwNGrams = pHuffman->ppwNGrams[wSymbol - pHuffman->wNumLiterals];
   wCount   = pwNGrams[0];
   FNX_ASSERT(wCount>0);
   for (w=1; w<=wCount; w++)
   {
      FNX_ASSERT(!(*pbDone));
      wSymbol = pwNGrams[w];
      if (wSymbol >=  pHuffman->wNumLiterals)
         InsertNGramIndices(wSymbol, ppList, pHuffman, pbDone);
      else if (wSymbol == pHuffman->wEndSymbol)
         *pbDone = TRUE;
      else InsertLink((voidPtr) ((SDWORD)wSymbol), ppList, pHuffman->pLinkPool);
   }
}  /* InsertNGramIndices */


/*FUNCTION_HEADER**********************
 * NAME:    ;BuildHuffmanCodeStrings
 * DESC:    Build strings for each Huffman symbol.
 * IN:      pHuffman - Huffman structure to be modified.
 * OUT:     pHuffman->psCodeStrings[wSymbol] contains the bit string (e.g., "011") for
              each symbol.
 * RETURN:  n/a
 * NOTES:   psCodeStrings[wSymbol]=NULL if wSymbol is not "used".
 *END_HEADER***************************/
void BuildHuffmanCodeStrings(HuffmanPtr pHuffman)
{
   SDWORD iTable, iPosition, iStringPosition;
   UDWORD uiCodeLength, uiBase, uiPattern;
   SWORD  wSymbol;
   if (pHuffman->psCodeStrings)
      return; /* Already generated */

   /* Allocate an (empty) array of pointers to point to the strings as they are generated */
   pHuffman->psCodeStrings = (char **)FNX_CALLOC(pHuffman->wNumSymbols, sizeof(char *));

   /* Handle the symbols in each table one at a time */
   for (iTable=0; iTable<pHuffman->iNumTables; iTable++)
   {
      uiCodeLength = pHuffman->pTables[iTable].uiCodeLength;
      /* Set 'uiBase' to the bit pattern of the first symbol in the table (left-padded with zeroes)*/
      uiBase = pHuffman->pTables[iTable].uiStart >> (pHuffman->cMaxCodeLength - uiCodeLength);

      /* Allocate a string for each of the symbols in the table */
      for (iPosition = pHuffman->pTables[iTable].uiFirstSymbol; iPosition < pHuffman->wNumUsed && 
           (UDWORD)pHuffman->pcCodeLengths[pHuffman->pwSymbolIndices[iPosition]]==uiCodeLength; iPosition++)
      {
         /* Get the symbox index so we know where to put the string */
         wSymbol = pHuffman->pwSymbolIndices[iPosition];
         /* Put the symbol's pattern into the rightmost bits of uiPattern */
         uiPattern = (SDWORD)uiBase + iPosition - (SDWORD)pHuffman->pTables[iTable].uiFirstSymbol;
         /* Allocate an array of characters, one per bit, plus a null terminator */
         FNX_ASSERT(pHuffman->psCodeStrings[wSymbol]==NULL);
         pHuffman->psCodeStrings[wSymbol] = (char *)FNX_CALLOC(uiCodeLength+1, sizeof(char));
         /* Set the characters to "0" or "1" for each bit */
         for (iStringPosition=uiCodeLength-1; iStringPosition>=0; iStringPosition--)
         {
            /* Set a character to "0" or "1" depending on the rightmost bit of uiPattern */
            pHuffman->psCodeStrings[wSymbol][iStringPosition] = (char)(uiPattern&1 ? '1' : '0');
            /* Shift uiPattern right by one bit to put the next bit in the rightmost position */
            uiPattern >>= 1;
         }  /* for each bit in the symbol's pattern */
      }  /* for each symbol in the table */
   }  /* for each table */
}  /* BuildHuffmanCodeStrings */


/*FUNCTION_HEADER**********************
 * NAME:    ;HuffmanEncode
 * DESC:    Do Huffman encoding on an array of indices
 * IN:      pHuffman       - Structure containing information on how to encode the symbols
            pNGramTree     - Structure containing information about the symbols needed to determine NGrams.
            pwSymbolStream - Array of (literal) symbol indices to be encoded
            iNumUsed       - Number of elements in pwSymbolIndicies[]
            piNumBytes     - Address in which to return the number of bytes in the returned buffer.
 * OUT:     
 * RETURN:  Pointer to a newly-allocated array of symbol indices derived from bit stream,
            or NULL on error.
 * NOTES:   Least significant bit in first byte is used first. (i.e., pBytes[0] & 0x01).
            Bytes are read until the end-of-string symbol (i.e., the one that yields the
              index of the symbol that is NULL) is found in the bit stream.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
UBYTE *HuffmanEncode(HuffmanPtr pHuffman, SWORDPTR pwSymbolStream, SDWORD iNumIndices, SDWORD *piNumBytes)
{
   SDWORD iPosition; /* Position in pwSymbolStream[] of first symbol that still needs to be encoded */
   SWORD wNGram, wNumNGrams, wFirstSymbol, wSymbol, wN, w;
   llistPtr pList, pLink, pLink2;
   SDWORD iNumBits, iBit;
   UBYTE *pucBuffer, *pucByte;
   char *pc;
   int i;

   if (pHuffman->psCodeStrings == NULL)
      BuildHuffmanCodeStrings(pHuffman);
#ifdef DUMP_ENCODING
   int j;
   printf("    Symbols: ");///...
   for (i=0; i<iNumIndices; i++)
      printf(" %3s", pHuffman->psLiterals[pwSymbolStream[i]]);
   printf("\n    Indices: ");
   for (i=0; i<iNumIndices; i++)
      printf(" %3d", pwSymbolStream[i]);
   printf("\n");///
#endif

   /* Create a linked list of the symbols so we can modify it if needed */
   pList=NULL;
   /* Insert the end-of-string symbol onto the end of the list */
   if (pwSymbolStream[iNumIndices-1] != pHuffman->wEndSymbol)
      InsertLink((voidPtr)((SDWORD)pHuffman->wEndSymbol), &pList, pHuffman->pLinkPool);
   /* Insert the rest of the symbols (starting with the last one so the list will be in forward order) */
   for (iPosition=iNumIndices-1; iPosition>=0; iPosition--)
      InsertLink((voidPtr)((SDWORD)pwSymbolStream[iPosition]), &pList, pHuffman->pLinkPool);

   /* For each NGram, see if there are any matches that need to be substituted.
      Start with first NGrams added, since later NGrams may be based on them. */
   wNumNGrams = pHuffman->wNumSymbols - pHuffman->wNumLiterals;
   for (wNGram=0; wNGram < wNumNGrams; wNGram++)
   {
      wFirstSymbol = pHuffman->ppwNGrams[wNGram][1];
      for (i=0, pLink=pList; pLink; pLink=pLink->pNext, i++)
      {
         wSymbol = (SWORD)((SDWORD)pLink->p);
         if (wSymbol == wFirstSymbol)
         {
            wN = pHuffman->ppwNGrams[wNGram][0];
            for(w=2, pLink2=pLink->pNext; w <= wN && pLink2; w++, pLink2=pLink2->pNext)
            {
               if (pHuffman->ppwNGrams[wNGram][w] != (SWORD)((SDWORD)pLink2->p))
                  break; /* Found a mismatch */
            }
            if (w==wN+1)
            {
               /* Didn't find a mismatch, so wNGram matches the symbols starting at pLink. */
               /* So put the NGram in pLink and delete the rest of the match symbols after that */
               pLink->p = (voidPtr)((SDWORD)wNGram+pHuffman->wNumLiterals);
               for (w=2; w <= wN; w++)
                  RemoveLink(&pLink->pNext, pHuffman->pLinkPool);
               /* We know that no NGram can use itself or any later NGram as part of itself,
                  so pLink itself need not be considered for use in wNGram nor in preceding
                  NGrams.  Thus, it is ok to let "pLink=pLink->pNext" proceed as usual in the for loop. */
#ifdef DUMP_ENCODING
               printf("  NGram %3d: ",wNGram+pHuffman->wNumLiterals);///
               for (j=0, pLink2=pList; pLink2; pLink2=pLink2->pNext, j++)///
               {
                  printf(" %3d", (SDWORD)(pLink2->p));///
                  if (j==i)
                  {
                     int k;///
                     for (k=1; k<pHuffman->ppwNGrams[wNGram][0]; k++)
                        printf("  <-");
                  }
               }
               printf("\n");///
#endif
            }  /* if we found a match */
         }  /* if the first symbol matches the NGram */
      }  /* for each symbol in the list */
   }  /* for each NGram */

   /* pList now contains a list of the symbols after NGram substitutions have been made. */
   /* Now count how many bits (and thus how many bytes) we will need */
   iNumBits=0;
   for (pLink=pList; pLink; pLink=pLink->pNext)
   {
      wSymbol = (SWORD)((SDWORD)pLink->p);
      FNX_ASSERT(pHuffman->pcCodeLengths[wSymbol]>0); // No unused symbols should remain here.
      iNumBits += pHuffman->pcCodeLengths[wSymbol];
   }  /* for pLink: counting bits */
   *piNumBytes = (iNumBits+7)>>3; /* Divide by 8 but round up to get the number of bytes needed */
   
   pucBuffer = (UBYTE *)FNX_CALLOC(*piNumBytes, sizeof(UBYTE));
   pucByte = pucBuffer;
   iBit=7;
#ifdef DUMP_ENCODING
   printf("  Encoding: ");///
#endif
   for (pLink=pList; pLink; pLink=pLink->pNext)
   {
      wSymbol = (SWORD)((SDWORD)pLink->p);
      FNX_ASSERT(pHuffman->psCodeStrings[wSymbol] && FNX_STRLEN(pHuffman->psCodeStrings[wSymbol]) == (UDWORD)pHuffman->pcCodeLengths[wSymbol]);
      for (pc = pHuffman->psCodeStrings[wSymbol]; *pc; pc++)
      {
         if (iBit<0)
         {
            pucByte++; /* Advance to the next byte in the buffer */
            iBit=7; /* Start over at the last bit */
         }
         /* Shift the byte one bit to the left to make room for the new bit. */
         (*pucByte) <<= 1;
         /* Set the rightmost bit if the code string contains a '1' (else leave it 0) */
         if (*pc == '1')
            *pucByte |= 1;
#ifdef DUMP_ENCODING
         if (*pc == '1')///
            printf("1");///
         else printf("0");///
#endif
         iBit--;
      }
#ifdef DUMP_ENCODING
      printf(" ");///
#endif
   }  /* for pLink: Encoding bits */
   /* Shift the last byte to the left if needed so that it is right-padded with 0's (instead of left-padded) */
   if (iBit>=0)
      (*pucByte) <<= (iBit+1);

#ifdef DUMP_ENCODING
   printf("\n   %d bits => %d bytes: ", iNumBits, *piNumBytes);
   for (i=0; i<*piNumBytes; i++)
      printf("%2X ", (UDWORD)pucBuffer[i]);
   printf("\n");
#endif
   FreeList(&pList, pHuffman->pLinkPool);

   return pucBuffer;
}  /* HuffmanEncode */
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;SymbolICmp
 * DESC:    See if a symbol matches the string at its current position.
 * IN:      ppc      - Address of a pointer into a string to be matched.
            sSymbol  - Pointer to the name of the (literal) symbol (e.g., "a" or "oU").
 * OUT:     *ppc is advanced beyond any matching characters within sSymbol.
 * RETURN:  -1 if the string beginning at pc < sSymbol (or if pc is shorter than sSymbol).
             0 if pc matches sSymbol
            +1 if pc > sSymbol.
 * NOTES:   A lot like stricmp(*pc,sSymbol) or strnicmp(*pc,sSymbol,strlen(sSymbol)),
            except that pc is advanced past the matching character(s),
            and it's ok for sSymbol to be shorter than *pc (i.e., the symbol
            is only supposed to match part of the string anyway), but
            if *pc is shorter than sSymbol, then a -1 is returned.
 *END_HEADER***************************/
SDWORD SymbolICmp(char **ppc, char *sSymbol)
{
   char *pc = *ppc;
   SDWORD iCompare=0;
   unsigned char uc1, uc2;
   while (*pc && *sSymbol && iCompare==0)
   {
      uc1 = (unsigned char)FNX_TOLOWER(*pc);
      uc2 = (unsigned char)FNX_TOLOWER(*sSymbol);
      if (uc1<uc2)
         iCompare=-1;
      else if (uc1>uc2)
         iCompare=1;
      else
      {
         iCompare=0;
         pc++;
         sSymbol++;
      }
   }
   *ppc = pc;
   if (iCompare==0 && *sSymbol)
      return -1; /* *ppc is shorter, so it is "less" than sSymbol */
   return iCompare;
}

/*FUNCTION_HEADER**********************
 * NAME:    ;CompareNGram
 * DESC:    Recursively expand an NGram and insert its symbol indices into a linked list.
 * IN:      pc       - Pointer into a string to be matched.
            wSymbol  - Index of NGram symbol to expand
            pHuffman - Structure containing information about NGrams, etc.
            pbDone   - Address of flag to set if the end symbol is encountered.
 * OUT:     *ppList has all of the literal symbols (except wEndSymbol) in uiIndex's NGram added to it.
            *pbDone is set to TRUE if wEndSymbol is encountered.
 * RETURN:  -1 if the string beginning at pc < the string beginning with the given ngram;
             0 if pc matches the ngram
            +1 if pc > the ngram.
 * NOTES:   Calls itself recursively if an NGram has a list of symbols that includes another NGram.
 *END_HEADER***************************/
SDWORD CompareNGram(char **ppc, SWORD wSymbol, HuffmanPtr pHuffman, BOOL *pbDone)
{
   SWORD w, wCount, *pwNGrams;
   SDWORD iCompare=0;

   FNX_ASSERT(wSymbol >= pHuffman->wNumLiterals);
   pwNGrams = pHuffman->ppwNGrams[wSymbol - pHuffman->wNumLiterals];
   wCount   = pwNGrams[0];
   FNX_ASSERT(wCount>0);
   for (w=1; w<=wCount && iCompare==0; w++)
   {
      FNX_ASSERT(!(*pbDone));
      wSymbol = pwNGrams[w];
      if (wSymbol >=  pHuffman->wNumLiterals)
         iCompare = CompareNGram(ppc, wSymbol, pHuffman, pbDone);
      else if (wSymbol == pHuffman->wEndSymbol)
         *pbDone = TRUE;
      else if (**ppc == 0) // Hit end-of-string, but there are still ngram symbols not explained.
         iCompare = -1; // the given string is shorter, so it is "less".
      else iCompare = SymbolICmp(ppc, pHuffman->psLiterals[wSymbol]);
   }
   return iCompare;
}  /* CompareNGram */

/*FUNCTION_HEADER**********************
 * NAME:    ;HuffmanDecode
 * DESC:    Do Huffman decoding on an array of bytes full of bits
 * IN:      sWord    - String to match (and return as soon as there is a mismatch) (NULL=>decode and allocate)
            pHuffman - Structure containing information needed to decode the bits.
            fp       - File to read from (NULL => use pBytes)
            pBytes   - Array of bytes full of Huffman-encoded bits (unknown length) (ignored if fp is non-NULL).
            piBytesRead - Address in which to return the number of bytes read (NULL=>ignore).
            ppwSymbols  - Address in which to return a pointer to the newly-allocated
                            array of symbols. (NULL=>use sWord to just do matching, and don't allocate).
            piListSize  - Address in which to return the number of symbols in the returned array.
 * OUT:     (pHuffman's Linked list pool temporarily has things used from it).
            pBytes is unchanged. An array of SDWORDs is allocated.
 * RETURN:  -1 if sWord<decoded string; 0 if equal; or +1 if sWord>decoded string, or -2 on error.
            Or, if sWord==NULL, return 0 on success, -2 on error.
 * NOTES:   Least significant bit in first byte is used first. (i.e., pBytes[0] & 0x01).
            If ppwSymbols!=NULL, then bytes are read until the end-of-string symbol 
              (i.e., the one that yields the index of the symbol that is NULL) 
              is found in the bit stream.
            If sWord!=NULL, then does comparison and returns as soon as it can determine
              whether sWord matches (i.e., like stricmp(sWord, decoded string)).
            If fp is non-NULL, then it is used.  Otherwise, pBytes is used.            
 *END_HEADER***************************/
SDWORD HuffmanDecode(char *sWord, HuffmanPtr pHuffman, FILE *fp, UBYTE *pBytes, 
                       SDWORDPTR piBytesRead, SWORDPTR *ppwSymbols, SDWORDPTR piListSize)
{
   UBYTE    *p; /* Pointer at the current byte in pBytes[] that we're using */
   UBYTE     c; /* Copy of *p, i.e., actual byte that we're shifting and pulling bits from 
                   (so we don't mess up original array) */
   UDWORD    uiByteBits;    /* How many bits we have already "read" from 'p' */
   UDWORD    uiPatternBits; /* How many bits we have "loaded" into iPattern (from real bytes.
                               Normally goes up to uiLength, but could be less if end of file
                               was hit.)*/
   UDWORD    uiPattern;     /* 4-byte value to be compared with table starting values */
   UDWORD    uiLength;      /* Length of pattern that needs to be compared, i.e., max symbol length */
   UDWORD    uiIndex;       /* Index in the chosen table of the given pattern */
   llistPtr  pList=NULL;    /* Linked list of indices of symbols taken from the bit stream */
   BOOL      bDone=FALSE;
   SDWORD    iTable, i;
   SWORDPTR  pwSymbolIndices;
   SWORD     wSymbol;
   BOOL      bEndOfFile=FALSE; /* Flag for whether we hit the end of file */
   SDWORD    iCompare=0; /* Result of stricmp(sWord,decoded word) so far; always 0 when sWord=NULL */
   char     *pc = sWord;

   /* Grab the first byte */
   if (fp)
   {
      p = NULL;
      c = (UBYTE)FNX_FGETC(fp);
      if (c==EOF)
         goto DecodeError;
   }
   else
   {
      p=pBytes;
      c = *p;
   }
   if (piBytesRead)
      *piBytesRead=1;
   uiByteBits=0; /* Haven't pulled any bits out of c (=*p) yet. */
   uiPatternBits=0; /* Haven't pushed any bits into uiPattern yet. */
   uiLength = (UDWORD)pHuffman->cMaxCodeLength;
   uiPattern = 0; /* Begin with an empty pattern buffer. */
   do
   {
      /* Pull first 'uiLength' bits out of the byte stream into uPattern. */
      /* [Once this works, use cMask[8]={0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80};
         and grab "chunk=min(uiByteBits, uiLength-uiPatternBits)" bits at a time
         instead of one bit at a time */
      while (uiPatternBits < uiLength)
      {
         /* Make sure we have a bit in 'c' we can use */
         if (uiByteBits >= 8) /* eight bits per byte */
         {
            /* Ran out of bits in 'c', so get the next byte */
            if (fp)
            {
               if (bEndOfFile || (c = (UBYTE)FNX_FGETC(fp))==EOF)
               {
                  if (uiPatternBits==0)
                     goto DecodeError; /* No more bits to consume, and no more bytes to read, 
                                          but still haven't found end-of-string symbol */
                  /* We hit the end of the file, so hopefully we've already
                     read the end-of-string symbol.  Shift the 'read' bits
                     to the very left part of uiPatternBits and go see
                     what they are. */
                  uiPattern <<= (uiLength - uiPatternBits);
                  bEndOfFile=TRUE;

                  /* Break out before incrementing *piBytesRead, since we didn't actually
                     read another byte.  Also, leave 'uiPatternBits' less than uiLength,
                     so that uiPatternBits indicates how many bits were actually read
                     from memory into uiPattern (and the rest were just 0-padded). */
                  break;
               }
            }
            else c = *(++p); /* Read byte from memory and get a copy to manipulate */
            
            /* Keep track of how many bytes were read (from the file or memory). */
            if (piBytesRead)
               (*piBytesRead)++;
            uiByteBits=0; /* Reset our counter of how many bits we've grabbed */
         }
         /* Shift uiPattern's bits left one bit. */
         uiPattern <<= 1;
         uiPatternBits++;
         /* Copy the leftmost bit of 'c' into the rightmost bit of uiPattern */
         if (c & 0x80)
            uiPattern |= 0x01;
         /* Shift c left by one bit */
         c <<= 1;
         uiByteBits++;
      }

      /* uiPattern now contains the first 'uiLength' bits of a pattern in its leftmost bits.
         Now see which table that pattern belongs in. (Start search at
         last table so we can use ">=", and also because the last table
         contains the shortest patterns, which are also the most common
         ones, so this makes the search shorter for more common patterns) */
      for (iTable=pHuffman->iNumTables-1; iTable>=0; iTable--)
      {
         if (uiPattern >= pHuffman->pTables[iTable].uiStart)
            break; /* Found the table that this pattern belongs to */
      }
      if (iTable<0)
         goto DecodeError;
      
      /* Subtract the starting symbol from the pattern, and shift
         if this table has patterns with less bits than uiLength,
         and then add this table's offset into the symbol table...*/
      uiIndex = uiPattern - pHuffman->pTables[iTable].uiStart;
      uiIndex >>= (uiLength - pHuffman->pTables[iTable].uiCodeLength);
      uiIndex += pHuffman->pTables[iTable].uiFirstSymbol;
      
      /* Now uiIndex magically contains the index of the symbol */
      if (uiIndex<0 || uiIndex>=(UDWORD)pHuffman->wNumSymbols)
         goto DecodeError;

      /* Translate the index (in pwSymbolIndices[]) into the actual symbol number */
      wSymbol = pHuffman->pwSymbolIndices[uiIndex];

      /* If this is an NGram, add each of its symbols to the list and
         check to see if each one is the end-of-string symbol */
      if (wSymbol >= pHuffman->wNumLiterals)
      {
         /* If we are building a symbol list, add the n-gram's symbols to it */
         if (ppwSymbols)
            InsertNGramIndices(wSymbol, &pList, pHuffman, &bDone);
         /* If we are comparing a string with the decoded symbols,
            compare it with the n-gram's symbols. */
         if (sWord)
            iCompare = CompareNGram(&pc, wSymbol, pHuffman, &bDone);
      }
      
      /* See if (1) we hit the end symbol while inserting the NGram, or (2) this is the literal end symbol */
      if (bDone || wSymbol == pHuffman->wEndSymbol)
      {
         SDWORD iExtraBits;
         bDone=TRUE;
         /* See if we "consumed" more bytes than we needed to (and if so, back up).
              uiPatternBits = #bits read into uiPattern from current byte AND previous bytes,
                              including the bits for the end symbol.
              .uiCodeLength = #bits in uiPatternBits the end symbol used.
              uiByteBits    = #bits in uiPatternBits that came from the current byte.
            So uiPatternBits - .uiCodeLenth - uiByteBits = #extra bits read before current byte.
            And "that+8" = #extra bits read INCLUDING current byte.
            So if we got more than 8 extra bits, we need to back up one or more bytes. */
         iExtraBits = (SDWORD)uiPatternBits - (SDWORD)pHuffman->pTables[iTable].uiCodeLength
                   - (SDWORD)uiByteBits + 8;
         /* If we have 8 or less extra bits, then we were SUPPOSED to read the current
            byte, so we don't need to back up at all. */
         if (iExtraBits>=8)
         {
            SDWORD iExtraBytes = iExtraBits / 8;
            if (fp)
               FNX_FSEEK(fp, -iExtraBytes, SEEK_CUR);
            if (piBytesRead)
               (*piBytesRead) -= iExtraBytes;
         }
      }
      else if (iCompare==0) /* didn't hit end symbol yet */
      {
         /* If building symbol list, add current symbol to the list. */
         if (ppwSymbols && wSymbol < pHuffman->wNumLiterals) /* => wasn't an NGram, so insert the symbol into the list */
            InsertLink((voidPtr)((SDWORD)wSymbol), &pList, pHuffman->pLinkPool);

         /* If comparing sWord, compare with current symbol */
         if (sWord && wSymbol < pHuffman->wNumLiterals) /* => wasn't an NGram, so match the symbol with the string */
            iCompare = SymbolICmp(&pc, pHuffman->psLiterals[wSymbol]);

         /* Now prepare uiPattern to continue to be used by setting the
            bits used by this symbol to 0, and by setting 'uiPatternBits'
            to the number of bits remaining in the pattern that are still to be used. */
         uiPattern &= pHuffman->pTables[iTable].uiPatternMask;
         uiPatternBits -= pHuffman->pTables[iTable].uiCodeLength;
      }
   } while (!bDone && iCompare==0); /* Continue forever until the end-of-string symbol is found,
                                       or a mismatch between sWord and the string is found. */

   if (ppwSymbols)
   {
      if (iCompare!=0)
      {
         /* If doing both decoding AND comparing with sWord, and a mismatch was found,
            then we're stopping early, so free up what we have and put NULL in there. */
         FreeList(&pList, pHuffman->pLinkPool);
         *ppwSymbols=NULL;
      }
      else /* Create *ppwSymbols[]. */
      {
         /* The end-of-string symbol has been found, so convert the linked list
            into an array of symbol indices and return it. */
         *piListSize = ListSize(pList);
         if (pList)
         {
            pwSymbolIndices = (SWORDPTR) FNX_MALLOC(*piListSize * sizeof(SWORD));
            for (i=*piListSize-1; pList; i--)
            {
               pwSymbolIndices[i] = (SWORD)((SDWORD)pList->p);
               RemoveLink(&pList, pHuffman->pLinkPool);
            }
            FNX_ASSERT(i==-1); /* Make sure we read each symbol */
         }
         else 
         {
            /* allocate something just so that the return value won't be NULL,
               which would indicate an error. */
            pwSymbolIndices = (SWORDPTR)FNX_CALLOC(1, sizeof(SWORD));
         }
         *ppwSymbols = pwSymbolIndices;
      }
   }

   /* Make sure we didn't just match a subset of sWord */
   if (sWord && iCompare==0 && *pc!=0)
      iCompare=1; /* sWord was longer than the decoded word, so it is "greater" */
   
   return iCompare;

DecodeError:
#ifdef BUILD_DCC_PROJECT
   if (sWord)
      printf("Error in Huffman decoding (looking for word %s)\n", sWord);
   else printf("Error in Huffman decoding\n");
#endif
   if (pList)
      FreeList(&pList, pHuffman->pLinkPool);
   return -2;
}  /* HuffmanDecode */


/*FUNCTION_HEADER**********************
 * NAME:    ;DecodeUntilMismatch
 * DESC:    Do Huffman decoding on an array of bytes full of bits,
               stopping as soon as it is determined that there is a mismatch.
 * IN:      sWord    - Word to compare with.
            pHuffman - Structure containing information needed to decode the bits.
            fp       - File to read from (NULL => use pBytes)
            pBytes   - Array of bytes full of Huffman-encoded bits (unknown length) (ignored if fp is non-NULL).
            piBytesRead - Address in which to return the number of bytes read (NULL=>ignore).
 * OUT:     (pHuffman's Linked list pool temporarily has things used from it).
            pBytes is unchanged. An array of SDWORDs is allocated.
            piBytesRead is filled with how many bytes were "consumed" from the file or byte stream.
 * RETURN:  stricmp(sWord, decoded string), i.e., -1 if sWord<decoded string, 0 if equal, +1 if sWord>decoded string.
 * NOTES:   If the returned value is 0, then all of the bytes will have been decoded.
            Otherwise, only some of them will, and it is the responsibility of the calling
            function to know where to go next.
 *END_HEADER***************************/
SDWORD DecodeUntilMismatch(char *sWord, HuffmanPtr pHuffman, FILE *fp, UBYTE *pBytes, SDWORDPTR piBytesRead)
{
   return HuffmanDecode(sWord, pHuffman, fp, pBytes, piBytesRead, NULL, NULL);
}

/*FUNCTION_HEADER**********************
 * NAME:    ;DecodeBitStream
 * DESC:    Do Huffman decoding on an array of bytes full of bits
 * IN:      pHuffman - Structure containing information needed to decode the bits.
            fp       - File to read from (NULL => use pBytes)
            pBytes   - Array of bytes full of Huffman-encoded bits (unknown length) (ignored if fp is non-NULL).
            piBytesRead - Address in which to return the number of bytes read (NULL=>ignore).
            piListSize  - Address in which to return the number of symbols in the returned array.
 * OUT:     (pHuffman's Linked list pool temporarily has things used from it).
            pBytes is unchanged. An array of SDWORDs is allocated.
 * RETURN:  Pointer to a newly-allocated array of symbol indices derived from bit stream,
            or NULL on error.
 * NOTES:   Least significant bit in first byte is used first. (i.e., pBytes[0] & 0x01).
            Bytes are read until the end-of-string symbol (i.e., the one that yields the
              index of the symbol that is NULL) is found in the bit stream.
            If fp is non-NULL, then it is used.  Otherwise, pBytes is used.
 *END_HEADER***************************/
SWORDPTR DecodeBitStream(HuffmanPtr pHuffman, FILE *fp, UBYTE *pBytes, SDWORDPTR piBytesRead, SDWORDPTR piListSize)
{
   SWORDPTR pwSymbols;

   HuffmanDecode(NULL, pHuffman, fp, pBytes, piBytesRead, &pwSymbols, piListSize);
   return pwSymbols;
}

/*FUNCTION_HEADER**********************
 * NAME:    ;FreeTokenVocab
 * DESC:    Free up a TokenVocab structure.
 * IN:      pTokenVocab - Tokenized vocabulary to free.
 * OUT:     pTokenVocab is free up.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
void FreeTokenVocab(TokenVocabPtr pTokenVocab)
{
   SDWORD       iWord;
   TokenWordPtr pWord;
   if (pTokenVocab)
   {
      if (pTokenVocab->ppTokenWords)
      {
         for (iWord=0; iWord < pTokenVocab->iNumWords; iWord++)
         {
            pWord = pTokenVocab->ppTokenWords[iWord];
            if (pWord)
            {
               FreeAndClear((void **)&pWord->pwSymbolIndices);
               if (!pTokenVocab->bSharedStrings)
                  FreeAndClear((void **)&pWord->sWord);
               FNX_FREE(pWord);
            }
         }
         FNX_FREE(pTokenVocab->ppTokenWords);
      }
      FNX_FREE(pTokenVocab);
   }
}  /* FreeTokenVocab */


/*FUNCTION_HEADER**********************
 * NAME:    ;TokenizeSpellings
 * DESC:    Free up a TokenVocab's symbols (if any), and create new symbols based on the spellings of each word.
 * IN:      pTokenVocab - Tokenized vocabulary to modify
 * OUT:     pTokenVocab->ppWords[*]->pwSymbolIndices are replaced with symbol indices representing
              the letters in the name of the word.
 * RETURN:  Pointer to the new NGram tree representing spelling NGrams.
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
NGramTreePtr TokenizeSpellings(TokenVocabPtr pTokenVocab)
{
   NGramTreePtr pNGramTree;
   char **psPhones; 
   unsigned char *pc; // Must be unsigned because we index
   char sLetter[2];
   SDWORD i, iNumIndices, iSymbolPos;
   SWORD *pwSymbols, wSymbolIndex;
   TokenWordPtr pWord;
   SWORD  pwSymbolMap[256], wNumSymbols, wSymbol;
   SDWORD   iWord;   
   H_HashEntry *pHashEntry;

   FNX_ASSERT(pTokenVocab);

   /* See which ASCII characters exist in any word's spelling */
   /* Initialize the elements in pwSymbolMap to 0, indicating they have not been used */
   memset(pwSymbolMap, 0, sizeof(SWORD) * 256);
   /* Set any ASCII value's entry to 1, indicating that it has been used */
   for (iWord=0; iWord<pTokenVocab->iNumWords; iWord++)
   {
      for (pc=(unsigned char *)pTokenVocab->ppTokenWords[iWord]->sWord; *pc; pc++)
         pwSymbolMap[*pc] = 1;
   }
   /* Now set each entry to -1 if not used, and to its wSymbol index if used */
   wNumSymbols=0;
   for (i=0; i<256; i++)
   {
      if (pwSymbolMap[i])
         pwSymbolMap[i] = wNumSymbols++;
      else pwSymbolMap[i]=-1;
   }
   
   /* Create a string for each symbol (consisting of a single character and a null terminator) */
   psPhones = (char **)FNX_CALLOC(wNumSymbols, sizeof(char *));
   sLetter[1]=0x00;
   /* (Skip the null terminator at the beginning, and add it as the last symbol) */
   for (i=1, wSymbol=0; i < 256; i++)
   {
      if (pwSymbolMap[i]>=0)
      {
         sLetter[0] = (char)i;
         psPhones[wSymbol++] = FNX_STRDUP(sLetter);
      }
   }
   FNX_ASSERT(wSymbol==wNumSymbols); /* (Haven't added null terminator symbol in yet) */

   pNGramTree = InitNGrams(psPhones, wNumSymbols, "", 0, FALSE);
   for (wSymbol=0; wSymbol<wNumSymbols; wSymbol++)
   {
      pHashEntry = H_FindHashEntry(pNGramTree->pSymbolHash, psPhones[wSymbol]);
      if (pHashEntry)
         wSymbolIndex = (SWORD)((SDWORD)H_GetHashValue(pHashEntry));
      else wSymbolIndex = -1;
      if (wSymbolIndex<0 || wSymbolIndex >= pNGramTree->wNumLiterals)
         Message(FNX_STDERR,"Error: Unknown symbol '%s'\n", psPhones[wSymbolIndex]);
      if (wSymbolIndex != wSymbol)
         Message(NULL, "Hey! Symbol mismatch: #%d (%s) != %d return by hash\n", (SDWORD)wSymbol, 
                psPhones[wSymbol], (SDWORD)wSymbolIndex);
      if (pwSymbolMap[psPhones[wSymbol][0]]!=wSymbol)
         Message(NULL,"Oops. %s = ASCII %d -> symbol %d = %s\n", psPhones[wSymbol], (SDWORD)(psPhones[wSymbol][0]),
           pwSymbolMap[psPhones[wSymbol][0]], psPhones[pwSymbolMap[psPhones[wSymbol][0]]]);
   }
   FreePointerArray(psPhones, wNumSymbols);

   /* Now read through the vocab file one word at a time.
      For each word, free up old tokens, create new tokens based on spelling,
      and add these to the NGram information */
   for (iWord=0; iWord<pTokenVocab->iNumWords; iWord++)
   {
      pWord = pTokenVocab->ppTokenWords[iWord];
      FreeAndClear((void **)&pWord->pwSymbolIndices);
         
      iNumIndices = FNX_STRLEN(pWord->sWord)+1; /* include null terminator */
      pwSymbols   = (SWORD *)FNX_CALLOC(iNumIndices, sizeof(SWORD));
      for (iSymbolPos=0, pc=(unsigned char *)pWord->sWord; *pc; pc++, iSymbolPos++)
      {
         /* Get the symbol index from the ASCII value */
         wSymbolIndex = pwSymbolMap[*pc];
         FNX_ASSERT(wSymbolIndex>=0); /* All occuring letters were already added as symbols */
         pwSymbols[iSymbolPos] = wSymbolIndex;
      }
      pwSymbols[iSymbolPos++] = pNGramTree->wEndSymbol;

      FNX_ASSERT(iSymbolPos==iNumIndices);
      AddNGrams(pNGramTree, pwSymbols, iNumIndices);
      pWord->wNumIndices = (SWORD)iNumIndices;
      pWord->pwSymbolIndices = pwSymbols;
   }  /* for each word */

   return pNGramTree;
}  /* TokenizeSpellings */
#endif



/*FUNCTION_HEADER**********************
 * NAME:    ;MapVocabSymbols
 * DESC:    Map the symbols in a tokenized vocabulary to the new values (i.e., with unused symbols removed)
              as determined in an NGram tree.
 * IN:      pNGramTree  - Tree of NGrams, with pwSymbolMap built.
            pTokenVocab - Structure containing an array of symbol indices for each word in a vocabulary.
 * OUT:     pTokenVocab->ppTokenWords[*]->pwSymbolIndices[*] are mapped to corresponding values
               in pNGramTree->pwSymbolMap[].
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
void MapVocabSymbols(NGramTreePtr pNGramTree, TokenVocabPtr pTokenVocab)
{
#ifdef USE_WINDOWS
   int cnt = 0;
#endif
   SWORD wSymbol;
   SDWORD iWord;
   TokenWordPtr pWord;

   if (pNGramTree==NULL || pTokenVocab==NULL)
      return; /* bogus input => no output */

   for (iWord=0; iWord<pTokenVocab->iNumWords; iWord++)
   {
      pWord = pTokenVocab->ppTokenWords[iWord];
      for (wSymbol=0; wSymbol < pWord->wNumIndices; wSymbol++)
         pWord->pwSymbolIndices[wSymbol] = pNGramTree->pwSymbolMap[pWord->pwSymbolIndices[wSymbol]];
   }
}  /* MapVocabSymbols */
#endif


/* Current version number for the Huffman code [Use a hex value that looks
   like the month, day, and year when looked at in hex]. */
#define HUFFMAN_VERSION 0x20020403 // i.e., 2002.04.03, or April 3, 2002
/* Version history:
   04 02 2002 - Original version.
 */

/*FUNCTION_HEADER**********************
 * NAME:    ;WriteHuffman
 * DESC:    Write a huffman structure to a file.
 * IN:      fp - File to write to
            pHuffman - Huffman structure to write
 * OUT:     The Huffman structure is written to fp.
 * RETURN:  0 on success, -1 on failure.
 * NOTES:   Format of the Huffman structure on disk:
              <iFormatDate>    - 4-byte integer [all integers are in network byte order]
              <wNumSymbols>    - 2-byte integer
              <wNumUsed>       - 2-byte integer
              For each symbol:
                 <pwSymbolIndices> - wNumSymbols * 2-byte integers
              <wNumLiterals>   - 2-byte integer: Number of literal strings
              <wNumSeparate>   - 2-byte integer: The first 'wNumSeparate' literal symbols need spaces between them.
              For each of 'wNumLiterals' literal:
                 <sLiteral>    - Zero-terminated string
              For each of 'wNumSymbols - wNumLiterals' NGrams:
                 <wN>          - 2-byte integer: Number of subsymbols in this NGram
                 For each of wN subsymbols:
                    <wSymbolIndex>
              For each symbol:
                 <cCodeLength> - Unsigned byte
              <cMaxCodeLength> - Unsigned byte: Maximum length of any code length
              <wEndSymbol>     - 2-byte index of the "end of string" symbol.
              <iNumTables>     - 4-byte integer: Number of tables.
              For each table:
                <uiStart>      - 4-byte unsigned integer
                <uiCodeLength> - 4-byte unsigned integer
                <uiFirstSymbol>- 4-byte unsigned integer
                <uiPatternMask>- 4-byte unsigned integer
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
#ifndef NO_SYSFILE_WRITES
SDWORD WriteHuffman(FILE *fp, HuffmanPtr pHuffman)
{
   SDWORD iError = 0, i;
   SWORD  w;

   /* Write version number */
   iError |= WriteInt32NBO(fp,HUFFMAN_VERSION);

   /* Write the number of symbols and their indices */
   iError |= WriteInt16NBO(fp, pHuffman->wNumSymbols);
   iError |= WriteInt16NBO(fp, pHuffman->wNumUsed);
   iError |= WriteInt16BlockNBO(fp, (unsigned short *)pHuffman->pwSymbolIndices, pHuffman->wNumSymbols);
   
   /* Write the literal string names */
   iError |= WriteInt16NBO(fp, pHuffman->wNumLiterals);
   iError |= WriteInt16NBO(fp, pHuffman->wNumSeparate);
   for (w=0; w < pHuffman->wNumLiterals; w++)
      iError |= WriteString(fp, pHuffman->psLiterals[w]);

   /* Write the NGrams */
   for (w=0; w < pHuffman->wNumSymbols - pHuffman->wNumLiterals; w++)
   {
      if (pHuffman->ppwNGrams[w])
         iError |= WriteInt16BlockNBO(fp, (unsigned short *)pHuffman->ppwNGrams[w], pHuffman->ppwNGrams[w][0]+1);
      else iError |= WriteInt16NBO(fp,0);
   }

   /* Write the code length for each symbol, the max code length, and the end symbol index */
   iError |= ((SWORD)FNX_FWRITE((void *)pHuffman->pcCodeLengths, (size_t)pHuffman->wNumSymbols, 1, fp) != pHuffman->wNumSymbols);
   iError |= (FNX_FWRITE(&pHuffman->cMaxCodeLength, 1, 1, fp)!= 1);
   iError |= WriteInt16NBO(fp,pHuffman->wEndSymbol);

   /* Write the huffman tables */
   iError |= WriteInt32NBO(fp,pHuffman->iNumTables);
   for (i=0; i<pHuffman->iNumTables; i++)
   {
      iError |= WriteInt32NBO(fp,pHuffman->pTables[i].uiStart);
      iError |= WriteInt32NBO(fp,pHuffman->pTables[i].uiCodeLength);
      iError |= WriteInt32NBO(fp,pHuffman->pTables[i].uiFirstSymbol);
      iError |= WriteInt32NBO(fp,pHuffman->pTables[i].uiPatternMask);
   }

   return iError;
}  /* WriteHuffman */
#endif
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadHuffman
 * DESC:    Read a huffman structure from a file.
 * IN:      fp - File to read from
 * OUT:     A Huffman structure is allocated and read from fp.
 * RETURN:  Pointer to the Huffman structure (or NULL on error).
 * NOTES:   See WriteHuffman() for the file format.
 *END_HEADER***************************/
HuffmanPtr ReadHuffman(FILE *fp)
{
   SDWORD iError = 0, i;
   SWORD  w, wNGramSize;
   SDWORD iVersion;
   HuffmanPtr pHuffman;
   char **psLiterals; // Temporary string to hold arrays of literals until it can be packed together.

   if (!fp)
      return NULL;

   /* Allocate Huffman structure */
   pHuffman = (HuffmanPtr)FNX_CALLOC(1,sizeof(Huffman));

   /* Read version number. */
   iError |= ReadInt32NBO(fp,(UDWORD *)&iVersion);

   //if (iVersion > 0x20020403)... do whatever new stuff here
   //...else...
   /* Write the number of symbols and their indices */
   iError |= ReadInt16NBO(fp, (UWORD *)&pHuffman->wNumSymbols);
   iError |= ReadInt16NBO(fp, (UWORD *)&pHuffman->wNumUsed);
   if (iError) goto ReadHuffmanErr;   

   /* Allocate and fill the symbol index array */
   pHuffman->pwSymbolIndices = (SWORDPTR)FNX_CALLOC(pHuffman->wNumSymbols, sizeof(SWORD));
   iError |= ReadInt16BlockNBO(fp, (UWORD *)pHuffman->pwSymbolIndices, pHuffman->wNumSymbols);
   
   /* Read the literal string names */
   iError |= ReadInt16NBO(fp,(UWORD *)&pHuffman->wNumLiterals);
   iError |= ReadInt16NBO(fp,(UWORD *)&pHuffman->wNumSeparate);
   if (iError) goto ReadHuffmanErr;   
   psLiterals = (char **)FNX_CALLOC(pHuffman->wNumLiterals, sizeof(char *));
   for (w=0; w < pHuffman->wNumLiterals; w++)
      iError |= ReadString(fp, &(psLiterals[w]));
   /* Convert list of strings into a single block of memory containing pointers and all strings */
   pHuffman->psLiterals = BuildStringList(psLiterals, (SDWORD)pHuffman->wNumLiterals);
   
   /* Free up the temporary array of strings */
   FreePointerArray(psLiterals, (SDWORD)pHuffman->wNumLiterals);
   if (iError) goto ReadHuffmanErr;   

   /* Read the NGrams */
   if (pHuffman->wNumSymbols > pHuffman->wNumLiterals)
   {
      SDWORD    iNumNGrams = pHuffman->wNumSymbols - pHuffman->wNumLiterals;
      SWORDPTR *ppwNGrams  = (SWORDPTR *)FNX_CALLOC(iNumNGrams, sizeof(SWORDPTR));
      SDWORD    iSize      = sizeof(SWORDPTR) * iNumNGrams;
      SWORDPTR  pwNGram;

      /* Read NGrams into temporary array ppwNGrams[w][] */
      for (w=0; w < iNumNGrams; w++)
      {
         iError |= ReadInt16NBO(fp,(UWORD *)&wNGramSize);
         ppwNGrams[w] = (SWORDPTR)FNX_CALLOC(wNGramSize+1, sizeof(SWORD));
         ppwNGrams[w][0] = wNGramSize;
         iError |= ReadInt16BlockNBO(fp, (UWORD *)&(ppwNGrams[w][1]), wNGramSize);
         iSize += (SDWORD)(wNGramSize+1) * sizeof(SWORD);
      }

      /* Now allocate a single block to hold all of the pointers and arrays in ppwNGrams[][],
         since that is how ppwNGrams is built originally, and that is how it is freed. */
      pHuffman->ppwNGrams = (SWORDPTR *)FNX_CALLOC(1,iSize);
      pwNGram             = (SWORDPTR)&pHuffman->ppwNGrams[iNumNGrams];
      for (w=0; w < iNumNGrams; w++)
      {
         pHuffman->ppwNGrams[w] = pwNGram;
         wNGramSize   = ppwNGrams[w][0];
         memcpy(pwNGram, ppwNGrams[w], (wNGramSize+1) * sizeof(SWORD));
         pwNGram     += (wNGramSize+1);
      }
      /* Free up the temporary 2-D array */
      FreePointerArray((char **)ppwNGrams, iNumNGrams);

      if (iError) goto ReadHuffmanErr;   
   }

   /* Write the code length for each symbol, the max code length, and the end symbol index */
   pHuffman->pcCodeLengths = (SBYTE *)FNX_CALLOC(pHuffman->wNumSymbols, sizeof(SBYTE));
   iError |= ((SWORD)FNX_FREAD((void *)pHuffman->pcCodeLengths, 1, (size_t)pHuffman->wNumSymbols, fp) != pHuffman->wNumSymbols);
   iError |= (FNX_FREAD(&pHuffman->cMaxCodeLength, 1, 1, fp)!= 1);
   iError |= ReadInt16NBO(fp,(UWORD *)&pHuffman->wEndSymbol);
   if (iError) goto ReadHuffmanErr;   

   /* Write the huffman tables */
   iError |= ReadInt32NBO(fp,(UDWORD *)&pHuffman->iNumTables);
   pHuffman->pTables = (CodeLengthTablePtr)FNX_CALLOC(pHuffman->iNumTables, sizeof(CodeLengthTable));
   for (i=0; i<pHuffman->iNumTables; i++)
   {
      iError |= ReadInt32NBO(fp,&pHuffman->pTables[i].uiStart);
      iError |= ReadInt32NBO(fp,&pHuffman->pTables[i].uiCodeLength);
      iError |= ReadInt32NBO(fp,&pHuffman->pTables[i].uiFirstSymbol);
      iError |= ReadInt32NBO(fp,&pHuffman->pTables[i].uiPatternMask);
      if (iError) goto ReadHuffmanErr;   
   }
   if (iError) 
      goto ReadHuffmanErr;   
   return pHuffman;

ReadHuffmanErr:
   if (pHuffman)
      FreeHuffman(pHuffman);
   return NULL;
}  /* ReadHuffman */

/*FUNCTION_HEADER**********************
 * NAME:    ;WriteEncodedTokens
 * DESC:    Write a list of strings to a file as huffman-encoded symbols.
 * IN:      fp - File to write to
            pHuffman - Huffman structure to use for the encoding
            pTokenVocab - Structure containing the tokenized strings to write.
 * OUT:     The huffman-encoded tokens for each string is written to fp.
 * RETURN:  0 on success, something else on failure.
 * NOTES:   Structure for this section:
              <iNumWords> - 32-bit integer
              for each word:
                <variable-length bytes with Huffman-encoded bits>
            Should only use in conjunction with WriteHuffman() so that the
              correct decoding is possible.
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
#ifndef NO_SYSFILE_WRITES
SDWORD WriteEncodedTokens(FILE *fp, HuffmanPtr pHuffman, TokenVocabPtr pTokenVocab)
{
   TokenWordPtr pWord;
   SDWORD i, iError=0;
   UBYTE *pucBytes;
   SDWORD iNumBytes;

   /* Write a table of huffman-encoded strings to the file, or a '0' if there aren't any */
   if (pTokenVocab && pTokenVocab->iNumWords>0)
   {
      /* Write the number of strings */
      iError |= WriteInt32NBO(fp,pTokenVocab->iNumWords);

      /* Huffman encode the symbols that make up each string,
         and write the encoded bytes to the file */
      for (i=0; i < pTokenVocab->iNumWords; i++)
      {
         pWord = pTokenVocab->ppTokenWords[i];
         pucBytes = HuffmanEncode(pHuffman, pWord->pwSymbolIndices, pWord->wNumIndices, &iNumBytes);
         iError |= ((SDWORD)FNX_FWRITE(pucBytes, iNumBytes, 1, fp) == iNumBytes);
         if (pucBytes)
            FNX_FREE(pucBytes);
      }
   }
   else iError |= WriteInt32NBO(fp, 0);

   return iError;
}  /* WriteEncodedTokens */
#endif
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;SymbolLength
 * DESC:    Find out how long a symbol will be (even if it is an NGram symbol)
 * IN:      pHuffman - Huffman structure containing information about each symbol.
            wSymbol  - Symbol to look up
            sDelims  - Characters around which no space is needed (""=>always put spaces; NULL=>never put spaces).
            pbPrevSep     - Pointer to a boolean indicating whether the previous symbol
                              may need to be separated from others like it with a ' '.
 * OUT:     *pbPrevSep is updated according to the last literal symbol processed.
 * RETURN:  Length of the symbol's string representation (including spaces, if any).
 * NOTES:   NGrams are recursively expanded.
            *pbPrevSep is TRUE iff previous symbol was <pHuffman->wSeparate,
              indicating that if this one is like that, too, then a ' '
              needs to be inserted between them.
 *END_HEADER***************************/
SDWORD SymbolLength(HuffmanPtr pHuffman, SWORD wSymbol, BOOL *pbPrevSep)
{
   SDWORD iSize=0;
   if (wSymbol==pHuffman->wEndSymbol)
      return 0; /* The end symbol does not print any actual characters */

   if (wSymbol < pHuffman->wNumLiterals)
   {
      /* See if wSymbol is one that needs to be separated by spaces */
      if (wSymbol < pHuffman->wNumSeparate)
      {
         /* This symbol is not a delimeter, so it might need a ' ' before it */
         if (*pbPrevSep)
         {
            /* The previous symbol was also not a delimeter, so we need
               a ' ' to separate the two */
            iSize++;
         }
         else *pbPrevSep = TRUE;
      }
      else *pbPrevSep = FALSE; /* wSymbol needs no space after it */

      if (pHuffman->psLiterals[wSymbol])
         iSize += FNX_STRLEN(pHuffman->psLiterals[wSymbol]);
   }
   else
   {
      SWORD n, wNGramSize, *pwNGram;
      pwNGram = pHuffman->ppwNGrams[wSymbol - pHuffman->wNumLiterals];
      wNGramSize = pwNGram[0];
      for (n=1; n<wNGramSize; n++)
         iSize += SymbolLength(pHuffman, pwNGram[n], pbPrevSep);
   }

   return iSize;
}  /* SymbolLength */

/*FUNCTION_HEADER**********************
 * NAME:    ;ConcatenateSymbol
 * DESC:    Concatenate a symbol's name to a string (recursively, if it is an NGram)
 * IN:      pHuffman      - Huffman structure containing information about each symbol.
            wSymbol       - Symbol to add
            pbPrevSep     - Pointer to a boolean indicating whether the previous symbol
                              may need to be separated from others like it with a ' '.
 * OUT:     *pbLastDelim is updated according to the last literal symbol processed.
 * RETURN:  Length of the symbol's string representation (including spaces, if any).
 * NOTES:   NGrams are recursively expanded.
 *END_HEADER***************************/
char *ConcatenateSymbol(char *s, HuffmanPtr pHuffman, SWORD wSymbol, BOOL *pbPrevSep)
{
   if (wSymbol < pHuffman->wNumLiterals)
   {
      /* See if wSymbol is not a delimeter */
      if (wSymbol < pHuffman->wNumSeparate)
      {
         /* This symbol is not a delimeter, so it might need a ' ' before it */
         if (*pbPrevSep == TRUE)
         {
            /* The previous symbol was also not a delimeter, so we need
               a ' ' to separate the two */
            *(s++) = ' ';
         }
         else *pbPrevSep = TRUE;
      }
      else *pbPrevSep = FALSE; /* wSymbol is a delimeter, so no space needed before it */
      if (pHuffman->psLiterals[wSymbol])
         s = StrCopyCat(s, pHuffman->psLiterals[wSymbol]);
   }
   else
   {
      SWORD n, wNGramSize, *pwNGram;
      pwNGram = pHuffman->ppwNGrams[wSymbol - pHuffman->wNumLiterals];
      wNGramSize = pwNGram[0];
      for (n=1; n<wNGramSize; n++)
         s = ConcatenateSymbol(s, pHuffman, pwNGram[n], pbPrevSep);
   }

   return s;
}  /* ConcatenateSymbol */

/*FUNCTION_HEADER**********************
 * NAME:    ;TokensToString
 * DESC:    Convert an array of Huffman token indices into a string.
 * IN:      pHuffman - Huffman structure containing information about each symbol.
            pwSymbolIndices - Array of symbol indices
            wNumSymbols     - Number of elements in pwSymbolIndices[].
 * OUT:     A string is allocated with the symbols' names concatenated in it.
 * RETURN:  Newly-allocated string (or NULL on error).
 * NOTES:   
 *END_HEADER***************************/
char *TokensToString(HuffmanPtr pHuffman, SWORDPTR pwSymbolIndices, SWORD wNumSymbols)
{
   SDWORD iSize;
   SWORD w;
   char *sString, *pc;
   BOOL  bPrevSep; /* Flag for whether the previous symbol might need a ' ' after it */

   /* Determine the size of the string */
   iSize=0;
   bPrevSep=FALSE;
   for (w=0; w<wNumSymbols; w++)
      iSize += SymbolLength(pHuffman, pwSymbolIndices[w], &bPrevSep);

   /* Now actually build the string */
   sString = (char *)FNX_MALLOC(iSize+1);
   pc = sString;
   bPrevSep=FALSE; /* reset flag */
   for (w=0; w<wNumSymbols; w++)
      pc = ConcatenateSymbol(pc, pHuffman, pwSymbolIndices[w], &bPrevSep);

   *pc = 0; /* null-terminate the string */
   FNX_ASSERT(iSize == (pc - sString));

   return sString;
}  /* TokensToString */

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadEncodedTokens
 * DESC:    Read a list of huffman-encoded symbol strings from a file.
 * IN:      fp - File to write to
            pHuffman - Huffman structure to use for the decoding
            bMakeString - Flag for whether to create each string from the word tokens
            bFreeSymbols - Flag for whether to free the tokens [usually after making the string!]
 * OUT:     A TokenVocab is allocated and filled with words with symbols and/or a string in each.
 * RETURN:  Pointer to the tokenized vocabulary, or NULL on error.
 * NOTES:   
 *END_HEADER***************************/
TokenVocabPtr ReadEncodedTokens(FILE *fp, HuffmanPtr pHuffman, BOOL bMakeString, BOOL bFreeSymbols)
{
   TokenVocabPtr pTokenVocab;
   TokenWordPtr pWord;
   SDWORD i;
   SDWORD iNumSymbols;
   SWORDPTR pwSymbolIndices;
   SDWORD iBytesRead;

   pTokenVocab = (TokenVocabPtr)FNX_CALLOC(1,sizeof(TokenVocab));
   /* Read the number of strings */
   if (ReadInt32NBO(fp,(UDWORD *)&pTokenVocab->iNumWords) != 0)
   {
      FNX_FREE(pTokenVocab);
      return NULL;
   }
   
   pTokenVocab->ppTokenWords = (TokenWordPtr *)FNX_CALLOC(pTokenVocab->iNumWords, sizeof(TokenWordPtr));

   /* Decode the Huffman-encoded symbols that make up each string */
   for (i=0; i < pTokenVocab->iNumWords; i++)
   {
      pwSymbolIndices = DecodeBitStream(pHuffman, fp, NULL, &iBytesRead, &iNumSymbols);
      if (pwSymbolIndices == NULL)
      {
         FreeTokenVocab(pTokenVocab);
         return NULL; /* error */
      }
      pWord = (TokenWordPtr)FNX_CALLOC(1, sizeof(TokenWord));
      if (bMakeString)
         pWord->sWord = TokensToString(pHuffman, pwSymbolIndices, (SWORD)iNumSymbols);
      if (bFreeSymbols)
         FNX_FREE(pwSymbolIndices);
      else
      {
         pWord->pwSymbolIndices = pwSymbolIndices;
         pWord->wNumIndices     = (SWORD)iNumSymbols;
      }
      pTokenVocab->ppTokenWords[i] = pWord;
   }

   return pTokenVocab;
}  /* ReadEncodedTokens */


/*FUNCTION_HEADER**********************
 * NAME:    ;ReadEncodedStringList
 * DESC:    Read a list of huffman-encoded symbol strings from a file.
 * IN:      fp - File to write to
            pHuffman - Huffman structure to use for the decoding
 * OUT:     A TokenVocab is allocated and filled with words with symbols in each.
 * RETURN:  Pointer to the tokenized vocabulary, or NULL on error.
 * NOTES:   The returned pTokenVocab still needs to have its symbols translated
              into strings if that is what is desired.
 *END_HEADER***************************/
char **ReadEncodedStringList(FILE *fp, SDWORDPTR piNumStrings)
{
   TokenVocabPtr pTokenVocab;
   HuffmanPtr    pHuffman;
   SDWORD        i;
   char        **psStrings;

   if (fp==NULL)
      return NULL;

   /* Read the Huffman encoding tree from the file */
   pHuffman = ReadHuffman(fp);
   if (pHuffman==NULL)
      return NULL;

   /* Read and decode the encoded strings from the file */
   pTokenVocab = ReadEncodedTokens(fp, pHuffman, TRUE/*make strings*/, TRUE/*free symbol indices*/);
   if (pTokenVocab==NULL)
   {
      FreeHuffman(pHuffman);
      return NULL;
   }

   /* Create an array of pointers to the strings */
   *piNumStrings = pTokenVocab->iNumWords;
   psStrings = (char **)FNX_CALLOC(pTokenVocab->iNumWords, sizeof(char *));
   for (i=0; i < pTokenVocab->iNumWords; i++)
   {
      psStrings[i] = pTokenVocab->ppTokenWords[i]->sWord;
      pTokenVocab->ppTokenWords[i]->sWord = NULL; /* So it won't be freed up */
   }

   /* Free up stuff */
   FreeHuffman(pHuffman);
   FreeTokenVocab(pTokenVocab);

   return psStrings;
}  /* ReadEncodedTokens */


/*FUNCTION_HEADER**********************
 * NAME:    ;WriteEncodedStringList
 * DESC:    Huffman encode an array of strings and write them to an opened file.
 * IN:      fp - File to write to
            psStrings - Array of strings to write
            iNumStrings - Number of strings to write
 * OUT:     fp has an array of Extended-Huffman-encoded strings written to it
            (which can be read via ReadEncodedStringList()).
 * RETURN:  0 on success, -1 on failure.
 * NOTES:   Format of the written chunk is:
              <MajorVersion>: 2 bytes [all numbers in network byte order]
              <MinorVersion>: 2 bytes
 *END_HEADER***************************/
#ifndef FNX_LEAN_AND_MEAN
#ifndef NO_SYSFILE_WRITES
SDWORD WriteEncodedStringList(FILE *fp, char **psStrings, SDWORD iNumStrings)
{
   TokenVocabPtr pTokenVocab;
   NGramTreePtr  pNGramTree;
   HuffmanPtr    pHuffman;
   SDWORD        iError=0, i;

   /* Allocate a token vocab full of words */
   pTokenVocab = (TokenVocabPtr) FNX_CALLOC(1,sizeof(TokenVocab));
   pTokenVocab->iNumWords = iNumStrings;
   pTokenVocab->ppTokenWords = (TokenWordPtr *)FNX_CALLOC(iNumStrings, sizeof(TokenWordPtr));

   /* Point all of the token words at the input strings */
   for (i=0; i<iNumStrings; i++)
   {
      pTokenVocab->ppTokenWords[i] = (TokenWordPtr) FNX_CALLOC(1, sizeof(TokenWord));
      pTokenVocab->ppTokenWords[i]->sWord = psStrings[i];
   }

   /* Create an NGram tree for all of the spellings of all of the strings */
   pNGramTree = TokenizeSpellings(pTokenVocab);

   /* Select NGrams and create a Huffman structure */
   pHuffman   = SelectNGrams(pNGramTree);

   /* Modify indices in pTokenVocab since some may have been removed and slid down. */
   MapVocabSymbols(pNGramTree, pTokenVocab);
   
   /* Write the Huffman structure to the file */
   iError |= WriteHuffman(fp, pHuffman);

   /* Write the encoded list of strings */
   iError |= WriteEncodedTokens(fp, pHuffman, pTokenVocab);

   /* Free up stuff */
   FreeHuffman(pHuffman);
   FreeNGramTree(pNGramTree);
   for (i=0; i<iNumStrings; i++)             /* Set sWord to NULL so it won't be freed, since */
      pTokenVocab->ppTokenWords[i]->sWord = NULL; /*   it points to a string in psStrings[] */
   FreeTokenVocab(pTokenVocab);

   return iError;
}  /* WriteEncodedStringList */
#endif
#endif

//#define TEST_HUFFMAN /* Define this to make Huffman.c a stand-alone executable */
#ifdef TEST_HUFFMAN
//#define TIME_HUFFMAN
#ifdef TIME_HUFFMAN
#include <time.h>
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;TestHuffman
 * DESC:    Do Huffman encoding and decoding on each word in a vocabulary
              to make sure we end up with what we started with.
 * IN:      pHuffman - Structure containing information needed to encode and decode pronunciations.
            pTokenVocab - Structure containing an array of symbol indices for each word in a vocabulary.
 * OUT:     Results printed to stdout.
 * RETURN:  0 on success, -1 if there are differences.
 * NOTES:   
 *END_HEADER***************************/
SDWORD TestHuffman(HuffmanPtr pHuffman, TokenVocabPtr pTokenVocab)
{
   SDWORD iWord, iResult=0;
   SDWORD  iNumUsed;
   UBYTE  *pucBytes;
   SDWORD  iNumBytes, iBytesRead, iSymbol;
   SWORD   *pwSymbolIndices;
   TokenWordPtr pWord;
   SDWORD  iTotalSymbols = 0; /* Total number of symbols in all words */
   SDWORD  iTotalBytes   = 0; /* Total number of bytes used in encoding of all words (including padded bits on end) */
   SDWORD  iOverhead;
   SWORD   wNGram;
   SDWORD  iMaxBytes=0; /* Maximum number of bytes needed to encode any pattern */
#ifdef TIME_HUFFMAN
   clock_t start, finish;
   double fDuration;
   UBYTE  **ppucBytes;
#endif

#ifdef DUMP_ENCODING
   FNX_ASSERT(pHuffman && pTokenVocab);
   printf("Testing Huffman encoding...\n");
   DumpHuffman(pHuffman);
#endif

#ifdef TIME_HUFFMAN
   printf("Timing the encoding and decoding of words...\n");
   start=clock();
#endif
   for (iWord=0; iWord<pTokenVocab->iNumWords; iWord++)
   {
      pWord = pTokenVocab->ppTokenWords[iWord];
#ifdef DUMP_ENCODING
      printf("%s\n", pWord->sWord);
#endif
      pucBytes = HuffmanEncode(pHuffman, pWord->pwSymbolIndices, pWord->wNumIndices, &iNumBytes);
      iTotalSymbols += pWord->wNumIndices;
      iTotalBytes   += iNumBytes;
      if (iNumBytes > iMaxBytes)
         iMaxBytes = iNumBytes;
#ifndef TIME_HUFFMAN
      printf(" %4d/%d: %-15s %2d bytes ->%2d bytes\n", iWord, pTokenVocab->iNumWords, pWord->sWord, 
         pWord->wNumIndices, iNumBytes);
#endif
      /* Decode array of symbol indices */
      pwSymbolIndices = DecodeBitStream(pHuffman, NULL, pucBytes, &iBytesRead, &iNumUsed);
      if (iNumUsed != pWord->wNumIndices-1) /* "-1", Since we don't get the "end-of-string" symbol upon decoding */
      {
         printf("Different number of symbols in word %s\n", pWord->sWord);
         iResult=-1; /* Had a difference */
      }
      else if (iBytesRead != iNumBytes)
      {
         printf("Encoding used %d bytes; decoding used %d, in word %s\n", iNumBytes, iBytesRead, pWord->sWord);
         iResult=-1; /* Had a difference */
      }
      else
      {
         for (iSymbol=0; iSymbol < iNumUsed; iSymbol++)
         {
            if (pwSymbolIndices[iSymbol] != pWord->pwSymbolIndices[iSymbol])
            {
               printf("Different symbols in word %s\n", pWord->sWord);
               iResult=-1;
            }
         }
      }
   }  /* for iWord */

#ifdef TIME_HUFFMAN
   finish=clock();
   fDuration = (double)(finish - start) / CLOCKS_PER_SEC;
   printf("%d words encoded and decoded in %lf seconds (=%lf seconds/word)\n", pTokenVocab->iNumWords, fDuration, fDuration/pTokenVocab->iNumWords);

   /* Now time encoding and decoding separately */
   ppucBytes = (UBYTE **)FNX_CALLOC(pTokenVocab->iNumWords, sizeof(UBYTE *));

   start=clock();
   for (iWord=0; iWord<pTokenVocab->iNumWords; iWord++)
   {
      pWord = pTokenVocab->ppTokenWords[iWord];
      ppucBytes[iWord] = HuffmanEncode(pHuffman, pWord->pwSymbolIndices, pWord->wNumIndices, &iNumBytes);
   }  /* for iWord */
   finish=clock();
   fDuration = (double)(finish - start) / CLOCKS_PER_SEC;
   printf("%d words encoded in %lf seconds (=%lf seconds/word)\n", pTokenVocab->iNumWords, fDuration, fDuration/pTokenVocab->iNumWords);

   start=clock();
   for (iWord=0; iWord<pTokenVocab->iNumWords; iWord++)
   {
      pwSymbolIndices = DecodeBitStream(pHuffman, NULL, ppucBytes[iWord], &iBytesRead, &iNumUsed);
      FNX_FREE(pwSymbolIndices);
      FNX_FREE(ppucBytes[iWord]);
   }  /* for iWord */
   finish=clock();
   fDuration = (double)(finish - start) / CLOCKS_PER_SEC;
   printf("%d words decoded in %lf seconds (=%lf seconds/word)\n", pTokenVocab->iNumWords, fDuration, fDuration/pTokenVocab->iNumWords);
#endif // timing huffman

   printf("%d words.  %d total (literal) symbols. Encoded into %d bytes => %.2f%% reduction\n", 
      pTokenVocab->iNumWords, iTotalSymbols, iTotalBytes, 
      100.0f*(float)(iTotalSymbols-iTotalBytes)/(float)iTotalSymbols);
   /* Calculate overhead */
   iOverhead=2+3*pHuffman->wNumSymbols+4+2+4+2+4+pHuffman->iNumTables*sizeof(CodeLengthTable);
   for (wNGram=0; wNGram < pHuffman->wNumSymbols-pHuffman->wNumLiterals; wNGram++)
      iOverhead += (pHuffman->ppwNGrams[wNGram][0]+1) * (pHuffman->wNumSymbols>255 ? 2 : 1);
   printf("  Overhead: %d bytes = %d total => %.2f%% real reduction\n", iOverhead, iOverhead+iTotalBytes,
      100.0f*(float)(iTotalSymbols-(iOverhead+iTotalBytes))/(float)iTotalSymbols);
   printf("  Max length of any pattern: %d bytes\n", iMaxBytes);
   return iResult;
}  /* TestHuffman */

int main(int argc, char *argv[])
{
   NGramTreePtr pNGramTree;
   char *sVocabFile, *sBinaryFile;
   TokenVocabPtr pTokenVocab;
   HuffmanPtr pHuffman;

   if (argc<5)
   {
      printf("Usage: %s -asr <DescFile>.desc <Vocab File>.vocab <Binary file>.dcc\n", argv[0]);
      printf("   OR: %s -tts <Symbols>.txt   <Input File>       <Binary file>.dcc\n", argv[0]);
      exit(-1);
   }

   sVocabFile = argv[3];
   sBinaryFile = argv[4];
   printf("Reading vocab file and constructing NGram tree...\n");

   if (FNX_STRICMP(argv[1],"-asr")==0)
   {
      /* Speech Recognition Dictionary */
      VocabTPtr pVocab;
      pVocab = ReadVocab(sVocabFile, NULL);
      pNGramTree = BuildVocabNGrams(pVocab, &pTokenVocab);
   }
   else if (FNX_STRICMP(argv[1],"-tts")==0)
   {
      char *sSymbolFile = argv[2], **psSymbols;
      SDWORD iNumSymbols;
      psSymbols = ReadSymbolList(sSymbolFile, &iNumSymbols);
      pNGramTree = BuildTTSNGrams(sVocabFile, psSymbols, iNumSymbols, &pTokenVocab);
      FreePointerArray(psSymbols, iNumSymbols);
   }
#if 1
   /* Convert the NGram tree into Huffman tables */
   pHuffman = SelectNGrams(pNGramTree);
   /* If any literal symbols were unused, then they will have been removed,
      and other symbols 'slid down'.  Since indices would thus have changed,
      the symbol indices stored in the vocab words must be mapped to the new
      values (stored in pNGramTree->pwSymbolMap). */
   MapVocabSymbols(pNGramTree, pTokenVocab);
   /* Make sure all of the original strings can be reconstructed from Huffman tree */
   TestHuffman(pHuffman, pTokenVocab);
   FreeNGramTree(pNGramTree);
#endif
   /* Create a new NGram tree of the SPELLINGS of the words */
   printf("Converting word spellings into symbol indices...\n");
   pNGramTree = TokenizeSpellings(pTokenVocab);
   printf("Selecting spelling NGrams...\n");
   pHuffman   = SelectNGrams(pNGramTree);
   MapVocabSymbols(pNGramTree, pTokenVocab);
   TestHuffman(pHuffman, pTokenVocab);

   /* Free up stuff */
   FreeNGramTree(pNGramTree);
   FreeTokenVocab(pTokenVocab);
}
#endif //TEST_HUFFMAN

