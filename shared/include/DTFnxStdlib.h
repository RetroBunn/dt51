/*******************************************************
This file maps the platform independant FNX_<x> symbols 
to either unicode or narrow functions.  If you want to 
use unicode define FNXUNICODE in your project. 
If you want to add a function to the list be sure to add 
it to both the unicode and narrow sections below. You 
should also add function mappings for the new function 
in plat/<platform>/include/dtfnxexstdlib.h.

  $Date: 2/29/04 2:54p $
  $Revision: 14 $

NOTE:
  All function mappings below use the parameters and behave 
  as the ANSI standard definitions describe.  In the case 
  of FONIX ANSI EXTENSION'S The functions will require the 
  parameters and behave as the Windows equivalent functions. 
*/
#ifndef __DTFNXSTDLIB_H__
#define __DTFNXSTDLIB_H__

/* Put the directory where your platform's dtfnxexstdlib.h exists into your include path. */
#include "DTFnxExStdlib.h"

/*********************************************
Byte Swapping Function Mappings
*********************************************/
//# define FNX_PLATISLITTLEENDIAN    FNXB_PLATISLITTLEENDIAN
//# define FNX_BYTESWAP16            FNXB_BYTESWAP16 
//# define FNX_BYTESWAP32            FNXB_BYTESWAP32 
//# define FNX_BLOCKBYTESWAP16       FNXB_BLOCKBYTESWAP16
//# define FNX_BLOCKBYTESWAP32       FNXB_BLOCKBYTESWAP32

/*********************************************
Debug printf statement
*********************************************/
#if 0
#if defined(DEBUG) || defined(_DEBUG)
	#ifdef _WIN32_WCE
		#define MAX_STRING_LEN 260
		#define FNXA_DBG_PRINTF(In_Args) \
		{ \
			char cString[MAX_STRING_LEN]; \
			wchar_t wString[MAX_STRING_LEN]; \
			FNX_SPRINTF( cString, (const char *)In_Args ); \
			MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, cString, MAX_STRING_LEN, wString, MAX_STRING_LEN ); \
			NKDbgPrintfW( _T("%s"), wString ); \
		} // end of FNXA_DBG_PRINTF
		#define FNXW_DBG_PRINTF( a ) NKDbgPrintfW( a )
	#else  // _WIN32_WCE
		//#define FNXA_DBG_PRINTF( a ) printf( (const char *) a )
		#define FNXA_DBG_PRINTF( a )
		//#define FNXW_DBG_PRINTF( a ) wprintf( (const wchar_t *) a )
		#define FNXW_DBG_PRINTF( a )
	#endif  // _WIN32_WCE
#else  // not DEGUG
	#define FNXA_DBG_PRINTF( a )
	#define FNXW_DBG_PRINTF( a )
#endif  // DEBUG
#endif
/*********************************************
Memory Function Mappings
*********************************************/
# define FNX_MALLOC   FNXB_MALLOC
# define FNX_CALLOC   FNXB_CALLOC
# define FNX_REALLOC  FNXB_REALLOC
# define FNX_FREE     FNXB_FREE

/*********************************************
Diagnostic Function Mappings
*********************************************/
# define FNX_ASSERT        FNXB_ASSERT


