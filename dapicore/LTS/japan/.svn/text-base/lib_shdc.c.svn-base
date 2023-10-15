/********************************************
	ILE_SHDC.C	updated at 31th July 1990
	出力データ関連操作
 ********************************************/

#define		EXT		extern

//#if defined(OS9)  //moved to port.h for each platform mlt 02/08/06
//#include	"stdio.h" //moved to port.h for each platform mlt 02/08/06
//#else //moved to port.h for each platform mlt 02/08/06
//#include	<stdio.h> //moved to port.h for each platform mlt 02/08/06
//#endif //moved to port.h for each platform mlt 02/08/06
#include "port.h" //moved to port.h for each platform mlt 02/08/06

#include	"onsei.h"
#include	"ile_envh.h"
#include	"ile_errh.h"
#include	"ile_dbgh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"


/*========== OMEGA_INIT() ===============
	Function: Initialize the output data are.
  ======================ShdfShokikasuru==*/
void OMEGA_INIT() 
{
	register integer_16 i;

	/* Output phonetic symbol watching position, current word conversion result length, and watching sentence position */
	cpron_ptr= cpron_len= sent_ptr= 0;

	/* Sentence position information */
	for(i=0;i<MAX_SENT;i++){
		sent_in_ptr[i]=sent_out_ptr[i]=sent_in_ptr_sav[i]=sent_out_ptr_sav[i]=0;
	}

	/* Conversion result */
	/* Storage area of the previous conversion result. */
	for(i=0;i<MAX_OMEGA;i++){ omega[i]=omega_sav[i]='\0'; }
}

/*========== OMEGA1000(al,di) ===========================================
	Function: Store the output result character that is passed by al in the output data area indicated by di.
	Value: Return the pointer specified below.
  ======================================================ShdfKekMjShimau==*/
integer_16 OMEGA1000(al,di) BYTE al; register integer_16 di; {
	if(di>=MAX_OMEGA){ jp_ERROR(Err_NaibuOVF); }	/* overflow */
	omega[di]=al;
	return (di+1);
}

/*========== OMEGA5000() =======================================================
	Function: Obtain the conversion result in the output data middle area according to the instruction of the current watching word notation.
			When it is a number, it is not called.
  =============================================================ShdfKekMotomeru==*/
void OMEGA5000(){
	register integer_16 di,bx;

	di=cpron_ptr;						/* Obtain the output result position.*/

	/* Obtain the notation according to the type of the current word.*/
	/* Punctuations and special symbols are categorized as simple word.*/
	switch(Stz_CE.stz_kind){
	case DICKIND_I:		di=IDIC5000(di); break;		/* Internal dictionary */
	case DICKIND_E:		di=EDIC5000(di); break;		/* External dictionary */
	case DICKIND_T:									/* Tan-kanji word */
						if(Stz_CE.stz_dman!=0xFF){
							di=TDIC5000(di);		/* Word in the dictionary */
						}else{
							di=TDIC5009(di);		/* Word not in the dictionary */
						}
						break;
	case DICKIND_K:		di=KKANA5000(di); break;	/* Katakana word */
	}

	cpron_ptr=di;			/* Store the position of the middle area of output data.*/
	bx=sent_ptr;		 	/* Obtain the sentence number of the middle area of output data.*/
							/* When it is a word that can be the beginning without prefix, */
	if(StzfAttrAri(Stz_CE,stz_ctl,BITCTL_FIRST)
	&& StzfAttrNashi(Stz_CE,stz_stz,BITSTZ_PREF)){
		/* if it exceeds the maximum number of sentences that can be output, */
		if(bx>=MAX_SENT){ jp_ERROR(Err_NaibuOVF); }
		/* Proceed the sentence if it is not a prefix.*/
		if(ceptr!=0){ bx++; sent_ptr=bx; }
	}
	/* Specify the input data position in the output data and the output data position.*/
	sent_out_ptr[bx]=di;
	sent_in_ptr [bx]=ceptr+celen;
}


/*========== OMEGA6000() ======================
	Function: Return the contents of the middle area of the output data by a word.
  ==============================ShdfKekModosu==*/
void OMEGA6000() {
	register integer_16 bx;

	bx=sent_ptr; 				/* Obtain the sentence position of the middle area of output data.*/
	sent_out_ptr[bx]=cpron_ptr;	/* Specify the output data position in the output data.*/
	sent_in_ptr [bx]=ceptr;		/* Specify the output data character position in the output data.*/
								/* When it is a word that can be the beginning without prefix, */
	if(StzfAttrAri(Stz_CE,stz_ctl,BITCTL_FIRST)
	&& StzfAttrNashi(Stz_CE,stz_stz,BITSTZ_PREF)){
		if(ceptr!=0){		/* Return the sentence if it is not a prefix.*/
			sent_in_ptr[bx]=sent_out_ptr[bx]=0;
			bx--;
			sent_ptr=bx;
		}
	}
}

/*========== OMEGA9000() =========================================
	Function: Move the information in the middle area of the output data to the output data area.
  =================================================ShdfKekWatasu==*/
void OMEGA9000() 
{
	register BYTE *si;
	integer_16 col;
	register integer_16 cx;
	LPBYTE shd;
	LPWORD shd16;

	onsei_addr->onsei_sentno=sent_ptr+1;
	shd16=onsei_addr->onsei_sent;
	for(cx=0;cx<=sent_ptr;++cx)
	{
		*shd16++=sent_in_ptr[cx];
		*shd16++=sent_out_ptr[cx];
	}

	shd16=onsei_addr->onsei_sent;
	shd=onsei_addr->onsei_speak;
	si=speak;
	col=0;
	++shd16;
	for(;*si;)
	{
		if(*si==0xFF)
		{
			*shd16=col;
			++si;
			shd16+=2;
		}
		else
		{
			*shd++ = *si++;
			col++;
		}
	}
	*shd++=0x00;
}

/*========== OMEGA_SAVE() ======================================
	Function: Store the output data temporarily to compare it with the next conversion result.
  ===============================================ShdfKekOboeru==*/
void OMEGA_SAVE() {
	memcpy(sent_in_ptr_sav, sent_in_ptr, MAX_SENT*2);
	memcpy(sent_out_ptr_sav,sent_out_ptr,MAX_SENT*2);
	memcpy(omega_sav,       omega,       MAX_OMEGA);
	memcpy(accent_sav,      accent0,     MAX_OMEGA);
}

/*========== OMEGA_CHECK() ===========================================
	Function: Check whether or not the current output data matches the previous conversion result.
		The items to be compared are pauses in sentence, phonetic symbols, and accents.
	Value: 0 ＝Different, 1＝Same
  ======================================================ShdfKekOnaji==*/
BOOL OMEGA_CHECK() {
	if(memcmp(sent_in_ptr, sent_in_ptr_sav, MAX_SENT*2)){ return 0; }
	if(memcmp(sent_out_ptr,sent_out_ptr_sav,MAX_SENT*2)){ return 0; }
	if(memcmp(omega,       omega_sav,       MAX_OMEGA )){ return 0; }
	if(memcmp(accent0,     accent_sav,      MAX_OMEGA )){ return 0; }
	return 1;
}

/***************************** END OF ILE_SHDC.C *****************************/

