/********************************************
	ILE_V5CC.C	updated at 18th June 1989
	5-step verb conjunctive form
 ********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_fddh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_v5ch.h"
#include	"ile_func.h"

/*========== V5DANYOU_PUSH() ====================================
	Function: Stack the information of the conjunctive ending of the omitted 5-step verb.
  ===============================================================*/
void V5DANYOU_PUSH() {
#if defined(O_DEBUG)
	DEBUG_STR("『連用形語尾追加ぢゃ。』\n");
#endif
	/* Add the sound of conjunctive ending to the output area.*/
	cpron_ptr=V5DAN5000(cpron_ptr); cpron_len=1;

	/* The current element is 5-step verb conjunctive ending.*/
	Stz_CE.stz_kind=DICKIND_5Y;
	Stz_CE.stz_nbno=1;
	Stz_CE.stz_bno[0]=Fdd_Header.Fdd_Bno5danYou;

	/* The automatically generated conjunctive ending should not be the last.*/
	/* Especially when the error code is 3 or 4, it becomes a problem.
	   If max_ceptr is placed just after the automatically generated conjunctive ending, it cannot be reconverted.*/
	/*Stz_CE.stz_ctl=BITCTL_LAST | BITCTL_PEDIC | BITCTL_FEDIC;*/
	Stz_CE.stz_ctl=BITCTL_PEDIC | BITCTL_FEDIC;

	/* Reset the output data position of the sentence information. */
	/* Because this is an ending, it should not be the top of the sentence.*/
	sent_out_ptr[sent_ptr]=cpron_ptr;
	STACK_PUSH();
}


/*========== V5DAN5000(ptr) ============================
	Function: Add the sound of "き" that is omitted form "動始める."
  ======================================================*/
integer_16 V5DAN5000(di) integer_16 di; {
	BYTE al,ah;
	register WORD si;
	register integer_16 cx;

	si=Fdd_Header.Fdd_V5youOfs;
	cx=FddHDR[si++];
	for(;cx--;){
		al=FddHDR[si++];
		ah=al/16; al&=0x0F;
		if(ah<10){ stc_accent_raw[stc_ptr][ah]=al; }
	}

	di=OMEGA1000(FddHDR[si+flg_v5you-Fdd_Header.Fdd_Bno5danLL],di);
	return di;
}

/***************************** END OF ILE_V5CC.C *****************************/

