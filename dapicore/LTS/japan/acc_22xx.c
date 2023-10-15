/***********************************************
	ACC_22XX.C	updated at 22th January 1990
	Accent combining routine except for numerals
 ***********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_acch.h"
#include	"ile_fddh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"
#include "pkind.h"
#include "ile_accd.h"

/*========== ACC22XX(i,j) ====================================
	Function: Out of two adjacent elements in accent combination,
		it examines the effect of the succeeding element on the preceding one and the changes of the succeeding element.
  ============================================================*/
void ACC22XX(i,j,a21,a22) integer_16 i,j; register WORD a21,a22; {

	/* When the effect on the preceding one corresponds to A, it is processed in first.*/
	if(a21==10)
	{ 
		ACC221A((integer_16)(j-1)); 
	}

	switch(a22){
	case  1:	ACC2221(j); break;
	case  3:	ACC0001(j); break;
	case  4:	ACC0005(j); break;
	case  5:	ACC2225(j); break;
	case  6:	ACC2226(i,j); break;
	case  7:	ACC2225(j); break;
	case  8:	ACC0004(j); break;
	case 10:	ACC222A(i,j); break;
	case 11:	ACC222B(i,j); break;
	case 12:	ACC222C(i,j); break;
	case 14:	ACC222E(i,j); break;
	case 101:	ACC222Z(j); break;		/* When the succeeding one is a compound noun */
	}

	switch(a21){
	case  1:	ACC000H(i); break;
	case  2:	ACC0002(i); break;
	case  3:	ACC2213(i); break;
	case  4:	ACC2214(i); break;
	case  6:	ACC2216(i,j); break;
	case  7:	ACC2217(i,j); break;
	case  8:	ACC0001(i); break;
	case  9:	ACC2219(i); break;

	/*case 10:	ACC221A(i); break;		Ｔ．Ｂ．Ｄ．*/
	/*case 11:	ACC221B(i); break;		Ｔ．Ｂ．Ｄ．*/

	}
}

/****************************************************************************/
/*																			*/
/*			The following describes the accent combining routine except for numerals.					*/
/*																			*/
/****************************************************************************/

/*========== ACC22CV(p,q) ==================================
	Function: It determines the accents of compound nouns and compound adjectives.

	　The preceding word is flattened, and the succeeding word is pronounced with high pitch and falls itself.
	　However, if the succeeding one is a flattened-type verb, the pitch of the ending of the word is raised.
  ==========================================================*/
void ACC22CV(p,q) integer_16 p; register integer_16 q; {
	register integer_16 qp;
	integer_16 r,bno;

	ACC000H(p);
	qp=phrase_ptr[q];
	if(phrase_kind[q]==pkind_adj_stem){ goto ACC22CV_200; }
	/* When the word is a flattened-type verb, it is pronounced with high pitch, and the ending is raised.*/
	if(chk_heiban(q)){ ACC0002(q); }
ACC22CV_200:
	/* When the word is an up-and-down type verb or adjective, it is pronounced with high pitch and falls itself.*/
	if(accent0[qp]==1){ accent0[qp]=2; }

	/*
	 *	 When a compound declinable word is nominalized, it is usually flattened.
	 * When it is converted into a verb, the ending is usually raised.
	 *	 Therefore, examine the first of the back-end number of the succeeding declinable word,
	 * and check whether the declinable word is a noun or not.
	 *	(Example)  UGOKIHAJIMEWA --- noun
	 *			UGOKIHAJIMETA --- verb
	 *			UGOKIHAJIMETE --- verb
	 */
	if(r=next_phrase(q)){
		--r;
		/*
		 * r indicates the element that locates immediately before the next segment.
		 * "SHI" in "UGOKIDASHI"r=q+1
		 * "HAJIME" in "UGOKIHAJIME"r=q
		 */
		for(bno=0;bno<stc_nbno[r];++bno){
			if(bno=stc_bno[r][bno]){ goto ACC22CV_590; }
		}
	}
ACC22CV_590:
	/*
	 * The back-end number of "始め (HAJIME)" in "動き始めは (UGOKIHAJIMEWA)" or "動き始めが (UGOKIHAJIMEGA)" is 7.
	 * The back-end number of "始め (HAJIME)" in "動き始める (UGOKIHAJIMERU)" or "動き始めた (UGOKIHAJIMETA)" is 47.
	 * When the back-end number is 7, it is recognized as a nominal form, and when the back-end number is 47, it is recognized as declinable word form.
	 */
	if(bno_tbl[bno]==pkind_noun){
		/* When it is in nominal form, it is flattened.*/
		ACC0005(q);
	}
}

