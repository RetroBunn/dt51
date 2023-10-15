/*C_HEADER_FILE****************************************************************
FILE        :  ShortenPronunciation.c
DESC        :  
TABS        :  3
OWNER       :  
DATE CREATED:  

(C) Copyright 2002 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/21/05 3:23p $
  $Revision: 21 $

*END_HEADER*******************************************************************/
#include "FnxPlatform.h"
#include "DTFnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxNetwork.h"
#include "FnxNames.h"
#include "FnxWord.h"
#include "FnxDesc.h"
#include "FnxFileIO.h"
#include "FnxVocab.h"
//#include "SearchGraph.h"
//#include "FnxGenPron.h"
//#include "FnxNnet.h"
#include "phonetic.h"

#ifndef FNX_LEAN_AND_MEAN

#define OR_STRING "|"

#define INIT_NODE_ID (-1)
#define END_NODE_ID  (-2)

typedef struct
{
   llistPtr pPrev;      /* Preceding nodes (could include INIT_NODE)  */
   llistPtr pNext;      /* Following nodes (could include FINAL_NODE) */
   llistPtr pDisjunction; /* Linked list of symbol lists that must be "or-ed" to pSymbols. */
   BOOL   bOptional;    /* True => Is optional, so add [] (and not ()) before concatenating */
   llistPtr pSymbols;   /* Linked list of strings that should be concatenated to represent this node 
                           (These point to the original strings, not copies, so should not be freed) */
   SDWORD   iID;        /* Index in dictionary's ppNodes[] array */
} DNode, *DNodePtr; /* Dictionary Node */

typedef struct
{
   DNode   InitNode;  /* Initial Node */
   DNode   EndNode;   /* Final Node */
   DNode **ppNodes;   /* Array of pointers to the (remaining) nodes in the graph (point into pNodeBuf[])*/
   SDWORD  iNumNodes; /* Number of elements (remaining) in ppNodes[] */
   DNode  *pNodeBuf;  /* Array of actual node structures, some of which may no longer be used */
} DGraph, *DGraphPtr; /* Dictionary Graph */


llistPtr CollapseDGraph(DGraphPtr pDGraph, LinkPoolPtr pLinkPool);

/* Debugging code... */
//#define DEBUG_DGRAPH
//#define DUMP_PROBLEMS

#ifdef DUMP_PROBLEMS
BOOL gbOuch;
#endif

#ifdef DEBUG_DGRAPH
void DumpSymbols(llistPtr pSymbols)
{
   llistPtr pLink;
   ReverseList(&pSymbols);
   for (pLink=pSymbols; pLink; pLink=pLink->pNext)
      FNX_PRINTF("%s ",(char *)pLink->p);
   FNX_PRINTF("\n");
   ReverseList(&pSymbols);
}
void DumpIndexList(llistPtr pList, char *sEndString)
{
   llistPtr pLink;
   DNodePtr pNode;
   for (pLink=pList; pLink; pLink=pLink->pNext)
   {
      pNode = (DNodePtr)pLink->p;
      FNX_PRINTF("%d%s", pNode->iID, pLink->pNext ? ", " : sEndString);
   }
}

void DumpDGraph(DGraphPtr pDGraph, char *sMessage)
{
   SDWORD   iNode;

   if (sMessage && sMessage[0])
      FNX_PRINTF("%s\n", sMessage);
   FNX_PRINTF("%d Nodes\n", pDGraph->iNumNodes);
   FNX_PRINTF("%d Initial Nodes: ", ListSize(pDGraph->InitNode.pNext));
   DumpIndexList(pDGraph->InitNode.pNext, "\n");
   FNX_PRINTF("%d Final Nodes:   ", ListSize(pDGraph->EndNode.pPrev));
   DumpIndexList(pDGraph->EndNode.pPrev, "\n");
   for (iNode=0; iNode<pDGraph->iNumNodes; iNode++)
   {
      FNX_PRINTF("Node %d: ", iNode);
      if (pDGraph->ppNodes[iNode]->bOptional)
         FNX_PRINTF("[opt]");
      if (pDGraph->ppNodes[iNode]->pDisjunction)
         FNX_PRINTF("(or)");
      DumpSymbols(pDGraph->ppNodes[iNode]->pSymbols);
      if (pDGraph->ppNodes[iNode]->pDisjunction)
      {
         llistPtr pLink;
         for (pLink=pDGraph->ppNodes[iNode]->pDisjunction; pLink; pLink=pLink->pNext)
         {
            FNX_PRINTF("|");
            DumpSymbols((llistPtr)pLink->p);
         }
      }
      FNX_PRINTF("  Prev: ");
      DumpIndexList(pDGraph->ppNodes[iNode]->pPrev,";  Next: ");
      DumpIndexList(pDGraph->ppNodes[iNode]->pNext,"\n");
   }
   FNX_PRINTF("\n");
}
#else
/* Just define DumpSymbols() as an empty macro to remove it */
#define DumpSymbols(x)
#define DumpDGraph(x,y)
#endif

/*FUNCTION_HEADER**********************
   NAME:    ;ClearDNode
   DESC:    Free up the pPrev, pNext and pSymbols list of a DNode.
   IN:      pDNode    - Structure to clear out.
            pLinkPool - Link pool to return links to.
   OUT:     pDNode's pPrev, pNext and pSymbols lists are freed up,
              and its bOptional flag and pDisjunction list are cleared.
   RETURN:  n/a
   NOTES:   Does NOT free up pDNode itself (since it is probably
              allocated as part of a larger buffer).
 *END_HEADER***************************/
void ClearDNode(DNodePtr pDNode, LinkPoolPtr pLinkPool)
{
   if (pDNode)
   {
      FreeList(&pDNode->pPrev, pLinkPool);
      FreeList(&pDNode->pNext, pLinkPool);
      FreeList(&pDNode->pSymbols, pLinkPool);
      pDNode->bOptional = FALSE;
      while (pDNode->pDisjunction)
      {
         llistPtr pList = (llistPtr)pDNode->pDisjunction->p;
         FreeList(&pList, pLinkPool);
         RemoveLink(&pDNode->pDisjunction, pLinkPool);
      }
      FNX_ASSERT(pDNode->pPrev==NULL && pDNode->pNext==NULL && pDNode->pSymbols==NULL);
      FNX_ASSERT(pDNode->pDisjunction==NULL);
   }
}

/*FUNCTION_HEADER**********************
   NAME:    ;FreeDGraph
   DESC:    Free up a DGraph structure.
   IN:      pDGraph - Structure to free up.
            pLinkPool - Link pool to return links to.
   OUT:     pLinkPool has links added back into its free list.
   RETURN:  n/a
   NOTES:   
 *END_HEADER***************************/
void FreeDGraph(DGraphPtr pDGraph, LinkPoolPtr pLinkPool)
{
   SDWORD iNode;
   if (pDGraph)
   {
      FNX_ASSERT(pDGraph->ppNodes);
      FNX_ASSERT(pDGraph->pNodeBuf);
      /* Free up the lists belonging to any remaining nodes in the graph */
      for (iNode = 0; iNode < pDGraph->iNumNodes; iNode++)
      {
         FNX_ASSERT(pDGraph->ppNodes[iNode]);
         ClearDNode(pDGraph->ppNodes[iNode], pLinkPool);
      }
      FreeList(&pDGraph->InitNode.pNext, pLinkPool);
      FreeList(&pDGraph->EndNode.pPrev, pLinkPool);
      FNX_FREE(pDGraph->ppNodes);
      FNX_FREE(pDGraph->pNodeBuf);
      FNX_FREE(pDGraph);
   }
}  /* FreeDGraph */

/*FUNCTION_HEADER**********************
   NAME:    ;WordToDGraph
   DESC:    Convert a wordT structure to a DGraph structure.
   IN:      pWord - Word to convert
            pLinkPool - Link pool to use.
   OUT:     pLinkPool has a bunch of links in it, and a DGraph is allocated.
   RETURN:  Pointer to pDGraph
   NOTES:   Free up using FreeDGraph() and the FreeLinkPool(pLinkPool).
            DO NOT free up pWord until you're done with pDGraph, because it
              uses pointers to (rather than copies of) the strings in pWord.
 *END_HEADER***************************/
DGraphPtr WordToDGraph(wordTPtr pWord, LinkPoolPtr pLinkPool)
{
   DGraphPtr pDGraph;
   SDWORD iNode, iFinal, iInit, iNext;
   DNodePtr pNode, pNextNode;
   llistPtr pLink;

   if (!pWord)
      return NULL;
   /* Initialize the graph */
   pDGraph = (DGraphPtr) FNX_CALLOC(1, sizeof(DGraph));
   pDGraph->InitNode.iID = INIT_NODE_ID;
   pDGraph->EndNode.iID  = END_NODE_ID;
   
   /* Create an array of DNodes corresponding to the nodes in the word's pronunciation graph */
   pDGraph->iNumNodes = pWord->numnodes;
   pDGraph->pNodeBuf = (DNodePtr)   FNX_CALLOC(pDGraph->iNumNodes, sizeof(DNode));
   
   /* Point the array ppNodes[] at the actual nodes, and set the nodes' ID and phoneme. */
   pDGraph->ppNodes  = (DNodePtr *) FNX_CALLOC(pDGraph->iNumNodes, sizeof(DNodePtr));
   for (iNode=0; iNode < pDGraph->iNumNodes; iNode++)
   {
      pDGraph->ppNodes[iNode] = &pDGraph->pNodeBuf[iNode];
      pDGraph->ppNodes[iNode]->iID = iNode;
      /* Insert the phoneme into the node's (empty) symbol list */
      InsertLink(pWord->nodes[iNode].phoneme, &pDGraph->ppNodes[iNode]->pSymbols, pLinkPool);
   }
   /* Connect nodes to their following nodes. */
   for (iNode=0; iNode < pDGraph->iNumNodes; iNode++)
   {
      for (iNext=0; iNext < pWord->nodes[iNode].numnext; iNext++)
      {
         // Make sure there aren't any duplicate links
         SDWORD iOtherNext;
         BOOL   bRepeat=FALSE;
         for (iOtherNext=0; iOtherNext<iNext; iOtherNext++)
         {
            if (pWord->nodes[iNode].next[iOtherNext] == pWord->nodes[iNode].next[iNext])
               bRepeat=TRUE;
         }
         if (!bRepeat)
            InsertLink(pDGraph->ppNodes[pWord->nodes[iNode].next[iNext]], &pDGraph->ppNodes[iNode]->pNext, pLinkPool);
      }
   }
   /* Connect final nodes to EndNode */
   for (iFinal=0; iFinal < pWord->numfinal; iFinal++)
   {
      iNode = pWord->finalnodes[iFinal];
      InsertLink(&pDGraph->EndNode, &pDGraph->ppNodes[iNode]->pNext, pLinkPool);
   }
   /* Connect InitNode to initial nodes */
   for (iInit=0; iInit < pWord->numinit; iInit++)
   {
      iNode = pWord->initnodes[iInit];
      InsertLink(pDGraph->ppNodes[iNode], &pDGraph->InitNode.pNext, pLinkPool);
   }
   /* Add a 'prev' link for every 'next' link in all nodes */
   for (iNode=-1; iNode < pDGraph->iNumNodes; iNode++)
   {
      if (iNode<0)
         pNode = &pDGraph->InitNode;
      else pNode = pDGraph->ppNodes[iNode];
      for (pLink=pNode->pNext; pLink; pLink = pLink->pNext)
      {
         pNextNode = (DNodePtr) pLink->p;
         InsertLink(pNode, &pNextNode->pPrev, pLinkPool);
      }
   }
   
#ifdef DEBUG_DGRAPH
   FNX_PRINTF("Word %s:\n", pWord->name);///
   DumpDGraph(pDGraph,"After converting to DGraph:");///
#endif
   /* Return the completed graph */
   return pDGraph;
}  /* WordToDGraph */

