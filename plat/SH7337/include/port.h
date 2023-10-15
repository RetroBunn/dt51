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
#include "DTFnxStdlib.h"
//#include <math.h>  
//#include <stdlib.h>
#include <string.h>
//#include <limits.h>
//#ifndef ARM7_NOSWI
//#if !defined OS_PALM && !defined CASIO_SH3
//#include <stdio.h>
//#endif
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
//#define WORD	unsigned short
typedef unsigned short                  WORD;
#endif

#define _inline

#define register

//#ifndef FILE
#if defined CASIO_SH3 && defined _BIGENDIAN_
#define FILE void
#endif
//#endif

//typedef void * voidPtr;

//typedef size_t  usize;

//#ifndef __CHAR_DEFINED__
//typedef char                            CHAR;
//#endif

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
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

typedef signed char S8;
typedef unsigned char U8;
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef unsigned long   int_fast8_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef int32_t			LONG;

typedef unsigned long DWORD;
typedef char SBYTE;
typedef unsigned char UBYTE;
typedef int SDWORD;
typedef unsigned short UWORD;
typedef unsigned int UDWORD;
typedef short SWORD;


#define xhuge

//typedef SBYTE  xhuge *SBYTEPTR; /* xhuge should be defined (usually as nothing) in FnxMachine.h */
//typedef SWORD  xhuge *SWORDPTR;
//typedef SDWORD xhuge *SDWORDPTR;
//typedef UWORD  xhuge *UWORDPTR;
//typedef UDWORD xhuge *UDWORDPTR;

// Define floating-point types (or their integer equivalents)
//   and other macros involved with INTEGER_CORE
//typedef  SWORD       CoreType;                  //  this must be SWORD not SDWORD for nnet weight reading
//typedef  SDWORD         SrchType;
//typedef  SDWORD         CalcType;
//#define   log2IntScale   10                      //  Number of bits to shift for scaling
//#define   sqrtIntScale   32                      //  Square root of the int scale.
//#define   IntScale    1024
//#define   HalfIntScale   512
//#define   SCALED_LN_OF_2 726817 // =IntScale*IntScale*ln(2) = 1024 * 1024 * 0.69314718056 = 726817.498
//#define   SCALEUP(X)     ((X) << log2IntScale)
//#ifdef SHIFT_IS_FASTER  // Define this in FnxMachine.h if shifting is faster than division on that platform.
//#define   SCALEDN(X)     (((X)) >> log2IntScale)    
//#define   SCALEDNROUND(X) (((X)+HalfIntScale) >> log2IntScale) // round to nearest value.
//#else
//#define   SCALEDN(X)     (((X)) / IntScale)      //  A right shift isn't faster on some platforms and may have rounding errors
//#define   SCALEDNROUND(X) (((X)+HalfIntScale) / IntScale) // round to nearest value.
//#endif
//#define   LogProbScale   1024

//typedef CoreType xhuge     *CoreTypePtr;
//typedef SrchType xhuge     *SrchTypePtr;
//typedef CalcType xhuge     *CalcTypePtr;

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

/* set bit masks for the possible character types */
#define       CHAR_BIT                8
#define       CHAR_MAX              127
#define       CHAR_MIN           (-128)
#define       SCHAR_MAX             127
#define       SCHAR_MIN          (-128)
#define       UCHAR_MAX             255
#define       SHRT_MAX            32767
#define       SHRT_MIN         (-32768)
#define       USHRT_MAX           65535
//#define       INT_MAX        2147483647
#define       INT_MIN    (-2147483647-1)
#define       UINT_MAX      4294967295u
#define       LONG_MAX       2147483647
#define       LONG_MIN   (-2147483647L-1L)
#define       ULONG_MAX     4294967295u

#if 0
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
#endif

#define FNX_MAX_PATH        260


//#define FNX_PUTC putc
#if defined EPSON_ARM7 || defined MULTIPLE_LANGUAGES_LOADED
#include "ltsnames.h"
#endif

#endif /* _PORT_H */
