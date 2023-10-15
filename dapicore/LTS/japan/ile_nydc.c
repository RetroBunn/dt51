/*************************************************
	ILE_NYDC.C	updated at 18th September 1990
	Matters related to input statement
 *************************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_envh.h"
#include	"ile_errh.h"
#include	"ile_fddh.h"
#include	"ile_kkhh.h"
#include	"ile_mjzh.h"
#include	"ile_nydh.h"
#include	"ile_func.h"


/*========== INERT_INIT() ===================================================
	Function: Standardize each character in input statement

	(1) Specify the types of characters.
			Kanji numeral 1 ::=ˆê“ñOlŒÜ˜Zµ”ª‹ãZˆë“óQ
			Kanji numeral 2 ::=\•SçE
			Kanji numeral 3 ::=”Šô‰½
			Kanji numeral 4 ::=–œ‰­’›‹äİ
			Kanji ::=Kanji characters except Kanji numerals
			Hiragana ::=‚  to ‚ğ‚ñ and a long vowel following a hiragana character
			Katakana ::=ƒA to ƒ’ƒ“ and a long vowel following a katakana character
			Alphabetic character ::=A to Z, A to (, and A to „`
			Arabic numeral ::=‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚O
			Opened parenthesis or bracket ::='"ikmoqsuwy
			Closed parenthesis or bracket ::='"jlnprtvxz
			Sign ::={|}
			Others
	(2) Comma and period: 
			When numbers exist before and after it, it is recognized as a delimiter inserted every three digits in a number or a decimal point.
			Otherwise, it is recognized as a special symbol.
	(3) Hyphen or minus sign:
			When alphanumeric characters exist before and after it, it is recognized as a hyphen.
			Otherwise, it is recognized as a minus sign.
		Example: 03-123-4567		hyphen
			The temperature today is -10 degrees.	minus
  ===========================================================================*/

