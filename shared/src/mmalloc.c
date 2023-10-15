/********************************************************************************* 		*/
/********************************************************************************* 		*/
/*                                                                    					*/
/*  COPYRIGHT NOTICE                                                  					*/
/*                                                                    					*/
/*  Copyright (c) Digital Equipment Corporation, 1998                 					*/
/*  Copyright © 2000, 2001 Force Computers, Inc., a Solectron company. All rights reserved.	*/
/*																	  					*/
/*  All Rights reserved. Unpublished rights reserved under the        					*/
/*  copyright laws of the United States. Copyright is claimed in      					*/
/*  the computer program and user interface thereof.                  					*/
/*                                                                    					*/
/*  The software contained on this media is proprietary to and        					*/
/*  embodies the confidential technology of Force Computers Inc.         				*/
/*  Possession, use, duplication or dissemination of     								*/
/*  the software and media is authorized only pursuant to a valid     					*/
/*  written license from Force Computers Incorporated.               					*/
/*                                                                    					*/
/*  The name of Force Computers Incorporated may not be used to      					*/
/*  endorse or promote products derived from this software without    					*/
/*  specific prior written permission. All other rights reserved.     					*/
/*                                                                    					*/
/*  THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR      					*/
/*  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, IMPLIED        					*/
/*  WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS        					*/
/*  FOR A PARTICULAR PURPOSE.                                         					*/
/*  Force assumes no responsibility AT ALL for the use or           					*/
/*  reliability of this software.                                     					*/
/*                                                                    					*/
/*                                                                    					*/
/* +----------------------------------------------------------------+ */
/* | USE, DUPLICATION OR DISCLOSURE BY THE U.S. GOVERNMENT IS       | */
/* | SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH (c)       | */
/* | DFARS 252.227-7013, OR IN FAR 52.227-14 ALT. II, AS APPLICABLE.| */
/* |                                                                | */
/* +----------------------------------------------------------------+ */
/*                                                                    */
/**********************************************************************/
/**********************************************************************/


/**********************************************************************/
/**********************************************************************/
/*                                                                    */
/*  File: mmalloc.c                                                   */
/*  Author: Bill Hallahan                                             */
/*  Date: February 29, 1996                                           */
/*                                                                    */
/*  Abstract:                                                         */
/*                                                                    */
/*    This function provides memory allocation functions that can be  */
/*    used in multimedia applications. It is strongly recommended     */
/*    that the macros defined in file mmalloc.h are used to call      */
/*    these functions.                                                */
/*                                                                    */
/*    The constant SHARED_MEMORY_ALLOCATION_SIZE can be increased to  */
/*    reduce the total number of shared memory segments used by the   */
/*    multimedia server. Ideally, this constant should be set to the  */
/*    maximum memory allocated by the mmeAllocMem() function.         */
/*                                                                    */
/**********************************************************************/
/**********************************************************************/
/* 001	MGS 	09/08/1997 	Made changes for osf build *
 * 002 	JAW 	02/27/1998 	Merged CE code.            *
 * 003 	CJL 	03/18/1998 	Removed specific path for dectalkf.h. *
 * 004 	JAW 	07/07/1998 	Added function reallocLock.           *
 * 005 	ETT		10/05/1998  Added Linux code.
 * 006 	NAL 	06/13/2000 	Warning removal
 * 007 	CAB		10/16/2000	Changed copyright info
 * 008	MGS		05/09/2001	Some VxWorks porting BATS#972
 * 009  CAB		05/14/2001	Edited and updated copyright
 * 010	MGS		06/19/2001	Solaris Port BATS#972
 **********************************************************************/
#include "dectalkf.h"
#include "port.h"

//moved to port.h for each platform - mlt
//#if !defined VXWORKS && !defined _APPLE_MAC_
//#include <malloc.h>
//#endif
#include "mmalloc.h"
//moved to port.h for each platform - mlt
//#include <stdio.h> // NAL warning removal


#if !defined UNDER_CE && !defined _UNIX_LIKE_
/**********************************************************************/
/*  Locked memory allocation functions for Windows NT and Windows 95. */
/**********************************************************************/

