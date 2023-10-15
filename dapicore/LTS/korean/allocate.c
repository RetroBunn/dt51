/*C_HEADER_FILE****************************************************************
FILE        :  allocate.c
DESC        :  memory handling functions
TABS        :  3
OWNER       :  fonix
DATE CREATED:  

(C) Copyright 2000 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 6/10/03 5:07p $
  $Revision: 20 $

*END_HEADER*******************************************************************/
#include "FnxAllocate.h"

#ifdef OS_AIX
//#include <stdio.h>   /* Required by AIX platform (TPE 08 May 2000) */
#include <string.h>
#endif

#ifdef TRACK_MEMORY
#include <malloc.h>
SDWORD   gnMallocs = 0, gnFrees = 0, gnBytes = 0, gnMaxBytes = 0, gnPtrs = 0, gnMaxPtrs = 0;

#ifdef TRACK_MEMORY_LEVEL1
struct aMSC    // MemoryStartChunk
{
#ifdef TRACK_MEMORY_LEVEL2
   struct aMSC *prev;
   struct aMSC *next;
#endif
   SDWORD   id;
   usize size;
   UBYTE fence[8];
};
typedef  struct aMSC FONIX_MSC;
typedef  FONIX_MSC   *FONIX_MSCPtr;

struct aMEC    // MemoryEndChunk
{
   UBYTE fence[8];
};
typedef  struct aMEC FONIX_MEC;
typedef  FONIX_MEC   *FONIX_MECPtr;

#ifdef TRACK_MEMORY_LEVEL2
#include "mutex.h"
int            gMListMIniting = -1;
Mutex       *gMListM = NULL;
FONIX_MSCPtr   gMList = NULL;
#endif //TRACK_MEMORY_LEVEL2

#define  FONIX_GetMSCPtr(p)   ((FONIX_MSCPtr)((UBYTE*)p-sizeof(FONIX_MSC)))
#define  FONIX_GetMECPtr(p)   ((FONIX_MECPtr)((UBYTE*)p+FONIX_GetMSCPtr(p)->size))
#define  FONIX_SetFence(p) {p[0]='f';p[1]='o';p[2]='n';p[3]='i';p[4]='x';p[5]=0xFF;p[6]=0x00;p[7]=0xAA;}
#define  FONIX_SetMC(p,mcid,mcsize) {FONIX_MSCPtr sc=FONIX_GetMSCPtr(p);FONIX_MECPtr ec;sc->id=mcid;sc->size=mcsize;FONIX_SetFence(sc->fence);ec=FONIX_GetMECPtr(p);FONIX_SetFence(ec->fence);}
#define  FONIX_GetMCID(p)  (FONIX_GetMSCPtr(p)->id)
#define  FONIX_GetMCSize(p)   (FONIX_GetMSCPtr(p)->size)
#define  FONIX_TestFence(p)   ((p[0]=='f')&&(p[1]=='o')&&(p[2]=='n')&&(p[3]=='i')&&(p[4]=='x')&&(p[5]==0xFF)&&(p[6]==0x00)&&(p[7]==0xAA))
#define  FONIX_TestMSCFence(p)   (FONIX_TestFence(FONIX_GetMSCPtr(p)->fence))
#define  FONIX_TestMECFence(p)   (FONIX_TestFence(FONIX_GetMECPtr(p)->fence))

