#if !defined(O_TALKONLY)
/************************************************
	ILE_MRUC.C	updated at 18th December 1990
	Matters related to learning
 ************************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_edic.h"
#include	"ile_errh.h"
#include	"ile_fddh.h"
#include	"ile_idic.h"
#include	"ile_jknh.h"
#include	"ile_kkhh.h"
#include	"ile_mruh.h"
#include	"ile_nydh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"
#include "ile_rnsc.h"

/*========== MRU_CSENT() =================================================
	Function: Learn the conversion results up to the current watching sentence.
			(When the current watching sentence is unconvertible, it learns up to before the sentence.)
  ===================================================GksfChbGakushuusuru==*/
void MRU_CSENT() {
	/* Return stacks until it reaches the watching sentence as long as the sentence is not unconvertible.*/
	/***if(kkhstat!=funou)then STACK_POP_FS(); fi***/
	/* Learn the element on the stack.*/
	MRU_ALL();
}


/*========== MRU_ALL() =================================================
	Function: Learn the current conversion result.
			(When there is an unconvertible sentence, it learns up to before the sentence.)
	Note: Note the sequence of abandoning processing and placement processing.
  ======================================================================*/
void MRU_ALL() {
	register integer_16 p;
	/*
	 * Leans the accent combination.
	 * Note that this processing is not related to the watching sentence position.
	 */
	for(p=stc_ptr;p--;){
		if(stc_mru[p] & (BITMRU_ACON|BITMRU_ACOFF)){
			ceptr=stc_in_ptr[p];
			celen=stc_in_len[p];
			switch(stc_kind[p]){
			case DICKIND_I:
				IDIC_ACC_STUDY(p);
				break;
			case DICKIND_E:
				EDIC_ACC_STUDY(p);
			}
		}
	}

	/* Learning is not required when none of the next target, longer segment, or shorter segment processing is executed.*/
	if(MRU_OR_NOT==0){ return; }

	/***if(kkhstat==funou){***/	/* If it is in unconvertible state, */
		/***STACK_POP_WS();***/		/* Return the stack until it reaches the current watching sentence.*/
		/* watching sentenceHowever, when the it is the top sentence, it is stc_ptr=0 at this point.*/
		/*if(ws_no==1){ return; }*/
	/***}***/
	kkhstat=mru;					/* It is in learning state. */

	for(ceptr=n_inert;ceptr--;){
		for(celen=n_inert-ceptr;celen;--celen){
			/* If the dictionary has been used, abandon the use of the dictionary.*/
			if(celen<=MAX_IDIC && JknfAttrAri(BITDUT_ID_USE)){
				IDIC_ABORT();
			}
			if(celen<=MAX_EDIC && JknfAttrAri(BITDUT_ED_USE)){
				EDIC_ABORT();
			}
		}
	}

	for(p=stc_ptr;p--;){			/* For each element */
		ceptr=stc_in_ptr[p]; celen=stc_in_len[p];
		/* If it is either the external or internal dictionary, erase the flag in the search table, and learn the conversion result.*/
		switch(stc_kind[p]){
		case DICKIND_I:
			JknfAttrToru(BITDUT_ID_USE);
			IDIC_MRU(p);
			break;
		case DICKIND_E:
			JknfAttrToru(BITDUT_ED_USE);
			EDIC_MRU(p);
		}
	}
}


/*========== MRU_REMEMBER() ========================
	Function: Record the word used in the current conversion result.
  ==================================================*/
void MRU_REMEMBER() {
	register integer_16 p;
	register integer_16 len;
	integer_16 ptr;

	for(p=stc_ptr;p--;){
		ptr=stc_in_ptr[p];
		len=stc_in_len[p];
		switch(stc_kind[p]){
		case DICKIND_I:
			JknfAttrAdd3(BITDUT_ID_USE,ptr,len);
			break;
		case DICKIND_E:
			JknfAttrAdd3(BITDUT_ED_USE,ptr,len);
		}
	}
}


/*========== IDIC_MRU(p) ==================
	Function: Learn the connection information of the current element.
	Input: p = Element number
  ====================NjsfStzGakushuusuru==*/
