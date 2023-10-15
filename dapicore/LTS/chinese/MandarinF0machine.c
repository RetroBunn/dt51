/*C_HEADER_FILE****************************************************************
FILE			:	MandarinF0Machine.c
DESC			:	A new stab at F0 control for Mandarin
TABS			:	4
OWNER			:	reiner@fonix.com (at least as long as I know what this does.:-)
DATE CREATED:	

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

  See function mandarin_tone_process() for table of puntuation durations
  See function mandarin_syllables() for syllable durations

*END_HEADER*******************************************************************/


/* Include files and defines. I am using the same header that goes into pinyinparse.c 
   Structures in Mandarin.h are changed accordingly, using the same structure names. */

#include "port.h"
//#include <string.h> //moved to port.h for all platform mlt

#define QTAF0MODEL

#define IN_DECTALK
#ifdef IN_DECTALK
#include "dectalkf.h"
#include "port.h"
#include "ls_def.h"
#include "ls_defs.h"
#include "ls_data.h"
#include "ph_def.h"
#include "tts.h"

#include "Mandarin.h"
#include "mandarinprot.h"
#endif 

#ifndef IN_DECTALK
#define userulesdebug
#define userules_is_main
#endif

#ifdef userulesdebug
#define debug_printf(fmt,args...) printf(fmt,## args)
#else
#ifdef _UNIX_LIKE_
#define debug_printf(fmt,args...)
#else
#define debug_printf(fmt,args)
#endif
#endif

/* Assumption: Syllable duration roughly 200 ms, framelength 6.40 ms
   so we have: about 32 frames per syllable. (200/6.40) 
   Thus normalization factor: 1/32 
   Will have to be changed to be varied at runtime.
   For the frequency similarly, I put in a factor of
   10 * 110 Hz and calculate with normalized frequencies
   for F0.
*/
    

// MANDF0MACHINE is defined (or not) in mandarinprot.h

#ifdef  MANDF0MACHINE
#define QTAF0MODEL
#define NORMALIZEFREQUENCY 10

/* debug flags for output to analyse with Matlab or visually */
// #define DEBUGMANDF0MACHINE
//#define DEBUGDETAIL
 
#define MANDF0FILEOPEN 1
#define MANDF0FILECLOSE 2
#define MANDF0PRINT 0
#endif


#ifdef DEBUGMANDF0MACHINE
//extern int inh_timing(LPTTS_HANDLE_T phTTS, int phone);
//extern int min_timing(LPTTS_HANDLE_T phTTS, int phone);

static FILE *mand_f0_fid=(FILE *) NULL;
char   mandf0printbuff[256];
static int    stopoutput;
static int    debugframecounter;

/* debug routine for printing stuff to file */

void  mandf0_print(MandF0Machine *M, int what, char *s)
{
	switch (what)
	{
	case 1:
		mand_f0_fid = FNX_FOPEN("matlaboutput.m","w");
		stopoutput = 0;
		break;
	case 2:	
		if (mand_f0_fid) FNX_FCLOSE(mand_f0_fid);
		break;	
    case 3:
		stopoutput = 1;
		break;
	case 4:
		stopoutput = 0;
		break;

	default:
		if (mand_f0_fid && !stopoutput) fprintf(mand_f0_fid,"%s",s);
		break;
	}
}
	
#if defined QTAF0MODEL && defined DEBUGMANDF0MACHINE
void  print_mand_intervals(MandF0Machine *M)
{
    MandF0ControlInterval *I;
    int n;

    for (n=0;n<M->numintervals; n++)
    {
	I = &(M->Mandintervals[n]);

	mandf0_print(M,0,mandf0printbuff);
    FNX_SPRINTF(mandf0printbuff," dur=%7.3f frms=%5i a=%7.3f b=%7.3f c=%7.3f d=%7.3f\n",I->pdur,I->nframes, I->a, I->b, I->c, I->d);
	mandf0_print(M,0,mandf0printbuff);
    }
}
#endif
#endif	


/* Balistic F0 contour underlay */

#define MAND_PHRASE_F0_CONTOUR 

#ifdef  MAND_PHRASE_F0_CONTOUR 
//reset_mand_phrase_f0(&F0phraseGenerator);
//add_time_to_mand_phrase_f0(&F0phraseGenerator,dt, frames);
//start_mand_phrase_f0(&F0phraseGenerator);

/*
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

static mandf0phrasegen F0phraseGenerator;
*/

#define LOGONEQUARTER -1.38629436111989
#define LOGONETHIRD   -1.09861228866811
#define LOGONEHALF    -0.69314718055995


void reset_mand_phrase_f0(mandf0phrasegen *m)
{
	m->phraseduration =0.0;
	m->phraseframes = 0;

    m->T = 0.0064;    

    m->time=0.0;
    m->un = 0.0;
    m->un1 = 0.0;
    m->xn = 0.0;
    m->xn1 = 0.0;
    m->yn = 0.0;
    m->yn1 = 0.0;
}

