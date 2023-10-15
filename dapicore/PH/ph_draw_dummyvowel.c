/* 
 ***********************************************************************
 *                           Copyright ©
 *	  Copyright © 2002 Fonix Corporation. All rights reserved. 
 *    Copyright © 2000-2001 Force Computer, Inc., a Solectron company. All rights reserved.
 *    © Digital Equipment Corporation 1996, 1997,1998,  1999 All rights reserved.
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
*/

#include "port.h"
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


#define phone_feature(a,b) (pDph_t->cur_speaker[(b)>>8]->featb[(b)&0x00FF])
#define place(b) (pDph_t->cur_speaker[(b)>>8]->place[(b)&0x00FF])
#define begtyp(a,b) (pDph_t->cur_speaker[(b)>>8]->begtyp[(b)&0x00FF])

#define phone_feature_2(b,a) (((pDph_t->allofeats[(a)] & FDUMMY_VOWEL)) ? \
					  ((phone_feature(pDph_t,pDph_t->allophons[(a-1)]) & FVOICD)? \
					  (phone_feature(pDph_t,pDph_t->allophons[(a)])):\
						(phone_feature(pDph_t,pDph_t->allophons[(a)])&(~FVOICD))): \
						(phone_feature(pDph_t,pDph_t->allophons[(a)])) )


const short lplos_build_time=7;
const short bplos_build_time=7;

#if defined PH_DEBUG || defined PH_SWAPDATA
int ii;			   /* for regression testing eab */
#endif                                           

#ifndef NO_INCLUDED_C_FILES
#include "ph_draw1.c" /* pick up the language dependent code */
#endif
//moved to port.h for each platform - mlt
//#if defined (WIN32) && defined (PRINTFDEBUG)
//#include "dbgwins.h"
//#endif
void r_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp);
void rit_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp);
void rs_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp);
void ParameterModulation(LPTTS_HANDLE_T phTTS, short *pwParameter, 
						 short *pwSequence, short nMax, short bIncrement);
void gr_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp);
void h_modulation (LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp);
//static void add_feature (PDPH_T pDph_t
void Phrase_intial_sil_start(LPTTS_HANDLE_T phTTS);
void Phrase_final_silence(LPTTS_HANDLE_T phTTS);
void	Set_pressure(LPTTS_HANDLE_T phTTS);
void Do_ue_dc(LPTTS_HANDLE_T phTTS);
void Do_once_per_phoneme(LPTTS_HANDLE_T phTTS);
void Do_Nasal(LPTTS_HANDLE_T phTTS);

extern char *phprint (short c);

#if (defined HLSYN || defined INTEGER)
	
	const short nasalization[13]={0, 0, 50, 100, 160, 180, 200,260,320,450,675,780,885};
	//const short nasalization[13]={0, 150, 200, 300, 400, 500, 600,700,800,800,805,8100,885};
	const short velar_f1[8] = { 180,220,260,280,320,390,400,410};
	const short dcval[13] = { 0, 20,40,60,80, 100,120, 140, 160, 180,200,220,240};

	const  short ueval[11] = { 0,40,60,80,100,120,140,160,180,200,220};


#endif //hslyn

	
void phdraw (LPTTS_HANDLE_T phTTS)
{
	PVTM_T pVtm_t = phTTS->pVTMThreadData;
	PKSD_T         pKsd_t = phTTS->pKernelShareData;
	//	SPD_CHIP	  far    *spdef;
	PARAMETER     *np;		   /* Pointer to control values    */

	short	*parp;	   /* Pointer to output buffer     */
	short	value;                         
	short	coarticulation =4;
	short coart_transtime=0;
	short	tmp,tmp1, ptmp =0 ;
	short	vot_time;
#if (defined HLSYN || defined INTEGER )
	short	barea_rel[18] = { 0,550,1000,1000,1000,
		1000,1000,1000,1000,1000,1000,1000,1000,
		1000,1000,1000,1000,1000};
	short	final_area_rel[18] = { 0,250,350,550,750,
		950,1000,1000,1000,1000,1000,1000,1000,
		1000,1000,1000,1000,1000};
	short	area_rel[18] = { 0,350,550,750,900,
		1000,1000,1000,1000,1000,1000,1000,1000,
		1000,1000,1000,1000,1000};
		short	tbarea_rel[18] = { 0,130,160,250, 350,
		500,1000,1000,1000,1000,1000,1000,1000,
		1000,1000,1000,1000,1000 };

	short	farea_rel[20] = {  500, 300,100,100, 100,
		100,100,100,100,100,100,100,100,
		100,100,100,100,100, 100, 100};
	short retro[6] = {100,70,50,30,20,10};
	//short nasalspolezero[x];
#endif //hlsyn

#ifdef PH_SWAPDATA
	char outbuf[20];
	short j;
#endif

	short			pholas = GEN_SIL;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;

	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
		
	
#ifndef MSDOS
#ifndef ARM7
		volatile BOOL		*bInReset;
#endif
#endif
	
		short                   temptilt;		
		
#ifndef MSDOS
#ifndef ARM7
		/* MGS 10/14/1997 BATS #470 Fixed crashed due to reset */
		bInReset =&(pDph_t->phTTS->bInReset);
#endif
#endif
			
		// the ARM compiler desn't like this in the array definition MGS
#if	(defined HLSYN || defined INTEGER )
		barea_rel[0]=pVtm_t->NOM_Fricative_Opening;
		area_rel[0]=pVtm_t->NOM_Fricative_Opening;
#endif
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
			pDph_t->param[OQU].outp = &(pDph_t->parstochip[OUT_OQ]);
			pDph_t->param[BRST].outp = &(pDph_t->parstochip[OUT_BRST]);
			pDph_t->param[BR].outp = &(pDph_t->parstochip[OUT_BR]);
		}
#endif
	//variables that are only modified here and need to be initallized
		pDph_t->parstochip[OUT_BRST] =0;
		
		if (pDph_t->nphone>=1)
		{
			pholas = pDph_t->allophons[ pDph_t->nphone - 1];
		}
		else
			pholas=0;
#if (defined TOMBUCHLER  )
		coarticulation = 0;
#else
		if(pKsd_t->lang_curr != LANG_german)
			coarticulation = 4;
		else
			coarticulation = 4;
#endif
		
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
					
#ifdef GERMAN_not //useful with hlsyn
					/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
					/* change first part of parallele amplitudes of                     	 */
					/* german affricate KS                                             	 */
					/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
					if((pDph_t->allophons[ pDph_t->nphone] == GRP_KSX) &&
						(pDph_t->tcum < (np->tspesh + 3)))
					{
						if (np == &PA2)
						{
							*parp = 42;
						}
						else if (np == &PA3)
						{
							*parp = 40;
						}
						else if (np == &PA4)
						{
							*parp = 0;
						}
						else if (np == &PA5)
						{
							*parp = 0;
						}
						else if (np == &PA6)
						{
							*parp = 0;
						}
						else if (np == &PAB)
						{
							*parp = 0;
						}
						
					}
					/* if */
#endif /* #ifdef GERMAN_out */
					/* Double burst for /k,g,ch,jh/                         */
					/*per caroline double burst is wrong for UK*/
#if (defined  INTEGER || !(defined HLSYN) )
					
					
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
			if(np == &PAV)
			{
				vot_time = 0;
				if(np->tspesh)
				{
					pDph_t->vot= np->tspesh; 
					if(pKsd_t->lang_curr == LANG_french)
					{
						//closed glottis for stop
						pDph_t->target_ag = 0;
						if(  pDph_t->tcum == np->tspesh-1)
						{
							pDph_t->target_ag = 120;
						}
						else if(  pDph_t->tcum >= np->tspesh)
						{
							pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA;
						}
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							FNX_PRINTF(" vot sets glotal opening %d \n",np->tspesh);
						}
#endif
					}
					else
					{
						//do this only for syl to set vot after plos
						//need to delay glotal spread by vot time
						pDph_t->vot= np->tspesh;

						if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSON1)
						{
							if(np->tspesh == 1)
							{
								pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA;
								if(pDph_t->area_g > pVtm_t->NOM_VOIC_GLOT_AREA+600)
									pDph_t->area_g = pVtm_t->NOM_VOIC_GLOT_AREA+600;
								pDph_t->agspeed =pVtm_t->VOT_speed;
							}
							else if( pDph_t->tcum == 3 && 
									 np->tspesh > 5 )
							{
								//long release start a slow drop
								if(pVtm_t->VOT_speed)
								{
									if( pDph_t->target_ag > pVtm_t->NOM_VOIC_GLOT_AREA+700)
										pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+700;
									pDph_t->agspeed =2;
								}
							}

							else if( pDph_t->tcum == np->tspesh-5 )
							{
								if(pVtm_t->VOT_speed)
								{
									pDph_t->agspeed = pVtm_t->VOT_speed;
								}
								if( pDph_t->target_ag > pVtm_t->NOM_VOIC_GLOT_AREA+1200)
									pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+1200;
							}

							else if( pDph_t->tcum == np->tspesh-2 && 
									 pDph_t->target_ag > pVtm_t->NOM_VOIC_GLOT_AREA+800 )
							{
								pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+800;
								PH_DEBUG_2080_P1(" Anticipating vot target_ag = %d\n", pDph_t->target_ag);
							}

							if( pDph_t->tcum == np->tspesh )
							{
								pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA;

								//except if in sil or dummy
								if( pDph_t->allophons[ pDph_t->nphone] != GEN_SIL && 
									pDph_t->allofeats[pDph_t->nphone] & FDUMMY_VOWEL )
								{
									pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+800;
								}

								PH_DEBUG_2080_P2(" vot sets glottal closing: vot=%d, target_ag=%d \n",
									np->tspesh, pDph_t->target_ag);
							}
						}	
					}
				}
				else
					pDph_t->vot=0;
			}
			
	}
	
	
	/* * * * * * * * * * * * * * */
	/* Reduce AV if glstop:   	 */
	/* * * * * * * * * * * * * * */
//	FNX_PRINTF( " %d \n",pDph_t->parstochip[OUT_AV]);
	if (pDph_t->parstochip[OUT_AV] > 6)
	{
		pDph_t->parstochip[OUT_AV] -= pDph_t->avglstop;
	}
#if (defined  INTEGER || !(defined HLSYN) )
	
	
	parp = &(pDph_t->parstochip[OUT_TLT]);
	
	*parp += (pDph_t->spdeftltoff - 3); /*from fphdraw.c*/
	
	
	
	/* Breathy offset special code */
	if (pDph_t->breathysw == 1)
	{	/* Set in ph_setar.c */
		if (pDph_t->parstochip[OUT_AV] > 40)
		{	/* Do only if AV on  */
			/* Add aspiration to voicing */
			if (pDphsettar->breathyah < 27)
			{
				pDphsettar->breathyah += 2;		/* asp increase 32 db/100 ms */
			}
			
			
			value = frac4mul (pDph_t->spdeflaxprcnt, (pDphsettar->breathyah ));
			
			/* Tilt down voicing spectrum */
			if (pDphsettar->breathytilt < 16)
			{
				pDphsettar->breathytilt += 1;	/* tilt decrease 16 dB/100 ms */
			}
			*parp += frac4mul (pDph_t->spdeflaxprcnt, pDphsettar->breathytilt);
#ifdef DEBUGPHT
#if defined (WIN32) && defined (PRINTFDEBUG)
			FNX_PRINTF("til2=%d \n",*parp);
#endif
#endif	// DEBUGPHT
		}
	}
	else
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
#else
	pDph_t->parstochip[OUT_TLT] =0;
	//it doesn't really do anything in hlsyn
#endif
	
	
	
	/* add in formant scaling */
	//Note scaling breaks f1==180 stuff
	if( pDph_t->parstochip[OUT_F1] > 250)
		pDph_t->parstochip[OUT_F1] = frac4mul( pDph_t->parstochip[OUT_F1], pDph_t->fnscale ) + ((4096 - (S32)pDph_t->fnscale ) >> 4);
	pDph_t->parstochip[OUT_F2] = frac4mul( pDph_t->parstochip[OUT_F2], pDph_t->fnscale ) + ((4096 - (S32)pDph_t->fnscale ) >> 3);
	pDph_t->parstochip[OUT_F3] = frac4mul( pDph_t->parstochip[OUT_F3], pDph_t->fnscale );
	
#if (defined HLSYN || defined INTEGER)
	pDph_t->parstochip[OUT_SEX] = pDph_t->malfem;
	for (; np <= &PTONGUEBODY; np++)
	{
		
		if(np == &PAREAL)
		{
			if(np->tspesh)
			{
				if(pDph_t->tcum >= np->tspesh )
				{
					pDph_t->in_brelease=0;
					pDph_t->in_tbrelease=0;
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
					pDph_t->in_tbrelease=0;
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
								// not honmorganic
								if(!((place(pDph_t->allophons[pDph_t->nphone+1]) & BLADEAFFECTED)
									== (place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED)))
								{
									pDph_t->in_brelease=1;
									pDph_t->bstep = -1;
									pDph_t->target_b = pVtm_t->NOM_Fricative_Opening;
								}
							}
							else
								if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FNASAL  )
									&& !(place(pDph_t->allophons[pDph_t->nphone]) & FGLOTTAL)
									&& !(phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD  ))
									pDph_t->in_brelease=1;

						}
						else	//affricate- release it
						{
								pDph_t->in_brelease=1;
							
								if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FRETRO)
								{
									if(pDph_t->bstep == 0)
										pDph_t->bstep = -5;
									else if (pDph_t->bstep >= -1 )
										pDph_t->bstep = -1;
								}
								else
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
				if (pDph_t->tcum >= np->tspesh )
				{
					
					pDph_t->in_lrelease=0;
					pDph_t->in_tbclosure=0;
					pDph_t->in_tbclosure=0;
					
					if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FCONSON )
					{	
						if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FPLOSV)
						{
							//re-enabled this is needed to prevent
							//bogus k release in black top.
							if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FSTOP))
							{
								//plos-not a polosive release it
								//or if stop followed by fric??
								// not honmorganic
								if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FOBST))
								{
									
									pDph_t->in_tbrelease=1;
									pDph_t->tbstep = -1;
									pDph_t->target_tb = pVtm_t->NOM_Fricative_Opening;
								}
								else
								{
									if(pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-2))
									{
									pDph_t->in_tbrelease=1;
									pDph_t->tbstep = -1;
									pDph_t->target_tb = pVtm_t->NOM_Fricative_Opening;
									}
								}
							}
							
						}
						else
							//affricate- release it
						{
							pDph_t->in_tbrelease=1;
							pDph_t->tbstep = -1;
							pDph_t->target_tb = pVtm_t->NOM_Fricative_Opening;
						}
						
					}
					else
						if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FNASAL  ))
							pDph_t->in_tbrelease=1;
				}
				else if (pDph_t->tcum  >= (np->tspesh-  (bplos_build_time+1)) 
					&& (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FBURST))
				{
					pDph_t->in_tbclosure=1;
					pDph_t->in_tbrelease=0;
					pDph_t->in_lrelease=0; 
					pDph_t->in_brelease=0;
				}
				//	else
				//	pDph_t->in_bfric =0;
			}//pareab
		}
		
	}
	
	if(pDph_t->nphone != pDph_t->nphonelast)
	{
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF("===================== at phone %d - %s ======================== \n", 
				pDph_t->nphone,
				phprint( pDph_t->allophons[pDph_t->nphone] ) );
		}		
#endif

		pDph_t->phonestep = 0;
		pDph_t->modulcount = 0;
	}
	else
	{
		pDph_t->phonestep ++;
	}
	
#if (defined HLSYN || defined INTEGER)
	
	if(pDph_t->nphone == 0) //in intial silence anticipate intial parameters
	{	
		Phrase_intial_sil_start(phTTS);
#ifdef HLSYN
		Do_ue_dc(phTTS);
#endif
		ptmp=0;
	}

	else if(pDph_t->allophons[pDph_t->nphone] == GEN_SIL &&
		( pDph_t->nphone > pDph_t->nallotot -4)	)
	{
			//we're end silence  silence
		{
		Phrase_final_silence(phTTS);
		pDph_t->target_ap =0;
		}
	}
	else // in a regular phoneme
	{
	if(pDph_t->allophons[pDph_t->nphone] == GEN_SIL )
		//intermediate silence				
	{
		pDph_t->target_ag = 2400;
		pDph_t->target_ap =0;

	}
#ifdef HLSYN		
		Do_ue_dc(phTTS);		

		Set_pressure(phTTS);
#endif



		//ACTIONS TO DO ONCE UPON A NEW phoneme		
		if(pDph_t->nphone != pDph_t->nphonelast)
		{			
			
		Do_once_per_phoneme( phTTS)	;
		
	} // phone!+phonelast i.e. set only once at start of phone		
	
	
	// THIS IS FOR IF WE DID A GLOTTAL STOP RIGHT BEFORE OBST
	if( (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone])   & FSTOP) &&	 	
	   !(phone_feature_2(pDph_t,pDph_t->nphone)   & FVOICD) &&
		(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FOBST) &&		// Next phoneme is obstruent
		 pDph_t->target_ag <= pVtm_t->NOM_Open_Glottis )	
	{
		if(pDph_t->phonestep > 2)
		{
			pDph_t->target_ag = pVtm_t->NOM_Open_Glottis;
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF("DID A GLOTTAL STOP RIGHT BEFORE OBST SET GLOTTIS TARGET \n");
			}
#endif	
		}
	}
	
	if (pDph_t->phonestep==1 
		&& (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST)
		&& (!(phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD)))
	
	{
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF("opening glottis later for unvoiced obst stop\n");
		}
#endif
		pDph_t->target_ag = pVtm_t->NOM_Open_Glottis;
		if ((phone_feature_2(pDph_t,pDph_t->nphone-1) & FVOICD)
			&&(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FNASAL))
		{
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF("prev phone unvoiced, set glottis to 1400 to avoid voicing at opening\n");
			}