/*********************************************
Unicode Function Mappings
*********************************************/
#ifdef FNXUNICODE
// File I/O Function Mappings
# define FNX_FOPEN        FNXW_FOPEN
# define FNX_FCLOSE       FNXW_FCLOSE
# define FNX_FEOF         FNXW_FEOF
# define FNX_FFLUSH       FNXW_FFLUSH
# define FNX_FGETC        FNXW_FGETC
# define FNX_FGETS        FNXW_FGETS
# define FNX_FPRINTF      FNXW_FPRINTF
# define FNX_FPUTC        FNXW_FPUTC
# define FNX_FPUTS        FNXW_FPUTS
# define FNX_FREAD        FNXW_FREAD
# define FNX_FSCANF       FNXW_FSCANF
# define FNX_FSEEK        FNXW_FSEEK
# define FNX_FSETPOS      FNXW_FSETPOS
# define FNX_FTELL        FNXW_FTELL
# define FNX_FWRITE       FNXW_FWRITE
# define FNX_FERROR       FNXW_FERROR
# define FNX_CLEARERR     FNXW_CLEARERR
# define FNX_REWIND       FNXW_REWIND
# define FNX_RENAME       FNXW_RENAME
# define FNX_REMOVE       FNXW_REMOVE
# define FNX_FINDDATA_T   FNXW_FINDDATA_T
# define FNX_FINDFIRST    FNXW_FINDFIRST
# define FNX_FINDNEXT     FNXW_FINDNEXT
# define FNX_FINDCLOSE    FNXW_FINDCLOSE
// Standard I/O Function Mappings
# define FNX_GETC         FNXW_GETC
# define FNX_GETCHAR      FNXW_GETCHAR
# define FNX_GETS         FNXW_GETS
# define FNX_PRINTF       FNXW_PRINTF
# define FNX_PUTC         FNXW_PUTC
# define FNX_PUTCHAR      FNXW_PUTCHAR
# define FNX_PUTS         FNXW_PUTS
# define FNX_SCANF        FNXW_SCANF
# define FNX_SETBUF       FNXW_SETBUF
# define FNX_UNGETC       FNXW_UNGETC
// Character Manipulation Mappings
# define FNX_TOLOWER(_c)  FNXW_TOLOWER(_c)
# define FNX_TOUPPER(_c)  FNXW_TOUPPER(_c)
// Character Classification Definitions
# define FNX_ISALPHA(_c)  FNXW_ISALPHA(_c)
# define FNX_ISUPPER(_c)  FNXW_ISUPPER(_c)
# define FNX_ISLOWER(_c)  FNXW_ISLOWER(_c)
# define FNX_ISDIGIT(_c)  FNXW_ISDIGIT(_c)
# define FNX_ISXDIGIT(_c) FNXW_ISXDIGIT(_c)
# define FNX_ISSPACE(_c)  FNXW_ISSPACE(_c)
# define FNX_ISPUNCT(_c)  FNXW_ISPUNCT(_c)
# define FNX_ISALNUM(_c)  FNXW_ISALNUM(_c)
# define FNX_ISPRINT(_c)  FNXW_ISPRINT(_c)
# define FNX_ISGRAPH(_c)  FNXW_ISGRAPH(_c)
# define FNX_ISCNTRL(_c)  FNXW_ISCNTRL(_c)
# define FNX_ISASCII(_c)  FNXW_ISASCII(_c)
// String Manipulation Mappings
# define FNX_STRDUP       FNXW_STRDUP // Fonix ANSI Extension, if you do not define FNXW_STRDUP or FNXA_STRDUP ANSI equivalents will be used
# define FNX_STRCAT       FNXW_STRCAT
# define FNX_STRCHR       FNXW_STRCHR
# define FNX_STRCMP       FNXW_STRCMP
# define FNX_STRICMP      FNXW_STRICMP // Fonix ANSI Extension, if you do not define FNXW_STRICMP or FNXA_STRICMP ANSI equivalents will be used
# define FNX_STRCPY       FNXW_STRCPY
# define FNX_STRCSPN      FNXW_STRCSPN
# define FNX_STRERROR     FNXW_STRERROR
# define FNX_STRLEN       FNXW_STRLEN
# define FNX_STRNCAT      FNXW_STRNCAT
# define FNX_STRNCMP      FNXW_STRNCMP
# define FNX_STRNCPY      FNXW_STRNCPY
# define FNX_STRNICMP     FNXW_STRNICMP // Fonix ANSI Extension, if you do not define FNXW_STRNICMP or FNXA_STRNICMP ANSI equivalents will be used
# define FNX_STRPBRK      FNXW_STRPBRK
# define FNX_STRRCHR      FNXW_STRRCHR
# define FNX_STRREV       FNXW_STRREV   // Fonix ANSI Extension, if you do not define FNXW_STRREV or FNXA_STRREV ANSI equivalents will be used
# define FNX_STRSPN       FNXW_STRSPN
# define FNX_STRSTR       FNXW_STRSTR
# define FNX_STRTOK       FNXW_STRTOK
# define FNX_STRUPR       FNXW_STRUPR   // Fonix ANSI Extension, if you do not define FNXW_STRUPR or FNXA_STRUPR ANSI equivalents will be used
# define FNX_STRLWR       FNXW_STRLWR   // Fonix ANSI Extension, if you do not define FNXW_STRLWR or FNXA_STRLWR ANSI equivalents will be used
# define FNX_BSEARCH      FNXW_BSEARCH  // Fonix ANSI Extension, if you do not define FNXW_BSEARCH or FNXA_BSEARCH ANSI equivalents will be used
// String I/O Function Mappings
# define FNX_SPRINTF      FNXW_SPRINTF
# define FNX_SSCANF        FNXW_SSCANF
// Time Function Mappings
# define FNX_TIME         FNXW_TIME
# define FNX_STRFTIME     FNXW_STRFTIME
# define FNX_LOCALTIME    FNXW_LOCALTIME
# define FNX_DIFFTIME     FNXW_DIFFTIME
# define FNX_DIFFTIMEDAYS FNXW_DIFFTIMEDAYS  // Convenience function, tells you the difference in days between 2 FNX_TIMESTRUCT structures
# define FNX_SLEEP        FNXW_SLEEP
// Data Conversion Function Mappings
# define FNX_ATOI         FNXW_ATOI
# define FNX_ATOL         FNXW_ATOL
# define FNX_ATOF         FNXW_ATOF

