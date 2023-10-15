/*H_HEADER_FILE***************************************************************
FILE        : FnxPlatform.h
DESC        : Determine which platform and OS is in use, include appropriate FnxMachine.h,
                and define integer types.
TABS        : 3
OWNER       : Fonix
DATE CREATED: 

(C) Copyright 1999,2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/28/05 2:28p $
  $Revision: 13 $

*END_HEADER******************************************************************/

/* This file contains mappings of type definitions needed to make it so
   that code can support either floating-point or integer mode operation.
   It also defines a variety of other things that are needed by all platforms,
   including names for the integer types that should be used when the size
   of integers must be guaranteed.

   Platform-specific definitions should be placed in the FnxMachine.h file
   of the platform.

   The include path needs to include the directory for your particular platform
   so that the correct version of FnxMachine.h and fnxexstdlib.h gets included.
*/

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#define bswap16(a) { char c; c=*((char*)&a); *((char*)&a)=*(((char*)&a)+1); *(((char*)&a)+1)=c; }
#define bswap32(a) { char c; c=*((char*)&a); *((char*)&a)=*(((char*)&a)+3); *(((char*)&a)+3)=c; c=*(((char*)&a)+1); *(((char*)&a)+1)=*(((char*)&a)+2); *(((char*)&a)+2)=c; }

/* Put the directory where your platform's FnxMachine.h exists 
   into your include path, so that this will include the right one. */
#include "FnxMachine.h"

#define FIX_SHORT_DATA_BUG								// In the future, this define may be removed if this fix
														//   proves valid for all platforms and situations

// Eventually replace these with types from stdint.h
#define  SBYTE    int8_t
#define  UBYTE    uint8_t

typedef int WBOOL;

#ifndef __SQLTYPES
#define  SWORD    int16_t
#define  UWORD    uint16_t
#define  SDWORD   int32_t
#define  UDWORD   uint32_t
#endif

typedef SBYTE  xhuge *SBYTEPTR; /* xhuge should be defined (usually as nothing) in FnxMachine.h */
typedef SWORD  xhuge *SWORDPTR;
typedef SDWORD xhuge *SDWORDPTR;
typedef UWORD  xhuge *UWORDPTR;
typedef UDWORD xhuge *UDWORDPTR;

typedef size_t  usize; /* size_t should be defined in FnxMachine.h */

/* These types are temporarily defined here until they can be removed
   from the rest of the code and replaced with the new "standard" names. */
#define sword8  int8_t
#define sword16 int16_t
#define sword32 int32_t
#define uword8  uint8_t
#define uword16 uint16_t
#define uword32 uint32_t

// Make sure FnxMachine.h defines endianness for this platform
#if !defined(WORDS_BIGENDIAN) && !defined(WORDS_LITTLEENDIAN)
#     error FnxMachine.h must define WORDS_BIGENDIAN or WORDS_LITTLEENDIAN
#endif 
#if defined(WORDS_BIGENDIAN) && defined(WORDS_LITTLEENDIAN)
#     error FnxMachine.h must define WORDS_BIGENDIAN or WORDS_LITTLEENDIAN, NOT BOTH!!
#endif 

#include "FnxError.h"
#ifdef USE_MEMFILE_IO
#include "FnxFiles.h"
#endif

// Define floating-point types (or their integer equivalents)
//   and other macros involved with INTEGER_CORE
#ifdef   INTEGER_CORE
   typedef  SWORD       CoreType;                  //  this must be SWORD not SDWORD for nnet weight reading
   typedef  SDWORD         SrchType;
   typedef  SDWORD         CalcType;
#  define   log2IntScale   10                      //  Number of bits to shift for scaling
#  define   sqrtIntScale   32                      //  Square root of the int scale.
#  define   IntScale    1024
#  define   HalfIntScale   512
#  define   SCALED_LN_OF_2 726817 // =IntScale*IntScale*ln(2) = 1024 * 1024 * 0.69314718056 = 726817.498
#  define   SCALEUP(X)     ((X) << log2IntScale)
#  ifdef SHIFT_IS_FASTER  // Define this in FnxMachine.h if shifting is faster than division on that platform.
#     define   SCALEDN(X)     (((X)) >> log2IntScale)    
#     define   SCALEDNROUND(X) (((X)+HalfIntScale) >> log2IntScale) // round to nearest value.
#  else
#     define   SCALEDN(X)     (((X)) / IntScale)      //  A right shift isn't faster on some platforms and may have rounding errors
#     define   SCALEDNROUND(X) (((X)+HalfIntScale) / IntScale) // round to nearest value.
#  endif
#  define   LogProbScale   1024
#else  // Not INTEGER_CORE
   typedef  float       CoreType;
   typedef  float       SrchType;
   typedef  float       CalcType;
#  define   SCALEUP(X)     ((X))
#  define   SCALEDN(X)     ((X))
#  define   IntScale    1.0F
#  define   sqrtIntScale 1.0F
#endif

typedef CoreType xhuge     *CoreTypePtr;
typedef SrchType xhuge     *SrchTypePtr;
typedef CalcType xhuge     *CalcTypePtr;

#define pDescExt           ".desc"
#define pConfigExt         ".config"

#define FDIR_ALL_SEP "\\/:^"  // Put all seperators into this string so any will work
#if defined(FLAT_DIR_STRUCTURE)
#  define   FDIR_SEP_CHAR  '^'
# define FDIR_SEP_STR   "^"
#elif defined(OS_WIN32)
#  define   FDIR_SEP_CHAR  '\\'
# define FDIR_SEP_STR   "\\"
#elif defined(OS_UNIX)                 // Unix and (Mac OS 10 and above)
#  define   FDIR_SEP_CHAR  '/'
# define FDIR_SEP_STR   "/"
#elif defined(OS_MAC) && !defined(OS_UNIX)   // Mac OS 9.x and below
#  define   FDIR_SEP_CHAR  ':'
# define FDIR_SEP_STR   ":"
#endif

#  if defined(OS_WIN32)
#     define   FNEWLINE    "\n"
#  elif defined(OS_UNIX)
#     define   FNEWLINE    "\n"
#  elif defined(OS_MAC)
#     define   FNEWLINE    "\r"
#  endif

// General Definitions
#ifndef TRUE
#  define TRUE 1
#endif
#ifndef  FALSE
#  define FALSE   0
#endif

#endif
