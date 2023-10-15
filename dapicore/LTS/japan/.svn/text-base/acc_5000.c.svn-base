/********************************************
	ACC_5000.C	updated at 16th July 1991
	Accent combination in segment
	Devoicing vowels
	Conversion between nasal consonant and voiced consonant
	Moving accent at conjunctive ending
	Determining the syllable of height 9
	Processing of ancillary "の (NO)"
	Controlling secondary accents
	Machine-independent part of phonetic data output
 ********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_acch.h"
#include	"ile_fddh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"
#include "pkind.h"
#include "ile_accd.h"


/*========== ACC5000() ===================================================
	Function:  Combining segments
		When the preceding segment is flattened, the succeeding segment is pronounced with high pitch and it is lowered at its own fall.
		When the preceding segment is up-and-down type, the succeeding segment is pronounced with low pitch.
		However, it is not easy to combine segment when the succeeding segment is head-high type.
		Do not combine the segment when the succeeding segment is long.
		Note:  When the both preceding and succeeding segments are the simple words, they are not combined.
			　When the end of the preceding segment is not an ancillary, it is not combined with other segment.
  ========================================================================*/
void ACC5000() {
	register integer_16 i,j;
	for(i=0;i<stc_ptr-1;++i)
	{
		if(phrase_len[i]!=0)
		{
			/* It is end if it is the last phrase. */
			if((j=next_phrase(i))==0){ return; }
			/* If either of them is a simple word, they are not combined. */
			if((phrase_kind[i]==pkind_others)||(phrase_kind[j]==pkind_others)){ goto ACC5000_190; }
			/* When a segment is too long, it is not combined with others. */
			if(phrase_len[i]+phrase_len[j]>MAX_PHRASE){ goto ACC5000_190; }
			/* .00 is not combined with others. */
			if(acc_accent_raw[j][1]==0 && acc_accent_raw[j][2]==0){ goto ACC5000_190; }
			/* When the preceding segment ends with a word other than an ancillary, for example a compound noun, the segment is not combined with others. */
			if(stc_ctl[j-1] & BITCTL_FIRST){ goto ACC5000_190; }
			/* When a pose is need to be inserted, the segment is not combined. */
			/*if(stc_pause[j-1]>0){ goto ACC5000_190; }*/
			goto ACC5000_190;	/* for DEBUG  Segments are never combined. */
			/************/
			/*  ACC5100(j); */
			/************/
		}
ACC5000_190:;
	}
}


/*========== ACC5100() =========================================================
	Function:  Combining segments
		When the preceding segment is flattened or ending-raised, the succeeding segment is pronounced with high pitch and it is lowered at its own fall.
		When the preceding segment is up-and-down type, the succeeding segment is pronounced with low pitch.
  ==============================================================================*/
void ACC5100(j) register integer_16 j; {
	register integer_16 ptr;
	ptr=phrase_ptr[j];
	/* When the succeeding segment is not head-high, the segment is combined. */
	if(accent0[ptr]!=0x82){
		if(accent0[ptr-1]==1){
			/* When the last syllable of the preceding segment is low, the preceding segment is pronounced with low pitch. */
			if(count_low(j)<=MAX_TONE){ ACC0004(j); }
		}else{
			/* When the last syllable of the preceding segment is high, the preceding segment is pronounced with high pitch. */
			if(count_high(j)<=MAX_TONE){ accent0[ptr]=2; }
		}
	}
}

/*========== count_high(i) ==========================================
	Function:  When segments are combined, count the number of consecutive high mora phonemes.
  ===================================================================*/
integer_16 count_high(i) integer_16 i; {
	register integer_16 c,p;
	c=0;
	for(p=phrase_ptr[i]-1;;--p){
		if(accent0[p]==2){ ++c; }else{ goto count_high_100; }
	}
count_high_100:
	/* The first mora phoneme of the succeeding segment becomes high.*/
	for(p=phrase_ptr[i]+1;p<phrase_ptr[i]+phrase_len[i];++p){
		if(accent0[p]!=1){ ++c; }else{ goto count_high_200; }
	}
count_high_200:
	return c+1;
}

