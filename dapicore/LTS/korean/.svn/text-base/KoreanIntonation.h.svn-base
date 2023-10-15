/*H_HEADER_FILE***************************************************************
FILE			: KoreanIntonaton.h
DESC			: 
TABS			: 4
OWNER			: Fonix
DATE CREATED: 14 Sept 2005

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER******************************************************************/
#ifndef	KOREAN_INTONATION_H
#define	KOREAN_INTONATION_H

// Intonation start flags
#define KR_INTON_SON1		0x0001	// First sonorant
#define KR_INTON_SYL1		0x0002	// First syllabic nucleus (Vowel or Syllabic n)

// Intonation patterns
#define KR_INTON_L			0x00000001	// Low tone
#define KR_INTON_H			0x00000002	// High tone
#define KR_INTON_X			0x00000004	// Interpolated tone
#define KR_INTON_a			0x00000008	// AP final boundary
#define KR_INTON_PLS		0x00000010	// AP medial tone (+)
#define KR_INTON_PCT		0x00000020	// IP final boundary (%)

// IP final tones
#define KR_INTON_LH			0x00000040	// This is a sharper, later rise starting after the onset of the final syllable.  Used for questions, continuation rises and explanatory endings.
#define KR_INTON_HL			0x00000080	// H is not as high and L is not as low as lone H% or L%.  Common in declaratives, wh-questions and news broadcasting
#define KR_INTON_LHL		0x00000100	// Implies being persuasive, insisting and confirmative
#define KR_INTON_HLH		0x00000200	// Not so common.  Implies speaker is confident and expecting listener's agreement
#define KR_INTON_LHLH		0x00000400	// Less common. Intensifies LH%'s meaning
#define KR_INTON_HLHL		0x00000800	// Less common. Intensifies HL%'s meaning
#define KR_INTON_LHLHL		0x00001000	// rare. Intensifies LHL%'s meaning

// Syllable/Word position flags
#define KR_POS_FIRST		0x0001	
#define KR_POS_MID			0x0002	
#define KR_POS_LAST			0x0004	

// Phrase type flags
#define KR_PHRS_NEUTRAL		0x0001
#define KR_PHRS_QUESTION	0x0002
#define KR_PHRS_EXCLAMATION	0x0004
#define KR_PHRS_WH_WORD		0x0008
#define KR_PHRS_YESNO		0x0010


typedef struct _tagKrSyllable
{
	char cTone;
	char bLong;						// Flag to indicate a long vowel in this syllable
	char bFocus;					// flag to set focus on this syllable
	int	 f0;						// Target pitch for this syllable
	int  f0_2;						// Optional 2nd pitch target for this syllable
	int  iTone;						// Tone bit flags
	int	 iPos;						// Syllable position flag
	char sPron[16];					// syllable phonetic pronunciation
	char sRoman[16];				// syllable romanization
	struct _tagKrSyllable 
		*pNext,						// next syllable in the word
		*pPrev;

}KOREAN_SYLLABLE;

typedef struct _tagKrWord
{
	int	 iPos;						// Word position flag
	char sWord[128];				// copy of the word romanization
	char sPron[128];				// phonetic pronunciation of word with syllable markers
	char bIsFocus;					// flag to indicate that this is or is not the focus word
	int	 nSyls;						// number of syllables in this word
	KOREAN_SYLLABLE *pSyl;			// pointer to individual syllable information
	struct _tagKrWord 
		*pNext,						// next word in the phrase
		*pPrev;

}KOREAN_WORD;

typedef struct _tagKrPhrase
{
	int	nWords;					// Number of words in phrase
	int iType;					// Phrase type (Ex. KR_PHRS_NEUTRAL, KR_PHRS_QUESTION, KR_PHRS_EXCLAMATION)
	int iInton;					// Phrase intonation flag
	char cEnd;					// End of phrase character
	char sPhrase[512];			// copy of the phrase
	KOREAN_WORD *pWords;		// pointer to individual word information
	struct _tagKrPhrase 
		*pNext,					// pointer to the next phrase
		*pPrev;

}KOREAN_PHRASE;

void KrFreePhrases(KOREAN_PHRASE **ppPhrases);
KOREAN_PHRASE *KrParsePhrase(LPTTS_HANDLE_T phTTS, char *sPhrase);

void KrApplyIntonation(LPTTS_HANDLE_T phTTS, KOREAN_PHRASE *pPhrases);

#endif