#ifndef MACHINE_H
#define MACHINE_H

#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

// By including stdint.h and/or defining the ones that are
// left out, define int8_t through int_fast8_t listed below.
#include <stdint.h>

typedef void * voidPtr;

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#define FNX_IMPORT(a,b)     a b
#define FNX_EXPORT_DYN(a,b)	a b
#define FNX_TYPE(a,b,c)     typedef a (*Type##b) c
#define FNX_EXPORT_DYN_TYPE(a,b,c) FNX_EXPORT_DYN(a,b) c; FNX_TYPE(a, b, c)
#define FNX_EXPORT_C

#define FNX_MAX_PATH        260

#define MMRESULT int

#ifdef _LIB		// building static libs
	#ifdef __cplusplus
		#define FNX_IMPORT_DATA(a,b)  extern "C" a b
	#else
		#define FNX_IMPORT_DATA(a,b)  extern a b
	#endif
	#define FNX_EXPORT_DATA(a)	a
#else  // _LIB
	#define FNX_IMPORT_DATA(a,b)  a b
	#define FNX_EXPORT_DATA(a)    a
#endif  // _LIB

#define xhuge

// ASR defines
#define MULTITHREADED
#define GLOBAL_COMMON
#define USE_SEARCH_GRAPH
//#define NO_SYSFILE_WRITES

// ASR & TTS defines
#define INIT_INTERRUPTS
#define HALT_INTERRUPTS
#define START_INTERRUPTS
#define SMALL_TTS

//#define USE_MEM_FILEIO
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

//////////////////////////////////
// Note: Minumum nBest, alpha nBest, and nVariations are defined in buildtc.h because they will be
//   the same for all platforms. The defines below can be set to valid values for the platform
//   the FnxMachine.h is written for. A Maximum nBest "define" for Alpha nodes has been retained
//   because it will affect memory usage differently than nBest for all other types of nodes.  
#define MAXNBEST			100000
// NOTE: The minimum nBest is the default nBest value
#define DEFALPHANBEST		10
#define MAXALPHANBEST		100000
#define DEFALPHANVARIATIONS	10
#define MAXALPHANVARIATIONS	10000

#endif