/*************************************************
Narrow Function Mappings
*************************************************/
#else
// File I/O Function Mappings
# define FNX_FOPEN        FNXA_FOPEN
# define FNX_FCLOSE       FNXA_FCLOSE
# define FNX_FEOF         FNXA_FEOF
# define FNX_FFLUSH       FNXA_FFLUSH
# define FNX_FGETC        FNXA_FGETC
# define FNX_FGETS        FNXA_FGETS
# define FNX_FPRINTF      FNXA_FPRINTF
# define FNX_FPUTC        FNXA_FPUTC
# define FNX_FPUTS        FNXA_FPUTS
# define FNX_FREAD        FNXA_FREAD
# define FNX_FSCANF       FNXA_FSCANF
# define FNX_FSEEK        FNXA_FSEEK
# define FNX_FSETPOS      FNXA_FSETPOS
# define FNX_FTELL        FNXA_FTELL
# define FNX_FWRITE       FNXA_FWRITE
# define FNX_FERROR       FNXA_FERROR
# define FNX_CLEARERR     FNXA_CLEARERR
# define FNX_REWIND       FNXA_REWIND
# define FNX_RENAME       FNXA_RENAME
# define FNX_REMOVE       FNXA_REMOVE
# define FNX_FINDDATA_T   FNXA_FINDDATA_T
# define FNX_FINDFIRST    FNXA_FINDFIRST
# define FNX_FINDNEXT     FNXA_FINDNEXT
# define FNX_FINDCLOSE    FNXA_FINDCLOSE
// Standard I/O Function Mappings
# define FNX_GETC         FNXA_GETC
# define FNX_GETCHAR      FNXA_GETCHAR
# define FNX_GETS         FNXA_GETS
# define FNX_PRINTF       FNXA_PRINTF
# define FNX_PUTC         FNXA_PUTC
# define FNX_PUTCHAR      FNXA_PUTCHAR
# define FNX_PUTS         FNXA_PUTS
# define FNX_SCANF        FNXA_SCANF
# define FNX_SETBUF       FNXA_SETBUF
# define FNX_UNGETC       FNXA_UNGETC
// Character Manipulation Mappings
# define FNX_TOLOWER(_c)  FNXA_TOLOWER(_c)
# define FNX_TOUPPER(_c)  FNXA_TOUPPER(_c)
// Character Classification Definitions
# define FNX_ISALPHA(_c)  FNXA_ISALPHA(_c)
# define FNX_ISUPPER(_c)  FNXA_ISUPPER(_c)
# define FNX_ISLOWER(_c)  FNXA_ISLOWER(_c)
# define FNX_ISDIGIT(_c)  FNXA_ISDIGIT(_c)
# define FNX_ISXDIGIT(_c) FNXA_ISXDIGIT(_c)
# define FNX_ISSPACE(_c)  FNXA_ISSPACE(_c)
# define FNX_ISPUNCT(_c)  FNXA_ISPUNCT(_c)
# define FNX_ISALNUM(_c)  FNXA_ISALNUM(_c)
# define FNX_ISPRINT(_c)  FNXA_ISPRINT(_c)
# define FNX_ISGRAPH(_c)  FNXA_ISGRAPH(_c)
# define FNX_ISCNTRL(_c)  FNXA_ISCNTRL(_c)
# define FNX_ISASCII(_c)  FNXA_ISASCII(_c)
// String Manipulation Mappings
# define FNX_STRDUP       FNXA_STRDUP // Fonix ANSI Extension, if you do not define FNXW_STRDUP or FNXA_STRDUP ANSI equivalents will be used
# define FNX_STRCAT       FNXA_STRCAT
# define FNX_STRCHR       FNXA_STRCHR
# define FNX_STRCMP       FNXA_STRCMP
# define FNX_STRICMP      FNXA_STRICMP // Fonix ANSI Extension, if you do not define FNXW_STRICMP or FNXA_STRICMP ANSI equivalents will be used
# define FNX_STRCPY       FNXA_STRCPY
# define FNX_STRCSPN      FNXA_STRCSPN
# define FNX_STRERROR     FNXA_STRERROR
# define FNX_STRLEN       FNXA_STRLEN
# define FNX_STRNCAT      FNXA_STRNCAT
# define FNX_STRNCMP      FNXA_STRNCMP
# define FNX_STRNCPY      FNXA_STRNCPY
# define FNX_STRNICMP     FNXA_STRNICMP // Fonix ANSI Extension, if you do not define FNXW_STRNICMP or FNXA_STRNICMP ANSI equivalents will be used
# define FNX_STRPBRK      FNXA_STRPBRK
# define FNX_STRRCHR      FNXA_STRRCHR
# define FNX_STRREV       FNXA_STRREV   // Fonix ANSI Extension, if you do not define FNXW_STRREV or FNXA_STRREV ANSI equivalents will be used
# define FNX_STRSPN       FNXA_STRSPN
# define FNX_STRSTR       FNXA_STRSTR
# define FNX_STRTOK       FNXA_STRTOK
# define FNX_STRUPR       FNXA_STRUPR  // Fonix ANSI Extension, if you do not define FNXW_STRUPR or FNXA_STRUPR ANSI equivalents will be used
# define FNX_STRLWR       FNXA_STRLWR  // Fonix ANSI Extension, if you do not define FNXW_STRLWR or FNXA_STRLWR ANSI equivalents will be used
# define FNX_BSEARCH      FNXA_BSEARCH  // Fonix ANSI Extension, if you do not define FNXW_BSEARCH or FNXA_BSEARCH ANSI equivalents will be used
// String I/O Function Mappings
# define FNX_SPRINTF      FNXA_SPRINTF
# define FNX_SSCANF       FNXA_SSCANF
// Time Function Mappings
# define FNX_TIME         FNXA_TIME
# define FNX_STRFTIME     FNXA_STRFTIME
# define FNX_LOCALTIME    FNXA_LOCALTIME
# define FNX_DIFFTIME     FNXA_DIFFTIME
# define FNX_DIFFTIMEDAYS FNXA_DIFFTIMEDAYS  // Convenience function, tells you the difference in days between 2 FNX_TIMESTRUCT structures
# define FNX_SLEEP        FNXA_SLEEP
// Data Conversion Function Mappings
# define FNX_ATOI         FNXA_ATOI
# define FNX_ATOL         FNXA_ATOL
# define FNX_ATOF         FNXA_ATOF
#endif




