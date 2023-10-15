/*C_HEADER_FILE****************************************************************
FILE        :  LoadRules.c
DESC        :  Load the phonetic rules
TABS        :  3
OWNER       :  Brian Moncur
DATE CREATED   :  Dec 25, 1998

(C) Copyright 1998 All rights reserved.
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
#include "FnxByteOrderIO.h"
#include "FnxLlist.h" // FreePointerArray()
#include "FnxHuffman.h"
#include "FnxMisc.h"

/* Version history:
    0x20020403 - 04/03/2002: First version.  Always Huffman-encoded.
    0x20020521 - 05/21/2002: Include flag for whether Huffman-encoded, and wrote plain strings if not.
*/
#define G2P_VERSION 0x20020905 /* Sept. 5, 2002: STAGE1 "HEADER_INDEX" information included */
#pragma message (">> Compiling G2P Version 0x20020905")

/* Context definitions */
const char Anything[] = "";   /* No context requirement */
const char Nothing[] = " ";   /* Context is beginning or end of word */

/* Phoneme definitions */
const char Pause[] = " ";  /* Short silence */
const char Silent[] = "";  /* No phonemes */

#ifndef FNX_LEAN_AND_MEAN

/*FUNCTION_HEADER**********************
 * NAME:    ;compare
 * DESC:    compare two strings.  This function
            is used in qsort.
 *END_HEADER***************************/
#ifdef OS_WIN32
int __cdecl compare( const void *arg1, const void *arg2 )
#else
int compare( const void *arg1, const void *arg2 )
#endif
{
   /* Compare all of both strings: */
   return FNX_STRCMP( * ( char** ) arg1, * ( char** ) arg2 );
}  /*  compare  */

/*FUNCTION_HEADER**********************
 * NAME:   ;GetNextWord
 * DESC:   Get the next word in a string buffer.
 * IN:     sSource - String to parse
           sDest   - Destination string to put word into.
           pbQuoted - Address in which to return a flag indicating whether the returned string was quoted.
 * OUT:    sDest[] is filled with a word from sSource
 * RETURN: Pointer to the next character after the stuff put into sDest[]
 * NOTES:  Skips leading white space.
           If a '"' character is found, then all characters until
             the closing quote are read into sDest.
           Terminates sDest[] with a null character.
 *END_HEADER***************************/
char *GetNextWord(char *sSource, char *sDest, BOOL *pbQuoted)
{
   char  *pcSource = sSource,
         *pcDest = sDest;

   /* Skip leading white space */
   while( *pcSource && FNX_ISSPACE(*pcSource) )
      pcSource++;

   /* The string begins with a quote ("), so read until a closing quote. */
   if( *pcSource && *pcSource == '\"')
   {
      *pbQuoted = TRUE;
      pcSource++; /* skip quote */
      while(*pcSource && *pcSource != '\"') 
      {
         if (*pcSource=='\\')
            pcSource++; // a '\' character allows the next character (e.g., '"' or '\') to be "escaped".
         *(pcDest++) = *(pcSource++);
      }
      pcSource++; /* Skip ending '"' */
   }
   else /* Not quoted, so read until white space is encountered */
   {
      *pbQuoted = FALSE;
      while(*pcSource && !FNX_ISSPACE(*pcSource))
         *(pcDest++) = *(pcSource++);
   }
   *pcDest = '\0'; /* null terminate the returned string */

   /* Return a pointer to the next character after the last one read */
   return pcSource;
}  /* GetNextWord */

/*FUNCTION_HEADER************************************************
 * NAME:   ;NextChar
 * DESC:   Advance "pc" to the next character, reading another line if needed.
 * IN:     ppc - Address of "pc", a pointer to a character.
           sLine - Buffer into which pc points.
           iMaxSize - Allocated size of sLine
           fp - File to read another line from if needed.
           bSkipComments - Flag for whether to skip comments beginning with "#", "**" or "//".
 * OUT:    pc is advanced to the next character, unless that would put it
             at the end of the string, in which case another line is read.
 * RETURN: TRUE if the read is successful, FALSE if end-of-file is encountered.
 * NOTES:
 *END_HEADER*****************************************************/
BOOL NextChar(char **ppc, char *sLine, int iMaxSize, FILE *fp, BOOL bSkipComments)
{
   char *pc;
   BOOL bNewLine=FALSE;
   FNX_ASSERT(ppc);
   pc = *ppc;
   while(*pc==0 || *(pc+1)==0 || (bSkipComments && 
         (*pc=='#' || (*pc=='*' && *(pc+1)=='*') || (*pc=='/' && *(pc+1)=='/')) ))
   {
      /* Reached the end of string (or was already at it),
         so read the next line */
      if (!FNX_FGETS(sLine, iMaxSize, fp))
         return FALSE;
      Strip(sLine);
      pc = sLine;
      bNewLine=TRUE;
   }
   if (!bNewLine)
      pc++;
   *ppc = pc;
   return TRUE;
}  /* NextChar */

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadStrings
 * DESC:    Read a list of strings into a newly-allocated (and sorted) array. 
 * IN:      pc      - Pointer to the current position in sLine[] to begin parsing from.
            sLine   - Buffer that the source data is in (and into which further lines may be read)
            iMaxLen - Allocated size of sLine[]
            fp - File to read further lines from if necessary.
            piNumStrings - Address in which to return the number of strings in the returned list.
 * OUT:     *ppc is advanced, sLine may be overwritten by further data from fp,
              and an array of new strings is allocated.
            *piNumStrings gets the number of strings (or -1 on error).
 * RETURN:  Pointer to a newly-allocated array of strings containing the list of strings (or NULL if there were none).
 * NOTES:   Parses the list (delimited by white space) until a ';' is found.
            Newlines are acceptable, so the list may be spread across multiple lines.
 *END_HEADER***************************/
char **ReadStrings(char *pc, char *sLine, int iMaxLen, FILE *fp, SDWORDPTR piNumStrings)
{
   llistPtr pList=NULL;
   SDWORD iListSize, iLen;
   LinkPoolPtr pLinkPool=NULL; // just use NULL for now.
   char **psStrings=NULL;
   char *sCopy;

   if (fp==NULL || pc==NULL || piNumStrings==NULL)
   {
      if (piNumStrings)
         *piNumStrings = -1; // => error 
      return NULL;
   }

   /* Read strings until a ';' is found */
   while (*pc!=';')
   {
      // Skip whitespace
      while (*pc>=0 && *pc<=' ')
      {
         /* Parse a character, reading another line from fp into sLine if necessary */
         if (!NextChar(&pc, sLine, iMaxLen, fp, TRUE))
            goto Error;
      }
      if (*pc!=';')
      {
         // Count how many characters there are before whitespace or ';'
         for (iLen=0; pc[iLen]<0 || pc[iLen]>' ' && pc[iLen]!=';'; iLen++)
            ;
         // Make a copy of the substring
         sCopy = FNX_MALLOC(iLen+1);
         memcpy(sCopy,pc,iLen);
         sCopy[iLen]=0; // null terminate;
         InsertLink(sCopy, &pList, pLinkPool);
         // Advance pc beyond the word we just copied.
         pc += iLen;
      }  /* if not ';' */
   }  /* while not ';' */
   iListSize = ListSize(pList);
   if (iListSize>0)
   {
      psStrings = ListToArray(&pList, iListSize, pLinkPool);
      qsort(psStrings, iListSize, sizeof(char *), compare); 
   }

   /* Return the list and the new current character position */
   *piNumStrings = iListSize;
   return psStrings;

Error:
   FreeList(&pList, pLinkPool);
   if (piNumStrings)
      *piNumStrings = -1; /* => error */
   return NULL;
}  /* ReadStrings */

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadLetters
 * DESC:    Read a list of letters into a newly-allocated string. 
 * IN:      ppc - Address of a pointer to the current position in sLine[] to begin parsing from.
            sLine - Buffer that the source data is in (and into which further lines may be read)
            iMaxLen - Allocated size of sLine[]
            fp - File to read further lines from if necessary.
 * OUT:     *ppc is advanced, sLine may be overwritten by further data from fp,
              and a new string is allocated.
 * RETURN:  Pointer to a newly-allocated string containing the list of letters.
 * NOTES:   Parses the list (ignoring white space) until a ';' is found.
            For example, reading "a b 
               c ;" or "abc;" would both yield the string "abc".
            Newlines are acceptable, so the list may be spread across multiple lines.
 *END_HEADER***************************/
