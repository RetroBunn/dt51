/*C_HEADER_FILE****************************************************************
FILE        :  pool.c
DESC        :  Functions to handle pools of structures
TABS        :  3
OWNER       :  Randy Wilson
DATE CREATED:  31 October 2000 (oooOOOOoooo!)

(C) Copyright 2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/27/03 3:11p $
  $Revision: 12 $

*END_HEADER*******************************************************************/

#include "FnxPlatform.h"
#include "FnxAllocate.h"
#include "FnxLlist.h"

//////
#if 1 // get rid of CheckFreeList()...
#define CheckFreeList(x)
#else // else debug...
CheckFreeList(PoolPtr pPool)
{
   int iOffset, iIndex, *p;
   voidPtr pBlockLink, pNext, *ppPointer;

   if (pPool)
   {
      for (p = (int *)pPool->pFreeList; p; p = (int *)*p)
      {
         /* Free up the blocks of structures */
         for (pBlock=pPool->pBlockList; pBlock; pBlock = pBlock->pNext)
         {
            iOffset = ((int)p - (int)pBlockLink - 4);
            iIndex = iOffset / pPool->iStructSize;
            if (iIndex>=0 && iIndex<pPool->iBlockSize)
            {
               FNX_ASSERT(iOffset % pPool->iStructSize == 0);
               break; /* Found a block where i is in the right range */
            }
         }  /* for pBlockLink */
         if (pBlock==NULL)
            iOffset=iOffset; /* Couldn't find a block that contains the element p on the free list */
      }  /* for p */
   }  /* if pool */
}
#endif

/*FUNCTION_HEADER**********************
   NAME:    ;NewPoolBlock
   DESC:    Allocate and initialize a block of structures to be used in a pool of structures.
   IN:      pPool - Pool to add a new block to.
   OUT:     pPool->pBlockList has a new block inserted into it.
            pPool->iBlockSize structures of size 'iStructSize' are allocated 
            in a new block, along with room at the beginning for a pointer to the next block.
            The new block's "pNext" field points to the old head of the block list.
            The new structures are all added to the pool's free list.
   RETURN:  n/a
   NOTES:   A block has one pointer followed by 'iBlockSize' structures of size
              'iStructSize' bytes each, and all of these structures are hooked
              into the linked list of free things by using the first four
              bytes (or however big a pointer is) of each structure as a "next" pointer.
            Because of this, EACH STRUCTURE MUST BE AT LEAST AS BIG AS A POINTER.
            These blocks should be freed by FreePool().
 *END_HEADER***************************/
void NewPoolBlock(PoolPtr pPool)
{

   BlockListPtr pNewBlock; /* New block of structures */
   UBYTE *pCurrentStruct;  /* Current structure within a block.  Use a pointer to single-byte values
                                so we can increment it by the size of the structures. */
   voidPtr *ppPointer; /* Double pointer: doesn't really matter what kind of double pointer.  If
                          dereferencing a void** into a void* causes problems on any architectures,
                          then we can use a "UBYTE **" or something else. */
   SDWORD iStructIndex;

   /* Allocate a block of 'iBlockSize' structures of size 'iStructSize',
      along with a pointer at the beginning. */
   pNewBlock = (BlockListPtr) FNX_MALLOC(sizeof(voidPtr) + pPool->iBlockSize * pPool->iStructSize);

   /* Insert the new block at the beginning of the block list */
   pNewBlock->pNext = pPool->pBlockList;
   pPool->pBlockList = pNewBlock;

   /* Point 'pCurrentSturct' at the first structure in the block */
   pCurrentStruct = (UBYTE *)&(pNewBlock->sData);

   /* Create a linked list of structures by using the first few bytes
      of each structure to point to the next one in the list. */
   for (iStructIndex=0; iStructIndex<pPool->iBlockSize-1; iStructIndex++)
   {
      /* Set 'ppPointer' to the address of the beginning of the current structure. */
      ppPointer = (voidPtr*)pCurrentStruct;
      /* Advance pCurrentStruct to point at the beginning of the next struct */
      pCurrentStruct += pPool->iStructSize;
      /* Set the pointer that occupies the first few bytes of the current structure
         to point at the next structure. */
      *ppPointer = pCurrentStruct;
   }
   /* Point the last free struct at the head of the old free list (which will often be NULL). */
   ppPointer = (voidPtr *) pCurrentStruct; /* Set ppPointer to the address of the beginning of pCurrentStruct */
   *ppPointer = pPool->pFreeList;   /* Change the pointer at the beginning of pCurrentStruct to point 
                                  to the original free list*/
   /* Point the free list at the head of this new block of free nodes 
      (skip the pointer at the beginning of the allocated block). */
   pPool->pFreeList = (voidPtr)&(pNewBlock->sData);
}  /* NewPoolBlock */

