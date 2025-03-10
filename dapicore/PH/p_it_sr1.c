/* 
 ***********************************************************************
 *
 *                           Copyright �
 *    Copyright � 2000 Force Computer, Inc., a Solectron company. All rights reserved.
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
 *    File Name:    p_it_sr1.c
 *    Author:       Matthew Schnee
 *    Creation Date:05-Jun-1996
 *
 *    Functionality:
 *		Spanish code from sphsort.c
 *
 ***********************************************************************
 *    Revision History:
 *
 * Rev  Who     Date            Description
 * ---  -----   -----------     --------------------------------------------
 * 001  SIK		07/08/1996  	Cleaning up and maintenance
 * 002	MGS		06/17/1998		phedit2 changes
 * 003  EAB		07/09/1998		Tuning Spanish with Juan
 * 004  EAB		07/20/1998      Copied from p_it_sr1.c after merge synchronization
 * 005  EAB		09/11/1998		I can't make anysense of old BH code---modififed
 * 006  EAB		09/29/1998 		Removed moronic rule.....
 * 007  ETT     11/25/1998      fixed error comment that linux complains about...
 * 008  MGS		04/13/2000		Changes for integrated phoneme set 
 * 009  EAB		06/28/2000		Unified Phoneme Set Changes
 * 010  CAB		10/18/2000		Changed copyright info and formatted comment section
 */
#include "dectalkf.h"
#include "ph_def.h"


/* 
 * Bits for Spanish allophonics
 */
#define KG      2					   /* [k] -> [gh] context                */
#define VOWEL      8				   /* Vowel (stressed or unstressed)     */
#define   STRESSED   16				   /* Stressed vowel                     */



#ifndef PHEDIT2
#if IT_TOT_ALLOPHONES != (LAP_PH & PVALUE) + 1
//#error "allo_bits isn 't correct"
//HELP ME l_all_ph.h and p_all_ph.h need to be updated with the new phoneme list
#endif
#endif


