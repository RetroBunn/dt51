/* 
 ***********************************************************************
 *
 *                           Copyright ©
 *	  Copyright © 2000 Force Computers, Inc., a Solectron Company. All rights reserved. 
 *    © Digital Equipment Corporation 1996, 1997. All rights reserved.
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
 *    File Name:    p_us_sy1.c
 *    Author:
 *    Creation Date:
 *
 *    Functionality:
 *  English syllabification and output 
 *
 ***********************************************************************
 *
 *  Rev Who	    Date        	Description
 *  --- -----   ----------- 	--------------------------------------------
 *  001 MGS     03/25/1996		Moved language dependent code from phsyl.c to here
 *  002 SIK		07/09/1996  	Cleaning up and maintenance
 *  004	MGS		10/05/2000		Redhat 6.2 and linux warning removal
 *  005 CAB		10/18/2000		Changed copyright info
 */

#include "dectalkf.h"
#include "ph_def.h"

const char us_ascky_check[] =
{
	0, 'i', 'I', 'e', 'E', '@', 'a', 'A', 'W', '^',
	'c', 'o', 'O', 'U', 'u', 'R', 'Y', 'x', '|', 0,
	0, 0, 0, 0, 'w', 'y', 'r', 'l', 'h', 0,
	0, 'm', 'n', 'G', 'L', 0, 'N', 'f', 'v', 'T',
	'D', 's', 'z', 'S', 'Z', 'p', 'b', 't', 'd', 'k',
	'g', '&', 'Q', 'q', 'C', 'J', 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, ' ', 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0,
};

#ifdef OS_PALM
const unsigned char * us_common_affixes[] =
#else
const unsigned char *const us_common_affixes[] =
#endif
{
	"sElvz",
	"kwIst",
	"flEks",
	"sfir",
	"stAn",
	"gr@f",
	"ples",
	"plen",
	"skop",
	"baks",
	"ston",
	"wRT",
	"lxnd",
	"l@nd",
	"k@st",
	"fI|S",
	"h@nd",
	"yard",
	"kcpf",
	"mxnt",
	"mEnt",
	"sElf",
	"st@t",
	"SI|p",
	"sAt",
	"vIl",
	"b@k",
	"bot",
	"lAf",
	"lAk",
	"pAp",
	"wck",
	"wcS",
	"wUd",
	"wRk",
	"kek",
	"bcl",
	"bEl",
	"del",
	"hIl",
	"hol",
	"hUd",
	"l|s",
	"m@n",
	"mxn",
	"mor",
	"nEk",
	"n|s",
	"Sap",
	"Z|n",
	"S|n",
	"tel",
	"tin",
	"tAm",
	"wRd",
	"wer",
	"wIl",
	"wAz",
	"b@g",
	"k@p",
	"kar",
	"k@t",
	"dxm",
	"flA",
	"mxn",
	"m@n",
	"mEn",
	"n^t",
	"pad",
	"ek",
	"bO",
	"de",
	"fL",
	"|J",
	"sc",
	"we",
	0
};

const char us_syl_vowels[] = "a@AeEiIoOuU^WRc|xLN";

#ifdef OS_PALM
const char * us_syl_cons[] =
#else
const char *const us_syl_cons[] =
#endif
{
	"spl", "spr", "str", "skw", "skl", "skr",
	" Sm", " SL",
	"pl", "pr",
	"bl", "br",
	"fl", "fr",
	"tw", "tr",
	"dw", "dr",
	"Tw", "Tr",
	"kw", "kl", "kr",
	"gw", "gl", "gr",
	"sw", "sl", "sp", "st", "sk", "sm", "sn",
	"Sw", "Sl", "Sr",
	" Y",
	"y",
	"f",
	"t",
	"d",
	"T",
	"k",
	"g",
	"s",
	"S",
	"p",
	"w",
	"l",
	"r",
	"h",
	"D",
	"z",
	"Z",
	"C",
	"J",
	"n",
	"m",
	"v",
	"b",
	0
};


