
/* 
 ***********************************************************************
 *
 *                           Copyright �
 *    Copyright � 2000-2001 Force Computers, Inc., a Solectron company. All rights reserved.
 *    � Digital Equipment Corporation 1996, 1997, 1998. All rights reserved.
 *
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Force Computers Incorporated and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Force or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:    ph_vset.c
 *    Author:       Dennis Klatt
 *    Creation Date:01-JAN-1985
 *
 *    Functionality:
 * 	  This file contains functions
 * 	  to select new speakers, to change individual
 * 	  fields of a speaker definition, and to
 * 	  convert the values from the format used by
 * 	  the voice commands to the format used by
 * 	  the signal processor. Based on the one for
 * 	  the new synthesizer.
 *
 ***********************************************************************
 *    Revision History:
 *
 * Rev  Who     Date        Description
 * ---  -----   ----------- -------------------------------------------- 
 * 0001 DK		01/01/1985  Initial creation
 * 0002 DGC		01/02/1985  The speaker def. code called "SPD_AS" "2".
 *          				Not a bug, just a tidy up.
 * 0003 DGC 	01/19/1985  The LIMIT structure def. is now in phdefs.h
 * 0004 DK		02/19/1985  Send to chip only pars that are used
#ifdef ENGLISH_US           Merged from phvset.c
 * 0005 DK		01/13/1985  Add Vax-only code to print spdefs for manual
 * 0006 DGC		06/18/1985  "g5" => "lo".
 * 0007 DK		07/18/1985  Rescale "SPD_FT".
 * 0008 DK		07/25/1985  Rescale spdeftltoff.
 * 0009 MGS		03/25/1996  Merged Win95 Code with 42c
 * 0010 EAB		04/04/1996  SPD_BR has had a bug since day one it wanted to be
 *                      	sp_br**2 >>1 not <<1 so that 100(max) is close to
 *                      	096(1 in frac arith) + sp_br**2 >>1 aprox max
 *                      	value of 8192.
 * 0011 tek		04/23/1996  remove spurious printf from 0010 (v26)
 * 0012 MGS		05/29/1996 	merged 0010 ad 0011 from english
#endif
#ifdef SPANISH              Merged from sphvset.c
 * 0005 MM		04/02/1985  68000
 * 0006 DF		03/06/1986  DT3 updates:  SPD_EF -> SPD_LX ; SPD_G5 -> SPD_LO
#endif
 * 0011	MGS		06/04/1996 	Merged spanish with english
 * 0012	MGS		06/06/1996	Changed file name from phvset.c ph_vset.c
 * 0013	MGS		06/18/1996	Merged German with english/spanish
 * 0014	GL		04/21/1997	BATS#360  remove spaces before "#define" or "#if" 
 * 0015 EAB		05/07/1997	EAB Adjust overall imbalance of apiration
 * 0016 DR		09/30/1997	UK BUILD: added UK STUFF
 * 0017 MGS     04/06/1998  made curspdef contain the speaker number
 * 0018 JAW     04/27/1998  Changed setparam so it will accept parameters up to SPD_GS
 *                          instead of SP_SR.
 * 0020 EAB		04/27/1998	Added code to support gs speaker def tha JAW added to arrray
 * 0021 JAW     05/04/1998  Made code from 4/6/98 only be compiled under non-MS-DOS
 *                          environments.
 * 0022 EAB     07/14/1998	Move code from malboundary to locus theory for SPANISH
 * 0023 EAB		10/9/1998	Verified hypothesis that malamp and femamp tables can be the same
							and implemented same saves some space and lots of tuning
 * 0024 EAB		10/15/1998	Removed German fudge factors code "more better"
 * 0025	EAB		10/16/1998	Modifiy the code to make Castillion more distinct from latin by making the fric
							and aspir stronger
 * 0026 EAB		10/16/1998	Last fix had a bug fixed it
 * 0027 EAB		10/26/1998	Reduce scaling of laryngealization most of range was perceptually useless 
 * 0028 EAB		10/24/1998	Code to use just mal_amp has proven sucessful-It simplifies tuning and takes advantage
							of the fact that the male voiecs have recieved more attention
 * 0029 EAB		10/29/1998	Added code to compensate fo LOWCOMPUTE voice gain changes
 * 0030 EAB		11/16/1998	BATS 804 added code to check limits of speaker definition
 * 0031 EAB		06/26/1999	Added in ifdef NEW_VOLUME code to test out and document an ph only software volume cobtrol
							this is not implemented 
 * 0032 EAB		10/07/1999	remove NEW_VOLUME and replace with Lockheed Martin SW_VOLUME
 * 0033 EAB		10/28/1999	Modified to support Lookheed-Martin chnages with ifdef SW_VOLUME
 * 0034 NAL		01/24/2000	Modified setparam to ignore tuned params if bDoTuning flag is set
 * 0035 EAB		04/07/2000 	Modified SP_ for universal phonemes
 * 0035 NAL		04/14/2000	Fix externs maltar, femtar, maldip, femdip, malamp, femamp, 
 * 							maleloc, femloc to match declarations in p_*_rom.c
 * 0036 CHJ		07/20/2000	Added French
 * 0037	CAB		10/18/2000	Fixed copyright info and formatted comments
 * 0039 EAB 	12/6/2000 	CHnage to reduce gettar overhead for 4.61
 * 0040 EAB 	03/15/2001 	Changed to left shift rather than mult by 8 for efficiency
 * 0041 CAB		03/16/2001	Updated copyright info
 * 0042	MFG		05/29/2001	Included dectalkf.h
 * 0043	CAB		06/01/2001	Fixed typo in copyright info
 * 0044 MGS		01/02/2002	fixed tuning bug with values at the end of the range 
 * 0045	MGS		04/11/2002		ARM7 port
 */

