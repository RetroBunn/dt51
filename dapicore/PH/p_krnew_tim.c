/* 
 ***********************************************************************
 *
 *                           Copyright ©
 *	  Copyright © 2002 Fonix Corporation. All rights reserved.
 *	  Copyright © 2000-2001 Force Computers, Inc., a Solectron Company. All rights reserved.
 *    © Digital Equipment Corporation 1996, 1997. All rights reserved.
 */


#include "dectalkf.h"
#include "ph_def.h"

//#define DEBUGPHT
//#define FASTTALK
//extern __inline short phone_feature(PDPH_T pDph_t, int phone);	   /* Phonetic features            */
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
void krnew_phtiming(LPTTS_HANDLE_T phTTS)
{
	PDPH_T			pDph_t = phTTS->pPHThreadData;
	PKSD_T          pKsd_t = phTTS->pKernelShareData;
	PDPHSETTAR_ST   pDphsettar = pDph_t->pSTphsettar;
	short           stcnt = 0;
	short			cons_dur =0;
	short           syldur = 0;
	short           ncnt = 0;
	short           endcnt = 0;
	short           adjust = 0;
	short           emphasissw = FALSE;		/* Made local and initialized */
	short                   
		pholas		= GEN_SIL,		// last phoneme
		struclas	= 0,
		fealas		= GEN_SIL,
		phocur		= 0,			// current phoneme
		struccur	= 0,
		feacur		= 0,
		phonext		= 0,			// next phoneme
		strucnext	= 0,
		feanext		= 0;
	short                   
		prcnt		= 0, 
		durinh		= 0, 
		durmin		= 0, 
		deldur		= 0,			// delta duration
		nphon		= 0;			// phoneme counter
	short
		dpause = 0,
		arg1,					/* arguments for the phmath routines. */
		arg2,
		tmp;	
	U32  wordfeat;

	init_timing (phTTS);

	pDphsettar->numstresses =0;
	pDph_t->tcumdur =0;

	/* MAIN LOOP, for each output phoneme */
	for (nphon = 0; nphon < pDph_t->nallotot; nphon++)
	{
		// Get information about the previous phoneme
		if (nphon > 0)
		{
			pholas = pDph_t->allophons[nphon-1];
			struclas = pDph_t->allofeats[nphon-1];
			fealas = phone_feature(pDph_t, pholas);
		}
		// Get info about next phoneme
		if( nphon < pDph_t->nallotot-1 )
		{
			phonext = pDph_t->allophons[nphon+1];
			strucnext = pDph_t->allofeats[nphon+1];
			feanext = phone_feature(pDph_t ,phonext);

			pDphsettar->phonex_timing = pDph_t->allophons[nphon+1];
			pDphsettar->strucnex = pDph_t->allofeats[nphon+1];
			pDphsettar->feanex = phone_feature(pDph_t, phonext);
		}

		// Get info about the current phoneme
		phocur = pDph_t->allophons[nphon];
		struccur = pDph_t->allofeats[nphon];
		feacur = phone_feature(pDph_t, phocur);
		pDphsettar->strucstressprev = (struccur & FSTRESS) IS_PLUS;

		tmp = phocur & PVALUE;
		prcnt = 128;								// Multiplicative constant (let 128 be 100%)

		if( (struccur & FSTRESS) IS_PLUS )
		{
			pDphsettar->numstresses++;
		}

		wordfeat = pDph_t->allofeats[nphon] & WORDFEAT;

		/* Convert inherent and minimum duration in msec to frames.*/
		durinh = mstofr(inh_timing(phTTS,phocur));
		durmin = mstofr(min_timing(phTTS,phocur));

		/* Additive increment - delta duration */
		deldur = 0;
	
		PH_DEBUG_2080_P2(" krnew_phtiming: phone %d (%s)", nphon, phprint(pDph_t->allophons[nphon]));
		PH_DEBUG_2080_P2(" durinh=%.1f, durmin=%.1f\n", durinh*6.4f, durmin*6.4f);


		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
		/* Duration Rules                         						   */
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
		/* Use user-specified duration if one exists.    */
		/* User durations can be huge; call the conversion routine.   */
		if( pDph_t->user_durs[nphon] != 0 )
		{
			if( pDph_t->user_durs[nphon] < 0 )
			{
				// User duration is in percent of inherent duration
				prcnt = (-pDph_t->user_durs[nphon]);
				pDphsettar->durxx = durinh * prcnt / 100;
				//prcnt = 128 * (-pDph_t->user_durs[nphon]) / 100;			
				//pDphsettar->durxx = (prcnt * (durinh - durmin)) DIV_BY128;
				//pDphsettar->durxx += durmin;
				PH_DEBUG_2080_P2("  User duration: %.1f ms (%d%%)\n", pDphsettar->durxx*6.4f, prcnt);
			}
			else
			{
				pDphsettar->durxx = mstofr(pDph_t->user_durs[nphon]);		// User duration is in absolute milliseconds
				PH_DEBUG_2080_P1("  User duration: %.1f ms\n", pDphsettar->durxx*6.4f);
			}
			deldur = 0;


			goto break3;
		}


		/* ======================================
					Silence duration rules
		   ====================================== */
		/* 
		 * Rule 1: Pause durations depend on syntax
		 *          Clause-initial pause should be minimal, i.e. NF64MS (enough
		 *          time for initial fricative to build up amp gradually)
		 *          Shortened to 0, except for fricitive and plosive in next phone
		 *          we go do 7 ...
		 */
		if(phocur == GEN_SIL)
		{
			if( (feanext & (FVOICD | FOBST)) || 
				(feanext & FPLOSV))
				dpause = 4;
			else
				dpause = 5;

			pDph_t->asperation = 0;		//(pDph_t->asperation - BASE_ASP) / 10;

			/* Treatment of other than clause-initial pauses: */
			if (nphon > 1)
			{
				/* If this clause ends in a comma, use short pause */
				/* Note extra compause added if user command [:dv cp __] */
				if ((struclas & FBOUNDARY) == FCBNEXT)
				{
					if (pDph_t->asperation > MAX_ASP_COMMA)
						pDph_t->asperation = MAX_ASP_COMMA;
					else if (pDph_t->asperation < MIN_ASP_COMMA)
						pDph_t->asperation = MIN_ASP_COMMA;

					dpause = pDph_t->nfcomma + pDph_t->compause + pDph_t->asperation;
				}

				/* End of clause has long pause if ends with "." "!" or "?" */
				/* Note extra perpause added if user command [:dv pp __] */
				if (((struclas & FBOUNDARY) & FSENTENDS) IS_PLUS)
				{
					if (pDph_t->asperation > MAX_ASP_PERIOD)
						pDph_t->asperation = MAX_ASP_PERIOD;
					else if (pDph_t->asperation < MIN_ASP_PERIOD);
						pDph_t->asperation = MIN_ASP_PERIOD;

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
			dpause = mlsh1 (dpause, pDphsettar->sprat1);		// pause * sprate / 16384

			/* Minimum pause is 13 ms*/
			if (dpause < 2)
				dpause = 2;

			/* Skip over remaining duration rules if input is SIL */
			pDphsettar->durxx = dpause;

			durinh = pDphsettar->durxx;
			goto break3;

		}	// phocur == GEN_SIL

	
		/* ======================================
					Vowel duration rules
		   ====================================== */
		else if( (feacur & FVOWEL) IS_PLUS )
		{
			if( (struccur & FSTRESS) IS_MINUS )
			{
				durmin >>= 1;
			}

			if( ((fealas & FSON2) IS_PLUS) &&
				 ((fealas & FNASAL) IS_MINUS) )
			{
				deldur = NF20MS;
				PH_DEBUG_2080("  Lengthen vowel in non-nasal soncon + vowel combination by 20ms.\n");
			}

			else if( ((struccur & FTYPESYL) == FFIRSTSYL) &&
				((struccur & FSTRESS_1) IS_PLUS) &&
				((struclas & FWINITC) IS_MINUS) )
			{
				deldur += NF25MS;
				PH_DEBUG_2080("  Lengthen word-initial stressed vowel of a poly-syllabic word by 25ms.\n");
			}
			else if( (fealas & FVOWEL) IS_PLUS ||
					 (feanext & FVOWEL) IS_PLUS )
			{
				arg1 = N65PRCNT;
				arg2 = prcnt;
				prcnt = mlsh1(arg1, arg2);	

				PH_DEBUG_2080_P1("  Shorten vowel+vowel combinations to %d%%.\n", (int)(arg1*100/N100PRCNT));
			}

			// Pre-Vocalic consonant duration affects
			if( (fealas & FCONSON) IS_PLUS )
			{
				arg1 = N100PRCNT;
				if( pholas == KRP_PP || 
					pholas == KRP_TT ||
					pholas == KRP_KK ||
					pholas == KRP_CC ||
					pholas == KRP_SS )
				{
					arg1 = N100PRCNT;		// Tense (72%)
					PH_DEBUG_2080_P1("  Shorten vowel to %d%% after Tense consonant/stop. (?)\n", (int)(arg1*100/N100PRCNT));
				}
				else
				if( pholas == KRP_P || 
					pholas == KRP_T ||
					pholas == KRP_K ||
					pholas == KRP_JH ||
					pholas == KRP_S )
				{
					arg1 = N63PRCNT;		// Lax
					PH_DEBUG_2080_P1("  Shorten vowel to %d%% after Lax consonant/stop.\n", (int)(arg1*100/N100PRCNT));
				}
				else
				if( pholas == KRP_PH || 
					pholas == KRP_TH ||
					pholas == KRP_KH ||
					pholas == KRP_CH ||
					pholas == KRP_HX )
				{
					arg1 = N85PRCNT;		// Aspirated (53%)
					PH_DEBUG_2080_P1("  Shorten vowel %d%% after Aspirated consonant/stop.\n", (int)(arg1*100/N100PRCNT));
				}
				else
				if( (fealas & FNASAL) IS_PLUS &&
					nphon >= 2 &&
					pDph_t->allophons[nphon-2] == GEN_SIL )
				{
					arg1 = N78PRCNT;
					PH_DEBUG_2080_P1("  Shorten vowel %d%% after Nasal and phrase initial.\n", (int)(arg1*100/N100PRCNT));
				}

				arg2 = prcnt;
				prcnt = mlsh1(arg1, arg2);	
			}

			// Post-vocalic consonant duration affects
			if( (feanext & FCONSON) IS_PLUS )
			{
				arg1 = N100PRCNT;
				if( phonext == KRP_P || 
					phonext == KRP_T ||
					phonext == KRP_K )
				{
					if( prcnt >= 100 )
						arg1 = N50PRCNT;
					else
						arg1 = N75PRCNT;
					PH_DEBUG_2080_P1("  Shorten vowel to %d%% before a Lax stop.\n", (int)(arg1*100/N100PRCNT));
				}
				else
				if( (feanext & FBURST) IS_PLUS )
				{
					if( prcnt >= 100 )
						arg1 = N35PRCNT;			// Temp Model 0.31
					else
						arg1 = N70PRCNT;
					PH_DEBUG_2080_P1("  Shorten vowel to %d%% before a stop.\n", (int)(arg1*100/N100PRCNT));
				}
				else
				if( (feanext & FNASAL) IS_PLUS )
				{
					if( nphon < pDph_t->nallotot-2 &&
						pDph_t->allophons[nphon+2] == GEN_SIL )
					{
						arg1 = N150PRCNT;
						PH_DEBUG_2080_P1("  Lengthen vowel %d%% before a Nasal and phrase final.\n", (int)(arg1*100/N100PRCNT));
					}
					else
					{
						if( prcnt >= 100 )
							arg1 = N25PRCNT;			// Temp Model 0.26
						else
							arg1 = N75PRCNT;
						PH_DEBUG_2080_P1("  Shorten vowel %d%% before a nasal.\n", (int)(arg1*100/N100PRCNT));
					}
				}
				else
				if( (feanext & FSONCON) IS_PLUS )
				{
					if( prcnt >= 100 )
						arg1 = N75PRCNT;			// Temp Model 0.73
					else
						arg1 = N87PRCNT;
					PH_DEBUG_2080_P1("  Shorten vowel %d%% before a liquid.\n", (int)(arg1*100/N100PRCNT));
				}
				else
				{
					if( prcnt >= 100 )
						arg1 = N35PRCNT;			// Temp Model 0.33
					else
						arg1 = N75PRCNT;
					PH_DEBUG_2080_P1("  Shorten vowel %d%% before a fricative.\n", (int)(arg1*100/N100PRCNT));
				}

				arg2 = prcnt;
				prcnt = mlsh1(arg1, arg2);
			}

			// Prosodic influence on vowel duration - 
			//	"Consonantal and Prosodic Influences on Korean Vowel Duration"	(CPIKVD)
			//  "A New Korean Speech Synthesis System and Temporal Model" (Temp Model)
			arg1 = N100PRCNT;
			if( pholas == GEN_SIL )
			{
				arg1 = N87PRCNT;				// Temp Model = 0.93, CPIKVD = 0.82
				PH_DEBUG_2080_P1("  Shorten vowel in phrase initial position to %d%%.\n", (int)(arg1*100/N100PRCNT));
			}
			else if( phonext == GEN_SIL )
			{
				arg1 = N150PRCNT;				// Temp Model = 1.72, CPIKVD = 0.98
				PH_DEBUG_2080_P1("  Lengthen vowel in clause final position to %d%%.\n", (int)(arg1*100/N100PRCNT));
			}
			else if( prcnt >= 100 )
			{
				arg1 = N70PRCNT;				// CPIKVD = 0.68, 0.59 ...
				PH_DEBUG_2080_P1("  Shorten vowel in phrase medial position to %d%%.\n", (int)(arg1*100/N100PRCNT));
			}
			arg2 = prcnt;
			prcnt = mlsh1(arg1, arg2);	

		}	// Vowel duration rules

		/* ======================================
					Nasal duration rules
		   ====================================== */
		else if( (feacur & FNASAL) IS_PLUS )
		{
			arg1 = N100PRCNT;	// default

			if( (feanext & FCONSON) IS_PLUS && 
				(strucnext & FWINITC) IS_PLUS )
			{
				arg1 = N150PRCNT;
				PH_DEBUG_2080_P1("  Lengthen nasal if word final to %d%%.\n", (int)(arg1*100/N100PRCNT));
			}
			else if( (fealas & FNASAL) IS_PLUS ||
					 (feanext & FNASAL) IS_PLUS )
			{
				arg1 = N60PRCNT;
				durmin >>= 1;
				PH_DEBUG_2080_P1("  Shorten nasal+nasal combination to %d%%.\n", (int)(arg1*100/N100PRCNT));
			}
			else if( pholas == GEN_SIL )
			{
				arg1 = N75PRCNT;
				durmin >>= 1;
				PH_DEBUG_2080_P1("  Shorten nasal if phrase initial to %d%%.\n", (int)(arg1*100/N100PRCNT));	// See bug 708
			}

			arg2 = prcnt;
			prcnt = mlsh1(arg1, arg2);	
		}

		/* ======================================
					Plosive duration rules
		   ====================================== */
		else if( (feacur & FPLOSV) IS_PLUS )
		{
			arg1 = N100PRCNT;		// default

			if( ((fealas & FPLOSV) IS_PLUS) &&
				((feanext & FOBST) IS_PLUS) &&
				((struccur & FBOUNDARY) > FMBNEXT) )
			{
				durmin >>= 1;
				arg1 = N25PRCNT;
				PH_DEBUG_2080_P1("  Shorten stop2 in stop+stop2+fricative combination to %d%%.\n", (int)(arg1*100/N100PRCNT));
			}
			else if( (feanext & FPLOSV) IS_PLUS ||
					 (fealas & FPLOSV) IS_PLUS )
			{
				durmin >>= 1;
				arg1 = N75PRCNT;		// 50%
				PH_DEBUG_2080_P1("  Shorten plosv+plosv combination to %d%%.\n", (int)(arg1*100/N100PRCNT));
			}
			else if( (feanext & FCONSON) IS_PLUS )
			{
				PH_DEBUG_2080("  Shorten plosive in plosv+conson combination?\n");
			}
			else if( (fealas & FCONSON) IS_PLUS )
			{
				PH_DEBUG_2080("  Shorten plosive in conson+plosv combination?\n");
			}
			arg2 = prcnt;
			prcnt = mlsh1(arg1, arg2);
		}

		/* ======================================
					Consonant duration rules
		   ====================================== */
		else if( (feacur & FCONSON) IS_PLUS )
		{
			arg1 = N100PRCNT;		// default

			if( (feacur & FSONCON) IS_PLUS )
			{
				if( phocur == KRP_L )
				{
					if( phonext == GEN_SIL )
					{
						arg1 = N180PRCNT;
						PH_DEBUG_2080_P1("  Lengthen phrase final /L/ to %d%%.\n", (int)(arg1*100/N100PRCNT));
					}
					else if( (fealas & FVOWEL) IS_PLUS )
					{
	 					// Shorten /L/ in coda final position
						arg1 = N65PRCNT;
						durmin >>= 1;
						PH_DEBUG_2080_P1("  Shorten /L/ in vowel+/L/ combinations to %d%%.\n", (int)(arg1*100/N100PRCNT));
					}
				}
			}
			// First consonant of a two consonant sequence
			else if( (feanext & FCONSON) IS_PLUS )		
			{
				if( (feanext & FPLOSV) IS_MINUS )
				{
					arg1 = N50PRCNT;
					durmin >>= 1;
					PH_DEBUG_2080_P1("  Shorten consonant + consonant combinations to %d%%.\n", (int)(arg1*100/N100PRCNT));
				}
				
				else if( (feanext & FPLOSV) IS_MINUS )
				{
					/* Default shortening is 70 percent for non plosive-plosive combinations */
					arg1 = N70PRCNT;
					durmin -= (durmin >> 2);
					PH_DEBUG_2080_P1("  Default shortening for non-plosive+plosive combinations to %d%%.\n", (int)(arg1*100/N100PRCNT));
				}
			}

			// Second consonant of a two consonant sequence
			else if( (fealas & FCONSON) IS_PLUS )
			{
				/* Second consonant of a two-consonant sequence */
				/* Default - shorten by 30% (Multiply by 0.7) */
				arg1 = N70PRCNT;

				if( (fealas & FNASAL) IS_PLUS &&
					(feacur & FBURST) IS_PLUS )
				{
					arg1 = N90PRCNT;
					durmin >>= 1;							// shorten durmin by 50%
					PH_DEBUG_2080_P1("  Shorten nasal-burst combination to %d%%.\n", (int)(arg1*100/N100PRCNT));
				}
				else if( (fealas & FBURST) IS_MINUS )
				{
					arg1 = N50PRCNT;						// Shorten S + SS combinations
					durmin >>= 1;							// shorten durmin by 50%
					PH_DEBUG_2080_P1("  Shorten consonant (non-plosive) combinations to %d%%.\n", (int)(arg1*100/N100PRCNT));
				}
				else
				{
					arg1 = N70PRCNT;
					durmin -= (durmin>>2);
					PH_DEBUG_2080_P1("  Default shortening of the second consonant of a two-consonant sequence to %d%%.\n", (int)(arg1*100/N100PRCNT));
				}
			}

			else if( (fealas & FVOWEL) IS_PLUS && 
					 (feacur & FVOICD) IS_MINUS )
			{
				arg1 = N110PRCNT;
				PH_DEBUG_2080_P1("  Lengthen unvoiced consonant after vowel to %d%%.\n", (int)(arg1*100/N100PRCNT));
			}

			arg2 = prcnt;
			prcnt = mlsh1 (arg1, arg2);

			/* 
			 * Rule 18:Shortening of prevocalic clustered semivowels clustered 
			 * on left by stop or fricative. Before this rule, many sounded like 
			 * syllabic reduced segmanents, so fruit sounded like feruit. */	 

			if( (feacur & FSONCON) IS_PLUS && 
				((fealas & FOBST) IS_PLUS) )
			{
				arg1 = prcnt;
				arg2 = N70PRCNT;
				prcnt = mlsh1 (arg1, arg2);
				PH_DEBUG_2080_P1("  Shorten semivowels clustered with a stop or fricative on the left to %d%%.\n", (int)(arg1*100/N100PRCNT));
			}

		}	// else if consonant

		
		/* Finish up */
		/* Set duration from durinh, durmin, and percent */
		pDphsettar->durxx = (prcnt * (durinh - durmin)) DIV_BY128;
		pDphsettar->durxx += durmin;   /* SHOULD BE DONE AFTER SPRATE ADJUSTMENT */

break3:

		/* Effect of speaking rate */
		if ((pDphsettar->sprat0 != 180) && (pDphsettar->durxx != 0))
		{
			arg1 = pDphsettar->durxx;
			arg2 = pDphsettar->sprat2;
			if(pDph_t->number_words == 1)					// Give single words a little longer duration
				arg2 += (pDphsettar->sprat2>>3);
			pDphsettar->durxx = mlsh1(arg1, arg2);			// Scale duration by the speaking rate

			PH_DEBUG_2080_P1("  Applying effect of speaking rate(%dwpm).\n", pDphsettar->sprat0);

			/* Effect of speaking rate on additive increment to dur */
			arg1 = deldur;
			arg2 = pDphsettar->sprat1;
			deldur = mlsh1(arg1, arg2);
		}

		/* Add in rule-governed additive increment to dur  */
		pDphsettar->durxx = pDphsettar->durxx + deldur;

		if( pDphsettar->durxx < 0 )
			pDphsettar->durxx=1;
	
		pDph_t->allodurs[nphon] = pDphsettar->durxx;

		PH_DEBUG_2080_P2("  Final duration = %.1f, prcnt=%d", 
			(pDphsettar->durxx * 6.4f), prcnt*100/128);
		PH_DEBUG_2080_P2(", durmin=%.1f, other additions = %.1f\n",
			durmin*6.4f, deldur*6.4f);

		if (pDph_t->allophons[nphon] != GEN_SIL)	   			   /* don't count silence 			  */
		{
			/* FNX_PRINTF("add %d for phon %d\n",pDphsettar->durxx,pDph_t->allophons[nphon]); 	  */
			//EAB 11/20/98 In English this is really not syldur but duration between stess as English
			//is a stressed timed language. The code was origianlly down for a syllable timed language hence hte syldur nomiclature
			syldur += pDphsettar->durxx;
		}

		if((pKsd_t->modeflag & MODE_READING)==0)
		{
			if(pDph_t->allofeats[nphon]& FSBOUND)
			{
				if( nphon ) 
				{
					if( (phone_feature( pDph_t, pDph_t->allophons[nphon+1]) & FSYLL) &&
						((pDph_t->allofeats[nphon+1] & FSBOUND) != FSBOUND))
					{
						pDph_t->allodurs[nphon] -= 	cons_dur;

						if (pDph_t->allodurs[nphon] <= 5)
							pDph_t->allodurs[nphon] = 5;
						cons_dur =0; //adjusmnet done zero cons_duration
					}
					else if((pDph_t->allofeats[nphon] & FSBOUND) == FSBOUND)
					{
						for (endcnt = nphon; endcnt >= 1; endcnt--)
						{ 
							if(endcnt < 1) //protection code
								break;
							//back up to fins first syl
							if(phone_feature( pDph_t ,pDph_t->allophons[endcnt]) & FSYLL)
							{
								if(cons_dur == 0)
									//	must have a cv with a place holder cons
									pDph_t->allodurs[endcnt] = pDph_t->allodurs[endcnt]>>1;
								else
									pDph_t->allodurs[endcnt] -= 	cons_dur;

								if (pDph_t->allodurs[endcnt] <= 5)
									pDph_t->allodurs[endcnt] = 5;
								cons_dur =0; //adjusmnet done zero cons_duration
								break;
							}
						}
					}
				}
			}
		}

		if (NSAMP_FRAME == 128)
			pDphsettar->durxx = (pDphsettar->durxx >> 1);	/* Save in array for phonetic comp */

		pDph_t->longcumdur += (pDphsettar->durxx * NSAMP_FRAME);	/* Cum dur in waveform samples     */
	
	}	// main loop
}