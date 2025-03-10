/* 
 ***********************************************************************
 *
 *                           Copyright �
 *	  Copyright � 2002 Fonix Corporation. All rights reserved.
 *	  Copyright � 2000-2001 Force Computers, a Solectron Company. All rights reserved.
 *    � SMART Modular Technologies 1999, 2000. All rights reserved.
 *    � Digital Equipment Corporation 1996, 1997. All rights reserved.
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
 *    File Name:    p_sp_st1.c
 *    Author:		Matthew Schnee
 *    Creation Date:04-Jun-1996
 *
 *    Functionality:
 *    Spanish specific functions from sphsetar.c
 *
 ***********************************************************************
 *
 *	Rev	Who		Date		Description
 *	---	-----	-----------	--------------------------------------------
 *	001	MGS		06/04/1996	file created
 *  002	GL		10/30/1996  Merge the changes from V43 code base.
 *	003 EDB		12/10/1996  code change to fix bug.
 *  004 EDB		01/10/1997	reduce tartemp for LAP_R and LAP_RR
 *							from 24 to 14.
 *  005 EDB		10/19/1997	use phTTS handler to replace pDph_t
 *  006 EAB		05/13/1998	Added slowtalk code BATS660
 *  007 EAB		05/20/1998  BATS681  Remove unneeded code--debugforward && debugbackwards
 *  008 GL		05/27/1998  BATS685  Remove unwanted debug code. fix the compiling problem
 *  009 EAB		07/8/1998	Changes to solve addition of new Phedit style of phrom
 *  010 EAB		07/14/1998 	Continued tuning for new code
 *  011 EAB		07/20/1998 	Copied from p_sp_st1.c after merge with new Latin file structure
 *  012 EAB		07/23/1998	The tilt code is bad in that it is all else if but the ordering
 *							was wrong and the proper code such as the bdg tilt is never
 *							excuted. When time availble re-write so that general rules execute
 *							first and then specific rules ovewrite them
 *  013 EAB		10/12/1998 	Tuned voicebar to a lower value to avoid problems
 *  014 EAB		10/23/1998  Modified aspiration per info Juan found 
 *    						in University of Chicago Spanish Dic.
 *  015 EAB		3/26/1999 	BATS 878 Fixed the burst-plosive and plosive-plosive problem 
 *  016 MGS		04/13/2000	Changes for integrated phoneme set 
 *  017 EAB		06/28/2000	Unified Phoneme Set Changes
 *  018 CAB		10/18/2000	Changed copyright info and formatted comments
 *  019	MGS		12/13/2000	Further optimization on gettar
 *  020	MGS		01/18/2001	Removed arg1 arg2 and arg3 from calculations
 *  021	MGS		04/11/2002	ARM7 port
 *	022	CAB		05/22/2002	Removed warnings
 */

#include "dectalkf.h"
#include "ph_def.h"

#define begtyp(a,b) (pDph_t->cur_speaker[(b)>>8]->begtyp[(b)&0x00FF])
#define endtyp(a,b) (pDph_t->cur_speaker[(b)>>8]->endtyp[(b)&0x00FF])
#define burdr(a,b) (pDph_t->cur_speaker[(b)>>8]->burdr[(b)&0x00FF])
#define place(a,b) (pDph_t->cur_speaker[(b)>>8]->place[(b)&0x00FF])
#define ptram(a,b) (pDph_t->cur_speaker[(b)>>8]->ptram[(b)&0x00FF])

 int it_spec_coart (PDPH_T pDph_t,
							short vowel,   /* Current phoneme              */
							short other);   /* Other (next/last) phoneme    */
/* unused param MGS */							/*short initial)*/ /* TRUE if other-vowel          */
/* ******************************************************************
 *      Function Name: sp_gettar()      
 *
 *  	Description: Get target value (or a pointer to first value of diphthong specification
 *                   (do not compute any coarticulatory influences of adjacent phones) 
 *      Arguments: LPTTS_HANDLE_T		Text-to-speech handle
 *				   short nphone_temp
 *
 *      Return Value: short
 *
 *      Comments:
 *
 * ******************************************************************/
