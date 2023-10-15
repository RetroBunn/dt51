/*
 ***********************************************************************
 *
 *                           Coryright (c)
 *    © Digital Equipment Corporation 1996, 1997, 1998. All rights reserved.
 *    © Force Computers, a Solectron Company, 2000. All rights reserved.
 *
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Digital Equipment Corporation and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Digital or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:    p_uk_sy1.c
 *    Author:	
 *    Creation Date:
 *
 *    Functionality:
 *  English syllabification and output 
 *
 ***********************************************************************
 *
 *	Rev	Who		Date			Description
 *	---	----	------------	--------------------------------------------
 *  001 MGS     03/25/1996		Moved language dependent code from phsyl.c to here
 *  002 SIK		07/09/1996  	Cleaning up and maintenance
 *	003 DR 		07/21/1997		Created, copied from p_us_sl1.c
 *	004 GL/CH 	01/16/1998		For BATS#549 Update this file for UK English
 *
 *
 */

#include "dectalkf.h"
#include "ph_def.h"

const char uk_ascky_check[] =
{
	'0',	'i',	'I',	'e',	'E',	'@',	'a',	'A',	'W',	'^',
	'c',	'o',	'O',	'U',	'u',	'R',	'Y',	'x',	'|',	'F',
	'K',	'P',	'M',	'j',	'w',	'y',	'r',	'l',	'h',	'B',
	'X',	'm',	'n',	'G',	'L',	'H', 	'N',	'f',	'v',	'T',
	'D',	's',	'z',	'S',	'Z',	'p',	'b',	't',	'd',	'k',
	'g',	'V',	'Q',	'q',	'C',	'J',	0,

	0, 0, 0,
	0, 0, 0, 0, 0, 0, ' ', 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0,
};

const unsigned char *CONSTCONST uk_common_affixes[] =
{
	(const unsigned char*)"sElvz",
	(const unsigned char*)"kwIst",
	(const unsigned char*)"flEks",
	(const unsigned char*)"sfir",
	(const unsigned char*)"stAn",
	(const unsigned char*)"graf",
	(const unsigned char*)"ples",
	(const unsigned char*)"plen",
	(const unsigned char*)"skop",
	(const unsigned char*)"baks",
	(const unsigned char*)"ston",
	(const unsigned char*)"wRT",
	(const unsigned char*)"lxnd",
	(const unsigned char*)"l@nd",
	(const unsigned char*)"kast",
	(const unsigned char*)"fIS",
	(const unsigned char*)"h@nd",
	(const unsigned char*)"yad",
	(const unsigned char*)"kBpf",
	(const unsigned char*)"mxnt",
	(const unsigned char*)"mEnt",
	(const unsigned char*)"sElf",
	(const unsigned char*)"st@t",
	(const unsigned char*)"SIp",
	(const unsigned char*)"sAt",
	(const unsigned char*)"vIl",
	(const unsigned char*)"b@k",
	(const unsigned char*)"bot",
	(const unsigned char*)"lAf",
	(const unsigned char*)"lAk",
	(const unsigned char*)"pAp",
	(const unsigned char*)"wck",
	(const unsigned char*)"wBS",
	(const unsigned char*)"wUd",
	(const unsigned char*)"wRk",
	(const unsigned char*)"kek",
	(const unsigned char*)"bcl",
	(const unsigned char*)"bEl",
	(const unsigned char*)"del",
	(const unsigned char*)"hIl",
	(const unsigned char*)"hol",
	(const unsigned char*)"hUd",
	(const unsigned char*)"l|s",
	(const unsigned char*)"m@n",
	(const unsigned char*)"mxn",
	(const unsigned char*)"mc",
	(const unsigned char*)"nEk",
	(const unsigned char*)"n|s",
	(const unsigned char*)"Sap",
	(const unsigned char*)"Z|n",
	(const unsigned char*)"S|n",
	(const unsigned char*)"tel",
	(const unsigned char*)"tin",
	(const unsigned char*)"tAm",
	(const unsigned char*)"wRd",
	(const unsigned char*)"wK",
	(const unsigned char*)"wIl",
	(const unsigned char*)"wAz",
	(const unsigned char*)"b@g",
	(const unsigned char*)"k@p",
	(const unsigned char*)"ka",
	(const unsigned char*)"k@t",
	(const unsigned char*)"dxm",
	(const unsigned char*)"flA",
	(const unsigned char*)"mxn",
	(const unsigned char*)"m@n",
	(const unsigned char*)"mEn",
	(const unsigned char*)"n^t",
	(const unsigned char*)"pad",  /* GL 01/16/1998, not sure, may need to use "pBd" */
	(const unsigned char*)"ek",
	(const unsigned char*)"bO",
	(const unsigned char*)"de",
	(const unsigned char*)"fL",
	(const unsigned char*)"|J",
	(const unsigned char*)"sc",
	(const unsigned char*)"we",
	(const unsigned char*)0
};