void add_time_to_mand_phrase_f0(mandf0phrasegen *m, double dt, int frames)
{
	m->phraseduration += dt;
	m->phraseframes += frames;
}

void start_mand_phrase_f0(mandf0phrasegen *m)
{
    double dur, h, htime,al;

/* reset part: */
    m->ramp = 16.0;

/* duration of phrase */
    dur = m->phraseduration;

/*  ramping up duration */
    m->T1 = 2.0/m->ramp;

/* decay time and decay rate */    
    htime = 0.85*dur;
    h = 0.5 * LOGONETHIRD * m->T / htime; 
    m->gamma = (1.0+h)/(1.0-h);   /* aprox exp()*/
    m->T2 = htime;

/* balistic parameters */
    al = 8.0;
    m->alf = m->T/(2.0+al*m->T);
    m->bet = (2.0-al*m->T)/(2.0+al*m->T);
    m->scale = 4.0/m->T;                 
}

double update_mand_phrase_f0(mandf0phrasegen *m)
{
    double f0delta;

	if (m->phraseduration < 1.5) return (0.0);

    m->time += m->T;
    
    if (m->time<m->T2) m->un = m->un*m->gamma;
    if (m->time<m->T1) m->un = m->ramp*m->time;
    if (m->time>m->T2) m->un = 0.75*m->un1 - 0.25;

    m->xn = m->alf*(m->un+m->un1) + m->bet*m->xn1;
    m->yn = m->alf*(m->xn+m->xn1) + m->bet*m->yn1;
    m->yn1=m->yn;
    m->xn1=m->xn;
    m->un1=m->un;
    f0delta = m->scale * m->yn;

    return (f0delta);
}

#endif 
/* endif: Balistic F0 phrase component */




/* forget about all this hideous scaling for now. A second is a second is a second */
#define AVERAGESYLLABLE 0.192 

#ifndef FRAMEDURATION
#define FRAMEDURATION 0.00640
#endif
#define MSECPERFRAME 6.40
#define SYLLABLESPERSEC (1.0/AVERAGESYLLABLE)

/* FRAMES PER SYLL ABOUT 30 
   SYLLABLES PER FRAME, WELL.
   */
#define FRAMESPERSYLL (AVERAGESYLLABLE/FRAMEDURATION) 
#define SYLLSPERFRAME (FRAMEDURATION/AVERAGESYLLABLE)  
#define MILLISECONDS  0.001
#define FRAMESPERSECOND (1000.0/6.40)
#define FRAMESPERMILLISECOND (1.0/6.40)



int  F0_ex_machina(MandF0Machine *M,  int phoneno, int thephone,int phdur, int f0ref)
{
    float fzero;
	int tone;
	double u;
	MandF0ControlInterval *I;
    M->ctime = M->ctime + FRAMEDURATION;
#ifdef DEBUGMANDF0MACHINE
	if (debugframecounter == 0)
	{
	mandf0_print(M,0,"ctldata=[ ...\n");
	}
	debugframecounter += 1;
#endif

    M->framesleft -= 1;
    if (M->framesleft <= 0) 
    {
		if (M->currentinterval < (M->numintervals-1)) 
		{
			M->currentinterval += 1;
		}
		else 
		{
#ifdef DEBUGMANDF0MACHINE
			mandf0_print(M,0,"];\n");
			mandf0_print(M,3,0);
#endif
			return M->lastF0;
		}
		I = &(M->Mandintervals[M->currentinterval]);
		M->a = I->a;
		M->b = I->b;
		M->c = I->c;
		M->d = I->d;
		M->F0filt.c1 = I->c1;
		M->F0filt.c2 = I->c2;
		M->F0filt.gamma = I->gamma;
		M->F0filt.lambda = (I->omega*I->omega);  /* Aha: That was the fudge factor now it makes sense as characteristic frequency */
		M->framesleft = I->nframes;
		M->ctime = 0.0;
    }

	/* note: c is quadratic coefficient, a linear, and b offset */
	//u = (M->c * M->ctime + M->a) * M->ctime + M->b  + f0ref;  /* ramp plus offset control */
     
	u = ((M->a * M->ctime + M->b)*M->ctime + M->c)*M->ctime + M->d + f0ref;


	fzero = shift_f0_filter_state(&(M->F0filt),u);
//	fzero = 100.0 + M->ctime*40.0;

//	fzero = u;

#ifdef  MAND_PHRASE_F0_CONTOUR 
//	fzero += update_mand_phrase_f0(&(M->F0phraseGenerator));
//	fzero = 100+10*update_mand_phrase_f0(&(M->F0phraseGenerator));
#endif 

    M->lastF0 = ((int) (fzero*10.0)); 
 

#ifdef DEBUGMANDF0MACHINE
	if (M->currentinterval <= (M->numintervals))
	{
		I = &(M->Mandintervals[M->currentinterval]);
		tone = I->tone;
//		FNX_SPRINTF(mandf0printbuff,"I=%5i phoneNo=%5i Phone=%5i phdur=%6i fref=%6i  %5i %10.4f %5i %10.5f %10.5f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %3i\n",
//		M->currentinterval,phoneno,thephone,phdur,f0ref,I->nframes,I->pdur, M->framesleft,M->ctime, fzero, u, M->a,M->b,M->c,I->omega,I->damp,tone);

		FNX_SPRINTF(mandf0printbuff,"%5i %5i %5i %6i %6i %5i %10.4f %5i %10.5f %10.5f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %3i\n",
		M->currentinterval,phoneno,thephone,phdur,f0ref,I->nframes,I->pdur, M->framesleft,M->ctime, fzero, u, M->a,M->b,M->c,I->omega,I->damp,tone);
        mandf0_print(M,0,mandf0printbuff);
	}
	else
	{
//		mandf0_print(M,0,"];\n");
		mandf0_print(M,MANDF0FILECLOSE, NULL);
	}
#endif

	/* for now let's hard code it since I don't want to 
	    CRASH EVERY TIME */
	if (M->lastF0<500) M->lastF0 = 500;
	if (M->lastF0>2000) M->lastF0 = 2000;
    return M->lastF0;
}