/*FUNCTION_HEADER**********************
   NAME:    ;SameLists
   DESC:    Tell whether two lists contain the same pointers.
   IN:      pList1, pList2 - The two lists to compare.
   OUT:     n/a
   RETURN:  TRUE if pList1 and pList2 both contain the same number 
              and same set of pointers; FALSE otherwise.
   NOTES:   
 *END_HEADER***************************/
BOOL SameLists(llistPtr pList1, llistPtr pList2)
{
   llistPtr pLink1, pLink2;
   if (ListSize(pList1)!=ListSize(pList2))
      return FALSE;
   for (pLink1=pList1; pLink1; pLink1=pLink1->pNext)
   {
      if (!LinkExists(pLink1->p, pList2))
         return FALSE;
   }
   for (pLink2=pList2; pLink2; pLink2=pLink2->pNext)
   {
      if (!LinkExists(pLink2->p, pList1))
         return FALSE;
   }
   return TRUE;
}  /* SameLists */

/*FUNCTION_HEADER**********************
   NAME:    ;SameIDLists
   DESC:    See if two linked lists contain nodes with the same set of ID numbers.
   IN:      pList1, pList2 - Two lists of DNodes.
   OUT:     n/a
   RETURN:  TRUE if pList1 and pList2 are the same size, and the ID# of every node
               in each list is also the ID# of a node in the other list.
   NOTES:   The matching nodes don't have to be in the same order in the two lists.
 *END_HEADER***************************/
BOOL SameIDLists(llistPtr pList1, llistPtr pList2)
{
   llistPtr pLink1, pLink2;
   DNodePtr pNode1, pNode2;

   /* Make sure list 1 and list 2 are the same size */
   if (ListSize(pList1)!=ListSize(pList2))
      return FALSE; /* Different numbers of links, so not the same list */

   /* Make sure everything in list 1 is in list 2 */
   for (pLink1=pList1; pLink1; pLink1=pLink1->pNext)
   {
      pNode1 = (DNodePtr)pLink1->p;
      for (pLink2=pList2; pLink2; pLink2=pLink2->pNext)
      {
         pNode2 = (DNodePtr)pLink2->p;
         if (pNode2->iID == pNode1->iID)
            break;
      }
      if (pLink2==NULL)
         return FALSE; /* Couldn't find pNode1->iID in pList2 */
   }

   /* Make sure everything in list 2 is in list 1 */
   for (pLink2=pList2; pLink2; pLink2=pLink2->pNext)
   {
      pNode2 = (DNodePtr)pLink2->p;
      for (pLink1=pList1; pLink1; pLink1=pLink1->pNext)
      {
         pNode1 = (DNodePtr)pLink1->p;
         if (pNode1->iID == pNode2->iID)
            break;
      }
      if (pLink1==NULL)
         return FALSE; /* Couldn't find pNode1->iID in pList2 */
   }

   return TRUE; /* No difference found, so the lists point to the same IDs */
}  /* SameIDList */

/*FUNCTION_HEADER**********************
   NAME:    ;SameSymbolLists
   DESC:    See if two lists of symbols match.
   IN:      pSymbols1, pSymbols2 - Two lists of symbols to compare.
   OUT:     n/a
   RETURN:  TRUE if pSymbols1 and pSymbols2 contain the same list of symbols.
   NOTES:   The pointers don't have to match, but the strings have to match,
              and be in the same order.
 *END_HEADER***************************/
BOOL SameSymbolLists(llistPtr pSymbols1, llistPtr pSymbols2)
{
   llistPtr pLink1, pLink2;
   char *sSymbol1, *sSymbol2;

   for (pLink1=pSymbols1, pLink2=pSymbols2; pLink1 && pLink2; pLink1=pLink1->pNext, pLink2=pLink2->pNext)
   {
      sSymbol1 = (char *)pLink1->p;
      sSymbol2 = (char *)pLink2->p;
      if (FNX_STRCMP(sSymbol1, sSymbol2)!=0)
         return FALSE;
   }
   if (pLink1 || pLink2)
      return FALSE; /* One list was longer than the other */
   return TRUE; /* No difference was found */
}  /* SameSymbolLists */

/*FUNCTION_HEADER**********************
   NAME:    ;SameDGraphs
   DESC:    See if two DGraphs contain the same information.
   IN:      pDGraph1, pDGraph2 - Two DGraphs to compare.
   OUT:     n/a
   RETURN:  TRUE if pDGraph1 and pDGraph2 are the same.  FALSE otherwise.
   NOTES:   The nodes have to have the same ID#s, be in the same order,
               have the same flags, and have the same symbol lists.
               The order of the various pNext and pPrev lists can be
               different as long as they point to the same set of
               nodes, i.e., a set nodes with the same ID#s.
 *END_HEADER***************************/
BOOL SameDGraphs(DGraphPtr pDGraph1, DGraphPtr pDGraph2)
{
   DNodePtr pDNode1, pDNode2;
   SDWORD iNode;

   //DumpDGraph(pDGraph1, "First DGraph for comparison:");
   //DumpDGraph(pDGraph2, "Second DGraph for comparison:");
   if (pDGraph1->iNumNodes != pDGraph2->iNumNodes)
   { 
//      FNX_PRINTF("Different number of nodes (%d vs. %d)\n", pDGraph1->iNumNodes, pDGraph2->iNumNodes); 
      return FALSE;
   }
   if (!SameIDLists(pDGraph1->InitNode.pNext, pDGraph2->InitNode.pNext))
   {
//      FNX_PRINTF("Different Init.pNext lists\n");
      return FALSE;
   }
   if (!SameIDLists(pDGraph1->EndNode.pPrev, pDGraph2->EndNode.pPrev))
   {
//      FNX_PRINTF("Different EndNode.pPrev lists\n");
      return FALSE;
   }
   for (iNode=0; iNode<pDGraph1->iNumNodes; iNode++)
   {
      pDNode1=pDGraph1->ppNodes[iNode];
      pDNode2=pDGraph2->ppNodes[iNode];
      if (pDNode1->iID != pDNode2->iID || pDNode1->iID!=iNode)
      {
//         FNX_PRINTF("Wrong ID#s: For node %d, IDs are %d and %d\n", iNode, pDNode1->iID, pDNode2->iID);
         return FALSE;
      }
      //Now that we use pDisjunction, we should really compare lists of lists,
      //  but I don't feel like it today...
      //if (pDNode1->bDisjunction != pDNode2->bDisjunction)
      //{
      //   FNX_PRINTF("Disjunction mismatch for node %d\n", iNode);
      //   return FALSE;
      //}
      if (pDNode1->bOptional != pDNode2->bOptional)
      {
//         FNX_PRINTF("Optional mismatch for node %d\n", iNode);
         return FALSE;
      }
      if (!SameIDLists(pDNode1->pPrev, pDNode2->pPrev))
      {
//         FNX_PRINTF("Different prev lists for node %d\n", iNode);
         return FALSE;
      }
      if (!SameIDLists(pDNode1->pNext, pDNode2->pNext))
      {
//         FNX_PRINTF("Different next lists for node %d\n", iNode);
         return FALSE;
      }
      if (!SameSymbolLists(pDNode1->pSymbols, pDNode2->pSymbols))
      {
//         FNX_PRINTF("Different symbol lists for node %d\n", iNode);
         return FALSE;
      }
   }  /* for iNode */
   return TRUE; /* No difference found */
}  /* SameDGraphs */

/*FUNCTION_HEADER**********************
   NAME:    ;CollapseDisjunctions
   DESC:    Remove redundancy from a list of disjunctive symbol lists.
   IN:      pNode - Node to collapse the disjunctions on.
            pLinkPool     - Link pool to use.
   OUT:     Redundant lists from *ppDisjunction are removed.
   RETURN:  TRUE if any change was made, FALSE otherwise.
   NOTES:   Currently just removes any exact duplicates (e.g., "a,a,b" -> "a,b").
            Eventually could do more complicated searches, such as identifying
              common initial and final strings (e.g., "i: kc [kh] l= , i: kc [kh] & l , I kc [kh] l="
              -> "i: kc[kh](l=|& l) , I kc [kh] l=").
 *END_HEADER***************************/
BOOL CollapseDisjunctions(DNodePtr pNode, LinkPoolPtr pLinkPool)
{
   llistPtr pLink1, pLink2, *ppPrev;
   BOOL bChanged=FALSE; /* Flag for whether any change was made */

   if (pNode->pDisjunction==NULL)
      return FALSE; /* No disjunction to try to collapse */

   /* Add pSymbols to the list to simplify the rest of the code */
   InsertLink(pNode->pSymbols, &pNode->pDisjunction, pLinkPool);

   /* First look to see if there are any exact duplicates in the list */
   for (pLink1 = pNode->pDisjunction; pLink1; pLink1 = pLink1->pNext)
   {
      ppPrev = &pLink1->pNext;
      for (pLink2=*ppPrev; pLink2; pLink2=*ppPrev)
      {
         if (pLink1 != pLink2 && SameSymbolLists((llistPtr)pLink1->p, (llistPtr)pLink2->p))
         {
            /* pLink1 and pLink2 have the same list of symbols, 
               so delete pLink2 and its list. */
            llistPtr pList=(llistPtr)pLink2->p;
            FreeList(&pList, pLinkPool);
            RemoveLink(ppPrev, pLinkPool);
            bChanged=TRUE;
         }
         else ppPrev = &pLink2->pNext;
      }  /* for pLink2 */
   }  /* for pLink1 */

   /* Remove the first element of the list, which was pSymbols */
   FNX_ASSERT(pNode->pDisjunction->p == pNode->pSymbols);
   RemoveLink(&pNode->pDisjunction, pLinkPool);

   return bChanged;
}  /* CollapseDisjunctions */

/*FUNCTION_HEADER**********************
   NAME:    ;ConnectDNodes
   DESC:    Connect two DNodes to each other.
   IN:      pLeft - DNode on the left
            pRight - DNode on the right.
   OUT:     pLeft is in pRight->pPrev, and pRight is in pLeft->pNext.
   RETURN:  n/a
   NOTES:   Does not check to make sure they aren't already in those lists.
 *END_HEADER***************************/
void ConnectDNodes(DNodePtr pLeft, DNodePtr pRight, LinkPoolPtr pLinkPool)
{
   InsertLink(pLeft, &pRight->pPrev, pLinkPool);
   InsertLink(pRight, &pLeft->pNext, pLinkPool);
}

/*FUNCTION_HEADER**********************
   NAME:    PrepNode
   DESC:    ;Prepare a node to have its symbols concatenated with another node's symbols.
   IN:      pNode - Node to be prepared
   OUT:     pNode->pSymbols has [] or () put around them if it is optional or a disjunction, respectively.
            pNode->bOptional and ->pDisjunction are cleared.
   RETURN:  n/a
   NOTES:   It is allowable to call this routine multiple times on the same node,
              since the flags will get cleared the first time and no further effects
              will happen later.
 *END_HEADER***************************/
void PrepNode(DNodePtr pNode, LinkPoolPtr pLinkPool)
{
   if (pNode->pDisjunction)
   {
      /* Double-check the disjunctions to make sure there are no duplicates
         in the list. */
      CollapseDisjunctions(pNode, pLinkPool);

      /* Take the linked list of disjunction symbol lists and concatenate
         them into a single list (separated by "|" symbols) */
      while (pNode->pDisjunction)
      {
         InsertLink(OR_STRING, &pNode->pSymbols, pLinkPool);
         InsertList(&pNode->pSymbols, (llistPtr)pNode->pDisjunction->p);
         RemoveLink(&pNode->pDisjunction, pLinkPool);
      }
      FNX_ASSERT(pNode->pDisjunction==NULL);
      if (pNode->bOptional)
      {
         SurroundSymbols(&pNode->pSymbols, "[", "]", pLinkPool);
         pNode->bOptional=FALSE;
      }
      else SurroundSymbols(&pNode->pSymbols, "(", ")", pLinkPool);
   }
   else if (pNode->bOptional)
   {
      SurroundSymbols(&pNode->pSymbols, "[", "]", pLinkPool);
      pNode->bOptional=FALSE;
   }    
}  /* PrepNode */

