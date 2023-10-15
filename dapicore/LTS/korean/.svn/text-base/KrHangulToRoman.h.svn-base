/*C_HEADER_FILE****************************************************************
FILE			:	KrHangulToRoman.h
DESC			:	Converts Unicode to ascii. Also contains conversion tables needed 
					to convert Katakana and Hiragana to Romongi.
TABS			:	3
OWNER			:	Fonix
DATE CREATED	:	03 May 2002

(C) Copyright 2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 7/22/03 6:28p $
  $Revision: 4 $

*END_HEADER*******************************************************************/
#ifndef LANGUAGE_H
#define LANGUAGE_H

typedef struct 
{
    wchar_t wszUCS;
    char    szRomongi[5];
} language;

typedef struct 
{
    wchar_t wszHangul;
    char    szRoman[7];
} languageKorean;

typedef struct 
{
    wchar_t wszUCSHalfWidthKat;
    wchar_t wszFullKat;
} conversion;

#define SYLLABLE_MARKER_CHAR	'-'
#define SYLLABLE_MARKER_STR		"-"
#define LONG_SYLLABLE_MARKER_CHAR	'~'
#define LONG_SYLLABLE_MARKER_STR	"~"

#define MAX_PHONEMES 512

#endif // LANGUAGE_H