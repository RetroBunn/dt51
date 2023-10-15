/*********************************************
	ILE_SUHC.C	updated at 17th April 1990
	Arabic numerals and Kanji numerals conversion
 *********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_envh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_func.h"

static const BYTE SuhwKan[10][2];
static const BYTE SuhwKan2[3][2];
static const BYTE SuhwKurai[19][2];


/*========== DIGIT_CONV(sw) ==================================================
	Function: Convert number string that includes a kanji numerals, Arabic numerals, signs, or decimal points into a kanji numeral string.
		The element before the decimal point is processed as a integer, and the element after the decimal point is read digit by digit.
		ÇPÇOñúÅ®è\ñúÅCÇPÇQÅDÇRÇSÅ®è\ìÒÅDéOél
		In digit-by-digit reading mode, all numbers are read digit by digit.(digit_type =1)
	Input : swÅÅ0: No reading is specified.
		ÇìÇóÅÅÇPÅFRead the numeral as a full number.
		ÇìÇóÅÅÇQÅFRead the numeral digit by digit.
  ============================================================================*/
void DIGIT_CONV(sw) integer_16 sw; {
	register integer_16 ptr,ikind;
	integer_16 cdptr,cdlen,maxlen;
	BYTE *kptr;

	digit_type=0;	/* normal type (integer,fraction) */
	digit_mode=0;	/* convert mode (integer) */
	n_kansuji=0;

	if(sw==1){ goto DIGIT_CONV_200; }
	if(sw==2){ digit_type=1; goto DIGIT_CONV_200; }

	if(onsei_addr->onsei_kouseisystem){
		/* In correction mode, always read numbers digit by digit.--89.11.29-- */
		digit_type=1; goto DIGIT_CONV_200;
	}

	/* When the number string includes a decimal point or comma, it cannot be read digit by digit.*/
	/* The number that can be read digit by digit can only include Arabic numbers and kanji numeral 1 (àÍìÒéOÅcÅZ).*/
	for(ptr=ceptr;ptr<ceptr+celen;++ptr){
		if((inert_kind[ptr]!=CHRKIND_KDigit1)
		&& (inert_kind[ptr]!=CHRKIND_ADigit)){
			/* When any numeric character other than Arabic numerals and kanji numeral 1 is included, do not read it digit by digit.*/
			goto DIGIT_CONV_200;
		}
	}

	/* When - is placed before or/and after a number string, it is read digit by digit.*/
	/* 235-3674, (235)3674, etc.*/
	if((ptr=ceptr-1)!=(-1)){
		ikind=inert[ptr*2]*256+inert[ptr*2+1];
		if(ikind==0x214A || ikind==0x214B || ikind==0x215D){
			digit_type=1;
		}
	}
	if((ptr=ceptr+celen)!=n_inert){
		ikind=inert[ptr*2]*256+inert[ptr*2+1];
		if(ikind==0x214A || ikind==0x214B || ikind==0x215D){
			digit_type=1;
		}
	}

	/* When a number string starts with zero, read it digit by digit.*/
	/* 03, 0990, etc.*/
	ikind=inert[ceptr*2]*256+inert[ceptr*2+1];
	if(ikind==0x213b || ikind==0x2330){	/* ÅZ or ÇO */
		digit_type=1;
	}

DIGIT_CONV_200:;
	ptr=ceptr;

	while(1){
		if(ptr>=ceptr+celen){ return; }

		ikind=inert_kind[ptr];
		if(ikind==CHRKIND_ADigit || ikind==CHRKIND_KDigit1){
			cdptr=ptr; cdlen=1;
			kptr=(&inert_kind[cdptr+cdlen]);
			while(*kptr==CHRKIND_ADigit || *kptr==CHRKIND_KDigit1
			   || *kptr==CHRKIND_DSep){
				++cdlen; ++kptr;
			}
			maxlen=ceptr+celen-cdptr;
			if(cdlen>maxlen){ cdlen=maxlen; }
			DIGIT_CONV1(cdptr,cdlen);
			ptr+=cdlen;
		}else{
			/* if decimal point is found, convert mode changed */
			if(inert_kind[ptr]==CHRKIND_DDP){ digit_mode=1; }
			kansuji[n_kansuji*2]  =inert[ptr*2];
			kansuji[n_kansuji*2+1]=inert[ptr*2+1];
			++n_kansuji; ++ptr;
		}
	}
}


/*========== DIGIT_CONV1(cdptr,cdlen) ==============================
	Input:cdptr					Offset of the character string to be converted
 			cdlen					Number of characters to be converted
			digit_mode				=0 : integer type
									=1 : fraction type
			digit_type				=0 : normal mode
									=1 : Digit-by-digit reading type
	Output:kansuji[]				Conversion result
 			n_kansuji				Number of characters in conversion result
	Function: Convert the current word into a standard number(maximum 20 digits)
			When the number has 20 or more digits, read it digit by digit.Example: àÍìÒéOélå‹
	Note:The input character includes separators (such as a comma) of number string.
  ==================================================================*/
