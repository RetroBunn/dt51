/*
 ***********************************************************************
 *
 *                           Copyright ©
 *	  Copyright © 2002 Fonix Corporation. All rights reserved.
 *
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Fonix Corporation and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Fonix or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:    lsw_main2.c
 *    Author:       Ellen Rasmussen
 *    Creation Date:09/26/2004
 *
 *    Functionality:
 *    delcaration of Lts_t when using MULTIPLE_LANGUAGES_LOADED define
 *
 ***********************************************************************
 *    Revision History:                    
 *
 *  Rev Who     Date        	Description
 *  --- -----   ----------- 	---------------------------------------
 ***************************************************************************/
#include "port.h"
#include "dectalkf.h"
#include "ls_def.h"
#include "tts.h"

#ifdef USE_NAND
#include "cm_def.h"
#include "ph_def.h"
#include "par_def.h"

extern void ls_util_send_phone(LPTTS_HANDLE_T phTTS,int ph);
extern void ls_spel_spell(LPTTS_HANDLE_T phTTS,LETTER *lp1, LETTER *lp2);
extern int ls_util_lookup(LPTTS_HANDLE_T phTTS,LETTER *llp, LETTER *rlp, int context);

extern const unsigned short parser_char_types[];
#ifndef KEEP_SEARCHING
#define KEEP_SEARCHING  0
#endif
#ifndef LS_TASK_LOOP
#define LS_TASK_LOOP    1
#endif
#ifndef SPELL_WORD
#define SPELL_WORD      2
#endif
#ifndef FINISHED_WORD
#define FINISHED_WORD   3
#endif
#endif //USE_NAND

#if defined MULTIPLE_LANGUAGES_LOADED && defined ARM7 && !defined EPSON_ARM7 && !defined ALLOC_MEMORY
LTS_T   Lts_t;
#endif

#ifdef USE_NAND
unsigned char GetUCharValue(LPTTS_HANDLE_T phTTS, int index, int tableoff)
{
	int ret=0;
	unsigned char value=0;
	PKSD_T pKsd_t=phTTS->pKernelShareData;

	ret=GetTableValue(pKsd_t->grfdicFileHandle,&value,index,tableoff);

	if (!ret)
	{
		return 0;
	}
	return value;
}
char GetCharValue(LPTTS_HANDLE_T phTTS,int index,int tableoff)
{
	int ret=0;
	char value=0;
	PKSD_T pKsd_t=phTTS->pKernelShareData;

	ret=GetTableValue(pKsd_t->grfdicFileHandle,&value,index,tableoff);

	if (!ret)
	{
		return 0;
	}
	return value;
}

unsigned short GetUShortValue(LPTTS_HANDLE_T phTTS,int index,int tableoff)
{
	int ret=0;
	unsigned short value=0;
	PKSD_T pKsd_t=phTTS->pKernelShareData;

	ret=GetTableValue(pKsd_t->grfdicFileHandle,&value,index,tableoff);

	if (!ret)
	{
		return 0;
	}
	return value;
}
short GetShortValue(LPTTS_HANDLE_T phTTS,int index,int tableoff)
{
	int ret=0;
	short value=0;
	PKSD_T pKsd_t=phTTS->pKernelShareData;

	ret=GetTableValue(pKsd_t->grfdicFileHandle,&value,index,tableoff);

	if (!ret)
	{
		return 0;
	}
	return value;
}


unsigned int GetUIntValue(LPTTS_HANDLE_T phTTS,int index,int tableoff)
{
	int ret=0;
	unsigned int value=0;
	PKSD_T pKsd_t=phTTS->pKernelShareData;

	ret=GetTableValue(pKsd_t->grfdicFileHandle,&value,index,tableoff);

	if (!ret)
	{
		return 0;
	}
	return value;
}

