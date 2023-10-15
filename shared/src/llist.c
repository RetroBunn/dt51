/*C_HEADER_FILE****************************************************************
FILE        :  llist.c
DESC        :  linked list functions
TABS        :  3
OWNER       :  Fonix
DATE CREATED:  11 October 1999

(C) Copyright 1999,2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/22/05 9:30a $
  $Revision: 6 $

*END_HEADER*******************************************************************/

#include "FnxPlatform.h"
#include "DTFnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxLlist.h"

/*FUNCTION_HEADER*******************
 * NAME:    ;NewStringLink
 * DESC:    Allocate a new linked list node pointing to a new string.
 * IN:      s - String to copy into link
 *          pNext - "next" pointer for the new link.
 * OUT:     A linked list node is allocated, along with a copy of s.
 * RETURN:  Pointer to the newly-allocated link.
 * NOTES:   Calling routine should call FreeLink() on the link eventually.
 *END_HEADER***************************/
llistPtr NewStringLink(char *s, llistPtr pNext)
{
   return NewLink(FNX_STRDUP(s), pNext);
}  /* NewStringLink */

/*FUNCTION_HEADER*******************
 * NAME:    ;FreeStringLink
 * DESC:    Free a linked list node and its string.
 * IN:      pLink - Link to free
 * OUT:     pLink is free'd along with its pointer ("p") [which could be a string].
 * RETURN:  Pointer to the "pNext" field of pLink (before it was freed).
 * NOTES:   The pNext field is returned to make it convenient to "pop"
            the top element off of a stack, e.g., pTop = FreeStringLink(pTop);
 *END_HEADER***************************/
llistPtr FreeStringLink(llistPtr pLink)
{
   llistPtr pNext;

   if (pLink)
   {
      pNext = pLink->pNext;
      if (pLink->p)
         FNX_FREE(pLink->p);
      FNX_FREE(pLink);
   }
   else pNext = NULL;

   return pNext;
}  /* FreeStringLink */

/*FUNCTION_HEADER**********************
 * NAME:    ;FindLink
 * DESC:    search pLList for member sName
 * IN:      pList - List to search for sName
            sName - String to compare with each link's string.
            bCaseSensitive - Flag for whether to do case-sensitive strcmp (instead of stricmp).
 * OUT:     n/a
 * RETURN:  pointer to the link that has sName, otherwise NULL if no link
            has sName
 * NOTES:   
 *END_HEADER***************************/
llistPtr FindLink(llistPtr pList, char *sName, BOOL bCaseSensitive)
{
   LLIST *pLink;

   for(pLink = pList; pLink; pLink = pLink->pNext)
   {
      if(bCaseSensitive)
      {
         if(FNX_STRCMP(pLink->p, sName) == 0)
            return pLink;
      }
      else
      {
         if(FNX_STRICMP(pLink->p, sName) == 0)
            return pLink;
      }
   }
   return NULL;
}

/*FUNCTION_HEADER*******************
 * NAME:    ;NewLink
 * DESC:    Allocate a new linked list node pointing to an existing pointer.
 * IN:      p       - Pointer to assign to link.
 *          pNext   - "next" pointer for the new link.
 * OUT:     A linked list node is allocated.
 * RETURN:  Pointer to the newly-allocated link.
 * NOTES:   Calling routine should call FreeLink() on the link eventually.
            To push things onto a stack, use "pTop = NewLink(pNewPtr, pTop);"
            If you're allocating very many links, you should consider using:
              pLinkPool=NewLinkPool(1000);
              pList=NULL;
              InsertLink(pPointer, &pList, pLinkPool);
              ...
              RemoveLink(&pList, pLinkPool);
              ...
              FreeLinkPool(pLinkPool);
 *END_HEADER***************************/
llistPtr NewLink(void *p, llistPtr pNext)
{
   llistPtr pLink;
   
   pLink = (llistPtr ) FNX_MALLOC(sizeof(LLIST));
   FNX_ASSERT(pLink);
   pLink->p = p;
   pLink->pNext = pNext;
   return pLink;
}  /* NewLink */

/*FUNCTION_HEADER*******************
 * NAME:    ;FreeLink
 * DESC:    Free a linked list node.
 * IN:      pLink - Link to free
 * OUT:     pLink is free'd.
 * RETURN:  Pointer to the "pNext" field of pLink (before it was freed).
 * NOTES:   The pNext field is returned to make it convenient to "pop"
            the top element off of a stack, e.g., pTop = FreeLink(pTop);
 *END_HEADER***************************/
