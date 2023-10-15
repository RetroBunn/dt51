/* ********************************************************************
 *								Copyright ©
 *    Copyright © 2002 Fonix Corporation. All rights reserved.
 *    Copyright © 2000-2001 Force Computers Inc., a Solectron company. All rights reserved.
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
 * ************************************************************************* 
 * Comments
 * install usa character set tables ...
 * rev	who		date		description
 * ------------------------------------------------------------------
 * 00?	GL		12/12/1996	need to change the usa_init() for local language.
 * 001	GL		04/21/1997	BATS#357  Add the code for __osf__ build 
 * 002  DR		09/30/1997	UK BUILD: added UK STUFF
 * 003	MFG		06/19/1998	Made changed to include latin american 
 * 004  ETT		10/05/1998  Added Linux code.
 * 005	MGS		04/13/2000  Changes for integrated phoneme set 
 * 006  NAL     05/23/2000  Added function prototype and changed usa_init() type from int to
 *                          void(warning removal)
 * 007	CHJ		07/20/2000	French added
 * 008 	CAB		10/16/00	Changed copyright info
 * 009	MGS		03/27/2001	Fix compiler warning
 * 010	CAB		03/28/2001	Updated copyright info
 * 011	MGS		05/09/2001	Some VxWorks porting BATS#972
 * 012	MFG		05/29/2001	Included dectalkf.h
 * 013	MGS		06/19/2001	Solaris Port BATS#972
 * 014	MGS		04/11/2002	ARM7 port
 * 015	CAB		04/26/2002	Removed warnings by typecast
 */

#include "port.h"
#include "dectalkf.h"

//moved to port.h for each platform - mlt
//#if defined _UNIX_LIKE_
//#include <stdlib.h>
//#endif

//moved to port.h for each platform - mlt
//#if defined ARM7 && !defined OS_PALM
//#include "stdlib.h"
//#include "string.h"
//#endif


#if defined MSDOS
#ifdef SPANISH_SP
#include "spa_def.h"
#include "spa_type.tab"
#include "spa_phon.tab"
#include "spa_err.tab"

#endif // SPANISH_SP

#ifdef SPANISH_LA
#include "la_def.h"
#include "la_type.tab"
#include "la_phon.tab"
#include "la_err.tab"
#endif

#ifdef ITALIAN
#include "it_def.h"
#include "it_type.tab"
#include "it_phon.tab"
#include "it_err.tab"
#endif

#ifdef JAPANESE
#include "jp_def.h"
#include "jp_type.tab"
#include "jp_phon.tab"
#include "jp_err.tab"
#endif

#ifdef HEBREW
#include "hb_def.h"
#include "hb_type.tab"
#include "hb_phon.tab"
#include "hb_err.tab"
#endif

#ifdef CHINESE
#include "ch_def.h"
#include "ch_type.tab"
#include "ch_phon.tab"
#include "ch_err.tab"
#endif

#ifdef KOREAN
#include "kr_def.h"
#include "kr_type.tab"
#include "kr_phon.tab"
#include "kr_err.tab"
#endif

#ifdef GERMAN
#include "ger_def.h"
#include "ger_type.tab"
#include "ger_phon.tab"
#include "ger_err.tab"
#endif

#ifdef ENGLISH_US
#include "usa_def.h"

/*
 *  include the tables here ... this allows me to determine
 *  the size and types without a lot of work ...
 */

#include        "usa_type.tab"
#include        "usa_phon.tab"
#include        "usa_err.tab"
#endif

#ifdef ENGLISH_UK
#include		"uk_def.h"
#include        "uk_type.tab"
#include        "uk_phon.tab"
#include        "uk_err.tab"
#endif

#ifdef FRENCH
#include		"fr_def.h"
#include        "fr_type.tab"
#include        "fr_phon.tab"
#include        "fr_err.tab"
#endif

#else // MSDOS
#include "spa_def.h"
#include "spa_type.tab"
#include "spa_phon.tab"
#include "spa_err.tab"
#include "la_def.h"
#include "la_type.tab"
#include "la_phon.tab"
#include "la_err.tab"
#include "it_def.h"
#include "it_type.tab" 
#include "it_phon.tab"
#include "it_err.tab"
#include "ger_def.h"
#include "ger_type.tab"
#include "ger_phon.tab"
#include "ger_err.tab"
#include "usa_def.h"
#include "usa_type.tab"
#include "usa_phon.tab"
#include "usa_err.tab"
#include "uk_def.h"
#include "uk_type.tab"
#include "uk_phon.tab"
#include "uk_err.tab"
#include "fr_def.h"
#include "fr_type.tab"
#include "fr_phon.tab"
#include "fr_err.tab"
#include "jp_def.h"		//needs a gap between includes for TLCS900(Besta) compiler

