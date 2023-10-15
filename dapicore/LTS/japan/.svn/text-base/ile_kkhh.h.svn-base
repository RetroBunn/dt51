/***********************************************
	ILE_KKHH.H	updated	at 3rd February 1988
	Data related to analysis processing
 ***********************************************/

EXT enum {
		shoki,			/* Initial state */
		bunsetsu,       /* Sentence setting state */
		funou,          /* Unconvertible state */
		err,            /* Error state */
		mru,            /* Learning state */
		riyousha        /* User-defined word state */
} kkhstat;

/* == KkhfMruKanou ==
  Sentence structureÅFKkhfMruKanou 
  Function: Check whether or not the current conversion state can be learned.
*/
#define	KkhfMruKanou	 (kkhstat==bunsetsu || kkhstat==funou)

#define	CONV_FIRST		1
#define	CONV_NEXT		2
#define	CONV_RIGHT		3
#define	CONV_LEFT		4
#define	CONV_SHORT		5
#define	CONV_LONG		6
#define	CONV_RETRY		7	/* Conversion up to the error 3 and 4 in initial conversion */

EXT	BYTE	conv_mode;		/* Conversion type */

/***************************** END OF ILE_KKHH.H *****************************/

