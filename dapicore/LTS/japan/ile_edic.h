/********************************************
	ILE_EDIC.H	updated at 16th June 1988
	Data related to external dictionary
 ********************************************/

#define	MaskEdicGrcd		0x7F	/* Grammar code */

/* External dictionary block number / position in the block */
EXT	WORD		edic_page_no;			/* Page number */
EXT	WORD		edic_ofs;				/* Offset in the page */

/* The save area for processing when the previous element in CS1000() is a number. */
EXT	WORD		edic_page_no_sav;
EXT	WORD		edic_ofs_sav;

/* The watching page start address in the external dictionary */
EXT	LPBYTE		edic_page_addr;

/* The matched length of the searched word and the keywords in the external dictionary (used for the dictionary registration)*/
EXT integer_16	ed_nsame;

/* The current watching word (from the flag 1 or flag 2 to the phonetic symbol) and its length */
EXT	integer_16	ed_ndata;
EXT	BYTE		ed_data[50];

/***************************** END OF ILE_EDIC.H *****************************/

