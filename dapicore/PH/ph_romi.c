 /* 
 ********************************************************************************************
 *
 *                           Copyright �
 *	  Copyright � 2002 Fonix Corporation. All rights reserved.
 *	  Copyright � 2000, 2001 Force Computers, Inc., a Solectron Company. All rights reserved.
 *    � Digital Equipment Corporation 1996, 1997. All rights reserved.
 *
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Fonix Corporation and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Fonix or an
 *    authorized sublicensor.
 *
 ********************************************************************************************
 *    File Name:    ph_romi.c
 *    Author:       Matthew Schnee
 *    Creation Date:06-Jun-1996
 *
 *    Functionality:
 *  	PH tables for phomemes
 *
 ********************************************************************************************
 *    Revision History:
 *	Rev	Who		Date		Description
 *	---	-----	-----------	-----------------------------------------------------------------
 *	001	MGS		06/06/1996	Initial creation
 *  002	GL		04/21/1997	BATS#360  remove spaces before "#define" or "#if" 
 *  003 DR		09/30/1997	UK BUILD: added UK STUFF
 *  004 EAB		01/16/1998  Moved language independent parameters to common file
							Needed for Bats 577
 *							This is needed for phedit when complete no ifdef will be needed
							as all versions will share these common files. Cosine  values are the same
							for all languages. 
 *  005 EAB		07/14/1998  For AD we've reached the point of no ifdef's required everything
							is to PHEDIT for rom code.
 *  006 EAB		07/20/1998	Needs SPANISH_LA and SPANISH_SP to differentiate rom files.
 *  007 EAB 	10/11/2000 	Merge Spaniush to one fbountab
 *  008 CAB		10/18/2000	Changed copyright info and formatted comments
 *  009	MFG		05/29/2001	Included dectalkf.h
 *  010	CAB		06/01/2001	Updated copyright info
 *  011	MGS		04/11/2002	ARM7 port
 *	012	CAB		05/23/2002	Updated copyright info
 */

/* Arrays used by the phonetic component */

#include "dectalkf.h"
#include "ph_def.h"            

#ifndef OS_PALM
#include "p_fr_rom.h"
#include "p_gr_rom.h"
#include "p_us_rom.h"
#include "p_uk_rom.h"
#include "p_sp_rom.h"
#include "p_la_rom.h" 
#include "p_it_rom.h"
#include "p_ch_rom.h"
#include "p_kr_rom.h"
#include "p_hb_rom.h"
#include "p_jp_rom.h"
#endif //OS_PALM

#include "p_us_sue.h"
#include "p_us_ed.h"
#include "p_us_ken.h"
#include "p_us_ali.h"

#ifdef OS_PALM
#pragma pcrelconstdata off
#endif

const short getcosine[64] =
{
	164, 163, 161, 158, 154, 148, 141, 132,
	123, 112, 100, 86, 72, 56, 38, 20,
	0, -20, -38, -56, -72, -86, -100, -112,
	-123, -132, -141, -148, -154, -158, -161, -163,
	-164, -163, -161, -158, -154, -148, -141, -132,
	-123, -112, -100, -86, -72, -56, -38, -20,
	0, 20, 38, 56, 72, 86, 100, 112,
	123, 132, 141, 148, 154, 158, 161, 163,
};

#ifdef OS_PALM
#pragma pcrelconstdata on
#endif

/* Linearize the TILT variable */
/* E.g. if you request 3 dB of tilt, must send 12 to chip to get 3 */

const short lineartilt[32] =
{
	0, 6, 8, 12, 15, 17, 19, 21, 23, 25,
	26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
	35, 36, 36, 37, 37, 38, 38, 39, 39, 39,
	40, 40
};