/****************************************************************************/
/*																			*/
/*		The effects on the preceding element when the accents are combined.				*/
/*																			*/
/****************************************************************************/

/*========== ACC2213(p) ====================================================
	Function: The ending of the pth element is raised. If the last syllable of the word is a double vowel, the pitch of the syllable is lowered.
			(Example) The pitch of "い (I)" in "けいざい (KEIZAI)" of "経済＋部 (KEIZAI + BU)" falls.
  ==========================================================================*/
void ACC2213(p) integer_16 p; {
	register integer_16 pp,pl;
	pp=phrase_ptr[p]; pl=phrase_len[p];
	ACC0002(p);
	/*
	 * When the last syllable is a double vowel, the accent point is moved by one syllable.
	 * The way to distinguish double vowels is as follows.
	 *	The element has two or more syllables, the last syllable is "イ (I)," and
	 *	the previous syllable is not a double consonant, syllabic nasal, or long vowel.
	 */
	if(pl>1 && omega[pp+pl-1]==0x01 && omega[pp+pl-2]<0xC0){
		accent0[pp+pl-1]=1; accent0[pp+pl-2]=0x82;
	}
}

/*========== ACC2214(p) ===============================
	Function: When the pth element is not flattened type, the pitch of the ending is raised.
		When the last syllable of the word is "イ (I)" of a double vowel, the pitch of the syllable is lowered.
  =====================================================*/
void ACC2214(p) integer_16 p; {
	register integer_16 pp,pl;
	/*if((pl>1 && accent0[pp+pl-1]==2)||(pl==1 && accent0[pp]==1)){*/
	if(chk_heiban(p)==0){
		pp=phrase_ptr[p]; pl=phrase_len[p];
		ACC0002(p);
		/*
		 * When the last syllable is "イ (I)" of a double vowel, the accent point is moved by one syllable.
		 * The way to distinguish double vowels is as follows.
		 *	The element has two or more syllables, the last syllable is "イ (I)," and
		 *	the previous syllable is not a double consonant, syllabic nasal, or long vowel.
		 */
		if(pl>1 && omega[pp+pl-1]==0x01 && omega[pp+pl-2]<0xC0){
			accent0[pp+pl-1]=1; accent0[pp+pl-2]=0x82;
		}
	}
}

/*========== ACC2216(p) ========================================================
	Function: When the ending of the pth element is raised, the fall of the accent is moved to one previous syllable.
		However, the accent of one-syllable head-high type word is not moved. (よい (YOI))
		If the second syllable from the stem of the word is a double consonant, the accent is not moved. (すっぱい (SUPPAI))

		(Example) 青い (AOI) 青く (AOKU) 良い (YOI) 良く (YOKU)

		(1)	動きた「く」 (UGOKITA"KU") 動きよ「く」 UGOKIYO"KU":　The accent is not moved to the previous syllable.
		(2)	書い「て」 (KAI"TE")					：　The accent moves to the previous syllable.
		(3)	動き／良「く」 (UGOKI/YO"KU")				：	The accent is not moved to the previous syllable.

		For (1), consider the forth bit of the flag 2.

		updated 87/9/7
  ==============================================================================*/
