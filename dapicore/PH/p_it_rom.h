// PH Rom file
//
// Copyright Information:
// 
//                           Copyright (c)
//    Copyright © 2002 Fonix Corporation. All rights reserved.
//    Copyright © 2000-2001 Force Computers, a Solectron Company. All rights reserved.
//    © Digital Equipment Corporation 1996, 1997, 1998. All rights reserved.
// 
//    Restricted Rights: Use, duplication, or disclosure by the U.S.
//    Government is subject to restrictions as set forth in subparagraph
//    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
//    52.227-14 Alt. III, as applicable.
// 
// 
//    This software is proprietary to and embodies the confidential
//    technology of Fonix Corporation and other parties.
//    Possession, use, or copying of this software and media is authorized
//    only pursuant to a valid written license from Fonix or an
//    authorized sublicensor.
// 
// Based on Dennis Klatt's PHRom File Format  Copyright (c) 1988 by Dennis Klatt
//
// Compile Type: Compiled from (-1/-1)
// Program: PHEdit(5.x)
//

#define IT_PH_PHONEME_COUNT 43
#define IT_PH_PHONEME_NAMES " _ AP EP IY OP UW AX Y RR L LL M N NH F S EH TD BD DD GD JH P B T D K G CH AO R KD Z W NX V ND MF PD NJ SH TS DZ "

// Inherent Duration (milliseconds)
const short it_inhdr_def[] = {
 300, 	// _
 120, 	// AP
 130, 	// EP
 120, 	// IY
 120, 	// OP
 110, 	// UW
 98, 	// AX
 80, 	// Y
 140, 	// RR
 100, 	// L
 60, 	// LL
 75, 	// M
 95, 	// N
 90, 	// NH
 100, 	// F
 125, 	// S
 118, 	// EH
 100, 	// TD
 90, 	// BD
 80, 	// DD
 80, 	// GD
 100, 	// JH
 75, 	// P
 90, 	// B
 85, 	// T
 80, 	// D
 120, 	// K
 60, 	// G
 150, 	// CH
 126, 	// AO
 90, 	// R
 120, 	// KD
 120, 	// Z
 65, 	// W
 100, 	// NX
 120, 	// V
 95, 	// ND
 90, 	// MF
 100, 	// PD
 90, 	// NJ
 125, 	// SH
 180, 	// TS
 165 }; 	//DZ

// Minimum Duration (milliseconds)
const short it_mindur_def[] = {
 300, 	// _
 50, 	// AP
 80, 	// EP
 80, 	// IY
 55, 	// OP
 80, 	// UW
 50, 	// AX
 70, 	// Y
 70, 	// RR
 60, 	// L
 30, 	// LL
 50, 	// M
 50, 	// N
 45, 	// NH
 60, 	// F
 65, 	// S
 55, 	// EH
 60, 	// TD
 60, 	// BD
 70, 	// DD
 50, 	// GD
 75, 	// JH
 45, 	// P
 60, 	// B
 50, 	// T
 70, 	// D
 90, 	// K
 50, 	// G
 140, 	// CH
 55, 	// AO
 40, 	// R
 90, 	// KD
 70, 	// Z
 30, 	// W
 60, 	// NX
 60, 	// V
 50, 	// ND
 60, 	// MF
 80, 	// PD
 45, 	// NJ
 60, 	// SH
 120, 	// TS
 120 };	//DZ

// Burst Duration (milliseconds)
const short it_burdr_def[] = {
 0, 	//_
 0, 	//AP
 0, 	//EP
 0, 	//IY
 0, 	//OP
 0, 	//UW
 0, 	//AX
 0, 	//Y
 0, 	//RR
 0, 	//L
 0, 	//LL
 0, 	//M
 0, 	//N
 0, 	//NH
 0, 	//F
 0, 	//S
 0, 	//EH
 0, 	//TD
 0, 	//BD
 15, 	//DD
 0, 	//GD
 45, 	//JH
 16, 	//P
 7, 	//B
 7, 	//T
 15, 	//D
 26, 	//K
 26, 	//G
 75, 	//CH
 0, 	//AO
 0, 	//R
 0, 	//KD
 0, 	//Z
 0, 	//W
 0, 	//NX
 0, 	//V
 0, 	//ND
 0, 	//MF
 0, 	//PD
 0, 	//NJ
 0, 	//SH
 80, 	//TS
 60 };	//DZ

// Beginning Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short it_begtyp_def[] = {
 4, 	// _
 2, 	// AP
 1, 	// EP
 1, 	// IY
 3, 	// OP
 3, 	// UW
 2, 	// AX
 1, 	// Y
 3, 	// RR
 5, 	// L
 3, 	// LL
 4, 	// M
 4, 	// N
 4, 	// NH
 4, 	// F
 4, 	// S
 1, 	// EH
 4, 	// TD
 4, 	// BD
 4, 	// DD
 4, 	// GD
 4, 	// JH
 4, 	// P
 4, 	// B
 4, 	// T
 4, 	// D
 4, 	// K
 4, 	// G
 4, 	// CH
 3, 	// AO
 4, 	// R
 4, 	// KD
 4, 	// Z
 4, 	// W
 4, 	// NX
 4, 	// V
 4, 	// ND
 4, 	// MF
 4, 	// PD
 4, 	// NJ
 4, 	// SH
 4, 	// TS
 4 };	// DZ

// Ending Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short it_endtyp_def[] = {
 4, 	// _
 2, 	// AP
 1, 	// EP
 1, 	// IY
 3, 	// OP
 3, 	// UW
 2, 	// AX
 1, 	// Y
 3, 	// RR
 4, 	// L
 3, 	// LL
 4, 	// M
 4, 	// N
 4, 	// NH
 4, 	// F
 4, 	// S
 1, 	// EH
 4, 	// TD
 4, 	// BD
 4, 	// DD
 4, 	// GD
 4, 	// JH
 4, 	// P
 4, 	// B
 4, 	// T
 4, 	// D
 4, 	// K
 4, 	// G
 4, 	// CH
 3, 	// AO
 4, 	// R
 4, 	// KD
 4, 	// Z
 4, 	// W
 4, 	// NX
 4, 	// V
 4, 	// ND
 4, 	// MF
 4, 	// PD
 4, 	// NJ
 4, 	// SH
 4, 	// TS
 4 };	// DZ

// Place of articulation
// FLABIAL		0x0001
// FDENTAL		0x0002
// FPALATL		0x0004
// FALVEL		0x0008
// FVELAR		0x0010
// FGLOTAL		0x0020
// F2BACKI		0x0040
// F2BACKF		0x0080
// FLABIALDENTAL	0x0100
// FPOSTALVEOLAR	0x0200
// FUVULAR		0x0400
// FPHARYNGEAL	0x0800
// FVELARF		0x1000
// FVELARB		0x2000
// FVELARR		0x4000
const short it_place_def[] = {
 0x0000, 	// _
 0x0000, 	// AP
 0x0000, 	// EP
 0x00c0, 	// IY
 0x0000, 	// OP
 0x0000, 	// UW
 0x0000, 	// AX
 0x00c0, 	// Y
 0x0008, 	// RR
 0x0000, 	// L
 0x0000, 	// LL
 0x0001, 	// M
 0x0008, 	// N
 0x0004, 	// NH
 0x0001, 	// F
 0x0008, 	// S
 0x0000, 	// EH
 0x0002, 	// TD
 0x0001, 	// BD
 0x0002, 	// DD
 0x0010, 	// GD
 0x0004, 	// JH
 0x0001, 	// P
 0x0001, 	// B
 0x0002, 	// T
 0x0002, 	// D
 0x0010, 	// K
 0x0010, 	// G
 0x0004, 	// CH
 0x0000, 	// AO
 0x0008, 	// R
 0x0010, 	// KD
 0x0008, 	// Z
 0x0000, 	// W
 0x0010, 	// NX
 0x0001, 	// V
 0x0002, 	// ND
 0x0001, 	// MF
 0x0001, 	// PD
 0x0004, 	// NJ
 0x0004, 	// SH
 0x0008, 	// TS
 0x0002 };	// DZ

// Feature bits
// FSYLL		0x00000001
// FVOICD		0x00000002
// FVOWEL		0x00000004
// FSON1		0x00000008
// FSONOR		0x00000010
// FOBST		0x00000020
// FPLOSV		0x00000040
// FNASAL		0x00000080
// FCONSON		0x00000100
// FSONCON		0x00000200
// FSON2		0x00000400
// FBURST		0x00000800
// FSTMARK		0x00001000
// FSTOP		0x00002000
// FFLAP		0x00004000
// FLATERAL		0x00008000
// FRETROFLEX	0x00010000
// FNFI1		0x00020000
// FNFI2		0x00040000
// FNFI3		0x00080000
const int it_featb_def[] = {
 0x00000010, 	// _
 0x0000001f, 	// AP
 0x0000001f, 	// EP
 0x0000041f, 	// IY
 0x0000001f, 	// OP
 0x0000041f, 	// UW
 0x0000041f, 	// AX
 0x0000071a, 	// Y
 0x0000011a, 	// RR
 0x0000071a, 	// L
 0x0000011a, 	// LL
 0x0000259a, 	// M
 0x0000259a, 	// N
 0x0000059a, 	// NH
 0x00000120, 	// F
 0x00000120, 	// S
 0x0000001f, 	// EH
 0x00002160, 	// TD
 0x00002962, 	// BD
 0x00002162, 	// DD
 0x00002162, 	// GD
 0x00002922, 	// JH
 0x00002960, 	// P
 0x00002962, 	// B
 0x00002960, 	// T
 0x00002962, 	// D
 0x00002960, 	// K
 0x00002962, 	// G
 0x00002920, 	// CH
 0x0000001f, 	// AO
 0x0000011a, 	// R
 0x00002960, 	// KD
 0x00000122, 	// Z
 0x0000013a, 	// W
 0x00000192, 	// NX
 0x00000112, 	// V
 0x00000592, 	// ND
 0x00000192, 	// MF
 0x00002160, 	// PD
 0x0000259a, 	// NJ
 0x00000120, 	// SH
 0x00002920, 	// TS
 0x00002922, 	// DZ
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
0 };

