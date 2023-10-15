/*********************************************
	ACC_2000.C	updated at 17th April 1990
	Main Part of Accent Combining Processing
 *********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_acch.h"
#include	"ile_envh.h"
#include	"ile_fddh.h"
#include	"ile_mruh.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"
#include "pkind.h"
#include "ile_accd.h"

/*============ ACC2000() =================================================
	Function: The accent of two adjacent elements are combined.

	The component parts of sentences are classified in the following categories.

	1.  Attributives				：この (KONO), 一身上の (ISSHINJOU NO), どんな (DONNA)
	2.  Prefix				：大 (DAI), 東 (TOH), 超 (CHOU), 国際 (KOKUSAI), 末梢 (MASSHOU)
	3.  Suffix				：者 (SHA), 用 (YOU), 長 (CHOU), 町 (CHOU)
	4.  Verb stem			：動（く） (UGO(KU), 居（る） (I(RU))
	5.  5-step conjunctive verb ending	：（動）き (UGO)KI
	6.  Adjective stem			：美し（い） UTSUKUSHI(I)
	7.  Self-sufficient words other than 4 or 6	：言語 (GENGO), 国分 (KOKUBUN), 東京 (TOKYO), 大きな (OOKINA), どんな (DONNA), 綺麗 (KIREI)
	8. Ancillary words other than 5		：（美し）い (USHUKUSHI)I, （動き）ます (UGOKI)MASU, counter, adverb
	9.  Alphabetic character	The one that has the only one carrier of accent
10.  Number	The one that has the only one carrier of accent
11.  Counter
12.  Words derived from Tan-Kanji dictionary

	The order of combination is as follows:

	0.  Tan-kanji + Tan-kanji		-> Self-sufficient word
	1.  Alphabetic character + Alphabetic character			-> Self-sufficient word
	2.  Number + Counter		-> Number
	3.  Number + Decimal point		-> Number
	4.  Number + Number			-> Adverb
	5.  Verb + Conjunctive ending	-> Verb
	6.  Compound verb / Compound adjective
	7.  Prefix + Self-sufficient word		-> Self-sufficient word
	8.  Self-sufficient word + Self-sufficient word		-> Self-sufficient word
	9.  Self-sufficient word + suffix		-> Self-sufficient word
10.  Attributive + Self-sufficient word		-> Self-sufficient word
11.  Self-sufficient word + Ancillary word		-> Phrase
12.  Adverb + Ancillary word		-> Phrase

	Handling of numbers and alphabetic characters

	Accent the alphabetic characters at every two characters.
	If one character is left at the end, accent the last three characters.

	(Example)	ICBM: aISHIi biIEmu
			IBM	：aIBIIEmu
	If you want to read ICBM without stopping such as "aISHIBIIEmu,"
	the registration with dictionary is required.
	When the number is an integer, accent at hundreds digit, tens digits, or ones digit, and
	accent the thousands or upper digits individually.
	Accent the decimal fractions, the same as the alphabetic characters, at every two digits.

	(Note) Because this routine destroys the fresh accent information, 
		use acc_accent_raw[][4] instead of stc_accent_raw[][].
  ========================================================================*/
