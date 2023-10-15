/*C_HEADER_FILE****************************************************************
FILE        :  Misc.c
DESC        :  Miscelaneous helper functions
TABS        :  3
OWNER       :  R. Brian Moncur
DATE CREATED:  11 October 1999

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/22/05 9:30a $
  $Revision: 12 $

*END_HEADER*******************************************************************/
#include "FnxPlatform.h"
#include "DTFnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxMisc.h"
#include "FnxLlist.h"
#include "FnxFiles.h"

#ifndef MAXBUF
#define MAXBUF 1024
#endif

#ifdef OS_UNIX

/*FUNCTION_HEADER**********************
 * NAME:    ;strupr
 * DESC:    Makes up for mistakenly using this nonstandard Windows
      function for UNIX systems.
 * OUT:     n/a
 * RETURN:  returns the same pointer value that is passed in.
 *END_HEADER***************************/
char *strupr(char *str) {
  char *ptr;
  ptr=str;  
  while(*ptr != '\0') {
        *ptr = FNX_TOUPPER(*ptr);
        ptr++;
  }
  return str;
}

#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;WhiteSpace
 * DESC:    Check to see if a character is a white space or not.
            This function is cross platform compatible with Unix
            and Dos/Windows systems.
 * IN:      c - a character
 * OUT:     n/a
 * RETURN:  TRUE if c is a white space character, FALSE if not
 * NOTES:   
 *END_HEADER***************************/
BOOL WhiteSpace(char c)
{
      if(c > 0 && c <= ' ')   // Check for characters 1 - 32 (white space characters)
         return TRUE;
      else
         return FALSE;

}

/*FUNCTION_HEADER**********************
   NAME:    ;ForwardToBackSlash
   DESC:    Convert forward slashes (/) in a string to backslashes (\).
   IN:      sFilename - String containing a filename, possibly with forward slashes.
   OUT:     sFilename's forward slashes are replaced with backslashes.
   RETURN:  n/a.
   NOTES:   For example, sFilename="/digit/speech/call0/ws034.wav" 
                      => sFilename="\digit\speech\call0\ws034.wav"
            For use in a non-DOS environment, simply return without doing anything
              to leave forward slashes alone.
 *END_HEADER***************************/
void BackToForwardSlash(char *sFilename)
{
   SDWORD i;
   for (i=0; sFilename[i]; i++)
   {
      if (sFilename[i]=='\\')
         sFilename[i]='/';
   }
}  /* ForwardToBackSlash */



/*FUNCTION_HEADER*******************
 * NAME:    ;CombineStrings
 * DESC:    Combine an array of strings into one space-delimited string.
 * IN:      psString - An array of pointers to strings.
            iNumStrings - Number of strings in psString[].
 * OUT:     A new string is allocated and filled with the strings in psString.
 * RETURN:  Pointer to the newly-allocated string.
 * NOTES:   For example, psString[0..2]={"I", "love", "ribs"} -->return "I love ribs".
            Calling routine needs to free up the returned string.
 *END_HEADER***************************/
char *CombineStrings(char **psString, SDWORD iNumStrings)
{
   SDWORD iString;
   SDWORD iLength=0;
   char *sCombo;

   for (iString=0; iString<iNumStrings; iString++)
      iLength += FNX_STRLEN(psString[iString]) + 1;

   sCombo = (char *) FNX_CALLOC(1, iLength);
   iLength = 0;
   for (iString=0; iString<iNumStrings; iString++)
   {
      FNX_STRCPY(&sCombo[iLength], psString[iString]); /* Keeps the string null-terminated */
      iLength+=FNX_STRLEN(psString[iString]);
      if (iString < iNumStrings-1)
      {
         FNX_STRCPY(&sCombo[iLength]," "); /* Keeps the string null-terminated */
         iLength++;
      }
   }  /* for iString */

   return sCombo;
}  /* CombineStrings */

/*FUNCTION_HEADER**********************
 * NAME:    ;WeThreeStrings   
 * DESC:    Allocate and create a string that is the concatenation of three other strings.
 * IN:      s1, s2, s3 - Three strings to be concatenated.
 * OUT:     A new string is allocated and filled with s1s2s3\0
 * RETURN:  Pointer to the new string.
 * NOTES:   Came from the east.
 *END_HEADER***************************/