char *ReadLetters(char *pc, char *sLine, int iMaxLen, FILE *fp)
{
   char sChars[256];
   int iNumChars=0;
   
   while (*pc!=';')
   {
      /* Skip white space */
      while (*pc>=0 && *pc<=' ')
      {
         if (!NextChar(&pc, sLine, MAX_LINE, fp, TRUE))
            goto Error;
      }
      if (*pc!=';')
      {
         if (iNumChars>255) // Make sure we don't overflow sChars[256].
         {
            Message(NULL,"Error: too many characters in definition\n");
            goto Error;
         }
         sChars[iNumChars++] = *pc;
         pc++;
      }  // if not ';'
   }  // while not ';'
   sChars[iNumChars]=0; // null terminate

   /* Return a copy of the string containing the list of characters */
   return FNX_STRDUP(sChars);
Error:
   return NULL;
}  /* ReadLetters */

/*FUNCTION_HEADER**********************
 * NAME:    ;MatchHeaderLine
 * DESC:    See if a line begins with a given header string.
 * IN:      ppc - Address in which to return the pointer to the character just after "; sType:"
            sLine - Line to read from
            sType - Type (e.g., "vowel") to match
            piResult - Address in which to return 1 if ok, or 0 on error.
 * OUT:     *ppc points to the character just after the ":",
            and *piResult contains 1 if ok, or 0 on error,
            unless sType didn't match, in which case neither is changed.
 * RETURN:  TRUE if sLine matched, FALSE otherwise.
 * NOTES:   Looks for a line such as "; vowel:" to match "vowel".
            Can handle optional whitespace around sType, so
               ";vowel:", "; vowel:", ";vowel :", etc., would all match.
            Assumes that sLine begins with ";", so do "Strip(sLine)" before calling this routine.
 *END_HEADER***************************/
static BOOL MatchHeaderLine(char **ppc, char *sLine, char *sType, SDWORDPTR piResult)
{
   char *pc=sLine;
   
   /* Make sure input is not bogus */
   FNX_ASSERT(piResult);
   if (!sLine || !sType || !ppc || *pc!=';')
   {
      *piResult=0;
      return FALSE; // Error.
   }
   
   /* Skip the initial ";" and any [optional] white space after it. */
   pc++;
   while (*pc>0 && *pc<=' ')
      pc++; // skip white space
   
   /* See if the header now begins with the give sType */
   if (FNX_STRNICMP(pc, sType, FNX_STRLEN(sType))!=0)
   {
      *piResult=1; /* No error, just doesn't match */
      return FALSE; // Doesn't begin with ";sType"
   }
   pc += FNX_STRLEN(sType); // Advance beyond the matched sType.

   /* Make sure there's a ":" next [after optional white space, if any]*/
   while (*pc>0 && *pc<=' ')
      pc++; // skip white space
   if (*pc!=':')
   {
      *piResult=1;
      return FALSE; // Didn't match after all.
   }
   pc++; // skip ':'

   /* Return results */
   *ppc = pc;
   *piResult=1;
   return TRUE; // Matched, and no error.
}  /* MatchHeaderLine */

/*FUNCTION_HEADER************************************************
 * NAME:   ;GetLetters
 * DESC:   Parse header information from a Graph2Phon rules file.
 * IN:     sLine   - Buffer containing a line read from the Graph2Phon file.
           iMaxLen - Allocated size of sLine
           fp      - File sLine was read from
           sType   - Name of kind of letter to read, e.g., "vowel".
           psLetters-Address in which to return a pointer to a newly-allocated string containing the letters.
           piResult - Address in which to return the result code, i.e. 1=success, 0=error. (NULL=>don't bother).
 * OUT:    Global "hi" has data read into it.
           sLine may have further lines read into it from fp if the current
             line does not contain the terminating ";"
           *psLetters points to a newly-allocatged string, if sType matched.
           *piResult contains a 1 on success, 0 if there was an error.           
 * RETURN: 1 if sType matched the beginning of sLine (after the initial ';'), 0 otherwise.
 * NOTES:  Assumes the line begins with a ';'.
           Ignores white space after ';' before looking for "sType".
           Requires a ':' after "sType", e.g., if sType="vowel", then "; vowel:", or ";vowel :" would both match.
 *END_HEADER*****************************************************/
static BOOL GetLetters(char *sLine, SDWORD iMaxLen, FILE *fp, char *sType, char **psLetters, SDWORDPTR piResult)
{
   char *pc;
   FNX_ASSERT(piResult && psLetters);
   if (MatchHeaderLine(&pc, sLine, sType, piResult))
   {
      if (*piResult==1) // ok so far
      {
         *psLetters = ReadLetters(pc, sLine, iMaxLen, fp);
         if (*psLetters==NULL)
            *piResult=0; /* Error in reading the letters. */
      }
      return TRUE; // Matched (whether or not there was also an error involved).
   }
   else return FALSE; /* didn't match */
}  /* GetLetters */

/*FUNCTION_HEADER************************************************
 * NAME:   ;GetStrings
 * DESC:   See if a line begins with a given "; title:" and parse a list of strings if it does.
 * IN:     sLine        - Buffer containing a line read from the Graph2Phon file.
           iMaxLen      - Allocated size of sLine
           fp           - File sLine was read from
           sType        - Name of kind of letter to read, e.g., "vowel".
           ppsStrings   - Address in which to return a pointer to a newly-allocated array
                            of strings parsed from this (and possibly following) lines.
           piNumStrings - Address in which to return the number of strings read.
             piResult   - Address in which to return the result code, i.e. 1=success, 0=error.
 * OUT:    Global "hi" has data read into it.
           sLine may have further lines read into it from fp if the current
             line does not contain the terminating ";"
           *ppsStrings and *piNumStrings are filled with an array of strings.
           *piResult contains a 1 on success, 0 if there was an error.           
 * RETURN: 1 if sType matched the beginning of sLine (after the initial ';'), 0 otherwise.
 * NOTES:  Assumes the line begins with a ';'.
           Ignores white space after ';' before looking for "sType".
           Requires a ':' after "sType", e.g., if sType="suffixes", then "; suffixes:", or ";suffixes :" would both match.
 *END_HEADER*****************************************************/
