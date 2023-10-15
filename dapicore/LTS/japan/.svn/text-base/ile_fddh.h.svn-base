/********************************************
	ILE_FDDH.H	updated at 16th July 1991
	Dictionary header data definition
 ********************************************/

/* Constant related to the initial load data on FD */
#define	MAX_FDDBLK		0x12	/* Maximum number of the initial load data blocks */
#define	Fdd_BlkSize		1024	/* Initial load data block length */ 
#define	Fdd_PartirSize	193		/* Top data size */

/* Header record definition */
typedef struct {
	BYTE	Fdd_DVer[4];		/* +01(  1) dictionary version number */
	BYTE	Fdd_UserID[22];		/* ;05(  5) customer name */
	BYTE	Fdd_DDate[6];		/* +1B( 27) Creation date */

	WORD	Fdd_Fil33;			/* +21( 33) (blank) */
	WORD	Fdd_ChrAttrOfs;		/* +23( 35) character code table offset*/

	WORD	Fdd_Fil37;			/* +25( 37) (blank) */
	WORD	Fdd_GrcdTblOfs;		/* +27( 39) dictionary grammar code table offset */

	WORD	Fdd_Fil41;			/* +29( 41) (blank) */
	WORD	Fdd_IdicIndOfs;		/* +2B( 48) grammar book character number pointer offset */

	WORD	Fdd_Fil45;			/* +2D( 45) (blank) */
	WORD	Fdd_IdicPronOfs;	/* +2F( 47) grammar book pronunciation information offset */
	
	WORD	Fdd_Fil49;			/* +31( 49) (blank) */
	WORD	Fdd_VecpOfs;		/* +33( 51) forward reference vector table offset*/

	WORD	Fdd_Fil53;			/* +35( 53) (blank) */
	WORD	Fdd_EdicIndOfs;		/* +37( 55) dictionary index offset */

	WORD	Fdd_Fil57;			/* +39( 57) (blank) */
	WORD	Fdd_TdicIndOfs;		/* +3B( 59) Tan-kanji dictionary keyword offset */

	WORD	Fdd_Fil61;			/* +3D( 61) (blank) */
 	WORD	Fdd_IdicOfs;		/* +3F( 63) internal dictionary offset */

	WORD	Fdd_HdrSector;		/* +41( 65) number of header sectors on FD */
	WORD	Fdd_HdrNg;			/* +43( 67) actual header length on FD */

	WORD	Fdd_MaxNjsLen;		/* +45( 69) maximum length of grammar book header */
	WORD	Fdd_MaxGjsInd;		/* +47( 71) dictionary index length */

	WORD	Fdd_Fil73;			/* +49( 73) (blank) */
	WORD	Fdd_Fil75;			/* +4B( 75) (blank) */

	WORD	Fdd_Fil77;			/* +4D( 77) (blank) */
	WORD	Fdd_V5youOfs;		/* +4F( 79) 5-step verb conjunctive ending phonologic table offset */

	WORD	Fdd_Fil81;			/* +51( 81) (blank) */
	WORD	Fdd_BnoTblOfs;		/* +53( 83) back-end number table offset */

	WORD	Fdd_Fil85;			/* +55( 85) (blank) */
	WORD	Fdd_MatrixOfs;		/* +57( 87) sentence matrix table offset */

	WORD	Fdd_Fil89;			/* +59( 89) (blank) */
	WORD	Fdd_EdicKeyOfs;		/* +5A(91) dictionary index key offset*/

	WORD	Fdd_Fil93;			/* +5C( 93) (blank) */
	WORD	Fdd_EdicIndSector;	/* +5E(95) Number of sectors of dictionary index */

	BYTE	Fdd_Fil97[8];		/* +60( 97..104) (blank) */

	WORD	Fdd_IdicPageOfs;	/* +69(105) grammar book page offset */
	WORD	Fdd_IdicPageSize;	/* +6B(107) page size (in sector units, 1024 bytes) */
	WORD	Fdd_IdicNoPage;		/* +6D(109) total number of pages (number of indexes) */
	WORD	Fdd_Fil111;			/* +6F(111) (blank) */

	WORD	Fdd_TdicPageOfs;	/* +71(113) Tan-kanji dictionary page offset */
	WORD	Fdd_TdicPageSize;	/* +73(115) page size (in sector units, 1024 bytes) */
	WORD	Fdd_TdicNoPage;		/* +75(117) total number of pages (number of indexes) */
	WORD	Fdd_Fil119;			/* +77( 119) (blank) */

	WORD	Fdd_EdicPageOfs;	/* +79(121) external dictionary page offset */
	WORD	Fdd_EdicPageSize;	/* +7B(123) page size (in sector units, 1024 bytes) */
	WORD	Fdd_EdicNoPage;		/* +7D(125) total number of pages (number of indexes) */
	WORD	Fdd_Fil127;			/* +7F(127) (blank) */

	BYTE	Fdd_BnoPrefo;		/* +81(129) back-end number of "‚¨ (O)" in formal lines */
	BYTE	Fdd_Bno5danLL;		/* +82(130) lower limit of back-end number of 5-step verb */
	BYTE	Fdd_Bno5danUL;		/* +83(131) upper limit of back-end number of 5-step verb */
	BYTE	Fdd_Bno5danYou;		/* +84(132) back-end number of 5-step verb conjunctive form */
	BYTE	Fdd_Bno1danMei;		/* +85(133) back-end number of 1-step noun form */
	BYTE	Fdd_Bno1danYou;		/* +86(134) back-end number of 1-step non-noun form */
	BYTE	Fdd_BnoSahen;		/* +87(135) back-end number of verbal noun */
	BYTE	Fdd_BnoSahenYou;	/* +88(136) back-end number of SAGYO verb conjunctive form */
	BYTE	Fdd_BnoHifu;		/* +89(137) back-end numbers of "”ñ(HI), •s(FU), –³(MU), and –¢(MI)" */
	BYTE	Fdd_BnoAdv;			/* +8A(138) back-end number of adverb */
	BYTE	Fdd_GrcdToku1;		/* +8B(139) grammar code of the special symbol 1 */
	BYTE	Fdd_GrcdToku2;		/* +8C(140) grammar code of the special symbol 2 */
	BYTE	Fdd_GrcdDigit;		/* +8D(141) grammar code of number */
	BYTE	Fdd_GrcdAdjv;		/* +8E(142) grammar code of the adjectival verb 2 */
	BYTE	Fdd_GrcdGai;		/* +8F(143) grammar code of foreign word */
	BYTE	Fdd_GrcdUsr;		/* +90(144) grammar code of user-registered word */
	BYTE	Fdd_GrcdDai;		/* +91(145) grammar code of the prefix for numbers "(‘æ DAI)" */
	BYTE	Fdd_GrcdPropLL;		/* +92(146) lower limit of proper noun grammar code */
	BYTE	Fdd_GrcdPropUL;		/* +93(147)   "   "   upper limit */
	BYTE	Fdd_PropMeaning;	/* +94(148) meaning category of proper noun */

	BYTE	Fdd_GrcdSufLL;		/* +95(149) lower limit of grammar code of forward connection of suffix */
	BYTE	Fdd_GrcdSufUL;		/* +96(150)   "         "   upper limit */

	BYTE	Fdd_Fil149[41];		/* +97(151)  43BYTES unused */
	BYTE	Fdd_GrcdNum1;		/* +C0(192) grammar code of the counter suffix 1 */
	BYTE	Fdd_GrcdNum2;		/* +C1(193) grammar code of the counter suffix 2 */

	BYTE	Fdd_Fil194[Fdd_BlkSize-Fdd_PartirSize];
								/* +C2(194) dictionary header (remains)*/
	BYTE	Fdd_Body[Fdd_BlkSize*(MAX_FDDBLK-1)];
								/*+401(1025) dictionary */
} DIC_STRUCT;

