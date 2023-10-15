/*C_HEADER_FILE****************************************************************
FILE        :  Graph2Phon.c (formerly "phonetic.c")
DESC        :  Functions used to execute the grapheme-to-phoneme conversion 
TABS        :  3
OWNER       :  
DATE CREATED:  

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.


*END_HEADER*******************************************************************/

#include "FnxPlatform.h"   
#include "FnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxFiles.h"
#include "phonetic.h"
#include "dccread.h"
#include "FnxLlist.h"

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

int FindRule (llistPtr *ppPronunList, char sWord[], int *piIndex, Graph2PhonPtr pGraph2Phon, int iRuleSet);
int LeftMatch ( char *sPattern, char *sWord, int iIndex, Graph2PhonPtr pGraph2Phon);
int RightMatch ( char *sPattern, char *sRemainder, Graph2PhonPtr pGraph2Phon);

/*FUNCTION_HEADER**********************
 * NAME:    ;translate
 * DESC:    Convert a word into its phonetic pronunciation
 * IN:      pGraph2Phon - Graph2Phon rules.
            sWordIn - Word to convert to phonemes
 * OUT:     A string is allocated
 * RETURN:  Pointer to the newly-allocated pronunciation string (or NULL on error).
 * NOTES:   Includes surrounding parentheses (e.g., "(tc [th] u)").
 *END_HEADER***************************/
