/* 
 ***********************************************************************
 *
 *                           Copyright �
 *    Copyright � 2000-2001 Force Computer, Inc., a Solectron company. All rights reserved.
 *    � Digital Equipment Corporation 1996, 1997. All rights reserved.
 *
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Force Computers Incoporated and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Force or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:    p_kr_st1.c
 *    Author:		Matthew Schnee
 *    Creation Date:04-Jun-1996
 *
 *    Functionality:
 *	  Korean specific functions from phsettar.c
 *
 ***********************************************************************
 *
 *	Rev	Who		Date		Description
 *	---	-----	-----------	--------------------------------------------
 *	001	MGS		06/04/1996	file created
 *	002 MGS		06/18/1996  moved setloc, vv_coartic_across_c, shrdur to ph_sttr2.c
 *  003 SIK		07/12/1996  Cleaning up and maintenance
 *  004	EAB		07/31/1996	Fixed typo with silence for single vowel phrases 
 *  005	GL		10/30/1996  Merge the changes from V43 code base.
 * 	006 EAB     02/06/1997 Isolated problem that was causing spa and pa to have the same VOT time.
 *  007 EDB		10/19/1997	use phTTS handler to replace pDph_t
 *  008 EAB		05/23/1998	The BATS660 found a problem with the level of the silenced glotal
 *							stop in SLOWTALK in US ENGLISH too
 *  009 EAB		05/18/1998  BATS249 removed unused variable pholm2.
 *	010  EAB	05/20/1998  BATS681  Remove unneeded code--debugforward && debugbackwards
 *  010 EAB	    			Reduced level of hardcoded voicebar and modified aspiration levels for new voice
 *  011 EAB 	02/03/1999 	Added in code suggested by Dennis including supplyinfg a weak burst for df and th
 *  012 EAB 	03/26/1999 	BATS 878 Fixed the burst-plosive and plosive-plosive problem 
 *  013	MGS		04/13/2000	Changes for integrated phoneme set 
 *  014 NAL		06/12/2000	Warning removal
 *  015 EAB     06/28/2000  Unified Phoneme Set Changes     
 *  016 CHJ		07/20/2000	Removed & PVALUE when comparing to USP_*. The language bits need to be set.
 *  017 CAB		10/18/2000	Changed copyright info and formmated comments
 *	018	MGS		12/13/2000	Further optimization on gettar
 *	019	MGS		01/18/2001	Removed arg1 arg2 and arg3 from calculations
 *	020 eab		07/10/2001	BATS 982 gettar re-written to better support unified phonemes 
 *	021	MGS		04/11/2002	ARM7 port
 */

#include "dectalkf.h"
#include "ph_def.h"

#define begtyp(a,b) (pDph_t->cur_speaker[(b)>>8]->begtyp[(b)&0x00FF])
#define endtyp(a,b) (pDph_t->cur_speaker[(b)>>8]->endtyp[(b)&0x00FF])
#define burdr(a,b) (pDph_t->cur_speaker[(b)>>8]->burdr[(b)&0x00FF])
#define place(a,b) (pDph_t->cur_speaker[(b)>>8]->place[(b)&0x00FF])
#define ptram(a,b) (pDph_t->cur_speaker[(b)>>8]->ptram[(b)&0x00FF])
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* C.                      G E T T A R                              	 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
 
/*
 *      Function Name: gettar()      
 *
 *  	Description: Get target value (or a pointer to first value of diphthong specification 
 * 					 (do not compute any coarticulatory influences of adjacent phones)         
 *      Arguments: PDPH_T pDph_t, 
 *				   short nphone_temp
 *
 *      Return Value: short 
 *
 *      Comments:
 *
 */
//extern const short us_place[];

