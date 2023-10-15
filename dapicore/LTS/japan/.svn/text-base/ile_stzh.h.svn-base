/*******************************************
	ILE_STZH.H	updated at 22th May 1989
	Data related to connection between elements
 *******************************************/
#ifndef ILE_STZH_H
#define ILE_STZH_H

/* Definition of the structure of the information related to the connection relation between elements */

typedef	struct {
	BYTE stz_kind;			/* Word type */
		/*(external dictionary/internal dictionary/5-step verb conjunctive ending/katakana/numeral/special symbol)*/
	BYTE stz_ctl;			/* Logical add of the control information */
	BYTE stz_f2;			/* Flag 2 */
	BYTE stz_stz;			/* Connection status */
	BYTE stz_ngrcd;			/* Number of grammar codes＝Number of forward vectors */
	BYTE stz_nbno;			/* Number of back-end numbers */
	BYTE stz_grcd[MAX_GRCD];/* Grammar code (meaningless except the external dictionary words) */
	BYTE stz_bno[MAX_GRCD];	/* Back-end number */
	BYTE stz_pno[MAX_GRCD];	/* Forward vector number */
	BYTE stz_mru;			/* Learning information */
	BYTE stz_dman;			/* mantissa */
	BYTE stz_dexp;			/* exponent */
		/*
		 *	Meanings of MAN and EXP
		 *	They indicate the mantissa part and the exponent part of a number.
		 *	To distinguish "一千(ISSEN)" and "千(SEN)," set MAN=1 for 一千, and set MAN=0 for 千.=set MAN=0 for "1" and "千."
		 *	For "十(JYU)" and "百(HYAKU)," set MAN=0 as necessary.
		 *	The mantissa parts of "数(SU)," "何(NAN)," and "幾(IKU)" are represented as 10, 11, and 12 respectively.
		 *	The mantissa parts of marks and decimal points are represented as 65 and 66 respectively, and their exponent as 0.
		 */
		/*
		 *	For a Tan-kanji,
		 *	set the type flag to dman, and set the total record size to dexp.
		 *	The total record size is the total record length of the remaining targets.
		 */
} STZ_STRUCT;

/* Information related to the number information */
#define DMANKIND_PL			 64		/* Plural number */
#define DMANKIND_SIGN		 65		/* sign */
#define DMANKIND_DP			 66		/* decimal point */
#define DMANKIND_NUM		129		/* numerator */

/* Information related to word type stc_kind[] */
#define	DICKIND_E		0x80		/* EXTERNAL DICTIONARY */
#define	DICKIND_I		0x40		/* INTERNAL DICTIONARY */
#define	DICKIND_D		0x20		/* NUMERALS */
#define	DICKIND_5Y		0x10		/* 5-step verb conjunctive ending  */
#define	DICKIND_K		0x08		/* Katakana word */
#define	DICKIND_T		0x04		/* Tan-kanji dictionary */

/* Information related to word type stc_ed_ofs[] */
#define DKIND_INT		0x01		/* integer type */
#define DKIND_FRAC		0x02		/* fraction type */

/* Connection status record definition */
#define	BITSTZ_PREFO5V	0x80		/* 5-step verb of the word following "お" */
									/* the conjunctive form is changed to SAHEN verbal noun type. */
#define	BITSTZ_KANGO	0x40		/* Chinese-origin word */
#define BITSTZ_PREF		0x20		/* A word following a prefix: it cannot be a delimiter of sentence. */

/* Control information record definition */
#define	BITCTL_PREF		0x80	/* prefix */
#define	BITCTL_SUF		0x40	/* suffix */
#define	BITCTL_PKANGO	0x20	/* Preceding word with a Chinese-origin word connected (preceding kango) */
#define	BITCTL_FKANGO	0x10	/* Following word with a Chinese-origin word connected (following kango) */
#define	BITCTL_FIRST	0x08	/* It can be the first. */
#define	BITCTL_LAST		0x04	/* It can be the last. */
#define	BITCTL_PEDIC	0x02	/* The preceding word can be in the external dictionary. preceding EDIC */
#define	BITCTL_FEDIC	0x01	/* The succeeding word can be in the external dictionary. following EDIC */

/* Flag 2 record definition */
#define BITFLG2_AUX		0x10
				/* Adverbs "ない" and "たい"*/
				/* Even if an element of which accent fall moves to one previous syllable follows, 
				the accent fall of such element does not move.
				It is originally used as a delimiter of a sentence, 
				but it is changed to be used as an adverb.*/
#define	BITFLG2_KANGO	0x08
				/* Chinese-origin word */
#define	BITFLG2_SUF		0x04
				/* Chinese-origin word suffix */
				/* "どまり" in "東京どまり" and "課長どまり" */
#define	BITFLG2_NADV	0x02
				/* Succeeding adverb (next adverb) */
				/* "つ" in "～につき"; Add the back-end number of an advert to "き" */
#define	BITFLG2_SELF	0x01
				/* "自身" in "あなた自身" and "それ自身" */
				/* The control information and the back-end number of this word is to be the same as one previous word. */

/* Grammar code and back-end number table */
#define GRCDTBL_CTL		0		/* Control information */
#define GRCDTBL_BNO		1		/* Back-end number */
#define GRCDTBL_PNO		2		/* Forward vector number */
#define GRCDTBL_NULL	3		/* Unused */


/*========== ce_is_kango ==========================================
	Sentence structure:ce_is_kango, pe_is_kango
	Function: Whether or not the preceding word (PE)/current watching word (CE) is a Chinese-origin word
  =================================================StzfXxgKangGzg==*/
#define	ce_is_kango \
	((Stz_CE.stz_f2 & BITFLG2_KANGO)||(Stz_CE.stz_stz & BITSTZ_KANGO))

#define	pe_is_kango \
	((Stz_PE.stz_f2 & BITFLG2_KANGO)||(Stz_PE.stz_stz & BITSTZ_KANGO))


/*========== StzfAttrAri =====================================================
	Sentence structure:StzfAttrAri(go,target,Attr)
	Function: Check whether or not the preceding element (go=PE)/control information of the watching element (go=CE)/flag 2/learning information 
		includes the attribute specified in Attr.
  ============================================================================*/
#define	StzfAttrAri(go,target,Attr)		(go.target & Attr)
#define	StzfAttrNashi(go,target,Attr)	((go.target & Attr)==0)


/*========== StzfAttrAdd =====================================================
	Sentence structure:StzfAttrAdd(go,target,Attr)
	Function: To the preceding element (go=PE)/control information of the watching element (go=CE)/flag 2/learning information,
		add the attribute specified in Attr.
  ============================================================================*/
#define	StzfAttrAdd(go,target,Attr)		(go.target|=Attr)


/* Structure definition of the processing related to connection between elements */
EXT	STZ_STRUCT		Stz_PE;		/* Preceding element, connection relation, supplemental information */
EXT	STZ_STRUCT		Stz_CE;		/* Current element, connection relation, supplemental information */

#endif
/***************************** END OF ILE_STZH.H *****************************/
