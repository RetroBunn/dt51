/***********************************************
	ACC_3000.C	updated at 30th October 1989
	General Rules for Double Consonant, Syllabic Nasal, and Long Vowel
 ***********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_acch.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_func.h"


/*========== ACC3000() =========================================
	Function:  When the fall of the accent is located immediately after a double consonant, syllabic nasal, or long vowel, 
		the fall of the accent is moved one previous syllable.
  ==============================================================*/
void ACC3000() {
	register integer_16 i,j;
	integer_16 cx;
	BYTE ch;
	for(i=0;i<stc_ptr;++i){
		if((cx=phrase_len[i])>2){
			for(j=phrase_ptr[i]+1,cx-=2;cx--;++j){
				ch=omega[j];
				if(ch>=0xC0 && ch<=0xD7){
					if(accent0[j]!=1 && accent0[j+1]==1){
						accent0[j-1]=0x82; accent0[j]=1;
					}
				}
			}
		}
	}
}

/*========== ACC4000() ======================================================
	Function:  Distinguishing a syllabic nasal from a long vowel

	In the number sound conversion, syllabic nasals and long vowels are not distinguished, so
	it is necessary to categorize the syllabic nasals and long vowels.
	In ile_dtbl.h, the syllabic nasal is defined as 0xD7, and the long vowel is defined as 0xCF.
	For items of both internal and external dictionaries, only when the last mora phoneme is a syllabic nasal or long vowel, 
	it depends on the next mora phoneme.
	Note that the mora phonemes other than the last one does not always depend on the next mora phoneme.
	If a pose is inserted after the syllabic nasal, it is X2.

	88.11.22
	It seems there is no exception, so every item needs to be checked.
  ===========================================================================*/
void ACC4000() 
{ 
	check_X(omega,cpron_ptr);
}


/*========== ACC4100(addr) ===================================
	Function:  Syllabic nasals depend on the next mora phoneme, and they are classified into several classes.

		Before Ni or JI, it is X3.
		Before PA row, MA row, or BA row, it is X1.
		Before NA row, TA row, DA row, or SA row, it is X2.
		Before GA row, QA row, or KA row, it is X4.
		Before A row or HA row, it is X5.
  ============================================================*/
void ACC4100(addr) register BYTE *addr; {
	BYTE next_mora;
	next_mora=(*(addr+1));

	switch(next_mora){
	case 0x39: case 0x89:
		*addr=0xD2;	return;					/* X3 before (NI),(JI) */
	}

	switch(next_mora & 0xF8){
	case 0xA0: case 0x50: case 0x98:
		*addr=0xD0; break;					/* X1 before PA,MA,BA */
	case 0x38: case 0x20: case 0x90: case 0x10:
		*addr=0xD1; break;					/* X2 before NA,TA,DA,SA */
	case 0x08: case 0x70: case 0x78:
		*addr=0xD3; break;					/* X4 before GA,QA,KA */
	case 0x00: case 0x40:
		*addr=0xD4; break;					/* X5 before A,HA */
	default:
		*addr=0xD1; break;					/* X2 before default */
	}
}

/*========== ACC4200(addr) ===================================
	Function:  Double consonants depend on the next mora phoneme, and they are classified into several classes.

		Before SA row, it is $1.
		Before SHA row, it is $2.
		Before HA row, it is $3.
		It is $ for others.
  ============================================================*/
void ACC4200(addr) register BYTE *addr; {
	switch(*(addr+1) & 0xF8){
	case 0x10:	*addr=0xC9; break;			/* $1 before SA */
	case 0x18:	*addr=0xCA; break;			/* $2 before SHA */
	case 0x40:	*addr=0xCB; break;			/* $3 before HA */
	default:	*addr=0xC8; break;			/* $ before default */
	}
}

/*========== check_X(p,l) =========================
	Function:  Classify the syllabic nasals and double consonants according to the preceding and succeeding letters.

	88.11.22
	It seems there is no exception, so every item needs to be checked.
  =================================================*/
void check_X(BYTE *p, integer_16 l)
{
	register integer_16 len; register BYTE *ptr;
	/* Syllabic nasal */
	for(len=l,ptr=p;len--;++ptr)
	{
		/*if(*ptr==0xD7){*/
		if((*ptr & 0xF0)==0xD0)
		{
			if(len==0)
			{
				*ptr=0xD1;
			}
			else
			{
				ACC4100(ptr);
			}
		}
	}

	/* Double consonant */
	for(len=l,ptr=p;len--;++ptr)
	{
		/*if(*ptr==0xCF){*/
		if((*ptr & 0xF8)==0xC8)
		{
			if(len==0)
			{
				*ptr=0xC8;
			}
			else
			{
				ACC4200(ptr);
			}
		}
	}
}

/***************************** END OF ACC_3000.C *****************************/

