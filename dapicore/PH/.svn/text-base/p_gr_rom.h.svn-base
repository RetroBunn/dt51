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

#define GR_PH_PHONEME_COUNT 62
#define GR_PH_PHONEME_NAMES " _ A E AE EX I O OE U UE AH EH AZ IH OH OZ UH UZ EI AU EU AN IM UM ON J L RR R H M N NG EL EM EN F V S Z SH ZH CH KH P B T D K G Q PF TS DJ TJ KS i1 e1 01 u1 y1 ER "

// Inherent Duration (milliseconds)
const short gr_inhdr_def[] = {
 255, 	// _
 90, 	// A
 90, 	// E
 80, 	// AE
 65, 	// EX
 70, 	// I
 105, 	// O
 125, 	// OE
 100, 	// U
 95, 	// UE
 180, 	// AH
 165, 	// EH
 175, 	// AZ
 180, 	// IH
 150, 	// OH
 155, 	// OZ
 170, 	// UH
 145, 	// UZ
 165, 	// EI
 160, 	// AU
 160, 	// EU
 180, 	// AN
 180, 	// IM
 160, 	// UM
 180, 	// ON
 75, 	// J
 80, 	// L
 90, 	// RR
 90, 	// R
 55, 	// H
 80, 	// M
 90, 	// N
 120, 	// NG
 140, 	// EL
 150, 	// EM
 155, 	// EN
 110, 	// F
 110, 	// V
 120, 	// S
 75, 	// Z
 120, 	// SH
 70, 	// ZH
 130, 	// CH
 110, 	// KH
 80, 	// P
 80, 	// B
 90, 	// T
 85, 	// D
 80, 	// K
 90, 	// G
 50, 	// Q
 110, 	// PF
 180, 	// TS
 100, 	// DJ
 130, 	// TJ
 140, 	// KS
 85, 	// i1
 120, 	// e1
 70, 	// 01
 80, 	// u1
 105, 	// y1
 120 }; 	//ER

// Minimum Duration (milliseconds)
const short gr_mindur_def[] = {
 7, 	// _
 50, 	// A
 55, 	// E
 50, 	// AE
 30, 	// EX
 44, 	// I
 60, 	// O
 50, 	// OE
 55, 	// U
 40, 	// UE
 135, 	// AH
 90, 	// EH
 95, 	// AZ
 110, 	// IH
 90, 	// OH
 70, 	// OZ
 130, 	// UH
 70, 	// UZ
 100, 	// EI
 100, 	// AU
 100, 	// EU
 90, 	// AN
 90, 	// IM
 90, 	// UM
 90, 	// ON
 45, 	// J
 40, 	// L
 70, 	// RR
 60, 	// R
 35, 	// H
 65, 	// M
 70, 	// N
 75, 	// NG
 90, 	// EL
 110, 	// EM
 110, 	// EN
 70, 	// F
 60, 	// V
 65, 	// S
 30, 	// Z
 70, 	// SH
 50, 	// ZH
 70, 	// CH
 60, 	// KH
 50, 	// P
 50, 	// B
 40, 	// T
 50, 	// D
 55, 	// K
 50, 	// G
 30, 	// Q
 60, 	// PF
 120, 	// TS
 60, 	// DJ
 90, 	// TJ
 85, 	// KS
 60, 	// i1
 75, 	// e1
 55, 	// 01
 55, 	// u1
 60, 	// y1
 70 };	//ER

// Burst Duration (milliseconds)
const short gr_burdr_def[] = {
 0, 	//_
 0, 	//A
 0, 	//E
 0, 	//AE
 0, 	//EX
 0, 	//I
 0, 	//O
 0, 	//OE
 0, 	//U
 0, 	//UE
 0, 	//AH
 0, 	//EH
 0, 	//AZ
 0, 	//IH
 0, 	//OH
 0, 	//OZ
 0, 	//UH
 0, 	//UZ
 0, 	//EI
 0, 	//AU
 0, 	//EU
 0, 	//AN
 0, 	//IM
 0, 	//UM
 0, 	//ON
 0, 	//J
 0, 	//L
 0, 	//RR
 0, 	//R
 0, 	//H
 0, 	//M
 0, 	//N
 0, 	//NG
 0, 	//EL
 0, 	//EM
 0, 	//EN
 0, 	//F
 0, 	//V
 0, 	//S
 0, 	//Z
 0, 	//SH
 0, 	//ZH
 0, 	//CH
 0, 	//KH
 7, 	//P
 7, 	//B
 13, 	//T
 13, 	//D
 14, 	//K
 16, 	//G
 0, 	//Q
 71, 	//PF
 80, 	//TS
 71, 	//DJ
 80, 	//TJ
 85, 	//KS
 0, 	//i1
 0, 	//e1
 0, 	//01
 0, 	//u1
 0, 	//y1
 0 };	//ER

// Beginning Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short gr_begtyp_def[] = {
 4, 	// _
 2, 	// A
 1, 	// E
 1, 	// AE
 6, 	// EX
 1, 	// I
 2, 	// O
 3, 	// OE
 2, 	// U
 3, 	// UE
 6, 	// AH
 1, 	// EH
 1, 	// AZ
 1, 	// IH
 2, 	// OH
 3, 	// OZ
 3, 	// UH
 3, 	// UZ
 2, 	// EI
 6, 	// AU
 2, 	// EU
 2, 	// AN
 1, 	// IM
 2, 	// UM
 2, 	// ON
 1, 	// J
 4, 	// L
 4, 	// RR
 2, 	// R
 4, 	// H
 4, 	// M
 4, 	// N
 4, 	// NG
 1, 	// EL
 4, 	// EM
 4, 	// EN
 4, 	// F
 4, 	// V
 4, 	// S
 4, 	// Z
 4, 	// SH
 4, 	// ZH
 4, 	// CH
 4, 	// KH
 4, 	// P
 4, 	// B
 4, 	// T
 4, 	// D
 4, 	// K
 4, 	// G
 4, 	// Q
 4, 	// PF
 4, 	// TS
 4, 	// DJ
 4, 	// TJ
 4, 	// KS
 1, 	// i1
 1, 	// e1
 2, 	// 01
 2, 	// u1
 3, 	// y1
 1 };	// ER

