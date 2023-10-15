/**********************************************************************/
/*   					Copyright �                                   */
/*  Copyright � 2001 Force Computers Inc. A Solectron Company. All rights reserved. */
/*  Copyright � SMART Modular Technologies 1999. All rights reserved. */
/*  Copyright Digital Equipment Corporation, 1994,                    */
/*  All rights reserved.                                              */
/*                                                                    */
/*  This software is proprietary to and embodies the confidential     */
/*  technology of Force Computers Incorporated. Possession, use,     */
/*  or copying of this software and media is authorized only pursuant */
/*  to a valid written license from Force or an authorized          */
/*  sublicensor.                                                      */
/*                                                                    */
/*  Restricted Rights: Use, duplication, or disclosure by the         */
/*  U.S. Government is subject to restrictions as set forth in        */
/*  subparagraph (c) (1) (ii) of DFARS 252.227-7013, or in            */
/*  FAR 52.227-19, or in FAR 52.227-14 Alt. III as applicable.        */
/*                                                                    */
/*  The name of Force Computers Incorporated may not be used to      */
/*  endorse or promote products derived from this software without    */
/*  specific prior written permission. All other rights reserved.     */
/*                                                                    */
/*  This software is provided "as is" and without any express or      */
/*  implied warranties, including, without limitation, implied        */
/*  warranties of non-infringement, merchantibility or fitness        */
/*  for a particular purpose. Force assumes no responsibility AT    */
/*  ALL for the use or reliability of this software.                  */
/*                                                                    */
/**********************************************************************/

/*
 * HISTORY
 * Revision 1.1.2.5  1998/11/16  time		Eric Thompson
 *		added define for osf. actually Matt did.
 * Revision 1.1.2.4  1998/11/12  time		Eric Thompson
 *     fixed stuff for osf
 * Revision 1.1.2.3  1996/01/03  21:08:07  Bill_Hallahan
 * 	New audio subsystem
 * 	[1996/01/03  21:02:31  Bill_Hallahan]
 *
 * Revision 1.1.2.2  1995/07/05  19:35:32  Krishna_Mangipudi
 * 	Copied from ./src/tts
 * 	[1995/07/05  19:32:23  Krishna_Mangipudi]
 * 
 * Revision 1.2.2.2  1994/11/07  23:07:20  Krishna_Mangipudi
 * 	Initial Check-in
 * 	[1994/11/07  21:12:51  Krishna_Mangipudi]
 * 
 * Revision 1.2  1994/11/04  18:33:29  root
 * 	Initial load of project
 * 
 */
/*
 * 001	MGS	09/09/1997	Changed code for osf
 * 002	MGS	05/09/2001	Some VxWorks porting BATS#972
 * 003	CAB	05/14/2001	Updated copyright info.
 * 004	CAB	05/14/2001	Consolidated multiple copyrights fields
 * 005	MGS	06/19/2001	Solaris Port BATS#972
 */
/*
**++
** FACILITY:  Workstation Multimedia  (WMM)  v1.0 
** 
** FILE NAME:   
** MODULE NAME: 
**
** MODULE DESCRIPTION: 
** 
** DESIGN OVERVIEW: 
** 
**--
*/

/*
**++
**
** FACILITY: DECtalk
**
** FILE NAME: dtmmedefs.h
**
** MODULE DESCRIPTION:
**       Basic definitions used by the DECtalk.
**	 Compatibility definitions for Multimedia Services for OSF/1.
**
** AUTHORS:
**
** CREATION DATE: 3/15/1993
**
** DESIGN OVERVIEW:
**         
**
**--
*/

#ifndef H_MMBASIC
#define H_MMBASIC

/*
** [Include Files]
*/
#include "dectalktypes.h"
/*
** Constant Definitions
*/

/*
** Data Structure Definitions
*/

/*
** Exported Global Variables
*/
/* None */

/*
** Pseudo Functions (#defined macros)
*/
/* None */

/*
** Exported Function Proto-types
*/
/* None */

