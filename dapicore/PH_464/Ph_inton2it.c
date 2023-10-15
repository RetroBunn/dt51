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
 * 0024 EAB		01/10/1997		Added length parameter to make_f0_command_it glide will be the first command to use this.
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

//#define phone_feature(a,b) (pDph_t->cur_speaker[(b)>>8]->featb[(b)&0x00FF])
//#define begtyp(b) (pDph_t->cur_speaker[(b)>>8]->begtyp[(b)&0x00FF])

/* MVP : Static function declarations */
void make_f0_command_it (LPTTS_HANDLE_T phTTS,short type, short rulenumber, short tar, short delay,
					  short length,short *psCumdur,short nphon);
void do_by_rule_command(LPTTS_HANDLE_T phTTS,short *mf0, short *cumdur,short *nphon);
void do_britich_inton(LPTTS_HANDLE_T phTTS,short *cumdur, short *nphon, short *n_last_syl_nuc);
void do_italian_stress(LPTTS_HANDLE_T phTTS,short *cumdur, short *nphon,short *targf0);

#define EMPH_FALL		  1				/* stress reduce shift for emph. stress 	*/
#define DELTAEMPH_SPEC  505				/* special value for fast emphatic str 	*/
#define DELTAEMPH		501				/* normal value for emphatic stress 		*/
#define DELTARISE		200				/* rise for continuing cadence */
#define DELTAFINAL		100				/* delta to remain at top in final cad. */
#define FINAL_FALL		  1				/* stress reduce shift for str. at top */


					  /*nd, ... accent in a phrase
					  * Check against MAX_NRISES in phinton.c
*/
	
		
		
		
		const short it_f0_mphrase_position[] =
		{
			
			200, 200, 190, 185, 180, 175 , 170, 165  
				
		};
		
		/* 
		* F0 rise as f(stress-level); Order is
		*      FNOSTRESS       unstressed
		*      FSTRESS_1       primary stress
		*      FSTRESS_2       secondary stress
		*      FEMPHASIS       emphatic stress
		*/
		
		const short it_f0_mstress_level[] =
		{
			/* 'stress `stress "stress                      */
			20, 201, 81, 281					   /* eab original stress */
				
		};
		/* 
		* Stress-related rise/fall amount in Hz*10 for
		* first, second, ... accent in a phrase
		* Check against MAX_NRISES in phinton.c
		*/
		
		const short it_f0_fphrase_position[] =
		{
			//eab gafingerpoken 9/21/04
			230, 220, 210, 200, 190, 180 , 170, 160 
		};
		const short it_f0_fstress_level[] =
		{
			/* 'stress `stress "stress                      */
			20, 281, 121, 291	
		};
		

		
		
		
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
		void phintonit (LPTTS_HANDLE_T phTTS)
		{
			PKSD_T	pKsd_t = phTTS->pKernelShareData;
			PDPH_T	pDph_t = phTTS->pPHThreadData;
			PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;

			int		temp;
//			short F0_CBOUND_PULSE;
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
			short F0_GLOTTALIZE;
			short Reduce_last;
			short F0_COMMA_FALL;
			
			
			
			short *f0_mstress_level;
			short *f0_fstress_level;
			short *f0_mphrase_position;
			short *f0_fphrase_position;
			
			
			/* eab 2/26/97 EAB Group hardcoded items into one file to be 
			handled differently later */
			/* Note F0_Final _fall is the number of hertz *10 that it
			will try to fall below the baseline on a declarative stressed final syllable.
			*/
			
			
			
			
			
			/* Automatic variables */
			short nphon = 0, mf0 = 0;
			short length=0;
//			short n_last_syl_nuc;
			short pholas = 0, struclas = 0, fealas = 0;
			U32  struccur = 0, feacur = 0;
			U32  stresscur = 0;
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
			short oddeven = -1;
			pDph_t->delta_special=0;
			pDphsettar->nrises_sofar = 0;
			
			pDphsettar->hatsize = 0;
			pDphsettar->hat_loc_re_baseline = 0;
			
			/* Beginning of initialization */
			//	pDph_t->commacnt =0; //BATS709
			
			inputscrewup = FALSE;
			cumdur = 0;
			stepcount=0;
			pDph_t->had_hatbegin=0;
			pDph_t->had_hatend=0;
			pDph_t->in_phrase_final = 0;
			pDph_t->nf0tot = 0;
			pholas = GEN_SIL;
			fealas = phone_feature( pDph_t,GEN_SIL);
			struclas = 0;
			mf0 = 0;
			pDph_t->prevtargf0 = -1; /* EAB 1/13/98 Want first target to end up plus
			also initalize completion flag */
			pDph_t->done =0;
		
			
		
				f0_mstress_level = (short *)it_f0_mstress_level;
				f0_fstress_level = (short *)it_f0_fstress_level;
				f0_mphrase_position = (short *)it_f0_mphrase_position;
				f0_fphrase_position = (short *)it_f0_fphrase_position;
				
				SCHWA1 = ITP_AX;
				SCHWA2 = ITP_AX;
				F0_QGesture1 = -151;
				F0_QGesture2 = 481;
				F0_CGesture1 = -50;
				F0_CGesture2 = 220;
				GEST_SHIFT = 1;
				MAX_NRISES  = 6; 
				F0_FINAL_FALL  = 160;
				F0_NON_FINAL_FALL  = 150;
				F0_QSYLL_FALL	= 80;
				F0_GLOTTALIZE  = -10; //New method that drops per cycle rather than impulse BATS 796 EAB 11/4/98
				F0_COMMA_FALL	 = 120;
				Reduce_last = 50;
				
			
		
				
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
					
					

					stresscur = struccur & FSTRESS;
					feacur = phone_feature( pDph_t,phocur);
					if (nphon < (pDph_t->nallotot - 1))
					{
						phonex = pDph_t->allophons[nphon + 1];
						strucnex = pDph_t->allofeats[nphon + 1];
						feanex = phone_feature( pDph_t,phonex);
					}

					
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
					if (nextsylbou >= FCBNEXT) {				/* RSM To not count spurious FPPNEXT, FVPNEXT, and FRELNEXT */
						nextphrbou = nextwrdbou;
					}
					/*	  Step 6, Look ahead if this is not a phrase-final syllable */
					else {
						//wait this code is broken phonex+1
						
						
						for (nphonx=nphonx+1;nphonx<pDph_t->nallotot; nphonx++) {
							if ((nextphrbou=pDph_t->allofeats[nphonx]&FBOUNDARY)>FRELNEXT) {	
								goto fbfound;
							}
						}
					}
fbfound:
					
					/* Rule 0: User-specified commands for phoneme f0 targets or singing */
					
					if ((pDph_t->f0mode == PHONE_TARGETS_SPECIFIED)
						|| (pDph_t->f0mode == SINGING))
					{
						if (pDph_t->user_f0[nphon] != 0)
						{
							make_f0_command_it ( phTTS, USER,0, (short)(1000 + pDph_t->user_f0[nphon]), 0, 0, &cumdur,nphon); // NAL warning removal
						}
						goto skiprules;
					}
				
					if((struccur & FHAT_BEGINS) IS_PLUS  )
						pDph_t->had_hatbegin= 1;
					/* eab 4/30/98  another oliver check I think hat falls are good*/

					if((struccur & FHAT_ENDS) IS_PLUS )
						pDph_t->had_hatend= 1;

					if (pDph_t->f0mode == HAT_F0_SIZES_SPECIFIED)
					{
						do_by_rule_command(phTTS,&mf0,&cumdur,&nphon );
					}
					else if((feacur & FSYLL) IS_PLUS)
					{
							
							/* Rule 2 stress rules*/
							
							
							if ( (stresscur & FSTRESS) IS_PLUS  )
							{			/* Primary or emph */
								/* Make stress IMPULSE prop. to degree of stress */
								/* and stress position relative to clause onset */
								targf0=0;

							
									if (pDph_t->malfem == MALE)
										targf0 = f0_mstress_level[stresscur];
									else
										targf0 =  f0_fstress_level[stresscur];
								
								
											
								if (pDph_t->malfem == MALE)
									targf0 += f0_mphrase_position[pDphsettar->nrises_sofar];
								else
									targf0 += f0_fphrase_position[pDphsettar->nrises_sofar];
								
								if( pDph_t->number_words == 1 )
									targf0 = targf0 - (targf0>>1);
								pDph_t->impulse_width = pDph_t->allodurs[nphon]-5; 

								
								if (pDph_t->cbsymbol )
								{
									targf0 >>= 2;	/* All gestures reduced in ? */
								}
								
								/* eab 2/21/97 EAB remove emphasisflag and associated stuff pulled see note in phsort.c */
							
								
								do_italian_stress(phTTS, &cumdur,&nphon,&targf0);
							
							
							
								
								/* Increment stressed syllable counter */
								if (pDphsettar->nrises_sofar < MAX_NRISES)
									pDphsettar->nrises_sofar++;
								if (pDphsettar->nrises_sofar == MAX_NRISES)
									pDphsettar->nrises_sofar=1;
								
								
			}
			else
			if(pDph_t->set_drop == 0
				&& pDph_t->in_phrase_final ==0)
			{
				pDph_t->set_drop = 1;
	
			}
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
	pDph_t->had_hatend = 0;
	pDph_t->in_phrase_final = 1;
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
		
		/* Make fall start 180 ms from end of this vowel */
		delayf0 = pDph_t->allodurs[nphon] - NF100MS;
		/* But not too early */
		if (delayf0 < NF25MS)
			delayf0 = NF25MS;
		
		if (((struccur & FBOUNDARY) == FCBNEXT ) || (pDph_t->clausetype == COMMACLAUSE && pKsd_t->lang_curr == LANG_english))
		{
			f0fall = F0_NON_FINAL_FALL;
			
			
			pDph_t->hatstate = AFTER_NONFINAL_FALL;
		}
		/* Non-final phrase, don't go below baseline at all */
//		if ((struccur & FBOUNDARY) == FVPNEXT)
//		{		
//			f0fall = 0;
//		}
		
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
	//no rise no hat - stay on the brim	
	//	f0fall += pDphsettar->hatsize;
	}
	
	

		{
			
				//for the updown below base we must do everything different for italian
		//		f0fall = pDphsettar->hatsize; 
				if(nphon < pDph_t->nallotot-6)
				{
					//we're at an intermediat down/up ppstart or vpstart so
					//don't drop below baseline
					delayf0 = -6;
				}
				else
					f0fall += F0_FINAL_FALL;
			
				if(nphon == pDph_t->nallotot-1)
					delayf0 -= 10;
				length = (pDph_t->allodurs[nphon])-delayf0;
					if(pDph_t->number_words == 1)
						f0fall = f0fall >>1;
				make_f0_command_it( phTTS, STEP, 3, (short)-(f0fall), delayf0,length , &cumdur, nphon);
		}
//			else
								
				make_f0_command_it( phTTS, GLIDE, 3, (short)-(f0fall-150), delayf0, length, &cumdur, nphon); 
		if( f0fall > 50)
			pDph_t->hatstate = AFTER_FINAL_FALL;
		
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
				// BATS 711 Old code a lie without stresscur it isn't checking for stress
				// old comment correct 
				// do to changing a comma boundary to a period we must check--
				//we really should decide on cluse stuff at the very beginning
				if (((struccur & FBOUNDARY) == FCBNEXT)
					|| ((struccur & FBOUNDARY) == FQUENEXT))
				{
					/* Time rise to begin near end of vowel */
					delayf0 = pDph_t->allodurs[nphon] - NF80MS;
					
					pDph_t->delta_special = 0;
					
					if ((struccur & FBOUNDARY) == FQUENEXT)
					{
						/* Sent.-final stressed vowel followed by q-mark */
						
						/* EAB We want the hardcoded gestures to be defined in a language specific 
						or speaker specific way file they ultimately want to be setable perhaps so for now I'm going
						to move all of these kinds of things to the speaker def files. 2/26/97 */
						
						/* found that it is firing on clause final syllable in German for some
						reason but also in German it presently appears to not be required so not worth
						troubleshooting at the moment */ 
						pDph_t->delta_special = 0; /* This code is garbage put here as a noop space filter
						so that sompiler wouldn't get lost*/
			
//								make_f0_command_it ( phTTS,IMPULSE, 341,F0_QGesture1, -6,15, &cumdur, nphon);
//								make_f0_command_it ( phTTS, IMPULSE, 341,F0_QGesture2, (pDph_t->allodurs[nphon]>>1)-5,20, &cumdur, nphon);
							//								make_f0_command_it ( phTTS,IMPULSE, 341,F0_QGesture1, -6,15, &cumdur, nphon);
								make_f0_command_it ( phTTS, IMPULSE, 341,F0_QGesture2,5 ,20, &cumdur, nphon);

						
					}
				
				else
				{
#ifdef THISSHOULDBEWHQAT
					/* Phrase-final stressed vowel followed by comma */
					/* 2/26/97 See comment above*/
					
					
					pDph_t->delta_special = -50;
					/* EAB 2/15/98 Needs earlier */
					
					delayf0 -= NF20MS;
					
					
					//BATS 709
					if(pDph_t->commacnt == 0)
					{
						//make_f0_command_it ( phTTS, IMPULSE,42,  F0_CGesture1, 3 ,12, &cumdur, nphon);
						make_f0_command_it ( phTTS, IMPULSE, 42, 120, (short)delayf0,18, &cumdur, nphon);
					}
					
					else
						
						
					{
						make_f0_command_it ( phTTS, IMPULSE,420,  F0_CGesture1, delayf0,24, &cumdur, nphon);
						make_f0_command_it ( phTTS, IMPULSE, 420, F0_CGesture2, (short)(pDph_t->allodurs[nphon]>>1),24, &cumdur, nphon); // NAL warning removal
					}
					pDph_t->commacnt++;
#endif THISSHOULDBEWHQAT							
				}
				}
				
				
				
				
	
				
				if ((feacur & FSYLL) IS_PLUS)
				{
					
				
								/* Rule 6: Continuation rise on unstress clause-final syll before  comma or ? */
			/* Rise occurs just before end of vowel */ 
			/* This rule also appears to apply a final pitch fall to all declarative sentence-final syllables RSM */
			
			delayf0 = pDph_t->allodurs[nphon] - NF115MS;
			if ((struccur & FBOUNDARY) == FQUENEXT)
			{

{
				/* Unstressed vowel followed by a question mark */
				make_f0_command (phTTS,IMPULSE, 6, F0_QGesture1, delayf0, 24, &cumdur, nphon);
				make_f0_command (phTTS,IMPULSE, 6, F0_QGesture2, pDph_t->allodurs[nphon],20, &cumdur, nphon);
				}
				

				
			}
			if ((struccur & FBOUNDARY) == FCBNEXT)
			{
				/* Unstressed vowel followed by a comma */		
					delayf0 = pDph_t->allodurs[nphon] - NF115MS;
			
				make_f0_command ( phTTS,IMPULSE, 6, F0_CGesture1, 0, 24, &cumdur, nphon);
				make_f0_command ( phTTS,IMPULSE, 6, F0_CGesture2,delayf0, 30, &cumdur, nphon);

				
			}
			
			
			
			
			
			else if (((struccur & FBOUNDARY) == FPERNEXT))
			{
				targf0 = F0_GLOTTALIZE-200;
				
				/* 
				* Pitch falls are less pronounced for some speakers 
				* to reduce impression of assertive personality 
				*/
				
				targf0 = frac4mul(targf0, pDph_t->assertiveness);
				
				pDph_t->test_targf0 = targf0; /* RSM variable use to reduce the final fall in GERMAN */
				pDph_t->impulse_width = 20;	/* RSM */
				/* Sent.-final unstressed vowel followed by a period */
				/* eab 4/13/98 comment is wrong this is stressed vowel so review code in detail 
				when time permits*/
#ifdef GERMAN
			
				pDph_t->impulse_width = 10;
				if(pDph_t->number_words == 1)
				{
					make_f0_command ( phTTS,IMPULSE, 6, (short)targf0, (short)(pDph_t->allodurs[nphon] - NF130MS), 20, &cumdur, nphon); // NAL warning removal
				}
				else
#endif							
				/*	EAB 11/4/98 Final glotalization gesture is very sensitive to timing and needs to be adjusted in onset if
				the phoneme following the syllable nucleus is voiced.BATS 796  */
				if(phone_feature( pDph_t,phonex) & FVOICD)
				{
					pDph_t->test_targf0 = targf0>>3;
					if(nphon+2 <= pDph_t->nallotot && (phone_feature( pDph_t,pDph_t->allophons[nphon+2]) & FVOICD))
						/* nucleus has two voiced phonemes following it so delay even more*/
					{
						make_f0_command ( phTTS,IMPULSE, 6, pDph_t->test_targf0,  (pDph_t->allodurs[nphon]), pDph_t->impulse_width, &cumdur, nphon);
					}
					else	/* RSM */
					{
						delayf0 = (pDph_t->allodurs[nphon]>>1) + (pDph_t->allodurs[nphon]>>2);
						make_f0_command( phTTS,IMPULSE, 6, pDph_t->test_targf0,  delayf0, pDph_t->impulse_width, &cumdur, nphon);
					}
				}
				else
				{	// CAB Removed warnings by enclosing typecast in ()
					make_f0_command( phTTS,IMPULSE, 6, targf0, (short)((pDph_t->allodurs[nphon]>>1)+3),
						pDph_t->impulse_width, &cumdur, nphon); // NAL warning removal
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
			
					else
					{
						if ((pDph_t->allofeats[nphon - 1] & FBOUNDARY) == FCBNEXT
							&& pDph_t->nf0tot > 0
							&& (pDph_t->allophons[nphon - 1] != GEN_SIL))
						{
							make_f0_command_it ( phTTS,F0_RESET, 7, 0, 0, 0, &cumdur, nphon); /* RESET! */
							issubclause = TRUE;
						}
					}
				}
				/* Rule 8: Reset baseline and hat position to brim if end of a sentence */
				if ((struclas & FSENTENDS) IS_PLUS
					&& nphon == (pDph_t->nallotot))
				{
					pDph_t->commacnt=0; //BATS709
					make_f0_command_it ( phTTS,F0_RESET, 8, 0, 0, 0, &cumdur, nphon);
					pDphsettar->hat_loc_re_baseline = 0;
					/* Hard reset counter of stressed sylls in clause */
					pDphsettar->nrises_sofar = 0;
				}
				
				
				
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
					* EAB 2/28/97 changing to generalize when FPLOS + Fburst then release into a schwa
				*/
				// 3/14/01 eab don't use dummy vowel if cons unvoiced
				// 6/14/01 eab chnage- use it but don't voic it we need the placeholder for the release
				
				if (( phonex == GEN_SIL)&& (phone_feature( pDph_t,phocur) & FPLOSV) 
					&& (phone_feature( pDph_t,phocur) & FBURST) 
					/*&& phone_feature( pDph_t,phocur) & FVOICD*/)
				{
					/* p t k b d g */
					/* || ((feacur & FNASAL) IS_PLUS) */ 
					/* m n nx en */
					/*&& (pDph_t->nallotot < NPHON_MAX)) I don't believe we should need this chnage earlier 
					NPHO_MAX code to a yellow zone code so we don't have to constantly check if were at the end things don't
					get added that frequently*/
					
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
						pDph_t->allophons[nphon + 1] = SCHWA1;
					}
					/*	      B,D,G need longer voicing in release to be heard as voiced */
					if (((phocur >= USP_P) && (phocur <= USP_G))	/* p t k b d g */
						&& ((feacur & FVOICD) IS_PLUS)) {
						pDph_t->allodurs[nphon+1] = NF40MS;
					}
					else {
						pDph_t->allodurs[nphon+1] = NF40MS;
					}
					
					
					cumdur += pDph_t->allodurs[nphon+1];
					
					/*eab 8/96 update tcumdur*/
					pDph_t->tcumdur +=pDph_t->allodurs[nphon+1];
					pDph_t->allofeats[nphon + 1] = pDph_t->allofeats[nphon] | FDUMMY_VOWEL;
					pDph_t->nallotot++;
					nphon++;
				}
				
				}
}

