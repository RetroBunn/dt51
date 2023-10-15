/*H_HEADER_FILE***************************************************************
FILE        : FnxMachine.h (Epson S1C33 platform version)
DESC        : Set platform (and processor)-specific definitions.
TABS        : 4
OWNER       : 
DATE CREATED: 

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/23/04 2:30p $
  $Revision: 4 $

*END_HEADER******************************************************************/
#ifndef MACHINE_H
#define MACHINE_H

#define INTEGER_CORE
#define USE_SEARCH_GRAPH
#define NO_SYSFILE_WRITES
//#define SCALE_TO_10BIT
//#define NEW_MELBIN_METHOD
#define SHIFT_IS_FASTER
#define POINTER_ACCESS_FASTER
//#define READ_NIST_FILES
//#define READ_PHONDAT
//#define SUPPORT_MULAW // Default is to support mulaw data under Win32.  Turn this off to make code slightly smaller.
#define CONCURRENT_SINGLE_THREADED
#define SMALL_TTS
//#define MIC_DATA_CENTER	512
//#define OOURA_FFT
#define FONIX_ALLOW_INTERNAL_FUNCTIONS
//#define NOLETTER2WORD

/* If this is not defined, then the Message() routine doesn't display anything. */
//#ifndef DISPLAY_ERROR_MESSAGES
//#  define DISPLAY_ERROR_MESSAGES
//#endif

//#define FNX_VECTOR_MULTIPLY(wp, vp, iters) MAC32(iters, wp, vp)
//#define WORDS_BIGENDIAN
//#define USE_WCHAR
//#define AUDIO_OUT_MAKE_11K
//#define FNX_LEAN_AND_MEAN

//#include <assert.h>
//#include <io.h>
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//#include <time.h>
//#include <stdlib.h>


// By including stdint.h and/or defining the ones that are 
// left out, define int8_t through int_fast8_t listed below.
//#include <stdint.h>
//typedef signed char     int8_t;
//typedef signed short	int16_t;
//typedef signed long		int32_t;	
//typedef unsigned char	uint8_t;
//typedef unsigned short	uint16_t;
//typedef unsigned long	uint32_t;	
//typedef unsigned long   int_fast8_t;

//typedef int BOOL; // previously defined in windef.h on Windows
//#define BOOL int

#ifndef __CHAR_DEFINED__
typedef char                            CHAR;
#endif

#define xhuge 
typedef void *voidPtr;

#define FNX_EXPORT_C
#ifndef  FNX_EXPORT
#  define FNX_EXPORT(a,b) a b
#endif
#define IMPORT(a,b) a b

//#if !defined(_SIZE_T_DEFINED)
//   typedef unsigned long size_t;
//#  define _SIZE_T_DEFINED
//#endif

#define WORDS_LITTLEENDIAN
//#define FNX_MAX_PATH 260

//#define HAVE_STDIO_H
//#define USE_MEM_FILEIO

/* These two defines are used for memory-mapped files (e.g., in WinCE),
   but probably are not needed for Win32. */
//#define INDEXED_SEARCH_GRAPH
//#define SHARED_SEARCH_GRAPH

#if defined(_DEBUG)
//#define TRACK_MEMORY
//#define TRACK_MEMORY_LEVEL1
//#define TRACK_MEMORY_LEVEL2
#endif

// TTS defines

#define FNX_EXPORT_DYN(a,b)	a b
#define FNX_TYPE(a,b,c)     typedef a (__stdcall * Type##b) c
#define FNX_EXPORT_DYN_TYPE(a,b,c) FNX_EXPORT_DYN(a,b) c;\
                                   FNX_TYPE(a, b, c)

#define FNX_IMPORT_DATA(a,b)  extern a b
#define FNX_EXPORT_DATA(a)	a

//#define TTS_DECOMP_16BIT
#define _NOPOSTFILTER_



//#define strstr mystrstr	//work around til get all strstr's out of the common code
//#define min(a,b) ((a<b)?a:b)
//#define max(a,b) ((a>b)?a:b)

#define INIT_INTERRUPTS
#define HALT_INTERRUPTS 
#define START_INTERRUPTS 

#define DEF_FRAME_SIZE		10
#define MINNBEST			1					// Also default for all Nodes except ALPHA NODES
#define MAXNBEST			10
#define DEFALPHANBEST		10
#define MAXALPHANBEST		10
#define MINALPHANVARIATIONS	1
#define DEFALPHANVARIATIONS	10
#define MAXALPHANVARIATIONS	10

#endif
