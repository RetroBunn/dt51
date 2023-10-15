/*C_HEADER_FILE****************************************************************
FILE        :  FnxLtsRulesEngine.c	(formerly Graph2Phon.c (formerly "phonetic.c"))
DESC        :  Functions used to execute the grapheme-to-phoneme conversion 
TABS        :  3
OWNER       :  
DATE CREATED:  

(C) Copyright 2006 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.


*END_HEADER*******************************************************************/
#include "port.h"
#include "FnxLtsRulesEngine.h"

//moved to port.h for each platform - MLT
//#include <stdio.h>
//#include <string.h>
//#include <ctype.h>

/*
** English to Phoneme translation.
**
** Rules are made up of four parts:
** 
**    The left context.
**    The text to match.
**    The right context.
**    The phonemes to substitute for the matched text.
**
** Procedure:
**
**    Seperate each block of letters (apostrophes included) 
**    and add a space on each side.  For each unmatched 
**    letter in the word, look through the rules where the 
**    text to match starts with the letter in the word.  If 
**    the text to match is found and the right and left 
**    context patterns also match, output the phonemes for
**    that rule and skip to the next unmatched letter.
**
**
** Special Context Symbols:
**
**    #  One or more vowels
**    :  Zero or more consonants
**    ^  One consonant.
**    .  One of b, d, v, g, j, l, m, n, r, w or z (voiced consonants)
**    %  One of er, e, es, ed, ing, ely (a suffix, in right context only)
**    >  A user defined suffix
**    +  One of e, i or y (a "front" vowel)
**    =  one or more numbers
*/

/* List of characters to treat as punctuation, if not already handled in punctuation rule */
#define PUNCTUATION_LIST  "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"

#if 0
#define FNX_STRCPY	strcpy
#define FNX_STRCAT	strcat
#define FNX_STRCMP	strcmp
#define FNX_STRLEN	strlen
#define FNX_TOLOWER tolower
#define FNX_STRCHR	strchr
#define FNX_MESSAGE	fprintf
#define	FNX_STDERR	stderr
#define FNX_ASSERT(x)
#endif

//#define DEBUG_RULES
#ifdef DEBUG_RULES
#define FNX_MESSAGE	fprintf
#endif

#define MAX_WORD	512

#ifndef BOOL
#define BOOL		unsigned char
#endif

#ifndef TRUE
#define TRUE		1
#endif

#ifndef FALSE
#define FALSE		0
#endif

int FindRule(char sWord[], int *piIndex, Graph2PhonPtr pGraph2Phon, int iRuleSet, char *sPron);
int LeftMatch(char *sPattern, char *sWord, int iIndex, Graph2PhonPtr pGraph2Phon);
int RightMatch(char *sPattern, char *sRemainder, Graph2PhonPtr pGraph2Phon);

/*FUNCTION_HEADER**********************
 * NAME:    ;translate
 * DESC:    Convert a word into its phonetic pronunciation
 * IN:      pGraph2Phon - Graph2Phon rules.
            sWordIn - Word to convert to phonemes
 * OUT:     A string is allocated
 * RETURN:  Pointer to the newly-allocated pronunciation string (or NULL on error).
 * NOTES:   Includes surrounding parentheses (e.g., "(tc [th] u)").
 *END_HEADER***************************/