#include "dectalkf.h"  
#include "ph_def.h"  
#ifndef MSDOS
#include "vtminst.h"	// NAL needed to control tuning
#endif
  
/***************************************************************************/
/* MVP: The following extern variables are now become elements of instance */
/* specific PH thread data structure DPH_T.                                */
/* extern  short   spdefb1off;                                             */
/* extern  short   spdeflaxprcnt;                                          */
/* extern  short   spdeftltoff;                                            */
/* extern  short   f0_dep_tilt;             How much f0 changes tilt.      */
/* extern  short   malfem;                  MALE or FEMALE.                */
/* extern  short   *p_locus;                Locus table.                   */
/* extern  short   *p_diph;                 Dipthong table.                */
/* extern  short   *p_tar;                  Targets.                       */
/* extern  short   *p_amp;                  Amplitudes.                    */
/* extern  short   arg1;                    For "mulsh" et al.             */
/* extern  short   arg2;                                                   */
/* extern  short   arg3;                                                   */
/* extern  short   curspdef[];              Holds current speaker def.     */
/* extern  FLAG    loadspdef;               Flag: need to load TMS320.     */
/* extern  short   *voidef[];               Speaker definition directory   */
/* extern  short   var_val[SPDEF];                                         */
/* extern  short   *voidef_8[];  Speaker definition directory   for 8 kHz. */
/* extern  short   assertiveness;           How much f0 falls at end.      */
/* extern  short   f0_lp_filter;            Cuttoff, f0 lowpass filter.    */
/* extern  short   size_hat_rise;           F0 hat rise, HZ times 10.      */
/* extern  short   scale_str_rise;          F0 scale factor, stress imp.   */
/* extern  short   f0basefall;                                             */
/* extern  short   f0minimum;                                              */
/* extern  short   f0scalefac;                                             */
/***************************************************************************/

/* extern  short   errors;  *//* Error masks.                 */

/* extern  short   last_voice; *//* MVP MI *//* reload voice */

extern short            *maleloc;	   /* Male tables.                 */
extern short            *maldip;
extern short            *maltar;
extern short            *malamp;

extern short            *femloc;	   /* Female tables.               */
extern short            *femdip;
extern short            *femtar;
extern short            *femamp;

#ifdef OS_PALM
#pragma pcrelconstdata off
#endif
extern CONSTSTRUCT struct rom_data_s us_rom_data_def;
#ifndef CASIO_SH3
extern CONSTSTRUCT struct rom_data_s uk_rom_data_def;
#endif
extern CONSTSTRUCT struct rom_data_s gr_rom_data_def;
extern CONSTSTRUCT struct rom_data_s sp_rom_data_def;
#ifndef CASIO_SH3
extern CONSTSTRUCT struct rom_data_s la_rom_data_def;
#endif
extern CONSTSTRUCT struct rom_data_s fr_rom_data_def;
extern CONSTSTRUCT struct rom_data_s it_rom_data_def;
extern CONSTSTRUCT struct rom_data_s jp_rom_data_def;
extern CONSTSTRUCT struct rom_data_s ch_rom_data_def;
extern CONSTSTRUCT struct rom_data_s hb_rom_data_def;
#ifdef OS_PALM
#pragma pcrelconstdata on
#endif

