/*H_HEADER_FILE***************************************************************
FILE			: Port.h
DESC			: Port.h for Symbian
TABS			: 3
OWNER			: 
DATE CREATED: 4 April 2005

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/

#ifndef PORT_H
#define PORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "DtFnxStdLib.h"

#define __far
#define _far
#define far
#define FAR
#define huge
#define volatile
#define inline
#define _inline

#ifdef SEPARATE_PROCESSES
#undef SEPARATE_PROCESSES
#endif

#define CONST		const
#define CONSTSTRUCT const
#define CONSTARRAY	const
#define CONSTCONST	const

#ifndef BOOL_DEFINED
#define BOOL_DEFINED
typedef int  BOOL;
#endif

#ifndef SHORT_DEFINED
#define SHORT_DEFINED
typedef short SHORT;
#endif

#ifndef U16_DEFINED
#define U16_DEFINED
typedef unsigned short  U16;
#endif

typedef signed char     int8_t;
typedef signed short    int16_t;
typedef signed long     int32_t;
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned long   uint32_t;
typedef unsigned long   int_fast8_t;

typedef signed char S8;
//typedef signed char int8_t;
typedef unsigned char U8;

#ifndef __CHAR_DEFINED__
typedef unsigned char CHAR;
#define __CHAR_DEFINED__
#endif

//typedef unsigned char uint8_t;
typedef unsigned char BYTE;

typedef short S16;
//typedef short int16_t;
typedef unsigned short DT_PIPE_T;
//typedef unsigned short uint16_t;
typedef unsigned short WORD;

typedef long S32;
//typedef long int32_t;
typedef unsigned long DWORD;
typedef unsigned long U32;
typedef unsigned long UINT;

typedef void * DT_HANDLE;
typedef void * LPVOID;
typedef void * PVOID;
typedef long MMRESULT;

#define TRUE 1
#define FALSE 0

#ifdef UIQ
#pragma mpwc_relax on
#pragma dont_inline on
#define __inline
#endif

#define OP_ResetEvent( pEvent )
#define OP_LockMutex( pMutex )
#define OP_UnlockMutex( pMutex )
#define OP_WaitForEvent( pEvent, uiMilliSeconds )

#include "GlobalDT.h"

#endif