/* PH Rom file
 * 
 * Copyright Information:
 * 
 *                           Copyright (c)
 *    Copyright � 2002 Fonix Corporation. All rights reserved.
 *    Copyright � 2000-2001 Force Computers, a Solectron Company. All rights reserved.
 *    � Digital Equipment Corporation 1996, 1997, 1998. All rights reserved.
 * 
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 * 
 * 
 *    This software is proprietary to and embodies the confidential
 *    technology of Fonix Corporation and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Fonix or an
 *    authorized sublicensor.
 * 
 * Based on Dennis Klatt's PHRom File Format  Copyright (c) 1988 by Dennis Klatt
 *
 * Compile Type: Compiled from (0/0)
 * Program: PHEdit(2)
 * Author: Kevin Bruckert
 *
 */
#ifdef PHEDIT2
short inhdr[100] = {
#else
const short us_inhdr_ken[] = {
#endif
 305, 
 170, 
 160, 
 200, 
 160, 
 230, 
 240, 
 190, 
 260, 
 160, 
 240, 
 220, 
 220, 
 170, 
 195, 
 180, 
 230, 
 120, 
 120, 
 270, 
 270, 
 270, 
 240, 
 240, 
 80, 
 75, 
 65, 
 75, 
 70, 
 120, 
 100, 
 70, 
 65, 
 80, 
 160, 
 60, 
 150, 
 100, 
 100, 
 100, 
 85, 
 126, 
 120, 
 115, 
 70, 
 85, 
 80, 
 85, 
 80, 
 90, 
 90, 
 40, 
 70, 
 30, 
 160, 
 100, 
 40, 
 100, 
 120, 
 0, 
 0, 
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

#ifdef PHEDIT2
short mindur[100] = {
#else
const short us_mindur_ken[] = {
#endif
 7, 
 80, 
 80, 
 110, 
 80, 
 80, 
 90, 
 100, 
 110, 
 70, 
 100, 
 90, 
 110, 
 80, 
 70, 
 90, 
 100, 
 50, 
 50, 
 110, 
 110, 
 110, 
 110, 
 110, 
 40, 
 30, 
 30, 
 40, 
 60, 
 70, 
 70, 
 60, 
 35, 
 50, 
 110, 
 35, 
 100, 
 60, 
 70, 
 50, 
 60, 
 65, 
 70, 
 60, 
 50, 
 50, 
 60, 
 50, 
 40, 
 50, 
 65, 
 20, 
 50, 
 5, 
 100, 
 75, 
 20, 
 60, 
 60, 
 0, 
 0, 
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

#ifdef PHEDIT2
short burdr[100] = {
#else
const short us_burdr_ken[] = {
#endif
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 13, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 7, 
 7, 
 14, 
 14, 
 12, 
 20, 
 0, 
 0, 
 0, 
 71, 
 45, 
 0, 
 0, 
 0, 
 0, 
 0, 
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

#ifdef PHEDIT2
short begtyp[100] = {
#else
const short us_begtyp_ken[] = {
#endif
 4, 
 1, 
 1, 
 1, 
 1, 
 1, 
 2, 
 2, 
 2, 
 2, 
 3, 
 3, 
 3, 
 3, 
 3, 
 3, 
 1, 
 2, 
 1, 
 1, 
 1, 
 2, 
 3, 
 3, 
 5, 
 1, 
 5, 
 5, 
 4, 
 3, 
 5, 
 4, 
 4, 
 4, 
 5, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1 };

#ifdef PHEDIT2
short endtyp[100] = {
#else
const short us_endtyp_ken[] = {
#endif
 4, 
 1, 
 1, 
 1, 
 1, 
 1, 
 2, 
 1, 
 3, 
 2, 
 3, 
 5, 
 1, 
 3, 
 5, 
 3, 
 3, 
 2, 
 1, 
 3, 
 3, 
 3, 
 3, 
 3, 
 5, 
 1, 
 5, 
 5, 
 4, 
 3, 
 5, 
 4, 
 4, 
 4, 
 5, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 4, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1, 
 1 };

#ifdef PHEDIT2
short place[500] = {
#else
const short us_place_ken[] = {
#endif
 0, 
 128, 
 0, 
 128, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 64, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 192, 
 0, 
 0, 
 0, 
 0, 
 0, 
 1, 
 8, 
 16, 
 0, 
 2, 
 8, 
 1, 
 1, 
 2, 
 2, 
 8, 
 8, 
 4, 
 4, 
 1, 
 1, 
 8, 
 8, 
 16, 
 16, 
 0, 
 40, 
 32, 
 4, 
 4, 
 0, 
 4, 
 32, 
 0, 
 0, 
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

#ifdef PHEDIT2
int featb[200] = {
#else
const int us_featb_ken[] = {
#endif
 16, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 1055, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 31, 
 1818, 
 1818, 
 1818, 
 1818, 
 272, 
 794, 
 794, 
 9626, 
 9626, 
 9626, 
 27, 
 10594, 
 9371, 
 288, 
 290, 
 288, 
 290, 
 288, 
 290, 
 288, 
 290, 
 10592, 
 10594, 
 10592, 
 10594, 
 10592, 
 10594, 
 290, 
 10594, 
 8224, 
 10528, 
 10530, 
 288, 
 288, 
 288, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
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

#ifdef PHEDIT2
short maltar[700] = {
#else
const short us_maltar_ken[] = {
#endif
 -1, 
 -2, 
 -6, 
 -10, 
 526, 
 775, 
 616, 
 -16, 
 -22, 
 576, 
 -28, 
 -34, 
 -40, 
 415, 
 -48, 
 -54, 
 -60, 
 -66, 
 -72, 
 -78, 
 -84, 
 -90, 
 -96, 
 -102, 
 350, 
 280, 
 400, 
 400, 
 -1, 
 470, 
 480, 
 300, 
 300, 
 180, 
 350, 
 300, 
 280, 
 340, 
 325, 
 320, 
 290, 
 320, 
 280, 
 300, 
 280, 
 300, 
 285, 
 350, 
 300, 
 180, 
 180, 
 350, 
 280, 
 -1, 
 350, 
 280, 
 290, 
 -1, 
 350, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -108, 
 -112, 
 -116, 
 1800, 
 1400, 
 1108, 
 -122, 
 -126, 
 1166, 
 -132, 
 -138, 
 -144, 
 1037, 
 -152, 
 -158, 
 -164, 
 -170, 
 -176, 
 -182, 
 -188, 
 -194, 
 -200, 
 -206, 
 650, 
 2070, 
 1030, 
 800, 
 -1, 
 1270, 
 850, 
 1070, 
 1550, 
 2352, 
 800, 
 1400, 
 1804, 
 1100, 
 1100, 
 1300, 
 1300, 
 1420, 
 1420, 
 2003, 
 1900, 
 1070, 
 1070, 
 1700, 
 1700, 
 2200, 
 1800, 
 1913, 
 1600, 
 -1, 
 2150, 
 1730, 
 1650, 
 -1, 
 1486, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -212, 
 -216, 
 -220, 
 2660, 
 2650, 
 2770, 
 -226, 
 -234, 
 2500, 
 -240, 
 -246, 
 -252, 
 2600, 
 2300, 
 -260, 
 -266, 
 -272, 
 -278, 
 -284, 
 -290, 
 -296, 
 -302, 
 -308, 
 2500, 
 2570, 
 1380, 
 2950, 
 -1, 
 1540, 
 2990, 
 2400, 
 2732, 
 2600, 
 2850, 
 2600, 
 2768, 
 1725, 
 2144, 
 2520, 
 2560, 
 2750, 
 2600, 
 2712, 
 2550, 
 2150, 
 2177, 
 2250, 
 2600, 
 2750, 
 2100, 
 2305, 
 2600, 
 -1, 
 2700, 
 2700, 
 2305, 
 -1, 
 2200, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 60, 
 60, 
 70, 
 60, 
 -314, 
 120, 
 -320, 
 -326, 
 90, 
 110, 
 90, 
 200, 
 80, 
 75, 
 90, 
 70, 
 90, 
 60, 
 80, 
 80, 
 140, 
 100, 
 90, 
 60, 
 50, 
 70, 
 70, 
 300, 
 80, 
 140, 
 130, 
 90, 
 130, 
 90, 
 90, 
 90, 
 200, 
 100, 
 200, 
 100, 
 200, 
 100, 
 200, 
 100, 
 200, 
 90, 
 200, 
 90, 
 200, 
 90, 
 90, 
 110, 
 -1, 
 200, 
 70, 
 90, 
 -1, 
 90, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 100, 
 130, 
 100, 
 150, 
 -332, 
 140, 
 100, 
 75, 
 70, 
 90, 
 70, 
 -338, 
 83, 
 70, 
 110, 
 -344, 
 80, 
 100, 
 120, 
 110, 
 90, 
 80, 
 90, 
 70, 
 200, 
 80, 
 65, 
 200, 
 80, 
 90, 
 120, 
 120, 
 160, 
 90, 
 110, 
 120, 
 120, 
 120, 
 90, 
 120, 
 180, 
 140, 
 240, 
 160, 
 180, 
 80, 
 150, 
 100, 
 160, 
 120, 
 100, 
 100, 
 -1, 
 280, 
 170, 
 100, 
 -1, 
 120, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 160, 
 190, 
 200, 
 220, 
 290, 
 250, 
 230, 
 150, 
 180, 
 120, 
 180, 
 170, 
 160, 
 140, 
 250, 
 -350, 
 180, 
 200, 
 200, 
 200, 
 150, 
 140, 
 180, 
 90, 
 300, 
 90, 
 120, 
 220, 
 130, 
 100, 
 250, 
 160, 
 320, 
 200, 
 200, 
 160, 
 150, 
 120, 
 150, 
 170, 
 300, 
 300, 
 300, 
 300, 
 180, 
 130, 
 250, 
 240, 
 280, 
 180, 
 150, 
 170, 
 -1, 
 250, 
 250, 
 170, 
 -1, 
 150, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 0, 
 64, 
 65, 
 65, 
 63, 
 63, 
 64, 
 64, 
 64, 
 64, 
 64, 
 65, 
 64, 
 65, 
 65, 
 65, 
 65, 
 62, 
 63, 
 65, 
 65, 
 64, 
 65, 
 65, 
 60, 
 64, 
 64, 
 63, 
 0, 
 64, 
 63, 
 58, 
 60, 
 60, 
 63, 
 50, 
 60, 
 0, 
 53, 
 0, 
 53, 
 0, 
 53, 
 0, 
 53, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 50, 
 0, 
 54, 
 0, 
 0, 
 53, 
 0, 
 0, 
 0, 
 0, 
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

#ifdef PHEDIT2
short femtar[700] = {
#else
const short us_femtar_ken[] = {
#endif
 -1, 
 -2, 
 -6, 
 -10, 
 -16, 
 -20, 
 -26, 
 -32, 
 -40, 
 -46, 
 -52, 
 -58, 
 -64, 
 -72, 
 -78, 
 -84, 
 -90, 
 -96, 
 -102, 
 -108, 
 -114, 
 -120, 
 -126, 
 -132, 
 330, 
 280, 
 350, 
 488, 
 -1, 
 490, 
 587, 
 300, 
 450, 
 280, 
 580, 
 220, 
 450, 
 360, 
 280, 
 340, 
 410, 
 340, 
 390, 
 320, 
 280, 
 379, 
 250, 
 370, 
 220, 
 370, 
 250, 
 350, 
 250, 
 -1, 
 370, 
 220, 
 350, 
 410, 
 370, 
 -138, 
 -144, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -150, 
 -154, 
 -158, 
 1973, 
 -164, 
 -170, 
 -176, 
 -182, 
 -188, 
 -194, 
 -200, 
 -206, 
 -214, 
 -220, 
 -226, 
 -232, 
 1780, 
 -238, 
 -244, 
 -250, 
 -256, 
 -262, 
 -268, 
 814, 
 2600, 
 1060, 
 1100, 
 -1, 
 1600, 
 1096, 
 1340, 
 1800, 
 2056, 
 990, 
 1860, 
 1530, 
 1250, 
 1250, 
 1750, 
 1750, 
 1730, 
 1802, 
 1750, 
 1980, 
 1150, 
 1150, 
 1860, 
 1860, 
 2190, 
 2190, 
 -1, 
 1860, 
 -1, 
 2100, 
 2100, 
 -1, 
 1650, 
 1600, 
 -274, 
 -280, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -286, 
 -290, 
 -294, 
 3011, 
 -300, 
 -306, 
 -312, 
 -320, 
 -326, 
 -332, 
 -338, 
 -344, 
 -352, 
 -358, 
 -364, 
 -370, 
 3060, 
 -376, 
 -382, 
 -388, 
 -394, 
 -402, 
 -408, 
 2522, 
 3400, 
 1990, 
 3200, 
 -1, 
 1950, 
 2900, 
 2190, 
 2800, 
 3100, 
 3050, 
 3020, 
 2920, 
 2700, 
 2700, 
 2940, 
 2940, 
 2800, 
 2960, 
 3100, 
 2800, 
 2900, 
 2470, 
 3020, 
 3020, 
 2710, 
 2710, 
 -1, 
 3000, 
 -1, 
 3150, 
 3150, 
 -1, 
 2700, 
 2400, 
 -414, 
 -420, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 80, 
 50, 
 50, 
 90, 
 -426, 
 130, 
 -432, 
 -438, 
 110, 
 160, 
 110, 
 100, 
 90, 
 90, 
 90, 
 80, 
 140, 
 80, 
 80, 
 120, 
 130, 
 90, 
 80, 
 80, 
 170, 
 90, 
 90, 
 500, 
 90, 
 90, 
 120, 
 120, 
 120, 
 90, 
 120, 
 110, 
 200, 
 140, 
 200, 
 120, 
 200, 
 140, 
 200, 
 120, 
 200, 
 100, 
 200, 
 110, 
 200, 
 100, 
 100, 
 90, 
 100, 
 200, 
 120, 
 100, 
 90, 
 90, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 150, 
 110, 
 90, 
 160, 
 240, 
 220, 
 165, 
 -444, 
 150, 
 330, 
 110, 
 -448, 
 100, 
 100, 
 250, 
 -454, 
 140, 
 180, 
 220, 
 190, 
 200, 
 170, 
 130, 
 80, 
 180, 
 150, 
 110, 
 -1, 
 200, 
 110, 
 150, 
 160, 
 600, 
 120, 
 90, 
 200, 
 140, 
 120, 
 220, 
 150, 
 200, 
 170, 
 240, 
 160, 
 180, 
 110, 
 150, 
 140, 
 160, 
 100, 
 100, 
 100, 
 -1, 
 230, 
 170, 
 100, 
 120, 
 120, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 270, 
 150, 
 130, 
 270, 
 300, 
 160, 
 180, 
 -460, 
 210, 
 240, 
 180, 
 180, 
 170, 
 180, 
 120, 
 -464, 
 200, 
 240, 
 200, 
 210, 
 160, 
 130, 
 140, 
 110, 
 200, 
 130, 
 120, 
 -1, 
 150, 
 130, 
 250, 
 250, 
 550, 
 200, 
 120, 
 160, 
 150, 
 120, 
 300, 
 270, 
 200, 
 200, 
 300, 
 300, 
 180, 
 150, 
 250, 
 170, 
 280, 
 150, 
 130, 
 130, 
 -1, 
 350, 
 350, 
 130, 
 150, 
 150, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 0, 
 65, 
 65, 
 65, 
 65, 
 65, 
 64, 
 64, 
 64, 
 64, 
 64, 
 65, 
 65, 
 65, 
 65, 
 64, 
 65, 
 62, 
 63, 
 65, 
 65, 
 64, 
 64, 
 65, 
 64, 
 64, 
 64, 
 64, 
 0, 
 64, 
 64, 
 60, 
 60, 
 60, 
 63, 
 50, 
 60, 
 0, 
 53, 
 0, 
 53, 
 0, 
 53, 
 0, 
 53, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 34, 
 0, 
 50, 
 0, 
 0, 
 53, 
 0, 
 0, 
 60, 
 0, 
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

#ifdef PHEDIT2
short maldip[3500] = {
#else
const short us_maldip_ken[] = {
#endif
 0, 
 0, 
 300, 
 40, 
 300, 
 -1, 
 300, 
 60, 
 300, 
 -1, 
 300, 
 10, 
 300, 
 160, 
 300, 
 -1, 
 512, 
 110, 
 570, 
 190, 
 407, 
 -1, 
 710, 
 110, 
 550, 
 230, 
 550, 
 -1, 
 640, 
 120, 
 700, 
 220, 
 700, 
 -1, 
 389, 
 40, 
 389, 
 170, 
 389, 
 -1, 
 540, 
 10, 
 580, 
 90, 
 470, 
 220, 
 470, 
 -1, 
 284, 
 40, 
 284, 
 130, 
 284, 
 -1, 
 490, 
 30, 
 460, 
 170, 
 460, 
 -1, 
 270, 
 45, 
 360, 
 150, 
 360, 
 -1, 
 536, 
 30, 
 500, 
 90, 
 520, 
 -1, 
 360, 
 30, 
 360, 
 90, 
 360, 
 -1, 
 350, 
 100, 
 420, 
 170, 
 420, 
 -1, 
 490, 
 40, 
 490, 
 230, 
 490, 
 -1, 
 660, 
 100, 
 570, 
 180, 
 570, 
 -1, 
 502, 
 90, 
 490, 
 150, 
 490, 
 -1, 
 420, 
 80, 
 440, 
 170, 
 440, 
 -1, 
 2300, 
 40, 
 2300, 
 -1, 
 2300, 
 60, 
 2300, 
 -1, 
 2300, 
 10, 
 2300, 
 160, 
 2300, 
 -1, 
 1388, 
 10, 
 1995, 
 -1, 
 1200, 
 110, 
 820, 
 225, 
 820, 
 -1, 
 929, 
 120, 
 1100, 
 220, 
 1125, 
 -1, 
 828, 
 50, 
 828, 
 170, 
 790, 
 -1, 
 900, 
 50, 
 920, 
 90, 
 1860, 
 220, 
 1860, 
 -1, 
 1051, 
 40, 
 1051, 
 130, 
 1051, 
 -1, 
 1067, 
 30, 
 1067, 
 170, 
 1067, 
 -1, 
 2000, 
 45, 
 1050, 
 150, 
 1000, 
 -1, 
 1301, 
 30, 
 1319, 
 90, 
 1356, 
 -1, 
 1300, 
 30, 
 1300, 
 90, 
 1300, 
 -1, 
 1850, 
 100, 
 1540, 
 170, 
 1510, 
 -1, 
 1650, 
 110, 
 1500, 
 190, 
 1500, 
 -1, 
 1210, 
 100, 
 1280, 
 180, 
 1280, 
 -1, 
 870, 
 100, 
 1100, 
 150, 
 1200, 
 -1, 
 860, 
 80, 
 1170, 
 170, 
 1200, 
 -1, 
 2900, 
 40, 
 2800, 
 -1, 
 2800, 
 60, 
 2800, 
 -1, 
 2800, 
 10, 
 2800, 
 160, 
 2800, 
 -1, 
 2802, 
 20, 
 2703, 
 50, 
 2775, 
 170, 
 2788, 
 -1, 
 2650, 
 120, 
 2550, 
 230, 
 2550, 
 -1, 
 2640, 
 40, 
 2640, 
 100, 
 2640, 
 -1, 
 2440, 
 40, 
 2320, 
 170, 
 2320, 
 -1, 
 2500, 
 140, 
 2250, 
 200, 
 2400, 
 250, 
 2400, 
 -1, 
 1268, 
 30, 
 1268, 
 170, 
 1268, 
 -1, 
 2600, 
 45, 
 2250, 
 95, 
 2200, 
 -1, 
 2500, 
 30, 
 2500, 
 90, 
 2500, 
 -1, 
 2520, 
 30, 
 2520, 
 90, 
 2520, 
 -1, 
 2800, 
 60, 
 1830, 
 160, 
 1800, 
 -1, 
 2500, 
 80, 
 1790, 
 190, 
 1750, 
 -1, 
 2450, 
 90, 
 1720, 
 180, 
 1680, 
 -1, 
 2300, 
 10, 
 1530, 
 150, 
 1530, 
 -1, 
 2100, 
 60, 
 1600, 
 180, 
 1560, 
 -1, 
 130, 
 130, 
 120, 
 210, 
 120, 
 -1, 
 130, 
 90, 
 65, 
 220, 
 65, 
 -1, 
 120, 
 130, 
 100, 
 240, 
 100, 
 -1, 
 90, 
 130, 
 90, 
 210, 
 90, 
 -1, 
 110, 
 100, 
 100, 
 210, 
 220, 
 -1, 
 150, 
 45, 
 70, 
 150, 
 70, 
 -1, 
 250, 
 45, 
 130, 
 100, 
 130, 
 -1 };

#ifdef PHEDIT2
short femdip[3500] = {
#else
const short us_femdip_ken[] = {
#endif
 0, 
 0, 
 350, 
 10, 
 315, 
 -1, 
 460, 
 60, 
 486, 
 -1, 
 590, 
 10, 
 500, 
 170, 
 490, 
 -1, 
 712, 
 90, 
 680, 
 -1, 
 860, 
 50, 
 840, 
 190, 
 830, 
 -1, 
 810, 
 40, 
 810, 
 200, 
 810, 
 -1, 
 822, 
 40, 
 822, 
 120, 
 570, 
 210, 
 570, 
 -1, 
 830, 
 20, 
 900, 
 70, 
 600, 
 -1, 
 720, 
 40, 
 720, 
 120, 
 720, 
 -1, 
 730, 
 120, 
 770, 
 220, 
 770, 
 -1, 
 610, 
 40, 
 480, 
 170, 
 470, 
 -1, 
 590, 
 50, 
 740, 
 145, 
 540, 
 220, 
 520, 
 -1, 
 530, 
 50, 
 570, 
 130, 
 570, 
 -1, 
 430, 
 40, 
 400, 
 180, 
 400, 
 -1, 
 560, 
 30, 
 560, 
 170, 
 560, 
 -1, 
 370, 
 70, 
 410, 
 155, 
 410, 
 -1, 
 720, 
 30, 
 750, 
 90, 
 750, 
 -1, 
 490, 
 30, 
 500, 
 90, 
 500, 
 -1, 
 360, 
 100, 
 500, 
 170, 
 500, 
 -1, 
 530, 
 40, 
 650, 
 190, 
 650, 
 -1, 
 800, 
 100, 
 700, 
 180, 
 700, 
 -1, 
 510, 
 108, 
 580, 
 180, 
 580, 
 -1, 
 420, 
 80, 
 500, 
 170, 
 520, 
 -1, 
 685, 
 20, 
 570, 
 70, 
 560, 
 -1, 
 355, 
 10, 
 429, 
 100, 
 450, 
 -1, 
 2700, 
 10, 
 2800, 
 -1, 
 2482, 
 60, 
 2200, 
 -1, 
 2350, 
 10, 
 2650, 
 170, 
 2650, 
 -1, 
 1800, 
 110, 
 1700, 
 190, 
 1700, 
 -1, 
 1350, 
 40, 
 1290, 
 200, 
 1250, 
 -1, 
 1465, 
 80, 
 1613, 
 150, 
 2140, 
 -1, 
 1550, 
 70, 
 1060, 
 200, 
 1040, 
 -1, 
 1400, 
 40, 
 1400, 
 120, 
 1400, 
 -1, 
 1160, 
 120, 
 1260, 
 220, 
 1260, 
 -1, 
 1120, 
 40, 
 780, 
 170, 
 760, 
 -1, 
 850, 
 40, 
 970, 
 90, 
 2200, 
 190, 
 2230, 
 -1, 
 1150, 
 50, 
 1150, 
 130, 
 1150, 
 -1, 
 1370, 
 40, 
 1160, 
 180, 
 1120, 
 -1, 
 1810, 
 30, 
 1850, 
 170, 
 1850, 
 -1, 
 2300, 
 80, 
 1420, 
 155, 
 1320, 
 -1, 
 1800, 
 30, 
 1800, 
 90, 
 1800, 
 -1, 
 2350, 
 100, 
 1650, 
 170, 
 1620, 
 -1, 
 2200, 
 110, 
 1580, 
 190, 
 1560, 
 -1, 
 1270, 
 100, 
 1600, 
 180, 
 1600, 
 -1, 
 900, 
 108, 
 1450, 
 221, 
 1450, 
 -1, 
 800, 
 80, 
 1400, 
 170, 
 1400, 
 -1, 
 2136, 
 20, 
 1630, 
 55, 
 978, 
 -1, 
 1100, 
 10, 
 1683, 
 100, 
 1800, 
 -1, 
 2800, 
 10, 
 3300, 
 -1, 
 3068, 
 60, 
 2990, 
 -1, 
 2950, 
 10, 
 3000, 
 170, 
 3000, 
 -1, 
 3100, 
 110, 
 3150, 
 190, 
 3150, 
 -1, 
 2950, 
 40, 
 2950, 
 200, 
 2950, 
 -1, 
 2940, 
 120, 
 3017, 
 160, 
 2880, 
 200, 
 2900, 
 -1, 
 2860, 
 10, 
 2817, 
 80, 
 2886, 
 -1, 
 2950, 
 40, 
 2950, 
 100, 
 2950, 
 -1, 
 2920, 
 40, 
 2920, 
 200, 
 2920, 
 -1, 
 2830, 
 40, 
 2780, 
 170, 
 2780, 
 -1, 
 3030, 
 130, 
 2800, 
 180, 
 2970, 
 220, 
 2970, 
 -1, 
 2800, 
 50, 
 2800, 
 130, 
 2800, 
 -1, 
 2800, 
 40, 
 2700, 
 180, 
 2700, 
 -1, 
 2120, 
 30, 
 2120, 
 170, 
 2120, 
 -1, 
 3000, 
 60, 
 2400, 
 120, 
 2400, 
 -1, 
 3000, 
 30, 
 3000, 
 90, 
 3000, 
 -1, 
 3200, 
 70, 
 2150, 
 170, 
 2150, 
 -1, 
 2840, 
 100, 
 2150, 
 190, 
 2150, 
 -1, 
 3000, 
 10, 
 2600, 
 90, 
 2000, 
 180, 
 2000, 
 -1, 
 2400, 
 10, 
 2000, 
 188, 
 2000, 
 -1, 
 2450, 
 70, 
 2050, 
 180, 
 2050, 
 -1, 
 2909, 
 20, 
 2900, 
 70, 
 2900, 
 -1, 
 2595, 
 10, 
 2393, 
 100, 
 2208, 
 -1, 
 240, 
 50, 
 140, 
 140, 
 140, 
 -1, 
 90, 
 120, 
 90, 
 220, 
 90, 
 -1, 
 130, 
 30, 
 150, 
 130, 
 100, 
 -1, 
 150, 
 10, 
 120, 
 -1, 
 100, 
 100, 
 180, 
 220, 
 180, 
 -1, 
 150, 
 80, 
 100, 
 150, 
 100, 
 -1, 
 160, 
 10, 
 170, 
 -1, 
 290, 
 70, 
 150, 
 130, 
 130, 
 -1 };

#ifdef PHEDIT2
short ptram[100] = {
#else
const short us_ptram_ken[] = {
#endif
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 1, 
 0, 
 31, 
 61, 
 91, 
 121, 
 151, 
 181, 
 211, 
 241, 
 271, 
 301, 
 331, 
 361, 
 391, 
 421, 
 0, 
 451, 
 0, 
 481, 
 511, 
 0, 
 541, 
 571, 
 0, 
 0, 
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

#ifdef PHEDIT2
short plocu[500] = {
#else
const short us_plocu_ken[] = {
#endif
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 1, 
 0, 
 0, 
 10, 
 19, 
 28, 
 37, 
 0, 
 46, 
 55, 
 64, 
 73, 
 82, 
 91, 
 100, 
 109, 
 118, 
 127, 
 136, 
 145, 
 154, 
 163, 
 172, 
 181, 
 190, 
 199, 
 0, 
 208, 
 217, 
 226, 
 235, 
 244, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 253, 
 0, 
 0, 
 262, 
 271, 
 280, 
 289, 
 0, 
 298, 
 307, 
 316, 
 325, 
 334, 
 343, 
 352, 
 361, 
 370, 
 379, 
 388, 
 397, 
 406, 
 415, 
 424, 
 433, 
 442, 
 451, 
 0, 
 460, 
 469, 
 478, 
 487, 
 496, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 505, 
 0, 
 0, 
 514, 
 523, 
 532, 
 541, 
 0, 
 550, 
 559, 
 568, 
 577, 
 586, 
 595, 
 604, 
 613, 
 622, 
 631, 
 640, 
 649, 
 658, 
 667, 
 676, 
 685, 
 694, 
 703, 
 0, 
 712, 
 721, 
 730, 
 739, 
 748, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 757, 
 766, 
 775, 
 0, 
 784, 
 793, 
 802, 
 811, 
 820, 
 829, 
 838, 
 847, 
 856, 
 865, 
 874, 
 883, 
 892, 
 901, 
 910, 
 919, 
 0, 
 928, 
 0, 
 937, 
 946, 
 0, 
 0, 
 955, 
 0, 
 0, 
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

#ifdef PHEDIT2
short maleloc[3500] = {
#else
const short us_maleloc_ken[] = {
#endif
 0, 
 400, 
 20, 
 30, 
 -1, 
 -1, 
 -1, 
 2900, 
 30, 
 50, 
 480, 
 20, 
 35, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 300, 
 30, 
 30, 
 1200, 
 10, 
 35, 
 2100, 
 30, 
 40, 
 300, 
 20, 
 35, 
 1550, 
 85, 
 35, 
 2700, 
 40, 
 45, 
 180, 
 25, 
 40, 
 2400, 
 10, 
 60, 
 2600, 
 105, 
 60, 
 340, 
 10, 
 45, 
 1350, 
 20, 
 50, 
 2700, 
 0, 
 50, 
 280, 
 20, 
 35, 
 1550, 
 75, 
 35, 
 2400, 
 40, 
 45, 
 300, 
 63, 
 30, 
 1, 
 92, 
 35, 
 1725, 
 35, 
 30, 
 300, 
 50, 
 30, 
 1, 
 92, 
 35, 
 2100, 
 35, 
 40, 
 340, 
 10, 
 45, 
 1350, 
 20, 
 50, 
 2700, 
 0, 
 50, 
 340, 
 10, 
 45, 
 1350, 
 20, 
 50, 
 2700, 
 0, 
 50, 
 310, 
 40, 
 40, 
 1240, 
 40, 
 50, 
 2750, 
 0, 
 70, 
 310, 
 40, 
 40, 
 1240, 
 35, 
 50, 
 2550, 
 0, 
 70, 
 285, 
 32, 
 55, 
 2003, 
 30, 
 70, 
 2712, 
 51, 
 70, 
 285, 
 32, 
 55, 
 1830, 
 30, 
 70, 
 2640, 
 51, 
 70, 
 350, 
 55, 
 20, 
 900, 
 56, 
 30, 
 2200, 
 25, 
 45, 
 330, 
 55, 
 20, 
 950, 
 56, 
 30, 
 2200, 
 25, 
 45, 
 220, 
 43, 
 35, 
 1800, 
 66, 
 35, 
 2650, 
 30, 
 45, 
 220, 
 43, 
 35, 
 1800, 
 66, 
 35, 
 2650, 
 30, 
 45, 
 220, 
 33, 
 45, 
 2250, 
 20, 
 50, 
 2700, 
 117, 
 40, 
 250, 
 33, 
 45, 
 2201, 
 40, 
 80, 
 3000, 
 113, 
 20, 
 350, 
 50, 
 40, 
 1800, 
 30, 
 30, 
 2200, 
 50, 
 30, 
 320, 
 43, 
 35, 
 1800, 
 66, 
 35, 
 2650, 
 30, 
 45, 
 320, 
 54, 
 55, 
 1750, 
 25, 
 70, 
 2750, 
 19, 
 70, 
 240, 
 32, 
 55, 
 1750, 
 25, 
 70, 
 2750, 
 19, 
 70, 
 350, 
 40, 
 40, 
 1800, 
 40, 
 40, 
 2200, 
 40, 
 40, 
 501, 
 50, 
 70, 
 1500, 
 20, 
 150, 
 2600, 
 50, 
 50, 
 300, 
 70, 
 20, 
 1610, 
 70, 
 30, 
 2160, 
 50, 
 60, 
 400, 
 20, 
 30, 
 -1, 
 -1, 
 -1, 
 2900, 
 30, 
 50, 
 480, 
 20, 
 30, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 300, 
 20, 
 30, 
 1, 
 88, 
 40, 
 1550, 
 80, 
 25, 
 300, 
 20, 
 30, 
 1400, 
 25, 
 75, 
 2600, 
 0, 
 60, 
 180, 
 25, 
 40, 
 1900, 
 20, 
 70, 
 2600, 
 20, 
 70, 
 350, 
 10, 
 50, 
 1300, 
 12, 
 55, 
 2720, 
 11, 
 55, 
 280, 
 20, 
 30, 
 1420, 
 25, 
 75, 
 2400, 
 30, 
 60, 
 320, 
 60, 
 30, 
 1, 
 91, 
 35, 
 1725, 
 65, 
 40, 
 300, 
 50, 
 30, 
 1, 
 92, 
 40, 
 2100, 
 65, 
 40, 
 350, 
 10, 
 50, 
 1300, 
 12, 
 55, 
 2720, 
 11, 
 55, 
 350, 
 10, 
 50, 
 1300, 
 12, 
 55, 
 2720, 
 11, 
 55, 
 310, 
 40, 
 40, 
 1240, 
 40, 
 50, 
 2630, 
 0, 
 70, 
 310, 
 40, 
 40, 
 1240, 
 35, 
 60, 
 2630, 
 0, 
 70, 
 285, 
 32, 
 55, 
 1900, 
 27, 
 70, 
 2270, 
 0, 
 85, 
 285, 
 32, 
 55, 
 1800, 
 27, 
 70, 
 2270, 
 0, 
 85, 
 350, 
 45, 
 25, 
 920, 
 46, 
 30, 
 2250, 
 40, 
 50, 
 330, 
 45, 
 25, 
 920, 
 46, 
 30, 
 2250, 
 40, 
 50, 
 220, 
 43, 
 50, 
 1700, 
 40, 
 75, 
 2600, 
 0, 
 50, 
 250, 
 43, 
 50, 
 1700, 
 40, 
 75, 
 2600, 
 0, 
 50, 
 320, 
 33, 
 50, 
 2000, 
 16, 
 70, 
 2000, 
 30, 
 40, 
 300, 
 33, 
 50, 
 1800, 
 40, 
 60, 
 2152, 
 30, 
 90, 
 350, 
 50, 
 40, 
 1800, 
 30, 
 30, 
 2200, 
 40, 
 30, 
 320, 
 43, 
 50, 
 1700, 
 40, 
 75, 
 2600, 
 0, 
 50, 
 320, 
 54, 
 55, 
 1680, 
 10, 
 70, 
 2450, 
 10, 
 70, 
 245, 
 32, 
 55, 
 1680, 
 5, 
 120, 
 2450, 
 10, 
 70, 
 350, 
 40, 
 40, 
 1800, 
 40, 
 40, 
 2000, 
 40, 
 40, 
 290, 
 70, 
 35, 
 1500, 
 20, 
 80, 
 2600, 
 50, 
 30, 
 300, 
 70, 
 30, 
 1711, 
 70, 
 30, 
 2150, 
 50, 
 60, 
 400, 
 20, 
 30, 
 -1, 
 -1, 
 -1, 
 2900, 
 30, 
 50, 
 480, 
 20, 
 30, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 300, 
 20, 
 30, 
 1200, 
 10, 
 35, 
 2700, 
 80, 
 25, 
 300, 
 20, 
 30, 
 1550, 
 25, 
 95, 
 2320, 
 0, 
 95, 
 180, 
 25, 
 40, 
 1700, 
 42, 
 70, 
 2400, 
 25, 
 70, 
 350, 
 10, 
 50, 
 1300, 
 12, 
 55, 
 2720, 
 11, 
 55, 
 280, 
 20, 
 30, 
 1550, 
 25, 
 95, 
 2420, 
 30, 
 95, 
 320, 
 60, 
 30, 
 1, 
 91, 
 35, 
 1725, 
 65, 
 40, 
 325, 
 50, 
 30, 
 1, 
 91, 
 40, 
 2100, 
 65, 
 40, 
 350, 
 10, 
 50, 
 1300, 
 12, 
 55, 
 2720, 
 11, 
 55, 
 350, 
 10, 
 50, 
 1300, 
 12, 
 55, 
 2720, 
 11, 
 55, 
 310, 
 40, 
 40, 
 1320, 
 15, 
 60, 
 2460, 
 0, 
 65, 
 310, 
 40, 
 40, 
 1320, 
 15, 
 60, 
 2460, 
 0, 
 65, 
 340, 
 32, 
 55, 
 1830, 
 27, 
 90, 
 2100, 
 20, 
 110, 
 340, 
 32, 
 55, 
 1830, 
 27, 
 90, 
 2100, 
 20, 
 110, 
 350, 
 45, 
 25, 
 920, 
 46, 
 30, 
 2250, 
 40, 
 50, 
 320, 
 45, 
 25, 
 920, 
 46, 
 30, 
 2250, 
 40, 
 50, 
 320, 
 43, 
 40, 
 1700, 
 40, 
 95, 
 2300, 
 0, 
 40, 
 250, 
 43, 
 40, 
 1700, 
 40, 
 95, 
 2300, 
 0, 
 85, 
 320, 
 33, 
 40, 
 1600, 
 42, 
 65, 
 2100, 
 15, 
 80, 
 290, 
 45, 
 40, 
 1800, 
 42, 
 65, 
 2100, 
 15, 
 80, 
 350, 
 50, 
 40, 
 1800, 
 30, 
 30, 
 2200, 
 40, 
 30, 
 320, 
 43, 
 40, 
 1700, 
 40, 
 95, 
 2300, 
 0, 
 95, 
 320, 
 54, 
 55, 
 1680, 
 50, 
 90, 
 2209, 
 20, 
 100, 
 245, 
 32, 
 55, 
 1680, 
 10, 
 90, 
 1970, 
 10, 
 100, 
 350, 
 50, 
 50, 
 1800, 
 40, 
 40, 
 2000, 
 40, 
 40, 
 501, 
 50, 
 40, 
 1600, 
 20, 
 90, 
 2600, 
 50, 
 40, 
 300, 
 70, 
 30, 
 1610, 
 70, 
 36, 
 2160, 
 50, 
 60, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 0 };

#ifdef PHEDIT2
short femloc[3500] = {
#else
const short us_femloc_ken[] = {
#endif
 0, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 300, 
 30, 
 30, 
 1380, 
 10, 
 35, 
 2100, 
 30, 
 20, 
 450, 
 30, 
 60, 
 1880, 
 39, 
 35, 
 3250, 
 50, 
 45, 
 280, 
 20, 
 40, 
 2760, 
 10, 
 70, 
 3000, 
 114, 
 60, 
 340, 
 30, 
 45, 
 1300, 
 35, 
 60, 
 3180, 
 35, 
 60, 
 450, 
 24, 
 35, 
 2300, 
 75, 
 35, 
 3200, 
 35, 
 45, 
 350, 
 65, 
 30, 
 1, 
 87, 
 40, 
 2600, 
 35, 
 30, 
 350, 
 50, 
 55, 
 1, 
 85, 
 40, 
 2600, 
 35, 
 40, 
 360, 
 30, 
 45, 
 1300, 
 40, 
 70, 
 3180, 
 35, 
 70, 
 340, 
 30, 
 45, 
 1300, 
 35, 
 60, 
 3180, 
 35, 
 60, 
 270, 
 50, 
 40, 
 960, 
 78, 
 0, 
 2980, 
 38, 
 70, 
 270, 
 25, 
 40, 
 960, 
 78, 
 60, 
 2800, 
 38, 
 70, 
 360, 
 32, 
 55, 
 1700, 
 30, 
 70, 
 2940, 
 51, 
 70, 
 320, 
 26, 
 55, 
 2000, 
 30, 
 70, 
 2940, 
 51, 
 70, 
 370, 
 10, 
 30, 
 1570, 
 47, 
 25, 
 2700, 
 22, 
 25, 
 290, 
 30, 
 30, 
 1800, 
 17, 
 25, 
 2690, 
 30, 
 35, 
 470, 
 33, 
 35, 
 2160, 
 60, 
 35, 
 3159, 
 30, 
 45, 
 270, 
 33, 
 35, 
 2150, 
 66, 
 35, 
 2800, 
 30, 
 45, 
 250, 
 33, 
 40, 
 2700, 
 40, 
 60, 
 2800, 
 80, 
 50, 
 300, 
 33, 
 45, 
 2550, 
 13, 
 70, 
 2200, 
 50, 
 45, 
 350, 
 50, 
 30, 
 1900, 
 50, 
 30, 
 2100, 
 50, 
 30, 
 470, 
 33, 
 35, 
 2150, 
 60, 
 35, 
 3150, 
 30, 
 45, 
 400, 
 34, 
 55, 
 2100, 
 25, 
 70, 
 3300, 
 19, 
 70, 
 370, 
 32, 
 55, 
 2000, 
 25, 
 70, 
 3300, 
 19, 
 70, 
 350, 
 50, 
 30, 
 1800, 
 50, 
 30, 
 2400, 
 50, 
 30, 
 501, 
 50, 
 70, 
 1600, 
 20, 
 150, 
 2160, 
 50, 
 60, 
 330, 
 70, 
 20, 
 1710, 
 70, 
 30, 
 2260, 
 50, 
 60, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 480, 
 30, 
 35, 
 1, 
 88, 
 40, 
 2100, 
 48, 
 30, 
 450, 
 60, 
 45, 
 1800, 
 0, 
 75, 
 3200, 
 0, 
 30, 
 280, 
 20, 
 40, 
 1530, 
 20, 
 70, 
 2620, 
 20, 
 70, 
 400, 
 30, 
 50, 
 1800, 
 42, 
 70, 
 3060, 
 11, 
 70, 
 450, 
 22, 
 30, 
 2200, 
 65, 
 75, 
 3140, 
 30, 
 60, 
 350, 
 75, 
 30, 
 1, 
 85, 
 30, 
 2000, 
 65, 
 40, 
 350, 
 75, 
 30, 
 1, 
 84, 
 30, 
 2000, 
 65, 
 40, 
 440, 
 30, 
 50, 
 1800, 
 42, 
 70, 
 3060, 
 11, 
 70, 
 400, 
 30, 
 50, 
 1800, 
 42, 
 70, 
 3060, 
 11, 
 70, 
 270, 
 50, 
 45, 
 1800, 
 0, 
 80, 
 2800, 
 0, 
 70, 
 270, 
 25, 
 45, 
 1845, 
 0, 
 70, 
 2800, 
 0, 
 70, 
 360, 
 32, 
 55, 
 1700, 
 7, 
 70, 
 2700, 
 0, 
 85, 
 320, 
 26, 
 55, 
 1850, 
 7, 
 70, 
 2700, 
 0, 
 85, 
 260, 
 50, 
 35, 
 1240, 
 8, 
 30, 
 2200, 
 65, 
 40, 
 360, 
 50, 
 20, 
 1130, 
 50, 
 30, 
 2530, 
 48, 
 40, 
 180, 
 56, 
 70, 
 2050, 
 0, 
 80, 
 2960, 
 0, 
 50, 
 270, 
 33, 
 45, 
 2050, 
 40, 
 80, 
 2790, 
 0, 
 50, 
 440, 
 33, 
 35, 
 1900, 
 0, 
 60, 
 2500, 
 0, 
 90, 
 340, 
 43, 
 50, 
 1900, 
 10, 
 80, 
 2370, 
 10, 
 80, 
 350, 
 50, 
 30, 
 1800, 
 50, 
 40, 
 2100, 
 50, 
 30, 
 470, 
 33, 
 45, 
 2050, 
 0, 
 80, 
 2990, 
 0, 
 50, 
 420, 
 40, 
 55, 
 1900, 
 10, 
 70, 
 3200, 
 10, 
 70, 
 380, 
 40, 
 55, 
 1900, 
 10, 
 70, 
 3200, 
 10, 
 70, 
 350, 
 50, 
 30, 
 1900, 
 50, 
 30, 
 2100, 
 50, 
 30, 
 330, 
 70, 
 35, 
 1610, 
 20, 
 80, 
 2160, 
 50, 
 60, 
 330, 
 70, 
 30, 
 1710, 
 70, 
 30, 
 2260, 
 50, 
 60, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 -1, 
 300, 
 20, 
 30, 
 1, 
 88, 
 40, 
 1750, 
 80, 
 30, 
 450, 
 30, 
 60, 
 1700, 
 70, 
 35, 
 2800, 
 0, 
 80, 
 280, 
 20, 
 40, 
 1650, 
 42, 
 70, 
 2500, 
 25, 
 70, 
 400, 
 30, 
 50, 
 1800, 
 42, 
 70, 
 3060, 
 11, 
 70, 
 450, 
 24, 
 30, 
 2160, 
 65, 
 80, 
 2590, 
 30, 
 80, 
 350, 
 75, 
 30, 
 1, 
 85, 
 30, 
 2000, 
 65, 
 40, 
 350, 
 75, 
 30, 
 1, 
 84, 
 30, 
 2000, 
 65, 
 40, 
 440, 
 30, 
 50, 
 1800, 
 42, 
 70, 
 3060, 
 11, 
 70, 
 400, 
 30, 
 50, 
 1800, 
 42, 
 70, 
 3060, 
 11, 
 70, 
 270, 
 50, 
 40, 
 1900, 
 10, 
 80, 
 2880, 
 0, 
 65, 
 270, 
 25, 
 40, 
 1900, 
 10, 
 80, 
 2800, 
 0, 
 65, 
 400, 
 32, 
 55, 
 1750, 
 7, 
 90, 
 2700, 
 20, 
 110, 
 320, 
 30, 
 55, 
 1840, 
 7, 
 90, 
 2700, 
 20, 
 110, 
 260, 
 45, 
 70, 
 1240, 
 8, 
 30, 
 1900, 
 65, 
 40, 
 360, 
 50, 
 20, 
 1130, 
 50, 
 30, 
 2530, 
 48, 
 40, 
 470, 
 33, 
 40, 
 1900, 
 0, 
 70, 
 2850, 
 0, 
 90, 
 270, 
 33, 
 40, 
 1900, 
 40, 
 80, 
 2700, 
 20, 
 80, 
 250, 
 46, 
 35, 
 1710, 
 71, 
 65, 
 2300, 
 0, 
 80, 
 370, 
 45, 
 40, 
 1710, 
 71, 
 65, 
 2300, 
 15, 
 80, 
 350, 
 50, 
 30, 
 1800, 
 50, 
 40, 
 2100, 
 50, 
 30, 
 470, 
 33, 
 40, 
 1900, 
 0, 
 70, 
 2900, 
 20, 
 70, 
 420, 
 34, 
 55, 
 2050, 
 10, 
 90, 
 3100, 
 10, 
 100, 
 380, 
 32, 
 55, 
 2050, 
 10, 
 90, 
 3100, 
 10, 
 100, 
 350, 
 50, 
 30, 
 1800, 
 50, 
 30, 
 2100, 
 50, 
 30, 
 501, 
 50, 
 40, 
 1600, 
 20, 
 90, 
 2260, 
 50, 
 60, 
 330, 
 70, 
 30, 
 1710, 
 70, 
 30, 
 2260, 
 50, 
 60, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 0, 
 -1, 
 -1, 
 -1, 
 1710, 
 70, 
 30, 
 -1, 
 -1, 
 -1, 
 0 };

const struct rom_data_s us_rom_data_ken = {
us_inhdr_ken,
us_mindur_ken,
us_burdr_ken,
us_begtyp_ken,
us_endtyp_ken,
us_place_ken,
us_featb_ken,
us_maltar_ken,
us_femtar_ken,
us_maldip_ken,
us_femdip_ken,
us_ptram_ken,
us_plocu_ken,
us_maleloc_ken,
us_femloc_ken
};