char *WeThreeStrings(char *s1, char *s2, char *s3)
{
   char *s, *pc;
   s = FNX_MALLOC((FNX_STRLEN(s1) + FNX_STRLEN(s2) + FNX_STRLEN(s3) + 1) * sizeof(char));
   pc = s;
   while (*s1) /* Copy s1 into s */
      *pc++ = *s1++;
   while (*s2) /* Concatenate s2 to s */
      *pc++ = *s2++;
   while (*s3) /* Concatenate s3 to s */
      *pc++ = *s3++;
   *pc = 0;    /* Null terminate */
   return s;
}  /* WeThreeStrings */

/*FUNCTION_HEADER**********************
   NAME:    ;GrabField
   DESC:    Copy a single whitespace-delimited string from another string.
              Treat anything within '{}' as a single string.
   IN:      sDest   - String to which characters will be copied (NULL=>just skip over the field).
            sSource - String from which characters will be copied.
   OUT:     sDest has the first string in sSource copied into it.
   RETURN:  Pointer to the beginning of the NEXT field in sSource after the one copied.
   NOTES:   This routine skips leading white space in sSource, so sDest will not 
               contain any leading or trailing white space.
            If the first non-whitespace character in sSource is '{', then
               everything AFTER the '{' (including whitespace) until just 
               before the next '}' is copied into sDest.
            For example, sSource="  uc  xy z" => sDest="uc" and return points to "xy z".
            Another example: sSource=" { a b c} xy z" => sDest="a b c", return "xy z".
            Note that leading & trailing whitespace within {} is also removed, but
              whitespace between fields within {} are left there.
            If sDest is NULL, then the field is just skipped instead of copied.
 *END_HEADER***************************/
char *GrabField(char *sDest, char *sSource)
{
   SDWORD i; /* Position in sSource */
   SDWORD j; /* Position in sDest */

   /* Skip leading white space */
   for (i=0; WhiteSpace(sSource[i]); i++)
      ;

   if (sSource[i]=='{')
   {
      /* String begins with '{', so grab everything until closing '}' */
      i++; /* Skip '{' */
      /* Skip leading white space within '{'*/
      while (WhiteSpace(sSource[i]))
         i++;
      for (j=0; sSource[i] && sSource[i]!='}'; i++, j++)
      {
         /* Skip over the field if sDest is NULL.  Otherwise, copy stuff over. */
         if (sDest)
            sDest[j] = sSource[i];
      }
      /* Null-terminate the string. */
      if (sDest)
         sDest[j]=0;
      /* Strip trailing whitespace from sDest. */
      for (j=FNX_STRLEN(sDest)-1; j>=0 && WhiteSpace(sDest[j]); j--)
         if (sDest)
            sDest[j]=0; /* Replace whitespace with null termination */
      /* Skip over final '}' in sSource */
      if (sSource[i]=='}')
         i++;
   }
   else
   {
      /* String does not begin with '{', so grab everything until next white space */
      for (j=0; sSource[i] && !WhiteSpace(sSource[i]); i++, j++)
      {
         if (sDest)
            sDest[j] = sSource[i];
      }
      /* Null-terminate sDest */
      if (sDest)
         sDest[j]=0;
   }

   /* Skip trailing white space */
   while (sSource[i] && WhiteSpace(sSource[i]))
      i++;
   
   return &sSource[i];
}  /* GrabField */

/*FUNCTION_HEADER**********************
   NAME:    ;SplitString
   DESC:    Convert a whitespace-delimited string into an array of strings.
   IN:      sString  - String to be split.
            piNum    - Number of elements in the returned array.
   OUT:     An array of strings is allocated, each of which points to a copy of one
              field in sString.
   RETURN:  Pointer to the newly-created array.
   NOTES:   For example, if sString=" a bc d ef ", this routine returns *piNum=4 and
              ppString[4]={"a", "bc", "d", "ef"}.
 *END_HEADER***************************/