/* Notes in F0*10 from C2 to C5 */
#ifdef OS_PALM
#pragma pcrelconstdata off
#endif
const short notetab[] =
{
	640,							   /* 1 = C2              */
	678,							   /* 2 = C#              */
	718,							   /* 3 = D               */
	761,							   /* 4 = D#              */
	806,							   /* 5 = E    B                  (HARRY)         */
	854,							   /* 6 = F    A          */
	905,							   /* 7 = F#   S          */
	959,							   /* 8 = G    S B                (PAUL)          */
	1016,							   /* 9 = G#   | A        */
	1076,							   /* 10 = A    | R        */
	1140,							   /* 11 = A#   | A        */
	1208,							   /* 12 = B    | T        */
	1280,							   /* 13 = C3   | O T              (FRANK)         */
	1356,							   /* 14 = C#   | N E      */
	1437,							   /* 15 = D    | E N      */
	1522,							   /* 16 = D#   | | O      */
	1613,							   /* 17 = E    | | R      */
	1709,							   /* 18 = F    | | | A            (BETTY)         */
	1810,							   /* 19 = F#   | | | L    */
	1918,							   /* 20 = G    | | | T    */
	2032,							   /* 21 = G#   | | | O    */
	2152,							   /* 22 = A    | | | |    */
	2280,							   /* 23 = A#   | | | |    */
	2416,							   /* 24 = B    | | | | S          (URSULA or KIT) */
	2560,							   /* 25 = C4   | B | | O  */
	2712,							   /* 26 = C#   B A | | P  */
	2874,							   /* 27 = D    A R | | R  */
	3044,							   /* 28 = D#   A A | | A  */
	3226,							   /* 29 = E    S T | | N  */
	3418,							   /* 30 = F      O | | O  */
	3620,							   /* 31 = F#     N | | |  */
	3836,							   /* 32 = G      E T | |  */
	4064,							   /* 33 = G#       E | |  */
	4304,							   /* 34 = A        N | |  */
	4560,							   /* 35 = A#       O | |  */
	4832,							   /* 36 = B        R | |  */
	5120							   /* 37 = C5         | |  */
};
/* Switch to set target to const, taram[ptram], or flocu[plocu] */
#ifdef OS_PALM
#pragma pcrelconstdata on
#endif

const char partyp[] =
{
	  /* F1   F2   F3   FZ   B1   B2   B3   AV              */
	3, 3, 3, 1, 4, 4, 4, 0,
	  /* AP   A2   A3   A4   A5   A6   AB   TILT            */
	0, 2, 2, 2, 2, 2, 2, 2
};

/* Table to permit use of mulsh() for division by 1 to 20 */

const short divtab[] =
{
	16384, 16384, 8192, 5461, 4096,
	3276, 2730, 2340, 2048, 1820,
	1638, 1489, 1365, 1260, 1170,
	1092, 1024, 964, 910, 862,
	819, 780, 745, 712, 682,
	655, 630, 607, 585, 565,
	546, 528, 512, 496, 482,
	468, 455, 443, 431, 420,
	409, 399, 390, 381, 372,
	364, 356, 349, 341, 334
};
/* Initial values for parameters */

const short parini[] =
{
	  /* F1   F2   F3   FZ   B1   B2   B3   AV              */
	600, 1600, 2600, 300, 50, 150, 250, 0,
	  /* AP   A2   A3   A4   A5   A6   AB   TILT            */
	0, 0, 0, 0, 0, 0, 0, 0
};
#ifdef OS_PALM
#pragma pcrelconstdata off
#endif

#ifdef SPANISH_not //with merged bits

/* Feature value bits for each boundary symbol in input */

const U32 bounftab[EXCLAIM - SBOUND + 1] =
{
	FSBOUND,						   /* SBOUND       */
	FMBNEXT,						   /* MBOUND       */
	FMBNEXT,						   /* HYPHEN       */
	FWBNEXT,						   /* WBOUND       */
	FPPNEXT,						   /* PPSTART      */
	FVPNEXT,						   /* VPSTART      */
	FRELNEXT,						   /* RELSTART     */
	FCBNEXT,						   /* COMMA        */
	FPERNEXT,						   /* PERIOD       */
	FQUENEXT,						   /* QUEST        */
	FEXCLNEXT						   /* EXCLAIM      */
};
#else
/* Feature value bits for each boundary symbol in input */

const short bounftab[] =
{

	FSYBNEXT,						   /* SBOUND       */
	FMBNEXT,						   /* MBOUND       */
	FMBNEXT,						   /* HYPHEN       */
	FWBNEXT,						   /* WBOUND       */
	FPPNEXT,						   /* PPSTART      */
	FVPNEXT,						   /* VPSTART      */
	FRELNEXT,						   /* RELSTART     */
	FCBNEXT,						   /* COMMA        */
	FPERNEXT,						   /* PERIOD       */
	FQUENEXT,						   /* QUEST        */
	FEXCLNEXT						   /* EXCLAIM      */
};
#endif

