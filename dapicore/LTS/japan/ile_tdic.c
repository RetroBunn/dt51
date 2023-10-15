/*********************************************
	ILE_TDIC.C	updated at 30th April 1990
	Tan-kanji dictionary
 *********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_edic.h"
#include	"ile_envh.h"
#include	"ile_fddh.h"
#include	"ile_kkhh.h"
#include	"ile_mruh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_tdic.h"
#include	"ile_func.h"
#include "ile_rnsc.h"


/*========== TDIC1000() ============================================
	Function: Check whether or not there is a possibility that the current watching word 
		exists in the Tan-kanji dictionary.
	Value: 	ÅÅÇO	Ignore.
			ÅÅÇP	Symbol that is not read
			ÅÅÇQ	Hiragana
			ÅÅÇR	Use Tan-kanji dictionary. If it is not in the dictionary, it is the same as 1.
  ==================================================================*/
integer_16 TDIC1000(){
	register BYTE *si;
	BYTE al,ah;

	al=inert_kind[ceptr];
	if(al==CHRKIND_HKana){
		if(celen>2){ return 0; }
	}else{
		if(celen>1){ return 0; }
	}

	ah=al & 0xF0;
	if(ah==CHRKIND_Other1||ah==CHRKIND_Other2){
		if(inert[ceptr*2]==0x21 && inert[ceptr*2+1]==0x3C){	/* Single long vowel */
			return 3;
		}
		return(onsei_addr->onsei_kouseisystem? 3:1);
	}

	switch(al){
	case CHRKIND_ADigit:
	case CHRKIND_KKana:
		return 0;
	case CHRKIND_Alpha:
		return(celen==1? 3:0);
	}

	/* hiragana - kanji */
	if((onsei_addr->onsei_usetankan==0)
	|| (conv_mode==CONV_FIRST)
	|| (ceptr+celen<=max_ceptr)){
		return 0;
	}

	if(al==CHRKIND_HKana){
		/* One hiragana character is OK.  If the second character is a dependent character, two characters are OK.*/
		if(celen==1){ return 2; }
		si=inert+ceptr*2;
		if(*(si+2)==0x24){
			if(*(si+3)==0x63||*(si+3)==0x65||*(si+3)==0x67){
				return 2;
			}
		}
		return 0;
	}else{
		return 3;
	}
	/* When the preceding element cannot be the last, it is not OK.
	 *	if(stc_ptr>0){
	 *		if(0==(Stz_PE.stz_ctl & BITCTL_LAST)){ return 0; }
	 *	}
	 */
}


/*========== TDIC2XXX() ================================================
	Function: Search a kanji character starting with inert[ceptr*2] from the Tan-kanji dictionary.
  ======================================================================*/
BOOL TDIC2XXX(){
	register WORD ax;
	register BYTE *si;

	if(TDIC2000()==0){ return 0; }		/* Initial conversion */
	si=inert+ceptr*2;
	ax=(*si<<8)|*(si+1);					/* Search character */
	/*
	 * When the dictionary lookup character is a kanji, 
	 *	 if both the preceding and succeeding characters are not kanji, it is pronounced in kun reading.
	 *	 If either or both preceding and succeeding characters are kanji, then it is pronounced in on reading.
	 * When the dictionary lookup character is a special symbol, 
	 *	 only the correction reading is used in correction mode.
	 */
	/*if(Stz_CE.stz_mru & BITMRU_ABORT){ return 1; }*/
L100:;
	if(ax>0x3000){						/* Processing for kanji characters */
		if(is_zengo_kanji(ceptr)){
			/* When a kanji character is preceding or succeeding another kanji character, on-reading is OK.*/
			if(Stz_CE.stz_dman & BITTAN_ON){ return 1; }
		}else{
			/* When both preceding and succeeding character are not kanji, kun-reading is OK.*/
			if(Stz_CE.stz_dman & BITTAN_KUN){ return 1; }
		}
	}else{
		if(onsei_addr->onsei_kouseisystem){
			/* In correction mode, correction reading is OK.*/
			if(Stz_CE.stz_dman & BITTAN_KOUSEI){ return 1; }
		}
	}
	if(TDIC3000()==1){ goto L100; }		/* Next target */
	/* When there is no item that satisfies the condition, use the top target.*/
	return(TDIC2000());
}


/*========== TDIC2000() ================================================
	Function: Search a kanji character starting with inert[ceptr*2] from the Tan-kanji dictionary.
  ======================================================================*/
