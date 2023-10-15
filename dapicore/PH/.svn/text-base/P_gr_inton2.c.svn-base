/* ww_02_27_01
 ***********************************************************************
 *
 *                           Copyright ©
 *    Copyright © 2002 Fonix Corporation. All rights reserved.
 *    Copyright © 2000-2001 Force Computers, Inc., a Solectron company. All rights reserved.
 *    © SMART Modular Technologies 1999, 2000. All rights reserved.
 *    © Digital Equipment Corporation 1996, 1997, 1998, 1999 All rights reserved.
 *   
 *     U.S. Government Rights: Consistent with FAR 12.211 and 12.212, 
 *     Commercial Computer Software, Computer Software Documentation, 
 *     and Technical Data for Commercial Items are licensed to the U.S. 
 *     Government under vendor's standard commercial license.
 *
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Fonix Corporation and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Fonix or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:    ph_inton.c
 *    Author:
 *    Creation Date:
 *
 *    Functionality:
 *    FUNDAMENTAL FREQUENCY RULES
 *
 ***********************************************************************
 *    Revision History:
 * Rev  Who     Date            Description
 * ---  -----   -----------     -------------------------------------------- 
 * 0001 DK 		12/16/1984		Initial creation
 * 0002 DGC		12/27/1984		Version for 80186, use mstofr()
 * 0003 DK		01/09/1985		Fix handling of user inputted f0 commands
 * 0004 DK		01/21/1985		Fix bug causing f0 to drift down in long sentences
 * 0005 DK		03/01/1985		Reduce pitch gestures in a clause ended by "?"
 * 0006 DK		04/18/1985		Try releasing final nasals into silence for intellig.
 * 0007 DK		04/25/1985		Fix continuation rise so not too early
 * 0008 DK		05/17/1985		F0 fall cannot occur too early in a long vowel
 * 0009 DK		06/14/1985		Fix f0 fall for f0mode=HAT_LOCATIONS_SPECIFIED
 * 0010 DK		06/19/1985		Fix insertion of dummy-vowel phoneme
 * 0011 MGS		03/25/1996		Merged WIN 95 code to 42c 
 * 0012 MGS		04/01/1996		Added MSDBG blocks
 * 0013 MGS		06/04/1996		Merged Spanish with English 
 * 0014	MGS		06/06/1996		Changed file name from phinton.c ph_inton.c
 * 0015 EDB		01/10/1997		Fix many data.
 * 0016 EAB		02/22/1997		Copied rule 3 was checked to make it work with new doitlater code in ph_aloph
 *								It has to be in twice so that the rules fire in the proper order i.e. otherwise
 *								rule 4 will fire before rule three in a normal ordering. Time eprmitting later
 *								thus may be able to be simplified.
 * 0017 EAB		04/09/1997		Fixed hat_rise fall phonemic markings see note below
 *								Fixes BAT 346
 * 0018 EAB		04/18/1997		Completed merge with 5.0 and French plus fixed a problem where somehow and extra line of code
 *								erroneuosly snuck in.
 * 0019 EAB		05/15/1997		Found that hat_rise hat_fall still didn't work and traced problem back to rewrite in1984
 *								I also removed uneeded restriction that a hat_rise couldn't operate if someone had already
 *								put in a hat rise. Let people do whatever they want aldo this removed the variable hatpos
 *								The code now assigns the hat rise or fall to the next phoneme that is FSYLL perhaps later
 *								we might want to open it up to FSONOR. Also night want to defferiate final fall effects from
 *								final hat fall and not have it automatic.
 *
 * 0020 KSB		05/20/1997		Moved f0 and place to gl_phones
 * 0021 EAB		06/02/1997		Fixed redundant line of code (looks like editing mistake) no no note at delete
 * 0022 EAB		09/08/1997		EAB Don't you DARE try to diff this with a previous version major surgery
 *								and this is only the beginning also this re-write removed the need for even odd 
 *								enforcement on commands so I removed the unnecessary code
 * 0023 EAB		12/12/1997		Modify code for UK_English
 * 0024 EAB		01/10/1997		Added length parameter to Make_f0_command glide will be the first command to use this.
 * 0025 EAB		01/22/1998		Modified UK English intonation rules per Caroline
 * 0026 EAB		01/22/1998		Put in a bit of a kludge so that last syllable gesture
 *								(rule 23) occurs on the last syllable as desired for UK English
 *								and not on last STRESSED syllable as in American English bats 575
 * 0027 EAB		02/10/1998		Submitted wrong version with a bug causing last gesture to be incorrect BATS 600
 * 0028 EAB		02/16/1998		Re-wrinting for 4.5+ go get all on the same base 
 * 0029 EAB		03/02/1998		Added length to IMPULSE commands to support new command syntax ( note step by definition
 *								have a length of zero-we could change it to be a ramp
 * 0030	gl		03/25/1998		Added DBGV command for PH debug variable passing
 *								also add dectalkf.h to catch the defined symbol
 *								For BATS#639 to change phinton() to use argument phTTS instead of pDph_t
 * 0031 EAB		04/10/1998		Add new German tuning rules plus add new parameters for debug printout to Make_f0
 * 0032 EAB		06/07/1998		eab 7/8/98 Begin to remove hat rise hat fall pattern. It doesn't just do the rise fall so like
								a cancer tumor the removal must be carefully done
 * 0033 EAB		07/08/1998		BATS 711 found bug in counting tcumdur + 709 German tuning
 * 0034 EAB		07/22/1998		First pass at adding wordfeatr with part of speech
								to intonation. Removed old GERMAN unused wordclass...
 * 0035 EAB		07/24/1998		Modified calling handle of MAKE_F0 to support debug printouts
 * 0036 EAB		08/17/1998		Spanish tuning with Juan
 * 0037 EAB		09/11/1998		Still improving/experimenting to improve naturalness
 * 0038 EAB		09/29/1998		Found some hidden problems ewhere values
 *								were getting sucked out of ROM.c instead of locally --also
 *								tuned for SPANISH_LA
 * 0039 EAB		10/16/1998		Final tuning from new release of spanish
 * 0040 EAB		10/22/1998		Bats 776- Some arrays were too short for max pointer movement
 *								causing a failure depending on whether the data follwoing the array 
 * 								was freindly or unfreindly values......
 * 0041 EAB						Further tuning of intonation values for relelase
 * 0042 EAB		11/04/1998		Final glotalization gesture is very sensitive to timing and needs to be adjusted in onset if
 *								the phoneme following the syllable nucleus is voiced BATS 796.
 * 0043 EAB		11/06/1998		Final adjustments for new release-this file is not the default version but I wanted to give an
 *								option to chose it BATS 807
 * 0044 EAB		11/09/1998		Tuned the UK_English male and female voice BATS 777
 *								if (new_intonation enabled for UK) This as part of the overall 5.0
 *								tuning process file in AD already contains changes 
 * 0045 EAB		11/10/1998		Fixed BATS 791 failure was dur to the fact that typing mode
 *								sent data without and end of clause which ph can handle but the tcumdur
 *								calulation was not handling correctly.
 * 0046	GL		11/20/1998		BATS#828 use PH_DEBUG to replace _DEBUG
 * 0047 EAB		02/03/1999		Added change from NWSNOAA->NWS_US for multi language NOA
 *								Plus did some tuning and added an printout to verifiy that some code is no longer
 *								needed and can be removed later and chnaged a variale name to a more explanatory one
 * 0048 EAB						Added in copyright notices plus trying to tune this ad code
 * 0049 EAb		06/07/1999		BATS 897
 * 0050 EAB		04/17/1999		Tuning changes for 4.6
 * 0051 EAB		04/18/1999		Fixed ifdef for UK for N_last_sylL...
 * 0052 CAB		03/15/2000		WINprintf not supported under Windows CE
 * 0053 MGS		04/13/2000		Changes for integrated phoneme set 
 * 0054 NAL		04/14/2000		Changed externs featb, begtyp to match declaration
 * 0055 CAB		05/23/2000		WINprintf not supported under Windows CE
 * 0056 NAL		06/12/2000		cast varibales (warning removal)
 * 0057 EAB		06/28/2000		Unified Phoneme Set Changes
 * 0058 CHJ		07/20/2000		French added
 * 0059 CHJ		07/28/2000		French feature bit modifications
 * 0060 CAB		09/21/2000		Fixed  copyright infoi and formatted comment section.
 * 0061 EAB		03/02/2001		Changed Fsonor back to FVOICD for rule 6 as silence has always
 *								been declared an FSONOR which causes this rule to do bad things.....
 *								also end glottal rules will be moved shortly to pressure model
 * 0062 EAB		03/13/2001		Tuning of intonation with Winfried.
 * 0063 EAB		03/28/2001		Fix bats 952 comma intonation
 * 0064 CAB		05/16/2001		Fixed warning by adding ()
   0046 EAB		07/10/2001
 * 0047 CAB		05/02/2002		Condensed #if
 * 0048 CAB		05/22/2002		Removed warnings
 */