// Ending Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short gr_endtyp_def[] = {
 4, 	// _
 2, 	// A
 1, 	// E
 1, 	// AE
 6, 	// EX
 1, 	// I
 2, 	// O
 3, 	// OE
 2, 	// U
 3, 	// UE
 6, 	// AH
 1, 	// EH
 1, 	// AZ
 1, 	// IH
 2, 	// OH
 3, 	// OZ
 3, 	// UH
 3, 	// UZ
 1, 	// EI
 3, 	// AU
 1, 	// EU
 2, 	// AN
 1, 	// IM
 2, 	// UM
 2, 	// ON
 1, 	// J
 4, 	// L
 4, 	// RR
 2, 	// R
 4, 	// H
 4, 	// M
 4, 	// N
 4, 	// NG
 1, 	// EL
 4, 	// EM
 4, 	// EN
 4, 	// F
 4, 	// V
 4, 	// S
 4, 	// Z
 4, 	// SH
 4, 	// ZH
 4, 	// CH
 4, 	// KH
 4, 	// P
 4, 	// B
 4, 	// T
 4, 	// D
 4, 	// K
 4, 	// G
 4, 	// Q
 4, 	// PF
 4, 	// TS
 4, 	// DJ
 4, 	// TJ
 4, 	// KS
 1, 	// i1
 1, 	// e1
 2, 	// 01
 2, 	// u1
 3, 	// y1
 2 };	// ER

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
const short gr_place_def[] = {
 0x0000, 	// _
 0x0000, 	// A
 0x0000, 	// E
 0x0000, 	// AE
 0x0000, 	// EX
 0x0000, 	// I
 0x0000, 	// O
 0x0000, 	// OE
 0x0000, 	// U
 0x0000, 	// UE
 0x0000, 	// AH
 0x0000, 	// EH
 0x0000, 	// AZ
 0x0000, 	// IH
 0x0000, 	// OH
 0x0000, 	// OZ
 0x0000, 	// UH
 0x0000, 	// UZ
 0x0000, 	// EI
 0x0000, 	// AU
 0x0000, 	// EU
 0x0000, 	// AN
 0x0000, 	// IM
 0x0000, 	// UM
 0x0000, 	// ON
 0x00c0, 	// J
 0x0000, 	// L
 0x0010, 	// RR
 0x0010, 	// R
 0x0000, 	// H
 0x0001, 	// M
 0x0008, 	// N
 0x0010, 	// NG
 0x0000, 	// EL
 0x0001, 	// EM
 0x0008, 	// EN
 0x0001, 	// F
 0x0001, 	// V
 0x0008, 	// S
 0x0008, 	// Z
 0x0004, 	// SH
 0x0004, 	// ZH
 0x0010, 	// CH
 0x0010, 	// KH
 0x0001, 	// P
 0x0001, 	// B
 0x0008, 	// T
 0x0008, 	// D
 0x0010, 	// K
 0x0010, 	// G
 0x0020, 	// Q
 0x0001, 	// PF
 0x0008, 	// TS
 0x0008, 	// DJ
 0x0008, 	// TJ
 0x0008, 	// KS
 0x0000, 	// i1
 0x0000, 	// e1
 0x0000, 	// 01
 0x0000, 	// u1
 0x0000, 	// y1
 0x0000 };	// ER

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
const int gr_featb_def[] = {
 0x00000010, 	// _
 0x0000001f, 	// A
 0x0000001f, 	// E
 0x0000001f, 	// AE
 0x0000001f, 	// EX
 0x0000001f, 	// I
 0x0000001f, 	// O
 0x0000001f, 	// OE
 0x0000001f, 	// U
 0x0000001f, 	// UE
 0x0000001f, 	// AH
 0x0000001f, 	// EH
 0x0000001f, 	// AZ
 0x0000001f, 	// IH
 0x0000001f, 	// OH
 0x0000001f, 	// OZ
 0x0000001f, 	// UH
 0x0000001f, 	// UZ
 0x0000001f, 	// EI
 0x0000001f, 	// AU
 0x0000001f, 	// EU
 0x0000009f, 	// AN
 0x0000009f, 	// IM
 0x0000009f, 	// UM
 0x0000009f, 	// ON
 0x0000071a, 	// J
 0x0000071a, 	// L
 0x00000132, 	// RR
 0x0000071a, 	// R
 0x00000110, 	// H
 0x0000259a, 	// M
 0x0000259a, 	// N
 0x0000259a, 	// NG
 0x0000041b, 	// EL
 0x0000249b, 	// EM
 0x0000249b, 	// EN
 0x00000120, 	// F
 0x00000122, 	// V
 0x00000120, 	// S
 0x00000122, 	// Z
 0x00000120, 	// SH
 0x00000122, 	// ZH
 0x00000120, 	// CH
 0x00000120, 	// KH
 0x00002960, 	// P
 0x00002962, 	// B
 0x00002960, 	// T
 0x00002962, 	// D
 0x00002960, 	// K
 0x00002962, 	// G
 0x00000110, 	// Q
 0x00002920, 	// PF
 0x00002920, 	// TS
 0x00002962, 	// DJ
 0x00002920, 	// TJ
 0x00002920, 	// KS
 0x0000001f, 	// i1
 0x0000001f, 	// e1
 0x0000001f, 	// 01
 0x0000001f, 	// u1
 0x0000001f, 	// y1
 0x0000001b, 	// ER
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
const short gr_maltar_def[] = {
// ==== F1 ====
 -1, 	// _
 753, 	// A
 510, 	// E
 649, 	// AE
 470, 	// EX
 305, 	// I
 590, 	// O
 468, 	// OE
 -2, 	// U
 -6, 	// UE
 708, 	// AH
 386, 	// EH
 479, 	// AZ
 290, 	// IH
 353, 	// OH
 394, 	// OZ
 285, 	// UH
 296, 	// UZ
 -10, 	// EI
 -18, 	// AU
 -24, 	// EU
 550, 	// AN
 549, 	// IM
 725, 	// UM
 480, 	// ON
 300, 	// J
 344, 	// L
 320, 	// RR
 600, 	// R
 -1, 	// H
 300, 	// M
 320, 	// N
 250, 	// NG
 400, 	// EL
 -30, 	// EM
 -36, 	// EN
 340, 	// F
 340, 	// V
 320, 	// S
 309, 	// Z
 300, 	// SH
 280, 	// ZH
 350, 	// CH
 450, 	// KH
 340, 	// P
 210, 	// B
 350, 	// T
 350, 	// D
 300, 	// K
 429, 	// G
 -1, 	// Q
 350, 	// PF
 500, 	// TS
 280, 	// DJ
 553, 	// TJ
 350, 	// KS
 366, 	// i1
 407, 	// e1
 407, 	// 01
 345, 	// u1
 325, 	// y1
 -42, 	// ER
// ==== F2 ====
 -1, 	// _
 1200, 	// A
 1715, 	// E
 1607, 	// AE
 1270, 	// EX
 2200, 	// I
 997, 	// O
 1373, 	// OE
 -48, 	// U
 -52, 	// UE
 1268, 	// AH
 2136, 	// EH
 1915, 	// AZ
 2301, 	// IH
 624, 	// OH
 1402, 	// OZ
 558, 	// UH
 1760, 	// UZ
 -56, 	// EI
 -64, 	// AU
 -70, 	// EU
 1229, 	// AN
 1526, 	// IM
 1200, 	// UM
 780, 	// ON
 2100, 	// J
 1179, 	// L
 1250, 	// RR
 1250, 	// R
 -1, 	// H
 1200, 	// M
 1800, 	// N
 1600, 	// NG
 850, 	// EL
 -78, 	// EM
 -84, 	// EN
 1300, 	// F
 1300, 	// V
 1420, 	// S
 1420, 	// Z
 1850, 	// SH
 1650, 	// ZH
 2445, 	// CH
 1100, 	// KH
 1100, 	// P
 1100, 	// B
 1600, 	// T
 1650, 	// D
 1790, 	// K
 1790, 	// G
 -1, 	// Q
 1340, 	// PF
 1880, 	// TS
 1800, 	// DJ
 1886, 	// TJ
 1600, 	// KS
 1810, 	// i1
 1892, 	// e1
 758, 	// 01
 615, 	// u1
 1424, 	// y1
 -90, 	// ER
// ==== F3 ====
 -1, 	// _
 2801, 	// A
 2460, 	// E
 2417, 	// AE
 2600, 	// EX
 2848, 	// I
 2750, 	// O
 2017, 	// OE
 -96, 	// U
 -100, 	// UE
 2638, 	// AH
 2665, 	// EH
 2517, 	// AZ
 3000, 	// IH
 2927, 	// OH
 2294, 	// OZ
 -104, 	// UH
 2054, 	// UZ
 -108, 	// EI
 -116, 	// AU
 -122, 	// EU
 2605, 	// AN
 2402, 	// IM
 2385, 	// UM
 2723, 	// ON
 3050, 	// J
 2523, 	// L
 3050, 	// RR
 2600, 	// R
 -1, 	// H
 2100, 	// M
 2400, 	// N
 2600, 	// NG
 2700, 	// EL
 -132, 	// EM
 -138, 	// EN
 2580, 	// F
 2580, 	// V
 2550, 	// S
 2620, 	// Z
 2550, 	// SH
 2550, 	// ZH
 3003, 	// CH
 2256, 	// KH
 2150, 	// P
 2150, 	// B
 2679, 	// T
 2600, 	// D
 2250, 	// K
 2500, 	// G
 -1, 	// Q
 2670, 	// PF
 2710, 	// TS
 2600, 	// DJ
 2731, 	// TJ
 2600, 	// KS
 2760, 	// i1
 2624, 	// e1
 2680, 	// 01
 2765, 	// u1
 2177, 	// y1
 -142, 	// ER
// ==== B1 ====
 -1, 	// _
 90, 	// A
 90, 	// E
 90, 	// AE
 130, 	// EX
 80, 	// I
 90, 	// O
 90, 	// OE
 160, 	// U
 120, 	// UE
 110, 	// AH
 80, 	// EH
 80, 	// AZ
 90, 	// IH
 90, 	// OH
 90, 	// OZ
 160, 	// UH
 80, 	// UZ
 100, 	// EI
 85, 	// AU
 90, 	// EU
 200, 	// AN
 200, 	// IM
 200, 	// UM
 200, 	// ON
 70, 	// J
 110, 	// L
 220, 	// RR
 180, 	// R
 90, 	// H
 110, 	// M
 90, 	// N
 90, 	// NG
 90, 	// EL
 90, 	// EM
 90, 	// EN
 300, 	// F
 160, 	// V
 150, 	// S
 140, 	// Z
 200, 	// SH
 100, 	// ZH
 150, 	// CH
 180, 	// KH
 300, 	// P
 150, 	// B
 180, 	// T
 130, 	// D
 200, 	// K
 90, 	// G
 130, 	// Q
 300, 	// PF
 300, 	// TS
 300, 	// DJ
 220, 	// TJ
 300, 	// KS
 80, 	// i1
 120, 	// e1
 120, 	// 01
 90, 	// u1
 90, 	// y1
 -148, 	// ER
// ==== B2 ====
 -1, 	// _
 110, 	// A
 120, 	// E
 120, 	// AE
 120, 	// EX
 140, 	// I
 90, 	// O
 70, 	// OE
 120, 	// U
 100, 	// UE
 150, 	// AH
 120, 	// EH
 120, 	// AZ
 150, 	// IH
 110, 	// OH
 110, 	// OZ
 90, 	// UH
 100, 	// UZ
 120, 	// EI
 90, 	// AU
 120, 	// EU
 200, 	// AN
 200, 	// IM
 200, 	// UM
 200, 	// ON
 200, 	// J
 120, 	// L
 250, 	// RR
 180, 	// R
 120, 	// H
 450, 	// M
 250, 	// N
 300, 	// NG
 110, 	// EL
 240, 	// EM
 280, 	// EN
 260, 	// F
 500, 	// V
 280, 	// S
 210, 	// Z
 240, 	// SH
 160, 	// ZH
 250, 	// CH
 100, 	// KH
 180, 	// P
 160, 	// B
 150, 	// T
 250, 	// D
 200, 	// K
 120, 	// G
 240, 	// Q
 250, 	// PF
 150, 	// TS
 150, 	// DJ
 190, 	// TJ
 150, 	// KS
 120, 	// i1
 160, 	// e1
 80, 	// 01
 120, 	// u1
 120, 	// y1
 -154, 	// ER
// ==== B3 ====
 -1, 	// _
 250, 	// A
 250, 	// E
 220, 	// AE
 220, 	// EX
 220, 	// I
 120, 	// O
 230, 	// OE
 160, 	// U
 150, 	// UE
 220, 	// AH
 240, 	// EH
 220, 	// AZ
 160, 	// IH
 120, 	// OH
 150, 	// OZ
 150, 	// UH
 150, 	// UZ
 200, 	// EI
 150, 	// AU
 220, 	// EU
 300, 	// AN
 300, 	// IM
 300, 	// UM
 300, 	// ON
 300, 	// J
 150, 	// L
 300, 	// RR
 280, 	// R
 170, 	// H
 350, 	// M
 350, 	// N
 220, 	// NG
 250, 	// EL
 350, 	// EM
 350, 	// EN
 300, 	// F
 500, 	// V
 500, 	// S
 300, 	// Z
 300, 	// SH
 300, 	// ZH
 250, 	// CH
 500, 	// KH
 180, 	// P
 200, 	// B
 250, 	// T
 250, 	// D
 280, 	// K
 180, 	// G
 260, 	// Q
 350, 	// PF
 250, 	// TS
 250, 	// DJ
 250, 	// TJ
 250, 	// KS
 160, 	// i1
 180, 	// e1
 170, 	// 01
 160, 	// u1
 160, 	// y1
 250, 	// ER
// ==== AV ====
 0, 	// _
 62, 	// A
 65, 	// E
 65, 	// AE
 65, 	// EX
 65, 	// I
 65, 	// O
 65, 	// OE
 65, 	// U
 65, 	// UE
 63, 	// AH
 60, 	// EH
 65, 	// AZ
 65, 	// IH
 60, 	// OH
 65, 	// OZ
 65, 	// UH
 65, 	// UZ
 65, 	// EI
 63, 	// AU
 65, 	// EU
 65, 	// AN
 65, 	// IM
 65, 	// UM
 65, 	// ON
 60, 	// J
 65, 	// L
 65, 	// RR
 65, 	// R
 0, 	// H
 63, 	// M
 58, 	// N
 63, 	// NG
 60, 	// EL
 60, 	// EM
 60, 	// EN
 0, 	// F
 63, 	// V
 0, 	// S
 43, 	// Z
 0, 	// SH
 43, 	// ZH
 0, 	// CH
 0, 	// KH
 0, 	// P
 0, 	// B
 0, 	// T
 0, 	// D
 0, 	// K
 0, 	// G
 51, 	// Q
 0, 	// PF
 0, 	// TS
 56, 	// DJ
 0, 	// TJ
 0, 	// KS
 65, 	// i1
 55, 	// e1
 65, 	// 01
 65, 	// u1
 65, 	// y1
 63 };	// ER

// Female - F1,F2,F3,B1,B2,B3,AV data for each phoneme
//     Negative numbers are offsets into femdip table (multi-part formants)
//     Positive numbers are actual values
const short gr_femtar_def[] = {
// ==== F1 ====
 -1, 	// _
 751, 	// A
 592, 	// E
 860, 	// AE
 390, 	// EX
 393, 	// I
 700, 	// O
 520, 	// OE
 440, 	// U
 374, 	// UE
 779, 	// AH
 431, 	// EH
 553, 	// AZ
 329, 	// IH
 430, 	// OH
 438, 	// OZ
 350, 	// UH
 342, 	// UZ
 -2, 	// EI
 -8, 	// AU
 -14, 	// EU
 550, 	// AN
 550, 	// IM
 510, 	// UM
 590, 	// ON
 300, 	// J
 350, 	// L
 650, 	// RR
 723, 	// R
 -1, 	// H
 420, 	// M
 250, 	// N
 420, 	// NG
 440, 	// EL
 420, 	// EM
 420, 	// EN
 360, 	// F
 390, 	// V
 380, 	// S
 207, 	// Z
 190, 	// SH
 500, 	// ZH
 350, 	// CH
 864, 	// KH
 400, 	// P
 362, 	// B
 400, 	// T
 380, 	// D
 600, 	// K
 210, 	// G
 -1, 	// Q
 350, 	// PF
 290, 	// TS
 260, 	// DJ
 350, 	// TJ
 350, 	// KS
 -1, 	// i1
 -1, 	// e1
 -1, 	// 01
 -1, 	// u1
 -1, 	// y1
 300, 	// ER
// ==== F2 ====
 -1, 	// _
 1460, 	// A
 1944, 	// E
 2050, 	// AE
 1400, 	// EX
 2040, 	// I
 1000, 	// O
 1373, 	// OE
 1020, 	// U
 1431, 	// UE
 1347, 	// AH
 2241, 	// EH
 2368, 	// AZ
 2316, 	// IH
 729, 	// OH
 953, 	// OZ
 1048, 	// UH
 1667, 	// UZ
 -20, 	// EI
 -24, 	// AU
 -28, 	// EU
 1100, 	// AN
 1700, 	// IM
 1200, 	// UM
 800, 	// ON
 2447, 	// J
 1350, 	// L
 1583, 	// RR
 1599, 	// R
 -1, 	// H
 1451, 	// M
 1884, 	// N
 1470, 	// NG
 1300, 	// EL
 1270, 	// EM
 1340, 	// EN
 1997, 	// F
 1676, 	// V
 1800, 	// S
 1711, 	// Z
 2000, 	// SH
 1850, 	// ZH
 2790, 	// CH
 1365, 	// KH
 800, 	// P
 1901, 	// B
 2247, 	// T
 1850, 	// D
 2020, 	// K
 2100, 	// G
 -1, 	// Q
 1100, 	// PF
 2000, 	// TS
 1900, 	// DJ
 1600, 	// TJ
 1900, 	// KS
 -1, 	// i1
 -1, 	// e1
 -1, 	// 01
 -1, 	// u1
 -1, 	// y1
 1700, 	// ER
// ==== F3 ====
 -1, 	// _
 2841, 	// A
 2867, 	// E
 2850, 	// AE
 2625, 	// EX
 2667, 	// I
 2617, 	// O
 2120, 	// OE
 2240, 	// U
 2284, 	// UE
 2785, 	// AH
 2871, 	// EH
 2973, 	// AZ
 2796, 	// IH
 2900, 	// OH
 2835, 	// OZ
 2760, 	// UH
 2585, 	// UZ
 -34, 	// EI
 -38, 	// AU
 -44, 	// EU
 2400, 	// AN
 2800, 	// IM
 2800, 	// UM
 3000, 	// ON
 2900, 	// J
 2650, 	// L
 3300, 	// RR
 2644, 	// R
 -1, 	// H
 2575, 	// M
 3024, 	// N
 3000, 	// NG
 2500, 	// EL
 2130, 	// EM
 2500, 	// EN
 2930, 	// F
 2523, 	// V
 3150, 	// S
 2740, 	// Z
 2800, 	// SH
 3000, 	// ZH
 3250, 	// CH
 2900, 	// KH
 1800, 	// P
 2782, 	// B
 3020, 	// T
 3100, 	// D
 2600, 	// K
 3029, 	// G
 -1, 	// Q
 2150, 	// PF
 3100, 	// TS
 2600, 	// DJ
 2600, 	// TJ
 2600, 	// KS
 -1, 	// i1
 -1, 	// e1
 -1, 	// 01
 -1, 	// u1
 -1, 	// y1
 2600, 	// ER
// ==== B1 ====
 300, 	// _
 130, 	// A
 160, 	// E
 130, 	// AE
 160, 	// EX
 70, 	// I
 120, 	// O
 70, 	// OE
 160, 	// U
 220, 	// UE
 90, 	// AH
 50, 	// EH
 70, 	// AZ
 130, 	// IH
 70, 	// OH
 70, 	// OZ
 70, 	// UH
 100, 	// UZ
 90, 	// EI
 70, 	// AU
 -50, 	// EU
 200, 	// AN
 200, 	// IM
 200, 	// UM
 200, 	// ON
 70, 	// J
 110, 	// L
 500, 	// RR
 90, 	// R
 400, 	// H
 90, 	// M
 70, 	// N
 90, 	// NG
 70, 	// EL
 90, 	// EM
 90, 	// EN
 300, 	// F
 200, 	// V
 300, 	// S
 80, 	// Z
 300, 	// SH
 300, 	// ZH
 300, 	// CH
 150, 	// KH
 300, 	// P
 150, 	// B
 300, 	// T
 150, 	// D
 300, 	// K
 150, 	// G
 -1, 	// Q
 300, 	// PF
 300, 	// TS
 70, 	// DJ
 300, 	// TJ
 300, 	// KS
 -1, 	// i1
 -1, 	// e1
 -1, 	// 01
 -1, 	// u1
 -1, 	// y1
 -1, 	// ER
// ==== B2 ====
 300, 	// _
 170, 	// A
 120, 	// E
 150, 	// AE
 140, 	// EX
 120, 	// I
 120, 	// O
 170, 	// OE
 80, 	// U
 170, 	// UE
 160, 	// AH
 110, 	// EH
 150, 	// AZ
 90, 	// IH
 130, 	// OH
 140, 	// OZ
 70, 	// UH
 70, 	// UZ
 160, 	// EI
 90, 	// AU
 -54, 	// EU
 200, 	// AN
 200, 	// IM
 200, 	// UM
 200, 	// ON
 90, 	// J
 100, 	// L
 400, 	// RR
 230, 	// R
 300, 	// H
 240, 	// M
 350, 	// N
 250, 	// NG
 90, 	// EL
 240, 	// EM
 300, 	// EN
 120, 	// F
 300, 	// V
 180, 	// S
 120, 	// Z
 100, 	// SH
 100, 	// ZH
 200, 	// CH
 150, 	// KH
 180, 	// P
 80, 	// B
 120, 	// T
 100, 	// D
 460, 	// K
 120, 	// G
 -1, 	// Q
 180, 	// PF
 150, 	// TS
 150, 	// DJ
 150, 	// TJ
 150, 	// KS
 -1, 	// i1
 -1, 	// e1
 -1, 	// 01
 -1, 	// u1
 -1, 	// y1
 -1, 	// ER
// ==== B3 ====
 300, 	// _
 80, 	// A
 200, 	// E
 180, 	// AE
 140, 	// EX
 150, 	// I
 180, 	// O
 150, 	// OE
 170, 	// U
 150, 	// UE
 90, 	// AH
 180, 	// EH
 170, 	// AZ
 120, 	// IH
 50, 	// OH
 90, 	// OZ
 90, 	// UH
 80, 	// UZ
 190, 	// EI
 150, 	// AU
 -58, 	// EU
 300, 	// AN
 300, 	// IM
 300, 	// UM
 300, 	// ON
 150, 	// J
 130, 	// L
 500, 	// RR
 350, 	// R
 300, 	// H
 420, 	// M
 540, 	// N
 400, 	// NG
 150, 	// EL
 420, 	// EM
 460, 	// EN
 150, 	// F
 300, 	// V
 300, 	// S
 200, 	// Z
 300, 	// SH
 300, 	// ZH
 300, 	// CH
 300, 	// KH
 180, 	// P
 130, 	// B
 90, 	// T
 240, 	// D
 580, 	// K
 180, 	// G
 -1, 	// Q
 180, 	// PF
 250, 	// TS
 250, 	// DJ
 250, 	// TJ
 250, 	// KS
 -1, 	// i1
 -1, 	// e1
 -1, 	// 01
 -1, 	// u1
 -1, 	// y1
 -1, 	// ER
// ==== AV ====
 0, 	// _
 57, 	// A
 59, 	// E
 59, 	// AE
 57, 	// EX
 58, 	// I
 58, 	// O
 58, 	// OE
 59, 	// U
 59, 	// UE
 56, 	// AH
 59, 	// EH
 59, 	// AZ
 58, 	// IH
 56, 	// OH
 58, 	// OZ
 60, 	// UH
 60, 	// UZ
 59, 	// EI
 55, 	// AU
 58, 	// EU
 58, 	// AN
 58, 	// IM
 58, 	// UM
 60, 	// ON
 52, 	// J
 55, 	// L
 45, 	// RR
 56, 	// R
 0, 	// H
 53, 	// M
 53, 	// N
 53, 	// NG
 57, 	// EL
 59, 	// EM
 57, 	// EN
 0, 	// F
 54, 	// V
 0, 	// S
 55, 	// Z
 0, 	// SH
 60, 	// ZH
 0, 	// CH
 0, 	// KH
 0, 	// P
 0, 	// B
 0, 	// T
 0, 	// D
 0, 	// K
 20, 	// G
 0, 	// Q
 0, 	// PF
 0, 	// TS
 46, 	// DJ
 0, 	// TJ
 0, 	// KS
 57, 	// i1
 57, 	// e1
 57, 	// 01
 57, 	// u1
 57, 	// y1
 57 };	// ER

// Male - F1,F1T,F2,F2T,F3,F3T,B1,B1T,B2,B2T,B3,B3T,AV,AVT data for Multi-part formants
const short gr_maldip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _
 0, 	// _
 440, 	// U F1
 10, 	// U F1 duration
 380, 	// U F1
 -1, 	// U F1 duration
 395, 	// UE F1
 4, 	// UE F1 duration
 370, 	// UE F1
 -1, 	// UE F1 duration
 590, 	// EI F1
 10, 	// EI F1 duration
 622, 	// EI F1
 56, 	// EI F1 duration
 493, 	// EI F1
 120, 	// EI F1 duration
 471, 	// EI F1
 -1, 	// EI F1 duration
 720, 	// AU F1
 40, 	// AU F1 duration
 480, 	// AU F1
 150, 	// AU F1 duration
 475, 	// AU F1
 -1, 	// AU F1 duration
 515, 	// EU F1
 20, 	// EU F1 duration
 490, 	// EU F1
 70, 	// EU F1 duration
 451, 	// EU F1
 -1, 	// EU F1 duration
 470, 	// EM F1
 10, 	// EM F1 duration
 301, 	// EM F1
 30, 	// EM F1 duration
 279, 	// EM F1
 -1, 	// EM F1 duration
 420, 	// EN F1
 25, 	// EN F1 duration
 310, 	// EN F1
 45, 	// EN F1 duration
 279, 	// EN F1
 -1, 	// EN F1 duration
 590, 	// ER F1
 10, 	// ER F1 duration
 558, 	// ER F1
 50, 	// ER F1 duration
 540, 	// ER F1
 -1, 	// ER F1 duration
 866, 	// U F2
 10, 	// U F2 duration
 750, 	// U F2
 -1, 	// U F2 duration
 1421, 	// UE F2
 4, 	// UE F2 duration
 1497, 	// UE F2
 -1, 	// UE F2 duration
 1094, 	// EI F2
 18, 	// EI F2 duration
 1201, 	// EI F2
 50, 	// EI F2 duration
 1609, 	// EI F2
 98, 	// EI F2 duration
 1801, 	// EI F2
 -1, 	// EI F2 duration
 1280, 	// AU F2
 40, 	// AU F2 duration
 820, 	// AU F2
 150, 	// AU F2 duration
 810, 	// AU F2
 -1, 	// AU F2 duration
 843, 	// EU F2
 20, 	// EU F2 duration
 850, 	// EU F2
 65, 	// EU F2 duration
 1651, 	// EU F2
 115, 	// EU F2 duration
 1716, 	// EU F2
 -1, 	// EU F2 duration
 2000, 	// EM F2
 10, 	// EM F2 duration
 2000, 	// EM F2
 45, 	// EM F2 duration
 2000, 	// EM F2
 -1, 	// EM F2 duration
 1500, 	// EN F2
 20, 	// EN F2 duration
 1500, 	// EN F2
 50, 	// EN F2 duration
 1500, 	// EN F2
 -1, 	// EN F2 duration
 1330, 	// ER F2
 10, 	// ER F2 duration
 1287, 	// ER F2
 60, 	// ER F2 duration
 1245, 	// ER F2
 -1, 	// ER F2 duration
 2451, 	// U F3
 10, 	// U F3 duration
 2451, 	// U F3
 -1, 	// U F3 duration
 2224, 	// UE F3
 4, 	// UE F3 duration
 2380, 	// UE F3
 -1, 	// UE F3 duration
 2239, 	// UH F3
 10, 	// UH F3 duration
 2250, 	// UH F3
 -1, 	// UH F3 duration
 2660, 	// EI F3
 15, 	// EI F3 duration
 2617, 	// EI F3
 50, 	// EI F3 duration
 2381, 	// EI F3
 90, 	// EI F3 duration
 2510, 	// EI F3
 -1, 	// EI F3 duration
 2580, 	// AU F3
 30, 	// AU F3 duration
 2800, 	// AU F3
 150, 	// AU F3 duration
 2830, 	// AU F3
 -1, 	// AU F3 duration
 2705, 	// EU F3
 30, 	// EU F3 duration
 2700, 	// EU F3
 60, 	// EU F3 duration
 2305, 	// EU F3
 90, 	// EU F3 duration
 2400, 	// EU F3
 130, 	// EU F3 duration
 2553, 	// EU F3
 -1, 	// EU F3 duration
 2630, 	// EM F3
 10, 	// EM F3 duration
 2563, 	// EM F3
 30, 	// EM F3 duration
 2553, 	// EM F3
 -1, 	// EM F3 duration
 2224, 	// EN F3
 10, 	// EN F3 duration
 2221, 	// EN F3
 -1, 	// EN F3 duration
 2466, 	// ER F3
 10, 	// ER F3 duration
 2501, 	// ER F3
 50, 	// ER F3 duration
 2510, 	// ER F3
 -1, 	// ER F3 duration
// ====== Bandwidths and duration ======
 90, 	// ER B1
 10, 	// ER B1 duration
 160, 	// ER B1
 50, 	// ER B1 duration
 180, 	// ER B1
 -1, 	// ER B1 duration
 120, 	// ER B2
 10, 	// ER B2 duration
 140, 	// ER B2
 -1, 	// ER B2 duration
// ====== Amplitude of Voicing ======
 0};