/*========== count_low(i) ===========================================
	Function:  When segments are combined, count the number of consecutive low mora phonemes.
  ===================================================================*/
integer_16 count_low(i) integer_16 i; {
	register integer_16 c,p;
	c=0;
	for(p=phrase_ptr[i]-1;;--p){
		if(accent0[p]==1){ ++c; }else{ goto count_low_100; }
	}
count_low_100:
	/* All succeeding segments are pronounced with low pitch. */
	return c+phrase_len[i];
}


/*========== ACC6000() ======================
	Function:  Convert a nasal consonant at the head of a segment to a voiced consonant.
		  Devoicing vowels.
  ===========================================*/
void ACC6000() 
{
	register integer_16 ptr,len; integer_16 i;
	BYTE mora1,mora2,a1,a2,a3;
	
	/* Convert a nasal consonant at the head of a segment to a voiced consonant.*/
	for(i=0;i<stc_ptr;++i){
		if(phrase_len[i]!=0){
			mora1=omega[ptr=phrase_ptr[i]];
			if((mora1 & 0xF8)==0x78){ omega[ptr]=(mora1 & 0x07)|0x70; }
		}
	}
	
	/* Set 2 for the level of 0 x 82 (accent point). */
	for(i=cpron_ptr;i--;){
		if(accent0[i]==0x82){ accent0[i]=2; }
	}
	
	/*
	* When KI, KU, SHI, SU, CHI, TSU, HI, FU, or SHU is 
	* located before the syllable of K, S, T, H, or P row, it is devoiced.
	*
	* In addition, 
	* When PI or PU is 
	* located before the syllable of K, S, T, H, or P row, it is devoiced.-- without RICOH --
	*
	* When CHU, FI, or TSI is 
	* located before the syllable of K, S, T, H, or P row, it is devoiced.-- RICOH --
	*/
	for(i=0;i<stc_ptr;++i){
		if((len=phrase_len[i])!=0){
			ptr=phrase_ptr[i];
			for(;len--;++ptr){
				mora1=omega[ptr];
				if(len){			/* When it is not the last syllable of the segment */
					switch(mora1){
					case 0x09: case 0x0A:		/* KI KU */
					case 0x29: case 0x32:		/* CHI TSU */
#if defined(V_RICOH)
					case 0x2A: case 0x31:		/* CHU TSI */
#else
					case 0xA2:					/* PU */
#endif
						mora2=omega[ptr+1];
						switch(mora2 & 0xF8){
						case 0x08: case 0x10: case 0x18:	/* KA SA TA HA PA rows */
						case 0x20: case 0x28: case 0x30:
						case 0x40: case 0x48: case 0xA0:
							/* All except a fall of the accent are devoiced (lie 87.10.16)*/
							/*if(accent0[ptr]==2 && accent0[ptr+1]==1){*/
							/*	;*/
							/*}else{*/
							accent0[ptr]|=0x80;
							/*}*/
						}
					}
					
					switch(mora1){
					case 0x19: case 0x12:				/* SHI SU */
					case 0x41: case 0x42: case 0x1A:	/* HI, FU, SHU */
#if defined(V_RICOH)
					case 0x49:							/* FI */
#else
					case 0xA1:							/* PI */
#endif
						mora2=omega[ptr+1];
						switch(mora2 & 0xF8){
						case 0x08: case 0x20: case 0x28:	/* KA TA PA rows */
						case 0x30: case 0xA0:
							accent0[ptr]|=0x80;
						}
					}
				}
			}
		}
	}
	
	/*
	* A short KI, KU, SHI, SU, CHI, or TSU at the end of the segment is devoiced.
	* In addition, 
	* a low PI or PU at the end of the segment is devoiced.-- without RICOH --
	* A low CHU, FI, or TSI at the end of the segment is devoiced.-- RICOH --
	*/
	for(i=0;i<stc_ptr;++i){
		if((len=phrase_len[i])!=0){
			ptr=phrase_ptr[i]+len-1;
			if(accent0[ptr]==1){
				if(next_phrase(i)){
					/* When the segment is succeeded by a voiced consonant, it is not devoiced.*/
					switch(omega[ptr+1] & 0xF8){
					case 0x00: case 0x38: case 0x50:	/* A, NA, and MA rows */
					case 0x58: case 0x60: case 0x68:	/* YA, RA, and WA rows */
					case 0x70: case 0x78: case 0x80:	/* GA, GA, and ZA rows */
					case 0x88: case 0x90: case 0x98:	/* JA, DA, and BA rows */
					case 0xA8: case 0xB8:				/* VA and GUA rows */
						goto ACC6000_200;
					}
				}
				switch(omega[ptr]){
				case 0x09: case 0x0A: case 0x19:		/* KI KU SHI */
				case 0x12: case 0x29: case 0x32:		/* SU CHI TSU */
				case 0x1A:								/* SHU */
#if defined(V_RICOH)
				case 0x2A: case 0x49: case 0x31:		/* CHU, FI TSI */
#else
				case 0xA1: case 0xA2:					/* PI PU */
#endif
					accent0[ptr]|=0x80;
				}
				
ACC6000_200:;
			}
		}
	}
	
#if defined(V_RICOH)
#else
	/*
	* When the same high pitch syllable is placed after the syllable of _}, ・|,_}・|, which is low head accent.
	 *		(Example)  KA and KO which are the beginning of KAKASHI and KOKORO
	 * However, they are not devoiced in RICHO version.
	 */
	for(i=0;i<stc_ptr;++i){
		if((len=phrase_len[i])!=0){
			ptr=phrase_ptr[i];
			if(accent0[ptr]==1 && omega[ptr]==omega[ptr+1]){
				switch(omega[ptr]){
				case 0x08: case 0x0C:	/* KA, KO */
					accent0[ptr]|=BITACC_MUSEI;
				}
			}
		}
	}

	/*
	 * When the syllable of A row or O row is placed after _}, ・|,_}・|, which is low head accent.
	 *		(Example)  HO and HA which are the beginning of HOKORI and HAKA
	 * However, they are not devoiced in RICHO version.
	 */
	for(i=0;i<stc_ptr;++i){
		if((len=phrase_len[i])!=0){
			ptr=phrase_ptr[i];
			if(accent0[ptr]==1){
				switch(omega[ptr]){
				case 0x40: case 0x44:	/* HA, HO */
					switch(omega[ptr+1] & 0x07){
					case 0x00: case 0x04:	/* A or O row */
						accent0[ptr]|=BITACC_MUSEI;
					}
				}
			}
		}
	}
#endif

	/* When three devoiced sounds are continued*/
	for(i=0;i<cpron_ptr-2;++i){
		a1=accent0[i]; a2=accent0[i+1]; a3=accent0[i+2];
		if((a1 & 0x80)&&(a2 & 0x80)&&(a3 & 0x80)){
			/* The middle sound is not devoiced.*/
			accent0[i+1]&=0x7F;
		}
	}

	/* When two devoiced sounds are continued*/
	for(i=0;i<cpron_ptr-1;++i){
		a1=accent0[i]; a2=accent0[i+1];
		if((a1 & 0x80)&&(a2 & 0x80)){
			/*
			 * The preceding on is devoiced.
			 * However, if one of them is in KA row, the letter in KA row is not devoiced.
			 * When both are in KA row, the preceding one is devoiced.
			 * KI in "焚き付ける (taKITSUKERU)" is not devoiced.
			 * Ki in "歴史的 (reKISHITEKI)" is not devoiced.
			 * Ku in "建築と (keXCHIKUTO)" is not devoiced.
			 * The second KI in "聞き方 (kiKIKATA)" is not devoiced.
			 * Ki in "歴史的 (reKISHITEKI)" is not devoiced.
			 *			updated 91. 7.15
			 */
			/*if((a1 & 0x7F)==(a2 & 0x7F)){*/
			/*mora1=omega[i] & 0xF8;*/
			mora2=omega[i+1] & 0xF8;
			if(mora2==0x08){
				accent0[i+1] &=0x7F;
			}else{
				accent0[i] &=0x7F;
			}
			/*}*/
			/*
			 * When the pitch of two items are different, the lower one is expected to be devoiced, however, there are too many exceptions, so
			 * they are processed as the same pitch items.
			 *			updated 91. 7.16
			 *if((a1 & 0x7F)!=(a2 & 0x7F)){
			 *	if((a1 & 0x7F)==2){
			 *		accent0[i]&=0x7F;
			 *	}else{
			 *		accent0[i+1]&=0x7F;
			 *	}
			 *}
			 */
		}
	}
}


