/*H_HEADER_FILE***************************************************************
FILE        : SelectSinglePron.h
DESC        : SelectSinglePron.c prototype
TABS        : 3
OWNER       : fonix 
DATE CREATED   : 25 April 2005

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 
  $Revision: 

*END_HEADER******************************************************************/
#ifndef SINGLE_H
#define  SINGLE_H

#include "DTFnxStdlib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*FUNCTION_HEADER**********************
 * NAME:	;SelectSinglePron
 * DESC: 	 Selects a single pronunciation from a pronunciation string produced by a dictionary lookup.  The
 *           pronunciation is the most common among the alternates (first alternate in all alternate groups)/
 * IN:		 sPronnunciation - input pronunciation string from dictionary lookup
 *           bRemoveOptionals - TRUE to remove the optional phons from sPronunciation
 *								FALSE - to include the optional phons in the pronunciation
 * OUT:		sPronunciation is modified
 * RETURN:	sPronunciation - pointer to sPronunciation
 *					         NULL if errors are encountered.
 * NOTES:	
 *END_HEADER***************************/
int SelectSinglePron(char *sPron, SDWORD bRemove, SDWORD bCombineYW);

#if defined(__cplusplus)
}
#endif

#endif
