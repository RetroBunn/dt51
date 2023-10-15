/* 
***********************************************************************
*
*                           Copyright ©
*	  Copyright © 2002 Fonix Corporation. All rights reserved.
*	  Copyright © 2000-2001 Force Computers, Inc., a Solectron Company. All rights reserved.
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
*/ 

#include "dectalkf.h"
#include "ph_def.h"

//#define DEBUGPHT

extern int inh_timing(LPTTS_HANDLE_T phTTS, int phone);
extern int min_timing(LPTTS_HANDLE_T phTTS, int phone);


/* ******************************************************************
*      Function Name: phtiming()      
*
*  	Description: 
*
*      Arguments: LPTTS_HANDLE_T phTTS Text-to-speech handle
*
*      Return Value: void
*
*      Comments:
*
* *****************************************************************/
void ch_phtiming(LPTTS_HANDLE_T phTTS)
{
	short                   psonsw = 0, posvoc = 0;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	short                   stcnt = 0;
	short                   syldur = 0;
	short                   ncnt = 0;
	short                   endcnt = 0;
	short					sonocnt = 0;
	short                   adjust = 0;
	short                   emphasissw = FALSE;		/* Made local and initialized */
	short                   pholas = GEN_SIL;		/* Made local and initialized */
	int                   struclas = 0;			/* Made local and initialized */
	int                   fealas = GEN_SIL;		/* Made local and initialized */
	short                   prcnt = 0, durinh = 0, durmin = 0, deldur = 0, nphon = 0;
	short                   phocur = 0, do_syl_adjust =0; 
	int				feacur = 0, feasyllabiccur = 0;
	int                   struccur = 0, strucboucur = 0, strucstresscur = 0;
	short                   dpause = 0;
	short					arg1,arg2;	/* arguments for the phmath routines. */
	
	
	short tmp;
	/* Initialization  (Set sprat1, sprat2, zero counters, print debug) */
	
	init_timing (phTTS);
	
	pDphsettar->numstresses =0;
	pDph_t->tcumdur =0;/* 9/97EAB Since durations are done differently 
					   in typing mode calculation
					   of total dur must be moved to here also
	NOTE TO CARL THIS MAY HAVE ALREADY BEEN SUBMITTED BY DOUG*/
	//#define MSDBG
	
	/* MAIN LOOP, for each output phoneme */
	
	for (nphon = 0; nphon < pDph_t->nallotot; nphon++)
	{
		if (nphon > 0)
		{
			pholas = pDph_t->allophons[nphon - 1];
			struclas = pDph_t->allofeats[nphon - 1];
			fealas = phone_feature(pDph_t ,pholas);
		}
		
		phocur = pDph_t->allophons[nphon];
		tmp = phocur & PVALUE;
		struccur = pDph_t->allofeats[nphon];
		strucboucur = struccur & FBOUNDARY;
		feacur = phone_feature( pDph_t ,phocur);
		feasyllabiccur = feacur & FSYLL;
		strucstresscur = struccur & FSTRESS;
		
	

		if (pDph_t->user_durs[nphon] > 0)
		{
			
			pDphsettar->durxx = mstofr(pDph_t->user_durs[nphon] + 4);
			
			deldur = 0;
			
#ifdef MSDBG5
			FNX_PRINTF ("durxx = mstofr(user_durs[nphon]+4) durxx=%d\n", pDphsettar->durxx);
#endif
			
#ifdef DEBUG_USER_PROSODICS
			FNX_PRINTF ("\tFound user_dur[%s] = %3d frames in PHTIMING\n",
				phprint (phocur), pDphsettar->durxx);
#endif
			
			goto break3;
		}
		else if (pDph_t->user_durs[nphon] < 0)
		{
			do_syl_adjust = 1;
			prcnt = -(pDph_t->user_durs[nphon]>>1);
			durinh = ((inh_timing(phTTS,phocur) * 10) + 50) >> 6;
			pDphsettar->durxx = (prcnt * durinh) DIV_BY128;
			
			goto break3;
			
		}
		prcnt = 128;
		/* Convert inherent and minimum duration in msec to frames.*/
		/* Fixed overflow in 16 bits is not possible on these ones.*/
		
		durinh = ((inh_timing(phTTS,phocur) * 10) + 50) >> 6;
		durmin = ((min_timing(phTTS,phocur) * 10) + 50) >> 6;
		
		
		/* Additive increment */
		deldur = 0;
		/* Multiplicative constant (let 128 be 100%) */
	
		
		
		/* 
		* Rule 1: Pause durations depend on syntax
		*          Clause-initial pause should be minimal, i.e. NF64MS (enough
		*          time for initial fricative to build up amp gradually)
		*          Shortened to 0, except for fricitive and plosive in next phone
		*          we go do 7 ...
		*/
		if (phocur == GEN_SIL)
		{
			if ((pDphsettar->feanex & (FVOICD | FOBST)) || (pDphsettar->feanex & FPLOSV))
				
				dpause = 4;//NF7MS; 
			else
				dpause = 5;
			
			pDph_t->asperation = (pDph_t->asperation - BASE_ASP) / 10;
			
			/* Treatment of other than clause-initial pauses: */
			if (nphon > 1)
			{
				/* If this clause ends in a comma, use short pause */
				/* Note extra compause added if user command [:dv cp __] */
				if ((struclas & FBOUNDARY) == FCBNEXT)
				{
#ifdef MSDEBUG
					FNX_PRINTF ("asperation 1111 asperation=%d\n", pDph_t->asperation);
#endif
					
					if (pDph_t->asperation > MAX_ASP_COMMA)
						pDph_t->asperation = MAX_ASP_COMMA;
					else if (pDph_t->asperation < MIN_ASP_COMMA);
					
					pDph_t->asperation = MIN_ASP_COMMA;
#ifdef MSDEBUG
					FNX_PRINTF ("asperation is now screwed up 1111\n");
#endif
					dpause = pDph_t->nfcomma + pDph_t->compause + pDph_t->asperation;
				}
				/* End of clause has long pause if ends with "." "!" or "?" */
				/* Note extra perpause added if user command [:dv pp __] */
				if (((struclas & FBOUNDARY) & FSENTENDS) IS_PLUS)
				{
#ifdef MSDEBUG
					FNX_PRINTF ("asperation 2222 asperation=%d\n", pDph_t->asperation);
#endif
					if (pDph_t->asperation > MAX_ASP_PERIOD)
						pDph_t->asperation = MAX_ASP_PERIOD;
					else if (pDph_t->asperation < MIN_ASP_PERIOD);
					pDph_t->asperation = MIN_ASP_PERIOD;
#ifdef MSDEBUG
					FNX_PRINTF ("asperation is now screwed up 2222\n");
#endif
					dpause = pDph_t->nfperiod + pDph_t->perpause + pDph_t->asperation;	
				}
			}
			/* Make sentence-initial pause long if this is a new paragraph */
			else if (pDph_t->newparagsw != FALSE)
			{
				dpause = pDph_t->nfperiod;
			}
			
			pDph_t->asperation = 0;
			
			/* Effect of speaking rate greatest on pauses */
			
			arg1 = dpause;
			arg2 = pDphsettar->sprat1;
			dpause = mlsh1 (arg1, arg2);
			/* Minimum pause is 13 ms*/
			if (dpause < 2)
				dpause = 2;
			
			/* Skip over remaining duration rules if input is SIL */
			
			pDphsettar->durxx = dpause;
#ifdef MSDBG5
			FNX_PRINTF ("durxx = dpause durxx=%d\n", pDphsettar->durxx);
#endif
			
			durinh = pDphsettar->durxx;		/* for debugging print only */
			durmin = pDphsettar->durxx;
			goto break3;
		}

				

			
				/* Set duration from durinh, durmin, and percent */
				
				pDphsettar->durxx = (prcnt * (durinh - durmin)) DIV_BY128;
#ifdef MSDBG5
				FNX_PRINTF ("durxx = (prcnt * (durinh - durmin)) DIV_BY128 durxx=%d\n", pDphsettar->durxx);
#endif
				pDphsettar->durxx += durmin;   /* SHOULD BE DONE AFTER SPRATE ADJUSTMENT */
#ifdef MSDBG5
				FNX_PRINTF ("durxx += durmin durxx=%d\n", pDphsettar->durxx);
#endif
				//FNX_PRINTF ("durxx += durmin durxx=%d\n", pDphsettar->durxx);
				/* Rule for slow speaking lengthen inserted glotal stop*/
//				if(phocur == USP_Q && pKsd_t->sprate< 75)
//					pDphsettar->durxx = 1+((80-pKsd_t->sprate) );

break3:				
				/* Effect of speaking rate */
//				if ((pDphsettar->sprat0 != 180) && (pDphsettar->durxx != 0))
//				{
//					arg1 = pDphsettar->durxx;
//					arg2 = pDphsettar->sprat2;
//					if(pDph_t->number_words == 1)
//						arg2 += (pDphsettar->sprat2>>3);
//					pDphsettar->durxx = mlsh1 (arg1, arg2) + 1;		/* Round upwards */
#ifdef MSDBG5
					FNX_PRINTF ("durxx = mlsh1(arg1,arg2)+1 durxx=%d\n", pDphsettar->durxx);
#endif
					
					/* Effect of speaking rate on additive increment to dur */
//					arg1 = deldur;
//					arg2 = pDphsettar->sprat1;
//					deldur = mlsh1 (arg1, arg2);
//				}
				/* Add in rule-governed additive increment to dur  */
//				pDphsettar->durxx = pDphsettar->durxx + deldur;
#ifdef MSDBG5
				FNX_PRINTF ("durxx = durxx + deldur durxx=%d\n", pDphsettar->durxx);
#endif
				
				if (pDphsettar->durxx < 0 ) /*eab oct 93 found dur could get set =0 compromise*/
					pDphsettar->durxx=1;    /*over putting command later(safer) see comment above*/

					pDph_t->allodurs[nphon] = pDphsettar->durxx;
#ifdef why				
				if(((pDph_t->allofeats[nphon+1] & FSBOUND)
				||	pDph_t->allophons[nphon+1] == GEN_SIL)
				&& do_syl_adjust)
				{
					for (endcnt = nphon; stcnt - (endcnt); endcnt--)
					{
						
					//	FNX_PRINTF("ph=%d ",pDph_t->allophons[endcnt]); 
						
						if (phone_feature( pDph_t ,pDph_t->allophons[endcnt]) & FSYLL)
						{
							do_syl_adjust = 0;
							pDph_t->allodurs[endcnt] =(prcnt * (pDph_t->allodurs[endcnt])) DIV_BY128;
							if (pDph_t->allodurs[endcnt] <=6)
								pDph_t->allodurs[endcnt]=6;
							
							//FNX_PRINTF ("to  %d \n", ((pDph_t->allodurs[endcnt] * NSAMP_FRAME) / 10));
							break;
						}	
					}
						//	  FNX_PRINTF("set  syldur from %d to %d in %d adjusts.\n",
						//	  ((syldur)*64)/10,((syldur+(ncnt*adjust))*64)/10,ncnt ); 
						
						ncnt = 0;
						/* FNX_PRINTF("-- \n"); */
						stcnt = nphon;
						/* reset slydur */
						syldur = 0;
						sonocnt = 0;
					}
#endif 			
					pDph_t->longcumdur += (pDphsettar->durxx * NSAMP_FRAME);	/* Cum dur in waveform samples     */
	}	
}