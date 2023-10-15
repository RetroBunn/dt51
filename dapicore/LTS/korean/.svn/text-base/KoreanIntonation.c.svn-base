/*C_HEADER_FILE****************************************************************
FILE			:	KoreanIntonation.c
DESC			:	Add Intonation information to phrase.
TABS			:	4
OWNER			:	Fonix
DATE CREATED	:	13 Sept 2005	

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
//#include "FnxPlatform.h"
#include "ls_def.h"			// definition for ls_util_write_pipe()
#include "ph_def.h"			// definition of PDPH_T thread data
#include "DTFnxStdlib.h"
#include "FnxLtsRulesEngine.h"
#include "SelectSinglePron.h"
#include "KrHangulToRoman.h"
#include "onealign.h"
#include "KoreanIntonation.h"

// Compare with ...\dapicore\include\kr_phon.tab
static const char * CONSTCONST gpsKoreanFonixbet[]= {
	"",			// _
	"i",		// i
	"E",		// e
	"@",		// A
	"u",		// u
	"U",		// U
	"Ui",		// x
	"oU",		// o
	"ao",		// C
	"A",		// a
	"jE",		// 1
	"j@",		// 2
	"ju",		// 3
	"joU",		// 4
	"jao",		// 5
	"jA",		// 6
	"wi",		// 7
	"wE",		// 8
	"",			// 9
	"wao",		// 0
	"wA",		// w
	"m",		// m
	"n",		// n
	"N",		// N
	"pc ph",	// p lax/lenix
	"pc ph_h",	// P aspriated
	"p_q",		// B tense
	"bc bh",	// b lax/lenis
	"tc th",	// t lax/lenis
	"tc th_h",	// T aspirated
	"t_q",		// D tense
	"dc dh",	// d lax/lenis
	"kc kh",	// k lax/lenis
	"kc kh_h",	// K aspirated
	"k_q",		// G tense
	"gc gh",	// g lax/lenis
	"s",		// s
	"ss",		// Z
	"S",		// S
	"h",		// h
	"j",		// j
	"l",		// l
	"tf",		// r
	"dZ",		// J
	"tS",		// H
	"t_q tS",	// c
	"woU",		// W	/* 46  = */
	"",				/* 47  = */
	"",             /* 48  = */
	"",             /* 49  = */

	"",             /* 50  = */
	"",             /* 51  = */
	"",             /* 52  = */
	"",             /* 53  = */
	"",             /* 54  = */
	"",             /* 55  = */
	"",             /* 56  = */
	"",             /* 57  = */
	"",             /* 58  = */
	"",             /* 59  = */

	"",             /* 60  = */
	"",             /* 61  = */
	"",             /* 62  = */
	"",             /* 63  = */
	"",             /* 64  = */
	"",             /* 65  = */
	"",             /* 66  = */
	"",             /* 67  = */
	"",             /* 68  = */
	"",             /* 69  = */

	"",             /* 70  = */
	"",             /* 71  = */
	"",             /* 72  = */
	"",             /* 73  = */
	"",             /* 74  = */
	"",             /* 75  = */
	"",             /* 76  = */
	"",             /* 77  = */
	"",             /* 78  = */
	"",             /* 79  = */

	"",             /* 80  = */
	"",             /* 81  = */
	"",             /* 82  = */
	"",             /* 83  = */
	"",             /* 84  = */
	"",             /* 85  = */
	"",             /* 86  = */
	"",             /* 87  = */
	"",             /* 88  = */
	"",             /* 89  = */

	"",             /* 90  = */
	"",             /* 91  = */
	"",             /* 92  = */
	"",             /* 93  = */
	"",             /* 94  = */
	"",             /* 95  = */
	"",             /* 96  = */
	"",             /* 97  = */
	"",             /* 98  = */
	"",             /* 99  = */

	"~",		/* BLOCK_RULES =	~	*/
	"=",		/* S3 =  			=	*/
	"`",		/* S2 = 			` 	*/
	"'",		/* S1 =				' 	*/
	"\"",		/* SEMPH =			"   */
	"/",		/* HAT_RISE  = 		/	*/
	"\\",		/* HAT_FALL  = 		\	*/
	"/\\",		/* HAT_RF  = 		<	*/
	"-",		/* SBOUND  =		-	*/
	"",			/* MBOUND  = 		*	*/
	"#",		/* HYPHEN  = 		#	*/
	" ",		/* WBOUND  = 	 		*/
	"",			/* PPSTART =		(	*/
	"",			/* VPSTART = 		)	*/
	";",		/* RELSTART  = 		;	*/
	",",		/* COMMA  =			,	*/
	".",		/* PERIOD =			.	*/
	"?",		/* QUEST  =			?	*/
	"!",		/* EXCLAIM  = 		!	*/
	"",			/* NEW_PARAGRAPH =	+	*/
	"",			/* SPECIALWORD =	^	*/
	"",			/* LINKRWORD =		&	*/
	""			/* DOUBLCONS =		>	*/
};

static const unsigned char   * CONSTCONST gpsKr_arpa[] = {
	"_",
	"iy",           /* 1  =  i */	// pascii 1  // 
	"eh",           /* 2  =  e */	// pascii 7  // 
	"ae",           /* 3  =  A */	// pascii 9 //
	"uw",           /* 4  =  u */	// pascii 17 //
	"uh",           /* 5  =  U */	// pascii 19 //
	"ui",           /* 6  =  x */	// pascii 19 1 diphthong // 
	"ow",           /* 7  =  o */	// pascii 21 //
	"ao",           /* 8  =  C */	// pascii 23 // 
	"aa",           /* 9  =  a */	// pascii 24 //	
	"ye",           /* 10  = 1 */	// pascii 82 7 diphthong //
	"yh",           /* 11  = 2 */	// pascii 82 9 diphthong //
	"yu",           /* 12  = 3 */	// pascii 82 17 diphthong //
	"yo",           /* 13  = 4 */	// pascii 82 21 diphthong //
	"yc",           /* 14  = 5 */	// pascii 82 23 diphthong //
	"ya",           /* 15  = 6 */	// pascii 82 24 diphthong //
	"wi",           /* 16  = 7 */	// pascii 85 1 diphthong //
	"we",           /* 17  = 8 */ 	// pascii 85 7 diphthong //
	"wh",           /* 18  = 9 */	// pascii 85 9 diphthong //
	"wc",           /* 19  = 0 */	// pascii 85 23 diphthong //
	"wa",           /* 20  = w */	// pascii 85 24 diphthong //
	"m",           /* 21  = m */	// pascii 31 //
	"n",           /* 22  = n */	// pascii 33 //
	"nx",           /* 23  = N */	// pascii 36 //
	"p",           /* 24  = p */	// pascii 39 //
	"ph",           /* 25  = P */	// pascii 39 486 aspirated //
	"pp",           /* 26  = B */	// pascii 39 378 glottalized //
	"b",           /* 27  = b */	// pascii 40 //
	"t",           /* 28  = t */	// pascii 41 //
	"th",           /* 29  = T */	// pascii 41 486 aspirated //	
	"tt",           /* 30  = D */	// pascii 41 378 glottalized //
	"d",           /* 31  = d */	// pascii 42 //
	"k",           /* 32  = k */	// pascii 47 //
	"kh",           /* 33  = K */	// pascii 47 486 aspirated //
	"kk",           /* 34  = G */	// pascii 47 378 glottalized //
	"g",           /* 35  = g */	// pascii 48 //
	"s",           /* 36  = s */	// pascii 61 //
	"ss",           /* 37  = Z */	// pascii 61 378 glottalized//
	"sh",           /* 38  = S */	// pascii 65 //
	"hx",           /* 39  = h */	// pascii 76 //
	"y",           /* 40  = j */	// pascii 82 //
	"l",           /* 41  = l */	// pascii 90 //
	"df",           /* 42  = r */	// pascii 97 //
	"jh",           /* 43  = J */	// pascii 115 //
	"ch",           /* 44  = H */	// pascii 116 //
	"cc",           /* 45  = c */	// pascii 116 378 glottalized //
	"wo",           /* 46  = W */
	
	"",            /* 47  = */
	"",             /* 48  = */
	"",             /* 49  = */

	"",             /* 50  = */
	"",             /* 51  = */
	"",             /* 52  = */
	"",             /* 53  = */
	"",             /* 54  = */
	"",             /* 55  = */
	"",             /* 56  = */
	"",             /* 57  = */
	"",             /* 58  = */
	"",             /* 59  = */

	"",             /* 60  = */
	"",             /* 61  = */
	"",             /* 62  = */
	"",             /* 63  = */
	"",             /* 64  = */
	"",             /* 65  = */
	"",             /* 66  = */
	"",             /* 67  = */
	"",             /* 68  = */
	"",             /* 69  = */

	"",             /* 70  = */
	"",             /* 71  = */
	"",             /* 72  = */
	"",             /* 73  = */
	"",             /* 74  = */
	"",             /* 75  = */
	"",             /* 76  = */
	"",             /* 77  = */
	"",             /* 78  = */
	"",             /* 79  = */

	"",             /* 80  = */
	"",             /* 81  = */
	"",             /* 82  = */
	"",             /* 83  = */
	"",             /* 84  = */
	"",             /* 85  = */
	"",             /* 86  = */
	"",             /* 87  = */
	"",             /* 88  = */
	"",             /* 89  = */

	"",             /* 90  = */
	"",             /* 91  = */
	"",             /* 92  = */
	"",             /* 93  = */
	"",             /* 94  = */
	"",             /* 95  = */
	"",             /* 96  = */
	"",             /* 97  = */
	"",             /* 98  = */
	"",             /* 99  = */

	"~",	/* BLOCK_RULES =	~	*/
	"=",	/* S3 =  			=	*/
	"`",	/* S2 = 			` 	*/
	"\'",	/* S1 =				' 	*/
	"\"",	/* SEMPH =			"   */
	"/",	/* HAT_RISE  = 		/	*/
	"\\",	/* HAT_FALL  = 		\	*/
	"/\\",	/* HAT_RF  = 		<	*/
	"-",	/* SBOUND  =		-	*/
	"*",	/* MBOUND  = 		*	*/
	"#",	/* HYPHEN  = 		#	*/
	" ",	/* WBOUND  = 	 		*/
	"(",	/* PPSTART =		(	*/
	")",	/* VPSTART = 		)	*/
	";",	/* RELSTART  = 		;	*/
	",",	/* COMMA  =			,	*/
	".",	/* PERIOD =			.	*/
	"?",	/* QUEST  =			?	*/
	"!",	/* EXCLAIM  = 		!	*/
	"+",	/* NEW_PARAGRAPH =	+	*/
	"^",	/* SPECIALWORD =	^	*/
	"&",	/* LINKRWORD =		&	*/
	">"		/* DOUBLCONS =		>	*/
};			       

//#define KR_CAN_USE_ALLOCS