llistPtr FreeLink(llistPtr pLink)
{
   llistPtr pNext;

   if (pLink)
   {
      pNext = pLink->pNext;
      FNX_FREE(pLink);
   }
   else pNext = NULL;

   return pNext;
}  /* FreeLink */

/*FUNCTION_HEADER*******************
 * NAME:    ;FreeList
 * DESC:    Free a linked list.
 * IN:      ppLink - Address of head of list to free
            pLinkPool  - Pool of links to return links to (NULL=>Deallocate() individually)
 * OUT:     The entire list is free'd, and *ppLink is set to NULL.
 * RETURN:  n/a
 * NOTES:   The links are all freed, but the things they point to are NOT freed.
            If pLinkPool is NULL then the links are individually freed using Deallocate().
            Otherwise, the links are returned to the free list of pLinkPool.
 *END_HEADER***************************/
void FreeList(llistPtr *ppLink, LinkPoolPtr pLinkPool)
{
   llistPtr pNext;

   if (pLinkPool)
   {
      while (*ppLink)
      {
         /* Remove the first link in the list and return it to pLinkPool's free list. */
         /* (*ppLink is advanced to the next link in the list) */
         RemoveLink(ppLink, pLinkPool);
      }
   }
   else /* No pool of links, so deallocate each one. */
   {
      while(*ppLink)
      {
         pNext = (*ppLink)->pNext;
         FNX_FREE(*ppLink);
         *ppLink=pNext;
      }
   }
}  /* FreeList */

/*FUNCTION_HEADER**********************
   NAME:    ;ListSize
   DESC:    Tell how many elements are in a linked list.
   IN:      pList - Head of a linked list.
   OUT:     n/a
   RETURN:  Number of elements in pList.
   NOTES:   
 *END_HEADER***************************/
SDWORD ListSize(llistPtr pList)
{
   SDWORD lListSize=0;
   while (pList)
   {
      lListSize++;
      pList = pList->pNext;
   }

   return lListSize;
}  /* ListSize */

/*FUNCTION_HEADER**********************
   NAME:    ;CombineStringList
   DESC:    Convert a linked list of strings into a single string.
   IN:      ppList    - Address of the head of a linked list.
            iNumLinks - Number of links in the linked list.
            pLinkPool     - Pool of links to return the freed links to (NULL=>use Deallocate() on each).
   OUT:     The linked list pointed to by *ppList is free'd, and all of
              the strings pointed to are also freed.  A big string is
            allocated with all of the strings in it (with a space between each).
   RETURN:  Pointer to the newly-allocated string.
   NOTES:   *ppList is assumed to be in reverse order, so the first element
              in pList becomes the last part of the returned string.
 *END_HEADER***************************/
char *CombineStringList(llistPtr *ppList, LinkPoolPtr pLinkPool)
{
   char     *sString, *pcDest, *pcSource;
   SDWORD   iLength=0;
   llistPtr pList;
   
   /* Make sure we have a list to work on */
   if (!ppList || !*ppList )
      return NULL;
   
   /*  Reverse the list so it comes out in the same order as it went in */
   ReverseList(ppList);
   
   for(pList = *ppList; pList; pList = pList->pNext)
   {
      if (pList->p)
         iLength += FNX_STRLEN((char *)pList->p ) + 1;
   }
   
   /* Allocate an array of pointers to hold the pointers in the linked list */
   if( (sString = (char *) FNX_CALLOC(iLength+1, sizeof(char))) == NULL)
   {
      return NULL;
   }
   
   pcDest = sString;
   while (*ppList)
   {
      pList = *ppList;
      pcSource = (char *)pList->p;
      if (pcSource)
      {
         /* Copy the current string and a ' ' onto the end of the real string,
            and advance pcSource to where the next string needs to continue. */
         while (*pcSource)
            *(pcDest++) = *(pcSource++);

         /* Only add a ' ' if there is still another string */
         if (pList->pNext)
            *(pcDest++) = ' ';
         
         /* Free up the string from the list itself */
         FNX_FREE(pList->p);
      }
      /* Remove the top element from *ppList */
      RemoveLink(ppList, pLinkPool);
   }  /* while */
   
   return sString;
   
}  /* CombineStringList */


