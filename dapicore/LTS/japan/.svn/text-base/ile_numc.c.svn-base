/**********************************************
	ILE_NUMC.C	updated at 1st October 1990
	Processing of number conversion and counter suffixes
 **********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_acch.h"
#include	"ile_edic.h"
#include	"ile_envh.h"
#include	"ile_errh.h"
#include	"ile_idic.h"
#include	"ile_kkhh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"
#include "pkind.h"

/*
 *	(1) Meanings of MAN and EXP
 *		They indicate the mantissa part and the exponent part of a number.
 *		To distinguish "àÍêÁ(ISSEN)" and "êÁ(SEN)," set MAN=1 for àÍêÁ, and set MAN=0 for êÁ.
 *		For "è\(JYUU)" and "ïS(HYAKU)," set MAN=0 as necessary.
 *		For "è\àÍ(JYUU ICHI)" to "è\ã„(JYUUKYU)," process the mantissa part as 11 to 19, and process the exponent part as 1.
 *		The mantissa parts of "êî(SU)," "âΩ(NAN)," and "äÙ(IKU)" are represented as 21, 22, and 23 respectively.
 *		The mantissa parts of marks and decimal points are represented as 65 and 66 respectively, and their exponent as 0.
 *
 *	(2) Because syllabic nasals and double consonants depend on the sound of the succeeding element, process them using the codes 0xD7 and 0xCF.
 *	After they are combined with their counter suffixes, categorize them in DxD0 to DxD4, and 0xC8 to 0xCB.
 */

static const BYTE DPRON_TBL1[]={
	/* JIS    MAN EXP ACC.	   PRON. */	
	0x21,0x3B,  0, 0, 0x01, 0x02,0x83,0x64,		/* ÅZ */
	0x30,0x6C,  1, 0, 0x02, 0x02,0x01,0x29,		/* àÍ */
	0x46,0x73,  2, 0, 0x01, 0x01,0x39,			/* ìÒ */
	0x3B,0x30,  3, 0, 0x00, 0x02,0x10,0xD7,		/* éO */
	0x3B,0x4D,  4, 0, 0x01, 0x02,0x5C,0xD7,		/* él */
	0x38,0x5E,  5, 0, 0x01, 0x01,0x74,			/* å‹ */
	0x4F,0x3B,  6, 0, 0x02, 0x02,0x64,0x0A,		/* òZ */
	0x3C,0X37,  7, 0, 0x01, 0x02,0x38,0x38,		/* éµ */
	0x48,0x2C,  8, 0, 0x02, 0x02,0x40,0x29,		/* î™ */
	0x36,0x65,  9, 0, 0x01, 0x02,0x0E,0xC0,		/* ã„ */
	0x3F,0x74, 21, 0, 0x01, 0x02,0x12,0xC0,		/* êî */
	0x32,0x3F, 22, 0, 0x01, 0x02,0x38,0xD7,		/* âΩ */
	0x34,0x76, 23, 0, 0x01, 0x02,0x01,0x0A,		/* äÙ */

	0x3D,0x3D,  0, 1, 0x01, 0x02,0x8A,0xC0,		/* è\ */
	0x3D,0x26,  0, 1, 0x01, 0x02,0x8A,0xC0,		/* èE */
	0x49,0x34,  0, 2, 0x02, 0x02,0x45,0x0A,		/* ïS */
	0x40,0x69,  0, 3, 0x01, 0x02,0x13,0xD7,		/* êÁ */

	0x4B,0x7C,  0, 4, 0x01, 0x02,0x50,0xD7,		/* ñú */
	0x68,0x5F,  0, 4, 0x01, 0x02,0x50,0xD7,		/* ‰› */
	0x32,0x2F,  0, 8, 0x01, 0x02,0x04,0x0A,		/* â≠ */
	0x43,0x7B,  0,12, 0x01, 0x02,0x2C,0xC0,		/* íõ */
	0x35,0x7E,  0,16, 0x01, 0x02,0x0B,0xC0,		/* ãû */
	
	0x21,0x5C, 65, 0, 0x00, 0x03,0xA2,0x60,0x12,		/* Å{ */
	0x21,0x5D, 65, 0, 0x00, 0x04,0x50,0x01,0x38,0x12,	/* Å| */
	0x21,0x5E, 65, 0, 0x04, 0x07,0xA2,0x60,0x12,0x50,0x01,0x38,0x12,	/* Å} */
	0x21,0x25, 66, 0, 0x01, 0x02,0x23,0xD7,				/* ÅD */

	0xFF										/* STOPPER */
};

