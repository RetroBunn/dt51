/*C_HEADER_FILE****************************************************************
FILE        :  SelectSinglePron.c
DESC        :  Selects a single (the first or most common) pronunciation from a pronunciation string.
TABS        :  3
OWNER       :  fonix
DATE CREATED:  25 April 2005

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 
  $Revision: 

*END_HEADER*******************************************************************/

#include "port.h"
#include "DTFnxStdlib.h"
//#include "FnxAllocate.h" 

/*  For examining some details of the extraction process */
//#define  PRINT_DETAILS

// Uncomment the following to use memory allocations 
//#define SSP_USE_ALLOCS

#define MAX_SINGLE_PRON	512

/*FUNCTION_HEADER**********************
 * NAME:		;StripOuterParens
 * DESC: 	Remove the initial and final parentheses
 * IN:		   sPron - a pronunciation string from reading a dictionary
 * OUT:		sPron is modified, parenthisis are overwritten with blanks
 * RETURN:	1 if parenthesis successfully blanked, 2 if there were no enclosing parentheses
 *                    -1 if there is a problem - outside parenthesis not matched
 * NOTES:	
 *END_HEADER***************************/
SDWORD StripOuterParens( char *sPron )
{
   BOOL   bSeenPhon = 0, bInitialParen=0, bEndParen=0;
   SDWORD   iLength;
   char *pc;

   pc = sPron;
   /* Find initial parenthesis */ 
   while(*pc)
   {
      if( *pc != '(' && *pc != ' ')
      {
         bSeenPhon = 1;
         break;
      }
      if( *pc == '(' && !bSeenPhon )
      {
         *pc = ' ';
         bInitialParen = 1;
         break;
      }
      pc++;
   }

   /* Find final parenthesis */
   iLength = FNX_STRLEN(sPron);
   pc = sPron+iLength-1;
   while(iLength)
   {
      if( *pc != ')' && *pc != ' ' )
      {
         bSeenPhon = 2;
         break;
      }
      if( *pc == ')' && bSeenPhon !=2 )
      {
         *pc = ' ';
         bEndParen = 1;
         break;
      }
      pc--;
   }

   if( bInitialParen && bEndParen )  //Found and "spaced" both leading and ending parens
      return 1;
   else if( bSeenPhon == 2 )  //No leading and ending parens
      return 0;
   else  // Problem: probably mismatched parens
      return -1;

} 

/*FUNCTION_HEADER**********************
 * NAME:		;RemoveOptionals
 * DESC: 	Removes optional phons from a pronunciation string or includes them in the pronunciation
 * IN:		   sPron - a pronunciation string from dictionary lookup
 *              bRemove - boolean controlling operation; TRUE for removal of optional phons, FALSE for
 *                                  including them in the pronunciation
 * OUT:		sPrron is modified.
 * RETURN:	1 for all cases.
 * NOTES:	
 *END_HEADER***************************/
SDWORD RemoveOptionals(char *sPron, BOOL bRemove )
{
   char *pc;

   if( !FNX_STRLEN(sPron) )
      return 0;

   pc = sPron;

   /* Remove optional phons */
   if(bRemove)
   {
      while(*pc)
      {
         if( *pc == '[' )
         {
            while(*pc != ']' )
            {
               *pc = ' ';
               pc++;
            }
            *pc = ' ';
         }
         pc++;
      }
      return 1;
   }

   /* Remove enclosing brackets from optional phons */
   else
   {
      while(*pc)
      {
         if( *pc == '[' || *pc == ']' )
            *pc = ' ';
         pc++;
      }
      return 1;
   }

}


/*FUNCTION_HEADER**********************
 * NAME:	;CompressSpaces
 * DESC: 	Replaces multiple spaces in a pronunciation string iwith a single space
 * IN:		sPron - pronunciation string: characters and spaces
 * OUT:		sPron is modified
 * RETURN:	n/a
 * NOTES:	
 *END_HEADER***************************/
