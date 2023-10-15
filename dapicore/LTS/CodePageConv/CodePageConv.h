/*H_HEADER_FILE***************************************************************
FILE			: CodePageConv.h
DESC			: 
TABS			: 4
OWNER			: Fonix
DATE CREATED	: 15 Sept 2005 

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER******************************************************************/
#ifndef	CODEPAGECONV_H
#define	CODEPAGECONV_H

typedef enum _tagCodeSort
{
	eUtf16=0,
	eSjis,
	eEuc,
	eKsc,
	eGbk

}CODE_TYPE;

// Unicode section boundaries
#define UNI_HIRAGANA_MIN	0x3041
#define UNI_HIRAGANA_MAX	0x309e
#define UNI_KATAKANA_MIN	0x30a1
#define UNI_KATAKANA_MAX	0x30fe
#define UNI_STDCJK_MIN		0x4e00
#define UNI_STDCJK_MAX		0x9fa0

#define EUC_HIRAGANA_MIN	0xa4a1
#define EUC_HIRAGANA_MAX	0xa4f3
#define EUC_KATAKANA_MIN	0xa5a1
#define EUC_KATAKANA_MAX	0xa5f6

#if defined(__cplusplus)
extern "C" {
#endif

extern int Sjis2Utf(unsigned char *sSjis, wchar_t *wsUtf, int nUtf);
extern int Utf2Sjis(wchar_t *wsUtf, unsigned char *sSjis, int nSjis);
extern int IsSjis(unsigned char *sSjis);

extern int Euc2Utf(unsigned char *sEuc, wchar_t *wsUtf, int nUtf);
extern int Utf2Euc(wchar_t *wsUtf, unsigned char *sEuc, int nEuc);

extern int Gbk2Utf(unsigned char *sGbk, wchar_t *wsUtf, int nUtf);
extern int IsGbk(unsigned char *sGbk);

extern int Ksc2Utf(unsigned char *sKsc, wchar_t *wsUtf, int nUtf);
extern int IsKsc(unsigned char *sKsc);

#ifdef CASIO_SH3
extern void InitBsortGlobals();
#endif //CASIO_SH3

#if defined(__cplusplus)
}
#endif

#endif
