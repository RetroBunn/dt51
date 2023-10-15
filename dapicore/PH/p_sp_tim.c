/* 
 ***********************************************************************
 *
 *                           Copyright ©
 *    © Digital Equipment Corporation 1996, 1997 All rights reserved.
 *    © SMART Modular Technologies 1999, 2000. All rights reserved.
 *	  Copyright © 2000-2001 Force Computers, Inc., a Solectron Company. All rights reserved.
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
 *
 ***********************************************************************
 *    File Name:    p_la_tim.c
 *    Author:		Matthew Schnee
 *    Creation Date:06-Jun-1996
 *
 *    Functionality:
 *		Spanish DURATION RULES
 *
 ***********************************************************************
 *    Revision History:
 *
 * Rev  Who     Date            Description
 * ---  -----   -----------     -------------------------------------------- 
 * 0001 DK 		09/01/1984	    Initial creation
 * 0002 DGC		12/27/1984		Modified for the 80186.
 * 0003 DGC		01/02/1985	    Added some conditional calls to the "mstofr"
 *                      		routine. Some of the conversions from MS to
 *                      		frames caused overflow on 16 bit machines.
 * 0004 DK		02/26/1985    	[nt] cluster too long
 * 0005 DK		03/18/1985     	period pause and comma pause code had a bug
 
 * 0006 MM		04/02/1985    	68000 hacks.
 * 0007 MM		05/29/1985     	Stuffed in the grotesque Spanish code.
 * 0008 GL		02/13/1996     	make sure pDph_t->allodurs[] will not go below zero.
 * 0009 MGS		06/06/1996		Moved spanish phtiming to here
 * 0010 SIK		07/12/1996  	Cleaning up and maintenance                    
 * 0011 EDB 	12/10/1996		Many changes...
 * 0012 EDB		01/10/1997		Add "NOTYET" block. 
 * 0013 EAB		10/12/1997      Added typing mode and remove obsolete prphdurs debug routine
 * 0014 EDB		10/19/1997	    use phTTS handler to replace pDph_t
 * 0015 EAB		05/12/1998		BATS 660 Fastalk alignment and SLOWTALK e_q lengthening
 * 0016 EAB		07/08/1998		added tcumdur stuff
 * 0018 EAB		07/14/1998 		Continued tuning this time I really changed tilt
 * 0019 EAB		07/13/1998		Found redundant tcumdur code that was not needed. It's calculated
 *								in phinton1/2 now.BATS 713 tcumdur addition removed
 * 0020 EAB		07/20/1998 		opied from  p_sp_tim.c after merge with _LA
 * 0021 eab		07/22/1998		Modified duration rules to support all levels of reduction on a monosylable
								and tuned up the syllable timed reference. 
 * 0022 EAB 	10/16/1998   	Tuned the Spanish
 * 0023 EAB 	10/27/1998   	In short comma phrases reduced the pause duration
 * 0024	EAB 	10/29/1998   	Fixed duration of vowel following another vowel Juan often lost perception of scond vowel
								also fixed duration of intervolcalic n		
 * 0025 EAB 	10/29/1998 		Further refinement of rules with Juan
 * 0026	EAB 	11/12/1998    	BATS 816 see notes with bats for details
 * 0027	MGS		04/13/2000		Changes for integrated phoneme set 
 * 0028	NAL 	04/14/2000   	Fix extern 'place' to match declarations in p_*_rom.c
 * 0029	EAB 	06/28/2000		Unified Phoneme Set Changes
 * 0030 CAB		10/18/2000		Changed copyright info
 * 0031 EAB 	10/7/2000 		Fix bug -thanks matt!
 * 0032 CAB		02/23/2001		Updated copyright info
 * 0033 CAB		02/23/2001		Removed duplicate and changed to USP_Q
 *
 */

#include "dectalkf.h"
#include "ph_def.h"
                              
/* Tables located in PHROM.C */
//extern short            *place;	   /* Phonetic "place" features */

#define   FVDSTOP (FVOICD+FOBST+FPLOSV+FCONSON+FBURST)
//#define DEBUGPHT
extern int min_timing(LPTTS_HANDLE_T phTTS, int phone);
extern int inh_timing(LPTTS_HANDLE_T phTTS, int phone);
//extern __inline short phone_feature(PDPH_T pDph_t, int phone);


/* 
 * This table contains durations for rule 2.
 */
const short dur_2_tab[] =
{
	N100PRCNT,						   /* Monosyllabic   */
	N80PRCNT,						   /* Bisyllabic     */
	N75PRCNT,						   /* Trisyllabic    */
	N67PRCNT						   /* Multisyllabic  */
};

/* 
 * This table contains durations for rule 3A.
 */

const short dur_3a_tab[] =
{
	/* Decreased all unstressed (no boundary) by 20%                  		   */
	N80PRCNT,						   /* unstressed, closed, no boundary next */
	N85PRCNT,						   /* unstressed, closed,    boundary next */
	N55PRCNT,						   /* unstressed, open,	  no boundary next */
	N80PRCNT,						   /* unstressed, open,      boundary next */
	/* Increased all stressed by 10%                                  		   */
	N117PRCNT,						   /* stressed, closed, no boundary next   */
	N132PRCNT,						   /* stressed, closed,    boundary next   */
	N120PRCNT,						   /* stressed,   open, no boundary next   */
	N160PRCNT						   /* stressed,   open,    boundary next   */
};