/*========== ACC7000() =================================================
	Function:  When a conjunctive verb that is located just before a punctuation or at the end of a sentence, if the conjunctive verb is ending-raised type, 
		the fall of the accent is moved one previous syllable.

	(Example): 飲み (NOMI), 食べ (TABE), 守り (MAMORI), 生き (IKI)
		　When the word includes a mora phoneme, such as 察し (SASSHI) or 信じ (SHINJI), the accent is moved on more previous syllable.
  ======================================================================*/
void ACC7000() {
	register integer_16 i;
	for(i=1;i<stc_ptr;++i){
		/* If ith element is a punctuation, check (i-1)th element.*/
		if(chk_separator(i)){ ACC7100((integer_16)(i-1)); }
	}
	/* If the end of sentence is not punctuation, check the end of the sentence.*/
	if(chk_separator((integer_16)(stc_ptr-1))==0){ ACC7100((integer_16)(stc_ptr-1)); }
}

void ACC7100(i) register integer_16 i; {
	integer_16 c,bno,case_tbl; register integer_16 ptr;
	for(c=0;c<stc_nbno[i];++c){
		if(bno=stc_bno[i][c]){
			case_tbl=Fdd_Header.Fdd_BnoTblOfs;
			/* When the fourth bit is on, it is a conjunctive form.*/
			if(FddHDR[case_tbl+bno-1] & BITBNO_Renyou){
				goto ACC7000_100;
			}
		}
	}
	return;

	ACC7000_100:;
	/* Exclude the one-syllable conjunctive form (except 5-step verb).*/
	/*
	 * Conjunctive ending or (5-step conjunctive verb)
	 * A stem containing 2 or more letters + ending (such as "下さい (KUDASAI), an exception of 5-step verb) or
	 * A stem containing 2 or more letters (1-step conjunctive verb containing 2 or more letters)
	if((bno_tbl[bno-1]==pkind_verb_renyou)
	|| (bno_tbl[bno-1]==pkind_verb_inflect && stc_out_len[i-1]>1)
	|| (bno_tbl[bno-1]!=pkind_verb_inflect && stc_out_len[i]>1)){
	 */
	/*  When the 57th column is 1, the accent does not move.*/
	if(stc_accent_raw[i][6]!=1){
		ptr=stc_out_ptr[i]+stc_out_len[i]-1;
		/*
		 * Note that ptr==0, or when the element is one-syllable word, the accent cannot move.
		 */
		if(ptr>0 && accent0[ptr]==0x82){
			accent0[ptr-1]=0x82; accent0[ptr]=1;
		}
	}
	return;
}

