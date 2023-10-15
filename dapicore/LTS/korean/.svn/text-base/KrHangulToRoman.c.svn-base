/*C_HEADER_FILE****************************************************************
FILE			:	KrHangulToRoman.c
DESC			:	
TABS			:	4
OWNER			:	Fonix
DATE CREATED	:	

(C) Copyright 2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.


Encoding Hangul in Unicode 
http://www.uni-graz.at/~katzer/korean_hangul_unicode.html

Theoretically, it would be possible to encode Korean texts with Jamo only and leave the task of 
Hangul construction to the font renderer. In Unicode, this is allowed, as a well-formed sequence 
of Jamo is canonically equivalent to the corresponding Hangul. Yet due to lack of support in 
current renderers, this is not recommended practise. To see whether your browser supports composition 
of Hangul from Jamo, compare the following three representations of the syllable HWEOLH: Precomposed 
Hangul ?, three Jamo ???, three Jamo separated by zero-width nonjoiners ?????. Ideally, the first two 
should render identically as compound Hangul. 
Instead, Korean is usualy coded in terms of Hangul characters that do not explicitly reference the 
underlying Jamo characters. Isolated Jamo are rarely found in Korean texts. The Unicode Standard assigns 
an individual code point to each Hangul. To calculate the code point of a Hangul from its Jamo components, 
the following formula may be used: 

Code point of Hangul = tail + (vowel-1)*28 + (lead-1)*588 + 44032 

In this formula, lead, vowel and tail refer to the small integer numbers given in the above tables 
(if there is no tail consonant, use the value 0). The Hangul syllabary occupies the Unicode range 
from AC00 (decimal 44032) to D7A3 (decimal 55171). 

In the other direction, the phonetic value of a Hangul can be calculated from its code point. It is 
convenient to use the modulo function mod(a,b), which yields the remainder of the quotient a/b, and 
the integer function int(a) which yields the integer part of a. 

tail = mod (Hangul codepoint - 44032, 28) 
vowel = 1 + mod (Hangul codepoint - 44032 - tail, 588) / 28 
lead = 1 + int [ (Hangul codepoint - 44032)/588 ] 



*END_HEADER*******************************************************************/
#include "stdio.h"


#include "port.h"

#include "FnxPlatform.h"
#include "FnxMisc.h"
#include "FnxByteOrder.h"
#include "KrHangulToRoman.h"
#include "KrTextNormal.h"

#define MAX_PHRASE_LENGTH 2048 // Maximum length a phrase for recognition is allowed to be.

/* In Unicode 2.0, Hanguel syllables go from 0xAC00-0xD7A3. 
   Each value represents one syllable, which consists of
   an initial consonant, a vowel, and possibly a final consonant.*/
#define HANGUL_BASE 0xAC00 // Beginning of Hangul characters
#define HANGUL_END  0xD7A3 // Last Hangul character

#define NUM_HANGUL_INITIAL 19
#define NUM_HANGUL_VOWEL 21
#define NUM_HANGUL_FINAL 28


/* In Unicode 2.0, Hanguel syllables go from 0xAC00-0xD7A3. 
   Each value represents one syllable, which consists of
   an initial consonant, a vowel, and possibly a final consonant.
   The possible initial consonants, vowels and final consonants
   are defined in the arrays psInitial[], psVowel[] and psFinal[],
   respectively.  The syllables are arranged such that all
   combinations of these are possible. */
static char * CONSTCONST psInitial[NUM_HANGUL_INITIAL] = {
			// http://www.korean.go.kr/eng/etc/rok_cont.html - official romanization info
	"g",	// g,k lax or plain stop
	"kk",	// kk tense stop
	"n",	
	"d",	// d,t lax or plain stop
	"tt",	// tt tense stop
	"r", 
	"m", 
	"b",	// b,p lax or plain stop
	"pp",	// pp tense stop
    "s",	// plain fricative
	"ss",	// tense fricative
	"-",	// no leading consonant
	"j",	// j plain affricate
	"jj",	// jj tense affricate
	"ch",	// aspirated affricate
	"k",	// k aspirated stop
	"t",	// t aspirated stop
	"p",	// p aspirated stop
	"h"		// plain fricative
};
static char * CONSTCONST psVowel[NUM_HANGUL_VOWEL]
  = {"a", "ae", "ya", "yae", "eo", "e", "yeo", "ye", "o",
     "wa", "wae", "oe", "yo", "u", "wo", "we", "wi", "yu",
     "eu", "ui", "i"};