/*FUNCTION_HEADER**********************
   NAME:    ;ListToArray
   DESC:    Convert a linked list of pointers into an array of pointers.
   IN:      ppList    - Address of the head of a linked list.
            iNumLinks - Number of links in the linked list.
            pLinkPool     - Pool of links to return the freed links to (NULL=>use Deallocate() on each).
   OUT:     The linked list pointed to by *ppList is free'd, and an array of 
              pointers is allocated.  *ppList=NULL if iNumLinks was correct.
   RETURN:  Pointer to the array of pointers.
   NOTES:   *ppList is assumed to be in reverse order, so the first element
              in pList becomes the last element in the returned array.
            The return type is char **, but you can typecast it to whatever **.
 *END_HEADER***************************/
char **ListToArray(llistPtr *ppList, SDWORD iNumLinks, LinkPoolPtr pLinkPool)
{
   SDWORD lIndex;
   char **ppArray;

   /* Make sure we have a list to work on */
   if (!ppList || !*ppList || iNumLinks <= 0)
      return NULL;

   /* Allocate an array of pointers to hold the pointers in the linked list */
   if( (ppArray = (char **) FNX_CALLOC(iNumLinks, sizeof(void *))) == NULL)
   {
      return NULL;
   }
   /* Copy the pointers from the links into the array, and deallocate
      each link.  Visit the list in reverse order, since elements were
      inserted such that the last element is first in the list. */
   for (lIndex=iNumLinks-1; lIndex >= 0 && *ppList; lIndex--)
   {
      ppArray[lIndex] = (*ppList)->p;
      RemoveLink(ppList, pLinkPool);
   }  /* for lIndex */

   /* Make sure the number of elements in the list matched iNumLinks */
   if (lIndex != -1)
   {
      Message(FNX_STDERR, "Warning in ListToArrays: Built an array of %ld elements\n", iNumLinks);
      Message(FNX_STDERR, "   but only %ld were in the list.\n", iNumLinks - lIndex);
   }

   if (*ppList)
   {
      Message(FNX_STDERR, "Warning in ListToArrays: Built an array of %ld elements\n", iNumLinks);
      Message(FNX_STDERR, "   but there were more than that in the list.\n");
   }

   /* Return the array of pointers */
   return ppArray;
}  /* ListToArray */

/*FUNCTION_HEADER**********************
   NAME:    ;FreePointerArray
   DESC:    Free an array of pointers and its elements.
   IN:      ppPtrArray - An array of pointers to something (e.g., array of string pointers).
   OUT:     ppPtrArray[0..iNumElements-1] and ppPtrArray are free'd.
   RETURN:  n/a
   NOTES:   
 *END_HEADER***************************/
void FreePointerArray(char **ppPtrArray, SDWORD iNumElements)
{
   SDWORD iIndex;
   if (ppPtrArray)
   {
      for (iIndex=0; iIndex<iNumElements; iIndex++)
      {
         if(ppPtrArray[iIndex])
            FNX_FREE(ppPtrArray[iIndex]);
      }
      FNX_FREE(ppPtrArray);
   }  /* if */
}  /* FreePointerArray */

/*FUNCTION_HEADER**********************
   NAME:    ;NewLinkPool
   DESC:    Create a new pool of links for efficient allocation & freeing of linked list links.
   IN:      iBlockSize - Number of links that should be allocated at a time in blocks. (0=>use default of 1000)
   OUT:     A link pool is allocated and the first 'iBlockSize' links are allocated within it.
            The "pFree" list is set to include all of the newly-allocated links.
   RETURN:  Pointer to the newly-allocated pool.
   NOTES:   Malloc is slow and usually uses lots of bytes of overhead for
              each allocation.  A linked list structure is only 8 bytes 
              (i.e., two pointers), so if lots of links are going to be
              allocated--and especially if they are going to be allocated
              and freed repeatedly--then using a pool of links is more efficient.
            The pool initially is allocated with 'iBlockSize' links, and
              all of the links are added to a "free" list.  When a new link
              is needed, it is taken off of the free list.  When one is freed,
              it is added back to the free list.  If the free list runs out,
              another block of 'iBlockSize' nodes are allocated.
            The routine "FreeLinkPool" releases all of the storage.  There is
              currently no method for doing garbage collection, since moving
              the links would break all of the pointers to them, so the pool
              grows as needed without ever shrinking until you free up the whole pool.
            If you are building some links that will be temporary and some that
              will be permanent, you may want to use separate pools so that
              the temporary one can be freed up early, and the permanent
              one can be kept around until the end.
 *END_HEADER***************************/
LinkPoolPtr NewLinkPool(SDWORD iBlockSize)
{
   return (LinkPoolPtr)NewPool(iBlockSize, sizeof(LLIST));
}  /* NewLinkPool */