void ACC2216(p,q) integer_16 p,q; {
	register integer_16 pp,pl;
	integer_16 pls;
	pp=phrase_ptr[p]; pl=phrase_len[p];
	/*
	 * 「～/し/よ/く」 (~/SHI/YO/KU), 「動/き/よ/く」 (UGO/KI/YO/KU):  Whether or not the preceding element is a one-syllable word
	 *　is determined by the element before combined.
	 */
	/*
	 *	The accent of one-syllable word that could be the head of a string does not move forward.
	 *	The accent of one-syllable word that could not be the head of a string moves forward.
	 */
	pls=stc_out_len[q-1];			/* Length of the previous element */

	/*
	 * (Past) When the length of the (q-1)th element string is 3 or longer, and the second syllable is a double consonant, the accent does not move.
	 * (Now)  When the 57th column is 1, the accent does not move.
	 *		(Example)  すっぱい (SUPPAI) -> すっぱく (SUPPAKU)
	 *			　動きたい (UGOKITAI) -> 動きたく (UGOKITAKU)
	 */
	/*if(pl>=3 && (omega[pp+pl-2] & 0xF8)==0xC8){ return; }*/
	/*if(stc_accent_raw[p][6]==1){ return; }*/
	if(stc_accent_raw[q-1][6]==1){ return; }

	/* When the fourth bit of the flag 2 is 1, the accent does not move.*/
	if(stc_f2[q-1] & BITFLG2_AUX){ return; }
	/* When the element is one-syllable word and it could be the head of a string, the accent does not move.*/
	if(pls==1 && (stc_ctl[q-1] & BITCTL_FIRST)){ return; }
	/* The accent does not move unless the ending is raised.*/
	if(accent0[pp+pl-1]!=0x82){ return; }

	/* When the word could be the head of a string and has two or more syllables, and its ending is raised, the accent moves.*/
	/* When the word could not be the head of a string and has one or more syllables, and its ending is raised, the accent moves.*/
	if(pp+pl>1){
		accent0[pp+pl-2]=0x82; accent0[pp+pl-1]=1;
	}
}

/*========== ACC2217(p,q) ============================================
	Function: When the ending of the pth element is raised, the fall of the accent is moved to one previous syllable.
		When the element is a flattened type word, the ending is raised.
		However, it does not move the accent of one-syllable head-high type. (YO I)
		If the second syllable from the stem of the word is a double consonant, the accent is not moved. (すっぱい (SUPPAI))

		(Example)  青い (AOI) 青かった (AOKATTA) 良い (YOI) 良かった (YOKATTA)
  ====================================================================*/
void ACC2217(p,q) integer_16 p,q; {
	register integer_16 pp,pl;
	integer_16 pls;
	pp=phrase_ptr[p]; pl=phrase_len[p];
	/*
	 *	「～/られ/た/かっ/た」 (~/RARE/TA/KAT/TA), 「～し/た/かっ/た」 (~SHI/TA/KAT/TA):  Whether or not the preceding element is one-syllable word
	 *	is determined by the element before combined.
	 */
	pls=stc_out_len[q-1];
	/* When the element is a flattened type word, the ending is raised.*/
	if((pls>1 && accent0[pp+pl-1]==2)||(pls==1 && accent0[pp]==1)){
		ACC0002(p); return;
	}
	/*
	 * (Past) When the length of the (q-1)th element string is 3 or longer, and the second syllable is a double consonant, the accent does not move.
	 * (Now)  When the 57th column is 1, the accent does not move.
	 *		(Example)  すっぱい (SUPPAI) -> すっぱかった (SUPPAKATTA)
	 */
	/*if(pl>=3 && (omega[pp+pl-2] & 0xF8)==0xC8){ return; }*/
	if(stc_accent_raw[q-1][6]==1){ return; }

	/* When the fourth bit of the flag 2 is 1, the accent does not move.*/
	if(stc_f2[q-1] & BITFLG2_AUX){ return; }
	/* When the element is one-syllable word and it could be the head of a string, the accent does not move.*/
	if(pls==1 && (stc_ctl[q-1] & BITCTL_FIRST)){ return; }
	/* The accent does not move unless the ending is raised.*/
	if(accent0[pp+pl-1]!=0x82){ return; }

	/* When the word could be the head of a string and has two or more syllables, and its ending is raised, the accent moves.*/
	/* When the word could not be the head of a string and has one or more syllables, and its ending is raised, the accent moves.*/
	if(pp+pl>1){
		accent0[pp+pl-2]=0x82; accent0[pp+pl-1]=1;
	}
}