/*FUNCTION_HEADER**********************
   NAME:    ;CopyList
   DESC:    Make a copy of a linked list.
   IN:      pList - List to copy.
            pLinkPool - Pool of links to use
   OUT:     pLinkPool has links allocated from it.
   RETURN:  Pointer to the new list.
   NOTES:   Makes a copy of the list of pointers, but doesn't duplicate
              the things being pointed to (e.g., strings, structures, etc.).
 *END_HEADER***************************/
llistPtr CopyList(llistPtr pList, LinkPoolPtr pLinkPool)
{
   llistPtr pCopy=NULL;
   while (pList)
   {
      InsertLink(pList->p, &pCopy, pLinkPool);
      pList = pList->pNext;
   }
   ReverseList(&pCopy);
   return pCopy;
}  /* CopyList */

/*FUNCTION_HEADER**********************
   NAME:    ;CopyListOfLists
   DESC:    Make a copy of a linked list of linked lists of pointers.
   IN:      pMainList - List of lists to copy.
            pLinkPool - Link pool to use.
   OUT:     n/a
   RETURN:  Pointer to the newly-built copy of pMainList, containing
              newly-allocated lists of pointers to the same things
              as the original list points to.
   NOTES:   Does not share any links with pMainList, but DOES point
              to the same ultimate addresses.
 *END_HEADER***************************/
llistPtr CopyListOfLists(llistPtr pMainList, LinkPoolPtr pLinkPool)
{
   llistPtr pLink;
   llistPtr pCopy=NULL;
   llistPtr pSubList;
   for (pLink=pMainList; pLink; pLink=pLink->pNext)
   {
      pSubList = CopyList((llistPtr)pLink->p, pLinkPool);
      InsertLink(pSubList, &pCopy, pLinkPool);
   }
   ReverseList(&pCopy);
   return pCopy;
}  /* CopyListOfLists */

/*FUNCTION_HEADER**********************
   NAME:    ;CopyDGraph
   DESC:    Make a copy of a DGraph.
   IN:      pDGraph - DGraph to copy.
            pLinkPool - Link pool to use.
   OUT:     n/a
   RETURN:  Pointer to the newly-built DGraph.
   NOTES:   Will only allocate enough nodes to accomodate the current pDGraph->iNumNodes,
              even if pDGraph originally had more nodes than that allocated (before
              combining some nodes).
 *END_HEADER***************************/
DGraphPtr CopyDGraph(DGraphPtr pDGraph, LinkPoolPtr pLinkPool)
{
   DGraphPtr pCopy;
   DNodePtr  pNode, pPrevNode, pNextNode;
   SDWORD    iNode;
   llistPtr  pLink;

   DumpDGraph(pDGraph, "Copying this DGraph:");

   /* Allocate a DGraph */
   pCopy = FNX_CALLOC(1,sizeof(DGraph));

   /* Copy the nodes */
   pCopy->iNumNodes = pDGraph->iNumNodes;
   /* Allocate an additional node to allow for a node to be split (as is often
      done when calling this routine). */
   pCopy->pNodeBuf = (DNodePtr)   FNX_CALLOC(pCopy->iNumNodes+1, sizeof(DNode)); // +1 to allow for a node split.
   
   /* Point the array ppNodes[] at the actual nodes, and set the nodes' ID and phoneme. */
   pCopy->ppNodes  = (DNodePtr *) FNX_CALLOC(pCopy->iNumNodes+1, sizeof(DNodePtr)); // +1 to allow for a node split.
   for (iNode=0; iNode < pCopy->iNumNodes; iNode++)
      pCopy->ppNodes[iNode] = &pCopy->pNodeBuf[iNode];
   for (iNode=0; iNode < pCopy->iNumNodes; iNode++)
   { 
      pNode = pCopy->ppNodes[iNode];
      pNode->iID = iNode;
      FNX_ASSERT(pNode->pPrev==NULL && pNode->pNext==NULL);
      pNode->pDisjunction = CopyListOfLists(pDGraph->ppNodes[iNode]->pDisjunction, pLinkPool);
      pNode->bOptional    = pDGraph->ppNodes[iNode]->bOptional;
      pNode->pSymbols     = CopyList(pDGraph->ppNodes[iNode]->pSymbols, pLinkPool);

      /* Copy the prev and next lists, and replace pointers to nodes in pDGraph
         with pointers to corresponding nodes in pCopy. */
      pNode->pPrev = CopyList(pDGraph->ppNodes[iNode]->pPrev, pLinkPool);
      for (pLink=pNode->pPrev; pLink; pLink=pLink->pNext)
      {
         pPrevNode = (DNodePtr) pLink->p;
         if (pPrevNode->iID==INIT_NODE_ID)
            pLink->p = &pCopy->InitNode;
         else pLink->p = pCopy->ppNodes[pPrevNode->iID];
      }
      pNode->pNext = CopyList(pDGraph->ppNodes[iNode]->pNext, pLinkPool);
      for (pLink=pNode->pNext; pLink; pLink=pLink->pNext)
      {
         pNextNode = (DNodePtr) pLink->p;
         if (pNextNode->iID == END_NODE_ID)
            pLink->p = &pCopy->EndNode;
         else pLink->p = pCopy->ppNodes[pNextNode->iID];
      }
   }

   /* Copy the InitNode and EndNode information */
   memcpy(&pCopy->InitNode, &pDGraph->InitNode, sizeof(DNode));
   pCopy->InitNode.pNext = CopyList(pDGraph->InitNode.pNext, pLinkPool);
   for (pLink=pCopy->InitNode.pNext; pLink; pLink=pLink->pNext)
   {
      pNextNode = (DNodePtr) pLink->p;
      if (pNextNode->iID == END_NODE_ID)
         pLink->p = &pCopy->EndNode;
      else pLink->p = pCopy->ppNodes[pNextNode->iID];
   }

   memcpy(&pCopy->EndNode,  &pDGraph->EndNode,  sizeof(DNode));
   pCopy->EndNode.pPrev = CopyList(pDGraph->EndNode.pPrev, pLinkPool);
   for (pLink=pCopy->EndNode.pPrev; pLink; pLink=pLink->pNext)
   {
      pPrevNode = (DNodePtr) pLink->p;
      if (pPrevNode->iID==INIT_NODE_ID)
         pLink->p = &pCopy->InitNode;
      else pLink->p = pCopy->ppNodes[pPrevNode->iID];
   }

   //DumpDGraph(pCopy, "Here is the copy of the original DGraph:");

#ifdef DEBUG_DGRAPH
   //if (!SameDGraphs(pDGraph, pCopy))
   //   FNX_PRINTF("Uh-oh! Copy not the same as the original!\n");
#endif
   return pCopy;
}  /* CopyDGraph */

/*FUNCTION_HEADER**********************
   NAME:    ;RecurseDGraph
   DESC:    Recursively add symbols of all nodes to a list.
   IN:      pNodes - List of nodes to recursively visit.
            ppSymbols - Address in which to return the list of symbols for the first pronunciation.
            ppCurrent - Address of list of symbols so far in the current pronunciation.
            ppDisjunction - Address in which to return a list of the disjunctions
                            (i.e., all pronunciations after the first one)
            pbOptional    - Address in which to return a flag indicating whether the
                              returned pronunciation is optional.
   OUT:     *ppSymbols has symbols added to it.
   RETURN:  n/a
   NOTES:   If there is more than one node in pNodes, then each will
              be added as a disjunction.
            For example, given a->b,c; b->c,d; c->d as the links in a graph
              with nodes a,b,c,d; This is an ambiguous graph which could be
              described with pronunciations "a(b[c]|c)d", "a(b|[b]c)d",
              or enumerated as "a b c d|a b d|a c d", which is what this
              routine would do.
            The symbols are on the list in reverse order
            This routine does NOT put parentheses around the final result.
 *END_HEADER***************************/
void RecurseDGraph(DNodePtr pNode, llistPtr *ppSymbols, llistPtr *ppCurrent, llistPtr *ppDisjunction, LinkPoolPtr pLinkPool, BOOL *pbOptional)
{
   llistPtr pLink, pCopy;
   SDWORD   i, iNumInserted;
   if (!pNode)
      return;
   if (pNode->iID == END_NODE_ID)
   {
      /* We've reached the end of a pronunciation, so add ppCurrent's symbols onto ppSymbols. */
      if (*ppCurrent==NULL) // empty pronunciation, indicating that InitNode was connected to EndNode,
         *pbOptional=TRUE;  // so the entire disjunction is optional.
      else
      {
         /* Make a copy of *ppCurrent, since nodes may be reused in other pronunciations */
         pCopy = CopyList(*ppCurrent, pLinkPool);
         if (*ppSymbols)
         {
            /* There is already a "first" pronunciation, so add stuff to the disjunction list */
            InsertLink(pCopy, ppDisjunction, pLinkPool);
         }
         else
         {
            /* This is the first pronunciation, so put the symbols in there */
            *ppSymbols = pCopy;
         }
      }
   }
   else
   {
      if (pNode->iID == INIT_NODE_ID)
         iNumInserted=0;
      else
      {
         /* This is not the initial node, so it should have some symbols. */
         /* Put () or [] around it if needed before allowing it to be combined 
            with others. (e.g., if a node had "a | b", and it was being concatenated
            with "c d" before being "or-ed" with "e f", we need "(a|b)c d|e f", 
            NOT "a|b c d|e f", which is very different.*/
         PrepNode(pNode, pLinkPool);
         /* Create a copy of the symbols to be inserted into ppCurrent */
         pCopy = CopyList(pNode->pSymbols, pLinkPool);
         iNumInserted = ListSize(pCopy);
         InsertList(ppCurrent, pCopy);
      }
      /* Now recurse to all following nodes. */
      for (pLink=pNode->pNext; pLink; pLink=pLink->pNext)
         RecurseDGraph((DNodePtr)pLink->p, ppSymbols, ppCurrent, ppDisjunction, pLinkPool, pbOptional);
      /* Now remove the symbols from ppCurrent that came from pCopy */
      for (i=0; i<iNumInserted; i++)
         RemoveLink(ppCurrent, pLinkPool);
   }
}  /* RecurseDGraph */

/*FUNCTION_HEADER**********************
   NAME:    ;ConcatAdjacent
   DESC:    Look for adjacent nodes that connect only to each other and concatenate them into one node.
   IN:      pDGraph   - Graph to look for such combinations in.
            pLinkPool - Pool of links to use.
   OUT:     Some nodes in pDGraph may be merged
   RETURN:  TRUE if any nodes were merged, FALSE otherwise (i.e., bProgress).
   NOTES:   "Rule 1", described in Randy Wilson's Log Book V, page 30.
 *END_HEADER***************************/