/*FUNCTION_HEADER**********************
 * NAME:	;KrPhraseStructMemory
 * DESC: 	Get or return a KOREAN_PHRASE structure.
 * IN:		pReturn - address of a structure being returned, 
						NULL if you want to get a structure.
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
#define KR_NUM_PHRASES 32
KOREAN_PHRASE *KrPhraseStructMemory(KOREAN_PHRASE *pReturn)
{
#ifdef KR_CAN_USE_ALLOCS
	if( pReturn )
	{
		FNX_FREE(pReturn);
		return NULL;
	}
	else
	{
		return (KOREAN_PHRASE *)FNX_CALLOC(1, sizeof(KOREAN_PHRASE));
	}
#else
	int
		i;
	static int
#if defined CASIO_SH3 && defined _BIGENDIAN_
		nUsed,
		nMaxUsed,
		iOut;
#else
		nUsed=0,
		nMaxUsed=0,
		iOut=0;
#endif
	static char
		pbStatus[KR_NUM_PHRASES];
	static KOREAN_PHRASE 
		KrPhraseStructs[KR_NUM_PHRASES],
#if defined CASIO_SH3 && defined _BIGENDIAN_
		*pNextOut;
#else
		*pNextOut=NULL;
#endif
	// A structure is being returned so let's find it and check it back in
	if( pReturn )
	{
		for(i=0; i<KR_NUM_PHRASES; i++)
		{
			if( pReturn == &KrPhraseStructs[i] )
			{
				nUsed--;
				memset(pReturn, 0, sizeof(KOREAN_PHRASE));
				pbStatus[i] = 0;	// Mark this structure as "available"
				return NULL;
			}
		}
	}

	if( pbStatus[iOut] == 0 )
	{
		pbStatus[iOut] = 1;			// Mark this structure as "unavailable"
		pNextOut = &KrPhraseStructs[iOut];
		iOut++;
		if( iOut >= KR_NUM_PHRASES )
			iOut = iOut%KR_NUM_PHRASES;
		nUsed++;
		if( nUsed > nMaxUsed)
			nMaxUsed = nUsed;
		memset(pNextOut, 0, sizeof(KOREAN_PHRASE));
		return pNextOut;
	}
	else
	{
		for(i=0; i<KR_NUM_PHRASES; i++)
		{
			if( pbStatus[(iOut+i)%KR_NUM_PHRASES] == 0 )
			{
				iOut = (iOut+i)%KR_NUM_PHRASES;
				pbStatus[iOut] = 1;						// Mark as "unavailable"
				pNextOut = &KrPhraseStructs[iOut];
				iOut++;
				if( iOut >= KR_NUM_PHRASES )
					iOut = iOut%KR_NUM_PHRASES;
				nUsed++;
				if( nUsed > nMaxUsed)
					nMaxUsed = nUsed;
				memset(pNextOut, 0, sizeof(KOREAN_PHRASE));
				return pNextOut;
			}
		}
	}

	return NULL;
#endif
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrWordStructMemory
 * DESC: 	Get or return a KOREAN_WORD structure.
 * IN:		pReturn - address of a structure being returned, 
						NULL if you want to get a structure.
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
#define KR_NUM_WORDS 256
KOREAN_WORD *KrWordStructMemory(KOREAN_WORD *pReturn)
{
#ifdef KR_CAN_USE_ALLOCS
	if( pReturn )
	{
		FNX_FREE(pReturn);
		return NULL;
	}
	else
	{
		return (KOREAN_WORD *)FNX_CALLOC(1, sizeof(KOREAN_WORD));
	}
#else
	int
		i;
	static int
#if defined CASIO_SH3 && defined _BIGENDIAN_
		nUsed,
		nMaxUsed,
		iOut;
#else
		nUsed=0,
		nMaxUsed=0,
		iOut=0;
#endif
	static char
		pbStatus[KR_NUM_WORDS];

	static KOREAN_WORD 
		KrWordStructs[KR_NUM_WORDS],
#if defined CASIO_SH3 && defined _BIGENDIAN_
		*pNextOut;
#else
		*pNextOut=NULL;
#endif

	// A structure is being returned so let's find it and check it back in
	if( pReturn )
	{
		for(i=0; i<KR_NUM_WORDS; i++)
		{
			if( pReturn == &KrWordStructs[i] )
			{
				nUsed--;
				memset(pReturn, 0, sizeof(KOREAN_WORD));
				pbStatus[i] = 0;	// Mark this structure as "available"
				return NULL;
			}
		}
	}

	if( pbStatus[iOut] == 0 )
	{
		pbStatus[iOut] = 1;			// Mark this structure as "unavailable"
		pNextOut = &KrWordStructs[iOut];
		iOut++;
		if( iOut >= KR_NUM_WORDS )
			iOut = iOut%KR_NUM_WORDS;
		nUsed++;
		if( nUsed > nMaxUsed)
			nMaxUsed = nUsed;
		memset(pNextOut, 0, sizeof(KOREAN_WORD));
		return pNextOut;
	}
	else
	{
		for(i=0; i<KR_NUM_WORDS; i++)
		{
			if( pbStatus[(iOut+i)%KR_NUM_WORDS] == 0 )
			{
				iOut = (iOut+i)%KR_NUM_WORDS;
				pbStatus[iOut] = 1;						// Mark as "unavailable"
				pNextOut = &KrWordStructs[iOut];
				iOut++;
				if( iOut >= KR_NUM_WORDS )
					iOut = iOut%KR_NUM_WORDS;
				nUsed++;
				if( nUsed > nMaxUsed)
					nMaxUsed = nUsed;
				memset(pNextOut, 0, sizeof(KOREAN_WORD));
				return pNextOut;
			}
		}
	}

	return NULL;
#endif
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrSylStructMemory
 * DESC: 	Get or return a KOREAN_SYLLABLE structure.
 * IN:		pReturn - address of a structure being returned, 
						NULL if you want to get a structure.
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
#define KR_NUM_SYL 512
KOREAN_SYLLABLE *KrSylStructMemory(KOREAN_SYLLABLE *pReturn)
{
#ifdef KR_CAN_USE_ALLOCS
	if( pReturn )
	{
		FNX_FREE(pReturn);
		return NULL;
	}
	else
	{
		return (KOREAN_SYLLABLE *)FNX_CALLOC(1, sizeof(KOREAN_SYLLABLE));
	}
#else
	int
		i;
	static int
#if defined CASIO_SH3 && defined _BIGENDIAN_
		nUsed,
		nMaxUsed,
		iOut;
#else
		nUsed=0,
		nMaxUsed=0,
		iOut=0;
#endif
	static char
		pbStatus[KR_NUM_SYL];
	static KOREAN_SYLLABLE 
		KrSylStructs[KR_NUM_SYL],
#if defined CASIO_SH3 && defined _BIGENDIAN_
		*pNextOut;
#else
		*pNextOut=NULL;
#endif

	// A structure is being returned so let's find it and check it back in
	if( pReturn )
	{
		for(i=0; i<KR_NUM_SYL; i++)
		{
			if( pReturn == &KrSylStructs[i] )
			{
				nUsed--;
				memset(pReturn, 0, sizeof(KOREAN_SYLLABLE));
				pbStatus[i] = 0;	// Mark this structure as "available"
				return NULL;
			}
		}
	}

	if( pbStatus[iOut] == 0 )
	{
		pbStatus[iOut] = 1;			// Mark this structure as "unavailable"
		pNextOut = &KrSylStructs[iOut];
		iOut++;
		if( iOut >= KR_NUM_SYL )
			iOut = iOut%KR_NUM_SYL;
		nUsed++;
		if( nUsed > nMaxUsed)
			nMaxUsed = nUsed;
		memset(pNextOut, 0, sizeof(KOREAN_SYLLABLE));
		return pNextOut;
	}
	else
	{
		// find the first available memory
		for(i=0; i<KR_NUM_SYL; i++)
		{
			if( pbStatus[(iOut+i)%KR_NUM_SYL] == 0 )
			{
				iOut = (iOut+i)%KR_NUM_SYL;
				pbStatus[iOut] = 1;						// Mark as "unavailable"
				pNextOut = &KrSylStructs[iOut];
				iOut++;
				if( iOut >= KR_NUM_SYL )
					iOut = iOut%KR_NUM_SYL;
				nUsed++;
				if( nUsed > nMaxUsed)
					nMaxUsed = nUsed;
				memset(pNextOut, 0, sizeof(KOREAN_SYLLABLE));
				return pNextOut;
			}
		}
	}

	return NULL;
#endif
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsVowel
 * DESC: 	Check to see if the input asky phoneme is a vowel
 * IN:		cPhone - one of the asky phoneme set
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int KrIsVowel(char cPhone)
{
	if( FNX_STRCHR("ieAuUxoCa12345678wW", cPhone) )
		return 1;
	else
		return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsSonorant
 * DESC: 	Check to see if the input asky phone is a sonorant consonant
 * IN:		cPhone - one of the asky phoneme set
 * OUT:		
 * RETURN:	1 if true, 0 if false
 * NOTES:	
 *END_HEADER***************************/
