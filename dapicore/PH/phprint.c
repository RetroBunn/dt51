/* 
 ***********************************************************************
 *
 *                           Copyright ©
 *    Copyright © 2000,2001 Force Computers, Inc., a Solectron Company. All rights reserved.
 *
 *    Restricted Rights: "USe, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Force Computers Incorporated and other parties.
 *    Possession, "USe, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Force or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:    phprint.c
 *    Author:       Michel Divay
 *    Creation Date:11/11/2000
 *
 *    Functionality:
 *    
 *    
 *
 ***********************************************************************
 *    Revision History:
 *
 * Rev  Who     Date            Description
 * ---  -----   -----------     --------------------------------------------  
 * 0001 MD		11/22/2000      Initial creation
 * 0002	CAB		08/31/2001		Added ifdef NEW_PHONES
 *								Added include for dectalkf.h		
 */

/* phprint.c
   code externe des phonemes : code Michel Divay sur 1 ou 2 caractères 
*/

#include "dectalkf.h"

#include "port.h"

#ifdef NEW_PHONES
#include "l_all_ph.h"
#include "cmd.h"
#else
#include "l_fr_ph.h"	// TOT_ALLOPHONES, FinNorm, FSyntVirg
#endif

//moved to port.h for each platform - mlt
//#include <stdio.h>

#if 0
static char* lognames[] = {
/* 00 */  "_",
/* 01 */  "A",
/* 02 */  "ƒ", //â
/* 03 */  "Š", //è
/* 04 */  "Au",
/* 05 */  "E",
/* 06 */  "‚",  /é
/* 07 */  "Eu",
/* 08 */  "I",
/* 09 */  "O",
/* 10 */  "O6",
/* 11 */  "Ou",
/* 12 */  "U",
/* 13 */  "An",
/* 14 */  "In",
/* 15 */  "On",
/* 16 */  "Un",
/* 17 */  "Ap",
/* 18 */  "L",
/* 19 */  "R",
/* 20 */  "W",
/* 21 */  "Wu",
/* 22 */  "Y",
/* 23 */  "Ch",
/* 24 */  "F",
/* 25 */  "J",
/* 26 */  "Rx",
/* 27 */  "S",
/* 28 */  "V",
/* 29 */  "Z",
/* 30 */  "B",
/* 31 */  "D",
/* 32 */  "G",
/* 33 */  "K",
/* 34 */  "P",
/* 35 */  "T",
/* 36 */  "Gn",
/* 37 */  "M",
/* 38 */  "N",
/* 39 */  "Ng",
/* 40 */  "Xx",
/* 41 */  "-"
};
#endif