extern void changeSpeakerValues(LPTTS_HANDLE_T phTTS,TSpeakerDef *speakerDef, currentSpeaker, SPD_CHIP *);

/*
 *      Function Name: setparam()       
 *
 *  	Description: This function is called by
 * 					 "kltask" in ph_task.c to zap a parameter in the current
 *					 speaker definition. The "which" is the "SPD_"
 *					 symbol; the value is the value. Wild "which"
 *					 values are ignored. Wild values are pulled
 *					 into range, but log an error too.
 *
 *      Arguments: PDPH_T pDph_t,  Pointer to PH thread 
 *								   instance specific data structure
 *				   int which,
 *				   int value
 *
 *      Return Value: void
 *
 *      Comments:
 *
 */
 
void setparam (LPTTS_HANDLE_T phTTS, int which, int value)
{
	register LIMIT         *lp;
	extern   const LIMIT         limit[];


	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
#ifdef WIN32
	PVTM_T			pVtm_t	=	phTTS->pVTMThreadData;
#endif
	
	
	int voice = pKsd_t->last_voice;



	if (which < SPD_SEX || which > SPD_GP) /* changed upper limit from SPD_SR to SPD_GS, JAW
		                                    4/27/98 */
	{								   /* Check for junk. */
		return;
	}
	lp = (LIMIT *) &limit[which];

#ifdef WIN32
	if(pVtm_t->bDoTuning) /* Ignore autotuned vals when autotuning *///
	{

		if (value < lp->l_min)
		{								   /* Lower limit check.   */
			value = lp->l_min;
		}
		else if (value > lp->l_max)
		{								   /* Upper limit check.   */
			value = lp->l_max;
		}
		pDph_t->curspdef[which] = value;   /* Zap the value and    */

	}

	else
#endif
	{
		/* fixed tuning bug with values at the end of the range MGS */
#ifdef CASIO_SH3
		value += (pDph_t->tunedef_8[voice][which]);
#else
		value += (pDph_t->tunedef[voice][which]);
#endif //CASIO_SH3
		if (value < lp->l_min)
		{								   /* Lower limit check.   */
			value = lp->l_min;
		}
		else if (value > lp->l_max)
		{								   /* Upper limit check.   */
			value = lp->l_max;
		}
		pDph_t->curspdef[which] = value;   /* Zap the value and    */
	}

	pDph_t->loadspdef = TRUE;		   /* ask for reload.      */
}

/*
 *      Function Name: usevoice()       
 *
 *  	Description: Select a new voice. The
 * 					 "voice" is a voice number, like
 *					 "PERFECT_PAUL". No need to range check
 *					 the number, because there is no ":vo",
 *					 only ":n?", and you cannot get a bad
 *					 voice, unless there is a bad bug.
 *
 *      Arguments: LPTTS_HANDLE_T phTTS, 
 *				   int voice
 *
 *      Return Value: void
 *
 *      Comments:
 *
 */


