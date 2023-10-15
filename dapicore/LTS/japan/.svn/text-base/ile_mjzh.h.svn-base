/********************************************
	ILE_MJZH.H	updated at 19th July 1988
	Character attribute
 ********************************************/

/* Record definitions in the character attribute table */
#define	MjzBitToji	0x80	/* Closed parenthesis (a character that cannot be the top: special symbol 2) */
#define	MjzBitDigit	0x08	/* Number (alphanumeric) */
#define	MjzBitSoku	0x04	/* Double consonant and syllabic nasal (hiragana and katakana) */
#define	MjzBitHido	0x02	/* Dependent characters (ÇüÇ°Ç£Ç•ÇßÇ·Ç„ÇÂÅ[)(hiragana and katakana) */

/*========== MjzfGetChrAttr(r) ======================================
	Function: Return the character attribute that corresponds to the JIS kanji code second byte in r.
  ===================================================================*/
#define	MjzfGetChrAttr(r)		FddHDR[Fdd_Header.Fdd_ChrAttrOfs+r]

/*========== MjzfToku1(r) =======================
	Function: Check whether or not the character attribute r is a special symbol 1.
  ===============================================*/
#define	MjzfToku1(r)			((r & MjzBitToji)==0)

/*========== MjzfDigit(r) =================
	Function: Check whether or not the character attribute r is a number.
  =========================================*/
#define	MjzfDigit(r)			(r & MjzBitDigit)

/*========== MjzfHido(r) ========================
	Function: Check whether or not the character attribute r is a dependable character.
  ===============================================*/
#define	MjzfHido(r)				(r & MjzBitHido)

/*========== MjzfSoku(r) ============================
	Function: Check whether or not the character attribute r is a dependent character.
  ===================================================*/
#define	MjzfSoku(r)				(r & MjzBitSoku)

/***************************** END OF ILE_MJZH.H *****************************/

