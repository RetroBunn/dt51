/* 
 ***********************************************************************
 *
 *                           Copyright ©
 *    © Digital Equipment Corporation 1996, 1997, 1998. All rights reserved.
 *    Copyright © 2000-2001 Force Computers Inc., a Solectron Company. All rights reserved.
 *
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Force Computers Incorporated and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Force or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:    p_us_vdf.c
 *    Author:
 *    Creation Date:
 *
 *    Functionality:
 *      Speaker defs for:
 *              1. PAUL
 *              2. BETTY
 *              3. HARRY
 *              4. FRANK
 *              5. DENNIS
 *              6. KIT
 *              7. URSULA
 *              8. RITA
 *              9. WENDY
 *              10. ED						
 *              11. MATT	 
 *              12. SUE	 
 *              13. MARY	 
 *              14. LYNN	 
 *              15. TOM	 
 *              16. IVAN	 
 *              17. CHARLINE
 *              18. JACKIE
 *              19. VAL
 *
 *      Cur speaker def does not really change until loadspdef set to TRUE
 *
 *      Thus one can load a new speaker into curspdef[] at any time
 *      without ever really changing the output voice until PHCLAUSE()
 *      is called with a new input phonemic clause.
 *
 ***********************************************************************
 *    Revision History:
 *
 * Rev  Who     Date            Description
 * ---  -----   -----------     -------------------------------------------- 
 * 0001 DK		12/06/1984	    Adopted from DECtalk klvdef.c
 * 0002 DGC		12/27/1984      Added the "readonly" things for the 80186.
 * 0003 DK		01/14/1985	    Fine tune voices to new tilt(f0) function
 * 0004 DK		01/21/1985      Increase richness of Paul (less base, more like old Paul)
 * 0005 DK		04/22/1985      Fix Betty to better match Diane Br.
 * 0006 DK		04/30/1985      Overload calibration for 3.0 for all voices
 * 0007 DK		06/03/1985      Increase SR for more lively voices
 * 0008 DK		06/10/1985	    Paul: ap down, Betty: ap up, Dennis: less breathy
 * 0009 DK		06/20/1985      Betty: ap back down a bit
 * 0010 DK 		07/24/1985      Boost LO so don't have to shift R1c output
 * 0011 DK		07/29/1985      Adjust spdef levels to avoid overloads during aspiration
 * 0012 DK		08/26/1985      Ursula still overloads, back off gains
 * 0013 DGC		09/06/1985      Harry head size to 115, from 120.
 * 0014 EAB 	01/07/1991	    re-evaluated and adjusted gains for all voices for 
 *                      		DECtalk-PC release
 * 0015 eab		05/03/1993      Changed betty's values to match 88 code except for new
 * 0016 WIH		08/19/1993      Added definitions for 8 kHz. sample rate.
 * 0017 EAB		03/22/1995	    Merged VTM definitions from Alpha group.
 * 0018 SIK		01/16/1996    	Removed white space inbetween # and include in places
 *                    			where #include is commented out.
 * 0019 MGS		03/25/1996	    Merged 42c code to WIN 95 42a code 
 * 0020 MGS		05/29/1996	 	Merged ED's changed since 0019
 * 0021	MGS		06/06/1996  	Changed file name from phvdef,c to ph_vdef.c
 * 0022 MGS     07/29/1996      Rolled back changed to the BR (breathiness parameter)
 * 0023 EDB     12/10/1996      Change kit_8[] breathness from 47 to 47-20
 * 0024 EAB     1/23/97			Checked and modified gh and gf balance after vocal tract.
 * 0025	TQL		01/23/97		Tuned the gains for code freeze.
 * 0026 TQL		02/20/97		Tuned the gains for code freeze.
 * 0027 TQL		05/08/97		Tuned the gains for code freeze.
 * 0028 EAB/CJL 08/14/97        Hand tuned changes.
 * 0029 EDB     10/19/1997      add NWSNOAA support
 * 0030 CJL     11/07/1997      EAB Made NWSNOAA Female voice changes.
 * 0031 EAB		1/27/98			Checked tunnig of 8k voices seems ok exxcept Paul's
								frication level was at 84 (propbably a typo chnged to 74)
								Bats 491 && 554
 * 0032 JAW     04/27/1998      Added default glottal speeds.
 * 0033 EAB	    7/13/98         AD tuning 
 * 0034 EAB		7/21/98			Tune smoothness parameter voices had too little tilt 
 * 0035 EAB		7/22/98		    Quick tune for new_intonation voices for AD
 * 0036 EAB		9/29/98  	    More minor tuning
 * 0037 EAB 	10/16/98        New tuning for new release
 * 0038 eab 	11/5 98         Refined after Jenny's tuning 8 and 11 khz.BATS 807
 * 0039 EAB 	11/16/98	    As part of bats 804(not submitted yet) found illegal value for Kit's F7 also noticed
 *					            that GF and gh were too high (BATS 818)
 * 0040 EAB 	2/23/99 		Working on Betty (female voice)
 * 0041 EAB 	3/26/99 		"To every gain  tune, tune.... tune... 
 * 0042 EAB 	10/10/00 		Revert to earlier version,, the 4 and 5th formants are not correct and Ken and I discussed this
 *								and the only thing we're sure of is that Dennis had a reason for what he did. Also the VTM has 
 *								some bill hallahan code to zap formants over 4500.
 * 0043 CAB		10/13/00		Formated comment section and fixed copyright info
 * 0045 CAB		02/22/01		Updated copyright info.
 * 0046 eab 	3/1/5/01 adJUSTED SOME F5 ABD B5 TO AID WITH DISCRIMATION
 * 0047 EAB		3/28/01 Fixed autotune overload problem Bats 955
 * 0048	MGS		04/11/2002		ARM7 port
 * 0049	MFG		09/19/2002	 	Added support for new chris voice
 */
#include "ph_defs.h" 


/**********************************************************************/
/**********************************************************************/
/* SPEAKER DEFINITIONS FOR 10 khz and 11 kHz.                         */
/**********************************************************************/
/**********************************************************************/

