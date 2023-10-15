/************************************************
	ILE_SSKC.C	updated at 20th February 1991
	Interconnection relationship
 ************************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_fddh.h"
#include	"ile_sskh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"


/*========== BNO_VECP() ==========================
	Function: Check whether or not the current element and the preceding element are connected.
  ================================================*/
BOOL BNO_VECP() {
	register integer_16 ibno,ipno;
	integer_16 nbno_pe,npno_ce,bno,pno;

	nbno_pe=Stz_PE.stz_nbno;		/* the number of bno of preceding element */
	npno_ce=Stz_CE.stz_ngrcd;		/* the number of vecp of current element */
	for(ibno=0;ibno<nbno_pe;++ibno){
		if(bno=Stz_PE.stz_bno[ibno]){
			for(ipno=0;ipno<npno_ce;++ipno){
				if(pno=Stz_CE.stz_pno[ipno]){
					if(bno_pno(bno,pno)){ goto L100; }
				}
			}
		}
	}

	/* if preceding noun is KANGO and current noun is proper noun,
	  preceding reference vector of current noun is changed. */
	if(pe_is_kango &&
	   chk_limits(Fdd_Header.Fdd_GrcdPropLL,Fdd_Header.Fdd_GrcdPropUL,
				  Stz_CE.stz_grcd,Stz_CE.stz_ngrcd)){
		for(ibno=0;ibno<nbno_pe;++ibno){
			if(bno=Stz_PE.stz_bno[ibno]){
				if(bno<=8){
					if(bno_prop(bno)){ return 1; }
				}
			}
		}
	}
	return 0;

L100:
	/* Changing the order of back-end numbers */
	if(ibno!=0){
		Stz_PE.stz_bno[ibno]=Stz_PE.stz_bno[0];
		Stz_PE.stz_bno[0]=(BYTE)bno;
		stc_bno[stc_ptr-1][ibno]=stc_bno[stc_ptr-1][0];
		stc_bno[stc_ptr-1][0]=(BYTE)bno;
	}
	return 1;
}


BOOL bno_prop(bno) register integer_16 bno; {
	if(Fdd_Header.Fdd_PropMeaning & (0x80 >> ((bno-1)%8))){ return 1; }
	return 0;
}


BOOL bno_pno(bno,pno) register integer_16 bno,pno; {
	BYTE *si; WORD di;
	di=(pno-1)*VECP_BYTE + Fdd_Header.Fdd_VecpOfs;
	si=FddHDR+di;
	if(*(si+(bno-1)/8) & (0x80 >> ((bno-1)%8))){ return 1; }
	return 0;
}

/***************************** END OF ILE_SSKC.C *****************************/