void usevoice (LPTTS_HANDLE_T phTTS, int voice)
{
	short			*newspdef;
	short			*tunespdef;
	int            i;
	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PVTM_T pVtm_t = phTTS->pVTMThreadData;
#ifndef CASIO_SH3
	struct speaker_roms_s *sp_ptr=NULL;
#endif //CASIO_SH3
#ifdef PH_DEBUG
	//eab 11/16/98 BATS 804 
	extern   const LIMIT         limit[];
	LIMIT         *lp;
	short value;
#endif
	
#ifndef CASIO_SH3
	pDph_t->cur_speaker[PFUSA]=&us_rom_data_def;
	pDph_t->cur_speaker[PFUK]=&uk_rom_data_def;
	pDph_t->cur_speaker[PFGR]=&gr_rom_data_def;
	pDph_t->cur_speaker[PFSP]=&sp_rom_data_def;
	pDph_t->cur_speaker[PFLA]=&la_rom_data_def;
	pDph_t->cur_speaker[PFFR]=&fr_rom_data_def;
	pDph_t->cur_speaker[PFIT]=&it_rom_data_def;
	pDph_t->cur_speaker[PFJP]=&jp_rom_data_def;
	pDph_t->cur_speaker[PFCH]=&ch_rom_data_def;
	pDph_t->cur_speaker[PFHE]=&hb_rom_data_def;
	
	sp_ptr=pDph_t->speaker_rom_ptr;
	
	while (sp_ptr)
	{
		if (sp_ptr->speaker_numbers[voice])
		{
			pDph_t->cur_speaker[sp_ptr->language]=sp_ptr->rom_data;
		}
		sp_ptr=(struct speaker_roms_s *)sp_ptr->next;
	}
#endif //CASIO_SH3



#ifdef EPSON_ARM7
#else
#ifdef CASIO_SH3
	if(pKsd_t->lang_curr == LANG_english)
#endif
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
#ifndef CASIO_SH3
	pDph_t->tunedef_8[9] = (short*)us_ed_8_tune;
	pDph_t->tunedef_8[10] = (short*)us_matt_8_tune;
	pDph_t->tunedef_8[11] = (short*)us_sue_8_tune;
	pDph_t->tunedef_8[12] = (short*)us_mary_8_tune;
	pDph_t->tunedef_8[13] = (short*)us_lynn_8_tune;
	pDph_t->tunedef_8[14] = (short*)us_tom_8_tune;
	pDph_t->tunedef_8[15] = (short*)us_ivan_8_tune;
	pDph_t->tunedef_8[16] = (short*)us_charline_8_tune;
	pDph_t->tunedef_8[17] = (short*)us_jackie_8_tune;
#endif
	pDph_t->tunedef[0] = (short*)us_paul_tune;
	pDph_t->tunedef[1] = (short*)us_betty_tune;
	pDph_t->tunedef[2] = (short*)us_harry_tune;
	pDph_t->tunedef[3] = (short*)us_frank_tune;
	pDph_t->tunedef[4] = (short*)us_dennis_tune;
	pDph_t->tunedef[5] = (short*)us_kit_tune;
	pDph_t->tunedef[6] = (short*)us_ursula_tune;
	pDph_t->tunedef[7] = (short*)us_rita_tune;
	pDph_t->tunedef[8] = (short*)us_wendy_tune;
#ifndef CASIO_SH3
	pDph_t->tunedef[9] = (short*)us_ed_tune;
	pDph_t->tunedef[10] = (short*)us_matt_tune;
	pDph_t->tunedef[11] = (short*)us_sue_tune;
	pDph_t->tunedef[12] = (short*)us_mary_tune;
	pDph_t->tunedef[13] = (short*)us_lynn_tune;
	pDph_t->tunedef[14] = (short*)us_tom_tune;
	pDph_t->tunedef[15] = (short*)us_ivan_tune;
	pDph_t->tunedef[16] = (short*)us_charline_tune;
	pDph_t->tunedef[17] = (short*)us_jackie_tune;
#endif
	}
	

#if 0
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
		pDph_t->tunedef_8[9] =  (short*)jp_ed_8_tune;
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
#endif
#ifdef CASIO_SH3
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
#endif //CASIO_SH3
#endif
	
	
	changeSpeakerValues(phTTS, &pVtm_t->speakerDef, voice, (SPD_CHIP *)&(pVtm_t->parambuff[1]) );
	
	if (pKsd_t->uiSampleRate < 8763)
	{
#ifdef CASIO_SH3
		newspdef = pDph_t->voidef_8[voice];
#else
		newspdef = pDph_t->voidef[voice];
#endif //CASIO_SH3
		tunespdef = pDph_t->tunedef_8[voice];
	}
	else
	{
		newspdef = pDph_t->voidef[voice];
		tunespdef = pDph_t->tunedef[voice];
	}
	
	for (i = 0; i < SPDEF; ++i)
	{
		pDph_t->curspdef[i] = newspdef[i] + tunespdef[i];
		//eab 11/16/98 BATS 804 If ANY vlaues are out of allowable ranges scream LOUDLY 
#ifdef PH_DEBUG
		value=0;
		lp = &limit[i];
		if (pDph_t->curspdef[i] < lp->l_min)
		{	/* Lower limit check.   */
			value = lp->l_min;
		}
		else if (pDph_t->curspdef[i] > lp->l_max)
		{								   /* Upper limit check.   */
			value = lp->l_max;
		}
		
#endif
	}
	
