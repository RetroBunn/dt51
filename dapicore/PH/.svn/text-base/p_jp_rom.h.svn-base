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

#define JP_PH_PHONEME_COUNT 41
#define JP_PH_PHONEME_NAMES " _ I E A O U YE YA YO YU WI WE WA WO H M N NG EM EN NV BH F DH S Z CX SH ZH GH R P B T D K G TS DZ CH JH "

// Inherent Duration (milliseconds)
const short jp_inhdr_def[] = {
 305, 	// _
 105, 	// I
 180, 	// E
 135, 	// A
 130, 	// O
 110, 	// U
 200, 	// YE
 190, 	// YA
 250, 	// YO
 250, 	// YU
 180, 	// WI
 180, 	// WE
 160, 	// WA
 170, 	// WO
 95, 	// H
 80, 	// M
 85, 	// N
 120, 	// NG
 120, 	// EM
 130, 	// EN
 120, 	// NV
 80, 	// BH
 90, 	// F
 80, 	// DH
 100, 	// S
 80, 	// Z
 120, 	// CX
 108, 	// SH
 80, 	// ZH
 80, 	// GH
 47, 	// R
 125, 	// P
 65, 	// B
 110, 	// T
 65, 	// D
 70, 	// K
 70, 	// G
 145, 	// TS
 80, 	// DZ
 145, 	// CH
 80 }; 	//JH

// Minimum Duration (milliseconds)
const short jp_mindur_def[] = {
 200, 	// _
 48, 	// I
 100, 	// E
 52, 	// A
 60, 	// O
 60, 	// U
 80, 	// YE
 80, 	// YA
 80, 	// YO
 80, 	// YU
 80, 	// WI
 80, 	// WE
 80, 	// WA
 80, 	// WO
 54, 	// H
 34, 	// M
 50, 	// N
 50, 	// NG
 50, 	// EM
 95, 	// EN
 50, 	// NV
 50, 	// BH
 60, 	// F
 50, 	// DH
 52, 	// S
 36, 	// Z
 60, 	// CX
 64, 	// SH
 50, 	// ZH
 50, 	// GH
 40, 	// R
 50, 	// P
 45, 	// B
 53, 	// T
 45, 	// D
 56, 	// K
 30, 	// G
 83, 	// TS
 60, 	// DZ
 83, 	// CH
 60 };	//JH

// Burst Duration (milliseconds)
const short jp_burdr_def[] = {
 0, 	//_
 0, 	//I
 0, 	//E
 0, 	//A
 0, 	//O
 0, 	//U
 0, 	//YE
 0, 	//YA
 0, 	//YO
 0, 	//YU
 0, 	//WI
 0, 	//WE
 0, 	//WA
 0, 	//WO
 0, 	//H
 0, 	//M
 0, 	//N
 0, 	//NG
 0, 	//EM
 0, 	//EN
 0, 	//NV
 0, 	//BH
 0, 	//F
 0, 	//DH
 0, 	//S
 0, 	//Z
 0, 	//CX
 0, 	//SH
 0, 	//ZH
 0, 	//GH
 0, 	//R
 7, 	//P
 7, 	//B
 7, 	//T
 7, 	//D
 7, 	//K
 13, 	//G
 58, 	//TS
 39, 	//DZ
 58, 	//CH
 39 };	//JH

// Beginning Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short jp_begtyp_def[] = {
 4, 	// _
 1, 	// I
 1, 	// E
 2, 	// A
 3, 	// O
 2, 	// U
 1, 	// YE
 1, 	// YA
 1, 	// YO
 1, 	// YU
 3, 	// WI
 3, 	// WE
 3, 	// WA
 3, 	// WO
 4, 	// H
 4, 	// M
 4, 	// N
 4, 	// NG
 4, 	// EM
 4, 	// EN
 1, 	// NV
 4, 	// BH
 4, 	// F
 4, 	// DH
 4, 	// S
 4, 	// Z
 4, 	// CX
 4, 	// SH
 4, 	// ZH
 4, 	// GH
 4, 	// R
 4, 	// P
 4, 	// B
 4, 	// T
 4, 	// D
 4, 	// K
 4, 	// G
 4, 	// TS
 4, 	// DZ
 4, 	// CH
 4 };	// JH

