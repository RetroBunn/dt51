/*******************************************
	ACC_24XX.C	updated at 19th May 1989
	Accent determining routine of Number + Counter
 *******************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_acch.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"


/****************************************************************************/
/*																			*/
/*			The following describes the accent determining routine of Number + Counter.				*/
/*																			*/
/****************************************************************************/

/*========== ACC2410(p,q) ================================================
	Function: The qth counter and the pth number affect each other and are combined as 1 type.

	　In other words, a number is flattened, and a counter is pronounced with high pitch, and the entire tone is flattened.
  ========================================================================*/
void ACC2410(p,q) register integer_16 p,q; {
	ACC000H(p); ACC0005(q);
}

/*========== ACC2411(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 11 type.

	　In other words, a number is flattened, and a counter is pronounced with high pitch, and the entire tone is flattened.
	　However, when the number is 3 (SAN), 4 (YON), 5 (GO), 7 (NANA), 9 (KYU) 10 (JYU), or multiples of 10 (JYU), its ending is raised, and
		its counter is pronounced with low pitch.
		When the number is 3 (SAN), 4 (YON), or 9 (KYU), the accent moves to one previous syllable because of its syllabic nasal or long vowel.

	　The ending of the multiple of 10 (JYU) or 100 (HYAKU) is raised.
	　The accent of multiple of 十万 (JYU MAN), 百万 (HYAKU MAN), 千万 (SEN MAN), 十億 (JYU OKU), 百億 (HYAKU OKU), 千億 (SEN OKU), 十兆 (JYU CHOU), 百兆 (HYAKU CHOU), or 千兆 (SEN CHOU) is middle-raised type, 
	which is lowered at the last syllable.
  ==========================================================================*/
void ACC2411(p,q) integer_16 p,q; 
{
	register integer_16 a1,am; 
	integer_16 ae;
	am=stc_dman[p]; 
	ae=stc_dexp[p]; 
	a1=am*100+ae;
	
	/* When the number is a compound numeric and its ones digit is not zero, its ending is raised.*/
	if(ae==0 && am<=12 && p>0 && stc_kind[p-1]==DICKIND_D)
	{
		goto ACC2411_ODAKA;
	}
	if(ae==3||ae==4||ae==8||ae==12){ goto ACC2411_HEIBAN; }
	if((ae==1||ae==2)&& am>=1){ goto ACC2411_ODAKA; }	/* 20,200 */
	if(ae>=5 && am>=1){ goto ACC2411_NAKADAKA; } /* 20万 (NIJYU MAN), 200万 (NIHYAKU MAN), 2000万 (NISEN MAN), 20億 (NIJYU OKU) ...*/
	
	switch(a1){
	case 300: case 400: case 500: case 700: case 900:
		goto ACC2411_ODAKA;
	default:
		goto ACC2411_HEIBAN;
	}
	
ACC2411_ODAKA:
	ACC0002(p); 
	ACC0004(q); 
	return;
ACC2411_NAKADAKA:
	ACC0002(p);
	accent0[stc_out_ptr[q]-1]=1;
	accent0[stc_out_ptr[q]-2]=0x82;
	ACC0004(q); 
	return;
ACC2411_HEIBAN:
	ACC000H(p); 
	ACC0005(q); 
	return;
}

/*========== ACC2412(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 12 type.

	　In other words, a number is flattened, and a counter is pronounced with high pitch, and the entire tone is flattened.
	　However, when the number is 11 (JYU ICHI) to 19 (JYU KYU), or multiple of 10 (JYU), multiple of 100 (HYAKU), or multiple of 1000 (SEN),
	the number is flattened, and the counter is head-high.
  ==========================================================================*/
void ACC2412(p,q) integer_16 p,q; 
{
	register integer_16 am; 
	integer_16 ae;
	am=stc_dman[p]; ae=stc_dexp[p];

	ACC000H(p);
	if(am<=9 && ae==0 && stc_out_len[p]>2){ goto ACC2412_100; } /* 11..19 */
	if(ae>=1 && ae<=3 && am>1){ goto ACC2412_100; }	/* Multiple of 10 (JYU), 100 (HYAKU), or 1000 (SEN) */

	ACC0005(q); return;
ACC2412_100:;
	ACC0001(q);
}