void make_f0_command_it(LPTTS_HANDLE_T phTTS, short type, short rulenumber, short tar,
				 			 short delay, short length, short *psCumdur, short nphon)
{
	PKSD_T pKsd_t = phTTS->pKernelShareData;
	PDPH_T pDph_t = phTTS->pPHThreadData;

	/* Cudur reflects time (in frames) since last f0 command        */
	/* Cumdur+delay should never be less than zero                  */

	/* static short prpholas, temp; *//* MVP : Never Used,comment it out */
	/* If requested time is earlier than last f0 command, zero offset */
		
#ifdef PH_DEBUG

#endif // PH_DEBUG
	if(length == 0 && type != 3)
	{
#ifdef PH_DEBUG
#ifndef UNDER_CE	//CAB 03/15/00 WINprintf not supported under Windows 
	
		WINprintf("error length ==0 settting to 1\n");

#endif
#endif
	length=1;
	}
	//init lastevent
	if(pDph_t->nf0tot == 0)
		pDph_t->lastevent = 0;
	if(delay + pDph_t->tcumdur < pDph_t->lastevent)
	{
		//can't have an event before previous
		delay = (pDph_t->lastevent-pDph_t->tcumdur)+1;
#ifdef PH_DEBUG
#ifndef UNDER_CE	//CAB 03/15/00 WINprintf not supported under Windows CE
	if (DT_DBG(PH_DBG,0x010))
		WINprintf(" requested an event before previous one setting to 1 frame after last event % \n ",delay);
#endif
#endif // PH_DEBUG
	}
	 
	//if ((delay + *psCumdur) < 0)
	//{
	//		delay = -(*psCumdur);
	//}
	/* Save commands */	
	pDph_t->f0tim[pDph_t->nf0tot] =pDph_t->lastevent = pDph_t->tcumdur + delay;
	if(pDph_t->f0tim[pDph_t->nf0tot] == 0)
		//zero is not functional 1 is the smallest 
		pDph_t->f0tim[pDph_t->nf0tot] =1;
	pDph_t->f0tar[pDph_t->nf0tot] = tar;
	pDph_t->f0type[pDph_t->nf0tot] = type;
	/* eab 1/10/98 We need to be able to specifiy the length
	of the event instead of having only
	one choice. Initally some commands will ignore length*/
	pDph_t->f0length[pDph_t->nf0tot] = length;
//	printf(" command is at time %d \n",(int)(6.4*pDph_t->f0tim[pDph_t->nf0tot]));
	/* "Zero" counter of time since last command */
//	*psCumdur = (-delay);
#ifdef PH_DEBUG
#ifndef UNDER_CE	//CAB 03/15/00 WINprintf not supported under Windows CE
	if (DT_DBG(PH_DBG,0x010))
//		WINprintf("phon %d nphon %d rule %d type %d , tar %d delay %d length %d  \n",(pDph_t->allophons[nphon] & PVALUE), nphon, rulenumber,type, tar, delay, length);
		WINprintf("tcum %d time point %d phon %d nphon %d rule %d type %d , tar %d delay %d length %d  \n",(int)(pDph_t->tcumdur*6.4),(int)(pDph_t->lastevent*6.4),(pDph_t->allophons[nphon] & PVALUE), nphon, rulenumber,type, tar, delay, length);
#endif
#endif
	/* Increment counter of number of f0 commands issued */
	if (pDph_t->nf0tot < NPHON_MAX - 1)
	{
		pDph_t->nf0tot++;
	}
}