/* Perfect Paul */
const short paul[SPDEF] =
{
	1,		// SEX = male
	0,		// SM (smoothness, baseline spectral tilt offset 0-100%), only affects voiced objects, more tilt causes amplitude of higher glottal pulse frequencies to drop off
	100,	// AS (assertiveness, degree of final f0 fall in 0-200%), end-of-phrase pitch drop
	100,	// AP (Average pitch in Hz), base pitch
	100,	// PR (pitch range in percent of Paul's range 0-200%)
	9,		// BR (breathiness in dB), defines spectral shape of the noise
	25,		// RI (was 45,Richness in %, actually nopen is 100-RI % of T0), not used in HLSYN
	4,		// NF (additional fixed number of samples in nopen), limit for minimum #samples
	0,		// LA (laryngealization, in percent), affects phase and amplitude of glottal pulses, makes voice creeky
	100,	// HS (head size, in percent relative to normal for SEX, 0-200%)
	3500,	// F4 (was 3350, frequency in Hz of cascade 4th formant = F4*100/HS), use ZAPF to delete
	250,	// B4 (was 230, bandwidth in Hz of cascade 4th formant), use ZAPB to delete
	3900,	/* F5 (was 3900, frequency in Hz of cascade 5th formant = F5*100/HS) */
	1000,	/* B5 (was 180, bandwidth in Hz of cascaded 5th formant) */
	3500,	// F7 (frequency in Hz of parallel 4th formant = F7), used in unvoiced frication
	4500,	// F8 (frequency in Hz of parallel 5th formant = F8), used in unvoiced frication
    54,     /* GF (gain of frication source in dB) */
    59,     /* GH (gain of aspiration source in dB) */
	59,		/* GV (gain of voicing source in dB ) */
	70,		/* GN (gain of input to cascade nasal pole pair in dB) */
	70,		/* G1 (gain of input to cascade 5th formant in dB) */
	64,		/* G2 (gain of input to cascade 4th formant in dB) */
	64,		/* G3 (gain of input to cascade 3rd formant in dB) */
	65, 	/* G4 (gain of input to cascade 2nd formant in dB) */
	69, 	/* LO (Loudness, gain input to cascade 1st formant in dB), G5 or Gain of F1 */
	73,		/* FT (f0-dependent spectral tilt in % of max) */
	18,		// BF (baseline f0 fall in Hz), end-of-phrase fall
	0,		// LX (lax folds adjacent to voiceless sound -> breathiness),  not used
	90,		// QU (quickness of larynx gestures in % of max quickness), not used
	10,		// HR (hat-pattern fundamental frequency rise in Hz), not used in all languages
	28,		/* SR (height of max stress-rise impulse of f0 in Hz, was 32) */
	400,    // AGO - Average glottal opening (mm^2 * 100)
	1300,	// AGVO - Voiced Obstruent glottal target
	2700,	// AGUO - average Glottal opening for unvoiced obstruent
	500,	// UNVOW - Unstressed Vowel glottal opening
	20,		// CHINK - default minimum chink area - open chink for voiced obstruent for more frication
	70,		// OQ - open quotient 0-100%, average period of gottal cycle, affects amount of low frequency energy
	11001,	// GP - Tracheal pole, not used (experimental)
	1001,	// GZ - Tracheal zero, not used (experimental)
	1,		//OS Gain
	PAUL,	// NAME
	0,		//new5
	0,		//new6
	658,//endofphrase_spread_target
	70,//HL_B1m;
	110,//HL_B2m;
	160,//HL_B3m;
	180,//HL_B4m;
	200,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	260,//HL_B4F;
	270,//HL_B5F;
	4800,//HL_F6;
	600,//HL_B6F;
	30,//stress_step;
	80,//unstress_pressure;
	200,//stress_pressure;
	800,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	10,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	600,//HL_acd_f1_break;
	38,//Ka;
	-100,//f2_ref_scale;
	-150,//f3_ref_scale;
	1,//diplo_step;
	200,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	150,//tune_param_1; //lift for a stress vowel
	250,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	100,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4200 //HL_F5

};	// Paul


/* Beautiful Betty */
const short betty[SPDEF] =
{
	FEMALE,		/* SEX = f */
	0,			/* SM (smoothness in %, actually spectral tilt offset) */
	100,		/* AS (assertiveness, degree of final f0 fall in % */
	180,		/* AP (Average pitch in Hz) */
	100,		/* PR (pitch range in percent of Paul's range) */
	0,			/* BR (breathiness in dB) */
	20,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	10,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	4300,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	160,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	4700,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	600,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4200,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4900,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    67,         /* GF (gain of frication source in dB) */
    59,         /* GH (gain of aspiration source in dB) */
	64,			/* GV (gain of voicing source in dB ) */
	86,			/* GN (gain of input to cascade nasal pole pair in dB) */
	86,			/* G1 (gain of input to cascade 5th formant in dB) */
	66,			/* G2 (gain of input to cascade 4th formant in dB) */
	52,			/* G3 (gain of input to cascade 3rd formant in dB) */
	69,			/* G4 (gain of input to cascade 2nd formant in dB) */
	86,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	30,			/* FT (f0-dependent spectral tilt in % of max) */
	15,			/* BF (baseline f0 fall in Hz) */
	49,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	85,			/* QU (quickness of larynx gestures in % of max quickness) */
	0,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	35,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	380,        /* AGO */
	1100,		/* agvo */
	2500,		/* aguo */
	600,		/*unvow*/
	20,		//chink area 
	80,			//open quotient
	29100,
	18900,
	1,			//OS Gain
	BETTY,		//NAME
	0,			//new5
	0,			//new6
	438,			//endofphrase_spread_target
	80,			//HL_B1m;
	98,			//HL_B2m;
	145,		//HL_B3m;
	300,		//HL_B4m;
	600,		//HL_B5m;
	250,		//HL_B2F;
	320,		//HL_B3F;
	260,		//HL_B4F;
	370,		//HL_B5F;
	4700,		//HL_F6;
	600,		//HL_B6F;
	20,			//stress_step;
	30,			//unstress_pressure;
	160,		//stress_pressure;
	800,		//nom_sub_pressure;
	100,		//nom_fricative_opening;
	0,			//nom_glot_stop_area;
	3,			//vot_speed;
	23,			//endofphrase_spread;
	5,			//HL_num_formants;
	1350,		//HL_f1_hi_shift;
	350,		//HL_acd_f1_break;
	35,			//Ka;
	180,		//f2_ref_scale;
	180,		//f3_ref_scale;
	7,			//diplo_step;
	450,		//endpoint_below_ap;
	-100,		//endpoint_mult_stress;
	220,		//tune_param_1; //lift for a stress vowel
	450,		//tune_param_2; //lift with a stressed vowel following a stop
	100,		//init_st_no_aspir;
	204,		//str_vow_before_final;
	350,		//agm; // Modal glottal area
	40,			//KTL
	4500		//HL_F5

};	// Betty

