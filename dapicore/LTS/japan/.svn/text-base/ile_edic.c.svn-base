/*************************************************
	ILE_EDIC.C	updated at 13th September 1990
	External dictionary
 *************************************************/

#define		EXT		extern

//#include <stddef.h> //moved to port.h for each platform MLT 01/24/06
#include "port.h"
#include	"onsei.h"
#include	"ile_edic.h"
#include	"ile_envh.h"
#include	"ile_errh.h"
#include	"ile_fddh.h"
#include	"ile_jknh.h"
#include	"ile_kkhh.h"
#include	"ile_mruh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"
#include "ile_rnsc.h"

LPBYTE Fdd_EdicIndex = NULL;

/*========== EDIC1000() ==========================================
	Function: Check whether or not there is a possibility that the current watching word exists in the external dictionary.
  ===============================================GjsfKanouseiAri==*/
BOOL EDIC1000() {
	BYTE al;
 	/*
	 *	When it exceeds the maximum number of characters of keyword in the external dictionary, there is no possibility.
	 *	When it is recorded that there is no notation in the dictionary search table, there is no possibility.
	 *
	 *	The external dictionary does not contain any word that begins with a double consonant or syllabic nasal.--- lie: For example, "ヵ月 (KAGETSU)"
	 *	if(inert_attr[ceptr]==CHRATTR_Soku)then goto nashi; fi
	 */
	if(celen>MAX_EDIC){ goto nashi; }
	if(JknfAttrAri(BITDUT_ED_NONE)){ goto nashi; }
	/*
	 * When the initial abandoned word search is instructed, if the searched word is not an initial abandoned word, there is no possibility.
	 * if(StzfAttrAri(Stz_CE,stz_mru,BITMRU_ABORT) &&
	 * (JknfAttrAri(BITDUT_ED_ABORT)==0)){ goto nashi; }
	 */
	/* When the backward lookup is not instructed, if the searched word in not a symbol, there is no possibility.*/
	if(ceptr!=0){
		if(pe_is_kango){ goto ari; }
		if(StzfAttrAri(Stz_PE,stz_ctl,BITCTL_FEDIC)==0){
			al=inert[ceptr*2];
			if(al==0x24){ goto nashi; }
			if(al==0x25){ goto nashi; }
			if(al>0x2F){ goto nashi; }
		}
	}
	ari:	return 1;
	nashi:	return 0;
}


/*========== EDIC2XXX() ====================================================
	Function: Obtains the offset in page of the external dictionary that has the same notation as the current word notation and that matches the required current state,
 		, and specify the connection information of the current word.
  =====================================================GjsfYomChantoSagasu==*/
BOOL EDIC2XXX() {
	LPBYTE bp;

	/* When the searched word exists in the dictionary search table, */
	if(JknfAttrAri(BITDUT_ED_EXIST)){
		/* obtain the external dictionary block that has the specified notation.*/
		edic_page_no = EDIC2100();
		/* Load the external dictionary, andobtain the page top address in edic_page_addr.*/
		RnsfReadEdic(edic_page_no,&edic_page_addr);
		/* From the dictionary search table, retrieve the offset in page, and save the position of the flag 2.*/
		edic_ofs=JknfEdicToridasu;
		bp=edic_ofs+edic_page_addr;
	}else{
		/* If it cannot be found, make sure to search properly.*/
		if(EDIC2000()){
			bp=edic_ofs+edic_page_addr;
			/* When the searched word is found, record that the word is found in the external dictionary.*/
			JknfAttrAdd(BITDUT_ED_EXIST);
			/* Store the offset in page in the dictionary search table.*/
			JknfEdicShimau(edic_ofs);
		}else{
			/* When it cannot be found, record that the word is not found in the external dictionary.*/
			JknfAttrAdd(BITDUT_ED_NONE);
			return 0;
		}
	}

	/* When the learning function is available, learn the current element.*/
	if(kkhstat!=mru){
		/* When the current watching element is the initial abandoned word*/
		/* Note:  This processing is for learning breaks of segment,
				 do not search the same character word without an abandoning flag.*/
		if(*(bp+1) & BITMRU_ABORT){
			/* When the initial abandoned word is not the search target,*/
			if(StzfAttrNashi(Stz_CE,stz_mru,BITMRU_ABORT)){
				/* record the initial abandoned word in the dictionary search table, and abandon the watching element.*/
				JknfAttrAdd(BITDUT_ED_ABORT);
				return 0;
				/*return EDIC3XXX();*/
			}
		}else{
			/* When the watching element is the initial adoption element, 
			   if the initial abandoned word is set as a search target, the watching element is abandoned. */
			if(StzfAttrAri(Stz_CE,stz_mru,BITMRU_ABORT)){
				return 0;
				/*return EDIC3XXX();*/
			}
		}
	}
	
	/* When the current watching element is the user deletion word,*/
	if(*(bp+1) & BITMRU_DEL){
		/* search the next same-character word.*/
		if(EDIC3XXX()==0){				/* The processing ends when no same-character word is found.*/
			JknfAttrAdd(BITDUT_ED_NONE);	/* Record that the search target is not in the external dictionary.*/
			return 0;
		}
	}

	/* Specify the connection information of the current word.*/
	EDIC4000();
	return 1;
}


