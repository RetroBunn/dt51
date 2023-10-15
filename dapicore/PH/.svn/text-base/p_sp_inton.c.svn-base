/*C_HEADER_FILE****************************************************************
FILE			:	p_sp_inton.c
DESC			:	
TABS			:	4
OWNER			:	
DATE CREATED	:	

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
#include "dectalkf.h"
#include "ph_def.h"

#define BEFORE_HAT_RISE			0
#define ON_TOP_OF_HAT			1
#define AFTER_FINAL_FALL		2
#define AFTER_NONFINAL_FALL		3
#define DONTKNOW				0
#define QUESTCLAUSE				1
#define VERBPHRASE				2
#define PERIODCLAUSE			3

/* Duration of the "dummy vowel" inserted after a clause-final stop. */
#define DUMMY_V_DUR   NF15MS

#define phone_feature(a,b) (pDph_t->cur_speaker[(b)>>8]->featb[(b)&0x00FF])
#define begtyp(b) (pDph_t->cur_speaker[(b)>>8]->begtyp[(b)&0x00FF])


/***************************************************************************/
/* MVP : The following extern variables are now become elements of instance */
/* specific PH thread data structure DPH_T.                                */
/* extern short allophons[];    Integer rep of phonetic string             */
/* extern short allofeats[];    Structural features                        */
/* extern short allodurs[];     Duration in frames for each phone          */
/* extern short nallotot;       Number of phones in phonetic string        */
/* extern short arg1,arg2,arg3; Used for muldv(pDph_t->arg1,pDph_t->arg2,pDph_t->arg3) */
/* extern short *user_f0;       User-specified f0 commands, optional       */
/* extern short *user_offset;   User-specified f0 command time offset      */
/* extern FLAG  newparagsw;    Make f0 higher initially if =1              */
/* Set to 0 here after raising f0              							   */
/* extern short f0mode;        State variable determine if rules used      */
/* extern short cbsymbol;      Equals QUEST if clause ends in ?            */
/*   1/17/99 EAB Note cbcymbol is either 0 or the phonemic value of a ?    */
/*	so if(cbsymbol == Quest) and if(cbsymbol) are equivalent               */
/* extern short assertiveness; Speaker def parameter                       */
/* extern short size_hat_rise; Speaker def parameter                       */
/* extern short scale_str_rise;Speaker def parameter                       */
/* extern short f0tar[];       F0 target commands, in Hz*10                */
/* extern short f0tim[];       Times between commands, in frames           */
/* extern short nf0tot;        Number of commands for cur clause           */
/***************************************************************************/


	
void do_sp_non_phrase_final(LPTTS_HANDLE_T phTTS,short stress_target, short *cumdur, short nphon);
extern void make_f0_command(LPTTS_HANDLE_T phTTS,short type, const int rulenumber, 
                     short tar, short delay, short length, short *psCumdur, short nphon);


#define EMPH_FALL		  1				/* stress reduce shift for emph. stress 	*/
#define DELTAEMPH_SPEC  505				/* special value for fast emphatic str 	*/
#define DELTAEMPH		501				/* normal value for emphatic stress 		*/
#define DELTARISE		200				/* rise for continuing cadence */
#define DELTAFINAL		100				/* delta to remain at top in final cad. */
#define FINAL_FALL		  1				/* stress reduce shift for str. at top */


