/*H_HEADER_FILE***************************************************************
FILE        : FnxFiles.h
DESC        : 
TABS        : 3
OWNER       : Fonix
DATE CREATED: 

(C) Copyright 1999,2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 2/27/04 4:47p $
  $Revision: 12 $

*END_HEADER******************************************************************/
#ifndef FILES_H
#define FILES_H

#ifdef USE_MEMFILE_IO

#include "FnxPlatform.h"
#include "DTFnxStdlib.h"

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef OS_UNIX
#	include <glob.h>
#endif


#ifndef FNXG_MEMF_VERIFY_DEFINED
	#define FNXG_MEMF_VERIFY_DEFINED
	static const UDWORD FNXG_MEMF_VERIFY = (UDWORD)0x76664d46;	// Equivalent to 'vfMF'
																// will show up as 'FMfv' in a memory dump
#endif  // FNXG_MEMF_VERIFY_DEFINED
typedef struct mf_iobuf 
{
   UDWORD    _IsMfPtr;
   char *    _ptr;
   SDWORD    _cnt;
   char *    _base;
   SDWORD    _flag;
   SDWORD    _file;
   SDWORD    _charbuf;
   SDWORD    _bufsiz;
   char *    _tmpfname;
   FILE *    _fp;
   void *    _privateMap;
} MF_FILE;

#define MF_EOF          (-1)
#define MF_SEEK_CUR     1
#define MF_SEEK_END     2
#define MF_SEEK_SET     0
#define MF_IOREAD       0x0001
#define MF_IOWRT        0x0002
#define MF_IOFBF        0x0000
#define MF_IOLBF        0x0040
#define MF_IONBF        0x0004
#define MF_IOMYBUF      0x0008
#define MF_IOEOF        0x0010
#define MF_IOERR        0x0020
#define MF_IOSTRG       0x0040
#define MF_IORW         0x0080
#define MF_IOAPPEND     0x0200
#define MF_CREATE       (MF_IOWRT | MF_IORW)
#define MF_READ         (MF_IOREAD | MF_IORW)
#define MF_WRITE        (MF_IOWRT | MF_IORW | MF_IOAPPEND)
#define MF_FILENAME_MAX 260
#define MEM_STRUCT      0xF000
#define MAX_WBUF_SIZE   512

#ifndef EOF
#define EOF          MF_EOF
#endif

#ifndef SEEK_CUR
#define SEEK_CUR     MF_SEEK_CUR
#endif

#ifndef SEEK_END
#define SEEK_END     MF_SEEK_END
#endif

#ifndef SEEK_SET
#define SEEK_SET     MF_SEEK_SET
#endif

// from IO.H
#define FNX_ATRIB_NORMAL       0x00    /* Normal file - No read/write restrictions */
#define FNX_ATRIB_RDONLY       0x01    /* Read only file */
#define FNX_ATRIB_HIDDEN       0x02    /* Hidden file */
#define FNX_ATRIB_SYSTEM       0x04    /* System file */
#define FNX_ATRIB_SUBDIR       0x10    /* Subdirectory */
#define FNX_ATRIB_ARCH         0x20    /* Archive file */

#ifndef FNXG_MEMFFF_VERIFY_DEFINED
	#define FNXG_MEMFFF_VERIFY_DEFINED
	static const UDWORD FNXG_MEMFFF_VERIFY = (UDWORD)0x66664d46;	// Equivalent to 'ffMF'
																// will show up at 'FMff' in a memory dump
#endif  // FNXG_MEMFFF_VERIFY_DEFINED

struct FNXA_FINDDATA_T
{
	UDWORD  _IsMfFfPtr;
   void *  pMap;
   SDWORD  _flag;
	int     attrib;					// * used in the public API
	long    nOSRet;					// * used in the public API (sort of)
	char    name[FNX_MAX_PATH];		// * used in the public API
	char    input[FNX_MAX_PATH];
#ifdef OS_UNIX
//*** these elements are private
	glob_t	glob;
	int		next;
#endif
};
struct FNXW_FINDDATA_T
{
	UDWORD  _IsMfFfPtr;
	void *  pMap;
   SDWORD  _flag;
  int     attrib;
   long    nOSRet;
#ifdef OS_QNXNTO // GBringhurst
    char name[FNX_MAX_PATH];
    char input[FNX_MAX_PATH];
#else
  wchar_t name[FNX_MAX_PATH];
  wchar_t input[FNX_MAX_PATH];
#endif
};

#if defined(__cplusplus)
extern "C" {
#endif

FNX_EXPORT( FILE *,  MemFileOpenPrivate( const void * pMemFileTable, const char * pName, const char * pFlags ) );
FNX_EXPORT( long,   MemFileFindFirstPrivate( const void * pMemFileTable, struct FNXA_FINDDATA_T * lpaFindFileDat ) );

FNX_EXPORT( FILE *, MemStreamCreate(FILE *fp) );
FNX_EXPORT( void, MemStreamDestroy(FILE *fp) );
FNX_EXPORT( FILE *,  MemFileOpen( const char *, const char * ) );
FNX_EXPORT( SDWORD,  MemFileClose( FILE * ) );
FNX_EXPORT( SDWORD,  MemFileGetc( FILE * ) );
FNX_EXPORT( wchar_t,  MemFileGetwc( FILE * ) );
FNX_EXPORT( SDWORD,  MemFileUngetc( SDWORD, FILE * ) );
FNX_EXPORT( char *,  MemFileGets( char *, SDWORD, FILE * ) );
FNX_EXPORT( wchar_t *,  MemFileGetws( wchar_t *, SDWORD, FILE * ) );
FNX_EXPORT( usize,   MemFileRead( voidPtr, usize, usize, FILE * ) );
FNX_EXPORT( usize,   MemFileWrite( const voidPtr, usize, usize, FILE * ) );
FNX_EXPORT( SDWORD,  MemFileSeek( FILE *, SDWORD, int ) );
FNX_EXPORT( SDWORD,  MemFileTell( FILE * ) );
FNX_EXPORT( void,    MemFileRewind( FILE * ) );
FNX_EXPORT( SDWORD,  MemFileFlush( FILE * ) );
FNX_EXPORT( SDWORD,  MemFileEof( FILE * ) );
FNX_EXPORT( int,     MemFilePutc( int, FILE * ) );
FNX_EXPORT( int,     MemFilePuts( const char *, FILE * ) );
FNX_EXPORT( int,     MemFileSetpos( FILE *, fpos_t * ) );
FNX_EXPORT( int,     MemFileError( FILE * ) );
FNX_EXPORT( void,    MemFileClearerr( FILE * ) ); 
FNX_EXPORT( int,     MemFileRemove( const char * ) );
FNX_EXPORT( int,     MemFileRename( const char *, const char * ) );
FNX_EXPORT( int,     MemFilePrintf( FILE *, const char *, ... ) );
FNX_EXPORT( int,     MemFileScanf( FILE *, const char *, ... ) );
FNX_EXPORT( long,    MemFileFindFirst( const char *lpaRootName, struct FNXA_FINDDATA_T * lpaFindFileData ) );
FNX_EXPORT( int,     MemFileFindNext( long nFFRtn, struct FNXA_FINDDATA_T * lpaFindFileData ) );
FNX_EXPORT( int,     MemFileFindClose( long nFFRtn ) );

#if defined(__cplusplus)
}
#endif

#endif  //USE_MEMFILE_IO

#endif // FILES_H