int translate(Graph2PhonPtr pGraph2Phon, char *sWordIn, char *sPron)
{
	char  *pc, 
		  *pcIn=sWordIn,
		  sWord[MAX_WORD];
	int   iIndex = 0,		/* Current position in word */
		  iRuleSet,			/* First letter of match part */
		  iRuleNum,			/*  Which rule was used  */
		  iWordInLen=0;		/* length of input word */
	
	if (pGraph2Phon==NULL)
		return 0;			/* No graph2phon rules available */
	
#ifdef DEBUG_GRAPH2PHON
	char  sRulesUsed[MAX_LINE], 
		sCurRule[MAX_LINE];
	memset(sRulesUsed, 0, MAX_LINE*sizeof(char));   /*  Keep track of the rules used for debug  */
#endif
	
	/* Make a copy of the input word with a ' ' at the beginning and end */
	iWordInLen = (int)FNX_STRLEN( sWordIn );
	if( iWordInLen==0 )
		return 0;

	// Make sure that there is a leading and trailing space around the word
	if( *sWordIn != ' ' )
		FNX_STRCPY( sWord, " " );
	FNX_STRCAT( sWord, sWordIn );
	if( *(sWordIn + iWordInLen - 1) != ' ' )
		FNX_STRCAT( sWord, " " );
	
	/* Convert to lower case */
	for (pc=sWord; *pc; pc++)
		*pc = FNX_TOLOWER(*pc);
	
	/* Now look at each character in the word and see what rule matches it.
		For each match, advance 'iIndex' by the number of characters "consumed",
		and add a pointer to a string containing the pronunciation for those letters
		to pPronunList. */
	do
	{
		/* Set 'iRuleSet' to the index of which rule to use */
		if(( pc = FNX_STRCHR( pGraph2Phon->pRuleIndex, sWord[iIndex] )) != NULL)
		{
			iRuleSet = (int)((pc - pGraph2Phon->pRuleIndex));
		}
		else
		{
			iRuleSet = 0;
		}

		/* Look to see which rule within pGraph2Phon->ppPhoneticRules[iRuleSet] matches sWord[iIndex...],
		and add the resulting phonetic string to pPronunList. */
		iRuleNum = FindRule(sWord, &iIndex, pGraph2Phon, iRuleSet, sPron);
		
#ifdef DEBUG_GRAPH2PHON
		if(gppiRuleCount)                         /*  Keep track of the number of times each rule is used for debug  */
			gppiRuleCount[iRuleSet][iRuleNum]++;
		if(iRuleSet > 0)
		{
			FNX_SPRINTF(sCurRule, " %c[%ld] %s\0", pRuleIndex[iRuleSet-1], iRuleNum, (char *)pPronunList->p);
		}
		else
		{
			if(PhoneticRules[iRuleSet][iRuleNum][3] &&
				FNX_STRLEN(PhoneticRules[iRuleSet][iRuleNum][3]) > 0 &&
				FNX_STRCMP(PhoneticRules[iRuleSet][iRuleNum][3], " ") != 0 )
			{
				FNX_SPRINTF(sCurRule, " #[%ld] %s\0", iRuleNum, (char *)pPronunList->p);
			}
			else
			{
				*sCurRule = 0;
			}
		}
		
		FNX_STRCAT(sRulesUsed, sCurRule);
#endif

	} while ( *(sWord + iIndex) );
	
	/* Add "()" around pronunciation */
	//SurroundSymbols(&pPronunList, "(", ")", pGraph2Phon->pLinkPool);
	
	/* Convert linked list of symbols to a string */
	//SymbolsToString(pPronunList, pGraph2Phon->pLinkPool, sPron);
	
#ifdef DEBUG_GRAPH2PHON
	if( giShowRules == 1 )
	{
		char *sTemp = sPronunciation;
		sPronunciation = WeThreeStrings(sTemp, " | ", sRulesUsed);
		FNX_FREE(sPronunciation);
	}
	
	if( giShowRules == 2 )
	{
		char *sTemp = sPronunciation;
		sPronunciation = WeThreeStrings(sTemp, " | ", sRulesUsed);
		FNX_FREE(sPronunciation);
	}
#endif
	
	return 1;
} /* end: translate */


/*FUNCTION_HEADER**********************
   NAME:    ;HasDelimeter
   DESC:    Tell whether a string is a base phoneme stream (as opposed to a delimeter).
   IN:      s - String (e.g., "bc" or "|" or even "bc [bh]")
            bRight - Flag for whether to look at the last character instead of the first one.
   OUT:     n/a
   RETURN:  TRUE if s does not begin (or end, if bRight is set) with a character in "{}()[]|"
   NOTES:   Used to determine whether additional space need to be put after the symbol.
 *END_HEADER***************************/
BOOL HasDelimeter(char *s, BOOL bRight)
{
	char c;
#ifndef CASIO_SH3
	FNX_ASSERT(s && s[0]);
#endif
	if (bRight)
		c = s[FNX_STRLEN(s)-1];
	else c = s[0];
	if( FNX_STRCHR("{}()[]|", c) )
		return TRUE;
	else return FALSE;
}  /* HasDelimeter */


/*FUNCTION_HEADER**********************
 * NAME:    ;BSearch
 * DESC:    Use a binary search technique to find a string
            in the an array of strings.
 * IN:      psList      - array of strings
            iNumInList  - number of strings in array
            sKey        - string to find
 * OUT:     
 * RETURN:  -1 if not found, index of string if found
 * NOTES:   
 *END_HEADER***************************/