#ifndef MSDOS
	/* MGS made curspdef contain the speaker number */
	pDph_t->curspdef[SPD_NM]=voice;
	//pDph_t->curspdef[SPD_SEX] = pDph_t->malfem;
#endif

	pDph_t->loadspdef = TRUE;		   /* Ask for reload.      */
	pKsd_t->last_voice = voice;
}


/*
 *      Function Name: saveval()        
 *
 *  	Description: Make "var_val" the same as
 * 					 the current speaker. Called from the
 * 					 main loop in "phmain" on a SAVE.
 *
 *      Arguments: PDPH_T pDph_t
 *
 *      Return Value: void
 *
 *      Comments:
 *
 */
void saveval (PDPH_T pDph_t)
{
	register int            i;

	for (i = 0; i < SPDEF; ++i)
		pDph_t->var_val[i] = pDph_t->curspdef[i];
}


/*
 *      Function Name: setspdef()        
 *
 *  	Description: This routine is called by
 * 					 "phclause" to recompute and reload a speaker
 * 					 definition. The magic numbers are pulled from the
 *					 "curspdef" array (where they are stored in a form that
 *					 is similar to the user format), converted to the bits
 *					 needed by the signal processor, and blasted over
 *					 to the TMS32010. 
 *
 *      Arguments: LPTTS_HANDLE_T phTTS
 *
 *      Return Value: void
 *
 *      Comments: This routine does not appear to do
 *				  all the stuff that "fcheck" and "convchip" did.
 *				  Is this intentional?
 *
 */

