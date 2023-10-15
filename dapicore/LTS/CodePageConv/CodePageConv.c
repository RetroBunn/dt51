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
#include "port.h"
#include "CodePageConv.h"
#include "CodeConvTable.h"

#if defined CASIO_SH3
int
		bSortBySjis,
		bSortByEuc,
		bSortByKsc,
		bSortByGbk;

/*FUNCTION_HEADER**********************
 * NAME:	;InitBsortGlobals
 * DESC: 	Function used to initialize bsort globals
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void InitBsortGlobals()
{
		bSortBySjis=1;
		bSortByEuc=1;
		bSortByKsc=1;
		bSortByGbk=1;
}
#endif //CASIO_SH3

/*FUNCTION_HEADER**********************
 * NAME:	;CodeCmp
 * DESC: 	Function used to sort a **pCode2Utf table by the Code values in column 0
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int CodeCmp(const void *arg1, const void *arg2)
{
	CODE_CONV 
		p1 = *(CODE_CONV *)arg1, 
		p2 = *(CODE_CONV *)arg2;

	if( p1.code == p2.code )		
		return 0;
	else if( p1.code > p2.code )	
		return 1;
	else	
		return -1;
}

/*FUNCTION_HEADER**********************
 * NAME:	;CodeCmp
 * DESC: 	Function used to sort a **pCode2Utf table by the Unicode values in column 1
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int UtfCmp(const void *arg1, const void *arg2)
{
	CODE_CONV 
		p1 = *(CODE_CONV *)arg1, 
		p2 = *(CODE_CONV *)arg2;

	if( p1.utf == p2.utf )		
		return 0;
	else if( p1.utf > p2.utf )	
		return 1;
	else	
		return -1;
}

/*FUNCTION_HEADER**********************
 * NAME:	;CodeFind
 * DESC: 	Function used to find a code value in the table **pCode2Utf
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int CodeFind(const void *arg1, const void *arg2)
{
	unsigned short p1 = *(unsigned short *)arg1;
	CODE_CONV	   p2 = *(CODE_CONV *)arg2;

	if( p1 == p2.code )
		return 0;
	else if( p1 > p2.code )
		return 1;
	else
		return -1;
}
/*FUNCTION_HEADER**********************
 * NAME:	;UtfFind
 * DESC: 	Function used to find a unicode value in the table **pCode2Utf
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int UtfFind(const void *arg1, const void *arg2)
{
	unsigned short p1 = *(unsigned short *)arg1;
	CODE_CONV	   p2 = *(CODE_CONV *)arg2;

	if( p1 == p2.utf )
		return 0;
	else if( p1 > p2.utf )
		return 1;
	else
		return -1;
}

/*FUNCTION_HEADER**********************
 * NAME:	;ConvertCode
 * DESC: 	Convert an input string from one code type to another.
			Typically this will be used to convert to Unicode
 * IN:		str - input data
			eIn - input code type
			eOut - output code type
 * OUT:		
 * RETURN:	number of characters converted on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int ConvertCode(unsigned short *str, CODE_TYPE eIn, CODE_TYPE eOut)
{
	unsigned short 
		*pc;
	unsigned int
		nRows;
	void 
		*pVoid;
	CODE_CONV
		cd,
		*pCode2Utf;
	int
		bNeedsSort=0;

#ifndef CASIO_SH3
static int
		bSortBySjis = 1,
		bSortByEuc = 1,
		bSortByKsc = 1,
		bSortByGbk = 1;


#endif //CASIO_SH3
	if( eOut == eUtf16 )
	{
		bNeedsSort = 0;
		switch( eIn )
		{
			case eSjis:
				pCode2Utf = ppwSjis2Utf;
				nRows = sizeof(ppwSjis2Utf) / sizeof(CODE_CONV);
				if( bSortBySjis == 0 )
				{
					bNeedsSort = 1;
					bSortBySjis = 1;
				}
				break;
			case eEuc:	
				pCode2Utf = ppwEuc2Utf;
				nRows = sizeof(ppwEuc2Utf) / sizeof(CODE_CONV);
				if( bSortByEuc == 0 )
				{
					bNeedsSort = 1;
					bSortByEuc = 1;
				}
				break;
			case eKsc:	
				pCode2Utf = ppwKsc2Utf;
				nRows = sizeof(ppwKsc2Utf) / sizeof(CODE_CONV);
				if( bSortByKsc == 0 )
				{
					bNeedsSort = 1;
					bSortByKsc = 1;
				}
				break;
			case eGbk:	
				pCode2Utf = ppwGbk2Utf;
				nRows = sizeof(ppwGbk2Utf) / sizeof(CODE_CONV);
				if( bSortByGbk == 0 )
				{
					bNeedsSort = 1;
					bSortByGbk = 1;
				}

				break;
			default:
				return 0;		// Error
		}

		// Sort by Code column (0)
		if( bNeedsSort )
			qsort((void *)pCode2Utf, nRows, sizeof(short *), CodeCmp);

		for( pc = str; *pc; pc++ )
		{
			pVoid = (void *)FNX_BSEARCH(&(*pc), (void *)pCode2Utf, nRows, sizeof(unsigned short *), CodeFind);

			if( pVoid != NULL )
			{
				cd = *(CODE_CONV *)pVoid;
				*pc = cd.utf;
			}
		}
	}
	else if( eIn == eUtf16 )
	{
		bNeedsSort = 0;
		switch( eOut )
		{
			case eSjis:
				pCode2Utf = ppwSjis2Utf;
				nRows = sizeof(ppwSjis2Utf) / sizeof(CODE_CONV);
				if( bSortBySjis == 1 )
				{
					bNeedsSort = 1;
					bSortBySjis = 0;
				}
				break;
			case eEuc:	
				pCode2Utf = ppwEuc2Utf;
				nRows = sizeof(ppwEuc2Utf) / sizeof(CODE_CONV);
				if( bSortByEuc == 1 )
				{
					bNeedsSort = 1;
					bSortByEuc = 0;
				}
				break;
			case eKsc:	
				pCode2Utf = ppwKsc2Utf;
				nRows = sizeof(ppwKsc2Utf) / sizeof(CODE_CONV);
				if( bSortByKsc == 1 )
				{
					bNeedsSort = 1;
					bSortByKsc = 0;
				}
				break;
			case eGbk:	
				pCode2Utf = ppwGbk2Utf;
				nRows = sizeof(ppwGbk2Utf) / sizeof(CODE_CONV);
				if( bSortByGbk == 1 )
				{
					bNeedsSort = 1;
					bSortByGbk = 0;
				}
				break;
			default:
				return 0;		// Error
		}

		// Sort by unicode column (1)
		if( bNeedsSort )
			qsort((void *)pCode2Utf, nRows, sizeof(short *), UtfCmp);

		for( pc = str; *pc; pc++ )
		{
			pVoid = (void *)FNX_BSEARCH(&(*pc), (void *)pCode2Utf, nRows, sizeof(unsigned short *), UtfFind);

			if( pVoid != NULL )
			{
				cd = *(CODE_CONV *)pVoid;
				*pc = cd.code;
			}
		}	

	}

	return (pc - str);
}

/*FUNCTION_HEADER**********************
 * NAME:	;Sjis2Utf
 * DESC: 	convert a shift-jis stream into unicode
 * IN:		sSjis - 1 and 2 byte shift-jis characters
			nUtf - max length of wsUtf
 * OUT:		wsUtf - unicode string
 * RETURN:	number of characters in sSjis that were converted on success, 0 on failure
 * NOTES:
	Shift-JIS (SJIS) encoding scheme:
	The first byte of each character is used to determine the number of bytes for 
	that character. The values from 0x20 to 0x7F and from 0xA0 to 0xDF are used to 
	encode ASCII and Katakana characters, with exceptions. The positions from 
	0x81 to 0x9f and from 0xe0 to 0xfc are reserved for use as the first byte of 
	a multibyte character. The JISX0208 characters are mapped to the multibyte values 
	starting at 0x8140. The second byte of a multibyte character can have any value. 
 *END_HEADER***************************/