static const BYTE DPRON_TBL2[]={
	/*   JIS		    MAN EXP ACC.		  PRON. */
	0x30,0x6C,0x3D,0x26,  2, 1, 0x03, 0x04,0x01,0x29,0x8A,0xC0,	/* àÍèE */
	0x46,0x73,0x3D,0x3D,  2, 1, 0x01, 0x03,0x39,     0x8A,0xC0,	/* ìÒè\ */
	0x46,0x73,0x3D,0x26,  2, 1, 0x01, 0x03,0x39,     0x8A,0xC0,	/* ìÒèE */
	0x3B,0x30,0x3D,0x3D,  3, 1, 0x01, 0x04,0x10,0xD7,0x8A,0xC0,	/* éOè\ */
	0x3B,0x30,0x3D,0x26,  3, 1, 0x01, 0x04,0x10,0xD7,0x8A,0xC0,	/* éOèE */
	0x3B,0x4D,0x3D,0x3D,  4, 1, 0x01, 0x04,0x5C,0xD7,0x8A,0xC0,	/* élè\ */
	0x3B,0x4D,0x3D,0x26,  4, 1, 0x01, 0x04,0x5C,0xD7,0x8A,0xC0,	/* élèE */
	0x38,0x5E,0x3D,0x3D,  5, 1, 0x02, 0x03,0x74,     0x8A,0xC0,	/* å‹è\ */
	0x38,0x5E,0x3D,0x26,  5, 1, 0x02, 0x03,0x74,     0x8A,0xC0,	/* å‹èE */
	0x4F,0x3B,0x3D,0x3D,  6, 1, 0x03, 0x04,0x64,0x0A,0x8A,0xC0,	/* òZè\ */
	0x4F,0x3B,0x3D,0x26,  6, 1, 0x03, 0x04,0x64,0x0A,0x8A,0xC0,	/* òZèE */
	0x3C,0x37,0x3D,0x3D,  7, 1, 0x02, 0x04,0x38,0x38,0x8A,0xC0,	/* éµè\ */
	0x3C,0x37,0x3D,0x26,  7, 1, 0x02, 0x04,0x38,0x38,0x8A,0xC0,	/* éµèE */
	0x48,0x2C,0x3D,0x3D,  8, 1, 0x03, 0x04,0x40,0x29,0x8A,0xC0,	/* î™è\ */
	0x48,0x2C,0x3D,0x26,  8, 1, 0x03, 0x04,0x40,0x29,0x8A,0xC0,	/* î™èE */
	0x36,0x65,0x3D,0x3D,  9, 1, 0x01, 0x04,0x0E,0xC0,0x8A,0xC0,	/* ã„è\ */
	0x36,0x65,0x3D,0x26,  9, 1, 0x01, 0x04,0x0E,0xC0,0x8A,0xC0,	/* ã„èE */
	0x3F,0x74,0x3D,0x3D, 21, 1, 0x01, 0x04,0x12,0xC0,0x8A,0xC0,	/* êîè\ */
	0x32,0x3F,0x3D,0x3D, 22, 1, 0x01, 0x04,0x38,0xD7,0x8A,0xC0,	/* âΩè\ */
	0x34,0x76,0x3D,0x3D, 23, 1, 0x01, 0x04,0x01,0x0A,0x8A,0xC0,	/* äÙè\ */

	0x30,0x6C,0x49,0x34,  2, 2, 0x04, 0x04,0x01,0xC8,0xA5,0x0A,	/* àÍïS */
	0x46,0x73,0x49,0x34,  2, 2, 0x03, 0x03,0x39,     0x45,0x0A,	/* ìÒïS */
	0x3B,0x30,0x49,0x34,  3, 2, 0x01, 0x04,0x10,0xD7,0x9D,0x0A,	/* éOïS */
	0x3B,0x4D,0x49,0x34,  4, 2, 0x01, 0x04,0x5C,0xD7,0x45,0x0A,	/* élïS */
	0x38,0x5E,0x49,0x34,  5, 2, 0x03, 0x03,0x74,     0x45,0x0A,	/* å‹ïS */
	0x4F,0x3B,0x49,0x34,  6, 2, 0x04, 0x04,0x64,0xC8,0xA5,0x0A,	/* òZïS */
	0x3C,0x37,0x49,0x34,  7, 2, 0x02, 0x04,0x38,0x38,0x45,0x0A,	/* éµïS */
	0x48,0x2C,0x49,0x34,  8, 2, 0x04, 0x04,0x40,0xC8,0xA5,0x0A,	/* î™ïS */
	0x36,0x65,0x49,0x34,  9, 2, 0x01, 0x04,0x0E,0xC0,0x45,0x0A,	/* ã„ïS */
	0x3F,0x74,0x49,0x34, 21, 2, 0x01, 0x04,0x12,0xC0,0x45,0x0A,	/* êîïS */
	0x32,0x3F,0x49,0x34, 22, 2, 0x01, 0x04,0x38,0xD7,0x9D,0x0A,	/* âΩïS */
	0x34,0x76,0x49,0x34, 23, 2, 0x01, 0x04,0x01,0x0A,0x45,0x0A,	/* äÙïS */

	0x30,0x6C,0x40,0x69,  1, 3, 0x03, 0x04,0x01,0xC8,0x13,0xD7,	/* àÍêÁ */
	0x46,0x73,0x40,0x69,  2, 3, 0x02, 0x03,0x39,     0x13,0xD7,	/* ìÒêÁ */
	0x3B,0x30,0x40,0x69,  3, 3, 0x03, 0x04,0x10,0xD7,0x83,0xD7,	/* éOêÁ */
	0x3B,0x4D,0x40,0x69,  4, 3, 0x03, 0x04,0x5C,0xD7,0x13,0xD7,	/* élêÁ */
	0x38,0x5E,0x40,0x69,  5, 3, 0x02, 0x03,0x74,     0x13,0xD7,	/* å‹êÁ */
	0x4F,0x3B,0x40,0x69,  6, 3, 0x03, 0x04,0x64,0x0A,0x13,0xD7,	/* òZêÁ */
	0x3C,0x37,0x40,0x69,  7, 3, 0x03, 0x04,0x38,0x38,0x13,0xD7,	/* éµêÁ */
	0x48,0x2C,0x40,0x69,  8, 3, 0x03, 0x04,0x40,0xC8,0x13,0xD7,	/* î™êÁ */
	0x36,0x65,0x40,0x69,  9, 3, 0x03, 0x04,0x0E,0xC0,0x13,0xD7,	/* ã„êÁ */
	0x3F,0x74,0x40,0x69, 21, 3, 0x01, 0x04,0x12,0xC0,0x13,0xD7,	/* êîêÁ */
	0x32,0x3F,0x40,0x69, 22, 3, 0x03, 0x04,0x38,0xD7,0x83,0xD7,	/* âΩêÁ */
	0x34,0x76,0x40,0x69, 23, 3, 0x01, 0x04,0x01,0x0A,0x13,0xD7,	/* äÙêÁ */

	0x4A,0X23,0X3F,0X74, 64, 0, 0x03, 0x04,0x42,0x0A,0x12,0xC0,	/* ï°êî */

	0x3D,0x3D,0x30,0x6C, 11, 1, 0x04, 0x04,0x8A,0xC0,0x01,0x29,	/* è\àÍ */
	0x3D,0x26,0x30,0x6C, 11, 1, 0x04, 0x04,0x8A,0xC0,0x01,0x29,	/* èEàÍ */
	0x3D,0x3D,0x46,0x73, 12, 1, 0x03, 0x03,0x8A,0xC0,0x39,		/* è\ìÒ */
	0x3D,0x26,0x46,0x73, 12, 1, 0x03, 0x03,0x8A,0xC0,0x39,		/* èEìÒ */
	0x3D,0x3D,0x3B,0x30, 13, 1, 0x01, 0x04,0x8A,0xC0,0x10,0xD7,	/* è\éO */
	0x3D,0x26,0x3B,0x30, 13, 1, 0x01, 0x04,0x8A,0xC0,0x10,0xD7,	/* èEéO */
	0x3D,0x3D,0x3B,0x4D, 14, 1, 0x03, 0x04,0x8A,0xC0,0x5C,0xD7,	/* è\él */
	0x3D,0x26,0x3B,0x4D, 14, 1, 0x03, 0x04,0x8A,0xC0,0x5C,0xD7,	/* èEél */
	0x3D,0x3D,0x38,0x5E, 15, 1, 0x01, 0x03,0x8A,0xC0,0x74,		/* è\å‹ */
	0x3D,0x26,0x38,0x5E, 15, 1, 0x01, 0x03,0x8A,0xC0,0x74,		/* èEå‹ */
	0x3D,0x3D,0x4F,0x3B, 16, 1, 0x04, 0x04,0x8A,0xC0,0x64,0x0A,	/* è\òZ */
	0x3D,0x26,0x4F,0x3B, 16, 1, 0x04, 0x04,0x8A,0xC0,0x64,0x0A,	/* èEòZ */
	0x3D,0x3D,0x3C,0x37, 17, 1, 0x03, 0x04,0x8A,0xC0,0x38,0x38,	/* è\éµ */
	0x3D,0x26,0x3C,0x37, 17, 1, 0x03, 0x04,0x8A,0xC0,0x38,0x38,	/* èEéµ */
	0x3D,0x3D,0x48,0x2C, 18, 1, 0x04, 0x04,0x8A,0xC0,0x40,0x29,	/* è\î™ */
	0x3D,0x26,0x48,0x2C, 18, 1, 0x04, 0x04,0x8A,0xC0,0x40,0x29,	/* èEî™ */
	0x3D,0x3D,0x36,0x65, 19, 1, 0x03, 0x04,0x8A,0xC0,0x0E,0xC0,	/* è\ã„ */
	0x3D,0x26,0x36,0x65, 19, 1, 0x03, 0x04,0x8A,0xC0,0x0E,0xC0,	/* èEã„ */

	0xFF														/* STOPPER */
};