// Ending Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short jp_endtyp_def[] = {
 4, 	// _
 1, 	// I
 1, 	// E
 2, 	// A
 3, 	// O
 2, 	// U
 1, 	// YE
 2, 	// YA
 3, 	// YO
 2, 	// YU
 1, 	// WI
 1, 	// WE
 2, 	// WA
 3, 	// WO
 4, 	// H
 4, 	// M
 4, 	// N
 4, 	// NG
 4, 	// EM
 4, 	// EN
 1, 	// NV
 4, 	// BH
 4, 	// F
 4, 	// DH
 4, 	// S
 4, 	// Z
 4, 	// CX
 4, 	// SH
 4, 	// ZH
 4, 	// GH
 4, 	// R
 4, 	// P
 4, 	// B
 4, 	// T
 4, 	// D
 4, 	// K
 4, 	// G
 4, 	// TS
 4, 	// DZ
 4, 	// CH
 4 };	// JH

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
const short jp_place_def[] = {
 0x0000, 	// _
 0x0000, 	// I
 0x0000, 	// E
 0x0000, 	// A
 0x0000, 	// O
 0x0000, 	// U
 0x0000, 	// YE
 0x0000, 	// YA
 0x0000, 	// YO
 0x0000, 	// YU
 0x0000, 	// WI
 0x0000, 	// WE
 0x0000, 	// WA
 0x0000, 	// WO
 0x0000, 	// H
 0x0001, 	// M
 0x0008, 	// N
 0x0010, 	// NG
 0x0001, 	// EM
 0x0008, 	// EN
 0x0000, 	// NV
 0x0001, 	// BH
 0x0001, 	// F
 0x0002, 	// DH
 0x0008, 	// S
 0x0008, 	// Z
 0x0004, 	// CX
 0x000c, 	// SH
 0x0004, 	// ZH
 0x0010, 	// GH
 0x0008, 	// R
 0x0001, 	// P
 0x0001, 	// B
 0x000c, 	// T
 0x0008, 	// D
 0x0010, 	// K
 0x0010, 	// G
 0x0008, 	// TS
 0x0008, 	// DZ
 0x000c, 	// CH
 0x000c };	// JH

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
const int jp_featb_def[] = {
 0x00000010, 	// _
 0x0000001f, 	// I
 0x0000001f, 	// E
 0x0000001f, 	// A
 0x0000001f, 	// O
 0x0000001f, 	// U
 0x0000041f, 	// YE
 0x0000041f, 	// YA
 0x0000041f, 	// YO
 0x0000041f, 	// YU
 0x0000041f, 	// WI
 0x0000041f, 	// WE
 0x0000041f, 	// WA
 0x0000041f, 	// WO
 0x00000110, 	// H
 0x0000259a, 	// M
 0x0000259a, 	// N
 0x0000249a, 	// NG
 0x0000049b, 	// EM
 0x0000249b, 	// EN
 0x0000009f, 	// NV
 0x00000122, 	// BH
 0x00000120, 	// F
 0x00000122, 	// DH
 0x00000120, 	// S
 0x00000122, 	// Z
 0x00000120, 	// CX
 0x00000120, 	// SH
 0x00000122, 	// ZH
 0x00000122, 	// GH
 0x0000231a, 	// R
 0x00002960, 	// P
 0x00002962, 	// B
 0x00002960, 	// T
 0x00002962, 	// D
 0x00002960, 	// K
 0x00002962, 	// G
 0x00002920, 	// TS
 0x00000122, 	// DZ
 0x00002920, 	// CH
 0x00002922, 	// JH
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
const short jp_maltar_def[] = {
// ==== F1 ====
 -1, 	// _
 320, 	// I
 472, 	// E
 800, 	// A
 600, 	// O
 325, 	// U
 -2, 	// YE
 -8, 	// YA
 -14, 	// YO
 -20, 	// YU
 -26, 	// WI
 -32, 	// WE
 -38, 	// WA
 -44, 	// WO
 -1, 	// H
 420, 	// M
 300, 	// N
 420, 	// NG
 420, 	// EM
 300, 	// EN
 -1, 	// NV
 280, 	// BH
 340, 	// F
 280, 	// DH
 320, 	// S
 250, 	// Z
 300, 	// CX
 300, 	// SH
 300, 	// ZH
 290, 	// GH
 -50, 	// R
 350, 	// P
 250, 	// B
 350, 	// T
 250, 	// D
 350, 	// K
 250, 	// G
 350, 	// TS
 250, 	// DZ
 350, 	// CH
 260, 	// JH
// ==== F2 ====
 -1, 	// _
 2340, 	// I
 2125, 	// E
 1430, 	// A
 930, 	// O
 1422, 	// U
 -54, 	// YE
 -60, 	// YA
 -66, 	// YO
 -72, 	// YU
 -78, 	// WI
 -84, 	// WE
 -90, 	// WA
 -96, 	// WO
 -1, 	// H
 1270, 	// M
 1500, 	// N
 1600, 	// NG
 1270, 	// EM
 1500, 	// EN
 -1, 	// NV
 1200, 	// BH
 1300, 	// F
 1600, 	// DH
 1420, 	// S
 1420, 	// Z
 1800, 	// CX
 1650, 	// SH
 1650, 	// ZH
 1650, 	// GH
 1600, 	// R
 1100, 	// P
 1100, 	// B
 1600, 	// T
 1600, 	// D
 1800, 	// K
 2100, 	// G
 1600, 	// TS
 1600, 	// DZ
 1750, 	// CH
 1730, 	// JH
// ==== F3 ====
 -1, 	// _
 3140, 	// I
 2686, 	// E
 2690, 	// A
 2640, 	// O
 2550, 	// U
 -102, 	// YE
 -108, 	// YA
 -114, 	// YO
 -120, 	// YU
 -126, 	// WI
 -132, 	// WE
 -138, 	// WA
 -144, 	// WO
 -1, 	// H
 2500, 	// M
 3000, 	// N
 2400, 	// NG
 2130, 	// EM
 3000, 	// EN
 -1, 	// NV
 2100, 	// BH
 2100, 	// F
 2600, 	// DH
 2550, 	// S
 2600, 	// Z
 2400, 	// CX
 2550, 	// SH
 2550, 	// ZH
 2200, 	// GH
 2600, 	// R
 2150, 	// P
 2150, 	// B
 2600, 	// T
 2600, 	// D
 2700, 	// K
 2500, 	// G
 2600, 	// TS
 2600, 	// DZ
 3020, 	// CH
 2700, 	// JH
// ==== B1 ====
 500, 	// _
 60, 	// I
 100, 	// E
 140, 	// A
 70, 	// O
 65, 	// U
 65, 	// YE
 -150, 	// YA
 65, 	// YO
 65, 	// YU
 50, 	// WI
 50, 	// WE
 -156, 	// WA
 50, 	// WO
 400, 	// H
 150, 	// M
 150, 	// N
 150, 	// NG
 150, 	// EM
 110, 	// EN
 -1, 	// NV
 140, 	// BH
 300, 	// F
 140, 	// DH
 300, 	// S
 140, 	// Z
 300, 	// CX
 300, 	// SH
 140, 	// ZH
 140, 	// GH
 90, 	// R
 300, 	// P
 150, 	// B
 300, 	// T
 150, 	// D
 300, 	// K
 150, 	// G
 300, 	// TS
 150, 	// DZ
 300, 	// CH
 70, 	// JH
// ==== B2 ====
 500, 	// _
 160, 	// I
 80, 	// E
 120, 	// A
 70, 	// O
 90, 	// U
 140, 	// YE
 140, 	// YA
 -162, 	// YO
 -168, 	// YU
 -174, 	// WI
 -180, 	// WE
 -186, 	// WA
 80, 	// WO
 300, 	// H
 240, 	// M
 300, 	// N
 250, 	// NG
 240, 	// EM
 160, 	// EN
 -1, 	// NV
 120, 	// BH
 150, 	// F
 120, 	// DH
 80, 	// S
 120, 	// Z
 200, 	// CX
 100, 	// SH
 120, 	// ZH
 140, 	// GH
 100, 	// R
 180, 	// P
 80, 	// B
 150, 	// T
 100, 	// D
 160, 	// K
 120, 	// G
 150, 	// TS
 100, 	// DZ
 150, 	// CH
 150, 	// JH
// ==== B3 ====
 500, 	// _
 210, 	// I
 100, 	// E
 140, 	// A
 80, 	// O
 110, 	// U
 200, 	// YE
 190, 	// YA
 -192, 	// YO
 -198, 	// YU
 -204, 	// WI
 -210, 	// WE
 -216, 	// WA
 120, 	// WO
 300, 	// H
 120, 	// M
 160, 	// N
 200, 	// NG
 120, 	// EM
 220, 	// EN
 -1, 	// NV
 150, 	// BH
 200, 	// F
 150, 	// DH
 200, 	// S
 200, 	// Z
 300, 	// CX
 300, 	// SH
 300, 	// ZH
 300, 	// GH
 300, 	// R
 180, 	// P
 130, 	// B
 250, 	// T
 240, 	// D
 280, 	// K
 180, 	// G
 250, 	// TS
 240, 	// DZ
 280, 	// CH
 180, 	// JH
// ==== AV ====
 0, 	// _
 66, 	// I
 65, 	// E
 63, 	// A
 66, 	// O
 66, 	// U
 66, 	// YE
 66, 	// YA
 66, 	// YO
 66, 	// YU
 66, 	// WI
 66, 	// WE
 66, 	// WA
 66, 	// WO
 0, 	// H
 63, 	// M
 63, 	// N
 63, 	// NG
 63, 	// EM
 63, 	// EN
 65, 	// NV
 58, 	// BH
 0, 	// F
 58, 	// DH
 0, 	// S
 54, 	// Z
 0, 	// CX
 0, 	// SH
 60, 	// ZH
 60, 	// GH
 63, 	// R
 0, 	// P
 20, 	// B
 0, 	// T
 20, 	// D
 0, 	// K
 20, 	// G
 0, 	// TS
 20, 	// DZ
 0, 	// CH
 20 };	// JH

// Female - F1,F2,F3,B1,B2,B3,AV data for each phoneme
//     Negative numbers are offsets into femdip table (multi-part formants)
//     Positive numbers are actual values
const short jp_femtar_def[] = {
// ==== F1 ====
 -1, 	// _
 320, 	// I
 600, 	// E
 800, 	// A
 600, 	// O
 400, 	// U
 -2, 	// YE
 -8, 	// YA
 -14, 	// YO
 -20, 	// YU
 -26, 	// WI
 -32, 	// WE
 -38, 	// WA
 -44, 	// WO
 -1, 	// H
 420, 	// M
 420, 	// N
 420, 	// NG
 420, 	// EM
 420, 	// EN
 -1, 	// NV
 280, 	// BH
 340, 	// F
 280, 	// DH
 320, 	// S
 240, 	// Z
 300, 	// CX
 300, 	// SH
 300, 	// ZH
 290, 	// GH
 350, 	// R
 350, 	// P
 210, 	// B
 350, 	// T
 210, 	// D
 350, 	// K
 210, 	// G
 350, 	// TS
 210, 	// DZ
 350, 	// CH
 260, 	// JH
// ==== F2 ====
 -1, 	// _
 2340, 	// I
 1950, 	// E
 1430, 	// A
 930, 	// O
 1620, 	// U
 -50, 	// YE
 -56, 	// YA
 -62, 	// YO
 -68, 	// YU
 -74, 	// WI
 -80, 	// WE
 -86, 	// WA
 -92, 	// WO
 -1, 	// H
 1270, 	// M
 1340, 	// N
 1600, 	// NG
 1270, 	// EM
 1340, 	// EN
 -1, 	// NV
 1200, 	// BH
 1300, 	// F
 1600, 	// DH
 1420, 	// S
 1420, 	// Z
 1800, 	// CX
 1650, 	// SH
 1650, 	// ZH
 1650, 	// GH
 1600, 	// R
 1100, 	// P
 1100, 	// B
 1600, 	// T
 1600, 	// D
 1790, 	// K
 1790, 	// G
 1600, 	// TS
 1600, 	// DZ
 1750, 	// CH
 1730, 	// JH
// ==== F3 ====
 -1, 	// _
 3140, 	// I
 2700, 	// E
 2690, 	// A
 2640, 	// O
 2370, 	// U
 -98, 	// YE
 -104, 	// YA
 -110, 	// YO
 -116, 	// YU
 -122, 	// WI
 -128, 	// WE
 -134, 	// WA
 -140, 	// WO
 -1, 	// H
 2130, 	// M
 2500, 	// N
 2000, 	// NG
 2130, 	// EM
 2500, 	// EN
 -1, 	// NV
 2100, 	// BH
 2100, 	// F
 2600, 	// DH
 2550, 	// S
 2600, 	// Z
 2400, 	// CX
 2550, 	// SH
 2550, 	// ZH
 2200, 	// GH
 2600, 	// R
 2150, 	// P
 2150, 	// B
 2600, 	// T
 2600, 	// D
 2250, 	// K
 2250, 	// G
 2600, 	// TS
 2600, 	// DZ
 2700, 	// CH
 2700, 	// JH
// ==== B1 ====
 500, 	// _
 60, 	// I
 70, 	// E
 140, 	// A
 70, 	// O
 65, 	// U
 65, 	// YE
 -146, 	// YA
 65, 	// YO
 65, 	// YU
 50, 	// WI
 50, 	// WE
 50, 	// WA
 -1, 	// WO
 400, 	// H
 150, 	// M
 150, 	// N
 150, 	// NG
 150, 	// EM
 150, 	// EN
 -1, 	// NV
 140, 	// BH
 300, 	// F
 140, 	// DH
 300, 	// S
 140, 	// Z
 300, 	// CX
 300, 	// SH
 140, 	// ZH
 140, 	// GH
 90, 	// R
 300, 	// P
 150, 	// B
 300, 	// T
 150, 	// D
 300, 	// K
 150, 	// G
 300, 	// TS
 150, 	// DZ
 300, 	// CH
 70, 	// JH
// ==== B2 ====
 500, 	// _
 160, 	// I
 140, 	// E
 90, 	// A
 70, 	// O
 90, 	// U
 140, 	// YE
 140, 	// YA
 -152, 	// YO
 -158, 	// YU
 -164, 	// WI
 -170, 	// WE
 -176, 	// WA
 -182, 	// WO
 300, 	// H
 240, 	// M
 300, 	// N
 250, 	// NG
 240, 	// EM
 300, 	// EN
 -1, 	// NV
 120, 	// BH
 150, 	// F
 120, 	// DH
 80, 	// S
 120, 	// Z
 200, 	// CX
 100, 	// SH
 120, 	// ZH
 140, 	// GH
 100, 	// R
 180, 	// P
 80, 	// B
 150, 	// T
 100, 	// D
 160, 	// K
 120, 	// G
 150, 	// TS
 100, 	// DZ
 150, 	// CH
 150, 	// JH
// ==== B3 ====
 500, 	// _
 210, 	// I
 190, 	// E
 140, 	// A
 80, 	// O
 110, 	// U
 200, 	// YE
 190, 	// YA
 -188, 	// YO
 -194, 	// YU
 -200, 	// WI
 -206, 	// WE
 -212, 	// WA
 -218, 	// WO
 300, 	// H
 120, 	// M
 160, 	// N
 200, 	// NG
 120, 	// EM
 160, 	// EN
 -1, 	// NV
 150, 	// BH
 200, 	// F
 150, 	// DH
 200, 	// S
 200, 	// Z
 300, 	// CX
 300, 	// SH
 300, 	// ZH
 300, 	// GH
 300, 	// R
 180, 	// P
 130, 	// B
 250, 	// T
 240, 	// D
 280, 	// K
 180, 	// G
 250, 	// TS
 240, 	// DZ
 280, 	// CH
 180, 	// JH
// ==== AV ====
 0, 	// _
 66, 	// I
 65, 	// E
 65, 	// A
 66, 	// O
 66, 	// U
 66, 	// YE
 66, 	// YA
 66, 	// YO
 66, 	// YU
 0, 	// WI
 66, 	// WE
 66, 	// WA
 66, 	// WO
 0, 	// H
 63, 	// M
 63, 	// N
 63, 	// NG
 63, 	// EM
 63, 	// EN
 65, 	// NV
 58, 	// BH
 0, 	// F
 58, 	// DH
 0, 	// S
 54, 	// Z
 0, 	// CX
 0, 	// SH
 60, 	// ZH
 60, 	// GH
 63, 	// R
 0, 	// P
 20, 	// B
 0, 	// T
 20, 	// D
 0, 	// K
 20, 	// G
 0, 	// TS
 20, 	// DZ
 0, 	// CH
 20 };	// JH

// Male - F1,F1T,F2,F2T,F3,F3T,B1,B1T,B2,B2T,B3,B3T,AV,AVT data for Multi-part formants
const short jp_maldip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _
 0, 	// _
 280, 	// YE F1
 30, 	// YE F1 duration
 520, 	// YE F1
 60, 	// YE F1 duration
 540, 	// YE F1
 -1, 	// YE F1 duration
 285, 	// YA F1
 30, 	// YA F1 duration
 730, 	// YA F1
 60, 	// YA F1 duration
 760, 	// YA F1
 -1, 	// YA F1 duration
 270, 	// YO F1
 50, 	// YO F1 duration
 565, 	// YO F1
 130, 	// YO F1 duration
 565, 	// YO F1
 -1, 	// YO F1 duration
 270, 	// YU F1
 70, 	// YU F1 duration
 300, 	// YU F1
 130, 	// YU F1 duration
 300, 	// YU F1
 -1, 	// YU F1 duration
 300, 	// WI F1
 30, 	// WI F1 duration
 330, 	// WI F1
 80, 	// WI F1 duration
 330, 	// WI F1
 -1, 	// WI F1 duration
 300, 	// WE F1
 30, 	// WE F1 duration
 580, 	// WE F1
 80, 	// WE F1 duration
 610, 	// WE F1
 -1, 	// WE F1 duration
 330, 	// WA F1
 30, 	// WA F1 duration
 750, 	// WA F1
 80, 	// WA F1 duration
 780, 	// WA F1
 -1, 	// WA F1 duration
 300, 	// WO F1
 30, 	// WO F1 duration
 500, 	// WO F1
 80, 	// WO F1 duration
 590, 	// WO F1
 -1, 	// WO F1 duration
 265, 	// R F1
 20, 	// R F1 duration
 265, 	// R F1
 -1, 	// R F1 duration
 2140, 	// YE F2
 30, 	// YE F2 duration
 1970, 	// YE F2
 90, 	// YE F2 duration
 1900, 	// YE F2
 -1, 	// YE F2 duration
 2275, 	// YA F2
 30, 	// YA F2 duration
 1490, 	// YA F2
 90, 	// YA F2 duration
 1430, 	// YA F2
 -1, 	// YA F2 duration
 2290, 	// YO F2
 50, 	// YO F2 duration
 1158, 	// YO F2
 130, 	// YO F2 duration
 1017, 	// YO F2
 -1, 	// YO F2 duration
 2290, 	// YU F2
 70, 	// YU F2 duration
 870, 	// YU F2
 130, 	// YU F2 duration
 870, 	// YU F2
 -1, 	// YU F2 duration
 1670, 	// WI F2
 30, 	// WI F2 duration
 2250, 	// WI F2
 80, 	// WI F2 duration
 2300, 	// WI F2
 -1, 	// WI F2 duration
 1200, 	// WE F2
 30, 	// WE F2 duration
 1670, 	// WE F2
 80, 	// WE F2 duration
 1780, 	// WE F2
 -1, 	// WE F2 duration
 1000, 	// WA F2
 30, 	// WA F2 duration
 1250, 	// WA F2
 80, 	// WA F2 duration
 1280, 	// WA F2
 -1, 	// WA F2 duration
 750, 	// WO F2
 30, 	// WO F2 duration
 830, 	// WO F2
 80, 	// WO F2 duration
 900, 	// WO F2
 -1, 	// WO F2 duration
 3140, 	// YE F3
 30, 	// YE F3 duration
 2680, 	// YE F3
 70, 	// YE F3 duration
 2650, 	// YE F3
 -1, 	// YE F3 duration
 3000, 	// YA F3
 30, 	// YA F3 duration
 2800, 	// YA F3
 70, 	// YA F3 duration
 2800, 	// YA F3
 -1, 	// YA F3 duration
 3010, 	// YO F3
 50, 	// YO F3 duration
 2385, 	// YO F3
 130, 	// YO F3 duration
 2500, 	// YO F3
 -1, 	// YO F3 duration
 3010, 	// YU F3
 70, 	// YU F3 duration
 2240, 	// YU F3
 130, 	// YU F3 duration
 2240, 	// YU F3
 -1, 	// YU F3 duration
 2500, 	// WI F3
 30, 	// WI F3 duration
 3050, 	// WI F3
 80, 	// WI F3 duration
 3100, 	// WI F3
 -1, 	// WI F3 duration
 2300, 	// WE F3
 30, 	// WE F3 duration
 2700, 	// WE F3
 80, 	// WE F3 duration
 2730, 	// WE F3
 -1, 	// WE F3 duration
 2580, 	// WA F3
 30, 	// WA F3 duration
 2750, 	// WA F3
 80, 	// WA F3 duration
 2780, 	// WA F3
 -1, 	// WA F3 duration
 2420, 	// WO F3
 30, 	// WO F3 duration
 2580, 	// WO F3
 80, 	// WO F3 duration
 2630, 	// WO F3
 -1, 	// WO F3 duration
// ====== Bandwidths and duration ======
 50, 	// YA B1
 20, 	// YA B1 duration
 160, 	// YA B1
 90, 	// YA B1 duration
 160, 	// YA B1
 -1, 	// YA B1 duration
 80, 	// WA B1
 30, 	// WA B1 duration
 100, 	// WA B1
 80, 	// WA B1 duration
 100, 	// WA B1
 -1, 	// WA B1 duration
 200, 	// YO B2
 40, 	// YO B2 duration
 70, 	// YO B2
 120, 	// YO B2 duration
 70, 	// YO B2
 -1, 	// YO B2 duration
 200, 	// YU B2
 40, 	// YU B2 duration
 80, 	// YU B2
 130, 	// YU B2 duration
 80, 	// YU B2
 -1, 	// YU B2 duration
 80, 	// WI B2
 30, 	// WI B2 duration
 200, 	// WI B2
 80, 	// WI B2 duration
 200, 	// WI B2
 -1, 	// WI B2 duration
 80, 	// WE B2
 30, 	// WE B2 duration
 180, 	// WE B2
 80, 	// WE B2 duration
 180, 	// WE B2
 -1, 	// WE B2 duration
 80, 	// WA B2
 30, 	// WA B2 duration
 100, 	// WA B2
 80, 	// WA B2 duration
 100, 	// WA B2
 -1, 	// WA B2 duration
 300, 	// YO B3
 40, 	// YO B3 duration
 90, 	// YO B3
 100, 	// YO B3 duration
 90, 	// YO B3
 -1, 	// YO B3 duration
 300, 	// YU B3
 40, 	// YU B3 duration
 110, 	// YU B3
 100, 	// YU B3 duration
 110, 	// YU B3
 -1, 	// YU B3 duration
 120, 	// WI B3
 30, 	// WI B3 duration
 380, 	// WI B3
 80, 	// WI B3 duration
 380, 	// WI B3
 -1, 	// WI B3 duration
 120, 	// WE B3
 30, 	// WE B3 duration
 280, 	// WE B3
 80, 	// WE B3 duration
 280, 	// WE B3
 -1, 	// WE B3 duration
 120, 	// WA B3
 30, 	// WA B3 duration
 180, 	// WA B3
 80, 	// WA B3 duration
 180, 	// WA B3
 -1, 	// WA B3 duration
// ====== Amplitude of Voicing ======
 0};

