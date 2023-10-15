/* 
 ***********************************************************************
 *
 *                           Copyright ©
 *    Copyright © 2000-2001 Force Computer, Inc., a Solectron company. All rights reserved.
 *    © Digital Equipment Corporation 1996, 1997. All rights reserved.
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
 *    File Name:    p_jp_st1.c
 *    Author:		Matthew Schnee
 *    Creation Date:04-Jun-1996
 *
 *    Functionality:
 *	  English specific functions from phsettar.c
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
 *  	Description: Get target value (or a pointer to first value of diphthong specification 
 * 					 (do not compute any coarticulatory influences of adjacent phones)         
 *      Arguments: PDPH_T pDph_t, 
 *				   short nphone_temp
 *      Return Value: short 
 *      Comments:
 */
//extern const short jp_place[];

int jp_gettar (LPTTS_HANDLE_T phTTS, int nphone_temp)
{
	short                   phone_temp, phlas_temp, phnex_temp,tartemp=0, pphotr, npar;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	const short *jp_place=pDph_t->cur_speaker[PFJP]->place;

// if we're at beggining silence then sil value is the value of the next 
	//phone because we anticipate

	phlas_temp = get_phone(pDph_t,nphone_temp - 1);
	phone_temp = get_phone(pDph_t,nphone_temp);
	phnex_temp = get_phone(pDph_t,nphone_temp + 1);

	npar = pDphsettar->np - &PF1;
	if (pDphsettar->np < &PFZ)                      
		pphotr = (npar) * JP_TOT_ALLOPHONES;
	else
		pphotr = (npar - 1) * JP_TOT_ALLOPHONES;
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
		if ((((phone_temp) == JP_N) || ((phone_temp) == JP_EN))
			&& (npar == B2 - 1))
		{
			if (begtyp(pDph_t,phnex_temp) != 1)
			{
				tartemp += 60;
			}
		}
		/* Special rule for B3 of \n/ adjacent to high-front vowels */
		if ((((phone_temp) == JP_N) || ((phone_temp) == JP_EN) || ((phone_temp) == JP_NG))
			&& (npar == B3 - 1))
		{
			if (((jp_place[phnex_temp & PVALUE] & F2BACKI) IS_PLUS)
				|| ((jp_place[(phlas_temp & PVALUE)] & F2BACKF) IS_PLUS))
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
				/* Voice [h] if unstressed and preceeded by voiced seg */
				if (((phone_temp) == JP_H)
					&& ((phone_feature( pDph_t,(phlas_temp)) & FVOICD) IS_PLUS)
					&& ((pDph_t->allofeats[nphone_temp] & FSTRESS_1) IS_MINUS)
					&& !pDph_t->Cite_It)
				{
					tartemp = 54;
				}
				
		
		}
		
		
		
	
	/* Rules for aspiration amplitude */
	else
	{
		if ((phone_temp) == JP_H)
		{
			tartemp = 46;
			if (begtyp(pDph_t,phnex_temp)  != 1)
			{
				tartemp = 48;	   /* Stronger asp before +back */
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

			else if ((pDph_t->allofeats[nphone_temp] & FDUMMY_VOWEL) IS_PLUS)
			{
				tartemp = 10;
			}
			else if ((phone_feature( pDph_t,phone_temp ) & FOBST) IS_PLUS)
			{
				tartemp = 7;
				if (((phone_feature( pDph_t,phone_temp) & FVOICD) IS_PLUS)
					&& (((phone_feature( pDph_t,phone_temp) & FPLOSV) IS_PLUS)
						|| (pDphsettar->phcur == JP_JH)))
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
short jp_special_coartic (PDPH_T pDph_t, short nfon, short diphpos)
{
	/* Note: Gen coartic of 5% with adjacent segs elsewhere, so stuff here is big */
	/* This routine is only called if the current segment is diph (i.e. a vowel) */

	short                   temp, fonnex, foncur, fonlas;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
//	extern const short jp_place[];
	const short *jp_place=pDph_t->cur_speaker[PFJP]->place;

	temp = 0;
	foncur = get_phone(pDph_t, nfon);
	fonnex = get_phone(pDph_t, nfon + 1);
	fonlas = get_phone(pDph_t, nfon - 1);


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
void jp_forw_smooth_rules (LPTTS_HANDLE_T phTTS, short shrif, short pholas,
				   			   int fealas, int feacur, short struclas,
				   			   short struccur, short feanex)
{
	short                   temp;	   /* MVP MI : This variable is made local */
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	//PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	const short *jp_place=pDph_t->cur_speaker[PFJP]->place;

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
				//	if ((pholas == JP_LL) && (pDphsettar->np == &PF1))
				//	{
				//		pDphsettar->bouval += 80;
				//	}
					
				}
				else
				{
					/* 2. Vowel-[vowel/h] transition */
					/* Preceeding seg has strong influence on [h] init val */
					if (pDphsettar->phcur == JP_H)
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
				else if (((pDphsettar->phcur == JP_N) || (pDphsettar->phcur == JP_EN))
						 && (endtyp(pDph_t,pholas) == 1))
				{
					if (pDphsettar->np == &PF2)
					{
						pDphsettar->bouval -= 100;
						if ((jp_place[pholas  & PVALUE] & F2BACKF) IS_PLUS)
						{
							pDphsettar->bouval -= 100;
						}
					}
					if (pDphsettar->np == &PF3)
						pDphsettar->bouval -= 100;;
				}
				/* Lower F2 of [m] nasal murmur near [i,e] */
				else if ((pDphsettar->np == &PF2) && (pDphsettar->phcur == JP_M)
						 && ((jp_place[pholas  & PVALUE] & F2BACKF) IS_PLUS))
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
			if ((pDphsettar->np == &PB2) && ((pholas == JP_N) || (pholas == JP_EN))
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
	else if (/*(pDphsettar->par_type IS_PARALLEL_FORM_AMP)
			 ||*/ (pDphsettar->par_type IS_AV_OR_AH))
	{

		/* See if onset, i.e. plosive or large source intensity increase */
		temp = pDphsettar->np->tarcur - 10;
		if ((pDphsettar->bouval < temp) || ((fealas & FPLOSV) IS_PLUS)
			|| (pholas == JP_JH))
		{
			pDphsettar->bouval = temp;
			if ((feacur & FOBST) IS_MINUS)
				pDphsettar->durtran = NF20MS;
			/* Voicing is 
			ial */
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
			if ((pDphsettar->phcur == JP_CH) || (pDphsettar->phcur == JP_JH))
			{
				pDphsettar->durtran = pDph_t->durfon - NF15MS;
				pDphsettar->bouval = pDphsettar->np->tarcur - 30;
				//debugforward (" CH/JH rule", pDphsettar->np);
			}
		}
		/* Offset of a vowel into voiceless open vocal tract is breathy */
		if (pDphsettar->np == &PAP)
		{
			if ((pDphsettar->phcur == GEN_SIL) || (pDphsettar->phcur == JP_F) 
				|| (pDphsettar->phcur == JP_S) || (pDphsettar->phcur == JP_SH))
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
void jp_back_smooth_rules (LPTTS_HANDLE_T phTTS, short shrib, int feacur,
				   			   int feanex, short strucnex)
{
	short                   temp;	   /* MVP MI : This varaible is made local */
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	//PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	const short *jp_place=pDph_t->cur_speaker[PFJP]->place;

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
					if (pDphsettar->phonex == JP_H)
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
				else if (((pDphsettar->phcur == JP_N) || (pDphsettar->phcur == JP_EN))
						 && (begtyp(pDph_t,pDphsettar->phonex) == 1))
				{
					if (pDphsettar->np == &PF2)
					{
						pDphsettar->bouval -= 100;
						if ((jp_place[pDphsettar->phonex  & PVALUE] & F2BACKI) IS_PLUS)
						{
							pDphsettar->bouval -= 100;
						}
					}
					if (pDphsettar->np == &PF3)
						pDphsettar->bouval -= 100;
				}
				/* Lower F2 of [m] murmur near [i,y,yu,ir] */
				else if ((pDphsettar->np == &PF2) && (pDphsettar->phcur == JP_M)
						 && ((jp_place[pDphsettar->phonex & PVALUE] & F2BACKI) IS_PLUS))
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
			if (pDphsettar->phonex == JP_EN)
				pDphsettar->durtran = NF130MS;
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
			if ((pDphsettar->np == &PB2) && ((pDphsettar->phonex == JP_N) || (pDphsettar->phonex == JP_EN))
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
		if ((pDphsettar->np == &PAV) && (pDphsettar->bouval < pDphsettar->np->tarnex)
			 && (pDphsettar->phcur != JP_DH)
			&& (pDphsettar->phcur != JP_JH) && (pDphsettar->phcur != JP_ZH) && (pDphsettar->phcur != JP_Z))
		{
			pDphsettar->durtran = 0;
			//debugbackward (" Make next onset abrupt", pDphsettar->np);
			/* Voicebar dies out in a voiced plosive */
			if (((feacur & FPLOSV) IS_PLUS) || (pDphsettar->phcur == JP_CH))
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
		if (pDphsettar->phcur >= JP_P)
		{
			pDphsettar->durtran = NF15MS;
			if (pDphsettar->phcur < JP_CH)
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
			if ((pDphsettar->bouval < temp) || ((temp > 0)
												&& (pDphsettar->np == &PAV) && ((strucnex & FDUMMY_VOWEL) IS_PLUS)))
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
		if ((pDphsettar->phonex >= JP_P)
			&& (((feacur & FNASAL) IS_MINUS) || (pDphsettar->np != &PAV)))
		{
			pDphsettar->durtran = 0;
			//debugbackward (" Stop closure next", pDphsettar->np);
		}
		/* Onset of a vowel from voiceless open vocal tract is breathy */
		if (pDphsettar->np == &PAP)
		{
			if (
			/* OUT                    (pDphsettar->phcur == GEN_SIL) ||                         END OUT */
				   (pDphsettar->phcur == JP_F) 
				   || (pDphsettar->phcur == JP_S) || (pDphsettar->phcur == JP_SH))
			{
				if (((feanex & FVOICD) IS_PLUS)
					&& ((feanex & FOBST) IS_MINUS))
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
void jp_special_rules (LPTTS_HANDLE_T phTTS, int fealas,int feacur, int feanex, short struclm2,

short struccur, short pholas, short struclas)
{
	short bdur, vot; /* MVP made as a local variable */
	short closure_dur;	/* MVP made as a local variable */
//	short tmp;
//	short phcur;

	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	//PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	const short *jp_place=pDph_t->cur_speaker[PFJP]->place;



/*    SPECIAL RULE 1: Burst duration for plosives and affricates	     */

	bdur = 0;
        	if ((feacur & FBURST) IS_PLUS)
			{

            bdur = mstofr (burdr(pDph_t,pDphsettar->phcur));;	/* Look up inher. burst dur in table */
	    closure_dur = pDph_t->durfon - bdur;
			for (pDphsettar->np = &PA2; pDphsettar->np <= &PAB; pDphsettar->np++)
		{							   /* All fric gains to */
			pDphsettar->np->tspesh = closure_dur;	/* zero during closur */
			pDphsettar->np->pspesh = 0;
			
//Set it once per loop when PAB
			if(pDphsettar->np == &PAB)
			{
			if(jp_place[pDphsettar->phcur & PVALUE] & FLABIAL)
			{
				PAREAL.tspesh=closure_dur;
				PAREAB.tspesh =0;
				PTONGUEBODY.tspesh=0;
			}
			else if(jp_place[pDphsettar->phcur & PVALUE] & BLADEAFFECTED )
			{
				PAREAL.tspesh=0;
				PAREAB.tspesh=closure_dur;
				PTONGUEBODY.tspesh=0;
			}
				else if(jp_place[pDphsettar->phcur & PVALUE] & FVELAR )
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
		
/*    SPECIAL RULE 2: Voice onset time for aspirated plosives */

		vot = 0;
        if ((((fealas & FPLOSV) IS_PLUS)
          && ((fealas & FVOICD) IS_MINUS)
          && ((feacur & FSONOR) IS_PLUS))
		|| ((pDph_t->allofeats[pDph_t->nphone] & FDELET) IS_PLUS)) {

            PAP.pspesh = 58;		/* Amplitude of aspiration in dB     */
            PAV.pspesh = 0;		/* Amplitude of voicing during aspir */

	    if ((struccur & FWINITC) IS_PLUS) {
	        vot =5; /* Asp is re phone begin (burst end) */
	    }
	    else 
		{
		vot = 3; /* Vot shorter if not word intial    */
	    }

	    if ((pDph_t->allofeats[pDph_t->nphone] & FDELET) IS_PLUS)
		{
		vot = NF20MS;
	    }
		if(jp_place[pholas & PVALUE] & FVELAR)
			vot= 5;
		if(jp_place[pholas & PVALUE] & FLABIAL
		||	jp_place[pholas & PVALUE] & FDENTAL	)
			vot= 0;

	    if (vot > pDph_t->durfon) 
		{
		vot = pDph_t->durfon;		/* Vot can't exceed dur of cur phone */
	    }

	    PAV.tspesh = vot;
	    PAP.tspesh = vot;
	}
//eab special rule for voicebar
		 if (((feacur & FPLOSV) IS_PLUS)
          && ((feacur & FVOICD) IS_PLUS))
		 {
			PAV.pspesh = 50;
			PAV.tspesh = pDph_t->durfon;
		 }


}