void setspdef (LPTTS_HANDLE_T phTTS)
{
	register S32            nlong;
	SPD_CHIP far            *spdef;

	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PVTM_T pVtm_t = phTTS->pVTMThreadData;
	SPEAKER_DEF_T *speaker_def_ptr;

#ifdef SEPARATE_PROCESSES
	spdef = (SPD_CHIP far *) FNX_MALLOC (SPDEF_PARS * sizeof (short));

#else
	spdef = (SPD_CHIP far *) spcget (SPC_type_speaker);
#endif

	pDph_t->malfem = pDph_t->curspdef[SPD_SEX];	/* Determine SEX   */
	spdef->sex = pDph_t->malfem;
	speaker_def_ptr=(SPEAKER_DEF_T *)pDph_t->curspdef;

	//eab initalize last_lang to a bad value so it won't compare first time through
	pDph_t->last_lang = 0;

	/* The following are not sent to chip, just used by higher level routines */
	pVtm_t->NOM_UNSTRESSED_VOWEL = pDph_t->curspdef[SPD_UNVOW];
	pVtm_t->NOM_VOIC_GLOT_AREA = pDph_t->curspdef[SPD_AGO];
	pVtm_t->NOM_VOICED_OBSTRUENT = pDph_t->curspdef[SPD_AGVO];
	if (pKsd_t->lang_curr == LANG_chinese)
			pVtm_t->NOM_VOICED_OBSTRUENT += 400;
	pVtm_t->NOM_Open_Glottis = pDph_t->curspdef[SPD_AGUO];
	pVtm_t->NOM_Area_Chink = pDph_t->curspdef[SPD_CHINK];
	pVtm_t->NOM_Open_Quo = pDph_t->curspdef[SPD_OQ];
	pVtm_t->glotal_pole = pDph_t->curspdef[SPD_GP];
	pVtm_t->glotal_zero = pDph_t->curspdef[SPD_GZ];
	pVtm_t->NOM_UNVOICED_SON = 1800;
	pDph_t->f0_dep_tilt = pDph_t->curspdef[SPD_FT];			/* FT -> FT */ /* FL in spanish */
	pDph_t->assertiveness = pDph_t->curspdef[SPD_AS] * 41;	/* AS in % -> AS */
/* BATS 711 MOve German to the new method for filter calculation*/
	pDph_t->f0_lp_filter = (1500 + 15 * pDph_t->curspdef[SPD_QU]);	/* QU in % -> lp cuttoff */
	pDph_t->size_hat_rise = pDph_t->curspdef[SPD_HR] * 10;	/* HR in Hz -> Hz*10    */
	pDph_t->scale_str_rise = pDph_t->curspdef[SPD_SR];		/* SR in Hz -> mult. sc. fac */
	// the -12 is a fudge factor to keep it similiar to 260
	pDph_t->f0minimum = (pDph_t->curspdef[SPD_AP]) * 10;		/* AP -> f0min          */
	pDph_t->f0scalefac = pDph_t->curspdef[SPD_PR] * 41;		/* PR -> f0scale        */
	pDph_t->f0basefall = pDph_t->curspdef[SPD_BF] * 10;		/* baseline fall        */
	pDph_t->spdeflaxprcnt = pDph_t->curspdef[SPD_LX] * 41;	/* degree of lax breathiness */

#ifdef HLSYN
	pVtm_t->Tiltm = (pDph_t->curspdef[SPD_SM] * 20) / 100;				// Baseline tilt of speaker
#else
	pDph_t->spdeftltoff = (pDph_t->curspdef[SPD_SM] * 25) / 100;		/* SM (%) -> dB tilt    */
#endif
	
	/* FNX_PRINTF("WA?br  %d \n",pDph_t->curspdef[SPD_BR]); */
	pDph_t->spdefb1off = (pDph_t->curspdef[SPD_BR] * pDph_t->curspdef[SPD_BR]) >> 1;
	pDph_t->spdefb1off += 4096;		   						/* BR -> B1-offset      */
	/* BR=55 -> scale B1 by 2.5 factor      */
	/* BR= 0 -> scale B1 by 1.0 factor      */

	/* 
	 * The following are all sent to the synthesizer chip 
	 */

	spdef->fnscale = (200 - pDph_t->curspdef[SPD_HS]) * 41;	/* HS -> FNscale        */
	pDph_t->fnscale = spdef->fnscale;
	if (pDph_t->curspdef[SPD_F4] == ZAPF)
	{
		spdef->r4cb = ZAPF;
	}
	else
	{
		nlong = pDph_t->curspdef[SPD_F4];
		nlong = nlong * spdef->fnscale;
		spdef->r4cb = (short)(nlong >> 12);	   		/* F4 -> F4*FNscale     */
	}

	spdef->r4cc = pDph_t->curspdef[SPD_B4];	/* B4 -> B4             */
	if (spdef->r4cb > 4950)
	{
		spdef->r4cb = ZAPF;			   		/* F4 too big, zap it   */
		spdef->r4cc = ZAPB;			   		/* and bw   			*/
	}

	if (pDph_t->curspdef[SPD_F5] == ZAPF)
	{
		spdef->r5cb = ZAPF;
	}
	else
	{
		nlong = pDph_t->curspdef[SPD_F5];
		nlong = nlong * spdef->fnscale;
		spdef->r5cb = nlong >> 12;	   		/* F5 -> F5*FNscale     */
	}

	/* 
	 *  B5 -> B5
	 */

	/*EAB- 6/25/99 This was a test for a new software volume control requested by Tom Kopec for
	a customer. Since the system is tuned "hot" the volume is at a max and these controls allow
	it to be reduced. It works by reducing the the gain of the final cascade resonator (different depending
	on what version of the vocal tract is used), and the two other noise source gains GH and GF. You simply need do 
	decrease these all by the same db amount and the results tract with good fidelity */



	spdef->r5cc = pDph_t->curspdef[SPD_B5];
	if (spdef->r5cb > (phTTS->pKernelShareData->uiSampleRate>>1))
	{
		spdef->r5cb = ZAPF;			   		/* F5 too big, zap it   */
		spdef->r5cc = ZAPB;			   		/* and bw   			*/
	}
	spdef->r4pb = pDph_t->curspdef[SPD_P4];	/* F7 -> F4p            */
	spdef->r5pb = pDph_t->curspdef[SPD_P5];	/* F8 -> F5p            */
	spdef->t0jit = pDph_t->curspdef[SPD_LA];
	//3/15/01 Changed to left shift rather than mult.  */
	spdef->r5ca = pDph_t->curspdef[SPD_G1];	/* G1 -> G1 in dB       */
	spdef->r4ca = pDph_t->curspdef[SPD_G2];	/* G2 -> G2 in dB       */
	spdef->r3ca = pDph_t->curspdef[SPD_G3];	/* G3 -> G3 in dB       */
#ifdef NEW_VOLUME
	//Assumes vocal tract with the second formant as the last resonatorr f5-f1-f4-f3-f2 ordering
	spdef->r2ca = pDph_t->curspdef[SPD_G4]-temp;	/* G4 -> G4 in dB       */
#else
	spdef->r2ca = pDph_t->curspdef[SPD_G4];	/* G4 -> G4 in dB       */
#endif

	spdef->r1ca = pDph_t->curspdef[SPD_LO];	/* LO -> LO in dB       */
	/* EAB 12/16/97 Comments incorrect - note comment in ph_vset 
	is not correct this code allows a range of approx 12.5% to 60%  
	for nopen1 as a percentage and not	0 to 100 */
#ifdef LOWCOMPUTE
	spdef->nopen1 = 5000 + (160 * (100 - pDph_t->curspdef[SPD_RI]));	/* RI -> K1  */
	spdef->nopen2 = pDph_t->curspdef[SPD_NF];/* NF -> K2     */
#else
	spdef->nopen1 = 5000 + (160 * (100 - pDph_t->curspdef[SPD_RI]));	/* RI -> K1  */
	spdef->nopen2 = pDph_t->curspdef[SPD_NF] * 4;/* NF -> K2     */
#endif
	spdef->aturb = pDph_t->curspdef[SPD_BR] ;	/* BR -> BR     */

#ifdef SW_VOLUME

/*EAB- 10/7/99 lockheed Martin functionality moved to new code base
	Since the system is tuned "hot" the volume is at a max and these controls allow
	it to be reduced. It works by reducing the the gain of the final cascade resonator (different depending
	on what version of the vocal tract is used), and the two other noise source gains GH and GF. You simply need do 
	decrease these all by the same db amount and the results tract with good fidelity */


/* tek 08aug99 
 * adjust the three final gains by the dB amount specified by the
 * user volume command
 */
   (*spdef).r1ca += KS.CurrentVolumeDB;         
   (*spdef).afgain += KS.CurrentVolumeDB;	
   (*spdef).apgain += KS.CurrentVolumeDB;
#endif /*SW_VOLUME*/
	spdef->rnpgain = pDph_t->curspdef[SPD_GN];	/* GN -> GN             */
#ifdef LOWCOMPUTE
	spdef->rnpgain = pDph_t->curspdef[SPD_GN];	/* GN -> GN             */
	spdef->azgain = pDph_t->curspdef[SPD_GV]+6;	/* GV -> GV             */
#else
	spdef->azgain = pDph_t->curspdef[SPD_GV];	/* GV -> GV             */
	spdef->rnpgain = pDph_t->curspdef[SPD_GN];	/* GN -> GN             */
#endif

		spdef->afgain = pDph_t->curspdef[SPD_GF];   /* GF -> GF */

	if (pKsd_t->lang_curr == LANG_japanese)
		spdef->apgain = pDph_t->curspdef[SPD_GH]-7;	/* GH -> GH */
	else
  	spdef->apgain = pDph_t->curspdef[SPD_GH];	/* GH -> GH */





#ifndef MSDOS
	spdef->osgain = pDph_t->curspdef[SPD_OS];	/* BH Added speaker to packet *//* GH -> GH  */
	spdef->speaker = pDph_t->curspdef[SPD_NM];	/* BH Added speaker to packet *//* GH -> GH  */
#endif

	spdef->HL_B1m=speaker_def_ptr->HL_B1m;
	spdef->HL_B2m=speaker_def_ptr->HL_B2m;
	spdef->HL_B3m=speaker_def_ptr->HL_B3m;
	spdef->HL_B4m=speaker_def_ptr->HL_B4m;
	spdef->HL_B5m=speaker_def_ptr->HL_B5m;
	spdef->HL_B2F=speaker_def_ptr->HL_B2F;
	spdef->HL_B3F=speaker_def_ptr->HL_B3F;
	spdef->HL_B4F=speaker_def_ptr->HL_B4F;
	spdef->HL_B5F=speaker_def_ptr->HL_B5F;
	spdef->HL_F5=speaker_def_ptr->HL_F5;
	spdef->HL_F6=speaker_def_ptr->HL_F6;
	spdef->HL_B6F=speaker_def_ptr->HL_B6F;
	spdef->stress_step=speaker_def_ptr->stress_step;
	spdef->unstress_pressure=speaker_def_ptr->unstress_pressure;
	spdef->stress_pressure=speaker_def_ptr->stress_pressure;
	spdef->nom_sub_pressure=speaker_def_ptr->nom_sub_pressure;
	spdef->nom_fricative_opening=speaker_def_ptr->nom_fricative_opening;
	spdef->nom_glot_stop_area=speaker_def_ptr->nom_glot_stop_area;
	spdef->vot_speed=speaker_def_ptr->vot_speed;
	spdef->endofphrase_spread=speaker_def_ptr->endofphrase_spread;
	spdef->endofphrase_spread_target=speaker_def_ptr->endofphrase_spread_target;
	spdef->HL_num_formants=speaker_def_ptr->HL_num_formants;
	spdef->HL_f1_hi_shift=speaker_def_ptr->HL_f1_hi_shift;
	spdef->HL_acd_f1_break=speaker_def_ptr->HL_acd_f1_break;
	spdef->Ka=speaker_def_ptr->Ka;
	spdef->f2_ref_scale=speaker_def_ptr->f2_ref_scale;
	spdef->f3_ref_scale=speaker_def_ptr->f3_ref_scale;
	spdef->diplo_step=speaker_def_ptr->diplo_step;
	spdef->endpoint_below_ap=speaker_def_ptr->endpoint_below_ap;
	spdef->endpoint_mult_stress=speaker_def_ptr->endpoint_mult_stress;
	spdef->tune_param_1=speaker_def_ptr->tune_param_1; //lift for a stress vowel
	spdef->tune_param_2=speaker_def_ptr->tune_param_2; //lift with a stressed vowel following a stop
	spdef->init_st_no_aspir=speaker_def_ptr->init_st_no_aspir;
	spdef->str_vow_before_final=speaker_def_ptr->str_vow_before_final;
	spdef->agm=speaker_def_ptr->agm; // Modal glottal area
	spdef->KTL=speaker_def_ptr->KTL;



#ifdef SEPARATE_PROCESSESdi
	FNX_FWRITE (&sd, sizeof (short), 1, stdout);
	FNX_FWRITE (spdef, sizeof (short), SPDEF_PARS, stdout);

	FNX_FFLUSH (stdout);
	FNX_FREE (spdef);
#else
// for(i=0;i<=31;i++) { FNX_PRINTF("spdef[%d]=%d \n",i,curspdef[i]); } 
#ifdef DEBUGVSET
	FNX_PRINTF ("r4cb is %d \n", spdef->r4cb);
	FNX_PRINTF ("r4cc is %d \n", spdef->r4cc);
	FNX_PRINTF ("r5cb is %d \n", spdef->r5cb);
	FNX_PRINTF ("r5cc is %d \n", spdef->r5cc);
	FNX_PRINTF ("r4pb  is %d \n", spdef->r4pb);
	FNX_PRINTF ("r5pb  is %d \n", spdef->r5pb);
	FNX_PRINTF ("t0jit is %d \n", spdef->t0jit);
	FNX_PRINTF ("r5ca  is %d \n", spdef->r5ca);
	FNX_PRINTF ("r4ca  is %d \n", spdef->r4ca);
	FNX_PRINTF ("r3ca  is %d \n", spdef->r3ca);
	FNX_PRINTF ("r2ca  is %d \n", spdef->r2ca);
	FNX_PRINTF ("r1ca  is %d \n", spdef->r1ca);
	FNX_PRINTF ("nopen1 is %d \n", spdef->nopen1);
	FNX_PRINTF ("nopen2 is %d \n", spdef->nopen2);
	FNX_PRINTF ("aturb is %d \n", spdef->aturb);
	FNX_PRINTF ("fnscale is %d \n", spdef->fnscale);
	FNX_PRINTF ("afgain is %d \n", spdef->afgain);
	FNX_PRINTF ("rnpgain is %d \n", spdef->rnpgain);
	FNX_PRINTF ("azgain is %d \n", spdef->azgain);
	FNX_PRINTF ("apgain is %d \n", spdef->apgain);
	FNX_PRINTF ("notused is %d \n", 0);	   /* hardwire */
#endif
#ifdef MSDOS
	spcwrite ((unsigned short _far *) spdef);	/* MVP : typecast was unsigned int _far * */
#else
	spcwrite (pKsd_t, (unsigned short _far *) spdef);	/* MVP : typecast was unsigned int _far * */
#endif

#endif
}
/***************************************end of ph_vset.c******************************/
