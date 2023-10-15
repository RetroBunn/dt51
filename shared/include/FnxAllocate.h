
/*H_HEADER_FILE***************************************************************
FILE        : allocate.h
DESC        : memory allocation routines
TABS        : 3
OWNER       : Fonix
DATE CREATED: 

(C) Copyright 2000 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/26/03 4:11p $
  $Revision: 14 $

*END_HEADER******************************************************************/
#ifndef FNXALLOCATE_H
#  define FNXALLOCATE_H

/* Uncomment this line if you need to run BoundsChecker to track down
   memory leaks.  (Otherwise, all memory leaks will appear in the
   Allocate() routine, which isn't too helpful). */
//#define DEBUG_MEMORY_LEAKS

/* Uncomment this line if you want to keep memory debug information.
   The total number of allocations is kept as are the number of pointers currently
   allocated, and the total number of bytes in currently allocated memory. */
//#define TRACK_MEMORY

/* The level 1 and 2 memory tracking is only turned on in debug builds. */
#if defined (_DEBUG) && defined(TRACK_MEMORY)

/* Uncomment this line if you want to enable more intensive memory debugging.
   Chunks of data are added before the beginning and after the end of the allocated memory.
   The start chunk contains the count of when the memory was allocated and the size
   of the memory block. In addition each chunk contains an array of specific values
   called fences that are used to check for memory overruns.
   NOTE: TRACK_MEMORY MUST ALSO BE DEFINED FOR THIS TO OPERATE! */
//#   define TRACK_MEMORY_LEVEL1

/* Uncomment this line if you want to enable memory list tracking. A list of allocated
   blocks will be kept and can be checked to see if memory has been allocated and not
   released.  [drw - TRACK_MEMORY_LEVEL2 requires being able to #include "mutex.h", wherever that is]
   NOTE: TRACK_MEMORY AND TRACK_MEMORY_LEVEL1 MUST ALSO BE DEFINED FOR THIS TO OPERATE! */
//#   define TRACK_MEMORY_LEVEL2
#endif

#if defined(__cplusplus)
   extern "C" {
#endif

#include "FnxPlatform.h"
#include "DTFnxStdlib.h"
// Looking for <assert.h>? Put it in your FnxMachine.h

#  ifdef DEBUG_MEMORY_LEAKS
#      include <stdlib.h>
#  define   fnxMalloc   malloc
#  define  fnxCalloc calloc
#  define   fnxRealloc  realloc
#  define   fnxFree     free
#else  // not DEBUG_MEMORY_LEAKS
#     ifdef FONIX_MEMORY_MANAGER
      // Use these defines to pin point memory leaks with BoundsChecker
#        if defined(IMPORT_MEMPROCS)
#           define   MEM_ACCESS  IMPORT
#        elif defined(EXPORT_MEMPROCS)  // IMPORT_MEMPROCS
#           define   MEM_ACCESS  FNX_EXPORT
#        else  // EXPORT_MEMPROCS
#           define   MEM_ACCESS(a,b) a b
#        endif  // EXPORT_MEMPROCS

         MEM_ACCESS(voidPtr, fnxMalloc(usize size));
         MEM_ACCESS(voidPtr, fnxCalloc(usize num, usize size));
         MEM_ACCESS(voidPtr, fnxRealloc(voidPtr ptr, usize size));
         MEM_ACCESS(void, fnxFree(voidPtr ptr));
         MEM_ACCESS(void, MemCheck(char *message));
         MEM_ACCESS(int, MemAllocsCalled());
         MEM_ACCESS(int, MemBytesAllocated());
         MEM_ACCESS(int, MemFreesCalled());
         MEM_ACCESS(int, MemPtrsAllocated());

#     else  // not FONIX_MEMORY_MANAGER
#        include <stdlib.h>
#           if defined(WIN32) || defined(UNDER_CE)
               FNX_EXPORT(voidPtr, fnxMalloc(usize size) );
               FNX_EXPORT(voidPtr, fnxCalloc(usize num, usize size) );
               FNX_EXPORT(voidPtr, fnxRealloc(voidPtr ptr, usize size) );
               FNX_EXPORT(void, fnxFree(voidPtr ptr) );
               FNX_EXPORT(void, MemCheck(char *message));
               FNX_EXPORT(int, MemAllocsCalled());
               FNX_EXPORT(int, MemBytesAllocated());
               FNX_EXPORT(int, MemFreesCalled());
               FNX_EXPORT(int, MemPtrsAllocated());
#           endif  // WIN32 || UNDER_CE
            voidPtr fnxMalloc(usize size);
            voidPtr fnxCalloc(usize num, usize size);
            voidPtr fnxRealloc(voidPtr ptr, usize size);
            void fnxFree(voidPtr ptr);
#  endif  // FONIX_MEMORY_MANAGER
#endif // not DEBUG_MEMORY_LEAKS

#ifdef ALIGN_DATA_16 // Pentium III or Mac G4 vector processor optimitzations
   FNX_EXPORT(voidPtr, Allocate16(usize size));
   FNX_EXPORT(void,Deallocate16(voidPtr ptr));
#endif

/*  Define some necessary prototypes  */
FNX_EXPORT( void, FreeAndClear(voidPtr *ppMemory));
FNX_EXPORT( char **, NVecAlloc(SDWORD iNumRows, SDWORD iNumCols, SDWORD iSize));
FNX_EXPORT( CoreTypePtr *, CoreVecAlloc(SDWORD rows, SDWORD cols));
FNX_EXPORT( CalcTypePtr *, VecAlloc(SDWORD rows, SDWORD cols));
FNX_EXPORT( CalcTypePtr *, VecCopy(CalcTypePtr *ppfSourceVec, SDWORD rows, SDWORD cols));
FNX_EXPORT( void, VecFree(voidPtr *ptr));

#if defined(__cplusplus)
}
#endif
// FNXALLOCATE_H
#endif 