/*========== ACC2413(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 13 type.

	　In other words, a number is flattened, and a counter is pronounced with high pitch, and the entire tone is flattened.
	　However, when the number is 11 (JYU ICHI) to 19 (JYU KYU), or multiple of 10 (JYU), multiple of 100 (HYAKU), or multiple of 1000 (SEN),
	When the number is flattened, the counter is pronounced with low pitch, and the last syllable of the number is mora phoneme, 
	its fall moves to the previous syllable.
  ==========================================================================*/
void ACC2413(p,q) integer_16 p,q; 
{
	register integer_16 pp,pl;
	ACC2412(p,q);
	/* When the last syllable is in ア (A) row, the accent point is moved by one syllable.*/
	pp=phrase_ptr[p]; 
	pl=phrase_len[p];
	if((omega[pp+pl-1] & 0xF8)==0x00)
	{
		accent0[pp+pl-1]=1; 
		accent0[pp+pl-2]=0x82;
	}
}

/*========== ACC2420(p,q) ================================================
	Function: The qth counter and the pth number affect each other and are combined as 2 type.

	  In other words, a number is flattened, and a counter is pronounced with high pitch, and the entire tone is raised-ending.
	However, the tone of multiple of 1000 (SEN) is flattened.
  ========================================================================*/
void ACC2420(p,q) integer_16 p,q; 
{
	register integer_16 qp,ql;
	qp=phrase_ptr[q]; 
	ql=phrase_len[q];
	ACC000H(p); 
	ACC0005(q);
	accent0[qp+ql-1]= (stc_dman[p]>=1 && stc_dexp[p]==3 ? 2:0x82);
}

/*========== ACC2421(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 21 type.

	　In other words, a number is flattened, and a counter is pronounced with high pitch, and the entire tone is raised-ending.
	　However, when the number is 3 (SAN), 4 (YON), 7 (NANA), multiple of 10 (JYU), or multiple of 100 (HYAKU), its ending is raised, and
		its counter is pronounced with low pitch.
		When the number is 3 (SAN) or 4 (YON), the accent moves to one previous syllable because of its syllabic nasal or long vowel.
		This applies also to when the multiple of 10 (JYU) or 100 (HYAKU) becomes a double consonant.
  ==========================================================================*/
void ACC2421(p,q) integer_16 p,q; 
{
	register integer_16 a1,am; integer_16 ae,qp,ql;
	am=stc_dman[p]; ae=stc_dexp[p]; a1=am*100+ae;
	if(ae==1 && am>1){ goto ACC2421_100; }	/* 20..90 */
	if(ae==2 && am>1){ goto ACC2421_100; }	/* 200..900 */
	switch(a1)
	{
	case 300: case 400: case 700:
		goto ACC2421_100;
	default:
		qp=phrase_ptr[q]; 
		ql=phrase_len[q];
		ACC000H(p); 
		ACC0005(q);
		accent0[qp+ql-1]= (am>1 && ae==3 ? 2:0x82);
		return;
	}
	
ACC2421_100:
	ACC0002(p); 
	ACC0004(q);
}

/*========== ACC2422(p,q) ====================================================
	Function: The qth counter and the pth number affect each other and are combined as 22 type.

	　In other words, a number is flattened, and a counter is pronounced with high pitch, and the entire tone is raised-ending.
	　However, when the number is 3 (SAN), 4 (YON), 6 (ROKU), 7 (NANA), 8 (HACHI), 9 (KYU), 10 (JYU), or multiple of 10 (JYU), its ending is raised, and
		its counter is pronounced with low pitch.
		When the number is 3 (SAN), 4 (YON), 9 (KYU), or 10 (JYU), the accent moves to one previous syllable because of its syllabic nasal or long vowel.
		This applies also to when the multiple of 10 (JYU) becomes a double consonant.
  ============================================================================*/
