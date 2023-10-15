#ifndef MACHINE_H
#define MACHINE_H

//#include <assert.h>
#include "assert.h"
//#include <io.h>
//#include "io.h"
//#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define __cdecl

typedef unsigned long	fpos_t;

// By including stdint.h and/or defining the ones that are 
// left out, define int8_t through int_fast8_t listed below.
//#include <stdint.h>
typedef signed char     int8_t;
typedef signed short    int16_t;
typedef signed long     int32_t;
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned long   uint32_t;
typedef unsigned long   int_fast8_t;

#ifndef FAR
#   define FAR
#endif

#ifndef NEAR
#define NEAR
#endif

#ifndef VOID
#define VOID void
#endif


//typedef HANDLE HDRVR;

typedef unsigned char                   BYTE;
typedef unsigned short                  WORD;
typedef unsigned long                   DWORD;
typedef unsigned int                    UINT;
typedef int                             BOOL;
typedef unsigned int					UDWORD;
typedef unsigned char					UBYTE;
typedef unsigned short                  WCHAR;
typedef unsigned long					ULONG;

//added for Symbian 6.1
typedef unsigned char		UCHAR;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL NEAR           *PBOOL;
typedef BOOL FAR            *LPBOOL;
typedef BYTE NEAR           *PBYTE;
typedef BYTE FAR            *LPBYTE;
typedef int NEAR            *PINT;
typedef int FAR             *LPINT;
typedef WORD NEAR           *PWORD;
typedef WORD FAR            *LPWORD;
typedef long FAR            *LPLONG;
typedef DWORD NEAR          *PDWORD;
typedef DWORD FAR           *LPDWORD;
typedef void FAR            *LPVOID;
typedef const void FAR      *LPCVOID;


#ifndef __CHAR_DEFINED__
typedef char                            CHAR;
#endif

#ifdef UNICODE
typedef WCHAR                           TCHAR;
#else
typedef char                            TCHAR;
#endif

typedef long LONG;

typedef WCHAR FAR *                     LPWSTR;
typedef const WCHAR FAR *               LPCWSTR;
typedef CHAR FAR *                      LPSTR;
typedef const CHAR FAR *                LPCSTR;
typedef TCHAR FAR *                     LPTSTR;
typedef const TCHAR FAR *               LPCTSTR;
typedef DWORD                           LCID;
typedef const void FAR *                LPCVOID;
typedef LONG LRESULT;
typedef void * voidPtr;

//#ifndef size_t
//typedef unsigned int size_t;
//#endif

#		ifndef WINAPI
#			define  WINAPI
#		endif

#ifndef FNX_IMPORT
#define FNX_IMPORT(a,b)     __declspec(dllimport) a b
#endif

#ifndef FNX_EXPORT
//added for ccb40
//#define FNX_EXPORT(a,b) a b
#define FNX_EXPORT(a,b)     __declspec(dllexport) a b
#endif

#ifndef FNX_EXPORT_C
//#define FNX_EXPORT_C     EXPORT_C
#define FNX_EXPORT_C     
#endif

//#define FNX_EXPORT_DYN(a,b)	__declspec(dllexport) a __cdecl b
#define FNX_EXPORT_DYN(a,b) a b
#define FNX_TYPE(a,b,c)     typedef a (__cdecl* Type##b) c
//#define FNX_EXPORT_DYN_TYPE(a,b,c) FNX_EXPORT_DYN(a,b) c;\
//                                   FNX_TYPE(a, b, c)
#define FNX_EXPORT_DYN_TYPE(a,b,c) a b c

#define FNX_MAX_PATH        260

#ifdef _LIB		// building static libs
	#ifdef __cplusplus
		#define FNX_IMPORT_DATA(a,b)  extern "C" a b
	#else
		#define FNX_IMPORT_DATA(a,b)  extern a b
	#endif
	#define FNX_EXPORT_DATA(a)	a
#else  // _LIB
	#define FNX_IMPORT_DATA(a,b)  __declspec(dllimport) a b
	#define FNX_EXPORT_DATA(a)    __declspec(dllexport) a
#endif  // _LIB

#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)

#define OS_PALM //added for PALM port
//#define STDIO_PALM_NATIVE_NAMES_ONLY //PALM Stdio
#define xhuge

#define NOLETTER2WORD
////Optimized Vector Multiply
//#define USE_XSCALE_VECTOR_MULTIPLY
//#define SCALED_DOT_PRODUCT
//#ifdef USE_XSCALE_VECTOR_MULTIPLY	// this define was added to a unique project since it is armsa1110-specific
//	// Vector Multiply
//	#define FNX_VECTOR_MULTIPLY(a,b,c) ArmXscaleVectorMultiply(a,b,c)
//    int ArmXscaleVectorMultiply( short * wp, short * vp, int iters );
//#endif

//Memory Manager defines
#if defined(__cplusplus)
extern "C" {
#endif

FNX_EXPORT(void *, fnxrealloc(void *ptr, UInt32 size) );
FNX_EXPORT(void *, fnxmalloc(UInt32 size));
FNX_EXPORT(void, fnxfree(void *ptr));

#if defined(__cplusplus)
}
#endif


#define malloc fnxmalloc
#define realloc fnxrealloc
#define free fnxfree
//#define strtok fnxstrtok

