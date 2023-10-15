/**********************************************
	ILE_HNKC.C	updated at 8th January 1991
	Main conversion	
 **********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_bunh.h"
#include	"ile_edic.h"
#include	"ile_envh.h"
#include	"ile_fddh.h"
#include	"ile_idic.h"
#include	"ile_kkhh.h"
#include	"ile_mruh.h"
#include	"ile_nydh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_v5ch.h"
#include	"ile_func.h"
#include "ile_rnsc.h"

static integer_16	pop_counter = 0;


/*========== CS1000(ind) =====================================
	When the input is ind=0, start conversion from the current position.
		When it is ind=1, continue backtracking in the current state.
	Function: Continue the sentence voice conversion according to the current specified environment.
	Value: ÅÅÇO	Unconvertible
		ÅÅÇP	Conversion succeeded
		ÅÅÇQ	Unconvertible because of the limit of backtracking times
  ============================================HnkfHenkansuru==*/
integer_16 CS1000(ind) BOOL ind; 
{
	register integer_16 si,stc_before;
	integer_16 res;
	BYTE ch;

	pop_counter=0;				/* Reset the counter of the backtracking times*/
	if(ind==1){ goto CS1000_BACKTRACK; }

CS1000_START:
	Stz_CE.stz_mru=0;		/* Initialize the learning information the conversion start word.*/

CS1000_100:
	/* Obtain the maximum length of the following character string.*/
	/****************************************************************
	 *	There are various combinations of the index characters of the external dictionary.	*
	 *																*
	 *		(1)	kanji + hiragana										*
	 *		(2)	kanji + katakana		(ex) ãûÉZÉâ(KYOSERA)						*
	 *		(3)	kanji + alphabetic characters			(ex) ÇbÇaÇrÉ\ÉjÅ[(CBS SONY)				*
	 *		(4)	kanji + Arabic numerals		(ex) ÇPÇPÇOî‘(HYAKU TO BAN)					*
	 *		(5)	kanji + kanji numerals		(ex) î™åÀ(HACHINOHE)						*
	 *																*
	 *	Note that other combinations may be registered by users, and many words of other various combinations .	*
	 *	may exist in the external dictionary.										*
	 *																*
	 *	On the other hand, there are only three combinations exist in the internal dictionary.				*
	 *																*
	 *		(1) kanji, (2) hiragana, (3) kanji + hiragana				*
	 ****************************************************************/
	/* Repeat them as much as the character strings to be converted exist.*/
	
	if((celen=n_inert-ceptr)==0)
	{ 
		goto CS1000_SUCCESS; 
	}

	/* This loop is for the initial abandoned word.*/
	while(1)
	{
		/* Obtain the maximum number of characters of word to be looked up in the dictionary.*/
		if(INERT1000()==0)
		{ 
			goto CS1000_BACKTRACK; 
		}
		do{						/* Loop of the longest match method*/
			/****************
			 *	Internal dictionary	*
			 ****************/
			if(IDIC1000())		// Check the internal dictionary for this word
			{
				if(IDIC2000())
				{
					do{
						if(check_idic_null()==0)
						{
							if(FOLLOW())	// Check to see if there is a relationship between this character and the previous
							{ 
								res=1; 
								goto CS1000_NEXT; 
							}
						}
						CS1000_NXT_I: ;
					}while(IDIC3000());		// Get the location of the internal dictionary's next homonym.
				}
			}
			/****************
			 *	External dictionary	*
			 ****************/
			if(EDIC1000())		// Look for this word in the external dictionary
			{
				if(EDIC2XXX())
				{
					do{
						if(check_edic_null()==0)
						{
							if(FOLLOW())
							{ 
								goto CS1000_NEXT; 
							}
						}
						res=EDIC3XXX();
						CS1000_NXT_E: ;
					}while(res);
				}
			}
			/****************
			 *	Number processing	*
			 ****************/
			if(NUMB1000())
			{
				StzfElmKind(&Stz_CE,DICKIND_D);
				OTHER_GRCD();
				if(FOLLOW())
				{
					if(NUMB5000(0))
					{ 
						goto CS1000_100; 
					}
				}
			}
			/*************++++***
			 *	Katakana noun processing	*
			 ********************/
			if(KKANA1000())		// See if a katakana conversion is possible
			{
				StzfElmKind(&Stz_CE,DICKIND_K);
				OTHER_GRCD();
				if(FOLLOW())
				{ 
					goto CS1000_NEXT; 
				}
			}
			/************************************************************
			 *	Processing for forcible reading of unreadable phrase by looking up the Tan-kanji dictionary 	*
			 ************************************************************/
			/*
			 * kanji - hiragana
			 *	Unavailable in initial conversion mode
			 *	In retry mode, the processing is required.
			 *	Unavailable if the phrase precedes the longest character string that was able to be converted in the initial conversion mode.
			 * katakana - number
			 *	Ignore.
			 * Symbol
			 *	Always read it in correction mode.
			 * Alphabetic character
			 *	Always read.
			 */
			switch(res=TDIC1000())
			{
				case 0:	goto CS1000_SHORTEN;
				case 1:	goto CS1000_TDIC_NONE;
				case 2:	goto CS1000_TDIC_NONE;
			}

			if(TDIC2XXX()){
				do{
					if(FOLLOW()){ goto CS1000_NEXT; }
					res=TDIC3000();
					CS1000_NXT_T: ;
				}while(res);
				goto CS1000_SHORTEN;
			}

			CS1000_TDIC_NONE:;
				/* Character that is not found in any dictionary.Process it somehow.*/
				TDIC4100();
				/* The type flag (0xFF) indicates that the word is not in the Tan-kanji dictionary.*/
				/* TDIC4100Watch the order of call because ( ) damages Stz_CE.*/
				Stz_CE.stz_dman=0xFF;
				if(FOLLOW()){ goto CS1000_NEXT; }

			CS1000_SHORTEN:;
		}while(celen=INERT2000(ceptr,celen));	// Shorten the "current element length" starting at the "current element start position" 

		/* When the search of the initial abandoned word has finished, give up the use of dictionary word.*/
		if(StzfAttrAri(Stz_CE,stz_mru,BITMRU_ABORT)){ goto CS1000_ND; }
		/* Instruct the search of the initial abandoned word.*/
		StzfAttrAdd(Stz_CE,stz_mru,BITMRU_ABORT);
		/* To repeat the dictionary lookups, obtain the maximum length of the following character string.*/
		celen=n_inert-ceptr;
	}/* This loop is for the initial abandoned word.*/

CS1000_ND:	/* non existent in dictionary */
	/********************
	 *	Katakana noun processing	*
	 ********************
	 *celen=n_inert-ceptr;
	 *INERT1000();
	 * When the word includes characters other than katakana, shorten it.*
	 *if(inert_kind[ceptr]!=CHRKIND_KKana){ goto CS1000_ND_V5; }
	 *while(1){
	 *	if(OTHER2000()){ break; }
	 *	celen=INERT2000(ceptr,celen);
	 *}
	 * When the preceding character is naturally-generated katakana, no processing is performed.89.11.15 *
	 *if(ceptr!=0){
	 *	if(stc_kind[stc_ptr-1]==DICKIND_K){ goto CS1000_ND_V5; }
	 *}
	 * When the word is a katakana word succeeding another katakana word, and 
	 * if it starts with a syllabic nasal, long vowel, or double consonant, an error is generated.91.1.8
	 *
	 *if(ceptr!=0){
	 *	if(inert[ceptr*2-2]==0x25){
	 *		if(inert_attr[ceptr]==CHRATTR_Soku){ goto CS1000_ND_V5; }
	 *	}
	 *}
	 *StzfElmKind(&Stz_CE,DICKIND_K);	* The type of the word is katakana noun.*
	 *OTHER_GRCD();						* Specify the grammar information of the katakana noun.*
	 *if(FOLLOW()){ goto CS1000_NEXT; }
	 */
//CS1000_ND_V5:;
	/* If there is no preceding element, the automatic generation of the 5-step verb conjunctive conjugation ending cannot be performed.*/
	if(stc_ptr==0){ goto CS1000_BACKTRACK; }
	/*
	 * When the preceding element includes a 5-step verb stem, it assumes that the conjunctive conjugation ending is omitted, and 
	 * it generates the ending automatically and attempts to convert the following element.
	 *
	 *	 When the following element is an element to be connected to a stem, such as a conjunctive conjugation ending, 
	 * it becomes redundant because the conjunctive conjugation ending has been generated.
	 *	 However, "(Ç®òbÇµÇƒOHANASHISHITE)" are also to be read as "Ç®ÇÕÇ»ÇµÇµÇƒ(OHANASHISHITE),"
	 * it is necessary to leave the processing.
	 *	 As a result, "çsÇ¡Çƒ(ITTE)" can also be read as "Ç®Ç±Ç»Ç¢Ç¡Çƒ(OKONAITTE)" or "Ç¢Ç´Ç¡Çƒ(IKITTE),"
	 * but it cannot be avoided.
	 */
	stc_before=stc_ptr-1;
	/*
	 *	When the preceding element is not a 5-step verb stem, no processing is performed.
	 *	When the preceding element is a 5-step verb stem, its back-end number is stored.
	 *	This back-end number is required to generate the conjunctive conjugation ending is automatically later.
	 */
	if((si=chk_limits(Fdd_Header.Fdd_Bno5danLL,Fdd_Header.Fdd_Bno5danUL,
					  &stc_bno[stc_before][0],stc_nbno[stc_before]))==0){ goto CS1000_BACKTRACK; }
	flg_v5you=stc_bno[stc_before][si-1];	/* Back-end number of a 5-step verb */
	/*
	 * The last character of a stem of a shortened form of a 5-step verb conjunctive conjugation must be a kanji.
	 *		"Ç§Ç≤Ç´(UGOKI)" or "ñ¬Ç©Çµ(NAKASHI)" are not acceptable."Ç‘ÇøâÛÇµ(BUCHIKOWASHI) is acceptable.
	 */
	if(inert_kind[stc_in_ptr[stc_before]+stc_in_len[stc_before]-1]!=CHRKIND_Kanji){
		goto CS1000_BACKTRACK;
	}
	/* When a punctuation follows immediately after a stem, it is not recognized as a shortened form.*/
	ch=inert_kind[ceptr] & 0xF0;
	if(ch==CHRKIND_Other1||ch==CHRKIND_Other2){ goto CS1000_BACKTRACK; }
	/* When a non-kanji character follows immediately after a stem, it is not recognized as a shortened form.*/
	ch=inert_kind[ceptr] & 0xF0;
	if(ch!=CHRKIND_Kanji){ goto CS1000_BACKTRACK; }
	/* It generates the conjunctive conjugation ending automatically and attempts to convert the following element.*/
	V5DANYOU_PUSH();
	StzfElmForward();		/* Proceed the element connection related information by an element.*/
	goto CS1000_START;

CS1000_NEXT:;
	/*
	 * When the current watching element is a counter suffix, and the preceding element is a number, 
	 * the number is read as a full number forcibly.
	 * However, this processing is not performed in correction mode.
	 */
	if(onsei_addr->onsei_kouseisystem==0 &&
	   Stz_CE.stz_kind==DICKIND_E && stc_ptr>1)
	{
		if(chk_limits(Fdd_Header.Fdd_GrcdNum1,Fdd_Header.Fdd_GrcdNum2, Stz_CE.stz_grcd,Stz_CE.stz_ngrcd))
		{
			if(chk_value(Fdd_Header.Fdd_GrcdDigit, Stz_PE.stz_grcd,Stz_PE.stz_ngrcd))
			{
				NUMB5XXX(1);
			}
		}
	}
	OMEGA5000();			/* When it can be connected, obtain the output result of the current element.*/
	STACK_PUSH();			/* Stack the information of the current element on the stack.*/
	ceptr+=celen;			/* Next input data position */
	/*
	 *	When the current watching element is a counter suffix, and the preceding element is a number, 
	 *	pronunciations of numbers and counter suffixes may vary.
	 *	In such cases, the contents of the stack is more likely to be changed.
	 *	It requires special attention.
	 *	The counter suffixes exist only in the external dictionary.
	 */
	if(Stz_CE.stz_kind==DICKIND_E && stc_ptr>1)
	{
		if(chk_limits(Fdd_Header.Fdd_GrcdNum1,Fdd_Header.Fdd_GrcdNum2, Stz_CE.stz_grcd,Stz_CE.stz_ngrcd))
		{
			if(chk_value(Fdd_Header.Fdd_GrcdDigit, Stz_PE.stz_grcd,Stz_PE.stz_ngrcd))
			{
				DIGIT7000();
			}
		}
	}

	StzfElmForward();		/* Proceed the word connection related information by one word.*/
	goto CS1000_100;		/* Repeat it as long as the word is connectable.*/

CS1000_SUCCESS:;
	ACCXXXX();				// Add accent information
	/*
	 *	When the conversion succeeds, set max_ceptr to any number except zero.
	 *	The valus of max_ceptr can be changed only when it is in initial mode.
	 *	This is used for pron.c.-- However, it is not used as of 88/2/23.
	 */
	if(conv_mode==CONV_FIRST)
	{ 
		max_ceptr=n_inert; 
	}
	return 1;

CS1000_BACKTRACK: ;
	/************************************************************************
	 *	Even if there is a break error in a number string, the processing is next target is not performed.		*
	 *	It is probably impossible to happen such thing in usual number strings.	*
	 *	If it happens in the future, we will reconsider it.				*
	 ************************************************************************/

	/*
	 *	Save the longest one of the converted elements.
	 *	If the current element cannot be the last, do not save it.
	 */
	if(conv_mode==CONV_FIRST && ceptr>max_ceptr){
		/*
		 *	when the preceding element is an automatically-generated conjunctive conjugation ending, it cannot be a break.
		 *	This correction is performed by V5DAN_PUSH().In other words, clear BITCTL_LAST.
		 */
		/*$if(stc_kind[stc_ptr-1]!=DICKIND_5Y){*/
			/* Save the element only when its preceding element can be the last.*/
			if(stc_ctl[stc_ptr-1] & BITCTL_LAST){
				max_ceptr=ceptr; /*max_cpron_ptr=cpron_ptr;*/
			}
		/*$fi*/
	}

 	/* If it is not the top word,*/
	while(ceptr!=0){
		/*
		 *	when the watching sentence length is fixed, 
		 *	it cannot be converted if it has been returned before the watching sentence.
		 */
		if(conv_mode==CONV_NEXT||conv_mode==CONV_SHORT||conv_mode==CONV_LONG){
			if(ceptr<=wsptr){ return 0; };
		}

		/* Limit the backtrack times to improve the conversion speed of the unconvertible elements.*/
		/* It cannot be aborted by the pop counts except in initial conversion.*/
		if(conv_mode==CONV_FIRST){ ++pop_counter; }
		if(pop_counter>MAX_POP_TIMES){ goto CS1000_TIME; }

		/* Return the contents in stack by one.*/
		STACK_POP();

		/************************************************************************
		 *	Depending on the counter suffix, the pronunciation of numbers may change, or 				*
		 *	the last syllable of the number may be changed to a double consonant.  Therefore, when a backtrack is generated, *
		 *	it is necessary to restore the pronunciation and accent of numbers to the original form.					*
		 *	For example, "ìx" in "ÇQÇOìx" can be read in two different ways, "TABI" and "DO,"		*
		 *	which are both counter suffixes. When "TABI" appears first and 20 takes a double consonant, 	*
		 *	if "DO" appears next, 20 is still with double consonant, 		*
		 *	so it is pronounced as "NIJUDDO."										*
		 *	Therefore, after a stack is popped, if the top of the stack is a number,*
		 *	pop the number and reconvert the number.				*
		 *	The connection information of the counter suffixes must be stored here.				*
		 ************************************************************************/

		/* When the preceding element is a number, reconvert it.*/
		if(stc_ptr){ NUMB5XXX(0); }

		/* When the restored element has its origin in the internal dictionary, go on to the succeeding processing of the internal dictionary search.*/
		if(Stz_CE.stz_kind==DICKIND_I)
		{
			push_null((WORD)ceptr, (WORD)idic_addr, 0);
			goto CS1000_NXT_I;
		}

		/* When the restored element has its origin in the external dictionary, */
		if(Stz_CE.stz_kind==DICKIND_E){
			push_null(ceptr,edic_ofs,edic_page_no);
			/* look up the external dictionary again, and search the next same character word with different pronunciation.*/
			RnsfReadEdic(edic_page_no,&edic_page_addr);
			res=EDIC3XXX();
			goto CS1000_NXT_E;
		}

		/* When the restored element has its origin in the Tan-kanji dictionary, */
		if(Stz_CE.stz_kind==DICKIND_T){
			if(Stz_CE.stz_dman==0xFF){
				/* if the word is not unreadable, the next target cannot exist.*/
				res=0;
			}else{
				/* Look up the Tan-kanji dictionary again, and search the next pronunciation.*/
				RnsfReadEdic(edic_page_no,&edic_page_addr);
				res=TDIC3000();
			}
			goto CS1000_NXT_T;
		}
		/*
		 *	When the restored element is not from the dictionaries but generated automatically,
		 *	change the length.
		 *	Katakana, number, and special symbol contradict each other, 
		 *	if one of them cannot be converted, then any of them is unconvertible.
		 */
		/* Because there is no next target for katakana noun, pop one more element.*/
		if(Stz_CE.stz_kind!=DICKIND_K){
			goto CS1000_SHORTEN;
		}
	}

//CS1000_FAIL:;	
	return 0;	/* Notify of unconvertible state.*/

CS1000_TIME:;	
	return 2;	/* Limit of pop counts */
}

