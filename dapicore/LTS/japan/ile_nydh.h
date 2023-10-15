/*********************************************
	ILE_NYDH.H	updated at 30th April 1990
	Input data
 *********************************************/

/* definitions for ( inert_kind[] ) */
/* Do not use 0x00. */

#define	CHRKIND_Kanji	0x10		/* Kanji */
#define	CHRKIND_HKana	0x20		/* Hiragana */
#define	CHRKIND_KKana	0x30		/* Katakana */

#define CHRKIND_KDigit1	0x41		/* Kanji numeral 1 : ˆê“ñOlŒÜ˜Zµ”ª‹ãZˆë“óQ */
#define CHRKIND_KDigit2	0x42		/* Kanji numeral 2 : \•SçE */
#define CHRKIND_KDigit3	0x43		/* Kanji numeral 3 : Šô”‰½ */
#define CHRKIND_KDigit4	0x44		/* Kanji numeral 4 : –œ‰­’›‹äİ */
#define	CHRKIND_ADigit	0x45		/* Arabic numeral : ‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚O */
#define	CHRKIND_DSign	0x46		/* Sign : |{} */
#define	CHRKIND_DSep	0x47		/* Digit grouping separator: C*/
#define	CHRKIND_DDP		0x48		/* DECIMAL POINT : D*/
#define CHRKIND_Digit	(CHRKIND_ADigit & 0xF0)

#define	CHRKIND_Alpha	0x50		/* Alphabetic characters, Russian characters, and Greek characters */

#define CHRKIND_Other1	0x60		/* A symbol that can be the top */
#define CHRKIND_Other2	0x70		/* A symbol that cannot be the top */

#define		CHRKIND_BOpen	0x01	/* Opened parenthesis:  io" */
#define		CHRKIND_BClose	0x02	/* Closed parenthesis:  jp"*/
#define		CHRKIND_Other	0x03	/* Other special symbols : |(hyphen)E */

/* definitions for ( inert_attr[] ) */

#define	CHRATTR_Soku	0x01 		/* Double consonant and syllabic nasal */
#define	CHRATTR_Hido	0x02		/* Contracted sound and dependent character (‚Ÿ‚¡‚£‚¥‚§[) */


/* Check whether or not a type of the current watching character (k=jsu) has attribute z. */
#define	NydfMjJsu(z,d)	(inert_kind[ceptr+d]==z)

EXT	integer_16	n_inert;				/* Input data length */
EXT	BYTE		inert   [2*MAX_INERT];	/* Input sentence          (original) */
EXT	BYTE		inert_kind[MAX_INERT];	/* Input sentence character type          (original) */
EXT BYTE		inert_attr[MAX_INERT];	/* Input sentence character attribute (standard) */

EXT	integer_16	ceptr,ceptr_sav;		/* current element pointer */
EXT	integer_16	celen,celen_sav;		/* current element length */

EXT integer_16	max_ceptr;				/* The position of the longest character string that can be converted without any special processing. */

EXT BYTE		inert_kana[MAX_EDIC*2+1];
EXT BYTE		inert_pron[MAX_EDIC+1];

/***************************** END OF ILE_NYDH.H *****************************/