void INERT_INIT() {
	register BYTE *kptr,*aptr;
	LPBYTE nyd;
	BYTE ah,al,dl,kind;
	WORD ax;
	integer_16 id1,id2;

	n_inert=0;
	for(kptr=inert;	     kptr<(inert+MAX_INERT*2)   ;){ *kptr++='\0'; }
	for(kptr=inert_kind; kptr<(inert_kind+MAX_INERT);){ *kptr++='\0'; }
	for(kptr=inert_attr; kptr<(inert_attr+MAX_INERT);){ *kptr++='\0'; }
	ceptr=0; celen=0; ceptr_sav=0; celen_sav=0;

	nyd= onsei_addr->onsei_inert;	/* Address of input character string */
	id1=0; id2=0;
	kptr=inert_kind; aptr=inert_attr;
	while(1){
		ah=(*nyd++);				/* Fetch the first byte of the input character.*/
		if(ah==0){ break; }		/* When it is the end of string, the processing ends.*/

		if(id1>=MAX_INERT){ jp_ERROR(Err_InertOVF); }	/* Exceeds the number of characters. */

		al=(*nyd++);				/* Fetch the second byte of the input character.*/
		ax=al|(ah<<8);
		inert[id2]=ah; inert[id2+1]=al;
		*aptr=0;					/* Reset the attribute of the input character.*/

		/* A half-size character causes an error.*/
		if(ah==0x00||ah==0x20||ah==0x29){
			jp_ERROR(Err_Hankaku);
		}

		/* Categorizing kanji numerals and signs (+ and ().*/
		switch(ax){
		case 0x306C: case 0x4673: case 0x3B30: case 0x3B4D:	/* ˆê“ñOl */
		case 0x385E: case 0x4F3B: case 0x3C37: case 0x482C:	/* ŒÜ˜Zµ”ª */
		case 0x3665: case 0x213B:							/* ‹ãZ */
		case 0x306D: case 0x4675: case 0x3B32:				/* ˆë“óQ */
			*kptr=CHRKIND_KDigit1; goto NextChr;
		case 0x3D3D: case 0x4934: case 0x4069:				/* \•Sç */
		case 0x3D26:										/* E */
			*kptr=CHRKIND_KDigit2; goto NextChr;
		case 0x323F: case 0x3476: case 0x3F74:				/* ‰½”Šô */
		/* Compound0x4A23 */									/* Plural number */
			*kptr=CHRKIND_KDigit3; goto NextChr;
		case 0x4B7C: case 0x322F: case 0x437B: case 0x357E: /* –œ‰­’›‹ */
		case 0x685F:										/* äİ */
			if(id1==0){ break; }
			if(*(kptr-1)==CHRKIND_KDigit1 || *(kptr-1)==CHRKIND_KDigit2
			|| *(kptr-1)==CHRKIND_KDigit3 || *(kptr-1)==CHRKIND_ADigit){
				*kptr=CHRKIND_KDigit4; goto NextChr;
			}else{
				break;
			}
		/* case 0x215C: case 0x215E: */							/* {} */
			/* *kptr=CHRKIND_DSign; goto NextChr; */
		}

		/* Categorizing kanji, hiragana, and katakana characters */
		if(ah>=0x30){ *kptr=CHRKIND_Kanji; goto NextChr; }
		if(ah==0x24){				/* Hiragana */
			*kptr=CHRKIND_HKana;
			dl=MjzfGetChrAttr(al);		/* Look up the character attribute table. */
			if(MjzfHido(dl)){		/* Dependent characters (‚Ÿ‚¡‚£‚¥‚§‚á‚ã‚å) */
				*aptr=CHRATTR_Hido; goto NextChr;
			}
			if(MjzfSoku(dl)){		/* Double consonant or syllabic nasal */
				*aptr=CHRATTR_Soku; goto NextChr;
			}
			goto NextChr;
		}

		if(ah==0x25){				/* Katakana */
			*kptr=CHRKIND_KKana;
			dl=MjzfGetChrAttr(al);		/* Look up the character attribute table. */
			if(MjzfHido(dl)){		/* Dependent characters (ƒ@ƒBƒDƒFƒHƒƒƒ…ƒ‡) */
				*aptr=CHRATTR_Hido; goto NextChr;
			}
			if(MjzfSoku(dl)){		/* Double consonant or syllabic nasal */
				*aptr=CHRATTR_Soku; goto NextChr;
			}
			goto NextChr;
		}

		/* Categorizing alphabetic characters, Greek characters, Russian characters, and Arabic numerals  */
		*kptr=CHRKIND_Alpha;
		if(ah==0x23 && al>=0x41){ goto NextChr; }	/* English */
		if(ah==0x26){ goto NextChr; }				/* Greek */
		if(ah==0x27){ goto NextChr; }				/* Russian */

		if(ah==0x23 && al<=0x39){					/* digit */
			*kptr=CHRKIND_ADigit; goto NextChr;
		}

		if(ah==0x21){
			switch(al){
			case 0x39: case 0x3A:	/* XY (90”N5Œ1“ú)*/
				*kptr=CHRKIND_Kanji;
				goto NextChr;
			case 0x3C:
				/*
				 * If a long vowel is placed at the top of the sentence or if a long vowel follows after a non-kana character, the sentence is incorrect.
				 * When it follows a hiragana, it has to be a hiragana, and when it follows a katakana, it has to be a katakana.
				 * Also, a long vowel should be processed in the same way as double consonants and syllabic nasals.
				 */
				kind=(*(kptr-1));	/*inert_kind[id1-1];*/
				if(id1==0										/* Long vowel at the top. */
				||(inert[id2-2]==0x21 && inert[id2-1]==0x3C)	/* When the preceding character is a long vowel */
				||(kind!=CHRKIND_HKana && kind!=CHRKIND_KKana) ){	/* When the preceding character is not a kana */
					goto yomenai;
				}
				*kptr=kind;
				*aptr=CHRATTR_Soku;
				goto NextChr;
			default:
				yomenai:
				dl=MjzfGetChrAttr(al);		/* Look up the character attribute table. */
				*kptr=(MjzfToku1(dl)? CHRKIND_Other1:CHRKIND_Other2);

				switch(al){
				case 0x46: case 0x48: case 0x4A: case 0x4C: case 0x4E:
				case 0x50: case 0x52: case 0x54: case 0x56: case 0x58:
				case 0x5A:
					*kptr|=CHRKIND_BOpen; goto NextChr;
				case 0x47: case 0x49: case 0x4B: case 0x4D: case 0x4F:
				case 0x51: case 0x53: case 0x55: case 0x57: case 0x59:
				case 0x5B:
					*kptr|=CHRKIND_BClose; goto NextChr;
				default:
					*kptr|=CHRKIND_Other; goto NextChr;
				}
			}
		}else{
			/* 22xx,2cxx,2dxx */
			*kptr=CHRKIND_Other1 | CHRKIND_Other;
		}

		NextChr:
		id1++; id2+=2;
		++kptr; ++aptr;
	}

	if(id1==0){ jp_ERROR(Err_InertNone); }		/* When the length of the input character string is zero */

	*kptr=0;			/* Set null to the last character. */
	n_inert=id1;		/* Number of input characters */

	INERT_DIGIT();		/* Categorizing hyphen and period */
	INERT_COMMA();		/* Categorizing commas */

	if(n_inert==0){ jp_ERROR(Err_InertNone); } /* When the length of the input character string is zero */

	ceptr=0;
	onsei_addr->onsei_ninert= n_inert;

	return;
}