BOOL TDIC2000(){
	register WORD ax,mx;
	BYTE *si,mh;
	LPBYTE bp;

	TDIC2100();				/* obtain the Tan-kanji dictionary block that has the specified notation. */
	RnsfReadEdic(edic_page_no,&edic_page_addr);
							/* Load the Tan-kanji dictionary, andobtain the address in edic_page_addr. */
	bp=edic_page_addr;		/* Initialize the address in the external dictionary page. */
	si=inert+ceptr*2;		/* Offset of search character */
	ax=(*si<<8)|*(si+1);	/* Search characterÅiÇiÇhÇrÅj*/
TDIC2000_COMPARE:;
	/* When it reaches the end of the page, the character to be searched is not on the dictionary.*/
	if(0x00==(mh=(*bp))){ goto TDIC2000_NOTFOUND; }
	/* Obtain the reference character (JIS).*/
	/* When (*(WORD *)bp) is used for accessing, high and low is reversed. Be aware of it.*/
	mx=(mh<<8)|*(bp+1);
	/* When the keyword is small, skip to the next keyword.*/
	if(ax>mx){
		bp+=(*(bp+2)+3); goto TDIC2000_COMPARE;
	}
	/* When the keyword is large, the character to be searched is not on the dictionary.*/
	if(ax<mx){ goto TDIC2000_NOTFOUND; }

	/* The character to be searched is on the dictionary.*/
	/* Store the total size of the Tan-kanji record and the position of the attribute flag.*/
	tdic_len=(*(bp+2));
	tdic_ofs=(WORD)(bp-edic_page_addr+3);
	TDIC4000();
	return 1;
TDIC2000_NOTFOUND:;
	return 0;
}


/*========== TDIC2100() ========================================
	Function: Obtain the block number of the Tan-kanji dictionary that contains the character to be searched.
  ==============================================================*/
void TDIC2100(){
	register BYTE *table;
	register integer_16 i;
	BYTE *si;
	WORD ax;

	si=inert+ceptr*2;							/* Offset of search character */
	ax=(*si<<8)|*(si+1);							/* Search characterÅiÇiÇhÇrÅj*/
	table=FddHDR+Fdd_Header.Fdd_TdicIndOfs;		/* Offset of index */

	/* Because the index size is 10 at most, the binary search is not necessary.*/
	for(i=0;i<Fdd_Header.Fdd_TdicNoPage;++i,table+=2){
		/* When (*(WORD *)table) is used for accessing, high and log is reversed. Be aware of it.*/
		if(ax < ((*table<<8)|*(table+1))){ goto TDIC2100_FOUND; }
	}
TDIC2100_FOUND:;
	i--;
	/* Obtain the page number on FD according to the block number. */
	edic_page_no=Fdd_Header.Fdd_TdicPageSize*i+Fdd_Header.Fdd_TdicPageOfs+1;
}


/*========== TDIC3000() ============
	Function: Next target of Tan-kanji conversion
  ==================================*/
BOOL TDIC3000() 
{
	register WORD ax;
	integer_16 tdic_ofs_save;
	LPBYTE bp;
	
	/* Fetch the current watching position.*/
	bp=edic_page_addr+tdic_ofs;
	tdic_ofs_save=tdic_ofs;
	/* Skip the type flag, the accent information, and the phonetic information.*/
	ax=(*(++bp));
	bp+=(ax>>4)+(ax & 0x0F)+1;
	/* Store the current watching position.*/
	tdic_ofs=(integer_16)(bp-edic_page_addr);
	/* Update the total size of the next target record.*/
	tdic_len-=(tdic_ofs-tdic_ofs_save);
	if(tdic_len==0){ return 0; }	/* When it is the target position, there is no next target.*/
	TDIC4000();
	return 1;
}


/*========== TDIC4000() ==============
	Function: Specify the connection information of the Tan-kanji.
  ====================================*/
void TDIC4000() {
	LPBYTE bp;

	/* Make settings of connection information that does not refer to the dictionary.*/
	TDIC4100();

	/* Watch the order of call because TDIC4100( ) damages Stz_CE.*/
	/* Set the type flag.*/
	bp=tdic_ofs+edic_page_addr;
	Stz_CE.stz_dman=(*bp);
}


/*========== TDIC4100() ==============================
	Function: Specify the connection information of the Tan-kanji except type flag.
  ====================================================*/