// Female diphthongs
const short jp_femdip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _
 0, 	// _
 280, 	// YE F1
 35, 	// YE F1 duration
 520, 	// YE F1
 100, 	// YE F1 duration
 540, 	// YE F1
 -1, 	// YE F1 duration
 350, 	// YA F1
 20, 	// YA F1 duration
 730, 	// YA F1
 90, 	// YA F1 duration
 760, 	// YA F1
 -1, 	// YA F1 duration
 280, 	// YO F1
 30, 	// YO F1 duration
 520, 	// YO F1
 100, 	// YO F1 duration
 550, 	// YO F1
 -1, 	// YO F1 duration
 280, 	// YU F1
 40, 	// YU F1 duration
 310, 	// YU F1
 90, 	// YU F1 duration
 320, 	// YU F1
 -1, 	// YU F1 duration
 300, 	// WI F1
 30, 	// WI F1 duration
 330, 	// WI F1
 80, 	// WI F1 duration
 330, 	// WI F1
 -1, 	// WI F1 duration
 300, 	// WE F1
 30, 	// WE F1 duration
 580, 	// WE F1
 80, 	// WE F1 duration
 610, 	// WE F1
 -1, 	// WE F1 duration
 330, 	// WA F1
 30, 	// WA F1 duration
 750, 	// WA F1
 80, 	// WA F1 duration
 780, 	// WA F1
 -1, 	// WA F1 duration
 300, 	// WO F1
 30, 	// WO F1 duration
 500, 	// WO F1
 80, 	// WO F1 duration
 590, 	// WO F1
 -1, 	// WO F1 duration
 2140, 	// YE F2
 35, 	// YE F2 duration
 1970, 	// YE F2
 100, 	// YE F2 duration
 1900, 	// YE F2
 -1, 	// YE F2 duration
 2100, 	// YA F2
 30, 	// YA F2 duration
 1490, 	// YA F2
 120, 	// YA F2 duration
 1430, 	// YA F2
 -1, 	// YA F2 duration
 1900, 	// YO F2
 40, 	// YO F2 duration
 1050, 	// YO F2
 120, 	// YO F2 duration
 1010, 	// YO F2
 -1, 	// YO F2 duration
 2000, 	// YU F2
 40, 	// YU F2 duration
 1580, 	// YU F2
 130, 	// YU F2 duration
 1560, 	// YU F2
 -1, 	// YU F2 duration
 1670, 	// WI F2
 30, 	// WI F2 duration
 2250, 	// WI F2
 80, 	// WI F2 duration
 2300, 	// WI F2
 -1, 	// WI F2 duration
 1200, 	// WE F2
 30, 	// WE F2 duration
 1670, 	// WE F2
 80, 	// WE F2 duration
 1780, 	// WE F2
 -1, 	// WE F2 duration
 1000, 	// WA F2
 30, 	// WA F2 duration
 1250, 	// WA F2
 80, 	// WA F2 duration
 1280, 	// WA F2
 -1, 	// WA F2 duration
 750, 	// WO F2
 30, 	// WO F2 duration
 830, 	// WO F2
 80, 	// WO F2 duration
 900, 	// WO F2
 -1, 	// WO F2 duration
 3140, 	// YE F3
 40, 	// YE F3 duration
 2680, 	// YE F3
 80, 	// YE F3 duration
 2650, 	// YE F3
 -1, 	// YE F3 duration
 3020, 	// YA F3
 30, 	// YA F3 duration
 2600, 	// YA F3
 60, 	// YA F3 duration
 2600, 	// YA F3
 -1, 	// YA F3 duration
 2930, 	// YO F3
 30, 	// YO F3 duration
 2250, 	// YO F3
 80, 	// YO F3 duration
 2500, 	// YO F3
 -1, 	// YO F3 duration
 2900, 	// YU F3
 40, 	// YU F3 duration
 2260, 	// YU F3
 80, 	// YU F3 duration
 2230, 	// YU F3
 -1, 	// YU F3 duration
 2500, 	// WI F3
 30, 	// WI F3 duration
 3050, 	// WI F3
 80, 	// WI F3 duration
 3100, 	// WI F3
 -1, 	// WI F3 duration
 2300, 	// WE F3
 30, 	// WE F3 duration
 2700, 	// WE F3
 80, 	// WE F3 duration
 2730, 	// WE F3
 -1, 	// WE F3 duration
 2580, 	// WA F3
 30, 	// WA F3 duration
 2750, 	// WA F3
 80, 	// WA F3 duration
 2780, 	// WA F3
 -1, 	// WA F3 duration
 2420, 	// WO F3
 30, 	// WO F3 duration
 2580, 	// WO F3
 80, 	// WO F3 duration
 2630, 	// WO F3
 -1, 	// WO F3 duration
