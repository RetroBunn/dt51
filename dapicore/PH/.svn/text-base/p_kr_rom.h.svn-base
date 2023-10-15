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

#define KR_PH_PHONEME_COUNT 47
#define KR_PH_PHONEME_NAMES " _ IY EH AE UW UH UI OW AO AA YE YH YU YO YC YA WI WE WH WC WA M N NX P PH PP B T TH TT D K KH KK G S SS SH HX Y L DF JH CH CC WO "

// Inherent Duration (milliseconds)
const short kr_inhdr_def[] = {
 305, 	// _
 140, 	// IY
 250, 	// EH
 170, 	// AE
 143, 	// UW
 120, 	// UH
 165, 	// UI
 200, 	// OW
 180, 	// AO
 140, 	// AA
 240, 	// YE
 240, 	// YH
 195, 	// YU
 200, 	// YO
 200, 	// YC
 250, 	// YA
 200, 	// WI
 200, 	// WE
 300, 	// WH
 180, 	// WC
 190, 	// WA
 100, 	// M
 90, 	// N
 90, 	// NX
 75, 	// P
 100, 	// PH
 100, 	// PP
 75, 	// B
 75, 	// T
 100, 	// TH
 100, 	// TT
 75, 	// D
 75, 	// K
 100, 	// KH
 100, 	// KK
 75, 	// G
 120, 	// S
 140, 	// SS
 120, 	// SH
 80, 	// HX
 75, 	// Y
 125, 	// L
 70, 	// DF
 100, 	// JH
 150, 	// CH
 100, 	// CC
 190 }; 	//WO

// Minimum Duration (milliseconds)
const short kr_mindur_def[] = {
 7, 	// _
 80, 	// IY
 130, 	// EH
 67, 	// AE
 55, 	// UW
 65, 	// UH
 79, 	// UI
 110, 	// OW
 90, 	// AO
 75, 	// AA
 130, 	// YE
 135, 	// YH
 77, 	// YU
 100, 	// YO
 120, 	// YC
 130, 	// YA
 120, 	// WI
 109, 	// WE
 150, 	// WH
 100, 	// WC
 100, 	// WA
 60, 	// M
 40, 	// N
 50, 	// NX
 50, 	// P
 65, 	// PH
 65, 	// PP
 50, 	// B
 40, 	// T
 65, 	// TH
 65, 	// TT
 50, 	// D
 50, 	// K
 65, 	// KH
 65, 	// KK
 50, 	// G
 75, 	// S
 75, 	// SS
 60, 	// SH
 60, 	// HX
 30, 	// Y
 45, 	// L
 30, 	// DF
 75, 	// JH
 100, 	// CH
 75, 	// CC
 95 };	//WO

// Burst Duration (milliseconds)
const short kr_burdr_def[] = {
 0, 	//_
 0, 	//IY
 0, 	//EH
 0, 	//AE
 0, 	//UW
 0, 	//UH
 0, 	//UI
 0, 	//OW
 0, 	//AO
 0, 	//AA
 0, 	//YE
 0, 	//YH
 0, 	//YU
 0, 	//YO
 0, 	//YC
 0, 	//YA
 0, 	//WI
 0, 	//WE
 0, 	//WH
 0, 	//WC
 0, 	//WA
 0, 	//M
 0, 	//N
 0, 	//NX
 14, 	//P
 28, 	//PH
 7, 	//PP
 14, 	//B
 14, 	//T
 28, 	//TH
 7, 	//TT
 14, 	//D
 14, 	//K
 28, 	//KH
 7, 	//KK
 14, 	//G
 0, 	//S
 0, 	//SS
 0, 	//SH
 0, 	//HX
 0, 	//Y
 0, 	//L
 0, 	//DF
 65, 	//JH
 70, 	//CH
 50, 	//CC
 0 };	//WO

// Beginning Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short kr_begtyp_def[] = {
 4, 	// _
 1, 	// IY
 1, 	// EH
 1, 	// AE
 3, 	// UW
 2, 	// UH
 2, 	// UI
 3, 	// OW
 2, 	// AO
 2, 	// AA
 1, 	// YE
 1, 	// YH
 1, 	// YU
 1, 	// YO
 1, 	// YC
 1, 	// YA
 2, 	// WI
 2, 	// WE
 5, 	// WH
 2, 	// WC
 3, 	// WA
 4, 	// M
 4, 	// N
 4, 	// NX
 4, 	// P
 4, 	// PH
 4, 	// PP
 4, 	// B
 4, 	// T
 4, 	// TH
 4, 	// TT
 4, 	// D
 4, 	// K
 4, 	// KH
 4, 	// KK
 4, 	// G
 4, 	// S
 4, 	// SS
 4, 	// SH
 4, 	// HX
 1, 	// Y
 5, 	// L
 3, 	// DF
 4, 	// JH
 4, 	// CH
 4, 	// CC
 5 };	// WO