/*FUNCTION_HEADER**********************
   NAME:    ;NewPool
   DESC:    Create a new pool of structures for efficient allocation & freeing of them.
   IN:      iBlockSize - Number of structures that should be allocated at a time in blocks. (0=>use default of 1000)
            iStructSize- Size of each structure (in bytes), i.e., sizeof(structure).
   OUT:     A pool structure is allocated and the first 'iBlockSize' structures are allocated within it.
            The "pFree" list is set to include all of the newly-allocated links.
   RETURN:  Pointer to the newly-allocated pool.
   NOTES:   Malloc is slow and usually uses lots of bytes of overhead for
              each allocation.  If lots of structures are going to be
              allocated--and especially if they are going to be allocated
              and freed repeatedly--then using a pool of structures is more efficient.
            The pool initially is allocated with 'iBlockSize' structures, and
              all of the structures are added to a "free" list.  When a new structures
              is needed, it is taken off of the free list.  When one is freed,
              it is added back to the free list.  If the free list runs out,
              another block of 'iBlockSize' structures is allocated.
            The routine "FreePool" releases all of the storage.  There is
              currently no method for doing garbage collection, since moving
              the structures would break all of the pointers to them, so the pool
              grows as needed without ever shrinking until you free up the whole pool.
            If you are building some links that will be temporary and some that
              will be permanent, you should use separate pools so that
              the temporary one can be freed up early, and the permanent
              one can be kept around until the end.
 *END_HEADER***************************/
PoolPtr NewPool(SDWORD iBlockSize, SDWORD iStructSize)
{
   PoolPtr pPool;

   /* If iBlockSize<=0, then use default size of 1000. */
   if (iBlockSize<1)
      iBlockSize = 1000;

   /* Allocate a pool structure */
   pPool = (PoolPtr) FNX_CALLOC(1, sizeof(Pool));
   pPool->iBlockSize = iBlockSize;
   if (iStructSize<4)
      iStructSize=4;
   if (iStructSize%4 != 0)
      iStructSize += 4 - (iStructSize%4);
   pPool->iStructSize = iStructSize;

   /* Set pointers to NULL so they will be used properly in NewLinkBlock */
   pPool->pFreeList  = NULL;
   pPool->pBlockList = NULL;

   /* Allocate the first block of links, and add them all to the free list */
   NewPoolBlock(pPool);

   /* Return the pool */
   return pPool;
}  /* NewPool */

/*FUNCTION_HEADER**********************
   NAME:    ;FreePool
   DESC:    Free up a pool of structures (i.e., drains the pool).
   IN:      pPool - Pool of structures to be freed.
   OUT:     pPool and all of its (blocks of) structures are freed.
   RETURN:  n/a
   NOTES:   Make sure none of the structures in this pool are still
              being used! (i.e., don't leave any dangling pointers
              in the pool; or in other words, "Don't p in the Pool!")
 *END_HEADER***************************/