void ACC2000() 
{
	/* Tan-kanji */
	if(onsei_addr->onsei_kouseisystem==0)
	{
		ACC2700(pkind_tankanji,	pkind_tankanji);
		ACC2700(pkind_tankanji,	pkind_suf);
		/*	Combining "、" and "学校(GAKKOU)" in the phrase "朝、学校へ(ASA, GAKKOU E)" 
			causes a problem. Avoid combining them.*/
		/*ACC2900(pkind_tankanji,pkind_jiritsu);*/
	}

	/* alphabets */
	ACC2500(pkind_alpha1,	pkind_alpha1);	// Combine the accents of 2 alpha characters
	ACC2500(pkind_alphac,	pkind_alpha1);

	ACC2900(pkind_alpha1,	pkind_jiritsu);
	ACC2900(pkind_alphac,	pkind_jiritsu);

	/*
	 *	When a number follows after "第 (DAI)", "図 (ZU)", "表 (HYOU)", and the counter follows after the number, 
	 *	the accent combining order varies with the number of digits of the number.  Be aware of it.
	 *
	 *	(1)  For one-digit number
	 *		(Example) "第二世代 (DAINI SEDAI)"
	 *		The prefix "第 (DAI)" and the number "二 (NI)" are combined, they are Sinicised.
	 *		The words of Chinese origin "第二 (DAINI)" and "世代 (SEDAI)" are combined.
	 *			Combination format:  [[第 (DAI)］[二 (NI)]]世代 (SEDAI)]
	 *
	 *	(2)  When the number has two or more digits or decimals
	 *		(Example) "第十三世代 (DAI JYUSAN SEDAI)"
	 *		The prefix "第 (DAI)" and the number "十三 (JYUSAN)" are not combined.
	 *		The words of Chinese origin "第十三 (DAI JYUSAN)" and the counter "世代 (SEDAI)" are combined.
	 *			Combination format:  [第 (DAI)[[十三 (JYUSAN)][世代 (SEDAI)]]
	 *					[第 (DAI)[[五十 (GOJYU)][[五 (GO)][世代 (SEDAI)]]]]
	 */
	ACC2800();		/*The word "第 (DAI)" and a one-digit number is combined and Sinicised.*/

	/*
	 *	Number + Counter (including a user-registered word such as 1 + "segment")
	 */
	ACC2400();
	ACC2200(pkind_digiti0,	pkind_jiritsu,		pkind_digitic);
	ACC2200(pkind_digiti1,	pkind_jiritsu,		pkind_digitic);
	ACC2200(pkind_digiti2,	pkind_jiritsu,		pkind_digitic);
	ACC2200(pkind_digiti3,	pkind_jiritsu,		pkind_digitic);
	ACC2200(pkind_digitf,	pkind_jiritsu,		pkind_digitfc);

	ACC2600();		/* decimal point */

	/* digits */
	/*
	 * To read "74番" as "_}峠|ナ_}灼⑯_|ヨ_}殃渺_|" instead of "_}峠|ナ_}灼⑯巒舗渊|",
	 * the following processing must be canceled. This applies also to "740番" and "74番."
	 *	(See how it goes for a while.)
	 *
	 * For example, it makes a lot problems on processing of the word "年 (NEN)." The way of recognizing compound numerals is a problem to solve.
	 * 14 (JYUSHI) and 15 (JYUGO) are compound numerals, but 13 (JYU SAN) and 16 (JYU ROKU) are not compound numerals.
	 * To solve this problem, it is required to categorize the numerals precisely.(88-8-24)
	 *		(1) 11 to 19 are exceptions.
	 *		(2) 21 or higher depends on the tone, which are head-high, middle-raised, flattened, and ending-raised.
	 */
	ACC2300(pkind_digiti1,	pkind_digiti0);
	ACC2300(pkind_digiti2,	pkind_digiti0);
	ACC2300(pkind_digiti2,	pkind_digiti1);

	ACC2300(pkind_digitf,	pkind_digitf);
	ACC2300(pkind_digitfc,	pkind_digitf);

	/*
	 * In the past, numeral + counter and a single numeral are treated as adverbs, however
	 * it is better to treat them as self-sufficient words for handling the word like "1トントラック (1 TON TORAKKU)."
	 * Treat all numerals as self-sufficient words, and when any problem occurs, work it out separately.
	 */
	ACC2900(pkind_digiti0,	pkind_jiritsu);
	ACC2900(pkind_digiti1,	pkind_jiritsu);
	ACC2900(pkind_digiti2,	pkind_jiritsu);
	ACC2900(pkind_digiti3,	pkind_jiritsu);
	ACC2900(pkind_digitf,	pkind_jiritsu);
	ACC2900(pkind_digitic,	pkind_jiritsu);
	ACC2900(pkind_digitfc,	pkind_jiritsu);

	/* Because a 5-step conjunctive verb is equivalent to a noun, process it at first.*/
	ACC2200(pkind_verb_stem,	pkind_verb_renyou,	pkind_verb_stem);

	/*
	 * When a general prefix is added to a noun or SA-GYO irregular change nominal
	 * When a prefix "お(O)" is added to a noun, SA-GYO irregular change nominal, or 5-step conjunctive verb
	 */
	ACC2200(pkind_pref,			pkind_verb_stem,	pkind_verb_stem);
	ACC2200(pkind_pref,			pkind_adj_stem,		pkind_adj_stem);
	ACC2200(pkind_pref,			pkind_jiritsu,		pkind_jiritsu);
	ACC2200(pkind_pref,			pkind_ren,			pkind_jiritsu);

	/* Compound verb or compound adjective */
	ACC2200(pkind_verb_stem,	pkind_verb_stem,	pkind_verb_stem);
	ACC2200(pkind_adj_stem,		pkind_verb_stem,	pkind_verb_stem);
	ACC2200(pkind_verb_stem,	pkind_adj_stem,		pkind_adj_stem);
	ACC2200(pkind_adj_stem,		pkind_adj_stem,		pkind_adj_stem);
	ACC2900(pkind_verb_stem,	pkind_jiritsu);
	ACC2900(pkind_adj_stem,		pkind_jiritsu);

	/*
	 * When a prefix (especially two-letter prefix such as "具体(GUTAI)"
	 * has an ancillary word (such as "的(TEKI)" or a suffix "化(KA)."
	 */
	ACC2200(pkind_pref,		pkind_fuzoku,		pkind_jiritsu);
	ACC2200(pkind_pref,		pkind_suf,			pkind_jiritsu);

	/* Word of Chinese origin */
	ACC2K00();
	/* ((Numeral + Count) + Noun) is not processed.*/
	/* Compound verb or compound adjective */
	/* The preceding verb should be in conjunctive form only. The preceding adjective should be a stem only.*/
	ACC2200(pkind_jiritsu,	pkind_jiritsu,		pkind_jiritsu);

	/*
	 *	When a suffix is added to a noun, SA-GYO irregular change nominal, or 5-step conjunctive verb
	 *
	 * To convert "変換操作法 (HENKAN SOUSA HOU)" properly, it is probably better to process this after
	 *	the compound nouns are combined.
	 * However, to convert "視覚障害者 (SHIKAKU SHOUGAISHA)," it is better to process this before that.
	 * A compound noun ((Numeral + Counter) + Noun) is also possible, so an adverb should also be processed.
	 */
	ACC2200(pkind_jiritsu,	pkind_suf,			pkind_jiritsu);
	ACC2200(pkind_jiritsuc,	pkind_suf,			pkind_jiritsuc);
	ACC2200(pkind_adv,		pkind_suf,			pkind_jiritsu);

	/* Word of Chinese origin */
	ACC2K00();

	/* For processing Noun + Suffix + Noun */
	ACC2200(pkind_jiritsu,	pkind_jiritsu,		pkind_jiritsu);

	ACC2900(pkind_jiritsuc,	pkind_jiritsu);

	/*(Noun + Suffix) + Suffix */
	ACC2200(pkind_jiritsu,	pkind_suf,			pkind_jiritsu);

	/* Attributive */
	ACC2200(pkind_ren,		pkind_jiritsu,		pkind_jiritsu);
	ACC2200(pkind_ren,		pkind_fuzoku,		pkind_jiritsu);
	ACC2200(pkind_ren,		pkind_adv,			pkind_adv);

	/* Ancillary */
	ACC2200(pkind_jiritsu,	pkind_fuzoku,		pkind_jiritsu);
	ACC2200(pkind_adv,		pkind_fuzoku,		pkind_adv);
	ACC2200(pkind_tankanji,	pkind_fuzoku,		pkind_jiritsu);
}


