/*C_HEADER_FILE****************************************************************
FILE			:	FnxLtsRules2Code.c
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
#include "FnxLtsRulesEngine.h"
#include <stdlib.h>
#include <stdio.h>		// printf
#include <memory.h>		// memset
#include <string.h>		// strchr

/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void WriteFileHeader(FILE *fp, char *sLang)
{
	fprintf(fp, "/*C_HEADER_FILE****************************************************************\n");
	fprintf(fp, "FILE			:	Fnx%sLtsRules.c\n", sLang);
	fprintf(fp, "DESC			:	Letter-to-sound rules for %s\n", sLang);
	fprintf(fp, "TABS			:	4\n");
	fprintf(fp, "OWNER			:	Fonix\n");
	fprintf(fp, "DATE CREATED	:	\n\n");
	fprintf(fp, "(C) Copyright 2005 All rights reserved.\n");
	fprintf(fp, "This is an unpublished work, and is confidential and proprietary: \n");
	fprintf(fp, "technology and information of fonix corporation.  No part of this\n");
	fprintf(fp, "code may be reproduced, used or disclosed without written consent of \n");
	fprintf(fp, "fonix corporation in each and every instance.\n\n");
	fprintf(fp, "	  $Date:  $\n");
	fprintf(fp, "	  $Revision:  $\n\n");
	fprintf(fp, "*END_HEADER*******************************************************************/\n");
	fprintf(fp, "#include \"FnxLtsRulesEngine.h\"\n\n");
}

/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int ParseArrayOfStrings(char *sString, char ***ppsArray)
{
	char
		**psArray,
		*sTok;
	int
		i,
		nStrs=0;

	sTok = strtok(sString, " ");
	while( sTok && *sTok != ';' )
	{
		nStrs++;
		sTok = strtok(NULL, " ");
	}

	if( nStrs == 0 )
		return 0;

	psArray = (char **)calloc(nStrs, sizeof(char *));
	sTok = sString;
	for(i=0; i<nStrs; i++)
	{
		psArray[i] = _strdup(sTok);
		sTok += strlen(sTok)+1;
		while( *sTok == 0x00 )
			sTok++;
	}

	if( ppsArray )
		*ppsArray = psArray;
	
	return nStrs;
}

/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int GetStrings(char *sBuf, char **psStrings)
{
	char *pc;
	int	
		i,
		iString=0;

	if( sBuf == NULL || psStrings == NULL )
		return 0;

	for( pc=sBuf, i=0; *pc; pc++ )
	{
		if( (i==0 && *pc == 0x00) ||
			(*pc == '/' && *(pc+1) == '/') )		// ignore anything after the comment delimiters
			break;

		if( *pc == '"' )				// Suck up a quote delimited string
		{
			pc++;
			i=1;
			psStrings[iString][0] = '"';
			while( *pc && *pc != '"' && *pc != '\t' )
			{
				if( *pc != '\\' )
				{
					psStrings[iString][i++] = *pc;
				}
				pc++;
			}
			psStrings[iString][i++] = '"';		// null terminate string
			psStrings[iString][i] = 0x00;		// null terminate string
			iString++;
		}
		else if( *pc != ' ' && *pc != '\t' )	// suck up a non-quote delimited word
		{
			i=1;
			psStrings[iString][0] = '"';
			while( *pc && *pc != ' ' && *pc != '\t')
			{
				psStrings[iString][i++] = *pc;
				pc++;
			}		
			psStrings[iString][i++] = '"';		// null terminate string
			psStrings[iString][i] = 0x00;		// null terminate string
			iString++;
		}
	}

	for(i=0; i<iString; i++)
	{
		if( strstr(psStrings[i], "Anything") )
		{
			strcpy(psStrings[i], "\"\"");
		}
		else if( strstr(psStrings[i], "Nothing") )
		{
			strcpy(psStrings[i], "\" \"");
		}
		else if( strstr(psStrings[i], "Silent") )
		{
			strcpy(psStrings[i], "\"\"");
		}
		else if( strstr(psStrings[i], "Pause") )
		{
			strcpy(psStrings[i], "\" \"");
		}
	}

	return iString;

}

typedef struct _tagLtsRule
{
	char
		sLeft[64],
		sCntr[64],
		sRight[64],
		sPron[128];
	struct _tagLtsRule *pNext;
}LTSRULE;