int GetIntValue(LPTTS_HANDLE_T phTTS,int index,int tableoff)
{
	int ret=0;
	int value=0;
	PKSD_T pKsd_t=phTTS->pKernelShareData;

	ret=GetTableValue(pKsd_t->grfdicFileHandle,&value,index,tableoff);

	if (!ret)
	{
		return 0;
	}
	return value;
}
#endif


#ifdef USE_NAND
/*
 *	Function Name:
 *	ls_rule_phone_alloc
 *
 *	Description:
 * 	Allocate a new
 * 	phoneme from the list of
 * 	free phoneme nodes. Return a
 * 	pointer to the new node,
 * 	or NULL if there are no nodes
 * 	left in the free list.
 *
 *	Arguments:            
 *		PLTS_T 	pLts_t
 *
 *	Return Value:
 *
 *	Comments:
 *
 */
PHONE *ls_rule_phone_alloc(PLTS_T pLts_t)
{
	 PHONE	*pp;

	if ((pp=pLts_t->pflp) != NULL)
	{
		pLts_t->pflp = pp->p_fp;
//		pp->p_ip = NULL;
                pp->p_fp = pp->p_bp = NULL;
	}
	return (pp);
}

/*
 *	Function Name:
 *	ls_rule_phone_free
 *
 *	Description:
 * 	Put a phoneme node back
 * 	onto the list of free phoneme
 * 	nodes, for use by "ls_rule_phone_alloc".
 *
 *	Arguments:            
 *		PLTS_T 	pLts_t
 *		PHONE *pp
 *
 *	Return Value:
 *		None
 *
 *	Comments:
 *
 */
void ls_rule_phone_free(PLTS_T pLts_t,PHONE *pp)
{
	pp->p_fp = pLts_t->pflp;
	pLts_t->pflp = pp;
}                               

/* ******************************************************************
 *  Function Name: find_next_marker() 
 *
 *  Description:
 *
 *  Arguments:	PLTS_T pLts_t
 *				int pos
 *
 *  Return Value: int
 *
 *  Comments:
 *
 * *****************************************************************/
#if defined ENGLISH_US || defined ITALIAN

int find_next_marker(PLTS_T pLts_t,int pos)
{
	int i;
	int count=1;
	for (i=pos+1;i<pLts_t->fc_index;i++)
	{
		if (pLts_t->pro_markers[i]&0x00FFFFFF)
		{
			break;
		}
		count++;
	}
	return(count);
}
#endif

/* ******************************************************************
 *  Function Name:                      
 *      ls_task_find_end_of_word()
 *
 *  Description:                
 *      finds the end of the word contained the global cword array
 *
 *  Arguments:
 *      LETTER  *llp    the left bounding pointer to the word
 *      LETTER **rlp    the right bounding pointer to the word
 *      LETTER **elp    another pointer (set to the value of rlp)
 *
 *  Return Value:                               
 *      None
 *
 *  Comments:
 *      rlp and elp are set by this function and passed back to the 
 *      caller
 *
 * *****************************************************************/
void ls_task_find_end_of_word(LETTER *llp, LETTER **rlp, LETTER **elp)
{
#ifdef LS1DEBUG
		FNX_PRINTF("entering ls_task_find_end_of_word\n");
#endif
	(*elp) = llp;
	while ((*elp)->l_ch != EOS) /* find the end of the word ?? */
	{
#ifdef LS1DEBUG
			FNX_PRINTF(" %02x %c \n",(*elp)->l_ch,(*elp)->l_ch);
#endif   
		
		++(*elp);               
	}
#ifdef LS1DEBUG
		FNX_PRINTF (" %02x %c \n",(*elp)->l_ch,(*elp)->l_ch);
#endif
	
	(*rlp) = (*elp);
	
#ifdef LS1DEBUG
		FNX_PRINTF("found the end of word ");
		FNX_PRINTF("left=%u  right=%u\n",llp,*rlp);
#endif
}

