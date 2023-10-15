/***********************************************************************
 *
 * Copyright (c) 2003 Fonix Corporation or its subsidiaries.
 * All rights reserved.
 *
 ***********************************************************************/

/***********************************************************************
 *
 * File:
 *	Palmconfig_sp.h
 *
 * Description:
 *	Palm specific defines and headers
 *
 *	Version 1.0 	- Initial Revision (12/16/03)
 *
 ***********************************************************************/

#ifndef PALMCONFIG_SP_H_
#define PALMCONFIG_SP_H_


#include <PalmTypes.h>
#include <FileStream.h>//PALM file streaming functions
#include <StringMgr.h> //PALM string functions
//#include <StdIOPalm.h>//PALM stdio functions
#include <MemoryMgr.h>//PALM Memory Functions
#include <MemGlue.h> //PALM MemGluePtrNew function
#include <PalmOS.h>
#include <SysGlue.h>
#include <SoundMgr.h>
#include "Mathlib.h" //PALM extended Math functions
#define OS_PALM

// Stub out the "FILE" type until we support real file IO
typedef	void	FILE;

// We don't support re-direction yet, stdin is always the keyboard and
//  stdout is always the stdio window. 
#define	stdin		((FILE*)0)
#define	stdout		((FILE*)1)
#define	stderr		((FILE*)2)

#define far
//map functions to Palm equivalents
#define atoi StrAToI

//Don't use Metrowerks stdio.h
#ifndef _MSL_STDIO_H
#define _MSL_STDIO_H
#endif

//Don't use Metrowerks stdlib.h
#ifndef _MSL_STDLIB_H
#define _MSL_STDLIB_H
#endif


#ifndef ARM7
#define ARM7
#endif

#ifndef ALLOC_MEMORY
#define ALLOC_MEMORY
#endif

#ifndef BLD_DECTALK_DLL
#define BLD_DECTALK_DLL
#endif

#ifndef ARM7_NOSWI
#define ARM7_NOSWI
#endif

#ifndef OPTIMIZE_FILTER_CODE_BY_LOCATION
#define OPTIMIZE_FILTER_CODE_BY_LOCATION
#endif

#ifndef SPANISH
#define SPANISH
#endif

#ifndef SPANISH_SP
#define SPANISH_SP
#endif


#ifndef LOW_COMPUTE
#define LOW_COMPUTE
#endif

#ifndef LOW_COMPUTE_8K
#define LOW_COMPUTE_8K
#endif

#ifndef NO_ALIGN_8
#define NO_ALIGN_8
#endif

#ifndef NO_INCLUDED_C_FILES
#define NO_INCLUDED_C_FILES
#endif

//Palm is big endian
#ifndef _BIGENDIAN_
#define _BIGENDIAN_
#endif


int toupper(int ch);

#endif /* PALMCONFIG_SP_H_ */