// Male - F1,F2,F3,B1,B2,B3,AV data for each phoneme
//     Negative numbers are offsets into maldip table (multi-part formants)
//     Positive numbers are actual values
const short it_maltar_def[] = {
// ==== F1 ====
 -1, 	// _
 765, 	// AP
 395, 	// EP
 300, 	// IY
 445, 	// OP
 325, 	// UW
 550, 	// AX
 310, 	// Y
 480, 	// RR
 377, 	// L
 380, 	// LL
 300, 	// M
 280, 	// N
 280, 	// NH
 340, 	// F
 320, 	// S
 540, 	// EH
 386, 	// TD
 220, 	// BD
 300, 	// DD
 180, 	// GD
 280, 	// JH
 350, 	// P
 220, 	// B
 350, 	// T
 300, 	// D
 280, 	// K
 210, 	// G
 475, 	// CH
 560, 	// AO
 374, 	// R
 220, 	// KD
 310, 	// Z
 295, 	// W
 430, 	// NX
 325, 	// V
 180, 	// ND
 400, 	// MF
 350, 	// PD
 280, 	// NJ
 300, 	// SH
 500, 	// TS
 300, 	// DZ
// ==== F2 ====
 -1, 	// _
 1240, 	// AP
 2000, 	// EP
 2100, 	// IY
 775, 	// OP
 715, 	// UW
 1260, 	// AX
 2200, 	// Y
 1550, 	// RR
 1300, 	// L
 800, 	// LL
 1197, 	// M
 1461, 	// N
 2000, 	// NH
 1100, 	// F
 1520, 	// S
 1870, 	// EH
 1523, 	// TD
 900, 	// BD
 1595, 	// DD
 1335, 	// GD
 1730, 	// JH
 1000, 	// P
 900, 	// B
 1700, 	// T
 1650, 	// D
 1790, 	// K
 1700, 	// G
 1800, 	// CH
 885, 	// AO
 1315, 	// R
 1800, 	// KD
 1420, 	// Z
 610, 	// W
 1600, 	// NX
 1100, 	// V
 1461, 	// ND
 1400, 	// MF
 1000, 	// PD
 2000, 	// NJ
 1600, 	// SH
 1880, 	// TS
 1529, 	// DZ
// ==== F3 ====
 -1, 	// _
 2400, 	// AP
 2482, 	// EP
 2900, 	// IY
 2317, 	// OP
 2522, 	// UW
 2600, 	// AX
 2900, 	// Y
 2600, 	// RR
 2800, 	// L
 2500, 	// LL
 2327, 	// M
 2498, 	// N
 2990, 	// NH
 2080, 	// F
 2700, 	// S
 2466, 	// EH
 2488, 	// TD
 1800, 	// BD
 2546, 	// DD
 2390, 	// GD
 2700, 	// JH
 2100, 	// P
 1800, 	// B
 2600, 	// T
 2600, 	// D
 2400, 	// K
 2520, 	// G
 2700, 	// CH
 2582, 	// AO
 1850, 	// R
 2400, 	// KD
 2600, 	// Z
 2250, 	// W
 2100, 	// NX
 2144, 	// V
 2498, 	// ND
 2500, 	// MF
 2100, 	// PD
 2990, 	// NJ
 2350, 	// SH
 2710, 	// TS
 2600, 	// DZ
// ==== B1 ====
 250, 	// _
 100, 	// AP
 110, 	// EP
 90, 	// IY
 100, 	// OP
 120, 	// UW
 100, 	// AX
 100, 	// Y
 200, 	// RR
 120, 	// L
 60, 	// LL
 130, 	// M
 140, 	// N
 105, 	// NH
 300, 	// F
 300, 	// S
 240, 	// EH
 300, 	// TD
 110, 	// BD
 90, 	// DD
 90, 	// GD
 70, 	// JH
 160, 	// P
 110, 	// B
 200, 	// T
 90, 	// D
 200, 	// K
 90, 	// G
 250, 	// CH
 90, 	// AO
 200, 	// R
 200, 	// KD
 140, 	// Z
 50, 	// W
 90, 	// NX
 140, 	// V
 140, 	// ND
 90, 	// MF
 160, 	// PD
 105, 	// NJ
 200, 	// SH
 300, 	// TS
 300, 	// DZ
// ==== B2 ====
 250, 	// _
 150, 	// AP
 160, 	// EP
 200, 	// IY
 150, 	// OP
 180, 	// UW
 150, 	// AX
 200, 	// Y
 200, 	// RR
 150, 	// L
 170, 	// LL
 150, 	// M
 350, 	// N
 425, 	// NH
 150, 	// F
 150, 	// S
 150, 	// EH
 150, 	// TD
 110, 	// BD
 80, 	// DD
 120, 	// GD
 170, 	// JH
 150, 	// P
 110, 	// B
 150, 	// T
 80, 	// D
 160, 	// K
 120, 	// G
 250, 	// CH
 100, 	// AO
 60, 	// R
 160, 	// KD
 100, 	// Z
 80, 	// W
 250, 	// NX
 120, 	// V
 350, 	// ND
 250, 	// MF
 150, 	// PD
 425, 	// NJ
 240, 	// SH
 150, 	// TS
 150, 	// DZ
// ==== B3 ====
 250, 	// _
 200, 	// AP
 200, 	// EP
 250, 	// IY
 200, 	// OP
 250, 	// UW
 250, 	// AX
 400, 	// Y
 200, 	// RR
 110, 	// L
 250, 	// LL
 250, 	// M
 350, 	// N
 450, 	// NH
 150, 	// F
 150, 	// S
 150, 	// EH
 250, 	// TD
 130, 	// BD
 240, 	// DD
 180, 	// GD
 250, 	// JH
 180, 	// P
 130, 	// B
 250, 	// T
 240, 	// D
 280, 	// K
 180, 	// G
 250, 	// CH
 200, 	// AO
 130, 	// R
 280, 	// KD
 300, 	// Z
 80, 	// W
 150, 	// NX
 120, 	// V
 350, 	// ND
 150, 	// MF
 180, 	// PD
 450, 	// NJ
 300, 	// SH
 250, 	// TS
 250, 	// DZ
// ==== AV ====
 0, 	// _
 62, 	// AP
 65, 	// EP
 63, 	// IY
 63, 	// OP
 64, 	// UW
 64, 	// AX
 64, 	// Y
 60, 	// RR
 64, 	// L
 60, 	// LL
 64, 	// M
 65, 	// N
 64, 	// NH
 0, 	// F
 0, 	// S
 65, 	// EH
 0, 	// TD
 0, 	// BD
 0, 	// DD
 0, 	// GD
 0, 	// JH
 0, 	// P
 0, 	// B
 0, 	// T
 0, 	// D
 0, 	// K
 0, 	// G
 0, 	// CH
 65, 	// AO
 58, 	// R
 0, 	// KD
 50, 	// Z
 62, 	// W
 60, 	// NX
 50, 	// V
 62, 	// ND
 64, 	// MF
 0, 	// PD
 58, 	// NJ
 0, 	// SH
 0, 	// TS
 0 };	// DZ

// Female - F1,F2,F3,B1,B2,B3,AV data for each phoneme
//     Negative numbers are offsets into femdip table (multi-part formants)
//     Positive numbers are actual values
const short it_femtar_def[] = {
// ==== F1 ====
 -1, 	// _
 976, 	// AP
 515, 	// EP
 472, 	// IY
 -2, 	// OP
 488, 	// UW
 666, 	// AX
 320, 	// Y
 480, 	// RR
 400, 	// L
 390, 	// LL
 300, 	// M
 450, 	// N
 280, 	// NH
 320, 	// F
 340, 	// S
 730, 	// EH
 350, 	// TD
 310, 	// BD
 310, 	// DD
 180, 	// GD
 220, 	// JH
 310, 	// P
 310, 	// B
 370, 	// T
 220, 	// D
 180, 	// K
 220, 	// G
 475, 	// CH
 650, 	// AO
 350, 	// R
 180, 	// KD
 310, 	// Z
 310, 	// W
 400, 	// NX
 280, 	// V
 180, 	// ND
 400, 	// MF
 310, 	// PD
 365, 	// NJ
 320, 	// SH
 290, 	// TS
 290, 	// DZ
// ==== F2 ====
 -1, 	// _
 1546, 	// AP
 2360, 	// EP
 2238, 	// IY
 -6, 	// OP
 1098, 	// UW
 1580, 	// AX
 2537, 	// Y
 1743, 	// RR
 1400, 	// L
 1200, 	// LL
 1444, 	// M
 1800, 	// N
 2000, 	// NH
 800, 	// F
 1730, 	// S
 2075, 	// EH
 2182, 	// TD
 1735, 	// BD
 1495, 	// DD
 890, 	// GD
 2100, 	// JH
 1500, 	// P
 1150, 	// B
 1860, 	// T
 1860, 	// D
 2336, 	// K
 2190, 	// G
 2100, 	// CH
 920, 	// AO
 1450, 	// R
 2336, 	// KD
 1520, 	// Z
 610, 	// W
 1200, 	// NX
 1250, 	// V
 1600, 	// ND
 1400, 	// MF
 1800, 	// PD
 1900, 	// NJ
 1980, 	// SH
 2000, 	// TS
 2000, 	// DZ
// ==== F3 ====
 -1, 	// _
 2888, 	// AP
 3051, 	// EP
 3033, 	// IY
 3051, 	// OP
 2929, 	// UW
 2832, 	// AX
 2955, 	// Y
 2550, 	// RR
 2910, 	// L
 2815, 	// LL
 2457, 	// M
 2800, 	// N
 2990, 	// NH
 2715, 	// F
 2800, 	// S
 2970, 	// EH
 2888, 	// TD
 2150, 	// BD
 2789, 	// DD
 2817, 	// GD
 3150, 	// JH
 2716, 	// P
 2150, 	// B
 3020, 	// T
 3020, 	// D
 2400, 	// K
 2710, 	// G
 2700, 	// CH
 2700, 	// AO
 2550, 	// R
 2400, 	// KD
 2800, 	// Z
 2250, 	// W
 2800, 	// NX
 2700, 	// V
 2800, 	// ND
 2500, 	// MF
 2716, 	// PD
 2630, 	// NJ
 2930, 	// SH
 3100, 	// TS
 3100, 	// DZ
// ==== B1 ====
 250, 	// _
 100, 	// AP
 100, 	// EP
 90, 	// IY
 100, 	// OP
 100, 	// UW
 100, 	// AX
 110, 	// Y
 200, 	// RR
 90, 	// L
 60, 	// LL
 120, 	// M
 120, 	// N
 105, 	// NH
 300, 	// F
 200, 	// S
 80, 	// EH
 300, 	// TD
 100, 	// BD
 60, 	// DD
 90, 	// GD
 120, 	// JH
 300, 	// P
 100, 	// B
 200, 	// T
 110, 	// D
 200, 	// K
 90, 	// G
 250, 	// CH
 100, 	// AO
 200, 	// R
 200, 	// KD
 140, 	// Z
 50, 	// W
 90, 	// NX
 140, 	// V
 105, 	// ND
 90, 	// MF
 300, 	// PD
 105, 	// NJ
 200, 	// SH
 300, 	// TS
 300, 	// DZ
// ==== B2 ====
 250, 	// _
 140, 	// AP
 140, 	// EP
 140, 	// IY
 140, 	// OP
 140, 	// UW
 140, 	// AX
 120, 	// Y
 160, 	// RR
 110, 	// L
 200, 	// LL
 150, 	// M
 160, 	// N
 425, 	// NH
 150, 	// F
 200, 	// S
 160, 	// EH
 150, 	// TD
 80, 	// BD
 130, 	// DD
 120, 	// GD
 170, 	// JH
 180, 	// P
 150, 	// B
 150, 	// T
 140, 	// D
 160, 	// K
 120, 	// G
 250, 	// CH
 140, 	// AO
 60, 	// R
 160, 	// KD
 100, 	// Z
 80, 	// W
 250, 	// NX
 120, 	// V
 425, 	// ND
 250, 	// MF
 150, 	// PD
 425, 	// NJ
 240, 	// SH
 150, 	// TS
 150, 	// DZ
// ==== B3 ====
 250, 	// _
 220, 	// AP
 220, 	// EP
 220, 	// IY
 220, 	// OP
 220, 	// UW
 220, 	// AX
 240, 	// Y
 130, 	// RR
 120, 	// L
 400, 	// LL
 150, 	// M
 250, 	// N
 450, 	// NH
 150, 	// F
 200, 	// S
 270, 	// EH
 150, 	// TD
 130, 	// BD
 240, 	// DD
 180, 	// GD
 350, 	// JH
 180, 	// P
 130, 	// B
 250, 	// T
 170, 	// D
 280, 	// K
 180, 	// G
 250, 	// CH
 220, 	// AO
 130, 	// R
 280, 	// KD
 300, 	// Z
 80, 	// W
 350, 	// NX
 120, 	// V
 450, 	// ND
 150, 	// MF
 150, 	// PD
 450, 	// NJ
 300, 	// SH
 250, 	// TS
 250, 	// DZ
// ==== AV ====
 0, 	// _
 50, 	// AP
 54, 	// EP
 52, 	// IY
 52, 	// OP
 50, 	// UW
 52, 	// AX
 54, 	// Y
 48, 	// RR
 58, 	// L
 45, 	// LL
 43, 	// M
 46, 	// N
 54, 	// NH
 0, 	// F
 0, 	// S
 53, 	// EH
 0, 	// TD
 0, 	// BD
 30, 	// DD
 0, 	// GD
 0, 	// JH
 0, 	// P
 0, 	// B
 0, 	// T
 0, 	// D
 0, 	// K
 0, 	// G
 0, 	// CH
 53, 	// AO
 48, 	// R
 0, 	// KD
 45, 	// Z
 52, 	// W
 50, 	// NX
 53, 	// V
 45, 	// ND
 52, 	// MF
 0, 	// PD
 54, 	// NJ
 0, 	// SH
 0, 	// TS
 0 };	// DZ

