/* 
 ***********************************************************************
 *
 *                           Copyright (c)
 *	  Copyright � 2000 Force Computers, a Solectron Company. All rights reserved.
 *    � Digital Equipment Corporation 1996, 1997 All rights reserved.
 *
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Force Computers Incorporated and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Force or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:    p_us_sr1.c
 *    Author:       Matthew Schnee
 *    Creation Date:05-Jun-1995
 *
 *    Functionality:
 *		English code from phsort.c
 *
 ***********************************************************************
 *    Revision History:
 *	Rev	Who		Date			Description
 *	---	-----	-----------		--------------------------------------------
 *	001	MGS		06/19/1996		Moved init_med_final,find_syll_to_stress to 
 *								ph_sort2.c English and German
 *								Moved get_next_bound_type, move_stdangle  to
 *								ph_sort2.c English and Spanish
 *	002 SIK		07/12/1996  	Cleaning up and maintenance
 *  003	GL		04/21/1997		BATS#357  Add the code for __osf__ build 
 *  004	GL		04/21/1997		BATS#360  remove spaces before "#define" or "#if" 
 *  005	MGS		04/13/2000		Changes for integrated phoneme set 
 *  006 NAL		06/12/2000		Warning removal
 *  007 EAB     06/28/2000     	Unified Phoneme Set Changes
 *  008	MGS		10/05/2000		Redhat 6.2 and linux warning removal
 *  009 CAB		10/18/2000		Changed copyright info and formatted comments
 */

#include "dectalkf.h"
#include "ph_def.h"

/* 
 * Scan forward to see if this consonant is followed by a stress symbol 
 * before encounter vowel or boundary.  If so, check to see if legal cluster 
 */

#define NOCLUSTER   	0
#define CLUSTER      	1
#define CLUSTER_TRYS   	2



/*
 *      Function Name: phcluster()
 *
 *  	Description: If f & s are first and second elements of potential cluster, return 
 * 					 either CLUSTER, NOCLUSTER, or CLUSTER_TRYS 
 *					 (true and look for prior [s]) 
 *
 *      Arguments: short f,
 *				   chort s	
 *
 *      Return Value: 
 *
 *      Comments:
 *
 */
short ch_phcluster (short f, short s)
{
	switch (f)
	{
	case USP_P:
		if ((s == USP_LL) || (s == USP_R))
			return (CLUSTER_TRYS);
		break;
	case USP_B:
		if ((s == USP_LL) || (s == USP_R))
			return (CLUSTER);
		break;
	case USP_F:
		if (s == USP_R)
			return (CLUSTER_TRYS);
		if (s == USP_LL)
			return (CLUSTER);
		break;
	case USP_T:
		if (s == USP_R)
			return (CLUSTER_TRYS);
		if (s == USP_W)
			return (CLUSTER);
		break;
	case USP_D:
	case USP_TH:
		if ((s == USP_R) || (s == USP_W))
			return (CLUSTER);
		break;
	case USP_K:
		if ((s == USP_R) || (s == USP_LL) || (s == USP_W))
			return (CLUSTER_TRYS);
		break;
	case USP_G:
		if ((s == USP_R) || (s == USP_LL) || (s == USP_W))
			return (CLUSTER);
		break;
	case USP_S:
		if ((s == USP_W) || (s == USP_LL) || (s == USP_P) || (s == USP_T)
			|| (s == USP_K) || (s == USP_M) || (s == USP_N) || (s == USP_F))
			return (CLUSTER);
		break;
	case USP_SH:
		if ((s == USP_W) || (s == USP_LL) || (s == USP_P) || (s == USP_T)
			|| (s == USP_R) || (s == USP_M) || (s == USP_N))
			return (CLUSTER);
		break;
	}
	return (NOCLUSTER);
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */