/*C_HEADER_FILE****************************************************************
FILE			:	onealign.c
DESC			:	dp matching functions
TABS			:	3
OWNER			:	
DATE CREATED:	

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 10/26/01 5:36p $
  $Revision: 2 $

*END_HEADER*******************************************************************/
//#include <stdlib.h> //moved to port.h mlt 02/09/06
//#include <string.h> //moved to port.h mlt 02/09/06
#include "port.h"
#include "onealign.h"

/* matching related constant, but potentially configrable */
#define DELETION_PENALTY       3
#define INSERTION_PENALTY      3
#define SUBSTITUTION_PENALTY   4
#ifndef max
#define max(a,b) ((a)>(b))?(a):(b);
#endif


//#ifndef FNX_STRICMP  // now in Dtfnxstdlib.h mlt 02/09/06

//#define FNX_STRICMP stricmp // now in Dtfnxstdlib.h mlt 02/09/06
//#endif // now in Dtfnxstdlib.h mlt 02/09/06

//#ifndef FNX_CALLOC // now in Dtfnxstdlib.h mlt 02/09/06
//#define FNX_CALLOC calloc // now in Dtfnxstdlib.h mlt 02/09/06
//#endif // now in Dtfnxstdlib.h mlt 02/09/06

//#ifndef FNX_FREE // now in Dtfnxstdlib.h mlt 02/09/06
//#define FNX_FREE free // now in Dtfnxstdlib.h mlt 02/09/06
//#endif // now in Dtfnxstdlib.h mlt 02/09/06

#define FILLCHAR '#'

/* data structure for matching table */
enum {INSERTION, DELETION, CORRECT, SUBSTITUTION};

/*FUNCTION_HEADER**********************
 *  NAME:	;AppendStrings
 *
 *  DESC:	Append two words to the end of two word lists.
 *
 *  IN:     sTarget - Target word list (e.g., "I love them")
 *          sRecog - Output word list (e.g., "I like ####")
 *          sTargetWord    - Target word to be appended (or NULL if insertion), (e.g., "ribs")
 *          sRecogWord    - Output word to be appended (or NULL if deletion), (e.g., "chicken")
 *          nTargetLength - Amount of memory allocated for sTarget
 *          nRecogLength  - Amount of memory allocated for sRecog
 *
 *  OUT:	sTargetWord and sRecogWord are appended to sTarget and sRecog, respectively,
 *          along with additional spaces to make sure sTarget and sRecog are the same length.
 *
 *          If sRecogWord or sTargetWord are NULL, then FILLCHAR's are used to make them as long
 *          as the other word (e.g., "####" to take the place of "THEM" above).
 *
 *          If sRecogWord and sTargetWord don't match, the words are output in UPPER CASE, else lower case.
 *
 *  RETURN:	n/a.
 *  NOTES:	
*END_HEADER***************************/
void AppendStrings(char *sTarget, char *sRecog, char *sTargetWord, char *sRecogWord, int iLength, int bChangeCase)
{
	int i;        /* Index into the input strings sTargetWord[i] and sRecogWord[i]*/
	int iTarLen, iRecLen, iMaxLen; /* Length of sTargetWord and sRecogWord, and max of those. */
	int iBothLen; /* Index into sTarget and sRecog, and also the length of both of these so far. */
	int iMatch;   /* Flag for whether sTargetWord and sRecogWord are the same word */
	
	/* Decide if the two strings match */
	if (sTargetWord && sRecogWord && FNX_STRICMP(sTargetWord, sRecogWord) == 0)
		iMatch=1;
	else
		iMatch=0;
	
	/* get the length of sRecogWord and sTargetWord, and find the max of them */
	iTarLen = ((sTargetWord == NULL)? 0 : FNX_STRLEN(sTargetWord));
	iRecLen = ((sRecogWord == NULL)? 0 : FNX_STRLEN(sRecogWord));
	iMaxLen = max(iTarLen,iRecLen);
	
	/* Add a space if there are already words in the strings. */
	iBothLen = FNX_STRLEN(sTarget); /* = strlen(sRecog) */
	
	if (iBothLen + iMaxLen >= iLength)
		/* We don't have enough room to write the sTargetWord */
		return;
	
	if (iBothLen > 0)
	{
		sRecog[iBothLen] = sTarget[iBothLen] = ' ';
		iBothLen++;
	}
	
	/* Append one character at a time to both sTarget and sRecog. */
	for (i = 0; i < iMaxLen; i++)
	{
		if (sTargetWord == NULL)				/* There was a deletion, so use '#' for this entire word */
		{
			sTarget[iBothLen] = FILLCHAR;
		}
		else if (i < iTarLen)
		{
			if (iMatch)
			{
				if( bChangeCase )
					sTarget[iBothLen] = FNX_TOLOWER(sTargetWord[i]);	/* sTargetWord == sRecogWord, so use lower case */
				else
					sTarget[iBothLen] = sTargetWord[i];
			}
			else
			{
				if( bChangeCase )
					sTarget[iBothLen] = FNX_TOUPPER(sTargetWord[i]);	/* sTargetWord != sRecogWord, so use upper case */
				else
					sTarget[iBothLen] = sTargetWord[i];
			}
		}
		else
		{
			sTarget[iBothLen] = ' '; /* sTargetWord is shorter than sRecogWord, so append spaces */
		}
		
		if (sRecogWord == NULL)
			sRecog[iBothLen] = FILLCHAR;
		else if (i < iRecLen)
		{
			if (iMatch)
			{
				if( bChangeCase )
					sRecog[iBothLen] = FNX_TOLOWER(sRecogWord[i]);
				else
					sRecog[iBothLen] = sRecogWord[i];
			}
			else
			{
				if( bChangeCase )
					sRecog[iBothLen] = FNX_TOUPPER(sRecogWord[i]);
				else
					sRecog[iBothLen] = sRecogWord[i];
			}
		}
		else
			sRecog[iBothLen]=' ';
		
		if (++iBothLen >= iLength)
			break;
	}  /* for */
	/* Null-terminate both strings */
	sTarget[iBothLen] = sRecog[iBothLen] = '\0';
}  /* AppendStrings */

