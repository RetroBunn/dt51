/* 
 ***********************************************************************
 *                           Copyright �
 *	  Copyright � 2002 Fonix Corporation. All rights reserved. 
 *    Copyright � 2000-2001 Force Computer, Inc., a Solectron company. All rights reserved.
 *    � Digital Equipment Corporation 1996, 1997,1998,  1999 All rights reserved.
 *
 *	  U.S. Government Rights: Consistent with FAR 12.211 and 12.212, 
 *    Commercial Computer Software, Computer Software Documentation, 
 *    and Technical Data for Commercial Items are licensed to the U.S. 
 *    Government under vendor's standard commercial license.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Fonix Corporation and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Fonix or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:    ph_draw.c
 *    Author:
 *    Creation Date:
 *
 *    Functionality:
 * 	  Realize each 6.4 ms time frame as a set of 16 control parameters
 *    (plus the fundamental period T0, which is set by PHDRAWT0.C)
 *    1. Set target values for this time frame.
 *    2. Add diphthongization increment if apropriate
 *    3. Smooth tran at boundary with previous segment.
 *    4. Smooth tran at boundary with next segment.
 *    5. Execute exception rules: e.g. set init part of phone to const
 *
 * 	  Ordering of control parameters in param[] structured array:
 *    F0,F1,F2,F3,FZ,B1,B2,B3,AV,AP,A2,A3,A4,A5,A6,AB,TILT
 * 	  Note that this isn't cast in concrete anymore, because of the
 * 	  "OUT_" stuff.
 ***********************************************************************
 *    Revision History:
 *
 * Rev  Who     Date            Description
 * ---  -----   -----------     -------------------------------------------- 
 * 0001 DK 		08/03/1984	    Initial creation
 * 0002 DK		08/12/1984	    Add vowel-vowel coartic across conson
 * 0003 DGC		12/27/1984	    Modified for the 80186.
 * 0004 DK		01/17/1985      Reverse tilt dependence on f0, initialize *outp
 * 0005 DK 		01/29/1985	    Reduce AV during glottal stop
 * 0006 DK		02/19/1985	    Tilt calc now standard, move spdef Tilt offset to chip
 * 0007 DK 		05/06/1985	    Add code to make breathy offset if breathysw == 1
 * 0008 DK		05/28/1985	    Make breathy offset code spdef via LX -> spdeflaxprcnt
 * 0009 DK		07/12/1985	    Clean up f0_dep_tlt code
 * 0010 DK		07/16/1985	    Use spdef offset here instead of SPC
 * 0011 DK		07/24/1985	    Rename chip stuff, make outpar structure into array
 * 0012 DK 		07/29/1985	    Breathy voices have wider first formant bandwidth
 * 0013 EAB		03/03/1996	    Modified the way an adjust was added to compensate
 *                      		for tilt, the old METHOD SIMPLY WAS NOT DOING ENOUGH.
 * 0014 CJL		03/18/1996	    Removing volume/tilt change; causes English overs.
 * 0015 MGS 	03/25/1996	    Merged WIN 95 code with 42c
 * 0007 MM		04/02/1985	    68000
 * 0008 MM		07/19/1985	    Added trill modulator (from German DECtalk)
 * 0009 MM		04/10/1986	    Allow Tilt to be specified by special rules.
 * 0010 MM		04/23/1986	    Changed [r] timing per suggestion from Dr. Quilis.
 * 0011 DF		06/03/1986	    DT3 updates: replace outpar by parstochip
 * 0013 BNK		08/06/1986	    Add german uvular R
 * 0014 BNK		06/20/1986	    Treatment of german affricates and plosives
 * 0015 CJL		03/30/1995	    File was phdraw.c. Is now gphdraw.c. Changed
 *                              phdefs.h->gphdefs.h
 * 0016 EAB 	03/03/1996		Modified the way an adjust was added to compensate for tilt, 
 *                    			the old METHOD SIMPLY WAS NOT DOING ENOUGH.
 * 0017 EAB		04/07/1996		Had to reduce effect and added check so that we don't ever set
 *                      		anything negative
 * 0016	MGS		06/03/1996 		Merged spanish with english		
 * 0017 MGS		06/06/1996 		hanged file name from phdraw.c to ph_draw.c
 * 0018	MGS		06/17/1996		Merged German with english/spanish
 * 0019 SIK		07/09/1996  	Cleaning up and maintenance
 * 0020 EDB 	12/10/1996		Many code change, also include debug window.
 * 0021 EDB		01/10/1997		Add some Spanish code and debug code.
 * 0022 GL		01/16/1997		fix the bug to correctly separate the code for
 *								German and Spanish in "compensate the loudness decrease..." code
 * 0023 EAB		02/14/1997		Improve distinction of trilled r by adding a voicing component to rr
 * 0024 GL		03/05/1997		Move r_modulation() from l_gr_dr1.c to here.
 * 0024 GL		03/05/1997		Move r_modulation() from l_gr_dr1.c to here.
 * 0024	GL		04/21/1997		BATS#360  remove spaces before "#define" or "#if" 
 * 0025 NCS     07/29/1997      Merged in OCTEL changes
 * 0026 EAB		10/12/1997		Removed old garbage that was ifdefed out
 * 0027 MGS     10/14/1997      BATS #470 Fixed, Reset/Crash
 * 0028 EAB/CJL 11/07/1997      Add Special Swap development code.
 * 0028 EAB		11/18/1997		Rmove double burst for UK English
 * 0029 EAB		05/11/1998		Added new VTM control parameters enabled in dectalkf.h with NEW_VTM
 * 0030 EAB     03/20/1998		Found that the using pointer nphone instead of np_drawto caused some
 *								lack of synchronization of several frames at times problem really 
								surfaced with control of German trills.c
 * 0031 EAB		04/29/1998		Many changes for German plus new intnation parameter as well as 
								new handle for R-mod for better debug and tune r_mod
 * 0032 eab		05/27/1998		bats 690 lateral at end of phrase
 * 0033 EAB		07/13/1998		BATS 711 Especially the tilt stuff I'm not sure backward compatibilty
								The tilt stuff will forever
 * 0034 EAB 	07/20/1998		Continued work on Spanish with Juan 
 * 0035 EAB		09/24/1998		Increased the glotal speed of nasal's per request from ginger
 * 0036 EAB		09/29/1998 		Correct typo and raise elvelar level slightly
 * 0037 eab 	10/13/1998 		Tuned Spanish and improved debug code
 * 0038 EAB 	10/15/1998 		Modified out_gs for Spanish nasals
 * 0039	GL		11/20/1998		BATS#828 use PH_DEBUG to replace _DEBUG
 * 0040	mfg		01/08/1999		WINprint not supported under Windows CE #ifdef out 
 * 0042 EAB		1/26/99 EAB     0014 17-Sep-86 DK	Add code to control open quotient
             0015 19-Mar-87 DK	Female voice AV down and OQ up at low f0
								Also added in more code for Evan Ballaban ouput of VTM parameers
 * 0043 EAB 	02/23/1999 		updated copright and gov reg notice, added comment, and improved swapdata
 *
 * 0044	MGS		04/13/2000		Changes for integrated phoneme set 
 * 0045 NAL		04/14/2000		Fixed extern phone_feature( pDph_t,] to extern *featb to match ph_rom.c files
 * 0046 NAL		05/24/2000		Removed extra }
 * 0047 EAB		05/24/2000		Fixed SPANUSH->SPANISH
 * 0048 EAB		07/28/2000		Found that pointer to allophone array is better as nphone
 * 0049 EAB		08/16/2000		Added first universal phon rule for lateral Actrulaau just L
								volumne reduction-can't be done by normal ramping because it would be too slow
 * 0050	CAB		10/18/2000		Fixed copyright info and formatted comment section. 
 * 0051 CAB		01/16/2001		Merged Michel Divay changes for French
 * 0052 CAB		01/23/2001		Fixed dangling if statement.
 * 0053 CAB		01/26/2001		Removed extra if (temptilt < 0) temptilt = 0; from code
 * 0054 EAB		3/13/2001		Add allophonic variant of R phoneme where it becomes less voiced and aspirated if followed
 *								by an unvoiced...
 * 0055 EAB		02/28/2001		fix burst for german ts phonmeme
 * 0056 MGS		05/18/2001		Fix errant winprint call
 * 0057	eab 	7/10/2001		Improvements 7/10/01 tuning hlsyn
 * 0058 EAB 					refinements for german 7/13/01 primarily with the aspiration and anticipated frication in short vowels
 * 0059 EAB 					Refinements to German vowel rules especially dealing with anticipated events occurring within the vowel
 * 0060 MGS		03/21/2002		Single threaded ph
 * 0061 MGS		04/17/2002		ARM7 port
 * 0062	CAB		07/11/2002		Fixed #ifdef
 * 0063	CAB		09/18/2002		Removed redefine variable
*/

#include "dectalkf.h"
#include "ph_def.h"  
#include "vtminst.h"

/* This is defined to add the code to be used to perform a regression test. */
//#define PH_REGRESSION_TEST

#ifdef PH_SWAPDATA   
FILE *PHSwapIn = NULL;
FILE *PHSwapOut = NULL;
#endif

#undef _inline
#undef __inline

extern short *featb;
#define phone_feature(a,b) (all_featb[(b)>>8][(b)&0x00ff])
#define place(b) all_place[(b)>>8][(b)&0xFF]

//extern __inline short phone_feature(PDPH_T pDph_t, int phone);	   /* Phonetic features */
//extern __inline short place(int);

const short lplos_build_time=7;
const short bplos_build_time=7;
//short tmp;

/***************************************************************************/
/* MVP : The following variables are never used ,commented out             */
/* extern short dipspec[40];     Contains dipthong specs                   */
/* extern short durfon;          Duration of current phone, in frames      */
/***************************************************************************/

/***************************************************************************/
/* MVP : The following extern variables are now become elements of instance*/
/* specific PH thread data structure DPH_T.                                */
/* Input arrays (set by call to PHSETTAR.C whenever time for new phone)    */
/* extern PARAMETER param[];       Struc of input vars for each par        */
/* extern short fvvtran,bvvtran,tvvbacktr,dfvvtran,dbvvtran;  F2 V-V       */
/* extern short breathysw;          Set to one if breathy offset           */
/* extern short spdefb1off;         Scale factor for B1 if breathy         */
/* extern short spdeflaxprcnt;      Set to 0 - 4096, percent breathy       */
/* For computation of TILT only                                            */
/* extern short    spdeftltoff;     Tilt offset spdef constant             */
/* extern short    f0_dep_tilt;     Sp def %-f0-effect                     */
/* extern short    f0;              Unscaled current f0                    */
/* Output arrays: All parameter values stored here                         */
/* extern short parstochip[];    Array incl state and par[TILT]            */
/* extern short tcum;       Time relative to phoneme begin, in frames      */
/* extern short avglstop;   Used to reduce AV during glstop                */
/***************************************************************************/

/* Variables initialized elsewhere   */

#if defined PH_DEBUG || defined PH_SWAPDATA
int ii;			   /* for regression testing eab */
#endif                                           

#ifndef NO_INCLUDED_C_FILES
#include "ph_draw1.c" /* pick up the language dependent code */
#endif
#if defined (WIN32) && defined (PRINTFDEBUG)
#include "dbgwins.h"
#endif
void r_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp);
void rit_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp);
void rs_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp);
void gr_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp);
void h_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp);
//static void add_feature (PDPH_T pDph_t
void Phrase_intial_sil_start(LPTTS_HANDLE_T phTTS);
void Phrase_final_silence(LPTTS_HANDLE_T phTTS);
void	Set_pressure(LPTTS_HANDLE_T phTTS);
void Do_ue_dc(LPTTS_HANDLE_T phTTS);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* D R A W P A R S                                  					 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*
 *      Function Name: phdraw()      
 *
 *  	Description: Smooths curves between points.
 *
 *      Arguments: PDPH_T pDph_t
 *
 *      Return Value: 
 *
 *      Comments:
 *
 */

	
	const short nasalization[13]={0, 30, 60, 100, 130, 160, 190,320,450,570,675,780,885};
	//const short nasalization[13]={0, 150, 200, 300, 400, 500, 600,700,800,800,805,8100,885};
	const short velar_f1[8] = { 180,220,260,280,320,390,400,410};
	const short dcval[11] = { 0, 30,40,80,90, 95,96, 100, 110,105,120};

	const  short ueval[11] = { 0,40,60,80,90,100,115,120,125,125,130};