void ACC2422(p,q) integer_16 p,q; 
{
	register integer_16 a1,am; 
	integer_16 ae,qp,ql;
	am=stc_dman[p]; 
	ae=stc_dexp[p]; 
	a1=am*100+ae;
	if(ae==1){ goto ACC2422_100; }	/* 10, 20..90 */
	switch(a1)
	{
	case 300: case 400: case 600: case 700: case 800: case 900:
		goto ACC2422_100;
	default:
		qp=phrase_ptr[q]; ql=phrase_len[q];
		ACC000H(p); ACC0005(q);
		accent0[qp+ql-1]= (am>1 && ae==3 ? 2:0x82);
		return;
	}
	
ACC2422_100:
	ACC0002(p); 
	ACC0004(q);
}

/*========== ACC2423(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 23 type.

	　In other words, a number is flattened, and a counter is pronounced with high pitch, and the entire tone is raised-ending.
	　However, when the number is 2 (NI), 3 (SAN), 4 (YON), 5 (GO), 7 (NANA), 9 (KYU), multiple of 10 (JYU), multiple of 100 (HYAKU), or 1000 (SEN),
		its ending is raised, and its counter is pronounced with low pitch.
		When the number is 3 (SAN), 4 (YON), 9 (KYU), or 10 (JYU), the accent moves to one previous syllable because of its syllabic nasal or long vowel.
		This applies also to when the multiple of JYU becomes a double consonant.
  =========================================================================*/
void ACC2423(p,q) integer_16 p,q; 
{
	register integer_16 a1,am; 
	integer_16 ae,qp,ql;
	am=stc_dman[p]; 
	ae=stc_dexp[p]; 
	a1=am*100+ae;
	if(ae==1 && am>1){ goto ACC2423_100; }	/* 20..90 */
	if(ae==2 && am>1){ goto ACC2423_100; }	/* 200..900 */
	switch(a1)
	{
	case 200: case 300: case 400: case 500: case 700: case 900:
	case 003:			/*  Can 千 (SEN) and 一千 (ISSEN) be distinguished? *** problem *** */
		goto ACC2423_100;
	default:
		qp=phrase_ptr[q]; 
		ql=phrase_len[q];
		ACC000H(p); 
		ACC0005(q);
		accent0[qp+ql-1]= (am>1 && ae==3 ? 2:0x82);
		return;
	}
	
ACC2423_100:
	ACC0002(p); 
	ACC0004(q);
}

/*========== ACC2424(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 24 type.

	　In other words, a number is flattened, and a counter is pronounced with high pitch, and the entire tone is raised-ending.
	　However, when the number is 3 (SAN), 4 (YON), 5 (GO), 7 (NANA), 9 (KYU), or multiples of 10 (JYU), its ending is raised, and
		its counter is pronounced with low pitch.
		When the number is 3 (SAN), 4 (YON), or 9 (KYU), the accent moves to one previous syllable because of its syllabic nasal or long vowel.
  ==========================================================================*/
void ACC2424(p,q) integer_16 p,q; {
	register integer_16 a1,am; integer_16 ae,qp,ql;
	am=stc_dman[p]; ae=stc_dexp[p]; a1=am*100+ae;
	if(ae==1 && am>1 && am<=9){ goto ACC2424_100; }	/* 20..90 */
	switch(a1){
	case 300: case 400: case 500: case 700: case 900:
		goto ACC2424_100;
	default:
		qp=phrase_ptr[q]; ql=phrase_len[q];
		ACC000H(p); ACC0005(q);
		accent0[qp+ql-1]= (am>1 && ae==3 ? 2:0x82);
		return;
	}

ACC2424_100:;
	ACC0002(p); ACC0004(q);
}

/*========== ACC2430(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 30 type.

	　In other words, a number is flattened, and a counter is pronounced with high pitch, and the pitch is lowered at the fall of the counter.
  ==========================================================================*/
void ACC2430(p,q,falls) register integer_16 p,q; integer_16 falls; {
	ACC000H(p); ACC0003(q,falls);
	accent0[phrase_ptr[q]]=2;
}

/*========== ACC2440(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 40 type.

	　In other words, the number is flattened, and the counter becomes head-high.
  ==========================================================================*/
void ACC2440(p,q) register integer_16 p,q; {
	ACC000H(p); ACC0001(q);
}