#ifndef OS_PALM
#ifdef USING_MULTIPLE_VOICE_TABLES
const int *all_featb[32] = {
/* 00 */	us_featb_def,
/* 01 */	us_featb_def,
/* 02 */	uk_featb_def,
/* 03 */	gr_featb_def,
/* 04 */	sp_featb_def,
/* 05 */	la_featb_def,
/* 06 */	fr_featb,
/* 07 */	it_featb_def,
/* 08 */	NULL,
/* 09 */	NULL,
/* 0A */	NULL,
/* 0B */	NULL,
/* 0C */	NULL,
/* 0D */	NULL,
/* 0E */	NULL,
/* 0F */	NULL,
/* 10 */	NULL,
/* 11 */	NULL,
/* 12 */	NULL,
/* 13 */	NULL,
/* 14 */	NULL,
/* 15 */	NULL,
/* 16 */	NULL,
/* 17 */	NULL,
/* 18 */	NULL,
/* 19 */	NULL,
/* 1A */	NULL,
/* 1B */	NULL,
/* 1C */	NULL,
/* 1D */	NULL,
/* 1E */	NULL,
/* 1F */	NULL
};

const short *all_place[32] = {
/* 00 */	us_place_def,
/* 01 */	us_place_def,
/* 02 */	uk_place_def,
/* 03 */	gr_place_def,
/* 04 */	sp_place_def,
/* 05 */	la_place_def,
/* 06 */	fr_place_def,
/* 07 */	it_place_def,
/* 08 */	NULL,
/* 09 */	NULL,
/* 0A */	NULL,
/* 0B */	NULL,
/* 0C */	NULL,
/* 0D */	NULL,
/* 0E */	NULL,
/* 0F */	NULL,
/* 10 */	NULL,
/* 11 */	NULL,
/* 12 */	NULL,
/* 13 */	NULL,
/* 14 */	NULL,
/* 15 */	NULL,
/* 16 */	NULL,
/* 17 */	NULL,
/* 18 */	NULL,
/* 19 */	NULL,
/* 1A */	NULL,
/* 1B */	NULL,
/* 1C */	NULL,
/* 1D */	NULL,
/* 1E */	NULL,
/* 1F */	NULL
};

const short *all_begtyp[32] = {
/* 00 */	us_begtyp_def,
/* 01 */	us_begtyp_def,
/* 02 */	uk_begtyp_def,
/* 03 */	gr_begtyp_def,
/* 04 */	sp_begtyp_def,
/* 05 */	la_begtyp_def,
/* 06 */	fr_begtyp,
/* 07 */	it_begtyp_def,
/* 08 */	NULL,
/* 09 */	NULL,
/* 0A */	NULL,
/* 0B */	NULL,
/* 0C */	NULL,
/* 0D */	NULL,
/* 0E */	NULL,
/* 0F */	NULL,
/* 10 */	NULL,
/* 11 */	NULL,
/* 12 */	NULL,
/* 13 */	NULL,
/* 14 */	NULL,
/* 15 */	NULL,
/* 16 */	NULL,
/* 17 */	NULL,
/* 18 */	NULL,
/* 19 */	NULL,
/* 1A */	NULL,
/* 1B */	NULL,
/* 1C */	NULL,
/* 1D */	NULL,
/* 1E */	NULL,
/* 1F */	NULL
};

const short *all_endtyp[32] = {
/* 00 */	us_endtyp_def,
/* 01 */	us_endtyp_def,
/* 02 */	uk_endtyp_def,
/* 03 */	gr_endtyp_def,
/* 04 */	sp_endtyp_def,
/* 05 */	la_endtyp_def,
/* 06 */	fr_endtyp,
/* 07 */	it_endtyp_def,
/* 08 */	NULL,
/* 09 */	NULL,
/* 0A */	NULL,
/* 0B */	NULL,
/* 0C */	NULL,
/* 0D */	NULL,
/* 0E */	NULL,
/* 0F */	NULL,
/* 10 */	NULL,
/* 11 */	NULL,
/* 12 */	NULL,
/* 13 */	NULL,
/* 14 */	NULL,
/* 15 */	NULL,
/* 16 */	NULL,
/* 17 */	NULL,
/* 18 */	NULL,
/* 19 */	NULL,
/* 1A */	NULL,
/* 1B */	NULL,
/* 1C */	NULL,
/* 1D */	NULL,
/* 1E */	NULL,
/* 1F */	NULL
};

