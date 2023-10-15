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

#define PH_PHONEME_COUNT 57
#define PH_PHONEME_NAMES " _  IY IH EY EH AE AA AY AW AH AO OW OY UH UW RR YU AX IX IR ER AR OR UR W  Y  R  L  HX OH LX M  N  NX EL DZ EN F  V  TH DH S  Z  SH ZH P  B  T  D  K  G  YR TX Q  CH JH DF "

// Inherent Duration (milliseconds)
const short uk_inhdr_def[] = {
 300, 	// _ 
 140, 	// IY
 100, 	// IH
 200, 	// EY
 120, 	// EH
 160, 	// AE
 220, 	// AA
 240, 	// AY
 230, 	// AW
 140, 	// AH
 180, 	// AO
 200, 	// OW
 220, 	// OY
 120, 	// UH
 160, 	// UW
 180, 	// RR
 210, 	// YU
 160, 	// AX
 120, 	// IX
 210, 	// IR
 250, 	// ER
 250, 	// AR
 250, 	// OR
 230, 	// UR
 60, 	// W 
 70, 	// Y 
 65, 	// R 
 75, 	// L 
 77, 	// HX
 180, 	// OH
 100, 	// LX
 80, 	// M 
 75, 	// N 
 80, 	// NX
 160, 	// EL
 60, 	// DZ
 170, 	// EN
 100, 	// F 
 90, 	// V 
 100, 	// TH
 60, 	// DH
 115, 	// S 
 75, 	// Z 
 115, 	// SH
 70, 	// ZH
 85, 	// P 
 80, 	// B 
 85, 	// T 
 80, 	// D 
 100, 	// K 
 90, 	// G 
 280, 	// YR
 70, 	// TX
 5, 	// Q 
 160, 	// CH
 100, 	// JH
 70 }; 	//DF

// Minimum Duration (milliseconds)
const short uk_mindur_def[] = {
 7, 	// _ 
 70, 	// IY
 60, 	// IH
 110, 	// EY
 80, 	// EH
 80, 	// AE
 90, 	// AA
 100, 	// AY
 110, 	// AW
 70, 	// AH
 100, 	// AO
 90, 	// OW
 110, 	// OY
 80, 	// UH
 80, 	// UW
 90, 	// RR
 160, 	// YU
 60, 	// AX
 50, 	// IX
 120, 	// IR
 120, 	// ER
 120, 	// AR
 120, 	// OR
 120, 	// UR
 15, 	// W 
 30, 	// Y 
 30, 	// R 
 40, 	// L 
 35, 	// HX
 80, 	// OH
 70, 	// LX
 60, 	// M 
 50, 	// N 
 50, 	// NX
 110, 	// EL
 35, 	// DZ
 100, 	// EN
 60, 	// F 
 70, 	// V 
 40, 	// TH
 35, 	// DH
 65, 	// S 
 60, 	// Z 
 60, 	// SH
 50, 	// ZH
 70, 	// P 
 60, 	// B 
 50, 	// T 
 40, 	// D 
 75, 	// K 
 65, 	// G 
 160, 	// YR
 50, 	// TX
 5, 	// Q 
 100, 	// CH
 70, 	// JH
 20 };	//DF

// Burst Duration (milliseconds)
const short uk_burdr_def[] = {
 0, 	//_ 
 0, 	//IY
 0, 	//IH
 0, 	//EY
 0, 	//EH
 0, 	//AE
 0, 	//AA
 0, 	//AY
 0, 	//AW
 0, 	//AH
 0, 	//AO
 0, 	//OW
 0, 	//OY
 0, 	//UH
 0, 	//UW
 0, 	//RR
 0, 	//YU
 0, 	//AX
 0, 	//IX
 0, 	//IR
 0, 	//ER
 0, 	//AR
 0, 	//OR
 0, 	//UR
 0, 	//W 
 0, 	//Y 
 0, 	//R 
 0, 	//L 
 0, 	//HX
 0, 	//OH
 0, 	//LX
 0, 	//M 
 0, 	//N 
 0, 	//NX
 0, 	//EL
 13, 	//DZ
 0, 	//EN
 0, 	//F 
 0, 	//V 
 0, 	//TH
 0, 	//DH
 0, 	//S 
 0, 	//Z 
 0, 	//SH
 0, 	//ZH
 7, 	//P 
 7, 	//B 
 13, 	//T 
 13, 	//D 
 26, 	//K 
 26, 	//G 
 0, 	//YR
 0, 	//TX
 0, 	//Q 
 71, 	//CH
 49, 	//JH
 7 };	//DF

// Beginning Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short uk_begtyp_def[] = {
 4, 	// _ 
 1, 	// IY
 1, 	// IH
 1, 	// EY
 1, 	// EH
 1, 	// AE
 2, 	// AA
 2, 	// AY
 2, 	// AW
 2, 	// AH
 3, 	// AO
 3, 	// OW
 3, 	// OY
 3, 	// UH
 3, 	// UW
 3, 	// RR
 1, 	// YU
 2, 	// AX
 1, 	// IX
 1, 	// IR
 1, 	// ER
 2, 	// AR
 3, 	// OR
 3, 	// UR
 5, 	// W 
 1, 	// Y 
 5, 	// R 
 5, 	// L 
 4, 	// HX
 2, 	// OH
 5, 	// LX
 4, 	// M 
 4, 	// N 
 4, 	// NX
 5, 	// EL
 4, 	// DZ
 4, 	// EN
 4, 	// F 
 4, 	// V 
 4, 	// TH
 4, 	// DH
 4, 	// S 
 4, 	// Z 
 4, 	// SH
 4, 	// ZH
 4, 	// P 
 4, 	// B 
 4, 	// T 
 4, 	// D 
 4, 	// K 
 4, 	// G 
 1, 	// YR
 4, 	// TX
 4, 	// Q 
 4, 	// CH
 4, 	// JH
 4 };	// DF