/*========== ACC2441(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 41 type.

	　In other words, the number is flattened, and the counter becomes head-high.
	However, when the number is 4 (YON), 7 (NANA), 9 (KYU), multiple of 10 (JYU), multiple of 100 (HYAKU), or 1000 (SEN), its ending is raised, and the counter is pronounced with log pitch.
	Also, when 1 (ICHI) to 9 (KYU), 10 (JYU), 100 (HYAKU), 1000 (SEN), 数(SUU), 何 (NAN), or 幾 (IKU) is added to 万 (MAN), 億 (OKU), or兆 (CHOU), the entire tone is flattened.
		(Example) 回 (KAI)
  ==========================================================================*/
void ACC2441(p,q) integer_16 p,q; {
	register integer_16 a1,am; integer_16 ae;
	am=stc_dman[p]; ae=stc_dexp[p]; a1=am*100+ae;
	if(ae==1 && am>1){ goto ACC2441_200; }	/* Multiple of 10 (JYU) */
	if(ae==2 && am>1){ goto ACC2441_200; }	/* Multiple of 100 (HYAKU) */
	if(ACC2499(am,ae)){ goto ACC2441_500; }
	switch(a1){
	case 400: case 700: case 900: case 003:
		goto ACC2441_200;
	default:
		ACC000H(p); ACC0001(q); return;
	}

ACC2441_200:;
	ACC0002(p); ACC0004(q); return;
ACC2441_500:;
	ACC000H(p); ACC0005(q);
}

/*========== ACC2442(p,q) ====================================================
	Function: The qth counter and the pth number affect each other and are combined as 42 type.

	　In other words, the number is flattened, and the counter becomes head-high.
	However, when the number is 3 (SAN), 4 (YON), 7 (NANA), 9 (KYU), multiple of 10 (JYU), multiple of 100 (HYAKU), or 1000 (SEN), its ending is raised, and the counter is pronounced with log pitch.
	Also, when 1 (ICHI) to 9 (KYU), 10 (JYU), 100 (HYAKU), 1000 (SEN), 数(SUU), 何 (NAN), or 幾 (IKU) is added to 万 (MAN), 億 (OKU), or兆 (CHOU), the entire tone is flattened.
		(Example) 寸 (SUN)
  ============================================================================*/
void ACC2442(p,q) integer_16 p,q; {
	register integer_16 a1,am; integer_16 ae;
	am=stc_dman[p]; ae=stc_dexp[p]; a1=am*100+ae;
	/*if(ae== 1 && am>1){ goto ACC2442_200; }*/	/* 20..90 */
	/*if(ae== 2 && am>1){ goto ACC2442_200; }*/	/* 200..900 */
	if(am>1 && (ae==1||ae==2)){ goto ACC2442_200; }	/* 20..90, 200..900 */
	if(ACC2499(am,ae)){ goto ACC2442_500; }
	switch(a1){
	case 300: case 400: case 700: case 900: case 003:
		goto ACC2442_200;
	default:
		ACC000H(p); ACC0001(q); return;
	}

ACC2442_200:;
	ACC0002(p); ACC0004(q); return;
ACC2442_500:;
	ACC000H(p); ACC0005(q);
}

/*========== ACC2443(p,q) ======================================================
	Function: The qth counter and the pth number affect each other and are combined as 43 type.

	　In other words, the number is flattened, and the counter becomes head-high.
	However, when the number is 3 (SAN), 4 (YON), 7 (NANA), 8 (HACHI), 9 (KYU), 10 (JYU), multiple of 10 (JYU), multiple of 100 (HYAKU), or 1000 (SEN), its ending is raised, and the counter is pronounced with log pitch.
	Also, when 1 (ICHI) to 9 (KYU), 10 (JYU), 100 (HYAKU), 1000 (SEN), 数(SUU), 何 (NAN), or 幾 (IKU) is added to 万 (MAN), 億 (OKU), or兆 (CHOU), the entire tone is flattened.
		(Example) 合 (GOU)
  ==============================================================================*/