#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////
// Fonix ANSI Extensions (using all ANSI code)
///////////////////////////////////////////////////////////////
#ifndef FNXW_STRDUP
#  define FNXW_STRDUP   fnxwStrdup
#  define FNXW_BUILD_STRDUP
   /***********************************************************
   Allocates a copy of a string.
   [in]  pStr     string to copy
   [out] return      a copy of the string (created using Allocate, must be free'd with a call to Deallocate)
   ***********************************************************/
   FNX_EXPORT( wchar_t *, fnxwStrdup(const wchar_t *pStr) );
#endif

#ifndef FNXW_STRNICMP
#  define FNXW_STRNICMP fnxwStrnicmp
#  define FNXW_BUILD_STRNICMP
   /***********************************************************
   Performs a case insensitive comparison of two strings.
   [in]  string1     string to compare
   [in]  string2     string to compare
   [out] count    the number of characters to compare
   [out] return      0 if the strings are equal, less than 0 if string1 is less than string2, greater than 0 if string1 is greater than string2
   ***********************************************************/
   FNX_EXPORT( int, fnxwStrnicmp( const wchar_t *string1, const wchar_t *string2, size_t count ) );
#endif

#ifndef FNXW_STRICMP
#  define FNXW_STRICMP  fnxwStricmp
#  define FNXW_BUILD_STRICMP
   /***********************************************************
   Performs a case insensitive comparison of two strings.
   [in]  string1     string to compare
   [in]  string2     string to compare
   [out] return      0 if equal, less than 0 if string1 is less than string2, greater than 0 if string1 is greater than string2
   ***********************************************************/
   FNX_EXPORT( int, fnxwStricmp( const wchar_t *string1, const wchar_t *string2 ) );
