/*H_HEADER_FILE***************************************************************
FILE        : llist.h
DESC        : linked list definitions
TABS        : 3
OWNER       : R. Brian Moncur
DATE CREATED   : 11 October 1999

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/26/03 4:12p $
  $Revision: 7 $

*END_HEADER******************************************************************/
#ifndef  LLIST_H
#define  LLIST_H

#include "FnxPlatform.h"
#include "FnxPool.h"

#ifdef OS_UNIX
#  include <sys/stat.h>
#  include <fcntl.h>
#  include <unistd.h>
#  include <sys/types.h>
#  include <dirent.h>
#  include <errno.h>
#endif

#ifdef  OS_UNIX
#  define  _MAX_PATH  FILENAME_MAX
#endif

/* Linked list of pointers. WARNING: The 'pNext' field MUST be first!
   While this structure is usually used for a linked list of pointers,
   it is also used for linked lists of memory blocks which start with
   a 'next' pointer and then have data (e.g., a pool of indices)
   immediately after the pointer. */
typedef struct _llist
{
   struct _llist xhuge *pNext;
   void *p;
} LLIST, xhuge *llistPtr;

/* In order to be more efficient in time & space, a pool
   of linked list nodes can be maintained.  Links are
   allocated in blocks and freed links are reused before
   additional blocks of links are allocated. */
/* Define LinkPool (and LinkPoolPtr) using the general
   Pool structure.  Having a separate type definition
   for link pools will help make sure we don't mix the
   pools.  That would be bad. */
typedef Pool LinkPool, xhuge *LinkPoolPtr;

#if defined(__cplusplus)
extern "C" {
#endif

FNX_EXPORT( LinkPoolPtr, NewLinkPool(SDWORD iBlockSize));
FNX_EXPORT( void, InsertLink(void *p, llistPtr *pList, LinkPoolPtr pLinkPool));
FNX_EXPORT( void, DeleteLink(void *p, llistPtr *pList, LinkPoolPtr pLinkPool));

/* Linked-list functions */
FNX_EXPORT( LLIST *, FindLink(LLIST *pLList, char *sName, BOOL bCaseSensitive));
FNX_EXPORT( LLIST *, NewLink(void *p, LLIST *pNext));
FNX_EXPORT( LLIST *, NewStringLink(char *s, LLIST *pNext) );
FNX_EXPORT( LLIST *, FreeLink(LLIST *pLink));
FNX_EXPORT( LLIST *, FreeStringLink(LLIST *pLink));

FNX_EXPORT( SDWORD,  ListSize(LLIST *pList));
FNX_EXPORT(char *,  CombineStringList(llistPtr *ppList, LinkPoolPtr pLinkPool));
FNX_EXPORT(char **, ListToArray(LLIST **ppList, SDWORD iNumElements, LinkPoolPtr pLinkPool) );
FNX_EXPORT(void,    FreePointerArray(char **ppPtrArray, SDWORD iNumElements));
FNX_EXPORT(void,    FreeList(LLIST **ppLink, LinkPoolPtr pLinkPool));
FNX_EXPORT(LinkPoolPtr, NewLinkPool(SDWORD iBlockSize));
FNX_EXPORT(void,    FreeLinkPool(LinkPoolPtr pLinkPool));
FNX_EXPORT(void,    InsertLink(void *p, llistPtr *ppList, LinkPoolPtr pLinkPool));
FNX_EXPORT(void,    AppendLink(void *p, llistPtr *ppList, LinkPoolPtr pLinkPool));
FNX_EXPORT(void,    RemoveLink(llistPtr *ppList, LinkPoolPtr pLinkPool));
FNX_EXPORT(SDWORD,  ReplaceLink(llistPtr pList, void *pOldPointer, void *pNewPointer));
FNX_EXPORT(SDWORD,  RemovePointerFromList(void *pOldPointer, llistPtr *ppList, LinkPoolPtr pLinkPool));
FNX_EXPORT(BOOL,    LinkExists(void *pOldPointer, llistPtr pList));
FNX_EXPORT(void,    ReverseList(llistPtr *ppList));

#if defined(__cplusplus)
}
#endif

#endif
