/*C_HEADER_FILE****************************************************************
FILE			:	ILE_IDIC.C
DESC			:	Internal Dictionary
TABS			:	3
OWNER			:	Fonix
DATE CREATED	:	5 Sept 1989

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
#define		EXT		extern

#include	"onsei.h"
#include	"ile_fddh.h"
#include	"ile_idic.h"
#include	"ile_jknh.h"
#include	"ile_kkhh.h"
#include	"ile_mruh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"


/*FUNCTION_HEADER**********************
 * NAME:	;IDIC1000
 * DESC: 	Check in the internal dictionary to see if the current 
			attention word is found.
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
BOOL IDIC1000() 
{
	/*
		Check the status of the attention elements, then make decision
		when looking up in the internal dictionary 
		If the greatest possible number is exceeded, there is no possibility.
		If in the dictionary referene table it is written having no reading, there is no possibility.
		If any other situation than the above, there is possibility
	*/
	if(celen>MAX_IDIC)
		return 0;
	if(JknfAttrAri(BITDUT_ID_NONE))
		return 0;

	return 1;

	/*
		From first time abandoned words search instruction, if it is not a first time abandoned word, then ???
	 *	if( StzfAttrAri(Stz_CE, stz_mru, BITMRU_ABORT) &&
			JknfAttrAri(BITDUT_ID_ABORT)==0 )
			{ return 0; }
	 */
}


/*FUNCTION_HEADER**********************
 * NAME:	;IDIC2000()
 * DESC: 	Begin from the current element start location, 
			there is a current element length of a word.  
			Seek for address in the memory in the internal dictionary.  
			If there is an error, set the error code and return.
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
BOOL IDIC2000() 
{
	register BYTE *si,*di;
	IDIC_INDICES *mjsptr;
	BYTE *endptr,*source,*njsptr;
	integer_16 len,cebyte;
	WORD offset;

	cebyte=celen*2;

	/* If it is in the dictionary reference table, then use it. */
	if(JknfAttrAri(BITDUT_ID_EXIST))
	{
		njsptr=JknfIdicToridasu;
		goto IDIC2000_200;
	}

	source=(&inert[ceptr*2]);

	mjsptr = (IDIC_INDICES *)(&FddHDR[Fdd_Header.Fdd_IdicIndOfs]
			+ sizeof(IDIC_INDICES)*(celen-1));
	/* offset = mjsptr->idic_len_ptr; */
	offset = (mjsptr->idic_len_ptr1 <<8) + mjsptr->idic_len_ptr2;
	njsptr = FddHDR + Fdd_Header.Fdd_IdicOfs + offset;
	/* offset = (mjsptr+1)->idic_len_ptr; */
	offset = ((mjsptr+1)->idic_len_ptr1 <<8) + (mjsptr+1)->idic_len_ptr2;
	endptr = FddHDR + Fdd_Header.Fdd_IdicOfs + offset;

	for(;;)
	{
		if(njsptr>=endptr)
		{ 
			JknfAttrAdd(BITDUT_ID_NONE); 
			return 0; 
		}
	
		/* Compare list */
		si=source; 
		di=njsptr;
		for(len=cebyte; len; len--,si++,di++)
		{
			if(*si!=(*di))
			{ 
				break; 
			}
		}

		/* If they all match, then OK.  */		
		if(len==0)
		{ 
			break; 
		}
			
		/* If the internal dictionary is larger, then record that it wasn't i the internal dictionary. */
		if(*si<*di)
		{ 
			JknfAttrAdd(BITDUT_ID_NONE); 
			return 0; 
		}

		/* If the internal dictionary's current element list is smaller, then proceed to the next list. */
		njsptr += cebyte+SIZE_IDIC;
	}

	/* Save the current observed element's control information offset. */
	njsptr+=cebyte;
	JknfAttrAdd(BITDUT_ID_EXIST);	/* Record that it is in the internal dictionary.  */
	JknfIdicShimau(njsptr);			/* Close the offset in the dictionary reference table. */
	
IDIC2000_200:
	idic_addr=njsptr;
	/* If it is in the learning state (condition), use the current word.  */
	if(kkhstat != mru)
	{
		if(((IDIC_DATA *)njsptr)->idic_mru & BITMRU_ABORT)
		{
			/* ¸If the word that was found is an 'abandoned' word and 
				if the directions are abandoned words non-adaptive, 
				then search for the next candidate.
			 */
			JknfAttrAdd(BITDUT_ID_ABORT);
			if(StzfAttrNashi(Stz_CE, stz_mru, BITMRU_ABORT))
			{
				return IDIC3000();
			}
		}
		else
		{
			/*	If the word found is not an abandoned word, and if the 
				directions are abandoned words adoptive, then search 
				for the next candidate.
			 */
			if(StzfAttrAri(Stz_CE, stz_mru, BITMRU_ABORT))
			{
				return IDIC3000();
			}
		}
	}

	/*	Setting the observed elements linking (joining) information, 
		pronunciatin information, etc. */
	IDIC4000();
	return 1;
}