static char * CONSTCONST psFinal[NUM_HANGUL_FINAL]
  = {"", "g", "kk", "gs", "n", "nj", "nh", "d", "l", "lg",
     "lm", "lb", "ls", "lt", "lp", "lh", "m", "b", "bs",
     "s", "ss", "ng", "j", "ch", "k", "t", "p", "h"};

/* Compare two SWORDS pointed to by void pointers */
int CmpSWORD(const void *a, const void *b)
{
   SWORD *pwA = (SWORD *)a;
   SWORD *pwB = (SWORD *)b;
   if (*pwA < *pwB)
      return -1;
   if (*pwA > *pwB)
      return 1;
   return 0;
}

#define NUM_AMBIGUOUS_HANGUL 27

 /* Following is a list of {final<<8+initial} indices of consonants
    which are ambiguous and thus need a '-' between them.  This
    list must be sorted by value so that a bsearch() is possible. */
static const short pwAmbiguous[NUM_AMBIGUOUS_HANGUL]=
   {0x0001 /* -kk*/, 0x0004 /* -tt*/, 0x0008 /* -pp*/, 0x000a /* -ss*/, 
    0x000d /* -jj*/, 0x010a /*g-ss*/, 0x020f /*kk-k*/, 0x0309 /*gs-s*/,
    0x0400 /* n-g (not truly ambiguous, but it's misleading to see "ng" together when n-g is meant)*/,
    0x040d /*n-jj*/, 0x050c /*nj-j*/, 0x0804 /*l-tt*/, 0x0808 /*l-pp*/, 
    0x080a /*l-ss*/, 0x0c09 /*ls-s*/, 0x0d10 /*lt-t*/, 0x0e11 /*lp-p*/, 
    0x110a /*b-ss*/, 0x1209 /*bs-s*/, 0x1309 /*s-s*/,  0x130a /*s-ss*/, 
    0x1409 /*ss-s*/, 0x160c /*j-j*/,  0x1801 /*k-kk*/, 0x180f /*k-k*/, 
    0x1910 /*t-t*/,  0x1a11 /*p-p*/};


/*FUNCTION_HEADER**********************
 * NAME:    ;LongestMatch
 * DESC:    Find the longest string in a list of strings that match the beginning of a given string.
 * IN:      s - String to try to find a match in.
            psStringList - Array of strings to try to match to the beginning of 's'.
            iNumStrings - Number of strings in psStringList[].
 * OUT:     n/a
 * RETURN:  Index of the longest string in psStringList that 's' begins with.
            Returns a -1 if no match is found.
 * NOTES:   For example, if s="eon-o" and the list contains {"a", "eo", "e", "o", and "yeo"},
               then elements [1] ("eo") and [2] ("e") would both match the beginning
               of the string, but [1] is longer, and thus its index would be returned.
 *END_HEADER***************************/
int LongestMatch(char *s, char **psStringList, int iNumStrings)
{
   int i;
   int iLen, iBestLen=-1;
   int iBestIndex = -1; /* Haven't found a match yet */
   char *pc1, *pc2;

   for (i=0; i<iNumStrings; i++)
   {
      iLen=0;
      for (pc1=s, pc2=psStringList[i]; *pc1 && *pc2 && *pc1==*pc2; pc1++, pc2++)
         iLen++;
      if (*pc2==0) /* Reached the end of psStringList[i], indicating that it matched the beginning of s */
      {
         if (iLen > iBestLen)
         {
            iBestLen = iLen;
            iBestIndex = i;
         }
      }
   }  /* for i */
   return iBestIndex;
}  /* LongestMatch */

/*FUNCTION_HEADER**********************
 * NAME:    ;StrCopyCat
 * DESC:    Copy one string to another, and return a pointer to the END of the new string.
 * IN:      sDest - Location to copy the string to
            sSrc  - String to copy into sDest
 * OUT:     sSrc is copied into sDest
 * RETURN:  Pointer to the END of sDest (i.e., where the null terminator is)
 * NOTES:   Same as 'strcpy(sDest, sSource)', except that it returns a pointer
              to the end of a string.  So if you are concatentating a whole
              bunch of strings, you can do so using this routine instead of
              "strcat", which would have to start at the beginning of the
              string to find the end of the (longer and longer) string each time.
 *END_HEADER***************************/