void TDIC4100() {
	register BYTE *si;
	register WORD ax;

	StzfElmKind(&Stz_CE,DICKIND_T);

	/* Change the back-end number depending on whether or not it is a symbol.ÅBÅiÇXÇOÅDÇSÅDÇRÇOÅj*/
	switch(inert_kind[ceptr] & 0xF0){
	case CHRKIND_Other1:	/* Symbol that can be at the top */
		StzfGrcdAdd(Fdd_Header.Fdd_GrcdToku1);
		StzfGrcdStore(Fdd_Header.Fdd_GrcdUsr);
		break;
	case CHRKIND_Other2:	/* A symbol that cannot be the top */
		/* Even if it is a symbol that cannot be the top, it can be the top of the character string.*/
		StzfGrcdAdd((BYTE)(ceptr ? Fdd_Header.Fdd_GrcdToku2 : Fdd_Header.Fdd_GrcdToku1));
		if(ceptr==0){
			StzfGrcdStore(Fdd_Header.Fdd_GrcdUsr);
		}
		break;
	default:		/* kana, alphabetic character, and kanji */
		StzfGrcdStore(Fdd_Header.Fdd_GrcdUsr);
		/*StzfGrcdStore(Fdd_Header.Fdd_GrcdGai);*/
		break;
	}

	/* Grammar code -> back-end number, forward vector number, or control information*/
	StzfGrcdOR();
	/*
	 * A long vowel, syllabic nasal, double consonant, and "Ç" cannot be the first character.
	 * However, in case a sentence that starts with "ÇÒ", "Å[", or "Ç¡" is input, 
	 * in rewrite mode, the character that cannot be the top of the sentence 
	 * can be the top.
	 */
	si=inert+ceptr*2;					/* Offset of search character */
	ax=(*si<<8)|*(si+1);				/* Search characterÅiÇiÇhÇrÅj*/
	if(conv_mode==CONV_FIRST || ceptr>0){
		if(ax==0x213C||ax==0x2443||ax==0x2472||ax==0x2473
					 ||ax==0x2543||ax==0x2572||ax==0x2573){
			Stz_CE.stz_ctl &= ~BITCTL_FIRST;
		}
	}

	/* Flag 2:ÅÅChinese-origin word */
	Stz_CE.stz_f2= 0x80|BITFLG2_KANGO;

	/* Avoid hiragana that follows another hiragana being the top of the sentence.*/
	if(ceptr>0 && *si==0x24 && omega[stc_out_ptr[stc_ptr-1]]!=0xFF){
		Stz_CE.stz_ctl &= ~BITCTL_FIRST;
	}
}


/*========== TDIC5000(di) ===============================================
	Function: Store the phonetic symbol of the current element in the output data area from the dith character.
  =======================================================================*/
integer_16 TDIC5000(di) integer_16 di; {
	register integer_16 a_len,p_len;
	BYTE ah,al;
	BYTE *si,*ti;
	LPBYTE bp;
	integer_16 cx;

	/* Fetch the current watching position.*/
	bp=tdic_ofs+edic_page_addr;
	/* Skip the type flag.*/
	bp++;

	p_len=(*bp++);
	a_len=p_len>>4;				/* length of accent information */
	p_len &= 0x0F;				/* length of pronunciation information */

	/* Fetch the accent raw information.*/
	for(;a_len--;){
		al=(*bp++);
		ah=al/16; al=al%16;
		if(ah<10){ stc_accent_raw[stc_ptr][ah]=al; }
	}

	ACC0010();

	/* Fetch the phonetic information.*/
	if(p_len==0){
		cpron_len=0;

		si= &inert[ceptr*2]; ti=inert_kana;
		for(cx=celen*2;cx--;){ *ti++=(*si++); }
		*ti=0x00;

		cx=mkhatu(inert_kana,inert_pron);

		for(si=inert_pron;cx--;++si){
			di=OMEGA1000(*si,di); ++cpron_len;
		}
	}else{
		cpron_len=p_len;			/* Specify the number of phonetic symbols. */
		for(;p_len--;){ al=(*bp++); di=OMEGA1000(al,di); }
	}
	return di;
}


/*========== TDIC5009(di) ==========================
	Function: Store the phonetic symbol of Tan-kanji that is unreadable because it is not in the dictionary 
		in the output data area from the dith character.
  ==================================================*/
integer_16 TDIC5009(di) register integer_16 di; {
	register BYTE *si;
	BYTE ah,al;

	/*
	 * Set the accent raw information.
	 *	Basic type is flattened type.
	 *	When it is combined, flatten the preceding word, and it is pronounced with high pitch, and the entire sentence becomes raised ending.
	 */
	stc_accent_raw[stc_ptr][0]=0;
	stc_accent_raw[stc_ptr][1]=1;
	stc_accent_raw[stc_ptr][2]=5;

	/* Set the phonetic symbol.*/
	si=(&inert[ceptr*2]);
	ah=(*si++); al=(*si);
	/* A long vowel is exceptionally processed.*/
	if(ah==0x21 && al==0x3C){
		cpron_len=1; al=0xC0; goto TDIC5009_KANA;
	}
	/* The special symbols are not read.*/
	if(ah!=0x24){
		cpron_len=1; al=0xFF; di=OMEGA1000(al,di); goto TDIC5009_END;
	}
	/* Hiragana */
	cpron_len=1;
	if(kana_mora()==0){ goto TDIC5009_END; }
	al=kkana_buf[0];
TDIC5009_KANA:;
	di=OMEGA1000(al,di);
	goto TDIC5009_END;
TDIC5009_END:;
	return di;
}

/***************************** END OF ILE_TDIC.C *****************************/

