/*H_HEADER_FILE***************************************************************
FILE			: GlobalCommon.h
DESC			: 
TABS			: 3
OWNER			: 
DATE CREATED: 3 March 2003

(C) Copyright 2003 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/
#ifndef	GLOBALCOMMON_H
#define	GLOBALCOMMON_H

#include "port.h"
#ifdef ARM7
#include "FonixTtsDtSimple.h"
#endif

typedef struct
{
	// from memfileio.c
	int					NumMemFiles;	// initialize to 0;
	FnxMemFileMapping	*pFileMap;		// initialize to NULL;

	int					globalCommonCount;
#ifdef MULTITHREADED
} GlobalCommon, *GlobalCommonPtr;

typedef struct
{
#endif

#ifdef MULTITHREADED
} GlobalMemory, *GlobalMemoryPtr;
#else
} GlobalCommon, *GlobalCommonPtr;
#endif

#if defined(__cplusplus)
extern "C" {
#endif

GlobalCommonPtr InitCommonGlobals();
FNX_EXPORT(GlobalCommonPtr, GetGlobalCommonPtr() );

#if defined(MULTITHREADED)
GlobalCommonPtr NewCommonTlsValue();
GlobalCommonPtr GetCommonTlsValue();
FNX_EXPORT(void,  IncrementCommonTlsCount() );
void DecrementCommonTlsCount();

GlobalMemoryPtr InitMemoryGlobals();
GlobalMemoryPtr GetGlobalMemoryPtr();
#else
GlobalCommonPtr InitMemoryGlobals();
#endif

#if defined(OS_SYMBIAN) || defined(MULTITHREADED)
FNX_EXPORT( void,	 DeleteCommonTlsValue() );
#endif
#ifdef MULTITHREADED
FNX_EXPORT(void, InitTlsCriticalSection() );
#endif

#if defined(__cplusplus)
}
#endif

#endif