// ====== Bandwidths and duration ======
 50, 	// YA B1
 20, 	// YA B1 duration
 160, 	// YA B1
 90, 	// YA B1 duration
 160, 	// YA B1
 -1, 	// YA B1 duration
 200, 	// YO B2
 40, 	// YO B2 duration
 70, 	// YO B2
 120, 	// YO B2 duration
 70, 	// YO B2
 -1, 	// YO B2 duration
 200, 	// YU B2
 40, 	// YU B2 duration
 80, 	// YU B2
 130, 	// YU B2 duration
 80, 	// YU B2
 -1, 	// YU B2 duration
 80, 	// WI B2
 30, 	// WI B2 duration
 200, 	// WI B2
 80, 	// WI B2 duration
 200, 	// WI B2
 -1, 	// WI B2 duration
 80, 	// WE B2
 30, 	// WE B2 duration
 180, 	// WE B2
 80, 	// WE B2 duration
 180, 	// WE B2
 -1, 	// WE B2 duration
 80, 	// WA B2
 30, 	// WA B2 duration
 100, 	// WA B2
 80, 	// WA B2 duration
 100, 	// WA B2
 -1, 	// WA B2 duration
 80, 	// WO B2
 30, 	// WO B2 duration
 80, 	// WO B2
 80, 	// WO B2 duration
 80, 	// WO B2
 -1, 	// WO B2 duration
 300, 	// YO B3
 40, 	// YO B3 duration
 90, 	// YO B3
 100, 	// YO B3 duration
 90, 	// YO B3
 -1, 	// YO B3 duration
 300, 	// YU B3
 40, 	// YU B3 duration
 110, 	// YU B3
 100, 	// YU B3 duration
 110, 	// YU B3
 -1, 	// YU B3 duration
 120, 	// WI B3
 30, 	// WI B3 duration
 380, 	// WI B3
 80, 	// WI B3 duration
 380, 	// WI B3
 -1, 	// WI B3 duration
 120, 	// WE B3
 30, 	// WE B3 duration
 280, 	// WE B3
 80, 	// WE B3 duration
 280, 	// WE B3
 -1, 	// WE B3 duration
 120, 	// WA B3
 30, 	// WA B3 duration
 180, 	// WA B3
 80, 	// WA B3 duration
 180, 	// WA B3
 -1, 	// WA B3 duration
 120, 	// WO B3
 30, 	// WO B3 duration
 120, 	// WO B3
 80, 	// WO B3 duration
 120, 	// WO B3
 -1, 	// WO B3 duration
// ====== Amplitude of Voicing ======
 0};

// Offsets into Amplitude data
const short jp_ptram_def[] = {
 0, 	// _
 0, 	// I
 0, 	// E
 0, 	// A
 0, 	// O
 0, 	// U
 0, 	// YE
 0, 	// YA
 0, 	// YO
 0, 	// YU
 0, 	// WI
 0, 	// WE
 0, 	// WA
 0, 	// WO
 0, 	// H
 0, 	// M
 0, 	// N
 0, 	// NG
 0, 	// EM
 0, 	// EN
 0, 	// NV
 0, 	// BH
 0, 	// F
 0, 	// DH
 0, 	// S
 0, 	// Z
 0, 	// CX
 0, 	// SH
 0, 	// ZH
 0, 	// GH
 0, 	// R
 0, 	// P
 0, 	// B
 0, 	// T
 0, 	// D
 0, 	// K
 0, 	// G
 0, 	// TS
 0, 	// DZ
 0, 	// CH
 0 };	// JH

