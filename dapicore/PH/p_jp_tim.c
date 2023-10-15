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
 ***********************************************************************
 *    Revision History:
 *
 * Rev  Who     Date            Description
 * ---  -----   -----------     --------------------------------------------
 * 0001 DK 		09/01/1984      Initial creation
 * 0002 DGC		12/27/1984	    Modified for the 80186.
 * 0003 DGC		01/02/1985    	Added some conditional calls to the "mstofr"
 *          					routine. Some of the conversions from MS to
 *          					frames caused overflow on 16 bit machines.
 * 0004 DK		02/26/1985 	    [nt] cluster too long
 * 0005 DK		03/18/1985    	period pause and comma pause code had a bug
 * 0006 DK		03/25/1985     	Let phrase-final lengthening apply to word before prep
 * 0007 DK		04/17/1985	    Reduce compound shortening and short-word lengthening
 * 0008 DK 		04/23/1985	    Word-final fricatives longer
 * 0009 DK 		04/25/1985	    Final lengthing before preposition only at slow sprate
 * 0010 DK		05/15/1985	    Fix [nt] cluster reduction to happen only at word end
 * 0011 DK		05/17/1985	    Make word-init stressed vowels longer, final ptk shorter
 * 0012 DK		05/23/1985	    Word-initial vowels not quite so short, less vowel
 *           					lengthening induced by postvoc voiced fric
 * 0013 DK		06/20/1985      Fix nasal durs for "pense,pen,pend"
 * 0014 EAB		06/16/1990	    Allow speaking rate to 550 word per min. (from 350)
 * 0015 EAB		07/25/1990     	ADDED CHANGE TO ALLOW VARIABLE SETTING OF COMMA PAUSE
 *          					FOR NANCY JARRELL OF CHB TO GET IT TO ZERO. NOTE
 *          					-300 SETTING OF COMPAUSE ALLOWS SETTING TO ZERO BUT
 *          					THE CODE HAS NOT BEEN CHECKED FOR ERRORS.
 *
 *              DURATION RULES
 * 0016 EAB		05/03/1993      ADDED NEW PHONE DF TO DIFFERENTIATE T FROM D FLAP
 *                             	and added rules to make use of it.
 * 0017 EAB 	05/02/1993      restrucutred a bunch of stuff-reduced 
 *                              
 * 0018 EAB		05/02/1993      ADDED PETROCELLI'S NEW DURATION RULES.
 * 0019 MGS		03/25/1996      Merged win 95 code to 42c
 * 0020 MGS 	04/01/1996      Added MSDBG statements for debugging
 * 0021 MGS 	04/02/1996      made sure all local variable are initialized
 * 0022 MGS		06/06/1996	 	moved phtiming here.
 * 0023 SIK		07/12/1996  	Cleaning up and maintenance
 * 0024 GL		10/30/1996		merge the change from V43 code base.
 * 0025	GL		04/21/1997		BATS#360  remove spaces before "#define" or "#if" 
 * 0026	MGS		08/26/1997		Merged in fasttalk
 * 0027 EAB		09/08/1997		Added in changes to improve fastalk typing and SLOWSPEAK
 * 0028 EAB     10/12/1997		Removed Obsolete prphdurs and prdurs bats 495(performance)
 *								And improved typing_mode
 * 0029 EAB		04/4/1998		Found problem where stess was modifying aspiration as well as av because it was in
 *							    the wrong place. This had potential of causing other nasty problems. 
 * 0030 EAB		07/13/1998		Found redundant tcumdur code that was not needed. It's calculated
 *							    in phinton1/2 now.BATS 713 tcumdur addition removed
 * 0031 eab		07/22/1998		Modified duration rules to support all levels of reduction on a monosylable
 * 0032 EAB		08/17/1998 	    Refinfed and added some rules for ENGLISH DECTALK
 * 0033 EAB		09/11/1998 	    Refinfed and added some rules for ENGLISH DECTALK (ditto)
 * 0034 EAB     02/03/1999		Improved some rules that were compounded to too strong an effct in some place
								Changed vowcnt to sonocnt becuase we're now wounting sonorants
								did further tuning to improve stressed timed rythm
 * 0035 EAB     05/26/1999		BATS 894 Inter vocalic the are no longer flapped for better articualtion but
								the timing rule of American English still needs to fire.
 * 0036 EAB		07/09/1999		BATS 905 and 906 for NWS_NOAA
 * 0037 EAB     04/17/2000      Tuned some paramters for 4.6 release
 * 0037	MGS		04/13/2000		Changes for integrated phoneme set 
 * 0038 NAL		04/18/2000		Change for integrated phoneme set
 * 0064 CAB	    10/18/2000	    Changed copyright info
 * 0065 eab						Modified to support fduration modification by part of speech.
 * 0066 EAB 					Minor chnage to inmrpove behavior...
 * 0067 cab		03/16/2001		Update copyright info
 * 0068 EAB						bats 943 discrimation of p's d's etc.
 * 0069	CAB		05/02/2002		Updated copyright info
 */ 