char **SplitString(char *sString, SDWORD *piNum)
{
   LLIST *pList;      /* List of substrings parsed out so far. */
   char *pc;          /* Pointer to the current position in sString. */
   char *sBuf = NULL; /* Temporary string to hold the current field. */
   SDWORD iNumList;      /* Count of how many items are in pList */
   char **psString = NULL;   /* Array of pointers to the substrings. */

   /* Initialize: Start with an empty list, and with pc pointing at the beginning of sString*/
   pList    = NULL;
   iNumList = 0;
   pc       = sString;

   *piNum = 0;
   sBuf = FNX_MALLOC( MAXBUF );

   if( sBuf )
   {
      /* Grab one field at a time, and insert it into a linked list. */
      do
      {
        pc = GrabField(sBuf, pc);
        if (sBuf[0])
        {
          pList = NewLink( FNX_STRDUP(sBuf), pList );
          iNumList++;
        }
      } while (sBuf[0]);

      if (iNumList > 0)
      {
        /* Free pList and convert it to an array */
        psString = ListToArray(&pList, iNumList, NULL);
      }
      else psString = NULL;

      *piNum = iNumList;

      FNX_FREE( sBuf );
   } /* if sBuf */

   return psString;
}  /* SplitString */

/*FUNCTION_HEADER*******************
 * NAME:    ;Strip
 * DESC:    Strip leading & trailing whitespace off of a string.
 * IN:      s - string to be stripped.
 * OUT:     Any leading and trailing whitespace in 's' are removed.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
void Strip(char *s)
{
   SDWORD iFrom, iTo;
   SDWORD iStart=0; /* Flag for whether we've found the first non-whitespace char is s yet */
   SDWORD iLast=-1;  /* Position of last non-whitespace character found */
   if (!s)
      return;
   for (iFrom=iTo=0; s[iFrom]; iFrom++)
   {
      if(! WhiteSpace(s[iFrom])) // Check for characters 1 - 32 (white space characters)
      {
         iStart=1; /* Found a non-whitespace character, so we can begin copying from iFrom to iTo */
         iLast=iTo; /* Keep track of where in the new s[] the last non-whitespace character was found*/
      }
      if (iStart)
         s[iTo++] = s[iFrom];
   }  /* for iFrom */
   
   /* Null-terminate the string at the character just after the last
      non-whitespace character.  If there were no non-whitespace char's,
      then this makes s empty. */
   s[iLast+1]=0x00;
}  /* Strip */

/*FUNCTION_HEADER**********************
   NAME:    ;EndsWith
   DESC:    Tell whether one string ends with another.
   IN:      sString - String (e.g., "E:\digit\speechfiles\call1\cool.wav")
            sEnd    - Ending string (e.g., ".wav")
   OUT:     n/a
   RETURN:  1 if sString ends with sEnd, 0 otherwise.
   NOTES:   Case-sensistive.
 *END_HEADER***************************/
SDWORD EndsWith(char *sString, char *sEnd)
{
   SDWORD iStringPos;

   /* Get the position where sString and sEnd are supposed to be the same */
   iStringPos = FNX_STRLEN(sString) - FNX_STRLEN(sEnd);

   if (iStringPos < 0)
      return 0; /* sString is shorter than sEnd, so it can't end with sEnd */

   if (FNX_STRCMP(&sString[iStringPos], sEnd)==0)
      return 1;
   else return 0;
}  /* EndsWith */

/*FUNCTION_HEADER**********************
   NAME:    ;EndsWithI
   DESC:    Tell whether one string ends with another (case-insensitive).
   IN:      sString - String (e.g., "E:\digit\speechfiles\call1\cool.wav")
            sEnd    - Ending string (e.g., ".wav")
   OUT:     n/a
   RETURN:  1 if sString ends with sEnd, 0 otherwise.
   NOTES:   Same as EndsWith(), except that it is case-insensitive.
 *END_HEADER***************************/
SDWORD EndsWithI(char *sString, char *sEnd)
{
   SDWORD iStringPos;

   /* Get the position where sString and sEnd are supposed to be the same */
   iStringPos = FNX_STRLEN(sString) - FNX_STRLEN(sEnd);

   if (iStringPos < 0)
      return 0; /* sString is shorter than sEnd, so it can't end with sEnd */

   if (FNX_STRICMP(&sString[iStringPos], sEnd)==0)
      return 1;
   else return 0;
}  /* EndsWithI */

/*FUNCTION_HEADER**********************
   NAME:    ;BeginsWithI
   DESC:    Tell whether one string begins with another (case-insensitive).
   IN:      sString - String (e.g., "E:\digit\speechfiles\call1\cool.wav")
            sBegin  - Beginning string (e.g., "E:\Digit\speechfiles")
   OUT:     n/a
   RETURN:  1 if sString begins with sBegin, 0 otherwise.
   NOTES:   Similar to strnicmp(sString, sBegin, strlen(sBegin)), except that
              it checks for NULLs and returns true/false.
 *END_HEADER***************************/