/*FUNCTION_HEADER**********************
 *  NAME:	;DPMatchStrings
 *  DESC:	Matches two lists of strings for insertions, deletions, and substitutions.
 *  IN:     psTarget -- Target/correct/reference string list.
 *			nTarget  -- Number of strings in psTarget.
 *			psRecog  -- Recognized/estimated/hypothesized string list.
 *			nRecog   -- Number of strings in nRecog.
 *  OUT:	piMatch  -- Matching (needs nTarget+nRecog locations to be already allocated.)
 *  RETURN:	nMatch   -- Number of items in piMatch.
 *  NOTES:	
 *
 *		Originally extracted from Tony Robinson's DPMATCH2.C file.
 *
 *		Aligns the symbols between the Marked and Found lists to
 *		determine insertions, deletions, and substitutions.
 *END_HEADER***************************/
int DPMatchStrings(char *psTarget[], int nTarget, char *psRecog[], int nRecog, int *piMatch)
{
	/* Macro for index calculations */
#define	rect(i,j) ((i)*(nTarget+1)+(j))
	int	i, j;
	int	iFrom;
	int	*piFrom;
	float	*pfScoring;
	float	fThisScore;
	float	fDiagonalScore;
	float	fPreviousScore;
	int	nMatch;
	
	piFrom  = (int *)FNX_CALLOC((nRecog+1)*(nTarget+1), sizeof(int));
	pfScoring = (float *)FNX_CALLOC((nTarget+1), sizeof(float));
	/*
	* Score by carrying forward the path from i-1 and j-1
	* to the i, j element.
	*/
	pfScoring[0] = INSERTION_PENALTY * 0;
	piFrom[rect(0,0)]  = INSERTION;
	for (j=1; j <= (int )nTarget; j++)
	{
		pfScoring[j] = (float)(DELETION_PENALTY * j);		/* Initialize border */
		piFrom[rect(0,j)]  = DELETION;
	}
	for(i = 1; i <= (int )nRecog; i++)
	{
		fPreviousScore = (float)(INSERTION_PENALTY * (i-1));
		pfScoring[0] = (float)(INSERTION_PENALTY * i);
		piFrom[rect(i,0)]  = INSERTION;
		for(j = 1; j <= (int )nTarget; j++)
		{
			fDiagonalScore = fPreviousScore;
			fPreviousScore = pfScoring[j];
			fThisScore = fDiagonalScore;
			if(FNX_STRICMP(psRecog[i - 1], psTarget[j - 1])==0)
			{
				piFrom[rect(i,j)]  = CORRECT;		/* mark as correct */
			}
			else
			{
				fThisScore += SUBSTITUTION_PENALTY;
				piFrom[rect(i,j)]  = SUBSTITUTION;		/* mark as substitution */
				if(fPreviousScore + INSERTION_PENALTY < fThisScore)
				{
					fThisScore = fPreviousScore + INSERTION_PENALTY;
					piFrom[rect(i,j)]  = INSERTION;		/* mark as insertion */
				}
				if(pfScoring[j - 1] + DELETION_PENALTY < fThisScore)
				{
					fThisScore = pfScoring[j - 1] + DELETION_PENALTY;
					piFrom[rect(i,j)]  = DELETION;		/* mark as deletion */
				}
			}  /* else */
			pfScoring[j] = fThisScore;			/* Save the score */
		}  /* for j */
	}  /* for i */
	   /*
	   * Back track through the from matrix beginning with
	   * the last element for both lists.
	*/
	nMatch = 0;
	i = nRecog;
	j = nTarget;
	while (i>0 || j>0)
	{
		iFrom = piFrom[rect(i,j)];
		if ((i <= 0) || (iFrom == DELETION))
		{
		/*
		* Marked as "deletion" so skip past the symbol in the
		* correct list.
			*/
			--j;
			iFrom = DELETION;
		}
		else if ((j <= 0) || (iFrom == INSERTION))
		{
		/*
		* Marked as "insertion" so skip past the symbol in
		* the "estimated" list.
			*/
			--i;
			iFrom = INSERTION;
		}
		else
		{
		/*
		* Substitution or correct, so advance on both lists.
			*/
			--j;
			--i;
			iFrom = (FNX_STRICMP(psRecog[i],psTarget[j])==0) ? CORRECT : SUBSTITUTION;
		}
		piMatch[nMatch++] = iFrom;
	}
	/*
	* Reverse the list.
	*/
	for (i=0, j=nMatch-1; i<j; i++, j--)
	{
		iFrom = piMatch[i];
		piMatch[i] = piMatch[j];
		piMatch[j] = iFrom;
	}
	FNX_FREE(pfScoring);
	FNX_FREE(piFrom);
	return(nMatch);
	
}	/*  DPMatch  */
#undef rect