char *translate(Graph2PhonPtr pGraph2Phon, char *sWordIn)
{
   char  *pc, 
         *sWord = NULL, 
         *sPronunciation=NULL;
   int   iIndex = 0, /* Current position in word */
         iRuleSet,      /* First letter of match part */
         iRuleNum,/*  Which rule was used  */
         iWordInLen=0;  /* length of input word */
   llistPtr pPronunList=NULL;

   if (pGraph2Phon==NULL)
      return NULL; /* No graph2phon rules available */

#ifdef DEBUG_GRAPH2PHON
   char  sRulesUsed[MAX_LINE], 
         sCurRule[MAX_LINE];
         memset(sRulesUsed, 0, MAX_LINE*sizeof(char));   /*  Keep track of the rules used for debug  */
#endif

   /* Make a copy of the input word with a ' ' at the beginning and end */
   iWordInLen = FNX_STRLEN( sWordIn );
   if( iWordInLen==0 )
      return 0;
   sWord = (char *)FNX_CALLOC( (iWordInLen + 3), sizeof(char) ); // room for possible leading space, possible trailing space, and null
   if( *sWordIn != ' ' )
      FNX_STRCAT( sWord, " " );
   FNX_STRCAT( sWord, sWordIn );
   if( *(sWordIn + iWordInLen - 1) != ' ' )
      FNX_STRCAT( sWord, " " );
   
   /* Convert to lower case */
   for (pc=sWord; *pc; pc++)
      *pc = FNX_TOLOWER(*pc);

   /* Create a link pool to hold linked list of strings that make up new pronunciation */
   if (!pGraph2Phon->pLinkPool)
      pGraph2Phon->pLinkPool = NewLinkPool(20);

   /* Now look at each character in the word and see what rule matches it.
      For each match, advance 'iIndex' by the number of characters "consumed",
      and add a pointer to a string containing the pronunciation for those letters
      to pPronunList. */
   do
   {
      /* Set 'iRuleSet' to the index of which rule to use */
      if(( pc = FNX_STRCHR( pGraph2Phon->pRuleIndex, sWord[iIndex] )) != NULL)
      {
         iRuleSet = (pc - pGraph2Phon->pRuleIndex)+1; /* change for foreign language -- rule index based on position in "rule" string */
      }
      else
      {
         iRuleSet = 0;
      }
      /* Look to see which rule within pGraph2Phon->ppPhoneticRules[iRuleSet] matches sWord[iIndex...],
         and add the resulting phonetic string to pPronunList. */
      iRuleNum = FindRule ( &pPronunList, sWord, &iIndex, pGraph2Phon, iRuleSet);

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
   SurroundSymbols(&pPronunList, "(", ")", pGraph2Phon->pLinkPool);

   /* Convert linked list of symbols to a string */
   sPronunciation = SymbolsToString(pPronunList, pGraph2Phon->pLinkPool);

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

   FNX_FREE( sWord );

   return sPronunciation;
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
   FNX_ASSERT(s && s[0]);
   if (bRight)
      c = s[FNX_STRLEN(s)-1];
   else c = s[0];
   if (CharInString(c,"{}()[]|"))
      return TRUE;
   else return FALSE;
}  /* HasDelimeter */

/*FUNCTION_HEADER**********************
   NAME:    ;SurroundSymbols
   DESC:    Put a pair of symbols "around" a linked list.
   IN:      ppList - Address of pointer to linked list to be modified
            sLeft  - String to put on the "left" (i.e., at end) of ppList
            sRight - String to put on the "right" (i.e., at the beginning) of ppList
            pLinkPool - Link pool to use
   OUT:     *ppList has a link pointing to sRight inserted at the beginning, and a
            link to sLeft appended to the end.
   RETURN:  n/a
   NOTES:   *ppList is assumed to be in reverse order.  So calling SurroundSymbols(*pList,"[","]",pLinkPool)
            when pList->"c"->"b"->"a" => pList->"]"->"c"->"b"->"a"->"[",
            which seems silly until you draw it backwards:
            "["<-"a"<-"b"<-"c"<-"]".
 *END_HEADER***************************/
void SurroundSymbols(llistPtr *ppList, char *sLeft, char *sRight, LinkPoolPtr pLinkPool)
{
   AppendLink(sLeft, ppList, pLinkPool);
   InsertLink(sRight, ppList, pLinkPool);
}  /* SurroundSymbols */

/*FUNCTION_HEADER**********************
   NAME:    ;SymbolsToString
   DESC:    Convert a linked list of pronunciation symbols into a string.
   IN:      pSymbols - Linked list of pronunciation symbols (in reverse order).
            pLinkPool - Pool of links to use.
   OUT:     The links in pSymbols are freed up (or returned to pLinkPool),
              but the strings they point to are not.
   RETURN:  Pointer to a string containing the pronunciation.
   NOTES:   (e.g., "]" "c" "[" "b" "a" -> "a b[c]")
 *END_HEADER***************************/
char *SymbolsToString(llistPtr pSymbols, LinkPoolPtr pLinkPool)
{
   SDWORD  iNumSymbols, iSymbol, iLength;
   char  **psSymbols, *pc, *sPronunciation;

   /* Convert pSymbols into an array of strings */
   iNumSymbols = ListSize(pSymbols);
   psSymbols = ListToArray(&pSymbols, iNumSymbols, pLinkPool);
   /* Get the length of the a string with all elements concatenated */
   iLength=1; /* For null terminator */
   for (iSymbol=0; iSymbol<iNumSymbols; iSymbol++)
   {
      FNX_ASSERT(psSymbols[iSymbol] && psSymbols[iSymbol][0]);
      /* Add room for a ' ' if the previous symbol was not a delimeter,
         i.e., put spaces between basephones. */
      if (iSymbol>0 && !HasDelimeter(psSymbols[iSymbol-1],TRUE) && !HasDelimeter(psSymbols[iSymbol],FALSE))
         iLength++;
      iLength += FNX_STRLEN(psSymbols[iSymbol]);
   }

   sPronunciation = (char *)FNX_MALLOC(iLength*sizeof(char));
   pc = sPronunciation;
   for (iSymbol=0; iSymbol<iNumSymbols; iSymbol++)
   {
      if (iSymbol>0 && !HasDelimeter(psSymbols[iSymbol-1],TRUE) && !HasDelimeter(psSymbols[iSymbol],FALSE))
         *pc++ = ' ';
      FNX_STRCPY(pc, psSymbols[iSymbol]);
      pc+=FNX_STRLEN(psSymbols[iSymbol]);
   }
   *pc=0; /* Make sure it's null terminated */
   /* Free up psSymbols. (Don't free strings, because they all exist somewhere else) */
   FNX_FREE(psSymbols);

   return sPronunciation;
}  /* SymbolsToString */

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
int FindRule (llistPtr *ppPronunList, char sWord[], int *piIndex, Graph2PhonPtr pGraph2Phon, int iRuleSet)
{
   PhoneticRule   *pRule, *pRules;
   char           *sLeft, *sMatch, *sRight, *sOutput;
   int            iRemainder;
   BOOL           bPunctuation=(iRuleSet==0)?TRUE:FALSE;
   int            iRuleNum;

   pRules = pGraph2Phon->ppPhoneticRules[iRuleSet];
   
   for (iRuleNum=0; ; iRuleNum++ ) /* Search for the rule */
   {
      pRule = pRules++;
      sMatch = (*pRule)[1];

      /* See if we've hit the end of this rule set without finding a match */
      if ( sMatch == NULL || *sMatch == '\0')   /* bad symbol! */
      {
         /* Don't bother reporting an error if it is simply unhandled punctuation in the punctuation rule. */
         if (!(bPunctuation && FNX_STRCHR(PUNCTUATION_LIST,sWord[*piIndex])))
            Message (FNX_STDERR, "Error: Can't find rule for: '%c' in \"%s\"\n", sWord[*piIndex], sWord );
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
         InsertLink(sOutput, ppPronunList, pGraph2Phon->pLinkPool);
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
   count = FNX_STRLEN ( sPattern );
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
            Message ( FNX_STDERR, "Bad char in left rule: '%c'\n", *pat );
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
            Message ( FNX_STDERR, "Bad char in right rule:'%c'\n", *pat );
            return(0);
      }
   }
   return ( 1 );
}
