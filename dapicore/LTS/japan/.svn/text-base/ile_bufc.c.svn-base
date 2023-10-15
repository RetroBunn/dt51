/*********************************************
	ILE_BUFC.C	updated at 24th April 1990
	Subroutines
 *********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_acch.h"
#include	"ile_fddh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_func.h"


/*========== get_case(p) ====================================
	Function: Refer to the case determining table for the back-end number of the pth element.
	Value: A value (8 bits) in the case determining table.
  ===========================================================*/
WORD get_case(p) register integer_16 p; {
	register integer_16 i;
	WORD bno;

	for(i=0;i<stc_nbno[p];++i){
		if(bno=stc_bno[p][i]){ goto get_case_200; }
	}
get_case_200:;
	return FddHDR[Fdd_Header.Fdd_BnoTblOfs+bno-1];
}


/*========== chk_heiban(p) =====================
	Function: Check whether or not the pth element is flattened type.
	Value: When it is flattened type, set 1. Otherwise, set 0.
  ==============================================*/
BOOL chk_heiban(p) integer_16 p; {
	register integer_16 pp,pl;

	pp=phrase_ptr[p]; pl=phrase_len[p];
	if((pl>1 && accent0[pp+pl-1]==2)||(pl==1 && accent0[pp]==1)){
		return 1;
	}else{
		return 0;
	}
}


/*========== chk_odaka(p) ======================
	Function: Check whether or not the pth element is raised-ending type.
	Value: When it is raised-ending type, set 1. Otherwise set 0.
  ==============================================*/
BOOL chk_odaka(p) register integer_16 p; {
	register integer_16 pl;

	pl=phrase_len[p];
	if(pl>1 && accent0[phrase_ptr[p]+pl-1]==0x82){
		return 1;
	}else{
		return 0;
	}
}


/*========== chk_separator(i) =====================
	Function: Check whether or not the ith character is a special symbol type.
	Value:  When it is a special symbol, set the character code. Otherwise, set 0.
  =================================================*/
WORD chk_separator(i) register integer_16 i; {
	BYTE ch;
	register integer_16 ptr;

	ptr=stc_in_ptr[i];
	/* If an element contains two or more characters, it cannot be a special symbol.*/
	if(stc_out_len[i]!=1){ return 0; }
	ch=inert_kind[ptr];
	/* If a decimal point functions as a period, it is recognized as a special symbol.(3 (SAN) / . / 6êlÇ™Åc (ROKUNINGA---))*/
	if(ch==CHRKIND_DDP){ return(0x2125); }
	ch &= 0xF0;
	if(ch==CHRKIND_Other1||ch==CHRKIND_Other2){
		return((inert[ptr*2]<<8) | inert[ptr*2+1]);
	}
	return 0;
}


/*========== next_phrase(i) =================
	Function: Obtain the number of the phrase next to the ith phrase.
	Value: When there is the next phrase, set the phrase number. Otherwise, set 0.
  ===========================================*/
integer_16 next_phrase(i) register integer_16 i; {
	register integer_16 j;

	for(j=i+1;j<stc_ptr;++j){
		if(phrase_len[j]>0){ return j; }
	}
	return 0;
}


/*========== net_phrase_in_len(i) =================
	Function: Obtain the number of the input characters of the ith phrase.
	Value: Number of input characters
  =================================================*/
integer_16 net_phrase_in_len(i) integer_16 i; {
	integer_16 j;
	register integer_16 len;

	len=((j=next_phrase(i))? stc_in_ptr[j]:n_inert) - stc_in_ptr[i];
	return len;
}


/*========== knj_number(i) =================
	Function: Obtain the number of kanji characters of the ith phrase.
	Value: Number of kanji characters
  ==========================================*/
integer_16 knj_number(i) integer_16 i; {
	integer_16 j,knj;
	register integer_16 ptr,len;

	len=((j=next_phrase(i))? stc_in_ptr[j]:n_inert)-(ptr=stc_in_ptr[i]);
	for(knj=0;len--;ptr++){
		if(inert_kind[ptr]==CHRKIND_Kanji){ ++knj; }
	}
	return knj;
}