void IDIC_MRU(p) integer_16 p; {
	register BYTE *si,*di;
	BYTE tmp;
	integer_16 len;

	/* Fetch the internal dictionary offset.*/
	di=FddHDR+stc_ed_ofs[p];
	/* Erase the abandon flag.*/
	((IDIC_DATA *)di)->idic_mru &= ~BITMRU_ABORT;
	/*
	 * Search the first element that is written in the same way as the watching element.
	 * If no element is found, the dictionary is damaged.
	 */
	if(IDIC2000()==0){ jp_ERROR(Err_Fatal_Idic); }
	/* Fetch the position of the first element that is written in the same way.*/
	si=idic_addr;
	/* If the first element written in the same way is not the watching element, switch the fixed information part.*/
	if(di!=si){
		for(len=SIZE_IDIC; len--; ++si,++di){
			tmp=(*si); *si=(*di); *di=tmp;
		}
	}
}


/*========== IDIC_ABORT() ==============================================
	Function: Abandon the use of the internal dictionary element that is written in the same way as the watching element.
  ====================================================NjsfYomHoukisuru==*/
void IDIC_ABORT() {
	/* Look up the internal dictionary.If it is not found, the dictionary is damaged.*/
	if(IDIC2000()==0){ jp_ERROR(Err_Fatal_Idic); }
	do{
		((IDIC_DATA *)idic_addr)->idic_mru |= BITMRU_ABORT;
	}while(IDIC3000());
}


/*========== IDIC_ACC_STUDY(p) ===================
	Function: Learn whether or not to combine the accents of the words in the internal dictionary
	Input: p = Element number
  ================================================*/
void IDIC_ACC_STUDY(p) integer_16 p; {
	idic_addr=FddHDR+stc_ed_ofs[p];
	if(stc_mru[p] & BITMRU_ACOFF){
		((IDIC_DATA *)idic_addr)->idic_mru |= BITMRU_ACOFF;
		((IDIC_DATA *)idic_addr)->idic_mru &= ~BITMRU_ACON;
	}else{
		((IDIC_DATA *)idic_addr)->idic_mru |= BITMRU_ACON;
		((IDIC_DATA *)idic_addr)->idic_mru &= ~BITMRU_ACOFF;
	}
}


/*========== EDIC_MRU_INIT() ===========
	Function: Initialize the leaning state.
  ======================================*/
void EDIC_MRU_INIT() {
	EdicMruDone_LBN[0]= EdicMruDone_OFS[0]= 0;
}


/*========== EDIC_MRU_NEED(Page,bp,f2) =====================
	Input: Page	External dictionary page number where the current watching word exists
 		bp	Address of the current watching word
 		f2	Address of the preceding word of the homonym
	Output: 0		No learning is required
 		  1		Learning is required
	Function: Check whether or not to learn the current word.
  ==========================================================*/
BOOL EDIC_MRU_NEED(Page,bp,f2) WORD Page; LPBYTE bp,f2; {
	register integer_16 si;
	register WORD ax;
	WORD bx;

	si=0; ax=Page; bx=(WORD)(f2-edic_page_addr);
	/* It compares the current word with the information of words that have been learned and determines whether or not to learn it.*/
	while(1){
		/* It ends when all checks are done.*/
		if((EdicMruDone_LBN[si]==0)&&(EdicMruDone_OFS[si]==0)){ break; }
		/* When the page number matches with the offset in page, learning is not performed.*/
		if((EdicMruDone_LBN[si]==ax)&&(EdicMruDone_OFS[si]==bx)){ return 0; }
		si++;
	}
	/* Store the information of the word to be learned.*/
	EdicMruDone_LBN[si]=ax; EdicMruDone_OFS[si++]=bx;
	/* Insert a stopper of the table.*/
	EdicMruDone_LBN[si]=0; EdicMruDone_OFS[si]=0;
	return 1;
}


