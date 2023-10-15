/************************************************
	ILE_JKNH.H	updated at 20th February 1991
	Dictionary search table
 ************************************************/

/* Dictionary search table dictionary using table */
EXT	BYTE		dut_value[MAX_INERT*MAX_EDIC];	/* Search information */
EXT	WORD		dut_edofs[MAX_INERT*MAX_EDIC];	/* Offset in page of the external dictionary */
EXT	BYTE		*dut_idaddr[MAX_INERT*MAX_EDIC];/* Address in the internal dictionary */

/* Record definition in the dictionary search table */
#define		BITDUT_ED_NONE	0x80	/* Corresponding item not found in the external dictionary */
#define		BITDUT_ED_ABORT	0x40	/* Abandon flag detected in the external dictionary */
#define		BITDUT_ED_USE	0x20	/* External dictionary used for conversion */
#define		BITDUT_ED_EXIST	0x10	/* Corresponding item found in the external dictionary */
#define		BITDUT_ID_NONE	0x08	/* Corresponding item not found in the internal dictionary */
#define		BITDUT_ID_ABORT	0x04	/* Abandon flag detected in the internal dictionary */
#define		BITDUT_ID_USE	0x02	/* Internal dictionary used for conversion */
#define		BITDUT_ID_EXIST	0x01	/* Corresponding item found in the internal dictionary */

/*========== dut_ptr ==========
  Function: Obtain the offset of the dictionary search table.
*/
#define		dut_ptr					(ceptr*MAX_EDIC+celen)

/*========== JknfAttrAri ==========
  Sentence structure:JknfAttrAri(shu)
  Function: Check whether or not there is an attribute specified with shu in the dictionary search table.
  Return value:Not zero when there is an attribute.
*/
#define	JknfAttrAri(shu)			(dut_value[dut_ptr] & shu)

/*========== JknfAttrAdd ==========
  Sentence structure：  JknfAttrAdd(shu)
  Function: Add the attribute specified with shu to the dictionary search table.
*/
#define	JknfAttrAdd(shu)			(dut_value[dut_ptr] |= shu)
#define	JknfAttrAdd3(shu,ptr,len)	(dut_value[ptr*MAX_EDIC+len] |= shu)

/*========== JknfAttrToru ==========
  Sentence structure：  JknfAttrToru(shu)
  Function: Remove the attribute specified with shu from the dictionary search table.
*/
#define	JknfAttrToru(shu)			(dut_value[dut_ptr] &= ~shu)

/*========== JknfEdicShimau ==========
  Sentence structure：JknfEdicShimau(bp)
  Input:bp	Offset in page of the external dictionary
  Function: Store the offset in page of the external dictionary into the dictionary search table.
*/
#define	JknfEdicShimau(bp)			(dut_edofs[dut_ptr]=bp)

/*========== JknfEdicToridasu ==========
  Sentence structure：JknfEdicToridasu
  Function: Retrieve the offset in page of the external dictionary from the dictionary search table.
*/
#define	JknfEdicToridasu			(dut_edofs[dut_ptr])

/*========== JknfIdicShimau ==========
  Sentence structure：JknfIdicShimau(bp)
  Input:bp	Address in the internal dictionary
  Function: Store the address in the internal dictionary into the dictionary search table.
*/
#define	JknfIdicShimau(bp)			(dut_idaddr[dut_ptr]=bp)

/*========== JknfIdicToridasu ==========
  Sentence structure:JknfIdicToridasu
  Function: Retrieve the offset in page of the internal dictionary from the dictionary search table.
*/
#define	JknfIdicToridasu			(dut_idaddr[dut_ptr])

/*
 *	The following part is now a dummy.
 *	There is supposed to be a bug, but it is not certain.
 *	It will be restarted as soon as the routing is determined.
 *	define O_NULL
 */

#if defined(O_NULL)
/* Input character search table */
#define MAX_NULL 100
EXT WORD		null_no;
EXT integer_16	null_ptr[MAX_NULL];
EXT WORD		null_ofs[MAX_NULL];
EXT WORD		null_page[MAX_NULL];
#endif

/***************************** END OF ILE_JKNH.H *****************************/