char *StrCopyCat(char *sDest, char *sSource)
{
   char *pcDest, *pcSource;
   /* Copy sSource into sDest */
   for (pcDest=sDest, pcSource=sSource; *pcSource; pcSource++, pcDest++)
      *pcDest = *pcSource;
   *pcDest=0; /* Null terminate */
   /* Return pcDest, the location of the null terminator at the end of the string. */
   return pcDest;
}  /* StrCopyCat */


/*FUNCTION_HEADER**********************
 * NAME:    ;HangulToRoman
 * DESC:    Convert a Unicode Hangul string to a romanized narrow-character string.
 * IN:      wsHangul - A wide-character string of Unicode 2.0 Hangul characters.
            sAscii    - Buffer to put romanized characters into (NULL=>calculate size and allocate it).
 * OUT:     An ASCII string is allocated if necessary, and then 
               filled with a romanized version of the string.
 * RETURN:  Size of string to pass in, or 0 on error.
 * NOTES:   Any unicode characters in the range 0x0000-0x00FF (i.e., 0-255)
              are copied over directly as ASCII characters.
            Unicode characters not in the ASCII (0-255) or Hangul (0xAC00-0xD7A3) ranges
              cause a '?' to be output.
            The resulting romanized string can be converted back to Hangul Unicode
              by calling RomanToHangul().
 *END_HEADER***************************/
int HangulToRoman(wchar_t *wsHangul, char *sAscii)
{
	int 
		iOffset,  /* Index into array of Unicode Hangul characters */
		iInitial, /* Index into psInitial[] array */
		iVowel,   /* Index into psVowel[] array */
		iFinal,   /* Index into psFinal[] array */
		iLength,  /* Total number of characters for entire array */
		iSyllablesPerInitial = NUM_HANGUL_VOWEL*NUM_HANGUL_FINAL,
		iPrevFinal; /* Index in psFinal[] of the final consonant of the previous syllable */
   wchar_t 
	   *ws;
   BOOL 
	   bNewWord=TRUE; /* Flag for whether the next symbol begins a new word */
   char 
	   *sRoman, *pc;
   SWORD 
	   wPair;    /* Temporarily value consisting of (iFinalConsonant<<8) + iInitialConsonant */
   
   if (wsHangul==NULL)
      return 0;

   if (sAscii==NULL)
   {
	   /* Determine the length of the array to allocate */
	   iLength = 0;
	   for (ws = wsHangul; *ws; ws++)
	   {
		   if (*ws < HANGUL_BASE || *ws > HANGUL_END)		// *ws is not a Hangul character
		   {
				iLength++; // Use an ASCII symbol or '?' for any non-Hangul characters
				bNewWord=TRUE;
		   }
		   else
		   {
			   /* Get the offset of the hangul character in the Hangul section of the Unicode space. */
			   iOffset = (int)*ws - HANGUL_BASE;
			   
			   /* Get the offset of the three parts of the syllable */
			   iInitial = iOffset / iSyllablesPerInitial;
			   iVowel	= (iOffset%iSyllablesPerInitial) / 28;
			   iFinal	= iOffset%28;
			   
			   // Insert a syllable break
			   if( !bNewWord )
			   {
				   iLength++;
			   }

			   /* The initial symbol should only be a '-' if this is the beginning of a new word */
			   if ((bNewWord && iInitial!=11) || (!bNewWord && iInitial==11))
			   {
				   iLength += FNX_STRLEN(psInitial[iInitial]);
			   }
			   else if (!bNewWord) // i.e., skip an initial 11 of a new word
			   {
				   wPair = (((SWORD)iPrevFinal) << 8) + (SWORD)iInitial;
				   if (FNX_BSEARCH(&wPair, pwAmbiguous, NUM_AMBIGUOUS_HANGUL, sizeof(SWORD), CmpSWORD))
					   iLength++; // Add one for '-'
				   iLength += FNX_STRLEN(psInitial[iInitial]);
			   }
			   // ...(else this is a new word with an initial silent consonant (#11), so add nothing).
			   iLength += FNX_STRLEN(psVowel[iVowel]) + strlen(psFinal[iFinal]);
			   iPrevFinal = iFinal;
			   bNewWord=FALSE;
		   }
	   }  /* for ws */
	   return iLength+1;
	   
   }
   else 
	   sRoman = sAscii;

   bNewWord=TRUE;
   for (pc=sRoman, ws = wsHangul; *ws; ws++)
   {
	   if (*ws < HANGUL_BASE || *ws > HANGUL_END)
	   {

		   if (*ws<255)
			   *pc++ = (char)*ws;	// Copy any ASCII characters straight across (e.g., digits, punctuation, etc.)
		   else 
			   *pc++ = '?'; 	// Use a '?' for any unknown Unicode characters. 
		   bNewWord=TRUE;
	   }
	   else // Hangul
	   {
		   /* Get the offset of the hangul character in the Hangul section of the Unicode space. */
		   iOffset = (int)*ws - HANGUL_BASE;
		   
		   /* Get the offset of the three parts of the syllable */
		   iInitial = iOffset / iSyllablesPerInitial;
		   iVowel	= (iOffset%iSyllablesPerInitial) / NUM_HANGUL_FINAL;
		   iFinal	= iOffset%NUM_HANGUL_FINAL;
#ifndef CASIO_SH3
		   FNX_ASSERT(iInitial>=0 && iInitial < NUM_HANGUL_INITIAL && 
			   iVowel>=0 && iVowel< NUM_HANGUL_VOWEL && 
			   iFinal>=0 && iFinal < NUM_HANGUL_FINAL);
#endif
		   
		   // Insert a syllable break
		   if( !bNewWord )
		   {
			   pc = StrCopyCat(pc, SYLLABLE_MARKER_STR);
		   }
		   
		   /* If there is no initial consonant (i.e., #11), and this is not
			  the beginning of a new word, then a '-' is needed.  For example, 
			  "hage" could be "ha-ge" or "hag-e", in the latter case, the initial 
			  silent consonant is represented by a '-'.  We never need a '-' at
			  the beginning of a word, though. However, if we have a single syllable word
			  like 'i', this can be mistaken by the LTS rules for a roman letter so we will
			  put a '-' in front for this case*/
		   if( (bNewWord && iInitial!=11) || 
			   (!bNewWord && iInitial==11) ||
			   (bNewWord && iInitial == 11 && iVowel > 0 && iFinal == 0 && *(ws+1) == 0x00) )
		   {
			   pc = StrCopyCat(pc, psInitial[iInitial]);
		   }
		   else if (!bNewWord) // i.e., skip an initial 11 of a new word
		   {
			   /* This is not the beginning of a word, and the initial consonant
			   is not the silent one, so we must check for ambiguities that
			   can arise with double consonants.  For example, "mokki" could 
			   be "mok-ki" or "mo-kki" [but not "mokk-i", since the initial 
			   silent consonant would have been taken care of in the "if" 
			   statement above].*/
			   /* Do a binary search into the {final,initial} pairs stored in
			   pwAmbiguous[] to see if the current pair is in there.  The table
			   consists of final<<8+initial, so make such a value that we can use. */

			   // This isn't necessary since we are already putting a '-' between each syllable
//			   SWORD wPair = (((SWORD)iPrevFinal) << 8) + (SWORD)iInitial;
//			   if (FNX_BSEARCH(&wPair, pwAmbiguous, NUM_AMBIGUOUS_HANGUL, sizeof(SWORD), CmpSWORD))
//				   *pc++ = '-'; /* Insert a '-' between ambiguous final/initial consonant pairs */
			   pc = StrCopyCat(pc, psInitial[iInitial]);
		   }
		   // ...(else this is a new word with an initial silent consonant (#11), so add nothing).
		   
		   /* Copy the vowel */
		   pc = StrCopyCat(pc, psVowel[iVowel]);
		   
		   /* Copy the final consonant (which may be the empty string) */
		   iPrevFinal = iFinal; /* Remember the previous consonant ID so as to check for ambiguity. */
		   pc = StrCopyCat(pc, psFinal[iFinal]);
		   bNewWord=FALSE;
	   }
	}
	*pc = 0x00;		// null terminate;

   return FNX_STRLEN(sRoman);

}  /* HangulToRoman */
 

