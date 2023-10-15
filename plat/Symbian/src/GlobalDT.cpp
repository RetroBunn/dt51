/*C_HEADER_FILE***************************************************************
FILE			: GlobalDT.c
DESC			: 
TABS			: 4
OWNER			: 
DATE CREATED: 6 Feb 2004

(C) Copyright 2004 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/

#include <e32std.h>
#include <e32uid.h>
#include <e32base.h>
#include <e32std.h>
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
//extern int TextToSpeechStart(char *input, short *buffer, int output_format);

class DT_Thread:public RThread
{
public:
	GlobalDTPtr GetTls()
	{
		return GetDTTlsValue();
	}
};

GlobalDTPtr NewDTTlsValue()
{
	GlobalDTPtr gp;

	gp = new GlobalDT;
	gp->gpDECtalkUserData = NULL;
	gp->Cmd_t = 0;
	gp->Dph_t = 0;
	gp->STphsettar = 0;
	gp->cur_packet_number = 0;
	gp->max_packet_number = 0;
	gp->pDictPath = 0;
	gp->bOutput_queue = false;
	gp->bHaltCalled = false;
	gp->simpleData.phTTS = 0;
	gp->simpleData.g_user_dict = NULL;
	gp->simpleData.g_callback = NULL;
	gp->simpleData.sm_buffer = NULL;
	gp->simpleData.g_usercallback = NULL;
	gp->simpleData.String = NULL;
	gp->simpleData.gReset = 0x000E;		//FULL_ENGINE_RESET defined in simpleapi.h
	gp->vtmData.Vtm_t = 0;
	gp->vtmData.tBuffer = 0;

	gp->queueStruct.speechQueue = new (ELeave) CArrayPtrFlat<short>(10);
	gp->queueStruct.qMutex = NULL;
	gp->queueStruct.speechSmph = NULL;
	gp->queueStruct.bFinished = true;

	gp->langStruct.ch_bSort = 0;

	Dll::SetTls(gp);

	return gp;

}

GlobalDTPtr GetDTTlsValue()
{
	GlobalDTPtr gp = STATIC_CAST(GlobalDTPtr, Dll::Tls());

	return gp;
}

void DeleteDTTlsValue()
{
	GlobalDTPtr gp = STATIC_CAST(GlobalDTPtr, Dll::Tls());
	
	//ResetQueue();
	if (gp)
	{
		FNX_FREE(gp->gpDECtalkUserData);
		gp->gpDECtalkUserData = NULL;
		FNX_FREE(gp->Cmd_t);
		gp->Cmd_t = NULL;

		FNX_FREE(gp->pDictPath);
		gp->pDictPath = NULL;

		FNX_FREE(gp->simpleData.g_user_dict);
		gp->simpleData.g_user_dict = NULL;
		FNX_FREE(gp->simpleData.sm_buffer);
		gp->simpleData.sm_buffer = NULL;
		if(gp->simpleData.String)
		{
			FNX_FREE(gp->simpleData.String);
			gp->simpleData.String = NULL;
		}
		
		CArrayPtrFlat<short>* queue = static_cast<CArrayPtrFlat<short>*>(gp->queueStruct.speechQueue);
		queue->ResetAndDestroy();
		delete queue;
		queue = NULL;

		if(gp->queueStruct.speechSmph)
			((RSemaphore*)gp->queueStruct.speechSmph)->Close();
		if(gp->queueStruct.qMutex)
			((RMutex*)gp->queueStruct.qMutex)->Close();

		delete gp->queueStruct.qMutex;
		delete gp->queueStruct.speechSmph;
		
		delete gp;
		gp = NULL;
	}
}

GlobalDTPtr InitDTGlobals()
{
	GlobalDTPtr	gp;
	gp = NewDTTlsValue();

	return gp;
}

void SetGlobalData(GlobalDTPtr data)
{
	Dll::SetTls(data);
}

GlobalDTPtr GetGlobalDTPtr()
{
	GlobalDTPtr	gpDT = GetDTTlsValue();

	if (gpDT == NULL)
	{
		gpDT = InitDTGlobals();
	}
	return gpDT;
}

#ifdef SYMBIAN_LOGGING
void LogData(char * str, int val)
{
	FILE* file;

	file = fopen("e:\\system\\apps\\speechserver\\log.txt", "a");
	if(file)
	{  
		if(str && val)
			fprintf(file, "%u - %s %d\r\n",  User::TickCount(), str, val);
		else if(val)
			fprintf(file, "%u - %d\r\n", User::TickCount(), val);
		else if(str)
			fprintf(file, "%u - %s\r\n", User::TickCount(),str);
	}
	fclose(file);
}
#endif

#if defined(__cplusplus)
}
#endif