SDWORD BeginsWithI(char *sString, char *sBegin)
{
   if (!sBegin)
      sBegin="";
   if (!sString)
      sString="";
   if (FNX_STRNICMP(sString, sBegin, FNX_STRLEN(sBegin))==0)
      return 1;
   else return 0;
}  /* BeginsWithI */

/*FUNCTION_HEADER**********************
   NAME:    ;EndsWithNumber
   DESC:    Tells whether a filename ends with a numeric extension
   IN:      sFilename - Filename to check (e.g., "C:\Data\digit\trainphn\nnet.27")
   OUT:     n/a
   RETURN:  1 if filename has a numeric extension
            0 otherwise
   NOTES:    
 *END_HEADER***************************/
SDWORD EndsWithNumber(char *sFilename)
{
   SDWORD iStart,iResult=1;

   iStart=FNX_STRLEN(sFilename)-1;
   while(iStart>=0 && sFilename[iStart] != '.')
      iStart--;
   if(sFilename[iStart]=='.' && (unsigned)iStart<FNX_STRLEN(sFilename)-1)
      do
      {
         iStart++;
         if(! (sFilename[iStart]>= '0' && sFilename[iStart] <= '9'))
         {
            iResult=0;
            break;
         }
      }while((unsigned)iStart<FNX_STRLEN(sFilename)-1);
   else
      iResult=0;

   return(iResult);
} /*  EndsWithNumber  */

/*FUNCTION_HEADER**********************
 * NAME:    ;CharInString     
 * DESC:    See if a character is in a string.
 * IN:      c - Character to look for
            s - String to look in.
 * OUT:     sDest is filled with the next whitespace- or delimiter- delimited string in fp.
 * RETURN:  TRUE if c is in s; FALSE otherwise.
 * NOTES:   
 *END_HEADER***************************/
SDWORD CharInString(char c, char *s)
{
   SDWORD i;
   for (i=0; s[i]; i++)
      if (c==s[i])
         return TRUE;
   return FALSE;
}  /* CharInString */

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadField     
 * DESC:    Read a field (but treat delimiters as separate fields)
 * IN:      sDest - Character buffer to read into.
            sDelim- String containing one or more delimiters to treat as separate fields.
            fp    - File pointer to read from.
 * OUT:     sDest is filled with the next whitespace- or delimiter- delimited string in fp.
            On EOF, sDest is set to the empty string.
 * RETURN:  Length of string copied into sDest, if any, or 0 on EOF.
 * NOTES:   Pretty much like an fscanf(fp,"%s",sDest), except that if a delimiter (e.g., ';')
              is encountered after some non-whitespace text, it is left there for the
              next read.
            For example, if called repeatedly with ReadField(sDest,";",fp) on a file containing:
               "define onestate   \n
                    $bck_l<f     <f>;"
            (where '\n' is a newline) this routine would return the strings:
               "define", "onestate", "$bck_l<f", "<f>", ";", all with a return value of 1,
               and then "" with a return value of 0 indicating end-of-file.
            Useful for parsing whitespace-separated/semi-colon-terminated lines
               such as those used in description files.  Also useful for parsing lines
               that have other delimeters, such as parentheses or brackets, '|' symbols, etc.
 *END_HEADER***************************/
SDWORD ReadField(char *sDest, char *sDelim, FILE *fp)
{
   SDWORD      c;   /* Current character */
   SDWORD   i=0; /* Position in sDest */

   /* Skip whitespace and get first character */
   do
      c = FNX_FGETC(fp);
   while (c!=EOF && c>0 && c<=' ');

   /* Read until whitespace, EOF, or delimiter char */
   while (c!=EOF && !CharInString((char)c,sDelim) && !(c>0 && c<=' '))
   {
      sDest[i++] = (char)c;
      c = FNX_FGETC(fp);
   }
   /* If this string contains ONLY a ';', allow it */
   if (CharInString((char)c, sDelim))
   {
      if (i==0)
     {
         sDest[i++] = (char)c; /* String will contain only the delimiter */
     }
      else 
     {
      //The string contained something before the delimiter, so put
      //the delimiter back into the input stream to be read next time
      //djb. good luck!
//    FNX_FSEEK(fp, -1, SEEK_CUR);
      //drw: fseek() doesn't always work when a file is opened in
      //  text mode, but instead goes to strange places at times.
      //  Therefore, we need to [1] use ungetc(), or [2] modify
      //  ReadField() and all calls to it to pass around a '&cNextChar'
      //  to do our own manual ungetc(), or [3] make sure all fopens
      //  are done in binary mode, which might get us extra whitespace
      //  (newline or linefeed) characters on DOS text files.
      //  Any disputes are to be settled on the racquetball court. -Randy Wilson
         FNX_UNGETC( c, fp ); 
      }
   }
   /* Null-terminate the string (even if we haven't read anything)*/
   sDest[i]=0x00;
   return i; /* Return the length of the string read, if any, or 0 on EOF. */
}  /* ReadField */