int Sjis2Utf(unsigned char *sSjis, wchar_t *wsUtf, int nUtf)
{
	unsigned char 
		*pc=NULL;
	int
		nRead=0;

	if( sSjis == NULL || wsUtf == NULL )
		return 0;

	// Copy Sjis characters into a wide character string.  This has to be done carefully
	// since some Sjis characters are single byte and some are multi-byte.
	for(pc = sSjis; *pc && nRead < nUtf; pc++)
	{
		if( 0x20 <= *pc && *pc <= 0x7f )			// single byte ascii
		{
			wsUtf[nRead++] = *pc;
		}
		else if( *pc == 0x0d )						// must have a \r\n pair
		{
			wsUtf[nRead++] = *pc;
			if( *(pc+1) != 0x0a )
				wsUtf[nRead++] = 0x0a;
		}
		else if( *pc == 0x0a )						// must have a \r\n pair
		{
			if( *(pc-1) != 0x0d )
				wsUtf[nRead++] = 0x0d;
			wsUtf[nRead++] = *pc;
		}
		else if( 0xa0 <= *pc && *pc <= 0xdf )		// single byte kana
		{
			wsUtf[nRead++] = *pc;
		}
		else if( (0x81 <= *pc && *pc <= 0x9f) ||	// first byte of 2 byte character
				 (0xe0 <= *pc && *pc <= 0xfc) )
		{
			wsUtf[nRead++] = (*pc << 8) + *(pc+1);
			pc++;
		}
	}
	wsUtf[nRead] = 0x00;		// null terminate

	ConvertCode(wsUtf, eSjis, eUtf16);

	return (pc-sSjis);			// number of characters converted
}


/*FUNCTION_HEADER**********************
 * NAME:	;Utf2Sjis
 * DESC: 	Convert unicode characters to Shift Jis
 * IN:		wsUtf - unicode string
			nSjis - maximum size of sSjis
 * OUT:		sSjis - shift jis string
 * RETURN:	number of characters converted
 * NOTES:	
 *END_HEADER***************************/
int Utf2Sjis(wchar_t *wsUtf, unsigned char *sSjis, int nSjis)
{
	unsigned char 
		*pc=NULL;
	wchar_t
		*pwc;
	int
		nRead=0;

	if( sSjis == NULL || wsUtf == NULL )
		return 0;

	ConvertCode(wsUtf, eUtf16, eSjis);

	// Copy Sjis characters into a wide character string.  This has to be done carefully
	// since some Sjis characters are single byte and some are multi-byte.
	for(pwc = wsUtf, pc=sSjis; *pwc && pc-sSjis < nSjis-2; pwc++)
	{
		if( ! (*pwc & 0xff00) )
		{
			*pc = (unsigned char)(*pwc & 0x00ff);
			pc++;
		}
		else
		{
			*pc = (unsigned char)((*pwc & 0xff00) >> 8);
			pc++;
			*pc = (unsigned char)(*pwc & 0x00ff);
			pc++;
		}
	}
	*pc = 0x00;		// null terminate

	return (pwc-wsUtf);			// number of characters converted
}