int kr_gettar (LPTTS_HANDLE_T phTTS, int nphone_temp)
{
	short                   phone_temp, phlas_temp, phnex_temp,tartemp=0, pphotr, npar;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	const short *kr_place=pDph_t->cur_speaker[PFKR]->place;

// if we're at beggining silence then sil value is the value of the next 
	//phone because we anticipate

	phlas_temp = get_phone(pDph_t,nphone_temp - 1);
	phone_temp = get_phone(pDph_t,nphone_temp);
	phnex_temp = get_phone(pDph_t,nphone_temp + 1);

	npar = pDphsettar->np - &PF1;
	if (pDphsettar->np < &PFZ)                      
		pphotr = (npar) * KR_TOT_ALLOPHONES;
	else
		pphotr = (npar - 1) * KR_TOT_ALLOPHONES;
		/* No table entries for PAP parameter */

	/* GETTAR:  F1, F2, F3, B1, B2, B3 */
	if ((pDphsettar->par_type = partyp[npar]) IS_FORM_FREQ_OR_BW)
	{
		
		if ((tartemp = pDph_t->p_tar[(phone_temp & PVALUE)  + pphotr]) < -1)
		{
			return (tartemp);		   
		}
		

		if (tartemp < -1)
		{
			tartemp = pDph_t->p_diph[-tartemp];
		}
#if (defined  INTEGER || !(defined HLSYN) )
		/* Fricatives have higher F1 if preceeded by a vowel */
		if ((npar == F1 - 1)
			&& ((phone_feature( pDph_t,phone_temp ) & FOBST) IS_PLUS)
			&& ((phone_feature( pDph_t,phone_temp ) & FSTOP) IS_MINUS)
			&& ((phone_feature( pDph_t,phlas_temp ) & FSYLL) IS_PLUS))
		{
			tartemp += 40;
		}
	
		/* Special rule for B2 of \n/ before non-front vowels */
		if ((((phone_temp) == KRP_N) || ((phone_temp) == KRP_NX))
			&& (npar == B2 - 1))
		{
			if (begtyp(pDph_t,phnex_temp) != 1)
			{
				tartemp += 60;
			}
		}
		/* Special rule for B3 of \n/ adjacent to high-front vowels */
		if ((((phone_temp) == KRP_N) || ((phone_temp) == KRP_NX) || ((phone_temp) == KRP_NX))
			&& (npar == B3 - 1))
		{
			if (((kr_place[phnex_temp & PVALUE] & F2BACKI) IS_PLUS)
				|| ((kr_place[(phlas_temp & PVALUE)] & F2BACKF) IS_PLUS))
			{
				tartemp = 1600;
			}
		}
	}
	/* 
	 * eab do nasals differently by nasalizing vowel before it and then 
	 * reduce dur on n not vowel in rule 22 context. The code actually nasalizes
	 * anything in front of it 
	 */
	/* GETTAR:  FZ */
	else if (pDphsettar->par_type IS_NASAL_ZERO_FREQ)
	{
		tartemp = NON_NASAL_ZERO;				   /* Default for non-nasalized, cancel FP=280 */
		if ((phone_feature( pDph_t  ,phone_temp) & FNASAL) IS_PLUS)
		{
			tartemp = NASAL_ZERO_CONS;			   /* Value dur nasal murmur (527=max) */
		}
    /* if ((pDphsettar->phonex == N  || pDphsettar->phonex == M) && ((phone_temp & PVALUE) != R )) { tartemp = 300; }        */
	}
	/* GETTAR:  AV, AP */
	else if (pDphsettar->par_type IS_AV_OR_AH)
	{
		/* Rules for voicing amplitude */
		if (npar == AV - 1)
		{
			tartemp = pDph_t->p_tar[(phone_temp & PVALUE) + pphotr];
//			FNX_PRINTF(" %d is av AT %d PHONE_TEMP\n",tartemp,phone_temp);
			/* 5/13/98 EAB The glotal stop in this instance goes all the way to perceived silence
			for some reason it was too strong so I fixed it*/

			if(pKsd_t->sprate <100)
				if ((phone_temp) == USP_Q) 
					tartemp -=30;
			/* Dummy vowel has less intensity */
			if ((pDph_t->allofeats[nphone_temp ] & FDUMMY_VOWEL) IS_PLUS)
			{
				tartemp -= 12;
			}
			/* Voiced stop devoiced if preceding seg voiceless */
			if (((phone_feature( pDph_t,phone_temp) & FPLOSV) IS_PLUS)
				&& ((phone_feature( pDph_t,phlas_temp) & FVOICD) IS_MINUS))
			{
				tartemp = 0;
			}
			

	
		
	}

#endif	
	
#ifndef HLSYN
	/* Rules for aspiration amplitude */
		else
		{
			if ((phone_temp) == KRP_HX)
			{
				tartemp = 57;
				if (begtyp(pDph_t,phnex_temp)  != 1)
				{
					tartemp = 58;	   /* Stronger asp before +back */
				}
			}
			else
			{
				tartemp = 0;
			}
		}
#endif
	}
#if !defined HLSYN && !defined INTEGER
	/* GETTAR:  A2, A3, A4, A5, A6, AB */
	else if (pDphsettar->par_type IS_PARALLEL_FORM_AMP)
	{
		/* If ptram >0, it is a pointer in obstruent array taram */
		if ((pDphsettar->np != &PTILT) && ((tartemp = ptram(pDph_t,phone_temp)) > 0))
		{
			short begtypnex = begtyp(pDph_t,phnex_temp) - 1;
			if (phnex_temp  == GEN_SIL)
				begtypnex = endtyp(pDph_t,phlas_temp ) - 1;
			if (begtypnex == 4)
				begtypnex = 2;
			tartemp += (npar - A2 + 1 + (6 * begtypnex));
			tartemp = pDph_t->p_amp[tartemp];

			/* Burst has less intensity if dummy vowel next */
			if ((pDph_t->allofeats[nphone_temp + 1] & FDUMMY_VOWEL) IS_PLUS)
			{
				if (tartemp >= 3)
				{
					tartemp -= 3;
				}
			}
		}
		/* GETTAR:  TLT */

		/* Source spectral tilt: highly tilted for obstruents */
		/* (Voiced obstruents are special case, set F1=0 to signal voicebar) */
		if (pDphsettar->np == &PTILT)
		{
			tartemp = 0;
			if ((phone_temp ) == GEN_SIL)
			{
				tartemp = 0;
			}
			/* eab hx energy too high at high frequency try controling with tilt */
			if ((phone_temp ) == KRP_HX)
			{
				tartemp = 20;
			}

			else if ((pDph_t->allofeats[nphone_temp] & FDUMMY_VOWEL) IS_PLUS)
			{
				tartemp = 10;
			}
			else if ((phone_feature( pDph_t,phone_temp ) & FOBST) IS_PLUS)
			{
				tartemp = 7;
				if (((phone_feature( pDph_t,phone_temp) & FVOICD) IS_PLUS)
					&& (((phone_feature( pDph_t,phone_temp) & FPLOSV) IS_PLUS)
						|| (pDphsettar->phcur == USP_JH)))
				{
					tartemp = 40;	   /* Max tilt for [b,d,g] */
				}
			}
			else if ((phone_feature( pDph_t,phone_temp ) & FNASAL) IS_PLUS)
			{
				tartemp += 6;		   /* Tilt down nasal murmurs */
				}			        

/*	      Female front vowels should be tilted down slightly */
			else if 
			((begtyp(pDph_t,phone_temp ) == 1) || (endtyp(pDph_t,phone_temp) == 1)) 
			{
					tartemp += 6;
			}
				else
				{
					tartemp += 3;
				}
		}
	}
#endif //hlsyn
	return (tartemp);
}

/*
 *      Function Name: special_coartic()      
 *
 *  	Description: 
 *
 *      Arguments: 	PDPH_T pDph_t, 
 *					short nfon, 
 *					short diphpos
 *
 *      Return Value: 
 *
 *      Comments:
 *
 */
short kr_special_coartic (PDPH_T pDph_t, short nfon, short diphpos)
{
	/* Note: Gen coartic of 5% with adjacent segs elsewhere, so stuff here is big */
	/* This routine is only called if the current segment is diph (i.e. a vowel) */

	short                   temp, fonnex, foncur, fonlas;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
//	extern const short us_place[];
	const short *us_place=pDph_t->cur_speaker[PFKR]->place;

	temp = 0;
	foncur = get_phone(pDph_t, nfon);
	fonnex = get_phone(pDph_t, nfon + 1);
	fonlas = get_phone(pDph_t, nfon - 1);


	/* F3 target of selected vowels */
	if (pDphsettar->np == &PF3)
	{
		if (((phone_feature( pDph_t,foncur) & FVOWEL) IS_PLUS) && (foncur != USP_RR))
		{
			if (((fonlas == USP_W) || (fonlas == USP_R) || (fonlas == USP_RX))
				|| ((fonnex == USP_W) || (fonnex == USP_R) || (fonnex == USP_RX)))
			{
				temp = -150;
			}
		}
	}
#ifndef HLSYN
	/* F2 target of selected vowels */
	if (pDphsettar->np == &PF2)
	{
		/* Front vowel F2 target lowered before [LX] */
		if (fonnex == USP_LX)
		{
			if (((foncur >= USP_IY) && (foncur <= USP_AE)) || (foncur == USP_IX))
			{
				temp = -150;
			}
			if (((foncur == USP_AY) || (foncur == USP_OY))
				&& (diphpos == 1))
			{
				temp = -250;
			}
			if (((foncur == USP_AY) || (foncur == USP_OY))
				&& (diphpos > 1))
			{
				temp = -350;

			}
		}
	
		/* [UW] F2 target raised adjacent to an alveolar */
		if (foncur == KRP_UW)
		{
			if ((us_place[fonlas & PVALUE] & FALVEL) IS_PLUS)
			{
				temp = 200;
			}
		}
		if ((foncur == KRP_UW)
			|| ((foncur == KRP_YU) && (diphpos > 0)))
		{
			if ((us_place[fonnex  & PVALUE] & FALVEL) IS_PLUS)
			{
				temp += 200;
			}
		}
		/* Effects are greater for unstressed vowels */
		if ((pDph_t->allofeats[nfon] & FSTRESS) IS_MINUS)
		{
			temp += (temp >> 1);

			/* Unstressed YU has a fronted U part */
			if ((foncur == KRP_YU) && (diphpos > 0))
			{
				temp = 400;
			}
		}
		/* Reduce effects for phrase-final stressed vowels */
		else if ((pDph_t->allofeats[nfon] & FBOUNDARY) >= FVPNEXT)
		{
			temp = temp >> 1;
		}
		/* Maximum change should not be excessive */
		if (temp > 400)
			temp = 400;
		if (temp < -400)
			temp = -400;
	}
#endif
	return (temp);
}

