/*H_HEADER_FILE***************************************************************
FILE        : FnxMachine.h (WIN32 OS/INTEL platform version)
DESC        : Set platform (and processor)-specific definitions.
TABS        : 3
OWNER       : 
DATE CREATED: 

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/
#ifndef MACHINE_H
#define MACHINE_H

#define INTEGER_CORE
#define USE_SEARCH_GRAPH
//#define SCALE_TO_10BIT
//#define NEW_MELBIN_METHOD
//#define SHIFT_IS_FASTER
#ifndef INTEGER_CORE // Ooura FFT has rounding problems on low-volume waves in integer mode.
#  define OOURA_FFT  // But it is a bit faster than the next-fastest FFT, so use it in floating point mod e.
#endif
//#define INTEL_SPL_FFT
#define READ_NIST_FILES
//#define READ_PHONDAT
#define SUPPORT_MULAW // Allow the reading of mulaw RIFF (.wav) and NIST files.

/* If this is not defined, then the Message() routine doesn't display anything. */
//#ifndef DISPLAY_ERROR_MESSAGES
//#  define DISPLAY_ERROR_MESSAGES
//#endif

#include <assert.h>
#ifndef ARM7
#include <io.h>
#endif
//#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Include stdint.h when available.  Until then...
typedef unsigned long  int_fast8_t;
typedef __int64         int64_t;

#if !defined(__MWERKS__)   // probably because I use precompiled headers
  typedef int BOOL; // previously defined in windef.h on Windows
#endif

#ifndef _16BIT
#  define  xhuge
#endif

typedef void xhuge *voidPtr;

#ifndef  FNX_EXPORT
#  define FNX_EXPORT(a,b) __declspec(dllexport) a b
#endif
#define IMPORT(a,b) __declspec(dllimport) a b

#if !defined(_SIZE_T_DEFINED)
   typedef unsigned int size_t;
#  define _SIZE_T_DEFINED
#endif

#define WORDS_LITTLEENDIAN
#define OS_WIN32
//#define FNX_MAX_PATH _MAX_PATH

#define HAVE_STDIO_H
//#define USE_BUILTIN_MIC
//#define INCLUDE_NN_PRUNING
//#define HAVE_AV2001_DLL
//#define USE_WCHAR

/* These two defines are used for memory-mapped files (e.g., in WinCE),
   but probably are not needed for Win32. */
//#define INDEXED_SEARCH_GRAPH
//#define SHARED_SEARCH_GRAPH

/* You should define ALIGN_DATA_16 MMX[integer] or SSE[floating-point] SIMD
   (Only works on Pentium with MMX; not Pentium Pro or below,
   but makes neural network calculations 2-8 times as fast).
   To compile, you'll need "Visual Studio 6 Service Pack 5", 
   and the "processor pack" */
//#define ALIGN_DATA_16 
//#define NO_ALIGNED_MALLOC
//For Pentium 4 or higher with Integer Core you will want to define USE_SSE2 to do an 8 way vecmult.
//#define USE_SSE2 
//For AMD K6 or Athlon, define USE_3DNOW.  Requires an AMD processor pack
//#define USE_3DNOW
//#define USE_ASM_SIMD

#if defined(_DEBUG)
//#define TRACK_MEMORY
//#define TRACK_MEMORY_LEVEL1
//#define TRACK_MEMORY_LEVEL2
#endif

#endif