/**********************************************************************/
/**********************************************************************/
/*                                                                    */
/*  Function: mallocLock                                              */
/*  Author:   Bill Hallahan                                           */
/*  Date:     March 10, 1993                                          */
/*                                                                    */
/*  Abstract:                                                         */
/*                                                                    */
/*    This function allocates global locked memory.                   */
/*    The memory is uninitialized.                                    */
/*                                                                    */
/*                                                                    */
/*  Inputs:                                                           */
/*                                                                    */
/*    uiSize    A value of type unsigned int that equals the number   */
/*              of bytes to allocate.                                 */
/*                                                                    */
/*                                                                    */
/*  Outputs:                                                          */
/*                                                                    */
/*    The function will return a pointer to memory if the allocation  */
/*    succeeds. If the allocation fails then NULL will be returned.   */
/*                                                                    */
/*                                                                    */
/**********************************************************************/
/**********************************************************************/

void * mallocLock( unsigned int uiSize )
{
  HGLOBAL hMem;

  /********************************************************************/
  /*  Allocate and Lock Global Memory.                                */
  /********************************************************************/

  hMem = GlobalAlloc( GMEM_MOVEABLE, (size_t)uiSize );

  return GlobalLock( hMem );
}

#ifndef MSDOS
/**********************************************************************/
/**********************************************************************/
/*                                                                    */
/*  function: reallocLock                                             */
/*  Author:   Bill Hallahan                                           */
/*  Date:     March 10, 1993                                          */
/*                                                                    */
/*  Abstract:                                                         */
/*                                                                    */
/*    reallocLock changes the size of the object pointed to by        */
/*    pMem to "size". If the new size is larger the space is          */
/*    uninitialized.                                                  */
/*                                                                    */
/*                                                                    */
/*  Inputs:                                                           */
/*                                                                    */
/*    pMem       A pointer to the memory to be reallocated            */
/*                                                                    */
/*  Outputs:                                                          */
/*                                                                    */
/*    The function will return a pointer to new memory if the         */
/*    allocation succeeds. If the allocation fails then NULL will     */
/*    be returned.                                                    */
/*                                                                    */
/*                                                                    */
/**********************************************************************/
/**********************************************************************/

void * reallocLock( void * pMem, size_t size )
{
  HGLOBAL hMem;
  void *pvReturn; // tek 18jun98 debugging

  hMem = GlobalHandle( pMem );

#ifdef _DEBUG
  {
	  char szTemp[256];
	  FNX_SPRINTF(szTemp,"reallocLock: was ptr:%08lx  hMem:%08lx\n",
	  pMem, hMem);
	  OutputDebugString(szTemp);
  }
#endif //_DEBUG

  hMem = GlobalReAlloc( hMem, size, GMEM_MOVEABLE );

  pvReturn = GlobalLock( hMem );
#ifdef _DEBUG
  {
	  char szTemp[256];
	  FNX_SPRINTF(szTemp,"reallocLock: (ptr was %08lx) is ptr:%08lx  hMem:%08lx\n",
	  pMem, pvReturn, hMem);
	  OutputDebugString(szTemp);
  }
#endif //_DEBUG

  return(pvReturn);
}
#endif /* #ifndef MSDOS */

/**********************************************************************/
/**********************************************************************/
/*                                                                    */
/*  function: freeLock                                                */
/*  Author:   Bill Hallahan                                           */
/*  Date:     March 10, 1993                                          */
/*                                                                    */
/*  Abstract:                                                         */
/*                                                                    */
/*    This function frees memory allocated by the mallocLock()        */
/*    function.                                                       */
/*                                                                    */
/*                                                                    */
/*  Inputs:                                                           */
/*                                                                    */
/*    pMem       A pointer to the memory to be freed.                 */
/*                                                                    */
/*  Outputs:                                                          */
/*                                                                    */
/*    The function will return a value of FALSE if the memory was     */
/*    succesfully freed. Otherwise the value TRUE will be returned.   */
/*                                                                    */
/*                                                                    */
/**********************************************************************/
/**********************************************************************/

unsigned int freeLock( void * pMem )
{
  HGLOBAL hMem;

  hMem = GlobalHandle( pMem );

  if ( GlobalUnlock( hMem ))
    return TRUE;

  if( GlobalFree( hMem ) != NULL )
    return TRUE;

  return FALSE;
}

#endif //UNDER_CE