static	STZ_STRUCT Stz_PE_SAV;	/* Connection relation Storage area */
static	STZ_STRUCT Stz_CE_SAV;	/* Connection relation Storage area */

/*========== NUMB1000() ==================================================
	Function: Check whether or not the number conversion of the character string from the position ceptr to the number of character celen is available.
	Value: 1 = There is a possibility / 0 = There is no possibility.
  ========================================================================*/
BOOL NUMB1000() {
	BYTE al;
	//register integer_16 ptr;

	/* When the initial abandon word search is specified, no processing is performed.*/
	/*****if(Stz_CE.stz_mru & BITMRU_ABORT)then return 0; fi*****/

	/* If a character that is not a number is included, there is no possibility.*/
	if((al=(BYTE)OTHER2000())==0){ return 0; }
	if(al!=CHRKIND_Digit){ return 0; }

	/*
	 *	When the preceding character is a number, no processing is performed.--- Lie
	 *		ìåãûÇP(TOKYO1), è\éOÇP(JYUU SAN 1), íËêîÇQ(TEISUU 2), ÇQêiêîÇP(NI SHINSUU 1), etc.
	 *		Because the last character of a noun may be a number, 
	 *		it is probably better not to do this check.
	 *	However, for decimal points, this processing is exceptionally performed.In such cases, the decimal point is a delimiter.
	 *	if((ptr=ceptr-1)!=(-1)){
	 *		if((inert_kind[ptr] & 0xF0)==CHRKIND_Digit
	 *		&& (inert_kind[ptr]!=CHRKIND_DDP)){ return 0; }
	 *	}
	 *
	 *
	 * When the preceding character is not a number, the processing is performed.
	 *	if((ptr=ceptr+celen)==n_inert){ return 1; }
	 *	if((inert_kind[ptr] & 0xF0)!=CHRKIND_Digit){ return 1; }
	 *
	 *
	 *	When the preceding character is a number, ----- lie
	 *		When it is è\(JYUU), ïS(HYAKU), êÁ(SEN), ñú(MAN), â≠(OKU), or íõ(CHOU), the processing is performed.	(100 / â≠â~(OKU EN))
	 *		When it is a decimal point, the processing is performed.					ÅiÇRÅ^ÅDÅ^ÇTÅcÅj
	 *		In other cases, the processing is not performed.
	 *	After a number, a word starting with "êî(SUU)," "âΩ(NAN)," or "äÙ(IKU)" follows a number, or when it is a word like "î™åÀ(HACHINOHE)"
	 *	may follow, so this processing should not be performed.
	 *	if(inert_kind[ptr]==CHRKIND_KDigit2){ return 1; }
	 *	if(inert_kind[ptr]==CHRKIND_KDigit4){ return 1; }
	 *	if(inert_kind[ptr]==CHRKIND_DDP){ return 1; }
	 *	return 0;
	 */
	return 1;
}