//F0_ex_machina(MandF0Machine *M,  int phoneno, int thephone,int phdur, int f0ref)



#ifdef DEBUGMANDF0MACHINE
#ifdef DEBUGDETAIL	
void look_at_allowdurs(LPTTS_HANDLE_T phTTS,MandF0Machine *M)
{
	int k;
	PDPH_T  pDph_t = phTTS->pPHThreadData;

	for (k=0;k<10;k++)
	{
	FNX_SPRINTF(mandf0printbuff,"allodurs[%4i]=%5i\n",k,pDph_t->allodurs[k]);
    mandf0_print(M,0,mandf0printbuff);
	}
}
#endif
#endif

/*
  Loop thought the intervals and define the polynomical coefficients for 
  each interval.
*/


void   set_mandctl_values(MandF0Machine *M)
{
    int n;

    MandF0ControlInterval *I;

    for (n=0;n<M->numintervals; n++)
    {
	I = &(M->Mandintervals[n]);	
	make_digital_QTA_parameters(I);
	}
	    
    M->currentinterval=-1;
	M->framesleft=0;  
//	reset_mand_f0_filter(&M->F0filt, M->lastF0 * 0.1);
#ifdef DEBUGMANDF0MACHINE
	debugframecounter = 0;
#endif

}
 
void cranck_up_f0_iteration(LPTTS_HANDLE_T phTTS,MandF0Machine *M, int ntimes, int f0ref)
{
	int k;
	int f0;
	double initf0;
	MandF0ControlInterval *I;	

	if (!M) return;
	if (M->is_on<2) return;

	/* start first phonation at the exact pitch where it would be 
	   starting if it was forming the tone of the first syllable. */
	initf0 = (double) f0ref;

	if (M->numintervals>0)
	{
		/* what's this?-  i reprogram the first 
			interval which is going to be for a few frames or
			128 ms such that, when the first syllable is synthesized
			the F0 contour is closer to the goal of the first syllable.
			Better would be: A proper initial attack method 
		*/
		I = &(M->Mandintervals[1]);	
		I->omega = I->omega*2.0;

		initf0 = I->d ;
		I = &(M->Mandintervals[0]); 
		I->d = initf0+f0ref;    // dectalk doesn't know when starting.
		initf0 += f0ref;
		I->a = 0.0;
		I->b = 0.0;
		I->c = 0.0;  

	}

	set_mandctl_values(M);   
	reset_mand_f0_filter(&M->F0filt,initf0); 

	for (k=0;k<ntimes;k++)
	{
		f0=F0_ex_machina(M,0 ,666 ,666,0);
	}

	I->d = I->d - f0ref;
	M->d = I->d;
}

void initialize_intervals(MandF0ControlInterval *I, int n)
{
    int i;
    for (i=0;i<n;i++)
    {
	I[i].a=0.0;
	I[i].b=0.0;
	I[i].c=0.0;
	I[i].d=0.0;
	I[i].omega=10.0;
	I[i].damp=1.5;
	I[i].nframes=0;
	I[i].parentsyll=NOT_AN_INDEX;
	I[i].tone =0;
    }
}


/* subroutine to be called every time we start a new 
   phrase. It basically cleans up from the last time 
   a phrase was formed. */