// Ending Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
const short uk_endtyp_def[] = {
 4, 	// _ 
 1, 	// IY
 1, 	// IH
 1, 	// EY
 1, 	// EH
 1, 	// AE
 2, 	// AA
 1, 	// AY
 5, 	// AW
 2, 	// AH
 3, 	// AO
 5, 	// OW
 1, 	// OY
 3, 	// UH
 5, 	// UW
 3, 	// RR
 3, 	// YU
 2, 	// AX
 1, 	// IX
 3, 	// IR
 3, 	// ER
 3, 	// AR
 3, 	// OR
 3, 	// UR
 5, 	// W 
 1, 	// Y 
 5, 	// R 
 5, 	// L 
 4, 	// HX
 2, 	// OH
 5, 	// LX
 4, 	// M 
 4, 	// N 
 4, 	// NX
 5, 	// EL
 4, 	// DZ
 4, 	// EN
 4, 	// F 
 4, 	// V 
 4, 	// TH
 4, 	// DH
 4, 	// S 
 4, 	// Z 
 4, 	// SH
 4, 	// ZH
 4, 	// P 
 4, 	// B 
 4, 	// T 
 4, 	// D 
 4, 	// K 
 4, 	// G 
 1, 	// YR
 4, 	// TX
 4, 	// Q 
 4, 	// CH
 4, 	// JH
 4 };	// DF

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
const short uk_place_def[] = {
 0x0000, 	// _ 
 0x0080, 	// IY
 0x0000, 	// IH
 0x0080, 	// EY
 0x0000, 	// EH
 0x0000, 	// AE
 0x0000, 	// AA
 0x0000, 	// AY
 0x0000, 	// AW
 0x0000, 	// AH
 0x0000, 	// AO
 0x0000, 	// OW
 0x0000, 	// OY
 0x0000, 	// UH
 0x0000, 	// UW
 0x0000, 	// RR
 0x0040, 	// YU
 0x0000, 	// AX
 0x0000, 	// IX
 0x0000, 	// IR
 0x0000, 	// ER
 0x0000, 	// AR
 0x0000, 	// OR
 0x0000, 	// UR
 0x0000, 	// W 
 0x00c0, 	// Y 
 0x0000, 	// R 
 0x0000, 	// L 
 0x0000, 	// HX
 0x0080, 	// OH
 0x0000, 	// LX
 0x0001, 	// M 
 0x0008, 	// N 
 0x0010, 	// NX
 0x0000, 	// EL
 0x0002, 	// DZ
 0x0008, 	// EN
 0x0001, 	// F 
 0x0001, 	// V 
 0x0002, 	// TH
 0x0002, 	// DH
 0x0008, 	// S 
 0x0008, 	// Z 
 0x0004, 	// SH
 0x0004, 	// ZH
 0x0001, 	// P 
 0x0001, 	// B 
 0x0008, 	// T 
 0x0008, 	// D 
 0x0010, 	// K 
 0x0010, 	// G 
 0x0000, 	// YR
 0x0028, 	// TX
 0x0020, 	// Q 
 0x0004, 	// CH
 0x0004, 	// JH
 0x0008 };	// DF

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
const int uk_featb_def[] = {
 0x00000010, 	// _ 
 0x0000001f, 	// IY
 0x0000001f, 	// IH
 0x0000001f, 	// EY
 0x0000001f, 	// EH
 0x0000001f, 	// AE
 0x0000001f, 	// AA
 0x0000001f, 	// AY
 0x0000001f, 	// AW
 0x0000001f, 	// AH
 0x0000001f, 	// AO
 0x0000001f, 	// OW
 0x0000001f, 	// OY
 0x0000001f, 	// UH
 0x0000001f, 	// UW
 0x0000001f, 	// RR
 0x0000041f, 	// YU
 0x0000001f, 	// AX
 0x0000001f, 	// IX
 0x0000001f, 	// IR
 0x0000001f, 	// ER
 0x0000001f, 	// AR
 0x0000001f, 	// OR
 0x0000001f, 	// UR
 0x0000071a, 	// W 
 0x0000071a, 	// Y 
 0x0000071a, 	// R 
 0x0000071a, 	// L 
 0x00000110, 	// HX
 0x0000001f, 	// OH
 0x0000031a, 	// LX
 0x0000259a, 	// M 
 0x0000259a, 	// N 
 0x0000259a, 	// NX
 0x0000001b, 	// EL
 0x00002962, 	// DZ
 0x0000249b, 	// EN
 0x00000120, 	// F 
 0x00000122, 	// V 
 0x00000120, 	// TH
 0x00000122, 	// DH
 0x00000120, 	// S 
 0x00000122, 	// Z 
 0x00000120, 	// SH
 0x00000122, 	// ZH
 0x00002960, 	// P 
 0x00002962, 	// B 
 0x00002960, 	// T 
 0x00002962, 	// D 
 0x00002960, 	// K 
 0x00002962, 	// G 
 0x0000001f, 	// YR
 0x00002962, 	// TX
 0x00002002, 	// Q 
 0x00002920, 	// CH
 0x00002922, 	// JH
 0x00002962, 	// DF
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
const short uk_maltar_def[] = {
// ==== F1 ====
 -1, 	// _ 
 -2, 	// IY
 -6, 	// IH
 -10, 	// EY
 -16, 	// EH
 -22, 	// AE
 653, 	// AA
 -28, 	// AY
 -36, 	// AW
 -42, 	// AH
 -48, 	// AO
 -54, 	// OW
 -60, 	// OY
 -68, 	// UH
 370, 	// UW
 -74, 	// RR
 -80, 	// YU
 -86, 	// AX
 -92, 	// IX
 -98, 	// IR
 -104, 	// ER
 -110, 	// AR
 -116, 	// OR
 -122, 	// UR
 295, 	// W 
 260, 	// Y 
 310, 	// R 
 340, 	// L 
 -1, 	// HX
 558, 	// OH
 414, 	// LX
 430, 	// M 
 430, 	// N 
 230, 	// NX
 450, 	// EL
 210, 	// DZ
 280, 	// EN
 340, 	// F 
 325, 	// V 
 320, 	// TH
 430, 	// DH
 320, 	// S 
 280, 	// Z 
 300, 	// SH
 280, 	// ZH
 350, 	// P 
 350, 	// B 
 350, 	// T 
 300, 	// D 
 210, 	// K 
 250, 	// G 
 -128, 	// YR
 210, 	// TX
 -1, 	// Q 
 350, 	// CH
 260, 	// JH
 350, 	// DF
// ==== F2 ====
 -1, 	// _ 
 -134, 	// IY
 -138, 	// IH
 -142, 	// EY
 -148, 	// EH
 -154, 	// AE
 1212, 	// AA
 -160, 	// AY
 -166, 	// AW
 -172, 	// AH
 -178, 	// AO
 -184, 	// OW
 -190, 	// OY
 -198, 	// UH
 1300, 	// UW
 -204, 	// RR
 -210, 	// YU
 -216, 	// AX
 -222, 	// IX
 -228, 	// IR
 -234, 	// ER
 -240, 	// AR
 -246, 	// OR
 -252, 	// UR
 610, 	// W 
 2070, 	// Y 
 1054, 	// R 
 1200, 	// L 
 -1, 	// HX
 930, 	// OH
 980, 	// LX
 1140, 	// M 
 1530, 	// N 
 2100, 	// NX
 800, 	// EL
 1400, 	// DZ
 1340, 	// EN
 1100, 	// F 
 1100, 	// V 
 1300, 	// TH
 1400, 	// DH
 1420, 	// S 
 1420, 	// Z 
 1900, 	// SH
 1650, 	// ZH
 1100, 	// P 
 691, 	// B 
 1600, 	// T 
 1600, 	// D 
 1800, 	// K 
 1790, 	// G 
 -258, 	// YR
 1600, 	// TX
 -1, 	// Q 
 2250, 	// CH
 2039, 	// JH
 1600, 	// DF
// ==== F3 ====
 -1, 	// _ 
 -264, 	// IY
 -268, 	// IH
 -272, 	// EY
 -278, 	// EH
 -284, 	// AE
 2613, 	// AA
 -290, 	// AY
 -298, 	// AW
 -304, 	// AH
 -310, 	// AO
 -316, 	// OW
 -322, 	// OY
 -330, 	// UH
 2333, 	// UW
 -336, 	// RR
 -342, 	// YU
 -348, 	// AX
 -354, 	// IX
 -360, 	// IR
 -366, 	// ER
 -372, 	// AR
 -378, 	// OR
 -384, 	// UR
 2195, 	// W 
 2950, 	// Y 
 1538, 	// R 
 2750, 	// L 
 -1, 	// HX
 2585, 	// OH
 2644, 	// LX
 2201, 	// M 
 2544, 	// N 
 2600, 	// NX
 2850, 	// EL
 2600, 	// DZ
 2600, 	// EN
 2080, 	// F 
 2144, 	// V 
 2520, 	// TH
 2419, 	// DH
 2550, 	// S 
 2600, 	// Z 
 2679, 	// SH
 2550, 	// ZH
 2150, 	// P 
 2150, 	// B 
 2680, 	// T 
 2690, 	// D 
 2316, 	// K 
 2520, 	// G 
 -390, 	// YR
 2600, 	// TX
 -1, 	// Q 
 2700, 	// CH
 2700, 	// JH
 2600, 	// DF
// ==== B1 ====
 -1, 	// _ 
 60, 	// IY
 90, 	// IH
 70, 	// EY
 90, 	// EH
 120, 	// AE
 90, 	// AA
 -396, 	// AY
 -402, 	// AW
 90, 	// AH
 110, 	// AO
 90, 	// OW
 200, 	// OY
 80, 	// UH
 75, 	// UW
 90, 	// RR
 70, 	// YU
 95, 	// AX
 60, 	// IX
 80, 	// IR
 80, 	// ER
 140, 	// AR
 100, 	// OR
 90, 	// UR
 60, 	// W 
 50, 	// Y 
 70, 	// R 
 70, 	// L 
 300, 	// HX
 110, 	// OH
 90, 	// LX
 130, 	// M 
 130, 	// N 
 130, 	// NX
 90, 	// EL
 90, 	// DZ
 130, 	// EN
 200, 	// F 
 100, 	// V 
 200, 	// TH
 100, 	// DH
 200, 	// S 
 100, 	// Z 
 200, 	// SH
 100, 	// ZH
 200, 	// P 
 90, 	// B 
 200, 	// T 
 90, 	// D 
 200, 	// K 
 90, 	// G 
 120, 	// YR
 110, 	// TX
 -1, 	// Q 
 200, 	// CH
 70, 	// JH
 90, 	// DF
// ==== B2 ====
 -1, 	// _ 
 120, 	// IY
 150, 	// IH
 170, 	// EY
 160, 	// EH
 -408, 	// AE
 90, 	// AA
 100, 	// AY
 75, 	// AW
 70, 	// AH
 120, 	// AO
 70, 	// OW
 -414, 	// OY
 83, 	// UH
 70, 	// UW
 110, 	// RR
 -420, 	// YU
 70, 	// AX
 100, 	// IX
 120, 	// IR
 120, 	// ER
 130, 	// AR
 80, 	// OR
 90, 	// UR
 60, 	// W 
 200, 	// Y 
 80, 	// R 
 65, 	// L 
 200, 	// HX
 80, 	// OH
 90, 	// LX
 120, 	// M 
 400, 	// N 
 250, 	// NX
 90, 	// EL
 110, 	// DZ
 300, 	// EN
 120, 	// F 
 120, 	// V 
 90, 	// TH
 120, 	// DH
 180, 	// S 
 140, 	// Z 
 240, 	// SH
 160, 	// ZH
 180, 	// P 
 120, 	// B 
 150, 	// T 
 100, 	// D 
 160, 	// K 
 120, 	// G 
 110, 	// YR
 100, 	// TX
 -1, 	// Q 
 280, 	// CH
 130, 	// JH
 100, 	// DF
// ==== B3 ====
 -1, 	// _ 
 260, 	// IY
 210, 	// IH
 200, 	// EY
 220, 	// EH
 290, 	// AE
 200, 	// AA
 230, 	// AY
 150, 	// AW
 180, 	// AH
 120, 	// AO
 180, 	// OW
 370, 	// OY
 160, 	// UH
 140, 	// UW
 90, 	// RR
 -426, 	// YU
 200, 	// AX
 200, 	// IX
 200, 	// IR
 200, 	// ER
 150, 	// AR
 140, 	// OR
 180, 	// UR
 80, 	// W 
 300, 	// Y 
 90, 	// R 
 120, 	// L 
 220, 	// HX
 130, 	// OH
 160, 	// LX
 150, 	// M 
 460, 	// N 
 400, 	// NX
 200, 	// EL
 200, 	// DZ
 460, 	// EN
 150, 	// F 
 120, 	// V 
 150, 	// TH
 170, 	// DH
 300, 	// S 
 300, 	// Z 
 300, 	// SH
 300, 	// ZH
 180, 	// P 
 130, 	// B 
 250, 	// T 
 240, 	// D 
 280, 	// K 
 180, 	// G 
 170, 	// YR
 170, 	// TX
 -1, 	// Q 
 250, 	// CH
 150, 	// JH
 170, 	// DF
// ==== AV ====
 0, 	// _ 
 60, 	// IY
 60, 	// IH
 60, 	// EY
 60, 	// EH
 60, 	// AE
 60, 	// AA
 60, 	// AY
 60, 	// AW
 60, 	// AH
 60, 	// AO
 60, 	// OW
 60, 	// OY
 60, 	// UH
 60, 	// UW
 59, 	// RR
 60, 	// YU
 60, 	// AX
 60, 	// IX
 60, 	// IR
 60, 	// ER
 60, 	// AR
 60, 	// OR
 60, 	// UR
 60, 	// W 
 60, 	// Y 
 60, 	// R 
 58, 	// L 
 0, 	// HX
 60, 	// OH
 58, 	// LX
 60, 	// M 
 55, 	// N 
 57, 	// NX
 58, 	// EL
 50, 	// DZ
 60, 	// EN
 0, 	// F 
 53, 	// V 
 0, 	// TH
 50, 	// DH
 0, 	// S 
 53, 	// Z 
 0, 	// SH
 53, 	// ZH
 0, 	// P 
 0, 	// B 
 0, 	// T 
 0, 	// D 
 0, 	// K 
 0, 	// G 
 64, 	// YR
 0, 	// TX
 44, 	// Q 
 0, 	// CH
 0, 	// JH
 44 };	// DF

// Female - F1,F2,F3,B1,B2,B3,AV data for each phoneme
//     Negative numbers are offsets into femdip table (multi-part formants)
//     Positive numbers are actual values
const short uk_femtar_def[] = {
// ==== F1 ====
 -1, 	// _ 
 -2, 	// IY
 -6, 	// IH
 -10, 	// EY
 -16, 	// EH
 -22, 	// AE
 775, 	// AA
 -28, 	// AY
 -36, 	// AW
 -42, 	// AH
 -48, 	// AO
 -54, 	// OW
 -60, 	// OY
 -68, 	// UH
 -74, 	// UW
 -80, 	// RR
 -86, 	// YU
 -92, 	// AX
 -98, 	// IX
 -104, 	// IR
 -110, 	// ER
 -114, 	// AR
 -120, 	// OR
 -126, 	// UR
 350, 	// W 
 320, 	// Y 
 350, 	// R 
 360, 	// L 
 -1, 	// HX
 725, 	// OH
 480, 	// LX
 350, 	// M 
 362, 	// N 
 276, 	// NX
 480, 	// EL
 280, 	// DZ
 450, 	// EN
 360, 	// F 
 300, 	// V 
 340, 	// TH
 320, 	// DH
 340, 	// S 
 300, 	// Z 
 320, 	// SH
 300, 	// ZH
 370, 	// P 
 280, 	// B 
 370, 	// T 
 300, 	// D 
 330, 	// K 
 280, 	// G 
 -132, 	// YR
 280, 	// TX
 -1, 	// Q 
 370, 	// CH
 280, 	// JH
 370, 	// DF
// ==== F2 ====
 -1, 	// _ 
 -138, 	// IY
 -142, 	// IH
 -146, 	// EY
 -152, 	// EH
 -158, 	// AE
 1106, 	// AA
 -164, 	// AY
 -170, 	// AW
 -176, 	// AH
 -182, 	// AO
 -188, 	// OW
 -194, 	// OY
 -202, 	// UH
 -208, 	// UW
 -214, 	// RR
 -220, 	// YU
 -226, 	// AX
 -232, 	// IX
 -238, 	// IR
 -244, 	// ER
 -248, 	// AR
 -254, 	// OR
 -260, 	// UR
 800, 	// W 
 2490, 	// Y 
 1033, 	// R 
 1000, 	// L 
 -1, 	// HX
 1019, 	// OH
 930, 	// LX
 1340, 	// M 
 2160, 	// N 
 2056, 	// NX
 990, 	// EL
 1860, 	// DZ
 1530, 	// EN
 1150, 	// F 
 1150, 	// V 
 1530, 	// TH
 732, 	// DH
 1640, 	// S 
 1640, 	// Z 
 1980, 	// SH
 1980, 	// ZH
 1150, 	// P 
 1150, 	// B 
 1860, 	// T 
 1860, 	// D 
 2190, 	// K 
 2190, 	// G 
 -266, 	// YR
 1860, 	// TX
 -1, 	// Q 
 2100, 	// CH
 2100, 	// JH
 1860, 	// DF
// ==== F3 ====
 -1, 	// _ 
 -272, 	// IY
 -276, 	// IH
 -280, 	// EY
 -286, 	// EH
 -292, 	// AE
 2765, 	// AA
 -298, 	// AY
 -306, 	// AW
 -312, 	// AH
 -318, 	// AO
 -324, 	// OW
 -330, 	// OY
 -338, 	// UH
 -344, 	// UW
 -350, 	// RR
 -356, 	// YU
 2697, 	// AX
 3200, 	// IX
 2310, 	// IR
 -362, 	// ER
 2200, 	// AR
 2150, 	// OR
 2100, 	// UR
 2630, 	// W 
 3400, 	// Y 
 1700, 	// R 
 3430, 	// L 
 -1, 	// HX
 2489, 	// OH
 2990, 	// LX
 2590, 	// M 
 2765, 	// N 
 3100, 	// NX
 3320, 	// EL
 3020, 	// DZ
 2920, 	// EN
 2460, 	// F 
 2460, 	// V 
 2940, 	// TH
 2940, 	// DH
 2930, 	// S 
 3000, 	// Z 
 2930, 	// SH
 2940, 	// ZH
 2470, 	// P 
 2470, 	// B 
 3020, 	// T 
 3020, 	// D 
 2710, 	// K 
 2710, 	// G 
 2852, 	// YR
 3000, 	// TX
 -1, 	// Q 
 3150, 	// CH
 3150, 	// JH
 3000, 	// DF
// ==== B1 ====
 -1, 	// _ 
 75, 	// IY
 75, 	// IH
 75, 	// EY
 80, 	// EH
 150, 	// AE
 180, 	// AA
 100, 	// AY
 100, 	// AW
 110, 	// AH
 70, 	// AO
 100, 	// OW
 100, 	// OY
 90, 	// UH
 90, 	// UW
 90, 	// RR
 80, 	// YU
 140, 	// AX
 80, 	// IX
 80, 	// IR
 110, 	// ER
 130, 	// AR
 90, 	// OR
 80, 	// UR
 80, 	// W 
 170, 	// Y 
 90, 	// R 
 90, 	// L 
 500, 	// HX
 90, 	// OH
 90, 	// LX
 120, 	// M 
 120, 	// N 
 120, 	// NX
 90, 	// EL
 120, 	// DZ
 110, 	// EN
 200, 	// F 
 140, 	// V 
 200, 	// TH
 120, 	// DH
 200, 	// S 
 140, 	// Z 
 200, 	// SH
 120, 	// ZH
 200, 	// P 
 100, 	// B 
 200, 	// T 
 110, 	// D 
 200, 	// K 
 100, 	// G 
 100, 	// YR
 90, 	// TX
 100, 	// Q 
 200, 	// CH
 120, 	// JH
 100, 	// DF
// ==== B2 ====
 -1, 	// _ 
 220, 	// IY
 190, 	// IH
 190, 	// EY
 160, 	// EH
 240, 	// AE
 200, 	// AA
 190, 	// AY
 150, 	// AW
 150, 	// AH
 130, 	// AO
 110, 	// OW
 180, 	// OY
 100, 	// UH
 100, 	// UW
 250, 	// RR
 170, 	// YU
 140, 	// AX
 180, 	// IX
 220, 	// IR
 190, 	// ER
 200, 	// AR
 170, 	// OR
 130, 	// UR
 80, 	// W 
 180, 	// Y 
 150, 	// R 
 110, 	// L 
 -1, 	// HX
 200, 	// OH
 110, 	// LX
 340, 	// M 
 200, 	// N 
 600, 	// NX
 120, 	// EL
 90, 	// DZ
 200, 	// EN
 140, 	// F 
 120, 	// V 
 220, 	// TH
 210, 	// DH
 200, 	// S 
 170, 	// Z 
 240, 	// SH
 160, 	// ZH
 180, 	// P 
 110, 	// B 
 150, 	// T 
 140, 	// D 
 160, 	// K 
 100, 	// G 
 100, 	// YR
 100, 	// TX
 -1, 	// Q 
 230, 	// CH
 170, 	// JH
 100, 	// DF
// ==== B3 ====
 -1, 	// _ 
 270, 	// IY
 220, 	// IH
 300, 	// EY
 270, 	// EH
 300, 	// AE
 180, 	// AA
 270, 	// AY
 280, 	// AW
 210, 	// AH
 110, 	// AO
 180, 	// OW
 180, 	// OY
 170, 	// UH
 180, 	// UW
 120, 	// RR
 220, 	// YU
 200, 	// AX
 240, 	// IX
 200, 	// IR
 150, 	// ER
 160, 	// AR
 130, 	// OR
 140, 	// UR
 110, 	// W 
 200, 	// Y 
 130, 	// R 
 120, 	// L 
 -1, 	// HX
 150, 	// OH
 130, 	// LX
 250, 	// M 
 350, 	// N 
 550, 	// NX
 200, 	// EL
 120, 	// DZ
 160, 	// EN
 150, 	// F 
 120, 	// V 
 300, 	// TH
 270, 	// DH
 200, 	// S 
 200, 	// Z 
 300, 	// SH
 300, 	// ZH
 180, 	// P 
 150, 	// B 
 250, 	// T 
 170, 	// D 
 280, 	// K 
 150, 	// G 
 130, 	// YR
 130, 	// TX
 -1, 	// Q 
 350, 	// CH
 350, 	// JH
 130, 	// DF
// ==== AV ====
 0, 	// _ 
 63, 	// IY
 63, 	// IH
 63, 	// EY
 63, 	// EH
 63, 	// AE
 63, 	// AA
 63, 	// AY
 63, 	// AW
 63, 	// AH
 63, 	// AO
 64, 	// OW
 64, 	// OY
 64, 	// UH
 64, 	// UW
 63, 	// RR
 64, 	// YU
 62, 	// AX
 63, 	// IX
 64, 	// IR
 64, 	// ER
 64, 	// AR
 64, 	// OR
 64, 	// UR
 64, 	// W 
 64, 	// Y 
 64, 	// R 
 62, 	// L 
 0, 	// HX
 64, 	// OH
 62, 	// LX
 60, 	// M 
 60, 	// N 
 62, 	// NX
 62, 	// EL
 50, 	// DZ
 60, 	// EN
 0, 	// F 
 53, 	// V 
 0, 	// TH
 53, 	// DH
 0, 	// S 
 53, 	// Z 
 0, 	// SH
 53, 	// ZH
 0, 	// P 
 0, 	// B 
 0, 	// T 
 0, 	// D 
 0, 	// K 
 0, 	// G 
 63, 	// YR
 0, 	// TX
 50, 	// Q 
 0, 	// CH
 0, 	// JH
 34 };	// DF

// Male - F1,F1T,F2,F2T,F3,F3T,B1,B1T,B2,B2T,B3,B3T,AV,AVT data for Multi-part formants
const short uk_maldip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _ 
 0, 	// _ 
 345, 	// IY F1
 40, 	// IY F1 duration
 330, 	// IY F1
 -1, 	// IY F1 duration
 362, 	// IH F1
 60, 	// IH F1 duration
 362, 	// IH F1
 -1, 	// IH F1 duration
 553, 	// EY F1
 60, 	// EY F1 duration
 345, 	// EY F1
 160, 	// EY F1 duration
 345, 	// EY F1
 -1, 	// EY F1 duration
 622, 	// EH F1
 60, 	// EH F1 duration
 622, 	// EH F1
 110, 	// EH F1 duration
 622, 	// EH F1
 -1, 	// EH F1 duration
 725, 	// AE F1
 130, 	// AE F1 duration
 725, 	// AE F1
 210, 	// AE F1 duration
 725, 	// AE F1
 -1, 	// AE F1 duration
 730, 	// AY F1
 20, 	// AY F1 duration
 730, 	// AY F1
 130, 	// AY F1 duration
 430, 	// AY F1
 210, 	// AY F1 duration
 430, 	// AY F1
 -1, 	// AY F1 duration
 710, 	// AW F1
 110, 	// AW F1 duration
 550, 	// AW F1
 230, 	// AW F1 duration
 550, 	// AW F1
 -1, 	// AW F1 duration
 760, 	// AH F1
 40, 	// AH F1 duration
 760, 	// AH F1
 100, 	// AH F1 duration
 760, 	// AH F1
 -1, 	// AH F1 duration
 414, 	// AO F1
 60, 	// AO F1 duration
 414, 	// AO F1
 110, 	// AO F1 duration
 414, 	// AO F1
 -1, 	// AO F1 duration
 540, 	// OW F1
 20, 	// OW F1 duration
 490, 	// OW F1
 100, 	// OW F1 duration
 345, 	// OW F1
 -1, 	// OW F1 duration
 530, 	// OY F1
 40, 	// OY F1 duration
 470, 	// OY F1
 110, 	// OY F1 duration
 470, 	// OY F1
 210, 	// OY F1 duration
 470, 	// OY F1
 -1, 	// OY F1 duration
 449, 	// UH F1
 70, 	// UH F1 duration
 449, 	// UH F1
 130, 	// UH F1 duration
 449, 	// UH F1
 -1, 	// UH F1 duration
 552, 	// RR F1
 60, 	// RR F1 duration
 572, 	// RR F1
 522, 	// RR F1 duration
 545, 	// RR F1
 -1, 	// RR F1 duration
 270, 	// YU F1
 15, 	// YU F1 duration
 304, 	// YU F1
 130, 	// YU F1 duration
 305, 	// YU F1
 -1, 	// YU F1 duration
 550, 	// AX F1
 30, 	// AX F1 duration
 550, 	// AX F1
 90, 	// AX F1 duration
 550, 	// AX F1
 -1, 	// AX F1 duration
 460, 	// IX F1
 30, 	// IX F1 duration
 460, 	// IX F1
 90, 	// IX F1 duration
 460, 	// IX F1
 -1, 	// IX F1 duration
 328, 	// IR F1
 20, 	// IR F1 duration
 414, 	// IR F1
 105, 	// IR F1 duration
 553, 	// IR F1
 -1, 	// IR F1 duration
 587, 	// ER F1
 40, 	// ER F1 duration
 656, 	// ER F1
 100, 	// ER F1 duration
 691, 	// ER F1
 -1, 	// ER F1 duration
 861, 	// AR F1
 30, 	// AR F1 duration
 570, 	// AR F1
 130, 	// AR F1 duration
 587, 	// AR F1
 -1, 	// AR F1 duration
 691, 	// OR F1
 20, 	// OR F1 duration
 518, 	// OR F1
 100, 	// OR F1 duration
 656, 	// OR F1
 -1, 	// OR F1 duration
 420, 	// UR F1
 20, 	// UR F1 duration
 440, 	// UR F1
 100, 	// UR F1 duration
 440, 	// UR F1
 -1, 	// UR F1 duration
 881, 	// YR F1
 10, 	// YR F1 duration
 554, 	// YR F1
 100, 	// YR F1 duration
 760, 	// YR F1
 -1, 	// YR F1 duration
 2373, 	// IY F2
 40, 	// IY F2 duration
 2373, 	// IY F2
 -1, 	// IY F2 duration
 2012, 	// IH F2
 60, 	// IH F2 duration
 2212, 	// IH F2
 -1, 	// IH F2 duration
 2039, 	// EY F2
 60, 	// EY F2 duration
 2102, 	// EY F2
 160, 	// EY F2 duration
 2180, 	// EY F2
 -1, 	// EY F2 duration
 1866, 	// EH F2
 80, 	// EH F2 duration
 1866, 	// EH F2
 140, 	// EH F2 duration
 1866, 	// EH F2
 -1, 	// EH F2 duration
 1470, 	// AE F2
 40, 	// AE F2 duration
 1538, 	// AE F2
 120, 	// AE F2 duration
 1642, 	// AE F2
 -1, 	// AE F2 duration
 1200, 	// AY F2
 40, 	// AY F2 duration
 1448, 	// AY F2
 120, 	// AY F2 duration
 2070, 	// AY F2
 -1, 	// AY F2 duration
 1200, 	// AW F2
 110, 	// AW F2 duration
 820, 	// AW F2
 225, 	// AW F2 duration
 820, 	// AW F2
 -1, 	// AW F2 duration
 1400, 	// AH F2
 40, 	// AH F2 duration
 1400, 	// AH F2
 100, 	// AH F2 duration
 1400, 	// AH F2
 -1, 	// AH F2 duration
 864, 	// AO F2
 60, 	// AO F2 duration
 888, 	// AO F2
 110, 	// AO F2 duration
 898, 	// AO F2
 -1, 	// AO F2 duration
 1365, 	// OW F2
 10, 	// OW F2 duration
 1071, 	// OW F2
 100, 	// OW F2 duration
 1002, 	// OW F2
 -1, 	// OW F2 duration
 933, 	// OY F2
 40, 	// OY F2 duration
 1451, 	// OY F2
 110, 	// OY F2 duration
 1814, 	// OY F2
 210, 	// OY F2 duration
 1814, 	// OY F2
 -1, 	// OY F2 duration
 1158, 	// UH F2
 70, 	// UH F2 duration
 1158, 	// UH F2
 130, 	// UH F2 duration
 1158, 	// UH F2
 -1, 	// UH F2 duration
 1434, 	// RR F2
 60, 	// RR F2 duration
 1434, 	// RR F2
 170, 	// RR F2 duration
 1434, 	// RR F2
 -1, 	// RR F2 duration
 2212, 	// YU F2
 15, 	// YU F2 duration
 1074, 	// YU F2
 130, 	// YU F2 duration
 1008, 	// YU F2
 -1, 	// YU F2 duration
 1247, 	// AX F2
 30, 	// AX F2 duration
 1247, 	// AX F2
 90, 	// AX F2 duration
 1269, 	// AX F2
 -1, 	// AX F2 duration
 1680, 	// IX F2
 30, 	// IX F2 duration
 1680, 	// IX F2
 90, 	// IX F2 duration
 1680, 	// IX F2
 -1, 	// IX F2 duration
 2212, 	// IR F2
 20, 	// IR F2 duration
 2281, 	// IR F2
 105, 	// IR F2 duration
 1659, 	// IR F2
 -1, 	// IR F2 duration
 1935, 	// ER F2
 80, 	// ER F2 duration
 1711, 	// ER F2
 100, 	// ER F2 duration
 1486, 	// ER F2
 -1, 	// ER F2 duration
 1591, 	// AR F2
 30, 	// AR F2 duration
 1123, 	// AR F2
 100, 	// AR F2 duration
 1434, 	// AR F2
 -1, 	// AR F2 duration
 1521, 	// OR F2
 20, 	// OR F2 duration
 1209, 	// OR F2
 100, 	// OR F2 duration
 1417, 	// OR F2
 -1, 	// OR F2 duration
 860, 	// UR F2
 20, 	// UR F2 duration
 1170, 	// UR F2
 100, 	// UR F2 duration
 1200, 	// UR F2
 -1, 	// UR F2 duration
 1244, 	// YR F2
 10, 	// YR F2 duration
 1659, 	// YR F2
 100, 	// YR F2 duration
 1469, 	// YR F2
 -1, 	// YR F2 duration
 2886, 	// IY F3
 40, 	// IY F3 duration
 2886, 	// IY F3
 -1, 	// IY F3 duration
 2750, 	// IH F3
 60, 	// IH F3 duration
 2750, 	// IH F3
 -1, 	// IH F3 duration
 2660, 	// EY F3
 60, 	// EY F3 duration
 2700, 	// EY F3
 160, 	// EY F3 duration
 2700, 	// EY F3
 -1, 	// EY F3 duration
 2660, 	// EH F3
 90, 	// EH F3 duration
 2670, 	// EH F3
 140, 	// EH F3 duration
 2680, 	// EH F3
 -1, 	// EH F3 duration
 2480, 	// AE F3
 130, 	// AE F3 duration
 2480, 	// AE F3
 2480, 	// AE F3 duration
 2480, 	// AE F3
 -1, 	// AE F3 duration
 2713, 	// AY F3
 120, 	// AY F3 duration
 2650, 	// AY F3
 160, 	// AY F3 duration
 2696, 	// AY F3
 210, 	// AY F3 duration
 2696, 	// AY F3
 -1, 	// AY F3 duration
 2650, 	// AW F3
 120, 	// AW F3 duration
 2550, 	// AW F3
 230, 	// AW F3 duration
 2550, 	// AW F3
 -1, 	// AW F3 duration
 2730, 	// AH F3
 40, 	// AH F3 duration
 2730, 	// AH F3
 100, 	// AH F3 duration
 2730, 	// AH F3
 -1, 	// AH F3 duration
 2620, 	// AO F3
 20, 	// AO F3 duration
 2690, 	// AO F3
 50, 	// AO F3 duration
 2690, 	// AO F3
 -1, 	// AO F3 duration
 2498, 	// OW F3
 10, 	// OW F3 duration
 2385, 	// OW F3
 100, 	// OW F3 duration
 2333, 	// OW F3
 -1, 	// OW F3 duration
 2527, 	// OY F3
 40, 	// OY F3 duration
 2450, 	// OY F3
 110, 	// OY F3 duration
 2450, 	// OY F3
 160, 	// OY F3 duration
 2450, 	// OY F3
 -1, 	// OY F3 duration
 2471, 	// UH F3
 70, 	// UH F3 duration
 2471, 	// UH F3
 130, 	// UH F3 duration
 2470, 	// UH F3
 -1, 	// UH F3 duration
 2333, 	// RR F3
 60, 	// RR F3 duration
 2333, 	// RR F3
 170, 	// RR F3 duration
 2333, 	// RR F3
 -1, 	// RR F3 duration
 2622, 	// YU F3
 15, 	// YU F3 duration
 2471, 	// YU F3
 130, 	// YU F3 duration
 2556, 	// YU F3
 -1, 	// YU F3 duration
 2646, 	// AX F3
 30, 	// AX F3 duration
 2646, 	// AX F3
 90, 	// AX F3 duration
 2646, 	// AX F3
 -1, 	// AX F3 duration
 2520, 	// IX F3
 30, 	// IX F3 duration
 2520, 	// IX F3
 90, 	// IX F3 duration
 2520, 	// IX F3
 -1, 	// IX F3 duration
 2852, 	// IR F3
 20, 	// IR F3 duration
 2578, 	// IR F3
 105, 	// IR F3 duration
 2627, 	// IR F3
 -1, 	// IR F3 duration
 2696, 	// ER F3
 100, 	// ER F3 duration
 2627, 	// ER F3
 100, 	// ER F3 duration
 2558, 	// ER F3
 -1, 	// ER F3 duration
 2546, 	// AR F3
 30, 	// AR F3 duration
 2540, 	// AR F3
 100, 	// AR F3 duration
 2570, 	// AR F3
 -1, 	// AR F3 duration
 2644, 	// OR F3
 10, 	// OR F3 duration
 2498, 	// OR F3
 100, 	// OR F3 duration
 2575, 	// OR F3
 -1, 	// OR F3 duration
 2100, 	// UR F3
 20, 	// UR F3 duration
 1600, 	// UR F3
 100, 	// UR F3 duration
 1560, 	// UR F3
 -1, 	// UR F3 duration
 2814, 	// YR F3
 10, 	// YR F3 duration
 2659, 	// YR F3
 100, 	// YR F3 duration
 2690, 	// YR F3
 -1, 	// YR F3 duration
// ====== Bandwidths and duration ======
 130, 	// AY B1
 90, 	// AY B1 duration
 65, 	// AY B1
 220, 	// AY B1 duration
 65, 	// AY B1
 -1, 	// AY B1 duration
 120, 	// AW B1
 130, 	// AW B1 duration
 100, 	// AW B1
 240, 	// AW B1 duration
 100, 	// AW B1
 -1, 	// AW B1 duration
 110, 	// AE B2
 130, 	// AE B2 duration
 100, 	// AE B2
 210, 	// AE B2 duration
 100, 	// AE B2
 -1, 	// AE B2 duration
 110, 	// OY B2
 40, 	// OY B2 duration
 140, 	// OY B2
 110, 	// OY B2 duration
 220, 	// OY B2
 -1, 	// OY B2 duration
 150, 	// YU B2
 15, 	// YU B2 duration
 110, 	// YU B2
 80, 	// YU B2 duration
 70, 	// YU B2
 -1, 	// YU B2 duration
 250, 	// YU B3
 15, 	// YU B3 duration
 130, 	// YU B3
 80, 	// YU B3 duration
 130, 	// YU B3
 -1, 	// YU B3 duration
// ====== Amplitude of Voicing ======
 0};