/*========== ACC2K00() ===============================
	Function: The accents of words of Chinese origin are combined.
  ====================================================*/
void ACC2K00() 
{
	/*	Categorize the words of Chinese origin into solo word of Chinese origin 
		and compound word of Chinese origin.*/
	ACC1K00();	
	ACC2200(pkind_jiritsu,	pkind_jiritsu,	pkind_jiritsuc);
	ACC2200(pkind_jiritsuc,	pkind_jiritsu,	pkind_jiritsuc);
	ACC2200(pkind_jiritsu,	pkind_jiritsuc,	pkind_jiritsuc);
}


/*========== ACC2200(pkind1,pkind2,pkind) ===============================
	Function: When the types of two adjacent elements are pkind1 and pkind2, 
		combine their accent, and their type after combination is pkind.
  =======================================================================*/
void ACC2200(WORD pkind1, WORD pkind2, WORD pkind)
{
	register integer_16 i,j;
	integer_16 pp,pl,c,bno;
	BYTE a13,a21,a22;
	WORD case_tbl;
ACC2200_10:
	i=0;
ACC2200_20:
	for(;i<stc_ptr-1;++i)
	{
		if(phrase_len[i]!=0 && phrase_kind[i]==pkind1)
		{ goto ACC2200_100; }
	}
	return;

ACC2200_100:
	j=i+1; 
	while(phrase_len[j]==0 && j<stc_ptr)
	{ ++j; }
	if(j==stc_ptr)
	{ return; }
	if(phrase_kind[j]!=pkind2)
	{ ++i; goto ACC2200_20; }

	if(stc_pause[j]){ 
		++i; 
		goto ACC2200_20; 
	}

	/*
	 *	When the succeeding word of Chinese origin (it could be the head word) is a word of which accent combining is required, combine it.
	 */
	if((stc_ctl[j] & BITCTL_FIRST)&&(stc_stz[j] & BITSTZ_PREF)==0)
	{
		if(stc_mru[j] & BITMRU_ACON)
		{
			a13=acc_accent_raw[i][3];
			a21=acc_accent_raw[j][1];
			a22=acc_accent_raw[j][2];
			if(a13==0 && a21==0 && a22==0)
			{
				++i; 
				goto ACC2200_20;
			}
			else
			{
				goto ACC2200_200;
			}
		}
	}

	/*
	 *	When the succeeding word of Chinese origin (it could be the head word) is a word of which accent combining is to be renounced, do not combine it.
	 */
	if((stc_ctl[j] & BITCTL_FIRST)&&(stc_stz[j] & BITSTZ_PREF)==0)
	{
		if(stc_mru[j] & BITMRU_ACOFF)
		{
			goto ACC2200_140;
		}
	}

	if(pkind1!=pkind_jiritsu && pkind1!=pkind_jiritsuc)
	{ goto ACC2200_150; }

	if(pkind2!=pkind_jiritsu && pkind2!=pkind_jiritsuc)
	{ goto ACC2200_150; }

	if((stc_f2[i] & BITFLG2_KANGO)==0 &&(stc_stz[i] & BITSTZ_KANGO)==0)
	{
		goto ACC2200_150;
	}
	if((stc_f2[j] & BITFLG2_KANGO)==0 &&(stc_stz[j] & BITSTZ_KANGO)==0)
	{
		goto ACC2200_150;
	}
	/*
	 * Both ith word and jth word are words of Chinese origin.
	 *
	 *	If the combine word has six or more letters, do not combine them.
	 *	However, when the jth word has only one letter, it is an exception. (Suffix) (63/10/18)
	 */
	if(knj_number(j)==1 && stc_in_len[j]==1)
	{ goto ACC2200_150; }

	if(knj_number(i)+knj_number(j)>6)
	{ goto ACC2200_140; }

	goto ACC2200_150;

ACC2200_140:
	acc_accent_raw[j][1]=acc_accent_raw[j][2]=0;
	++i; goto ACC2200_20;

ACC2200_150:
	a13=acc_accent_raw[i][3];
	a21=acc_accent_raw[j][1];
	a22=acc_accent_raw[j][2];

	/*
	 *	Compound verb or compound adjective
	 *
	 *	"始め (HAJIME)" in "動き始める (UGOKI HAJIMERU)" is a verb, but "始め (HAJIME)" in "動き始めが (UGOKI HAJIME GA)" is a noun.
	 *	Therefore, check all back-end numbers of jth word to find whether or not it is a verb.
	 *	This check is performed by ACC1000().
	 */
	if( (pkind1==pkind_verb_stem||pkind1==pkind_adj_stem) &&
		(pkind2==pkind_verb_stem||pkind2==pkind_adj_stem))
	{
		ACC22CV(i,j); 
		goto ACC2200_360;
	}
#if defined(Biceps_Femoris)
	if(pkind1==pkind_verb_stem||pkind1==pkind_adj_stem)
	{
		for(bno=0;bno<stc_nbno[j];++bno)
		{
			if(pk=stc_bno[j][bno])
			{
				if( bno_tbl[pk-1]==pkind_verb_stem || 
					bno_tbl[pk-1]==pkind_adj_stem )
				{
					ACC22CV(i,j); 
					goto ACC2200_360;
				}
			}
		}
	}
#endif

	/*
	 * When both it does not affect either preceding or succeeding word, the accents are not combined.
	 * When the variation rule of the word is specified, it is recognized as they are compound.
	 *
	 * For example, when "世界 (SEKAI)" and "最初 (SAISHO)" are combined for "世界最初の (SEKAI SAISHO NO),"
	 * if "の (NO)" is combined, "の (NO)" flattens "世界最初 (SEKAI SAISHO)."
	 * When "の (NO)" is combined with "世界 (SEKAI)," and "最初 (SAISHO)," "の (NO)" only affects "最初 (SAISHO)."
	 */
	if(a13==0 && a21==0 && a22==0)
	{
		++i; 
		goto ACC2200_20;
	}

	/* Do not combine the word immediately after the conjunctive modifier. */
	for(c=0;c<stc_nbno[i];++c)
	{
		if(bno=stc_bno[i][c])
		{
			case_tbl=Fdd_Header.Fdd_BnoTblOfs;
			/* Only the lower three bits are related to the case.*/
			/* Words except conclusive form, attributive case, or conjunctive modifier case are combined.*/
			if((FddHDR[case_tbl+bno-1] & 0x07)==0x00)
			{ goto ACC2200_155; }

			/* When the word immediately after the word of conclusive form, attributive modifier case, or conjunctive modifier case is */
			if(stc_ctl[j] & BITCTL_FIRST)
			{
				/* a self-sufficient word, do not combine it.*/
				++i; 
				goto ACC2200_20;
			}
			else
			{
				/* If it is an ancillary, combine it.*/
				goto ACC2200_155;
			}
		}
	}

ACC2200_155:

#if defined(LIE)/* Lie */
	/* When the preceding segment is an item of 1B or 5B, and the preceding segment is head-high SA-GYO irregular change nominal (of Chinese origin), 
	 * the succeeding segment is 58 type. (87.6.20) such as "られ(RARE)"
	 * It is because the accent of the stem is not easily changed in SA-GYO irregular change nominal + ancillary.
	 *if((stc_f2[i]&BITFLG2_KANGO)||(stc_stz[i]&BITSTZ_KANGO)){
	 *	if((stc_f2[j]&BITFLG2_KANGO)||(stc_stz[j]&BITSTZ_KANGO)){ goto ACC2200_195; }
	 *	if(stc_bno[i][0]==Fdd_Header.Fdd_BnoSahen){
	 *		a21=0; if(a22==11){ if(accent0[phrase_ptr[i]]==0x82){ a22=8; } }
	 *	}
	 *}
	 */
#endif

#if !defined(LIE)/* True */
	/*When a21=9, Alternately, if there is an ancillary that may flatten its preceding word precedes, 
	 * and when it locates after the peak of the accent, the succeeding element is always pronounced with low pitch.
	 * In other words, the succeeding segment is 58 type. (87.6.23) such as "られ(RARE)"
	 */
#endif

	/* For example, when the item of 9B follows the SA-GYO irregular change verb, and it is not flattened, 
	 * the succeeding word is pronounced with low pitch not high pitch even if the word is possibly pronounced with high pitch.
	 * Also when the element of 9B follows the head-high or middle high SA-GYO irregular change verb, the succeeding word is always pronounced with low pitch.
	 * Ignore all except ancillaries.
	 */
	pp=phrase_ptr[i]; 
	pl=phrase_len[i];
	/*if((stc_ctl[j] & BITCTL_FIRST)==0 && (a21==9 || j-i>1)){*/
	/*
	 * Items of B are 0B, 1B, or 9B.
	 *		Example of 1B:  帰「り」 (KAE"RI")
	 *		Example of 5B:  帰「っ」た (KAE"T"TA), 返「っ」た (KAE"T"TA), 通「っ」た (KAYO"T"TA)
	 *		Example of 0B:  有難う「ござい」ました(ARIGATOU "GOZAI" MASHITA)
	 * Whether or not the item of 0B or 9B has passed the fall of the stem is considered, but the item of 1B is not considered.
	 * However, whether or not the item of 1B has passed the fall of "stem + ending" is considered.
	 */
	/*if((phrase_kind[j]==pkind_fuzoku) && (a21==9 || a21==0 || j-i>1)){*/
	/*
	 *	For (j-i>1), (prefix + self-sufficient word) is also the target.
	 *	For (phrase_kind[j-1]==pkind_fuzoku), it becomes the target only when its preceding word is ancillary.*/
	if(phrase_kind[j]==pkind_fuzoku)
	{
		if(a21==9 || a21==0 || phrase_kind[j-1]==pkind_fuzoku)
		{
			if(pl>1 && accent0[pp+pl-1]==1)
			{
				/* All words that may be pronounced with high pitch are to be the targets. */
				/*if(a22==1 || a22==2 || a22==5 || a22==11){*/
				a21=0; 
				a22=8;
				/*}*/
			}
		}
	}

	/* When its succeeding segment is 00, do not combine it. */
	if((a21==0||a21==0xFF)&&(a22==0||a22==0xFF))
	{
		/* When it is an ancillary, it should be considered as a group even if its accent is not combined. */
		if(pkind1==pkind_pref||pkind1==pkind_ren)
		{ goto ACC2200_200; }

		if(pkind2==pkind_suf||pkind2==pkind_fuzoku)
		{	
			goto ACC2200_360; 
		}
		++i; 
		goto ACC2200_20;
	}

ACC2200_200:;
	/*
	 *	Combination of the prefix "お(O)"
	 * "お(O)" is for a13=1. pkind_pref and pkind_prefo are not distinguished.
	 * if(pkind1==pkind_prefo){ ACC22PO(i,j); goto ACC2200_360; }
	 */

	/*
	 *	When the succeeding element cannot be the head, ignore a13.
	 *	(Example) Use a13 for "お手紙拝見しました (OTEGAMI HAIKEN SHIMASHITA)。" or "私塩野です (WATASHI SHIONO DESU)。"
	 *	(Example) Ignore a13 for "お手紙を拝見しました (OTEGAMI WO HAIKEN SHIMASHITA)。" or "私は塩野です (WATASHI HA SHIONO DESU)。"
	 */
	if((stc_ctl[j] & BITCTL_FIRST)==0 || a13==0)
	{
		/*
		 *	 When the succeeding element cannot be the head, or it does not affect the preceding element, 
		 * consider the effect of the succeeding element on the preceding one.
		 */
		ACC22XX(i,j,a21,a22);
	}
	else
	{
		/*
		 *	 When the succeeding element can be the head, 
		 * if it affects the preceding element, it is processed by priority, and 
		 * ignore the effect of the succeeding element on the preceding one.
		 */
        switch(a13)
		{
		case  1:	ACC22PO(i,j); break;
		case  2:	ACC2232(i,j); break;
		case  3:	ACC2233(i,j); break;
		case  4:	break;
		case  5:	break;
		case  6:	
			acc_accent_raw[j][1]=0; 
			acc_accent_raw[j][2]=0;
			++i; 
			goto ACC2200_20;	/* Do not combine them.*/
		case  7:	ACC0004(j); break;
		case  8:	break;
		case  9:	ACC2239(i,j); break;
		default:	break;
		}
	}

ACC2200_360:
	phrase_len[i]+=phrase_len[j];
	phrase_kind[i]= (BYTE)pkind;
	phrase_ptr[j]=phrase_len[j]=0;
	/*
	 *	Equalize the effect of "self-sufficient word + ancillary" on the preceding item and the effect of the preceding "self-sufficient word."
	 *	For the effect of "self-sufficient word + self-sufficient word" on the preceding item,
	 *	use the effect of the preceding "self-sufficient word" on the preceding one if it has one, 
	 *	and if not, use the effect of succeeding "self-sufficient word."
	 *
	 *	For example, the effect of "札幌市 (SAPPORO SHI)" on the preceding item is the same as the effect of "札幌 (SAPPORO)," and 
	 *	it is different from the effect of "市 (SHI)."
	 */
	if(stc_ctl[j] & BITCTL_FIRST)
	{
		/*
		 *	There is no problem in "Japanese analysis" + "system," however,
		 *	for "Japanese" + "analysis system," the combination rule of the "analysis system" 
		 *	causes a problem. the combination rule of the "analysis system" is different from the combination rule of "analysis" and "system," and 
		 *	 therefore, the preceding word may be flattened and it may be pronounced with high pitch and it is lowered at the fall 
		 *	of its own.
		 */
		acc_accent_raw[i][1]=1;		/* Flatten the preceding item. */
		acc_accent_raw[i][2]=101;	/* Pronounced with high pitch. */
#if defined(Perhaps_LIE)
		/* The followings are lies. They are not lies, but there are too many exceptions.*/
		if(acc_accent_raw[i][1]==0xFF)
		{
			acc_accent_raw[i][1]=acc_accent_raw[j][1];
		}
		if(acc_accent_raw[i][2]==0xFF)
		{
			acc_accent_raw[i][2]=acc_accent_raw[j][2];
		}
#endif
	}
	/*
	 *	Equalize the effect of "prefix + noun" on the succeeding item and the effect of "noun."
	 */
	if(stc_ctl[i] & BITCTL_PREF)
	{
		acc_accent_raw[i][3]=acc_accent_raw[j][3];
	}
	goto ACC2200_10;
}