int BSearch(char **psList, int iNumInList, char *sKey)
{
   int   iFirst=0, 
         iMiddle, 
         iLast=iNumInList-1,
         iComp;    /* Result of comparison of middle with key  */

   if(psList == NULL || iNumInList==0)
      return -1;

   /* Use binary search to find an entry with sKey */
   do 
   {
      iMiddle = (iFirst + iLast)>>1;
      iComp = FNX_STRCMP(sKey, psList[iMiddle]);
      if (iComp<0)
         iLast = iMiddle;
      else if (iComp>0)
         iFirst = iMiddle;
   } while (iComp && iFirst < iLast-1);
   
   if (iComp == 0)
      return iMiddle;
   else if(FNX_STRCMP(sKey, psList[iFirst]) == 0 )
      return iFirst;
   else if(FNX_STRCMP(sKey, psList[iLast]) == 0 )
      return iLast;
   else
      return -1;

}  /*  BSearch  */

/* Macros for matching different kinds of characters */
#define IS_DIGIT(c)            FNX_STRCHR(pGraph2Phon->sNumbers,c)
#define IS_CONSONANT(c)        FNX_STRCHR(pGraph2Phon->sConsonants,c)
#define IS_VOWEL(c)            FNX_STRCHR(pGraph2Phon->sVowels,c)
#define IS_VOICED_CONSONANT(c) FNX_STRCHR(pGraph2Phon->sConsonants_v, c)
#define IS_FRONT_VOWEL(c)      FNX_STRCHR(pGraph2Phon->sVowels_f, c)

/* No longer supported:
  ~ = l, r
  * = b, c, d, f, g, k, m, n, p, s, t, v, x, z 
  ? = 2 or more of '*'
*/

/*FUNCTION_HEADER**********************
 * NAME:	;CatAllProns
 * DESC: 	Concatenate all possible pronunciations
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void CatAllProns(char *sPron, char *sPhonemes)
{
	if( sPron == NULL || sPhonemes == NULL )
		return;

	FNX_STRCAT(sPron, " ");
	FNX_STRCAT(sPron, sPhonemes);
}

/*FUNCTION_HEADER**********************
 * NAME:	;CatSinglePron
 * DESC: 	Concatenate a single pronunciation.
			Remove all optional bracketing.
			Only use the first possibility from an OR grouping.
 * IN:		sPhonemes
 * OUT:		sPron
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void CatSinglePron(char *sPron, char *sPhonemes)
{
	char
		*pcPron,
		*pcPhon;
	BOOL
		bOption=FALSE;
	int
		iOrState=0;
	
	if( sPron == NULL || sPhonemes == NULL )
		return;

	FNX_STRCAT(sPron, " ");			// Add a leading space
	pcPron = sPron + FNX_STRLEN(sPron);
	pcPhon = sPhonemes;

	while( pcPhon && *pcPhon != 0x00 )
	{
		if( *pcPhon == '[' )		// Don't copy optional brackets
			bOption = TRUE;
		else if( *pcPhon == ']' )
			bOption = FALSE;
		else if( *pcPhon == '(' )	// Start of a possible OR grouping
			iOrState = 1;			
		else if( *pcPhon == ')' )	// Reset the OR state
			iOrState = 0;
		else if( *pcPhon == '|' )	// Don't copy anything after the OR symbol until iOrState is reset
			iOrState = 2;
		else if( iOrState < 2 )
		{
			*pcPron = *pcPhon;
			pcPron++;
		}
		pcPhon++;
	}
	*pcPron = 0x00;
}

/*FUNCTION_HEADER**********************
 * NAME:    ;FindRule
 * DESC:    find the rule to apply
 * IN:      ppPronunList - Address of linked list of phonetic strings from matched rules.
            sWord   - Word to be processed
            piIndex  - Address of position in sWord[] to begin consuming letters.
            pGraph2Phon - Graph2Phon rules
            iRuleSet    - Index in pGraph2Phon->ppPhoneticRules[] of the set of rules to examine.
 * OUT:     *piIndex is advanced beyond any "consumed" characters.
            *ppPronunList has a pointer to the matched rule's phonetic string added to it.
 * RETURN:  Index of rule number within the given rule set (i.e., pGraph2Phon->ppPhoneticRules[iRuleSet][])
            that matched sWord[...iIndex...].
 * NOTES:   
 *END_HEADER***************************/