int it_gettar (LPTTS_HANDLE_T phTTS, int nphone_temp)
{
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;

	short                   phone_temp, phlas_temp, phnex_temp, tartemp=0, pphotr, npar;
	short                   phone_feat;
//	const short it_place[];
	const short *it_place=pDph_t->cur_speaker[PFSP]->place;


	npar = pDphsettar->np - &PF1;
	if (pDphsettar->np < &PFZ)
		pphotr = (npar) * IT_TOT_ALLOPHONES;
	else
		pphotr = (npar - 1) * IT_TOT_ALLOPHONES;
	/* No table entries for PAP parameter */

	phlas_temp = get_phone(pDph_t,nphone_temp - 1);
	phone_temp = get_phone(pDph_t,nphone_temp);
	phnex_temp = get_phone(pDph_t,nphone_temp + 1);


	phone_feat = phone_feature( pDph_t,phone_temp);

	/* FORMANT FREQUENCIES AND BANDWIDTHS */

	if ((pDphsettar->par_type = partyp[npar]) IS_FORM_FREQ_OR_BW)
	{
		if ((tartemp = pDph_t->p_tar[(phone_temp & PVALUE)  + pphotr]) < -1)
		{
			return (tartemp);	/* Pointer to diph info in p_diph[] */
		}
		

		if (tartemp < -1)
		{
			tartemp = pDph_t->p_diph[-tartemp];
		}
	
		/* Special rule for B3 of /n/ adjacent to /i/ */
		if ((npar == (B3 - F1))
			&& (phone_temp == ITP_N
				|| phone_temp == ITP_NH
				|| phone_temp == ITP_NX)
			&& (((it_place[phnex_temp & PVALUE] & F2BACKI) IS_PLUS)
				|| ((it_place[phlas_temp & PVALUE] & F2BACKI) IS_PLUS)
			)
			)
		{
			tartemp = 300; /* 12/10/1996 EDB, was 1600 */
		}

	
		/* 
	 	 * Special rule for /i/ following /f/
	 	 */
		if ((npar == (B3 - F1))
			&& ((it_place[phone_temp & PVALUE] & F2BACKI) IS_PLUS)
			&& (phlas_temp == ITP_F))
		{
			tartemp = 90;
		}
		/* 
	 	 * Special rule for /r/ and /rr/ after "back" vowel.        8-Jul-86
	 	 */
		if ((phone_temp == ITP_R || phone_temp == ITP_RR)
			&& (phlas_temp == ITP_AP || phlas_temp == ITP_AX))
		{
			switch (npar)
			{
				case (F1 - F1):
					tartemp -= 100;
					break;

			}
		}
	
	}

	/* SOURCE AMPLITUDE TARGETS (AV & AP) */
	else if (pDphsettar->par_type IS_AV_OR_AH)
	{

		/* Rules for voicing amplitude */
		if (npar == AV - 1)
		{
			tartemp = pDph_t->p_tar[(phone_temp & PVALUE) + pphotr];

			

			/* No voicing for stop-release dummy vowels      30-Jul-86       */
			if ((pDph_t->allofeats[nphone_temp] & FDUMMY_VOWEL) IS_PLUS)
			{
				tartemp = 0;
			}
				/* Reduce amplitudes if unstressed */
							/* Reduce amplitudes if unstressed */
			if ((pDph_t->allofeats[nphone_temp] & FSTRESS_2) IS_PLUS)
			{
				tartemp -= 2;
			}
			else if ((pDph_t->allofeats[nphone_temp] & FSTRESS) IS_MINUS)
			{
				tartemp -= 3;
			}
			if (tartemp < 0)
				tartemp = 0;
			
			
		}

		/* Rules for aspiration amplitude */

		else
		{

			tartemp = 0;
			if(phone_temp == ITP_R || phone_temp == ITP_RR)
				tartemp=30;
			if(phone_temp == ITP_LL)
				tartemp=30;
		}
	}

	/* PARALLEL FORMANT AMPLITUDES */

	else if (pDphsettar->par_type IS_PARALLEL_FORM_AMP)
	{
		/* Source spectral tilt: highly tilted for obstruents */

		/* (Voiced obstruents are special case, set F1=0 to signal voicebar) */
		if (pDphsettar->np == &PTILT)
		{
			tartemp = 3;
			if (phone_temp == GEN_SIL)
			{
				tartemp = 3;	   /* eab */
			}
		
			else if (phone_temp == ITP_L && (phnex_temp == ITP_OP 
				|| phlas_temp == ITP_UW || phlas_temp == ITP_AO))
			{
				tartemp = 10 - 5 ;
			}
			else if ((begtyp(pDph_t,phone_temp) == 1) || (endtyp(pDph_t,phone_temp) == 1))
			{
				if (pDph_t->malfem == FEMALE)
				{
					tartemp += 5;
				}
				else
				{
					tartemp += 3;
				}
			}

			
			/* 
			 * Added 7-Jul-86 (MM) to increase tilt for [r] and [rr].
			 */
			else if (phone_temp == ITP_R || phone_temp == ITP_RR)
			{
				tartemp = 24;
			}
			/* 
			 * Added 12-Apr-86 (MM) to set tilt for pseudo-voicebars
			 * Modified 17-Apr-86 (MM) to take value from table.
			 */
			/* eab removed wrong bracket from here */
			else if ((phone_feat & FNASAL) IS_PLUS)
			{
				tartemp = 6;	
			}
			else if ((phone_feat & FOBST) IS_PLUS)
			{
				tartemp = 7;

			}
		}

		/* If ptram > 0, it is a pointer in obstruent array taram */
#if !defined(HLSYN) && !defined(INTEGER)
		else if ((tartemp = ptram(pDph_t,phone_temp)) > 0)
		{

			short begtypnex = begtyp(pDph_t,phnex_temp) - 1;

			if (phnex_temp == GEN_SIL)
				begtypnex = endtyp(pDph_t,phlas_temp) - 1;
			if (begtypnex == OBSTRUENT)
				begtypnex = BACK_UNROUNDED_VOWEL;
			tartemp += (npar - A2 + 1 + (6 * begtypnex));
			tartemp = pDph_t->p_amp[tartemp];

		}
#endif

		/* Reduce amplitudes if dummy vowel next   30-Jul-86 */
		/* Actual value is just a guess */

		if ((pDph_t->allofeats[nphone_temp + 1] & FDUMMY_VOWEL) IS_PLUS)
		{
			tartemp -= 6;
			if (tartemp < 0)
				tartemp = 0;

		}
	}

	/* NASAL ZERO */

	else if (pDphsettar->par_type IS_NASAL_ZERO_FREQ)
	{
		tartemp = NON_NASAL_ZERO;	/* Default for non-nasalized, cancel FP=280 */
		if ((phone_feat & FNASAL) IS_PLUS)
		{
			tartemp = NASAL_ZERO_BOUNDARY;  /* Value dur nasal murmur (527=max) */

		}
	}
	return (tartemp);
}

/* ******************************************************************
 *      Function Name: special_coartic()      
 *
 *  	Description: 
 *
 *      Arguments: PDPH_T pDph_t
 *				   short nfon
 *				   short diphpos
 *
 *      Return Value: short
 *
 *      Comments:
 *
 * *****************************************************************/
short it_special_coartic(PDPH_T pDph_t, short nfon, short diphpos)
{
/* Note: Gen coartic of 5% with adjacent segs elsewhere, so stuff here is big */
/* This routine is only called if the current segment is diph (i.e. a vowel) */
/* 
 * Completely redone for Spanish                                16-Apr-86
 */
	short temp, fonnex, foncur, fonlas;

	temp = 0;
	foncur = get_phone(pDph_t,nfon);
	fonnex = get_phone(pDph_t,nfon + 1);
	fonlas = get_phone(pDph_t,nfon - 1);

	/* 
	 * This assumes that changes are mostly symmetric.
	 */
	temp += it_spec_coart (pDph_t,foncur, fonlas);
	temp += it_spec_coart (pDph_t,foncur, fonnex);

	return (temp);
}


/* ********************************************************************
 *      Function Name: span_spec_coart()      
 *
 *  	Description: Compute vowel coarticulation.  The "rule" was derived by examining
 * 					 a table of nonsense syllables.  It might be a bit overdone.
 *					 Note that it applies after general coarticulation.  The proper
 *					 way to determine the proper values is to disable this routine,
 *					 then generate CVCV nonsense syllables (using -d1024 to print
 *					 only the mid-vowel values), comparing them with natural CVCV
 *					 syllables.
 *					 Note: this function is called only for vowels.
 *
 *      Arguments: PDPH_T pDph_t,
 *				   short vowel,   Current phoneme              
 *				   short other   Other (next/last) phoneme  
 *
 *      Return Value: int
 *
 *      Comments:
 *
 * *****************************************************************/
int it_spec_coart (PDPH_T pDph_t,
							short vowel,   /* Current phoneme              */
							short other)   /* Other (next/last) phoneme    */
/* unused param MGS */							/*short initial)*/ /* TRUE if other-vowel          */