// Female diphthongs
const short uk_femdip_def[] = {
// ====== Formants Frequencies and duration ======
 0, 	// _ 
 0, 	// _ 
 380, 	// IY F1
 10, 	// IY F1 duration
 380, 	// IY F1
 -1, 	// IY F1 duration
 466, 	// IH F1
 60, 	// IH F1 duration
 466, 	// IH F1
 -1, 	// IH F1 duration
 639, 	// EY F1
 30, 	// EY F1 duration
 639, 	// EY F1
 170, 	// EY F1 duration
 639, 	// EY F1
 -1, 	// EY F1 duration
 708, 	// EH F1
 90, 	// EH F1 duration
 708, 	// EH F1
 140, 	// EH F1 duration
 708, 	// EH F1
 -1, 	// EH F1 duration
 830, 	// AE F1
 50, 	// AE F1 duration
 1020, 	// AE F1
 190, 	// AE F1 duration
 1020, 	// AE F1
 -1, 	// AE F1 duration
 846, 	// AY F1
 40, 	// AY F1 duration
 800, 	// AY F1
 120, 	// AY F1 duration
 730, 	// AY F1
 220, 	// AY F1 duration
 590, 	// AY F1
 -1, 	// AY F1 duration
 850, 	// AW F1
 20, 	// AW F1 duration
 1000, 	// AW F1
 100, 	// AW F1 duration
 680, 	// AW F1
 -1, 	// AW F1 duration
 830, 	// AH F1
 40, 	// AH F1 duration
 830, 	// AH F1
 100, 	// AH F1 duration
 830, 	// AH F1
 -1, 	// AH F1 duration
 518, 	// AO F1
 120, 	// AO F1 duration
 518, 	// AO F1
 219, 	// AO F1 duration
 518, 	// AO F1
 -1, 	// AO F1 duration
 720, 	// OW F1
 40, 	// OW F1 duration
 530, 	// OW F1
 170, 	// OW F1 duration
 510, 	// OW F1
 -1, 	// OW F1 duration
 501, 	// OY F1
 60, 	// OY F1 duration
 740, 	// OY F1
 133, 	// OY F1 duration
 535, 	// OY F1
 220, 	// OY F1 duration
 432, 	// OY F1
 -1, 	// OY F1 duration
 600, 	// UH F1
 50, 	// UH F1 duration
 700, 	// UH F1
 130, 	// UH F1 duration
 700, 	// UH F1
 -1, 	// UH F1 duration
 430, 	// UW F1
 40, 	// UW F1 duration
 400, 	// UW F1
 180, 	// UW F1 duration
 400, 	// UW F1
 -1, 	// UW F1 duration
 691, 	// RR F1
 9, 	// RR F1 duration
 760, 	// RR F1
 248, 	// RR F1 duration
 755, 	// RR F1
 -1, 	// RR F1 duration
 350, 	// YU F1
 90, 	// YU F1 duration
 380, 	// YU F1
 140, 	// YU F1 duration
 380, 	// YU F1
 -1, 	// YU F1 duration
 622, 	// AX F1
 30, 	// AX F1 duration
 622, 	// AX F1
 90, 	// AX F1 duration
 622, 	// AX F1
 -1, 	// AX F1 duration
 530, 	// IX F1
 30, 	// IX F1 duration
 530, 	// IX F1
 90, 	// IX F1 duration
 530, 	// IX F1
 -1, 	// IX F1 duration
 360, 	// IR F1
 100, 	// IR F1 duration
 540, 	// IR F1
 170, 	// IR F1 duration
 540, 	// IR F1
 -1, 	// IR F1 duration
 725, 	// ER F1
 10, 	// ER F1 duration
 881, 	// ER F1
 -1, 	// ER F1 duration
 960, 	// AR F1
 100, 	// AR F1 duration
 700, 	// AR F1
 180, 	// AR F1 duration
 700, 	// AR F1
 -1, 	// AR F1 duration
 640, 	// OR F1
 90, 	// OR F1 duration
 600, 	// OR F1
 180, 	// OR F1 duration
 600, 	// OR F1
 -1, 	// OR F1 duration
 420, 	// UR F1
 80, 	// UR F1 duration
 520, 	// UR F1
 170, 	// UR F1 duration
 520, 	// UR F1
 -1, 	// UR F1 duration
 881, 	// YR F1
 140, 	// YR F1 duration
 753, 	// YR F1
 210, 	// YR F1 duration
 861, 	// YR F1
 -1, 	// YR F1 duration
 2627, 	// IY F2
 10, 	// IY F2 duration
 2627, 	// IY F2
 -1, 	// IY F2 duration
 2497, 	// IH F2
 60, 	// IH F2 duration
 2497, 	// IH F2
 -1, 	// IH F2 duration
 2316, 	// EY F2
 30, 	// EY F2 duration
 2368, 	// EY F2
 170, 	// EY F2 duration
 2454, 	// EY F2
 -1, 	// EY F2 duration
 2185, 	// EH F2
 80, 	// EH F2 duration
 2185, 	// EH F2
 140, 	// EH F2 duration
 2185, 	// EH F2
 -1, 	// EH F2 duration
 2130, 	// AE F2
 110, 	// AE F2 duration
 1900, 	// AE F2
 190, 	// AE F2 duration
 1900, 	// AE F2
 -1, 	// AE F2 duration
 1380, 	// AY F2
 90, 	// AY F2 duration
 2070, 	// AY F2
 200, 	// AY F2 duration
 2400, 	// AY F2
 -1, 	// AY F2 duration
 1750, 	// AW F2
 60, 	// AW F2 duration
 1240, 	// AW F2
 170, 	// AW F2 duration
 1240, 	// AW F2
 -1, 	// AW F2 duration
 1570, 	// AH F2
 40, 	// AH F2 duration
 1650, 	// AH F2
 100, 	// AH F2 duration
 1650, 	// AH F2
 -1, 	// AH F2 duration
 960, 	// AO F2
 120, 	// AO F2 duration
 960, 	// AO F2
 220, 	// AO F2 duration
 960, 	// AO F2
 -1, 	// AO F2 duration
 1350, 	// OW F2
 40, 	// OW F2 duration
 970, 	// OW F2
 140, 	// OW F2 duration
 960, 	// OW F2
 -1, 	// OW F2 duration
 898, 	// OY F2
 40, 	// OY F2 duration
 1090, 	// OY F2
 150, 	// OY F2 duration
 1987, 	// OY F2
 220, 	// OY F2 duration
 2212, 	// OY F2
 -1, 	// OY F2 duration
 1350, 	// UH F2
 50, 	// UH F2 duration
 1350, 	// UH F2
 130, 	// UH F2 duration
 1350, 	// UH F2
 -1, 	// UH F2 duration
 1370, 	// UW F2
 40, 	// UW F2 duration
 1160, 	// UW F2
 180, 	// UW F2 duration
 1120, 	// UW F2
 -1, 	// UW F2 duration
 1434, 	// RR F2
 9, 	// RR F2 duration
 1417, 	// RR F2
 248, 	// RR F2 duration
 1400, 	// RR F2
 -1, 	// RR F2 duration
 2298, 	// YU F2
 40, 	// YU F2 duration
 1244, 	// YU F2
 210, 	// YU F2 duration
 1244, 	// YU F2
 -1, 	// YU F2 duration
 1607, 	// AX F2
 30, 	// AX F2 duration
 1607, 	// AX F2
 90, 	// AX F2 duration
 1607, 	// AX F2
 -1, 	// AX F2 duration
 2470, 	// IX F2
 30, 	// IX F2 duration
 2440, 	// IX F2
 90, 	// IX F2 duration
 2440, 	// IX F2
 -1, 	// IX F2 duration
 2700, 	// IR F2
 100, 	// IR F2 duration
 1800, 	// IR F2
 170, 	// IR F2 duration
 1740, 	// IR F2
 -1, 	// IR F2 duration
 2126, 	// ER F2
 10, 	// ER F2 duration
 1624, 	// ER F2
 -1, 	// ER F2 duration
 1470, 	// AR F2
 100, 	// AR F2 duration
 1650, 	// AR F2
 180, 	// AR F2 duration
 1650, 	// AR F2
 -1, 	// AR F2 duration
 1250, 	// OR F2
 100, 	// OR F2 duration
 1600, 	// OR F2
 190, 	// OR F2 duration
 1600, 	// OR F2
 -1, 	// OR F2 duration
 1350, 	// UR F2
 80, 	// UR F2 duration
 1550, 	// UR F2
 170, 	// UR F2 duration
 1550, 	// UR F2
 -1, 	// UR F2 duration
 1417, 	// YR F2
 150, 	// YR F2 duration
 1814, 	// YR F2
 210, 	// YR F2 duration
 1676, 	// YR F2
 -1, 	// YR F2 duration
 3247, 	// IY F3
 10, 	// IY F3 duration
 3247, 	// IY F3
 -1, 	// IY F3 duration
 3042, 	// IH F3
 60, 	// IH F3 duration
 3042, 	// IH F3
 -1, 	// IH F3 duration
 3007, 	// EY F3
 20, 	// EY F3 duration
 3017, 	// EY F3
 170, 	// EY F3 duration
 3024, 	// EY F3
 -1, 	// EY F3 duration
 3145, 	// EH F3
 90, 	// EH F3 duration
 3145, 	// EH F3
 140, 	// EH F3 duration
 3145, 	// EH F3
 -1, 	// EH F3 duration
 3100, 	// AE F3
 110, 	// AE F3 duration
 3150, 	// AE F3
 190, 	// AE F3 duration
 3150, 	// AE F3
 -1, 	// AE F3 duration
 2660, 	// AY F3
 150, 	// AY F3 duration
 2680, 	// AY F3
 200, 	// AY F3 duration
 2740, 	// AY F3
 240, 	// AY F3 duration
 2817, 	// AY F3
 -1, 	// AY F3 duration
 3050, 	// AW F3
 70, 	// AW F3 duration
 2900, 	// AW F3
 200, 	// AW F3 duration
 2900, 	// AW F3
 -1, 	// AW F3 duration
 3060, 	// AH F3
 40, 	// AH F3 duration
 3060, 	// AH F3
 100, 	// AH F3 duration
 3060, 	// AH F3
 -1, 	// AH F3 duration
 2614, 	// AO F3
 40, 	// AO F3 duration
 2614, 	// AO F3
 200, 	// AO F3 duration
 2614, 	// AO F3
 -1, 	// AO F3 duration
 2960, 	// OW F3
 40, 	// OW F3 duration
 2960, 	// OW F3
 200, 	// OW F3 duration
 2960, 	// OW F3
 -1, 	// OW F3 duration
 2627, 	// OY F3
 140, 	// OY F3 duration
 2800, 	// OY F3
 200, 	// OY F3 duration
 2661, 	// OY F3
 270, 	// OY F3 duration
 2661, 	// OY F3
 -1, 	// OY F3 duration
 3050, 	// UH F3
 50, 	// UH F3 duration
 3050, 	// UH F3
 130, 	// UH F3 duration
 3050, 	// UH F3
 -1, 	// UH F3 duration
 2800, 	// UW F3
 40, 	// UW F3 duration
 2700, 	// UW F3
 180, 	// UW F3 duration
 2700, 	// UW F3
 -1, 	// UW F3 duration
 2696, 	// RR F3
 9, 	// RR F3 duration
 2696, 	// RR F3
 248, 	// RR F3 duration
 2690, 	// RR F3
 -1, 	// RR F3 duration
 3232, 	// YU F3
 10, 	// YU F3 duration
 3007, 	// YU F3
 20, 	// YU F3 duration
 2661, 	// YU F3
 -1, 	// YU F3 duration
 2760, 	// ER F3
 10, 	// ER F3 duration
 2760, 	// ER F3
 -1, 	// ER F3 duration
// ====== Bandwidths and duration ======
// ====== Amplitude of Voicing ======
 0};