// Female diphthongs
const short gr_femdip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _
 0, 	// _
 721, 	// EI F1
 10, 	// EI F1 duration
 499, 	// EI F1
 160, 	// EI F1 duration
 499, 	// EI F1
 -1, 	// EI F1 duration
 707, 	// AU F1
 10, 	// AU F1 duration
 456, 	// AU F1
 164, 	// AU F1 duration
 440, 	// AU F1
 -1, 	// AU F1 duration
 550, 	// EU F1
 53, 	// EU F1 duration
 500, 	// EU F1
 115, 	// EU F1 duration
 430, 	// EU F1
 -1, 	// EU F1 duration
 1527, 	// EI F2
 10, 	// EI F2 duration
 2006, 	// EI F2
 -1, 	// EI F2 duration
 1198, 	// AU F2
 10, 	// AU F2 duration
 1068, 	// AU F2
 -1, 	// AU F2 duration
 1210, 	// EU F2
 53, 	// EU F2 duration
 1781, 	// EU F2
 115, 	// EU F2 duration
 2020, 	// EU F2
 -1, 	// EU F2 duration
 2849, 	// EI F3
 10, 	// EI F3 duration
 2873, 	// EI F3
 -1, 	// EI F3 duration
 2876, 	// AU F3
 10, 	// AU F3 duration
 2929, 	// AU F3
 120, 	// AU F3 duration
 2929, 	// AU F3
 -1, 	// AU F3 duration
 2815, 	// EU F3
 53, 	// EU F3 duration
 2681, 	// EU F3
 115, 	// EU F3 duration
 2981, 	// EU F3
 -1, 	// EU F3 duration
