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

#define SP_PH_PHONEME_COUNT 39
#define SP_PH_PHONEME_NAMES " _ A E I O U WX YX RR L LL M N NH F S J TH BH DH GH YH P B T D K G CH Y R Q Z W NX V IX MX PH "

// Inherent Duration (milliseconds)
const short sp_inhdr_def[] = {
 300, 	// _
 120, 	// A
 120, 	// E
 125, 	// I
 120, 	// O
 120, 	// U
 75, 	// WX
 50, 	// YX
 110, 	// RR
 100, 	// L
 100, 	// LL
 100, 	// M
 95, 	// N
 110, 	// NH
 100, 	// F
 125, 	// S
 110, 	// J
 100, 	// TH
 50, 	// BH
 50, 	// DH
 55, 	// GH
 100, 	// YH
 75, 	// P
 75, 	// B
 100, 	// T
 60, 	// D
 110, 	// K
 60, 	// G
 160, 	// CH
 100, 	// Y
 80, 	// R
 20, 	// Q
 75, 	// Z
 65, 	// W
 90, 	// NX
 75, 	// V
 40, 	// IX
 90, 	// MX
 120 }; 	//PH

// Minimum Duration (milliseconds)
const short sp_mindur_def[] = {
 300, 	// _
 60, 	// A
 60, 	// E
 60, 	// I
 60, 	// O
 60, 	// U
 20, 	// WX
 30, 	// YX
 90, 	// RR
 60, 	// L
 50, 	// LL
 50, 	// M
 50, 	// N
 60, 	// NH
 60, 	// F
 65, 	// S
 60, 	// J
 67, 	// TH
 30, 	// BH
 35, 	// DH
 30, 	// GH
 75, 	// YH
 45, 	// P
 30, 	// B
 80, 	// T
 35, 	// D
 70, 	// K
 35, 	// G
 100, 	// CH
 50, 	// Y
 60, 	// R
 5, 	// Q
 60, 	// Z
 30, 	// W
 60, 	// NX
 30, 	// V
 40, 	// IX
 60, 	// MX
 60 };	//PH

// Burst Duration (milliseconds)
const short sp_burdr_def[] = {
 0, 	//_
 0, 	//A
 0, 	//E
 0, 	//I
 0, 	//O
 0, 	//U
 0, 	//WX
 0, 	//YX
 0, 	//RR
 0, 	//L
 0, 	//LL
 0, 	//M
 0, 	//N
 0, 	//NH
 0, 	//F
 0, 	//S
 0, 	//J
 0, 	//TH
 0, 	//BH
 0, 	//DH
 7, 	//GH
 45, 	//YH
 7, 	//P
 7, 	//B
 13, 	//T
 15, 	//D
 7, 	//K
 15, 	//G
 71, 	//CH
 0, 	//Y
 0, 	//R
 0, 	//Q
 0, 	//Z
 0, 	//W
 0, 	//NX
 7, 	//V
 0, 	//IX
 0, 	//MX
 0 };	//PH

// Beginning Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short sp_begtyp_def[] = {
 4, 	// _
 2, 	// A
 1, 	// E
 1, 	// I
 3, 	// O
 3, 	// U
 3, 	// WX
 1, 	// YX
 4, 	// RR
 5, 	// L
 1, 	// LL
 4, 	// M
 4, 	// N
 4, 	// NH
 4, 	// F
 4, 	// S
 4, 	// J
 4, 	// TH
 2, 	// BH
 4, 	// DH
 4, 	// GH
 4, 	// YH
 4, 	// P
 4, 	// B
 4, 	// T
 4, 	// D
 4, 	// K
 4, 	// G
 4, 	// CH
 1, 	// Y
 3, 	// R
 2, 	// Q
 4, 	// Z
 5, 	// W
 4, 	// NX
 4, 	// V
 1, 	// IX
 4, 	// MX
 4 };	// PH

// Ending Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short sp_endtyp_def[] = {
 4, 	// _
 2, 	// A
 1, 	// E
 1, 	// I
 3, 	// O
 3, 	// U
 2, 	// WX
 1, 	// YX
 4, 	// RR
 4, 	// L
 1, 	// LL
 4, 	// M
 4, 	// N
 4, 	// NH
 4, 	// F
 4, 	// S
 4, 	// J
 4, 	// TH
 2, 	// BH
 4, 	// DH
 4, 	// GH
 4, 	// YH
 4, 	// P
 4, 	// B
 4, 	// T
 4, 	// D
 4, 	// K
 4, 	// G
 4, 	// CH
 1, 	// Y
 3, 	// R
 2, 	// Q
 4, 	// Z
 2, 	// W
 4, 	// NX
 4, 	// V
 1, 	// IX
 4, 	// MX
 4 };	// PH

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
const short sp_place_def[] = {
 0x0000, 	// _
 0x0000, 	// A
 0x0000, 	// E
 0x0000, 	// I
 0x0000, 	// O
 0x0000, 	// U
 0x0000, 	// WX
 0x00c0, 	// YX
 0x0008, 	// RR
 0x0000, 	// L
 0x00c0, 	// LL
 0x0001, 	// M
 0x0008, 	// N
 0x0008, 	// NH
 0x0001, 	// F
 0x0008, 	// S
 0x0010, 	// J
 0x0002, 	// TH
 0x0001, 	// BH
 0x0002, 	// DH
 0x0010, 	// GH
 0x0004, 	// YH
 0x0001, 	// P
 0x0001, 	// B
 0x0002, 	// T
 0x0002, 	// D
 0x0010, 	// K
 0x0010, 	// G
 0x0004, 	// CH
 0x00c0, 	// Y
 0x0008, 	// R
 0x0020, 	// Q
 0x0008, 	// Z
 0x0001, 	// W
 0x0010, 	// NX
 0x0001, 	// V
 0x00c0, 	// IX
 0x0001, 	// MX
 0x0001 };	// PH

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
const int sp_featb_def[] = {
 0x00000110, 	// _
 0x0000001f, 	// A
 0x0000001f, 	// E
 0x0000001f, 	// I
 0x0000001f, 	// O
 0x0000001f, 	// U
 0x0000041a, 	// WX
 0x0000071a, 	// YX
 0x0000011a, 	// RR
 0x0000871a, 	// L
 0x0000071a, 	// LL
 0x0000259a, 	// M
 0x0000259a, 	// N
 0x0000259a, 	// NH
 0x00000120, 	// F
 0x00000120, 	// S
 0x00000120, 	// J
 0x00000120, 	// TH
 0x00000132, 	// BH
 0x00000122, 	// DH
 0x00000122, 	// GH
 0x00002922, 	// YH
 0x00002960, 	// P
 0x00002962, 	// B
 0x00002960, 	// T
 0x00002962, 	// D
 0x00002960, 	// K
 0x00002962, 	// G
 0x00002920, 	// CH
 0x0000071a, 	// Y
 0x0000011a, 	// R
 0x00000022, 	// Q
 0x00000122, 	// Z
 0x0000041a, 	// W
 0x0000259a, 	// NX
 0x00002962, 	// V
 0x00000012, 	// IX
 0x00000192, 	// MX
 0x00000120, 	// PH
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
 0, 
 0, 
 0, 
 0, 
0 };