/*========== INERT_DIGIT() ==================================================
	Function: Categorizing hyphen and minus sign
		Categorizing by determining if the period is a delimiter or a decimal point.
  ===========================================================================*/
void INERT_DIGIT() {
	register integer_16 id1,id2;
	integer_16 bptr,nptr;
	WORD ax;
	BYTE ah,al;

	id1=0; id2=0;
	while(1){
		if(inert_kind[id1]==0){ break; }
 
		bptr=id1-1;
		if(bptr!=-1){ ah=inert_kind[bptr]; }	/* Type of the preceding character */
		nptr=id1+1;
		if(nptr!=n_inert){ al=inert_kind[nptr]; }	/* Type of the succeeding character */

		ax=(inert[id2]<<8) | inert[id2+1];		/* Fetch one character. */

		if(ax==0x215D || ax==0x215C || ax==0x215E){
			/* "+, -, or (": When alphanumeric characters exist before and after it, it is recognized as a special symbol.
					   Otherwise, it is recognizes as a sign. */
			inert_kind[id1]=CHRKIND_Other1 | CHRKIND_Other;
			if(bptr!= -1 && nptr!=n_inert){
				if((ah & 0xF0)==CHRKIND_Digit || ah==CHRKIND_Alpha){
					if((al & 0xF0)==CHRKIND_Digit || al==CHRKIND_Alpha){
						goto NextChr2;
					}
				}
			}
			if(nptr!=n_inert){
				if((al & 0xF0)==CHRKIND_Digit){
					/* When a number follows, it is recognized as a number, otherwise, it is recognized as a special symbol.*/
					inert_kind[id1]=CHRKIND_DSign;
				}
			}
			goto NextChr2;
		}

		if(ax==0x2125){
			/* When a number exists before and after a period, the period is a decimal point, otherwise, it is a punctuation.*/
			if(bptr== -1){ goto NextChr2; }		/* 1st char */
			if(nptr==n_inert){ goto NextChr2; }		/* last char */
			if((ah & 0xF0)==CHRKIND_Digit &&
			   (al & 0xF0)==CHRKIND_Digit){	/* A number exists before and after it. */
				inert_kind[id1]= (ax==0x2124? CHRKIND_DSep:CHRKIND_DDP);
				goto NextChr2;
			}
		}

		NextChr2: ;
		id1++; id2+=2;
	}
}


/*========== INERT_COMMA() ==================================================
	Function: Categorizing by determining if the comma is a delimiter or a digit grouping separator.

		‡@	When 1- to 3-digit number precedes a number, and 3-digit number follows the number, it is a digit grouping separator, 
			otherwise, it is a punctuation.

			‚PC‚Q‚R‚SC‚T‚U‚V			F	‚P‚Q‚R‚S‚T‚U‚V
			‚PC‚Q‚RC‚S‚TC‚U‚V		F	‚PE‚Q‚RE‚S‚TE‚U‚V
			‚P‚Q‚R‚SC‚T‚U‚V			F	‚P‚Q‚R‚SE‚T‚U‚V
			ˆêC“ñOlCŒÜ˜Zµ			F	‚P‚Q‚R‚S‚T‚U‚V
			ˆêC“ñ•SO\lCŒÜ•S˜Z\µ	F	‚PE‚Q‚R‚SE‚T‚U‚V

		‡A	If there is any punctuation a number string, it is recognized as a punctuation.

			‚P‚QC‚R‚SC‚T‚U‚VC‚W‚X‚O	F	‚P‚QE‚R‚SE‚T‚U‚VE‚W‚X‚O
			‚P‚QC‚R‚S‚TC‚U‚V‚WC‚X‚O	F	‚P‚QE‚R‚S‚TE‚U‚V‚WE‚X‚O
			‚P‚QC‚R‚S‚TC‚U‚VC‚W‚X‚O	F	‚P‚QE‚R‚S‚TE‚U‚VE‚W‚X‚O
  ===========================================================================*/
