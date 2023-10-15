/*H_HEADER_FILE***************************************************************
FILE			: CJK2Pinyin.h
DESC			: 
TABS			: 3
OWNER			: 
DATE CREATED	: 6 Dec 2005

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER******************************************************************/
#ifndef	CJK2PINYIN_H
#define	CJK2PINYIN_H

#include "port.h"
//#ifndef ARM7  //moved to port.h for each platform MLT 02/10/06
//#include <wchar.h>  //moved to port.h for each platform MLT 02/10/06
//#else //moved to port.h for each platform MLT 02/10/06
//typedef unsigned short wchar_t; //moved to port.h for each platform MLT 02/10/06
//#endif //moved to port.h for each platform MLT 02/10/06

//typedef int  BOOL; //moved to port.h for each platform MLT 02/10/06

//#ifndef TRUE //moved to port.h for each platform MLT 02/10/06
//#define TRUE 1 //moved to port.h for each platform MLT 02/10/06
//#endif //moved to port.h for each platform MLT 02/10/06

//#ifndef FALSE  //moved to port.h for each platform MLT 02/10/06
//#define FALSE 0 //moved to port.h for each platform MLT 02/10/06
//#endif //moved to port.h for each platform MLT 02/10/06

#define MAX_PHRASE_LENGTH	128
#define MAX_HANZI_CONTEXT	15		// Max length of Hanzi context
#define MAX_PINYIN			10		// Max length of pinyin+tone
typedef struct _tagHanziContext
{
		wchar_t wsHanziContext[MAX_HANZI_CONTEXT];
        struct _tagHanziContext *pNext;
}HanziContext;

typedef struct _tagPinyinWithTone
{
        char sPinyinWithTone[MAX_PINYIN];
        HanziContext *pHanziContext;
        struct _tagPinyinWithTone *pNext;
}PinyinWithTone;

typedef struct _tagHanzi
{
		wchar_t wcHanzi;
        PinyinWithTone *pPinyinWithTone;
		struct _tagHanzi *pNext;
}Hanzi;

extern char *PinyinTableWithTones[];
extern const unsigned short CJKUnicodeOffsetToPinyinTable[];
extern int gnPinyinPlusTones;
extern int gnMaxCJK;

//extern int ConvertToAscii(void *phTTS, void *lpInput, char *sPinyin, int iInType);
extern Hanzi *ReadPolyPhoneTable(char *sPolyPhoneFile);
extern void FreePolyPhoneTable(Hanzi *pHeadHanzi);


#endif
