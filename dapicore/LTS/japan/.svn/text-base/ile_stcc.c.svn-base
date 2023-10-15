/************************************************
	ILE_STCC.C	updated at 14th November 1989
	Matters related to stack
 ************************************************/

#define		EXT		extern

#if defined(DEBUG_STC)
#include	<stdio.h>
#endif

#include	"onsei.h"
#include	"ile_bunh.h"
#include	"ile_dbgh.h"
#include	"ile_edic.h"
#include	"ile_errh.h"
#include	"ile_fddh.h"
#include	"ile_idic.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_tdic.h"
#include	"ile_func.h"

BYTE		stc_accent_raw[MAX_STACK][10] = {{0}};	/* Accent raw data */

/*========== STACK_INIT() ===============
	Function: Initialize the dictionary lookup stack.
  ======================StcfShokikasuru==*/
void STACK_INIT() {
	register integer_16 cx;
	stc_ptr=0;
	/* initialize next accent data region */
	for(cx=10;cx--;){ stc_accent_raw[stc_ptr][cx]=0x00; }
	/*stc_accent_raw[stc_ptr][4]=0xFF;	Second accent */
}


/*========== STACK_PUSH() ===============
	Function: Stack the information on the dictionary lookup stack.
  =======================StcfStackTsumu==*/
void STACK_PUSH() {
	register integer_16 cx,sp;

#if defined(DEBUG_STC)
	if(debug[1]||debug[2]){ DEBUG_PN("<STC_PUSH>"); }
#endif

	if(stc_ptr==MAX_STACK){ jp_ERROR(Err_NaibuOVF); }

	RtkfChudanShiraberu();				/* If there is a processing interrupt request, stop the conversion.*/
	sp=stc_ptr;							/* Obtain the available stack start position. */
	stc_out_len[sp]=(BYTE)cpron_len;			/* Number of characters in output data */
	stc_out_ptr[sp]=(sp==0 ? 0 : stc_out_ptr[sp-1]+stc_out_len[sp-1]);
	stc_in_ptr[sp]=ceptr;				/* Input data position */
	stc_in_len[sp]=(BYTE)celen;				/* Number of characters in input data */
	stc_f2[sp] =Stz_CE.stz_f2;		/* Flag 2 (type flag of Tan-kanji dictionary)*/
	stc_ctl[sp]=Stz_CE.stz_ctl;		/* Control information */
	stc_mru[sp]=Stz_CE.stz_mru;		/* Learning information */
	stc_stz[sp]=Stz_CE.stz_stz;		/* Connection status */
	stc_dman[sp]=Stz_CE.stz_dman;	/* Number information */
	stc_dexp[sp]=Stz_CE.stz_dexp;	/* Number information */

	cx=stc_nbno[sp]=Stz_CE.stz_nbno;	/* Number of back-end numbers */
	if(cx){	/* When there is a back-end number, store the back-end number (origin at 1 for cx). */
		do{ stc_bno[sp][cx-1]=Stz_CE.stz_bno[cx-1]; }while(--cx);
	}
	cx=stc_ngrcd[sp]=Stz_CE.stz_ngrcd;	/* Number of grammar codes */
	if(cx){	/* When there is a grammar code, store it (origin at 1 for cx). */
		do{ stc_grcd[sp][cx-1]=Stz_CE.stz_grcd[cx-1]; }while(--cx);
	}

	switch(stc_kind[sp]=Stz_CE.stz_kind){
	case DICKIND_5Y:					/* 5-step verb automatic generation conjunctive ending */
		stc_in_len[sp]=0;
	case DICKIND_E:						/* External self-sufficient word dictionary word */
		stc_ed_pag[sp]=edic_page_no;
		stc_ed_ofs[sp]=edic_ofs;
		break;
	case DICKIND_T:						/* Tan-kanji dictionary word */
		stc_ed_pag[sp]=edic_page_no;
		stc_ed_ofs[sp]=tdic_ofs;
		stc_dexp[sp]=(BYTE)tdic_len;
		break;
	case DICKIND_I:						/* Internal ancillary word dictionary */
		stc_ed_pag[sp]=0;
		stc_ed_ofs[sp]=(WORD)(idic_addr-FddHDR);
		break;
	/* case DICKIND_D: --- stc_ed_ofs is digit kind. (int. or frac.) */
	}

	stc_ptr++;
	/* initialize next accent data region */
	for(cx=10;cx--;){ stc_accent_raw[stc_ptr][cx]=0x00; }
	/*stc_accent_raw[stc_ptr][4]=0xFF;	Second accent */

#if defined(DEBUG_STC)
	if(debug[1]){ DEBUG_STC_ALL(); }
	if(debug[2]){ DEBUG_STC_CE(stc_ptr); }
#endif
}