/*========== ACC2219(p) ======================================
	Function: When the pth element has two or more syllables except when the second syllable is low,
		the element is flattened.
  ============================================================*/
void ACC2219(p) integer_16 p; {
	register integer_16 pp,pl;
	pp=phrase_ptr[p]; pl=phrase_len[p];
	if(pl>1 && accent0[pp+pl-1]==1){
		;
	}else{
		ACC000H(p);
	}
}

/*========== ACC221A(p) ==============================================
	Function: When the ending of the pth element is high, check its back-end number with the back-end number table.
		When the second bit is 1, the element is flattened.
  ====================================================================*/
void ACC221A(p) integer_16 p; {
	register integer_16 pp,pl;
	integer_16 n;

	/*<Exceptional processing> When the 57th column of the pth element is 3, the pth element is flattened.*/
	if(stc_accent_raw[p][6]==3){ ACC000H(p); return; }

	pp=phrase_ptr[p]; pl=phrase_len[p];
	if(accent0[pp+pl-1]!=0x82){ return; }

	for(n=stc_nbno[p];n--;){
		if(FddHDR[Fdd_Header.Fdd_BnoTblOfs+stc_bno[p][n]-1] & BITBNO_2){
			ACC000H(p); return;
		}
	}
}

/*========== ACC221B(p) ==============================================
	Function: 
  ====================================================================*/
void ACC221B(p) integer_16 p; {
}

/****************************************************************************/
/*																			*/
/*		Changes of itself when the accent combination occurs				*/
/*																			*/
/****************************************************************************/

/*========== ACC2221(q) =====================================================
	Function: The qth element is combined as 21 type.

	　The first syllable is high, and it is lowered at the fall of the second accent.
	If the second accent does not exist,
	when the element is flattened type, it sets the second accent = 1.
	In other cases, it sets the second accent = the first accent.(89/1/10)
  ==============================================================================*/
void ACC2221(q) integer_16 q; {
	register integer_16 qp;
	BYTE acc2;

	acc2=stc_accent_raw[q][4];	/* The second accent */

	/* When the second accent exists, it is pronounced with high pitch, and it is lowered at the fall of the second accent.*/
	if(acc2!=0xFF){
		/* When the second accent exists, the fall of the succeeding word changes.*/
		if(acc2==0){ ACC000H(q); }else{ ACC0003(q,acc2); }
	}

	/* When the second accent is not defined*/
	if(stc_accent_raw[q][0]==0){
		/* When the element is a flattened type word, it is lowered at the first syllable.*/
		ACC0001(q);
	}else{
		/* When the element is not a flattened type word, it is pronounced with high pitch, and it is lowered at the fall of the first accent.*/
		qp=phrase_ptr[q];
		if(accent0[qp]==1){ accent0[qp]=2; }
	}
}

/*========== ACC2222(q) ====================
	Function: The qth element is combined as 22 type.
	　In other words, it is pronounced with high pitch, and it is lowered at the fall of its own.
	　Currently not used.
void ACC2222(q) register integer_16 q; {
	register integer_16 qp;
	qp=phrase_ptr[q];
	if(accent0[qp]==1){ accent0[qp]=2; }
}
  ==========================================*/

/*========== ACC2223(q) ====================
	Function: The qth element is combined as 23 type.

	　In other words, it is pronounced with high pitch, it is lowered at the last syllable.
  ==========================================*/
void ACC2223(q) integer_16 q; 
{
	register integer_16 qp,ql;
	qp=phrase_ptr[q]; ql=phrase_len[q];
	ACC0003(q, (integer_16)(ql-1));		/* Raising the middle */
	accent0[qp]=2;
}

/*========== ACC2224(p) ====================
	Function: The pth element is combined as 24 type.

	　In other words, it is pronounced with high pitch, and the entire element is flattened.
 ACC2224(p) integer_16 p; { ACC0005(q); }
 ==========================================*/

/*========== ACC2225(p) ====================
	Function: The pth element is combined as 25 type.

	　In other words, it is pronounced with high pitch, and the ending of the element is raised.
 ==========================================*/