/*FUNCTION_HEADER**********************
   NAME:    ;FreeLinkPool
   DESC:    Free up a pool of linked list links.
   IN:      pLinkPool - Pool of linked list to be freed.
   OUT:     pLinkPool and all of its links are freed.
   RETURN:  n/a
   NOTES:   Make sure none of the links in this pool are still
              being used! (i.e., don't leave any dangling pointers
              in the pool; or in other words, "don't p in the Pool!")
 *END_HEADER***************************/
void FreeLinkPool(LinkPoolPtr pLinkPool)
{
   FreePool((PoolPtr)pLinkPool);
}  /* FreeLinkPool */

/*FUNCTION_HEADER**********************
   NAME:    ;InsertLink
   DESC:    Insert a link into the beginning of a linked list.
   IN:      p - Pointer to insert into the list.
            ppList - Address of the head of the list to be modified.
            pLinkPool  - Pool of links to use to get the new link (NULL=>use Allocate())
   OUT:     *ppList points at a new link which points to p and the old *ppList.
            pLinkPool is modified (if non-null).
   RETURN:  n/a
   NOTES:   If pLinkPool is NULL, this routine simply uses NewLink(), but in such
              cases, you had better be sure to use FreeLink() with a NULL pool, too.
            Similarly, you MUST call FreeLink() with the same pool you used for
              InsertLink(), or you could be hosed.  The exception is that you can
              call FreeLinkPool() to free all of the links in a pool at once
              without calling FreeLinkPool() for each link.
 *END_HEADER***************************/
void InsertLink(void *p, llistPtr *ppList, LinkPoolPtr pLinkPool)
{
   llistPtr pLink;

   if (pLinkPool)
   {
      /* Get a link from the free list in the pool (expanding the free list if necessary) */
      pLink = (llistPtr) GetFromPool((PoolPtr)pLinkPool);
      pLink->pNext     = *ppList;      /* Point the new link to the old list */
      pLink->p         = p;            /* Remember the actual pointer being added to the list */
      *ppList          = pLink;        /* Adjust the head of the list to point at the new link */
   }
   else /* No pool of links, so just use Allocate() for the link. */
      *ppList = NewLink(p, *ppList);
}  /* InsertLink */

/*FUNCTION_HEADER**********************
   NAME:    ;AppendLink
   DESC:    Append a link onto the end of a linked list.
   IN:      p - Pointer to append to the end of the list.
            ppList - Address of the head of the list to be modified.
            pLinkPool  - Pool of links to use to get the new link (NULL=>use Allocate())
   OUT:     *ppList points at the original head of the list, if any, or at p, if it is the only link.
            The list has p at the end of it.
            pLinkPool is modified (if non-null).
   RETURN:  n/a
   NOTES:   See InsertLink()'s notes in regards to the use of pLinkPool.
            Slower than InsertLink(), because this routine traverses the list first.
 *END_HEADER***************************/
void AppendLink(void *p, llistPtr *ppList, LinkPoolPtr pLinkPool)
{
   llistPtr pLink;

   for (pLink = *ppList; pLink; pLink=pLink->pNext)
      ppList = &pLink->pNext; /* Advance ppList to be the address of the pointer that needs
                                 to point to the next link (whether the head of the list or
                                 the 'pNext' field of the last link) */

   if (pLinkPool)
   {
      /* Get a link from the free list in the pool (expanding the free list if necessary) */
      pLink = (llistPtr) GetFromPool((PoolPtr)pLinkPool);
      pLink->pNext     = NULL;
      pLink->p         = p;            /* Remember the actual pointer being added to the list */
      *ppList          = pLink;        /* Point at the new link from the last node OR the head of the list */
   }
   else /* No pool of links, so just use Allocate() for the link. */
      *ppList = NewLink(p, NULL);
}  /* AppendLink */

/*FUNCTION_HEADER**********************
   NAME:    ;RemoveLink
   DESC:    Remove a link from the beginning of a list (and return it to a link pool, if any) 
   IN:      ppList - Address of the head of the list to be modified.
            pLinkPool  - Pool of links to return the link to (NULL=>Deallocate() it).
   OUT:     *ppList points at the next element in the list, i.e., the first element is removed.
            pLinkPool has the first element of *ppList added to its "pFreeList".
   RETURN:  n/a
   NOTES:   If pLinkPool is NULL, this routine uses Deallocate() to free the link.
              If the link was allocated from a pool, this will cause a crash,
              so make sure you're consistent: Use a pool for InsertLink() AND RemoveLink(),
              or use NULL for both.
            To free a single link that has already been removed from a list,
              simply do "RemoveLink(&pLink, pLinkPool)" and then ignore the new value of pLink.
 *END_HEADER***************************/