void ACC2443(p,q) integer_16 p,q; {
	register integer_16 a1,am; integer_16 ae;
	am=stc_dman[p]; ae=stc_dexp[p]; a1=am*100+ae;
	/*if(ae== 1 && am>1){ goto ACC2443_200; }*/	/* 20..90 */
	/*if(ae== 2 && am>1){ goto ACC2443_200; }*/	/* 200..900 */
	if(am>1 && (ae==1||ae==2)){ goto ACC2443_200; }	/* 20..90, 200..900 */
	if(ACC2499(am,ae)){ goto ACC2443_500; }
	switch(a1){
	case 300: case 400: case 700: case 800: case 900:
	case 001: case 003:
		goto ACC2443_200;
	default:
		ACC000H(p); ACC0001(q); return;
	}

ACC2443_200:;
	ACC0002(p); ACC0004(q); return;
ACC2443_500:;
	ACC000H(p); ACC0005(q);
}

/*========== ACC2450(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 50 type.

	　In other words, the number is flattened, and the counter becomes head-high.
	　However, the number is 2 (NI) or 5 (GO), its ending is raised, and the counter is pronounced with low pitch.
  ==========================================================================*/
void ACC2450(p,q) integer_16 p,q; {
	register integer_16 a1,am; integer_16 ae;
	am=stc_dman[p]; ae=stc_dexp[p]; a1=am*100+ae;
	switch(a1){
	case 200: case 500:
		ACC0002(p); ACC0004(q); break;
	default:
		ACC000H(p); ACC0001(q);
	}
}

/*========== ACC2460(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 60 type.

	　In other words, its ending is raised, and its counter is pronounced with low pitch.
	　However, when 1 (ICHI) to 9 (KYU), 10 (JYU), 100 (HYAKU), 1000 (SEN), 数 (SUU), 何 (NAN), 幾 (IKU) is added to 千 (SEN), 万 (MAN), 億 (OKU), or 兆 (CHOU),
	the number is flattened, and its counter is pronounced with high pitch, and the entire tone is flattened.
	　The accent of multiple of 十万 (JYU MAN), 百万 (HYAKU MAN), 千万 (SEN MAN), 十億 (JYU OKU), 百億 (HYAKU OKU), 千億 (SEN OKU), 十兆 (JYU CHOU), 百兆 (HYAKU CHOU), or 千兆 (SEN CHOU) is middle-raised type, 
	which is lowered at the last syllable.
		(Example) 個 (KO), トン (TON)
  ==========================================================================*/
void ACC2460(p,q) integer_16 p,q; {
	register integer_16 am,ae;
	am=stc_dman[p]; ae=stc_dexp[p];

	if((ae==3 && am>=1) || ACC2499(am,ae)){
		/* The ending of the number is raised, and its counter is pronounced with high pitch.*/
		ACC000H(p); ACC0005(q);
	}else{
		if(ae>=5 && am>=1){
			/* 20万 (NIJYU MAN), 200万 (NIHYAKU MAN), 2000万 (NISEN MAN), 20億 (NIJYU OKU) ...*/
			ACC0002(p);
			accent0[stc_out_ptr[q]-1]=1;
			accent0[stc_out_ptr[q]-2]=0x82;
			ACC0004(q);
		}else{
			/* The ending of the number is raised, and its counter is pronounced with low pitch.*/
			ACC0002(p); ACC0004(q);
		}
	}
}

/*========== ACC2461(p,q) ======================================================
	Function: The qth counter and the pth number affect each other and are combined as 61 type.

	　In other words, its ending is raised, and its counter is pronounced with low pitch.
	　However, when 1 (ICHI) to 9 (KYU), 10 (JYU), 100 (HYAKU), 1000 (SEN), 数 (SUU), 何 (NAN), 幾 (IKU) is added to 5 (GO) and 千 (SEN), 万 (MAN), 億 (OKU), or 兆 (CHOU),
	the number is flattened, and its counter is pronounced with high pitch, and the entire tone is flattened.
	　The accent of multiple of 十万 (JYU MAN), 百万 (HYAKU MAN), 千万 (SEN MAN), 十億 (JYU OKU), 百億 (HYAKU OKU), 千億 (SEN OKU), 十兆 (JYU CHOU), 百兆 (HYAKU CHOU), or 千兆 (SEN CHOU) is middle-raised type, 
	which is lowered at the last syllable.
  ==============================================================================*/