BOOL ConcatAdjacent(DGraphPtr pDGraph, LinkPoolPtr pLinkPool)
{
   SDWORD iNode;
   DNodePtr pNode, pNextNode, pLaterNode;
   llistPtr pLink;
   BOOL bProgress=FALSE;

   /*** Rule 1: If a node has one following node, and its following node
        has only one preceding node, then concatenate them into one node. */
   for (iNode=0; iNode < pDGraph->iNumNodes; iNode++)
   {
      pNode = pDGraph->ppNodes[iNode];
      FNX_ASSERT(pNode);
      /* See if pNode has exactly one following node that has exactly one preceding node.
         Also, make sure the following node is not END_NODE, since we don't want to combine
         with that! */
      if (ListSize(pNode->pNext)==1)
      {
         pNextNode = (DNodePtr)pNode->pNext->p;
         if (ListSize(pNextNode->pPrev)==1 && pNextNode->iID>=0)
         {
            FNX_ASSERT((DNodePtr)pNextNode->pPrev->p==pNode);
            /*** Combine pNextNode into pNode. */
            /* 1. Prepare pNode for concatenation. */
            PrepNode(pNode, pLinkPool);
            PrepNode(pNextNode, pLinkPool);
            /* 2. Concatenate pNextNode's symbols onto the end of pNode's symbols
                  (by inserting its symbols BEFORE pNode's symbols, since the list is backwards). */
            InsertList(&pNode->pSymbols, pNextNode->pSymbols);
            /* 3. Free up pNode's next list and replace it with pNextNode's next list. */
            FreeList(&pNode->pNext, pLinkPool);
            pNode->pNext = pNextNode->pNext;
            /* 4. Free up pNextNode's prev and next list */
            FreeList(&pNextNode->pPrev, pLinkPool);
            pNextNode->pNext = NULL; // Don't free this list, since it was swiped by pNode->pNext.
            /* 5. Replace all 'prev' pointers back to pNextNode to point at pNode. */
            for (pLink=pNode->pNext; pLink; pLink=pLink->pNext)
            {
               pLaterNode = (DNodePtr) pLink->p;
               ReplaceLink(pLaterNode->pPrev, pNextNode, pNode);
            }
            /* 6. Remove pNextNode from the list of nodes by sliding the last
                  one down into the place used by pNextNode. */
            pDGraph->ppNodes[pNextNode->iID]      = pDGraph->ppNodes[pDGraph->iNumNodes-1]; /* Move last node down */
            pDGraph->ppNodes[pNextNode->iID]->iID = pNextNode->iID; /* Set the ID of the moved node */
            pDGraph->ppNodes[--pDGraph->iNumNodes] = NULL; /* Set last node to NULL and decrease node count */

            bProgress=TRUE;
            iNode--; /* Undo "iNode++" to try again on the same node to see if the 
                        NEW next node can also be concatenated. */
            DumpDGraph(pDGraph, "[Rule 1: concatenation]");///
         }  /* If concatenating */
      }  /* if one next node */
   }  /* for iNode [Rule 1]*/

   return bProgress;
}  /* Rule 1: ConcatAdjacent */

/*FUNCTION_HEADER**********************
   NAME:    ;CombineDisjunctions
   DESC:    Look for nodes with the same prev and next lists, 
              and combine them into a disjunction node.
   IN:      pDGraph   - Graph to look for such combinations in.
            pLinkPool - Pool of links to use.
   OUT:     Some nodes in pDGraph may be merged
   RETURN:  TRUE if any nodes were merged, FALSE otherwise (i.e., bProgress).
   NOTES:   "Rule 2", described in Randy Wilson's Log Book V, page 30.
 *END_HEADER***************************/
BOOL CombineDisjunctions(DGraphPtr pDGraph, LinkPoolPtr pLinkPool)
{
   SDWORD iNode;
   DNodePtr pNode, pBuddyNode, pPrevNode, pBuddyPrevNode, pBuddyNextNode;
   llistPtr pPrevLink, pBuddyPrevLink, pBuddyLink, pBuddyNextLink, pNextBuddyLink;
   BOOL bProgress=FALSE;

   /*** Rule 2: If two nodes have the same set of preceding AND following nodes,
        then concatenate them into a disjunction */
   for (iNode=0; iNode < pDGraph->iNumNodes; iNode++)
   {
      pNode = pDGraph->ppNodes[iNode];
      FNX_ASSERT(pNode);
      for (pPrevLink = pNode->pPrev; pPrevLink; pPrevLink=pPrevLink->pNext)
      {
         pPrevNode = (DNodePtr) pPrevLink->p;
         for (pBuddyLink = pPrevNode->pNext; pBuddyLink; pBuddyLink=pNextBuddyLink)
         {
            /* Remember this in case we delete pNextLink, which will happen if
               pBuddyNode gets merged into pNode. */
            pNextBuddyLink = pBuddyLink->pNext;
            pBuddyNode = (DNodePtr) pBuddyLink->p;
            if (pBuddyNode != pNode && SameLists(pBuddyNode->pNext, pNode->pNext)
                && SameLists(pBuddyNode->pPrev, pNode->pPrev))
            {
               /* Found two nodes with the same prev & next lists, so they can be
                  combined into a disjuction ("or") node */
               /* 1. Remove all pointers from previous and following nodes to pBuddyNode */
               for (pBuddyPrevLink = pBuddyNode->pPrev; pBuddyPrevLink; pBuddyPrevLink=pBuddyPrevLink->pNext)
               {
                  pBuddyPrevNode = (DNodePtr) pBuddyPrevLink->p;
                  RemovePointerFromList(pBuddyNode, &pBuddyPrevNode->pNext, pLinkPool);
               }
               FreeList(&pBuddyNode->pPrev, pLinkPool);
               for (pBuddyNextLink = pBuddyNode->pNext; pBuddyNextLink; pBuddyNextLink=pBuddyNextLink->pNext)
               {
                  pBuddyNextNode = (DNodePtr) pBuddyNextLink->p;
                  RemovePointerFromList(pBuddyNode, &pBuddyNextNode->pPrev, pLinkPool);
               }
               FreeList(&pBuddyNode->pNext, pLinkPool);
               
               /* 2. Move all of pBuddyNode's symbols (and disjunctive symbol lists)
                     to pNode's pDisjunction list. */
               InsertLink(pBuddyNode->pSymbols, &pNode->pDisjunction, pLinkPool);
               pBuddyNode->pSymbols=NULL;
               InsertList(&pNode->pDisjunction, pBuddyNode->pDisjunction);
               pBuddyNode->pDisjunction = NULL;
               
               /* 3. If (a|[b])=>[a|b], so if pBuddyNode is optional, that makes pNode optional, too. */
               if (pBuddyNode->bOptional)
                  pNode->bOptional=TRUE;
               
               /* 4. Remove pBuddyNode from the list of nodes by sliding the last
                     one down into the place used by pNextNode. */
               pDGraph->ppNodes[pBuddyNode->iID]      = pDGraph->ppNodes[pDGraph->iNumNodes-1]; /* Move last node down */
               pDGraph->ppNodes[pBuddyNode->iID]->iID = pBuddyNode->iID; /* Set the ID of the moved node */
               pDGraph->ppNodes[--pDGraph->iNumNodes] = NULL; /* Set last node to NULL and decrease node count */
               bProgress=TRUE;
               DumpDGraph(pDGraph, "[Rule 2: Disjunction]");///
            }  /* if there's a buddy node */
         }  /* for each possible buddy node */
      }  /* for each pNode->pPrev */
   }  /* for iNode [Rule 2] */

   return bProgress;
}  /* Rule 2: CombineDisjunctions */

/*FUNCTION_HEADER**********************
   NAME:    ;FindOptional
   DESC:    Look for nodes with exactly one prev and next node which point to each other,
              and make the node optional.
   IN:      pDGraph   - Graph to look for such combinations in.
            pLinkPool - Pool of links to use.
   OUT:     Some nodes in pDGraph may become "optional", and links "around" them removed.
   RETURN:  TRUE if any nodes were made optional, FALSE otherwise (i.e., bProgress).
   NOTES:   "Rule 3", described in Randy Wilson's Log Book V, page 30.
 *END_HEADER***************************/
BOOL FindOptional(DGraphPtr pDGraph, LinkPoolPtr pLinkPool)
{
   SDWORD iNode;
   DNodePtr pNode, pPrevNode, pNextNode;
   BOOL bProgress=FALSE;

   /*** 3. Look for optional nodes, i.e., those with exactly one prev and next node
           which point to the node and each other in their next and prev lists, respectively */
   for (iNode=0; iNode < pDGraph->iNumNodes; iNode++)
   {
      pNode = pDGraph->ppNodes[iNode];
      FNX_ASSERT(pNode);
      if (ListSize(pNode->pPrev)==1 && ListSize(pNode->pNext)==1)
      {
         /* pNode has exactly one prev and one next node.  Now see if they
            both point at pNode and each other */
         pPrevNode = (DNodePtr)pNode->pPrev->p;
         pNextNode = (DNodePtr)pNode->pNext->p;
         if (LinkExists(pNextNode, pPrevNode->pNext) && LinkExists(pPrevNode, pNextNode->pPrev))
         {
            // This should be true, since pNode pointed to these two nodes and links should be bidirectional.
            FNX_ASSERT(LinkExists(pNode, pPrevNode->pNext) && LinkExists(pNode, pNextNode->pPrev));
            /* The two nodes around pNode each point to pNode and each other,
               so we can remove the links between pPrevNode and pNextNode and make
               pNode "optional". */
            RemovePointerFromList(pNextNode, &pPrevNode->pNext, pLinkPool);
            RemovePointerFromList(pPrevNode, &pNextNode->pPrev, pLinkPool);
            FNX_ASSERT(pNode->bOptional==FALSE); /* Shouldn't become optional more than once! */
            pNode->bOptional=TRUE;
            bProgress=TRUE;
            DumpDGraph(pDGraph, "[Rule 3: Optional]");///
         }  /* if found an optional node */
      }  /* if pNode has exactly one prev and next node */
   }  /* for iNode [Rule 3] */

   return bProgress;
}  /* Rule 3: FindOptional */

/*FUNCTION_HEADER**********************
   NAME:    ;FindComplexOptional
   DESC:    Look for nodes that can be optional, even if they have multiple prev or next nodes (but not both).
   IN:      pDGraph   - Graph to look for such combinations in.
            pLinkPool - Pool of links to use.
   OUT:     Some nodes in pDGraph may become "optional", and links "around" them removed.
   RETURN:  TRUE if any nodes were made optional, FALSE otherwise (i.e., bProgress).
   NOTES:   "Rule 4", described in Randy Wilson's Log Book V, page 131.
            This rule would handle those optional nodes found in Rule 3, but is a bit slower,
              so rules 1-3 are applied until no further progress can be made, and then this
              routine is tried to see if more complicated matches exist.
            This rule allows a node to become "optional" if it has:
              (a) exactly 1 prev node, and pPrev->pNext is the same as pNode->pNext plus pNode itself.
              (b) exactly 1 next node, which comes from this node and exactly all of
                  the nodes in pNode->pPrev.
 *END_HEADER***************************/