/*FUNCTION_HEADER**********************
 * NAME:	;ConvertToAscii
 * DESC: 	Convert korean text into a romanized version
 * IN:		phTTS - pointer to the TTS data structure
			wstr - the korean input text
 * OUT:		szbuf - the romanized text
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int ConvertToAscii(LPVOID phTTS, void *wstr, char *szbuf, BOOL bUnicode)
{
	char
		sTmp[32],
		sRomanWord[128],
		*pc;
#if defined CASIO_SH3 && defined _BIGENDIAN_
	wchar_t 
		*pwc1,
		*pwc2,
		pwcTmp,
		wsNormal[128],
		wsWordEndings[] = {0x20,0x2d,0x5f,0x2e,0x3f,0x21,0x2c,0x3b,0x3a,0xd,0xa}; // hex equivalents for " -_.?!,;:\r\n";
#else
	wchar_t 
		*pwc1,
		*pwc2,
		pwcTmp,
		wsNormal[128],
		wsWordEndings[] = L" -_.?!,;:\r\n";
#endif
	int
		nConverted=0,
		nWords=0,
		iSepType=0,
		nUsed,
		bTextNormalCmd=0;
	static int
#if defined CASIO_SH3 && defined _BIGENDIAN_
		bDebugMode,
#else
		bDebugMode=0,
#endif
		bTextNormalMode=1;

	if( wstr == NULL ||			// idiot check
		szbuf == NULL )
		return 0;

	memset(sRomanWord, 0, 128);
	memset(wsNormal, 0, 128*sizeof(wchar_t));
	szbuf[0] = 0x00;

	// Convert 1 word at a time so that we can also do Text normalization
	for( pwc1=wstr; *pwc1; pwc1++ )
	{
		iSepType = 0;
		if( HANGUL_BASE <= *pwc1 && *pwc1 <= HANGUL_END )	// Found a word that begins with hangul
		{
			for( pwc2=pwc1; ; pwc2++ )							// Find the end of the word
			{
				if( FNXW_STRCHR(wsWordEndings, *pwc2) )
				{
					iSepType = 1;
					break;
				}
				else if( !(HANGUL_BASE <= *pwc2 && *pwc2 <= HANGUL_END) )
				{
					if( KrIsNumber(pwc2) || KrIsAlpha(pwc2) || KrIsSymbol(pwc2) )
						iSepType = 2;

					break;
				}
			}
			pwcTmp = *pwc2;										// Save the terminating character
			*pwc2 = 0x00;										// Null terminate the word
			nConverted += HangulToRoman(pwc1, sRomanWord);		// Convert to Romaji

			FNXA_STRCAT(szbuf, sRomanWord);
			
			if( iSepType == 1 )
			{
				sTmp[0] = (char)pwcTmp;								// copy the separating character
				sTmp[1] = 0x00;
				FNXA_STRCAT(szbuf, sTmp);
				nConverted++;
			}
			else if( iSepType == 2 )
			{
				FNXA_STRCAT(szbuf, "-");
			}

			*pwc2 = pwcTmp;										// Restore the terminating character

			if( pwcTmp == 0x0d &&								// Keep CR LF characters together
				*(pwc2+1) == 0x0a )
			{
				sTmp[0] = 0x0a;									// copy the separating characters
				sTmp[1] = 0x00;
				FNXA_STRCAT(szbuf, sTmp);
				nConverted++;
				pwc2++;
			}

			nWords++;											// increment the word counter

			if( pwc2 > pwc1 )
				pwc1 = pwc2-1;
		}	// if Hangul

		else if( *pwc1 == '^' &&							// Keep any focus commands
				 HANGUL_BASE <= *(pwc1+1) && *(pwc1+1) <= HANGUL_END )
		{
			FNXA_STRCAT(szbuf, "^");
		}

		else if( *pwc1 == '[' &&							// Keep any debug statements (or [:<cmd>...] )
				 *(pwc1+1) == ':' )
		{
			if( nWords == 0 )
			{
				pc = szbuf;										// get a pointer to the beginning of the output buffer
				nWords++;
			}
			else
			{
				pc = szbuf + FNXA_STRLEN(szbuf);				// get a pointer to the end of the output buffer
			}
				
#if defined CASIO_SH3 && defined _BIGENDIAN_
			if( FNXW_STRSTR(pwc1, ":debug") ||				// commands that will enable debug mode
					 FNXW_STRSTR(pwc1, ":DEBUG") ||
					 FNXW_STRSTR(pwc1, ":Debug") ||
					 FNXW_STRSTR(pwc1, ":phon") ||
					 FNXW_STRSTR(pwc1, ":PHON") ||
					 FNXW_STRSTR(pwc1, ":Phon") )
#else
			if( FNXW_STRSTR(pwc1, L":debug") ||				// commands that will enable debug mode
					 FNXW_STRSTR(pwc1, L":DEBUG") ||
					 FNXW_STRSTR(pwc1, L":Debug") ||
					 FNXW_STRSTR(pwc1, L":phon") ||
					 FNXW_STRSTR(pwc1, L":PHON") ||
					 FNXW_STRSTR(pwc1, L":Phon") )
#endif
			{
#if defined CASIO_SH3 && defined _BIGENDIAN_
				if( FNXW_STRSTR(pwc1, "tn") ||					// command to turn on/off text normalization
					FNXW_STRSTR(pwc1, "TN") ||
					FNXW_STRSTR(pwc1, "normal") ||
					FNXW_STRSTR(pwc1, "NORMAL") ||
					FNXW_STRSTR(pwc1, "Normal") )
#else
				if( FNXW_STRSTR(pwc1, L"tn") ||					// command to turn on/off text normalization
					FNXW_STRSTR(pwc1, L"TN") ||
					FNXW_STRSTR(pwc1, L"normal") ||
					FNXW_STRSTR(pwc1, L"NORMAL") ||
					FNXW_STRSTR(pwc1, L"Normal") )
#endif
				{
					bTextNormalCmd = TRUE;
#if defined CASIO_SH3 && defined _BIGENDIAN_
					if( FNXW_STRSTR(pwc1, "off") ||
						FNXW_STRSTR(pwc1, "OFF") )
#else
					if( FNXW_STRSTR(pwc1, L"off") ||
						FNXW_STRSTR(pwc1, L"OFF") )
#endif
					{
						bTextNormalMode = FALSE;
					}
#if defined CASIO_SH3 && defined _BIGENDIAN_
					else if( FNXW_STRSTR(pwc1, "on") ||
							 FNXW_STRSTR(pwc1, "ON") )
#else
					else if( FNXW_STRSTR(pwc1, L"on") ||
							 FNXW_STRSTR(pwc1, L"ON") )
#endif
					{
						bTextNormalMode = TRUE;
					}
				}

				bDebugMode = TRUE;
			}
			else
			{
				bDebugMode = FALSE;
			}

			for( pwc2 = pwc1; *pwc2; pwc2++ )					// copy until we get to the end of the [:debug ...] section
			{
				if( !bTextNormalCmd )							// don't copy text normalization commands
				{

					*pc = *pwc2 & 0x00FF;
					pc++;
				}

				if( *pwc2 == ']' )
				{
					if( !bTextNormalCmd )
						*pc = 0x00;
					break;
				}
			}
			bTextNormalCmd = FALSE;

			pwc1 = pwc2;										// skip to end of [:debug ...] section
		}
		else if( bDebugMode &&								// Skip debug data sections [...]
				 *pwc1 == '[' )
		{
			if( nWords == 0 )
			{
				pc = szbuf;										// get a pointer to the beginning of the output buffer
				nWords++;
			}
			else
			{
				pc = szbuf + FNXA_STRLEN(szbuf);				// get a pointer to the end of the output buffer
			}
				
			for( pwc2 = pwc1; *pwc2; pwc2++ )					// copy until we get to the end of the [...] section
			{
				*pc = *pwc2 & 0x00FF;
				pc++;
				if( *pwc2 == ']' )
				{
					*pc = 0x00;
					break;
				}
			}
			pwc1 = pwc2;										// skip to end of [...] section
		}

		else if( KrIsAlpha(pwc1) ||							// This word  begins with a character that needs to be normalized to Hangul
				 KrIsNumber(pwc1) || 
				 KrIsSymbol(pwc1) )
		{
			for( pwc2=pwc1; *pwc2; pwc2++ )						// Find the end of the word
			{
				if( FNXW_STRCHR(wsWordEndings, *pwc2) )
				{
					if( KrIsNumber(pwc2+1) ||					// Don't stop in the middle of a real number
						KrIsAlpha(pwc2+1) )						// email address or URL
						continue;
					else
					{
						iSepType = 1;
						break;
					}
				}
				else if( (HANGUL_BASE <= *pwc2 && *pwc2 <= HANGUL_END) )
				{
					if( KrIsUnitOfMeasure(pwc2) )				// Don't stop if unit of measure
						continue;
					else if( (nUsed = KrIsCountingWord(pwc2)) )
					{
						pwc2 += (nUsed-1);
						continue;
					}
					else
					{
						iSepType = 2;
						break;
					}
				}
			}
			pwcTmp = *pwc2;
			*pwc2 = 0x00;

			// Normalize
			if( bTextNormalMode )
			{
				nUsed = KrNormalizeText(pwc1, wsNormal);
			}
			else
			{
				FNXW_STRCPY(wsNormal, pwc1);
				nUsed = FNXW_STRLEN(wsNormal);
			}

			HangulToRoman(wsNormal, sRomanWord);				// Convert to Romaji			
			if( nWords == 0 )
				FNXA_STRCPY(szbuf, sRomanWord);					// copy to the output buffer
			else
				FNXA_STRCAT(szbuf, sRomanWord);
			

			nConverted += pwc2-pwc1;
			
			if( iSepType == 1 )									// copy the separating character
			{
				if( nUsed > 0 && nUsed < (pwc2-pwc1) )
					sTmp[0] = ' ';
				else
					sTmp[0] = (char)pwcTmp;							
	
				sTmp[1] = 0x00;
				FNXA_STRCAT(szbuf, sTmp);
				nConverted++;
			}
			else if( iSepType == 2 )
			{
				FNXA_STRCAT(szbuf, "-");						// the next character is Hangul so add a syllable separator
			}
			else
			{
				FNXA_STRCAT(szbuf, " ");
			}

			*pwc2 = pwcTmp;										// Restore the terminating character

			if( pwcTmp == 0x0d &&								// Keep CR LF characters together
				*(pwc2+1) == 0x0a )
			{
				sTmp[0] = 0x0a;									// copy the separating characters
				sTmp[1] = 0x00;
				FNXA_STRCAT(szbuf, sTmp);
				nConverted++;
				pwc2++;
			}

			nWords++;											// increment the word counter
			if( nUsed < pwc2-pwc1 &&
				nUsed > 0 )
			{
				pwc1 += nUsed-1;
			}
			else if( pwc2 > pwc1 )
			{
				pwc1 = pwc2-1;
			}

		}
	}

	return nConverted;
}


/*FUNCTION_HEADER*******************
 * NAME:	;CheckUnicodeHeader
 * DESC:	Read the first two or three bytes of a Unicode file to see what kind it is.
 * IN:		fp - File to check.
			pbLittleEndian - Address in which to return a flag indicating whether the unicode
            file is little-endian or not.
 * OUT:		*pbLittleEndian is modified (IF the file is unicode).
			The file is advanced beyond the 2- or 3-byte header, if there is one,
			or is rewound to the beginning, if there is not.
 * RETURN:	TRUE if the file is unicode, FALSE otherwise.
 * NOTES:	File should be opened and positioned at the very beginning.
 *END_HEADER***************************/
