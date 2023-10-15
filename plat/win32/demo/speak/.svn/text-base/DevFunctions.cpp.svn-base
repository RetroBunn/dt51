/*C_HEADER_FILE****************************************************************
FILE			:	DevFunctions.cpp
DESC			:	
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

#include "speak.h"
#include "CodePageConv.h"

/*FUNCTION_HEADER**********************
 * NAME:	;TranslateJapaneseWordList
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void TranslateJapaneseWordList(LPTTS_HANDLE_T *phTTS, int iLang, char *sWordList, char *sTranslationFile)
{
	char
		*pc,
		sKanjiRom[128],
		sKanaRom[128];
	wchar_t 
		wc = L'\n',
		*pwc,
		wsWord[128],
		wsKanji[128],
		wsKana[128],
		wsPos[128];
	int
		i=0;
	FILE 
		*fpIn, 
		*fpOut;

	if( (fpIn = fopen(sWordList, "rb")) == NULL )
		return;

	if( (fpOut = fopen(sTranslationFile, "wb")) == NULL )
	{
		fclose(fpIn);
		return;
	}

	fread(&wc, sizeof(wchar_t), 1, fpIn);				// Read unicode header
	
	wc = 0xfeff;
	fwrite(&wc, sizeof(wchar_t), 1, fpOut);				// Write unicode header to output file

	while( fgetws(wsWord, 128, fpIn) )
	{
		i++;

		if( (pwc = wcschr(wsWord, L'\n')) != NULL )		// Remove newline character
			*pwc = 0x00;

		if( (pwc = wcstok(wsWord, L";")) != NULL )		// Get the Kanji
			wcscpy(wsKanji, pwc);
		else
			wsKanji[0] = 0x00;

		if( (pwc = wcstok(NULL, L";")) != NULL )		// Get the Kana if available
			wcscpy(wsKana, pwc);
		else
			wsKana[0] = 0x00;

		if( (pwc = wcstok(NULL, L";\n")) != NULL )		// Get the POS
			wcscpy(wsPos, pwc);
		else
			wsPos[0] = 0x00;

		sKanjiRom[0] = sKanaRom[0] = 0x00;

		TextToSpeechGetRomanizedText( phTTS[iLang], wsKana, sKanaRom, 128, eUtf16 );

		if( (pc = strchr(sKanaRom, '.')) )		// Remove the trailing period
			*pc = 0x00;

		fwprintf(fpOut, L"%s;%s;%S;%s\n", wsKanji, wsKana, sKanaRom, wsPos);
	}

	fclose(fpIn);
	fclose(fpOut);
}


/*FUNCTION_HEADER**********************
 * NAME:	;CompareKanjiKanaTranslation
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void CompareKanjiKanaTranslation(LPTTS_HANDLE_T *phTTS, int iLang, char *sWordList, char *sOutFile, char *sAccentFile)
{
	char
		*pc1, *pc2,
		c = '\n',
		sTmp[] = "  ",
		sKanjiRom[128],
		sKanaRom[128],
		sKanjiRomWOAccent[128],
		sKanaRomWOAccent[128];
	wchar_t 
		wc = L'\n',
		*pwc,
		wsWord[128],
		wsKanji[128],
		wsKana[128];
	int
		i=0,
		nKanji=0,
		nKana=0,
		nTranslated=0,
		nKanjiTranslated=0,
		nKanaTranslated=0,
		nMatching=0,
		nMatchPhones=0,
		nTotal=0;
	FILE 
		*fpIn, 
		*fpOut,
		*fpAccent;	// Those with non-matching accent only

	if( (fpIn = fopen(sWordList, "rb")) == NULL )		// Open input list of Kanji and kana
		return;

	if( (fpOut = fopen(sOutFile, "wb")) == NULL )		// Open output file
	{
		fclose(fpIn);
		return;
	}

	if( (fpAccent = fopen(sAccentFile, "wb")) == NULL )		// Open output file
	{
		fclose(fpIn);
		fclose(fpOut);
		return;
	}

	fread(&wc, sizeof(wchar_t), 1, fpIn);				// Read unicode header
	
	wc = 0xfeff;
	fwrite(&wc, sizeof(wchar_t), 1, fpOut);				// Write unicode header to output file
	fwrite(&wc, sizeof(wchar_t), 1, fpAccent);			// Write unicode header to output file

	// Write a blank header that will be over-written later
	fwprintf(fpOut, L"Total Word pairs:[%06d], Kanji:[%06d], Kana:[%06d]\n"
					L"Translated:[%06d], Kanji:[%06d], Kana:[%06d]\n"
					L"Matching:[%06d], Phones Matching:[%06d]\n", 
					nTotal, nKanji, nKana, 
					nTranslated, nKanjiTranslated, nKanaTranslated,
					nMatching, nMatchPhones);

	while( fgetws(wsWord, 128, fpIn) )
	{
		i++;

		wsKanji[0] = wsKana[0] = 0x00;
		sKanjiRom[0] = sKanaRom[0] = 0x00;

		if( (pwc = wcschr(wsWord, L'\n')) != NULL )		// Remove newline character
			*pwc = 0x00;

		if( (pwc = wcstok(wsWord, L" ")) != NULL )		// Get Kanji
			wcscpy(wsKanji, pwc);

		if( (pwc = wcstok(NULL, L" \n")) != NULL )		// Get Kana
			wcscpy(wsKana, pwc);

		if( wsKanji[0] )	nKanji++;
		if( wsKana[0] )		nKana++;
		if( wsKanji[0] == NULL || wsKana[0] == 0x00 )	// Make sure we got both
			continue;

		nTotal++;

		// Translate Kanji and Kana to romaji
		//phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize( phTTS->pLTSThreadData );
		TextToSpeechGetRomanizedText( phTTS[iLang], wsKanji, sKanjiRom, 128, eUtf16 );
		
		//phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize( phTTS->pLTSThreadData );
		TextToSpeechGetRomanizedText( phTTS[iLang], wsKana, sKanaRom, 128, eUtf16 );
		
		if( sKanjiRom[0] )	nKanjiTranslated++;
		if( sKanaRom[0] )	nKanaTranslated++;

		if( sKanjiRom[0] == 0x00 || sKanaRom[0] == 0x00 )
		{
			TextToSpeechGetRomanizedText( phTTS[iLang], NULL, NULL, 0, 0 );	// Re-initialize the dictionary
			continue;
		}
		else
		{
			nTranslated++;
		}

		if( strcmp(sKanjiRom, sKanaRom) != 0 )
		{
			strcpy(sKanjiRomWOAccent, sKanjiRom);
			strcpy(sKanaRomWOAccent, sKanaRom);

			// Strip accent marks from kanji-romaji
			for( pc1 = pc2 = sKanjiRomWOAccent; pc1 && *pc1; pc1++ )
			{
				if( ('a' <= *pc1 && *pc1 <= 'z') ||
					('A' <= *pc1 && *pc1 <= 'Z') )
				{
					*pc2 = *pc1;
					pc2++;
				}
			}
			*pc2 = 0x00;

			// Strip accent marks from kana-romaji
			for( pc1 = pc2 = sKanaRomWOAccent; pc1 && *pc1; pc1++ )
			{
				if( ('a' <= *pc1 && *pc1 <= 'z') ||
					('A' <= *pc1 && *pc1 <= 'Z') )
				{
					*pc2 = *pc1;
					pc2++;
				}
			}
			*pc2 = 0x00;

			if( strcmp(sKanjiRomWOAccent, sKanaRomWOAccent) == 0 )
			{
				nMatchPhones++;
				fwprintf(fpAccent, L"%s;%S - %s;%S\n", wsKanji, sKanjiRom, wsKana, sKanaRom);

			}
			else
			{
				fwprintf(fpOut, L"%s;%S - %s;%S\n", wsKanji, sKanjiRom, wsKana, sKanaRom);
			}

		}
		else
		{
			nMatching++;
		}

	}

	fseek(fpOut, sizeof(wchar_t), SEEK_SET);
	// Write header
	fwprintf(fpOut, L"Total Word pairs:[%06d], Kanji:[%06d], Kana:[%06d]\n"
					L"Translated:[%06d], Kanji:[%06d], Kana:[%06d]\n"
					L"Matching:[%06d], Phones Matching:[%06d]\n", 
					nTotal, nKanji, nKana, 
					nTranslated, nKanjiTranslated, nKanaTranslated,
					nMatching, nMatchPhones);


	fclose(fpIn);
	fclose(fpOut);
}