#endif
			pDph_t->area_g=1200;
		}
	}

	if( phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FVOWEL)
	{
		if( pDph_t->allophons[pDph_t->nphone] == GRP_I
			||
			pDph_t->allophons[pDph_t->nphone] == GRP_E
			||
			pDph_t->allophons[pDph_t->nphone] == GRP_AE
			||
			pDph_t->allophons[pDph_t->nphone] == GRP_U
			||
			pDph_t->allophons[pDph_t->nphone] == GRP_UE
			||
			pDph_t->allophons[pDph_t->nphone] == GRP_O
			||
			pDph_t->allophons[pDph_t->nphone] == GRP_OE
			||
			pDph_t->allophons[pDph_t->nphone] == GRP_A
			||
			pDph_t->allophons[pDph_t->nphone] == GRP_EI
			||
			pDph_t->allophons[pDph_t->nphone] == GRP_AU
			||
			pDph_t->allophons[pDph_t->nphone] == GRP_EU			
			)
			//helpme  help me too: added the diphthongs. 
			
			
			
			if((pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-4)
				&& pDph_t->tcum > 8)
				&& 	(!(phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD)))
			{
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF("GERMAN vowel ending so target glottis to 1400 \n");
				}
#endif
				pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+1000;
				pDph_t->agspeed = 2;
			}
	}

	if(place(pDph_t->allophons[pDph_t->nphone]) & FVELAR  )	
	{
		if (pKsd_t->lang_curr == LANG_japanese
			&& pDph_t->allophons[pDph_t->nphone+1] == JP_I)
				pDph_t->parstochip[OUT_A2] = 5001;
			else
			    pDph_t->parstochip[OUT_A2] = 5000;

		PH_DEBUG_2080_P1(" Velar affected so jam A2 (A2 = %d)\n", pDph_t->parstochip[OUT_A2]);
	}
	
	if(place(pDph_t->allophons[pDph_t->nphone-1]) & FALVEL 
		&& (phone_feature( pDph_t, pDph_t->allophons[ pDph_t->nphone]) & FOBST)
		&& pDph_t->nphone !=0
		&& (phone_feature( pDph_t, pDph_t->allophons[ pDph_t->nphone-1]) & FBURST)
		&& (phone_feature( pDph_t, pDph_t->allophons[ pDph_t->nphone-1]) & FOBST)
		&& (phone_feature_2( pDph_t,  pDph_t->nphone-1) & FVOICD)
		&& (phone_feature_2( pDph_t,  pDph_t->nphone) & FVOICD))
	{
		coart_transtime=1;
		coarticulation=1;
	}
	else
	{
		coart_transtime=0;
		if (coarticulation > pDph_t->allodurs[pDph_t->nphone]>>1)
			coarticulation=pDph_t->allodurs[pDph_t->nphone]>>1;
		else
			coarticulation=4;
	}

	
	if (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FOBST)
		if( !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FSTOP)
			&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FBURST
			&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FNASAL))
			)
		{
			//if(pDph_t->tcum >= ((pDph_t->allodurs[pDph_t->nphone]-6)))
			//if next a fricative anticipate start fric earllier
			//and widen glotis
			//	pDph_t->target_ag += 20;
			
			if(pDph_t->tcum >= ((pDph_t->allodurs[pDph_t->nphone]-1)))
			{
				
				if((place(pDph_t->allophons[pDph_t->nphone+1])) & FLABIAL )
				{	
					
					pDph_t->target_l=100;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Anticipating fric narrow lips.\n");
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
						FNX_PRINTF(" DENTAL or labial affected so jam A2\n");
					}
#endif
					
					pDph_t->parstochip[OUT_A2] = 1000;
					
				}	
				else if(place(pDph_t->allophons[pDph_t->nphone+1]) & FPOSTALVELAR )
				{
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Postalvelar affected so jam A2 \n");
					}
#endif
					 pDph_t->parstochip[OUT_A2] = 2000;
				}
				else if(place(pDph_t->allophons[pDph_t->nphone+1]) & FPALATL )
				{
					
					//blade not affect so set it open
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" PALATEL or palatel-alvelar affected so jam A3&4\n");
					}
#endif
				if(place(pDph_t->allophons[pDph_t->nphone+1]) & FALVEL )
								//palatel alvelar for Japanese
					{
						pDph_t->parstochip[OUT_A2] = 2500;
					}
					else 
					pDph_t->parstochip[OUT_A2] = 2000;


				}
				else if(place(pDph_t->allophons[pDph_t->nphone+1]) & FALVEL )
				{
					
					//blade not affect so set it open
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" ALVELAR ALVELAQR-PALATEL affected so jam A2\n");
					}
					

#endif
					if(place(pDph_t->allophons[pDph_t->nphone+1]) & FPALATL )
								//palatel alvelar for Japanese
							{
								pDph_t->parstochip[OUT_A2] = 2500;
							}	
				 else if(place(pDph_t->allophons[pDph_t->nphone+1]) & FALVEL )
						if(pDph_t->phonestep >2)
						{
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
			
		}
		
		
		
		
		
#ifndef TOMBUCHLER
		if(!(pDph_t->allofeats[pDph_t->nphone+1 ] & FDUMMY_VOWEL)
			&& !(phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD)
			&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FSONOR
			&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FCONSON)
		{	
			//in things like was happy the glottis needs to opn enough in anticipation so that
			//we don't get a glottal pulse at release
			//also we need the closuer if in frication to open sslowly
			if((pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-2)))
			{
				//kinda a cheat added all at once because > 1000 doen't matter.4
				pDph_t->target_l += 10;
				pDph_t->target_b += 10;
				pDph_t->target_tb += 10;
			}
			
			if(pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-2))
			{
				pDph_t->target_ag = pVtm_t->NOM_UNVOICED_SON;
				pDph_t->agspeed = 2;
				
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF(" Open glottis in anticipation of  HX. \n");
				}
#endif
			}
		}
#else
		if(pDph_t->allophons[pDph_t->nphone] == UKP_HX )
			
			pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+1000;
		else
#endif
			if(!(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL)
				&& !(phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD)
				&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSONOR
				&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FCONSON)
			{
				pDph_t->target_l = 1000;
				pDph_t->target_b = 1000;
				pDph_t->target_tb= 1000;
				if (pKsd_t->lang_curr == LANG_japanese)

				pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+1200;
				else
				pDph_t->target_ag = pVtm_t->NOM_UNVOICED_SON;

				pDph_t->agspeed = 2;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF("HX so  glottis  target  at %d \n", pDph_t->target_ag);
				}
#endif
				
			}
			
			if(!(pDph_t->allofeats[pDph_t->nphone + 1] & FDUMMY_VOWEL)
				&& !(phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD)
				&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FSONOR
				&& phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FCONSON
				&& (pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-7)))
			{
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF("SPread glottis for hx  \n");
				}
#endif
				
				
			}
			if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FNASAL ))
			{
				if(place(pDph_t->allophons[pDph_t->nphone]) & FPOSTALVELAR )
				{
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Postalvelar affected so jam A3&4\n");
					}
#endif
					pDph_t->parstochip[OUT_A2] = 2000;
				}
				if(place(pDph_t->allophons[pDph_t->nphone]) & FDENTAL )
				{
					
					//blade not affect so set it open
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" DENTAL affected so jam A2\n");
					}
#endif
					
					
					pDph_t->parstochip[OUT_A2] = 1000;
						
						
					
					
					if(pDph_t->allophons[pDph_t->nphone] == USP_DH
						|| pDph_t->allophons[pDph_t->nphone] == USP_TH
						|| pDph_t->allophons[pDph_t->nphone] == USP_DZ
						|| pDph_t->allophons[pDph_t->nphone] == UKP_DH
						|| pDph_t->allophons[pDph_t->nphone] == UKP_TH
						|| pDph_t->allophons[pDph_t->nphone] == UKP_DZ)
					{
						pDph_t->parstochip[OUT_A2] = 1200;
					}
					
					if( pDph_t->allophons[pDph_t->nphone] == USP_TH
						|| pDph_t->allophons[pDph_t->nphone] == UKP_TH)
					{
						pDph_t->parstochip[OUT_A2] = 1201;
					}
					
					
					
				}	
				else if( place(pDph_t->allophons[pDph_t->nphone]) & FLABIAL )
				{
					
					//blade not affect so set it open
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Labial affected so jam A2\n");
					}
#endif
					if(pDph_t->allophons[pDph_t->nphone] == JP_F)
						pDph_t->parstochip[OUT_A2] = 1301;
					else
						pDph_t->parstochip[OUT_A2] = 1300;
					
					
				}
			
				if(place(pDph_t->allophons[pDph_t->nphone]) & FPALATL )
				{
					//unless otherwise modified
					pDph_t->parstochip[OUT_A2] = 2000;
					if(pDph_t->allophons[pDph_t->nphone] == USP_ZH )
								pDph_t->parstochip[OUT_A2] = 2001;
					
					if(	  pDph_t->allophons[pDph_t->nphone] == KRP_CH
						|| pDph_t->allophons[pDph_t->nphone] == KRP_JH
							|| pDph_t->allophons[pDph_t->nphone] == KRP_CC)

							pDph_t->parstochip[OUT_A2] = 2201;

					if( (pDph_t->allophons[pDph_t->nphone] == USP_JH
						|| pDph_t->allophons[pDph_t->nphone] == USP_CH
						||( pDph_t->allophons[pDph_t->nphone] ==  GRP_SH
						&& pDph_t->allophons[pDph_t->nphone-1] == GRP_CH)))
					{
						//FNX_PRINTF("areab %d localcnt %d \n",pDph_t->area_b,pDph_t->localcnt);
						pDph_t->agspeed=2;
						if(pDph_t->phonestep == 0)
							pDph_t->localcnt = 1;

						if(pDph_t->allophons[pDph_t->nphone] == USP_CH
						|| pDph_t->allophons[pDph_t->nphone] == USP_JH)
						
						{
							pDph_t->parstochip[OUT_A2] = 2200;
					

						
							if(  pDph_t->localcnt <= 5 )
							{
								//After a few frames the front palatel shifts to a palatel
								pDph_t->parstochip[OUT_A2] = 2200;
								
							
#ifdef PH_DEBUG
								if(DT_DBG(PH_DBG,0x080))
								{
									FNX_PRINTF(" PALATEL roll start \n ");
									
								}
#endif								
								
							}
							else
									
								
								
								pDph_t->parstochip[OUT_A2] = 2200;	
								
								
						}
						else
						{		
							pDph_t->localcnt = 0;	
								pDph_t->parstochip[OUT_A2] = 2000;
							if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FRETRO)
								pDph_t->parstochip[OUT_A2] = 2123;
							
#ifdef PH_DEBUG
							if(DT_DBG(PH_DBG,0x080))
							{
								FNX_PRINTF(" PALATEL or palatel-alvelar affected so jam A2\n");
							}
#endif
							if(place(pDph_t->allophons[pDph_t->nphone]) & FALVEL )
								//palatel alvelar for Japanese
							{
								pDph_t->parstochip[OUT_A2] = 2500;
							}
						}
						
					}
					else
						pDph_t->localcnt = 0;
				}
				
				if(pDph_t->allophons[ pDph_t->nphone] == CHP_ZR)
				{
					if(pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]-NF40MS)
					{
						pDph_t->target_b += 10;
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							FNX_PRINTF("in chin zr  ab tar to %d  \n",pDph_t->target_b );
						}		
						
#endif
					}
				}
				if(place(pDph_t->allophons[pDph_t->nphone]) & FALVEL )
				{
					
					//blade not affect so set it open
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" alvelar or alevalr-palate affected so jam A2\n");
					}
#endif
					
					
					
					pDph_t->parstochip[OUT_A2] = 3000;
					
					//new code for voice alvel ie z
					if(phone_feature_2(pDph_t, pDph_t->nphone) & FVOICD)
						pDph_t->parstochip[OUT_A2] = 3000;
					
					
					if(place(pDph_t->allophons[pDph_t->nphone]) & FPALATL )
						//palatel alvelar for Japanese
					{
						pDph_t->parstochip[OUT_A2] = 2500;
					}
					if( pDph_t->allophons[pDph_t->nphone] == USP_DH)
						pDph_t->parstochip[OUT_A2] = 3300;
				}
		}
		//eab if followed by a fricative the release ends up coarticulated to 
		//the new place hence new- 3/14/05 don't coartoc */
		if((/*( place(pDph_t->allophons[pDph_t->nphone - 1]) & FPALATL 
			||*/ place(pDph_t->allophons[pDph_t->nphone - 1]) & FDENTAL 
			|| place(pDph_t->allophons[pDph_t->nphone - 1]) & FALVEL
			|| place(pDph_t->allophons[pDph_t->nphone - 1]) & FLABIAL)
			&&
			//eab if followed by a fricative the release ends up coarticulated to 
			//the new place hence we don't want to carry over the old coart
			(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FOBST))
		{
			/*	&&  (!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FPLOSV))*/
			if ((pDph_t->phonestep < 2 && pDph_t->phonestep<coarticulation)|| pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL)	
				
			{
				pDph_t->parstochip[OUT_A2] = pDph_t->lastthing;
			}
			else
			{
				//delay change in a vowel
				if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSONOR)
					&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST)
					&& pDph_t->phonestep < pDph_t->allodurs[pDph_t->nphone] >>1)
				{
					pDph_t->parstochip[OUT_A2] = pDph_t->lastthing;
				}
				else
					pDph_t->lastthing =0;
			}
		}
		if(pDph_t->parstochip[OUT_A2] >= 1000)
			pDph_t->lastthing = pDph_t->parstochip[OUT_A2];	
	}
	
	
	
				
	if(pDph_t->nphone)
	{
		if( phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSONCON)
		{
			
			if(pDph_t->tcum <= (pDph_t->allodurs[pDph_t->nphone]>>1))
			{
				if(pDph_t->target_ag <pVtm_t->NOM_VOIC_GLOT_AREA+300
					&& (pDph_t->allophons[ pDph_t->nphone] != USP_R))
					//special rules needed for retroflected
				{
					pDph_t->agspeed = 3;
				}
			}
			else
			{
				//worry about when next phone is not voiced..
				if(pDph_t->target_ag > pVtm_t->NOM_VOIC_GLOT_AREA)
					pDph_t->agspeed = 1;
			}
			
			
			if( pDph_t->allophons[pDph_t->nphone] == FP_R
				|| pDph_t->allophons[pDph_t->nphone] == USP_R)
				
			{
				
				pDph_t->parstochip[OUT_A2] = 4000;
				//temp hack fix it
			}
		}
	}
	

	if((pDph_t->allophons[pDph_t->nphone+1] == USP_LL
		|| pDph_t->allophons[pDph_t->nphone+1] == USP_LX)
		&& pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-4)
		&& (!phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSTOP ) )
	{

		if(pDph_t->target_ag > pVtm_t->NOM_VOIC_GLOT_AREA+200)
			pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+200;
	}

	//rule to spread glottis on ll overode vot 
	// if need to add back in it must be an incremental rule

	Do_Nasal( phTTS);
	
	// specifically to help things like z but try to generalize gesture
	// Anticipate changing the area of the glottis from wide open to near-voicing
	// within the last 25% of the current phoneme.
	if( (phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone+1]) & FSON1) && 
		pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone] - 3)
	{
		if(pDph_t->target_ag > pVtm_t->NOM_VOIC_GLOT_AREA+400)
		{
			pDph_t->target_ag -= 100;
		}
		else if(pDph_t->target_ag < pVtm_t->NOM_VOIC_GLOT_AREA)
		{
			pDph_t->target_ag += 100;
		}
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF(" Anticipating fson1 so target_ag = %d glottis  \n",pDph_t->target_ag);
		}
#endif
	}

	if( phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone+1]) & FOBST )
	{
		if( (pDph_t->allophons[ pDph_t->nphone+1] == SPP_BH)
			|| (pDph_t->allophons[ pDph_t->nphone+1] == SPP_DH)
			|| (pDph_t->allophons[ pDph_t->nphone+1] == SPP_GH)
			|| (pDph_t->allophons[ pDph_t->nphone+1] == LAP_BH)
			|| (pDph_t->allophons[ pDph_t->nphone+1] == LAP_DH)
			|| (pDph_t->allophons[ pDph_t->nphone+1] == LAP_GH) )
		{
			// anticipate narrowing the glottis for approximates to prevent aspiration or frication
			pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA;	
		}

		else if((phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD)
			    && !(phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FNASAL))
		{
			if( pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-NF30MS)
				//not greter than half of phon
				&& pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]>>1)
			{
				if(pDph_t->target_ag < pVtm_t->NOM_VOIC_GLOT_AREA+400)
				{
					pDph_t->target_ag += 20;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Anticipating voiced obstruent spread glottis - not in nasal \n");
					}
#endif
				}
			}
		}
		else

		{
			if( pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-NF40MS)
				&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FNASAL ))
			{				
				
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF(" Anticipating an unvoiced obstruent spread glottis sooner  \n");
				}
#endif
				// if spreads too slow with get a voied obstruent
					if(pDph_t->target_ag < pVtm_t->NOM_VOIC_GLOT_AREA+700)
					{
								
						ptmp += 4;
					pDph_t->target_ag += ptmp;
					}


			}
		}
	}
	
	if(phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FOBST )
	{
		if ( (phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone+1]) & FNASAL))
		
		{
			//special rule for nasals following a plosive
		
		
			if( pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-NF50MS))
			{
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF(" Anticipating voicing for a nasal narrow glottis  \n");

				}
