/* 
 ***********************************************************************
 *
 *                           Copyright ©
 *    Copyright © 2000 Force Computer, Inc., a Solectron company. All rights reserved.
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
 *    File Name:    p_la_sr1.c
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
 * 004  EAB		07/20/1998      Copied from p_la_sr1.c after merge synchronization
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
#if LA_TOT_ALLOPHONES != (LAP_PH & PVALUE) + 1
#error "allo_bits isn 't correct"
#endif
#endif

extern int get_symbol (PDPH_T pDph_t,short i);

/* 
 * Allophonic manipulation for Spanish.  May insert or delete 
 * symbols.  This is done here so the feature bit calculation 
 * is correct. 
 */
void la_spanish_allophonics (LPTTS_HANDLE_T phTTS)
{
	int                     next;  			/* Next real phoneme       */
	int                     curr;  			/* Current phoneme         */
	int                     n;
	int                     m;
	short                  *pp;	   			/* -> symbols[n]          */
	short                  *mp;	   			/* -> symbols[m]          */
	short                   feat;  			/* Next phoneme's features     */
	unsigned short          last_featb;		/* Last phoneme's featb[] entry     */
	short                   next_featb;		/* Next phoneme's featb[] entry     */
	short                   wbnext;			/* TRUE if boundary next     */
	short                   sbnext;			/* TRUE if syllable boundary */
	short        
		nextphone=0,		// next real phoneme
		truelast=0,			// last real phoneme
		plainlast=0;		// last phoneme symbol
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
		if ((next & PVALUE) >= MBOUND)
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
		if ((next & PVALUE) == SBOUND)
		{
			sbnext = TRUE;
			m++;
			mp++;
			next = *mp;
		}

		if((next & PVALUE) == S1 ||
			(next & PVALUE) == S2 )
		{
			feat = (VOWEL | STRESSED);
			m++;
			mp++;
			next = *mp;
		}

		// Find the next phoneme
		if( (next & 0xff) >= 100 )
		{
			while( (*mp & 0xff) >= 100 &&
				m < pDph_t->nsymbtot )
			{
				m++;
				mp++;
			}
			if( m < pDph_t->nsymbtot )
				nextphone = *mp;
			else
				nextphone = GEN_SIL;
		}
		else
			nextphone = next;

		if( (next & 0xff) < 100)
		{
			if (((next_featb = phone_feature( pDph_t,next)) & FVOWEL) IS_PLUS)
				feat = VOWEL;
			else if (next >= LAP_RR && next <= MAX_PHONES)
				feat = allo_bits[next - LAP_RR];
		}

		if (truelast > 0)
		{
			if ((truelast & 0xFF) < 100 )
			{
				last_featb = phone_feature( pDph_t,truelast);
			}
		}
		else
		{
			last_featb = phone_feature( pDph_t,GEN_SIL);
			truelast = GEN_SIL;
		}


		/* 
		* last    last true phoneme processed 
		* curr    current phoneme 
		* next    next phoneme (skipping over boundaries and stress) 
		* feat	   features of next phoneme 
		* sbnext  TRUE if start of a syllable 
		*/

		switch (curr)
		{
		case BLOCK_RULES:		   /* Applies to the word!         */
			for ( ; n < pDph_t->nsymbtot && pDph_t->symbols[n+1] != WBOUND ; n++, pp++)
				;

			continue;  // NAL warning removal

		case LAP_V:
			if( (last_featb & FNASAL) ||	// Stay /v/ if preceded by a nasal
				truelast == GEN_SIL )		// Stay /v/ if phrase initial
			{
				curr = LAP_V; //stays the same
			}
			else
			{
				curr = LAP_BH;
			}
			break;

		case LAP_B:
			/* 
			* OUT 23-Apr-86: 
			* B, V -> [th] / ... (#) {p t c k q ch f s z j} 
			*      || [b]  / {lateral} (#) ...     added ?? 
			*      || [b]  / {unvoiced} (#) ...    added 2-Feb-86 
			*      || [b]  / ... {unvoiced}        added 2-Feb-86 
			*      || [b]  / {nasal or clstart} (#) ... 
			*      || [bh] 
			* NEW: 
			* B,V -> [b] / [# or nasal] (#) ...
			*      || [bh] 
			*/
			if( last_featb & FNASAL || 
				truelast == GEN_SIL )
			{
				curr = LAP_B; //stays the same
			}
			else
			{
				curr = LAP_BH;
			}
			break;

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
			if( truelast == GEN_SIL || 
				truelast == LAP_L || 
				truelast == LAP_LL || 
				last_featb & FNASAL ||
				nextphone == GEN_SIL )		// Don't approximate (dh) if phrase final
			{
				curr = LAP_D;
				break;
			}
			if ((*mp & PVALUE) > WBOUND)
				//next == GEN_SIL) skip over wboung to gen_sil
			{
				if ((truelast != LAP_N && truelast != LAP_L))
					curr = LAP_DH;
			}
			else if ((last_featb & FNASAL) IS_MINUS
				|| (last_featb & FSYLL) IS_PLUS
				|| (next_featb & FSYLL) IS_PLUS)
			{
				curr = LAP_DH;
			}
			break;

		case LAP_G:
			// Rule: g -> gh  if
			// Left context 
			//		IS:			Sonorant or Word initial 
			//		but NOT:	phrase initial, N, NX
			// Right context
			//		IS:			Vowel or consonant
			//		but NOT:	I, E
			//
			// Examples of g -> gh:	
			//		el gato, la gata, lago, algo, agnóstico, siguiente, 
			//		aburguloesado, aguerrido, vulgar
			// Examples of g !-> gh: 
			//		gato, un gato, mango
			//
			// Rules from 4.64
			if( (last_featb & FNASAL) ||
				(last_featb & FVOICD) IS_MINUS || 
				(next_featb & FVOICD) IS_MINUS || 
				(plainlast & PVALUE) > WBOUND )
			{
				curr = LAP_G;		 //stays the same
			}
			else
			{
				curr = LAP_GH;
			}
			break;


			/* 
			* The nasal assimilation rule is mostly in phsettar.c  8-May-86 
			*/
		case LAP_N:
			switch (nextphone)
			{
				// N -> M if next phoneme is /P,B,V,M,F/
			case LAP_P:			
			case LAP_B:
			case LAP_V:
			case LAP_M:			// Ex. inmovil -> immovil
			case LAP_F:
				curr = LAP_M;
				break;

				// N -> NX if next phoneme is K,G,J
			case LAP_K:			
			case LAP_G:
			case LAP_J:
				curr = LAP_NX;
				break;
			}
			break;

		case LAP_S:
			if( (phone_feature(pDph_t, nextphone) & FVOICD) IS_PLUS &&
				(phone_feature(pDph_t, nextphone) & FCONSON) IS_PLUS )
			{
				curr = LAP_Z;
			}
			break;

		case LAP_TH:
			curr = LAP_S;
			break;

		case LAP_I:
			// Rules for unstressed spanish /i/
			if( plainlast != S1 )
			{
				if( wbnext )	// final position
				{
					// VOWEL+i+WBOUND -> goes to /yx/ (ex. soy, muy, ley, guay)
					// CONSONANT+i+WBOUND -> /i/ (ex. casi)
					if( (phone_feature(pDph_t,truelast) & FVOWEL) IS_PLUS )
					{
						curr = LAP_YX;
					}
				}

				// If next to a vowel and U did not precede then change to YX
				else if( truelast != LAP_U &&				// ex. bien, reino, viuda
					truelast != LAP_NH &&				// niño - n i nh i o
					truelast != LAP_N &&				//  niño - n i n i o
					((phone_feature(pDph_t,truelast) & FVOWEL) IS_PLUS ||
					(phone_feature(pDph_t,nextphone) & FVOWEL) IS_PLUS) )
				{
					curr = LAP_YX;
				}
			}
			break;

		case LAP_Y:
				if( wbnext )								// /Y/ in word final position -> /YX/
				{
					curr = LAP_YX;							// ex. hay, hoy, estoy
				}
				else if( (plainlast&PVALUE) >= MBOUND &&	// word initial
						 wbnext)							// word final
				{
					// [-vowel] Y [-vowel] -> I
					if( (last_featb & FVOWEL) IS_MINUS && 
						(next_featb & FVOWEL) IS_MINUS)
					{
						curr = LAP_I;
					}
					else
					{
						curr = LAP_YX;						// Dipthongizes
					}
				}
				else if( (plainlast&PVALUE) >= MBOUND &&	// word initial
						 truelast != GEN_SIL)				// not phrase initial
				{
					curr = LAP_YX;							// ex. "la hierba" y -> yx
				}
				break;

		case LAP_U:
			// Rules for unstressed spanish /U/
			if( plainlast != S1 )
			{
				// ex. hueso in phrase initial position
				if( truelast == GEN_SIL &&
					(phone_feature(pDph_t,nextphone) & FVOWEL) IS_PLUS )
				{
					curr = LAP_W;
				}
				// ex. cuanto, bueno, cuidado
				else if( truelast != LAP_I &&
						 ((phone_feature(pDph_t,nextphone) & FVOWEL) IS_PLUS ||
						  (phone_feature(pDph_t,truelast) & FVOWEL) IS_PLUS) )
				{
					curr = LAP_WX;
				}
			}
			break;

		default:
			break;				   /* Do nothing                   */
		}
		*pp = curr;
		plainlast = curr;
		if ((curr & PVALUE)< 100)
			truelast = curr;
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

int la_getsyllclass (PDPH_T pDph_t,short curr)
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
		if( (phone & PVALUE) >= MAX_PHONES)   /* Boundary or str. vow    */
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

 