void reset_MandF0Machine(LPTTS_HANDLE_T phTTS, MandF0Machine *M, int flag, int basef0)   
{

	M->freesyll = 0;

    M->lastendtime = 0.0;
    M->lastc = 0.0;
    M->lastd = 1.0;
    M->a = M->b = M->c = 0.0;
    M->d = 1.0;            // initial F0 
    
    M->framesleft=0;          // set to number of frames, then counted down
    M->currentsyll=0;
    M->currentinterval=0;    
    M->phoneme_in_phrase=0;
    M->numsyllables=0;         // total number of syllables in phrase
	initialize_intervals(M->Mandintervals, M->numintervals);
    M->numintervals=0;         // total number of subintervals in phrase
    M->numphonemes=0;
    M->numcontrolphones=0;

    M->lastF0goal = basef0*NORMALIZEFREQUENCY;

	if (M->is_on<1) return;

//	PKSD_T                  pKsd_t = phTTS->pKernelShareData;

/* This stuff does not work: can't access these data */
	if (phTTS->pKernelShareData)
	{
		if (phTTS->pKernelShareData->sprate >= 0)
		{
			M->speedtau = 180.0/((float) phTTS->pKernelShareData->sprate);
		}
		else
		{
			M->speedtau = 1.0;
		}
	}


#ifdef QTAF0MODEL
	if (flag) reset_mand_f0_filter(&M->F0filt, (double ) basef0);
#endif

#ifdef DEBUGMANDF0MACHINE
	mandf0_print(M,4,0);
	FNX_SPRINTF(mandf0printbuff,"tosay ={...\n");
    mandf0_print(M,0,mandf0printbuff);
#endif 


    M->is_on = 2;
}


/* Call this once to allocated all the memory and initialize
   structures */

void init_MandF0Machine(MandF0Machine *M, int maxnsyll, int maxnintervals, int speakrate, int basef0)   
{
	int i;

	if (speakrate <= 0) M->speedtau = 1.0;
	else M->speedtau = 205.0/((float) speakrate);

    if (M->is_on > 0) 	return;  /* don't alloc all this stuff twice!! */

/* Note: CALLOC has to go here. We need instead 
   a fixed array to store the syllables.
*/

    M->Mandsylls = (MandSyll **) FNX_CALLOC(maxnsyll, sizeof(MandSyll *)); /* pointer array */
    M->Mandintervals = (MandF0ControlInterval *)  FNX_CALLOC(maxnintervals, sizeof(MandF0ControlInterval));
	for (i=0;i<maxnsyll;i++)
	{
		M->Mandsylls[i]=(MandSyll *) FNX_CALLOC(1,sizeof(MandSyll));
	}
	M->freesyll = 0;
    initialize_intervals(M->Mandintervals, maxnintervals);

    M->lastF0 = 1200;
    M->lastF0goal = basef0*NORMALIZEFREQUENCY;   /* note: This is integrating */
	M->is_on = 1;
	M->speedtau = 1.0;
}

/* call this to clean up the mess (e.g., when the module is no longer used) */

void switch_off_MandF0Machine(MandF0Machine *M)
{
	int i;
    if (M->is_on == 0) return;
	for (i=0;i<MAXMANDF0SYLLABLES;i++)
	{
		if (M->Mandsylls[i]) FNX_FREE(M->Mandsylls[i]);
	}
	
    if (M->Mandsylls) FNX_FREE(M->Mandsylls);
    M->Mandsylls = (MandSyll **) NULL;
    if(M->Mandintervals) FNX_FREE(M->Mandintervals);
    M->Mandintervals = (MandF0ControlInterval *) NULL;
    M->is_on = 0;
}



/* dont' worry about pinyinparse. I will start working on replacing a 
lot of it's functionality, even though that is a little bit of a 
painful process. 
*/

MandF0ControlInterval *gimmy_a_new_interval(MandF0Machine *M)
{	
	MandF0ControlInterval *I;

	if (M->numintervals >= MAXMANDF0INTERVALS) return ((MandF0ControlInterval *) NULL);    
    M->currentinterval = M->numintervals;
    M->numintervals += 1;

    I = &(M->Mandintervals[M->currentinterval]);
    I->a = 0.0;
    I->b = 0.0;
    I->c = 0.0;
    I->d = 0.0;
    I->nframes = 0;     /* not yet known */
 //   I->phonemeindex = M->phoneme_in_phrase;
    I->parentsyll = M->currentsyll;
	I->tone =0;
	return (I);
}
/* 

  The intention of the make_tonal_gestures subroutine is to implement 
  tone gesture targets for the different tones. All calculations are
  done with actual time in seconds but normalized frequency, where 1.0 
  corresponds to the base F0. Later, when it's 
  known which phonemes and how many phonemes are in the syllable, 
  we make a second path and modify the timing. For the F0 goals, I will also
  not care at all about the values given in pinyinparse. It's just too complicated
  trying to merge these two methods together. However, timing changes 
  from pinyinparse.c are taken into consideration as they influence the 
  duration of each phoneme. 
  
*/



#define REFERENCEF0 120

/* Yet another cludge: Modeling of f0 contours of the raising and falling tones (2 and 4) by a
   parabola. 
   Method: Calculation on a normalized interval of duration 1 first.
   The input parameters y0 and y1 represent the F0 offset at the beginning and end 
   of the interval. u0 is the point in time where the slope goes through zero, and f0 
   is an optional offset.
   For example to modelt the 4th tone: y0=20, y1=-30, u0=0.1 means f0 control function
   will start 20 Hz above the reference F0, and end 30 Hz below the reference F0.
   The resulting parabola goes up a little bit until it reaches u0 = 0.1 and then 
   down to the final value -30. (u0 is relative to normalized syllable duration, 
   that is 0.1 means 10 percent of the total duraction). The resulting polynomial
   parameters a b c are then normalized for the actual syllable duration. 
*/

