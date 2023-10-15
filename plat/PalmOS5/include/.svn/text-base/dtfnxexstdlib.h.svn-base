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

// Stub out the "FILE" type until we support real file IO
//typedef	void	FILE;

#include "PalmTypes.h"
#include <FileStream.h>//PALM file streaming functions
#include <StringMgr.h> //PALM string functions
//#include <StdIOPalm.h>//PALM stdio functions
#include <MemoryMgr.h>//PALM Memory Functions
#include <MemGlue.h> //PALM MemGluePtrNew function
// Set this flag to indicate to not use standard file calls instead use PALM File Streaming functions.
#define FNX_OVERRIDE_FILE_CALLS

#ifndef SEEK_SET
#define SEEK_SET	0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR	1
#endif
#ifndef SEEK_END
#define SEEK_END	2
#endif
/****************************************
Palm Specific Defines
*****************************************/
#define	PALM_FILE_EXT		".pdb"

/****************************************
General I/O 
****************************************/
#define FNX_STDIN           stdin
#define FNX_STDOUT          stdout
#define FNX_STDERR          stderr

/*********************************************
Memory Function Mappings
*********************************************/
#define FNXB_MALLOC         fnxmalloc
#define FNXB_CALLOC         fnxcalloc
#define FNXB_REALLOC        fnxrealloc
#define FNXB_FREE           fnxfree

//#define malloc 				MemPtrNew
//#define free 				MemPtrFree
//#define memset				MemSet
#define memmove				MemMove
#define memcmp				MemCmp
#define memcpy				MemMove
//#define calloc				MemPtrCalloc

#define malloc				fnxmalloc
#define calloc				fnxcalloc
#define realloc				fnxrealloc
#define free				fnxfree

#ifndef FNX_EXPORT
#define FNX_EXPORT(a,b)     __declspec(dllexport) a b
#endif

//typedef void * voidPtr;
//typedef unsigned int size_t;
//typedef size_t  usize;

FNX_EXPORT(voidPtr, fnxmalloc(usize size));
FNX_EXPORT(voidPtr, fnxcalloc( usize size, usize value ) );
FNX_EXPORT(voidPtr, fnxrealloc(voidPtr ptr, usize size) );
FNX_EXPORT(void, fnxfree(voidPtr ptr));

/****************************************
General Mappings
****************************************/
#define FNX_FOPENWITHPATH   FNX_FOPEN
#define FNX_TIMESTRUCT      time_t
#define FNX_TM_TIMESTRUCT   struct tm

//typedef unsigned long	fpos_t;

/*********************************************
Diagnostic Function Mappings
*********************************************/
#define FNXB_ASSERT         assert

/****************************************
PALM Standard Lib Mappings
****************************************/
#define atoi				StrAToI

#ifndef qsort
#define qsort				fnxaqsort
//#define FNX_BUILD_QSORT  //use Fonix defined qsort
#define FNXA_BUILD_QSORT
FNX_EXPORT(void, fnxaqsort(void * base, size_t num, size_t width,int (* compare)(const void * elem1, const void * elem2)));
#endif

#ifndef bsearch
#define bsearch				fnxabsearch
#define FNX_PALM_BUILD_BSEARCH
FNX_EXPORT(void*, fnxabsearch(const void * key, const void * base, size_t num, size_t width,short (* compare)(const void * elem1, const void * elem2, Int32 other)));
#endif

#ifndef sscanf
#define sscanf				fnxsscanf
#define FNX_BUILD_SSCANF
FNX_EXPORT(int, fnxsscanf(const char * buffer, const char * format, ...));
#endif

//#ifndef fnxaTime
//#define fnxaTime			fnxtime
//#define FNX_BUILD_TIME
//FNX_EXPORT( FNX_TIMESTRUCT, fnxtime( FNX_TIMESTRUCT *pResult ) );
//#endif

//#ifndef fnxaLocaltime
//#define fnxaLocaltime		fnxlocaltime
//#define FNX_BUILD_LOCALTIME
//FNX_EXPORT( struct tm*, fnxlocaltime( const time_t *timer ) );
//#endif


#ifndef memset
#define memset				fnxmemset
#define FNX_BUILD_MEMSET
FNX_EXPORT(void *, fnxmemset(void *dest, int c, UInt32 count));
#endif