/*========== ACC2300(dk1,dk2) ================================================
	Function: Combine the accents of numbers and make one number.

	When the preceding number is one-digit number, and the succeeding number is also one-digit number, the pitch of the succeeding one is lowered.
	When the number is two- or more-digit number, it is lowered except when it is head-high type.
	When the preceding number is either middle-raised or ending-raised type, if the succeeding number is flattened type, the pitch is entirely flattened.
	If the succeeding number is up-and-down type, the preceding number is flattened, and the succeeding number is pronounced with high pitch, and
	it is lowered at its own fall.
	The preceding number can never be flattened. The possible flattened type number is 3 only.
	However, if the succeeding number is pronounced with low pitch, too may mora numbers may 
	cause to returning to the original accent.


	(Example) 301: Head-high + One-digit				さ'んびゃくいち (SA'NBYAKU ICHI)
			320: Head-high + Two- or more-digit and head-high		さ'んびゃく　に'じゅー (SA'NBYAKU NI'JYU)
			311: Head-high + Two- or more-digit and not head-high	さ'んびゃくじゅーいち(SA'NBYAKU JYUICHI)
										or さ'んびゃく　じゅーいち(SA'NBYAKU JYUICHI)
			63: Middle-raised + Flattened				ろくじゅーさん(ROKUJYU SAN)
			67: Middle-raised + Head-high				ろくじゅーな'な(ROKUJYU NA'NA)

	(Exception) 77 and 67
			Both are "middle-raised + head-high," and 7 of 67 is pronounced with high pitch, but
		7 of 77 begins with low pitch. The accent of 700 has the same phenomenon.
			Even if the preceding number is middle-raised, when more than two syllables of the succeeding number are low, it seems that it works as
		head-high type.
  ============================================================================*/