void ACC2225(p) integer_16 p; {
	register integer_16 pp,pl;
	pp=phrase_ptr[p]; pl=phrase_len[p];
	ACC0005(p);
	accent0[pp+pl-1]=0x82;
}

/*========== ACC2226(p,q) ============================================
	Function: The qth element depends on the pth element and is combined as 26 type.

	　In other words, when the pth element is a flattened type word, it is pronounced with high pitch, and it is lowered at the fall of its own.
	Otherwise, the pitch of the entire element is low.
  ====================================================================*/
void ACC2226(p,q) integer_16 p; register integer_16 q; {
	register integer_16 qp;
	/*integer_16 pp,pl;*/
	/*pp=phrase_ptr[p]; pl=phrase_len[p];*/
	/*if((pl>1 && accent0[pp+pl-1]==2)||(pl==1 && accent0[pp]==1)){*/
	if(chk_heiban(p)){
		if(accent0[qp=phrase_ptr[q]]==1){ accent0[qp]=2; }
	}else{
		ACC0004(q);
	}
}

/*========== ACC2227(p,q) ==================================================
	Function: The qth element depends on the pth element and is combined as 27 type.

		　In other words, when the pth element is a flattened type word, it is pronounced with high pitch and it is lowered immediately.
		Otherwise, it is pronounced with low pitch.
  ==========================================================================*/
void ACC2227(p,q) register integer_16 p,q; {
	/*register integer_16 pp,pl; pp=phrase_ptr[p]; pl=phrase_len[p];*/
	/*if((pl>1 && accent0[pp+pl-1]==2)||(pl==1 && accent0[pp]==1)){*/
	if(chk_heiban(p)){
		ACC0001(q);		/* The qth element is a head-high type. */
	}else{
		ACC0004(q);		/* The entire qth element is low.*/
	}
}

/*========== ACC2228(p) ====================
	Function: The pth element is combined as 28 type.
	　In other words, it is pronounced with low pitch.
  ACC2228(p) integer_16 p; { ACC0004(p); }
  ==========================================*/

/*========== ACC222A(p,q) ============================================
	Function: The qth element depends on the pth element and is combined as 2A type.

	　In other words, when the pth element is a flattened or raised ending type word, it is pronounced with high pitch and it is lowered at the fall of its own.
	　Otherwise, it is pronounced with low pitch.
  ====================================================================*/
void ACC222A(p,q) integer_16 p; register integer_16 q; {
	register integer_16 qp;

	if(chk_heiban(p)||chk_odaka(p)){
		qp=phrase_ptr[q];
		if(accent0[qp]==1){ accent0[qp]=2; }
	}else{
		ACC0004(q);
	}
}

/*========== ACC222B(p,q) ================================================
	Function: The qth element depends on the pth element and is combined as 2B type.

	　In other words, when the pth element is a flattened type word, the qth element is pronounced with high pitch, and the entire element is flattened.
	Otherwise, the qth element is pronounced with high pitch and it is lowered at the fall of its own.
  ========================================================================*/
void ACC222B(p,q) integer_16 p; register integer_16 q; {
	register integer_16 qp;

	if(chk_heiban(p)){
		/* When the preceding element is a flattened type word, the entire element is flattened.*/
		ACC0005(q);
	}else{
		/* It is pronounced with high pitch and it is lowered at the fall of its own.*/
		qp=phrase_ptr[q];
		if(accent0[qp]==1){ accent0[qp]=2; }
	}
}

/*========== ACC222C(p,q) ============================================
	Function: The qth element depends on the pth element and is combined as 2C type.

	　In other words, when the preceding word is a noun and it is a flattened or raised-ending type word, the element is pronounced with high pitch and the entire element is flattened.
	Otherwise, it is pronounced with low pitch.
  ====================================================================*/