const short *all_ptram[32] = {
/* 00 */	us_ptram_def,
/* 01 */	us_ptram_def,
/* 02 */	uk_ptram_def,
/* 03 */	gr_ptram_def,
/* 04 */	sp_ptram_def,
/* 05 */	la_ptram_def,
/* 06 */	fr_ptram,
/* 07 */	it_ptram_def,
/* 08 */	NULL,
/* 09 */	NULL,
/* 0A */	NULL,
/* 0B */	NULL,
/* 0C */	NULL,
/* 0D */	NULL,
/* 0E */	NULL,
/* 0F */	NULL,
/* 10 */	NULL,
/* 11 */	NULL,
/* 12 */	NULL,
/* 13 */	NULL,
/* 14 */	NULL,
/* 15 */	NULL,
/* 16 */	NULL,
/* 17 */	NULL,
/* 18 */	NULL,
/* 19 */	NULL,
/* 1A */	NULL,
/* 1B */	NULL,
/* 1C */	NULL,
/* 1D */	NULL,
/* 1E */	NULL,
/* 1F */	NULL
};

const short *all_burdr[32] = {
/* 00 */	us_burdr_def,
/* 01 */	us_burdr_def,
/* 02 */	uk_burdr_def,
/* 03 */	gr_burdr_def,
/* 04 */	sp_burdr_def,
/* 05 */	la_burdr_def,
/* 06 */	fr_burdr,
/* 07 */	it_burdr_def,
/* 08 */	NULL,
/* 09 */	NULL,
/* 0A */	NULL,
/* 0B */	NULL,
/* 0C */	NULL,
/* 0D */	NULL,
/* 0E */	NULL,
/* 0F */	NULL,
/* 10 */	NULL,
/* 11 */	NULL,
/* 12 */	NULL,
/* 13 */	NULL,
/* 14 */	NULL,
/* 15 */	NULL,
/* 16 */	NULL,
/* 17 */	NULL,
/* 18 */	NULL,
/* 19 */	NULL,
/* 1A */	NULL,
/* 1B */	NULL,
/* 1C */	NULL,
/* 1D */	NULL,
/* 1E */	NULL,
/* 1F */	NULL
};

const short *all_plocu[32] = {
/* 00 */	us_plocu_def,
/* 01 */	us_plocu_def,
/* 02 */	uk_plocu_def,
/* 03 */	gr_plocu_def,
/* 04 */	sp_plocu_def,
/* 05 */	la_plocu_def,
/* 06 */	fr_plocu,
/* 07 */	it_plocu_def,
/* 08 */	NULL,
/* 09 */	NULL,
/* 0A */	NULL,
/* 0B */	NULL,
/* 0C */	NULL,
/* 0D */	NULL,
/* 0E */	NULL,
/* 0F */	NULL,
/* 10 */	NULL,
/* 11 */	NULL,
/* 12 */	NULL,
/* 13 */	NULL,
/* 14 */	NULL,
/* 15 */	NULL,
/* 16 */	NULL,
/* 17 */	NULL,
/* 18 */	NULL,
/* 19 */	NULL,
/* 1A */	NULL,
/* 1B */	NULL,
/* 1C */	NULL,
/* 1D */	NULL,
/* 1E */	NULL,
/* 1F */	NULL
};

#endif //OS_PALM

//short *inhdr              = uk_inhdr;
//short *mindur             = uk_mindur;
//short *burdr              = uk_burdr;
//short *f0segtars          = uk_f0segtars;
//short *begtyp             = uk_begtyp;
//short *endtyp             = uk_endtyp;
//short *place              = uk_place;
//short *featb              = uk_featb;
//short *femtar             = uk_femtar;
//short *maldip             = uk_maldip;
//short *femdip             = uk_femdip;
//short *ptram              = uk_ptram;
//short *malamp             = uk_malamp;
//short *femamp             = uk_femamp;
//short *plocu              = uk_plocu;
//short *maleloc            = uk_maleloc;
//short *femloc             = uk_femloc;
//short *f0glstp            = uk_f0glstp;
//short *f0_phrase_position = uk_f0_phrase_position;
//short *f0_stress_level    = uk_f0_stress_level;

#endif

#ifdef OS_PALM
#pragma pcrelconstdata on
#endif