#ifdef TRACK_MEMORY_LEVEL2
#define FONIX_LockList()   {if(gMListMIniting<0){gMListMIniting=1;gMListM=MutexInit(MUTEX_TYPE_PLAIN,100000);gMListMIniting=0;};if(gMListM)MutexLock(gMListM);}
#define  FONIX_UnlockList()   {if(!gMListMIniting)MutexUnlock(gMListM);}
#define  FONIX_AddToList(p)   {FONIX_LockList();{FONIX_MSCPtr sc=FONIX_GetMSCPtr(p);sc->prev=NULL;sc->next=gMList;if(gMList)gMList->prev=sc;gMList=sc;};FONIX_UnlockList();}
#define FONIX_RemoveFromList(p)  {FONIX_LockList();{FONIX_MSCPtr sc=FONIX_GetMSCPtr(p);if(sc==gMList){if(sc->next)sc->next->prev=NULL;gMList=sc->next;}else{if(sc->prev)sc->prev->next=sc->next;if(sc->next)sc->next->prev=sc->prev;}};FONIX_UnlockList();}
#endif //TRACK_MEMORY_LEVEL2

#endif //TRACK_MEMORY_LEVEL1

#endif //TRACK_MEMORY



#ifndef FONIX_MEMORY_MANAGER

#ifndef DEBUG_MEMORY_LEAKS

/***************************************************
 *  NAME:   fnxMalloc
 *  DESC:   Allocate a block of memory.
 *  IN:     size - Bytes to allocate
 *  OUT: 
 *  RETURN: a void pointer to the allocated memory.
 *  NOTES:  The Allocate function allocates a memory block
 *       of at least size bytes. The block may be larger
 *       than size bytes because of space required for
 *       alignment and maintenance information.
 ***************************************************/
voidPtr fnxMalloc(usize size)
{
   voidPtr  ptr = NULL;
#ifdef TRACK_MEMORY_LEVEL1
   usize tsize;
#endif //TRACK_MEMORY_LEVEL1

#ifdef MALLOC_ZERO_FIX
   if ( !size )
      size = 1;   // malloc( 0 ) behavior is undefined across OS, but it happens in the code
#endif //MALLOC_ZERO_FIX

#ifdef TRACK_MEMORY_LEVEL1
   tsize = size + sizeof(FONIX_MSC) + sizeof(FONIX_MEC);
   ptr = malloc(tsize);
#else //not TRACK_MEMORY_LEVEL1

   ptr = malloc(size); /* Regular memory allocation */

#endif //TRACK_MEMORY_LEVEL1

#ifdef TRACK_MEMORY
   if ( ptr )
   {
      gnMallocs++;
      gnBytes += size;
      if(gnBytes > gnMaxBytes)
         gnMaxBytes = gnBytes;
      gnPtrs++;
      if (gnPtrs > gnMaxPtrs)
         gnMaxPtrs = gnPtrs;
#  ifdef TRACK_MEMORY_LEVEL1
      ptr = (voidPtr)( (char*)ptr + sizeof(FONIX_MSC) );
      FONIX_SetMC(ptr,gnMallocs,size);
#    ifdef TRACK_MEMORY_LEVEL2
      FONIX_AddToList(ptr);
#    endif //TRACK_MEMORY_LEVEL2
#  endif //TRACK_MEMORY_LEVEL1
   }
#endif //TRACK_MEMORY

   FNX_ASSERT(ptr);  // Make sure memory allocation succeeded.

   return ptr;
}



/***************************************************
 *  NAME:   fnxCalloc
 *  DESC:   Allocates memory blocks and clears them.
 *  IN:     num - number of units
 *       size - bytes per unit
 *  OUT: 
 *  RETURN: a void pointer to the allocated memory.
 *  NOTES:  The Allocate function allocates a memory block
 *       of at least size bytes. The block may be larger
 *       than size bytes because of space required for
 *       alignment and maintenance information.
 ***************************************************/
voidPtr fnxCalloc(usize num, usize size)
{
   usize tsize = num * size;
   voidPtr ptr = FNX_MALLOC ( tsize );

   if ( ptr != NULL )
      memset ( ptr, 0, tsize );
   return ( ptr );
}



