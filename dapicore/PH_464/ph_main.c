/* 
 ***********************************************************************
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
 *    File Name:    ph_main.c
 *    Author:
 *    Creation Date:
 *
 *    Functionality:
 * 	  This file contains the
 * 	  mainline of the synthesizer task.
 * 	  It reads phonemes from letter to
 * 	  sound, packs them into clauses, and
 * 	  converts them to signal processor
 * 	  control frames.
 ***********************************************************************
 *    Revision History:
 *
 * Rev  Who     Date            Description
 * ---  -----   -----------     --------------------------------------------  
 * 001  DGC    	12/27/1984		Renamed from "kl1.c". Many edits for
 *                      		the new synthesizer.
 * 002  DGC   	01/02/1985		Added an "mstofr" routine that watches
 *                      		out for overflow on 16 bit machines.
 * 003  DGC		01/19/1985    	Dennis changed "phdefs.h" so that it always
 *                      		included "def.h". Deleted the include line
 *                      		that was in this file.
 * 004  DGC		01/24/1985    	Added some code at the top of the main
 *                      		loop that turns WBOUND into COMMA if it
 *                      		looks like we are getting close to the edge.
 * 005  DGC		01/31/1985    	Changed the way that "SYNC" is done.
 * 006  DGC		03/06/1985    	Changed the code that writes out the index
 *                      		reply stuff to use "PUTSEQ".
 * 007  DGC		04/17/1985    	Changes due to default/0 change in "ansi.c".
 * 008  DGC 	06/02/1985   	Added LOG_PHONEME.
 * 009  DGC		06/07/1985    	"ef" => "lx" in speaker definition.
 * 010  DGC 	06/18/1985   	"g5" => "lo" in speaker definition.
 * 011  DGC 	06/19/1985	    Enforce limits for ":ra", ":cp", ":pp".
 * 012  DGC		07/26/1985	    "outpar" isn't  structure anymore.
 * 013  DGC		08/08/1985	    "haltsw" (FLAG) => "halting" (short), new sync.
 *    							Released as C5005 V1.0 firmware.
 * 014  DGC 	10/21/1985   	Changes for KRM.
 * 015  DGC 	11/07/1985	    Fixed a bug in indexing found by Kurzweil.
 * 016  EAB 	01/12/1990  	Put in changes for NKR and SENT.(compile changes)
 * 017  EAB 	01/16/1990  	change rate limit from 350 to 550
 * 018  EAB 	07/25/1990	    ADDED COMMA PAUSE CHANGED FOR NANCY JARRELL-CHB
 * 019  SGS		09/17/1990    	Added PR control switches
 * 020  CJL		03/15/1995    	Added debug code for printf bug; uses define DEBUG
 * 021  JDB		09/17/1995   	Replaced /n's with \n's.
 * 022  MGS 	03/21/1996	  	WIN32 code merge 
 * 023	MGS	 	05/31/1996		kltask moved to ph_task.c file
 * 024	MGS		05/31/1996		Merged spanish with english
 * 025	MGS		06/06/1996		Changed file name from phmain.c ph_main.c
 * 026	SIK		07/08/1996  	Cleaning up and maintenance
 * 027  GL		10/26/1996		merge the TEK 8/13/96 change into the code
 * 028  GL		12/05/1996		remove the language pipe hack for DTEX.
 * 029  GL		12/11/1996		initialize the lang_curr only for MSDOS
 *								also remove the WIN32 language pipe hack
 * 030	GL		04/21/1997		BATS#357  Add the code for __osf__ build 
 * 031	GL		04/21/1997		BATS#360  remove spaces before "#define" or "#if" 
 * 032  DR		09/30/1997		UK BUILD: added UK STUFF
 * 033	MGS		10/14/1997		BATS #470 Fixed crashing due to reset
 * 034	ET		06/04/1998		Merged in code from PHEDIT2
 * 035	MGS		06/17/1998		phedit2 changes
 * 036	mfg		06/22/1998		Added support for LANG_latin_american
 * 037  ETT		10/05/1998      	Added Linux code.
 * 038  EAB		02/03/1999		Added change from NWSNOAA->NWS_US for multi language NOA
								and new code for evan ballaban to allow multiple vtm frame 
								file outputs
 * 042	mfg		07/22/1999		included  cemm.h
 * 043	NAL		01/20/2000		Added initialization of speaker param arrays
 * 044	MGS		04/13/2000		Changes for integrated phoneme set 
								tunedef,tunedef_8 
 * 045  NAL		06/12/2000		Added function prototype (warning removal)
 * 045  NAL		06/13/2000		Fixed val to use proper offsets BATS #930
 * 046	CHJ		07/20/2000		French added
 * 047 	CAB		10/18/2000		Changed copyright info and formatted comments
 * 048	MGS		05/09/2001		Some VxWorks porting BATS#972
 * 049  CAB		05/14/2001		Updated copyright
 * 050	MFG		05/29/2001		Included dectalkf.h
 * 051	MGS		06/19/2001		Solaris Port BATS#972
 * 052	MGS		03/21/2002		Single threaded ph
 * 053	MGS		04/11/2002		ARM7 port
 * 054	CAB		04/25/2002		Removed warnings with typecast
 * 055	MFG		09/19/2002	 	Added support for new chris voice
 * 056	CAB		09/19/2002		Changed chris voice to us only
 * 057  EAB     11/18/2002      RE-merged in Mollie's chnages that I accidentally overwrote
 */

#include "dectalkf.h"
#include "ph_def.h"		/* the new all inclusive include file for ph */

#ifdef UNDER_CE
#include "cemm.h"
#endif //UNDER_CE

#if defined _UNIX_LIKE_ 
#include <stdlib.h>
#endif

#if defined ARM7 && !defined OS_PALM
#include <stdlib.h>
#include <string.h>
#endif

#ifdef SEPARATE_PROCESSES
struct share_data      *kernel_share;

#endif