void ACC2461(p,q) integer_16 p,q; {
	register integer_16 am,ae;
	am=stc_dman[p]; ae=stc_dexp[p];

	if((ae==0 && am==5) || (ae==3 && am>=1) || ACC2499(am,ae)){
		/* The ending of the number is raised, and its counter is pronounced with high pitch.*/
		ACC000H(p); ACC0005(q);
	}else{
		if(ae>=5 && am>=1){
			/* 20万 (NIJYU MAN), 200万 (NIHYAKU MAN), 2000万 (NISEN MAN), 20億 (NIJYU OKU) ...*/
			ACC0002(p);
			accent0[stc_out_ptr[q]-1]=1;
			accent0[stc_out_ptr[q]-2]=0x82;
			ACC0004(q);
		}else{
			/* The ending of the number is raised, and its counter is pronounced with low pitch.*/
			ACC0002(p); ACC0004(q);
		}
	}
}

/*========== ACC2462(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 62 type.

	　In other words, its ending is raised, and its counter is pronounced with low pitch.
	　However, when 1 (ICHI) to 9 (KYU), 10 (JYU), 100 (HYAKU), 1000 (SEN), 数 (SUU), 何 (NAN), 幾 (IKU) is added to 千 (SEN), 万 (MAN), 億 (OKU), or 兆 (CHOU),
	the number is flattened, and its counter is pronounced with high pitch, and the entire tone is flattened.
	　When the number is a solo or compound 3 (SAN), 4 (YON), 5 (GO), or 9 (KYU), the number is flattened, and
	its counter becomes high-head. However, 13 (JYUSAN) is exceptionally middle-raised.
	　The accent of multiple of 十万 (JYU MAN), 百万 (HYAKU MAN), 千万 (SEN MAN), 十億 (JYU OKU), 百億 (HYAKU OKU), 千億 (SEN OKU), 十兆 (JYU CHOU), 百兆 (HYAKU CHOU), or 千兆 (SEN CHOU) is middle-raised type, 
	which is lowered at the last syllable.
  ==========================================================================*/
void ACC2462(p,q) integer_16 p,q; {
	register integer_16 a1,am; integer_16 ae,d11_19;
	am=stc_dman[p]; ae=stc_dexp[p]; a1=am*100+ae;

	/* 11 (JYU ICHI) to 19 (JYU KYU) are handled as basic numerals in this program, however, they are treated as compound numerals in this document.*/
	d11_19=(am>=11 && am<=19 && ae==1 ? 1:0);

	if((ae==3 && am>=1) || ACC2499(am,ae)){
		ACC000H(p); ACC0005(q); return;
	}

	if((d11_19==0 && a1==300) || a1==400 || a1==500 || a1==900){
		ACC000H(p); ACC0001(q);
	}else{
		if(ae>=5 && am>=1){
			/* 20万 (NIJYU MAN), 200万 (NIHYAKU MAN), 2000万 (NISEN MAN), 20億 (NIJYU OKU) ...*/
			ACC0002(p);
			accent0[stc_out_ptr[q]-1]=1;
			accent0[stc_out_ptr[q]-2]=0x82;
			ACC0004(q);
		}else{
			/* The ending of the number is raised, and its counter is pronounced with low pitch.*/
			ACC0002(p); ACC0004(q);
		}
	}
}

/*========== ACC2463(p,q) ==================================================
	Function: The qth counter and the pth number affect each other and are combined as 63 type.

	　In other words, basically, its ending is raised, and its counter is pronounced with low pitch.
	However, when the number is a solo 3 (SAN), or 4 (YON) or 5 (GO), or
	when 1 (ICHI) to 9 (KYU), 10 (JYU), 100 (HYAKU), 1000 (SEN), 数 (SUU), 何 (NAN), 幾 (IKU) is added to 千 (SEN), 万 (MAN), 億 (OKU), or 兆 (CHOU),
	the number is flattened, and its counter is pronounced with high pitch, and the entire tone is flattened.
	　When the first syllable of the last SAN of a compound numeral is high, it is lowered at the second syllable, and the counter is pronounced with low pitch.
	When 13 (JYU SAN) is added, it exceptionally becomes middle-raised.
	　The accent of multiple of 十万 (JYU MAN), 百万 (HYAKU MAN), 千万 (SEN MAN), 十億 (JYU OKU), 百億 (HYAKU OKU), 千億 (SEN OKU), 十兆 (JYU CHOU), 百兆 (HYAKU CHOU), or 千兆 (SEN CHOU) is middle-raised type, 
	which is lowered at the last syllable.

		(Example) 段 (DAN), 年 (NEN)
  ==========================================================================*/