/*FUNCTION_HEADER**********************
 * NAME:	;MatchStrings
 * DESC: 	Do a dynamic-programming match between two arrays of strings.
 * IN:		psTarget - Array of target/reference/correct strings (can be NULL if nTarget==0)
 *          nTarget  - Number of strings in psTarget
 *          psRecog  - Array of recognized/estimated/hypothesized words. (Can be NULL if nRecog==0)
 *          nRecog   - Number of strings in psRecog
 *          piInsertions - Address of int to increment with # of insertions in psTarget
 *          piDeletions  - Address of int to increment with # of deletions in psRecog
 *          piCorrect    - Address of int to increment with # of correct matches between psTarget and psRecog
 *          piSubstitutions-Addr.  of int to increment with # of substitutions.
 *          psTargetOutput -Address of string in which to return a target string (NULL=>ignore)
 *          psRecogOutput  -Address of string in which to return a recognized string (NULL=>ignore)
 * OUT:		piInsertions, piDeletions, piTarget and piSubstitutions are incremented (unless NULL),
 *           and psTarget and psRecog are filled with pointers to newly-allocated
 *           strings suitable for printing to a .ali file (unless they are NULL).
 * RETURN:	TRUE if the word lists match.  FALSE if there is an error.
 * NOTES:	For example, if psTarget={"I","love","ribs"} and psRecog={"I", "really", "love", "chicken"},
 *            then psTarget="I ###### love RIBS   ", and
 *                 psRecog ="I really love CHICKEN".
 *          Since there was one insertion ("really"), *piInsertions in incremented, and so on.
 *          It is up to the calling routine to make sure the ins/del/cor/sub are initialized
 *            to 0.  Also, be careful to pass the ins/del/cor/sub parameters in the right order!
 *          If piIns/Del/Cor/Sub or psTarget/Output are NULL, they are ignored.
 *          The calling routine needs to free up the string returned in psTarget and psRecog.
 *          Word accuracy = (C-I)/(C+S+D); Word recognition = C/(C+S+D).
 *END_HEADER***************************/
