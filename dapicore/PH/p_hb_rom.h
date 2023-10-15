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
// Compile Type: Compiled from (0/0)
// Program: PHEdit(5.x)
//

#define HB_PH_PHONEME_COUNT 60
#define HB_PH_PHONEME_NAMES " _  IY EY EH AU AH AO O OY U AX W  Y R  H L M  N  F  V  TH S  Z  SH P  B  T  D  K  G  Q  JH TS CH E1 A1 O1 O2 YY RR HH LL MM NN VV SS ZZ PP BB TT T2 DD C KK GG AL NG CZ KZ TZ "

// Inherent Duration (milliseconds)
const short hb_inhdr_def[] = {
 305, 	// _ 
 170, 	// IY
 200, 	// EY
 100, 	// EH
 170, 	// AU
 160, 	// AH
 240, 	// AO
 100, 	// O
 220, 	// OY
 110, 	// U
 80, 	// AX
 60, 	// W 
 70, 	// Y
 140, 	// R 
 120, 	// H
 75, 	// L
 100, 	// M 
 80, 	// N 
 100, 	// F 
 100, 	// V 
 85, 	// TH
 115, 	// S 
 120, 	// Z 
 120, 	// SH
 90, 	// P 
 80, 	// B 
 85, 	// T 
 80, 	// D 
 90, 	// K 
 70, 	// G 
 100, 	// Q 
 100, 	// JH
 100, 	// TS
 120, 	// CH
 60, 	// E1
 100, 	// A1
 65, 	// O1
 100, 	// O2
 100, 	// YY
 180, 	// RR
 77, 	// HH
 100, 	// LL
 130, 	// MM
 100, 	// NN
 130, 	// VV
 150, 	// SS
 150, 	// ZZ
 120, 	// PP
 100, 	// BB
 110, 	// TT
 110, 	// T2
 105, 	// DD
 90, 	// C
 120, 	// KK
 90, 	// GG
 100, 	// AL
 100, 	// NG
 110, 	// CZ
 110, 	// KZ
 130 }; 	//TZ

// Minimum Duration (milliseconds)
const short hb_mindur_def[] = {
 7, 	// _ 
 80, 	// IY
 110, 	// EY
 60, 	// EH
 140, 	// AU
 70, 	// AH
 100, 	// AO
 60, 	// O
 110, 	// OY
 55, 	// U
 30, 	// AX
 15, 	// W 
 30, 	// Y
 70, 	// R 
 35, 	// H
 50, 	// L
 75, 	// M 
 50, 	// N 
 60, 	// F 
 55, 	// V 
 50, 	// TH
 65, 	// S 
 65, 	// Z 
 60, 	// SH
 70, 	// P 
 50, 	// B 
 50, 	// T 
 40, 	// D 
 60, 	// K 
 30, 	// G 
 10, 	// Q 
 75, 	// JH
 60, 	// TS
 60, 	// CH
 40, 	// E1
 45, 	// A1
 40, 	// O1
 60, 	// O2
 50, 	// YY
 90, 	// RR
 35, 	// HH
 65, 	// LL
 100, 	// MM
 75, 	// NN
 70, 	// VV
 85, 	// SS
 85, 	// ZZ
 90, 	// PP
 65, 	// BB
 65, 	// TT
 65, 	// T2
 55, 	// DD
 60, 	// C
 80, 	// KK
 40, 	// GG
 10, 	// AL
 10, 	// NG
 60, 	// CZ
 60, 	// KZ
 90 };	//TZ

// Burst Duration (milliseconds)
const short hb_burdr_def[] = {
 0, 	//_ 
 0, 	//IY
 0, 	//EY
 0, 	//EH
 0, 	//AU
 0, 	//AH
 0, 	//AO
 0, 	//O
 0, 	//OY
 0, 	//U
 0, 	//AX
 0, 	//W 
 0, 	//Y
 0, 	//R 
 0, 	//H
 0, 	//L
 0, 	//M 
 0, 	//N 
 0, 	//F 
 0, 	//V 
 0, 	//TH
 0, 	//S 
 0, 	//Z 
 0, 	//SH
 7, 	//P 
 7, 	//B 
 16, 	//T 
 16, 	//D 
 26, 	//K 
 26, 	//G 
 0, 	//Q 
 45, 	//JH
 0, 	//TS
 0, 	//CH
 0, 	//E1
 0, 	//A1
 0, 	//O1
 0, 	//O2
 0, 	//YY
 0, 	//RR
 0, 	//HH
 0, 	//LL
 0, 	//MM
 0, 	//NN
 0, 	//VV
 0, 	//SS
 0, 	//ZZ
 11, 	//PP
 11, 	//BB
 20, 	//TT
 20, 	//T2
 20, 	//DD
 26, 	//C
 33, 	//KK
 34, 	//GG
 0, 	//AL
 0, 	//NG
 0, 	//CZ
 0, 	//KZ
 0 };	//TZ

// Beginning Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short hb_begtyp_def[] = {
 4, 	// _ 
 1, 	// IY
 1, 	// EY
 1, 	// EH
 6, 	// AU
 2, 	// AH
 3, 	// AO
 3, 	// O
 3, 	// OY
 2, 	// U
 2, 	// AX
 5, 	// W 
 1, 	// Y
 3, 	// R 
 4, 	// H
 5, 	// L
 4, 	// M 
 4, 	// N 
 4, 	// F 
 4, 	// V 
 4, 	// TH
 4, 	// S 
 4, 	// Z 
 4, 	// SH
 4, 	// P 
 4, 	// B 
 4, 	// T 
 4, 	// D 
 4, 	// K 
 4, 	// G 
 4, 	// Q 
 4, 	// JH
 1, 	// TS
 4, 	// CH
 1, 	// E1
 2, 	// A1
 3, 	// O1
 3, 	// O2
 1, 	// YY
 3, 	// RR
 4, 	// HH
 5, 	// LL
 4, 	// MM
 4, 	// NN
 4, 	// VV
 4, 	// SS
 4, 	// ZZ
 4, 	// PP
 4, 	// BB
 4, 	// TT
 4, 	// T2
 4, 	// DD
 4, 	// C
 4, 	// KK
 4, 	// GG
 4, 	// AL
 4, 	// NG
 4, 	// CZ
 4, 	// KZ
 1 };	// TZ

