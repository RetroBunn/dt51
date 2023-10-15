/************************************************
	ILE_STZC.C	updated at 19th February 1991
	Connection relations between elements
 ************************************************/

#define		EXT		extern

#if defined(O_DEBUG)||defined(DEBUG_STZ)
#include	<stdio.h>
#endif

#include	"onsei.h"
#include	"ile_bunh.h"
#include	"ile_dbgh.h"
#include	"ile_fddh.h"
#include	"ile_kkhh.h"
#include	"ile_nydh.h"
#include	"ile_stzh.h"
#include	"ile_func.h"

/*========== StzfElmKind(s,kind) ===========================================
	Function: Set the word type of the preceding element (s = Stz_PE) and the current element (s = Stz_CE) to kind, and 
		initialize all except the learning information.
  ==========================================================================*/
void StzfElmKind(STZ_STRUCT *s, BYTE kind)
{
	BYTE work;

	work=s->stz_mru;		/* Store the learning information. */
	FOLLOW_INIT(s);			/* Clear the connection information of the current element. */
	s->stz_kind=kind; 		/* Specify the word type. */
	s->stz_mru=work;		/* Return the learning information. */
}


/*========== FOLLOW_INIT(di) ==================================
	Function: Initialize the information related to the connection relation between the preceding element and the current element.
  =========================================StzfXxgShokikasuru==*/
void FOLLOW_INIT(STZ_STRUCT *di)
{
	register integer_16 i;

	/* Word type, logical add of the control information, flag 2, connection status, learning information, and number information */
	di->stz_kind=
	di->stz_ctl=
	di->stz_f2=
	di->stz_stz=
	di->stz_mru=
	di->stz_dman=
	di->stz_dexp='\0';
	/* Number of grammar codes and number of beck-end numbers */
	di->stz_ngrcd=di->stz_nbno=0;
	/* Grammar code, forward vector number, back-end number */
	for(i=MAX_GRCD;i--;)
	{
		di->stz_grcd[i] = di->stz_pno[i] = di->stz_bno[i] = '\0';
	}
}


/*========== StzfElmBackward() =========================
	Function: Move the information related to the connection relations of the 
		preceding element to the current element.
  =====================================StzfChmGoModosu==*/
void StzfElmBackward() {
	/*	Shift the information related to connection of the preceding element to 
		the current element, and initialize the information related to the 
		connection of the preceding element. */
	memcpy(&Stz_CE,&Stz_PE,sizeof(STZ_STRUCT));
	FOLLOW_INIT(&Stz_PE);
}


/*========== StzfElmForward() ========================
	Function: Move the information related to the connection relations of the 
		current element to the preceding element.
  =================================StzfChmGoSusumeru==*/
void StzfElmForward() {
	/* Shift the information related to connection of the current element to the 
		preceding element, and initialize the information related to the connection 
		of the current word. */
	memcpy(&Stz_PE,&Stz_CE,sizeof(STZ_STRUCT));
	FOLLOW_INIT(&Stz_CE);
}


/*========== StzfGrcdStore(code) ==========
	Function: Stores the grammar code of the current element.
  =========================================*/
void StzfGrcdStore(code) BYTE code; {
	if(Stz_CE.stz_ngrcd<MAX_GRCD){
		Stz_CE.stz_grcd[Stz_CE.stz_ngrcd]=code;
		Stz_CE.stz_ngrcd++;
	}
}


/*========== StzfGrcdOR(code) ==========================================
	Function: From all the grammar codes, collect the back-end number, 
		forward vector number, and control information, and 
		store them in an appropriate place.
		Obtain OR of the control information and store it.
  ======================================================================*/