void quadratictone(MandF0ControlInterval *I, double y0, double y1, double u0, double dur, double f0)
{
	double a,b,c;

	a = (y0-y1)/(u0+u0-1.0);
	b = y1-y0-a;
	c = y0;

	I->c = a/(dur*dur);
	I->a = b/dur;
	I->b = c+f0;
	I->pdur = dur;
}

/*
 variablecubictone
 Input and output: A pointer to a control interval.
   Input: (note, changed sequence of paramters)
   dur:      syllable duration in seconds (e.g., 0.18)
   f0:       offset F0 (actually usually set to zero as it gets later added)
   a1,  a2:  F0 targets for minimal and maximal duration at the beginning of the syllable.
  da1, da2:  F0 slope targets for minimal and maximal duration at the beginning of the syllable.
   b1,  b2:  F0 targets for minimal and maximal duration at the end of the syllable.
  db1, db2:  F0 slope targets for minimal and maximal duration at the end of the syllable.
  omega1, omega2: extreme values for of omega for shortest and longest syllable durations.
  damp1 damp2:    extreme values for damping ratio for shortest and longests syllable durations.

  sequence of parameters: All parameters for the shortest syllable followed by all the
  parameters for the longest syllable:

  short:   beginning F0,  ending F0,  beginning slope ,  ending slope ,  omega,   damping
   long:   beginning F0,  ending F0,  beginning slope ,  ending slope ,  omega,   damping

*/

void variablecubictone(MandF0ControlInterval *I, float dur, float f0, 
					   float a1, float b1, float da1, float db1, float omega1, float damp1, 
					   float a2, float b2, float da2, float db2, float omega2, float damp2)
{
	float x, v0,v0d,v1, v1d;
	float a,b,c,d;

	x = (dur-0.08)*2.0;    // normalized duration
	if (x<0.0) x=0.0;      
	if (x>1.0) x=1.0;

	x = 2*x/(x+1);         // convex function : higher slope for small x
	v0 = (1-x)*a1+x*a2;     // interpolations using x as parameter
	v0d = (1-x)*da1+x*da2;
	v1 = (1-x)*b1+x*b2;
	v1d = (1-x)*db1+x*db2;
	v0d = v0d*dur;          // scale slopes (compensate for normalization)
	v1d = v1d*dur;

	d=v0;
	c=v0d;
	a = v0d+v1d+2*v0-2*v1;
	b = v1-v0-v0d-a;

	I->a = a/(dur*dur*dur);   // scale coefficients - undo normalization
	I->b = b/(dur*dur);
	I->c = c/dur;
	I->d = d+f0;
	I->omega = (1-x)*omega1+x*omega2;  // interpolated omega and damping
	I->damp = (1-x)*damp1+x*damp2;
	I->pdur = dur;

}

/* duration is specified in milliseconds not seconds. Since the parameters in 
    QTA model require seconds we multiply with 0.001 */