int KrIsSonorant(char cPhone)
{
	if( FNX_STRCHR("mnNbdglr", cPhone) )		// Asky phonemes for sonorant consonants
		return 1;
	else
		return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrChangeF0Target
 * DESC: 	modify the f0 target
 * IN:		phTTS
			dur - duration
			df0 - change in f0
			delay - delay
			cmd - command number/count for this syllable.  
				  There can be up to 3 F0 commands per syllabic
 * OUT:		
 * RETURN:	none
 * NOTES:	
			<, / and \ are the F0 commands.  Their shape has nothing to do
			with how they are used.
			< - binds to the first sonorant
			/ - binds to first vowel
			\ - binds to first vowel
 *END_HEADER***************************/
static void KrChangeF0Target(LPTTS_HANDLE_T phTTS,int dur, int df0, int delay, int cmd)
{
	char sCommand[] = " </\\";
    short buf[4];
    PKSD_T pKsd_t = phTTS->pKernelShareData;
	
	if( cmd == 0 )	cmd = 1;
	if( cmd > 3 )	cmd = 3;

	if( df0 == 0 )
		return;

	if( df0 > 50 || df0 < -50)
		df0++;

    buf[0] = phTTS->pKernelShareData->reverse_ascky[sCommand[cmd]];
	buf[0] += (3 << PSNEXTRA);		// Set the number of items to follow buf[0]
    buf[1] = dur;
    buf[2] = df0;
    buf[3] = delay;
    ls_util_write_pipe(phTTS->pKernelShareData, &buf[0], 4);
	phTTS->current_f0_level += df0;
	PH_DEBUG_2010_P3("**Kr::KrChangeF0Target: df0=%d, dur=%d, f0=%d\n", df0, dur, phTTS->current_f0_level);

}

/*FUNCTION_HEADER**********************
 * NAME:	;KrGetBaseF0
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int KrGetBaseF0(LPTTS_HANDLE_T phTTS)  
{     
    PDPH_T pDph_t = (PDPH_T)phTTS->pPHThreadData;

	return pDph_t->curspdef[SPD_AP];
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrSetCurrentF0
 * DESC: 	set the current global f0 level
 * IN:		f0 - fundamental frequency
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static void KrSetCurrentF0(LPTTS_HANDLE_T phTTS, int f0)
{
    phTTS->current_f0_level = f0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrGetCurrentF0
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int KrGetCurrentF0(LPTTS_HANDLE_T phTTS)
{
	//PDPH_T pDph_t = (PDPH_T)phTTS->pPHThreadData;
	//return pDph_t->f0prime;		// f0prime isn't set until much later in processing

	return(phTTS->current_f0_level);
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrResetCurrentF0
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static void KrResetCurrentF0(LPTTS_HANDLE_T phTTS)
{
	int 
		iBaseF0 = KrGetBaseF0(phTTS),
		iCurF0 = KrGetCurrentF0(phTTS);

//	KrChangeF0Target(phTTS, 50, iBaseF0-iCurF0, -25, 1);
//	KrSetCurrentF0(phTTS, iBaseF0);

}


/*FUNCTION_HEADER**********************
 * NAME:	;KrFreePhrases
 * DESC: 	Free all of the phrase/word/syllable data
 * IN:		ppPhrases - address of the pointer to the head of the list of phrases
 * OUT:		all memory used by ppPhrases in released
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void KrFreePhrases(KOREAN_PHRASE **ppPhrases)
{
	KOREAN_PHRASE	*pTmpPhrase, *pPhrase;
	KOREAN_WORD		*pTmpWord, *pWord;
	KOREAN_SYLLABLE *pTmpSyl, *pSyl;

	pPhrase = *ppPhrases;
	while( pPhrase )
	{
		pTmpPhrase = pPhrase;
		pPhrase = pPhrase->pNext;

		pWord = pTmpPhrase->pWords;					// Free all words for this phrase
		while( pWord )
		{
			pTmpWord = pWord;
			pWord = pWord->pNext;

			pSyl = pTmpWord->pSyl;					// Free all syllables for this word
			while( pSyl )
			{
				pTmpSyl = pSyl;
				pSyl = pSyl->pNext;
				
				KrSylStructMemory(pTmpSyl);
				pTmpSyl = NULL;
			}

			KrWordStructMemory(pTmpWord);
			pTmpWord = NULL;
		}

		KrPhraseStructMemory(pTmpPhrase);	
		pTmpPhrase = NULL;
	}

	*ppPhrases = NULL;

}	// KrFreePhrases


/*FUNCTION_HEADER**********************
 * NAME:	;KrConvertFonixbet2AskyPhonemes
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int KrConvertFonixbet2AskyPhonemes(LPTTS_HANDLE_T phTTS, char *sFonixbet, char *sAskyPhones, int nMaxPhones)
{
	int i;
	int dtindex=0;
	int pos=0;
	int best_match;
	int best_length;
	int length;
	int match;
	PKSD_T pKsd_t=phTTS->pKernelShareData;

#ifdef PH_DEBUG
	char sArpa[128];
	sArpa[0] = 0x00;
#endif

	while( !pKsd_t->halting && sFonixbet[pos] )
	{
		while( sFonixbet[pos]==' ') 
		{
			pos++;
		}
		best_match=0;
		best_length=0;
		for (i=0;i<PHO_SYM_TOT;i++)
		{
			length=FNX_STRLEN(gpsKoreanFonixbet[i]);
			match=FNX_STRNCMP(sFonixbet+pos, gpsKoreanFonixbet[i], length);
			if (match==0)
			{
				if (length>best_length)
				{
					best_match=i;
					best_length=length;
				}
			}
		}
		if (best_length<=0)
		{
			while( sFonixbet[pos] && sFonixbet[pos] != ' ') 
			{
				pos++;
			}
		}
		else
		{
			pos+=best_length;
			sAskyPhones[FNX_STRLEN(sAskyPhones)] = phTTS->pKernelShareData->ascky[best_match];

#ifdef PH_DEBUG
			if( sArpa[0] != 0x00 )
				FNX_STRCAT(sArpa, " ");
			FNX_STRCAT(sArpa, gpsKr_arpa[best_match]);
#endif
		}
	}

#ifdef PH_DEBUG
	if(DT_DBG(PH_DBG,0x001))
	{
		FNX_PRINTF("\n**KR Fonixbet:<%s>\n     Askybet:<%s>\n     Arpabet:<%s>", sFonixbet, sAskyPhones, sArpa);
	}
#endif

	return 1;
}	// KrConvertFonixbet2AskyPhonemes

/*FUNCTION_HEADER**********************
 * NAME:	;RemoveDoubleHyphens
 * DESC: 	Convert something like "s oU gc gh - - i l" into "s oU gc gh ~ i l"
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void RemoveDoubleHyphens(char *sPron)
{
	char *pc;

	while( (pc = FNX_STRSTR(sPron, "--")) )
	{
		FNX_STRCPY(pc+1, pc+2);
	}
}

int KrCountSyllables(char *sText)
{
	char	*pc;
	int		bSawMarkerLast=0;
	int		nSyls=0;

	for(pc=sText; *pc; pc++)
	{
		if( *pc == '-' && !bSawMarkerLast )
		{
			nSyls++;
			bSawMarkerLast = 1;
		}
		else if( *pc != ' ' )
		{
			bSawMarkerLast = 0;
		}
	}

	return nSyls+1;		// There's one more syllable than there are markers.
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrRomaji2Fonixbet
 * DESC: 	Convert a Romaji string to a Fonixbet pronunciation
 * IN:		phTTS - pointer to TTS global data
			sRomaji - Romaji input
			nMax - max size of sFonixbet
 * OUT:		sFonixbet - Fonixbet pronunciation
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int KrRomaji2Fonixbet(LPTTS_HANDLE_T phTTS, char *sRomaji, char *sFonixbet, int nMax)
{
	PLTS_T pLts_t=phTTS->pLTSThreadData;
	PKSD_T pKsd_t=phTTS->pKernelShareData;
	char
		*pc,
		sWord[MAX_PHONEMES],
		sWordAll[MAX_PHONEMES],
		sPron[MAX_PHONEMES],
		sPronAll[MAX_PHONEMES];
	int	nWordLen,
		nWordAll,
		nSumFonixbet=0;
		
	for( pc=sRomaji; *pc; pc++ )
	{
		if( pKsd_t->halting )
			break;

		memset(sWord,0,MAX_PHONEMES);
		memset(sWordAll,0,MAX_PHONEMES);
		memset(sPron,0,MAX_PHONEMES);
		memset(sPronAll,0,MAX_PHONEMES);
		
		nWordLen=0;
		nWordAll=0;

		// Skip leading spaces, line feeds etc, but not breath breaks
		while( *pc && *pc <= ' ' && *pc != BREATH_BREAK) 
		{
			pc++;
		}

		if( *pc == 0x00 )
			return nSumFonixbet;
		
		// Copy input characters until we reach a word end ' ' or sentence end '.'
		while( *pc && !pKsd_t->halting)
		{
			if( *pc != SYLLABLE_MARKER_CHAR )
			{
				// Don't copy syllable boundary markers.  We don't want to confuse the LTS system
				sWord[nWordLen++] = *pc;
			}

			sWordAll[nWordAll++] = *pc;
			pc++;

			if( FNX_STRCHR(" ,.?!)\n\r", *pc) )
				break;
		}
		
		if (pKsd_t->halting) return 0;

		if( nWordLen > 0 )
		{
			// LTS rules use double hyphens now
			//RemoveDoubleHyphens(sWordAll);

			// Apply letter to sound rules
			if( translate(&pLts_t->LtsRules, sWordAll, sPronAll) )		// Get pron. with syllable boundaries
			{
				SelectSinglePron(sPronAll, 0, 1);									// Eliminate optional and alternate pronunciations
#ifdef PH_DEBUG
#ifdef _WINDOWS
				if( KrCountSyllables(sWordAll) != KrCountSyllables(sPronAll) )
				{
					char sText[128];
					sprintf(sText, "%d Syllables in word /%s/ \ndo not match %d syllables in fonixbet /%s/", 
						KrCountSyllables(sWordAll), sWordAll, 
						KrCountSyllables(sPronAll), sPronAll);
					MessageBox(NULL, sText, "Warning", MB_OK);
				}
#endif

				if(DT_DBG(LTS_DBG,0x100))
				{
					FNX_PRINTF("\n<%s>", sWordAll);
				}				
				else if(DT_DBG(PH_DBG,0x001))
				{
					FNX_PRINTF("\n**KR Romaji:<%s>", sWordAll);
				}
#endif

				if( sFonixbet )
				{
					FNX_STRCAT(sFonixbet, sPronAll);
					if( *pc && FNX_STRCHR(" ,.?!", *pc) )
						sFonixbet[FNX_STRLEN(sFonixbet)] = *pc;

				}

				nSumFonixbet += FNX_STRLEN(sPronAll);
				if( *pc && FNX_STRCHR(" ,.?!", *pc) )
					nSumFonixbet++;

				if( *pc == 0x00 )
					break;
				pc++;
			}
		}

	}	// while reading all characters

	return nSumFonixbet;

}	// KrRomaji2Fonixbet


/*FUNCTION_HEADER**********************
 * NAME:	;KrParsePhrase
 * DESC: 	Parse one or more Korean phrases into words and syllables 
			to make it easier to further analyze.
 * IN:		sPhrase - string containing one or more phrases
 * OUT:		none
 * RETURN:	pointer to KOREAN_PHRASE structure on success, NULL on failure
 * NOTES:	
 *END_HEADER***************************/
KOREAN_PHRASE *KrParsePhrase(LPTTS_HANDLE_T phTTS, char *sPhrase)
{
	char *sTok,
		 *pc,
		 sLocal[MAX_PHONEMES],
		 *sPhraseSeps = ".,;:?!(){}[]\0",	// Should these be user configurable?
		 *sWordSeps   = " \n\r",
		 *sSylSeps	  = "-~\n\r\0",
		 sFonixbet[MAX_PHONEMES],
		 sAsky[MAX_PHONEMES],
		 bFocusNextWord=false;
	int	 iPos, nWords=0, i;
	KOREAN_PHRASE 
		*pHeadPhrase=NULL, 
		*pPhrase=NULL;
	KOREAN_WORD	  
		*pWord=NULL;
	KOREAN_SYLLABLE 
		*pSyl=NULL;

	if( sPhrase == NULL || 
		FNX_STRLEN(sPhrase) == 0 )
		return NULL;

	// Get a local copy of sPhrase because we are going to mangle it
	FNXA_STRCPY(sLocal, sPhrase);

	// ------------------------------------------
	// Parse all of the phrases
	// ------------------------------------------
	sTok = FNX_STRTOK(sLocal, sPhraseSeps);
	while( sTok )
	{
		if( pHeadPhrase == NULL )
		{
			pHeadPhrase = pPhrase = KrPhraseStructMemory(NULL);	
		}
		else
		{
			pPhrase->pNext = KrPhraseStructMemory(NULL);
			pPhrase->pNext->pPrev = pPhrase;
			pPhrase = pPhrase->pNext;
		}

		// Get a copy of the this phrase
		FNXA_STRCPY(pPhrase->sPhrase, sTok);

		// Get the character that marks the end of this phrase
		iPos = (sTok-sLocal) + FNX_STRLEN(sTok);
		pPhrase->cEnd = sPhrase[iPos];

		switch(pPhrase->cEnd)
		{
		case '?':
			pPhrase->iType |= KR_PHRS_QUESTION;
			break;

		case '!':
			pPhrase->iType |= KR_PHRS_EXCLAMATION;
			break;

		default:
			pPhrase->iType |= KR_PHRS_NEUTRAL;
			break;
		}

		sTok = FNX_STRTOK(NULL, sPhraseSeps);
	}
	
	// ---------------------------------------------
	// Parse the words from each phrase
	// ---------------------------------------------
	for(pPhrase=pHeadPhrase; pPhrase; pPhrase=pPhrase->pNext)
	{
		char *pcStart, *pc, cEnd;
		int	nLenPhrase;

		// Parse all of the words
		pWord = NULL;

		nLenPhrase = FNX_STRLEN(pPhrase->sPhrase);

		// Skip any leading separating characters
		for( pc=pPhrase->sPhrase; pc && *pc && FNX_STRCHR(sWordSeps, *pc); pc++ )
			;
		
		pcStart = pc;
		while( *pcStart )
		{
			while( pc && *pc && !FNX_STRCHR(sWordSeps, *pc) )		// Find the end of this word
				pc++;

			if( pc-pcStart <= 0 )
				break;

			if( *pcStart == '^' )									// Capture focus command for next word
			{
				bFocusNextWord = true;
				pcStart++;
			}

			if( pPhrase->pWords == NULL )
			{
				pPhrase->pWords = pWord = KrWordStructMemory(NULL);
				pWord->iPos = KR_POS_FIRST;
				pPhrase->nWords = 1;
			}
			else
			{
				pWord->pNext = KrWordStructMemory(NULL);
				pWord->pNext->pPrev = pWord;
				pWord = pWord->pNext;
				pWord->iPos = KR_POS_MID;
				pPhrase->nWords++;
			}

			// Get a copy of the this word
			cEnd = *pc;
			*pc = 0x00;
			FNXA_STRCPY(pWord->sWord, pcStart);
			if( bFocusNextWord )
			{
				pWord->bIsFocus = true;
				bFocusNextWord = false;
			}

			// Convert this word to a phonetic pronunciation
			memset(sFonixbet, 0, MAX_PHONEMES);
			memset(sAsky, 0, MAX_PHONEMES);
			if( KrRomaji2Fonixbet(phTTS, pWord->sWord, sFonixbet, MAX_PHONEMES) )
			{
				KrConvertFonixbet2AskyPhonemes(phTTS, sFonixbet, sAsky, MAX_PHONEMES);
				FNXA_STRCPY(pWord->sPron, sAsky);
			}

			if( cEnd == 0x00 )
				break;

			pcStart = pc+1;		// Start on the next word
			while(*pcStart == ' ')
				pcStart++;

			pc = pcStart;
			while( pc && *pc && FNX_STRCHR(sWordSeps, *pc) )		// Find the end of this word
				pc++;

		}

		if( pWord )
		{
			if( pWord->iPos == KR_POS_FIRST )
				pWord->iPos |= KR_POS_LAST;
			else
			{	
				char *pc;
				pWord->iPos = KR_POS_LAST;
				if( (pc = FNX_STRSTR(pWord->sWord, "-kka")) &&			// phrase ends in -kka
					pc == pWord->sWord+FNX_STRLEN(pWord->sWord)-4 )
				{
					pPhrase->iType |= KR_PHRS_QUESTION;					// should have question intonation
				}
			}
		}
	}

	if( pHeadPhrase == NULL )
		return NULL;

	if( pHeadPhrase->nWords == 0 )
	{
		KrFreePhrases(&pHeadPhrase);
		return NULL;
	}

	// ---------------------------------------------
	// Parse the syllables from each word
	// ---------------------------------------------
	for(pPhrase=pHeadPhrase; pPhrase; pPhrase=pPhrase->pNext)
	{
		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{

			if( pWord->sPron[0] == 0x00 )
				continue;

			// Get a local copy of sPron because we are going to mangle it
			FNXA_STRCPY(sLocal, pWord->sPron);
			pc = pWord->sWord;

			// Parse all of the syllables
			pSyl = NULL;
			sTok = FNX_STRTOK(sLocal, sSylSeps);
			while( sTok )
			{
				if( pWord->pSyl == NULL )
				{
					pWord->pSyl = pSyl = KrSylStructMemory(NULL);
					pSyl->iPos = KR_POS_FIRST;
					pWord->nSyls = 1;
				}
				else
				{
					pSyl->pNext = KrSylStructMemory(NULL);
					pSyl->pNext->pPrev = pSyl;
					pSyl = pSyl->pNext;
					pSyl->iPos = KR_POS_MID;
					pWord->nSyls++;
				}

				// Get a copy of this syllable's pronunciation
				FNXA_STRCPY(pSyl->sPron, sTok);

				// Get a copy of this syllable's romanization
				for(i=0; i<16 && *pc && FNXA_STRCHR(sSylSeps, *pc) == NULL; i++, pc++ )
				{
					pSyl->sRoman[i] = *pc;
				}
				while( *pc && FNXA_STRCHR(sSylSeps, *pc) )
					pc++;

				// Check to see if this syllable was preceded by a long vowel marker
				if( pWord->sPron[sTok-sLocal-1] == LONG_SYLLABLE_MARKER_CHAR )
					pSyl->bLong = 1;

				sTok = FNX_STRTOK(NULL, sSylSeps);
			}
			if( pSyl )
			{
				if( pSyl->iPos == KR_POS_FIRST )
					pSyl->iPos |= KR_POS_LAST;
				else
					pSyl->iPos = KR_POS_LAST;
			}
		}
	}

	return pHeadPhrase;

}	// KrParsePhrase

/*FUNCTION_HEADER**********************
 * NAME:	;KrGetToneString
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void KrGetToneString(int iTone, char *sTone)
{
	if( iTone & KR_INTON_L )
		FNX_STRCPY(sTone, "L");
	else if( iTone & KR_INTON_H )
		FNX_STRCPY(sTone, "H");
	else if( iTone & KR_INTON_X )
		FNX_STRCPY(sTone, "X");
	else if( iTone & KR_INTON_LH )
		FNX_STRCPY(sTone, "LH");
	else if( iTone & KR_INTON_HL )
		FNX_STRCPY(sTone, "HL");
	else if( iTone & KR_INTON_LHL )
		FNX_STRCPY(sTone, "LHL");
	else if( iTone & KR_INTON_HLH )
		FNX_STRCPY(sTone, "HLH");
	else if( iTone & KR_INTON_LHLH )
		FNX_STRCPY(sTone, "LHLH");
	else if( iTone & KR_INTON_HLHL )
		FNX_STRCPY(sTone, "HLHL");
	else if( iTone & KR_INTON_LHLHL )
		FNX_STRCPY(sTone, "LHLHL");
	else
		FNX_STRCPY(sTone, "?");
}

#ifndef CASIO_SH3 
/*FUNCTION_HEADER**********************
 * NAME:	;KrPrint
 * DESC: 	Print syllable information
 * IN:		pPhrases
 * OUT:		
 * RETURN:	
 * NOTES:
 *END_HEADER***************************/
void KrPrint(LPTTS_HANDLE_T phTTS, KOREAN_PHRASE *pPhrases)
{
	char sTone[24];
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord;
	KOREAN_SYLLABLE 
		*pSyl;

	FNX_PRINTF("\n**KR KrPrint: \n");

	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{
			for(pSyl=pWord->pSyl; pSyl; pSyl=pSyl->pNext)
			{
				KrGetToneString(pSyl->iTone, sTone);
				FNX_PRINTF("(%s-%d)%s%c\n",
					sTone, 
					pSyl->f0,
					pSyl->sPron,
					pSyl->pNext ? '-' : ' ');
			}
			FNX_PRINTF(" - eow -\n");
		}
		FNX_PRINTF(" - End of Phrase -\n");
	}
}
#endif