#ifndef memchr
#define memchr				fnxmemchr
#define FNX_BUILD_MEMCHR
FNX_EXPORT(void *, fnxmemchr( const void *s, int c, size_t n));
#endif

#ifndef memcpy
#define memcpy				fnxmemcpy
#define FNX_BUILD_MEMCPY
FNX_EXPORT(void *, fnxmemcpy( void *dest, const void *src, size_t count ));
#endif

#ifndef sleep
#define sleep				fnxsleep
#define FNX_BUILD_SLEEP
FNX_EXPORT(void, fnxsleep(int delay));
#endif

#ifndef abs
#define abs					fnxabs
#define FNX_BUILD_ABS
FNX_EXPORT(int, fnxabs(int n));
#endif

#ifndef strncat
#define strncat				fnxstrncat
#define FNX_BUILD_STRNCAT
FNX_EXPORT(char *, fnxstrncat( char *d, const char *s, size_t l));
#endif

#ifndef strtok
#define strtok				fnxstrtok
#define FNX_BUILD_STRTOK
FNX_EXPORT(char *, fnxstrtok(char *s, const char *ct));
//FNX_EXPORT(char *,fnxstrtok(char *string, const char *token));
#endif

#ifndef strcpy
#define strcpy				StrCopy
#endif

#ifndef strcmp
#define strcmp				fnxstrcmp
#define FNX_BUILD_STRCMP
FNX_EXPORT(int, fnxstrcmp(const char *s1, const char *s2));
#endif

#ifndef strdup
//#define strdup				fnxstrdup
#define strdup				fnxaStrdup //Use Fonix defined strdup
#define FNXA_BUILD_STRDUP  
//#define FNX_BUILD_STRDUP //Use my strdup
//FNX_EXPORT(char *, fnxstrdup (const char *s));
#endif

#ifndef sprintf
#define sprintf				StrPrintF
#endif

#ifndef toupper
#define toupper				fnxatoupper
#define FNXA_BUILD_TOUPPER
FNX_EXPORT(int, fnxatoupper (int c));
#endif

#ifndef tolower
#define tolower				fnxatolower
#define FNXA_BUILD_TOLOWER
FNX_EXPORT(int, fnxatolower (int c));
#endif

#ifndef perror
#define perror 				fnxaperror
#define FNXA_BUILD_PERROR
FNX_EXPORT(void, fnxaperror(const char *pText));
#endif

/****************************************
Memfile native file routins
****************************************/
#ifndef FNX_OVERRIDE_FILE_CALLS
#define FNX_MF_FOPEN         fopen
#define FNX_MF_FCLOSE        fclose
#define FNX_MF_UNGETC        ungetc
#define FNX_MF_GETC          getc
#define FNX_MF_FGETS         fgets
#define FNX_MF_FWRITE        fwrite
#define FNX_MF_FREAD         fread
#define FNX_MF_FSEEK         fseek
#define FNX_MF_FTELL         ftell
#define FNX_MF_REWIND        rewind
#define FNX_MF_FEOF          feof
#define FNX_MF_CLEARERR      clearerr
#define FNX_MF_FLUSH         fflush
#define FNX_MF_VFPRINTF      vfprintf
#define FNX_MF_FSCANF        fscanf
#define FNX_MF_FPUTC         fputc
#define FNX_MF_FPUTS         fputs
#define FNX_MF_FSETPOS       fsetpos
#define FNX_MF_FERROR        ferror
#endif  // not FNX_OVERRIDE_FILE_CALLS
#define FNX_MF_REMOVE       remove
#define FNX_MF_RENAME       rename
#define FNX_MF_FINDDATA_T   _finddata_t
#define FNX_MF_FINDFIRST    _findfirst
#define FNX_MF_FINDNEXT     _findnext
#define FNX_MF_FINDCLOSE    _findclose