static BOOL GetStrings(char *sLine, SDWORD iMaxLen, FILE *fp, char *sType, char ***ppsStrings, 
                       SDWORDPTR piNumStrings, SDWORDPTR piResult)
{
   char *pc;
   FNX_ASSERT(piResult && ppsStrings && piNumStrings);
   if (MatchHeaderLine(&pc, sLine, sType, piResult))
   {
      if (*piResult==1) // ok so far
      {
         *ppsStrings = ReadStrings(pc, sLine, iMaxLen, fp, piNumStrings);
         if (*piNumStrings<0)
            *piResult=0; // Error in reading the strings.
      }
      return TRUE; // Matched (whether or not there was also an error involved).
   }
   else return FALSE; /* Didn't match */
}  /* GetLetters */

/*FUNCTION_HEADER************************************************
 * NAME:    ;CheckForHeaderInformation
 * DESC:     Parse header information from a Graph2Phon rules file.
 * IN:       sLine   - Buffer containing a line read from the Graph2Phon file.
             iMaxLen - Allocated size of sLine
             pGraph2Phon - Graph2Phon rules structure.
             fp      - File sLine was read from
 * OUT:      Global "hi" has data read into it.
             sLine may have further lines read into it from fp if the current
               line does not contain the terminating ";"
 * RETURN:   1 on success, 0 on error (e.g., if no match was found).
 * NOTES:    It is considered an "error" to not match one of the strings,
               since otherwise a line shouldn't start with ';'.
 *END_HEADER*****************************************************/
int CheckForHeaderInformation( char *sLine, int iMaxLen, Graph2PhonPtr pGraph2Phon, FILE *fp )
{
   SDWORD iResult=0;
   /* The following tries matching each string to the beginning of sLine
      (with a ';' in front and a ':' after it), and when a match is found,
      a TRUE is returned, which cases the "||" to short-circuit and causes
      'iResult' to be returned.  In this case iResult=1 on success, and 0
      if there was an error. */
   if (GetLetters(sLine, iMaxLen, fp, "letters",      &pGraph2Phon->sLetters, &iResult) ||
       GetLetters(sLine, iMaxLen, fp, "numbers",      &pGraph2Phon->sNumbers, &iResult) ||
       GetLetters(sLine, iMaxLen, fp, "vowels",       &pGraph2Phon->sVowels, &iResult) ||
       GetLetters(sLine, iMaxLen, fp, "vowels_front", &pGraph2Phon->sVowels_f, &iResult) ||
       GetLetters(sLine, iMaxLen, fp, "consonants",   &pGraph2Phon->sConsonants, &iResult) ||
       GetLetters(sLine, iMaxLen, fp, "consonants_voiced", &pGraph2Phon->sConsonants_v, &iResult) ||
       GetLetters(sLine, iMaxLen, fp, "nasals",       &pGraph2Phon->sNasals, &iResult) ||
       GetStrings(sLine, iMaxLen, fp, "endings",      &pGraph2Phon->psEndingsList, &pGraph2Phon->nEndingsList, &iResult) ||
       GetStrings(sLine, iMaxLen, fp, "suffixes",     &pGraph2Phon->psSuffixList, &pGraph2Phon->nSuffixList, &iResult) ||
       GetStrings(sLine, iMaxLen, fp, "output",       &pGraph2Phon->psOutputList, &pGraph2Phon->nOutputList, &iResult))
       return iResult;
   else return 0; // didn't find one of the above.
}  /* CheckHeaderInformation */

/*FUNCTION_HEADER**********************
 * NAME:    ;WellParenthesized
 * DESC:    Make sure a pronunciation substring has parentheses when needed,
              and that parentheses match in any case.
 * IN:      sPronunciation - String to examine
 * OUT:     n/a
 * RETURN:  TRUE if ok, FALSE if there is a problem.
 * NOTES:   If a pronunciation has a disjunction ("or") in it (i.e., a "|"),
              then there MUST be parentheses around that part, or else
              the or will apply to everything to the left and right
              of what this pronunciation is concatenated with.
            For example, if the pronunciation for "5" is "f I-w n f | f I-w m f",
              as it was in the German.rules file, then the pronunciation for
              "55" would be "f I-w n f | f I-w m f f I-w n f | f I-w m f".
              This is wrong, since it allows these three pronunciations:
                f I-w n f
                f I-w m f f I-w n f
                f I-w m f
              instead of the desired four:
                f I-w n f f I-w n f 
                f I-w n f f I-w m f
                f I-w m f f I-w n f 
                f I-w m f f I-w m f
              as would be correctly generated by using parentheses:
                "(f I-w n f | f I-w m f)" or, better yet, "f I-w (n|m) f"
 *END_HEADER***************************/
BOOL WellParenthesized(char *sPronunciation)
{
   char *pc;
   SDWORD iParenDepth=0;

   for (pc=sPronunciation; *pc; pc++)
   {
      if (*pc==')')
      {
         iParenDepth--;
         if (iParenDepth<0)
            return FALSE; // A ')' before a matching '('
      }
      else if (*pc=='(')
         iParenDepth++;
      else if (*pc=='|' && iParenDepth<=0)
         return FALSE; // A '|' does not have parentheses around it.
   }
   if (iParenDepth!=0)
      return FALSE; // Mismatched set of parentheses.
   return TRUE; // All parentheses (if any) lined up.
}  /* WellParenethesized */

/*FUNCTION_HEADER**********************
 * NAME:    ;LoadRules
 * DESC:    Load phonetic rules from a file
 * IN:      sFile - rules filename
 * OUT:     A Graph2Phone structure and all of its fields are allocated.
 * RETURN:  Pointer to a newly-allocated Graph2Phon structure.
 * NOTES:   
 *END_HEADER***************************/