EXT	DIC_STRUCT Fdd_Header;
EXT	LPBYTE Fdd_EdicIndex;

#define	FddHDR	((BYTE *)&Fdd_Header)
#define	FddBODY	((BYTE *)Fdd_Header.Fdd_Body)

/*
 *	Back-end number table (table offset for case determination) value
 *
 *	2nd bit: Used when the effect on the preceding element is A.
 *	3rd bit: The accent level of the particle "(‚íWA)" or "(‚ËNE)" becomes 9 at the end of a sentence.
 *	4th bit: The accent point of the conjunctive ending form of raised-ending type word is moves to one previous syllable.
 *	5th bit: There is an ancillary of which accent becomes special when it is attached to the flattened-type noun.
 *	6th to 8th bits: Used for determining the volume of pauses.
 */
#define	BITBNO_1			0x80
#define	BITBNO_2			0x40		/* Use when the effect on the preceding element is A. */
#define	BITBNO_Level9		0x20		/* Particle of which height is 9 */
#define	BITBNO_Renyou		0x10		/* Conjunctive form */
#define	BITBNO_Taigen		0x08		/* Indeclinable form */
#define	BITBNO_Shushi		0x04		/* Ending form */
#define	BITBNO_RentaiKaku	0x02		/* Attributive modification */
#define	BITBNO_RenyouKaku	0x01		/* conjunctive modification */

/***************************** END OF ILE_FDDH.H *****************************/