/****************************************
Unicode Function Mappings
****************************************/
// File I/O Function Mappings
#ifndef FNX_OVERRIDE_FILE_CALLS
#define FNXW_FOPEN          _wfopen
#define FNXW_FCLOSE         fclose
#define FNXW_FGETC          fgetwc
#define FNXW_UNGETC         ungetc
#define FNXW_FGETS          fgetws
#define FNXW_FREAD          fread
#define FNXW_FWRITE         fwrite
#define FNXW_FSEEK          fseek
#define FNXW_FTELL          ftell
#define FNXW_REWIND         fnxaRewind // Map to narrow, no need to re-implement
#define FNXW_FFLUSH         fflush
#define FNXW_FEOF           feof
#define FNXW_FPRINTF        fwprintf
#define FNXW_FPUTC          fputwc
#define FNXW_FPUTS          fputws
#define FNXW_FSCANF         fwscanf
#define FNXW_FSETPOS        fsetpos
#define FNXW_FERROR         ferror
#define FNXW_CLEARERR       clearerr
#define FNXW_REMOVE         fnxwRemove
#define FNXW_RENAME         fnxwRename
#endif  // not FNX_OVERRIDE_FILE_CALLS
#define FNXW_FINDFIRST      _wfindfirst
#define FNXW_FINDNEXT       _wfindnext
#define FNXW_FINDCLOSE      _findclose
// Standard I/O Function Mappings
// Character Manipulation Mappings
//#define FNXW_TOLOWER(_c)    towlower(_c)
//#define FNXW_TOUPPER(_c)    towupper(_c)
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
#define FNXW_ISASCII(_c)    iswascii(_c)
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
#define FNXW_STRTOK         wcstok
#define FNXW_STRUPR         _wcsupr // Fonix ANSI Extension, if you do not define FNXW_STRUPR or FNXA_STRUPR ANSI equivalents will be used
#define FNXW_STRLWR         _wcslwr // Fonix ANSI Extension, if you do not define FNXW_STRLWR or FNXA_STRLWR ANSI equivalents will be used
#define FNXW_BSEARCH        bsearch  // Fonix ANSI Extension, if you do not define FNXW_BSEARCH or FNXA_BSEARCH ANSI equivalents will be used

// String I/O Function Mappings
#define FNXW_SPRINTF        swprintf
#define FNXW_SSCANF         swscanf
// Time Function Mappings
#define FNXW_TIME           fnxaTime          // Map to narrow, no need to re-implement
#define FNXW_STRFTIME       fnxwStrftime
#define FNXW_LOCALTIME      fnxaLocaltime     // Map to narrow, no need to re-implement
#define FNXW_DIFFTIME       fnxaDifftime      // Map to narrow, no need to re-implement
#define FNXW_DIFFTIMEDAYS   fnxaDiffTimeDays  // Convenience function, tells you the difference in days between 2 FNX_TIMESTRUCT structures (Map to narrow, no need to re-implement)
#define FNXW_SLEEP          Sleep             // Sleep for milliseconds
// Data Conversion Function Mappings
#define FNXW_ATOI           _wtoi
#define FNXW_ATOL           _wtol
#define FNXW_ATOF           _wtof