// Offsets into Amplitude data
const short uk_ptram_def[] = {
 0, 	// _ 
 0, 	// IY
 0, 	// IH
 0, 	// EY
 0, 	// EH
 0, 	// AE
 0, 	// AA
 0, 	// AY
 0, 	// AW
 0, 	// AH
 0, 	// AO
 0, 	// OW
 0, 	// OY
 0, 	// UH
 0, 	// UW
 0, 	// RR
 0, 	// YU
 0, 	// AX
 0, 	// IX
 0, 	// IR
 0, 	// ER
 0, 	// AR
 0, 	// OR
 0, 	// UR
 0, 	// W 
 0, 	// Y 
 0, 	// R 
 0, 	// L 
 0, 	// HX
 1, 	// OH
 0, 	// LX
 0, 	// M 
 0, 	// N 
 0, 	// NX
 0, 	// EL
 31, 	// DZ
 0, 	// EN
 61, 	// F 
 91, 	// V 
 121, 	// TH
 151, 	// DH
 181, 	// S 
 211, 	// Z 
 241, 	// SH
 271, 	// ZH
 301, 	// P 
 331, 	// B 
 361, 	// T 
 391, 	// D 
 421, 	// K 
 451, 	// G 
 0, 	// YR
 481, 	// TX
 0, 	// Q 
 511, 	// CH
 541, 	// JH
 571 };	// DF