#endif
				if(pDph_t->target_ag > pVtm_t->NOM_VOIC_GLOT_AREA+700)
					pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+700;

			}
		}
	
		else if( (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST &&
				 !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FPLOSV) &&
				 phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD &&
				 !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FNASAL)) ||
				 ((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST) &&
				  (phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD) &&
				 !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FPLOSV) &&
				 !(phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD))
				 )
		{
			//non plos obsturent followed by a voiced so anticpate voicing and start closing z
			//glottis if previous obstruent has larger glottal opening
			if(pDph_t->target_ag >= pVtm_t->NOM_VOIC_GLOT_AREA+ 800)
			{
				if( pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-NF15MS) &&				// within 2 frames of the end of this phoneme
					(phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD))		// next phoneme is voiced
				{

					if( pDph_t->allophons[pDph_t->nphone+1] != USP_R && 
						pDph_t->allophons[pDph_t->nphone] != KRP_S )
					{
						if(pDph_t->target_ag > pVtm_t->NOM_VOIC_GLOT_AREA+500)
							pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+500;
						pDph_t->agspeed=1;

						PH_DEBUG_2080_P2(" Anticipating voicing, use high agspeed %d, set target_ag %d \n", 
							pDph_t->agspeed,
							pDph_t->target_ag);
					}
				}
				else
				{
					pDph_t->agspeed=3;
					PH_DEBUG_2080_P1(" Not anticipating voicing, use slow agspeed %d\n", pDph_t->agspeed);
				}
			}
			else if((phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FOBST) 
				&& (phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FSONOR)
				&& (phone_feature_2(pDph_t, pDph_t->nphone-1) & FVOICD)
				&& (phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone-1]) & FOBST)
				&& (phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone-1]) & FPLOSV)
				&& pDph_t->phonestep<4)
			{
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF("voicd obst plosv to Obstr Sonor agspeed = 1\n");
				}
#endif
				pDph_t->agspeed=1;
			}
			else
			{
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF(" Obstr to voiced agspeed = 3\n");
				}
#endif
				pDph_t->agspeed=3;
			}
		}
	}





	// if we're voiced aim for voicng pressure
	//and we're not in beginning silence
	if(phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD
		&& pDph_t->nphone != 0)
	{
		if(pDph_t->pressure <= pVtm_t->NOM_Sub_Pressure)
			pDph_t->pressure +=70;
	}
	if(pDph_t->allophons[ pDph_t->nphone+1] == CHP_NX)
	{
		pDph_t->target_tb = 400 -(200 *pDph_t->phonestep)/pDph_t->allodurs[pDph_t->nphone];
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF(" Target tongue body = %d \n",pDph_t->target_tb );
		}
#endif
	}
	if(0)//pDph_t->allophons[ pDph_t->nphone] == JP_YO
		//&& pDph_t->phonestep > (pDph_t->allodurs[pDph_t->nphone]-6))
		//|| pDph_t->allophons[ pDph_t->nphone+1] == JPP_YC
		//|| pDph_t->allophons[ pDph_t->nphone+1] == JPP_Y
		//|| pDph_t->allophons[ pDph_t->nphone+1] == JPP_Yo)
	{
		pDph_t->in_tbrelease=0;
		//	pDph_t->target_tb = 700 -(600 *(pDph_t->phonestep-(pDph_t->allodurs[pDph_t->nphone]>>1))/(pDph_t->allodurs[pDph_t->nphone]>>1));
		if(pDph_t->target_tb > 125)
			pDph_t->target_tb -= 155;
		else
			pDph_t->target_tb = 100;
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF(" Target tongue body = %d \n",pDph_t->target_tb );
		}
#endif

	}		

	if(pDph_t->allophons[ pDph_t->nphone] == CHP_NX)
	{

		pDph_t->target_tb -= 10;
		if(pDph_t->target_tb  < 0)
			pDph_t->target_tb =0;
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF("nx-slow-close tongue body = %d \n",pDph_t->target_tb );
		}
#endif
	}		


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

	//if(pDph_t->in_tbclosure)
	//{
	//	//if it isn't closed by other means closr it now
	//	pDph_t->target_tb = 0;
	//	pDph_t->tbstep = 0;
	//}
	if(pDph_t->target_tb < pDph_t->area_tb)
	{
		//
		if(pDph_t->area_tb)
		{
			//start shutting blade rapidly
			// must be large enough to not pass through a small area
			pDph_t->area_tb -= 350;
			//and close
			if(pDph_t->area_tb < pDph_t->target_tb )
				pDph_t->area_tb = pDph_t->target_tb;
		}
	}

	else if( pDph_t->target_tb != pDph_t->area_tb ||
			 pDph_t->in_tbrelease == 1)
	{		

		if( pDph_t->in_tbrelease == 1 && 
			pDph_t->area_tb < 1000 &&
			pDph_t->allophons[pDph_t->nphone] != GEN_SIL)
		{
			//	if(pDph_t->tbstep == 1)
			//	pDph_t->area_g = 577;

			if(pDph_t->tbstep == -1)
			{
				pDph_t->tbstep =1;
				pDph_t->target_tb = 120;
				pDph_t->area_tb = 120;
			}

			else if( phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FBURST ||
					 phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FBURST )	// RBM not sure why this was here
			{	
				//plosive release sits stays at fric value until one step after bstep =0
				pDph_t->target_tb = 1000;
				pDph_t->area_tb = tbarea_rel[pDph_t->tbstep];

				if(pDph_t->tbstep <= 9 )
					pDph_t->tbstep++;
				
				PH_DEBUG_2080_P1(" Phone with burst with body_affected so (area_tb=%d)\n",	pDph_t->area_tb);
			}
			else
			{
				if((place(pDph_t->allophons[pDph_t->nphone])) & FVELAR )
				{
					PH_DEBUG_2080(" Affricate release with tongue body so target_tb to pVtm_t->NOM_fric \n");

					pDph_t->target_tb = pVtm_t->NOM_Fricative_Opening;
				}
				else
				{
					PH_DEBUG_2080(" Body Affricate done- end rleease \n");
					pDph_t->target_tb = 1000;
					pDph_t->in_tbrelease = 0;	
				}
			}
		}
		else if((pDph_t->in_tbrelease == 0 || pDph_t->in_tbclosure == 0))
		{
			if (pDph_t->target_tb > pDph_t->area_tb)
			{
				//open the tb slower
				pDph_t->area_tb += ((pDph_t->target_tb - pDph_t->area_tb)>>2);
			}
			else
			{
				//and close it 
				pDph_t->area_tb += ((pDph_t->target_tb - pDph_t->area_tb)>>1);
			}
		}
		if( place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED 
			&& place(pDph_t->allophons[pDph_t->nphone-1]) & FVELAR &&
			pDph_t->allophons[pDph_t->nphone] != SPP_R &&		// Don't coarticulate the spanish r
			pDph_t->allophons[pDph_t->nphone] != LAP_R)
		{
			//if(pDph_t->phonestep < coarticulation)
			//	pDph_t->area_tb = pDph_t->last_area_tb;
		} 
	}

	if (pKsd_t->lang_curr == LANG_korean)	
	{
		if( (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSTOP) IS_PLUS
			&& (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FSTOP) IS_PLUS)
		{
			if(place(pDph_t->allophons[pDph_t->nphone-1]) & FVELAR)
			{
				if(pDph_t->phonestep <  coarticulation)
					pDph_t->area_tb = pDph_t->last_area_tb;
			}
			else if(place(pDph_t->allophons[pDph_t->nphone-1]) & BLADEAFFECTED )
			{
				if(pDph_t->phonestep <  coarticulation)
					pDph_t->area_b = pDph_t->last_area_b;
			}
			else if(place(pDph_t->allophons[pDph_t->nphone-1]) & FLABIAL  )
			{
				if(pDph_t->phonestep <  coarticulation)
					pDph_t->area_l = pDph_t->last_area_l;
			}
		}
	}

					
	//special hack for v french until I talk with ken
	if(pDph_t->allophons[pDph_t->nphone] == FP_V
		&& pDph_t->tcum > (pDph_t->allodurs[pDph_t->nphone]-4))
	{
		pDph_t->target_l += 30;
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
					FNX_PRINTF("Release labial frication\n");
				}
#endif
			}


		}
#ifdef PH_DEBUG

		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF("In labial frication\n");
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
	//FNX_PRINTF("%d tar \n",pDph_t->target_l);
	else if (pDph_t->target_l != pDph_t->area_l)
	{	

		if(pDph_t->in_lrelease == 1 && pDph_t->area_l < 1000)
		{	
			if( phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FBURST ||
				phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FBURST )
			{	//plosive release sits stays at fric value until one step after bstep =0
				if(pDph_t->lstep == -1) //HELPME MGS
				{
					pDph_t->area_l = pVtm_t->NOM_Fricative_Opening;
					pDph_t->lstep =1;
				}
				else
				{
					pDph_t->target_l =1000;
					pDph_t->area_l = area_rel[pDph_t->lstep];
					if(phone_feature_2( pDph_t, pDph_t->nphone) & FVOICD)
						pDph_t->area_l += 50;
					if( pDph_t->allophons[pDph_t->nphone] == SPP_P ||	// No aspiration for SPP_P
						pDph_t->allophons[pDph_t->nphone] == LAP_P )
					{
						pDph_t->area_l = 0;
					}

					if(pDph_t->lstep <= 9 )
						pDph_t->lstep++;
				}

				// If nasal passage is open, close it
				if( pDph_t->nasal_step > 0 )
				{
					pDph_t->nasal_step = 0;
					pDph_t->target_narea = 0;

					PH_DEBUG_2080(" ... close nasal passage (used for voicebar)\n");
				}

				PH_DEBUG_2080_P2(" Phone with burst and lips affected: target_l = %d, area_l = %d\n",
					pDph_t->target_l, 
					pDph_t->area_l);
			}
			else
			{
				if((place(pDph_t->allophons[pDph_t->nphone])) & FLABIAL )
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Affricate release with lips so target_l to pVtm_t->NOM_fric (%d)\n",
							pVtm_t->NOM_Fricative_Opening);
					}
#endif
					pDph_t->area_l = pVtm_t->NOM_Fricative_Opening;
#ifdef PH_DElUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" llade Affricate done- end rleease \n");

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
		
		

		
		
	//need special rules for flaps
	//need a ftap feature for flaapped things
	if( pDph_t->allophons[pDph_t->nphone] == USP_DX ||
		pDph_t->allophons[pDph_t->nphone] == USP_DF)
	{

#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF(" Saw a flaps o flap it \n");
		}
#endif


		//chnage to a 20 ms closure
		if(pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]>>1)
		{
			if(pDph_t->area_flap <= 850)
				pDph_t->area_flap += 500;
			else 
				pDph_t->area_flap =1200;
		}


		else if( pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]>>1)-3 )
		{
			if(pDph_t->area_flap > 0)
			{
				pDph_t->area_flap -= 500;
			}
			else
			{
				pDph_t->area_flap =0;
			}
		}



	}
	else
		pDph_t->area_flap = 1200;
		
		
	if(pDph_t->target_b < pDph_t->area_b)
	{
		//
		if(pDph_t->area_b)
		{
			//and close
			if ((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FNASAL) &&
				(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSTOP) &&
				(phone_feature_2(pDph_t,pDph_t->nphone-1) & FVOICD))
			{
				if (pDph_t->allodurs[pDph_t->nphone]<=3 && pDph_t->area_b > 350)
					pDph_t->area_b-=300;
					
				// if it is a nasal, make the last stiep before close  very small opening to avoid click
				if (pDph_t->area_b <=50)
					pDph_t->area_b = pDph_t->target_b;
				else if (pDph_t->area_b <= 600)
					pDph_t->area_b=50;
				else
				//start shutting blade rapidly
					pDph_t->area_b -= 300;
			}
			else if(pDph_t->area_b <= 600)
				pDph_t->area_b = pDph_t->target_b;
			else
			//start shutting blade rapidly
				pDph_t->area_b -= 300;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF("Closing blade rapidly area_b = %d\n",pDph_t->area_b);
				}
#endif
		}
	}
		
	else if (pDph_t->target_b != pDph_t->area_b
			|| pDph_t->bstep <= -1) // HELPME MGS
	{	
		if(pDph_t->in_brelease == 1 && pDph_t->area_b < 1000)
		{
			if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1])) & FBURST ||
				(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone])) & FBURST	)
			{	//plosive release sits stays at fric value until one step after bstep =0
				if(pDph_t->bstep < 0)// HELPME MGS
				{
					if(pDph_t->bstep < -1)
					{
						pDph_t->area_b = retro[-pDph_t->bstep];
						pDph_t->bstep++;
						pDph_t->target_b = 1000;
					}
					else
					{
						pDph_t->area_b = pVtm_t->NOM_Fricative_Opening;
						pDph_t->bstep =1;
						pDph_t->target_b = 1000;
					}
				}
				else
				{
					if( pDph_t->target_b >= 0 && 
						pDph_t->allophons[pDph_t->nphone] != USP_DH)
						//dh has special opening c0ode
						//blade to blade wnats to stay closed
					{
						if ((pDph_t->allofeats[pDph_t->nphone] & FDUMMY_VOWEL)	)
						{
							pDph_t->area_b = final_area_rel[pDph_t->bstep];
						}
						else
						{
							pDph_t->area_b = barea_rel[pDph_t->bstep];
						}
						if(pDph_t->bstep <=9 )
							pDph_t->bstep++;
					}
					else
						pDph_t->area_b =0;
				}
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF(" Phone with burst with blade affected so area_b = %d\n",
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
						FNX_PRINTF(" Affricate release with blade_affected so target_b to pVtm_t->NOM_fric \n");
					}
#endif
					pDph_t->area_b = pVtm_t->NOM_Fricative_Opening;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Blade Affricate done- end rleease \n");

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
							FNX_PRINTF(" retro \n");

						}
#endif
					}					
				}

				else
#endif	
					if(pDph_t->phonestep == 0 && pDph_t->area_b <  190
						&& pDph_t->allophons[ pDph_t->nphone-1] != JP_R &&
						!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FNASAL))
						pDph_t->area_b = 100;
					else
					{
						// release nasal into voiced slower
						if ((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FNASAL) &&
							(phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD) && 
							!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST))
						{
							if (pDph_t->phonestep == 0)
								pDph_t->area_b=50;
							else
								pDph_t->area_b += ((pDph_t->target_b - pDph_t->area_b)>>1);
						}
						else
						{
							pDph_t->area_b += ((pDph_t->target_b - pDph_t->area_b)>>1);
						}
					}

#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF("releasing blade area_b is %d\n",pDph_t->area_b);
					}
#endif


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
					|| place(pDph_t->allophons[pDph_t->nphone]) & FVELAR)
				{
					if(pDph_t->phonestep < coarticulation)
					{
						pDph_t->area_b = pDph_t->last_area_b;
						//and if previous was a blade fric close it briefly
						if(place(pDph_t->allophons[pDph_t->nphone-1]) & BLADEAFFECTED
							&& pDph_t->area_b < 200 )

						{
							pDph_t->area_b =0;
							pDph_t->target_b = 100;
#ifdef PH_DEBUG					
							if(DT_DBG(PH_DBG,0x080))
							{
								FNX_PRINTF(" Coarticulating  previous was a blade fric close blade temporarily \n");

							}
#endif
						}
					}
					else
					{
						/// Ed needs to add a better frication rule
						///							pDph_t->area_b =300;
					}
					pDph_t->target_b = 1000;

				}
		}

		if (pDph_t->area_b > 1000)
			pDph_t->area_b= 1000; //safety code eventually eliminate
	}
	if( place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED
		|| place(pDph_t->allophons[pDph_t->nphone+1]) & BLADEAFFECTED)
		if	(phone_feature( pDph_t, pDph_t->allophons[ pDph_t->nphone]) & FSTOP
							&& ( pDph_t->allophons[pDph_t->nphone+1] == USP_DH
							|| pDph_t->allophons[pDph_t->nphone+1] == USP_TH
							 || pDph_t->allophons[pDph_t->nphone+1] == UKP_DH
							|| pDph_t->allophons[pDph_t->nphone+1] == UKP_TH))
					if( pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]-2)
					{
						pDph_t->area_b = 0;
					}




	// if however we're doing a baldeaffected delay open to allow closure
	if(place(pDph_t->allophons[pDph_t->nphone-1]) & BLADEAFFECTED 
		&& (phone_feature( pDph_t, pDph_t->allophons[ pDph_t->nphone]) & FOBST)
		&& !(phone_feature_2( pDph_t, pDph_t->nphone) & FVOICD)
		&& pDph_t->nphone !=0)
	{
		if(pDph_t->phonestep <  (coarticulation-coart_transtime))
		{
			pDph_t->area_b = pDph_t->last_area_b;
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF("COARTICULATING THE BLADE  area_b=%d\n",pDph_t->area_b);
			}
#endif		
		}
		else if (pDph_t->phonestep <  coarticulation)
		{
			//pDph_t->area_b += ((pDph_t->target_b - pDph_t->area_b)>>1);
			pDph_t->area_b = pDph_t->target_b ;
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF("COARTICULATING THE BLADE slower transision area_b=%d\n",pDph_t->area_b);
			}
#endif		
		}

	}



	if( pDph_t->allophons[pDph_t->nphone] == USP_DH
			|| pDph_t->allophons[pDph_t->nphone] == USP_TH
			|| pDph_t->allophons[pDph_t->nphone] == USP_DZ
			|| pDph_t->allophons[pDph_t->nphone] == UKP_DH
			|| pDph_t->allophons[pDph_t->nphone] == UKP_TH
			|| pDph_t->allophons[pDph_t->nphone] == UKP_DZ)

	{
		if(pDph_t->target_ag <= 400)
			pDph_t->target_ap += 100;
		/*	|| pDph_t->allophons[pDph_t->nphone] == USP_DZ )*/
		//((pDph_t->allofeats[pDph_t->nphone] & FBOUNDARY) < FWBNEXT)
		//Post processsing rule to add special closure REF 1000
		//eab aug 30 but not is previous was a stop except for a nasal
		/*&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FSTOP*/
		//if ( phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FNASAL)
		///eab need better rule
		if(1)//(pDph_t->allofeats[pDph_t->nphone] & FBOUNDARY) >= FCBNEXT)
		{
			if( pDph_t->allophons[pDph_t->nphone] == USP_DH )
				tmp = 6;
			else
				tmp=9;
			if(pDph_t->allophons[pDph_t->nphone+1] == GEN_SIL)
				tmp = pDph_t->allodurs[pDph_t->nphone]; 
			if( pDph_t->allophons[pDph_t->nphone] == USP_DH
				|| pDph_t->allophons[pDph_t->nphone] == UKP_TH)

				if (pDph_t->phonestep <  (pDph_t->allodurs[pDph_t->nphone]-tmp))
				{
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Do a closure for dh ot th   \n");
					}
#endif
					//test
					pDph_t->target_b= 0;

					//too fast causes click
					//pDph_t->area_b= 0;			
				}
				else
				{
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" start dh frication   \n");
					}
