/*****************************************************

  $Date: 3/23/04 1:30p $
  $Revision: 4 $

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
General Structure Mappings
****************************************/
#define FNX_TIMESTRUCT			time_t
#define FNX_TM_TIMESTRUCT		struct tm

/*********************************************
Memory Function Mappings
*********************************************/
//#define FNXB_MALLOC		fnxMalloc
//#define FNXB_CALLOC		fnxCalloc
//#define FNXB_REALLOC		fnxRealloc
//#define FNXB_FREE			fnxFree
//#define FNX_MEM_SIZE		_msize
#define FNXB_MALLOC			malloc
#define FNXB_CALLOC			calloc
#define FNXB_REALLOC		realloc
#define FNXB_FREE			free

/*********************************************
Diagnostic Function Mappings
*********************************************/
#define FNXB_ASSERT		assert

// File I/O Stream Mappings
#define FNX_STDIN				stdin
#define FNX_STDOUT				stdout
#define FNX_STDERR				stderr

/****************************************
Memfile native file routins
****************************************/
#define FNX_MF_FOPEN        mfopen
#define FNX_MF_FCLOSE       mfclose
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
#define FNX_MF_FINDDATA_T   _finddata_t
#define FNX_MF_FINDFIRST    _findfirst
#define FNX_MF_FINDNEXT     _findnext
#define FNX_MF_FINDCLOSE    _findclose
#define FNX_MF_GETFILELEN(f) _filelength( _fileno(f) )

/****************************************
Unicode Function Mappings
****************************************/
// File I/O Function Mappings
#define FNXW_FOPEN			FnxS1C33WFOpen
#define FNXW_FCLOSE			wfclose
#define FNXW_FEOF			wfeof
#define FNXW_FFLUSH			wfflush
#define FNXW_FGETC			wfgetwc
#define FNXW_FGETS			wfgetws
#define FNXW_FPRINTF		wfwprintf
#define FNXW_FPUTC			wfputwc
#define FNXW_FPUTS			wfputws
#define FNXW_FREAD			wfread
#define FNXW_FSCANF			wfwscanf
#define FNXW_FSEEK			wfseek
#define FNXW_FSETPOS		wfsetpos
#define FNXW_FTELL			wftell
#define FNXW_FWRITE			wfwrite
#define FNXW_FERROR			wferror
#define FNXW_CLEARERR		wfclearerr
#define FNXW_REWIND			wfrewind
#define FNXW_FINDFIRST		_wfindfirst
#define FNXW_FINDNEXT		_wfindnext
#define FNXW_FINDCLOSE		_wfindclose
// Standard I/O Function Mappings
#define FNXW_GETC			getwc
#define FNXW_GETCHAR		getwchar
#define FNXW_GETS			_getws
#define FNXW_PRINTF			wprintf
#define FNXW_PUTC			putwc
#define FNXW_PUTCHAR		putwchar
#define FNXW_PUTS			_putws
#define FNXW_SCANF			wscanf
#define FNXW_SETBUF			setbuf
#define FNXW_UNGETC			ungetwc
// Character Manipulation Mappings
#define FNXW_TOLOWER(_c)	towlower(_c)
#define FNXW_TOUPPER(_c)	towupper(_c)
// Character Classification Definitions
#define FNXW_ISALPHA(_c)	iswalpha(_c)
#define FNXW_ISUPPER(_c)	iswupper(_c)
#define FNXW_ISLOWER(_c)	iswlower(_c)
#define FNXW_ISDIGIT(_c)	iswdigit(_c)
#define FNXW_ISXDIGIT(_c)	iswxdigit(_c)
#define FNXW_ISSPACE(_c)	iswspace(_c)
#define FNXW_ISPUNCT(_c)	iswpunct(_c)
#define FNXW_ISALNUM(_c)	iswalnum(_c)
#define FNXW_ISPRINT(_c)	iswprint(_c)
#define FNXW_ISGRAPH(_c)	iswgraph(_c)
#define FNXW_ISCNTRL(_c)	iswcntrl(_c)
#define FNXW_ISASCII(_c)	iswascii(_c)
// String Manipulation Mappings
//#define FNXW_STRDUP		_wcsdup  // Fonix ANSI Extension. Use the Fonix version so that it can keep track of memory through Allocate.
#define FNXW_STRCAT			wcscat
#define FNXW_STRCHR			wcschr
#define FNXW_STRREV			_wcsrev
#define FNXW_STRCMP			wcscmp
#define FNXW_STRICMP		_wcsicmp  // Fonix ANSI Extension, if you do not define FNXW_STRICMP or FNXA_STRICMP ANSI equivalents will be used
//#define FNXW_STRCPY			wcscpy
#define FNXW_STRCSPN		wcscspn
#define FNXW_STRERROR		strerror
#define FNXW_STRLEN			wcslen
#define FNXW_STRNCAT		wcsncat
#define FNXW_STRNCMP		wcsncmp
#define FNXW_STRNCPY		wcsncpy
#define FNXW_STRNICMP		_wcsnicmp // Fonix ANSI Extension, if you do not define FNXW_STRNICMP or FNXA_STRNICMP ANSI equivalents will be used
#define FNXW_STRPBRK		wcspbrk
#define FNXW_STRRCHR		wcsrchr
#define FNXW_STRSPN			wcsspn
#define FNXW_STRSTR			wcsstr
#define FNXW_STRTOK			wcstok
#define FNXW_STRUPR			_wcsupr  // Fonix ANSI Extension, if you do not define FNXW_STRUPR or FNXA_STRUPR ANSI equivalents will be used
#define FNXW_STRLWR			_wcslwr  // Fonix ANSI Extension, if you do not define FNXW_STRLWR or FNXA_STRLWR ANSI equivalents will be used
#define FNXW_BSEARCH		bsearch  // Fonix ANSI Extension, if you do not define FNXW_BSEARCH or FNXA_BSEARCH ANSI equivalents will be used
// String I/O Function Mappings
#define FNXW_SPRINTF		swprintf
#define FNXW_SSCANF			swscanf
// Time Function Mappings
#define FNXW_TIME			time
#define FNXW_STRFTIME		wcsftime
#define FNXW_LOCALTIME		localtime
#define FNXW_DIFFTIME		difftime
#define FNXW_DIFFTIMEDAYS	fnxaDiffTimeDays	// Convenience function, tells you the difference in days between 2 FNX_TIMESTRUCT structures (map to Narrow, no need to re-implement)
#define FNXW_SLEEP			Sleep				// Sleep for milliseconds
// Data Conversion Function Mappings
#define FNXW_ATOI			wtoi
#define FNXW_ATOL			wtol
#define FNXW_ATOF			wtof