void ACC222C(p,q) register integer_16 p,q; {
	/* Check whether or not the preceding element of the qth element is noun using the back-end number.*/
	/* Note that the preceding element, which is (q-1)th element, is not the pth element.*/
	/* When the fifth bit is 1, it is recognized as nominal form.*/

	/*<Exceptional processing>  When the 57th column of the pth element is 2, it is pronounced with low pitch.*/
	if(stc_accent_raw[q-1][6]==2){ goto ACC222C_200; }

	if((get_case((integer_16)(q-1)) & BITBNO_Taigen) && (chk_heiban(p)||chk_odaka(p)))
	{
		/* When the preceding word is nominal form, and it is a flattened or raised ending type word, the entire element is flattened.*/
		ACC000H(p); 
		ACC0005(q); 
		return;
	}
ACC222C_200:
	/* Otherwise, it is pronounced with low pitch.*/
	ACC0004(q);
}

/*========== ACC222D(q) ====================
	Function: The qth element is combined as 2D type.
	　In other words, it is pronounced with high pitch and keeps it to the second syllable.
	　Currently not used.
void ACC222D(q) register integer_16 q; {
	register integer_16 qp;
	qp=phrase_ptr[q];
	ACC0003(q,2); accent0[qp]=2;
}
  ==========================================*/

/*========== ACC222E(p,q) ============================================
	Function: The qth element depends on the pth element and is combined as 2E type.

	　In other words, when the preceding word is a noun and it is a flattened type word, it is pronounced with high pitch and it is lowered at the fall of its own.
		Otherwise, it is pronounced with low pitch.
  ====================================================================*/
void ACC222E(p,q) integer_16 p; register integer_16 q; {
	register integer_16 qp;

	/* Check whether or not the preceding element of the qth element is noun using the back-end number.*/
	/* Note that the preceding element, which is (q-1)th element, is not the pth element.*/
	/* When the fifth bit is 1, it is recognized as nominal form.*/
	if((get_case((integer_16)(q-1)) & BITBNO_Taigen) && chk_heiban(p))
	{
		/* When the preceding word is in nominal form and it is a flattened type word, it is pronounced with high pitch and it is lowered at the fall of its own.*/
		qp=phrase_ptr[q];
		if(accent0[qp]==1){ accent0[qp]=2; }
	}else{
		/* Otherwise, it is pronounced with low pitch.*/
		ACC0004(q);
	}
}

/*========== ACC222Z(q) ===================================================
	Function: The qth element is combined as 101 type.

	　In other words, it is pronounced with high pitch and it is lowered at the fall of its own.

	Comments: There is no problem in "日本語解析 (NIHONGO KAISEKI)" + "システム (SHISUTEMU)," however,
		for "日本語 (NIHONGO)" + "解析システム (KAIASEKI SHISUTEMU)," the combination rule of the "解析システム (KAISEKI SHISUTEMU)" 
		causes a problem. the combination rule of the "解析システム (KAISEKI SHISUTEMU)" is different from the combination rule of "解析 (KAISEKI)" and "システム (SHISUTEMU)," and 
		 therefore, the preceding word may be flattened and it may is pronounced with high pitch and it is lowered at the fall 
		of its own.
  ==========================================================================*/
void ACC222Z(q) register integer_16 q; {
	register integer_16 qp;
	qp=phrase_ptr[q];
	if(accent0[qp]==1){ accent0[qp]=2; }
}

/****************************************************************************/
/*																			*/
/*			Effects of the succeeding element  when the accent combination occurs				*/
/*																			*/
/****************************************************************************/

/*========== ACC22PO(p,q) =============================================
	Function: It determines the accent when "お (O)" is added.

	Any of the following cases, the pitch of "お (O)" is low.

	お (O) + adjective:  The following element is pronounced with high pitch and it is flattened.
	お (O) + verb:  The following element is pronounced with high pitch and it is flattened.
	お (O) + noun: The head-high noun does not change.
				When the noun is not high-head, 
				if the second accent exists, the accent remains.
				Otherwise, the following element is pronounced with high pitch and flattened.
  =====================================================================*/