/*FUNCTION_HEADER**********************
 * NAME:	;KrSendPhone
 * DESC: 	Send phoneme to sythesizer
 * IN:		phone - phoneme to send
			duration - duration value
 * OUT:		
 * RETURN:	
 * NOTES:
 *END_HEADER***************************/
void KrSendPhone(LPTTS_HANDLE_T phTTS, char phone, int duration, int dF0, int delay)
{
    short buf[6];
	
    PKSD_T pKsd_t = phTTS->pKernelShareData;
	
	PH_DEBUG_2010_P3("**KR KrSendPhone: /%c/, duration = %d%s\n", 
			phone, abs(duration),
			duration < 0 ? "%%" : "ms");

	buf[0] = phTTS->pKernelShareData->reverse_ascky[phone];

	if( duration == 0 )
	{
		ls_util_send_phone(phTTS, buf[0]);
	}
	else
	{
		buf[0] = phTTS->pKernelShareData->reverse_ascky[phone];
		buf[0] += (3 << PSNEXTRA);		// Stuff the number of extra items to follow into buf[0]
		buf[1] = duration;
		buf[2] = dF0;
		buf[3] = delay;
 
		ls_util_write_pipe(phTTS->pKernelShareData, &buf[0], 4);
		phTTS->current_f0_level += dF0;
	}
}	// KrSendPhone