/* ******************************************************************
 *  Function Name:  
 *      ls_task_remove_case()
 *
 *  Description:           
 *      this function removes the case from the current word
 *
 *  Arguments:                                                      
 *      LETTER *llp     the left bounding pointer of the word
 *      LETTER *rlp     The right bounding pointer of the word
 *
 *  Return Value:                                   
 *      a value that indicates what action to take next
 *      possible values are
 *      KEEP_SEARCHING  Tells ls_task_to continue the search for a possible
 *                      text type
 *      LS_TASK_LOOP    Return to the top of the while loop on ls_task_main
 *      SPELL_WORD      Spell the entire word
 *      FINISHED_WORD   The word was spoken. Read the next word from the pipe
 *
 *  Comments:
 *
 * *****************************************************************/
void ls_task_remove_case(LETTER *llp, LETTER *rlp)
{       
	while (llp != rlp) 
	{
		llp->l_ch = ls_lower[(llp->l_ch)];
		++llp;
	}
}

/* ******************************************************************
 *      Function Name:
 *              ls_util_is_dot()
 *
 *      Description:      
 *      		checks to see if the character in the current item is as dot '.'
 * 				Return TRUE if the character in the
 * 				current item is an ASCII ".". Return FALSE if it
 * 				is anything else. This is used in  few places to decide
 * 				if we are in an abbreviation context.
 *
 *      Arguments:                                         
 *              PLTS_T pLts_t
 *
 *      Return Value:
 *              TRUE if the current iten is a dot '.'
 *              False otherwise
 *
 *      Comments:          
 *              this function uses the global citem variable
 *              this function is used in a few places to decide if this is 
 *              an abbreviation context
 *
 * *****************************************************************/
int ls_util_is_dot(PLTS_T pLts_t)
{
	if (pLts_t->citem.i_word[0] == ((PFASCII<<PSFONT)|'.'))
	{
		return (TRUE);
	}
	return (FALSE);
}


/* ******************************************************************
 *      Function Name:  ls_util_is_white()
 *
 *      Description:
 * 			Return TRUE if the ITEM pointed to
 * 			by "ip" is some kind of white space. Yes,
 * 			this probably should be done with a bit
 * 			in the type. The HT and the VT
 * 			are not considered to be white space,
 * 			because they become "," and flush
 * 			phonemes. Essentially "white" means
 * 			"ls_task_do_right_punct would send a WBOUND".
 *
 *      Arguments:
 *			ITEM *ip
 *      Return Value:
 *          int
 *
 *      Comments:
 *           
 * *****************************************************************/
int ls_util_is_white(ITEM *ip)
{
	  int   c;

	if ((ip->i_word[0]&PFONT) == (PFASCII<<PSFONT)) 
	{
		c = ip->i_word[0] & PVALUE;
		if (c==' ' || c==0xA0 || c==LF || c==CR || c==FF)
			return (TRUE);
	}
	return (FALSE);
}

/* ******************************************************************
 *      Function Name:  ls_util_read_item()
 *
 *      Description:
 * 			Arrange that the "citem" external
 * 			variable contains the next item of input
 * 			from the front end. Understands how
 * 			lookahead works.
 *
 *      Arguments:
 *			LPTTS_HANDLE_T phTTS	Text-to-speech handle
 *                                              
 *      Return Value:
 *          void
 *
 *      Comments:
 *              
 * *****************************************************************/
void ls_util_read_item(LPTTS_HANDLE_T phTTS)
{
	int   i;    
	PLTS_T  pLts_t;
	pLts_t = phTTS->pLTSThreadData;

	if (pLts_t->nitem.i_nword == 0)
		ls_util_next_item(phTTS);
	pLts_t->citem.i_nword =pLts_t->nitem.i_nword;
	pLts_t->nitem.i_nword = 0;
	for (i=0; i<4; ++i)
		pLts_t->citem.i_word[i] = pLts_t->nitem.i_word[i];
}