int FindRule(char sWord[], int *piIndex, Graph2PhonPtr pGraph2Phon, int iRuleSet, char *sPron)
{
	PhoneticRule   *pRule, *pRules;
	char           *sLeft, *sMatch, *sRight, *sOutput;
	int            iRemainder;
	BOOL           bPunctuation=(iRuleSet==0)?TRUE:FALSE;
	int            iRuleNum;
	
	pRules = &pGraph2Phon->pPhoneticRules[pGraph2Phon->piRuleIndex[iRuleSet]];
	
	for (iRuleNum=0; ; iRuleNum++ ) /* Search for the rule */
	{
		pRule = pRules++;
		sMatch = (*pRule)[1];
		
		/* See if we've hit the end of this rule set without finding a match */
		if ( sMatch == NULL || *sMatch == '\0')   /* bad symbol! */
		{
			/* Don't bother reporting an error if it is simply unhandled punctuation in the punctuation rule. */
#ifdef DEBUG_RULES
			if (!(bPunctuation && FNX_STRCHR(PUNCTUATION_LIST,sWord[*piIndex])))
				FNX_MESSAGE(FNX_STDERR, "Error: Can't find rule for: '%c' in \"%s\"\n", sWord[*piIndex], sWord );
#endif
			(*piIndex)++; // Skip it!
			return ( -1); // => no rule found
		}
		
		/* See if sWord[iIndex...] matches pRule[1] */
		for ( iRemainder = *piIndex; *sMatch != '\0'; sMatch++, iRemainder++ )
		{
			if ( *sMatch != sWord[iRemainder] )
				break;
		}
		if ( *sMatch != '\0' )  /* found missmatch */
			continue;
		
		/* sWord[iIndex..iRemainder] matched pRule[1][], so now see if the contexts also match */
		sLeft = (*pRule)[0];
		sRight = (*pRule)[2];
		
		if ( !LeftMatch(sLeft, sWord, *piIndex, pGraph2Phon) )
			continue;

		if ( !RightMatch(sRight, &sWord[iRemainder], pGraph2Phon))
			continue;
		
		sOutput = (*pRule)[3];
		
		if (sOutput && sOutput[0])
		{
			//CatSinglePron(sPron, sOutput);
			CatAllProns(sPron, sOutput);
		}
		
		*piIndex = iRemainder;
		
		return ( iRuleNum );
	}
} /* end: FindRule */

/*FUNCTION_HEADER**********************
 * NAME:    ;LeftMatch
 * DESC:    check the left context to see if it matches
 * IN:      sPattern - Character string describing what needs to match to the left of sWord[iIndex].
            sWord    - Word that matching is being done on.
            iIndex   - Current position in sWord[]
            pGraph2Phon - Graph2Phon rules.
 * OUT:     n/a
 * RETURN:  TRUE if 'sPattern' matches the characters to the left of sWord[iIndex]; FALSE otherwise.
 * NOTES:   
 *END_HEADER***************************/
int LeftMatch ( char *sPattern, char *sWord, int iIndex, Graph2PhonPtr pGraph2Phon)
{
   char  *pat;
   char  *text;
   int   count;

   if ( *sPattern == '\0' )   /* empty string matches any context */
      return 1;
   else if (iIndex<1)
      return 0; /* Empty context can't match anything except the empty string,
                   which was already checked for above */
   /* point to last character in pattern string */
   count = (int)FNX_STRLEN( sPattern );
   pat = sPattern + ( count - 1 );

   /* point to last character before current position in sWord */
   iIndex--;
   text = &sWord[iIndex];

   for ( ; count > 0 && iIndex>=0; pat--, count-- )
   {
      /* First check for simple text or space */
      if ( FNX_STRCHR(pGraph2Phon->sLetters, *pat ) || ( *pat == '\'') || ( *pat == ' ' ) || (*pat=='-'))
      {
         if (*pat == *text)// || (*pat==' ' && FNX_STRCHR(PUNCTUATION_LIST,*text)))
         {
            /* Either we matched, //or there was punctuation, which we'll let match with a ' ' */
            text--;
            iIndex--;
            continue;
         }
         else return(0);
      }

      switch ( *pat )
      {
         case '#':                              /* # (pound sign) one or more vowels */
            if ( !IS_VOWEL(*text) )
               return(0);

            text--;
            iIndex--;

            while ( IS_VOWEL ( *text ) )
            {
               text--;
               iIndex--;
            }
            break;

         case ':':                              /* : (colon) zero or more consonants */
            while ( IS_CONSONANT ( *text ) )
            {
               text--;
               iIndex--;
            }
            break;

         case '$':                              /*  $ (dollar sign) two or more consonants  */
            {
               int nConsonants=0;
               while( IS_CONSONANT(*text) )
               {
                  nConsonants++;
                  text--;
                  iIndex--;
               }
               if(nConsonants < 2)
                  return(0);
            }
            break;

         case '^':                              /* ^ (carrot) one consonant */
            if ( !IS_CONSONANT ( *text ) )
               return(0);
            text--;
            iIndex--;
            break;

         case '.':                              /* . (period) voiced consonant */
            if ( ! IS_VOICED_CONSONANT(*text) )
               return(0);
            text--;
            iIndex--;
            break;

         case '+':                              /* + (plus sign) front vowel */
            if( ! IS_FRONT_VOWEL(*text) )
               return(0);
            text--;
            iIndex--;
            break;

         case '=':                              /*  = (equal sign) one or more numbers  */
            while( IS_DIGIT(*text) )
            {
               text--;
               iIndex--;
            }
            break;

         case '%':
         default:
#ifdef DEBUG_RULES
            FNX_MESSAGE( FNX_STDERR, "Bad char in left rule: '%c'\n", *pat );
#endif
            return(0);
         }
   }
   return ( 1 );
}