// ====== Bandwidths and duration ======
 75, 	// EU B1
 8, 	// EU B1 duration
 120, 	// EU B1
 -1, 	// EU B1 duration
 120, 	// EU B2
 8, 	// EU B2 duration
 180, 	// EU B2
 -1, 	// EU B2 duration
 120, 	// EU B3
 8, 	// EU B3 duration
 220, 	// EU B3
 -1, 	// EU B3 duration
// ====== Amplitude of Voicing ======
 0};

// Offsets into Amplitude data
const short gr_ptram_def[] = {
 0, 	// _
 0, 	// A
 0, 	// E
 0, 	// AE
 0, 	// EX
 0, 	// I
 0, 	// O
 0, 	// OE
 0, 	// U
 0, 	// UE
 0, 	// AH
 0, 	// EH
 0, 	// AZ
 0, 	// IH
 0, 	// OH
 0, 	// OZ
 0, 	// UH
 0, 	// UZ
 0, 	// EI
 0, 	// AU
 0, 	// EU
 0, 	// AN
 0, 	// IM
 0, 	// UM
 0, 	// ON
 0, 	// J
 0, 	// L
 1, 	// RR
 0, 	// R
 0, 	// H
 0, 	// M
 0, 	// N
 0, 	// NG
 0, 	// EL
 0, 	// EM
 0, 	// EN
 31, 	// F
 61, 	// V
 91, 	// S
 121, 	// Z
 151, 	// SH
 181, 	// ZH
 211, 	// CH
 241, 	// KH
 271, 	// P
 301, 	// B
 331, 	// T
 361, 	// D
 391, 	// K
 421, 	// G
 0, 	// Q
 451, 	// PF
 481, 	// TS
 511, 	// DJ
 541, 	// TJ
 571, 	// KS
 0, 	// i1
 0, 	// e1
 0, 	// 01
 0, 	// u1
 0, 	// y1
 0 };	// ER

// Offsets into Locus data
const short gr_plocu_def[] = {
// ==== Front ====
 0, 	// _
 0, 	// A
 0, 	// E
 0, 	// AE
 0, 	// EX
 0, 	// I
 0, 	// O
 0, 	// OE
 0, 	// U
 0, 	// UE
 0, 	// AH
 0, 	// EH
 0, 	// AZ
 0, 	// IH
 0, 	// OH
 0, 	// OZ
 0, 	// UH
 0, 	// UZ
 0, 	// EI
 0, 	// AU
 0, 	// EU
 0, 	// AN
 0, 	// IM
 0, 	// UM
 0, 	// ON
 0, 	// J
 0, 	// L
 0, 	// RR
 0, 	// R
 0, 	// H
 1, 	// M
 10, 	// N
 19, 	// NG
 0, 	// EL
 0, 	// EM
 0, 	// EN
 28, 	// F
 37, 	// V
 46, 	// S
 55, 	// Z
 64, 	// SH
 73, 	// ZH
 82, 	// CH
 91, 	// KH
 100, 	// P
 109, 	// B
 118, 	// T
 127, 	// D
 136, 	// K
 145, 	// G
 0, 	// Q
 154, 	// PF
 163, 	// TS
 172, 	// DJ
 181, 	// TJ
 190, 	// KS
 0, 	// i1
 0, 	// e1
 0, 	// 01
 0, 	// u1
 0, 	// y1
 0, 	// ER
// ==== Back ====
 0, 	// _
 0, 	// A
 0, 	// E
 0, 	// AE
 0, 	// EX
 0, 	// I
 0, 	// O
 0, 	// OE
 0, 	// U
 0, 	// UE
 0, 	// AH
 0, 	// EH
 0, 	// AZ
 0, 	// IH
 0, 	// OH
 0, 	// OZ
 0, 	// UH
 0, 	// UZ
 0, 	// EI
 0, 	// AU
 0, 	// EU
 0, 	// AN
 0, 	// IM
 0, 	// UM
 0, 	// ON
 0, 	// J
 0, 	// L
 0, 	// RR
 0, 	// R
 0, 	// H
 199, 	// M
 208, 	// N
 217, 	// NG
 0, 	// EL
 0, 	// EM
 0, 	// EN
 226, 	// F
 235, 	// V
 244, 	// S
 253, 	// Z
 262, 	// SH
 271, 	// ZH
 280, 	// CH
 289, 	// KH
 298, 	// P
 307, 	// B
 316, 	// T
 325, 	// D
 334, 	// K
 343, 	// G
 0, 	// Q
 352, 	// PF
 361, 	// TS
 370, 	// DJ
 379, 	// TJ
 388, 	// KS
 0, 	// i1
 0, 	// e1
 0, 	// 01
 0, 	// u1
 0, 	// y1
 0, 	// ER
// ==== Round ====
 0, 	// _
 0, 	// A
 0, 	// E
 0, 	// AE
 0, 	// EX
 0, 	// I
 0, 	// O
 0, 	// OE
 0, 	// U
 0, 	// UE
 0, 	// AH
 0, 	// EH
 0, 	// AZ
 0, 	// IH
 0, 	// OH
 0, 	// OZ
 0, 	// UH
 0, 	// UZ
 0, 	// EI
 0, 	// AU
 0, 	// EU
 0, 	// AN
 0, 	// IM
 0, 	// UM
 0, 	// ON
 0, 	// J
 0, 	// L
 0, 	// RR
 0, 	// R
 0, 	// H
 397, 	// M
 406, 	// N
 415, 	// NG
 0, 	// EL
 0, 	// EM
 0, 	// EN
 424, 	// F
 433, 	// V
 442, 	// S
 451, 	// Z
 460, 	// SH
 469, 	// ZH
 478, 	// CH
 487, 	// KH
 496, 	// P
 505, 	// B
 514, 	// T
 523, 	// D
 532, 	// K
 541, 	// G
 0, 	// Q
 550, 	// PF
 559, 	// TS
 568, 	// DJ
 577, 	// TJ
 586, 	// KS
 0, 	// i1
 0, 	// e1
 0, 	// 01
 0, 	// u1
 0, 	// y1
 0, 	// ER
// ==== Low ====
 0, 	// _
 0, 	// A
 0, 	// E
 0, 	// AE
 0, 	// EX
 0, 	// I
 0, 	// O
 0, 	// OE
 0, 	// U
 0, 	// UE
 0, 	// AH
 0, 	// EH
 0, 	// AZ
 0, 	// IH
 0, 	// OH
 0, 	// OZ
 0, 	// UH
 0, 	// UZ
 0, 	// EI
 0, 	// AU
 0, 	// EU
 0, 	// AN
 0, 	// IM
 0, 	// UM
 0, 	// ON
 0, 	// J
 595, 	// L
 0, 	// RR
 0, 	// R
 0, 	// H
 604, 	// M
 613, 	// N
 622, 	// NG
 0, 	// EL
 0, 	// EM
 0, 	// EN
 631, 	// F
 640, 	// V
 649, 	// S
 658, 	// Z
 667, 	// SH
 676, 	// ZH
 685, 	// CH
 694, 	// KH
 703, 	// P
 712, 	// B
 721, 	// T
 730, 	// D
 739, 	// K
 748, 	// G
 757, 	// Q
 766, 	// PF
 775, 	// TS
 784, 	// DJ
 793, 	// TJ
 802, 	// KS
 0, 	// i1
 0, 	// e1
 0, 	// 01
 0, 	// u1
 0, 	// y1
 0 };	// ER