/*========== NUMB5000(sw) ==================================================
	Function: Store the pronunciation of the number that starts from the current element start position in the output data area.
		The stack operation and sentence position setting are also performed with this routine.
	Note: Because syllabic nasals and double consonants depend on the sound of the succeeding element, process them using the codes 0xD7 and 0xCF.
		After they are combined with their counter suffixes, categorize them in DxD0 to DxD4, and 0xC8 to 0xCB.
	Input : swÅÅ0: No reading is specified.
		swÅÅ1: Read the numeral as a full number.
		swÅÅ2: Read the numeral digit by digit.
  ===========================================================================*/
BOOL NUMB5000(sw) integer_16 sw; {
	const BYTE* tbl;
        BYTE* si;
	integer_16 dman,dexp,frac_len,int_len;
	integer_16 di,bx,cx,dptr,dlen,dptr2,dlen2,dif,dlast_precede;

	if(kkhstat==err){ return 0; }

	int_len=NUM0010();
	frac_len=NUM0020();
	DIGIT_CONV(sw);
	digit_mode=0;		/* reset digit convert mode (to integer) */
	dptr=0;
NUMB5000_100:;
	di=cpron_ptr;
	if((dlen=n_kansuji-dptr)==0){ goto NUMB5000_SUCCESS; }
	if(dlen>2){ dlen=2; }
	dptr2=dptr;	dlen2=dlen;
NUMB5000_200:;
	if(dlen2==1){ tbl=DPRON_TBL1; }else{ tbl=DPRON_TBL2; }
	while(1){
		if(*tbl==0xFF){ goto NUMB5000_NF; }	/* not found */
		si=(&kansuji[dptr2*2]); cx=dlen2*2; dif=0;
		for(;cx--;){
			if(*si-*tbl){ dif++; }
			++si; ++tbl;
		}
		if(dif==0){ goto NUMB5000_F; }			/* found */
		tbl+=3; cx=(*tbl); tbl+=cx+1;
	}
NUMB5000_NF:;										/* NOT FOUND !*/
	if((dlen2=(--dlen))==0){ return 0; }		/* convert disable */
	goto NUMB5000_200;								/* search length 1 */

NUMB5000_F:;										/* FOUND !*/
	stc_ed_ofs[stc_ptr]=pkind_digiti0;
	Stz_CE.stz_dman=(*tbl); ++tbl;
	Stz_CE.stz_dexp=(*tbl);
	stc_ed_ofs[stc_ptr]+=(*tbl); ++tbl;
	if(stc_ed_ofs[stc_ptr]>pkind_digiti3){ stc_ed_ofs[stc_ptr]=pkind_digiti3; }
		/*
		 *	stc_ed_ofs[] =	0..9	 : pkind_digiti0
		 *					10..90	 : pkind_digiti0+1
		 *					100..900 : pkind_digiti0+2
		 *					>=1000	 : pkind_digiti0+3
		 */
	stc_accent_raw[stc_ptr][0]=(*tbl++);			/* basic accent type */
	stc_accent_raw[stc_ptr][1]=0;
	stc_accent_raw[stc_ptr][2]=0;
	/* "(NO)" is pronounced with low pitch except 3.*/
	if(Stz_CE.stz_dman!=3 || Stz_CE.stz_dexp!=0){
		stc_accent_raw[stc_ptr][6]=2;
	}
	dlast_precede=di-1;
													/* move pronunciation data */
	cx=cpron_len=(*tbl++);							/* mora length */

	/* Delimiters such as a comma */
	/* if(cx==0){ dptr+=dlen; goto NUMB5000_100; } */

	for(;cx--;){ di=OMEGA1000(*tbl++,di); }

	if(Stz_CE.stz_dman || Stz_CE.stz_dexp<4 || dptr==0){
		goto NUMB5000_500;
	}

	/* However, in correction mode, output it without any change.--89.12.12-- */
	if(onsei_addr->onsei_kouseisystem){ goto NUMB5000_500; }

	/***********************************************/
	/* For ñú(MAN), â≠(OKU), íõ(CHOU), or ãû(KYOU), combine it with the preceding number. */
	/***********************************************/

	/* When 1(ICHI), 8(HACHI), 10(JYUU), 11(JYUU ICHI), or 18(JYUU HACHI) precedes íõ(CHOU) or ãû(KYOU), it turns to be a double consonants.*/
	if(Stz_CE.stz_dexp!=12 && Stz_CE.stz_dexp!=16){ goto NUMB5000_320; }
	dman=stc_dman[stc_ptr-1];
	dexp=stc_dexp[stc_ptr-1];
	/* For 1(ICHI), 8(HACHI), 10(JYUU), multiples of 10(JYUU), 11(JYUU ICHI), or 18(JYUU HACHI), */
	if(dman==11||dman==18){ goto NUMB5000_310; }		/* 11,18 */
	if(dman>10){ goto NUMB5000_320; }					/* 12..17,19 */
	if(dexp==1){ goto NUMB5000_310; }					/* 10,20..90 */
	if(dexp!=0){ goto NUMB5000_320; }					/* >=100 */
	if(dman==1||dman==8){ goto NUMB5000_310; }			/* 1,8 */
	goto NUMB5000_320;										/* else */
NUMB5000_310:
	omega[dlast_precede]=0xCF;
NUMB5000_320:
	/**
	 **	For 11 to 19, set stz_dexp to 1.
	 **	11 to 19 are exceptions, however, 11ñú(MAN), 11â≠(OKU), and 11íõ(CHOU) can be processed normally.
	 **	if(Stz_PE.stz_dman<=9 && Stz_PE.stz_dexp==0
	 **	&& stc_out_len[stc_ptr-1]>2){
	 **		stc_dman[stc_ptr-1]=2;
	 **		stc_dexp[stc_ptr-1]=1;
	 **		stc_ed_ofs[stc_ptr-1]=pkind_digiti0+1;
	 **	}
	 **/

	/* The accent of the preceding number is flattened, and the following ñú(MAN) is head-high, but â≠(OKU), íõ(CHOU), and ãû(KYOU) are pronounced with low pitch. */
	if(Stz_CE.stz_dexp==4){
		stc_accent_raw[stc_ptr-1][0]=stc_out_len[stc_ptr-1]+1;
	}else{
		/* âΩ(NAN), êî(SUU), äÙ(IKU) + â≠(OKU), íõ(CHOU), ãû(KYOU) are head-high. */
		stc_accent_raw[stc_ptr-1][0] =
			( (stc_dman[stc_ptr-1]>=21 && stc_dman[stc_ptr-1]<=23)
				? 0x01 : stc_out_len[stc_ptr-1] );
	}
	stc_ed_ofs[stc_ptr-1]+=Stz_CE.stz_dexp;
	if(stc_ed_ofs[stc_ptr-1]>pkind_digiti3){
		stc_ed_ofs[stc_ptr-1]=pkind_digiti3;
	}
	stc_dexp[stc_ptr-1]+=Stz_CE.stz_dexp;
	stc_out_len[stc_ptr-1]+=2;

	dptr+=dlen;				/* Next input data position */
	cpron_ptr=di;			/* Store the position of the middle area of output data. */
	/*
	 * For conversion of "éµïSñú(NANA NYAKU MAN)," when "éµïS(NANA HYAKU)" is converted, sent_in_ptr[] 
	 * is set to 3.When "ñú(MAN)" is converted, do not add the length 1 to "ñú(MAN)."
	 *		sent_in_ptr[bx]+=dlen; --- Lie
	 */
	sent_in_ptr[bx]=ceptr+celen;
	sent_out_ptr[sent_ptr]=di;
	memcpy(&Stz_PE,&Stz_CE,sizeof(STZ_STRUCT));
							/* Proceed the word connection related information by one word. */
	goto NUMB5000_100;

NUMB5000_500:
	/*
	 *	10, 50, 60, or 80 that precedes 1 to 9 is flattened.
	 *	In such cases, the ending of 1 to 9 is raised ---- lie
	 *
	 *	if(Stz_CE.stz_dexp==0 && Stz_CE.stz_dman<=9){
	 *		if(stc_dexp[stc_ptr-1]==1){
	 *			switch(stc_dman[stc_ptr-1]){
	 *			case 0: case 5: case 6: case 8:
	 *				stc_accent_raw[stc_ptr-1][0]=0;
	 *				stc_accent_raw[stc_ptr][0]=cpron_len;
	 *			}
	 *		}
	 *	}
	 */
	/*
	 *	For number of digits after decimal point or number to be read digit by digit, 2 and 5 turns to long vowels.
	 *	However, there is only one digit number in decimal place, it does not turn to a long vowel.
	 *	When the number is read digit by digit, the first digit never turns to a long vowel.
	 */
	if((digit_mode==1 && frac_len>1)||(digit_type==1 && int_len>1)){
		stc_ed_ofs[stc_ptr]=pkind_digitf;
		switch(Stz_CE.stz_dman*100+Stz_CE.stz_dexp){
		case 200:
		case 500:
			++cpron_len; di=OMEGA1000(0xC0,di);
		}
	}

	/*
	 *	When there is a decimal point, switch to decimal mode.
	 *	When the number preceding the decimal point is under 10, the number becomes head-high.--- ???
	 *	1, 8, or 10 that precedes a decimal point turns to a double consonant.
	 *	2 or 5 that precedes a decimal point turns to a long vowel.
	 */
	if(Stz_CE.stz_dman==DMANKIND_DP){
		digit_mode=1;
		/* When a number precedes, */
		if(dptr!=0){
			/*if(stc_dexp[stc_ptr-1]==0){ stc_accent_raw[stc_ptr-1][0]=1; }*/

			/* if the number is 1(ICHI), 8(HACHI), 10(JYUU), or a multiple of 10(JYUU), it turns to a double consonant.*/
			/* 11 to 19 are processed in the same way as 1 to 9.*/
			if(stc_dman[stc_ptr-1]<11 || 19<stc_dman[stc_ptr-1]){
				if(stc_dexp[stc_ptr-1]==1){ goto NUMB5000_540; }
			}

			switch(stc_dman[stc_ptr-1]*100+stc_dexp[stc_ptr-1]){
			case 100: case 800: case 1101: case 1801:
				NUMB5000_540:
				/* It turns to a double consonant except in correction mode.--89.12.12-- */
				if(onsei_addr->onsei_kouseisystem==0){
					omega[dlast_precede]=0xCF;
				}
				break;
			/* If it is 2 or 5,  */
			case 200: case 500: case 1201: case 1501:
				/*
				 * for example, the center 5 in "63.5.5" follows a decimal point, so it turns to a long vowel, however,
				 *  it is also precedes a decimal point.To void turning to a long vowel twice, 
				 *  whether or not it has been turned to a long vowel is checked.-- 88.6.13 --
				 */
				if(0xC0!=omega[di-3]){
					omega[di]=omega[di-1]; omega[di-1]=omega[di-2];
					omega[di-2]=0xC0;
					++di;
					stc_out_len[stc_ptr-1]=stc_out_len[stc_ptr-1]+1;
				}
			}
		}
	}

	cpron_ptr=di;			/* Store the position of the middle area of output data. */
	bx=sent_ptr;		 	/* Obtain the sentence number of the middle area of output data. */
	/* Only the top number can be the beginning of the sentence. */
	if(dptr){
		Stz_CE.stz_ctl &= ~BITCTL_FIRST;
	}else{
		Stz_CE.stz_ctl |= BITCTL_FIRST;
	}
	if(dptr==0){			/* Only when dptr == 0, it can be the beginning of the sentence. */
							/* When it is a word that can be the beginning without prefix,  */
		if(StzfAttrAri(Stz_CE,stz_ctl,BITCTL_FIRST)
		&& StzfAttrAri(Stz_CE,stz_stz,BITSTZ_PREF)==0){
			/* if it exceeds the maximum number of sentences that can be output, */
			if(bx>=MAX_SENT){ jp_ERROR(Err_NaibuOVF); }
			/* Proceed the sentence if it is not a prefix. */
			if(ceptr!=0){ bx++; sent_ptr=bx; }
		}
	}
	/* Specify the position of the last character of the sentence with the origin at 1. */
	sent_out_ptr[bx]=di;
	sent_in_ptr [bx]=ceptr+celen;	/*dptr+dlen;*/

	STACK_PUSH();
	/*
	 *	During PUSH processing, ceptr and celen indicate the top of the number string and the total length.
	 *	Be aware that they don't correspond to the PUSH elements.
	 */ 
	dptr+=dlen;				/* Next input data position */
	memcpy(&Stz_PE,&Stz_CE,sizeof(STZ_STRUCT));
							/* Proceed the word connection related information by one word. */
	goto NUMB5000_100;

NUMB5000_SUCCESS:
	FOLLOW_INIT(&Stz_CE);
	ceptr+=celen;
	return 1;
}


