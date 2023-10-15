/************************************************************
 *
 *                           Copyright ©
 *	  Copyright © 2002 Fonix Corporation. All rights reserved.
 *	  Copyright © 2000, 2001 Force Computers, Inc., a Solectron Company. All rights reserved.
 *    © Digital Equipment Corporation 1996, 1997. All rights reserved.
 *
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Fonix Corporation and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Fonix or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:    opthread.h
 *    Author:       Bill Hallahan
 *    Creation Date:15-NOV-1995
 *
 *    Functionality:
 *    Tone Generation code for DTMF and single tone.
 *
 ***********************************************************************
 *    Revision History:                                        
 *
 * Rev  Who 	Date        Description
 * ---  -----   ----------- --------------------------------------------
 * 001  BH 		11/15/195	Initial release
 * 002	GL		04/21/1997	BATS#357  Add the code for __osf__ build 
 * 003  ETT		10/05/1998  Added Linux code.
 * 004  mfg		10/15/1998	made MAX_TONE_BLOCK  4096 for UNDER_CE
 * 005  ETT		11/12/1998	fixed stuff for osf.
 * 006	mfg		10/10/2000	windows CE new compilier and warning fixes
 * 007 	CAB		10/16/2000	Changed copyright info
 * 008	MGS		05/09/2001	Some VxWorks porting BATS#972
 * 009	CAB		05/14/2001	Updated copyright
 * 010	MFG		05/29/2001	Included dectalkf.h
 * 011	MGS		06/19/2001	Solaris Port BATS#972
 * 012	MGS		04/11/2002	ARM7 port
 * 013	CAB		07/31/2002	Fixed __osf__ typo
 */

/**********************************************************************/
/*  Include files.                                                    */
/**********************************************************************/
#include "dectalkf.h"
#ifndef EPSON_ARM7
#ifdef WIN32
#include <windows.h>
#endif

#include <math.h>
#ifdef VXWORKS
#include <string.h>
#include <stdlib.h>
#else
#if defined ARM7 || defined _APPLE_MAC_
#if !defined OS_PALM && !defined CASIO_SH3
#include <stdio.h>
#endif
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#else
#include <malloc.h>
#endif
#endif
#include "kernel.h"	   /* For PKSD_T definition */
#include "tts.h"	   /* For TTS_HANDLE_T definition  */
#include "cmd.h"
#include "sinetab.h"
#include "vtminst.h"    /* MVP MI New : New header file */

/* GL 04/21/1997  change this for OSF build */
#if defined _UNIX_LIKE_
#if defined __osf__
#include "dtmmedefs.h"
#endif
#include "opthread.h"
#endif
/**********************************************************************/
/*  Symbol definitions.                                               */
/**********************************************************************/

#define  RISE_TIME       0.002

#ifdef	UNDER_CE
#define  MAX_TONE_BLOCK   4096
#else	
#define  MAX_TONE_BLOCK   1024
#endif
#define  TONE_SYMBOL    0x7FFF

/**********************************************************************/
/*  External function prototypes.                                     */
/**********************************************************************/

extern void OutputData( LPTTS_HANDLE_T,
                        short *,
                        unsigned int,
                        DWORD,
                        DWORD,
						DWORD);
extern void OutputDataTone( LPTTS_HANDLE_T,
                        short *,
                        unsigned int,
                        DWORD,
                        DWORD,
						DWORD);

/**********************************************************************/
/*  Function prototypes.                                              */
/**********************************************************************/

static float Tone( float, float * );

/*  Function: PlayTones                                               */
/*  Author: Bill Hallahan                                             */
/*  Date: June 29, 1994                                               */
/*                                                                    */
/*  Abstract:                                                         */
/*                                                                    */
/*    This function generates and plays tone waveforms. Up to two     */
/*    two tones may be generated.                                     */
/*                                                                    */
/*                                                                    */
/*                                                                    */
/*  Input:                                                            */
/*                                                                    */
/*    phTTS             A pointer to a structure of type              */
/*                      TTS_HANDLE_T.                                 */
/*                                                                    */
/*    DurationInMsec    A float that is equal to the duration of the */
/*                      tone burst in milli-seconds.                  */
/*                                                                    */
/*    Freq_0            A float that is equal to the frequency of    */
/*                      tone 0 in Hertz.                              */
/*                                                                    */
/*    Amp_0             A float that is equal to the amplitude of    */
/*                      tone 0.                                       */
/*                                                                    */
/*    Freq_1            A float that is equal to the frequency of    */
/*                      tone 1 in Hertz.                              */
/*                                                                    */
/*    Amp_1             A float that is equal to the amplitude of    */
/*                      tone 1.                                       */
/*                                                                    */
/*    SampleRate        A float that is equal to the sample rate     */
/*                      in seconds.                                   */
/*  MVP : MI the below 2 args are removed.                            */
/*    SamplePeriod      A float that is equal to the sampling period */
/*                      in seconds.                                   */
/*                                                                    */
/*    bCancel           The address of a cancel flag.                 */
/*                                                                    */
/*  Output:                                                           */
/*                                                                    */
/*    This function will return a value of FALSE if successful.       */
/*                                                                    */
/**********************************************************************/
/**********************************************************************/

