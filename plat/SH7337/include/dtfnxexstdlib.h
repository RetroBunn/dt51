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

#if !defined(__FNXEXSTDLIB_H__)
#define __FNXEXSTDLIB_H__

#include <string.h>
//#include <stdlib.h>

#ifndef SEEK_SET
#define SEEK_SET	0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR	1
#endif
#ifndef SEEK_END
#define SEEK_END	2
#endif

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

#define __cdecl

#ifndef FNX_EXPORT
#define FNX_EXPORT(a,b) extern a b
#endif

//extern void *calloc(size_t, size_t);
//extern void free(void *) ;
//extern void *malloc(size_t);
//extern void *realloc(void *, size_t) ;
extern void *bsearch(const void *, const void *, size_t, size_t,
                                  int(*)(const void*,const void*) ) ;
extern void qsort(void *, size_t, size_t,
                                  int(*)(const void*,const void*) );

/*********************************************
Diagnostic Function Mappings
*********************************************/
#define FNXB_ASSERT		assert

/****************************************
General I/O
****************************************/
#define FNX_STDIN           NULL
//#define FNX_STDOUT          stdout
//#define FNX_STDERR          stderr
//#define FNX_STDIN           stdin
#define FNX_STDOUT          NULL
#define FNX_STDERR			NULL

#define FNX_PERROR			perror

/*********************************************
Memory Function Mappings
*********************************************/
//#define FNX_MEM_SIZE		_msize
//# define FNXB_MALLOC		malloc
//# define FNXB_CALLOC		calloc
//# define FNXB_REALLOC		realloc
//# define FNXB_FREE			free
# define FNXB_MALLOC
# define FNXB_CALLOC
# define FNXB_REALLOC
# define FNXB_FREE

/****************************************
General Mappings
****************************************/
#define FNX_FOPENWITHPATH   FNX_FOPEN
#define FNX_TIMESTRUCT      time_t
#define FNX_TM_TIMESTRUCT   struct tm


/****************************************
Memfile native file routins
****************************************/
#define FNX_MF_FOPEN        fopen
#define FNX_MF_FCLOSE       fclose
#define FNX_MF_UNGETC       ungetc
#define FNX_MF_GETC         getc
#define FNX_MF_FGETS        fgets
#define FNX_MF_FWRITE       fwrite
#define FNX_MF_FREAD        fread
#define FNX_MF_FSEEK        fseek
#define FNX_MF_FTELL        ftell
#define FNX_MF_REWIND       rewind
#define FNX_MF_FEOF         feof
#define FNX_MF_CLEARERR     clearerr
#define FNX_MF_FLUSH        fflush
#define FNX_MF_VFPRINTF     vfprintf
#define FNX_MF_FSCANF       fscanf
#define FNX_MF_FPUTC        fputc
#define FNX_MF_FPUTS        fputs
#define FNX_MF_FSETPOS      fsetpos
#define FNX_MF_FERROR       ferror
#define FNX_MF_REMOVE       remove
#define FNX_MF_RENAME       rename
#define FNX_MF_FINDDATA_T   FNXA_FINDDATA_T
#define FNX_MF_FINDFIRST    _findfirst
#define FNX_MF_FINDNEXT     _findnext
#define FNX_MF_FINDCLOSE    _findclose