/*========== NUMB5XXX(sw) ==================================================
	Function: When the preceding element is a number, save the current element, and reconvert the preceding number.
	Input : swÅÅ0: No reading is specified.
		swÅÅ1: Read the numeral as a full number.
		swÅÅ2: Read the numeral digit by digit.
  ===========================================================================*/
void NUMB5XXX(sw) integer_16 sw; {
	/* When the preceding element is a number, reconvert it.*/
	if(stc_kind[stc_ptr-1]==DICKIND_D){
		/*
		 *	Store he connection information of the number or the element that precedes the number.
		 *
		 *	The information of the number may be changed when the pronunciation of the number is obtained.
		 *	In other words, if an element preceding a number is "ëÊ(DAI), ê}(ZU), or ï\(HYOU),"
		 *	the number is changed to the Kango(Chinese-origin word) connection.
		 *	After NUMB5000() is executed, this Kango connection information is erased.
		 *	Therefore, it is necessary to store the connection information of numbers.
		 *	However, there must be no problem if the processing is rewritten so that the Kango connection of number is performed by 
		 *	NUM5000() instead of FOLLOW().
		 *
		 *	The connection information of the element that follows a number is used immediately below it.
		 */
		memcpy(&Stz_PE_SAV,&Stz_PE,sizeof(STZ_STRUCT));
		memcpy(&Stz_CE_SAV,&Stz_CE,sizeof(STZ_STRUCT));
		edic_page_no_sav=edic_page_no;
		edic_ofs_sav=edic_ofs;
		idic_addr_sav=idic_addr;
		ceptr_sav=ceptr; celen_sav=celen;

		/* Pop the number, and reconvert it.cpron_prtr may vary.*/
		STACK_POP();

		StzfElmKind(&Stz_CE,DICKIND_D);		/* The type of word is to be a numeral.*/
		OTHER_GRCD();						/* Specify the grammar information of the number.*/

		/*
		 * When PE is a prefix, prevent CE from being a delimiter of the sentence.
		 * However, if CTL is damaged, it may be a problem in accent processing, so write it in STZ.
		 *		This information is used for NUMB5000(sw).
		 */
		if(ceptr!=0){
			if(StzfAttrAri(Stz_PE,stz_ctl,BITCTL_PREF)){
				Stz_CE.stz_stz |= BITSTZ_PREF;
			}
		}
		NUMB5000(sw);

		/* Return the connection information of the counter (or element following a number).*/
		edic_page_no=edic_page_no_sav;
		edic_ofs=edic_ofs_sav;
		idic_addr=idic_addr_sav;
		ceptr=ceptr_sav; celen=celen_sav;
		memcpy(&Stz_PE,&Stz_PE_SAV,sizeof(STZ_STRUCT));
		memcpy(&Stz_CE,&Stz_CE_SAV,sizeof(STZ_STRUCT));
		stc_stz[stc_ptr-1]=Stz_PE.stz_stz;
	}
}