void ACC2463(p,q) integer_16 p,q; {
	register integer_16 a1,am; integer_16 ae,pp,pl,complex,d11_19;
	pp=phrase_ptr[p]; pl=phrase_len[p];
	am=stc_dman[p]; ae=stc_dexp[p]; a1=am*100+ae;

	if((ae==3 && am>=1) || ACC2499(am,ae)){
		ACC000H(p); ACC0005(q); return;
	}

	/************************************************************************/
	/*																		*/
	/*	To check whether the compound numerical is pronounced with high pitch or low pitch, 	*/
	/*	check the tone of the previous syllable. In other words, when the previous syllable is high, the compound numerical is pronounced with high pitch, and if it is low, 		*/
	/*	it is pronounced with low pitch.															*/
	/*																		*/
	/************************************************************************/

	/* Zero for a solo numerical, and 1 for a compound numerical */
	complex=(p>0 && stc_kind[p-1]==DICKIND_D ? 1:0);
	/* 11 (JYU ICHI) to 19 (JYU KYU) are exceptionally treated.*/
	d11_19=(am>=11 && am<=19 && ae==1 ? 1:0);

	/*
	 * The tone of 3 (SAN), 4 (YO), 5 (GO), 9 (KU) are flattened.
	 * The ending of 1 (ICHI), 2 (NI), 4 (YON), 6 (ROKU), 7 (NANA), 8 (HACHI), or 9 (KYU) is raised, and its counter is pronounced with low pitch.
	 */
	if(complex==0 && ae==0){
		if(am==3||am==5||((am==4||am==9)&& stc_out_len[q-1]==1)){
			goto ACC2463_HEIBAN;
		}else{
			goto ACC2463_ODAKA;
		}
	}

	/*
	 * 14 (JYU YO), 15 (JYU GO), or 19 (JYU KU) is high-head, and its counter is pronounced with low pitch.
	 * 14 (JYU YON) or 19 (JYU KYU), and 
	 * 11 (JYU ICHI), 12 (JYU NI), 13 (JYU SAN), 16 (JYU ROKU), 17 (JYU NANA), or 18 (JYU HACHI), is raised-ending, and its counter is pronounced with low pitch.
	 */
	if(d11_19){
		if(((am==14||am==19)&& stc_out_len[q-1]==3)||am==15){
			goto ACC2463_ATAMA;
		}else{
			goto ACC2463_ODAKA;
		}
	}

	/* 21 (NIJYU ICHI) or higher */
	/************************************************************************/
	/*			See <ACC2300> for the processing described here.							*/
	/*	　The accent combining order for a compound numeral with a counter, the counter precedes */
	/*	the numeral. However, for combining the counter, the result of the compound numeral is	*/
	/*	required. Such troublesome processing is required accordingly.				*/
	/*	　There are some problems with the accent combining order of numerals, and depending on 		*/
	/*	the result of future study, this processing may be changed drastically.			*/
	/************************************************************************/
	/* When the previous number is 1000 or more and the last syllable is low, the counter is pronounced with low pitch.*/
	/* When the previous number is 1000 or more, and the last syllable is high, go to the next.*/
	if(stc_dexp[p-1]>=3){
		if(accent0[pp+pl-1]==1){
			goto ACC2463_ODAKA;
		}else{
			goto ACC2463_300;
		}
	}
	/* When the previous number is head-high, its ending is raised, and the counter is pronounced with low pitch.*/
	if(accent0[pp-stc_out_len[p-1]]==0x82){ goto ACC2463_ODAKA; }
	/* When the previous number is not head-high, and the latter one is flattened, go to the next.*/
	if(chk_heiban(p)){ goto ACC2463_300; }
	/* When the previous number is not head-high, and the latter one is up-and-down, the counter is pronounced with low pitch only when the latter one has two or more syllables and the last syllable is low.*/
	if(pl==1||(pl>1 && accent0[pp+pl-1]!=1)){ goto ACC2463_300; }
	goto ACC2463_ODAKA;

ACC2463_300:
	/* When SAN is placed at the last of a compound numeral and the first syllable is high, the tone is lowered at the second syllable and the counter is low.*/
	if(a1==300){
		if(accent0[pp-1]!=1){
			/* When 3 (SAN) that is placed at the last of a compound numeral is raised, */
			/* or when the previous syllable is high, 3 (SAN) becomes high.*/
			goto ACC2463_ATAMA;
		}
	}

	/* When the number is 4 (YON), 5 (GO), 9 (KYU) of a compound numeral or single numeral, the counter becomes high.*/	
	/* Otherwise, the ending of the numeral is raised, and the counter becomes low.*/
	/*if(complex==0 && (a1==400 || a1==500)){*/
	if(a1==400||a1==500||a1==900){
		goto ACC2463_HEIBAN;
	}else{
		if(ae>=5 && am>=1){
			/* 20万 (NIJYU MAN), 200万 (NIHYAKU MAN), 2000万 (NISEN MAN), 20億 (NIJYU OKU) ...*/
			ACC0002(p);
			accent0[stc_out_ptr[q]-1]=1;
			accent0[stc_out_ptr[q]-2]=0x82;
			ACC0004(q);
			return;
		}else{
			/* The ending of the number is raised, and its counter is pronounced with low pitch.*/
			goto ACC2463_ODAKA;
		}
	}

ACC2463_ATAMA:
	ACC0001(p); ACC0004(q); return;
ACC2463_ODAKA:
	ACC0002(p); ACC0004(q); return;
ACC2463_HEIBAN:
	ACC000H(p); ACC0005(q); return;
}