BOOL CheckUnicodeHeader(FILE *fp, BOOL *pbLittleEndian)
{
	BOOL bUnicode=FALSE;
	unsigned char sBuf[4];

	/* Unicode files usually begin with "FF FE" (little-endian), or "FE FF" (big-endian).
	So check to see if we have one of those cases. */
	FNX_FREAD(sBuf, 2, 1, fp);
	if (sBuf[0]==0xFF && sBuf[1]==0xFE)
	{
		bUnicode = TRUE;
		*pbLittleEndian=TRUE;
	}
	else if (sBuf[0]==0xFE && sBuf[1]==0xFF)
	{
		bUnicode = TRUE;
		*pbLittleEndian=FALSE;
	}
	else
	{
		/* Compressed unicode files begin with a byte before the FFFE/FEFF bytes
		that inidcate what kind of compression is used.  We'll ignore most kinds,
		but two standard kinds we can handle:
		0x0E => This is a regular (uncompressed, UTF-16) unicode file.
		0x0F => This is a UTF-8 unicode file, i.e., it uses 1 byte per character, 
		probably in ASCII, so just treat it as though it was not unicode.
		See http://www.unicode.org/unicode/reports/tr6/index.html#Signature
		*/
		FNX_FREAD(&sBuf[2], 1, 1, fp);
		if (sBuf[1]==0xFF && sBuf[2]==0xFE)
			*pbLittleEndian=TRUE;
		else if (sBuf[1]==0xFE && sBuf[2]==0xFF)
			*pbLittleEndian=FALSE;
		else FNX_FSEEK(fp, 0, SEEK_SET);
		bUnicode=FALSE;
	}
	return bUnicode;
}  /* CheckUnicodeHeader */

