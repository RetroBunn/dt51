/*H_HEADER_FILE***************************************************************
FILE        : FnxNames.h
DESC        : 
TABS        : 3
OWNER       : Fonix
DATE CREATED: 

(C) Copyright 1999,2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/26/03 4:12p $
  $Revision: 3 $

*END_HEADER******************************************************************/
#ifndef NAMES_H
#define NAMES_H

#include "FnxPlatform.h"
#include "FnxHash.h"
#include "FnxDesc.h"

typedef struct _diphone
{
  SWORD  cat;
  SDWORD hmm;
  char   *modelname;
  SDWORD mindur;
  SDWORD maxdur;
}_diphoneT, xhuge *diphoneTPtr;
#define SIZE_DIPHONET      sizeof(_diphoneT)

SWORD BasePhoneIndex(DescPtr pDesc, char *sPhone);
diphoneTPtr defineCenter(DescPtr pDesc, char *sCenter);
diphoneTPtr defineLeft(DescPtr pDesc, char *sLeft, char *sCenter);
diphoneTPtr defineRight(DescPtr pDesc, char *sCenter, char *sRight);
SWORD GetCenter(DescPtr pDesc, SWORD iCenter);
SWORD GetLeft(DescPtr pDesc, SWORD iLeft, SWORD iCenter);
SWORD GetRight(DescPtr pDesc, SWORD iCenter, SWORD iRight);
SWORD GetTriphone(DescPtr pDesc, SWORD iLeft, SWORD iCenter, SWORD iRight);

#endif