void RemoveLink(llistPtr *ppList, LinkPoolPtr pLinkPool)
{
   llistPtr pLink;
   
   /* Make sure we don't crash */
   if (!ppList)
      return;
   /* Get a pointer to the link being "freed" (recycled) */
   pLink = *ppList;
   /* Move the head of the list beyond the link being freed */
   *ppList = pLink->pNext;
   if (pLinkPool)
      ReturnToPool(pLink, (PoolPtr)pLinkPool);
   else FNX_FREE(pLink);
}  /* RemoveLink */

/*FUNCTION_HEADER*******************
 * NAME:    ;ReplaceLink
 * DESC:    Replace a pointer in a linked list with another pointer.
 * IN:      pList       - List to be searched.
            pOldPointer - Pointer to find in the list.
            pNewPointer - Pointer to replace the old one with.
 * OUT:     If one of the elements in the linked list points to pOldPointer,
               the pointer is replaced with pNewPointer.
 * RETURN:  0 on success, -1 if not found.
 * NOTES:   
 *END_HEADER***************************/
SDWORD ReplaceLink(llistPtr pList, void *pOldPointer, void *pNewPointer)
{
   llistPtr pLink;

   for (pLink=pList; pLink; pLink = pLink->pNext)
   {
      if (pLink->p == pOldPointer)
      {
         /* Found the pointer in the list, so replace it and return */
         pLink->p = pNewPointer;
         return 0;
      }
   }
   return -1; /* Didn't find it */
}  /* ReplaceLink */

/*FUNCTION_HEADER*******************
 * NAME:    ;RemovePointerFromList
 * DESC:    Remove a pointer in a linked list.
 * IN:      pOldPointer - Pointer to find in the list.
            ppList      - Address of list to be searched.
            pLinkPool       - Pool of links to return the deleted link to (NULL=>Deallocate())
 * OUT:     If one of the elements in the linked list points to pOldPointer,
               the pointer is removed, and the removed link is free'd.
               The head of the list will be changed if the link to removed
               is the first one in the list.
 * RETURN:  0 on success, -1 if not found.
 * NOTES:   
 *END_HEADER***************************/
SDWORD RemovePointerFromList(void *pOldPointer, llistPtr *ppList, LinkPoolPtr pLinkPool)
{
   llistPtr pLink;
   llistPtr pLast = NULL; /* Pointer to previous link */

   for (pLink=*ppList; pLink; pLink = pLink->pNext)
   {
      if (pLink->p == pOldPointer)
      {
         if (pLast)
            pLast->pNext = pLink->pNext;
         else (*ppList) = pLink->pNext;
         RemoveLink(&pLink, pLinkPool);
         return 0; /* => "ok" => found it */
      }
      pLast = pLink;
   }
   return -1; /* Didn't find it */
}  /* RemovePointerFromList */

/*FUNCTION_HEADER*******************
 * NAME:    ;LinkExists
 * DESC:    Decide if a pointer exists in a linked list.
 * IN:      pOldPointer - Pointer to find in the list.
            pList       - List to be searched.
 * OUT:     n/a
 * RETURN:  TRUE if pOldPointer is in pList.  False otherewise.
 * NOTES:   
 *END_HEADER***************************/
BOOL LinkExists(void *pOldPointer, llistPtr pList)
{
   llistPtr pLink;

   for (pLink=pList; pLink; pLink = pLink->pNext)
   {
      if (pLink->p == pOldPointer)
         return TRUE;
   }
   return FALSE; /* Didn't find it */
}  /* LinkExists */

/*FUNCTION_HEADER*******************
 * NAME:    ;ReverseList
 * DESC:    Reverse the order of nodes in a linked list.
 * IN:      ppList - Address of the beginning of the linked list to be reversed.
 * OUT:     *ppList points to the new head of the list (which used to be the end of it),
              and all of the nodes are in the list in reverse order.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
void ReverseList(llistPtr *ppList)
{
   llistPtr pLink, pLast, pNext;
   pLast=NULL;
   for (pLink = *ppList; pLink; pLink = pNext)
   {
      /* Remember the next pointer before replacing it */
      pNext = pLink->pNext;
      /* Point the current link at the previous one */
      pLink->pNext = pLast;
      /* Advance pLast to remember what the previous link was */
      pLast = pLink;
   }
   /* Set the head of the list to be the last element in the original list */
   *ppList = pLast;
}  /* ReverseList */