#endif
					//pDph_t->in_brelease = 1;
					//	if((pDph_t->allofeats[pDph_t->nphone] & FBOUNDARY) >= FWBNEXT)
					if(pDph_t->allophons[pDph_t->nphone+1] == GEN_SIL)
						pDph_t->target_b  = pVtm_t->NOM_Fricative_Opening;
				}
		}
		else
			pDph_t->target_b  = pVtm_t->NOM_Fricative_Opening ;

		pDph_t->target_ap = 500;
	}
			
			
			//if(pDph_t->allophons[pDph_t->nphone] == USP_Z
	if(phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone+1]) & FOBST 
		&& (phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone+1]) & FCONSON)
		&& phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD
			&& pDph_t->allophons[pDph_t->nphone+2] == GEN_SIL
			&& pDph_t->tcum >=7)
			{
					
					
						//set a2 for next cons 
				if(place(pDph_t->allophons[pDph_t->nphone+1]) & FLABIAL
					|| (place(pDph_t->allophons[pDph_t->nphone+1]) & FDENTAL ))
						pDph_t->parstochip[OUT_A2] = 1300;
				else if((place(pDph_t->allophons[pDph_t->nphone+1])) & FLABIAL )
						pDph_t->parstochip[OUT_A2] = 1300;
				else if((place(pDph_t->allophons[pDph_t->nphone+1])) & FALVEL)
						pDph_t->parstochip[OUT_A2] = 3000;
				else if((place(pDph_t->allophons[pDph_t->nphone+1])) & FPALATL )
						pDph_t->parstochip[OUT_A2] = 2500;


					//	FNX_PRINTF(" 1 target_ag %d \n",pDph_t->target_ag);
			}

		if(phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone+1]) & FOBST 
		&& (phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone+1]) & FCONSON)
		&& phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD
		// dont' anticipate an affricate
		&& !(phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone+1]) & FBURST)
		&& pDph_t->allophons[pDph_t->nphone+2] == GEN_SIL )
		if( pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]-6)
				{
					
					if(pDph_t->target_b >= 300)
						pDph_t->target_b -= 100;
					
					if(pDph_t->target_b >= 150)
						pDph_t->target_b -= 50;
					
				
					pDph_t->target_ag = 1000;
					pDph_t->target_ap = 500;
					pDph_t->agspeed = 3;
					if(pDph_t->dcstep == 0)
					{
						pDph_t->dcstep=1;
						pDph_t->uestep=1;
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
						{
							FNX_PRINTF(" Anticipating voiced obstrUENT by starting ue  \n");
						}
#endif


					}
			//	FNX_PRINTF(" 2 target_ag %d  ag %d \n",pDph_t->target_ag,pDph_t->area_g);
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" anticipating voiced obst at end of phone \n");
						
					}
#endif
				}


			
			/* SPecial rule to spread te glottis for the french schwa */
			//EAB june 19. 2001
			
			if(pDph_t->allophons[pDph_t->nphone] == FP_AP)
			{
				//spread the glottis for AP at the very end of the phoneme return it to nominal
				if( pDph_t->tcum <= pDph_t->allodurs[pDph_t->nphone]>>1)
				{
					if(pDph_t->delta_a_forap <= 500)
						pDph_t->delta_a_forap += 250;
				}
				if( pDph_t->tcum <= pDph_t->allodurs[pDph_t->nphone]- 2)
					if(pDph_t->delta_a_forap >= 250)
						pDph_t->delta_a_forap -= 250;
			}
			//need to also delay start of fall til part way into stressed vowel	
			if(pDph_t->allofeats[pDph_t->nphone] & FHAT_ENDS)
//				&& (pDph_t->nallotot - pDph_t->nphone) <= 10)
			
				pDph_t->in_phrase_final =1;
			
#ifndef ODED 			
#ifndef TOMBUCHLER 
			if(  pDph_t->nphone  >= pDph_t->last_sonorant
				&& pDph_t->last_sonorant > 1
				&& pDph_t->nphone > (pDph_t->nallotot -7)
				&& !((phone_feature(pDph_t,pDph_t->allophons[pDph_t->last_sonorant])) & FNASAL
			 &&	(phone_feature(pDph_t,pDph_t->allophons[pDph_t->last_sonorant])) & FSTOP ))
			{
				if(pDph_t->delta_area_g < 1900)
				{
				if(phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FOBST 
				&& (phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FCONSON)
				&& phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD )

					pDph_t->delta_area_g +=  (pVtm_t->EndOfPhrase_Spread * 3)>>3;
				else
					pDph_t->delta_area_g +=  pVtm_t->EndOfPhrase_Spread>>1;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Spreading  glotis at final sonorant area_g value %d and pressure_droping also %d target %d\n",pDph_t->area_g,pDph_t->pressure_drop,pDph_t->target_ag);
						
					}
#endif
				}
			}
			else
				//reset delta_area_g
#endif
#else
	if(  pDph_t->nphone  > pDph_t->last_sonorant)
			{
//if( pDphsettar->nframb >  (pDph_t->tcumdur-5)
//						&& (pDph_t->tcumdur > 5)
{
				if(pDph_t->delta_area_g < 1900)
				{
					
					pDph_t->delta_area_g +=  pVtm_t->EndOfPhrase_Spread>>1;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Spreading citing glotis at final sonorant delta value %d and pressure_droping also %d target %d\n",pDph_t->delta_area_g,pDph_t->pressure_drop,pDph_t->target_ag);
						
					}
#endif
				}				
			}
	}			
	else
				//reset delta_area_g


#endif//oded
	{
		//don't reset on dummy
		if(pDph_t->nphone == 0)
			pDph_t->delta_area_g = 0;
	}
					
	if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSYLL)
	{
		if( !(pKsd_t->lang_curr == LANG_chinese || 
			  pKsd_t->lang_curr == LANG_japanese ||
			  pKsd_t->lang_curr == LANG_korean))
		{
			if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSYLL)
			{
				//LAST BOUNDARY ISSUE NEEDS FIXING IT'S LOCATION IS NOT DEFINITIVE
				if(((pDph_t->allofeats[pDph_t->nphone] & FBOUNDARY) >= FCBNEXT)
					&& pDph_t->syl_pressure == 0)
				{
					value=0;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
						FNX_PRINTF("I'm seeing the last boundary %d \n",pDph_t->nphone );
#endif			
					//note problem when number real phones == 2 it starts at the 
					//beginning of the first phone hence low pressure.

					if(pDph_t->syl_pressure == 0
						&& pDph_t->nphone+2 <= pDph_t->nallotot )
					{
						if(pDph_t->allofeats[pDph_t->nallotot-2 ] & FDUMMY_VOWEL )
						{

							value = (pDph_t->allodurs[pDph_t->nallotot-2])+
								(pDph_t->allodurs[pDph_t->nallotot-3]);

							pDph_t->last_real_phon = pDph_t->nallotot-3;

							//note fdummy gets added later so only nallotot gets incremented
						}
						else
						{
							if(pDph_t->last_real_phon != pDph_t->nphone)
								value=	pDph_t->allodurs[pDph_t->last_real_phon];

							pDph_t->last_real_phon = pDph_t->nallotot-2;
						}

						//add in the vowel
						value += pDph_t->allodurs[pDph_t->nphone];				
						if(pDph_t->last_real_phon > pDph_t->nphone +1)
						{
							//intermediate phoneme
							value += pDph_t->allodurs[pDph_t->nphone +1];
						}
						if( pDph_t->syl_pressure == 0 &&
							pDphsettar->nframb > 9 )
						{
							if(phone_feature(pDph_t, pDph_t->allophons[pDph_t->last_real_phon ]) & FOBST)		// last phoneme is an obstruent
								// nframb for short words needs pressure to ramp u
							{
								//research by slifka 
								if(phone_feature_2(pDph_t, pDph_t->last_real_phon ) & FVOICD)	// last phoneme is a voiced obstruent
								{
									if(phone_feature(pDph_t, pDph_t->allophons[pDph_t->last_real_phon ]) & (FOBST+FCONSON)
										&& !(phone_feature(pDph_t, pDph_t->allophons[pDph_t->last_real_phon ]) & FSTOP))
										pDph_t->syl_pressure = (((pDph_t->pressure) - 650)/(value));
									else

										pDph_t->syl_pressure = (((pDph_t->pressure) - 400)/(value));
								}
								else
								{
									if(phone_feature(pDph_t, pDph_t->allophons[pDph_t->last_real_phon ]) & FSTOP)
										//plosive release
										pDph_t->syl_pressure = (((pDph_t->pressure) -600)/(value));
									else
										pDph_t->syl_pressure = (((pDph_t->pressure) -500)/(value));
								}
							}
							else	// !FOBST
							{
								pDph_t->syl_pressure = (((pDph_t->pressure) -350)/(value));
							}
						}
					}

#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						//if(pDph_t->syl_pressure > 0)
						FNX_PRINTF("Pressure drop from last syl set to per frame %d  \n", pDph_t->syl_pressure);
					}
#endif
					if( pDphsettar->nframb >  (pDph_t->tcumdur-15)
						&& (pDph_t->tcumdur > 15))	
					{	
						//REALLY START DROPPING AT 100 MS FROM END OF LAST PHONEME
						//unless dummy release vowel and then sooner
						if ( pDph_t->nphone ==  pDph_t->nallotot-1)
						{
							if( pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]-50/*NF80MS*/)
							{
								if(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FOBST)
								{
									if (pDph_t->pressure_drop < 2000)
										pDph_t->pressure_drop += 18;
#ifdef PH_DEBUG
									if(DT_DBG(PH_DBG,0x080))
									{
										FNX_PRINTF(" last drop  \n");
									}
#endif
								}
								else
								{
									if(pDph_t->pressure_drop < 3000
										&& !(phone_feature_2( pDph_t, ( pDph_t->nphone)) & FVOICD))
									{
										if (pDph_t->pressure_drop < 1000)
											pDph_t->pressure_drop += 15;
#ifdef PH_DEBUG
										if(DT_DBG(PH_DBG,0x080))
										{
											FNX_PRINTF(" Pressure drop for voiced  \n");
										}
#endif
									}
								}
							}
						}
					}
				}	// Last Boundary
			}
		}
	}
	
		if(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL)
		{
			if (phone_feature_2( pDph_t, pDph_t->nphone-1) & FVOICD)
			{
					pDph_t->pressure_drop += 50;
			}
			else
			{
					pDph_t->pressure_drop += 30;
			}
		}
#ifdef ODED
	
			if((phone_feature( pDph_t, pDph_t->allophons[ pDph_t->nphone])) & FSTOP)
			if(!(phone_feature( pDph_t, pDph_t->allophons[ pDph_t->nphone])) & FBURST	)
			{
				if( pDph_t->nphone >= 3)			

					pDph_t->pressure_drop +=60;
			}
			else
			{
				if( pDph_t->nphone >= 3
				&& pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]-5)			

					pDph_t->pressure_drop +=20;
				
			}
		if(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL)
					pDph_t->pressure_drop -=100;


	
#endif

				if( pDphsettar->nframb <= 1)
				{
					//Initialize at the begiining
					pDph_t->delta_area_g = 0;
				}
#ifdef ODED
	
			if((phone_feature( pDph_t, pDph_t->allophons[ pDph_t->nphone])) & FSTOP)
			if(!(phone_feature( pDph_t, pDph_t->allophons[ pDph_t->nphone])) & FBURST	)
			{
				if( pDph_t->nphone >= 3)			

					pDph_t->pressure_drop +=60;
			}
			else
			{
				if( pDph_t->nphone >= 3
				&& pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]-5)			

					pDph_t->pressure_drop +=20;
				
			}
		if(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL)
					pDph_t->pressure_drop +=100;


	
#else
				if( pDph_t->syl_pressure != 0)
				{
					pDph_t->pressure_drop += pDph_t->syl_pressure;
					//FNX_PRINTF("xxxxxxxxxxxxxxxxPressure drop from last syl %d to %d at %d \n",
					//	pDph_t->syl_pressure,pDph_t->pressure_drop, pDphsettar->nframb);
				}
#endif
				
				
				if(pDph_t->allophons[pDph_t->nphone] == GRP_Q)
				{
					
					if( pDph_t->tcum <= pDph_t->allodurs[pDph_t->nphone]>>1)
					{
						if (pDph_t->delta_area_gstop <=200)
						{
							pDph_t->delta_area_gstop += 200;
						}
					}
					else if( pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]-3)
					{
						if (pDph_t->delta_area_gstop >= 200)
						{
							pDph_t->delta_area_gstop -= 200;
						}
					}
				}
				
				else
					pDph_t->delta_area_gstop =0;
				
				
				
				if((phone_feature_2(pDph_t,pDph_t->nphone-1) & FVOICD))
				{
					if(place(pDph_t->allophons[pDph_t->nphone-1]) & FGLOTTAL)
					{
						
						
						//if( pDph_t->tcum > pDph_t->allodurs[pDph_t->nphone]-3)
						
#ifdef PH_DEBUG
							if(DT_DBG(PH_DBG,0x080))
							{
								FNX_PRINTF(" glottalized obstruent release slowly \n");
							}
#endif	
							//release glottal gesture slowly
							pDph_t->agspeed = 2;
						
						}
					
					
				}
				
				
				if((pDph_t->allophons[pDph_t->nphone] == FP_R))
				{
					
					//set ue and dc to zero need to set dctep as well or it will jump
					//after the r as dc will be set
					pDph_t->dcstep = 0;
					pDph_t->parstochip[OUT_DC] = 0;
					pDph_t->parstochip[OUT_UE] = 0;
					
					if( !(phone_feature_2(pDph_t,pDph_t->nphone-1) & FVOICD))
					{
						//	pDph_t->area_g = pVtm_t->NOM_UNVOICED_SON;
						pDph_t->target_ag = pVtm_t->NOM_UNVOICED_SON;
						pDph_t->agspeed = 3;
					}
					else
					{

						pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+800;
						pDph_t->agspeed = 3;
					}
				}
				if(! (pKsd_t->lang_curr == LANG_japanese))
				{
					
					if (pKsd_t->lang_curr == LANG_chinese)
					{
						if( (pDph_t ->allofeats[pDph_t->nphone] & FSTRESS) == FSTRESS_2)
						{
							if(pDph_t->target_ag < pVtm_t->NOM_UNSTRESSED_VOWEL)
								//the if is needed to make it wait for end of vot
							{
#ifdef PH_DEBUG
								if(DT_DBG(PH_DBG,0x080))
								{
									FNX_PRINTF("spread glottis for S2 phonemse in Chinese \n");
								}
#endif
							pDph_t->target_ag = 900;       // Ed: 1100
							}
						}
						//eab remove glotttal rule as it essentially overroad all other glotttal rules.
						
					}
					else        // following clause applies for non chinese (Reiner)
					{
						
						if(!(pDph_t->allofeats[pDph_t->nphone] & FSTRESS)
							&& (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSYLL))
						{
							if(!(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL))
							{
								//spread glottis for unstressed vowels
								
								if(pDph_t->tcum == np->tspesh)
									//the if is needed to make it wait for end of vot
								{
									pDph_t->target_ag = pVtm_t->NOM_UNSTRESSED_VOWEL;
									
#ifdef PH_DEBUG
									if(DT_DBG(PH_DBG,0x080))
									{
										FNX_PRINTF("spread glottis for unstressed phonemes target %d  \n",pDph_t->target_ag);
									}
#endif
									
								}
							}
							
							
						}
					}
				}
				
				
			
#ifdef HLSYN		
				if( pDph_t->parstochip[OUT_PS] <= pVtm_t->NOM_Sub_Pressure -400 && 
					pDph_t->nphone > 1 )
				{
					if( pDphsettar->diplo <= 100- pDphsettar->diplo_step)
					{
						pDphsettar->diplo += pDphsettar->diplo_step ;
					}
				}
				
				else
				{
					pDphsettar->diplo =0;
				}
				
			pDph_t->parstochip[OUT_DP] = pDphsettar->diplo;

#else
		pDph_t->parstochip[OUT_DP] = 0;
#endif
		if( pKsd_t->lang_curr == LANG_french &&	
			(phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone])) & FBURST && 
			(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone])) & FSTOP )
		{
			if (pDph_t->phonestep ==  (pDph_t->allodurs[pDph_t->nphone]-1))
				pDph_t->agspeed =3;
			else if(pDph_t->phonestep >  (pDph_t->allodurs[pDph_t->nphone]-6))
			{
				if(!(phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD))
					if(pDph_t->area_g > 900)
						//basically shut it quickly here
						pDph_t->area_g = 900;
				pDph_t->agspeed =1;
				pDph_t->target_ag =0;
			}
	
		
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF(" Target of  glottis at stop %d .\n",pDph_t->target_ag);
			}