/* ******************************************************************
 *      Function Name:  ls_util_next_item()
 *
 *      Description:
 * 			Read an item from the input stream,   and store it into the "nitem"
 * 			external variable. Used to peek ahead at the input, and called by
 * 			"ls_util_read_item" to actually do reading.
 *
 * 			Now we also handle the lts flushes and synchronous lts command here ...
 *
 *      Arguments:
 *			LPTTS_HANDLE_T phTTS	Text-to-speech handle
 *                                              
 *      Return Value:
 *          void
 *
 *      Comments:
 *             
 * *****************************************************************/
void ls_util_next_item(LPTTS_HANDLE_T phTTS)
{
	PLTS_T  pLts_t=phTTS->pLTSThreadData;

	if (pLts_t->cur_read_pos>=pLts_t->cur_input_pos && 
		!((pLts_t->cur_read_pos==pLts_t->cur_input_pos) && (pLts_t->cur_index<pLts_t->num_indexes)))
	{
		pLts_t->nitem.i_nword = 0;
		pLts_t->nitem.i_word[0]=0;
	}
	else
	{
		if (pLts_t->cur_index!=-1 && pLts_t->cur_index<pLts_t->num_indexes && 
			pLts_t->cur_read_pos==pLts_t->indexes[pLts_t->cur_index].pos)
		{
			pLts_t->nitem.i_nword=3;
			pLts_t->nitem.i_word[0]=(pLts_t->indexes[pLts_t->cur_index].data[0]& ~PNEXTRA);
			pLts_t->nitem.i_word[1]=pLts_t->indexes[pLts_t->cur_index].data[1];
			pLts_t->nitem.i_word[2]=pLts_t->indexes[pLts_t->cur_index].data[2];
			pLts_t->cur_index++;
		}
		else
		{
			pLts_t->nitem.i_nword = 1;
			pLts_t->nitem.i_word[0]=pLts_t->input_array[pLts_t->cur_read_pos++];
		}
	}
}


/* ******************************************************************
 *      Function Name:  ls_util_is_aword
 *
 *      Description:
 *      	This function check the data between the llp and rlp pointers
 *          for a legal word string with only alphabet
 *
 *      Arguments:
 *          LETTER *llp     INPUT - pointer to the beginning of the word
 *          LETTER *rlp     INPUT - pointer to the EOS at the end of the word
 *                                              
 *      Return Value:
 *          TRUE   is an alphabet word with vowel
 *          FALSE  not an alphabet word or word without vowel
 *
 *      Comments:
 *          rlp must be greater than or equal to llp
 * *****************************************************************/
int ls_util_is_aword(LETTER *llp, LETTER *rlp)
{
	int flag=FALSE;
	       
	if (llp >= rlp) return(FALSE);
	while (llp!=rlp)
	{
		if (!(IS_ALPHA(llp->l_ch))) return(FALSE);
		if (IS_VOWEL(llp->l_ch)) flag=TRUE;
		++llp;
	}
	return(flag);      
}

/* ******************************************************************
 *      Function Name:
 *              ls_util_is_clause()
 *
 *      Description:      
 *
 *      Arguments:                                         
 *              LPTTS_HANDLE_T phTTS
 *
 *      Return Value:
 *              TRUE
 *              False
 *
 *      Comments:
 *
 * *****************************************************************/
int ls_util_is_clause(LPTTS_HANDLE_T phTTS)
{
	PLTS_T	pLts_t=phTTS->pLTSThreadData;
#ifdef NEW_MULTI_LANG_ARCH
	if ((phTTS->ph_funcs.char_types[pLts_t->citem.i_word[0]&PVALUE])&MARK_clause)
#else
	if ((char_types[pLts_t->citem.i_word[0]&PVALUE])&MARK_clause)
#endif
	{
		return (TRUE);
	}
	return (FALSE);
}