/***************************************************
 *  NAME:   fnxRealloc
 *  DESC:   Reallocate a memory block
 *  IN:     ptr - Pointer to previously allocated memory block
 *          size - New size in bytes
 *  OUT: 
 *  RETURN: a void pointer to the reallocated (and possibly
 *       moved) memory block. The return value is NULL if
 *       the size is zero and the buffer argument is not NULL,
 *       or if there is not enough available memory to expand
 *       the block to the given size. In the first case, the
 *       original block is freed. In the second, the original
 *       block is unchanged.
 *  NOTES:  
 ***************************************************/
voidPtr fnxRealloc(voidPtr ptr, usize size)
{
   {
      if ( ptr == NULL )
         return ( fnxMalloc ( size ) );
   }
   {
#ifdef TRACK_MEMORY_LEVEL1
      SDWORD oid = FONIX_GetMCID(ptr);
      usize osize = FONIX_GetMCSize(ptr);
      usize tsize;
#endif //TRACK_MEMORY_LEVEL1

#ifdef MALLOC_ZERO_FIX
      if( !size )
         size = 1;   // malloc( 0 ) behavior is undefined across OS, but it happens in the code
#endif //MALLOC_ZERO_FIX

#ifdef TRACK_MEMORY

#  ifdef TRACK_MEMORY_LEVEL1
      if ( ptr )
      {
         FNX_ASSERT ( FONIX_TestMSCFence(ptr) );   // fence at beginning of memory block has been damaged!
         FNX_ASSERT ( FONIX_TestMECFence(ptr) );   // fence at end of memory block has been damaged!
#    ifdef TRACK_MEMORY_LEVEL2
         FONIX_RemoveFromList(ptr);
#    endif //TRACK_MEMORY_LEVEL2
         gnBytes += ( size - osize );
      }
      else
         gnBytes += size;
      tsize = size + sizeof(FONIX_MSC) + sizeof(FONIX_MEC);
      ptr = realloc ( FONIX_GetMSCPtr(ptr), tsize );
#  else //not TRACK_MEMORY_LEVEL1
      if ( ptr )
         gnBytes += ( size - _msize(ptr) );
      else
         gnBytes += size;
      ptr = realloc ( ptr, size );
#  endif //TRACK_MEMORY_LEVEL1
      if ( gnBytes > gnMaxBytes )
         gnMaxBytes = gnBytes;
#  ifdef TRACK_MEMORY_LEVEL1
      if ( ptr )
      {
         ptr = (voidPtr)( (char*)ptr + sizeof(FONIX_MSC) );
         FONIX_SetMC(ptr,oid,size);
#    ifdef TRACK_MEMORY_LEVEL2
         FONIX_AddToList(ptr);
#    endif //TRACK_MEMORY_LEVEL2
      }
#  endif //TRACK_MEMORY_LEVEL1
#else //not TRACK_MEMORY

      ptr = realloc ( ptr, size );  /* Regular memory allocation */

#endif

      FNX_ASSERT ( ptr );  // memory allocation has failed!
   }
   return ( ptr );
}



/***************************************************
 *  NAME:   fnxFree
 *  DESC:   Deallocates or frees a memory block.
 *  IN:     ptr - Previously allocated memory block to be freed
 *  OUT: 
 *  RETURN: 
 *  NOTES:  
 ***************************************************/
void fnxFree(voidPtr ptr)
{
   FNX_ASSERT(ptr);  // a NULL pointer was passed into Deallocate!

#ifdef TRACK_MEMORY
   if ( ptr )
   {
#ifdef TRACK_MEMORY_LEVEL1
      FNX_ASSERT ( FONIX_TestMSCFence(ptr) );   // fence at beginning of memory block has been damaged!
      FNX_ASSERT ( FONIX_TestMECFence(ptr) );   // fence at end of memory block has been damaged!
#ifdef TRACK_MEMORY_LEVEL2
      FONIX_RemoveFromList(ptr);
#endif //TRACK_MEMORY_LEVEL2
      gnBytes -= FONIX_GetMCSize(ptr);
      free ( FONIX_GetMSCPtr(ptr) );
#else //not TRACK_MEMORY_LEVEL1
      gnBytes -= _msize(ptr);
      free ( ptr );
#endif //TRACK_MEMORY_LEVEL1
      gnFrees++;
      gnPtrs--;
   }
#else //not TRACK_MEMORY

   free ( ptr );  /* Regular memory deallocatino */

#endif //TRACK_MEMORY
}