/*========== EDIC2000() ===================================================
	Function: Obtain the offset in page and the page top address of the external dictionary that has the word that starts at the current element start position and 
		measures up to the current element length.
  ==========================================================GjsfYomSagasu==*/
BOOL EDIC2000() {
	register BYTE *si;
	register integer_16 bx;
	BYTE cechr,al;
	integer_16 ax,dist,ed_nsame_old;
	LPBYTE bp,f1;

	edic_page_no = EDIC2100();		/* Obtain the external dictionary page number that has the specified notation.*/
	RnsfReadEdic(edic_page_no,&edic_page_addr);
							/* Load the external dictionary, andobtain the page top address in edic_page_addr.*/
	bp=edic_page_addr;		/* Initialize the address in the external dictionary page.*/
	bx=0;					/* Initialize the number of the bytes compared.*/
	ed_nsame=0;

	si=ceptr*2+inert;

	while(1){
		f1=bp;		/* Store the position of flag 1.*/
		/* Fetch the flag 1, and obtain the number of bytes in the word of which notation that matches with the preceding word.*/
		ax=(*bp++) & 0x1F;	/* tail 5 bit */
		/* At the end of the external file, store the end position of the block.*/
		if(ax==0x1F){ goto EDIC2000_997; }
		/* get distance to next flag 1 */
		dist=(*bp++);
		/* If the number of bytes matched is greater than the number of bytes compared, 
		   comparing the rest is meaningless, so skip the comparison to the next flag 1.*/
		if(ax>bx){ goto EDIC2000_500; }
		/* IF it is the same or smaller, re-specify the number of bytes compared.*/
		if(ax<bx){ goto EDIC2000_997; }
		/*bx=ax;*/
		/* Until the number of bytes compared becomes the same as the notation of the current word, */
		while(bx!=celen*2){
			cechr=si[bx];
			al=(*bp);					/* fetch one byte. */
			/* If it is flag 2, skip the reading up to the next flag 1.*/
			if(sign(al)){ goto EDIC2000_500; }
			bp++;
			/* If it is smaller than the current word, skip the reading up to the next flag 1.*/
			if(al<cechr){ goto EDIC2000_500; }
			/* Compared to the current word, if it is larger,  */
			if(al>cechr){ goto EDIC2000_997; }	/* the current word does not exist in the dictionary. */
			/* Store the matched length.(This processing is performed in dictionary registration.)*/
			++bx; ed_nsame=bx;
			/*ed_same[bx++]=al;*/
		}
		/* When the current word completely match with the current watching word, */
		if((*bp & 0xC0)==0x80){	/* 10?????? */
			/*ed_same[bx]=0;*/		/* After watched reading, add 0.*/
			edic_ofs=(WORD)(bp-edic_page_addr);	/* Store the position of flag 2.*/
			/* Assume that there is a notation, and return.*/
			/* It is ed_nsame==celen*2.*/
			/*return edic_ofs;*/
			return 1;
		}else{
			goto EDIC2000_997;
		}

		EDIC2000_500:
		ed_nsame_old=ed_nsame;
		bp=f1+dist+2;	/* Skip the reading up to the next flag 1.*/
	}
EDIC2000_997:;
	/*
	 *	When it is not found, specify the number of bytes that matches with the previous word.
	 *	Set edic_ofs so that it indicates the address of the flag 1.
	 *	This is used for dictionary registration.
	 */
	ed_nsame=ed_nsame_old;
	edic_ofs=f1-edic_page_addr;
	return 0;
}