#ifdef STEVE_HAWKINGS
/* Huge Harry */
const short harry[SPDEF] =
{
	MALE,		/* SEX = m */
	30,			/* SM (smoothness in %, actually spectral tilt offset) */
	100,		/* AS (assertiveness, degree of final f0 fall in % */
	110,		/* AP (Average pitch in Hz) */
	100,		/* PR (pitch range in percent of Paul's range) */
	0,			/* BR (breathiness in dB) */
	70,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	0,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	3450,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	160,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	3900,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	120,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	3500,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4000,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    55,         /* GF (gain of frication source in dB) */
    40,         /* GH (gain of aspiration source in dB) */
	55,			/* GV (gain of voicing source in dB ) */
	62,			/* GN (gain of input to cascade nasal pole pair in dB) */
	67,			/* G1 (gain of input to cascade 5th formant in dB) */
	50,			/* G2 (gain of input to cascade 4th formant in dB) */
	54,     	/* G3 (gain of input to cascade 3rd formant in dB) */
	62,			/* G4 (gain of input to cascade 2nd formant in dB) */
	57,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	0,			/* FT (f0-dependent spectral tilt in % of max) */
	0,			/* BF (baseline f0 fall in Hz) */
	0,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	55,			/* QU (quickness of larynx gestures in % of max quickness) */
	10,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	22,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	500,        /* AGO */
	1000,		/*agvo */
	2300,		/*aguo */
	1000,		/*unvow*/
	0,	//chink area 
	50, //open quotient
	9779, //gp
	650, //gz
	1, //OS Gain
	HARRY,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	60,//HL_B1m;
	110,//HL_B2m;
	110,//HL_B3m;
	230,//HL_B4m;
	340,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	260,//HL_B4F;
	260,//HL_B5F;
	4990,//HL_F6;
	1200,//HL_B6F;
	50,//stress_step;
	80,//unstress_pressure;
	400,//stress_pressure;
	800,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	0,//vot_speed;
	2,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	540,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	0,//diplo_step;
	200,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	60,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4400 //HL_F5
};	// Harry (Stephen Hawkings)

#else

/* Huge Harry */
const short harry[SPDEF] =
{
	MALE,		/* SEX = m */
	0,			/* SM (smoothness in %, actually spectral tilt offset) */
	100,		/* AS (assertiveness, degree of final f0 fall in % */
	87,			/* AP (Average pitch in Hz) */
	80,			/* PR (pitch range in percent of Paul's range) */
	0,			/* BR (breathiness in dB) */
	70,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	20,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	107,		/* HS (head size, in percent relative to normal for SEX) */
	3500,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	280,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	3700,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	400,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	3200,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4880,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    59,         /* GF (gain of frication source in dB) */
    52,         /* GH (gain of aspiration source in dB) */
	59,			/* GV (gain of voicing source in dB ) */
	61,			/* GN (gain of input to cascade nasal pole pair in dB) */
	66,			/* G1 (gain of input to cascade 5th formant in dB) */
	49,			/* G2 (gain of input to cascade 4th formant in dB) */
	53,     	/* G3 (gain of input to cascade 3rd formant in dB) */
	61,			/* G4 (gain of input to cascade 2nd formant in dB) */
	56,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	10,			/* FT (f0-dependent spectral tilt in % of max) */
	5,			/* BF (baseline f0 fall in Hz) */
	0,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	95,			/* QU (quickness of larynx gestures in % of max quickness) */
	10,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	22,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	500,        /* AGO */
	1000,		/*4agvo */
	2300,		/*aguo */
	1000,		/*unvow*/
	0,	//chink area 
	90, //open quotient
	9779, //gp
	650, //gz
	1, //OS Gain
	HARRY,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	60,//HL_B1m;
	110,//HL_B2m;
	110,//HL_B3m;
	230,//HL_B4m;
	340,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	260,//HL_B4F;
	260,//HL_B5F;
	4990,//HL_F6;
	1200,//HL_B6F;
	50,//stress_step;
	80,//unstress_pressure;
	400,//stress_pressure;
	800,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	0,//vot_speed;
	2,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	540,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	0,//diplo_step;
	200,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	60,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4500 //HL_F5

};	// Harry
#endif	// (! Stephen Hawkings)


//hlsyn
/* Frail Frank */
const short frank[SPDEF] =
{
//really ken
	1,			/* SEX = m */
	30,			/* SM (smoothness in %, actually spectral tilt offset) */
	100,		/* AS (assertiveness, degree of final f0 fall in % */
	110,		/* AP (Average pitch in Hz) */
	100,		/* PR (pitch range in percent of Paul's range) */
	0,			/* BR (breathiness in dB) */
	20,			/* RI (was 45,Richness in %, actually nopen is 100-RI % of T0) */
	10,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	3500,		/* F4 (was 3350, frequency in Hz of cascade 4th formant = F4*100/HS) */
	350,		/* B4 (was 230, bandwidth in Hz of cascade 4th formant) */
	4500,		/* F5 (was 3900, frequency in Hz of cascade 5th formant = F5*100/HS) */
	500,		/* B5 (was 180, bandwidth in Hz of cascaded 5th formant) */
	3400,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4800,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    60,         /* GF (gain of frication source in dB) */
    50,         /* GH (gain of aspiration source in dB) */
	60,			/* GV (gain of voicing source in dB ) */
	71,			/* GN (gain of input to cascade nasal pole pair in dB) */
	71,			/* G1 (gain of input to cascade 5th formant in dB) */
	65,			/* G2 (gain of input to cascade 4th formant in dB) */
	65,			/* G3 (gain of input to cascade 3rd formant in dB) */
	66, 		/* G4 (gain of input to cascade 2nd formant in dB) */
	70, 		/* LO (Loudness, gain input to cascade 1st formant in dB) */
	73,			/* FT (f0-dependent spectral tilt in % of max) */
	18,			/* BF (baseline f0 fall in Hz) */
	0,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	40,			/* QU (quickness of larynx gestures in % of max quickness) */
	18,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	5,			/* SR (height of max stress-rise impulse of f0 in Hz, was 32) */
	400,        /* AGO */
	1000,		/*agvo */
	2100,		/*aguo */
	700,		/*unvow*/
	0,	//chink area 
	80, //open quotient
	12351,
	2351,
	1, //OS Gain
	FRANK,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	100,//HL_B1m;
	120,//HL_B2m;
	150,//HL_B3m;
	180,//HL_B4m;
	350,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	260,//HL_B4F;
	270,//HL_B5F;
	4800,//HL_F6;
	600,//HL_B6F;
	10,//stress_step;
	80,//unstress_pressure;
	100,//stress_pressure;
	850,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	1,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	540,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	8,//diplo_step;
	100,//endpoint_below_ap;
	10,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	100,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4500 //HL_F5

};	// Frank