// Male - F1,F2,F3,B1,B2,B3,AV data for each phoneme
//     Negative numbers are offsets into maldip table (multi-part formants)
//     Positive numbers are actual values
const short sp_maltar_def[] = {
// ==== F1 ====
 -1, 	// _
 735, 	// A
 454, 	// E
 270, 	// I
 463, 	// O
 300, 	// U
 320, 	// WX
 285, 	// YX
 550, 	// RR
 377, 	// L
 280, 	// LL
 300, 	// M
 180, 	// N
 180, 	// NH
 340, 	// F
 280, 	// S
 500, 	// J
 360, 	// TH
 280, 	// BH
 371, 	// DH
 405, 	// GH
 280, 	// YH
 350, 	// P
 280, 	// B
 386, 	// T
 360, 	// D
 600, 	// K
 280, 	// G
 -2, 	// CH
 280, 	// Y
 480, 	// R
 -1, 	// Q
 310, 	// Z
 295, 	// W
 280, 	// NX
 280, 	// V
 500, 	// IX
 400, 	// MX
 300, 	// PH
// ==== F2 ====
 -1, 	// _
 1160, 	// A
 1801, 	// E
 2290, 	// I
 874, 	// O
 870, 	// U
 700, 	// WX
 2200, 	// YX
 1650, 	// RR
 1300, 	// L
 2500, 	// LL
 1200, 	// M
 1461, 	// N
 1461, 	// NH
 1100, 	// F
 1700, 	// S
 1100, 	// J
 1500, 	// TH
 815, 	// BH
 1368, 	// DH
 1400, 	// GH
 1730, 	// YH
 1000, 	// P
 900, 	// B
 1523, 	// T
 1600, 	// D
 1800, 	// K
 1790, 	// G
 -8, 	// CH
 2400, 	// Y
 1500, 	// R
 -1, 	// Q
 1420, 	// Z
 610, 	// W
 1800, 	// NX
 900, 	// V
 2250, 	// IX
 1400, 	// MX
 1500, 	// PH
// ==== F3 ====
 -1, 	// _
 2122, 	// A
 2463, 	// E
 3010, 	// I
 2347, 	// O
 2240, 	// U
 2314, 	// WX
 2550, 	// YX
 2650, 	// RR
 2800, 	// L
 2900, 	// LL
 2100, 	// M
 2498, 	// N
 2498, 	// NH
 2080, 	// F
 2650, 	// S
 2256, 	// J
 2700, 	// TH
 2270, 	// BH
 2305, 	// DH
 2350, 	// GH
 2700, 	// YH
 2100, 	// P
 1800, 	// B
 2488, 	// T
 2600, 	// D
 2280, 	// K
 2520, 	// G
 -14, 	// CH
 2900, 	// Y
 2500, 	// R
 -1, 	// Q
 2600, 	// Z
 2250, 	// W
 2600, 	// NX
 1800, 	// V
 2850, 	// IX
 2500, 	// MX
 2500, 	// PH
// ==== B1 ====
 250, 	// _
 140, 	// A
 95, 	// E
 170, 	// I
 110, 	// O
 90, 	// U
 50, 	// WX
 100, 	// YX
 200, 	// RR
 120, 	// L
 60, 	// LL
 130, 	// M
 140, 	// N
 140, 	// NH
 300, 	// F
 300, 	// S
 180, 	// J
 200, 	// TH
 90, 	// BH
 60, 	// DH
 140, 	// GH
 70, 	// YH
 160, 	// P
 110, 	// B
 300, 	// T
 90, 	// D
 200, 	// K
 90, 	// G
 200, 	// CH
 80, 	// Y
 200, 	// R
 -1, 	// Q
 140, 	// Z
 50, 	// W
 90, 	// NX
 140, 	// V
 120, 	// IX
 90, 	// MX
 300, 	// PH
// ==== B2 ====
 250, 	// _
 220, 	// A
 120, 	// E
 120, 	// I
 110, 	// O
 110, 	// U
 80, 	// WX
 160, 	// YX
 125, 	// RR
 150, 	// L
 170, 	// LL
 350, 	// M
 350, 	// N
 350, 	// NH
 150, 	// F
 150, 	// S
 100, 	// J
 90, 	// TH
 160, 	// BH
 130, 	// DH
 120, 	// GH
 170, 	// YH
 150, 	// P
 110, 	// B
 150, 	// T
 80, 	// D
 160, 	// K
 120, 	// G
 280, 	// CH
 120, 	// Y
 125, 	// R
 -1, 	// Q
 100, 	// Z
 80, 	// W
 250, 	// NX
 120, 	// V
 170, 	// IX
 250, 	// MX
 150, 	// PH
// ==== B3 ====
 250, 	// _
 170, 	// A
 120, 	// E
 220, 	// I
 170, 	// O
 130, 	// U
 80, 	// WX
 300, 	// YX
 130, 	// RR
 110, 	// L
 250, 	// LL
 250, 	// M
 350, 	// N
 350, 	// NH
 150, 	// F
 150, 	// S
 500, 	// J
 150, 	// TH
 120, 	// BH
 240, 	// DH
 180, 	// GH
 250, 	// YH
 180, 	// P
 130, 	// B
 250, 	// T
 240, 	// D
 280, 	// K
 180, 	// G
 350, 	// CH
 200, 	// Y
 130, 	// R
 -1, 	// Q
 300, 	// Z
 80, 	// W
 150, 	// NX
 120, 	// V
 240, 	// IX
 150, 	// MX
 150, 	// PH
// ==== AV ====
 0, 	// _
 62, 	// A
 66, 	// E
 66, 	// I
 65, 	// O
 66, 	// U
 66, 	// WX
 53, 	// YX
 64, 	// RR
 64, 	// L
 64, 	// LL
 60, 	// M
 64, 	// N
 64, 	// NH
 0, 	// F
 0, 	// S
 0, 	// J
 0, 	// TH
 58, 	// BH
 53, 	// DH
 58, 	// GH
 0, 	// YH
 0, 	// P
 0, 	// B
 0, 	// T
 0, 	// D
 0, 	// K
 0, 	// G
 0, 	// CH
 64, 	// Y
 64, 	// R
 54, 	// Q
 48, 	// Z
 64, 	// W
 60, 	// NX
 64, 	// V
 64, 	// IX
 64, 	// MX
 0 };	// PH