/*========== EDIC2100() ======================================================
	Function:	Obtain the block number and the page number of the block in the 
				external dictionary that has the word that starts at the current 
				word start position and measure up to the current word length.
  =============================================================GjmfYomSagasu==*/
unsigned short EDIC2100() 
{
	register BYTE *si;
	register integer_16 dif;
	integer_16 cx,len,cebyte;
	integer_16 LL,UL,IP;
	LPBYTE di;
	WORD offset;
	
	cebyte=celen*2;
	
	LL=0;								/* ページ番号下限 */
	UL=Fdd_Header.Fdd_EdicNoPage;		/* ページ番号上限 */
	IP=UL/2;							/* 初回比較位置 */
	
	do{
		si=inert+ceptr*2;				/* 検索文字のオフセット */
		di=3*IP+Fdd_EdicIndex;
		cx=(WORD)*(di+2);
		
		/* offset=(*(WORD far *)di); */
		offset= *di + (*(di+1)<<8);
		di=Fdd_EdicIndex+Fdd_Header.Fdd_EdicKeyOfs+offset;
		
		/* Compare the notations.*/
		for(len=cebyte;len--;--cx){
			if(cx){
				if(dif=(*di++)-(*si++)){ goto EDIC2100_170; }
			}else{
				dif=(-1); goto EDIC2100_170;
			}
		}
		if(cx){
			dif=1;
		}else{
			goto EDIC2100_900;
		}
		
EDIC2100_170:;
/** When the watching external dictionary keyword is longer, specify the upper limit 
	of the table lookup as the current watching number.
	When the watching external dictionary keyword is shorter, specify the lower limit 
	of the table lookup as the current watching number.  */
			 if(dif>0){
				 UL=IP; IP=(LL+IP)/2; dif=IP-UL;
			 }else{
				 LL=IP; IP=(IP+UL)/2; dif=IP-LL;
			 }
	}while(dif);						/* If the result is different from the last comparison position, repeat it.*/
	
EDIC2100_900:
	/* Obtain the page number on FD according to the block number. */
	edic_page_no=Fdd_Header.Fdd_EdicPageSize*IP+Fdd_Header.Fdd_EdicPageOfs+1;

	return edic_page_no;
}


/*========== EDIC3XXX() ===============================
  Function:  Obtain the position of the next homonym after the word in the external dictionary.
  ===============================GjsfTsugiTangoSagasu==*/
BOOL EDIC3XXX() 
{
	LPBYTE bp;

	while(1){
		/* When there is no next target, the processing ends.*/
		if(EDIC3000()==0){ return 0; }
		bp=edic_ofs+edic_page_addr;
		if((*(bp+1) & BITMRU_DEL)==0){ return 1; }
		/* When it is a deleted word, search the next.*/
	}
}


/*========== EDIC3000() ===============================
  Function:   Obtain the position of the next homonym after the word in the external dictionary.
  ===============================GjsfTsugiTangoSagasu==*/
BOOL EDIC3000() {
	LPBYTE bp;
	BYTE al;

	bp=edic_ofs+edic_page_addr;		/* Fetch the current watching position.*/

	/* If there is the flag 2, skip it.If not, the dictionary is damaged.*/
	if((*bp & 0xC0)!=0x80){ jp_ERROR(Err_Fatal_Edic); }
	bp++;

	/* Skip the learning information and grammar code if there is any.*/
	do{ bp++; }while(sign(*bp));
	/* Skip the accent information and the phonetic information.*/
	al=(*bp);
	bp+=(al>>4)+(al & 0x0F)+1;

	edic_ofs=(WORD)(bp-edic_page_addr);	/* Store the current watching position.*/
	if((*bp & 0xE0)==0xE0){ return 0; }		/* If it is the flag 1, there is no next target.*/

	/* Specify the connection information of the current word.*/
	EDIC4000();
	return 1;
}


/*========== EDIC4000() ====================
	Function: Specify the connection information of the current word.
  ====================GjsfGzgStzSetteisuru==*/