#ifdef PHEDIT2 /* ET merged from PHEDIT2 */
#ifdef ENGLISH_US
short TOT_ALLOPHONES = 59;
#elif defined ENGLISH_UK
short TOT_ALLOPHONES = 57;
#elif defined SPANISH_SP
short TOT_ALLOPHONES = 39;
#elif defined SPANISH_LA
short TOT_ALLOPHONES = 39;
#elif defined FRENCH
short TOT_ALLOPHONES = 40;
#else
short TOT_ALLOPHONES = (PH_LAST_PH+1);  /* total number of phones */
#endif
#endif /* PHEDIT2 */
											
/* 
 * #ifdef __osf__ this is the opaque PIPE input handle    
 * MVP : Now it is same as for NT. extern void *vtm_pipe; 
 * #endif 
 */


/* int             reset_pitch;   *//* MVP MI Made instance specific in DPH_T */
/* int             default_pitch; *//* MVP MI Made instance specific in DPH_T */

/***************************************************************************/
/* MVP: The following extern variables are now become elements of instance */
/* specific PH thread data structure DPH_T.                                */
/* Input arrays (set by call to PH_SETAR.C whenever time for new phone)    */
/* extern PARAMETER param[];        Struc of input vars for each par       */
/* extern  short   parstochip[];    Array of paramters to TMS.             */
/* extern  short   symbols[];       Where input symbols go.                */
/* extern  short   nsymbtot;        Length of above.                       */
/* extern  short   *user_durs;      Where user durations go.               */
/* extern  short   *user_f0;        Where user f0 commands go.             */
/* extern  short curspdef[];        current speaker definition             */
/* extern  FLAG    loadspdef;       Flag: need to load TMS320.             */
/* extern  short   compause;        Comma pause, frames                    */
/* extern  short   perpause;        Period pause, frames                   */
/* int     bound;                                                          */
/* int     nphone;                                                         */
/* int     lastoffs;                                                       */
/* MVP MI :                       Now kinp made local wherever it is used  */
/* extern  P_PIPE  kinp;          Link to KLSYN input pipe                 */
/* extern  short   simage;        Switch image(NOT USED)                   */
/* extern  short   sprate;     MVP :Is now an element of Kernel_share_data */
/* Speaking rate                										   */
/* extern  short   last_voice;  MVP MI Not used                            */
/* Voice for tone reloads 												   */
/* extern  short curspdef[];    current speaker definition                 */
/* extern   int docitation;                                                */
/***************************************************************************/

/* 
 * Because the KRM uses a very large
 * number of index marks, Kurzweil asked for the index
 * event queue to be made larger. This was possible
 * because a lot of space was freed up in the RAM since
 * a lot of things (tasks, option buffers, and so on)
 * got deleted from the code.
 */

/* MVP : Function prototypes */

#if defined _UNIX_LIKE_
extern void spcfree(unsigned short *);
#endif

#ifndef MSDOS
void FreePHInstanceData (PDPH_T pDph_t);
void spcfree(unsigned short *); // NAL warning removal
#endif

/* Static function declarations */

/*
 *      Function Name:
 *
 *  	Description: process creation main ... this entry is called by the 
 *					 loader to create any static processes that are needed 
 *					 for this task ...
 *
 *      Arguments: 		
 *                 	#ifdef MSDOS
 *						data_seg, stack_start 
 *					#else
 *						LPTTS_HANDLE_T phTTS
 *      Return Value: int 0
 *
 *      Comments:
 *
 */

#ifdef WIN32

int __stdcall ph_main (LPTTS_HANDLE_T phTTS)

#endif

#ifdef MSDOS
struct TTS_HANDLE_TAG   hTTS;
LPTTS_HANDLE_T          phTTS;
DPHSETTAR_ST            STphsettar;
DPH_T                   Dph_t;

#define WITHOUT_CALLOC               
#ifndef NULL
#define NULL ((void *)0)
#endif

main (data_seg, stack_start)
	unsigned int            data_seg;
	unsigned int            stack_start;
#endif

#ifdef ARM7
#ifndef OS_PALM
#include <stdlib.h>
#include <string.h>
#endif //OS_PALM
#ifndef EPSON_ARM7
#ifndef OS_SYMBIAN
DPHSETTAR_ST            STphsettar;
DPH_T                   Dph_t;
#else
#include "GlobalDT.h"
#endif
#endif
int ph_main(LPTTS_HANDLE_T phTTS)
#endif

/* GL 04/21/1997  change to be the same as the latest OSF code */
#if defined _UNIX_LIKE_
#ifdef SINGLE_THREADED
DWORD ph_main(LPTTS_HANDLE_T phTTS)
#else
OP_THREAD_ROUTINE(ph_main, LPTTS_HANDLE_T phTTS)
#endif
#endif