/*FUNCTION_HEADER**********************
 * NAME:    ;ExtractField     
 * DESC:    Extract a field from a string
 * IN:      sDest  - String to copy field into.
            sDelim - String containing characters to use as delimeters.
 * OUT:     sDest contains the next whitespace- or delimeter- separated field,
               OR the next delimeter, if nothing occurs before it,
               OR only a null-terminating character, if the end-of-string was encountered.
 * RETURN:  Number of characters "read" from sBuffer.
 * NOTES:   Any character preceded by '\' will be "escaped" and not treated as a delimiter.
            (To use the '\' character itself, you would need to escape it by putting it twice).
            To call repeatedly, use iPos += ExtractField(sDest, sDelim, &sBuffer[iPos]),
              and iPos will be updated appropriately, and each call will pick up where
              the last one left off.
 *END_HEADER***************************/
SDWORD ExtractField(char *sDest, char *sDelim, char *sBuffer)
{
   char c;            /* Current character, i.e., sBuffer[iBufPos] */
   SDWORD iBufPos=0;  /* Current position in sBuffer */
   SDWORD iDestPos=0; /* Current position in iDest */
   
   /* Skip whitespace and get first non-whitespace character */
   do
      c = sBuffer[iBufPos++];
   while (c>0 && c<=' ');

   /* Read until whitespace or delimiter char */
   while (c && !CharInString(c,sDelim) && !(c>0 && c<=' '))
   {
      /* If c is '\', then the following character is "escaped", so
           accept it even if it is a special delimiter character. */
      if (c=='\\')
         c = sBuffer[iBufPos++];
      /* Copy the current character into the destination string. */
      sDest[iDestPos++] = c;
      /* Make sure we don't read off the end of the string if the last 
         character in the string just happens to be '\' */
      if (!c)
         break;
      c = sBuffer[iBufPos++];
   }  /* while */

   if (c)
   {
      if(CharInString(c, sDelim))
      {
         /* If this string contains ONLY a delimeter, allow it */
         if (iDestPos==0)
            sDest[iDestPos++] = c; /* String will contain only the delimiter */
         else iBufPos--; /* String contained something before delimeter, so put it back for later use */
      }
   }
   else iBufPos--; /* Went past end-of-string null-termination character, so go back to it so
                      that we don't read off the end next time. */
   /* Null-terminate the destination string (even if we haven't read anything)*/
   sDest[iDestPos]=0x00;
   return iBufPos; /* Return number of characters read from iBufPos. */
}  /* ExtractField */

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadTxt    
 * DESC:    Read a text file and return a list of its words.
 * IN:      sTxtFile - Filename of a .txt file.
            plNumWords - Address in which to return the number of words in the text file.
 * OUT:     An array of *plNumWords pointers is allocated, each of which points
              to a newly-allocated string containing one word from the text file.  Also,
              the number of words in the array is put into plNumWords.
 * RETURN:  Pointer to the array of word strings.
 * NOTES:   
 *END_HEADER***************************/