void EDIC4000() 
{
	LPBYTE bp;
	BYTE al,ah;

	StzfElmKind(&Stz_CE,DICKIND_E);	/* Types of words are to be in external dictionary.*/
	bp=edic_ofs+edic_page_addr;		/* Current word address*/
	Stz_CE.stz_f2=(*bp++);			/* Fetch the flag 2.*/
	al=(*bp++);
	ah=Stz_CE.stz_mru;				/*(Carry over the previous abandoned word flag.)*/
	ah &= BITMRU_ABORT;
	al &= ~BITMRU_ABORT;
	Stz_CE.stz_mru=al|ah;

	/* Specify all grammar codes.*/
	while(1){
		al=(*bp++);						/* Fetch one byte of the external dictionary information.*/
		if(sign(al)==0){ break; }	/* Stop if it is not the grammar code.*/
		al &=MaskEdicGrcd;				/* Fetch the grammar code part.*/
		StzfGrcdStore(al);				/* Add the grammar code.*/
	}

	/* Grammar code -> back-end number, forward vector number, or control information */
	StzfGrcdOR();
}


/*========== EDIC5000(di) ===============================================
	Function: Store the phonetic symbol of the current element in the output data area from the dith character.
  ======================================================GjsfKekMotomeru==*/
integer_16 EDIC5000(integer_16 di) 
{
	register BYTE *si;
	register integer_16 cx;
	integer_16 a_len,p_len;
	BYTE ah,al,*ti;
	LPBYTE bp;

	/* Fetch the current watching position (position of the flag 2), and skip the flag 2.*/
	bp=edic_ofs+edic_page_addr; 
	bp++;
	/* Skip the learning information and grammar code if there is any.(MSB of the grammar code is ON.) */
	do{ bp++; }while(sign(*bp));

	p_len=(*bp++);
	a_len=p_len>>4;				/* length of accent information */
	p_len &= 0x0F;				/* length of pronunciation information */

	for(cx=a_len;cx--;)
	{
		al=(*bp++);
		ah=al/16; al=al%16;
		if(ah<10){ stc_accent_raw[stc_ptr][ah]=al; } /* accent raw data */
	}

	ACC0010();

	/* Fetch the phonetic information.*/
	if(p_len==0)
	{
		cpron_len=0;

		si= &inert[ceptr*2]; 
		ti=inert_kana;
		for(cx=celen*2;cx--;)
		{ 
			*ti++=(*si++); 
		}
		*ti=0x00;

		cx=mkhatu(inert_kana,inert_pron);

		for(si=inert_pron;cx--;++si)
		{
			di=OMEGA1000(*si,di); 
			++cpron_len;
		}
	}
	else
	{
		for(cx=cpron_len=p_len;cx--;)
		{
			al=(*bp++); 
			di=OMEGA1000(al,di);
		}
	}
	/*
	 *	When it can be connected with long vowel, and the next character is not a long vowel, add a long vowel.
	 *	However, if it is in correction mode, do nothing.
	 */
	if(onsei_addr->onsei_kouseisystem){ goto EDIC5000_990; }
	for(cx=Stz_CE.stz_nbno;cx--;)
	{
		if(Stz_CE.stz_bno[cx]==60){ goto EDIC5000_700; }
	}
	goto EDIC5000_990;
EDIC5000_700:
	if((cx=ceptr+celen)==n_inert){ goto EDIC5000_770; }
	if(inert[cx*2]!=0x21||inert[cx*2+1]!=0x3C)
	{
		EDIC5000_770:
		di=OMEGA1000(0xC0,di); cpron_len++;
	}
EDIC5000_990:
	return di;
}


void ACC0010(void) 
{
	register BYTE *di;
	if(chk_limits(Fdd_Header.Fdd_GrcdNum1,Fdd_Header.Fdd_GrcdNum2,
		Stz_CE.stz_grcd,Stz_CE.stz_ngrcd)==0)
	{
		/* If it is not a counter suffix, perform the following processing.*/
		di= &stc_accent_raw[stc_ptr][0];
		if(*(di+4)==0x00 && *(di+1))
		{
			if(*di)
			{
				*(di+4)=(*di);	/* (*di) is not Flattened type */
			}
			else
			{
				*(di+4)=1;		/* (*di) is Flattened type */
			}
		}
		if(*di==0x0F)
		{
			*di= 0;
			*(di+1)= *(di+2)= *(di+4)= 1;
		}
		if(*(di+4)==0x0F)
		{
			*(di+4)=0;
		}
	}
}

/***************************** END OF ILE_EDIC.C *******++++******************/