void CompressSpaces(char *sPron)
{
	char *pc, *pct;
	char  pcLast[1];
	SDWORD   iLength;
#ifdef SSP_USE_ALLOCS
	char *sTemp;
	sTemp = FNX_STRDUP(sPron);
#else
	char sTemp[MAX_SINGLE_PRON];
	FNX_STRCPY(sTemp, sPron);
#endif

	iLength = FNX_STRLEN(sPron);

	/* Remove multiple spaces, copy back into input string */
	memset(sPron,  0x00, iLength);
	pc = sPron;
	pct = sTemp;
	pcLast[0] = *pct;

	while( *pct )
	{
		if( pcLast[0] == ' ' && *pct == ' ' )
		{
			pcLast[0] = *pct;
			pct++;
		}
		else
		{
			*pc = *pct;
			pcLast[0] = *pct;
			pct++;
			pc++;
		}
	}

#ifdef SSP_USE_ALLOCS
	FNX_FREE(sTemp);
#endif
	return;
}


          
/*FUNCTION_HEADER**********************
 * NAME:	;ExtractFirstAlternate
 * DESC: 	Extracts the first non-empty alternate pronunciation from a pronunciation group.
 * IN:		pc - pointer to the beginning of a group of alternate pronunciations
 * OUT:		n/a
 * RETURN:	a pointer to the appropriate alternate pronunication.
 *          NULL is returned if no valid alternate was present in the string
 * NOTES:	Alternate pronunciations may be removed by the remmove optionals operation.
 *          Calling function is responsible for releasing the referenced by the return.
 *END_HEADER***************************/
void ExtractFirstAlternate(char *pc, char *sAlt)
{
   char		*pca; 
   SDWORD   iValid = 0;
   SDWORD   iLength;

   iLength = FNX_STRLEN(pc);
   
   pca = sAlt;

   while(*pc)
   {
      *pca = *pc;
      if( !iValid && *pc != ' ' && *pc != '|' && *pc != ')' )  //check for valid phon character
         iValid = 1;
      pc++; pca++;

      if(*pc == '|' || *pc == ')' )  //end of alternate segment reached ?
      {
         if(iValid)
         {
            *pca = 0x00; 
            return;
         }
         else //alternate segment was empty (all spaces)
         {
            if(*pc == ')' ) //all alternates were empty(ie consisted only of optionals
            {
               return;
            }
            else // alternate segments remain
            {
               memset(sAlt, 0x00, iLength);
               pca = sAlt;
               pc++;
            }
         } //end of invalid processing
      } //end of if '| of ')' section

   }// end of while(*pc) loop

}


/*FUNCTION_HEADER**********************
 * NAME:	;ExtractAlternates
 * DESC: 	Extract the alternate pronunciations from a  group of (possibly nested) alternate pronunciations
 * IN:		sPartial - a group of alternate pronunciations
 * OUT:		iDepth - the depth of nested alternate pronunciations
 * RETURN:	a pointer to the alternates extracted
 *          NULL if no alternates were extracted
 * NOTES:	Alternate pronunciations may be removed by the remmove optionals operation.
 *          Calling function is responsible for releasing the referenced by the return.
 *END_HEADER***************************/
void ExtractAlternates(char *sPartial, SDWORD *iDepth, char *sAlternate )
{
   char *pc;
   SDWORD iLength, i;
#ifdef SSP_USE_ALLOCS
			char *pcAlt;
#else
			char pcAlt[MAX_SINGLE_PRON];
#endif

   *iDepth = 0;
   /* Check for valid string and allocate memory for alternate string */
   iLength = FNX_STRLEN(sPartial);
   pc = sPartial;
   if(!iLength || *pc != '(' )
      return;

   /*Count number of nested levels */
   while( *pc != ')' )
   {
      if(*pc == '(')
         (*iDepth)++;
      pc++;
   }
   pc = sPartial; // reset pointer

   /* Extract the alternates from each level of nesting */
    for( i=0; i<*iDepth; i++)
	{
		if( *pc == '(' )
		{
			*(pc++);	// step past the opening paren
#ifdef SSP_USE_ALLOCS
			pcAlt = (char*)FNX_CALLOC(FNX_STRLEN(pc), sizeof(char) );
#else
			memset(pcAlt, 0, MAX_SINGLE_PRON*sizeof(char));
#endif

			ExtractFirstAlternate(pc, pcAlt);

			if(pcAlt && *pcAlt)
			{
				FNX_STRCAT(sAlternate, " ");
				FNX_STRCAT(sAlternate, pcAlt);
#ifdef SSP_USE_ALLOCS
				FNX_FREE(pcAlt);
#endif
			}
		}
	}
}



