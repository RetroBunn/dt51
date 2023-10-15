/*
 * 001	MGS		05/09/2001		Some VxWorks porting BATS#972
 * 002	MGS		06/19/2001		Solaris Port BATS#972
 */
//moved to port.h for each platform - mlt
//#include <stdlib.h>
//#if !defined VXWORKS && !defined _APPLE_MAC_
//#include <malloc.h>
//#endif
//#include <stdio.h>
#include "port.h" //added for platform specific stuff - mlt
#ifdef __arm__
#define _MIT_POSIX_THREADS 1
#endif
//moved to port.h for each platform - mlt
//#if defined _UNIX_LIKE_
//#include <pthread.h>
//#endif
//#include "opthread.h"
#include "mmalloc.h"
#include "playaudd.h"
#include "playaud.h"


/**********************************************************************/
/*  Shared memory allocation structures for UNIX                      */
/**********************************************************************/

typedef long qAlign;

union MEM_HEADER_T
{
  struct
  {
    union MEM_HEADER_T * pLink;
    unsigned int uiSize;
  } Block;

  qAlign qForceAlignment;  /* This forces proper memory alignment */
};

typedef union MEM_HEADER_T MEMORY_HEADER_T;
typedef MEMORY_HEADER_T * LPMEMORY_HEADER_T;

/**********************************************************************/
/*  Structure for Shared Memory Linked List.                          */
/**********************************************************************/

struct SHARED_MEMORY_LIST_TAG
{
  struct SHARED_MEMORY_LIST_TAG * pLink;
  void * pSharedMemory;
};

typedef struct SHARED_MEMORY_LIST_TAG SHARED_MEMORY_LIST_T;
typedef SHARED_MEMORY_LIST_T * LPSHARED_MEMORY_LIST_T;

/**********************************************************************/
/*  Structure for Allocated Memory Linked List.                       */
/**********************************************************************/

struct ALLOCATED_MEMORY_LIST_TAG
{
  struct ALLOCATED_MEMORY_LIST_TAG * pLink;
  void * pAllocatedMemory;
};

typedef struct ALLOCATED_MEMORY_LIST_TAG ALLOCATED_MEMORY_LIST_T;
typedef ALLOCATED_MEMORY_LIST_T * LPALLOCATED_MEMORY_LIST_T;


typedef struct MESSAGE_QUEUE_TAG
{

  LPATYPE_T pStart;
  LPATYPE_T pInput;
  LPATYPE_T pOutput;
  unsigned int uiInputPosition;
  unsigned int uiOutputPosition;
  unsigned int uiLength;
  unsigned int uiCount;
  HEVENT_T hevNotFull;
  HEVENT_T hevNotEmpty;
  HMUTEX_T hmxMessageQueue;
} MESSAGE_QUEUE_T;

typedef MESSAGE_QUEUE_T * LPMESSAGE_QUEUE_T;

typedef struct shm_struct {
	// stuff from playaud.c
        unsigned int uiGlobalPlayAudioInstance;
        unsigned int bGlobalPlayAudioThreadExit; 
        HTHREAD_T hGlobalPlayAudioThread;
        HMUTEX_T hmxGlobalSendPlayAudio;
        LPMESSAGE_QUEUE_T pGlobalReportMessageQueue;
        LPMESSAGE_QUEUE_T pGlobalPlayAudioMessageQueue;

#ifdef OS_SIXTY_FOUR_BIT
	unsigned int uiGlobalHandleListLength;
	HMUTEX_T hmxGlobalHandleList;
	HPLAY_AUDIO_T * ppGlobalHandleList; 
#endif

} shared_mem_t;

typedef shared_mem_t *pshared_mem_t;