// Offsets into Locus data
const short uk_plocu_def[] = {
// ==== Front ====
 0, 	// _ 
 0, 	// IY
 0, 	// IH
 0, 	// EY
 0, 	// EH
 0, 	// AE
 0, 	// AA
 0, 	// AY
 0, 	// AW
 0, 	// AH
 0, 	// AO
 0, 	// OW
 0, 	// OY
 0, 	// UH
 0, 	// UW
 0, 	// RR
 0, 	// YU
 0, 	// AX
 0, 	// IX
 0, 	// IR
 0, 	// ER
 0, 	// AR
 0, 	// OR
 0, 	// UR
 0, 	// W 
 0, 	// Y 
 1, 	// R 
 0, 	// L 
 0, 	// HX
 0, 	// OH
 0, 	// LX
 10, 	// M 
 19, 	// N 
 28, 	// NX
 0, 	// EL
 37, 	// DZ
 46, 	// EN
 55, 	// F 
 64, 	// V 
 73, 	// TH
 82, 	// DH
 91, 	// S 
 100, 	// Z 
 109, 	// SH
 118, 	// ZH
 127, 	// P 
 136, 	// B 
 145, 	// T 
 154, 	// D 
 163, 	// K 
 172, 	// G 
 0, 	// YR
 181, 	// TX
 0, 	// Q 
 190, 	// CH
 199, 	// JH
 208, 	// DF
// ==== Back ====
 217, 	// _ 
 0, 	// IY
 0, 	// IH
 0, 	// EY
 0, 	// EH
 0, 	// AE
 0, 	// AA
 0, 	// AY
 0, 	// AW
 0, 	// AH
 0, 	// AO
 0, 	// OW
 0, 	// OY
 0, 	// UH
 0, 	// UW
 0, 	// RR
 0, 	// YU
 0, 	// AX
 0, 	// IX
 0, 	// IR
 0, 	// ER
 0, 	// AR
 0, 	// OR
 226, 	// UR
 0, 	// W 
 0, 	// Y 
 235, 	// R 
 0, 	// L 
 0, 	// HX
 0, 	// OH
 0, 	// LX
 244, 	// M 
 253, 	// N 
 262, 	// NX
 0, 	// EL
 271, 	// DZ
 280, 	// EN
 289, 	// F 
 298, 	// V 
 307, 	// TH
 316, 	// DH
 325, 	// S 
 334, 	// Z 
 343, 	// SH
 352, 	// ZH
 361, 	// P 
 370, 	// B 
 379, 	// T 
 388, 	// D 
 397, 	// K 
 406, 	// G 
 0, 	// YR
 415, 	// TX
 0, 	// Q 
 424, 	// CH
 433, 	// JH
 442, 	// DF
// ==== Round ====
 0, 	// _ 
 0, 	// IY
 0, 	// IH
 0, 	// EY
 0, 	// EH
 0, 	// AE
 0, 	// AA
 0, 	// AY
 0, 	// AW
 0, 	// AH
 451, 	// AO
 0, 	// OW
 0, 	// OY
 0, 	// UH
 0, 	// UW
 0, 	// RR
 0, 	// YU
 0, 	// AX
 0, 	// IX
 0, 	// IR
 0, 	// ER
 0, 	// AR
 0, 	// OR
 0, 	// UR
 0, 	// W 
 0, 	// Y 
 460, 	// R 
 0, 	// L 
 0, 	// HX
 0, 	// OH
 0, 	// LX
 469, 	// M 
 478, 	// N 
 487, 	// NX
 0, 	// EL
 496, 	// DZ
 505, 	// EN
 514, 	// F 
 523, 	// V 
 532, 	// TH
 541, 	// DH
 550, 	// S 
 559, 	// Z 
 568, 	// SH
 577, 	// ZH
 586, 	// P 
 595, 	// B 
 604, 	// T 
 613, 	// D 
 622, 	// K 
 631, 	// G 
 0, 	// YR
 640, 	// TX
 0, 	// Q 
 649, 	// CH
 658, 	// JH
 667, 	// DF
// ==== Low ====
 0, 	// _ 
 0, 	// IY
 0, 	// IH
 0, 	// EY
 0, 	// EH
 0, 	// AE
 0, 	// AA
 0, 	// AY
 0, 	// AW
 0, 	// AH
 0, 	// AO
 0, 	// OW
 0, 	// OY
 0, 	// UH
 676, 	// UW
 0, 	// RR
 0, 	// YU
 0, 	// AX
 0, 	// IX
 0, 	// IR
 0, 	// ER
 0, 	// AR
 0, 	// OR
 0, 	// UR
 0, 	// W 
 0, 	// Y 
 685, 	// R 
 0, 	// L 
 0, 	// HX
 0, 	// OH
 0, 	// LX
 694, 	// M 
 703, 	// N 
 712, 	// NX
 0, 	// EL
 721, 	// DZ
 730, 	// EN
 739, 	// F 
 748, 	// V 
 757, 	// TH
 766, 	// DH
 775, 	// S 
 784, 	// Z 
 793, 	// SH
 802, 	// ZH
 811, 	// P 
 820, 	// B 
 829, 	// T 
 838, 	// D 
 847, 	// K 
 856, 	// G 
 0, 	// YR
 865, 	// TX
 0, 	// Q 
 874, 	// CH
 883, 	// JH
 0 };	// DF

