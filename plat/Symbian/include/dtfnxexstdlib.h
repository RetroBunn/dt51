/*****************************************************
This file maps the unicode and narrow function defines 
created in dtfnxstdlib.h to default function names.

If you want to add new functions to this list be sure to 
add a define to both the unicode and narrow sections below, 
you will also need to add a FNX_<x> define to the 
dtfnxstdlib.h file.

FNXW_<x> = Unicode function
FNXA_<x> = Narrow function
*****************************************************/

#if !defined(__DTFNXEXSTDLIB_H__)
#define __DTFNXEXSTDLIB_H__

#include <stdio.h>
#include <string.h>
#include <assert.h>
/****************************************
General I/O 
****************************************/
#define FNX_STDIN           stdin
#define FNX_STDOUT          stdout
#define FNX_STDERR          stderr

/*********************************************
Memory Function Mappings
*********************************************/

#define FNXB_MALLOC         epocmalloc
#define FNXB_CALLOC         epoccalloc
#define FNXB_REALLOC        epocrealloc
#define FNXB_FREE           epocfree

/*********************************************
Diagnostic Function Mappings
*********************************************/
#define FNXB_ASSERT         assert

/****************************************
Unicode Function Mappings
****************************************/
// File I/O Function Mappings
#define FNXW_FOPEN          wfopen
#define FNXW_FCLOSE         fclose
#define FNXW_FGETC          fgetwc
#define FNXW_UNGETC         ungetwc
#define FNXW_FGETS          fgetws
#define FNXW_FREAD          fread
#define FNXW_FWRITE         fwrite
#define FNXW_FSEEK          fseek
#define FNXW_FTELL          ftell
#define FNXW_REWIND         rewind
#define FNXW_FFLUSH         fflush
#define FNXW_FEOF           feof
#define FNXW_FPRINTF        fwprintf
#define FNXW_FSCANF         fwscanf
#define FNXW_FPUTC          fputwc
#define FNXW_FPUTS          fputws
#define FNXW_FSETPOS        fsetpos
#define FNXW_FERROR         ferror
#define FNXW_CLEARERR       clearerr
#define FNXW_REMOVE         remove
#define FNXW_RENAME         rename
#define FNXW_FINDDATA_T		_wfinddata_t
#define FNXW_FINDFIRST      _wfindfirst
#define FNXW_FINDNEXT       _wfindnext
#define FNXW_FINDCLOSE      _findclose
// Character Manipulation Mappings
//#define FNXW_TOLOWER(_c)    towlower(_c)
//#define FNXW_TOUPPER(_c)    towupper(_c)
// String Manipulation Mappings
//#define FNXW_STRDUP         _wcsdup  // Fonix ANSI Extension. Use the Fonix version so that it can keep track of memory through Allocate.
#define FNXW_STRCAT         wcscat
#define FNXW_STRCHR         wcschr
#define FNXW_STRREV         _wcsrev
#define FNXW_STRCMP         wcscmp
#define FNXW_STRICMP        _wcsicmp  // Fonix ANSI Extension, if you do not define FNXW_STRICMP or FNXA_STRICMP ANSI equivalents will be used
#define FNXW_STRCPY         wcscpy
#define FNXW_STRCSPN        wcscspn
#define FNXW_STRERROR       strerror
#define FNXW_STRLEN         wcslen
#define FNXW_STRNCAT        wcsncat
#define FNXW_STRNCMP        wcsncmp
#define FNXW_STRNCPY        wcsncpy
#define FNXW_STRNICMP       _wcsnicmp // Fonix ANSI Extension, if you do not define FNXW_STRNICMP or FNXA_STRNICMP ANSI equivalents will be used
#define FNXW_STRPBRK        wcspbrk
#define FNXW_STRRCHR        wcsrchr
#define FNXW_STRSPN         wcsspn
#define FNXW_STRSTR         wcsstr
#define FNXW_STRTOK         wcstok_r
#define FNXW_STRUPR         _wcsupr  // Fonix ANSI Extension, if you do not define FNXW_STRUPR or FNXA_STRUPR ANSI equivalents will be used
#define FNXW_STRLWR         _wcslwr  // Fonix ANSI Extension, if you do not define FNXW_STRLWR or FNXA_STRLWR ANSI equivalents will be used
#define FNXW_BSEARCH        bsearch  // Fonix ANSI Extension, if you do not define FNXW_BSEARCH or FNXA_BSEARCH ANSI equivalents will be used
// String I/O Function Mappings
#define FNXW_SPRINTF        swprintf
#define FNXW_SSCANF         swscanf
// Time Function Mappings
#ifdef UIQ
#define FNXW_SLEEP          sleep 
#else
#define FNXW_SLEEP          Sleep 
#endif
// Data Conversion Function Mappings
#define FNXW_ATOI           _wtoi
#define FNXW_ATOL           _wtol
#define FNXW_ATOF           _wtof