const char uk_syl_vowels[] = "a@AeEiIoOuU^WRc|xLNB";

const char *CONSTCONST uk_syl_cons[] =
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

/*
 *      Function Name: saysyllable()      
 *
 *  	Description: used to break the symbol array up into syllable chunks
 *  				 and pass that on ...
 *
 *      Arguments: LPTTS_HANDLE_T phTTS
 *
 *      Return Value: void
 *
 *      Comments:
 *
 */

void uk_saysyllable (LPTTS_HANDLE_T phTTS)
{

	int i, j, k;   /* MVP int m; was unreferenced varaible */
	int last, old_tot;
	short temp_symbols[NPHON_MAX + SAFETY + 2];
	short temp_user_durs[NPHON_MAX + SAFETY + 2];
	short temp_user_f0[NPHON_MAX + SAFETY + 2];
	//short temp_user_length[NPHON_MAX + SAFETY + 2];

	PKSD_T pKsd_t = phTTS->pKernelShareData;
	PDPH_T pDph_t = (PDPH_T)phTTS->pPHThreadData;

	/* 
	 *  then, save the clause ...
	 */

	for (i = 0; i <= pDph_t->nsymbtot; i++)
	{
		temp_symbols[i] = pDph_t->symbols[i];
		temp_user_durs[i] = pDph_t->user_durs[i];
		temp_user_f0[i] = pDph_t->user_f0[i];
		temp_user_f0[i] = pDph_t->user_length[i];

	}

	old_tot = pDph_t->nsymbtot;
	last = 0;
	while (last <= old_tot)
	{
		pDph_t->phone_struct[0] = WBOUND;
		last += 1;
		for (j = 0; (temp_symbols[j + last] != WBOUND) && (j + last < old_tot) && (j < 256); j++)
			pDph_t->phone_struct[j + 1] = temp_symbols[j + last];
		pDph_t->phone_struct[j + 1] = 0;
		/* 
		 *  syllabify it, and return the length of syllable_struct ...
		 */
		k = ph_syllab (pDph_t, j);
		pDph_t->syllable_struct[k] = 0;
		/* 
		 *  now, after the comma, start breaking the word up ....
		 */
		syl_clause_init (pDph_t);
		while (--k >= 0)
		{
			/* 
			 *  count up the sounded phones ...
			 */
			if (uk_ascky_check[temp_symbols[last]])
				pDph_t->nphone++;
			if (pDph_t->syllable_struct[k] == SBOUND)
				speak_syllable (phTTS);
			else
			{
				pDph_t->symbols[pDph_t->nsymbtot] = temp_symbols[last];
				pDph_t->user_durs[pDph_t->nsymbtot] = temp_user_durs[last];
				pDph_t->user_f0[pDph_t->nsymbtot++] = temp_user_f0[last++];
			}
		}
		/* 
		 *  take care of the last accumulated syllable ...
		 */
		if (pDph_t->nsymbtot > 1)
			speak_syllable (phTTS);
	}
}
