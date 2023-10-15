/*C_HEADER_FILE****************************************************************
FILE			:	ThreadSync.c
DESC			:	
TABS			:	4
OWNER			:	fonix
DATE CREATED:	6 March 2003

(C) Copyright 2003 All rights reserved.
This is an unpublished work, and is confidential and proprietary:
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of
fonix corporation in each and every instance.

  $Date: $
  $Revision: $

*END_HEADER*******************************************************************/
//#include <windows.h>
#include "SystemMgr.h"

#ifdef UNDER_CE
#define	THREAD_RETURN	DWORD WINAPI
#else
//#include <process.h>

#define	THREAD_RETURN	void
#endif

#include "ThreadSync.h"

void RecognitionThread(void *);

//CRITICAL_SECTION	g_CriticalSection;

THREAD_RETURN RecogThread(void *pGlobals)
{
	RecognitionThread(pGlobals);
}

void LockSyncObject()
{
//	EnterCriticalSection(&g_CriticalSection);
}

void UnlockSyncObject()
{
//	LeaveCriticalSection(&g_CriticalSection);
}

void InitSyncObject()
{
//	InitializeCriticalSection(&g_CriticalSection);
}

void DestroySyncObject()
{
//	DeleteCriticalSection(&g_CriticalSection);
}

int StartThread(void *pGlobals)
{
#ifdef UNDER_CE
 	return CreateThread(NULL, 10240, RecognitionThread, pGlobals, 0, &g_hRecogThread);
#else
//	return _beginthread(RecognitionThread, 10240, pGlobals);
#endif
}

void Delay(int sTime)
{
	SysTaskDelay(sTime);
//	Sleep(sTime);
}