Graph2PhonPtr LoadRules(char *sFile)
{
   char  sLine[MAX_LINE],
         sWord[MAX_WORD],
         *pc;
   SDWORD   i, iRule = 0, iNumRuleSets = 0, iHeaderCount = 0;
   FILE *fp;
   PhoneticRule **ppPhoneticRules = NULL;
   llistPtr pRuleSetList=NULL; /* Linked list of rule sets */
   llistPtr pRuleList=NULL;    /* Linked list of rules in the current rule set */
   llistPtr pRuleNameList=NULL; /* Linked list of names of rules ("punctuation", "a", "b", etc.) */
   LinkPoolPtr pLinkPool=NULL;
   char **psRuleNames=NULL; /* Array of 32-bit values that are really characters typecast as pointers */
   PhoneticRule *pRule;
   SDWORD iRuleSet;
   PhoneticRule *pRules;
   Graph2PhonPtr pGraph2Phon;

   if( (fp = FNX_FOPEN(sFile, "r")) == NULL )
   {
      Message(FNX_STDERR, "Can't open file %s\n", sFile);
      return NULL;
   }
#ifdef DEBUG_GRAPH2PHON
//   giShowRules = 1;
#endif

   pGraph2Phon = (Graph2PhonPtr)FNX_CALLOC(1,sizeof(GRAPH2PHON));
   pLinkPool = NewLinkPool(20);

   /* Read each line in the file */
   while( FNX_FGETS(sLine, MAX_LINE, fp) )
   {
      /* Remove any leading and trailing white space */
      Strip(sLine);

      //memset(PR, 0, sizeof(PhoneticRule));
      //ppPhoneticRules = (PhoneticRule **)FNX_CALLOC( iNumRuleSets+1, sizeof(PhoneticRule *));
      //*ppRuleIndex = (char *)FNX_CALLOC( iNumRuleSets+1, sizeof(char) );

      if(  (sLine[0] == '*' && sLine[1] == '*')  /* Comment beginning with '**' */
         ||(sLine[0] == '/' && sLine[1] == '/')  /* comment beginning with '//' */
         || sLine[0] == 0)                       /* Blank line */
         continue;

      /* load header information (vowels, consonants, etc.) before moving on to rule section */
      /* verify header information (accounted for and formatted correctly) */
      if( *sLine == ';' && CheckForHeaderInformation( sLine, MAX_LINE, pGraph2Phon, fp ) )
      {
         iHeaderCount++;
         continue;
      }

      /* exit if header information missing */
      if( iHeaderCount < HEADER_COUNT )
      {
         Message(FNX_STDERR,"Error: Header of Graph2Phon file '%s' is not complete or incorrect\n", sFile);
         goto LoadRulesErr;
      }

      /* See if the line begins with "Rule:" */
      if( BeginsWithI(sLine, "Rule:")) //  here comes a new rule set
      {
         if (pRuleList)
         {
            /* We have come to a new rule, so the previous rule set is now complete. */
            /* So insert the current rule list into the RuleSetList, and set it to NULL */
            InsertLink(pRuleList, &pRuleSetList, pLinkPool);
            pRuleList = NULL;
         }

         FNX_SSCANF(sLine, "Rule: %s", sWord);
         if( FNX_STRCMP(sWord, "punctuation") == 0 )
         {
            /* 'punctuation' must be the very first rule! */
            if (pRuleSetList!=NULL)
            {
               Message(FNX_STDERR,"Error: First rule set was not 'punctuation'\n");
               goto LoadRulesErr;
            }
         }
         else
         {
            if (sWord[0]==0 || sWord[1]!=0)
            {
               Message(FNX_STDERR,"Error: Rule name is the wrong length in '%s'\n", sLine);
               goto LoadRulesErr;
            }
            /* Insert the single character into the linked list (typecast as a void *) */
            InsertLink((void *)((SDWORD)sWord[0]), &pRuleNameList, pLinkPool);
         }
      }
      else /* Read four strings into a new rule */
      {
         BOOL bIsQuoted;
         pRule = (PhoneticRule *)FNX_CALLOC(1, sizeof(PhoneticRule));
         pc = sLine;
         for(i = 0; i < 4; i++ )
         {
            if (*pc==0x00)
            {
               Message(FNX_STDERR,"Error: Not four strings in Graph2Phon rule:\n  %s\n", sLine);
               goto LoadRulesErr;
            }
            pc = GetNextWord(pc, sWord, &bIsQuoted);
            
            /* A single '0' (i.e., the digit zero, not the null character)
               without quotes is apparently interpreted as an empty string.
               So if the string is "0" and there was no quote, then
               replace this with the empty string. */
            if (FNX_STRCMP(sWord,"0")==0 && !bIsQuoted)
               sWord[0]=0x00;
            
            if((i==0 || i==2) && FNX_STRICMP(sWord, "Anything") == 0 )
               FNX_STRCPY(sWord, Anything);
            else if((i==0 || i==2) && FNX_STRICMP(sWord, "Nothing") == 0 )
               FNX_STRCPY(sWord, Nothing);
            else if(i==3 && FNX_STRICMP(sWord, "Silent") == 0 )
               FNX_STRCPY(sWord, Silent);
            else if(i==3 && FNX_STRICMP(sWord, "Pause") == 0 )
               FNX_STRCPY(sWord, Pause);
            else if (!bIsQuoted)
               Message(NULL,"Warning: Unquoted symbols in field %d of 4 in rule:\n  %s\n", i, sLine);
            if (i==3 && !WellParenthesized(sWord))
            {
               Message(NULL,"Error in Rule:\n  %s\nAny '|' in a pronunciation MUST have '(' and ')' around it!!\n", sLine);
               // We COULD do 
               //     (*pRule)[i]=WeThreeStrings("(",sWord,")"); 
               // and save their bacon, but let's make them fix it instead, to be sure it's right.
               goto LoadRulesErr;
            }
            (*pRule)[i] = FNX_STRDUP(sWord);
         }  /* for i */
         InsertLink(pRule, &pRuleList, pLinkPool);
      }  /* else rule */
   }  /* while there are lines to read */

   if (pRuleList)
   {
      /* Insert the last rule list into the RuleSetList */
      InsertLink(pRuleList, &pRuleSetList, pLinkPool);
   }

   /* Convert the linked list of rule sets (each of which is a linked list of phonetic rules)
      to a two-dimensinal array of phonetic rules. */
   /* First count the rules and create an array of pointers to the rule lists */
   iNumRuleSets = ListSize(pRuleSetList);

   /* Insert a NULL onto the end of the rule set list to signal the end of the list */
   InsertLink(NULL, &pRuleSetList, pLinkPool);

   ppPhoneticRules = (PhoneticRule **)ListToArray(&pRuleSetList, iNumRuleSets+1, pLinkPool);

   /* Then convert each rule list into an array of rules */
   for (iRuleSet=iNumRuleSets-1; iRuleSet>=0; iRuleSet--)
   {
      pRuleList = (llistPtr) ppPhoneticRules[iRuleSet];
      
      /* Count how many rules there were in this rule set */
      i = ListSize(pRuleList);

      /* Allocate that many rules plus an empty (all NULL) one at the end */
      pRules = (PhoneticRule *)FNX_CALLOC(i+1, sizeof(PhoneticRule));

      /* Copy the pointers from each rule on the linked list to the array we just allocated */
      while (pRuleList)
      {
         FNX_ASSERT(i>0);
         pRule = (PhoneticRule *)pRuleList->p;
         
         /* Move the pointers inside of pRule over to the array of rules */
         memcpy(&pRules[--i], pRule, 4 * sizeof(char *));
         
         /* Free up the little array of four pointers, since we have copied the pointers. */
         FNX_FREE(pRule);

         /* Free up the linked list element and move on to the next one */
         RemoveLink(&pRuleList, pLinkPool);
      }  /* while pRuleList */
      FNX_ASSERT(i == 0);

      ppPhoneticRules[iRuleSet] = pRules;
   }  /* for iRuleSet */

   /* Convert the linked list of rule names into a single string
      containing one character for each rule (except the first one,
      i.e., "punctuation") */
   if (iNumRuleSets>1)
   {
      pGraph2Phon->pRuleIndex = FNX_MALLOC(iNumRuleSets); /* +1 for null terminator, but -1 because punctuation is not in the list */
      FNX_ASSERT(ListSize(pRuleNameList) == iNumRuleSets-1);
      psRuleNames = ListToArray(&pRuleNameList, iNumRuleSets-1, pLinkPool);
      for (iRule=0; iRule<iNumRuleSets-1; iRule++)
      {
         /* Cast the pointer as 32-bit integer, and then as a character */
         pGraph2Phon->pRuleIndex[iRule] = (char)((SDWORD)psRuleNames[iRule]);
      }
      pGraph2Phon->pRuleIndex[iRule] = 0x00; /* Null terminate the rule index string */
      FNX_FREE(psRuleNames);
   }
   else pGraph2Phon->pRuleIndex = FNX_STRDUP(""); /* Empty but non-null string */
   
   FNX_FCLOSE( fp );

   pGraph2Phon->ppPhoneticRules = ppPhoneticRules;

   /* pLinkPool has probably grown larger than it will need to be for
      normal Graph2Phon use, so free it up and create a new one for
      Graph2Phon to use in building pronunciations */
   FreeLinkPool(pLinkPool);
   pGraph2Phon->pLinkPool = NewLinkPool(20);
   return pGraph2Phon;

LoadRulesErr:
   if (fp)
      FNX_FCLOSE(fp);
   while (pRuleList)
   {
      FreePointerArray((char **)&(pRuleList->p), 4);
      RemoveLink(&pRuleList, pLinkPool);
   }
   while (pRuleSetList)
   {
      pRuleList = (llistPtr)pRuleSetList->p;
      while (pRuleList)
      {
         FreePointerArray((char **)&(pRuleList->p), 4);
         RemoveLink(&pRuleList, pLinkPool);
      }
      RemoveLink(&pRuleSetList, pLinkPool);
   }
   if (pRuleNameList)
      FreeList(&pRuleNameList, pLinkPool);
   FreeLinkPool(pLinkPool);
   FreeRules(pGraph2Phon);

   return NULL;
}  /* LoadRules */