/****************************************
Unicode Function Mappings
****************************************/
// File I/O Function Mappings
#define FNXW_FOPEN          _wfopen
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
//#define FNXW_FINDDATA_T   _wfinddata_t
#define FNXW_FINDFIRST      _wfindfirst
#define FNXW_FINDNEXT       _wfindnext
#define FNXW_FINDCLOSE      _findclose
// Standard I/O Function Mappings
// Character Manipulation Mappings
#define FNXW_TOLOWER(_c)    towlower(_c)
#define FNXW_TOUPPER(_c)    towupper(_c)
// Character Classification Definitions
#define FNXW_ISALPHA(_c)    iswalpha(_c)
#define FNXW_ISUPPER(_c)    iswupper(_c)
#define FNXW_ISLOWER(_c)    iswlower(_c)
#define FNXW_ISDIGIT(_c)    iswdigit(_c)
#define FNXW_ISXDIGIT(_c)   iswxdigit(_c)
#define FNXW_ISSPACE(_c)    iswspace(_c)
#define FNXW_ISPUNCT(_c)    iswpunct(_c)
#define FNXW_ISALNUM(_c)    iswalnum(_c)
#define FNXW_ISPRINT(_c)    iswprint(_c)
#define FNXW_ISGRAPH(_c)    iswgraph(_c)
#define FNXW_ISCNTRL(_c)    iswcntrl(_c)
// don't map this so the default one gets built in FnxStdLib
//#define FNXW_ISASCII(_c)    iswascii(_c)
// String Manipulation Mappings
#define FNXW_STRDUP         _wcsdup  // Fonix ANSI Extension. Use the Fonix version so that it can keep track of memory through Allocate.
//#define FNXW_STRCAT         wcscat
#define FNXW_STRCHR         fnxwcschr
#define FNXW_STRREV         _wcsrev
#define FNXW_STRCMP         wcscmp
#define FNXW_STRICMP        _wcsicmp  // Fonix ANSI Extension, if you do not define FNXW_STRICMP or FNXA_STRICMP ANSI equivalents will be used
#define FNXW_STRCPY         fnxwcscpy
#define FNXW_STRCSPN        wcscspn
#define FNXW_STRERROR       strerror
#define FNXW_STRLEN         fnxwcslen
#define FNXW_STRNCAT        wcsncat
#define FNXW_STRNCMP        wcsncmp
#define FNXW_STRNCPY        fnxwcsncpy
#define FNXW_STRNICMP       _wcsnicmp // Fonix ANSI Extension, if you do not define FNXW_STRNICMP or FNXA_STRNICMP ANSI equivalents will be used
#define FNXW_STRPBRK        wcspbrk
#define FNXW_STRRCHR        wcsrchr
#define FNXW_STRSPN         wcsspn
#define FNXW_STRSTR         fnxwcsstr
#define FNXW_STRTOK         fnxwcstok
#define FNXW_STRUPR         _wcsupr  // Fonix ANSI Extension, if you do not define FNXW_STRUPR or FNXA_STRUPR ANSI equivalents will be used
#define FNXW_STRLWR         _wcslwr  // Fonix ANSI Extension, if you do not define FNXW_STRLWR or FNXA_STRLWR ANSI equivalents will be used
#define FNXW_BSEARCH        fnxbsearch  // Fonix ANSI Extension, if you do not define FNXW_BSEARCH or FNXA_BSEARCH ANSI equivalents will be used
// String I/O Function Mappings
#define FNXW_SPRINTF        swprintf
#define FNXW_SSCANF         swscanf
// Time Function Mappings
#define FNXW_TIME           time
#define FNXW_STRFTIME       wcsftime
#define FNXW_LOCALTIME      localtime
#define FNXW_DIFFTIME       difftime
//#define FNXW_DIFFTIMEDAYS   fnxaDiffTimeDays  // Convenience function, tells you the difference in days between 2 FNX_TIMESTRUCT structures (map to Narrow, no need to re-implement)
#define FNXW_SLEEP          FnxDelay             // Sleep for millisecond
// Data Conversion Function Mappings
//#define FNXW_ATOI           _wtoi
#define FNXW_ATOL           _wtol
#define FNXW_ATOF           _wtof

#ifdef USE_MEMFILE_IO
/********************************************
Narrow Function Mappings
********************************************/
#define	FNXA_FOPEN			MemFileOpen
#define FNXA_FCLOSE			MemFileClose
#define FNXA_FGETC			MemFileGetc
//#define FNXA_UNGETC         MemFileUngetc
#define FNXA_FGETS			MemFileGets
#define FNXA_FREAD			MemFileRead
#define FNXA_FWRITE			MemFileWrite
#define FNXA_FSEEK			MemFileSeek
#define FNXA_FTELL			MemFileTell
#define FNXA_REWIND			MemFileRewind
#define FNXA_FFLUSH			MemFileFlush
#define FNXA_FEOF			MemFileEof
#define FNXA_FPRINTF		MemFilePrintf	//MemFileFunctionErrorPrintf	// MemFilePrintf - not implemented for mem files
#define FNXA_FSCANF			MemFileFunctionErrorScanf	// MemFileScanf - not implemented for mem files
#define FNXA_FPUTC			MemFileFunctionErrorPutc	// MemFilePutc - not implemented for mem files
#define FNXA_FPUTS			MemFileFunctionErrorPuts	// MemFilePuts - not implemented for mem files
#define FNXA_FSETPOS		MemFileFunctionErrorSetpos	// MemFileSetpos - not implemented for mem files
#define FNXA_FERROR			MemFileError				// MemFileError - quick and dirty implementation
#define FNXA_CLEARERR		MemFileFunctionErrorClearerr	// MemFileClearerr - not implemented for mem files
#define FNXA_REMOVE			MemFileFunctionErrorRemove	// MemFileRemove - not implemented for mem files
#define FNXA_RENAME			MemFileFunctionErrorRename	// MemFileRename - not implemented for mem files
#define FNXA_GETFILELEN     MemFileGetFileLength
#define FNXA_FINDFIRST		MemFileFindFirst
#define FNXA_FINDNEXT		MemFileFindNext
#define FNXA_FINDCLOSE		MemFileFindClose

