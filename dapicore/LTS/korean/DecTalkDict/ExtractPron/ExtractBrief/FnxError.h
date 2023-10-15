/*H_HEADER_FILE***************************************************************
FILE        : Error.h
DESC        : error handling data and functions
TABS        : 3
OWNER       : fonix
DATE CREATED: 

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 2/27/04 3:33p $
  $Revision: 5 $

*END_HEADER******************************************************************/
#ifndef  ERROR_H
#define  ERROR_H

#ifndef OK
#define OK 0
#define _NO_ERROR 0
#define _ERROR -1
#endif

/*  Error codes  */
#define  FNX_OK               0x0000
#define  FNX_ERROR            0x0001
#define  FNX_OUTOFMEMORY      0x0002
#define  FNX_INVALIDARG       0x0004
#define  FNX_ABORT            0x0008
#define  FNX_UNINITIALIZED    0x0010
#define  FNX_BUSY             0x0020
#define  FNX_INSUFFICIENTDATA 0x0040

#define  FNX_FILEOPEN         0x0100
#define  FNX_FILEREAD         0x0200
#define  FNX_FILEWRITE        0x0400

#define  FILE_NOT_FOUND    -1
#define  FILE_IO_ERROR     -2
#define  UNKNOWN_RECORD    -3
#define  OUT_OF_MEMORY     -4
#define  VERSION_ERROR     -5
#define  INVALID_FILE      -6
#define  FILE_OPEN_ERROR   -7
#define  STRING_LEN_ERROR  -8

typedef struct errMessage  _errMessage;
#define SIZE_ERRMESSAGE    sizeof(_errMessage)
typedef struct errMessage  xhuge *errMessagePtr;

struct errMessage
{
   errMessagePtr pNext, pPrev;
   char     *sMessage;
   SDWORD   iErrNum;
};

#if defined(__cplusplus)
extern "C" {
#endif

FNX_EXPORT( void, ErrorSet( SDWORD err, char *sMessage ) );
FNX_EXPORT( errMessagePtr, ErrorGet( void ) );
FNX_EXPORT( void, ErrorClearAll( void ) );
FNX_EXPORT( void, Message(void *pVoid, char *fmt, ...) );

#ifdef HAVE_STDIO_H
//#include <stdio.h>
extern void ErrorDisplayMessages(FILE *fpStream);
extern void ErrorDisplay(FILE *fpStream, errMessagePtr pErr);
#endif

#if defined(__cplusplus)
}
#endif

#endif
