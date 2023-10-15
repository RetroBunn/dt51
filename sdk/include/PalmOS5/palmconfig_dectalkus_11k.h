/***********************************************************************
 *
 * Copyright (c) 2003 Fonix Corporation or its subsidiaries.
 * All rights reserved.
 *
 ***********************************************************************/

/***********************************************************************
 *
 * File:
 *	Palmconfig_us.h
 *
 * Description:
 *	Palm specific defines and headers
 *
 *	Version 1.0 	- Initial Revision (12/16/03)
 *
 ***********************************************************************/

#ifndef PALMCONFIG_US_H_
#define PALMCONFIG_US_H_


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

#ifndef ACNA
#define ACNA
#endif

#ifndef ARM7_NOSWI
#define ARM7_NOSWI
#endif

//#ifndef CHEESY_DICT_COMPRESSION
//#define CHEESY_DICT_COMPRESSION
//#endif

#ifndef OPTIMIZE_FILTER_CODE_BY_LOCATION
#define OPTIMIZE_FILTER_CODE_BY_LOCATION
#endif

//#ifndef MULTIPLE_LANGUAGES_LOADED
//#define MULTIPLE_LANGUAGES_LOADED
//#endif

#ifndef ENGLISH
#define ENGLISH
#endif

#ifndef ENGLISH_US
#define ENGLISH_US
#endif

#ifndef NO_ALIGN_8
#define NO_ALIGN_8
#endif

#ifndef NO_INCLUDED_C_FILES
#define NO_INCLUDED_C_FILES
#endif

//#ifndef TUNE_8KHZ_VOICE
//#define TUNE_8KHZ_VOICE
//#endif

//Palm is big endian
#ifndef _BIGENDIAN_
#define _BIGENDIAN_
#endif


int toupper(int ch);

#endif /* PALMCONFIG_US_H_ */