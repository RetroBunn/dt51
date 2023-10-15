/*C_HEADER_FILE***************************************************************
FILE			: DTSymbianThreading.cpp
DESC			: 
TABS			: 4
OWNER			: 
DATE CREATED: 29 Mar 2006

(C) Copyright 2006 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/

#include <e32std.h>
#include <e32uid.h>
#include <e32base.h>
#include "DTSymbianThreading.h"
//#include "GlobalDT.h"
#include "SimpleApi.h"
#include "FonixTtsDtSimple.h"

_LIT(KThreadName, "DT_Thread");
_LIT(KFindThread, "DT_Thread*");
static const TUint KMaxHeapSize = 0x10000;  // 64K
_LIT(KDateString4,"%-B%0%J%1%T%2%S%.%*C4%3%");


#if defined(__cplusplus)
extern "C" {
#endif
extern void*	epoccalloc ( size_t nel, size_t size );
extern int TextToSpeechStart(char *input, short *buffer, int output_format);

typedef struct
{
	GlobalDTPtr gp;
	char* str;
}ThreadStruct;

class DT_Thread:public RThread
{
public:
	GlobalDTPtr GetTls()
	{
		return GetDTTlsValue();
	}
};

GlobalDTPtr GetGlobalDTPtrFromThread(unsigned int threadId)
{
	DT_Thread thread;
	TThreadId id(threadId);

	if(threadId >= 0)
	{
		int error = thread.Open(id);
		if(KErrNone == error)
		{
			GlobalDTPtr	gpDT = thread.GetTls();
			Dll::SetTls(gpDT);
			thread.Close();
			return gpDT;
		}
		else
			return NULL;
	}
	else
		return GetGlobalDTPtr();
}

int LockQueue()
{
	GlobalDTPtr gp = GetGlobalDTPtr();
	RMutex* mut = static_cast<RMutex*>(gp->queueStruct.qMutex);

	if(mut)
		mut->Wait();
	return 0;
}

int UnlockQueue()
{
	GlobalDTPtr gp = GetGlobalDTPtr();
	RMutex* mut = static_cast<RMutex*>(gp->queueStruct.qMutex);
	
	if(mut)
		mut->Signal();
	return 0;
}

short* AddToSpeechQueue(short* data, int length)
{
	GlobalDTPtr gp = GetGlobalDTPtr();
	CArrayPtrFlat<short>* queue = static_cast<CArrayPtrFlat<short>*>(gp->queueStruct.speechQueue);
	RSemaphore* sem = static_cast<RSemaphore*>(gp->queueStruct.speechSmph);
	FTTSDTUDATA_T* gpDECtalkUserData = (FTTSDTUDATA_TAG *)gp->gpDECtalkUserData;
	
	if(queue)
	{
		LockQueue();
		queue->AppendL(data, 1);
		UnlockQueue();
	}
	if(gp->queueStruct.bufSize <= GetQueueCount() * length)
	{
		if(sem)
		{
			sem->Wait();
		}
	}
	short* buffer = (short*)calloc(1, length*sizeof(short));
	gpDECtalkUserData->gDECtalkBufPtr = buffer;
	return buffer;
}

void SignalThread()
{
	GlobalDTPtr gp = GetGlobalDTPtr();
	RSemaphore* sem = static_cast<RSemaphore*>(gp->queueStruct.speechSmph);

	if(sem) 
		sem->Signal();
}

void ResetQueue()
{
	GlobalDTPtr gp = GetGlobalDTPtr();
	CArrayPtrFlat<short>* queue = static_cast<CArrayPtrFlat<short>*>(gp->queueStruct.speechQueue);

	if(queue)
	{	
		int count = 0;
		LockQueue();
		count = queue->Count();
		for(int i = 0; i < count; i++)
		{
			short* temp = queue->At(0);
			queue->Delete(0);
			FNX_FREE(temp);
		}
		queue->Reset();
		UnlockQueue();
	}
}

int GetSpeechData(short* buffer, int buflength )
{
	short* data = NULL;
	GlobalDTPtr gp = GetGlobalDTPtr();
	CArrayPtrFlat<short>* queue = static_cast<CArrayPtrFlat<short>*>(gp->queueStruct.speechQueue);
	FTTSDTUDATA_T* gpDECtalkUserData = (FTTSDTUDATA_TAG *)gp->gpDECtalkUserData;
	const int pktSize = gpDECtalkUserData->gDECtalkPktSize[gpDECtalkUserData->gDECtalkFlags];
	LPTTS_HANDLE_T phTTS = (LPTTS_HANDLE_T)gp->simpleData.phTTS;
	int total_copied = 0;

	while(!phTTS->pKernelShareData->halting && total_copied <= buflength - (pktSize))
	{
		if(GetQueueCount() == 0 && gp->queueStruct.bFinished)
			break;

		LockQueue();
		if(queue && queue->Count() > 0)
		{
			data = queue->At(0);
			queue->Delete(0);
		}
		UnlockQueue();

		if(data)
		{
			memcpy(buffer+total_copied, data, pktSize*2);
			total_copied += pktSize;
			FNX_FREE(data);
			data = NULL;
			//free_counter++;
		}
		else if(total_copied != 0)
			break;

	} 

	if(!gp->queueStruct.bFinished)
	{
		SignalThread();
	}

	return total_copied;
}

int GenerateTTS(TAny *aPtr)
{
	int retval = ERR_NOERROR;
	GlobalDTPtr gp = static_cast<GlobalDTPtr>(aPtr);
	Dll::SetTls(gp);

	FTTSDTUDATA_T* gpDECtalkUserData = (FTTSDTUDATA_TAG *)gp->gpDECtalkUserData;

	ResetQueue();
	retval = TextToSpeechStart( gp->simpleData.String , gpDECtalkUserData->gDECtalkBufPtr, gpDECtalkUserData->gDECtalkFlags);	
	gp->queueStruct.bFinished = true;

	if(gpDECtalkUserData->gDECtalkBufPtr)
	{	FNX_FREE(gpDECtalkUserData->gDECtalkBufPtr);
		gpDECtalkUserData->gDECtalkBufPtr = NULL;
	}
	Dll::SetTls(NULL);
	User::Exit(0);
	return retval;
}

void StartThread(char *String)
{
	GlobalDTPtr gp = GetGlobalDTPtr();
	RSemaphore* sem = static_cast<RSemaphore*>(gp->queueStruct.speechSmph);
	RMutex* mut1 = static_cast<RMutex*>(gp->queueStruct.qMutex);
	TBuf16<50> iText;

	int ret = KErrNone;

	TTime time;
	time.HomeTime();
	time.FormatL(iText,KDateString4);
	iText.Insert(0, KThreadName);
	
	if(gp->simpleData.String)
		FNX_FREE(gp->simpleData.String);

	gp->simpleData.String = strdup(String);
	gp->queueStruct.bFinished = false;

	if(sem)
		sem->Close();
	if(mut1)
		mut1->Close();

	mut1 = new (ELeave) RMutex;
	sem = new (ELeave) RSemaphore;

	mut1->CreateLocal();
	sem->CreateLocal(0);

	gp->queueStruct.qMutex = mut1;
	gp->queueStruct.speechSmph = sem;

	RThread thread;
	ret = thread.Create( iText,	GenerateTTS, KDefaultStackSize, NULL, gp);
	gp->queueStruct.threadId = (TUint)thread.Id();
	if(ret == KErrNone)
	{
		thread.SetPriority(EPriorityMuchMore);
		thread.Resume();
		thread.Close();
	}
}

int GetQueueCount()
{
	GlobalDTPtr gp = GetGlobalDTPtr();
	CArrayPtrFlat<short>* queue = static_cast<CArrayPtrFlat<short>*>(gp->queueStruct.speechQueue);
	int count = 0;

	if(queue)
	{
		LockQueue();
		count = queue->Count();
		UnlockQueue();
	}
	return count;
}

void ResumeThread()
{
	GlobalDTPtr gp = GetGlobalDTPtr();
	RThread thread;
	thread.Open(gp->queueStruct.threadId);
	thread.Resume();
	thread.Close();
}

void* GetThreadData()
{
	return GetGlobalDTPtr();
}

#if defined(__cplusplus)
}
#endif