#if 0 // Not really needed under STAGE1 graph2phon, but could be needed
      // if there are really user suffixes being added in.
/*FUNCTION_HEADER**********************
 * NAME:   ;LoadSuffixFile
 * DESC:   Read a list of suffixes from a file. 
 * IN:     sSuffixFile - File to read from.
           ppsSuffixList - Address in which to return an array of suffixes
 * OUT:    *ppsSuffixList points to a newly-allocated array of suffix strings.
 * RETURN:  Number of elements in the returned array.
 * NOTES:   
 *END_HEADER***************************/
int LoadSuffixFile(char *sSuffixFile, char ***ppsSuffixList)
{
   char  sLine[MAX_LINE];
   int   nSuffixList = 0;
   FILE *fp;
   llistPtr pSuffixList=NULL;

   fp = FNX_FOPEN(sSuffixFile, "r");
   if( fp )
   {
      nSuffixList=0;
      while(FNX_FGETS(sLine, MAX_LINE, fp))
      {
         Strip(sLine);
         if (sLine[0])
         {
            InsertLink(FNX_STRDUP(sLine), &pSuffixList, NULL);
            nSuffixList++;
         }
      }         

      FNX_ASSERT(nSuffixList==ListSize(pSuffixList));
      (*ppsSuffixList) = ListToArray(&pSuffixList, nSuffixList, NULL);
      
      FNX_FCLOSE(fp);

      qsort((*ppsSuffixList), nSuffixList, sizeof(char *), CaseCmpString);
   }

   return nSuffixList;

}  /*  LoadSuffixFile  */
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;WrapStringList
 * DESC:    Write a list of strings to a file, wrapping and indenting as necessary.
 * IN:      fp - File to write to
            psStrings - Array of strings to write
            iNumStrings - Number of strings in psStrings[]
            iMargin - Amount to indent each line (also, assumed starting position within first line)
            iLimit  - Number of characters to allow per line before starting a new line.
 * OUT:     Strings are written to fp, possibly on several lines.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
static void WrapStringList(FILE *fp, char **psStrings, SDWORD iNumStrings, SDWORD iMargin, SDWORD iLimit)
{
   SDWORD i;
   SDWORD iWidth=iMargin;
   for (i=0; i<iNumStrings; i++)
   {
      FNX_FPRINTF(fp," %s", psStrings[i]);
      iWidth += 1 + FNX_STRLEN(psStrings[i]);
      if (iWidth > iLimit)
      {
         FNX_FPRINTF(fp,"\n%*c", iMargin,' ');
         iWidth = iMargin;
      }
   }
}  /* WrapStringList */

/*FUNCTION_HEADER**********************
 * NAME:    ;WriteRules
 * DESC:    Write phonetic rules to one or two text files.
 * IN:      sRulesFile      - Name of .rules file to write rules to.
            sSuffixFile     - Name of file to write list of suffixes to.
            ppPhoneticRules - Array of phonetic rules to write.
            pRuleIndex      - A string of characters, where each character represents a rule set.
            psSuffixList    - Address in which to return an array of strings containing suffixes.
            nSuffixList     - Number of suffixes in psSuffixList[].
 * OUT:     *ppRuleIndex points to a string with a letter for each rule.
            *ppsSuffixList contains a list of suffixes (if there were any in the file, NULL otherwise).
            *piNumSuffix contains the number of elements in ppsSuffixList.
 * RETURN:  0 on success, -1 on error.
 * NOTES:   Any string in the rule list that has a space or tab in it is
              surrounded by double quotes (e.g., "bc [bh]") so that it will
              be treated as a single string.
            Empty strings are written as "", i.e., two double quotes in a row.
 *END_HEADER***************************/