// Male Locus data
const short gr_maleloc_def[] = {
 0, 
// Front
 350, 	// M F1 locus
 30, 	// M percent
 30, 	// M transition duration
 1200, 	// M F2 locus
 10, 	// M percent
 35, 	// M transition duration
 2500, 	// M F3 locus
 30, 	// M percent
 40, 	// M transition duration
 450, 	// N F1 locus
 20, 	// N percent
 35, 	// N transition duration
 1700, 	// N F2 locus
 40, 	// N percent
 45, 	// N transition duration
 2400, 	// N F3 locus
 35, 	// N percent
 45, 	// N transition duration
 280, 	// NG F1 locus
 25, 	// NG percent
 40, 	// NG transition duration
 1600, 	// NG F2 locus
 20, 	// NG percent
 70, 	// NG transition duration
 2250, 	// NG F3 locus
 20, 	// NG percent
 70, 	// NG transition duration
 300, 	// F F1 locus
 58, 	// F percent
 20, 	// F transition duration
 1400, 	// F F2 locus
 40, 	// F percent
 35, 	// F transition duration
 2500, 	// F F3 locus
 35, 	// F percent
 30, 	// F transition duration
 325, 	// V F1 locus
 30, 	// V percent
 30, 	// V transition duration
 1119, 	// V F2 locus
 75, 	// V percent
 25, 	// V transition duration
 2500, 	// V F3 locus
 50, 	// V percent
 40, 	// V transition duration
 317, 	// S F1 locus
 40, 	// S percent
 40, 	// S transition duration
 1240, 	// S F2 locus
 35, 	// S percent
 50, 	// S transition duration
 2550, 	// S F3 locus
 0, 	// S percent
 70, 	// S transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1240, 	// Z F2 locus
 35, 	// Z percent
 50, 	// Z transition duration
 2550, 	// Z F3 locus
 0, 	// Z percent
 70, 	// Z transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1830, 	// SH F2 locus
 30, 	// SH percent
 70, 	// SH transition duration
 2640, 	// SH F3 locus
 51, 	// SH percent
 70, 	// SH transition duration
 285, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 1700, 	// ZH F2 locus
 27, 	// ZH percent
 70, 	// ZH transition duration
 2270, 	// ZH F3 locus
 0, 	// ZH percent
 85, 	// ZH transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1750, 	// CH F2 locus
 25, 	// CH percent
 70, 	// CH transition duration
 2750, 	// CH F3 locus
 19, 	// CH percent
 70, 	// CH transition duration
 300, 	// KH F1 locus
 72, 	// KH percent
 20, 	// KH transition duration
 1869, 	// KH F2 locus
 99, 	// KH percent
 80, 	// KH transition duration
 2569, 	// KH F3 locus
 63, 	// KH percent
 50, 	// KH transition duration
 350, 	// P F1 locus
 55, 	// P percent
 20, 	// P transition duration
 950, 	// P F2 locus
 56, 	// P percent
 30, 	// P transition duration
 2200, 	// P F3 locus
 25, 	// P percent
 45, 	// P transition duration
 350, 	// B F1 locus
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
 1800, 	// T F2 locus
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
 320, 	// K F1 locus
 33, 	// K percent
 50, 	// K transition duration
 1990, 	// K F2 locus
 20, 	// K percent
 55, 	// K transition duration
 3000, 	// K F3 locus
 125, 	// K percent
 50, 	// K transition duration
 250, 	// G F1 locus
 33, 	// G percent
 45, 	// G transition duration
 1990, 	// G F2 locus
 20, 	// G percent
 50, 	// G transition duration
 3000, 	// G F3 locus
 40, 	// G percent
 50, 	// G transition duration
 265, 	// PF F1 locus
 80, 	// PF percent
 30, 	// PF transition duration
 1350, 	// PF F2 locus
 80, 	// PF percent
 40, 	// PF transition duration
 2670, 	// PF F3 locus
 80, 	// PF percent
 40, 	// PF transition duration
 245, 	// TS F1 locus
 80, 	// TS percent
 30, 	// TS transition duration
 1900, 	// TS F2 locus
 47, 	// TS percent
 40, 	// TS transition duration
 2727, 	// TS F3 locus
 40, 	// TS percent
 40, 	// TS transition duration
 335, 	// DJ F1 locus
 78, 	// DJ percent
 30, 	// DJ transition duration
 2200, 	// DJ F2 locus
 71, 	// DJ percent
 30, 	// DJ transition duration
 2402, 	// DJ F3 locus
 8, 	// DJ percent
 30, 	// DJ transition duration
 245, 	// TJ F1 locus
 80, 	// TJ percent
 30, 	// TJ transition duration
 1886, 	// TJ F2 locus
 50, 	// TJ percent
 40, 	// TJ transition duration
 2731, 	// TJ F3 locus
 50, 	// TJ percent
 40, 	// TJ transition duration
 240, 	// KS F1 locus
 80, 	// KS percent
 50, 	// KS transition duration
 2306, 	// KS F2 locus
 77, 	// KS percent
 70, 	// KS transition duration
 2377, 	// KS F3 locus
 54, 	// KS percent
 40, 	// KS transition duration
// Back
 350, 	// M F1 locus
 25, 	// M percent
 30, 	// M transition duration
 500, 	// M F2 locus
 25, 	// M percent
 40, 	// M transition duration
 1500, 	// M F3 locus
 40, 	// M percent
 30, 	// M transition duration
 450, 	// N F1 locus
 20, 	// N percent
 30, 	// N transition duration
 1720, 	// N F2 locus
 25, 	// N percent
 30, 	// N transition duration
 2400, 	// N F3 locus
 25, 	// N percent
 35, 	// N transition duration
 280, 	// NG F1 locus
 25, 	// NG percent
 40, 	// NG transition duration
 1600, 	// NG F2 locus
 42, 	// NG percent
 70, 	// NG transition duration
 2159, 	// NG F3 locus
 20, 	// NG percent
 70, 	// NG transition duration
 335, 	// F F1 locus
 60, 	// F percent
 30, 	// F transition duration
 400, 	// F F2 locus
 60, 	// F percent
 45, 	// F transition duration
 2300, 	// F F3 locus
 40, 	// F percent
 40, 	// F transition duration
 335, 	// V F1 locus
 60, 	// V percent
 30, 	// V transition duration
 1400, 	// V F2 locus
 60, 	// V percent
 35, 	// V transition duration
 2300, 	// V F3 locus
 50, 	// V percent
 40, 	// V transition duration
 310, 	// S F1 locus
 40, 	// S percent
 35, 	// S transition duration
 1240, 	// S F2 locus
 40, 	// S percent
 50, 	// S transition duration
 2680, 	// S F3 locus
 0, 	// S percent
 70, 	// S transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1240, 	// Z F2 locus
 33, 	// Z percent
 60, 	// Z transition duration
 2630, 	// Z F3 locus
 0, 	// Z percent
 70, 	// Z transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1700, 	// SH F2 locus
 27, 	// SH percent
 70, 	// SH transition duration
 2270, 	// SH F3 locus
 0, 	// SH percent
 85, 	// SH transition duration
 285, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 1700, 	// ZH F2 locus
 27, 	// ZH percent
 70, 	// ZH transition duration
 2270, 	// ZH F3 locus
 0, 	// ZH percent
 85, 	// ZH transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 50, 	// CH transition duration
 1780, 	// CH F2 locus
 16, 	// CH percent
 60, 	// CH transition duration
 2100, 	// CH F3 locus
 0, 	// CH percent
 90, 	// CH transition duration
 500, 	// KH F1 locus
 50, 	// KH percent
 20, 	// KH transition duration
 1300, 	// KH F2 locus
 99, 	// KH percent
 80, 	// KH transition duration
 2570, 	// KH F3 locus
 93, 	// KH percent
 50, 	// KH transition duration
 350, 	// P F1 locus
 25, 	// P percent
 45, 	// P transition duration
 950, 	// P F2 locus
 56, 	// P percent
 30, 	// P transition duration
 2140, 	// P F3 locus
 25, 	// P percent
 45, 	// P transition duration
 350, 	// B F1 locus
 55, 	// B percent
 20, 	// B transition duration
 920, 	// B F2 locus
 46, 	// B percent
 30, 	// B transition duration
 2250, 	// B F3 locus
 40, 	// B percent
 50, 	// B transition duration
 320, 	// T F1 locus
 45, 	// T percent
 50, 	// T transition duration
 1700, 	// T F2 locus
 40, 	// T percent
 75, 	// T transition duration
 2600, 	// T F3 locus
 0, 	// T percent
 50, 	// T transition duration
 320, 	// D F1 locus
 43, 	// D percent
 50, 	// D transition duration
 1700, 	// D F2 locus
 40, 	// D percent
 75, 	// D transition duration
 2600, 	// D F3 locus
 0, 	// D percent
 50, 	// D transition duration
 320, 	// K F1 locus
 33, 	// K percent
 50, 	// K transition duration
 1800, 	// K F2 locus
 16, 	// K percent
 6, 	// K transition duration
 2150, 	// K F3 locus
 0, 	// K percent
 90, 	// K transition duration
 300, 	// G F1 locus
 55, 	// G percent
 50, 	// G transition duration
 1800, 	// G F2 locus
 16, 	// G percent
 60, 	// G transition duration
 2150, 	// G F3 locus
 0, 	// G percent
 90, 	// G transition duration
 260, 	// PF F1 locus
 85, 	// PF percent
 50, 	// PF transition duration
 1350, 	// PF F2 locus
 80, 	// PF percent
 50, 	// PF transition duration
 2675, 	// PF F3 locus
 85, 	// PF percent
 40, 	// PF transition duration
 253, 	// TS F1 locus
 65, 	// TS percent
 30, 	// TS transition duration
 1800, 	// TS F2 locus
 43, 	// TS percent
 40, 	// TS transition duration
 2700, 	// TS F3 locus
 18, 	// TS percent
 65, 	// TS transition duration
 200, 	// DJ F1 locus
 10, 	// DJ percent
 50, 	// DJ transition duration
 2200, 	// DJ F2 locus
 50, 	// DJ percent
 50, 	// DJ transition duration
 2171, 	// DJ F3 locus
 29, 	// DJ percent
 40, 	// DJ transition duration
 253, 	// TJ F1 locus
 50, 	// TJ percent
 50, 	// TJ transition duration
 1890, 	// TJ F2 locus
 50, 	// TJ percent
 65, 	// TJ transition duration
 2731, 	// TJ F3 locus
 50, 	// TJ percent
 40, 	// TJ transition duration
 221, 	// KS F1 locus
 43, 	// KS percent
 40, 	// KS transition duration
 2100, 	// KS F2 locus
 77, 	// KS percent
 70, 	// KS transition duration
 1700, 	// KS F3 locus
 80, 	// KS percent
 60, 	// KS transition duration
// Round
 350, 	// M F1 locus
 25, 	// M percent
 30, 	// M transition duration
 500, 	// M F2 locus
 50, 	// M percent
 35, 	// M transition duration
 1550, 	// M F3 locus
 40, 	// M percent
 40, 	// M transition duration
 450, 	// N F1 locus
 20, 	// N percent
 30, 	// N transition duration
 1500, 	// N F2 locus
 25, 	// N percent
 35, 	// N transition duration
 2420, 	// N F3 locus
 25, 	// N percent
 40, 	// N transition duration
 440, 	// NG F1 locus
 25, 	// NG percent
 40, 	// NG transition duration
 1600, 	// NG F2 locus
 42, 	// NG percent
 70, 	// NG transition duration
 1920, 	// NG F3 locus
 25, 	// NG percent
 70, 	// NG transition duration
 320, 	// F F1 locus
 60, 	// F percent
 30, 	// F transition duration
 1400, 	// F F2 locus
 60, 	// F percent
 35, 	// F transition duration
 2300, 	// F F3 locus
 50, 	// F percent
 40, 	// F transition duration
 320, 	// V F1 locus
 60, 	// V percent
 30, 	// V transition duration
 1400, 	// V F2 locus
 60, 	// V percent
 35, 	// V transition duration
 2300, 	// V F3 locus
 50, 	// V percent
 40, 	// V transition duration
 220, 	// S F1 locus
 80, 	// S percent
 90, 	// S transition duration
 1320, 	// S F2 locus
 15, 	// S percent
 60, 	// S transition duration
 2900, 	// S F3 locus
 60, 	// S percent
 90, 	// S transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1320, 	// Z F2 locus
 15, 	// Z percent
 60, 	// Z transition duration
 2460, 	// Z F3 locus
 0, 	// Z percent
 65, 	// Z transition duration
 340, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1630, 	// SH F2 locus
 27, 	// SH percent
 90, 	// SH transition duration
 2100, 	// SH F3 locus
 20, 	// SH percent
 110, 	// SH transition duration
 340, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 1630, 	// ZH F2 locus
 27, 	// ZH percent
 90, 	// ZH transition duration
 2100, 	// ZH F3 locus
 20, 	// ZH percent
 110, 	// ZH transition duration
 250, 	// CH F1 locus
 70, 	// CH percent
 20, 	// CH transition duration
 2300, 	// CH F2 locus
 60, 	// CH percent
 100, 	// CH transition duration
 3030, 	// CH F3 locus
 60, 	// CH percent
 60, 	// CH transition duration
 600, 	// KH F1 locus
 90, 	// KH percent
 20, 	// KH transition duration
 1300, 	// KH F2 locus
 99, 	// KH percent
 80, 	// KH transition duration
 2600, 	// KH F3 locus
 60, 	// KH percent
 40, 	// KH transition duration
 350, 	// P F1 locus
 45, 	// P percent
 25, 	// P transition duration
 920, 	// P F2 locus
 46, 	// P percent
 30, 	// P transition duration
 2290, 	// P F3 locus
 40, 	// P percent
 50, 	// P transition duration
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
 40, 	// T transition duration
 1700, 	// T F2 locus
 40, 	// T percent
 95, 	// T transition duration
 2300, 	// T F3 locus
 0, 	// T percent
 95, 	// T transition duration
 320, 	// D F1 locus
 43, 	// D percent
 40, 	// D transition duration
 1700, 	// D F2 locus
 40, 	// D percent
 95, 	// D transition duration
 2300, 	// D F3 locus
 0, 	// D percent
 95, 	// D transition duration
 320, 	// K F1 locus
 33, 	// K percent
 40, 	// K transition duration
 1600, 	// K F2 locus
 42, 	// K percent
 65, 	// K transition duration
 2050, 	// K F3 locus
 15, 	// K percent
 80, 	// K transition duration
 300, 	// G F1 locus
 45, 	// G percent
 40, 	// G transition duration
 1600, 	// G F2 locus
 42, 	// G percent
 65, 	// G transition duration
 1920, 	// G F3 locus
 15, 	// G percent
 80, 	// G transition duration
 275, 	// PF F1 locus
 80, 	// PF percent
 50, 	// PF transition duration
 1340, 	// PF F2 locus
 81, 	// PF percent
 30, 	// PF transition duration
 2670, 	// PF F3 locus
 80, 	// PF percent
 60, 	// PF transition duration
 290, 	// TS F1 locus
 45, 	// TS percent
 50, 	// TS transition duration
 1970, 	// TS F2 locus
 71, 	// TS percent
 30, 	// TS transition duration
 2570, 	// TS F3 locus
 31, 	// TS percent
 80, 	// TS transition duration
 280, 	// DJ F1 locus
 50, 	// DJ percent
 30, 	// DJ transition duration
 1730, 	// DJ F2 locus
 75, 	// DJ percent
 40, 	// DJ transition duration
 2311, 	// DJ F3 locus
 36, 	// DJ percent
 30, 	// DJ transition duration
 250, 	// TJ F1 locus
 45, 	// TJ percent
 50, 	// TJ transition duration
 1770, 	// TJ F2 locus
 50, 	// TJ percent
 60, 	// TJ transition duration
 2731, 	// TJ F3 locus
 70, 	// TJ percent
 65, 	// TJ transition duration
 284, 	// KS F1 locus
 52, 	// KS percent
 40, 	// KS transition duration
 1960, 	// KS F2 locus
 88, 	// KS percent
 70, 	// KS transition duration
 2083, 	// KS F3 locus
 45, 	// KS percent
 50, 	// KS transition duration
// Low
 0, 	// L F1 locus
 0, 	// L percent
 0, 	// L transition duration
 -1, 	// L F2 locus
 -1, 	// L percent
 -1, 	// L transition duration
 0, 	// L F3 locus
 0, 	// L percent
 0, 	// L transition duration
 200, 	// M F1 locus
 10, 	// M percent
 10, 	// M transition duration
 1200, 	// M F2 locus
 80, 	// M percent
 20, 	// M transition duration
 2540, 	// M F3 locus
 40, 	// M percent
 25, 	// M transition duration
 250, 	// N F1 locus
 20, 	// N percent
 30, 	// N transition duration
 1450, 	// N F2 locus
 10, 	// N percent
 75, 	// N transition duration
 2720, 	// N F3 locus
 50, 	// N percent
 65, 	// N transition duration
 440, 	// NG F1 locus
 25, 	// NG percent
 40, 	// NG transition duration
 900, 	// NG F2 locus
 80, 	// NG percent
 70, 	// NG transition duration
 1920, 	// NG F3 locus
 25, 	// NG percent
 70, 	// NG transition duration
 492, 	// F F1 locus
 52, 	// F percent
 40, 	// F transition duration
 1158, 	// F F2 locus
 33, 	// F percent
 30, 	// F transition duration
 2311, 	// F F3 locus
 10, 	// F percent
 30, 	// F transition duration
 2300, 	// V F1 locus
 50, 	// V percent
 30, 	// V transition duration
 1460, 	// V F2 locus
 86, 	// V percent
 30, 	// V transition duration
 2644, 	// V F3 locus
 80, 	// V percent
 30, 	// V transition duration
 238, 	// S F1 locus
 80, 	// S percent
 60, 	// S transition duration
 1746, 	// S F2 locus
 37, 	// S percent
 30, 	// S transition duration
 2873, 	// S F3 locus
 60, 	// S percent
 50, 	// S transition duration
 220, 	// Z F1 locus
 20, 	// Z percent
 60, 	// Z transition duration
 1700, 	// Z F2 locus
 37, 	// Z percent
 50, 	// Z transition duration
 2673, 	// Z F3 locus
 81, 	// Z percent
 50, 	// Z transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1700, 	// SH F2 locus
 80, 	// SH percent
 80, 	// SH transition duration
 2270, 	// SH F3 locus
 0, 	// SH percent
 85, 	// SH transition duration
 285, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 1700, 	// ZH F2 locus
 27, 	// ZH percent
 70, 	// ZH transition duration
 2222, 	// ZH F3 locus
 0, 	// ZH percent
 85, 	// ZH transition duration
 244, 	// CH F1 locus
 78, 	// CH percent
 30, 	// CH transition duration
 1970, 	// CH F2 locus
 50, 	// CH percent
 40, 	// CH transition duration
 2750, 	// CH F3 locus
 60, 	// CH percent
 50, 	// CH transition duration
 350, 	// KH F1 locus
 78, 	// KH percent
 30, 	// KH transition duration
 1000, 	// KH F2 locus
 2, 	// KH percent
 240, 	// KH transition duration
 2800, 	// KH F3 locus
 60, 	// KH percent
 50, 	// KH transition duration
 355, 	// P F1 locus
 45, 	// P percent
 20, 	// P transition duration
 950, 	// P F2 locus
 43, 	// P percent
 20, 	// P transition duration
 2200, 	// P F3 locus
 50, 	// P percent
 30, 	// P transition duration
 200, 	// B F1 locus
 45, 	// B percent
 25, 	// B transition duration
 1100, 	// B F2 locus
 80, 	// B percent
 25, 	// B transition duration
 1600, 	// B F3 locus
 50, 	// B percent
 30, 	// B transition duration
 433, 	// T F1 locus
 11, 	// T percent
 40, 	// T transition duration
 2005, 	// T F2 locus
 69, 	// T percent
 30, 	// T transition duration
 2600, 	// T F3 locus
 96, 	// T percent
 30, 	// T transition duration
 250, 	// D F1 locus
 50, 	// D percent
 40, 	// D transition duration
 1707, 	// D F2 locus
 45, 	// D percent
 50, 	// D transition duration
 2525, 	// D F3 locus
 33, 	// D percent
 40, 	// D transition duration
 320, 	// K F1 locus
 32, 	// K percent
 60, 	// K transition duration
 1800, 	// K F2 locus
 16, 	// K percent
 60, 	// K transition duration
 2126, 	// K F3 locus
 0, 	// K percent
 90, 	// K transition duration
 290, 	// G F1 locus
 45, 	// G percent
 40, 	// G transition duration
 1604, 	// G F2 locus
 47, 	// G percent
 40, 	// G transition duration
 1971, 	// G F3 locus
 22, 	// G percent
 80, 	// G transition duration
 400, 	// Q F1 locus
 10, 	// Q percent
 15, 	// Q transition duration
 1400, 	// Q F2 locus
 20, 	// Q percent
 20, 	// Q transition duration
 2400, 	// Q F3 locus
 20, 	// Q percent
 25, 	// Q transition duration
 255, 	// PF F1 locus
 30, 	// PF percent
 10, 	// PF transition duration
 1140, 	// PF F2 locus
 33, 	// PF percent
 20, 	// PF transition duration
 1900, 	// PF F3 locus
 80, 	// PF percent
 30, 	// PF transition duration
 253, 	// TS F1 locus
 50, 	// TS percent
 30, 	// TS transition duration
 1900, 	// TS F2 locus
 80, 	// TS percent
 30, 	// TS transition duration
 2557, 	// TS F3 locus
 27, 	// TS percent
 40, 	// TS transition duration
 420, 	// DJ F1 locus
 50, 	// DJ percent
 40, 	// DJ transition duration
 1307, 	// DJ F2 locus
 5, 	// DJ percent
 50, 	// DJ transition duration
 2325, 	// DJ F3 locus
 33, 	// DJ percent
 40, 	// DJ transition duration
 253, 	// TJ F1 locus
 50, 	// TJ percent
 30, 	// TJ transition duration
 1700, 	// TJ F2 locus
 80, 	// TJ percent
 30, 	// TJ transition duration
 2557, 	// TJ F3 locus
 27, 	// TJ percent
 40, 	// TJ transition duration
 248, 	// KS F1 locus
 32, 	// KS percent
 60, 	// KS transition duration
 1595, 	// KS F2 locus
 77, 	// KS percent
 70, 	// KS transition duration
 2040, 	// KS F3 locus
 50, 	// KS percent
 40, 	// KS transition duration
 0};