/*========== STACK_POP() ====================
	Function: Unstack the information from the dictionary lookup stack.
  ===========================StcfStackOrosu==*/
void STACK_POP() {
	register integer_16 sp,cx;

#if defined(DEBUG_STC)
	if(debug[3]){ DEBUG_PN("<STACK_POP>"); DEBUG_STC_CE(stc_ptr); }
#endif

	RtkfChudanShiraberu();			/* If there is a processing interrupt request, stop the conversion.*/

	if(stc_kind[stc_ptr-1]==DICKIND_5Y){				/* 5-step verb conjunctive ending */
		/* Return the information related to the connection information by two words.*/
		--stc_ptr;
		sp=stc_ptr-1;
		Stz_CE.stz_kind=stc_kind[sp];

		if(cx=Stz_CE.stz_nbno=stc_nbno[sp]){
			do{ Stz_CE.stz_bno[cx-1]=stc_bno[sp][cx-1]; }while(--cx);
		}
		if(cx=Stz_CE.stz_ngrcd=stc_ngrcd[sp]){
			do{ Stz_CE.stz_grcd[cx-1]=stc_grcd[sp][cx-1]; }while(--cx);
		}

		Stz_CE.stz_ctl=stc_ctl[sp];				/* Control information */
		Stz_CE.stz_f2=stc_f2[sp];				/* Flag 2 */
		Stz_CE.stz_stz=stc_stz[sp];				/* Connection status */
		Stz_CE.stz_mru=stc_mru[sp];				/* Learning information */
		Stz_CE.stz_dman=stc_dman[sp];			/* Number information */
		Stz_CE.stz_dexp=stc_dexp[sp];			/* Number information */
	}else{
		/* Return the information related to the connection information by one word.*/
		StzfElmBackward();
	}

STACK_POP_100:
	stc_ptr--;
	sp=stc_ptr;
	ceptr=stc_in_ptr[sp];			/* current element pointer */
	celen=stc_in_len[sp];			/* current element length */
	cpron_ptr=stc_out_ptr[sp];		/* current pronunciation pointer */
									/* Return the information related to the current watching word. */
	switch(stc_kind[sp]){
	case DICKIND_I:					/* Internal ancillary word dictionary word */
		idic_addr=FddHDR+stc_ed_ofs[sp]; break;
	case DICKIND_D:					/* Internal combined number */
		if(sp==0){ break; }	/* no more stack exist */
		/*
		 * When the preceding word is a number, pop until the preceding word becomes a non-number word.
		 *	When "二" of "三十二" is popped, "三十" is always popped.
		 *	When "一" of "1.|一" is popped, do not pop "1."
		 *	In other words, pop it until it becomes the number that can be at the top.
		 */
		if(stc_ctl[sp] & BITCTL_FIRST){ break; }
		if(stc_kind[sp-1]==DICKIND_D){
			Stz_CE.stz_ctl=stc_ctl[sp-1];
			goto STACK_POP_100;
		}
		break;
	case DICKIND_E:					/* External self-sufficient word dictionary word */
		edic_page_no=stc_ed_pag[sp];	/* Page number */
		edic_ofs=stc_ed_ofs[sp];		/* Offset in the page */
		break;
	case DICKIND_T:					/* Tan-kanji dictionary word */
		edic_page_no=stc_ed_pag[sp];	/* Page number */
		tdic_ofs=stc_ed_ofs[sp];		/* Offset in the page */
		tdic_len=stc_dexp[sp];			/* Total record size */
		break;
	}

	OMEGA6000();						/* Return the output result. */
	if(stc_ptr){						/* Return the information related to the preceding word if any preceding word remains.*/
		sp=stc_ptr-1;
		StzfElmKind(&Stz_PE,stc_kind[sp]);
		if(cx=Stz_PE.stz_nbno=stc_nbno[sp]){
			do{ Stz_PE.stz_bno[cx-1]=stc_bno[sp][cx-1]; }while(--cx);
		}
		if(cx=Stz_PE.stz_ngrcd=stc_ngrcd[sp]){
			do{ Stz_PE.stz_grcd[cx-1]=stc_grcd[sp][cx-1]; }while(--cx);
		}
		Stz_PE.stz_f2=stc_f2[sp];			/* Flag 2 */
		Stz_PE.stz_ctl=stc_ctl[sp];			/* Control information */
		Stz_PE.stz_mru=stc_mru[sp];			/* Learning information */
		Stz_PE.stz_stz=stc_stz[sp];			/* Connection status */
		Stz_PE.stz_dman=stc_dman[sp];		/* Number information */
		Stz_PE.stz_dexp=stc_dexp[sp];		/* Number information */
	}

	/* initialize next accent data region */
	for(cx=10;cx--;){ stc_accent_raw[stc_ptr][cx]=0x00; }
	/*stc_accent_raw[stc_ptr][4]=0xFF;	Second accent */
}