// Male - F1,F1T,F2,F2T,F3,F3T,B1,B1T,B2,B2T,B3,B3T,AV,AVT data for Multi-part formants
const short it_maldip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _
 0, 	// _
// ====== Bandwidths and duration ======
// ====== Amplitude of Voicing ======
 0};

// Female diphthongs
const short it_femdip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _
 0, 	// _
 692, 	// OP F1
 30, 	// OP F1 duration
 644, 	// OP F1
 -1, 	// OP F1 duration
 1261, 	// OP F2
 30, 	// OP F2 duration
 1334, 	// OP F2
 -1, 	// OP F2 duration
// ====== Bandwidths and duration ======
// ====== Amplitude of Voicing ======
 0};

// Offsets into Amplitude data
const short it_ptram_def[] = {
 0, 	// _
 0, 	// AP
 0, 	// EP
 0, 	// IY
 0, 	// OP
 0, 	// UW
 0, 	// AX
 0, 	// Y
 1, 	// RR
 0, 	// L
 31, 	// LL
 0, 	// M
 0, 	// N
 0, 	// NH
 61, 	// F
 91, 	// S
 0, 	// EH
 121, 	// TD
 151, 	// BD
 181, 	// DD
 211, 	// GD
 241, 	// JH
 271, 	// P
 301, 	// B
 331, 	// T
 361, 	// D
 391, 	// K
 421, 	// G
 451, 	// CH
 0, 	// AO
 0, 	// R
 481, 	// KD
 511, 	// Z
 0, 	// W
 0, 	// NX
 541, 	// V
 0, 	// ND
 0, 	// MF
 571, 	// PD
 0, 	// NJ
 601, 	// SH
 631, 	// TS
 661 };	// DZ

// Offsets into Locus data
const short it_plocu_def[] = {
// ==== Front ====
 0, 	// _
 0, 	// AP
 0, 	// EP
 0, 	// IY
 0, 	// OP
 0, 	// UW
 0, 	// AX
 0, 	// Y
 0, 	// RR
 0, 	// L
 1, 	// LL
 10, 	// M
 19, 	// N
 28, 	// NH
 37, 	// F
 46, 	// S
 0, 	// EH
 55, 	// TD
 64, 	// BD
 73, 	// DD
 82, 	// GD
 91, 	// JH
 100, 	// P
 109, 	// B
 118, 	// T
 127, 	// D
 136, 	// K
 145, 	// G
 154, 	// CH
 0, 	// AO
 163, 	// R
 172, 	// KD
 181, 	// Z
 0, 	// W
 190, 	// NX
 199, 	// V
 208, 	// ND
 0, 	// MF
 217, 	// PD
 226, 	// NJ
 235, 	// SH
 244, 	// TS
 253, 	// DZ
// ==== Back ====
 0, 	// _
 0, 	// AP
 0, 	// EP
 0, 	// IY
 0, 	// OP
 0, 	// UW
 0, 	// AX
 0, 	// Y
 0, 	// RR
 0, 	// L
 262, 	// LL
 271, 	// M
 280, 	// N
 289, 	// NH
 298, 	// F
 307, 	// S
 0, 	// EH
 316, 	// TD
 325, 	// BD
 334, 	// DD
 343, 	// GD
 352, 	// JH
 361, 	// P
 370, 	// B
 379, 	// T
 388, 	// D
 397, 	// K
 406, 	// G
 415, 	// CH
 0, 	// AO
 424, 	// R
 433, 	// KD
 442, 	// Z
 0, 	// W
 451, 	// NX
 460, 	// V
 469, 	// ND
 0, 	// MF
 478, 	// PD
 487, 	// NJ
 496, 	// SH
 505, 	// TS
 514, 	// DZ
// ==== Round ====
 0, 	// _
 0, 	// AP
 0, 	// EP
 0, 	// IY
 0, 	// OP
 0, 	// UW
 0, 	// AX
 0, 	// Y
 0, 	// RR
 0, 	// L
 523, 	// LL
 532, 	// M
 541, 	// N
 550, 	// NH
 559, 	// F
 568, 	// S
 577, 	// EH
 586, 	// TD
 595, 	// BD
 604, 	// DD
 613, 	// GD
 622, 	// JH
 631, 	// P
 640, 	// B
 649, 	// T
 658, 	// D
 667, 	// K
 676, 	// G
 685, 	// CH
 0, 	// AO
 694, 	// R
 703, 	// KD
 712, 	// Z
 0, 	// W
 721, 	// NX
 730, 	// V
 739, 	// ND
 0, 	// MF
 748, 	// PD
 757, 	// NJ
 766, 	// SH
 775, 	// TS
 784, 	// DZ
// ==== Low ====
 0, 	// _
 0, 	// AP
 0, 	// EP
 0, 	// IY
 0, 	// OP
 0, 	// UW
 0, 	// AX
 0, 	// Y
 0, 	// RR
 0, 	// L
 0, 	// LL
 793, 	// M
 802, 	// N
 811, 	// NH
 820, 	// F
 829, 	// S
 0, 	// EH
 838, 	// TD
 847, 	// BD
 856, 	// DD
 865, 	// GD
 874, 	// JH
 883, 	// P
 892, 	// B
 901, 	// T
 910, 	// D
 919, 	// K
 928, 	// G
 937, 	// CH
 946, 	// AO
 0, 	// R
 955, 	// KD
 964, 	// Z
 0, 	// W
 973, 	// NX
 0, 	// V
 982, 	// ND
 0, 	// MF
 991, 	// PD
 1000, 	// NJ
 1009, 	// SH
 1018, 	// TS
 1027 };	// DZ