void ACC2300(WORD dk1, WORD dk2)
{
	register integer_16 i,j;
	integer_16 ip,il,jp,jl;

ACC2300_10:
	i=0;
ACC2300_20:
	for(;i<stc_ptr-1;++i)
	{
		if(phrase_len[i]!=0 && phrase_kind[i]==dk1)
		{ goto ACC2300_100; }
	}
	return;

ACC2300_100:
	j=i+1; 
	while(phrase_len[j]==0 && j<stc_ptr)
	{ ++j; }
	if(j==stc_ptr)
	{ return; }
	if(phrase_kind[j]!=dk2)
	{ 
		++i; 
		goto ACC2300_20; 
	}
	/*a1=stc_dman[i]*100+stc_dexp[i];*/
	/*a2=stc_dman[j]*100+stc_dexp[j];*/

	ip=phrase_ptr[i]; 
	jp=phrase_ptr[j];
	il=phrase_len[i]; 
	jl=phrase_len[j];

	/*
	 * The accents of "Number + (number + counter)" or "number + number" are combined, but
	 * the accents of "(number + counter) + (number + counter)" are not combined.
	 */
	if(stc_dman[j-1]==DMANKIND_NUM)
	{ goto ACC2300_360; }

	/*
	 *	The decimal point is pronounced with low pitch.
	 *	The one-digit number before the decimal point is flattened.
	 *	The one-digit number is changed to head-high if the processing of a double consonant or syllabic nasal is performed later.
	 *	if(stc_dman[j]==DMANKIND_DP){
	 *		if(stc_dexp[i]==0){ ACC0001(i); }
	 *		ACC0004(j); goto ACC2300_360;
	 *	}
	 */

	if(dk2==pkind_digitf)
	{		/* dk1=digitf or digitfc */
		ACC000H(i); 
		ACC0001(j); 
		goto ACC2300_360;
	}
	/*
	 *	When the preceding number is head-high, or
	 *	When the preceding number is middle-raised and the last two digits are pronounced with low pitch, such as 70 or 700
	 */
	if( accent0[ip]==0x82 || 
		(il>2 && accent0[ip+il-1]==1 && accent0[ip+il-2]==1) )
	{
		/*
		 *	The one-digit number is always pronounced with low pitch.
		 *	The two or more digit numbers are pronounced with low pitch except when the number is head-high.
		 */
		if(stc_dexp[j]==0 || (accent0[jp]!=0x82 && stc_dexp[j]>1))
		{
			/* It is pronounced with low pitch unless there are too many low mora phonemes. */
			if(count_low(j)<=MAX_TONE)
			{ ACC0004(j); }
		}
		goto ACC2300_360;
	}

	if(accent0[jp+jl-1]==1 || accent0[jp+jl-1]==0x82)
	{
		ACC000H(i);					/* Middle-raised or ending-raised + up-and-down */
		if(accent0[jp]==1)
		{ accent0[jp]=2; }
	}
	else{
		ACC000H(i); 
		ACC0005(j);		/* Middle-raised or ending-raised + up-and-down */
	}

ACC2300_360:
	phrase_len[i]+=phrase_len[j];
	phrase_kind[i] = (dk2==pkind_digitf ? pkind_digitfc : pkind_digitic);

	phrase_ptr[j]=phrase_len[j]=0;
	acc_accent_raw[i][1]=0;
	acc_accent_raw[i][2]=0;
	goto ACC2300_10;
}


