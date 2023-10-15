/************************************************************************
 *
 *                           Copyright ©
 *	  Copyright © 2000-2001 Force Computers Inc., a Solectron company. All rights reserved.
 *    © Digital Equipment Corporation 1995. All rights reserved.
 *
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Force Computers Incorporated and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Force or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:        port.h
 *    Author:
 *    Creation Date:
 *
 *    Functionality:
 *    DECtalk porting specific header file - FOR ARM7
 *
 *************************************************************************/

#ifndef _PORT_H
#define _PORT_H

/*
 ************************************************************************
 *  ARM7TDMI
 */
#include "dectalkf.h"
#include <math.h>  
// we have stdio.h in two places - do we just need the ifdef? 
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DTFnxStdlib.h"
//#ifndef ARM7_NOSWI
#if !defined CASIO_SH3 && !defined _BIGENDIAN_
#include <stdio.h>
#endif
//#endif

#define OP_ResetEvent( pEvent )
#define OP_LockMutex( pMutex )
#define OP_UnlockMutex( pMutex )
#define OP_WaitForEvent( pEvent, uiMilliSeconds )

#define __far
#define _far
#define far
#define FAR
#define huge
#define volatile

#ifdef SEPARATE_PROCESSES
#undef SEPARATE_PROCESSES
#endif

//define CONSTSTRUCT as "const" if your platform needs it
//in front of a struct declaration else define it as nothing
#define CONSTSTRUCT const
//define CONSTCONST as "const" if your platform can declare a const const array
//else define it as nothing
#define CONSTCONST const
#define CONSTARRAY const
#define CONST const 
#define INT_MAX 2000000000
#define __cdecl

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef EOS
#define EOS	0               /* End Of String */
#endif

#ifndef BYTE
#define BYTE	unsigned char  /* de 0 a 255 */
#endif

#ifndef WORD_DEFINED
#define WORD_DEFINED
#define WORD	unsigned short
#endif

#define _inline

#define register

#ifndef _FILE_DEFINED
#define FILE void
#define _FILE_DEFINED
#endif

typedef unsigned int size_t;

#ifndef __CHAR_DEFINED__
#define __CHAR_DEFINED__
typedef char CHAR;
#endif

#ifndef BOOL_DEFINED
#define BOOL_DEFINED
typedef int BOOL;
#endif
#ifndef UINT_DEFINED
#define UINT_DEFINED
typedef unsigned int UINT;
#endif
typedef unsigned short DT_PIPE_T;
typedef long S32;
typedef long LONG;
typedef unsigned long U32;
typedef short S16;
#ifdef FRENCH
typedef unsigned short SHORT;
#else
typedef short SHORT;
#endif
#ifndef U16_DEFINED
#define U16_DEFINED
typedef unsigned short U16;
#endif

typedef signed char S8;
typedef unsigned char U8;
typedef unsigned long DWORD;
typedef signed long SDWORD;

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef unsigned long   int_fast8_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#define EOF     (-1)
typedef void * DT_HANDLE;
typedef void * LPVOID;
typedef void * PVOID;
typedef long MMRESULT;
#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FNX_EXPORT
#define FNX_EXPORT(a,b) extern a b
#endif

#define FnxCallType

//typedef  DT_HANDLE  HTHREAD_T;
//typedef  DT_HANDLE  HEVENT_T;
//typedef  CRITICAL_SECTION  MUTEX_T;
//typedef  MUTEX_T *  HMUTEX_T;

#define FNX_MAX_PATH        260

#ifdef CASIO_SH3
/* set bit masks for the possible character types */

#define _UPPER          0x1     /* upper case letter */
#define _LOWER          0x2     /* lower case letter */
#define _DIGIT          0x4     /* digit[0-9] */
#define _SPACE          0x8     /* tab, carriage return, newline, */
                                /* vertical tab or form feed */
#define _PUNCT          0x10    /* punctuation character */
#define _CONTROL        0x20    /* control character */
#define _BLANK          0x40    /* space char */
#define _HEX            0x80    /* hexadecimal digit */

#define _LEADBYTE       0x8000                  /* multibyte leadbyte */
#define _ALPHA          (0x0100|_UPPER|_LOWER)  /* alphabetic character */
#define       LONG_MAX       2147483647
#define       LONG_MIN   (-2147483647L-1L)
#endif //CASIO_SH3

//#define FNX_PUTC putc
#if defined EPSON_ARM7 || defined MULTIPLE_LANGUAGES_LOADED
#include "ltsnames.h"
#endif

#endif /* _PORT_H */
