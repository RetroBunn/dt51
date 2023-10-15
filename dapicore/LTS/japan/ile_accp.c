/*********************************************
	ILE_ACCP.C	updated at 17th April 1990
	Determination of case of segment and estimation of pause position
 *********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_acch.h"
#include	"ile_envh.h"
#include	"ile_fddh.h"
#include	"ile_mruh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"
#include "pkind.h"

#if defined(O_JAL)
extern BYTE buf[];
#endif

#define		CONTINUE		 0		/* No pause is inserted.*/
#define		RENTAI_NOPAUSE	 1		/* Attributive modification case: No pause is inserted.*/
#define		RENTAI			 2		/* Attributive modification case: Pause insertion is undetermined.*/
#define		RENYOU			 4		/* Conjunctive modification case: Pause insertion is undetermined.*/
#define		PAUSE_SHORT		 8		/* Insert a short pause.*/
#define		PAUSE_LONG		16		/* Insert a long pause.*/

/*#define	PAUSE_MEDIUM	12		   Pause after adverb*/

#define		NAKATEN			0x2126	/* uEv */
#define		TOUTEN			0x2123	/* uBv */

/*========== PAUSE1000() =========================
	Function: Checks the case of the segment and determines whether or not to insert a pause.
  ================================================*/
void PAUSE1000() 
{
	BYTE al;
	integer_16 bno,even,mem;
	WORD code;
	register integer_16 i,c;

	/* Initialize the segment case according to the back-end number. */
	stc_pause[0]=0;
	for(i=0;i<stc_ptr-1;++i){
		stc_pause[i+1]=0;
		for(c=0;c<stc_nbno[i];++c){
			if(bno=stc_bno[i][c]){
				/* Only the lower three bits are related to the segment case.*/
				switch(FddHDR[Fdd_Header.Fdd_BnoTblOfs+bno-1] & 0x07){
				case BITBNO_RentaiKaku:
					al=RENTAI; break;
				case BITBNO_RenyouKaku:
					al=RENYOU;
					/* When the segment is a conjunctive modification case and adverb, insert a pause.
					 * if(bno==Fdd_Header.Fdd_BnoAdv){ al=PAUSE_MEDIAM; fi
					 */
					break;
				case BITBNO_Shushi:
					al=PAUSE_LONG; break;
				default:
					al=CONTINUE; break;
				}
				stc_pause[i+1]=al;
				goto PAUSE1000_170;
			}
		}
		PAUSE1000_170:;
	}

	/*
	 * The element before 59 should be in ending form.
	 *		==> It is not good because a pause is inserted between the compound nouns.
	 *	for(i=1;i<stc_ptr;++i){
	 *		if(acc_accent_raw[i][1]==5 && acc_accent_raw[i][2]==9){
	 *			stc_pause[i-1]=BITBNO_Shushi;
	 *		}
	 *	}
	 */
	/*
	 * The accent of the element preceding an ancillary is always combined.
	 * The compound verb or compound adjective should be considered as a word, so
	 * no pause should be inserted in such word.(87.1.13)
	 * A pause should always be inserted at the end of a sentence.
	 * A punctuation (special symbol) is not considered.
	 */
	for(i=1;i<stc_ptr;++i){
		/* The accent of the element preceding an ancillary is always combined.*/
		if((stc_ctl[i] & BITCTL_FIRST)==0){ stc_pause[i]=0; }
		/*
		 *	The compound verb or compound adjective should be considered as a word, so
		 *	no pause should be inserted in such word.
		 *	"(verb stem or verb conjunctive conjugation ending) + (verb stem or adjective stem)"
		 *	A pause should not be inserted in the above case.
		 */
		if((phrase_kind_sav[i-1]==pkind_verb_stem
		  ||phrase_kind_sav[i-1]==pkind_verb_renyou)
		 &&(phrase_kind_sav[i]==pkind_verb_stem
		  ||phrase_kind_sav[i]==pkind_adj_stem)){
			stc_pause[i]=CONTINUE;
		}
	}

	/*
	 * A punctuation should be a boundary between clauses.(A decimal point that is changed to a delimiter is also included.)
	 * A pause is always inserted immediately after a punctuation, accordingly.
	 * However, even if there is a special symbol (such as a blank space) at the beginning of a sentence, 
	 * no pause is inserted between the sentence and the succeeding segment.
	 */
	for(i=1;i<stc_ptr-1;++i){
		if(code=chk_separator(i)){
			if(code==NAKATEN
			&&(inert_kind[stc_in_ptr[i-1]]==CHRKIND_KKana
			 ||inert_kind[stc_in_ptr[i+1]]==CHRKIND_KKana)){
				/*
				 *	When the punctuation is a middle dot,
				 *	a pause is not inserted if either preceding or succeeding word is in katakana.
				 *	(Example) ƒjƒ…[Eƒˆ[ƒN (NEW-YORK), ƒ|[ƒYEŠÔ (PAUSE-JIKAN)
				 */
				stc_pause[i]=stc_pause[i+1]=CONTINUE;
			}else{
				/* The case preceding a punctuation should be cleared in advance.*/
				stc_pause[i]=CONTINUE;
				/* A long pause is inserted at a period, and a short pause is inserted at any other punctuation.*/
				stc_pause[i+1]=(code==TOUTEN? PAUSE_LONG:PAUSE_SHORT);
			}
		}
	}

#if defined(O_JAL)
	/*
	 * Remove the pause immediately before a one-byte space.
	 */
	for(i=1;i<stc_ptr-1;++i){
		if(chk_han_space(i)){
			/* The case preceding a one-byte space should be cleared in advance.*/
			stc_pause[i]=CONTINUE;
			stc_pause[i+1]=0;
		}
	}
#endif

	/********************************************************************
	 *																	*
	 *	Meaning of stc_pause[] at this point									*
	 *																	*
	 *		When the preceding element is a punctuation, special symbol, or end form	F	PAUSE_LONG				*
	 *		When the preceding element is a conjunctive modification				F	RENYOU					*
	 *		When the preceding element is an attributive modification				F	RENTAI					*
	 *		No pause is inserted immediately before it.			F	0						*
	 *																	*
	 ********************************************************************/

	/*
	 * It may be better to insert a pause after a topic particle "‚Í(WA)."
	 *
	 *		This is just an assumption.
	 *
	 *	for(i=0;i<stc_ptr;++i){
	 *		if(stc_bno[i][0]==99){ stc_pause[i]=PAUSE_SHORT; }
	 *	}
	 */

	/*
	 * When the element is an attributive modification, if the number of mora phonemes between the element and the previous or following pause exceeds a certain number,
	 * a pause is forcibly inserted, otherwise it is combined.
	 *	for(c=0,i=0;i<stc_ptr;++i){
	 *		if(stc_pause[i]==0){ c+=stc_out_len[i]; }
	 *		if(stc_pause[i]>=4 || stc_pause[i]==BITBNO_RenyouKaku){ c=0; }
	 *		if(stc_pause[i]==BITBNO_RentaiKaku){ mem=i; }
	 *		if(c>MAX_PHRASE){ stc_pause[mem]=4; c-=mem; }
	 *	}
	 *	for(c=0,i=stc_ptr;i--;){
	 *		if(stc_pause[i]==0){ c+=stc_out_len[i]; }
	 *		if(stc_pause[i]>=4 || stc_pause[i]==BITBNO_RenyouKaku){ c=0; }
	 *		if(stc_pause[i]==BITBNO_RentaiKaku){ mem=i; }
	 *		if(c>MAX_PHRASE){ stc_pause[mem]=4; c-=mem; }
	 *	}
	 *	for(i=0;i<stc_ptr;++i){
	 *		if(stc_pause[i]==BITBNO_RentaiKaku){ stc_pause[i]=0; }
	 *	}
	 */

	/*
	 *	When more than one attributive modification continuously appears, see the sentence from the end, and 
	 *	combine the odd-numbered element, and insert a pause at the even-numbered element.
	 */
	even=1;
	for(i=stc_ptr;i--;){
		switch(stc_pause[i]){
		case RENTAI:	even=1-even;
						stc_pause[i]=(even? PAUSE_SHORT:RENTAI_NOPAUSE);
						break;
		case 0:			break;
		default:		even=1;
		}
	}

	/*
	 * When the element is a conjunctive modification, if the number of mora phonemes between the element and the previous or following pause exceeds a certain number,
	 * insert a pause forcibly.
	 * c=0;
	 *	for(i=0;i<stc_ptr;++i){
	 *		if(stc_pause[i]==0){ c+=stc_out_len[i]; }
	 *		if(stc_pause[i]>=4){ c=0; }
	 *		if(stc_pause[i]==BITBNO_RenyouKaku){ mem=i; }
	 *		if(c>MAX_PHRASE){ stc_pause[mem]=4; c-=mem; }
	 *	}
	 *	c=0;
	 *	for(i=stc_ptr;i--;){
	 *		if(stc_pause[i]==0){ c+=stc_out_len[i]; }
	 *		if(stc_pause[i]>=4){ c=0; }
	 *		if(stc_pause[i]==BITBNO_RenyouKaku){ mem=i; }
	 *		if(c>MAX_PHRASE){ stc_pause[mem]=4; c-=mem; }
	 *	}
	 */

	/*
	 *	When more than one conjunctive modification continuously appears, see the sentence from the beginning, and 
	 *	combine the odd-numbered element, and insert a pause at the even-numbered element.
	 *	However, if the sentence consists of attributive + conjunctive + conjunctive + ---, insert a pause between the conjunctive modifications (attributive + conjunctive / conjunctive + ---).
	 *	If the sentence consists of conjunctive + attributive + conjunctive + ---, insert a pause between the first conjunctive modification and the attributive modification, and insert another pause after the second conjunctive modification (conjunctive/ attributive + conjunctive / ---).
	 *
	 *	(Example)	”ü‚µ‚¢‰Ô‚ª(UTSUKUSHII HANAGA) / ç‚­(SAKU)
	 *			t‚ª—ˆ‚Ä(HARUGAKITE) / ‰Ô‚ªç‚­ (HANAGA SAKU)
	 *			„‚Í(WATASHIWA) / –…‚ÌŠwZ‚Ö (IMOUTONO GAKKOUE) / s‚Á‚½ (ITTA)
	 *			Œ¾ŒêHŠw‚Í—DG‚¾H(GENGOKOUGAKUHA YUUSHUUDA?)
	 *			Œ¾ŒêHŠw‚Ì‹Zp‚Í(GENGOKOUNO GIJUTSUWA) / —DG‚¾H(YUUSHUUDA?)
	 *			Œ¾ŒêHŠw‚Ì(GENGOKOUNO) / ˆêŒË‚Ì‹Zp‚Í(ICHINOHENO GIJYUTSUWA) / —DG‚¾H(YUUSHUUDA?)
	 *			”ü‚µ‚¢‰Ô‚ª (USTUKUSHII HANAGA) / ç‚¢‚Ät‚ª(SAITE HARUGA) / —ˆ‚é(KURU)	(There is not much choice.)
	 */
	even=1;
	for(i=0;i<stc_ptr;++i){
		switch(stc_pause[i]){
		case RENYOU:
			mem=i; even=1-even;
			stc_pause[i]=(even? PAUSE_SHORT:CONTINUE);
			break;
		case CONTINUE:
			break;
		case RENTAI_NOPAUSE:
			stc_pause[i]=CONTINUE;
			if(even==0){ stc_pause[mem]=PAUSE_SHORT; }
			even=0;
			break;
		default:
			even=1;
		}
	}

	/*
	 * To pronounce this as "”ü‚µ‚¢‰Ô‚ª(UTSUKUSHII HANAGA) / ç‚¢‚Ä(SAITE) / t‚ª—ˆ‚é(HARUGA KURU),
	 * a pause is inserted not only before but also after "attribute + conjunctive."
	 * even=1; c=0;
	 * for(i=0;i<stc_ptr;++i){
	 *	 switch(stc_pause[i]){
	 *	 case RENYOU:
	 *		if(c==4){ even=0; c=0; }
	 *		mem=i; even=1-even; stc_pause[i]=(even? PAUSE_SHORT:CONTINUE);
	 *		if(c==2){ c=4; }
	 *		break;
	 *	 case CONTINUE:
	 *		break;
	 *	 case RENTAI_NOPAUSE:
	 *		stc_pause[i]=CONTINUE;
	 *		if(even==0){ stc_pause[mem]=PAUSE_SHORT; }
	 *		even=0; c=2; break;
	 *	 default:
	 *		even=1; c=0;
	 *	 }
	 * }
	 */

	/********************************************************************
	 *																	*
	 *	Meaning of stc_pause[] at this point									*
	 *																	*
	 *		Insert a long pause immediately before it.	F	PAUSE_LONG				*
	 *		Insert a short pause immediately before it.	F	PAUSE_SHORT				*
	 *		No pause is inserted immediately before it.			F	0						*
	 *																	*
	 ********************************************************************/

	/*
	 *	Consider the operation regarding a pause if there is any.(63/10/18)
	 *	However, only the element at the end of the segment is to be considered.
	 */
	for(i=0;i<stc_ptr;++i){
		if(stc_mru[i] & BITMRU_PINS){
			stc_pause[i]=PAUSE_SHORT;
		}else{
			if(stc_mru[i] & BITMRU_PDEL){
				stc_pause[i]=0;
			}
		}
	}

	/*
	 *	A short pause before the number is preferred, however, whether or not to insert it is pending.
	 *	Because both "\Œ(JUUGATSU)" and "ˆê’v(ICCHI)" are words of Chinese origin, and a pause should be inserted before "\Œ(JUUGATSU)," but
	 *	no pause should be inserted before "ˆê’v(ICCHI)."
	 *
	 *for(i=1;i<stc_ptr;++i){
	 *	A pause can be inserted between the non-Chinese origin word element and a number.
	 *	Note that the numerals in the external dictionary (such as ‚P‚OŒ (10 GATSI) or ˆê“ú(ICHINICHI) are to be the objects.)
	 *	c=stc_in_ptr[i];
	 *	if((inert_kind[c-1]&0xF0)!=CHRKIND_Digit&&(inert_kind[c]&0xF0)==CHRKIND_Digit){
	 *		If a pause has already existed, leave it there.
	 *		if(stc_pause[i]==0){ stc_pause[i]=PAUSE_SHORT; }
	 *	}
	 *}
	 */

	/*
	 *	When there is any number preceding ’›(CHO), ‰­(OKU), or –œ(MAN), insert a pause.
	 */
	for(i=1;i<stc_ptr;++i){
		if(stc_kind[i-1]==DICKIND_D && stc_kind[i]==DICKIND_D){
			if(stc_dexp[i-1]>=4){
				/* If a pause has already existed, leave it there.*/
				if(stc_pause[i]==0){ stc_pause[i]=PAUSE_SHORT; }
			}
		}
	}

	/*
	 *  stc_pause[] at this point si to be the number of syllables of a pause to be inserted immediately before the element  
	 * is represented as in 1/8 syllabic units.
	 */

	/*
	 *	Insert a long pause before our after a special symbol in correction mode.
	 */
	for(i=0;i<stc_ptr;++i){
		if(onsei_addr->onsei_kouseisystem && stc_kind[i]==DICKIND_T){
			al=inert_kind[stc_in_ptr[i]] & 0xF0;
			if(al==CHRKIND_Other1 || al==CHRKIND_Other2){
				stc_pause[i]=PAUSE_LONG;
				if(i<stc_ptr-1){ stc_pause[i+1]=PAUSE_LONG; }
			}
		}
	}

}