// Offsets into Locus data
const short jp_plocu_def[] = {
// ==== Front ====
 0, 	// _
 0, 	// I
 0, 	// E
 0, 	// A
 0, 	// O
 0, 	// U
 0, 	// YE
 0, 	// YA
 0, 	// YO
 0, 	// YU
 0, 	// WI
 0, 	// WE
 0, 	// WA
 0, 	// WO
 0, 	// H
 1, 	// M
 10, 	// N
 19, 	// NG
 0, 	// EM
 28, 	// EN
 0, 	// NV
 0, 	// BH
 37, 	// F
 46, 	// DH
 55, 	// S
 64, 	// Z
 73, 	// CX
 82, 	// SH
 91, 	// ZH
 100, 	// GH
 109, 	// R
 118, 	// P
 127, 	// B
 136, 	// T
 145, 	// D
 154, 	// K
 163, 	// G
 172, 	// TS
 181, 	// DZ
 190, 	// CH
 199, 	// JH
// ==== Back ====
 0, 	// _
 0, 	// I
 0, 	// E
 0, 	// A
 0, 	// O
 0, 	// U
 0, 	// YE
 0, 	// YA
 0, 	// YO
 0, 	// YU
 0, 	// WI
 0, 	// WE
 0, 	// WA
 0, 	// WO
 0, 	// H
 208, 	// M
 217, 	// N
 226, 	// NG
 0, 	// EM
 235, 	// EN
 0, 	// NV
 0, 	// BH
 244, 	// F
 253, 	// DH
 262, 	// S
 271, 	// Z
 280, 	// CX
 289, 	// SH
 298, 	// ZH
 307, 	// GH
 316, 	// R
 325, 	// P
 334, 	// B
 343, 	// T
 352, 	// D
 361, 	// K
 370, 	// G
 379, 	// TS
 388, 	// DZ
 397, 	// CH
 406, 	// JH
// ==== Round ====
 0, 	// _
 0, 	// I
 0, 	// E
 0, 	// A
 0, 	// O
 0, 	// U
 0, 	// YE
 0, 	// YA
 0, 	// YO
 0, 	// YU
 0, 	// WI
 0, 	// WE
 0, 	// WA
 0, 	// WO
 0, 	// H
 415, 	// M
 424, 	// N
 433, 	// NG
 0, 	// EM
 442, 	// EN
 0, 	// NV
 0, 	// BH
 451, 	// F
 460, 	// DH
 469, 	// S
 478, 	// Z
 487, 	// CX
 496, 	// SH
 505, 	// ZH
 514, 	// GH
 523, 	// R
 0, 	// P
 532, 	// B
 541, 	// T
 550, 	// D
 559, 	// K
 568, 	// G
 577, 	// TS
 586, 	// DZ
 595, 	// CH
 604, 	// JH
// ==== Low ====
 0, 	// _
 0, 	// I
 0, 	// E
 0, 	// A
 0, 	// O
 0, 	// U
 0, 	// YE
 0, 	// YA
 0, 	// YO
 0, 	// YU
 0, 	// WI
 0, 	// WE
 0, 	// WA
 0, 	// WO
 0, 	// H
 0, 	// M
 0, 	// N
 0, 	// NG
 0, 	// EM
 0, 	// EN
 0, 	// NV
 0, 	// BH
 0, 	// F
 0, 	// DH
 0, 	// S
 0, 	// Z
 0, 	// CX
 0, 	// SH
 0, 	// ZH
 0, 	// GH
 0, 	// R
 0, 	// P
 0, 	// B
 0, 	// T
 0, 	// D
 0, 	// K
 0, 	// G
 0, 	// TS
 0, 	// DZ
 0, 	// CH
 0 };	// JH