#endif  //not DEBUG_MEMORY_LEAKS


/******** MemCheck **********/
void MemCheck ( char *message )
{
#ifdef   TRACK_MEMORY
   if ( message != NULL )
      printf ( "MemCheck - %s\n", message );
   else
      printf ( "MemCheck\n" );
#endif
#ifdef   TRACK_MEMORY_LEVEL2
   if ( gMList != NULL )
   {
      FONIX_MSCPtr ptr = gMList;
      void *vptr;

      while ( ptr != NULL )
      {
         vptr = (voidPtr)( (char*)ptr + sizeof(FONIX_MSC) );
         FNX_ASSERT ( FONIX_TestMSCFence(vptr) );  // fence at beginning of memory block has been damaged!
         FNX_ASSERT ( FONIX_TestMECFence(vptr) );  // fence at end of memory block has been damaged!
         printf ( "    Allocation #%d, Size %d\n", ptr->id, ptr->size );
         ptr = ptr->next;
      }
      printf ( "    ...End of allocations.\n\n" );
   }
   else
      printf ( "    ...No allocated memory in list.\n\n" );
#else
#  ifdef TRACK_MEMORY
      printf ( "    ...No checking enabled!\n\n" );
#  endif
#endif
}



/******** MemAllocsCalled **********/
int   MemAllocsCalled ( )
{
#ifdef   TRACK_MEMORY
   return ( gnMallocs );
#else
   return ( 0 );
#endif
}

/******** MemBytesAllocated **********/
int   MemBytesAllocated ( )
{
#ifdef   TRACK_MEMORY
   return ( gnBytes );
#else
   return ( 0 );
#endif
}

/******** MemFreesCalled **********/
int   MemFreesCalled ( )
{
#ifdef   TRACK_MEMORY
   return ( gnFrees );
#else
   return ( 0 );
#endif
}

/******** MemPtrsAllocated **********/
int   MemPtrsAllocated ( )
{
#ifdef   TRACK_MEMORY
   return ( gnPtrs );
#else
   return ( 0 );
#endif
}



#else //FONIX_MEMORY_MANAGER defined...

/******************************
   FONIX_MEMORY_MANAGER

   malloc is redefined in memarray.h to be memarray.c::myMalloc() 
   realloc is redefined in memarray.h to be memarray.c::myRealloc()
   free is redefined in memarray.h to be memarray.c::myFree()

 ******************************/

#include "FnxMemArray.h"

/***************************************************
 *  NAME:   fnxMalloc
 *  DESC:   Allocates memory blocks.
 *  IN:     size - Bytes to allocate
 *  OUT: 
 *  RETURN: a void pointer to the allocated memory.
 *  NOTES:  The Allocate function allocates a memory block
 *       of at least size bytes. The block may be larger
 *       than size bytes because of space required for
 *       alignment and maintenance information.
 ***************************************************/
voidPtr fnxMalloc(usize size)
{
#ifdef MALLOC_ZERO_FIX
   if( !size )
      size = 1;   // malloc( 0 ) behavior is undefined across OS, but it happens in the code
#endif

   SDWORDPTR   ptr = (SDWORDPTR)malloc(size);

   FNX_ASSERT(ptr);

#ifdef TRACK_MEMORY
   if (ptr)
   {
      gnMallocs++;
      gnBytes += GetMemSize(ptr);
      if (gnBytes > gnMaxBytes)
      {
         gnMaxBytes = gnBytes;
      }
      gnPtrs++;
      if (gnPtrs > gnMaxPtrs)
      {
         gnMaxPtrs = gnPtrs;
      }
   }
#endif //TRACK_MEMORY

   return ptr;
}