void  make_tonal_gestures(MandF0Machine *M, int tone, double duration)
{
    MandF0ControlInterval *I;
 
	switch(tone)
	{
	case 0:                           // used for final lengthening
		I = gimmy_a_new_interval(M);
		I->omega = 12.0;        // wild guess.
		I->damp = 2.5;
		I->d = -2.0;
		I->pdur = duration*MILLISECONDS;
		break;

//   Reference F0 is kept as 0.0 since it is added later.
//   Note: variable sequence is changed: 1st line is short syllable
//                                       2nd line is long syllable.
//   Slopes have units of Hz per second. Specify parameters in two lines
//   See description of variablecubictone.
//   for the shortest syllable duration (~50ms) first and then for the longest (~500ms)
//  short:   beginning F0,  ending F0,  beginning slope ,  ending slope ,  omega,   damping
//   long:   beginning F0,  ending F0,  beginning slope ,  ending slope ,  omega,   damping
//   XinChuan: Note these defines:
#define MODIFY_MAND_TONE_REINER
  //#define MODIFY_MAND_TONE_XINCHUAN
#ifdef MODIFY_MAND_TONE_REINER
	case 1:                         // High tone 
		I = gimmy_a_new_interval(M);
		variablecubictone(I, duration*MILLISECONDS, 10.0,
			   28.0, 24.0, 20.0,  -120.0,    35.0,  1.5, 
               28.0, 24.0, 20.0,  -120.0,    15.0,  1.5);
		break;
	
	case 2:                          // raising tone
		I = gimmy_a_new_interval(M);
        variablecubictone(I, duration*MILLISECONDS, 10.0,
	           -25.0,    15.0, -35.0 ,  10.0, 50.0,  1.5,
			   -18.0,    20.0, -35.0 ,  10.0, 25.0,  1.5);
		break;
		
	case 3:                          // LOW falling raising tone
		I = gimmy_a_new_interval(M);
		variablecubictone(I, duration*MILLISECONDS, 10.0,
			 -25.0,   -20.0,  -200.0,  170.0,  50.0, 1.5,
			 -10.0,   -5.0,  -250.0,  210.0,  25.0, 1.5);

		break;
		
	case 4:                           // fast falling tone
		I = gimmy_a_new_interval(M);
		variablecubictone(I, duration*MILLISECONDS, 10.0,
			 10.0,  -25.0,  100.0, -220.0,  50.0,  1.5,
			  7.0,  -30.0,   400.0, -150.0,  20.0,  1.5); 

		break;
#endif

/* beginning of Xinchuan's thus far accepted settings: */
#ifdef MODIFY_MAND_TONE_XINCHUAN

	case 1:                         // High tone 
		I = gimmy_a_new_interval(M);
		variablecubictone(I, duration*MILLISECONDS, 0.0,
			   30.0, 25.0,  10.0,  -10.0,    35.0,  1.5, 
               22.0, 20.0,   5.0,   5.0,    15.0,  1.5);
		break;
	
	case 2:                          // raising tone
		I = gimmy_a_new_interval(M);
        variablecubictone(I, duration*MILLISECONDS, 0.0,
	           -20.0,   50.0,  10.0 , 120.0, 60.0,  1.5,
			   -5.0,    30.0,  -5.0 , 100.0, 25.0,  1.5);
		break;
		
	case 3:                          // LOW falling raising tone
		I = gimmy_a_new_interval(M);
		variablecubictone(I, duration*MILLISECONDS, 0.0,
			-15.0,  -13.0,  -5.0,   5.0,  40.0, 1.5,
			 -5.0,   -6.0,  -25.0,  30.0,  25.0, 1.5);

		break;
		
	case 4:                           // fast falling tone
		I = gimmy_a_new_interval(M);
		variablecubictone(I, duration*MILLISECONDS, 0.0,
			45.0,  -10.0,   0.0, -150.0,  50.0,  1.5,
			30.0,   -5.0,  50.0, -50.0,  20.0,  1.5); 

		break;
#endif    /* XINCHUAN's   */

	case 5:                           // NEUTRAL TONE
		I = gimmy_a_new_interval(M);
		I->omega = 5.0;        // wild guess.
		I->damp = 1.5;
		I->a =  0.0;
		I->d =  12.0;
		I->pdur = duration*MILLISECONDS;
		break;
		
	case 6:                           //  PAUSE NOT REALLY A TONE
		I = gimmy_a_new_interval(M);
		I->omega = 20.0;
		I->damp = 1.5;
		I->c = -10.0;
		I->d = -15.0;		
		I->pdur = duration*MILLISECONDS; 
		I->parentsyll=NOT_AN_INDEX;
		break;

	case 7:                                // Initial onset beginning phrase
		I = gimmy_a_new_interval(M);       //  then  raising up 
		I->omega = 5.0;
		I->damp = 1.5;
		I->a = 0.0;
		I->b = 0.0;
		I->pdur = duration*MILLISECONDS;
		I->parentsyll = NOT_AN_INDEX;
		break;
	}

	I->nframes = (int) (I->pdur * FRAMESPERSECOND + 0.5);
	I->tone = (short) tone;
    I->omega = I->omega / M->speedtau ;

#ifdef  MAND_PHRASE_F0_CONTOUR 
    add_time_to_mand_phrase_f0(&(M->F0phraseGenerator),I->pdur, I->nframes);
#endif 

#ifdef DEBUGMANDF0MACHINE
#ifdef DEBUGDETAIL
	FNX_SPRINTF(mandf0printbuff," I->nframes=%5i I->pdur = %10.6f\n",I->nframes,I->pdur);
    mandf0_print(M,0,mandf0printbuff);	
#endif
#endif 

//	M->lastF0goal = I->G;
	
}

/* end of QTA (2nd order with delay) method */




/* 
Is all a little really like Dectalk: From the garden through the kitchen
to the celler and back through the garage into the living room...
This little thing below gets called by pinyinparse in order to make a new syllable.
pinyinparse thinks it's getting new memory (looks like calloc), but, no no, it's the wicked machine
here that provides the space, let's pinyinparse fill in some blanks and then
call this machine to receive the new data. Of course, i've got to initialize it
properly.  

  the following takes the role of
  allocating space for a new syllable:
*/

MandSyll *newMand_Syll(LPTTS_HANDLE_T phTTS)
{
    MandF0Machine *M;
	MandSyll *newsyll = (MandSyll *) NULL;

	M=&(phTTS->MandarinF0Machine); 

	if( M->freesyll < MAXMANDF0SYLLABLES)
	{
		newsyll = M->Mandsylls[M->freesyll];
		if (newsyll) memset(newsyll,0,sizeof(MandSyll));
		M->freesyll += 1;
	}

	return newsyll;
}

