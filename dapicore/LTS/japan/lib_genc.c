/***********************************************
	ILE_GENC.C	updated at 4th November 1990
	Creation of phonogram data [Kokubun format]
 ***********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_acch.h"
#include	"ile_envh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"

#ifndef UNONSEI
static integer_16 GEN_OUTPUT_C( BYTE   , integer_16 );
static integer_16 GEN_OUTPUT_S( BYTE * , integer_16 );
#endif

static const BYTE hardchar_table[][3]={
	'A',  0,  0,	'I',  0,  0,	'U',  0,  0,	'E',  0,  0,	/* 00..03 */
	'O',  0,  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 04..07 */
	'K','A',  0,	'K','I',  0,	'K','U',  0,	'K','E',  0,	/* 08..0B */
	'K','O',  0,	'K','Y','A',	'K','Y','U',	'K','Y','O',	/* 0C..0F */
	'S','A',  0,	'S','I',  0,	'S','U',  0,	'S','E',  0,	/* 10..13 */
	'S','O',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 14..17 */
	'S','H','A',	'S','H','I',	'S','H','U',	'S','H','E',	/* 18..1B */
	'S','H','O',	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 1C..1F */
	'T','A',  0,	'T','I',  0,	'T','U',  0,	'T','E',  0,	/* 20..23 */
	'T','O',  0,	'C','H','A',	'C','H','U',	'C','H','O',	/* 24..27 */
	'C','H','A',	'C','H','I',	'C','H','U',	'C','H','E',	/* 28..2B */
	'C','H','O',	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 2C..2F */
	'T','S','A',	'T','S','I',	'T','S','U',	'T','S','E',	/* 30..33 */
	'T','S','O',	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 34..37 */
	'N','A',  0,	'N','I',  0,	'N','U',  0,	'N','E',  0,	/* 38..3B */
	'N','O',  0,	'N','Y','A',	'N','Y','U',	'N','Y','O',	/* 3C..3F */
	'H','A',  0,	'H','I',  0,	'H','U',  0,	'H','E',  0,	/* 40..43 */
	'H','O',  0,	'H','Y','A',	'H','Y','U',	'H','Y','O',	/* 44..47 */
	'F','A',  0,	'F','I',  0,	'?','?',  0,	'F','E',  0,	/* 48..4B */
	'F','O',  0,	'F','Y','A',	'F','Y','U',	'F','Y','O',	/* 4C..4F */
	'M','A',  0,	'M','I',  0,	'M','U',  0,	'M','E',  0,	/* 50..53 */
	'M','O',  0,	'M','Y','A',	'M','Y','U',	'M','Y','O',	/* 54..57 */
	'Y','A',  0,	'?','?',  0,	'Y','U',  0,	'Y','E',  0,	/* 58..5B */
	'Y','O',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 5C..5F */
	'R','A',  0,	'R','I',  0,	'R','U',  0,	'R','E',  0,	/* 60..63 */
	'R','O',  0,	'R','Y','A',	'R','Y','U',	'R','Y','O',	/* 64..67 */
	'W','A',  0,	'W','I',  0,	'?','?',  0,	'W','E',  0,	/* 68..6B */
	'W','O',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 6C..6F */
	'G','A',  0,	'G','I',  0,	'G','U',  0,	'G','E',  0,	/* 70..73 */
	'G','O',  0,	'G','Y','A',	'G','Y','U',	'G','Y','O',	/* 74..77 */
	'Q','A',  0,	'Q','I',  0,	'Q','U',  0,	'Q','E',  0,	/* 78..7B */
	'Q','O',  0,	'Q','Y','A',	'Q','Y','U',	'Q','Y','O',	/* 7C..7F */
	'Z','A',  0,	'Z','I',  0,	'Z','U',  0,	'Z','E',  0,	/* 80..83 */
	'Z','O',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 84..87 */
	'J','A',  0,	'J','I',  0,	'J','U',  0,	'J','E',  0,	/* 88..8B */
	'J','O',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 8C..8F */
	'D','A',  0,	'D','I',  0,	'D','U',  0,	'D','E',  0,	/* 90..93 */
	'D','O',  0,	'D','Y','A',	'D','Y','U',	'D','Y','O',	/* 94..97 */
	'B','A',  0,	'B','I',  0,	'B','U',  0,	'B','E',  0,	/* 98..9B */
	'B','O',  0,	'B','Y','A',	'B','Y','U',	'B','Y','O',	/* 9C..9F */
	'P','A',  0,	'P','I',  0,	'P','U',  0,	'P','E',  0,	/* A0..A3 */
	'P','O',  0,	'P','Y','A',	'P','Y','U',	'P','Y','O',	/* A4..A7 */
	'V','A',  0,	'V','I',  0,	'V','U',  0,	'V','E',  0,	/* A8..AB */
	'V','O',  0,	'V','Y','A',	'V','Y','U',	'V','Y','O',	/* AC..AF */
	'K','W','A',	'K','W','I',	'?','?',  0,	'K','W','E',	/* B0..B3 */
	'K','W','O',	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* B4..B7 */
	'G','W','A',	'G','W','I',	'?','?',  0,	'G','W','E',	/* B8..BB */
	'G','W','O',	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* BC..BF */
	'-',  0,  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* C0..C3 */
	'?','?',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* C4..C7 */
	/* CF is an uncategorized double consonant at a number conversion. */
	'$',  0,  0,	'$',  0,  0,	'$',  0,  0,	'$',  0,  0,	/* C8..CB */
	'?','?',  0,	'?','?',  0,	'?','?',  0,	'$',  0,  0,	/* CC..CF */
	/* D7 is an uncategorized syllabic nasal at a number conversion. */
	'X',  0,  0,	'X',  0,  0,	'X',  0,  0,	'X',  0,  0,	/* D0..D3 */
	'X',  0,  0,	'?','?',  0,	'?','?',  0,	'X',  0,  0,	/* D4..D7 */
	0																/* STOPPER */
};