// Ending Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short hb_endtyp_def[] = {
 4, 	// _ 
 1, 	// IY
 1, 	// EY
 1, 	// EH
 3, 	// AU
 2, 	// AH
 3, 	// AO
 3, 	// O
 1, 	// OY
 2, 	// U
 2, 	// AX
 5, 	// W 
 1, 	// Y
 3, 	// R 
 4, 	// H
 4, 	// L
 4, 	// M 
 4, 	// N 
 4, 	// F 
 4, 	// V 
 4, 	// TH
 4, 	// S 
 4, 	// Z 
 4, 	// SH
 4, 	// P 
 4, 	// B 
 4, 	// T 
 4, 	// D 
 4, 	// K 
 4, 	// G 
 4, 	// Q 
 4, 	// JH
 1, 	// TS
 4, 	// CH
 1, 	// E1
 2, 	// A1
 3, 	// O1
 3, 	// O2
 1, 	// YY
 3, 	// RR
 4, 	// HH
 4, 	// LL
 4, 	// MM
 4, 	// NN
 4, 	// VV
 4, 	// SS
 4, 	// ZZ
 4, 	// PP
 4, 	// BB
 4, 	// TT
 4, 	// T2
 4, 	// DD
 4, 	// C
 4, 	// KK
 4, 	// GG
 4, 	// AL
 4, 	// NG
 4, 	// CZ
 4, 	// KZ
 1 };	// TZ

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
const short hb_place_def[] = {
 0x0000, 	// _ 
 0x0080, 	// IY
 0x0080, 	// EY
 0x0000, 	// EH
 0x0000, 	// AU
 0x0000, 	// AH
 0x0000, 	// AO
 0x0000, 	// O
 0x0000, 	// OY
 0x0000, 	// U
 0x0000, 	// AX
 0x0000, 	// W 
 0x00c4, 	// Y
 0x0008, 	// R 
 0x0000, 	// H
 0x0000, 	// L
 0x0001, 	// M 
 0x0008, 	// N 
 0x0001, 	// F 
 0x0001, 	// V 
 0x0002, 	// TH
 0x0008, 	// S 
 0x0008, 	// Z 
 0x0004, 	// SH
 0x0001, 	// P 
 0x0001, 	// B 
 0x0008, 	// T 
 0x0008, 	// D 
 0x2010, 	// K 
 0x0010, 	// G 
 0x0020, 	// Q 
 0x0004, 	// JH
 0x0004, 	// TS
 0x0000, 	// CH
 0x0000, 	// E1
 0x0000, 	// A1
 0x0000, 	// O1
 0x0000, 	// O2
 0x00c0, 	// YY
 0x0008, 	// RR
 0x0000, 	// HH
 0x0000, 	// LL
 0x0001, 	// MM
 0x0008, 	// NN
 0x0001, 	// VV
 0x0008, 	// SS
 0x0008, 	// ZZ
 0x0001, 	// PP
 0x0001, 	// BB
 0x0008, 	// TT
 0x0008, 	// T2
 0x0008, 	// DD
 0x2010, 	// C
 0x2010, 	// KK
 0x0010, 	// GG
 0x0020, 	// AL
 0x2800, 	// NG
 0x0020, 	// CZ
 0x0020, 	// KZ
 0x0004 };	// TZ

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
const int hb_featb_def[] = {
 0x00000010, 	// _ 
 0x0000001f, 	// IY
 0x0000001f, 	// EY
 0x0000001f, 	// EH
 0x0000001f, 	// AU
 0x0000001f, 	// AH
 0x0000001f, 	// AO
 0x0000001f, 	// O
 0x0000001f, 	// OY
 0x0000001f, 	// U
 0x0000001f, 	// AX
 0x0000071a, 	// W 
 0x0000041a, 	// Y
 0x0000011a, 	// R 
 0x00000110, 	// H
 0x0000071a, 	// L
 0x0000259a, 	// M 
 0x0000259a, 	// N 
 0x00000120, 	// F 
 0x00000122, 	// V 
 0x00000120, 	// TH
 0x00000120, 	// S 
 0x00000122, 	// Z 
 0x00000120, 	// SH
 0x00002960, 	// P 
 0x00002962, 	// B 
 0x00002960, 	// T 
 0x00002962, 	// D 
 0x00002960, 	// K 
 0x00002962, 	// G 
 0x00000000, 	// Q 
 0x00002922, 	// JH
 0x00000120, 	// TS
 0x00000110, 	// CH
 0x0000001f, 	// E1
 0x0000001f, 	// A1
 0x0000001f, 	// O1
 0x0000001f, 	// O2
 0x0000071a, 	// YY
 0x0000011a, 	// RR
 0x00000110, 	// HH
 0x0000071a, 	// LL
 0x0000259a, 	// MM
 0x0000259a, 	// NN
 0x00000122, 	// VV
 0x00000120, 	// SS
 0x00000122, 	// ZZ
 0x00002960, 	// PP
 0x00002962, 	// BB
 0x00002960, 	// TT
 0x00002960, 	// T2
 0x00002962, 	// DD
 0x00002960, 	// C
 0x00002960, 	// KK
 0x00002962, 	// GG
 0x00000022, 	// AL
 0x00000120, 	// NG
 0x00000120, 	// CZ
 0x00000120, 	// KZ
 0x00000120, 	// TZ
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
const short hb_maltar_def[] = {
// ==== F1 ====
 -1, 	// _ 
 -2, 	// IY
 529, 	// EY
 454, 	// EH
 -6, 	// AU
 -12, 	// AH
 -18, 	// AO
 463, 	// O
 -24, 	// OY
 -32, 	// U
 -36, 	// AX
 295, 	// W 
 280, 	// Y
 480, 	// R 
 -1, 	// H
 377, 	// L
 220, 	// M 
 320, 	// N 
 340, 	// F 
 325, 	// V 
 460, 	// TH
 320, 	// S 
 325, 	// Z 
 300, 	// SH
 350, 	// P 
 220, 	// B 
 350, 	// T 
 300, 	// D 
 280, 	// K 
 250, 	// G 
 -1, 	// Q 
 280, 	// JH
 -1, 	// TS
 300, 	// CH
 454, 	// E1
 -42, 	// A1
 463, 	// O1
 463, 	// O2
 280, 	// YY
 480, 	// RR
 -1, 	// HH
 377, 	// LL
 220, 	// MM
 320, 	// NN
 325, 	// VV
 320, 	// SS
 325, 	// ZZ
 350, 	// PP
 220, 	// BB
 350, 	// TT
 350, 	// T2
 300, 	// DD
 280, 	// C
 280, 	// KK
 250, 	// GG
 -1, 	// AL
 815, 	// NG
 300, 	// CZ
 300, 	// KZ
 -1, 	// TZ
// ==== F2 ====
 -1, 	// _ 
 -48, 	// IY
 1973, 	// EY
 1801, 	// EH
 -52, 	// AU
 -58, 	// AH
 -64, 	// AO
 874, 	// O
 -70, 	// OY
 -78, 	// U
 -82, 	// AX
 810, 	// W 
 2315, 	// Y
 1350, 	// R 
 -1, 	// H
 800, 	// L
 1150, 	// M 
 1650, 	// N 
 1100, 	// F 
 1100, 	// V 
 1500, 	// TH
 1520, 	// S 
 1520, 	// Z 
 1600, 	// SH
 1051, 	// P 
 691, 	// B 
 1700, 	// T 
 1650, 	// D 
 1790, 	// K 
 1800, 	// G 
 -1, 	// Q 
 1730, 	// JH
 -1, 	// TS
 1400, 	// CH
 1801, 	// E1
 -88, 	// A1
 874, 	// O1
 874, 	// O2
 2070, 	// YY
 1350, 	// RR
 -1, 	// HH
 800, 	// LL
 1150, 	// MM
 1650, 	// NN
 1100, 	// VV
 1520, 	// SS
 1520, 	// ZZ
 1051, 	// PP
 691, 	// BB
 1700, 	// TT
 1700, 	// T2
 1650, 	// DD
 1790, 	// C
 1790, 	// KK
 1800, 	// GG
 -1, 	// AL
 1300, 	// NG
 1400, 	// CZ
 1400, 	// KZ
 -1, 	// TZ
// ==== F3 ====
 -1, 	// _ 
 -94, 	// IY
 2583, 	// EY
 2463, 	// EH
 -98, 	// AU
 -104, 	// AH
 -110, 	// AO
 2347, 	// O
 -116, 	// OY
 -124, 	// U
 -128, 	// AX
 2177, 	// W 
 2900, 	// Y
 2500, 	// R 
 -1, 	// H
 2800, 	// L
 2260, 	// M 
 2600, 	// N 
 2080, 	// F 
 2144, 	// V 
 2420, 	// TH
 2550, 	// S 
 2500, 	// Z 
 2550, 	// SH
 2150, 	// P 
 2177, 	// B 
 2600, 	// T 
 2600, 	// D 
 2200, 	// K 
 2500, 	// G 
 -1, 	// Q 
 2700, 	// JH
 -1, 	// TS
 2400, 	// CH
 2463, 	// E1
 -134, 	// A1
 2347, 	// O1
 2347, 	// O2
 2570, 	// YY
 2500, 	// RR
 -1, 	// HH
 2800, 	// LL
 2260, 	// MM
 2600, 	// NN
 2144, 	// VV
 2550, 	// SS
 2500, 	// ZZ
 2150, 	// PP
 2177, 	// BB
 2600, 	// TT
 2600, 	// T2
 2600, 	// DD
 2200, 	// C
 2200, 	// KK
 2500, 	// GG
 -1, 	// AL
 2360, 	// NG
 2400, 	// CZ
 2400, 	// KZ
 -1, 	// TZ
// ==== B1 ====
 -1, 	// _ 
 60, 	// IY
 70, 	// EY
 60, 	// EH
 -140, 	// AU
 90, 	// AH
 110, 	// AO
 90, 	// O
 200, 	// OY
 80, 	// U
 90, 	// AX
 90, 	// W 
 50, 	// Y
 70, 	// R 
 300, 	// H
 140, 	// L
 130, 	// M 
 90, 	// N 
 200, 	// F 
 100, 	// V 
 200, 	// TH
 200, 	// S 
 100, 	// Z 
 200, 	// SH
 200, 	// P 
 90, 	// B 
 200, 	// T 
 90, 	// D 
 200, 	// K 
 90, 	// G 
 -1, 	// Q 
 70, 	// JH
 -1, 	// TS
 90, 	// CH
 60, 	// E1
 90, 	// A1
 90, 	// O1
 90, 	// O2
 50, 	// YY
 70, 	// RR
 300, 	// HH
 140, 	// LL
 130, 	// MM
 90, 	// NN
 100, 	// VV
 200, 	// SS
 100, 	// ZZ
 200, 	// PP
 90, 	// BB
 200, 	// TT
 200, 	// T2
 90, 	// DD
 200, 	// C
 200, 	// KK
 90, 	// GG
 -1, 	// AL
 -1, 	// NG
 90, 	// CZ
 90, 	// KZ
 -1, 	// TZ
// ==== B2 ====
 -1, 	// _ 
 100, 	// IY
 100, 	// EY
 150, 	// EH
 75, 	// AU
 70, 	// AH
 90, 	// AO
 70, 	// O
 -146, 	// OY
 83, 	// U
 80, 	// AX
 110, 	// W 
 200, 	// Y
 120, 	// R 
 200, 	// H
 222, 	// L
 120, 	// M 
 120, 	// N 
 120, 	// F 
 120, 	// V 
 90, 	// TH
 180, 	// S 
 140, 	// Z 
 240, 	// SH
 180, 	// P 
 80, 	// B 
 150, 	// T 
 100, 	// D 
 160, 	// K 
 120, 	// G 
 -1, 	// Q 
 170, 	// JH
 -1, 	// TS
 120, 	// CH
 150, 	// E1
 70, 	// A1
 70, 	// O1
 70, 	// O2
 200, 	// YY
 120, 	// RR
 200, 	// HH
 222, 	// LL
 120, 	// MM
 120, 	// NN
 120, 	// VV
 180, 	// SS
 140, 	// ZZ
 180, 	// PP
 80, 	// BB
 150, 	// TT
 150, 	// T2
 100, 	// DD
 160, 	// C
 160, 	// KK
 120, 	// GG
 -1, 	// AL
 -1, 	// NG
 120, 	// CZ
 120, 	// KZ
 -1, 	// TZ
// ==== B3 ====
 -1, 	// _ 
 160, 	// IY
 200, 	// EY
 220, 	// EH
 150, 	// AU
 180, 	// AH
 120, 	// AO
 180, 	// O
 170, 	// OY
 160, 	// U
 180, 	// AX
 150, 	// W 
 300, 	// Y
 150, 	// R 
 220, 	// H
 233, 	// L
 250, 	// M 
 160, 	// N 
 150, 	// F 
 120, 	// V 
 150, 	// TH
 300, 	// S 
 300, 	// Z 
 300, 	// SH
 180, 	// P 
 130, 	// B 
 250, 	// T 
 240, 	// D 
 280, 	// K 
 180, 	// G 
 -1, 	// Q 
 250, 	// JH
 -1, 	// TS
 150, 	// CH
 220, 	// E1
 180, 	// A1
 180, 	// O1
 180, 	// O2
 300, 	// YY
 150, 	// RR
 220, 	// HH
 233, 	// LL
 250, 	// MM
 160, 	// NN
 120, 	// VV
 300, 	// SS
 300, 	// ZZ
 180, 	// PP
 130, 	// BB
 250, 	// TT
 250, 	// T2
 240, 	// DD
 280, 	// C
 280, 	// KK
 180, 	// GG
 -1, 	// AL
 -1, 	// NG
 150, 	// CZ
 150, 	// KZ
 -1, 	// TZ
// ==== AV ====
 0, 	// _ 
 64, 	// IY
 60, 	// EY
 63, 	// EH
 64, 	// AU
 64, 	// AH
 64, 	// AO
 65, 	// O
 64, 	// OY
 65, 	// U
 62, 	// AX
 60, 	// W 
 64, 	// Y
 64, 	// R 
 0, 	// H
 63, 	// L
 58, 	// M 
 60, 	// N 
 0, 	// F 
 40, 	// V 
 0, 	// TH
 0, 	// S 
 40, 	// Z 
 0, 	// SH
 0, 	// P 
 0, 	// B 
 0, 	// T 
 0, 	// D 
 0, 	// K 
 0, 	// G 
 54, 	// Q 
 40, 	// JH
 0, 	// TS
 0, 	// CH
 63, 	// E1
 64, 	// A1
 65, 	// O1
 65, 	// O2
 70, 	// YY
 70, 	// RR
 0, 	// HH
 70, 	// LL
 62, 	// MM
 68, 	// NN
 44, 	// VV
 0, 	// SS
 44, 	// ZZ
 0, 	// PP
 0, 	// BB
 0, 	// TT
 0, 	// T2
 0, 	// DD
 0, 	// C
 0, 	// KK
 0, 	// GG
 54, 	// AL
 54, 	// NG
 0, 	// CZ
 0, 	// KZ
 0 };	// TZ

// Female - F1,F2,F3,B1,B2,B3,AV data for each phoneme
//     Negative numbers are offsets into femdip table (multi-part formants)
//     Positive numbers are actual values
const short hb_femtar_def[] = {
// ==== F1 ====
 -1, 	// _ 
 -2, 	// IY
 529, 	// EY
 454, 	// EH
 -6, 	// AU
 -12, 	// AH
 -18, 	// AO
 463, 	// O
 -24, 	// OY
 -32, 	// U
 -36, 	// AX
 295, 	// W 
 280, 	// Y
 480, 	// R 
 -1, 	// H
 377, 	// L
 220, 	// M 
 320, 	// N 
 340, 	// F 
 325, 	// V 
 460, 	// TH
 320, 	// S 
 325, 	// Z 
 300, 	// SH
 350, 	// P 
 220, 	// B 
 350, 	// T 
 300, 	// D 
 280, 	// K 
 250, 	// G 
 -1, 	// Q 
 280, 	// JH
 -1, 	// TS
 300, 	// CH
 454, 	// E1
 -42, 	// A1
 463, 	// O1
 463, 	// O2
 280, 	// YY
 480, 	// RR
 -1, 	// HH
 377, 	// LL
 220, 	// MM
 320, 	// NN
 325, 	// VV
 320, 	// SS
 325, 	// ZZ
 350, 	// PP
 220, 	// BB
 350, 	// TT
 350, 	// T2
 300, 	// DD
 280, 	// C
 280, 	// KK
 250, 	// GG
 -1, 	// AL
 -1, 	// NG
 300, 	// CZ
 300, 	// KZ
 -1, 	// TZ
// ==== F2 ====
 -1, 	// _ 
 -48, 	// IY
 1973, 	// EY
 1801, 	// EH
 -52, 	// AU
 -58, 	// AH
 -64, 	// AO
 874, 	// O
 -70, 	// OY
 -78, 	// U
 -82, 	// AX
 810, 	// W 
 2315, 	// Y
 1350, 	// R 
 -1, 	// H
 800, 	// L
 1150, 	// M 
 1650, 	// N 
 1100, 	// F 
 1100, 	// V 
 1500, 	// TH
 1520, 	// S 
 1520, 	// Z 
 1600, 	// SH
 1051, 	// P 
 691, 	// B 
 1700, 	// T 
 1650, 	// D 
 1790, 	// K 
 1800, 	// G 
 -1, 	// Q 
 1730, 	// JH
 -1, 	// TS
 1400, 	// CH
 1801, 	// E1
 -88, 	// A1
 874, 	// O1
 874, 	// O2
 2070, 	// YY
 1350, 	// RR
 -1, 	// HH
 800, 	// LL
 1150, 	// MM
 1650, 	// NN
 1100, 	// VV
 1520, 	// SS
 1520, 	// ZZ
 1051, 	// PP
 691, 	// BB
 1700, 	// TT
 1700, 	// T2
 1650, 	// DD
 1790, 	// C
 1790, 	// KK
 1800, 	// GG
 -1, 	// AL
 -1, 	// NG
 1400, 	// CZ
 1400, 	// KZ
 -1, 	// TZ
// ==== F3 ====
 -1, 	// _ 
 -94, 	// IY
 2583, 	// EY
 2463, 	// EH
 -98, 	// AU
 -104, 	// AH
 -110, 	// AO
 2347, 	// O
 -116, 	// OY
 -124, 	// U
 -128, 	// AX
 2177, 	// W 
 2900, 	// Y
 2500, 	// R 
 -1, 	// H
 2800, 	// L
 2260, 	// M 
 2600, 	// N 
 2080, 	// F 
 2144, 	// V 
 2420, 	// TH
 2550, 	// S 
 2500, 	// Z 
 2550, 	// SH
 2150, 	// P 
 2177, 	// B 
 2600, 	// T 
 2600, 	// D 
 2200, 	// K 
 2500, 	// G 
 -1, 	// Q 
 2700, 	// JH
 -1, 	// TS
 2400, 	// CH
 2463, 	// E1
 -134, 	// A1
 2347, 	// O1
 2347, 	// O2
 2570, 	// YY
 2500, 	// RR
 -1, 	// HH
 2800, 	// LL
 2260, 	// MM
 2600, 	// NN
 2144, 	// VV
 2550, 	// SS
 2500, 	// ZZ
 2150, 	// PP
 2177, 	// BB
 2600, 	// TT
 2600, 	// T2
 2600, 	// DD
 2200, 	// C
 2200, 	// KK
 2500, 	// GG
 -1, 	// AL
 -1, 	// NG
 2400, 	// CZ
 2400, 	// KZ
 -1, 	// TZ
// ==== B1 ====
 -1, 	// _ 
 60, 	// IY
 70, 	// EY
 60, 	// EH
 -140, 	// AU
 90, 	// AH
 110, 	// AO
 90, 	// O
 200, 	// OY
 80, 	// U
 90, 	// AX
 90, 	// W 
 50, 	// Y
 70, 	// R 
 300, 	// H
 140, 	// L
 130, 	// M 
 90, 	// N 
 200, 	// F 
 100, 	// V 
 200, 	// TH
 200, 	// S 
 100, 	// Z 
 200, 	// SH
 200, 	// P 
 90, 	// B 
 200, 	// T 
 90, 	// D 
 200, 	// K 
 90, 	// G 
 -1, 	// Q 
 70, 	// JH
 -1, 	// TS
 90, 	// CH
 60, 	// E1
 90, 	// A1
 90, 	// O1
 90, 	// O2
 50, 	// YY
 70, 	// RR
 300, 	// HH
 140, 	// LL
 130, 	// MM
 90, 	// NN
 100, 	// VV
 200, 	// SS
 100, 	// ZZ
 200, 	// PP
 90, 	// BB
 200, 	// TT
 200, 	// T2
 90, 	// DD
 200, 	// C
 200, 	// KK
 90, 	// GG
 -1, 	// AL
 -1, 	// NG
 90, 	// CZ
 90, 	// KZ
 -1, 	// TZ
// ==== B2 ====
 -1, 	// _ 
 100, 	// IY
 100, 	// EY
 150, 	// EH
 75, 	// AU
 70, 	// AH
 90, 	// AO
 70, 	// O
 -146, 	// OY
 83, 	// U
 80, 	// AX
 110, 	// W 
 200, 	// Y
 120, 	// R 
 200, 	// H
 222, 	// L
 120, 	// M 
 120, 	// N 
 120, 	// F 
 120, 	// V 
 90, 	// TH
 180, 	// S 
 140, 	// Z 
 240, 	// SH
 180, 	// P 
 80, 	// B 
 150, 	// T 
 100, 	// D 
 160, 	// K 
 120, 	// G 
 -1, 	// Q 
 170, 	// JH
 -1, 	// TS
 120, 	// CH
 150, 	// E1
 70, 	// A1
 70, 	// O1
 70, 	// O2
 200, 	// YY
 120, 	// RR
 200, 	// HH
 222, 	// LL
 120, 	// MM
 120, 	// NN
 120, 	// VV
 180, 	// SS
 140, 	// ZZ
 180, 	// PP
 80, 	// BB
 150, 	// TT
 150, 	// T2
 100, 	// DD
 160, 	// C
 160, 	// KK
 120, 	// GG
 -1, 	// AL
 -1, 	// NG
 120, 	// CZ
 120, 	// KZ
 -1, 	// TZ
// ==== B3 ====
 -1, 	// _ 
 160, 	// IY
 200, 	// EY
 220, 	// EH
 150, 	// AU
 180, 	// AH
 120, 	// AO
 180, 	// O
 170, 	// OY
 160, 	// U
 180, 	// AX
 150, 	// W 
 300, 	// Y
 150, 	// R 
 220, 	// H
 233, 	// L
 250, 	// M 
 160, 	// N 
 150, 	// F 
 120, 	// V 
 150, 	// TH
 300, 	// S 
 300, 	// Z 
 300, 	// SH
 180, 	// P 
 130, 	// B 
 250, 	// T 
 240, 	// D 
 280, 	// K 
 180, 	// G 
 -1, 	// Q 
 250, 	// JH
 -1, 	// TS
 150, 	// CH
 220, 	// E1
 180, 	// A1
 180, 	// O1
 180, 	// O2
 300, 	// YY
 150, 	// RR
 220, 	// HH
 233, 	// LL
 250, 	// MM
 160, 	// NN
 120, 	// VV
 300, 	// SS
 300, 	// ZZ
 180, 	// PP
 130, 	// BB
 250, 	// TT
 250, 	// T2
 240, 	// DD
 280, 	// C
 280, 	// KK
 180, 	// GG
 -1, 	// AL
 -1, 	// NG
 150, 	// CZ
 150, 	// KZ
 -1, 	// TZ
// ==== AV ====
 0, 	// _ 
 64, 	// IY
 60, 	// EY
 63, 	// EH
 64, 	// AU
 64, 	// AH
 64, 	// AO
 65, 	// O
 64, 	// OY
 65, 	// U
 62, 	// AX
 60, 	// W 
 64, 	// Y
 64, 	// R 
 0, 	// H
 63, 	// L
 58, 	// M 
 60, 	// N 
 0, 	// F 
 40, 	// V 
 0, 	// TH
 0, 	// S 
 40, 	// Z 
 0, 	// SH
 0, 	// P 
 0, 	// B 
 0, 	// T 
 0, 	// D 
 0, 	// K 
 0, 	// G 
 54, 	// Q 
 40, 	// JH
 0, 	// TS
 0, 	// CH
 63, 	// E1
 64, 	// A1
 65, 	// O1
 65, 	// O2
 70, 	// YY
 70, 	// RR
 0, 	// HH
 70, 	// LL
 62, 	// MM
 68, 	// NN
 44, 	// VV
 0, 	// SS
 44, 	// ZZ
 0, 	// PP
 0, 	// BB
 0, 	// TT
 0, 	// T2
 0, 	// DD
 0, 	// C
 0, 	// KK
 0, 	// GG
 54, 	// AL
 54, 	// NG
 0, 	// CZ
 0, 	// KZ
 0 };	// TZ

// Male - F1,F1T,F2,F2T,F3,F3T,B1,B1T,B2,B2T,B3,B3T,AV,AVT data for Multi-part formants
const short hb_maldip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _ 
 0, 	// _ 
 340, 	// IY F1
 40, 	// IY F1 duration
 330, 	// IY F1
 -1, 	// IY F1 duration
 710, 	// AU F1
 110, 	// AU F1 duration
 550, 	// AU F1
 230, 	// AU F1 duration
 550, 	// AU F1
 -1, 	// AU F1 duration
 620, 	// AH F1
 40, 	// AH F1 duration
 620, 	// AH F1
 100, 	// AH F1 duration
 620, 	// AH F1
 -1, 	// AH F1 duration
 640, 	// AO F1
 120, 	// AO F1 duration
 700, 	// AO F1
 220, 	// AO F1 duration
 700, 	// AO F1
 -1, 	// AO F1 duration
 540, 	// OY F1
 10, 	// OY F1 duration
 580, 	// OY F1
 90, 	// OY F1 duration
 470, 	// OY F1
 220, 	// OY F1 duration
 470, 	// OY F1
 -1, 	// OY F1 duration
 440, 	// U F1
 10, 	// U F1 duration
 380, 	// U F1
 -1, 	// U F1 duration
 550, 	// AX F1
 30, 	// AX F1 duration
 550, 	// AX F1
 90, 	// AX F1 duration
 550, 	// AX F1
 -1, 	// AX F1 duration
 620, 	// A1 F1
 40, 	// A1 F1 duration
 620, 	// A1 F1
 100, 	// A1 F1 duration
 620, 	// A1 F1
 -1, 	// A1 F1 duration
 2100, 	// IY F2
 40, 	// IY F2 duration
 2140, 	// IY F2
 -1, 	// IY F2 duration
 1200, 	// AU F2
 110, 	// AU F2 duration
 820, 	// AU F2
 225, 	// AU F2 duration
 820, 	// AU F2
 -1, 	// AU F2 duration
 1170, 	// AH F2
 40, 	// AH F2 duration
 1170, 	// AH F2
 100, 	// AH F2 duration
 1170, 	// AH F2
 -1, 	// AH F2 duration
 929, 	// AO F2
 120, 	// AO F2 duration
 1100, 	// AO F2
 220, 	// AO F2 duration
 1125, 	// AO F2
 -1, 	// AO F2 duration
 900, 	// OY F2
 50, 	// OY F2 duration
 920, 	// OY F2
 90, 	// OY F2 duration
 1860, 	// OY F2
 220, 	// OY F2 duration
 1860, 	// OY F2
 -1, 	// OY F2 duration
 866, 	// U F2
 10, 	// U F2 duration
 750, 	// U F2
 -1, 	// U F2 duration
 1260, 	// AX F2
 30, 	// AX F2 duration
 1260, 	// AX F2
 90, 	// AX F2 duration
 1260, 	// AX F2
 -1, 	// AX F2 duration
 1170, 	// A1 F2
 40, 	// A1 F2 duration
 1170, 	// A1 F2
 100, 	// A1 F2 duration
 1170, 	// A1 F2
 -1, 	// A1 F2 duration
 2720, 	// IY F3
 40, 	// IY F3 duration
 2700, 	// IY F3
 -1, 	// IY F3 duration
 2650, 	// AU F3
 120, 	// AU F3 duration
 2550, 	// AU F3
 230, 	// AU F3 duration
 2550, 	// AU F3
 -1, 	// AU F3 duration
 2600, 	// AH F3
 40, 	// AH F3 duration
 2600, 	// AH F3
 100, 	// AH F3 duration
 2600, 	// AH F3
 -1, 	// AH F3 duration
 2640, 	// AO F3
 40, 	// AO F3 duration
 2640, 	// AO F3
 100, 	// AO F3 duration
 2640, 	// AO F3
 -1, 	// AO F3 duration
 2500, 	// OY F3
 140, 	// OY F3 duration
 2250, 	// OY F3
 200, 	// OY F3 duration
 2400, 	// OY F3
 250, 	// OY F3 duration
 2400, 	// OY F3
 -1, 	// OY F3 duration
 2451, 	// U F3
 10, 	// U F3 duration
 2451, 	// U F3
 -1, 	// U F3 duration
 2600, 	// AX F3
 30, 	// AX F3 duration
 2600, 	// AX F3
 90, 	// AX F3 duration
 2600, 	// AX F3
 -1, 	// AX F3 duration
 2600, 	// A1 F3
 40, 	// A1 F3 duration
 2600, 	// A1 F3
 100, 	// A1 F3 duration
 2600, 	// A1 F3
 -1, 	// A1 F3 duration
// ====== Bandwidths and duration ======
 120, 	// AU B1
 130, 	// AU B1 duration
 100, 	// AU B1
 240, 	// AU B1 duration
 100, 	// AU B1
 -1, 	// AU B1 duration
 110, 	// OY B2
 100, 	// OY B2 duration
 100, 	// OY B2
 210, 	// OY B2 duration
 220, 	// OY B2
 -1, 	// OY B2 duration
// ====== Amplitude of Voicing ======
 0};