/*========== ACC8000() =========================================================
	Function: (1) The height of the syllable that precedes the question mark (?) is set to 9.
		　(2)  When a particle WA, YO, or NE is placed just before a punctuation or at the end of the sentence, 
				its height is set to 9.
					(Example), 赤いわ「ね」 (AKAIWA "NE"), 動いた「わ」 (UGOITA"WA")
				The third bit in the back-end number table of the particle is on.
  ==============================================================================*/
void ACC8000() {
	integer_16 i,j,case_tbl,ptr,len;
	for(i=0;i<stc_ptr;++i){
		/* Check the following phrase when the phrase length is 0.*/
		if((len=phrase_len[i])==0){ goto ACC8000_190; }
		/* When the phrase consists of special characters, check the next phrase.*/
		if(len==1 && accent0[phrase_ptr[i]]==0xFF){ goto ACC8000_190; }

		/* Check the number of the phrase of which next phrase length is not 0. If it is the last phrase, return 0.*/
		j=next_phrase(i);
		if(j==0){ j=stc_ptr; }
		/* Check the location of the last syllable of the target phrase.*/
		ptr=phrase_ptr[i]+len-1;

		/***************************************************/
		/* (1) The height of the mora phoneme that precedes the question mark (?) is set to 9.*/
		/***************************************************/

		/* When the (ptr)th character is not at the end of the sentence, */
		if(j){
			/* (ptr+1)th character is a special symbol, and */
			if(chk_separator(j)){
				/* and the (ptr+1)th character is a question mark, the pitch height of the (ptr)the syllable is set to 9.*/
				if(inert[stc_in_ptr[j]*2]==0x21 && inert[stc_in_ptr[j]*2+1]==0x29){
					accent0[ptr]=9;
				}
			}
		}

		/*************************************************************************/
		/* (2) The height of the pitch of WA, YO, or NE just before a punctuation or at the end of the sentence is set to 9.*/
		/*************************************************************************/

		/* When (ptr)th character is at the end of the sentence, or when (ptr+1)th character is a special symbol, */
		if(j==stc_ptr || chk_separator(j)){
			/* check the back-end number table.  When it is a particle of which height could be set to 9, */
			case_tbl=Fdd_Header.Fdd_BnoTblOfs;
			if(FddHDR[case_tbl+stc_bno[j-1][0]-1] & BITBNO_Level9){
				accent0[ptr]=9;
			}
		}

		ACC8000_190:;
	}
}