void StzfGrcdOR() {
	register BYTE *si;
	register integer_16 cx;
	integer_16 cond;
	BYTE ctl,grcd;
/********************************************************************************
 *																				*
 *	ÅwWhen the current element has the Chinese-origin word suffix but the preceding element is not the Chinese origin word,	*
 *	ignore the grammar code that is connected before the suffix.Perform the connection check only with matrix, and	*
 *	ignore the Chinese-origin word connection check.Åx														*
 *																				*
 *	(Example) "é´èëÇÃêÊê∂" is correct."é´èëêÊê∂" is incorrect.							*
 *		"ìåãûÇÃêÊê∂" is correct."ìåãûêÊê∂" is incorrect.							*
 *																				*
 *	The upper and lower limits of the grammar code connected before the suffix is 	*
 *	written on the 149th and 150th bytes in the communication area.																*
 *																				*
 *	(Explanation)																	*
 *	There are self-sustainable and not self-sustainable Chinese-origin suffixes.  When the preceding element is 			*
 *	a Chinese-origin word, it can be connected to the word of which part of speech is  semantically connectable in both ways.				*
 *	However, when the preceding element is not a Chinese-origin word, it can be connected to only the self-sustainable Chinese-origin suffix. 	*
 *	and the possibility is checked with its matrix only.To avoid errors such as "é´èëêÊê∂,"	*
 *	it is required to remove the check of the Chinese-origin word connection.		*
 *																				*
 *	(Example) Self-sustainable ------ êÊê∂ÅAã≥éˆ										*
 *		Not self-sustainable ------ é~ÇË											*
 *																				*
 ********************************************************************************/
	/*
	 * When it is a Chinese-origin word suffix and its preceding element is not a Chinese origin word, ignore the grammar code in the certain range.
	 * When it is the top of the sentence, do not ignore.
	 */
	cond=(Stz_CE.stz_f2 & BITFLG2_SUF) && pe_is_kango==0;
	if(ceptr==0){ cond=0; }
	/*
	 * From all the grammar codes, collect the back-end number, forward vector number, and control information, and 
	 * store them in an appropriate place.
	 * Obtain OR of the control information and store it.
	 */
	for(cx=Stz_CE.stz_ngrcd;cx--;){
		/* Fetch the grammar code.*/
		grcd=Stz_CE.stz_grcd[cx];
		if(cond){
			if(grcd>=Fdd_Header.Fdd_GrcdSufLL && grcd<=Fdd_Header.Fdd_GrcdSufUL){
				goto Next;
			}
		}

		/* Look up the grammar code table. */
		si=FddHDR+Fdd_Header.Fdd_GrcdTblOfs;

		/* Move the control information. */
		ctl=((char(*)[4])si)[grcd-1][GRCDTBL_CTL];
		Stz_CE.stz_ctl|=ctl;

		/* When the current element is in Chinese-origin word connection of the preceding element, add the Chinese-origin word to the connection status instruction. */
		if(ctl & BITCTL_PKANGO){ Stz_CE.stz_stz|=BITSTZ_KANGO; }
		/*
		 *	The Chinese-origin word flag specified here is
		 *	used for checking the existence of the Chinese-origin word connection with the preceding word.
		 *	When the connection with the preceding word is confirmed,
		 *	the meaning of the flag is changed so that it indicates the Chinese-origin word connectability with the succeeding word.
		 */

		/* Move the forward vector number. */
		Stz_CE.stz_pno[cx]=((char(*)[4])si)[grcd-1][GRCDTBL_PNO];
		/* Move the back-end number. */
		StzfBnoAdd(&Stz_CE,((char(*)[4])si)[grcd-1][GRCDTBL_BNO]);

		Next:;
	}
}


/*========== StzfGrcdAdd(grcd) ===============
	Function: Add the connection relation code of the current element.
  ============================================*/
