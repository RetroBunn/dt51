/*				P H D R A W T 0 . C 			*/
/* Copyright	1988,				by Dennis H. Klatt	*/
/* 

	*	076  MFG	09/30/2002		removed Winpreintf for windows CE
*/

/* f0mode:
*
*	1  NORMAL
*		pDph_t->f0tar[] contains step (f0 even), impulse (f0 odd), and baseline
*		 reset (f0=0) commands created by rules.
*		pDph_t->f0tim[] contains incremental time in frames since last command.
*		A slow psuedo-random variation is added to f0 so as to prevent
*		 an interval of constant f0.  Any glottal stop gestures are
*		 added in at the end. 
*		NEW STUFF-Note we occasionally want a few frames at near constant f0 to give
*			a soft tonal quality to a voice esp female eab 96
*
*	2  HAT_LOCATIONS_SPECIFIED
*		User specified location of hatrise/fall.  Same as NORMAL as
*		 far as this module is concerned.
*
*	3  HAT_F0_SIZES_SPECIFIED
*		User attached steps and impulses to hatrise, hatfall,
*		 and stress phones.  Same as NORMAL as far as this module
*		 is concerned.
*
*	4  SINGING 
*		pDph_t->f0tar[] contains note requests [1 - 37], offset by 2000, that
*		 have been selected by user <time,f0> requests attached to
*		 selected phonemes, usually vowels, usually one per syllable.
*		pDph_t->f0tim[] contains incremental time in frames since last note.
*		Movement to a new note begins at start of segment and takes
*		 100 ms.  A 6 Hz vibratto of magnitude +/- 2 Hz is added to f0.
*
*
*	5  PHONE_TARGETS_SPECIFIED
*		pDph_t->f0tar[] contains f0 requests in Hz that have been selected
*		 by user <dur,f0> requests attached to selected phonemes,
*		 in which case f0 ramps linearly from previous value to pDph_t->f0tar[]
*		 over the duration of the phoneme.
*		pDph_t->f0tim[] contains incremental time in frames since last command.
*		A slow psuedo-random variation is imposed on f0 to prevent
*		 an interval of constant f0.
*
*	6  TIME_VALUE_SPECIFIED
*		pDph_t->f0tar[] contains f0 requests in Hz that have been selected
*		 by user {time,f0} requests, in which case f0 ramps linearly
*		 from previous value to pDph_t->f0tar[] over the time interval since
*		 the last {time,f0} command.
*		pDph_t->f0tim[] contains incremental time in frames since last command.
*		A slow psuedo-random variation is imposed on f0 to prevent
*		 an interval of constant f0.Bats 349
*/

#include "ph_def.h"

#include "tts.h"
#include "Mandarin.h"
#include "mandarinprot.h"

//#define MANDF0MACHINE defined in mandarinprot.h


//#define CREEKMALE
#define TWOPI 4096			/* For getcosine() function below */
#define PI 2048
#define PIOVER2 1024
#define DT_ONE	(PIOVER2*PIOVER2)

//#define GRAPHF0
//#define DEBUGF0


#define HIGHEST_F0	  5121	/*	Maximum F0 in Hz*10 */
#define LOWEST_F0	   500	/*	Minimum F0 in Hz*10 */
#define F_SEG_LOWPASS	  3000	/* Nominal cutoff freq of 1-pole low-pass	 */
#define DELAY_SEG_LOWPASS	 3	/* Delay in frames to half-way of step resp. */
#define F0SHFT			 3	/* Shift to avoid roundoff errors in		 */
/*	 filtering f0 commands			 */

/*	  External constants from PHROM.C */
/* extern short f0glstp[]; *//* F0 dip for a glottal stop */
// eab 2/17/98 No longer used extern short			  f0segtars[];	 /* Array of segmental influences */
//	extern short *featb;		/* Feature values for phonemes */
extern short notetab[]; 	/* f0 target for notes C2-C5 (1-37) */
extern short getcosine[];	/* Cos tab for jitter and/or vibratto */
//extern short randnum();

//	extern int begtyp(int phone);
//	extern int endtyp(int phone);

#define phone_feature(a,b) (pDph_t->cur_speaker[(b)>>8]->featb[(b)&0x00FF])
#define place(b) (pDph_t->cur_speaker[(b)>>8]->place[(b)&0xFF])


/* MVP : static function declarations*/
static void set_user_target(PDPH_T pDph_t,short *psF0command); 
static void filter_commands(PDPH_T pDph_t,short f0in); 
static void filter_seg_commands(PDPH_T pDph_t,short f0in);
static void linear_interp(PDPH_T pDph_t); 
static void set_tglst(PDPH_T pDph_t);

const short gst_delta[9] = {  90, 80,70, 60,50, 43, 20, 0};
//int oarcnt=0;

const short	uk_f0msegtars[] =
{	
	/* SI    IY	 IH    EY	 EH    AE	 AA    AY	 AW    AH	*/
	50,  100,	 60,   40,	 20,   0,	 0,    0,	 0,    20,
		
	/* AO    OW	 OY    UH	 UW    RR	 YU    AX	 IX    IR	*/
	0,		 30, 50,  60,	 140,  50,	100, 30, 60, 100,
	/* ER    AR	 OR    UR	  W 	Y	  R 	L	 HX    OH	*/
	60,	0,	 30,   80,	 60,   60,	  0,	0,	 200,  0,
	/* LX 	M	  N    NG	 EL    D$	 EN 	F	  V    TH	*/
      0,		0,		0,  0,    0,  -20,    0,  300,  -60,  300,
	/* DH 	S	  Z    SH	 ZH 	P	  B 	T	  D 	K	*/
      -60,  300,  -60,  300,  -50,  300,  -50,  300,  -50,  300,
      /* G    DX    TQ     Q    CH    JH  DF                         */
      -20,  -10,    0,    0,  300,  -20,	-20
};

const short	uk_f0fsegtars[] =
{
	/* SI    IY	 IH    EY	 EH    AE	 AA    AY	 AW    AH	*/
	50,  180,	 90,   60,	 30,   0,	 0,    0,	 0,    30,
	/* AO    OW	 OY    UH	 UW    RR	 YU    AX	 IX    IR	*/
	0,     40,	 70,   70,	 180,  50,	100, 30, 60, 100,
	/* ER    AR	 OR    UR	  W 	Y	  R 	L	 HX    OH	*/
	70,	0,	 30,   80,	 60,   60,	  0,	0,	 200,  0,
	/* LX 	M	  N    NG	 EL    D$	 EN 	F	  V    TH	*/
      0,		0,		0,  0,    0,  -20,    0,  300,  -60,  300,
	/* DH 	S	  Z    SH	 ZH 	P	  B 	T	  D 	K	*/
      -60,  300,  -60,  300,  -50,  300,  -50,  300,  -50,  300,
      /* G    DX    TQ     Q    CH    JH  DF                         */
      -20,  -10,    0,    0,  300,  -20,	-20
};


const short sp_f0msegtars[] =
{
	/* E_SI	E_A   E_E	E_I   E_O	E_U E_WX  E_YX */
		30,	0,	  150,	200,  30,	140, -50 , 140,
		
	/* E_RR	E_L  E_LL	   E_M		 E_N  E_NH	 E_F   E_S	 E_J  E_TH	*/
		-50, -50, -50 ,		0,		  0,	0 , 300,	300, -70, 300,
	
	/* E_BH  E_DH  E_GH  E_YH   E_P		 E_B   E_T	 E_D   E_K	 E_G  */
	-50,	-50,  -50,	-50,	300,	-50,	300, -50, 300 , -50,
	
	/* E_CH	E_Y   E_R	E_Q */
		300 , -50, -50, 0,
	
	/* E_Z   E_W	E_NX  E_V	E_IX  E_MX	E_PH */
		-50, -50,	-50,  -50,	-20,   0,  300 
};

const short sp_f0fsegtars[] =
{
	/* E_SI	E_A   E_E	E_I   E_O	E_U E_WX  E_YX */
		30,	0,	  150,	200,  30,	140, -50 , 140,
		
	/* E_RR	E_L  E_LL	E_M   E_N  E_NH   E_F	E_S   E_J  E_TH  */
		-50, -50, -50 ,		0,		  0,	0 , 300,	300, -70, 300,
		
	/* E_BH  E_DH  E_GH  E_YH   E_P		 E_B   E_T	 E_D   E_K	 E_G  */
	-50,	-50,  -50,	-50,	300,	-50,	300, -50, 300 , -50,
		
	/* E_CH	E_Y   E_R	E_Q */
		300 , -50, -50, 0,
				
	/* E_Z   E_W	E_NX  E_V	E_IX  E_MX	E_PH */
		-50, -50,	-50,  -50,	-20,   0,  300 
};

const short la_f0msegtars[] =
{
	/* E_SI	E_A   E_E	E_I   E_O	E_U E_WX  E_YX */
		30,	0,	  150,	200,  30,	140, -50 , 140,
		
	/* E_RR	E_L  E_LL	   E_M		 E_N  E_NH	 E_F   E_S	 E_J  E_TH	*/
		-50, -50, -50 ,		0,		  0,	0 , 300,	300, -70, 300,
		
	/* E_BH  E_DH  E_GH  E_YH   E_P		 E_B   E_T	 E_D   E_K	 E_G  */
	-50,	-50,  -50,	-50,	300,	-50,	300, -50, 300 , -50,
		
	/* E_CH	E_Y   E_R	E_Q */
		300 , -50, -50, 0,
	
	/* E_Z   E_W	E_NX  E_V	E_IX  E_MX	E_PH */
		-50, -50,	-50,  -50,	-20,   0,  300 
};

const short la_f0fsegtars[] =
{
	/* E_SI	E_A   E_E	E_I   E_O	E_U E_WX  E_YX */
		30,	0,	  150,	200,  30,	140, -50 , 140,
		
	/* E_RR	E_L  E_LL	E_M   E_N  E_NH   E_F	E_S   E_J  E_TH  */
		-50, -50, -50 ,		0,		  0,	0 , 300,	300, -70, 300,
	
	/* E_BH  E_DH  E_GH  E_YH   E_P		 E_B   E_T	 E_D   E_K	 E_G  */
	-50,	-50,  -50,	-50,	300,	-50,	300, -50, 300 , -50,
	
	/* E_CH	E_Y   E_R	E_Q */
		300 , -50, -50, 0,
			
	/* E_Z   E_W	E_NX  E_V	E_IX  E_MX	E_PH */
		-50, -50,	-50,  -50,	-20,   0,  300 
};


/*	  Incremental changes to F0 caused by segmental influences */

const short gr_f0msegtars[] = {	
	/* GEN_SIL	 A	   E	AE	  EX	 I	   O	OE	   U	UE	*/
		10,	 40,   60,	   10,	  80,	0,   0,	0,   0,	0,
	/* AH    EH	AZ	  IH	OH	 OZ    UH	UZ	  EI	AU	*/
	20,   20,	 60,  60,	80,  80,   60,	40,   0,	 0,
	/* EU    AN	 IM    UM	 ON 	J	  L    RR	  R 	H	*/
	0,   0,	 0,   0,	 0,   0,	  -10,	  -10,	-10,	0,
	/* M	   N	NG	  EL	EM	  EN	 F	   V	 S	   Z	*/
	0,  0,	0,   0,  0,  0,  0,  0,	 0,   0,
	/* SH    ZH	 CH    KH	  P 	B	  T 	D	  K 	G	*/
	0,  0,	0,  0,	0,  0,	0,  0,	0,  0,
	/* Q	  PF	TS	  DJ	TJ	  KS */
	0,    0,	 0,    0,	 0,    0
};
/*	  Incremental changes to F0 caused by segmental influences */