// Male Locus data
const short it_maleloc_def[] = {
 0, 
// Front
 -1, 	// LL F1 locus
 -1, 	// LL percent
 -1, 	// LL transition duration
 -1, 	// LL F2 locus
 -1, 	// LL percent
 -1, 	// LL transition duration
 -1, 	// LL F3 locus
 -1, 	// LL percent
 -1, 	// LL transition duration
 238, 	// M F1 locus
 10, 	// M percent
 30, 	// M transition duration
 1200, 	// M F2 locus
 10, 	// M percent
 16, 	// M transition duration
 2050, 	// M F3 locus
 10, 	// M percent
 20, 	// M transition duration
 280, 	// N F1 locus
 20, 	// N percent
 35, 	// N transition duration
 1420, 	// N F2 locus
 80, 	// N percent
 55, 	// N transition duration
 2600, 	// N F3 locus
 40, 	// N percent
 45, 	// N transition duration
 195, 	// NH F1 locus
 10, 	// NH percent
 30, 	// NH transition duration
 2039, 	// NH F2 locus
 10, 	// NH percent
 100, 	// NH transition duration
 2735, 	// NH F3 locus
 30, 	// NH percent
 30, 	// NH transition duration
 374, 	// F F1 locus
 10, 	// F percent
 30, 	// F transition duration
 1, 	// F F2 locus
 92, 	// F percent
 35, 	// F transition duration
 2080, 	// F F3 locus
 35, 	// F percent
 30, 	// F transition duration
 310, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1400, 	// S F2 locus
 40, 	// S percent
 50, 	// S transition duration
 2550, 	// S F3 locus
 0, 	// S percent
 70, 	// S transition duration
 350, 	// TD F1 locus
 43, 	// TD percent
 40, 	// TD transition duration
 1700, 	// TD F2 locus
 50, 	// TD percent
 95, 	// TD transition duration
 2700, 	// TD F3 locus
 50, 	// TD percent
 95, 	// TD transition duration
 200, 	// BD F1 locus
 25, 	// BD percent
 25, 	// BD transition duration
 900, 	// BD F2 locus
 40, 	// BD percent
 30, 	// BD transition duration
 2100, 	// BD F3 locus
 25, 	// BD percent
 45, 	// BD transition duration
 336, 	// DD F1 locus
 80, 	// DD percent
 50, 	// DD transition duration
 1800, 	// DD F2 locus
 66, 	// DD percent
 35, 	// DD transition duration
 2600, 	// DD F3 locus
 30, 	// DD percent
 45, 	// DD transition duration
 250, 	// GD F1 locus
 33, 	// GD percent
 45, 	// GD transition duration
 2500, 	// GD F2 locus
 20, 	// GD percent
 52, 	// GD transition duration
 2800, 	// GD F3 locus
 20, 	// GD percent
 20, 	// GD transition duration
 240, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1750, 	// JH F2 locus
 25, 	// JH percent
 70, 	// JH transition duration
 2750, 	// JH F3 locus
 19, 	// JH percent
 70, 	// JH transition duration
 350, 	// P F1 locus
 55, 	// P percent
 20, 	// P transition duration
 950, 	// P F2 locus
 35, 	// P percent
 30, 	// P transition duration
 2200, 	// P F3 locus
 25, 	// P percent
 45, 	// P transition duration
 200, 	// B F1 locus
 25, 	// B percent
 25, 	// B transition duration
 900, 	// B F2 locus
 40, 	// B percent
 30, 	// B transition duration
 2100, 	// B F3 locus
 25, 	// B percent
 45, 	// B transition duration
 320, 	// T F1 locus
 43, 	// T percent
 35, 	// T transition duration
 1700, 	// T F2 locus
 66, 	// T percent
 35, 	// T transition duration
 2650, 	// T F3 locus
 30, 	// T percent
 45, 	// T transition duration
 250, 	// D F1 locus
 43, 	// D percent
 35, 	// D transition duration
 1800, 	// D F2 locus
 66, 	// D percent
 35, 	// D transition duration
 2600, 	// D F3 locus
 30, 	// D percent
 45, 	// D transition duration
 280, 	// K F1 locus
 33, 	// K percent
 45, 	// K transition duration
 1990, 	// K F2 locus
 20, 	// K percent
 50, 	// K transition duration
 2400, 	// K F3 locus
 50, 	// K percent
 50, 	// K transition duration
 250, 	// G F1 locus
 33, 	// G percent
 45, 	// G transition duration
 1990, 	// G F2 locus
 20, 	// G percent
 50, 	// G transition duration
 3000, 	// G F3 locus
 113, 	// G percent
 50, 	// G transition duration
 318, 	// CH F1 locus
 10, 	// CH percent
 50, 	// CH transition duration
 1825, 	// CH F2 locus
 25, 	// CH percent
 60, 	// CH transition duration
 2775, 	// CH F3 locus
 19, 	// CH percent
 70, 	// CH transition duration
 300, 	// R F1 locus
 50, 	// R percent
 50, 	// R transition duration
 1300, 	// R F2 locus
 50, 	// R percent
 50, 	// R transition duration
 1800, 	// R F3 locus
 50, 	// R percent
 50, 	// R transition duration
 320, 	// KD F1 locus
 33, 	// KD percent
 45, 	// KD transition duration
 2200, 	// KD F2 locus
 20, 	// KD percent
 50, 	// KD transition duration
 2400, 	// KD F3 locus
 50, 	// KD percent
 50, 	// KD transition duration
 320, 	// Z F1 locus
 54, 	// Z percent
 55, 	// Z transition duration
 1750, 	// Z F2 locus
 25, 	// Z percent
 70, 	// Z transition duration
 2776, 	// Z F3 locus
 19, 	// Z percent
 70, 	// Z transition duration
 440, 	// NX F1 locus
 25, 	// NX percent
 40, 	// NX transition duration
 2200, 	// NX F2 locus
 15, 	// NX percent
 60, 	// NX transition duration
 2600, 	// NX F3 locus
 80, 	// NX percent
 60, 	// NX transition duration
 300, 	// V F1 locus
 50, 	// V percent
 30, 	// V transition duration
 1, 	// V F2 locus
 92, 	// V percent
 35, 	// V transition duration
 2080, 	// V F3 locus
 35, 	// V percent
 40, 	// V transition duration
 280, 	// ND F1 locus
 20, 	// ND percent
 35, 	// ND transition duration
 1420, 	// ND F2 locus
 80, 	// ND percent
 55, 	// ND transition duration
 2600, 	// ND F3 locus
 40, 	// ND percent
 45, 	// ND transition duration
 350, 	// PD F1 locus
 55, 	// PD percent
 20, 	// PD transition duration
 950, 	// PD F2 locus
 35, 	// PD percent
 30, 	// PD transition duration
 2200, 	// PD F3 locus
 25, 	// PD percent
 45, 	// PD transition duration
 280, 	// NJ F1 locus
 20, 	// NJ percent
 35, 	// NJ transition duration
 2300, 	// NJ F2 locus
 20, 	// NJ percent
 55, 	// NJ transition duration
 2900, 	// NJ F3 locus
 20, 	// NJ percent
 90, 	// NJ transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1630, 	// SH F2 locus
 30, 	// SH percent
 70, 	// SH transition duration
 2340, 	// SH F3 locus
 51, 	// SH percent
 70, 	// SH transition duration
 245, 	// TS F1 locus
 80, 	// TS percent
 30, 	// TS transition duration
 1900, 	// TS F2 locus
 47, 	// TS percent
 40, 	// TS transition duration
 2727, 	// TS F3 locus
 40, 	// TS percent
 40, 	// TS transition duration
 250, 	// DZ F1 locus
 43, 	// DZ percent
 35, 	// DZ transition duration
 1800, 	// DZ F2 locus
 66, 	// DZ percent
 35, 	// DZ transition duration
 2600, 	// DZ F3 locus
 30, 	// DZ percent
 45, 	// DZ transition duration
// Back
 -1, 	// LL F1 locus
 -1, 	// LL percent
 -1, 	// LL transition duration
 -1, 	// LL F2 locus
 -1, 	// LL percent
 -1, 	// LL transition duration
 -1, 	// LL F3 locus
 -1, 	// LL percent
 -1, 	// LL transition duration
 280, 	// M F1 locus
 20, 	// M percent
 30, 	// M transition duration
 1000, 	// M F2 locus
 10, 	// M percent
 20, 	// M transition duration
 1800, 	// M F3 locus
 80, 	// M percent
 20, 	// M transition duration
 280, 	// N F1 locus
 20, 	// N percent
 30, 	// N transition duration
 1420, 	// N F2 locus
 80, 	// N percent
 50, 	// N transition duration
 2632, 	// N F3 locus
 30, 	// N percent
 60, 	// N transition duration
 244, 	// NH F1 locus
 10, 	// NH percent
 30, 	// NH transition duration
 2039, 	// NH F2 locus
 10, 	// NH percent
 100, 	// NH transition duration
 2665, 	// NH F3 locus
 30, 	// NH percent
 40, 	// NH transition duration
 320, 	// F F1 locus
 60, 	// F percent
 30, 	// F transition duration
 1, 	// F F2 locus
 91, 	// F percent
 35, 	// F transition duration
 2044, 	// F F3 locus
 65, 	// F percent
 40, 	// F transition duration
 310, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1271, 	// S F2 locus
 40, 	// S percent
 50, 	// S transition duration
 2610, 	// S F3 locus
 0, 	// S percent
 60, 	// S transition duration
 450, 	// TD F1 locus
 30, 	// TD percent
 45, 	// TD transition duration
 1600, 	// TD F2 locus
 40, 	// TD percent
 85, 	// TD transition duration
 2491, 	// TD F3 locus
 10, 	// TD percent
 50, 	// TD transition duration
 350, 	// BD F1 locus
 45, 	// BD percent
 25, 	// BD transition duration
 920, 	// BD F2 locus
 46, 	// BD percent
 30, 	// BD transition duration
 1800, 	// BD F3 locus
 40, 	// BD percent
 45, 	// BD transition duration
 483, 	// DD F1 locus
 10, 	// DD percent
 40, 	// DD transition duration
 1700, 	// DD F2 locus
 40, 	// DD percent
 75, 	// DD transition duration
 2600, 	// DD F3 locus
 0, 	// DD percent
 50, 	// DD transition duration
 300, 	// GD F1 locus
 33, 	// GD percent
 50, 	// GD transition duration
 1500, 	// GD F2 locus
 16, 	// GD percent
 60, 	// GD transition duration
 2100, 	// GD F3 locus
 10, 	// GD percent
 65, 	// GD transition duration
 245, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1680, 	// JH F2 locus
 5, 	// JH percent
 120, 	// JH transition duration
 2450, 	// JH F3 locus
 10, 	// JH percent
 70, 	// JH transition duration
 350, 	// P F1 locus
 45, 	// P percent
 25, 	// P transition duration
 920, 	// P F2 locus
 46, 	// P percent
 30, 	// P transition duration
 2250, 	// P F3 locus
 45, 	// P percent
 30, 	// P transition duration
 350, 	// B F1 locus
 45, 	// B percent
 25, 	// B transition duration
 920, 	// B F2 locus
 46, 	// B percent
 30, 	// B transition duration
 1800, 	// B F3 locus
 40, 	// B percent
 45, 	// B transition duration
 320, 	// T F1 locus
 43, 	// T percent
 50, 	// T transition duration
 1700, 	// T F2 locus
 10, 	// T percent
 75, 	// T transition duration
 2600, 	// T F3 locus
 10, 	// T percent
 50, 	// T transition duration
 250, 	// D F1 locus
 43, 	// D percent
 50, 	// D transition duration
 1700, 	// D F2 locus
 40, 	// D percent
 75, 	// D transition duration
 2600, 	// D F3 locus
 0, 	// D percent
 50, 	// D transition duration
 280, 	// K F1 locus
 33, 	// K percent
 50, 	// K transition duration
 1800, 	// K F2 locus
 16, 	// K percent
 50, 	// K transition duration
 2000, 	// K F3 locus
 20, 	// K percent
 90, 	// K transition duration
 300, 	// G F1 locus
 33, 	// G percent
 50, 	// G transition duration
 1780, 	// G F2 locus
 16, 	// G percent
 60, 	// G transition duration
 2150, 	// G F3 locus
 0, 	// G percent
 90, 	// G transition duration
 320, 	// CH F1 locus
 10, 	// CH percent
 50, 	// CH transition duration
 1600, 	// CH F2 locus
 10, 	// CH percent
 50, 	// CH transition duration
 2450, 	// CH F3 locus
 10, 	// CH percent
 70, 	// CH transition duration
 300, 	// R F1 locus
 50, 	// R percent
 50, 	// R transition duration
 1300, 	// R F2 locus
 50, 	// R percent
 50, 	// R transition duration
 1800, 	// R F3 locus
 50, 	// R percent
 50, 	// R transition duration
 320, 	// KD F1 locus
 33, 	// KD percent
 45, 	// KD transition duration
 1990, 	// KD F2 locus
 20, 	// KD percent
 50, 	// KD transition duration
 2150, 	// KD F3 locus
 0, 	// KD percent
 90, 	// KD transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1690, 	// Z F2 locus
 15, 	// Z percent
 60, 	// Z transition duration
 2550, 	// Z F3 locus
 10, 	// Z percent
 70, 	// Z transition duration
 440, 	// NX F1 locus
 25, 	// NX percent
 40, 	// NX transition duration
 1800, 	// NX F2 locus
 20, 	// NX percent
 70, 	// NX transition duration
 2150, 	// NX F3 locus
 20, 	// NX percent
 70, 	// NX transition duration
 300, 	// V F1 locus
 50, 	// V percent
 30, 	// V transition duration
 1, 	// V F2 locus
 91, 	// V percent
 40, 	// V transition duration
 2100, 	// V F3 locus
 65, 	// V percent
 40, 	// V transition duration
 280, 	// ND F1 locus
 20, 	// ND percent
 30, 	// ND transition duration
 1420, 	// ND F2 locus
 80, 	// ND percent
 50, 	// ND transition duration
 2632, 	// ND F3 locus
 30, 	// ND percent
 60, 	// ND transition duration
 350, 	// PD F1 locus
 45, 	// PD percent
 25, 	// PD transition duration
 920, 	// PD F2 locus
 46, 	// PD percent
 30, 	// PD transition duration
 2250, 	// PD F3 locus
 45, 	// PD percent
 30, 	// PD transition duration
 244, 	// NJ F1 locus
 10, 	// NJ percent
 30, 	// NJ transition duration
 2300, 	// NJ F2 locus
 20, 	// NJ percent
 70, 	// NJ transition duration
 2900, 	// NJ F3 locus
 20, 	// NJ percent
 90, 	// NJ transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1600, 	// SH F2 locus
 27, 	// SH percent
 70, 	// SH transition duration
 2270, 	// SH F3 locus
 0, 	// SH percent
 85, 	// SH transition duration
 253, 	// TS F1 locus
 65, 	// TS percent
 30, 	// TS transition duration
 1800, 	// TS F2 locus
 43, 	// TS percent
 40, 	// TS transition duration
 2700, 	// TS F3 locus
 18, 	// TS percent
 65, 	// TS transition duration
 250, 	// DZ F1 locus
 43, 	// DZ percent
 50, 	// DZ transition duration
 1700, 	// DZ F2 locus
 40, 	// DZ percent
 75, 	// DZ transition duration
 2600, 	// DZ F3 locus
 0, 	// DZ percent
 50, 	// DZ transition duration
// Round
 -1, 	// LL F1 locus
 -1, 	// LL percent
 -1, 	// LL transition duration
 -1, 	// LL F2 locus
 -1, 	// LL percent
 -1, 	// LL transition duration
 -1, 	// LL F3 locus
 -1, 	// LL percent
 -1, 	// LL transition duration
 280, 	// M F1 locus
 20, 	// M percent
 30, 	// M transition duration
 948, 	// M F2 locus
 10, 	// M percent
 20, 	// M transition duration
 2220, 	// M F3 locus
 10, 	// M percent
 25, 	// M transition duration
 280, 	// N F1 locus
 20, 	// N percent
 30, 	// N transition duration
 1400, 	// N F2 locus
 25, 	// N percent
 95, 	// N transition duration
 1800, 	// N F3 locus
 40, 	// N percent
 35, 	// N transition duration
 181, 	// NH F1 locus
 10, 	// NH percent
 30, 	// NH transition duration
 2000, 	// NH F2 locus
 10, 	// NH percent
 1000, 	// NH transition duration
 2520, 	// NH F3 locus
 30, 	// NH percent
 30, 	// NH transition duration
 320, 	// F F1 locus
 60, 	// F percent
 30, 	// F transition duration
 1, 	// F F2 locus
 91, 	// F percent
 25, 	// F transition duration
 2180, 	// F F3 locus
 10, 	// F percent
 40, 	// F transition duration
 310, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1250, 	// S F2 locus
 15, 	// S percent
 60, 	// S transition duration
 2384, 	// S F3 locus
 0, 	// S percent
 60, 	// S transition duration
 -1, 	// EH F1 locus
 -1, 	// EH percent
 -1, 	// EH transition duration
 -1, 	// EH F2 locus
 -1, 	// EH percent
 -1, 	// EH transition duration
 -1, 	// EH F3 locus
 -1, 	// EH percent
 -1, 	// EH transition duration
 450, 	// TD F1 locus
 30, 	// TD percent
 45, 	// TD transition duration
 1500, 	// TD F2 locus
 66, 	// TD percent
 35, 	// TD transition duration
 2541, 	// TD F3 locus
 10, 	// TD percent
 50, 	// TD transition duration
 320, 	// BD F1 locus
 45, 	// BD percent
 25, 	// BD transition duration
 720, 	// BD F2 locus
 36, 	// BD percent
 35, 	// BD transition duration
 2270, 	// BD F3 locus
 50, 	// BD percent
 30, 	// BD transition duration
 426, 	// DD F1 locus
 10, 	// DD percent
 45, 	// DD transition duration
 1700, 	// DD F2 locus
 40, 	// DD percent
 95, 	// DD transition duration
 2600, 	// DD F3 locus
 30, 	// DD percent
 85, 	// DD transition duration
 290, 	// GD F1 locus
 45, 	// GD percent
 40, 	// GD transition duration
 800, 	// GD F2 locus
 42, 	// GD percent
 65, 	// GD transition duration
 1923, 	// GD F3 locus
 15, 	// GD percent
 80, 	// GD transition duration
 245, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1680, 	// JH F2 locus
 10, 	// JH percent
 90, 	// JH transition duration
 1970, 	// JH F3 locus
 10, 	// JH percent
 100, 	// JH transition duration
 350, 	// P F1 locus
 45, 	// P percent
 30, 	// P transition duration
 888, 	// P F2 locus
 46, 	// P percent
 30, 	// P transition duration
 2198, 	// P F3 locus
 40, 	// P percent
 30, 	// P transition duration
 320, 	// B F1 locus
 45, 	// B percent
 25, 	// B transition duration
 720, 	// B F2 locus
 36, 	// B percent
 35, 	// B transition duration
 1900, 	// B F3 locus
 40, 	// B percent
 35, 	// B transition duration
 320, 	// T F1 locus
 43, 	// T percent
 40, 	// T transition duration
 1700, 	// T F2 locus
 5, 	// T percent
 95, 	// T transition duration
 2300, 	// T F3 locus
 0, 	// T percent
 95, 	// T transition duration
 250, 	// D F1 locus
 43, 	// D percent
 40, 	// D transition duration
 1700, 	// D F2 locus
 40, 	// D percent
 95, 	// D transition duration
 2300, 	// D F3 locus
 0, 	// D percent
 95, 	// D transition duration
 280, 	// K F1 locus
 33, 	// K percent
 45, 	// K transition duration
 1400, 	// K F2 locus
 60, 	// K percent
 75, 	// K transition duration
 2050, 	// K F3 locus
 15, 	// K percent
 80, 	// K transition duration
 290, 	// G F1 locus
 45, 	// G percent
 40, 	// G transition duration
 1600, 	// G F2 locus
 42, 	// G percent
 65, 	// G transition duration
 1920, 	// G F3 locus
 15, 	// G percent
 80, 	// G transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1678, 	// CH F2 locus
 10, 	// CH percent
 90, 	// CH transition duration
 2350, 	// CH F3 locus
 10, 	// CH percent
 80, 	// CH transition duration
 300, 	// R F1 locus
 50, 	// R percent
 50, 	// R transition duration
 1300, 	// R F2 locus
 50, 	// R percent
 50, 	// R transition duration
 1800, 	// R F3 locus
 50, 	// R percent
 50, 	// R transition duration
 320, 	// KD F1 locus
 33, 	// KD percent
 45, 	// KD transition duration
 1200, 	// KD F2 locus
 42, 	// KD percent
 65, 	// KD transition duration
 2150, 	// KD F3 locus
 0, 	// KD percent
 90, 	// KD transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1198, 	// Z F2 locus
 40, 	// Z percent
 50, 	// Z transition duration
 2541, 	// Z F3 locus
 0, 	// Z percent
 70, 	// Z transition duration
 440, 	// NX F1 locus
 25, 	// NX percent
 40, 	// NX transition duration
 1700, 	// NX F2 locus
 42, 	// NX percent
 70, 	// NX transition duration
 1920, 	// NX F3 locus
 25, 	// NX percent
 70, 	// NX transition duration
 325, 	// V F1 locus
 50, 	// V percent
 30, 	// V transition duration
 1, 	// V F2 locus
 91, 	// V percent
 40, 	// V transition duration
 2100, 	// V F3 locus
 65, 	// V percent
 40, 	// V transition duration
 280, 	// ND F1 locus
 20, 	// ND percent
 30, 	// ND transition duration
 1400, 	// ND F2 locus
 25, 	// ND percent
 95, 	// ND transition duration
 1800, 	// ND F3 locus
 40, 	// ND percent
 35, 	// ND transition duration
 350, 	// PD F1 locus
 45, 	// PD percent
 30, 	// PD transition duration
 888, 	// PD F2 locus
 46, 	// PD percent
 30, 	// PD transition duration
 2198, 	// PD F3 locus
 40, 	// PD percent
 30, 	// PD transition duration
 181, 	// NJ F1 locus
 10, 	// NJ percent
 30, 	// NJ transition duration
 2000, 	// NJ F2 locus
 10, 	// NJ percent
 70, 	// NJ transition duration
 2520, 	// NJ F3 locus
 30, 	// NJ percent
 90, 	// NJ transition duration
 340, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1630, 	// SH F2 locus
 27, 	// SH percent
 90, 	// SH transition duration
 2100, 	// SH F3 locus
 20, 	// SH percent
 110, 	// SH transition duration
 290, 	// TS F1 locus
 45, 	// TS percent
 50, 	// TS transition duration
 1970, 	// TS F2 locus
 71, 	// TS percent
 30, 	// TS transition duration
 2570, 	// TS F3 locus
 31, 	// TS percent
 80, 	// TS transition duration
 250, 	// DZ F1 locus
 44, 	// DZ percent
 40, 	// DZ transition duration
 1700, 	// DZ F2 locus
 40, 	// DZ percent
 95, 	// DZ transition duration
 2300, 	// DZ F3 locus
 0, 	// DZ percent
 95, 	// DZ transition duration
// Low
 0, 	// M F1 locus
 0, 	// M percent
 0, 	// M transition duration
 0, 	// M F2 locus
 0, 	// M percent
 0, 	// M transition duration
 0, 	// M F3 locus
 0, 	// M percent
 0, 	// M transition duration
 0, 	// N F1 locus
 0, 	// N percent
 0, 	// N transition duration
 0, 	// N F2 locus
 0, 	// N percent
 0, 	// N transition duration
 0, 	// N F3 locus
 0, 	// N percent
 0, 	// N transition duration
 0, 	// NH F1 locus
 0, 	// NH percent
 0, 	// NH transition duration
 0, 	// NH F2 locus
 0, 	// NH percent
 0, 	// NH transition duration
 0, 	// NH F3 locus
 0, 	// NH percent
 0, 	// NH transition duration
 0, 	// F F1 locus
 0, 	// F percent
 0, 	// F transition duration
 0, 	// F F2 locus
 0, 	// F percent
 0, 	// F transition duration
 0, 	// F F3 locus
 0, 	// F percent
 0, 	// F transition duration
 0, 	// S F1 locus
 0, 	// S percent
 0, 	// S transition duration
 0, 	// S F2 locus
 0, 	// S percent
 0, 	// S transition duration
 0, 	// S F3 locus
 0, 	// S percent
 0, 	// S transition duration
 0, 	// TD F1 locus
 0, 	// TD percent
 0, 	// TD transition duration
 0, 	// TD F2 locus
 0, 	// TD percent
 0, 	// TD transition duration
 0, 	// TD F3 locus
 0, 	// TD percent
 0, 	// TD transition duration
 0, 	// BD F1 locus
 0, 	// BD percent
 0, 	// BD transition duration
 0, 	// BD F2 locus
 0, 	// BD percent
 0, 	// BD transition duration
 0, 	// BD F3 locus
 0, 	// BD percent
 0, 	// BD transition duration
 0, 	// DD F1 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// DD F2 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// DD F3 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// GD F1 locus
 0, 	// GD percent
 0, 	// GD transition duration
 0, 	// GD F2 locus
 0, 	// GD percent
 0, 	// GD transition duration
 0, 	// GD F3 locus
 0, 	// GD percent
 0, 	// GD transition duration
 0, 	// JH F1 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F2 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F3 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// P F1 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// P F2 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// P F3 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// B F1 locus
 0, 	// B percent
 0, 	// B transition duration
 0, 	// B F2 locus
 0, 	// B percent
 0, 	// B transition duration
 0, 	// B F3 locus
 0, 	// B percent
 0, 	// B transition duration
 0, 	// T F1 locus
 0, 	// T percent
 0, 	// T transition duration
 0, 	// T F2 locus
 0, 	// T percent
 0, 	// T transition duration
 0, 	// T F3 locus
 0, 	// T percent
 0, 	// T transition duration
 0, 	// D F1 locus
 0, 	// D percent
 0, 	// D transition duration
 0, 	// D F2 locus
 0, 	// D percent
 0, 	// D transition duration
 0, 	// D F3 locus
 0, 	// D percent
 0, 	// D transition duration
 0, 	// K F1 locus
 0, 	// K percent
 0, 	// K transition duration
 0, 	// K F2 locus
 0, 	// K percent
 0, 	// K transition duration
 0, 	// K F3 locus
 0, 	// K percent
 0, 	// K transition duration
 0, 	// G F1 locus
 0, 	// G percent
 0, 	// G transition duration
 0, 	// G F2 locus
 0, 	// G percent
 0, 	// G transition duration
 0, 	// G F3 locus
 0, 	// G percent
 0, 	// G transition duration
 0, 	// CH F1 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F2 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F3 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// AO F1 locus
 0, 	// AO percent
 0, 	// AO transition duration
 0, 	// AO F2 locus
 0, 	// AO percent
 0, 	// AO transition duration
 0, 	// AO F3 locus
 0, 	// AO percent
 0, 	// AO transition duration
 0, 	// KD F1 locus
 0, 	// KD percent
 0, 	// KD transition duration
 0, 	// KD F2 locus
 0, 	// KD percent
 0, 	// KD transition duration
 0, 	// KD F3 locus
 0, 	// KD percent
 -1, 	// KD transition duration
 0, 	// Z F1 locus
 0, 	// Z percent
 0, 	// Z transition duration
 0, 	// Z F2 locus
 0, 	// Z percent
 0, 	// Z transition duration
 0, 	// Z F3 locus
 0, 	// Z percent
 0, 	// Z transition duration
 0, 	// NX F1 locus
 0, 	// NX percent
 0, 	// NX transition duration
 0, 	// NX F2 locus
 0, 	// NX percent
 0, 	// NX transition duration
 0, 	// NX F3 locus
 0, 	// NX percent
 0, 	// NX transition duration
 0, 	// ND F1 locus
 0, 	// ND percent
 0, 	// ND transition duration
 0, 	// ND F2 locus
 0, 	// ND percent
 0, 	// ND transition duration
 0, 	// ND F3 locus
 0, 	// ND percent
 0, 	// ND transition duration
 0, 	// PD F1 locus
 0, 	// PD percent
 0, 	// PD transition duration
 0, 	// PD F2 locus
 0, 	// PD percent
 0, 	// PD transition duration
 0, 	// PD F3 locus
 0, 	// PD percent
 0, 	// PD transition duration
 0, 	// NJ F1 locus
 0, 	// NJ percent
 0, 	// NJ transition duration
 0, 	// NJ F2 locus
 0, 	// NJ percent
 0, 	// NJ transition duration
 0, 	// NJ F3 locus
 0, 	// NJ percent
 0, 	// NJ transition duration
 0, 	// SH F1 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// SH F2 locus
 0, 	// SH percent
 0, 	// SH transition duration
 -1, 	// SH F3 locus
 -1, 	// SH percent
 -1, 	// SH transition duration
 253, 	// TS F1 locus
 50, 	// TS percent
 30, 	// TS transition duration
 1900, 	// TS F2 locus
 80, 	// TS percent
 30, 	// TS transition duration
 2557, 	// TS F3 locus
 27, 	// TS percent
 40, 	// TS transition duration
 0, 	// DZ F1 locus
 0, 	// DZ percent
 0, 	// DZ transition duration
 1900, 	// DZ F2 locus
 80, 	// DZ percent
 30, 	// DZ transition duration
 2557, 	// DZ F3 locus
 27, 	// DZ percent
 40, 	// DZ transition duration
 0};