#if defined (ARM7) && !defined (OS_SYMBIAN)
short gToneBuffer[MAX_TONE_BLOCK];
float gRiseBuffer[24]; // RISE_TIME * 11025 +1
#endif

BOOL PlayTones( LPTTS_HANDLE_T phTTS,
                float DurationInMsec,
                float Freq_0,
                float Amp_0,
                float Freq_1,
                float Amp_1,
                float SampleRate
                )
{
  int i;
  int iRiseSamples;
  int iCenterSamples;
  int iCenterCount;
  int iSynthCount;
  int iTotalSamples;
  float * pRiseBuffer;
  float * pRise;
  short * pToneBuffer;
  short * pBuffer;
  float Sample;
  float PhaseIncrement_0;
  float Phase_0;
  float PhaseIncrement_1;
  float Phase_1;
  DWORD dwDurationInFrames;
  PKSD_T pKsd_t = phTTS->pKernelShareData;
  /********************************************************************/
  /*  Calculate the duration in frames.                               */
  /********************************************************************/

  dwDurationInFrames = (int)( 0.15625 * DurationInMsec );

  /********************************************************************/
  /*  Calculate the tone generation parameters.                       */
  /********************************************************************/

  iTotalSamples = (int)( 0.001 * DurationInMsec * SampleRate );
  iRiseSamples = (int)((float)RISE_TIME * SampleRate );
  iCenterSamples = iTotalSamples - ( iRiseSamples << 1 );

  if ( iCenterSamples < 0 )
  {
    iRiseSamples = iCenterSamples >> 1;
    iCenterSamples = 0;
  }

  /********************************************************************/
  /*  Allocate the tone audio buffer.                                 */
  /********************************************************************/
#if defined (ARM7) && !defined (OS_SYMBIAN)
  pToneBuffer=gToneBuffer;
#else
  pToneBuffer = (short *)malloc( MAX_TONE_BLOCK * sizeof(short));
#endif
  if ( pToneBuffer == NULL )
  {
    return( TRUE );
  }

  /********************************************************************/
  /*  Allocate the rise gain buffer.                                  */
  /********************************************************************/
#if defined (ARM7) && !defined (OS_SYMBIAN)
  pRiseBuffer=gRiseBuffer;
#else
  pRiseBuffer = (float *)malloc( iRiseSamples * sizeof(float));
#endif

  if ( pRiseBuffer == NULL )
  {
    return( TRUE );
  }

  /******************************************************************/
  /*  Build the rise time table.                                    */
  /******************************************************************/

  PhaseIncrement_0 = 0.25 * TWO_PI_EQUIVALENT / (float)iRiseSamples;
  Phase_0 = 0.0;

  pRise = pRiseBuffer;

  for ( i = 0; i < iRiseSamples; i++ )
  {
    Sample = SineTable[(int)Phase_0];
    *pRise++ = Sample * Sample;
    Phase_0 += PhaseIncrement_0;
  }

  /********************************************************************/
  /*  Generate tones.                                                 */
  /********************************************************************/

  PhaseIncrement_0 = Freq_0 * pKsd_t->SamplePeriod * TWO_PI_EQUIVALENT;
  Phase_0 = 0.0;
  PhaseIncrement_1 = Freq_1 * pKsd_t->SamplePeriod * TWO_PI_EQUIVALENT;
  Phase_1 = 0.0;

  /********************************************************************/
  /*  Generate Samples during the rise time portion of the tone.      */
  /********************************************************************/

  pBuffer = pToneBuffer;

  for ( i = 0; i < iRiseSamples; i++ )
  {
    Sample  = Amp_0 * Tone( PhaseIncrement_0, &Phase_0 );
    Sample += Amp_1 * Tone( PhaseIncrement_1, &Phase_1 );
    *pBuffer++ = (short)( pRiseBuffer[i] * Sample );
  }

  /********************************************************************/
  /*  Play the rise time portion of the tone waveform.                */
  /*  Also send the duration which is in multiples of 6.4 msec.       */
  /********************************************************************/
#ifdef ARM7
  OutputDataTone( phTTS,
              pToneBuffer,
              iRiseSamples,
              TONE_SYMBOL,
              (DWORD)( 0.15625 * DurationInMsec ),0);
  		if (phTTS->pKernelShareData->halting)
		{
			return(0);
		}

#else
  OutputData( phTTS,
              pToneBuffer,
              iRiseSamples,
              TONE_SYMBOL,
              (DWORD)( 0.15625 * DurationInMsec ),0);
#endif

  /********************************************************************/
  /*  Generate the center portion of the tone.                        */
  /********************************************************************/

  iCenterCount = 0;

  while (( iCenterCount < iCenterSamples ) && ( ! pKsd_t->halting))
  {
    iSynthCount = iCenterSamples - iCenterCount;

    if ( iSynthCount > MAX_TONE_BLOCK )
    {
      iSynthCount = MAX_TONE_BLOCK;
    }

    pBuffer = pToneBuffer;

    for ( i = 0; i < iSynthCount; i++ )
    {
      Sample  = Amp_0 * Tone( PhaseIncrement_0, &Phase_0 );
      Sample += Amp_1 * Tone( PhaseIncrement_1, &Phase_1 );
      *pBuffer++ = (short)Sample;
    }

    iCenterCount += iSynthCount;

    /******************************************************************/
    /*  Queue the samples.                                            */
    /******************************************************************/

#ifdef ARM7
    OutputDataTone( phTTS, pToneBuffer, iSynthCount, TONE_SYMBOL, 0 ,0);
		if (phTTS->pKernelShareData->halting)
		{
			return(0);
		}
#else
    OutputData( phTTS, pToneBuffer, iSynthCount, TONE_SYMBOL, 0 ,0);
#endif
  }

  /********************************************************************/
  /*  Generate Samples during the fall time portion of the tone.      */
  /********************************************************************/

  pBuffer = pToneBuffer;

  for ( i = iRiseSamples - 1; i >= 0; i-- )
  {
    Sample  = Amp_0 * Tone( PhaseIncrement_0, &Phase_0 );
    Sample += Amp_1 * Tone( PhaseIncrement_1, &Phase_1 );
    *pBuffer++ = (short)( pRiseBuffer[i] * Sample );
  }

  /********************************************************************/
  /*  Play the fall time portion of the tone waveform.                */
  /********************************************************************/

#ifdef ARM7
  OutputDataTone( phTTS, pToneBuffer, iRiseSamples, TONE_SYMBOL, 0,0 );
		if (phTTS->pKernelShareData->halting)
		{
			return(0);
		}
		//clear out the buffer (adding a small amount of silence if necessary
  OutputDataTone( phTTS, NULL, 0, TONE_SYMBOL, 0,0 );
		if (phTTS->pKernelShareData->halting)
		{
			return(0);
		}
#else
  OutputData( phTTS, pToneBuffer, iRiseSamples, TONE_SYMBOL, 0,0 );
#endif

  /********************************************************************/
  /*  Free the rise gain buffer and the tone audio buffer.            */
  /********************************************************************/
  
#if !defined (ARM7) || defined(OS_SYMBIAN)
  free( pRiseBuffer );
  free( pToneBuffer );
#endif

  return( FALSE );
}

