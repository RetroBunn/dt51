/*C_HEADER_FILE****************************************************************
FILE			:	CodePageConv.c
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
//#include <stdlib.h> //moved to port.h for each platform MLT 01/24/06
//#include <stdio.h> //moved to port.h for each platform MLT 01/24/06
//#include <string.h> //moved to port.h for each platform MLT 01/24/06
#include "port.h"
#include "CodePageConv.h"
#include "MergedCodeTable.h"

#ifdef UNONSEI
extern int err_count;
#endif

static CODE_TYPE eSort;

/*FUNCTION_HEADER**********************
 * NAME:	;Utf16Cmp
 * DESC: 	Sort the Code Table by the Unicode values
 * IN:		arg1 - pointer to structure
			arg2 - ditto
 * OUT:		none
 * RETURN:	0 if they match, 1 if arg1 > arg2, -1 if arg1 < arg2
 * NOTES:	
 *END_HEADER***************************/
int Utf16Cmp(const void *arg1, const void *arg2)
{
	CODE_TRANSL p1 = *(CODE_TRANSL *)arg1, 
				p2 = *(CODE_TRANSL *)arg2;

	if( p1.utf16 == p2.utf16 )		
		return 0;
	else if( p1.utf16 > p2.utf16 )	
		return 1;
	else	
		return -1;
}
int SjisCmp(const void *arg1, const void *arg2)
{
	CODE_TRANSL p1 = *(CODE_TRANSL *)arg1, 
				p2 = *(CODE_TRANSL *)arg2;

	if( p1.sjis == p2.sjis )		
		return 0;
	else if( p1.sjis > p2.sjis )	
		return 1;
	else	
		return -1;
}
int EucCmp(const void *arg1, const void *arg2)
{
	CODE_TRANSL p1 = *(CODE_TRANSL *)arg1, 
				p2 = *(CODE_TRANSL *)arg2;

	if( p1.euc == p2.euc )		
		return 0;
	else if( p1.euc > p2.euc )	
		return 1;
	else	
		return -1;
}

/*FUNCTION_HEADER**********************
 * NAME:	;Utf16Find
 * DESC: 	Find an entry with a given UTF16 value
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int Utf16Find(const void *arg1, const void *arg2)
{
	unsigned short p1 = *(unsigned short *)arg1;
	CODE_TRANSL	   p2 = *(CODE_TRANSL *)arg2;

	if( p1 == p2.utf16 )
		return 0;
	else if( p1 > p2.utf16 )
		return 1;
	else
		return -1;
}

int SjisFind(const void *arg1, const void *arg2)
{
	unsigned short p1 = *(unsigned short *)arg1;
	CODE_TRANSL	   p2 = *(CODE_TRANSL *)arg2;

	if( p1 == p2.sjis )
		return 0;
	else if( p1 > p2.sjis )
		return 1;
	else
		return -1;
}

int EucFind(const void *arg1, const void *arg2)
{
	unsigned short p1 = *(unsigned short *)arg1;
	CODE_TRANSL	   p2 = *(CODE_TRANSL *)arg2;

	if( p1 == p2.euc )
		return 0;
	else if( p1 > p2.euc )
		return 1;
	else
		return -1;
}

/*FUNCTION_HEADER**********************
 * NAME:	;Convert
 * DESC: 	Convert a character from one code page to another
 * IN:		code - inpute character
			eIn  - input type of code
			eOut - output type
 * OUT:		none
 * RETURN:	converted character
 * NOTES:	
 *END_HEADER***************************/