void phdraw (LPTTS_HANDLE_T phTTS)
{

	PVTM_T pVtm_t = phTTS->pVTMThreadData;
	PKSD_T         pKsd_t = phTTS->pKernelShareData;
//	SPD_CHIP	  far    *spdef;
	PARAMETER     *np;		   /* Pointer to control values    */
	short         *parp;	   /* Pointer to output buffer     */
		short          value;                         
	short coarticulation =4;
	short tmp;
		short vot_time;

	short		area_rel[18] =
		{ 0,300, 600,800, 900,
	1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000 };
	short		farea_rel[20] =
	{  500, 300,100,100, 100,
	100,100,100,100,100,100,100,100,
	100,100,100,100,100, 100, 100};


#ifdef PH_SWAPDATA
	char outbuf[20];
	short j;
#endif

	short			pholas = GEN_SIL;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;

	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;

		
#ifndef MSDOS
#ifndef ARM7
	/* MGS 10/14/1997 BATS #470 Fixed crashed due to reset */
	volatile BOOL		*bInReset;
#endif
#endif
	
	/* register short del_av; */
	/* static short drawinitsw; *//* MVP made instance specific added to PHSETTAR struct */
	/* static short breathyah,breathytilt; *//* Used to make breathyness  */
	short                   temptilt;
//	EAB		7/13/98			BATS 711 removed vadjust
	

#ifndef MSDOS
#ifndef ARM7
	/* MGS 10/14/1997 BATS #470 Fixed crashed due to reset */
	bInReset =&(pDph_t->phTTS->bInReset);
#endif
#endif
		
	
		
/* Loop across all parameters but T0. I changed this so that it    */
/* pulls the value of "parp" from the "outp" field of the struct.  */
/* This lets these loops be written nicely, but makes it possible  */
/* to reorder things in the output.                                */

// the ARM compiler desn't like this in the array definition MGS

area_rel[0]=pVtm_t->NOM_Fricative_Opening=100;

#ifndef MSDOS
				if (pDphsettar->drawinitsw == 0)
				{
					pDphsettar->drawinitsw = 1;
					pDph_t->param[F0].outp = &(pDph_t->parstochip[OUT_T0]);
					pDph_t->param[F1].outp = &(pDph_t->parstochip[OUT_F1]);
					pDph_t->param[F2].outp = &(pDph_t->parstochip[OUT_F2]);
					pDph_t->param[F3].outp = &(pDph_t->parstochip[OUT_F3]);
					pDph_t->param[FZ].outp = &(pDph_t->parstochip[OUT_FZ]);
					pDph_t->param[B1].outp = &(pDph_t->parstochip[OUT_B1]);
					pDph_t->param[B2].outp = &(pDph_t->parstochip[OUT_B2]);
					pDph_t->param[B3].outp = &(pDph_t->parstochip[OUT_B3]);
					pDph_t->param[AV].outp = &(pDph_t->parstochip[OUT_AV]);
					pDph_t->param[AP].outp = &(pDph_t->parstochip[OUT_AP]);
					pDph_t->param[A2].outp = &(pDph_t->parstochip[OUT_A2]);
					pDph_t->param[A3].outp = &(pDph_t->parstochip[OUT_A3]);
					pDph_t->param[A4].outp = &(pDph_t->parstochip[OUT_A4]);
					pDph_t->param[A5].outp = &(pDph_t->parstochip[OUT_A5]);
					pDph_t->param[A6].outp = &(pDph_t->parstochip[OUT_A6]);
					pDph_t->param[AB].outp = &(pDph_t->parstochip[OUT_AB]);
					pDph_t->param[TILT].outp = &(pDph_t->parstochip[OUT_TLT]);
					pDph_t->param[AREAG].outp = &(pDph_t->parstochip[OUT_AG]);
					pDph_t->param[AREAL].outp = &(pDph_t->parstochip[OUT_AL]);
					pDph_t->param[AREAN].outp = &(pDph_t->parstochip[OUT_AN]);
					pDph_t->param[AREAB].outp = &(pDph_t->parstochip[OUT_ABLADE]);
					pDph_t->param[PRESS].outp = &(pDph_t->parstochip[OUT_PS]);
					pDph_t->param[TONGUEBODY].outp = &(pDph_t->parstochip[OUT_ATB]);
					pDph_t->param[CHINK].outp = &(pDph_t->parstochip[OUT_CNK]);
					pDph_t->param[UEL].outp = &(pDph_t->parstochip[OUT_UE]);
					pDph_t->param[DC].outp = &(pDph_t->parstochip[OUT_DC]);
					pDph_t->param[BRST].outp = &(pDph_t->parstochip[OUT_BRST]);
					pDph_t->param[BR].outp = &(pDph_t->parstochip[OUT_BR]);

					
				}
#endif

	
	if (pDph_t->nphone>=1)
	{
		pholas = pDph_t->allophons[ pDph_t->nphone - 1];
	}
	else
		pholas=0;

 coarticulation = 0;

	if(pDph_t->nphone != pDph_t->nphonelast)
	{
#ifdef PH_DEBUG

		if(DT_DBG(PH_DBG,0x080))
		{
			printf(" at phone %s \n", phprint( pDph_t->allophons[pDph_t->nphone] ) );
			
		}
		
#endif
		pDph_t->phonestep =0;
	pDph_t->modulcount =0;
	}
	else
	{
		pDph_t->phonestep ++;
		
	}	
	for (np = &PF1; np <= &PB3; ++np)
	{
			
		parp = np->outp;			   /* Where it goes.       */

		/* If diphthongized seg, see if new straight line called for.   */
#ifndef MSDOS
#ifdef ARM7
		if (phTTS->pKernelShareData->halting) return;
#else
		if (phTTS->pKernelShareData->halting) return;
		/* MGS 10/14/1997 BATS #470 Fixed crashed due to reset */
		if (*bInReset)	return;
#endif
#endif


	    /* crashing if adjust != 0 eab 11/96 need to fix correctly eab */
		if (pDph_t->tcum > np->durlin && pDph_t->tcum > 0 && np->durlin >=0){
			if (np->ndip == 0) return;  // boiler plate for when the reset happens at the wrong time
			np->durlin = *np->ndip++;
			np->deldip = *np->ndip++;
			np->tarcur += (np->dipcum DIV_BY8);
			np->dipcum = 0;
			// printf("deldipindraw %d %d\n",np->deldip,np->ndip); 
				
		}

		/* Set target value and smooth forward. The delta-dipth and the */
		/* delta-trans are *8 to avoid roundoff propogation.            */
		np->dipcum += np->deldip;
		value = np->dipcum + np->ftran;

		/* Then shrink transition magnitude by appropriate increment.   */
		if (np->ftran != 0)
			np->ftran -= np->dftran;

		/* Smooth backwards. Delta-transition is *8 to avoid roundoff   */
		/* propogation. Transition magnitude is then changed by the     */
		/* appropriate increment.                                       */
		if (pDph_t->tcum >= np->tbacktr)
		{
			value += np->btran;
			np->btran += np->dbtran;
		}

		/* Vowel-vowel coartic across a consonant, for F2 only.         */
		if (np == &PF2)
		{
			value += pDph_t->fvvtran;
			if (pDph_t->fvvtran != 0)
				pDph_t->fvvtran -= pDph_t->dfvvtran;
			if (pDph_t->tcum >= pDph_t->tvvbacktr)
			{
				value += pDph_t->bvvtran;
				pDph_t->bvvtran += pDph_t->dbvvtran;
			}
		}

		/* 
		 * Store the computed paramter into the right spot in the block 
		 * of data about to be sent to the TMS320.                      
		 */
		*parp = (value DIV_BY8) + np->tarcur;
	

			/* Special rules (I.e. BW windening for aspir)                  */
			if (np->tspesh > 0)
			{
				if (pDph_t->tcum < np->tspesh)
				{
					if(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL)
		{
					*parp += 50;
					if (np == &PB1)
						*parp += 75;
					}else
					*parp = np->pspesh;
				}
			}
		

#ifndef HLSYN //done int hl		
			/* Breathy voices have wider first formant bandwidth */
			else if (np == &PB1)
			{
				*parp = frac4mul (*parp, pDph_t->spdefb1off);
			}
#endif
	}

	/* 
	 * End of loop for F[1,2,3], FZ, B[1,2,3].                         
	 * Begin loop for amplitude parameters AV, AP, A[2,3,4,5,6], AB.   
 	 */

	for (; np <= &PTILT; np++)
	{
	
		parp = np->outp;			   /* Where it goes.       */

		/* Smooth forward, use shift to avoid roundoff propogation.     */
		value = np->tarcur + (np->ftran DIV_BY8);
		/* Then shrink transition magnitude by appropriate increment.   */
		if (np->ftran != 0)
			np->ftran -= np->dftran;

		/* 
		 * Smooth backward, using shift to avoid roundoff propogation.  
		 * Modify transition magnitude by the appropriate increment.   
		 */
		if (pDph_t->tcum >= np->tbacktr)
		{
			*parp = value + (np->btran DIV_BY8);
			np->btran += np->dbtran;
		}
		else
		{
			*parp = value;
		}

		/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
		/* Special rules (I.e. vot, aspir, and burst dur for plos).     */
	
		 if (np->tspesh > 0)
		{
			if (pDph_t->tcum < np->tspesh)
			{
				
				*parp = np->pspesh;
			}
			else
			{
				

							/* Double burst for /k,g,ch,jh/                         */
							/*per caroline double burst is wrong for UK*/
#if ( !(defined HLSYN) )

				
				if ((np > &PAP)
					&& (pDph_t->tcum == (np->tspesh + 1))
					&& (*parp >= 10))
				{

					if (pDph_t->allophons[ pDph_t->nphone] == GRP_KSX)
					{
						*parp = 0;
					}
					else
					*parp -= 10;
				}

#endif//hlsyn
			}
		}
		if	(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL
			|| pDph_t->allofeats[pDph_t->nphone+ 1 ] & FDUMMY_VOWEL )
		{
				if (np == &PA2)
					{
						*parp -= 10;
						if(*parp <0)
							*parp = 0;
					}
					else if (np == &PA3)
					{
						*parp -= 10;
						if(*parp <0)
							*parp = 0;
					}
					else if (np == &PA4)
					{
						*parp -= 10;
						if(*parp <0)
							*parp = 0;
					}
					else if (np == &PA5)
					{
						*parp -= 10;
						if(*parp <0)
							*parp = 0;
					}
					else if (np == &PA6)
					{
						*parp -= 10;
						if(*parp <0)
							*parp = 0;
					}
					else if (np == &PAB)
					{
						*parp -= 10;
						if(*parp <0)
							*parp = 0;
					}

			if(np == &PAP ) 
			{
				*parp -= pDph_t->phonestep<<1;
				if(*parp < 0)
					*parp =0;
			}
			else
			
				if(np == &PAV)
			{
				*parp -= pDph_t->phonestep<<2;
				if(*parp < 0)
					*parp =0;
			}
				
		}
		else if(np == &PAV)
		{
				vot_time = 0;
			if(np->tspesh )
					{
					//do this only for syl to set vot after plos
					//need to delay glotal spread by vot time
					vot_time = np->tspesh;
if(pKsd_t->lang_curr == LANG_italian)
{
					if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSON1)
				{

						//special case - rapid onset close like crazy-kinda breathy is still breathier
						// note actual vot 0f 6.3 not possible as I use this for
						//vot of  esseentially 0
						if(np->tspesh == 1)
						{
							pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA;
							if(pDph_t->area_g > 1000)
								pDph_t->area_g = 1000;
							pDph_t->agspeed =pVtm_t->VOT_speed;
						}
						else if(np->tspesh <= 5)
						{
							pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA;
							if(pDph_t->area_g > 1300)
								pDph_t->agspeed = 1;
							else
								pDph_t->agspeed =pVtm_t->VOT_speed;
						}
						else if(  pDph_t->tcum == 3
						&& np->tspesh >5 )
					{
						//after release start a slow drop
						if(pVtm_t->VOT_speed)
						{
								if( pDph_t->target_ag > pVtm_t->NOM_VOIC_GLOT_AREA+700)
									pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+700;
						pDph_t->agspeed =3;
						}
					}
					
						else if(  pDph_t->tcum == np->tspesh-5)
					{
						if(pVtm_t->VOT_speed)
						{
					
						pDph_t->agspeed = pVtm_t->VOT_speed;
						}
							if( pDph_t->target_ag > pVtm_t->NOM_VOIC_GLOT_AREA+600)
								pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+600;

					}
					
					
					else if(  pDph_t->tcum == np->tspesh-2)
							
					{
						if( pDph_t->target_ag > pVtm_t->NOM_VOIC_GLOT_AREA+380)
						pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+380;
						pDph_t->agspeed =1;
						if(pVtm_t->VOT_speed > 2
							&& np->tspesh >= 5)
						{
							
						pDph_t->agspeed = 2;
						}
						

					}
					
					if(  pDph_t->tcum == np->tspesh)
					{
						pDph_t->lastvot= np->tspesh;
						pDph_t->target_ag= pVtm_t->NOM_VOIC_GLOT_AREA;

						//except if in sil
						if(pDph_t->allophons[ pDph_t->nphone] != GEN_SIL)
						{
							pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA;
#ifdef PH_DEBUG
							if(DT_DBG(PH_DBG,0x080))
							{
								printf(" vot sets glotal closing %d \n",np->tspesh);
								
							}
#endif
						}
						
					}
					

				}
			
			}
			else
				pDph_t->lastvot=0;
		}
			
			
			
	}
	}


	/* * * * * * * * * * * * * * */
	/* Reduce AV if glstop:   	 */
	/* * * * * * * * * * * * * * */
	//printf( " %d \n",pDph_t->parstochip[OUT_AP]);
	if (pDph_t->parstochip[OUT_AV] > 6)
	{
		pDph_t->parstochip[OUT_AV] -= pDph_t->avglstop;
	}


	

	parp = &(pDph_t->parstochip[OUT_TLT]);	/* Where it goes.       */
		

	*parp += (pDph_t->spdeftltoff - 6); /*from fphdraw.c*/

	

	//EAB		7/13/98			BATS 711 

	*parp += (pDph_t->spdeftltoff - 3); /*from fphdraw.c*/


	
	/* Breathy offset special code */
//	if (pDph_t->breathysw == 1)
//	{	/* Set in ph_setar.c */
	//	if (pDph_t->parstochip[OUT_AV] > 40)
	//	{	/* Do only if AV on  */
			/* Add aspiration to voicing */
	//		if (pDphsettar->breathyah < 27)
	//		{
	//			pDphsettar->breathyah += 2;		/* asp increase 32 db/100 ms */
	//		}


//			value = frac4mul (pDph_t->spdeflaxprcnt, (pDphsettar->breathyah ));

	



				
			/* Tilt down voicing spectrum */
//			if (pDphsettar->breathytilt < 16)
//			{
//				pDphsettar->breathytilt += 1;	/* tilt decrease 16 dB/100 ms */
//			}
//			*parp += frac4mul (pDph_t->spdeflaxprcnt, pDphsettar->breathytilt);
#ifdef DEBUGPHT
#if defined (WIN32) && defined (PRINTFDEBUG)
				WINprintf("til2=%d \n",*parp);
#endif
#endif	// DEBUGPHT
//		}
//	}
//	else
	{
		/* Zero or initialize all breathyness variables */
		pDphsettar->breathyah = 0;
		pDphsettar->breathytilt = 0;
	}

	/* Source tilt can't be more than 31 dB */
	if (*parp > 31)
	{
		*parp = 31;
	}
	
	if (*parp < 0)
	{
		*parp = 0;
	}

	



	/* add in formant scaling */
//Note scaling breaks f1==180 stuff
 if( pDph_t->parstochip[OUT_F1] > 250)
	pDph_t->parstochip[OUT_F1] = frac4mul( pDph_t->parstochip[OUT_F1], pDph_t->fnscale ) + ((4096 - (S32)pDph_t->fnscale ) >> 4);
  pDph_t->parstochip[OUT_F2] = frac4mul( pDph_t->parstochip[OUT_F2], pDph_t->fnscale ) + ((4096 - (S32)pDph_t->fnscale ) >> 3);
  pDph_t->parstochip[OUT_F3] = frac4mul( pDph_t->parstochip[OUT_F3], pDph_t->fnscale );
			

	pDph_t->parstochip[OUT_SEX] = pDph_t->malfem;


if(pKsd_t->lang_curr == LANG_italian)
{
	for (; np <= &PTONGUEBODY; np++)
	{
		
		if(np == &PAREAL)
		{
			if(np->tspesh)
			{
				if(pDph_t->tcum >= np->tspesh )
				{
					pDph_t->in_brelease=0;
					pDph_t->in_lclosure=0;
					
						if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FCONSON )
						{	
							if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FPLOSV)
							{
								
								if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FPLOSV))
								{
									//plos not a polosive release it
										// not honmorganic
									if(!(place(pDph_t->allophons[pDph_t->nphone+1]) & FLABIAL))
									{
									
									pDph_t->in_lrelease=1;
									pDph_t->target_l= pVtm_t->NOM_Fricative_Opening;
									}
								}
							}
						
							}
						else
						if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FNASAL  ))
							pDph_t->in_lrelease=1;
					
				}
				else if ( pDph_t->tcum  >= (np->tspesh-(bplos_build_time) ) 
					&& ( phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FBURST))
				{
					pDph_t->in_lclosure=1;
					pDph_t->in_lrelease=0;
					pDph_t->in_brelease=0; 
				}
				
			}//pareal
			
		}
		
		if(np == &PAREAB)
		{
			if(np->tspesh)
			{
						
				
				if (pDph_t->tcum >= np->tspesh )
				{

					pDph_t->in_lrelease=0;
					pDph_t->in_bclosure=0;
				
						if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FCONSON )
						{	
							if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FPLOSV)
							{
								
								if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FSTOP))
								{
									//plos-not a polosive release it
								
									if(!(place(pDph_t->allophons[pDph_t->nphone+1]) & BLADEAFFECTED)
										|| (pKsd_t->lang_curr == LANG_italian))
									{
									
									pDph_t->in_brelease=1;
									pDph_t->bstep = -1;
									pDph_t->target_b = pVtm_t->NOM_Fricative_Opening;
									}
								}
						

							}
							else
								//affricate- release it
							{
									pDph_t->in_brelease=1;
									pDph_t->bstep = -1;
									pDph_t->target_b = pVtm_t->NOM_Fricative_Opening;
							}
					
						}
						else
						if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FNASAL  ))
							pDph_t->in_brelease=1;
				}
				else if (pDph_t->tcum  >= (np->tspesh-  (bplos_build_time+1)) 
					&& (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FBURST))
				{
					pDph_t->in_bclosure=1;
					pDph_t->in_brelease=0;
					pDph_t->in_lrelease=0; 
				}
				//	else
				//	pDph_t->in_bfric =0;
			}//pareab
		}
		if(np == &PTONGUEBODY)
		{

			if(np->tspesh)
			{
				// bts10183 coarticulate a velar plos follwoed by a stop
				if (pDph_t->tcum >=(np->tspesh) 
					&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FSTOP))
				{
					pDph_t->in_tbclosure=0;
				
					pDph_t->in_lrelease=0;
					//tstep ==1 keeps the release in fricatiom not allowing the 
					//potentially slow release
					pDph_t->target_tb =100;
					pDph_t->in_tbrelease=1;
				}
			
			}//ptonguebody


		}
		
		
	}
	
	

	
	if(pDph_t->nphone == 0) //in intial silence anticipate intial parameters
	{	
		Phrase_intial_sil_start(phTTS);
#ifdef HLSYN
		Do_ue_dc(phTTS);
#endif
	}
	else if(pDph_t->allophons[pDph_t->nphone] == GEN_SIL)
				{
		Phrase_final_silence(phTTS);
			}		
			
				
	else // in a regular phoneme
				{
#ifdef HLSYN		
		Do_ue_dc(phTTS);		
				
		Set_pressure(phTTS);
#endif

		
		if(pDph_t->nphone != pDph_t->nphonelast)
		{			
			
			
		
			
			//********If previous phone is........
			if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FPLOSV))
			{
				
				//do at start of phone but not later i.e. once per phone only
				//previous not a plosive so kill the release
				pDph_t->in_lrelease=0;
				pDph_t->in_brelease=0;
				pDph_t->in_tbrelease=0;
				pDph_t->bstep=0;
				
#ifdef DEBUGIOT
				if(DT_DBG(PH_DBG,0x080))
				{
					printf("previous phone not a plos so we're not in a release cyle\n");
				}
#endif
				
			}
			
			
			/// I this phone is a .....
			
			if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST)
			{
				
			
				
				
				if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & 004000)
				{
					
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" Has burst so shut something...");
					}
