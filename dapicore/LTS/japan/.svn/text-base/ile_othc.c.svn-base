/**********************************************
	ILE_OTHC.C	updated at 8th January 1991
	Conversion of special symbols and katakana words
 **********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_envh.h"
#include	"ile_errh.h"
#include	"ile_fddh.h"
#include	"ile_kkhh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"

#include	"ile_mruh.h"

/*========== KKANA1000() ===================================================
	Function: Check whether or not the katakana conversion of the character string 
		from the position ceptr to the number of character celen is available.
	Value: 1 = Possibly available, 0 = Impossible
  ==========================================================================*/
BOOL KKANA1000() 
{
	BYTE al;

	/* When the initial abandon word search is not specified, no processing is performed.*/
	if((Stz_CE.stz_mru & BITMRU_ABORT)==0){ return 0; }

	/* If a character that is not a katakana character is included, there is no possibility.*/
	if((al=(BYTE)OTHER2000())==0){ return 0; }
	if(al!=CHRKIND_KKana){ return 0; }

	/* When the preceding character is a katakana character, no processing is performed.(91.1.8_}箪・|)*/
	if(ceptr!=0){
		if(*(WORD *)&inert[ceptr*2-2]==0x3C21){
			if(inert[ceptr*2-4]==0x25){ return 0; }
		}else{
			if(inert[ceptr*2-2]==0x25){ return 0; }
		}
	}

	/* When the preceding character is an automatically-generated katakana character, no processing is performed.*/
	if(ceptr!=0){
		if(stc_kind[stc_ptr-1]==DICKIND_K){ return 0; }
	}

	/* When it starts with a syllabic, long vowel, or double consonant, and if the preceding character is not a katakana character, the processing is performed.*/
	if(inert_attr[ceptr]==CHRATTR_Soku){
		/* When it is the top, the processing is performed.*/
		if(ceptr==0){ return 1; }
		/* When the preceding character is not a katakana character, the processing is performed.*/
		if(inert_kind[ceptr-1]!=CHRKIND_KKana){ return 1; }
		return 0;
	}
	return 1;
}


/*========== KKANA5000(ptr) ============================================
	Function: Store the pronunciation of the katakana word that starts at the 
		current watching word starting position 
		in the position starting with the offset di in the output data area.
  ======================================================================*/
integer_16 KKANA5000(di) integer_16 di; {
	register BYTE *si;
	register integer_16 cx;
	integer_16 last_chouon;
	BYTE ch;

	si=(&stc_accent_raw[stc_ptr][0]);
	/*
	 *	Convert the katakana word into mora data.
	 *	If it cannot be converted, no processing can be performed.
	 *	The mara data is stored in kkana_len,kkana_buf.
	 */
	if(kana_mora()==0){ jp_ERROR(Err_HenkanFunou); }

	/* Give special attention to a word that starts with a syllabic nasal, long vowel, or double consonant.*/
	/* A long vowel is processing using kana_mora().It is not actually read.*/
	if(kkana_buf[0]==0xCF){ kkana_buf[0]=0x32; }

	/* Check whether or not the last character is a long vowel.*/
	last_chouon=(kkana_buf[kkana_len-1]==0xC0 ? 1:0);
	cx=kkana_len-last_chouon;
	/*
	 *	When the word has 5 or more syllables, the accent fall is placed on antepenultimate syllable.However, a long vowel at the end is ignored.
	 *	When the word has 3 syllables and it ends with a long vowel, the accent fall is places on the second syllable.（グレー、フリー、タブー）
	 *	When the word  has less than 3 syllables, it has head-high accent.
	 */
	if(cx>=5){ goto KKANA5000_NAKA3; }
	if(kkana_len==3 && last_chouon){ goto KKANA5000_NAKA2; }
	if(cx<=3){ goto KKANA5000_ATAMA; }
	/*
	 *	When the word has four syllables, and its third syllable is a mora phoneme, the accent fall is on the second syllable.
	 *	Otherwise, it has head-high accent.
	 */
	ch=kkana_buf[2];
	if(0xC0==ch||0xCF==ch||0xD7==ch){ goto KKANA5000_NAKA2; }

KKANA5000_ATAMA:	*si=1; goto KKANA5000_500;
KKANA5000_NAKA2:	*si=2; goto KKANA5000_500;
KKANA5000_NAKA3:	*si=(last_chouon? kkana_len-3:kkana_len-2);
KKANA5000_500:
	*(++si)=0;		/* stc_accent_raw[stc_ptr][1]=0 */
	*(++si)=0;		/* stc_accent_raw[stc_ptr][2]=0 */

	/* Copy the pronunciation data into the output area.*/
	for(cx=cpron_len=kkana_len,si=kkana_buf; cx--; ){
		di=OMEGA1000(*si++,di);
	}
	return di;
}