/*FUNCTION_HEADER**********************
 * NAME:	;SelectSinglePron
 * DESC: 	Selects a single pronunciation from a pronunciation string produced by a dictionary lookup.  The
 *          pronunciation is the most common among the alternates (first alternate in all alternate groups)/
 * IN:		sPronnunciation - input pronunciation string from dictionary lookup
 *          bRemoveOptionals - TRUE to remove the optional phons from sPronunciation
 *                             FALSE - to include the optional phons in the pronunciation
			bCombineYW	- TRUE to Reconstitute y+ and w+ phones; copy into output
 * OUT:		sPronunciation is modified
 * RETURN:	sPronunciation - pointer to sPronunciation
 *          NULL if errors are encountered.
 * NOTES:	
 *END_HEADER***************************/
int SelectSinglePron(char *sPronunciation, BOOL bRemoveOptionals, BOOL bCombineYW)
{
	char sSinglePron[MAX_SINGLE_PRON];
	char *pc, *pcs;
	SDWORD   iPronLen;
#ifdef SPP_USE_ALLOCS
		 char *sAlternate;
#else
		 char sAlternate[MAX_SINGLE_PRON];
#endif

	/* Check to insure we have a non-empty streing */
	if( sPronunciation == NULL ||
		(iPronLen = FNX_STRLEN(sPronunciation)) == 0 )
		return 0;

#ifdef PRINT_DETAILS
     /**************************************************/
   FNX_FPRINTF(stdout, "Raw pron: %s\n", sPronunciation);
   /**************************************************/
#endif

   //StripOuterParens(sPronunciation);
   RemoveOptionals(sPronunciation, bRemoveOptionals);
   CompressSpaces(sPronunciation);

   /* Clear memory for working string */
   memset(sSinglePron, 0, MAX_SINGLE_PRON*sizeof(char));
   pcs = sSinglePron;

   /* Find first phon*/
   pc = sPronunciation;
   while( *pc  == ' ' )//skip spaces
      pc++;

   /* Remainder of pron string */
   while(*pc)
   {
      if(*pc == '(' ) //beginning of alternates
      {
         char  *pca;
         SDWORD iDepth;

#ifdef SPP_USE_ALLOCS
         sAlternate = (char *)FNX_CALLOC(FNX_STRLEN(pc), sizeof(char));
#else
		 memset(sAlternate, 0, MAX_SINGLE_PRON*sizeof(char));
#endif

		 ExtractAlternates(pc, &iDepth, sAlternate);
		 pca = sAlternate;
         while(*pca)
         {
            *pcs = *pca;
            pcs++; pca++;
         }

#ifdef SPP_USE_ALLOCS
         FNX_FREE( sAlternate );
#endif

         while(iDepth) //Move to end of alternate group
         {
            if( *pc == ')' )
            {
               iDepth--;
               if(iDepth == 0)
                  break;
            }
            pc++;
         }

      }
      else if(*pc != ')')
      {
         *pcs = *pc;
         pcs++; pc++;
      }
	  else  
         pc++;

   }

#ifdef PRINT_DETAILS
   /**************************************************/
   FNX_FPRINTF(stdout, "Raw single: %s\n", sSinglePron); //Raw =>extra spaces
   /**************************************************/
#endif

   /* Remove duplicate spaces, copy back into input string */
   CompressSpaces(sSinglePron);
   /* find end of pronunciation; trim off any trailing blanks */
   {
      SDWORD iLen, i;
      pcs = sSinglePron;
      iLen = FNX_STRLEN(pcs);
      pcs += iLen;
      for(i=0; i<iLen; i++)
      {
         if( *pcs && *pcs != ' ')
            break;
         pcs--;
      }
      *(pcs+1) = 0x00;

      /* Reconstitute y+ and w+ phones; copy into output */
      memset(sPronunciation,  0x00, iPronLen);
      pc = sPronunciation;
      pcs = sSinglePron;
      while( *pcs )
      {
         *pc = *pcs;

         if( bCombineYW && (*pcs == 'j' || *pcs == 'w') && *(pcs+1) == ' ' )
            pcs++;
         pc++;pcs++;
      }
   }
  
   return 1;

}