/*========== ACC2499(am,ae) ==================================================
	Function:  Whether or not 数 (SUU), 何 (NAN), 幾 (IKU), 1 (ICHI) to 9 (KYU), 10 (JYU), 100 (HYAKU), 1000 (SEN) is added to 千 (SEN), 万 (MAN), 億 (OKU), or 兆 (CHOU),
		is checked.

	Value: 　When the number is 数千 (SUU SEN), 数万 (SUU MAN), 数億 (SUU OKU), 数兆 (SUU CHOU), 
		　一千(ISSEN) to 九千 (KYU SEN), 一万 (ICHI MAN) to 九万 (KYU MAN), 一億 (ICHI OKU) to 九億 (KYU OKU), 一兆 (ICCHOU) to 九兆 (KYU CHOU) or
		　十万 (JYU MAN), 百万 (HYAKU MAN), 千万 (SEN MAN), 十億 (JYU OKU), 百億 (HYAKU OKU), 千億 (SEN OKU), 十兆 (JYUCCHOU), 百兆 (HYAKU CHOU), or 千兆 (SEN CHOU), 1 is returned.
		　When the number is 千 (SEN), 数十万 (SUU JYU MAN), 数百万 (SUU HYAKU MAN), 二十万 (NIJYU MAN), 一千万 (ISSEN MAN), or 一千億 (ISSEN OKU), 0 is returned.
  ==========================================================================*/
BOOL ACC2499(am,ae) register integer_16 am,ae; {
	/* When the number is less than 1000, 0 is returned.*/
	if(ae<=2){ return 0; }
	/* 一万 (ICHI MAN) to 九万 (KYU MAN), 一億 (ICHI OKU) to 九億 (KYU OKU), 一兆 (ICCHOU) to 九兆(KYU CHOU) */
	if(ae==4 || ae==8 || ae==12){ return 1; }
	/* 一千 (ISSEN) to 九千 (KYU SEN) (except 千(SEN))*/
	if(ae==3 && am>=1){ return 1; }
	/* 十万 (JYU MAN), 百万 (HYAKU MAN), 千万 (SEN MAN), 十億 (JYU OKU), 百億 (HYAKU OKU), 千億(SEN OKU), 十兆 (JYU CHOU), 百兆 (HYAKU CHOU), or 千兆 (SEN CHOU) */
	if(am==0 && ae>=5){ return 1; }
	return 0;
}

/***************************** END OF ACC_24XX.C *****************************/