BOOL FindComplexOptional(DGraphPtr pDGraph, LinkPoolPtr pLinkPool)
{
   SDWORD iNode;
   DNodePtr pNode, pPrevNode, pNextNode;
   llistPtr pNextLink, pPrevLink;
   BOOL bProgress=FALSE;

   /*** 4. Look for more complicated optional nodes, i.e., those with 
           (a) exactly 1 prev node, and pPrev->pNext is the same as pNode->pNext plus pNode itself.
           (b) exactly 1 next node, which comes from this node and exactly all of
               the nodes in pNode->pPrev. */
   for (iNode=0; iNode < pDGraph->iNumNodes; iNode++)
   {
      pNode = pDGraph->ppNodes[iNode];
      FNX_ASSERT(pNode);
      if (ListSize(pNode->pPrev)==1)
      {
         /* pNode has exactly one prev node, so see if it is possible
            that pPrevNode points only at pNode and its pNext nodes. */
         pPrevNode = (DNodePtr)pNode->pPrev->p;
         if (ListSize(pPrevNode->pNext)==ListSize(pNode->pNext)+1)
         {
            for (pNextLink=pNode->pNext; pNextLink; pNextLink=pNextLink->pNext)
            {
               if (!LinkExists(pNextLink->p, pPrevNode->pNext))
                  break;
            }
            if (pNextLink==NULL)
            {
               /* All of the nodes in pNode->pNext were also in pPrevNode->pNext,
                  which has the same number of nodes + 1 (for pNode), so we can
                  make pNode optional and remove links from pPrevNode to all other following nodes. */
               // This should be true, since pNode pointed to this node and links should be bidirectional.
               FNX_ASSERT(LinkExists(pNode, pPrevNode->pNext));
               pNode->bOptional=TRUE;
               for (pNextLink=pNode->pNext; pNextLink; pNextLink=pNextLink->pNext)
               {
                  pNextNode = (DNodePtr)pNextLink->p;
                  RemovePointerFromList(pPrevNode, &pNextNode->pPrev, pLinkPool);
                  RemovePointerFromList(pNextNode, &pPrevNode->pNext, pLinkPool);
               }
               /* Now that we know that pPrevNode and pNode are in sequence
                  with one-to-one linkage, we could concatenate them together.
                  For now, let Rule 1 take care of that the next time around. */
               bProgress=TRUE;
               DumpDGraph(pDGraph, "[Rule 4a: Complex optional]");///
            }  /* if found an optional node */
         }  /* if sizes match */
      }  /* if pNode has exactly one prev node */
      else if (ListSize(pNode->pNext)==1)
      {
         /* pNode has exactly one next node, so see if it is possible
            that pNextNode points back only at pNode and its pPrev nodes. */
         pNextNode = (DNodePtr)pNode->pNext->p;
         if (ListSize(pNextNode->pPrev)==ListSize(pNode->pPrev)+1)
         {
            for (pPrevLink=pNode->pPrev; pPrevLink; pPrevLink=pPrevLink->pNext)
            {
               if (!LinkExists(pPrevLink->p, pNextNode->pPrev))
                  break;
            }
            if (pPrevLink==NULL)
            {
               /* All of the nodes in pNode->pPrev were also in pNextNode->pPrev,
                  which has the same number of nodes + 1 (for pNode), so we can
                  make pNode optional and remove links from pNextNode back to all 
                  other previous nodes. */
               // This should be true, since pNode pointed to this nodes and links should be bidirectional.
               FNX_ASSERT(LinkExists(pNode, pNextNode->pPrev));
               pNode->bOptional=TRUE;
               for (pPrevLink=pNode->pPrev; pPrevLink; pPrevLink=pPrevLink->pNext)
               {
                  pPrevNode = (DNodePtr)pPrevLink->p;
                  RemovePointerFromList(pNextNode, &pPrevNode->pNext, pLinkPool);
                  RemovePointerFromList(pPrevNode, &pNextNode->pPrev, pLinkPool);
               }
               /* Now that we know that pNode and pNextNode are in sequence
                  with one-to-one linkage, we could concatenate them together.
                  For now, let Rule 1 take care of that the next time around. */
               bProgress=TRUE;
               DumpDGraph(pDGraph, "[Rule 4b: Complex optional]");///
            }  /* if found an optional node */
         }  /* if sizes match */
      }
   }  /* for iNode [Rule 4] */
   
   return bProgress;
}  /* Rule 4: FindComplexOptional */

/*FUNCTION_HEADER**********************
 * NAME:   ;SortDNodes
 * DESC:   Reorder the nodes in a DGraph so that all nodes only go to things after them.
 * IN:     pDGraph   - Graph to collapse.
 * OUT:    pDGraph->ppNodes[] is reordered, and each node's ID reflects its new position in the list.
 * RETURN: TRUE if any changes were made; FALSE if already sorted.
 * NOTES:  Assumes there are no cycles in the graph.
 *END_HEADER***************************/
BOOL SortDNodes(DGraphPtr pDGraph)
{
   SDWORD iNode;
   DNodePtr pNode, pNextNode;
   BOOL bChanges=FALSE;
   llistPtr pLink;

   DumpDGraph(pDGraph, "Before sorting:");
   for (iNode=0; iNode<pDGraph->iNumNodes; iNode++)
   {
      /* Check to see if this node goes to anything before it. */
      pNode = pDGraph->ppNodes[iNode];
      for (pLink=pNode->pNext; pLink; pLink=pLink->pNext)
      {
         pNextNode=(DNodePtr)pLink->p;
         if (pNextNode->iID < pNode->iID && pNextNode->iID != END_NODE_ID)
         {
            /* Swap pNextNode and pNode */
            SDWORD iOldID, iOldNextID;
            iOldID = pNode->iID;
            iOldNextID = pNextNode->iID;
            pDGraph->ppNodes[iOldNextID]=pNode;
            pDGraph->ppNodes[iOldID]=pNextNode;
            pNode->iID=iOldNextID;
            pNextNode->iID=iOldID;
            iNode = pNode->iID-1; // to make up for the "++"
            bChanges=TRUE; // Remember that changes were made.
            break; // Exit the for(pLink) loop and re-check this node.
         }  /* if out of order */
      }  /* for pLink */
   }  /* for iNode */

   DumpDGraph(pDGraph, "After sorting:");
   return bChanges;
}  /* SortDNodes */

/*FUNCTION_HEADER**********************
 * NAME:   ;FindSplitPoint
 * DESC:   Look for a place in the graph where it can be split into multiple independent parts.
 * IN:     pDGraph - Graph to look for a split point in.
 * OUT:    Sorts pDGraph->ppNodes[].
 * RETURN: Index in pDGraph->ppNodes[] after which the graph can be split, or -1 if none.
 * NOTES:  This is tricky, but here goes: "Any nodes before the split point that
             go to any nodes after the split point must go to the SAME SET of
             nodes after the split point (even if they also connect to different
             nodes before the split point)."  See Randy Wilson's Log Book V, page 134,
             for examples.
 *END_HEADER***************************/
SDWORD FindSplitPoint(DGraphPtr pDGraph)
{
   SDWORD iSplitPoint; /* Index in pDGraph->ppNodes[] of the node after 
                          which we are considering splitting the graph */
   SDWORD iFromNode;   /* Index of the current node before the split point (InitNode and node 0..iSplitPoint) */
   DNodePtr pFromNode; /* Pointer to the current node */
   llistPtr pNextLink; /* Position in the current node's pNext list */
   DNodePtr pNextNode; /* Pointer to the current next node */
   llistPtr pNextList; /* "pNext" list of the first node found that went to nodes after the split point */
   BOOL     bCrossed;  /* Flag for whether pFromNode had something in its pNext list after iSplitPoint */
   BOOL     bMismatch; /* Flag for whether pFromNode did not have the same set of things after iSplitPoint as pNextList */

   SortDNodes(pDGraph);
   FNX_ASSERT(!SortDNodes(pDGraph)); // Make sure graph is now sorted.

   /* Check for each possible split point (don't bother trying to split
      before the first node nor after the last node.  Use 'iNumNodes-1'
      so that we don't try splitting after the last node.) */
   for (iSplitPoint=0; iSplitPoint<pDGraph->iNumNodes-1; iSplitPoint++)
   {
      /* See if the graph can be split between node iSplitPoint and iSplitPoint+1.
         This is possible if all nodes before the split point that
         goes to anything after the split point, go to the same set of
         nodes after the split point (even if they also go to other different
         nodes before the split point). */
      pNextList = NULL;
      bMismatch = FALSE; /* Indicate that we haven't found a problem with splitting at iSplitPoint yet. */
      for (iFromNode=-1; iFromNode<=iSplitPoint && !bMismatch; iFromNode++)
      {
         if (iFromNode==-1)
            pFromNode = &pDGraph->InitNode;
         else pFromNode = pDGraph->ppNodes[iFromNode];
         bCrossed = FALSE;
         for (pNextLink=pFromNode->pNext; pNextLink && !bCrossed; pNextLink=pNextLink->pNext)
         {
            pNextNode = (DNodePtr)pNextLink->p;
            if (pNextNode->iID > iSplitPoint || pNextNode->iID==END_NODE_ID)
            {
               /* Indicate that pFromNode does indeed go to something beyond iSplitPoint,
                  and that we have checked to see if it matches or not. */
               bCrossed = TRUE;
               /* iFromNode is before the split point, and goes to
                  something after the split point.  See if this is the
                  first node that has done so. */
               if (!pNextList)
               {
                  /* This is the first node we have found before the split point
                     that goes to anything after it, so use its list as the one
                     to compare all others with. */
                  pNextList = pFromNode->pNext;
               }
               else
               {
                  /* Compare pFromNode->pNext with pNextList to make sure that
                     they both have the same set of nodes, NOT including any
                     nodes before the split point. */
                  llistPtr pLink1, pLink2;
                  DNodePtr pNode1, pNode2;
                  llistPtr pList1=pFromNode->pNext, pList2=pNextList;

                  /* Make sure everything in list 1 (after the split point) is in list 2 */
                  for (pLink1=pList1; pLink1 && !bMismatch; pLink1=pLink1->pNext)
                  {
                     pNode1 = (DNodePtr)pLink1->p;
                     if (pNode1->iID > iSplitPoint || pNode1->iID == END_NODE_ID)
                     {
                        for (pLink2=pList2; pLink2; pLink2=pLink2->pNext)
                        {
                           pNode2 = (DNodePtr)pLink2->p;
                           if (pNode2->iID == pNode1->iID)
                              break;
                        }
                        if (pLink2==NULL)
                           bMismatch=TRUE; /* Couldn't find pNode1->iID in pList2 */
                     }
                  }  /* for pLink1 */
                  
                  /* Make sure everything in list 2 (after the split point) is in list 1 */
                  for (pLink2=pList2; pLink2 && !bMismatch; pLink2=pLink2->pNext)
                  {
                     pNode2 = (DNodePtr)pLink2->p;
                     if (pNode2->iID > iSplitPoint || pNode2->iID == END_NODE_ID)
                     {
                        for (pLink1=pList1; pLink1; pLink1=pLink1->pNext)
                        {
                           pNode1 = (DNodePtr)pLink1->p;
                           if (pNode1->iID == pNode2->iID)
                              break;
                        }
                        if (pLink1==NULL)
                           bMismatch=TRUE; /* Couldn't find pNode1->iID in pList2 */
                     }
                  }  /* for pLink2 */
               }  /* else check for mismatches */
            } /* if next node > split point */
         } /* for pNextLink */
      } /* for iFromNode */
      if (!bMismatch)
      { 
         /* All nodes before the split point that go to anything after the split point
            go to the same set of after-split-point-nodes.  So return the index of
            the node after which the graph can be split. */
         return iSplitPoint;
      }
   } /* for iSplitPoint */
   return -1; /* No valid split point found */
}  /* FindSplitPoint */

/*FUNCTION_HEADER**********************
 * NAME:   ;SplitDGraph
 * DESC:   Split a DGraph into two parts.
 * IN:     pDGraph - DGraph to split.
           iSplitPoint - Split point to use, i.e., all nodes after iSplitPoint go into new graph.
           pLinkPool - Link pool to use.
 * OUT:    pDGraph retains only nodes 0..iSplitPoint, and all nodes after that go into
             a newly-allocated graph.
 * RETURN: Pointer to the newly-allocated graph containing the right half of the graph.
 * NOTES:  Assumes that pDGraph has already been sorted, and that the split point has
             already been found.  There should be at least one node on each side of the
             split point.
 *END_HEADER***************************/