/**********************************************************************/
/**********************************************************************/
/*                                                                    */
/*  Function: Tone                                                    */
/*  Author: Bill Hallahan                                             */
/*  Date: June 29, 1994                                               */
/*                                                                    */
/*  Abstract:                                                         */
/*                                                                    */
/*    This function generates a single tone sample.                   */
/*                                                                    */
/*                                                                    */
/*  Input:                                                            */
/*                                                                    */
/*    PhaseIncrement    A value of type float that is equal to the   */
/*                      phase increment for the desired tone          */
/*                      frequency at the current sample rate.         */
/*                                                                    */
/*    pPhase            A pointer to a float that contains the       */
/*                      current phase of the tone sinusoid.           */
/*                                                                    */
/*  Output:                                                           */
/*                                                                    */
/*    This function returns a float equal to the next tone sample.   */
/*                                                                    */
/**********************************************************************/
/**********************************************************************/

static float Tone( float PhaseIncrement, float * pPhase )
{
  float Sample;

  /********************************************************************/
  /*  Synthesize tone sample 1.                                       */
  /********************************************************************/

  Sample = SineTable[(int)*pPhase];

  *pPhase += PhaseIncrement;

  if ( *pPhase >= TWO_PI_EQUIVALENT )
    *pPhase -= TWO_PI_EQUIVALENT;

  return( Sample );
}
#endif