/*FUNCTION_HEADER**********************
 * NAME:	;KrAssignSylPitch
 * DESC: 	Assign a pitch value to each syllable based on it's
			context and tone value (H, L, X, HL ... )
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
#define KR_FULL_STEP_MALE	28
#define KR_FULL_STEP_FEMALE	36
void KrAssignSylPitch(LPTTS_HANDLE_T phTTS, KOREAN_PHRASE *pPhrases)
{
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord;
	KOREAN_SYLLABLE 
		*pSyl;
	int	
		iAvgPitch,			// Average pitch for this speaker
		iPitchRange,		// Half of the full dynamic range (average -> iMaxPitch) or (average -> iMinPitch)
		iMaxStressPitch,	// Maximum pitch for a stressed syllable
		iMaxPitch,			// Maximum pitch for an H syllable
		iMinPitch,			// Minimum pitch for an L syllable
		iPitchStep,			// Amount iPitchRange changes from one syllable to the next.
		iInterpToneStep,	// Interpolated tone step - depends on distance from L-to-H (ex. LXH, LXXH, LXXXH)
		nWords,				// number of words in a phrase
		nSyl,				// number of syllables in a phrase
		nWordsInBreathGroup,
		iFullStep,
		iHalfStep;
    PKSD_T 
		pKsd_t = phTTS->pKernelShareData;
	PDPH_T 
		pDph_t = phTTS->pPHThreadData;

	if( pDph_t->malfem == FEMALE )		// switch to female
	{
		iFullStep = KR_FULL_STEP_FEMALE;
	}
	else
	{
		iFullStep = KR_FULL_STEP_MALE;
	}

	// Apply the pitch range modification
	if( 25 < pDph_t->curspdef[SPD_PR] && pDph_t->curspdef[SPD_PR] < 200 &&
		pDph_t->curspdef[SPD_PR] != 100 )
	{
		iFullStep = iFullStep * pDph_t->curspdef[SPD_PR] / 10;		// deca-hertz
	}

	iHalfStep = iFullStep >> 1;

	phTTS->current_f0_level = iAvgPitch = KrGetBaseF0(phTTS) * 10;

	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		iPitchRange = iFullStep * 10;

		// count the number of words and syllables in this phrase
		for(pWord=pPhrase->pWords, nWords=0, nSyl=0; pWord; pWord=pWord->pNext)		// Count the number of words in this phrase
		{
			nWords++;
			for(pSyl=pWord->pSyl; pSyl; pSyl=pSyl->pNext)
				nSyl++;
		}

		if( nSyl == 0 )
			continue;

		// All pitch values are in deca-hertz
		iPitchStep = iPitchRange * 2 / 10 / nSyl;		// Drop 20% over the length of the sentence
		iMaxStressPitch = iAvgPitch + (iPitchRange * 13 / 10) + iPitchStep;
		iMaxPitch = iAvgPitch + iPitchRange + iPitchStep;
		iMinPitch = iAvgPitch - (iPitchRange>>1);	// + iPitchStep;

		iInterpToneStep = 0;
		for(pWord=pPhrase->pWords, nWordsInBreathGroup=0; pWord; pWord=pWord->pNext, nWordsInBreathGroup++)
		{
			if( pWord != pPhrase->pWords )
				iPitchRange -= iPitchStep;					// reduce the tone step a little for each syllable in the phrase

			for(pSyl=pWord->pSyl; pSyl; pSyl=pSyl->pNext)
			{

				iMaxStressPitch -= iPitchStep;
				iMaxPitch -= iPitchStep;
				//iMinPitch += iPitchStep;

				// Calculate the interpolated pitch step depending on the number of Xs
				if( (pSyl->iTone & KR_INTON_X) &&
					iInterpToneStep == 0 )
				{
					int nX=0;
					KOREAN_SYLLABLE *pSyl2;
					for( pSyl2=pSyl; pSyl2; pSyl2=pSyl2->pNext)
					{
						nX++;
						if( !(pSyl2->iTone & KR_INTON_X) )
							break;
					}
					if( (pSyl->pPrev->iTone & KR_INTON_H) &&			// H->L
						((pSyl2->iTone & KR_INTON_L) ||
						 (pSyl2->iTone & KR_INTON_LH) ||
						 (pSyl2->iTone & KR_INTON_LHL) ||
						 (pSyl2->iTone & KR_INTON_LHLH) ||
						 (pSyl2->iTone & KR_INTON_LHLHL)) )
					{
						iInterpToneStep = (iMinPitch-pSyl->pPrev->f0) / nX;
					}
					else if( (pSyl->pPrev->iTone & KR_INTON_L) &&		// L->H
							 ((pSyl2->iTone & KR_INTON_H) ||
							  (pSyl2->iTone & KR_INTON_HL) ||
							  (pSyl2->iTone & KR_INTON_HLH) ||
							  (pSyl2->iTone & KR_INTON_HLHL)) )
					{
						iInterpToneStep = (iMaxPitch-pSyl->pPrev->f0) / nX;
					}
					else
					{
						iInterpToneStep = 0;
					}
				}	// -X-

				// Set the pitch for each syllable
				if( pSyl->iTone & KR_INTON_H )
				{
					pSyl->f0 = iMaxPitch;
					if( pSyl->pNext == NULL &&
						pWord->nSyls >= 4 )
					{
						pSyl->f0 = pSyl->f0 * 11 / 10;			// increase F0 of second H of AP 
					}
					iInterpToneStep = 0;
				}
				else if( pSyl->iTone & KR_INTON_HL )
				{
					pSyl->f0 = iMaxPitch;
					pSyl->f0_2 = iAvgPitch;	// + ((iMaxPitch-iAvgPitch)>>2);
					iInterpToneStep = 0;
				}
				else if( pSyl->iTone & KR_INTON_L )
				{
					if( pWord->pPrev == NULL &&
						pSyl->pPrev == NULL &&
						pSyl->pNext &&
						(pSyl->pNext->iTone & KR_INTON_H) )
					{
						// Make the first syllable's f0 higher - halfway between the 
						// peak on the next syllable and the minimum of the sentence.  Sun-Ah
						pSyl->f0 = iAvgPitch;
					}
					else
					if( pSyl->pPrev &&
						(pSyl->pPrev->iTone & KR_INTON_H) &&
						pSyl->pNext &&
						(pSyl->pNext->iTone & KR_INTON_H) )
					{
						// An L between 2 H's is not fully reallized, so the target should
						// be a little higher than iMinPitch. Sun-Ah
						pSyl->f0 = iAvgPitch;
					}
					else
					{
						pSyl->f0 = iMinPitch;
					}
					iInterpToneStep = 0;
				}
				else if( pSyl->iTone & KR_INTON_LH )
				{
					if( pSyl->pPrev &&
						(pSyl->pPrev->iTone & KR_INTON_L) )
						pSyl->f0 = pSyl->pPrev->f0;
					else
						pSyl->f0 = iAvgPitch;

					pSyl->f0_2 = iAvgPitch + (((iMaxPitch-iAvgPitch)*3)>>2);		// = Avg + (Max-Avg)*3/4
					iInterpToneStep = 0;
				}
				else if( pSyl->iTone & KR_INTON_X )
				{
					pSyl->f0 = pSyl->pPrev->f0 + iInterpToneStep;
				}

				// Take care of final syllable affects
				if( pSyl->pNext == NULL &&						// last syllable
					pWord->pNext == NULL )						// of last word
				{
					if( (pPhrase->iType & KR_PHRS_QUESTION) &&
						!(pPhrase->iType & KR_PHRS_WH_WORD) )
					{
						pSyl->f0 = iMaxStressPitch;	//pSyl->f0 * 3 / 2;			// increase pitch rise 50%
					}
					else if( pPhrase->iType & KR_PHRS_EXCLAMATION )
					{
						pSyl->f0 = pSyl->f0 * 5 / 4;			// increase pitch rise by 25%
					}
				}

			}	// for each syllable in word

		}	// for each word in phrase

	}	// For each phrase

}	// KrAssignSylPitch

/*FUNCTION_HEADER**********************
 * NAME:	;KrPlaySounds
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void KrPlaySounds(LPTTS_HANDLE_T phTTS, KOREAN_PHRASE *pPhrases)
{
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord;
	KOREAN_SYLLABLE 
		*pSyl;
	char 
		*pc,
		cLastPhon=0x00,
		sTone[32];
	short
		bFoundVowel;
	int	
		iStop,
		duration=0,			// percent change of inherent duration
		dF0=0,				// change in pitch
		delay=0,			// delay in ms
		iLastSylPitch,
		nSyl,
		nWords,
		nWordsInBreathGroup;
    PKSD_T 
		pKsd_t = phTTS->pKernelShareData;
	PDPH_T 
		pDph_t = phTTS->pPHThreadData;

	KrAssignSylPitch(phTTS, pPhrases);

#ifdef PH_DEBUG
	if( DT_DBG(PH_DBG, 0x002) )
	{	
		KrPrint(phTTS, pPhrases);
	}
#endif


	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		iLastSylPitch = KrGetBaseF0(phTTS) * 10;

		for(pWord=pPhrase->pWords, nWords=0; pWord; pWord=pWord->pNext)		// Count the number of words in this phrase
		{
			nWords++;
		}

		for(pWord=pPhrase->pWords, nWordsInBreathGroup=0; pWord; pWord=pWord->pNext, nWordsInBreathGroup++)
		{
			for(pSyl=pWord->pSyl, nSyl=1; pSyl; pSyl=pSyl->pNext, nSyl++)
			{

#ifdef PH_DEBUG
				if( DT_DBG(PH_DBG, 0x010) )
				{	KrGetToneString(pSyl->iTone, sTone);
					FNX_PRINTF("\n**KR KrPlaySounds: (%s) - Tone\n", sTone);
				}
#endif

				if( pSyl->iTone & KR_INTON_HL )						// Mihwa doesn't like this question intonation pattern.
				{													// but Sun-Ah does.
					dF0 = (pSyl->f0 - iLastSylPitch) / 10;
					if( KrIsSonorant(pSyl->sPron[0]) )
					{
						if( pSyl->sPron[2] != 0x00 &&
							KrIsSonorant(pSyl->sPron[2]) )
						{
							KrChangeF0Target(phTTS, 150, dF0, 0, 1);
							delay = 50;
						}
						else
						{
							KrChangeF0Target(phTTS, 120, dF0, 0, 1);
							delay = 20;
						}
					}
					else
					{
						KrChangeF0Target(phTTS, 50, dF0, 0, 2);
						delay = 50;
					}

					dF0 = (pSyl->f0_2 - pSyl->f0) / 10;
					KrChangeF0Target(phTTS, 100, dF0, delay, 3);
					iLastSylPitch = pSyl->f0_2;
				}
				else if( pSyl->iTone & KR_INTON_LH )
				{
					dF0 = (pSyl->f0 - iLastSylPitch) / 10;
					if( KrIsSonorant(pSyl->sPron[0]) )
					{
						if( pSyl->sPron[2] != 0x00 &&
							KrIsSonorant(pSyl->sPron[2]) )
						{
							KrChangeF0Target(phTTS, 170, dF0, 0, 1);
							delay = 70;
						}
						else
						{
							KrChangeF0Target(phTTS, 150, dF0, 0, 1);
							delay = 50;
						}
					}
					else
					{
						KrChangeF0Target(phTTS, 70, dF0, 0, 2);
						delay = 70;
					}

					dF0 = (pSyl->f0_2 - pSyl->f0) / 10;
					KrChangeF0Target(phTTS, 100, dF0, delay, 3);
					iLastSylPitch = pSyl->f0_2;
				}
				else	// Not HL or LH
				{
					// Start moving toward the pitch target immediately if the 
					//  syllable initial is a sonorant consonant
					// Reach the pitch target at the end of all sonorants in this syllable

					int iCmd,		// 1 of 3 pitch commands (1 - binds to first sonorant, 2 & 3 bind to the first vowel)
						iDur, 
						iPhon=0;

					if( KrIsSonorant(pSyl->sPron[0]) )				// First phoneme is a sonorant
						iCmd = 1;
					else
						iCmd = 2;

					// find the first sonorant/vowel in this syllable
					while( pSyl->sPron[iPhon] != 0x00 &&
						   !KrIsSonorant(pSyl->sPron[iPhon]) &&
						   !KrIsVowel(pSyl->sPron[iPhon]) )
					{
						iPhon++;
					}

					// find the duration % to the end of the last vowel
					iDur=0;
					bFoundVowel = 0;
					while( pSyl->sPron[iPhon] != 0x00 &&
						   (KrIsVowel(pSyl->sPron[iPhon]) ||
						   KrIsSonorant(pSyl->sPron[iPhon])) )
					{
						if( KrIsVowel(pSyl->sPron[iPhon]) )
							bFoundVowel = 1;

						// Don't include -coda sonorants
						if( bFoundVowel &&
							KrIsSonorant(pSyl->sPron[iPhon]) )
							break;

						iDur += 100;
						iPhon++;
					}

					if( pWord->pPrev == NULL &&			// Phrase initial word
						pSyl->pPrev == NULL &&			// Word initial syllable
						(pSyl->iTone & KR_INTON_L) )
					{
						// f0 of the sentence initial syllable should be either low
						// and flat over the syllable or slightly rise toward the 
						// f0 peak of the second syllable.  Sun-Ah
						iDur = 20;
					}
					else if( nSyl == 2 &&
							 (pSyl->iTone & KR_INTON_H) &&
							 !KrIsSonorant(pSyl->sPron[0]) &&
							 iDur > 80 )
					{
						// The f0 peak on the AP-second syllable should be high from the
						// beginning especially when it begins with a voiceless consonant.  Sun-Ah
						iDur -= 80;
					}
					else if( iDur >= 100 )
					{
						// Reach target a little before the end of the syllable
						iDur -= 20;
					}

					dF0 = (pSyl->f0 - iLastSylPitch) / 10;				// change from deca-hertz to hertz
					KrChangeF0Target(phTTS, iDur, dF0, 0, iCmd);		// reach pitch target by the end of the sonorant/vowels
					iLastSylPitch = pSyl->f0;
				}

				// Now send each of the phonemes in this syllable
				for( pc=pSyl->sPron; pc && *pc; pc++ )
				{
					// Korean speakers don't really do this.  There is a slight shift in
					// formants but no stop.  iy+iy -> iy+ih
					// If you have two consecutive vowels that are the same (ex. iy iy)
					// then you need to put a short pause between them.
					//if( KrIsVowel(cLastPhon) &&
					//	KrIsVowel(*pc) &&
					//	cLastPhon == *pc )
					//{
					//	KrSendPhone(phTTS, '_', 15, 0, 0);		// Send a short pause
					//	KrSendPhone(phTTS, *pc, 0, 0, 0);		// Send second vowel
					//}
					//else 
					if( *pc == 'h' &&						// Shorten /h/ in syllable initial
						 pc == pSyl->sPron &&				//  AP medial positions by half
						 pSyl != pWord->pSyl )
					{
						KrSendPhone(phTTS, *pc, -50, 0, 0);		
					}
					else
					{
						KrSendPhone(phTTS, *pc, 0, 0, 0);
					}

					cLastPhon = *pc;		// Keep track of the last phoneme

				}	// For each phoneme in syllable

			}	// for each syllable in word
			ls_util_send_phone(phTTS, WBOUND);

			// We need to take a breath every now and then if the phrase starts to get too long.
			if( nWordsInBreathGroup >= 5 && 
				nWords > 7 )
			{
				KrSendPhone(phTTS, '_', 250, 0, 0);		// Send a short pause
				nWordsInBreathGroup = 0;
			}

		}	// for each word in phrase

		iStop = 0;
		switch(pPhrase->cEnd)
		{
			case '?':	iStop = QUEST;		break;
			case '.':	iStop = PERIOD;		break;
			case ',':	iStop = COMMA;		break;
			case '!':	iStop = EXCLAIM;	break;
			case ';':	iStop = COMMA;		break;
			case ':':	iStop = PERIOD;		break;
			case '(':	iStop = COMMA;		break;
			case ')':	iStop = COMMA;		break;
			default:						break;
		}
		if( iStop > 0 )
		{
			ls_util_send_phone(phTTS, iStop);			// send stop value
		}

	}	// For each phrase
}	// KrPlaySounds


/*FUNCTION_HEADER**********************
 * NAME:	;KrCombineWords
 * DESC: 	Sometimes words need to be combined for intonation phrasing
 * IN:		pWord1 - pointer to 1st word
			pWord2 - pointer to 2nd word to be added to end of 1st word
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void KrCombineWords(KOREAN_WORD *pWord1, KOREAN_WORD *pWord2)
{
	KOREAN_SYLLABLE 
		*pSyl;

	// Add this syllable to the end of the last word
	for(pSyl=pWord1->pSyl; pSyl; pSyl=pSyl->pNext)
	{
		if( pSyl->pNext == NULL &&					// found end of 1st word
			pWord2->pSyl )
		{
			pSyl->pNext = pWord2->pSyl;				// Concatenate syllables to the end of the previous word
			pWord2->pSyl->pPrev = pSyl;				// Fix up the backwards link
			pWord1->pNext = pWord2->pNext;			// Fix up the links to skip this word
			pWord1->nSyls += pWord2->nSyls;			// increment number of syllables
			FNXA_STRCAT(pWord1->sPron, " ");		// Concatenate pronunciation and word strings
			FNXA_STRCAT(pWord1->sPron, pWord2->sPron);
			FNXA_STRCAT(pWord1->sWord, " ");
			FNXA_STRCAT(pWord1->sWord, pWord2->sWord);

			KrWordStructMemory(pWord2);				// Get rid of current word since it has been added into the previous
			break;
		}
	}
}


/*FUNCTION_HEADER**********************
 * NAME:	;KrIsWhWord
 * DESC: 	Test a word to see if it is a wh-word
 * IN:		sWord - the word to be tested
 * OUT:		none
 * RETURN:	1 if it is a wh-word, 0 if it is not
 * NOTES:	
 *END_HEADER***************************/