// Female diphthongs
const short hb_femdip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _ 
 0, 	// _ 
 340, 	// IY F1
 40, 	// IY F1 duration
 330, 	// IY F1
 -1, 	// IY F1 duration
 710, 	// AU F1
 110, 	// AU F1 duration
 550, 	// AU F1
 230, 	// AU F1 duration
 550, 	// AU F1
 -1, 	// AU F1 duration
 620, 	// AH F1
 40, 	// AH F1 duration
 620, 	// AH F1
 100, 	// AH F1 duration
 620, 	// AH F1
 -1, 	// AH F1 duration
 640, 	// AO F1
 120, 	// AO F1 duration
 700, 	// AO F1
 220, 	// AO F1 duration
 700, 	// AO F1
 -1, 	// AO F1 duration
 540, 	// OY F1
 10, 	// OY F1 duration
 580, 	// OY F1
 90, 	// OY F1 duration
 470, 	// OY F1
 220, 	// OY F1 duration
 470, 	// OY F1
 -1, 	// OY F1 duration
 440, 	// U F1
 10, 	// U F1 duration
 380, 	// U F1
 -1, 	// U F1 duration
 550, 	// AX F1
 30, 	// AX F1 duration
 550, 	// AX F1
 90, 	// AX F1 duration
 550, 	// AX F1
 -1, 	// AX F1 duration
 620, 	// A1 F1
 40, 	// A1 F1 duration
 620, 	// A1 F1
 100, 	// A1 F1 duration
 620, 	// A1 F1
 -1, 	// A1 F1 duration
 2100, 	// IY F2
 40, 	// IY F2 duration
 2140, 	// IY F2
 -1, 	// IY F2 duration
 1200, 	// AU F2
 110, 	// AU F2 duration
 820, 	// AU F2
 225, 	// AU F2 duration
 820, 	// AU F2
 -1, 	// AU F2 duration
 1170, 	// AH F2
 40, 	// AH F2 duration
 1170, 	// AH F2
 100, 	// AH F2 duration
 1170, 	// AH F2
 -1, 	// AH F2 duration
 929, 	// AO F2
 120, 	// AO F2 duration
 1100, 	// AO F2
 220, 	// AO F2 duration
 1125, 	// AO F2
 -1, 	// AO F2 duration
 900, 	// OY F2
 50, 	// OY F2 duration
 920, 	// OY F2
 90, 	// OY F2 duration
 1860, 	// OY F2
 220, 	// OY F2 duration
 1860, 	// OY F2
 -1, 	// OY F2 duration
 866, 	// U F2
 10, 	// U F2 duration
 750, 	// U F2
 -1, 	// U F2 duration
 1260, 	// AX F2
 30, 	// AX F2 duration
 1260, 	// AX F2
 90, 	// AX F2 duration
 1260, 	// AX F2
 -1, 	// AX F2 duration
 1170, 	// A1 F2
 40, 	// A1 F2 duration
 1170, 	// A1 F2
 100, 	// A1 F2 duration
 1170, 	// A1 F2
 -1, 	// A1 F2 duration
 2720, 	// IY F3
 40, 	// IY F3 duration
 2700, 	// IY F3
 -1, 	// IY F3 duration
 2650, 	// AU F3
 120, 	// AU F3 duration
 2550, 	// AU F3
 230, 	// AU F3 duration
 2550, 	// AU F3
 -1, 	// AU F3 duration
 2600, 	// AH F3
 40, 	// AH F3 duration
 2600, 	// AH F3
 100, 	// AH F3 duration
 2600, 	// AH F3
 -1, 	// AH F3 duration
 2640, 	// AO F3
 40, 	// AO F3 duration
 2640, 	// AO F3
 100, 	// AO F3 duration
 2640, 	// AO F3
 -1, 	// AO F3 duration
 2500, 	// OY F3
 140, 	// OY F3 duration
 2250, 	// OY F3
 200, 	// OY F3 duration
 2400, 	// OY F3
 250, 	// OY F3 duration
 2400, 	// OY F3
 -1, 	// OY F3 duration
 2451, 	// U F3
 10, 	// U F3 duration
 2451, 	// U F3
 -1, 	// U F3 duration
 2600, 	// AX F3
 30, 	// AX F3 duration
 2600, 	// AX F3
 90, 	// AX F3 duration
 2600, 	// AX F3
 -1, 	// AX F3 duration
 2600, 	// A1 F3
 40, 	// A1 F3 duration
 2600, 	// A1 F3
 100, 	// A1 F3 duration
 2600, 	// A1 F3
 -1, 	// A1 F3 duration
// ====== Bandwidths and duration ======
 120, 	// AU B1
 130, 	// AU B1 duration
 100, 	// AU B1
 240, 	// AU B1 duration
 100, 	// AU B1
 -1, 	// AU B1 duration
 110, 	// OY B2
 100, 	// OY B2 duration
 100, 	// OY B2
 210, 	// OY B2 duration
 220, 	// OY B2
 -1, 	// OY B2 duration
// ====== Amplitude of Voicing ======
 0};

// Offsets into Amplitude data
const short hb_ptram_def[] = {
 0, 	// _ 
 0, 	// IY
 0, 	// EY
 0, 	// EH
 0, 	// AU
 0, 	// AH
 0, 	// AO
 0, 	// O
 0, 	// OY
 0, 	// U
 0, 	// AX
 0, 	// W 
 0, 	// Y
 0, 	// R 
 0, 	// H
 0, 	// L
 0, 	// M 
 0, 	// N 
 1, 	// F 
 31, 	// V 
 61, 	// TH
 91, 	// S 
 121, 	// Z 
 151, 	// SH
 181, 	// P 
 211, 	// B 
 241, 	// T 
 271, 	// D 
 301, 	// K 
 331, 	// G 
 0, 	// Q 
 361, 	// JH
 391, 	// TS
 421, 	// CH
 0, 	// E1
 0, 	// A1
 0, 	// O1
 0, 	// O2
 0, 	// YY
 0, 	// RR
 0, 	// HH
 0, 	// LL
 0, 	// MM
 0, 	// NN
 451, 	// VV
 481, 	// SS
 511, 	// ZZ
 541, 	// PP
 571, 	// BB
 601, 	// TT
 631, 	// T2
 661, 	// DD
 691, 	// C
 721, 	// KK
 751, 	// GG
 0, 	// AL
 0, 	// NG
 781, 	// CZ
 811, 	// KZ
 841 };	// TZ