DGraphPtr SplitDGraph(DGraphPtr pDGraph, SDWORD iSplitPoint, LinkPoolPtr pLinkPool)
{
   DGraphPtr pRightGraph; /* New DGraph containing the nodes after the split point */
   SDWORD iNode;
   DNodePtr pNode, pNextNode, pPrevNode;
   llistPtr pLink;
   BOOL bCrossed, bSawEndNode, bSawInitNode;
   llistPtr *ppPrev; /* ADDRESS of "next" pointer that might need to be updated */

   FNX_ASSERT(!SortDNodes(pDGraph)); // make sure nodes are sorted.
   FNX_ASSERT(iSplitPoint>=0 && iSplitPoint < pDGraph->iNumNodes-1); // make sure we're doing a real split.

   /* Make a copy of pDGraph before we start messing with anything. */
   pRightGraph = CopyDGraph(pDGraph, pLinkPool);
   
   /* Go through the nodes we're keeping in pDGraph and for any nodes
      that connect to anything after the split point, remove links to
      nodes after the split point and add a single link to the EndNode, if necessary. */
   for (iNode=-1; iNode<=iSplitPoint; iNode++)
   {
      if (iNode==-1) //INIT_NODE_ID
         pNode = &pDGraph->InitNode;
      else pNode = pDGraph->ppNodes[iNode];
      bCrossed=FALSE;
      bSawEndNode=FALSE;
      ppPrev = &pNode->pNext;
      for (pLink = *ppPrev; pLink; pLink=*ppPrev)
      {
         pNextNode = (DNodePtr)pLink->p;
         if (pNextNode->iID > iSplitPoint || pNextNode->iID==END_NODE_ID)
         {
            bCrossed=TRUE; /* Indicate that this node is connected to something after the Split Point */
            if (pNextNode->iID == END_NODE_ID)
            {
               FNX_ASSERT(!bSawEndNode); // Make sure EndNode is not in the list twice!
               bSawEndNode=TRUE;
               ppPrev = &pLink->pNext;
            }
            else RemoveLink(ppPrev, pLinkPool);
         }
         else ppPrev = &pLink->pNext;
      }  /* for pLink */
      if (bCrossed && !bSawEndNode)
      {
         /* If pNode crossed the split point and is not already connected to the
            EndNode, then connect it to the EndNode (of this new, shrunken graph). */
         ConnectDNodes(pNode, &pDGraph->EndNode, pLinkPool);
      }
   }  /* for iNode */
   
   /* Remove all links from the EndNode to any nodes after the split point */
   /* (Use ppPrev to point at the POINTER that needs to be updated if a link
      is removed.  It starts out pointing at EndNode->pPrev, and then points
      to the "pNext" pointer of the previous link.  That way, when RemoveLink
      is called, we can always update the pointer that pointed to pLink,
      regardless of whether it was at the head of the list). */
   ppPrev = &pDGraph->EndNode.pPrev;
   for (pLink=*ppPrev; pLink; pLink=*ppPrev)
   {
      pNode = (DNodePtr)pLink->p;
      if (pNode->iID > iSplitPoint)
         RemoveLink(ppPrev, pLinkPool);
      else ppPrev = &pLink->pNext;
   }
   for (iNode=iSplitPoint+1; iNode<pDGraph->iNumNodes; iNode++)
      ClearDNode(pDGraph->ppNodes[iNode], pLinkPool);
   pDGraph->iNumNodes = iSplitPoint+1;
   DumpDGraph(pDGraph, "Left half of graph:");

   /*****/
   /* Now fix pRight: Go through the nodes we're keeping in pRight and for any nodes
      that connect to anything before the split point, remove links to
      nodes before the split point and add a single link to the InitNode, if necessary. */
   for (iNode=iSplitPoint+1; iNode<=pRightGraph->iNumNodes; iNode++)
   {
      if (iNode==pRightGraph->iNumNodes)
         pNode = &pRightGraph->EndNode;
      else pNode = pRightGraph->ppNodes[iNode];
      bCrossed=FALSE;
      bSawInitNode=FALSE;
      ppPrev = &pNode->pPrev;
      for (pLink = *ppPrev; pLink; pLink=*ppPrev)
      {
         pPrevNode = (DNodePtr)pLink->p;
         if (pPrevNode->iID <= iSplitPoint || pPrevNode->iID==INIT_NODE_ID)
         {
            bCrossed=TRUE; /* Indicate that this node is connected to something before the Split Point */
            if (pPrevNode->iID == INIT_NODE_ID)
            {
               FNX_ASSERT(!bSawInitNode); // Make sure InitNode is not in the list twice!
               bSawInitNode=TRUE;
               ppPrev = &pLink->pNext;
            }
            else RemoveLink(ppPrev, pLinkPool);
         }
         else ppPrev = &pLink->pNext;
      }  /* for pLink */
      if (bCrossed && !bSawInitNode)
      {
         /* If pNode crossed the split point and is not already connected to the
            InitNode, then connect it to the EndNode (of this new, shrunken graph). */
         ConnectDNodes(&pRightGraph->InitNode, pNode, pLinkPool);
      }
   }  /* for iNode */
   
   /* Remove all links from the InitNode to any nodes before the split point */
   ppPrev = &pRightGraph->InitNode.pNext;
   for (pLink = *ppPrev; pLink; pLink = *ppPrev)
   {
      pNode = (DNodePtr)pLink->p;
      if (pNode->iID <= iSplitPoint && pNode->iID != END_NODE_ID)
         RemoveLink(ppPrev, pLinkPool);
      else ppPrev = &pLink->pNext;
   }
   pRightGraph->iNumNodes = pRightGraph->iNumNodes - iSplitPoint - 1;

   /* Clear out the nodes that were before the split point */
   for (iNode=0; iNode < iSplitPoint; iNode++)
      ClearDNode(pRightGraph->ppNodes[iNode], pLinkPool);

   /* Slide nodes down to indices beginning at 0. */
   for (iNode=0; iNode < pRightGraph->iNumNodes; iNode++)
   {
      pRightGraph->ppNodes[iNode] = pRightGraph->ppNodes[iNode+iSplitPoint+1];
      pRightGraph->ppNodes[iNode]->iID = iNode;
   }
   DumpDGraph(pRightGraph,"Right half of graph:");
   
   return pRightGraph;
}  /* SplitDGraph */

/*FUNCTION_HEADER**********************
 * NAME:   ;TrySplittingGraph
 * DESC:   Look to see if a DGraph can be split.  If so, do so and recursively
             collapse the two subgraphs, and combine the results.
 * IN:     pDGraph - DGraph to consider splitting.
           pLinkPool - Link pool to use.
 * OUT:    pDGraph might have its nodes collapsed into two nodes representing
             subgraphs that it could be split into.  (Nothing is done if FALSE is returned).
 * RETURN: TRUE if the graph was split, FALSE otherwise.
 * NOTES:  
 *END_HEADER***************************/
BOOL TrySplittingGraph(DGraphPtr pDGraph, LinkPoolPtr pLinkPool)
{
   DGraphPtr pRightGraph;
   SDWORD iSplitPoint;
   DNodePtr pLeftNode, pRightNode;

   /* See if the graph can be split into two completely connected halves */
   iSplitPoint = FindSplitPoint(pDGraph);

   if (iSplitPoint<0)
      return FALSE; /* Couldn't split the graph */
   else
   {
      FNX_ASSERT(pDGraph->iNumNodes >= 2); // make sure we have at least 2 nodes, because we'll need them.
       /* We can split the graph into subparts */
      pRightGraph = SplitDGraph(pDGraph, iSplitPoint, pLinkPool);
      CollapseDGraph(pDGraph, pLinkPool);
      CollapseDGraph(pRightGraph, pLinkPool);
      FNX_ASSERT(pRightGraph->iNumNodes==1 && pDGraph->iNumNodes==1);

      DumpDGraph(pDGraph,"Left Graph:");
      DumpDGraph(pRightGraph,"Right Graph:");

      /* Now that pDGraph and pRightGraph have been collapsed to one node each,
         combine their nodes into a single graph. */
      /* Find an unused node in the node buffer of pDGraph to use for ppNodes[1] */
      if (pDGraph->ppNodes[0] == &pDGraph->pNodeBuf[0])
         pDGraph->ppNodes[1] = &pDGraph->pNodeBuf[1];
      else pDGraph->ppNodes[1] = &pDGraph->pNodeBuf[0];
      pDGraph->iNumNodes = 2;
      pDGraph->ppNodes[1]->iID = 1;

      /* Copy information from pRightGraph->ppNodes[0] over to pDGraph->ppNodes[1], and free up pRightGraph. */
      pLeftNode  = pDGraph->ppNodes[0];
      pRightNode = pDGraph->ppNodes[1];
      pRightNode->pDisjunction = pRightGraph->ppNodes[0]->pDisjunction;
      pRightNode->bOptional    = pRightGraph->ppNodes[0]->bOptional;
      pRightNode->pSymbols     = pRightGraph->ppNodes[0]->pSymbols;
      pRightGraph->ppNodes[0]->pSymbols = NULL;
      pRightGraph->ppNodes[0]->pDisjunction = NULL;
      FreeDGraph(pRightGraph, pLinkPool);

      /* Connect pRightNode to pLeftNode and EndNode */
      pRightNode->pNext = pRightNode->pPrev = NULL; // Clear out these dangling values.
      InsertLink(pLeftNode, &pRightNode->pPrev, pLinkPool);
      InsertLink(&pDGraph->EndNode, &pRightNode->pNext, pLinkPool);

      /* Connect pLeftNode to pRightNode instead of to EndNode */
      FNX_ASSERT(pLeftNode->pNext && pLeftNode->pNext->p == (void *)&pDGraph->EndNode);
      pLeftNode->pNext->p = (void *)pRightNode;

      /* Connect EndNode to pRightNode instead of pLeftNode */
      FNX_ASSERT(pDGraph->EndNode.pPrev->p == (void *)pLeftNode);
      pDGraph->EndNode.pPrev->p = (void *)pRightNode;
    
      DumpDGraph(pDGraph, "After connecting the two halves:");
      return TRUE; /* Was able to split the graph */
   }
   FNX_ASSERT(0); // shouldn't be able to reach here.
}  /* TrySplittingGraph */


/*FUNCTION_HEADER**********************
   NAME:    ;CollapseDGraph
   DESC:    Collapse a pronunciation graph down to a linked list of pronunciation symbols.
   IN:      pDGraph   - Graph to collapse.
            pLinkPool - Pool of links to use.
   OUT:     pDGraph is freed up, and a (hopefully optimal) linked list of symbols is built.
   RETURN:  0 on success, -1 on error (e.g., if recursion too deep).
   NOTES:   The process of collapsation is described in Randy Wilson's Log Book V, 
              pages 30-32 and 131-133.
            Calls itself recursively when it hits inherently ambiguous cases that
              require splitting nodes to continue, in order to try various combinations
              to see which results in the shortest strings.
 *END_HEADER***************************/