/* external code for phonemes */
char *flognames[] = {
  /* 00 */  "_",
  /* 01 */  "A",
  /* 02 */  "A3",
  /* 03 */  "E2",
  /* 04 */  "Au",
  /* 05 */  "E",
  /* 06 */  "E1",
  /* 07 */  "Eu",
  /* 08 */  "I",
  /* 09 */  "O",
  /* 10 */  "O6",
  /* 11 */  "Ou",
  /* 12 */  "U",
  /* 13 */  "An",
  /* 14 */  "In",
  /* 15 */  "On",
  /* 16 */  "Un",
  /* 17 */  "Ap",
  /* 18 */  "L",
  /* 19 */  "R",
  /* 20 */  "W",
  /* 21 */  "Wu",
  /* 22 */  "Y",
  /* 23 */  "Ch",
  /* 24 */  "F",
  /* 25 */  "J",
  /* 26 */  "Rx",
  /* 27 */  "S",
  /* 28 */  "V",
  /* 29 */  "Z",
  /* 30 */  "B",
  /* 31 */  "D",
  /* 32 */  "G",
  /* 33 */  "K",
  /* 34 */  "P",
  /* 35 */  "T",
  /* 36 */  "Gn",
  /* 37 */  "M",
  /* 38 */  "N",
  /* 39 */  "Ng",
  /* 40 */  "Xx",
  /* 41 */  "-"
};
char *uslognames[]={
 "SIL",		 
 "US_IY",		 
 "US_IH",	 
 "US_EY",		 
 "US_EH",		 
 "US_AE",		 
 "US_AA",		 
 "US_AY",		 
 "US_AW",		 
 "US_AH",		 
 "US_AO",		
 "US_OW",		
 "US_OY",		
 "US_UH",		
 "US_UW",		
 "US_RR",		
 "US_YU",		
 "US_AX",		
 "US_IX",		
 "US_IR",		
 "US_ER",		
 "US_AR",		
 "US_OR",		
 "US_UR",		
 "US_W",		
 "US_Y",		
 "US_R",		
 "US_LL",		
 "US_HX",	
 "US_RX",	
 "US_LX",		
 "US_M",		
 "US_N",		
 "US_NX",		
 "US_EL",	
 "US_DZ",	
 "US_EN",	
 "US_F",	
 "US_V",		
 "US_TH",		
 "US_DH",	
 "US_S",	
 "US_Z",		
 "US_SH",		
 "US_ZH",	
 "US_P",	
 "US_B",		
 "US_T",		
 "US_D",		
 "US_K",		
 "US_G",		
 "US_DX",		
 "US_TX",	
 "US_Q",			
 "US_CH",		
 "US_JH",	
 "US_DF",	
 "US_TZ",	
 "US_CZ",	
 "US_LY",
 "US_RE",
 "US_X1",
 "US_X2",
 "US_X3",
 "US_X4",
 "US_X5",
 "US_X6",
 "US_X7",
 "US_X8",
 "US_X9",
 "US_Z1"
};
char *uklognames[]={
 "SIL",		 
 "UK_IY",		 
 "UK_IH",	 
 "UK_EY",		 
 "UK_EH",		 
 "UK_AE",		 
 "UK_AA",		 
 "UK_AY",		 
 "UK_AW",		 
 "UK_AH",		 
 "UK_AO",		
 "UK_OW",		
 "UK_OY",		
 "UK_UH",		
 "UK_UW",		
 "UK_RR",		
 "UK_YU",		
 "UK_AX",		
 "UK_IX",		
 "UK_IR",		
 "UK_ER",		
 "UK_AR",		
 "UK_OR",		
 "UK_UR",		
 "UK_W",		
 "UK_Y",		
 "UK_R",		
 "UK_LL",		
 "UK_HX",	
 "UK_RX",	
 "UK_LX",		
 "UK_M",		
 "UK_N",		
 "UK_NX",		
 "UK_EL",	
 "UK_DZ",	
 "UK_EN",	
 "UK_F",	
 "UK_V",		
 "UK_TH",		
 "UK_DH",	
 "UK_S",	
 "UK_Z",		
 "UK_SH",		
 "UK_ZH",	
 "UK_P",	
 "UK_B",		
 "UK_T",		
 "UK_D",		
 "UK_K",		
 "UK_G",		
 "UK_DX",		
 "UK_TX",	
 "UK_Q",			
 "UK_CH",		
 "UK_JH",	
 "UK_DF",	
 "UK_TZ",	
 "UK_CZ",	
};


char *grlognames[]={
"SIL",
"GRP_A",
"GRP_E",
"GRP_AE",
"GRP_EX",	 
"GRP_I",		 
"GRP_O",		
"GRP_OE",	
"GRP_U",		 
"GRP_UE",	
"GRP_AH",	
"GRP_EH",	
"GRP_AEH",	
"GRP_IH",	
"GRP_OH",	
"GRP_OEH",	
"GRP_UH",	
"GRP_UEH",	
"GRP_EI",	
"GRP_AU",	
"GRP_EU",	
"GRP_AN",	
"GRP_IM",
"GRP_UM",	
"GRP_ON",	
"GRP_J",	
"GRP_L",		
"GRP_RR",
"GRP_R",		
"GRP_H",	
"GRP_M",	
"GRP_N",	
"GRP_NG",	
"GRP_EL",
"GRP_EM",	
"GRP_EN",	
"GRP_F",	
"GRP_V",	    
"GRP_S",		
"GRP_Z",		
"GRP_SH",	
"GRP_ZH",	
"GRP_CH",		
"GRP_KH",	
"GRP_P",	
"GRP_B",	
"GRP_T",	
"GRP_D",	
"GRP_K",	
"GRP_G",	
"GRP_Q",	
"GRP_PF",	
"GRP_TS",	
"GRP_DJ",	
"GRP_TJ",	
"GRP_KSX",	
"GRP_I1",	
"GRP_E1",	
"GRP_O1",
"GRP_U1",	
"GRP_Y1",	
"GRP_ER",	
};