void StzfGrcdAdd(BYTE grcd)
{
	register BYTE *si;
	register integer_16 ax;
	BYTE ctl;
	
	/* Specify the grammar code. */
	ax=Stz_CE.stz_grcd[Stz_CE.stz_ngrcd]=grcd;
	si=FddHDR+Fdd_Header.Fdd_GrcdTblOfs;
	/* Obtain OR of the control information. */
	ctl=((char(*)[4])si)[ax-1][GRCDTBL_CTL];
	Stz_CE.stz_ctl|=ctl;
	/* When the current element is in Chinese-origin word connection of the preceding element, add the Chinese-origin word to the connection status instruction. */
	if(ctl & BITCTL_PKANGO){ Stz_CE.stz_stz|=BITSTZ_KANGO; }
	
	/*
	* The Chinese-origin word flag that is specified here is used for checking the existence of the Chinese-origin word connection with the preceding word.
	* When the connection relation with the preceding element is confirmed, the meaning of the flag is changed so that 
	* the Chinese-origin word connectability with the succeeding word.
	*/
	Stz_CE.stz_pno[Stz_CE.stz_ngrcd]=((char(*)[4])si)[ax-1][GRCDTBL_PNO];	/* Move the forward vector number. */
	StzfBnoAdd(&Stz_CE,((char(*)[4])si)[ax-1][GRCDTBL_BNO]);
	/* Move the back-end number. */
	Stz_CE.stz_ngrcd++;						/* Increase the number of grammar codes. */
}


/*========== StzfBnoAdd(elm,bno) =============
	Function: Add bno to the back-end number of the current element.
  ============================================*/
void StzfBnoAdd(STZ_STRUCT *elm, BYTE bno)
{
	register integer_16 n;
	integer_16 next;
 
	n=next=elm->stz_nbno;			/* Fetch the number of the back-end numbers. */
	/* Check whether there are the same back-end numbers. */
	do{
		if(--n<0){				/* Return one of the watching back-end number. */
									/* Stop when there is no back-end number. */
									/* If all the back-end numbers are different,  */
			elm->stz_bno[next]=bno;	/* Move the back-end number. */
			elm->stz_nbno++;		/* Increase the number of the back-end numbers. */
			return;
		}
	}while(bno!=(BYTE)elm->stz_bno[n]);	/* When the back-end number is different, repeat the processing. */
}


/*========== FOLLOW() =================================================
	Function:	Check whether or not there is the connection relation between the 
				current element and the preceding element.
	Value:	1 = There is the connection relation.  
			0 = There is no connection relation.
  =========================================================StzfStzAri==*/