void FreePool(PoolPtr pPool)
{
   voidPtr pBlockLink, pNext, *ppPointer;
   if (pPool)
   {
      /* Free up the blocks of structures */
      for (pBlockLink=pPool->pBlockList; pBlockLink; pBlockLink = pNext)
      {
         /* Remember the address of the next link, since we are about
            to deallocate the block of links that includes the current link. */
         ppPointer = (voidPtr *) pBlockLink; /* Get the address of where the 'next' pointer is, 
                                                i.e., the beginning of the free block. */
         pNext = *ppPointer;                 /* Copy the next pointer out of that address */
         /* Free up the current block. */
         FNX_FREE(pBlockLink);
      }  /* for pBlockLink */

      /* Free the actual pool structure */
      FNX_FREE(pPool);
   }  /* if pPool */
}  /* FreePool */

/*FUNCTION_HEADER**********************
   NAME:    ;GetFromPool
   DESC:    Get a pointer to a free structure from a pool a structures.
   IN:      pPool  - Pool of links to use to get the new structure.
   OUT:     pPool is modified such that one structure is "removed" from
              the free list.  If the free list is already empty,
              then a new block of nodes is allocated.  Also,
              the returned structure is zeroed out.
   RETURN:  Pointer to the structure taken from the free list.
   NOTES:   The pool knows how big its structures are.  The calling
              routine is responsible to make sure it is
              "using the right pool for the right job."
            Free the structure up by calling "ReturnToPool".
 *END_HEADER***************************/
voidPtr GetFromPool(PoolPtr pPool)
{
   voidPtr pStruct, *ppNext;
   CheckFreeList(pPool);///

   if (!pPool)
      return NULL; /* No pool, so no structures available. */
   if (!pPool->pFreeList)
   {
//#ifdef STATIC_MEMORY
//      return NULL; /* Don't allocate additional structures when you run out.
//                      You needed to allocate more to begin with. */
//#else
      /* Allocate another block of structures.  Insert the block into
         the block list, and insert the new structures into the 
         (currently empty) free list. */
      NewPoolBlock(pPool);
      if (pPool->pFreeList==NULL)
         return NULL; /* Out of memory */
//#endif
   }
   
   /* Retrieve a link off of the free list, and add it to *ppList */
   pStruct = pPool->pFreeList;        /* Get a pointer to the first free link on the free list. */
   FNX_ASSERT( (int)pStruct);                   /* (We should have added more links above if there weren't any available.)*/
   ppNext = (voidPtr *)pPool->pFreeList; /* Copy the address of the first free block (which is
                                               also the address of the 'next' pointer inside it) into ppPointer*/
   pPool->pFreeList = *ppNext;/* Move the head of the free list past the one we grabbed */
   /* Zero out the struct, since it may have garbage in it 
      (and does at least begin with a pointer that shouldn't be there).*/
   memset(pStruct, 0, pPool->iStructSize);
   /* Return a pointer to the struct */
   CheckFreeList(pPool);///
   return pStruct;
}  /* GetFromPool */

/*FUNCTION_HEADER**********************
   NAME:    ;ReturnToPool
   DESC:    Return a structure to the free list in a pool of structures.
   IN:      pStruct - Structure to return to the pool.
            pPool   - Pool of links to return the structure to.
   OUT:     pStruct is added to the beginning of pPool's free list.
   RETURN:  n/a
   NOTES:   Make sure you return structures only to the pool they came from,
              or you could be in deep trouble.  Don't pollute the pool!
 *END_HEADER***************************/
void ReturnToPool(voidPtr pStruct, PoolPtr pPool)
{
   voidPtr *ppStructNextPtr;

   CheckFreeList(pPool);///
   /* Make sure we don't crash */
   if (!pStruct || !pPool)
      return;
   /** Insert pStruct into the beginning of pPool's free list */
   ppStructNextPtr = (voidPtr *)pStruct; /* Copy the address of the hidden 'next' pointer at
                                            the beginning of pStruct into ppStructNextPtr. */
   *ppStructNextPtr = pPool->pFreeList;  /* Change the pointer at the beginning of pStruct to
                                            point to the old head of the free list */
   pPool->pFreeList = pStruct;           /* Point the free list at the new structure. */
   CheckFreeList(pPool);///
}  /* ReturnToPool */