// Ending Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short kr_endtyp_def[] = {
 4, 	// _
 1, 	// IY
 1, 	// EH
 1, 	// AE
 3, 	// UW
 3, 	// UH
 1, 	// UI
 3, 	// OW
 3, 	// AO
 2, 	// AA
 1, 	// YE
 1, 	// YH
 3, 	// YU
 3, 	// YO
 3, 	// YC
 2, 	// YA
 1, 	// WI
 1, 	// WE
 1, 	// WH
 3, 	// WC
 2, 	// WA
 4, 	// M
 4, 	// N
 4, 	// NX
 4, 	// P
 4, 	// PH
 4, 	// PP
 4, 	// B
 4, 	// T
 4, 	// TH
 4, 	// TT
 4, 	// D
 4, 	// K
 4, 	// KH
 4, 	// KK
 4, 	// G
 4, 	// S
 4, 	// SS
 4, 	// SH
 4, 	// HX
 1, 	// Y
 4, 	// L
 3, 	// DF
 4, 	// JH
 4, 	// CH
 4, 	// CC
 3 };	// WO

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
const short kr_place_def[] = {
 0x0000, 	// _
 0x0000, 	// IY
 0x0000, 	// EH
 0x0000, 	// AE
 0x0000, 	// UW
 0x0000, 	// UH
 0x0000, 	// UI
 0x0000, 	// OW
 0x0000, 	// AO
 0x0000, 	// AA
 0x0000, 	// YE
 0x0000, 	// YH
 0x0000, 	// YU
 0x0000, 	// YO
 0x0000, 	// YC
 0x0000, 	// YA
 0x0000, 	// WI
 0x0000, 	// WE
 0x0000, 	// WH
 0x0000, 	// WC
 0x0000, 	// WA
 0x0001, 	// M
 0x0008, 	// N
 0x1000, 	// NX
 0x0001, 	// P
 0x0001, 	// PH
 0x0001, 	// PP
 0x0001, 	// B
 0x0008, 	// T
 0x0002, 	// TH
 0x0028, 	// TT
 0x0008, 	// D
 0x0010, 	// K
 0x1000, 	// KH
 0x0010, 	// KK
 0x0010, 	// G
 0x0008, 	// S
 0x0008, 	// SS
 0x0004, 	// SH
 0x0000, 	// HX
 0x00c0, 	// Y
 0x0000, 	// L
 0x0008, 	// DF
 0x0004, 	// JH
 0x0004, 	// CH
 0x000c, 	// CC
 0x0000 };	// WO

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
const int kr_featb_def[] = {
 0x00000012, 	// _
 0x0000001e, 	// IY
 0x0000001e, 	// EH
 0x0000001e, 	// AE
 0x0000001e, 	// UW
 0x0000001e, 	// UH
 0x0000001e, 	// UI
 0x0000001e, 	// OW
 0x0000001e, 	// AO
 0x0000001e, 	// AA
 0x0000001e, 	// YE
 0x0000001e, 	// YH
 0x0000001e, 	// YU
 0x0000041e, 	// YO
 0x0000041e, 	// YC
 0x0000041e, 	// YA
 0x0000001e, 	// WI
 0x0000001e, 	// WE
 0x0000001e, 	// WH
 0x0000001e, 	// WC
 0x0000001e, 	// WA
 0x0000259a, 	// M
 0x0000259a, 	// N
 0x0000259a, 	// NX
 0x00002960, 	// P
 0x00002960, 	// PH
 0x00002960, 	// PP
 0x00002962, 	// B
 0x00002960, 	// T
 0x00002960, 	// TH
 0x00002960, 	// TT
 0x00002962, 	// D
 0x00002960, 	// K
 0x00002960, 	// KH
 0x00002960, 	// KK
 0x00002962, 	// G
 0x00000120, 	// S
 0x00000120, 	// SS
 0x00000120, 	// SH
 0x00000110, 	// HX
 0x0000071a, 	// Y
 0x0000071a, 	// L
 0x0000211a, 	// DF
 0x00002922, 	// JH
 0x00002920, 	// CH
 0x00002960, 	// CC
 0x0000061e, 	// WO
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
const short kr_maltar_def[] = {
// ==== F1 ====
 -1, 	// _
 341, 	// IY
 346, 	// EH
 659, 	// AE
 300, 	// UW
 440, 	// UH
 325, 	// UI
 448, 	// OW
 570, 	// AO
 730, 	// AA
 -2, 	// YE
 -6, 	// YH
 -12, 	// YU
 -18, 	// YO
 -24, 	// YC
 -32, 	// YA
 285, 	// WI
 -40, 	// WE
 -46, 	// WH
 -56, 	// WC
 -62, 	// WA
 279, 	// M
 -68, 	// N
 305, 	// NX
 631, 	// P
 214, 	// PH
 312, 	// PP
 220, 	// B
 -74, 	// T
 350, 	// TH
 407, 	// TT
 300, 	// D
 686, 	// K
 350, 	// KH
 250, 	// KK
 305, 	// G
 427, 	// S
 427, 	// SS
 300, 	// SH
 -1, 	// HX
 280, 	// Y
 366, 	// L
 250, 	// DF
 305, 	// JH
 380, 	// CH
 365, 	// CC
 -80, 	// WO
// ==== F2 ====
 -1, 	// _
 1973, 	// IY
 1912, 	// EH
 1720, 	// AE
 870, 	// UW
 1020, 	// UH
 -86, 	// UI
 686, 	// OW
 840, 	// AO
 1090, 	// AA
 -96, 	// YE
 -100, 	// YH
 -106, 	// YU
 -112, 	// YO
 -120, 	// YC
 -128, 	// YA
 -134, 	// WI
 -142, 	// WE
 -148, 	// WH
 -158, 	// WC
 -164, 	// WA
 1372, 	// M
 -172, 	// N
 1029, 	// NX
 900, 	// P
 2502, 	// PH
 1523, 	// PP
 691, 	// B
 -178, 	// T
 1932, 	// TH
 1700, 	// TT
 1650, 	// D
 1505, 	// K
 1000, 	// KH
 1800, 	// KK
 1709, 	// G
 1322, 	// S
 1322, 	// SS
 1600, 	// SH
 -1, 	// HX
 2070, 	// Y
 -184, 	// L
 1688, 	// DF
 1485, 	// JH
 1650, 	// CH
 1892, 	// CC
 -190, 	// WO
// ==== F3 ====
 -1, 	// _
 2807, 	// IY
 2583, 	// EH
 2410, 	// AE
 2240, 	// UW
 2240, 	// UH
 -198, 	// UI
 2563, 	// OW
 2410, 	// AO
 2440, 	// AA
 -206, 	// YE
 -210, 	// YH
 -216, 	// YU
 -222, 	// YO
 -228, 	// YC
 -234, 	// YA
 -240, 	// WI
 -246, 	// WE
 -252, 	// WH
 -262, 	// WC
 -268, 	// WA
 2217, 	// M
 -274, 	// N
 2482, 	// NX
 2639, 	// P
 2299, 	// PH
 1984, 	// PP
 2177, 	// B
 2600, 	// T
 2563, 	// TH
 2600, 	// TT
 2600, 	// D
 1973, 	// K
 2274, 	// KH
 2500, 	// KK
 2583, 	// G
 2530, 	// S
 2530, 	// SS
 2550, 	// SH
 -1, 	// HX
 2570, 	// Y
 -280, 	// L
 2380, 	// DF
 2441, 	// JH
 2510, 	// CH
 2502, 	// CC
 -286, 	// WO
// ==== B1 ====
 -1, 	// _
 120, 	// IY
 90, 	// EH
 100, 	// AE
 120, 	// UW
 100, 	// UH
 180, 	// UI
 90, 	// OW
 160, 	// AO
 120, 	// AA
 100, 	// YE
 100, 	// YH
 100, 	// YU
 90, 	// YO
 160, 	// YC
 120, 	// YA
 90, 	// WI
 80, 	// WE
 90, 	// WH
 110, 	// WC
 120, 	// WA
 130, 	// M
 90, 	// N
 130, 	// NX
 200, 	// P
 200, 	// PH
 160, 	// PP
 90, 	// B
 200, 	// T
 461, 	// TH
 120, 	// TT
 90, 	// D
 200, 	// K
 100, 	// KH
 120, 	// KK
 90, 	// G
 100, 	// S
 232, 	// SS
 200, 	// SH
 300, 	// HX
 50, 	// Y
 150, 	// L
 120, 	// DF
 100, 	// JH
 200, 	// CH
 200, 	// CC
 90, 	// WO
// ==== B2 ====
 -1, 	// _
 120, 	// IY
 120, 	// EH
 150, 	// AE
 90, 	// UW
 170, 	// UH
 150, 	// UI
 70, 	// OW
 170, 	// AO
 300, 	// AA
 120, 	// YE
 150, 	// YH
 180, 	// YU
 70, 	// YO
 170, 	// YC
 150, 	// YA
 110, 	// WI
 200, 	// WE
 110, 	// WH
 100, 	// WC
 150, 	// WA
 120, 	// M
 200, 	// N
 250, 	// NX
 180, 	// P
 180, 	// PH
 150, 	// PP
 80, 	// B
 150, 	// T
 223, 	// TH
 180, 	// TT
 100, 	// D
 160, 	// K
 220, 	// KH
 160, 	// KK
 120, 	// G
 140, 	// S
 280, 	// SS
 240, 	// SH
 200, 	// HX
 200, 	// Y
 200, 	// L
 120, 	// DF
 80, 	// JH
 280, 	// CH
 280, 	// CC
 120, 	// WO
// ==== B3 ====
 -1, 	// _
 200, 	// IY
 250, 	// EH
 290, 	// AE
 220, 	// UW
 100, 	// UH
 240, 	// UI
 180, 	// OW
 140, 	// AO
 200, 	// AA
 250, 	// YE
 290, 	// YH
 180, 	// YU
 180, 	// YO
 140, 	// YC
 250, 	// YA
 350, 	// WI
 100, 	// WE
 150, 	// WH
 100, 	// WC
 250, 	// WA
 250, 	// M
 350, 	// N
 400, 	// NX
 180, 	// P
 180, 	// PH
 180, 	// PP
 130, 	// B
 240, 	// T
 270, 	// TH
 200, 	// TT
 240, 	// D
 280, 	// K
 250, 	// KH
 100, 	// KK
 180, 	// G
 300, 	// S
 330, 	// SS
 300, 	// SH
 220, 	// HX
 300, 	// Y
 180, 	// L
 140, 	// DF
 100, 	// JH
 250, 	// CH
 250, 	// CC
 240, 	// WO
// ==== AV ====
 0, 	// _
 65, 	// IY
 65, 	// EH
 65, 	// AE
 65, 	// UW
 65, 	// UH
 65, 	// UI
 65, 	// OW
 65, 	// AO
 65, 	// AA
 63, 	// YE
 63, 	// YH
 64, 	// YU
 65, 	// YO
 65, 	// YC
 65, 	// YA
 65, 	// WI
 65, 	// WE
 65, 	// WH
 65, 	// WC
 65, 	// WA
 60, 	// M
 60, 	// N
 60, 	// NX
 0, 	// P
 0, 	// PH
 0, 	// PP
 60, 	// B
 0, 	// T
 0, 	// TH
 0, 	// TT
 60, 	// D
 0, 	// K
 0, 	// KH
 0, 	// KK
 60, 	// G
 0, 	// S
 0, 	// SS
 0, 	// SH
 0, 	// HX
 65, 	// Y
 60, 	// L
 60, 	// DF
 0, 	// JH
 0, 	// CH
 0, 	// CC
 65 };	// WO

// Female - F1,F2,F3,B1,B2,B3,AV data for each phoneme
//     Negative numbers are offsets into femdip table (multi-part formants)
//     Positive numbers are actual values
const short kr_femtar_def[] = {
// ==== F1 ====
 -1, 	// _
 310, 	// IY
 -2, 	// EH
 602, 	// AE
 -8, 	// UW
 373, 	// UH
 -14, 	// UI
 499, 	// OW
 570, 	// AO
 986, 	// AA
 -18, 	// YE
 -24, 	// YH
 -28, 	// YU
 -32, 	// YO
 -36, 	// YC
 -40, 	// YA
 -44, 	// WI
 -48, 	// WE
 -52, 	// WH
 -56, 	// WC
 -60, 	// WA
 300, 	// M
 244, 	// N
 450, 	// NX
 379, 	// P
 375, 	// PH
 250, 	// PP
 250, 	// B
 370, 	// T
 370, 	// TH
 370, 	// TT
 300, 	// D
 280, 	// K
 -64, 	// KH
 -72, 	// KK
 265, 	// G
 340, 	// S
 340, 	// SS
 300, 	// SH
 -1, 	// HX
 220, 	// Y
 365, 	// L
 320, 	// DF
 380, 	// JH
 350, 	// CH
 408, 	// CC
 305, 	// WO
// ==== F2 ====
 -1, 	// _
 2814, 	// IY
 -80, 	// EH
 2195, 	// AE
 -86, 	// UW
 2704, 	// UH
 -92, 	// UI
 1029, 	// OW
 840, 	// AO
 1794, 	// AA
 -96, 	// YE
 -102, 	// YH
 -106, 	// YU
 -110, 	// YO
 -114, 	// YC
 -122, 	// YA
 -126, 	// WI
 -130, 	// WE
 -134, 	// WH
 -138, 	// WC
 -142, 	// WA
 1340, 	// M
 -146, 	// N
 2600, 	// NX
 1150, 	// P
 1727, 	// PH
 1150, 	// PP
 1150, 	// B
 1860, 	// T
 1860, 	// TH
 1860, 	// TT
 1650, 	// D
 1790, 	// K
 -150, 	// KH
 -158, 	// KK
 2316, 	// G
 1730, 	// S
 1730, 	// SS
 1600, 	// SH
 -1, 	// HX
 2100, 	// Y
 1340, 	// L
 -1, 	// DF
 2100, 	// JH
 1750, 	// CH
 1479, 	// CC
 -166, 	// WO
// ==== F3 ====
 -1, 	// _
 3471, 	// IY
 -174, 	// EH
 3013, 	// AE
 -180, 	// UW
 3222, 	// UH
 -186, 	// UI
 3068, 	// OW
 2410, 	// AO
 2957, 	// AA
 2848, 	// YE
 -190, 	// YH
 -194, 	// YU
 -198, 	// YO
 -202, 	// YC
 -210, 	// YA
 -214, 	// WI
 -218, 	// WE
 -222, 	// WH
 -226, 	// WC
 -230, 	// WA
 2190, 	// M
 -234, 	// N
 3100, 	// NX
 1920, 	// P
 2775, 	// PH
 2470, 	// PP
 2470, 	// B
 3020, 	// T
 3020, 	// TH
 3020, 	// TT
 2600, 	// D
 2200, 	// K
 -238, 	// KH
 -246, 	// KK
 3067, 	// G
 2800, 	// S
 2800, 	// SS
 2550, 	// SH
 -1, 	// HX
 3000, 	// Y
 2935, 	// L
 -1, 	// DF
 3150, 	// JH
 2700, 	// CH
 2445, 	// CC
 -254, 	// WO
// ==== B1 ====
 -1, 	// _
 75, 	// IY
 80, 	// EH
 70, 	// AE
 90, 	// UW
 120, 	// UH
 90, 	// UI
 90, 	// OW
 100, 	// AO
 130, 	// AA
 80, 	// YE
 70, 	// YH
 200, 	// YU
 106, 	// YO
 160, 	// YC
 130, 	// YA
 90, 	// WI
 80, 	// WE
 52, 	// WH
 90, 	// WC
 67, 	// WA
 120, 	// M
 120, 	// N
 200, 	// NX
 200, 	// P
 200, 	// PH
 100, 	// PP
 100, 	// B
 200, 	// T
 200, 	// TH
 200, 	// TT
 90, 	// D
 200, 	// K
 787, 	// KH
 641, 	// KK
 90, 	// G
 200, 	// S
 232, 	// SS
 200, 	// SH
 300, 	// HX
 120, 	// Y
 100, 	// L
 90, 	// DF
 70, 	// JH
 200, 	// CH
 300, 	// CC
 120, 	// WO
// ==== B2 ====
 -1, 	// _
 220, 	// IY
 160, 	// EH
 180, 	// AE
 100, 	// UW
 170, 	// UH
 100, 	// UI
 270, 	// OW
 120, 	// AO
 220, 	// AA
 160, 	// YE
 180, 	// YH
 260, 	// YU
 124, 	// YO
 220, 	// YC
 220, 	// YA
 110, 	// WI
 160, 	// WE
 232, 	// WH
 130, 	// WC
 398, 	// WA
 150, 	// M
 220, 	// N
 500, 	// NX
 180, 	// P
 180, 	// PH
 110, 	// PP
 110, 	// B
 150, 	// T
 150, 	// TH
 150, 	// TT
 100, 	// D
 160, 	// K
 322, 	// KH
 344, 	// KK
 120, 	// G
 200, 	// S
 487, 	// SS
 240, 	// SH
 200, 	// HX
 170, 	// Y
 100, 	// L
 100, 	// DF
 170, 	// JH
 280, 	// CH
 150, 	// CC
 160, 	// WO
// ==== B3 ====
 -1, 	// _
 270, 	// IY
 270, 	// EH
 250, 	// AE
 180, 	// UW
 100, 	// UH
 180, 	// UI
 180, 	// OW
 240, 	// AO
 160, 	// AA
 270, 	// YE
 250, 	// YH
 300, 	// YU
 228, 	// YO
 160, 	// YC
 160, 	// YA
 350, 	// WI
 270, 	// WE
 114, 	// WH
 110, 	// WC
 270, 	// WA
 250, 	// M
 350, 	// N
 600, 	// NX
 180, 	// P
 180, 	// PH
 150, 	// PP
 150, 	// B
 250, 	// T
 250, 	// TH
 250, 	// TT
 240, 	// D
 280, 	// K
 2265, 	// KH
 813, 	// KK
 180, 	// G
 200, 	// S
 890, 	// SS
 300, 	// SH
 220, 	// HX
 350, 	// Y
 120, 	// L
 170, 	// DF
 250, 	// JH
 250, 	// CH
 250, 	// CC
 80, 	// WO
// ==== AV ====
 0, 	// _
 65, 	// IY
 65, 	// EH
 65, 	// AE
 65, 	// UW
 65, 	// UH
 66, 	// UI
 65, 	// OW
 64, 	// AO
 64, 	// AA
 65, 	// YE
 63, 	// YH
 65, 	// YU
 65, 	// YO
 65, 	// YC
 65, 	// YA
 64, 	// WI
 63, 	// WE
 63, 	// WH
 63, 	// WC
 65, 	// WA
 60, 	// M
 60, 	// N
 64, 	// NX
 0, 	// P
 0, 	// PH
 0, 	// PP
 0, 	// B
 0, 	// T
 0, 	// TH
 0, 	// TT
 0, 	// D
 0, 	// K
 0, 	// KH
 0, 	// KK
 0, 	// G
 0, 	// S
 0, 	// SS
 0, 	// SH
 0, 	// HX
 64, 	// Y
 60, 	// L
 0, 	// DF
 0, 	// JH
 0, 	// CH
 0, 	// CC
 0 };	// WO

// Male - F1,F1T,F2,F2T,F3,F3T,B1,B1T,B2,B2T,B3,B3T,AV,AVT data for Multi-part formants
const short kr_maldip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _
 0, 	// _
 330, 	// YE F1
 10, 	// YE F1 duration
 530, 	// YE F1
 -1, 	// YE F1 duration
 407, 	// YH F1
 10, 	// YH F1 duration
 660, 	// YH F1
 150, 	// YH F1 duration
 660, 	// YH F1
 -1, 	// YH F1 duration
 407, 	// YU F1
 20, 	// YU F1 duration
 300, 	// YU F1
 50, 	// YU F1 duration
 300, 	// YU F1
 -1, 	// YU F1 duration
 427, 	// YO F1
 20, 	// YO F1 duration
 610, 	// YO F1
 195, 	// YO F1 duration
 610, 	// YO F1
 -1, 	// YO F1 duration
 305, 	// YC F1
 70, 	// YC F1 duration
 488, 	// YC F1
 150, 	// YC F1 duration
 305, 	// YC F1
 195, 	// YC F1 duration
 305, 	// YC F1
 -1, 	// YC F1 duration
 325, 	// YA F1
 10, 	// YA F1 duration
 601, 	// YA F1
 85, 	// YA F1 duration
 772, 	// YA F1
 160, 	// YA F1 duration
 772, 	// YA F1
 -1, 	// YA F1 duration
 336, 	// WE F1
 70, 	// WE F1 duration
 530, 	// WE F1
 130, 	// WE F1 duration
 530, 	// WE F1
 -1, 	// WE F1 duration
 305, 	// WH F1
 10, 	// WH F1 duration
 325, 	// WH F1
 90, 	// WH F1 duration
 590, 	// WH F1
 180, 	// WH F1 duration
 488, 	// WH F1
 295, 	// WH F1 duration
 488, 	// WH F1
 -1, 	// WH F1 duration
 336, 	// WC F1
 20, 	// WC F1 duration
 570, 	// WC F1
 65, 	// WC F1 duration
 570, 	// WC F1
 -1, 	// WC F1 duration
 488, 	// WA F1
 10, 	// WA F1 duration
 692, 	// WA F1
 80, 	// WA F1 duration
 686, 	// WA F1
 -1, 	// WA F1 duration
 269, 	// N F1
 10, 	// N F1 duration
 260, 	// N F1
 85, 	// N F1 duration
 260, 	// N F1
 -1, 	// N F1 duration
 366, 	// T F1
 10, 	// T F1 duration
 325, 	// T F1
 70, 	// T F1 duration
 325, 	// T F1
 -1, 	// T F1 duration
 336, 	// WO F1
 10, 	// WO F1 duration
 453, 	// WO F1
 235, 	// WO F1 duration
 453, 	// WO F1
 -1, 	// WO F1 duration
 1437, 	// UI F2
 20, 	// UI F2 duration
 1953, 	// UI F2
 55, 	// UI F2 duration
 2038, 	// UI F2
 97, 	// UI F2 duration
 1909, 	// UI F2
 160, 	// UI F2 duration
 1909, 	// UI F2
 -1, 	// UI F2 duration
 2160, 	// YE F2
 10, 	// YE F2 duration
 1840, 	// YE F2
 -1, 	// YE F2 duration
 1871, 	// YH F2
 10, 	// YH F2 duration
 1720, 	// YH F2
 150, 	// YH F2 duration
 1720, 	// YH F2
 -1, 	// YH F2 duration
 1871, 	// YU F2
 20, 	// YU F2 duration
 870, 	// YU F2
 50, 	// YU F2 duration
 870, 	// YU F2
 -1, 	// YU F2 duration
 1871, 	// YO F2
 20, 	// YO F2 duration
 1097, 	// YO F2
 105, 	// YO F2 duration
 922, 	// YO F2
 195, 	// YO F2 duration
 922, 	// YO F2
 -1, 	// YO F2 duration
 2014, 	// YC F2
 10, 	// YC F2 duration
 1871, 	// YC F2
 33, 	// YC F2 duration
 976, 	// YC F2
 106, 	// YC F2 duration
 976, 	// YC F2
 -1, 	// YC F2 duration
 2124, 	// YA F2
 10, 	// YA F2 duration
 1351, 	// YA F2
 155, 	// YA F2 duration
 1351, 	// YA F2
 -1, 	// YA F2 duration
 651, 	// WI F2
 10, 	// WI F2 duration
 2145, 	// WI F2
 85, 	// WI F2 duration
 2209, 	// WI F2
 100, 	// WI F2 duration
 2209, 	// WI F2
 -1, 	// WI F2 duration
 732, 	// WE F2
 70, 	// WE F2 duration
 1840, 	// WE F2
 130, 	// WE F2 duration
 1840, 	// WE F2
 -1, 	// WE F2 duration
 610, 	// WH F2
 10, 	// WH F2 duration
 1037, 	// WH F2
 90, 	// WH F2 duration
 1607, 	// WH F2
 180, 	// WH F2 duration
 1871, 	// WH F2
 295, 	// WH F2 duration
 1871, 	// WH F2
 -1, 	// WH F2 duration
 732, 	// WC F2
 20, 	// WC F2 duration
 840, 	// WC F2
 80, 	// WC F2 duration
 840, 	// WC F2
 -1, 	// WC F2 duration
 858, 	// WA F2
 10, 	// WA F2 duration
 1078, 	// WA F2
 60, 	// WA F2 duration
 1322, 	// WA F2
 185, 	// WA F2 duration
 1322, 	// WA F2
 -1, 	// WA F2 duration
 1802, 	// N F2
 10, 	// N F2 duration
 1749, 	// N F2
 85, 	// N F2 duration
 1749, 	// N F2
 -1, 	// N F2 duration
 1700, 	// T F2
 10, 	// T F2 duration
 773, 	// T F2
 70, 	// T F2 duration
 773, 	// T F2
 -1, 	// T F2 duration
 1523, 	// L F2
 10, 	// L F2 duration
 1608, 	// L F2
 30, 	// L F2 duration
 1608, 	// L F2
 -1, 	// L F2 duration
 732, 	// WO F2
 10, 	// WO F2 duration
 689, 	// WO F2
 50, 	// WO F2 duration
 1220, 	// WO F2
 235, 	// WO F2 duration
 1220, 	// WO F2
 -1, 	// WO F2 duration
 2217, 	// UI F3
 40, 	// UI F3 duration
 2644, 	// UI F3
 97, 	// UI F3 duration
 2482, 	// UI F3
 160, 	// UI F3 duration
 2482, 	// UI F3
 -1, 	// UI F3 duration
 3000, 	// YE F3
 40, 	// YE F3 duration
 2827, 	// YE F3
 -1, 	// YE F3 duration
 2156, 	// YH F3
 10, 	// YH F3 duration
 2410, 	// YH F3
 150, 	// YH F3 duration
 2410, 	// YH F3
 -1, 	// YH F3 duration
 2156, 	// YU F3
 20, 	// YU F3 duration
 2240, 	// YU F3
 50, 	// YU F3 duration
 2240, 	// YU F3
 -1, 	// YU F3 duration
 2467, 	// YO F3
 20, 	// YO F3 duration
 2187, 	// YO F3
 90, 	// YO F3 duration
 2187, 	// YO F3
 -1, 	// YO F3 duration
 2949, 	// YC F3
 10, 	// YC F3 duration
 2381, 	// YC F3
 65, 	// YC F3 duration
 2381, 	// YC F3
 -1, 	// YC F3 duration
 3072, 	// YA F3
 10, 	// YA F3 duration
 2488, 	// YA F3
 101, 	// YA F3 duration
 2488, 	// YA F3
 -1, 	// YA F3 duration
 2075, 	// WI F3
 10, 	// WI F3 duration
 3011, 	// WI F3
 100, 	// WI F3 duration
 3011, 	// WI F3
 -1, 	// WI F3 duration
 2290, 	// WE F3
 70, 	// WE F3 duration
 2480, 	// WE F3
 130, 	// WE F3 duration
 2480, 	// WE F3
 -1, 	// WE F3 duration
 2187, 	// WH F3
 10, 	// WH F3 duration
 2155, 	// WH F3
 90, 	// WH F3 duration
 2423, 	// WH F3
 230, 	// WH F3 duration
 2441, 	// WH F3
 295, 	// WH F3 duration
 2441, 	// WH F3
 -1, 	// WH F3 duration
 2290, 	// WC F3
 20, 	// WC F3 duration
 2410, 	// WC F3
 80, 	// WC F3 duration
 2410, 	// WC F3
 -1, 	// WC F3 duration
 2445, 	// WA F3
 10, 	// WA F3 duration
 2543, 	// WA F3
 185, 	// WA F3 duration
 2543, 	// WA F3
 -1, 	// WA F3 duration
 2488, 	// N F3
 10, 	// N F3 duration
 2563, 	// N F3
 85, 	// N F3 duration
 2563, 	// N F3
 -1, 	// N F3 duration
 2258, 	// L F3
 10, 	// L F3 duration
 2381, 	// L F3
 30, 	// L F3 duration
 2381, 	// L F3
 -1, 	// L F3 duration
 2290, 	// WO F3
 10, 	// WO F3 duration
 2724, 	// WO F3
 50, 	// WO F3 duration
 2563, 	// WO F3
 235, 	// WO F3 duration
 2563, 	// WO F3
 -1, 	// WO F3 duration
// ====== Bandwidths and duration ======
// ====== Amplitude of Voicing ======
 0};

