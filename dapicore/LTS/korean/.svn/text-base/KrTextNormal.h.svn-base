/*H_HEADER_FILE***************************************************************
FILE			: KrTextNormal.h
DESC			: 
TABS			: 4
OWNER			: 
DATE CREATED	: 17 April 2006

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER******************************************************************/
#ifndef	KRTEXTNORMAL_H
#define	KRTEXTNORMAL_H

#if defined(__cplusplus)
extern "C" {
#endif

int KrIsAlpha(wchar_t *pwc);
int KrIsNumber(wchar_t *pwc);
int KrIsSymbol(wchar_t *pwc);
int KrIsCountingWord(wchar_t *pwsText);
int KrIsUnitOfMeasure(wchar_t *pwc);
int KrIsDateTime(wchar_t *pwsText);
int KrIsEmail(wchar_t *wsInput);
int KrIsURL(wchar_t *wsInput);
int KrNormalizeNumber(wchar_t *wsNum, wchar_t *wsText, int iType, int bUseReduced);
int KrNormalizeDigits(wchar_t *wsInput, wchar_t *wsNormal, int bOk2UseNK);

int KrNormalizeText(wchar_t *wsInput, wchar_t *wsHangul);

#if defined(__cplusplus)
}
#endif


#endif