/* #define MSDBG4 */
#include "dectalkf.h"


//BTS10192 Fixes some phoneme based on MRT
#include "ph_def.h"

#define BEFORE_HAT_RISE			0
#define ON_TOP_OF_HAT			1
#define AFTER_FINAL_FALL		2
#define AFTER_NONFINAL_FALL		3
#define DONTKNOW				0
#define QUESTCLAUSE				1
#define VERBPHRASE				2
#define PERIODCLAUSE			3


#define phone_feature(a,b) (pDph_t->cur_speaker[(b)>>8]->featb[(b)&0x00FF])
#define begtyp(b) (pDph_t->cur_speaker[(b)>>8]->begtyp[(b)&0x00FF])



/* 
 * Duration of the "dummy vowel" inserted after a clause-final stop.
 */
/* #define  DUMMY_V_DUR NF25MS      -- seems a bit long */
#define DUMMY_V_DUR   NF15MS



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

/* Input variables:                                                    */

/* Output variables:                                                   */

/* TABLES located in PH_ROM.C                                          */

//extern short f0_stress_level[];			/* F0 rise as f(stress-level)  	 */

//extern __inline short phone_feature(PDPH_T pDph_t, int phone);	   /* Phonetic features            */
//extern __inline short begtyp(int phone);
//extern short *begtyp;