{
	/* Added a variable to get the handle of Current instance krenel_share_data */
	PKSD_T                  pKsd_t;
	PDPH_T                  pDph_t = NULL;
	PDPHSETTAR_ST           pDphsettar_st = NULL;	/* Pointer to PHSETTAR.C file STATIC structure */

#ifdef WITHOUT_CALLOC
	int                     i;		   /* MVP : 03/18/96 */
#endif

#ifdef MSDOS
	phTTS = &hTTS;
	phTTS->pKernelShareData = kernel_share;		/* set a pointer to the KS structure */
	pKsd_t = phTTS->pKernelShareData;
	phTTS->pPHThreadData = &Dph_t;
	pDph_t = phTTS->pPHThreadData;
	pDph_t->pSTphsettar = &STphsettar;
	pDphsettar_st = pDph_t->pSTphsettar;
#elif defined ARM7
	pKsd_t = phTTS->pKernelShareData;
#ifdef EPSON_ARM7
	pDph_t = phTTS->pPHThreadData;
	pDphsettar_st = pDph_t->pSTphsettar;
	memset(pDph_t,0,sizeof(DPH_T));
	memset(pDphsettar_st,0,sizeof(DPHSETTAR_ST));
#else
#ifndef OS_SYMBIAN
	memset(&Dph_t,0,sizeof(DPH_T));
	memset(&STphsettar,0,sizeof(DPHSETTAR_ST));
	phTTS->pPHThreadData = &Dph_t;
	pDph_t = phTTS->pPHThreadData;
	pDph_t->pSTphsettar = &STphsettar;
	pDphsettar_st = pDph_t->pSTphsettar;
#else
	if((pDph_t = GetGlobalDTPtr()->Dph_t) == NULL)
	{
		pDph_t = malloc(sizeof(DPH_T));
		GetGlobalDTPtr()->Dph_t = pDph_t;
	}
	if((pDphsettar_st = GetGlobalDTPtr()->STphsettar) == NULL)
	{
		pDphsettar_st = malloc(sizeof(DPHSETTAR_ST));
		GetGlobalDTPtr()->STphsettar = pDphsettar_st;
	}
	memset(pDph_t,0,sizeof(DPH_T));
	memset(pDphsettar_st,0,sizeof(DPHSETTAR_ST));
	phTTS->pPHThreadData = pDph_t;
	pDph_t->pSTphsettar = pDphsettar_st;

#endif //OS_SYMBIAN
#endif
	/* MGS BATS 470 Fixed crashing due to reset */
			pDph_t->phTTS=phTTS;
#else
	pKsd_t = phTTS->pKernelShareData;
#if defined _UNIX_LIKE_
    /* GL 04/21/1997  add this as the latest OSF code */
    /* Initialize thread error field to no error */
    phTTS->uiThreadError = MMSYSERR_NOERROR;
#endif

#ifdef SEPARATE_PROCESSES
	kernel_share = (struct share_data *) malloc (sizeof (struct share_data));

#endif


	/* MVP MI kinp is not used in this function  kinp = pKsd_t->lang_ph[LANG_english]; */
	if ((pDph_t = (PDPH_T) calloc (1, sizeof (DPH_T))) == NULL)
#ifdef SINGLE_THREADED
		return (MMSYSERR_NOMEM);
#else
#ifdef WIN32
		return (MMSYSERR_NOMEM);
#endif
#if defined _UNIX_LIKE_
		phTTS->uiThreadError = MMSYSERR_NOMEM;
        else
#endif
#endif // SINGLE_THREADED
        {
			/* Associate this PH thread instance specific structure with current speech object */
			phTTS->pPHThreadData = pDph_t;
#ifndef MSDOS
			/* MGS BATS 470 Fixed crashing due to reset */
			pDph_t->phTTS=phTTS;
#endif
			/* MVP : Initialize all structure pointers in DPH_T to NULL. */
			pDph_t->pSTphsettar = NULL;
			
			/****************************************************************************/
			/* MVP : Allocation of structures specific to STATIC varaibles in each file */
			/****************************************************************************/
			
			/* Structure for PHSETTAR.C file specific static variables */
			/* MVP: 03/19/96 Use calloc() to initialize all elements to zero. */
			if ((pDphsettar_st = (PDPHSETTAR_ST) calloc (1, sizeof (DPHSETTAR_ST))) == NULL)
			{
				FreePHInstanceData (pDph_t);
				phTTS->pPHThreadData = NULL;
#ifdef SINGLE_THREADED
				return(MMSYSERR_NOMEM);
#else
#ifdef WIN32
				return (MMSYSERR_NOMEM);
#endif
#if defined _UNIX_LIKE_
			phTTS->uiThreadError = MMSYSERR_NOMEM;
		
#endif
#endif // SINGLE_THREADED
			}
		}

#ifndef SINGLE_THREADED
#ifdef WIN32
SetEvent (phTTS->hMallocSuccessEvent);	/* Malloc s are success,set the event */
#endif
#if defined _UNIX_LIKE_
        /* CP: Set the event, even if malloc eerror occurred. User
         * will look at uiThreadError for actual error code.
         */
		OP_SetEvent(phTTS->hMallocSuccessEvent);
        if (phTTS->uiThreadError != MMSYSERR_NOERROR)
		{
			OP_ExitThread(phTTS->uiThreadError);
			OP_THREAD_RETURN;
		}
#endif
#endif // SINGLE_THREADED
#endif // !MSDOS
	/* Associate this structure handle with current PH thread data structure */
	pDph_t->pSTphsettar = pDphsettar_st;
	/* MVP :Do required initialization of certain elements of DPHSETTAR_ST structure */
#ifdef WITHOUT_CALLOC
	pDphsettar_st->drawinitsw = 0;
	pDphsettar_st->breathyah = 0;
	pDphsettar_st->breathytilt = 0;
	pDphsettar_st->nrises_sofar = 0;
	pDphsettar_st->hatsize = 0;    
	pDphsettar_st->tarbas=0;
	pDphsettar_st->hat_loc_re_baseline = 0;
	pDphsettar_st->initsw = 0;		   	/* MVP :03/19/96 */
	pDphsettar_st->sprlast = 0;		   	/* MVP :03/19/96 */
	pDphsettar_st->strucstressprev = 0;	/* MVP :03/19/96 */      
	pDphsettar_st->phonex_drawt0 = 0;  	/* MVP :03/19/96 */
	pDphsettar_st->tarseg = 0;		   	/* MVP :03/19/96 */
	pDphsettar_st->tarseg1 = 0;		   	/* MVP :03/19/96 */
	pDphsettar_st->nimp = 0;		   	/* MVP :03/19/96 */
	pDphsettar_st->timecos10 = 0;	   	/* MVP :03/19/96 */
	pDphsettar_st->timecos15 = 0;	   	/* MVP :03/19/96 */
	pDphsettar_st->timecosvib = 0;	/* MVP :03/19/96 */
	/* MVP : 03/15/96 Do required initialization of certain elements of  DPH_T structure    */
	pDph_t->initpardelay = 0;
	/* MVP: 03/18/96 */
	for (i = 0; i < VOICE_PARS; i++)
		pDph_t->parstochip[i] = 0;
	pDph_t->shrink=0;
	pDph_t->shrib=0;
	pDph_t->shrif=0;


#ifdef PH_SWAPDATA
	pDph_t->PHSwapCnt=0; //Foe evan balaban
#endif


#endif  // WITHOUT_CALLOC

	/* MVP : Initialize the speaker param arrays voidef,voidef_8 here */
	/* NAL : */
 	
#ifdef EPSON_ARM7
	pDph_t->voidef_8[0] = (short*)paul_8;
	pDph_t->voidef_8[1] = (short*)paul_8;
	pDph_t->voidef_8[2] = (short*)paul_8;
	pDph_t->voidef_8[3] = (short*)paul_8;
	pDph_t->voidef_8[4] = (short*)paul_8;
	pDph_t->voidef_8[5] = (short*)paul_8;
	pDph_t->voidef_8[6] = (short*)paul_8;
	pDph_t->voidef_8[7] = (short*)paul_8;
	pDph_t->voidef_8[8] = (short*)paul_8;
	pDph_t->voidef_8[9] = (short*)paul_8;

	// CAB Removed warnings by typecast
	pDph_t->voidef[0] = (short*)paul;
	pDph_t->voidef[1] = (short*)paul;
	pDph_t->voidef[2] = (short*)paul;
	pDph_t->voidef[3] = (short*)paul;
	pDph_t->voidef[4] = (short*)paul;
	pDph_t->voidef[5] = (short*)paul;
	pDph_t->voidef[6] = (short*)paul;
	pDph_t->voidef[7] = (short*)paul;
	pDph_t->voidef[8] = (short*)paul;
	pDph_t->voidef[9] = (short*)paul;
#elif defined CASIO_SH3
	// CAB Removed warnings by typecast
	if(pKsd_t->lang_curr == LANG_french)
	{
	pDph_t->voidef_8[0] = (short*)fr_paul;
	pDph_t->voidef_8[1] = (short*)fr_betty;
	pDph_t->voidef_8[2] = (short*)fr_harry;
	pDph_t->voidef_8[3] = (short*)fr_frank;
	pDph_t->voidef_8[4] = (short*)fr_dennis;
	pDph_t->voidef_8[5] = (short*)fr_kit;
	pDph_t->voidef_8[6] = (short*)fr_ursula;
	pDph_t->voidef_8[7] = (short*)fr_rita;
	pDph_t->voidef_8[8] = (short*)fr_wendy;
//	pDph_t->voidef_8[9] = pDph_t->var_val;


	}

	else 
	{
	pDph_t->voidef_8[0] = (short*)us_paul;
	pDph_t->voidef_8[1] = (short*)us_betty;
	pDph_t->voidef_8[2] = (short*)us_harry;
	pDph_t->voidef_8[3] = (short*)us_frank;
	pDph_t->voidef_8[4] = (short*)us_dennis;
	pDph_t->voidef_8[5] = (short*)us_kit;
	pDph_t->voidef_8[6] = (short*)us_ursula;
	pDph_t->voidef_8[7] = (short*)us_rita;
	pDph_t->voidef_8[8] = (short*)us_wendy;
//	pDph_t->voidef_8[9] = pDph_t->var_val;
	}
	

#else

	// CAB Removed warnings by typecast
	pDph_t->voidef[0] = (short*)paul;
	pDph_t->voidef[1] = (short*)betty;
	pDph_t->voidef[2] = (short*)harry;
	pDph_t->voidef[3] = (short*)frank;
	pDph_t->voidef[4] = (short*)dennis;
	pDph_t->voidef[5] = (short*)kit;
	pDph_t->voidef[6] = (short*)ursula;
	pDph_t->voidef[7] = (short*)rita;
	pDph_t->voidef[8] = (short*)wendy;
	pDph_t->voidef[9] = (short*)ed;
	pDph_t->voidef[10] = (short*)matt;
	pDph_t->voidef[11] = (short*)sue;
	pDph_t->voidef[12] = (short*)mary;
	pDph_t->voidef[13] = (short*)lynn;
	pDph_t->voidef[14] = (short*)tom;
	pDph_t->voidef[15] = (short*)ivan;
	pDph_t->voidef[16] = (short*)charline;
	pDph_t->voidef[17] = (short*)jackie;
	pDph_t->voidef[18] = pDph_t->var_val;
#endif


#ifdef EPSON_ARM7
	pDph_t->tunedef_8[0] = (short*)default_tune;
	pDph_t->tunedef_8[1] = (short*)default_tune;;
	pDph_t->tunedef_8[2] = (short*)default_tune;;
	pDph_t->tunedef_8[3] = (short*)default_tune;;
	pDph_t->tunedef_8[4] = (short*)default_tune;;
	pDph_t->tunedef_8[5] = (short*)default_tune;;
	pDph_t->tunedef_8[6] = (short*)default_tune;;
	pDph_t->tunedef_8[7] = (short*)default_tune;;
	pDph_t->tunedef_8[8] = (short*)default_tune;;
	pDph_t->tunedef_8[9] = (short*)default_tune;;
	pDph_t->tunedef[0] = (short*)default_tune;;
	pDph_t->tunedef[1] = (short*)default_tune;;
	pDph_t->tunedef[2] = (short*)default_tune;;
	pDph_t->tunedef[3] = (short*)default_tune;;
	pDph_t->tunedef[4] = (short*)default_tune;;
	pDph_t->tunedef[5] = (short*)default_tune;;
	pDph_t->tunedef[6] = (short*)default_tune;;
	pDph_t->tunedef[7] = (short*)default_tune;;
	pDph_t->tunedef[8] = (short*)default_tune;;
	pDph_t->tunedef[9] = (short*)default_tune;;
#elif defined CASIO_SH3
	if(pKsd_t->lang_curr == LANG_english)
	{
	pDph_t->tunedef_8[0] = (short*)us_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)us_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)us_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)us_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)us_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)us_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)us_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)us_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)us_wendy_8_tune;

	}

	if(pKsd_t->lang_curr == LANG_spanish)
	{
	pDph_t->tunedef_8[0] = (short*)sp_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)sp_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)sp_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)sp_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)sp_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)sp_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)sp_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)sp_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)sp_wendy_8_tune;

	}
	if(pKsd_t->lang_curr == LANG_french)
	{
	pDph_t->tunedef_8[0] = (short*)fr_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)fr_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)fr_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)fr_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)fr_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)fr_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)fr_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)fr_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)fr_wendy_8_tune;

	}
	if(pKsd_t->lang_curr == LANG_german)
	{
	pDph_t->tunedef_8[0] = (short*)gr_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)gr_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)gr_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)gr_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)gr_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)gr_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)gr_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)gr_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)gr_wendy_8_tune;

	}
	if(pKsd_t->lang_curr == LANG_italian)
	{
	pDph_t->tunedef_8[0] = (short*)it_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)it_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)it_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)it_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)it_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)it_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)it_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)it_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)it_wendy_8_tune;

	}