// Female - F1,F2,F3,B1,B2,B3,AV data for each phoneme
//     Negative numbers are offsets into femdip table (multi-part formants)
//     Positive numbers are actual values
const short sp_femtar_def[] = {
// ==== F1 ====
 -1, 	// _
 908, 	// A
 632, 	// E
 320, 	// I
 565, 	// O
 310, 	// U
 295, 	// WX
 320, 	// YX
 550, 	// RR
 400, 	// L
 350, 	// LL
 300, 	// M
 180, 	// N
 207, 	// NH
 320, 	// F
 360, 	// S
 500, 	// J
 360, 	// TH
 280, 	// BH
 338, 	// DH
 230, 	// GH
 280, 	// YH
 370, 	// P
 310, 	// B
 350, 	// T
 310, 	// D
 180, 	// K
 180, 	// G
 350, 	// CH
 280, 	// Y
 350, 	// R
 -1, 	// Q
 310, 	// Z
 310, 	// W
 280, 	// NX
 310, 	// V
 500, 	// IX
 400, 	// MX
 300, 	// PH
// ==== F2 ====
 -1, 	// _
 1561, 	// A
 2337, 	// E
 2596, 	// I
 1070, 	// O
 841, 	// U
 610, 	// WX
 2537, 	// YX
 1650, 	// RR
 1400, 	// L
 2200, 	// LL
 1444, 	// M
 1600, 	// N
 1680, 	// NH
 800, 	// F
 2150, 	// S
 1100, 	// J
 1500, 	// TH
 815, 	// BH
 1737, 	// DH
 1400, 	// GH
 1730, 	// YH
 1150, 	// P
 1150, 	// B
 2182, 	// T
 1495, 	// D
 2336, 	// K
 890, 	// G
 2180, 	// CH
 2400, 	// Y
 1450, 	// R
 -1, 	// Q
 1520, 	// Z
 610, 	// W
 2056, 	// NX
 1150, 	// V
 2250, 	// IX
 1400, 	// MX
 1500, 	// PH
// ==== F3 ====
 -1, 	// _
 2703, 	// A
 3048, 	// E
 3210, 	// I
 2841, 	// O
 2575, 	// U
 2250, 	// WX
 2955, 	// YX
 2650, 	// RR
 2910, 	// L
 2500, 	// LL
 2457, 	// M
 2800, 	// N
 3220, 	// NH
 2715, 	// F
 3172, 	// S
 2256, 	// J
 2700, 	// TH
 2270, 	// BH
 2800, 	// DH
 2350, 	// GH
 2700, 	// YH
 2470, 	// P
 2150, 	// B
 2888, 	// T
 2789, 	// D
 2400, 	// K
 2817, 	// G
 3100, 	// CH
 2900, 	// Y
 2550, 	// R
 -1, 	// Q
 2800, 	// Z
 2250, 	// W
 3100, 	// NX
 2150, 	// V
 2850, 	// IX
 2500, 	// MX
 2500, 	// PH
// ==== B1 ====
 250, 	// _
 140, 	// A
 95, 	// E
 110, 	// I
 120, 	// O
 120, 	// U
 50, 	// WX
 110, 	// YX
 200, 	// RR
 120, 	// L
 60, 	// LL
 120, 	// M
 120, 	// N
 105, 	// NH
 300, 	// F
 300, 	// S
 180, 	// J
 200, 	// TH
 90, 	// BH
 130, 	// DH
 140, 	// GH
 70, 	// YH
 300, 	// P
 100, 	// B
 300, 	// T
 60, 	// D
 200, 	// K
 90, 	// G
 200, 	// CH
 80, 	// Y
 200, 	// R
 -1, 	// Q
 140, 	// Z
 50, 	// W
 90, 	// NX
 140, 	// V
 120, 	// IX
 90, 	// MX
 300, 	// PH
// ==== B2 ====
 250, 	// _
 140, 	// A
 120, 	// E
 270, 	// I
 140, 	// O
 120, 	// U
 80, 	// WX
 110, 	// YX
 125, 	// RR
 150, 	// L
 170, 	// LL
 150, 	// M
 350, 	// N
 425, 	// NH
 150, 	// F
 150, 	// S
 100, 	// J
 90, 	// TH
 160, 	// BH
 130, 	// DH
 120, 	// GH
 170, 	// YH
 180, 	// P
 150, 	// B
 150, 	// T
 130, 	// D
 160, 	// K
 120, 	// G
 280, 	// CH
 120, 	// Y
 60, 	// R
 -1, 	// Q
 100, 	// Z
 80, 	// W
 250, 	// NX
 120, 	// V
 170, 	// IX
 250, 	// MX
 150, 	// PH
// ==== B3 ====
 250, 	// _
 120, 	// A
 120, 	// E
 360, 	// I
 150, 	// O
 160, 	// U
 80, 	// WX
 150, 	// YX
 130, 	// RR
 120, 	// L
 250, 	// LL
 150, 	// M
 350, 	// N
 450, 	// NH
 150, 	// F
 150, 	// S
 500, 	// J
 150, 	// TH
 120, 	// BH
 240, 	// DH
 180, 	// GH
 250, 	// YH
 180, 	// P
 130, 	// B
 250, 	// T
 240, 	// D
 280, 	// K
 180, 	// G
 350, 	// CH
 200, 	// Y
 130, 	// R
 -1, 	// Q
 300, 	// Z
 80, 	// W
 350, 	// NX
 120, 	// V
 240, 	// IX
 150, 	// MX
 150, 	// PH
// ==== AV ====
 0, 	// _
 60, 	// A
 66, 	// E
 62, 	// I
 62, 	// O
 63, 	// U
 62, 	// WX
 62, 	// YX
 64, 	// RR
 58, 	// L
 62, 	// LL
 55, 	// M
 55, 	// N
 64, 	// NH
 0, 	// F
 0, 	// S
 0, 	// J
 0, 	// TH
 58, 	// BH
 50, 	// DH
 58, 	// GH
 0, 	// YH
 0, 	// P
 0, 	// B
 0, 	// T
 0, 	// D
 0, 	// K
 0, 	// G
 0, 	// CH
 64, 	// Y
 60, 	// R
 53, 	// Q
 55, 	// Z
 60, 	// W
 60, 	// NX
 54, 	// V
 60, 	// IX
 58, 	// MX
 0 };	// PH

// Male - F1,F1T,F2,F2T,F3,F3T,B1,B1T,B2,B2T,B3,B3T,AV,AVT data for Multi-part formants
const short sp_maldip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _
 0, 	// _
 350, 	// CH F1
 10, 	// CH F1 duration
 325, 	// CH F1
 70, 	// CH F1 duration
 355, 	// CH F1
 -1, 	// CH F1 duration
 1750, 	// CH F2
 10, 	// CH F2 duration
 1650, 	// CH F2
 70, 	// CH F2 duration
 1650, 	// CH F2
 -1, 	// CH F2 duration
 2700, 	// CH F3
 10, 	// CH F3 duration
 2550, 	// CH F3
 70, 	// CH F3 duration
 2550, 	// CH F3
 -1, 	// CH F3 duration
// ====== Bandwidths and duration ======
// ====== Amplitude of Voicing ======
 0};

// Female diphthongs
const short sp_femdip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _
 0, 	// _
// ====== Bandwidths and duration ======
// ====== Amplitude of Voicing ======
 0};

// Offsets into Amplitude data
const short sp_ptram_def[] = {
 0, 	// _
 0, 	// A
 0, 	// E
 0, 	// I
 0, 	// O
 0, 	// U
 0, 	// WX
 1, 	// YX
 31, 	// RR
 0, 	// L
 61, 	// LL
 0, 	// M
 0, 	// N
 0, 	// NH
 91, 	// F
 121, 	// S
 151, 	// J
 181, 	// TH
 211, 	// BH
 241, 	// DH
 271, 	// GH
 301, 	// YH
 331, 	// P
 361, 	// B
 391, 	// T
 421, 	// D
 451, 	// K
 481, 	// G
 511, 	// CH
 0, 	// Y
 541, 	// R
 0, 	// Q
 571, 	// Z
 0, 	// W
 0, 	// NX
 601, 	// V
 0, 	// IX
 0, 	// MX
 631 };	// PH