/*FUNCTION_HEADER**********************
   NAME:    ;ReturnAllToPool
   DESC:    Return all elements of a pool to the free list of the pool.
   IN:      pPool   - Pool of links to return the structure to.
   OUT:     All elements in pPool are added to pPool's free list.
   RETURN:  n/a
   NOTES:   
 *END_HEADER***************************/
void ReturnAllToPool(PoolPtr pPool)
{
   voidPtr pBlockLink, pNext, *ppPointer;
   BlockListPtr pBlock;
   UBYTE   *pCurrentStruct;
   voidPtr *ppFreeList;
   SDWORD   iStructIndex, iStructSize, iBlockSize;

   if (pPool)
   {
      iStructSize = pPool->iStructSize;
      iBlockSize  = pPool->iBlockSize;
      /* Start out with ppFreeList pointing at the address of the main freelist pointer.
         At each point, *ppFreeList will point at the current structure, and then will
         advance to point at the structure's "pNext" field (which is its first four bytes).
         This allows the assignment to be made regardless of whether we are on the first
         block, a later block, or a structure within a block. */
      ppFreeList = &pPool->pFreeList;
      /* Free up the blocks of structures */
      for (pBlockLink=pPool->pBlockList; pBlockLink; pBlockLink = pNext)
      {
         /* Remember the address of the next link. */
         ppPointer = (voidPtr *) pBlockLink; /* Get the address of where the 'next' pointer is, 
                                                i.e., the beginning of the free block. */
         pNext = *ppPointer;                 /* Copy the next pointer out of that address */

         /* Typecast pBlockLink as a (UBYTE *) so that we can index past the first 4 bytes */
         pBlock = (BlockListPtr) pBlockLink;
         /* Point 'pCurrentStruct' at the first structure in the current block */
         pCurrentStruct = (UBYTE *)&(pBlock->sData);

         /* Recreate a linked list of structures by using the first few bytes
            of each structure to point to the next one in the list. */
         for (iStructIndex=0; iStructIndex < iBlockSize; iStructIndex++)
         {
            /* Point the last structure (or head of the list) to the current structure */
            *ppFreeList = (voidPtr)pCurrentStruct;
            /* Advance ppFreeList to point at this structure's 'pNext' field, which is its first four bytes */
            ppFreeList = (voidPtr *)pCurrentStruct;

            /* Advance pCurrentStruct to point at the beginning of the next struct */
            pCurrentStruct += iStructSize;
         }  /* for each structure in the current block */
      }  /* for pBlockLink */
      /* Null-terminate the free list */
      *ppFreeList = NULL;
   }  /* if pPool */
   CheckFreeList(pPool);///
}  /* ReturnAllToPool */

#ifdef STATIC_MEMORY
/*FUNCTION_HEADER**********************
   NAME:    ;FillPool
   DESC:    Pre-allocate a given number of elements in a pool.
   IN:      pPool   - Pool of structures to beef up.
            iNum    - Number of structures to pre-allocate
   OUT:     pPool has as many blocks of structures added to the free list
              as necessary so that at least iNum are allocated.
   RETURN:  n/a
   NOTES:   Any structures already being used in the pool are still ok.
              All newly-allocated structures are added to the free list.
 *END_HEADER***************************/
void FillPool(PoolPtr pPool, SDWORD iNum)
{
   BlockListPtr pBlock;
   SDWORD iNumBlocks, iNumBlocksNeeded;

   /* Count how many blocks are allocated */
   for (iNumBlocks=0, pBlock = pPool->pBlockList; pBlock; pBlock=pBlock->pNext)
      iNumBlocks++;
   /* Calculate how many blocks are needed to have at least iNum structures */
   iNumBlocksNeeded = iNum / pPool->iBlockSize;
   if (pPool->iBlockSize * iNumBlocksNeeded < iNum)
      iNumBlocksNeeded++;
   /* Add additional blocks to the free list */
   while (iNumBlocks < iNumBlocksNeeded)
   {
      NewPoolBlock(pPool);
      iNumBlocks++;
   }
}  /* FillPool */
#endif // STATIC_MEMORY