#else
//	if(pKsd_t->lang_curr == LANG_english)
	{
	pDph_t->tunedef_8[0] = (short*)us_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)us_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)us_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)us_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)us_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)us_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)us_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)us_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)us_wendy_8_tune;
	pDph_t->tunedef_8[9] = (short*)us_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)us_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)us_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)us_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)us_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)us_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)us_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)us_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)us_jackie_8_tune;
	pDph_t->tunedef[0] = (short*)us_paul_tune;
	pDph_t->tunedef[1] = (short*)us_betty_tune;
	pDph_t->tunedef[2] = (short*)us_harry_tune;
	pDph_t->tunedef[3] = (short*)us_frank_tune;
	pDph_t->tunedef[4] = (short*)us_dennis_tune;
	pDph_t->tunedef[5] = (short*)us_kit_tune;
	pDph_t->tunedef[6] = (short*)us_ursula_tune;
	pDph_t->tunedef[7] = (short*)us_rita_tune;
	pDph_t->tunedef[8] = (short*)us_wendy_tune;
	pDph_t->tunedef[9] =  (short*)us_ed_tune;
	pDph_t->tunedef[10] = (short*)us_matt_tune;
	pDph_t->tunedef[11] = (short*)us_sue_tune;
	pDph_t->tunedef[12] = (short*)us_mary_tune;
	pDph_t->tunedef[13] = (short*)us_lynn_tune;
	pDph_t->tunedef[14] = (short*)us_tom_tune;
	pDph_t->tunedef[15] = (short*)us_ivan_tune;
	pDph_t->tunedef[16] = (short*)us_charline_tune;
	pDph_t->tunedef[17] = (short*)us_jackie_tune;
	}
