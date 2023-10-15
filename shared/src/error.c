/*C_HEADER_FILE****************************************************************
FILE        :  error.c
DESC        :  report error values
TABS        :  3
OWNER       :  
DATE CREATED:  18 Oct 1999

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/28/05 1:59p $
  $Revision: 6 $

*END_HEADER*******************************************************************/

#if defined(_WINDOWS) || defined(UNDER_CE)
#include <windows.h>
#include <winuser.h>
#endif

#include "FnxPlatform.h"
#include "DTFnxStdlib.h"
#include "FnxAllocate.h"

/*  GlobalCommon routines are used by Embedded SDK code; not used by CORETECH */
#ifdef GLOBAL_COMMON
#include "GlobalCommon.h"
#endif

#ifdef EPSON
#include <smcvals.h>
#endif

#include <stdarg.h>


#define MAX_ERRSTRING   2048


#if !defined(UNDER_CE)

enum {ERR_OK, ERR_WARNING, ERR_CRITICAL};
typedef struct tagError
{
   SDWORD   iError;
   SDWORD   iErrLevel;
   char  *sMessage;
} ERROR_DATA;

/*  Ignore these error messages until we figure out what they ought to be  */
const ERROR_DATA pError[] = {
   {0,      ERR_OK,  "no error"},
   {-1,     ERR_CRITICAL,  "mfccdeltaCompute failed"},
   {-2,     ERR_CRITICAL,  "Int_melFrame failed"},
   {-10,    ERR_CRITICAL,  "Out of memory"},
   {-11,    ERR_CRITICAL,  "File IO error"},
   {-100,   ERR_CRITICAL,  "ConfigFileIO.c:  Can't read config file"},  // ConfigFileIO.c

   {0,0,NULL}
};
#endif
#ifndef GLOBAL_COMMON
static errMessagePtr gpErrMessages=NULL;
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;ErrorGet
 * DESC:    Get a pointer to the head of the error messages linked list
 * IN:      none
 * OUT:     none
 * RETURN:  pointer to an errMessage structure
 * NOTES:   
 *END_HEADER***************************/
errMessagePtr ErrorGet( void )
{
#ifdef GLOBAL_COMMON
   GlobalCommonPtr	gp = GetGlobalCommonPtr();
	return (errMessagePtr)gp->pErrMessages;
#else
   return gpErrMessages;
#endif
}


/*FUNCTION_HEADER**********************
 * NAME:    ;ErrorSet
 * DESC:    Create an error structure and add it to the
            linked list of error structures.
 * IN:      err - error number
            sMessage - message (if NULL, see if there is a message corresponding to err)
 * OUT:     
 * RETURN:  
 * NOTES:   
 *END_HEADER***************************/
void ErrorSet(SDWORD err, char *sMessage)
{
#ifdef GLOBAL_COMMON
	GlobalCommonPtr	gp = GetGlobalCommonPtr();
#endif
   errMessagePtr pErr;

   /*  Create an errMessage structure  */
   pErr = (errMessagePtr)FNX_CALLOC(1,SIZE_ERRMESSAGE);

   /*  Get the error code  */
   pErr->iErrNum = err;

   if(sMessage)
      pErr->sMessage = FNX_STRDUP(sMessage);

   /*  Add this message to the linked list  */
#ifdef GLOBAL_COMMON
   	if(gp->pErrMessages == NULL)
		gp->pErrMessages = pErr;
#else
   if(gpErrMessages == NULL)
      gpErrMessages = pErr;
#endif
   else
   {
      /*  Put the latest error message on the top of the stack  */
#ifdef GLOBAL_COMMON
      pErr->pNext = (errMessagePtr)gp->pErrMessages;
		((errMessagePtr)gp->pErrMessages)->pPrev = pErr;
		gp->pErrMessages = pErr;
#else
      pErr->pNext = gpErrMessages;
      gpErrMessages->pPrev = pErr;
      gpErrMessages = pErr;
#endif
   }
}  /*  ErrorSet  */


/*FUNCTION_HEADER**********************
 * NAME:    ;ErrorClear
 * DESC:    Deallocate the memory used by an error message
 * IN:      pErr2Clear - pointer to the error that is to be cleared
 * OUT:     none
 * RETURN:  none
 * NOTES:   
 *END_HEADER***************************/
void ErrorClear( errMessagePtr pErr2Clear )
{
#ifdef GLOBAL_COMMON
   GlobalCommonPtr	gp = GetGlobalCommonPtr();
#endif
   errMessagePtr pErr, pNextErr;

#ifdef GLOBAL_COMMON
   for(pErr = (errMessagePtr)gp->pErrMessages; pErr; pErr = pNextErr)
#else
   for(pErr=gpErrMessages; pErr; pErr = pNextErr)
#endif
   {
      pNextErr = pErr->pNext;
      if(pErr == pErr2Clear)
      {
         if(pErr2Clear->pPrev == NULL)
#ifdef GLOBAL_COMMON
     			gp->pErrMessages = pErr2Clear->pNext;
#else
            gpErrMessages = pErr2Clear->pNext;
#endif
         else
            pErr2Clear->pPrev->pNext = pErr2Clear->pNext;

         if (pErr2Clear->pNext)
            pErr2Clear->pNext->pPrev = pErr2Clear->pPrev;

         if(pErr2Clear->sMessage)
            FNX_FREE(pErr->sMessage);
         FNX_FREE(pErr2Clear);
         break;
      }
   }
}