/*========== NUM0010() ===============
	Function: Obtain the number of digits in integer portion of a number.
  ====================================*/
integer_16 NUM0010() {
	BYTE *si;
	integer_16 len,cx;

	si=(&inert[ceptr*2]);
	len=0;
	for(cx=celen;cx--;){
		/* Instead of "except a decimal points," "except numbers" is the end condition.*/
		/* This is to recognize the integer portion of "ÇQñú(NI MAN)" as one digit.*/
		/* It is preferable to read it as "NI MAN" not "NII MAN" even in correction mode.*/
		/*if(*si==0x21 && *(si+1)==0x25){ goto NUM0010_200; }*/
		if(*si!=0x23 || *(si+1)<0x30 || *(si+1)>0x39){ goto NUM0010_200; }
		++len; si+=2;
	}
NUM0010_200:;
	return len;
}


/*========== NUM0020() ===============
	Function: Obtain the number of digits in fractional portion of a number.
  ====================================*/
integer_16 NUM0020() {
	BYTE *si;
	integer_16 len,cx;

	si=(&inert[(ceptr+celen-1)*2]);
	len=0;
	for(cx=celen;cx--;){
		if(*si==0x21 && *(si+1)==0x25){ goto NUM0020_200; }
		++len; si-=2;
	}
NUM0020_200:;
	if(cx==-1){ len=0; }
		/* Because cs-- is specified in for statement, after it passes {, cx becomes -1.*/
	return len;
}