/***************************************************
 *  NAME:   fnxRealloc
 *  DESC:   Reallocate a memory block
 *  IN:     ptr - Pointer to previously allocated memory block
 *       size - New size in bytes
 *  OUT: 
 *  RETURN: a void pointer to the reallocated (and possibly
 *       moved) memory block. The return value is NULL if
 *       the size is zero and the buffer argument is not NULL,
 *       or if there is not enough available memory to expand
 *       the block to the given size. In the first case, the
 *       original block is freed. In the second, the original
 *       block is unchanged.
 *  NOTES:  
 ***************************************************/
voidPtr fnxRealloc(voidPtr ptr, usize size)
{
   SDWORD      oldSize;
   SDWORDPTR   newPtr;

#ifdef MALLOC_ZERO_FIX
   if( !size )
      size = 1;   // malloc( 0 ) behavior is undefined across OS, but it happens in the code
#endif

   if (ptr)
   {
#ifdef TRACK_MEMORY
      oldSize = GetMemSize(ptr);
#endif
      
      newPtr = (SDWORDPTR)realloc(ptr, size);

#ifdef TRACK_MEMORY
      if (newPtr)
      {
         gnBytes += GetMemSize(newPtr) - oldSize;
         if (gnBytes > gnMaxBytes)
         {
            gnMaxBytes = gnBytes;
         }
      }
#endif
   }
   else
   {
      newPtr = fnxMalloc(size);
   }

   return newPtr;
}



/***************************************************
 *  NAME:   fnxFree
 *  DESC:   Deallocates or frees a memory block.
 *  IN:     ptr - Previously allocated memory block to be freed
 *  OUT: 
 *  RETURN: 
 *  NOTES:  
 ***************************************************/
void fnxFree(voidPtr ptr)
{
   if (ptr)
   {
#ifdef TRACK_MEMORY
      gnBytes -= GetMemSize(ptr);
      gnPtrs--;
#endif

      free(ptr);
   }
}

#endif   /*  FONIX_MEMORY_MANAGER  */

#ifdef ALIGN_DATA_16
#ifdef NO_ALIGNED_MALLOC
/* If there is no special command available to allocate a
   16-byte aligned block of memory, we'll create one ourselves.
   This is done by allocating size+17 bytes.  The first byte
   is set to a 1, and then as many other bytes as necessary
   are set to 0 until a 16-byte boundary is reached.  The
   returned address is the one on the 16-byte boundary.
   In Deallocate16, the preceding 0's are skipped until
   the 1 is found, and then THAT address is passed to free(). */
voidPtr Allocate16(usize size)
{
   char *ptr;                 /* Use a char pointer so the address arithmatic will use units of 1 */

   ptr = malloc(size + 17);
   ptr[0] = 0x01;             /* Set the first allocated byte to 1 */
   ptr++;                     /* Move past the 1. */
   while ((UDWORD)ptr&(UDWORD)0x0F) /* See if we have found a 16-byte aligned address yet */
     *(ptr++) = 0;               /* Set all filler bytes to 0 */
   return (voidPtr) ptr;         /* Return the 16-byte aligned address [which is preceding by a 1 and possibly 0's */
}



void Deallocate16(voidPtr ptr)
{
   char *p = ptr;  /* Get a character pointer so that "p--" will subtract 1 instead of 4 or something */

   /* 'ptr' was NOT returned by malloc, but an earlier address was, so skip all
      preceding 0's until the 1 is found. */
   p--; /* Move to the previous byte */
   while (*p == 0)
      p--;
   FNX_ASSERT(*p == 1);
   /* Now that we have found the address that was originally returned by malloc, free it */
   free(p);
}

