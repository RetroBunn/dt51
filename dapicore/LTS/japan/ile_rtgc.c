/*************************************************
	ILE_RTGC.C	updated at 12th September 1991
	Deletion of dictionary registration
 *************************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_edic.h"
#include	"ile_envh.h"
#include	"ile_errh.h"
#include	"ile_fddh.h"
#include	"ile_kkhh.h"
#include	"ile_mruh.h"
#include	"ile_nydh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"
#include "ile_rnsc.h"

/*========== EDIC_ADD() ====================
	Function: Register the user-defined word with the external dictionary.
  =============================RtgfTouroku==*/
void EDIC_ADD() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	register integer_16 cptr,nptr;
	integer_16 cx;
	BYTE al,ah,l;
	LPBYTE f1,f2,bp;

	kkhstat=shoki;				/* Make the initial setting. */
	INERT_INIT();				/* Move the input data to the input work area. */
	PRON_INIT();				/* Initialize the conversion processing-related area. */
	ceptr=0; celen=n_inert;
	if((RtgfNydShiraberu()==0) || (EDIC1000()==0)){
		/* Either notation or reading is not appropriate as a registered word. */
		ERROR5000(); jp_ERROR(Err_EdicTooLong);
	}
	ed_ndata=0;					/* Initialize the length of an additional word. */

	/* Look up the external dictionary, and if the corresponding reading is not found, add one from the flag 1.(case 3) */
	if(EDIC2000()==0){ goto EDIC_CASE_3; }

	/* When the corresponding reading is found in the external dictionary, */
	do{
		bp=edic_ofs+edic_page_addr;
		/* if the notation in the external dictionary matches with the notation of the registered word, and if the grammar code of the registered word is 
		the grammar code of the user-defined word, restore the deletion flag.(case 1) */
		if(RtgfKnjHykOnaji(bp) && RtgfGrcdAri(Fdd_Header.Fdd_GrcdUsr,bp)){
			goto EDIC_CASE_1;
		}
	}while(EDIC3000());

	/* If the next target does not exist, add one from the flag 2.(case 2) */
	/* case 2 */
	bp=edic_ofs+edic_page_addr;
	/* Search the flag 1 of the same-character word group and the flag 2 of the top word. */
	EdicfSentouSagasu(bp,&f1,&f2);
	edic_ofs=(WORD)(f2-edic_page_addr);
	/* Create the flags subsequent to the flag 2. */
	RtgfKchTsukuru(0);
	/* Check whether or not the created additional words can be stored in the page. */
	if(RtgfTsuikaKanou()==0){ jp_ERROR(Err_EdicOVF); }
	/*
	 * Update the number of bytes up to the next flag 1.
	 * In this processing, the contents of the page is overwritten.
	 * Before the page is overwritten, make sure it will not overflow.
	 */
	al=(*(f1+1)); al+=ed_ndata; *(f1+1)=al;
	goto EDIC_INSERT;	/* Add one from the flag 2. */

EDIC_CASE_1:
	/* case 1 */
	if((al=(*(bp+1))) & BITMRU_DEL){
		/* When the deletion flag is set, remove it and write.*/
		*(bp+1) = (al & ~BITMRU_DEL);
		goto EDIC_WRITE;
	}else{
		/* When the deletion flag is not set, it has been registered already, so an error is generated.*/
		jp_ERROR(Err_TourokuSumi);
	}

EDIC_CASE_3:
	/* case 3 */
	RtgfFlag1Tsukuru();		/* Add one from the flag 1. */
	/* Check whether or not the created additional words can be stored in the page. */
	if(RtgfTsuikaKanou()==0){ jp_ERROR(Err_EdicOVF); }
	bp=edic_ofs+edic_page_addr;
	/* If there is a possibility that the registered word and the next keyword match partially,  */
	if((*bp & 0x1F)==ed_nsame){
		l=0; cptr=2; nptr=2;
		/* measure the matched length . */
		while(1){
			al=(*(bp+nptr));
			ah=ed_data[cptr];
			if(sign(al) || sign(ah)){ goto EDIC_CASE_3_100; }
			if(al!=ah){ goto EDIC_CASE_3_100; }
			++l; ++nptr; ++cptr;
		}
		EDIC_CASE_3_100:;
		if(l==0){ goto EDIC_INSERT; }
		/*
		 * Rewrite the lengths of the flag 1 of the next word and the same-character word group
		 * In this processing, the contents of the page is overwritten.
		 * Before the page is overwritten, make sure it will not overflow.
		 */
		al=(*bp); al=((al & 0x1F)+l)|0xE0; *bp=al;
		al=(*(bp+1)); *(bp+1)=al-l;
		EdicfTsumeru(l,bp+2);
	}