/********************************************
Narrow Function Mappings
********************************************/
// File I/O Function Mappings
#ifndef FNX_OVERRIDE_FILE_CALLS
#define FNXA_FOPEN          MemFileOpen
#define FNXA_FCLOSE         MemFileClose
#define FNXA_FGETC          MemFileGetc
#define FNXA_UNGETC         MemFileUngetc
#define FNXA_FGETS          MemFileGets
#define FNXA_FREAD          MemFileRead
#define FNXA_FWRITE         MemFileWrite
#define FNXA_FSEEK          MemFileSeek
#define FNXA_FTELL          MemFileTell
#define FNXA_REWIND         MemFileRewind
#define FNXA_FFLUSH         MemFileFlush
#define FNXA_FEOF           MemFileEof
//#define FNXA_FPRINTF        MemFilePrintf
#define FNXA_FPUTC          MemFilePutc
#define FNXA_FPUTS          MemFilePuts
#define FNXA_FSCANF         MemFileScanf
#define FNXA_FSETPOS        MemFileSetpos
#define FNXA_FERROR         MemFileError
#define FNXA_CLEARERR       MemFileClearerr
#define FNXA_REMOVE         MemFileRemove
#define FNXA_RENAME         MemFileRename
#endif  // not FNX_OVERRIDE_FILE_CALLS
#define FNXA_FINDFIRST      MemFileFindFirst
#define FNXA_FINDNEXT       MemFileFindNext
#define FNXA_FINDCLOSE      MemFileFindClose
// Standard I/O Function Mappings
//#define FNXA_PRINTF         printf
// Character Manipulation Mappings
//#define FNXA_TOLOWER(_c)    (char)towlower((wchar_t)_c)
//#define FNXA_TOUPPER(_c)    (char)towupper((wchar_t)_c)
// Character Classification Definitions
#define FNXA_ISALPHA(_c)    (_c >= 'a' && _c <= 'z' || _c >= 'A' && _c <= 'Z')
#define FNXA_ISUPPER(_c)    (_c >= 'A' && _c <= 'Z')
#define FNXA_ISLOWER(_c)    (_c >= 'a' && _c <= 'z')
#define FNXA_ISDIGIT(_c)    (_c >= '0' && _c <= '9')
#define FNXA_ISXDIGIT(_c)   isxdigit(_c)
#define FNXA_ISSPACE(_c)    (_c == ' ' || _c == '\t' || _c == '\r' || _c == '\n' || _c == '\v' || _c == '\f')
#define FNXA_ISPUNCT(_c)    ispunct(_c)
#define FNXA_ISALNUM(_c)    isalnum(_c)
#define FNXA_ISPRINT(_c)    (_c >= 32 && _c <= 126)	// 32=' ' and 126='~' in ASCII
#define FNXA_ISGRAPH(_c)    isgraph(_c)
#define FNXA_ISCNTRL(_c)    iscntrl(_c)
#define FNXA_ISASCII(_c)    isascii(_c)

// String Manipulation Mappings
//#define FNXA_STRDUP         _strdup  // Fonix ANSI Extension. Use the Fonix version so that it can keep track of memory through Allocate.
//#define FNXA_STRDUP         strdup  // Fonix ANSI Extension. Use the Fonix version so that it can keep track of memory through Allocate.
#define FNXA_STRCAT         StrCat
#define FNXA_STRCHR         StrChr
//#define FNXA_STRREV         _strrev
#define FNXA_STRCMP         strcmp
#define FNXA_STRICMP        StrCaselessCompare  // Fonix ANSI Extension, if you do not define FNXW_STRICMP or FNXA_STRICMP ANSI equivalents will be used
#define FNXA_STRCPY         StrCopy
//#define FNXA_STRCSPN        strcspn
#define FNXA_STRERROR       strerror
#define FNXA_STRLEN         StrLen
#define FNXA_STRNCAT        strncat
#define FNXA_STRNCMP        StrNCompare
#define FNXA_STRNCPY        StrNCopy
//#define FNXA_STRNICMP       _strnicmp  // Fonix ANSI Extension, if you do not define FNXW_STRNICMP or FNXA_STRNICMP ANSI equivalents will be used
//#define FNXA_STRPBRK        strpbrk
//#define FNXA_STRRCHR        strrchr
//#define FNXA_STRSPN         strspn
#define FNXA_STRSTR         StrStr
#define FNXA_STRTOK         strtok
//#define FNXA_STRUPR         _strupr   // Fonix ANSI Extension, if you do not define FNXW_STRUPR or FNXA_STRUPR ANSI equivalents will be used
//#define FNXA_STRLWR         strlwr   // Fonix ANSI Extension, if you do not define FNXW_STRLWR or FNXA_STRLWR ANSI equivalents will be used
#define FNXA_BSEARCH        bsearch  // Fonix ANSI Extension, if you do not define FNXW_BSEARCH or FNXA_BSEARCH ANSI equivalents will be used

// String I/O Function Mappings
#define FNXA_SPRINTF        sprintf
#define FNXA_SSCANF         sscanf
// Time Function Mappings
#define FNXA_TIME           fnxaTime
#define FNXA_STRFTIME       fnxaStrftime
#define FNXA_LOCALTIME      fnxaLocaltime
#define FNXA_DIFFTIME       fnxaDifftime
#define FNXA_DIFFTIMEDAYS   fnxaDiffTimeDays  // Convenience function, tells you the difference in days between 2 FNX_TIMESTRUCT structures
#define FNXA_SLEEP          sleep             // Sleep for milliseconds
// Data Conversion Function Mappings
#define FNXA_ATOI           StrAToI
#define FNXA_ATOL           atol
#define FNXA_ATOF           atof