/*========== chk_value(AL,SI,CX) ====================================================
	Sentence structureÅFPTR = chk_value(AL,SI,CX);
		In such cases, SI[PTR - 1] = AL.
	Function: Check whether or not the element AL is included in the byte sequence SI[] of the size CX.
	Return value: When it is 0, no attribute exists.
		Otherwise, it indicates the position of the element equal to AL with the origin at 1.
  ===================================================================================*/
integer_16 chk_value(AL,SI,CX) register BYTE *SI; BYTE AL; register integer_16 CX; {
	for(;CX--;){ if(SI[CX]==AL){ return (CX+1); } }
	return 0;
}


/*========== chk_limits(LL,UL,SI,CX) ===================================================
	Sentence structure: PTR = chk_limits(LL,UL,SI,CX);
		In such cases, LL ÅÖ SI[PTR - 1] ÅÖ UL.
	Function: Check whether or not the element between LL and UL is included in the byte sequence SI[] of the size CX.
	Return value: When it is 0, no attribute exists.Otherwise, it indicates the position of the element between LL to UL with the origin at 1.
  ======================================================================================*/
integer_16 chk_limits(LL,UL,SI,CX) register BYTE *SI; BYTE LL,UL; register integer_16 CX; {
	for(;CX--;){
		if(SI[CX]>=LL && SI[CX]<=UL){ return (CX+1); }
	}
	return 0;
}


/*========== is_zengo_kanji(i) =================================================
	Function: Check whether or not the either or both preceding and succeeding characters of ith character are kanji characters.
	Value: ÅÅ0: Neither of them is a kanji character.
		ÅÅ1: Either of them is a kanji character.
  ==============================================================================*/
BOOL is_zengo_kanji(ptr) integer_16 ptr; 
{
	register BYTE *si;
	register integer_16 ptr2;
	
	if((ptr2=ptr-1)!=(-1))
	{
		si=inert+ptr2*2;
		/*ax=(*si<<8)|*(si+1); if(ax>0x3000){ return 1; }*/
		if(*si>=0x30){ return 1; }
	}
	if((ptr2=ptr+1)!=n_inert)
	{
		si=inert+ptr2*2;
		/*ax=(*si<<8)|*(si+1); if(ax>0x3000){ return 1; }*/
		if(*si>=0x30){ return 1; }
	}
	return 0;
}


/*========== before_ch_ptr(i) ================================
	Function: Obtain the position of the preceding character of the ith character.
	Value: When there is a preceding character, set the position of the character. Otherwise, set -1.
		Because the character position is indicated with the origin at 0, the value can be 0.
	integer_16 before_ch_ptr(i) register integer_16 i; {
		--i;
		return i;
	}
  ============================================================*/

/*========== next_ch_ptr(i) ======================
	Function: Obtain the position of the succeeding character of the ith character.
	Value: When there is a succeeding character, set the position of the character. Otherwise, set -1.
	integer_16 next_ch_ptr(i) register integer_16 i; {
		++i;
		if(i==n_inert){ return -1; }
		return i;
	}
  ================================================*/

/*========== first_char_ptr(i) =========================
	Function: Obtain the position of the top character of the ith phrase.
	Value: Position of the top character
	integer_16 first_char_ptr(i) integer_16 i; {
		return stc_in_ptr[i];
	}
  ======================================================*/

/*========== first_or_not(i) =====================
	Function: Check whether or not the ith character is the top character or not.
	Value: When it is the top character, set 1. Otherwise, set 0.
	BOOL first_or_not(i) integer_16 i; {
		return (i==0);
	}
  ================================================*/

/*========== last_or_not(i) ======================
	Function: Check whether or not the ith character is the last character.
	Value: When it is the last character, set 1. Otherwise, set 0.
	BOOL last_or_not(i) integer_16 i; {
		return (i==n_inert-1);
	}
  ================================================*/

/***************************** END OF ILE_BUFC.C *****************************/

