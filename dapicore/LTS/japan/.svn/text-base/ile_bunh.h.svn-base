/********************************************
	ILE_BUNH.H	updated at 16th June 1988
	Data related to segments
 ********************************************/

/*
 *	ws_no : Watching segment number (origin at 1, and 0 for the initial conversion)
 *		It is required that the sentence voice conversion backtrack processing does not go back
 *		before the segment number specified here.
 *	wsptr : Start position of the watching segment (origin at 0)
 *	fsptr : Start position of the following segment of the watching segment (origin at 0)
 *		In the second choice, longer segment, or shorter segment processing, record the first and the last positions of the watching segment, and
 *		In INERT1000()ÅEFOLLOW(), conversions that contradict these positions are excluded.
 *		Obtain fsptr when the possibility of shorter or longer segment conversion is checked.
 *		fsptr_sav is used for restoring the conversion result when any conversion error occurs.
 *
 *		watching sentence no.
 *		watching sentence pointer
 *		following sentence pointer
 */

EXT	integer_16	ws_no;			/* User-watching segment number (origin at 1)*/
EXT	integer_16	wsptr;			/* Start character position of the watching segment (origin at 0)*/
EXT	integer_16	fsptr;			/* Start character position of the following segment of the watching segment (origin at 0)*/
EXT	integer_16	fsptr_sav;		/* fsptr Storage area */

/***************************** END OF ILE_BUNH.H *****************************/