/*========== ACC_JOSI_NO() ========================
	Function: Processing of an ancillary "の (NO)" of which effect on the succeeding element is 9
  =================================================*/
void ACC_JOSI_NO(void) 
{
	register integer_16 i,p;
	/* The first syllable of "蛇口 (JAGUCHI)" of "水道の蛇口 (SUIDOU NO JAGUCHI)" is raised because of the effect of "の (NO)."*/
	/* This processing must be performed after the combination processing of all ancillaries.*/
	for(i=0;i<stc_ptr-1;++i)
	{
		if(acc_accent_raw[i][3]==9)
		{
			/* When the element is the one raises the succeeding syllable, */
			if(stc_pause[i+1]==0)
			{
				/* if a pose is inserted, it does not affect the succeeding syllable.*/
				p=stc_out_ptr[i+1];
				/* Only when the syllable is high, raise the next syllable.*/
				if(accent0[p-1]!=1 && omega[p]!=0xFF)
				{ 
					accent0[p]=2; 
				}
			}
		}
	}
}


/*========== ACC_PHRASE() ==================================
	Function:  Determine the delimiter of the phrase that rise a "wave."
  ==========================================================*/
void ACC_PHRASE(void) 
{
	register integer_16 i,j;
	integer_16 precede,fall;
	integer_16 cx;
	BYTE *si;
/*
 *	"言語工学研究所 (GENGO KOUGAKU KENKYUJO)" consists of two phrases, one is "言語工学 (GENGO KOUGAKU)," and the other is "研究所 (KENKYUJO)."
 *	"私の会社 (WATASHINO KAISHA)" is one phrase.
 *	Adjust the border of phrases so that each phrase can have one fall.
 */
	for(i=0;i<stc_ptr;++i){
		if(phrase_len[i]==0){ goto ACC_PHRASE_90; }
		precede=1;
		fall=0;
		for(si=(&accent0[phrase_ptr[i]]),cx=phrase_len[i];cx--;++si){
			if(precede==2 && *si==1){ fall=1; }
			if(fall==1){ *si=1; }
			precede=(*si);
		}
		ACC_PHRASE_90:;
	}
ACC_PHRASE_100:
	i=0;
ACC_PHRASE_110:
	for(;i<stc_ptr-1;++i){
		if(phrase_len[i]!=0){ goto ACC_PHRASE_120; }
	}
	return;
ACC_PHRASE_120:
	j=i+1;
	while(phrase_len[j]==0 && j<stc_ptr){ ++j; }
	if(j==stc_ptr){ return; }

	if(stc_pause[j]!=0){ ++i; goto ACC_PHRASE_110; }

	if(phrase_len[i]==1){
		/*
		 *	When the preceding element is one-syllable word, 
		 *	if it is low pitch, it is OK only when the head of the succeeding element is high.
		 *	If it is high pitch, it is OK only when all the succeeding elements are low.
		 */
		if(accent0[phrase_ptr[i]]==1){
			if(accent0[phrase_ptr[j]]==1){
				goto ACC_PHRASE_SEPARATE;
			}else{
				goto ACC_PHRASE_INTEGRATE;
			}
		}else{
			goto ACC_PHRASE_180;
		}
	}else{
		/*
		 *	When the preceding element is two- or more-syllable word, 
		 *	if the last syllable of the preceding element is low pitch, it is OK only when all the succeeding elements are low.
		 *	If the last syllable of the preceding element is high pitch, it is OK when the head of the succeeding element is high and when all the succeeding elements are low.
		 */
		if(accent0[phrase_ptr[j]-1]!=1){
			if(accent0[phrase_ptr[j]]!=1){ goto ACC_PHRASE_INTEGRATE; }
		}
	}
ACC_PHRASE_180:;
	/* It is OK when all the succeeding elements are low.*/
	for(si=(&accent0[phrase_ptr[j]]),cx=phrase_len[j]; cx--; ++si){
		if(*si!=1){ goto ACC_PHRASE_SEPARATE; }
	}
ACC_PHRASE_INTEGRATE:;
	phrase_len[i]+=phrase_len[j];
	phrase_ptr[j]=phrase_len[j]=0;
	goto ACC_PHRASE_100;
ACC_PHRASE_SEPARATE:;
	++i;
	goto ACC_PHRASE_110;
}


integer_16 ACC_OUTPUT_C(al,di)
	BYTE al; register integer_16 di;
{
	if(di>=MAX_SPEAK){ jp_ERROR(Err_NaibuOVF); }
	speak[di]=al;
	return (di+1);
}


integer_16 ACC_OUTPUT_N(num,len,di) integer_16 num,len,di; {
	register integer_16 b,l;
	/* Check the number of digits of the number to be output. */
	for(b=10,l=1;b<=num;b*=10,l++)
		;
	b/=10;
	/* If the number of digits is not enough, add zeros. */
	for(;len>l;len--){
		di=ACC_OUTPUT_C('0',di);
	}
	/* Output the number. */	
	/*while(len--){*/
	while(l--){
		di=ACC_OUTPUT_C((BYTE)((num/b)+'0'), di); 
		num%=b; 
		b/=10;
	}
	return di;
}


integer_16 ACC_OUTPUT_S(str,di)
	register BYTE *str; register integer_16 di;
{
	while(*str){ di=ACC_OUTPUT_C(*str++,di); }
	return di;
}

/***************************** END OF ACC_5000.C *****************************/

