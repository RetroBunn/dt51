/*H_HEADER_FILE***************************************************************
FILE        : FnxByteOrder.h
DESC        : Function prototypes for routines to read, write and convert values to/from Network Byte Order
TABS        : 3
OWNER       : Fonix
DATE CREATED: 

(C) Copyright 1999,2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/27/03 3:11p $
  $Revision: 5 $

*END_HEADER******************************************************************/
#ifndef BYTEORDERIO_H
#define BYTEORDERIO_H

#include "FnxPlatform.h"

#if defined(__cplusplus)
extern "C" {
#endif

FNX_EXPORT(SDWORD, WriteInt32NBO(FILE *fp, UDWORD i));
FNX_EXPORT(SDWORD, WriteInt16NBO(FILE *fp, UWORD i));
FNX_EXPORT(SDWORD, WriteCalcTypeNBO(FILE *fp, CalcType fValue));
FNX_EXPORT(SDWORD, WriteString(FILE *fp, char *s));
FNX_EXPORT(SDWORD, WriteStringList(FILE *fp, char **psStringList, SDWORD iNumStrings));
FNX_EXPORT(SDWORD, ReadInt32NBO(FILE *fp, UDWORD *pi));
FNX_EXPORT(SDWORD, ReadInt16NBO(FILE *fp, UWORD *pi));
FNX_EXPORT(SDWORD, ReadCalcTypeNBO(FILE *fp, CalcType *pf));
FNX_EXPORT(SDWORD, ReadString(FILE *fp, char **ps));
FNX_EXPORT(SDWORD, ReadStringList(FILE *fp, char ***ppsStringList, SDWORD *piNumStrings));
FNX_EXPORT(SDWORD, ReadInt32BlockNBO(FILE *fp, UDWORD *pValues, UDWORD iNumItems));
FNX_EXPORT(SDWORD, ReadInt16BlockNBO(FILE *fp, UWORD *pValues, UDWORD iNumItems));
FNX_EXPORT(SDWORD, WriteInt32BlockNBO(FILE *fp, UDWORD *pValues, UDWORD iNumItems));
FNX_EXPORT(SDWORD, WriteInt16BlockNBO(FILE *fp, UWORD *pValues, UDWORD iNumItems));

#if defined(__cplusplus)
}
#endif

#endif
