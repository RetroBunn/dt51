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

  $Date: 3/26/03 4:11p $
  $Revision: 3 $

*END_HEADER******************************************************************/
#ifndef BYTEORDER_H
#define BYTEORDER_H

#include "FnxPlatform.h"

#if defined(__cplusplus)
extern "C" {
#endif

FNX_EXPORT(BOOL, LittleEndian());
FNX_EXPORT(UDWORD, ByteSwap32(UDWORD net));
FNX_EXPORT(UWORD, ByteSwap16(UWORD net));
FNX_EXPORT(void, BlockByteSwap32(UDWORDPTR pi, UDWORD iSize));
FNX_EXPORT(void, BlockByteSwap16(UWORDPTR pw, UDWORD iSize));

#if defined(__cplusplus)
}
#endif

#endif