int MatchStrings(char *psTarget[], int nTarget, char *psRecog[], int nRecog, 
                  int *piInsertions, int *piDeletions, int *piCorrect, int *piSubstitutions,
                  char **psTargetOutput, char **psRecogOutput, int bChangeCase)
{
	
	char	*sTargetOutput, *sRecogOutput;
	int	*piMatch; /* Array of INS/DEL/COR/SUB symbols used in the best-aligned DP path */
	int	nMatch;   /* Number of elements in piMatch */
	int	i;        /* Index into piMatch[] */
	int	iLength;  /* Length of psTargetOutput and psRecogOutput */
	int	iTarget, iRecog; /* Current position in psTarget[] and psRecog[] */
	int	iTargetLen, iRecogLen; /* Length of current target/recog word */
	int	bExactMatch=1; /* Flag for whether the two word sequences exactly match */
	
	piMatch = (int *) FNX_CALLOC(nTarget + nRecog, sizeof(int));
	
	/** Compute match for the two sequences. */
	nMatch = DPMatchStrings(psTarget, nTarget, psRecog, nRecog, piMatch);
	
	/** Build two strings for printing to the alignment (.ali) file */
	if (psTargetOutput && psRecogOutput)
	{
		/* Figure out how long to make the two strings */
		iLength=0;
		iTarget = iRecog = 0;
		for (i=0; i<nMatch; i++)
		{
			switch(piMatch[i])
			{
            case INSERTION: 
				iLength += FNX_STRLEN(psRecog[iRecog++]) + 1; 
				break;
            case DELETION: 
				iLength += FNX_STRLEN(psTarget[iTarget++]) + 1; 
				break;
            case CORRECT:
            case SUBSTITUTION: 
				iRecogLen  = FNX_STRLEN(psRecog[iRecog++]);
				iTargetLen = FNX_STRLEN(psTarget[iTarget++]);
				iLength += max(iTargetLen, iRecogLen) + 1;
				break;
			}  /* switch*/
		}  /* for i */
		/* Allocate strings to hold the target & recog sentences */
		sTargetOutput = (char *) FNX_CALLOC(iLength+1, sizeof(char));
		sRecogOutput  = (char *) FNX_CALLOC(iLength+1, sizeof(char));
		iTarget = iRecog = 0;
		for (i=0; i<nMatch; i++)
		{
			switch(piMatch[i])
			{
            case INSERTION: 
				AppendStrings(sTargetOutput, sRecogOutput, NULL, psRecog[iRecog++], iLength, bChangeCase); 
				break;
            case DELETION: 
				AppendStrings(sTargetOutput, sRecogOutput, psTarget[iTarget++], NULL, iLength, bChangeCase); 
				break;
            case CORRECT:
				AppendStrings(sTargetOutput, sRecogOutput, psTarget[iTarget++], psRecog[iRecog++], iLength, bChangeCase);
				break;
            case SUBSTITUTION: 
				AppendStrings(sTargetOutput, sRecogOutput, psTarget[iTarget++], psRecog[iRecog++], iLength, bChangeCase);
				break;
			}  /* switch*/
		}  /* for i */
		
		/* Return the two strings via parameters */
		*psTargetOutput = sTargetOutput;
		*psRecogOutput  = sRecogOutput;
	}  /* if psTarget & psRecog exist */
	
	/** Increment ins/del/cor/sub parameters as necessary */
	for (i=0; i<nMatch; i++)
	{
		switch(piMatch[i])
		{
		case INSERTION:    if (piInsertions)    (*piInsertions)++;    bExactMatch=0; break;
		case DELETION:     if (piDeletions)     (*piDeletions)++;     bExactMatch=0; break;
		case CORRECT:      if (piCorrect)       (*piCorrect)++;                          break;
		case SUBSTITUTION: if (piSubstitutions) (*piSubstitutions)++; bExactMatch=0; break;
		}  /* switch*/
	}  /* for i */
	
	/** Free up the memory for the marks. */
	FNX_FREE(piMatch);
	
	return bExactMatch;
}  /* MatchStrings */

#ifdef ONEALIGN_PROJECT
/*FUNCTION_HEADER**********************
 * NAME:		;main (onealign)
 * DESC: 	Tell how many ins/del/cor/sub there are between two strings.
 * IN:		command-line arguments: "reference sentence" "hypothesized sentence"
 * OUT:		The two strings are printed one above each other, with corresponding
 *          words lined up.  Insertions and deletions have "####" as place-holders.
 *          Errors are shown in upper-case, while correct words are in lower-case.
 * RETURN:	n/a
 * NOTES:	
*END_HEADER***************************/
int main(int argc, char *argv[])
{
	
	char **psTarget, **psRecog;
	int  iNumTarget, iNumRecog;
	int  iInsertions, iDeletions, iCorrect, iSubstitutions;
	char *sTarget, *sRecog;
	
	/* parse the command line and set options or print usages */
	if(argc != 3) 
	{
		FNX_FPRINTF(stderr,"Usage: %s \"Target/reference sentence\" \"Recognized/hypothesized sentence\"\n", argv[0]);
		exit(1);
	}
	/* Convert the input sentence strings into arrays of word strings */
	psTarget = SplitString(argv[1],&iNumTarget);
	psRecog  = SplitString(argv[2],&iNumRecog);
	/* Initialize the stats to 0 */
	iInsertions = iDeletions = iCorrect = iSubstitutions = 0;
	/* Do DP */
	MatchStrings(psTarget, iNumTarget, psRecog, iNumRecog, 
		&iInsertions, &iDeletions, &iCorrect, &iSubstitutions, &sTarget, &sRecog);
	/* Print target & recognized sentence */
	FNX_PRINTF("%s\n%s\n\n",sTarget, sRecog);
	return 0;
}  /* main */
#endif

