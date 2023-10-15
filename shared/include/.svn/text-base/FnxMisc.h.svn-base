/*H_HEADER_FILE***************************************************************
FILE        : misc.h
DESC        : miscelaneous helper functions
TABS        : 3
OWNER       : R. Brian Moncur
DATE CREATED   : 11 October 1999

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 7/07/03 1:04p $
  $Revision: 10 $

*END_HEADER******************************************************************/
#ifndef  MISC_H
#define  MISC_H

#include "FnxPlatform.h"

#ifndef MAXBUF
#define MAXBUF 2048
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern BOOL WhiteSpace(char c);
// Don't change this!  This means you!  We know what we are doing.
#define ForwardToBackSlash BackToForwardSlash
extern void BackToForwardSlash(char *sFilename);
extern char *CombineStrings(char **psString, SDWORD lNumStrings);
extern char *WeThreeStrings(char *s1, char *s2, char *s3);
extern char *GrabField(char *sDest, char *sSource);
extern char **SplitString(char *sString, SDWORD *piNum);
extern void Strip(char *s);
extern SDWORD EndsWith(char *sString, char *sEnd);
extern SDWORD EndsWithI(char *sString, char *sEnd);
extern SDWORD BeginsWithI(char *sString, char *sBegin);
extern SDWORD EndsWithNumber(char *sFilename);
extern SDWORD CharInString(char c, char *s);
extern SDWORD ReadField(char *sDest, char *sDelim, FILE *fp);
extern SDWORD ExtractField(char *sDest, char *sDelim, char *sBuffer);
extern char **ReadTxt(char *sTxtFile, SDWORD *plNumWords);
extern char **BuildStringList(char **psNames, SDWORD iNumNames);
extern char *StrCopyCat(char *sDest, char *sSource);
FNX_EXPORT(char *, MakeCombinedString(char *sPrefix, char *sSeparator, char *sSuffix, char **psElements, SDWORD iNumElements));
extern int SameString(char *s1, char *s2);
extern int SameStringI(char *s1, char *s2);
#ifdef OS_WIN32
extern int __cdecl CaseCmpString(const void *pA, const void *pB);
#else
extern int CaseCmpString(const void *pA, const void *pB);
#endif
extern void RemoveDuplicateStrings(char **psStrings, SDWORD *piNumStrings);

#ifdef OS_UNIX
char *strupr(char *str);
#endif

#ifdef __cplusplus
}
#endif


#endif