unsigned short Convert(unsigned short code, CODE_TYPE eIn, CODE_TYPE eOut)
{
	int nTbl = sizeof(pCodeTable) / sizeof(CODE_TRANSL);
	void *pVoid;
	CODE_TRANSL cd;

	// Make sure that we are sorted by the input type
	if( eSort != eIn )
	{
		switch(eIn)
		{
			case eUtf16:
				qsort((void *)pCodeTable, nTbl, sizeof(CODE_TRANSL), Utf16Cmp);
				pVoid = bsearch(&code, (void *)pCodeTable, nTbl, sizeof(CODE_TRANSL), Utf16Find);
				break;
			case eSjis:
				qsort((void *)pCodeTable, nTbl, sizeof(CODE_TRANSL), SjisCmp);
				pVoid = bsearch(&code, (void *)pCodeTable, nTbl, sizeof(CODE_TRANSL), SjisFind);
				break;
			case eEuc:
				qsort((void *)pCodeTable, nTbl, sizeof(CODE_TRANSL), EucCmp);
				pVoid = bsearch(&code, (void *)pCodeTable, nTbl, sizeof(CODE_TRANSL), EucFind);
				break;
			default:
				return code;
		}
		eSort = eIn;
	}

	// Find the input code
	switch(eIn)
	{
		case eUtf16:
			pVoid = bsearch(&code, (void *)pCodeTable, nTbl, sizeof(CODE_TRANSL), Utf16Find);
			break;
		case eSjis:
			pVoid = bsearch(&code, (void *)pCodeTable, nTbl, sizeof(CODE_TRANSL), SjisFind);
			break;
		case eEuc:
			pVoid = bsearch(&code, (void *)pCodeTable, nTbl, sizeof(CODE_TRANSL), EucFind);
			break;
		default:
			return code;
	}

	// Return the translated output code
	if( pVoid != NULL )
	{
		cd = *(CODE_TRANSL *)pVoid;
		switch(eOut)
		{
			case eUtf16:
				return cd.utf16;
			case eSjis:
				return cd.sjis;
			case eEuc:
				return cd.euc;
			default:
				return code;
		}
	}
#ifdef UNONSEI
	else
	{
		err_count++;
		fprintf(stderr,"unknown EUC=0x%04X\n",code);
	}
#endif
	return code;
}