/*========== ACC2400() =======================================
	Function: Combine the accents of numbers and counters, and make one number.
  ============================================================*/
void ACC2400() 
{
	register integer_16 i,j;
	BYTE a20,a21;

ACC2400_10:
	i=0;
ACC2400_20:
	for(;i<stc_ptr-1;++i)
	{
		if(phrase_len[i])
		{
			if(phrase_kind[i]==pkind_digitf)
			{ goto ACC2400_100; }
			if(phrase_kind[i]/10==pkind_digiti0/10)
			{ goto ACC2400_100; }
		}
	}
	return;
ACC2400_100:
	j=i+1; 
	while(phrase_len[j]==0 && j<stc_ptr)
	{ ++j; }
	if(j==stc_ptr)
	{ return; }
	if(stc_dman[j]!=DMANKIND_NUM)
	{ ++i; goto ACC2400_20; }
	/*a1 =stc_dman[i]*100+stc_dexp[i];*/
	a20=acc_accent_raw[j][0];
	a21=acc_accent_raw[j][1];

	/*
	 * "複数本(FUKUSUU HON)", etc. : "複数(FUKUSUU)" is flattened.
	 *	At a21=3, the counter is pronounced with high pitch and lowered at its own fall.
	 *	In other cases, it pronounced with high pitch and flattened.
	 */
	if(stc_dman[i]==DMANKIND_PL)
	{
		ACC000H(i);
		if(a21==3)
		{
			if(accent0[phrase_ptr[j]]==1)
			{ accent0[phrase_ptr[j]]=2; }
		}
		else
		{
			ACC0005(j);
		}
		goto ACC2400_360;
	}

	if(a20==1 && a21==1){ ACC2411(i,j); goto ACC2400_360; }
	if(a20==1          ){ ACC2410(i,j); goto ACC2400_360; }

	if(a20==2 && a21==1){ ACC2421(i,j); goto ACC2400_360; }
	if(a20==2 && a21==2){ ACC2422(i,j); goto ACC2400_360; }
	if(a20==2 && a21==3){ ACC2423(i,j); goto ACC2400_360; }
	if(a20==2 && a21==4){ ACC2424(i,j); goto ACC2400_360; }
	if(a20==2          ){ ACC2420(i,j); goto ACC2400_360; }

	if(a20==3          ){ ACC2430(i,j,a21); goto ACC2400_360; }

	if(a20==4 && a21==1){ ACC2441(i,j); goto ACC2400_360; }
	if(a20==4 && a21==2){ ACC2442(i,j); goto ACC2400_360; }
	if(a20==4 && a21==3){ ACC2443(i,j); goto ACC2400_360; }
	if(a20==4          ){ ACC2440(i,j); goto ACC2400_360; }

	if(a20==5          ){ ACC2450(i,j); goto ACC2400_360; }

	if(a20==6 && a21==1){ ACC2461(i,j); goto ACC2400_360; }
	if(a20==6 && a21==2){ ACC2462(i,j); goto ACC2400_360; }
	if(a20==6 && a21==3){ ACC2463(i,j); goto ACC2400_360; }
	if(a20==6          ){ ACC2460(i,j); goto ACC2400_360; }

ACC2400_360:
	phrase_len[i]+=phrase_len[j]; 
	phrase_ptr[j]=phrase_len[j]=0;
	acc_accent_raw[i][1]=acc_accent_raw[i][2]=0;
	goto ACC2400_10;
}