#endif
		}
		//here
		if (pDph_t->target_ag <= pVtm_t->NOM_VOIC_GLOT_AREA+200)
			pDph_t->target_ag += pDph_t->delta_a_forap;

		if(pKsd_t->sprate >= 350)		// ADD IN FOR HIGH SPEED 
			 pDph_t->agspeed =1;
				
		if( ((pDph_t->target_ag - pDph_t->area_g)>>pDph_t->agspeed) > 350)
			pDph_t->area_g += 250;
		else if( ((pDph_t->target_ag - pDph_t->area_g)) < -900 )
			pDph_t->area_g -= 600;
		else
		{
			if(pDph_t->target_ag == 0 && ((pDph_t->target_ag - pDph_t->area_g)>>pDph_t->agspeed) > -15)
				pDph_t->area_g = 0;
			pDph_t->area_g += ((pDph_t->target_ag - pDph_t->area_g)>>pDph_t->agspeed);
		}
		
				
		if(pDph_t->in_lrelease || pDph_t->in_tbrelease || pDph_t->in_brelease)
		{
			if( pDph_t->allophons[pDph_t->nphone] != GEN_SIL )
			{
				if(pDph_t->had_burst == 0)
				{
					pDph_t->had_burst =1;

					if(pDph_t->in_tbrelease )
						pDph_t->parstochip[OUT_BRST] = 1;
					else
						//stronger for labial or blade
						pDph_t->parstochip[OUT_BRST] = 2;
				}
				else
					pDph_t->parstochip[OUT_BRST] = 0;
			}		
		}
		else if(pDph_t->parstochip[OUT_BRST] >= 0)
		{
			pDph_t->had_burst = 0;
			pDph_t->parstochip[OUT_BRST] = 0;
		}
		else
		{
			//allows special case like th to set a burst
			pDph_t->parstochip[OUT_BRST]=1;
		}

					
		if( (pDph_t->nphone == 1 && phone_feature(pDph_t,pDph_t->allophons[1]) & FSYLL) IS_PLUS)
		{
			if(pDph_t->phonestep == 0)
			{
				pDph_t->parstochip[OUT_BR] = pDph_t->vowel_start_burst = 60;
				//pDph_t->parstochip[OUT_BR] += 10;
			}
			else
			{
				if( pDph_t->vowel_start_burst >0)
				{
					pDph_t->vowel_start_burst -= 20;
				}
				if( pDph_t->vowel_start_burst <0)
					pDph_t->vowel_start_burst =0;
			}
			pDph_t->parstochip[OUT_BR] = pDph_t->vowel_start_burst;
		}
		else
			pDph_t->parstochip[OUT_BR] = 0;

		pDph_t->area_ap += ((pDph_t->target_ap - pDph_t->area_ap)>>2);
		pDph_t->parstochip[OUT_CNK] = pDph_t->area_ap + pVtm_t->NOM_Area_Chink;
		tmp = pDph_t->area_g + pDph_t->delta_area_g - pDph_t->delta_area_gstop;
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
			// This prevents a full closure for intervocalic-nasals
			if( (pKsd_t->lang_curr == LANG_korean || 
				 pKsd_t->lang_curr == LANG_spanish || 
				 pKsd_t->lang_curr == LANG_latin_american) &&
				 pDph_t->nphone > 0 &&
				(phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone-1]) & FSONOR) &&
				(phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone]) & FNASAL) &&
				(phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone+1]) & FSONOR) &&
				pDph_t->area_b < 20 )
			{
				pDph_t->area_b = 20;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
					FNX_PRINTF(" nasal approximate: blade to %d\n", pDph_t->area_b);
#endif
			}

			pDph_t->parstochip[OUT_ABLADE] = pDph_t->area_b;
		}
		pDph_t->parstochip[OUT_ATB] = pDph_t->area_tb;
				
		//	FNX_PRINTF(" %d \n",pDph_t->area_b);

		if(pDph_t->allophons[pDph_t->nphone] == GRP_KH
			|| pDph_t->allophons[pDph_t->nphone] == SPP_J
			|| pDph_t->allophons[pDph_t->nphone] == LAP_J)
		{
			pDph_t->parstochip[OUT_PLACE] = 80;
		}
		else if(pDph_t->allophons[pDph_t->nphone] == GRP_CH)
		{
			pDph_t->parstochip[OUT_PLACE] = 45;
		}
		else if(place(pDph_t->allophons[pDph_t->nphone]) & FVELAR )
			//although y is considered an cons in this case it acts like a vowel.
			//need to research how to handle this in general this is just a hack fix for the release
		{
			if( pDph_t->allophons[pDph_t->nphone+1] == LAP_Y || 
				pDph_t->allophons[pDph_t->nphone+1] == SPP_Y)
			{
				pDph_t->parstochip[OUT_PLACE] = 45;
			}
			else if(place(pDph_t->allophons[pDph_t->nphone]) & FVELARR)
				pDph_t->parstochip[OUT_PLACE] = 46;
			else
			{
				switch (begtyp(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) )

				{
				case 1:
					if (pKsd_t->lang_curr == LANG_chinese)
					{
						pDph_t->parstochip[OUT_PLACE] = 42;
					}
					else
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
#ifdef INTEGER
//				short tmp1;
				tmp =0;

				if((pDph_t->area_l >= 150 && pDph_t->area_b >= 150 &&
					pDph_t->area_tb >= 150) || pDph_t->area_n > 150
					|| pDph_t->nphone == 0)
				{
					pDph_t->oral_pressure = 00;
				}
				else
				{
					if(pDph_t->oral_pressure < 5500)
					{
						pDph_t->oral_pressure += 1400;
						
					}
				}
				tmp1=300;	

				if(pDph_t->area_l != 0 && pDph_t->area_b != 0 &&
					pDph_t->area_tb != 0 )
				{
					if(pDph_t->area_l < 80)
						tmp1=pDph_t->area_l;
					if(pDph_t->area_b < pDph_t->area_l)
						tmp1= pDph_t->area_b;
					if(pDph_t->area_tb < pDph_t->area_b)
						tmp1 = pDph_t->area_tb; 
					if(tmp1 < 80)
					{
						//for very small araeas reduce the gf
						//for now assume that it's not enough are to
						if(tmp1 <= 10)
							tmp =37;
						else if(tmp1 <= 20)
							tmp =40;
						else if(tmp1 <= 60)
							tmp =47;
						else if(tmp1 <= 80)
							tmp =50;
						
					}
					else
					{
						if((pDph_t->area_l <= 400) && (pDph_t->area_l >= 10))
						{
							tmp = pDph_t->oral_pressure/(pDph_t->area_l);
						}
						if((pDph_t->area_b <= 400) && (pDph_t->area_b >= 10))
						{
							if(tmp < pDph_t->oral_pressure/(pDph_t->area_b))
								tmp = pDph_t->oral_pressure/(pDph_t->area_b);
						}
						if((pDph_t->area_tb <= 400) && (pDph_t->area_tb >= 10))
						{
							if(tmp < pDph_t->oral_pressure/(pDph_t->area_tb));
							tmp = pDph_t->oral_pressure/(pDph_t->area_tb);
						}
					}
					
				}

				// Maximum value of AF (in db) for a given inter oral pressure
				if(tmp > 57)
					tmp=57;

				if((pDph_t->area_g + pDph_t->delta_area_gst - pDph_t->delta_area_gstop)< 1200)
				{
					//if the total glotal area is less 1200 reduce level of
					//fric for voiced obstruent
					tmp -= 5;
					if((pDph_t->area_l <= 150 || pDph_t->area_b <= 150 || pDph_t->area_tb <= 150) && 
						pDph_t->area_n < 100)
					{
						pDph_t->av_reduction += 4;
					}
					else
						pDph_t->av_reduction =0;
				
					pDph_t->parstochip[OUT_AV] -= pDph_t->av_reduction;
					if(pDph_t->parstochip[OUT_AV] < 0 )
						pDph_t->parstochip[OUT_AV] =0;
				}

				if(tmp == 0)
				{
					pDph_t->parstochip[OUT_GF] -= (pDph_t->parstochip[OUT_GF]>>2) ;
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

				//	FNX_PRINTF(" av %d \n ", pDph_t->parstochip[OUT_AV]);
#ifdef ITHINKITSREDUNDANTATMOEMNT
				if(pDph_t->parstochip[OUT_AV] > 30)
				{
					tmp =(pDph_t->area_g + pDph_t->delta_area_gst - pDph_t->delta_area_gstop);
					tmp = ((tmp-400)>>6);
					if(tmp < 0 )
						tmp=0;
					pDph_t->parstochip[OUT_AV] -= tmp;
					if(	pDph_t->parstochip[OUT_AV] < 0 )
						pDph_t->parstochip[OUT_AV] =0;
				}
#endif //redudndant
#endif //Integer
						//FNX_PRINTF(" tmp %d av2 %d \n ", tmp, pDph_t->parstochip[OUT_AV]);
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
					tmp =  pDph_t->pressure - (pDph_t->pressure_drop + pDph_t->stress_pulse);
					//FNX_PRINTF(" %d %d %d %d  hi \n",tmp,pDph_t->pressure , pDph_t->pressure_drop , pDph_t->stress_pulse);
					tmp -= pDph_t->pressure_gest;
					if(pDph_t->nphone >=1)
					{
						tmp += pDph_t->pressure_burst;
						if(pDph_t->pressure_burst != 0)
							if(((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone])) & FSYLL) IS_PLUS)
							{
								if(pDph_t->pressure_burst > 0)
									pDph_t->pressure_burst -=50;
								else
									pDph_t->pressure_burst =0;
					}
					}
				//	FNX_PRINTF("%d pburst %d %d %d \n",pDph_t->pressure, pDph_t->pressure_burst,tmp, pDph_t->nphone);
#endif

					if(tmp < 100 && pDph_t->nphone > 1
						|| tmp <0)
					{	
						
						pDph_t->pressure = 0;
						tmp =0;
					}	
					
					pDph_t->parstochip[OUT_F4] = pDph_t->curspdef[SPD_F4];
					
					pDph_t->parstochip[OUT_PS] = tmp;
					
					pDph_t->parstochip[OUT_AN] = pDph_t->area_n;
					
				//	pDph_t->parstochip[OUT_FZ]  = 500;
				//	pDph_t->parstochip[OUT_FNP] = 500;


					
					pDph_t->lastf1 = pDph_t->parstochip[OUT_F1];
				
				
					if( pDph_t->lasta2 > 500 && pDph_t->phonestep < coarticulation)
					{
#ifdef PH_DEBUG
						if(DT_DBG(PH_DBG,0x080))
							FNX_PRINTF("Coarticulating A2 = %d\n",pDph_t->lasta2);
#endif
						//last thing was marked 
						//but if this one is too don't change it
						if(pDph_t->parstochip[OUT_A2] == 0)
							pDph_t->parstochip[OUT_A2] = pDph_t->lasta2;
					//	FNX_PRINTF(" %d %d \n", pDph_t->parstochip[OUT_A2],pDph_t->phonestep );
					}


					pDph_t->lasta2 = pDph_t->parstochip[OUT_A2];
					pDph_t->nphonelast = pDph_t->nphone;
					
#endif //hlsyn
#endif //HLSYN
		
					
					/* Compensate for loudness decrease when strongly tilted */
					if (pDph_t->parstochip[OUT_AV] > 3)
					{
						temptilt = (*parp >> 2) - 4;
						if (temptilt < 0)
							temptilt = 0;			   /* tilt must be 20 or more */
						pDph_t->parstochip[OUT_AV] += temptilt;
						
						
					}
					
					
					
					
					/* eab 6/25/98 cleanup*/
					//EAB		7/13/98			BATS 711 
					/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
					/* if current phone is uvular /RR/, modulate several parameters      */
					/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
					/* EAB boolean true false in r_mod simply defines whether we're done and it's
					time to increment the counter*/
					
#ifdef INTEGER
					if( pDph_t->allophons[pDph_t->nphone] == SPP_J ||
						pDph_t->allophons[pDph_t->nphone] == LAP_J )
					{
						r_modulation (phTTS,pDph_t->param[A2].outp, N10PRCNT, TRUE);
					}
#endif
					if (pDph_t->allophons[ pDph_t->nphone] == GRP_KH)
					{
						
						r_modulation (phTTS,pDph_t->param[TONGUEBODY].outp, N50PRCNT, TRUE);

					}
					
					else if( pDph_t->allophons[ pDph_t->nphone] == GRP_RR )
					{
#ifdef HLSYN						
						// close tongue body and then modulate my zero mass tongue body 
						pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+300;
						//since we're man handling the AREA SET THE TARGET
						//for to open after we're through
						pDph_t->target_tb = 1000;
						pDph_t->parstochip[OUT_ATB] = 500;
						pDph_t->agspeed = 1;
						if (pDph_t->allophons[ pDph_t->nphone] == GRP_RR)
							//hack for 5.0 release fix it prettier later
						{
							if( phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone-1)]) & FVOWEL )
							{
								gr_modulation (phTTS,&pDph_t->parstochip[OUT_ATB], N80PRCNT, TRUE);
							}
							else
							{	
								gr_modulation (phTTS,&pDph_t->parstochip[OUT_ATB], N80PRCNT, TRUE);
							}
						}
						else
						{
							pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+1000;
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
							r_modulation (phTTS, pDph_t->param[A2].outp, N10PRCNT, FALSE);
							r_modulation (phTTS,pDph_t->param[A3].outp, N10PRCNT, TRUE);
						}
#endif
						
						
					}
					//	else
					//		/* Initialiatize the modulation counter eab 2/6/98*/
					//		pDph_t->modulcount =0;
					
				
					if ( pDph_t->allophons[ pDph_t->nphone] == ITP_RR)
					{
						if(pDph_t->modulcount <=7)
						{	
							
#if (defined HLSYN ) 
							if(!(phone_feature_2(pDph_t,pDph_t->nphone-1) & FVOICD))
							{
								pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+700;
							}
							
							pDph_t->parstochip[OUT_AG] = 900;
							//tr blend is a hack at the moment
							pDph_t->parstochip[OUT_A2] = 2100;
							rs_modulation (phTTS,pDph_t->param[AREAB].outp, N90PRCNT, TRUE);
							
#else
							//	rit_modulation (phTTS,pDph_t->param[A2].outp, N10PRCNT, FALSE);
							//a2 is an index into tables for non_hlsyn don't modulate it
							//	rit_modulation (phTTS,pDph_t->param[A3].outp, N20PRCNT, FALSE);
							//if av isn't one yet due to plosive wait
							if(*pDph_t->param[AV].outp >30)
								r_modulation (phTTS,pDph_t->param[AV].outp, N50PRCNT, TRUE);
#endif
						}
						
						
						
					}

					else if ( pDph_t->allophons[ pDph_t->nphone] == JP_R)
					{
						if(pDph_t->modulcount <=7)
						{
#if (defined HLSYN ) 
							pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+100;
							
							pDph_t->parstochip[OUT_A2] = 2100;
							pDph_t->parstochip[OUT_ABLADE] = 1000;
							rs_modulation (phTTS,pDph_t->param[AREAB].outp, N95PRCNT, TRUE);
							
#else
							//no A2 it's a pointer			
							//			rs_modulation(phTTS,pDph_t->param[A2].outp, N10PRCNT, FALSE);
							//rs_modulation(phTTS,pDph_t->param[A3].outp, N20PRCNT, FALSE);
							//if av isn't one yet due to plosive wait
							if(*pDph_t->param[AV].outp >30)
								rs_modulation(phTTS,pDph_t->param[AV].outp, N30PRCNT, TRUE);
#endif
						}
					}
					
					else if( pDph_t->allophons[pDph_t->nphone] == SPP_RR || 
							 pDph_t->allophons[pDph_t->nphone] == LAP_RR || 
							 pDph_t->allophons[pDph_t->nphone] == HEP_RR)
					{
						short pwSequence[] = {
							0,0,-N10PRCNT,									// open
							-N50PRCNT,-N90PRCNT,-N50PRCNT,					// close
							-N25PRCNT,-N10PRCNT,-N25PRCNT,					// open
							-N50PRCNT,-N90PRCNT,-N50PRCNT,					// close
							-N25PRCNT,-N10PRCNT,-N25PRCNT,					// open
							-N50PRCNT,-N90PRCNT,-N50PRCNT					// close
						};

#ifdef HLSYN
						// if beginning of word start at index 4 (closed)
						if( pDph_t->nphone > 0 && 
							pDph_t->allophons[pDph_t->nphone-1] == GEN_SIL &&
							pDph_t->smodulcount == 0)
						{
							pDph_t->smodulcount = 4;
						}
						*pDph_t->param[AREAB].outp = 300;	//160;
						pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+100;
						pDph_t->parstochip[OUT_A2] = 2100;

						//r_modulation (phTTS,pDph_t->param[AREAB].outp, N50PRCNT, TRUE);
						ParameterModulation(phTTS, pDph_t->param[AREAB].outp, pwSequence, sizeof(pwSequence)/sizeof(short), TRUE);

#else
						r_modulation (phTTS,pDph_t->param[AV].outp, N20PRCNT, FALSE);
						r_modulation (phTTS,pDph_t->param[A2].outp, N20PRCNT, FALSE);
						r_modulation (phTTS,pDph_t->param[A3].outp, N20PRCNT, TRUE);
#endif
					}

					// Tapped r sound
					else if( pDph_t->allophons[pDph_t->nphone] == LAP_R || 
							 pDph_t->allophons[pDph_t->nphone] == SPP_R || 
							 pDph_t->allophons[pDph_t->nphone] == HEP_R || 
							 pDph_t->allophons[pDph_t->nphone] == ITP_R ||
							 pDph_t->allophons[pDph_t->nphone] == KRP_DF )
					{
						short 
							pwSequence[] = {
							0,0,0,0												// voicing
							-N75PRCNT,-N95PRCNT,-N80PRCNT,							// tap
							-N65PRCNT,0,0,0};												// voicing
						int
							nSeq = sizeof(pwSequence) / sizeof(short);
#if (defined HLSYN ) 

						*pDph_t->param[AREAB].outp = 600;
						pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+100;
						pDph_t->parstochip[OUT_A2] = 2100;

						if( phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone+1]) & FOBST )
						{
							// Move tap to beginning of /r/
							if( pDph_t->smodulcount == 0 )
								pDph_t->smodulcount = 3;

#if 0
							// Move tap to end of /r/
							if( pDph_t->tcum < pDph_t->allodurs[pDph_t->nphone]-5 )
							{
								pDph_t->smodulcount = 0;
							}
							else if( pDph_t->tcum == pDph_t->allodurs[pDph_t->nphone]-5 )
							{
								pDph_t->smodulcount = 4;
							}
#endif
						}

						ParameterModulation(phTTS, pDph_t->param[AREAB].outp, pwSequence, nSeq, 
							pDph_t->smodulcount < nSeq-1 ? TRUE : FALSE);	// Don't increment smodulcount once we hit the end of pwSequence
#else
						//no A2 it's a pointer			
						//rs_modulation(phTTS,pDph_t->param[A2].outp, N10PRCNT, FALSE);
						//rs_modulation(phTTS,pDph_t->param[A3].outp, N20PRCNT, FALSE);
						//if av isn't one yet due to plosive wait
						if(*pDph_t->param[AV].outp >30)
							rs_modulation(phTTS,pDph_t->param[AV].outp, N30PRCNT, TRUE);
