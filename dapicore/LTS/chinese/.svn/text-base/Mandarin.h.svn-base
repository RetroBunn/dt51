/*H_HEADER_FILE***************************************************************
FILE			: Mandarin.h
DESC			: 
TABS			: 4
OWNER			: 
DATE CREATED: 13 Feb 2006

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER******************************************************************/
#ifndef	MANDARIN_H
#define	MANDARIN_H

#define DEFAULT_TONE '5'
#define QTAF0MODEL

typedef struct _PinyinAscii
{
	char sPinyin[10];
	char sAscii[10];
}PINYIN_ASCII;

#define MAXRULEBUFLEN 100       
#define MAXRULEALLBUFFERLENGTH (6*MAXRULEBUFLEN)          /* do not change the 6 */

#include "MandQTAmodel.h"


typedef struct _tagMandarinSyll
{
    char syll[6];		// syllable phonemes
    int  tone;			// tone value	1 - 5, 0 for punctuation
 //   int  toneseq;		// tone sequence
    int  durscale;		// 
    int  ninterval;
    short startphoneme;         // index of phoneme in the phrase where the interval starts
    short endphoneme;           // and ends. 
//	short nframes;              // number of frames 
//  short controlphonemes;    // number of control phonemes that were sent during this syllable.
//  MandF0ControlInterval   *firstinterval;
    struct _tagMandarinSyll *pNext;
}MandSyll;

#define MAND_PHRASE_F0_CONTOUR 

#ifdef  MAND_PHRASE_F0_CONTOUR 
//reset_mand_phrase_f0(&F0phraseGenerator);
//add_time_to_mand_phrase_f0(&F0phraseGenerator,dt, frames);
//start_mand_phrase_f0(&F0phraseGenerator);

typedef struct _f0_mand_phrase_contour{
    double T;
    double time;
	double phraseduration;
	int    phraseframes;
    double T1,T2;
    double alf,bet;
    double un,un1,xn,xn1,yn,yn1;
    double scale;
    double ramp, gamma;
} mandf0phrasegen;

#endif 

typedef struct _tagMandarinF0Machine
{
  // state information used during computation of control regimes:
    short is_on;
    float lastendtime;
    float lastc, lastd;         // coefficients c and d for next interval
    float a,b,c,d;              // coefficients in current interval
    
    // state information used while calculating F0 contour
    float  ctime;                // within current interval.
    float  lastF0goal;
	float  speedtau;            // related to speaking rate.
    short  framesleft;          // set to number of frames, then counted down
    short  lastF0;
	short  freesyll;
    short  currentsyll;
    short  currentinterval;    
    short  phoneme_in_phrase;
    short  numsyllables;         // total number of syllables in phrase
    short  numintervals;         // total number of subintervals in phrase
    short  numphonemes;
    short  numcontrolphones;
#ifdef QTAF0MODEL
	MandF0filter F0filt;
#endif
#ifdef  MAND_PHRASE_F0_CONTOUR 
    mandf0phrasegen F0phraseGenerator;
#endif
    MandSyll                   **Mandsylls;           /* pointer array */
    MandF0ControlInterval	 *Mandintervals;  /* data array of structures */
} MandF0Machine;


// Tone sequence definitions
// See - http://hctv.humnet.ucla.edu/departments/linguistics/VowelsandConsonants/vowels/chapter2/chinese/recording2.1.html
/*
There are four lexical tones in Mandarin Chinese. They are
generally described as 55, 35, 214, and 51 in 5-point scale
system [1]. Among the four tones tone2 and tone3 are the
most likely to be confused. Previous studies on perceptual
cues of tone2 and tone3 discrimination show unanimously
that the position of the turning point and the range of the
falling part of the F0 contour are most crucial and reliable
[2,3].
 */
// map from previous:
// 1 =>1;  2 => 2;  3 => 3;  4 => 6;  5 => 7
// 6 and 7 are added.
#define TONESEQ1 0x0066			 
#define TONESEQ2 0x0546			 
#define TONESEQ3 0x0213		 
#define TONESEQ4 0x0071		 
#define TONESEQ5 0x0022
#define TONESEQ_DEF 0x0000

#define TONESEQ1a 0x0043
#define TONESEQ2a 0x0035
#define TONESEQ3a 0x0033
#define TONESEQ4a 0x0053
#define TONESEQ4b 0x0041
#define TONESEQ4c 0x0012
#define TONESEQ5a 0x0021
#define TONESEQ5b 0x0323

#define TONESEQ_DEF 0x0000
 
#define MAX_PINYIN_PHONEMES	256

// These defines need to match the definitions in ch_phon.tab
#define MANDARIN_CONTROL_PHONES "~=`'\"/\\<-*# ();:,.?!+^&>"
#define MANDARIN_PHONES	"_iUeEAI2Xu53oO4a678mnNpbtdkgfsSrxhRywlczqjCZKJW^9"


// API from Pinyin2Ascii.c
extern int ConvertPinyinStr2Phonemes(char *sPinyinStr, char *sPhonemeStr, int nMaxLen);

/* definitions for the Mandarin F0 machine */
typedef enum {
    MFZ_INIT,
    MFZ_INITSYLLABLES,
    MFZ_CLEANUP,
    MFZ_STARTSYLLABLE,
    MFZ_PAUSE_RESET,
    MFZ_PUT_PHONEME,
	MFZ_PUTSYLLABLE,
    MFZ_PUT_CNTR_PHONEME,
	MFZ_MAKE_INTERVAL,
    MFZ_F0TARGET_TOWARDS,
    MFZ_F0TARGET_UP,
    MFZ_F0TARGET_DOWN,
    MFZ_GETDURATIONS,
	MFZ_FINISHPHRASE,
    MFZ_NEWCOEFFIENTS,
    MFZ_FRAMETICK,
    MFZ_GET_F0,
    MFZ_PRINT_INTERVALS,
    MFZ_PRINT_SYLLABLES
} MFZ_Code;

#define NOT_AN_INDEX (-1)
#define VOID_NULL_PTR ((void *) NULL)

#define MAXMANDF0INTERVALS 120
#define MAXMANDF0SYLLABLES 120

#endif