#include "jp_type.tab"
#include "jp_phon.tab"
#include "jp_err.tab"
#include "ch_def.h"
#include "ch_type.tab"
#include "ch_phon.tab"
#include "ch_err.tab"
#include "kr_type.tab"
#include "kr_phon.tab"
#include "kr_err.tab"
#include "hb_type.tab"
#include "hb_phon.tab"
#include "hb_err.tab"
CONSTARRAY unsigned char language_prefixes[] = {
	'u', 's',
	'u', 'k',
	's', 'p',
	'g', 'r',
	'l', 'a',
	'f', 'r',
	'i', 't',
	'j', 'p',
	'k', 'r',
	'c', 'h',
	'h', 'e'
};

CONSTARRAY int language_size=sizeof(language_prefixes);

const unsigned char *CONSTCONST arpabet_arrays[]= {
	usa_arpa,
	uk_arpa,
	spanish_arpa,
	german_arpa,
	la_arpa,
	french_arpa,
	it_arpa, 
	jp_arpa,
	kr_arpa,
	ch_arpa,
	he_arpa
};

CONSTARRAY unsigned int arpabet_sizes[] = {
	sizeof(usa_arpa),
	sizeof(uk_arpa),
	sizeof(spanish_arpa),
	sizeof(german_arpa),
	sizeof(la_arpa),
	sizeof(french_arpa),
	sizeof(it_arpa),
	sizeof(jp_arpa),
	sizeof(kr_arpa),
	sizeof(ch_arpa),
	sizeof(he_arpa)
};
CONSTARRAY unsigned int arpabet_lang_flags[] = {
	LANG_english,
	LANG_british,
	LANG_spanish,
	LANG_german,
	LANG_latin_american,
	LANG_french,		
	LANG_italian,
	LANG_japanese,
	LANG_chinese,
	LANG_korean,
	LANG_hebrew


};

CONSTARRAY unsigned int arpabet_lang_fonts[] = {
	PFUSA,
	PFUK,
	PFSP,
	PFGR,
	PFLA,
	PFFR,
	PFIT,
	PFJP,
	PFCH,
	PFKR,
	PFHE
};


CONSTARRAY unsigned int lang_fonts_shift[] = {
	PFUSA,
	PFFR,
	PFGR,
	PFSP,
	PFJP,
	PFUK,
	PFLA,
	PFIT,
	PFKR,
	PFCH,
	PFHE
};



#endif // MSDOS

/* MVP : The below variable "nlt" is now made local to usa_init function and
 * dynamically allocated to support multiple instances of speech object.
 */
/*struct  dtpc_language_tables nlt;*/  

/* 
 * #define USADEBUG 1
 */

#if defined _UNIX_LIKE_
extern void default_lang( PKSD_T , unsigned int, unsigned int);
#endif

void default_lang(PKSD_T, unsigned int, unsigned int); // NAL warning removal

#ifndef ALLOC_MEMORY
#ifndef EPSON_ARM7
struct dtpc_language_tables nlt;
#endif
#endif

/* ******************************************************************
 *  Function: usa_init()
 *                               
 *  Description: 
 *
 *	Arguments:
 *		PKSD_T pKsd_t
 *
 *	Return Value:
 *		void
 *
 *	Comments:
 * *****************************************************************/