#if defined(O_JAL)
chk_han_space(i) integer_16 i; {
	BYTE ch;
	integer_16 ptr;
	register WORD before,after;

	ptr=stc_in_ptr[i];
	/* If an element contains two or more characters, it cannot be a special symbol.*/
	if(stc_out_len[i]!=1){ return 0; }
	ch=inert_kind[ptr];
	ch &= 0xF0;
	if(ch!=CHRKIND_Other1 && ch!=CHRKIND_Other2){ return 0; }
	if(((buf[ptr*2]<<8) | buf[ptr*2+1])!=0x2020){ return 0; }
	/* When there are alphanumeric characters before or after a one-byte space, do not insert a pause.*/
	before = (buf[ptr*2-2]<<8) | buf[ptr*2-1];
	after  = (buf[ptr*2+2]<<8) | buf[ptr*2+3];
	if( (before>0x2040 && before<0x205B) ||			/* A..Z */
		(before>0x2060 && before<0x207B) ||			/* a..z */
		(before>0x202F && before<0x203A) ||			/* 0..9 */
		(before>0x232F && before<0x233A) ||			/* ‚O..‚P */
		(before>0x2340 && before<0x235B) ||			/* ‚`..‚y */
		(before>0x2360 && before<0x237B) ||			/* ‚..‚š */
		(before>0x2620 && before<0x277F) ){		/* ƒŸ..„‘ */
		if( (after>0x2040 && after<0x205B) ||			/* A..Z */
			(after>0x2060 && after<0x207B) ||			/* a..z */
			(after>0x202F && after<0x203A) ||			/* 0..9 */
			(after>0x232F && after<0x233A) ||			/* ‚O..‚P */
			(after>0x2340 && after<0x235B) ||			/* ‚`..‚y */
			(after>0x2360 && after<0x237B) ||			/* ‚..‚š */
			(after>0x2620 && after<0x277F) ){		/* ƒŸ..„‘ */
				return 1;
		}
	}
	return 0;
}
#endif

/***************************** END OF ILE_ACCP.C *****************************/