/*
 *      Function Name: forw_smooth_rules()      
 *
 *  	Description: Determine parameters of forward smoothing  
 *					 f(pholas,pDphsettar->phcur)
 *
 *      Arguments:	PDPH_T pDph_t, 
 *					short shrif, 
 * 					short pholas,
 *				   	short fealas, 
 *				   	short feacur, 
 *				   	short struclas,
 *				   	short struccur, short feanex
 *
 *      Return Value: 
 *
 *      Comments:
 *
 */
void kr_forw_smooth_rules (LPTTS_HANDLE_T phTTS, short shrif, short pholas,
				   			   int fealas, int feacur, short struclas,
				   			   short struccur, int feanex)
{
	short                   temp;	   /* MVP MI : This variable is made local */
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	//PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	const short *us_place=pDph_t->cur_speaker[PFKR]->place;

	//debugforward ("Set default", pDphsettar->np);
	/* FORWARD SMOOTH: F1, F2, F3 */
	if (pDphsettar->par_type IS_FORM_FREQ)
	{
		/* 0. Use default values for obst-obst transition */
		if ((feacur & FSONOR) IS_PLUS)
		{
			if ((feacur & FSONCON) IS_MINUS)
			{
				pDphsettar->durtran = NF45MS;
				if ((fealas & FSONCON) IS_PLUS)
				{
					/* 1. Soncon-vowel transition, use 25-75% rule */
					pDphsettar->bouval = (pDphsettar->bouval + pDphsettar->np->tarlas) >> 1;
					/* Make F1 discontinuous for light /l/ */
				//	if ((pholas == USP_LL) && (pDphsettar->np == &PF1))
				//	{
				//		pDphsettar->bouval += 80;
				//	}
					/* Make F3 & F2 transitions slower out of /r/ */
					if ((pholas == USP_R) && (pDphsettar->np != &PF1))
					{
						pDphsettar->durtran = NF70MS;
					}
				}
				else
				{
					/* 2. Vowel-[vowel/h] transition */
					/* Preceeding seg has strong influence on [h] init val */
					if (pDphsettar->phcur == KRP_HX)
					{
						pDphsettar->bouval = (pDphsettar->bouval + pDphsettar->np->tarlas) >> 1;
					}
				}
			}
			else
			{
				/* Phcur is a sonorant conson */
				if ((fealas & FSONCON) IS_MINUS)
				{
					/* 3. Vowel-soncon trans, use 75-25% rule */
					pDphsettar->bouval = (pDphsettar->bouval + pDphsettar->np->tarcur) >> 1;
					pDphsettar->durtran = NF30MS;
				}
				else
				{
					/* 4. Soncon-soncon transition */
					pDphsettar->durtran = NF30MS;
				}
			}
		}
		/* Bound value = previous target if current phone is sil */
		/* eab not if it's the first sil EAB 4/apr/95 I've fixed this once before */
		if (pDphsettar->phcur == GEN_SIL)
		{
			/*Eab 7/31/96 changed > 2 to >1 for ending sil*/
			if (pDph_t->nphone > 1)
			{
				pDphsettar->bouval = pDphsettar->np->tarlas;
			}
			else
			{
				pDphsettar->bouval = pDphsettar->np->tarnex;
			}
            pDphsettar->durtran = pDph_t->durfon;
		}
		else
		{
			/* 5. pholas=obst, pDphsettar->phcur=sonor transition */
			if (setloc (phTTS, (short)(pDph_t->nphone - 1), pDph_t->nphone, 'i', (short)(pDph_t->nphone - 2), feanex)) // NAL warning removal
			{
				//debugforward (" Use locus,percent", pDphsettar->np);
			}
			/* 6. pholas=sonor, pDphsettar->phcur=obst transition */
			if (setloc (phTTS, pDph_t->nphone, (short)(pDph_t->nphone - 1), 'f', (short)(pDph_t->nphone + 1),feanex)) // NAL warning removal
			{
				//debugforward (" Use locus,percent", pDphsettar->np);
			}
			/* Dummy vowel for final plosive release into silence is too */
			/* short for an extensive formant transition, make tran less */
			if ((struccur & FDUMMY_VOWEL) IS_PLUS)
			{
				/* OUT                      xx += ((pDphsettar->bouval - pDphsettar->np->tarend) >> 1); pDphsettar->np->tarend += xx;   (DOESN'T
				 * WORK) END OUT */
			}
#if (defined  INTEGER || !(defined HLSYN) )
			/* F1 raised at onset of voiceless plosive release */
			if (((fealas & FPLOSV) IS_PLUS)
				&& ((fealas & FVOICD) IS_MINUS))
			{
				if (pDphsettar->np == &PF1)
					pDphsettar->bouval += 100;
			}
#endif
			/* Transitions modified inside obstruents */
			if ((feacur & FOBST) IS_PLUS)
			{
				pDphsettar->durtran = NF30MS;
				if (pDphsettar->np == &PF1)
					pDphsettar->durtran = NF20MS;
				/* Transitions take all of plosive duration */
				if ((feacur & FPLOSV) IS_PLUS)
				{
					pDphsettar->durtran = pDph_t->durfon;
				}
			}

			/* Higher formant transitions slow inside a nasal */
			if ((feacur & FNASAL) IS_PLUS)
			{
				pDphsettar->durtran = pDph_t->durfon;
				/* Except F1, which jumps to value above FNZRO */
				if (pDphsettar->np == &PF1)
				{
					pDphsettar->durtran = 0;
				}
#if (defined  INTEGER || !(defined HLSYN) )
				/* Lower F2 & F3 of [n] nasal murmur after front vowels */
				else if (((pDphsettar->phcur == KRP_N) || (pDphsettar->phcur == KRP_NX))
						 && (endtyp(pDph_t,pholas) == 1))
				{
					if (pDphsettar->np == &PF2)
					{
						pDphsettar->bouval -= 100;
						if ((us_place[pholas  & PVALUE] & F2BACKF) IS_PLUS)
						{
							pDphsettar->bouval -= 100;
						}
					}
					if (pDphsettar->np == &PF3)
						pDphsettar->bouval -= 100;;
				}
				/* Lower F2 of [m] nasal murmur near [i,e] */
				else if ((pDphsettar->np == &PF2) && (pDphsettar->phcur == KRP_M)
						 && ((us_place[pholas  & PVALUE] & F2BACKF) IS_PLUS))
				{
					pDphsettar->bouval -= 150;
				}
#endif
			}

		}
		/* Shrink transition dur inside sonor if sonor short */
		if (((feacur & FOBST) IS_MINUS)
			&& (endtyp(pDph_t,pholas) != OBSTRUENT)   /* Unless prev seg is obst */
			&& (pDphsettar->durtran > 0))
		{
			//pDph_t->arg1 = pDphsettar->durtran;
			//pDph_t->arg2 = shrif;
			pDphsettar->durtran = mlsh1 (pDphsettar->durtran, shrif) + 1;
		}
	}
	/* FORWARD SMOOTH:  FN */
	else if (pDphsettar->par_type IS_NASAL_ZERO_FREQ)
	{
		pDphsettar->durtran = 0;
		if (((fealas & FNASAL) IS_PLUS)
			&& ((feacur & FNASAL) IS_MINUS))
		{
			pDphsettar->bouval = NASAL_ZERO_BOUNDARY;
			pDphsettar->durtran = NF80MS;
		}
	}
	/* FORWARD SMOOTH:  B1, B2, B3 */
	else if (pDphsettar->par_type IS_FORM_BW)
	{
		/* Default transition duration is 40 ms */
		pDphsettar->durtran = NF40MS;

		/* Widen first formant bw if preceeding seg voiceless */
		if ((feacur & FVOICD) IS_PLUS)
		{
			if ((pDphsettar->np == &PB1)
				&& ((fealas & FVOICD) IS_MINUS))
			{
				pDphsettar->durtran = NF50MS;
				/* More increase for low vowels (F1 high) */
				pDphsettar->bouval = pDphsettar->np->tarcur + (PF1.tarcur >> 3);
			
			}
		}
		else
		{                                       
			pDphsettar->durtran = NF20MS;
		}

		/* Treat boundary with silence */
		if (pholas == GEN_SIL)
		{
			pDphsettar->bouval = pDphsettar->np->tarcur + ((&PB3 - pDphsettar->np) * 50);
			pDphsettar->durtran = NF50MS;
		}
		else if (pDphsettar->phcur == GEN_SIL)
		{
			pDphsettar->bouval = pDphsettar->np->tarlas + ((&PB3 - pDphsettar->np) * 50);
			if (((phone_feature( pDph_t,pDph_t->allophons[pDph_t->nphone - 2]) & FVOICD) IS_MINUS)
				&& ((struclas & FDUMMY_VOWEL) IS_PLUS)
				&& (pDphsettar->np == &PB1))
			{
				pDphsettar->bouval = 300;	/* Kluge to avoid discontinutiy */
			}
			pDphsettar->durtran = NF50MS;
		}

		/* BW1 widen, to nasalize transition out of previous nasal */
		if ((fealas & FNASAL) IS_PLUS)
		{
			pDphsettar->bouval = pDphsettar->np->tarcur;	/* B2,B3 not influ by nasal */
			/* Except F2 of [n], which is wider in a non-front vowel */
			if ((pDphsettar->np == &PB2) && ((pholas == KRP_N) || (pholas == KRP_NX))
				&& (begtyp(pDph_t,pDphsettar->phcur) != 1))
			{
				pDphsettar->bouval += 60;
				pDphsettar->durtran = NF60MS;
			}
			if (pDphsettar->np == &PB1)
			{
				pDphsettar->durtran = NF100MS;
				pDphsettar->bouval += 70;
			}
		}

		/* Nasals have constant bandwidths at target values */
		if ((feacur & FNASAL) IS_PLUS)
		{
			pDphsettar->durtran = 0;
			//debugforward (" Nasal has const par val", pDphsettar->np);
		}
	}
	/* FORWARD SMOOTH:  AV, AP, A2, A3, A4, A5, A6, AB */

	/* Default pDphsettar->bouval is average of tarcur & tarend, default tc is 30 ms */
	else if( pDphsettar->par_type IS_AV_OR_AH)
	{
		/* See if onset, i.e. plosive or large source intensity increase */
		temp = pDphsettar->np->tarcur - 10;
		if( pDphsettar->bouval < temp || 
			(fealas & FPLOSV) IS_PLUS || 
			pholas == KRP_JH)
		{
			pDphsettar->bouval = temp;
			if ((feacur & FOBST) IS_MINUS)
				pDphsettar->durtran = NF20MS;


			if (pDphsettar->np == &PAV)
			{
				/* Gradual buildup of voicing */
				if (pholas == GEN_SIL)
				{
					if ((feacur & FVOICD) IS_PLUS)
					{
						pDphsettar->durtran = NF45MS;
						pDphsettar->bouval -= 8;
					}
				}
				/* Obstruent voicing onset is abrupt */
				if ((fealas & FOBST) IS_PLUS)
				{
					pDphsettar->bouval = temp + 6;
				}
				/* Plosive onset is abrupt (used mainly for [bdg]) */
				if ((fealas & FPLOSV) IS_PLUS)
				{
					pDphsettar->bouval = pDphsettar->np->tarcur - 5;
				}
			}
		
		}
		/* If last nasal, and source amp increased, abrupt onset */
		if (((fealas & FNASAL) IS_PLUS)
			&& ((feacur & FVOICD) IS_PLUS))
		{
			pDphsettar->durtran = 0;
			//debugforward (" Onset from nasal", pDphsettar->np);
		}
		/* Voicing source amp const in intervocalic nasal */
		if ((feacur & FNASAL) IS_PLUS)
		{
			if ((fealas & FVOICD) IS_PLUS)
			{
				if (pDphsettar->np == &PAV)
					pDphsettar->durtran = 0;
			}
		}
		/* See if offset, i.e. source intensity decreasing */
		temp = pDphsettar->np->tarlas - 10;
		if (pDphsettar->bouval < temp)
		{
			/* Reduce bounval by 3 dB because bval time is onset */
			/* of next phoneme */
			pDphsettar->bouval = temp - 3;
			/* Source amplitudes fall gradually into silence */
			if (pDphsettar->phcur == GEN_SIL)
				pDphsettar->durtran = NF70MS;
			/* Except voicing offset is abrupt */
			if (pDphsettar->np == &PAV)
				pDphsettar->durtran = 0;
			//debugforward (" Offset", pDphsettar->np);
		}
		/* Buildup A3 gradually in [C, J] */
		if (pDphsettar->np == &PA3)
		{
			if ((pDphsettar->phcur == KRP_CH) || (pDphsettar->phcur == KRP_JH))
			{
				pDphsettar->durtran = pDph_t->durfon - NF15MS;
				pDphsettar->bouval = pDphsettar->np->tarcur - 30;
				//debugforward (" CH/JH rule", pDphsettar->np);
			}
		}
		/* Offset of a vowel into voiceless open vocal tract is breathy */
		if (pDphsettar->np == &PAP)
		{
			if ((pDphsettar->phcur == GEN_SIL)  || (pDphsettar->phcur == KRP_TH)
				|| (pDphsettar->phcur == KRP_S) || (pDphsettar->phcur == KRP_SH))
			{
				if (((fealas & FVOICD) IS_PLUS)
					&& ((fealas & FOBST) IS_MINUS))
				{
					if (pDphsettar->phcur == GEN_SIL)
					{
						pDphsettar->bouval = 46;
						pDphsettar->durtran = NF80MS;
					}
					else
					{
						pDphsettar->bouval = 42;
						pDphsettar->durtran = NF45MS;
					}
				}
			}
		}
		/* FORWARD SMOOTH:  TLT */

		/* Tilt parameter jumps to target values near stops and silence */
		if (pDphsettar->np == &PTILT)
		{
			pDphsettar->durtran = NF25MS;
			if (pholas == GEN_SIL)
			{
				pDphsettar->bouval = pDphsettar->np->tarcur;
			}
			if (pDphsettar->phcur == GEN_SIL)
			{
				/* Reach into par buffer to get actual previous value */
				pDphsettar->bouval = pDph_t->parstochip[OUT_TLT];
			}
			if (((fealas & FSTOP) IS_PLUS)
				|| ((feacur & FSTOP) IS_PLUS))
			{
				pDphsettar->durtran = 0;
			}
		}
	}
	/* Truncate tran dur if exceeds duration of current phone */
	if (pDphsettar->durtran > pDph_t->durfon)
		pDphsettar->durtran = pDph_t->durfon;
	/* Or duration of 20 frames */
	if (pDphsettar->durtran > NF130MS)
		pDphsettar->durtran = NF130MS;
	/* Do not allow amplitude value to go below zero */
	if (pDphsettar->bouval < 0)
		pDphsettar->bouval = 0;
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* I. Determine parameters of backward smoothing  f(pDphsettar->phcur,pDphsettar->phonex) */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*
 *      Function Name: back_smooth_rules()      
 *
 *  	Description: PDPH_T pDph_t, short shrib, short feacur,
 *				   	 short feanex, short strucnex
 *
 *      Arguments:	PDPH_T pDph_t, 
 * 					short shrib, 
 *					short feacur,
 *				   	short feanex, 
 *				   	short strucnex
 *
 *      Return Value: 
 *
 *      Comments:
 *
 */
void kr_back_smooth_rules (LPTTS_HANDLE_T phTTS, short shrib, int feacur,
				   			   int feanex, short strucnex)
{
	short                   temp;	   /* MVP MI : This varaible is made local */
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	//PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	const short *us_place=pDph_t->cur_speaker[PFKR]->place;

	//debugbackward ("Set default", pDphsettar->np);

	/* BACKWARD SMOOTH:  F1, F2, F3 */
	if (pDphsettar->par_type IS_FORM_FREQ)
	{
		/* 0. Use default values for obst-obst transition */
		if ((feacur & FSONOR) IS_PLUS)
		{
			pDphsettar->durtran = NF45MS;
			if ((feacur & FSONCON) IS_MINUS)
			{
				if ((feanex & FSONCON) IS_PLUS)
				{
					/* 1. Vowel-soncon trans, use 75-25% rule */
					pDphsettar->bouval = (pDphsettar->bouval + pDphsettar->np->tarnex) >> 1;
					/* F3 transitions slower esp for [r,l] */
					if (pDphsettar->np == &PF3)
					{
						pDphsettar->durtran = NF64MS;
					}
				}
				else
				{
					/* 2. Vowel-[vowel/h] transition */
					/* Following [h] has little influence on pDphsettar->bouval */
					if (pDphsettar->phonex == KRP_HX)
					{
						pDphsettar->bouval = (pDphsettar->bouval + pDphsettar->np->tarend) >> 1;
					}
				}
			}
			else
			{
				pDphsettar->durtran = NF40MS;
				if ((feanex & FSONCON) IS_MINUS)
				{
					/* 3. Soncon-vowel trans, use 25-75% rule */
					pDphsettar->bouval = (pDphsettar->bouval + pDphsettar->np->tarend) >> 1;
					pDphsettar->durtran = NF20MS;
				}
				else
				{
					/* 4. Soncon-soncon transition */
					/* Use defaults */
				}
			}
		}
		/* No backward smoothing if next phone is silence */
		if (pDphsettar->phonex == GEN_SIL)
		{
			pDphsettar->durtran = 0;
		}
		else
		{
			/* 5. pDphsettar->phcur = sonor, pDphsettar->phonex = obst transition */
			if (setloc (phTTS, (short)(pDph_t->nphone + 1), pDph_t->nphone, 'f', (short)(pDph_t->nphone + 2),feanex)) // NAL warning removal
			{
				//debugbackward (" Use locus,percent", pDphsettar->np);
			}
			/* 6. pDphsettar->phcur=obst, pDphsettar->phonex=sonor transition */
			if (setloc (phTTS, pDph_t->nphone, (short)(pDph_t->nphone + 1), 'i', (short)(pDph_t->nphone - 1),feanex)) // NAL warning removal
			{
				//debugbackward (" Use locus,percent", pDphsettar->np);
			}
			/* Transitions slow inside obstruents */
			if ((feacur & FOBST) IS_PLUS)
			{
				pDphsettar->durtran = NF30MS;
				if (pDphsettar->np == &PF1)
					pDphsettar->durtran = NF20MS;
				/* Transitions take all of plosive duration */
				if ((feacur & FPLOSV) IS_PLUS)
				{
					pDphsettar->durtran = pDph_t->durfon;
#if (defined  INTEGER || !(defined HLSYN) )
					if ((pDphsettar->np == &PF1) && ((feacur & FVOICD) IS_MINUS))
					{
						pDphsettar->bouval += 100;
					}
#endif
				}
			}
			/* Higher formant transitions slow inside a nasal */
#if (defined  INTEGER || !(defined HLSYN) )
			if ((feacur & FNASAL) IS_PLUS)
			{
				pDphsettar->durtran = pDph_t->durfon;
				/* Except F1, which jumps to value below FNZRO */
				if (pDphsettar->np == &PF1)
				{
					pDphsettar->durtran = 0;
				}
				/* Lower F2 & F3 of [n] nasal murmur before front vowels */
				else if (((pDphsettar->phcur == KRP_N) || (pDphsettar->phcur == KRP_NX))
						 && (begtyp(pDph_t,pDphsettar->phonex) == 1))
				{
					if (pDphsettar->np == &PF2)
					{
						pDphsettar->bouval -= 100;
						if ((us_place[pDphsettar->phonex  & PVALUE] & F2BACKI) IS_PLUS)
						{
							pDphsettar->bouval -= 100;
						}
					}
					if (pDphsettar->np == &PF3)
						pDphsettar->bouval -= 100;
				}
				/* Lower F2 of [m] murmur near [i,y,yu,ir] */
				else if ((pDphsettar->np == &PF2) && (pDphsettar->phcur == KRP_M)
						 && ((us_place[pDphsettar->phonex & PVALUE] & F2BACKI) IS_PLUS))
				{
					pDphsettar->bouval -= 150;
				}
			}
#endif
		}
		/* Shrink tran dur inside sonorant if sonorant short */
		if (((feacur & FOBST) IS_MINUS)
			&& (begtyp(pDph_t,pDphsettar->phonex) != 4)	/* Unless next seg is obst */
			&& (pDphsettar->durtran > 0))
		{
			//pDph_t->arg1 = pDphsettar->durtran;
			//pDph_t->arg2 = shrib;
			pDphsettar->durtran = mlsh1 (pDphsettar->durtran, shrib) + 1;
		}
	}
	/* BACKWARD SMOOTH:  FN */
	else if (pDphsettar->par_type IS_NASAL_ZERO_FREQ)
	{
		pDphsettar->durtran = 0;
		/* Nasalization cue: place zero between F1 and FP */
		if (((feanex & FNASAL) IS_PLUS)
			&& ((feacur & FNASAL) IS_MINUS))
		{
			pDphsettar->bouval = NASAL_ZERO_BOUNDARY;
			pDphsettar->durtran = NF80MS;
		
		}
	}
	/* BACKWARD SMOOTH:  B1, B2, B3 */
	else if (pDphsettar->par_type IS_FORM_BW)
	{
		pDphsettar->durtran = NF40MS;
		if ((feacur & FVOICD) IS_PLUS)
		{

			/* Glottis opens early before -voice C, widen B1 */
			if (pDphsettar->np == &PB1)
			{
				if ((feanex & FVOICD) IS_MINUS)
				{
					pDphsettar->durtran = NF50MS;
					/* More increase for low vowels (F1 high) */
					pDphsettar->bouval = pDphsettar->np->tarend + (PF1.tarcur >> 3);

					/* Effect is greater for a female voice */
					if (pDph_t->malfem == FEMALE)
					{
						pDphsettar->durtran = NF100MS;
					}
				}
			}
		}
		else
		{
			pDphsettar->durtran = NF20MS;
		}
		/* Treat boundary with silence */
		/* OUT ??? */
		if (pDphsettar->phonex == GEN_SIL)
		{
			pDphsettar->bouval = pDphsettar->np->tarend + ((&PB3 - pDphsettar->np) * 50);
			pDphsettar->durtran = NF50MS;
		}
		else if (pDphsettar->phcur == GEN_SIL)
		{
			pDphsettar->bouval = pDphsettar->np->tarnex + ((&PB3 - pDphsettar->np) * 50);
			pDphsettar->durtran = NF50MS;
		}
		/* BW1 widen, to nasalize transition into next nasal */
		if ((feanex & FNASAL) IS_PLUS)
		{
			pDphsettar->bouval = pDphsettar->np->tarend;
			/* Except F2 of [n], which is wider before a non-front vowel */
			if ((pDphsettar->np == &PB2) && ((pDphsettar->phonex == KRP_N) || (pDphsettar->phonex == KRP_NX))
				&& (endtyp(pDph_t,pDphsettar->phcur) != 1))
			{
				pDphsettar->bouval += 60;
				pDphsettar->durtran = NF60MS;
			}
			if (pDphsettar->np == &PB1)
			{
				pDphsettar->durtran = NF100MS;
				pDphsettar->bouval += 100;
			}
		}
		/* Nasals have constant bandwidths at target values */
		if ((feacur & FNASAL) IS_PLUS)
		{
			pDphsettar->durtran = 0;
			//debugbackward (" Nasal has const. par val", pDphsettar->np);
		}
	}
	/* BACKWARD SMOOTH:  AV, AP, A2, A3, A4, A5, A6, AB */
	else if ( (pDphsettar->par_type IS_AV_OR_AH))
	{
		/* See if onset, i.e. source intensity increasing */
		temp = pDphsettar->np->tarnex - 10;
		if (pDphsettar->bouval < temp)
		{
			pDphsettar->bouval = temp;
			/* Onset of an init fricative or /h/ is very gradual */
			if (pDphsettar->phcur == GEN_SIL)
			{
				pDphsettar->durtran = NF70MS;
			}
			//debugbackward (" Onset", pDphsettar->np);
		}
		/* Voicing is special:  onset is abrupt, except if a voiced fric */
		if( pDphsettar->np == &PAV && 
			pDphsettar->bouval < pDphsettar->np->tarnex && 
			pDphsettar->phcur != KRP_JH )
		{
			pDphsettar->durtran = 0;
			//debugbackward (" Make next onset abrupt", pDphsettar->np);
			/* Voicebar dies out in a voiced plosive */
			if( (feacur & FPLOSV) IS_PLUS || 
				pDphsettar->phcur == KRP_CH)
			{
				if ((feacur & FVOICD) IS_PLUS)
				{
					pDphsettar->bouval = pDphsettar->np->tarend - 3;
					pDphsettar->durtran = NF45MS;
					//debugbackward (" Voicebar dies out", pDphsettar->np);
				}
				/* Do not allow prevoicing in a voiceless plosive */
				else
				{
					pDphsettar->bouval = 0;
				}
				goto endbsmo;
			}
		}
		/* If next nasal, & curr phone is voiced, set AV const */
		if (((feanex & FNASAL) IS_PLUS)
			&& ((feacur & FVOICD) IS_PLUS))
		{
			pDphsettar->durtran = 0;
			//debugforward (" AV const in voiced to  nasal", pDphsettar->np);
		}
		/* If curr phone nasal, and next is voiced non-obst, AV const */
		if ((feacur & FNASAL) IS_PLUS)
		{
			if (((feanex & FVOICD) IS_PLUS)
				&& ((feanex & FOBST) IS_MINUS)
				&& ((strucnex & FDUMMY_VOWEL) IS_MINUS))
			{
				pDphsettar->durtran = 0;
				//debugbackward (" Make murmur const AV", pDphsettar->np);
			}
			else
			{
				pDphsettar->durtran = NF40MS;
			}
		}
		/* See if offset, i.e. source intensity decreasing */
		temp = pDphsettar->np->tarend - 10;
		/* Plosive burst does not get attenuated during offset */
		if (pDphsettar->phcur >= KRP_P)
		{
			pDphsettar->durtran = NF15MS;
			if (pDphsettar->phcur < KRP_CH)
			{
				temp = pDphsettar->np->tarend;
			}
		}
		if (pDphsettar->bouval < temp)
		{							   /* Or does it ??? */
			pDphsettar->bouval = temp - 3;
			pDphsettar->durtran = NF20MS;
		}
		/* Voicing amp falls gradually at end of phrase */
		/* (Source sudden offset, or next seg is a dummy vowel) */
		if (pDphsettar->np == &PAV)
		{
			if( (pDphsettar->bouval < temp) || ((temp > 0)
				&& (pDphsettar->np == &PAV) 
				&& ((strucnex & FDUMMY_VOWEL) IS_PLUS)))
			{
				pDphsettar->bouval = temp + 3;
				if ((pDphsettar->phonex == GEN_SIL)
					|| ((strucnex & FDUMMY_VOWEL) IS_PLUS))
				{
					pDphsettar->durtran = NF75MS;
				}
			}
			else if (pDphsettar->np == &PAP)
				pDphsettar->bouval = PAP.tarend - 6;
			//debugbackward (" Offset to noise", pDphsettar->np);
		}
		/* No smoothing of source amps if next segment has burst */
		if ((pDphsettar->phonex >= KRP_P)
			&& (((feacur & FNASAL) IS_MINUS) || (pDphsettar->np != &PAV)))
		{
			pDphsettar->durtran = 0;
			//debugbackward (" Stop closure next", pDphsettar->np);
		}
		/* Onset of a vowel from voiceless open vocal tract is breathy */
		if (pDphsettar->np == &PAP)
		{
			if( pDphsettar->phcur == KRP_TH || 
				pDphsettar->phcur == KRP_S || 
				pDphsettar->phcur == KRP_SH )
			{
				if( ((feanex & FVOICD) IS_PLUS) &&
					((feanex & FOBST) IS_MINUS) )
				{
					pDphsettar->bouval = 52;
					pDphsettar->durtran = NF40MS;
				}
			}

			/* Offset of a vowel into silence is breathy */
			if (((feacur & FSYLL) IS_PLUS)
				&& (pDphsettar->phonex == GEN_SIL))
			{
				pDphsettar->bouval = 52;
				pDphsettar->durtran = NF130MS;
			}
		}
		/* BACKWARD SMOOTH:  TLT */

		/* Tilt parameter jumps to target values near stops and silence */
		if (pDphsettar->np == &PTILT)
		{
			pDphsettar->durtran = NF25MS;
			if (pDphsettar->phonex == GEN_SIL)
			{
				pDphsettar->bouval = pDphsettar->np->tarend;
			}
			if (pDphsettar->phcur == GEN_SIL)
			{
				pDphsettar->bouval = pDphsettar->np->tarnex;
			}
			if (((feanex & FSTOP) IS_PLUS)
				|| ((feacur & FSTOP) IS_PLUS))
			{
				pDphsettar->durtran = 0;
			}
			/* Long breathy offset into silence */
			if (((feacur & FVOICD) IS_PLUS)
				&& ((feacur & FNASAL) IS_MINUS))
			{
				if (pDphsettar->phonex == GEN_SIL)
				{
					pDphsettar->bouval = 15;
					pDphsettar->durtran = NF130MS;
				}
			}
		}
	}
	/* Truncate back transition so as not to exceed 20 frames */
  endbsmo:
	if (pDphsettar->durtran > NF130MS)
		pDphsettar->durtran = NF130MS;
	/* Truncate backward tran so as not to exceed dur of phone */
	if (pDphsettar->durtran > pDph_t->durfon)
		pDphsettar->durtran = pDph_t->durfon;
	pDphsettar->np->tbacktr = pDph_t->durfon - pDphsettar->durtran;
	/* No parameter can take on negative values */
	if (pDphsettar->bouval < 0)
		pDphsettar->bouval = 0;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* J.              S P E C I A L - R U L E S                        */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*
 *      Function Name:       
 *
 *  	Description: special_rules 
 *
 *      Arguments:	PDPH_T pDph_t,  
 *					short fealas,
 *			   		short feacur, 
 *			   		short feanex, 
 *			   		short struclm2,
 *			   		short struccur, 
 *			   		short pholas, 
 *			   		short struclas 
 *
 *      Return Value: void
 *
 *      Comments:
 *
 */
void kr_special_rules (LPTTS_HANDLE_T phTTS, short fealas,
			   				int feacur, int feanex, short struclm2,
			   				short struccur, short pholas, short struclas)
{
	short                   bdur, vot; /* MVP made as a local variable */
	short                   closure_dur;	/* MVP made as a local variable */
	short tmp;
	
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	//PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	const short *kr_place=pDph_t->cur_speaker[PFKR]->place;
	
	/* SPECIAL RULE 1: Burst duration for plosives and affricates             */
	tmp = pDphsettar->phcur & PVALUE;
	bdur = burdr(pDph_t,pDphsettar->phcur);   /* Look up inher. burst dur in msec in table */
	
	if ((feacur & FBURST) IS_PLUS)
	{
		if(	pDph_t->allophons[pDph_t->nphone+1] == GEN_SIL)
			bdur = 0;
		else
			bdur = mstofr(bdur);		   /* Convert to frames         */
		
		/* Don't release burst in homorganic plosiv-nasal & plos-plos sequence */
		/* bats 878 EAB 4/2/99*/
		
		
		/* Dennis had a rule that said in homorganic (meaning
		in this case the same place of articulation) nasal plosives
		and plosive plosive one should not release the burst of the 
		initial plosive. This is incorrect place because a nasal
		doesn't have a place of articulation so it can never match 
		plus the homorganic I don't believe really means exact same 
		place of articulation. A plosive followed by a nasal will 
		not be realeased-period. Secondly, a plosive that has 
		similiar place of artculation should follow the rule.
		i=(i.e an aveloar or a dental are equivalent)
		So, I added new masks to group places into "homorganic
		groupings"
		
		*/
		
		
		if ((feanex & (FNASAL | FPLOSV)) IS_PLUS)
		{		
			bdur = 0;
		}
		
		
		if (bdur > 1)
		{
			if (((feacur & FPLOSV) IS_PLUS)
				&& ((feanex & FOBST) IS_PLUS))
			{
				bdur--;				   /* Shorten burst before obst by 6 ms */
			}
			else if (pDph_t->durfon < NF50MS)
			{
				bdur--;				   /* Shorten burst if closure short */
			}
		}
		
		closure_dur = pDph_t->durfon - bdur;
		
		if ((pDphsettar->phcur == KRP_CH) || (pDphsettar->phcur == KRP_JH))
		{
			if (closure_dur > NF60MS)
				closure_dur = NF60MS;
			//new thing added for fast speech we need some closure
			if (closure_dur < 2)
				closure_dur = 2;
			
		}
		
		for (pDphsettar->np = &PA2; pDphsettar->np <= &PAB; pDphsettar->np++)
		{							   /* All fric gains to */
			pDphsettar->np->tspesh = closure_dur;	/* zero during closur */
			pDphsettar->np->pspesh = 0;
			
			//Set it once per loop whne PAB
			if(pDphsettar->np == &PAB)
			{
				if(kr_place[pDphsettar->phcur & PVALUE] & FLABIAL)
				{
					PAREAL.tspesh=closure_dur;
					PAREAB.tspesh =0;
					PTONGUEBODY.tspesh=0;
				}
				else if(kr_place[pDphsettar->phcur & PVALUE] & BLADEAFFECTED )
				{
					PAREAL.tspesh=0;
					PAREAB.tspesh=closure_dur;
					PTONGUEBODY.tspesh=0;
				}
				else if(kr_place[pDphsettar->phcur & PVALUE] & FVELAR )
				{
					PAREAL.tspesh=0;
					PAREAB.tspesh=0;
					PTONGUEBODY.tspesh=closure_dur;
				}
			}
		} // if np == &pab
		//pDph_t->in_closure =1;
		//pDph_t->in_release =0;
	} //if burst
	
	
	
	/* SPECIAL RULE 2: Voice onset time for aspirated plosives */
	
	vot = 0;
	
	if( (feacur & FSONOR) IS_PLUS &&		// Current phoneme is sonorant
		(fealas & FVOICD) IS_MINUS &&		// Last phoneme is unvoiced
		(fealas & FPLOSV) IS_MINUS )		//                 fricative
	{
		PAP.pspesh = 54;					// Amplitude of aspiration in dB
		PAV.pspesh = 0;						// Amplitude of voicing during aspir

		if( pDph_t->allophons[pDph_t->nphone-1] == KRP_S) 
		{
			if( (struclas & FWINITC) IS_PLUS )	// Word initial /s/ should have lots of vot (aspiration) after it
			{
				vot = mstofr(75);
				PAV.tspesh = vot;				// tspesh := time special for voice onset time
				PAP.tspesh = vot;
			}
		}
	}
	else
	if( ((fealas & FPLOSV) IS_PLUS) &&		// Last phoneme is a plosive (excluding affricates and nasals)
		((fealas & FVOICD) IS_MINUS) &&		// Last phoneme is not voiced
		((feacur & FSONOR) IS_PLUS ) )		// Current phoneme is a sonorant
	{
		PAP.pspesh = 54;					/* Amplitude of aspiration in dB     */
		
		if (begtyp(pDph_t,pDphsettar->phcur) != 1)
		{
			PAP.pspesh = 56;				/* Stronger asp before +back */
		}
		PAV.pspesh = 0;						/* Amplitude of voicing during aspir */
		

		if( pDph_t->allophons[pDph_t->nphone-1] == KRP_PP )			// Tense unvoiced stops
			vot = mstofr(10);
		else if( pDph_t->allophons[pDph_t->nphone-1] == KRP_TT )
			vot = mstofr(15);
		else if( pDph_t->allophons[pDph_t->nphone-1] == KRP_KK )
			vot = mstofr(20);

		else if( pDph_t->allophons[pDph_t->nphone-1] == KRP_P )		// Lax/Lenis unvoiced stops
		{
			vot = mstofr(50);
		}
		else if( pDph_t->allophons[pDph_t->nphone-1] == KRP_T )
		{
			vot = mstofr(60);
		}
		else if( pDph_t->allophons[pDph_t->nphone-1] == KRP_K )
		{
			vot = mstofr(70);
		}
		
		else if( pDph_t->allophons[pDph_t->nphone-1] == KRP_PH )	// Aspirated unvoiced stops
			vot = mstofr(70);
		else if( pDph_t->allophons[pDph_t->nphone-1] == KRP_TH )
			vot = mstofr(80);
		else if( pDph_t->allophons[pDph_t->nphone-1] == KRP_KH )
			vot = mstofr(90);
		else
			vot = mstofr(20);
		
		
#ifdef FASTTYPING_MODE
		if( phTTS->bInTypingMode == TRUE || 
			pKsd_t->sprate > 300)
		{
			vot=vot>>2;
			if(vot == 0)
				vot=1;
			
			PAV.pspesh += 10;
			PAP.pspesh -=5;
		}
#endif

		PAV.tspesh = vot;	// Amplitude of voicing
		PAP.tspesh = vot;	// Amplitude of aspiration - have aspiration continue into vowel
		
		/* Widen 1st and 2nd formant bws when glottis open for aspir */
		PB1.tspesh = vot;
		PB2.tspesh = vot;
		PB1.pspesh = PB1.tarcur + 250;
		PB2.pspesh = PB2.tarcur + (70);
	}


	/* SPECIAL RULE 3: Create realistic voicebar, avoid pops and clicks */
	/* Amp of voicebar set here, AV target in table invalid */
	/* Set AV=0 for last 12.8 ms, let AV die out, thus avoid click */
	/* Set to under 250 to signal voicebar */
	
	/* Problem: spectrum has too much F4 if f2,3 are high, as in [i] */
	
	if( ((feacur & FBURST) IS_PLUS) &&		// Current phoneme is a plosive or affricate
		((feacur & FVOICD) IS_PLUS) &&		// Current phoneme is voiced
		((fealas & FVOICD) IS_PLUS) &&		// Previous phoneme is voiced
		((feanex & FVOICD) IS_MINUS) )		// Next phoneme is NOT voiced - Voicebar only if next -V
	{
		PAV.tspesh = pDph_t->durfon - NF15MS;
		PB1.tspesh = pDph_t->durfon;
		PB2.tspesh = pDph_t->durfon;
		PB3.tspesh = pDph_t->durfon;
		PAV.pspesh = 10;			   /* Large since low-pass TILT attenuates it 
										  eab voicebars can be trouble and are not really perceptual*/
#if (defined  INTEGER || !(defined HLSYN) )
		PB1.pspesh = 150;
		PB2.pspesh = 150;
		PB3.pspesh = 150;
#else
		PB1.pspesh = 500;
		PB2.pspesh = 500;
		PB3.pspesh = 500;
#endif
	}
}
