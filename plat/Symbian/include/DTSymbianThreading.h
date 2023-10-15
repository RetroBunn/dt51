/*H_HEADER_FILE***************************************************************
FILE			: GlobalDT.h
DESC			: 
TABS			: 3
OWNER			: 
DATE CREATED: 6 Feb 2004

(C) Copyright 2004 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/
#ifndef	GLOBALDT_H
#define	GLOBALDT_H

#include "port.h"

#if defined(__cplusplus)
extern "C" {
#endif

int LockQueueCount();
int UnlockQueueCount();
int LockQueue();
int UnlockQueue();
void ResetQueue();
int GetSpeechData(short* buffer, int buflength);
void StartThread(char *String);
int GetQueueCount();
void SignalThread();
void* GetThreadData();

#if defined(__cplusplus)
}
#endif

#endif