/*========== ACC2500(ak1,ak2) ==============================
	Function: Combine the accents of alphabetic characters, and make one alphabetic character.
  ==========================================================*/
void ACC2500(WORD ak1, WORD ak2) 
{
	register integer_16 i,j;

ACC2500_10:
	i=0;

ACC2500_20:
	for(;i<stc_ptr-1;++i)
	{
		if(phrase_len[i]!=0 && phrase_kind[i]==ak1)
		{ 
			goto ACC2500_100; 
		}
	}
	return;

ACC2500_100:
	j=i+1; 
	while(phrase_len[j]==0 && j<stc_ptr)
	{ ++j; }
	
	if(j==stc_ptr)
	{ return; }
	
	if(phrase_kind[j]!=ak2)
	{ 
		++i; 
		goto ACC2500_20; 
	}

	ACC000H(i); 
	ACC0001(j);

	phrase_len[i]+=phrase_len[j]; 
	phrase_kind[i]=pkind_alphac;
	phrase_ptr[j]=phrase_len[j]=0;
	acc_accent_raw[i][1]=acc_accent_raw[i][2]=0;
	goto ACC2500_10;
}


/*========== ACC2600() =====================================
	Function:  Processing of decimal points
  ==========================================================*/
void ACC2600() 
{
	register integer_16 i,j;
ACC2600_10:
	i=0;
ACC2600_20:
	for(;i<stc_ptr-1;++i)
	{
		if(phrase_len[i]!=0)
		{
			if( phrase_kind[i]>=pkind_digiti0 && 
				phrase_kind[i]<=pkind_digitfc)
			{
				goto ACC2600_100;
			}
		}
	}
	return;

ACC2600_100:
	j=i+1; 
	while(phrase_len[j]==0 && j<stc_ptr)
	{ ++j; }
	if(j==stc_ptr)
	{ return; }

	/*if(phrase_kind[j]!=pkind_digiti0){ ++i; goto ACC2600_20; }*/
	if(stc_dman[j] != DMANKIND_DP)
	{ 
		++i; 
		goto ACC2600_20; 
	}

	/*
	 *	The decimal point is pronounced with low pitch.
	 *	The variation rule of the number preceding the decimal point is described below.
	 *  When there are two mora phonemes, it is head-high, and there are three or more mora phonemes, the pitch is middle-raised, which is lowered at the last syllable.
	 *
	 *		￣＿、＿￣＿、＿￣￣＿、＿￣￣￣＿
	 */
	/*if(stc_dman[j]==DMANKIND_DP){*/
	if(phrase_len[i]==2)
	{ ACC0001(i); }
	if(phrase_len[i]>2)
	{ 
		ACC0003(i, (integer_16)(phrase_len[i]-1)); 
	}
	ACC0004(j);
	/*}else{*/
		/*++i; goto ACC2600_20;*/
	/*}*/

	phrase_len[i]+=phrase_len[j];

	/*phrase_kind[i]=(phrase_kind[i]==pkind_digitfc? pkind_digitfc:pkind_digitic);*/
	phrase_kind[i]=pkind_digitic;

	phrase_ptr[j]=phrase_len[j]=0;
	acc_accent_raw[i][1]=acc_accent_raw[i][2]=0;
	goto ACC2600_10;
}


/*========== ACC2700(ak1,ak2) ==============================================
	Function: Combine the accents of Tan-kanji and Tan-kanji, and make one Tan-kanji.
			The result accent type is the flattened type regardless of the original accent type.

		Hiragana, Katakana, and special symbols are all flattened.
		A single one keeps the original accent without being flattened.
  ==========================================================================*/