/* these values are from Windows mmsystem.h */
/****************************************************************************

                        General error return values

****************************************************************************/
#define MMSYSERR_BASE         0
#define MMSYSERR_NOERROR      0                    /* no error */
#define MMSYSERR_ERROR        (MMSYSERR_BASE + 1)  /* unspecified error */
#define MMSYSERR_BADDEVICEID  (MMSYSERR_BASE + 2)  /* device ID out of range */
#define MMSYSERR_NOTENABLED   (MMSYSERR_BASE + 3)  /* driver failed enable */
#define MMSYSERR_ALLOCATED    (MMSYSERR_BASE + 4)  /* device already allocated */
#define MMSYSERR_INVALHANDLE  (MMSYSERR_BASE + 5)  /* device handle is invalid */
#define MMSYSERR_NODRIVER     (MMSYSERR_BASE + 6)  /* no device driver present */
#define MMSYSERR_NOMEM        (MMSYSERR_BASE + 7)  /* memory allocation error */
#define MMSYSERR_NOTSUPPORTED (MMSYSERR_BASE + 8)  /* function isn't supported */
#define MMSYSERR_BADERRNUM    (MMSYSERR_BASE + 9)  /* error value out of range */
#define MMSYSERR_INVALFLAG    (MMSYSERR_BASE + 10) /* invalid flag passed */
#define MMSYSERR_INVALPARAM   (MMSYSERR_BASE + 11) /* invalid parameter passed */
#define MMSYSERR_HANDLEBUSY   (MMSYSERR_BASE + 12) /* handle being used */
                                                   /* simultaneously on another */
                                                   /* thread (eg callback) */
#define MMSYSERR_INVALIDALIAS (MMSYSERR_BASE + 13) /* specified alias not found */
/* these are unused but included for completeness */
#define MMSYSERR_BADDB        (MMSYSERR_BASE + 14) /* bad registry database */
#define MMSYSERR_KEYNOTFOUND  (MMSYSERR_BASE + 15) /* registry key not found */
#define MMSYSERR_READERROR    (MMSYSERR_BASE + 16) /* registry read error */
#define MMSYSERR_WRITEERROR   (MMSYSERR_BASE + 17) /* registry write error */
#define MMSYSERR_DELETEERROR  (MMSYSERR_BASE + 18) /* registry delete error */
#define MMSYSERR_VALNOTFOUND  (MMSYSERR_BASE + 19) /* registry value not found */
#define MMSYSERR_NODRIVERCB   (MMSYSERR_BASE + 20) /* driver does not call DriverCallback */
#define MMSYSERR_LASTERROR    (MMSYSERR_BASE + 20) /* last error in range */

/* defines for dwFormat field of WAVEINCAPS and WAVEOUTCAPS */
#define WAVE_INVALIDFORMAT     0x00000000       /* invalid format */
#define WAVE_FORMAT_1M08       0x00000001       /* 11.025 kHz, Mono,   8-bit */
#define WAVE_FORMAT_1S08       0x00000002       /* 11.025 kHz, Stereo, 8-bit */
#define WAVE_FORMAT_1M16       0x00000004       /* 11.025 kHz, Mono,   16-bit */
#define WAVE_FORMAT_1S16       0x00000008       /* 11.025 kHz, Stereo, 16-bit */
#define WAVE_FORMAT_2M08       0x00000010       /* 22.05  kHz, Mono,   8-bit */
#define WAVE_FORMAT_2S08       0x00000020       /* 22.05  kHz, Stereo, 8-bit */
#define WAVE_FORMAT_2M16       0x00000040       /* 22.05  kHz, Mono,   16-bit */
#define WAVE_FORMAT_2S16       0x00000080       /* 22.05  kHz, Stereo, 16-bit */
#define WAVE_FORMAT_4M08       0x00000100       /* 44.1   kHz, Mono,   8-bit */
#define WAVE_FORMAT_4S08       0x00000200       /* 44.1   kHz, Stereo, 8-bit */
#define WAVE_FORMAT_4M16       0x00000400       /* 44.1   kHz, Mono,   16-bit */
#define WAVE_FORMAT_4S16       0x00000800       /* 44.1   kHz, Stereo, 16-bit */

/* flags for wFormatTag field of WAVEFORMAT */
#define WAVE_FORMAT_PCM     1 

#define WAVE_MAPPER     ((DWORD)(-1))   /* device ID for wave device mapper */

/* these values are from Windows mmreg.h */
#define WAVE_FORMAT_MULAW      0x00000007	/* 8      kHz, Mono,   Mu-law */

/* these are other options available on unix */
#define WAVE_OPEN_SHAREABLE   0x00000004       /* Open device as shareable */

#endif  /* H_MMBASIC */
