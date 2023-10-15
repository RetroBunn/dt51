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
 *    DECtalk porting specific header file - FOR WINDOWS 95 Code
 *
 ***********************************************************************
 *    Revision History:
 *
 *  Rev Name    Date        Description
 *  --- -----   ----------- --------------------------------------------
 *  001	GL		04/21/1997	BATS#357  Add the code for __osf__ build 
 *  002 MGS		09/08/1997	Made change for osf build
 *				11/13/1997	bats423: correct LP_AUDIO_HANDLE_T (aug97)
 *  003 GL 		05/04/1998	Add dectalkf.h here to make sure every file catch
 *                          the setup.
 *  004 ETT		10/05/1998  Added Linux code.
 *  005	MGS		07/14/2000	Sapi 5 additions
 *  006	CAB		01/19/2001	Fixed copyright
 *  007	MGS		02/28/2001	Merged in base changes needed for ACCESS32 merge
 *  008	MGS		05/09/2001	Some VxWorks porting BATS#972
 *  009	MGS		05/18/2001	More VxWorks porting
 *  010	MGS		06/19/2001	Solaris Port BATS#972
 *  011	MGS		04/11/2002	ARM7 port
 *************************************************************************/

#ifndef _PORT_H
#define _PORT_H

#include "dectalkf.h"

/*
 ************************************************************************
 *  WINDOWS/NT
 */

#ifndef _WINDOW_H
#define _WINDOW_H
#include <windows.h>
#endif // _WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include  <malloc.h>
#include <mmreg.h>
#include <mmsystem.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <direct.h>
#include <process.h>
#include <stddef.h>
#include <tchar.h>

#include "mmalloc.h"

/* mimic stdint.h */
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
typedef signed __int8 int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#endif
 
#if defined WIN32 && defined PRINTFDEBUG
#include "dbgwins.h"
#endif
/*
 * fake out some MSDOS stuff
 */

#define __far
#define _far
#define far
#define near
#define huge
#define volatile

typedef void * voidPtr;
typedef size_t  usize;

#define FNX_EXPORT_C
#ifndef  FNX_EXPORT
#  define FNX_EXPORT(a,b) __declspec(dllexport) a b
#endif
#define IMPORT(a,b) __declspec(dllimport) a b

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
#define FAR far

//#if !defined BOOL_DEFINED
//#define BOOL_DEFINED
typedef int  BOOL;
//#endif

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

typedef unsigned short DT_PIPE_T;
typedef int32_t S32;
typedef uint32_t U32;
typedef int16_t S16;
typedef uint16_t U16;
typedef int8_t S8;
typedef uint8_t U8;
typedef uint64_t QWORD, * PQWORD; //tek 04aug97 sapi fixes

typedef signed long SDWORD;
typedef unsigned long UDWORD;

typedef HANDLE DT_HANDLE;
typedef  DT_HANDLE  HTHREAD_T;
typedef  DT_HANDLE  HEVENT_T;
typedef  CRITICAL_SECTION  MUTEX_T;
typedef  MUTEX_T *  HMUTEX_T;

#define FNX_MAX_PATH        260

#include "DTFnxStdlib.h"

#if !(defined OLEDECTALK) && !(defined SAPI5DECTALK)
#include "playaudd.h"
typedef PLAY_AUDIO_T * 	LPAUDIO_HANDLE_T;
#endif //OLEDECTALK


/* SWAP_dd_eeeeeee */ 
/* dd is 16 or 32 bits */
/* eeeeee is 
   BIG for big-endian numbers 
   LITTLE for little-endian numbers */
/* ex on intel SWAP_32_LITTLE(x) does nothing
   but on sparc SWAP_32_LITTLE(x) swaps the bytes */

#ifndef _BIGENDIAN_
#define SWAP_16_BIG(x) (((((U16)(x))&0xff00)>>8) | \
                        ((((U16)(x))&0x00ff)<<8))
#define SWAP_16_LITTLE(x) (x)
#define SWAP_32_BIG(x) (((((U32)(x))&0xff000000)>>24) | \
                        ((((U32)(x))&0x00ff0000)>>8) | \
                        ((((U32)(x))&0x0000ff00)<<8) | \
                        ((((U32)(x))&0x000000ff)<<24))
#define SWAP_32_LITTLE(x) (x)
#else
#define SWAP_16_LITTLE(x) (((((U16)(x))&0xff00)>>8) | \
                           ((((U16)(x))&0x00ff)<<8))
#define SWAP_16_BIG(x) (x)
#define SWAP_32_LITTLE(x) (((((U32)(x))&0xff000000)>>24) | \
                           ((((U32)(x))&0x00ff0000)>>8) | \
                           ((((U32)(x))&0x0000ff00)<<8) | \
                           ((((U32)(x))&0x000000ff)<<24))
#define SWAP_32_BIG(x) (x)
#endif

#ifndef WideStringtoAsciiString
#define WideStringtoAsciiString(a, b, c)	wcstombs(a, b, c)
#endif


#ifndef SUN_ULAW
#define SUN_ULAW        1
#endif
#ifndef SUN_LIN_8
#define SUN_LIN_8       2
#endif
#ifndef SUN_LIN_16
#define SUN_LIN_16      3
#endif

#endif /* _PORT_H */
