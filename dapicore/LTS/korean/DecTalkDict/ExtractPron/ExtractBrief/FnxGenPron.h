/*H_HEADER_FILE***************************************************************
FILE        : FnxGenPron.h
DESC        : Prototypes needed for automatic pronunciation generation 
TABS        : 3
OWNER       : Randy Wilson
DATE CREATED: 29 June 2001

(C) Copyright 2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/
#ifndef FNXADAPT_H
#define FNXADAPT_H

#include "FnxRecognize.h"
#include "FnxDesc.h"
#include "FnxVocab.h"
#include "FnxSearchen.h"

//#include "FnxNNet.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* Support routines: */
//char     *StrCopyCat(char *sDest, char *sSource);
//VocabTPtr MakeBasephoneVocab(DescPtr pDesc, BOOL bLinkClosures);

/* Needed externally: */
FNX_EXPORT(RecogTPtr, MakeBasephoneRecog(DescPtr pDesc, 
           ConfigPtr pConfig, 
           NNetTPtr pNNet,
           SDWORD nBest));

FNX_EXPORT(char, *SearchListString(SearchListPtr pSearchList));
FNX_EXPORT(char, *CleanUpPronunciation(char* sPronunciation));
FNX_EXPORT(char, *MakePronunciation(RecogTPtr pRecog, ConfigPtr pConfig, DescPtr pDesc, NNetTPtr pNNet,  FTKWavePtr *ppWave, SWORD nWaves, SWORD nBest, SWORD bClean));


#if defined(__cplusplus)
}
#endif


#endif