/* ******************************************************************
 *      Function Name:             
 *              ls_util_is_name()
 *
 *      Description:       
 *              this function decides weather or not the word is a name
 *
 *      Arguments:                                                 
 *				LPTTS_HANDLE_T phTTS	Text-to-speech handle
 *              LETTER *llp				The left bounding pointer to the word
 *              LETTER *rlp				The right bounding pointer to the word
 *
 *      Return Value:                                             
 *              TRUE if the word is a name
 *              FALSE otherwise
 *
 *      Comments:          
 *              this function returns FALSE for non acna
 *
 * *****************************************************************/
/* for non acna, everything is not a name */    
int ls_util_is_name(LPTTS_HANDLE_T phTTS, LETTER *llp, LETTER *rlp)
{
#if defined ACNA && !defined USE_NAND && !defined USE_464
	PLTS_T  pLts_t;
	PKSD_T  pKsd_t;

	pLts_t = phTTS->pLTSThreadData;
	pKsd_t = phTTS->pKernelShareData;   
	if(pKsd_t->pronflag & PRON_ACNA_NAME)
		return(TRUE);
	if (pKsd_t->last_preamble_command==3)
	{
		pKsd_t->pronflag |= PRON_ACNA_NAME;
		return(TRUE);
	}
	if((pKsd_t->modeflag & MODE_NAME) == 0)
		return(TRUE);
#ifdef NEW_LTS
	if(pLts_t->cur_word_index == 0)
#else
	if(pLts_t->fc_index == 0)
#endif
		return(FALSE);
	if((*llp).l_ch < 64 || (*llp).l_ch > 97 )/*first character upper??*/
		return(FALSE);
	for(llp++;llp<rlp;llp++)
		if( (*llp).l_ch  >122 ||  (*llp).l_ch <97) /*the rest lower*/
			return(FALSE);
	pKsd_t->pronflag |= PRON_ACNA_NAME;
		return(TRUE);
#else
	return(FALSE);
#endif
}

/* ******************************************************************
 *      Function Name:  
 *          ls_util_is_year()
 *      Description:
 *
 *		 	Check to see if the digit group
 * 			enclosed by "llp" and "rlp" looks enough
 * 			like a year to be spoken by "ls_proc_do_4_digits". Years
 * 			are 4 characters long, all digits. The first character
 * 			must not be a zero ("0100" isn't a year). The middle two
 * 			digits must not both be zero ("2000" is best read as a
 * 			number, and "2002" sounds stupid as "twenty zero two").
 * 			Return TRUE or FALSE.
 *
 *      Arguments:
 *          LETTER *llp      	INPUT - pointer to the beginning of the word
 *          LETTER *rlp        	INPUT - pointer to the EOS at the end of the word
 *
 *      Return Value:
 			int
 *
 *      Comments:
 *
 * *****************************************************************/
int ls_util_is_year(LETTER *llp, LETTER *rlp)
{
	LETTER        *tlp1;
	int   ndig;

	ndig = 0;                               /* Count digits, check. */
	tlp1 = llp;                             /* for all digits.      */
	while (tlp1 != rlp) 
	{
		if (!IS_DIGIT(tlp1->l_ch))
			return (FALSE);
		++ndig;
		++tlp1;
	}
	/* MGS 07/22/97 BATS #412 */
	if ((rlp-1)->l_ch==0xBC || (rlp-1)->l_ch==0xBD) /* don't let years have 1/2 or 1/4 in them */
		return (FALSE);
	if (ndig != 4)                          /* Must be 4 digits.    */
		return (FALSE);
	if (llp->l_ch == '0')                   /* No initial "0", no   */
		return (FALSE);                 /* imbedded "00" pair.  */
	if ((llp+1)->l_ch=='0' && (llp+2)->l_ch=='0')
		return (FALSE);
	return (TRUE);
}