/*FUNCTION_HEADER**********************
 * NAME:	;sp_phinton
 * DESC: 	
 * IN:		phTTS - pointer to TTS global data
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void sp_phinton(LPTTS_HANDLE_T phTTS)
{
	PKSD_T	pKsd_t = phTTS->pKernelShareData;
	PDPH_T	pDph_t = phTTS->pPHThreadData;

	PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;

	short F0_CBOUND_PULSE;
	short SCHWA1;
	short SCHWA2;
	short F0_QGesture1;
	short F0_QGesture2;
	short F0_CGesture1;
	short F0_CGesture2;
	short GEST_SHIFT;
	short MAX_NRISES;
	short F0_FINAL_FALL;
	short F0_NON_FINAL_FALL;
	short F0_QSYLL_FALL;
	short *f0_mstress_level;
	short *f0_fstress_level;
	short *f0_mphrase_position;
	short *f0_fphrase_position;

	/* F0 rise as f(stress-level); Order is unstr, primary, secondary, emphasis */
	/*  WARNING eab f0_stress_level + f0_phrase_pos must add up to an odd number 
		or you will be creating a step function instead of the desired IMPULSE function */
											/* First clause    Second clause  */
	/* 300, 275, 250, 200, 175, 150, 50,50 last pos=0 causes bad problems */
	const short la_f0_mphrase_position[] = { 120, 120, 120, 120, 120, 80, 70, 60 };
	const short sp_f0_mphrase_position[] = { 120, 120, 120, 120, 120, 80, 70, 60 };

	/* 
	* F0 rise as f(stress-level); Order is
	*      FNOSTRESS       unstressed
	*      FSTRESS_1       primary stress
	*      FSTRESS_2       secondary stress
	*      FEMPHASIS       emphatic stress
	*/
	const short la_f0_mstress_level[] =	{ 0, 161, 61, 281};		/* 'stress `stress "stress  */
	const short sp_f0_mstress_level[] =	{ 0, 161, 61, 281 };

	/* 
	 * Stress-related rise/fall amount in Hz*10 for
	 * first, second, ... accent in a phrase
	 * Check against MAX_NRISES in phinton.c
	 */
	const short la_f0_fphrase_position[] = {200, 180, 160, 160, 150, 150, 140};
	const short sp_f0_fphrase_position[] = {200, 180, 160, 160, 150, 150, 140};

	/* 
	* F0 rise as f(stress-level); Order is
	*      FNOSTRESS       unstressed
	*      FSTRESS_1       primary stress
	*      FSTRESS_2       secondary stress
	*      FEMPHASIS       emphatic stress
	*/
	const short la_f0_fstress_level[] = {0, 160, 81, 251};		/* 'stress `stress "stress   */
	const short sp_f0_fstress_level[] =	{0, 160, 81, 251};


	/* Automatic variables */
	short nphon = 0, mf0 = 0;
	short gesture_ref=0;
	short length=0;
	short pholas = 0, struclas = 0, fealas = 0;
	U32  struccur = 0, feacur = 0;
	U32  stresscur = 0, wordfeat=0;
	short phonex = 0, strucnex = 0, feanex = 0;
	short targf0 = 0, delayf0 = 0;
	short f0fall = 0;		/* Extra fall below baseline at end of clause */
	short nphonx = 0;		/* short temp is never used MVP */
	short cumdur = 0, phocur = 0;		/* MVP : made local */
	short stepcount;
	short inputscrewup = 0;	/* MVP : was of type FLAG */
	short lowrisesw;	
	short nextsylbou =0 ,nextwrdbou =0 ,nextphrbou =0;
	short issubclause = 0;   /* TRUE signals subordinate clause */
	short NotQuest = 1;
	short n=0;

	pDph_t->delta_special=0;
	pDphsettar->nrises_sofar = 0;
	pDphsettar->hatsize = 0;
	pDphsettar->hat_loc_re_baseline = 0;

	/* Beginning of initialization */

	pDph_t->last_sonorant = 999;	
	inputscrewup = FALSE;
	cumdur = 0;
	stepcount=0;
	pDph_t->had_hatbegin=0;
	pDph_t->had_hatend=0;
	pDph_t->had_multiple=0;
	pDph_t->hatpos =0;
	pDph_t->nf0tot = 0;
	pholas = GEN_SIL;
	fealas = phone_feature( pDph_t,GEN_SIL);
	struclas = 0;
	mf0 = 0;
	pDph_t->prevtargf0 = -1; /* EAB 1/13/98 Want first target to end up plus
							 also initalize completion flag */
	pDph_t->done =0;

	if(pKsd_t->lang_curr == LANG_latin_american)
	{
		f0_mstress_level = (short *)la_f0_mstress_level;
		f0_fstress_level = (short *)la_f0_fstress_level;
		f0_mphrase_position = (short *)la_f0_mphrase_position;
		f0_fphrase_position = (short *)la_f0_fphrase_position;


		F0_CBOUND_PULSE = 700;
		SCHWA1 = LAP_IX;
		SCHWA2 = LAP_IX;
		F0_QGesture1 = -220;
		F0_QGesture2 = 350;
		F0_CGesture1 = -81;
		F0_CGesture2 = 171;
		GEST_SHIFT = 2; 
		MAX_NRISES = 6;
		F0_FINAL_FALL = 160;
		F0_NON_FINAL_FALL = 150;
		F0_QSYLL_FALL	 = 80;

	}
	else if(pKsd_t->lang_curr == LANG_spanish)
	{
		f0_mstress_level = (short *)sp_f0_mstress_level;
		f0_fstress_level = (short *)sp_f0_fstress_level;
		f0_mphrase_position = (short *)sp_f0_mphrase_position;
		f0_fphrase_position = (short *)sp_f0_fphrase_position;


		F0_CBOUND_PULSE = 700;
		SCHWA1 = SPP_IX;
		SCHWA2 = SPP_IX;
		F0_QGesture1 = -220;
		F0_QGesture2 = 350;
		F0_CGesture1 = -81;
		F0_CGesture2 = 171;
		GEST_SHIFT = 2; 
		MAX_NRISES = 6;
		F0_FINAL_FALL = 160;
		F0_NON_FINAL_FALL = 150;
		F0_QSYLL_FALL	 = 80;

	}
	else
	{
		return;
	}

	/* Should set nrises_sofar to zero after a ph_init=0 hard reset */
	/* End of initialization */


	/* MAIN LOOP, for each output phoneme */
	for (nphon = 0; nphon < pDph_t->nallotot; nphon++)
	{
		if (nphon > 0)
		{
			pholas = pDph_t->allophons[nphon - 1];
			struclas = pDph_t->allofeats[nphon - 1];
			fealas = phone_feature(pDph_t,pholas);
		}

		phocur = pDph_t->allophons[nphon];
		struccur = pDph_t->allofeats[nphon];


		if(struccur & WORDFEAT) /*EAB This weird code allows for wordfeat to be updaed only when new information arrives
								This is test code and in reality it needs to be cleared at a word boundary
								The above code is not syncronizing ok*/
		{
			wordfeat = struccur & WORDFEAT;
			if(wordfeat & F_NOUN)
			{
				wordfeat = 25;
			}
			else if(wordfeat & F_VERB)
			{
				wordfeat = 20;

			}
			else if(wordfeat & F_ADJ)
			{
				wordfeat = 35;
			}
		}
		else
			wordfeat=0;

		stresscur = struccur & FSTRESS;
		feacur = phone_feature( pDph_t,phocur);
		if (nphon < (pDph_t->nallotot - 1))
		{
			phonex = pDph_t->allophons[nphon + 1];
			strucnex = pDph_t->allofeats[nphon + 1];
			feanex = phone_feature( pDph_t,phonex);
		}


		pDph_t->hatstatel = pDph_t->hatstate;	/* Remember previous state */
		if (phocur == GEN_SIL) {
			pDph_t->hatstate = BEFORE_HAT_RISE;
		}
		//numwowels not used yet so removed BATS 711
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		//#ifndef GERMAN /* 02_10_01 RSM */
		/* These rules often want to know the type of boundary after the
		*  current syllable, and the type of boundary after the current
		*  word, and the type of boundary after the current phrase/clause.
		*/

		/*	  Step 1, skip over word-initial consonants of this syllable */
		nphonx = nphon;
		while ((pDph_t->allofeats[nphonx] & FWINITC) IS_PLUS) {
			nphonx++;
		}
		/*	  Step 2, Look up boundary immediately after current syll */
		nextsylbou = pDph_t->allofeats[nphonx] & FBOUNDARY;
		/*	  Step 3, Try to make direct assignment of boundary after current word */
		if (nextsylbou >= FWBNEXT) {
			nextwrdbou = nextsylbou;
		}
		/*	  Step 4, Look ahead if this is not a word-final syllable */
		else {
			for (nphonx=nphonx+1;nphonx<pDph_t->nallotot; nphonx++) {
				if ((nextwrdbou=pDph_t->allofeats[nphonx]&FBOUNDARY)>=FWBNEXT) {
					goto wbfound;
				}
			}
		}
wbfound:
		/*	  Step 5, Try to make direct assignment of boundary after curr phrase */
		if (nextsylbou >= FCBNEXT) 
		{	/* RSM To not count spurious FPPNEXT, FVPNEXT, and FRELNEXT */
			nextphrbou = nextwrdbou;
		}
		/*	  Step 6, Look ahead if this is not a phrase-final syllable */
		else 
		{
			for (nphonx=nphonx+1;nphonx<pDph_t->nallotot; nphonx++) 
			{
				if ((nextphrbou=pDph_t->allofeats[nphonx]&FBOUNDARY)>FRELNEXT) 
				{	
					goto fbfound;
				}
			}
		}

fbfound:
		/* 
		* printf("phocur %d feacur %d struccur %d feanex %d phonex %d strucnex %d\n",
		* phocur,feacur,struccur,feanex,phonex,strucnex);  
		*/

		/* Rule 0: User-specified commands for phoneme f0 targets or singing */

		if( pDph_t->f0mode == PHONE_TARGETS_SPECIFIED || 
			pDph_t->f0mode == SINGING )
		{
			if (pDph_t->user_f0[nphon] != 0)
			{
				make_f0_command ( phTTS, USER,0, (short)(1000 + pDph_t->user_f0[nphon]), 0, 0, &cumdur,nphon); // NAL warning removal
			}
			goto skiprules;
		}

		/* Rule 1: If at bottom of hat, goto top on +HAT_RISE +syllabic */

		/* EAB 4/9/97 Found a basic flaw whose error cause was generated a long time ago
		manual placed f0hat get ignores if the next thing isn't plus syllabic.Looking at
		the code it's hard to believe it ever worked all correctly. Looking at the tuning example I can
		not figure out how it could have ever wroked correctly. The first hat rise in the example 
		would have been seen but only becuase the next word started with a vowel.What it should do is
		remember that it has a hat_rise or hat_fall pending. and execute it at the next syllabic*/
		/* eab 9/7/97 If were in a real short phrase don;t doit*/
		/* eab 7/8/98 Begin to remove hat rise hat fall pattern. 
		EAB 1/25/98 Since evreyone is so used to the sound of it I think we need to keep hat_rise_fall*/

		if((struccur & FHAT_BEGINS) IS_PLUS  )
			pDph_t->had_hatbegin= 1;

		if((struccur & FHAT_ENDS) IS_PLUS )
			pDph_t->had_hatend= 1;

		if( pDph_t->f0mode == NORMAL || 
			pDph_t->f0mode == HAT_F0_SIZES_SPECIFIED )
		{
			if ((feacur & FSYLL) IS_PLUS)
			{
				if( pDph_t->hatpos != AT_TOP_OF_HAT )
				{
					/* eab 4/9/97 BATS#346  use had_hatbegin instead of FHAT_BEGINS*/
					if ((pDph_t->had_hatbegin
						|| nphon >= 5 ) && pDphsettar->nrises_sofar ==0)
					{
						if (pDph_t->f0mode == NORMAL && !pDph_t->special_phrase)
						{
							pDph_t->had_hatbegin=0;
							if(pDph_t->had_hatend == 1)
								//both at once reduce jesture
								pDphsettar->hatsize = pDph_t->size_hat_rise-(pDph_t->size_hat_rise>>2);
							else
								pDphsettar->hatsize = pDph_t->size_hat_rise;	/* speaker-def param */

							if(nphon >= 5 && pDphsettar->nrises_sofar ==0)
							{
								pDphsettar->nrises_sofar++;
								pDphsettar->hatsize = pDph_t->size_hat_rise>>1;
							}

							if(pDph_t->clausetype == QUESTION)
								pDphsettar->hatsize = 100;

							/* 
							* PUT IN CODE TO REDUCE HATSIZE IN SHORTER OF 
							* TWO HAT PATTERNS OF A SENTENCE 
							*/
							if(pDph_t->had_multiple)
							{
								pDphsettar->hatsize = pDphsettar->hatsize-40;
								delayf0 = pDph_t->allodurs[nphon];
							}
							else
								delayf0=0;

							/* Begin gesture earlier if also hat fall on same vowel */
							if ((struccur & FHAT_ENDS) IS_PLUS)
							{
								delayf0 = -NF80MS;
							}


							//if first syllable voiced stressed
							make_f0_command( phTTS,STEP, 1, pDphsettar->hatsize, delayf0,15, &cumdur, nphon);
							//if primary stressed item much later in the sentence 
							//make_f0_command( phTTS,GLIDE, 1, 80/*pDphsettar->hatsize*/, -2/*delayf0*/,10, &cumdur, nphon);
							//( phTTS,GLIDE, 1, 320/*pDphsettar->hatsize*/, -2/*delayf0*/,10, &cumdur, nphon);
						}
						else if (pDph_t->f0mode == HAT_F0_SIZES_SPECIFIED)
						{
							pDphsettar->hatsize = ((pDph_t->user_f0[mf0] - 200) * 10) + 2;
							if ((pDphsettar->hatsize >= 2000) || (pDphsettar->hatsize <= 0)
								|| (inputscrewup == TRUE))
							{
								/* this is abort code for a goof*/
								pDphsettar->hatsize = 2;	/* Must be even, greater than 0 */

							}
							delayf0 = mstofr (pDph_t->user_offset[mf0]);
							mf0++;

							/* Make hat rise occur at user_dur ms re vowel onset */
							make_f0_command( phTTS,STEP, 1, (short)(pDphsettar->hatsize),
								delayf0, 15, &cumdur, nphon); // NAL warning removal
						}

						pDphsettar->hat_loc_re_baseline += pDphsettar->hatsize;
						pDph_t->hatpos = AT_TOP_OF_HAT;
						pDph_t->hatstate = ON_TOP_OF_HAT;
					}
				}

				if (pDph_t->special_phrase)
				{
					pDphsettar->nrises_sofar = 5;
				}

				if (issubclause)
				{
					pDphsettar->nrises_sofar = 3;
					issubclause = FALSE;
				}


				/* Rule 2: Add stress pulse to every stressed vowel, smaller pulse at end */

				targf0=0;
				if ( pDph_t->had_hatend 
					&& pDph_t->clausetype == QUESTION)
				{
					pDph_t->had_hatend=0;
					//spanish question which wants pitch rise from last
					//STRESSED vowel
					goto squest;
				}

				if (!pDph_t->special_phrase && ((stresscur & FSTRESS) IS_PLUS  )
					&& (struccur & FBOUNDARY) != FQUENEXT)
				{			/* Primary or emph */
					/* Make stress IMPULSE prop. to degree of stress */
					/* and stress position relative to clause onset */

					/* Increment stressed syllable counter */
					if(nphon >= 5
						&& pDphsettar->nrises_sofar ==0)
						//if we into a sentence a ways and
						//we still haven't had a stess reduce the first stress level
						pDphsettar->nrises_sofar++;	
					if (pDph_t->malfem == MALE)
						targf0 = f0_mstress_level[stresscur];
					else
						targf0 = f0_fstress_level[stresscur];


					if(stresscur == 3)
						//don't reduce pukse
					{
						if (pDph_t->malfem == MALE)
							targf0 += f0_mphrase_position[0];
						else
							targf0 += f0_fphrase_position[0];
					}
					else
						if (pDph_t->malfem == MALE)
							targf0 += f0_mphrase_position[pDphsettar->nrises_sofar];
						else
							targf0 += f0_fphrase_position[pDphsettar->nrises_sofar];

					//	if( pDph_t->number_words == 1 )
					//		targf0 = targf0 - (targf0>>1);

					//EAB Phrase final stressed syllable don't wack
					//it so hard unless emphatic-but this doesn't work correctly but
					// it's too dangerous to fix right before a release the finalsyl
					// is not marked as final in a single syl word the phrbound is 
					// a look ahead so that doesn't work num_words to versus word num is the right sol I think

					if (pDph_t->cbsymbol )
					{
						targf0 >>= 1;	/* All gestures reduced in ? */
					}

					/* eab 2/21/97 EAB remove emphasisflag and associated stuff pulled see note in phsort.c */

					/* Begin gesture 1/4 of way into the vowel */

					do_sp_non_phrase_final( phTTS,targf0, &cumdur, nphon );

					pDphsettar->nrises_sofar++;
					if (pDphsettar->nrises_sofar < MAX_NRISES)
						pDphsettar->nrises_sofar++;
					if (pDphsettar->nrises_sofar == MAX_NRISES)
						pDphsettar->nrises_sofar=1;

				}
				/* EAB 2/27/97 Fhat_fall on last stressed syl is not always appropriate because there aare times when there
				is still too many phonemes left to go to end of clause and we need to delay the fall. Need to check it in two places
				FSYL test which is not needed because we must assume the fhat was put in the coreect place to begin with, but the 
				duplication is so that the rules fire in the correct order also*/

				/* Rule 3: Execute hat fall */

				/* If presently at top of hat, return to base shortly after */
				/* vowel onset if this is last stressed syllable in phrase */
				if ( pDph_t->had_hatend )

				{
					pDph_t->had_hatend=0;
					pDph_t->had_multiple =1;
					pDph_t->hatpos = 0;		
					if (pDph_t->f0mode == NORMAL)
					{
						/* EAB The code is badly broken we didn't know it because limit code in PHDRwt0
						was preventing it from jumping off the cliff it's being totally re-written
						It's too broken to try and comment on why I cahnged what I'm simply trying 
						to make it work the way it was intended to  Note f0 is a delta value rlative to a hopeful
						return to baseline offset by f0delta In further investigation it was really
						not so awfule but values were */

						/* Default assumptions: */
						/* Make fall try to go below baseline by 21 Hz in a 
						declarative sentence with stressed final syllable */
						f0fall = F0_FINAL_FALL;
						pDph_t->hatstate = AFTER_FINAL_FALL;
						/* Make fall start 160 ms from end of this vowel */
						delayf0 = pDph_t->allodurs[nphon] - NF160MS;
						//unless it's the last thing then earlier
						if(nphon == pDph_t->nallotot -2)
							delayf0 -= NF60MS;
						if(delayf0 < 0)
							delayf0 = 0;
						if(stresscur == 3)
							delayf0 += 6;

						if (((struccur & FBOUNDARY) == FCBNEXT ) || pDph_t->clausetype == COMMACLAUSE )
						{
							f0fall = F0_NON_FINAL_FALL;

							pDph_t->hatstate = AFTER_NONFINAL_FALL;
						}
						/* Non-final phrase, don't go below baseline at all */
						//	if ((struccur & FBOUNDARY) <= FVPNEXT)
						//	{
						//		pDph_t->hatstate = AFTER_NONFINAL_FALL;
						//		f0fall = 0;
						//	}
						else
						{

							/*	Delay fall if more sonorants after nucleus */
							//don't delay it if not a final fall
							if (nphon <= pDph_t->nallotot -4)
							{
								delayf0 += pDph_t->allodurs[nphon+1]>>1;
							}
						}

						/* Or because question rise on same syllable */
						if ((struccur & FBOUNDARY) == FQUENEXT)
						{
							f0fall = F0_QSYLL_FALL;
						}



						if (pDph_t->hatstate == AFTER_FINAL_FALL) {
							lowrisesw = 0;
						}


						/* Pitch falls are less pronounced for some speakers 
						* to reduce impression of assertive personality */
						f0fall = frac4mul (f0fall, pDph_t->assertiveness);

						if (pDph_t->cbsymbol)
						{
							f0fall = f0fall >> 1;	/* Gest reduced in ? */
						}

						/* Total fall is hatsize + f0fall below baseline */

						//f0fall += (pDphsettar->hatsize-(pDphsettar->hatsize>>2));
						f0fall += pDphsettar->hatsize;
					}


					/* Unless user->specified fall */
					else if (pDph_t->f0mode == HAT_F0_SIZES_SPECIFIED )
					{
						f0fall = ((pDph_t->user_f0[mf0] - 400) * 10) + 2;	/* Even */
						if ((f0fall >= 2000) || (f0fall <= 0)
							|| (inputscrewup == TRUE))
						{
							f0fall = 2;		
							/* Must be even greater than 0 */
						}

						delayf0 = mstofr(pDph_t->user_offset[mf0]);
						mf0++;
					}

					length = 25;

					make_f0_command( phTTS, GLIDE, 3, (short)-f0fall, delayf0, length, &cumdur, nphon); // NAL warning removal

					pDphsettar->hat_loc_re_baseline -= f0fall;
				}

				/* 
				* Rule 4: Add positive pulse to approximate nonterminal fall-rise          
				* in stressed clause-final but non-sentence-final syllable, 
				* or in sentence ending in a question mark 
				*/
				delayf0 = -5;
				if ((struccur & FBOUNDARY) == FQUENEXT)
					NotQuest = 0;	   /* it is a question allow early stress */

				if ((struccur & FBOUNDARY) == (FPERNEXT | FEXCLNEXT | FSENTENDS))
				{
					NotQuest = 1;
				}

				if( (struccur & FBOUNDARY) == FQUENEXT || 
					(struccur & FBOUNDARY) == FCBNEXT )
				{
squest:					
					length = pDph_t->allodurs[nphon];
					if( nphon < pDph_t->nallotot-2 && 
						phone_feature( pDph_t,pDph_t->allophons[nphon+1]) & FSON1)
					{
						length +=pDph_t->allodurs[nphon+1];
					}

					if( (struccur & FBOUNDARY) == FQUENEXT ||
						pDph_t->clausetype == QUESTION )
					{
						/* Sent.-final stressed vowel followed by q-mark */

						/* EAB We want the hardcoded gestures to be defined in a language specific 
						or speaker specific way file they ultimately want to be setable perhaps so for now I'm going
						to move all of these kinds of things to the speaker def files. 2/26/97 */

						pDph_t->delta_special = 0; 

						make_f0_command( phTTS, GLIDE, 341, F0_QGesture2, delayf0, length, &cumdur, nphon);
						
					}
					else if((struccur & FBOUNDARY) == FCBNEXT)
					{
						/* Phrase-final stressed vowel followed by comma */
						
						pDph_t->delta_special = -50;
						
						delayf0 -= NF40MS;

						if((pKsd_t->modeflag & MODE_READING)==1)
						{
							make_f0_command ( phTTS, IMPULSE,420,  F0_CGesture1, delayf0,24, &cumdur, nphon);
							make_f0_command ( phTTS, IMPULSE, 420, (F0_CGesture2>>1), (short)(pDph_t->allodurs[nphon]>>1),24, &cumdur, nphon); // NAL warning removal
						}
						else
						{
							make_f0_command ( phTTS, IMPULSE,420,  F0_CGesture1, delayf0,24, &cumdur, nphon);
							make_f0_command ( phTTS, IMPULSE, 420, F0_CGesture2, (short)(pDph_t->allodurs[nphon]>>1),24, &cumdur, nphon); // NAL warning removal
						}
					}	
				}
			}


			/* 
			* Rule 5: Final fall on unstress clause-final syl, or on stressed 
			* clause - final syll that didn't have hat fall due to earlier emphasis 
			*/
			if ((feacur & FSYLL) IS_PLUS)
			{
				if(((stresscur & FSTRESS_1) IS_MINUS) &&
					((struccur & FHAT_ENDS) IS_MINUS))
				{					   /* or 1-str nofall */
					/* Pitch falls (glottalize) at end of declar. sent. */
					if (((struccur & FBOUNDARY) == FPERNEXT)
						|| ((struccur & FBOUNDARY) == FEXCLNEXT))
					{
						targf0 = 93;
						/* 
						* Pitch falls are less pronounced for some speakers 
						* to reduce impression of assertive personality 
						*/
						targf0 = frac4mul (targf0, pDph_t->assertiveness);

						targf0 |= 01;  /* Must be odd */

						pDph_t->test_targf0 = targf0;	/* RSM created this variable to reduce final fall in GERMAN */
						pDph_t->impulse_width = 16;		/* RSM */

						/* Sent.-final unstressed vowel followed by a period */
						/* EAB with addition of new code to glotalize in phdrwt0 this
						needs to grt alot weaker*/
						if(pDph_t->number_words == 1)
						{
							make_f0_command ( phTTS,GLOTTAL, 5, (short)(targf0>>1), (short)(pDph_t->allodurs[nphon] - NF30MS), 30, &cumdur, nphon); // NAL warning removal
						}
						else
						{
							/*	EAB 11/4/98 Final glotalization gesture is very sensitive to timing and needs to be adjusted in onset if
							the phoneme following the syllable nucleus is voiced BATS 796. */
							if(phone_feature( pDph_t,phonex) & FVOICD)
							{
								pDph_t->test_targf0 = targf0>>3;
								if(nphon+2 <= pDph_t->nallotot && (phone_feature( pDph_t,pDph_t->allophons[nphon+2]) & FVOICD))
									/* nucleus has two voiced phonemes following it so delay even more*/
								{
									make_f0_command ( phTTS,IMPULSE, 5, pDph_t->test_targf0,  (pDph_t->allodurs[nphon]), pDph_t->impulse_width, &cumdur, nphon);
								}
								else
								{
									delayf0 = (pDph_t->allodurs[nphon]>>1) + (pDph_t->allodurs[nphon]>>2);
									make_f0_command ( phTTS,IMPULSE, 5, pDph_t->test_targf0,  delayf0, pDph_t->impulse_width, &cumdur, nphon);
								}

							}
							else
							{
								make_f0_command ( phTTS,IMPULSE, 5, pDph_t->test_targf0, (short)(pDph_t->allodurs[nphon]>>1), pDph_t->impulse_width, &cumdur, nphon); // NAL warning removal
							}
						}
					}
				}
			}


			/* Rule 7: Reset baseline at end of sentence */

			if (phocur == GEN_SIL)
			{
				stepcount=0;
				/* Reset f0 to hat bottom from sub-hat-bottom */
				if ((pDphsettar->hat_loc_re_baseline != 0) && (pDph_t->nf0tot > 0))
				{
					pDphsettar->hat_loc_re_baseline = 0;
				}

				if (nphon > 0)
					pDphsettar->nrises_sofar = 1;	/* Soft reset */

				pDph_t->hatpos=AT_BOTTOM_OF_HAT;

				{
					if ((pDph_t->allofeats[nphon - 1] & FBOUNDARY) == FCBNEXT
						&& pDph_t->nf0tot > 0
						&& (pDph_t->allophons[nphon - 1] != GEN_SIL))
					{
						make_f0_command(phTTS, F0_RESET, 7, 0, 0, 0, &cumdur, nphon); /* RESET! */
						issubclause = TRUE;
					}
				}
			}

			/* Rule 8: Reset baseline and hat position to brim if end of a sentence */
			/*** Add condition to reset if long clause followed by comma and long clause */


skiprules:					   /* END OF F0 RULES */

			/* Update cumdur to time at end of current phone */
			cumdur += pDph_t->allodurs[nphon];
			/* add up duration for phdrawt0	eab 8/96 don't count final silence 
			eab 7/8/98 Bats 711*/
			if( (nphon <= (pDph_t->nallotot-1) &&
				(nphon > 0 && (pDph_t->allophons[nphon] & PVALUE)!= 0))
				|| nphon==0 ) //1st two lines check end of cluase
				//This counts inital silence (we don't vount final silence 
				/* EAB It turns out that there are two possibilites for the way things
				get transmitted one is with and end of clause symbols and the other is without(implied)
				therefore you have to do two checks to know whether or not your at the last real phoneme
				or at a silence phoneme BATS 897 */
				pDph_t->tcumdur += pDph_t->allodurs[nphon];




			/* Rule 9: Add short schwa vowel to create release of [p,t,k,b,d,g] into sil. 
			* Logically, this kind of rule should appear in PHALLOPH.C, but
			* delaying it to here makes all dur and f0 rules much simpler 
			* EAB 2/28/97 changing to generalize when FPLOS + Fburst then release 
			*/

		}
	}
}