// Offsets into Locus data
const short sp_plocu_def[] = {
// ==== Front ====
 0, 	// _
 0, 	// A
 0, 	// E
 0, 	// I
 0, 	// O
 0, 	// U
 0, 	// WX
 0, 	// YX
 1, 	// RR
 0, 	// L
 0, 	// LL
 10, 	// M
 19, 	// N
 28, 	// NH
 37, 	// F
 46, 	// S
 55, 	// J
 64, 	// TH
 73, 	// BH
 82, 	// DH
 91, 	// GH
 100, 	// YH
 109, 	// P
 118, 	// B
 127, 	// T
 136, 	// D
 145, 	// K
 154, 	// G
 163, 	// CH
 0, 	// Y
 172, 	// R
 0, 	// Q
 181, 	// Z
 0, 	// W
 190, 	// NX
 199, 	// V
 0, 	// IX
 0, 	// MX
 0, 	// PH
// ==== Back ====
 0, 	// _
 0, 	// A
 0, 	// E
 0, 	// I
 0, 	// O
 0, 	// U
 0, 	// WX
 0, 	// YX
 208, 	// RR
 0, 	// L
 0, 	// LL
 217, 	// M
 226, 	// N
 235, 	// NH
 244, 	// F
 253, 	// S
 262, 	// J
 271, 	// TH
 280, 	// BH
 289, 	// DH
 298, 	// GH
 307, 	// YH
 316, 	// P
 325, 	// B
 334, 	// T
 343, 	// D
 352, 	// K
 361, 	// G
 370, 	// CH
 0, 	// Y
 379, 	// R
 0, 	// Q
 388, 	// Z
 0, 	// W
 397, 	// NX
 406, 	// V
 0, 	// IX
 0, 	// MX
 0, 	// PH
// ==== Round ====
 0, 	// _
 0, 	// A
 0, 	// E
 0, 	// I
 0, 	// O
 0, 	// U
 0, 	// WX
 0, 	// YX
 415, 	// RR
 0, 	// L
 0, 	// LL
 424, 	// M
 433, 	// N
 442, 	// NH
 451, 	// F
 460, 	// S
 469, 	// J
 478, 	// TH
 487, 	// BH
 496, 	// DH
 505, 	// GH
 514, 	// YH
 523, 	// P
 532, 	// B
 541, 	// T
 550, 	// D
 559, 	// K
 568, 	// G
 577, 	// CH
 0, 	// Y
 586, 	// R
 0, 	// Q
 595, 	// Z
 0, 	// W
 604, 	// NX
 613, 	// V
 0, 	// IX
 0, 	// MX
 0, 	// PH
// ==== Low ====
 0, 	// _
 0, 	// A
 0, 	// E
 0, 	// I
 0, 	// O
 0, 	// U
 0, 	// WX
 0, 	// YX
 0, 	// RR
 0, 	// L
 0, 	// LL
 622, 	// M
 631, 	// N
 640, 	// NH
 649, 	// F
 658, 	// S
 0, 	// J
 667, 	// TH
 676, 	// BH
 685, 	// DH
 694, 	// GH
 703, 	// YH
 712, 	// P
 721, 	// B
 730, 	// T
 739, 	// D
 748, 	// K
 757, 	// G
 766, 	// CH
 775, 	// Y
 0, 	// R
 0, 	// Q
 784, 	// Z
 0, 	// W
 793, 	// NX
 0, 	// V
 0, 	// IX
 0, 	// MX
 0 };	// PH

