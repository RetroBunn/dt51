/*C_HEADER_FILE****************************************************************
FILE			:	Pinyin2Ascii.c
DESC			:	
TABS			:	4
OWNER			:	
DATE CREATED:	

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
//#include <stdlib.h> //moved to port.h for each platform 02/21/06 mlt
//#include <string.h> //moved to port.h for each platform 02/21/06 mlt
#include "port.h"
#include "Mandarin.h"

PINYIN_ASCII tPinyin2Ascii[] =
{
	{"a",		"A"},
	{"ai",		"6"},
	{"an",		"An"},
	{"ang",		"aN"},
	{"ao",		"7"},
	{"ba",		"bA"},
	{"bai",		"b6"},
	{"ban",		"bAn"},
	{"bang",	"baN"},
	{"bao",		"b7"},
	{"bei",		"be"},
	{"ben",		"b^n"},
	{"beng",	"b^N"},
	{"bi",		"bi"},
	{"bian",	"bJEn"},
	{"biao",	"bJ7"},
	{"bie",		"bJE"},
	{"bin",		"bin"},
	{"bing",	"biN"},
	{"bo",		"bO"},
	{"bu",		"bu"},
	{"ca",		"cA"},
	{"cai",		"c6"},
	{"can",		"cAn"},
	{"cang",	"caN"},
	{"cao",		"c7"},
	{"ce",		"c3"},
	{"cen",		"c^n"},
	{"ceng",	"c^N"},
	{"cha",		"CA"},
	{"chai",	"C6"},
	{"chan",	"CAn"},
	{"chang",	"CaN"},
	{"chao",	"C7"},
	{"che",		"C3"},
	{"chen",	"C^n"},
	{"cheng",	"C^N"},
	{"chi",		"C2"},
	{"chong",	"C5N"},
	{"chou",	"Co"},
	{"chu",		"Cu"},
	{"chuai",	"CW6"},
	{"chuan",	"CWAn"},
	{"chuang",	"CWaN"},
	{"chui",	"CWe"},
	{"chun",	"CWXn"},
	{"chuo",	"CWO"},
	{"ci",		"cI"},
	{"cong",	"c5N"},
	{"cou",		"co"},
	{"cu",		"cu"},
	{"cuan",	"cWAn"},
	{"cui",		"cWe"},
	{"cun",		"cWXn"},
	{"cuo",		"cWO"},
	{"da",		"dA"},
	{"dai",		"d6"},
	{"dan",		"dAn"},
	{"dang",	"daN"},
	{"dao",		"d7"},
	{"de",		"d3"},
	{"dei",		"de"},
	{"deng",	"d^N"},
	{"di",		"di"},
	{"dia",		"dJA"},
	{"dian",	"dJEn"},
	{"diao",	"dJ7"},
	{"die",		"dJE"},
	{"ding",	"diN"},
	{"diu",		"dJo"},
	{"dong",	"d5N"},
	{"dou",		"do"},
	{"du",		"du"},
	{"duan",	"dWAn"},
	{"dui",		"dWe"},
	{"dun",		"dWXn"},
	{"duo",		"dWO"},
	{"e",		"3"},
	{"ei",		"e"},
	{"en",		"^n"},
	{"eng",		"^N"},
	{"er",		"8"},
	{"fa",		"fA"},
	{"fan",		"fAn"},
	{"fang",	"faN"},
	{"fei",		"fe"},
	{"fen",		"f^n"},
	{"feng",	"f^N"},
	{"fo",		"fO"},
	{"fou",		"fo"},
	{"fu",		"fu"},
	{"ga",		"gA"},
	{"gai",		"g6"},
	{"gan",		"gAn"},
	{"gang",	"gaN"},
	{"gao",		"g7"},
	{"ge",		"g3"},
	{"gei",		"ge"},
	{"gen",		"g^n"},
	{"geng",	"g^N"},
	{"gong",	"g5N"},
	{"gou",		"go"},
	{"gu",		"gu"},
	{"gua",		"gWA"},
	{"guai",	"gW6"},
	{"guan",	"gWAn"},
	{"guang",	"gWaN"},
	{"gui",		"gWe"},
	{"gun",		"gWXn"},
	{"guo",		"gWO"},
	{"ha",		"hA"},
	{"hai",		"h6"},
	{"han",		"hAn"},
	{"hang",	"haN"},
	{"hao",		"h7"},
	{"he",		"h3"},
	{"hei",		"he"},
	{"hen",		"h^n"},
	{"heng",	"h^N"},
	{"hong",	"h5N"},
	{"hou",		"ho"},
	{"hu",		"hu"},
	{"hua",		"hWA"},
	{"huai",	"hW6"},
	{"huan",	"hWAn"},
	{"huang",	"hWaN"},
	{"hui",		"hWe"},
	{"hun",		"hWXn"},
	{"huo",		"hWO"},
	{"ji",		"ji"},
	{"jia",		"jJA"},
	{"jian",	"jJEn"},
	{"jiang",	"jJaN"},
	{"jiao",	"jJ7"},
	{"jie",		"jJE"},
	{"jin",		"jin"},
	{"jing",	"jiN"},
	{"jiong",	"jJ5N"},
	{"jiu",		"jJo"},
	{"ju",		"jU"},
	{"juan",	"jUAn"},
	{"jue",		"jUE"},
	{"jun",		"jUn"},
	{"ka",		"kA"},
	{"kai",		"k6"},
	{"kan",		"kAn"},
	{"kang",	"kaN"},
	{"kao",		"k7"},
	{"ke",		"k3"},
	{"ken",		"k^n"},
	{"keng",	"k^N"},
	{"kong",	"k5N"},
	{"kou",		"ko"},
	{"ku",		"ku"},
	{"kua",		"kWA"},
	{"kuai",	"kW6"},
	{"kuan",	"kWAn"},
	{"kuang",	"kWaN"},
	{"kui",		"kWe"},
	{"kun",		"kWXn"},
	{"kuo",		"kWO"},
	{"la",		"lA"},
	{"lai",		"l6"},
	{"lan",		"lAn"},
	{"lang",	"laN"},
	{"lao",		"l7"},
	{"le",		"l3"},
	{"lei",		"le"},
	{"leng",	"l^N"},
	{"li",		"li"},
	{"lia",		"lJA"},
	{"lian",	"lJEn"},
	{"liang",	"lJaN"},
	{"liao",	"lJ7"},
	{"lie",		"lJE"},
	{"lin",		"lin"},
	{"ling",	"liN"},
	{"liu",		"lJo"},
	{"long",	"l5N"},
	{"lou",		"lo"},
	{"lu",		"lu"},
#ifdef CASIO_SH3
	{"l0xfc",		"lU"}, //0xfc = "ü"
#else
	{"lü",		"lU"},
#endif
	{"luan",	"lWAn"},
	{"lue",		"lUE"},
#ifdef CASIO_SH3
	{"l0xfce",		"lUE"}, //0xfc = "ü"
#else
	{"lüe",		"lUE"},
#endif
	{"lun",		"lWXn"},
	{"luo",		"lWO"},
	{"lv",		"lU"},		// alternate to lü
	{"lve",		"lUE"},		// alternate to lüe
	{"ma",		"mA"},
	{"mai",		"m6"},
	{"man",		"mAn"},
	{"mang",	"maN"},
	{"mao",		"m7"},
	{"me",		"m3"},
	{"mei",		"me"},
	{"men",		"m^n"},
	{"meng",	"m^N"},
	{"mi",		"mi"},
	{"mian",	"mJEn"},
	{"miao",	"mJ7"},
	{"mie",		"mJE"},
	{"min",		"min"},
	{"ming",	"miN"},
	{"miu",		"mJo"},
	{"mo",		"mO"},
	{"mou",		"mo"},
	{"mu",		"mu"},
	{"na",		"nA"},
	{"nai",		"n6"},
	{"nan",		"nAn"},
	{"nang",	"naN"},
	{"nao",		"n7"},
	{"ne",		"n3"},
	{"nei",		"ne"},
	{"nen",		"n^n"},
	{"neng",	"n^N"},
	{"ng",		"N"},
	{"ni",		"ni"},
	{"nian",	"nJEn"},
	{"niang",	"nJaN"},
	{"niao",	"nJ7"},
	{"nie",		"nJE"},
	{"nin",		"nin"},
	{"ning",	"niN"},
	{"niu",		"nJo"},
	{"nong",	"n5N"},
	{"nou",		"no"},
	{"nu",		"nu"},
#ifdef CASIO_SH3
	{"n0xfc",		"nU"}, //0xfc = "ü"
#else
	{"nü",		"nU"},
#endif
	{"nuan",	"nWAn"}, 
	{"nue",		"nUE"},
	{"nüe",		"nUE"},
	{"nuo",		"nWO"},
	{"nv",		"nU"},		// alternate to nü
	{"nve",		"nUE"},		// alternate to nüe
	{"ou",		"o"},
	{"pa",		"pA"},
	{"pai",		"p6"},
	{"pan",		"pAn"},
	{"pang",	"paN"},
	{"pao",		"p7"},
	{"pei",		"pe"},
	{"pen",		"p^n"},
	{"peng",	"p^N"},
	{"pi",		"pi"},
	{"pian",	"pJEn"},
	{"piao",	"pJ7"},
	{"pie",		"pJE"},
	{"pin",		"pin"},
	{"ping",	"piN"},
	{"po",		"pO"},
	{"pou",		"po"},
	{"pu",		"pu"},
	{"qi",		"qi"},
	{"qia",		"qJA"},
	{"qian",	"qJEn"},
	{"qiang",	"qJaN"},
	{"qiao",	"qJ7"},
	{"qie",		"qJE"},
	{"qin",		"qin"},
	{"qing",	"qiN"},
	{"qiong",	"qJ5N"},
	{"qiu",		"qJo"},
	{"qu",		"qU"},
	{"quan",	"qUAn"},
	{"que",		"qUE"},
	{"qun",		"qUn"},
	{"ran",		"rAn"},
	{"rang",	"raN"},
	{"rao",		"r7"},
	{"re",		"r3"},
	{"ren",		"r^n"},
	{"reng",	"r^N"},
	{"ri",		"r2"},
	{"rong",	"r5N"},
	{"rou",		"ro"},
	{"ru",		"ru"},
	{"ruan",	"rWAn"},
	{"rui",		"rWe"},
	{"run",		"rWXn"},
	{"ruo",		"rWO"},
	{"sa",		"sA"},
	{"sai",		"s6"},
	{"san",		"sAn"},
	{"sang",	"saN"},
	{"sao",		"s7"},
	{"se",		"s3"},
	{"sen",		"s^n"},
	{"seng",	"s^N"},
	{"sha",		"SA"},
	{"shai",	"S6"},
	{"shan",	"SAn"},
	{"shang",	"SaN"},
	{"shao",	"S7"},
	{"she",		"S3"},
	{"shei",	"Se"},
	{"shen",	"S^n"},
	{"sheng",	"S^N"},
	{"shi",		"S2"},
	{"shou",	"So"},
	{"shu",		"Su"},
	{"shua",	"SWA"},
	{"shuai",	"SW6"},
	{"shuan",	"SWAn"},
	{"shuang",	"SWaN"},
	{"shui",	"SWe"},
	{"shun",	"SWXn"},
	{"shuo",	"SWO"},
	{"si",		"sI"},
	{"song",	"s5N"},
	{"sou",		"so"},
	{"su",		"su"},
	{"suan",	"sWAn"},
	{"sui",		"sWe"},
	{"sun",		"sWXn"},
	{"suo",		"sWO"},
	{"ta",		"tA"},
	{"tai",		"t6"},
	{"tan",		"tAn"},
	{"tang",	"taN"},
	{"tao",		"t7"},
	{"te",		"t3"},
	{"teng",	"t^N"},
	{"ti",		"ti"},
	{"tian",	"tJEn"},
	{"tiao",	"tJ7"},
	{"tie",		"tJE"},
	{"ting",	"tiN"},
	{"tong",	"t5N"},
	{"tou",		"to"},
	{"tu",		"tu"},
	{"tuan",	"tWAn"},
	{"tui",		"tWe"},
	{"tun",		"tWXn"},
	{"tuo",		"tWO"},
	{"wa",		"wA"},
	{"wai",		"w6"},
	{"wan",		"wAn"},
	{"wang",	"waN"},
	{"wei",		"we"},
	{"wen",		"w^n"},
	{"weng",	"w^N"},
	{"wo",		"wO"},
	{"wu",		"u"},
	{"xi",		"xi"},
	{"xia",		"xJA"},
	{"xian",	"xJEn"},
	{"xiang",	"xJaN"},
	{"xiao",	"xJ7"},
	{"xie",		"xJE"},
	{"xin",		"xin"},
	{"xing",	"xiN"},
	{"xiong",	"xJ5N"},
	{"xiu",		"xJo"},
	{"xu",		"xU"},
	{"xuan",	"xUAn"},
	{"xue",		"xUE"},
	{"xun",		"xUn"},
	{"ya",		"yA"},
	{"yan",		"yEn"},
	{"yang",	"yaN"},
	{"yao",		"y7"},
	{"ye",		"yE"},
	{"yi",		"yi"},
	{"yin",		"yin"},
	{"ying",	"yiN"},
	{"yo",		"yO"},
	{"yong",	"y5N"},
	{"you",		"yo"},
	{"yu",		"U"},
	{"yuan",	"yUAn"},
	{"yue",		"UE"},
	{"yun",		"yUn"},
	{"za",		"zA"},
	{"zai",		"z6"},
	{"zan",		"zAn"},
	{"zang",	"zaN"},
	{"zao",		"z7"},
	{"ze",		"z3"},
	{"zei",		"ze"},
	{"zen",		"z^n"},
	{"zeng",	"z^N"},
	{"zha",		"ZA"},
	{"zhai",	"Z6"},
	{"zhan",	"ZAn"},
	{"zhang",	"ZaN"},
	{"zhao",	"Z7"},
	{"zhe",		"Z3"},
	{"zhei",	"Ze"},
	{"zhen",	"Z^n"},
	{"zheng",	"Z^N"},
	{"zhi",		"Z2"},
	{"zhong",	"Z5N"},
	{"zhou",	"Zo"},
	{"zhu",		"Zu"},
	{"zhua",	"ZWA"},
	{"zhuai",	"ZW6"},
	{"zhuan",	"ZWAn"},
	{"zhuang",	"ZWaN"},
	{"zhui",	"ZWe"},
	{"zhun",	"ZWXn"},
	{"zhuo",	"ZWO"},
	{"zi",		"zI"},
	{"zong",	"z5N"},
	{"zou",		"zo"},
	{"zu",		"zu"},
	{"zuan",	"zWAn"},
	{"zui",		"zWe"},
	{"zun",		"zWXn"},
	{"zuo",		"zWO"}
};

static const int nPinyin = sizeof(tPinyin2Ascii) / sizeof(PINYIN_ASCII);

/*FUNCTION_HEADER**********************
 * NAME:	;SortCmp
 * DESC: 	Compare function for sorting
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int SortCmp(const void *arg1, const void *arg2)
{
	PINYIN_ASCII 
		p1 = *(PINYIN_ASCII *)arg1, 
		p2 = *(PINYIN_ASCII *)arg2;

	return FNX_STRCMP(p1.sPinyin, p2.sPinyin);

}

/*FUNCTION_HEADER**********************
 * NAME:	;FindCmp
 * DESC: 	Compare function for finding a pinyin
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int FindCmp(const void *arg1, const void *arg2)
{
	char 
		*p1 = (char *)arg1;
	PINYIN_ASCII 
		p2 = *(PINYIN_ASCII *)arg2;

	return FNX_STRCMP(p1, p2.sPinyin);
}

/*FUNCTION_HEADER**********************
 * NAME:	;SortPinyin
 * DESC: 	Function to sort Pinyin list
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void SortPinyin(void)
{
	qsort((void *)tPinyin2Ascii, nPinyin, sizeof(PINYIN_ASCII), SortCmp);
}


/*FUNCTION_HEADER**********************
 * NAME:	;Pinyin2Ascii
 * DESC: 	Function to find a Pinyin in the list and 
			convert to it's Ascii representation
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
char *Pinyin2Ascii(char *sPinyin, char *sAsky)
{
	void *pVoid;
	PINYIN_ASCII
		*pPinyin;
#ifndef OS_SYMBIAN
	static char bSort=0;
#else
	char bSort;
	GlobalDTPtr gp = GetGlobalDTPtr();
	bSort = gp->langStruct.ch_bSort;
#endif

	if( bSort == 0 )
	{
		SortPinyin();
		bSort = 1;
#ifdef OS_SYMBIAN
		gp->langStruct.ch_bSort = bSort;
#endif
	}

	if( sPinyin == NULL || *sPinyin == 0x00 )		// Idiot check
		return NULL;

	sAsky[0] = 0x00;

	pVoid = FNX_BSEARCH(sPinyin, (void *)tPinyin2Ascii, nPinyin, sizeof(PINYIN_ASCII), FindCmp);
	if( pVoid != NULL )
	{
		pPinyin = (PINYIN_ASCII *)pVoid;
		FNX_STRCPY(sAsky, pPinyin->sAscii);
		return sAsky;
	}
	else if( *(sPinyin + FNX_STRLEN(sPinyin) - 1) == 'r' )
	{
		*(sPinyin + FNX_STRLEN(sPinyin) - 1) = 0x00;		// remove the 'r' and search again

		pVoid = FNX_BSEARCH(sPinyin, (void *)tPinyin2Ascii, nPinyin, sizeof(PINYIN_ASCII), FindCmp);
		if( pVoid != NULL )
		{
			pPinyin = (PINYIN_ASCII *)pVoid;
			FNX_STRCPY(sAsky, pPinyin->sAscii);
			FNX_STRCAT(sAsky, "9");
			return sAsky;
		}
		else
		{
			*(sPinyin + FNX_STRLEN(sPinyin) - 1) = 'r';	// put it back ???
			return NULL;
		}

	}
	else
	{
		return NULL;
	}
}

/*FUNCTION_HEADER**********************
 * NAME:	;ConvertPinyinStr2AsciiStr
 * DESC: 	Convert pinyin+tone to tone+phonemes
 * IN:		sPinyinStr - string containing pinyin+tone
 * OUT:		sPhonemeStr - string to return tone+phonemes
 * RETURN:	length of sPhonemeStr on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int ConvertPinyinStr2Phonemes(char *sPinyinStr, char *sPhonemeStr, int nMaxLen)
{
	char 
		c,
		*pc,
		*pcStart=NULL,
		sTone[2],
		sPunc[2],
		sPinyin[64],
		sAsky[12];
	int	
		nSyllables=0,
		nLenPhonemeStr=0;

	if( sPinyinStr == NULL )
		return 0;

	sPhonemeStr[0] = 0x00;
	sTone[0] = sTone[1] = 0x00;
	sPunc[0] = sPunc[1] = 0x00;

	for( pc = sPinyinStr; *pc || pcStart != NULL; pc++ )
	{
#ifdef CASIO_SH3
		if( ('A' <= *pc && *pc <= 'Z') || *pc == '0xdc' ) //0xdc = "Ü"
#else
		if( ('A' <= *pc && *pc <= 'Z') || *pc == 'Ü' )
#endif
		{
			*pc = (*pc - 'A') + 'a';		// Convert to lower case
			
			if( pcStart == NULL )			// Keep track of the beginning of the pinyin syllable
				pcStart = pc;
		}
#ifdef CASIO_SH3
		else if( ('a' <= *pc && *pc <= 'z') || *pc == '0xfc' ) //0xfc = "ü"
#else
		else if( ('a' <= *pc && *pc <= 'z') || *pc == 'ü' )
#endif
		{
			if( pcStart == NULL )
				pcStart = pc;					// Keep track of the beginning of the pinyin
		}
		else if( '0' <= *pc && *pc <= '9' )		// found the end of a pinyin without a tone
		{
			sTone[0] = *pc;					// save the tone value
			sTone[1] = 0x00;
			*pc = 0x00;						// null terminate the pinyin
			
			if( pcStart == NULL )			// Somebody accidentally put the tone first ... ?
				continue;

			FNX_STRCPY(sPinyin, pcStart);

			if( (Pinyin2Ascii(pcStart, sAsky)) != NULL )
			{
				if( nSyllables > 0 )
				{
					FNX_STRCAT(sPhonemeStr, "-");
					nLenPhonemeStr++;
				}
				
				nLenPhonemeStr += FNX_STRLEN(sAsky)+1;	// sum in length of phonemes + tone
				if( sPhonemeStr )
				{
					FNX_STRCAT(sPhonemeStr, sTone);
					FNX_STRCAT(sPhonemeStr, sAsky);
				}
				nSyllables++;
			}
			pcStart = NULL;					// re-initialize for the next pinyin

		}
		else if( pcStart )	// found the end of a pinyin without a tone
		{
			if( sTone[0] == 0x00 )
				sTone[0] = DEFAULT_TONE;	// use a default tone of 3 if none is given
			sTone[1] = 0x00;
			c = *pc;						// save ending character
			*pc = 0x00;						// null terminate the pinyin
			FNX_STRCPY(sPinyin, pcStart);

			if( (Pinyin2Ascii(pcStart, sAsky)) != NULL )
			{
				if( nSyllables > 0 )
				{
					FNX_STRCAT(sPhonemeStr, "-");
					nLenPhonemeStr++;
				}

				nLenPhonemeStr += FNX_STRLEN(sAsky)+1;	// sum in length of phonemes + tone
				if( sPhonemeStr )
				{
					FNX_STRCAT(sPhonemeStr, sTone);
					FNX_STRCAT(sPhonemeStr, sAsky);
				}
				
				nSyllables++;
			}

			if( c && FNX_STRCHR(MANDARIN_CONTROL_PHONES, c) )
			{
				sPunc[0] = c;
				FNX_STRCAT(sPhonemeStr, sPunc);
				nLenPhonemeStr++;
			}

			pcStart = NULL;					// re-initialize for the next pinyin
			sTone[0] = 0x00;

			if( c == 0x00 || *(pc+1) == 0x00 )
				break;

		}
		else if( FNX_STRCHR(MANDARIN_CONTROL_PHONES , *pc) )
		{
			sPunc[0] = *pc;
			FNX_STRCAT(sPhonemeStr, sPunc);
			nLenPhonemeStr++;
		}
	}

	return nLenPhonemeStr;

}