BOOL FOLLOW(void) 
{
	register integer_16 cx;
	BYTE bno;
#if defined(DEBUG_STZ)
	if(debug[4]){ DEBUG_PN("<FOLLOW>"); DEBUG_STZ(); }
#endif
	/*
	 *	At the last element, 
	 *	when it can be the last element, connect it.  If it cannot be the last element, do not connect it.
	 *	Because t he top element can also be the last element, be careful about checking.
	 */
	if((ceptr+celen)==n_inert){
		if((Stz_CE.stz_ctl & BITCTL_LAST)==0){ goto FOLLOW_997; }
	}
	/*
	 * At the top element, 
	 * when it can be the top element, connect it.  If it cannot be the top element, do not connect it.
	 */
	if(ceptr==0){
		if(Stz_CE.stz_ctl & BITCTL_FIRST){
			goto FOLLOW_510;
		}else{
			goto FOLLOW_997;
		}
	}
	/*
	 * The border between the preceding element and the succeeding element is the position where the Tan-kanji dictionary search is started, 
	 * the connection relation is not checked.
	 *   At the first conversion, of course, the connection relation must be checked.
	 * However, whether or not it can be the top element must be checked.
	 *
	 *	(Example) Between "Ç©ÇÁ" and "ÇP" in "ÇQÅFëΩÇ©ÇÁÇPÅFëΩ"
	 *		Because "ÇP" is not a Tan-kanji, a special processing is required.
	 */
	if(conv_mode!=CONV_FIRST){
		if(ceptr==max_ceptr){ goto FOLLOW_500; }
	}

	/*=============== The top element can never go below this.===============*/

	/*
	 *	When the current element is a Tan-kanji, if the preceding element is a Tan-kanji, connect them.
	 *	In other cases, connect it except it is a syllabic nasal, long vowel, double consonant, or "Ç".-- Lie --
	 *
	 * About "Ç”Ç≥Ç™Ç¡Çƒ," up to "Ç”Ç≥Ç™" can be normally converted, however, "Ç¡" and subsequent cannot be converted.
	 *	As a result, the Tan-kanji that cannot be the top also needs to be connected.
	 */
	/*
	 * Even when the current element is a Tan-kanji, if it is a symbol, check its connectability.
	 * If "Ç©ÅA" appears for "èëÅA", it is a problem.ÅiÇXÇOÅDÇSÅDÇRÇOÅj
	 */
	if(Stz_CE.stz_kind==DICKIND_T){
		switch(inert_kind[ceptr] & 0xF0){
		case CHRKIND_Other1:
		case CHRKIND_Other2:
			break;				/* Check the matrix for symbols.*/
		default:
			goto FOLLOW_500;	/* OK except symbols.*/
		}
	}

	/* Processing for when both the preceding element and the current element are numbers*/
	if(Stz_PE.stz_kind==DICKIND_D && Stz_CE.stz_kind==DICKIND_D){
		goto FOLLOW_500;
	}

	/* For example for "ÇPÇOÇPÇbÇa" or "ÇoÇRÇb," the connection of a number and an alphabetic character is allowed.*/
	if(Stz_PE.stz_kind==DICKIND_D && Stz_CE.stz_kind==DICKIND_E){
		/* When the current element is an alphabetic character, connect it.*/
		if(inert_kind[ceptr]==CHRKIND_Alpha){ goto FOLLOW_500; }
	}

	/*
	 * For example, "FM" or "ROM."
	 *	The connection of an uppercase alphabetic character and an alphabetic character with numeric attribute is not allowed.
	 *	The connection of a lowercase character is allowed.(aM byte)
	 */
	if(Stz_PE.stz_kind==DICKIND_E && Stz_CE.stz_kind==DICKIND_E){
		/* When the preceding element ends with an uppercase alphabetic character, 
		   and the current element starts with an alphabetic character, */
		if(inert_kind[ceptr-1]==CHRKIND_Alpha
		&& inert_kind[ceptr]==CHRKIND_Alpha
		&& inert[ceptr*2-1]<0x60){
			/* the current element is not connected if it has a back-end number.*/
			if(chk_value(Fdd_Header.Fdd_GrcdDigit,
						 Stz_CE.stz_grcd,Stz_CE.stz_ngrcd)){
				goto FOLLOW_997;
			}
		}
	}

	/* When the preceding element is a prefix, do not connect it to a prefix or suffix.*/
	if(StzfAttrAri(Stz_PE,stz_ctl,BITCTL_PREF)){
		if(StzfAttrAri(Stz_CE,stz_ctl,BITCTL_PREF)
		|| StzfAttrAri(Stz_CE,stz_ctl,BITCTL_SUF)){ goto FOLLOW_997; }
	}else{ 
		if(StzfAttrAri(Stz_PE,stz_ctl,BITCTL_SUF)){
			/* When the preceding element is a suffix, do not connect it to a suffix.*/
			if(StzfAttrAri(Stz_CE,stz_ctl,BITCTL_SUF)){ goto FOLLOW_997; }
		}
	}

	/* When it is the Chinese-origin word suffix, checking of the Chinese-origin word connection is not checked.*/
	if(StzfAttrAri(Stz_CE,stz_f2,BITFLG2_SUF)){ goto FOLLOW_100; }
	/*
	 * When it is not the Chinese-origin word suffix, checking of the Chinese-origin word connection is not checked.
	 *	(Example) "ìåãûàÍ" is correct."ìcíÜàÍ" is incorrect.
	 */
	if(StzfAttrAri(Stz_CE,stz_ctl,BITCTL_SUF)){ goto FOLLOW_100; }

	if((pe_is_kango==0)||(ce_is_kango==0)){ goto FOLLOW_100; }

	/**************************************
	 * When both the current element and the preceding element are Chinese-origin words *
	 **************************************/

	/* When the preceding element is îÒ, ïs, ñ≥, or ñ¢(Chinese-origin word) and the current element is a Chinese-origin word, 
	   Add an adjective verb to the back-end number.*/
	if(chk_value(Fdd_Header.Fdd_BnoHifu, Stz_PE.stz_bno, Stz_PE.stz_nbno)){
		StzfGrcdAdd(Fdd_Header.Fdd_GrcdAdjv);
	}
	goto FOLLOW_500;

	/**********************************************************
	 * When either or both the current element and the preceding element are not Chinese-origin words, *
	 **********************************************************/
FOLLOW_100:
	 /* When the preceding element is a prefix "Ç®"*/
	if(chk_value(Fdd_Header.Fdd_BnoPrefo,
				 Stz_PE.stz_bno,Stz_PE.stz_nbno)){
		/* When the current element is a 5-step verb stem, specify a 5-step verb that follows "Ç®."*/
		if(chk_limits(Fdd_Header.Fdd_Bno5danLL,Fdd_Header.Fdd_Bno5danUL,
					  Stz_CE.stz_bno,Stz_CE.stz_nbno)){
			Stz_CE.stz_stz |= BITSTZ_PREFO5V;
		}else{
			/* when the current element is a 1-step verbal noun-form stem, add SAHEN to the current element.*/
			if(chk_value(Fdd_Header.Fdd_Bno1danMei,
						 Stz_CE.stz_bno,Stz_CE.stz_nbno)){
				StzfBnoAdd(&Stz_CE,Fdd_Header.Fdd_BnoSahen);
			}
		}
	}else{
		/*
		 * When the current element is a 5-step verb stem that follows "Ç®," and the current element has the conjunctive ending, 
		 * Add the SAHEN verb stem to the current element.
		 */
		if(StzfAttrAri(Stz_PE,stz_stz,BITSTZ_PREFO5V) &&
		   chk_value(Fdd_Header.Fdd_Bno5danYou,
					 Stz_CE.stz_bno,Stz_CE.stz_nbno)){
			StzfBnoAdd(&Stz_CE,Fdd_Header.Fdd_BnoSahen);
		}
	}

	/* When the preceding element is an internal dictionary word and a current element adverb is added, */
	/* "Ç´" following "Ç¬" in "Å`Ç…Ç¬Ç´" can function as an adverb.(conjunctive ending) */
	if(Stz_PE.stz_kind==DICKIND_I){
		if(StzfAttrAri(Stz_PE,stz_f2,BITFLG2_NADV)){
			/*
			 * When the current word is an ending of the 5-step conjunctive verb form, add an adverb.
			 * When the current word is an ending of the 1-step conjunctive verb form, add an adverb.
			 * When the current word is an ending of the SAHEN conjunctive verb form, add an adverb.
			 */
			if(chk_value(Fdd_Header.Fdd_Bno5danYou,
						 Stz_CE.stz_bno,Stz_CE.stz_nbno)
			|| chk_value(Fdd_Header.Fdd_Bno1danMei,
						 Stz_CE.stz_bno,Stz_CE.stz_nbno)
			|| chk_value(Fdd_Header.Fdd_Bno1danYou,
						 Stz_CE.stz_bno,Stz_CE.stz_nbno)
			|| chk_value(Fdd_Header.Fdd_BnoSahenYou,
						 Stz_CE.stz_bno,Stz_CE.stz_nbno)){
				StzfBnoAdd(&Stz_CE,Fdd_Header.Fdd_BnoAdv);
			}
		}
	}

	/* Connection check with matrix*/
	if(BNO_VECP()==0){ goto FOLLOW_997; }

FOLLOW_500:
	/*
	 * When the preceding element is a prefix, prevent the current element from being a delimiter of the sentence.
	 * However, if the control information is damaged, it may be a problem in accent processing, so write it the connection information.
	 */
	if(StzfAttrAri(Stz_PE,stz_ctl,BITCTL_PREF)){
		Stz_CE.stz_stz |= BITSTZ_PREF;
	}
FOLLOW_510:

#if !defined(O_TALKONLY)
	/*
	 *	<<For the processing for fixing the watching sentence length>>
	 *   For the processing of next target, longer segment, or shorter segment, 
	 * specify the start positions of the watching sentence and the next sentence in advance, 
	 * and abandon the sentences that contradict with the specified positions.
	 *   Both the start position and the next start position are the same for the next target.
	 * For processing for the shorter or longer segment, obtain the next start position in advance.
	 */
	if(conv_mode==CONV_NEXT||conv_mode==CONV_LONG||conv_mode==CONV_SHORT){
		/*
		 * For numbers, if there is any contradiction of ceptr, celen, or fsptr, do not connect it.
		 * For the shorter segment processing, "ÇPÇOÇOÇPêl" can be shortened by one character but not by two character.
		 * Check whether or not celen or fsptr is overflowed.
		 */
		if(WS_CE_CHK()==0){ goto FOLLOW_997; }
		/*
		 * and the current element starts within the fixed position instruction, 
		 * and when the element can be the top, do not connect it.
		 */
		if(wsptr<ceptr && ceptr<fsptr){
			if(StzfAttrAri(Stz_CE,stz_ctl,BITCTL_FIRST)){
				if(StzfAttrNashi(Stz_CE,stz_stz,BITSTZ_PREF)){
					goto FOLLOW_997;
				}
			}
		}
		/*
		 * When the current element starts with the start or end of the fixed position instruction,
		 * and when the element cannot be the top, do not connect it.
		 */
		if(wsptr==ceptr||ceptr==fsptr){
			if(StzfAttrNashi(Stz_CE,stz_ctl,BITCTL_FIRST)){ goto FOLLOW_997; }
			if(StzfAttrAri(Stz_CE,stz_stz,BITSTZ_PREF)){ goto FOLLOW_997; }
		}
	}
#endif

	/* When the current element is in succeeding Chinese-origin word connection, connect the Chinese-origin word.*/
	if(StzfAttrAri(Stz_CE,stz_ctl,BITCTL_FKANGO)){ goto FOLLOW_720; }
	/* when the preceding element is not the prefix "ëÊ," remove the Chinese-origin word connection.*/
	if(chk_value(Fdd_Header.Fdd_GrcdDai,
				 Stz_PE.stz_bno,Stz_PE.stz_nbno)==0){
		goto FOLLOW_740;
	}
	/* When the current element is not a number, remove the Chinese-origin word connection.*/
	if(chk_value(Fdd_Header.Fdd_GrcdDigit,
				 Stz_CE.stz_grcd,Stz_CE.stz_ngrcd)==0){
		goto FOLLOW_740;
	}

FOLLOW_720:
	/* Add a Chinese-origin word to the connection.*/
	Stz_CE.stz_stz |= BITSTZ_KANGO; goto FOLLOW_900;
	/* In other cases, remove the Chinese-origin word connection.*/
FOLLOW_740:
	/* Delete the Chinese-origin word from the connection.*/
	Stz_CE.stz_stz &= ~BITSTZ_KANGO;
FOLLOW_900:
	/*
	 * The last "Å[" in "ÉRÉìÉsÉÖÅ[É^Å[" or "é©êg" in "ÇªÇÍé©êg"
	 * "Ç∑Ç◊Çƒ" in "Å`Ç∑Ç◊Çƒ"
	 * Note that "Ç∑Ç◊Çƒ" in "Å`Ç™Ç∑Ç◊Çƒ" is excluded.(89/1/20)
	 * Use the control information and back-end number of the previous word for this element.
	 */
	if(StzfAttrAri(Stz_CE,stz_f2,BITFLG2_SELF)){
		/*
		 * When there is no preceding element, exclude it.
		 * When the suffix cannot be the top, copy it.
		 */
		if(ceptr==0){ goto FOLLOW_990; }
		if(Stz_PE.stz_kind==DICKIND_T){
			switch(inert_kind[ceptr-1] & 0xF0){
			case CHRKIND_Other1:
			case CHRKIND_Other2:
				goto FOLLOW_990;
			}
		}
		if((Stz_CE.stz_ctl & BITCTL_FIRST)==0){ goto FOLLOW_910; }
		/*
		 * when the preceding element is an indeclinable, use the previous one.
		 */
		for(cx=0;cx<Stz_PE.stz_nbno;++cx){
			if(bno=Stz_PE.stz_bno[cx]){
				if(FddHDR[Fdd_Header.Fdd_BnoTblOfs+bno-1] & BITBNO_Taigen){
					goto FOLLOW_910;
				}
			}
		}
	}
	goto FOLLOW_990;
FOLLOW_910:
	Stz_CE.stz_ctl|=Stz_PE.stz_ctl & ~BITCTL_FIRST;	/* without 1st */
	Stz_CE.stz_stz=Stz_PE.stz_stz;
	Stz_CE.stz_f2|=Stz_PE.stz_f2 & 0x08;	/* Chinese-origin word bit */
	cx=(Stz_CE.stz_nbno=Stz_PE.stz_nbno);
	for(;cx--;){
		Stz_CE.stz_bno[cx]=Stz_PE.stz_bno[cx];
	}
FOLLOW_990:
#if defined(O_DEBUG)
	if(debug[6]){ DEBUG_ELM(1); }
#endif
	return 1;
FOLLOW_997:
#if defined(O_DEBUG)
	if(debug[6]){ DEBUG_ELM(0); }
#endif
	return 0;
}