#if 0
	if(pKsd_t->lang_curr == LANG_japanese)
	{
	pDph_t->tunedef_8[0] = (short*)jp_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)jp_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)jp_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)jp_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)jp_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)jp_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)jp_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)jp_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)jp_wendy_8_tune;
	pDph_t->tunedef_8[9] = (short*)jp_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)jp_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)jp_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)jp_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)jp_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)jp_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)jp_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)jp_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)jp_jackie_8_tune;
	pDph_t->tunedef[0] = (short*)jp_paul_tune;
	pDph_t->tunedef[1] = (short*)jp_betty_tune;
	pDph_t->tunedef[2] = (short*)jp_harry_tune;
	pDph_t->tunedef[3] = (short*)jp_frank_tune;
	pDph_t->tunedef[4] = (short*)jp_dennis_tune;
	pDph_t->tunedef[5] = (short*)jp_kit_tune;
	pDph_t->tunedef[6] = (short*)jp_ursula_tune;
	pDph_t->tunedef[7] = (short*)jp_rita_tune;
	pDph_t->tunedef[8] = (short*)jp_wendy_tune;
	pDph_t->tunedef[9] =  (short*)jp_ed_tune;
	pDph_t->tunedef[10] = (short*)jp_matt_tune;
	pDph_t->tunedef[11] = (short*)jp_sue_tune;
	pDph_t->tunedef[12] = (short*)jp_mary_tune;
	pDph_t->tunedef[13] = (short*)jp_lynn_tune;
	pDph_t->tunedef[14] = (short*)jp_tom_tune;
	pDph_t->tunedef[15] = (short*)jp_ivan_tune;
	pDph_t->tunedef[16] = (short*)jp_charline_tune;
	pDph_t->tunedef[17] = (short*)jp_jackie_tune;
	}
	if(pKsd_t->lang_curr == LANG_british)
	{
	pDph_t->tunedef_8[0] = (short*)uk_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)uk_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)uk_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)uk_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)uk_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)uk_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)uk_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)uk_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)uk_wendy_8_tune;
	pDph_t->tunedef_8[9] =  (short*)uk_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)uk_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)uk_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)uk_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)uk_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)uk_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)uk_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)uk_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)uk_jackie_8_tune;
	pDph_t->tunedef[0] = (short*)uk_paul_tune;
	pDph_t->tunedef[1] = (short*)uk_betty_tune;
	pDph_t->tunedef[2] = (short*)uk_harry_tune;
	pDph_t->tunedef[3] = (short*)uk_frank_tune;
	pDph_t->tunedef[4] = (short*)uk_dennis_tune;
	pDph_t->tunedef[5] = (short*)uk_kit_tune;
	pDph_t->tunedef[6] = (short*)uk_ursula_tune;
	pDph_t->tunedef[7] = (short*)uk_rita_tune;
	pDph_t->tunedef[8] = (short*)uk_wendy_tune;
	pDph_t->tunedef[9] =  (short*)uk_ed_tune;
	pDph_t->tunedef[10] = (short*)uk_matt_tune;
	pDph_t->tunedef[11] = (short*)uk_sue_tune;
	pDph_t->tunedef[12] = (short*)uk_mary_tune;
	pDph_t->tunedef[13] = (short*)uk_lynn_tune;
	pDph_t->tunedef[14] = (short*)uk_tom_tune;
	pDph_t->tunedef[15] = (short*)uk_ivan_tune;
	pDph_t->tunedef[16] = (short*)uk_charline_tune;
	pDph_t->tunedef[17] = (short*)uk_jackie_tune;
	}

	if(pKsd_t->lang_curr == LANG_latin_american)
	{
	pDph_t->tunedef_8[0] = (short*)la_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)la_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)la_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)la_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)la_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)la_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)la_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)la_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)la_wendy_8_tune;
	pDph_t->tunedef_8[9] =  (short*)la_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)la_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)la_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)la_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)la_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)la_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)la_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)la_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)la_jackie_8_tune;
	pDph_t->tunedef[0] = (short*)la_paul_tune;
	pDph_t->tunedef[1] = (short*)la_betty_tune;
	pDph_t->tunedef[2] = (short*)la_harry_tune;
	pDph_t->tunedef[3] = (short*)la_frank_tune;
	pDph_t->tunedef[4] = (short*)la_dennis_tune;
	pDph_t->tunedef[5] = (short*)la_kit_tune;
	pDph_t->tunedef[6] = (short*)la_ursula_tune;
	pDph_t->tunedef[7] = (short*)la_rita_tune;
	pDph_t->tunedef[8] = (short*)la_wendy_tune;
	pDph_t->tunedef[9] =  (short*)la_ed_tune;
	pDph_t->tunedef[10] = (short*)la_matt_tune;
	pDph_t->tunedef[11] = (short*)la_sue_tune;
	pDph_t->tunedef[12] = (short*)la_mary_tune;
	pDph_t->tunedef[13] = (short*)la_lynn_tune;
	pDph_t->tunedef[14] = (short*)la_tom_tune;
	pDph_t->tunedef[15] = (short*)la_ivan_tune;
	pDph_t->tunedef[16] = (short*)la_charline_tune;
	pDph_t->tunedef[17] = (short*)la_jackie_tune;
	}
	if(pKsd_t->lang_curr == LANG_spanish)
	{
	pDph_t->tunedef_8[0] = (short*)sp_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)sp_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)sp_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)sp_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)sp_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)sp_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)sp_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)sp_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)sp_wendy_8_tune;
	pDph_t->tunedef_8[9] =  (short*)sp_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)sp_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)sp_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)sp_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)sp_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)sp_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)sp_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)sp_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)sp_jackie_8_tune;
	pDph_t->tunedef[0] = (short*)sp_paul_tune;
	pDph_t->tunedef[1] = (short*)sp_betty_tune;
	pDph_t->tunedef[2] = (short*)sp_harry_tune;
	pDph_t->tunedef[3] = (short*)sp_frank_tune;
	pDph_t->tunedef[4] = (short*)sp_dennis_tune;
	pDph_t->tunedef[5] = (short*)sp_kit_tune;
	pDph_t->tunedef[6] = (short*)sp_ursula_tune;
	pDph_t->tunedef[7] = (short*)sp_rita_tune;
	pDph_t->tunedef[8] = (short*)sp_wendy_tune;
	pDph_t->tunedef[9] =  (short*)sp_ed_tune;
	pDph_t->tunedef[10] = (short*)sp_matt_tune;
	pDph_t->tunedef[11] = (short*)sp_sue_tune;
	pDph_t->tunedef[12] = (short*)sp_mary_tune;
	pDph_t->tunedef[13] = (short*)sp_lynn_tune;
	pDph_t->tunedef[14] = (short*)sp_tom_tune;
	pDph_t->tunedef[15] = (short*)sp_ivan_tune;
	pDph_t->tunedef[16] = (short*)sp_charline_tune;
	pDph_t->tunedef[17] = (short*)sp_jackie_tune;
	}
	if(pKsd_t->lang_curr == LANG_french)
	{
	pDph_t->tunedef_8[0] = (short*)fr_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)fr_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)fr_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)fr_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)fr_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)fr_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)fr_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)fr_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)fr_wendy_8_tune;
	pDph_t->tunedef_8[9] =  (short*)fr_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)fr_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)fr_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)fr_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)fr_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)fr_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)fr_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)fr_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)fr_jackie_8_tune;
	pDph_t->tunedef[0] = (short*)fr_paul_tune;
	pDph_t->tunedef[1] = (short*)fr_betty_tune;
	pDph_t->tunedef[2] = (short*)fr_harry_tune;
	pDph_t->tunedef[3] = (short*)fr_frank_tune;
	pDph_t->tunedef[4] = (short*)fr_dennis_tune;
	pDph_t->tunedef[5] = (short*)fr_kit_tune;
	pDph_t->tunedef[6] = (short*)fr_ursula_tune;
	pDph_t->tunedef[7] = (short*)fr_rita_tune;
	pDph_t->tunedef[8] = (short*)fr_wendy_tune;
	pDph_t->tunedef[9] =  (short*)fr_ed_tune;
	pDph_t->tunedef[10] = (short*)fr_matt_tune;
	pDph_t->tunedef[11] = (short*)fr_sue_tune;
	pDph_t->tunedef[12] = (short*)fr_mary_tune;
	pDph_t->tunedef[13] = (short*)fr_lynn_tune;
	pDph_t->tunedef[14] = (short*)fr_tom_tune;
	pDph_t->tunedef[15] = (short*)fr_ivan_tune;
	pDph_t->tunedef[16] = (short*)fr_charline_tune;
	pDph_t->tunedef[17] = (short*)fr_jackie_tune;
	}
	if(pKsd_t->lang_curr == LANG_german)
	{
	pDph_t->tunedef_8[0] = (short*)gr_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)gr_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)gr_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)gr_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)gr_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)gr_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)gr_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)gr_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)gr_wendy_8_tune;
	pDph_t->tunedef_8[9] =  (short*)gr_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)gr_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)gr_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)gr_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)gr_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)gr_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)gr_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)gr_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)gr_jackie_8_tune;
	pDph_t->tunedef[0] = (short*)gr_paul_tune;
	pDph_t->tunedef[1] = (short*)gr_betty_tune;
	pDph_t->tunedef[2] = (short*)gr_harry_tune;
	pDph_t->tunedef[3] = (short*)gr_frank_tune;
	pDph_t->tunedef[4] = (short*)gr_dennis_tune;
	pDph_t->tunedef[5] = (short*)gr_kit_tune;
	pDph_t->tunedef[6] = (short*)gr_ursula_tune;
	pDph_t->tunedef[7] = (short*)gr_rita_tune;
	pDph_t->tunedef[8] = (short*)gr_wendy_tune;
	pDph_t->tunedef[9] =  (short*)gr_ed_tune;
	pDph_t->tunedef[10] = (short*)gr_matt_tune;
	pDph_t->tunedef[11] = (short*)gr_sue_tune;
	pDph_t->tunedef[12] = (short*)gr_mary_tune;
	pDph_t->tunedef[13] = (short*)gr_lynn_tune;
	pDph_t->tunedef[14] = (short*)gr_tom_tune;
	pDph_t->tunedef[15] = (short*)gr_ivan_tune;
	pDph_t->tunedef[16] = (short*)gr_charline_tune;
	pDph_t->tunedef[17] = (short*)gr_jackie_tune;
	}
	if(pKsd_t->lang_curr == LANG_italian)
	{
	pDph_t->tunedef_8[0] = (short*)it_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)it_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)it_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)it_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)it_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)it_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)it_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)it_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)it_wendy_8_tune;
	pDph_t->tunedef_8[9] =  (short*)it_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)it_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)it_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)it_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)it_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)it_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)it_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)it_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)it_jackie_8_tune;
	pDph_t->tunedef[0] = (short*)it_paul_tune;
	pDph_t->tunedef[1] = (short*)it_betty_tune;
	pDph_t->tunedef[2] = (short*)it_harry_tune;
	pDph_t->tunedef[3] = (short*)it_frank_tune;
	pDph_t->tunedef[4] = (short*)it_dennis_tune;
	pDph_t->tunedef[5] = (short*)it_kit_tune;
	pDph_t->tunedef[6] = (short*)it_ursula_tune;
	pDph_t->tunedef[7] = (short*)it_rita_tune;
	pDph_t->tunedef[8] = (short*)it_wendy_tune;
	pDph_t->tunedef[9] =  (short*)it_ed_tune;
	pDph_t->tunedef[10] = (short*)it_matt_tune;
	pDph_t->tunedef[11] = (short*)it_sue_tune;
	pDph_t->tunedef[12] = (short*)it_mary_tune;
	pDph_t->tunedef[13] = (short*)it_lynn_tune;
	pDph_t->tunedef[14] = (short*)it_tom_tune;
	pDph_t->tunedef[15] = (short*)it_ivan_tune;
	pDph_t->tunedef[16] = (short*)it_charline_tune;
	pDph_t->tunedef[17] = (short*)it_jackie_tune;
	}
	if(pKsd_t->lang_curr == LANG_korean)
	{
	pDph_t->tunedef_8[0] = (short*)kr_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)kr_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)kr_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)kr_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)kr_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)kr_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)kr_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)kr_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)kr_wendy_8_tune;
	pDph_t->tunedef_8[9] =  (short*)kr_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)kr_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)kr_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)kr_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)kr_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)kr_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)kr_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)kr_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)kr_jackie_8_tune;
	pDph_t->tunedef[0] = (short*)kr_paul_tune;
	pDph_t->tunedef[1] = (short*)kr_betty_tune;
	pDph_t->tunedef[2] = (short*)kr_harry_tune;
	pDph_t->tunedef[3] = (short*)kr_frank_tune;
	pDph_t->tunedef[4] = (short*)kr_dennis_tune;
	pDph_t->tunedef[5] = (short*)kr_kit_tune;
	pDph_t->tunedef[6] = (short*)kr_ursula_tune;
	pDph_t->tunedef[7] = (short*)kr_rita_tune;
	pDph_t->tunedef[8] = (short*)kr_wendy_tune;
	pDph_t->tunedef[9] =  (short*)kr_ed_tune;
	pDph_t->tunedef[10] = (short*)kr_matt_tune;
	pDph_t->tunedef[11] = (short*)kr_sue_tune;
	pDph_t->tunedef[12] = (short*)kr_mary_tune;
	pDph_t->tunedef[13] = (short*)kr_lynn_tune;
	pDph_t->tunedef[14] = (short*)kr_tom_tune;
	pDph_t->tunedef[15] = (short*)kr_ivan_tune;
	pDph_t->tunedef[16] = (short*)kr_charline_tune;
	pDph_t->tunedef[17] = (short*)kr_jackie_tune;
	}

	if(pKsd_t->lang_curr == LANG_chinese)
	{
	pDph_t->tunedef_8[0] = (short*)ch_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)ch_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)ch_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)ch_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)ch_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)ch_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)ch_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)ch_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)ch_wendy_8_tune;
	pDph_t->tunedef_8[9] =  (short*)ch_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)ch_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)ch_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)ch_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)ch_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)ch_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)ch_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)ch_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)ch_jackie_8_tune;
	pDph_t->tunedef[0] = (short*)ch_paul_tune;
	pDph_t->tunedef[1] = (short*)ch_betty_tune;
	pDph_t->tunedef[2] = (short*)ch_harry_tune;
	pDph_t->tunedef[3] = (short*)ch_frank_tune;
	pDph_t->tunedef[4] = (short*)ch_dennis_tune;
	pDph_t->tunedef[5] = (short*)ch_kit_tune;
	pDph_t->tunedef[6] = (short*)ch_ursula_tune;
	pDph_t->tunedef[7] = (short*)ch_rita_tune;
	pDph_t->tunedef[8] = (short*)ch_wendy_tune;
	pDph_t->tunedef[9] =  (short*)ch_ed_tune;
	pDph_t->tunedef[10] = (short*)ch_matt_tune;
	pDph_t->tunedef[11] = (short*)ch_sue_tune;
	pDph_t->tunedef[12] = (short*)ch_mary_tune;
	pDph_t->tunedef[13] = (short*)ch_lynn_tune;
	pDph_t->tunedef[14] = (short*)ch_tom_tune;
	pDph_t->tunedef[15] = (short*)ch_ivan_tune;
	pDph_t->tunedef[16] = (short*)ch_charline_tune;
	pDph_t->tunedef[17] = (short*)ch_jackie_tune;
	}

	if(pKsd_t->lang_curr == LANG_hebrew)
	{
	pDph_t->tunedef_8[0] = (short*)hb_paul_8_tune;
	pDph_t->tunedef_8[1] = (short*)hb_betty_8_tune;
	pDph_t->tunedef_8[2] = (short*)hb_harry_8_tune;
	pDph_t->tunedef_8[3] = (short*)hb_frank_8_tune;
	pDph_t->tunedef_8[4] = (short*)hb_dennis_8_tune;
	pDph_t->tunedef_8[5] = (short*)hb_kit_8_tune;
	pDph_t->tunedef_8[6] = (short*)hb_ursula_8_tune;
	pDph_t->tunedef_8[7] = (short*)hb_rita_8_tune;
	pDph_t->tunedef_8[8] = (short*)hb_wendy_8_tune;
	pDph_t->tunedef_8[9] =  (short*)hb_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)hb_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)hb_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)hb_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)hb_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)hb_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)hb_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)hb_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)hb_jackie_8_tune;
	pDph_t->tunedef[0] = (short*)hb_paul_tune;
	pDph_t->tunedef[1] = (short*)hb_betty_tune;
	pDph_t->tunedef[2] = (short*)hb_harry_tune;
	pDph_t->tunedef[3] = (short*)hb_frank_tune;
	pDph_t->tunedef[4] = (short*)hb_dennis_tune;
	pDph_t->tunedef[5] = (short*)hb_kit_tune;
	pDph_t->tunedef[6] = (short*)hb_ursula_tune;
	pDph_t->tunedef[7] = (short*)hb_rita_tune;
	pDph_t->tunedef[8] = (short*)hb_wendy_tune;
	pDph_t->tunedef[9] =  (short*)hb_ed_tune;
	pDph_t->tunedef[10] = (short*)hb_matt_tune;
	pDph_t->tunedef[11] = (short*)hb_sue_tune;
	pDph_t->tunedef[12] = (short*)hb_mary_tune;
	pDph_t->tunedef[13] = (short*)hb_lynn_tune;
	pDph_t->tunedef[14] = (short*)hb_tom_tune;
	pDph_t->tunedef[15] = (short*)hb_ivan_tune;
	pDph_t->tunedef[16] = (short*)hb_charline_tune;
	pDph_t->tunedef[17] = (short*)hb_jackie_tune;
	}