#elif __VEC__                                // AltiVec
voidPtr Allocate16(usize size)
{
   voidPtr  ptr = vec_malloc(size);
   FNX_ASSERT(ptr);
   return ptr;
}



void Deallocate16(voidPtr ptr)
{
   FNX_ASSERT(ptr);
   if ( ptr )
   {
      vec_free(ptr);
   }
}
#elif defined(linux)
#include <malloc.h>
voidPtr Allocate16(usize size)
{
   voidPtr  ptr = memalign(size, 16);
   FNX_ASSERT(ptr);
   return ptr;
}



void Deallocate16(voidPtr ptr)
{
   FNX_ASSERT(ptr);
   if ( ptr )
   {
      free(ptr);
   }
}

#else // assume Windows
// 16-byte-aligned versions of Allocate() and Deallocate() for use
//   in Pentium III optimized code (when using vector processors).
#include "xmmintrin.h"

voidPtr Allocate16(usize size)
{
   voidPtr  ptr = _mm_malloc(size, 16);
   FNX_ASSERT(ptr);
   return ptr;
}



void Deallocate16(voidPtr ptr)
{
   FNX_ASSERT(ptr);
   if ( ptr )
   {
      _mm_free(ptr);
   }
}
#endif   // __VEC__

/*FUNCTION_HEADER**********************
 * NAME:   ;RoundUp16
 * DESC:   Round a number up to an even multiple of 16 (unless it already is one).
 * IN:     iSize - Value to round up.
 * OUT:    n/a
 * RETURN: iSize + any value needed to make it a multiple of 16 (e.g., 28->32, 3->16, 64->64).
 * NOTES:  Just returns iSize if it is already a multiple of 16.
 *END_HEADER***************************/
SDWORD RoundUp16(SDWORD iSize)
{
   if (iSize & 0x0F)
   {
      /* iSize is not a multiple of 16, so round up */
      iSize += (16 - iSize & 0x0F);
   }
   return iSize;
}
#endif   // ALIGN_DATA_16



/*FUNCTION_HEADER**********************
 * NAME:   ;NVecAlloc
 * DESC:   Allocate an efficient 2-dimensional array of elements of any size.
 * IN:     iNumVectors  - Number of vectors to allocate in the block.
           iNumElements - Number of elements per vector.
           iElementSize - Number of bytes in each element.
 * OUT:    A two-dimensional array of iElementSize-sized elements is allocated.
 * RETURN: Pointer to the 2-D array.
 * NOTES:  Use VecFree(ppVec) to free up the returned 2D array.
           This routine allocates ONE block of memory, which contains
             an array of pointers at the beginning which point to the
             beginning of each of the vectors located in the last portion
             of the block.
           You can call as "ppStruct=NVecAlloc(iNumStruct,1,sizeof(STRUCT))"
             to efficiently allocate an array of pointers to allocated structures that
             can be easily free'd.
 *END_HEADER***************************/
char **NVecAlloc(SDWORD iNumVectors, SDWORD iNumElements, SDWORD iElementSize)
{
   char **psVec = NULL;
   SDWORD i;
   SDWORD iPointersSize; /* Size needed for all pointers at the beginning of the block*/
   SDWORD iVectorSize;   /* Size of each vector, in bytes (including any extra bytes to 
                            align to 16-byte boundaries, if needed). */

   /* The arithmatic in this routine depends upon characters being a single byte */
   FNX_ASSERT(sizeof(char) == 1);
   if (iNumVectors > 0 && iNumElements > 0)
   {
      /* Allocate a single block of memory with enough room for
         pointers to all of the vectors PLUS the actual vectors. 
         (Round up to the nearest 16-byte boundary, iff DATA_ALIGN_16 is defined,
         so that each vector can begin on a 16-byte boundary).*/
      iPointersSize = iNumVectors * sizeof(char *);
      iVectorSize   = iNumElements * iElementSize;
      psVec = (char **)FNX_MALLOC(iPointersSize + iNumVectors * iVectorSize);
      if (psVec != NULL)
      {
         /* Set the first pointer to point just beyond the array of pointers,
            i.e., point at the beginning of the block of real vector data */
         psVec[0] = (char *)((SDWORD)psVec + iPointersSize);
         /* Clear all the vectors out by setting them to 0 */
         memset(psVec[0], 0, iNumVectors * iVectorSize);
         /* Set all of the other pointers into the main block of memory at the 
            location where each vector begins */
         for (i = 1; i < iNumVectors; i++)
            psVec[i] = (char *)((SDWORD)psVec[i - 1] + iVectorSize);
      }
   }  /* if we have rows & columns */
   else psVec = NULL;

   return psVec;
}  /* NVecAlloc */