/* ******************************************************************
 *      Function Name:
 *			ls_util_copyword()
 *
 *      Description:
 * 			This routine copies a word,
 * 			starting at the beginning and ending at the
 * 			EOS at the end of the word. It is used when lookahead
 * 			has required that the next word in the input stream be
 * 			considered, before a decision can be made on how
 * 			a chunk of text is spoken.
 *
 *      Arguments:
 *			LETTER        *tlp
 * 			LETTER        *flp
 *
 *      Return Value:    
 *
 *      Comments:
 *
 * *****************************************************************/
void ls_util_copyword(LETTER *tlp, LETTER *flp)
{
	while (flp->l_ch != EOS) 
	{
		tlp->l_ch = flp->l_ch;
		++tlp;
		++flp;
	}
	tlp->l_ch = EOS;
	// tlp->l_ip = NULL;
}


/* ******************************************************************
 *  Function Name:
 *      ls_task_parse_number() 
 *
 *  Description:
 *		Scan a number. The "llp" is where
 * 		you start. The "rlp" is as far as you can go.
 * 		The "np" points to a NUM structure that gets filled
 * 		in. Return the right hand end of the scanned off
 * 		characters. This routine understands about the two
 * 		multinational characters "1/2" and "1/4". They are
 * 		part of the integer part of the number, and
 * 		block the scanning of additional stuff.
 *
 *
 *  Arguments:	LPTTS_HANDLE_T phTTS
 *				LETTER *llp
 *				LETTER *rlp
 *				NUM *np
 *
 *  Return Value: LETTER  *
 *
 *  Comments:
 *
 * *****************************************************************/

LETTER  *ls_task_parse_number(LPTTS_HANDLE_T phTTS,LETTER *llp, LETTER *rlp, NUM *np)
{
	LETTER  *tlp1;
	LETTER  *tlp2;
	int     ncbs;   
	int break_flag;
	PLTS_T  pLts_t;
	PKSD_T  pKsd_t;

	pLts_t = phTTS->pLTSThreadData;
	pKsd_t = phTTS->pKernelShareData;   

	np->n_ilp = NULL;                       /* Null scan. */
	np->n_flp = NULL;
	np->n_elp = NULL;
	tlp1 = llp;
	if (tlp1 != rlp
	&& (tlp1->l_ch == 0xBC                  /* 1/4 */
	||  tlp1->l_ch == 0xBD                  /* 1/2 */
	||  IS_DIGIT(tlp1->l_ch))) 
	{
		np->n_ilp = tlp1;
		while (tlp1 != rlp) 
		{
			/* 1/2 and 1/4. */
			if (tlp1->l_ch==0xBC || tlp1->l_ch==0xBD) 
			{
				++tlp1;
				np->n_irp = tlp1;
				return (tlp1);
			}
			/* Comma (period if this is MODE_EUROPE).*/
			if (tlp1->l_ch == pLts_t->schar) 
			{
				tlp2 = tlp1;
				ncbs = 3;
				break_flag = 0;
				while (ncbs-- && tlp2!=llp) 
				{
					--tlp2;
					if (tlp2->l_ch == pLts_t->schar)
                    {						
						break_flag = 1;
						break;
				    }
				}    
				if (break_flag)
				   break;
				if (tlp2!=llp && (tlp2-1)->l_ch!=pLts_t->schar)
					break;
				tlp2 = tlp1+1;
				ncbs = 3;
				while (ncbs--) 
				{
					if (tlp2==rlp || !IS_DIGIT(tlp2->l_ch))
					{
					   break_flag = 1;
					   break;
					}	
					++tlp2;
				}
				
				if (break_flag)
				   break;
				   
				/*
				 * The normal DECtalk code does not
				 * make this check; instead, it implemented
				 * the exact rules of the DECtalk I. Peter
				 * Stevens at Kurzweil thought that this extra
				 * check was appropriate, and I tend to
				 * agree with him. We should probably make
				 * this change in all DECtalk code.
				 */
				/* Note from EAB-I have looked at this and 
				 * can't figure out how it makes the dectalk
				 * do anything different, but for chicken 
				 * soup reasons I'm leaving it in. 
				 */     

				if (tlp2!=rlp && IS_DIGIT(tlp2->l_ch))
					break;
				++tlp1;
				continue;
			}
			if (IS_DIGIT(tlp1->l_ch)) 
			{
				++tlp1;
				continue;
			}
			break;
		}
		np->n_irp = tlp1;
	}
	if (tlp1!=rlp && tlp1->l_ch==pLts_t->fchar) 
	{   /* Fraction             */
		np->n_flp = tlp1;
		++tlp1;
		while (tlp1!=rlp && IS_DIGIT(tlp1->l_ch))
			++tlp1;
		np->n_frp = tlp1;
	}
	if (tlp1!=rlp && tlp1->l_ch=='e' && (pKsd_t->modeflag & MODE_MATH)) 
	{        /* Exponant.            */
		tlp2 = tlp1;
		++tlp1;
		if ( tlp1!=rlp && (tlp1->l_ch=='+' || tlp1->l_ch=='-'))
			++tlp1;
		if (tlp1!=rlp && IS_DIGIT(tlp1->l_ch)) 
		{
			np->n_elp = tlp2;
			++tlp1;
			while (tlp1!=rlp && IS_DIGIT(tlp1->l_ch))
				++tlp1;
			np->n_erp = tlp1;
		}
	}
	return (tlp1);
}