#endif
					
					if((place(pDph_t->allophons[pDph_t->nphone])) & FLABIAL )
					{	
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf("the lips so open the blade\n");
						}
#endif
						
						//labial plosive obst
						pDph_t->target_l= 0;
						pDph_t->target_b = 1000;
						pDph_t->target_tb=1000;
					}
					
					if((place(pDph_t->allophons[pDph_t->nphone])) & BLADEAFFECTED )
					{	
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf("the blade  so open the lips\n");
						}
#endif
						
						
						//non labial plosive obstruent i.e. it's the blade
						pDph_t->target_b=0;
						pDph_t->target_l=1000;
						pDph_t->target_tb=1000;
						
					}
					
					
					if((place(pDph_t->allophons[pDph_t->nphone])) & FVELAR )
					{
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf("the tongue body so open blade and open the lips\n");
						}
						
#endif					
						//non-plosive non-labial obstruent i.e. the blade
						pDph_t->lstep =0;
						pDph_t->target_b= 1000;
						//pDph_t->area_b = pVtm_t->NOM_Fricative_Opening;
						pDph_t->target_l= 1000;
						pDph_t->target_tb= 0;
						
						
					
		
					}
				}
				
				else 
				{
#ifdef PH_DEBUG
					
					
					
					if(DT_DBG(PH_DBG,0x080))
					{
						printf("Non burst obst so narrow something...");
					}
#endif
					
					if((place(pDph_t->allophons[pDph_t->nphone])) & FLABIAL )
					{	
						
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf("the lips and open the blade\n");
						}
#endif
						//non-plosive labial obstruent
						pDph_t->lstep = 0;			
				
						pDph_t->target_l= 100;
						
						pDph_t->target_b = 1000;
						pDph_t->bstep=0;
						pDph_t->target_tb= 1000;					
					}
					
					else if((place(pDph_t->allophons[pDph_t->nphone])) & BLADEAFFECTED )
					{	
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf("the blade and open the lips\n");
						}
#endif					
						

						//non-plosive non-labial obstruent i.e. the blade
						pDph_t->lstep =0;
						pDph_t->target_b= pVtm_t->NOM_Fricative_Opening;
						//pDph_t->area_b = pVtm_t->NOM_Fricative_Opening;
						pDph_t->target_l= 1000;
						pDph_t->target_tb= 1000;
			

					}
					else if((place(pDph_t->allophons[pDph_t->nphone])) & FVELAR )
					{
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf("the tongue body so open blade and open the lips\n");
						}
#endif					
						
						//non-plosive non-labial obstruent i.e. the blade
						pDph_t->lstep =0;
						pDph_t->target_b= 1000;
						//pDph_t->area_b = pVtm_t->NOM_Fricative_Opening;
						pDph_t->target_l= 1000;
						pDph_t->target_tb= 100;
						//if(pDph_t->allophons[pDph_t->nphone] == SP_J)
						//	pDph_t->target_tb= 400;
					}
					else //something else like a spanish y so releasee the other
					{
						pDph_t->target_l= 1000;
						pDph_t->target_tb= 1000;
						
					}
				}
				//special rule for dh and th eab 7/10/02 
				//help ken
				
				
		}	//Fobst
		
		
		
		if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSTOP
			&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FBURST))
		{
			//okay we're at a stop without bursts ie. flapped d, glottal stop
			//or an soncon nasal
			
			if(place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED )
				//for alvelars
			{
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					printf(" At beg of Phone w / stop w/alvel so blade target to 0 ");
					printf(" and labial to 1000 \n");
				}
#endif
				pDph_t->in_bclosure = 1;
				pDph_t->target_b =0;
				pDph_t->target_l =1000;
				pDph_t->target_tb =1000;
				pDph_t->agspeed =1;
			}
			if( place(pDph_t->allophons[pDph_t->nphone]) & FVELAR)
			{
				//for velars indicate closed tongue body;
				pDph_t->target_tb =0;
				pDph_t->target_b =1000;
				pDph_t->target_l =1000;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					printf(" At beg of Phone w / stop -atb so atb  target to 0 ");
					printf(" and others to 1000 \n");
				}
#endif
			}
			
			if(place(pDph_t->allophons[pDph_t->nphone]) & FLABIAL )
			{
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					printf(" At beg of Phone w / stop w/labial so lip target to 0 ");
					printf(" and blade to 1000 \n");
				}
#endif
				
				pDph_t->target_b =1000;
				pDph_t->target_l =0;

				
			}
			
		}//It has a Stop
		
			if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSON1 
			&& !(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL))
		{
			//				A sonorant wow!
			if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSTOP ))
			{
				if(pDph_t->phonestep >1) //wait in case of a release
				//this loooks like its redundant
				pDph_t->target_b = 1000;
				pDph_t->target_l = 1000;
				pDph_t->target_tb= 1000;
				if(PAV.tspesh ==0)
				{
					//vot hard
					//and previous thing wasn't a stop with vot 
					pDph_t->target_ag= pVtm_t->NOM_VOIC_GLOT_AREA;
					
					
					if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FOBST
						|| pDph_t->nphone == 0 )
					{
					pDph_t->agspeed = 1;
			}
					else
			{
						pDph_t->agspeed = 3;
					}
				
					pDph_t->area_g  -= 150;
			}
				
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
			{
					printf("in a FSON1 ag tar to pVtm_t->NOM_V  \n");	
					
				}		
				
#endif
				
//?? needed				pDph_t->target_b = 1000;
			}
			///open whatever isn't shut
			if(pDph_t->allophons[ pDph_t->nphone] == USP_R)
				
				//	|| pDph_t->allophons[ pDph_t->nphone+1] == USP_N
				//	|| pDph_t->allophons[ pDph_t->nphone+1] == USP_M)
			{
				pDph_t->target_ag += 200;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					printf(" widening test glottis for r's  \n");
				}
#endif
				}
			else if(place(pDph_t->allophons[pDph_t->nphone]) & FALVEL )
				{
					pDph_t->target_ag = pVtm_t->NOM_Open_Glottis+100;
				}
			else if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSON1 )
			{
				
				pDph_t->target_b = 1000;
			}
			
			else if(!((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FPLOSV)
				&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FVOICD) ))
			{
				pDph_t->target_ag= pVtm_t->NOM_VOIC_GLOT_AREA;
				pDph_t->agspeed = 1;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					printf("redundant?? in a FSON1 ag tar to pVtm_t->NOM_V  \n");	
					
				}
				
				
				
#endif
			}
			
		}	
		
	
		
		
		
	} // phone!+phonelast i.e. set only once at start of phone		

		

	if(place(pDph_t->allophons[pDph_t->nphone]) & FVELAR  )	
	{
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			printf("velar affected so jam A2\n");
		}
#endif
		
		pDph_t->parstochip[OUT_A2] = 5000;
	}
	

	
	if (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FOBST)
		if( !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FSTOP)
			&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FBURST)
			)
		{
			//if(pDph_t->tcum >= ((pDph_t->allodurs[pDph_t->nphone]-6)))
			//if next a fricative anticipate start fric earllier
			//and widen glotis
			//	pDph_t->target_ag += 20;
			
			if(pDph_t->tcum >= ((pDph_t->allodurs[pDph_t->nphone]-1)))
			{
				
				pDph_t->target_ag = 1200;
				if((place(pDph_t->allophons[pDph_t->nphone+1])) & FLABIAL )
				{	
					pDph_t->target_l=100;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" Anticipating fric narrow lips.\n");
					}
#endif				
					
				}
				
				
				
				if(place(pDph_t->allophons[pDph_t->nphone]) & FDENTAL 
					|| place(pDph_t->allophons[pDph_t->nphone+1]) & FLABIAL )
				{
					
					//blade not affect so set it open
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" DENTAL or labial affected so jam A2\n");
					}
#endif
				
					{
						pDph_t->parstochip[OUT_A2] = 1000;
					}
				}	
						else if(place(pDph_t->allophons[pDph_t->nphone+1]) & FPALATL )
						{
							
							//blade not affect so set it open
#ifdef PH_DEBUG
							if(DT_DBG(PH_DBG,0x080))
							{
								printf(" PALATEL affected so jam A3&4\n");
							}
#endif
							pDph_t->parstochip[OUT_A2] = 2000;
						}
						else if(place(pDph_t->allophons[pDph_t->nphone+1]) & FALVEL )
						{
							
							//blade not affect so set it open
#ifdef PH_DEBUG
							if(DT_DBG(PH_DBG,0x080))
						{
								printf(" ALVELAR affected so jam A2\n");
							}
#endif
					if(place(pDph_t->allophons[pDph_t->nphone+1]) & FALVEL )
						if(pDph_t->phonestep >2)
							//lt combo the thing looks like an s
							if(place(pDph_t->allophons[pDph_t->nphone-1]) & FLABIAL )
							{
								pDph_t->parstochip[OUT_A2] = 2000;
							}
							else
							{
							pDph_t->parstochip[OUT_A2] = 3000;

						}
						
						
					}
					
				}
					
			}



		
		
		if(!(pDph_t->allofeats[pDph_t->nphone+1 ] & FDUMMY_VOWEL)
			&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FVOICD)
			&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FSONOR
			&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FCONSON)
		{	
			//in things like was happy the glottis needs to opn enough in anticipation so that
			//we don't get a glottal pulse at release
			//also we need the closuer if in frication to open sslowly
			if((pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-5)))
			{
				//kinda a cheat added all at once because > 1000 doen't matter.4
				pDph_t->target_l += 30;
				pDph_t->target_b += 30;
				pDph_t->target_tb += 30;
			}
			
	
		}

		if(!(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL)
			&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FVOICD)
			&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSONOR
			&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FCONSON)
		{
			pDph_t->target_l = 1000;
			pDph_t->target_b = 1000;
			pDph_t->target_tb= 1000;
				
			

	
					
	}
	if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FNASAL ))
	{
	if(place(pDph_t->allophons[pDph_t->nphone]) & FDENTAL )
	{
		
		//blade not affect so set it open
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			printf(" DENTAL affected so jam A2\n");
		}
#endif
			if(phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FVOICD)
				pDph_t->parstochip[OUT_A2] = 1100;
			else
			{
					
					{
						pDph_t->parstochip[OUT_A2] = 1000;
					}
			}	


		if(pDph_t->allophons[pDph_t->nphone] == USP_DH
			|| pDph_t->allophons[pDph_t->nphone] == USP_TH
			|| pDph_t->allophons[pDph_t->nphone] == USP_DZ
			 )
		{
			pDph_t->parstochip[OUT_A2] = 1200;
		}
			
					
					
					
		}	
	else if( place(pDph_t->allophons[pDph_t->nphone]) & FLABIAL )
	{
				
		//blade not affect so set it open
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			printf(" Labial affected so jam A2\n");
		}
#endif
	pDph_t->parstochip[OUT_A2] = 1300;
					
					
	}
	else if(place(pDph_t->allophons[pDph_t->nphone]) & FPALATL )
	{
		//blade not affect so set it open
		if( (pDph_t->allophons[pDph_t->nphone] == USP_JH
			|| pDph_t->allophons[pDph_t->nphone] == USP_CH
			||( pDph_t->allophons[pDph_t->nphone] ==  GRP_SH
			&& pDph_t->allophons[pDph_t->nphone-1] == GRP_T)))
		{
			

			
			if( pDph_t->area_b && pDph_t->localcnt <= 6 )
				
			{
				
				
				
				//After a few frames the front palatel shifts to a plaltel
				pDph_t->parstochip[OUT_A2] = 2200;
				pDph_t->localcnt++;	
				
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					printf(" PALATEL roll star \n ");
					
				}
#endif
			}
			else
				pDph_t->parstochip[OUT_A2] = 2000;
			
		}
		
	
		else
		{		
						pDph_t->localcnt =0;	
			if(phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FVOICD)
				pDph_t->parstochip[OUT_A2] = 2000;
			else
			pDph_t->parstochip[OUT_A2] = 2000;
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				printf(" PALATEL affected so jam A3&4\n");
			}
#endif
		}
		
	}
		else if(place(pDph_t->allophons[pDph_t->nphone]) & FALVEL )
	{
			
			//blade not affect so set it open
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				printf(" ALVELAR affected so jam A2\n");
			}
#endif
				
					if(place(pDph_t->allophons[pDph_t->nphone+1]) & FALVEL )
						if(pDph_t->phonestep >2)
							//lt combo the thing looks like an s
							if(place(pDph_t->allophons[pDph_t->nphone-1]) & FLABIAL )
							{
								pDph_t->parstochip[OUT_A2] = 2000;
							}
							else
							{
							pDph_t->parstochip[OUT_A2] = 3000;
							}

							//
							pDph_t->parstochip[OUT_A2] = 3000;
							if( pDph_t->allophons[pDph_t->nphone] == USP_DH)
								pDph_t->parstochip[OUT_A2] = 3300;
				}
		}
			//eab if followed by a fricative the release ends up coarticulated to 
			//the new place hence 
		if(( place(pDph_t->allophons[pDph_t->nphone - 1]) & FPALATL 
			|| place(pDph_t->allophons[pDph_t->nphone - 1]) & FDENTAL 
			|| place(pDph_t->allophons[pDph_t->nphone - 1]) & FALVEL
			|| place(pDph_t->allophons[pDph_t->nphone - 1]) & FLABIAL)
			&& (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST)
			&&
			//eab if followed by a fricative the release ends up coarticulated to 
			//the new place hence we don't want to carry over the old coart
			(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FOBST))