/*========== OTHER2000() =============================================================
	Function: Check whether or not the character string from the position ceptr to the 
		number of character celen has more than one type of characters.
	Value: ＝0: Has more than one type of characters./ ( 0: Return the type of character.(Upper 4 bits)
  ====================================================================================*/
WORD OTHER2000() {
	/* The type of character is indicated with the upper 4 bits.*/
	register BYTE *bx; BYTE al; register integer_16 cx;

	cx=celen; bx=(&inert_kind[ceptr]);
	
	/* Compare the type of character based on the upper 4 bits.*/
	al=(*bx) & 0xF0; ++bx; --cx;
	for(;cx--;bx++){
		if(al!=(*bx & 0xF0)){ return 0; }
	}
	return al;
}


/*========== OTHER5000(ptr) ========================================
	Function: Store the pronunciation of the simple word that starts at the current element starting position 
 		 in the position starting with the offset ptr in the output data area.
  =================================================TjgfKekMotomeru==*/
integer_16 OTHER5000(di) register integer_16 di; {
	di=OMEGA1000(0xFF,di);
	cpron_len=1;			/* Reading is tentatively ignored.*/
	return di;
}


/*========== OTHER_GRCD() =========================================
	Function: Make settings of grammar information of the simple word that starts 
		at the current watching word starting position.
	Note:  Hiragana and katakana words are processed in the same way as foreign words.
  =================================================================*/
void OTHER_GRCD() 
{
	/*
	 *	According to the character type, determine the grammar code and back-end number.
	 *	(Exception) When the length is 1, and it is a decimal point, it is recognized as Other2.
	 *			(3 (SAN) / . / 5人が… (GONINGA---))
	 */
	if(celen==1 && inert_kind[ceptr]==CHRKIND_DDP){ goto OTHER_GRCD_120; }

	switch(inert_kind[ceptr] & 0xF0){
	case CHRKIND_Other1:	/* A character that can be placed at the top */
		StzfGrcdAdd(Fdd_Header.Fdd_GrcdToku1);
		StzfGrcdStore(Fdd_Header.Fdd_GrcdUsr);
		break;
	case CHRKIND_Other2:	/* A character that cannot be placed at the top */
		OTHER_GRCD_120:
		/* Even when it is a character that cannot be placed the top, if it is placed the top of the input character string, it is processed as a character that can be placed the top of a word.*/
		if(ceptr==0){
			StzfGrcdAdd(Fdd_Header.Fdd_GrcdToku1);
			StzfGrcdStore(Fdd_Header.Fdd_GrcdUsr);
		}else{
			StzfGrcdAdd(Fdd_Header.Fdd_GrcdToku2);
		}
		break;
	case CHRKIND_Digit:
		StzfGrcdAdd(Fdd_Header.Fdd_GrcdDigit);
		break;
	case CHRKIND_KKana:
		StzfGrcdAdd(Fdd_Header.Fdd_GrcdGai);
		StzfGrcdAdd(Fdd_Header.Fdd_GrcdUsr);
		StzfGrcdAdd(36);	/* _}弓_|,_}累綾・|,_}箕荷 _|*/
		StzfGrcdAdd(88);	/* _}騰慰宛_|,_}朧仟_|*/
		StzfGrcdAdd(123);	/* _}橘 _|*/
		StzfGrcdAdd(126);	/* _}橘 _|*/
		break;
	}
}

/***************************** END OF ILE_OTHC.C *****************************/