static void it_spanish_allophonics (LPTTS_HANDLE_T phTTS)
/* 
 * Allophonic manipulation for Spanish.  May insert or delete 
 * symbols.  This is done here so the feature bit calculation 
 * is correct. 
 */
	{
		int                     next;  			/* Next real phoneme       */
		int                     curr;  			/* Current phoneme         */
		int                     n;
		int                     m;
		short                  *pp;	   			/* -> symbols[n]          */
		short                  *mp;	   			/* -> symbols[m]          */
		short                   feat;  			/* Next phoneme's features     */
		int           last_featb;		/* Last phoneme's featb[] entry     */
		int                   next_featb;		/* Next phoneme's featb[] entry     */
		short                   wbnext;			/* TRUE if boundary next     */
		short                   sbnext;			/* TRUE if syllable boundary */
		short                   truelast;		/* For 'y' test                    */
		short                   last = COMMA;	/* Clause start, see 'y' rule  */
		short                   localoff = 0;
		PDPH_T                  pDph_t=phTTS->pPHThreadData;
	   
		for (n = 0, pp = &pDph_t->symbols[0]; n < pDph_t->nsymbtot; n++, pp++)
		{
			curr = *pp;
			m = n + 1;
			mp = pp + 1;
			if ((m = n + 1) >= pDph_t->nsymbtot)
				next = GEN_SIL;
			else
				next = *mp;
			wbnext = FALSE;
			if (next >= MBOUND)
			{
				wbnext = TRUE;
				if (m + 1 < pDph_t->nsymbtot)
				{
					m++;
					mp++;
					next = *mp;
				}
			}
			sbnext = FALSE;
			if (next == SBOUND)
			{
				sbnext = TRUE;
				m++;
				mp++;
				next = *mp;
			}
			if (next == S1)
			{
				feat = (VOWEL | STRESSED);
				m++;
				mp++;
				next = *mp;
			}
			if (((next_featb = phone_feature( pDph_t,next)) & FVOWEL) IS_PLUS)
				feat = VOWEL;
			else if (next >= LAP_RR && next <= MAX_PHONES)
				feat = allo_bits[next - LAP_RR];
			else
			
			if ((curr & 0xFF) < 100 ) //ref 2000
			{
				last = (curr & 0xFF);
			last_featb = phone_feature( pDph_t,last);
			}
			/* 
			 * last    last true phoneme processed 
			 * curr    current phoneme 
			 * next    next phoneme (skipping over boundaries and stress) 
			 * feat
			 * features of next phoneme 
			 * sbnext  TRUE if start of a syllable 
			 */
		if(last != 0)//eab silence has wierd propoerties that should cause allophonic variation
			switch (curr)
			{
			case BLOCK_RULES:		   /* Applies to the word!         */
				return; // (1); // NAL warning removal





				/* eab 9/4/98 This code is better previous stuff was junk*/
				case LAP_B:
					if(last_featb & FSONOR && next_featb & FSONOR)
				{
					curr = LAP_BH;
				}



				break;
				/* FOund that Juan pronounces LL quite different at the begiining 
				and intervocalic eab 8/5/98
				n==1 becuause first wb not marked*/
			case LAP_LL:
				if (truelast == WBOUND || n == 1)
					break;
				else
				{
					curr = LAP_Y;
					break;
				}

			case LAP_D:

				/* 
				 *  OUT: 23-Apr-86 
				 *   D -> [th] / ... (#) {p t c k q ch f s z j} 
				 *   || [d]  / {unvoiced} ...           added 2-Feb-86 
				 *   || [d]  / {nasal, l, ll, clstart} (#) ... 
				 *   || [dh] 
				 * NEW: 
				 *   D -> [d]  /[#, l, or nasal] ... 
				 *   || [dh] 
				 */
#if 0
				if ((feat & LATIN) != 0)
					curr = LAP_TH;
				else if (((last_featb & (FNASAL | FSONCON)) != 0)
						 || ((last_featb & FVOICD) IS_MINUS)
						 || (last == COMMA))
					;
				else
				{
					curr = LAP_DH;
				}
#else

				if (((last_featb & FNASAL) IS_PLUS)
					|| (last == LAP_L)
					|| (last == COMMA))
					;
				else
				{
					curr = LAP_DH;
				}
#endif
				break;

#ifdef LAP_V
#endif

			case LAP_G:
				/* 
				 * OUT: 23-Apr-86 
				 * G -> [j] / ... (#) {p t c k q ch f s z j} 
				 *   || [g] / {unvoiced cons}  (#) ... (Added 2-Feb-86) 
				 *   || [g] / {nasal, clstart} (#) ... 
				 *   || [gh] 
				 * NEW: 
				 * G -> [g]  / {# or nasal} ... 
				 *   || [gh] 
				 */
#if 0
				if ((feat & LATIN) != 0)
					curr = LAP_J;
				else if (((last_featb & FNASAL) IS_PLUS)
						 || ((last_featb & FVOICD) IS_MINUS)
						 || last == COMMA)
					;
				else
				{
					curr = LAP_GH;
				}
#else

				if (((last_featb & FNASAL) IS_PLUS)
					|| last == COMMA)
					curr = LAP_G;
				else
				{
					curr = LAP_GH;
				}

#endif
				break;

#if 0
			case LAP_K:
				/* 
				 * OUT: 23-Apr-86 
				 * NOTE: changed KG test to exclude non-voiced seg's and word-final 
				 * Changed to keep K post-vocalically. 
				 * K -> [gh] / ... { #, p, t, c, b, d, m, n, ch, f, z } 
				 */
#if 1
				if (!sbnext
					&& (feat & KG) != 0
					&& (next_featb & FVOICD) IS_PLUS)
					curr = LAP_GH;
#else
				if (wbnext || (feat & KG) != 0)
					curr = LAP_GH;
#endif
				break;
#endif

#if 0
				/* 
				 * The nasal assimilation rule is mostly in phsettar.c  8-May-86 
				 */
			case LAP_N:
				/* 
				 * NOTE: needs to be put back in (possibly in phsettar.c) 
				 * N -> [m]  / ... (#) {p, b, v, m} 
				 * NOTE: Spanish informants deny n->m  
				 * NOTE: Spanish informants deny '# p' 
				 *   || [mx] / ... (#) {f} 
				 *   || [nx] / ... (#) {k g j} 
				 */
				switch (next)
				{
#if 0
				case LAP_P:
#if 1
					if (wbnext)
						break;
#endif
				case LAP_B:
#ifdef LAP_V
				case LAP_V:
#endif
				case LAP_M:
					curr = LAP_M;
					break;
#endif

				case LAP_F:
					curr = LAP_M;
					break;
				case LAP_K:
				case LAP_G:
				case LAP_J:
					curr = LAP_NX;
					break;
				}
				break;
#endif

			case LAP_N:
				/* 
				 * 12-May-86 
				 * N -> [m]  / ... (#) [m]      "inmovil>immovil" 
				 */
				if (next == LAP_M)
					curr = LAP_M;
				break;

			case LAP_Y:
				/* 
				 * Y -> [yh]  / {#, nasal, lateral} (#) ...      5-May-86 
				 *   || [y] 
				 * The following rules are for the word 'y' * * 'y' -> [i]
				 * / [-vowel] ... [-vowel] 
				 *     || [yx] 
				 * Note that [yx] will dipthongize by rules in phalloph.c 
				 */
				if (truelast >= MBOUND && wbnext)
				{					   /* the word 'y' */
					if ((last_featb & FVOWEL) IS_MINUS
						&& (next_featb & FVOWEL) IS_MINUS)
						curr = LAP_I;	   /* Stressed?               */
					else
					{
						curr = LAP_YX;   /* Dipthongizes                */
					}
				}
				//ref 2003
#ifdef NEEDFIX
				else if (((last_featb & (FNASAL | FSONCON)) != 0)
						 || (last == COMMA))
				{

					curr = LAP_YH;
				}
#endif
				break;

			default:
				break;				   /* Do nothing                   */
			}
			*pp = curr;
			if (curr < SBOUND)
				last = curr;
			truelast = curr;		   /* Might be a boundary              */
		}
	}
 

 