/* Kit the Kid */
//hlsyn
const short kit[SPDEF] =
{
	FEMALE,		/* SEX = f */
	50,			/* SM (smoothness in %, actually spectral tilt offset) */
	65,			/* AS (assertiveness, degree of final f0 fall in % */
	285,		/* AP (Average pitch in Hz) */
	120,		/* PR (pitch range in percent of Paul's range) */
	0,			/* BR (breathiness in dB) */
	40,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	10,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	96,			/* HS (head size, in percent relative to normal for SEX) */
	4700,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	500,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	ZAPF,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	ZAPB,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4450,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4800,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
	60,			/* GF (gain of frication source in dB) */
	55,			/* GH (gain of aspiration source in dB) */
	60,			/* GV (gain of voicing source in dB ) */
	68,			/* GN (gain of input to cascade nasal pole pair in dB) */
	65,			/* G1 (gain of input to cascade 5th formant in dB) */
	69,			/* G2 (gain of input to cascade 4th formant in dB) */
	60,			/* G3 (gain of input to cascade 3rd formant in dB) */
	55,			/* G4 (gain of input to cascade 2nd formant in dB) */
	65,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	75,			/* FT (f0-dependent spectral tilt in % of max) */
	10,			/* BF (baseline f0 fall in Hz) */
	75,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	50,			/* QU (quickness of larynx gestures in % of max quickness) */
	20,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	20,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	300,        /* AGO */
	1000,		/*agvo */
	2100,		/*aguo */
	700,		/*unvow*/
	0,	//chink area 
	30, //open quotient
	9500, //gp
	1600, //gz
	1, //OS Gain
	KIT,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	95,//HL_B1m;
	130,//HL_B2m;
	160,//HL_B3m;
	180,//HL_B4m;
	200,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	260,//HL_B4F;
	270,//HL_B5F;
	4800,//HL_F6;
	1200,//HL_B6F;
	10,//stress_step;
	80,//unstress_pressure;
	100,//stress_pressure;
	800,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	0,//vot_speed;
	10,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	950,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	0,//diplo_step;
	300,//endpoint_below_ap;
	300,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	60,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4700 //HL_F5

};	// Kit

const short ursula[SPDEF] =
{
	FEMALE,		/* SEX = f */
	60,			/* SM (smoothness in %, actually spectral tilt offset) */
	100,		/* AS (assertiveness, degree of final f0 fall in % */
	220,		/* AP (Average pitch in Hz) */
	100,		/* PR (pitch range in percent of Paul's range) */
	0,			/* BR (breathiness in dB) */
	60,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	5,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	4450,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	260,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	4950,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	600,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4450,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4900,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    60,         /* GF (gain of frication source in dB) */
    55,         /* GH (gain of aspiration source in dB) */
	60,			/* GV (gain of voicing source in dB ) */
	70,			/* GN (gain of input to cascade  pole pair in dB) */
	69,			/* G1 (gain of input to cascade 5th formant in dB) */
	73,			/* G2 (gain of input to cascade 4th formant in dB) */
    55,         /* G3 (gain of input to cascade 3rd formant in dB) */
	59,			/* G4 (gain of input to cascade 2nd formant in dB) */
	66,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	60,			/* FT (f0-dependent spectral tilt in % of max) */
	18,			/* BF (baseline f0 fall in Hz) */
	50,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	30,			/* QU (quickness of larynx gestures in % of max quickness) */
	1,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	32,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	350,        /* AGO */
	1000,		/*agvo */
	1500,		/*aguo */
	700,		/*unvow*/
	0,	//chink area 
	65, //open quotient
	29200,
	1100,
	1, //OS Gain
	URSULA,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	120,//HL_B1m;
	130,//HL_B2m;
	140,//HL_B3m;
	230,//HL_B4m;
	340,//HL_B5m;
	250,//HL_B2F;
	220,//HL_B3F;
	250,//HL_B4F;
	200,//HL_B5F;
	4800,//HL_F6;
	1200,//HL_B6F;
	20,//stress_step;
	80,//unstress_pressure;
	100,//stress_pressure;
	900,//nom_sub_pressure;
	110,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	8,//endofphrase_spread;
	5,//HL_num_formants;
	1280,//HL_f1_hi_shift;
	650,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	0,//diplo_step;
	250,//endpoint_below_ap;
	-100,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	100,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4650 //HL_F5

};	// Ursula



/* Rough Rita */
//really sueb
const short rita[SPDEF] =
{
	FEMALE,		/* SEX = f */
	70,			/* SM (smoothness in %, actually spectral tilt offset) */
	100,		/* AS (assertiveness, degree of final f0 fall in % */
	190,		/* AP (Average pitch in Hz) */
	100,		/* PR (pitch range in percent of Paul's range) */
	40,			/* BR (breathiness in dB) */
	40,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	0,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	4076,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	240,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	ZAPF,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	ZAPB,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4040,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	ZAPF,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    60,         /* GF (gain of frication source in dB) */
    45,         /* GH (gain of aspiration source in dB) */
	50,			/* GV (gain of voicing source in dB ) */
	40,			/* GN (gain of input to cascade nasal pole pair in dB) */
	66,			/* G1 (gain of input to cascade 5th formant in dB) */
	65,			/* G2 (gain of input to cascade 4th formant in dB) */
	60,			/* G3 (gain of input to cascade 3rd formant in dB) */
	65,			/* G4 (gain of input to cascade 2nd formant in dB) */
	63,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	30,			/* FT (f0-dependent spectral tilt in % of max) */
	10,			/* BF (baseline f0 fall in Hz) */
	60,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	45,			/* QU (quickness of larynx gestures in % of max quickness) */
	5,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	50,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	450,        /* AGO */
	1000,		/*agvo */
	1800,		/*aguo */
	400,		/*unvow*/
	00,			//chink area 
	73,			//open quotient
	12750,
	1100,
	1,			//OS Gain
	RITA,		// NAME
	0,			//new5
	0,			//new6
	438,			//endofphrase_spread_target
	140,		//HL_B1m;
	220,		//HL_B2m;
	240,		//HL_B3m;
	230,		//HL_B4m;
	340,		//HL_B5m;
	250,		//HL_B2F;
	320,		//HL_B3F;
	260,		//HL_B4F;
	260,		//HL_B5F;
	4990,		//HL_F6;
	600,		//HL_B6F;
	20,			//stress_step;
	80,			//unstress_pressure;
	100,		//stress_pressure;
	650,		//nom_sub_pressure;
	120,		//nom_fricative_opening;
	0,			//nom_glot_stop_area;
	1,			//vot_speed;
	5,			//endofphrase_spread;
	5,			//HL_num_formants;
	1180,		//HL_f1_hi_shift;
	650,		//HL_acd_f1_break;
	45,			//Ka;
	0,			//f2_ref_scale;
	450,		//f3_ref_scale;
	0,			//diplo_step;
	530,		//endpoint_below_ap;
	75,			//endpoint_mult_stress;
	200,		//tune_param_1; //lift for a stress vowel
	450,		//tune_param_2; //lift with a stressed vowel following a stop
	300,		//init_st_no_aspir;
	60,			//str_vow_before_final;
	700,		//agm; // Modal glottal area
	0,			//KTL
	5200		//HL_F5

};	// Rita