/*========== EDIC_MRU(p) =====================================================
	Function: Learn the connection information of the current watching word.Move the information of the current watching word to the top of the homonym, and 
 		rewrite it in the external dictionary.
	Input: p = Element number
  ============================================================================*/
void EDIC_MRU(p) register integer_16 p; {
	LPBYTE bp,f1,f2;
	integer_16 mru=0;

	/* Read the external dictionary, and obtain the address in edic_page_addr.*/
	RnsfReadEdic(stc_ed_pag[p],&edic_page_addr);
	/* Calculate the address of flag 2.*/
	bp=stc_ed_ofs[p]+edic_page_addr;

	/* Search the flag 1 of the same-character word group and the flag 2 of the top word.*/
	EdicfSentouSagasu(bp,&f1,&f2);

	/*
	 *	If the same-character word group has been learned before, learning is not performed.
	 *	If it learns improperly, after the sequence is changed, 
	 *	it uses edic_ofs before the change to clear the abandon flag.
	 *	As an inevitable consequence, it damages the dictionary after the change.
	 *Do not perform learning when the page number matches with the position of the flag 2 of the preceding word.
	 *	As long as there is only one target, the above matter does not cause any problems.
	 */
	if(EDIC_MRU_NEED(stc_ed_pag[p],bp,f2)==0){ return; }

	if(*(bp+1) & BITMRU_ABORT){		/* When the abandon flag is added,*/
		*(bp+1) &= ~BITMRU_ABORT;		/* erase the abandon flag.*/
		mru=1;
	}

	/* When the current watching word is not the top of the homonym, it is necessary to change the sequence.*/
	if(f2!=bp){
		EdicfToridasu(bp);		/* Retrieve the watching word, and measure its length.*/
		EdicfShift(bp-1, bp+ed_ndata-1, (integer_16)(bp-f2)); /* Close up the retrieved place.*/
		EdicfIreru(f2);			/* Insert the watching word at the top of the same-character word.*/
		mru=1;
	}

	if(mru){
		RnsfWriteEdic(stc_ed_pag[p]);		/* Write the learning result.*/
	}
}


/*========== EDIC_ABORT() =========================================
	Function: Abandon the use of the external dictionary element that is read in the same way as the current word.
  =================================================================*/
void EDIC_ABORT() {
	LPBYTE bp;
	/* If the reading of the word is not found in the external dictionary, the dictionary is damaged.*/
	if(EDIC2000()==0){ jp_ERROR(Err_Fatal_Edic); }
	bp=edic_ofs+edic_page_addr;
	if((*(bp+1) & BITMRU_ABORT)==0){		/* When the abandon flag is not added,*/
		*(bp+1)|=BITMRU_ABORT;				/* add the abandon flag.*/
		RnsfWriteEdic(edic_page_no);		/* Write the learning result.*/
	}
}


/*========== EDIC_ACC_STUDY(p) ===================
	Function: Learn whether or not to combine the accents of the words in the external dictionary
	Input: p = Element number
  ================================================*/
void EDIC_ACC_STUDY(p) integer_16 p; {
	LPBYTE bp;
	/* Read the external dictionary, and obtain the page top address in edic_page_addr.*/
	RnsfReadEdic(stc_ed_pag[p],&edic_page_addr);
	bp=stc_ed_ofs[p]+edic_page_addr;
	if(stc_mru[p] & BITMRU_ACOFF){
		*(bp+1)|= BITMRU_ACOFF;
		*(bp+1)&= ~BITMRU_ACON;
	}else{
		*(bp+1)|= BITMRU_ACON;
		*(bp+1)&= ~BITMRU_ACOFF;
	}
	RnsfWriteEdic(stc_ed_pag[p]);		/* Write the learning result.*/
}


/*========== EdicfToridasu(bp) ======================================
	Input: bp			Address of the word to be fetched
	Output: ed_data		Fetched word
 		ed_ndata		Length of the fetched word
	Function: Fetch the watching word (from flag 2 to the phonetic symbol), and
 		measure the length.
  ==================================================================*/