// ASR defines
#define INTEGER_CORE
//#define HAVE_STDIO_H  //PALM doesn't have stdio
#define SHIFT_IS_FASTER
#define POINTER_ACCESS_FASTER
//#define WORDS_LITTLEENDIAN
#define WORDS_BIGENDIAN
#define OOURA_FFT //commented this out for 4.0
#define USE_SEARCH_GRAPH
#define NO_EMB_MEM_MANAGER //Palm uses its own memory manager calls
//#define NO_GLOBALS //Palm can use Globals
//#define NO_SYSFILE_WRITES //Palm can write to files

// ASR & TTS defines
//#define EVAL_BOMB_JWR		// define "Just-Work-Right" only if OS_WIN32 is true and UNDER_CE is false
//#define EVAL_BOMB_JWR_NAG	// define "Just-Work-Right" 'NAG' mode only if OS_WIN32 is true and UNDER_CE is false
#define _NOPOSTFILTER_
#define USE_COMPRESSED_DICTIONARIES
#define INIT_INTERRUPTS
#define HALT_INTERRUPTS
#define START_INTERRUPTS

//Small vocab TTS define for ccb31
#define SMALL_TTS


//#define FNX_LEAN_AND_MEAN

//This is for ccb40
#define FONIX_ALLOW_INTERNAL_FUNCTIONS

//Added for Symbian 6.1
#define NO_MLE_ENGINE
//#define NO_DT_ENGINE
#define NO_HDT_ENGINE
#define _LIB //Using Static libs
//#define EMACHINE //needed to bypass #defines in lvconfig.h???????

//#define USE_MEM_FILEIO  // added for 3.0
//#define DISPLAY_ERROR_MESSAGES
//#define FNX_VECTOR_MULTIPLY(a,b,c) myvm(a,b,c)
//#define TTS_DECOMP_16BIT

//#define USE_WCHAR
//#define AUDIO_OUT_MAKE_11K

//////////////////////////////////
// USA English TTS Fonix Options

//#define FLAT_DIR_STRUCTURE
//#define CUP28PROJECT

/* Additional character sets */
//#define	SUPPORT_UNICODE

/* Input text extensions */
#define SUPPORT_CONTROLTAGS	// uncommented on 04-23-2002

/* Input text extensions */
//#define SUPPORT_SAPI

/* Poly-syllable system */
#define SUPPORT_POLYSYLLABLES

/* Signal Processing (floating point only) */
//#define SUPPORT_SHIFTVOICE

/* Error log file */
//#define SUPPORT_ERRORLOG

/* Dependencies to FAAST-For-Server utilities */
//#define SUPPORT_FAAST_SERVER

/* Utility functions used by userdict/sapi/etc. */
//#define SUPPORT_LVTOOLS

/* PSOLA Stress shifting */
/*#define SUPPORT_PSOLA */
/*#define SUPPORT_PSOLA_SMOOTHING */
/*#define SUPPORT_SPACIALIZATION */

/* Language Processing */
#define SUPPORT_LANGMODULE_LARGE
/*#define SUPPORT_LANGMODULE_SMALL */
/*#define SUPPORT_LANGMODULE_NONE */

/* Text Normalization */
#define SUPPORT_NORMMODULE_LARGE
/*#define SUPPORT_NORMMODULE_SMALL */
/*#define SUPPORT_NORMMODULE_NONE */

/* Data storage and/or Memory usage */
#define SUPPORT_SNDHASH_FROMFILE
/*#define SUPPORT_SNDHASH_FROMMEM */
#define SUPPORT_SNDHASH_CACHE
#define SUPPORT_SNDDATA_FROMFILE
/*#define SUPPORT_SNDDATA_FROMMEM */
/*#define SUPPORT_SNDDATA_CACHE */
#define SUPPORT_DICTHASH_FROMFILE
/*#define SUPPORT_DICTHASH_FROMMEM */
#define SUPPORT_DICTHASH_CACHE
#define SUPPORT_DICTDATA_FROMFILE
/*#define SUPPORT_DICTDATA_FROMMEM */
/*#define SUPPORT_DICTDATA_CACHE */
#define SUPPORT_SNDFMTDAT_FROMFILE
/*#define SUPPORT_SNDFMTDAT_FROMMEM */
/*#define SUPPORT_SNDFMTDAT_CACHE */
#define SUPPORT_POLYTABLE_FROMFILE
/*#define SUPPORT_POLYTABLE_FROMMEM */
#define SUPPORT_POLYTABLE_CACHE

/* Audio output buffer resize increment */
#define AUDIO_BLOCKSIZE 100000

/* Phonetic/POSP dictionary formats */
#define SUPPORT_DICT_COMPRESSED
#define SUPPORT_DICT_UNCOMPRESSED

/* Sound bank encoding styles */
#define SUPPORT_SNDBANK_ULAW
#define SUPPORT_SNDBANK_ALAW
/*#define SUPPORT_SNDBANK_ADPCM */
//#define SUPPORT_SNDBANK_NUMINA
/*#define SUPPORT_SNDBANK_CYBIT6 */
/*#define SUPPORT_SNDBANK_CYBIT12 */
#define SUPPORT_SNDBANK_CYBIT64
#define SUPPORT_SNDBANK_LINEAR
//////////////////////////////////

#define MAXNBEST			10
#define DEFALPHANBEST		10
#define MAXALPHANBEST		10
#define DEFALPHANVARIATIONS	10
#define MAXALPHANVARIATIONS	10

#endif