/*  
    This little two line code piece will 
	pull result in all kinds of terminations
	The synthesizer basically wants the control after that
	and we have to wait until it has synthesized everything
	"said" sofar. After we return from this subroutine
	it's time to start from new making control intervals.
*/

/* rule: syllables starting with non-high vowel are preceeded by 
   glottal stop (realized as slight glottalization) 
*/
int process_mand_glottalization(char *syll, int len)
{
	char c;
	int nlen,i;
	nlen=len;

	c = syll[0];
	if (c=='e'  || c=='E' || c=='A' || c=='a' || c=='6' || c=='7')
	{
		nlen += 1;
		for (i=nlen; i>0; i--) syll[i]=syll[i-1];   // move all including final 0
		syll[0] = 'H';  // glottal stop
	}
	return nlen;
}

int  mand_machine_syllable(LPTTS_HANDLE_T phTTS, MandF0Machine *M, char *syll, int tone, int millisecs, int cntrl)
{
	double durations[6];
	double pdur;
	int k, len;
    short buf[4];
	int ctl, cnt;
	char testletter;  /* debug stuff */

	len = 0;
	if (tone>=1 && tone <= 5 && syll != (char *) NULL)
	{
		len = FNX_STRLEN(syll);	
		len = process_mand_glottalization(syll,len);
       /* here cntrl is set to 1 if the last syllable is being processed */
		pdur = mand_duration_calc(phTTS, syll, durations, tone, M->speedtau,cntrl);  // durations (in msec)


		make_tonal_gestures(M, tone, pdur);  // pdur in msec

		cnt = M->numintervals;

		if (tone==5)       
  		{
		ls_util_send_phone(phTTS,S2); // MAND_S2: means: less than no stress
		}

		for (k=0;k<len;k++)
		{
#ifdef DEBUGMANDF0MACHINE
//		inht = inh_timing(phTTS, phTTS->pKernelShareData->reverse_ascky[syll[k]]);
		FNX_SPRINTF(mandf0printbuff,"      {'%c', %i, %i}\n",syll[k],(int) durations[k],cnt);  /* for Matlab to read */
		mandf0_print(M,0,mandf0printbuff);

		printf("sending %c  dur =%g\n",syll[k],durations[k]);
#endif

		buf[0] = phTTS->pKernelShareData->reverse_ascky[syll[k]];
		buf[0]+=(1 << PSNEXTRA);
		buf[1] = (int) (durations[k]+0.5);    // add half a frame length to round and then some...
		ls_util_write_pipe(phTTS->pKernelShareData,&buf[0],2);
		}
	}
	else
	{
		ctl = cntrl;
		if (ctl==0) ctl = ' ';// phTTS->pKernelShareData->reverse_ascky[' '];
		pdur = (double ) millisecs;
	//	make_tonal_gestures(M, tone, pdur); // "tone" is 6 or more: pause types  .
		cnt = M->numintervals;

#ifdef DEBUGMANDF0MACHINE
		if (tone==7) testletter='@';
		else         testletter='#';
		FNX_SPRINTF(mandf0printbuff,"      {'%c', %i, %i}\n",testletter, (int) millisecs, cnt);  /* for Matlab to read */
		mandf0_print(M,0,mandf0printbuff);
#endif
	
	}
	return (len);
}
	

/* Mand_F0_machine:  
   The last three parameters can be [dur,delta, delay] or [tone,0,0]

	Note the flag MANDF0MACHINE:
	if it is not set, any call to Mand_F0_will result in 
	no action except init and get F0. 
	So I only have to switch this switch.

 */ 