/* Whispery Wendy */
//really ali
const short wendy[SPDEF] =
{
	FEMALE,			/* SEX = m */
	20,				/* SM (smoothness in %, actually spectral tilt offset) */
	50,	   			/* AS (assertiveness, degree of final f0 fall in % */
	195,			/* AP (Average pitch in Hz) */
	100,			/* PR (pitch range in percent of Paul's range) */
	45,				/* BR (breathiness in dB) */
	20,				/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	10,				/* NF (additional fixed number of samples in nopen) */
	0,				/* LA (laryngealization, in percent) */
	100,			/* HS (head size, in percent relative to normal for SEX) */
	4600,			/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	300,			/* B4 (bandwidth in Hz of cascade 4th formant) */
	ZAPF,			/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	ZAPB,			/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4200,			/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4800,			/* F8 (frequency in Hz of parallel 5th formant = F8) */
					/* complaints that whisper voice sometimes overload-dropped source  2db for Wendy doctor and frank */
	55,				/* GF (gain of frication source in dB) */
	55,				/* GH (gain of aspiration source in dB) */
	59,				/* GV (gain of voicing source in dB ) */
	71,				/* GN (gain of input to cascade nasal pole pair in dB) */
	69,				/* G1 (gain of input to cascade 5th formant in dB) */
	78,				/* G2 (gain of input to cascade 4th formant in dB) */
	56,				/* G3 (gain of input to cascade 3rd formant in dB) */
	57,				/* G4 (gain of input to cascade 2nd formant in dB) */
	68,				/* LO (Loudness, gain input to cascade 1st formant in dB) */
	100,			/* FT (f0-dependent spectral tilt in % of max) */
	10,				/* BF (baseline f0 fall in Hz) */
	80,				/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	20,				/* QU (quickness of larynx gestures in % of max quickness) */
	18,				/* HR (hat-pattern fundamental frequency rise in Hz) */
	22,				/* SR (height of max stress-rise impulse of f0 in Hz) */
	450,            /* AGO */
	1000,			/*agvo */
	2500,			/*aguo */
	900,			/*unvow*/
	60,				//chink area 
	60,				//open quotient
	11700,
	1100,
	1,				//OS Gain
	WENDY,			// NAME
	0,				//new5
	0,				//new6
	438,				//endofphrase_spread_target
	120,			//HL_B1m;
	130,			//HL_B2m;
	140,			//HL_B3m;
	230,			//HL_B4m;
	340,			//HL_B5m;
	250,			//HL_B2F;
	220,			//HL_B3F;
	250,			//HL_B4F;
	200,			//HL_B5F;
	4800,			//HL_F6;
	1200,			//HL_B6F;
	20,				//stress_step;
	80,				//unstress_pressure;
	100,			//stress_pressure;
	900,			//nom_sub_pressure;
	110,			//nom_fricative_opening;
	0,				//nom_glot_stop_area;
	2,				//vot_speed;
	2,				//endofphrase_spread;
	5,				//HL_num_formants;
	1350,			//HL_f1_hi_shift;
	350,			//HL_acd_f1_break;
	30,				//Ka;
	0,				//f2_ref_scale;
	0,				//f3_ref_scale;
	0,				//diplo_step;
	400,			//endpoint_below_ap;
	100,			//endpoint_mult_stress;
	60,				//tune_param_1; //lift for a stress vowel
	60,				//tune_param_2; //lift with a stressed vowel following a stop
	60,				//init_st_no_aspir;
	60,				//str_vow_before_final;
	400,			//agm; // Modal glottal area
	0,				//KTL
	4850			//HL_F5

};	// Wendy

/* Doctor Dennis */
const short dennis[SPDEF] =
{
	MALE,		/* SEX = m */
	65,			/* SM (smoothness in %, actually spectral tilt offset) */
	100,		/* AS (assertiveness, degree of final f0 fall in % */
	110,		/* AP (Average pitch in Hz) */
	100,		/* PR (pitch range in percent of Paul's range) */
	30,			/* BR (breathiness in dB) */
	20,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	10,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	3500,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	240,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	3800,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	180,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4100,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4900,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
				/* complaint that whisper voice sometimes overload-dropped source  2db for Wendy doctor and frank */
	66,			/* GF (gain of frication source in dB) */
	53,			/* GH (gain of aspiration source in dB) */
	66,			/* GV (gain of voicing source in dB ) */
	71,			/* GN (gain of input to cascade nasal pole pair in dB) */
	75,			/* G1 (gain of input to cascade 5th formant in dB) */
	65,			/* G2 (gain of input to cascade 4th formant in dB) */
	57,         /* G3 (gain of input to cascade 3rd formant in dB) */
	62,			/* G4 (gain of input to cascade 2nd formant in dB) */
	72,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	100,		/* FT (f0-dependent spectral tilt in % of max) */
	9,			/* BF (baseline f0 fall in Hz) */
	70,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	50,			/* QU (quickness of larynx gestures in % of max quickness) */
	10,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	22,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	400,        /* AGO */
	1000,		/*agvo */
	1200,		/*aguo */
	700,		/*unvow*/
	0,	//chink area 
	50, //open quotient
	11100,
	500,
	1, //OS Gain
	DENNIS,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	70,//HL_B1m;
	90,//HL_B2m;
	130,//HL_B3m;
	180,//HL_B4m;
	200,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	260,//HL_B4F;
	270,//HL_B5F;
	4800,//HL_F6;
	600,//HL_B6F;
	10,//stress_step;
	80,//unstress_pressure;
	100,//stress_pressure;
	800,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	10,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	540,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	0,//diplo_step;
	400,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	60,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4500 //HL_F5

};	// Dennis


/**********************************************************************/
/**********************************************************************/
/* SPEAKER DEFINITIONS FOR 10 khz and 11 kHz.                         */
/**********************************************************************/
/**********************************************************************/

/* Perfect Paul */
const short ed[SPDEF] =
{
	1,			/* SEX = m */
	10,			/* SM (smoothness in %, actually spectral tilt offset) */
	120,		/* AS (assertiveness, degree of final f0 fall in % */
	122,		/* AP (Average pitch in Hz) */
	91,			/* PR (pitch range in percent of Paul's range) */
	0,			/* BR (breathiness in dB) */
	25,			/* RI (was 45,Richness in %, actually nopen is 100-RI % of T0) */
	20,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	3300,		/* F4 (was 3350, frequency in Hz of cascade 4th formant = F4*100/HS) */
	260,		/* B4 (was 230, bandwidth in Hz of cascade 4th formant) */
	4160,		/* F5 (was 3900, frequency in Hz of cascade 5th formant = F5*100/HS) */
	270,		/* B5 (was 180, bandwidth in Hz of cascaded 5th formant) */
	3400,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4160,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    60,         /* GF (gain of frication source in dB) */
    55,         /* GH (gain of aspiration source in dB) */
	60,			/* GV (gain of voicing source in dB ) */
	71,			/* GN (gain of input to cascade nasal pole pair in dB) */
	71,			/* G1 (gain of input to cascade 5th formant in dB) */
	65,			/* G2 (gain of input to cascade 4th formant in dB) */
	65,			/* G3 (gain of input to cascade 3rd formant in dB) */
	66, 		/* G4 (gain of input to cascade 2nd formant in dB) */
	70, 		/* LO (Loudness, gain input to cascade 1st formant in dB) */
	73,			/* FT (f0-dependent spectral tilt in % of max) */
	18,			/* BF (baseline f0 fall in Hz) */
	0,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	90,			/* QU (quickness of larynx gestures in % of max quickness) */
	10,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	25,			/* SR (height of max stress-rise impulse of f0 in Hz, was 32) */
	400,        /* AGO */
	1000,		/*agvo */
	2100,		/*aguo */
	600,		/*unvow*/
	50,	//chink area 
	90, //open quotient
	11001,//gp
	1001,//gz
	1, //OS Gain
	ED,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	60,//HL_B1m;
	90,//HL_B2m;
	130,//HL_B3m;
	180,//HL_B4m;
	200,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	260,//HL_B4F;
	270,//HL_B5F;
	4700,//HL_F6;
	600,//HL_B6F;
	10,//stress_step;
	80,//unstress_pressure;
	200,//stress_pressure;
	800,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	10,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	600,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	0,//diplo_step;
	220,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	150,//tune_param_1; //lift for a stress vowel
	120,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	100,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4500 //HL_F5

};	// Ed