/*========== STACK_POP_FS() =========================================
	Function: Unstack the information from the dictionary lookup stack up to just before the user-watching sentence.
		After the execution, ceptr(current element pointer) and
		becomes equal to fsptr(following sentence pointer).
  ================================================StcfBunOnajiOrosu==*/
void STACK_POP_FS() {
	while(ceptr>fsptr){ STACK_POP(); }
}


/*========== STACK_POP_WS() =====================================
	Function: Unstack the information from the dictionary lookup stack up to the user-watching sentence.
		After the execution, ceptr(current element pointer) and
		becomes equal to fsptr(following sentence pointer).
  ============================================StcfBunTemaeOrosu==*/
void STACK_POP_WS() {
	while(ceptr>wsptr){ STACK_POP(); }
}


#if defined(DEBUG_STC)
/* debug routine for STACK */
void DEBUG_STC_ALL() {
	register integer_16 p;
	for(p=1;p<=stc_ptr;p++){ DEBUG_STC_CE(p); }
}

void DEBUG_STC_CE(ptr) integer_16 ptr; {
	register integer_16 p,i; integer_16 n,sip,sil;
	p=ptr-1; sip=stc_in_ptr[p]; sil=stc_in_len[p];
	FNX_PRINTF(" (%d) iP=%d",ptr,sip+1); FNX_PRINTF(":%d",sil);
	/*FNX_PRINTF(",oP=%d",stc_out_ptr[p]+1); FNX_PRINTF(":%d",stc_out_len[p]);*/
	putchar(','); DEBUG_K1(&inert[sip*2],sil);
	switch(stc_kind[p]){
	case DICKIND_E:  FNX_PRINTF(",external"); break;
	case DICKIND_I:  FNX_PRINTF(",internal"); break;
	case DICKIND_D:  FNX_PRINTF(",number"); break;
	case DICKIND_5Y: FNX_PRINTF(",conjunctive"); break;
	case DICKIND_K:  FNX_PRINTF(",katakana"); break;
	case DICKIND_T:  FNX_PRINTF(",Tan-kanji"); break;
	}
	FNX_PRINTF(",F2="); DEBUG_H1(stc_f2[p]);
	FNX_PRINTF(",CTL="); DEBUG_H1(stc_ctl[p]);
	FNX_PRINTF(",MRU="); DEBUG_H1(stc_mru[p]);
	FNX_PRINTF(",STZ="); DEBUG_H1(stc_stz[p]);
	FNX_PRINTF(",BNO=");
	for(n=stc_nbno[p],i=0;n--;i++){
		FNX_PRINTF("%d",stc_bno[p][i]); if(n>0){ putchar(','); }
	}
	putchar('\n');
}			
#endif

/***************************** END OF ILE_STCC.C *****************************/