#endif

#ifndef FNXW_STRUPR
#  define FNXW_STRUPR   fnxwStrupr
#  define FNXW_BUILD_STRUPR
   /***********************************************************
   Performs an in place conversion of a string to upper case
   [in]  string      the string to convert
   [out] return      pointer to the converted string (same as input pointer)
   ***********************************************************/
   FNX_EXPORT( char *, fnxwStrupr( wchar_t *string ) );
#endif

#ifndef FNXW_STRLWR
#  define FNXW_STRLWR   fnxwStrlwr
#  define FNXW_BUILD_STRLWR
   /***********************************************************
   Performs an in place conversion of a string to lower case
   [in]  string      the string to convert
   [out] return      pointer to the converted string (same as input pointer)
   ***********************************************************/
   FNX_EXPORT( wchar_t *, fnxwStrlwr( wchar_t *string ) );
#endif

#ifndef FNXW_STRREV
#  define FNXW_STRREV   fnxwStrrev
#  define FNXW_BUILD_STRREV
   /***********************************************************
   Performs an in place reverse of all characters in a string
   [in]  string      the string to convert
   [out] return      pointer to the converted string (same as input pointer)
   ***********************************************************/
   FNX_EXPORT( wchar_t *, fnxwStrrev( wchar_t *string ) );
#endif

#ifndef FNXW_ISASCII
#  define FNXW_ISASCII  fnxwIsascii
#  define FNXW_BUILD_ISASCII
   /***********************************************************
   Performs an in place reverse of all characters in a string
   [in]  string      the string to convert
   [out] return      pointer to the converted string (same as input pointer)
   ***********************************************************/
   FNX_EXPORT( int, fnxwIsascii( wchar_t c ) );
#endif

#ifndef FNXA_STRDUP
#  define FNXA_STRDUP   fnxaStrdup
#  define FNXA_BUILD_STRDUP
   /***********************************************************
   Allocates a copy of a string.
   [in]  pStr     string to copy
  [out] return      a copy of the string (created using Allocate, must be free'd with a call to Deallocate)
   ***********************************************************/
   FNX_EXPORT( char *, fnxaStrdup(const char *pStr) );