//#ifndef FNX_LEAN_AND_MEAN
#  if !defined(FNX_LEAN_AND_MEAN) || defined(TRAIN_PHONEME_WEIGHT)  // Need it for training phoneme weights
char **ReadTxt(char *sTxtFile, SDWORD *plNumWords)
{
   FILE *fp;
   LLIST *pWordList;
   char **psWord = NULL, *sWord, *sBuf = NULL;
   SDWORD iNumWords;

   *plNumWords = 0;

   if (sTxtFile==NULL || sTxtFile[0]==0)
      return NULL;
   fp = FNX_FOPEN(sTxtFile, "r");
   if (!fp)
   {
      Message(FNX_STDERR,"Couldn't open '%s' for reading in ReadTxt.\n", sTxtFile);
      *plNumWords = 0;
      return NULL;
   }

   iNumWords=0;
   pWordList=NULL;
   
   sBuf = FNX_MALLOC( MAXBUF );

   if( sBuf )
   {
      /* Grab the next word, but treat '<' and '>' as separate words,
        e.g., "i love<burp> ribs" will come out as "i", "love", "<", "burp", ">", "ribs",
        and the "burp" and ">" will be swallowed up (as it were) in the first 'if' below. */
      while (ReadField(sBuf,"<>",fp))
      {
         /*  Don't include things like <bn>, <bs: on sale now>, .cough, *PARTIALWORD or PARTIALWORD*
          *  We may want them later if we train special models for them
          *  but for now they hose recognition testing  
          */
        if (FNX_STRCMP(sBuf,"<")==0)
        {
          /* Throw stuff away until we get a closing ">" */
          while (ReadField(sBuf,"<>",fp) && FNX_STRCMP(sBuf,">")!=0)
          {
            if (FNX_STRCMP(sBuf,"<")==0)
               Message(FNX_STDERR,"Warning: Two '<' without a matching '>' in %s\n", sTxtFile);
          }
          if (FNX_STRCMP(sBuf,">")!=0)
            Message(FNX_STDERR,"Warning: '<' had no closing '>' in %s\n", sTxtFile);
          continue; /* Don't want to add ">" as a word. */
        }
        else if (FNX_STRCMP(sBuf,"<")==0)
          Message(FNX_STDERR,"Warning: '>' without a preceding '<' in %s\n", sTxtFile);
        else if ((sBuf[0]=='.') || FNX_STRCHR(sBuf,'*'))
        {
          //Message(FNX_STDERR,"Warning: Throwing out word '%s' in file %s\n", sBuf, sTxtFile);
          continue;
        }

        /* Looks like we got a real word, so add it to our list. */
        if (FNX_STRCHR(sBuf,'<') || FNX_STRCHR(sBuf,'>') || FNX_STRCHR(sBuf,'*'))
          Message(FNX_STDERR,"Warning: using word '%s' from %s\n", sBuf, sTxtFile);
        sWord = FNX_STRDUP(sBuf);
        pWordList = NewLink(sWord, pWordList);
        iNumWords++;
      }
      FNX_FREE( sBuf );
   } /* if sBuf */
   FNX_FCLOSE(fp);

   if (iNumWords > 0)
   {
      /* Build an array of strings from the linked list of strings, and free links. */
      psWord = ListToArray(&pWordList, iNumWords, NULL);
   }  /* if */
   else
   {
      psWord = NULL;
   }

   *plNumWords = iNumWords;

   return psWord;
}  /* ReadTxt */
#endif


/*FUNCTION_HEADER**********************
 * NAME:    ;BuildStringList
 * DESC:    Put an array of strings and pointers to them into a single block of memory.
 * IN:      psNames - Array of pointers to strings.
            iNumNames - Number of strings in psNames[].
 * OUT:     A single array of bytes is allocated, with 'iNumNames' pointers
              at the beginning, and copies of the strings in 'psNames[]'
              at the end, with the pointers pointing at these new copies.
 * RETURN:  Address of the newly-allocated block of memory.
 * NOTES:   Deallocate the returned block with a single "Deallocate()",
              i.e., DON'T deallocate each string, since all of the strings
              and pointers to them are all in a single contiguous block
              of memory (kind of like VecAlloc(), except with variable-sized vec's).
 *END_HEADER***************************/
