/************************************************
	ILE_IDIC.H	updated at 20th February 1991
	Data relating to the internal dictionary
 ************************************************/

/* Internal dictionary characters/numbers distinction pointers */
typedef	struct 
{
	/*WORD		idic_len_ptr;*/
	BYTE		idic_len_ptr2;
	BYTE		idic_len_ptr1;
	WORD		idic_index_dummy;
} IDIC_INDICES;

/* Internal dictionary fixed information structure definition */
typedef	struct {
	BYTE		idic_ctl;		/* control information */
	BYTE		idic_f2;		/* flag 2 */
	BYTE		idic_bno;		/* end number */
	BYTE		idic_pno;		/* front end reference vector number: offset is 20 times the amount */
	/*WORD		idic_acc_ofs;*/	/* accent & pronunciation data offset */
	BYTE		idic_acc_ofs2;	/* accent & pronunciation data offset */
	BYTE		idic_acc_ofs1;	/* accent & pronunciation data offset */
	BYTE		idic_mru;		/* training information */
} IDIC_DATA;

#define	SIZE_IDIC	7		/* sizeof(IDIC_DATA)=8 !!! */

/* Address for informatoin control for items of the internal dictionary */
EXT	BYTE		*idic_addr;

/* Save area for when processing when there is a number at the very beginning in CS1000() */
EXT	BYTE		*idic_addr_sav;

/***************************** END OF ILE_IDIC.H *****************************/