void ACC2700(WORD ak1, WORD ak2)
{
	register integer_16 i,j;
ACC2700_10:
	i=0;
ACC2700_20:
	for(;i<stc_ptr-1;++i)
	{
		if(phrase_len[i]!=0 && phrase_kind[i]==ak1)
		{ goto ACC2700_100; }
	}
	return;
ACC2700_100:
	j=i+1; 
	while(phrase_len[j]==0 && j<stc_ptr)
	{ ++j; }
	if(j==stc_ptr)
	{ return; }
	if(phrase_kind[j]!=ak2)
	{ ++i; goto ACC2700_20; }

	if(j<stc_ptr-1 && phrase_kind[j+1]==pkind_tankanji)
	{
		/* When there is another Tan-kanji after the jth Tan-kanji, the entire element is flattened.*/
		ACC000H(i); 
		ACC0005(j);
	}
	else
	{
		/*
		 *	 When there is no other Tan-kanji after the jth Tan-kaji, 
		 * the effect of jth Tan-kanji on the preceding one and its own variation.
		 */
		ACC22XX(i,j,acc_accent_raw[j][1],acc_accent_raw[j][2]);
	}

	phrase_len[i]+=phrase_len[j]; 
	phrase_kind[i]=pkind_tankanji;
	phrase_ptr[j]=phrase_len[j]=0;
	acc_accent_raw[i][1]=acc_accent_raw[i][2]=0;
	goto ACC2700_10;
}


/*========== ACC2800() =====================================================
	Function:  Combine the element of which 54th column of the master is 4 and a number.
		There are the following three types of the element of which 54th column of the master is 4.
			"第(DAI)," "図(ZU)," "表(HYOU)"

		It is combined only when the number is a one-digit number, and it is not combined when the number is a two- or more-digit number or a decimal number.
		When the element is head-high, such as "(DAI)," the number is pronounced with low pitch.
		When the element is not head-high, such as "表(DAI)," the number is pronounced with high pitch.

	(Example) The "第１(DAI ICHI)" is combined, and "1 (ICHI)" is pronounced with low pitch. "第25 (DAI NIJUGO)" is not combined.
		(Example) The "図１(ZU ICHI)" is combined, and "1 (ICHI)" is pronounced with high pitch. "図25 (ZU NIJUGO)" is not combined.
		(Example) The "表1 (HYOU ICHI)" is combined, and "1 (ICHI)" is pronounced with high pitch. "表25 (HYOU NIJUGO)" is not combined.

	(Remarks)  When the element has one mora phonemes and it is flattened such as "図(ZU)," or when the element is a two- or more-digit number, 
			it is better to make the "図 (ZU) head-high except when the number is head-high, 
			or it is better to make a pause.
				(For example, "図 (ZU)"
  ==========================================================================*/
void ACC2800() 
{
	register integer_16 i,j;
	BYTE al;
	/* If ceptr or celen is destroyed, it causes a problem when there is no next choice.  Be aware of it.*/
	ceptr_sav=ceptr; 
	celen_sav=celen;
ACC2800_10:
	i=0;
ACC2800_20:
	for(;i<stc_ptr-1;++i)
	{
		if(phrase_len[i]!=0 && acc_accent_raw[i][3]==4)
		{ goto ACC2800_100; }
	}
	goto ACC2800_999;

ACC2800_100:
	j=i+1; 
	while(phrase_len[j]==0 && j<stc_ptr)
	{ ++j; }
	if(j==stc_ptr)
	{ goto ACC2800_999; }

	al=phrase_kind[j];
	if((al==pkind_digitf)||(al/10==pkind_digiti0/10))
	{
		/* Measure the actual position and length of the succeeding number.*/
		ceptr=stc_in_ptr[j]; 
		celen=n_inert-ceptr;
		while(OTHER2000()==0)
		{ celen=INERT2000(ceptr,celen); }

		/* Process only the one-digit integer.*/
		/* Processed only when there is no counter immediately after the number.*/
		if(NUM0010()==1 && NUM0020()==0)
		{
			if(stc_ctl[j+1] & BITCTL_FIRST)
			{
				goto ACC2800_200;
			}
		}
	}
	++i; 
	goto ACC2800_20;

ACC2800_200:
	if(accent0[phrase_ptr[i]]==1)
	{
		if(accent0[phrase_ptr[j]]==1)
		{ accent0[phrase_ptr[j]]=2; }
	}
	else
	{
		ACC0004(j);
	}
	phrase_len[i]+=phrase_len[j]; 
	phrase_kind[i]=pkind_jiritsu;
	phrase_ptr[j]=phrase_len[j]=0;
	acc_accent_raw[i][1]=acc_accent_raw[i][2]=acc_accent_raw[i][3]=0;
	goto ACC2800_10;

ACC2800_999:
	ceptr=ceptr_sav; 
	celen=celen_sav;
	return;
}


/*========== ACC2900(pkind1,pkind2) ==========================
	Function: Convert pkind1 of phrase_kind[] with pkind2.
  ============================================================*/
void ACC2900(WORD pkind1, WORD pkind2)
{
	register integer_16 i;
	for(i=stc_ptr;i--;)
	{
		if(phrase_kind[i]==pkind1)
		{ 
			phrase_kind[i]=(BYTE)pkind2; 
		}
	}
}

/***************************** END OF ACC_2000.C *****************************/