// Offsets into Locus data
const short hb_plocu_def[] = {
// ==== Front ====
 0, 	// _ 
 0, 	// IY
 0, 	// EY
 0, 	// EH
 0, 	// AU
 0, 	// AH
 0, 	// AO
 0, 	// O
 0, 	// OY
 0, 	// U
 0, 	// AX
 0, 	// W 
 0, 	// Y
 0, 	// R 
 0, 	// H
 0, 	// L
 1, 	// M 
 10, 	// N 
 19, 	// F 
 28, 	// V 
 37, 	// TH
 46, 	// S 
 55, 	// Z 
 64, 	// SH
 73, 	// P 
 82, 	// B 
 91, 	// T 
 100, 	// D 
 109, 	// K 
 118, 	// G 
 0, 	// Q 
 127, 	// JH
 136, 	// TS
 145, 	// CH
 0, 	// E1
 0, 	// A1
 0, 	// O1
 0, 	// O2
 0, 	// YY
 0, 	// RR
 0, 	// HH
 0, 	// LL
 154, 	// MM
 163, 	// NN
 172, 	// VV
 181, 	// SS
 190, 	// ZZ
 199, 	// PP
 208, 	// BB
 217, 	// TT
 226, 	// T2
 235, 	// DD
 244, 	// C
 253, 	// KK
 262, 	// GG
 0, 	// AL
 0, 	// NG
 271, 	// CZ
 280, 	// KZ
 289, 	// TZ
// ==== Back ====
 0, 	// _ 
 0, 	// IY
 0, 	// EY
 0, 	// EH
 0, 	// AU
 0, 	// AH
 0, 	// AO
 0, 	// O
 0, 	// OY
 0, 	// U
 0, 	// AX
 0, 	// W 
 0, 	// Y
 0, 	// R 
 0, 	// H
 0, 	// L
 298, 	// M 
 307, 	// N 
 316, 	// F 
 325, 	// V 
 334, 	// TH
 343, 	// S 
 352, 	// Z 
 361, 	// SH
 370, 	// P 
 379, 	// B 
 388, 	// T 
 397, 	// D 
 406, 	// K 
 415, 	// G 
 0, 	// Q 
 424, 	// JH
 433, 	// TS
 442, 	// CH
 0, 	// E1
 0, 	// A1
 0, 	// O1
 0, 	// O2
 0, 	// YY
 0, 	// RR
 0, 	// HH
 0, 	// LL
 451, 	// MM
 460, 	// NN
 469, 	// VV
 478, 	// SS
 487, 	// ZZ
 496, 	// PP
 505, 	// BB
 514, 	// TT
 523, 	// T2
 532, 	// DD
 541, 	// C
 550, 	// KK
 559, 	// GG
 0, 	// AL
 0, 	// NG
 568, 	// CZ
 577, 	// KZ
 586, 	// TZ
// ==== Round ====
 0, 	// _ 
 0, 	// IY
 0, 	// EY
 0, 	// EH
 0, 	// AU
 0, 	// AH
 0, 	// AO
 0, 	// O
 0, 	// OY
 0, 	// U
 0, 	// AX
 0, 	// W 
 0, 	// Y
 0, 	// R 
 0, 	// H
 0, 	// L
 595, 	// M 
 604, 	// N 
 613, 	// F 
 622, 	// V 
 631, 	// TH
 640, 	// S 
 649, 	// Z 
 658, 	// SH
 667, 	// P 
 676, 	// B 
 685, 	// T 
 694, 	// D 
 703, 	// K 
 712, 	// G 
 0, 	// Q 
 721, 	// JH
 730, 	// TS
 739, 	// CH
 0, 	// E1
 0, 	// A1
 0, 	// O1
 0, 	// O2
 0, 	// YY
 0, 	// RR
 0, 	// HH
 0, 	// LL
 748, 	// MM
 757, 	// NN
 766, 	// VV
 775, 	// SS
 784, 	// ZZ
 793, 	// PP
 802, 	// BB
 811, 	// TT
 820, 	// T2
 829, 	// DD
 838, 	// C
 847, 	// KK
 856, 	// GG
 0, 	// AL
 0, 	// NG
 865, 	// CZ
 874, 	// KZ
 883, 	// TZ
// ==== Low ====
 0, 	// _ 
 0, 	// IY
 0, 	// EY
 0, 	// EH
 0, 	// AU
 0, 	// AH
 0, 	// AO
 0, 	// O
 0, 	// OY
 0, 	// U
 0, 	// AX
 0, 	// W 
 0, 	// Y
 0, 	// R 
 0, 	// H
 0, 	// L
 892, 	// M 
 901, 	// N 
 910, 	// F 
 919, 	// V 
 928, 	// TH
 937, 	// S 
 946, 	// Z 
 955, 	// SH
 964, 	// P 
 973, 	// B 
 982, 	// T 
 991, 	// D 
 1000, 	// K 
 1009, 	// G 
 0, 	// Q 
 1018, 	// JH
 0, 	// TS
 0, 	// CH
 0, 	// E1
 0, 	// A1
 0, 	// O1
 0, 	// O2
 0, 	// YY
 0, 	// RR
 0, 	// HH
 0, 	// LL
 1027, 	// MM
 1036, 	// NN
 1045, 	// VV
 1054, 	// SS
 1063, 	// ZZ
 1072, 	// PP
 1081, 	// BB
 1090, 	// TT
 1099, 	// T2
 1108, 	// DD
 1117, 	// C
 1126, 	// KK
 1135, 	// GG
 0, 	// AL
 0, 	// NG
 0, 	// CZ
 0, 	// KZ
 0 };	// TZ