/*	&&  (!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FPLOSV))*/
			if (pDph_t->phonestep < 1 || pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL)

		{
			pDph_t->parstochip[OUT_A2] = pDph_t->lastthing;
		}
		else
		{
				//delay change in a vowel
				if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSYLL)
					&& pDph_t->phonestep < pDph_t->allodurs[pDph_t->nphone] >>1)
				{
					pDph_t->parstochip[OUT_A2] = pDph_t->lastthing;
				}
				else
			pDph_t->lastthing =0;
		}
		if(pDph_t->parstochip[OUT_A2] >= 1000)
			pDph_t->lastthing = pDph_t->parstochip[OUT_A2];	
	}
					
	if(pDph_t->nphone)
		
		//Nasal velum rules
		if(place(pDph_t->allophons[pDph_t->nphone]) &  FVELAR
			&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FNASAL )
			//ng so set tbclosure
		{
			
			if(pDph_t->tcum <= (pDph_t->allodurs[pDph_t->nphone]))
			{
				pDph_t->in_tbclosure =1;
			}
		}
		



 		

#ifdef TONGUE_BODY_AREA
 if(pDph_t->allophons[ pDph_t->nphone] == FP_R)
 {
		pDph_t->target_tb = 200;
		//shut quick to avoid voicing --a cheap coarticualtion
		//pDph_t->area_tb = 200;
 }		

//if(pDph_t->allophons[pDph_t->nphone] == USP_LL
//				|| pDph_t->allophons[pDph_t->nphone] == USP_LX)


 if(!(place(pDph_t->allophons[pDph_t->nphone]) &  FVELAR))
		{
				pDph_t->in_tbclosure =0;
		}

		if(pDph_t->in_tbclosure)
		{
			//if it isn't closed by other means closr it now
			pDph_t->target_tb = 0;
		}
		if(pDph_t->target_tb < pDph_t->area_tb)
		{
			//
			if(pDph_t->area_tb)
			{
				//start shutting blade rapidly
				pDph_t->area_tb -= 310;
				//and close
				if(pDph_t->area_tb < pDph_t->target_tb )
					pDph_t->area_tb = pDph_t->target_tb;
			}
		}
		
		else if (pDph_t->target_tb != pDph_t->area_tb)
		{		

			if(pDph_t->in_tbrelease == 1 && pDph_t->area_tb < 1000)
			{

				 if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FBURST ||
					phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FBURST	)
				{	//plosive release sits stays at fric value until one step after bstep =0

					{
					pDph_t->area_tb = area_rel[pDph_t->tbstep];
					
					}
					if(pDph_t->tbstep <=9 )
						pDph_t->tbstep++;
					
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" Phone with burst with body_affected so target b=areea %d\n",
							pDph_t->area_tb);
					}
#endif
					
				}
				else
				{
					if((place(pDph_t->allophons[pDph_t->nphone])) & BLADEAFFECTED )
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf(" Affricate release with tongue  so target_tb to pVtm_t->NOM_fric \n");
						}
#endif
				pDph_t->target_tb = pVtm_t->NOM_Fricative_Opening;
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf(" Blade Affricate done- end rleease \n");
							
						}
#endif
						//					pDph_t->in_tbrelease =0;
						
						
				}
				
				
			}
			else if((pDph_t->in_tbrelease == 0 || pDph_t->in_tbclosure == 0))
			{
				
				if (pDph_t->target_tb > pDph_t->area_tb)
				{
					

				 //open the blade slower
					pDph_t->area_tb += ((pDph_t->target_tb - pDph_t->area_tb)>>3);
				}
				else
					//and close it 
					pDph_t->area_tb += ((pDph_t->target_tb - pDph_t->area_tb)>>1);
				
				// if however we're doing a Bladeaffected  delay open to allow closure
				// if it's a stop
//				..in going in theis is worng in the in. It needs to be in tbrelease as well
					//becuse body is opening slowly
				if(place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED 
				&& place(pDph_t->allophons[pDph_t->nphone-1]) & FVELAR)
				{
					if(pDph_t->phonestep <  coarticulation)
						pDph_t->area_tb = pDph_t->last_area_tb;
				}
			}
			/*if(place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED 
				&& place(pDph_t->allophons[pDph_t->nphone-1]) & FVELAR)
				{
					if(pDph_t->phonestep <  coarticulation)
						pDph_t->area_tb = pDph_t->last_area_tb;
				} */
			
		}

//end of new tb stuff


#else //TONGUE_BODY
		
		if(pDph_t->in_tbclosure)
		{
			if(place(pDph_t->allophons[pDph_t->nphone]) &  FVELAR)
			{
			if(!(phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FSTOP) 
				 && pDph_t->allophons[pDph_t->nphone] != GEN_SIL)
			{
			pDph_t->parstochip[OUT_F1] = 210;
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf("In a non-stopped velar so f1=210\n");
						}
					
#endif
			
			}
			else
			{	
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				printf("In stopped velar so f1=180\n");

			}					
#endif
			if(pDph_t->phonestep > 0
				|| pDph_t->allophons[pDph_t->nphone] == GEN_SIL)
			{
			pDph_t->target_b = 1000;
			pDph_t->target_l = 1000;

			}
			else
				//keep it closed until f1 acts for coarticulation
				//else you get strong glottal pule at boundary
				pDph_t->target_b = 0;

			if(!pDph_t->f1_velar)
			{
				pDph_t->f1_velar = pDph_t->parstochip[OUT_F1];
			}
			pDph_t->f1_velar -= ((pDph_t->parstochip[OUT_F1]-180)>>1);
			if(pDph_t->f1_velar < 290)
				pDph_t->f1_velar = 180;
			pDph_t->parstochip[OUT_F1] = pDph_t->f1_velar;
			pDph_t->tstep = 0;
			}
			}
		}
		else
			pDph_t->f1_velar =0;
		
		if(pDph_t->in_tbrelease || (pDph_t->tstep && pDph_t->tstep <7))
		{
			
			if(pDph_t->tstep <= 3 )
			{
				if(phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FSTOP 
					&& pDph_t->tstep == 1
				/*	|| phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FSTOP*/)
				{
											
						pDph_t->parstochip[OUT_F1] =240;
					
				}
				else 
				{
					pDph_t->parstochip[OUT_F1]= velar_f1[pDph_t->tstep];


				
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" velar  step %d f1 %d\n",pDph_t->tstep,pDph_t->parstochip[OUT_F1]);
					}
#endif
					
				}
				pDph_t->tstep++;
				
			}
			else if(pDph_t->tstep > 3)
			{
				if (velar_f1[pDph_t->tstep] < 300 )
					pDph_t->parstochip[OUT_F1] = velar_f1[pDph_t->tstep];

				else if(pDph_t->parstochip[OUT_F1] < velar_f1[pDph_t->tstep])
				{
				pDph_t->parstochip[OUT_F1] = ((pDph_t->parstochip[OUT_F1] + velar_f1[pDph_t->tstep]) >>1);
				}
				if(pDph_t->tstep >= 7)
						
					pDph_t->tstep = 0;
				pDph_t->tstep++;
				pDph_t->in_tbrelease =0;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					
				printf(" velar release step %d f1 %d\n",pDph_t->tstep,pDph_t->parstochip[OUT_F1]);
					
				}
#endif
				
			}
			
					
			
			
		}

		if(place(pDph_t->allophons[pDph_t->nphone-1]) &  FVELAR
			&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FNASAL 
			&& !(place(pDph_t->allophons[pDph_t->nphone]) &  FVELAR))
			//delay tongue drop slighlty for nx
			//f1 is a pain is has to be constantly overwritten in this
			//case if we're at sil i.e. end of phrase it doesn't get released
			if(pDph_t->phonestep <=2 
				|| pDph_t->allophons[pDph_t->nphone] == GEN_SIL)
			{
					pDph_t->parstochip[OUT_F1] =180;
					pDph_t->in_tbclosure =0;
					pDph_t->f1_velar =0;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" velar nasal ie. nx so delay release %d \n",pDph_t->tstep);
					}
#endif

			}
#ifdef HELP
		if(place(pDph_t->allophons[pDph_t->nphone+1]) &  FVELAR )
			if(pDph_t->phonestep == pDph_t->allodurs[pDph_t->nphone]-1)
			{
				//close earlier to avoid a burble
					pDph_t->parstochip[OUT_F1] =180;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" shut f1 early velar coming \n");
					}
#endif
			}

#endif
		if(place(pDph_t->allophons[pDph_t->nphone-1]) &  FVELAR &&
			place(pDph_t->allophons[pDph_t->nphone]) &  FVELAR)
			if(pDph_t->phonestep <= 1)
			{

				// hold for carticulation if it was burst
				if(pDph_t->lastf1 == 180 )
				{

					pDph_t->parstochip[OUT_F1] =180;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" lastf1=180 closure hold %d \n",pDph_t->tstep);
					}
#endif		
				}
			}
			if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone ]) & FSTOP
				&& place(pDph_t->allophons[pDph_t->nphone]) &  FVELAR
				&&  phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone +1]) & FSTOP)
			{
				//ve;ar stop-stop so don't release velar
						pDph_t->parstochip[OUT_F1] =180;
			}

#endif //TONGUE

		if(pDph_t->in_lclosure == 1)
		{
			pDph_t->target_l = 0;
			pDph_t->lstep = 0;
			
		}


		if(pDph_t->in_lfric)
		{

			//release(frication) during a fricative
			
			pDph_t->area_l = pVtm_t->NOM_Fricative_Opening;
			pDph_t->target_l = pVtm_t->NOM_Fricative_Opening;
		
			 if(pDph_t->nphonelast != pDph_t->nphone)
			{
				// just changed phone so cancel fric and go to release
				 if(!(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL))
				 {
			

				 //keep on fricating if last thing
					pDph_t->in_lrelease =1;
					pDph_t->area_l = 270;
				pDph_t->lstep =3;
								
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					printf("Release labial frication\n");
				}
#endif
				 }

				
			}
#ifdef PH_DEBUG
			 
			if(DT_DBG(PH_DBG,0x080))
			{
				printf("In labial frication\n");
			}
#endif

			
			
		}
		
		else if(pDph_t->target_l < pDph_t->area_l)
		{
			//
			if(pDph_t->area_l)
			{
				//start shutting lips rapidly
				pDph_t->area_l -= 400;
				//and close
				if(pDph_t->area_l < pDph_t->target_l )
					pDph_t->area_l = pDph_t->target_l;
			}
		}		
		else if (pDph_t->target_l != pDph_t->area_l)
		{	

			if(pDph_t->in_lrelease == 1 && pDph_t->area_l < 1000)
			{

				 if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FBURST ||
					phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FBURST	)
				{	//plosive release sits stays at fric value until one step after bstep =0
					if(pDph_t->lstep == -1) //HELPME MGS
					{
						pDph_t->area_l = pVtm_t->NOM_Fricative_Opening;
						pDph_t->lstep =1;
						
					}
					else
					{
					pDph_t->area_l = area_rel[pDph_t->lstep];
					if(pDph_t->lstep <=9 )
						pDph_t->lstep++;
					}
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" Phone with burst with blade_affected so target l=areea %d\n",
							pDph_t->area_l);
					}
#endif
				}
				else
				{
					if((place(pDph_t->allophons[pDph_t->nphone])) & FLABIAL )
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf(" Affricate release with lips so target_l to pVtm_t->NOM_fric \n");
						}
#endif
						pDph_t->area_l = pVtm_t->NOM_Fricative_Opening;
#ifdef PH_DElUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf(" llade Affricate done- end rleease \n");
							
						}
#endif
						//					pDph_t->in_lrelease =0;
						
						
				}
				
				
			}
			else if((pDph_t->in_lrelease == 0 || pDph_t->in_lclosure == 0))
			{
				if (pDph_t->target_l > pDph_t->area_l) //open the lips
					pDph_t->area_l += ((pDph_t->target_l - pDph_t->area_l)>>2);
				else
				{

						//and close it 
				if(pDph_t->target_l == 0)
					{
					pDph_t->area_l += ((pDph_t->target_l - (pDph_t->area_l+100))>>1);
				if(pDph_t->target_l == 0 && pDph_t->area_l < 300)
						pDph_t->area_l = 0;
				}
				else
				{
					pDph_t->area_l += ((pDph_t->target_l - (pDph_t->area_l))>>1);
				if(pDph_t->area_l < pDph_t->target_l )
					pDph_t->area_l = pDph_t->target_l;
				}
				}


				// if however we're doing a baldeaffected delay open to allow closure
				// if it's a stop
				if(place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED )
				{
					if(pDph_t->phonestep <  coarticulation)
						pDph_t->area_b = pDph_t->last_area_b;
				}

					//than closing
					pDph_t->area_l += ((pDph_t->target_l - pDph_t->area_l)>>2);
					if(pDph_t->target_l == 0 && pDph_t->area_l < 260)
						pDph_t->area_l = 0;
				
				// if however we're doing a blade delay open to allow closure
				// if it's a stop
				if(place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED )
				{
					if(pDph_t->phonestep < coarticulation)
						pDph_t->area_l = pDph_t->last_area_l;
				}
			}
			
			
			if (pDph_t->area_l > 1000)
				pDph_t->area_l= 1000; //safety code eventually eliminate
		}



		 if(pDph_t->target_b < pDph_t->area_b)
		{
			//
			if(pDph_t->area_b)
			{
				//start shutting blade rapidly
				pDph_t->area_b -= 400;
				//and close
				if(pDph_t->area_b < pDph_t->target_b )
					pDph_t->area_b = pDph_t->target_b;
			}
		}
		
		else if (pDph_t->target_b != pDph_t->area_b
			|| pDph_t->bstep == -1) // HELPME MGS
		{	
		

			if(pDph_t->in_brelease == 1 && pDph_t->area_b < 1000)
			{
					
				 if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FBURST ||
					phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FBURST	)
				{	//plosive release sits stays at fric value until one step after bstep =0
					if(pDph_t->bstep == -1)// HELPME MGS
					{
						pDph_t->area_b = pVtm_t->NOM_Fricative_Opening;
						pDph_t->bstep =1;
						pDph_t->target_b = 1000;
					}
					else
					{
					if(pDph_t->target_b != 0)
						//blade to blade wnats to stay closed
					{

					pDph_t->area_b = area_rel[pDph_t->bstep];
					if(pDph_t->bstep <=9 )
						pDph_t->bstep++;
					}
					else
						pDph_t->area_b =0;
					}
			
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" Phone with burst with blade_affected so area b=area %d\n",
							pDph_t->area_b);
					}
#endif
					
				}
				else
				{
					if(place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED )
					{
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf(" Affricate release with blade_affected so target_b to pVtm_t->NOM_fric \n");
						}
#endif
						pDph_t->area_b = pVtm_t->NOM_Fricative_Opening;
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf(" Blade Affricate done- end rleease \n");
							
						}