const short sue[SPDEF] =
{
	FEMALE,		/* SEX = f */
	80,			/* SM (smoothness in %, actually spectral tilt offset) */
	100,		/* AS (assertiveness, degree of final f0 fall in % */
	175, 		/* AP (Average pitch in Hz) */
	100,		/* PR (pitch range in percent of Paul's range) */
	10,			/* BR (breathiness in dB) */
	40,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	0,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	4350,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	280,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	ZAPF,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	ZAPB,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4300,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4800,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    60,         /* GF (gain of frication source in dB) */
    55,         /* GH (gain of aspiration source in dB) */
	60,			/* GV (gain of voicing source in dB ) */
	63,			/* GN (gain of input to cascade nasal pole pair in dB) */
	56,			/* G1 (gain of input to cascade 5th formant in dB) */
	65,			/* G2 (gain of input to cascade 4th formant in dB) */
	60,			/* G3 (gain of input to cascade 3rd formant in dB) */
	60,			/* G4 (gain of input to cascade 2nd formant in dB) */
	63,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	30,			/* FT (f0-dependent spectral tilt in % of max) */
	10,			/* BF (baseline f0 fall in Hz) */
	30,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	85,			/* QU (quickness of larynx gestures in % of max quickness) */
	0,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	35,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	350,        /* AGO */
	1000,		/* agvo */
	1800,		/* aguo */
	800,		/*unvow*/
	51,	//chink area 
	70, //open quotient
	2250,
	1800,
	1, //OS Gain
	SUE,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	140,//HL_B1m;
	140,//HL_B2m;
	240,//HL_B3m;
	230,//HL_B4m;
	320,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	260,//HL_B4F;
	260,//HL_B5F;
	4990,//HL_F6;
	600,//HL_B6F;
	20,//stress_step;
	100,//unstress_pressure;
	200,//stress_pressure;
	650,//nom_sub_pressure;
	120,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	5,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	650,//HL_acd_f1_break;
	40,//Ka;
	0,//f2_ref_scale;
	450,//f3_ref_scale;
	0,//diplo_step;
	530,//endpoint_below_ap;
	75,//endpoint_mult_stress;
	200,//tune_param_1; //lift for a stress vowel
	450,//tune_param_2; //lift with a stressed vowel following a stop
	300,//init_st_no_aspir;
	60,//str_vow_before_final;
	350,//agm; // Modal glottal area
	0,//KTL
	5200 //HL_F5
	
};	// Sue

/* Huge Harry */
const short matt[SPDEF] =
{
	MALE,		/* SEX = m */
	25,			/* SM (smoothness in %, actually spectral tilt offset) */
	100,		/* AS (assertiveness, degree of final f0 fall in % */
	104,		/* AP (Average pitch in Hz) */
	100,		/* PR (pitch range in percent of Paul's range) */
	0,			/* BR (breathiness in dB) */
	30,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	20,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	3300,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	280,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	4400,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	400,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	3300,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4200,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    60,         /* GF (gain of frication source in dB) */
    53,         /* GH (gain of aspiration source in dB) */
	60,			/* GV (gain of voicing source in dB ) */
	62,			/* GN (gain of input to cascade nasal pole pair in dB) */
	67,			/* G1 (gain of input to cascade 5th formant in dB) */
	50,			/* G2 (gain of input to cascade 4th formant in dB) */
	54,     	/* G3 (gain of input to cascade 3rd formant in dB) */
	62,			/* G4 (gain of input to cascade 2nd formant in dB) */
	57,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	10,			/* FT (f0-dependent spectral tilt in % of max) */
	5,			/* BF (baseline f0 fall in Hz) */
	0,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	95,			/* QU (quickness of larynx gestures in % of max quickness) */
	20,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	22,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	500,        /* AGO */
	1000,		/*agvo */
	2300,		/*aguo */
	1000,		/*unvow*/
	0,	//chink area 
	50, //open quotient
	9950, //gp
	850, //gz
	1, //OS Gain
	MATT,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	80,//HL_B1m;
	90,//HL_B2m;
	150,//HL_B3m;
	230,//HL_B4m;
	340,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	400,//HL_B4F;
	400,//HL_B5F;
	4800,//HL_F6;
	1200,//HL_B6F;
	20,//stress_step;
	80,//unstress_pressure;
	100,//stress_pressure;
	900,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	3,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	540,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	3,//diplo_step;
	400,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	60,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4500 //HL_F5

};	// Matt


//hlsyn
/* Frail Frank */
const short lynn[SPDEF] =
{
//really ken
	1,			/* SEX = m */
	30,			/* SM (smoothness in %, actually spectral tilt offset) */
	120,		/* AS (assertiveness, degree of final f0 fall in % */
	125,		/* AP (Average pitch in Hz) */
	100,		/* PR (pitch range in percent of Paul's range) */
	50,			/* BR (breathiness in dB) */
	20,			/* RI (was 45,Richness in %, actually nopen is 100-RI % of T0) */
	10,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	3400,		/* F4 (was 3350, frequency in Hz of cascade 4th formant = F4*100/HS) */
	260,		/* B4 (was 230, bandwidth in Hz of cascade 4th formant) */
	4300,		/* F5 (was 3900, frequency in Hz of cascade 5th formant = F5*100/HS) */
	280,		/* B5 (was 180, bandwidth in Hz of cascaded 5th formant) */
	3400,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4800,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    60,         /* GF (gain of frication source in dB) */
    50,         /* GH (gain of aspiration source in dB) */
	60,			/* GV (gain of voicing source in dB ) */
	71,			/* GN (gain of input to cascade nasal pole pair in dB) */
	71,			/* G1 (gain of input to cascade 5th formant in dB) */
	65,			/* G2 (gain of input to cascade 4th formant in dB) */
	65,			/* G3 (gain of input to cascade 3rd formant in dB) */
	66, 		/* G4 (gain of input to cascade 2nd formant in dB) */
	70, 		/* LO (Loudness, gain input to cascade 1st formant in dB) */
	73,			/* FT (f0-dependent spectral tilt in % of max) */
	18,			/* BF (baseline f0 fall in Hz) */
	0,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	40,			/* QU (quickness of larynx gestures in % of max quickness) */
	18,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	25,			/* SR (height of max stress-rise impulse of f0 in Hz, was 32) */
	400,        /* AGO */
	1000,		/*agvo */
	2100,		/*aguo */
	700,		/*unvow*/
	0,	//chink area 
	50, //open quotient
	23251,
	2351,
	1, //OS Gain
	PAUL,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	70,//HL_B1m;
	110,//HL_B2m;
	160,//HL_B3m;
	180,//HL_B4m;
	200,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	260,//HL_B4F;
	270,//HL_B5F;
	4800,//HL_F6;
	600,//HL_B6F;
	30,//stress_step;
	80,//unstress_pressure;
	200,//stress_pressure;
	800,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	10,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	600,//HL_acd_f1_break;
	42,//Ka;
	-100,//f2_ref_scale;
	-150,//f3_ref_scale;
	1,//diplo_step;
	200,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	150,//tune_param_1; //lift for a stress vowel
	250,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	100,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4500 //HL_F5

};	// Lynn