// Male Locus data
const short jp_maleloc_def[] = {
 0, 
// Front
 350, 	// M F1 locus
 40, 	// M percent
 40, 	// M transition duration
 900, 	// M F2 locus
 85, 	// M percent
 15, 	// M transition duration
 2100, 	// M F3 locus
 32, 	// M percent
 25, 	// M transition duration
 300, 	// N F1 locus
 24, 	// N percent
 40, 	// N transition duration
 1500, 	// N F2 locus
 70, 	// N percent
 50, 	// N transition duration
 2800, 	// N F3 locus
 30, 	// N percent
 45, 	// N transition duration
 480, 	// NG F1 locus
 20, 	// NG percent
 40, 	// NG transition duration
 2300, 	// NG F2 locus
 20, 	// NG percent
 60, 	// NG transition duration
 3000, 	// NG F3 locus
 105, 	// NG percent
 60, 	// NG transition duration
 280, 	// EN F1 locus
 20, 	// EN percent
 35, 	// EN transition duration
 1550, 	// EN F2 locus
 75, 	// EN percent
 35, 	// EN transition duration
 2400, 	// EN F3 locus
 40, 	// EN percent
 45, 	// EN transition duration
 310, 	// F F1 locus
 50, 	// F percent
 40, 	// F transition duration
 1240, 	// F F2 locus
 85, 	// F percent
 40, 	// F transition duration
 2550, 	// F F3 locus
 0, 	// F percent
 45, 	// F transition duration
 260, 	// DH F1 locus
 40, 	// DH percent
 35, 	// DH transition duration
 1700, 	// DH F2 locus
 75, 	// DH percent
 35, 	// DH transition duration
 2600, 	// DH F3 locus
 40, 	// DH percent
 20, 	// DH transition duration
 310, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1540, 	// S F2 locus
 80, 	// S percent
 50, 	// S transition duration
 2650, 	// S F3 locus
 0, 	// S percent
 50, 	// S transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1540, 	// Z F2 locus
 80, 	// Z percent
 50, 	// Z transition duration
 2550, 	// Z F3 locus
 0, 	// Z percent
 70, 	// Z transition duration
 310, 	// CX F1 locus
 40, 	// CX percent
 40, 	// CX transition duration
 1240, 	// CX F2 locus
 35, 	// CX percent
 50, 	// CX transition duration
 2550, 	// CX F3 locus
 0, 	// CX percent
 70, 	// CX transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 2100, 	// SH F2 locus
 0, 	// SH percent
 60, 	// SH transition duration
 2940, 	// SH F3 locus
 20, 	// SH percent
 60, 	// SH transition duration
 245, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 2100, 	// ZH F2 locus
 0, 	// ZH percent
 60, 	// ZH transition duration
 2940, 	// ZH F3 locus
 20, 	// ZH percent
 60, 	// ZH transition duration
 250, 	// GH F1 locus
 43, 	// GH percent
 45, 	// GH transition duration
 2300, 	// GH F2 locus
 70, 	// GH percent
 50, 	// GH transition duration
 3300, 	// GH F3 locus
 50, 	// GH percent
 50, 	// GH transition duration
 350, 	// R F1 locus
 35, 	// R percent
 20, 	// R transition duration
 1700, 	// R F2 locus
 60, 	// R percent
 35, 	// R transition duration
 2700, 	// R F3 locus
 80, 	// R percent
 35, 	// R transition duration
 300, 	// P F1 locus
 40, 	// P percent
 20, 	// P transition duration
 100, 	// P F2 locus
 90, 	// P percent
 20, 	// P transition duration
 2300, 	// P F3 locus
 30, 	// P percent
 25, 	// P transition duration
 250, 	// B F1 locus
 40, 	// B percent
 20, 	// B transition duration
 1000, 	// B F2 locus
 90, 	// B percent
 20, 	// B transition duration
 2300, 	// B F3 locus
 25, 	// B percent
 25, 	// B transition duration
 300, 	// T F1 locus
 43, 	// T percent
 35, 	// T transition duration
 1700, 	// T F2 locus
 75, 	// T percent
 35, 	// T transition duration
 2600, 	// T F3 locus
 40, 	// T percent
 20, 	// T transition duration
 260, 	// D F1 locus
 40, 	// D percent
 35, 	// D transition duration
 1700, 	// D F2 locus
 60, 	// D percent
 35, 	// D transition duration
 2600, 	// D F3 locus
 40, 	// D percent
 20, 	// D transition duration
 350, 	// K F1 locus
 43, 	// K percent
 45, 	// K transition duration
 1800, 	// K F2 locus
 70, 	// K percent
 50, 	// K transition duration
 3100, 	// K F3 locus
 30, 	// K percent
 50, 	// K transition duration
 250, 	// G F1 locus
 33, 	// G percent
 45, 	// G transition duration
 2100, 	// G F2 locus
 20, 	// G percent
 50, 	// G transition duration
 3000, 	// G F3 locus
 113, 	// G percent
 50, 	// G transition duration
 300, 	// TS F1 locus
 43, 	// TS percent
 35, 	// TS transition duration
 2000, 	// TS F2 locus
 0, 	// TS percent
 35, 	// TS transition duration
 2700, 	// TS F3 locus
 0, 	// TS percent
 45, 	// TS transition duration
 250, 	// DZ F1 locus
 33, 	// DZ percent
 35, 	// DZ transition duration
 2000, 	// DZ F2 locus
 0, 	// DZ percent
 35, 	// DZ transition duration
 2700, 	// DZ F3 locus
 0, 	// DZ percent
 45, 	// DZ transition duration
 300, 	// CH F1 locus
 50, 	// CH percent
 50, 	// CH transition duration
 2050, 	// CH F2 locus
 0, 	// CH percent
 50, 	// CH transition duration
 2900, 	// CH F3 locus
 0, 	// CH percent
 50, 	// CH transition duration
 250, 	// JH F1 locus
 30, 	// JH percent
 50, 	// JH transition duration
 2050, 	// JH F2 locus
 0, 	// JH percent
 50, 	// JH transition duration
 2900, 	// JH F3 locus
 0, 	// JH percent
 50, 	// JH transition duration
// Back
 350, 	// M F1 locus
 30, 	// M percent
 40, 	// M transition duration
 900, 	// M F2 locus
 60, 	// M percent
 20, 	// M transition duration
 2100, 	// M F3 locus
 90, 	// M percent
 25, 	// M transition duration
 300, 	// N F1 locus
 22, 	// N percent
 40, 	// N transition duration
 1400, 	// N F2 locus
 70, 	// N percent
 55, 	// N transition duration
 2600, 	// N F3 locus
 20, 	// N percent
 50, 	// N transition duration
 480, 	// NG F1 locus
 20, 	// NG percent
 40, 	// NG transition duration
 1700, 	// NG F2 locus
 20, 	// NG percent
 70, 	// NG transition duration
 2150, 	// NG F3 locus
 20, 	// NG percent
 70, 	// NG transition duration
 280, 	// EN F1 locus
 20, 	// EN percent
 30, 	// EN transition duration
 1420, 	// EN F2 locus
 25, 	// EN percent
 75, 	// EN transition duration
 2400, 	// EN F3 locus
 30, 	// EN percent
 60, 	// EN transition duration
 310, 	// F F1 locus
 50, 	// F percent
 40, 	// F transition duration
 820, 	// F F2 locus
 80, 	// F percent
 40, 	// F transition duration
 2300, 	// F F3 locus
 50, 	// F percent
 45, 	// F transition duration
 200, 	// DH F1 locus
 53, 	// DH percent
 35, 	// DH transition duration
 2500, 	// DH F2 locus
 80, 	// DH percent
 55, 	// DH transition duration
 2600, 	// DH F3 locus
 50, 	// DH percent
 50, 	// DH transition duration
 310, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1540, 	// S F2 locus
 30, 	// S percent
 50, 	// S transition duration
 2690, 	// S F3 locus
 0, 	// S percent
 70, 	// S transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1540, 	// Z F2 locus
 30, 	// Z percent
 60, 	// Z transition duration
 2690, 	// Z F3 locus
 0, 	// Z percent
 70, 	// Z transition duration
 310, 	// CX F1 locus
 40, 	// CX percent
 40, 	// CX transition duration
 1240, 	// CX F2 locus
 35, 	// CX percent
 60, 	// CX transition duration
 2630, 	// CX F3 locus
 0, 	// CX percent
 70, 	// CX transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1900, 	// SH F2 locus
 0, 	// SH percent
 60, 	// SH transition duration
 2800, 	// SH F3 locus
 40, 	// SH percent
 65, 	// SH transition duration
 245, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 1900, 	// ZH F2 locus
 0, 	// ZH percent
 60, 	// ZH transition duration
 2800, 	// ZH F3 locus
 40, 	// ZH percent
 65, 	// ZH transition duration
 280, 	// GH F1 locus
 33, 	// GH percent
 40, 	// GH transition duration
 1650, 	// GH F2 locus
 20, 	// GH percent
 45, 	// GH transition duration
 1000, 	// GH F3 locus
 83, 	// GH percent
 50, 	// GH transition duration
 350, 	// R F1 locus
 37, 	// R percent
 20, 	// R transition duration
 1600, 	// R F2 locus
 40, 	// R percent
 45, 	// R transition duration
 2600, 	// R F3 locus
 70, 	// R percent
 35, 	// R transition duration
 320, 	// P F1 locus
 50, 	// P percent
 25, 	// P transition duration
 720, 	// P F2 locus
 80, 	// P percent
 30, 	// P transition duration
 2250, 	// P F3 locus
 58, 	// P percent
 30, 	// P transition duration
 300, 	// B F1 locus
 40, 	// B percent
 25, 	// B transition duration
 620, 	// B F2 locus
 80, 	// B percent
 30, 	// B transition duration
 2250, 	// B F3 locus
 58, 	// B percent
 30, 	// B transition duration
 320, 	// T F1 locus
 55, 	// T percent
 35, 	// T transition duration
 2500, 	// T F2 locus
 75, 	// T percent
 55, 	// T transition duration
 2600, 	// T F3 locus
 50, 	// T percent
 50, 	// T transition duration
 200, 	// D F1 locus
 53, 	// D percent
 35, 	// D transition duration
 1600, 	// D F2 locus
 40, 	// D percent
 55, 	// D transition duration
 2600, 	// D F3 locus
 50, 	// D percent
 50, 	// D transition duration
 350, 	// K F1 locus
 43, 	// K percent
 40, 	// K transition duration
 1650, 	// K F2 locus
 20, 	// K percent
 45, 	// K transition duration
 1000, 	// K F3 locus
 83, 	// K percent
 50, 	// K transition duration
 300, 	// G F1 locus
 33, 	// G percent
 50, 	// G transition duration
 2100, 	// G F2 locus
 16, 	// G percent
 60, 	// G transition duration
 2100, 	// G F3 locus
 0, 	// G percent
 90, 	// G transition duration
 300, 	// TS F1 locus
 43, 	// TS percent
 45, 	// TS transition duration
 1850, 	// TS F2 locus
 30, 	// TS percent
 75, 	// TS transition duration
 2500, 	// TS F3 locus
 30, 	// TS percent
 50, 	// TS transition duration
 250, 	// DZ F1 locus
 33, 	// DZ percent
 45, 	// DZ transition duration
 1850, 	// DZ F2 locus
 30, 	// DZ percent
 75, 	// DZ transition duration
 2500, 	// DZ F3 locus
 30, 	// DZ percent
 50, 	// DZ transition duration
 300, 	// CH F1 locus
 50, 	// CH percent
 50, 	// CH transition duration
 1950, 	// CH F2 locus
 0, 	// CH percent
 50, 	// CH transition duration
 2450, 	// CH F3 locus
 0, 	// CH percent
 40, 	// CH transition duration
 250, 	// JH F1 locus
 30, 	// JH percent
 50, 	// JH transition duration
 1950, 	// JH F2 locus
 0, 	// JH percent
 50, 	// JH transition duration
 2450, 	// JH F3 locus
 0, 	// JH percent
 40, 	// JH transition duration
// Round
 350, 	// M F1 locus
 20, 	// M percent
 30, 	// M transition duration
 970, 	// M F2 locus
 10, 	// M percent
 40, 	// M transition duration
 1550, 	// M F3 locus
 80, 	// M percent
 25, 	// M transition duration
 300, 	// N F1 locus
 24, 	// N percent
 40, 	// N transition duration
 1400, 	// N F2 locus
 0, 	// N percent
 75, 	// N transition duration
 2650, 	// N F3 locus
 0, 	// N percent
 75, 	// N transition duration
 480, 	// NG F1 locus
 20, 	// NG percent
 40, 	// NG transition duration
 1700, 	// NG F2 locus
 42, 	// NG percent
 70, 	// NG transition duration
 1920, 	// NG F3 locus
 25, 	// NG percent
 70, 	// NG transition duration
 280, 	// EN F1 locus
 20, 	// EN percent
 30, 	// EN transition duration
 1550, 	// EN F2 locus
 25, 	// EN percent
 95, 	// EN transition duration
 2420, 	// EN F3 locus
 30, 	// EN percent
 95, 	// EN transition duration
 310, 	// F F1 locus
 50, 	// F percent
 40, 	// F transition duration
 820, 	// F F2 locus
 80, 	// F percent
 40, 	// F transition duration
 2300, 	// F F3 locus
 50, 	// F percent
 45, 	// F transition duration
 250, 	// DH F1 locus
 43, 	// DH percent
 40, 	// DH transition duration
 1300, 	// DH F2 locus
 0, 	// DH percent
 65, 	// DH transition duration
 2560, 	// DH F3 locus
 0, 	// DH percent
 65, 	// DH transition duration
 310, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1320, 	// S F2 locus
 15, 	// S percent
 60, 	// S transition duration
 2660, 	// S F3 locus
 0, 	// S percent
 65, 	// S transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1320, 	// Z F2 locus
 15, 	// Z percent
 60, 	// Z transition duration
 2660, 	// Z F3 locus
 0, 	// Z percent
 65, 	// Z transition duration
 310, 	// CX F1 locus
 40, 	// CX percent
 40, 	// CX transition duration
 1320, 	// CX F2 locus
 15, 	// CX percent
 60, 	// CX transition duration
 2460, 	// CX F3 locus
 0, 	// CX percent
 65, 	// CX transition duration
 280, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1700, 	// SH F2 locus
 0, 	// SH percent
 60, 	// SH transition duration
 2300, 	// SH F3 locus
 20, 	// SH percent
 70, 	// SH transition duration
 240, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 1830, 	// ZH F2 locus
 0, 	// ZH percent
 60, 	// ZH transition duration
 2300, 	// ZH F3 locus
 20, 	// ZH percent
 70, 	// ZH transition duration
 280, 	// GH F1 locus
 45, 	// GH percent
 40, 	// GH transition duration
 1400, 	// GH F2 locus
 60, 	// GH percent
 50, 	// GH transition duration
 2120, 	// GH F3 locus
 15, 	// GH percent
 50, 	// GH transition duration
 350, 	// R F1 locus
 33, 	// R percent
 20, 	// R transition duration
 1400, 	// R F2 locus
 40, 	// R percent
 40, 	// R transition duration
 2300, 	// R F3 locus
 80, 	// R percent
 35, 	// R transition duration
 300, 	// B F1 locus
 40, 	// B percent
 25, 	// B transition duration
 620, 	// B F2 locus
 80, 	// B percent
 25, 	// B transition duration
 2250, 	// B F3 locus
 50, 	// B percent
 30, 	// B transition duration
 320, 	// T F1 locus
 53, 	// T percent
 40, 	// T transition duration
 1300, 	// T F2 locus
 0, 	// T percent
 65, 	// T transition duration
 2560, 	// T F3 locus
 0, 	// T percent
 65, 	// T transition duration
 250, 	// D F1 locus
 43, 	// D percent
 40, 	// D transition duration
 1300, 	// D F2 locus
 40, 	// D percent
 65, 	// D transition duration
 2560, 	// D F3 locus
 0, 	// D percent
 65, 	// D transition duration
 350, 	// K F1 locus
 55, 	// K percent
 40, 	// K transition duration
 1200, 	// K F2 locus
 60, 	// K percent
 50, 	// K transition duration
 1800, 	// K F3 locus
 60, 	// K percent
 50, 	// K transition duration
 290, 	// G F1 locus
 45, 	// G percent
 40, 	// G transition duration
 2100, 	// G F2 locus
 42, 	// G percent
 65, 	// G transition duration
 1920, 	// G F3 locus
 15, 	// G percent
 80, 	// G transition duration
 300, 	// TS F1 locus
 43, 	// TS percent
 40, 	// TS transition duration
 1500, 	// TS F2 locus
 0, 	// TS percent
 70, 	// TS transition duration
 2450, 	// TS F3 locus
 0, 	// TS percent
 75, 	// TS transition duration
 250, 	// DZ F1 locus
 33, 	// DZ percent
 40, 	// DZ transition duration
 1500, 	// DZ F2 locus
 0, 	// DZ percent
 70, 	// DZ transition duration
 2450, 	// DZ F3 locus
 0, 	// DZ percent
 75, 	// DZ transition duration
 300, 	// CH F1 locus
 50, 	// CH percent
 50, 	// CH transition duration
 1730, 	// CH F2 locus
 10, 	// CH percent
 70, 	// CH transition duration
 2350, 	// CH F3 locus
 10, 	// CH percent
 70, 	// CH transition duration
 250, 	// JH F1 locus
 30, 	// JH percent
 50, 	// JH transition duration
 1730, 	// JH F2 locus
 10, 	// JH percent
 70, 	// JH transition duration
 2350, 	// JH F3 locus
 10, 	// JH percent
 70, 	// JH transition duration
// Low
 0};