int KrIsWhWord(char *sWord)
{
	char *sWhWords[] = {
		"nu-ga",		// (who) is coming?
		"nu-gu",		// (Whom) do you want to be like?
		"mwo",			// (what) do you want? (informal)
		"mwol",			// (what)
		"myeoch",		// (How) many years have you lived in Korea?
		"mu-seun",		// (what) color is it?
		"mu--eos",		// (what) is your name?
		"eo-tteon",		// (what) kind of drinks do you have?
		"myeoch",		// (what) time do we arrive?
		"eo-di",		// where
		"eo-di--e",		// where
		"eon-je",		// (when) are you going?
		"eo-tteoh-ge",	// how
		"eol-ma",		// (how) much is it?
		"eo-neu",		// (which) way should we go?
		//"-wae",		// why forms it's own AP unless followed by a verb
		""
	};	
	int i;

	for(i=0; sWhWords[i][0] != 0x00; i++ )
	{
		if( FNXA_STRSTR(sWord, sWhWords[i]) == sWord )
			return 1;
	}

	return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrSetFocusOnWhWords
 * DESC: 	Look for wh-words and set the focus flag if found
 * IN:		pPhrases - pointer to all phrases
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void KrSetFocusOnWhWords(KOREAN_PHRASE *pPhrases)
{
	char
		bAlreadyFocused=0;
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord;

	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		// Don't look for a new focus word if there is already a focus word
		bAlreadyFocused=0;
		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{
			if( pWord->bIsFocus )
				bAlreadyFocused = 1;
		}
		if( bAlreadyFocused )
			continue;

		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{
			if( KrIsWhWord(pWord->sWord) )
			{
				pWord->bIsFocus = 1;
				pWord->pSyl->bFocus = 1;
				pPhrase->iType |= KR_PHRS_WH_WORD;
				break;
			}
		}
	}
}

/*FUNCTION_HEADER**********************
 * NAME:	;EndsWith
 * DESC: 	Check to see if a word ends with a particular ending
 * IN:		sWord - the word to check
			sEnding - the ending
 * OUT:		none
 * RETURN:	1 if it does end with sEnding, 0 if it doesn't 
 * NOTES:	
 *END_HEADER***************************/