#ifndef NO_SYSFILE_WRITES
SDWORD WriteRules(char *sRulesFile, Graph2PhonPtr pGraph2Phon)
{
   SDWORD iNumRuleSets; /* Number of elements in ppPhoneticRules (=strlen(pRuleIndex)+1). */
   SDWORD iRuleSet, iRule, i;
   char   *s;
   FILE   *fp;

   if (sRulesFile==NULL || pGraph2Phon==NULL)
      return -1;

   /*** Write rules */
   fp = FNX_FOPEN(sRulesFile, "wt");
   if (fp==NULL)
   {
      Message(NULL,"Error: Could not open rules file '%s' for writing\n", sRulesFile);
      return -1;
   }
   FNX_FPRINTF(fp, "** (C) Copyright 2003 Fonix Corporation. All rights reserved. **\n");

   iNumRuleSets = 1 /* for 'punctuation'*/ + FNX_STRLEN(pGraph2Phon->pRuleIndex);

   FNX_FPRINTF(fp,"\n; letters:");
   for (s=pGraph2Phon->sLetters; *s; s++)
      FNX_FPRINTF(fp," %c", *s);
   
   FNX_FPRINTF(fp,";\n; numbers:");
   for (s=pGraph2Phon->sNumbers; *s; s++)
      FNX_FPRINTF(fp," %c", *s);
   
   FNX_FPRINTF(fp,";\n; vowels:");
   for (s=pGraph2Phon->sVowels; *s; s++)
      FNX_FPRINTF(fp," %c", *s);
   
   FNX_FPRINTF(fp,";\n; vowels_front:");
   for (s=pGraph2Phon->sVowels_f; *s; s++)
      FNX_FPRINTF(fp," %c", *s);
   
   FNX_FPRINTF(fp,";\n; consonants:");
   for (s=pGraph2Phon->sConsonants; *s; s++)
      FNX_FPRINTF(fp," %c", *s);
   
   FNX_FPRINTF(fp,";\n; consonants_voiced:");
   for (s=pGraph2Phon->sConsonants_v; *s; s++)
      FNX_FPRINTF(fp," %c", *s);
   
   FNX_FPRINTF(fp,";\n; nasals:");
   for (s=pGraph2Phon->sNasals; *s; s++)
      FNX_FPRINTF(fp," %c", *s);
   
   FNX_FPRINTF(fp,";\n; endings:");
   WrapStringList(fp, pGraph2Phon->psEndingsList, pGraph2Phon->nEndingsList, FNX_STRLEN("; endings:"), 80);

   FNX_FPRINTF(fp,";\n; suffixes:");
   WrapStringList(fp, pGraph2Phon->psSuffixList, pGraph2Phon->nSuffixList, FNX_STRLEN("; suffixes:"), 80);

   FNX_FPRINTF(fp,";\n; output:");
   WrapStringList(fp, pGraph2Phon->psOutputList, pGraph2Phon->nOutputList, FNX_STRLEN("; output:"), 80);

   FNX_FPRINTF(fp,";\n\n");

   for (iRuleSet=0; iRuleSet < iNumRuleSets; iRuleSet++)
   {
      if (iRuleSet==0)
         fprintf(fp, "Rule: punctuation\n");
      else fprintf(fp, "Rule: %c\n", pGraph2Phon->pRuleIndex[iRuleSet-1]);

      for (iRule=0; pGraph2Phon->ppPhoneticRules[iRuleSet][iRule][0]!=NULL; iRule++)
      {
         fprintf(fp, "     ");
         for (i=0; i<4; i++)
         {
            s = pGraph2Phon->ppPhoneticRules[iRuleSet][iRule][i];
            if (i==3)
            {
               if (FNX_STRCMP(s, Pause)==0)
                  fprintf(fp,"Pause\n");
               else if (FNX_STRCMP(s, Silent)==0)
                  fprintf(fp,"Silent\n");
               else fprintf(fp,"\"%s\"\n",s);
            }
            else 
            {
               /* Output 'Nothing' instead of " " in first and third column. */
               if ((i==0 || i==2) && FNX_STRCMP(s, Nothing)==0)
                  fprintf(fp,"%-10s ", "Nothing");
               /* Output 'Anything' instead of "" in first and third column. */
               else if ((i==0 || i==2) && FNX_STRCMP(s, Anything)==0)
                  fprintf(fp,"%-10s ", "Anything");
               else // print a quoted string and then enough spaces to line up at the next column.
               {
                  char *pc;
                  SDWORD iLen;
                  fprintf(fp,"\""); // opening quotes
                  /* Print the characters in s, with any '\' or '"' characters escaped */
                  iLen=2; // for the opening and closing quotes.
                  for (pc=s; *pc; pc++)
                  {
                     if (*pc=='"' || *pc=='\\')
                        fprintf(fp,"\\"), iLen++;
                     fprintf(fp,"%c", *pc);
                     iLen++;
                  }
                  fprintf(fp,"\""); // closing quotes.
                  do // Print enough spaces to line columns up when convenient (but at least 1 space, and not more than 9).
                  {
                     fprintf(fp," ");
                  } while (iLen++ < 10);
               }  /* else regular string */
            }
         }  /* for i */
      }  /* for iRule */
   }  /* for iRuleSet */
   FNX_FCLOSE(fp);

   return 0;
}  /* WriteRules */
#endif // not NO_SYSFILE_WRITES

/* If you make any changes to the Graph2Phon binary format that affect
   how BinaryWriteRules or BinaryLoadRules operates, then you need to
   change the version and put if (new version) then {new way} else {do things the old way}. */

/*FUNCTION_HEADER**********************
 * NAME:    ;WriteBinaryRules
 * DESC:    Write phonetic rules to a binary file
 * IN:      fp - Opened file to write to (Must be opened in binary mode!)
            ppPhoneticRules - Array of phonetic rules to write.
            pRuleIndex      - A string of characters, where each character represents a rule set.
            psSuffixList    - Address in which to return an array of strings containing suffixes.
            nSuffixList     - Number of suffixes in psSuffixList[].
            bCompressRules  - Flag for whether to Huffman-encode the rules.
 * OUT:     *ppRuleIndex points to a string with a letter for each rule.
            *ppsSuffixList contains a list of suffixes (if there were any in the file, NULL otherwise).
            *piNumSuffix contains the number of elements in ppsSuffixList.
 * RETURN:  0 on success, -1 on error.
 * NOTES:   Writes rules out in the following format:
              "G2PB"         - 4 character string to make sure we're in the right place.
              <iVersion>     - 4-byte integer containing version date [see definition of G2P_VERSION]
              <iNumRuleSets> - 4-byte integer saying how many rule sets there are (including "punctuation")
              [pcRuleIndex]  - 1 character for each <iNumRuleSets>.
              For each rule set:
                <#Rules>
              <#Suffixes> - Number of suffixes
            At that point is a Huffman-encoded array of strings, where the order of the strings is:
              For each rule set:
                For each rule:
                  <string1> <string2> <string3> <string4>
              For each suffix:
                <string>
            If STAGE1 (i.e., version 2002.09.05):
                 <sLetters> - String containing a list of letters supported by the language 
                               (NBO length followed by characters)
                 <sNumbers> - List of digits
                 <sVowels>  - List of vowels
                 <sVowels_f>- List of front vowels
                 <sConsonants> - List of consonants
                 <sConsonants_v> - List of voiced consonants
                 <sNasals>       - List of nasals
                 <psEndingsList> - Array of strings containing standard suffixes for the language
                                    (NBO #strings, followed by that many <string>'s)
                 <psOutputList>  - Array of phoneme names for this language.
            And finally:
              "ENDG2P" - 6-character string to let us know we got to the end successfully.
            Use BinaryReadRules() to read this stuff back in.
 *END_HEADER***************************/