#else
/********************************************
Narrow Function Mappings
********************************************/
// File I/O Function Mappings
#if defined (CASIO_SH3) && defined (_BIGENDIAN_)
#define _inline
#define FNXA_FOPEN			fnxfopen
#define FNXA_FCLOSE			fnxfclose
#define FNXA_FREAD			fnxfread  
#define FNXA_FWRITE			fnxfwrite
#define FNXA_FSEEK			fnxfseek
#else
#define FNXA_FOPEN			fopen
#define FNXA_FCLOSE			fclose
#define FNXA_FREAD			fread  
//#define FNXA_FWRITE			fwrite
//#define FNXA_FSEEK			fseek
#endif
//#define FNXA_FOPEN          fopen
//#define FNXA_FCLOSE         fclose
//#define FNXA_FGETC          fgetc
//#define FNXA_FGETS          fgets
//#define FNXA_PUTC			putc
//#define FNXA_PUTCHAR		putchar
//#define FNXA_PUTS			puts
//#define FNXA_GETC			getc
//#define FNXA_GETCHAR		getchar
//#define FNXA_GETS			gets
//#define FNXA_FREAD          fread
//#define FNXA_FWRITE         fwrite
//#define FNXA_FSEEK          fseek
//#define FNXA_FTELL          ftell
//#define FNXA_REWIND         rewind
//#define FNXA_FFLUSH         fflush
//#define FNXA_FEOF           feof
//#ifndef CASIO_SH3
//#define FNXA_FPRINTF        fprintf
//#endif
//#define FNXA_FSCANF         fscanf
//#define FNXA_FPUTC          fputc
//#define FNXA_FPUTS          fputs
//#define FNXA_FSETPOS        fsetpos
//#define FNXA_FERROR         ferror
#define FNXA_CLEARERR       clearerr
#define FNXA_REMOVE         remove
#define FNXA_RENAME         rename
#define FNXA_FINDFIRST      findfirst
#define FNXA_FINDNEXT       findnext
#define FNXA_FINDCLOSE      findclose
#endif //USE_MEMFILE_IO

#define FNXA_UNGETC         ungetc