#endif
						//					pDph_t->in_brelease =0;
						
					}	
					else
						pDph_t->area_b += ((pDph_t->target_b - pDph_t->area_b)>>1);
				}
				
				
			}
					
			else if((pDph_t->in_brelease == 0 || pDph_t->in_bclosure == 0))
			{
				
				if (pDph_t->target_b > pDph_t->area_b)
				{
					
#ifdef notworking
					if(pDph_t->allophons[ pDph_t->nphone] == USP_R)
					//Special slow release for retroflexed r
					{
						
							if( pDph_t->tcum <= 10)
							{
							
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							printf(" retro \n");
							
						}
#endif
								
							}
								
					}

					else
#endif	
				     if(pDph_t->target_b <= 200
						 && pDph_t->area_b < 100)
						 pDph_t->area_b =  pDph_t->target_b;
					 else
						 pDph_t->area_b += ((pDph_t->target_b - pDph_t->area_b)>>1);
					

				}
				else
					//and close it 
				if(pDph_t->target_b == 0)
					{
					pDph_t->area_b += ((pDph_t->target_b - (pDph_t->area_b))>>2);
				if(pDph_t->target_b == 0 && pDph_t->area_b <= 500)
						pDph_t->area_b = 0;
				}
				else
				{
					pDph_t->area_b += ((pDph_t->target_b - (pDph_t->area_b))>>1);
				if(pDph_t->area_b < pDph_t->target_b )
					pDph_t->area_b = pDph_t->target_b;
				}

				// if however we're doing a labial delay open to allow closure
				// if it's a stop
				if(place(pDph_t->allophons[pDph_t->nphone]) & FLABIAL 
					|| place(pDph_t->allophons[pDph_t->nphone]) & FVELAR )
				{
					if(pDph_t->phonestep <  coarticulation)
					{
						pDph_t->area_b = pDph_t->last_area_b;
					//and if previous was a blade fric close it briefly
					if(place(pDph_t->allophons[pDph_t->nphone-1]) & BLADEAFFECTED
						&& pDph_t->area_b < 200)
						pDph_t->area_b =0;
					}
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" Coarticulating if prvious was a blade fric close it temporarily \n");
						printf(" and/or delay closure \n");
					}
#endif

				}
			}
			
			if (pDph_t->area_b > 1000)
				pDph_t->area_b= 1000; //safety code eventually eliminate
		}


#ifndef TOMBUCHLER	
			if(pDph_t->in_phrase_final == 1
				|| pDph_t->in_phrase_final == 2)
		{
				if(	(pDph_t->allofeats[pDph_t->nphone] & FTYPESYL) == FMONOSYL)
		{
					pDph_t->in_phrase_final = 2;
					if(pDph_t->tcum <= (pDph_t->allodurs[pDph_t->nphone]>>2)+vot_time)
			{
			
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
							printf(" Delaying til later becuase monosy\n");
					
				}
#endif
		
	}
	
		}
				
				
		
					
				}

				
			
#endif
			
					

		
	


			if((pDph_t->allophons[pDph_t->nphone] == FP_R))
			{

			//set ue and dc to zero need to set dctep as well or it will jump
				//after the r as dc will be set
			pDph_t->dcstep = 0;
			pDph_t->parstochip[OUT_DC] = 0;
			pDph_t->parstochip[OUT_UE] = 0;

			if( !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FVOICD))
			{
				
					
					//	pDph_t->area_g = pVtm_t->NOM_UNVOICED_SON;
						pDph_t->target_ag = pVtm_t->NOM_UNVOICED_SON;
						pDph_t->agspeed = 3;
			}
			else
			{
					
		
						//pDph_t->area_g = 1800;
						pDph_t->target_ag = 1280;
						pDph_t->agspeed = 3;
			}
			}


	//TEST
				if(!(pDph_t->allofeats[pDph_t->nphone] & FSTRESS)
					&& (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSYLL)
					&&  //next thing isn't a normal voiced phone
					 !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FVOICD))
				{
					if(!(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL))
						{
							//spread glottis for unstressed vowels
#ifdef PH_DEBUG
							if(DT_DBG(PH_DBG,0x080))
							{
								printf("spread glottis for unstressed vowels \n");
							}
#endif
							pDph_t->target_ag = pVtm_t->NOM_UNSTRESSED_VOWEL;
						}
						
					
				}
				
			
		
				if( pDphsettar->nframb >  (pDph_t->tcumdur-3))
				{
					
					if( pDphsettar->diplo <= 80)
					{
						pDphsettar->diplo += 20;
					}
					
				}
				
				else
				{
					pDphsettar->diplo =0;
				}
			
		
			
			pDph_t->parstochip[OUT_DP] = 0;//pDphsettar->diplo;

#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			if(pDphsettar->diplo)
			printf(" pDphsettar->diplo %d .\n",pDphsettar->diplo);
		}
#endif


		
		if(pKsd_t->sprate >= 350)
		// ADD IN FOR HIGH SPEED 
			pDph_t->agspeed =1;
				
		if( ((pDph_t->target_ag - pDph_t->area_g)>>pDph_t->agspeed) > 300)
			//talk to ken hack rule for now d ent had a ue dc problem with velum open and the glotis target jumps 
			//from 400 to 12000 couses a click 
					pDph_t->area_g += 350;
				else if( ((pDph_t->target_ag - pDph_t->area_g)) < -1600)
					//talk to ken hack rule for now d ent had a ue dc problem with velum open and the glotis target jumps 
					//from 400 to 12000 couses a click 
					pDph_t->area_g -= 600;
				
		else
					pDph_t->area_g += ((pDph_t->target_ag - pDph_t->area_g)>>pDph_t->agspeed);
				//+ pDph_t->delta_a_forap;
				
		//for high speed
		//pDph_t->area_g = pDph_t->target_ag;
	if(pDph_t->in_lrelease || pDph_t->in_tbrelease || pDph_t->in_brelease)
	{
		if(pDph_t->parstochip[OUT_BRST] == 0)
			if(pDph_t->in_tbrelease )
			pDph_t->parstochip[OUT_BRST] = 1;
			else
			//stronger for labial or blade
			pDph_t->parstochip[OUT_BRST] = 2;
		else 
			pDph_t->parstochip[OUT_BRST] = -1;
	}
		else 
				
				pDph_t->parstochip[OUT_BR] = 0;
				
			//	printf("%d \n",pDph_t->vowel_start_burst);
	pDph_t->area_ap += ((pDph_t->target_ap - pDph_t->area_ap)>>2);
	pDph_t->parstochip[OUT_CNK] = pDph_t->area_ap + pVtm_t->NOM_Area_Chink;
				tmp = pDph_t->area_g + pDph_t->delta_area_g ;
	if(tmp <0)
		tmp=0;
	pDph_t->parstochip[OUT_AG] = tmp;

	pDph_t->parstochip[OUT_AL] = pDph_t->area_l;
	pDph_t->last_area_b = pDph_t->area_b;
	pDph_t->last_area_l = pDph_t->area_l;
	if( pDph_t->area_flap < pDph_t->area_b)
	{
					if(pDph_t->area_flap < 0)
						pDph_t->area_flap =0;
		pDph_t->parstochip[OUT_ABLADE] = pDph_t->area_flap;
	}
			else
			{
		pDph_t->parstochip[OUT_ABLADE] = pDph_t->area_b;
			}
	pDph_t->parstochip[OUT_ATB] = pDph_t->area_tb;
//	printf(" %d %d %d\n",pDph_t->parstochip[OUT_ATB],pDph_t->area_tb,
//		pDph_t->tbstep);
				
				
			
				//printf(" %d \n",pDph_t->gps_value);
	if(pDph_t->allophons[pDph_t->nphone] == GRP_KH
		|| pDph_t->allophons[pDph_t->nphone] == SPP_J
		)

	pDph_t->parstochip[OUT_PLACE] = 80;

	else if(pDph_t->allophons[pDph_t->nphone] == GRP_CH)
	{
		pDph_t->parstochip[OUT_PLACE] = 45;
	}
	else if(place(pDph_t->allophons[pDph_t->nphone]) & FVELAR )
		//although y is considered an cons in this case it acts like a vowel.
		//need to research how to handle this in general this is just a hack fix for the release
	{
		if(
			 pDph_t->allophons[pDph_t->nphone+1] == SPP_Y)
		{
			pDph_t->parstochip[OUT_PLACE] = 45;
		}
		else
	{
			switch (begtyp(pDph_t->allophons[pDph_t->nphone+1]) )
		{
		case 1:
			pDph_t->parstochip[OUT_PLACE] = 45;
			break;
		case 3:
			pDph_t->parstochip[OUT_PLACE] = 40;
			break;
		default:
			pDph_t->parstochip[OUT_PLACE] = 42;
		}
	} 
	
	}

				tmp =0;
					if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FSTOP)
					&& pKsd_t->lang_curr == LANG_italian 
					&& (pDph_t->phonestep == 1 || pDph_t->phonestep == 2)
					&& pDph_t->in_brelease == 1)
					{
				//	pDph_t->bstep = -1;
				//	pDph_t->area_b=0;
					tmp =0;
					}
					else
				if(pDph_t->area_l != 0 && pDph_t->area_b != 0 &&
					pDph_t->area_tb != 0 )
				{
					if((pDph_t->area_l <= 400) && (pDph_t->area_l > 99))
					{
						tmp = 5400/(pDph_t->area_l);
					}
					if((pDph_t->area_b <= 400) && (pDph_t->area_b > 99))
	{
						if(tmp < 5400/(pDph_t->area_b))
						tmp = 5400/(pDph_t->area_b);
					}
					if((pDph_t->area_tb <= 400) && (pDph_t->area_tb > 99))
		{
						if(tmp < 5400/(pDph_t->area_tb));
						tmp = 5400/(pDph_t->area_tb);
		}
	}
				if(tmp == 0)
	{
					pDph_t->parstochip[OUT_GF] -= (pDph_t->parstochip[OUT_GF]>>1) ;
					if(pDph_t->parstochip[OUT_GF] < 0)
						pDph_t->parstochip[OUT_GF] =0;
				}
				else
				{
					//special hack for the unvoiced voiced z
					if(pDphsettar->phcur == ITP_DZ )
					{
						tmp -= 10;
					}
					if(tmp > 0)
						pDph_t->parstochip[OUT_GF] = tmp;
			else
		
						pDph_t->parstochip[OUT_GF] = 0;
				}
	//	printf(" %d %d \n",pDph_t->parstochip[OUT_GF],pDph_t->area_b);
					
}
					//#ifdef HACK //for testing a pressure drop pause
					//eab This is for a short pressure drop pause for that
					if(pDph_t->allofeats[pDph_t->nphone] & PRESSBOUND)
					{
						if(pDph_t->tcum <= pDph_t->allodurs[pDph_t->nphone]>>1)
						{
							pDph_t->pressure_gest += 20;                   
						}
						else
						{
							if(pDph_t->pressure_gest > 0)
								pDph_t->pressure_gest -= 20;
							else
								pDph_t->pressure_gest =0;		
	}
					}
					else
						pDph_t->pressure_gest =0;
					
					//#endif
#ifdef TOMBUCHLER
	 tmp = pDph_t->pressure-pDph_t->spressure- pDph_t->pressure_drop;

	 if ( pDph_t->nphone == pDph_t->nphonetot-1)
			tmp = 0;
#else
		tmp =  pDph_t->pressure - pDph_t->pressure_drop;
					tmp -= pDph_t->pressure_gest;
			
#endif
	if(tmp < 100 && pDph_t->nphone > 1
		|| tmp <0)
	{	
		pDph_t->pressure_drop =0;
		pDph_t->pressure = 0;
		pDph_t->syl_pressure =0;
		tmp =0;
	}	

	pDph_t->parstochip[OUT_F4] = pDph_t->curspdef[SPD_F4];

	pDph_t->parstochip[OUT_PS] = tmp;
	
	pDph_t->parstochip[OUT_AN] = pDph_t->area_n;
				
	//need to include issue where two obstruents are adjacentone voiced the other not,
	//so in this case the 
	// thing needs to the other extreme

	pDph_t->lastf1 = pDph_t->parstochip[OUT_F1];

	pDph_t->nphonelast = pDph_t->nphone;
	


	/* I think this should be in verify with oliver*/

	/* Compensate for loudness decrease when strongly tilted */
	if (pDph_t->parstochip[OUT_AV] > 3)
	{
		temptilt = (*parp >> 2) - 4;
		if (temptilt < 0)
			temptilt = 0;			   /* tilt must be 20 or more */
		pDph_t->parstochip[OUT_AV] += temptilt;		
	}

	if ( pDph_t->allophons[ pDph_t->nphone] == SPP_J)
	{
	
		r_modulation (phTTS,pDph_t->param[A2].outp, N10PRCNT, TRUE);
	}
	if (pDph_t->allophons[ pDph_t->nphone] == GRP_KH )
	{
		r_modulation (phTTS,pDph_t->param[A2].outp, N10PRCNT, FALSE);
		r_modulation (phTTS,pDph_t->param[A3].outp, N20PRCNT, FALSE);
		r_modulation (phTTS,pDph_t->param[AV].outp, N8PRCNT, TRUE);
	}

	else if (pDph_t->allophons[ pDph_t->nphone] == GRP_RR
		)
	{
		if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FVOICD) IS_MINUS)
				{
					pDph_t->parstochip[OUT_AV] -= 10;
					if(pDph_t->parstochip[OUT_AP] <= 45)
					{
					pDph_t->parstochip[OUT_AP] = 45;
					}
				}
			
			
#ifdef HLSYN		
		// close tongue body and then modulate my zero mass tongue body 
			pDph_t->target_ag = 700;
			pDph_t->parstochip[OUT_ATB] = 200;
			pDph_t->agspeed = 1;
			if (pDph_t->allophons[ pDph_t->nphone] == GRP_RR)
				//hack for 5.0 release fix it prettier later
			{
				
			
				if (phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone-1)]) & FVOWEL )
				{
					
					gr_modulation (phTTS,&pDph_t->parstochip[OUT_ATB], N40PRCNT, TRUE);
				}
				else
				{
					
					gr_modulation (phTTS,&pDph_t->parstochip[OUT_ATB], N40PRCNT, TRUE);
				}
			}
			else
			{
				pDph_t->target_ag = 1400;
				pDph_t->parstochip[OUT_ATB] = 170;
				gr_modulation (phTTS,&pDph_t->parstochip[OUT_ATB], N90PRCNT, TRUE);
				pDph_t->modulcount++; //increase modulation speed
			}
#else
if ((phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone-1)]) & FVOWEL) IS_PLUS)
		{
			r_modulation (phTTS,pDph_t->param[AB].outp, 0, FALSE);
			r_modulation (phTTS,pDph_t->param[AV].outp, N5PRCNT-300, FALSE);
			r_modulation (phTTS,pDph_t->param[A2].outp, N20PRCNT, FALSE);
			r_modulation (phTTS,pDph_t->param[A3].outp, N20PRCNT, TRUE);
		}
		else
		{
			r_modulation (phTTS,pDph_t->param[AB].outp, 0, FALSE);
			r_modulation (phTTS,pDph_t->param[AV].outp, N5PRCNT, FALSE);
			r_modulation (phTTS,pDph_t->param[A2].outp, N10PRCNT, FALSE);
			r_modulation (phTTS,pDph_t->param[A3].outp, N10PRCNT, TRUE);
		}
#endif
	if(pDph_t->parstochip[OUT_AV] < 0)
		pDph_t->parstochip[OUT_AV] = 0;

	}
//	else
//		/* Initialiatize the modulation counter eab 2/6/98*/
 //		pDph_t->modulcount =0;

	
	if (( 
		 pDph_t->allophons[ pDph_t->nphone+1] == SPP_R)
		
		|| pDph_t->allophons[ pDph_t->nphone] == ITP_R)
	{
		pDph_t->target_ag = 700;
	}
	if ( pDph_t->allophons[ pDph_t->nphone] == 8099)
	{
		if(pDph_t->modulcount <=7)
		{	
			
#if (defined HLSYN ) 
			if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FVOICD))
			{
				pDph_t->target_ag = 1100;
			}
			
			
			pDph_t->parstochip[OUT_ATB] = 300;
			
			pDph_t->parstochip[OUT_AG] = 900;
			//tr blend is a hack at the moment
			pDph_t->parstochip[OUT_A2] = 2100;
			r_modulation (phTTS,pDph_t->param[AREAB].outp, N100PRCNT, TRUE);
			
			