/*FUNCTION_HEADER**********************
 * NAME:    ;RightMatch
 * DESC:    check the right context to see if it matches
 * IN:      sPattern - Graph2phon rule pattern to match
            sRemainder - Remaining part of word
            pGraph2Phon - Graph2Phon rules, including suffix list.
 * OUT:     
 * RETURN:  
 * NOTES:   
 *END_HEADER***************************/
int RightMatch ( char *sPattern, char *sRemainder, Graph2PhonPtr pGraph2Phon)
{
   char  *pat;
   char  *text;

   if ( *sPattern == '\0' )   /* null string matches any context */
      return ( 1 );

   text = sRemainder;

   for ( pat = sPattern; *pat != '\0'; pat++) 
   {
      /* First check for simple text or space */
      if ( FNX_STRCHR(pGraph2Phon->sLetters, *pat ) || ( *pat == '\'' ) || ( *pat == ' ' ) || (*pat=='-'))
      {
         if (*pat == *text)// || (*pat==' ' && FNX_STRCHR(PUNCTUATION_LIST,*text))) // if punctuation, allow ' ' to match.
         {
            text++;
            continue;
         }
         else return(0);
      }

      switch ( *pat )
      {
         case '#':                              /* # (pound sign) one or more vowels */
            if ( !IS_VOWEL(*text) )
               return(0);

            text++;

            while ( IS_VOWEL ( *text ) )
               text++;
            break;

         case ':':                              /* : (colon) zero or more consonants */
            while ( IS_CONSONANT ( *text ) )
               text++;
            break;

         case '$':                              /* $ (dollar sign) two or more consonants  */
            {
               int nConsonants=0;
               while( IS_CONSONANT(*text) )
               {
                  nConsonants++;
                  text++;
               }
               if(nConsonants < 2)
                  return(0);
            }
            break;

         case '^':                              /* ^ (carrot) one consonant */
            if ( !IS_CONSONANT(*text) )
               return(0);
            text++;
            break;

         case '.':                              /* . (period) voiced consonant */
            if ( ! IS_VOICED_CONSONANT(*text) )
               return(0);
            text++;
            break;

         case '+':                              /* + (plus sign) front vowel */
            if ( ! IS_FRONT_VOWEL(*text) )
               return(0);
            text++;
            break;

         case '=':                              /* = (equal sign) one or more numbers  */
            while( IS_DIGIT(*text) )
               text++;
            break;

         /* No longer supported:
           case '*': //one of: b, c, d, f, g, k, m, n, p, s, t, v, x, z 
           case '?': //one or more of '*' 
         */

         case '%':   /*  ends in a suffix  */
         {
            if( *(pat+1) == '>' )   /*  may be followed by a user suffix (compound suffix)  */
            {
               if( BSearch( pGraph2Phon->psEndingsList, pGraph2Phon->nEndingsList, text ) >= 0 )
               {
                  while( *text != ' ' ) text++;
                  break;
               }
               else
                  return(0);
            }
            else 
            {
               if( BSearch( pGraph2Phon->psEndingsList, pGraph2Phon->nEndingsList, text ) >= 0 )
               {
                  while( *text != ' ' ) text++;
                  break;
               }
               else
                  return(0);
            }
         }
         break;
         
         case '>':      /*  contains a user defined suffix  */
            if( BSearch(pGraph2Phon->psSuffixList, pGraph2Phon->nSuffixList, text) >= 0 )
            {
               while( *text != ' ' ) text++;
               break;
            }
            else
               return(0);

         default:
#ifdef DEBUG_RULES
            FNX_MESSAGE( FNX_STDERR, "Bad char in right rule:'%c'\n", *pat );
#endif
            return(0);
      }
   }
   return ( 1 );
}