/*FUNCTION_HEADER**********************
 * NAME:   ;CoreVecAlloc
 * DESC:   Allocate an efficient 2-dimensional array of CoreType's (i.e., 2-byte shorts or 4-byte floats,
             depending on whether INTEGER_CORE is defined or not, respectively).
 * IN:     iNumVectors - Number of rows (i.e., number of vectors)
           iNumElements - Number of columns (i.e., number of floats per vector)
 * OUT:    A two-dimensional array of CoreType's is allocated.
 * RETURN: Pointer to the 2-D array.
 * NOTES:  The same as VecAlloc(), except that it uses CoreType's.
           Use VecFree(ppfVec) to free up the returned 2D array.
           Also, if DATA_ALIGN_16 is defined, then, unlike VecAlloc() (or NVecAlloc()),
             this routine will ensure that all vectors begin on a
             16-byte-aligned address.
 *END_HEADER***************************/
CoreTypePtr *CoreVecAlloc(SDWORD iNumVectors, SDWORD iNumElements)
{
   char **psVec = NULL;
   SDWORD i;
   SDWORD iPointersSize; /* Size needed for all pointers at the beginning of the block*/
   SDWORD iVectorSize;   /* Size of each vector, in bytes (including any extra bytes to 
                            align to 16-byte boundaries, if needed). */

   /* The arithmatic in this routine depends upon characters being a single byte */
   FNX_ASSERT(sizeof(char) == 1);
   if (iNumVectors > 0 && iNumElements > 0)
   {
      /* Allocate a single block of memory with enough room for
         pointers to all of the vectors PLUS the actual vectors. 
         (Round up to the nearest 16-byte boundary, iff DATA_ALIGN_16 is defined,
         so that each vector can begin on a 16-byte boundary.  Include
         an additional 16 bytes in case it is necessary to leave a few
         bytes of a gap between the pointers and the first vector to
         make sure the first vector is 16-byte-aligned.).*/
      iPointersSize = iNumVectors * sizeof(char *);
#ifdef ALIGN_DATA_16
      iVectorSize   = RoundUp16(iNumElements * sizeof(CoreType));
      psVec = (char **)FNX_MALLOC(iPointersSize + iNumVectors * iVectorSize + 16);
#else
      iVectorSize   = iNumElements * sizeof(CoreType);
      psVec = (char **)FNX_MALLOC(iPointersSize + iNumVectors * iVectorSize);
#endif
      if (psVec != NULL)
      {
         /* Set the first pointer to point just beyond the array of pointers,
            i.e., point at the beginning of the block of real vector data */
         psVec[0] = (char *)((SDWORD)psVec + iPointersSize);
#ifdef ALIGN_DATA_16
         /* If doing 16-byte-aligned vectors, make sure the first vector begins
            on a 16-byte boundary. */
         psVec[0] = (char *)RoundUp16((SDWORD)psVec[0]);
#endif
         /* Clear all the vectors out by setting them to 0 */
         memset(psVec[0], 0, iNumVectors * iVectorSize);
         /* Set all of the other pointers into the main block of memory at the 
            location where each vector begins */
         for (i = 1; i < iNumVectors; i++)
            psVec[i] = (char *)((SDWORD)psVec[i - 1] + iVectorSize);
      }
   }  /* if we have rows & columns */
   else psVec = NULL;

   return (CoreTypePtr *)psVec;
}  /* CoreVecAlloc */