/*FUNCTION_HEADER**********************
 * NAME:	;IDIC3000()
 * DESC: 	Request the location of the internal dictionary's word's next homonym.
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
BOOL IDIC3000() 
{
	integer_16 len;
	IDIC_INDICES *mjsptr;
	BYTE *endptr,*source;
	register BYTE *si,*njsptr;
	WORD offset;

	source = ceptr*2+inert;
	njsptr = idic_addr+SIZE_IDIC;

	mjsptr = (IDIC_INDICES *)(&FddHDR[Fdd_Header.Fdd_IdicIndOfs]
			+ sizeof(IDIC_INDICES)*celen);
	/* offset = mjsptr->idic_len_ptr; */
	offset = (mjsptr->idic_len_ptr1 <<8) + mjsptr->idic_len_ptr2;
	endptr = FddHDR + Fdd_Header.Fdd_IdicOfs + offset;

	for(;;)
	{
		if(njsptr>=endptr)
		{ return 0; }

		/* Compare the list. */
		si=source;
		for(len=celen*2; len--;)
		{
			if(*si++!=(*njsptr++))
			{ return 0; }
		}
	
		/* If it is in the learning state, use the current word.  */
		if(kkhstat==mru)
		{ break; }
		/*
			Last time when it was abandoned word, record it in the 
			dictionary's reference table and if are adopt abandoned word then use.
		 */
		if(((IDIC_DATA *)njsptr)->idic_mru & BITMRU_ABORT)
		{
			JknfAttrAdd(BITDUT_ID_ABORT);
			if(StzfAttrAri(Stz_CE,stz_mru,BITMRU_ABORT))
			{ break; }
		}
		else
		{
			if(StzfAttrNashi(Stz_CE,stz_mru,BITMRU_ABORT))
			{ break; }
		}
		njsptr += SIZE_IDIC;
	}

	idic_addr=njsptr;
	IDIC4000();
	return 1;
}


/*FUNCTION_HEADER**********************
 * NAME:	;IDIC4000
 * DESC: 	Set the current words linking information
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void IDIC4000() 
{
	register IDIC_DATA *njsptr;

	StzfElmKind(&Stz_CE,DICKIND_I);			/* Vocabulary classification is internal dictionary */
	njsptr = (IDIC_DATA *)idic_addr;		/* Pick out the observed location of the internal dictionary*/
	Stz_CE.stz_f2 = njsptr->idic_f2;		/* Set flag 2*/
	Stz_CE.stz_ctl = njsptr->idic_ctl;		/* Set control information */
	Stz_CE.stz_ngrcd = 1;					/* grammar code number is one. */
	StzfBnoAdd(&Stz_CE,njsptr->idic_bno);	/* Set the end number */
	Stz_CE.stz_pno[0] = njsptr->idic_pno;	/* Set the front vector number */

	/* Set the training information. (carry over the last times abandoned word flag.)*/
	Stz_CE.stz_mru = (njsptr->idic_mru & ~BITMRU_ABORT) | (Stz_CE.stz_mru & BITMRU_ABORT);

	/*
		If the current word is a kanji linking preceding word, add (includde) the kanji word 
		to the linking condition instruction here in order to check the existence or absense 
		of a kanji linking for the preceding word, use the kanji flag that was set.
	 */
	if(njsptr->idic_ctl & BITCTL_PKANGO)
	{ 
		Stz_CE.stz_stz |= BITSTZ_KANGO; 
	}
}


/*FUNCTION_HEADER**********************
 * NAME:	;IDIC5000
 * DESC: 	Store the current observed word's pronunciation list from the output data areas's di character.
 * IN:		di
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
integer_16 IDIC5000(integer_16 di)
{
	register BYTE 
		*si;
	register integer_16 
		cx;
	IDIC_DATA 
		*njsptr;
	integer_16 
		a_len,
		p_len;
	BYTE 
		*accptr,
		al,
		ah,
		*ti;
	WORD 
		offset;

	/* Pull out the internal dictionary's current observed position.  */
	njsptr=(IDIC_DATA *)idic_addr;

	/* Pull out the internal dictionary's accent and pronunciation position  */
	/* offset = njsptr->idic_acc_ofs; */
	offset = (njsptr->idic_acc_ofs1 <<8) + njsptr->idic_acc_ofs2;
	accptr = (&FddHDR[Fdd_Header.Fdd_IdicPronOfs]) + offset;

	p_len=(*accptr++);
	a_len=p_len>>4;				/* length of accent information */
	p_len &= 0x0F;				/* length of pronunciation information */

	for(cx=a_len; cx--; )
	{
		al=(*accptr++);
		ah=al/16; 
		al=al%16;
		if(ah<10)
		{ 
			stc_accent_raw[stc_ptr][ah]=al; 
		}
	}

	ACC0010();

	/* Pull out pronunciation information  */
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
		for(si=inert_pron; cx--; ++si)
		{
			di=OMEGA1000(*si,di); ++cpron_len;
		}
	}
	else
	{
		for(cx=cpron_len=p_len; cx--; ) 
		{
			al=(*accptr++); 
			di=OMEGA1000(al,di);
		}
	}
	return di;
}

/***************************** END OF ILE_IDIC.C *****************************/