llistPtr CollapseDGraph(DGraphPtr pDGraph, LinkPoolPtr pLinkPool)
{
   BOOL bProgress;
   BOOL bOptional;

   DumpDGraph(pDGraph, "Before collapsation:\n");

   /* Apply collapsation rules until no further progress can be made */
   do /* Apply rules 1-4 */
   {
      do /* Apply simple (and faster) rules 1-3 to combine nodes together  */
      {
         bProgress = FALSE;
         /* Rule 1: If a node has one following node, and its following node
            has only one preceding node, then concatenate them into one node. */
         if (ConcatAdjacent(pDGraph, pLinkPool))
            bProgress = TRUE;

         /* Rule 2: If two nodes have the same set of preceding AND following nodes,
            then concatenate them into a disjunction */
         if (CombineDisjunctions(pDGraph, pLinkPool))
            bProgress = TRUE;

         /* Rule 3: Look for optional nodes, i.e., those with exactly one prev and next node
            which point to the node and each other in their next and prev lists, respectively */
         if (FindOptional(pDGraph, pLinkPool))
            bProgress = TRUE;

      } while (bProgress && pDGraph->iNumNodes>1);

      if (pDGraph->iNumNodes>1)
      {
         /*** 4. Look for more complicated optional nodes, i.e., those with 
                 (a) exactly 1 prev node, and pPrev->pNext is the same as pNode->pNext plus pNode itself.
                 (b) exactly 1 next node, which comes from this node and exactly all of
                     the nodes in pNode->pPrev. */
         if (FindComplexOptional(pDGraph, pLinkPool))
            bProgress = TRUE;
//       else if (FindKnownGoobers(pDGraph, pLinkPool))
//          bProgress = TRUE;
         /*** 5. Try splitting the graph into independent portions, and collapsing further there */
         else if (pDGraph->iNumNodes>1 && TrySplittingGraph(pDGraph, pLinkPool))
            bProgress = TRUE;
//       else if (SplitNodes(pDGraph, pLinkPool))
//          bProgress = TRUE;
      }
   } while (bProgress && pDGraph->iNumNodes>1);

   /* No further progress can be made, so see if we have gotten down to one node yet */
   if (pDGraph->iNumNodes > 1)
   {
      /* There were multiple nodes that couldn't be collapsed further.
         If there was a single first and/or last node, pull them off
         and only enumerate the problem part in the middle. */
      SDWORD iResult, iNode;
      DNodePtr pFirstNode, pLastNode, pNextNode, pPrevNode;
      llistPtr pCurrent;
      llistPtr pSymbols;
      llistPtr pLink;
      llistPtr pDisjunction;

      DumpDGraph(pDGraph,"No further progress possible.  Graph:");
#ifdef DUMP_PROBLEMS
      gbOuch=TRUE;
#endif
      if (ListSize(pDGraph->InitNode.pNext)==1)
      {
         /* Remove the first node from the graph, and put its symbols
            and a '(' into 'pSymbols'. */
         pFirstNode = (DNodePtr)pDGraph->InitNode.pNext->p; // Point to first node in network.
         FreeList(&pDGraph->InitNode.pNext, pLinkPool);     // Free up the InitNode's pNext list.
         pDGraph->InitNode.pNext = pFirstNode->pNext;       // Point InitNode at those after the first node
         /* Insert InitNode into the pPrev list of each node following pFirstNode,
            and remove the link to pFirstNode. */
         for (pLink=pFirstNode->pNext; pLink; pLink=pLink->pNext)
         {
            pNextNode = (DNodePtr)pLink->p;
            iResult=RemovePointerFromList(pFirstNode, &pNextNode->pPrev, pLinkPool);
            FNX_ASSERT(iResult==0);//Make sure the pointer was in the list.
            InsertLink(&(pDGraph->InitNode), &pNextNode->pPrev, pLinkPool);
         }
         pFirstNode->pNext=NULL;
      }
      else pFirstNode = NULL;

      if (ListSize(pDGraph->EndNode.pPrev)==1)
      {
         /* Remove the last node from the graph for now */
         pLastNode = (DNodePtr)pDGraph->EndNode.pPrev->p; // Point to the last node in the network
         FreeList(&pDGraph->EndNode.pPrev, pLinkPool);    // Free up the EndNode's pPrev list
         pDGraph->EndNode.pPrev = pLastNode->pPrev;       // Point EndNode at the list of next-to-last nodes
         /* Insert EndNode into the pNext list of each node before pLastNode,
            and remove the link to pLast Node. */
         for (pLink=pLastNode->pPrev; pLink; pLink=pLink->pNext)
         {
            pPrevNode = (DNodePtr)pLink->p;
            iResult=RemovePointerFromList(pLastNode, &pPrevNode->pNext, pLinkPool);
            FNX_ASSERT(iResult==0);//Make sure the pointer was in the list.
            InsertLink(&(pDGraph->EndNode), &pPrevNode->pNext, pLinkPool);
         }
         pLastNode->pPrev=NULL;
      }
      else pLastNode = NULL;

      /* Build a list of symbols for the nodes that are left */
      pSymbols     = NULL;
      pCurrent     = NULL;
      pDisjunction = NULL;
      bOptional    = FALSE;
      RecurseDGraph(&pDGraph->InitNode, &pSymbols, &pCurrent, &pDisjunction, pLinkPool, &bOptional);
      FNX_ASSERT(pCurrent==NULL);

      /* Now force pDGraph to have a single node with pSymbols in it. */
      for (iNode=0; iNode<pDGraph->iNumNodes; iNode++)
         ClearDNode(pDGraph->ppNodes[iNode], pLinkPool);
      FreeList(&pDGraph->InitNode.pNext, pLinkPool);
      FreeList(&pDGraph->EndNode.pPrev, pLinkPool);
      pDGraph->ppNodes[0]->iID = 0;
      pDGraph->ppNodes[0]->pDisjunction = pDisjunction;
      pDGraph->ppNodes[0]->bOptional = bOptional;
      ConnectDNodes(&pDGraph->InitNode, pDGraph->ppNodes[0], pLinkPool);
      ConnectDNodes(pDGraph->ppNodes[0], &pDGraph->EndNode, pLinkPool);
      pDGraph->ppNodes[0]->pSymbols = pSymbols;
      pDGraph->iNumNodes = 1;

      if (pFirstNode || pLastNode)
      {
         PrepNode(pDGraph->ppNodes[0], pLinkPool);
         SurroundSymbols(&pDGraph->ppNodes[0]->pSymbols, "(", ")", pLinkPool);
      }
      if (pFirstNode)
      {
         PrepNode(pFirstNode, pLinkPool);
         InsertList(&pFirstNode->pSymbols, pSymbols);
         pSymbols=pFirstNode->pSymbols;
         pFirstNode->pSymbols=NULL;
      }
      if (pLastNode)
      {
         PrepNode(pLastNode, pLinkPool);
         InsertList(&pSymbols, pLastNode->pSymbols);
         pLastNode->pSymbols=NULL;
      }
   }

   /* At this point, the graph should have been reduced to a single node. */
   FNX_ASSERT(pDGraph->InitNode.pNext && (DNodePtr)pDGraph->InitNode.pNext->p == pDGraph->ppNodes[0]);
   FNX_ASSERT(ListSize(pDGraph->InitNode.pNext)==1 && ListSize(pDGraph->EndNode.pPrev)==1 &&
              pDGraph->InitNode.pNext->p == pDGraph->EndNode.pPrev->p);

#ifdef DEBUG_DGRAPH
   FNX_PRINTF("Output symbols:\n");
   DumpSymbols(pDGraph->ppNodes[0]->pSymbols);
   if (pDGraph->ppNodes[0]->pDisjunction)
   {
      llistPtr pLink;
      for (pLink=pDGraph->ppNodes[0]->pDisjunction; pLink; pLink=pLink->pNext)
      {
         FNX_PRINTF("|");
         DumpSymbols((llistPtr)pLink->p);
      }
   }
#endif
   return 0; /* ok */
}  /* CollapseDGraph */

/*FUNCTION_HEADER**********************
   NAME:    ;GetPronunciation
   DESC:    Get a string containing the pronunciation string for a word.
   IN:      pWord        - Word structure containing a basephone pronunciation graph
            ppSymbolList - Address in which to return a linked list of the symbols (NULL=>don't return list)
            pLinkPool    - Pool of links to use.
   OUT:     a string sPronunciation is allocated
   RETURN:  sPronunciation
   NOTES:   Compresses the pronunciation (e.g., "{a b c e | a c e | a d c e }" -> "(a[b|d]c e)").
            If ppSymbolList=NULL, then it is ignored.  Use &pSymbolList if you
              want a linked list (in reverse order) of the symbols in the pronunciation.
              Note that ppSymbolList contains pointers into the phone strings in pWord,
              so don't free up pWord until you're done with the strings in ppSymbolList
              (or do "for(p=pSymbolList;p;p=p->pNext)p->p=strdup(p->p);" to make copies of the strings).

 *END_HEADER***************************/
char *GetPronunciation(wordTPtr pWord, llistPtr *ppSymbolList, LinkPoolPtr pLinkPool)
{
	char sPronunciation[128];	/* Combined pronunciation */
	DGraphPtr pDGraph;
	llistPtr pSymbols;			/* Linked list of all symbols in the pronunciation (in reverse order) */
	
	if (pWord->numinit==0)
	{
		FNX_ASSERT(pWord->numnodes==0);
		FNX_ASSERT(pWord->numfinal==0);
		return NULL; /* Don't get stuck if there are no nodes */
	}
	
	/* Convert pWord into a Dictionary Graph (DGraph) structure */
	pDGraph = WordToDGraph(pWord, pLinkPool);
	
	/** Combined nodes in the DGraph structure until there is a single node remaining **/
	CollapseDGraph(pDGraph, pLinkPool);
	FNX_ASSERT(pDGraph->iNumNodes==1);
	if (pDGraph->ppNodes[0]->pDisjunction)
		PrepNode(pDGraph->ppNodes[0], pLinkPool);
	else SurroundSymbols(&pDGraph->ppNodes[0]->pSymbols, "(",")",pLinkPool);
	pSymbols= pDGraph->ppNodes[0]->pSymbols;
	pDGraph->ppNodes[0]->pSymbols = NULL;
	FreeDGraph(pDGraph, pLinkPool);
	
	/* Make a copy of the list of symbols to return, since pSymbols will
	be freed up by SymbolsToString(). */

	if (ppSymbolList)
		*ppSymbolList = CopyList(pSymbols, pLinkPool);
	
	/* Convert the list of symbols into a string */
 //   SymbolsToString(pSymbols, pLinkPool);
	
//	return sPronunciation;
}  /* GetPronunciation */

/*FUNCTION_HEADER**********************
   NAME:    ;ShortenPronunciation
   DESC:    Try to compress a pronunciation
   IN:      psPronunciation - Pronunciation to be shortened (if possible)
            pLinkPool - Pool of linked list nodes to use (NULL=>allocate one internally).
   OUT:     *psPronunciation is possibly deallocated in which case a new string is allocated in its place
   RETURN:  n/a
   NOTES:   Compresses the pronunciation (e.g., "{a b c e | a c e | a d c e }" -> "(a[b|d]c e)").
            *psPronunciation is either left unchanged, or is deallocated and
            replaced with a newly-allocated string with a shorter pronunciation.
 *END_HEADER***************************/
