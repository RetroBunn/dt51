/*****************************************************
This file maps the unicode and narrow function defines
created in fnxstdlib.h to default function names.

If you want to add new functions to this list be sure to
add a define to both the unicode and narrow sections below,
you will also need to add a FNX_<x> define to the
fnxstdlib.h file.

FNXW_<x> = Unicode function
FNXA_<x> = Narrow function
*****************************************************/

#if !defined(__FNXEXSTDLIB_H__)
#define __FNXEXSTDLIB_H__

/****************************************
General I/O
****************************************/
#define FNX_STDIN           stdin
#define FNX_STDOUT          stdout
#define FNX_STDERR          stderr

#define FNX_PERROR			perror

/*********************************************
Memory Function Mappings
*********************************************/
//#define FNX_MEM_SIZE		_msize
# define FNXB_MALLOC		malloc
# define FNXB_CALLOC		calloc
# define FNXB_REALLOC		realloc
# define FNXB_FREE			free


/*********************************************
Diagnostic Function Mappings
*********************************************/
#ifdef _QNX_DEBUG_BUILD_
#define FNXB_ASSERT         assert
#else
#define FNXB_ASSERT
#endif


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
#define FNXW_FOPEN          fopen
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
#define FNXW_STRUPR         _wcsupr  // Fonix ANSI Extension, if you do not define FNXW_STRUPR or FNXA_STRUPR ANSI equivalents will be used
#define FNXW_STRLWR         _wcslwr  // Fonix ANSI Extension, if you do not define FNXW_STRLWR or FNXA_STRLWR ANSI equivalents will be used
#define FNXW_BSEARCH        bsearch  // Fonix ANSI Extension, if you do not define FNXW_BSEARCH or FNXA_BSEARCH ANSI equivalents will be used
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
#define FNXA_STRICMP        strcasecmp  // Fonix ANSI Extension, if you do not define FNXW_STRICMP or FNXA_STRICMP ANSI equivalents will be used
#define FNXA_STRCPY         strcpy
#define FNXA_STRCSPN        strcspn
#define FNXA_STRERROR       strerror
#define FNXA_STRLEN         strlen
#define FNXA_STRNCAT        strncat
#define FNXA_STRNCMP        strncmp
#define FNXA_STRNCPY        strncpy
#define FNXA_STRNICMP       strncasecmp  // Fonix ANSI Extension, if you do not define FNXW_STRNICMP or FNXA_STRNICMP ANSI equivalents will be used
#define FNXA_STRPBRK        strpbrk
#define FNXA_STRRCHR        strrchr
#define FNXA_STRSPN         strspn
#define FNXA_STRSTR         strstr
#define FNXA_STRTOK         strtok
#define FNXA_STRUPR         _strupr   // Fonix ANSI Extension, if you do not define FNXW_STRUPR or FNXA_STRUPR ANSI equivalents will be used
#define FNXA_STRLWR         _strlwr   // Fonix ANSI Extension, if you do not define FNXW_STRLWR or FNXA_STRLWR ANSI equivalents will be used
#define FNXA_BSEARCH        bsearch  // Fonix ANSI Extension, if you do not define FNXW_BSEARCH or FNXA_BSEARCH ANSI equivalents will be used
// String I/O Function Mappings
#define FNXA_SPRINTF        sprintf
#define FNXA_SSCANF         sscanf
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

//FNX_EXPORT(double, fnxaDiffTimeDays( FNX_TIMESTRUCT timer1, FNX_TIMESTRUCT timer2 ) );

#if defined(__cplusplus)
}
#endif

#endif