typedef struct _tagLtsRuleSet
{
	char
		sName[32];
	struct LTSRULE *pRule;
	struct _tagLtsRuleSet *pNext;
}LTSRULESET;

/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
Graph2PhonPtr ReadRuleFile(char *sRuleFile)
{
	char
		*pc,
		*sTok,
		sTmp[256],
		sBuf[512];
	char
		**psStrings;
	int
		i,
		nRuleSets=0;
	FILE
		*fp;
	Graph2PhonPtr
		pLtsRules;
	LTSRULESET
		*pLtsRuleSetHead=NULL,
		*pSet;
	LTSRULE
		*pRule;

	if( (fp = fopen(sRuleFile, "rt")) == NULL )
		return NULL;

	pLtsRules = (Graph2PhonPtr)calloc(1, sizeof(GRAPH2PHON));
	psStrings = (char **)calloc(8, sizeof(char *));
	for(i=0; i<8; i++)
		psStrings[i] = (char *)calloc(128, sizeof(char));

	while( fgets(sBuf, 512, fp) )
	{
		if( (sBuf[0] == '/' && sBuf[1] == '/') ||			// comment line don't process
			(sBuf[0] == '*' && sBuf[1] == '*') ||			//   ditto
			sBuf[0] == '\r' ||								// empty line
			sBuf[0] == '\n' )								//   ditto
			continue;

		if( (pc = strchr(sBuf, '\r')) ||					// strip off the trailing newline
			(pc = strchr(sBuf, '\n')) )
			*pc = 0x00;

		if( sBuf[0] == ';' )								// process a data group
		{
			if( (pc = strchr(sBuf, ':')) == NULL )
				continue;

			pc++;
			sTmp[0] = ' ';
			for(i=1; i<256 && *pc; pc++)
			{
				if( *pc != ' ' &&
					*pc != ';' )
					sTmp[i++] = *pc;
			}
			sTmp[i] = 0x00;

			if( strstr(sBuf, "letters:") )
			{
				pLtsRules->pRuleIndex = _strdup(sTmp);
				pLtsRules->sLetters = _strdup(&sTmp[1]);
			}
			else if( strstr(sBuf, "numbers:") )
				pLtsRules->sNumbers = _strdup(&sTmp[1]);
			else if( strstr(sBuf, "vowels:") )
				pLtsRules->sVowels = _strdup(&sTmp[1]);
			else if( strstr(sBuf, "vowels_front:") )
				pLtsRules->sVowels_f = _strdup(&sTmp[1]);
			else if( strstr(sBuf, "consonants:") )
				pLtsRules->sConsonants = _strdup(&sTmp[1]);
			else if( strstr(sBuf, "consonants_voiced:") )
				pLtsRules->sConsonants_v = _strdup(&sTmp[1]);
			else if( strstr(sBuf, "nasals:") )
				pLtsRules->sNasals = _strdup(&sTmp[1]);
			else if( strstr(sBuf, "endings:") != NULL &&
					 strstr(sBuf, "none") == NULL )
			{
				pc = strchr(sBuf, ':') + 1;
				pLtsRules->nEndingsList = ParseArrayOfStrings(pc, &pLtsRules->psEndingsList);
			}
			else if( strstr(sBuf, "suffixes:") != NULL &&
					 strstr(sBuf, "none") == NULL )
			{
				pc = strchr(sBuf, ':') + 1;
				pLtsRules->nSuffixList = ParseArrayOfStrings(pc, &pLtsRules->psSuffixList);
			}
			else if( strstr(sBuf, "output:") != NULL &&
					 strstr(sBuf, "none") == NULL )
			{
				pc = strchr(sBuf, ':') + 1;
				pLtsRules->nOutputList = ParseArrayOfStrings(pc, &pLtsRules->psOutputList);
			}
		}	// parse "; data: ..."
		else if( (pc = strstr(sBuf, "Rule:")) != NULL ||				// Found the start of a Rule set
				 (pc = strstr(sBuf, "rule:")) != NULL )
		{
			if( pLtsRuleSetHead == NULL )
			{
				pLtsRuleSetHead = pSet = (LTSRULESET *)calloc(1, sizeof(LTSRULESET));
			}
			else
			{
				pSet->pNext = (LTSRULESET *)calloc(1, sizeof(LTSRULESET));
				pSet = pSet->pNext;
			}
			// Get the rule name
			pc += 5;
			if( (sTok = strtok(pc, " ")) != NULL )
			{
				strcpy(pSet->sName, sTok);
			}
			nRuleSets++;
			pRule = NULL;
		}
		else
		{
			if( GetStrings(sBuf, psStrings) == 4 )
			{
				if( pSet->pRule == NULL )
				{
					pSet->pRule = pRule = (LTSRULE *)calloc(1, sizeof(LTSRULE));
				}
				else
				{
					pRule->pNext = (LTSRULE *)calloc(1, sizeof(LTSRULE));
					pRule = pRule->pNext;
				}
				strcpy(pRule->sLeft, psStrings[0]);
				strcpy(pRule->sCntr, psStrings[1]);
				strcpy(pRule->sRight, psStrings[2]);
				strcpy(pRule->sPron, psStrings[3]);
			}
		}
	}

	pLtsRules->pPhoneticRules = (PhoneticRule *)pLtsRuleSetHead;
	return pLtsRules;
}