/* Kit the Kid */
const short jackie[SPDEF] =
{
	FEMALE,		/* SEX = f */
	50,			/* SM (smoothness in %, actually spectral tilt offset) */
	65,			/* AS (assertiveness, degree of final f0 fall in % */
	285,		/* AP (Average pitch in Hz) */
	120,		/* PR (pitch range in percent of Paul's range) */
	0,			/* BR (breathiness in dB) */
	40,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	10,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	96,			/* HS (head size, in percent relative to normal for SEX) */
	4700,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	500,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	ZAPF,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	ZAPB,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4450,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4800,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
	60,			/* GF (gain of frication source in dB) */
	55,			/* GH (gain of aspiration source in dB) */
	60,			/* GV (gain of voicing source in dB ) */
	68,			/* GN (gain of input to cascade nasal pole pair in dB) */
	65,			/* G1 (gain of input to cascade 5th formant in dB) */
	69,			/* G2 (gain of input to cascade 4th formant in dB) */
	60,			/* G3 (gain of input to cascade 3rd formant in dB) */
	55,			/* G4 (gain of input to cascade 2nd formant in dB) */
	65,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	75,			/* FT (f0-dependent spectral tilt in % of max) */
	10,			/* BF (baseline f0 fall in Hz) */
	75,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	50,			/* QU (quickness of larynx gestures in % of max quickness) */
	20,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	20,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	300,        /* AGO */
	1000,		/*agvo */
	2100,		/*aguo */
	700,		/*unvow*/
	0,	//chink area 
	50, //open quotient
	9500, //gp
	1600, //gz
	1, //OS Gain
	JACKIE,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	80,//HL_B1m;
	90,//HL_B2m;
	150,//HL_B3m;
	230,//HL_B4m;
	340,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	400,//HL_B4F;
	400,//HL_B5F;
	4800,//HL_F6;
	1200,//HL_B6F;
	20,//stress_step;
	80,//unstress_pressure;
	100,//stress_pressure;
	900,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	3,//endofphrase_spread;
	5,//HL_num_formants;
	1280,//HL_f1_hi_shift;
	650,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	3,//diplo_step;
	400,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	60,//str_vow_before_final;
	300,//agm; // Modal glottal area
	0,//KTL
	4500 //HL_F5

};	// Jackie


const short mary[SPDEF] =
{
	FEMALE,		/* SEX = f */
	60,			/* SM (smoothness in %, actually spectral tilt offset) */
	100,		/* AS (assertiveness, degree of final f0 fall in % */
	240,		/* AP (Average pitch in Hz) */
	100,		/* PR (pitch range in percent of Paul's range) */
	0,			/* BR (breathiness in dB) */
	70,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	5,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	4150,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	260,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	ZAPF,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	ZAPB,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4300,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4900,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    60,         /* GF (gain of frication source in dB) */
    55,         /* GH (gain of aspiration source in dB) */
	60,			/* GV (gain of voicing source in dB ) */
	70,			/* GN (gain of input to cascade  pole pair in dB) */
	69,			/* G1 (gain of input to cascade 5th formant in dB) */
	73,			/* G2 (gain of input to cascade 4th formant in dB) */
    55,         /* G3 (gain of input to cascade 3rd formant in dB) */
	59,			/* G4 (gain of input to cascade 2nd formant in dB) */
	66,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	60,			/* FT (f0-dependent spectral tilt in % of max) */
	18,			/* BF (baseline f0 fall in Hz) */
	50,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	30,			/* QU (quickness of larynx gestures in % of max quickness) */
	1,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	32,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	300,        /* AGO */
	1000,		/*agvo */
	1500,		/*aguo */
	700,		/*unvow*/
	0,	//chink area 
	55, //open quotient
	22200,
	1100,
	1, //OS Gain
	MARY,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	80,//HL_B1m;
	90,//HL_B2m;
	150,//HL_B3m;
	230,//HL_B4m;
	340,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	400,//HL_B4F;
	400,//HL_B5F;
	4800,//HL_F6;
	1200,//HL_B6F;
	20,//stress_step;
	80,//unstress_pressure;
	100,//stress_pressure;
	900,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	3,//endofphrase_spread;
	5,//HL_num_formants;
	1280,//HL_f1_hi_shift;
	650,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	3,//diplo_step;
	400,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	60,//str_vow_before_final;
	300,//agm; // Modal glottal area
	0,//KTL
	4500 //HL_F5

};	// Mary


/* Rough Rita */
//really sueb
const short charline[SPDEF] =
{
	FEMALE,		/* SEX = f */
	40,			/* SM (smoothness in %, actually spectral tilt offset) */
	130,		/* AS (assertiveness, degree of final f0 fall in % */
	190,		/* AP (Average pitch in Hz) */
	120,		/* PR (pitch range in percent of Paul's range) */
	53,			/* BR (breathiness in dB) */
	40,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	0,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	4207,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	280,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	ZAPF,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	ZAPB,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4140,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4900,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
    55,         /* GF (gain of frication source in dB) */
    50,         /* GH (gain of aspiration source in dB) */
	55,			/* GV (gain of voicing source in dB ) */
	60,			/* GN (gain of input to cascade nasal pole pair in dB) */
	66,			/* G1 (gain of input to cascade 5th formant in dB) */
	65,			/* G2 (gain of input to cascade 4th formant in dB) */
	60,			/* G3 (gain of input to cascade 3rd formant in dB) */
	65,			/* G4 (gain of input to cascade 2nd formant in dB) */
	63,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	30,			/* FT (f0-dependent spectral tilt in % of max) */
	10,			/* BF (baseline f0 fall in Hz) */
	60,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	45,			/* QU (quickness of larynx gestures in % of max quickness) */
	5,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	30,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	350,        /* AGO */
	1000,		/*agvo */
	1500,		/*aguo */
	600,		/*unvow*/
	0,	//chink area 
	61, //open quotient
	17520,
	950,
	1, //OS Gain
	CHARLINE,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	80,//HL_B1m;
	90,//HL_B2m;
	150,//HL_B3m;
	230,//HL_B4m;
	340,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	400,//HL_B4F;
	400,//HL_B5F;
	4800,//HL_F6;
	1200,//HL_B6F;
	20,//stress_step;
	80,//unstress_pressure;
	100,//stress_pressure;
	900,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	3,//endofphrase_spread;
	5,//HL_num_formants;
	1280,//HL_f1_hi_shift;
	650,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	3,//diplo_step;
	400,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	60,//str_vow_before_final;
	300,//agm; // Modal glottal area
	0,//KTL
	4500 //HL_F5

};	// Charline