/*FUNCTION_HEADER**********************
 * NAME: ;VecAlloc
 * DESC:    Allocate an efficient 2-dimensional array of CalcType's (e.g., floats).
 * IN:      iNumVectors - Number of rows (i.e., number of vectors)
            iNumElements - Number of columns (i.e., number of floats per vector)
 * OUT:     A two-dimensional array of floats is allocated.
 * RETURN:  Pointer to the 2-D array.
 * NOTES:   Use VecFree(ppfVec) to free up the returned 2D array.
 *END_HEADER***************************/
CalcTypePtr *VecAlloc(SDWORD iNumVectors, SDWORD iNumElements)
{
   return (CalcTypePtr *) NVecAlloc(iNumVectors, iNumElements, sizeof(CalcType));
}  /* VecAlloc */



/*FUNCTION_HEADER**********************
 * NAME: ;VecFree
 * DESC:    Free an array of vectors allocated by VecAlloc.
 * IN:      ptr - Pointer to the array of vectors to be freed.
 * OUT:     The array of vectors is freed.
 * RETURN:  n/a
 * NOTES:   Can handle (i.e., ignore) NULL pointers.
            ptr is an array of pointers into different vectors
            located in the SAME block of memory.  Thus, ptr[0]
            is freed to free up the block of memory containing
            all the values, and then ptr itself is freed to
            free up all the pointers.
 *END_HEADER***************************/
void VecFree(voidPtr *ptr)
{
   if (ptr)
   {
      FNX_FREE(ptr);
   }
}  /* VecFree */



/*FUNCTION_HEADER**********************
 * NAME:    ;VecCopy
 * DESC:    Allocate a copy of an efficient vector array.
 * IN:      ppfVec - Source vector to be copied
            iNumVectors - Number of rows (i.e., number of vectors)
            iNumElements - Number of columns (i.e., number of floats per vector)
 * OUT:     A two-dimensional array of floats is allocated and
              filled with the same values as ppfVec[][].
 * RETURN:  Pointer to the 2-D array.
 * NOTES:   Use VecFree() to free the returned value.  See VecAlloc() for
              information on the 2-D array structure.
            Does not check to make sure iNumVectors and iNumElements matches.
 *END_HEADER***************************/
CalcTypePtr *VecCopy(CalcTypePtr *ppfVec, SDWORD iNumVectors, SDWORD iNumElements)
{
   CalcTypePtr *ppfNewVec;
   /* Allocate a new, empty 2-D array */
   ppfNewVec = VecAlloc(iNumVectors, iNumElements);
   /* Copy all of the data from the old array into the new one */
   memcpy(ppfNewVec[0], ppfVec[0], sizeof(CalcType) * iNumVectors * iNumElements);
   /* Return a pointer to the new array */
   return ppfNewVec;
}  /* VecCopy */



/***************************************************
 *  NAME:   FreeAndClear
 *  DESC:   Deallocates a block of memory and sets the pointer to NULL.
 *  IN:     ppMemory - Address of pointer to previously allocated memory block to be freed
 *  OUT:    *ppMemory is deallocated and set to NULL (unless already NULL, in which case nothing happens).
 *  RETURN: n/a
 *  NOTES:  It is fine for *ppMemory to be NULL already, so instead of doing
              if (pPtr) {Deallocate(pPtr); pPtr=NULL;}, you can do FreeAndClear((voidPtr *)&pPtr);
 ***************************************************/
void FreeAndClear(voidPtr *ppMemory)
{
   if (ppMemory && *ppMemory)
   {
      FNX_FREE(*ppMemory);
      *ppMemory = NULL;
   }
}  /* FreeAndClear */