#define	CRLF	",((KAIGYO-))."

#ifndef UNONSEI
/*========== ACC_OUTPUT() ==========
	Function: Phonogram data creation
  ==================================*/
void ACC_OUTPUT() {
	register integer_16 i,di;
	integer_16 len,pause,fall,ptr;
	integer_16 precede,current;		/* Pitch of the accent (precede is the pitch of the previous element)*/
	integer_16 question;			/* Indicate whether or not it is a question.*/
	BYTE chr[4];				/* For phonetic symbol */

	di=0;
	chr[3]=0x00;	/* stopper */
	/*
	 *	The maximum number of fall in a phrase is 1.
	 *	The second fall, which the secondary accent, is suppressed in this version.
	 *	A fall is a counter for that.
	 */
	/* Write the beginning of the sentence.*/
	/* di=GEN_OUTPUT_C('[',di); */

	/* To determine the accent fall, memorize the pitch of the previous element.(Default 1)*/
	/* precede=1; fall=0; */
	for(i=0;i<stc_ptr;++i){
		/*ptr=stc_in_ptr[i];*/
		/* Fetch the volume of a pause to be inserted just before it.*/
		pause=stc_pause[i];
		if(pause){
			/* When there is a pause,*/
			/* write the end of the phrase as long as it is not the top of the sentence.*/
			if(i){ di=GEN_OUTPUT_S("))",di); }
			/* Write the beginning of the pause and the phrase.*/
			di=GEN_OUTPUT_S(",((",di);
			precede=1; fall=0;
		}else{
			/* When there is no pause, */
			if(i==0){
				/* write the beginning of the pause if it is the top of the sentence.*/
				di=GEN_OUTPUT_S("((",di);
				precede=1; fall=0;
			}else{
				/* If it is not the top of the sentence,*/
				if(phrase_len[i]){
					if(!(stc_out_len[i]==1 && omega[stc_out_ptr[i]]==0xFF)){
						/* If it is the beginning of the sentence, write ending and beginning of the sentence.*/
						/* However, be aware of the punctuations and special symbols.*/
						/* Ignore the sentence of which length is 1 and the data is 0xFF.*/
						di=GEN_OUTPUT_S(")(",di);
						precede=1; fall=0;
					}
				}
			}
		}

		if((stc_ctl[i] & BITCTL_FIRST) && (stc_stz[i] & BITSTZ_PREF)==0){
			if(i){
				di=ACC_OUTPUT_C(0xFF,di);
			}
		}

		/* Write the syllables of each phrase.*/
		for(ptr=stc_out_ptr[i],len=stc_out_len[i];len--;++ptr){
			current=accent0[ptr] & BITACC_LEVEL;
			if(omega[ptr]!=0xFF){
				/* Convert each phonemes into Roman characters.*/
				code_to_hardchar(omega[ptr],0, chr);
				/* fall==1 A fall is not written because it is the secondary accent.*/
				if(precede==2 && current==1 && fall<1){
					di=GEN_OUTPUT_C(0x27,di); ++fall;
				}
				di=GEN_OUTPUT_S(chr,di);
				precede=question=current;
			}
		}
	}

	/* Write the end of the phrase and the end of the sentence.*/
	/* At the end of a sentence, insert a pause for about 2 mora phonemes regardless of the existence of the punctuation.*/
	if(question==9){
		di=GEN_OUTPUT_S("))?",di);
	}else{
		di=GEN_OUTPUT_S(")).",di);
	}
	di=ACC_OUTPUT_C(0xFF,di);
	di=GEN_OUTPUT_C(0x00,di);
}


integer_16 GEN_OUTPUT_S(str,di)
	register BYTE *str; register integer_16 di;
{
	while(*str){ di=GEN_OUTPUT_C(*str++,di); }
	return di;
}


integer_16 GEN_OUTPUT_C(ch,di)
	BYTE ch; register integer_16 di;
{
	/* speakAvoid an empty segment "()" appearing in brackets [].*/
	if(ch==')'){
		if(speak[di-1]=='('){ --di; return di; }
	}
	if(ch=='.'){
		if(speak[di-1]==','){ --di; }
	}
	if(ch==','){
		if(speak[di-1]!=')'){ return di; }
	}
	di=ACC_OUTPUT_C(ch,di);
	return di;
}

/*========== code_to_hardchar(ch,ac; a) ======================================
	Function: Convert the internal pronunciation codes into half-sized roman characters.
		When ac is 0x80, devoice it.
		When ch is greater than 0xD4, the value is not guaranteed.
		When ch is an abnormal value, return "???".

	Note: When it is unconvertible, 0xD7 and 0xCF before the double consonant and syllabic nasal are categorized are used.
		Be aware of it.However, it is only in number processing.
  ===============================================================================*/
void code_to_hardchar(ch,ac, a) BYTE ch,ac; register BYTE *a; {
	const BYTE* addr;

	addr=(&hardchar_table[ch][0]);
	a[0]=(*addr++); a[1]=(*addr++); a[2]=(*addr);
}

#endif


void code_to_hardchar2(ch,ac, a) BYTE ch,ac; register BYTE *a; {
	const BYTE* addr;

	addr=(&hardchar_table[ch][0]);
	if (*addr)
		a[0]=(*addr++); 
	if (*addr)
		a[1]=(*addr++); 
	if (*addr)
		a[2]=(*addr);
}


/***************************** END OF ILE_GENC.C *****************************/