const short gr_f0fsegtars[] = {
	/* GEN_SIL	  A 	E	 AE    EX	  I 	O	 OE 	U	 UE */
	70,	 15,   15,	   15,	  10,	70,   45,	70,   26,	100,
	/* AH    EH	AZ	  IH	OH	 OZ    UH	UZ	  EI	AU	*/
	26,   26,	 60,  60,	80,   80,  60,	40,   80,	45,
	/* EU    AN	 IM    UM	 ON 	J	  L    RR	  R 	H	*/
	60,   10,	45,   45,	60,   60,	 -15,	 -15,  -15,    0,
	/* M	   N	NG	  EL	EM	  EN	 F	   V	 S	   Z	*/
	-70,  -70,	-70,   0,  -70,  -70,  400,  -70,  -70,  -70,
	/* SH    ZH	 CH    KH	  P 	B	  T 	D	  K 	G	*/
	400,  -70,	400,  400,	400,  -70,	400,  -70,	400,  -70,
	/* Q	  PF	TS	  DJ	TJ	  KS */
	-70,	  0,	0,	  0,	0,	  0
};



const short	us_f0msegtars[] =
{
	/* SI    IY    IH    EY    EH    AE    AA    AY    AW    AH	*/
	50,  90,  80,    50,   30,    0,    0,    0,   0,    20,

	/* AO    OW    OY    UH    UW    RR    YU    AX    IX    IR	*/
	0,   30,   60,   80,  90,   50,  90,   30,   70,  50,

	/* ER    AR    OR    UR     W     Y     R     L    HX    RX	*/
	     50,    0,   30,   60,  -60,  -60,    0,    0,  200,    0,

	/* LX     M     N    NX    EL    D$    EN     F     V    TH	*/
	      0,    0,    0,    0,    0,  -20,    0,  180,  -60,  180,

	/* DH     S     Z    SH    ZH     P     B     T     D     K	*/
	    -60,  180,  -60,  180,  -60,  200,  -20,  150,  -20,  150,

	/*       G    DX    TQ     Q    CH    JH				*/
	         -20,  -10,    0,    0,  150,  -20,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

/* Incremental changes to F0 caused by segmental influences */

const short	us_f0fsegtars[] =
{
	/* SI    IY	 IH    EY	 EH    AE	 AA    AY	 AW    AH */
	50,   60,    0,  0,   40,   0,     0,    0,    0, 40,
		
	/* AO    OW	 OY    UH	 UW    RR	 YU    AX	 IX    IR */
		0,  40,	 70,   90,   160,   80,  150,  60,   80,   120,
		
	/* ER    AR	 OR    UR	  W 	Y	  R 	L	 HX    RX */
	80, 0, 50, 120, 80, 80, 0, 0, 200, 0,
		
	/* LX 	M	  N    NG	 EL    D$	 EN 	F	  V    TH */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		
	/* DH 	S	  Z    SH	 ZH 	P	  B 	T	  D 	K */
		250, 200,	-20, 200, 0, 200, 0, 200, 0, 200,
		
	/* G	  DX	TQ	   Q	CH	  JH  DF CZ TZ */
	0, 0, 0, 0, 0, 0, 0	,0,0,

	/* ly re x1 x2 x3 x4 x5 x6 x7 x8 x9 z1 */
	    0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* Incremental changes to F0 caused by segmental influences 
eab prelimary test indicate that the 300 values are an exageration
while -50 for d look good*/

const short	fr_f0msegtars[] = {
	/* SI 	A	 A3    E2	 Au 	E	 E1    Eu	  I 	O	*/
	50,	0,	  0,	100,	  0,	0,	  200,	0,	  300,	0,
		
	/* O6    Ou	  U    An	 In    On	 Un  SegAXP   L 	R  */
	0,	0,	  0,	200,	  0,	0,	  0,	0,	  0,	0,
		
	/*  W    Wu	  Y    Ch	  F 	J	 Rx 	S	  V 	Z  */
		-60,-60, 140,  300,	300,  -20,	 0,   300,  -60, -60,
		
	/*  B 	D	  G 	K	  P 	T	 Gn 	M	  N    Ng  */
	-70, -70,   -70,	0,	0,	  0,  -70,	-70, -70, -70,
		
	/* SegX  SegSil */
	0,   0
};

/* Incremental changes to F0 caused by segmental influences (Male) */
// These entirely made up for now.
const short	kr_f0msegtars[] =
{
	0, 		// _
	90, 	// IY
	70, 	// EH
	50, 	// AE
	30, 	// UW
	30, 	// UH
	30, 	// UI
	30, 	// OW
	30, 	// AO
	30, 	// AA
	30, 	// YE
	30, 	// YH
	30, 	// YU
	30, 	// YO
	30, 	// YC
	30, 	// YA
	30, 	// WI
	30, 	// WE
	30, 	// WH
	30, 	// WC
	30, 	// WA
	0, 		// M
	0, 		// N
	0, 		// NX
	150,	// P
	150, 	// PH
	150, 	// PP
	-20, 	// B
	150, 	// T
	150, 	// TH
	150, 	// TT
	-20, 	// D
	150, 	// K
	150, 	// KH
	150, 	// KK
	-20, 	// G
	150, 	// S
	150, 	// SS
	150, 	// SH
	90, 	// HX
	30, 	// Y
	0, 		// L
	0, 		// DF
	-20, 	// JH
	150, 	// CH
	30, 	// CC
	30		// WO
};	


/* Incremental changes to F0 caused by segmental influences  (Female) */
// These are entirely made up for now
const short	kr_f0fsegtars[] =
{
	0, 		// _
	90, 	// IY
	70, 	// EH
	50, 	// AE
	30, 	// UW
	30, 	// UH
	30, 	// UI
	30, 	// OW
	30, 	// AO
	30, 	// AA
	30, 	// YE
	30, 	// YH
	30, 	// YU
	30, 	// YO
	30, 	// YC
	30, 	// YA
	30, 	// WI
	30, 	// WE
	30, 	// WH
	30, 	// WC
	30, 	// WA
	0, 		// M
	0, 		// N
	0, 		// NX
	150,	// P
	150, 	// PH
	150, 	// PP
	-20, 	// B
	150, 	// T
	150, 	// TH
	150, 	// TT
	-20, 	// D
	150, 	// K
	150, 	// KH
	150, 	// KK
	-20, 	// G
	150, 	// S
	150, 	// SS
	150, 	// SH
	90, 	// HX
	30, 	// Y
	0, 		// L
	0, 		// DF
	-20, 	// JH
	150, 	// CH
	30, 	// CC
	30		// WO
};


/* Mandarin F0 segmental offsets (male) */
const short ch_f0msegtars[] =
{      
/* CH_SIL, CH_IY , CH_UE , CH_EY , CH_EH , CH_A  , CH_IF , CH_IR */
    20   ,   20  ,   20  ,   -10 ,  10   , -20   ,   20  ,  20  ,
/* CH_AX , CH_UW , CH_UH , CH_UC , CH_OW , CH_WO , CH_AO , CH_AA */
     0   ,   30  ,    30 ,    0  ,  30   ,  30   ,   20  ,  -30  ,
/* CH_AY , CH_AW , CH_ER , CH_M  , CH_N  , CH_NX , CH_P  , CH_PV */
     0   ,   0   ,    0  ,   10  ,   0   , -10   ,    50   ,  0  ,
/* CH_T  , CH_TV , CH_K  , CH_KV , CH_F  , CH_S  , CH_SR , CH_ZR */
    50  ,  50  ,   50  ,    0  ,   0   ,    50  ,    50,   20  ,
/* CH_TJ , CH_CH , CH_RF , CH_Y  , CH_W  , CH_L  , CH_TS , CH_DS */
    50   , -100 ,    0  ,   50  ,  50   ,  100  ,   100 ,  100  ,
/* CH_JJ , CH_JV , CH_T1 , CH_D1 , CH_KH , CH_YI , CH_WU , CH_AH */
    20  ,   20  ,   20  ,    5  ,  -30 ,   20  ,   10  ,    0  ,
/* CH_XR , CH_AR , CH_OR , CH_1R , CH_WR , CH_2R , CH_UR , CH_3R */
     0   ,  -40  ,   -30 ,   -30 ,  -30  ,  -20   ,   10  ,   20 ,
/* CH_4R , CH_5R , CH_YR , CH_X1 , CH_X2 , CH_X3 , CH_X4  , CH_X5 */
   -20   ,   30  ,    30 ,  -30  ,  -30  ,    0  ,    0   ,   0  
};

/* Mandarin F0 segmental offsets (female) */
const short ch_f0fsegtars[] =
{      
/* CH_SIL, CH_IY , CH_UE , CH_EY , CH_EH , CH_A  , CH_IF , CH_IR */
    50   ,  100  ,   50  ,  100  ,  50   , -50   ,   80  ,  80  ,
/* CH_AX , CH_UW , CH_UH , CH_UC , CH_OW , CH_WO , CH_AO , CH_AA */
     0   ,   40  ,    40 ,    0  ,  40   ,  40   ,   20  ,  -40  ,
/* CH_AY , CH_AW , CH_ER , CH_M  , CH_N  , CH_NX , CH_P  , CH_PV */
     0   ,   0   ,    0  ,  100  ,  80   ,  30   ,   300   ,  -50  ,
/* CH_T  , CH_TV , CH_K  , CH_KV , CH_F  , CH_S  , CH_SR , CH_ZR */
    300  ,  200  ,   50  ,    0  ,   0   ,  300  ,   300,   100  ,
/* CH_TJ , CH_CH , CH_RF , CH_Y  , CH_W  , CH_L  , CH_TS , CH_DS */
    300   , -200 ,    0  ,   50  ,  50   ,  100  ,   400 ,  200  ,
/* CH_JJ , CH_JV , CH_T1 , CH_D1 , CH_KH , CH_YI , CH_WU , CH_AH */
    300  ,  100  ,   20  ,    5  ,  -100 ,   60  ,   20  ,    0  ,
/* CH_XR , CH_AR , CH_OR , CH_1R , CH_WR , CH_2R , CH_UR , CH_3R */
     0   ,  -40  ,   -30 ,   -30 ,  -50  ,  -20   ,   30  ,   50 ,
/* CH_4R , CH_5R , CH_YR , CH_X1 , CH_X2 , CH_X3 , CH_X4  , CH_X5 */
   -20   ,   50  ,    50 ,  -50  ,  -30  ,    0  ,    0   ,   0  
};


const short *CONSTCONST fr_f0fsegtars = fr_f0msegtars;
/* Incremental changes to F0 caused by segmental influences */


/*    Incremental changes to F0 caused by segmental influences */
	const short jp_f0segtars[] = {
	     50,  100,   40,    0,   30,  100,   50,   10,   40,  100,
	     70,   30,    0,   40,  300,  -50,  -50,  -50,  -50,  -50,
	     40,  -50,  300,  -50,  300,  -50,  300,  300,  -50,  -50,
	      0,  300,  -50,  300,  -50,  300,  -50,  300,  -50,  300,
	    -50
	};



/* ******************************************************************
 *      Function Name: pht0draw()
 *
 *      Description: Searches through parameters given to the phoneme
 *
 *      Arguments: LPTTS_HANDLE_T phTTS	Text-to-speech handle
 *
 *      Return Value: void
 *
 *      Comments:
 *
 * *****************************************************************/
void pht0draw(LPTTS_HANDLE_T phTTS) 
{	
	/*	  Automatic variables */
#ifdef GRAPHF0
	int icnt;
	char prntbuf[121];
#endif
	int temp,dtglst,pseudojitter=0;	
	PKSD_T pKsd_t;
	PDPH_T pDph_t;
	PDPHSETTAR_ST pDphsettar;
	short f0seg=0,f0in=0;
	short tmp;
	
	pKsd_t = phTTS->pKernelShareData;
	pDph_t = phTTS->pPHThreadData;
	pDphsettar = pDph_t->pSTphsettar;

	/*pDphsettar->timecos10=0; pDphsettar->timecos15=0; pDphsettar->timecosvib=0;*/
		
	if(pDph_t->malfem == MALE)
	{	
		/*	  Initialize */
		if (pDph_t->nf0ev <= -2) 
		{

			/* Hard initialization */
			/* for now hardcode baseline for init experimentation eab 8/96*/
			/* EAB BUG- found problem with f0command, it needs to be a global variable
			or it sometimes doesn't get handled correctly*/
			pDph_t->clausepos=0;
			pDphsettar->phocur = GEN_SIL;

			/* redundant and incorrectly placed code since a soft init automatically follows a hard init
			the code only has to be in once*/

			/*		  Time since last reset of baseline fall, in frames */
			pDphsettar->nframb = 0;
			pDph_t->f0primefall =0;
			pDph_t->f0primefalldelta = pDph_t->f0basefall/(pDph_t->tcumdur+1);
			pDphsettar->basetime = 0;
			pDphsettar->basecntr = 0;
			pDphsettar->f0delta  = 0;

			/*eab 4/11/97 Moved these variables to a proper place of initlaization*/
			pDphsettar->timecos10=0; pDphsettar->timecos15=0; pDphsettar->timecosvib=0; 

			/*		  If within 32 ms (5 frames) of nframg, glottal stop gesture */
			/*		  is in progress */
			pDphsettar->tglstp = -200;

			/*		  Set filter memory to init baseline fall (f0 in hz*10) */
			/*		  Set filter memory to init baseline fall (f0 in hz*10) */
			pDphsettar->f0las1 = pDph_t->f0minimum<< F0SHFT;
			pDphsettar->f0las2 = pDph_t->f0minimum<< F0SHFT;


			//			oarcnt = 0;
			pDphsettar->tarhat = 0;
			pDphsettar->tarimp = 0;
			pDphsettar->delimp = 0;

			/*		Set smoothing constants for ( critical-damped? ) 2nd-order sys	*/

			pDphsettar->f0a2 = pDph_t->f0_lp_filter;	/* Impulse and hat commands */
			pDphsettar->f0b = FRAC_ONE - pDphsettar->f0a2;
			pDphsettar->f0a1 = pDphsettar->f0a2 << F0SHFT;

			pDphsettar->f0sa2 =  F_SEG_LOWPASS; /* Segmental influences */

			pDphsettar->f0sb = FRAC_ONE - pDphsettar->f0sa2;
			pDphsettar->f0sa1 = pDphsettar->f0sa2 << F0SHFT;

			/*		Variables  relevent only if f0mode >= SINGING */

			pDphsettar->newnote = pDphsettar->f0basestart;
			pDphsettar->delnote = 0;
			pDphsettar->delcum = 0;
			pDphsettar->f0start = pDph_t->f0;
			pDphsettar->vibsw = 0;

			/*		Initialize pointer to f0 command string */

			pDph_t->nf0ev = -1;
		}

		/*	  Reinit pointer and time of first f0 command if new clause */
		if( pDph_t->nf0ev == -1 ) 
		{		
			pDphsettar->nimpcnt = 0;
			/* Soft initialization */
			pDphsettar->tarimp =0;
			pDph_t->enddrop =0;
			pDph_t->f0 = pDphsettar->f0basestart;

			/*	  Set Beginning and final frequency of baseline fall */
			switch (pDph_t->clausetype)
			{
			case 0: /*	declarative  */
				pDph_t->clausepos=0;
				break; //BATS 704

			case 1: /*	comma  First one goes up but later ones are more declarative*/
				// But long ones tend to be declarative! eab 4/15/00
				// MOve clausetype selection earlier as cbsym has to be decide as well
				break; //BATS 704

			case 2: /*	exclaimatory  */
				//4/15/00 EAB short one clasify as exclamatory but long ones suffer
				//from the don't know which part to emphasize problem so better devalrative.
				pDph_t->clausepos =0;
				break;


			case 3: /*	question  */
				pDph_t->clausepos =0;
				break;

			default:
				break;
			}

			//		oarcnt=0;
			pDphsettar->f0slas1 = 0;	/* Segmental filter avg output is zero */
			pDphsettar->f0slas2 = 0;	


			pDphsettar->nframb = 0;
			pDphsettar->drift =0;
			pDphsettar->basetime=0;
			pDphsettar->basecntr =0;
			pDphsettar->f0delta =0;
			pDph_t->special_phrase = 0;
			//		oarcnt=0;
			/*	  Raise baseline for first sentence of a paragraph */
			if (pDph_t->newparagsw != FALSE) 
			{
				pDphsettar->beginfall += 120;
				pDphsettar->endfall += 70;
				pDph_t->newparagsw = FALSE;
				//WINprintf ("New paragraph  beginfall %d, endfall %d\n", pDphsettar->beginfall, pDphsettar->endfall );
			}

			/*		  Time between 0 and first	f0 command, in frames */
			pDphsettar->dtimf0 = pDph_t->f0tim[0];
			/*		   Pointer into dur and phone arrays */
			pDphsettar->np_drawt0 = -1;
			pDphsettar->npg = -1;
			pDph_t->nf0ev = 0;

			/*		  Time since last f0 command, in frames */

			/* INITIALIZE NFRAM TO DELAY THROUGH FILTER THIS USED TO BE IN AND WAS NOT IN
			88 STUFF BUT IS REALLY NEEDED*/
			pDphsettar->nframs	= 0;
			pDphsettar->nfram	= 6- ((pDph_t->f0_lp_filter-1300)>>8);
			pDphsettar->nframg	= 0;		/*eab 0 works much better - 6-((pDph_t->f0_lp_filter-1300)>>8);*/
			pDph_t->f0primefall =0;
			pDph_t->f0primefalldelta = pDph_t->f0basefall/(pDph_t->tcumdur+1);		
			if (pDph_t->f0mode< SINGING) 
			{
				pDphsettar->nfram = pDphsettar->nframs >> 1;
			}
			else 
			{
				pDphsettar->nfram = 0;	/* Start note slightly early if singing */
			}

			/* Time since beginning of cur phonetic segment, in frames */
			pDphsettar->f0las1 = pDph_t->f0minimum<< F0SHFT;
			pDphsettar->f0las2 = pDph_t->f0minimum<< F0SHFT;

			pDphsettar->f0slas1 = 0;	/* Segmental filter avg output is zero */
			pDphsettar->f0slas2 = 0;
			pDph_t->f0 = pDphsettar->f0basestart;
			pDphsettar->nframs = 0; 	
			/* Used in computing segmental effects */


			/*		  Extra time, in frames, used to delay or advance f0 gesture assoc. */
			/*		  with a particular segment, e.g. at delayed vot, or anticipate in V-V */
			pDphsettar->extrad = -DELAY_SEG_LOWPASS; /* Start gesture toward next seg early */
			/*		  Duration of current segment, in frames */
			pDphsettar->segdur = 0;
			pDphsettar->segdrg = 0;
			pDph_t->lastallo=0;
			pDph_t->keepallo=0;
#ifdef GFAPHF0
			pDph_t->lastone=-1;
			pDph_t->keepdur=0;
#endif
			pDph_t->glotalize =0;
			pDphsettar->glide_stepamount=0;
			pDphsettar->glide_tot=0;
			pDphsettar->glide_inc =0;
			/*	  Must be at bottom of hat */
			pDphsettar->tarhat = 0; 	/* should be anyway, except for emergency halt */
			pDph_t->addjit = 305;
		}
		/*	  End of initialization */



		/*	See if new f0 commands issued					*/
		/*	  To get f0 commands to occur at right times, need to take		*/
		/*	  into account delay introduced by low-pass filter. Response to */
		/*	  a step command begins xx frames earlier than f0time[] request */
		/*	  so f0 gets half-way to target at nominal step onset time		*/

		while( (pDphsettar->nframb >= pDphsettar->dtimf0) && 
			   (pDph_t->nf0ev < pDph_t->nf0tot)) 
		{

			pDph_t->tmp = 0;

			pDphsettar->f0command = pDph_t->f0tar[pDph_t->nf0ev];	/* New target f0 */
			pDphsettar->type = pDph_t->f0type[pDph_t->nf0ev];
			pDphsettar->nfram -= pDphsettar->dtimf0;

			pDphsettar->length = pDph_t->f0length[pDph_t->nf0ev];


			if (pDph_t->f0mode== TIME_VALUE_SPECIFIED) 
			{
				pDphsettar->dtimf0 = pDph_t->f0tim[pDph_t->nf0ev];
				pDph_t->nf0ev++;
				set_user_target(pDph_t,&pDphsettar->f0command);
			}
			else 
			{
				pDph_t->nf0ev++;	/* Achieve target at next time */
				pDphsettar->dtimf0 = pDph_t->f0tim[pDph_t->nf0ev];
				switch(pDphsettar->type)
				{
				case USER: /*user specified f0 target*/
					set_user_target(pDph_t,&pDphsettar->f0command);
					break;

				case F0_RESET: /* f0 reset*/

					pDphsettar->tarhat = 0;		/* Go to bottom of hat pattern 
												and for UK init glide, note glide is not ifdefed _uk becuase
												it is a command we ant to allow others to use*/
					pDph_t->glotalize =0;
					//pDphsettar->glide_stepamount=0;
					//pDphsettar->glide_tot=0;
					//pDphsettar->glide_inc=0;
					break; //BATS 704
				case STEP:
					if(pKsd_t->lang_curr == LANG_british)
						break;

					pDphsettar->tarhat += pDphsettar->f0command;

					/* Command is a step, reset pDphsettar->tarhat */
					if (pDphsettar->f0command < 0) 
					{	/* Cancel previous impulse if step */
						/* is of opposite sign */
						if (pDphsettar->tarimp > 0) 
						{	
							pDphsettar->tarimp = 0;
							pDphsettar->delimp = 0;
						}
					}
					else
					{
						if (pDphsettar->tarimp < 0) 
						{
							pDphsettar->tarimp = 0;
							pDphsettar->delimp = 0;
						}
					}
					break;

				case GLIDE:/* eab 1/10/98 work in progress */
					if(pDphsettar->glide_stepamount !=0)	//last command interrupted by new command adjust
						tmp =  pDphsettar->glide_stepamount;
					else
						tmp=0;
					pDphsettar->glide_stepamount = pDphsettar->f0command+tmp;
					pDphsettar->glide_inc =(pDphsettar->glide_stepamount/pDphsettar->length);
					break;

				case GLOTTAL:
					if(pKsd_t->lang_curr == LANG_british)
						break;

					if(pKsd_t->lang_curr != LANG_french)
					{
						pDph_t->enddrop= -pDphsettar->f0command;
						pDph_t->glotalize =1;
					}
					break;

				case IMPULSE:

					/* Odd, command is impulse	*/
					/*			  Impulse realized as 24-frame "step plus ramp" from f0command */
					/*			  to three times focommand */
					/* eab old ocde used to have an impulse as a 2*f0command that would be realized as an 
					16 frame wide pulse. This new scheme proposed by Dennis Klatt uses 
					imp=f0command+(f0command _ f0command>>4 meaning it will take 16 farmes to
					reach double height. The old one never reached target so this new approach I think 
					presently has two problems it's dealyed too much and it lasts too long causing higher f0 values
					and more percieved effect. I want to try it differently starting out close to the old code with a pulse command that 
					trails off.
					with a downward slope think of it as a rectangular pulse with a triangle placed on
					top instead of a second rectangular pulse- by the way it's not working correctly at
					the moment*/

					pDphsettar->tarimp = pDphsettar->f0command;
					pDphsettar->delimp = pDphsettar->f0command>>2;

					pDphsettar->nimp = pDphsettar->length;
					pDphsettar->delimp = (pDphsettar->f0command/pDphsettar->nimp)<<1;
					pDphsettar->nimpcnt = 0;
					break;
				}
			}
			/*        Loop back to look for more f0 commands */
		}
#ifndef HLSYN
		if (pKsd_t->lang_curr == LANG_british)
		{

			/*EAB Drop pitch rapidly at  end of utterance
			enddrop now reflects pitch dropoff at end of utterance and not final creek
			hence the removal of the tcumdur stuff
			9/19/97 */
			if(  pDph_t->enddrop 
				&& pDph_t->glotalize  && pDph_t->number_words >= 3)
			{
				if(pDph_t->f0minimum > 500)
				{
					pDph_t->enddrop += pDph_t->enddrop>>1;
				}
			}
		}
#endif // HLSYN	


		pDphsettar->nframb++;		

		/*    Impulse duration fixed at 24 frames, count down to zero */
		/*    (actually, duration is function of speaker def par "quickness" */

		if (pDphsettar->nimpcnt == (pDphsettar->nimp)) {
			pDphsettar->nimpcnt = 0;
			pDphsettar->tarimp = 0;
			pDphsettar->delimp = 0;
			pDphsettar->nimp = 0;
		}
		else  if (pDphsettar->nimpcnt < (pDphsettar->nimp>>1)) 
		{
			//pDphsettar->nimp--;
			pDphsettar->tarimp += pDphsettar->delimp;
			//pDphsettar->nimp = 0;
			pDphsettar->nimpcnt++;
		}
		else
		{
			pDphsettar->nimpcnt++;
			pDphsettar->tarimp -= pDphsettar->delimp;
		}

		/*    Segmental effect on f0, reset pDphsettar->tarseg if time exceeds cum dur */

		if( pDphsettar->nframs >= (pDphsettar->segdur + pDphsettar->extrad) && 
			pDphsettar->np_drawt0 < (pDph_t->nallotot-1) ) 
		{
			pDphsettar->nframs -= pDphsettar->segdur;
			pDphsettar->segdur = pDph_t->allodurs[++pDphsettar->np_drawt0];
			pDphsettar->phocur = pDph_t->allophons[pDphsettar->np_drawt0];

			/* EAB Found long standing bug-- due to the compensation for the delay through the filters
			the first phoneme is getting cheated on duration */
			if(pDphsettar->np_drawt0 == 1)
			{
				pDphsettar->nframs = -DELAY_SEG_LOWPASS;
			}

			if (pDphsettar->np_drawt0 < pDph_t->nallotot)  
				pDphsettar->phonex_drawt0 = pDph_t->allophons[pDphsettar->np_drawt0+1];


			/* Set next f0 segmental incremental target */
			tmp = pDphsettar->phocur & PFONT;
			if(tmp == PFUSA<<PSFONT)
			{
				f0seg = us_f0msegtars[pDphsettar->phocur & PVALUE];	
			}
			else if(tmp == PFGR<<PSFONT)
			{
				f0seg = gr_f0msegtars[pDphsettar->phocur & PVALUE];	
			}
			else if(tmp == PFUK<<PSFONT)
			{
				f0seg = uk_f0msegtars[pDphsettar->phocur & PVALUE];	
			}
			else if(tmp == PFLA<<PSFONT)
			{
				f0seg = la_f0msegtars[pDphsettar->phocur & PVALUE];
			}
			else if(tmp == PFSP<<PSFONT)
			{
				f0seg = sp_f0msegtars[pDphsettar->phocur & PVALUE]>>1;
			}
			else if(tmp==PFFR<<PSFONT)
			{
				f0seg = fr_f0msegtars[pDphsettar->phocur & PVALUE];
			//	printf(" f0seg  %d \n",f0seg);
			}
			else if(tmp==PFIT<<PSFONT)
			{
				f0seg = 0;//needtofic fr_f0msegtars[pDphsettar->phocur & PVALUE];
			}
			else if(tmp==PFJP<<PSFONT)
			{
				f0seg = jp_f0segtars[pDphsettar->phocur & PVALUE];
			}
			else if(tmp==PFKR<<PSFONT)
			{
				f0seg = kr_f0msegtars[pDphsettar->phocur & PVALUE];
			}
			else if(tmp==PFCH<<PSFONT)    // added: Reiner
			{
				f0seg = ch_f0msegtars[pDphsettar->phocur & PVALUE];
			}


			pDphsettar->extrad = -DELAY_SEG_LOWPASS;	/* Assume like V-V trans */
			/* so start new target early */
			/*        Delay start of f0 rise for upcoming voiceless segment until boundary */
			if ((phone_feature( pDph_t,pDphsettar->phonex_drawt0) & FVOICD) IS_MINUS) 
			{
				pDphsettar->extrad = 0;			/* All of rise during voicless */
			}

			/*   Delay f0 fall from voiceless plosive until vot (when glottis closes)*/
			if( (phone_feature( pDph_t,pDphsettar->phocur) & FVOICD) IS_MINUS ) 
			{	
				pDphsettar->tarseg1 = f0seg;	/* Gesture fast, go to only 1 lpfilter */
				pDphsettar->tarseg = 0;
				pDphsettar->extrad = 1;			/* -V fric, fall starts at voicing onset */
				if ((phone_feature( pDph_t,pDphsettar->phocur) & FPLOSV) IS_PLUS) 
				{
					pDphsettar->extrad = 5;		/* -V plos, assume VOT = 32 ms */
					if ((pDph_t->allofeats[pDphsettar->np_drawt0] & FSTRESS) IS_MINUS) 
					{
						pDphsettar->extrad = 3;
					}
				}
			}
			else 
			{
				pDphsettar->tarseg = f0seg;	  /* Normal gesture for voiced segments is */
				pDphsettar->tarseg1 = 0;	  /* slow, use both segmental 1-pole filters */
			}
		}

		/*    Glottal stop gesture, test at beginning of each phoneme */
		/* eab 11/22/97 per caroline remove glotalization for UK*/
		//glottal gesture needs f0 - not built into hlsyn today no time to add it now
#ifndef HLSYN
		if( pKsd_t->lang_curr != LANG_chinese &&
			pKsd_t->lang_curr != LANG_japanese && 
			pKsd_t->lang_curr != LANG_korean )
		{
			set_tglst(pDph_t);		
		}
#endif
		/* Set times of f0 fall pDphsettar->tglstp,pDphsettar->tglstn */

		if (pDph_t->f0mode < SINGING) 
		{
			/*	  Filter f0 step and impulse commands to produce next value f0 */
			/* increment gilde towards target and cancel increment when as close as poss to target
			eab 1/21/98 */
			pDphsettar->glide_tot += pDphsettar->glide_inc;

			if(pKsd_t->lang_curr == LANG_british)
			{
				if(pDphsettar->glide_tot && pDphsettar->glide_inc ==0)
					pDphsettar->glide_tot -= (pDphsettar->glide_tot>>4); 
			}

			//WINprintf("male %d  %d %d\n", pDphsettar->glide_tot,pDphsettar->glide_stepamount,pDphsettar->glide_inc );
			pDphsettar->glide_stepamount -= pDphsettar->glide_inc;
			/*EAB 1/10/98 set glide_inc to zero if we've reached target*/
			if(pDphsettar->glide_inc > 0 )
			{
				if ( pDphsettar->glide_stepamount < pDphsettar->glide_inc)
				{
					pDphsettar->glide_stepamount=0;
					pDphsettar->glide_inc =0;
				}
			}
			else
			{
				if(pDphsettar->glide_inc < 0 )
				{
					if ( pDphsettar->glide_stepamount > pDphsettar->glide_inc)
					{
						pDphsettar->glide_stepamount=0;
						pDphsettar->glide_inc =0;
					}
				}
			}

			f0in = (pDph_t->f0minimum + pDphsettar->tarhat + (pDphsettar->tarimp));

		
			filter_seg_commands(pDph_t,pDphsettar->tarseg);		/* Input is pDphsettar->tarseg, output is pDphsettar->f0s */
				
			f0in += pDphsettar->glide_tot;						// Add in glide value

			filter_commands(pDph_t, (short)(f0in));				/* Input is f0in, output is f0  */
		
			/* Add in glide value to F0 eab 1/21/98 */
			// Olivertest 
#ifdef  STEVE_HAWKINGS
			pDph_t->f0prime = pDph_t->f0;// + (pDph_t->f0s>>1);
#else
			if(pKsd_t->lang_curr == LANG_japanese)
				pDph_t->f0prime = pDph_t->f0 + (pDph_t->f0s>>1) ;	/* This will be spdef-scaled output value */
			else if(pKsd_t->lang_curr == LANG_spanish || 
				pKsd_t->lang_curr == LANG_latin_american)
				pDph_t->f0prime = pDph_t->f0 + (pDph_t->f0s>>1);
			else if(pKsd_t->lang_curr == LANG_korean )
			{
				pDph_t->f0prime = pDph_t->f0;	// + pDph_t->f0s;	
			}
			else
				pDph_t->f0prime = pDph_t->f0 + pDph_t->f0s;
			
#endif


			if( pKsd_t->lang_curr != LANG_english && 
				pKsd_t->lang_curr != LANG_korean )
			{
				pDph_t->f0prime -= pDph_t->f0primefall;
			}

			if( pDph_t->f0basefall > pDph_t->f0primefall )
			{
				pDph_t->f0primefall++;
			}

#ifdef CREEKMALE
			if( pDphsettar->nframb >  pDph_t->tcumdur-4
				&& pDph_t->clausetype == DECLARATIVE 
				&& pDph_t->number_words > 5 )
			{
				pDph_t->avcreek = -6;
				pDph_t->f0prime = pDph_t->f0prime >>1;
			}
			else
			{
				pDph_t->avcreek = 0;
			}
#endif

		}
		else 
		{
			/*	  Linear interpolation to 'pDphsettar->newnote' over 100 ms or phoneme duration */
			/*    Add vibratto if pDphsettar->vibsw=1  */
			linear_interp(pDph_t);
		}

		//FNX_PRINTF("phocur %d %d %d F0in %d \n",pDphsettar->phocur, pDphsettar->tarbas, pDph_t->enddrop, pDph_t->f0prime);

		/*    Glottalization gesture */
		/*    F0 dip by 60 Hz linear ramp in 8 frames each direction about pDphsettar->tglstp */
		dtglst = pDphsettar->nframg - pDphsettar->tglstp;
		if(pDph_t->allophons[pDphsettar->npg ] == HEP_NG)
		{
			dtglst -= 5;
		}
		if( pDph_t->allophons[pDphsettar->npg-1 ] == HEP_NG)
		{
			dtglst += 3;
		}

		if (dtglst < 0)
			dtglst = (-dtglst);

		if (dtglst <= 7)
		{
			pDph_t->f0prime += ((dtglst * 70) - 550);
		}

		/*    Add f0 drift or flutter (approx 3 and 5-Hz sine waves, each +/-1.0 Hz) */
		if( pDph_t->f0mode < SINGING) 
		{
			pDphsettar->timecos5 += 131;		/* Prime number to reduce coincidence */
			if (pDphsettar->timecos5 > TWOPI)    pDphsettar->timecos5 -= TWOPI;
			pDphsettar->timecos3 += 79;
			if (pDphsettar->timecos3 > TWOPI)    pDphsettar->timecos3 -= TWOPI;
			pseudojitter = getcosine[pDphsettar->timecos5>>6]
			- getcosine[pDphsettar->timecos3>>6];
			//pDph_t->arg1 = pseudojitter;
			/* eab found flutter is not a speaker def yet*/
			pDph_t->arg2 = 700;//pDph_t->f0flutter;
			/* "FLUTTER" spdef parameter, 10% -> +/-1 Hz, */
#ifndef  STEVE_HAWKINGS
			pDph_t->f0prime += mlsh1(pseudojitter,700);	
#endif
			if(pDph_t->clausetype == 2)
			{
				//	pDph_t->f0prime += mlsh1(pseudojitter,pDph_t->addjit);
				pDph_t->addjit = -pDph_t->addjit;
			}
			/*  100% corresp. to +/- 10 Hz max flutter */
		}

		/*    Introduce variability to period at startup from a voiceless interval */
		/*	not implemented */

		/*    Scale f0 according to current speaker definition, the number 120 is
		*    the nominal average pitch of Paul's voice (AP in spdef)  */

		if (pDph_t->f0mode < SINGING) 
		{
			pDph_t->f0prime = pDph_t->f0minimum	+ (frac4mul((pDph_t->f0prime - pDph_t->f0minimum), pDph_t->f0scalefac));
		}
//		tmp = frac4mul((pDph_t->f0prime - pDph_t->f0minimum), pDph_t->f0scalefac);
//		printf(" factor %d \n", tmp);
		/*    See if f0 exceeds legal bounds, truncate  */
		if (pDph_t->f0prime > HIGHEST_F0) 
		{
			pDph_t->f0prime = HIGHEST_F0;
		}
		else if (pDph_t->f0prime < LOWEST_F0) 
		{
			pDph_t->f0prime = LOWEST_F0;
		}

		/*    Change from Middle C = 256 Hz (A = 430.4) to A = 440 Hz (SHOULD RE-DO */
		/*    TABLE INSTEAD) */
		if (pDph_t->f0mode == SINGING) 
		{
			pDph_t->f0prime = frac4mul(pDph_t->f0prime,4190);
		}

		/*    Save value of period t0 in parameter array  */
		/*    (ONLY ESSENTIAL DIVIDE INSTRUCTION IN ALL OF DECTALK) */
#ifdef MANDF0MACHINE
		if(pKsd_t->lang_curr == LANG_chinese)
		{
#ifdef NEW_MULTI_LANG_ARCH

			pDph_t->f0prime	= phTTS->lts_funcs[phTTS->cur_lts_lang]->Mand_F0_machine(phTTS, MFZ_GET_F0,NULL,pDphsettar->np_drawt0,0,0);
			pDph_t->f0prime += mlsh1(pseudojitter,1100);
			filter_seg_commands(pDph_t,pDphsettar->tarseg);
			pDph_t->f0prime += pDph_t->f0s;
			// ED from Reiner: Please add here segmentally varied F0 changes. Table is defined above 
			// ch_f0msegtars and ch_f0fsegtars. And f0set is set above but only for the male case.

			//printf(" %d \n",mlsh1(pseudojitter, 1100));
#else
			pDph_t->f0prime	= Mand_F0_machine(phTTS, MFZ_GET_F0,NULL,pDphsettar->np_drawt0,0,0);
			pDph_t->f0prime += mlsh1(pseudojitter,1100);
			filter_seg_commands(pDph_t,pDphsettar->tarseg);
			pDph_t->f0prime += pDph_t->f0s;
			//	printf(" %d \n",mlsh1(pseudojitter,1100));
#endif
		}
#endif


#if (defined  INTEGER || !(defined HLSYN) )
		pDph_t->parstochip[OUT_T0]  = muldv(400, 1000, pDph_t->f0prime);	// pass the period
#else
		pDph_t->parstochip[OUT_T0]  = pDph_t->f0prime;		// pass the frequency


		if( pDph_t->tcum == 0 )
		{
#ifdef PH_DEBUG
			if(DT_DBG(PH_DBG,0x200))
			{
						FNX_PRINTF("===================== at phone %d - %s ======================== \n", 
				pDph_t->nphone, (phprint(pDph_t->allophons[pDph_t->nphone])) );
			}
#endif
		}

#ifdef PH_DEBUG
		if(DT_DBG(PH_DBG,0x200))
		{
			FNX_PRINTF(" f0prime: %4d, f0: %4d, f0s (segmental): %3d\n", 
			pDph_t->f0prime, pDph_t->f0, pDph_t->f0s);
		}
#endif

#endif	

		/* debug switch */
		if( (pKsd_t->logflag & LOG_OUTPHON) || 
			DT_DBG(PH_DBG,0x008) ||	
			DT_DBG(PH_DBG,0x004))
		{
			/* if (np == 0 && allophons[np] == GEN_SIL) { lastone=np; }   */
			if (pDphsettar->np_drawt0 != pDphsettar->lastone)
			{
#ifdef MSDBG4 
				FNX_PRINTF("lastone=%d f0prime=%d\n",pDphsettar->lastone,pDph_t->f0prime/10);
				FNX_PRINTF ("allophons[%d]=%d ", pDphsettar->np_drawt0, pDph_t->allophons[pDphsettar->np_drawt0]);
				FNX_PRINTF ("allodurs[%d]=%d\n", pDphsettar->np_drawt0, pDph_t->allodurs[pDphsettar->np_drawt0]*64/10);
#endif
				if ((pDphsettar->np_drawt0 >= 0))
				{

#ifdef MSDOS
					/*WAIT_PRINT;*/
					dologphoneme (pDph_t->allophons[pDphsettar->np_drawt0],
						(pDph_t->allodurs[pDphsettar->np_drawt0] * 64 / 10),
						(pDph_t->f0prime / 10));
					FNX_PRINTF("\n");
					/*SIGNAL_PRINT;*/
#else
					dologphoneme (phTTS, pDph_t->allophons[pDphsettar->np_drawt0],
						(short)  (pDph_t->allodurs[pDphsettar->np_drawt0] * 64 / 10),
						(short) (pDph_t->f0prime / 10));
#ifdef PRINTFDEBUG
					FNX_PRINTF ("\n");
#endif
#ifndef ARM7
					if (pKsd_t->logflag & LOG_OUTPHON)
					{
						if (FNX_FPRINTF (phTTS->pLogFile, "\n") < 0)
						{
							TextToSpeechErrorHandler (phTTS,
								ERROR_WRITING_FILE,
								0L);
						}
					}
#endif
#endif // MSDOS
				}
				/* keepdur = (pDph_t->allodurs[pDphsettar->np_drawt0] * NSAMP_FRAME / 10); */		/* eab need to keep orig value of dur */ 
				/* keepallo = pDph_t->allophons[pDphsettar->np_drawt0]; */
				pDphsettar->lastone = pDphsettar->np_drawt0;
			}
		}

		/*    Increment time counters */
		pDphsettar->nfram++;
		pDphsettar->nframs++;
		pDphsettar->nframg++;

	}	/*end of if malfem==male*/
	else
	{
		if (pDph_t->nf0ev <= -2) 
		{
			/* Hard initialization */
			/* for now hardcode baseline for init experimentation eab 8/96*/
			/* eab BUG- found problem with f0command, it needs to be a global variable
			or it sometimes doesn't get handled correctly*/
			pDph_t->clausepos=0;
			pDphsettar->phocur = GEN_SIL;

			/*Question*/
			pDph_t->glotalize =0;
			pDphsettar->glide_stepamount=0;

			/*        Time since last reset of baseline fall, in frames */
			pDphsettar->nframb = 0;
			pDphsettar->drift =0;
			pDph_t->f0primefall =0;
			pDph_t->f0primefalldelta = pDph_t->f0basefall/pDph_t->tcumdur;

			pDphsettar->basetime =0;
			pDphsettar->basecntr =0;
			pDphsettar->f0delta =0;

			/*eab 4/11/97 Moved these variables to a proper place of initlaization*/
			pDphsettar->timecos10=0; pDphsettar->timecos15=0; pDphsettar->timecosvib=0;	

			/*        If within 32 ms (5 frames) of nframg, glottal stop gesture */
			/*        is in progress */
			pDphsettar->tglstp = -200;

			/*        Set filter memory to init baseline fall (f0 in hz*10) */
			/* eab 7/22/98 changed to >>1 to account for scaling of female voice*/
			pDphsettar->f0las1 = pDph_t->f0minimum<< F0SHFT;
			pDphsettar->f0las2 = pDph_t->f0minimum<< F0SHFT;
			//		oarcnt = 0;
			pDphsettar->f0slas1 = 0;	/* Segmental filter avg output is zero */
			pDphsettar->f0slas2 = 0;
			pDph_t->f0 = pDphsettar->f0basestart;
			pDphsettar->tarhat = 0;
			pDphsettar->tarimp = 0;
			pDphsettar->delimp = 0;

			/*      Set smoothing constants for ( critical-damped? ) 2nd-order sys  */

			pDphsettar->f0a2 = pDph_t->f0_lp_filter;	/* Impulse and hat commands */
			pDphsettar->f0b = FRAC_ONE - pDphsettar->f0a2;
			pDphsettar->f0a1 = pDphsettar->f0a2 << F0SHFT;

			pDphsettar->f0sa2 =  F_SEG_LOWPASS;	/* Segmental influences */

			pDphsettar->f0sb = FRAC_ONE - pDphsettar->f0sa2;
			pDphsettar->f0sa1 = pDphsettar->f0sa2 << F0SHFT;

			/*      Variables  relevent only if f0mode >= SINGING */

			pDphsettar->newnote = pDphsettar->f0basestart;
			pDphsettar->delnote = 0;
			pDphsettar->delcum = 0;
			pDphsettar->f0start = pDph_t->f0;
			pDphsettar->vibsw = 0;
			pDph_t->f0 = pDph_t->f0minimum;	
			/*      Initialize pointer to f0 command string */

			pDph_t->nf0ev = -1;
		}

		/*    Reinit pointer and time of first f0 command if new clause */
		if( pDph_t->nf0ev == -1 ) 
		{		
			/* Soft initialization */
			pDphsettar->nimpcnt = 0;
			pDphsettar->tarimp =0;
			pDph_t->enddrop =0;


			pDphsettar->nframb = 0;
			pDphsettar->drift =0;
			pDphsettar->basetime=0;
			pDphsettar->basecntr =0;
			pDphsettar->f0delta =0;
			pDph_t->special_phrase = 0;
			//		oarcnt=0;
			/*	  Raise baseline for first sentence of a paragraph */
			if (pDph_t->newparagsw != FALSE) 
			{
				pDphsettar->beginfall += 120;
				pDphsettar->endfall += 70;
				pDph_t->newparagsw = FALSE;
			}

			/*        Time between 0 and first  f0 command, in frames */
			pDphsettar->dtimf0 = pDph_t->f0tim[0];
			/*         Pointer into dur and phone arrays */
			pDphsettar->np_drawt0 = -1;
			pDphsettar->npg = -1;
			pDph_t->nf0ev = 0;



			/*        Time since last f0 command, in frames */

			/* INITIALIZE NFRAM TO DELAY THROUGH FILTER THIS USED TO BE IN AND WAS NOT IN
			88 STUFF BUT IS REALLY NEEDED*/
			//		oarcnt=0;
			pDphsettar->nframs = 0;
			pDphsettar->nfram =  0;
			pDphsettar->nframg = 0;//6- ((pDph_t->f0_lp_filter-1300)>>8);
			pDph_t->f0primefall =0;
			pDph_t->f0primefalldelta = pDph_t->f0basefall/pDph_t->tcumdur;		

			pDph_t->f0 = pDph_t->f0minimum;

			if (pDph_t->f0mode< SINGING) 
			{
				pDphsettar->nfram = pDphsettar->nframs >> 1;
			}
			else 
			{
				pDphsettar->nfram = 0;	/* Start note slightly early if singing */
			}

			pDphsettar->f0slas1 = 0;
			pDphsettar->f0slas2 = 0;

			pDphsettar->nframs = 0;		
			/* Used in computing segmental effects */


			/*        Extra time, in frames, used to delay or advance f0 gesture assoc. */
			/*        with a particular segment, e.g. at delayed vot, or anticipate in V-V */
			pDphsettar->extrad = -DELAY_SEG_LOWPASS; /* Start gesture toward next seg early */
			/*        Duration of current segment, in frames */
			pDphsettar->segdur = 0;
			pDphsettar->segdrg = 0;
			pDph_t->lastallo=0;
			pDph_t->keepallo=0;
#ifdef GFAPHF0
			pDph_t->lastone=-1;
			pDph_t->keepdur=0;
#endif
			pDph_t->glotalize =0;
			pDphsettar->glide_stepamount=0;
			pDphsettar->glide_tot=0;
			pDphsettar->glide_inc =0;
			/*	  Must be at bottom of hat */
			pDphsettar->tarhat = 0;	    /* should be anyway, except for emergency halt */
			pDph_t->addjit = 305;


		}
		/*    End of initialization */



		/*  See if new f0 commands issued					*/
		/*    To get f0 commands to occur at right times, need to take		*/
		/*    into account delay introduced by low-pass filter. Response to	*/
		/*    a step command begins xx frames earlier than f0time[] request	*/
		/*    so f0 gets half-way to target at nominal step onset time		*/

		while ((pDphsettar->nframb >= pDphsettar->dtimf0) && 
			(pDph_t->nf0ev < pDph_t->nf0tot)) 
		{

			pDphsettar->f0command = pDph_t->f0tar[pDph_t->nf0ev];	/* New target f0 */
			pDphsettar->type = pDph_t->f0type[pDph_t->nf0ev];
			pDphsettar->nfram -= pDphsettar->dtimf0;
			/* eab 1/10/98 added length parameter*/
			pDphsettar->length = pDph_t->f0length[pDph_t->nf0ev];

			if (pDph_t->f0mode== TIME_VALUE_SPECIFIED) {
				pDphsettar->dtimf0 = pDph_t->f0tim[pDph_t->nf0ev];
				pDph_t->nf0ev++;
				set_user_target(pDph_t,&pDphsettar->f0command);
			}
			else {
				pDph_t->nf0ev++;	/* Achieve target at next time */
				pDphsettar->dtimf0 = pDph_t->f0tim[pDph_t->nf0ev];
				switch(pDphsettar->type)
				{
				case USER: /*user specified f0 target*/
					set_user_target(pDph_t,&pDphsettar->f0command);
					break;

				case F0_RESET: /* f0 reset*/

					pDphsettar->tarhat = 0;		/* Go to bottom of hat pattern 
												and for UK init glide, note glide is not ifdefed _uk becuase
												it is a command we ant to allow others to use*/
					pDph_t->glotalize =0;
					//pDphsettar->glide_stepamount=0;
					//pDphsettar->glide_tot=0;
					//pDphsettar->glide_inc=0;
					break;
				case STEP:
					if (pKsd_t->lang_curr == LANG_british)
						break;

					pDphsettar->tarhat += pDphsettar->f0command;
					/* Command is a step, reset pDphsettar->tarhat */

					if (pDphsettar->f0command < 0) 
					{	/* Cancel previous impulse if step */
						/* is of opposite sign */
						if (pDphsettar->tarimp > 0) 
						{   
							pDphsettar->tarimp = 0;
							pDphsettar->delimp = 0;
						}
					}
					else
					{
						if (pDphsettar->tarimp < 0) 
						{
							pDphsettar->tarimp = 0;
							pDphsettar->delimp = 0;
						}
					}
					break;
				case GLIDE:/* eab 1/10/98 work in progress */
					if(pDphsettar->glide_stepamount !=0)
						//last command interrupted by new command adjust
						tmp =  pDphsettar->glide_stepamount;
					else
						tmp=0;
					pDphsettar->glide_stepamount = pDphsettar->f0command+tmp;
					//		pDphsettar->glide_stepamount = pDphsettar->f0command;
					pDphsettar->glide_inc =(pDphsettar->glide_stepamount/pDphsettar->length);

					break;

				case GLOTTAL:
					if (pKsd_t->lang_curr == LANG_british)
						break;

					pDph_t->enddrop= -pDphsettar->f0command;
					pDph_t->glotalize =1;
					break; //BATS 704	
				case IMPULSE:

					/* Odd, command is impulse  */
					/*	          Impulse realized as 24-frame "step plus ramp" from f0command */
					/*	          to three times focommand */
					/* eab old ocde used to have an impulse as a 2*f0command that would be realized as an 
					16 frame wide pulse. This new scheme proposed by Dennis Klatt uses 
					imp=f0command+(f0command _ f0command>>4 meaning it will take 16 farmes to
					reach double height. The old one never reached target so this new approach I think 
					presently has two problems it's dealyed too much and it lasts too long causing higher f0 values
					and more percieved effect. I want to try it differently starting out close to the old code with a pulse command that 
					trails off.
					with a downward slope think of it as a rectangular pulse with a triangle placed on
					top instead of a second rectangular pulse- by the way it's not working correctly at
					the moment*/

					pDphsettar->tarimp = pDphsettar->f0command;

					//pDphsettar->delimp = pDphsettar->f0command>>1;
					// pDphsettar->nimp = 24 - ((pDph_t->f0_lp_filter-1300)>>8);
					pDphsettar->nimp = pDphsettar->length;
					pDphsettar->delimp = (pDphsettar->f0command/pDphsettar->nimp)<<1;
					pDphsettar->nimpcnt = 0;
					break;

				}
			}

			/*        Loop back to look for more f0 commands */
		}

		pDphsettar->nframb++;

		if (pDphsettar->nimpcnt == (pDphsettar->nimp)) {
			pDphsettar->nimpcnt = 0;
			pDphsettar->tarimp = 0;
			pDphsettar->delimp = 0;
			pDphsettar->nimp = 0;
		}
		else  if (pDphsettar->nimpcnt <= (pDphsettar->nimp>>1)) {
			//pDphsettar->nimp--;
			pDphsettar->tarimp += pDphsettar->delimp;
			//pDphsettar->nimp = 0;
			pDphsettar->nimpcnt++;
		}
		else
		{
			pDphsettar->nimpcnt++;
			pDphsettar->tarimp -= pDphsettar->delimp;
		}

		/*    Segmental effect on f0, reset pDphsettar->tarseg if time exceeds cum dur */
		if( pDphsettar->nframs >= (pDphsettar->segdur + pDphsettar->extrad) &&
			pDphsettar->np_drawt0 < (pDph_t->nallotot-1) ) 
		{
				pDphsettar->nframs -= pDphsettar->segdur;
				pDphsettar->segdur = pDph_t->allodurs[++pDphsettar->np_drawt0];
				pDphsettar->phocur = pDph_t->allophons[pDphsettar->np_drawt0];
				/* EAB Found long standing bug-- due to the compensation for the delay through the filters
				the first phoneme is getting cheated on duration */
				if(pDphsettar->np_drawt0 == 1)
				{
					pDphsettar->nframs = -DELAY_SEG_LOWPASS;
				}

				if (pDphsettar->np_drawt0 < pDph_t->nallotot)  
					pDphsettar->phonex_drawt0 = pDph_t->allophons[pDphsettar->np_drawt0+1];


				/*        Set next f0 segmental incremental target */
				tmp = pDphsettar->phocur & PFONT;
				if(tmp == PFUSA<<PSFONT)
				{
					f0seg = us_f0fsegtars[pDphsettar->phocur & PVALUE];	
				}
				else if(tmp == PFGR<<PSFONT)
				{
					f0seg = gr_f0fsegtars[pDphsettar->phocur & PVALUE];	
				}
				else if(tmp == PFUK<<PSFONT)
				{
					f0seg = uk_f0fsegtars[pDphsettar->phocur & PVALUE];	
				}
				else if(tmp == PFLA<<PSFONT)
				{
					f0seg = la_f0fsegtars[pDphsettar->phocur & PVALUE];
				}
				else if(tmp == PFSP<<PSFONT)
				{
					f0seg = sp_f0fsegtars[pDphsettar->phocur & PVALUE];
				}
				else if(tmp == PFIT<<PSFONT)
				{
					f0seg = 0;//sp_f0fsegtars[pDphsettar->phocur & PVALUE];
				}
				else if(tmp == PFJP<<PSFONT)
				{
					f0seg = jp_f0segtars[pDphsettar->phocur & PVALUE];
				}
				else if(tmp == PFFR<<PSFONT)
				{
					f0seg = fr_f0fsegtars[pDphsettar->phocur & PVALUE];
				}
				else if(tmp == PFKR<<PSFONT)
				{
					f0seg = kr_f0fsegtars[pDphsettar->phocur & PVALUE];
				}
				else
					f0seg = 0;

				//reduce vowel height effect for japanese
				if( pKsd_t->lang_curr == LANG_japanese &&
					(phone_feature( pDph_t,pDph_t->allophons[pDphsettar->npg]) & FVOWEL) IS_PLUS)
				{
					f0seg = f0seg>>2;
				}


				/*	  Effect is half as much in unstressed segments */
				pDphsettar->extrad = -DELAY_SEG_LOWPASS;	/* Assume like V-V trans */
				/* so start new target early */
				/*        Delay start of f0 rise for upcoming voiceless segment until boundary */
				if ((phone_feature( pDph_t,pDphsettar->phonex_drawt0) & FVOICD) IS_MINUS) {
					pDphsettar->extrad = 0;			/* All of rise during voicless */
				}
				/*        Delay f0 fall from voiceless plosive until vot (when glottis closes)*/
				//ah but this goofs up onset into voicelee it should be phocur -1 I think
				if ((phone_feature( pDph_t,pDph_t->allophons[pDphsettar->np_drawt0-1]) & FVOICD) IS_MINUS) 
				{	
					pDphsettar->tarseg1 = f0seg;  /* Gesture fast, go to only 1 lpfilter */
					pDphsettar->tarseg = 0;
					pDphsettar->extrad = 1;	/* -V fric, fall starts at voicing onset */
					if ((phone_feature( pDph_t,pDphsettar->phocur) & FPLOSV) IS_PLUS) 
					{
						pDphsettar->extrad = 5;		/* -V plos, assume VOT = 32 ms */
						if ((pDph_t->allofeats[pDphsettar->np_drawt0] & FSTRESS) IS_MINUS) 
						{
							pDphsettar->extrad = 3;
						}
					}
				}
				else {
					pDphsettar->tarseg = f0seg;	  /* Normal gesture for voiced segments is */
					pDphsettar->tarseg1 = 0;	  /* slow, use both segmental 1-pole filters */
				}
		}

		/*    Glottal stop gesture, test at beginning of each phoneme */
		/* eab 11/22/97 per caroline remove glotalization */
#ifndef HLSYN
		if( pKsd_t->lang_curr != LANG_japanese && 
			pKsd_t->lang_curr != LANG_chinese && 
			pKsd_t->lang_curr != LANG_korean )
		{
			set_tglst(pDph_t);		
		}

#endif

		/* Set times of f0 fall pDphsettar->tglstp,pDphsettar->tglstn */

		if (pDph_t->f0mode< SINGING) {

			/*	  Filter f0 step and impulse commands to produce next value f0 */
			/* increment gilde towards target and cancel increment when as close as poss to target
			eab 1/21/98 */
			pDphsettar->glide_tot += pDphsettar->glide_inc;
			if (pKsd_t->lang_curr == LANG_british)
			{
				if(pDphsettar->glide_tot && pDphsettar->glide_inc ==0)
					pDphsettar->glide_tot -= (pDphsettar->glide_tot>>4);
			}

			pDphsettar->glide_stepamount -= pDphsettar->glide_inc;

			/*EAB 1/10/98 set glide_inc to zero if we've reached target*/
			if(pDphsettar->glide_inc > 0 )
			{
				if ( pDphsettar->glide_stepamount <= pDphsettar->glide_inc)
				{
					pDphsettar->glide_stepamount=0;
					pDphsettar->glide_inc =0;
				}
			}
			else
				if(pDphsettar->glide_inc < 0 )
				{
					if ( pDphsettar->glide_stepamount >= pDphsettar->glide_inc)
					{
						pDphsettar->glide_stepamount=0;
						pDphsettar->glide_inc =0;
					}
				}


				f0in = (pDph_t->f0minimum + pDphsettar->tarhat + pDphsettar->tarimp);

				/*	  Reduce segmental tongue height effect of sonorants toward */
				/*	  end of segment (98% per frame)  */

			

				filter_seg_commands(pDph_t,pDphsettar->tarseg);	/* Input is pDphsettar->tarseg, output is pDphsettar->f0s */
				f0in += pDphsettar->glide_tot;					// Add in glide value

				filter_commands(pDph_t, (short)(f0in));			// Input is f0in, output is f0
				
				// Add in segmental effects
				if(pKsd_t->lang_curr == LANG_japanese)
					pDph_t->f0prime = pDph_t->f0 + (pDph_t->f0s>>1) ;	/* This will be spdef-scaled output value */
				else if(pKsd_t->lang_curr == LANG_spanish || 
					pKsd_t->lang_curr == LANG_latin_american)
					pDph_t->f0prime = pDph_t->f0 + (pDph_t->f0s>>1);
				else if(pKsd_t->lang_curr == LANG_korean )
					pDph_t->f0prime = pDph_t->f0;	// + pDph_t->f0s;
				else
					pDph_t->f0prime = pDph_t->f0 + (pDph_t->f0s>>2);	

				if( pKsd_t->lang_curr != LANG_english && 
					pKsd_t->lang_curr != LANG_korean )
				{
					pDph_t->f0prime -= pDph_t->f0primefall;
				}

				if(pDph_t->f0basefall > pDph_t->f0primefall)
					pDph_t->f0primefall++;

#ifdef CREEKFEMALE
				if( pDphsettar->nframb >  pDph_t->tcumdur-4 
					&& pDph_t->clausetype == DECLARATIVE 
					&& pDph_t->number_words > 5)
				{
					pDph_t->avcreek = -6;
					pDph_t->f0prime = pDph_t->f0prime >>1;
				}
				else
				{
					pDph_t->avcreek = 0;
				}

				//	WINprintf( "phocur %d %d %d F0in %d \n",pDphsettar->phocur, pDphsettar->tarbas, pDph_t->enddrop, pDph_t->f0prime);
#endif

		}

		else 
		{
			/*	  Linear interpolation to 'pDphsettar->newnote' over 100 ms or phoneme duration */
			/* Add vibratto if pDphsettar->vibsw=1  */
			linear_interp(pDph_t);
		}

		/*    Glottalization gesture */
		/*    F0 dip by 60 Hz linear ramp in 8 frames each direction about pDphsettar->tglstp */
		dtglst = pDphsettar->nframg - pDphsettar->tglstp;
		if (dtglst < 0)
			dtglst = (-dtglst);

		if (dtglst <= 7)
		{
			pDph_t->f0prime += ((dtglst * 70) - 550);
		}


		/*	  And reduce AV somewhat (ugly code, but F0 computed before AV) */
		if (dtglst <= 5) 
		{
			pDph_t->avglstop = (6 - dtglst);	/* Global variable, used in PHDRAW.C */
		}
		else 
		{
			pDph_t->avglstop = 0;
		}

		/*    Add f0 drift or flutter (approx 3 and 5-Hz sine waves, each +/-1.0 Hz) */
		if (pDph_t->f0mode < SINGING) 
		{
			pDphsettar->timecos5 += 131;		/* Prime number to reduce coincidence */
			if (pDphsettar->timecos5 > TWOPI)    pDphsettar->timecos5 -= TWOPI;
			pDphsettar->timecos3 += 79;
			if (pDphsettar->timecos3 > TWOPI)    pDphsettar->timecos3 -= TWOPI;
			pseudojitter = getcosine[pDphsettar->timecos5>>6] - getcosine[pDphsettar->timecos3>>6];
			pDph_t->arg1 = pseudojitter;
			pDph_t->arg2 = 700;	//pDph_t->f0flutter;//4/16/98 eab higher for female voice
			/* "FLUTTER" spdef parameter, 10% -> +/-1 Hz, */
			pDph_t->f0prime += mlsh1(pDph_t->arg1,pDph_t->arg2);	
			/*  100% corresp. to +/- 10 Hz max flutter */
		}

		/*    Introduce variability to period at startup from a voiceless interval */
		/*	  not implemented */

		/*    Scale f0 according to current speaker definition, the number 120 is
		*    the nominal average pitch of Paul's voice (AP in spdef)  */
		if (pDph_t->f0mode< SINGING) 
		{
			if(pDph_t->clausetype == 2)
			{
				pDph_t->f0prime = pDph_t->f0minimum	+ frac4mul((pDph_t->f0prime - pDph_t->f0minimum), pDph_t->f0scalefac+500);
			}
			else
			{
				pDph_t->f0prime = pDph_t->f0minimum	+ frac4mul((pDph_t->f0prime - pDph_t->f0minimum), pDph_t->f0scalefac);
			}
		}

		/*    See if f0 exceeds legal bounds, truncate  */
		if (pDph_t->f0prime > HIGHEST_F0) 
		{
			pDph_t->f0prime = HIGHEST_F0;
		}
		else if (pDph_t->f0prime < LOWEST_F0) 
		{
			pDph_t->f0prime = LOWEST_F0;
		}

		/*    Change from Middle C = 256 Hz (A = 430.4) to A = 440 Hz (SHOULD RE-DO */
		/*    TABLE INSTEAD) */
		if (pDph_t->f0mode== SINGING) 
		{
			pDph_t->f0prime = frac4mul(pDph_t->f0prime,4190);
		}

#ifdef MANDF0MACHINE
		if(pKsd_t->lang_curr == LANG_chinese)
		{
#ifdef NEW_MULTI_LANG_ARCH
			pDph_t->f0prime = phTTS->lts_funcs[phTTS->cur_lts_lang]->Mand_F0_machine(phTTS, MFZ_GET_F0,NULL,pDph_t->f0prime,0,0);
			pDph_t->f0prime += mlsh1(pseudojitter,700);
			filter_seg_commands(pDph_t,pDphsettar->tarseg);
			pDph_t->f0prime += pDph_t->f0s;
#else
			pDph_t->f0prime	= Mand_F0_machine(phTTS, MFZ_GET_F0,NULL,pDphsettar->np_drawt0,0,0);
			pDph_t->f0prime += mlsh1(pseudojitter,1100);
			filter_seg_commands(pDph_t,pDphsettar->tarseg);
			pDph_t->f0prime += pDph_t->f0s;
			//	printf(" %d \n",mlsh1(pseudojitter,1100));
#endif
		}
#endif
		//	temp = muldv(400, 1000, pDph_t->f0prime);

#if (defined  INTEGER || !(defined HLSYN) )
		pDph_t->parstochip[OUT_T0]  = muldv(400, 1000, pDph_t->f0prime);
#else
		pDph_t->parstochip[OUT_T0]  =  pDph_t->f0prime;
//		PH_DEBUG_2010_P1(" f0prime: %d\n", pDph_t->f0prime);
#endif	

		/* debug switch */
		if( ((pKsd_t->logflag) & LOG_OUTPHON) || 
			DT_DBG(PH_DBG,0x008))
		{
#ifdef MSDBG4
			if (pDphsettar->lastone==-1)
			{
				for (keepdur=0;keepdur<TOT_ALLOPHONES;keepdur++)
				{
					FNX_PRINTF("phone#=%d == %c%c\n",keepdur,pKsd_t->arpabet[keepdur <<1],pKsd_t->arpabet[(keepdur <<1)+1]);
				}  
			}
#endif
			/* if (np == 0 && allophons[np] == GEN_SIL) { lastone=np; }                  */
			if (pDphsettar->np_drawt0 != pDphsettar->lastone)
			{
#ifdef MSDBG4 
				FNX_PRINTF("lastone=%d f0prime=%d\n",pDphsettar->lastone,pDph_t->f0prime/10);
				FNX_PRINTF ("allophons[%d]=%d ", pDphsettar->np_drawt0, pDph_t->allophons[pDphsettar->np_drawt0]);
				FNX_PRINTF ("allodurs[%d]=%d\n", pDphsettar->np_drawt0, pDph_t->allodurs[pDphsettar->np_drawt0]*64/10);
#endif
				if ((pDphsettar->np_drawt0 >= 0))
				{

#ifdef MSDOS
					/*WAIT_PRINT;*/
					dologphoneme (pDph_t->allophons[pDphsettar->np_drawt0],
						(pDph_t->allodurs[pDphsettar->np_drawt0] * 64 / 10),
						(pDph_t->f0prime / 10));
					FNX_PRINTF("\n");
					/*SIGNAL_PRINT;*/
#else
					dologphoneme (phTTS, pDph_t->allophons[pDphsettar->np_drawt0],
						(short)(pDph_t->allodurs[pDphsettar->np_drawt0] * 64 / 10),
						(short)(pDph_t->f0prime / 10));  // NAL warning removal
#ifdef PRINTFDEBUG
					FNX_PRINTF ("\n");
#endif
#ifndef ARM7
					if (pKsd_t->logflag & LOG_OUTPHON)
					{
						if (FNX_FPRINTF (phTTS->pLogFile, "\n") < 0)
						{
							TextToSpeechErrorHandler (phTTS,
								ERROR_WRITING_FILE,
								0L);
						}
					}
#endif
#endif // MSDOS
				}
				/* keepdur = (pDph_t->allodurs[pDphsettar->np_drawt0] * NSAMP_FRAME / 10); */		/* eab need to keep orig value of dur */ 
				/* keepallo = pDph_t->allophons[pDphsettar->np_drawt0]; */
				pDphsettar->lastone = pDphsettar->np_drawt0;
			}
		}

		/*    Increment time counters */
		pDphsettar->nfram++;
		pDphsettar->nframs++;
		pDphsettar->nframg++;

	} /* end of fem stuff*/

}	// pht0draw

/* ******************************************************************
 *      Function Name: set_user_target()
 *
 *      Description: Set user target
 *
 *      Arguments:	PDPH_T pDph_t
 *					short *psF0command
 *
 *      Return Value: void
 *
 *      Comments:
 *
 ******************************************************************/
static void set_user_target(PDPH_T pDph_t, short *psF0command)
{
	short trandur=0;
    PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;
	int tmp;

	if (*psF0command > 1500)  
	{
		tmp = 	(*psF0command / 1000);
		if(tmp > 0)
		{
		tmp = (6-tmp)*100;
		pDph_t->spressure = tmp;
		}
		else
		{
			pDph_t->spressure =0;
		}
	}
	*psF0command = *psF0command%1000;   /* 2000 is offset flag */
	
	
	if (*psF0command <= 37) 
	{	/* Pointer to C5, highest possible sung note */
		
		pDphsettar->newnote = notetab[*psF0command-1];
		pDphsettar->vibsw = 1;
		/*	  Set pDphsettar->delnote*4 so transition happens over 16 frames (100 ms) */
		pDphsettar->delnote = ((pDphsettar->newnote - pDph_t->f0) >> 2);
	}
	else {						/* Straight-lines */
		*psF0command *= 10;
		if (*psF0command < LOWEST_F0) 
		{
			*psF0command = LOWEST_F0;
		}
		else if (*psF0command > HIGHEST_F0) 
		{
			*psF0command = HIGHEST_F0;
		}
		pDphsettar->newnote = *psF0command;
		pDphsettar->vibsw = 0;
		/*	  Compute duration of linear transition */
		if (pDph_t->f0mode== TIME_VALUE_SPECIFIED) {
			trandur = pDphsettar->dtimf0;	
			/*		Dur since last f0 command		*/
			/* OUT		FNX_PRINTF("trandur = %d, target=%d, curf0=%d\n",
			trandur, pDphsettar->newnote, f0);  END OUT */
			if (trandur == 0)  
				pDph_t->f0 = pDphsettar->newnote;
		}
		else {	
#ifdef TOMBUCHLER
			trandur = 8;
#else
			trandur = pDph_t->allodurs[pDphsettar->npg+1];	/* Dur of cur phoneme */
#endif
		}
		/*	  Compute incremental change to f0*10 every frame */
		pDphsettar->delnote = (pDphsettar->newnote - pDph_t->f0) << 2;	/* f0 change times 40 */
		if (pDphsettar->delnote > 0) {
			pDphsettar->delnote += (trandur - 1);	/* Round upward */
		}
		if (pDphsettar->delnote < 0) {
			pDphsettar->delnote -= (trandur - 1);	/* Round downward */
		}
		if (trandur != 0) {
			pDphsettar->delnote /= trandur;
		}
		/*	  ELSE INSTANTANEOUS JUMP, was  8-frame (50 ms) transition */
		/*	  OUT	    else {
		pDphsettar->delnote = pDphsettar->delnote >> 1;
		}
		END OUT */
	}
	pDphsettar->delcum = 0;
	pDphsettar->f0start = pDph_t->f0;
}

/* ******************************************************************
 *      Function Name: set_tglst()
 *
 *      Description: 
 *
 *      Arguments:	PDPH_T pDph_t
 *
 *      Return Value: void
 *
 *      Comments:
 *
 * *****************************************************************/
static void set_tglst(PDPH_T pDph_t)
{
PKSD_T pKsd_t = ((LPTTS_HANDLE_T)(pDph_t->phTTS))->pKernelShareData;
	PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;
	
	if (pDphsettar->nframg >= pDphsettar->segdrg) {
		pDphsettar->nframg -= pDphsettar->segdrg;
		pDphsettar->segdrg = pDph_t->allodurs[++pDphsettar->npg];
		/*        Cancel glottal stop gesture that occurred at last phone onset */
		if (pDphsettar->tglstp == 0)    
			pDphsettar->tglstp = -200;
		/*        Start second half of glottal stop gesture */
		if (pDphsettar->tglstp > 0) 
		{
			pDphsettar->tglstp = 0;
		}

		/*        Insert glottal stop after cur seg */
		/*         if next segment a vowel? */
		/*         and is next segment in first syllable? */
		/*         and is current segment in word-final rime? */
		/*         and is next segment not the diphthong /YU/? */
		pDphsettar->tglstn = -200;
		//new rule 8/14/01 don't do it with a functor
		//8/15/01 too broad narrow it to a and an...
#ifdef  STEVE_HAWKINGS
		if ( ((phone_feature( pDph_t,pDph_t->allophons[pDphsettar->npg+1]) & FSYLL) IS_PLUS)
				&& pDphsettar->npg+1 == 1)
		{
				pDphsettar->tglstn = pDphsettar->segdrg;
			}
#else
		if(pKsd_t->lang_curr == LANG_japanese)
		{
		if(pDph_t->allophons[pDphsettar->npg ] == JP_EN)
			pDphsettar->tglstn = pDphsettar->segdrg;

		}
		else
		{

		if(pDph_t->allofeats[pDphsettar->npg-1] & F_FUNC )
		{
			//an
			if(pDph_t->allophons[pDphsettar->npg] == USP_N
				&& pDph_t->allophons[pDphsettar->npg-1] == USP_EH
				&& (pDph_t->allofeats[pDphsettar->npg-1] & FBOUNDARY) >= FWBNEXT)
						return;
			//a 
			if(pDph_t->allophons[pDphsettar->npg] == USP_AX
				&& (pDph_t->allofeats[pDphsettar->npg] & FBOUNDARY) >= FWBNEXT)
						return;

		}
		if (((phone_feature( pDph_t,pDph_t->allophons[pDphsettar->npg+1]) & FVOWEL) IS_PLUS)
			&& ((pDph_t->allofeats[pDphsettar->npg+1] & (FMEDIALSYL & FFINALSYL)) IS_MINUS)
			&& ((pDph_t->allofeats[pDphsettar->npg] & FBOUNDARY) >= FWBNEXT)
			&& (pDph_t->allophons[pDphsettar->npg+1] != USP_YU)) {
			/*	      If cur seg is vowel, don't do it unless vowel ident, or pbound */
			if ((phone_feature( pDph_t,pDph_t->allophons[pDphsettar->npg]) & FSYLL) IS_PLUS) {
				if (((pDph_t->allophons[pDphsettar->npg] == pDph_t->allophons[pDphsettar->npg+1])
					&& ((pDph_t->allofeats[pDphsettar->npg+1] & FSTRESS_1) IS_PLUS) )
					|| ((pDph_t->allofeats[pDphsettar->npg] & FBOUNDARY) >= FVPNEXT)) {
					pDphsettar->tglstn = pDphsettar->segdrg;
				}
			}
			/*	      If  next segment primary stressed, */
			/*	      and if curr seg a consonant other than a plosive, do it */
			//need new method getting into trouble
			else if ( ((phone_feature( pDph_t,pDph_t->allophons[pDphsettar->npg]) & FPLOSV) IS_MINUS)
				&& (pDph_t->allophons[pDphsettar->npg] != USP_DX)
				&& ((pDph_t->allofeats[pDphsettar->npg+1] & FSTRESS_1) IS_PLUS) ) {
				pDphsettar->tglstn = pDphsettar->segdrg;
			}
		}
		/*        And at beginning and end of glottalized segs TQ and Q */
        //    if ((pDph_t->gl_phones[pDph_t->gl_lang][pDph_t->gl_group].phonames[pDph_t->allophons[pDphsettar->npg+1]].place & FGLOTTAL) IS_PLUS) {
		//      pDphsettar->tglstn = pDphsettar->segdrg;
		
		//}
		//if ((pDph_t->gl_phones[pDph_t->gl_lang][pDph_t->gl_group].phonames[pDph_t->allophons[pDphsettar->npg]].place & FGLOTTAL) IS_PLUS) 
		//{
		//  pDphsettar->tglstn = pDphsettar->segdrg;
		//}
		//wrong! fix later

		

	//	if((pDphsettar->npg + 1 <= pDph_t->nallotot) &&
	//		(place(pDph_t->allophons[pDphsettar->npg + 1] ) & FGLOTTAL) IS_PLUS
	//		&& pDph_t->allophons[pDphsettar->npg +1] != HEP_NG)
	//	{
	//		pDphsettar->tglstn = pDphsettar->segdrg;
	//	}
		
		if ((place(pDph_t->allophons[pDphsettar->npg]) & FGLOTTAL) IS_PLUS
			&& pDph_t->allophons[pDphsettar->npg ] != HEP_NG)
		{
			pDphsettar->tglstn = pDphsettar->segdrg;
		}
		if(pDph_t->allophons[pDphsettar->npg ] == HEP_NG)
			pDphsettar->tglstn = pDphsettar->segdrg;

	}
#endif
}

	/*    Wait until current gl stop gesture over before setting time of next one */
	else if ((pDphsettar->nframg == 8) || (pDphsettar->nframg == (pDphsettar->segdrg - 1))) 
	{
		pDphsettar->tglstp = pDphsettar->tglstn;
	}
}

/*******************************************************************
 *      Function Name: filter_commands()
 *
 *      Description: Filter-hat / Impulse-commands
 *
 *      Arguments:	PDPH_T pDph_t
 *					short f0in
 *
 *      Return Value: void
 *
 *      Comments:
 *
 ******************************************************************/

static void filter_commands(PDPH_T pDph_t,short f0in) 
{	/* Convert 'f0in' command to smoothed 'f0' */
//	short f0outa, f0outb, f0outc, f0outd, f0out1, f0out2;
	PKSD_T pKsd_t = ((LPTTS_HANDLE_T)(pDph_t->phTTS))->pKernelShareData;

	PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;

if(pKsd_t->lang_curr == LANG_german
   || pKsd_t->lang_curr == LANG_spanish
   || pKsd_t->lang_curr == LANG_english
   || pKsd_t->lang_curr == LANG_french
    || pKsd_t->lang_curr == LANG_latin_american)
{
		short f0outa, f0outb, f0outc, f0outd, f0out1, f0out2;

	/*    First pole (separate into 2 poles to min truncation errors) */
	pDph_t->arg1 = pDphsettar->f0a1;
	pDph_t->arg2 = f0in;
	f0outa = mlsh1(pDphsettar->f0a1,f0in);
	pDph_t->arg1 = pDphsettar->f0b;
	pDph_t->arg2 = pDphsettar->f0las1;
	f0outb = mlsh1(pDphsettar->f0b,pDphsettar->f0las1);
	f0out1 = f0outa + f0outb;
	pDphsettar->f0las1 = f0out1;
	/*    Second pole */
	pDph_t->arg1 = pDphsettar->f0a2;
	pDph_t->arg2 = f0out1;
	f0outc = mlsh1(pDphsettar->f0a2,f0out1);
	pDph_t->arg1 = pDphsettar->f0b;
	pDph_t->arg2 = pDphsettar->f0las2;
	f0outd = mlsh1(pDphsettar->f0b,pDphsettar->f0las2);
	f0out2 = f0outc + f0outd;
	pDphsettar->f0las2 = f0out2;
	pDph_t->f0 = f0out2 >> F0SHFT;	/* Unscaled fundamental frequency	   */
}
else
	pDph_t->f0 -= (pDph_t->f0-f0in)>>1;

/* ****************** NOT USED *************************************/
#if 0
	//	FNX_PRINTF(
	//"[%s] pDphsettar->tarbas=%4d pDphsettar->tarhat=%3d pDphsettar->tarimp=%3d tarsum=%4d\n",
	//        phprint(pDph_t->allophons[pDphsettar->npg]), pDphsettar->tarbas, pDphsettar->tarhat, pDphsettar->tarimp, f0in);
	
	/*    (Check for overloads if change gr tc or size of impulses) */
	WINprintf("f0in=%6d   a=%6d b=%6d 1=%6d c=%6d d=%6d 2=%6d\n",
		f0in, f0outa, f0outb, f0out1, f0outc, f0outd, f0out2);
#endif // 0
/* *****************************************************************/
}

/* ******************************************************************
 *      Function Name: filter_seg_commands()
 *
 *      Description: Filter-segmental - commands
 *
 *      Arguments:	PDPH_T pDph_t
 *					short f0in
 *
 *      Return Value: void
 *
 *      Comments:
 *
 * *****************************************************************/
static void filter_seg_commands(PDPH_T pDph_t, short targseg) 
{	
	short f0souta, f0soutb, f0soutc, f0soutd, f0sout1, f0sout2;
	PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;



	/*    First pole (separate into 2 poles to min truncation errors) */
	pDph_t->arg1 = pDphsettar->f0sa1;
	pDph_t->arg2 = pDphsettar->tarseg;
	f0souta = mlsh1(pDphsettar->f0sa1, pDphsettar->tarseg);
	pDph_t->arg1 = pDphsettar->f0sb;
	pDph_t->arg2 = pDphsettar->f0slas1;
	f0soutb = mlsh1(pDphsettar->f0sb,pDphsettar->f0slas1);
	f0sout1 = f0souta + f0soutb;
	pDphsettar->f0slas1 = f0sout1;
	
	/*    Second pole */
	pDph_t->arg1 = pDphsettar->f0sa2;
	pDph_t->arg2 = f0sout1 + (pDphsettar->tarseg1 << F0SHFT);	/* Use only one pole */
	f0soutc = mlsh1(pDphsettar->f0sa2,(f0sout1 + (pDphsettar->tarseg1 << F0SHFT)));
	pDph_t->arg1 = pDphsettar->f0sb;
	pDph_t->arg2 = pDphsettar->f0slas2;
	f0soutd = mlsh1(pDphsettar->f0sb,pDphsettar->f0slas2);
	f0sout2 = f0soutc + f0soutd;
	pDphsettar->f0slas2 = f0sout2;
	pDph_t->f0s = f0sout2 >> F0SHFT;  /* Unscaled fundamental frequency	   */
}

/* ******************************************************************
 *
 * 
 *      Function Name: linear_interp()
 *
 *      Description: Sing-or-linear - Interp
 *
 *      Arguments: PDPH_T pDph_t
 *
 *      Return Value: void
 *
 *      Comments:
 *
 * *****************************************************************/
static void linear_interp(PDPH_T pDph_t) 
{
	PDPHSETTAR_ST pDphsettar = pDph_t->pSTphsettar;
	pDphsettar->delcum += pDphsettar->delnote;
	pDph_t->f0 = pDphsettar->f0start + (pDphsettar->delcum >> 2);
	
#ifdef TOMBUCHLER
	pDphsettar->vibsw = 1;

#endif
	
	if (pDphsettar->delnote >= 0)
	{	/* Do not overshoot pDphsettar->newnote */
		if (pDph_t->f0 > pDphsettar->newnote) {
			pDph_t->f0 = pDphsettar->newnote;
			pDphsettar->f0start = pDphsettar->newnote;
			pDphsettar->delcum = 0;
			pDphsettar->delnote = 0;
#ifdef TOMBUCHLER
			pDph_t->tmp = 0;
#endif
		}
	}
	else
	{
		if (pDph_t->f0 < pDphsettar->newnote)
		{
			pDph_t->tmp = 0;

			pDph_t->f0 = pDphsettar->newnote;
			pDphsettar->f0start = pDphsettar->newnote;
			pDphsettar->delcum = 0;
			pDphsettar->delnote = 0;
		}
	}
	pDph_t->f0prime = pDph_t->f0;	/* To be scaled by spdef */
#ifdef TOMBUCHLER
	if(1)
#else
	if (pDphsettar->vibsw == 1) 
#endif

	{	/* Singing */
		/*	  Add vibratto of 6.2 Hz (25 frames/cycle), +/- 2.05 Hz ampl. */
		pDphsettar->timecosvib += 165;
		if (pDphsettar->timecosvib > TWOPI)    
			pDphsettar->timecosvib -= TWOPI;
#ifdef TOMBUCHLER
	pDph_t->f0prime += ((getcosine[pDphsettar->timecosvib>>6] >> 3)*pDph_t->tmp)/1000;
	if(pDph_t->tmp < 1000)
		pDph_t->tmp += 200;
//	FNX_PRINTF("%d \n",((getcosine[pDphsettar->timecosvib>>6] >> 3)*pDph_t->tmp)/1000);
#else
	pDph_t->f0prime += getcosine[pDphsettar->timecosvib>>6] >> 3;

#endif
		
	}
}