/*FUNCTION_HEADER**********************
 * NAME:    ;BlockByteSwap16
 * DESC:    Swap the bytes of each 2-byte integer in an array
 * IN:      pi - Array of 16-bit (2-byte) integers to swap bytes in
            iSize - Number of elements in pi[]
 * OUT:     pi[0..iSize-1] each have their bytes swapped.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
void BlockByteSwap16(UWORDPTR pw, UDWORD iSize)
{
   UDWORD i;
   for (i=0; i< iSize; i++)
   {
      *pw = ((unsigned short) 0x00FFU & *pw >> 8) | ((unsigned short) 0xFF00U & *pw << 8);
      pw++; // some compilers don't handle the *pw++ = F(*pw) well.
   }
}

/*FUNCTION_HEADER*******************
 * NAME:	  ;ReadWordList
 * DESC:	  Read a file containing lines of the form "<ID#><tab><word or phrase>\n"
 * IN:     sWordList  - Filename of word list file containing lines with 
                          "<ID#><tab><word or phrase>\n" (Ignore any lines beginning with non-numeric characters).
           ppsWords   - Address in which to return a pointer to an array of 
                          strings with the words (or phrases).
           ppiWordIDs - Address in which to return a pointer to an array of 
                          ID#s associated with each element in (*ppsPhrases)[].
 * OUT:    *ppsPhrases and *ppiPhraseID are modified.
 * RETURN: Number of words or phrases read (or -1 on error).
 * NOTES:
 *END_HEADER***************************/