/*FUNCTION_HEADER**********************
 * NAME:	;sp_do_phrase_final
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void sp_do_phrase_final(LPTTS_HANDLE_T phTTS, short *cumdur, short nphon)
{
	short f0fall,delayf0,length;
	PKSD_T pKsd_t = phTTS->pKernelShareData;
	PDPH_T pDph_t = phTTS->pPHThreadData;
	PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;

	pDph_t->had_hatend=0;
	pDph_t->had_multiple =1;
	pDph_t->hatpos = 0;		
	if (pDph_t->f0mode == NORMAL)
	{
		/* EAB The code is badly broken we didn't know it because limit code in PHDRwt0
		was preventing it from jumping off the cliff it's being totally re-written
		It's too broken to try and comment on why I cahnged what I'm simply trying 
		to make it work the way it was intended to  Note f0 is a delta value rlative to a hopeful
		return to baseline offset by f0delta In further investigation it was really
		not so awfule but values were */

		/* Default assumptions: */
		/* Make fall try to go below baseline by 21 Hz in a 
		declarative sentence with stressed final syllable */
		f0fall = 180;
		pDph_t->hatstate = AFTER_FINAL_FALL;
		/* Make fall start 160 ms from end of this vowel */
		delayf0 = pDph_t->allodurs[nphon] - NF160MS;
		//unless it's the last thing then earlier
		if(nphon == pDph_t->nallotot -2)
			delayf0 -= NF60MS;
		if(delayf0 < 0)
			delayf0 = 0;
		pDph_t->last_sonorant = 1; //default cASE

		if( ((pDph_t->allofeats[nphon] & FBOUNDARY) == FCBNEXT ) || 
			pDph_t->clausetype == COMMACLAUSE )
		{
			f0fall = 150;

			pDph_t->hatstate = AFTER_NONFINAL_FALL;
		}
		else
		{
			/*	Delay fall if more sonorants after nucleus */
			//don't delay it if not a final fall
			if (nphon <= pDph_t->nallotot -4)
			{
				delayf0 += pDph_t->allodurs[nphon+1]>>1;
			}
		}

		/* Or because question rise on same syllable */
		if (( pDph_t->allofeats[nphon]& FBOUNDARY) == FQUENEXT)
		{
			f0fall = 80;
		}


		/* Pitch falls are less pronounced for some speakers 
		* to reduce impression of assertive personality */
		f0fall = frac4mul (f0fall, pDph_t->assertiveness);

		if (pDph_t->cbsymbol)
		{
			f0fall = f0fall >> 1;	/* Gest reduced in ? */
		}

		/* Total fall is hatsize + f0fall below baseline */

		//f0fall += (pDphsettar->hatsize-(pDphsettar->hatsize>>2));
		f0fall += pDphsettar->hatsize;
	}

	length = 25;
	if(pDph_t->clausetype == QUESTION )
	{
		delayf0 = -5;
		f0fall = -350; //question rise
		length = pDph_t->allodurs[nphon] +  pDph_t->allodurs[nphon+1];
		make_f0_command( phTTS, GLIDE, 3, (short)-f0fall, delayf0, length, cumdur, nphon);
	}
	else
		make_f0_command( phTTS, GLIDE, 3, (short)-f0fall, delayf0, length, cumdur, nphon);

	pDphsettar->hat_loc_re_baseline -= f0fall;

}

