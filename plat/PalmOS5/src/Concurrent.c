/*C_HEADER_FILE****************************************************************
FILE			:	Concurrent.c
DESC			:	Windows specific functions for doing concurrent recognition
				:	on its own thread
TABS			:	4
OWNER			:	fonix
DATE CREATED:	4 September 2002

(C) Copyright 2002 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: $
  $Revision: $

*END_HEADER*******************************************************************/

#include <windows.h>
#ifndef UNDER_CE
#include <process.h>
#endif

#include "Concurrent.h"
#include "WaveList.h"
#include "FNXRecognize.h"

static int				g_numSamples = 0;
static unsigned long	g_hRecogThread = 0;
static HANDLE			g_hWavRecog = NULL;
static HANDLE			g_hWavReset = NULL;
static HANDLE			g_hWavDone = NULL;


/********************************************************
 *                   RecognitionThread
 *
 * PURPOSE: Perform real time recognition on buffers as
 *			they are available
 * INPUTS:  param - pointer to mic data
 * OUTPUTS: NONE
 * RETURN:  
 * NOTES:   
 ********************************************************/
#ifdef UNDER_CE
DWORD WINAPI RecognitionThread(voidPtr param)
#else
void RecognitionThread(voidPtr param)
#endif
{
	int			result;
	BOOL		done = FALSE;
	FTKWavePtr	pWave;
	WaveList	lastWav;
	WaveListPtr	pWavList= &lastWav;
	MicInfoPtr	pMicInfo = (MicInfoPtr)param;

	pWavList->pNext = pMicInfo->pWavListStart;
	while (!done)
	{
		if ((result = WaitForSingleObject(g_hWavRecog, 100)) == WAIT_OBJECT_0)
		{
			FNX_ASSERT(pWavList && pWavList->pNext);
			if (pWavList->pNext)
			{
				pWavList = pWavList->pNext;
				pWave = pWavList->pWave;
				g_numSamples += pWave->nSamples;
				done = pWavList->pNext == (WaveListPtr)-1;
			}
			FNX_ASSERT(pWave);
			pMicInfo->pRecogProc(pMicInfo->pRecogData, pWave, done);
		}
		if ((result = WaitForSingleObject(g_hWavReset, 0)) == WAIT_OBJECT_0)
		{
			int			numRecog = 0;
			RecogTPtr	*ppRecog = (RecogTPtr *)pMicInfo->pRecogData;

			while (ppRecog[numRecog])
			{ 
   				ResetRecognition(ppRecog[numRecog]);
				numRecog++;
			}
			// clear the recognition semaphore
			while (WaitForSingleObject(g_hWavRecog, 0) == WAIT_OBJECT_0)
			{};
			done = TRUE;
		}
	};

	SetEvent(g_hWavDone);

#ifdef UNDER_CE
	return 0;
#endif
}

void ConcurrentInit(MicInfoPtr pMicInfo)
{
	if (pMicInfo->pRecogProc)
	{
		FNX_ASSERT(g_hWavRecog == NULL);
		FNX_ASSERT(g_hWavReset == NULL);
		FNX_ASSERT(g_hWavDone == NULL);

		g_hWavRecog = CreateSemaphore(NULL, 0, 1000, NULL);
		g_hWavReset = CreateEvent(NULL, FALSE, FALSE, NULL);
		g_hWavDone = CreateEvent(NULL, FALSE, FALSE, NULL);
	}
}

void ConcurrentStart(MicInfoPtr pMicInfo)
{
	g_numSamples = 0;
#ifdef UNDER_CE
 	CreateThread(NULL, 10240, RecognitionThread, pMicInfo, 0, &g_hRecogThread);
#else
	g_hRecogThread = _beginthread(RecognitionThread, 10240, pMicInfo);
#endif
}

void ConcurrentReady()
{
	ReleaseSemaphore(g_hWavRecog, 1, NULL);
}

void ConcurrentReset()
{
	int		result;

	FNX_ASSERT(g_hRecogThread);
	if (g_hRecogThread)
	{
		SetEvent(g_hWavReset);
		result = WaitForSingleObject(g_hWavDone, INFINITE);
		FNX_ASSERT(result == WAIT_OBJECT_0);

		g_hRecogThread = g_numSamples = 0;
	}
}

SDWORD ConcurrentFinish(WaveListPtr pLast)
{
	int		result, numSamples = 0;

	if (g_hRecogThread)
	{
		FNX_ASSERT(pLast->pNext == NULL);
		// temporarily set next ptr to indicate last wave so recognition will flush
		pLast->pNext = (WaveListPtr)-1;
		ReleaseSemaphore(g_hWavRecog, 1, NULL);
		result = WaitForSingleObject(g_hWavDone, INFINITE);
		// restore next ptr to NULL
		pLast->pNext = NULL;
		FNX_ASSERT(result == WAIT_OBJECT_0);
		numSamples = g_numSamples;
		g_hRecogThread = g_numSamples = 0;
	}

	// return number of samples processed
	return numSamples;
}

void ConcurrentFree()
{
	if (g_hWavRecog)
	{
		CloseHandle(g_hWavRecog);
		g_hWavRecog = NULL;
	}
	if (g_hWavReset)
	{
		CloseHandle(g_hWavReset);
		g_hWavReset = NULL;
	}
	if (g_hWavDone)
	{
		CloseHandle(g_hWavDone);
		g_hWavDone = NULL;
	}
}