// File I/O Function Mappings
#define FNX_FOPENWITHPATH	FNX_FOPEN
#define FNX_FSCREATE		MemStreamCreate
#define FNX_FSDESTROY		MemStreamDestroy
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

// Standard I/O Function Mappings
#define FNXA_GETC			getc
#define FNXA_GETCHAR		getchar
#define FNXA_GETS			gets
#define FNXA_PRINTF			FnxS1C33DummyPrintf
#define FNXA_PUTC			putc
#define FNXA_PUTCHAR		putchar
#define FNXA_PUTS			puts
#define FNXA_SCANF			scanf
#define FNXA_SETBUF			setbuf
#define FNXA_UNGETC			MemFileUngetc
// Character Manipulation Mappings
//#define FNXA_TOLOWER(_c)	tolower(_c)
//#define FNXA_TOUPPER(_c)	toupper(_c)
// Character Classification Definitions
//#define FNXA_ISALPHA(_c)	isalpha(_c)
//#define FNXA_ISUPPER(_c)	isupper(_c)
//#define FNXA_ISLOWER(_c)	islower(_c)
//#define FNXA_ISDIGIT(_c)	isdigit(_c)
//#define FNXA_ISXDIGIT(_c)	isxdigit(_c)
//#define FNXA_ISSPACE(_c)	isspace(_c)
//#define FNXA_ISPUNCT(_c)	ispunct(_c)
//#define FNXA_ISALNUM(_c)	isalnum(_c)
//#define FNXA_ISPRINT(_c)	isprint(_c)
//#define FNXA_ISGRAPH(_c)	isgraph(_c)
//#define FNXA_ISCNTRL(_c)	iscntrl(_c)
//#define FNXA_ISASCII(_c)	isascii(_c)
// String Manipulation Mappings
//#define FNXA_STRDUP			_strdup	// Fonix ANSI Extension. Use the Fonix version so that it can keep track of memory through Allocate.
#define FNXA_STRCAT				strcat
#define FNXA_STRCHR				strchr
//#define FNXA_STRREV			strrev
#define FNXA_STRCMP				strcmp
//#define FNXA_STRICMP			_stricmp // Fonix ANSI Extension, if you do not define FNXW_STRICMP or FNXA_STRICMP ANSI equivalents will be used
#define FNXA_STRCPY				strcpy
#define FNXA_STRCSPN			strcspn
//#define FNXA_STRERROR			strerror
#define FNXA_STRLEN				strlen
#define FNXA_STRNCAT			strncat
#define FNXA_STRNCMP			strncmp
#define FNXA_STRNCPY			strncpy
//#define FNXA_STRNICMP			_strnicmp // Fonix ANSI Extension, if you do not define FNXW_STRNICMP or FNXA_STRNICMP ANSI equivalents will be used
//#define FNXA_STRPBRK			strpbrk
#define FNXA_STRRCHR			strrchr
#define FNXA_STRSPN				strspn
#define FNXA_STRSTR				strstr
#define FNXA_STRTOK				strtok
//#define FNXA_STRUPR				_strupr // Fonix ANSI Extension, if you do not define FNXW_STRUPR or FNXA_STRUPR ANSI equivalents will be used
//#define FNXA_STRLWR				_strlwr // Fonix ANSI Extension, if you do not define FNXW_STRLWR or FNXA_STRLWR ANSI equivalents will be used
#define FNXA_BSEARCH			bsearch	// Fonix ANSI Extension, if you do not define FNXW_BSEARCH or FNXA_BSEARCH ANSI equivalents will be used
// String I/O Function Mappings
#define FNXA_SPRINTF			sprintf
#define FNXA_SSCANF				sscanf
// Time Function Mappings
#define FNXA_TIME				time
//#define FNXA_STRFTIME			strftime
//#define FNXA_LOCALTIME			localtime
//#define FNXA_DIFFTIME			difftime
#define FNXA_DIFFTIMEDAYS		fnxaDiffTimeDays	// Convenience function, tells you the difference in days between 2 FNX_TIMESTRUCT structures
//#define FNXA_SLEEP				Sleep				// Sleep for milliseconds
// Data Conversion Function Mappings
#define FNXA_ATOI				atoi
//#define FNXA_ATOL				atol
//#define FNXA_ATOF				atof


