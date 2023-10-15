#if defined(O_DEBUG)
/************************************************
	ILE_DBGH.H	updated at 24th February 1988
	‚c‚d‚a‚t‚f DATA
 ************************************************/

/* debug option definition */
EXT integer_8	debug[100];
			/* debug[ 1];	STACK_PUSH() all element */
			/* debug[ 2];	STACK_PUSH() current element */
			/* debug[ 3];	STACK_POP()  current element */
			/* debug[ 4];	FOLLOW() Stz_CE and Stz_PE */
			/* debug[ 5];	OMEGA9000() stack contents after xfer */
			/* debug[ 6];	FOLLOW() Stz_CE */

/***************************** END OF ILE_DBGH.H *****************************/
#endif