#endif
					}
					
					else if( pDphsettar->phcur != SPP_J && 
							 pDphsettar->phcur != LAP_J &&
							 pDphsettar->phcur != UKP_NX)
					{
						pDph_t->smodulcount =0;			// Intialize the modulation counter
					}
						
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

					if(pDphsettar->phcur == UKP_K)
					{
						*pDph_t->param[AREAB].outp =100;
					}


					if(pDph_t->allophons[pDph_t->nphone ] == UKP_NX)
					{
						*pDph_t->param[AREAG].outp = 450;
						r_modulation (phTTS,pDph_t->param[AREAG].outp, N50PRCNT, TRUE);
					}

					if (pDphsettar->phcur == USP_CZ	
						|| pDphsettar->phcur == HEP_CZ)
					{

#ifdef HLSYN
						*pDph_t->param[TONGUEBODY].outp =400;
						pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+1000; //SPECIAL FOR THIS SOUND AT THE MOMENT
						h_modulation (phTTS,pDph_t->param[TONGUEBODY].outp , N90PRCNT, TRUE);
						//	pDph_t->parstochip[OUT_F1] = 270;
						//gr_modulation (phTTS,&pDph_t->parstochip[OUT_F1], N10PRCNT, TRUE);
#else
						*pDph_t->param[AP].outp = 70;
						h_modulation (phTTS,pDph_t->param[AP].outp , N20PRCNT, TRUE);
						*pDph_t->param[AV].outp = 20;
						h_modulation (phTTS,pDph_t->param[AV].outp , N20PRCNT, TRUE);
#endif

					}
						
#ifdef PH_DEBUG

					//FNX_PRINTF(" %d \n",pDph_t->parstochip[OUT_F2]);		
					if(pDph_t->parstochip[OUT_F2] <= 708)
						pDph_t->parstochip[OUT_F2] +=1;
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
						(pDph_t->parstochip[OUT_TLT] < 0 ))
					{
#ifdef PH_DEBUG
						FNX_PRINTF(" ERROR Negative value \n");
#endif
					}
#endif	// PH_DEBUG
									
#ifdef NEW_VTM
					pDph_t->parstochip[OUT_FNP] = 290;

					if(pDph_t->allophons[ pDph_t->nphone] == GRP_R)
					{
						if((phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD) IS_MINUS)
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
						
					if ((pDph_t->allophons[ pDph_t->nphone+1] == GEN_SIL)
						&& (pDph_t->allophons[ pDph_t->nphone] == SPP_IX))
						pDph_t->parstochip[OUT_AV] -=3;

					if ((pDph_t->allophons[ pDph_t->nphone+1] == GEN_SIL)
						&& (pDph_t->allophons[ pDph_t->nphone] == LAP_IX))
						pDph_t->parstochip[OUT_AV] -=3;

#endif
						
#endif /*NEW_VTM*/
						
					/* eab 4/5/98 For 5.0 all languages should do this    */
					/* In a lateral like l av jumps whem mouth and tongue open tract*/
					if(pDph_t->allophons[ pDph_t->nphone] == UKP_LL
						|| pDph_t->allophons[ pDph_t->nphone] == USP_LL
						|| pDph_t->allophons[ pDph_t->nphone] == FP_L
						|| pDph_t->allophons[ pDph_t->nphone] == SPP_L 
						|| pDph_t->allophons[ pDph_t->nphone] == LAP_L 
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
						j=FNX_SPRINTF(outbuf,"phdata%d",pDph_t->PHSwapCnt);
#else
						j=FNX_SPRINTF(outbuf,"hldata%d",pDph_t->PHSwapCnt);
#endif
						j=FNX_SPRINTF(outbuf+j,".out");
						
						
						if (pDph_t->PHSwapIn == NULL && pDph_t->PHSwapOut == NULL)
						{
#ifndef HLSYN
							//pDph_t->PHSwapIn = FNX_FOPEN("phdata.in","rb");
#else
							pDph_t->PHSwapIn = FNX_FOPEN("hldata.in","rb");
#endif
							if(pDph_t->PHSwapIn == NULL)
							{
								pDph_t->PHSwapOut = FNX_FOPEN(outbuf,"wb");
#if !defined HLSYN && defined PH_DEBUG

								FNX_FPRINTF(pDph_t->PHSwapOut," AP   F1   A2   A3   A4   A5   A6   AB  TILT  T0   AV   F2   F3    FZ   B1   B2   B3       \r\n");
#else
							//	FNX_FPRINTF(pDph_t->PHSwapOut," PHON   T0  F1   F2   F3  F4   AG   AL   ATB  ABLADE   AN   CNK  PS    DC   UE   FZ   PLACE  \r\n");
#endif
							}
							
							//                if (pDph_t->PHSwapIn != NULL) 
							//					FNX_FSCANF(pDph_t->PHSwapIn," AP   F1   A2   A3   A4   A5   A6   AB  TILT  T0   AV   F2   F3   FZ   B1   B2   B3\r\n");
						}
#ifndef HLSYN
						if (pDph_t->PHSwapOut != NULL) {
							for (ii = 0; ii < 32; ii++) {
#ifdef PH_DEBUG
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[ii]);
#endif
							}
#ifdef PH_DEBUG
							FNX_FPRINTF(pDph_t->PHSwapOut,"\r\n");
#endif
						}
						
						if (pDph_t->PHSwapIn != NULL) {
							for (ii = 0; ii < 32; ii++) {
								FNX_FSCANF(pDph_t->PHSwapIn,"%4d ",&pDph_t->parstochip[ii]);
							}
							FNX_FSCANF(pDph_t->PHSwapIn,"\r\n");
							if (FNX_FEOF(pDph_t->PHSwapIn)) {
								FNX_FCLOSE(pDph_t->PHSwapIn);
								pDph_t->PHSwapIn = FNX_FOPEN("phdata.in","rb");
								FNX_FSCANF(pDph_t->PHSwapIn," PH   T0	F1   F2   F3   F4   AG   AL   ATB  ABLADE  AN   CNK   PS   DC   UE   FZ   PLACE  \r\n");
							}
						}
#else
						
						if (pDph_t->PHSwapOut != NULL) 
							
#ifdef FULLSET
						{
							FNX_FSCANF(pDph_t->PHSwapIn,"\r\n")
							if (pDph_t->PHSwapOut != NULL) {
								for (ii = 0; ii < 16; ii++) {
#ifdef PH_DEBUG
									FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[ii]);
#endif
								}
#ifdef PH_DEBUG
								FNX_FPRINTF(pDph_t->PHSwapOut,"\r\n");
#endif
								for (ii = 16; ii < 37; ii++) {
#ifdef PH_DEBUG
									FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[ii]);
#endif
								}
#ifdef PH_DEBUG
								FNX_FPRINTF(pDph_t->PHSwapOut,"\r\n");
#endif
							}
#else
							{
#ifdef PH_DEBUG
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",(pDph_t->parstochip[OUT_PH]));
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_T0]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_A2]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_F1]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_F2]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_F3]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_F4]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_AG]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%5d ",pDph_t->parstochip[OUT_AL]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%5d ",pDph_t->parstochip[OUT_AB]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%5d ",pDph_t->parstochip[OUT_ATB]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%5d ",pDph_t->parstochip[OUT_ABLADE]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%5d ",pDph_t->parstochip[OUT_AN]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%5d ",pDph_t->parstochip[OUT_CNK]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_PS]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_DC]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_UE]);
								FNX_FPRINTF(pDph_t->PHSwapOut,"%4d ",pDph_t->parstochip[OUT_PLACE]);
							
								
								FNX_FPRINTF(pDph_t->PHSwapOut,"\r\n");
#endif
							}
#endif
							if (pDph_t->PHSwapIn != NULL) {
#ifdef FULLSET
								for (ii = 0; ii < 16; ii++) {
									FNX_FSCANF(pDph_t->PHSwapIn,"%4d ",&pDph_t->parstochip[ii]);
								}
								FNX_FSCANF(pDph_t->PHSwapIn,"\r\n");
								for (ii = 16; ii < 37; ii++) {
									FNX_FSCANF(pDph_t->PHSwapIn,"%4d ",&pDph_t->parstochip[ii]);
								}
							
#else
							//FNX_FSCANF(pDph_t->PHSwapIn," AP   F1   A2   A3   A4   A5   A6   AB  TILT  T0   AV   F2   F3    FZ   B1   B2   B3       \r\n");

								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_PH]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_T0]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_A2]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_F1]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_F2]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_F3]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_F4]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_AG]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%5hd ",&pDph_t->parstochip[OUT_AL]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%5hd ",&pDph_t->parstochip[OUT_AB]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%5hd ",&pDph_t->parstochip[OUT_ATB]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%5hd ",&pDph_t->parstochip[OUT_ABLADE]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%5hd ",&pDph_t->parstochip[OUT_AN]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%5hd ",&pDph_t->parstochip[OUT_CNK]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_PS]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_DC]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_UE]);
								FNX_FSCANF(pDph_t->PHSwapIn,"%4hd ",&pDph_t->parstochip[OUT_PLACE]);
								FNX_FSCANF(pDph_t->PHSwapIn,"\r\n");
								
#endif
								if (FNX_FEOF(pDph_t->PHSwapIn)) {
									FNX_FCLOSE(pDph_t->PHSwapIn);
									pDph_t->PHSwapIn = FNX_FOPEN("phdata.in","rb");
									
								}
							}
							
							
#endif //hlsyn
							
#endif	// PH_SWAPDATA
							
//FNX_PRINTF(" %d \n",pDph_t->parstochip[OUT_B1]);	
#ifdef PH_DEBUG
							if(DT_DBG(PH_DBG,0x020))
							{
								if( (pDphsettar->phcur & PVALUE) != 0)
								{
#ifdef DEBUGPHT
//dtfnxexstdlib.h has FNX_PRINTF mappring - mlt
//#if defined (WIN32) && defined (PRINTFDEBUG)
//									FNX_PRINTF ("*phcur= %d \n", pDphsettar->phcur);
									
									
//#else
									FNX_PRINTF ("*phcur= %d \n", pDphsettar->phcur);
									//FNX_PRINTF ("%s \n", phprint(pDphsettar->phcur));
									
									
									
//#endif	// defined (WIN32) && defined (PRINTFDEBUG)
#endif	// DEBUGPHT
									
#ifndef UNDER_CE
									//		FNX_PRINTF ("phon= %d  ", ((pDph_t->allophons[ pDph_t->nphone]& PVALUE)));
									//FNX_PRINTF ("*phcur= %d", pDphsettar->phcur);
									//		FNX_PRINTF ("%s \n", phprint(pDphsettar->phcur));
									
#endif
									for (ii = 0; ii<=32; ii++)			   /* EAB FOR REGRESSION TESTING */
									{
										WAIT_PRINT;
//dtfnxexstdlib.h has FNX_PRINTF mappring - mlt
//#if defined (WIN32) && defined (PRINTFDEBUG)
//										FNX_PRINTF("%d ", pDph_t->parstochip[ii]);
//#else
#ifdef PH_DEBUG
										FNX_PRINTF("%d ", pDph_t->parstochip[ii]);
#endif
//#endif // defined (WIN32) && defined (PRINTFDEBUG)
										SIGNAL_PRINT;
									}
									WAIT_PRINT;

//dtfnxexstdlib.h has FNX_PRINTF mappring - mlt
//#if defined (WIN32) && defined (PRINTFDEBUG)
//									FNX_PRINTF ("\n");
//#else
#ifdef PH_DEBUG
									FNX_PRINTF ("\n");
#endif
//#endif	// defined (WIN32) && defined (PRINTFDEBUG)
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
		arg2 = 0;//
		break;
	case 3:
		arg2 = 0;//+percent;
		
		break;
	case 4:
		arg2 = 0;
		
		break;
	case 5:
		arg2 = 0;//-percent;  
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
		arg2 = 0;//-percent>>1;
		break;
	case 11:
		arg2 = 0;//-percent>>1;
		break;
	case 12:
		arg2 =  0;//-percent>>1;
		break;
	case 13:
		arg2 =  -percent;
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
	
//	printf(" %d \n", *formpointer);	
	*formpointer += mlsh1 (arg1,arg2);
//	printf("2nd %d \n", *formpointer);	
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
		arg2 = 0;
		if (temp == TRUE)
		{
			pDph_t->smodulcount=-1;
		}
	}
	
	
	*formpointer += mlsh1 (arg1,arg2);
	//FNX_PRINTF("%d \n ", *formpointer);
	if (temp == TRUE)
	{
		pDph_t->smodulcount++;
	}
}
/* rit_modulation */

void rs_modulation(LPTTS_HANDLE_T phTTS,short *formpointer, short percent, short temp)
{
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	short  arg1, arg2;		/* arguments for mlsh1 */
	
	arg1 = *formpointer;
	
	
	switch (pDph_t->smodulcount)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		arg2 = 0;
		break;
	case 4:
	case 5:
	case 6:
		arg2 = -percent;
		break;
	case 7:
		arg2 =  -percent>>1;
		break;
	default:
		arg2 = 0;
		break;
	}
	
	*formpointer += mlsh1 (arg1, arg2);

	if (temp == TRUE)
	{
		pDph_t->smodulcount++;
	}
}
/* rs_modulation */

/*FUNCTION_HEADER**********************
 * NAME:	;ParameterModulation
 * DESC: 	Modulate some parameter according to the values in pwSequence
 * IN:		phTTS - pointer to the global TTS data
			pwSequence - sequence describing the modulation pattern
			nMax - max number of values in pwSequence
			bIncrement - flag to increment the modulation counter
 * OUT:		pwParameter - pointer to the parameter to modulate
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void ParameterModulation(LPTTS_HANDLE_T phTTS, short *pwParameter, 
						 short *pwSequence, short nMax, short bIncrement)
{
	PDPH_T
		pDph_t = phTTS->pPHThreadData;
	short  
		arg1, arg2;		/* arguments for mlsh1 */
	
	arg1 = *pwParameter;
	if( pDph_t->smodulcount < nMax )
		arg2 = pwSequence[pDph_t->smodulcount];
	else
		arg2 = pwSequence[pDph_t->smodulcount%nMax];	// circulate back to the beginning if going long 
	
	*pwParameter += mlsh1 (arg1, arg2);

	if(bIncrement == TRUE)
	{
		pDph_t->smodulcount++;
	}
}	// ParameterModulation



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
		arg2 = +percent;
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
		arg2 = +percent;
		break;
	case 11:
		arg2 = +percent;
		break;
	case 13:
		arg2 =  +percent;
		break;
	case 14:
		arg2 = +percent;
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
*      Comments: Seems to be about the same as k_modulation is used in phdraw()
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

