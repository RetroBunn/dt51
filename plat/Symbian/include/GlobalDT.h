/*H_HEADER_FILE***************************************************************
FILE			: GlobalDT.h
DESC			: 
TABS			: 3
OWNER			: 
DATE CREATED: 6 Feb 2004

(C) Copyright 2004 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/
//#ifndef	GLOBALDT_H
//#define	GLOBALDT_H

#include "port.h"
#include "kernel.h"

typedef struct 
{
	volatile short* tBuffer;
	volatile int tBufferCount;
	volatile void* Vtm_t;
} vtmiontStruct;

typedef struct
{
	volatile void* phTTS;
	volatile char *g_user_dict;
	volatile short *(*g_callback)(short *,long, void*);
	volatile short *(*g_usercallback)(short *,long, void*);
	volatile short* sm_buffer;
	volatile char* String;
	volatile int gReset;
	volatile int gDTinUse;
} simpleAPIStruct;

typedef struct
{
	volatile void* speechQueue;
	volatile void* qMutex;
	volatile void* qCountMutex;
	volatile void* speechSmph;
	volatile int bufSize;
	volatile unsigned int threadId;
	volatile int bFinished;
} speechQueueStruct;

typedef struct
{
	volatile char ch_bSort;
} languageStruct;

typedef struct
{
	volatile void* gpDECtalkUserData;
	volatile vtmiontStruct vtmData;
	volatile simpleAPIStruct simpleData;
	volatile speechQueueStruct queueStruct;
	volatile languageStruct langStruct;
	volatile void* Cmd_t;
	volatile void* STphsettar;
	volatile void* Dph_t;
	volatile char* pDictPath;
	volatile short cur_packet_number;	//services.c
	volatile short max_packet_number;	//services.c
	volatile struct spc_packet global_spc_pkt[1];	//services.c
	volatile int bOutput_queue;
	volatile int bHaltCalled;

} GlobalDT, *GlobalDTPtr;

#if defined(__cplusplus)
extern "C" {
#endif

GlobalDTPtr InitDTGlobals();
GlobalDTPtr NewDTTlsValue();

FNX_EXPORT(GlobalDTPtr, GetGlobalDTPtr());
FNX_EXPORT(void, SetGlobalData(GlobalDTPtr data));
FNX_EXPORT(GlobalDTPtr, GetDTTlsValue());
FNX_EXPORT(void, DeleteDTTlsValue());

#ifdef SYMBIAN_LOGGING
void LogData(char * str, int val);
#endif
#if defined(__cplusplus)
}
#endif

//#endif
