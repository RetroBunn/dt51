/*H_HEADER_FILE***************************************************************
FILE        : pool.h
DESC        : Defintions for a pool of structures
TABS        : 3
OWNER       : Randy Wilson
DATE CREATED   : 31 October 2000

(C) Copyright 2000 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/26/03 4:12p $
  $Revision: 6 $

*END_HEADER******************************************************************/
#ifndef  POOL_H
#define  POOL_H

#include "FnxPlatform.h"

typedef struct _BlockList
{
   struct _BlockList *pNext;
   char  *sData; /* Use &pBlockList->sData to get the address of where the data begins */
   /* and then data... */
} xhuge *BlockListPtr; /* No need to allocate a single blocklist struct, since data must be included */

/* In order to be more efficient in time & space, a pool
   of structures can be maintained.  Structures are
   allocated in blocks and freed structures are reused before
   additional blocks of structures are allocated. */
typedef struct _pool
{
   void        *pFreeList;   /* Pointer to the first free structure in the pool */
   BlockListPtr pBlockList;  /* Linked list of blocks of structures. */
   SDWORD       iBlockSize;  /* Number of structures to allocate in each block of structures */
   SDWORD       iStructSize; /* Size of each structure */
} Pool, xhuge *PoolPtr;

/* You should probably define a new pool type for each kind of
   thing you're going to store in a pool to avoid confusing
   multiple pools you might be using (e.g., LinkPoolPtr, NodePoolPtr...).*/

/* Function prototypes */
#if defined(__cplusplus)
extern "C" {
#endif

extern PoolPtr NewPool(SDWORD iBlockSize, SDWORD iStructSize);
extern void    FreePool(PoolPtr pPool);
extern voidPtr GetFromPool(PoolPtr pPool);
extern void    ReturnToPool(voidPtr pStruct, PoolPtr pPool);
extern void    ReturnAllToPool(PoolPtr pPool);

#ifdef STATIC_MEMORY
extern void FillPool(PoolPtr pPool, SDWORD iNum);
#endif

#if defined(__cplusplus)
}
#endif

#endif