/* 
 * Rule 4a is a mess.  The tables are as follows:
 *      con_4a_class[]          Classifies each consonant into one
 *                              of six rule types.  The values are random
 *                              (they follow the original rule encoding).
 *      dur_4a_tab[]            Each rule type gives different values
 *                              for two "special" vowels, and for the others.
 *                              This table is indexed by the con_4a_class[]
 *                              code.
 * For example, suppose the sequence is [O CH] in an open syllable.
 * con_4a_class[CH] gives 2.
 * tst_4a_tabl[2].v1 equals [O] and the syllable is open, so the
 * duration index is set to 2 and the duration is thus
 * tst_4a_tab[2].dur[2].
 *
 * The values have the following "meaning":
 * 0    SON2 and NASAL (nasals)
 * 1    SON2 and not NASAL (Lateral and liquid)
 * 2    CH
 * 3    R
 * 4    OBST and PLOSIV (occlusives)
 * 5    OBST and not PLOSIV (voiceless fricitives)
 * 6    Not OBST (voiced fricitives)
 */

const short            con_4a_class[SPP_PH - SPP_WX + 1] =
{
	6, 6,							   /* WX YX                 	*/
	6, 1, 1, 0, 0, 0, 5, 5,			   /* RR  L LL  M  N NH  F  S   */
	5, 5, 6, 6, 6, 6, 4, 4,			   /* J TH BH DH GH YH  P  B    */
	4, 4, 4, 4, 2, 5, 3, 6,			   /* T  D  K  G CH  Y  R  Q    */
	6, 5, 0, 5, 6, 0, 5				   /* Z  W NX SH  V MX PH       */
};

/* 
 * durations in dur_4a_tab are organized as follows:
 * 0    not v1 or v2,   open syllable
 * 1    not v1 or v2, closed syllable
 * 2        v1 or v2,    open syllable
 * 3        v1 or v2,  closed syllable
 */


const struct rule_4a   dur_4a_tab[7] =
{
	  /* 0 */ 
 {SPP_U, SPP_I, N97PRCNT, N92PRCNT, N100PRCNT, N90PRCNT},
	  /* 1 */ 
 {SPP_U, SPP_I, N100PRCNT, N87PRCNT, N100PRCNT, N90PRCNT},
	  /* 2 */ 
 {SPP_O, SPP_U, N115PRCNT, N80PRCNT, N90PRCNT, N97PRCNT},
	  /* 3 */ 
 {SPP_A, SPP_E, N115PRCNT, N120PRCNT, N97PRCNT, N107PRCNT},
	  /* 4 */ 
 {SPP_I, SPP_E, N110PRCNT, N82PRCNT, N90PRCNT, N97PRCNT},
	  /* 5 */ 
 {SPP_I, SPP_E, N115PRCNT, N80PRCNT, N100PRCNT, N90PRCNT},
	  /* 6 */ 
 {SPP_A, SPP_O, N95PRCNT, N105PRCNT, N100PRCNT, N87PRCNT}
};

const short dur_6_tab[8] =
{
	  /* unstressed   stressed  */
	  /* mono- or bisyllabic    */
	N82PRCNT, N100PRCNT,			   /* I _          */
	N87PRCNT, N100PRCNT,			   /* U _          */
	  /* tri-  or multisyll.    */
	N74PRCNT, N90PRCNT,				   /* I _          */
	N78PRCNT, N90PRCNT				   /* U _           */
};

/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int PrcntOf(int pct, int val)
{
	unsigned short pct128[] = {
		0, 
		1, 3, 4, 5, 6, 8, 9, 10, 12, 13,
		14, 15, 17, 18, 19, 20, 22, 23, 24, 26,
		27, 28, 29, 31, 32, 33, 35, 36, 37, 38, 
		40, 41, 42, 44, 45, 46, 47, 49, 50, 51, 
		52, 54, 55, 56, 58, 59, 60, 61, 63, 64, 
		65, 67, 68, 69, 70, 72, 73, 74, 76, 77, 
		78, 79, 81, 82, 83, 84, 86, 87, 88, 90, 
		91, 92, 93, 95, 96, 97, 99, 100, 101, 102, 
		104, 105, 106, 108, 109, 110, 111, 113, 114, 115, 
		116, 118, 119, 120, 122, 123, 124, 125, 127, 128,
		129, 131, 132, 133, 134, 136, 137, 138, 140, 141,
		142, 143, 145, 146, 147, 148, 150, 151, 152, 154,
		155, 156, 157, 159, 160, 161, 163, 164, 165, 166,
		168, 169, 170, 172, 173, 174, 175, 177, 178, 179,
		180, 182, 183, 184, 186, 187, 188, 189, 191, 192,
		193, 195, 196, 197, 198, 200, 201, 202, 204, 205,
		206, 207, 209, 210, 211, 212, 214, 215, 216, 218,
		219, 220, 221, 223, 224, 225, 227, 228, 229, 230,
		232, 233, 234, 236, 237, 238, 239, 241, 242, 243,
		244, 246, 247, 248, 250, 251, 252, 253, 255, 256
	};

	if( pct <= 0 )
		return 0;
	if( val > sizeof(pct128)/sizeof(short) )
		return val;

	return (pct128[pct] * val) >> 7;
}

