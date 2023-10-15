/********************************************
	ILE_STCH.H	updated at 16th June 1988
	Stack definition
 ********************************************/

/* Dictionary lookup stack related variable */

EXT BYTE		stc_kind[MAX_STACK];			/* Element type (=stz_kind) */
EXT integer_16	stc_in_ptr[MAX_STACK];			/* Input data position */
EXT BYTE		stc_in_len[MAX_STACK];			/* Number of characters in input data */
EXT integer_16	stc_out_ptr[MAX_STACK];			/* Output data position */
EXT BYTE		stc_out_len[MAX_STACK];			/* Number of characters in output data */
EXT BYTE		stc_f2[MAX_STACK];				/* Copying the extended control information */
EXT BYTE		stc_ctl[MAX_STACK];				/* Control information */
EXT BYTE		stc_mru[MAX_STACK];				/* Learning information */
EXT WORD		stc_ed_pag[MAX_STACK];			/* External dictionary page number */
EXT WORD		stc_ed_ofs[MAX_STACK];			/* Position in the extended dictionary page */
	/*
	 *	For the internal dictionary word, the offset from the top of the residential part is stored.
	 *	For the external dictionary word, the offset from the top of the page is stored.
	 */
EXT BYTE		stc_stz[MAX_STACK];				/* Connection status */
EXT BYTE		stc_nbno[MAX_STACK];			/* Number of back-end numbers */
EXT BYTE		stc_bno[MAX_STACK][MAX_GRCD];	/* Back-end number */
EXT BYTE		stc_ngrcd[MAX_STACK];			/* Number of external dictionary grammar codes */
EXT BYTE		stc_grcd[MAX_STACK][MAX_GRCD];	/* External dictionary grammar code */
EXT BYTE		stc_dman[MAX_STACK];			/* Mantissa, sign, decimal point, and counter suffix */
EXT BYTE		stc_dexp[MAX_STACK];			/* Exponent */

EXT BYTE		stc_accent_raw[MAX_STACK][10];	/* Accent raw data */
EXT BYTE		stc_pause[MAX_STACK];			/* Volume of a pause */

EXT	integer_16	stc_ptr;						/* Stack watching position */

/***************************** END OF ILE_STCH.H *****************************/