char *splognames[]={
"SIL",
"SPP_A",   //((PFSP<<PSFONT) |SP_A	)               /*       Palabra        */
"SPP_E",   //((PFSP<<PSFONT) |SP_E	)               /*       Leo            */
"SPP_I",      //((PFSP<<PSFONT) |SP_I	)               /*       Hilo           */
"SPP_O",      //((PFSP<<PSFONT) |SP_O	)               /*       Hola           */
"SPP_U",      //((PFSP<<PSFONT) |SP_U )               /*       Lunes          */
"SPP_WX",	 //((PFSP<<PSFONT) |SP_WX)               /* Rounded dipth semiv. */
"SPP_YX",		 //((PFSP<<PSFONT) |SP_YX)               /* Unround dipth semiv. */
"SPP_RR",		 //((PFSP<<PSFONT) |SP_RR)               /*       Rama           */
"SPP_L",		 //((PFSP<<PSFONT) |SP_L	)               /*       Luna           */
"SPP_LL",		//((PFSP<<PSFONT) |SP_LL)              /*       Calle          */
"SPP_M",		//((PFSP<<PSFONT) |SP_M)              /*       Mama'          */
"SPP_N",		//((PFSP<<PSFONT) |SP_N)              /*       Nana           */
"SPP_NH",		//((PFSP<<PSFONT) |SP_NH)              /*       Munoz          */
"SPP_F",		//((PFSP<<PSFONT) |SP_F)              /*       Feo            */
"SPP_S",		//((PFSP<<PSFONT) |SP_S)              /*       Casa           */
"SPP_J",		//((PFSP<<PSFONT) |SP_J)              /*       Caja           */
"SPP_TH",		//((PFSP<<PSFONT) |SP_TH)              /*       Caza           */
"SPP_BH",		//((PFSP<<PSFONT) |SP_BH)              /*       Haba           */
"SPP_DH",		//((PFSP<<PSFONT) |SP_DH)              /*       Hada           */
"SPP_GH",		//((PFSP<<PSFONT) |SP_GH)              /*       Haga           */
"SPP_YH",		//((PFSP<<PSFONT) |SP_YH)              /*       Yate affricate */
"SPP_P",		//((PFSP<<PSFONT) |SP_P)              /*       Papa'          */
"SPP_B",		//((PFSP<<PSFONT) |SP_B)              /*       Barco          */
"SPP_T",		//((PFSP<<PSFONT) |SP_T)              /*       Tela           */
"SPP_D",		//((PFSP<<PSFONT) |SP_D)              /*       Dama           */
"SPP_K",		//((PFSP<<PSFONT) |SP_K)              /*       Casa           */
"SPP_G",		//((PFSP<<PSFONT) |SP_G)              /*       Gasa           */
"SPP_CH",		//((PFSP<<PSFONT) |SP_CH)              /*       Charco         */
"SPP_Y",		//((PFSP<<PSFONT) |SP_Y)              /*       Haya fricitive */
"SPP_R",		//((PFSP<<PSFONT) |SP_R)              /*       Sara           */
"SPP_Q",		//((PFSP<<PSFONT) |SP_Q)              /*       ~n offglide    */
"SPP_Z",		//((PFSP<<PSFONT) |SP_Z)              /*       Desde          */
"SPP_W",		//((PFSP<<PSFONT) |SP_W)              /*       Hueso          */
"SPP_NX",		//((PFSP<<PSFONT) |SP_NX)              /*       Mango          */
"SPP_V",		//((PFSP<<PSFONT) |SP_V)              /*       Afgano         */
"SPP_IX",		//((PFSP<<PSFONT) |SP_IX)              /*       ~n offglide    */
"SPP_MX",		//((PFSP<<PSFONT) |SP_MX)              /*       Infierno ((nf)  */
"SPP_PH",		//((PFSP<<PSFONT) |SP_PH)              /*       Observar       */
};