// Male Locus data
const short sp_maleloc_def[] = {
 0, 
// Front
 400, 	// RR F1 locus
 50, 	// RR percent
 60, 	// RR transition duration
 1400, 	// RR F2 locus
 20, 	// RR percent
 60, 	// RR transition duration
 2700, 	// RR F3 locus
 50, 	// RR percent
 60, 	// RR transition duration
 350, 	// M F1 locus
 30, 	// M percent
 30, 	// M transition duration
 1200, 	// M F2 locus
 10, 	// M percent
 35, 	// M transition duration
 2500, 	// M F3 locus
 30, 	// M percent
 40, 	// M transition duration
 280, 	// N F1 locus
 20, 	// N percent
 35, 	// N transition duration
 1420, 	// N F2 locus
 80, 	// N percent
 55, 	// N transition duration
 2600, 	// N F3 locus
 40, 	// N percent
 45, 	// N transition duration
 280, 	// NH F1 locus
 20, 	// NH percent
 35, 	// NH transition duration
 2200, 	// NH F2 locus
 80, 	// NH percent
 55, 	// NH transition duration
 2800, 	// NH F3 locus
 40, 	// NH percent
 45, 	// NH transition duration
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
 300, 	// J F1 locus
 72, 	// J percent
 20, 	// J transition duration
 1869, 	// J F2 locus
 10, 	// J percent
 40, 	// J transition duration
 2569, 	// J F3 locus
 63, 	// J percent
 50, 	// J transition duration
 360, 	// TH F1 locus
 10, 	// TH percent
 45, 	// TH transition duration
 1500, 	// TH F2 locus
 20, 	// TH percent
 35, 	// TH transition duration
 2700, 	// TH F3 locus
 0, 	// TH percent
 50, 	// TH transition duration
 250, 	// BH F1 locus
 30, 	// BH percent
 30, 	// BH transition duration
 815, 	// BH F2 locus
 50, 	// BH percent
 35, 	// BH transition duration
 2170, 	// BH F3 locus
 50, 	// BH percent
 30, 	// BH transition duration
 400, 	// DH F1 locus
 10, 	// DH percent
 45, 	// DH transition duration
 1500, 	// DH F2 locus
 20, 	// DH percent
 35, 	// DH transition duration
 2700, 	// DH F3 locus
 0, 	// DH percent
 50, 	// DH transition duration
 240, 	// GH F1 locus
 44, 	// GH percent
 18, 	// GH transition duration
 2300, 	// GH F2 locus
 10, 	// GH percent
 80, 	// GH transition duration
 2340, 	// GH F3 locus
 10, 	// GH percent
 50, 	// GH transition duration
 240, 	// YH F1 locus
 32, 	// YH percent
 55, 	// YH transition duration
 1750, 	// YH F2 locus
 25, 	// YH percent
 70, 	// YH transition duration
 2750, 	// YH F3 locus
 19, 	// YH percent
 70, 	// YH transition duration
 350, 	// P F1 locus
 55, 	// P percent
 20, 	// P transition duration
 950, 	// P F2 locus
 35, 	// P percent
 30, 	// P transition duration
 2200, 	// P F3 locus
 25, 	// P percent
 45, 	// P transition duration
 330, 	// B F1 locus
 55, 	// B percent
 20, 	// B transition duration
 1300, 	// B F2 locus
 40, 	// B percent
 30, 	// B transition duration
 2100, 	// B F3 locus
 25, 	// B percent
 45, 	// B transition duration
 350, 	// T F1 locus
 43, 	// T percent
 40, 	// T transition duration
 1700, 	// T F2 locus
 50, 	// T percent
 95, 	// T transition duration
 2700, 	// T F3 locus
 50, 	// T percent
 95, 	// T transition duration
 336, 	// D F1 locus
 80, 	// D percent
 50, 	// D transition duration
 1800, 	// D F2 locus
 66, 	// D percent
 35, 	// D transition duration
 2600, 	// D F3 locus
 30, 	// D percent
 45, 	// D transition duration
 270, 	// K F1 locus
 33, 	// K percent
 45, 	// K transition duration
 2400, 	// K F2 locus
 50, 	// K percent
 63, 	// K transition duration
 2700, 	// K F3 locus
 53, 	// K percent
 66, 	// K transition duration
 250, 	// G F1 locus
 33, 	// G percent
 45, 	// G transition duration
 1990, 	// G F2 locus
 20, 	// G percent
 50, 	// G transition duration
 3000, 	// G F3 locus
 113, 	// G percent
 20, 	// G transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1934, 	// CH F2 locus
 88, 	// CH percent
 10, 	// CH transition duration
 2750, 	// CH F3 locus
 88, 	// CH percent
 10, 	// CH transition duration
 -1, 	// R F1 locus
 -1, 	// R percent
 -1, 	// R transition duration
 -1, 	// R F2 locus
 -1, 	// R percent
 -1, 	// R transition duration
 -1, 	// R F3 locus
 -1, 	// R percent
 -1, 	// R transition duration
 320, 	// Z F1 locus
 54, 	// Z percent
 55, 	// Z transition duration
 1750, 	// Z F2 locus
 25, 	// Z percent
 70, 	// Z transition duration
 2776, 	// Z F3 locus
 19, 	// Z percent
 70, 	// Z transition duration
 280, 	// NX F1 locus
 25, 	// NX percent
 40, 	// NX transition duration
 2100, 	// NX F2 locus
 15, 	// NX percent
 60, 	// NX transition duration
 3000, 	// NX F3 locus
 100, 	// NX percent
 60, 	// NX transition duration
 330, 	// V F1 locus
 55, 	// V percent
 20, 	// V transition duration
 900, 	// V F2 locus
 40, 	// V percent
 30, 	// V transition duration
 2100, 	// V F3 locus
 25, 	// V percent
 45, 	// V transition duration
// Back
 400, 	// RR F1 locus
 50, 	// RR percent
 60, 	// RR transition duration
 1400, 	// RR F2 locus
 20, 	// RR percent
 60, 	// RR transition duration
 2700, 	// RR F3 locus
 50, 	// RR percent
 60, 	// RR transition duration
 350, 	// M F1 locus
 20, 	// M percent
 30, 	// M transition duration
 1200, 	// M F2 locus
 70, 	// M percent
 40, 	// M transition duration
 2500, 	// M F3 locus
 80, 	// M percent
 25, 	// M transition duration
 450, 	// N F1 locus
 22, 	// N percent
 30, 	// N transition duration
 2200, 	// N F2 locus
 65, 	// N percent
 75, 	// N transition duration
 2600, 	// N F3 locus
 30, 	// N percent
 60, 	// N transition duration
 450, 	// NH F1 locus
 22, 	// NH percent
 30, 	// NH transition duration
 2200, 	// NH F2 locus
 20, 	// NH percent
 120, 	// NH transition duration
 2800, 	// NH F3 locus
 40, 	// NH percent
 120, 	// NH transition duration
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
 500, 	// J F1 locus
 50, 	// J percent
 20, 	// J transition duration
 1300, 	// J F2 locus
 99, 	// J percent
 80, 	// J transition duration
 2570, 	// J F3 locus
 30, 	// J percent
 50, 	// J transition duration
 360, 	// TH F1 locus
 10, 	// TH percent
 50, 	// TH transition duration
 1300, 	// TH F2 locus
 12, 	// TH percent
 55, 	// TH transition duration
 2700, 	// TH F3 locus
 11, 	// TH percent
 55, 	// TH transition duration
 250, 	// BH F1 locus
 30, 	// BH percent
 30, 	// BH transition duration
 815, 	// BH F2 locus
 50, 	// BH percent
 50, 	// BH transition duration
 2270, 	// BH F3 locus
 50, 	// BH percent
 50, 	// BH transition duration
 350, 	// DH F1 locus
 10, 	// DH percent
 50, 	// DH transition duration
 1400, 	// DH F2 locus
 12, 	// DH percent
 55, 	// DH transition duration
 2720, 	// DH F3 locus
 11, 	// DH percent
 55, 	// DH transition duration
 480, 	// GH F1 locus
 17, 	// GH percent
 78, 	// GH transition duration
 1660, 	// GH F2 locus
 20, 	// GH percent
 64, 	// GH transition duration
 2100, 	// GH F3 locus
 21, 	// GH percent
 62, 	// GH transition duration
 245, 	// YH F1 locus
 32, 	// YH percent
 55, 	// YH transition duration
 1680, 	// YH F2 locus
 5, 	// YH percent
 120, 	// YH transition duration
 2450, 	// YH F3 locus
 10, 	// YH percent
 70, 	// YH transition duration
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
 450, 	// T F1 locus
 30, 	// T percent
 45, 	// T transition duration
 1600, 	// T F2 locus
 40, 	// T percent
 85, 	// T transition duration
 2600, 	// T F3 locus
 10, 	// T percent
 50, 	// T transition duration
 483, 	// D F1 locus
 10, 	// D percent
 40, 	// D transition duration
 1700, 	// D F2 locus
 40, 	// D percent
 75, 	// D transition duration
 2600, 	// D F3 locus
 0, 	// D percent
 50, 	// D transition duration
 646, 	// K F1 locus
 31, 	// K percent
 38, 	// K transition duration
 1639, 	// K F2 locus
 34, 	// K percent
 35, 	// K transition duration
 2192, 	// K F3 locus
 45, 	// K percent
 25, 	// K transition duration
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
 54, 	// CH percent
 55, 	// CH transition duration
 1680, 	// CH F2 locus
 10, 	// CH percent
 70, 	// CH transition duration
 2450, 	// CH F3 locus
 10, 	// CH percent
 70, 	// CH transition duration
 -1, 	// R F1 locus
 -1, 	// R percent
 -1, 	// R transition duration
 -1, 	// R F2 locus
 -1, 	// R percent
 -1, 	// R transition duration
 -1, 	// R F3 locus
 -1, 	// R percent
 -1, 	// R transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1690, 	// Z F2 locus
 15, 	// Z percent
 60, 	// Z transition duration
 2550, 	// Z F3 locus
 10, 	// Z percent
 70, 	// Z transition duration
 362, 	// NX F1 locus
 45, 	// NX percent
 54, 	// NX transition duration
 1116, 	// NX F2 locus
 39, 	// NX percent
 46, 	// NX transition duration
 2311, 	// NX F3 locus
 49, 	// NX percent
 31, 	// NX transition duration
 350, 	// V F1 locus
 45, 	// V percent
 25, 	// V transition duration
 920, 	// V F2 locus
 46, 	// V percent
 30, 	// V transition duration
 1800, 	// V F3 locus
 40, 	// V percent
 45, 	// V transition duration
// Round
 400, 	// RR F1 locus
 50, 	// RR percent
 60, 	// RR transition duration
 1400, 	// RR F2 locus
 20, 	// RR percent
 60, 	// RR transition duration
 2700, 	// RR F3 locus
 50, 	// RR percent
 60, 	// RR transition duration
 350, 	// M F1 locus
 20, 	// M percent
 30, 	// M transition duration
 900, 	// M F2 locus
 10, 	// M percent
 40, 	// M transition duration
 2500, 	// M F3 locus
 80, 	// M percent
 25, 	// M transition duration
 450, 	// N F1 locus
 25, 	// N percent
 30, 	// N transition duration
 2160, 	// N F2 locus
 65, 	// N percent
 80, 	// N transition duration
 2600, 	// N F3 locus
 30, 	// N percent
 80, 	// N transition duration
 450, 	// NH F1 locus
 25, 	// NH percent
 30, 	// NH transition duration
 2160, 	// NH F2 locus
 65, 	// NH percent
 80, 	// NH transition duration
 2800, 	// NH F3 locus
 30, 	// NH percent
 80, 	// NH transition duration
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
 300, 	// J F1 locus
 90, 	// J percent
 20, 	// J transition duration
 1300, 	// J F2 locus
 99, 	// J percent
 80, 	// J transition duration
 2600, 	// J F3 locus
 30, 	// J percent
 40, 	// J transition duration
 360, 	// TH F1 locus
 10, 	// TH percent
 50, 	// TH transition duration
 1300, 	// TH F2 locus
 12, 	// TH percent
 55, 	// TH transition duration
 2700, 	// TH F3 locus
 11, 	// TH percent
 55, 	// TH transition duration
 250, 	// BH F1 locus
 30, 	// BH percent
 30, 	// BH transition duration
 815, 	// BH F2 locus
 50, 	// BH percent
 30, 	// BH transition duration
 2270, 	// BH F3 locus
 50, 	// BH percent
 30, 	// BH transition duration
 400, 	// DH F1 locus
 10, 	// DH percent
 50, 	// DH transition duration
 1300, 	// DH F2 locus
 12, 	// DH percent
 55, 	// DH transition duration
 2720, 	// DH F3 locus
 11, 	// DH percent
 55, 	// DH transition duration
 380, 	// GH F1 locus
 39, 	// GH percent
 35, 	// GH transition duration
 1200, 	// GH F2 locus
 32, 	// GH percent
 30, 	// GH transition duration
 2350, 	// GH F3 locus
 32, 	// GH percent
 41, 	// GH transition duration
 245, 	// YH F1 locus
 32, 	// YH percent
 55, 	// YH transition duration
 1680, 	// YH F2 locus
 10, 	// YH percent
 90, 	// YH transition duration
 1970, 	// YH F3 locus
 10, 	// YH percent
 100, 	// YH transition duration
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
 1000, 	// B F2 locus
 36, 	// B percent
 35, 	// B transition duration
 1900, 	// B F3 locus
 40, 	// B percent
 35, 	// B transition duration
 450, 	// T F1 locus
 30, 	// T percent
 45, 	// T transition duration
 1500, 	// T F2 locus
 66, 	// T percent
 35, 	// T transition duration
 2650, 	// T F3 locus
 43, 	// T percent
 35, 	// T transition duration
 280, 	// D F1 locus
 43, 	// D percent
 45, 	// D transition duration
 1700, 	// D F2 locus
 40, 	// D percent
 95, 	// D transition duration
 2600, 	// D F3 locus
 43, 	// D percent
 85, 	// D transition duration
 320, 	// K F1 locus
 33, 	// K percent
 45, 	// K transition duration
 1200, 	// K F2 locus
 42, 	// K percent
 65, 	// K transition duration
 2150, 	// K F3 locus
 0, 	// K percent
 90, 	// K transition duration
 290, 	// G F1 locus
 45, 	// G percent
 40, 	// G transition duration
 1400, 	// G F2 locus
 50, 	// G percent
 65, 	// G transition duration
 2350, 	// G F3 locus
 10, 	// G percent
 100, 	// G transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1480, 	// CH F2 locus
 20, 	// CH percent
 60, 	// CH transition duration
 1820, 	// CH F3 locus
 20, 	// CH percent
 60, 	// CH transition duration
 -1, 	// R F1 locus
 -1, 	// R percent
 -1, 	// R transition duration
 -1, 	// R F2 locus
 -1, 	// R percent
 -1, 	// R transition duration
 -1, 	// R F3 locus
 -1, 	// R percent
 -1, 	// R transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1198, 	// Z F2 locus
 40, 	// Z percent
 50, 	// Z transition duration
 2541, 	// Z F3 locus
 0, 	// Z percent
 70, 	// Z transition duration
 330, 	// NX F1 locus
 40, 	// NX percent
 12, 	// NX transition duration
 980, 	// NX F2 locus
 50, 	// NX percent
 40, 	// NX transition duration
 2450, 	// NX F3 locus
 16, 	// NX percent
 100, 	// NX transition duration
 320, 	// V F1 locus
 45, 	// V percent
 25, 	// V transition duration
 720, 	// V F2 locus
 36, 	// V percent
 35, 	// V transition duration
 1900, 	// V F3 locus
 40, 	// V percent
 35, 	// V transition duration
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
 0, 	// TH F1 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F2 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F3 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// BH F1 locus
 0, 	// BH percent
 0, 	// BH transition duration
 0, 	// BH F2 locus
 0, 	// BH percent
 0, 	// BH transition duration
 0, 	// BH F3 locus
 0, 	// BH percent
 0, 	// BH transition duration
 0, 	// DH F1 locus
 0, 	// DH percent
 0, 	// DH transition duration
 0, 	// DH F2 locus
 0, 	// DH percent
 0, 	// DH transition duration
 0, 	// DH F3 locus
 0, 	// DH percent
 0, 	// DH transition duration
 0, 	// GH F1 locus
 0, 	// GH percent
 0, 	// GH transition duration
 0, 	// GH F2 locus
 0, 	// GH percent
 0, 	// GH transition duration
 0, 	// GH F3 locus
 0, 	// GH percent
 0, 	// GH transition duration
 0, 	// YH F1 locus
 0, 	// YH percent
 0, 	// YH transition duration
 0, 	// YH F2 locus
 0, 	// YH percent
 0, 	// YH transition duration
 0, 	// YH F3 locus
 0, 	// YH percent
 0, 	// YH transition duration
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
 0, 	// Y F1 locus
 0, 	// Y percent
 0, 	// Y transition duration
 0, 	// Y F2 locus
 0, 	// Y percent
 0, 	// Y transition duration
 0, 	// Y F3 locus
 0, 	// Y percent
 0, 	// Y transition duration
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
 0};