/*FUNCTION_HEADER**********************
 * NAME:	;IsSjis
 * DESC: 	Determine if character set is Shift-Jis
 * IN:		sSjis - input character stream
 * OUT:		
 * RETURN:	1 - yes, 0 - no
 * NOTES:	
 *END_HEADER***************************/
int IsSjis(unsigned char *sSjis)
{
	unsigned char 
		*pc;
	int
		nSjis=0;

	for(pc = sSjis; *pc ; pc++)
	{
		if( (0x20 <= *pc && *pc <= 0x7f) ||			// single byte ascii
			*pc == 0x0a || *pc == 0x0d )
		{
			nSjis++;
		}
		else if( 0xa0 <= *pc && *pc <= 0xdf )		// single byte kana
		{
			nSjis++;
		}
		else if( (0x81 <= *pc && *pc <= 0x9f) ||	// first byte of 2 byte character
				 (0xe0 <= *pc && *pc <= 0xfc) )
		{
			nSjis += 2;
			pc++;
		}
	}

	if( nSjis == pc-sSjis )
		return 1;
	else
		return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;Euc2Utf
 * DESC: 	convert a EUC-JP (Extended Unix Code) stream into unicode
 * IN:		sEuc - 1 and 2 byte shift-jis characters
			nUtf - max length of wsUtf
 * OUT:		wsUtf - unicode string
 * RETURN:	number of characters in sSjis that were converted on success, 0 on failure
 * NOTES:

	http://rikai.com/library/kanjitables/kanji_codes.euc.shtml

 *END_HEADER***************************/
int Euc2Utf(unsigned char *sEuc, wchar_t *wsUtf, int nUtf)
{
	unsigned char 
		*pc=NULL;
	int
		nRead=0;

	if( sEuc == NULL || wsUtf == NULL )
		return 0;

	// Copy Euc characters into a wide character string.  This has to be done carefully
	// since some Euc characters are single byte and some are multi-byte.
	for(pc = sEuc; *pc && nRead < nUtf; pc++)
	{
		if( 0x20 <= *pc && *pc <= 0x7f )			// single byte ascii
		{
			wsUtf[nRead++] = *pc;
		}
		else if( *pc == 0x0d )						// must have a \r\n pair
		{
			wsUtf[nRead++] = *pc;
			if( *(pc+1) != 0x0a )
				wsUtf[nRead++] = 0x0a;
		}
		else if( *pc == 0x0a )						// must have a \r\n pair
		{
			if( *(pc-1) != 0x0d )
				wsUtf[nRead++] = 0x0d;
			wsUtf[nRead++] = *pc;
		}
		else if( 0xa1 <= *pc && *pc <= 0xfe ) 		// first byte of 2 byte character
		{
			wsUtf[nRead++] = (*pc << 8) + *(pc+1);
			pc++;
		}
	}
	wsUtf[nRead] = 0x00;		// null terminate

	ConvertCode(wsUtf, eEuc, eUtf16);

	return (pc-sEuc);			// number of characters converted
}

/*FUNCTION_HEADER**********************
 * NAME:	;Utf2Euc
 * DESC: 	Convert unicode characters to Shift Jis
 * IN:		wsUtf - unicode string
			nEuc - maximum size of sEuc
 * OUT:		sEuc - Euc string
 * RETURN:	number of characters converted
 * NOTES:	
 *END_HEADER***************************/
int Utf2Euc(wchar_t *wsUtf, unsigned char *sEuc, int nEuc)
{
	unsigned char 
		*pc=NULL;
	wchar_t
		*pwc;
	int
		nRead=0;

	if( sEuc == NULL || wsUtf == NULL )
		return 0;

	ConvertCode(wsUtf, eUtf16, eEuc);

	for(pwc = wsUtf, pc=sEuc; *pwc && pc-sEuc < nEuc-2; pwc++)
	{
		if( ! (*pwc & 0xff00) )
		{
			*pc = (unsigned char)(*pwc & 0x00ff);			// some characters are single byte
			pc++;
		}
		else
		{
			*pc = (unsigned char)((*pwc & 0xff00) >> 8);	// others are 2-bytes
			pc++;
			*pc = (unsigned char)(*pwc & 0x00ff);
			pc++;
		}
	}
	*pc = 0x00;			// null terminate

	return (pwc-wsUtf);			// number of characters converted
}

/*FUNCTION_HEADER**********************
 * NAME:	;Gbk2Utf
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	number of characters converted
 * NOTES:	

	Properties of GB18030-2000 
	GB18030-2000 has the following significant properties: 

	It incorporates Unicode's CJK Unified Ideographs Extension A completely. 
	It provides code space for all used and unused code points of Unicode's plane 0 (BMP) and its 15 
	additional planes. While being a code- and character-compatible "superset" of GBK, GB18030-2000, 
	at the same time, intends to provide space for all remaining code points of Unicode. Thus, it 
	effectively creates a one-to-one relationship between parts of GB18030-2000 and Unicode's complete 
	encoding space. 
	In order to accomplish the Unihan incorporation and code space allocation for Unicode 3.0, 
	GB18030-2000 defines and applies a four-byte encoding mechanism. 

	GB18030-2000 encodes characters in sequences of one, two, or four bytes. The following are 
	valid byte sequences (byte values are hexadecimal): 

	Single-byte: 0x00-0x7f 
	Two-byte: 0x81-0xfe + 0x40-0x7e, 0x80-0xfe 
	Four-byte: 0x81-0xfe + 0x30-0x39 + 0x81-0xfe + 0x30-0x39 

	The single-byte portion applies the coding structure and principles of the standard GB 11383 
	(identical to ISO 4873:1986) by using the code points 0x00 through 0x7f. 

	The two-byte portion uses two eight-bit binary sequences to express a character. The code points 
	of the first (leading) byte range from 0x81 through 0xfe. The code points of the second (trailing) 
	byte ranges from 0x40 through 0x7e and 0x80 through 0xfe. 

	The four-byte portion uses the code points 0x30 through 0x39, which are vacant in GB 11383, as an 
	additional means to extend the two-byte encodings, thus effectively increasing the number of 
	four-byte codes to now include code points ranging from 0x81308130 through 0xfe39fe39. 

	GB18030-2000 has 1.6 million valid byte sequences, but there are only 1.1 million code points 
	in Unicode, so there are about 500,000 byte sequences in GB18030-2000 that are currently unassigned.

	http://developers.sun.com/dev/gadc/technicalpublications/articles/gb18030.html


 *END_HEADER***************************/
int Gbk2Utf(unsigned char *sGbk, wchar_t *wsUtf, int nUtf)
{
	unsigned char 
		*pc;
	int
		nRead=0;

	if( sGbk == NULL || wsUtf == NULL )
		return 0;

	// Copy Gbk characters into a wide character string.  This has to be done carefully
	// since some Sjis characters are single byte and some are multi-byte.
	for(pc = sGbk; *pc && nRead < nUtf; pc++)
	{
		if( *pc == 0x0d )									// must have a \r\n pair
		{
			wsUtf[nRead++] = *pc;
			if( *(pc+1) != 0x0a )
				wsUtf[nRead++] = 0x0a;
		}
		else if( *pc == 0x0a )								// must have a \r\n pair
		{
			if( *(pc-1) != 0x0d )
				wsUtf[nRead++] = 0x0d;
			wsUtf[nRead++] = *pc;
		}
		else if( 0x00 <= *pc && *pc <= 0x7f )				// single byte ascii
		{
			wsUtf[nRead++] = *pc;
		}
		else if( (0x81 <= *pc && *pc <= 0xfe) &&			// first byte of 2 byte character
				 ((0x40 <= *(pc+1) && *(pc+1) <= 0x7e) ||	// second byte of 2 byte character
				  (0x80 <= *(pc+1) && *(pc+1) <= 0xfe)) )
		{
			wsUtf[nRead++] = (*pc << 8) + *(pc+1);
			pc++;
		}
	}
	wsUtf[nRead] = 0x00;		// null terminate

	ConvertCode(wsUtf, eGbk, eUtf16);

	return (pc-sGbk);			// number of characters converted
}


/*FUNCTION_HEADER**********************
 * NAME:	;IsGbk
 * DESC: 	Determine if data is Gbk
 * IN:		sGbk - input character stream
 * OUT:		
 * RETURN:	1 - yes, 0 - no
 * NOTES:	
 *END_HEADER***************************/
int IsGbk(unsigned char *sGbk)
{
	unsigned char 
		*pc;
	int
		nGbk=0;

	// Copy Gbk characters into a wide character string.  This has to be done carefully
	// since some Sjis characters are single byte and some are multi-byte.
	for(pc = sGbk; *pc; pc++)
	{
		if( 0x00 <= *pc && *pc <= 0x7f )			// single byte ascii
		{
			nGbk++;
		}
		else if( (0x81 <= *pc && *pc <= 0xfe) &&			// first byte of 2 byte character
				 ((0x40 <= *(pc+1) && *(pc+1) <= 0x7e) ||	// second byte of 2 byte character
				  (0x80 <= *(pc+1) && *(pc+1) <= 0xfe)) )
		{
			nGbk += 2;
			pc++;
		}
		//	Four-byte: 0x81-0xfe + 0x30-0x39 + 0x81-0xfe + 0x30-0x39 
		else if( (0x81 <= *pc && *pc <= 0xfe) &&
				 (0x30 <= *(pc+1) && *(pc+1) <= 0x39) &&
				 (0x81 <= *(pc+2) && *(pc+2) <= 0xfe) &&
				 (0x30 <= *(pc+3) && *(pc+3) <= 0x39) )
		{
			nGbk += 4;
			pc += 3;
		}
	}

	if( nGbk == (pc-sGbk) )
		return 1;
	else
		return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;Ksc2Utf
 * DESC: 	Convert Korean characters to unicode
 * IN:		sKsc - Korean input buffer
			nUtf - max length of output
 * OUT:		wsUtf - Korean unicode characters
 * RETURN:	number of characters converted on success, 0 on failure
 * NOTES:	

	Unified Hangul Code
	UHC, or Extended Wansung, is a superset of  KS C 5601-1987, incorporating all the 
	Hangul characters of Johab.  It has an 8-bit encoding form with the following byte-ranges:

     Single-byte ASCII:       0x21-0x7E
     UHC first byte range:    0x81-0xFE
     UHC second byte ranges:  0x41-0x5A, 0x61-0x7A, 0x81-0xFE

	 http://zsigri.tripod.com/fontboard/cjk/ksc.html

 *END_HEADER***************************/
int Ksc2Utf(unsigned char *sKsc, wchar_t *wsUtf, int nUtf)
{
	unsigned char 
		*pc;
	int
		nRead=0;

	// Copy Ksc characters into a wide character string.  This has to be done carefully
	// since some Ksc characters are single byte and some are multi-byte.
	for(pc = sKsc; *pc && nRead < nUtf; pc++)
	{
		if( 0x20 <= *pc && *pc <= 0x7e )			// single byte ascii
		{
			wsUtf[nRead++] = *pc;
		}
		else if( *pc == 0x0d )						// must have a \r\n pair
		{
			wsUtf[nRead++] = *pc;
			if( *(pc+1) != 0x0a )
				wsUtf[nRead++] = 0x0a;
		}
		else if( *pc == 0x0a )						// must have a \r\n pair
		{
			if( *(pc-1) != 0x0d )
				wsUtf[nRead++] = 0x0d;
			wsUtf[nRead++] = *pc;
		}
		else if( (0x81 <= *pc && *pc <= 0xfe) &&			// first byte of 2 byte character
				 ((0x41 <= *(pc+1) && *(pc+1) <= 0x5a) ||	// second byte of 2 byte character
				  (0x61 <= *(pc+1) && *(pc+1) <= 0x7a) ||
				  (0x81 <= *(pc+1) && *(pc+1) <= 0xfe)) )
		{
			wsUtf[nRead++] = (*pc << 8) + *(pc+1);
			pc++;
		}
	}
	wsUtf[nRead] = 0x00;		// null terminate

	ConvertCode(wsUtf, eKsc, eUtf16);

	return (pc-sKsc);			// number of characters converted

}

/*FUNCTION_HEADER**********************
 * NAME:	;IsKsc
 * DESC: 	Determine if data is Unified Hangul Characters
 * IN:		sKsc - character stream
 * OUT:		
 * RETURN:	1 - yes, 0 - no
 * NOTES:	
 *END_HEADER***************************/
int IsKsc(unsigned char *sKsc)
{
	unsigned char 
		*pc;
	int
		nKsc=0;

	for(pc = sKsc; *pc; pc++)
	{
		if( (0x20 <= *pc && *pc <= 0x7e) ||			// single byte ascii
			*pc == 0x0a || *pc == 0x0d )			// need to account for carriage return / line feed
		{
			nKsc++;
		}
		else if( (0x81 <= *pc && *pc <= 0xfe) &&			// first byte of 2 byte character
				 ((0x41 <= *(pc+1) && *(pc+1) <= 0x5a) ||	// second byte of 2 byte character
				  (0x61 <= *(pc+1) && *(pc+1) <= 0x7a) ||
				  (0x81 <= *(pc+1) && *(pc+1) <= 0xfe)) )
		{
			nKsc += 2;
			pc++;
		}
	}
	
	if( nKsc == (pc-sKsc) )
		return 1;
	else
		return 0;

}

#ifdef CODE_PAGE_CONV_PROJECT
#include "MergedCodeTable.h"

void ConvertFile2Utf(char *sInFile, char *sOutFile)
{
	unsigned char 
		sBuf[512];
	wchar_t	
		wsBuf[512],
		wVal;
	int
		i,
		nSjis=0, nKsc=0, nGbk=0,
		nConverted;
	FILE 
		*fpIn,
		*fpOut;

	if( (fpIn = fopen(sInFile, "rb")) == NULL )
		return;

	if( (fpOut = fopen(sOutFile, "wb")) == NULL )
	{
		fclose(fpIn);
		return;
	}

	wVal = 0xfeff;
	FNX_FWRITE(&wVal, 1, sizeof(short), fpOut);

	while( fgets(sBuf, 512, fpIn) )
	{
		nSjis += IsSjis(sBuf);
		nKsc += IsKsc(sBuf);
		nGbk += IsGbk(sBuf);
	}

	fseek(fpIn, 0, SEEK_SET);

	while( fgets(sBuf, 512, fpIn) )
	{
		if( nSjis > 0 && nSjis > nKsc && nSjis > nGbk )
			nConverted = Sjis2Utf(sBuf, wsBuf, 512);
		else if( nGbk > 0 && nGbk > nSjis && nGbk > nKsc )
			nConverted = Gbk2Utf(sBuf, wsBuf, 512);
		else if( nKsc > 0 && nKsc > nSjis && nKsc > nGbk )
			nConverted = Ksc2Utf(sBuf, wsBuf, 512);

		for(i=0; i<nConverted; i++)
		{
			FNX_FWRITE(&wsBuf[i], 1, sizeof(wchar_t), fpOut);
		}

	}

	fclose(fpIn);
	fclose(fpOut);

}

#ifdef CREATE_TABLES
/*FUNCTION_HEADER**********************
 * NAME:	;Short0Cmp
 * DESC: 	Sort the Code Page Table by the Unicode values
 * IN:		arg1 - pointer to structure
			arg2 - ditto
 * OUT:		none
 * RETURN:	0 if they match, 1 if arg1 > arg2, -1 if arg1 < arg2
 * NOTES:	
 *END_HEADER***************************/
int Short0Cmp(const void *arg1, const void *arg2)
{
	unsigned short 
		*p1 = *(unsigned short **)arg1, 
		*p2 = *(unsigned short **)arg2;

	if( p1[0] == p2[0] )		
		return 0;
	else if( p1[0] > p2[0] )	
		return 1;
	else	
		return -1;
}
int Short1Cmp(const void *arg1, const void *arg2)
{
	unsigned short 
		*p1 = *(unsigned short **)arg1, 
		*p2 = *(unsigned short **)arg2;

	if( p1[1] == p2[1] )		
		return 0;
	else if( p1[1] > p2[1] )	
		return 1;
	else	
		return -1;
}
int Short2Cmp(const void *arg1, const void *arg2)
{
	unsigned short 
		*p1 = *(unsigned short **)arg1, 
		*p2 = *(unsigned short **)arg2;

	if( p1[2] == p2[2] )		
		return 0;
	else if( p1[2] > p2[2] )	
		return 1;
	else	
		return -1;
}
int Short3Cmp(const void *arg1, const void *arg2)
{
	unsigned short 
		*p1 = *(unsigned short **)arg1, 
		*p2 = *(unsigned short **)arg2;

	if( p1[3] == p2[3] )		
		return 0;
	else if( p1[3] > p2[3] )	
		return 1;
	else	
		return -1;
}
int Short4Cmp(const void *arg1, const void *arg2)
{
	unsigned short 
		*p1 = *(unsigned short **)arg1, 
		*p2 = *(unsigned short **)arg2;

	if( p1[4] == p2[4] )		
		return 0;
	else if( p1[4] > p2[4] )	
		return 1;
	else	
		return -1;
}

int Short0Find(const void *arg1, const void *arg2)
{
	unsigned short 
		p1 = *(unsigned short *)arg1, 
		*p2 = *(unsigned short **)arg2;

	if( p1 == p2[0] )		
		return 0;
	else if( p1 > p2[0] )	
		return 1;
	else	
		return -1;
}

/*FUNCTION_HEADER**********************
 * NAME:	;ReadCodePageTable
 * DESC: 	Read one of the CP###.txt files
 * IN:		
 * OUT:		ppTable
			pnRows
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
unsigned short **ReadCodePageTable(char *sFile, int *pnRows)
{
	char 
		sBuf[128],
		*pc;
	unsigned short
		wCp,
		wUtf,
		**ppTable;
	int 
		nData=0,
		nRead=0;
	FILE 
		*fp;

	if( (fp = fopen(sFile, "rt")) == NULL )
		return NULL;

	while( fgets(sBuf, 128, fp) )
	{
		if( (pc = strchr(sBuf, '#')) != NULL )
			*pc = 0x00;

		if( sBuf[0] && sscanf(sBuf, "%x %x", &wCp, &wUtf) == 2 )
		{
			nData++;
		}
	}

	if( (ppTable = (unsigned short **)calloc(nData, sizeof(unsigned short *))) == NULL )
		return NULL;

	fseek(fp, 0, SEEK_SET);
	while( fgets(sBuf, 128, fp) )
	{
		if( (pc = strchr(sBuf, '#')) != NULL )
		{
			*pc = 0x00;
			pc++;
		}

		if( sBuf[0] && sscanf(sBuf, "%x %x", &wCp, &wUtf) == 2 )
		{
			ppTable[nRead] = (unsigned short *)calloc(2, sizeof(unsigned short));
			ppTable[nRead][0] = wUtf;
			ppTable[nRead][1] = wCp;
			nRead++;
		}
	}

	fclose(fp);

	*pnRows = nRead;

	return ppTable;

}

/*FUNCTION_HEADER**********************
 * NAME:	;FreeTable
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void FreeTable(unsigned short **ppMergeTable, int nRows)
{
	int	i;

	for(i=0; i<nRows; i++)
	{
		free(ppMergeTable[i]);
	}
	free(ppMergeTable);
}


/*FUNCTION_HEADER**********************
 * NAME:	;WriteTable
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void WriteTable(char *sFile, unsigned short **ppMergeTable, int nRows, int nCols)
{
	int
		i, j;
	FILE *fp;

	if( (fp = fopen(sFile, "wt")) == NULL )
		return;

	fprintf(fp, "static short **ppCodeTable = {\n");

	for(i=0; i<nRows; i++)
	{
		fprintf(fp, "\t{");
		for(j=0; j<nCols; j++)
		{
			if( j<nCols-1 )
			{
				fprintf(fp, "0x%04x,", ppMergeTable[i][j]);
			}
			else
			{
				fprintf(fp, "0x%04x}", ppMergeTable[i][j]);
			}
		}

		if( i<nRows-1 )
		{
			fprintf(fp, ",\n");
		}
		else
		{
			fprintf(fp, "\n};\n\n");
		}
	}

	fclose(fp);
}

/*FUNCTION_HEADER**********************
 * NAME:	;WriteTables
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void WriteTables(char *sFile, unsigned short **ppMergeTable, int nRows, int nCols)
{
	char *psTitles[] = {
		"ppwSjis2Utf",
		"ppwEuc2Utf",
		"ppwKsc2Utf",
		"ppwGbk2Utf"
	};
	int
		i, col,
		nCount,
		bStart=1;
	FILE *fp;

	if( (fp = fopen(sFile, "wt")) == NULL )
		return;


	for(col=1; col<nCols; col++)
	{
		switch(col)
		{
		case 1:
			qsort((void *)ppMergeTable, nRows, sizeof(short *), Short1Cmp);
			break;
		case 2:
			qsort((void *)ppMergeTable, nRows, sizeof(short *), Short2Cmp);
			break;
		case 3:
			qsort((void *)ppMergeTable, nRows, sizeof(short *), Short3Cmp);
			break;
		case 4:
			qsort((void *)ppMergeTable, nRows, sizeof(short *), Short4Cmp);
			break;
		}

		fprintf(fp, "static short **%s = {\n", psTitles[col-1]);
		nCount = 0;
		for(i=0; i<nRows; i++)
		{
			if( ppMergeTable[i][col] != 0 )
			{
				if( bStart )
				{
					fprintf(fp, "\t{0x%04x, 0x%04x}", ppMergeTable[i][col], ppMergeTable[i][0]);
					bStart = 0;
				}
				else
				{
					fprintf(fp, ",\n\t{0x%04x, 0x%04x}", ppMergeTable[i][col], ppMergeTable[i][0]);
				}
				nCount++;
			}
		}
		fprintf(fp, "\n};\n");
		fprintf(fp, "//	There were %d values\n\n", nCount);
	}
	fclose(fp);
}

/*FUNCTION_HEADER**********************
 * NAME:	;DupCodeTable
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
unsigned short **DupCodeTable(CODE_TRANSL *pTable, int nRows, int nCols)
{
	int
		i;
	short 
		**ppNewTbl;

	if( (ppNewTbl = (unsigned short **)calloc(nRows, sizeof(unsigned short *))) == NULL )
		return NULL;

	for(i=0; i<nRows; i++)
	{
		ppNewTbl[i] = (unsigned short *)calloc(nCols, sizeof(unsigned short));
		
		ppNewTbl[i][0] = pTable[i].utf16;
		ppNewTbl[i][1] = pTable[i].sjis;
		ppNewTbl[i][2] = pTable[i].euc;
	}

	return ppNewTbl;
}

/*FUNCTION_HEADER**********************
 * NAME:	;AddTableCol
 * DESC: 	Add a new column on to the table
 * IN:		ppMergeTable - 2 dimensional array of shorts.  Column 0 should be unicode values
			pnRows - pointer to number of rows in ppMergeTable
			pnCols - pointer to number of columns in ppMergeTable
			ppNewTable - 2 dimensional array.  Col 0 is unicode values, Col 1 is new values
			nNewRows - number of rowns in ppNewTable
 * OUT:		ppMergeTable is updated with a new column of data
			pnRows is updated if new values are added to ppMerge Table
			pnCols is increased by 1 for the new column
 * RETURN:	
 * NOTES:	Unicode values are expected to be in ppMergeTable[r][0] and ppNewTable[r][0]
			Values are added from ppNewTable[r][1] to ppMergeTable[r][nNewCol]

 *END_HEADER***************************/
void AddTableCol(unsigned short ***pppMergeTable, int *pnRows, int *pnCols, 
				 unsigned short **ppNewTable, int nNewRows)
{
	int	
		i,
		nRows = *pnRows,
		nCols = *pnCols;
	unsigned short
		*pwRow;
	void 
		*pVoid;

	// Sort ppMergeTable by the unicode column
	qsort((void *)*pppMergeTable, nRows, sizeof(short *), Short0Cmp);

	// Add a column to ppMergeTable
	for(i=0; i<nRows; i++)
	{
		(*pppMergeTable)[i] = (unsigned short *)realloc((*pppMergeTable)[i], (nCols+1)*sizeof(unsigned short));
		(*pppMergeTable)[i][nCols] = 0;
	}

	for(i=0; i<nNewRows; i++)
	{
		// Find ppNewTable[i][0] in ppMergeTable[][0]
		pVoid = FNX_BSEARCH(&ppNewTable[i][0], (void *)*pppMergeTable, nRows, sizeof(short *), Short0Find);
		if( pVoid != NULL )
		{
			pwRow = *(unsigned short **)pVoid;
			pwRow[nCols] = ppNewTable[i][1];
		}
		else
		{
			*pppMergeTable = (unsigned short **)realloc(*pppMergeTable, (nRows+1)*sizeof(unsigned short *));
			(*pppMergeTable)[nRows] = (unsigned short *)calloc(nCols+1, sizeof(short));
			(*pppMergeTable)[nRows][0] = ppNewTable[i][0];
			(*pppMergeTable)[nRows][nCols] = ppNewTable[i][1];
			nRows++;
			qsort((void *)*pppMergeTable, nRows, sizeof(short *), Short0Cmp);
		}
	}

	*pnRows = nRows;
	*pnCols = nCols+1;

}

/*FUNCTION_HEADER**********************
 * NAME:	;MergeTableCol
 * DESC: 	Merge data from ppNewTable[][1] into ppMergeTable[][nCol]
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void MergeTableCol(unsigned short **ppMergeTable, int *pnRows, int nCols, int nCol, 
				   unsigned short **ppNewTable, int nNewRows)
{
	int	
		i,
		nRows = *pnRows;
	unsigned short
		*pwRow;
	void 
		*pVoid;

	// Sort ppMergeTable by the unicode column
	qsort((void *)ppMergeTable, nRows, sizeof(short *), Short0Cmp);

	for(i=0; i<nNewRows; i++)
	{
		// Find ppNewTable[i][0] in ppMergeTable[][0]
		pVoid = FNX_BSEARCH(&ppNewTable[i][0], (void *)ppMergeTable, nRows, sizeof(short *), Short0Find);
		if( pVoid != NULL )
		{
			pwRow = *(unsigned short **)pVoid;
			if( pwRow[nCol] == 0 && ppNewTable[i][1] != 0 )
				pwRow[nCol] = ppNewTable[i][1];
		}
		else
		{
			ppMergeTable = (unsigned short **)realloc(ppMergeTable, (nRows+1)*sizeof(unsigned short *));
			ppMergeTable[nRows] = (unsigned short *)calloc(nCols, sizeof(short));
			ppMergeTable[nRows][0] = ppNewTable[i][0];
			ppMergeTable[nRows][nCol] = ppNewTable[i][1];
			nRows++;
			qsort((void *)ppMergeTable, nRows, sizeof(short *), Short0Cmp);
		}
	}

	*pnRows = nRows;

}

/*FUNCTION_HEADER**********************
 * NAME:	;BuildMergedCodePageTable
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void BuildMergedCodePageTable(void)
{
	unsigned short
		**ppMergeTable,
		**ppSjisTable,
		**ppKscTable,
		**ppGbkTable;
	int
		nMergeRows = sizeof(pCodeTable) / sizeof(CODE_TRANSL),
		nMergeCols = 3,
		nSjisRows = 0,
		nKscRows = 0,
		nGbkRows = 0;

	printf("Duplicating Unicode/SJis/Euc table\n");
	ppMergeTable = DupCodeTable(pCodeTable, nMergeRows, nMergeCols);

	// Merge SJis info from the Code page 932 document found at:
	//	http://www.unicode.org/Public/MAPPINGS/VENDORS/MICSFT/WINDOWS/CP932.TXT
	printf("Merging cp932 SJis data\n");
	ppSjisTable = ReadCodePageTable("C:\\TTS\\DECtalk 5.1\\Docs\\Japanese\\CP932.SJIS.TXT", &nSjisRows);
	MergeTableCol(ppMergeTable, &nMergeRows, nMergeCols, 1, ppSjisTable, nSjisRows);
	FreeTable(ppSjisTable, nSjisRows);
	
	// Add Korean data from code page 949 found at:
	//	http://www.unicode.org/Public/MAPPINGS/VENDORS/MICSFT/WINDOWS/CP949.TXT
	printf("Adding cp949 Korean data\n");
	ppKscTable = ReadCodePageTable("C:\\TTS\\DECtalk 5.1\\Docs\\Korean\\CP949.TXT", &nKscRows);
	AddTableCol(&ppMergeTable, &nMergeRows, &nMergeCols, ppKscTable, nKscRows);
	FreeTable(ppKscTable, nKscRows);

	// Add GBK data from code page 936 found at:
	//	http://www.unicode.org/Public/MAPPINGS/VENDORS/MICSFT/WINDOWS/CP936.TXT
	printf("Adding cp936 GBK data\n");
	ppGbkTable = ReadCodePageTable("C:\\TTS\\DECtalk 5.1\\Docs\\Chinese\\CP936.GBK.TXT", &nGbkRows);
	AddTableCol(&ppMergeTable, &nMergeRows, &nMergeCols, ppGbkTable, nGbkRows);
	FreeTable(ppGbkTable, nGbkRows);

	WriteTable("MergedCodeTable.new.h", ppMergeTable, nMergeRows, nMergeCols);
	WriteTables("MergedCodeTables.new.h", ppMergeTable, nMergeRows, nMergeCols);

	FreeTable(ppMergeTable, nMergeRows);

}
#endif	// CREATE_TABLES

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
	int i, nConv;
	char *sInFile=NULL, *sOutFile=NULL;
	CODE_TYPE eIn, eOut;
	unsigned short str[500];
	//char cstr[500];
	FILE *fpIn, *fpOut;

	BuildMergedCodePageTable();
	return 0;

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
		else if( stricmp(argv[i], "-su") == 0 )
		{
			eIn = eSjis;	eOut = eUtf16;
		}
		else if( stricmp(argv[i], "-gu") == 0 )
		{
			eIn = eGbk;	eOut = eUtf16;
		}
		else if( stricmp(argv[i], "-ku") == 0 )
		{
			eIn = eKsc;	eOut = eUtf16;
		}
	}

	if( sInFile == NULL || sOutFile == NULL || eIn == eOut )
		return 0;

	if( eOut == eUtf16 &&
		(eIn == eSjis ||
		 eIn == eGbk ||
		 eIn == eKsc) )
	{
		ConvertFile2Utf(sInFile, sOutFile);
	}
	else
	{
		// Open the input file
		if( (fpIn = FNX_FOPEN(sInFile, "rb")) == NULL )
			return 0;

		// Open the output file
		if( (fpOut = FNX_FOPEN(sOutFile, "wb")) == NULL )
			return 0;

		// Read in wide characters
		FNX_FREAD(str, 500, sizeof(short), fpIn);
		FNX_FCLOSE(fpIn);

		nConv = ConvertCode(str, eIn, eOut);
		FNX_FWRITE(str, nConv, sizeof(short), fpOut);

		FNX_FCLOSE(fpOut);
	}

#if 0
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
		if( (pVoid = FNX_BSEARCH(&(pSjisUnicode[i].w2), (void *)pSjisUnicode, nS2U, sizeof(CODE_TRANSL), W2CodeFind)) != NULL )
		{
			su = *(CODE_TRANSL *)pVoid;

			if( (pVoid = FNX_BSEARCH(&(pSjisUnicode[i].w2), (void *)pEucUnicode, nE2U, sizeof(CODE_TRANSL), W2CodeFind)) != NULL )
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