/* ******************************************************************
 *  Function Name:  
 *      ls_task_lookahead_readword()
 *
 *  Description:        
 *      this function reads a word in from the pipe and stores it in
 *      an array of LETTER nodes.  Any index marks are placed in
 *      PHONE nodes and attached to the LETTER nodes.
 *
 * 		Read in a word. Store the letters, and the
 * 		associated index marks, into the array of LETTER
 * 		nodes passed as an argument. Any index marks found
 * 		during the read are packed into PHONE nodes and
 * 		attached to the LETTER nodes. This may not be very
 * 		easy to understand if you don't have the big
 * 		state machine flow in the DECtalk III notebook.
 *
 *  Arguments:                                           
 *      LPTTS_HANDLE_T phTTS    pointer to the instance specific stuff
 *      LETTER word[]			The array of LETTER nodes to store the word in
 *
 *  Return Value:                                     
 *      void
 *
 *  Comments:
 *      the maximum word read is NGWORD-1
 *
 * *****************************************************************/
void ls_task_lookahead_readword(LPTTS_HANDLE_T phTTS,LETTER word[])
{
	LETTER        *lp1;
	LETTER        *lp2;
	int   ksf=0;
	int   c=0;
	int pos=0;
	int second_time=0;
	PLTS_T  pLts_t;
	PKSD_T  pKsd_t;

	pLts_t = phTTS->pLTSThreadData;
	pKsd_t = phTTS->pKernelShareData;   
	
/*
 *  start with no flags for this word ...
 */

	lp1 = &word[0];                         /* Current location     */
	lp2 = &word[0];                         /* Rightmost location   */
	ksf = FALSE;                            /* Nothing kept         */
        
/* JDB: simple fix to avoid the goto's that used to be here */
/* loop: */
	pos=pLts_t->cur_read_pos;
	while(phTTS->ph_funcs.char_types[pLts_t->input_array[pos]] & (MARK_space))
		pos++;
	while (pos<=pLts_t->cur_input_pos && !(phTTS->ph_funcs.parser_char_types[pLts_t->input_array[pos]] & (TYPE_white|TYPE_clause))) 
	{
		lp1->l_ch = pLts_t->input_array[pos];
		//	lp1->l_ip = NULL;
		++lp1;
		++lp2;
		pos++;
	}

	lp1->l_ch = EOS;
	// lp1->l_ip = NULL; 
}

#endif