#else
			
			
			//	rit_modulation (phTTS,pDph_t->param[A2].outp, N10PRCNT, FALSE);
			//a2 is an index into tables for non_hlsyn don't modulate it
			//	rit_modulation (phTTS,pDph_t->param[A3].outp, N20PRCNT, FALSE);
			//if av isn't one yet due to plosive wait
			if(*pDph_t->param[AV].outp >30)
			r_modulation (phTTS,pDph_t->param[AV].outp, N70PRCNT, TRUE);
			

#endif
		}
	}
	
	else if (  pDph_t->allophons[ pDph_t->nphone] == SPP_R
		|| pDph_t->allophons[ pDph_t->nphone] == ITP_R)
	{
		if(1) //(pDph_t->smodulcount <=11)
		{		
#if (defined HLSYN ) 
			if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FVOICD))
			{
				pDph_t->target_ag = 1100;
			}
			pDph_t->parstochip[OUT_ATB] = 300;
			pDph_t->parstochip[OUT_AG] = 900;
			//tr blend is a hack at the moment
			pDph_t->parstochip[OUT_A2] = 2100;
			rs_modulation(phTTS,pDph_t->param[AREAB].outp, N100PRCNT, TRUE);
			
			
#else

			if(*pDph_t->param[AV].outp >30)
			{
				
			rs_modulation (phTTS,pDph_t->param[AV].outp, N90PRCNT, FALSE);
			rs_modulation (phTTS,pDph_t->param[F2].outp, N20PRCNT, TRUE);
			}
//			printf(" %d \n", *pDph_t->param[AV].outp);
#endif
		}
		
		
		
	}
	
	else if( pDph_t->allophons[ pDph_t->nphone] == SPP_RR
		|| pDph_t->allophons[ pDph_t->nphone] == ITP_RR
		)
	{

#ifdef HLSYN
		r_modulation (phTTS,pDph_t->param[AREAB].outp, N90PRCNT, TRUE);
#else
		r_modulation (phTTS,pDph_t->param[AV].outp, N20PRCNT, FALSE);
		r_modulation (phTTS,pDph_t->param[A2].outp, N20PRCNT, FALSE);
		r_modulation (phTTS,pDph_t->param[A3].outp, N20PRCNT, TRUE);
		

#endif

	}
	else
		/* Initialiatize the modulation counter eab 2/6/98*/
		if(pDphsettar->phcur != SPP_J
			)
		pDph_t->smodulcount =0;
	

 //for hebrew phonemes

	if(pDphsettar->phcur == USP_TZ )
	{
		pDphsettar->delay_cnt++;
		if(pDphsettar->delay_cnt <5)
		{
				pDph_t->parstochip[OUT_A6]=0;
				pDph_t->parstochip[OUT_A5]=0;
				pDph_t->parstochip[OUT_A4]=0;
				pDph_t->parstochip[OUT_A3]=0;
				pDph_t->parstochip[OUT_A2]=0;
				pDph_t->parstochip[OUT_AB]=0;
		}

		else if(pDphsettar->delay_cnt ==5)
		{
				pDph_t->parstochip[OUT_A6]=0;
				pDph_t->parstochip[OUT_A5]=0;
				pDph_t->parstochip[OUT_A4]=0;
				pDph_t->parstochip[OUT_A3]=0;
				pDph_t->parstochip[OUT_A2]=0;
			//  CHANGES EAB	7/13/98	BATS 711 Way too h
				pDph_t->parstochip[OUT_AB]=55;
		}
		else if(pDphsettar->delay_cnt <=7)
		{
				pDph_t->parstochip[OUT_A6]=0;
				pDph_t->parstochip[OUT_A5]=0;
				pDph_t->parstochip[OUT_A4]=0;
				pDph_t->parstochip[OUT_A3]=0;
				pDph_t->parstochip[OUT_A2]=0;
				pDph_t->parstochip[OUT_AB]=0;
		}

	}
	else
			/* if phcur !=ts then reset count*/
		pDphsettar->delay_cnt =0;




	/* eab 6/25/98 cleanup*/
	//EAB		7/13/98			BATS 711 
	/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
	/* if current phone is uvular /RR/, modulate several parameters      */
	/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
	/* EAB boolean true false in r_mod simply defines whether we're done and it's
	 time to increment the counter*/

	// if (pDph_t->allophons[pDph_t->nphone] == CZ)
#ifdef TOMBUCHLER
	if(pDphsettar->phcur == UKP_K)
	{
		*pDph_t->param[AREAB].outp =100;
	}


	if(pDph_t->allophons[pDph_t->nphone ] == UKP_NX)
	{
		*pDph_t->param[AREAG].outp = 450;
			r_modulation (phTTS,pDph_t->param[AREAG].outp, N50PRCNT, TRUE);
	}
	


	if (pDphsettar->phcur == USP_CZ	)
	{

#ifdef HLSYN
			*pDph_t->param[AREAB].outp =400;
			pDph_t->target_ag = 1400; //SPECIAL FOR THIS SOUND AT THE MOMENT
			h_modulation (phTTS,pDph_t->param[AREAB].outp , N90PRCNT, TRUE);
				//	pDph_t->parstochip[OUT_F1] = 270;
			//gr_modulation (phTTS,&pDph_t->parstochip[OUT_F1], N10PRCNT, TRUE);
#else
			*pDph_t->param[AP].outp = 50;
			h_modulation (phTTS,pDph_t->param[AP].outp , N20PRCNT, TRUE);
			*pDph_t->param[AV].outp = 20;
			h_modulation (phTTS,pDph_t->param[AV].outp , N20PRCNT, TRUE);
#endif

	}
//	else
//		/* Initialiatize the modulation counter eab 2/6/98*/
 //		pDph_t->modulcount =0;

#endif //tombuchler
	/* eab 12/12/96 Special code to allow for a burst + frication which occurs in the
	german sound TS the present code does not allow for this. This is a quick hack for 44
	until we're able to rewrite the burst/frication code in general This is not
	elegant but will work fine*/

#ifdef PH_DEBUG

/* DEBUG Code  verifies variables that should never hit 
	ceratin values  EAB 6/24/98*/

	
						//printf(" %d \n",pDph_t->parstochip[OUT_F2]);		
	
		if ((pDph_t->parstochip[OUT_T0] < 0) ||
		   (pDph_t->parstochip[OUT_F1] < 0)  ||
		   (pDph_t->parstochip[OUT_F2] < 0)  ||
		   (pDph_t->parstochip[OUT_F3] < 0)  ||
		   (pDph_t->parstochip[OUT_FZ] < 0)  ||
		   (pDph_t->parstochip[OUT_B1] < 0)  ||
		   (pDph_t->parstochip[OUT_B2] < 0)  ||
		   (pDph_t->parstochip[OUT_B3] < 0)  ||
		   (pDph_t->parstochip[OUT_AV] < 0)  ||
		   (pDph_t->parstochip[OUT_AP] < 0)  ||
							/* (pDph_t->parstochip[OUT_A2] < 0)  ||
		   (pDph_t->parstochip[OUT_A3] < 0)  ||
		   (pDph_t->parstochip[OUT_A4] < 0)  ||
		   (pDph_t->parstochip[OUT_A5] < 0)  ||
		   (pDph_t->parstochip[OUT_A6] < 0)  ||
							(pDph_t->parstochip[OUT_AB] < 0)  || */
		   (pDph_t->parstochip[OUT_TLT] < 0 ))
		{
#ifndef UNDER_CE
		WINprint(" ERROR Negative value \n");
#endif
		}

#endif	// PH_DEBUG

#ifdef NEW_VTM
			pDph_t->parstochip[OUT_FNP] = 290;

			if(pDph_t->allophons[ pDph_t->nphone] == GRP_R)
			{
			if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FVOICD) IS_MINUS)
				{
					pDph_t->parstochip[OUT_AV] -= 10;
					if(pDph_t->parstochip[OUT_AP] <= 45)
					{
					pDph_t->parstochip[OUT_AP] = 45;
					}
				}
			}
			

#ifndef HLSYN

						
		/* eab 4/23/98 Reduce av when a release schwa this code had the undesireable effect
		of reducing al occurrances of ex in  final position but it may be OKAY*/
		if ((pDph_t->allophons[pDph_t->nphone+1] == GEN_SIL)
			&& (pDph_t->allophons[ pDph_t->nphone] == GRP_EX))

			pDph_t->parstochip[OUT_AV] -=3;

					
#endif

#ifndef HLSYN

	if ((pDph_t->allophons[ pDph_t->nphone+1] == GEN_SIL)
		&& (pDph_t->allophons[ pDph_t->nphone] == SPP_IX))
		pDph_t->parstochip[OUT_AV] -=3;

	if ((pDph_t->allophons[ pDph_t->nphone+1] == GEN_SIL))
		pDph_t->parstochip[OUT_AV] -=3;

#endif

#endif /*NEW_VTM*/

		/* eab 4/5/98 For 5.0 all languages should do this    */
		/* In a lateral like l av jumps whem mouth and tongue open tract*/
			if(
				pDph_t->allophons[ pDph_t->nphone] == USP_LL
				|| pDph_t->allophons[ pDph_t->nphone] == FP_L
				|| pDph_t->allophons[ pDph_t->nphone] == SPP_L  
				|| pDph_t->allophons[ pDph_t->nphone] == GRP_L
				|| pDph_t->allophons[ pDph_t->nphone] == GRP_EL

				)
				pDph_t->parstochip[OUT_AV] -=6;
				/* BATS 690 There is evidently a slight discrepancy between where ph_draw
		thinks it is and where other parts of the code think they are, but this is too big
		to ponder now- this boiler plate will solve hte problem   */
		if(pDph_t->parstochip[OUT_AV] <0)
			pDph_t->parstochip[OUT_AV]=0;
	
        // added for French for Y phoneme as in "mieux", otherwise small click
		if(pDph_t->parstochip[OUT_F3] -pDph_t->parstochip[OUT_F2] < 300)
		{
			pDph_t->parstochip[OUT_F3] = pDph_t->parstochip[OUT_F2] + 300;
		}


#ifdef PH_SWAPDATA
#ifndef HLSYN
		j=sprintf(outbuf,"phdata%d",pDph_t->PHSwapCnt);
#else
		j=sprintf(outbuf,"hldata%d",pDph_t->PHSwapCnt);
#endif
		j=sprintf(outbuf+j,".out");


        if (pDph_t->PHSwapIn == NULL && pDph_t->PHSwapOut == NULL)
        {
#ifndef HLSYN
                pDph_t->PHSwapIn = fopen("phdata.in","rb");
#else
				pDph_t->PHSwapIn = fopen("hldata.in","rb");
#endif
				if(pDph_t->PHSwapIn == NULL)
				{
					pDph_t->PHSwapOut = fopen(outbuf,"wb");
#ifndef HLSYN
					fprintf(pDph_t->PHSwapOut," AP   F1   A2   A3   A4   A5   A6   AB  TILT  T0   AV   F2   F3    FZ   B1   B2   B3       \r\n");
#else
								fprintf(pDph_t->PHSwapOut," PHON   T0	F1   F2   F3    AG   AL   ATB  ABLADE   AN   CNK  PS    DC   UE   FZ   PLACE  \r\n");
#endif
				}
				
        }
#ifndef HLSYN
        if (pDph_t->PHSwapOut != NULL) {
                for (ii = 0; ii < 32; ii++) {
                        fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[ii]);
                }
                fprintf(pDph_t->PHSwapOut,"\r\n");
        }
		
        if (pDph_t->PHSwapIn != NULL) {
                for (ii = 0; ii < 32; ii++) {
					fscanf(pDph_t->PHSwapIn,"%4d ",&pDph_t->parstochip[ii]);
                }
                fscanf(pDph_t->PHSwapIn,"\r\n");
                if (feof(pDph_t->PHSwapIn)) {
					fclose(pDph_t->PHSwapIn);
					pDph_t->PHSwapIn = fopen("phdata.in","rb");
								fscanf(pDph_t->PHSwapIn," PH   T0	F1   F2   F3   F4   AG   AL   ATB  ABLADE  AN   CNK   PS   DC   UE   FZ   PLACE  \r\n");
                }
			}
#else
						
		if (pDph_t->PHSwapOut != NULL) 
							
#ifdef FULLSET
		{
							fscanf(pDph_t->PHSwapIn,"\r\n")
			if (pDph_t->PHSwapOut != NULL) {
                for (ii = 0; ii < 16; ii++) {
                        fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[ii]);
                }
                fprintf(pDph_t->PHSwapOut,"\r\n");
				 for (ii = 16; ii < 37; ii++) {
                        fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[ii]);
                }
                fprintf(pDph_t->PHSwapOut,"\r\n");
        }
#else
							{
			fprintf(pDph_t->PHSwapOut,"%4d ",(pDph_t->parstochip[OUT_PH] & PVALUE));
			fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_T0]);
			fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_F1]);
			fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_F2]);
			fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_F3]);
								fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_F4]);
			fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_AG]);
								fprintf(pDph_t->PHSwapOut,"%5d ",pDph_t->parstochip[OUT_AL]);
								fprintf(pDph_t->PHSwapOut,"%5d ",pDph_t->parstochip[OUT_ATB]);
								fprintf(pDph_t->PHSwapOut,"%5d ",pDph_t->parstochip[OUT_ABLADE]);
								fprintf(pDph_t->PHSwapOut,"%5d ",pDph_t->parstochip[OUT_AN]);
								fprintf(pDph_t->PHSwapOut,"%5d ",pDph_t->parstochip[OUT_CNK]);
			fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_PS]);
								fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_DC]);
								fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_UE]);
								fprintf(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_PLACE]);
							
								
			fprintf(pDph_t->PHSwapOut,"\r\n");
							}
#endif
		  if (pDph_t->PHSwapIn != NULL) {
#ifdef FULLSET
                 for (ii = 0; ii < 16; ii++) {
					fscanf(pDph_t->PHSwapIn,"%4d ",&pDph_t->parstochip[ii]);
                }
                fscanf(pDph_t->PHSwapIn,"\r\n");
				   for (ii = 16; ii < 37; ii++) {
					fscanf(pDph_t->PHSwapIn,"%4d ",&pDph_t->parstochip[ii]);
                }
                fscanf(pDph_t->PHSwapIn,"\r\n");
#else
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_PH]);
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_T0]);
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_F1]);
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_F2]);
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_F3]);
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_F4]);
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_AG]);
								fscanf(pDph_t->PHSwapIn,"%5hd ",&pDph_t->parstochip[OUT_AL]);
								fscanf(pDph_t->PHSwapIn,"%5hd ",&pDph_t->parstochip[OUT_ATB]);
								fscanf(pDph_t->PHSwapIn,"%5hd ",&pDph_t->parstochip[OUT_ABLADE]);
								fscanf(pDph_t->PHSwapIn,"%5hd ",&pDph_t->parstochip[OUT_AN]);
								fscanf(pDph_t->PHSwapIn,"%5hd ",&pDph_t->parstochip[OUT_CNK]);
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_PS]);
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_DC]);
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_UE]);
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_PLACE]);
								fscanf(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_GPS]);
			fscanf(pDph_t->PHSwapIn,"\r\n");
                
#endif
                if (feof(pDph_t->PHSwapIn)) {
					fclose(pDph_t->PHSwapIn);
					pDph_t->PHSwapIn = fopen("phdata.in","rb");

                }
		  }
			