EDIC_INSERT:
	bp=edic_ofs+edic_page_addr;
	cx=ed_ndata;
	EdicfAkeru(cx,bp);			/* Make the space for inserting the additional word.*/
	EdicfIreru(bp);				/* Insert the additional word.*/

EDIC_WRITE:
	RnsfWriteEdic(edic_page_no);	/* Write the changed external dictionary. */
	while(RnsfFlushBuffer());	/* Write the all learning result into the external dictionary. */
#endif
}


#if !defined(O_TALKONLY)
/*========== RtgfFlag1Tsukuru() ==================
	OutputFed_data		Place where the additional word is to be stored
 		  ed_ndata		Length of the additional word
	Function: Create flags subsequent to the flag 1.
  ================================================*/
void RtgfFlag1Tsukuru() {
	register BYTE *si;
	register integer_16 cx; 
	integer_16 di;
	BYTE al;

	/* Create the flag 1 (Set 0 to the length of reading that matches the preceding word.) */
	al=(BYTE)ed_nsame;
	ed_data[0]=0xE0 | al;
	di=2;
	/* Copy the notations. */
	cx=n_inert*2-ed_nsame;
	for(si=(&inert[ed_nsame]);cx--;){ ed_data[di++]=(*si++); }
	ed_ndata=di;
	/* Create the flags subsequent to the flag 2. */
	RtgfKchTsukuru(di);
	/* Set the distance up to the next flag 1.*/
	ed_data[1]=ed_ndata-2;
}
#endif


#if !defined(O_TALKONLY)
/*========== RtgfKchTsukuru(di) ====================
	InputFdi			Position where the flags subsequent to the flag 2 are stored
	OutputFed_data		Place where the additional word is to be stored
 		ed_ndata		Length of the additional word
	Function: Create flags subsequent to the flag 2.
  ==================================================*/
void RtgfKchTsukuru(di) integer_16 di; {
	register BYTE *dptr;
	register integer_16 cx;
	LPBYTE si;

	dptr = &ed_data[di];
	*dptr++ =0x80 | BITFLG2_KANGO;			/* Create  the flag 2. */
#if 1
	*dptr++ =0;								/* Create the learning information. */
#else
	*dptr++ =0 | BITMRU_ACOFF;				/* Create the learning information (personal name).*/
#endif
	*dptr++ =Fdd_Header.Fdd_GrcdUsr | 0x80;	/* Create the grammar codes. */
	ed_ndata+=3;
	/* Create kanji notations. */
	si=onsei_addr->onsei_omega;	/*ShdaChmHaj;*/	/* Fetch the address of the output data area. */

	/*
	 *	byte position
	 *   0		 1	   2...			  L1+2...
	 *	+-------+-----+--------------+--------------------+
	 *	|L1+L2+1|L1/L2| accent codes | pronunciation data |
	 *	+-------+-----+--------------+--------------------+
	 *	              |<-----L1----->|<--------L2-------->|
	 *
	 *	outbuf[0]				: number of total length (L1+L2+1)
	 *	outbuf[1] upper 4 bits	: number of accent code
	 *	outbuf[1] lower 4 bits	: mora number of pronunciation data
	 *	outbuf[2]..				: accent codes
	 *	outbuf[following]..		: pronunciation data
	 */
	ed_ndata += (cx=(*si++));
	for(;cx--;){ *dptr++=(*si++); }
}
#endif


/*========== EDIC_DELETE2() ==============================
	Function: Delete the user-defined word (independent execution) from the external dictionary.
  ===========================================RtgfSakujyo==*/