// Female diphthongs
const short kr_femdip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _
 0, 	// _
 650, 	// EH F1
 90, 	// EH F1 duration
 680, 	// EH F1
 140, 	// EH F1 duration
 680, 	// EH F1
 -1, 	// EH F1 duration
 430, 	// UW F1
 40, 	// UW F1 duration
 400, 	// UW F1
 180, 	// UW F1 duration
 400, 	// UW F1
 -1, 	// UW F1 duration
 385, 	// UI F1
 10, 	// UI F1 duration
 407, 	// UI F1
 -1, 	// UI F1 duration
 285, 	// YE F1
 90, 	// YE F1 duration
 448, 	// YE F1
 190, 	// YE F1 duration
 300, 	// YE F1
 -1, 	// YE F1 duration
 410, 	// YH F1
 10, 	// YH F1 duration
 860, 	// YH F1
 -1, 	// YH F1 duration
 280, 	// YU F1
 10, 	// YU F1 duration
 430, 	// YU F1
 -1, 	// YU F1 duration
 280, 	// YO F1
 10, 	// YO F1 duration
 429, 	// YO F1
 -1, 	// YO F1 duration
 244, 	// YC F1
 70, 	// YC F1 duration
 570, 	// YC F1
 -1, 	// YC F1 duration
 280, 	// YA F1
 10, 	// YA F1 duration
 810, 	// YA F1
 -1, 	// YA F1 duration
 337, 	// WI F1
 10, 	// WI F1 duration
 350, 	// WI F1
 -1, 	// WI F1 duration
 337, 	// WE F1
 10, 	// WE F1 duration
 651, 	// WE F1
 -1, 	// WE F1 duration
 330, 	// WH F1
 10, 	// WH F1 duration
 860, 	// WH F1
 -1, 	// WH F1 duration
 330, 	// WC F1
 10, 	// WC F1 duration
 730, 	// WC F1
 -1, 	// WC F1 duration
 330, 	// WA F1
 10, 	// WA F1 duration
 810, 	// WA F1
 -1, 	// WA F1 duration
 1199, 	// KH F1
 65, 	// KH F1 duration
 156, 	// KH F1
 31, 	// KH F1 duration
 319, 	// KH F1
 144, 	// KH F1 duration
 437, 	// KH F1
 -1, 	// KH F1 duration
 681, 	// KK F1
 16, 	// KK F1 duration
 474, 	// KK F1
 113, 	// KK F1 duration
 418, 	// KK F1
 14, 	// KK F1 duration
 412, 	// KK F1
 -1, 	// KK F1 duration
 2100, 	// EH F2
 90, 	// EH F2 duration
 2000, 	// EH F2
 140, 	// EH F2 duration
 2000, 	// EH F2
 -1, 	// EH F2 duration
 1370, 	// UW F2
 40, 	// UW F2 duration
 1160, 	// UW F2
 180, 	// UW F2 duration
 1120, 	// UW F2
 -1, 	// UW F2 duration
 1071, 	// UI F2
 10, 	// UI F2 duration
 1627, 	// UI F2
 -1, 	// UI F2 duration
 2441, 	// YE F2
 10, 	// YE F2 duration
 2360, 	// YE F2
 170, 	// YE F2 duration
 2522, 	// YE F2
 -1, 	// YE F2 duration
 2522, 	// YH F2
 10, 	// YH F2 duration
 2040, 	// YH F2
 -1, 	// YH F2 duration
 2600, 	// YU F2
 10, 	// YU F2 duration
 1370, 	// YU F2
 -1, 	// YU F2 duration
 2600, 	// YO F2
 10, 	// YO F2 duration
 875, 	// YO F2
 -1, 	// YO F2 duration
 2299, 	// YC F2
 70, 	// YC F2 duration
 1627, 	// YC F2
 106, 	// YC F2 duration
 1587, 	// YC F2
 145, 	// YC F2 duration
 1729, 	// YC F2
 -1, 	// YC F2 duration
 2600, 	// YA F2
 10, 	// YA F2 duration
 1350, 	// YA F2
 -1, 	// YA F2 duration
 799, 	// WI F2
 10, 	// WI F2 duration
 2700, 	// WI F2
 -1, 	// WI F2 duration
 799, 	// WE F2
 10, 	// WE F2 duration
 2000, 	// WE F2
 -1, 	// WE F2 duration
 680, 	// WH F2
 10, 	// WH F2 duration
 2040, 	// WH F2
 -1, 	// WH F2 duration
 680, 	// WC F2
 10, 	// WC F2 duration
 1160, 	// WC F2
 -1, 	// WC F2 duration
 864, 	// WA F2
 10, 	// WA F2 duration
 1350, 	// WA F2
 -1, 	// WA F2 duration
 1993, 	// N F2
 40, 	// N F2 duration
 1892, 	// N F2
 -1, 	// N F2 duration
 1700, 	// KH F2
 65, 	// KH F2 duration
 1725, 	// KH F2
 31, 	// KH F2 duration
 1487, 	// KH F2
 144, 	// KH F2 duration
 1562, 	// KH F2
 -1, 	// KH F2 duration
 1510, 	// KK F2
 16, 	// KK F2 duration
 1918, 	// KK F2
 113, 	// KK F2 duration
 1544, 	// KK F2
 14, 	// KK F2 duration
 1538, 	// KK F2
 -1, 	// KK F2 duration
 651, 	// WO F2
 10, 	// WO F2 duration
 751, 	// WO F2
 55, 	// WO F2 duration
 1136, 	// WO F2
 114, 	// WO F2 duration
 1136, 	// WO F2
 -1, 	// WO F2 duration
 2950, 	// EH F3
 90, 	// EH F3 duration
 3000, 	// EH F3
 140, 	// EH F3 duration
 3000, 	// EH F3
 -1, 	// EH F3 duration
 2800, 	// UW F3
 40, 	// UW F3 duration
 2700, 	// UW F3
 180, 	// UW F3 duration
 2700, 	// UW F3
 -1, 	// UW F3 duration
 2875, 	// UI F3
 10, 	// UI F3 duration
 2766, 	// UI F3
 -1, 	// UI F3 duration
 3684, 	// YH F3
 10, 	// YH F3 duration
 2850, 	// YH F3
 -1, 	// YH F3 duration
 3500, 	// YU F3
 10, 	// YU F3 duration
 2800, 	// YU F3
 -1, 	// YU F3 duration
 3500, 	// YO F3
 10, 	// YO F3 duration
 2787, 	// YO F3
 -1, 	// YO F3 duration
 3011, 	// YC F3
 70, 	// YC F3 duration
 2543, 	// YC F3
 106, 	// YC F3 duration
 2461, 	// YC F3
 145, 	// YC F3 duration
 2360, 	// YC F3
 -1, 	// YC F3 duration
 3500, 	// YA F3
 10, 	// YA F3 duration
 2950, 	// YA F3
 -1, 	// YA F3 duration
 2768, 	// WI F3
 10, 	// WI F3 duration
 2800, 	// WI F3
 -1, 	// WI F3 duration
 2768, 	// WE F3
 10, 	// WE F3 duration
 3000, 	// WE F3
 -1, 	// WE F3 duration
 2750, 	// WH F3
 10, 	// WH F3 duration
 2850, 	// WH F3
 -1, 	// WH F3 duration
 2750, 	// WC F3
 10, 	// WC F3 duration
 2920, 	// WC F3
 -1, 	// WC F3 duration
 2927, 	// WA F3
 10, 	// WA F3 duration
 2950, 	// WA F3
 -1, 	// WA F3 duration
 2853, 	// N F3
 95, 	// N F3 duration
 3454, 	// N F3
 -1, 	// N F3 duration
 2458, 	// KH F3
 65, 	// KH F3 duration
 2590, 	// KH F3
 31, 	// KH F3 duration
 2673, 	// KH F3
 144, 	// KH F3 duration
 2815, 	// KH F3
 -1, 	// KH F3 duration
 1884, 	// KK F3
 16, 	// KK F3 duration
 2870, 	// KK F3
 113, 	// KK F3 duration
 2674, 	// KK F3
 14, 	// KK F3 duration
 2984, 	// KK F3
 -1, 	// KK F3 duration
 2441, 	// WO F3
 10, 	// WO F3 duration
 2766, 	// WO F3
 73, 	// WO F3 duration
 2482, 	// WO F3
 128, 	// WO F3 duration
 2482, 	// WO F3
 -1, 	// WO F3 duration