// Male Locus data
const short uk_maleloc_def[] = {
 0, 
// Front
 -1, 	// R  F1 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 1000, 	// R  F2 locus
 100, 	// R  percent
 55, 	// R  transition duration
 1550, 	// R  F3 locus
 100, 	// R  percent
 40, 	// R  transition duration
 470, 	// M  F1 locus
 30, 	// M  percent
 30, 	// M  transition duration
 950, 	// M  F2 locus
 10, 	// M  percent
 35, 	// M  transition duration
 2150, 	// M  F3 locus
 30, 	// M  percent
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
 220, 	// NX F1 locus
 25, 	// NX percent
 40, 	// NX transition duration
 2200, 	// NX F2 locus
 15, 	// NX percent
 60, 	// NX transition duration
 3000, 	// NX F3 locus
 105, 	// NX percent
 60, 	// NX transition duration
 340, 	// DZ F1 locus
 10, 	// DZ percent
 45, 	// DZ transition duration
 1720, 	// DZ F2 locus
 20, 	// DZ percent
 50, 	// DZ transition duration
 2700, 	// DZ F3 locus
 0, 	// DZ percent
 50, 	// DZ transition duration
 450, 	// EN F1 locus
 20, 	// EN percent
 35, 	// EN transition duration
 1350, 	// EN F2 locus
 75, 	// EN percent
 35, 	// EN transition duration
 2600, 	// EN F3 locus
 40, 	// EN percent
 45, 	// EN transition duration
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
 1350, 	// TH F2 locus
 20, 	// TH percent
 50, 	// TH transition duration
 2700, 	// TH F3 locus
 0, 	// TH percent
 50, 	// TH transition duration
 340, 	// DH F1 locus
 10, 	// DH percent
 45, 	// DH transition duration
 1720, 	// DH F2 locus
 20, 	// DH percent
 50, 	// DH transition duration
 2700, 	// DH F3 locus
 0, 	// DH percent
 50, 	// DH transition duration
 310, 	// S  F1 locus
 40, 	// S  percent
 40, 	// S  transition duration
 1240, 	// S  F2 locus
 40, 	// S  percent
 50, 	// S  transition duration
 2550, 	// S  F3 locus
 0, 	// S  percent
 70, 	// S  transition duration
 310, 	// Z  F1 locus
 40, 	// Z  percent
 40, 	// Z  transition duration
 1240, 	// Z  F2 locus
 35, 	// Z  percent
 50, 	// Z  transition duration
 2550, 	// Z  F3 locus
 0, 	// Z  percent
 70, 	// Z  transition duration
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
 350, 	// P  F1 locus
 55, 	// P  percent
 20, 	// P  transition duration
 950, 	// P  F2 locus
 56, 	// P  percent
 30, 	// P  transition duration
 2200, 	// P  F3 locus
 25, 	// P  percent
 45, 	// P  transition duration
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
 1800, 	// T  F2 locus
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
 210, 	// K  F1 locus
 33, 	// K  percent
 45, 	// K  transition duration
 1900, 	// K  F2 locus
 20, 	// K  percent
 55, 	// K  transition duration
 3000, 	// K  F3 locus
 117, 	// K  percent
 50, 	// K  transition duration
 250, 	// G  F1 locus
 33, 	// G  percent
 45, 	// G  transition duration
 2101, 	// G  F2 locus
 10, 	// G  percent
 80, 	// G  transition duration
 3000, 	// G  F3 locus
 20, 	// G  percent
 20, 	// G  transition duration
 320, 	// TX F1 locus
 43, 	// TX percent
 35, 	// TX transition duration
 1800, 	// TX F2 locus
 66, 	// TX percent
 35, 	// TX transition duration
 2650, 	// TX F3 locus
 30, 	// TX percent
 45, 	// TX transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 2250, 	// CH F2 locus
 25, 	// CH percent
 70, 	// CH transition duration
 2900, 	// CH F3 locus
 19, 	// CH percent
 70, 	// CH transition duration
 240, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1750, 	// JH F2 locus
 25, 	// JH percent
 70, 	// JH transition duration
 2750, 	// JH F3 locus
 19, 	// JH percent
 70, 	// JH transition duration
 250, 	// DF F1 locus
 43, 	// DF percent
 35, 	// DF transition duration
 1800, 	// DF F2 locus
 66, 	// DF percent
 35, 	// DF transition duration
 2650, 	// DF F3 locus
 30, 	// DF percent
 45, 	// DF transition duration
// Back
 -1, 	// _  F1 locus
 -1, 	// _  percent
 -1, 	// _  transition duration
 -1, 	// _  F2 locus
 -1, 	// _  percent
 -1, 	// _  transition duration
 -1, 	// _  F3 locus
 -1, 	// _  percent
 -1, 	// _  transition duration
 -1, 	// UR F1 locus
 -1, 	// UR percent
 -1, 	// UR transition duration
 -1, 	// UR F2 locus
 -1, 	// UR percent
 -1, 	// UR transition duration
 -1, 	// UR F3 locus
 -1, 	// UR percent
 -1, 	// UR transition duration
 -1, 	// R  F1 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 1000, 	// R  F2 locus
 100, 	// R  percent
 55, 	// R  transition duration
 1500, 	// R  F3 locus
 100, 	// R  percent
 40, 	// R  transition duration
 450, 	// M  F1 locus
 20, 	// M  percent
 30, 	// M  transition duration
 1, 	// M  F2 locus
 88, 	// M  percent
 40, 	// M  transition duration
 1950, 	// M  F3 locus
 80, 	// M  percent
 25, 	// M  transition duration
 220, 	// N  F1 locus
 20, 	// N  percent
 30, 	// N  transition duration
 1420, 	// N  F2 locus
 25, 	// N  percent
 75, 	// N  transition duration
 2600, 	// N  F3 locus
 30, 	// N  percent
 60, 	// N  transition duration
 220, 	// NX F1 locus
 25, 	// NX percent
 40, 	// NX transition duration
 1800, 	// NX F2 locus
 20, 	// NX percent
 70, 	// NX transition duration
 2150, 	// NX F3 locus
 20, 	// NX percent
 70, 	// NX transition duration
 350, 	// DZ F1 locus
 10, 	// DZ percent
 50, 	// DZ transition duration
 1700, 	// DZ F2 locus
 12, 	// DZ percent
 55, 	// DZ transition duration
 2720, 	// DZ F3 locus
 11, 	// DZ percent
 55, 	// DZ transition duration
 450, 	// EN F1 locus
 20, 	// EN percent
 30, 	// EN transition duration
 1420, 	// EN F2 locus
 25, 	// EN percent
 75, 	// EN transition duration
 2600, 	// EN F3 locus
 30, 	// EN percent
 60, 	// EN transition duration
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
 2720, 	// TH F3 locus
 11, 	// TH percent
 55, 	// TH transition duration
 350, 	// DH F1 locus
 10, 	// DH percent
 50, 	// DH transition duration
 1700, 	// DH F2 locus
 12, 	// DH percent
 55, 	// DH transition duration
 2720, 	// DH F3 locus
 11, 	// DH percent
 55, 	// DH transition duration
 310, 	// S  F1 locus
 40, 	// S  percent
 40, 	// S  transition duration
 1240, 	// S  F2 locus
 40, 	// S  percent
 50, 	// S  transition duration
 2630, 	// S  F3 locus
 0, 	// S  percent
 70, 	// S  transition duration
 310, 	// Z  F1 locus
 40, 	// Z  percent
 40, 	// Z  transition duration
 1240, 	// Z  F2 locus
 35, 	// Z  percent
 60, 	// Z  transition duration
 2630, 	// Z  F3 locus
 0, 	// Z  percent
 70, 	// Z  transition duration
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
 350, 	// P  F1 locus
 45, 	// P  percent
 25, 	// P  transition duration
 920, 	// P  F2 locus
 46, 	// P  percent
 30, 	// P  transition duration
 2250, 	// P  F3 locus
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
 40, 	// T  percent
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
 210, 	// K  F1 locus
 33, 	// K  percent
 50, 	// K  transition duration
 1400, 	// K  F2 locus
 16, 	// K  percent
 50, 	// K  transition duration
 2150, 	// K  F3 locus
 20, 	// K  percent
 90, 	// K  transition duration
 300, 	// G  F1 locus
 33, 	// G  percent
 50, 	// G  transition duration
 1782, 	// G  F2 locus
 16, 	// G  percent
 60, 	// G  transition duration
 2152, 	// G  F3 locus
 0, 	// G  percent
 90, 	// G  transition duration
 320, 	// TX F1 locus
 43, 	// TX percent
 50, 	// TX transition duration
 1700, 	// TX F2 locus
 40, 	// TX percent
 75, 	// TX transition duration
 2600, 	// TX F3 locus
 0, 	// TX percent
 50, 	// TX transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1680, 	// CH F2 locus
 10, 	// CH percent
 70, 	// CH transition duration
 2450, 	// CH F3 locus
 10, 	// CH percent
 70, 	// CH transition duration
 245, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1680, 	// JH F2 locus
 10, 	// JH percent
 70, 	// JH transition duration
 2450, 	// JH F3 locus
 10, 	// JH percent
 70, 	// JH transition duration
 250, 	// DF F1 locus
 43, 	// DF percent
 50, 	// DF transition duration
 1700, 	// DF F2 locus
 40, 	// DF percent
 75, 	// DF transition duration
 2600, 	// DF F3 locus
 0, 	// DF percent
 50, 	// DF transition duration
// Round
 -1, 	// AO F1 locus
 -1, 	// AO percent
 -1, 	// AO transition duration
 -1, 	// AO F2 locus
 -1, 	// AO percent
 -1, 	// AO transition duration
 -1, 	// AO F3 locus
 -1, 	// AO percent
 -1, 	// AO transition duration
 -1, 	// R  F1 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 1000, 	// R  F2 locus
 100, 	// R  percent
 50, 	// R  transition duration
 1500, 	// R  F3 locus
 100, 	// R  percent
 40, 	// R  transition duration
 450, 	// M  F1 locus
 20, 	// M  percent
 30, 	// M  transition duration
 1, 	// M  F2 locus
 88, 	// M  percent
 40, 	// M  transition duration
 1950, 	// M  F3 locus
 80, 	// M  percent
 25, 	// M  transition duration
 450, 	// N  F1 locus
 20, 	// N  percent
 30, 	// N  transition duration
 1550, 	// N  F2 locus
 25, 	// N  percent
 95, 	// N  transition duration
 2320, 	// N  F3 locus
 30, 	// N  percent
 95, 	// N  transition duration
 220, 	// NX F1 locus
 25, 	// NX percent
 40, 	// NX transition duration
 1700, 	// NX F2 locus
 42, 	// NX percent
 70, 	// NX transition duration
 1820, 	// NX F3 locus
 25, 	// NX percent
 70, 	// NX transition duration
 350, 	// DZ F1 locus
 10, 	// DZ percent
 50, 	// DZ transition duration
 1700, 	// DZ F2 locus
 12, 	// DZ percent
 55, 	// DZ transition duration
 2720, 	// DZ F3 locus
 11, 	// DZ percent
 55, 	// DZ transition duration
 450, 	// EN F1 locus
 20, 	// EN percent
 30, 	// EN transition duration
 1550, 	// EN F2 locus
 25, 	// EN percent
 95, 	// EN transition duration
 2320, 	// EN F3 locus
 30, 	// EN percent
 95, 	// EN transition duration
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
 2300, 	// V  F3 locus
 65, 	// V  percent
 40, 	// V  transition duration
 350, 	// TH F1 locus
 10, 	// TH percent
 50, 	// TH transition duration
 1300, 	// TH F2 locus
 12, 	// TH percent
 55, 	// TH transition duration
 2720, 	// TH F3 locus
 11, 	// TH percent
 55, 	// TH transition duration
 350, 	// DH F1 locus
 10, 	// DH percent
 50, 	// DH transition duration
 1120, 	// DH F2 locus
 10, 	// DH percent
 55, 	// DH transition duration
 2720, 	// DH F3 locus
 11, 	// DH percent
 55, 	// DH transition duration
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
 1320, 	// Z  F2 locus
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
 340, 	// ZH F1 locus
 32, 	// ZH percent
 55, 	// ZH transition duration
 1630, 	// ZH F2 locus
 27, 	// ZH percent
 90, 	// ZH transition duration
 2100, 	// ZH F3 locus
 20, 	// ZH percent
 110, 	// ZH transition duration
 350, 	// P  F1 locus
 45, 	// P  percent
 25, 	// P  transition duration
 920, 	// P  F2 locus
 46, 	// P  percent
 30, 	// P  transition duration
 2250, 	// P  F3 locus
 40, 	// P  percent
 50, 	// P  transition duration
 350, 	// B  F1 locus
 45, 	// B  percent
 25, 	// B  transition duration
 820, 	// B  F2 locus
 30, 	// B  percent
 50, 	// B  transition duration
 1550, 	// B  F3 locus
 40, 	// B  percent
 50, 	// B  transition duration
 320, 	// T  F1 locus
 43, 	// T  percent
 40, 	// T  transition duration
 1700, 	// T  F2 locus
 40, 	// T  percent
 95, 	// T  transition duration
 2300, 	// T  F3 locus
 10, 	// T  percent
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
 210, 	// K  F1 locus
 33, 	// K  percent
 40, 	// K  transition duration
 1400, 	// K  F2 locus
 60, 	// K  percent
 75, 	// K  transition duration
 2050, 	// K  F3 locus
 15, 	// K  percent
 80, 	// K  transition duration
 290, 	// G  F1 locus
 45, 	// G  percent
 40, 	// G  transition duration
 1603, 	// G  F2 locus
 42, 	// G  percent
 65, 	// G  transition duration
 1923, 	// G  F3 locus
 15, 	// G  percent
 80, 	// G  transition duration
 320, 	// TX F1 locus
 43, 	// TX percent
 40, 	// TX transition duration
 1700, 	// TX F2 locus
 40, 	// TX percent
 95, 	// TX transition duration
 2300, 	// TX F3 locus
 0, 	// TX percent
 95, 	// TX transition duration
 320, 	// CH F1 locus
 54, 	// CH percent
 55, 	// CH transition duration
 1680, 	// CH F2 locus
 10, 	// CH percent
 90, 	// CH transition duration
 2350, 	// CH F3 locus
 10, 	// CH percent
 100, 	// CH transition duration
 245, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 1980, 	// JH F2 locus
 60, 	// JH percent
 90, 	// JH transition duration
 2650, 	// JH F3 locus
 60, 	// JH percent
 100, 	// JH transition duration
 250, 	// DF F1 locus
 43, 	// DF percent
 48, 	// DF transition duration
 1700, 	// DF F2 locus
 40, 	// DF percent
 95, 	// DF transition duration
 2600, 	// DF F3 locus
 30, 	// DF percent
 85, 	// DF transition duration
// Low
 -1, 	// UW F1 locus
 -1, 	// UW percent
 -1, 	// UW transition duration
 -1, 	// UW F2 locus
 -1, 	// UW percent
 -1, 	// UW transition duration
 -1, 	// UW F3 locus
 -1, 	// UW percent
 -1, 	// UW transition duration
 0, 	// R  F1 locus
 0, 	// R  percent
 0, 	// R  transition duration
 0, 	// R  F2 locus
 0, 	// R  percent
 0, 	// R  transition duration
 0, 	// R  F3 locus
 0, 	// R  percent
 0, 	// R  transition duration
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
 0, 	// NX F1 locus
 0, 	// NX percent
 0, 	// NX transition duration
 0, 	// NX F2 locus
 0, 	// NX percent
 0, 	// NX transition duration
 0, 	// NX F3 locus
 0, 	// NX percent
 0, 	// NX transition duration
 0, 	// DZ F1 locus
 0, 	// DZ percent
 0, 	// DZ transition duration
 0, 	// DZ F2 locus
 0, 	// DZ percent
 0, 	// DZ transition duration
 0, 	// DZ F3 locus
 0, 	// DZ percent
 0, 	// DZ transition duration
 0, 	// EN F1 locus
 0, 	// EN percent
 0, 	// EN transition duration
 0, 	// EN F2 locus
 0, 	// EN percent
 0, 	// EN transition duration
 0, 	// EN F3 locus
 0, 	// EN percent
 0, 	// EN transition duration
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
 0, 	// DH F1 locus
 0, 	// DH percent
 0, 	// DH transition duration
 0, 	// DH F2 locus
 0, 	// DH percent
 0, 	// DH transition duration
 0, 	// DH F3 locus
 0, 	// DH percent
 0, 	// DH transition duration
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
 0, 	// ZH F1 locus
 0, 	// ZH percent
 0, 	// ZH transition duration
 0, 	// ZH F2 locus
 0, 	// ZH percent
 0, 	// ZH transition duration
 0, 	// ZH F3 locus
 0, 	// ZH percent
 0, 	// ZH transition duration
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
 0, 	// TX F1 locus
 0, 	// TX percent
 0, 	// TX transition duration
 0, 	// TX F2 locus
 0, 	// TX percent
 0, 	// TX transition duration
 0, 	// TX F3 locus
 0, 	// TX percent
 0, 	// TX transition duration
 0, 	// CH F1 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F2 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F3 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// JH F1 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F2 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F3 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0};

// Female Locus
const short uk_femloc_def[] = {
 0, 
// Front
 -1, 	// R  F1 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 -1, 	// R  F2 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 -1, 	// R  F3 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 470, 	// M  F1 locus
 30, 	// M  percent
 30, 	// M  transition duration
 1380, 	// M  F2 locus
 10, 	// M  percent
 10, 	// M  transition duration
 2400, 	// M  F3 locus
 30, 	// M  percent
 10, 	// M  transition duration
 450, 	// N  F1 locus
 24, 	// N  percent
 35, 	// N  transition duration
 2300, 	// N  F2 locus
 75, 	// N  percent
 35, 	// N  transition duration
 3200, 	// N  F3 locus
 35, 	// N  percent
 45, 	// N  transition duration
 280, 	// NX F1 locus
 20, 	// NX percent
 40, 	// NX transition duration
 2860, 	// NX F2 locus
 40, 	// NX percent
 60, 	// NX transition duration
 3200, 	// NX F3 locus
 65, 	// NX percent
 60, 	// NX transition duration
 340, 	// DZ F1 locus
 30, 	// DZ percent
 45, 	// DZ transition duration
 1300, 	// DZ F2 locus
 35, 	// DZ percent
 60, 	// DZ transition duration
 3180, 	// DZ F3 locus
 35, 	// DZ percent
 60, 	// DZ transition duration
 450, 	// EN F1 locus
 24, 	// EN percent
 35, 	// EN transition duration
 2300, 	// EN F2 locus
 75, 	// EN percent
 35, 	// EN transition duration
 3200, 	// EN F3 locus
 35, 	// EN percent
 45, 	// EN transition duration
 350, 	// F  F1 locus
 65, 	// F  percent
 30, 	// F  transition duration
 1, 	// F  F2 locus
 87, 	// F  percent
 40, 	// F  transition duration
 2600, 	// F  F3 locus
 35, 	// F  percent
 30, 	// F  transition duration
 330, 	// V  F1 locus
 65, 	// V  percent
 30, 	// V  transition duration
 1, 	// V  F2 locus
 85, 	// V  percent
 40, 	// V  transition duration
 2600, 	// V  F3 locus
 35, 	// V  percent
 40, 	// V  transition duration
 360, 	// TH F1 locus
 30, 	// TH percent
 45, 	// TH transition duration
 1300, 	// TH F2 locus
 40, 	// TH percent
 70, 	// TH transition duration
 3180, 	// TH F3 locus
 35, 	// TH percent
 70, 	// TH transition duration
 340, 	// DH F1 locus
 30, 	// DH percent
 45, 	// DH transition duration
 1300, 	// DH F2 locus
 35, 	// DH percent
 60, 	// DH transition duration
 3180, 	// DH F3 locus
 35, 	// DH percent
 60, 	// DH transition duration
 330, 	// S  F1 locus
 40, 	// S  percent
 40, 	// S  transition duration
 2000, 	// S  F2 locus
 30, 	// S  percent
 50, 	// S  transition duration
 2980, 	// S  F3 locus
 0, 	// S  percent
 70, 	// S  transition duration
 320, 	// Z  F1 locus
 40, 	// Z  percent
 40, 	// Z  transition duration
 2000, 	// Z  F2 locus
 30, 	// Z  percent
 50, 	// Z  transition duration
 2980, 	// Z  F3 locus
 0, 	// Z  percent
 70, 	// Z  transition duration
 360, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 2000, 	// SH F2 locus
 30, 	// SH percent
 70, 	// SH transition duration
 2940, 	// SH F3 locus
 51, 	// SH percent
 70, 	// SH transition duration
 320, 	// ZH F1 locus
 26, 	// ZH percent
 55, 	// ZH transition duration
 2000, 	// ZH F2 locus
 30, 	// ZH percent
 70, 	// ZH transition duration
 2940, 	// ZH F3 locus
 51, 	// ZH percent
 70, 	// ZH transition duration
 440, 	// P  F1 locus
 55, 	// P  percent
 20, 	// P  transition duration
 1650, 	// P  F2 locus
 20, 	// P  percent
 90, 	// P  transition duration
 2690, 	// P  F3 locus
 55, 	// P  percent
 35, 	// P  transition duration
 360, 	// B  F1 locus
 40, 	// B  percent
 20, 	// B  transition duration
 1350, 	// B  F2 locus
 60, 	// B  percent
 25, 	// B  transition duration
 2690, 	// B  F3 locus
 55, 	// B  percent
 35, 	// B  transition duration
 470, 	// T  F1 locus
 33, 	// T  percent
 35, 	// T  transition duration
 2150, 	// T  F2 locus
 60, 	// T  percent
 35, 	// T  transition duration
 3150, 	// T  F3 locus
 30, 	// T  percent
 45, 	// T  transition duration
 370, 	// D  F1 locus
 33, 	// D  percent
 35, 	// D  transition duration
 2150, 	// D  F2 locus
 60, 	// D  percent
 35, 	// D  transition duration
 3150, 	// D  F3 locus
 30, 	// D  percent
 45, 	// D  transition duration
 440, 	// K  F1 locus
 33, 	// K  percent
 40, 	// K  transition duration
 2450, 	// K  F2 locus
 60, 	// K  percent
 50, 	// K  transition duration
 3350, 	// K  F3 locus
 80, 	// K  percent
 50, 	// K  transition duration
 320, 	// G  F1 locus
 33, 	// G  percent
 45, 	// G  transition duration
 2750, 	// G  F2 locus
 60, 	// G  percent
 50, 	// G  transition duration
 3350, 	// G  F3 locus
 90, 	// G  percent
 50, 	// G  transition duration
 470, 	// TX F1 locus
 33, 	// TX percent
 35, 	// TX transition duration
 2150, 	// TX F2 locus
 1852, 	// TX percent
 35, 	// TX transition duration
 3150, 	// TX F3 locus
 30, 	// TX percent
 45, 	// TX transition duration
 400, 	// CH F1 locus
 34, 	// CH percent
 55, 	// CH transition duration
 2000, 	// CH F2 locus
 25, 	// CH percent
 70, 	// CH transition duration
 3300, 	// CH F3 locus
 19, 	// CH percent
 70, 	// CH transition duration
 370, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 2000, 	// JH F2 locus
 25, 	// JH percent
 70, 	// JH transition duration
 3300, 	// JH F3 locus
 19, 	// JH percent
 70, 	// JH transition duration
 -1, 	// DF F1 locus
 -1, 	// DF percent
 -1, 	// DF transition duration
 -1, 	// DF F2 locus
 -1, 	// DF percent
 -1, 	// DF transition duration
 -1, 	// DF F3 locus
 -1, 	// DF percent
 -1, 	// DF transition duration
// Back
 -1, 	// _  F1 locus
 -1, 	// _  percent
 -1, 	// _  transition duration
 -1, 	// _  F2 locus
 -1, 	// _  percent
 -1, 	// _  transition duration
 -8, 	// _  F3 locus
 -1, 	// _  percent
 -1, 	// _  transition duration
 -1, 	// UR F1 locus
 -1, 	// UR percent
 -1, 	// UR transition duration
 -8, 	// UR F2 locus
 -1, 	// UR percent
 -1, 	// UR transition duration
 -1, 	// UR F3 locus
 -1, 	// UR percent
 -1, 	// UR transition duration
 -1, 	// R  F1 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 -1, 	// R  F2 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 -1, 	// R  F3 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 450, 	// M  F1 locus
 20, 	// M  percent
 30, 	// M  transition duration
 1, 	// M  F2 locus
 88, 	// M  percent
 40, 	// M  transition duration
 1750, 	// M  F3 locus
 80, 	// M  percent
 30, 	// M  transition duration
 450, 	// N  F1 locus
 22, 	// N  percent
 30, 	// N  transition duration
 2200, 	// N  F2 locus
 65, 	// N  percent
 75, 	// N  transition duration
 3140, 	// N  F3 locus
 30, 	// N  percent
 60, 	// N  transition duration
 280, 	// NX F1 locus
 20, 	// NX percent
 40, 	// NX transition duration
 1670, 	// NX F2 locus
 20, 	// NX percent
 70, 	// NX transition duration
 2620, 	// NX F3 locus
 20, 	// NX percent
 70, 	// NX transition duration
 400, 	// DZ F1 locus
 30, 	// DZ percent
 50, 	// DZ transition duration
 1800, 	// DZ F2 locus
 42, 	// DZ percent
 70, 	// DZ transition duration
 3060, 	// DZ F3 locus
 11, 	// DZ percent
 70, 	// DZ transition duration
 450, 	// EN F1 locus
 22, 	// EN percent
 30, 	// EN transition duration
 2200, 	// EN F2 locus
 65, 	// EN percent
 75, 	// EN transition duration
 3140, 	// EN F3 locus
 30, 	// EN percent
 60, 	// EN transition duration
 350, 	// F  F1 locus
 75, 	// F  percent
 30, 	// F  transition duration
 1, 	// F  F2 locus
 85, 	// F  percent
 30, 	// F  transition duration
 2000, 	// F  F3 locus
 65, 	// F  percent
 40, 	// F  transition duration
 330, 	// V  F1 locus
 75, 	// V  percent
 30, 	// V  transition duration
 1, 	// V  F2 locus
 84, 	// V  percent
 30, 	// V  transition duration
 2000, 	// V  F3 locus
 65, 	// V  percent
 40, 	// V  transition duration
 440, 	// TH F1 locus
 30, 	// TH percent
 50, 	// TH transition duration
 1800, 	// TH F2 locus
 42, 	// TH percent
 70, 	// TH transition duration
 3060, 	// TH F3 locus
 11, 	// TH percent
 70, 	// TH transition duration
 400, 	// DH F1 locus
 30, 	// DH percent
 50, 	// DH transition duration
 1800, 	// DH F2 locus
 42, 	// DH percent
 70, 	// DH transition duration
 3060, 	// DH F3 locus
 11, 	// DH percent
 70, 	// DH transition duration
 390, 	// S  F1 locus
 40, 	// S  percent
 40, 	// S  transition duration
 1800, 	// S  F2 locus
 40, 	// S  percent
 50, 	// S  transition duration
 3070, 	// S  F3 locus
 0, 	// S  percent
 70, 	// S  transition duration
 320, 	// Z  F1 locus
 35, 	// Z  percent
 40, 	// Z  transition duration
 1800, 	// Z  F2 locus
 40, 	// Z  percent
 50, 	// Z  transition duration
 3070, 	// Z  F3 locus
 0, 	// Z  percent
 70, 	// Z  transition duration
 360, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1850, 	// SH F2 locus
 7, 	// SH percent
 70, 	// SH transition duration
 2700, 	// SH F3 locus
 0, 	// SH percent
 85, 	// SH transition duration
 320, 	// ZH F1 locus
 26, 	// ZH percent
 55, 	// ZH transition duration
 1850, 	// ZH F2 locus
 7, 	// ZH percent
 70, 	// ZH transition duration
 2700, 	// ZH F3 locus
 0, 	// ZH percent
 85, 	// ZH transition duration
 440, 	// P  F1 locus
 45, 	// P  percent
 25, 	// P  transition duration
 1130, 	// P  F2 locus
 50, 	// P  percent
 30, 	// P  transition duration
 2530, 	// P  F3 locus
 48, 	// P  percent
 40, 	// P  transition duration
 360, 	// B  F1 locus
 50, 	// B  percent
 20, 	// B  transition duration
 1130, 	// B  F2 locus
 50, 	// B  percent
 30, 	// B  transition duration
 2530, 	// B  F3 locus
 48, 	// B  percent
 40, 	// B  transition duration
 470, 	// T  F1 locus
 33, 	// T  percent
 45, 	// T  transition duration
 2050, 	// T  F2 locus
 0, 	// T  percent
 80, 	// T  transition duration
 2990, 	// T  F3 locus
 0, 	// T  percent
 50, 	// T  transition duration
 370, 	// D  F1 locus
 33, 	// D  percent
 45, 	// D  transition duration
 2050, 	// D  F2 locus
 0, 	// D  percent
 80, 	// D  transition duration
 2990, 	// D  F3 locus
 0, 	// D  percent
 50, 	// D  transition duration
 440, 	// K  F1 locus
 33, 	// K  percent
 45, 	// K  transition duration
 1900, 	// K  F2 locus
 20, 	// K  percent
 90, 	// K  transition duration
 2500, 	// K  F3 locus
 0, 	// K  percent
 90, 	// K  transition duration
 340, 	// G  F1 locus
 43, 	// G  percent
 50, 	// G  transition duration
 1900, 	// G  F2 locus
 0, 	// G  percent
 60, 	// G  transition duration
 2500, 	// G  F3 locus
 0, 	// G  percent
 90, 	// G  transition duration
 470, 	// TX F1 locus
 33, 	// TX percent
 45, 	// TX transition duration
 2050, 	// TX F2 locus
 0, 	// TX percent
 80, 	// TX transition duration
 2990, 	// TX F3 locus
 0, 	// TX percent
 50, 	// TX transition duration
 420, 	// CH F1 locus
 40, 	// CH percent
 55, 	// CH transition duration
 1900, 	// CH F2 locus
 10, 	// CH percent
 70, 	// CH transition duration
 3200, 	// CH F3 locus
 10, 	// CH percent
 70, 	// CH transition duration
 380, 	// JH F1 locus
 40, 	// JH percent
 55, 	// JH transition duration
 1900, 	// JH F2 locus
 10, 	// JH percent
 70, 	// JH transition duration
 3200, 	// JH F3 locus
 10, 	// JH percent
 70, 	// JH transition duration
 -1, 	// DF F1 locus
 -1, 	// DF percent
 -1, 	// DF transition duration
 -1, 	// DF F2 locus
 -1, 	// DF percent
 -1, 	// DF transition duration
 -1, 	// DF F3 locus
 -1, 	// DF percent
 -1, 	// DF transition duration
// Round
 -1793, 	// AO F1 locus
 -1, 	// AO percent
 -1, 	// AO transition duration
 -1, 	// AO F2 locus
 -1, 	// AO percent
 -1, 	// AO transition duration
 -1, 	// AO F3 locus
 -1, 	// AO percent
 -1, 	// AO transition duration
 -1, 	// R  F1 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 -1, 	// R  F2 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 -1, 	// R  F3 locus
 -1, 	// R  percent
 -1, 	// R  transition duration
 450, 	// M  F1 locus
 20, 	// M  percent
 30, 	// M  transition duration
 1, 	// M  F2 locus
 88, 	// M  percent
 40, 	// M  transition duration
 1750, 	// M  F3 locus
 80, 	// M  percent
 30, 	// M  transition duration
 450, 	// N  F1 locus
 24, 	// N  percent
 30, 	// N  transition duration
 2160, 	// N  F2 locus
 65, 	// N  percent
 80, 	// N  transition duration
 2590, 	// N  F3 locus
 30, 	// N  percent
 80, 	// N  transition duration
 280, 	// NX F1 locus
 40, 	// NX percent
 40, 	// NX transition duration
 1650, 	// NX F2 locus
 42, 	// NX percent
 70, 	// NX transition duration
 2500, 	// NX F3 locus
 25, 	// NX percent
 70, 	// NX transition duration
 400, 	// DZ F1 locus
 30, 	// DZ percent
 50, 	// DZ transition duration
 1800, 	// DZ F2 locus
 42, 	// DZ percent
 70, 	// DZ transition duration
 3060, 	// DZ F3 locus
 11, 	// DZ percent
 70, 	// DZ transition duration
 450, 	// EN F1 locus
 24, 	// EN percent
 30, 	// EN transition duration
 2160, 	// EN F2 locus
 65, 	// EN percent
 80, 	// EN transition duration
 2590, 	// EN F3 locus
 30, 	// EN percent
 80, 	// EN transition duration
 350, 	// F  F1 locus
 75, 	// F  percent
 30, 	// F  transition duration
 1, 	// F  F2 locus
 85, 	// F  percent
 30, 	// F  transition duration
 2000, 	// F  F3 locus
 65, 	// F  percent
 40, 	// F  transition duration
 330, 	// V  F1 locus
 75, 	// V  percent
 30, 	// V  transition duration
 1, 	// V  F2 locus
 84, 	// V  percent
 30, 	// V  transition duration
 2000, 	// V  F3 locus
 65, 	// V  percent
 40, 	// V  transition duration
 440, 	// TH F1 locus
 30, 	// TH percent
 50, 	// TH transition duration
 1800, 	// TH F2 locus
 42, 	// TH percent
 70, 	// TH transition duration
 3060, 	// TH F3 locus
 11, 	// TH percent
 70, 	// TH transition duration
 400, 	// DH F1 locus
 30, 	// DH percent
 50, 	// DH transition duration
 1800, 	// DH F2 locus
 42, 	// DH percent
 70, 	// DH transition duration
 3060, 	// DH F3 locus
 11, 	// DH percent
 70, 	// DH transition duration
 390, 	// S  F1 locus
 40, 	// S  percent
 40, 	// S  transition duration
 1900, 	// S  F2 locus
 15, 	// S  percent
 60, 	// S  transition duration
 2880, 	// S  F3 locus
 0, 	// S  percent
 65, 	// S  transition duration
 320, 	// Z  F1 locus
 40, 	// Z  percent
 40, 	// Z  transition duration
 1900, 	// Z  F2 locus
 15, 	// Z  percent
 60, 	// Z  transition duration
 2880, 	// Z  F3 locus
 0, 	// Z  percent
 65, 	// Z  transition duration
 400, 	// SH F1 locus
 32, 	// SH percent
 55, 	// SH transition duration
 1840, 	// SH F2 locus
 7, 	// SH percent
 90, 	// SH transition duration
 2700, 	// SH F3 locus
 20, 	// SH percent
 110, 	// SH transition duration
 320, 	// ZH F1 locus
 30, 	// ZH percent
 55, 	// ZH transition duration
 1840, 	// ZH F2 locus
 7, 	// ZH percent
 90, 	// ZH transition duration
 2700, 	// ZH F3 locus
 20, 	// ZH percent
 110, 	// ZH transition duration
 440, 	// P  F1 locus
 45, 	// P  percent
 25, 	// P  transition duration
 1130, 	// P  F2 locus
 50, 	// P  percent
 30, 	// P  transition duration
 2530, 	// P  F3 locus
 48, 	// P  percent
 40, 	// P  transition duration
 360, 	// B  F1 locus
 50, 	// B  percent
 20, 	// B  transition duration
 1130, 	// B  F2 locus
 50, 	// B  percent
 30, 	// B  transition duration
 2530, 	// B  F3 locus
 48, 	// B  percent
 40, 	// B  transition duration
 470, 	// T  F1 locus
 33, 	// T  percent
 40, 	// T  transition duration
 1900, 	// T  F2 locus
 0, 	// T  percent
 70, 	// T  transition duration
 2900, 	// T  F3 locus
 20, 	// T  percent
 70, 	// T  transition duration
 370, 	// D  F1 locus
 33, 	// D  percent
 40, 	// D  transition duration
 1900, 	// D  F2 locus
 0, 	// D  percent
 80, 	// D  transition duration
 2900, 	// D  F3 locus
 20, 	// D  percent
 80, 	// D  transition duration
 440, 	// K  F1 locus
 33, 	// K  percent
 35, 	// K  transition duration
 1800, 	// K  F2 locus
 62, 	// K  percent
 65, 	// K  transition duration
 2520, 	// K  F3 locus
 15, 	// K  percent
 1872, 	// K  transition duration
 370, 	// G  F1 locus
 45, 	// G  percent
 40, 	// G  transition duration
 1800, 	// G  F2 locus
 62, 	// G  percent
 65, 	// G  transition duration
 2520, 	// G  F3 locus
 15, 	// G  percent
 80, 	// G  transition duration
 470, 	// TX F1 locus
 33, 	// TX percent
 40, 	// TX transition duration
 1900, 	// TX F2 locus
 0, 	// TX percent
 70, 	// TX transition duration
 2900, 	// TX F3 locus
 20, 	// TX percent
 70, 	// TX transition duration
 420, 	// CH F1 locus
 34, 	// CH percent
 55, 	// CH transition duration
 2050, 	// CH F2 locus
 10, 	// CH percent
 90, 	// CH transition duration
 3100, 	// CH F3 locus
 10, 	// CH percent
 100, 	// CH transition duration
 380, 	// JH F1 locus
 32, 	// JH percent
 55, 	// JH transition duration
 2050, 	// JH F2 locus
 10, 	// JH percent
 90, 	// JH transition duration
 3100, 	// JH F3 locus
 10, 	// JH percent
 100, 	// JH transition duration
 -1, 	// DF F1 locus
 -1, 	// DF percent
 -1, 	// DF transition duration
 -1, 	// DF F2 locus
 -1, 	// DF percent
 -1, 	// DF transition duration
 -1, 	// DF F3 locus
 -1, 	// DF percent
 -1, 	// DF transition duration
// Low
 -1, 	// UW F1 locus
 -1, 	// UW percent
 -1, 	// UW transition duration
 -1793, 	// UW F2 locus
 -1, 	// UW percent
 -1, 	// UW transition duration
 -1, 	// UW F3 locus
 -1, 	// UW percent
 -1, 	// UW transition duration
 0, 	// R  F1 locus
 0, 	// R  percent
 0, 	// R  transition duration
 0, 	// R  F2 locus
 0, 	// R  percent
 0, 	// R  transition duration
 0, 	// R  F3 locus
 0, 	// R  percent
 0, 	// R  transition duration
 0, 	// M  F1 locus
 0, 	// M  percent
 0, 	// M  transition duration
 0, 	// M  F2 locus
 0, 	// M  percent
 0, 	// M  transition duration
 1792, 	// M  F3 locus
 0, 	// M  percent
 0, 	// M  transition duration
 0, 	// N  F1 locus
 0, 	// N  percent
 7, 	// N  transition duration
 0, 	// N  F2 locus
 0, 	// N  percent
 0, 	// N  transition duration
 0, 	// N  F3 locus
 0, 	// N  percent
 7, 	// N  transition duration
 0, 	// NX F1 locus
 0, 	// NX percent
 0, 	// NX transition duration
 0, 	// NX F2 locus
 0, 	// NX percent
 0, 	// NX transition duration
 0, 	// NX F3 locus
 0, 	// NX percent
 0, 	// NX transition duration
 0, 	// DZ F1 locus
 0, 	// DZ percent
 0, 	// DZ transition duration
 0, 	// DZ F2 locus
 0, 	// DZ percent
 0, 	// DZ transition duration
 0, 	// DZ F3 locus
 0, 	// DZ percent
 0, 	// DZ transition duration
 0, 	// EN F1 locus
 0, 	// EN percent
 0, 	// EN transition duration
 0, 	// EN F2 locus
 0, 	// EN percent
 0, 	// EN transition duration
 0, 	// EN F3 locus
 0, 	// EN percent
 0, 	// EN transition duration
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
 1792, 	// V  transition duration
 0, 	// TH F1 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F2 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// TH F3 locus
 0, 	// TH percent
 0, 	// TH transition duration
 0, 	// DH F1 locus
 0, 	// DH percent
 0, 	// DH transition duration
 0, 	// DH F2 locus
 0, 	// DH percent
 0, 	// DH transition duration
 0, 	// DH F3 locus
 0, 	// DH percent
 0, 	// DH transition duration
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
 0, 	// ZH F1 locus
 0, 	// ZH percent
 0, 	// ZH transition duration
 0, 	// ZH F2 locus
 0, 	// ZH percent
 0, 	// ZH transition duration
 0, 	// ZH F3 locus
 0, 	// ZH percent
 0, 	// ZH transition duration
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
 7, 	// B  F3 locus
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
 0, 	// TX F1 locus
 0, 	// TX percent
 0, 	// TX transition duration
 0, 	// TX F2 locus
 0, 	// TX percent
 0, 	// TX transition duration
 0, 	// TX F3 locus
 0, 	// TX percent
 0, 	// TX transition duration
 0, 	// CH F1 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F2 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// CH F3 locus
 0, 	// CH percent
 0, 	// CH transition duration
 0, 	// JH F1 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F2 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0, 	// JH F3 locus
 0, 	// JH percent
 0, 	// JH transition duration
 0};

const struct rom_data_s uk_rom_data_def = {
uk_inhdr_def,
uk_mindur_def,
uk_burdr_def,
uk_begtyp_def,
uk_endtyp_def,
uk_place_def,
uk_featb_def,
uk_maltar_def,
uk_femtar_def,
uk_maldip_def,
uk_femdip_def,
uk_ptram_def,
uk_plocu_def,
uk_maleloc_def,
uk_femloc_def
};