// Male Locus data
const short hb_maleloc_def[] = {
 0, 
// Front
 260, 	// M  F1 locus
 80, 	// M  percent
 40, 	// M  transition duration
 1200, 	// M  F2 locus
 10, 	// M  percent
 35, 	// M  transition duration
 2322, 	// M  F3 locus
 40, 	// M  percent
 40, 	// M  transition duration
 450, 	// N  F1 locus
 20, 	// N  percent
 35, 	// N  transition duration
 1350, 	// N  F2 locus
 75, 	// N  percent
 35, 	// N  transition duration
 2600, 	// N  F3 locus
 40, 	// N  percent
 45, 	// N  transition duration
 300, 	// F  F1 locus
 63, 	// F  percent
 30, 	// F  transition duration
 1, 	// F  F2 locus
 92, 	// F  percent
 35, 	// F  transition duration
 2080, 	// F  F3 locus
 35, 	// F  percent
 30, 	// F  transition duration
 300, 	// V  F1 locus
 50, 	// V  percent
 30, 	// V  transition duration
 1, 	// V  F2 locus
 92, 	// V  percent
 35, 	// V  transition duration
 2080, 	// V  F3 locus
 35, 	// V  percent
 40, 	// V  transition duration
 340, 	// TH F1 locus
 10, 	// TH percent
 45, 	// TH transition duration
 1500, 	// TH F2 locus
 20, 	// TH percent
 35, 	// TH transition duration
 2420, 	// TH F3 locus
 0, 	// TH percent
 50, 	// TH transition duration
 310, 	// S  F1 locus
 40, 	// S  percent
 40, 	// S  transition duration
 1440, 	// S  F2 locus
 40, 	// S  percent
 50, 	// S  transition duration
 2550, 	// S  F3 locus
 0, 	// S  percent
 70, 	// S  transition duration
 310, 	// Z  F1 locus
 40, 	// Z  percent
 40, 	// Z  transition duration
 1440, 	// Z  F2 locus
 35, 	// Z  percent
 50, 	// Z  transition duration
 2550, 	// Z  F3 locus
 0, 	// Z  percent
 70, 	// Z  transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1630, 	// SH F2 locus
 30, 	// SH percent
 70, 	// SH transition duration
 2640, 	// SH F3 locus
 51, 	// SH percent
 70, 	// SH transition duration
 350, 	// P  F1 locus
 55, 	// P  percent
 20, 	// P  transition duration
 950, 	// P  F2 locus
 56, 	// P  percent
 50, 	// P  transition duration
 2200, 	// P  F3 locus
 25, 	// P  percent
 50, 	// P  transition duration
 330, 	// B  F1 locus
 55, 	// B  percent
 20, 	// B  transition duration
 900, 	// B  F2 locus
 56, 	// B  percent
 30, 	// B  transition duration
 2200, 	// B  F3 locus
 25, 	// B  percent
 45, 	// B  transition duration
 320, 	// T  F1 locus
 43, 	// T  percent
 35, 	// T  transition duration
 1700, 	// T  F2 locus
 66, 	// T  percent
 35, 	// T  transition duration
 2650, 	// T  F3 locus
 30, 	// T  percent
 45, 	// T  transition duration
 250, 	// D  F1 locus
 43, 	// D  percent
 35, 	// D  transition duration
 1800, 	// D  F2 locus
 66, 	// D  percent
 35, 	// D  transition duration
 2650, 	// D  F3 locus
 30, 	// D  percent
 45, 	// D  transition duration
 280, 	// K  F1 locus
 33, 	// K  percent
 45, 	// K  transition duration
 1980, 	// K  F2 locus
 20, 	// K  percent
 55, 	// K  transition duration
 3000, 	// K  F3 locus
 117, 	// K  percent
 50, 	// K  transition duration
 250, 	// G  F1 locus
 33, 	// G  percent
 45, 	// G  transition duration
 2100, 	// G  F2 locus
 20, 	// G  percent
 50, 	// G  transition duration
 2100, 	// G  F3 locus
 50, 	// G  percent
 45, 	// G  transition duration
 240, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1750, 	// JH F2 locus
 25, 	// JH percent
 70, 	// JH transition duration
 2750, 	// JH F3 locus
 19, 	// JH percent
 70, 	// JH transition duration
 501, 	// TS F1 locus
 50, 	// TS percent
 70, 	// TS transition duration
 1500, 	// TS F2 locus
 20, 	// TS percent
 150, 	// TS transition duration
 2600, 	// TS F3 locus
 50, 	// TS percent
 50, 	// TS transition duration
 300, 	// CH F1 locus
 70, 	// CH percent
 20, 	// CH transition duration
 1610, 	// CH F2 locus
 70, 	// CH percent
 30, 	// CH transition duration
 2160, 	// CH F3 locus
 50, 	// CH percent
 60, 	// CH transition duration
 260, 	// MM F1 locus
 80, 	// MM percent
 40, 	// MM transition duration
 1200, 	// MM F2 locus
 10, 	// MM percent
 35, 	// MM transition duration
 2322, 	// MM F3 locus
 40, 	// MM percent
 40, 	// MM transition duration
 450, 	// NN F1 locus
 20, 	// NN percent
 35, 	// NN transition duration
 1350, 	// NN F2 locus
 75, 	// NN percent
 35, 	// NN transition duration
 2600, 	// NN F3 locus
 40, 	// NN percent
 45, 	// NN transition duration
 300, 	// VV F1 locus
 50, 	// VV percent
 30, 	// VV transition duration
 1, 	// VV F2 locus
 92, 	// VV percent
 35, 	// VV transition duration
 2080, 	// VV F3 locus
 35, 	// VV percent
 40, 	// VV transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1440, 	// SS F2 locus
 40, 	// SS percent
 50, 	// SS transition duration
 2550, 	// SS F3 locus
 0, 	// SS percent
 70, 	// SS transition duration
 310, 	// ZZ F1 locus
 40, 	// ZZ percent
 40, 	// ZZ transition duration
 1440, 	// ZZ F2 locus
 35, 	// ZZ percent
 50, 	// ZZ transition duration
 2550, 	// ZZ F3 locus
 0, 	// ZZ percent
 70, 	// ZZ transition duration
 350, 	// PP F1 locus
 55, 	// PP percent
 20, 	// PP transition duration
 950, 	// PP F2 locus
 56, 	// PP percent
 50, 	// PP transition duration
 2200, 	// PP F3 locus
 25, 	// PP percent
 50, 	// PP transition duration
 330, 	// BB F1 locus
 55, 	// BB percent
 20, 	// BB transition duration
 900, 	// BB F2 locus
 56, 	// BB percent
 30, 	// BB transition duration
 2200, 	// BB F3 locus
 25, 	// BB percent
 45, 	// BB transition duration
 320, 	// TT F1 locus
 43, 	// TT percent
 35, 	// TT transition duration
 1700, 	// TT F2 locus
 66, 	// TT percent
 35, 	// TT transition duration
 2650, 	// TT F3 locus
 30, 	// TT percent
 45, 	// TT transition duration
 320, 	// T2 F1 locus
 43, 	// T2 percent
 35, 	// T2 transition duration
 1700, 	// T2 F2 locus
 66, 	// T2 percent
 35, 	// T2 transition duration
 2650, 	// T2 F3 locus
 30, 	// T2 percent
 45, 	// T2 transition duration
 250, 	// DD F1 locus
 43, 	// DD percent
 35, 	// DD transition duration
 1800, 	// DD F2 locus
 66, 	// DD percent
 35, 	// DD transition duration
 2650, 	// DD F3 locus
 30, 	// DD percent
 45, 	// DD transition duration
 280, 	// C F1 locus
 33, 	// C percent
 45, 	// C transition duration
 1980, 	// C F2 locus
 20, 	// C percent
 55, 	// C transition duration
 3000, 	// C F3 locus
 117, 	// C percent
 50, 	// C transition duration
 280, 	// KK F1 locus
 33, 	// KK percent
 45, 	// KK transition duration
 1980, 	// KK F2 locus
 20, 	// KK percent
 55, 	// KK transition duration
 3000, 	// KK F3 locus
 117, 	// KK percent
 50, 	// KK transition duration
 250, 	// GG F1 locus
 33, 	// GG percent
 45, 	// GG transition duration
 2100, 	// GG F2 locus
 20, 	// GG percent
 50, 	// GG transition duration
 2100, 	// GG F3 locus
 50, 	// GG percent
 45, 	// GG transition duration
 300, 	// CZ F1 locus
 70, 	// CZ percent
 20, 	// CZ transition duration
 1869, 	// CZ F2 locus
 99, 	// CZ percent
 80, 	// CZ transition duration
 2569, 	// CZ F3 locus
 63, 	// CZ percent
 50, 	// CZ transition duration
 300, 	// KZ F1 locus
 70, 	// KZ percent
 20, 	// KZ transition duration
 1869, 	// KZ F2 locus
 99, 	// KZ percent
 80, 	// KZ transition duration
 2569, 	// KZ F3 locus
 63, 	// KZ percent
 50, 	// KZ transition duration
 501, 	// TZ F1 locus
 50, 	// TZ percent
 70, 	// TZ transition duration
 1500, 	// TZ F2 locus
 20, 	// TZ percent
 150, 	// TZ transition duration
 2600, 	// TZ F3 locus
 50, 	// TZ percent
 50, 	// TZ transition duration
// Back
 450, 	// M  F1 locus
 20, 	// M  percent
 30, 	// M  transition duration
 1, 	// M  F2 locus
 88, 	// M  percent
 40, 	// M  transition duration
 2000, 	// M  F3 locus
 80, 	// M  percent
 25, 	// M  transition duration
 450, 	// N  F1 locus
 20, 	// N  percent
 30, 	// N  transition duration
 1520, 	// N  F2 locus
 25, 	// N  percent
 75, 	// N  transition duration
 2600, 	// N  F3 locus
 0, 	// N  percent
 60, 	// N  transition duration
 320, 	// F  F1 locus
 60, 	// F  percent
 30, 	// F  transition duration
 1, 	// F  F2 locus
 91, 	// F  percent
 35, 	// F  transition duration
 2100, 	// F  F3 locus
 65, 	// F  percent
 40, 	// F  transition duration
 300, 	// V  F1 locus
 50, 	// V  percent
 30, 	// V  transition duration
 1, 	// V  F2 locus
 91, 	// V  percent
 40, 	// V  transition duration
 2100, 	// V  F3 locus
 65, 	// V  percent
 40, 	// V  transition duration
 350, 	// TH F1 locus
 10, 	// TH percent
 50, 	// TH transition duration
 1300, 	// TH F2 locus
 12, 	// TH percent
 55, 	// TH transition duration
 2500, 	// TH F3 locus
 11, 	// TH percent
 55, 	// TH transition duration
 310, 	// S  F1 locus
 40, 	// S  percent
 40, 	// S  transition duration
 1440, 	// S  F2 locus
 40, 	// S  percent
 50, 	// S  transition duration
 2530, 	// S  F3 locus
 0, 	// S  percent
 70, 	// S  transition duration
 310, 	// Z  F1 locus
 40, 	// Z  percent
 40, 	// Z  transition duration
 1440, 	// Z  F2 locus
 35, 	// Z  percent
 60, 	// Z  transition duration
 2630, 	// Z  F3 locus
 0, 	// Z  percent
 70, 	// Z  transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1600, 	// SH F2 locus
 27, 	// SH percent
 70, 	// SH transition duration
 2270, 	// SH F3 locus
 0, 	// SH percent
 85, 	// SH transition duration
 350, 	// P  F1 locus
 45, 	// P  percent
 25, 	// P  transition duration
 920, 	// P  F2 locus
 46, 	// P  percent
 50, 	// P  transition duration
 1900, 	// P  F3 locus
 40, 	// P  percent
 50, 	// P  transition duration
 330, 	// B  F1 locus
 45, 	// B  percent
 25, 	// B  transition duration
 920, 	// B  F2 locus
 46, 	// B  percent
 30, 	// B  transition duration
 2250, 	// B  F3 locus
 40, 	// B  percent
 50, 	// B  transition duration
 320, 	// T  F1 locus
 43, 	// T  percent
 50, 	// T  transition duration
 1700, 	// T  F2 locus
 10, 	// T  percent
 75, 	// T  transition duration
 2600, 	// T  F3 locus
 10, 	// T  percent
 50, 	// T  transition duration
 250, 	// D  F1 locus
 43, 	// D  percent
 50, 	// D  transition duration
 1700, 	// D  F2 locus
 40, 	// D  percent
 75, 	// D  transition duration
 2600, 	// D  F3 locus
 0, 	// D  percent
 50, 	// D  transition duration
 280, 	// K  F1 locus
 33, 	// K  percent
 50, 	// K  transition duration
 1800, 	// K  F2 locus
 16, 	// K  percent
 50, 	// K  transition duration
 2000, 	// K  F3 locus
 20, 	// K  percent
 90, 	// K  transition duration
 250, 	// G  F1 locus
 33, 	// G  percent
 50, 	// G  transition duration
 1800, 	// G  F2 locus
 16, 	// G  percent
 60, 	// G  transition duration
 2100, 	// G  F3 locus
 0, 	// G  percent
 90, 	// G  transition duration
 245, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1680, 	// JH F2 locus
 5, 	// JH percent
 120, 	// JH transition duration
 2450, 	// JH F3 locus
 10, 	// JH percent
 70, 	// JH transition duration
 290, 	// TS F1 locus
 70, 	// TS percent
 35, 	// TS transition duration
 1500, 	// TS F2 locus
 20, 	// TS percent
 80, 	// TS transition duration
 2600, 	// TS F3 locus
 50, 	// TS percent
 30, 	// TS transition duration
 300, 	// CH F1 locus
 70, 	// CH percent
 30, 	// CH transition duration
 1711, 	// CH F2 locus
 70, 	// CH percent
 30, 	// CH transition duration
 2150, 	// CH F3 locus
 50, 	// CH percent
 60, 	// CH transition duration
 450, 	// MM F1 locus
 20, 	// MM percent
 30, 	// MM transition duration
 1, 	// MM F2 locus
 88, 	// MM percent
 40, 	// MM transition duration
 2000, 	// MM F3 locus
 80, 	// MM percent
 25, 	// MM transition duration
 450, 	// NN F1 locus
 20, 	// NN percent
 30, 	// NN transition duration
 1520, 	// NN F2 locus
 25, 	// NN percent
 75, 	// NN transition duration
 2600, 	// NN F3 locus
 0, 	// NN percent
 60, 	// NN transition duration
 300, 	// VV F1 locus
 50, 	// VV percent
 30, 	// VV transition duration
 1, 	// VV F2 locus
 91, 	// VV percent
 40, 	// VV transition duration
 2100, 	// VV F3 locus
 65, 	// VV percent
 40, 	// VV transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1440, 	// SS F2 locus
 40, 	// SS percent
 50, 	// SS transition duration
 2530, 	// SS F3 locus
 0, 	// SS percent
 70, 	// SS transition duration
 310, 	// ZZ F1 locus
 40, 	// ZZ percent
 40, 	// ZZ transition duration
 1440, 	// ZZ F2 locus
 35, 	// ZZ percent
 60, 	// ZZ transition duration
 2630, 	// ZZ F3 locus
 0, 	// ZZ percent
 70, 	// ZZ transition duration
 350, 	// PP F1 locus
 45, 	// PP percent
 25, 	// PP transition duration
 920, 	// PP F2 locus
 46, 	// PP percent
 50, 	// PP transition duration
 1900, 	// PP F3 locus
 40, 	// PP percent
 50, 	// PP transition duration
 330, 	// BB F1 locus
 45, 	// BB percent
 25, 	// BB transition duration
 920, 	// BB F2 locus
 46, 	// BB percent
 30, 	// BB transition duration
 2250, 	// BB F3 locus
 40, 	// BB percent
 50, 	// BB transition duration
 320, 	// TT F1 locus
 43, 	// TT percent
 50, 	// TT transition duration
 1700, 	// TT F2 locus
 10, 	// TT percent
 75, 	// TT transition duration
 2600, 	// TT F3 locus
 10, 	// TT percent
 50, 	// TT transition duration
 320, 	// T2 F1 locus
 43, 	// T2 percent
 50, 	// T2 transition duration
 1700, 	// T2 F2 locus
 10, 	// T2 percent
 75, 	// T2 transition duration
 2600, 	// T2 F3 locus
 10, 	// T2 percent
 50, 	// T2 transition duration
 250, 	// DD F1 locus
 43, 	// DD percent
 50, 	// DD transition duration
 1700, 	// DD F2 locus
 40, 	// DD percent
 75, 	// DD transition duration
 2600, 	// DD F3 locus
 0, 	// DD percent
 50, 	// DD transition duration
 280, 	// C F1 locus
 33, 	// C percent
 50, 	// C transition duration
 1800, 	// C F2 locus
 16, 	// C percent
 50, 	// C transition duration
 2000, 	// C F3 locus
 20, 	// C percent
 90, 	// C transition duration
 280, 	// KK F1 locus
 33, 	// KK percent
 50, 	// KK transition duration
 1800, 	// KK F2 locus
 16, 	// KK percent
 50, 	// KK transition duration
 2000, 	// KK F3 locus
 20, 	// KK percent
 90, 	// KK transition duration
 250, 	// GG F1 locus
 33, 	// GG percent
 50, 	// GG transition duration
 1800, 	// GG F2 locus
 16, 	// GG percent
 60, 	// GG transition duration
 2100, 	// GG F3 locus
 0, 	// GG percent
 90, 	// GG transition duration
 300, 	// CZ F1 locus
 70, 	// CZ percent
 30, 	// CZ transition duration
 1711, 	// CZ F2 locus
 70, 	// CZ percent
 30, 	// CZ transition duration
 2150, 	// CZ F3 locus
 50, 	// CZ percent
 60, 	// CZ transition duration
 300, 	// KZ F1 locus
 70, 	// KZ percent
 30, 	// KZ transition duration
 1711, 	// KZ F2 locus
 70, 	// KZ percent
 30, 	// KZ transition duration
 2150, 	// KZ F3 locus
 50, 	// KZ percent
 60, 	// KZ transition duration
 290, 	// TZ F1 locus
 70, 	// TZ percent
 35, 	// TZ transition duration
 1500, 	// TZ F2 locus
 20, 	// TZ percent
 80, 	// TZ transition duration
 2600, 	// TZ F3 locus
 50, 	// TZ percent
 30, 	// TZ transition duration
// Round
 450, 	// M  F1 locus
 20, 	// M  percent
 30, 	// M  transition duration
 970, 	// M  F2 locus
 10, 	// M  percent
 40, 	// M  transition duration
 1550, 	// M  F3 locus
 80, 	// M  percent
 25, 	// M  transition duration
 450, 	// N  F1 locus
 20, 	// N  percent
 30, 	// N  transition duration
 1500, 	// N  F2 locus
 30, 	// N  percent
 80, 	// N  transition duration
 2520, 	// N  F3 locus
 0, 	// N  percent
 95, 	// N  transition duration
 320, 	// F  F1 locus
 60, 	// F  percent
 30, 	// F  transition duration
 1, 	// F  F2 locus
 91, 	// F  percent
 35, 	// F  transition duration
 2100, 	// F  F3 locus
 65, 	// F  percent
 40, 	// F  transition duration
 325, 	// V  F1 locus
 50, 	// V  percent
 30, 	// V  transition duration
 1, 	// V  F2 locus
 91, 	// V  percent
 40, 	// V  transition duration
 2100, 	// V  F3 locus
 65, 	// V  percent
 40, 	// V  transition duration
 350, 	// TH F1 locus
 10, 	// TH percent
 50, 	// TH transition duration
 1300, 	// TH F2 locus
 12, 	// TH percent
 55, 	// TH transition duration
 2500, 	// TH F3 locus
 11, 	// TH percent
 55, 	// TH transition duration
 310, 	// S  F1 locus
 40, 	// S  percent
 40, 	// S  transition duration
 1320, 	// S  F2 locus
 15, 	// S  percent
 60, 	// S  transition duration
 2460, 	// S  F3 locus
 0, 	// S  percent
 65, 	// S  transition duration
 310, 	// Z  F1 locus
 40, 	// Z  percent
 40, 	// Z  transition duration
 1520, 	// Z  F2 locus
 15, 	// Z  percent
 60, 	// Z  transition duration
 2460, 	// Z  F3 locus
 0, 	// Z  percent
 65, 	// Z  transition duration
 340, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1630, 	// SH F2 locus
 27, 	// SH percent
 90, 	// SH transition duration
 2100, 	// SH F3 locus
 20, 	// SH percent
 110, 	// SH transition duration
 320, 	// P  F1 locus
 45, 	// P  percent
 25, 	// P  transition duration
 920, 	// P  F2 locus
 46, 	// P  percent
 50, 	// P  transition duration
 1900, 	// P  F3 locus
 40, 	// P  percent
 50, 	// P  transition duration
 330, 	// B  F1 locus
 45, 	// B  percent
 25, 	// B  transition duration
 720, 	// B  F2 locus
 36, 	// B  percent
 50, 	// B  transition duration
 1800, 	// B  F3 locus
 40, 	// B  percent
 40, 	// B  transition duration
 320, 	// T  F1 locus
 43, 	// T  percent
 40, 	// T  transition duration
 1400, 	// T  F2 locus
 5, 	// T  percent
 60, 	// T  transition duration
 2300, 	// T  F3 locus
 0, 	// T  percent
 60, 	// T  transition duration
 250, 	// D  F1 locus
 43, 	// D  percent
 40, 	// D  transition duration
 1700, 	// D  F2 locus
 40, 	// D  percent
 95, 	// D  transition duration
 2601, 	// D  F3 locus
 30, 	// D  percent
 85, 	// D  transition duration
 280, 	// K  F1 locus
 33, 	// K  percent
 40, 	// K  transition duration
 1400, 	// K  F2 locus
 60, 	// K  percent
 75, 	// K  transition duration
 2050, 	// K  F3 locus
 15, 	// K  percent
 80, 	// K  transition duration
 250, 	// G  F1 locus
 45, 	// G  percent
 40, 	// G  transition duration
 1600, 	// G  F2 locus
 42, 	// G  percent
 65, 	// G  transition duration
 1920, 	// G  F3 locus
 15, 	// G  percent
 80, 	// G  transition duration
 245, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1680, 	// JH F2 locus
 10, 	// JH percent
 90, 	// JH transition duration
 1970, 	// JH F3 locus
 10, 	// JH percent
 100, 	// JH transition duration
 501, 	// TS F1 locus
 50, 	// TS percent
 40, 	// TS transition duration
 1600, 	// TS F2 locus
 20, 	// TS percent
 90, 	// TS transition duration
 2600, 	// TS F3 locus
 50, 	// TS percent
 40, 	// TS transition duration
 300, 	// CH F1 locus
 70, 	// CH percent
 30, 	// CH transition duration
 1610, 	// CH F2 locus
 70, 	// CH percent
 36, 	// CH transition duration
 2160, 	// CH F3 locus
 50, 	// CH percent
 60, 	// CH transition duration
 450, 	// MM F1 locus
 20, 	// MM percent
 30, 	// MM transition duration
 970, 	// MM F2 locus
 10, 	// MM percent
 40, 	// MM transition duration
 1550, 	// MM F3 locus
 80, 	// MM percent
 25, 	// MM transition duration
 450, 	// NN F1 locus
 20, 	// NN percent
 30, 	// NN transition duration
 1500, 	// NN F2 locus
 30, 	// NN percent
 80, 	// NN transition duration
 2520, 	// NN F3 locus
 0, 	// NN percent
 95, 	// NN transition duration
 325, 	// VV F1 locus
 50, 	// VV percent
 30, 	// VV transition duration
 1, 	// VV F2 locus
 91, 	// VV percent
 40, 	// VV transition duration
 2100, 	// VV F3 locus
 65, 	// VV percent
 40, 	// VV transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1320, 	// SS F2 locus
 15, 	// SS percent
 60, 	// SS transition duration
 2460, 	// SS F3 locus
 0, 	// SS percent
 65, 	// SS transition duration
 310, 	// ZZ F1 locus
 40, 	// ZZ percent
 40, 	// ZZ transition duration
 1520, 	// ZZ F2 locus
 15, 	// ZZ percent
 60, 	// ZZ transition duration
 2460, 	// ZZ F3 locus
 0, 	// ZZ percent
 65, 	// ZZ transition duration
 320, 	// PP F1 locus
 45, 	// PP percent
 25, 	// PP transition duration
 920, 	// PP F2 locus
 46, 	// PP percent
 50, 	// PP transition duration
 1900, 	// PP F3 locus
 40, 	// PP percent
 50, 	// PP transition duration
 330, 	// BB F1 locus
 45, 	// BB percent
 25, 	// BB transition duration
 720, 	// BB F2 locus
 36, 	// BB percent
 50, 	// BB transition duration
 1800, 	// BB F3 locus
 40, 	// BB percent
 40, 	// BB transition duration
 320, 	// TT F1 locus
 43, 	// TT percent
 40, 	// TT transition duration
 1700, 	// TT F2 locus
 5, 	// TT percent
 95, 	// TT transition duration
 2300, 	// TT F3 locus
 0, 	// TT percent
 95, 	// TT transition duration
 320, 	// T2 F1 locus
 43, 	// T2 percent
 40, 	// T2 transition duration
 1700, 	// T2 F2 locus
 5, 	// T2 percent
 95, 	// T2 transition duration
 2300, 	// T2 F3 locus
 0, 	// T2 percent
 95, 	// T2 transition duration
 250, 	// DD F1 locus
 43, 	// DD percent
 40, 	// DD transition duration
 1700, 	// DD F2 locus
 40, 	// DD percent
 95, 	// DD transition duration
 2601, 	// DD F3 locus
 30, 	// DD percent
 85, 	// DD transition duration
 280, 	// C F1 locus
 33, 	// C percent
 40, 	// C transition duration
 1400, 	// C F2 locus
 60, 	// C percent
 75, 	// C transition duration
 2050, 	// C F3 locus
 15, 	// C percent
 80, 	// C transition duration
 280, 	// KK F1 locus
 33, 	// KK percent
 40, 	// KK transition duration
 1400, 	// KK F2 locus
 60, 	// KK percent
 75, 	// KK transition duration
 2050, 	// KK F3 locus
 15, 	// KK percent
 80, 	// KK transition duration
 250, 	// GG F1 locus
 45, 	// GG percent
 40, 	// GG transition duration
 1600, 	// GG F2 locus
 42, 	// GG percent
 65, 	// GG transition duration
 1920, 	// GG F3 locus
 15, 	// GG percent
 80, 	// GG transition duration
 300, 	// CZ F1 locus
 70, 	// CZ percent
 30, 	// CZ transition duration
 1610, 	// CZ F2 locus
 70, 	// CZ percent
 36, 	// CZ transition duration
 2160, 	// CZ F3 locus
 50, 	// CZ percent
 60, 	// CZ transition duration
 300, 	// KZ F1 locus
 70, 	// KZ percent
 30, 	// KZ transition duration
 1610, 	// KZ F2 locus
 70, 	// KZ percent
 36, 	// KZ transition duration
 2160, 	// KZ F3 locus
 50, 	// KZ percent
 60, 	// KZ transition duration
 501, 	// TZ F1 locus
 50, 	// TZ percent
 40, 	// TZ transition duration
 1600, 	// TZ F2 locus
 20, 	// TZ percent
 90, 	// TZ transition duration
 2600, 	// TZ F3 locus
 50, 	// TZ percent
 40, 	// TZ transition duration
// Low
 0, 	// M  F1 locus
 0, 	// M  percent
 0, 	// M  transition duration
 0, 	// M  F2 locus
 0, 	// M  percent
 0, 	// M  transition duration
 0, 	// M  F3 locus
 0, 	// M  percent
 0, 	// M  transition duration
 0, 	// N  F1 locus
 0, 	// N  percent
 0, 	// N  transition duration
 0, 	// N  F2 locus
 0, 	// N  percent
 0, 	// N  transition duration
 0, 	// N  F3 locus
 0, 	// N  percent
 0, 	// N  transition duration
 0, 	// F  F1 locus
 0, 	// F  percent
 0, 	// F  transition duration
 0, 	// F  F2 locus
 0, 	// F  percent
 0, 	// F  transition duration
 0, 	// F  F3 locus
 0, 	// F  percent
 0, 	// F  transition duration
 0, 	// V  F1 locus
 0, 	// V  percent
 0, 	// V  transition duration
 0, 	// V  F2 locus
 0, 	// V  percent
 0, 	// V  transition duration
 0, 	// V  F3 locus
 0, 	// V  percent
 0, 	// V  transition duration
 0, 	// TH F1 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F2 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F3 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// S  F1 locus
 0, 	// S  percent
 0, 	// S  transition duration
 0, 	// S  F2 locus
 0, 	// S  percent
 0, 	// S  transition duration
 0, 	// S  F3 locus
 0, 	// S  percent
 0, 	// S  transition duration
 0, 	// Z  F1 locus
 0, 	// Z  percent
 0, 	// Z  transition duration
 0, 	// Z  F2 locus
 0, 	// Z  percent
 0, 	// Z  transition duration
 0, 	// Z  F3 locus
 0, 	// Z  percent
 0, 	// Z  transition duration
 0, 	// SH F1 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// SH F2 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// SH F3 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// P  F1 locus
 0, 	// P  percent
 0, 	// P  transition duration
 0, 	// P  F2 locus
 0, 	// P  percent
 0, 	// P  transition duration
 0, 	// P  F3 locus
 0, 	// P  percent
 0, 	// P  transition duration
 0, 	// B  F1 locus
 0, 	// B  percent
 0, 	// B  transition duration
 0, 	// B  F2 locus
 0, 	// B  percent
 0, 	// B  transition duration
 0, 	// B  F3 locus
 0, 	// B  percent
 0, 	// B  transition duration
 0, 	// T  F1 locus
 0, 	// T  percent
 0, 	// T  transition duration
 0, 	// T  F2 locus
 0, 	// T  percent
 0, 	// T  transition duration
 0, 	// T  F3 locus
 0, 	// T  percent
 0, 	// T  transition duration
 0, 	// D  F1 locus
 0, 	// D  percent
 0, 	// D  transition duration
 0, 	// D  F2 locus
 0, 	// D  percent
 0, 	// D  transition duration
 0, 	// D  F3 locus
 0, 	// D  percent
 0, 	// D  transition duration
 0, 	// K  F1 locus
 0, 	// K  percent
 0, 	// K  transition duration
 0, 	// K  F2 locus
 0, 	// K  percent
 0, 	// K  transition duration
 0, 	// K  F3 locus
 0, 	// K  percent
 0, 	// K  transition duration
 0, 	// G  F1 locus
 0, 	// G  percent
 0, 	// G  transition duration
 0, 	// G  F2 locus
 0, 	// G  percent
 0, 	// G  transition duration
 0, 	// G  F3 locus
 0, 	// G  percent
 0, 	// G  transition duration
 0, 	// JH F1 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F2 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F3 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// MM F1 locus
 0, 	// MM percent
 0, 	// MM transition duration
 0, 	// MM F2 locus
 0, 	// MM percent
 0, 	// MM transition duration
 0, 	// MM F3 locus
 0, 	// MM percent
 0, 	// MM transition duration
 0, 	// NN F1 locus
 0, 	// NN percent
 0, 	// NN transition duration
 0, 	// NN F2 locus
 0, 	// NN percent
 0, 	// NN transition duration
 0, 	// NN F3 locus
 0, 	// NN percent
 0, 	// NN transition duration
 0, 	// VV F1 locus
 0, 	// VV percent
 0, 	// VV transition duration
 0, 	// VV F2 locus
 0, 	// VV percent
 0, 	// VV transition duration
 0, 	// VV F3 locus
 0, 	// VV percent
 0, 	// VV transition duration
 0, 	// SS F1 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// SS F2 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// SS F3 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// ZZ F1 locus
 0, 	// ZZ percent
 0, 	// ZZ transition duration
 0, 	// ZZ F2 locus
 0, 	// ZZ percent
 0, 	// ZZ transition duration
 0, 	// ZZ F3 locus
 0, 	// ZZ percent
 0, 	// ZZ transition duration
 0, 	// PP F1 locus
 0, 	// PP percent
 0, 	// PP transition duration
 0, 	// PP F2 locus
 0, 	// PP percent
 0, 	// PP transition duration
 0, 	// PP F3 locus
 0, 	// PP percent
 0, 	// PP transition duration
 0, 	// BB F1 locus
 0, 	// BB percent
 0, 	// BB transition duration
 0, 	// BB F2 locus
 0, 	// BB percent
 0, 	// BB transition duration
 0, 	// BB F3 locus
 0, 	// BB percent
 0, 	// BB transition duration
 0, 	// TT F1 locus
 0, 	// TT percent
 0, 	// TT transition duration
 0, 	// TT F2 locus
 0, 	// TT percent
 0, 	// TT transition duration
 0, 	// TT F3 locus
 0, 	// TT percent
 0, 	// TT transition duration
 0, 	// T2 F1 locus
 0, 	// T2 percent
 0, 	// T2 transition duration
 0, 	// T2 F2 locus
 0, 	// T2 percent
 0, 	// T2 transition duration
 0, 	// T2 F3 locus
 0, 	// T2 percent
 0, 	// T2 transition duration
 0, 	// DD F1 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// DD F2 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// DD F3 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// C F1 locus
 0, 	// C percent
 0, 	// C transition duration
 0, 	// C F2 locus
 0, 	// C percent
 0, 	// C transition duration
 0, 	// C F3 locus
 0, 	// C percent
 0, 	// C transition duration
 0, 	// KK F1 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// KK F2 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// KK F3 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// GG F1 locus
 0, 	// GG percent
 0, 	// GG transition duration
 0, 	// GG F2 locus
 0, 	// GG percent
 0, 	// GG transition duration
 0, 	// GG F3 locus
 0, 	// GG percent
 0, 	// GG transition duration
 0};