// ====== Bandwidths and duration ======
// ====== Amplitude of Voicing ======
 0};

// Offsets into Amplitude data
const short kr_ptram_def[] = {
 0, 	// _
 0, 	// IY
 0, 	// EH
 0, 	// AE
 0, 	// UW
 0, 	// UH
 0, 	// UI
 0, 	// OW
 0, 	// AO
 0, 	// AA
 0, 	// YE
 0, 	// YH
 0, 	// YU
 0, 	// YO
 0, 	// YC
 0, 	// YA
 0, 	// WI
 0, 	// WE
 0, 	// WH
 0, 	// WC
 0, 	// WA
 0, 	// M
 0, 	// N
 0, 	// NX
 1, 	// P
 31, 	// PH
 61, 	// PP
 91, 	// B
 121, 	// T
 151, 	// TH
 181, 	// TT
 211, 	// D
 241, 	// K
 271, 	// KH
 301, 	// KK
 331, 	// G
 361, 	// S
 391, 	// SS
 421, 	// SH
 0, 	// HX
 451, 	// Y
 0, 	// L
 0, 	// DF
 481, 	// JH
 511, 	// CH
 541, 	// CC
 0 };	// WO

// Offsets into Locus data
const short kr_plocu_def[] = {
// ==== Front ====
 0, 	// _
 0, 	// IY
 0, 	// EH
 0, 	// AE
 0, 	// UW
 0, 	// UH
 0, 	// UI
 0, 	// OW
 0, 	// AO
 0, 	// AA
 0, 	// YE
 0, 	// YH
 0, 	// YU
 0, 	// YO
 0, 	// YC
 0, 	// YA
 0, 	// WI
 0, 	// WE
 0, 	// WH
 0, 	// WC
 0, 	// WA
 1, 	// M
 10, 	// N
 19, 	// NX
 28, 	// P
 37, 	// PH
 46, 	// PP
 55, 	// B
 64, 	// T
 73, 	// TH
 82, 	// TT
 91, 	// D
 100, 	// K
 109, 	// KH
 118, 	// KK
 127, 	// G
 136, 	// S
 145, 	// SS
 154, 	// SH
 0, 	// HX
 163, 	// Y
 0, 	// L
 172, 	// DF
 181, 	// JH
 190, 	// CH
 199, 	// CC
 0, 	// WO
// ==== Back ====
 0, 	// _
 0, 	// IY
 0, 	// EH
 0, 	// AE
 0, 	// UW
 0, 	// UH
 0, 	// UI
 0, 	// OW
 0, 	// AO
 0, 	// AA
 0, 	// YE
 0, 	// YH
 0, 	// YU
 0, 	// YO
 0, 	// YC
 0, 	// YA
 0, 	// WI
 0, 	// WE
 0, 	// WH
 0, 	// WC
 0, 	// WA
 208, 	// M
 217, 	// N
 226, 	// NX
 235, 	// P
 244, 	// PH
 253, 	// PP
 262, 	// B
 271, 	// T
 280, 	// TH
 289, 	// TT
 298, 	// D
 307, 	// K
 316, 	// KH
 325, 	// KK
 334, 	// G
 343, 	// S
 352, 	// SS
 361, 	// SH
 0, 	// HX
 370, 	// Y
 0, 	// L
 379, 	// DF
 388, 	// JH
 397, 	// CH
 406, 	// CC
 0, 	// WO
// ==== Round ====
 0, 	// _
 0, 	// IY
 0, 	// EH
 0, 	// AE
 0, 	// UW
 0, 	// UH
 0, 	// UI
 0, 	// OW
 0, 	// AO
 0, 	// AA
 0, 	// YE
 0, 	// YH
 0, 	// YU
 0, 	// YO
 0, 	// YC
 0, 	// YA
 0, 	// WI
 0, 	// WE
 0, 	// WH
 0, 	// WC
 0, 	// WA
 415, 	// M
 424, 	// N
 433, 	// NX
 442, 	// P
 451, 	// PH
 460, 	// PP
 469, 	// B
 478, 	// T
 487, 	// TH
 496, 	// TT
 505, 	// D
 514, 	// K
 523, 	// KH
 532, 	// KK
 541, 	// G
 550, 	// S
 559, 	// SS
 568, 	// SH
 0, 	// HX
 577, 	// Y
 0, 	// L
 586, 	// DF
 595, 	// JH
 604, 	// CH
 613, 	// CC
 0, 	// WO
// ==== Low ====
 0, 	// _
 0, 	// IY
 0, 	// EH
 0, 	// AE
 0, 	// UW
 0, 	// UH
 0, 	// UI
 0, 	// OW
 0, 	// AO
 0, 	// AA
 0, 	// YE
 0, 	// YH
 0, 	// YU
 0, 	// YO
 0, 	// YC
 0, 	// YA
 0, 	// WI
 0, 	// WE
 0, 	// WH
 0, 	// WC
 0, 	// WA
 622, 	// M
 631, 	// N
 0, 	// NX
 640, 	// P
 649, 	// PH
 658, 	// PP
 0, 	// B
 667, 	// T
 676, 	// TH
 685, 	// TT
 694, 	// D
 703, 	// K
 712, 	// KH
 721, 	// KK
 730, 	// G
 739, 	// S
 748, 	// SS
 757, 	// SH
 0, 	// HX
 0, 	// Y
 0, 	// L
 0, 	// DF
 0, 	// JH
 766, 	// CH
 775, 	// CC
 0 };	// WO