#if defined(__cplusplus)
extern "C" {
#endif

//FNX_EXPORT(double, fnxaDiffTimeDays( FNX_TIMESTRUCT timer1, FNX_TIMESTRUCT timer2 ) );
#if defined(__MWERKS__)
long _ftol(float fp);
#endif

FNX_EXPORT( voidPtr, Allocate( usize size ) );
FNX_EXPORT( voidPtr, AllocateBlks( usize num, usize size ) );
FNX_EXPORT( voidPtr, Reallocate( voidPtr ptr, usize size ) );
FNX_EXPORT( void, Deallocate( voidPtr ptr ) );
FNX_EXPORT( void, delay( long ) );

#if !defined(FNXA_GETFILELEN) || !defined(FNX_MF_GETFILELEN)
	#if !defined(FNXA_GETFILELEN)
		#	define FNXA_GETFILELEN	fnxaGetFileLength
	#elif !defined(FNX_MF_GETFILELEN)
		#	define FNX_MF_GETFILELEN	fnxaGetFileLength
	#endif
	#	define FNX_BUILD_GETFILELEN
	/***********************************************************
	Returns the length of the file.
	***********************************************************/
	FNX_EXPORT( long, fnxaGetFileLength( FILE * fp ) );
#endif // _GETFILELEN

#if defined(__cplusplus)
}
#endif

#endif