char **BuildStringList(char **psNames, SDWORD iNumNames)
{
   SDWORD iBufferSize; /* Number of characters needed for the strings and 
                       their null terminators (but not the pointers to them) */
   SDWORD iName; /* Index in psNames[] */
   char *sBuffer; /* Pointer to the single block of memory with everything in it. */
   char **psPointer; /* Array of pointers to the copies of the strings; stored at the beginning of sBuffer */
   char *pcName; /* Current location in sBuffer to copy the next string into. */

   /* Count how many characters are needed for the entire buffer. */
   iBufferSize = 0;
   for (iName=0; iName<iNumNames; iName++)
   {
      if (psNames[iName])
         iBufferSize += FNX_STRLEN(psNames[iName]) + 1; /* +1 for null terminator */
   }
   /* Allocate a character buffer large enough to hold an array of 
      pointers into the strings plus the strings themselves. */
   sBuffer = (char *) FNX_MALLOC(sizeof(char *) * iNumNames + iBufferSize);
   /* Assign pointers at the beginning of psBuffer to point into the buffer,
      and copy the strings in. */
   psPointer = (char **)sBuffer;
   pcName    = &(sBuffer[sizeof(char *) * iNumNames]);
   for (iName=0; iName<iNumNames; iName++)
   {
      /* See if this string is NULL */
      if (psNames[iName])
      {
         /* String not NULL, so assign the pointer to the current position
            in the string buffer area. */
         psPointer[iName] = pcName;
         /* Copy the string into that position */
         FNX_STRCPY(pcName, psNames[iName]);
         /* Advance 'pcName' to point to just beyond this string. */
         pcName += FNX_STRLEN(psNames[iName]) + 1;
      }
      else 
      {
         /* NULL pointer, so put a NULL in there, and don't change pcName,
            since there is no string to put where pcName is. */
         psPointer[iName] = NULL;
      }
   }  /* for iName */

   /* Return a pointer to the new buffer */
   return (char **) sBuffer;
}  /* BuildStringList */

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
 * NAME:    ;MakeCombinedString
 * DESC:    Create a string consisting of a list of strings separated by a separator and surrounded by a prefix and suffix.
 * IN:      sPrefix - String to attach to beginning (e.g., "$basephones = (")
            sSeparator - String to insert between each element (e.g., "|")
            sSuffix    - String to append to end (e.g., ");" )
            psElements - Strings to be strung together (e.g, "one", "two", "three")
            iNumElements - Number of strings in psElements[]
 * OUT:     A string is allocated
 * RETURN:  Pointer to the newly-created string
 * NOTES:   
 *END_HEADER***************************/
char *MakeCombinedString(char *sPrefix, char *sSeparator, char *sSuffix, char **psElements, SDWORD iNumElements)
{
   SDWORD i, iLength, iSeparatorLength;
   char *sCombinedString, *pc;

   iSeparatorLength = FNX_STRLEN(sSeparator);
   iLength = FNX_STRLEN(sPrefix);
   for (i=0; i<iNumElements; i++)
   {
      iLength += FNX_STRLEN(psElements[i]);
      if (i==iNumElements-1)
         iLength += FNX_STRLEN(sSuffix);
      else iLength += iSeparatorLength;
   }
   iLength++; /* for null terminator */
   
   /* Create string */
   sCombinedString = (char *)FNX_CALLOC(iLength, sizeof(char));
   pc = StrCopyCat(sCombinedString,sPrefix);
   for (i=0; i<iNumElements; i++)
   {
      pc = StrCopyCat(pc, psElements[i]);
      if (i==iNumElements-1)
         pc = StrCopyCat(pc, sSuffix);
      else pc = StrCopyCat(pc, sSeparator);
   }
   *pc = 0; /* null terminate */
   
   return sCombinedString;
}  /* MakeCombinedString */

/*FUNCTION_HEADER**********************
 * NAME:    SameString
 * DESC:    Tell whether two strings are the same (treating NULL strings as ""),
              using a CASE-SENSITIVE comparison.
 * IN:      s1, s2 - Two strings to compare.
 * OUT:     n/a
 * RETURN:  TRUE if the two strings are the same (using strcmp)
            OR if they are both "empty" (i.e., "" or NULL).  FALSE otherwise.
 * NOTES:   
 *END_HEADER***************************/
int SameString(char *s1, char *s2)
{
   if (!s1 || !s1[0])
   {
      if (!s2 || !s2[0])
         return TRUE; /* Both empty => same string */
      else return FALSE; /* Only one empty => different string */
   }
   else
   {
      if (!s2 || !s2[0])
         return FALSE; /* Only s2 empty => different strings */
      else if (FNX_STRCMP(s1, s2)==0)
         return TRUE; /* Same string */
      else return FALSE; /* Different strings */
   }
   FNX_ASSERT(0); /* Shouldn't get here */
}  /* SameString */

/*FUNCTION_HEADER**********************
 * NAME:    SameStringI
 * DESC:    Tell whether two strings are the same (treating NULL strings as ""),
              using CASE-INSENSITIVE comparison.
 * IN:      s1, s2 - Two strings to compare.
 * OUT:     n/a
 * RETURN:  TRUE if the two strings are the same (using stricmp)
            OR if they are both "empty" (i.e., "" or NULL).  FALSE otherwise.
 * NOTES:   
 *END_HEADER***************************/