void ShortenPronunciation(char **psPronunciation, LinkPoolPtr pLinkPool)
{
   wordTPtr pWord;
   char *sNewPronunciation;
   LinkPoolPtr pMyLinkPool;
   if (pLinkPool)
      pMyLinkPool=pLinkPool;
   else pMyLinkPool = NewLinkPool(100);

   /* Build a word structure with a collapsed pronunciation graph */
   pWord = buildWord(*psPronunciation, "word", NULL);
   /* Convert the collapsed pronunciation graph into a string */
   sNewPronunciation = GetPronunciation(pWord, NULL, pLinkPool);
   if (FNX_STRLEN(sNewPronunciation) < FNX_STRLEN(*psPronunciation))
   {
      FNX_FREE(*psPronunciation);
      *psPronunciation = sNewPronunciation;
   }
   else FNX_FREE(sNewPronunciation);
   if (pLinkPool==NULL)
      FreeLinkPool(pMyLinkPool);
}  /* ShortenPronunciation */
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;WriteVocab    
 * DESC:    Write a vocab structure to a .vocab file.
 * IN:      pVocab - Vocabulary structure to write
            sVocabFileName - Filename to write to (empty or NULL => stdout)
 * OUT:     pVocab's contents are written to sVocabFileName (or to stdout).
 * RETURN:  0 on success, something else on error.
 * NOTES:   if sVocabFileName is NULL or "", then the text is written
              to stdout (i.e., the screen).
            pVocab should have been built WITHOUT expanding the words,
              e.g., ReadVocab(sVocabFile,NULL) should have been used,
              or something equivalent.  If the vocabulary has been
              expanded, then the output pronunciations may have duplicate
              phonemes (one for each category; e.g., the "e" basephone
              would be expanded to the categories "$sil<e <e> e>r" which
              would then be printed as the basephones "e e e".
 *END_HEADER***************************/
#ifndef NO_SYSFILE_WRITES
SDWORD WriteVocab(VocabTPtr pVocab, char *sVocabFileName)
{
   FILE     *fp;
   wordTPtr pWord;
   SDWORD      i, j;
   char     *sGram;
#ifndef FNX_LEAN_AND_MEAN
   char     *sPronunciation;
#endif
   LinkPoolPtr pLinkPool;

   pLinkPool = NewLinkPool(50);

   if (!pVocab->bBasephone)
   {
      Message(NULL,"Error: The vocabulary has been expanded into context-dependent phones.\n");
      Message(NULL,"       File '%s' not written (pass 'NULL' for pDesc into ReadVocab to get basephone vocab)\n");
      return -1;
   }
   if (sVocabFileName && sVocabFileName[0])
   {
      fp = FNX_FOPEN((const char *)sVocabFileName, "wt");
      if (!fp)
      {
         Message(FNX_STDERR, "Couldn't open vocab file '%s' for writing.\n", sVocabFileName);
         return -1;
      }
   }
   else
      fp = FNX_STDOUT;

   for (i = 0; i < pVocab->iNumWords; i++)
   {
      pWord = pVocab->ppWords[i];
      /* Write a word */
      FNX_FPRINTF(fp, "%-20s {", pWord->name);

#ifdef FNX_LEAN_AND_MEAN
      // old way (works, but expands all pronunciations)
      for (j = 0; j < pWord->numinit; j++)
      {
         /* Print all pronunciations beginning with this initial node. */
         /* Note: This will enumerate all pronunciations.  We should probably
            write a routine that will print out the pronunciations according
            to the graph structure that they are in, e.g., "s & m [p] T (i: | I) (n | N)"
            rather than listing all possibilities separately. */
         PrintPronun(pWord, pWord->initnodes[j], "" /* start with empty pronunciation*/,
                  NULL /* no probname=>use base phonemes */, " | " /* between each pronunciation */,
                  j == pWord->numinit-1 /* flag for whether this is the last set of pronunciations */,
                  fp /* output to this file */);
      }
#else // new way (shorter pronunciations.  Might work...)
      sPronunciation = GetPronunciation(pWord, NULL, pLinkPool);
      FNX_FPRINTF(fp, "%s", sPronunciation);
      FNX_FREE(sPronunciation);
#endif
      FNX_FPRINTF(fp, "};\n");
   }  /* for i */

   FNX_FPRINTF(fp,"\n");
   for (i = 0; i < pVocab->iNumGrammarRules; i++)
   {
      sGram = pVocab->psGrammar[i];

      while (*sGram)
      {
         /* Print first 60 characters, and then continue
            printing until the end of the string or the first space. */
         for (j = 0; *sGram && (j < 60 || !FNX_ISSPACE(*sGram)); j++)
            FNX_FPRINTF(fp, "%c", *sGram++);
         FNX_FPRINTF(fp, "\n");
         while (FNX_ISSPACE(*sGram))
            sGram++;
         if (*sGram) /* Not yet the end of the string */
            FNX_FPRINTF(fp, "         "); /* Indent next line. */
      }
   }
   if (fp != FNX_STDOUT)
      FNX_FCLOSE(fp);

   FreeLinkPool(pLinkPool);

   return 0; /* ok */
}  /* WriteVocab */
#endif

#ifndef FNX_LEAN_AND_MEAN
/*******************************************************************************
 * Code below is for stand-alone command-line .vocab-file shortener
 *******************************************************************************/
/*******************************************/
/* Recursively generate pronunciations for a word, and add them to a linked list */
void RecursePronun(wordTPtr pWord, SDWORD iNode, char *sPrefix, llistPtr *ppPronunList)
{
   char sBuf[200]; /* Current pronunciation being built */
   wstateTPtr pNode, pNext;
   SDWORD i;

   pNode = &(pWord->nodes[iNode]);
   /* Add the current node's category name to the string */
#ifndef NO_PRINTF
   FNX_SPRINTF(sBuf, "%s%s%s", sPrefix, sPrefix[0]?" ":"", pNode->phoneme);
#endif //NO_PRINTF
   /* Add the pronunciation to the list if this is a final node */
   if (pNode->type == PH_FINAL || pNode->type == PH_INITFINAL)
      InsertLink(FNX_STRDUP(sBuf), ppPronunList, NULL);

   /* Recurse on all following nodes (except for exit nodes) */
   for (i=0; i<pNode->numnext; i++)
   {
      pNext = &(pWord->nodes[pNode->next[i]]);
      if (pNext->type != PH_EXIT)
         RecursePronun(pWord, pNode->next[i], sBuf, ppPronunList);
   }
}  /* RecursePronun */

/* Return a sorted, newly-allocated array of newly-allocated strings containing all
   of the pronunciations possible for pWord. */
char **GetPronunciationList(wordTPtr pWord, SDWORDPTR piNumPronunciations)
{
   SDWORD    iInit, iNumPronun;
   llistPtr  pPronunList=NULL;
   char    **psPronun;

   for (iInit = 0; iInit < pWord->numinit; iInit++)
      RecursePronun(pWord, pWord->initnodes[iInit], "", &pPronunList);
   iNumPronun = ListSize(pPronunList);
   psPronun   = ListToArray(&pPronunList, iNumPronun, NULL);
   qsort(psPronun, iNumPronun, sizeof(char *), CaseCmpString);
   *piNumPronunciations = iNumPronun;
   return psPronun;
}

#ifdef SHORTEN_PROJECT
static void RemoveDuplicates(char **psPronunList, SDWORD *piNumPronun, char *sKind, char *sPronString, char *sWord)
{
   SDWORD iOldIndex, iNewIndex;
   
   for (iOldIndex=iNewIndex=0; iOldIndex<*piNumPronun; iNewIndex++)
   {
      /* Slide an old pointer down into its new place (unless they are still the same index) */
      if (iNewIndex<iOldIndex)
         psPronunList[iNewIndex]=psPronunList[iOldIndex];
      iOldIndex++; /* Skip past the pointer already used by iNewIndex */
      /* Skip all pointers that point to the same string */
      while (iOldIndex < *piNumPronun && SameString(psPronunList[iNewIndex], psPronunList[iOldIndex]))
      {
         FNX_PRINTF("Duplicate pronu. (%s) in %s list of word '%s'. %s\n",psPronunList[iNewIndex],sKind,sWord,
            sPronString?sPronString:"");
         FNX_FREE(psPronunList[iOldIndex]);
         iOldIndex++;
      }
   }  /* for iOld/NewIndex */
   
   /* Return the number of words in the new array of strings. */
   *piNumPronun = iNewIndex;
}
int main(int argc, char *argv[])
{
   VocabTPtr pVocab;
   wordTPtr pNewWord;
   char *sPronunciation, **psOldPronunciations, **psNewPronunciations, *sOld, *sNew;
   SDWORD iNumOldPronunciations, iNumNewPronunciations;
   LinkPoolPtr pLinkPool;
   SDWORD iWord, i;
   FILE *fp;

   /* Parse arguments, and read input vocab file */
   if (argc<2)
   {
      Message(stderr,"Usage: %s <OldVocabFile> <CompressedVocabFile>\n", argv[0]);
      Message(stderr,"  Utility to compress the pronunciation strings of words\n");
      exit(-1);
   }

   Message(stdout,"Reading vocab file...\n");
   pVocab = ReadVocab(argv[1], NULL);
   if (!pVocab)
   {
      Message(stderr,"Couldn't read vocab file '%s'\n", argv[1]);
      Message(stderr,"Usage: %s <OldVocabFile> <CompressedVocabFile>\n", argv[0]);
      exit(-1);
   }

   if (argc>=3)
      fp = FNX_FOPEN(argv[2],"wt");
   else fp = NULL;

   FNX_PRINTF("\nGenerating pronunciations...\n");
   pLinkPool = NewLinkPool(100);
   for (iWord=0; iWord<pVocab->iNumWords; iWord++)
   {
      FNX_PRINTF("%s                 \r", pVocab->ppWords[iWord]->name);
      sPronunciation = GetPronunciation(pVocab->ppWords[iWord], NULL, pLinkPool);
      if (fp)
      {
#ifdef DUMP_PROBLEMS
         if (gbOuch)///
#endif
         {///
            FNX_FPRINTF(fp,"%s%s;\n",pVocab->ppWords[iWord]->name, sPronunciation);
            FNX_PRINTF("%s                 \r", pVocab->ppWords[iWord]->name);
         }///
      }
      else
      {
         BOOL bDifferent;

         psOldPronunciations = GetPronunciationList(pVocab->ppWords[iWord], &iNumOldPronunciations);
         pNewWord = buildWord(sPronunciation, pVocab->ppWords[iWord]->name, NULL);
         psNewPronunciations = GetPronunciationList(pNewWord, &iNumNewPronunciations);
#if 1 // print only differing pronunciations
         RemoveDuplicates(psOldPronunciations,&iNumOldPronunciations,"Old",NULL,pVocab->ppWords[iWord]->name);
         RemoveDuplicates(psNewPronunciations,&iNumNewPronunciations,"New",sPronunciation,pVocab->ppWords[iWord]->name);
         if (iNumOldPronunciations!=iNumNewPronunciations)
            bDifferent=TRUE;
         else
         {
            bDifferent=FALSE;
            for (i=0; bDifferent && i<iNumOldPronunciations; i++)
            {
               if (FNX_STRCMP(psOldPronunciations[i],psNewPronunciations[i])!=0)
                  bDifferent=TRUE;
            }
         }
         if (bDifferent)
#endif
         {
            SDWORD iNew, iOld;
            FNX_PRINTF("%s   %s;\n", pVocab->ppWords[iWord]->name, sPronunciation);
            for (iNew=iOld=0; iOld<iNumOldPronunciations || iNew<iNumNewPronunciations; i++)
            {
               if (i<iNumOldPronunciations)
                  sOld = psOldPronunciations[i];
               else sOld = "";
               if (i<iNumNewPronunciations)
                  sNew = psNewPronunciations[i];
               else sNew = "";
               if (FNX_STRCMP(sOld,sNew)==0)
               {
                  FNX_PRINTF("  %-10s %-20s\n  %-10s %-20s\n\n", "", sOld, "", sNew);
               }
               else 
               {
                  FNX_PRINTF("  %-10s %-20s\n  %-10s %-20s\n\n", "Mismatch:", sOld, "", sNew);
               }
            }
         }
         else FNX_PRINTF("%s                 \r", pVocab->ppWords[iWord]->name);

         FNX_FREE(sPronunciation);
         FreePointerArray(psOldPronunciations, iNumOldPronunciations);
         FreePointerArray(psNewPronunciations, iNumNewPronunciations);
         freeWord(pNewWord);
      }
   }
   if (fp)
      FNX_FCLOSE(fp);
   FNX_PRINTF("\n");
   FreeLinkPool(pLinkPool);

   if (argc>=4)
   {
      FILE *fp1, *fp2, *fp3;
      SDWORD iShortest1=0, iShortest2=0, iSame=0;
      char sBuf1[10000], sBuf2[10000];
      fp1 = FNX_FOPEN(argv[1],"rt");
      fp2 = FNX_FOPEN(argv[2],"rt");
      fp3 = FNX_FOPEN(argv[3],"wt");
      while (FNX_FGETS(sBuf1,10000,fp1) && fgets(sBuf2,10000,fp2))
      {
         if (FNX_STRLEN(sBuf1)<FNX_STRLEN(sBuf2))
         {
            FNX_FPRINTF(fp3,"%s",sBuf1);
            iShortest1++;
         }
         else 
         {
            FNX_FPRINTF(fp3,"%s",sBuf2);
            if (FNX_STRLEN(sBuf2)<FNX_STRLEN(sBuf1))
               iShortest2++;
            else iSame++;
         }
      }
      FNX_FCLOSE(fp3);
      FNX_FCLOSE(fp2);
      FNX_FCLOSE(fp1);
      FNX_PRINTF("%d utterances.  %d shortest in %s; %d shortest in %s; %d same.\n", iShortest1+iShortest2,
         iShortest1, argv[1], iShortest2, argv[2], iSame);
   }
   return 0;
}
#endif //SHORTEN_PROJECT
#endif   // #ifndef FNX_LEAN_AND_MEAN