#ifndef NO_SYSFILE_WRITES
SDWORD WriteBinaryRules(FILE *fp, Graph2PhonPtr pGraph2Phon, BOOL bCompressRules)
{
   char **psStrings; /* Array of strings with pointers to all 4 strings of each rule for each rule set,
                        and then all of the suffix strings (if any) */
   SDWORD iNumStrings; /* Number of strings in psStrings */
   SDWORD iNumRuleSets; /* Number of elements in ppPhoneticRules (=strlen(pRuleIndex)+1). */
   SDWORD iError=0;
   SDWORD iRuleSet, iRule, i;

   if (fp==NULL || pGraph2Phon==NULL || pGraph2Phon->ppPhoneticRules==NULL || pGraph2Phon->pRuleIndex==NULL)
      return -1;

   iNumRuleSets = 1 /* for 'punctuation'*/ + FNX_STRLEN(pGraph2Phon->pRuleIndex);

   iError  = (FNX_FWRITE("G2PB", 4, 1, fp) == 4);
   iError |= WriteInt32NBO(fp, G2P_VERSION);
   iError |= WriteInt32NBO(fp, iNumRuleSets);
   iError |= WriteString(fp, pGraph2Phon->pRuleIndex);

   /* Count how many strings will be written, 
      and write the number of rules in each rule set. */
   iNumStrings=0;
   for (iRuleSet=0; iRuleSet < iNumRuleSets; iRuleSet++)
   {
      for (iRule=0; pGraph2Phon->ppPhoneticRules[iRuleSet][iRule][0]!=NULL; iRule++)
         iNumStrings+=4;
      /* Write the number of rules for this rule set */
      iError |= WriteInt32NBO(fp, iRule);
   }  /* for iRuleSet */
   iError |= WriteInt32NBO(fp, pGraph2Phon->nSuffixList);
   iNumStrings += pGraph2Phon->nSuffixList;

   /* Create an array of string pointers to point at
      all of the strings in all of the rules in all of the
      rule sets, plus all of the suffixes. */
   psStrings = (char **)FNX_CALLOC(iNumStrings, sizeof(char *));
   iNumStrings=0;
   for (iRuleSet=0; iRuleSet < iNumRuleSets; iRuleSet++)
   {
      for (iRule=0; pGraph2Phon->ppPhoneticRules[iRuleSet][iRule][0]!=NULL; iRule++)
      {
         for (i=0; i<4; i++)
            psStrings[iNumStrings++] = pGraph2Phon->ppPhoneticRules[iRuleSet][iRule][i];
      }
   }  /* for iRuleSet */
   for (i=0; i < pGraph2Phon->nSuffixList; i++)
      psStrings[iNumStrings++] = pGraph2Phon->psSuffixList[i];

   /* Write the list of strings (Huffman-encoded or not, depending on bCompressRules) */
   iError |= (FNX_FPUTC((int)bCompressRules, fp) != (int)bCompressRules);
   if (bCompressRules)
      iError |= WriteEncodedStringList(fp, psStrings, iNumStrings);
   else iError |= WriteStringList(fp, psStrings, iNumStrings);
   
   FNX_FREE(psStrings);

   /* Write Graph2Phon definitions */
   iError |= WriteString(fp, pGraph2Phon->sLetters);
   iError |= WriteString(fp, pGraph2Phon->sNumbers);
   iError |= WriteString(fp, pGraph2Phon->sVowels);
   iError |= WriteString(fp, pGraph2Phon->sVowels_f);
   iError |= WriteString(fp, pGraph2Phon->sConsonants);
   iError |= WriteString(fp, pGraph2Phon->sConsonants_v);
   iError |= WriteString(fp, pGraph2Phon->sNasals);
   iError |= WriteStringList(fp, pGraph2Phon->psEndingsList, pGraph2Phon->nEndingsList);
   iError |= WriteStringList(fp, pGraph2Phon->psOutputList, pGraph2Phon->nOutputList);

   /* Write "ENDG2P" to the file so we'll be able to make sure we got to the end properly. */
   iError |= (FNX_FWRITE("ENDG2P",6,1,fp)==6);

   return iError;
}  /* WriteBinaryRules */
#endif   //  NO_SYSFILE_WRITES

#endif   //  FNX_LEAN_AND_MEAN

/*FUNCTION_HEADER**********************
 * NAME:    ;FreeRules
 * DESC:    Free up phonetic rule memory
 * IN:      pGraph2Phon - Graph2Phon structure to free up.
 * OUT:     pGraph2Phon and its fields are freed up.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
void FreeRules( Graph2PhonPtr pGraph2Phon)
{
   SDWORD iRuleSet, iRule, iField;
   PhoneticRule *pRuleSet;
   char *sWord;

   if (pGraph2Phon)
   {
      if( pGraph2Phon->ppPhoneticRules )
      {
         for (iRuleSet=0; pGraph2Phon->ppPhoneticRules[iRuleSet]; iRuleSet++)
         {
            pRuleSet = pGraph2Phon->ppPhoneticRules[iRuleSet];
            for (iRule=0; pRuleSet[iRule][0]; iRule++)
            {
               for( iField = 0; iField < 4; iField++ )
               {
                  sWord = pRuleSet[iRule][iField];
                  if( sWord )
                  {
                     FNX_FREE( sWord );
                  }
                  else
                  { 
                     break;
                  }
               }
            }
            FNX_FREE( pRuleSet );
         }  /* for each rule set */
         FNX_FREE(pGraph2Phon->ppPhoneticRules);
      }
      if( pGraph2Phon->pRuleIndex )
      {
         FNX_FREE( pGraph2Phon->pRuleIndex );
      }
      FreeAndClear((voidPtr *)&pGraph2Phon->sLetters);
      FreeAndClear((voidPtr *)&pGraph2Phon->sNumbers);
      FreeAndClear((voidPtr *)&pGraph2Phon->sVowels);
      FreeAndClear((voidPtr *)&pGraph2Phon->sVowels_f);
      FreeAndClear((voidPtr *)&pGraph2Phon->sConsonants);
      FreeAndClear((voidPtr *)&pGraph2Phon->sConsonants_v);
      FreeAndClear((voidPtr *)&pGraph2Phon->sNasals);
      FreePointerArray(pGraph2Phon->psOutputList, pGraph2Phon->nOutputList);
      FreePointerArray(pGraph2Phon->psEndingsList, pGraph2Phon->nEndingsList);
      FreePointerArray(pGraph2Phon->psSuffixList, pGraph2Phon->nSuffixList);
      if (pGraph2Phon->pLinkPool)
         FreePool(pGraph2Phon->pLinkPool);
      FNX_FREE(pGraph2Phon);
   }
}  /* FreeRules */


/*FUNCTION_HEADER**********************
 * NAME:    ;LoadBinaryRules
 * DESC:    Load phonetic rules from a binary file
 * IN:      fp - Opened file pointer positioned where the Graph2Phon rules begin.
            ppRuleIndex   - Address in which to return a string of characters, 
                            where each character represents a rule set.
            ppsSuffixList - Address in which to return an array of strings containing suffixes.
            pnSuffixList  - Address in which to return the number of suffixes in psSuffixList[].
 * OUT:     *ppRuleIndex points to a string with a letter for each rule.
            *ppsSuffixList contains a list of suffixes (if there were any in the file, NULL otherwise).
            *piNumSuffix contains the number of elements in ppsSuffixList.
 * RETURN:  Pointer to array of phonetic rule sets
 * NOTES:   
 *END_HEADER***************************/