/*========== DIGIT7000() =====================
	Function: Examine the mutual effects of a number + a counter suffix
  ============================================*/
void DIGIT7000() {
	BYTE acc3,acc4,acc5;
	register integer_16 sp_d,sp_n;
	integer_16 dptr,dlen,nptr,nlen,dlast,dman,dexp,ln,di,l;
	integer_16 complex;	/* Set 1 to a compound number.*/

	/* integer_16	sent_in_ptr[MAX_SENT];				 input character position */
	/* integer_16	sent_out_ptr[MAX_SENT];				 output character position */
	/* BYTE			stc_accent_raw[MAX_STACK][10];		 raw accent data */
	/* BYTE			inert[MAX_INERT*2];					 inert data */
	/* BYTE			omega[MAX_OMEGA];					 pronunciation data */

	sp_d=stc_ptr-2;		/* stack pointer for digit */
	sp_n=stc_ptr-1;		/* stack pointer for numerator */

	stc_dman[sp_n] = DMANKIND_NUM;			/*counter suffix*/

	/* In correction mode, no processing is performed.--89.12.12-- */
	/* However, stc_dman[sp_n] needs to be specified.*/
	if(onsei_addr->onsei_kouseisystem){ return; }

	dptr=stc_out_ptr[sp_d]; dlen=stc_out_len[sp_d];
	nptr=stc_out_ptr[sp_n]; nlen=stc_out_len[sp_n];
	/*DKIND=stc_dman[sp_d]*100+stc_dexp[sp_d];*/
	acc3=stc_accent_raw[sp_n][2];
	acc4=stc_accent_raw[sp_n][3];
	acc5=stc_accent_raw[sp_n][4];
	dlast=dptr+dlen-1;
	dman=stc_dman[sp_d];
	dexp=stc_dexp[sp_d];

	/* When the number is 1000 or larger, no processing is performed.*/
	if(dexp>=3){ return; }

	/* Processing for when the number is 10 to 90, êîè\(SUU JYUU), êîïS(SUU HYAKU), 100 to 900,  */
	/* dexp==1 && dman>=11 && dman<=19Exclude it.*/
	/* The last syllable of 100 to 900 is changed to a double consonant only when it is in 5- or 6-type.*/
	if((dexp==1 && (dman<10||dman==21||dman==22||dman==23))
	|| (dexp==2 && (acc3==5||acc3==6))){
		/* Changing the last syllable of the number to a double consonant */
		if(acc3>=1 && acc3<=6){ omega[dlast]=0xCF; }
		/* Changing the top syllable of the counter suffix (turning to PA line)*/
		if(acc5>=2 && acc5<=7){ DIGIT7020(&omega[nptr]); }
		return;
	}
	/* For 100 to 900 which are not changed to double consonants, no processing is performed.*/
	if(dexp==2){ return; }


	/***********************************************************************
		In the following coding, "if(stc_out_len[sp_d]--2)[" is 
	in comment, because the basic numerals include not only 
	single 1 to 9 but also single 11 to 19, such as 1, 11, 2, 13, 3, and 13.
		However, ==When acc4 == 1, the change does not apply to 11 to 19.
	************************************************************************/

	/*
	 * Numbers except 1 to 9 are recognized as compound numbers.11 to 19, or 9801, etc.
	 * "ÇPî†" should be pronounced as "HITOHAKO," BUT "ÇPÇPî†" OR "ÇPÇOÇPî†" should be pronounced as "-- ICHI HAKO"?
	 *			-- How should it be handled?
	 * In "24éû" and "24éûä‘," 4 is pronounced as YO.
	 */
	complex=((stc_ptr>2)&&(stc_kind[stc_ptr-3]==DICKIND_D))||(dman>10);

	/* Processing for when the number is 1 to 9 or 11 to 19 */
	switch(dman){
	case 1:
	case 11:
		/* Changes in reading of the number */
		/*if(1==acc4 && 1==dman){*/
		if(1==acc4 || 2==acc4){
			if(!complex){
				/* "ICHI" -> "HITO" */
				omega[dlast-1]=0x41; omega[dlast]=0x24;
			}
		}else{
			/* Changing the last syllable of the number to a double consonant ($7).This, of course, does not apply to "HITO."*/
			switch(acc3){
			case 2: case 4: case 5: case 6:
				omega[dlast]=0xCF;
			}
			/* Changing the first syllable in the counter suffix into PA line. */
			switch(acc5){
			case 2: case 3: case 5: case 6:
				DIGIT7020(&omega[nptr]);
			}
		}
		break;
	case 2:
	case 12:
		/* Changes in reading of the number */
		/* 2 that is changed to a long vowel, for example it in fractional portion, is not applicable.*/
		/*if(acc4==1 && omega[dlast]!=0xC0){*/
		/*if(1==acc4 && 2==dman){*/
		if(1==acc4 || 2==acc4){
			if(!complex){
				/* "NI" -> "FUTA" */
				stc_out_len[sp_d]++; stc_out_ptr[sp_n]++;
				di=cpron_ptr;
				ln=stc_out_len[sp_n];
				for(l=0;l<ln;++l){ omega[di-l]=omega[di-l-1]; }
				omega[dlast]=0x42; omega[dlast+1]=0x20;
				sent_out_ptr[sent_ptr]++;
				cpron_ptr++;
			}
		}
		break;
	case 3:
	case 13:
		/* Changes in reading of the number */
		/*if(1==acc4 && 3==dman){*/
		if(1==acc4){
			if(!complex){
				/* "SAN" -> "MI" */
				stc_out_len[sp_d]--; stc_out_ptr[sp_n]--;
				ln=stc_out_len[sp_n]; di=cpron_ptr;
				omega[dlast-1]=0x51;
				for(;ln;--ln){ omega[di-ln-1]=omega[di-ln]; }
				sent_out_ptr[sent_ptr]--;
				cpron_ptr--;
				stc_accent_raw[sp_d][0]=1;
			}
		}else{
			/* Changing the first syllable in the counter suffix */
			switch(acc5){
			case 1:								/* Changing to voiced consonant */
				DIGIT7010(&omega[nptr]); break;
			case 4: case 5: case 6: case 7:		/* BA line */
				DIGIT7030(&omega[nptr]); break;
			case 2: case 3:						/* PA line */
				DIGIT7020(&omega[nptr]);
			}
		}
		break;
	case 4:
	case 14:
		/* Changes in reading of the number */
		/*if(7==acc3 || 11==acc3 || (1==acc4 && 4==dman)){*/
		if(7==acc3 || 11==acc3 || 1==acc4){
			if(1==acc4 && complex){ break; }
			/*delete*if(!complex){*/
				/* "YON" -> "YO" */
				stc_out_len[sp_d]--; stc_out_ptr[sp_n]--;
				ln=stc_out_len[sp_n]; di=cpron_ptr;
				for(;ln;--ln){ omega[di-ln-1]=omega[di-ln]; }
				sent_out_ptr[sent_ptr]--;
				cpron_ptr--;
				/* The basic accent of either 4 or 14 is 1 (head-high).*/
				stc_accent_raw[sp_d][0]=1;
			/*}*/
		}else{
			/* Changing the first syllable in the counter suffix */
			switch(acc5){
			case 2: case 3:
				DIGIT7020(&omega[nptr]); break;		/* P */
			case 7:
				DIGIT7030(&omega[nptr]);			/* B */
			}
		}
		break;
	case 6:
	case 16:
		/* Changing the last syllable of the number to a double consonant ($7).*/
		switch(acc3){
		case 3: case 5: case 6:
			omega[dlast]=0xCF;
		}
		/* Changing the first syllable in the counter suffix into PA line. */
		switch(acc5){
		case 2: case 3: case 4: case 5: case 6: case 7:
			DIGIT7020(&omega[nptr]);
		}
		break;
	case 7:
	case 17:
		/* Changes in reading of the number */
		switch(acc3){
		case 8: case 10: case 11:
			/*delete*if(!complex){*/
				/* "NANA" -> "SHICHI" */
				ln=stc_out_len[sp_n]; di=cpron_ptr;
				omega[dlast-1]=0x19; omega[dlast]=0x29;
				/* The basic accent of 7 is 2 (raised-ending), and 17 is 4 (raised-ending).*/
				stc_accent_raw[sp_d][0]=(7==dman ? 2:4);
			/*delete*}*/
		}
		break;
	case 8:
	case 18:
		/* Changing the last syllable of the number to a double consonant ($7).*/
		switch(acc3){
		case 4: case 6:
			omega[dlast]=0xCF;
		}
		/* Changing the first syllable in the counter suffix into PA line. */
		switch(acc5){
		case 3: case 6:
			DIGIT7020(&omega[nptr]);
		}
		break;
	case 9:
	case 19:
		/* Changes in reading of the number */
		switch(acc3){
		case 9: case 10: case 11:
			/*delete*if(!complex){*/
				/* "KYUU" -> "KU" */
				stc_out_len[sp_d]--; stc_out_ptr[sp_n]--;
				ln=stc_out_len[sp_n]; di=cpron_ptr;
				omega[dlast-1]=0x0A;
				for(;ln;--ln){ omega[di-ln-1]=omega[di-ln]; }
				sent_out_ptr[sent_ptr]--;
				cpron_ptr--;
				/* The basic accent of either 9 or 19 is 1 (head-high).*/
				stc_accent_raw[sp_d][0]=1;
			/*delete*}*/
		}
		break;
	}
}