/*FUNCTION_HEADER**********************
 * NAME:	;u2e
 * DESC: 	Convert a string from Unicode to EUC
 * IN:		str
 * OUT:		str
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void u2e(unsigned short *str)
{
	unsigned short *pc;

	for( pc = str; *pc; pc++ )
	{
		*pc = Convert(*pc, eUtf16, eEuc);
	}
}
void u2s(unsigned short *str)
{
	unsigned short *pc;

	for( pc = str; *pc; pc++ )
	{
		*pc = Convert(*pc, eUtf16, eSjis);
	}
}
void s2e(unsigned short *str)
{
	unsigned short *pc;

	for( pc = str; *pc; pc++ )
	{
		*pc = Convert(*pc, eSjis, eEuc);
	}
}
void s2u(unsigned short *str)
{
	unsigned short *pc;

	for( pc = str; *pc; pc++ )
	{
		*pc = Convert(*pc, eSjis, eUtf16);
	}
}
void e2u(unsigned short *str)
{
	unsigned short *pc;

	for( pc = str; *pc; pc++ )
	{
		*pc = Convert(*pc, eEuc, eUtf16);
	}
}
void e2s(unsigned short *str)
{
	unsigned short *pc;

	for( pc = str; *pc; pc++ )
	{
		*pc = Convert(*pc, eEuc, eSjis);
	}
}

#ifdef CODE_PAGE_CONV_PROJECT
int main(int argc, char **argv)
{
	int i;
	char *sInFile=NULL, *sOutFile=NULL;
	CODE_TYPE eIn, eOut;
	unsigned short str[500], *pus;
	//char cstr[500];
	FILE *fpIn, *fpOut;

	memset(str, 0, 500*sizeof(short));
	for( i=1; i<argc; i++ )
	{
		if( stricmp(argv[i], "-i") == 0 )
		{
			sInFile = argv[++i];
		}
		else if( stricmp(argv[i], "-o") == 0 )
		{
			sOutFile = argv[++i];
		}
		else if( stricmp(argv[i], "-ue") == 0 )
		{
			eIn = eUtf16;	eOut = eEuc;
		}
		else if( stricmp(argv[i], "-us") == 0 )
		{
			eIn = eUtf16;	eOut = eSjis;
		}
		else if( stricmp(argv[i], "-eu") == 0 )
		{
			eIn = eEuc;	eOut = eUtf16;
		}
		else if( stricmp(argv[i], "-es") == 0 )
		{
			eIn = eEuc;	eOut = eSjis;
		}
		else if( stricmp(argv[i], "-su") == 0 )
		{
			eIn = eSjis;	eOut = eUtf16;
		}
		else if( stricmp(argv[i], "-se") == 0 )
		{
			eIn = eSjis;	eOut = eEuc;
		}
	}

	if( sInFile == NULL || sOutFile == NULL || eIn == eOut )
		return 0;

	// Open the input file
	if( (fpIn = FNX_FOPEN(sInFile, "rb")) == NULL )
		return 0;

	// Open the output file
	if( (fpOut = FNX_FOPEN(sOutFile, "wb")) == NULL )
		return 0;

	// Read in wide characters
	FNX_FREAD(str, 500, sizeof(short), fpIn);
	FNX_FCLOSE(fpIn);

//	if( (fpIn = FNX_FOPEN(sInFile, "rb")) == NULL )
//		return 0;
//
//	FNX_FREAD(cstr, 500, sizeof(char), fpIn);
//	FNX_FCLOSE(fp);

	// Translate to the new code page
	switch(eIn)
	{
		case eUtf16:
			if( eOut == eSjis )		u2s(&str[1]);
			else					u2e(&str[1]);
			break;
		case eSjis:
			if( eOut == eUtf16 )	s2u(&str[1]);
			else					s2e(&str[1]);
			break;
		case eEuc:
			if( eOut == eUtf16 )	e2u(&str[1]);
			else					e2s(&str[1]);
			break;
		default:
			return 0;
	}

	for( pus=&str[1]; *pus; pus++ )
	{
		FNX_FWRITE(pus, 1, sizeof(short), fpOut);
	}
	FNX_FCLOSE(fpOut);

#if 0
	// Put it back to the way it started
	switch(eOut)
	{
		case eUtf16:
			if( eIn == eSjis )		u2s(&str[1]);
			else					u2e(&str[1]);
			break;
		case eSjis:
			if( eIn == eUtf16 )		s2u(&str[1]);
			else					s2e(&str[1]);
			break;
		case eEuc:
			if( eIn == eUtf16 )		e2u(&str[1]);
			else					e2s(&str[1]);
			break;
		default:
			return 0;
	}
#endif

#if 0	// I used this section to create the merged Utf16, Sjis, Euc table
	int i;
	int nS2U,
		nE2U;
	void *pVoid;
	CODE_TRANSL su, eu;

	nS2U = sizeof(pSjisUnicode) / sizeof(CODE_TRANSL);
	qsort((void *)pSjisUnicode, nS2U, sizeof(CODE_TRANSL), W2CodeCmp);

	nE2U = sizeof(pEucUnicode) / sizeof(CODE_TRANSL);
	qsort((void *)pEucUnicode, nE2U, sizeof(CODE_TRANSL), W2CodeCmp);

	for( i=0; i<nS2U; i++ )
	{
		if( (pVoid = bsearch(&(pSjisUnicode[i].w2), (void *)pSjisUnicode, nS2U, sizeof(CODE_TRANSL), W2CodeFind)) != NULL )
		{
			su = *(CODE_TRANSL *)pVoid;

			if( (pVoid = bsearch(&(pSjisUnicode[i].w2), (void *)pEucUnicode, nE2U, sizeof(CODE_TRANSL), W2CodeFind)) != NULL )
			{
				eu = *(CODE_TRANSL *)pVoid;

				FNX_PRINTF("\t{0x%04x, 0x%04x, 0x%04x},\n", su.w2, su.w1, eu.w1);
			}
			else
				FNX_PRINTF("Couldn't find %04x in the EUC table\n", pSjisUnicode[i].w2);
		}
		else
			FNX_PRINTF("Couldn't find %04x in the SJIS table\n", pSjisUnicode[i].w2);
	
	}
#endif

	return 0;
}
#endif