// Female Locus
const short it_femloc_def[] = {
 0, 
// Front
 350, 	// LL F1 locus
 10, 	// LL percent
 30, 	// LL transition duration
 1100, 	// LL F2 locus
 10, 	// LL percent
 10, 	// LL transition duration
 2800, 	// LL F3 locus
 10, 	// LL percent
 30, 	// LL transition duration
 480, 	// M F1 locus
 30, 	// M percent
 30, 	// M transition duration
 1400, 	// M F2 locus
 55, 	// M percent
 35, 	// M transition duration
 2000, 	// M F3 locus
 45, 	// M percent
 50, 	// M transition duration
 450, 	// N F1 locus
 30, 	// N percent
 60, 	// N transition duration
 1880, 	// N F2 locus
 39, 	// N percent
 35, 	// N transition duration
 3250, 	// N F3 locus
 50, 	// N percent
 45, 	// N transition duration
 195, 	// NH F1 locus
 10, 	// NH percent
 30, 	// NH transition duration
 2039, 	// NH F2 locus
 50, 	// NH percent
 60, 	// NH transition duration
 2735, 	// NH F3 locus
 50, 	// NH percent
 60, 	// NH transition duration
 362, 	// F F1 locus
 60, 	// F percent
 30, 	// F transition duration
 1750, 	// F F2 locus
 43, 	// F percent
 40, 	// F transition duration
 2700, 	// F F3 locus
 0, 	// F percent
 30, 	// F transition duration
 330, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 2000, 	// S F2 locus
 30, 	// S percent
 50, 	// S transition duration
 2980, 	// S F3 locus
 0, 	// S percent
 70, 	// S transition duration
 447, 	// TD F1 locus
 10, 	// TD percent
 45, 	// TD transition duration
 2375, 	// TD F2 locus
 10, 	// TD percent
 45, 	// TD transition duration
 3065, 	// TD F3 locus
 10, 	// TD percent
 45, 	// TD transition duration
 241, 	// BD F1 locus
 30, 	// BD percent
 30, 	// BD transition duration
 1500, 	// BD F2 locus
 15, 	// BD percent
 25, 	// BD transition duration
 2412, 	// BD F3 locus
 15, 	// BD percent
 25, 	// BD transition duration
 492, 	// DD F1 locus
 10, 	// DD percent
 50, 	// DD transition duration
 2515, 	// DD F2 locus
 10, 	// DD percent
 52, 	// DD transition duration
 3084, 	// DD F3 locus
 10, 	// DD percent
 52, 	// DD transition duration
 220, 	// GD F1 locus
 10, 	// GD percent
 50, 	// GD transition duration
 2700, 	// GD F2 locus
 10, 	// GD percent
 52, 	// GD transition duration
 2835, 	// GD F3 locus
 10, 	// GD percent
 52, 	// GD transition duration
 370, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 2000, 	// JH F2 locus
 25, 	// JH percent
 70, 	// JH transition duration
 3300, 	// JH F3 locus
 19, 	// JH percent
 70, 	// JH transition duration
 260, 	// P F1 locus
 50, 	// P percent
 30, 	// P transition duration
 1570, 	// P F2 locus
 47, 	// P percent
 25, 	// P transition duration
 1660, 	// P F3 locus
 73, 	// P percent
 35, 	// P transition duration
 290, 	// B F1 locus
 30, 	// B percent
 30, 	// B transition duration
 1800, 	// B F2 locus
 17, 	// B percent
 25, 	// B transition duration
 2650, 	// B F3 locus
 30, 	// B percent
 35, 	// B transition duration
 180, 	// T F1 locus
 56, 	// T percent
 50, 	// T transition duration
 2400, 	// T F2 locus
 25, 	// T percent
 35, 	// T transition duration
 3000, 	// T F3 locus
 10, 	// T percent
 45, 	// T transition duration
 270, 	// D F1 locus
 33, 	// D percent
 35, 	// D transition duration
 2150, 	// D F2 locus
 66, 	// D percent
 35, 	// D transition duration
 2800, 	// D F3 locus
 30, 	// D percent
 45, 	// D transition duration
 210, 	// K F1 locus
 46, 	// K percent
 40, 	// K transition duration
 2450, 	// K F2 locus
 13, 	// K percent
 70, 	// K transition duration
 3000, 	// K F3 locus
 110, 	// K percent
 50, 	// K transition duration
 270, 	// G F1 locus
 30, 	// G percent
 45, 	// G transition duration
 2550, 	// G F2 locus
 13, 	// G percent
 70, 	// G transition duration
 3000, 	// G F3 locus
 120, 	// G percent
 50, 	// G transition duration
 320, 	// CH F1 locus
 50, 	// CH percent
 55, 	// CH transition duration
 2170, 	// CH F2 locus
 25, 	// CH percent
 70, 	// CH transition duration
 2960, 	// CH F3 locus
 0, 	// CH percent
 70, 	// CH transition duration
 350, 	// R F1 locus
 50, 	// R percent
 50, 	// R transition duration
 1450, 	// R F2 locus
 50, 	// R percent
 50, 	// R transition duration
 2550, 	// R F3 locus
 50, 	// R percent
 50, 	// R transition duration
 310, 	// KD F1 locus
 10, 	// KD percent
 45, 	// KD transition duration
 2592, 	// KD F2 locus
 10, 	// KD percent
 50, 	// KD transition duration
 3180, 	// KD F3 locus
 10, 	// KD percent
 60, 	// KD transition duration
 270, 	// Z F1 locus
 25, 	// Z percent
 40, 	// Z transition duration
 960, 	// Z F2 locus
 78, 	// Z percent
 60, 	// Z transition duration
 2800, 	// Z F3 locus
 38, 	// Z percent
 70, 	// Z transition duration
 480, 	// NX F1 locus
 30, 	// NX percent
 40, 	// NX transition duration
 2760, 	// NX F2 locus
 10, 	// NX percent
 70, 	// NX transition duration
 1900, 	// NX F3 locus
 114, 	// NX percent
 60, 	// NX transition duration
 350, 	// V F1 locus
 50, 	// V percent
 55, 	// V transition duration
 1, 	// V F2 locus
 85, 	// V percent
 40, 	// V transition duration
 2600, 	// V F3 locus
 35, 	// V percent
 40, 	// V transition duration
 450, 	// ND F1 locus
 24, 	// ND percent
 35, 	// ND transition duration
 2100, 	// ND F2 locus
 60, 	// ND percent
 35, 	// ND transition duration
 3200, 	// ND F3 locus
 35, 	// ND percent
 45, 	// ND transition duration
 594, 	// PD F1 locus
 10, 	// PD percent
 30, 	// PD transition duration
 2222, 	// PD F2 locus
 10, 	// PD percent
 25, 	// PD transition duration
 2978, 	// PD F3 locus
 10, 	// PD percent
 25, 	// PD transition duration
 195, 	// NJ F1 locus
 10, 	// NJ percent
 30, 	// NJ transition duration
 2039, 	// NJ F2 locus
 50, 	// NJ percent
 60, 	// NJ transition duration
 2735, 	// NJ F3 locus
 50, 	// NJ percent
 30, 	// NJ transition duration
 280, 	// SH F1 locus
 50, 	// SH percent
 60, 	// SH transition duration
 2050, 	// SH F2 locus
 37, 	// SH percent
 70, 	// SH transition duration
 2150, 	// SH F3 locus
 70, 	// SH percent
 70, 	// SH transition duration
 290, 	// TS F1 locus
 80, 	// TS percent
 40, 	// TS transition duration
 2143, 	// TS F2 locus
 69, 	// TS percent
 50, 	// TS transition duration
 3000, 	// TS F3 locus
 27, 	// TS percent
 70, 	// TS transition duration
 290, 	// DZ F1 locus
 80, 	// DZ percent
 40, 	// DZ transition duration
 2143, 	// DZ F2 locus
 69, 	// DZ percent
 50, 	// DZ transition duration
 2143, 	// DZ F3 locus
 69, 	// DZ percent
 50, 	// DZ transition duration
// Back
 -1, 	// LL F1 locus
 -1, 	// LL percent
 -1, 	// LL transition duration
 -1, 	// LL F2 locus
 -1, 	// LL percent
 -1, 	// LL transition duration
 350, 	// LL F3 locus
 10, 	// LL percent
 2800, 	// LL transition duration
 480, 	// M F1 locus
 30, 	// M percent
 35, 	// M transition duration
 40, 	// M F2 locus
 83, 	// M percent
 40, 	// M transition duration
 2400, 	// M F3 locus
 48, 	// M percent
 30, 	// M transition duration
 450, 	// N F1 locus
 60, 	// N percent
 45, 	// N transition duration
 1800, 	// N F2 locus
 0, 	// N percent
 75, 	// N transition duration
 3200, 	// N F3 locus
 0, 	// N percent
 30, 	// N transition duration
 244, 	// NH F1 locus
 10, 	// NH percent
 30, 	// NH transition duration
 2039, 	// NH F2 locus
 50, 	// NH percent
 60, 	// NH transition duration
 2665, 	// NH F3 locus
 30, 	// NH percent
 40, 	// NH transition duration
 280, 	// F F1 locus
 60, 	// F percent
 30, 	// F transition duration
 550, 	// F F2 locus
 78, 	// F percent
 30, 	// F transition duration
 2100, 	// F F3 locus
 82, 	// F percent
 40, 	// F transition duration
 390, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1800, 	// S F2 locus
 40, 	// S percent
 50, 	// S transition duration
 3070, 	// S F3 locus
 0, 	// S percent
 70, 	// S transition duration
 767, 	// TD F1 locus
 10, 	// TD percent
 30, 	// TD transition duration
 1652, 	// TD F2 locus
 10, 	// TD percent
 50, 	// TD transition duration
 2891, 	// TD F3 locus
 10, 	// TD percent
 50, 	// TD transition duration
 240, 	// BD F1 locus
 30, 	// BD percent
 30, 	// BD transition duration
 1065, 	// BD F2 locus
 30, 	// BD percent
 45, 	// BD transition duration
 2506, 	// BD F3 locus
 20, 	// BD percent
 45, 	// BD transition duration
 594, 	// DD F1 locus
 10, 	// DD percent
 40, 	// DD transition duration
 2141, 	// DD F2 locus
 10, 	// DD percent
 50, 	// DD transition duration
 3059, 	// DD F3 locus
 10, 	// DD percent
 50, 	// DD transition duration
 220, 	// GD F1 locus
 10, 	// GD percent
 55, 	// GD transition duration
 1900, 	// GD F2 locus
 10, 	// GD percent
 55, 	// GD transition duration
 2200, 	// GD F3 locus
 10, 	// GD percent
 55, 	// GD transition duration
 380, 	// JH F1 locus
 40, 	// JH percent
 55, 	// JH transition duration
 1900, 	// JH F2 locus
 10, 	// JH percent
 70, 	// JH transition duration
 3200, 	// JH F3 locus
 10, 	// JH percent
 70, 	// JH transition duration
 260, 	// P F1 locus
 50, 	// P percent
 35, 	// P transition duration
 1240, 	// P F2 locus
 8, 	// P percent
 30, 	// P transition duration
 1900, 	// P F3 locus
 65, 	// P percent
 40, 	// P transition duration
 150, 	// B F1 locus
 50, 	// B percent
 35, 	// B transition duration
 890, 	// B F2 locus
 80, 	// B percent
 30, 	// B transition duration
 1570, 	// B F3 locus
 88, 	// B percent
 40, 	// B transition duration
 180, 	// T F1 locus
 56, 	// T percent
 70, 	// T transition duration
 2200, 	// T F2 locus
 0, 	// T percent
 100, 	// T transition duration
 2850, 	// T F3 locus
 0, 	// T percent
 70, 	// T transition duration
 270, 	// D F1 locus
 33, 	// D percent
 45, 	// D transition duration
 2050, 	// D F2 locus
 40, 	// D percent
 80, 	// D transition duration
 2790, 	// D F3 locus
 0, 	// D percent
 50, 	// D transition duration
 210, 	// K F1 locus
 46, 	// K percent
 45, 	// K transition duration
 1800, 	// K F2 locus
 0, 	// K percent
 80, 	// K transition duration
 2300, 	// K F3 locus
 0, 	// K percent
 90, 	// K transition duration
 510, 	// G F1 locus
 0, 	// G percent
 50, 	// G transition duration
 1900, 	// G F2 locus
 0, 	// G percent
 80, 	// G transition duration
 2370, 	// G F3 locus
 0, 	// G percent
 80, 	// G transition duration
 320, 	// CH F1 locus
 50, 	// CH percent
 55, 	// CH transition duration
 2200, 	// CH F2 locus
 0, 	// CH percent
 70, 	// CH transition duration
 3000, 	// CH F3 locus
 100, 	// CH percent
 70, 	// CH transition duration
 350, 	// R F1 locus
 50, 	// R percent
 50, 	// R transition duration
 1450, 	// R F2 locus
 50, 	// R percent
 50, 	// R transition duration
 2550, 	// R F3 locus
 50, 	// R percent
 50, 	// R transition duration
 350, 	// KD F1 locus
 10, 	// KD percent
 50, 	// KD transition duration
 2074, 	// KD F2 locus
 10, 	// KD percent
 50, 	// KD transition duration
 2588, 	// KD F3 locus
 10, 	// KD percent
 50, 	// KD transition duration
 270, 	// Z F1 locus
 25, 	// Z percent
 45, 	// Z transition duration
 1800, 	// Z F2 locus
 0, 	// Z percent
 80, 	// Z transition duration
 2800, 	// Z F3 locus
 0, 	// Z percent
 70, 	// Z transition duration
 500, 	// NX F1 locus
 30, 	// NX percent
 40, 	// NX transition duration
 1530, 	// NX F2 locus
 10, 	// NX percent
 70, 	// NX transition duration
 2700, 	// NX F3 locus
 20, 	// NX percent
 70, 	// NX transition duration
 350, 	// V F1 locus
 75, 	// V percent
 30, 	// V transition duration
 1, 	// V F2 locus
 84, 	// V percent
 30, 	// V transition duration
 2000, 	// V F3 locus
 65, 	// V percent
 40, 	// V transition duration
 450, 	// ND F1 locus
 22, 	// ND percent
 30, 	// ND transition duration
 2200, 	// ND F2 locus
 65, 	// ND percent
 75, 	// ND transition duration
 3140, 	// ND F3 locus
 30, 	// ND percent
 60, 	// ND transition duration
 679, 	// PD F1 locus
 10, 	// PD percent
 35, 	// PD transition duration
 1343, 	// PD F2 locus
 10, 	// PD percent
 25, 	// PD transition duration
 2861, 	// PD F3 locus
 10, 	// PD percent
 30, 	// PD transition duration
 244, 	// NJ F1 locus
 10, 	// NJ percent
 30, 	// NJ transition duration
 2039, 	// NJ F2 locus
 50, 	// NJ percent
 60, 	// NJ transition duration
 2665, 	// NJ F3 locus
 30, 	// NJ percent
 40, 	// NJ transition duration
 280, 	// SH F1 locus
 50, 	// SH percent
 65, 	// SH transition duration
 2050, 	// SH F2 locus
 0, 	// SH percent
 70, 	// SH transition duration
 2700, 	// SH F3 locus
 0, 	// SH percent
 80, 	// SH transition duration
 308, 	// TS F1 locus
 54, 	// TS percent
 50, 	// TS transition duration
 1800, 	// TS F2 locus
 43, 	// TS percent
 40, 	// TS transition duration
 3000, 	// TS F3 locus
 18, 	// TS percent
 65, 	// TS transition duration
 308, 	// DZ F1 locus
 54, 	// DZ percent
 50, 	// DZ transition duration
 1800, 	// DZ F2 locus
 43, 	// DZ percent
 40, 	// DZ transition duration
 3000, 	// DZ F3 locus
 18, 	// DZ percent
 65, 	// DZ transition duration
// Round
 350, 	// LL F1 locus
 10, 	// LL percent
 30, 	// LL transition duration
 1200, 	// LL F2 locus
 10, 	// LL percent
 30, 	// LL transition duration
 2800, 	// LL F3 locus
 10, 	// LL percent
 30, 	// LL transition duration
 480, 	// M F1 locus
 30, 	// M percent
 35, 	// M transition duration
 40, 	// M F2 locus
 83, 	// M percent
 40, 	// M transition duration
 2400, 	// M F3 locus
 48, 	// M percent
 30, 	// M transition duration
 450, 	// N F1 locus
 30, 	// N percent
 60, 	// N transition duration
 1700, 	// N F2 locus
 70, 	// N percent
 35, 	// N transition duration
 2800, 	// N F3 locus
 0, 	// N percent
 80, 	// N transition duration
 181, 	// NH F1 locus
 10, 	// NH percent
 30, 	// NH transition duration
 2000, 	// NH F2 locus
 10, 	// NH percent
 1000, 	// NH transition duration
 2520, 	// NH F3 locus
 30, 	// NH percent
 30, 	// NH transition duration
 390, 	// F F1 locus
 10, 	// F percent
 60, 	// F transition duration
 1096, 	// F F2 locus
 10, 	// F percent
 60, 	// F transition duration
 2100, 	// F F3 locus
 82, 	// F percent
 40, 	// F transition duration
 390, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1900, 	// S F2 locus
 15, 	// S percent
 60, 	// S transition duration
 2880, 	// S F3 locus
 0, 	// S percent
 65, 	// S transition duration
 220, 	// EH F1 locus
 80, 	// EH percent
 20, 	// EH transition duration
 2200, 	// EH F2 locus
 80, 	// EH percent
 90, 	// EH transition duration
 -1, 	// EH F3 locus
 -1, 	// EH percent
 -1, 	// EH transition duration
 496, 	// TD F1 locus
 10, 	// TD percent
 50, 	// TD transition duration
 1672, 	// TD F2 locus
 10, 	// TD percent
 50, 	// TD transition duration
 2858, 	// TD F3 locus
 10, 	// TD percent
 50, 	// TD transition duration
 240, 	// BD F1 locus
 15, 	// BD percent
 30, 	// BD transition duration
 708, 	// BD F2 locus
 15, 	// BD percent
 30, 	// BD transition duration
 2100, 	// BD F3 locus
 20, 	// BD percent
 25, 	// BD transition duration
 500, 	// DD F1 locus
 10, 	// DD percent
 45, 	// DD transition duration
 1615, 	// DD F2 locus
 10, 	// DD percent
 47, 	// DD transition duration
 2818, 	// DD F3 locus
 10, 	// DD percent
 50, 	// DD transition duration
 200, 	// GD F1 locus
 30, 	// GD percent
 50, 	// GD transition duration
 1100, 	// GD F2 locus
 20, 	// GD percent
 30, 	// GD transition duration
 2400, 	// GD F3 locus
 10, 	// GD percent
 40, 	// GD transition duration
 380, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 2200, 	// JH F2 locus
 0, 	// JH percent
 90, 	// JH transition duration
 2900, 	// JH F3 locus
 20, 	// JH percent
 100, 	// JH transition duration
 260, 	// P F1 locus
 50, 	// P percent
 35, 	// P transition duration
 1240, 	// P F2 locus
 8, 	// P percent
 30, 	// P transition duration
 1900, 	// P F3 locus
 65, 	// P percent
 40, 	// P transition duration
 150, 	// B F1 locus
 50, 	// B percent
 35, 	// B transition duration
 890, 	// B F2 locus
 80, 	// B percent
 30, 	// B transition duration
 1570, 	// B F3 locus
 88, 	// B percent
 40, 	// B transition duration
 180, 	// T F1 locus
 56, 	// T percent
 65, 	// T transition duration
 2600, 	// T F2 locus
 40, 	// T percent
 100, 	// T transition duration
 2850, 	// T F3 locus
 0, 	// T percent
 90, 	// T transition duration
 270, 	// D F1 locus
 33, 	// D percent
 40, 	// D transition duration
 1900, 	// D F2 locus
 40, 	// D percent
 80, 	// D transition duration
 2700, 	// D F3 locus
 20, 	// D percent
 80, 	// D transition duration
 210, 	// K F1 locus
 46, 	// K percent
 35, 	// K transition duration
 1710, 	// K F2 locus
 71, 	// K percent
 65, 	// K transition duration
 2300, 	// K F3 locus
 0, 	// K percent
 80, 	// K transition duration
 240, 	// G F1 locus
 43, 	// G percent
 40, 	// G transition duration
 1710, 	// G F2 locus
 71, 	// G percent
 65, 	// G transition duration
 2300, 	// G F3 locus
 0, 	// G percent
 80, 	// G transition duration
 320, 	// CH F1 locus
 50, 	// CH percent
 55, 	// CH transition duration
 2200, 	// CH F2 locus
 0, 	// CH percent
 90, 	// CH transition duration
 2800, 	// CH F3 locus
 50, 	// CH percent
 100, 	// CH transition duration
 350, 	// R F1 locus
 50, 	// R percent
 50, 	// R transition duration
 1450, 	// R F2 locus
 50, 	// R percent
 50, 	// R transition duration
 2550, 	// R F3 locus
 50, 	// R percent
 50, 	// R transition duration
 400, 	// KD F1 locus
 10, 	// KD percent
 45, 	// KD transition duration
 1184, 	// KD F2 locus
 10, 	// KD percent
 50, 	// KD transition duration
 2632, 	// KD F3 locus
 10, 	// KD percent
 70, 	// KD transition duration
 270, 	// Z F1 locus
 25, 	// Z percent
 40, 	// Z transition duration
 1900, 	// Z F2 locus
 10, 	// Z percent
 80, 	// Z transition duration
 2800, 	// Z F3 locus
 0, 	// Z percent
 65, 	// Z transition duration
 480, 	// NX F1 locus
 30, 	// NX percent
 40, 	// NX transition duration
 750, 	// NX F2 locus
 120, 	// NX percent
 70, 	// NX transition duration
 2750, 	// NX F3 locus
 33, 	// NX percent
 70, 	// NX transition duration
 350, 	// V F1 locus
 75, 	// V percent
 30, 	// V transition duration
 1, 	// V F2 locus
 84, 	// V percent
 30, 	// V transition duration
 2000, 	// V F3 locus
 65, 	// V percent
 40, 	// V transition duration
 450, 	// ND F1 locus
 25, 	// ND percent
 30, 	// ND transition duration
 2160, 	// ND F2 locus
 65, 	// ND percent
 80, 	// ND transition duration
 2800, 	// ND F3 locus
 30, 	// ND percent
 80, 	// ND transition duration
 443, 	// PD F1 locus
 10, 	// PD percent
 30, 	// PD transition duration
 962, 	// PD F2 locus
 10, 	// PD percent
 40, 	// PD transition duration
 2704, 	// PD F3 locus
 10, 	// PD percent
 30, 	// PD transition duration
 181, 	// NJ F1 locus
 10, 	// NJ percent
 30, 	// NJ transition duration
 2039, 	// NJ F2 locus
 50, 	// NJ percent
 60, 	// NJ transition duration
 2520, 	// NJ F3 locus
 30, 	// NJ percent
 30, 	// NJ transition duration
 280, 	// SH F1 locus
 50, 	// SH percent
 50, 	// SH transition duration
 2050, 	// SH F2 locus
 15, 	// SH percent
 80, 	// SH transition duration
 2500, 	// SH F3 locus
 0, 	// SH percent
 95, 	// SH transition duration
 290, 	// TS F1 locus
 41, 	// TS percent
 40, 	// TS transition duration
 2032, 	// TS F2 locus
 64, 	// TS percent
 40, 	// TS transition duration
 3000, 	// TS F3 locus
 31, 	// TS percent
 60, 	// TS transition duration
 290, 	// DZ F1 locus
 41, 	// DZ percent
 40, 	// DZ transition duration
 2032, 	// DZ F2 locus
 64, 	// DZ percent
 40, 	// DZ transition duration
 3000, 	// DZ F3 locus
 31, 	// DZ percent
 60, 	// DZ transition duration
// Low
 0, 	// M F1 locus
 0, 	// M percent
 0, 	// M transition duration
 0, 	// M F2 locus
 0, 	// M percent
 0, 	// M transition duration
 0, 	// M F3 locus
 0, 	// M percent
 0, 	// M transition duration
 0, 	// N F1 locus
 0, 	// N percent
 0, 	// N transition duration
 0, 	// N F2 locus
 0, 	// N percent
 0, 	// N transition duration
 0, 	// N F3 locus
 0, 	// N percent
 0, 	// N transition duration
 0, 	// NH F1 locus
 0, 	// NH percent
 0, 	// NH transition duration
 0, 	// NH F2 locus
 0, 	// NH percent
 0, 	// NH transition duration
 0, 	// NH F3 locus
 0, 	// NH percent
 0, 	// NH transition duration
 0, 	// F F1 locus
 0, 	// F percent
 0, 	// F transition duration
 0, 	// F F2 locus
 0, 	// F percent
 0, 	// F transition duration
 0, 	// F F3 locus
 0, 	// F percent
 0, 	// F transition duration
 0, 	// S F1 locus
 0, 	// S percent
 0, 	// S transition duration
 0, 	// S F2 locus
 0, 	// S percent
 0, 	// S transition duration
 0, 	// S F3 locus
 0, 	// S percent
 0, 	// S transition duration
 0, 	// TD F1 locus
 0, 	// TD percent
 0, 	// TD transition duration
 0, 	// TD F2 locus
 0, 	// TD percent
 0, 	// TD transition duration
 0, 	// TD F3 locus
 0, 	// TD percent
 0, 	// TD transition duration
 0, 	// BD F1 locus
 0, 	// BD percent
 0, 	// BD transition duration
 0, 	// BD F2 locus
 0, 	// BD percent
 0, 	// BD transition duration
 0, 	// BD F3 locus
 0, 	// BD percent
 0, 	// BD transition duration
 0, 	// DD F1 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// DD F2 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// DD F3 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// GD F1 locus
 0, 	// GD percent
 0, 	// GD transition duration
 0, 	// GD F2 locus
 0, 	// GD percent
 0, 	// GD transition duration
 0, 	// GD F3 locus
 0, 	// GD percent
 0, 	// GD transition duration
 0, 	// JH F1 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F2 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F3 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// P F1 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// P F2 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// P F3 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// B F1 locus
 0, 	// B percent
 0, 	// B transition duration
 0, 	// B F2 locus
 0, 	// B percent
 0, 	// B transition duration
 0, 	// B F3 locus
 0, 	// B percent
 0, 	// B transition duration
 0, 	// T F1 locus
 0, 	// T percent
 0, 	// T transition duration
 0, 	// T F2 locus
 0, 	// T percent
 0, 	// T transition duration
 0, 	// T F3 locus
 0, 	// T percent
 0, 	// T transition duration
 0, 	// D F1 locus
 0, 	// D percent
 0, 	// D transition duration
 0, 	// D F2 locus
 0, 	// D percent
 0, 	// D transition duration
 0, 	// D F3 locus
 0, 	// D percent
 0, 	// D transition duration
 0, 	// K F1 locus
 0, 	// K percent
 0, 	// K transition duration
 0, 	// K F2 locus
 0, 	// K percent
 0, 	// K transition duration
 0, 	// K F3 locus
 0, 	// K percent
 0, 	// K transition duration
 0, 	// G F1 locus
 0, 	// G percent
 0, 	// G transition duration
 0, 	// G F2 locus
 0, 	// G percent
 0, 	// G transition duration
 0, 	// G F3 locus
 0, 	// G percent
 0, 	// G transition duration
 0, 	// CH F1 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F2 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F3 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// AO F1 locus
 0, 	// AO percent
 0, 	// AO transition duration
 0, 	// AO F2 locus
 0, 	// AO percent
 0, 	// AO transition duration
 0, 	// AO F3 locus
 0, 	// AO percent
 0, 	// AO transition duration
 -1, 	// KD F1 locus
 -1, 	// KD percent
 -1, 	// KD transition duration
 -1, 	// KD F2 locus
 -1, 	// KD percent
 -1, 	// KD transition duration
 -1, 	// KD F3 locus
 -1, 	// KD percent
 -1, 	// KD transition duration
 0, 	// Z F1 locus
 0, 	// Z percent
 0, 	// Z transition duration
 0, 	// Z F2 locus
 0, 	// Z percent
 0, 	// Z transition duration
 0, 	// Z F3 locus
 0, 	// Z percent
 0, 	// Z transition duration
 0, 	// NX F1 locus
 0, 	// NX percent
 0, 	// NX transition duration
 0, 	// NX F2 locus
 0, 	// NX percent
 0, 	// NX transition duration
 0, 	// NX F3 locus
 0, 	// NX percent
 0, 	// NX transition duration
 -1, 	// ND F1 locus
 -1, 	// ND percent
 -1, 	// ND transition duration
 -1, 	// ND F2 locus
 -1, 	// ND percent
 -1, 	// ND transition duration
 -1, 	// ND F3 locus
 -1, 	// ND percent
 -1, 	// ND transition duration
 -1, 	// PD F1 locus
 -1, 	// PD percent
 -1, 	// PD transition duration
 -1, 	// PD F2 locus
 -1, 	// PD percent
 -1, 	// PD transition duration
 -1, 	// PD F3 locus
 -1, 	// PD percent
 -1, 	// PD transition duration
 -1, 	// NJ F1 locus
 -1, 	// NJ percent
 -1, 	// NJ transition duration
 -1, 	// NJ F2 locus
 -1, 	// NJ percent
 -1, 	// NJ transition duration
 -1, 	// NJ F3 locus
 -1, 	// NJ percent
 -1, 	// NJ transition duration
 -1, 	// SH F1 locus
 -1, 	// SH percent
 -1, 	// SH transition duration
 -1, 	// SH F2 locus
 -1, 	// SH percent
 -1, 	// SH transition duration
 -1, 	// SH F3 locus
 -1, 	// SH percent
 -1, 	// SH transition duration
 -1, 	// TS F1 locus
 -1, 	// TS percent
 -1, 	// TS transition duration
 -1, 	// TS F2 locus
 -1, 	// TS percent
 -1, 	// TS transition duration
 -1, 	// TS F3 locus
 -1, 	// TS percent
 -1, 	// TS transition duration
 -1, 	// DZ F1 locus
 -1, 	// DZ percent
 -1, 	// DZ transition duration
 -1, 	// DZ F2 locus
 -1, 	// DZ percent
 -1, 	// DZ transition duration
 -1, 	// DZ F3 locus
 -1, 	// DZ percent
 -1, 	// DZ transition duration
 0};

const struct rom_data_s it_rom_data_def = {
it_inhdr_def,
it_mindur_def,
it_burdr_def,
it_begtyp_def,
it_endtyp_def,
it_place_def,
it_featb_def,
it_maltar_def,
it_femtar_def,
it_maldip_def,
it_femdip_def,
it_ptram_def,
it_plocu_def,
it_maleloc_def,
it_femloc_def
};