void do_by_rule_command(LPTTS_HANDLE_T phTTS,short *mf0, short *cumdur,short *nphon)
{

	  PKSD_T pKsd_t = phTTS->pKernelShareData;
	  PDPH_T pDph_t = phTTS->pPHThreadData;
	  PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;
short temp,tmp;							
short delayf0;
short length;
				if( pDph_t->user_f0[*mf0])
				{
					pDphsettar->hatsize = (pDph_t->user_f0[*mf0] * 10);
					tmp = pDph_t->user_offset[*mf0];
					delayf0=0;
					temp = *nphon;
					//delayf0 = pDph_t->allodurs[*nphon]*pDph_t->user_offset[*mf0]/100;
					if(tmp < 0)
						delayf0 = pDph_t->allodurs[*nphon-1]*tmp/100;
					else while(tmp > 0) 
					{
						delayf0 += pDph_t->allodurs[temp]*pDph_t->user_offset[*mf0]/100;
						tmp -= 100;
						temp ++;
					}
					
			//		printf("delay %d percent  = %d\n",pDph_t->user_offset[*mf0],(int)(delayf0*6.4));
					tmp=pDph_t->user_length[*mf0];
					length=0;
					temp = *nphon;
					//delayf0 = pDph_t->allodurs[*nphon]*tmp/100;
					if(tmp < 0)
						length = pDph_t->allodurs[*nphon-1]*tmp/100;
					else while(tmp > 0) 
					{
						length += pDph_t->allodurs[temp]*tmp/100;
						tmp -= 100;
						temp ++;
					}	
					length -= delayf0;
				//	printf("lenght %d percent  = %d \n",pDph_t->user_length[*mf0],(int)(length*6.4));
			
					
					*mf0++;
					make_f0_command_it( phTTS,GLIDE, 99, (short)(pDphsettar->hatsize),
						delayf0, length, cumdur, *nphon); // NAL warning removal
					
				}
			}
			
		