// Male Locus data
const short kr_maleloc_def[] = {
 0, 
// Front
 280, 	// M F1 locus
 30, 	// M percent
 30, 	// M transition duration
 1200, 	// M F2 locus
 10, 	// M percent
 25, 	// M transition duration
 2000, 	// M F3 locus
 30, 	// M percent
 40, 	// M transition duration
 256, 	// N F1 locus
 25, 	// N percent
 23, 	// N transition duration
 1459, 	// N F2 locus
 25, 	// N percent
 23, 	// N transition duration
 2403, 	// N F3 locus
 25, 	// N percent
 23, 	// N transition duration
 220, 	// NX F1 locus
 25, 	// NX percent
 40, 	// NX transition duration
 2200, 	// NX F2 locus
 15, 	// NX percent
 60, 	// NX transition duration
 3000, 	// NX F3 locus
 105, 	// NX percent
 60, 	// NX transition duration
 350, 	// P F1 locus
 55, 	// P percent
 20, 	// P transition duration
 950, 	// P F2 locus
 56, 	// P percent
 50, 	// P transition duration
 2200, 	// P F3 locus
 25, 	// P percent
 50, 	// P transition duration
 350, 	// PH F1 locus
 55, 	// PH percent
 20, 	// PH transition duration
 950, 	// PH F2 locus
 56, 	// PH percent
 50, 	// PH transition duration
 2200, 	// PH F3 locus
 25, 	// PH percent
 50, 	// PH transition duration
 350, 	// PP F1 locus
 55, 	// PP percent
 20, 	// PP transition duration
 950, 	// PP F2 locus
 35, 	// PP percent
 30, 	// PP transition duration
 2200, 	// PP F3 locus
 25, 	// PP percent
 45, 	// PP transition duration
 330, 	// B F1 locus
 55, 	// B percent
 20, 	// B transition duration
 900, 	// B F2 locus
 56, 	// B percent
 30, 	// B transition duration
 2200, 	// B F3 locus
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
 320, 	// TH F1 locus
 43, 	// TH percent
 35, 	// TH transition duration
 1700, 	// TH F2 locus
 66, 	// TH percent
 35, 	// TH transition duration
 2650, 	// TH F3 locus
 30, 	// TH percent
 45, 	// TH transition duration
 450, 	// TT F1 locus
 43, 	// TT percent
 35, 	// TT transition duration
 1450, 	// TT F2 locus
 66, 	// TT percent
 35, 	// TT transition duration
 2600, 	// TT F3 locus
 30, 	// TT percent
 45, 	// TT transition duration
 250, 	// D F1 locus
 43, 	// D percent
 35, 	// D transition duration
 1800, 	// D F2 locus
 66, 	// D percent
 35, 	// D transition duration
 2650, 	// D F3 locus
 30, 	// D percent
 45, 	// D transition duration
 280, 	// K F1 locus
 33, 	// K percent
 45, 	// K transition duration
 1990, 	// K F2 locus
 20, 	// K percent
 55, 	// K transition duration
 3000, 	// K F3 locus
 125, 	// K percent
 50, 	// K transition duration
 280, 	// KH F1 locus
 67, 	// KH percent
 45, 	// KH transition duration
 1980, 	// KH F2 locus
 20, 	// KH percent
 55, 	// KH transition duration
 3000, 	// KH F3 locus
 117, 	// KH percent
 50, 	// KH transition duration
 250, 	// KK F1 locus
 33, 	// KK percent
 45, 	// KK transition duration
 2100, 	// KK F2 locus
 20, 	// KK percent
 50, 	// KK transition duration
 3000, 	// KK F3 locus
 70, 	// KK percent
 50, 	// KK transition duration
 250, 	// G F1 locus
 33, 	// G percent
 45, 	// G transition duration
 1990, 	// G F2 locus
 20, 	// G percent
 55, 	// G transition duration
 3000, 	// G F3 locus
 20, 	// G percent
 50, 	// G transition duration
 350, 	// S F1 locus
 50, 	// S percent
 50, 	// S transition duration
 1420, 	// S F2 locus
 50, 	// S percent
 50, 	// S transition duration
 2500, 	// S F3 locus
 50, 	// S percent
 50, 	// S transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1440, 	// SS F2 locus
 40, 	// SS percent
 50, 	// SS transition duration
 2550, 	// SS F3 locus
 0, 	// SS percent
 70, 	// SS transition duration
 285, 	// SH F1 locus
 25, 	// SH percent
 45, 	// SH transition duration
 1759, 	// SH F2 locus
 30, 	// SH percent
 40, 	// SH transition duration
 2640, 	// SH F3 locus
 25, 	// SH percent
 40, 	// SH transition duration
 -1, 	// Y F1 locus
 -1, 	// Y percent
 -1, 	// Y transition duration
 -1, 	// Y F2 locus
 -1, 	// Y percent
 -1, 	// Y transition duration
 -1, 	// Y F3 locus
 -1, 	// Y percent
 -1, 	// Y transition duration
 350, 	// DF F1 locus
 50, 	// DF percent
 30, 	// DF transition duration
 1740, 	// DF F2 locus
 96, 	// DF percent
 35, 	// DF transition duration
 2360, 	// DF F3 locus
 60, 	// DF percent
 45, 	// DF transition duration
 240, 	// JH F1 locus
 32, 	// JH percent
 50, 	// JH transition duration
 1750, 	// JH F2 locus
 25, 	// JH percent
 50, 	// JH transition duration
 2750, 	// JH F3 locus
 19, 	// JH percent
 50, 	// JH transition duration
 240, 	// CH F1 locus
 32, 	// CH percent
 55, 	// CH transition duration
 1750, 	// CH F2 locus
 25, 	// CH percent
 70, 	// CH transition duration
 2510, 	// CH F3 locus
 19, 	// CH percent
 70, 	// CH transition duration
 346, 	// CC F1 locus
 54, 	// CC percent
 55, 	// CC transition duration
 1851, 	// CC F2 locus
 25, 	// CC percent
 70, 	// CC transition duration
 2604, 	// CC F3 locus
 19, 	// CC percent
 70, 	// CC transition duration
// Back
 346, 	// M F1 locus
 50, 	// M percent
 25, 	// M transition duration
 1465, 	// M F2 locus
 50, 	// M percent
 25, 	// M transition duration
 2640, 	// M F3 locus
 75, 	// M percent
 26, 	// M transition duration
 325, 	// N F1 locus
 25, 	// N percent
 30, 	// N transition duration
 1442, 	// N F2 locus
 25, 	// N percent
 34, 	// N transition duration
 2533, 	// N F3 locus
 56, 	// N percent
 41, 	// N transition duration
 220, 	// NX F1 locus
 25, 	// NX percent
 40, 	// NX transition duration
 1800, 	// NX F2 locus
 20, 	// NX percent
 70, 	// NX transition duration
 2150, 	// NX F3 locus
 20, 	// NX percent
 70, 	// NX transition duration
 350, 	// P F1 locus
 45, 	// P percent
 25, 	// P transition duration
 920, 	// P F2 locus
 46, 	// P percent
 50, 	// P transition duration
 1900, 	// P F3 locus
 40, 	// P percent
 50, 	// P transition duration
 350, 	// PH F1 locus
 45, 	// PH percent
 25, 	// PH transition duration
 920, 	// PH F2 locus
 46, 	// PH percent
 50, 	// PH transition duration
 1900, 	// PH F3 locus
 40, 	// PH percent
 50, 	// PH transition duration
 350, 	// PP F1 locus
 45, 	// PP percent
 25, 	// PP transition duration
 920, 	// PP F2 locus
 46, 	// PP percent
 30, 	// PP transition duration
 2250, 	// PP F3 locus
 45, 	// PP percent
 30, 	// PP transition duration
 330, 	// B F1 locus
 45, 	// B percent
 25, 	// B transition duration
 920, 	// B F2 locus
 46, 	// B percent
 30, 	// B transition duration
 2250, 	// B F3 locus
 40, 	// B percent
 50, 	// B transition duration
 320, 	// T F1 locus
 43, 	// T percent
 50, 	// T transition duration
 1700, 	// T F2 locus
 25, 	// T percent
 25, 	// T transition duration
 2600, 	// T F3 locus
 25, 	// T percent
 25, 	// T transition duration
 320, 	// TH F1 locus
 43, 	// TH percent
 50, 	// TH transition duration
 1700, 	// TH F2 locus
 10, 	// TH percent
 75, 	// TH transition duration
 2600, 	// TH F3 locus
 10, 	// TH percent
 50, 	// TH transition duration
 610, 	// TT F1 locus
 43, 	// TT percent
 50, 	// TT transition duration
 1416, 	// TT F2 locus
 10, 	// TT percent
 75, 	// TT transition duration
 2600, 	// TT F3 locus
 10, 	// TT percent
 50, 	// TT transition duration
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
 400, 	// KH F1 locus
 67, 	// KH percent
 26, 	// KH transition duration
 1600, 	// KH F2 locus
 67, 	// KH percent
 26, 	// KH transition duration
 2000, 	// KH F3 locus
 67, 	// KH percent
 26, 	// KH transition duration
 300, 	// KK F1 locus
 33, 	// KK percent
 50, 	// KK transition duration
 1800, 	// KK F2 locus
 16, 	// KK percent
 60, 	// KK transition duration
 2100, 	// KK F3 locus
 0, 	// KK percent
 90, 	// KK transition duration
 300, 	// G F1 locus
 55, 	// G percent
 50, 	// G transition duration
 1800, 	// G F2 locus
 16, 	// G percent
 60, 	// G transition duration
 2150, 	// G F3 locus
 0, 	// G percent
 90, 	// G transition duration
 350, 	// S F1 locus
 50, 	// S percent
 50, 	// S transition duration
 1420, 	// S F2 locus
 50, 	// S percent
 50, 	// S transition duration
 2500, 	// S F3 locus
 50, 	// S percent
 50, 	// S transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1440, 	// SS F2 locus
 40, 	// SS percent
 50, 	// SS transition duration
 2530, 	// SS F3 locus
 0, 	// SS percent
 70, 	// SS transition duration
 285, 	// SH F1 locus
 25, 	// SH percent
 45, 	// SH transition duration
 1759, 	// SH F2 locus
 30, 	// SH percent
 40, 	// SH transition duration
 2640, 	// SH F3 locus
 25, 	// SH percent
 40, 	// SH transition duration
 -1, 	// Y F1 locus
 -1, 	// Y percent
 -1, 	// Y transition duration
 -1, 	// Y F2 locus
 -1, 	// Y percent
 -1, 	// Y transition duration
 -1, 	// Y F3 locus
 -1, 	// Y percent
 -1, 	// Y transition duration
 300, 	// DF F1 locus
 50, 	// DF percent
 30, 	// DF transition duration
 1340, 	// DF F2 locus
 40, 	// DF percent
 35, 	// DF transition duration
 2090, 	// DF F3 locus
 61, 	// DF percent
 50, 	// DF transition duration
 245, 	// JH F1 locus
 40, 	// JH percent
 50, 	// JH transition duration
 1680, 	// JH F2 locus
 40, 	// JH percent
 50, 	// JH transition duration
 2450, 	// JH F3 locus
 40, 	// JH percent
 50, 	// JH transition duration
 245, 	// CH F1 locus
 32, 	// CH percent
 55, 	// CH transition duration
 1680, 	// CH F2 locus
 5, 	// CH percent
 120, 	// CH transition duration
 2450, 	// CH F3 locus
 10, 	// CH percent
 70, 	// CH transition duration
 320, 	// CC F1 locus
 54, 	// CC percent
 55, 	// CC transition duration
 1680, 	// CC F2 locus
 10, 	// CC percent
 40, 	// CC transition duration
 2450, 	// CC F3 locus
 10, 	// CC percent
 70, 	// CC transition duration
// Round
 450, 	// M F1 locus
 20, 	// M percent
 30, 	// M transition duration
 970, 	// M F2 locus
 10, 	// M percent
 40, 	// M transition duration
 1550, 	// M F3 locus
 80, 	// M percent
 25, 	// M transition duration
 450, 	// N F1 locus
 20, 	// N percent
 30, 	// N transition duration
 1500, 	// N F2 locus
 25, 	// N percent
 25, 	// N transition duration
 2320, 	// N F3 locus
 50, 	// N percent
 25, 	// N transition duration
 220, 	// NX F1 locus
 25, 	// NX percent
 25, 	// NX transition duration
 1700, 	// NX F2 locus
 25, 	// NX percent
 25, 	// NX transition duration
 1820, 	// NX F3 locus
 25, 	// NX percent
 25, 	// NX transition duration
 320, 	// P F1 locus
 45, 	// P percent
 25, 	// P transition duration
 920, 	// P F2 locus
 46, 	// P percent
 50, 	// P transition duration
 1900, 	// P F3 locus
 40, 	// P percent
 50, 	// P transition duration
 320, 	// PH F1 locus
 45, 	// PH percent
 25, 	// PH transition duration
 920, 	// PH F2 locus
 46, 	// PH percent
 50, 	// PH transition duration
 1900, 	// PH F3 locus
 40, 	// PH percent
 50, 	// PH transition duration
 370, 	// PP F1 locus
 45, 	// PP percent
 30, 	// PP transition duration
 988, 	// PP F2 locus
 46, 	// PP percent
 30, 	// PP transition duration
 2300, 	// PP F3 locus
 40, 	// PP percent
 30, 	// PP transition duration
 330, 	// B F1 locus
 45, 	// B percent
 25, 	// B transition duration
 720, 	// B F2 locus
 36, 	// B percent
 50, 	// B transition duration
 1800, 	// B F3 locus
 40, 	// B percent
 40, 	// B transition duration
 320, 	// T F1 locus
 25, 	// T percent
 25, 	// T transition duration
 1700, 	// T F2 locus
 25, 	// T percent
 25, 	// T transition duration
 2300, 	// T F3 locus
 25, 	// T percent
 25, 	// T transition duration
 320, 	// TH F1 locus
 43, 	// TH percent
 40, 	// TH transition duration
 1700, 	// TH F2 locus
 5, 	// TH percent
 95, 	// TH transition duration
 2300, 	// TH F3 locus
 0, 	// TH percent
 95, 	// TH transition duration
 429, 	// TT F1 locus
 43, 	// TT percent
 40, 	// TT transition duration
 1160, 	// TT F2 locus
 5, 	// TT percent
 95, 	// TT transition duration
 2600, 	// TT F3 locus
 0, 	// TT percent
 95, 	// TT transition duration
 250, 	// D F1 locus
 43, 	// D percent
 40, 	// D transition duration
 1200, 	// D F2 locus
 40, 	// D percent
 95, 	// D transition duration
 2601, 	// D F3 locus
 30, 	// D percent
 85, 	// D transition duration
 280, 	// K F1 locus
 33, 	// K percent
 40, 	// K transition duration
 1400, 	// K F2 locus
 60, 	// K percent
 75, 	// K transition duration
 2050, 	// K F3 locus
 15, 	// K percent
 80, 	// K transition duration
 280, 	// KH F1 locus
 33, 	// KH percent
 40, 	// KH transition duration
 1400, 	// KH F2 locus
 60, 	// KH percent
 50, 	// KH transition duration
 2050, 	// KH F3 locus
 15, 	// KH percent
 50, 	// KH transition duration
 290, 	// KK F1 locus
 45, 	// KK percent
 40, 	// KK transition duration
 1600, 	// KK F2 locus
 42, 	// KK percent
 75, 	// KK transition duration
 1920, 	// KK F3 locus
 15, 	// KK percent
 80, 	// KK transition duration
 350, 	// G F1 locus
 45, 	// G percent
 40, 	// G transition duration
 1600, 	// G F2 locus
 42, 	// G percent
 65, 	// G transition duration
 1920, 	// G F3 locus
 15, 	// G percent
 80, 	// G transition duration
 350, 	// S F1 locus
 50, 	// S percent
 50, 	// S transition duration
 1420, 	// S F2 locus
 50, 	// S percent
 50, 	// S transition duration
 2500, 	// S F3 locus
 50, 	// S percent
 50, 	// S transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1320, 	// SS F2 locus
 15, 	// SS percent
 60, 	// SS transition duration
 2460, 	// SS F3 locus
 0, 	// SS percent
 65, 	// SS transition duration
 285, 	// SH F1 locus
 25, 	// SH percent
 45, 	// SH transition duration
 1630, 	// SH F2 locus
 27, 	// SH percent
 90, 	// SH transition duration
 2100, 	// SH F3 locus
 20, 	// SH percent
 110, 	// SH transition duration
 -1, 	// Y F1 locus
 -1, 	// Y percent
 -1, 	// Y transition duration
 -1, 	// Y F2 locus
 -1, 	// Y percent
 -1, 	// Y transition duration
 -1, 	// Y F3 locus
 -1, 	// Y percent
 -1, 	// Y transition duration
 350, 	// DF F1 locus
 40, 	// DF percent
 35, 	// DF transition duration
 1340, 	// DF F2 locus
 40, 	// DF percent
 75, 	// DF transition duration
 2090, 	// DF F3 locus
 42, 	// DF percent
 100, 	// DF transition duration
 245, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1680, 	// JH F2 locus
 10, 	// JH percent
 50, 	// JH transition duration
 1970, 	// JH F3 locus
 10, 	// JH percent
 50, 	// JH transition duration
 245, 	// CH F1 locus
 32, 	// CH percent
 55, 	// CH transition duration
 1680, 	// CH F2 locus
 10, 	// CH percent
 90, 	// CH transition duration
 1970, 	// CH F3 locus
 10, 	// CH percent
 100, 	// CH transition duration
 320, 	// CC F1 locus
 54, 	// CC percent
 56, 	// CC transition duration
 1480, 	// CC F2 locus
 20, 	// CC percent
 60, 	// CC transition duration
 1820, 	// CC F3 locus
 20, 	// CC percent
 60, 	// CC transition duration
// Low
 -1, 	// M F1 locus
 -1, 	// M percent
 -1, 	// M transition duration
 -1, 	// M F2 locus
 -1, 	// M percent
 -1, 	// M transition duration
 -1, 	// M F3 locus
 -1, 	// M percent
 -1, 	// M transition duration
 -1, 	// N F1 locus
 -1, 	// N percent
 -1, 	// N transition duration
 -1, 	// N F2 locus
 -1, 	// N percent
 -1, 	// N transition duration
 -1, 	// N F3 locus
 -1, 	// N percent
 -1, 	// N transition duration
 0, 	// P F1 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// P F2 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// P F3 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// PH F1 locus
 0, 	// PH percent
 0, 	// PH transition duration
 0, 	// PH F2 locus
 0, 	// PH percent
 0, 	// PH transition duration
 0, 	// PH F3 locus
 0, 	// PH percent
 0, 	// PH transition duration
 0, 	// PP F1 locus
 0, 	// PP percent
 0, 	// PP transition duration
 0, 	// PP F2 locus
 0, 	// PP percent
 0, 	// PP transition duration
 0, 	// PP F3 locus
 0, 	// PP percent
 0, 	// PP transition duration
 0, 	// T F1 locus
 0, 	// T percent
 0, 	// T transition duration
 0, 	// T F2 locus
 0, 	// T percent
 0, 	// T transition duration
 0, 	// T F3 locus
 0, 	// T percent
 0, 	// T transition duration
 0, 	// TH F1 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F2 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F3 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TT F1 locus
 0, 	// TT percent
 0, 	// TT transition duration
 0, 	// TT F2 locus
 0, 	// TT percent
 0, 	// TT transition duration
 0, 	// TT F3 locus
 0, 	// TT percent
 0, 	// TT transition duration
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
 0, 	// KH F1 locus
 0, 	// KH percent
 0, 	// KH transition duration
 0, 	// KH F2 locus
 0, 	// KH percent
 0, 	// KH transition duration
 0, 	// KH F3 locus
 0, 	// KH percent
 0, 	// KH transition duration
 0, 	// KK F1 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// KK F2 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// KK F3 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// G F1 locus
 0, 	// G percent
 0, 	// G transition duration
 0, 	// G F2 locus
 0, 	// G percent
 0, 	// G transition duration
 0, 	// G F3 locus
 0, 	// G percent
 0, 	// G transition duration
 0, 	// S F1 locus
 0, 	// S percent
 0, 	// S transition duration
 0, 	// S F2 locus
 0, 	// S percent
 0, 	// S transition duration
 0, 	// S F3 locus
 0, 	// S percent
 0, 	// S transition duration
 0, 	// SS F1 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// SS F2 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// SS F3 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// SH F1 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// SH F2 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// SH F3 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// CH F1 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F2 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F3 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CC F1 locus
 0, 	// CC percent
 0, 	// CC transition duration
 0, 	// CC F2 locus
 0, 	// CC percent
 0, 	// CC transition duration
 0, 	// CC F3 locus
 0, 	// CC percent
 0, 	// CC transition duration
 0};

