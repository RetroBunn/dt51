/*C_HEADER_FILE***************************************************************
FILE			: GlobalCommon.c
DESC			: 
TABS			: 4
OWNER			: 
DATE CREATED: August 2004

(C) Copyright 2003 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/

#include "port.h"
#include "GlobalCommon.h"

#if !defined(NO_GLOBALS) && !defined(MULTITHREADED)
static GlobalCommon		commonGlobals;
static GlobalCommonPtr	gpCommon = NULL;
#endif

#ifdef MULTITHREADED
static GlobalMemory		memoryGlobals;
static GlobalMemoryPtr	gmCommon = NULL;
#endif

GlobalCommonPtr InitCommonGlobals()
{
	GlobalCommonPtr	gp;
#if !defined(MULTITHREADED)
	GlobalCommonPtr gm;			// Global Common and Global Memory are same structure
#endif

#if defined(NO_GLOBALS) || defined(MULTITHREADED)
	gp = (void*)NewCommonTlsValue();
#else
	gp = &commonGlobals;
#endif
	gp->pFileMap		= NULL;
	gp->NumMemFiles		= 0;
	gp->globalCommonCount = 0;
	return gp;
}

#ifdef MULTITHREADED
GlobalMemoryPtr InitMemoryGlobals()
#else
GlobalCommonPtr InitMemoryGlobals()
#endif
{
#if defined(MULTITHREADED)
	GlobalMemoryPtr gm;

	gm = &memoryGlobals;
#else 
#if defined(NO_GLOBALS)
	GlobalCommonPtr gm = (void*)NewCommonTlsValue();
	GlobalCommonPtr gp;
#else
	GlobalCommonPtr gm;
	GlobalCommonPtr	gp;

	if (gpCommon)
	{
		gm = gpCommon;
	} else
	{
		gm = &commonGlobals;
	}
#endif // NO_GLOBALS
#endif // MULTITHREADED
#if !defined(MULTITHREADED) // && !defined(NO_GLOBALS)
	gp = gm;					// Global Common and Global Memory are same structure
								// Since same structure, Global Common needs to be initialized
	gp->globalCommonCount = 0;
	gp->pFileMap		= NULL;
	gp->NumMemFiles		= 0;
#endif
	
	return gm;
}

GlobalCommonPtr GetGlobalCommonPtr()
{
#if defined(NO_GLOBALS) || defined(MULTITHREADED)
	GlobalCommonPtr	gpCommon = (void*)GetCommonTlsValue();
#endif
	if (gpCommon == NULL)
	{
		gpCommon = InitCommonGlobals();
	}
	return gpCommon;
}

#ifdef MULTITHREADED
GlobalMemoryPtr GetGlobalMemoryPtr()
{
	if (gmCommon == NULL)
	{
		gmCommon = InitMemoryGlobals();
	}
	return gmCommon;
}
#else
GlobalCommonPtr GetGlobalMemoryPtr()
{
#if defined(NO_GLOBALS)
	GlobalCommonPtr	gpCommon = (void*)GetCommonTlsValue();
#endif

	if (gpCommon == NULL)
	{
		gpCommon = InitMemoryGlobals();
	}
	return gpCommon;
}
#endif

