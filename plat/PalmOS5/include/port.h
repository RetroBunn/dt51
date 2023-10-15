#ifndef _PORT_H
#define _PORT_H

#include "dectalkf.h"  
#include <limits.h>   
/*
 ************************************************************************
 *  ARM7TDMI
 */
 
#define OP_ResetEvent( pEvent )
#define OP_LockMutex( pMutex )
#define OP_UnlockMutex( pMutex )
#define OP_WaitForEvent( pEvent, uiMilliSeconds )

/*
 ************************************************************************
 *  PALM stuff
 ************************************************************************ 
 */

//#include <time.h>
/*
 * fake out some MSDOS stuff
 */
#define FAR
#define __far
#define _far
#define far
#define huge
#define volatile
#define _inline
#define __inline

#define TRUE 1
#define FALSE 0

#ifdef SEPARATE_PROCESSES
#undef SEPARATE_PROCESSES
#endif

typedef signed long SDWORD;
typedef unsigned long UDWORD;
typedef unsigned long DWORD;
typedef unsigned short WORD;

#define FNX_MAX_PATH        260

#define wchar_t unsigned short

typedef void * voidPtr;
typedef unsigned int size_t;
typedef size_t  usize;

//#include "DTFnxFiles.h"
#include "DTFnxStdlib.h"

//define CONSTSTRUCT as "const" if your platform needs it
//in front of a struct declaration else define it as nothing
#define CONSTSTRUCT
//define CONSTCONST as "const" if your platform can declare a const const array
//else define it as nothing
#define CONSTCONST
#define CONSTARRAY
#define CONST const

typedef unsigned short DT_PIPE_T;
typedef long S32;
typedef unsigned long U32;
typedef short S16;
typedef unsigned short U16;
typedef signed char S8;
typedef unsigned char U8;

typedef void * DT_HANDLE;
typedef void * LPVOID;
typedef void * PVOID;
typedef unsigned int UINT;
typedef long MMRESULT;

typedef long LONG;


#ifndef FNX_EXPORT
#define FNX_EXPORT(a,b)     __declspec(dllexport) a b
#endif

#define MAIN_DICT_NAME "dtalk_us.dic"

#endif /* _PORT_H */
