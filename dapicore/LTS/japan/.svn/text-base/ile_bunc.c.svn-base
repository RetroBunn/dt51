/***********************************************
	ILE_BUNC.C	updated at 25th October 1990
	Operations related to segment processing
	Movement of the watching sentence to the right or left
	Conversion of the watching sentence to the shorter or longer segment
 ***********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_bunh.h"
#include	"ile_envh.h"
#include	"ile_errh.h"
#include	"ile_kkhh.h"
#include	"ile_mruh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_func.h"

integer_16 ws_no = 0;
integer_16 wsptr = 0;
integer_16 fsptr = 0;
integer_16 fsptr_sav = 0;

/*========== PRON_FIRST() =========================
	Function: Initial sentence voice conversion (For details, see the external specifications.)
  ===========================ShhfShokaiHenkansuru==*/
void PRON_FIRST() {
	integer_16 status;
	conv_mode=CONV_FIRST;

#if !defined(O_TALKONLY)
	/* When the learning function is available, learn the segment up to the user-watching sentence.*/
	/*if(KkhfMruKanou)then MRU_CSENT(); fi*/
#endif

	/* Initialize.*/
	kkhstat=shoki;
	MRU_OR_NOT=0;
	PRON_INIT(); 
	INERT_INIT();

	clear_null();

	ceptr=0;					/* Set ceptr at the top of the sentence.*/
	status=CS1000(0);			/* From the current element position (ceptr), starts sentence voice conversion.*/
	if(status==1)				/* When it was able to be converted,*/
	{			
		WS_BECOMES_TOP();		/* set the watching sentence number to the top.*/
		kkhstat=bunsetsu;		/* Make the segment settings.*/
	}
	else
	{							/* When it was not able to be converted,*/
		/* if it is in Tan-kanji dictionary available mode, use the tan-kanji dictionary to convert it.*/
		/* If it is in Tan-kanji dictionary unavailable mode, reconvert them up to the point they were able to be converted.*/
		if(onsei_addr->onsei_usetankan==0)
		{
			if(max_ceptr==0)
			{
				/* If no character can be converted, an error is generated.*/
				ERROR5000();
				jp_ERROR(Err_HenkanFunou);
			}
			else
			{
				/* If at least one character can be converted, reconvert them up to the point they were able to be converted.*/
				/* The length of the segment is the maximum number of characters that were able to be converted.*/
				n_inert=max_ceptr;
			}
		}
#if defined(O_DEBUG)
		DEBUG_STR("『やり直しぢゃ。』\n");
#endif
		PRON_INIT2();			/* Initialize the output area, stack, and segment position information.*/
		ceptr=0;				/* Set ceptr at the top of the sentence.*/
		conv_mode=CONV_RETRY;
		/* From the current element position (ceptr), starts sentence voice conversion. */
		if(CS1000(0)==0){
			/* This is a conversion of single "っ(double consonant)" or "ん(syllabic nasal)."*/
			jp_ERROR(Err_HenkanFunou);
		}
		WS_BECOMES_TOP();
		kkhstat=bunsetsu;
		if(status==0){
			jp_ERROR(Err_HenkanTochuu);	/* status==0 */
		}else{
			jp_ERROR(Err_RestrictCNT);		/* status==2 */
		}
	}
}


/*========== PRON_NEXT() ============================
	Function: Next target of sentence voice conversion (For details, see the external specifications.)
  ===================BtgfBunsetsuTsugikouhoMotomeru==*/
void PRON_NEXT() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	conv_mode=CONV_NEXT;
	MRU_OR_NOT=1;
	if(kkhstat==bunsetsu){ goto PRON_NEXT_100; }	/* Segment state */
	if(kkhstat==funou   ){ goto PRON_NEXT_200; }	/* Unconvertible state */
	jp_ERROR(Err_Abnormal); 