/*========== DIGIT7010(ch) ===================================
	Function: Changing ch to voiced consonant.
  ============================================================*/
void DIGIT7010(ch) register BYTE *ch; {
	switch(*ch & 0xF8){
	case 0x08:	*ch=(*ch & 0x07) | 0x78; break;		/* KA --> QA */
	case 0x10:	*ch=(*ch & 0x07) | 0x80; break;		/* SA --> ZA */
	case 0x18:	*ch=(*ch & 0x07) | 0x88; break;		/* SHA --> JA */
	case 0x28:	*ch=(*ch & 0x07) | 0x88; break;		/* CHA --> JA */
	case 0x20:	*ch=(*ch & 0x07) | 0x90; break;		/* TA --> DA */
	case 0x40:	*ch=(*ch & 0x07) | 0x98; break;		/* HA --> BA */
	case 0x68:	*ch=(*ch & 0x07) | 0x98; break;		/* WA --> BA */
	}
}


/*========== DIGIT7020(ch) ===================================
	Function: Changing ch to P.
  ============================================================*/
void DIGIT7020(ch) register BYTE *ch; {
	switch(*ch & 0xF8){
	case 0x40: case 0x68:
		*ch=(*ch & 0x07) | 0xA0;	/* HA,WA --> PA */
	}
}


/*========== DIGIT7030(ch) ===================================
	Function: Changing ch to B.
  ============================================================*/
void DIGIT7030(ch) register BYTE *ch; {
	switch(*ch & 0xF8){
	case 0x40: case 0x68:
		*ch=(*ch & 0x07) | 0x98;	/* HA,WA --> BA */
	}
}


/***************************** END OF ILE_NUMC.C *****************************/