/*FUNCTION_HEADER**********************
 * NAME:	;Phrase_intial_sil_start
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void Phrase_intial_sil_start(LPTTS_HANDLE_T phTTS)
{
	int tmp;
	PVTM_T			pVtm_t = phTTS->pVTMThreadData;
	PKSD_T			pKsd_t = phTTS->pKernelShareData;
	PDPH_T          pDph_t = phTTS->pPHThreadData;
	PDPHSETTAR_ST   pDphsettar = pDph_t->pSTphsettar;

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
			pDph_t->pressure_burst = 0;
			if( (phone_feature(pDph_t,pDph_t->allophons[1]) & FPLOSV) IS_PLUS
				&& (phone_feature(pDph_t,pDph_t->allophons[1]) & FVOICD) IS_MINUS)
			{
				pDph_t->pressure = 300;
				pDph_t->pressure_burst = pDphsettar->ob_onset_pressure;
			}
			else
				pDph_t->pressure = 200;
		}
		else
		{
			pDph_t->pressure_burst =0;
			pDph_t->pressure = 300;
		}
		pDph_t->pressure_drop=0;
		pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA; 
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
		pDph_t->target_tb = 1000;
		pDph_t->syl_pressure = 0;

#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF(" AT beg sil init to default.\n");
		}
#endif

		if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FOBST)
		{
			if( (phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone+1])) & FBURST &&
				(phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone+1])) & FSTOP)
				//we have a total blockgage with a burst so shut something
			{
				if((phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone+1])) & FVOICD)
				{
					if((phone_feature(pDph_t, pDph_t->allophons[pDph_t->nphone+1])) & FOBST)
						pDph_t->target_ag = pVtm_t->NOM_VOICED_OBSTRUENT+400;
					else
					{
						pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA; //default open
						pDph_t->area_g = pVtm_t->NOM_VOIC_GLOT_AREA;
					}
					pDph_t->agspeed = 2;
					pDph_t->target_ap = 100;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Voiced with (burst) so ap\n");
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
						FNX_PRINTF(" Unvoiced burst with stop ag to %d \n",pDph_t->target_ag );
					}
#endif
				}

				// next phone = FOBST + FBURST + FSTOP
				if((place(pDph_t->allophons[pDph_t->nphone+1])) & FLABIAL )
				{	
					pDph_t->in_lclosure = 1;
					pDph_t->area_l = 0;
					pDph_t->area_b = 1000;
					pDph_t->target_l=0;
					pDph_t->target_narea =0;
					pDph_t->lstep=0;
					pDph_t->bstep=0;

#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" At beg sil next a labial w burst.\n");
					}
#endif
				}

				if( place(pDph_t->allophons[pDph_t->nphone+1]) & BLADEAFFECTED )
				{	
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF("Phone after silence blade_affected with a burst so set area and target to 0\n");
					}
#endif
					pDph_t->in_bclosure = 1;
					pDph_t->area_b = 0;
					pDph_t->target_b = 0;
					pDph_t->target_l = 1000;
					pDph_t->target_narea =0;
					pDph_t->bstep=0;
				}
				if(( place(pDph_t->allophons[pDph_t->nphone+1])) & FVELAR )
				{
					pDph_t->in_tbclosure = 1;
					pDph_t->tbstep =0;
					pDph_t->in_bclosure = 0;
					pDph_t->area_b = 1000;
					pDph_t->target_b = 1000;
					pDph_t->target_l = 1000;
					pDph_t->target_narea =0;
					pDph_t->tbstep=0;
					pDph_t->target_tb = 0;	
					pDph_t->area_tb = 0;
					pDph_t->bstep=0;
					pDph_t->lstep=0;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" At beg sil next a velar.\n");
					}
#endif
				}
			}	// FBURST + FSTOP

			else
			{	//obst w/o a burst
				if(place(pDph_t->allophons[pDph_t->nphone+1]) & BLADEAFFECTED )
				{	
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF(" Phone after silence blade_affected without a burst \n");
					}
#endif
					pDph_t->in_bclosure = 0;
					//pDph_t->area_l = 1000;
					pDph_t->target_b = 0;
					pDph_t->area_b = 0;
					pDph_t->target_ag = pVtm_t->NOM_VOICED_OBSTRUENT;

					pDph_t->agspeed = 3;

					pDph_t->target_l=1000;
					pDph_t->target_narea =0;
					pDph_t->bstep=0;
				}
			}	// !FBURST || !FSTOP
		}	// FOBST
	}	// nphone != nphonelast

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
		pDph_t->tbstep=0;

		if (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FOBST)
		{
			if( phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FSTOP && 
				phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FPLOSV)
			{
				//voiced ob so ag small for voicebar until releasae
				pDph_t->target_ag = 1300;
				pDph_t->area_g = 1700;
			}
			else
			{
				//change this to an absolute becasue we should be slightly abov the voicein 
				//strong trigger point, but can start below end target
				pDph_t->target_ag = 1400;
				pDph_t->area_g = 1400;
			}
		}
		else if(place(pDph_t->allophons[pDph_t->nphone+1]) & FGLOTTAL)
		{
			pDph_t->target_ag = 0;
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF(" Phone after sil GLOTTAL so target_ag = %d \n",pDph_t->target_ag);
			}
#endif
		}
		



		else 
		{//start narrow
			pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA>>1;
		}
		
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF(" Phone after sil so targetag = %d \n",pDph_t->target_ag);
		}
#endif

		if((place(pDph_t->allophons[pDph_t->nphone+1])) & FLABIAL )		// FVOICD + FLABIAL
		{	
			pDph_t->in_lclosure = 0;
			pDph_t->area_l = pVtm_t->NOM_Fricative_Opening;
			pDph_t->area_b = 1000;
			pDph_t->target_l=150;
			pDph_t->target_narea =0;
			pDph_t->lstep=0;

#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF(" At beg sil next a labial w/o burst.\n");
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
			pDph_t->nasal_step =0;
			pDph_t->dcstep = 0;
		} //Inital SILENCE INITALIZATION

		if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FNASAL) )
		{
			pDph_t->area_n=200;

			if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]+1) & FSTOP)

			{
				pDph_t->target_ag =pVtm_t->NOM_VOIC_GLOT_AREA;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					//			NNOOOOO ADD IN NG
					FNX_PRINTF(" Phone after sil a nasal stop \n so open velum and shut shomething..");
				}
#endif
			}
			if(place(pDph_t->allophons[pDph_t->nphone+1]) & BLADEAFFECTED )
			{
				pDph_t->area_b = 0;
				pDph_t->target_b = 0;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
					FNX_PRINTF(" the blade!\n");
#endif
			}
			else
				//must be an m
			{
				pDph_t->area_l = 0;
				pDph_t->target_l = 0;
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
					FNX_PRINTF(" the lips!\n");
#endif
			}


			pDph_t->target_narea =240;

			pDph_t->nasal_step = 7;
		}
		else
			pDph_t->nasal_step =0;

	}	// FVOICED
	else
	{
		pDph_t->area_g = pVtm_t->NOM_VOIC_GLOT_AREA+1000;
		pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+1000;
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
			FNX_PRINTF("Starting with unvoiced so open glottis\n");
#endif
	}

	if(pDph_t->allophons[pDph_t->nphone+1] == USP_DH
		|| pDph_t->allophons[pDph_t->nphone+1] == USP_TH
		|| pDph_t->allophons[pDph_t->nphone+1] == USP_DZ
		|| pDph_t->allophons[pDph_t->nphone+1] == UKP_DH
		|| pDph_t->allophons[pDph_t->nphone+1] == UKP_TH
		|| pDph_t->allophons[pDph_t->nphone+1] == UKP_DZ)
		//Post processsing rule to add special closure REF 1000
	{
		pDph_t->target_b = 0;
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF("Special rule for blade with dh-th and dz \n");
		}
#endif

	}	
			
}	// Phrase_intial_sil_start()
			
/*FUNCTION_HEADER**********************
 * NAME:	;Phrase_final_silence
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void Phrase_final_silence(LPTTS_HANDLE_T phTTS)
{
	PVTM_T			pVtm_t = phTTS->pVTMThreadData;
	PKSD_T			pKsd_t = phTTS->pKernelShareData;
	PDPH_T			pDph_t = phTTS->pPHThreadData;
	PDPHSETTAR_ST	pDphsettar = pDph_t->pSTphsettar;

	if(pDph_t->pressure >100)
	{
		if (pDph_t->pressure_drop < 2000)
		{
			pDph_t->pressure_drop +=80;
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF("at ending sil press drop == %d \n",pDph_t->pressure_drop);
			}
#endif
		}		
	}

	if(pDph_t->phonestep < 2)
	{		

		if(!(place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED ))
		{
			//blade not affect so set it open
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF(" Blade NOT affected so target b to 1000\n");
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
				FNX_PRINTF(" Phone before ending silence blade_affected so set target to 0\n");
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
			if(pDph_t->target_ag < 2000)
				pDph_t->target_ag = 2000;
			if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1])) & FNASAL
				&&	(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1])) & FSTOP )
				pDph_t->target_ag = 400;

#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF(" At end so set ag to %d\n",pDph_t->target_ag);
			}
#endif								
		}
		if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FOBST)
		{
			pDph_t->target_ag = 2500;
		}

		if(!(phone_feature_2(pDph_t,pDph_t->nphone-1) & FVOICD ))
		{
			pDph_t->target_ag = 1800;
			pDph_t->area_g += 100;


		}
	}
}
	
/*FUNCTION_HEADER**********************
 * NAME:	;Do_ue_dc
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	none
 * NOTES:	
	ue affects the intra oral pressure during a constricted oral tract.
	dc affects the compliance or stiffness of the vocal cords. 
	
	For example the voice bars are louder in Spanish - this can be modified by 
	controlling glottal opening and/or ue and/or dc but where is the right balance.

 *END_HEADER***************************/
#ifdef HLSYN
void Do_ue_dc(LPTTS_HANDLE_T phTTS)
{

	PVTM_T pVtm_t = phTTS->pVTMThreadData;
	PKSD_T pKsd_t = phTTS->pKernelShareData;
	PDPH_T pDph_t = phTTS->pPHThreadData;
	PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;

	if(pDph_t->nphone == 0)
	{
		pDph_t->dcstep =0;
	}

	if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST
		&& pDph_t->dcstep == 0
		&& pDph_t->area_n == 0
		//&& pDph_t->phonestep >= 1  // why phonestep >=1?? why dont do step 0?
		&&  (pDph_t->allophons[ pDph_t->nphone] != SPP_BH)
		&&  (pDph_t->allophons[ pDph_t->nphone] != SPP_DH )
		&&  (pDph_t->allophons[ pDph_t->nphone] != SPP_GH )
		&&  (pDph_t->allophons[ pDph_t->nphone] != LAP_BH)
		&&  (pDph_t->allophons[ pDph_t->nphone] != LAP_DH )
		&&  (pDph_t->allophons[ pDph_t->nphone] != LAP_GH )
		)
	{
		//I don't think we should wait to start ue causes problem
		//with vowel-z- so try it out and see if we brak anything
		// we may need to make ramp longer with smaller increments???
		//next add anticpaiotn of z in vowel -mainly for phrase 


		if(phone_feature_2( pDph_t, ( pDph_t->nphone)) & FVOICD
			&& !(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FNASAL))
		{
			if ((phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FSTOP) &&
				pDph_t->allodurs[pDph_t->nphone]<7)
			{
				// block dc and ue for short durations.
			}
			else
			{

			pDph_t->dcstep=1;
			pDph_t->uestep=1;
			}
		}
		else
		{
			pDph_t->dcstep=-1;
			pDph_t->uestep=-1;
		}

		PH_DEBUG_2080_P1(" obstruent dcstep to %d\n", pDph_t->dcstep);
	}

	if(pDph_t->dcstep != 0	)
	{
		//end voiced dcstep dcstep
		if((phone_feature_2( pDph_t, ( pDph_t->nphone)) & FVOICD) ||
			pDph_t->allophons[ pDph_t->nphone] == GEN_SIL )
		{
			if(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FOBST)
			{
				//ADD VOICED UNVOICED
				//end it only if next thing not also a voiced obstruent
				if(pDph_t->dcstep > 0 && (pDph_t->tcum > (pDph_t->allodurs[pDph_t->nphone]- pDph_t->dcstep)) 
					&&!(phone_feature_2( pDph_t,( pDph_t->nphone+1)) & FVOICD)
					&& (phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone+1)]) & FOBST)
					|| (pDph_t->allophons[ pDph_t->nphone+1] == SPP_BH)
					|| (pDph_t->allophons[ pDph_t->nphone+1] == SPP_DH)
					|| (pDph_t->allophons[ pDph_t->nphone+1] == SPP_GH)
					|| (pDph_t->allophons[ pDph_t->nphone+1] == LAP_BH)
					|| (pDph_t->allophons[ pDph_t->nphone+1] == LAP_DH)
					|| (pDph_t->allophons[ pDph_t->nphone+1] == LAP_GH))
				{
					pDph_t->dcstep--;
					if(	pDph_t->dcstep != 0)
						pDph_t->dcstep--;

					PH_DEBUG_2080_P1(" moving dcstep at end to %d\n",pDph_t->dcstep);
				}
				else
				{
					if(	pDph_t->dcstep <= 9
						&& 		pDph_t->dcstep >= 0)
					{
						pDph_t->dcstep++;
					}

					else if( pDph_t->dcstep >= -9)
						pDph_t->dcstep--;
				}
			}

			else if(pDph_t->area_n ==0) 
			{
				//if dcstep is of opposite sign it means we're obstr-obstru so change fast
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
				PH_DEBUG_2080_P1(" Move dcstep to %d\n",pDph_t->dcstep);

			}

			if( (!(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FOBST)
				&& pDph_t->tcum > 1) 
				|| pDph_t->area_n != 0
				//for  burst collapse at end of obstruent to increse pressure
				//changed not for fric because z vocing drops
				|| ((!(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone+1)])& FOBST)
				&& phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]& FOBST))))
			{

				if( ((phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]))& FBURST)
					&& (pDph_t->tcum >= pDph_t->allodurs[pDph_t->nphone]- 3 )
					||( (phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]))& FSON1) 
					&& pDph_t->phonestep < 6)
				{

					if(pDph_t->dcstep > 1)
					{
						pDph_t->dcstep-=3;
						if(pDph_t->dcstep < 0)
							pDph_t->dcstep =0;
					}
					else
					{
						pDph_t->dcstep+=3;
						if(pDph_t->dcstep > 0)
							pDph_t->dcstep =0;
					}
				}
			}
		}
		else
		{
			if( pDph_t->dcstep > -9)
				pDph_t->dcstep--;
		}

#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
			FNX_PRINTF("Do_ue_dc:: dcstep %d, nphone %d, tcum %d, total frames %d\n",
				pDph_t->dcstep,
				pDph_t->nphone,
				pDph_t->tcum,
				pDph_t->allodurs[pDph_t->nphone] );
#endif

#ifdef outfornow
		else 
		{

			if((phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)]) & FOBST
				&& pDph_t->area_n ==0 
				&& pDph_t->tcum <= pDph_t->allodurs[pDph_t->nphone]-3
				&&  phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)])& FBURST))
				|| (phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone)])& FBURST)) 
			{
				//if dcstep is of opposite sign it means we're obstr-obstru so chnage fast
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
			else if((!(phone_feature( pDph_t, pDph_t->allophons[( pDph_t->nphone+1)]) & FOBST)) 
				|| pDph_t->area_n != 0)
			{

				pDph_t->dcstep+=2;
				if(pDph_t->dcstep >0)
					pDph_t->dcstep =0;

			}

		}
#endif	
		if(pDph_t->dcstep >= 0)
		{
			//need to look at dc to get sign right 
			//this in for potential idea of increasing dc for a labial
			{
				//dc toward end of consonant
				pDph_t->parstochip[OUT_DC] = dcval[pDph_t->dcstep]; 
				pDph_t->parstochip[OUT_UE] = ueval[pDph_t->dcstep];
				//eab at the bouncdary start back down
			}
		}
		else
		{
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

	if( pKsd_t->lang_curr == LANG_spanish || 
		pKsd_t->lang_curr == LANG_latin_american)
	{
		pDph_t->parstochip[OUT_DC] = pDph_t->parstochip[OUT_DC]>>2;
		pDph_t->parstochip[OUT_UE] = pDph_t->parstochip[OUT_UE]>>1;
	}
	return;	
}
#endif		// HLSYN