#endif //hlsyn
			
#endif	// PH_SWAPDATA
		
	
#ifdef PH_DEBUG
	if(DT_DBG(PH_DBG,0x020))
	{
//	if((pDphsettar->phcur & PVALUE) != 0)
	{

#if defined (WIN32) && defined (PRINTFDEBUG)
									printf ("*phcur= %d \n",( pDphsettar->phcur & PVALUE));
				

#else
		//printf ("*phcur= %d \n", (pDphsettar->phcur & PVALUE));
		//printf ("%s \n", phprint(pDphsettar->phcur));



#endif	// defined (WIN32) && defined (PRINTFDEBUG)


#ifndef UNDER_CE
//		WINprintf ("phon= %d  ", ((pDph_t->allophons[ pDph_t->nphone]& PVALUE)));
			//printf ("*phcur= %d", pDphsettar->phcur);
//		printf ("%s \n", phprint(pDphsettar->phcur));

#endif
	for (ii = 0; ii<=32; ii++)		
		{
			WAIT_PRINT;
#if defined (WIN32) && defined (PRINTFDEBUG)
			WINprintf("%d ", pDph_t->parstochip[ii]);
#else
			printf("%d ", pDph_t->parstochip[ii]);
#endif // defined (WIN32) && defined (PRINTFDEBUG)
			SIGNAL_PRINT;
		}
		WAIT_PRINT;

#if defined (WIN32) && defined (PRINTFDEBUG)
		WINprintf ("\n");
#else
		printf ("\n");
#endif	// defined (WIN32) && defined (PRINTFDEBUG)
		SIGNAL_PRINT;
	}
	}
	
#endif	// PH_DEBUG

}




	// R_MOD CHANGES EAB		7/13/98			BATS 711
/*
 *      Function Name: r_modulation()     
 *
 *  	Description: Sets parameters for the Spanish r phoneme
 *
 *      Arguments: PDPH_T pDph_t,
 *				   short *formpointer, 
 *				   short percent, 
 *				   short bool
 *
 *      Return Value: void
 *
 *      Comments: Seems to be about the same as k_modulation; is used in phdraw()
 *					but k_modulation is not (don't know why).
 *
 */

void r_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp)
{
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
//	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	short  arg1, arg2;		/* arguments for mlsh1 */

	arg1 = *formpointer;

	
	switch (pDph_t->smodulcount)
	{
	case 0:
		arg2 = -percent;
		break;
	case 1:
		arg2 = -percent;
		break;
	case 2:
		arg2 = 0;//-percent;
		break;
	case 3:
		arg2 = 0;//+percent;
	
		break;
	case 4:
		arg2 = 0;
	
		break;
	case 5:
		arg2 =  0;
		break;
	case 6:
		arg2 = 0;//-percent;
		break;
	case 7:
		arg2 = -percent;
		
		break;
	case 8:
		arg2 = -percent;
		break;
	case 9:
		arg2 = 0;//-percent;
		break;
	case 10:
		arg2 = 0;//-percent;
		break;
	case 11:
		arg2 = 0;//-percent;
		break;
	case 12:
		arg2 = 0;// -percent;
		break;
	case 13:
		arg2 = -percent;
		break;
	case 14:
		arg2 = -percent>>1;
		break;
	case 15:
		arg2 = -percent>>1;
		break;
	case 16:
		arg2 = 0;//-percent>>1;
		break;
	default:
		arg2 = 0;//-percent>>1;
		if (temp == TRUE)
		{
			pDph_t->smodulcount=-1;
		}
	}
	
	
	*formpointer += mlsh1 (arg1,arg2);
	//ph_t->parstochip[OUT_AV] += 3;
	if (temp == TRUE)
	{
		pDph_t->smodulcount++;
	}
}
/* r_modulation */


void rit_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp)
{
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	//	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	short  arg1, arg2;		/* arguments for mlsh1 */
	
	arg1 = *formpointer;
	/* EAB I SEE TOO KINDS OR R ONE TAPPED THE OTHER SIMPLE  DEVOIED REGION BOTH SEE IN THE SAME 
	ENVIROMENTS--WHAT TO DO???? WAITING FOR JUAN'S RETURN*/
	
	
	switch (pDph_t->smodulcount)
	{
	case 0:
		arg2 = -percent;
		break;
	case 1:
		arg2 = -percent;
		break;
	case 2:
		arg2 = -percent;
		break;
	case 3:
		arg2 = -percent;
		
		break;
	case 4:
		arg2 = -percent ;
		
		break;
	case 5:
		arg2 =  -percent;
		break;
	case 6:
		arg2 = 0;//-percent;
		break;
	case 7:
		arg2 = 0;//-percent;
	
		break;
	case 8:
		arg2 = 0;//-percent;
		break;
	case 9:
		arg2 = 0;//-percent;
		break;
	case 10:
		arg2 = 0;//-percent;
		break;
	case 11:
		arg2 = 0;//-percent;
		break;
	case 13:
		arg2 =  0;//-percent;
		break;
	case 14:
		arg2 = 0;//-percent;
		break;
	case 15:
		arg2 = 0;//-percent;
		break;
	case 16:
		arg2 = 0;//-percent;
		break;
	default:
		arg2 = -percent;
		if (temp == TRUE)
		{
			pDph_t->smodulcount=-1;
		}
	}


	*formpointer += mlsh1 (arg1,arg2);
	//ph_t->parstochip[OUT_AV] += 3;
	if (temp == TRUE)
	{
		pDph_t->smodulcount++;
	}
}
/* rit_modulation */

void rs_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp)
{
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
//	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	short  arg1, arg2;		/* arguments for mlsh1 */

	arg1 = *formpointer;
	//single tap tarting in the closed
	// if arg > 200 then it must be a formant
	//so se can treat it differently
	
	switch (pDph_t->smodulcount)
	{
	case 0:
		arg2 = 0;
		break;
	case 1:
		if(arg1 >200)
			arg2 = -percent>>1;
		else
		arg2 = 0;
		break;
	case 2:
		if(arg1 >200)
			arg2 = -percent>>1;
		else
		arg2 = 0;
		break;
	case 3:
		if(arg1 >200)
			arg2 = -percent>>1;
		else
		arg2 = 0;//-percent>>1;
	
		break;
	case 4:
		if(arg1 >200)
			arg2 = -percent;
		else
		arg2 = -percent>>1;
	
		break;
	case 5:
		if(arg1 >200)
			arg2 = -percent;
		else
		arg2 =  -percent>>1;
		break;
	case 6:
		arg2 = -percent>>1;
		break;

	case 7:
		arg2 = 0;//-percent;
	
		break;
	case 8:
		
		arg2 = 0;//-percent;
		break;
	case 9:
		
		arg2 = 0;//-percent;
		break;
	case 10:

		arg2 = 0;
		break;
	case 11:
	
		arg2 = 0;//-percent>>1;
	default:
		
		arg2 = 0;
		
	}

	*formpointer += mlsh1 (arg1,arg2);

//	printf("%d \n ", *formpointer);

	if (temp == TRUE)
	{
		pDph_t->smodulcount++;
	}

}

/* rs_modulation */




/*
 *      Function Name: r_modulation()     
 *
 *  	Description: Sets parameters for the German r phoneme
 *
 *      Arguments: PDPH_T pDph_t,
 *				   short *formpointer, 
 *				   short percent, 
 *				   short bool
 *
 *      Return Value: void
 *
 *      Comments: Seems to be about the same as k_modulation; is used in phdraw()
 *					but k_modulation is not (don't know why).
 *
 */
 			// R_MOD CHANGES EAB		7/13/98			BATS 711

void gr_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp)
{
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
//	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;

	short            arg1, arg2;		/* arguments for mlsh1 */

	arg1 = *formpointer;

	switch (pDph_t->modulcount)
	{
	case 0:
		arg2 = -percent;
		break;
	case 1:
		arg2 = -percent;
		break;
	case 2:
		arg2 = -percent;
		break;
	case 3:
		
		arg2 = -percent;
		pDph_t->parstochip[OUT_AP] = 35;
		if (phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone-1)]) & FVOWEL )
			pDph_t->parstochip[OUT_AP] -=5;
		break;
	case 4:
		arg2 = -percent;
		pDph_t->parstochip[OUT_AP] =25;
		if (phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone-1)]) & FVOWEL )
			pDph_t->parstochip[OUT_AP] -=5;
		break;
	case 5:
		arg2 =  +percent;
		break;
	case 6:
		arg2 = +percent;
		break;
	case 7:
		arg2 = -percent;
		pDph_t->parstochip[OUT_AP] =30;
		if ((phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone-1)])) & FVOWEL )
			pDph_t->parstochip[OUT_AP] -=5;
		break;
	case 8:
		arg2 = -percent;
		pDph_t->parstochip[OUT_AP] =25;
		if ((phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone-1)])) & FVOWEL )
			pDph_t->parstochip[OUT_AP] -=5;
		break;
	case 9:
		arg2 = -( percent);
		break;
	case 10:
		arg2 = -percent;
		break;
	case 11:
		arg2 = +percent;
		break;
	case 13:
		arg2 =  +percent;
		pDph_t->parstochip[OUT_AP] =25;
		if ((phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone-1)])) & FVOWEL )
			pDph_t->parstochip[OUT_AP] -=5;
		break;
	case 14:
		arg2 = -percent;
		pDph_t->parstochip[OUT_AP] = 20;
		if ((phone_feature( pDph_t, pDph_t->allophons[ pDph_t->nphone-1])) & FVOWEL )
			pDph_t->parstochip[OUT_AP] -=5;
		break;
	case 15:
		arg2 = -percent;
		break;
	case 16:
		arg2 = -percent;
		break;
	default:
		arg2 = -percent;
		if (temp == TRUE)
		{
			pDph_t->modulcount=-1;
		}
	}
		if (temp == TRUE)
		{
			pDph_t->modulcount++;
		}

	/* switch */
	*formpointer += mlsh1(arg1,arg2);


}
/* r_modulation */


	// H_MOD CHANGES EAB		7/13/98			BATS 711
/*
 *      Function Name: r_modulation()     
 *
 *  	Description: Sets parameters for the Spanish r phoneme
 *
 *      Arguments: PDPH_T pDph_t,
 *				   short *formpointer, 
 *				   short percent, 
 *				   short bool
 *
 *      Return Value: void
 *
 *      Comments: Seems to be about the same as k_modulation; is used in phdraw()
 *					but k_modulation is not (don't know why).
 *
 */

void h_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp)
{
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
//	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
//	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	short  arg1, arg2;		/* arguments for mlsh1 */

	arg1 = *formpointer;
	/* EAB I SEE TOO KINDS OR R ONE TAPPED THE OTHER SIMPLE S DEVOIED REGION BOTH SEE IN THE SAME 
	ENVIROMENTS--WHAT TO DO???? WAITING FOR JUAN'S RETURN*/

	
	switch (pDph_t->modulcount)
	{
	case 0:
		arg2 =  0;
		break;
	case 1:
		arg2 = 0;
		break;
	case 2:
		arg2 = -percent;
		break;
	case 3:
		arg2 = -percent;
		break;
	case 4:
		arg2 = 0;
		break;
	case 5:
		arg2 =  0;
		break;
	case 6:
		arg2 = -percent;
		break;
	case 7:
		arg2 = 0;
		break;
	case 8:
		arg2 = 0;
		break;
	case 9:
		arg2 = 0;
		break;
	case 10:
		arg2 = -percent;
		break;
	case 11:
		arg2 = -percent;
		break;
	case 12:
		arg2 = -percent;
		break;
	case 13:
		arg2 =  0;
		break;
	case 14:
		arg2 = 0;
		break;
	case 15:
		arg2 = -percent;
		break;
	case 16:
		arg2 = 0;
		break;
	case 17:
		arg2 = 0;
		break;
	case 18:
		arg2 = -percent;
		break;
	case 19:
		arg2 = 0;
		break;
	default:
		arg2 = -percent;
		if (temp == TRUE)
		{
			pDph_t->modulcount=-1;
		}
	}

	*formpointer += mlsh1 (arg1,arg2);
	//ph_t->parstochip[OUT_AV] += 3;
	if (temp == TRUE)
	{
		pDph_t->modulcount++;
	}
}
/* h_modulation */
void Phrase_intial_sil_start(LPTTS_HANDLE_T phTTS)
{
	int tmp;
	PVTM_T pVtm_t = phTTS->pVTMThreadData;
	PKSD_T         pKsd_t = phTTS->pKernelShareData;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	
	
	tmp = 0;
	if(pDph_t->nphone != pDph_t->nphonelast)
	{
		
		//do at start of phone but not later i.e. once per phone only
		//Inital SILENCE INITALIZATION
		//Set intial deafults perhaps chnaged later
		pDph_t->in_phrase_final =0;
		pDph_t->last_real_phon = 1000; //init to large va;ue
		pDph_t->delta_area_gst =0;
		pDph_t->delta_area_gstop =0;
		pDph_t->delta_area_g =0;
		pDph_t->area_n=0;
		pDph_t->in_bclosure =0;
		pDph_t->in_lclosure = 0;
		if(pDph_t->number_words == 1)
		{
	
			if( (phone_feature(pDph_t,pDph_t->allophons[1]) & FPLOSV) IS_PLUS
				&& (phone_feature(pDph_t,pDph_t->allophons[1]) & FVOICD) IS_MINUS)
			{
				pDph_t->pressure = 200;
			
				
			}
			else
				pDph_t->pressure = 300;
		}
		
		pDph_t->pressure = 300;
		pDph_t->pressure_drop=0;
		pDph_t->target_ag = 400; 
		pDph_t->area_g=0;
		pDph_t->area_ap=0;
		pDph_t->target_ap=0;
		pDph_t->area_b = 1000;
		pDph_t->target_b = 1000;
		pDph_t->area_l = 1000;
		pDph_t->target_l = 1000;
		pDph_t->in_lrelease =0;
		pDph_t->in_brelease =0;
		pDph_t->in_tbrelease =0;
		pDph_t->in_tbclosure =0;
		pDph_t->area_tb = 1000;
		pDph_t->tbstep = 0;
		pDph_t->target_tb = 1000;
		pDph_t->syl_pressure = 0;
		
		
		
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			printf(" AT beg sil init to default.\n");
		}
#endif
		
		
		if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FOBST)
			
		{
			
			if(phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone+1]) & FBURST
				&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FSTOP)
				//we have a total blockgage with a burst so shut something
			{
				if(phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone+1]) & FVOICD)
				{
					pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA; //default open
					pDph_t->area_g = pVtm_t->NOM_VOIC_GLOT_AREA;
					pDph_t->agspeed =2;
					pDph_t->target_ap = 100;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" Voiced with (burst) so ag=40 ap =10\n");
					}
#endif
				}
				else
				{
					
					// We must anticipate plosive so open the glottis
					pDph_t->target_ag = pVtm_t->NOM_Open_Glottis; //default open
					pDph_t->area_g=pVtm_t->NOM_Open_Glottis;
					pDph_t->agspeed =3;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" Unvoiced burst with stop ag to .\n");
					}
#endif
				}
				
				if((place(pDph_t->allophons[pDph_t->nphone+1])) & FLABIAL )
				{	
					pDph_t->in_lclosure = 1;
					pDph_t->area_l = 0;
					pDph_t->area_b = 1000;
					pDph_t->target_l=0;
					pDph_t->target_narea =0;
					pDph_t->lstep=0;
					pDph_t->bstep=0;
					pDph_t->pressure = 200;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" At beg next a labial w burst.\n");
					}