#endif
#endif


#ifdef MSDOS
	pKsd_t->lang_curr = LANG_none;	/* KM added for initilizing lang tables */
#endif

#ifdef MSDOS
#ifdef ENGLISH_US
		default_lang (LANG_english, LANG_ph_ready);
#endif
#ifdef ENGLISH_UK
		default_lang (LANG_british, LANG_ph_ready);
#endif
#ifdef SPANISH_SP
		default_lang (LANG_spanish, LANG_ph_ready);
#endif
#ifdef SPANISH_LA
		default_lang (LANG_latin_american, LANG_ph_ready);
#endif
#ifdef GERMAN                        
		default_lang (LANG_german, LANG_ph_ready);
#endif
#ifdef FRENCH
		default_lang (LANG_french, LANG_ph_ready);
#endif
#ifdef ITALIAN
		default_lang (LANG_italian, LANG_ph_ready);
#endif
#ifdef JAPANESE
		default_lang (LANG_japanses, LANG_ph_ready);
#endif
#ifdef HEBREW
		default_lang (LANG_hebrew, LANG_ph_ready);
#endif
#ifdef CHINESE
		default_lang (LANG_chinese, LANG_ph_ready);
#endif
#ifdef KOREAN
		default_lang (LANG_korean, LANG_ph_ready);