/* Copied from Whispery Wendy ? */
const short tom[SPDEF] =
{
	FEMALE,		/* SEX = m */
	70,			/* SM (smoothness in %, actually spectral tilt offset) */
	50,	   		/* AS (assertiveness, degree of final f0 fall in % */
	200,		/* AP (Average pitch in Hz) */
	80,			/* PR (pitch range in percent of Paul's range) */
	5,			/* BR (breathiness in dB) */
	20,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	10,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	105,		/* HS (head size, in percent relative to normal for SEX) */
	4200,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	400,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	4800,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	600,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4200,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	4800,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
	/* complaints that whisper voice sometimes overload-dropped source  2db for Wendy doctor and frank */
	59,			/* GF (gain of frication source in dB) */
	55,			/* GH (gain of aspiration source in dB) */
	59,			/* GV (gain of voicing source in dB ) */
	71,			/* GN (gain of input to cascade nasal pole pair in dB) */
	69,			/* G1 (gain of input to cascade 5th formant in dB) */
	78,			/* G2 (gain of input to cascade 4th formant in dB) */
	56,			/* G3 (gain of input to cascade 3rd formant in dB) */
	57,			/* G4 (gain of input to cascade 2nd formant in dB) */
	68,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	100,		/* FT (f0-dependent spectral tilt in % of max) */
	10,			/* BF (baseline f0 fall in Hz) */
	80,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	20,			/* QU (quickness of larynx gestures in % of max quickness) */
	18,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	22,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	750,        /* AGO */
	1000,		/*agvo */
	1800,		/*aguo */
	700,		/*unvow*/
	0,	//chink area 
	75, //open quotient
	16020,
	900,
	1, //OS Gain
	TOM,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	80,//HL_B1m;
	90,//HL_B2m;
	150,//HL_B3m;
	230,//HL_B4m;
	340,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	400,//HL_B4F;
	400,//HL_B5F;
	4800,//HL_F6;
	1200,//HL_B6F;
	20,//stress_step;
	80,//unstress_pressure;
	100,//stress_pressure;
	900,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	3,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	540,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	3,//diplo_step;
	400,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	60,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4500 //HL_F5

};	// Tom


const short ivan[SPDEF] =
{
	MALE,		/* SEX = m */
	65,			/* SM (smoothness in %, actually spectral tilt offset) */
	100,		/* AS (assertiveness, degree of final f0 fall in % */
	110,		/* AP (Average pitch in Hz) */
	100,		/* PR (pitch range in percent of Paul's range) */
	30,			/* BR (breathiness in dB) */
	20,			/* RI (Richness in %, actually nopen is 100-RI % of T0) */
	10,			/* NF (additional fixed number of samples in nopen) */
	0,			/* LA (laryngealization, in percent) */
	100,		/* HS (head size, in percent relative to normal for SEX) */
	3500,		/* F4 (frequency in Hz of cascade 4th formant = F4*100/HS) */
	240,		/* B4 (bandwidth in Hz of cascade 4th formant) */
	3800,		/* F5 (frequency in Hz of cascade 5th formant = F5*100/HS) */
	180,		/* B5 (bandwidth in Hz of cascaded 5th formant) */
	4100,		/* F7 (frequency in Hz of parallel 4th formant = F7) */
	ZAPF,		/* F8 (frequency in Hz of parallel 5th formant = F8) */
	66,			/* GF (gain of frication source in dB) */
	53,			/* GH (gain of aspiration source in dB) */
	66,			/* GV (gain of voicing source in dB ) */
	71,			/* GN (gain of input to cascade nasal pole pair in dB) */
	75,			/* G1 (gain of input to cascade 5th formant in dB) */
	65,			/* G2 (gain of input to cascade 4th formant in dB) */
	57,         /* G3 (gain of input to cascade 3rd formant in dB) */
	62,			/* G4 (gain of input to cascade 2nd formant in dB) */
	72,			/* LO (Loudness, gain input to cascade 1st formant in dB) */
	100,		/* FT (f0-dependent spectral tilt in % of max) */
	9,			/* BF (baseline f0 fall in Hz) */
	70,			/* LX (lax folds adjacent to voiceless sound -> breathiness) */
	50,			/* QU (quickness of larynx gestures in % of max quickness) */
	10,			/* HR (hat-pattern fundamental frequency rise in Hz) */
	22,			/* SR (height of max stress-rise impulse of f0 in Hz) */
	400,        /* AGO */
	1000,		/*agvo */
	1200,		/*aguo */
	700,		/*unvow*/
	0,			//chink area 
	50,			//open quotient
	11100,
	500,
	1, //OS Gain
	IVAN,// NAME
	0,//new5
	0,//new6
	438,//endofphrase_spread_target
	80,//HL_B1m;
	90,//HL_B2m;
	150,//HL_B3m;
	230,//HL_B4m;
	340,//HL_B5m;
	250,//HL_B2F;
	320,//HL_B3F;
	400,//HL_B4F;
	400,//HL_B5F;
	4800,//HL_F6;
	1200,//HL_B6F;
	20,//stress_step;
	80,//unstress_pressure;
	100,//stress_pressure;
	900,//nom_sub_pressure;
	100,//nom_fricative_opening;
	0,//nom_glot_stop_area;
	1,//vot_speed;
	3,//endofphrase_spread;
	5,//HL_num_formants;
	1180,//HL_f1_hi_shift;
	540,//HL_acd_f1_break;
	30,//Ka;
	0,//f2_ref_scale;
	0,//f3_ref_scale;
	3,//diplo_step;
	400,//endpoint_below_ap;
	100,//endpoint_mult_stress;
	60,//tune_param_1; //lift for a stress vowel
	60,//tune_param_2; //lift with a stressed vowel following a stop
	60,//init_st_no_aspir;
	60,//str_vow_before_final;
	400,//agm; // Modal glottal area
	0,//KTL
	4500 //HL_F5

};	// Ivan


/****************************end of phvdef1.c**********************************/