{
	int            			loc;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	 const short *it_place=pDph_t->cur_speaker[PFIT]->place;

	
	loc = it_place[other & PVALUE];
	 if (pDphsettar->np == &PF2)
	{
		switch (vowel)
		{
		case ITP_AP:
			if (loc == FLABIAL)
			{
			}
			else
			{
				switch (other)
				{
				case ITP_CH:
				case ITP_Y:
				case ITP_NH:
					return (100);
				}
			}
			break;

		case ITP_IY:
			switch (other)
			{
				
				/* eab 7/15/98 FOund that coarticulation of eu dipthong lowers 
				the achieved value of e 2formant target*/
			case ITP_UW:
				return(-300);

			}
			break;


			case ITP_EP :		   /* eab 7/16/98* more code for double vowel dipthong*/
				
				switch (other)
				{
	
				case ITP_OP:
					return (-200);
				}
			

				
			break;


		case ITP_OP:
#if 01
/* OUT to prevent overload                              30-Apr-86       */
/* Back in again                                        30-Jul-86       */
			if (loc == FLABIAL
				&& other != ITP_F)
				return (-50);
#endif
			if (other == ITP_Y)
				return (100);
			break;

		case ITP_UW:


#if 01
/* OUT to prevent overload                              30-Apr-86       */
/* Back in again                                        30-Jul-86       */
			if (other == ITP_M
				|| other == ITP_F)
				return (-50);
#endif
			if (loc == FDENTAL
				|| other == ITP_S
				|| loc == FPALATL)
				return (75);
			break;
		}
	}
	else if (pDphsettar->np == &PF3)
	{
		switch (vowel)
		{
		case ITP_AP:
			if (loc == FLABIAL
				&& other != ITP_M)
				return (-100);
			else if (loc == FDENTAL)
				return (75);
			else if (loc == FVELAR)
				return (-75);
			else
			{
				switch (other)
				{
				case ITP_N:
					return (200);
				case ITP_S:
					return (100);
				case ITP_LL:
				case ITP_Y:
					return (-200);
				case ITP_NH:
					return (50);
				}
			}
			break;

		case ITP_IY:
			switch (other)
			{
			case ITP_M:
				return (300);
			case ITP_N:
				return (150);
			case ITP_LL:
				return (-50);
			case ITP_NH:
				return (75);
			break;
			}
		case ITP_EP:
			switch (other)
			{
			case ITP_M:
			case ITP_NH:
			case ITP_N:
				return (150);
			case ITP_OP:
				return(-100);
					
			}
			break;

		case ITP_OP:
			switch (other)
			{
			case ITP_M:
				return (75);
			case ITP_N:
				return (175);
			case ITP_NH:
				return (125);
			case ITP_Y:
			case ITP_F:
				break;
			default:
				if (loc == FLABIAL)
					return (-50);
				else if (loc == FVELAR)
					return (-100);
			}
			break;

		case ITP_UW:
			switch (other)
			{
			case ITP_M:
			case ITP_N:
			case ITP_NH:
			case ITP_LL:
			case ITP_G:
				return (-75);
			}
		}
	}
	return (0);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* F.                      S E T L O C                              */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* ******************************************************************
 *      Function Name: forw_smooth_rules()      
 *
 *  	Description: Determine parameters of forward smoothing  f(pholas,phcur) 
 *
 *      Arguments: 	PDPH_T pDph_t, 
 *				   	short shrif, 
 *				   	short pholas,
 *				    short fealas, 
 *				    short feacur, 
 *				    short struclas,
 *				    short struccur, 
 *				    short feanex
 *
 *      Return Value: void
 *
 *      Comments:
 *
 * *****************************************************************/
void it_forw_smooth_rules(LPTTS_HANDLE_T phTTS, short shrif, int pholas,
								 int fealas, int feacur, short struclas,
				                 short struccur, short feanex)
{
	short                   temp;	  
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
//	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
 	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
    const short *it_place=pDph_t->cur_speaker[PFIT]->place;

	//debugforward ("Set default", pDphsettar->np);

/* Formant frequencies */
/* Dipthongs first     */
	if (pDphsettar->par_type IS_FORM_FREQ_OR_BW
		&& (feacur & FVOWEL) IS_PLUS
		&& (fealas & FSEMIV) IS_PLUS
		&& (struccur & FBOUNDARY) == 0)
	{
		pDphsettar->durtran = pDph_t->durfon >> 1;
		pDphsettar->bouval = (pDphsettar->np->tarlas + pDphsettar->np->tarcur) >> 1;
		//debugforward (" dipthong (vowel) transition",pDphsettar->np);
	}
	else if (pDphsettar->par_type IS_FORM_FREQ_OR_BW
			 && (feacur & FSEMIV) IS_PLUS
			 && (fealas & FVOWEL) IS_PLUS
			 && (struccur & FBOUNDARY) == 0)
	{
		pDphsettar->durtran = pDph_t->durfon >> 1;
		pDphsettar->bouval = (pDphsettar->np->tarlas + pDphsettar->np->tarcur) >> 1;
		//debugforward (" dipthong (semivowel) transition",pDphsettar->np);
	}
	else if (pDphsettar->par_type IS_FORM_FREQ)
	{
		/* 0. Use default values for obst-obst transition */
		if ((feacur & FSONOR) IS_PLUS)
		{
			if ((feacur & FSONCON) IS_MINUS)
			{
				pDphsettar->durtran = NF45MS;
				if (pDphsettar->phcur == ITP_Y)	   /* Faster for y */
					pDphsettar->durtran = NF25MS;  /* 23-Apr-86    */
				if ((fealas & FSONCON) IS_PLUS)
				{
					/* 1. Soncon-vowel transition, use 25-75% rule */
					pDphsettar->bouval = (pDphsettar->bouval + pDphsettar->np->tarlas) >> 1;
					/* Make F1 discontinuous for light /l/           */
					/* Block if transition into silence              */
					/* (Suggestion from DHK, June 5)                 */
					if (pDphsettar->phcur != GEN_SIL
						&& (pholas == ITP_L) && (pDphsettar->np == &PF1))
					{
						pDphsettar->bouval += 80;
					}
#if 0
					/* Make F3 & F2 transitions slower out of /r/ */
					if (((pholas == ITP_R) || (pholas == ITP_RR))
						&& (pDphsettar->np != &PF1))
					{
						pDphsettar->durtran = NF70MS;
					}
#endif
					//debugforward (" soncon /vowel transition",pDphsettar->np);
				}
				else
				{
					/* 2. Vowel-[vowel/dh,gh,bh,ITP_J] transition */
					/* Preceeding seg has strong influence on [h] init val */
					/* if (phonex == ITP_DH) { bouval = (bouval + np->tarlas) >> 1;
					 * 
 					 * }            
 					 */

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
		//debugforward (" sonorant transition",pDphsettar->np);

		/* Bound value = previous target if current phone is sil */
		if (pDphsettar->phcur == GEN_SIL)
		{
			/* GL 10/30/96 changed to be same as English */
			if (pDph_t->nphone > 1)
			{
				pDphsettar->bouval = pDphsettar->np->tarlas;
			}
			else
			{
				pDphsettar->bouval = pDphsettar->np->tarnex;
			}
            pDphsettar->durtran = pDph_t->durfon;
            /*
			pDphsettar->bouval = pDphsettar->np->tarlas;
			pDphsettar->durtran = pDph_t->durfon;
			*/
		}
		else
		{
			if (pDphsettar->np <= &PF3)
			{
/* EAB 6/24/98 FOR DEBUG
			if (pDphsettar->np == &PF1)
			{
				WINprintf("embeeded f1= %d \n",pDphsettar->bouval);
			}

  */
				/* 5. pholas=obst, phcur=sonor transition */

				setloc (phTTS, (short)(pDph_t->nphone - 1), pDph_t->nphone, INITIAL, (short)(pDph_t->nphone - 2), feanex);
				/* 6. pholas=sonor, phcur=obst transition */
				setloc (phTTS, pDph_t->nphone, (short)(pDph_t->nphone - 1), FINAL, (short)(pDph_t->nphone + 1), feanex);

			}
#if 0
			/* 
			 * Doesn't work.
			 */
			/* Dummy vowel for final plosive release into silence is too */
			/* short for an extensive formant transition, make tran less */
			if ((struccur & FDUMMY_VOWEL) IS_PLUS)
			{
/* OUT                  xx += ((bouval - np->tarend) >> 1); np->tarend += xx;   (DOESN'T WORK) END OUT */
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
#ifndef HLSYN
				/* Lower F2 & F3 of [n] nasal murmur before front vowels */
				else if (((pDphsettar->phcur == ITP_N))
						 && (begtyp(pDph_t,pDphsettar->phonex) == 1))
				{
					if (pDphsettar->np == &PF2)
					{
						pDphsettar->bouval -= 100;
						if ((it_place[pDphsettar->phonex & PVALUE] & F2BACKI) IS_PLUS)
						{
							pDphsettar->bouval -= 100;
						}
					}
					if (pDphsettar->np == &PF3)
						pDphsettar->bouval -= 100;
				}
				/* Lower F2 of [m] nasal murmur near [i,e,ix] */
				else if ((pDphsettar->np == &PF2)
						 && (pDphsettar->phcur == ITP_M)
						 && ((it_place[pholas & PVALUE] & F2BACKF) IS_PLUS))
				{
					pDphsettar->bouval -= 150;
				}
				//debugforward (" nasals",pDphsettar->np);
#endif
			}
		}

		/* Shrink transition dur inside sonor if sonor short */
		if (((feacur & FOBST) IS_MINUS)
			&& (endtyp(pDph_t,pholas) != OBSTRUENT)	/* Unless prev seg is obst */
			&& (pDphsettar->durtran > 0))
		{
			//pDph_t->arg1 = pDphsettar->durtran;
			//pDph_t->arg2 = shrif;
			pDphsettar->durtran = mlsh1 (pDphsettar->durtran,shrif) + 1;
		}
		//debugforward (" Other formant frequency rule",pDphsettar->np);
	}

	/* Formant bandwidths */
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
		//debugforward (" After BW initial setup",pDphsettar->np);

		/* Treat boundary with silence */
		/* 
		 * This widens the glottis (?) for transitions from
		 * silence.  If you do this for [L] and [LL], it
		 * sounds like [al].
		 */
		if (pholas == GEN_SIL && ((feacur & FSONCON) IS_MINUS))
		{
			pDphsettar->bouval = pDphsettar->np->tarcur + ((&PB3 - pDphsettar->np) * 50);
			//debugforward (" Transition from silence",pDphsettar->np);
		}
		else if (pDphsettar->phcur == GEN_SIL)
		{
			pDphsettar->bouval = pDphsettar->np->tarlas + ((&PB3 - pDphsettar->np) * 50);
			if (((phone_feature( pDph_t,pDph_t->allophons[pDph_t->nphone - 2]) & FVOICD) IS_MINUS)
				&& (pDphsettar->np == &PB1))
			{
				pDphsettar->bouval = 260;	   /* Kluge to avoid discontinutiy */
			}
			pDphsettar->durtran = NF50MS;
			//debugforward (" Transition into silence",pDphsettar->np);
		}
		/* BW1 widen, to nasalize transition out of previous nasal */
		if ((fealas & FNASAL) IS_PLUS)
		{
			pDphsettar->bouval = pDphsettar->np->tarcur;   /* B2,B3 not influ by nasal */
			if (pDphsettar->np == &PB1)
			{
				pDphsettar->durtran = NF100MS;
				pDphsettar->bouval += 70;
			}
			//debugforward (" Transition from nasal",pDphsettar->np);
		}
		/* Nasals have constant bandwidths at target values */
		if ((feacur & FNASAL) IS_PLUS)
		{
			pDphsettar->durtran = 0;
			//debugforward (" Nasal has const par val",pDphsettar->np);
		}
		/* Special rule for [fi] */
		if ((pDphsettar->np == &PB3)
			&& ((it_place[pDphsettar->phcur & PVALUE] & F2BACKI) IS_PLUS)
			&& (pholas == ITP_F))
		{
			pDphsettar->durtran = 0;
			//debugforward (" [fi] special rule",pDphsettar->np);
		}
		//debugforward (" Other bandwidth rule",pDphsettar->np);
	}

	/* Source amplitudes, including parallel formant amplitudes */
	/* Default is max of [average,tarcur-12,tarlas-12] */
	else if ((pDphsettar->par_type IS_PARALLEL_FORM_AMP)
			 || (pDphsettar->par_type IS_AV_OR_AH))
	{
		/* See if onset, i.e. plosive or large source intensity increase */
		temp = pDphsettar->np->tarcur - 10;
		if ((pDphsettar->bouval < temp) || ((fealas & FPLOSV) IS_PLUS))
		{					   /* 7-May-86    */
			pDphsettar->bouval = temp;
			/* 
			 * No onset transition for B, D, G (22-Jan-86, MM)
			 */
			if ((feacur & FOBST) IS_MINUS)
			{
				pDphsettar->durtran = NF15MS;
				if (fealas ==
					(FVOICD + FOBST + FPLOSV + FCONSON + FBURST + FVBAR))
					pDphsettar->durtran = 0;
			}
			/* Voicing is special */
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
					pDphsettar->bouval = pDphsettar->np->tarcur - 2;
				}
			}
			//debugforward (" Onset",pDphsettar->np);
		}
		/* If last nasal, and source amp increased, abrupt onset */
		if (((fealas & FNASAL) IS_PLUS)
			&& ((feacur & FVOICD) IS_PLUS))
		{
			pDphsettar->durtran = 0;
			//debugforward (" Onset from nasal",pDphsettar->np);
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
			/* 
			 * Added to shorten stop burst               1-May-86
			 * Changed 20msec to 30msec                 22-Jul-86
			 */
			if (pDphsettar->phcur == GEN_SIL)
			{
				pDphsettar->durtran = ((fealas & FBURST) IS_PLUS) ? NF30MS : NF70MS;
			}
			/* Except voicing offset is abrupt */
			if (pDphsettar->np == &PAV)
				pDphsettar->durtran = 0;
			//debugforward (" Offset",pDphsettar->np);
		}
		/* Buildup A4 gradually in [CH and YH] */
		if (pDphsettar->np == &PA4)
		{
			if ((pDphsettar->phcur == ITP_CH))
			{
				pDphsettar->durtran = pDph_t->durfon - NF15MS;
				pDphsettar->bouval = pDphsettar->np->tarcur - 30;
				//debugforward (" CH/YH rule",pDphsettar->np);
			}
		}

		/* Offset of a vowel into voiceless open vocal tract is breathy */
		if (pDphsettar->np == &PAP)
		{
			if ((pDphsettar->phcur == GEN_SIL)
				|| feacur == (FOBST | FCONSON))
			{
				/* 
				 * [SI], [F], [TH], [S], [SH]
				 */
				if ((fealas & FSYLL) IS_PLUS)
				{
					if (pDphsettar->phcur == GEN_SIL)
					{
						/* 
						 * Changed 56 -> 40             22-Jul-86
						 */
						pDphsettar->bouval = 40;
						pDphsettar->durtran = NF80MS;
					}
					else
					{
						/* 
						 * Changed 52 -> 36             22-Jul-86
						 */
						pDphsettar->bouval = 36;
						pDphsettar->durtran = NF45MS;
					}
				}
				//debugforward (" Spanish AH si/f/th/s/sh rule",pDphsettar->np);
			}
		}
		/* Tilt parameter jumps to target values */
		if (pDphsettar->np == &PTILT)
		{
			pDphsettar->durtran = 0;
		}
	}
	/* Nasal antiformant frequency */
	else if (pDphsettar->par_type IS_NASAL_ZERO_FREQ)
	{
		pDphsettar->durtran = 0;
		if (((fealas & FNASAL) IS_PLUS)
			&& ((feacur & FNASAL) IS_MINUS))
		{
			pDphsettar->bouval = NASAL_ZERO_BOUNDARY;
			/* 
			 * Changed to give quick transition         28-Apr-86
			 * for "normal" nasals, slow for ~n
			 */
			pDphsettar->durtran = (pholas == ITP_NH) ? NF80MS : NF40MS;
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
	/*EAB 6/24/98 
		if (pDphsettar->np == &PF1)
			WINprintf("f1= %d \n",pDphsettar->bouval);
			*/
}


/* ******************************************************************
 *      Function Name: back_smooth_rules()      
 *
 *  	Description: 
 *
 *      Arguments: PDPH_T pDph_t
 *				   short shrib
 *				   short feacur
 *				   short feanex 
 *				   short strucnex
 *
 *      Return Value: void
 *
 *      Comments:
 *
 * *****************************************************************/
void it_back_smooth_rules (LPTTS_HANDLE_T phTTS, short shrib, int feacur,
				   int feanex, short strucnex)
{
	short                   temp;	   /* MVP MI : This varaible is made local */
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
//	PKSD_T                  pKsd_t = phTTS->pKernelShareData;

	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
 const short *it_place=pDph_t->cur_speaker[PFIT]->place;

	    //debugbackward("Backward (cur/nex) default",pDphsettar->np);
	/* Formant frequencies */
	if (pDphsettar->par_type IS_FORM_FREQ_OR_BW
		&& (feacur & FVOWEL) IS_PLUS
		&& (feanex & FSEMIV) IS_PLUS
		&& (strucnex & FBOUNDARY) == 0)
	{
		pDphsettar->durtran = pDph_t->durfon >> 1;
		pDphsettar->bouval = (pDphsettar->np->tarnex + pDphsettar->np->tarcur) >> 1;
		//debugbackward (" dipthong (vowel) transition",pDphsettar->np);
	}
	else if (pDphsettar->par_type IS_FORM_FREQ_OR_BW
			 && (feacur & FSEMIV) IS_PLUS
			 && (feanex & FVOWEL) IS_PLUS
			 && (strucnex & FBOUNDARY) == 0)
	{
		pDphsettar->durtran = pDph_t->durfon >> 1;
		pDphsettar->bouval = (pDphsettar->np->tarnex + pDphsettar->np->tarcur) >> 1;
		//debugbackward (" dipthong (semivowel) transition",pDphsettar->np);
	}
	else if (pDphsettar->par_type IS_FORM_FREQ)
	{        
		/* 0. Use default values for obst-obst transition */
		if ((feacur & FSONOR) IS_PLUS)
		{
			pDphsettar->durtran = NF45MS;
/* ****************** NOT USED *************************************/
#if 0
		  NOTE:[y] and[yh] are now     obstruents
			if                      (pDphsettar->phcur == ITP_YH)		/* Faster for y */
				pDphsettar->durtran = NF25MS;	/* 23-Apr-86    */
#endif // 0
/* *****************************************************************/

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
					/* First formant jumps down 80 Hz in /l/ */
					/* Block if transition from silence              */
					/* Suggestion from DHK, June 5, 85               */
					if (pDphsettar->phcur != GEN_SIL
						&& (pDphsettar->phonex == ITP_L) && (pDphsettar->np == &PF1))
					{
						pDphsettar->bouval += 80;
					}
				}
				else
				{
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
			if (pDphsettar->np <= &PF3)
			{
				/* 5. phcur=sonor, phonex=obst transition */
				setloc (phTTS, (short)(pDph_t->nphone + 1), pDph_t->nphone, FINAL, (short)(pDph_t->nphone + 2), feanex);
				/* 6. phcur=obst, phonex=sonor transition */
				setloc (phTTS, pDph_t->nphone, (short)(pDph_t->nphone + 1), INITIAL, (short)(pDph_t->nphone - 1), feanex);
			}
			/* Transitions slow inside obstruents */
			if ((feacur & FOBST) IS_PLUS)
			{
				pDphsettar->durtran = (pDphsettar->np == &PF1) ? NF20MS : NF30MS;
				/* Transitions take all of plosive duration */
				if ((feacur & FPLOSV) IS_PLUS)
				{
					pDphsettar->durtran = pDph_t->durfon;
				}
				//debugbackward (" Obstruent",pDphsettar->np);
			}

			/* Higher formant transitions slow inside a nasal */
			if ((feacur & FNASAL) IS_PLUS)
			{
				pDphsettar->durtran = pDph_t->durfon;
				/* Except F1, which jumps to value below FNZRO */
				if (pDphsettar->np == &PF1)
				{
					pDphsettar->durtran = 0;
				}
#ifndef HLSYN
				/* Lower F2 of [m] murmur near [i,y,yx] */
				else if ((pDphsettar->np == &PF2)
						 && (pDphsettar->phcur == ITP_M )
						 && ((it_place[pDphsettar->phonex & PVALUE] & F2BACKI) IS_PLUS))
				{
					pDphsettar->bouval -= 150;
				}
#endif
			}
		}

		/* Shrink tran dur inside sonorant if sonorant short */
		if (((feacur & FOBST) IS_MINUS)
			&& (begtyp(pDph_t,pDphsettar->phonex) != OBSTRUENT)	/* Unless next seg is obst */
			&& (pDphsettar->durtran > 0))
		{
			///pDph_t->arg1 = pDphsettar->durtran;
			//pDph_t->arg2 = shrib;
			pDphsettar->durtran = mlsh1 (pDphsettar->durtran,shrib) + 1;
		}
		//debugbackward (" Other formant freq. rule",pDphsettar->np);
	}
	/* Formant bandwidths */
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
		//debugbackward (" After BW initial setup",pDphsettar->np);
		/* Treat boundary with silence */
		/* OUT ??? */ 
		if (pDphsettar->phonex == GEN_SIL)
		{
			pDphsettar->bouval = pDphsettar->np->tarend + ((&PB3 - pDphsettar->np) * 50);
			pDphsettar->durtran = NF50MS;
			//debugbackward (" Transition to silence",pDphsettar->np);
		}
		else if (pDphsettar->phcur == GEN_SIL)
		{
			pDphsettar->bouval = pDphsettar->np->tarnex + ((&PB3 - pDphsettar->np) * 50);
			pDphsettar->durtran = NF50MS;
			/* 
			 * Faster transition into [L] and [LL]
			 */
			if ((feanex & FSONCON) IS_PLUS)
				pDphsettar->durtran = NF15MS;
			//debugbackward (" Transition from silence",pDphsettar->np);
		}

		/* BW1 widen, to nasalize transition into next nasal */
		if ((feanex & FNASAL) IS_PLUS)
		{
			pDphsettar->bouval = pDphsettar->np->tarend;
			if (pDphsettar->np == &PB1)
			{
				/* 
				 * Changed 20ms -> 40ms                 28-Apr-86
				 */
				pDphsettar->durtran = NF40MS;	/* shorter transition   */
				pDphsettar->bouval += 100;
			}
			//debugbackward (" Transition to nasal",pDphsettar->np);
		}
		/* Nasals have constant bandwidths at target values */
		if ((feacur & FNASAL) IS_PLUS)
		{
			pDphsettar->durtran = 0;
			//debugbackward (" Nasal has const. par val",pDphsettar->np);
		}
		//debugbackward (" Bandwidth result",pDphsettar->np);
	}

	/* Source amplitudes, including parallel formant amplitudes */
	else if ((pDphsettar->par_type IS_PARALLEL_FORM_AMP)
			 || (pDphsettar->par_type IS_AV_OR_AH))
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
			//debugbackward (" Onset",pDphsettar->np);
		}
		/* Voicing is special:  onset is abrupt, except if a voiced fric */
		if ((pDphsettar->np == &PAV) && (pDphsettar->bouval < pDphsettar->np->tarnex)
			&& feacur != (FVOICD | FSONOR | FCONSON))
		{
			/* 
			 * All but BH, DH, GH, YH, V, Z
			 */

			/* 
			 * All but Y, V, Z
			 */

			pDphsettar->durtran = 0;
			//debugbackward (" Make next onset abrupt",pDphsettar->np);
			/* Voicebar dies out in a voiced plosive */
			if (((feacur & FPLOSV) IS_PLUS)
				|| (pDphsettar->phcur == ITP_CH))
			{
				if ((feacur & FPLOSV) IS_PLUS)
				{
					if ((feacur & FVOICD) IS_PLUS)
					{
						pDphsettar->bouval = pDphsettar->np->tarend - 3;
						pDphsettar->durtran = NF45MS;
						//debugbackward (" Voicebar dies out",pDphsettar->np);
					}		  
							
					else
					{
						pDphsettar->bouval = 0;
					}
					goto endbsmo;
				}
			}
		}
		/* 
		 * Spanish prevoices [s] and [th]               8-May-86
		 * before voiced consonants
		 * (The exact amount is dialectical and depends
		 * on the pronunciation style.  We'll try 50%
		 * for want of anything better.
		 *
		 * This is essentially the allophonic rule
		 *      [s]->[z] / _ [+voice]
		 */
		if ((pDphsettar->np == &PAV)
			&& (pDphsettar->phcur == ITP_S )
			&& ((feanex & (FCONSON | FVOICD)) == (FCONSON | FVOICD)))
		{
			pDphsettar->durtran = pDph_t->durfon >> 1;
			//debugbackward (" [s, th] prevoicing rule",pDphsettar->np);
		}

		/* If next nasal, and current phone is voiced, set AV const */
		if (((feanex & FNASAL) IS_PLUS)
			&& ((feacur & FVOICD) IS_PLUS))
		{
			pDphsettar->durtran = 0;
			//debugbackward (" AV const in voiced to nasal",pDphsettar->np);
		}
		/* If current phone nasal, and next phone is voiced, AV constant */
		if (((feacur & FNASAL) IS_PLUS)
			&& ((feanex & FVOICD) IS_PLUS))
		{
			pDphsettar->durtran = 0;
			//debugbackward (" Make murmur const AV",pDphsettar->np);
		}
		/* See if offset, i.e. source intensity decreasing */
		temp = pDphsettar->np->tarend - 10;
		/* Plosive burst does not get attenuated during offset */
		if ((feacur & FPLOSV) IS_PLUS)
		{
			/* 
			 * Change from "always NF15MS"              22-Jul-86
			 * The value is changed by a special rule.
			 */
			if ((feacur & FBURST) IS_MINUS)
				pDphsettar->durtran = mstofr( burdr(pDph_t,pDphsettar->phcur) );	/* Use inherent */
			if (pDphsettar->phcur != ITP_CH )
			{
				temp = pDphsettar->np->tarend;
			}
			//debugbackward ("Plosive burst duration",pDphsettar->np);
		}
		if (pDphsettar->bouval < temp)
		{
			pDphsettar->bouval = temp - 3;
/* ***************** NOT USED **************************************/ 
#if 0
			/* Out (fix kiki problem) */
			pDphsettar->durtran = NF20MS;  /* Guess */
#endif // 0
/* *****************************************************************/
			if (pDphsettar->np == &PAV)
			{
				pDphsettar->bouval = temp + 4;
				/* Voicing amp falls gradually at end of phrase */
				if (pDphsettar->phonex == GEN_SIL)
				{
					pDphsettar->bouval = pDphsettar->bouval - 6;
					pDphsettar->durtran = NF40MS;	/* Guess                */
				}
			}
			if (pDphsettar->np == &PAP)
			{
				pDphsettar->bouval = PAP.tarend - 36;
			}
			//debugbackward (" Offset to noise",pDphsettar->np);
		}
		/* No smoothing of source amps if next segment has burst */
		if (((feanex & FPLOSV) IS_PLUS)
			|| (pDphsettar->phonex == ITP_CH))
		{
			pDphsettar->durtran = 0;
			//debugbackward (" Stop closure next",pDphsettar->np);
		}

		/* Onset of a vowel from voiceless open vocal tract is breathy */
		if (pDphsettar->np == &PAP)
		{
			if ((pDphsettar->phcur == GEN_SIL)
				|| feacur == (FOBST | FCONSON))
			{
				/* 
				 * (Select F, TH, S, SH)
				 * Select vowels only, so [l] and [ll] sound ok.
				 */
				if (((feanex & FSYLL) IS_PLUS))
				{
					pDphsettar->bouval = 40;
					pDphsettar->durtran = NF40MS;
				}
				//debugbackward (" Onset of vowel from vless voc tract",pDphsettar->np);
			}
			/* Offset of a vowel into silence is breathy */
			if (((feacur & FSYLL) IS_PLUS)
				&& (pDphsettar->phonex == GEN_SIL))
			{
				/* 
				 * Less effect for Spanish              22-Jul-86
				 */
				pDphsettar->bouval = 40;
				pDphsettar->durtran = NF50MS;
				//debugbackward (" Breathy offset of vowel to silence",pDphsettar->np);
			}
		}

		/* Tilt parameter jumps to target values except before voiceless */
		if (pDphsettar->np == &PTILT)
		{
			pDphsettar->durtran = 10;	   /* eab changed from 0 don't believe in 0 time */
			if (((feacur & FVOICD) IS_PLUS)
				&& ((feacur & FNASAL) IS_MINUS)
				&& ((feanex & FVOICD) IS_MINUS))
			{
				pDphsettar->durtran = NF50MS;
				pDphsettar->bouval = pDphsettar->np->tarnex >> 1;
				/* Breathy offset to a vowel */
				if (pDphsettar->phonex == GEN_SIL)
				{
					pDphsettar->durtran = NF130MS;
					pDphsettar->bouval = pDphsettar->np->tarnex;
				}
			}
			//debugbackward ("tilt",pDphsettar->np);
		}
	}

	/* Nasal antiresonator frequency */
	else if (pDphsettar->par_type IS_NASAL_ZERO_FREQ)
	{
		pDphsettar->durtran = 0;
		/* Nasalization cue: place zero between F1 and FP */
		if (((feanex & FNASAL) IS_PLUS)
			&& ((feacur & FNASAL) IS_MINUS))
		{
			pDphsettar->bouval = NASAL_ZERO_BOUNDARY;
			pDphsettar->durtran = NF20MS;
		}
		//debugbackward ("nasals",pDphsettar->np);
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
 *      Arguments:	LPTTS_HANDLE_T phTTS	Text-to-speech handle
 *					short fealas
 *			   		short feacur 
 *			   		short feanex 
 *			   		short struclm2
 *			   		short struccur 
 *			   		short pholas
 *			   		short struclas 
 *
 *      Return Value: void
 *
 *      Comments:
 *
 * *****************************************************************/
void it_special_rules (LPTTS_HANDLE_T phTTS, short fealas, int feacur, int feanex,
							  short struclm2, short struccur, short pholas, short struclas)
{
	short                   bdur, vot; /* MVP made as a local variable */
	short                   closure_dur;	/* MVP made as a local variable */
	

	PDPH_T                  pDph_t = phTTS->pPHThreadData;
#ifdef FASTTYPING_MODE	
	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
#endif
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	 const short *it_place=pDph_t->cur_speaker[PFIT]->place;

	/* SPECIAL RULE 1: Burst duration for plosives and affricates             */

	bdur = burdr(pDph_t,pDphsettar->phcur);   /* Look up inher. burst dur in msec in table */

	if ((feacur & FBURST) IS_PLUS)
	{
		bdur = mstofr (bdur);		   /* Convert to frames         */

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
#ifndef HLSYN
		if ((feanex & (FNASAL | FPLOSV)) IS_PLUS)
		{
			//EAB Don't release a plosive followed by a nasal period
			// The former comment is not quite correct becaue the place of articulation
			//between a nasal and a plosive can't be the same becuase the nasal's
			// doesn't have a place of articulation 2/26/99
			if((feacur & FPLOSV ) IS_PLUS)
				bdur=0;
			if ((it_place[pDphsettar->phcur & PVALUE] | MASKFRONT )== (it_place[pDphsettar->phonex] | MASKFRONT ))
			{		/* yes they're both done up front */
				bdur = 0;
			}
			else if (( it_place[pDphsettar->phcur & PVALUE] )== ( it_place[pDphsettar->phonex] ))
			{		/* yes they're both done up front */
				bdur = 0;
			}
		}
#endif
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

		for (pDphsettar->np = &PA2; pDphsettar->np <= &PAB; pDphsettar->np++)
		{							   /* All fric gains to */
				if(it_place[pDphsettar->phcur & PVALUE] & FLABIAL)
			{
				PAREAL.tspesh=closure_dur;
				PAREAB.tspesh =0;
				PTONGUEBODY.tspesh=0;
			}
			else if(it_place[pDphsettar->phcur & PVALUE] & BLADEAFFECTED )
			{
				PAREAL.tspesh=0;
				PAREAB.tspesh=closure_dur;
				PTONGUEBODY.tspesh=0;
			}
				else if(it_place[pDphsettar->phcur & PVALUE] & FVELAR )
			{
				PAREAL.tspesh=0;
				PAREAB.tspesh=0;
				PTONGUEBODY.tspesh=closure_dur;
			}
			pDphsettar->np->tspesh = closure_dur;	/* zero during closur */
			pDphsettar->np->pspesh = 0;
		}
	}
	/* SPECIAL RULE 2: Voice onset time for aspirated plosives */

	vot = 0;
	if ((((fealas & FPLOSV) IS_PLUS)
		 && ((fealas & FVOICD) IS_MINUS)
		 && ((feacur & FSONOR) IS_PLUS ))) 
	{
		PAP.pspesh = 48;	
		 //but we'll add that level later */
		if (begtyp(pDph_t,pDphsettar->phonex) != 1)
		{
			PAP.pspesh = 52;		   /* Stronger asp before +back */
		}
		

		vot = NF30MS;				   /* Asp dur for /p,t,k/ before stressed sonor */
		if ((struccur & FSTRESS_1) IS_MINUS)
		{
			vot = NF25MS;			   /* Vot shorter if vowel not stressed */
			PAP.pspesh -= 3;
		}
		if (((feacur & FSONCON) IS_PLUS) )
		{
			PAP.pspesh += 3;		   /* Aspiration stronger in sonor cons */
		}

		/* eab 2/6/976 Found code that was causing after Murhty port. Vlaue of pholm2
		was not being retained- substituted global variables that already exsist
		after release the old and I think vestigal variables need to be removed
		this problem affect all languages but in fact the code didn't exist in German
		at all but was needed don't know is struclm2 is working either*/

		if ( phone_feature( pDph_t,pDph_t->allophons[pDph_t->nphone -2]) == (FOBST+FCONSON ))          
		{
			if ((struclm2 & FBOUNDARY) IS_MINUS )
			{
				vot = NF15MS;	   
			}
		}
		else if (((feacur & FSYLL) IS_MINUS))
		{
			vot += NF20MS;			   /* Vot longer in a sonorant consonant */
		}
		if (vot >= pDph_t->durfon)
		{
			vot = pDph_t->durfon - 1;
			
		}
		/* Vot cannot exceed 1/2 duration of a stressed vowel */
		if ((vot > (pDph_t->durfon >> 1))
			&& ((feacur & FSYLL) IS_PLUS)
			&& ((struccur & FSTRESS_1) IS_PLUS))
		{
			vot = pDph_t->durfon >> 1;
		}
		if(pDph_t->allophons[pDph_t->nphone] == ITP_R)
			vot = 4;

		/* A dummy vowel is used to release a voiceless plosive into silence */
		if ((struccur & FDUMMY_VOWEL) IS_PLUS)
		{
			vot = pDph_t->durfon;
			PAP.pspesh -= 3;
		}
		/* eab in fast mode we simply when to model a much reduced faster
		release--no time to build up large pressures*/

#ifdef FASTTYPING_MODE
		if(phTTS->bInTypingMode == TRUE || pKsd_t->sprate >300)
		{
			
			vot=vot>>2;
			if(vot == 0)
				vot=1;
		

		PAV.pspesh += 20;
		PAP.pspesh -=5;
		}
#endif
		PAV.tspesh = vot;
		PAP.tspesh = vot;

		/* Widen 1st and 2nd formant bws when glottis open for aspir */
		PB1.tspesh = vot;
		PB2.tspesh = vot;
		PB1.pspesh = PB1.tarcur + 250;
		PB2.pspesh = PB2.tarcur + 70;
	}
	/* SPECIAL RULE 3: Create realistic voicebar, avoid pops and clicks */
	/* Amp of voicebar set here, AV target in table invalid */
	/* Set AV=0 for last 12.8 ms, let AV die out, thus avoid click */
	/* Set to under 250 to signal voicebar */

	/* Problem: spectrum has too much F4 if f2,3 are high, as in [i] */
	if (((feacur & FBURST) IS_PLUS)
		&& ((feacur & FVOICD) IS_PLUS)
		&& ((fealas & FVOICD) IS_PLUS)
		&& ((feanex & FVOICD) IS_MINUS)		/* Voicebar only if next -V */
		)
	{
		PAV.tspesh = pDph_t->durfon - NF15MS;
		PB1.tspesh = pDph_t->durfon;
		PB2.tspesh = pDph_t->durfon;
		PB3.tspesh = pDph_t->durfon;
		PAV.pspesh = 33;
		PB1.pspesh = 1000;
		PB2.pspesh = 1000;
		PB3.pspesh = 1500;
	}
}



#ifdef NOT_DONE_YET
/* ******************************************************************
 *      Function Name: shrdur()
 *
 *  	Description: SHRINK OR EXPAND DURIN NONLINEARLY IN A DIPHTHONG TO PRESERVE 
 * 					 TENDENCY TOWARD CONSTANT DURATION OF TRANSITION PORTION 
 *					 WITH CHANGES IN VOWEL DURATION
 *
 *      Arguments:	PDPH_T pDph_t
 *					short durin
 *					short inhdr_frames
 *				   	short shrink
 *
 *      Return Value: int
 *
 *      Comments:
 *
 * *****************************************************************/
int shrdur(PDPH_T pDph_t, short durin, short inhdr_frames, short shrink)
{
	short                   halfinhdr, quarterinhdr, foldswitch;
	short 					arg1,arg2;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;

	/* Convert from ms to number of frames */
	durin = mstofr (durin);
	halfinhdr = inhdr_frames >> 1;
	quarterinhdr = halfinhdr >> 1;
	/* Fold durin over about halfinhdr */
	foldswitch = 0;
	if (durin > halfinhdr)
	{
		durin = inhdr_frames - durin;
		foldswitch = 1;
	}
	if (durin < quarterinhdr)
	{
		/* Extra shrinkage about quartertime */
		if (shrink > FRAC_ONE)
		{
			/* Shrink/4 + (3/4 * FRAC_ONE) */
			arg2 = (shrink >> 2) + FRAC_3_4THS;
		}
		else
		{
			/* (2 * shrink) - FRAC_ONE */
			arg2 = (shrink - FRAC_ONE) + shrink;
		}
		if (arg2 <= 0)
			arg2 = 1;
		arg1 = durin;
		durin = mlsh1 (arg1,arg2);
	}
	else
	{
		/* Extra shrinkage about quartertime */
		if (shrink > FRAC_ONE)
		{
			/* (3/2 * FRAC_ONE ) - (shrink/2) */
			arg2 = FRAC_3_HALVES - (shrink >> 1);
		}
		else
		{
			arg1 = shrink;
			if (arg1 < 8193)
				arg1 = 8193;
			/* (3 * FRAC_ONE ) - (2 * shrink) */
			arg2 = ((((FRAC_ONE - arg1) + FRAC_ONE) - arg1)
					+ FRAC_ONE);
		}
		if (arg2 <= 0)
			arg2 = 1;
		arg1 = halfinhdr - durin;
		durin = halfinhdr - mlsh1 (arg1,arg2);
	}
	if (foldswitch == 1)
		durin = inhdr_frames - durin;
	arg1 = durin;
	arg2 = shrink;
	temp = mlsh1 (arg1,arg2) + 1;
	return (temp);
}
//#ifdef NOT_DONE_YET
#endif 