char *lalognames[]={
"SIL",
"LAP_A",   //((PFSP<<PSFONT) |SP_A	)               /*       Palabra        */
"LAP_E",   //((PFSP<<PSFONT) |SP_E	)               /*       Leo            */
"LAP_I",      //((PFSP<<PSFONT) |SP_I	)               /*       Hilo           */
"LAP_O",      //((PFSP<<PSFONT) |SP_O	)               /*       Hola           */
"LAP_U",      //((PFSP<<PSFONT) |SP_U )               /*       Lunes          */
"LAP_WX",	 //((PFSP<<PSFONT) |SP_WX)               /* Rounded dipth semiv. */
"LAP_YX",		 //((PFSP<<PSFONT) |SP_YX)               /* Unround dipth semiv. */
"LAP_RR",		 //((PFSP<<PSFONT) |SP_RR)               /*       Rama           */
"LAP_L",		 //((PFSP<<PSFONT) |SP_L	)               /*       Luna           */
"LAP_LL",		//((PFSP<<PSFONT) |SP_LL)              /*       Calle          */
"LAP_M",		//((PFSP<<PSFONT) |SP_M)              /*       Mama'          */
"LAP_N",		//((PFSP<<PSFONT) |SP_N)              /*       Nana           */
"LAP_NH",		//((PFSP<<PSFONT) |SP_NH)              /*       Munoz          */
"LAP_F",		//((PFSP<<PSFONT) |SP_F)              /*       Feo            */
"LAP_S",		//((PFSP<<PSFONT) |SP_S)              /*       Casa           */
"LAP_J",		//((PFSP<<PSFONT) |SP_J)              /*       Caja           */
"LAP_TH",		//((PFSP<<PSFONT) |SP_TH)              /*       Caza           */
"LAP_BH",		//((PFSP<<PSFONT) |SP_BH)              /*       Haba           */
"LAP_DH",		//((PFSP<<PSFONT) |SP_DH)              /*       Hada           */
"LAP_GH",		//((PFSP<<PSFONT) |SP_GH)              /*       Haga           */
"LAP_YH",		//((PFSP<<PSFONT) |SP_YH)              /*       Yate affricate */
"LAP_P",		//((PFSP<<PSFONT) |SP_P)              /*       Papa'          */
"LAP_B",		//((PFSP<<PSFONT) |SP_B)              /*       Barco          */
"LAP_T",		//((PFSP<<PSFONT) |SP_T)              /*       Tela           */
"LAP_D",		//((PFSP<<PSFONT) |SP_D)              /*       Dama           */
"LAP_K",		//((PFSP<<PSFONT) |SP_K)              /*       Casa           */
"LAP_G",		//((PFSP<<PSFONT) |SP_G)              /*       Gasa           */
"LAP_CH",		//((PFSP<<PSFONT) |SP_CH)              /*       Charco         */
"LAP_Y",		//((PFSP<<PSFONT) |SP_Y)              /*       Haya fricitive */
"LAP_R",		//((PFSP<<PSFONT) |SP_R)              /*       Sara           */
"LAP_Q",		//((PFSP<<PSFONT) |SP_Q)              /*       ~n offglide    */
"LAP_Z",		//((PFSP<<PSFONT) |SP_Z)              /*       Desde          */
"LAP_W",		//((PFSP<<PSFONT) |SP_W)              /*       Hueso          */
"LAP_NX",		//((PFSP<<PSFONT) |SP_NX)              /*       Mango          */
"LAP_V",		//((PFSP<<PSFONT) |SP_V)              /*       Afgano         */
"LAP_IX",		//((PFSP<<PSFONT) |SP_IX)              /*       ~n offglide    */
"LAP_MX",		//((PFSP<<PSFONT) |SP_MX)              /*       Infierno ((nf)  */
"LAP_PH",		//((PFSP<<PSFONT) |SP_PH)              /*       Observar       */
};