void INERT_COMMA() {
	register integer_16 id1,count;
	integer_16 comma;

	if(onsei_addr->onsei_kouseisystem){
		/* In correction mode, the number is always read digit by digit, so the comma is not distinguished.*/
		/* --89.11.29-- */
		return;
	}

	count=0; comma= -1;
	for(id1=n_inert; id1--;){
		switch(inert_kind[id1]){
		case CHRKIND_KDigit1:	/* Kanji numeral 1 : ˆê“ñOlŒÜ˜Zµ”ª‹ãZ */
		case CHRKIND_ADigit:	/* Arabic numeral : ‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚O */
			++count;
			break;
		default:
			if(inert[id1*2]==0x21 && inert[id1*2+1]==0x24){
				if(count==3){
					/* When a 3-digit number succeeds a comma, the comma is recognized as a digit grouping separator.*/
					inert_kind[id1]=CHRKIND_DSep;
					comma=id1;
				}
				count=0;
			}else{
				/* neither comma nor digit */
				if(count==0 || count>3){
					if(comma!= -1){
						/*A comma in "1234,567" or ",234" is a punctuation.*/
						inert_kind[comma]=CHRKIND_Other2 | CHRKIND_Other;
					}
				}
				count=0; comma= -1;
			}
		}
	}
	if(count==0 || count>3){
		if(comma!= -1){
			/*A comma in "1234,567" or ",234" is a punctuation.*/
			inert_kind[comma]=CHRKIND_Other2 | CHRKIND_Other;
		}
	}
	/*
	 * The following summarizes the above-described processing.
	 *	‚P‚Q‚R‚SC‚T‚U‚V			F	‚P‚Q‚R‚SE‚T‚U‚V			F‚n‚j
	 *	ˆêC“ñOlCŒÜ˜Zµ			F	‚PC‚Q‚R‚SC‚T‚U‚V			F‚n‚j
	 *	ˆêC“ñ•SO\lCŒÜ•S˜Z\µ	F	‚PE‚Q‚R‚SE‚T‚U‚V			F‚n‚j
	 *	‚PC‚Q‚R‚SC‚T‚U‚V			F	‚PC‚Q‚R‚SC‚T‚U‚V			F‚n‚j
	 *	‚PC‚Q‚RC‚S‚TC‚U‚V		F	‚PE‚Q‚RE‚S‚TE‚U‚V		F‚n‚j
	 *	‚P‚QC‚R‚SC‚T‚U‚VC‚W‚X‚O	F	‚P‚QE‚R‚SC‚T‚U‚VC‚W‚X‚O	F
	 *	‚P‚QC‚R‚S‚TC‚U‚V‚WC‚X‚O	F	‚P‚QC‚R‚S‚TC‚U‚V‚WE‚X‚O	F
	 *	‚P‚QC‚R‚S‚TC‚U‚VC‚W‚X‚O	F	‚P‚QC‚R‚S‚TE‚U‚VC‚W‚X‚O	F
	 */
	comma= -1;
	for(id1=n_inert; id1--;){
		switch(inert_kind[id1]){
		case CHRKIND_KDigit1:	/* Kanji numeral 1 : ˆê“ñOlŒÜ˜Zµ”ª‹ãZ */
		case CHRKIND_ADigit:	/* Arabic numeral : ‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚O */
			break;
		default:
			if(inert[id1*2]==0x21 && inert[id1*2+1]==0x24){
				if(comma==-1){
					if(inert_kind[id1]!=CHRKIND_DSep){
						comma=id1;
					}
				}else{
					inert_kind[id1]=CHRKIND_Other2 | CHRKIND_Other;
				}
			}else{
				comma= -1;
			}
		}
	}
	comma= -1;
	for(id1=0; id1<n_inert; ++id1){
		switch(inert_kind[id1]){
		case CHRKIND_KDigit1:	/* Kanji numeral 1 : ˆê“ñOlŒÜ˜Zµ”ª‹ãZ */
		case CHRKIND_ADigit:	/* Z—p”š : ‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚O */
			break;
		default:
			if(inert[id1*2]==0x21 && inert[id1*2+1]==0x24){
				if(comma== -1){
					if(inert_kind[id1]!=CHRKIND_DSep){
						comma=id1;
					}
				}else{
					inert_kind[id1]=CHRKIND_Other2 | CHRKIND_Other;
				}
			}else{
				comma= -1;
			}
		}
	}
}

	
/*========== INERT1000() ===============================================
	Function: Obtain the length of an element that starts from the 
		"current element start position," and is available for looking up the dictionary, 
		and the same type of character follows it.
	Value: Length of reading
  =============================================NydfSaichouGjsMotomeru==*/
