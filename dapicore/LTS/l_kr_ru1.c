/*C_HEADER_FILE****************************************************************
FILE			:	l_kr_ru1.c
DESC			:	Korean functions to process romaji
TABS			:	4
OWNER			:	
DATE CREATED:	

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
#include "ls_def.h"
#include "ls_rule.h"
#include "KoreanIntonation.h"


/*FUNCTION_HEADER**********************
 * NAME:	;Korean_ProcessRomaji
 * DESC: 	Parse input into phrases, words, syllables and convert to phonemes.
			Apply intonation processing and then speak
 * IN:		phTTS
 * OUT:		none
 * RETURN:	1 on success, 0 on failure
 * NOTES:	It is expected that the input text has already been converted
			to Romaji by the time it gets here.
 *END_HEADER***************************/
int Korean_ProcessRomaji(LPTTS_HANDLE_T phTTS, char *sRomaji)
{
	KOREAN_PHRASE *pKrPhrases;

	if( sRomaji == NULL || *sRomaji == 0x00 )
		return 0;

	if( (pKrPhrases = KrParsePhrase(phTTS, sRomaji)) == NULL )
		return 0;

	KrApplyIntonation(phTTS, pKrPhrases);

	KrFreePhrases(&pKrPhrases);

	return 1;

}

/*FUNCTION_HEADER**********************
 * NAME:	;ls_rule_korean_lts
 * DESC: 	This is where it all begins for Korean romaji processing
 * IN:		phTTS
 * OUT:		none
 * RETURN:	none
 * NOTES:	It is expected that the input text has already been converted
			to Romaji by the time it gets here.
 *END_HEADER***************************/
void ls_rule_korean_lts(LPTTS_HANDLE_T phTTS)
{
	PLTS_T pLts_t=phTTS->pLTSThreadData;

	Korean_ProcessRomaji(phTTS, pLts_t->input_array);
	return;

}
