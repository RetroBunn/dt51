#ifndef __fonixpublic_h
#define __fonixpublic_h

#if !defined(__cplusplus)
#ifndef BOOL
#define BOOL int
#endif
#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif
#endif

#if defined(OS_SYMBIAN)
#undef WIN32
#undef _WIN32
#define BOOL int
#endif

#if defined(WIN32) || defined(_WIN32) || defined(UNDER_CE)
#if !defined(UNDER_CE)
#include <stddef.h>
#endif
#define WIDE_CHARACTER
#endif

#if defined(WIN32) || defined(_WIN32) || defined(UNDER_CE)
#define FnxCallType __stdcall
#define FNX_EXPORT(a,b) __declspec(dllexport) a b
#define FnxExport(a,b) __declspec(dllexport) a __stdcall b
#elif defined (OS_SYMBIAN) || defined (OS_PALM)
#define FnxExport(a,b) __declspec(dllexport) a b
#define FnxCallType
#else
#define FnxExport(a,b) a b
#define FNX_EXPORT(a,b) a b
#define FnxCallType
#endif

#define FNX_MF_STATIC       (0x0001)
#define FNX_MF_WRITING      (0x0002)
#define FNX_MF_MAXFILES     64

typedef struct
{
    int  flags;
    int  len;
    char *pName;
    char *pAddr;
} FnxMemFileMapping;

#if defined(__cplusplus)
extern "C" {
#endif

FnxExport( void, FnxMemFileRegister( FnxMemFileMapping * ) );

// Memory routines
FnxExport( void, FnxCombineMemFileMaps(FnxMemFileMapping **ppMapsIn, int nMapsInCnt, FnxMemFileMapping *pMapOut) );
FnxExport( int,	 FnxMemSetBlockSize( int blockSize) );
FnxExport( int,	 FnxMemGetBlockSize() );
FnxExport( int,	 FnxMemGetSystemBytes( int *pGlobMaxSys, int *pLocalMaxSys, int *pCurSysBytes) );
FnxExport( int,	 FnxMemGetActualBytes( int *pGlobMaxAct, int *pLocalMaxAct, int *pCurActBytes) );
FnxExport( void,	 FnxMemResetLocalBytes() );

#if defined(__cplusplus)
}
#endif

// Call this macro to register your memory file after putting #include "myfile.mem" in your source
#define FNX_MEMFILE_REGISTER FnxMemFileRegister( FNX_MEMFILE_MAP );

#endif  // __fonixpublic_h