#include "dectalkf.h"
#include "ph_def.h"

//#define DEBUGPHT
//#define FASTTALK
//extern __inline short phone_feature(PDPH_T pDph_t, int phone);	   /* Phonetic features            */
extern int inh_timing(LPTTS_HANDLE_T phTTS, int phone);
extern int min_timing(LPTTS_HANDLE_T phTTS, int phone);

//first inital thing to tune to see what needs to be captured.
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
void jp_phtiming(LPTTS_HANDLE_T phTTS)
{
	short                   psonsw = 0, posvoc = 0;
	PDPH_T                  pDph_t = phTTS->pPHThreadData;
	PKSD_T                  pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST           pDphsettar = pDph_t->pSTphsettar;
	
	short                   stcnt = 0;
#ifdef TOMBUCHLER
	short					cons_dur =0;
#endif
	short                   syldur = 0;
	short                   ncnt = 0;
	short                   endcnt = 0;
	short					sonocnt = 0;
	short                   adjust = 0;
	short                   emphasissw = FALSE;		/* Made local and initialized */
	short                   pholas = GEN_SIL;		/* Made local and initialized */
	short                   struclas = 0;			/* Made local and initialized */
	short                   fealas = GEN_SIL;		/* Made local and initialized */
	short                   prcnt = 0, durinh = 0, durmin = 0, deldur = 0, nphon = 0;
	short                   phocur = 0,phonex=0;
	int						feacur = 0,feanex=0, feasyllabiccur = 0;
	long                   struccur = 0,strucnex=0, strucboucur = 0, strucstresscur = 0;
	short                   dpause = 0;
	short					arg1,arg2;	/* arguments for the phmath routines. */
#ifdef NEWTYPING_MODE
	short					numbersonor;
#endif

#ifdef TYPING_MODE
	short					minsize;
#endif
	
	short tmp;
	/* Initialization  (Set sprat1, sprat2, zero counters, print debug) */

	init_timing (phTTS);

	pDphsettar->numstresses =0;
	pDph_t->tcumdur =0;/* 9/97EAB Since durations are done differently 
					   in typing mode calculation
					   of total dur must be moved to here also
						NOTE TO CARL THIS MAY HAVE ALREADY BEEN SUBMITTED BY DOUG*/
//#define MSDBG5
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

		if((struccur & FSTRESS) IS_PLUS)
		{
			pDphsettar->numstresses++;
		}	
		if (nphon < (pDph_t->nallotot - 1))
		{
			pDphsettar->phonex_timing = pDph_t->allophons[nphon + 1];
			pDphsettar->strucnex = pDph_t->allofeats[nphon + 1];
			pDphsettar->feanex = phone_feature( pDph_t ,pDphsettar->phonex_timing);
		}		
        if (nphon < (pDph_t->nallotot-1)) {
		phonex = pDph_t->allophons[nphon + 1];
		strucnex = pDph_t->allofeats[nphon + 1];
		feanex = phone_feature( pDph_t ,phonex);
	    }

		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
		/* Duration Rules                         						   */
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
		/* Use user-specified duration if one exists.         */
		/* User durations can be huge; call the conversion routine.   */
		if (pDph_t->user_durs[nphon] != 0)
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

		/* Convert inherent and minimum duration in msec to frames.*/
		/* Fixed overflow in 16 bits is not possible on these ones.*/
		
		durinh = ((inh_timing(phTTS,phocur) * 10) + 5) >> 6;
		durmin = ((min_timing(phTTS,phocur) * 10) + 5) >> 6;


            prcnt = 128;


/*  Rule 1: Long phones have nearly double duration */
	    if ((struccur & FLONG) IS_PLUS) {
		durinh += ((durinh*7) >> 3);		/* Seven eighths */
		durmin += ((durmin*7) >> 3);
		
	    }
	    if ((struccur & FPPNEXT) IS_PLUS) {
		deldur += NF20MS;

	    }

/*  Rule 2: Pause durations depend on syntax */
            if (phocur == GEN_SIL) {
/*	      Clause-initial pause should be minimal, i.e. NF64MS (enough
 *	      time for initial fricative to build up amp gradually) */
                dpause = NF64MS;
				pDphsettar->nrises_sofar = 0;
/*	      Treatment of other than clause-initial pauses: */
		if (nphon > 1) {

/*                If this clause ends in a comma, use short pause */
                    if ((struclas & FBOUNDARY) == FCBNEXT) {
/*                    Extra comma pause added if user command :dv */
                        dpause = pDph_t->nfcomma + pDph_t->compause;
                    }

/*                End of clause has long pause if ends with "." or "?" */
                    if ((struccur & (FPPNEXT | FQUENEXT)) IS_PLUS) {
                        dpause = pDph_t->nfperiod + pDph_t->perpause;
                    }
                }

/*	      Make sentence-initial pause long if this is a new paragraph */
		else if (pDph_t->newparagsw == 1)    dpause = pDph_t->nfperiod;

/*            Effect of speaking rate greatest on pauses */
                arg1 = dpause;
                arg2 = pDphsettar->sprat1;
                dpause = mlsh1(arg1,arg2);

/*            Minimum pause is NF64MS */
                if (dpause < NF64MS)    dpause = NF64MS;

/*            Skip over remaining duration rules if input is GEN_SIL */
                pDphsettar->durxx = dpause;
		durinh = pDphsettar->durxx;	/* for debugging print only */
		durmin = pDphsettar->durxx;
		
                goto break3;
            }

/*  Rule 3: Influence of a postvocalic consonant */
	    if ((feacur & FSYLL) IS_PLUS) {

	    //  Case 1: /*Following silence				*/
		if (phonex == GEN_SIL) {
		    arg1 = N120PRCNT;
		}
	   //   Case 2:consonat  Following syll is voiceless consonant		*/
		else 
			if ((feanex & FVOICD) IS_MINUS) {
		    arg1 = N70PRCNT;
		}
/*	      Case 3: Following nasal				*/
		else if ((feanex & FNASAL) IS_PLUS) {
		    arg1 = N70PRCNT;
		    if ((feanex & FSYLL) IS_PLUS) {
			arg1 = N110PRCNT;
		    }
		}
/*	      Case 4: Following voiced consonant or vowel	*/
		else {
		    arg1 = N80PRCNT;		/* Default for voiced C */
		    if (phonex == JP_WA) {
			arg1 = N70PRCNT;
		    }
		    else if ((feanex & FVOWEL) IS_PLUS) {
			arg1 = N90PRCNT;
			if ((feacur & FNASAL) IS_PLUS) {  /* Syllabic nasal */
			    deldur += NF30MS;	/* followed by Vowel, lengthen */
			}
		    }
		}
/*	      Now compute change to prcnt */
		if (arg1 != N100PRCNT) {
		    arg2 = prcnt;
		    prcnt = mlsh1(arg1,arg2);
		}
	    }

/*  Rule 4: Influence of a prevocalic consonant */
	    if ((feacur & FSYLL) IS_PLUS) {
		arg1 = N100PRCNT;

/*	      Case 1: Preceeding consonant is voiceless	*/
		if (((fealas & FVOICD) IS_MINUS) && (pholas != GEN_SIL)) {
		    arg1 = N70PRCNT;
		}
		arg2 = prcnt;
		prcnt = mlsh1(arg1,arg2);
	
	    }

/*  Rule 5: The first segment after a pause is short */
	    if (pholas == GEN_SIL) {
		arg1 = N90PRCNT;
		if ((feacur & FNASAL) IS_PLUS
			&& phonex != GEN_SIL) {
		    arg1 = N60PRCNT;
		}
		arg2 = prcnt;
		prcnt = mlsh1(arg1,arg2);
		
	    }

/*  Rule 6: Lengthening of segments in clause-final rime */
            if ((struccur & FBOUNDARY ) > FPPNEXT)
			{
/*	      Except for syllabic nasals */
		if (((feacur & FSYLL) IS_PLUS)
		  && ((feacur & FNASAL) IS_PLUS)) {
		    deldur -= NF40MS;
		}
		else
			deldur +=NF40MS;
		
            }

/*  Rule 7: Vowels longer if pitch gesture present */
/*	  Reset number of accent rises sofar in a phrase if new phrase */
    if ((struccur & FBOUNDARY ) > FPPNEXT) 

		{
		pDphsettar->nrises_sofar = 0;
	    }

/*	  Vowel of first accent rise, and of first fall of clause longer */
	if ((struccur & FRISE) IS_PLUS
		&&  ((feacur & FSYLL) IS_PLUS)	) 
	{
		if (pDphsettar->nrises_sofar == 0) 
		{
			deldur += NF25MS;
		}
		else deldur += NF7MS;
		
		pDphsettar->nrises_sofar++;
	}
	    else if ((struccur & FFALL) IS_PLUS) {
		if (pDphsettar->nrises_sofar <= 1) {
		    deldur += NF15MS;
		}
		else deldur += NF7MS;

	    }

/*  Rule 8: Zero duration for deleted /i,u/ */
	    if ((struccur & FDELET) IS_PLUS) 
		{
			//pDph_t->allofeats[nphon ] = pDph_t->allofeats[nphon] | FDUMMY_VOWEL;
		if ((pholas >= JP_P)
		 && ((fealas & FVOICD) IS_MINUS)) {
		    durmin = NF30MS;
		    durinh = NF30MS;	/* Time for aspir of [p,t,k,ts,ch] */
		}
		if (pholas >= JP_S)
		{
			durmin = NF40MS;
		    durinh = NF40MS;

		}

		else {
		    durmin = NF7MS;
		    durinh = NF7MS;
		}
		deldur = 0;
		prcnt = 0;
	
	    }
		



/*        Set duration from durinh, durmin, and percent */
            pDphsettar->durxx = (prcnt * (durinh - durmin)) DIV_BY128;
	    pDphsettar->durxx += durmin;	/* SHOULD BE DONE AFTER SPRATE ADJUSTMENT */



		/* Effect of speaking rate */
		if ((pDphsettar->sprat0 != 180) && (pDphsettar->durxx != 0))
		{
			arg1 = pDphsettar->durxx;
			arg2 = pDphsettar->sprat2;
//			if(pDph_t->number_words == 1)
//				arg2 += (pDphsettar->sprat2>>3);
			pDphsettar->durxx = mlsh1 (arg1, arg2) + 1;		/* Round upwards */
#ifdef MSDBG5
			FNX_PRINTF ("durxx = mlsh1(arg1,arg2)+1 durxx=%d\n", pDphsettar->durxx);
#endif

/* Effect of speaking rate on additive increment to dur */
			arg1 = deldur;
			arg2 = pDphsettar->sprat1;
			deldur = mlsh1 (arg1, arg2);
		}
		/* Add in rule-governed additive increment to dur  */
		pDphsettar->durxx = pDphsettar->durxx + deldur;
#ifdef MSDBG5
		FNX_PRINTF ("durxx = durxx + deldur durxx=%d\n", pDphsettar->durxx);
#endif
break3:
		if (pDphsettar->durxx < 0 ) /*eab oct 93 found dur could get set =0 compromise*/
			pDphsettar->durxx=1;    /*over putting command later(safer) see comment above*/


		pDph_t->allodurs[nphon] = pDphsettar->durxx;	   /* Save in array for phonetic comp */


#ifdef TYPING_MODE  /*-DR 09/24/1997 Added to FIX BATS465*/
		
	if(phTTS->bInTypingMode == TRUE)
	{
		minsize= 30/(pDph_t->nallotot-1);
		if (minsize < 6)
			minsize=6;

		if((feacur & FSON1) IS_PLUS && phocur != GEN_SIL) 
			pDph_t->allodurs[nphon]= minsize;
		
	}
#endif /* TYPING_MODE */

#ifdef MSDBG4
		FNX_PRINTF ("allodurs[nphon] = durxx allodurs[%d]=%d\n", nphon, pDph_t->allodurs[nphon]);
#endif
		pDph_t->longcumdur += (pDphsettar->durxx * NSAMP_FRAME);	/* Cum dur in waveform samples     */
	}	
}