#if defined(DEBUG_STZ)
/*========== DEBUG_STZ() =====================================
	Function ÅFdebug routine for Stz_CE,Stz_PE,ceptr,celen.
  ============================================================*/
void DEBUG_STZ() {
	register integer_16 i,n;

	if(ceptr==0){ goto DEBUG_STZ99; }

	switch(Stz_PE.stz_kind){
	case DICKIND_D:  FNX_PRINTF(",êîéö"); break;
	case DICKIND_5Y: FNX_PRINTF(",òAóp"); break;
	case DICKIND_I:  FNX_PRINTF(",ì‡ïî"); break;
	default:
		FNX_PRINTF(pe_is_kango ? ",äøåÍ" : ",äOïî");
	}
	FNX_PRINTF(",F2="); DEBUG_H1(Stz_PE.stz_f2);
	FNX_PRINTF(",CTL="); DEBUG_H1(Stz_PE.stz_ctl);
	FNX_PRINTF(",MRU="); DEBUG_H1(Stz_PE.stz_mru);
	FNX_PRINTF(",STZ="); DEBUG_H1(Stz_PE.stz_stz);

	n=Stz_PE.stz_nbno; FNX_PRINTF(",NBNO=%d",n); FNX_PRINTF(",BNO=");
	for(i=0;n--;i++){
		FNX_PRINTF("%d",Stz_PE.stz_bno[i]);
		if(n>0){ putchar(','); }
	}
	putchar('\n');

DEBUG_STZ99:
	/* print current word */
	FNX_PRINTF(" iP=%d",ceptr+1); FNX_PRINTF(",iL=%d",celen);
	putchar(','); DEBUG_K1(&inert[ceptr*2],celen);
	putchar('\n');

	switch(Stz_CE.stz_kind){
	case DICKIND_D:  FNX_PRINTF(",êîéö"); break;
	case DICKIND_5Y: FNX_PRINTF(",òAóp"); break;
	case DICKIND_I:  FNX_PRINTF(",ì‡ïî"); break;
	default:
		FNX_PRINTF(ce_is_kango ? ",äøåÍ" : ",äOïî");
	}
	FNX_PRINTF(",F2="); DEBUG_H1(Stz_CE.stz_f2);
	FNX_PRINTF(",CTL="); DEBUG_H1(Stz_CE.stz_ctl);
	FNX_PRINTF(",MRU="); DEBUG_H1(Stz_CE.stz_mru);
	FNX_PRINTF(",STZ="); DEBUG_H1(Stz_CE.stz_stz);

	n=Stz_CE.stz_nbno; FNX_PRINTF(",NBNO=%d",n); FNX_PRINTF(",BNO=");
	for(i=0;n--;i++){
		FNX_PRINTF("%d",Stz_CE.stz_bno[i]);
		if(n>0){ putchar(','); }
	}
	putchar('\n');
}
#endif

/***************************** END OF ILE_STZC.C *****************************/