int EndsWith(char *sWord, char *sEnding)
{
	char *pcWord, *pcEnding;

	pcWord = sWord + strlen(sWord) -1;
	pcEnding = sEnding + strlen(sEnding) -1;

	if( sWord == NULL ||
		sEnding == NULL || 
		strlen(sWord) <= strlen(sEnding) )
		return 0;

	while( *pcWord == *pcEnding )
	{
		if( pcEnding <= sEnding )
			return 1;

		pcWord--;
		pcEnding--;
	}

	return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsHelperVerb
 * DESC: 	Check to see if the current word is a helper verb and
			the previous word is has a base verb ending
 * IN:		pWord - pointer to the current word
 * OUT:		none
 * RETURN:	1 if true, 0 if false
 * NOTES:	
			see the following link
			http://www.lsa.umich.edu/asian/korean/intermediate/lesson14/mp3/index_gram.htm

 *END_HEADER***************************/
typedef char *HELPERVERB[2]; /* Array of 2 character pointers */
int KrIsHelperVerb(KOREAN_WORD *pWord)
{
	int	i;
	HELPERVERB 
		Helpers[] = 
		{
			/*  verb base ending, helper verb  */
			{"eo", "beo-ri-da"},
			{"eo", "nae-da"},
			{"eo", "na-da"},
			{"eo", "ju-da"},
			{"eo", "deu-ri-da"},
			{"eo", "bo-da"},
			{"eo", "dae-da"},
			{"eo", "du-da"},
			{"eo", "neoh-da"},
			{"eo", "noh-da"},
			{"eo", "ga-ji-da"},
			{"eo", "ji-da"},
			{"eo", "ga-da"},
			{"eo", "o-da"},
			{"eo", "ga-da"},
			{"eo", "iss-da"},
			{"a", "beo-ri-da"},
			{"a", "nae-da"},
			{"a", "na-da"},
			{"a", "ju-da"},
			{"a", "deu-ri-da"},
			{"a", "bo-da"},
			{"a", "dae-da"},
			{"a", "du-da"},
			{"a", "neoh-da"},
			{"a", "noh-da"},
			{"a", "ga-ji-da"},
			{"a", "ji-da"},
			{"a", "ga-da"},
			{"a", "o-da"},
			{"a", "ga-da"},
			{"a", "iss-da"},
			{"go", "iss-da"},
			{"go", "sip-da"},
			{"ge", "ha-da"},
			{"ge", "man-deul-da"},
			{"eun-ga", "bo-da"},
			{"eun-ga", "sip-da"},
			{"neun-ga", "bo-da"},
			{"neun-ga", "sip-da"},
			{"ol-kka", "sip-da"},
			{"na", "bo-da"},
			{"", ""}
		};

	for(i=0; Helpers[i][0][0] != 0x00; i++)
	{
		if( strcmp(Helpers[i][1], pWord->sWord) == 0 &&						// Is helper verb?
			pWord->pPrev &&													// Does previous word end with a base verb ending
			EndsWith(pWord->pPrev->sWord, Helpers[i][0]) )
		{
			return 1;		// It's a helper verb
		}
	}

	return 0;		// Sorry charlie
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrCombineHelperVerbs
 * DESC: 	Combine helper verbs with their main verb 
			so that they are treated as a single AP
 * IN:		phTTS - pointer to TTS stuff
			pPhrases - pointer to parsed input data
 * OUT:		Helper verbs are combined with their main verb
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void KrCombineHelperVerbs(LPTTS_HANDLE_T phTTS, KOREAN_PHRASE *pPhrases)
{
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord,
		*pPrevWord;
    PKSD_T 
		pKsd_t = phTTS->pKernelShareData;


	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		pPrevWord = NULL;
		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{
			if( pWord->pPrev &&
				KrIsHelperVerb(pWord) )
			{
				// Add this word to the end of the last word
				KrCombineWords(pWord->pPrev, pWord);

#ifdef PH_DEBUG
				if(DT_DBG(LTS_DBG,0x080))
				{
					FNX_PRINTF("\n**KrCombineHelperVerbs %s %s\n", pWord->pPrev->sWord, pWord->sWord);
				}
#endif

			}
		}
	}
}


/*FUNCTION_HEADER**********************
 * NAME:	;KrIsVerb
 * DESC: 	Test a word to see if it is a verb
 * IN:		sWord - the word to be tested
			iGroup - Verb specific group number
 * OUT:		none
 * RETURN:	1 if it is a negative adverb, 0 if it is not
 * NOTES:	
 *END_HEADER***************************/
int KrIsVerb(KOREAN_WORD *pWord, int iGroup)
{
	char
		**psVerb,
		*sVerb1[] = {"hae", ""},
		*sVerb2[] = {"go", ""},
		*sVerb3[] = {"a", "eo", "yeo", "wa", "wo", ""},
		*sVerb4[] = {"ya", "man", "go", ""},
		*sVerb5[] = {"a", "eo", "yeo", ""},
		*sVerb6[] = {"reo", ""},
		*sVerb7[] = {"seo", ""},
		*sVerb8[] = {"da", ""};
	int i;
	KOREAN_SYLLABLE
		*pSyl,
		*pPrevSyl=NULL;

	// Find the word final syllable
	for(pSyl=pWord->pSyl; pSyl; pSyl=pSyl->pNext)
	{
		if( pSyl->pNext == NULL )
			break;

		pPrevSyl = pSyl;
	}

	if( pSyl == NULL )
		return 0;

	switch(iGroup)
	{
		case 1:	psVerb = sVerb1;	break;
		case 2: psVerb = sVerb2;	break;
		case 3: psVerb = sVerb3;	break;
		case 4: psVerb = sVerb4;	break;
		case 5: psVerb = sVerb5;	break;
		case 6: psVerb = sVerb6;	break;
		case 7: psVerb = sVerb7;	break;
		case 8: psVerb = sVerb8;	break;
		default:	return 0;
	}
	for(i=0; psVerb[i][0] != 0x00; i++ )
	{
		if( FNXA_STRICMP(pSyl->sRoman, psVerb[i]) == 0 )
		{
			if( iGroup == 7 &&
				pPrevSyl &&
				FNX_STRCMP(pPrevSyl->sRoman, "myeon") == 0 )	//  ...-myeon-seo ...-da does not combine to form 1 AP
				return 0;
			else
				return 1;
		}
	}

	return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsAuxVerb
 * DESC: 	Test a word to see if it is an auxiliary verb
 * IN:		sWord - the word to be tested
			iGroup - Aux Verb specific group number
 * OUT:		none
 * RETURN:	1 if it is a negative adverb, 0 if it is not
 * NOTES:	
 *END_HEADER***************************/
int KrIsAuxVerb(char *sWord, int iGroup)
{
	char
		**psAux,
		*sAux1[] = {"ju-se--yo", ""},
		*sAux2[] = {"sip-da", "de--yo", ""},
		*sAux3[] = {"ju-da", "du-da", "bo-da", ""},
		*sAux4[] = {"ha-da", ""},
		*sAux5[] = {"iss-da", ""},
		*sAux6[] = {"ga-da", ""};
	int i;

	switch(iGroup)
	{
		case 1:	psAux = sAux1;	break;
		case 2: psAux = sAux2;	break;
		case 3: psAux = sAux3;	break;
		case 4: psAux = sAux4;	break;
		case 5: psAux = sAux5;	break;
		case 6: psAux = sAux6;	break;
		default:	return 0;
	}
	for(i=0; psAux[i][0] != 0x00; i++ )
	{
		if( EndsWith(sWord, psAux[i]) == 0 )
			return 1;
	}

	return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrCombineIncompleteVerbs
 * DESC: 	verbs + auxiliary verb combine to form one AP
 * IN:		pPhrases - pointer to the phrases
 * OUT:		none
 * RETURN:	none
 * NOTES:	

			These groups combine together to form 1 AP
			Verb Endings		Auxiliary Verb
			-go					<sip-da>, <de--yo>
			-a -eo -yeo -wa -wo	<ju-da>, <du-da>, <bo-da>
			-ya -man			<ha-da>
			-a eo yeo			<iss-da>

			Complex verbs that combine to form 1 AP
			-go					<ha-da>
			-reo				<ga-da>
			-seo				-da

			Verb combinations that form 1 AP
			-l(final letter)	<geos> <geot-da>
			-l(final letter)	<geos> <i-da>, <geo-ye-yo>, <geos> <i-ye-yo>


			Verb+Auxiliary Verb combinations that do NOT combine to form 1 AP
			-do					<doe-da>

			Complex verbs that do NOT combine to form 1 AP
			-eu-myeon-seo		-da
			-myeon-seo			-da
			-ha-myeon-seo		-da
			-go					-da
 *END_HEADER***************************/
void KrCombineIncompleteVerbs(LPTTS_HANDLE_T phTTS, KOREAN_PHRASE *pPhrases)
{
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord,
		*pPrevWord;
    PKSD_T 
		pKsd_t = phTTS->pKernelShareData;


	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		pPrevWord = NULL;
		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{
			if( pPrevWord &&									// We have a previous word to combine with
				pPrevWord->nSyls < 7 &&							// Previous word can't be more than 7 syllables after combining
				pWord->pSyl &&									// Current word can't be some end of phrase symbol.
				((KrIsAuxVerb(pWord->sWord, 1) && KrIsVerb(pPrevWord, 1)) ||
				 (KrIsAuxVerb(pWord->sWord, 2) && KrIsVerb(pPrevWord, 2)) ||
				 (KrIsAuxVerb(pWord->sWord, 3) && KrIsVerb(pPrevWord, 3)) ||
				 (KrIsAuxVerb(pWord->sWord, 4) && KrIsVerb(pPrevWord, 4)) ||
				 (KrIsAuxVerb(pWord->sWord, 5) && KrIsVerb(pPrevWord, 5)) ||
				 (KrIsAuxVerb(pWord->sWord, 6) && KrIsVerb(pPrevWord, 6)) ||
				 (KrIsVerb(pWord, 8) && KrIsVerb(pPrevWord, 7)) )
				)
			{
				// Add this syllable to the end of the last word
				KrCombineWords(pPrevWord, pWord);

#ifdef PH_DEBUG
				if(DT_DBG(LTS_DBG,0x080))
				{
					FNX_PRINTF("\n**KrCombineIncompleteVerbs %s %s\n", pPrevWord->sWord, pWord->sWord);
				}
#endif

				pWord = pPrevWord;
			}
			// Verb combinations that form 1 AP ( -l geos (gat-da | i-da))
			else if( pWord && 
					 pPrevWord &&
					 pPrevWord->nSyls < 7 &&			// make sure the previous word is not too heavy
					 pWord->pNext && 
					 *(pPrevWord->sWord+FNX_STRLEN(pPrevWord->sWord)-1) == 'l' &&	// Previous word ends in 'l'
					 FNX_STRICMP(pWord->sWord, "geos") == 0 )
			{
				if( FNX_STRICMP(pWord->pNext->sWord, "gat-da") == 0 ||		// geos gat-da
					FNX_STRICMP(pWord->pNext->sWord, "i-da") == 0 )			// geos i-da
				{
					// Add this syllable to the end of the last word
					KrCombineWords(pPrevWord, pPrevWord->pNext);
					KrCombineWords(pPrevWord, pPrevWord->pNext);

#ifdef PH_DEBUG
					if(DT_DBG(LTS_DBG,0x080))
					{
						FNX_PRINTF("\n**KrCombineIncompleteVerbs: -l geos (gat-da | i-da)\n");
					}
#endif

					pWord = pPrevWord;
				}
			}
			pPrevWord = pWord;
		}
	}
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrCombineIdioms
 * DESC: 	Combine words in an idiomatic expression into 
			a single Accentual Phrase (AP)
 * IN:		pPhrases - pointer to phrases
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
typedef char *IDIOM[5]; /* Array of 5 character pointers */
void KrCombineIdioms(LPTTS_HANDLE_T phTTS, KOREAN_PHRASE *pPhrases)
{
	int
		i, j, nMatch;
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord,
		*pTmp;
	IDIOM 
		Idioms[] = 
		{
			{"an-nyeong-hi", "ga-se--yo", "", "", ""},				// good-bye
			{"cheo--eum", "boeb-gess-seub-ni-da", "", "", ""},		// How do you do?
			{"sin-se", "manh--i", "jyeoss-seub-ni-da", "", ""},		// I am indebted to you for your kindness
			{"mal-sseum-ha-sin", "dae-ro", "ib-ni-da", "", ""},		// It is as you said
			{"ga-ji-go", "gye-sib-na-kka", "", "", ""},				// Do you have it with you?
			{"eo-seo", "o-se--yo", "", "", ""},						// Welcome
			{"", "", "", "", ""}
		};
    PKSD_T 
		pKsd_t = phTTS->pKernelShareData;


	// Look for an idiomatic expression in this phrase
	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		if( pPhrase->nWords <= 1 )
			continue;

		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{
			for( i=0; Idioms[i][0][0] != 0x00; i++ )
			{
				if( FNX_STRCMP(pWord->sWord, Idioms[i][0]) == 0 )
				{
					nMatch=1;
					for(j=1, pTmp=pWord->pNext; Idioms[i][j][0] != 0x00 && pTmp != NULL; j++, pTmp=pTmp->pNext )
					{
						if( FNX_STRCMP(pTmp->sWord, Idioms[i][j]) != 0 )
						{
							nMatch = 0;
							break;
						}
						nMatch++;
					}
					if( nMatch > 0 &&
						Idioms[i][j][0] == 0x00 )
					{
						// Combine words in idiomatic expression into a single AP
						for(i=0; i<nMatch-1; i++)
						{
							KrCombineWords(pWord, pWord->pNext);
						}
#ifdef PH_DEBUG
						if(DT_DBG(LTS_DBG,0x080))
						{
							FNX_PRINTF("\n**KrCombineIdioms: %s\n", pWord->sWord);
						}
#endif

						break;
					}	// all words in idiom match
				}	// word matches first word in idiom
			}	// for all idioms
		}	// for all words
	}	// for all phrases
}	// KrCombineIdioms

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsNegAdverb
 * DESC: 	Test a word to see if it is a negative adverb
 * IN:		sWord - the word to be tested
 * OUT:		none
 * RETURN:	1 if it is a negative adverb, 0 if it is not
 * NOTES:	
 *END_HEADER***************************/
int KrIsNegAdverb(char *sWord)
{
	char *sNegAdverbs[] = {
		"an",
		"mos",
		""
	};	
	int i;

	for(i=0; sNegAdverbs[i][0] != 0x00; i++ )
	{
		if( FNXA_STRICMP(sWord, sNegAdverbs[i]) == 0 )
			return 1;
	}

	return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrSetFocusOnNegAdverbs
 * DESC: 	Look for negative adverbs and set the focus flag if found
 * IN:		pPhrases - pointer to all phrases
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void KrSetFocusOnNegAdverbs(KOREAN_PHRASE *pPhrases)
{
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord;

	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{
			if( KrIsNegAdverb(pWord->sWord) )
			{
				pWord->bIsFocus = 1;
				pWord->pSyl->bFocus = 1;
				break;
			}
		}
	}
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrPhraseOnFocusWord
 * DESC: 	Rule: Focus word + following words = AP
 * IN:		pPhrases - pointer to all phrases
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void KrPhraseOnFocusWord(LPTTS_HANDLE_T phTTS, KOREAN_PHRASE *pPhrases)
{
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord;
    PKSD_T 
		pKsd_t = phTTS->pKernelShareData;


	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{
			if( pWord->bIsFocus )									// Found a focus word
			{
				while(pWord->pNext)									// Combine Focus word and all following words in phrase
				{
					KrCombineWords(pWord, pWord->pNext);
				}
#ifdef PH_DEBUG
				if(DT_DBG(LTS_DBG,0x080))
				{
					FNX_PRINTF("\n**KrPhraseOnFocusWord %s\n", pWord->sWord);
				}
#endif
			}
		}
	}
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrSetTonePattern
 * DESC: 	Evaluate phrases and set the tone pattern for each syllable of each word.
 * IN:		pPhrases - pointer to phrases
 * OUT:		iTone value of each syllable is set
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void KrSetTonePattern(LPTTS_HANDLE_T phTTS, KOREAN_PHRASE *pPhrases)
{
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord;
	KOREAN_SYLLABLE 
		*pSyl,
		*pLastSyl=NULL;
	char 
		cTone,
		cRom1,
		cRom2;
	int
		iSyl,
		iTone;
    PKSD_T 
		pKsd_t = phTTS->pKernelShareData;

	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{
			if( pWord->nSyls == 0 || 
				pWord->pSyl == NULL )
				continue;

			pWord->pSyl->iTone = 0;

			if( pPhrase->nWords == 1 &&
				pPhrase->iType & KR_PHRS_YESNO )
			{
				if( pWord->nSyls == 1 )
				{
					pWord->pSyl->cTone = 'H';
					pWord->pSyl->iTone = KR_INTON_HL;
				}
				else if( pWord->nSyls == 2 )
				{
					pWord->pSyl->cTone = 'H';
					pWord->pSyl->iTone = KR_INTON_H;
					pWord->pSyl->pNext->cTone = 'L';
					pWord->pSyl->pNext->iTone = KR_INTON_L;
				}
				continue;
			}
			else if( pWord->nSyls == 1 &&					// 1 syllable words
				pWord->pSyl )
			{
				if( pWord->pSyl->bFocus )
				{
					pWord->pSyl->cTone = 'H';
					pWord->pSyl->iTone = KR_INTON_H;
				}
				else
				{
					pWord->pSyl->cTone = 'H';
					pWord->pSyl->iTone = KR_INTON_H;
				}

				pLastSyl = pWord->pSyl;
			}
			else if( pWord->nSyls == 2 &&					// 2 syllable words
					 pWord->pSyl &&
					 pWord->pSyl->pNext )
			{
				if( pWord->pSyl->bFocus )
				{
					pWord->pSyl->cTone = 'H';
					pWord->pSyl->iTone = KR_INTON_H;
					pWord->pSyl->pNext->cTone = 'L';
					pWord->pSyl->pNext->iTone = KR_INTON_L;
				}
				else
				{
					pWord->pSyl->cTone = 'L';
					pWord->pSyl->iTone = KR_INTON_L;
					pWord->pSyl->pNext->cTone = 'H';
					pWord->pSyl->pNext->iTone = KR_INTON_H;
				}
				pLastSyl = pWord->pSyl->pNext;
			}
			else if( pWord->nSyls == 3 &&					// 3 syllable words
					 pWord->pSyl && 
					 pWord->pSyl->pNext &&
					 pWord->pSyl->pNext->pNext )
			{
				if( pWord->pSyl->bFocus ||
					(pWord->pNext == NULL && pLastSyl && (pLastSyl->iTone & KR_INTON_H)) )
				{
					pWord->pSyl->cTone = 'H';
					pWord->pSyl->pNext->cTone = 'X';
					pWord->pSyl->pNext->pNext->cTone = 'L';

					pWord->pSyl->iTone |= KR_INTON_H;
					pWord->pSyl->pNext->iTone |= KR_INTON_X;
					pWord->pSyl->pNext->pNext->iTone |= KR_INTON_L;
				}
				else
				{
					pWord->pSyl->cTone = 'L';
					pWord->pSyl->pNext->cTone = 'X';
					pWord->pSyl->pNext->pNext->cTone = 'H';

					pWord->pSyl->iTone |= KR_INTON_L;
					pWord->pSyl->pNext->iTone |= KR_INTON_X;
					pWord->pSyl->pNext->pNext->iTone |= KR_INTON_H;
				}

				pLastSyl = pWord->pSyl->pNext->pNext;
			}
			else											// 4 or more syllable words
			{
				iSyl = 0;
				if( pWord->pSyl->bFocus &&
					!(pPhrase->iType & KR_PHRS_WH_WORD) )
				{
					cTone = 'H';
					iTone = KR_INTON_H;
				}
				else
				{
					cTone = 'L';
					iTone = KR_INTON_L;
				}

				for(pSyl=pWord->pSyl; pSyl; pSyl=pSyl->pNext)
				{
					if( (1 < iSyl && iSyl < pWord->nSyls-2) ||		// Middle syllable (not 1,2, n-1, n)
						(iSyl == 1 &&								// 2nd syllable is focused
						 pLastSyl &&
						 pLastSyl == pWord->pSyl && 
						 pLastSyl->bFocus &&
						 !(pPhrase->iType & KR_PHRS_WH_WORD)) )
					{
						pSyl->cTone = 'X';			// Middle tones are interpolated L-H-X-X-L-H
						pSyl->iTone = KR_INTON_X;
					}
					else
					{
						pSyl->cTone = cTone;
						pSyl->iTone = iTone;
						cTone = (cTone == 'H') ? 'L' : 'H';
						iTone = (iTone == KR_INTON_H) ? KR_INTON_L : KR_INTON_H;
					}
					iSyl++;

					pLastSyl = pSyl;
				}

			}

			// If first consonant of word is /h,s,p,t,k,ch,pp,tt,kk,jj,ss/ 
			// change beginning tone from L to H
			if( pWord->pSyl )
			{
				cRom1 = pWord->sWord[0];
				cRom2 = pWord->sWord[1];
			}
			else
			{
				cRom1 = ' ';
			}

			if( cRom1 == 'h' ||						// h
				cRom1 == 's' ||						// s
				cRom1 == 'p' ||						// aspirated stops
				cRom1 == 't' ||
				cRom1 == 'k' ||
				(cRom1 == 'c' && cRom2 == 'h') ||	// aspirated affricate
				(cRom1 == 'p' && cRom2 == 'p') ||	// tense stops
				(cRom1 == 't' && cRom2 == 't') ||
				(cRom1 == 'k' && cRom2 == 'k') ||
				(cRom1 == 'j' && cRom2 == 'j') ||	// tense affricate
				(cRom1 == 's' && cRom2 == 's') )	// tense fricative
			{
				pWord->pSyl->cTone = 'H';
				pWord->pSyl->iTone = KR_INTON_H;

				// Change 3 syllable words with tone pattern H-X-H to H-H-H
				if( pWord->nSyls == 3 &&
					pWord->pSyl && 
					pWord->pSyl->pNext &&
					(pWord->pSyl->pNext->iTone & KR_INTON_X) )
				{
					// Should be HHH if word is a modifier
					// Should be HLH if word is a head noun or verb

					// Since we don't know the word POS right now make it HHH
					pWord->pSyl->pNext->cTone = 'H';
					pWord->pSyl->pNext->iTone = KR_INTON_H;
				}
			}

			if( pWord->pNext == NULL )							// Last word of phrase ?
			{
				if( pPhrase->iType & KR_PHRS_QUESTION )			// Question phrase ?
				{
					if( pPhrase->iType & KR_PHRS_YESNO )
					{
						// H% if yes/no question
						pLastSyl->cTone = 'H';
						pLastSyl->iTone = KR_INTON_H;
					}
					else if( pPhrase->iType & KR_PHRS_WH_WORD )
					{
						// HL% if wh-question
						pLastSyl->cTone = 'H';
						pLastSyl->iTone = KR_INTON_HL;			// Sun-Ah says it should be HL, 
																// but Mihwa likes H
																// all of our examples do H
					}
					else
					{
						// LH% if question
						pLastSyl->cTone = 'H';
						pLastSyl->iTone = KR_INTON_H;		//KR_INTON_LH;
						
					}

					// Make sure that the second to last syllable is L so we can do a question rise
					for(pSyl=pWord->pSyl; pSyl; pSyl=pSyl->pNext)
					{
						if( pSyl->pNext && pSyl->pNext->pNext == NULL )
						{
							pSyl->cTone = 'L';
							pSyl->iTone = KR_INTON_L;
						}
					}
				}
				else if( pPhrase->iType & KR_PHRS_EXCLAMATION )	// Exclamation phrase !
				{
					// What kind of phrase final intonation patterns are used with exclamation phrases?
				}
				else if( EndsWith(pWord->sWord, "de--yo") )
				{
					pLastSyl->cTone = 'L';
					pLastSyl->iTone = KR_INTON_LH;				// Ending tone is LH

					if( pLastSyl->pPrev &&						// ...-L-LH%
						!(pLastSyl->pPrev->iTone & KR_INTON_L) )
					{
						pLastSyl->pPrev->iTone = KR_INTON_L;
					}
				}
				else											// Statement phrase .
				{
					pLastSyl->cTone = 'L';						// Ending tone should be L
					pLastSyl->iTone = KR_INTON_L;

					if( pWord->nSyls == 3 &&
						pWord->pSyl->iTone & KR_INTON_H )		// HHL -> HXL
					{
						pWord->pSyl->pNext->iTone = KR_INTON_X;
					}
					
				}

				pLastSyl->iTone |= KR_INTON_PCT;

				if( pLastSyl->iTone & KR_INTON_a )
					pLastSyl->iTone ^= KR_INTON_a;
			}
			else
			{
				pLastSyl->iTone |= KR_INTON_a;
			}

		}	// for all words

	}	// for all phrases

#ifdef PH_DEBUG
	if( DT_DBG(PH_DBG,0x001) ||
		DT_DBG(LTS_DBG, 0x080) )
	{
		char sTone[32];
		FNX_PRINTF("\n**KR Tones: ");
		for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
		{
			for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
			{
				for(pSyl=pWord->pSyl; pSyl; pSyl=pSyl->pNext)
				{
					if( pSyl != pWord->pSyl )
						FNX_PRINTF("-");

					KrGetToneString(pSyl->iTone, sTone);
					FNX_PRINTF("%s", sTone);

					if( pSyl->iTone & KR_INTON_a )
						FNX_PRINTF("a");
					if( pSyl->iTone & KR_INTON_PCT )
						FNX_PRINTF("%%");
					if( pSyl->iTone & KR_INTON_PLS )
						FNX_PRINTF("+");
				}

				if( pWord->pNext == NULL )						// End of Phrase ?
				{
					if( pPhrase->iType & KR_PHRS_QUESTION )
						FNX_PRINTF("? ");	// end of phrase
					if( pPhrase->iType & KR_PHRS_EXCLAMATION )
						FNX_PRINTF("! ");	// end of phrase
					if( pPhrase->iType & KR_PHRS_NEUTRAL )
						FNX_PRINTF(". ");	// end of phrase
				}
				else
				{
					FNX_PRINTF(" ");	// end of word
				}
			}
		}
		FNX_PRINTF("\n");
	}
#endif


}	// KrSetTonePattern


/*FUNCTION_HEADER**********************
 * NAME:	;KrCombineIncompleteNouns
 * DESC: 	When a word is an 'incomplete' noun such as "geod" (thing), 
			"su" (way), "de" (place), or "ji", these incomplete nouns 
			form on AP with the preceding noun
 * IN:		pPhrases - pointer to the phrases
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void KrCombineIncompleteNouns(KOREAN_PHRASE *pPhrases)
{
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord,
		*pPrevWord;

	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		pPrevWord = NULL;
		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{
			if( pPrevWord &&									// We have a previous word to combine with
				pWord->nSyls == 1 &&							// This word has only 1 syllable
				pPrevWord->nSyls < 7 &&							// Previous word can't be more than 7 syllables after combining
				(FNXA_STRCMP(pWord->sWord, "geod") == 0 ||		// This word is an incomplete noun
				 FNXA_STRCMP(pWord->sWord, "su") == 0 ||
				 FNXA_STRCMP(pWord->sWord, "de") == 0 ||
				 FNXA_STRCMP(pWord->sWord, "ji") == 0) )
			{
				KrCombineWords(pPrevWord, pWord);
			}
			pPrevWord = pWord;

		}
	}
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrSetFocusOnYesNoWords
 * DESC: 	
 * IN:		pPhrases - pointer to the phrases
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void KrSetFocusOnYesNoWords(KOREAN_PHRASE *pPhrases)
{
	char
		bAlreadyFocused=0;
	KOREAN_PHRASE 
		*pPhrase;
	KOREAN_WORD 
		*pWord;

	for(pPhrase=pPhrases; pPhrase; pPhrase=pPhrase->pNext)
	{
		for(pWord=pPhrase->pWords; pWord; pWord=pWord->pNext)
		{
			if( (FNX_STRCMP(pWord->sWord, "ne") == 0 ||		// yes
				 FNX_STRCMP(pWord->sWord, "anio") == 0) &&	// no
				 pPhrase->nWords == 1 )						// only 1 word in the phrase/clause
			{
				pWord->bIsFocus = 1;
				pWord->pSyl->bFocus = 1;
				pPhrase->iType |= KR_PHRS_YESNO;
				break;
			}
		}
	}
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrApplyIntonation
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void KrApplyIntonation(LPTTS_HANDLE_T phTTS, KOREAN_PHRASE *pPhrases)
{
    PKSD_T pKsd_t = phTTS->pKernelShareData;
	PDPH_T pDph_t = (PDPH_T)phTTS->pPHThreadData;

	// In the beginning each individual word is an Accentual Phrase (AP)
	// Rule: Word + incomplete noun = AP
	KrCombineIncompleteNouns(pPhrases);
	
	KrCombineIncompleteVerbs(phTTS, pPhrases);

	KrCombineHelperVerbs(phTTS, pPhrases);

	// Rule: wh-words + following words = AP
	KrSetFocusOnWhWords(pPhrases);			// Look for wh-words

	// Rule: Negative adverbs + following words = AP
	KrSetFocusOnNegAdverbs(pPhrases);

	// Rule: Yes/No words get emphasized
	KrSetFocusOnYesNoWords(pPhrases);

	// Combine focus word and following words into one AP
	KrPhraseOnFocusWord(phTTS, pPhrases);

	// Combine Idioms into one AP
	KrCombineIdioms(phTTS, pPhrases);

	// Set tone pattern for each Accentual Phrase (AP)
	KrSetTonePattern(phTTS, pPhrases);

	// The first syllable of a word has a slightly higher pitch.

	// The final syllable of a phrase is longer.

	// Command phrases have a falling intonation pattern.

	// Phrases with an exclamation point should have a dramatic tone

	KrPlaySounds(phTTS, pPhrases);

}