PRON_NEXT_100:					/* When it is in segment state,  */
	MRU_REMEMBER();				/* record the word that was used for the previous conversion result. */
	OMEGA_SAVE();				/* Store the previous conversion result for comparison. */
	/* Store the position of the following sentence of the watching sentence.*/
	/*fsptr_sav=fsptr;*/
	PRON_NEXT_120:
		STACK_POP_FS();			/* Return the stack until it reaches the current watching sentence. */
		if(CS1000(1)==0){ goto PRON_NEXT_180; }	/* If it is unconvertible, */
	if(OMEGA_CHECK()){ goto PRON_NEXT_120; }	/* If it is same as last time, redo it. */
	kkhstat=bunsetsu;			/* Set it in segment state. */
	goto PRON_NEXT_990;

PRON_NEXT_180:
	CS1000(0); 					/* Perform the segment sound conversion from the current status. */
	kkhstat=funou;				/* Set it in unconvertible state. */
	jp_ERROR(Err_NextNone);	 	/* Notify of the unconvertible state. */

PRON_NEXT_200:					/* If it is in unconvertible state, */
	STACK_POP_WS();				/* Return the stack until it reaches the next to the current watching sentence. */
	kkhstat=bunsetsu;			/* Record the segment setting state. */
	CS1000(0);					/* Reconvert the succeeding element. */

PRON_NEXT_990:
	return;
#endif
}


/*========== PRON_TERM() ============================
	Function: Determination of sentence voice conversion (For details, see the external specifications.)
  ============================KakfHenkanKakuteisuru==*/
void PRON_TERM() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	if(KkhfMruKanou){
		MRU_ALL();
		kkhstat=shoki;
	}else{
		jp_ERROR(Err_Abnormal);
	}
#endif
}


/*========== PRON_ACON() =================
	Function: Specifying the accent combination for the segment sound conversion
  ========================================*/
void PRON_ACON() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	integer_16 p;
	if(ws_no==sent_ptr+1){ return; }	/* Ignore it when it is the last segment.*/

	conv_mode=CONV_NEXT;
	/* Process it when it is in unconvertible state or in segment state.*/
	if(kkhstat==bunsetsu||kkhstat==funou){ goto PRON_ACON_100; }
	jp_ERROR(Err_Abnormal);

PRON_ACON_100:
	for(p=0;p<stc_ptr;++p){
		if(stc_in_ptr[p]==sent_in_ptr[ws_no-1]){ goto PRON_ACON_200; }
	}
PRON_ACON_200:					/* When it is in segment state,  */
	stc_mru[p]|=BITMRU_ACON;
	stc_mru[p]&=~BITMRU_ACOFF;
	ACCXXXX();
	kkhstat=bunsetsu;			/* Set it in segment state. */
#endif
}


/*========== PRON_ACOFF() ================
	Function: Abandoning the accent combination for the segment sound conversion
  ========================================*/
void PRON_ACOFF() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	integer_16 p;
	if(ws_no==sent_ptr+1){ return; }	/* Ignore it when it is the last segment.*/

	conv_mode=CONV_NEXT;
	/* Process it when it is in unconvertible state or in segment state.*/
	if(kkhstat==bunsetsu||kkhstat==funou){ goto PRON_ACOFF_100; }
	jp_ERROR(Err_Abnormal);

PRON_ACOFF_100:
	for(p=0;p<stc_ptr;++p){
		if(stc_in_ptr[p]==sent_in_ptr[ws_no-1]){ goto PRON_ACOFF_200; }
	}
PRON_ACOFF_200:					/* When it is in segment state,  */
	stc_mru[p]|=BITMRU_ACOFF;
	stc_mru[p]&=~BITMRU_ACON;
	ACCXXXX();
	kkhstat=bunsetsu;			/* Set it in segment state. */
#endif
}


/*========== PRON_PAUSE_INS() =========
	Function: Inserting a segment sound conversion pose forcibly
  =====================================*/
void PRON_PAUSE_INS() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	integer_16 p;
	if(ws_no==sent_ptr+1){ return; }	/* Ignore it when it is the last segment.*/

	conv_mode=CONV_NEXT;
	/* Process it when it is in unconvertible state or in segment state.*/
	if(kkhstat==bunsetsu||kkhstat==funou){ goto PRON_PINS_100; }
	jp_ERROR(Err_Abnormal);

PRON_PINS_100:
	for(p=0;p<stc_ptr;++p){
		if(stc_in_ptr[p]==sent_in_ptr[ws_no-1]){ goto PRON_PINS_200; }
	}