// Female Locus
const short jp_femloc_def[] = {
 0, 
// Front
 470, 	// M F1 locus
 40, 	// M percent
 40, 	// M transition duration
 1, 	// M F2 locus
 85, 	// M percent
 15, 	// M transition duration
 2100, 	// M F3 locus
 32, 	// M percent
 25, 	// M transition duration
 470, 	// N F1 locus
 24, 	// N percent
 40, 	// N transition duration
 1, 	// N F2 locus
 97, 	// N percent
 35, 	// N transition duration
 2800, 	// N F3 locus
 30, 	// N percent
 45, 	// N transition duration
 480, 	// NG F1 locus
 20, 	// NG percent
 40, 	// NG transition duration
 2300, 	// NG F2 locus
 20, 	// NG percent
 60, 	// NG transition duration
 3000, 	// NG F3 locus
 105, 	// NG percent
 60, 	// NG transition duration
 -1, 	// EN F1 locus
 -1, 	// EN percent
 -1, 	// EN transition duration
 -1, 	// EN F2 locus
 -1, 	// EN percent
 -1, 	// EN transition duration
 -1, 	// EN F3 locus
 -1, 	// EN percent
 -1, 	// EN transition duration
 310, 	// F F1 locus
 50, 	// F percent
 40, 	// F transition duration
 1240, 	// F F2 locus
 85, 	// F percent
 40, 	// F transition duration
 2550, 	// F F3 locus
 0, 	// F percent
 45, 	// F transition duration
 260, 	// DH F1 locus
 40, 	// DH percent
 35, 	// DH transition duration
 1700, 	// DH F2 locus
 75, 	// DH percent
 35, 	// DH transition duration
 2600, 	// DH F3 locus
 40, 	// DH percent
 20, 	// DH transition duration
 310, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1540, 	// S F2 locus
 80, 	// S percent
 50, 	// S transition duration
 2650, 	// S F3 locus
 0, 	// S percent
 50, 	// S transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1540, 	// Z F2 locus
 80, 	// Z percent
 50, 	// Z transition duration
 2550, 	// Z F3 locus
 0, 	// Z percent
 70, 	// Z transition duration
 310, 	// CX F1 locus
 40, 	// CX percent
 40, 	// CX transition duration
 1240, 	// CX F2 locus
 35, 	// CX percent
 50, 	// CX transition duration
 2550, 	// CX F3 locus
 0, 	// CX percent
 70, 	// CX transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 2100, 	// SH F2 locus
 0, 	// SH percent
 60, 	// SH transition duration
 2940, 	// SH F3 locus
 20, 	// SH percent
 60, 	// SH transition duration
 245, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 2100, 	// ZH F2 locus
 0, 	// ZH percent
 60, 	// ZH transition duration
 2940, 	// ZH F3 locus
 20, 	// ZH percent
 60, 	// ZH transition duration
 250, 	// GH F1 locus
 43, 	// GH percent
 45, 	// GH transition duration
 2300, 	// GH F2 locus
 70, 	// GH percent
 50, 	// GH transition duration
 3300, 	// GH F3 locus
 50, 	// GH percent
 50, 	// GH transition duration
 200, 	// R F1 locus
 35, 	// R percent
 30, 	// R transition duration
 1500, 	// R F2 locus
 90, 	// R percent
 35, 	// R transition duration
 2700, 	// R F3 locus
 10, 	// R percent
 35, 	// R transition duration
 300, 	// P F1 locus
 40, 	// P percent
 20, 	// P transition duration
 100, 	// P F2 locus
 90, 	// P percent
 20, 	// P transition duration
 2300, 	// P F3 locus
 30, 	// P percent
 25, 	// P transition duration
 250, 	// B F1 locus
 40, 	// B percent
 20, 	// B transition duration
 100, 	// B F2 locus
 90, 	// B percent
 20, 	// B transition duration
 2300, 	// B F3 locus
 25, 	// B percent
 25, 	// B transition duration
 300, 	// T F1 locus
 43, 	// T percent
 35, 	// T transition duration
 1700, 	// T F2 locus
 75, 	// T percent
 35, 	// T transition duration
 2600, 	// T F3 locus
 40, 	// T percent
 20, 	// T transition duration
 260, 	// D F1 locus
 40, 	// D percent
 35, 	// D transition duration
 1700, 	// D F2 locus
 75, 	// D percent
 35, 	// D transition duration
 2600, 	// D F3 locus
 40, 	// D percent
 20, 	// D transition duration
 350, 	// K F1 locus
 43, 	// K percent
 45, 	// K transition duration
 2300, 	// K F2 locus
 70, 	// K percent
 50, 	// K transition duration
 2800, 	// K F3 locus
 30, 	// K percent
 50, 	// K transition duration
 250, 	// G F1 locus
 43, 	// G percent
 45, 	// G transition duration
 2300, 	// G F2 locus
 70, 	// G percent
 50, 	// G transition duration
 2800, 	// G F3 locus
 30, 	// G percent
 50, 	// G transition duration
 300, 	// TS F1 locus
 43, 	// TS percent
 35, 	// TS transition duration
 2000, 	// TS F2 locus
 0, 	// TS percent
 35, 	// TS transition duration
 2700, 	// TS F3 locus
 0, 	// TS percent
 45, 	// TS transition duration
 250, 	// DZ F1 locus
 33, 	// DZ percent
 35, 	// DZ transition duration
 2000, 	// DZ F2 locus
 0, 	// DZ percent
 35, 	// DZ transition duration
 2700, 	// DZ F3 locus
 0, 	// DZ percent
 45, 	// DZ transition duration
 300, 	// CH F1 locus
 50, 	// CH percent
 50, 	// CH transition duration
 2050, 	// CH F2 locus
 0, 	// CH percent
 50, 	// CH transition duration
 2900, 	// CH F3 locus
 0, 	// CH percent
 50, 	// CH transition duration
 250, 	// JH F1 locus
 30, 	// JH percent
 50, 	// JH transition duration
 2050, 	// JH F2 locus
 0, 	// JH percent
 50, 	// JH transition duration
 2900, 	// JH F3 locus
 0, 	// JH percent
 50, 	// JH transition duration
// Back
 470, 	// M F1 locus
 30, 	// M percent
 40, 	// M transition duration
 1, 	// M F2 locus
 88, 	// M percent
 30, 	// M transition duration
 1, 	// M F3 locus
 97, 	// M percent
 40, 	// M transition duration
 470, 	// N F1 locus
 22, 	// N percent
 40, 	// N transition duration
 2000, 	// N F2 locus
 70, 	// N percent
 55, 	// N transition duration
 2600, 	// N F3 locus
 0, 	// N percent
 50, 	// N transition duration
 480, 	// NG F1 locus
 20, 	// NG percent
 40, 	// NG transition duration
 1700, 	// NG F2 locus
 20, 	// NG percent
 70, 	// NG transition duration
 2150, 	// NG F3 locus
 20, 	// NG percent
 70, 	// NG transition duration
 -1, 	// EN F1 locus
 -1, 	// EN percent
 -1, 	// EN transition duration
 -1, 	// EN F2 locus
 -1, 	// EN percent
 -1, 	// EN transition duration
 -1, 	// EN F3 locus
 -1, 	// EN percent
 -1, 	// EN transition duration
 310, 	// F F1 locus
 50, 	// F percent
 40, 	// F transition duration
 820, 	// F F2 locus
 80, 	// F percent
 40, 	// F transition duration
 2300, 	// F F3 locus
 50, 	// F percent
 45, 	// F transition duration
 200, 	// DH F1 locus
 53, 	// DH percent
 35, 	// DH transition duration
 2500, 	// DH F2 locus
 80, 	// DH percent
 55, 	// DH transition duration
 2600, 	// DH F3 locus
 50, 	// DH percent
 50, 	// DH transition duration
 310, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1540, 	// S F2 locus
 30, 	// S percent
 50, 	// S transition duration
 2690, 	// S F3 locus
 0, 	// S percent
 70, 	// S transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1540, 	// Z F2 locus
 30, 	// Z percent
 60, 	// Z transition duration
 2690, 	// Z F3 locus
 0, 	// Z percent
 70, 	// Z transition duration
 310, 	// CX F1 locus
 40, 	// CX percent
 40, 	// CX transition duration
 1240, 	// CX F2 locus
 35, 	// CX percent
 60, 	// CX transition duration
 2630, 	// CX F3 locus
 0, 	// CX percent
 70, 	// CX transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1900, 	// SH F2 locus
 0, 	// SH percent
 60, 	// SH transition duration
 2800, 	// SH F3 locus
 40, 	// SH percent
 65, 	// SH transition duration
 245, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 1900, 	// ZH F2 locus
 0, 	// ZH percent
 60, 	// ZH transition duration
 2800, 	// ZH F3 locus
 40, 	// ZH percent
 65, 	// ZH transition duration
 280, 	// GH F1 locus
 33, 	// GH percent
 40, 	// GH transition duration
 1650, 	// GH F2 locus
 20, 	// GH percent
 45, 	// GH transition duration
 1000, 	// GH F3 locus
 83, 	// GH percent
 50, 	// GH transition duration
 150, 	// R F1 locus
 37, 	// R percent
 30, 	// R transition duration
 2300, 	// R F2 locus
 70, 	// R percent
 45, 	// R transition duration
 2900, 	// R F3 locus
 70, 	// R percent
 35, 	// R transition duration
 320, 	// P F1 locus
 50, 	// P percent
 25, 	// P transition duration
 720, 	// P F2 locus
 80, 	// P percent
 30, 	// P transition duration
 2250, 	// P F3 locus
 58, 	// P percent
 30, 	// P transition duration
 300, 	// B F1 locus
 40, 	// B percent
 25, 	// B transition duration
 620, 	// B F2 locus
 80, 	// B percent
 30, 	// B transition duration
 2250, 	// B F3 locus
 58, 	// B percent
 30, 	// B transition duration
 320, 	// T F1 locus
 55, 	// T percent
 35, 	// T transition duration
 2500, 	// T F2 locus
 75, 	// T percent
 55, 	// T transition duration
 2600, 	// T F3 locus
 50, 	// T percent
 50, 	// T transition duration
 200, 	// D F1 locus
 53, 	// D percent
 35, 	// D transition duration
 2500, 	// D F2 locus
 80, 	// D percent
 55, 	// D transition duration
 2600, 	// D F3 locus
 50, 	// D percent
 50, 	// D transition duration
 350, 	// K F1 locus
 43, 	// K percent
 40, 	// K transition duration
 1650, 	// K F2 locus
 20, 	// K percent
 45, 	// K transition duration
 1000, 	// K F3 locus
 83, 	// K percent
 50, 	// K transition duration
 280, 	// G F1 locus
 33, 	// G percent
 40, 	// G transition duration
 1650, 	// G F2 locus
 20, 	// G percent
 45, 	// G transition duration
 1000, 	// G F3 locus
 83, 	// G percent
 50, 	// G transition duration
 300, 	// TS F1 locus
 43, 	// TS percent
 45, 	// TS transition duration
 1850, 	// TS F2 locus
 30, 	// TS percent
 75, 	// TS transition duration
 2500, 	// TS F3 locus
 30, 	// TS percent
 50, 	// TS transition duration
 250, 	// DZ F1 locus
 33, 	// DZ percent
 45, 	// DZ transition duration
 1850, 	// DZ F2 locus
 30, 	// DZ percent
 75, 	// DZ transition duration
 2500, 	// DZ F3 locus
 30, 	// DZ percent
 50, 	// DZ transition duration
 300, 	// CH F1 locus
 50, 	// CH percent
 50, 	// CH transition duration
 1950, 	// CH F2 locus
 0, 	// CH percent
 50, 	// CH transition duration
 2450, 	// CH F3 locus
 0, 	// CH percent
 40, 	// CH transition duration
 250, 	// JH F1 locus
 30, 	// JH percent
 50, 	// JH transition duration
 1950, 	// JH F2 locus
 0, 	// JH percent
 50, 	// JH transition duration
 2450, 	// JH F3 locus
 0, 	// JH percent
 40, 	// JH transition duration
// Round
 -1, 	// M F1 locus
 -1, 	// M percent
 -1, 	// M transition duration
 -1, 	// M F2 locus
 -1, 	// M percent
 -1, 	// M transition duration
 -1, 	// M F3 locus
 -1, 	// M percent
 -1, 	// M transition duration
 470, 	// N F1 locus
 24, 	// N percent
 40, 	// N transition duration
 1400, 	// N F2 locus
 0, 	// N percent
 75, 	// N transition duration
 2650, 	// N F3 locus
 0, 	// N percent
 75, 	// N transition duration
 480, 	// NG F1 locus
 20, 	// NG percent
 40, 	// NG transition duration
 1700, 	// NG F2 locus
 42, 	// NG percent
 70, 	// NG transition duration
 1920, 	// NG F3 locus
 25, 	// NG percent
 70, 	// NG transition duration
 -1, 	// EN F1 locus
 -1, 	// EN percent
 -1, 	// EN transition duration
 -1, 	// EN F2 locus
 -1, 	// EN percent
 -1, 	// EN transition duration
 -1, 	// EN F3 locus
 -1, 	// EN percent
 -1, 	// EN transition duration
 310, 	// F F1 locus
 50, 	// F percent
 40, 	// F transition duration
 820, 	// F F2 locus
 80, 	// F percent
 40, 	// F transition duration
 2300, 	// F F3 locus
 50, 	// F percent
 45, 	// F transition duration
 250, 	// DH F1 locus
 43, 	// DH percent
 40, 	// DH transition duration
 1300, 	// DH F2 locus
 0, 	// DH percent
 65, 	// DH transition duration
 2560, 	// DH F3 locus
 0, 	// DH percent
 65, 	// DH transition duration
 310, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1320, 	// S F2 locus
 15, 	// S percent
 60, 	// S transition duration
 2660, 	// S F3 locus
 0, 	// S percent
 65, 	// S transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1320, 	// Z F2 locus
 15, 	// Z percent
 60, 	// Z transition duration
 2660, 	// Z F3 locus
 0, 	// Z percent
 65, 	// Z transition duration
 310, 	// CX F1 locus
 40, 	// CX percent
 40, 	// CX transition duration
 1320, 	// CX F2 locus
 15, 	// CX percent
 60, 	// CX transition duration
 2460, 	// CX F3 locus
 0, 	// CX percent
 65, 	// CX transition duration
 280, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1700, 	// SH F2 locus
 0, 	// SH percent
 60, 	// SH transition duration
 2300, 	// SH F3 locus
 20, 	// SH percent
 70, 	// SH transition duration
 240, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 1830, 	// ZH F2 locus
 0, 	// ZH percent
 60, 	// ZH transition duration
 2300, 	// ZH F3 locus
 20, 	// ZH percent
 70, 	// ZH transition duration
 280, 	// GH F1 locus
 45, 	// GH percent
 40, 	// GH transition duration
 1400, 	// GH F2 locus
 60, 	// GH percent
 50, 	// GH transition duration
 2120, 	// GH F3 locus
 15, 	// GH percent
 50, 	// GH transition duration
 250, 	// R F1 locus
 33, 	// R percent
 30, 	// R transition duration
 1600, 	// R F2 locus
 50, 	// R percent
 40, 	// R transition duration
 2300, 	// R F3 locus
 0, 	// R percent
 35, 	// R transition duration
 -1, 	// B F1 locus
 -1, 	// B percent
 -1, 	// B transition duration
 -1, 	// B F2 locus
 -1, 	// B percent
 -1, 	// B transition duration
 -1, 	// B F3 locus
 -1, 	// B percent
 -1, 	// B transition duration
 320, 	// T F1 locus
 53, 	// T percent
 40, 	// T transition duration
 1300, 	// T F2 locus
 0, 	// T percent
 65, 	// T transition duration
 2560, 	// T F3 locus
 0, 	// T percent
 65, 	// T transition duration
 250, 	// D F1 locus
 43, 	// D percent
 40, 	// D transition duration
 1300, 	// D F2 locus
 0, 	// D percent
 65, 	// D transition duration
 2560, 	// D F3 locus
 0, 	// D percent
 65, 	// D transition duration
 350, 	// K F1 locus
 55, 	// K percent
 40, 	// K transition duration
 1400, 	// K F2 locus
 60, 	// K percent
 50, 	// K transition duration
 2120, 	// K F3 locus
 15, 	// K percent
 50, 	// K transition duration
 280, 	// G F1 locus
 45, 	// G percent
 40, 	// G transition duration
 1400, 	// G F2 locus
 60, 	// G percent
 50, 	// G transition duration
 2120, 	// G F3 locus
 15, 	// G percent
 50, 	// G transition duration
 300, 	// TS F1 locus
 43, 	// TS percent
 40, 	// TS transition duration
 1500, 	// TS F2 locus
 0, 	// TS percent
 70, 	// TS transition duration
 2450, 	// TS F3 locus
 0, 	// TS percent
 75, 	// TS transition duration
 250, 	// DZ F1 locus
 33, 	// DZ percent
 40, 	// DZ transition duration
 1500, 	// DZ F2 locus
 0, 	// DZ percent
 70, 	// DZ transition duration
 2450, 	// DZ F3 locus
 0, 	// DZ percent
 75, 	// DZ transition duration
 300, 	// CH F1 locus
 50, 	// CH percent
 50, 	// CH transition duration
 1730, 	// CH F2 locus
 10, 	// CH percent
 70, 	// CH transition duration
 2350, 	// CH F3 locus
 10, 	// CH percent
 70, 	// CH transition duration
 250, 	// JH F1 locus
 30, 	// JH percent
 50, 	// JH transition duration
 1730, 	// JH F2 locus
 10, 	// JH percent
 70, 	// JH transition duration
 2350, 	// JH F3 locus
 10, 	// JH percent
 70, 	// JH transition duration
// Low
 0};

const struct rom_data_s jp_rom_data_def = {
jp_inhdr_def,
jp_mindur_def,
jp_burdr_def,
jp_begtyp_def,
jp_endtyp_def,
jp_place_def,
jp_featb_def,
jp_maltar_def,
jp_femtar_def,
jp_maldip_def,
jp_femdip_def,
jp_ptram_def,
jp_plocu_def,
jp_maleloc_def,
jp_femloc_def
};