//#define phone_feature(a,b) (all_featb[(b)>>8][(b)&0x00ff])
//#define begtyp(b) all_begtyp[(b)>>8][(b)&0xFF]

/* MVP : Static function declarations */
	
/*
 *      Function Name: phinton()      
 *
 *  	Description: 
 *
 *      Arguments: LPTTS_HANDLE_T phTTS		Text-To-speech handle
 *
 *      Return Value: 
 *
 *      Comments:
 *
 */
/* GL 03/25/1998,  BATS#639 use phTTS argument instead of pDph_t */

#define EMPH_FALL		  1				/* stress reduce shift for emph. stress 	*/
#define DELTAEMPH_SPEC  505				/* special value for fast emphatic str 	*/
#define DELTAEMPH		501				/* normal value for emphatic stress 		*/
#define DELTARISE		200				/* rise for continuing cadence */
#define DELTAFINAL		100				/* delta to remain at top in final cad. */
#define FINAL_FALL		  1				/* stress reduce shift for str. at top */

void gr_phinton (LPTTS_HANDLE_T phTTS)
{
	PKSD_T	pKsd_t = phTTS->pKernelShareData;
	PDPH_T	pDph_t = phTTS->pPHThreadData;
	int		temp;

	PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;

	short SCHWA1;
	short SCHWA2;
	short F0_QGesture1;
	short  F0_QGesture2;
	short F0_CGesture1;
	short F0_CGesture2;
	short GEST_SHIFT;
	short  MAX_NRISES;
	short F0_FINAL_FALL;
	short F0_NON_FINAL_FALL;
	short  F0_QSYLL_FALL;
	short *f0_mstress_level;
	short *f0_fstress_level;
	short *f0_mphrase_position;
	short *f0_fphrase_position;


	/* eab 2/26/97 EAB Group hardcoded items into one file to be 
	handled differently later */
	/* Note F0_Final _fall is the number of hertz *10 that it
	will try to fall below the baseline on a declarative stressed final syllable.
	*/

	/*nd, ... accent in a phrase
	* Check against MAX_NRISES in phinton.c
	*/

	const short gr_f0_mphrase_position[] =
	{
		/* First clause    Second clause  */
		/* 300, 275, 250, 200, 175, 150, 50,50 last pos=0 causes bad problems */
		160, 110, 90, 85, 75, 65 , 65, 65
	};

	const short gr_f0_fphrase_position[] =
	{
		/* First clause    Second clause  */
		/* 300, 275, 250, 200, 175, 150, 50,50 last pos=0 causes bad problems */
		120, 110, 90, 85, 75, 65 , 65,65
	};

	/* 
	* F0 rise as f(stress-level); Order is
	* FNOSTRESS  unstressed
	* FSTRESS_1  primary stress
	* FSTRESS_2  secondary stress
	* FEMPHASIS  emphatic stress
	*/

	const short gr_f0_mstress_level[] = {
		/* 'stress `stress "stress                      */
		0, 81, 71, 261					   /* eab original stress */
	};
	const short gr_f0_fstress_level[] =	{
		/* 'stress `stress "stress                      */
		0, 101, 91, 261					   /* eab original stress */
	};

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

	if(pKsd_t->lang_curr == LANG_german)
	{
		f0_mstress_level = (short *)gr_f0_mstress_level;
		f0_fstress_level = (short *)gr_f0_fstress_level;
		f0_mphrase_position = (short *)gr_f0_mphrase_position;
		f0_fphrase_position = (short *)gr_f0_fphrase_position;

		SCHWA1 = GRP_EX;
		SCHWA2 = GRP_EX;
		F0_QGesture1 = -120;
		F0_QGesture2 = 351;
		F0_CGesture1 = -120;
		F0_CGesture2 = 140;
		GEST_SHIFT = 1;
		MAX_NRISES = 6;
		F0_FINAL_FALL = 140;
		F0_NON_FINAL_FALL = 80;
		F0_QSYLL_FALL	= 80;
	}
	else return;

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
		if (phocur == GEN_SIL) 
		{
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
		while ((pDph_t->allofeats[nphonx] & FWINITC) IS_PLUS) 
		{
			nphonx++;
		}

		/*	  Step 2, Look up boundary immediately after current syll */
		nextsylbou = pDph_t->allofeats[nphonx] & FBOUNDARY;

		/*	  Step 3, Try to make direct assignment of boundary after current word */
		if (nextsylbou >= FWBNEXT) 
		{
			nextwrdbou = nextsylbou;
		}
		/*	  Step 4, Look ahead if this is not a word-final syllable */
		else 
		{
			for (nphonx=nphonx+1;nphonx<pDph_t->nallotot; nphonx++) 
			{
				if ((nextwrdbou=pDph_t->allofeats[nphonx]&FBOUNDARY)>=FWBNEXT) 
				{
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

		if ((pDph_t->f0mode == PHONE_TARGETS_SPECIFIED)
			|| (pDph_t->f0mode == SINGING))
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

		/* eab 4/30/98  another oliver check I think hat falls are good*/

		if((struccur & FHAT_ENDS) IS_PLUS )
			pDph_t->had_hatend= 1;

		if ((pDph_t->f0mode == NORMAL) || (pDph_t->f0mode == HAT_F0_SIZES_SPECIFIED))
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
							{
								pDphsettar->hatsize = 100;
							}

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

							pDphsettar->hatsize = pDphsettar->hatsize>>2;
							make_f0_command( phTTS,STEP, 1, (short)(pDphsettar->hatsize), delayf0, 30, &cumdur, nphon);

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
					{
						if (pDph_t->malfem == MALE)
							targf0 += f0_mphrase_position[pDphsettar->nrises_sofar];
						else
							targf0 += f0_fphrase_position[pDphsettar->nrises_sofar];
					}

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

					delayf0 = (pDph_t->allodurs[nphon] >> 2);

					/* Begin IMPULSE much earlier when last stress of phrase */
					if (((struccur & FHAT_ENDS) IS_PLUS)
						|| ((struccur & FPERNEXT) IS_PLUS))
					{
						delayf0 = -NF50MS;
						targf0 = -80;
					}

					/* Except when syllable is emphasized */
					if (stresscur == FEMPHASIS)
					{
						delayf0 = NF7MS;
					}

					if (pDph_t->f0mode == HAT_F0_SIZES_SPECIFIED)
					{
						targf0 = ((pDph_t->user_f0[mf0] - 1000) * 10) + 1;	/* Odd */
						if ((targf0 >= 2000) || (targf0 <= 0)
							|| (inputscrewup == TRUE))
						{
							targf0 = 1;		/* Must be odd, gre ater than 0 */
						}
						delayf0 = mstofr (pDph_t->user_offset[mf0]);
						mf0++;
					}

					/* Scale by speaker def paramter SR, unless emphasized */
					temp = pDph_t->scale_str_rise;
					if ((stresscur == FEMPHASIS) && (temp < 32))
					{
						temp = 32;
					}
					pDph_t->arg2 = targf0;
					pDph_t->arg3 = 32;
					targf0 = muldv (temp, targf0, 32);

					make_f0_command( phTTS,IMPULSE, 22, targf0, delayf0,(pDph_t->allodurs[nphon]-delayf0), &cumdur, nphon);

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

						if (pDph_t->hatstate == AFTER_FINAL_FALL) 
						{
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
					make_f0_command( phTTS, STEP, 3, (short)-f0fall, delayf0, length, &cumdur, nphon); // NAL warning removal
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

				if( (struccur & FBOUNDARY) == FQUENEXT || (struccur & FBOUNDARY) == FCBNEXT )
				{
					if( (struccur & FBOUNDARY) == FQUENEXT )
					{
						/* Sent.-final stressed vowel followed by q-mark */

						/* EAB We want the hardcoded gestures to be defined in a language specific 
						or speaker specific way file they ultimately want to be setable perhaps so for now I'm going
						to move all of these kinds of things to the speaker def files. 2/26/97 */

						pDph_t->delta_special = 0; 

						make_f0_command ( phTTS,IMPULSE, 41,F0_QGesture1, delayf0,24, &cumdur, nphon);
						make_f0_command ( phTTS, IMPULSE, 41,F0_QGesture2, pDph_t->allodurs[nphon],24, &cumdur, nphon);
					}
					else if((struccur & FBOUNDARY) == FCBNEXT)
					{
						/* Phrase-final stressed vowel followed by comma */
						/* 2/26/97 See comment above*/

						pDph_t->delta_special = -50;
						/* EAB 2/15/98 Needs earlier */

						delayf0 -= NF40MS;

						//BATS 709
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

			/* EAB 2/27/97 Fhat_fall on last stressed syl is not always appropriate because there aare times when there
			is still too many phonemes left to go to end of clause and we need to delay the fall. In previous 
			position it did and FSYL test which is not need because we must assume the fhat was put in the
			coreect place to begin with sorry it put in the right place it turns out this code hasn't
			work since I believe 1984*/
		}

		/* 
		* Rule 5: Final fall on unstress clause-final syl, or on stressed 
		* clause - final syll that didn't have hat fall due to earlier emphasis 
		*/

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

			if ((pDph_t->allofeats[nphon - 1] & FBOUNDARY) == FCBNEXT
				&& pDph_t->nf0tot > 0
				&& (pDph_t->allophons[nphon - 1] != GEN_SIL))
			{
				make_f0_command ( phTTS,F0_RESET, 7, 0, 0, 0, &cumdur, nphon); /* RESET! */
				issubclause = TRUE;
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

		if( (phonex == GEN_SIL) && 
			(phone_feature(pDph_t,phocur) & FPLOSV) && 
			(phone_feature( pDph_t,phocur) & FBURST) || 
			((phone_feature( pDph_t,phocur) & FCONSON)) && 
			phocur == USP_T && 
			pholas == USP_P && 
			phonex != USP_HX)
		{
			/* p t k b d g */
			/* || ((feacur & FNASAL) IS_PLUS) */ 
			/* m n nx en */
			/*&& (pDph_t->nallotot < NPHON_MAX)) I don't believe we should need this chnage earlier 
			NPHO_MAX code to a yellow zone code so we don't have to constantly check if were at the end things don't
			get added that frequently*/
			//for pennisular spanish don't release a voiced stop
			if( phone_feature( pDph_t,phocur) & FVOICD )
			{	
				for (n = pDph_t->nallotot+1; n > nphon; n--)
				{
					pDph_t->allophons[n] = pDph_t->allophons[n - 1];
					pDph_t->allofeats[n] = pDph_t->allofeats[n - 1];
					pDph_t->allodurs[n] = pDph_t->allodurs[n - 1];
					pDph_t->user_f0[n] = pDph_t->user_f0[n - 1];
				}

				pDph_t->allophons[nphon + 1] = SCHWA1;
				if ( (begtyp(pholas ) == 1)
					|| (phone_feature( pDph_t,phocur) & FALVEL ))
				{
					pDph_t->allophons[nphon + 1] = SCHWA2;
				}
				/*	      B,D,G need longer voicing in release to be heard as voiced */
				if (((phocur >= USP_P) && (phocur <= USP_G))	/* p t k b d g */
					&& ((feacur & FVOICD) IS_PLUS)) {
						pDph_t->allodurs[nphon+1] = NF160MS;
				}
				else {
					pDph_t->allodurs[nphon+1] = NF160MS;
				}

				if(!(pDph_t->allophons[nphon ] == LAP_T
					||
					pDph_t->allophons[nphon] == SPP_T))
				{
					cumdur += pDph_t->allodurs[nphon+1];
					if(phocur == USP_T && pholas == USP_P)
						pDph_t->allodurs[nphon+1] = NF80MS;
					/*eab 8/96 update tcumdur*/
					pDph_t->tcumdur +=pDph_t->allodurs[nphon+1];
					pDph_t->allofeats[nphon + 1] = pDph_t->allofeats[nphon] | FDUMMY_VOWEL;
					pDph_t->nallotot++;
					nphon++;
				}
			}
		}
	}	// Main phoneme loop
}