char *itlognames[]={
"SIL",
"IT_AP",
"IT_EP",
"IT_IY",
"IT_OP",
"IT_UW",
"IT_AX",
"IT_Y",
"IT_RR",
"IT_L",
"IT_LL",
"IT_M",
"IT_N",
"IT_NH",
"IT_F",
"IT_S",
"IT_EH",
"IT_TD",
"IT_BD",
"IT_DD",
"IT_GD",
"IT_JH",
"IT_P",
"IT_B",
"IT_T",
"IT_D",
"IT_K",
"IT_G",
"IT_CH",
"IT_AO",
"IT_R",
"IT_KD",
"IT_Z",
"IT_W",
"IT_NX",
"IT_V",
"IT_ND",
"IT_MF",
"IT_PD",
"IT_NJ",
"IT_SH",
"IT_TS",
"IT_DZ",
};


char *jplognames[]={
"SIL",
"J_I ",
"J_E ",
"J_A ",
"J_O ",
"J_U ",
"J_YE",
"J_YA",
"J_YO",
"J_YU",
"J_WI",
"J_WE",
"J_WA",
"J_WO",
"J_H" ,
"J_M" ,
"J_N",
"J_NG",
"J_EM",
"J_EN",
"J_NV",
"J_BH",
"J_F" ,
"J_DH",
"J_S" ,
"J_Z" ,
"J_CX",
"J_SH",
"J_ZH",
"J_GH",
"J_R",
"J_P",
"J_B",
"J_T",
"J_D",
"J_K" ,
"J_G ",
"J_TS",
"J_DZ",
"J_CH",
"J_JH",
};

char *krlognames[]={
"SIL",
"KR_IY",
"KR_EH",
"KR_AE",
"KR_UW",
"KR_UH",
"KR_UI",
"KR_OW",
"KR_AO",
"KR_AA",
"KR_YE",
"KR_YH",
"KR_YU",
"KR_YO",
"KR_YC",
"KR_YA",
"KR_WI",
"KR_WE",
"KR_WH",
"KR_WC",
"KR_WA",
"KR_M ",
"KR_N",
"KR_NX",
"KR_P",
"KR_PH",
"KR_PP",
"KR_B",
"KR_T",
"KR_TH",
"KR_TT",
"KR_D ",
"KR_K",
"KR_KH",
"KR_KK",
"KR_G",
"KR_S",
"KR_SS",
"KR_SH",
"KR_HX",
"KR_Y",
"KR_L",
"KR_DF",
"KR_JH",
 "KR_CH",
 "KR_CC",
 "KR_WO",
};




char *chlognames[]={
"SIL",
"CH_IY",
"CH_UE",
"CH_EY",
"CH_EH",
"CH_A",
"CH_IF",
"CH_IR",
"CH_AX",
"CH_UW",
"CH_UH",
"CH_UC",
"CH_OW",
"CH_WO",
"CH_AO",
"CH_AA",
"CH_AY",
"CH_AW",
"CH_ER",
"CH_M",
"CH_N",
"CH_NX",
"CH_P",
"CH_PV",
"CH_T",
"CH_TV",
"CH_K",
"CH_KV",
"CH_F",
"CH_S",
"CH_SR",
"CH_ZR",
"CH_TJ",
"CH_CH",
"CH_RF",
"CH_Y",
"CH_W",
"CH_L",
"CH_TS",
"CH_DS",
"CH_JJ",
"CH_JV",
"CH_T1",
"CH_D1",
"CH_KH",
"CH_YI",
"CH_WU",
"CH_AH",
"CH_XR",
"CH_AR",
"CH_OR",
"CH_1R",
"CH_WR",
"CH_2R",
"CH_UR",
"CH_3R",
"CH_4R",
"CH_5R",
"CH_YR",
"CH_X1",
"CH_X2",
"CH_X3",
"CH_X4",
"CH_X5",

};

