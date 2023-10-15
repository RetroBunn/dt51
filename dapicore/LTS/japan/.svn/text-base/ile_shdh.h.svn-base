/*******************************************
	ILE_SHDH.H	updated at 19th May 1989
	Output data
 *******************************************/

/* Accent information mask pattern */
#define	BITACC_MUSEI	0x80
#define	BITACC_FIRST	0x40
#define	BITACC_LEVEL	0x0F

/* Output data management information */
EXT	integer_16		cpron_ptr;					/* Output data watching position */
EXT	integer_16		cpron_len;					/* Current word conversion result length */

/* Output data sentence management information */
EXT	integer_16		sent_ptr;					/* Watching sentence position */

/* Output data middle area */
EXT	integer_16		sent_in_ptr[MAX_SENT];		/* Input data position */
EXT	integer_16		sent_out_ptr[MAX_SENT];		/* Output data position */
EXT BYTE			omega[MAX_OMEGA];			/* pronunciation data */
EXT BYTE			speak[MAX_SPEAK];			/* Phonogram data */

EXT integer_16		kkana_len;					/* Area for katakana processing */
EXT BYTE			kkana_buf[MAX_OMEGA];

EXT BYTE			kansuji[MAX_INERT*2+1];		/* Kanji numerals area */
EXT integer_16		n_kansuji;
EXT integer_16		digit_mode;					/* Number conversion mode */
												/* =0 : integer type */
												/* =1 : fraction type */
EXT integer_16		digit_type;					/* Number type */
												/* =0 : normal type */
												/* =1 : Digit-by-digit reading type */

EXT BYTE			accent0[MAX_OMEGA];			/* accent data */


/* Storage area for checking whether or not the output data matches the previous result */
EXT BYTE			omega_sav[MAX_OMEGA];		/* pronunciation data */
EXT BYTE			accent_sav[MAX_OMEGA];		/* accent data */
EXT	integer_16		sent_in_ptr_sav[MAX_SENT];	/* Input data position */
EXT	integer_16		sent_out_ptr_sav[MAX_SENT];	/* Output data position */

/***************************** END OF ILE_SHDH.H *****************************/