integer_16 INERT1000() {
	/* There is no limit on number of characters in a katakana noun, number, or special symbol.*/

#if !defined(O_TALKONLY)
	/* For the processing of next target, longer segment, or shorter segment, */
	if(conv_mode==CONV_NEXT||conv_mode==CONV_SHORT||conv_mode==CONV_LONG){
		/* if the position and the length of the watching element conflict with the segment range, shorten it.*/
		while(celen && (WS_CE_CHK()==0)){
			celen=INERT2000(ceptr,celen);
		}
	}
#endif

	return celen;
}


/*========== INERT2000(Start position, reading length) =================================
	Function: Shorten the "current element length" starting at the "current element start position" 
 		with considering the dependent character.
	Value: "Current element length" after it is shortened
  =======================================================NydfYomChijimeru==*/
integer_16 INERT2000(integer_16 e_ptr, integer_16 e_len)
{
	/*
	 *	A dependent character such as in "‚Pƒ•Œ" or "ƒ•Œ" is allowed.
	 */
	--e_len;
	return e_len;
}


/*========== INERT200B(Start position, reading length) =================================
	Function: Shorten the "current sentence length" starting at the "current sentence start position" 
		with considering the dependent character.
	Value: "Current sentence length" after it is shortened
  =======================================================NydfYomChijimeru==*/
integer_16 INERT200B(integer_16 b_ptr, integer_16 b_len)
{

INERT200B_10:
	if(--b_len==0){ return 0; }

	/* When there is a dependent character at the top of  the succeeding sentence, shorten it again.*/
	if(inert_attr[b_ptr+b_len] & CHRATTR_Hido){ goto INERT200B_10; }
	return b_len;
}


/*========== INERT3000() ==================================================
	Function: Extend the "current element length" starting at the "current element start position" 
 		considering with the dependent character.
	Value: If it can be extended, return the "current element length."If not, return 0.

	integer_16 INERT3000(e_ptr,e_len) register integer_16 e_ptr,e_len; {
		if((e_ptr+e_len)>=n_inert){
			return 0;
		}else{
			e_len++; return e_len;
		}
	}
  ==========================================================NydfYomNobasu==*/


/*========== INERT300B() ==================================================
	Function: Extend the "current sentence length" starting at the "current sentence start position" 
 		considering with the dependent character.
	Value: If it can be extended, return the "current sentence length."If not, return 0.
  ==========================================================NydfYomNobasu==*/
integer_16 INERT300B(b_ptr,b_len) register integer_16 b_ptr,b_len; {

INERT300B_10:
	if((b_ptr+b_len)>=n_inert){ return 0; }
	++b_len;

	/* When there is a dependent character at the top of  the succeeding sentence, extend it again.*/
	if(inert_attr[b_ptr+b_len] & CHRATTR_Hido){ goto INERT300B_10; }

	return b_len;
}


/*========== INERT4000() ====================================================
	Function: Obtain the length of the same type of succeeding character that starts at the "current element start position"
		for the "current element length."
	Value: If there is an input character, set 1, otherwise, set 0.

	BOOL INERT4000() {
		register BYTE *bx,al;

		if(ceptr>=n_inert){ return 0; }	** There is no input character. **
		bx=(&inert_kind[ceptr]);

		celen=0;

		** Compare the type of character based on the upper 4 bits. **
		al=(*bx) & 0xF0; ++bx; ++celen;
		for(;*bx;celen++,bx++){
			if(al!=(*bx & 0xF0)){ break; }
		}

		return 1;
	}
  ==================================================NydfSaichouJsuMotomeru==*/

/***************************** END OF ILE_NYDC.C *****************************/