// Female Locus
const short hb_femloc_def[] = {
 0, 
// Front
 260, 	// M  F1 locus
 80, 	// M  percent
 40, 	// M  transition duration
 1200, 	// M  F2 locus
 10, 	// M  percent
 35, 	// M  transition duration
 2322, 	// M  F3 locus
 40, 	// M  percent
 40, 	// M  transition duration
 450, 	// N  F1 locus
 20, 	// N  percent
 35, 	// N  transition duration
 1350, 	// N  F2 locus
 75, 	// N  percent
 35, 	// N  transition duration
 2600, 	// N  F3 locus
 40, 	// N  percent
 45, 	// N  transition duration
 300, 	// F  F1 locus
 63, 	// F  percent
 30, 	// F  transition duration
 1, 	// F  F2 locus
 92, 	// F  percent
 35, 	// F  transition duration
 2080, 	// F  F3 locus
 35, 	// F  percent
 30, 	// F  transition duration
 300, 	// V  F1 locus
 50, 	// V  percent
 30, 	// V  transition duration
 1, 	// V  F2 locus
 92, 	// V  percent
 35, 	// V  transition duration
 2080, 	// V  F3 locus
 35, 	// V  percent
 40, 	// V  transition duration
 340, 	// TH F1 locus
 10, 	// TH percent
 45, 	// TH transition duration
 1500, 	// TH F2 locus
 20, 	// TH percent
 35, 	// TH transition duration
 2420, 	// TH F3 locus
 0, 	// TH percent
 50, 	// TH transition duration
 310, 	// S  F1 locus
 40, 	// S  percent
 40, 	// S  transition duration
 1440, 	// S  F2 locus
 40, 	// S  percent
 50, 	// S  transition duration
 2550, 	// S  F3 locus
 0, 	// S  percent
 70, 	// S  transition duration
 310, 	// Z  F1 locus
 40, 	// Z  percent
 40, 	// Z  transition duration
 1440, 	// Z  F2 locus
 35, 	// Z  percent
 50, 	// Z  transition duration
 2550, 	// Z  F3 locus
 0, 	// Z  percent
 70, 	// Z  transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1630, 	// SH F2 locus
 30, 	// SH percent
 70, 	// SH transition duration
 2640, 	// SH F3 locus
 51, 	// SH percent
 70, 	// SH transition duration
 350, 	// P  F1 locus
 55, 	// P  percent
 20, 	// P  transition duration
 950, 	// P  F2 locus
 56, 	// P  percent
 50, 	// P  transition duration
 2200, 	// P  F3 locus
 25, 	// P  percent
 50, 	// P  transition duration
 330, 	// B  F1 locus
 55, 	// B  percent
 20, 	// B  transition duration
 900, 	// B  F2 locus
 56, 	// B  percent
 30, 	// B  transition duration
 2200, 	// B  F3 locus
 25, 	// B  percent
 45, 	// B  transition duration
 320, 	// T  F1 locus
 43, 	// T  percent
 35, 	// T  transition duration
 1700, 	// T  F2 locus
 66, 	// T  percent
 35, 	// T  transition duration
 2650, 	// T  F3 locus
 30, 	// T  percent
 45, 	// T  transition duration
 250, 	// D  F1 locus
 43, 	// D  percent
 35, 	// D  transition duration
 1800, 	// D  F2 locus
 66, 	// D  percent
 35, 	// D  transition duration
 2650, 	// D  F3 locus
 30, 	// D  percent
 45, 	// D  transition duration
 280, 	// K  F1 locus
 33, 	// K  percent
 45, 	// K  transition duration
 1980, 	// K  F2 locus
 20, 	// K  percent
 55, 	// K  transition duration
 3000, 	// K  F3 locus
 117, 	// K  percent
 50, 	// K  transition duration
 250, 	// G  F1 locus
 33, 	// G  percent
 45, 	// G  transition duration
 2100, 	// G  F2 locus
 20, 	// G  percent
 50, 	// G  transition duration
 2100, 	// G  F3 locus
 50, 	// G  percent
 45, 	// G  transition duration
 240, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1750, 	// JH F2 locus
 25, 	// JH percent
 70, 	// JH transition duration
 2750, 	// JH F3 locus
 19, 	// JH percent
 70, 	// JH transition duration
 501, 	// TS F1 locus
 50, 	// TS percent
 70, 	// TS transition duration
 1500, 	// TS F2 locus
 20, 	// TS percent
 150, 	// TS transition duration
 2600, 	// TS F3 locus
 50, 	// TS percent
 50, 	// TS transition duration
 300, 	// CH F1 locus
 70, 	// CH percent
 20, 	// CH transition duration
 1610, 	// CH F2 locus
 70, 	// CH percent
 30, 	// CH transition duration
 2160, 	// CH F3 locus
 50, 	// CH percent
 60, 	// CH transition duration
 260, 	// MM F1 locus
 80, 	// MM percent
 40, 	// MM transition duration
 1200, 	// MM F2 locus
 10, 	// MM percent
 35, 	// MM transition duration
 2322, 	// MM F3 locus
 40, 	// MM percent
 40, 	// MM transition duration
 450, 	// NN F1 locus
 20, 	// NN percent
 35, 	// NN transition duration
 1350, 	// NN F2 locus
 75, 	// NN percent
 35, 	// NN transition duration
 2600, 	// NN F3 locus
 40, 	// NN percent
 45, 	// NN transition duration
 300, 	// VV F1 locus
 50, 	// VV percent
 30, 	// VV transition duration
 1, 	// VV F2 locus
 92, 	// VV percent
 35, 	// VV transition duration
 2080, 	// VV F3 locus
 35, 	// VV percent
 40, 	// VV transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1440, 	// SS F2 locus
 40, 	// SS percent
 50, 	// SS transition duration
 2550, 	// SS F3 locus
 0, 	// SS percent
 70, 	// SS transition duration
 310, 	// ZZ F1 locus
 40, 	// ZZ percent
 40, 	// ZZ transition duration
 1440, 	// ZZ F2 locus
 35, 	// ZZ percent
 50, 	// ZZ transition duration
 2550, 	// ZZ F3 locus
 0, 	// ZZ percent
 70, 	// ZZ transition duration
 350, 	// PP F1 locus
 55, 	// PP percent
 20, 	// PP transition duration
 950, 	// PP F2 locus
 56, 	// PP percent
 50, 	// PP transition duration
 2200, 	// PP F3 locus
 25, 	// PP percent
 50, 	// PP transition duration
 330, 	// BB F1 locus
 55, 	// BB percent
 20, 	// BB transition duration
 900, 	// BB F2 locus
 56, 	// BB percent
 30, 	// BB transition duration
 2200, 	// BB F3 locus
 25, 	// BB percent
 45, 	// BB transition duration
 320, 	// TT F1 locus
 43, 	// TT percent
 35, 	// TT transition duration
 1700, 	// TT F2 locus
 66, 	// TT percent
 35, 	// TT transition duration
 2650, 	// TT F3 locus
 30, 	// TT percent
 45, 	// TT transition duration
 320, 	// T2 F1 locus
 43, 	// T2 percent
 35, 	// T2 transition duration
 1700, 	// T2 F2 locus
 66, 	// T2 percent
 35, 	// T2 transition duration
 2650, 	// T2 F3 locus
 30, 	// T2 percent
 45, 	// T2 transition duration
 250, 	// DD F1 locus
 43, 	// DD percent
 35, 	// DD transition duration
 1800, 	// DD F2 locus
 66, 	// DD percent
 35, 	// DD transition duration
 2650, 	// DD F3 locus
 30, 	// DD percent
 45, 	// DD transition duration
 280, 	// C F1 locus
 33, 	// C percent
 45, 	// C transition duration
 1980, 	// C F2 locus
 20, 	// C percent
 55, 	// C transition duration
 3000, 	// C F3 locus
 117, 	// C percent
 50, 	// C transition duration
 280, 	// KK F1 locus
 33, 	// KK percent
 45, 	// KK transition duration
 1980, 	// KK F2 locus
 20, 	// KK percent
 55, 	// KK transition duration
 3000, 	// KK F3 locus
 117, 	// KK percent
 50, 	// KK transition duration
 250, 	// GG F1 locus
 33, 	// GG percent
 45, 	// GG transition duration
 2100, 	// GG F2 locus
 20, 	// GG percent
 50, 	// GG transition duration
 2100, 	// GG F3 locus
 50, 	// GG percent
 45, 	// GG transition duration
 300, 	// CZ F1 locus
 70, 	// CZ percent
 20, 	// CZ transition duration
 1869, 	// CZ F2 locus
 99, 	// CZ percent
 80, 	// CZ transition duration
 2569, 	// CZ F3 locus
 63, 	// CZ percent
 50, 	// CZ transition duration
 300, 	// KZ F1 locus
 70, 	// KZ percent
 20, 	// KZ transition duration
 1869, 	// KZ F2 locus
 99, 	// KZ percent
 80, 	// KZ transition duration
 2569, 	// KZ F3 locus
 63, 	// KZ percent
 50, 	// KZ transition duration
 501, 	// TZ F1 locus
 50, 	// TZ percent
 70, 	// TZ transition duration
 1500, 	// TZ F2 locus
 20, 	// TZ percent
 150, 	// TZ transition duration
 2600, 	// TZ F3 locus
 50, 	// TZ percent
 50, 	// TZ transition duration
// Back
 450, 	// M  F1 locus
 20, 	// M  percent
 30, 	// M  transition duration
 1, 	// M  F2 locus
 88, 	// M  percent
 40, 	// M  transition duration
 2000, 	// M  F3 locus
 80, 	// M  percent
 25, 	// M  transition duration
 450, 	// N  F1 locus
 20, 	// N  percent
 30, 	// N  transition duration
 1520, 	// N  F2 locus
 25, 	// N  percent
 75, 	// N  transition duration
 2600, 	// N  F3 locus
 0, 	// N  percent
 60, 	// N  transition duration
 320, 	// F  F1 locus
 60, 	// F  percent
 30, 	// F  transition duration
 1, 	// F  F2 locus
 91, 	// F  percent
 35, 	// F  transition duration
 2100, 	// F  F3 locus
 65, 	// F  percent
 40, 	// F  transition duration
 300, 	// V  F1 locus
 50, 	// V  percent
 30, 	// V  transition duration
 1, 	// V  F2 locus
 91, 	// V  percent
 40, 	// V  transition duration
 2100, 	// V  F3 locus
 65, 	// V  percent
 40, 	// V  transition duration
 350, 	// TH F1 locus
 10, 	// TH percent
 50, 	// TH transition duration
 1300, 	// TH F2 locus
 12, 	// TH percent
 55, 	// TH transition duration
 2500, 	// TH F3 locus
 11, 	// TH percent
 55, 	// TH transition duration
 310, 	// S  F1 locus
 40, 	// S  percent
 40, 	// S  transition duration
 1440, 	// S  F2 locus
 40, 	// S  percent
 50, 	// S  transition duration
 2530, 	// S  F3 locus
 0, 	// S  percent
 70, 	// S  transition duration
 310, 	// Z  F1 locus
 40, 	// Z  percent
 40, 	// Z  transition duration
 1440, 	// Z  F2 locus
 35, 	// Z  percent
 60, 	// Z  transition duration
 2630, 	// Z  F3 locus
 0, 	// Z  percent
 70, 	// Z  transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1600, 	// SH F2 locus
 27, 	// SH percent
 70, 	// SH transition duration
 2270, 	// SH F3 locus
 0, 	// SH percent
 85, 	// SH transition duration
 350, 	// P  F1 locus
 45, 	// P  percent
 25, 	// P  transition duration
 920, 	// P  F2 locus
 46, 	// P  percent
 50, 	// P  transition duration
 1900, 	// P  F3 locus
 40, 	// P  percent
 50, 	// P  transition duration
 330, 	// B  F1 locus
 45, 	// B  percent
 25, 	// B  transition duration
 920, 	// B  F2 locus
 46, 	// B  percent
 30, 	// B  transition duration
 2250, 	// B  F3 locus
 40, 	// B  percent
 50, 	// B  transition duration
 320, 	// T  F1 locus
 43, 	// T  percent
 50, 	// T  transition duration
 1700, 	// T  F2 locus
 10, 	// T  percent
 75, 	// T  transition duration
 2600, 	// T  F3 locus
 10, 	// T  percent
 50, 	// T  transition duration
 250, 	// D  F1 locus
 43, 	// D  percent
 50, 	// D  transition duration
 1700, 	// D  F2 locus
 40, 	// D  percent
 75, 	// D  transition duration
 2600, 	// D  F3 locus
 0, 	// D  percent
 50, 	// D  transition duration
 280, 	// K  F1 locus
 33, 	// K  percent
 50, 	// K  transition duration
 1800, 	// K  F2 locus
 16, 	// K  percent
 50, 	// K  transition duration
 2000, 	// K  F3 locus
 20, 	// K  percent
 90, 	// K  transition duration
 250, 	// G  F1 locus
 33, 	// G  percent
 50, 	// G  transition duration
 1800, 	// G  F2 locus
 16, 	// G  percent
 60, 	// G  transition duration
 2100, 	// G  F3 locus
 0, 	// G  percent
 90, 	// G  transition duration
 245, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1680, 	// JH F2 locus
 5, 	// JH percent
 120, 	// JH transition duration
 2450, 	// JH F3 locus
 10, 	// JH percent
 70, 	// JH transition duration
 290, 	// TS F1 locus
 70, 	// TS percent
 35, 	// TS transition duration
 1500, 	// TS F2 locus
 20, 	// TS percent
 80, 	// TS transition duration
 2600, 	// TS F3 locus
 50, 	// TS percent
 30, 	// TS transition duration
 300, 	// CH F1 locus
 70, 	// CH percent
 30, 	// CH transition duration
 1711, 	// CH F2 locus
 70, 	// CH percent
 30, 	// CH transition duration
 2150, 	// CH F3 locus
 50, 	// CH percent
 60, 	// CH transition duration
 450, 	// MM F1 locus
 20, 	// MM percent
 30, 	// MM transition duration
 1, 	// MM F2 locus
 88, 	// MM percent
 40, 	// MM transition duration
 2000, 	// MM F3 locus
 80, 	// MM percent
 25, 	// MM transition duration
 450, 	// NN F1 locus
 20, 	// NN percent
 30, 	// NN transition duration
 1520, 	// NN F2 locus
 25, 	// NN percent
 75, 	// NN transition duration
 2600, 	// NN F3 locus
 0, 	// NN percent
 60, 	// NN transition duration
 300, 	// VV F1 locus
 50, 	// VV percent
 30, 	// VV transition duration
 1, 	// VV F2 locus
 91, 	// VV percent
 40, 	// VV transition duration
 2100, 	// VV F3 locus
 65, 	// VV percent
 40, 	// VV transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1440, 	// SS F2 locus
 40, 	// SS percent
 50, 	// SS transition duration
 2530, 	// SS F3 locus
 0, 	// SS percent
 70, 	// SS transition duration
 310, 	// ZZ F1 locus
 40, 	// ZZ percent
 40, 	// ZZ transition duration
 1440, 	// ZZ F2 locus
 35, 	// ZZ percent
 60, 	// ZZ transition duration
 2630, 	// ZZ F3 locus
 0, 	// ZZ percent
 70, 	// ZZ transition duration
 350, 	// PP F1 locus
 45, 	// PP percent
 25, 	// PP transition duration
 920, 	// PP F2 locus
 46, 	// PP percent
 50, 	// PP transition duration
 1900, 	// PP F3 locus
 40, 	// PP percent
 50, 	// PP transition duration
 330, 	// BB F1 locus
 45, 	// BB percent
 25, 	// BB transition duration
 920, 	// BB F2 locus
 46, 	// BB percent
 30, 	// BB transition duration
 2250, 	// BB F3 locus
 40, 	// BB percent
 50, 	// BB transition duration
 320, 	// TT F1 locus
 43, 	// TT percent
 50, 	// TT transition duration
 1700, 	// TT F2 locus
 10, 	// TT percent
 75, 	// TT transition duration
 2600, 	// TT F3 locus
 10, 	// TT percent
 50, 	// TT transition duration
 320, 	// T2 F1 locus
 43, 	// T2 percent
 50, 	// T2 transition duration
 1700, 	// T2 F2 locus
 10, 	// T2 percent
 75, 	// T2 transition duration
 2600, 	// T2 F3 locus
 10, 	// T2 percent
 50, 	// T2 transition duration
 250, 	// DD F1 locus
 43, 	// DD percent
 50, 	// DD transition duration
 1700, 	// DD F2 locus
 40, 	// DD percent
 75, 	// DD transition duration
 2600, 	// DD F3 locus
 0, 	// DD percent
 50, 	// DD transition duration
 280, 	// C F1 locus
 33, 	// C percent
 50, 	// C transition duration
 1800, 	// C F2 locus
 16, 	// C percent
 50, 	// C transition duration
 2000, 	// C F3 locus
 20, 	// C percent
 90, 	// C transition duration
 280, 	// KK F1 locus
 33, 	// KK percent
 50, 	// KK transition duration
 1800, 	// KK F2 locus
 16, 	// KK percent
 50, 	// KK transition duration
 2000, 	// KK F3 locus
 20, 	// KK percent
 90, 	// KK transition duration
 250, 	// GG F1 locus
 33, 	// GG percent
 50, 	// GG transition duration
 1800, 	// GG F2 locus
 16, 	// GG percent
 60, 	// GG transition duration
 2100, 	// GG F3 locus
 0, 	// GG percent
 90, 	// GG transition duration
 300, 	// CZ F1 locus
 70, 	// CZ percent
 30, 	// CZ transition duration
 1711, 	// CZ F2 locus
 70, 	// CZ percent
 30, 	// CZ transition duration
 2150, 	// CZ F3 locus
 50, 	// CZ percent
 60, 	// CZ transition duration
 300, 	// KZ F1 locus
 70, 	// KZ percent
 30, 	// KZ transition duration
 1711, 	// KZ F2 locus
 70, 	// KZ percent
 30, 	// KZ transition duration
 2150, 	// KZ F3 locus
 50, 	// KZ percent
 60, 	// KZ transition duration
 290, 	// TZ F1 locus
 70, 	// TZ percent
 35, 	// TZ transition duration
 1500, 	// TZ F2 locus
 20, 	// TZ percent
 80, 	// TZ transition duration
 2600, 	// TZ F3 locus
 50, 	// TZ percent
 30, 	// TZ transition duration
// Round
 450, 	// M  F1 locus
 20, 	// M  percent
 30, 	// M  transition duration
 970, 	// M  F2 locus
 10, 	// M  percent
 40, 	// M  transition duration
 1550, 	// M  F3 locus
 80, 	// M  percent
 25, 	// M  transition duration
 450, 	// N  F1 locus
 20, 	// N  percent
 30, 	// N  transition duration
 1500, 	// N  F2 locus
 30, 	// N  percent
 80, 	// N  transition duration
 2520, 	// N  F3 locus
 0, 	// N  percent
 95, 	// N  transition duration
 320, 	// F  F1 locus
 60, 	// F  percent
 30, 	// F  transition duration
 1, 	// F  F2 locus
 91, 	// F  percent
 35, 	// F  transition duration
 2100, 	// F  F3 locus
 65, 	// F  percent
 40, 	// F  transition duration
 325, 	// V  F1 locus
 50, 	// V  percent
 30, 	// V  transition duration
 1, 	// V  F2 locus
 91, 	// V  percent
 40, 	// V  transition duration
 2100, 	// V  F3 locus
 65, 	// V  percent
 40, 	// V  transition duration
 350, 	// TH F1 locus
 10, 	// TH percent
 50, 	// TH transition duration
 1300, 	// TH F2 locus
 12, 	// TH percent
 55, 	// TH transition duration
 2500, 	// TH F3 locus
 11, 	// TH percent
 55, 	// TH transition duration
 310, 	// S  F1 locus
 40, 	// S  percent
 40, 	// S  transition duration
 1320, 	// S  F2 locus
 15, 	// S  percent
 60, 	// S  transition duration
 2460, 	// S  F3 locus
 0, 	// S  percent
 65, 	// S  transition duration
 310, 	// Z  F1 locus
 40, 	// Z  percent
 40, 	// Z  transition duration
 1520, 	// Z  F2 locus
 15, 	// Z  percent
 60, 	// Z  transition duration
 2460, 	// Z  F3 locus
 0, 	// Z  percent
 65, 	// Z  transition duration
 340, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1630, 	// SH F2 locus
 27, 	// SH percent
 90, 	// SH transition duration
 2100, 	// SH F3 locus
 20, 	// SH percent
 110, 	// SH transition duration
 320, 	// P  F1 locus
 45, 	// P  percent
 25, 	// P  transition duration
 920, 	// P  F2 locus
 46, 	// P  percent
 50, 	// P  transition duration
 1900, 	// P  F3 locus
 40, 	// P  percent
 50, 	// P  transition duration
 330, 	// B  F1 locus
 45, 	// B  percent
 25, 	// B  transition duration
 720, 	// B  F2 locus
 36, 	// B  percent
 50, 	// B  transition duration
 1800, 	// B  F3 locus
 40, 	// B  percent
 40, 	// B  transition duration
 320, 	// T  F1 locus
 43, 	// T  percent
 40, 	// T  transition duration
 1700, 	// T  F2 locus
 5, 	// T  percent
 95, 	// T  transition duration
 2300, 	// T  F3 locus
 0, 	// T  percent
 95, 	// T  transition duration
 250, 	// D  F1 locus
 43, 	// D  percent
 40, 	// D  transition duration
 1700, 	// D  F2 locus
 40, 	// D  percent
 95, 	// D  transition duration
 2601, 	// D  F3 locus
 30, 	// D  percent
 85, 	// D  transition duration
 280, 	// K  F1 locus
 33, 	// K  percent
 40, 	// K  transition duration
 1400, 	// K  F2 locus
 60, 	// K  percent
 75, 	// K  transition duration
 2050, 	// K  F3 locus
 15, 	// K  percent
 80, 	// K  transition duration
 250, 	// G  F1 locus
 45, 	// G  percent
 40, 	// G  transition duration
 1600, 	// G  F2 locus
 42, 	// G  percent
 65, 	// G  transition duration
 1920, 	// G  F3 locus
 15, 	// G  percent
 80, 	// G  transition duration
 245, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1680, 	// JH F2 locus
 10, 	// JH percent
 90, 	// JH transition duration
 1970, 	// JH F3 locus
 10, 	// JH percent
 100, 	// JH transition duration
 501, 	// TS F1 locus
 50, 	// TS percent
 40, 	// TS transition duration
 1600, 	// TS F2 locus
 20, 	// TS percent
 90, 	// TS transition duration
 2600, 	// TS F3 locus
 50, 	// TS percent
 40, 	// TS transition duration
 300, 	// CH F1 locus
 70, 	// CH percent
 30, 	// CH transition duration
 1610, 	// CH F2 locus
 70, 	// CH percent
 36, 	// CH transition duration
 2160, 	// CH F3 locus
 50, 	// CH percent
 60, 	// CH transition duration
 450, 	// MM F1 locus
 20, 	// MM percent
 30, 	// MM transition duration
 970, 	// MM F2 locus
 10, 	// MM percent
 40, 	// MM transition duration
 1550, 	// MM F3 locus
 80, 	// MM percent
 25, 	// MM transition duration
 450, 	// NN F1 locus
 20, 	// NN percent
 30, 	// NN transition duration
 1500, 	// NN F2 locus
 30, 	// NN percent
 80, 	// NN transition duration
 2520, 	// NN F3 locus
 0, 	// NN percent
 95, 	// NN transition duration
 325, 	// VV F1 locus
 50, 	// VV percent
 30, 	// VV transition duration
 1, 	// VV F2 locus
 91, 	// VV percent
 40, 	// VV transition duration
 2100, 	// VV F3 locus
 65, 	// VV percent
 40, 	// VV transition duration
 310, 	// SS F1 locus
 40, 	// SS percent
 40, 	// SS transition duration
 1320, 	// SS F2 locus
 15, 	// SS percent
 60, 	// SS transition duration
 2460, 	// SS F3 locus
 0, 	// SS percent
 65, 	// SS transition duration
 310, 	// ZZ F1 locus
 40, 	// ZZ percent
 40, 	// ZZ transition duration
 1520, 	// ZZ F2 locus
 15, 	// ZZ percent
 60, 	// ZZ transition duration
 2460, 	// ZZ F3 locus
 0, 	// ZZ percent
 65, 	// ZZ transition duration
 320, 	// PP F1 locus
 45, 	// PP percent
 25, 	// PP transition duration
 920, 	// PP F2 locus
 46, 	// PP percent
 50, 	// PP transition duration
 1900, 	// PP F3 locus
 40, 	// PP percent
 50, 	// PP transition duration
 330, 	// BB F1 locus
 45, 	// BB percent
 25, 	// BB transition duration
 720, 	// BB F2 locus
 36, 	// BB percent
 50, 	// BB transition duration
 1800, 	// BB F3 locus
 40, 	// BB percent
 40, 	// BB transition duration
 320, 	// TT F1 locus
 43, 	// TT percent
 40, 	// TT transition duration
 1700, 	// TT F2 locus
 5, 	// TT percent
 95, 	// TT transition duration
 2300, 	// TT F3 locus
 0, 	// TT percent
 95, 	// TT transition duration
 320, 	// T2 F1 locus
 43, 	// T2 percent
 40, 	// T2 transition duration
 1700, 	// T2 F2 locus
 5, 	// T2 percent
 95, 	// T2 transition duration
 2300, 	// T2 F3 locus
 0, 	// T2 percent
 95, 	// T2 transition duration
 250, 	// DD F1 locus
 43, 	// DD percent
 40, 	// DD transition duration
 1700, 	// DD F2 locus
 40, 	// DD percent
 95, 	// DD transition duration
 2601, 	// DD F3 locus
 30, 	// DD percent
 85, 	// DD transition duration
 280, 	// C F1 locus
 33, 	// C percent
 40, 	// C transition duration
 1400, 	// C F2 locus
 60, 	// C percent
 75, 	// C transition duration
 2050, 	// C F3 locus
 15, 	// C percent
 80, 	// C transition duration
 280, 	// KK F1 locus
 33, 	// KK percent
 40, 	// KK transition duration
 1400, 	// KK F2 locus
 60, 	// KK percent
 75, 	// KK transition duration
 2050, 	// KK F3 locus
 15, 	// KK percent
 80, 	// KK transition duration
 250, 	// GG F1 locus
 45, 	// GG percent
 40, 	// GG transition duration
 1600, 	// GG F2 locus
 42, 	// GG percent
 65, 	// GG transition duration
 1920, 	// GG F3 locus
 15, 	// GG percent
 80, 	// GG transition duration
 300, 	// CZ F1 locus
 70, 	// CZ percent
 30, 	// CZ transition duration
 1610, 	// CZ F2 locus
 70, 	// CZ percent
 36, 	// CZ transition duration
 2160, 	// CZ F3 locus
 50, 	// CZ percent
 60, 	// CZ transition duration
 300, 	// KZ F1 locus
 70, 	// KZ percent
 30, 	// KZ transition duration
 1610, 	// KZ F2 locus
 70, 	// KZ percent
 36, 	// KZ transition duration
 2160, 	// KZ F3 locus
 50, 	// KZ percent
 60, 	// KZ transition duration
 501, 	// TZ F1 locus
 50, 	// TZ percent
 40, 	// TZ transition duration
 1600, 	// TZ F2 locus
 20, 	// TZ percent
 90, 	// TZ transition duration
 2600, 	// TZ F3 locus
 50, 	// TZ percent
 40, 	// TZ transition duration
// Low
 0, 	// M  F1 locus
 0, 	// M  percent
 0, 	// M  transition duration
 0, 	// M  F2 locus
 0, 	// M  percent
 0, 	// M  transition duration
 0, 	// M  F3 locus
 0, 	// M  percent
 0, 	// M  transition duration
 0, 	// N  F1 locus
 0, 	// N  percent
 0, 	// N  transition duration
 0, 	// N  F2 locus
 0, 	// N  percent
 0, 	// N  transition duration
 0, 	// N  F3 locus
 0, 	// N  percent
 0, 	// N  transition duration
 0, 	// F  F1 locus
 0, 	// F  percent
 0, 	// F  transition duration
 0, 	// F  F2 locus
 0, 	// F  percent
 0, 	// F  transition duration
 0, 	// F  F3 locus
 0, 	// F  percent
 0, 	// F  transition duration
 0, 	// V  F1 locus
 0, 	// V  percent
 0, 	// V  transition duration
 0, 	// V  F2 locus
 0, 	// V  percent
 0, 	// V  transition duration
 0, 	// V  F3 locus
 0, 	// V  percent
 0, 	// V  transition duration
 0, 	// TH F1 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F2 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F3 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// S  F1 locus
 0, 	// S  percent
 0, 	// S  transition duration
 0, 	// S  F2 locus
 0, 	// S  percent
 0, 	// S  transition duration
 0, 	// S  F3 locus
 0, 	// S  percent
 0, 	// S  transition duration
 0, 	// Z  F1 locus
 0, 	// Z  percent
 0, 	// Z  transition duration
 0, 	// Z  F2 locus
 0, 	// Z  percent
 0, 	// Z  transition duration
 0, 	// Z  F3 locus
 0, 	// Z  percent
 0, 	// Z  transition duration
 0, 	// SH F1 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// SH F2 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// SH F3 locus
 0, 	// SH percent
 0, 	// SH transition duration
 0, 	// P  F1 locus
 0, 	// P  percent
 0, 	// P  transition duration
 0, 	// P  F2 locus
 0, 	// P  percent
 0, 	// P  transition duration
 0, 	// P  F3 locus
 0, 	// P  percent
 0, 	// P  transition duration
 0, 	// B  F1 locus
 0, 	// B  percent
 0, 	// B  transition duration
 0, 	// B  F2 locus
 0, 	// B  percent
 0, 	// B  transition duration
 0, 	// B  F3 locus
 0, 	// B  percent
 0, 	// B  transition duration
 0, 	// T  F1 locus
 0, 	// T  percent
 0, 	// T  transition duration
 0, 	// T  F2 locus
 0, 	// T  percent
 0, 	// T  transition duration
 0, 	// T  F3 locus
 0, 	// T  percent
 0, 	// T  transition duration
 0, 	// D  F1 locus
 0, 	// D  percent
 0, 	// D  transition duration
 0, 	// D  F2 locus
 0, 	// D  percent
 0, 	// D  transition duration
 0, 	// D  F3 locus
 0, 	// D  percent
 0, 	// D  transition duration
 0, 	// K  F1 locus
 0, 	// K  percent
 0, 	// K  transition duration
 0, 	// K  F2 locus
 0, 	// K  percent
 0, 	// K  transition duration
 0, 	// K  F3 locus
 0, 	// K  percent
 0, 	// K  transition duration
 0, 	// G  F1 locus
 0, 	// G  percent
 0, 	// G  transition duration
 0, 	// G  F2 locus
 0, 	// G  percent
 0, 	// G  transition duration
 0, 	// G  F3 locus
 0, 	// G  percent
 0, 	// G  transition duration
 0, 	// JH F1 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F2 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F3 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// MM F1 locus
 0, 	// MM percent
 0, 	// MM transition duration
 0, 	// MM F2 locus
 0, 	// MM percent
 0, 	// MM transition duration
 0, 	// MM F3 locus
 0, 	// MM percent
 0, 	// MM transition duration
 0, 	// NN F1 locus
 0, 	// NN percent
 0, 	// NN transition duration
 0, 	// NN F2 locus
 0, 	// NN percent
 0, 	// NN transition duration
 0, 	// NN F3 locus
 0, 	// NN percent
 0, 	// NN transition duration
 0, 	// VV F1 locus
 0, 	// VV percent
 0, 	// VV transition duration
 0, 	// VV F2 locus
 0, 	// VV percent
 0, 	// VV transition duration
 0, 	// VV F3 locus
 0, 	// VV percent
 0, 	// VV transition duration
 0, 	// SS F1 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// SS F2 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// SS F3 locus
 0, 	// SS percent
 0, 	// SS transition duration
 0, 	// ZZ F1 locus
 0, 	// ZZ percent
 0, 	// ZZ transition duration
 0, 	// ZZ F2 locus
 0, 	// ZZ percent
 0, 	// ZZ transition duration
 0, 	// ZZ F3 locus
 0, 	// ZZ percent
 0, 	// ZZ transition duration
 0, 	// PP F1 locus
 0, 	// PP percent
 0, 	// PP transition duration
 0, 	// PP F2 locus
 0, 	// PP percent
 0, 	// PP transition duration
 0, 	// PP F3 locus
 0, 	// PP percent
 0, 	// PP transition duration
 0, 	// BB F1 locus
 0, 	// BB percent
 0, 	// BB transition duration
 0, 	// BB F2 locus
 0, 	// BB percent
 0, 	// BB transition duration
 0, 	// BB F3 locus
 0, 	// BB percent
 0, 	// BB transition duration
 0, 	// TT F1 locus
 0, 	// TT percent
 0, 	// TT transition duration
 0, 	// TT F2 locus
 0, 	// TT percent
 0, 	// TT transition duration
 0, 	// TT F3 locus
 0, 	// TT percent
 0, 	// TT transition duration
 0, 	// T2 F1 locus
 0, 	// T2 percent
 0, 	// T2 transition duration
 0, 	// T2 F2 locus
 0, 	// T2 percent
 0, 	// T2 transition duration
 0, 	// T2 F3 locus
 0, 	// T2 percent
 0, 	// T2 transition duration
 0, 	// DD F1 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// DD F2 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// DD F3 locus
 0, 	// DD percent
 0, 	// DD transition duration
 0, 	// C F1 locus
 0, 	// C percent
 0, 	// C transition duration
 0, 	// C F2 locus
 0, 	// C percent
 0, 	// C transition duration
 0, 	// C F3 locus
 0, 	// C percent
 0, 	// C transition duration
 0, 	// KK F1 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// KK F2 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// KK F3 locus
 0, 	// KK percent
 0, 	// KK transition duration
 0, 	// GG F1 locus
 0, 	// GG percent
 0, 	// GG transition duration
 0, 	// GG F2 locus
 0, 	// GG percent
 0, 	// GG transition duration
 0, 	// GG F3 locus
 0, 	// GG percent
 0, 	// GG transition duration
 0};

const struct rom_data_s hb_rom_data_def = {
hb_inhdr_def,
hb_mindur_def,
hb_burdr_def,
hb_begtyp_def,
hb_endtyp_def,
hb_place_def,
hb_featb_def,
hb_maltar_def,
hb_femtar_def,
hb_maldip_def,
hb_femdip_def,
hb_ptram_def,
hb_plocu_def,
hb_maleloc_def,
hb_femloc_def
};