/*FUNCTION_HEADER**********************
 * NAME:	;Set_pressure
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void Set_pressure(LPTTS_HANDLE_T phTTS)
{
	PVTM_T pVtm_t = phTTS->pVTMThreadData;
	PKSD_T pKsd_t = phTTS->pKernelShareData;
	PDPH_T pDph_t = phTTS->pPHThreadData;
	PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;

	if(pDph_t->allophons[ pDph_t->nphone] == GEN_SIL)
	{
		if(pDph_t->pressure > 300)
			pDph_t->pressure -= 100;
		return;
	}
	if(pDph_t->pressure <= pVtm_t->NOM_Sub_Pressure
		&& pDph_t->nphone < 3)
	{
		if((phone_feature_2(pDph_t,pDph_t->nphone)) & FVOICD)
		{
			pDph_t->pressure += 70;

			PH_DEBUG_2080(" AT first phone so build up pressure for sonorant \n");
		}
		else
		{
			pDph_t->pressure += 80;

			PH_DEBUG_2080(" AT first phone so build up pressure for unvoiced\n");
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

	else if( (pDph_t->allofeats[pDph_t->nphone] & FSTRESS)
		&& ((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone])) & FSYLL)
		|| pDph_t->stress_pulse >0) 
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

		PH_DEBUG_2080_P1("stressed syl build pressure-stress pulse %d\n",pDph_t->stress_pulse);
	}

}	// Set_pressure


/*FUNCTION_HEADER**********************
 * NAME:	;Do_once_per_phoneme
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void Do_once_per_phoneme(LPTTS_HANDLE_T phTTS)
{
	PVTM_T pVtm_t = phTTS->pVTMThreadData;
	PKSD_T         pKsd_t = phTTS->pKernelShareData;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;

	//********If previous phone is........
	if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FPLOSV))
	{

		//do at start of phone but not later i.e. once per phone only
		//previous not a plosive so kill the release
		pDph_t->in_lrelease=0;
		pDph_t->in_brelease=0;
		pDph_t->in_tbrelease=0;
		pDph_t->bstep=0;
		pDph_t->lstep=0;
		pDph_t->tbstep=0;


#ifdef DEBUGIOT
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF("previous phone not a plos so we're not in a release cyle\n");
		}
#endif

	} 

	if((phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD))
	{
		if(place(pDph_t->allophons[pDph_t->nphone]) & FGLOTTAL)
		{

			PH_DEBUG_2080(" glottalized obstruent-- close glottis \n");

			if(pDph_t->tcum <= (pDph_t->allodurs[pDph_t->nphone]-4))
			{

				pDph_t->target_ag = pVtm_t->NOM_Glot_Stop_Area;
				if(pDph_t->area_g > pVtm_t->NOM_VOIC_GLOT_AREA+200)
					pDph_t->area_g = pVtm_t->NOM_VOIC_GLOT_AREA+200;
				pDph_t->agspeed =1;

			}
			if(pDph_t->allophons[pDph_t->nphone] == HEP_NG)
			{
				pDph_t->target_ag = 150;
				pDph_t->agspeed =1;
			}
		}
		else
		{
			if( pDph_t->vot == 0)
			{
				if((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone])) & FOBST)
				{
					pDph_t->target_ag = pVtm_t->NOM_VOICED_OBSTRUENT;
					PH_DEBUG_2080_P1(" Vot = 0, Setting target_ag for voiced-obstruent to %d\n", pDph_t->target_ag);
				}
				else
				{
					pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA;
					PH_DEBUG_2080_P1(" Vot = 0, Setting target_ag for voiced-sonorant to %d\n", pDph_t->target_ag);
				}
			}

			pDph_t->agspeed =1;
		}

	}

	/// If this phone is a .....
	if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST)
	{
		if((phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD))
		{
			if(place(pDph_t->allophons[pDph_t->nphone]) & FGLOTTAL)
			{
				PH_DEBUG_2080(" glottalized obstruent -- close glottis\n");
				pDph_t->target_ag = pVtm_t->NOM_Glot_Stop_Area;
				pDph_t->agspeed =1;

			}
			else
			{
				if(pDph_t->allophons[pDph_t->nphone] == JP_Z)
					pDph_t->target_ag = pVtm_t->NOM_VOICED_OBSTRUENT+300;
				else
					pDph_t->target_ag = pVtm_t->NOM_VOICED_OBSTRUENT+200;

				if(pKsd_t->lang_curr == LANG_korean)
					pDph_t->target_ag = pVtm_t->NOM_VOICED_OBSTRUENT+400;


				// voicd ob stop i.e. voicebar
				// order of checking important here
				if( phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSTOP &&
					phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD &&
					phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FPLOSV)
				{
					if( pDph_t->allophons[pDph_t->nphone] == SPP_B ||
						pDph_t->allophons[pDph_t->nphone] == LAP_B ||
						pDph_t->allophons[pDph_t->nphone] == SPP_V ||
						pDph_t->allophons[pDph_t->nphone] == LAP_V )
					{
						pDph_t->target_ag = 400;	// open glottis enough for voicing
						pDph_t->target_ap = 0;		// close chink

						pDph_t->target_narea = 100;	// open nasal passage for voicebar
						pDph_t->nasal_step = 1;

						PH_DEBUG_2080(" Spanish B voicebar (open glottis for voicing and nasal for voicebar) ...\n");
					}
					else
					{
						pDph_t->target_ag = 1200;	// area of glottis
						pDph_t->area_g = 1200;
						pDph_t->target_ap = 0;	// chink
	
						PH_DEBUG_2080(" Voicebar ...\n");
					}
				}
				else if(phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FBURST)
				{
					//affriacte
					pDph_t->target_ag = pVtm_t->NOM_VOICED_OBSTRUENT-200;
					pDph_t->target_ap = 400;	// chink
				}
				else
				{
					pDph_t->target_ag = pVtm_t->NOM_VOICED_OBSTRUENT;	// area of glottis
					pDph_t->target_ap = 400;	// chink

					pDph_t->agspeed =2;
				}
				if( pDph_t->allophons[pDph_t->nphone+1] == SPP_BH || 
					pDph_t->allophons[pDph_t->nphone+1] == SPP_DH || 
					pDph_t->allophons[pDph_t->nphone+1] == SPP_GH || 
					pDph_t->allophons[pDph_t->nphone+1] == LAP_BH || 
					pDph_t->allophons[pDph_t->nphone+1] == LAP_DH || 
					pDph_t->allophons[pDph_t->nphone+1] == LAP_GH )
				{
					pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA;	
				}
				if ( pDph_t->phonestep==0
					&& (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FNASAL) 
					&& (!(phone_feature_2(pDph_t,pDph_t->nphone) & FVOICD) ||
					(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSTOP)))
				{
					pDph_t->area_g+=(pDph_t->target_ag-pDph_t->area_g)>>1;
					//pDph_t->area_g+=400;
					if (pDph_t->target_ap < pDph_t->area_ap)
					{
						pDph_t->area_ap-=(pDph_t->area_ap-pDph_t->target_ap)>>1;
					}
					else 
					{
						pDph_t->area_ap+=(pDph_t->target_ap-pDph_t->area_ap)>>1;
					}
//					pDph_t->area_ap+=100;
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF("Voiced obstruent after nasal so move glottis to %d and ap to %d faster to avoid strong voicing\n",
							pDph_t->target_ag,pDph_t->target_ap);
					}
				}


#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF("Voiced obstruent so glottis to %d and ap to %d\n",
						pDph_t->target_ag,pDph_t->target_ap);
				}
#endif		

			}

		}
		else
		{
			if(place(pDph_t->allophons[pDph_t->nphone]) & FGLOTTAL)
			{

#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF(" glottalized obstruent-- close glottis \n");
				}
#endif					
				pDph_t->target_ag = pVtm_t->NOM_Glot_Stop_Area;

				pDph_t->agspeed =1;

			}
			else
			{

	
				if ((phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FBURST)
					|| (phone_feature(pDph_t,pDph_t->allophons[ pDph_t->nphone]) & FOBST))
				{
					//delay opening until later
					
				}
				else
				{
					PH_DEBUG_2080("opening glottis \n");

					pDph_t->target_ag = pVtm_t->NOM_Open_Glottis;
				}
			
			}
		}
		if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FBURST)
		{
			PH_DEBUG_2080(" Has burst so shut ");

			if((place(pDph_t->allophons[pDph_t->nphone])) & FLABIAL )
			{	
				PH_DEBUG_2080("the lips and open the blade and tongue body\n");

				pDph_t->target_l = 0;			// close lips
				pDph_t->target_b = 1000;		// open other constrictions
				pDph_t->target_tb= 1000;
			}

			if((place(pDph_t->allophons[pDph_t->nphone])) & BLADEAFFECTED )
			{	
				PH_DEBUG_2080("the blade and open the lips and tongue body\n");

				//nonlabial plosive OR AFFRICATE obstruent i.e. it's the blade
				pDph_t->target_b = 0;		// close blade
				pDph_t->target_l = 1000;	// open other constrictions
				pDph_t->target_tb= 1000;
			}
		
			if((place(pDph_t->allophons[pDph_t->nphone])) & FVELAR )
			{
				PH_DEBUG_2080("the tongue body and open blade and lips\n");

				//non-plosive non-labial obstruent i.e. the blade
				pDph_t->lstep =0;
				pDph_t->tbstep =0;
				pDph_t->target_tb= 0;		// close tongue body
				pDph_t->target_b = 1000;	// open other constrictions
				pDph_t->target_l = 1000;
			}
		}	// FBURST

		else	// Not FBURST
		{
			PH_DEBUG_2080("Non burst obst so narrow ... ");

			if((place(pDph_t->allophons[pDph_t->nphone])) & FLABIAL )
			{
				PH_DEBUG_2080("the lips and open the blade\n");

				//non-plosive labial obstruent
				pDph_t->lstep = 0;			

				pDph_t->target_l= 100;
				if( pDph_t->allophons[pDph_t->nphone] == SPP_BH || 
					pDph_t->allophons[pDph_t->nphone] == LAP_BH)
				{
					pDph_t->target_l = 300;
				}

				pDph_t->target_b = 1000;
				pDph_t->bstep=0;
				pDph_t->target_tb= 1000;					
			}

			else if((place(pDph_t->allophons[pDph_t->nphone])) & BLADEAFFECTED )
			{	
				//non-plosive non-labial obstruent i.e. the blade
				pDph_t->lstep =0;
				if( pDph_t->allophons[pDph_t->nphone] == SPP_DH || 
					pDph_t->allophons[pDph_t->nphone] == LAP_DH )
				{
					pDph_t->target_b = 200;
				}
				else if( !(pDph_t->allophons[pDph_t->nphone] == USP_DH) )
				{
					pDph_t->target_b = pVtm_t->NOM_Fricative_Opening;
				}

				//pDph_t->area_b = pVtm_t->NOM_Fricative_Opening;
				pDph_t->target_l	= 1000;
				pDph_t->target_tb	= 1000;

				PH_DEBUG_2080_P1("the blade to %d and open the lips\n", pDph_t->target_b);
			}
			else if((place(pDph_t->allophons[pDph_t->nphone])) & FVELAR )
			{
				PH_DEBUG_2080("the tongue body so open blade and open the lips\n");

				//non-plosive non-labial obstruent i.e. the blade
				pDph_t->lstep		= 0;
				pDph_t->target_b	= 1000;
				//pDph_t->area_b	= pVtm_t->NOM_Fricative_Opening;
				pDph_t->target_l	= 1000;
				pDph_t->target_tb	= 100;
				if( pDph_t->allophons[pDph_t->nphone] == SPP_GH	|| 
					pDph_t->allophons[pDph_t->nphone] == LAP_GH)
				{
					pDph_t->target_tb = 100;
					pDph_t->target_ap = 0;		// Close Chink

					PH_DEBUG_2080("SPANISH velar approximate ...");
				}
			}
			else if((place(pDph_t->allophons[pDph_t->nphone])) & FGLOTTAL )
			{
				PH_DEBUG_2080("the glottis to close\n");

				pDph_t->target_l= 1000;
				pDph_t->target_tb= 1000;
				pDph_t->target_ag = 0;		//keep glotis open longer
			}

			else //something else like a spanish y so releasee the other
			{
				pDph_t->target_l= 1000;
				pDph_t->target_tb= 1000;
				pDph_t->target_ag = 867;	//keep glotis open longer
			}
		}
	}	//Fobst
	else
		//not an obstruent so chink to zero.
		pDph_t->target_ap= 0;


	if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSTOP
		&& !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FBURST))
	{
		//okay we're at a stop without bursts ie. flapped d, glottal stop
		//or an soncon nasal or a trill

		if(place(pDph_t->allophons[pDph_t->nphone]) & BLADEAFFECTED )
			//for alvelars
		{
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF(" At beg of Phone w /stop w/alvel so blade target to 0 ");
				FNX_PRINTF(" and labial to 1000 \n");
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
			pDph_t->target_tb = 0;
			pDph_t->target_b =1000;
			pDph_t->target_l =1000;
			pDph_t->agspeed =2;
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF(" At beg of Phone w / stop w/labial so lip target to 0 ");
				FNX_PRINTF(" and blade to 1000 \n");
			}
#endif
		}

		if(place(pDph_t->allophons[pDph_t->nphone]) & FLABIAL )
		{
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF(" At beg of Phone w / stop w/labial so lip target to 0 ");
				FNX_PRINTF(" and blade to 1000 \n");
			}
#endif

			pDph_t->target_b =1000;
			pDph_t->target_l =0;

		}

	}//It has a Stop wo a burst

	if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSON1 
		&& !(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL)
		&& pDph_t->allophons[pDph_t->nphone] != CHP_NX)
	{

		//				A sonorant wow!
		if(!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSTOP ))
		{
			//if(pDph_t->phonestep >1)
			//	{}
			//wait in case of a release
			//this loooks like its redundant
			pDph_t->target_b = 1000;
			pDph_t->target_l = 1000;
			pDph_t->target_tb= 1000;

		}
		//		if(!((phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FPLOSV )
		//			 && (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FVOICD)))
		if(pDph_t->vot == 0)//vot sets it
		{
			//if stop then let other code set 
			if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST)
			{
				pDph_t->agspeed=1;
				pDph_t->target_ap=0;
			}
			if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FOBST)
			{
				//previous a voiced obstruent
				pDph_t->agspeed=1;
				if(pDph_t->area_g > 650)
				pDph_t->area_g= 650;
			}
			//target_ag = (pVtm_t->NOM_VOIC_GLOT_AREA+ pVtm_t->NOM_VOICED_OBSTRUENT)>>1;
			 
			if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FNASAL)
				pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA+100;
			else
				pDph_t->target_ag = pVtm_t->NOM_VOIC_GLOT_AREA;

#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x080))
			{
				FNX_PRINTF("in a FSON1 ag tar to %d  \n",pDph_t->target_ag );
			}		
#endif
		}
	}


	///open whatever isn't shut
	if(pDph_t->allophons[ pDph_t->nphone] == USP_R)
	{
		pDph_t->target_ag += 200;
#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x080))
		{
			FNX_PRINTF(" widening test glottis for r's  \n");
		}
#endif
	}	


	//problem with ag target setting early becuase a sonorant preceeded a 
	//plosive the glottal closing should be set be vot
	//v5.0 fixx to improve release of plosives in final position
	if(pDph_t->allofeats[pDph_t->nphone ] & FDUMMY_VOWEL)
	{
		pDph_t->in_tbrelease =1;
		if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FVOICD)
		{
			pDph_t->target_ag=pVtm_t->NOM_VOIC_GLOT_AREA+200;
		}
		else
		{
			pDph_t->target_ag = pVtm_t->NOM_Open_Glottis+300;
		}
	}

}


/*FUNCTION_HEADER**********************
 * NAME:	;Do_Nasal
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void Do_Nasal(LPTTS_HANDLE_T phTTS)
{
	PVTM_T pVtm_t = phTTS->pVTMThreadData;
	PKSD_T         pKsd_t = phTTS->pKernelShareData;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;

	//Nasal velum rules
	if( place(pDph_t->allophons[pDph_t->nphone]) & FVELAR &&
		phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FNASAL )
		//ng so set tbclosure
	{
		if(pDph_t->tcum <= (pDph_t->allodurs[pDph_t->nphone]))
		{
			pDph_t->in_tbclosure =1;
		}
	}

	if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FNASAL )
	{
		if( (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FOBST) &&	 	// Next phoneme is obstruent
			!(phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD) &&
			(pDph_t->allodurs[pDph_t->nphone] - pDph_t->tcum) <= 2 )					// Near end of nasal
		{
			//momentary glottal stop to avoid voicing
			if(pDph_t->area_g > 100)
				pDph_t->area_g -= 100;
			else
				pDph_t->area_g=0;

			pDph_t->target_ag = 0;

			// This code is to close velum early in the case of a nasal
			// followed by an obstr as in jumped oh
			if(pDph_t->nasal_step )
				pDph_t->nasal_step--;				// Close by 1 step at a time, not 2 like it used to be.  Too fast will cause it to sound un-natural.
			if(pDph_t->nasal_step )
				pDph_t->nasal_step--;				// Close by 1 step at a time, not 2 like it used to be.  Too fast will cause it to sound un-natural.

			PH_DEBUG_2080(" Nasal --> unvoiced obst so shut velum early and close glottis \n");
		}
		else if( (phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FOBST) &&	 	// Next phoneme is obstruent
			(phone_feature_2(pDph_t,pDph_t->nphone+1) & FVOICD) &&
			(pDph_t->allodurs[pDph_t->nphone] - pDph_t->tcum) <= 3   )				// Near end of nasal
		{
			// We want nasal_step to be at 2 (non-zero) at the last frame
			if(pDph_t->nasal_step >= 7)
				pDph_t->nasal_step=8;

			// This code is to close velum early in the case of a nasal
			// followed by an obstr as in jumped oh
			if(pDph_t->nasal_step )
			{
				pDph_t->nasal_step--;			// Close by 1 step at a time, not 2 like it used to be.  Too fast will cause it to sound un-natural.
				if(pDph_t->nasal_step )
					pDph_t->nasal_step--;		// Close by 1 step at a time, not 2 like it used to be.  Too fast will cause it to sound un-natural.
			}

			PH_DEBUG_2080(" Nasal --> voiced obst so shut velum early\n");
		}
		else if(pDph_t->nasal_step < 7)
		{
			pDph_t->nasal_step++;
			pDph_t->nasal_step++;
		}

		if(pDph_t->allodurs[pDph_t->nphone] <= 10)
		{
			if( pDph_t->nasal_step <= 1)
			{
				pDph_t->nasal_step =0;

				PH_DEBUG_2080(" Nasal shor delay velum drop and then do it faster \n");
			}
		}

		pDph_t->area_n = nasalization[pDph_t->nasal_step];	

		//pDph_t->lclosure = 1; //set closure to allow reseting of counts'

		PH_DEBUG_2080_P1(" Phone is a nasal (area_n = %d)\n",pDph_t->area_n);

	}	// FNASAL

	//eab special case for that money etc. if next is an artifical injected nasal
	else if( pKsd_t->lang_curr != LANG_french &&
			 phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FNASAL &&
			 phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSON1 &&
			 pDph_t->allophons[pDph_t->nphone+1] != pDph_t->allophons[pDph_t->nphone+2])
	{

		// In a sonorent with a nasal coming up drop velum
		//start droping velum 50% into vowel 
		//english og german only ????
		if (!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST))
		{

			// eab change to nasalize sooner >>2 instead of >>1 weab 6/08/04
			if( pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]>>2) 
				|| pKsd_t->lang_curr == LANG_chinese)
			{
				if(pDph_t->nasal_step <7)
					pDph_t->nasal_step++;
			}
		}
		else if (pDph_t->phonestep >  (pDph_t->allodurs[pDph_t->nphone]-4) )
		{
			if(pDph_t->nasal_step <7)
				pDph_t->nasal_step++;
		}

		pDph_t->area_n = nasalization[pDph_t->nasal_step ];
		PH_DEBUG_2080_P1(" Sonorent -> nasal, drop velum (area_n = %d)\n", pDph_t->area_n);
	}
	//if it's french or chinese nasal
	else if( (pKsd_t->lang_curr == LANG_french ||
			  pKsd_t->lang_curr == LANG_chinese) &&
			 phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FNASAL )
	{
		if( !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FOBST) &&
			pDph_t->tcum >= (pDph_t->allodurs[pDph_t->nphone]-2))
		{
			//start dropping velum slighlty before nasal
			if(pDph_t->nasal_step < 7)
				pDph_t->nasal_step++;
		}

		pDph_t->area_n = nasalization[pDph_t->nasal_step ];

		PH_DEBUG_2080_P1(" French or Chinese: Sonorent -> nasal, drop velum (area_n = %d)\n",pDph_t->area_n);
	}

	// we were in a nasal at some previous point 
	if( !(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FNASAL ) &&
		(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone-1]) & FNASAL ) )
	{
		if(pKsd_t->lang_curr == LANG_french)
		{
			//close it quickly for french 
			if(pDph_t->nasal_step)
			{
				if(pDph_t->nasal_step > 0)
					pDph_t->nasal_step--;
				if(pDph_t->nasal_step > 0)
					pDph_t->nasal_step--;

				pDph_t->area_n = nasalization[pDph_t->nasal_step ];
#ifdef PH_DEBUG
				if(DT_DBG(PH_DBG,0x080))
				{
					FNX_PRINTF("Previous phone is a nasal in french -drop velum,area_n = %d\n",pDph_t->area_n);
				}
#endif
			}
		}
		else	// for languages other than french
		{	
			if(pDph_t->nasal_step )
				// why avoid step 0 becasue in unsatis this causes a problem&& 
			//	pDph_t->phonestep )
			{
				if(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone]) & FSONOR)
				{

					//but not if between nasal's
					if(pDph_t->nasal_step > 0
						&& (!(phone_feature(pDph_t,pDph_t->allophons[pDph_t->nphone+1]) & FNASAL)))
						pDph_t->nasal_step--;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF("Previous phone  is a nasal-drop velum,area_n = %d\n",pDph_t->area_n);
					}
#endif	
					pDph_t->area_n = nasalization[pDph_t->nasal_step ];
					if(pDph_t->allophons[ pDph_t->nphone] == GEN_SIL && pDph_t->nphone<(pDph_t->nallotot-2))
					{
						pDph_t->nasal_step = 0;
#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF("Injected silence nsyep to 0 \n");
					}
#endif	
					}
				}
				else 		

				{
					//previous phone was a nasal but this one isn't plus its not a sonorant so o shut the velum quicker
					if(pDph_t->nasal_step > 4)
					{
						pDph_t->nasal_step -= 2;
					}
					else
						pDph_t->nasal_step--;
					if(pDph_t->nasal_step < 0)
						pDph_t->nasal_step = 0;
					pDph_t->area_n = nasalization[pDph_t->nasal_step ];

#ifdef PH_DEBUG
					if(DT_DBG(PH_DBG,0x080))
					{
						FNX_PRINTF("Previous phone is a nasal-drop velum,area_n = %d\n",pDph_t->area_n);
					}
#endif
				}
			}
		}	
	}
	pDph_t->area_n = nasalization[pDph_t->nasal_step];
}	// Do_Nasal