/*FUNCTION_HEADER**********************
 * NAME:    ;ErrorClearAll
 * DESC:    Deallocate all of the memory used by the err handling
 * IN:      gpErrMessages - global pointer to an error struct
 * OUT:     
 * RETURN:  
 * NOTES:   
 *END_HEADER***************************/
void ErrorClearAll( void )
{
#ifdef GLOBAL_COMMON
   GlobalCommonPtr	gp = GetGlobalCommonPtr();
	errMessagePtr	pErr = gp->pErrMessages;
#else
   errMessagePtr pErr = gpErrMessages;
#endif
   errMessagePtr pTmpErr;

   while( pErr )
   {
      pTmpErr = pErr->pNext;
      if( pErr->sMessage )
      {
         FNX_FREE( pErr->sMessage );
		 pErr->sMessage = NULL;
	  }
      FNX_FREE( pErr );
      pErr = pTmpErr;
   }

#ifdef GLOBAL_COMMON
   gp->pErrMessages = NULL;
#else
   gpErrMessages = NULL;
#endif
}


#ifdef DISPLAY_ERROR_MESSAGES
/*FUNCTION_HEADER**********************
 * NAME:    ;ErrorDisplay
 * DESC:    display an error
 * IN:      fpStream - pointer to output stream (can be NULL)
            pErr - pointer to error data
 * OUT:     
 * RETURN:  
 * NOTES:   
 *END_HEADER***************************/
void ErrorDisplay(FILE *fpStream, errMessagePtr pErr)
{

#ifdef UNDER_CE
   {
      wchar_t  mbMessage[512];

      MultiByteToWideChar(CP_ACP, 0, pErr->sMessage, -1, mbMessage, 512);

      MessageBox(NULL, mbMessage, TEXT("Message"), MB_OK);
   }
#else 
#if defined(_WINDOWS) && ! defined(_CONSOLE)
#pragma  message ("Compiling for windows messages")
   if(fpStream == NULL || fpStream == stderr)
   {
      MessageBox(NULL, pErr->sMessage, "Error", MB_OK | MB_ICONERROR);
   }
   else
      FNX_FPRINTF(fpStream, "%s", pErr->sMessage);
#else
   if(fpStream)
      FNX_FPRINTF(fpStream, "%s", pErr->sMessage);
   else
      FNX_PRINTF("%s", pErr->sMessage);
#ifdef OS_UNIX
   /* Flush the stream in unix systems, since they don't automatically do
      it until a buffer fills up. */
   FNX_FFLUSH(fpStream ? fpStream : stdout);
#endif
#endif
#endif

}  /*  ErrorDisplay  */

/*FUNCTION_HEADER**********************
 * NAME:    ;ErrorDisplayMessages
 * DESC:    run through the list of errors and display each one
 * IN:      fpStream - pointer to the output stream (can be NULL)
 * OUT:     
 * RETURN:  
 * NOTES:   
 *END_HEADER***************************/
void ErrorDisplayMessages(FILE *fpStream)
{
#ifdef GLOBAL_COMMON
  	GlobalCommonPtr	gp = GetGlobalCommonPtr();
#endif
   errMessagePtr pErr, pTmpErr;
 
#ifdef GLOBAL_COMMON
   for(pErr=gp->pErrMessages; pErr; )
#else
   for(pErr=gpErrMessages; pErr; )
#endif
   {
      ErrorDisplay(fpStream, pErr);

      /*  Clear the error after it has been displayed  */
      pTmpErr = pErr->pNext;
      ErrorClear(pErr);
      pErr = pTmpErr;
   }
}  /*  ErrorDisplayMessages  */

#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;Message
 * DESC:    Print messages to the appropriate place.
 * IN:      The same as fprintf
 * OUT:     If the global handle for a list box is provided the message
            is printed there.  If not a message is printed to the appropriate 
            stream if provided (stdout, stderr, fp).  If no stream is provided
            then output is directed to stdout.
            
 * RETURN:  
 * NOTES:   
 *END_HEADER***************************/
void Message(void *pVoid, char *fmt, ...)
{
   va_list argptr;
   char sMessage[MAX_ERRSTRING];
   SDWORDPTR piErr = (SDWORDPTR)(pVoid);

   /* Convert printf-like arguments into a string 'sMessage'. */
   va_start(argptr, fmt);
#ifdef OS_UNIX
   vsnprintf(sMessage, MAX_ERRSTRING, fmt, argptr);
#else
   vsprintf(sMessage, fmt, argptr);
#endif
   va_end(argptr);

   ErrorSet((piErr && *piErr<0) ? *piErr : -1, sMessage);

#ifdef DISPLAY_ERROR_MESSAGES
   ErrorDisplayMessages((FILE *)pVoid);
#endif
/*  Message  */
}  