#endif
					
					
				}
				
				if( place(pDph_t->allophons[pDph_t->nphone+1]) & BLADEAFFECTED )
				{	
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf("Phone after silence blade_affected with a burst so set area and target to 0\n");
					}
#endif
					pDph_t->in_bclosure = 1;
					pDph_t->area_b = 0;
					pDph_t->target_b = 0;
					pDph_t->target_l = 1000;
					pDph_t->target_narea =0;
					pDph_t->bstep=0;
				}
				// A tongue body movement done with F1
				if(( place(pDph_t->allophons[pDph_t->nphone+1])) & FVELAR )
				{
					pDph_t->in_tbclosure = 1;
					pDph_t->tstep =0;
					pDph_t->in_bclosure = 0;
					pDph_t->area_b = 1000;
					pDph_t->target_b = 1000;
					pDph_t->target_l = 1000;
					pDph_t->target_tb= 1000;
					pDph_t->target_narea =0;
					pDph_t->tbstep=0;
					pDph_t->target_tb = 0;	
					pDph_t->area_tb = 0;
					pDph_t->bstep=0;
					pDph_t->lstep=0;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" At beg sil next a velar.\n");
					}
#endif
				}
			}
			
			else
			{ //obst w/o a burst
				
				
				if(place(pDph_t->allophons[pDph_t->nphone+1]) & BLADEAFFECTED )
				{	
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" Phone after silence blade_affected without a burst \n");
					}
#endif
					pDph_t->in_bclosure = 0;
					//pDph_t->area_l = 1000;
					pDph_t->target_b = pVtm_t->NOM_Fricative_Opening+300;
					pDph_t->area_b = pVtm_t->NOM_Fricative_Opening+300;
					pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA;
					pDph_t->area_g = pVtm_t->NOM_VOIC_GLOT_AREA;
					pDph_t->agspeed = 3;
					
					pDph_t->target_l=1000;
					pDph_t->target_narea =0;
					pDph_t->bstep=0;
					
					pDph_t->pressure = 200; //get some pressure 
				}
			}
			}
			
			
			
			}
			
			
			
			
			if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FVOICD )
			{	
				pDph_t->in_tbclosure = 0;
				pDph_t->in_tbrelease = 0;
				pDph_t->in_tbclosure = 0;
				pDph_t->in_lclosure = 0;
				pDph_t->target_narea =0;
				pDph_t->agspeed = 2;
				pDph_t->lstep=0;
				pDph_t->bstep=0;
				if (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FOBST)
				{
					
					pDph_t->target_ag = pVtm_t->NOM_VOICED_OBSTRUENT;
				}
				else 
				{
					pDph_t->target_ag =pVtm_t->NOM_VOIC_GLOT_AREA;
				}
				
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					printf(" Phone after sil VOICD so targetag = %d \n",pDph_t->target_ag);
				}
#endif
				
				
				if((place(pDph_t->allophons[pDph_t->nphone+1])) & FLABIAL )
				{	
					pDph_t->in_lclosure = 0;
					pDph_t->area_l = pVtm_t->NOM_Fricative_Opening;
					pDph_t->area_b = 1000;
					pDph_t->target_l=150;
					pDph_t->target_narea =0;
					pDph_t->lstep=0;
					pDph_t->pressure = 300;
					
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						printf(" At beg sil next a labial w/o burst.\n");
					}
#endif
					
				} 
				
				if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FVOWEL) )
				{	
					pDph_t->in_lclosure = 0;
					pDph_t->target_narea =0;
					pDph_t->bstep=0;
					pDph_t->lstep=0;
					pDph_t->area_g=0;
					pDph_t->agspeed=1;
					pDph_t->area_l = 1000;
					pDph_t->area_b = 1000;
					pDph_t->target_l=1000;
					pDph_t->area_n = 0;
//					pDph_t->nasal_step =0;
					pDph_t->dcstep = 0;
				} //Inital SILENCE INITALIZATION
				if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FNASAL) )
				{
					pDph_t->area_n=200;
					
					if(pDph_t->allophons[pDph_t->nphone + 1] == USP_M
						|| pDph_t->allophons[pDph_t->nphone + 1] == USP_N)
						
					{
						pDph_t->target_ag =pVtm_t->NOM_VOIC_GLOT_AREA;
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							//			NNOOOOO ADD IN NG
							printf(" Phone after sil an english m or n \n so open velum and shut shomething..");
						}
#endif
					}
					else
						//must be an m
					{
						pDph_t->area_l = 0;
						pDph_t->target_l = 0;
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
							printf(" the lips!\n");
#endif
					}
					
					
					pDph_t->target_narea =240;
					
//					pDph_t->nasal_step = 7;
				}
//				else
//					pDph_t->nasal_step =0;
			}	
			else
			{
				pDph_t->area_g = 1410;
				pDph_t->target_ag = 1410;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
					printf("Starting with unvoiced so open glottis\n");
#endif
			}
			
			if(pDph_t->allophons[pDph_t->nphone+1] == USP_DH
				|| pDph_t->allophons[pDph_t->nphone+1] == USP_TH)
				//Post processsing rule to add special closure REF 1000
			{
				pDph_t->target_b = 0;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					printf("Special rule for blade with dh-th and dz \n");
				}
#endif
				
			}		
			}
			
			
			
			
			void Phrase_final_silence(LPTTS_HANDLE_T phTTS)
			{
				PVTM_T pVtm_t = phTTS->pVTMThreadData;
				PKSD_T         pKsd_t = phTTS->pKernelShareData;
				PDPH_T                  pDph_t = phTTS->pPHThreadData;
				PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
				
				
				{
					if(pDph_t->pressure >100)
						if (pDph_t->pressure_drop < 2000)
						{
							pDph_t->pressure_drop +=150;
#ifdef PH_DEBUG
							if(DT_DBG(PH_DBG,0x080))
							{
								printf("at ending sil press drop == %d \n",pDph_t->pressure_drop);
							}
#endif
						}		
						
						if(pDph_t->nphone != pDph_t->nphonelast)
						{		
							
							if(!(place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED ))
							{
								//blade not affect so set it open
#ifdef PH_DEBUG
								if(DT_DBG(PH_DBG,0x080))
								{
									printf(" Blade NOT affected so target b to 1000\n");
								}
#endif
								
								pDph_t->target_b=1000;
							}	
							
							if(place(pDph_t->allophons[pDph_t->nphone-1]) & FLABIAL)
							{
								//help me open lips for a plosive
								//pDph_t->in_lclosure = 0;
								//pDph_t->area_l = 0;
								if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1])) & FPLOSV )
								{
									pDph_t->target_l=1000;
								}
								else
								{
									pDph_t->target_l=0;
								}
								//pDph_t->target_narea =0;
								pDph_t->lstep=0;
								pDph_t->bstep=0;
							}
							else
								pDph_t->target_l =1000;
							if((place(pDph_t->allophons[pDph_t->nphone-1])) & BLADEAFFECTED )
							{	
#ifdef PH_DEBUG
								if(DT_DBG(PH_DBG,0x080))
								{
									printf(" Phone before ending silence blade_affected so set target to 0\n");
								}
#endif
								pDph_t->in_lclosure = 0;
								pDph_t->target_b = 0;
								//pDph_t->target_narea = 0;
								pDph_t->bstep=0;
							}
							else
								
								pDph_t->target_b = 1000;
							if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1])) & FSON1 )
							{	
								pDph_t->in_lclosure = 0;
								pDph_t->target_ag = 1800;
								pDph_t->area_g -= 80;
								
							}
							if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FOBST)
							{
								pDph_t->target_ag = 2500;
							}
							
							if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FVOICD ))
							{
								pDph_t->target_ag = 1800;
								pDph_t->area_g += 100;
								
								
							}
						}
				}
			}
			
#ifdef HLSYN
			void	Do_ue_dc(LPTTS_HANDLE_T phTTS)
			{
				PVTM_T pVtm_t = phTTS->pVTMThreadData;
				PKSD_T         pKsd_t = phTTS->pKernelShareData;
				PDPH_T                  pDph_t = phTTS->pPHThreadData;
				PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
				if(pDph_t->nphone == 0)
				{
					pDph_t->dcstep =0;
					
				}
				
				
				if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST
					&& pDph_t->dcstep == 0
					&& pDph_t->area_n == 0
					&& pDph_t->phonestep >= 1)
				{
					if(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FVOICD)
					{
						
						pDph_t->dcstep=1;
						pDph_t->uestep=1;
						
					}
					else
					{
						pDph_t->dcstep=-1;
						pDph_t->uestep=-1;
						
					}
					
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
						printf(" obstruent dcstep to %d\n",pDph_t->dcstep);
#endif			
				}
				
				if(pDph_t->dcstep != 0)
				{
					//if voiced incresae dcstep
					if(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FVOICD)
					{
						if(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FOBST)
						{
							//ADD VOICED UNVOICED
							//end it only if next thing not also a voiced obstruent
							if(pDph_t->dcstep > 0
								&& pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]-4
								&&!(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone+1)]) & FVOICD
								&& phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone+1)]) & FOBST))
							{
								pDph_t->dcstep--;
								if(	pDph_t->dcstep != 0)
									pDph_t->dcstep--;
								
								
#ifdef PH_DEBUG
								if(DT_DBG(PH_DBG,0x080))
									printf("moving dcstep at end to %d\n",pDph_t->dcstep);
#endif	
							}
							else
							{
								if(	pDph_t->dcstep <= 7)
									pDph_t->dcstep++;
							}
							
							
						}
						
						else if(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FOBST
							&& pDph_t->area_n ==0) 
						{
							//if dcstep is of opposite sign it means we're obstr-obstru so chnage faste
							if(pDph_t->dcstep < 0)
							{
								pDph_t->dcstep++;
								//for v5.
								//	if((pDph_t->allofeats[pDph_t->nphone+1] & FSTRESS))
								//	pDph_t->dcstep++;
							}
							if(pDph_t->dcstep < 9)
							{
								pDph_t->dcstep++;
								//for v5.
								//	if((pDph_t->allofeats[pDph_t->nphone+1] & FSTRESS))
								//	pDph_t->dcstep++;
							}
#ifdef PH_DEBUG
							if(DT_DBG(PH_DBG,0x080))
								printf("moving dcstep to %d\n",pDph_t->dcstep);
#endif	
						}
						else
							if((!(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FOBST)
								/*&& pDph_t->tcum > 1*/) 
								|| pDph_t->area_n != 0)
							{
								if(pDph_t->dcstep > 1)
								{
									pDph_t->dcstep-=2;
									if(pDph_t->dcstep < 0)
										pDph_t->dcstep =0;
								}
								else
									pDph_t->dcstep+=2;
								if(pDph_t->dcstep > 0)
									pDph_t->dcstep =0;
								

							}
							
#ifdef PH_DEBUG
							if(DT_DBG(PH_DBG,0x080))
								printf("now moving dcstep to %d\n",pDph_t->dcstep);
#endif	
							
					}
					else 
					{
						
						if(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FOBST
							&& pDph_t->area_n ==0) 
						{
							//if dcstep is of opposite sign it means we're obstr-obstru so chnage faste
							if(pDph_t->dcstep > 0)
							{
								pDph_t->dcstep--;
								//for v5.
								//	if((pDph_t->allofeats[pDph_t->nphone+1] & FSTRESS))
								//	pDph_t->dcstep++;
							}
							if(pDph_t->dcstep > -9)
								pDph_t->dcstep--;
						}
						else if((!(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FOBST)) 
							|| pDph_t->area_n != 0)
						{
							
							pDph_t->dcstep+=2;
							if(pDph_t->dcstep >0)
								pDph_t->dcstep =0;
							
						}
						
					}
					
					
					if(pDph_t->dcstep >= 0)
					{
						//need to look at dc to get sign right 
						//this in for potential idea of increasing dc for a labial
						
						if(place(pDph_t->allophons[pDph_t->nphone]) & FLABIAL)
						{
							//dc toward end of consonant
							pDph_t->parstochip[OUT_DC] = dcval[pDph_t->dcstep]; 
							pDph_t->parstochip[OUT_UE] = ueval[pDph_t->dcstep];
							//eab at the bouncdary start back down
						}
						else
						{
							//dc toward end of consonant
							pDph_t->parstochip[OUT_DC] = dcval[pDph_t->dcstep]; 
							pDph_t->parstochip[OUT_UE] = ueval[pDph_t->dcstep];
							//eab at the bouncdary start back down
						}
						
					}
					else
					{
						//this in for potential idea of increasing dc for a labial
						
						if(place(pDph_t->allophons[pDph_t->nphone]) & FLABIAL)
						{
							//dc toward end of consonant
							pDph_t->parstochip[OUT_DC] = -dcval[-pDph_t->dcstep]; 
							pDph_t->parstochip[OUT_UE] = -ueval[-pDph_t->dcstep];
							//eab at the bouncdary start back down
						}
						else
						{
							//dc toward end of consonant
							pDph_t->parstochip[OUT_DC] = -dcval[-pDph_t->dcstep]; 
							pDph_t->parstochip[OUT_UE] = -ueval[-pDph_t->dcstep];
							//eab at the bouncdary start back down
						}
					}		
					
	}
	else
	{
		pDph_t->parstochip[OUT_DC] = 0;
		pDph_t->parstochip[OUT_UE] = 0;
	}
	
	
	

	return;	
}
#endif

#ifdef HLSYN
void	Set_pressure(LPTTS_HANDLE_T phTTS)
{
	PVTM_T pVtm_t = phTTS->pVTMThreadData;
	PKSD_T         pKsd_t = phTTS->pKernelShareData;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	
	if(pDph_t->pressure <= pVtm_t->NOM_Sub_Pressure)
	{
		if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone])) & FVOICD)
		{
			
			pDph_t->pressure += 70;
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
				
			{
				printf(" AT first phone so build up pressure for sonorant \n");
			}
#endif
		}
		else
		{
			
			pDph_t->pressure += 80;
			
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
				
			{
				printf(" AT first phone so build up pressure for unvoiced\n");
			}
#endif
		}	
		
	}	
	
	
	if((pDph_t->allofeats[pDph_t->nphone] & FSTRESS)== FEMPHASIS
		/*&& (((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone])) & FSYLL) IS_PLUS)*/) 
	{		
		
		if(pDph_t->tcum <= pDph_t->allodurs[pDph_t->nphone]-NF130MS)
		{
			if(pDph_t->stress_pulse > 0)
				pDph_t->stress_pulse -=  pVtm_t->STRESS_STEP;
		}
		else
		{
			if(pDph_t->stress_pulse < pVtm_t->STRESS_PRESSURE)
				pDph_t->stress_pulse += pVtm_t->STRESS_STEP;
		}
	}
#ifdef outfor_now
	else if( !(pDph_t->allofeats[pDph_t->nphone] & FSTRESS)
		&& ((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone])) & FSYLL)) 
	{		
		
		if(pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]-NF50MS)
		{
			if(pDph_t->stress_pulse < 0)
				pDph_t->stress_pulse +=  pVtm_t->STRESS_STEP;
		}
		else
		{
			if(pDph_t->stress_pulse > -pVtm_t->UNSTRESS_PRESSURE)
				pDph_t->stress_pulse -=  pVtm_t->STRESS_STEP;
		} 
		if(place(pDph_t->allophons[pDph_t->nphone +1]) & FLABIAL
			&& ((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone])) & FPLOSV))
		{
			if(pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]-NF45MS)
			{
				
				pDph_t->target_l = 0;
			}
		}
	}
#endif
	else 
		
		pDph_t->stress_pulse=0; //but it already should be this should be redundant
		
}
#endif