PRON_PINS_200:					/* When it is in segment state, */
	stc_mru[p]|=BITMRU_PINS;
	stc_mru[p]&=~BITMRU_PDEL;
	ACCXXXX();
	kkhstat=bunsetsu;			/* Set it in segment state.*/
#endif
}


/*========== PRON_PAUSE_DEL() =========
	Function: Deleting a sentence sound conversion pose forcibly
  =====================================*/
void PRON_PAUSE_DEL() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	integer_16 p;
	if(ws_no==sent_ptr+1){ return; }	/* Ignore it when it is the last segment.*/

	conv_mode=CONV_NEXT;
	/* Process it when it is in unconvertible state or in segment state.*/
	if(kkhstat==bunsetsu||kkhstat==funou){ goto PRON_PDEL_100; }
	jp_ERROR(Err_Abnormal);

PRON_PDEL_100:
	for(p=0;p<stc_ptr;++p){
		if(stc_in_ptr[p]==sent_in_ptr[ws_no-1]){ goto PRON_PDEL_200; }
	}
PRON_PDEL_200:					/* When it is in segment state, */
	stc_mru[p]|=BITMRU_PDEL;
	stc_mru[p]&=~BITMRU_PINS;
	ACCXXXX();
	kkhstat=bunsetsu;			/* Set it in segment state.*/
#endif
}


/*========== PRON_SENT_NO() ==================
	Function: Extracting the segment number of the currently watching sentence
  ==============CbtfChuumokubunsetsuToridasu==*/
void PRON_SENT_NO() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	/* If it is in segment state or unconvertible state, */
	if(kkhstat==bunsetsu || kkhstat==funou){
		/* Specify the watching sentence number.*/
		onsei_addr -> onsei_wsno = ws_no;
	}else{
		jp_ERROR(Err_Abnormal);
	}
#endif
}


/*========== PRON_RIGHT() =======================
	Function: Moving the watching sentence to the right (For details, see the external specifications.)
		If it cannot be moved, an error is generated.
  =====================BmgfBunsetsuMigiIdousuru==*/
void PRON_RIGHT() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	conv_mode=CONV_RIGHT;
	if(kkhstat==bunsetsu || kkhstat==funou){
		/* If it is not in the initial conversion state,*/
		OMEGA9000();				/* the last conversion result is passed without any change.*/
		/* If it is not the watching sentence number, */
		if(ws_no!=sent_ptr+1){
			WS_MOVE_RIGHT();		/* Proceed the watching sentence.*/
			kkhstat=bunsetsu;		/* Make the segment settings.*/
			return;
		}else{					/* If it is the last segment, */
			jp_ERROR(Err_IdouFunou);	/* Notify of the unmovable state.*/
		}
	}else{
		jp_ERROR(Err_Abnormal);
	}
#endif
}


/*========== PRON_LEFT() ========================
	Function: Moving the watching sentence to the left (For details, see the external specifications.)
		If it cannot be moved, an error is generated.
  ===================BhifBunsetsuHidariIdousuru==*/
void PRON_LEFT() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	conv_mode=CONV_LEFT;
	if(kkhstat==bunsetsu || kkhstat==funou){
		/* If it is not in the initial conversion state, */
		OMEGA9000();				/* the last conversion result is passed without any change. */
		/* If the watching sentence is not the top sentence,  */
		if(ws_no!=1){
			WS_MOVE_LEFT();			/* Return the watching sentence. */
			kkhstat=bunsetsu;		/* Make the segment settings. */
			return;
		}else{					/* If it is the top segment,  */
			jp_ERROR(Err_IdouFunou);	/* Notify of the unmovable state. */
		}
	}else{
		jp_ERROR(Err_Abnormal);
	}
#endif
}


/*========== PRON_SHORT() ===========================
	Function: conversion of the focused segment to the longer segment (For details, see the external specifications.)
  ==========================BtnfTanhoukouHenkansuru==*/
