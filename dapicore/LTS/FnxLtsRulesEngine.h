/*H_HEADER_FILE***************************************************************
FILE			: FnxLtsRulesEngine.h
DESC			: 
TABS			: 4
OWNER			: 
DATE CREATED: 

(C) Copyright 22006 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER******************************************************************/
#ifndef	FNXLTSRULESENGINE_H
#define	FNXLTSRULESENGINE_H

#define NOTHING " "
#define ANYTHING ""
#define SILENT ""
#define PAUSE " "

typedef char *PhoneticRule[4]; /* PhoneticRule is an array of 4 character pointers */

typedef struct _GRAPH2PHON
{
   char  *pRuleIndex;		// String containing one letter for each rule set, except for the punctuation rule.
   char  *sLetters;			// List of valid (i.e., handled) letters for this language
   char  *sNumbers;			// List of digits this letter handles
   char  *sVowels;			// List of vowel characters for this language
   char  *sVowels_f;		// List of "front vowels" for this language
   char  *sConsonants;		// List of consonants for this language
   char  *sConsonants_v;	// List of voiced consonants for this language
   char  *sNasals;			// List of nasals for this language
   char **psEndingsList;	// Array of strings containing standard word endings for this languages
   int	nEndingsList;		// Number of elements in psEndingsList[]
   char **psOutputList;		// Array of strings containing valid phonemes for this language's current description file.
   int	nOutputList;		// Number of elements in psOutputList[]
   char **psSuffixList;		// Array of strings containing user-defined suffixes for this dictionary
   int	nSuffixList;		// Number of elements in psSuffixList[] (usually 0).
   int	*piRuleIndex;		// Index to rule start
   PhoneticRule *pPhoneticRules;	// Array[#RuleSets][#RulesInSet][4] of strings with rule definitions
} GRAPH2PHON, *Graph2PhonPtr;

/*FUNCTION_HEADER**********************
 * NAME:    ;translate
 * DESC:    Convert a word into its phonetic pronunciation
 * IN:      pGraph2Phon - Graph2Phon rules.
            sWordIn - Word to convert to phonemes
 * OUT:     A string is allocated
 * RETURN:  Pointer to the newly-allocated pronunciation string (or NULL on error).
 * NOTES:   Includes surrounding parentheses (e.g., "(tc [th] u)").
 *END_HEADER***************************/
extern int translate(Graph2PhonPtr pGraph2Phon, char *sWordIn, char *sPron);


#endif