void DIGIT_CONV1(cdptr,cdlen) integer_16 cdptr,cdlen; {
	/*
	 *	len		: length concludes comma
	 *	net_len	: length without comma
	 */
	register BYTE *si; BYTE ah,al;
	register integer_16 len; integer_16 net_len,dx;

	/* Digit-by-digit reading type or fraction type */
	if(digit_mode==1||digit_type==1){ goto DIGIT_CONV1_500; }

	/* One-digit number and the number that has more than 20 digits are read digit by digit.*/
	net_len=0;
	for(dx=0;dx<cdlen;++dx){
		if(inert_kind[cdptr+dx]==CHRKIND_ADigit
		|| inert_kind[cdptr+dx]==CHRKIND_KDigit1){
			++net_len;
		}
	}
	if(net_len>20 || net_len==1){ goto DIGIT_CONV1_500; }

	/* 1. Integer type */
	len=cdlen;						/* Fetch the number of characters to be converted. */
	si=cdptr*2+inert;				/* Fetch the address of the character string to be converted. */

	dx=0;
	do{
		ah=(*si++); al=(*si++);

		/* When it is a kanji numeral, convert it to an Arabic numeral.*/
		DIGIT_CONV2(&ah,&al);
		/* Ignore the characters other than numbers. */
		if(ah!=0x23 || al<0x30 || al>0x39){ goto DIGIT_CONV1_290; }

		/* When there is no characters to be converted */
		if(al==0x30){
			/* Add digit name for "â≠" or "ñú". */
			if((net_len & 3)==1){ if(dx){ goto DIGIT_CONV1_240; } }
			/* When the number of characters to be converted is not 1, do not convert. */
			if(n_kansuji ||(net_len!=1)){ goto DIGIT_CONV1_270; }
		}
		dx++;
		/* When the character to be converted is 1, and it is not hundreds digit or tens digit,  */
		if( (al!=0x31) || ((net_len & 2)==0) ){
			/* look up the table and obtain the number. */
			kansuji[n_kansuji*2  ]=SuhwKan[al-0x30][0];
			kansuji[n_kansuji*2+1]=SuhwKan[al-0x30][1];
			n_kansuji++;				/* Store the conversion result. */
		}
		DIGIT_CONV1_240:
		if(net_len!=1){	/* If it is not ones digit,  */
			/* set the address of the digit conversion table. */
			kansuji[n_kansuji*2  ]=SuhwKurai[net_len-2][0];
			kansuji[n_kansuji*2+1]=SuhwKurai[net_len-2][1];
			n_kansuji++; /* Store the conversion result. */
		}
		DIGIT_CONV1_270:
		if(((net_len & 02)==0) && (net_len & 1)){ dx=0; }
		--net_len;
		DIGIT_CONV1_290:;
	}while(--len);
	return;

/* ÇQÅDDigit-by-digit reading type */
DIGIT_CONV1_500:;
	len=cdlen;						/* Fetch the number of characters to be converted. */
	si=cdptr*2+inert;				/* Fetch the address of the character string to be converted. */
	do{
		ah=(*si++); al=(*si++);

		/* When it is a kanji numeral, convert it to an Arabic numeral.*/
		DIGIT_CONV2(&ah,&al);
		/* Ignore the characters other than numbers. */
		if(ah==0x23 && al>=0x30 && al<=0x39){
			kansuji[n_kansuji*2  ]=SuhwKan[al-0x30][0];
			kansuji[n_kansuji*2+1]=SuhwKan[al-0x30][1];
			n_kansuji++;
		}
	}while(--len);
	return;
}


/*========== DIGIT_CONV2(ah,al) ====================================
	Input:ah,al					Two-byte numeral
	Output:ah,al					Two-byte numeral
	Function: When the number is a kanji numeral, convert it into an Arabic number.
  ==================================================================*/
void DIGIT_CONV2(ah,al) BYTE *ah,*al; {
	integer_16 cx;
	const BYTE* si;
	/* ÅZàÍìÒéOélå‹òZéµî™ã„ */
	for(si= &SuhwKan[0][0],cx=0; cx<10; ++cx,si+=2){
		if(*ah==(*si) && *al==(*(si+1))){
			*ah=0x23; *al=0x30+cx; return;
		}
	}
	/* àÎìÛéQ */
	for(si= &SuhwKan2[0][0],cx=0; cx<3; ++cx,si+=2){
		if(*ah==(*si) && *al==(*(si+1))){
			*ah=0x23; *al=0x31+cx; return;
		}
	}
}

/* Kanji numerals ÅiÅZàÍìÒéOélå‹òZéµî™ã„Åj*/
static const BYTE SuhwKan[10][2]={
	0x21,0x3b,0x30,0x6c,0x46,0x73,0x3b,0x30,0x3b,0x4d,
	0x38,0x5e,0x4f,0x3b,0x3c,0x37,0x48,0x2c,0x36,0x65
};

/* Kanji numerals ÅiàÎìÛéQÅj*/
static const BYTE SuhwKan2[3][2]={
	0x30,0x6d,0x46,0x75,0x3b,0x32
};

/* Digits Åiè\ïSêÁñúè\ïSêÁâ≠è\ïSêÁíõè\ïSêÁãûè\ïSêÁÅj*/ 
static const BYTE SuhwKurai[19][2]={
	0x3d,0x3d,0x49,0x34,0x40,0x69,0x4b,0x7c,
	0x3d,0x3d,0x49,0x34,0x40,0x69,0x32,0x2f,
	0x3d,0x3d,0x49,0x34,0x40,0x69,0x43,0x7b,
	0x3d,0x3d,0x49,0x34,0x40,0x69,0x35,0x7E,
	0x3d,0x3d,0x49,0x34,0x40,0x69
};


/***************************** END OF ILE_SUHC.C *****************************/