#define FNX_PERROR			perror

#define _A_SUBDIR	1
#define _A_FILE		2
#define _A_UNKNOWN	3

#define fwrite FNXA_FWRITE
#define fopen FNXA_FOPEN
#define fclose FNXA_FCLOSE

#ifndef FNXA_TOUPPER
#define FNXA_TOUPPER fnxatoupper
#define FNXA_BUILD_TOUPPER
	FNX_EXPORT(int, fnxatoupper(int c));
#endif

#ifndef FNXA_PRINTF
#define FNXA_PRINTF fnxaprintf
#define FNX_BUILD_PRINTF
	FNX_EXPORT(int, fnxaprintf(const char * pText, ...));
#endif

#ifndef FNXA_STRLWR
#define FNXA_STRLWR fnxastrlwr  //my strlwr
#define FNX_BUILD_STRLWR
	FNX_EXPORT(char *, fnxastrlwr(char *string));
#endif

#ifdef FNX_OVERRIDE_FILE_CALLS

#ifndef FNXA_FREAD
#	define FNXA_FREAD fnxafread
#	define FNXA_BUILD_FREAD
	FNX_EXPORT( usize, fnxafread(void *pBuf,usize size,usize count,FILE *pStream) );
#endif
#ifndef FNXW_FREAD
#	define FNXW_FREAD fnxwfread
#	define FNXW_BUILD_FREAD
	FNX_EXPORT( usize, fnxwfread(void *pBuf,usize size,usize count,FILE *pStream) );
#endif

//#ifndef FNXA_FFLUSH
#	define FNXA_FFLUSH fnxfflush
#	define FNXA_BUILD_FFLUSH
	FNX_EXPORT(int, fnxfflush(FILE *pStream));
//#endif

#ifndef FNXA_FCLOSE
#	define FNXA_FCLOSE fnxfclose
#	define FNXA_BUILD_FCLOSE
	FNX_EXPORT( int, fnxfclose( FILE * fp ) );
#endif
#ifndef FNXW_FCLOSE
#	define FNXW_FCLOSE fnxfclose
#	define FNXA_BUILD_FCLOSE
	FNX_EXPORT( int, fnxfclose( FILE * fp ) );
#endif

#ifndef FNXA_FOPEN
#	define FNXA_FOPEN fnxafopen
#	define FNXA_BUILD_FOPEN
	FNX_EXPORT( FILE *, fnxafopen(const char *pName, const char *pFlags) );
#endif
//#ifndef FNXW_FOPEN
//#	define FNXW_FOPEN fnxwfopen
//#	define FNXW_BUILD_FOPEN
//	FNX_EXPORT( FILE *, fnxwfopen(const wchar_t *pName, const wchar_t *pFlags) );
//#endif
#ifndef FNXA_FSEEK
#	define FNXA_FSEEK  fnxfseek
#	define FNXA_BUILD_FSEEK
	FNX_EXPORT( int, fnxfseek(FILE *,long,int) );
#endif
#ifndef FNXW_FSEEK
#	define FNXW_FSEEK  fnxfseek
#	define FNXA_BUILD_FSEEK
	FNX_EXPORT( int, fnxfseek(FILE *,long,int) );
#endif

#ifndef FNXA_FTELL
#	define FNXA_FTELL  fnxftell
#	define FNXA_BUILD_FTELL
	FNX_EXPORT( DWORD, fnxftell(FILE *) );
#endif

#ifndef FNXW_FTELL
#	define FNXW_FTELL  fnxftell
#	define FNXW_BUILD_FTELL
	FNX_EXPORT( DWORD, fnxftell(FILE *) );
#endif

#ifndef FNXA_FWRITE
#	define FNXA_FWRITE  fnxafwrite
#	define FNXA_BUILD_FWRITE
	FNX_EXPORT( usize, fnxafwrite(const void *pBuf, usize size, usize count, FILE * pStream) );
#endif

#ifndef FNXA_FERROR
#	define FNXA_FERROR  fnxaferror
#	define FNXA_BUILD_FERROR
	FNX_EXPORT( int, fnxaferror( FILE *stream) );
