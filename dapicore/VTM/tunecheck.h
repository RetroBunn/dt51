#ifndef _TUNECHECK_H_
#define _TUNECHECK_H_

#define MAX_TRIGGER 26000
#define MAX_FRIC_TRIGGER 26000

typedef struct VTD_T {

#ifdef HLSYN_NEWPOLE
	S32 rnpd22;    /*  Second-previous output sample                       */
	S32 rnzd22;    /*  Second-previous output sample                       */
#endif

	S32 rnpmax;			/*maximum value within filter of casade rnp*/
	S32 rnzmax;			/*maximum value within filter of casade rnz*/
	S32 c1max;			/*maximum value within filter of casade 1*/
	S32 c2max;			/*maximum value within filter of casade 2*/
	S32 c3max;			/*maximum value within filter of casade 3*/
	S32 c4max;			/*maximum value within filter of casade 4*/
	S32 c5max;			/*maximum value within filter of casade 5*/
	S32 purevmax;		/*maximum value of downsampled voice */
	S32 r2pd1;    /*  Last output sample from parallel 2nd formant        */
	S32 r3pd1;    /*  Last output sample from parallel 3rd formant        */
	S32 r4pd1;    /*  Last output sample from parallel 4th formant        */
	S32 r5pd1;    /*  Last output sample from parallel 5th formant        */
	S32 r6pd1;	/*  Last output sample from parallel 6th formant        */
	S32	iwave; /* the final output        */
	
	BOOL bDidOverload;	/* true if we trapped an overload */
	DWORD	dwThisPhoneme;	/* phoneme at overload */
	DWORD	dwLastPhoneme;	/* the phoneme just prior */
	// these are the prior delay signals when we trapped.

	S32 r1cd2;    /*  Second-previous output sample                       */
	S32 r2cd2;    /*  Second-previous output sample                       */
	S32 r3cd2;    /*  Second-previous output sample                       */
	S32 r4cd2;    /*  Second-previous output sample                       */
	S32 r5cd2;    /*  Second-previous output sample                       */
	S32 rnpd2;    /*  Second-previous output sample                       */
	S32 rnzd2;    /*  Second-previous output sample                       */
	S32 rlpd2;    /*  Second-previous output sample                       */

} VTM_TUNER_DATA;

#endif