Graph2PhonPtr LoadBinaryRules(FILE *fp)
{
   char **psStrings; /* Array of strings with pointers to all 4 strings of each rule for each rule set,
                        and then all of the suffix strings (if any) */
   SDWORD iNumStrings; /* Number of strings in psStrings */
   SDWORD iNumRuleSets; /* Number of elements in ppPhoneticRules (=strlen(pRuleIndex)+1). */
   SDWORD iRuleSet, iRule, i;
   SDWORD iNumReadStrings;  /* Total number of strings read from Huffman encoding. */
   SDWORD iError=0, iVersion;
   SDWORDPTR piNumRules;
   char   sBuf[10];
   BOOL   bCompressRules;
   Graph2PhonPtr pGraph2Phon=NULL;

   if (fp==NULL)
      return NULL;

   /* Read "G2PB" and make sure that is what is in the first four bytes */
   iError  = (FNX_FREAD(sBuf, 1, 4, fp) != 4);
   sBuf[4]=0;
   if (FNX_STRCMP(sBuf,"G2PB")!=0)
   {
      Message(FNX_STDERR,"Error: Binary Graph2Phon segment does not begin with 'G2PB'\n");
      return NULL;
   }

   /* Read the version number and make sure it is ok */
   iError |= ReadInt32NBO(fp, (UDWORD *)&iVersion);

   /* Allocate an empty Graph2Phon structure */
   pGraph2Phon = FNX_CALLOC(1, sizeof(GRAPH2PHON));

   if (iVersion == 0x20020521 || iVersion == 0x20020403)
   {
      /* Old Graph2Phon version, so load the HEADER_INDEX structure with the old defaults. */
      pGraph2Phon->sLetters      = FNX_STRDUP("abcdefghijklmnopqrstuvwxyzåäáàêèëéîïìíîôöóúùüûœçñÿ");
      //pGraph2Phon->sLetters      = FNX_STRDUP("aäÄåÅâáàbßcçÇdeêéÉèëfghiîïìjklmnñÑoöÖœôóòpqrstuüÜûùúvwxyÿzapostraphyhyphen");
      pGraph2Phon->sVowels       = FNX_STRDUP("aeiouåäáàêèëéîïìÍíîôöóúùüûœ");
      pGraph2Phon->sVowels_f     = FNX_STRDUP("eiyíé");
      pGraph2Phon->sConsonants_v = FNX_STRDUP("bdvgjlmnrwz");
      pGraph2Phon->sConsonants   = FNX_STRDUP("bcdfghjklmnpqrstvwxyzçñ");
      //pGraph2Phon->sNumbers      = FNX_STRDUP("01234567689");
      pGraph2Phon->sNumbers      = FNX_STRDUP("01234567689");
      pGraph2Phon->sNasals       = FNX_STRDUP("nmñ");
      pGraph2Phon->psEndingsList = SplitString("e er es ed ing ely ers ings ingly edly ness edness nesses e's ed's er's es's ely's ing's er' ers' e' es' ed' ely' ing'",
                                     &pGraph2Phon->nEndingsList);
   }
   else if (iVersion != 0x20020905)
   {
      Message(FNX_STDERR,"Error: Unsupported version number '%08x' in binary Graph2Phon segment\n");
      return NULL;
   }

   /* Read the number of rule sets and the letter for each one (except the first) */
   iError |= ReadInt32NBO(fp, (UDWORD *)&iNumRuleSets);
   iError |= ReadString(fp, &pGraph2Phon->pRuleIndex);

   /* See how many rules there are for each rule set,
      and allocate enough pointers to hold them. */
   iNumStrings=0;
   piNumRules = (SDWORDPTR)FNX_MALLOC(iNumRuleSets * sizeof(SDWORD));
   for (iRuleSet=0; iRuleSet < iNumRuleSets; iRuleSet++)
   {
      /* Read the number of rules for this rule set */
      iError |= ReadInt32NBO(fp, (UDWORD *)&(piNumRules[iRuleSet]));
      iNumStrings += piNumRules[iRuleSet]*4;
   }  /* for iRuleSet */

   /* See how many suffixes there are, and allocate room for it */
   iError |= ReadInt32NBO(fp, (UDWORD *)&pGraph2Phon->nSuffixList);
   iNumStrings += pGraph2Phon->nSuffixList;

   /* The original version (2002.04.03) always did Huffman-encoding.
      Later versions (2002.05.21 and later) include a byte indicating
      whether or not the string list is Huffman-encoded. */
   if (iVersion == 0x20020403)
      bCompressRules = 1;
   else bCompressRules = FNX_FGETC(fp);

   if (bCompressRules)
      /* Read the list of huffman-encoded strings from the file */
      psStrings = ReadEncodedStringList(fp, &iNumReadStrings);
   else iError |= ReadStringList(fp, &psStrings, &iNumReadStrings);
   if (iNumStrings != iNumReadStrings)
   {
      Message(FNX_STDERR,"Error: Binary Graph2Phon segment said there would be %d strings, but only %d were decoded\n",
              iNumStrings, iNumReadStrings);
      FreePointerArray(psStrings, iNumReadStrings);
      FNX_FREE(piNumRules);
      return NULL;
   }

   /* Allocate main array of rule sets (allocate one additional "NULL" one to indicate end-of-list) */
   pGraph2Phon->ppPhoneticRules = (PhoneticRule **)FNX_CALLOC(iNumRuleSets+1, sizeof(PhoneticRule *)); 

   /* Allocate room for string pointers and move the strings over */
   iNumStrings=0;
   for (iRuleSet=0; iRuleSet < iNumRuleSets; iRuleSet++)
   {
      /* Allocate rules (plus one NULL one at the end to indicate the end of the list) */
      pGraph2Phon->ppPhoneticRules[iRuleSet] = (PhoneticRule *)FNX_CALLOC(piNumRules[iRuleSet]+1,sizeof(PhoneticRule));
      for (iRule=0; iRule < piNumRules[iRuleSet]; iRule++)
      {
         for (i=0; i<4; i++)
            pGraph2Phon->ppPhoneticRules[iRuleSet][iRule][i] = psStrings[iNumStrings++];
      }
   }  /* for iRuleSet */

   pGraph2Phon->psSuffixList = (char **)FNX_CALLOC(pGraph2Phon->nSuffixList, sizeof(char *));
   for (i=0; i < pGraph2Phon->nSuffixList; i++)
      pGraph2Phon->psSuffixList[i] = psStrings[iNumStrings++];
   
   FNX_ASSERT(iNumStrings == iNumReadStrings);

   if (iVersion>=0x20020905)
   {
      /* Read HEADER_INDEX stuff */
      iError |= ReadString(fp, &pGraph2Phon->sLetters);
      iError |= ReadString(fp, &pGraph2Phon->sNumbers);
      iError |= ReadString(fp, &pGraph2Phon->sVowels);
      iError |= ReadString(fp, &pGraph2Phon->sVowels_f);
      iError |= ReadString(fp, &pGraph2Phon->sConsonants);
      iError |= ReadString(fp, &pGraph2Phon->sConsonants_v);
      iError |= ReadString(fp, &pGraph2Phon->sNasals);
      iError |= ReadStringList(fp, &pGraph2Phon->psEndingsList, &pGraph2Phon->nEndingsList);
      iError |= ReadStringList(fp, &pGraph2Phon->psOutputList, &pGraph2Phon->nOutputList);
   }

   /* Read "ENDG2P" to the file so we'll be able to make sure we got to the end properly. */
   iError |= (FNX_FREAD(sBuf, 1, 6, fp)!=6);
   sBuf[6]=0;
   if (FNX_STRCMP(sBuf, "ENDG2P")!=0)
   {
      Message(FNX_STDERR,"Error: Binary Graph2Phon segment did not end with 'ENDG2P'\n");
      iError |= 1;
   }

   FreeAndClear((voidPtr *) &piNumRules);
   FreeAndClear((voidPtr *) &psStrings);

   if (iError)
   {
      FreeRules(pGraph2Phon);
      pGraph2Phon=NULL;
   }

   return pGraph2Phon;

}  /* LoadBinaryRules */