/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void sp_phtiming (LPTTS_HANDLE_T phTTS)
{
	int                     stcnt = 0;
	int                     syldur = 0;
	int                     ncnt = 0;
	int                     endcnt = 0;
	int                     vowcnt = 0;
	int                     adjust = 0;
	int                     index;	   /* Table pointer */
	int                     temp;
	const struct rule_4a    *tp;
	short                   strucsylcur=0;	/* Syllable structure     */
	short                   strucopensyl=0;	/* TRUE if open syllable  */
	short					arg1,arg2;	/* arguments for the phmath routines. */
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	short                   pholas = GEN_SIL, struclas=0, strboulas=0, strucstresslas=0;
	short                   fealas = GEN_SIL;
	short                   prcnt = 0, durinh = 0, durmin = 0, deldur = 0, nphon = 0;
	short                   phocur = 0, struccur = 0, strucboucur = 0, strucstresscur = 0;
	short					phonext=0, strucnex=0, strucbounex=0, strucstressnex=0;
	int						feacur = 0, feasyllabiccur = 0;
	short                   dpause = 0;
#ifdef NEWTYPING_MODE
	short					numbersonor;
	short					minsize;
#endif

	init_timing (phTTS);
	pDph_t->tcumdur =0;
	
#ifdef NEWTYPING_MODE
	numbersonor=0;
	for (nphon = 0; nphon < pDph_t->nallotot; nphon++)
	{
		feacur=phone_feature( pDph_t ,pDph_t->allophons[nphon]);
		if((feacur & FSONOR) IS_PLUS && pDph_t->allophons[nphon] != GEN_SIL)
			numbersonor +=1;
	}
#endif

	/* MAIN LOOP, for each output phoneme */
	for (nphon = 0; nphon < pDph_t->nallotot; nphon++)
	{
		if (nphon > 0)
		{
			pholas	 = pDph_t->allophons[nphon-1];
			struclas = pDph_t->allofeats[nphon-1];
			fealas	 = phone_feature(pDph_t, pholas);
			strboulas = struclas & FBOUNDARY;		// Boundary bit flags
			strucstresslas = struclas & FSTRESS;	// Stress bit flags
		}

		phocur = pDph_t->allophons[nphon];			// Get current phoneme
		struccur = pDph_t->allofeats[nphon];
		strucboucur = struccur & FBOUNDARY;			// Boundary bit flags
		feacur = phone_feature(pDph_t, phocur);
		feasyllabiccur = feacur & FSYLL;			// TRUE if +FSYLL
		strucstresscur = struccur & FSTRESS;		// Stress bit flags
		strucsylcur = struccur & FTYPESYL;
		strucopensyl = struccur & FOPEN_SYL;

		/* FNX_PRINTF("struc=%d bou=%d stress=%d syl=%d open=%d\n",struccur,strucboucur,strucstresscur,strucsylcur,strucopensyl); */
		/* FNX_PRINTF("feacur=%d feasyl=%d user_durs[%d]=%d\n",feacur,feasyllabiccur,nphon,pDph_t->user_durs[nphon]); */
		
		if( nphon < (pDph_t->nallotot - 1) )
		{
			pDphsettar->phonex_timing = phonext = pDph_t->allophons[nphon+1];
			pDphsettar->strucnex = strucnex = pDph_t->allofeats[nphon+1];
			pDphsettar->feanex = phone_feature(pDph_t, pDphsettar->phonex_timing);
			strucbounex = strucnex & FBOUNDARY;
			strucstressnex = strucnex & FSTRESS;
		}

		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
		/* Duration Rules                         						   */
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

		/* Use user-specified duration if one exists.                      */
		/* User durations can be huge; call the conversion routine.        */
		if (pDph_t->user_durs[nphon] != 0)
		{
			pDphsettar->durxx = mstofr (pDph_t->user_durs[nphon] + 4);

			goto break3;
		}                    
	
	
		/* Convert inherent and minimum duration in msec to frames.       */
		/* Fixed overflow in 16 bits is not possible on these ones.       */

		durinh = ((inh_timing(phTTS, phocur) * 10) + 50) >> 6;
		durmin = ((min_timing(phTTS, phocur) * 10) + 50) >> 6;
		/* Additive increment */
		deldur = 0;
		/* Multiplicative constant (let 128 be 100%) */
		prcnt = 100;

		/* Rule 1: Pause durations depend on syntax */
		if (phocur == GEN_SIL)
		{
			/* 
			 * Clause-initial pause should be minimal, i.e. NF64MS (enough 
			 * time for initial fricative to build up amp gradually) 
			 */
			dpause = NF64MS;

			/* Treatment of other than clause-initial pauses: */
			if (nphon > 1)
			{
				/* If this clause ends in a comma, use short pause */
				if (strboulas == FCBNEXT)
				{
					/* Note extra compause added if user command [:dv cp __] */
					dpause = pDph_t->nfcomma + pDph_t->compause;
				}
				/* End of clause has long pause if ends with "." "!" or "?"  */
				if ((strboulas & FSENTENDS) IS_PLUS)
				{
					/* Note extra perpause added if user command [:dv pp __] */
					dpause = pDph_t->nfperiod + pDph_t->perpause;
				}
				if(pDph_t->number_words <= 2)
					dpause = dpause>>1;

					
			}
			/* Make sentence-initial pause long if this is a new paragraph */
			else if (pDph_t->newparagsw != FALSE)
			{
				dpause = pDph_t->nfperiod;
			}
			/* Effect of speaking rate greatest on pauses */
			arg1 = dpause;
			arg2 = pDphsettar->sprat1;
			dpause = mlsh1 (arg1,arg2);

			/* Minimum pause is NF64MS */
			if (dpause < NF64MS)
				dpause = NF64MS;
			/* Skip over remaining duration rules if input is GEN_SIL 	*/
			pDphsettar->durxx = dpause;
			durinh = pDphsettar->durxx;	/* for debugging print only */
			durmin = pDphsettar->durxx;
			//prdurs (pDph_t, phocur, durinh, durmin, deldur, prcnt, 1);
			goto break3;
		}


		/* ===============  Vowel Rules ==============================

			Rule 2: if a syllabic segement, adjust duration dependent on
			the number of syllables.
		
		   =========================================================== */
		if ((feacur & FSYLL) IS_PLUS)
		{
			prcnt=mlsh1(dur_2_tab[strucsylcur >> FSYL_SHIFT],prcnt);
			/* 
			 * Rule 3: (for multi-syllabics).  Modify duration based
			 * on accent, structure of the syllable, and end of word.
			 */
			if (strucsylcur != FMONOSYL)
			{
				index = 0;
				if (strucboucur >= FWBNEXT)
					index++;
				if (strucopensyl IS_PLUS)
					index += 2;
				if (strucstresscur == FSTRESS_1 ||
					strucstresscur == FEMPHASIS )
					index += 4;
				prcnt=mlsh1(dur_3a_tab[index],prcnt);
			}
			else if( strucboucur == FWBNEXT &&
					 (strucstresscur == FSTRESS_1 || strucstresscur == FEMPHASIS) )
			{
				/* 
				 * Note: this doesn't apply at clause-final position.
				 */
				prcnt=mlsh1(N125PRCNT,prcnt);
			}
			if (strucstresscur == FSTRESS_2)
			{
				/* 
				 * Note: this doesn't apply at clause-final position.
				 */
				deldur = deldur + NF15MS;
			}


			if((((pDphsettar->phonex_timing &  PFONT) == (PFLA<<PSFONT))
				||
				((pDphsettar->phonex_timing &  PFONT) == (PFSP<<PSFONT)))
				&&
				(((phocur &  PFONT) == (PFSP<<PSFONT))
				||
				((phocur &  PFONT) == (PFLA<<PSFONT))))
			{


				/* 
				* Rule 4a.  Takes into account the effect of the next
				* segment on the duration of the vowel.  See comments
				* before the table for the gory details.
				* Note that rule 4a actually contains three separate
				* rules, one for stress, one for syllable structure,
				* and one for the next phoneme class.
				*
				* We know that phocur is a vowel!
				*/

				if ((pDphsettar->feanex & FCONSON) IS_PLUS)
				{
					//Noticeon the subttraction SP_WX is used instead of SPP_WX  as it does not
					//contain the language bits i.e. equi to SPP_WX & PVALUE
					//But this is ugly dangerous code and should be re-wrtiiten after release 
					// NOTe potentially added allophonic variation s suggested by the literature will
					//break 
					//eab 10/9/00 helpme

					tp = (struct rule_4a *) &dur_4a_tab[con_4a_class[(pDphsettar->phonex_timing&PVALUE) - SP_WX]];
					index = 0;
					if (tp->v1 == phocur
						|| tp->v2 == phocur)
						index += 2;
					if (strucopensyl IS_MINUS)
						index++;
					prcnt=mlsh1(tp->dur[index],prcnt);
				}
			}
			/* 
			 * Rule 4.  Take into account phrase-final position.
			 */
			if (strucboucur >= FPPNEXT)
			{
				prcnt=mlsh1(N120PRCNT,prcnt);
			}


			/* 
			 * Rule 5.  Homorganic vowel durations.
			 */
			if ((phocur == pDphsettar->phonex_timing
				 && strucboucur < FPPNEXT
				 && (struccur & FSBOUND) IS_MINUS)
				|| (phocur == pholas
					&& strboulas < FPPNEXT
					&& (struclas & FSBOUND) IS_MINUS))
			{
				prcnt=mlsh1(((strucstresscur == FSTRESS_1)? N80PRCNT : N67PRCNT),prcnt);
			}
			/* 
			 * Rule 6. Duration of the semiconsonant on dipthongs.
			 * Rule 7. Duration of the vowel in [vowel][semivowel] dipth.
			 */
			else if ((fealas & FSEMIV) IS_PLUS)
			{
				index = 0;
				if (strucsylcur >= FTRISYL)
					index = 4;
				if (pholas == SPP_WX || pholas == SPP_W)
					index += 2;
				if (strucstresscur != FSTRESS_1)
					index++;
				prcnt=mlsh1(dur_6_tab[index],prcnt);
			}
			/* 
			 * More dipthong hacking.  Shorten the vowel if
			 * it is the first part of a dipthong (next segment
			 * is yx or wx.)
			 */
			else if (((feacur & FVOWEL) IS_PLUS)
					 && ((struccur & FSBOUND) IS_MINUS)
					 && ((pDphsettar->feanex & FSEMIV) IS_PLUS))
			{
				prcnt=mlsh1(((strucstresscur == FNOSTRESS)? N85PRCNT : N90PRCNT),prcnt);
			}

			/* ============================================================== 
				Rule 9. Unstressed vowels.
			 
				An unstressed vowel in a vowel-vowel sequence is
				shortened if there isn't a boundary separating the
				two vowels.
			 
				If there are 2 consecutive strong unstressed vowels then
				they need to be shortened.

				The vowel is lengthened after ~n

			   ============================================================== */
			if (strucstresscur == FNOSTRESS)
			{
				if( (((pDphsettar->feanex & FSYLL) IS_PLUS) &&			// next phoneme is a vowel
					 ((pDphsettar->strucnex & FSBOUND) IS_MINUS) &&		// and not a boundary
					 (strucboucur == FNO_BOUNDARY)) 
					|| 
					(((fealas & FSYLL) IS_PLUS) &&						// last phoneme is a vowel
					 ((struccur & FSBOUND) IS_MINUS) &&					// and not a boundary
					 (strboulas == FNO_BOUNDARY)))
				{
					prcnt=mlsh1(N60PRCNT,prcnt);
				}
				else if( phocur == SPP_A || phocur == SPP_E || phocur == SPP_O )		// Strong vowel
				{
					if( strucstressnex == FNOSTRESS &&									// Unstressed
						(phonext == SPP_A || phonext == SPP_E || phonext == SPP_O) )	// Strong vowel
					{
						PH_DEBUG_2080_P1("sp_phtiming: phon %d, 1 of 2 strong unstressed vowels, reducing duration 50%%\n", nphon);
						prcnt = 50;		// I don't care about what other rules have already fired.  I want it at 50%
						durmin >>= 1;
					}
					else if( strucstresslas == FNOSTRESS &&								// Unstressed
							 (pholas == SPP_A || pholas == SPP_E || pholas == SPP_O) )	// Strong vowel
					{
						PH_DEBUG_2080_P1("sp_phtiming: phon %d, 2 of 2 strong unstressed vowels, reducing duration 50%%\n", nphon);
						prcnt = 50;		// I don't care about what other rules have already fired.  I want it at 50%
						durmin >>= 1;
					}

				}
			}

			// Lengthen all vowels after ~n                4-Feb-86
			if (pholas == SPP_NH)
			{
				prcnt=mlsh1(N125PRCNT,prcnt);
			}
		}
		/* End of vowel rules             */
		
		
		/* ---------------------------
		         Consonant rules.
		   --------------------------- */
		if ((feacur & FCONSON) IS_PLUS)
		{
			if( phocur == SPP_R )
			{
				if( (fealas & FPLOSV) IS_PLUS )			// plosive + R
				{
					if(pholas == SPP_K)
						deldur += 8;
					else
						deldur += 4;
				}
				else if( (pDphsettar->feanex & FPLOSV) IS_PLUS &&	// R + stop
						 (pDphsettar->feanex & FBURST) IS_PLUS )
				{
					// I want the /r/ before a stop to be 8 frames long (shorter)
					// otherwise it sounds too long
					if( pDph_t->allodurs[nphon] >= 8 )
					{
						prcnt = 128;
						durinh = 8;
						durmin = 0;
					}
				}
			}

			if( phocur == SPP_K &&						// K + S
				pDph_t->allophons[nphon+1] == SPP_S )
			{
				deldur = -5;
				prcnt=mlsh1(N10PRCNT,prcnt);
			}

			if (phocur == SPP_S)
			{
				/* 
				 * Rule 10. adjust duration of [s].
				 */
				temp = N100PRCNT;
				if( pholas == SPP_S ||						// shorten s in an s + s combination
					pDphsettar->phonex_timing == SPP_S )
				{
					temp = N30PRCNT;
					durmin >>= 1;
				}

				// this rule doesn't make much sense
				else if( (strucopensyl IS_PLUS) ||			// Open syll. - CV
						 (strucsylcur != FMONOSYL &&		// or end of multi-syllable word 
						  strucboucur >= FWBNEXT) )
				{
					temp = N92PRCNT;
				}
				else if( (strucopensyl IS_MINUS) &&			// ex. casa ???
						 strucboucur < FWBNEXT)
				{
					temp = N70PRCNT;
				}
				if ((pDphsettar->feanex & FPLOSV) IS_PLUS)	// s + plosive
				{
					temp = N78PRCNT;
				}
				prcnt=mlsh1(temp,prcnt);
			}
			else if (phocur == SPP_R || phocur == SPP_RR)
			{
				/* 
				 * Rule 11. Set duration for /r/ and /rr/.
				 * R  before boundary or consonant is longer.
				 * R  otherwise is a short trill, except after
				 *      certain consonants, where it is a flap.
				 * RR lengthens before boundary.
				 *
				 * Word-init RR is about one trill shorter. 28-Jul-86
				 */
				temp = N100PRCNT;
				if (phocur == SPP_R)
				{
					if( (strucboucur >= FMBNEXT) 
						|| 
						(((pDphsettar->feanex & FCONSON) IS_PLUS) &&
						 ((pDphsettar->feanex & FPLOSV) IS_MINUS)) )
					{
						temp = N150PRCNT;
					}
					else if( pholas == SPP_S || 
							 pholas == SPP_J || 
							 pholas == SPP_TH)
					{
						temp = N60PRCNT;
					}
					else if( (pDphsettar->feanex & FVOWEL) IS_PLUS )	// R should be a longer before a vowel
					{
						temp = N150PRCNT;
					}
				}
				else		/* if (phocur == SPP_RR) */
				{
					if (strucboucur >= FMBNEXT)
						temp = N120PRCNT;
					else if ((struccur & FWINITC) IS_PLUS)
						deldur -= NF30MS;
				}
				prcnt=mlsh1(temp,prcnt);
			}
			else if ((phocur == SPP_L || phocur == SPP_N)
					 && (strucopensyl IS_PLUS))
			{

				/* 
				 * Rule 12.  Adjust duration of [l] and [n]
				 * in open syllables.
				 */

				/* percentage(N85PRCNT); */

				prcnt=mlsh1(N105PRCNT,prcnt);
			}
			else if ((feacur & FSONOR) IS_MINUS)
			{
				/* 
				 * Rule 13. Adjust durations for all voiceless
				 * consonants except [s]:
				 * Shorten after N                          28-May-86
				 * Shorten unstressed after sonorants       23-Jul-86
				 * in unstressed syllable, but not after
				 * silence.
				 */
				temp = N100PRCNT;
				//	rule to shorten a stop after a nasal
				if( (fealas & FNASAL) IS_PLUS && 
					(feacur & FSTOP))
				{
					prcnt=mlsh1(N50PRCNT,prcnt);
					durmin = durmin >> 1;
				}
				else if( (feacur & FBURST) IS_PLUS && 
						 (fealas & FSONOR) IS_PLUS && 
						 pholas != GEN_SIL && 
						 strucstresscur == FNOSTRESS )
				{
					temp = N70PRCNT;
				}
				else if( (pDphsettar->phonex_timing == SPP_R || 
						  pDphsettar->phonex_timing == SPP_L) && 
						 (strucopensyl IS_PLUS))
				{
					temp = N90PRCNT;
				}
				else if (strucopensyl IS_MINUS)
				{
					temp = N110PRCNT;
				}

				prcnt=mlsh1(temp,prcnt);
			}
			/* 
			 * New geminate rule (first try)
			 * Rule 14.  Adjust durations for geminates.
			 */
			if( (phocur == pDphsettar->phonex_timing || phocur == pholas) &&
				strucboucur < FWBNEXT &&
				strboulas < FWBNEXT)
			{
				prcnt=mlsh1(((strucstresscur == FSTRESS_1)? N80PRCNT : N67PRCNT),prcnt);
			}

			if ((feacur & FNASAL) IS_PLUS)
			{
				// Lengthen [m],[n] when phrase final
				if( phocur != SPP_NH &&					
					(struccur & FBOUNDARY) >= FVPNEXT)
				{
					prcnt=mlsh1(N125PRCNT,prcnt);
				}
				// Shorten nasal when [-syll, -stop]
				else if( (pDphsettar->feanex & (FSYLL | FBURST)) == 0)
				{
					prcnt=mlsh1(N70PRCNT,prcnt);	/* Just a guess          */
				}
				/* eab 3-94 new rule needs more verification and perhaps refinement nasal in front of plosive gets shortened */
				else if ((pDphsettar->feanex & FPLOSV) IS_PLUS)
				{
					temp = N70PRCNT;
					prcnt=mlsh1(temp,prcnt);
				}
			}

			if((phone_feature( pDph_t,pDph_t->allophons[nphon+1]) & WBOUND) IS_PLUS)
			{
				//DOn't include stops or bursts 
				if(pDph_t->allophons[nphon+2] == pDph_t->allophons[nphon+1])
				{
					/* two in a row so shorten one given the effect
					of overall actually the longest*/
					if( phone_feature( pDph_t,pDph_t->allophons[nphon+1]) & FBURST )
						deldur=-NF30MS;
				}
			}

			// Stop gap needs to be shortened when we have 2 consecutive unvoiced stops
			if( (feacur & FPLOSV) IS_PLUS &&
				(feacur & FVOICD) IS_MINUS )
			{
				if( ((pDphsettar->feanex & FPLOSV) IS_PLUS && (pDphsettar->feanex & FVOICD) IS_MINUS) ||
					((fealas & FPLOSV) IS_PLUS && (fealas & FVOICD) IS_MINUS) )
				{							// (example: aceptar)
					deldur = -(durinh/4);	// subtract 25% of the inherent duration
					durmin = durmin >> 1;	// when we have a PLOSV+PLOSV combination
				}
			}

		}	// current phoneme is a consonant
		/* End of consonant rules */
		
		// lengthen stressed vowels
		if( (strucstresscur == FSTRESS_1 || strucstresscur == FEMPHASIS) &&
			(feacur & FVOWEL) IS_PLUS )
		{
			arg1 = prcnt;
			arg2 = N150PRCNT;
			deldur += 2;
			prcnt = mlsh1 (arg1, arg2);
		}
		/* Finish up */
		

#if 0
		// This method gives us a true percentage so that we can calculate 
		// things more accurately.  If we decide that we like it then we should 
		// go through all of the NXXPRCNT values and modify them by 0.78125
		prcnt = (short)((prcnt * 0.78125) + 0.5);
		pDphsettar->durxx = PrcntOf(prcnt, durinh);
		if( pDphsettar->durxx < durmin )
			pDphsettar->durxx = durmin;
#else
		/* Set duration from durinh, durmin, and percent */
			pDphsettar->durxx = (prcnt * (durinh - durmin)) DIV_BY128;
			pDphsettar->durxx += durmin;
#endif

		/* Effect of speaking rate */
		if ((pDphsettar->sprat0 != 180) && (pDphsettar->durxx != 0))
		{
			arg1 = pDphsettar->durxx;
			arg2 = pDphsettar->sprat2;
			pDphsettar->durxx = mlsh1 (arg1,arg2) + 1;	/* Round upwards */

			/* Effect of speaking rate on additive increment to dur */
			arg1 = deldur;
			arg2 = pDphsettar->sprat1;
			deldur = mlsh1 (arg1,arg2);
		}
		/* Add in rule-governed additive increment to dur  */

		pDphsettar->durxx += deldur;
		/* for debuggin spanish rate stuff eab */
		/* FNX_PRINTF("%d durmin, %d deldur\n, ",durmin,deldur); */


break3:


		/* Check for gross error */
		if (pDphsettar->durxx < 0)
		{
			pDphsettar->durxx = 2;
		}
		pDph_t->allodurs[nphon] = pDphsettar->durxx;	   /* Save in array for phonetic comp */
		if (pDph_t->allophons[nphon] != GEN_SIL)	   			   /* don't count silence 			  */
		{
			/* FNX_PRINTF("add %d for phon %d\n",pDphsettar->durxx,pDph_t->allophons[nphon]); 	  */
			syldur += pDphsettar->durxx;
		}
		/* 
		 * if( pDph_t->allophons[nphon] > 0 && pDph_t->allophons[nphon] <= 7 )      
		 * don't count silence 
		 */
		/* Instead of counting vowels now count sonorants */
		if ((feacur & FSONOR) IS_PLUS && pDph_t->allophons[nphon] != 0)
		{
			/* FNX_PRINTF("+voe on  %d vowcnt=%d\n",pDph_t->allophons[nphon],vowcnt); */
			vowcnt++;
		}

		//EAB 11/20/98 Found that consonants before vowel are also marked with stress and these we want to ignore here
		if( pDph_t->number_words >= 3)		
		{
			//the syl bounds are not properly marked so lets use vowel instead
			//if (((pDph_t->allofeats[nphon] & FISBOUND) && (nphon != 0) || (nphon == pDph_t->nallotot - 2)))
			if (((phone_feature( pDph_t,pDph_t->allophons[nphon]) & FVOWEL) IS_PLUS )|| (nphon == pDph_t->nallotot - 2))
			{
				/* FNX_PRINTF("strucc=%o of phon %d at %d",struccur,pDph_t->allophons[nphon],nphon); */
#ifdef DEBUGPHT
#if defined (WIN32) && defined (PRINTFDEBUG)
				WINprintf (" 2fbound struccur%o, p= %d\n", struccur, pDph_t->allophons[nphon]);
				WINprintf ("syldur = %d \n ", (syldur * 64) / 10);
				WINprintf ("vowcnt=%d\n", vowcnt);
#endif
#endif
				switch (vowcnt)
				{
				case 1:

					adjust = ((pDph_t->timeref - (syldur >> 1)) >> 1);
					break;
				case 2:
					adjust = ((pDph_t->timeref - (syldur >> 1)) >> 1);
					break;
				case 3:
					/* do 3/8 instead of divide by 3 */
					adjust = ((pDph_t->timeref - (syldur >> 1)) >> 3) * 3;
					break;
				case 4:
					adjust = ((pDph_t->timeref - (syldur >> 1)) >> 2);
					break;
				case 5:
					adjust = ((pDph_t->timeref - (syldur >> 1)) >> 1);
					break;

				default:

#ifdef DEBUGPHT
					FNX_PRINTF ("WHY HERE??");
					FNX_PRINTF ("vowcnt=%d phon= %d nphon= %d\n", vowcnt, pDph_t->allophons[nphon], nphon);
					FNX_PRINTF ("vowcnt=%d phon= %d nphon= %d\n", vowcnt, pDph_t->allophons[nphon], nphon);
#endif

					/* adjust=0; */ /*turns off syllable timed rythum*/
					adjust = adjust>>1;
					break;
				}
				/* 0015 EAB     05/11/98		Added in Fasttalk time alignement feature */
				/* BATS 660 ADD FASTTALK*/ /* Test with Juan*/
				//if (pDphsettar->sprat0 <= 250) /* note above 250 sprat0=250+(sprat-250)>>1 */
				//	{
				//	adjust=0; /* NEED TO ADD AS AN ADJUSTABLE PARAMETER FOR MORE TIMING.*/
				//	}
				/*	else*/ if(pDphsettar->sprat0 >= 325)
					adjust=adjust>>1;
				else if(pDphsettar->sprat0 >= 250)
					adjust=adjust>>2;

				if (pDph_t->user_durs[nphon] != 0 || pDph_t->f0mode == SINGING)
				{
					adjust = 0;
				}

				/* FNX_PRINTF("stcnt %d endcnt %d \n",stcnt,nphon); */

				adjust = 0;

				for (endcnt = nphon; stcnt - (endcnt); endcnt--)
				{
					/* dologphoneme(pDph_t->allophons[endcnt],0,0); */
					/* FNX_PRINTF("nphon %d ",endcnt); FNX_PRINTF("p=%d ",pDph_t->allophons[endcnt]); */

					/* FNX_PRINTF("ph=%d ",pDph_t->allophons[endcnt]); */
					/* if( pDph_t->allophons[endcnt] <= 7 && pDph_t->allophons[endcnt] >0) */
					/* change from adjusting just vowels to any sonorant */


					if ((phone_feature(pDph_t, pDph_t->allophons[endcnt]) & FSONOR) IS_PLUS)
					{
						/* 
						* FNX_PRINTF("set  %d dur %d syldur=%d adj=%d \n",
						* pDph_t->allophons[endcnt],pDph_t->allodurs[endcnt],
						* (syldur*64)/10,adjust); 
					 */

#ifdef DEBUGPHT
						FNX_PRINTF ("set  %d dur %d syldur=%d adj=%d", pDph_t->allophons[endcnt], pDph_t->allodurs[endcnt], (syldur * 64) / 10, adjust);
#endif


						pDph_t->allodurs[endcnt] += adjust;
						/* If real short to beign with don't touch*/
						if(pDph_t->allodurs[endcnt] <=6)
						{
#ifdef DEBUGPHT
#if defined (WIN32) && defined (PRINTFDEBUG)
							WINprintf("BINGO");
#endif
#endif
							pDph_t->allodurs[endcnt]=6;
						}
						/* if(pDph_t->allodurs[endcnt] <= 5) pDph_t->allodurs[endcnt]=5; */
#ifdef DEBUGPHT
						FNX_PRINTF ("to  %d \n", ((pDph_t->allodurs[endcnt] * NSAMP_FRAME) / 10));
#endif
						ncnt++;
					}
				}

#if defined (WIN32) && defined (PRINTFDEBUG)
				/* WINprintf("set  syldur from %d to %d in %d adjusts.\n",
				((syldur)*64)/10,((syldur+(ncnt*adjust))*64)/10,ncnt ); */
#endif

				ncnt = 0;
				/* FNX_PRINTF("-- \n"); */
				stcnt = nphon;
				/* reset slydur */
				syldur = 0;
				vowcnt = 0;

			}
		}
		
#ifdef NOTYPING_MODE

		if(phTTS->bInTypingMode == TRUE)
		{
		if(pDph_t->nallotot >3)
				{
		minsize= 20/(pDph_t->nallotot-1);
		if (minsize < 4)
			minsize=4;

		if((feacur & FSYLL) IS_PLUS && nphon == 1) 
			pDph_t->allodurs[nphon]= minsize;
			}
		}
#endif /* typping mode*/

#ifdef DEBUG_PHTIMING
		FNX_PRINTF ("final dur of allodurs[%d]%d = %d\n",nphon, pDph_t->allophons[nphon], pDphsettar->durxx * 64 / 10);
		FNX_PRINTF ("final dur of allodurs[%d]%d = %d\n",nphon, pDph_t->allophons[nphon], pDph_t->allodurs[nphon] * 64 / 10);
		FNX_PRINTF ("user_durs[%d]=%d\n",nphon,pDph_t->user_durs[nphon]);

#endif

        /* Cum dur in waveform samples     */
		pDph_t->longcumdur += (pDphsettar->durxx * NSAMP_FRAME);	   
		
		//Specail rule for dipthong-identified by no stress
		if( phone_feature( pDph_t , pDph_t->allophons[nphon-1 ]) & FSYLL
			&&  ((struclas & FSTRESS_1) IS_MINUS)
			&& (pDph_t->allofeats[nphon-1] & FSBOUND) != FSBOUND
			&&( phone_feature( pDph_t , pDph_t->allophons[nphon ]) & FSYLL))
		{
			pDph_t->allodurs[nphon ] += pDph_t->allodurs[nphon]>>2;
			pDph_t->allodurs[nphon -1] -= pDph_t->allodurs[nphon-1 ]>>2;
		}
	}
	/* post processing timing for syllable timed rythm */
	/* debug code */
    /* prphdurs (pDph_t) */	
}

                               