#endif

#ifndef FNXA_TOLOWER
#  define FNXA_TOLOWER  fnxaTolower
#  define FNXA_BUILD_TOLOWER
   /***********************************************************
   Convert a character to lower case [Fonix: even if international]
   [in]  c           character to convert
   [out] return      c, converted to lower case
   ***********************************************************/
   FNX_EXPORT( int, fnxaTolower( int c ));
#endif

#ifndef FNXA_TOUPPER
#  define FNXA_TOUPPER  fnxaToupper
#  define FNXA_BUILD_TOUPPER
   /***********************************************************
   Convert a character to upper case [Fonix: even if international]
   [in]  c           character to convert
   [out] return      c, converted to upper case
   ***********************************************************/
   FNX_EXPORT( int, fnxaToupper( int c ));
#endif

#ifndef FNXA_STRNICMP
#  define FNXA_STRNICMP fnxaStrnicmp
#  define FNXA_BUILD_STRNICMP
  /***********************************************************
   Performs a case insensitive comparison of two strings.
   [in]  string1     string to compare
   [in]  string2     string to compare
   [out] count    the number of characters to compare
   [out] return      0 if the strings are equal, less than 0 if string1 is less than string2, greater than 0 if string1 is greater than string2
   ***********************************************************/
   FNX_EXPORT( int, fnxaStrnicmp( const char *string1, const char *string2, size_t count ) );
#endif

#ifndef FNXA_STRICMP
#  define FNXA_STRICMP  fnxaStricmp
#  define FNXA_BUILD_STRICMP
   /***********************************************************
   Performs a case insensitive comparison of two strings.
   [in]  string1     string to compare
   [in]  string2     string to compare
   [out] return      0 if equal, less than 0 if string1 is less than string2, greater than 0 if string1 is greater than string2
   ***********************************************************/
   FNX_EXPORT( int, fnxaStricmp( const char *string1, const char *string2 ) );
#endif

#ifndef FNXA_STRUPR
#  define FNXA_STRUPR   fnxaStrupr
#  define FNXA_BUILD_STRUPR
   /***********************************************************
   Performs an in place conversion of a string to upper case
   [in]  string      the string to convert
   [out] return      pointer to the converted string (same as input pointer)
   ***********************************************************/
   FNX_EXPORT( char *, fnxaStrupr( char *string ) );
#endif

#ifndef FNXA_STRLWR
#  define FNXA_STRLWR   fnxaStrlwr
#  define FNXA_BUILD_STRLWR
   /***********************************************************
   Performs an in place conversion of a string to lower case
   [in]  string      the string to convert
   [out] return      pointer to the converted string (same as input pointer)
   ***********************************************************/
   FNX_EXPORT( char *, fnxaStrlwr( char *string ) );
#endif

#ifndef FNXA_STRREV
#  define FNXA_STRREV   fnxaStrrev
#  define FNXA_BUILD_STRREV
   /***********************************************************
   Performs an in place reverse of all characters in a string
   [in]  string      the string to convert
   [out] return      pointer to the converted string (same as input pointer)
   ***********************************************************/
   FNX_EXPORT( char *, fnxaStrrev( char *string ) );
#endif

#ifndef FNXA_ISASCII
#  define FNXA_ISASCII  fnxaIsascii
#  define FNXA_BUILD_ISASCII
   /***********************************************************
   Performs an ?
   [in]  ?
   [out] ?
   ***********************************************************/
   FNX_EXPORT( int, fnxaIsascii( int c ) );
#endif


#ifndef FNXA_STRRCHR
#  define FNXA_STRRCHR  fnxaStrrchr
#  define FNXA_BUILD_STRRCHR
   /***********************************************************
   Scan a string for the last occurrence of a character.
   [in]  string     to search in.
   [in]  character  to search for.
   [out] return     pointer to char found or NULL if not found.
   ***********************************************************/
   FNX_EXPORT( char *, fnxaStrrchr(const char * string, int) );