// Female Locus
const short gr_femloc_def[] = {
 0, 
// Front
 326, 	// M F1 locus
 9, 	// M percent
 10, 	// M transition duration
 1500, 	// M F2 locus
 40, 	// M percent
 40, 	// M transition duration
 2800, 	// M F3 locus
 50, 	// M percent
 30, 	// M transition duration
 250, 	// N F1 locus
 20, 	// N percent
 35, 	// N transition duration
 1650, 	// N F2 locus
 55, 	// N percent
 35, 	// N transition duration
 2900, 	// N F3 locus
 40, 	// N percent
 45, 	// N transition duration
 242, 	// NG F1 locus
 35, 	// NG percent
 40, 	// NG transition duration
 2533, 	// NG F2 locus
 23, 	// NG percent
 80, 	// NG transition duration
 3300, 	// NG F3 locus
 0, 	// NG percent
 60, 	// NG transition duration
 244, 	// F F1 locus
 80, 	// F percent
 30, 	// F transition duration
 1, 	// F F2 locus
 92, 	// F percent
 35, 	// F transition duration
 2100, 	// F F3 locus
 33, 	// F percent
 60, 	// F transition duration
 320, 	// V F1 locus
 70, 	// V percent
 30, 	// V transition duration
 1676, 	// V F2 locus
 10, 	// V percent
 40, 	// V transition duration
 2523, 	// V F3 locus
 50, 	// V percent
 40, 	// V transition duration
 250, 	// S F1 locus
 37, 	// S percent
 40, 	// S transition duration
 2000, 	// S F2 locus
 69, 	// S percent
 50, 	// S transition duration
 3000, 	// S F3 locus
 0, 	// S percent
 70, 	// S transition duration
 220, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1711, 	// Z F2 locus
 10, 	// Z percent
 50, 	// Z transition duration
 2740, 	// Z F3 locus
 10, 	// Z percent
 65, 	// Z transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1830, 	// SH F2 locus
 30, 	// SH percent
 70, 	// SH transition duration
 2640, 	// SH F3 locus
 51, 	// SH percent
 70, 	// SH transition duration
 285, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 1830, 	// ZH F2 locus
 30, 	// ZH percent
 70, 	// ZH transition duration
 2640, 	// ZH F3 locus
 51, 	// ZH percent
 70, 	// ZH transition duration
 150, 	// CH F1 locus
 60, 	// CH percent
 30, 	// CH transition duration
 2800, 	// CH F2 locus
 60, 	// CH percent
 40, 	// CH transition duration
 3200, 	// CH F3 locus
 60, 	// CH percent
 40, 	// CH transition duration
 864, 	// KH F1 locus
 50, 	// KH percent
 30, 	// KH transition duration
 1400, 	// KH F2 locus
 60, 	// KH percent
 40, 	// KH transition duration
 2800, 	// KH F3 locus
 60, 	// KH percent
 40, 	// KH transition duration
 400, 	// P F1 locus
 10, 	// P percent
 20, 	// P transition duration
 800, 	// P F2 locus
 36, 	// P percent
 40, 	// P transition duration
 1871, 	// P F3 locus
 43, 	// P percent
 45, 	// P transition duration
 235, 	// B F1 locus
 52, 	// B percent
 40, 	// B transition duration
 1901, 	// B F2 locus
 80, 	// B percent
 30, 	// B transition duration
 2600, 	// B F3 locus
 80, 	// B percent
 45, 	// B transition duration
 317, 	// T F1 locus
 37, 	// T percent
 35, 	// T transition duration
 2363, 	// T F2 locus
 61, 	// T percent
 35, 	// T transition duration
 3000, 	// T F3 locus
 30, 	// T percent
 45, 	// T transition duration
 237, 	// D F1 locus
 40, 	// D percent
 35, 	// D transition duration
 1737, 	// D F2 locus
 50, 	// D percent
 35, 	// D transition duration
 2728, 	// D F3 locus
 33, 	// D percent
 45, 	// D transition duration
 302, 	// K F1 locus
 49, 	// K percent
 40, 	// K transition duration
 2284, 	// K F2 locus
 46, 	// K percent
 40, 	// K transition duration
 3408, 	// K F3 locus
 66, 	// K percent
 50, 	// K transition duration
 220, 	// G F1 locus
 50, 	// G percent
 20, 	// G transition duration
 1950, 	// G F2 locus
 10, 	// G percent
 60, 	// G transition duration
 3200, 	// G F3 locus
 20, 	// G percent
 50, 	// G transition duration
 244, 	// PF F1 locus
 49, 	// PF percent
 30, 	// PF transition duration
 970, 	// PF F2 locus
 69, 	// PF percent
 40, 	// PF transition duration
 2857, 	// PF F3 locus
 33, 	// PF percent
 30, 	// PF transition duration
 290, 	// TS F1 locus
 80, 	// TS percent
 40, 	// TS transition duration
 2143, 	// TS F2 locus
 69, 	// TS percent
 50, 	// TS transition duration
 3000, 	// TS F3 locus
 27, 	// TS percent
 70, 	// TS transition duration
 285, 	// DJ F1 locus
 32, 	// DJ percent
 55, 	// DJ transition duration
 1830, 	// DJ F2 locus
 30, 	// DJ percent
 70, 	// DJ transition duration
 2640, 	// DJ F3 locus
 51, 	// DJ percent
 70, 	// DJ transition duration
 285, 	// TJ F1 locus
 32, 	// TJ percent
 55, 	// TJ transition duration
 1830, 	// TJ F2 locus
 30, 	// TJ percent
 70, 	// TJ transition duration
 2640, 	// TJ F3 locus
 51, 	// TJ percent
 70, 	// TJ transition duration
 250, 	// KS F1 locus
 37, 	// KS percent
 40, 	// KS transition duration
 2144, 	// KS F2 locus
 69, 	// KS percent
 50, 	// KS transition duration
 3000, 	// KS F3 locus
 0, 	// KS percent
 70, 	// KS transition duration
// Back
 104, 	// M F1 locus
 69, 	// M percent
 30, 	// M transition duration
 943, 	// M F2 locus
 33, 	// M percent
 20, 	// M transition duration
 2400, 	// M F3 locus
 0, 	// M percent
 50, 	// M transition duration
 250, 	// N F1 locus
 20, 	// N percent
 30, 	// N transition duration
 1620, 	// N F2 locus
 55, 	// N percent
 75, 	// N transition duration
 2800, 	// N F3 locus
 0, 	// N percent
 60, 	// N transition duration
 440, 	// NG F1 locus
 25, 	// NG percent
 30, 	// NG transition duration
 1640, 	// NG F2 locus
 20, 	// NG percent
 70, 	// NG transition duration
 2400, 	// NG F3 locus
 20, 	// NG percent
 60, 	// NG transition duration
 264, 	// F F1 locus
 44, 	// F percent
 30, 	// F transition duration
 845, 	// F F2 locus
 26, 	// F percent
 40, 	// F transition duration
 3232, 	// F F3 locus
 90, 	// F percent
 40, 	// F transition duration
 390, 	// V F1 locus
 76, 	// V percent
 30, 	// V transition duration
 1676, 	// V F2 locus
 98, 	// V percent
 40, 	// V transition duration
 2523, 	// V F3 locus
 50, 	// V percent
 40, 	// V transition duration
 308, 	// S F1 locus
 54, 	// S percent
 50, 	// S transition duration
 2000, 	// S F2 locus
 63, 	// S percent
 50, 	// S transition duration
 2800, 	// S F3 locus
 0, 	// S percent
 65, 	// S transition duration
 207, 	// Z F1 locus
 15, 	// Z percent
 20, 	// Z transition duration
 1655, 	// Z F2 locus
 26, 	// Z percent
 60, 	// Z transition duration
 2600, 	// Z F3 locus
 20, 	// Z percent
 50, 	// Z transition duration
 218, 	// SH F1 locus
 51, 	// SH percent
 30, 	// SH transition duration
 2000, 	// SH F2 locus
 50, 	// SH percent
 40, 	// SH transition duration
 2600, 	// SH F3 locus
 50, 	// SH percent
 40, 	// SH transition duration
 155, 	// ZH F1 locus
 43, 	// ZH percent
 55, 	// ZH transition duration
 1962, 	// ZH F2 locus
 39, 	// ZH percent
 60, 	// ZH transition duration
 2500, 	// ZH F3 locus
 0, 	// ZH percent
 100, 	// ZH transition duration
 180, 	// CH F1 locus
 80, 	// CH percent
 30, 	// CH transition duration
 2600, 	// CH F2 locus
 40, 	// CH percent
 50, 	// CH transition duration
 3250, 	// CH F3 locus
 60, 	// CH percent
 40, 	// CH transition duration
 850, 	// KH F1 locus
 0, 	// KH percent
 30, 	// KH transition duration
 1400, 	// KH F2 locus
 60, 	// KH percent
 40, 	// KH transition duration
 2500, 	// KH F3 locus
 0, 	// KH percent
 40, 	// KH transition duration
 323, 	// P F1 locus
 29, 	// P percent
 25, 	// P transition duration
 800, 	// P F2 locus
 0, 	// P percent
 25, 	// P transition duration
 2600, 	// P F3 locus
 0, 	// P percent
 30, 	// P transition duration
 271, 	// B F1 locus
 54, 	// B percent
 25, 	// B transition duration
 900, 	// B F2 locus
 80, 	// B percent
 30, 	// B transition duration
 2600, 	// B F3 locus
 80, 	// B percent
 40, 	// B transition duration
 301, 	// T F1 locus
 15, 	// T percent
 30, 	// T transition duration
 2400, 	// T F2 locus
 56, 	// T percent
 40, 	// T transition duration
 3000, 	// T F3 locus
 30, 	// T percent
 55, 	// T transition duration
 307, 	// D F1 locus
 36, 	// D percent
 50, 	// D transition duration
 1874, 	// D F2 locus
 64, 	// D percent
 50, 	// D transition duration
 2600, 	// D F3 locus
 0, 	// D percent
 60, 	// D transition duration
 320, 	// K F1 locus
 20, 	// K percent
 50, 	// K transition duration
 2020, 	// K F2 locus
 95, 	// K percent
 70, 	// K transition duration
 2320, 	// K F3 locus
 95, 	// K percent
 70, 	// K transition duration
 232, 	// G F1 locus
 50, 	// G percent
 40, 	// G transition duration
 1800, 	// G F2 locus
 50, 	// G percent
 40, 	// G transition duration
 2400, 	// G F3 locus
 50, 	// G percent
 950, 	// G transition duration
 264, 	// PF F1 locus
 44, 	// PF percent
 30, 	// PF transition duration
 845, 	// PF F2 locus
 26, 	// PF percent
 40, 	// PF transition duration
 2600, 	// PF F3 locus
 0, 	// PF percent
 40, 	// PF transition duration
 308, 	// TS F1 locus
 54, 	// TS percent
 50, 	// TS transition duration
 1800, 	// TS F2 locus
 43, 	// TS percent
 40, 	// TS transition duration
 3000, 	// TS F3 locus
 18, 	// TS percent
 65, 	// TS transition duration
 155, 	// DJ F1 locus
 43, 	// DJ percent
 55, 	// DJ transition duration
 1962, 	// DJ F2 locus
 39, 	// DJ percent
 60, 	// DJ transition duration
 2500, 	// DJ F3 locus
 0, 	// DJ percent
 100, 	// DJ transition duration
 218, 	// TJ F1 locus
 51, 	// TJ percent
 30, 	// TJ transition duration
 1416, 	// TJ F2 locus
 45, 	// TJ percent
 40, 	// TJ transition duration
 2500, 	// TJ F3 locus
 30, 	// TJ percent
 80, 	// TJ transition duration
 308, 	// KS F1 locus
 54, 	// KS percent
 50, 	// KS transition duration
 1432, 	// KS F2 locus
 13, 	// KS percent
 50, 	// KS transition duration
 2500, 	// KS F3 locus
 0, 	// KS percent
 65, 	// KS transition duration
// Round
 113, 	// M F1 locus
 68, 	// M percent
 30, 	// M transition duration
 800, 	// M F2 locus
 11, 	// M percent
 20, 	// M transition duration
 2072, 	// M F3 locus
 58, 	// M percent
 45, 	// M transition duration
 250, 	// N F1 locus
 20, 	// N percent
 35, 	// N transition duration
 1664, 	// N F2 locus
 56, 	// N percent
 30, 	// N transition duration
 2700, 	// N F3 locus
 50, 	// N percent
 40, 	// N transition duration
 266, 	// NG F1 locus
 47, 	// NG percent
 40, 	// NG transition duration
 2016, 	// NG F2 locus
 24, 	// NG percent
 70, 	// NG transition duration
 2100, 	// NG F3 locus
 90, 	// NG percent
 60, 	// NG transition duration
 293, 	// F F1 locus
 90, 	// F percent
 30, 	// F transition duration
 1997, 	// F F2 locus
 77, 	// F percent
 40, 	// F transition duration
 2900, 	// F F3 locus
 75, 	// F percent
 40, 	// F transition duration
 390, 	// V F1 locus
 70, 	// V percent
 30, 	// V transition duration
 1676, 	// V F2 locus
 50, 	// V percent
 40, 	// V transition duration
 2523, 	// V F3 locus
 50, 	// V percent
 40, 	// V transition duration
 270, 	// S F1 locus
 21, 	// S percent
 40, 	// S transition duration
 2032, 	// S F2 locus
 64, 	// S percent
 40, 	// S transition duration
 2800, 	// S F3 locus
 0, 	// S percent
 80, 	// S transition duration
 310, 	// Z F1 locus
 40, 	// Z percent
 40, 	// Z transition duration
 1540, 	// Z F2 locus
 35, 	// Z percent
 50, 	// Z transition duration
 2550, 	// Z F3 locus
 0, 	// Z percent
 70, 	// Z transition duration
 285, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1830, 	// SH F2 locus
 30, 	// SH percent
 70, 	// SH transition duration
 2640, 	// SH F3 locus
 51, 	// SH percent
 70, 	// SH transition duration
 285, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 1830, 	// ZH F2 locus
 30, 	// ZH percent
 70, 	// ZH transition duration
 2640, 	// ZH F3 locus
 51, 	// ZH percent
 70, 	// ZH transition duration
 150, 	// CH F1 locus
 60, 	// CH percent
 30, 	// CH transition duration
 2800, 	// CH F2 locus
 60, 	// CH percent
 40, 	// CH transition duration
 3200, 	// CH F3 locus
 60, 	// CH percent
 40, 	// CH transition duration
 850, 	// KH F1 locus
 60, 	// KH percent
 30, 	// KH transition duration
 1400, 	// KH F2 locus
 60, 	// KH percent
 40, 	// KH transition duration
 2800, 	// KH F3 locus
 60, 	// KH percent
 40, 	// KH transition duration
 249, 	// P F1 locus
 12, 	// P percent
 20, 	// P transition duration
 1075, 	// P F2 locus
 51, 	// P percent
 30, 	// P transition duration
 2400, 	// P F3 locus
 0, 	// P percent
 45, 	// P transition duration
 295, 	// B F1 locus
 50, 	// B percent
 20, 	// B transition duration
 1200, 	// B F2 locus
 80, 	// B percent
 30, 	// B transition duration
 2400, 	// B F3 locus
 80, 	// B percent
 30, 	// B transition duration
 270, 	// T F1 locus
 0, 	// T percent
 35, 	// T transition duration
 2296, 	// T F2 locus
 57, 	// T percent
 55, 	// T transition duration
 2600, 	// T F3 locus
 0, 	// T percent
 45, 	// T transition duration
 247, 	// D F1 locus
 50, 	// D percent
 35, 	// D transition duration
 1900, 	// D F2 locus
 64, 	// D percent
 35, 	// D transition duration
 2875, 	// D F3 locus
 58, 	// D percent
 45, 	// D transition duration
 274, 	// K F1 locus
 6, 	// K percent
 40, 	// K transition duration
 2114, 	// K F2 locus
 29, 	// K percent
 55, 	// K transition duration
 2500, 	// K F3 locus
 0, 	// K percent
 70, 	// K transition duration
 250, 	// G F1 locus
 27, 	// G percent
 40, 	// G transition duration
 1400, 	// G F2 locus
 67, 	// G percent
 40, 	// G transition duration
 2002, 	// G F3 locus
 17, 	// G percent
 40, 	// G transition duration
 293, 	// PF F1 locus
 21, 	// PF percent
 30, 	// PF transition duration
 720, 	// PF F2 locus
 77, 	// PF percent
 40, 	// PF transition duration
 2300, 	// PF F3 locus
 0, 	// PF percent
 50, 	// PF transition duration
 290, 	// TS F1 locus
 41, 	// TS percent
 40, 	// TS transition duration
 2032, 	// TS F2 locus
 64, 	// TS percent
 40, 	// TS transition duration
 3000, 	// TS F3 locus
 31, 	// TS percent
 60, 	// TS transition duration
 285, 	// DJ F1 locus
 32, 	// DJ percent
 55, 	// DJ transition duration
 1830, 	// DJ F2 locus
 30, 	// DJ percent
 70, 	// DJ transition duration
 2640, 	// DJ F3 locus
 51, 	// DJ percent
 70, 	// DJ transition duration
 285, 	// TJ F1 locus
 32, 	// TJ percent
 55, 	// TJ transition duration
 1830, 	// TJ F2 locus
 30, 	// TJ percent
 70, 	// TJ transition duration
 2640, 	// TJ F3 locus
 51, 	// TJ percent
 70, 	// TJ transition duration
 270, 	// KS F1 locus
 21, 	// KS percent
 40, 	// KS transition duration
 2032, 	// KS F2 locus
 64, 	// KS percent
 40, 	// KS transition duration
 2700, 	// KS F3 locus
 0, 	// KS percent
 60, 	// KS transition duration
// Low
 -1, 	// L F1 locus
 -1, 	// L percent
 -1, 	// L transition duration
 -1, 	// L F2 locus
 -1, 	// L percent
 -1, 	// L transition duration
 -1, 	// L F3 locus
 -1, 	// L percent
 -1, 	// L transition duration
 184, 	// M F1 locus
 58, 	// M percent
 30, 	// M transition duration
 970, 	// M F2 locus
 13, 	// M percent
 20, 	// M transition duration
 2400, 	// M F3 locus
 0, 	// M percent
 50, 	// M transition duration
 450, 	// N F1 locus
 20, 	// N percent
 30, 	// N transition duration
 1150, 	// N F2 locus
 55, 	// N percent
 95, 	// N transition duration
 2620, 	// N F3 locus
 0, 	// N percent
 95, 	// N transition duration
 392, 	// NG F1 locus
 47, 	// NG percent
 30, 	// NG transition duration
 2075, 	// NG F2 locus
 20, 	// NG percent
 70, 	// NG transition duration
 2510, 	// NG F3 locus
 73, 	// NG percent
 60, 	// NG transition duration
 153, 	// F F1 locus
 46, 	// F percent
 40, 	// F transition duration
 1100, 	// F F2 locus
 0, 	// F percent
 40, 	// F transition duration
 2700, 	// F F3 locus
 0, 	// F percent
 40, 	// F transition duration
 390, 	// V F1 locus
 70, 	// V percent
 60, 	// V transition duration
 1676, 	// V F2 locus
 30, 	// V percent
 60, 	// V transition duration
 2523, 	// V F3 locus
 55, 	// V percent
 70, 	// V transition duration
 420, 	// S F1 locus
 8, 	// S percent
 40, 	// S transition duration
 1879, 	// S F2 locus
 68, 	// S percent
 60, 	// S transition duration
 2700, 	// S F3 locus
 0, 	// S percent
 65, 	// S transition duration
 395, 	// Z F1 locus
 -4, 	// Z percent
 40, 	// Z transition duration
 1650, 	// Z F2 locus
 0, 	// Z percent
 60, 	// Z transition duration
 2700, 	// Z F3 locus
 0, 	// Z percent
 65, 	// Z transition duration
 364, 	// SH F1 locus
 20, 	// SH percent
 50, 	// SH transition duration
 1700, 	// SH F2 locus
 0, 	// SH percent
 50, 	// SH transition duration
 2700, 	// SH F3 locus
 0, 	// SH percent
 50, 	// SH transition duration
 291, 	// ZH F1 locus
 32, 	// ZH percent
 60, 	// ZH transition duration
 1700, 	// ZH F2 locus
 0, 	// ZH percent
 60, 	// ZH transition duration
 2700, 	// ZH F3 locus
 0, 	// ZH percent
 110, 	// ZH transition duration
 180, 	// CH F1 locus
 80, 	// CH percent
 30, 	// CH transition duration
 2400, 	// CH F2 locus
 40, 	// CH percent
 50, 	// CH transition duration
 3250, 	// CH F3 locus
 60, 	// CH percent
 40, 	// CH transition duration
 850, 	// KH F1 locus
 35, 	// KH percent
 30, 	// KH transition duration
 1400, 	// KH F2 locus
 63, 	// KH percent
 50, 	// KH transition duration
 2570, 	// KH F3 locus
 75, 	// KH percent
 40, 	// KH transition duration
 540, 	// P F1 locus
 -125, 	// P percent
 20, 	// P transition duration
 1860, 	// P F2 locus
 23, 	// P percent
 20, 	// P transition duration
 2700, 	// P F3 locus
 0, 	// P percent
 20, 	// P transition duration
 271, 	// B F1 locus
 54, 	// B percent
 40, 	// B transition duration
 1901, 	// B F2 locus
 80, 	// B percent
 30, 	// B transition duration
 2600, 	// B F3 locus
 80, 	// B percent
 30, 	// B transition duration
 200, 	// T F1 locus
 50, 	// T percent
 60, 	// T transition duration
 1578, 	// T F2 locus
 53, 	// T percent
 60, 	// T transition duration
 2900, 	// T F3 locus
 0, 	// T percent
 60, 	// T transition duration
 426, 	// D F1 locus
 23, 	// D percent
 40, 	// D transition duration
 1800, 	// D F2 locus
 10, 	// D percent
 50, 	// D transition duration
 2700, 	// D F3 locus
 0, 	// D percent
 50, 	// D transition duration
 305, 	// K F1 locus
 35, 	// K percent
 60, 	// K transition duration
 1963, 	// K F2 locus
 30, 	// K percent
 40, 	// K transition duration
 3059, 	// K F3 locus
 40, 	// K percent
 40, 	// K transition duration
 166, 	// G F1 locus
 35, 	// G percent
 80, 	// G transition duration
 1710, 	// G F2 locus
 5, 	// G percent
 80, 	// G transition duration
 1971, 	// G F3 locus
 22, 	// G percent
 80, 	// G transition duration
 -1, 	// Q F1 locus
 -1, 	// Q percent
 -1, 	// Q transition duration
 -1, 	// Q F2 locus
 -1, 	// Q percent
 -1, 	// Q transition duration
 -1, 	// Q F3 locus
 -1, 	// Q percent
 -1, 	// Q transition duration
 53, 	// PF F1 locus
 46, 	// PF percent
 40, 	// PF transition duration
 1100, 	// PF F2 locus
 0, 	// PF percent
 40, 	// PF transition duration
 2700, 	// PF F3 locus
 0, 	// PF percent
 40, 	// PF transition duration
 420, 	// TS F1 locus
 48, 	// TS percent
 40, 	// TS transition duration
 1279, 	// TS F2 locus
 48, 	// TS percent
 60, 	// TS transition duration
 3000, 	// TS F3 locus
 27, 	// TS percent
 65, 	// TS transition duration
 291, 	// DJ F1 locus
 32, 	// DJ percent
 60, 	// DJ transition duration
 1700, 	// DJ F2 locus
 0, 	// DJ percent
 60, 	// DJ transition duration
 2700, 	// DJ F3 locus
 0, 	// DJ percent
 110, 	// DJ transition duration
 364, 	// TJ F1 locus
 20, 	// TJ percent
 50, 	// TJ transition duration
 1700, 	// TJ F2 locus
 30, 	// TJ percent
 50, 	// TJ transition duration
 2700, 	// TJ F3 locus
 30, 	// TJ percent
 50, 	// TJ transition duration
 420, 	// KS F1 locus
 8, 	// KS percent
 40, 	// KS transition duration
 1579, 	// KS F2 locus
 38, 	// KS percent
 60, 	// KS transition duration
 2700, 	// KS F3 locus
 0, 	// KS percent
 65, 	// KS transition duration
 0};

const struct rom_data_s gr_rom_data_def = {
gr_inhdr_def,
gr_mindur_def,
gr_burdr_def,
gr_begtyp_def,
gr_endtyp_def,
gr_place_def,
gr_featb_def,
gr_maltar_def,
gr_femtar_def,
gr_maldip_def,
gr_femdip_def,
gr_ptram_def,
gr_plocu_def,
gr_maleloc_def,
gr_femloc_def
};