/*FUNCTION_HEADER**********************
 * NAME:	;ACCXXXX
 * DESC: 	Add accent information
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void ACCXXXX() 
{
	PAUSE1000();	/* Determining the categories including conjunctive or attributive modifications and end form, and the pause time*/
	/*
	 * Watch the order of calls of ACC1000..ACC700, OMEGA9000, and PAUSE1000.
	 */
	ACC4000();		/* Categorizing syllabic nasal and double consonant*/
	ACC1000();		/* Setting of basic accents*/
	ACC2000();		/* Combining accents*/

	/*PAUSE1000();	Determining the categories including conjunctive or attributive modifications and end form, and the pause time*/
	ACC_JOSI_NO();	/* When there is no pause, if the case particle "ÇÃ(NO)" is high-pitch, then the next syllable is raised.*/
	ACC5000();		/* Combining accents of sentences*/
	ACC_PHRASE();	/* Determine a phrase delimiter on a "wave."*/

	ACC7000();		/*
					 * Exceptional processing of a conjunctive ending.A fall moves to one previous syllable.
					 * Because "é@Çµ(SASSHI)" and "êMÇ∂(SHINJI)" include mora phonemes, 
					 * it moves to one more syllable, and this processing is performed by ACC3000().
					 */
	ACC3000();		/* Processing for when the fall of an accent exists immediately before a syllabic nasal, double consonant, or long vowel.*/
	ACC6000();		/* Converting the nasal voiced consonant at the top of the sentence and devoicing a vowel*/
	ACC8000();		/* Determine the syllable of level 9 (interrogative sentence).*/

	ACC_OUTPUT();
	OMEGA9000();	/* Call the conversion result, and pass it to the program.*/
}

/***************************** END OF ILE_HNKC.C *****************************/