// Female Locus
const short sp_femloc_def[] = {
 0, 
// Front
 400, 	// RR F1 locus
 50, 	// RR percent
 60, 	// RR transition duration
 1400, 	// RR F2 locus
 20, 	// RR percent
 60, 	// RR transition duration
 2700, 	// RR F3 locus
 50, 	// RR percent
 60, 	// RR transition duration
 238, 	// M F1 locus
 10, 	// M percent
 30, 	// M transition duration
 1100, 	// M F2 locus
 90, 	// M percent
 20, 	// M transition duration
 2758, 	// M F3 locus
 50, 	// M percent
 30, 	// M transition duration
 450, 	// N F1 locus
 70, 	// N percent
 35, 	// N transition duration
 2100, 	// N F2 locus
 60, 	// N percent
 35, 	// N transition duration
 3200, 	// N F3 locus
 50, 	// N percent
 45, 	// N transition duration
 280, 	// NH F1 locus
 20, 	// NH percent
 35, 	// NH transition duration
 2200, 	// NH F2 locus
 80, 	// NH percent
 55, 	// NH transition duration
 2800, 	// NH F3 locus
 40, 	// NH percent
 45, 	// NH transition duration
 362, 	// F F1 locus
 10, 	// F percent
 60, 	// F transition duration
 2085, 	// F F2 locus
 10, 	// F percent
 60, 	// F transition duration
 2776, 	// F F3 locus
 10, 	// F percent
 60, 	// F transition duration
 353, 	// S F1 locus
 10, 	// S percent
 60, 	// S transition duration
 1905, 	// S F2 locus
 30, 	// S percent
 60, 	// S transition duration
 2740, 	// S F3 locus
 90, 	// S percent
 60, 	// S transition duration
 300, 	// J F1 locus
 72, 	// J percent
 20, 	// J transition duration
 1869, 	// J F2 locus
 10, 	// J percent
 40, 	// J transition duration
 2569, 	// J F3 locus
 63, 	// J percent
 50, 	// J transition duration
 360, 	// TH F1 locus
 10, 	// TH percent
 45, 	// TH transition duration
 1500, 	// TH F2 locus
 20, 	// TH percent
 35, 	// TH transition duration
 2700, 	// TH F3 locus
 0, 	// TH percent
 50, 	// TH transition duration
 250, 	// BH F1 locus
 30, 	// BH percent
 30, 	// BH transition duration
 815, 	// BH F2 locus
 50, 	// BH percent
 35, 	// BH transition duration
 2170, 	// BH F3 locus
 50, 	// BH percent
 30, 	// BH transition duration
 454, 	// DH F1 locus
 10, 	// DH percent
 35, 	// DH transition duration
 2378, 	// DH F2 locus
 10, 	// DH percent
 42, 	// DH transition duration
 2972, 	// DH F3 locus
 10, 	// DH percent
 60, 	// DH transition duration
 240, 	// GH F1 locus
 10, 	// GH percent
 45, 	// GH transition duration
 1866, 	// GH F2 locus
 20, 	// GH percent
 50, 	// GH transition duration
 2340, 	// GH F3 locus
 10, 	// GH percent
 50, 	// GH transition duration
 240, 	// YH F1 locus
 32, 	// YH percent
 55, 	// YH transition duration
 1750, 	// YH F2 locus
 25, 	// YH percent
 70, 	// YH transition duration
 2750, 	// YH F3 locus
 19, 	// YH percent
 70, 	// YH transition duration
 280, 	// P F1 locus
 50, 	// P percent
 30, 	// P transition duration
 1570, 	// P F2 locus
 47, 	// P percent
 25, 	// P transition duration
 1660, 	// P F3 locus
 73, 	// P percent
 35, 	// P transition duration
 360, 	// B F1 locus
 40, 	// B percent
 20, 	// B transition duration
 1350, 	// B F2 locus
 60, 	// B percent
 25, 	// B transition duration
 2690, 	// B F3 locus
 55, 	// B percent
 35, 	// B transition duration
 447, 	// T F1 locus
 10, 	// T percent
 45, 	// T transition duration
 2375, 	// T F2 locus
 10, 	// T percent
 45, 	// T transition duration
 3065, 	// T F3 locus
 10, 	// T percent
 45, 	// T transition duration
 492, 	// D F1 locus
 10, 	// D percent
 50, 	// D transition duration
 2515, 	// D F2 locus
 10, 	// D percent
 52, 	// D transition duration
 3084, 	// D F3 locus
 10, 	// D percent
 52, 	// D transition duration
 310, 	// K F1 locus
 10, 	// K percent
 45, 	// K transition duration
 2592, 	// K F2 locus
 10, 	// K percent
 50, 	// K transition duration
 3180, 	// K F3 locus
 10, 	// K percent
 60, 	// K transition duration
 220, 	// G F1 locus
 10, 	// G percent
 50, 	// G transition duration
 2700, 	// G F2 locus
 10, 	// G percent
 52, 	// G transition duration
 2835, 	// G F3 locus
 10, 	// G percent
 52, 	// G transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1750, 	// CH F2 locus
 25, 	// CH percent
 70, 	// CH transition duration
 2750, 	// CH F3 locus
 19, 	// CH percent
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
 505, 	// Z F1 locus
 10, 	// Z percent
 45, 	// Z transition duration
 1668, 	// Z F2 locus
 10, 	// Z percent
 45, 	// Z transition duration
 3080, 	// Z F3 locus
 10, 	// Z percent
 45, 	// Z transition duration
 280, 	// NX F1 locus
 20, 	// NX percent
 40, 	// NX transition duration
 2760, 	// NX F2 locus
 10, 	// NX percent
 70, 	// NX transition duration
 2900, 	// NX F3 locus
 114, 	// NX percent
 60, 	// NX transition duration
 360, 	// V F1 locus
 40, 	// V percent
 20, 	// V transition duration
 1350, 	// V F2 locus
 60, 	// V percent
 25, 	// V transition duration
 2690, 	// V F3 locus
 55, 	// V percent
 35, 	// V transition duration
// Back
 400, 	// RR F1 locus
 50, 	// RR percent
 60, 	// RR transition duration
 1400, 	// RR F2 locus
 20, 	// RR percent
 60, 	// RR transition duration
 2700, 	// RR F3 locus
 50, 	// RR percent
 60, 	// RR transition duration
 247, 	// M F1 locus
 10, 	// M percent
 30, 	// M transition duration
 1124, 	// M F2 locus
 90, 	// M percent
 20, 	// M transition duration
 2743, 	// M F3 locus
 50, 	// M percent
 40, 	// M transition duration
 450, 	// N F1 locus
 70, 	// N percent
 30, 	// N transition duration
 2200, 	// N F2 locus
 65, 	// N percent
 75, 	// N transition duration
 3140, 	// N F3 locus
 50, 	// N percent
 60, 	// N transition duration
 450, 	// NH F1 locus
 22, 	// NH percent
 30, 	// NH transition duration
 2200, 	// NH F2 locus
 20, 	// NH percent
 120, 	// NH transition duration
 2800, 	// NH F3 locus
 40, 	// NH percent
 120, 	// NH transition duration
 725, 	// F F1 locus
 10, 	// F percent
 60, 	// F transition duration
 1521, 	// F F2 locus
 10, 	// F percent
 60, 	// F transition duration
 2644, 	// F F3 locus
 10, 	// F percent
 60, 	// F transition duration
 605, 	// S F1 locus
 10, 	// S percent
 60, 	// S transition duration
 1271, 	// S F2 locus
 10, 	// S percent
 60, 	// S transition duration
 2610, 	// S F3 locus
 10, 	// S percent
 60, 	// S transition duration
 500, 	// J F1 locus
 50, 	// J percent
 20, 	// J transition duration
 1300, 	// J F2 locus
 99, 	// J percent
 80, 	// J transition duration
 2570, 	// J F3 locus
 30, 	// J percent
 50, 	// J transition duration
 360, 	// TH F1 locus
 10, 	// TH percent
 50, 	// TH transition duration
 1300, 	// TH F2 locus
 12, 	// TH percent
 55, 	// TH transition duration
 2700, 	// TH F3 locus
 11, 	// TH percent
 55, 	// TH transition duration
 250, 	// BH F1 locus
 30, 	// BH percent
 30, 	// BH transition duration
 815, 	// BH F2 locus
 50, 	// BH percent
 50, 	// BH transition duration
 2270, 	// BH F3 locus
 50, 	// BH percent
 50, 	// BH transition duration
 626, 	// DH F1 locus
 10, 	// DH percent
 40, 	// DH transition duration
 1813, 	// DH F2 locus
 10, 	// DH percent
 35, 	// DH transition duration
 2981, 	// DH F3 locus
 10, 	// DH percent
 50, 	// DH transition duration
 240, 	// GH F1 locus
 10, 	// GH percent
 50, 	// GH transition duration
 1700, 	// GH F2 locus
 30, 	// GH percent
 50, 	// GH transition duration
 2223, 	// GH F3 locus
 10, 	// GH percent
 70, 	// GH transition duration
 245, 	// YH F1 locus
 32, 	// YH percent
 55, 	// YH transition duration
 1680, 	// YH F2 locus
 5, 	// YH percent
 120, 	// YH transition duration
 2450, 	// YH F3 locus
 10, 	// YH percent
 70, 	// YH transition duration
 280, 	// P F1 locus
 50, 	// P percent
 30, 	// P transition duration
 1240, 	// P F2 locus
 8, 	// P percent
 30, 	// P transition duration
 1900, 	// P F3 locus
 65, 	// P percent
 40, 	// P transition duration
 360, 	// B F1 locus
 50, 	// B percent
 20, 	// B transition duration
 1130, 	// B F2 locus
 50, 	// B percent
 30, 	// B transition duration
 2506, 	// B F3 locus
 48, 	// B percent
 40, 	// B transition duration
 767, 	// T F1 locus
 10, 	// T percent
 30, 	// T transition duration
 1652, 	// T F2 locus
 10, 	// T percent
 50, 	// T transition duration
 2891, 	// T F3 locus
 10, 	// T percent
 50, 	// T transition duration
 594, 	// D F1 locus
 10, 	// D percent
 40, 	// D transition duration
 2141, 	// D F2 locus
 10, 	// D percent
 50, 	// D transition duration
 3059, 	// D F3 locus
 10, 	// D percent
 50, 	// D transition duration
 350, 	// K F1 locus
 10, 	// K percent
 50, 	// K transition duration
 2074, 	// K F2 locus
 10, 	// K percent
 50, 	// K transition duration
 2588, 	// K F3 locus
 10, 	// K percent
 50, 	// K transition duration
 220, 	// G F1 locus
 10, 	// G percent
 55, 	// G transition duration
 1900, 	// G F2 locus
 10, 	// G percent
 55, 	// G transition duration
 2200, 	// G F3 locus
 10, 	// G percent
 55, 	// G transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1680, 	// CH F2 locus
 10, 	// CH percent
 70, 	// CH transition duration
 2450, 	// CH F3 locus
 10, 	// CH percent
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
 767, 	// Z F1 locus
 10, 	// Z percent
 30, 	// Z transition duration
 1652, 	// Z F2 locus
 10, 	// Z percent
 50, 	// Z transition duration
 2891, 	// Z F3 locus
 10, 	// Z percent
 50, 	// Z transition duration
 280, 	// NX F1 locus
 20, 	// NX percent
 40, 	// NX transition duration
 1530, 	// NX F2 locus
 20, 	// NX percent
 70, 	// NX transition duration
 2620, 	// NX F3 locus
 20, 	// NX percent
 70, 	// NX transition duration
 360, 	// V F1 locus
 50, 	// V percent
 20, 	// V transition duration
 1130, 	// V F2 locus
 50, 	// V percent
 30, 	// V transition duration
 2506, 	// V F3 locus
 48, 	// V percent
 40, 	// V transition duration
// Round
 400, 	// RR F1 locus
 50, 	// RR percent
 60, 	// RR transition duration
 1400, 	// RR F2 locus
 20, 	// RR percent
 60, 	// RR transition duration
 2700, 	// RR F3 locus
 50, 	// RR percent
 60, 	// RR transition duration
 350, 	// M F1 locus
 20, 	// M percent
 30, 	// M transition duration
 900, 	// M F2 locus
 90, 	// M percent
 20, 	// M transition duration
 2500, 	// M F3 locus
 50, 	// M percent
 25, 	// M transition duration
 450, 	// N F1 locus
 70, 	// N percent
 30, 	// N transition duration
 2160, 	// N F2 locus
 65, 	// N percent
 80, 	// N transition duration
 2800, 	// N F3 locus
 50, 	// N percent
 80, 	// N transition duration
 450, 	// NH F1 locus
 25, 	// NH percent
 30, 	// NH transition duration
 2160, 	// NH F2 locus
 65, 	// NH percent
 80, 	// NH transition duration
 2800, 	// NH F3 locus
 30, 	// NH percent
 80, 	// NH transition duration
 390, 	// F F1 locus
 10, 	// F percent
 60, 	// F transition duration
 1096, 	// F F2 locus
 10, 	// F percent
 60, 	// F transition duration
 2723, 	// F F3 locus
 10, 	// F percent
 60, 	// F transition duration
 402, 	// S F1 locus
 10, 	// S percent
 60, 	// S transition duration
 1161, 	// S F2 locus
 10, 	// S percent
 60, 	// S transition duration
 2484, 	// S F3 locus
 10, 	// S percent
 60, 	// S transition duration
 300, 	// J F1 locus
 90, 	// J percent
 20, 	// J transition duration
 1300, 	// J F2 locus
 99, 	// J percent
 80, 	// J transition duration
 2600, 	// J F3 locus
 30, 	// J percent
 40, 	// J transition duration
 360, 	// TH F1 locus
 10, 	// TH percent
 50, 	// TH transition duration
 1300, 	// TH F2 locus
 12, 	// TH percent
 55, 	// TH transition duration
 2700, 	// TH F3 locus
 11, 	// TH percent
 55, 	// TH transition duration
 250, 	// BH F1 locus
 30, 	// BH percent
 30, 	// BH transition duration
 815, 	// BH F2 locus
 50, 	// BH percent
 30, 	// BH transition duration
 2270, 	// BH F3 locus
 50, 	// BH percent
 30, 	// BH transition duration
 458, 	// DH F1 locus
 10, 	// DH percent
 40, 	// DH transition duration
 1687, 	// DH F2 locus
 10, 	// DH percent
 55, 	// DH transition duration
 2856, 	// DH F3 locus
 10, 	// DH percent
 50, 	// DH transition duration
 240, 	// GH F1 locus
 10, 	// GH percent
 50, 	// GH transition duration
 869, 	// GH F2 locus
 90, 	// GH percent
 50, 	// GH transition duration
 2163, 	// GH F3 locus
 10, 	// GH percent
 70, 	// GH transition duration
 245, 	// YH F1 locus
 32, 	// YH percent
 55, 	// YH transition duration
 1680, 	// YH F2 locus
 10, 	// YH percent
 90, 	// YH transition duration
 1970, 	// YH F3 locus
 10, 	// YH percent
 100, 	// YH transition duration
 280, 	// P F1 locus
 50, 	// P percent
 35, 	// P transition duration
 1110, 	// P F2 locus
 8, 	// P percent
 30, 	// P transition duration
 1900, 	// P F3 locus
 65, 	// P percent
 40, 	// P transition duration
 360, 	// B F1 locus
 50, 	// B percent
 20, 	// B transition duration
 1010, 	// B F2 locus
 50, 	// B percent
 30, 	// B transition duration
 2300, 	// B F3 locus
 48, 	// B percent
 40, 	// B transition duration
 496, 	// T F1 locus
 10, 	// T percent
 50, 	// T transition duration
 1672, 	// T F2 locus
 10, 	// T percent
 50, 	// T transition duration
 2858, 	// T F3 locus
 10, 	// T percent
 50, 	// T transition duration
 500, 	// D F1 locus
 10, 	// D percent
 45, 	// D transition duration
 1615, 	// D F2 locus
 10, 	// D percent
 47, 	// D transition duration
 2818, 	// D F3 locus
 10, 	// D percent
 50, 	// D transition duration
 400, 	// K F1 locus
 10, 	// K percent
 45, 	// K transition duration
 1184, 	// K F2 locus
 10, 	// K percent
 50, 	// K transition duration
 2632, 	// K F3 locus
 10, 	// K percent
 70, 	// K transition duration
 200, 	// G F1 locus
 30, 	// G percent
 50, 	// G transition duration
 1100, 	// G F2 locus
 20, 	// G percent
 30, 	// G transition duration
 2400, 	// G F3 locus
 10, 	// G percent
 40, 	// G transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1680, 	// CH F2 locus
 10, 	// CH percent
 90, 	// CH transition duration
 2350, 	// CH F3 locus
 10, 	// CH percent
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
 496, 	// Z F1 locus
 10, 	// Z percent
 50, 	// Z transition duration
 1672, 	// Z F2 locus
 10, 	// Z percent
 50, 	// Z transition duration
 2858, 	// Z F3 locus
 10, 	// Z percent
 50, 	// Z transition duration
 280, 	// NX F1 locus
 20, 	// NX percent
 40, 	// NX transition duration
 1650, 	// NX F2 locus
 42, 	// NX percent
 70, 	// NX transition duration
 2500, 	// NX F3 locus
 25, 	// NX percent
 70, 	// NX transition duration
 360, 	// V F1 locus
 50, 	// V percent
 20, 	// V transition duration
 1010, 	// V F2 locus
 50, 	// V percent
 30, 	// V transition duration
 2300, 	// V F3 locus
 48, 	// V percent
 40, 	// V transition duration
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
 0, 	// TH F1 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F2 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F3 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// BH F1 locus
 0, 	// BH percent
 0, 	// BH transition duration
 0, 	// BH F2 locus
 0, 	// BH percent
 0, 	// BH transition duration
 0, 	// BH F3 locus
 0, 	// BH percent
 0, 	// BH transition duration
 0, 	// DH F1 locus
 0, 	// DH percent
 0, 	// DH transition duration
 0, 	// DH F2 locus
 0, 	// DH percent
 0, 	// DH transition duration
 0, 	// DH F3 locus
 0, 	// DH percent
 0, 	// DH transition duration
 0, 	// GH F1 locus
 0, 	// GH percent
 0, 	// GH transition duration
 0, 	// GH F2 locus
 0, 	// GH percent
 0, 	// GH transition duration
 0, 	// GH F3 locus
 0, 	// GH percent
 0, 	// GH transition duration
 0, 	// YH F1 locus
 0, 	// YH percent
 0, 	// YH transition duration
 0, 	// YH F2 locus
 0, 	// YH percent
 0, 	// YH transition duration
 0, 	// YH F3 locus
 0, 	// YH percent
 0, 	// YH transition duration
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
 0, 	// Y F1 locus
 0, 	// Y percent
 0, 	// Y transition duration
 0, 	// Y F2 locus
 0, 	// Y percent
 0, 	// Y transition duration
 0, 	// Y F3 locus
 0, 	// Y percent
 0, 	// Y transition duration
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
 0};

const struct rom_data_s sp_rom_data_def = {
sp_inhdr_def,
sp_mindur_def,
sp_burdr_def,
sp_begtyp_def,
sp_endtyp_def,
sp_place_def,
sp_featb_def,
sp_maltar_def,
sp_femtar_def,
sp_maldip_def,
sp_femdip_def,
sp_ptram_def,
sp_plocu_def,
sp_maleloc_def,
sp_femloc_def
};


