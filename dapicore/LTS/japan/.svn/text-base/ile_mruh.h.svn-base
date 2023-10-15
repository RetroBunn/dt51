/***********************************************
	ILE_MRUH.H	updated at 8th November 1988
	Data related to learning
 ***********************************************/

/* Learning information record definition */
#define	BITMRU_DEL		0x80	/* External dictionary deletion flag (external dictionary)*/
#define	BITMRU_ABORT	0x40	/* Initial abandon flag (external dictionary and internal dictionary)*/
#define	BITMRU_ACOFF	0x20	/* Accent combination abandon flag (external dictionary and internal dictionary)*/
#define	BITMRU_ACON		0x10	/* Forcible accent combination flag (external dictionary and internal dictionary)*/
#define	BITMRU_PINS		0x08	/* Forcible pause insertion flag (external dictionary and internal dictionary)*/
#define	BITMRU_PDEL		0x04	/* Forcible pause deletion flag (external dictionary and internal dictionary)*/

/*
 *	MRU_OR_NOT : MRU execution flag
 *		When the initial result is determined without performing the next target, longer segment, or shorter segment processing,
 *		no learning is required.
 */
EXT integer_16	MRU_OR_NOT;		/* When it is 1, execute MRU.When it is 0, MRU is not executed.*/

#if !defined(O_TALKONLY)
/* Table for recording the words that have been learned by sorting. */
EXT	WORD		EdicMruDone_LBN[MAX_STACK+1];	/* Logical block number */
EXT	WORD		EdicMruDone_OFS[MAX_STACK+1];	/* Position in block */
#endif

/***************************** END OF ILE_MRUH.H *****************************/

