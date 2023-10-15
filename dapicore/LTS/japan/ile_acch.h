/***********************************************
	ILE_ACCH.H	updated at 24th October 1988
	Data definition for accent combining processing
 ***********************************************/

#ifndef EXT 
#define EXT extern
#endif

EXT BYTE		phrase_kind[MAX_STACK];		/* phrase grammer kind */
EXT integer_16	phrase_ptr [MAX_STACK];		/* phrase start pointer */
EXT integer_16	phrase_len [MAX_STACK];		/* phrase length */

 /* Because stc_accent_raw[][0..3] can be damaged in acc2000(), copy it in the work area for use.*/
EXT BYTE		acc_accent_raw[MAX_STACK][4];

 /* Because phrase_kind[] can be damaged in acc2000(), copy it in the work area for use.*/
/* This work area is used for PAUSE1000() only.*/
EXT BYTE		phrase_kind_sav[MAX_STACK];

#define MAX_PHRASE	30		/* Maximum number of mora phonemes in one breath */
#define MAX_TONE	30		/* Maximum number of continuous mora phonemes on the same pitch */

/***************************** END OF ILE_ACCH.H *****************************/