void EDIC_DELETE2() {
#if !defined(O_DEBUG)
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	register integer_16 cnd;
	BYTE al;
	LPBYTE bp;

	kkhstat=shoki;				/* Make the initial setting. */
	INERT_INIT();				/* Move the input data to the input work area. */
	PRON_INIT();				/* Initialize the conversion processing-related area. */
	ceptr=0; celen=n_inert;
	if((RtgfNydShiraberu()==0) || (EDIC1000()==0)){
		/* Either notation or reading is not appropriate as a registered word. */
		ERROR5000(); jp_ERROR(Err_EdicTooLong);
	}
	cnd=EDIC2000();				/* Look up the external dictionary. */
	do{						/* Until the word of which grammar code matches is found */
		while(1){			/* Until the word of which reading and notation match is found */
			bp=edic_ofs+edic_page_addr;
			/* If the corresponding reading is not found in the external dictionary, set an error code and end. */
			if(cnd==0){ jp_ERROR(Err_MiTouroku); }
			/* It is OK if the notation in the external dictionary matches the output data. */
			if(RtgfKnjHykOnaji(bp)){ break; }
			/* Find the next homonym. */
			cnd=EDIC3000();
		}
		/* It is OK when the grammar code matches the user-defined word. */
	}while(RtgfGrcdAri(Fdd_Header.Fdd_GrcdUsr,bp)==0);

	/* When the deletion flag of the learning information is set, an error is generated. */
	if((al=(*(bp+1))) & BITMRU_DEL){ jp_ERROR(Err_MiTouroku); }
	/* Set the deletion flag. */
	*(bp+1) = (al | BITMRU_DEL);

	RnsfWriteEdic(edic_page_no);	/* Write the updated external dictionary. */
	while(RnsfFlushBuffer());		/* Write the all learning result into the external dictionary. */
#endif
#endif
}


/*========== EDIC_DELETE() =============================
	Function: Delete the user-defined word (conversion word) from the external dictionary.
  ======================================================*/
void EDIC_DELETE() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	LPBYTE bp;
	/*
	 *	When the conversion word consists of one element and has one grammar code, and it is 
	 *	the grammar code of the user-defined word, delete it.
	 */
	if(stc_kind[0]==DICKIND_E && stc_ptr==1){
		if(stc_ngrcd[0]==1 && stc_grcd[0][0]==Fdd_Header.Fdd_GrcdUsr){
			bp=edic_ofs+edic_page_addr;		/* Obtain the address of flag 2.*/
			*(bp+1) |= BITMRU_DEL;			/* Set the deletion flag.*/
			RnsfWriteEdic(edic_page_no);	/* Write the updated external dictionary.*/
			while(RnsfFlushBuffer());		/* Write the all learning result into the external dictionary.*/
			MRU_OR_NOT=0;					/* Specify not to learn this result.*/
			return;
		}
	}
	jp_ERROR(Err_MiTouroku);
#endif
}


#if !defined(O_TALKONLY)
/*========== RtgfKnjHykOnaji(bp) =================
	Function: Check whether or not the notation of the external dictionary and the output data.
  ===================================================*/
BOOL RtgfKnjHykOnaji(bp) LPBYTE bp; {
	register integer_16 cx;
	LPBYTE si;

	bp++;						/* Skip the flag 2. */
	/* Skip the learning information and grammar code if there is any. */
	do{ bp++; }while(sign(*bp));

	si=onsei_addr->onsei_omega;	/*ShdaChmHaj;*/ /* Fetch the address of the output data area. */
	cx=(*si++);
	for(;cx--;){
		if(*si++!=(*bp++)){ return 0; }
	}
	return 1;
}
#endif


#if !defined(O_TALKONLY)
/*========== RtgfGrcdAri(grcd,bp) ====================
	InputFgrcd	Grammar code
	Function: Check whether or not the current watching word has the specified grammar code.
  =======================================================*/
BOOL RtgfGrcdAri(grcd,bp) BYTE grcd; LPBYTE bp; {
	bp+=2;								/* Skip the flag w and the learning information. */
	while(sign(*bp)){				/* As long as the grammar codes exist, */
		/* if the grammar code matches the specified grammar code, */
		if((*bp & 0x7F)==grcd){ return 1; }
		bp++;
	}
	return 0;
}
#endif


#if !defined(O_TALKONLY)
/*========== RtgfTsuikaKanou() ====================
	Function: Check whether or not the dictionary registered word can be stored in the page.
	Value: ‚O	Insufficient free space in the dictionary
		‚P	Sufficient free space in the dictionary
  =================================================*/
BOOL RtgfTsuikaKanou() {
	register integer_16 cx;
	LPBYTE bp;

	bp=edic_page_addr+(Fdd_BlkSize*Fdd_Header.Fdd_EdicPageSize-1);
	cx=0;
	while(1){
		if(*bp==0xFF){ ++cx; }else{ goto RtgfTK_100; }
		if(cx>ed_ndata){ return 1; }
		--bp;
	}

RtgfTK_100:
	if(cx>ed_ndata){ return 1; }else{ return 0; }
}
#endif


#if !defined(O_TALKONLY)
/*========== RtgfNydShiraberu() ==========
	Function: Check whether or not the reading of the registered word is appropriate
  ========================================*/
BOOL RtgfNydShiraberu() {
	if(n_inert>MAX_EDIC){ return 0; }else{ return 1; }
}
#endif

/***************************** END OF ILE_RTGC.C *****************************/