/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void WriteRules(FILE *fp, Graph2PhonPtr pLtsRules, char *sLang)
{
	int 
		i,
		nSets=0,
		nRules=0;
	LTSRULESET
		*pSet;
	LTSRULE
		*pRule;

	if( fp == NULL || pLtsRules == NULL )
		return;

	nSets = (int)strlen(pLtsRules->pRuleIndex);
	pLtsRules->piRuleIndex = (int *)calloc(nSets, sizeof(int));
	for(pSet=(LTSRULESET *)pLtsRules->pPhoneticRules, i=0; pSet; pSet=pSet->pNext)
	{
		pLtsRules->piRuleIndex[i++] = nRules;
		for(pRule=pSet->pRule; pRule; pRule=pRule->pNext)
		{
			nRules++;
		}
	}
	
	fprintf(fp, "const char s%sRuleIndex[]  = \"%s\";\n", sLang, pLtsRules->pRuleIndex);
	fprintf(fp, "const char s%sLetters[]    = \"%s\";\n", sLang, pLtsRules->sLetters);
	fprintf(fp, "const char s%sNumbers[]    = \"%s\";\n", sLang, pLtsRules->sNumbers);
	fprintf(fp, "const char s%sVowels[]     = \"%s\";\n", sLang, pLtsRules->sVowels);
	fprintf(fp, "const char s%sVowels_f[]   = \"%s\";\n", sLang, pLtsRules->sVowels_f);
	fprintf(fp, "const char s%sConsonants[] = \"%s\";\n", sLang, pLtsRules->sConsonants);
	fprintf(fp, "const char s%sConsonants_v[]= \"%s\";\n", sLang, pLtsRules->sConsonants_v);
	fprintf(fp, "const char s%sNasals[]     = \"%s\";\n", sLang, pLtsRules->sNasals);

	fprintf(fp, "const char *ps%sOutputList[]= {\n", sLang);
	for(i=0; i<pLtsRules->nOutputList; i++)
	{
		if( i==0 )
			fprintf(fp, "\t\"%s\", ", pLtsRules->psOutputList[i]);
		else if( i<pLtsRules->nOutputList-1 ) 
			fprintf(fp, "\"%s\", ", pLtsRules->psOutputList[i]);
		else
			fprintf(fp, "\"%s\"", pLtsRules->psOutputList[i]);

		if( (i+1)%10 == 0 )
			fprintf(fp, "\n\t");
	}
	fprintf(fp, "};\n\n");

	fprintf(fp, "const int n%sOutputList    = %d;\n\n", sLang, pLtsRules->nOutputList);

	fprintf(fp, "const int pi%sRuleIndex[]	= {\n", sLang);
	for(i=0; i<nSets; i++)
	{
		if( i==0 )
			fprintf(fp, "\t%d, ", pLtsRules->piRuleIndex[i]);
		else if( i<nSets-1 )
			fprintf(fp, "%d, ", pLtsRules->piRuleIndex[i]);
		else
			fprintf(fp, "%d", pLtsRules->piRuleIndex[i]);


		if( (i+1)%10 == 0 )
			fprintf(fp, "\n\t");
	}
	fprintf(fp, "};\n\n");

	fprintf(fp, "const PhoneticRule p%sPhoneticRules[] = {\n", sLang);
	for(pSet=(LTSRULESET *)pLtsRules->pPhoneticRules, i=0; pSet; pSet=pSet->pNext)
	{
		fprintf(fp, "\t// Rule: %s\n", pSet->sName);
		for(pRule=pSet->pRule; pRule; pRule=pRule->pNext)
		{
			fprintf(fp, "\t{%s, \t%s, \t%s, \t%s}%c\n", 
				pRule->sLeft,
				pRule->sCntr,
				pRule->sRight,
				pRule->sPron,
				!pSet->pNext && !pRule->pNext ? ' ' : ',' );
		}
	}
	fprintf(fp, "};\n\n");


}