void do_italian_stress( LPTTS_HANDLE_T phTTS,short *cumdur, short *nphon,short *targf0)
{
	
	  PKSD_T pKsd_t = phTTS->pKernelShareData;
	  PDPH_T pDph_t = phTTS->pPHThreadData;

short length;
									
							length = pDph_t->allodurs[*nphon];
							if(phone_feature( pDph_t,pDph_t->allophons[*nphon+1]) & FSONOR && pDph_t->allophons[*nphon+1] != GEN_SIL)
							{
								length += pDph_t->allodurs[*nphon+1];
							}
							if(phone_feature( pDph_t,pDph_t->allophons[*nphon+2]) & FSONOR && pDph_t->allophons[*nphon+2] != GEN_SIL)
							{
								length += pDph_t->allodurs[*nphon+1];
							}
							
							if( *nphon < (pDph_t->nallotot-3))
							{
							//	make_f0_command_it( phTTS,GLIDE, 24, -200, 0,10 , cumdur, *nphon);
							//	make_f0_command_it( phTTS,GLIDE, 24, (*targf0<<1)+195,10,length , cumdur, *nphon);
							//	make_f0_command_it( phTTS,GLIDE, 24, -*targf0<<1,length+4 ,12, cumdur, *nphon);
									make_f0_command_it( phTTS,GLIDE, 24,*targf0 ,-10,10 , cumdur, *nphon);
								make_f0_command_it( phTTS,GLIDE, 24, -*targf0,10,length , cumdur, *nphon);
								//make_f0_command_it( phTTS,GLIDE, 24, -*targf0<<1,length+4 ,12, cumdur, *nphon);
							}
		
							
						}							




  /***********************end of ph_inton2.c**************************************/