// Standard I/O Function Mappings
//#define FNXA_PRINTF         printf
// Character Manipulation Mappings
#define FNXA_TOLOWER(_c)    tolower(_c)
#define FNXA_TOUPPER(_c)    toupper(_c)
// Character Classification Definitions
#define FNXA_ISALPHA(_c)    isalpha(_c)
#define FNXA_ISUPPER(_c)    isupper(_c)
#define FNXA_ISLOWER(_c)    islower(_c)
#define FNXA_ISDIGIT(_c)    isdigit(_c)
#define FNXA_ISXDIGIT(_c)   isxdigit(_c)
#define FNXA_ISSPACE(_c)    isspace(_c)
#define FNXA_ISPUNCT(_c)    ispunct(_c)
#define FNXA_ISALNUM(_c)    isalnum(_c)
#define FNXA_ISPRINT(_c)    isprint(_c)
#define FNXA_ISGRAPH(_c)    isgraph(_c)
#define FNXA_ISCNTRL(_c)    iscntrl(_c)
#define FNXA_ISASCII(_c)    isascii(_c)
// String Manipulation Mappings
#define FNXA_STRDUP         strdup  // Fonix ANSI Extension. Use the Fonix version so that it can keep track of memory through Allocate.
#define FNXA_STRCAT         strcat
#define FNXA_STRCHR         strchr
#define FNXA_STRREV         strrev
#define FNXA_STRCMP         strcmp
#define FNXA_STRICMP        _stricmp  // Fonix ANSI Extension, if you do not define FNXW_STRICMP or FNXA_STRICMP ANSI equivalents will be used
#define FNXA_STRCPY         strcpy
#define FNXA_STRCSPN        strcspn
#define FNXA_STRERROR       strerror
#define FNXA_STRLEN         strlen
#define FNXA_STRNCAT        strncat
#define FNXA_STRNCMP        strncmp
#define FNXA_STRNCPY        strncpy
#define FNXA_STRNICMP       strncasecmp  // Fonix ANSI Extension, if you do not define FNXW_STRNICMP or FNXA_STRNICMP ANSI equivalents will be used
//#define FNXA_STRNICMP       strnicmp  // Fonix ANSI Extension, if you do not define FNXW_STRNICMP or FNXA_STRNICMP ANSI equivalents will be used
#define FNXA_STRPBRK        strpbrk
#define FNXA_STRRCHR        strrchr
#define FNXA_STRSPN         strspn
#define FNXA_STRSTR         strstr
#define FNXA_STRTOK         strtok
#define FNXA_STRUPR         _strupr   // Fonix ANSI Extension, if you do not define FNXW_STRUPR or FNXA_STRUPR ANSI equivalents will be used
#define FNXA_STRLWR         _strlwr   // Fonix ANSI Extension, if you do not define FNXW_STRLWR or FNXA_STRLWR ANSI equivalents will be used
#define FNXA_BSEARCH        fnxbsearch  // Fonix ANSI Extension, if you do not define FNXW_BSEARCH or FNXA_BSEARCH ANSI equivalents will be used
// String I/O Function Mappings
//#define FNXA_SPRINTF        sprintf
//#define FNXA_SSCANF         sscanf
// Time Function Mappings
#define FNXA_TIME           time
#define FNXA_STRFTIME       strftime
#define FNXA_LOCALTIME      localtime
#define FNXA_DIFFTIME       difftime
//#define FNXA_DIFFTIMEDAYS   fnxaDiffTimeDays  // Convenience function, tells you the difference in days between 2 FNX_TIMESTRUCT structures
#define FNXA_SLEEP          FnxDelay             // Sleep for millisecond
// Data Conversion Function Mappings
#define FNXA_ATOI           atoi
#define FNXA_ATOL           atol
#define FNXA_ATOF           atof

#define _A_SUBDIR   1
#define _A_FILE     2
#define _A_UNKNOWN  3

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef FNXA_FGETS
#	define FNXA_FGETS  fnxafgets
#	define FNXA_BUILD_FGETS
	FNX_EXPORT( char *, fnxafgets( char *string, int n, void *stream ) );
#endif

#ifndef FNXA_FGETC
#	define FNXA_FGETC  fnxafgetc
#	define FNXA_BUILD_FGETC
	FNX_EXPORT( int, fnxafgetc( void *stream ) );
#endif

#ifndef FNXW_STRCPY
#	define FNXW_STRCPY fnxwcscpy
#	define FNXW_BUILD_STRCPY
	FNX_EXPORT( wchar_t *, fnxwcscpy(wchar_t * str1,const wchar_t * str2));
#endif

#ifndef FNXW_STRLEN
#	define FNXW_STRLEN fnxwcslen
#	define FNXW_BUILD_STRLEN
	FNX_EXPORT( size_t, fnxwcslen(const wchar_t * s));
#endif


#ifndef FNXW_STRCHR
#  define FNXW_STRCHR  fnxwcschr
#  define FNXW_BUILD_STRCHR
   FNX_EXPORT( wchar_t*, fnxwcschr(const wchar_t* str, wchar_t ch));
#endif

#ifndef FNXW_STRTOK
#  define FNXW_STRTOK  fnxwcstok
#  define FNXW_BUILD_STRTOK
   FNX_EXPORT( wchar_t, *fnxwcstok(wchar_t *s, const wchar_t *ct) );
#endif


//FNX_EXPORT(double, fnxaDiffTimeDays( FNX_TIMESTRUCT timer1, FNX_TIMESTRUCT timer2 ) );
FNX_EXPORT(void *, fnxfopen(const char *pName, const char *pFlags));
FNX_EXPORT(int,  fnxfclose(void *pStream));
FNX_EXPORT(wchar_t *, fnxwcstok(wchar_t *s, const wchar_t *ct));
FNX_EXPORT(wchar_t*,  fnxwcschr(const wchar_t* str, wchar_t ch));
FNX_EXPORT(wchar_t *, fnxwcsstr(const wchar_t *s,const wchar_t *b));
#if defined(__cplusplus)
}
#endif

#endif