char *helognames[]={
"GEN_SIL",
"HE_IY",
"HE_EY",
"HE_EH",
"HE_AU",
"HE_AH",
"HE_AO",
"HE_O ",
"HE_OY",
"HE_U ",
"HE_AX",
"HE_W ",
"HE_Y ",
"HE_R ",
"HE_H ",
"HE_L ",
"HE_M ",
"HE_N ",
"HE_F ",
"HE_V ",
"HE_TH",
"HE_S ",
"HE_Z ",
"HE_SH",
"HE_P ",
"HE_B ",
"HE_T ",
"HE_D ",
"HE_K ",
"HE_G ",
"HE_Q ",
"HE_JH",
"HE_TS",
"HE_CH",
"HE_E1",
"HE_A1",
"HE_O1",
"HE_O2",
"HE_YY",
"HE_RR",
"HE_HH",
"HE_LL",
"HE_MM",
"HE_NN",
"HE_VV",
"HE_SS",
"HE_ZZ",
"HE_PP",
"HE_BB",
"HE_TT",
"HE_T2",
"HE_DD",
"HE_C ",
"HE_KK",
"HE_GG",
"HE_AL",
"HE_NG",
"HE_CZ",
"HE_KZ",
"HE_TZ",

};

/* phoneme c is converted in an external code */
char* phprint (short c) 
{
	static char resu [10];

	if( ( (c & 0xFF00) == PFFR<<PSFONT) ) {
		c = (short) (c & 0x00FF);
		return flognames[c];
	}
	else if( ( (c & 0xFF00) == PFUSA<<PSFONT) ) {
		c = (short) (c & 0x00FF);
		return uslognames[c];
	}
	else if( ( (c & 0xFF00) == PFUK<<PSFONT) ) {
		c = (short) (c & 0x00FF);
		return uklognames[c];
	}
	else if ( ( (c & 0xFF00) == PFGR<<PSFONT) ) {
		c = (short) (c & 0x00FF);
		return grlognames[c];
	} 
	else if ( ( (c & 0xFF00) == PFSP<<PSFONT) ) {
		c = (short) (c & 0x00FF);
		return splognames[c];
	}
	else if ( ( (c & 0xFF00) == PFLA<<PSFONT) ) {
		c = (short) (c & 0x00FF);
		return lalognames[c];
	}
	else if ( ( (c & 0xFF00) == PFIT<<PSFONT) ) {
		c = (short) (c & 0x00FF);
		return itlognames[c];
	}
	else if ( ( (c & 0xFF00) == PFJP<<PSFONT) ) {
		c = (short) (c & 0x00FF);
		return jplognames[c];
	}
	else if ( ( (c & 0xFF00) == PFKR<<PSFONT) ) {
		c = (short) (c & 0x00FF);
		return krlognames[c];
	}
	else if ( ( (c & 0xFF00) == PFCH<<PSFONT) ) {
		c = (short) (c & 0x00FF);
		return chlognames[c];
	}
	else if ( ( (c & 0xFF00) == PFHE<<PSFONT) ) {
		c = (short) (c & 0x00FF);
		return helognames[c];
	}
	else {
		switch (c) {
			case FinNorm:   return ".";
			case FSyntVirg: return ",";
			case FinInterr: return "?";
			case FrontMot:  return " ";
			default : 
			  FNX_SPRINTF (resu,"<%4x>", c);
			  return resu;
		}
	}

	/* else if( ( (c&0xFF00) == 0x1d00) ) {
	c = (short) (c&0x00FF);

	switch(c) {
	case CgBas:     return("<Bas>");
	case CgConj:     return("<Conj>");
	case CgPPS:      return("<PPS>");
	case CgVA:       return("<VA>");
	case CgArt:     return("<Art>");
	case CgDivers:   return("<Divers>");
	case CgPrep:    return("<Prep>");
	case CgPosDem:  return("<PosDem>");
	case CgInterr:   return("<Interr>");
	case CgDe:       return("<De>");
	case CgPrep2:    return("<Prep2>");
	case CgAV:      return("<AV>");
	default:
	FNX_SPRINTF(resu,"<%4x>",c);
	return(resu);
	}

	} else {
	FNX_SPRINTF resu,"<%4x>",c);
	return resu);
	} 

	return(" <?? phoneme inconnu> "); */

} /* phprint */