/*FUNCTION_HEADER**********************
 * NAME:	;do_sp_non_phrase_final
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void do_sp_non_phrase_final(LPTTS_HANDLE_T phTTS,short stress_target, short *cumdur, short nphon)
{
	short  delayf0,length,last_sonorant;
	PKSD_T pKsd_t = phTTS->pKernelShareData;
	PDPH_T pDph_t = phTTS->pPHThreadData;
	PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;


	last_sonorant = 1; //default cASEA
	length = pDph_t->allodurs[nphon];	

	delayf0 = -3;
	//and set length to last_sonorant_ a "flat time" of say 7 frames

	if( length <= 1)
		length = 1;

	if ((pDph_t->allofeats[nphon] & FHAT_ENDS) IS_MINUS
		|| ((phone_feature( pDph_t, pDph_t->allophons[nphon+1])) & FVOWEL )
		|| ((phone_feature( pDph_t, pDph_t->allophons[nphon-1])) & FVOWEL ))
	{
		//check for fson1 before vowel
		if(phone_feature( pDph_t,pDph_t->allophons[nphon-1 ]) & FSON1
			&& (!(phone_feature( pDph_t,pDph_t->allophons[nphon-1]) & FSTOP)
			|| phone_feature( pDph_t,pDph_t->allophons[nphon-1]) & FNASAL ))
		{
			delayf0 = -pDph_t->allodurs[nphon-1];
			length += pDph_t->allodurs[nphon];
		}
		if(!(phone_feature( pDph_t,pDph_t->allophons[nphon+1]) & FSYLL))
			length += pDph_t->allodurs[nphon+1]-7;

		if( pDph_t->clausetype == QUESTION && 
			nphon >= pDph_t->nallotot-5)
			return;

		//stress_target += length;
		if(pDph_t->had_hatend == 1)
		{
			length = pDph_t->allodurs[nphon]>>2;
			make_f0_command( phTTS, GLIDE, 223, (short)stress_target, 0, length, cumdur, nphon);			
			make_f0_command( phTTS, GLIDE, 224, (short)-stress_target, length, 14, cumdur, nphon);

		}
		else
		{
			make_f0_command( phTTS, GLIDE, 221, (short)stress_target, delayf0, length, cumdur, nphon);			
			make_f0_command( phTTS, GLIDE, 222, (short)-stress_target, length, 12, cumdur, nphon);
		}
	}
	else
	{
		if(pDph_t->clausetype == QUESTION
			&& nphon <= pDph_t->nallotot -4)
			return;

		make_f0_command( phTTS, GLIDE, 2221, (short)stress_target, delayf0, length , cumdur, nphon);			
		make_f0_command( phTTS, GLIDE, 2222, (short)-stress_target, length, 7, cumdur, nphon);

	}
}	// do_sp_non_phrase_final