void EdicfToridasu(LPBYTE bp)
{
	register integer_16 a_len,p_len;
	integer_16 bx;
	BYTE al;

	bx=0;						/* Resetting the record length */
	al=ed_data[bx++]=(*bp++);	/* Fetch the flag 2. */

	/* Search a bug of learning.*/
	if(sign(al)==0){ jp_ERROR(Err_Fatal_Edic); }

	/* Fetch the learning information and the grammar code. */
	do{ ed_data[bx++]=(*bp++); }while(sign(*bp));

        p_len=(*bp++);
	ed_data[bx++]=(BYTE)p_len;
	a_len=p_len>>4;				/* length of accent information */
	p_len &= 0x0F;				/* length of pronunciation information */

	/* accent information */
	for(;a_len--;){ ed_data[bx++]=(*bp++); }

	/* pronunciation information */
	for(;p_len--;){ ed_data[bx++]=(*bp++); }

	ed_ndata=bx;	/* Length of the fetched word */
}


/*========== EdicfIreru(bp) ========================
	Input: bp			Address to be input
 		ed_data[]		Word to be input
 		ed_ndata		Length of the word to be input
	Function: Input the watching word to the specified place.
  =================================================*/
void EdicfIreru(bp) LPBYTE bp; {
	register BYTE *si;
	register integer_16 cx;
	for(cx=ed_ndata,si=ed_data;cx--;){
		*bp++=(*si++);
	}
}


/*========== EdicfShift(si,di,cx) =============
	Function: Move the data for the sequence change of learning
  ============================================*/
void EdicfShift(LPBYTE si, LPBYTE di, integer_16 cx)
{
	for(;cx--;)
	{
		*di-- = (*si--);
	}
}


/*========== EdicfAkeru(cx,bp) =============================================
	Input: bp			Address to be opened up
 		  cx			Number of bytes to be opened up
	Function: Open up space of the specified number of bytes from the specified place in the external dictionary.
  =========================================================================*/
void EdicfAkeru(cx,bp) register integer_16 cx; LPBYTE bp; {
	register integer_16 ax;
	LPBYTE si,di;

	ax=Fdd_BlkSize*Fdd_Header.Fdd_EdicPageSize;
	si=edic_page_addr+(ax-cx); di=edic_page_addr+ax;
	cx=ax-((integer_16)(bp-edic_page_addr)+cx);
	for(;cx;--cx){
		*(--di)=(*(--si));
	}
}


/*========== EdicfTsumeru(cx,bp) ===========================================
	Input: bp			Address to be closed up
 		  cx			Number of bytes to be closed up
	Function: Close up the contents of the specified number of bytes from the specified place in the external dictionary.
  =========================================================================*/
void EdicfTsumeru(cx,bp) register integer_16 cx; LPBYTE bp; {
	LPBYTE si;

	si=bp+cx;
	cx=Fdd_BlkSize*Fdd_Header.Fdd_EdicPageSize-(WORD)(bp-edic_page_addr)-cx;
	for(;cx;--cx){
		*bp++=(*si++);
	}
}


/*========== EdicfSentouSagasu(bp,&f1,&f2) ===========================================
	Input: es:[di+bp]	Address of flat 2 of the current watching word
	Output: f1			Address of flag 1 of the first same-character word
		f2			Address of flag 2 of the first same-character word
	Function: Obtain the address of the top word in the same-character word group that includes the current watching word
  ==============================================================================*/
void EdicfSentouSagasu(bp,f1,f2) LPBYTE bp,*f1,*f2; {
	LPBYTE save,bx;

	bx=edic_page_addr;				/* Start checking from the top of the page.*/
	while(1){
		if(bx>=bp){ break; }	/* If it is the flag 1 after the watching word, the processing ends.*/
		save=bx;					/* Record the offset in page of the flag 1.*/
		bx+=(*(bx+1)+2);
	}
	*f1=save;				/* Recorded offset in page of the flag 1 */
	bx=save+2;				/* Offset in page of the keyword */
	while(sign(*bx)==0){ ++bx; }	/* Skip the keyword.*/
	*f2=bx;
}

/***************************** END OF ILE_MRUC.C *****************************/
#endif

