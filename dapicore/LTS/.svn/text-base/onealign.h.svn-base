/*H_HEADER_FILE***************************************************************
FILE			: onealign.h
DESC			: Data structures and prototypes for dynamic programming string-matching functions.
TABS			: 3
OWNER			: Randy Wilson
DATE CREATED: 16 April 1999

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/
#ifndef	ONEALIGN_H
#define	ONEALIGN_H

void AppendStrings(char *sTarget, char *sRecog, char *sTargetWord, char *sRecogWord, int iLength, int bChangeCase);
int DPMatchStrings(char *psTarget[], int nTarget, char *psRecog[], int nRecog, int *piMatch);
int MatchStrings(char *psTarget[], int nTarget, char *psRecog[], int nRecog, 
                  int *piInsertions, int *piDeletions, int *piCorrect, int *piSubstitutions,
                  char **psTargetOutput, char **psRecogOutput, int bChangeCase);

#endif