int Mand_F0_machine(LPTTS_HANDLE_T phTTS, MFZ_Code opcode, void *ptr, int par1, int par2, int par3)
{
    int ret,duration,phone_number,f0ref, thephone;
    MandF0Machine *M;
    char *pc;
    MandSyll *CurrSyll, *newSyll;
	PDPH_T	pDph_t = phTTS->pPHThreadData;
//		duration = pDph_t->cur_speaker[PFCH]->inhdr[par1];

	f0ref = pDph_t->curspdef[SPD_AP];

    M = &(phTTS->MandarinF0Machine); 
	if (!M) return 0;

	ret=1;	

    switch (opcode)
    {
	case MFZ_INIT:
	    /* specify max number of syllables and intervals in the call */

#ifdef DEBUGMANDF0MACHINE
	    if (M->is_on == 0) mandf0_print(M, MANDF0FILEOPEN, NULL);  /* make sure  this is only opened once */
#endif
	    init_MandF0Machine(M,par1,par2,par3, 120); //GetBaseF0(phTTS));   
		
#ifdef DEBUGMANDF0MACHINE
//		sprintf(mandf0printbuff,"% MFZ_INIT speakrate = %i\n",par3);
//	    mandf0_print(M,0,mandf0printbuff);
#endif	
	    ret = 1;

	    break;
	    
	case MFZ_CLEANUP:
	    switch_off_MandF0Machine(M);   /* call only to free memory and only once */
	
	    break;
	    
	case MFZ_INITSYLLABLES:
	    reset_MandF0Machine(phTTS, M, 1, 120);// GetBaseF0(phTTS));
#ifdef  MAND_PHRASE_F0_CONTOUR 
        reset_mand_phrase_f0(&(M->F0phraseGenerator));
#endif 

		make_tonal_gestures(M, 5, 64); // for starting up filter
	    break;
	    
	case MFZ_STARTSYLLABLE:
	    /* if this is called, it means a new syllable is going to start:
	       we get the tone information extra. */
		newSyll = (MandSyll *) ptr;   // cast from void*
		if (newSyll) pc = newSyll->syll;
		if (pc[0] =='\0') return;

		if (M->numsyllables < MAXMANDF0SYLLABLES)
		{
			M->currentsyll += 1;
			M->numsyllables += 1;
		}
		else
		{
			return (0);
		}

	    break;

	case MFZ_PUTSYLLABLE:
	      newSyll = (MandSyll *) ptr;
		  if (newSyll) pc = newSyll->syll;
		  else         pc = (char *) NULL;
		  if (!pc) return (0);
		  if (pc[0]=='\0') return (0);    /* empty syllable: forget about it! */

		  ret = mand_machine_syllable(phTTS, M, pc, par1, 0, par2);   // par1 is tone.  par2 : lastsyll 1 or 0
	     break;
		
	case MFZ_PUT_CNTR_PHONEME:
	    /* count up phonemes*/
/* Problem is: the whole thing gets reset when an end of phrase particle is sent. 
   So I have to terminate graciously. Which is, I postpone sending the
   komma, period, or whatever, until I have done all the other preparations
*/
	    M->phoneme_in_phrase += 1;
	    M->numcontrolphones += 1;
        mand_machine_syllable(phTTS, M, 0, 6, par1, par2);    /* par2 is control signal */

#ifdef DEBUGMANDF0MACHINE
#ifdef DEBUGDETAIL
        look_at_allowdurs(phTTS,M);
#endif
		mandf0_print(M,0,"};\n");  /* for Matlab analysis */
#endif
//	    set_mandctl_values(M);   
		
#ifdef  MAND_PHRASE_F0_CONTOUR 
        start_mand_phrase_f0(&(M->F0phraseGenerator));
#endif
		/* when returning from the next call, the whole schebang said 
		   sofar has been synthesized, and should hit your
		   eardrums any time soon 
		*/
		break;

//		send_mand_control_phoneme(phTTS, M, par1, par2);  
 
	case MFZ_PAUSE_RESET:
	    reset_MandF0Machine(phTTS,M, 0, 120);// GetBaseF0(phTTS));
#ifdef  MAND_PHRASE_F0_CONTOUR 
        reset_mand_phrase_f0(&(M->F0phraseGenerator));
#endif 
//		printf("call tonal_gesture 96\n");
		make_tonal_gestures(M, 5, 96);
	    break;

	case MFZ_MAKE_INTERVAL:             /* Used to make start interval */
	    M->phoneme_in_phrase += 1;
	    M->numcontrolphones += 1;
		printf("MFZ_MAKE_INTERVAL\n");
		mand_machine_syllable(phTTS, M, 0, 7, 32,0); 
//		set_mandctl_values(M); 
#ifdef DEBUGMANDF0MACHINE
#ifdef DEBUGDETAIL
        look_at_allowdurs(phTTS,M);
#endif
		mandf0_print(M,0,"};\n");  /* for Matlab analysis */
#endif

		break;

	case MFZ_FINISHPHRASE:

#ifdef DEBUGMANDF0MACHINE
#ifdef DEBUGDETAIL
        look_at_allowdurs(phTTS,M);
#endif
		mandf0_print(M,0,"};\n");  /* for Matlab analysis */
#endif
//	    set_mandctl_values(M);   
		
#ifdef  MAND_PHRASE_F0_CONTOUR 
        start_mand_phrase_f0(&(M->F0phraseGenerator));
#endif
/* Here I need code that makes the synthesiser actually start synthesis. 
   After that I'll have to reset the syllable array 
*/

		break;

	case MFZ_NEWCOEFFIENTS:
//		calculate_syll_durations(phTTS, M);

		cranck_up_f0_iteration(phTTS,M,4,f0ref);
//		printf("cranck called\n");
	    break;
	    
	case MFZ_GET_F0:
		if(par1<0 || par1 > 99) 
		{
			duration = -666;  //invalid control phone
		}
		else
		{		 
		duration = pDph_t->cur_speaker[PFCH]->inhdr[par1];
		thephone = pDph_t->allophons[par1] & 0xff;
		}

	    ret = F0_ex_machina(M,par1, thephone,duration,f0ref);
	    return (ret);
	    break;	    

	case MFZ_PRINT_SYLLABLES:
	    //  print_mand_syllables(M);
	    break;

    }
    return ret;
}