int SameStringI(char *s1, char *s2)
{
   if (!s1 || !s1[0])
   {
      if (!s2 || !s2[0])
         return TRUE; /* Both empty => same string */
      else return FALSE; /* Only one empty => different string */
   }
   else
   {
      if (!s2 || !s2[0])
         return FALSE; /* Only s2 empty => different strings */
      else if (FNX_STRICMP(s1, s2)==0)
         return TRUE; /* Same string */
      else return FALSE; /* Different strings */
   }
   FNX_ASSERT(0); /* Shouldn't get here */
}  /* SameStringI */

/*FUNCTION_HEADER**********************
 * NAME:    ;CaseCmpString
 * DESC:    Compare strings (for use in qsort and bsearch), using case-sensitive
              comparison if they are the same otherwise.  Treat "NULL" as smaller
              than anything else.
 * IN:      pA, pB - Pointers to two pointers to strings.
 * OUT:     n/a
 * RETURN:  -1 if a<b, 0 if a==b, 1 if a>b
 * NOTES:   Compares two strings structures using stricmp().  If they are the same, 
              it compares them using strcmp().  
            If either string is NULL, then NULL is treated as "less than" 
              anything else (i.e., NULL < "aaa").
            To use outside of qsort() or bsearch() use CaseCmpString(&s1, &s2).
 *END_HEADER***************************/
#ifdef OS_WIN32
int __cdecl CaseCmpString(const void *pA, const void *pB)
#else
int CaseCmpString(const void *pA, const void *pB)
#endif
{
   char **psA;
   char **psB;
   char *sA, *sB;
   SDWORD iCmp;

   /* Convert void pointers to wordnode **'s */
   psA = (char **) pA;
   psB = (char **) pB;
   FNX_ASSERT(psA && psB);

   /* Get pointers to word nodes */
   sA = *psA;
   sB = *psB;

   /* Make sure they're not null and compare strings */
   if (!sA || !sB)
   {
      if (!sA && !sB) return 0; /* Both null, so they're equal */
      else if (!sA) return -1;  /* A is null, so it is less than B */
      else return +1;           /* B is null, so it is less than A */
   }

   /* Compare word nodes.  If they are the same with stricmp, 
        use strcmp to see if they are different. This allows
        the words to be sorted by letters first, and then
        by capitalization only on matchin words. */
   iCmp = FNX_STRICMP(sA, sB);
   if (iCmp==0)
      iCmp = FNX_STRCMP(sA, sB);
   return iCmp;   
}  /* CaseCmpString */

/*FUNCTION_HEADER**********************
 * NAME:   ;RemoveDuplicateStrings
 * DESC:   Sort an array of strings and remove all duplicates.
 * IN:     psStrings - array of strings
           piNumStrings - address of the number of strings
 * OUT:    psStrings[] is sorted; any duplicates are freed and other strings slid
             down to fill in the holes; *piNumStrings is updated to reflect the
             number of remaining strings in the list.
 * RETURN: n/a
 * NOTES:  
 *END_HEADER***************************/
void RemoveDuplicateStrings(char **psStrings, SDWORD *piNumStrings)
{
   SDWORD iOldIndex, iNewIndex;
   
   /* Make sure we don't have an empty list */
   if (psStrings==NULL || *piNumStrings<1)
      return;

   /* Sort the strings */
   qsort(psStrings, *piNumStrings, sizeof(char *), CaseCmpString);

   /* Remove duplicates */
   for (iOldIndex=iNewIndex=0; iOldIndex<*piNumStrings; iNewIndex++)
   {
      /* Slide an old pointer down into its new place (unless they are still the same index) */
      if (iNewIndex<iOldIndex)
         psStrings[iNewIndex]=psStrings[iOldIndex];
      iOldIndex++; /* Skip past the pointer already used by iNewIndex */
      /* Skip all pointers that point to the same string */
      while (iOldIndex < *piNumStrings && SameString(psStrings[iNewIndex], psStrings[iOldIndex]))
      {
         FNX_FREE(psStrings[iOldIndex]);
         iOldIndex++;
      }
   }  /* for iOld/NewIndex */
   
   /* Set the deleted strings to NULL, and return the new number of strings
      in *piNumPronun. */
   while (*piNumStrings > iNewIndex)
   {
      psStrings[--(*piNumStrings)] = NULL;
   }
}  /* RemoveDuplicateStrings */