/********************************************
Narrow Function Mappings
********************************************/
// File I/O Function Mappings
#define FNXA_FOPEN          fopen
#define FNXA_FCLOSE         fclose
#define FNXA_FGETC          fgetc
#define FNXA_FGETS          fgets
#define FNXA_FREAD          fread
#define FNXA_FWRITE         fwrite
#define FNXA_FSEEK          fseek
#define FNXA_FTELL          ftell
#define FNXA_REWIND         rewind
#define FNXA_FFLUSH         fflush
#define FNXA_FEOF           feof
#define FNXA_FPRINTF        fprintf
#define FNXA_FSCANF         fscanf
#define FNXA_FPUTC          fputc
#define FNXA_FPUTS          fputs
#define FNXA_FSETPOS        fsetpos
#define FNXA_FERROR         ferror
#define FNXA_CLEARERR       clearerr
#define FNXA_REMOVE         remove
#define FNXA_RENAME         rename
#define FNXA_FINDFIRST      findfirst
#define FNXA_FINDNEXT       findnext
#define FNXA_FINDCLOSE      findclose

// Standard I/O Function Mappings
#define FNXA_PRINTF         printf
#define FNX_PERROR			printf

#define FNXA_UNGETC          ungetc
// Character Manipulation Mappings
//#define FNXA_TOLOWER(_c)    tolower(_c)
//#define FNXA_TOUPPER(_c)    toupper(_c)

// String Manipulation Mappings
//#define FNXA_STRDUP         _strdup  // Fonix ANSI Extension. Use the Fonix version so that it can keep track of memory through Allocate.
#define FNXA_STRCAT         strcat
#define FNXA_STRCHR         strchr
#define FNXA_STRREV         _strrev

#define FNXA_STRCMP         strcmp
//#define FNXA_STRICMP        _stricmp  // Fonix ANSI Extension, if you do not define FNXW_STRICMP or FNXA_STRICMP ANSI equivalents will be used
#define FNXA_STRCPY         strcpy
#define FNXA_STRCSPN        strcspn
#define FNXA_STRERROR       strerror
#define FNXA_STRLEN         strlen
#define FNXA_STRNCAT        strncat
#define FNXA_STRNCMP        strncmp
#define FNXA_STRNCPY        strncpy
//#define FNXA_STRNICMP       _strnicmp  // Fonix ANSI Extension, if you do not define FNXW_STRNICMP or FNXA_STRNICMP ANSI equivalents will be used
#define FNXA_STRPBRK        strpbrk
#define FNXA_STRRCHR        strrchr
#define FNXA_STRSPN         strspn
#define FNXA_STRSTR         strstr
#define FNXA_STRTOK         strtok

#define FNXA_BSEARCH        bsearch
// String I/O Function Mappings
#define FNXA_SPRINTF        sprintf
#define FNXA_SSCANF         sscanf
#define FNXA_ISSPACE		isspace

#ifndef FNX_EXPORT
#define FNX_EXPORT(a,b)     __declspec(dllexport) a b
#endif

#ifdef UIQ
#define FNXA_SLEEP          sleep   
#else
#ifndef FNXA_SLEEP
#define FNXA_SLEEP fnxasleep
#define FNX_BUILD_SLEEP
	#if defined(__cplusplus)
	extern "C" {
	#endif
	
		void fnxasleep(int delay);
		
	#if defined(__cplusplus)
	}
	#endif
#endif
#endif //UIQ

// Data Conversion Function Mappings
#define FNXA_ATOI           atoi
#define FNXA_ATOL           atol
#define FNXA_ATOF           atof

#ifndef _MAX_PATH
#define _MAX_PATH	256
#endif
#ifndef MAX_PATH
#define MAX_PATH	_MAX_PATH
#endif

#if defined(__cplusplus)
extern "C" {
#endif

FNX_EXPORT(void*, epocmalloc ( size_t size ));
FNX_EXPORT(void*, epoccalloc ( size_t nel, size_t size ));
FNX_EXPORT(void, epocfree ( void* mem ));
FNX_EXPORT(void*, epocrealloc ( void* mem, size_t newsize ));
FNX_EXPORT(int, stricmp(const char *string1, const char *string2));
FNX_EXPORT(wchar_t *, wcstok_r(wchar_t *s, const wchar_t *delim, wchar_t **lasts));
FNX_EXPORT(wchar_t *, wcschr( const wchar_t *string, int c ));
FNX_EXPORT(wchar_t *, wcsstr(const wchar_t *str, const wchar_t *srch));
FNX_EXPORT(wchar_t*, fgetws(wchar_t* pwcz, int n, FILE* pFile));
#if defined(__cplusplus)
}
#endif
#endif