#endif

	create_process (kltask, 4, data_seg, stack_start, 0);


#else
	default_lang (pKsd_t, pKsd_t->lang_curr, LANG_ph_ready);

	kltask (phTTS);
#ifdef SINGLE_THREADED
	return MMSYSERR_NOERROR;
#else
	/* Free the allocated instance specific structure,before the thread returns */
	FreePHInstanceData (pDph_t);
	phTTS->pPHThreadData = pDph_t = NULL;
#endif
#if defined (MSDOS) || defined (WIN32)
	return 0;						/* No error MVP */
#endif
#if defined _UNIX_LIKE_
#ifdef SINGLE_THREADED
	return MMSYSERR_NOERROR;
#else
		OP_ExitThread(MMSYSERR_NOERROR);
		OP_THREAD_RETURN;
#endif
#endif
#endif
}

#ifndef MSDOS
#ifndef ARM7
void FreePHInstanceData(PDPH_T pDph_t)
{
if (pDph_t->pSTphsettar)
     free (pDph_t->pSTphsettar);
     pDph_t->pSTphsettar = NULL;
     
     // tek 13aug96 have to free the last delaypars
     if(pDph_t->delaypars)
     spcfree(pDph_t->delaypars);
     
     if (pDph_t)
     free (pDph_t);
     
pDph_t = NULL;
     
     }
#endif
#endif
/*****************************end of phmain.c**************************************/