int FnxReadWordList(char *wsWordFile, char *wsWordConvertionFile)
{
   FILE *fp, *fpWrite;                     /* Word list file */
   wchar_t wsBuf[MAX_PHRASE_LENGTH*sizeof(wchar_t)] = {0}; /* Character array to read each line into */
   unsigned char sBuf[MAX_PHRASE_LENGTH] = {'\0'}; /* Character array to read each line into */
   unsigned char sBufRomanji[MAX_PHRASE_LENGTH] = {'\0'}; /* Character array to read each line into */
   int  iNumWords=0;        /* Number of words in pWordList and pIDList */
   SDWORD iNumber = 0;
   BOOL bUnicode;           /* Flag for whether the text file is unicode */
   BOOL bLittleEndian;      /* Flag for whether the unicode file is little-endian */
   BOOL bGrammar = FALSE;

   /* Open the word list file */
   fp = FNX_FOPEN(wsWordFile, "rb");
   if (fp==NULL)
   {
//      Message(NULL,"Error: Could not open word list file '%S'\n", wsWordList);
      return -1;
   }

   fpWrite = FNX_FOPEN(wsWordConvertionFile, "w");

   bUnicode = CheckUnicodeHeader(fp, &bLittleEndian);

   bUnicode = TRUE;
   while (bUnicode ? (int)fgetws(wsBuf, MAX_PHRASE_LENGTH, fp) : (int)FNX_FGETS(sBuf, MAX_PHRASE_LENGTH, fp))
   {
	   if (bUnicode)
      {
#ifdef WORDS_LITTLEENDIAN
         if (!bLittleEndian)
#else
         if (bLittleEndian)
#endif
         {  /* Swap the bytes if different from the host */
            BlockByteSwap16(wsBuf, FNXW_STRLEN(wsBuf));
         }
         ConvertToAscii(NULL, wsBuf, sBufRomanji, bUnicode);
      }
		else
		{
//			int strLength;
//			wchar_t * wTemp;
			// We need to check each line to see if it is Unicode or not.
//			if (sBuf[0] < 0x80)
//			{

//				strLength = FNX_STRLEN(sBuf);
//				memset(wsBuf, 0, MAX_PHRASE_LENGTH*sizeof(wchar_t));
				// We need to convert the sentence to wide for the convertion to romongi.
//				mbstowcs( wsBuf,  sBuf, strLength );
//				wTemp = wsBuf;
//			}
//			else
//			{
//				wTemp = (wchar_t *)sBuf;
//				BlockByteSwap16(wTemp, FNXW_STRLEN(wTemp));
//			}
			// sBuf will be over written.
			ConvertToAscii(NULL, (wchar_t*)sBuf, sBufRomanji, FALSE);
		}

	  if (sBufRomanji[0]==0)
	  {
//		   FNX_PRINTF("\n");
         FNX_FWRITE("\n", sizeof(char), 1, fpWrite);
		   continue; /* Skip blank lines */
	  }

//     FNX_PRINTF("Romongi String = %s\n", sBufRomanji);
     FNX_FWRITE(sBufRomanji, sizeof(char), FNX_STRLEN(sBufRomanji), fpWrite);

	  memset( sBufRomanji, 0, MAX_PHRASE_LENGTH);
	  sBuf[0] = 0;
	  wsBuf[0] = 0;
  
	}  /* while not at end of file */

   /* Close the word list file */
   FNX_FCLOSE(fpWrite);
   FNX_FCLOSE(fp);
   return 0;
}  /* ReadWordList */