void PRON_SHORT() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	conv_mode=CONV_SHORT;
	/* If it is in segment state or unconvertible state,  */
	if(kkhstat==bunsetsu || kkhstat==funou){
		MRU_OR_NOT=1;
		/* Store the position of the following sentence of the watching sentence.*/
		fsptr_sav=fsptr;
		MRU_REMEMBER();				/* Record the word that was used for the previous conversion result. */
		do{						/* Repeat this process until a break of the short segment is found.*/
			/* If the user-watching sentence cannot be shortened, the state is restored, and an error is generated. */
			if(WS_CHK_SHORT()==0){ PRON_RECOVER(); }
			/* Return the stack until it reaches the watching sentence (ceptr==wsptr).*/
			STACK_POP_WS();
			/* It starts conversion from the top of the watching sentence.*/
		}while(CS1000(0)==0);
		return;
	}else{						/* If it is in other state, */
		jp_ERROR(Err_Abnormal);	/* notify of the call contradiction. */
	}
#endif
}


/*========== PRON_LONG() ============================
	Function: conversion of the watching sentence to the longer segment (For details, see the external specifications.)
  =========================BchfChouhoukouHenkansuru==*/
void PRON_LONG() {
#if defined(O_TALKONLY)
	jp_ERROR(Err_Abnormal);
#else
	conv_mode=CONV_LONG;
	/* If it is in segment state or unconvertible state,  */
	if(kkhstat==bunsetsu || kkhstat==funou){
		MRU_OR_NOT=1;
		/* save the position of the following sentence of the watching sentence.*/
		fsptr_sav=fsptr;
		/* If the watching sentence is not the last segment,  */
		if(ws_no!=sent_ptr+1){
			MRU_REMEMBER(); 		 	/* Record the word that was used for the previous conversion result.*/
			do{						/* Repeat this process until a break of the long segment is found.*/
				/* If the user-focused segment cannot be extended, it is restored, and an error is generated. */
				if(WS_CHK_LONG()==0){ PRON_RECOVER(); }
				/* Return the stack until it reaches the focused segment (ceptr==wsptr).*/
				STACK_POP_WS();
				/* It starts conversion from the top of the watching sentence.*/
			}while(CS1000(0)==0);
			return;
		}
		PRON_RECOVER();				/* If it is the last segment, an error is generated. */
	}
	/* In other state, notify of the call contradiction. */
	jp_ERROR(Err_Abnormal);
#endif
}


#if !defined(O_TALKONLY)
/*========== PRON_RECOVER() ==============================
	Function: Processing for when conversion to the longer or shorter segment is not available
  =============================================BchfRecvr==*/
void PRON_RECOVER() {
	kkhstat=bunsetsu;				/* Make the segment setting. */
	fsptr=fsptr_sav;				/* Return the position of the following segment of the watching sentence. */
	STACK_POP_WS();					/* Return the stack to the watching sentence. */
	CS1000(0);						/* Re-convert the segment from the top of the watching sentence. */
	jp_ERROR(Err_IdouFunou);			/* Set the error code and return.*/
}
#endif


/*========== WS_BECOMES_TOP() ===================
	Function: Set the position of the user-watching sentence to the top.
		Make watching sentence to Top position.
  ============================BunfChbHajimesuru==*/
void WS_BECOMES_TOP() {
	onsei_addr->onsei_wsno = ws_no = 1;
							/* Set 1 for the watching sentence no. */
	wsptr=0;				/* Specify the position of the watching sentence. */
	fsptr=sent_in_ptr[0];	/* Specify the position of the following sentence of the watching sentence. */
}


#if !defined(O_TALKONLY)
/*========== WS_MOVE_LEFT() ==================
	Function: Return one segment of the user-watching sentence management information.
  =============================BunfChbModosu==*/
void WS_MOVE_LEFT() {
	/* Reduce the user-watching sentence number. */
	--ws_no;
	onsei_addr -> onsei_wsno = ws_no;
	/* Set the start position of the preceding user-watching sentence to the end position of the current segment. */
	fsptr=wsptr;
	/* Set the start position of the user-watching sentence.*/
	/* Set the end position of the preceding user-watching sentence to the start position of the current segment.
	   If it is the first segment, the start position of the segment is to be the beginning of the sentence. */
	wsptr=(ws_no==1 ? 0 : sent_in_ptr[ws_no-2]);
}
#endif


