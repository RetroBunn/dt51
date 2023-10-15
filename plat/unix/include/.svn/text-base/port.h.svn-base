#ifndef PORT_H
#define PORT_H
#define _UNIX_LIKE_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h> /* get _POSIX_THREADS, if there */
#include <string.h>

#include "dectalktypes.h" 
#include "opthread.h"

/* some old MS-DOG defines */
#define __far
#define _far
#define far
#define FAR
#define near
#define NEAR
#define huge
#define CALLBACK
#define APIENTRY
#define WINAPI   	APIENTRY

#define FNX_EXPORT_C
#ifndef  FNX_EXPORT
#  define FNX_EXPORT(a,b) extern a b
#endif
#define IMPORT(a,b) a b
#include "DTFnxStdlib.h"

/* These get fixed up by autoconf anyway */
#define CONST const
/* 
 * define CONSTSTRUCT as "const" if your platform needs it
 * in front of a struct declaration else define it as nothing
 */
#define CONSTSTRUCT const
/*
 * define CONSTCONST as "const" if your platform can declare a const const array
 * else define it as nothing
 */
#define CONSTCONST const
#define CONSTARRAY const

#ifndef EOS
#define EOS	0               /* End Of String */
#endif

#define _inline inline

typedef unsigned short DT_PIPE_T;
typedef int32_t S32;
typedef uint32_t U32;
typedef int16_t S16;
typedef uint16_t U16;
typedef int8_t S8;
typedef uint8_t U8;

typedef short int SHORT;

#if 0
typedef int32_t SDWORD;
typedef uint32_t UDWORD;
typedef uint32_t UINT;

typedef void* DT_HANDLE;
typedef void* LPVOID;
typedef void* PVOID;
#endif

typedef uint8_t BYTE;
typedef char CHAR;
typedef wchar_t WCHAR;
typedef CHAR *LPCSTR;
typedef WCHAR *LPWSTR;
typedef CONST WCHAR *LPCWSTR;
#define WideStringtoAsciiString(a, b, c)      wcstombs(a, b, c)

/* Handle is 32 bit UINT */
#ifdef VXWORKS
typedef LONG *DT_HANDLE;
#else
typedef LONG *DT_HANDLE;
typedef DT_HANDLE HANDLE;
#endif
typedef void* LPVOID;
typedef void* PVOID;
typedef uint64_t QWORD, * PQWORD; //tek 04aug97 sapi fixes
typedef LONG                LPARAM;
typedef UINT                WPARAM;

/* general extended waveform format structure
   Use this for all NON PCM formats
   (information common to all formats)
*/
#ifndef tWAVEFORMATEX
#define _WAVEFORMATEX_
typedef struct tWAVEFORMATEX
{
    WORD    wFormatTag;        /* format type */
    WORD    nChannels;         /* number of channels (i.e. mono, stereo...) */
    DWORD   nSamplesPerSec;    /* sample rate */
    DWORD   nAvgBytesPerSec;   /* for buffer estimation */
    WORD    nBlockAlign;       /* block size of data */
    WORD    wBitsPerSample;    /* Number of bits per sample of mono data */
    WORD    cbSize;            /* The count in bytes of the size of
                                    extra information (after cbSize) */

} WAVEFORMATEX;
typedef WAVEFORMATEX       *PWAVEFORMATEX;
typedef WAVEFORMATEX NEAR *NPWAVEFORMATEX;
typedef WAVEFORMATEX FAR  *LPWAVEFORMATEX;
#endif /* _WAVEFORMATEX_ */

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

/* this value is from Windows mmsystem.h */
#define CALLBACK_FUNCTION   0x00030000l    /* dwCallback is a FARPROC */

#ifndef SUN_ULAW
#define SUN_ULAW        1
#endif
#ifndef SUN_LIN_8
#define SUN_LIN_8       2
#endif
#ifndef SUN_LIN_16
#define SUN_LIN_16      3
#endif
#endif