// Female Locus
const short kr_femloc_def[] = {
 0, 
// Front
 300, 	// M F1 locus
 30, 	// M percent
 30, 	// M transition duration
 1380, 	// M F2 locus
 10, 	// M percent
 35, 	// M transition duration
 2100, 	// M F3 locus
 30, 	// M percent
 20, 	// M transition duration
 450, 	// N F1 locus
 20, 	// N percent
 35, 	// N transition duration
 1350, 	// N F2 locus
 75, 	// N percent
 35, 	// N transition duration
 2600, 	// N F3 locus
 40, 	// N percent
 45, 	// N transition duration
 480, 	// NX F1 locus
 30, 	// NX percent
 40, 	// NX transition duration
 2760, 	// NX F2 locus
 10, 	// NX percent
 70, 	// NX transition duration
 1900, 	// NX F3 locus
 114, 	// NX percent
 60, 	// NX transition duration
 70, 	// P F1 locus
 10, 	// P percent
 30, 	// P transition duration
 1570, 	// P F2 locus
 47, 	// P percent
 25, 	// P transition duration
 2700, 	// P F3 locus
 22, 	// P percent
 25, 	// P transition duration
 370, 	// PH F1 locus
 10, 	// PH percent
 30, 	// PH transition duration
 1570, 	// PH F2 locus
 47, 	// PH percent
 25, 	// PH transition duration
 2700, 	// PH F3 locus
 22, 	// PH percent
 25, 	// PH transition duration
 290, 	// PP F1 locus
 30, 	// PP percent
 30, 	// PP transition duration
 1800, 	// PP F2 locus
 17, 	// PP percent
 25, 	// PP transition duration
 2690, 	// PP F3 locus
 30, 	// PP percent
 35, 	// PP transition duration
 290, 	// B F1 locus
 30, 	// B percent
 30, 	// B transition duration
 1800, 	// B F2 locus
 17, 	// B percent
 25, 	// B transition duration
 2690, 	// B F3 locus
 30, 	// B percent
 35, 	// B transition duration
 470, 	// T F1 locus
 33, 	// T percent
 35, 	// T transition duration
 2160, 	// T F2 locus
 60, 	// T percent
 35, 	// T transition duration
 3159, 	// T F3 locus
 30, 	// T percent
 45, 	// T transition duration
 470, 	// TH F1 locus
 33, 	// TH percent
 35, 	// TH transition duration
 2160, 	// TH F2 locus
 60, 	// TH percent
 35, 	// TH transition duration
 3159, 	// TH F3 locus
 30, 	// TH percent
 45, 	// TH transition duration
 470, 	// TT F1 locus
 33, 	// TT percent
 35, 	// TT transition duration
 2160, 	// TT F2 locus
 60, 	// TT percent
 35, 	// TT transition duration
 3159, 	// TT F3 locus
 30, 	// TT percent
 45, 	// TT transition duration
 270, 	// D F1 locus
 33, 	// D percent
 35, 	// D transition duration
 2150, 	// D F2 locus
 66, 	// D percent
 35, 	// D transition duration
 2800, 	// D F3 locus
 30, 	// D percent
 45, 	// D transition duration
 280, 	// K F1 locus
 33, 	// K percent
 45, 	// K transition duration
 1980, 	// K F2 locus
 20, 	// K percent
 55, 	// K transition duration
 3000, 	// K F3 locus
 117, 	// K percent
 50, 	// K transition duration
 280, 	// KH F1 locus
 33, 	// KH percent
 45, 	// KH transition duration
 1980, 	// KH F2 locus
 20, 	// KH percent
 55, 	// KH transition duration
 3000, 	// KH F3 locus
 117, 	// KH percent
 50, 	// KH transition duration
 280, 	// KK F1 locus
 33, 	// KK percent
 45, 	// KK transition duration
 1980, 	// KK F2 locus
 20, 	// KK percent
 55, 	// KK transition duration
 3000, 	// KK F3 locus
 117, 	// KK percent
 50, 	// KK transition duration
 250, 	// G F1 locus
 33, 	// G percent
 45, 	// G transition duration
 2100, 	// G F2 locus
 20, 	// G percent
 50, 	// G transition duration
 2100, 	// G F3 locus
 50, 	// G percent
 45, 	// G transition duration
 270, 	// S F1 locus
 50, 	// S percent
 40, 	// S transition duration
 960, 	// S F2 locus
 78, 	// S percent
 0, 	// S transition duration
 2980, 	// S F3 locus
 38, 	// S percent
 70, 	// S transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1440, 	// SS F2 locus
 40, 	// SS percent
 50, 	// SS transition duration
 2550, 	// SS F3 locus
 0, 	// SS percent
 70, 	// SS transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1630, 	// SH F2 locus
 30, 	// SH percent
 70, 	// SH transition duration
 2640, 	// SH F3 locus
 51, 	// SH percent
 70, 	// SH transition duration
 370, 	// Y F1 locus
 32, 	// Y percent
 55, 	// Y transition duration
 2000, 	// Y F2 locus
 25, 	// Y percent
 70, 	// Y transition duration
 3300, 	// Y F3 locus
 19, 	// Y percent
 70, 	// Y transition duration
 320, 	// DF F1 locus
 50, 	// DF percent
 30, 	// DF transition duration
 1800, 	// DF F2 locus
 50, 	// DF percent
 30, 	// DF transition duration
 2500, 	// DF F3 locus
 50, 	// DF percent
 30, 	// DF transition duration
 370, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 2000, 	// JH F2 locus
 25, 	// JH percent
 70, 	// JH transition duration
 3300, 	// JH F3 locus
 19, 	// JH percent
 70, 	// JH transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1750, 	// CH F2 locus
 25, 	// CH percent
 70, 	// CH transition duration
 2750, 	// CH F3 locus
 19, 	// CH percent
 70, 	// CH transition duration
 245, 	// CC F1 locus
 80, 	// CC percent
 30, 	// CC transition duration
 1900, 	// CC F2 locus
 47, 	// CC percent
 40, 	// CC transition duration
 2727, 	// CC F3 locus
 40, 	// CC percent
 40, 	// CC transition duration
// Back
 480, 	// M F1 locus
 30, 	// M percent
 35, 	// M transition duration
 1, 	// M F2 locus
 88, 	// M percent
 40, 	// M transition duration
 2100, 	// M F3 locus
 48, 	// M percent
 30, 	// M transition duration
 450, 	// N F1 locus
 230, 	// N percent
 30, 	// N transition duration
 1420, 	// N F2 locus
 25, 	// N percent
 75, 	// N transition duration
 2600, 	// N F3 locus
 0, 	// N percent
 60, 	// N transition duration
 500, 	// NX F1 locus
 30, 	// NX percent
 40, 	// NX transition duration
 1530, 	// NX F2 locus
 10, 	// NX percent
 70, 	// NX transition duration
 2700, 	// NX F3 locus
 20, 	// NX percent
 70, 	// NX transition duration
 260, 	// P F1 locus
 50, 	// P percent
 35, 	// P transition duration
 1240, 	// P F2 locus
 8, 	// P percent
 30, 	// P transition duration
 2200, 	// P F3 locus
 65, 	// P percent
 40, 	// P transition duration
 260, 	// PH F1 locus
 50, 	// PH percent
 35, 	// PH transition duration
 1240, 	// PH F2 locus
 8, 	// PH percent
 30, 	// PH transition duration
 2200, 	// PH F3 locus
 65, 	// PH percent
 40, 	// PH transition duration
 360, 	// PP F1 locus
 50, 	// PP percent
 20, 	// PP transition duration
 1130, 	// PP F2 locus
 50, 	// PP percent
 30, 	// PP transition duration
 2530, 	// PP F3 locus
 48, 	// PP percent
 40, 	// PP transition duration
 360, 	// B F1 locus
 50, 	// B percent
 20, 	// B transition duration
 1130, 	// B F2 locus
 50, 	// B percent
 30, 	// B transition duration
 2530, 	// B F3 locus
 48, 	// B percent
 40, 	// B transition duration
 180, 	// T F1 locus
 56, 	// T percent
 70, 	// T transition duration
 2050, 	// T F2 locus
 0, 	// T percent
 80, 	// T transition duration
 2960, 	// T F3 locus
 0, 	// T percent
 50, 	// T transition duration
 180, 	// TH F1 locus
 56, 	// TH percent
 70, 	// TH transition duration
 2050, 	// TH F2 locus
 0, 	// TH percent
 80, 	// TH transition duration
 2960, 	// TH F3 locus
 0, 	// TH percent
 50, 	// TH transition duration
 180, 	// TT F1 locus
 56, 	// TT percent
 70, 	// TT transition duration
 2050, 	// TT F2 locus
 0, 	// TT percent
 80, 	// TT transition duration
 2960, 	// TT F3 locus
 0, 	// TT percent
 50, 	// TT transition duration
 270, 	// D F1 locus
 33, 	// D percent
 45, 	// D transition duration
 2050, 	// D F2 locus
 40, 	// D percent
 80, 	// D transition duration
 2790, 	// D F3 locus
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
 280, 	// KH F1 locus
 33, 	// KH percent
 50, 	// KH transition duration
 1800, 	// KH F2 locus
 16, 	// KH percent
 50, 	// KH transition duration
 2000, 	// KH F3 locus
 20, 	// KH percent
 90, 	// KH transition duration
 280, 	// KK F1 locus
 33, 	// KK percent
 50, 	// KK transition duration
 1800, 	// KK F2 locus
 16, 	// KK percent
 50, 	// KK transition duration
 2000, 	// KK F3 locus
 20, 	// KK percent
 90, 	// KK transition duration
 250, 	// G F1 locus
 33, 	// G percent
 50, 	// G transition duration
 1800, 	// G F2 locus
 16, 	// G percent
 60, 	// G transition duration
 2100, 	// G F3 locus
 0, 	// G percent
 90, 	// G transition duration
 270, 	// S F1 locus
 50, 	// S percent
 45, 	// S transition duration
 1800, 	// S F2 locus
 0, 	// S percent
 80, 	// S transition duration
 2800, 	// S F3 locus
 0, 	// S percent
 70, 	// S transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1440, 	// SS F2 locus
 40, 	// SS percent
 50, 	// SS transition duration
 2530, 	// SS F3 locus
 0, 	// SS percent
 70, 	// SS transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1600, 	// SH F2 locus
 27, 	// SH percent
 70, 	// SH transition duration
 2270, 	// SH F3 locus
 0, 	// SH percent
 85, 	// SH transition duration
 380, 	// Y F1 locus
 40, 	// Y percent
 55, 	// Y transition duration
 1900, 	// Y F2 locus
 10, 	// Y percent
 70, 	// Y transition duration
 3200, 	// Y F3 locus
 10, 	// Y percent
 70, 	// Y transition duration
 300, 	// DF F1 locus
 50, 	// DF percent
 30, 	// DF transition duration
 1800, 	// DF F2 locus
 50, 	// DF percent
 40, 	// DF transition duration
 1800, 	// DF F3 locus
 50, 	// DF percent
 30, 	// DF transition duration
 380, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1900, 	// JH F2 locus
 5, 	// JH percent
 120, 	// JH transition duration
 3200, 	// JH F3 locus
 10, 	// JH percent
 70, 	// JH transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1680, 	// CH F2 locus
 10, 	// CH percent
 40, 	// CH transition duration
 2450, 	// CH F3 locus
 10, 	// CH percent
 70, 	// CH transition duration
 253, 	// CC F1 locus
 65, 	// CC percent
 30, 	// CC transition duration
 1800, 	// CC F2 locus
 43, 	// CC percent
 40, 	// CC transition duration
 2700, 	// CC F3 locus
 18, 	// CC percent
 65, 	// CC transition duration
// Round
 300, 	// M F1 locus
 20, 	// M percent
 30, 	// M transition duration
 1, 	// M F2 locus
 88, 	// M percent
 40, 	// M transition duration
 1750, 	// M F3 locus
 80, 	// M percent
 30, 	// M transition duration
 450, 	// N F1 locus
 20, 	// N percent
 30, 	// N transition duration
 1500, 	// N F2 locus
 25, 	// N percent
 95, 	// N transition duration
 2320, 	// N F3 locus
 0, 	// N percent
 95, 	// N transition duration
 480, 	// NX F1 locus
 30, 	// NX percent
 40, 	// NX transition duration
 750, 	// NX F2 locus
 120, 	// NX percent
 70, 	// NX transition duration
 2750, 	// NX F3 locus
 33, 	// NX percent
 70, 	// NX transition duration
 260, 	// P F1 locus
 45, 	// P percent
 70, 	// P transition duration
 1240, 	// P F2 locus
 8, 	// P percent
 30, 	// P transition duration
 1900, 	// P F3 locus
 65, 	// P percent
 40, 	// P transition duration
 260, 	// PH F1 locus
 45, 	// PH percent
 70, 	// PH transition duration
 1240, 	// PH F2 locus
 8, 	// PH percent
 30, 	// PH transition duration
 1900, 	// PH F3 locus
 65, 	// PH percent
 40, 	// PH transition duration
 360, 	// PP F1 locus
 50, 	// PP percent
 20, 	// PP transition duration
 1130, 	// PP F2 locus
 50, 	// PP percent
 30, 	// PP transition duration
 2530, 	// PP F3 locus
 48, 	// PP percent
 40, 	// PP transition duration
 360, 	// B F1 locus
 50, 	// B percent
 20, 	// B transition duration
 1130, 	// B F2 locus
 50, 	// B percent
 30, 	// B transition duration
 2530, 	// B F3 locus
 48, 	// B percent
 40, 	// B transition duration
 470, 	// T F1 locus
 33, 	// T percent
 40, 	// T transition duration
 1900, 	// T F2 locus
 0, 	// T percent
 70, 	// T transition duration
 2850, 	// T F3 locus
 0, 	// T percent
 90, 	// T transition duration
 470, 	// TH F1 locus
 33, 	// TH percent
 40, 	// TH transition duration
 1900, 	// TH F2 locus
 0, 	// TH percent
 70, 	// TH transition duration
 2850, 	// TH F3 locus
 0, 	// TH percent
 90, 	// TH transition duration
 470, 	// TT F1 locus
 33, 	// TT percent
 40, 	// TT transition duration
 1900, 	// TT F2 locus
 0, 	// TT percent
 70, 	// TT transition duration
 2850, 	// TT F3 locus
 0, 	// TT percent
 90, 	// TT transition duration
 270, 	// D F1 locus
 33, 	// D percent
 40, 	// D transition duration
 1900, 	// D F2 locus
 40, 	// D percent
 80, 	// D transition duration
 2700, 	// D F3 locus
 30, 	// D percent
 80, 	// D transition duration
 280, 	// K F1 locus
 33, 	// K percent
 40, 	// K transition duration
 1400, 	// K F2 locus
 60, 	// K percent
 75, 	// K transition duration
 2050, 	// K F3 locus
 15, 	// K percent
 80, 	// K transition duration
 280, 	// KH F1 locus
 33, 	// KH percent
 40, 	// KH transition duration
 1400, 	// KH F2 locus
 60, 	// KH percent
 75, 	// KH transition duration
 2050, 	// KH F3 locus
 15, 	// KH percent
 80, 	// KH transition duration
 280, 	// KK F1 locus
 33, 	// KK percent
 40, 	// KK transition duration
 1400, 	// KK F2 locus
 60, 	// KK percent
 75, 	// KK transition duration
 2050, 	// KK F3 locus
 15, 	// KK percent
 80, 	// KK transition duration
 250, 	// G F1 locus
 45, 	// G percent
 40, 	// G transition duration
 1600, 	// G F2 locus
 42, 	// G percent
 65, 	// G transition duration
 1920, 	// G F3 locus
 15, 	// G percent
 80, 	// G transition duration
 270, 	// S F1 locus
 50, 	// S percent
 40, 	// S transition duration
 1900, 	// S F2 locus
 10, 	// S percent
 80, 	// S transition duration
 2880, 	// S F3 locus
 0, 	// S percent
 65, 	// S transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1320, 	// SS F2 locus
 15, 	// SS percent
 60, 	// SS transition duration
 2460, 	// SS F3 locus
 0, 	// SS percent
 65, 	// SS transition duration
 340, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1630, 	// SH F2 locus
 27, 	// SH percent
 90, 	// SH transition duration
 2100, 	// SH F3 locus
 20, 	// SH percent
 110, 	// SH transition duration
 380, 	// Y F1 locus
 32, 	// Y percent
 55, 	// Y transition duration
 2050, 	// Y F2 locus
 10, 	// Y percent
 90, 	// Y transition duration
 3100, 	// Y F3 locus
 10, 	// Y percent
 100, 	// Y transition duration
 300, 	// DF F1 locus
 50, 	// DF percent
 30, 	// DF transition duration
 1800, 	// DF F2 locus
 50, 	// DF percent
 40, 	// DF transition duration
 1800, 	// DF F3 locus
 50, 	// DF percent
 30, 	// DF transition duration
 380, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 2050, 	// JH F2 locus
 10, 	// JH percent
 90, 	// JH transition duration
 3100, 	// JH F3 locus
 10, 	// JH percent
 100, 	// JH transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1580, 	// CH F2 locus
 20, 	// CH percent
 40, 	// CH transition duration
 2350, 	// CH F3 locus
 10, 	// CH percent
 100, 	// CH transition duration
 290, 	// CC F1 locus
 45, 	// CC percent
 50, 	// CC transition duration
 1970, 	// CC F2 locus
 71, 	// CC percent
 30, 	// CC transition duration
 2570, 	// CC F3 locus
 31, 	// CC percent
 80, 	// CC transition duration
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
 0, 	// P F1 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// P F2 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// P F3 locus
 0, 	// P percent
 0, 	// P transition duration
 0, 	// PH F1 locus
 0, 	// PH percent
 0, 	// PH transition duration
 0, 	// PH F2 locus
 0, 	// PH percent
 0, 	// PH transition duration
 0, 	// PH F3 locus
 0, 	// PH percent
 0, 	// PH transition duration
 -1, 	// PP F1 locus
 -1, 	// PP percent
 -1, 	// PP transition duration
 -1, 	// PP F2 locus
 -1, 	// PP percent
 -1, 	// PP transition duration
 -1, 	// PP F3 locus
 -1, 	// PP percent
 -1, 	// PP transition duration
 -1, 	// T F1 locus
 -1, 	// T percent
 -1, 	// T transition duration
 -1, 	// T F2 locus
 -1, 	// T percent
 -1, 	// T transition duration
 -1, 	// T F3 locus
 -1, 	// T percent
 -1, 	// T transition duration
 -1, 	// TH F1 locus
 -1, 	// TH percent
 -1, 	// TH transition duration
 -1, 	// TH F2 locus
 -1, 	// TH percent
 -1, 	// TH transition duration
 -1, 	// TH F3 locus
 -1, 	// TH percent
 -1, 	// TH transition duration
 -1, 	// TT F1 locus
 -1, 	// TT percent
 -1, 	// TT transition duration
 -1, 	// TT F2 locus
 -1, 	// TT percent
 -1, 	// TT transition duration
 -1, 	// TT F3 locus
 -1, 	// TT percent
 -1, 	// TT transition duration
 -1, 	// D F1 locus
 -1, 	// D percent
 -1, 	// D transition duration
 -1, 	// D F2 locus
 -1, 	// D percent
 -1, 	// D transition duration
 -1, 	// D F3 locus
 -1, 	// D percent
 -1, 	// D transition duration
 0, 	// K F1 locus
 0, 	// K percent
 0, 	// K transition duration
 0, 	// K F2 locus
 0, 	// K percent
 0, 	// K transition duration
 0, 	// K F3 locus
 0, 	// K percent
 0, 	// K transition duration
 0, 	// KH F1 locus
 0, 	// KH percent
 0, 	// KH transition duration
 0, 	// KH F2 locus
 0, 	// KH percent
 0, 	// KH transition duration
 0, 	// KH F3 locus
 0, 	// KH percent
 0, 	// KH transition duration
 0, 	// KK F1 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// KK F2 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// KK F3 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// G F1 locus
 0, 	// G percent
 0, 	// G transition duration
 0, 	// G F2 locus
 0, 	// G percent
 0, 	// G transition duration
 0, 	// G F3 locus
 0, 	// G percent
 0, 	// G transition duration
 -1, 	// S F1 locus
 -1, 	// S percent
 -1, 	// S transition duration
 -1, 	// S F2 locus
 -1, 	// S percent
 -1, 	// S transition duration
 -1, 	// S F3 locus
 -1, 	// S percent
 -1, 	// S transition duration
 0, 	// SS F1 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// SS F2 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// SS F3 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// SH F1 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// SH F2 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// SH F3 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// CH F1 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F2 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F3 locus
 0, 	// CH percent
 0, 	// CH transition duration
 253, 	// CC F1 locus
 50, 	// CC percent
 30, 	// CC transition duration
 1900, 	// CC F2 locus
 80, 	// CC percent
 30, 	// CC transition duration
 2557, 	// CC F3 locus
 27, 	// CC percent
 40, 	// CC transition duration
 0};

const struct rom_data_s kr_rom_data_def = {
kr_inhdr_def,
kr_mindur_def,
kr_burdr_def,
kr_begtyp_def,
kr_endtyp_def,
kr_place_def,
kr_featb_def,
kr_maltar_def,
kr_femtar_def,
kr_maldip_def,
kr_femdip_def,
kr_ptram_def,
kr_plocu_def,
kr_maleloc_def,
kr_femloc_def
};