/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void WriteInitTermFuncs(FILE *fp, char *sLang)
{
	fprintf(fp, "int Initialize(void *pVoid)\n");
	fprintf(fp, "{\n");
	fprintf(fp, "	Graph2PhonPtr pLtsRules		= (Graph2PhonPtr)pVoid;\n\n");
	fprintf(fp, "	pLtsRules->pRuleIndex		= s%sRuleIndex;\n", sLang);
	fprintf(fp, "	pLtsRules->sLetters			= s%sLetters;\n", sLang);
	fprintf(fp, "	pLtsRules->sNumbers			= s%sNumbers;\n", sLang);
	fprintf(fp, "	pLtsRules->sVowels			= s%sVowels;\n", sLang);
	fprintf(fp, "	pLtsRules->sVowels_f		= s%sVowels_f;\n", sLang);
	fprintf(fp, "	pLtsRules->sConsonants		= s%sConsonants;\n", sLang);
	fprintf(fp, "	pLtsRules->sConsonants_v	= s%sConsonants_v;\n", sLang);
	fprintf(fp, "	pLtsRules->sNasals			= s%sNasals;\n", sLang);
	fprintf(fp, "	pLtsRules->psOutputList		= ps%sOutputList;\n", sLang);
	fprintf(fp, "	pLtsRules->nOutputList		= n%sOutputList;\n", sLang);
	fprintf(fp, "	pLtsRules->piRuleIndex		= pi%sRuleIndex;\n", sLang);
	fprintf(fp, "	pLtsRules->pPhoneticRules	= p%sPhoneticRules;\n\n", sLang);
	fprintf(fp, "	return 0;\n");
	fprintf(fp, "}\n\n");

	fprintf(fp, "int Terminate(void *pVoid)\n");
	fprintf(fp, "{\n");
	fprintf(fp, "	Graph2PhonPtr pLtsRules = (Graph2PhonPtr)pVoid;\n\n");
	fprintf(fp, "	memset(pLtsRules, 0, sizeof(GRAPH2PHON));\n\n");
	fprintf(fp, "	return 0;\n");
	fprintf(fp, "}\n");
}

/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void PrintUsage(void)
{
	printf("FnxLtsRules2Code - application to read a Letter-to-sound rules file and create a compilable version.\n");
	printf("\nUsage: FnxLtsRules2Code.exe <rules file> <out file> <Lang>\n");
	printf("\t\t<rules file> - Letter-to-sound rules file\n");
	printf("\t\t<out file>   - output path and filename\n");
	printf("\t\t<Lang>       - 2 letter language identifier (eg. Kr, Sp, La)\n");

}

/*FUNCTION_HEADER**********************
 * NAME:	;
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int main(int argc, char **argv)
{
	char 
		*sInfile,	//	= "C:\\AsrCoreTech\\Dictionary\\Korean\\KoreanRulesFBF.txt",
		*sOutfile,	//	= ".\\KrLtsRules.c",
		*sLang;		//	= "Kr";
	Graph2PhonPtr	
		pLtsRules;
	FILE 
		*fp;

	if( argc != 4 )
	{
		PrintUsage();
		return 1;
	}

	sInfile = argv[1];
	sOutfile = argv[2];
	sLang = argv[3];

	if( (fp = fopen(sOutfile, "wt")) == NULL )
	{
		printf("Error: Can't open output file %s\n", sOutfile);
		return 1;
	}

	if( strlen(sLang) > 2 )
	{
		printf("Warning: The language id <%s> should only be 2 characters long.\n", sLang);
	}

	printf("Working: Writing file %s ... ", sOutfile);
	WriteFileHeader(fp, sLang);
	if( (pLtsRules = ReadRuleFile(sInfile)) != NULL )
	{
		WriteRules(fp, pLtsRules, sLang);
		WriteInitTermFuncs(fp, sLang);
		printf("Done\n");
	}
	else
	{
		printf("\nError: Can't read the rules file %s\n", sInfile);
	}
	fclose(fp);

	return 0;
}