#endif

#ifndef FNXA_STRPBRK
#  define FNXA_STRPBRK  fnxaStrpbrk
#  define FNXA_BUILD_STRPBRK
   /***********************************************************
   Find the first substring.
   [in]  string      Null-terminated string to search 
   [in]  strCharSet  Null-terminated character set to search in.
   [out] return      the index of the first character in string 
   that does belong to the set of characters in strCharSet. 
   ***********************************************************/
   FNX_EXPORT( char *, fnxaStrpbrk(const char * string, const char * strCharSet) );
#endif

#ifndef FNXA_STRSPN
#  define FNXA_STRSPN   fnxaStrspn
#  define FNXA_BUILD_STRSPN
   /***********************************************************
   Find the first substring.
   [in]  string      Null-terminated string to search 
   [in]  strCharSet  Null-terminated character set to search in.
   [out] return      the index of the first character in string 
   that does not belong to the set of characters in strCharSet. 
   ***********************************************************/
   FNX_EXPORT( size_t, fnxaStrspn(const char * string, const char * strCharSet) );
#endif


//#if !defined FNXA_BSEARCH || !defined FNXW_BSEARCH
//#  define FNXA_BSEARCH  fnxaBSearch
//#  define FNX_BUILD_BSEARCH
//   /***********************************************************
//   Performs a binary search
//   [in]  ...
//   [out] ...
//   ***********************************************************/
//   FNX_EXPORT( void *, fnxaBSearch( const void *key, const void *base, size_t num, size_t width, int (__cdecl *compare)(const void *, const void *) ) );
//#endif

#ifndef FNXW_WCTOMB
#define wctomb		        fnxawctomb
#define FNXW_WCTOMB fnxawctomb

#define FNXW_BUILD_WCTOMB
  FNX_EXPORT(int, fnxawctomb (char *s, wchar_t wchar));
#endif

#ifndef FNXW_WCSTOMBS
//#define wcstombs		        fnxawcstombs	// This function does not work correctly
#define FNXW_WCSTOMBS fnxawcstombs
#define FNXW_BUILD_WCSTOMBS
   FNX_EXPORT( size_t, fnxawcstombs (char *s, const wchar_t *pwcs, size_t n));
#endif

#ifndef FNXW_ATOI
#define FNXW_ATOI	fnxawtoi
#define FNXW_BUILD_ATOI
   FNX_EXPORT( int, fnxawtoi(const wchar_t *str));
#endif

#ifndef FNXW_STRCAT
#define FNXW_STRCAT fnxawstrcat
#define FNXW_BUILD_STRCAT
   FNX_EXPORT(wchar_t *, fnxwstrcat(wchar_t * dest,const wchar_t * src));
#endif



/***********************************************************
Performs FNX_STRNCPY and guarantees that dest is null terminated
***********************************************************/
//FNX_EXPORT( char *, FNX_STRNCPY_NULL( char *dest, const char *src, int n ) );

/***********************************************************
Default Byte Swapping Mappings
***********************************************************/
//#ifndef FNXB_PLATISLITTLEENDIAN
//#   define FNXB_PLATISLITTLEENDIAN   LittleEndian
//#endif
//#ifndef FNXB_BYTESWAP16
//#   define FNXB_BYTESWAP16           ByteSwap16
//#endif
//#ifndef FNXB_BYTESWAP32
//#   define FNXB_BYTESWAP32           ByteSwap32
//#endif
//#ifndef FNXB_BLOCKBYTESWAP16
//#   define FNXB_BLOCKBYTESWAP16      BlockByteSwap16   
//#endif
//#ifndef FNXB_BLOCKBYTESWAP32
//#   define FNXB_BLOCKBYTESWAP32      BlockByteSwap32
//#endif

#if defined(__cplusplus)
}
#endif

#endif  // __DTFNXSTDLIB_H__