void ACC22PO(p,q) integer_16 p,q; {
	integer_16 acc; register integer_16 qp,bno;

	ACC0004(p);
	qp=phrase_ptr[q];
	bno=stc_bno[q][0];
	bno=bno_tbl[bno-1];
	if(bno==pkind_verb_stem||bno==pkind_verb_sa){ goto ACC22PO_verb; }
	if(bno==pkind_adj_stem){ goto ACC22PO_adj; }

	/* When the word is high-head, there is no change.*/
	if(stc_accent_raw[q][0]==1){ return; }
	/* When the second accent does not exist, it is pronounced with high pitch and it is flattened.*/
	if((acc=stc_accent_raw[q][4])==0xFF){
		ACC0005(q);
	}else{
		if(acc==0){ ACC000H(q); }else{ ACC0003(q,acc); }
	}
	if(accent0[qp]==1){ accent0[qp]=2; }
	return;
ACC22PO_verb:;
ACC22PO_adj:;
	ACC0005(q);
}

/*========== ACC2232(p,q) ======================================================
	Function: The pth element affects the qth element and is combined as 32 type.

	  In other words, the pth element is flattened, 
	and the second syllable of the qth element is accentuated if it exists. Otherwise, the head of the element is accentuated.
  ==============================================================================*/
void ACC2232(p,q) integer_16 p,q; {
	BYTE acc4;
	register integer_16 qp,ql;
	ACC000H(p);
	if((acc4=stc_accent_raw[q][4])!=0xFF){
		ACC0003(q,acc4);
		qp=phrase_ptr[q]; ql=phrase_len[q];
		if(ql>1 && accent0[qp]==1){
			accent0[qp]=2;
		}
	}else{
		ACC0001(q);
	}
}

/*========== ACC2233(p,q) ============================================
	Function: The pth element affects the qth element and is combined as 33 type.

	  In other words, when the pth element is a flattened type word, it is pronounced with high pitch and it is lowered at the fall of its own.
  ====================================================================*/
void ACC2233(p,q) integer_16 p,q; {
	register integer_16 qp;
	qp=phrase_ptr[q];
	ACC000H(p);
	if(accent0[qp]==1){ accent0[qp]=2; }
}

/*========== ACC2234(p,q) ============================================
	Function: The pth element affects the qth element and is combined as 34 type.

	  In other words, when the qth element contains 2 or more digits number, it is not combined.
	When the qth element is a one-digit number and the pth element is head-high, the qth element is pronounced with low pitch.
	When the pth element is not head-high, the qth element is pronounced with high pitch.

	(Example) The "第1 (DAI ICHI)" is combined, and "1 (ICHI)" is pronounced with low pitch. "第25 (DAI NIJUGO)" is not combined.
		　(Example) The "図1 (ZU ICHI)" is combined, and "1 (ICHI)" is pronounced with high pitch. "図25 (ZU NIJUGO)" is not combined.
		　(Example) The "表1 (HYOU ICHI)" is combined, and "1 (ICHI)" is pronounced with high pitch. "表25 (HYOU NIJUGO)" is not combined.
		　The pth element divided into these three types.

			This processing is performed by ACC2800().
  ====================================================================*/

/*========== ACC2236(p,q) ============================================
	Function: The pth element affects the qth element and is combined as 36 type.

	  In other words, the both pth and qth elements keep their own accents.
		(Example)  各 (KAKU)
  ====================================================================*/

/*========== ACC2237(p,q) ============================================
	Function: The pth element affects the qth element and is combined as 37 type.

	  In other words, the pth element keeps its own accent, and the qth element is pronounced with low pitch.
		(Example) どんな (DONNA)
ACC2237(p,q) integer_16 p,q; { ACC0004(q); }
  ====================================================================*/

/*========== ACC2239(p,q) ============================================
	Function: The pth element affects the qth element and is combined as 39 type.

	  In other words, the last syllable of the pth element is high pitch, and the pitch of the first syllable of the qth element becomes with high pitch.

		(Example) の (NO) (case particle)
  ====================================================================*/
void ACC2239(p,q) integer_16 p,q; {
	register integer_16 qp;
	if(accent0[phrase_ptr[p]+phrase_len[p]-1]!=1){
		qp=phrase_ptr[q];
		if(accent0[qp]==1){ accent0[qp]=2; }
	}
}

/***************************** END OF ACC_22XX.C *****************************/