void usa_init(PKSD_T pKsd_t)
{
	volatile struct dtpc_language_tables _far *lt;
	int dont_link=0;
	
	struct  dtpc_language_tables *pnlt;
	/* nlt is allocated here ,It will be made free in DeleteTextToSpeechObject routine
	* in API sub-system.
	*/
	
#ifdef EPSON_ARM7	
	pnlt=&pKsd_t->k_nlt;
#else
#ifndef ALLOC_MEMORY
	pnlt=&nlt;
#else
	if( (pnlt = (struct dtpc_language_tables*)FNX_MALLOC(sizeof(struct dtpc_language_tables)))== NULL)
    {
		//MessageBox(NULL,"Error allocating dtpc_language_tables structure",  Error",MB_OK);
		return;// (MMSYSERR_NOMEM);
	}
#endif // ALLOC_MEMORY
#endif
	
	/*
	*  fill structure ...
	*/
	
#ifdef USADEBUG
	f_fprintf("In usa init\n");
#endif
	
	lt = pKsd_t->loaded_languages;
	if(lt != NULL_LT)
	{
		while (lt!=NULL_LT)
		{
			if (lt->lang_id==pKsd_t->lang_curr)
			{
				pnlt=lt;
				dont_link=1;
				break;
			}
			lt=lt->link;
		}
	}
	
	if (dont_link==0)
	{
		pnlt->link = NULL_LT;
		if (pKsd_t->lang_curr==LANG_english)
		{
			pnlt->lang_id = LANG_english;
			// CAB Removed warnings by typecast
			pnlt->lang_ascky = (unsigned char *)usa_ascky;
			pnlt->lang_ascky_size = sizeof(usa_ascky);
			// CAB Removed warnings by typecast
			pnlt->lang_reverse_ascky = (unsigned int *)usa_ascky_rev;
			pnlt->lang_arpabet = (unsigned char *)usa_arpa;
			pnlt->lang_arpa_size = sizeof(usa_arpa);
			pnlt->lang_arpa_case = FALSE;
			pnlt->lang_typing =  (unsigned char **)usa_type;
			pnlt->lang_error = (unsigned char **)usa_error;
		}
		
		if (pKsd_t->lang_curr==LANG_british)
		{
			pnlt->lang_id = LANG_british;
			// CAB Removed warnings by typecast
			pnlt->lang_ascky = (unsigned char *)uk_ascky;
			pnlt->lang_ascky_size = sizeof(uk_ascky);
			// CAB Removed warnings by typecast
			pnlt->lang_reverse_ascky = (unsigned int *)uk_ascky_rev;
			pnlt->lang_arpabet = (unsigned char *)uk_arpa;
			pnlt->lang_arpa_size = sizeof(uk_arpa);
			pnlt->lang_arpa_case = FALSE;
			pnlt->lang_typing = (unsigned char **)uk_type;
			pnlt->lang_error = (unsigned char **)uk_error;
		}
		
		if (pKsd_t->lang_curr==LANG_italian)
		{
			pnlt->lang_id = LANG_italian;
			// CAB Removed warnings by typecast
			pnlt->lang_ascky = (unsigned char *)(it_ascky);
			pnlt->lang_ascky_size = sizeof(it_ascky);
			// CAB Removed warnings by typecast
			pnlt->lang_reverse_ascky = (unsigned int *)it_ascky_rev;
			pnlt->lang_arpabet = (unsigned char *)it_arpa;
			pnlt->lang_arpa_size = sizeof(it_arpa);
			pnlt->lang_arpa_case = FALSE;
			pnlt->lang_typing = (unsigned char **)it_type;
			pnlt->lang_error = (unsigned char **)it_error;
		}
		if (pKsd_t->lang_curr==LANG_latin_american)
		{
			pnlt->lang_id = LANG_latin_american;
			// CAB Removed warnings by typecast
			pnlt->lang_ascky = (unsigned char *)la_ascky;
			pnlt->lang_ascky_size = sizeof(la_ascky);
			// CAB Removed warnings by typecast
			pnlt->lang_reverse_ascky = (unsigned int *)la_ascky_rev;
			pnlt->lang_arpabet = (unsigned char *)la_arpa;
			pnlt->lang_arpa_size = sizeof(la_arpa);
			pnlt->lang_arpa_case = FALSE;
			pnlt->lang_typing = (unsigned char **)la_type;
			pnlt->lang_error = (unsigned char **)la_error;
		}
		if (pKsd_t->lang_curr==LANG_spanish)
		{
			pnlt->lang_id = LANG_spanish;
			// CAB Removed warnings by typecast
			pnlt->lang_ascky = (unsigned char *)spanish_ascky;
			pnlt->lang_ascky_size = sizeof(spanish_ascky);
			// CAB Removed warnings by typecast
			pnlt->lang_reverse_ascky = (unsigned int *)spanish_ascky_rev;
			pnlt->lang_arpabet = (unsigned char *)spanish_arpa;
			pnlt->lang_arpa_size = sizeof(spanish_arpa);
			pnlt->lang_arpa_case = FALSE;
			pnlt->lang_typing = (unsigned char **)spanish_type;
			pnlt->lang_error = (unsigned char **)spanish_error;
		}
		
		if (pKsd_t->lang_curr==LANG_german)
		{
			pnlt->lang_id = LANG_german;
			// CAB Removed warnings by typecast
			pnlt->lang_ascky = (unsigned char *)german_ascky;
			pnlt->lang_ascky_size = sizeof(german_ascky);
			// CAB Removed warnings by typecast
			pnlt->lang_reverse_ascky = (unsigned int *)german_ascky_rev;
			pnlt->lang_arpabet = (unsigned char *)german_arpa;
			pnlt->lang_arpa_size = sizeof(german_arpa);
			pnlt->lang_arpa_case = FALSE;
			pnlt->lang_typing = (unsigned char **)german_type;
			pnlt->lang_error = (unsigned char **)german_error;
		}
		
		if (pKsd_t->lang_curr==LANG_french)
		{
			pnlt->lang_id = LANG_french;
			// CAB Removed warnings by typecast
			pnlt->lang_ascky = (unsigned char *)french_ascky;
			pnlt->lang_ascky_size = sizeof(french_ascky);
			// CAB Removed warnings by typecast
			pnlt->lang_reverse_ascky = (unsigned int *)french_ascky_rev;
			pnlt->lang_arpabet = (unsigned char *)french_arpa;
			pnlt->lang_arpa_size = sizeof(french_arpa);
			pnlt->lang_arpa_case = FALSE;
			pnlt->lang_typing = (unsigned char **)french_type;
			pnlt->lang_error = (unsigned char **)french_error;
		}
		
		if (pKsd_t->lang_curr==LANG_chinese)
		{
			pnlt->lang_id = LANG_chinese;
			// CAB Removed warnings by typecast
			pnlt->lang_ascky = (unsigned char *)ch_ascky;
			pnlt->lang_ascky_size = sizeof(ch_ascky);
			// CAB Removed warnings by typecast
			pnlt->lang_reverse_ascky = (unsigned int *)ch_ascky_rev;
			pnlt->lang_arpabet = (unsigned char *)ch_arpa;
			pnlt->lang_arpa_size = sizeof(ch_arpa);
			pnlt->lang_arpa_case = FALSE;
			pnlt->lang_typing = (unsigned char **)ch_type;
			pnlt->lang_error = (unsigned char **)ch_error;
		}
		
		if (pKsd_t->lang_curr==LANG_korean)
		{
			pnlt->lang_id = LANG_korean;
			// CAB Removed warnings by typecast
			pnlt->lang_ascky = (unsigned char *)kr_ascky;
			pnlt->lang_ascky_size = sizeof(kr_ascky);
			// CAB Removed warnings by typecast
			pnlt->lang_reverse_ascky = (unsigned int *)kr_ascky_rev;
			pnlt->lang_arpabet = (unsigned char *)kr_arpa;
			pnlt->lang_arpa_size = sizeof(kr_arpa);
			pnlt->lang_arpa_case = FALSE;
			pnlt->lang_typing = (unsigned char **)kr_type;
			pnlt->lang_error = (unsigned char **)kr_error;
		}
		
		if (pKsd_t->lang_curr==LANG_hebrew)
		{
			pnlt->lang_id = LANG_hebrew;
			// CAB Removed warnings by typecast
			pnlt->lang_ascky = (unsigned char *)he_ascky;
			pnlt->lang_ascky_size = sizeof(he_ascky);
			// CAB Removed warnings by typecast
			pnlt->lang_reverse_ascky = (unsigned int *)he_ascky_rev;
			pnlt->lang_arpabet = (unsigned char *)he_arpa;
			pnlt->lang_arpa_size = sizeof(he_arpa);
			pnlt->lang_arpa_case = FALSE;
			pnlt->lang_typing =  (unsigned char **)he_type;
			pnlt->lang_error = (unsigned char **)he_error;
		}
		
		if (pKsd_t->lang_curr==LANG_japanese)
		{
			pnlt->lang_id = LANG_japanese;
			// CAB Removed warnings by typecast
			pnlt->lang_ascky = (unsigned char *)jp_ascky;
			pnlt->lang_ascky_size = sizeof(jp_ascky);
			// CAB Removed warnings by typecast
			pnlt->lang_reverse_ascky = (unsigned int *)jp_ascky_rev;
			pnlt->lang_arpabet = (unsigned char *)jp_arpa;
			pnlt->lang_arpa_size = sizeof(jp_arpa);
			pnlt->lang_arpa_case = FALSE;
			pnlt->lang_typing = (unsigned char **)jp_type;
			pnlt->lang_error = (unsigned char **)jp_error;
		}
	}
	/* GL 12/12/1996  set the language table */
	pKsd_t->ascky = pnlt->lang_ascky;
	pKsd_t->ascky_size = pnlt->lang_ascky_size;
	pKsd_t->reverse_ascky = pnlt->lang_reverse_ascky;
	pKsd_t->arpabet = pnlt->lang_arpabet;
	pKsd_t->arpa_size = pnlt->lang_arpa_size;
	pKsd_t->arpa_case = pnlt->lang_arpa_case;
	pKsd_t->typing_table = pnlt->lang_typing;
	pKsd_t->error_table = pnlt->lang_error;
	
	
	
	/*
	*  thread on chain ...
	*/
	if (dont_link==0)
	{
		lt = pKsd_t->loaded_languages;
		if(lt == NULL_LT)
			pKsd_t->loaded_languages = pnlt;
		else
		{
			while((*lt).link != NULL_LT)
				lt = (*lt).link;
			(*lt).link = pnlt;
		}
	}
	/*
	*  Install the language bit flag ...
	*/
	
	default_lang(pKsd_t,pKsd_t->lang_curr,LANG_tables_ready);
}
