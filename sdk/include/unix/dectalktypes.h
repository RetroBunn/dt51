/*
 * dectalktypes.h -- common types needed for ttsapi.h
 *
 * Copyright 2005 Fonix Corporation.  All rights reserved.
 *
 * This must be included after other more standard includes (stdio.h, etc), so that features.h will be included first.
 */
#ifndef DECTALKTYPES_H
#define DECTALKTYPES_H

#if (defined(__STDC__) && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || defined(HAVE_STDINT_H)
#include <stdint.h>
#ifndef INT8_MAX
typedef int_least8_t int8_t;
#endif
#ifndef INT16_MAX
typedef int_least16_t int16_t;
#endif
#ifndef INT32_MAX
typedef int_least32_t int32_t;
#endif
#ifndef UINT8_MAX
typedef uint_least8_t uint8_t;
#endif
#ifndef UINT16_MAX
typedef uint_least16_t uint16_t;
#endif
#ifndef UINT32_MAX
typedef uint_least32_t uint32_t;
#endif
#elif (defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE >= 500)) || defined(HAVE_INTTYPES_H)
#include <inttypes.h>
#else
/* This is a guess */
typedef signed char            int8_t;
typedef short int              int16_t;
typedef int                    int32_t;
typedef unsigned char          uint8_t;
typedef unsigned short int     uint16_t;
typedef unsigned int           uint32_t;
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#if !defined(VXWORKS) && !defined(BOOL_DEFINED)
#define BOOL_DEFINED
typedef unsigned char		BOOL;
#endif
#ifndef _DWORD
#define _DWORD
typedef uint32_t		DWORD;
#endif
typedef int32_t			LONG;
typedef uint32_t		ULONG;
typedef DWORD*			LPDWORD;
typedef char*			LPSTR;
typedef unsigned char		UCHAR;

#if !defined(VXWORKS) && !defined(_UINT)
#define _UINT
typedef uint32_t		UINT;
#endif
typedef UINT			MMRESULT;

typedef unsigned short		USHORT;

#ifndef _WORD
#define _WORD
typedef uint16_t		WORD;
#endif

#ifndef VXWORKS
typedef void			VOID;
#endif

#endif