/*
 *      Function Name: getsyllclass()      
 *
 *  	Description: Return FOPEN_SYL if the syllable is open, else 0.
 *
 *      Arguments: PDPH_T pDph_t,
 *				   short curr
 *
 *      Return Value: int
 *
 *      Comments:
 *
 */

static int it_getsyllclass (PDPH_T pDph_t,short curr)
	   /* Follows nucleus vowel */
{
	int                     phone;

	/* 
	 * Note that next will exceed TOT_ALLOPHONES if a syllable-boundary,
	 * word-boundary, or stress mark follows.
	 * This implies that dipthongs (V1 V2) build closed syllables.
	 */
	do
	{
		phone = get_symbol(pDph_t,curr++);   /* Get phoneme           */
		if (phone >= MAX_PHONES)   /* Boundary or str. vow    */
			return (FOPEN_SYL);		   /* is open sylable    */
	}
	while ((phone_feature( pDph_t,phone) & (FVOWEL | FSEMIV)) IS_PLUS);
	switch (phone)
	{								   /* V N (-) L is open */
	case LAP_N:
	case LAP_S:
	case LAP_RR:
	case LAP_T:
		if (get_symbol(pDph_t,curr) == SBOUND)
		{
			curr++;
		}
		if (get_symbol(pDph_t,curr) == LAP_L)
		{
			return (FOPEN_SYL);
		}
	}
	return (0);						   /* Closed syllable    */
}

 