#endif

#ifndef FNXA_FEOF
#	define FNXA_FEOF  fnxaferror
#	define FNXA_BUILD_FEOF
	FNX_EXPORT( int, fnxafeof( FILE *stream) );
#endif

#ifndef FNXA_REWIND
#	define FNXA_REWIND  fnxaRewind
#	define FNXA_BUILD_REWIND
	FNX_EXPORT( void, fnxaRewind( FILE *stream ) );
#endif

#ifndef FNXA_FGETS
#	define FNXA_FGETS  fnxafgets
#	define FNXA_BUILD_FGETS
	FNX_EXPORT( char *, fnxafgets( char *string, int n, FILE *stream ) );
#endif

#ifndef FNXA_FGETC
#	define FNXA_FGETC  fnxafgetc
#	define FNXA_BUILD_FGETC
	FNX_EXPORT( int, fnxafgetc( FILE *stream ) );
#endif

#ifndef FNXA_FPUTC
#	define FNXA_FPUTC  fnxafputc
#	define FNXA_BUILD_FPUTC
	FNX_EXPORT( int, fnxafputc(int c, FILE *stream ) );
#endif

#ifndef FNXA_UNGETC
#	define FNXA_UNGETC  fnxaungetc
#	define FNXA_BUILD_UNGETC
	FNX_EXPORT( int, fnxaungetc( int c, FILE *stream ) );
#endif

#ifndef FNXA_FPRINTF
#	define FNXA_FPRINTF  fnxafprintf
#	define FNXA_BUILD_FPRINTF
	FNX_EXPORT( int, fnxafprintf( FILE *fp, const char *format, ... ) );
#endif

#ifndef FNXA_FSCANF
#	define FNXA_FSCANF  fnxafscanf
#	define FNXA_BUILD_FSCANF
	FNX_EXPORT( int, fnxafscanf( FILE *fp, const char *format, ... ) );
#endif

#ifndef FNXA_REMOVE
#define FNXA_REMOVE		fnxaremove
#define FNXA_BUILD_REMOVE
	FNX_EXPORT( int, fnxaremove( const char *path) );
#endif

#else
	#ifndef FNXW_FOPEN
	#	define FNXW_FOPEN fnxwfopen
	#	define FNXW_BUILD_FOPEN
		FNX_EXPORT( FILE *, fnxwfopen(const wchar_t *pName, const wchar_t *pFlags) );
	#endif

#endif  // FNX_OVERRIDE_FILE_CALLS


// #define MAX_PATH	FILENAME_MAX

#ifndef _MAX_PATH
#define _MAX_PATH	256
#endif
#ifndef MAX_PATH
#define MAX_PATH	_MAX_PATH
#endif


struct _finddata_t {
  int attrib;
  char name[MAX_PATH];
  char path[MAX_PATH];
};

struct tm {
        int tm_sec;     /* seconds after the minute - [0,59] */
        int tm_min;     /* minutes after the hour - [0,59] */
        int tm_hour;    /* hours since midnight - [0,23] */
        int tm_mday;    /* day of the month - [1,31] */
        int tm_mon;     /* months since January - [0,11] */
        int tm_year;    /* years since 1900 */
        int tm_wday;    /* days since Sunday - [0,6] */
        int tm_yday;    /* days since January 1 - [0,365] */
        int tm_isdst;   /* daylight savings time flag */
};

long _findfirst(char *dname,struct _finddata_t *FileData);
int _findnext(long FileId,struct _finddata_t *FileData);
long _findclose(long FileId);

#if defined(__cplusplus)
extern "C" {
#endif

//FNX_EXPORT(double, fnxaDiffTimeDays( FNX_TIMESTRUCT timer1, FNX_TIMESTRUCT timer2 ) );
FNX_EXPORT( voidPtr, EmbMalloc( usize size ) );
FNX_EXPORT( voidPtr, EmbCalloc( usize num, usize size ) );
FNX_EXPORT( voidPtr, EmbRealloc( voidPtr ptr, usize size ) );
FNX_EXPORT( void, EmbFree( voidPtr ptr ) );

#if defined(__cplusplus)
}
#endif

#endif // __FNXEXSTDLIB_H__