#if !defined(O_TALKONLY)
/*========== WS_MOVE_RIGHT() ===================
	Function: Proceed one sentence of the user-watching sentence management information.
  =============================BunfChbSusumeru==*/
void WS_MOVE_RIGHT() {
	/* Add up the user-watching sentence number. */
	++ws_no;
	onsei_addr -> onsei_wsno = ws_no;
	/* Set the end position of the preceding user-watching sentence to the start position of the current segment. */
	wsptr=fsptr;
	/* Set the end position of the user-watching sentence. */
	fsptr=sent_in_ptr[ws_no-1];
}
#endif


#if !defined(O_TALKONLY)
/*========== WS_CHK_SHORT() ==========================================================
	Sentence structure: if (WS_CHK_SHORT()) for when it is shortened, else for when it is not shortened; 
	Function: Determine whether or not the current user-watching sentence can be shortened, and it can be shortened, specify the length.
		In addition, specify the new segment end position.
		The segment end position is the start position of the following segment (with the origin at 0).
	Output: If it can be shortened, the length of the segment after it is shortened  (not zero) is set.
		If it cannot be shortened, 0 is set.
  ===============================================================BunfChbYomChijimaru==*/
integer_16 WS_CHK_SHORT() {
	register integer_16 new_len,ptr; integer_16 i;

	/* (Past) Numbers cannot be shortened.(Current) Only when the decimal number functions as a delimiter, the number can be shortened.*/
	for(i=0;i<stc_ptr;++i){
		if(stc_in_ptr[i]==fsptr){ goto WS_CHK_SHORT100; }
	}
	i=stc_ptr;
WS_CHK_SHORT100:
	/*if(stc_kind[i-1]==DICKIND_D){ return 0; }*/

	ptr=wsptr;
	/* The watching sentence is shortened. */
	new_len=(integer_16)INERT200B(ptr, (integer_16)(fsptr-ptr));
	/* The end position of the new segment is set. */
	fsptr=ptr+new_len;
	return new_len;		/* The new segment length (if it is not shortened, 0 is set.)*/
}
#endif


#if !defined(O_TALKONLY)
/*========== WS_CHK_LONG() ===========================================================
	Sentence structure: if (WS_CHK_LONG()) for when it is extended, else for when it is not extended;
	Function: Determine whether or not the current user-watching sentence can be extended, and it can be extended, specify the length.
	Output: If it can be extended, the length of the segment after it is extended  (not zero) is set.
		If it cannot be extended, 0 is set.
  ==================================================================BunfChbYomNobiru==*/
integer_16 WS_CHK_LONG() {
	register integer_16 new_len,ptr;
	ptr=wsptr;
	/* The watching sentence is extended. */
	new_len = INERT300B(ptr, (integer_16)(fsptr-ptr));
	/* The end position of the new segment is set. */
	fsptr=ptr+new_len;
	return new_len;		/* The new segment length (if it is not extended, 0 is set.)*/
}
#endif


/*========== SENT_INIT() ================
	Function: Initialize the watching sentence management information.
  ======================BunfShokikasuru==*/
void SENT_INIT() {
	register integer_16 AX=0;
	/* watching sentence no. */
	/* watching sentence pointer */
	/* following sentence pointer */
	ws_no=wsptr=fsptr=fsptr_sav=AX;
}


#if !defined(O_TALKONLY)
/*========== WS_CE_CHK() =========================================================
	Sentence structure：if(WS_CE_CHK()){ no error; }else{ error; }
	Function: Check whether or not the start position and length of the current element contradict with the segment fixing instruction position.
	Output: 1 : Normal, 0 : Error
  ================================================================BunfYomKoteiAu==*/
BOOL WS_CE_CHK() {
	register integer_16 cetail,ptr;
	cetail=(ptr=ceptr)+celen-1;
	/* When the current element crosses the start of the instruction position, there is a contradiction. */
	/* When the current element crosses the end of the instruction position, there is a contradiction. */
	if((ptr<wsptr) && (cetail>=wsptr)){ return 0; }
	if((ptr<fsptr) && (cetail>=fsptr)){ return 0; }
	return 1;
}
#endif

/***************************** END OF ILE_BUNC.C *****************************/

