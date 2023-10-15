/*C_HEADER_FILE****************************************************************
FILE			:	KrTextNormal.c
DESC			:	Text Normalization routines for Korean
TABS			:	4
OWNER			:	Fonix
DATE CREATED:	12 April 2006

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
#include "port.h"
#include "ph_def.h"				// definition of PDPH_T thread data
#include "KrTextNormal.h"
#include "KoreanIntonation.h"

/* In Unicode 2.0, Hanguel syllables go from 0xAC00-0xD7A3. 
   Each value represents one syllable, which consists of
   an initial consonant, a vowel, and possibly a final consonant.*/
#define HANGUL_BASE 0xAC00 // Beginning of Hangeul characters
#define HANGUL_END  0xD7A3 // Last Hangeul character

#define SYMBOL_US_DOLLAR		0x0024	// '$'
#define SYMBOL_PERCENT			0x0025	// '%'
#define SYMBOL_AND				0x0026	// '&'
#define SYMBOL_AT				0x0040	// '@'
#define SYMBOL_CENT				0x00A2	// Cent sign
#define SYMBOL_UK_POUND			0x00A3	// Sterling pound, Irish punt, Italian Lira, Turkish Lira
#define SYMBOL_YEN_YUAN			0x00A5	// Japanese Yen, Chinese Yuan sign
#define SYMBOL_COPYRIGHT		0x00A9	// Copyright
#define SYMBOL_REGISTERED		0x00AE	// Registered
#define SYMBOL_DEGREE			0x00B0	// degee for temperature (15°C, 50°F) or for angle 30° in math. 
#define SYMBOL_ONEQUARTER		0x00BC	// 1/4
#define SYMBOL_ONEHALF			0x00BD	// 1/2
#define SYMBOL_THREEQUARTERS	0x00BE	// 3/4
#define SYMBOL_LIRA				0x20A4	// Lira
#define SYMBOL_EURO				0x20AC	// Euro
#define SYMBOL_WON				0x20A9	// Won - Korean currency
#define SYMBOL_DEGREES_C		0x2103	// °C
#define SYMBOL_DEGREES_F		0x2109	// °F
#define SYMBOL_TRADEMARK		0x2122	// TM
#define SYMBOL_OPEN_PAREN		0x0028	// (
#define SYMBOL_COMMA			0x002C	// ,

#define HANGUL_YEAR				0xB144
#define HANGUL_MONTH			0xC6D4
#define HANGUL_DAY				0xC77C
#define HANGUL_HOUR				0xC2DC
#define HANGUL_MIN				0xBD84
#define HANGUL_AT				0xC573
#define HANGUL_POINT			0xC810	// 6.3 - six point three
#define HANGUL_DOT				0xB2F7


/*
	10K
	1.
	2.
	900? (km symbol)
	5m
	(i)
	(ii)
*/

#if defined CASIO_SH3 && defined _BIGENDIAN_
static void xtox
        (
        unsigned long val,
        wchar_t *buf,
        unsigned radix,
        int is_neg
        )
{
        wchar_t *p;                /* pointer to traverse string */
        wchar_t *firstdig;         /* pointer to first digit */
        wchar_t temp;              /* temp char */
        unsigned digval;         /* value of digit */

        p = buf;

        if (is_neg) {
            /* negative, so output '-' and negate */
            *p++ = '-';
            val = (unsigned long)(-(long)val);
        }

        firstdig = p;           /* save pointer to first digit */

        do {
            digval = (unsigned) (val % radix);
            val /= radix;       /* get next digit */

            /* convert to ascii and store */
            if (digval > 9)
                *p++ = (wchar_t) (digval - 10 + 'a');  /* a letter */
            else
                *p++ = (wchar_t) (digval + '0');       /* a digit */
        } while (val > 0);

        /* We now have the digit of the number in the buffer, but in reverse
           order.  Thus we reverse them now. */

        *p-- = '\0';            /* terminate string; p points to last digit */

        do {
            temp = *p;
            *p = *firstdig;
            *firstdig = temp;   /* swap *p and *firstdig */
            --p;
            ++firstdig;         /* advance to next two digits */
        } while (firstdig < p); /* repeat until halfway */
}

wchar_t * _itow (int value, wchar_t *string, int radix)
{
	if (radix == 10 && value < 0)
		xtox((unsigned long)value, string, radix, 1);
	else
		xtox((unsigned long)(unsigned int)value, string, radix, 0);
	return string;
}
#endif

#if 0
wchar_t * _itow (int value, wchar_t *string, int radix)
{
	wchar_t		tmp [33];
	wchar_t		* tp = tmp;
	int		i;
	unsigned int	v;
	int		sign;
	wchar_t		* sp;

	if (radix > 36 || radix <= 1)
	{
//		__set_errno(EDOM);
		return 0;
	}

	sign = ((radix == 10) && (value < 0));
	if (sign)
	{
		v = -value;
	}
	else
	{
		v = (unsigned) value;
	}
	while (v || tp == tmp)
	{
		i = v % radix;
		v = v / radix;
		if (i < 10)
		{
			*tp++ = i+ (wchar_t) '0';
		}
		else
		{
			*tp++ = i + (wchar_t) 'a' - 10;
		}
	}

	if (string == 0)
	{
		string = (wchar_t *) malloc((tp-tmp) + (sign + 1) * sizeof(wchar_t));
	}
	sp = string;

	if (sign)
	{
		*sp++ = (wchar_t) '-';
	}
	while (tp > tmp)
	{
		*sp++ = *--tp;
	}
	*sp = (wchar_t) 0;
	return string;
}
#endif


/*FUNCTION_HEADER**********************
 * NAME:	;FNXW_CHRCAT
 * DESC: 	Add 1 character to the end of a string
 * IN:		wsText - the string
			wc - the character
 * OUT:		wsText with wc added to the end.
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void FNXW_CHRCAT(wchar_t *wsText, wchar_t wc)
{
	wchar_t *pwc;

	for(pwc=wsText; *pwc; pwc++)
		;
	*pwc = wc;
	*(pwc+1) = 0x00;
}

/*FUNCTION_HEADER**********************
 * NAME:	;FNXW_ITOA
 * DESC: 	Convert an integer to a string
 * IN:		iVal - integer value to convert
			radix - Base of value; must be in the range 2 – 36
 * OUT:		wsText - the string result
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
wchar_t *FNXW_ITOA(int iVal, wchar_t *wsText, int radix)
{
	_itow(iVal, wsText, radix);		// This will need to be Fonix-ized

	return wsText;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsAlpha
 * DESC: 	Determine if the input is an alpha character or not
 * IN:		pwc - pointer to the input character
 * OUT:		none
 * RETURN:	1 yes, 0 no
 * NOTES:	
 *END_HEADER***************************/
int KrIsAlpha(wchar_t *pwc)
{
	if( ('a' <= *pwc && *pwc <= 'z') )
	{
		return (*pwc - 'a') + 1;
	}
	else if( ('A' <= *pwc && *pwc <= 'Z') )
	{
		return (*pwc -'A') + 1;
	}
	else
	{
		return 0;
	}
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrNormalizeAlpha
 * DESC: 	Change a roman alphabet letter into it's Hangul equivalent
 * IN:		wc - an alphabet character
 * OUT:		wsNormal - the Hangul equivalent
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
int KrNormalizeAlpha(wchar_t wc, wchar_t *wsNormal)
{
	wchar_t wsAlpha[][4] = {
		{0xc5d0, 0xc774, 0x0000, 0x0000},	// a
		{0xbe44, 0x0000, 0x0000, 0x0000},	// b
		{0xc528, 0x0000, 0x0000, 0x0000},	// c
		{0xb514, 0x0000, 0x0000, 0x0000},	// d
		{0xc774, 0x0000, 0x0000, 0x0000},	// e
		{0xc5d0, 0xd504, 0x0000, 0x0000},	// f
		{0xc950, 0x0000, 0x0000, 0x0000},	// g
		{0xc5d0, 0xc774, 0xcde8, 0x0000},	// h
		{0xc544, 0xc774, 0x0000, 0x0000},	// i
		{0xc81c, 0xc774, 0x0000, 0x0000},	// j
		{0xcf00, 0xc774, 0x0000, 0x0000},	// k
		{0xc5d8, 0x0000, 0x0000, 0x0000},	// l
		{0xc5e0, 0x0000, 0x0000, 0x0000},	// m
		{0xc5d4, 0x0000, 0x0000, 0x0000},	// n
		{0xc624, 0x0000, 0x0000, 0x0000},	// o
		{0xd53c, 0x0000, 0x0000, 0x0000},	// p
		{0xd050, 0x0000, 0x0000, 0x0000},	// q
		{0xc54c, 0x0000, 0x0000, 0x0000},	// r
		{0xc5d0, 0xc2a4, 0x0000, 0x0000},	// s
		{0xd2f0, 0x0000, 0x0000, 0x0000},	// t
		{0xc720, 0x0000, 0x0000, 0x0000},	// u
		{0xbdd4, 0xc774, 0x0000, 0x0000},	// v
		{0xb354, 0xbd88, 0xb958, 0x0000},	// w
		{0xc5d1, 0xc2a4, 0x0000, 0x0000},	// x
		{0xc640, 0xc774, 0x0000, 0x0000},	// y
		{0xc9c0, 0x0000, 0x0000, 0x0000}	// z
	};

	int iChar = KrIsAlpha(&wc);

	if( iChar >= 1 )
	{
		FNXW_STRCPY(wsNormal, wsAlpha[iChar-1]);
		return 1;
	}
	else
	{
		return 0;
	}
	
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrNormalizeAlphaString
 * DESC: 	Change a string of roman alphabet letters into it's Hangul equivalents
 * IN:		wsInput - pointer to input string
 * OUT:		wsNormal - pointer to string of Hangul equivalents
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
int KrNormalizeAlphaString(wchar_t *wsInput, wchar_t *wsNormal)
{
	wchar_t 
		*pwc,
		wsAlpha[8];

	wsNormal[0] = 0x00;

	for(pwc=wsInput; *pwc && KrIsAlpha(pwc); pwc++)
	{
		if( KrNormalizeAlpha(*pwc, wsAlpha) )
		{
			if( pwc != wsInput )					// Mihwa says that koreans slow down when reading alpha-letters
			{
#if defined CASIO_SH3 && defined _BIGENDIAN_
				FNXW_STRCAT(wsNormal, ", ");
#else
				FNXW_STRCAT(wsNormal, L", ");
#endif
			}
			FNXW_STRCAT(wsNormal, wsAlpha);
		}
	}

	return (pwc-wsInput);
}


/*FUNCTION_HEADER**********************
 * NAME:	;KrIsDigit
 * DESC: 	Determine if the input character is a digit
 * IN:		wc - wide character
 * OUT:		none
 * RETURN:	0 if not a digit
			1 if it is a digit
 * NOTES:	
 *END_HEADER***************************/
int KrIsDigit(wchar_t wc)
{
	if( '0' <= wc && wc <= '9' )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*FUNCTION_HEADER**********************
 * NAME:	;KrIsNumber
 * DESC: 	Determine if the input string points to a number or not
 * IN:		pwsText - pointer to the input string
 * OUT:		none
 * RETURN:	0 if not a number else number of characters used in number
 * NOTES:	
 *END_HEADER***************************/
int KrIsNumber(wchar_t *pwsText)
{
	wchar_t *pwc;
	int iLen=0;

	if( '0' <= *pwsText && *pwsText <= '9' )
	{
		for(pwc = pwsText; *pwc; pwc++, iLen++)
		{
			if( !(('0' <= *pwc && *pwc <= '9') ||
				 *pwc == '.') )
				break;
		}
		return iLen;
	}
	else
		return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsFollowedByCountingWord
 * DESC: 	Determine if the input string points to a counting word or not
 * IN:		pwsText - pointer to the input string
 * OUT:		none
 * RETURN:	number of characters used if pwsText begins with a counting word, 0 if not
 * NOTES:	
 *END_HEADER***************************/
int KrIsCountingWord(wchar_t *pwsText)
{
	wchar_t psWords[][3] = {
		{0xac1c, 0x0000, 0x0000},	// gae
		{0xbd84, 0x0000, 0x0000},	// bun
		{0xba85, 0x0000, 0x0000},	// myeong
		{0xb9c8, 0xb9ac, 0x0000},	// mari
		{0xc7a5, 0x0000, 0x0000},	// jang
		{0xacfc, 0x0000, 0x0000},	// gwa
		{0xb300, 0x0000, 0x0000},	// dae
		{0xad8c, 0x0000, 0x0000},	// gwon
		{0xadf8, 0xb8e8, 0x0000},	// geuru
		{0xc790, 0xb8e8, 0x0000},	// jaru
		{0xcf24, 0xb808, 0x0000},	// kyeolle
		{0xcc99, 0x0000, 0x0000},	// cheok
		{0xcc44, 0x0000, 0x0000},	// chae
		{0xd1b5, 0x0000, 0x0000},	// tong
		{0xc0ac, 0xb78c, 0x0000},	// saram
		//{0xce35, 0x0000, 0x0000},	// cheung (floor) - Mihwa says this word is an exception and shouldn't solicit Natural Korean numbers
		{0xc794, 0x0000, 0x0000},	// jan
		{0xbcd1, 0x0000, 0x0000},	// byeong
		{0xbc8c, 0x0000, 0x0000},	// beol
		{0xb3c8, 0x0000, 0x0000},	// don
		{0xc8fd, 0x0000, 0x0000},	// jug
		{0xcf8c, 0x0000, 0x0000},	// kwae
		{0xc190, 0x0000, 0x0000},	// son
		{0xc0b4, 0x0000, 0x0000},	// sal
	};

	int
		i,
		nWords = sizeof(psWords) / sizeof(wchar_t *);

	for( i=0; i<nWords; i++ )
	{
		if( FNXW_STRSTR(pwsText, psWords[i]) == pwsText )
			return FNXW_STRLEN(psWords[i]);
	}
	return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsSymbol
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	0 if NOT a recognized symbol
			1 if it IS a recognized symbol
 * NOTES:	
 *END_HEADER***************************/
int KrIsSymbol(wchar_t *pwc)
{
	unsigned short wSymbols[] = {
		SYMBOL_DEGREES_C,
		SYMBOL_DEGREES_F,
		SYMBOL_DEGREE,
		SYMBOL_US_DOLLAR,
		SYMBOL_PERCENT,
		SYMBOL_AND,
		SYMBOL_AT,
		SYMBOL_CENT,
		SYMBOL_UK_POUND,
		SYMBOL_YEN_YUAN,
		SYMBOL_COPYRIGHT,
		SYMBOL_REGISTERED,
		SYMBOL_LIRA,
		SYMBOL_EURO,
		SYMBOL_WON,
		SYMBOL_ONEQUARTER,
		SYMBOL_ONEHALF,
		SYMBOL_THREEQUARTERS,
		SYMBOL_TRADEMARK,
		SYMBOL_OPEN_PAREN
	};

	if( FNXW_STRCHR(wSymbols, *pwc) != NULL )
		return 1;
	else
		return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrNormalizeSymbol
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int KrNormalizeSymbol(wchar_t *pwc, wchar_t *wsNormal)
{
	int 
		nUsed=0;
	unsigned short wHangul[][6] = {
		{0xc12d, 0xc528, 0x0000, 0x0000, 0x0000, 0x0000},		//SYMBOL_DEGREES_C,
		{0xd654, 0xc528, 0x0000, 0x0000, 0x0000, 0x0000},		//SYMBOL_DEGREES_F,
		{0xb3c4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},		//SYMBOL_DEGREE,
		{0xb2ec, 0xb7ec, 0x0000, 0x0000, 0x0000, 0x0000},		//SYMBOL_US_DOLLAR,
		{0xd37c, 0xc13c, 0xd2b8, 0x0000, 0x0000, 0x0000},		//SYMBOL_PERCENT,
		{0xc564, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},		//SYMBOL_AND,
		{0xc573, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},		//SYMBOL_AT,
		{0xc13c, 0xd2b8, 0x0000, 0x0000, 0x0000, 0x0000},		//SYMBOL_CENT,
		{0xd30c, 0xc6b4, 0xb4dc, 0x0000, 0x0000, 0x0000},		//SYMBOL_UK_POUND,
		{0xc5d4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},		//SYMBOL_YEN_YUAN,
		{0xc800, 0xc791, 0xad8c, 0x0000, 0x0000, 0x0000},		//SYMBOL_COPYRIGHT,
		{0xb4f1, 0xb85d, 0x0020, 0xc0c1, 0xd45c, 0x0000},		//SYMBOL_REGISTERED,
		{0xb9ac, 0xb77c, 0x0000, 0x0000, 0x0000, 0x0000},		//SYMBOL_LIRA,
		{0xc720, 0xb7fd, 0x0000, 0x0000, 0x0000, 0x0000},		//SYMBOL_EURO,
		{0xc774, 0xae30, 0xb294, 0x0000, 0x0000, 0x0000},		//SYMBOL_WON,
		{0xc0ac, 0xbd84, 0xc758, 0xc77c, 0x0000, 0x0000},		//SYMBOL_ONEQUARTER,
		{0xc774, 0xbd84, 0xc758, 0xc77c, 0x0000, 0x0000},		//SYMBOL_ONEHALF,
		{0xc0ac, 0xbd84, 0xc758, 0xc0bc, 0x0000, 0x0000},		//SYMBOL_THREEQUARTERS,
		{0xc0c1, 0xd45c, 0x0000, 0x0000, 0x0000, 0x0000},		//SYMBOL_TRADEMARK
	};

	switch( *pwc )
	{
		case SYMBOL_DEGREES_C:
			FNXW_STRCPY(wsNormal, wHangul[0]);
			nUsed = 1;
			break;
		case SYMBOL_DEGREES_F:
			FNXW_STRCPY(wsNormal, wHangul[1]);
			nUsed = 1;
			break;
		case SYMBOL_DEGREE:
			FNXW_STRCPY(wsNormal, wHangul[2]);
			nUsed = 1;
			break;
		case SYMBOL_US_DOLLAR:
			if( KrIsNumber(pwc+1) )
			{
				nUsed = KrNormalizeNumber(pwc+1, wsNormal, 1, 0);
				FNXW_STRCAT(wsNormal, wHangul[3]);
				nUsed++;
			}
			else
			{
				FNXW_STRCPY(wsNormal, wHangul[3]);
				nUsed = 1;
			}
			break;
		case SYMBOL_PERCENT:
			FNXW_STRCPY(wsNormal, wHangul[4]);
			nUsed = 1;
			break;
		case SYMBOL_AND:
			FNXW_STRCPY(wsNormal, wHangul[5]);
			nUsed = 1;
			break;
		case SYMBOL_AT:
			FNXW_STRCPY(wsNormal, wHangul[6]);
			nUsed = 1;
			break;
		case SYMBOL_CENT:
			if( KrIsNumber(pwc+1) )
			{
				nUsed = KrNormalizeNumber(pwc+1, wsNormal, 1, 0);
				FNXW_STRCAT(wsNormal, wHangul[7]);
				nUsed++;
			}
			else
			{
				FNXW_STRCPY(wsNormal, wHangul[7]);
				nUsed = 1;
			}
			break;
		case SYMBOL_UK_POUND:
			if( KrIsNumber(pwc+1) )
			{
				nUsed = KrNormalizeNumber(pwc+1, wsNormal, 1, 0);
				FNXW_STRCAT(wsNormal, wHangul[8]);
				nUsed++;
			}
			else
			{
				FNXW_STRCPY(wsNormal, wHangul[8]);
				nUsed = 1;
			}
			break;
		case SYMBOL_YEN_YUAN:
			if( KrIsNumber(pwc+1) )
			{
				nUsed = KrNormalizeNumber(pwc+1, wsNormal, 1, 0);
				FNXW_STRCAT(wsNormal, wHangul[9]);
				nUsed++;
			}
			else
			{
				FNXW_STRCPY(wsNormal, wHangul[9]);
				nUsed = 1;
			}
			break;
		case SYMBOL_COPYRIGHT:
			FNXW_STRCPY(wsNormal, wHangul[10]);
			nUsed = 1;
			break;
		case SYMBOL_REGISTERED:
			FNXW_STRCPY(wsNormal, wHangul[11]);
			nUsed = 1;
			break;
		case SYMBOL_LIRA:
			if( KrIsNumber(pwc+1) )
			{
				nUsed = KrNormalizeNumber(pwc+1, wsNormal, 1, 0);
				FNXW_STRCAT(wsNormal, wHangul[12]);
				nUsed++;
			}
			else
			{
				FNXW_STRCPY(wsNormal, wHangul[12]);
				nUsed = 1;
			}
			break;
		case SYMBOL_EURO:
			if( KrIsNumber(pwc+1) )
			{
				nUsed = KrNormalizeNumber(pwc+1, wsNormal, 1, 0);
				FNXW_STRCAT(wsNormal, wHangul[13]);
				nUsed++;
			}
			else
			{
				FNXW_STRCPY(wsNormal, wHangul[13]);
				nUsed = 1;
			}
			break;
		case SYMBOL_WON:
			if( KrIsNumber(pwc+1) )
			{
				nUsed = KrNormalizeNumber(pwc+1, wsNormal, 1, 0);
				FNXW_STRCAT(wsNormal, wHangul[14]);
				nUsed++;
			}
			else
			{
				FNXW_STRCPY(wsNormal, wHangul[14]);
				nUsed = 1;
			}
			break;
		case SYMBOL_ONEQUARTER:
			FNXW_STRCPY(wsNormal, wHangul[15]);
			nUsed = 1;
			break;
		case SYMBOL_ONEHALF:
			FNXW_STRCPY(wsNormal, wHangul[16]);
			nUsed = 1;
			break;
		case SYMBOL_THREEQUARTERS:
			FNXW_STRCPY(wsNormal, wHangul[17]);
			nUsed = 1;
			break;
		case SYMBOL_TRADEMARK:
			FNXW_STRCPY(wsNormal, wHangul[18]);
			nUsed = 1;
			break;
	}

	return nUsed;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsUnitOfMeasure
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	0 if NOT a unit of measure
			1 if it IS
 * NOTES:	
 *END_HEADER***************************/
int KrIsUnitOfMeasure(wchar_t *pwc)
{
	unsigned short wUnits[] = {
		SYMBOL_DEGREES_C,			// ==> These need to be changed !!!!!!!!!
		SYMBOL_DEGREES_F,
		SYMBOL_DEGREE,
		SYMBOL_US_DOLLAR,
		SYMBOL_PERCENT,
		SYMBOL_AND,
		SYMBOL_AT,
		SYMBOL_CENT,
		SYMBOL_UK_POUND,
		SYMBOL_YEN_YUAN,
		SYMBOL_COPYRIGHT,
		SYMBOL_REGISTERED,
		SYMBOL_LIRA,
		SYMBOL_EURO,
		SYMBOL_WON,
		SYMBOL_ONEQUARTER,
		SYMBOL_ONEHALF,
		SYMBOL_THREEQUARTERS,
		SYMBOL_TRADEMARK,
		HANGUL_YEAR,
		HANGUL_MONTH,
		HANGUL_DAY
	};

	if( FNXW_STRCHR(wUnits, *pwc) != NULL )
		return 1;
	else
		return 0;
}

typedef enum {
	eKR_CNTRY_AREA_CELL_NUMBER=1,
	eKR_CNTRY_AREA_NUMBER,
	eKR_AREA_CELL_NUMBER_PAREN,
	eKR_AREA_NUMBER_PAREN,
	eKR_AREA_CELL_NUMBER,
	eKR_AREA_NUMBER,
	eKR_CELL_NUMBER,
	eKR_NUMBER
} KR_PHONE_NUMBER;

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsPhoneNumber
 * DESC: 	Determine if input is a phone number
 * IN:		
 * OUT:		
 * RETURN:	0 if NOT a phone number
			1 if it IS
 * NOTES:	
			Possible phone number formats
			#-##-###-####-####	18/14/4
			#-##-###-###-####	17/13/4
			(###)####-####		14/11/1
			###-####-####		13/11/2
			(###)###-####		13/10/1
			###-###-####		12/10/2
			####-####			9/8/1
			###-####			8/7/1
			112 ... 119			3/0
 *END_HEADER***************************/
int KrIsPhoneNumber(wchar_t *wsInput)
{
	wchar_t
		*pwc = wsInput,
		*pwcGroup = NULL;
	int
		nDigits=0,
		nDash=0,
		nMax=0,
		nMin=1000,
		nOpen=0,
		nClose=0,
		nLen=0;

	if( *pwc == '1' &&
		*(pwc+1) == '1' &&
		KrIsDigit(*(pwc+2)) )
	{
		return 1;
	}

	for(pwc=wsInput; *pwc; pwc++)
	{
		if( KrIsDigit(*pwc) )						// Found a digit
		{
			nDigits++;
			if( pwcGroup == NULL )
				pwcGroup = pwc;
		}
		else if( *pwc == '-' )						// Found a dash
		{
			nDash++;
			if( pwcGroup )
			{
				if( pwc-pwcGroup > nMax )
					nMax = (pwc-pwcGroup);			// Find the max group size
				if( pwc-pwcGroup < nMin )
					nMin = (pwc-pwcGroup);			// Find the min group size

				pwcGroup = NULL;
			}
		}
		else if( *pwc == '(' )						// Found an open parenthesis
		{
			nOpen++;
		}
		else if( *pwc == ')' )						// Found a close parenthesis
		{
			nClose++;
			if( pwcGroup )
			{
				if( pwc-pwcGroup > nMax )
					nMax = (pwc-pwcGroup);			// Find the max group size
				else if( pwc-pwcGroup < nMin )
					nMin = (pwc-pwcGroup);			// Find the min group size
			}
			pwcGroup = NULL;
		}
	}

	if( pwcGroup )
	{
		if( pwc-pwcGroup > nMax )
			nMax = (pwc-pwcGroup);			// Find the max group size
		else if( pwc-pwcGroup < nMin )
			nMin = (pwc-pwcGroup);			// Find the min group size
	}

	nLen = pwc-wsInput;

	switch(nLen)
	{
		case 18:
			if( nDigits == 14 &&
				nDash == 4 &&
				nMax == 4 )
				return eKR_CNTRY_AREA_CELL_NUMBER;
			break;

		case 17:
			if( nDigits == 13 &&
				nDash == 4 && 
				nMax == 4)
				return eKR_CNTRY_AREA_NUMBER;
			break;

		case 14:
			if( nDigits == 11 &&
				nDash == 1 && 
				nMax == 4 )
				return eKR_AREA_CELL_NUMBER_PAREN;
		case 13:
			if( nDigits == 11 &&
				nDash == 2 &&
				nMax == 4 &&
				nMin == 3)
				return eKR_AREA_CELL_NUMBER;
			else if( nDigits == 10 &&
					 nDash == 1 &&
					 nOpen == 1 && 
					 nClose == 1 &&
					 nMax == 4 && 
					 nMin == 3 )
				return eKR_AREA_NUMBER_PAREN;
			break;

		case 12:
			if( nDigits == 10 && 
				nDash == 2 &&
				nMax == 4 && 
				nMin == 3 )
				return eKR_AREA_NUMBER;
			break;

		case 9:
			if( nDigits == 8 && 
				nDash == 1 && 
				nMax == 4 && 
				nMin == 4 )
				return eKR_CELL_NUMBER;
			break;

		case 8:
			if( nDigits == 7 &&
				nDash == 1 &&
				nMax == 4 && 
				nMin == 3 )
				return eKR_NUMBER;
			break;
	}

	return 0;
}


/*FUNCTION_HEADER**********************
 * NAME:	;KrNormalizePhoneNumber
 * DESC: 	Normalize a phone number
 * IN:		wsInput - pointer to the phone number
			iType - one of the enum values from KR_PHONE_NUMBER or 0 if unknown
 * OUT:		wsNormal - the normalized phone number
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int KrNormalizePhoneNumber(wchar_t *wsInput, wchar_t *wsNormal, int iType)
{
	wchar_t
		*pwc,
		*pwcLast=NULL,
		*pwcEnd,
		wsFirst[5],
		wsCntry[5],
		wsArea[5],
		wsPrefix[5],
		wsPostfix[5],
		wsText[64],
		wsDash[] = {SYMBOL_COMMA, 0xc5d0, SYMBOL_COMMA, 0x0000};		// e;
	int
		iFormat = iType;

	if( iFormat < eKR_CNTRY_AREA_CELL_NUMBER || iFormat > eKR_NUMBER )
		iFormat = KrIsPhoneNumber(wsInput);

	if( iFormat < eKR_CNTRY_AREA_CELL_NUMBER || iFormat > eKR_NUMBER )
		return 0;

	// Find the end of the phone number
	for(pwc=wsInput; *pwc; pwc++)
	{
		if( !KrIsDigit(*pwc) &&
			*pwc != '-' &&
			*pwc != '(' &&
			*pwc != ')' )
		{
			break;
		}
	}
	pwcLast = pwc;

	// Initialize some values
	wsFirst[0] = wsCntry[0] = wsArea[0] = wsPrefix[0] = wsPostfix[0] = 0x00;
	pwcEnd = NULL;
	wsNormal[0] = 0x00;

	// Work backwards to extract the number groups
	while( pwc >= wsInput )
	{
		if( KrIsDigit(*pwc) )
		{
			if( pwcEnd == NULL )
			{
				pwcEnd = pwc;
			}
			else if( pwc == wsInput &&
					 pwcEnd )
			{
				if( ! *wsPostfix )
				{
					FNXW_STRNCPY(wsPostfix, pwc, pwcEnd-pwc+1);
					wsPostfix[pwcEnd-pwc+1] = 0x00;
				}
				else if( ! *wsPrefix )
				{
					FNXW_STRNCPY(wsPrefix, pwc, pwcEnd-pwc+1);
					wsPrefix[pwcEnd-pwc+1] = 0x00;
				}
				else if( ! *wsArea )
				{
					FNXW_STRNCPY(wsArea, pwc, pwcEnd-pwc+1);
					wsArea[pwcEnd-pwc+1] = 0x00;
				}
				else if( ! *wsCntry )
				{
					FNXW_STRNCPY(wsCntry, pwc, pwcEnd-pwc+1);
					wsCntry[pwcEnd-pwc+1] = 0x00;
				}
				else if( ! *wsFirst )
				{
					FNXW_STRNCPY(wsFirst, pwc, pwcEnd-pwc+1);
					wsFirst[pwcEnd-pwc+1] = 0x00;
				}
				pwcEnd = NULL;

			}
		}
		else if( *pwc == '-' ||
				 *pwc == ')' ||
				 *pwc == '(' )
		{
			
			if( pwcEnd )
			{
				if( ! *wsPostfix )
				{
					FNXW_STRNCPY(wsPostfix, pwc+1, pwcEnd-pwc);
					wsPostfix[pwcEnd-pwc] = 0x00;
				}
				else if( ! *wsPrefix )
				{
					FNXW_STRNCPY(wsPrefix, pwc+1, pwcEnd-pwc);
					wsPrefix[pwcEnd-pwc] = 0x00;
				}
				else if( ! *wsArea )
				{
					FNXW_STRNCPY(wsArea, pwc+1, pwcEnd-pwc);
					wsArea[pwcEnd-pwc] = 0x00;
				}
				else if( ! *wsCntry )
				{
					FNXW_STRNCPY(wsCntry, pwc+1, pwcEnd-pwc);
					wsCntry[pwcEnd-pwc] = 0x00;
				}
				else if( ! *wsFirst )
				{
					FNXW_STRNCPY(wsFirst, pwc+1, pwcEnd-pwc);
					wsFirst[pwcEnd-pwc] = 0x00;
				}
				pwcEnd = NULL;
			}
		}
		pwc--;
	}

	if( *wsFirst )
	{
		KrNormalizeDigits(wsFirst, wsText, 0);
		FNXW_STRCAT(wsNormal, wsText);
	}
	if( *wsCntry )
	{
		KrNormalizeDigits(wsCntry, wsText, 0);
		if( *wsFirst )
			FNXW_STRCAT(wsNormal, wsDash);
		FNXW_STRCAT(wsNormal, wsText);
	}
	if( *wsArea )
	{
		if( KrIsDigit(wsArea[0]) &&
			wsArea[1] == '0' &&
			wsArea[2] == '0' )
		{
			// Say 8 hundred instead of 8 0 0
			KrNormalizeNumber(wsArea, wsText, 1, 0);	
			if( *wsCntry )
				FNXW_STRCAT(wsNormal, wsDash);
			FNXW_STRCAT(wsNormal, wsText);
		}
		else
		{
			KrNormalizeDigits(wsArea, wsText, 0);
			if( *wsCntry )
				FNXW_STRCAT(wsNormal, wsDash);
			FNXW_STRCAT(wsNormal, wsText);
		}

	}
	if( *wsPrefix )
	{
		KrNormalizeDigits(wsPrefix, wsText, 1);
		if( *wsArea )
			FNXW_STRCAT(wsNormal, wsDash);
		FNXW_STRCAT(wsNormal, wsText);
	}
	if( *wsPostfix )
	{
		if( FNXW_STRLEN(wsPostfix) == 3 &&
			wsPostfix[0] == '1' &&
			wsPostfix[1] == '1' &&
			KrIsDigit(wsPostfix[2]) )					// 11# numbers are always pronounced "il il ..."
		{
			KrNormalizeDigits(wsPostfix, wsText, 0);
			if( *wsPrefix )
				FNXW_STRCAT(wsNormal, wsDash);
			FNXW_STRCAT(wsNormal, wsText);
		}
		else
		{
			KrNormalizeDigits(wsPostfix, wsText, 1);
			if( *wsPrefix )
				FNXW_STRCAT(wsNormal, wsDash);
			FNXW_STRCAT(wsNormal, wsText);
		}
	}

	return pwcLast-wsInput;
}


/*FUNCTION_HEADER**********************
 * NAME:	;KrIsEmail
 * DESC: 	Determine if input is an email address
 * IN:		
 * OUT:		
 * RETURN:	0 if NOT an email address
			1 if it IS an email address
 * NOTES:	
 *END_HEADER***************************/
int KrIsEmail(wchar_t *wsInput)
{
	wchar_t
		*pwc;
	int
		nAt=0,
		nPeriod=0;

	for(pwc = wsInput; *pwc && *pwc != ' '; pwc++)
	{
		if( !(KrIsAlpha(pwc) || 
			  *pwc == '@' || 
			  *pwc == '.' || 
			  *pwc == '/' || 
			  *pwc == '_' || 
			  *pwc == '-') )
			return 0;

		if( *pwc == '@' )
			nAt++;
		if( *pwc == '.' )
			nPeriod++;
	}

	if( nAt != 1 )
		return 0;
	if( nPeriod == 0 )
		return 0;

	return 1;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrNormalizeEmail
 * DESC: 	Spell out an email address by converting it to Hangul
 * IN:		wsInput - email address to normalize
 * OUT:		wsNormal - Hangul pronunciation of email address
 * RETURN:	number of characters in wsInput that were converted on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int KrNormalizeEmail(wchar_t *wsInput, wchar_t *wsNormal)
{
	int
		nChars=0;
	wchar_t 
		*pwc,
		wsTmp[64];

	wchar_t wsEmailWords[][4] = {
		{0xcef4, 0x0000, 0x0000, 0x0000},	// com
		{0xb137, 0x0000, 0x0000, 0x0000},	// net
		{0xc624, 0xb974, 0xadf8, 0x0000},	// org
		{0xc950, 0xba54, 0xc77c, 0x0000},	// gmail
	};

	wsNormal[0] = 0x00;

	for( pwc=wsInput; *pwc; pwc++ )
	{
		if( *pwc == '@' )
		{
			FNXW_CHRCAT(wsNormal, 0x0020);
			FNXW_CHRCAT(wsNormal, HANGUL_AT);
			
			if( (*(pwc+1) == 'g' || *(pwc+1) == 'G') &&
					 (*(pwc+2) == 'm' || *(pwc+2) == 'M') &&
					 (*(pwc+3) == 'a' || *(pwc+3) == 'A') &&
					 (*(pwc+4) == 'i' || *(pwc+4) == 'I') &&
					 (*(pwc+5) == 'l' || *(pwc+5) == 'L') )
			{
				FNXW_CHRCAT(wsNormal, 0x0020);
				FNXW_STRCAT(wsNormal, wsEmailWords[3]);
				pwc += 5;
			}
		}
		else if( *pwc == '.' )
		{
			FNXW_CHRCAT(wsNormal, 0x0020);
			FNXW_CHRCAT(wsNormal, HANGUL_DOT);

			if( (*(pwc+1) == 'c' || *(pwc+1) == 'C') &&
				(*(pwc+2) == 'o' || *(pwc+2) == 'O') &&
				(*(pwc+3) == 'm' || *(pwc+3) == 'M') )
			{
				FNXW_CHRCAT(wsNormal, 0x0020);
				FNXW_STRCAT(wsNormal, wsEmailWords[0]);
				pwc += 3;
			}
			else if( (*(pwc+1) == 'n' || *(pwc+1) == 'N') &&
					 (*(pwc+2) == 'e' || *(pwc+2) == 'E') &&
					 (*(pwc+3) == 't' || *(pwc+3) == 'T') )
			{
				FNXW_CHRCAT(wsNormal, 0x0020);
				FNXW_STRCAT(wsNormal, wsEmailWords[1]);
				pwc += 3;
			}
			else if( (*(pwc+1) == 'o' || *(pwc+1) == 'O') &&
					 (*(pwc+2) == 'r' || *(pwc+2) == 'R') &&
					 (*(pwc+3) == 'g' || *(pwc+3) == 'G') )
			{
				FNXW_CHRCAT(wsNormal, 0x0020);
				FNXW_STRCAT(wsNormal, wsEmailWords[2]);
				pwc += 3;
			}

		}
		else if( KrIsAlpha(pwc) )
		{
			KrNormalizeAlpha(*pwc, wsTmp);
			FNXW_CHRCAT(wsNormal, 0x0020);
			FNXW_STRCAT(wsNormal, wsTmp);
#if defined CASIO_SH3 && defined _BIGENDIAN_
			FNXW_STRCAT(wsNormal, ", ");	// slow down when reading alphabet letters
#else
			FNXW_STRCAT(wsNormal, L", ");	// slow down when reading alphabet letters
#endif
		}
		else if( KrIsNumber(pwc) )
		{
			pwc += KrNormalizeNumber(pwc, wsTmp, 1, 0);
			FNXW_CHRCAT(wsNormal, 0x0020);
			FNXW_STRCAT(wsNormal, wsTmp);
		}
	}

	return (pwc - wsInput);
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsUrl
 * DESC: 	Determine if input is a URL
 * IN:		
 * OUT:		
 * RETURN:	0 if NOT a URL
			1 if it IS a URL
 * NOTES:	
 *END_HEADER***************************/
int KrIsURL(wchar_t *wsInput)
{
	wchar_t
		*pwc;
	int
		nAlpha=0,
		nNum=0,
		nPeriod=0,
		nOk=0;

	for(pwc = wsInput; *pwc && *pwc != ' '; pwc++)
	{
		if( KrIsAlpha(pwc) )
		{
			nAlpha++;
			if( *pwc == 'h' && 
				*(pwc+1) == 't' &&
				*(pwc+2) == 't' &&
				*(pwc+3) == 'p' &&
				*(pwc+4) == ':' )
			{
				return 1;
			}

			if( *pwc == 'w' &&
				*(pwc+1) == 'w' &&
				*(pwc+2) == 'w' &&
				*(pwc+3) == '.' )
			{
				return 1;
			}
		}
		else if( KrIsNumber(pwc) )
		{
			nNum++;
		}
		else if( *pwc == '.' )
		{
			nPeriod++;
			nOk++;
		}
		else if( *pwc == '/' ||
				 *pwc == '-' || 
				 *pwc == '_' )
			nOk++;
	}

	if( nPeriod >= 1 &&
		(nAlpha + nNum + nOk) == pwc-wsInput )
	{
		return 1;
	}
	else
		return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrNormalizeURL
 * DESC: 	Spell out a web address by converting it to Hangul
 * IN:		wsInput - web address to normalize
 * OUT:		wsNormal - Hangul pronunciation of web address
 * RETURN:	number of characters in wsInput that were converted on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int KrNormalizeURL(wchar_t *wsInput, wchar_t *wsNormal)
{
	int
		nChars=0;
	wchar_t 
		*pwc,
		wsTmp[64],
		wsText[64];

	typedef enum {
		eKrCom,
		eKrNet,
		eKrOrg,
		eKrSlash,
		eKrHyphen,
		eKrUnderScore,
		eKrColon
	};
	wchar_t wsWebWords[][7] = {
		{0xcef4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// com
		{0xb137, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// net
		{0xc624, 0xb974, 0xadf8, 0x0000, 0x0000, 0x0000, 0x0000},	// org
		{0xc2ac, 0xb798, 0xc26c, 0x0000, 0x0000, 0x0000, 0x0000},	// slash
		{0xd558, 0xc774, 0xd508, 0x0000, 0x0000, 0x0000, 0x0000},	// hyphen
		{0xc5b8, 0xb354, 0x0020, 0xc2a4, 0xcf54, 0xc5b4, 0x0000},	// underscore
		{0xcf5c, 0xb860, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},	// colon

	};

	wsNormal[0] = 0x00;

	for( pwc=wsInput; *pwc; pwc++ )
	{
		if( *pwc == '.' )
		{
			FNXW_CHRCAT(wsNormal, 0x0020);
			FNXW_CHRCAT(wsNormal, HANGUL_DOT);

			if( (*(pwc+1) == 'c' || *(pwc+1) == 'C') &&
				(*(pwc+2) == 'o' || *(pwc+2) == 'O') &&
				(*(pwc+3) == 'm' || *(pwc+3) == 'M') )
			{
				FNXW_CHRCAT(wsNormal, 0x0020);
				FNXW_STRCAT(wsNormal, wsWebWords[eKrCom]);
				pwc += 3;
			}
			else if( (*(pwc+1) == 'n' || *(pwc+1) == 'N') &&
					 (*(pwc+2) == 'e' || *(pwc+2) == 'E') &&
					 (*(pwc+3) == 't' || *(pwc+3) == 'T') )
			{
				FNXW_CHRCAT(wsNormal, 0x0020);
				FNXW_STRCAT(wsNormal, wsWebWords[eKrNet]);
				pwc += 3;
			}
			else if( (*(pwc+1) == 'o' || *(pwc+1) == 'O') &&
					 (*(pwc+2) == 'r' || *(pwc+2) == 'R') &&
					 (*(pwc+3) == 'g' || *(pwc+3) == 'G') )
			{
				FNXW_CHRCAT(wsNormal, 0x0020);
				FNXW_STRCAT(wsNormal, wsWebWords[eKrOrg]);
				pwc += 3;
			}

		}
		else if( *pwc == ':' )
		{
			FNXW_CHRCAT(wsNormal, 0x0020);
			FNXW_STRCAT(wsNormal, wsWebWords[eKrColon]);
		}
		else if( *pwc == '/' ||
				 *pwc == '\\' )
		{
			FNXW_CHRCAT(wsNormal, 0x0020);
			FNXW_STRCAT(wsNormal, wsWebWords[eKrSlash]);
		}
		else if( *pwc == '-' )
		{
			FNXW_CHRCAT(wsNormal, 0x0020);
			FNXW_STRCAT(wsNormal, wsWebWords[eKrHyphen]);
		}
		else if( *pwc == '_' )
		{
			FNXW_CHRCAT(wsNormal, 0x0020);
			FNXW_STRCAT(wsNormal, wsWebWords[eKrUnderScore]);
		}
		else if( KrIsAlpha(pwc) )
		{
			KrNormalizeAlpha(*pwc, wsText);
			FNXW_CHRCAT(wsNormal, 0x0020);
			FNXW_STRCAT(wsNormal, wsText);
#if defined CASIO_SH3 && defined _BIGENDIAN_
			FNXW_STRCAT(wsNormal, ", ");
#else
			FNXW_STRCAT(wsNormal, L", ");
#endif
		}
		else if( KrIsNumber(pwc) )
		{
			wsTmp[0] = *pwc;	// 1 digit at a time
			wsTmp[1] = 0x00;
			KrNormalizeNumber(wsTmp, wsText, 1, 0);
			FNXW_CHRCAT(wsNormal, 0x0020);
			FNXW_STRCAT(wsNormal, wsText);
		}
		else
		{
			break;
		}
	}

	return (pwc - wsInput);
}


/*FUNCTION_HEADER**********************
 * NAME:	;KrNormalizeNumber
 * DESC: 	Take a number composed of roman numerals and convert it into
			Korean numbers.
 * IN:		iNum - an integer number
			iType - the number system to use. iType = 1 (Sino-Korean) or iType = 2 (Native or Pure Korean)
			bUseReduced - use the reduced form of the number if available
 * OUT:		wsText - the Korean number form
 * RETURN:	0 on failure, number of characters used from wsNum on success
 * NOTES:	
 *END_HEADER***************************/
int KrNormalizeNumber(wchar_t *wsNum, wchar_t *wsText, int iType, int bUseReduced)
{
	int
		iLen,
		nWhole,
		nFrac,
		iDigit,
		bFoundPt;
	wchar_t
		*pwc;

	// Sino-Korean numbers
	wchar_t wsSKExceptions[][3] = {
		{0xc2ec, 0x0000, 0x0000},	// 10			(sim)
		{0xb275, 0x0000, 0x0000},	// 6			(nyuk)
	};
	wchar_t wsSKDigits[][2] = {
		{0xc601, 0x0000},			// 0			(yeong)
		{0xc77c, 0x0000},			// 1			(il)
		{0xc774, 0x0000},			// 2			(i)
		{0xc0bc, 0x0000},			// 3			(sam)
		{0xc0ac, 0x0000},			// 4			(sa)
		{0xc624, 0x0000},			// 5			(o)
		{0xc721, 0x0000},			// 6			(yuk)  (reduction - 0xc720 yu ?)
		{0xce60, 0x0000},			// 7			(chil)
		{0xd314, 0x0000},			// 8			(pal)
		{0xad6c, 0x0000}			// 9			(gu)
	};

	wchar_t wsSKTens[][3] = {
		{0xc2ed, 0x0000, 0x0000},	// 10			(sip)		(reduction - 0xc2dc - si)
		{0xc774, 0xc2ed, 0x0000},	// 20			(i sip)
		{0xc0bc, 0xc2ed, 0x0000},	// 30			(sam sip)
		{0xc0ac, 0xc2ed, 0x0000},	// 40			(sa sip)
		{0xc624, 0xc2ed, 0x0000},	// 50			(o sip)
		{0xc721, 0xc2ed, 0x0000},	// 60			(yuk sip)
		{0xce60, 0xc2ed, 0x0000},	// 70			(chil sip)
		{0xd314, 0xc2ed, 0x0000},	// 80			(pal sip)
		{0xad6c, 0xc2ed, 0x0000}	// 90			(gu sip)
	};
	wchar_t wsSKMag[][3] = {
		{0xc2ed, 0x0000, 0x0000},	// 10			(sip)
		{0xbc31, 0x0000, 0x0000},	// 100			(baek)		[hundred]
		{0xcc9c, 0x0000, 0x0000},	// 1000			(cheon)		[thousand]
		{0xb9cc, 0x0000, 0x0000},	// 10000		(man)		[ten-thousand]
		{0xc2ed, 0x0000, 0x0000},	// 100000		(sip-man)	[hundred-thousand]
		{0xbc31, 0x0000, 0x0000},	// 1000000		(baek-man)	[million]
		{0xcc9c, 0x0000, 0x0000},	// 10000000		(cheon-man)	[ten-million]
		{0xc5b5, 0x0000, 0x0000},	// 100000000	(euk)		[hundred-million]
		{0xc2ed, 0x0000, 0x0000},	// 1000000000	(sip-euk)	[billion]	
		{0xbc31, 0x0000, 0x0000},	// 10000000000	(baek-euk)	[ten-billion]	
		{0xcc9c, 0x0000, 0x0000},	// 100000000000	(cheon-euk)	[hundred-billion]	
		{0xc870, 0x0000, 0x0000}	// 1000000000000(jo)		[trillion]
	};

	// Natural Korean numbers
	wchar_t wsNKDigits[][3] = {
		{0x0020, 0x0000, 0x0000},	// 0
		{0xd558, 0xb098, 0x0000},	// 1	hana
		{0xb458, 0x0000, 0x0000},	// 2	dul
		{0xc14b, 0x0000, 0x0000},	// 3	set
		{0xb137, 0x0000, 0x0000},	// 4	net
		{0xb2e4, 0xc12f, 0x0000},	// 5	daseot
		{0xc5ec, 0xc12f, 0x0000},	// 6	yeoseot
		{0xc77c, 0xacf1, 0x0000},	// 7	ilgop
		{0xc5ec, 0xb35f, 0x0000},	// 8	yeodeolb
		{0xc544, 0xd649, 0x0000}	// 9	ahop
	};
	wchar_t wsNKReducedDigits[][3] = {
		{0x0020, 0x0000, 0x0000},	// 0
		{0xd55c, 0x0000, 0x0000},	// 1	han
		{0xb450, 0x0000, 0x0000},	// 2	du
		{0xc138, 0x0000, 0x0000},	// 3	se
		{0xb124, 0x0000, 0x0000},	// 4	ne
		{0xb2e4, 0xc12f, 0x0000},	// 5
		{0xc5ec, 0xc12f, 0x0000},	// 6
		{0xc77c, 0xacf1, 0x0000},	// 7
		{0xc5ec, 0xb35c, 0x0000},	// 8	yeo-deol
		{0xc544, 0xd649, 0x0000}	// 9
	};
	wchar_t wsNKTens[][3] = {
		{0xc5f4, 0x0000, 0x0000},	// 10
		{0xc2a4, 0xbb3c, 0x0000},	// 20
		{0xc11c, 0xb978, 0x0000},	// 30
		{0xb9c8, 0xd754, 0x0000},	// 40
		{0xc270, 0x0000, 0x0000},	// 50
		{0xc608, 0xc21c, 0x0000},	// 60
		{0xc77c, 0xd754, 0x0000},	// 70
		{0xc5ec, 0xb4e0, 0x0000},	// 80
		{0xc544, 0xd754, 0x0000}	// 90
	};
	wchar_t wsNKMag[][3] = {
		{0xc5f4, 0x0000, 0x0000},	// 10
		{0xc628, 0x0000, 0x0000},	// 100
		{0xc988, 0xbbc4, 0x0000}	// 1000
	};

	if( iType != 1 && iType != 2 )
		return 0;

	// Find out how long this number is.  Include both whole and fractional parts
	nWhole = nFrac = bFoundPt = 0;
	for(pwc=wsNum, iLen=0; *pwc; pwc++, iLen++)
	{
		if( !( KrIsNumber(pwc) || *pwc == '.' || *pwc == ',') )
			break;

		if( *pwc == '.' )
		{
			bFoundPt = 1;
		}
		else if( *pwc != ',' )
		{
			if( !bFoundPt )
				nWhole++;
			else
				nFrac++;
		}
	}

	if( iLen == 0 )
		return 0;

	if( nWhole > 13 )	// Can't handle a number bigger than 9 trillion
		return iLen;

	if( nWhole > 4 )
	{
		iType = 1;		// Large numbers must be in Sino-Korean
	}

	wsText[0] = 0x00;

	if( nWhole == 1 )
	{
		iDigit = *wsNum - '0';
		FNXW_STRCPY(wsText, iType==1 ? wsSKDigits[iDigit] : bUseReduced ? wsNKReducedDigits[iDigit] : wsNKDigits[iDigit]);
		if( nFrac == 0 )
			return iLen;
		else
		{
			nWhole--;
			pwc = wsNum + 1;	// Start the for loop with a pointer to the decimal point
		}
	}
	else
	{
		pwc = wsNum;			// Start the for loop with a pointer to the beginning of the number
	}

	for( ; *pwc; pwc++ )
	{
		if( '0' <= *pwc && *pwc <= '9' )
		{
			iDigit = *pwc - '0';	
		}
		else if( *pwc == '.' )
		{
			FNXW_CHRCAT(wsText, HANGUL_POINT);	// When we get to a decimal point insert the hangul for "point"
			continue;
		}
		else if( *pwc == ',' )				// skip any commas
		{
			continue;
		}
		else
		{
			// Error!
			continue;
		}

		if( nWhole == 1 )					// Ones place
		{
			if( iDigit >= 1 )
			{
				// Just say the digit for the ones place
				if( iType == 1 &&			// Sino-Korean
					iDigit == 6 )			// digit is 6
				{
					FNXW_STRCAT(wsText, wsSKExceptions[1]);		// Don't say yug, say nyug (exception rule)
				}
				else
				{
					FNXW_STRCAT(wsText, iType==1 ? wsSKDigits[iDigit] : bUseReduced ? wsNKReducedDigits[iDigit] : wsNKDigits[iDigit]);
				}
			}
			nWhole--;
		}
		else if( nWhole > 1 )
		{
			if( iDigit == 1 ) 
			{
				if( nWhole == 5 ||
					nWhole == 9 )
				{
					FNXW_STRCAT(wsText, wsSKDigits[iDigit]);  // however we do want to say il-eog
				}
				// In the tens place or higher if the value is a '1' then don't say the digit,
				// just say the magnitude value
				if( iType == 1 &&			// Sino-Korean
					 nWhole == 2 &&			// Tens place
					 *(pwc+1) == '6' )		// Next number is 6
				{
					FNXW_STRCAT(wsText, wsSKExceptions[0]);		//	Don't say sip, say sim - exception rule
				}
				else
				{
					FNXW_STRCAT(wsText, iType==1 ? wsSKMag[nWhole-2] : wsNKMag[nWhole-2]);
				}
			}
			else
			{
				if( iType == 2 &&		// Natural Korean
					nWhole == 2 &&		// Tens place
					iDigit >= 2 )		// 20, 30, 40 ... 90
				{
					FNXW_STRCAT(wsText, wsNKTens[iDigit-1]);
				}
				else if( iType == 1 &&			// Sino-Korean
						 nWhole == 2 &&			// Tens place
						 *(pwc+1) == '6' )		// Next number is 6
				{
					FNXW_STRCAT(wsText, wsSKDigits[iDigit]);
					FNXW_STRCAT(wsText, wsSKExceptions[0]);		//	Don't say sip, say sim
				}
				else if( iDigit > 1 )
				{
					// In the tens place or higher say the digit followed by the magnitude (eg. four thousand)
					FNXW_STRCAT(wsText, iType==1 ? wsSKDigits[iDigit] : bUseReduced ? wsNKReducedDigits[iDigit] : wsNKDigits[iDigit]);
					FNXW_STRCAT(wsText, wsSKMag[nWhole-2]);
				}
				else if( iDigit == 0 &&
						 (nWhole == 13 ||
						  nWhole == 9 ||
						  nWhole == 5 ) )
				{
					FNXW_STRCAT(wsText, wsSKMag[nWhole-2]);
				}
			}
			nWhole--;
		}
		else if( nFrac > 0 )
		{
			// For the fractional parts just say each value as a digit (eg. point one two three four)
			FNXW_STRCAT(wsText, iType==1 ? wsSKDigits[iDigit] : wsNKDigits[iDigit]);
			nFrac--;
		}

	}

	return iLen;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrNormalizeDigits
 * DESC: 	Convert a string of 1 or more digits into the Hangul
			characters for each individual digit
 * IN:		wsInput - pointer to the string of digits
			bOk2UseNK - use NK in cases of 11, 22 or 55
 * OUT:		wsNormal - Hangul output string
 * RETURN:	number of characters converted on success
 * NOTES:	
 *END_HEADER***************************/
int KrNormalizeDigits(wchar_t *wsInput, wchar_t *wsNormal, int bOk2UseNK)
{
	wchar_t
		*pwc,
		wsNum[4],
		wsText[12];

	wsNormal[0] = 0x00;
	for( pwc=wsInput; *pwc; pwc++ )
	{
		if( ! KrIsDigit(*pwc) )
			break;
		wsNum[0] = *pwc;
		wsNum[1] = 0x00;

		if( bOk2UseNK &&
			(*pwc == '1' && (*(pwc-1) == '1' || *(pwc+1) == '1') ) ||	// say "hana hana" instead of "il il" for clarity
			(*pwc == '2' && (*(pwc-1) == '2' || *(pwc+1) == '2') ) ||	// say "dul dul" instead of "i i"
			(*pwc == '5' && (*(pwc-1) == '5' || *(pwc+1) == '5') ) )	// say "daseot daseot" instead of "o o"
			KrNormalizeNumber(wsNum, wsText, 2, 0);
		else
			KrNormalizeNumber(wsNum, wsText, 1, 0);

		if( wsNormal[0] )
			FNXW_CHRCAT(wsNormal, SYMBOL_COMMA);
		FNXW_STRCAT(wsNormal, wsText);
	}

	return pwc-wsInput;
}

// List of recognized Korean Date/Time formats
typedef enum {
	eYYYYMMDD=1,
	eYYMMDD,
	eMMDDYYYY,
	eMMDDHHMM,
	eDDHHMM,
	eHHMM,
	eHMM,
	eNNNNY,
	eNNM,
	eNND
} KR_DATE_TIME;

/*FUNCTION_HEADER**********************
 * NAME:	;KrIsDateTime
 * DESC: 	Determine if the input string fits one of the date/time forms
 * IN:		pwsText - pointer to the input string
 * OUT:		
 * RETURN:	0 if not a date/time, 
			1 if HH:MM
			2 if MM.DD.HH:MM
			3 if DD.HH:MM
			4 if YYYY-MM-DD or YYYY/MM/DD or YYYY.MM.DD
			5 if ####Y
			6 if ##M
			7 if ##D
			8 if H:MM
			9 YY/MM/DD or YY-MM-DD or YY.MM.DD
 * NOTES:	(Y,M,D are the Korean symbols for Year, Month and Day)

 *END_HEADER***************************/
int KrIsDateTime(wchar_t *pwsText)
{
#if defined CASIO_SH3 && defined _BIGENDIAN_
	wchar_t 
		*pwc = pwsText,
	    wsDateSeps[] = {0x2f,0x2d,0x2e}; //hex equivalent for "/-."
#else
	wchar_t 
		*pwc = pwsText,
		wsDateSeps[] = L"/-.";
#endif

	if( KrIsNumber(pwc) &&		// H
		KrIsNumber(pwc+1) &&	// H
		*(pwc+2) == ':' &&		// :
		KrIsNumber(pwc+3) &&	// M
		KrIsNumber(pwc+4) &&	// M
		!KrIsNumber(pwc+5) )
	{
		return eHHMM;
	}

	if( KrIsNumber(pwc) &&		// H
		*(pwc+1) == ':' &&		// :
		KrIsNumber(pwc+2) &&	// M
		KrIsNumber(pwc+3) &&	// M
		!KrIsNumber(pwc+4) )
	{
		return eHMM;
	}

	if( KrIsNumber(pwc) &&		// M
		KrIsNumber(pwc+1) &&	// M
		*(pwc+2) == '.' &&		// .
		KrIsNumber(pwc+3) &&	// D
		KrIsNumber(pwc+4) &&	// D
		*(pwc+5) == '.' &&		// .
		KrIsNumber(pwc+6) &&	// H
		KrIsNumber(pwc+7) &&	// H
		*(pwc+8) == ':' &&		// :
		KrIsNumber(pwc+9) &&	// M
		KrIsNumber(pwc+10) &&	// M
		!KrIsNumber(pwc+11) )
	{
		return eMMDDHHMM;
	}

	if( KrIsNumber(pwc) &&		// D
		KrIsNumber(pwc+1) &&	// D
		*(pwc+2) == '.' &&		// .
		KrIsNumber(pwc+3) &&	// H
		KrIsNumber(pwc+4) &&	// H
		*(pwc+5) == ':' &&		// :
		KrIsNumber(pwc+6) &&	// M
		KrIsNumber(pwc+7) &&	// M
		!KrIsNumber(pwc+8) )
	{
		return eDDHHMM;
	}

	if( KrIsNumber(pwc) &&		// Y
		KrIsNumber(pwc+1) &&	// Y
		KrIsNumber(pwc+2) &&	// Y
		KrIsNumber(pwc+3) &&	// Y
		FNXW_STRCHR(wsDateSeps, *(pwc+4)) &&
		KrIsNumber(pwc+5) &&	// M
		KrIsNumber(pwc+6) &&	// M
		FNXW_STRCHR(wsDateSeps, *(pwc+7)) &&
		KrIsNumber(pwc+8) &&	// D
		KrIsNumber(pwc+9) &&	// D
		!KrIsNumber(pwc+10) )
	{
		return eYYYYMMDD;
	}

	if( KrIsNumber(pwc) &&		// Y
		KrIsNumber(pwc+1) &&	// Y
		KrIsNumber(pwc+2) &&	// Y
		KrIsNumber(pwc+3) &&	// Y
		*(pwc+4) == HANGUL_YEAR )		// Korean Year Symbol
	{
		return eNNNNY;
	}

	if( KrIsNumber(pwc) &&		// M
		KrIsNumber(pwc+1) &&	// M
		*(pwc+2) == HANGUL_MONTH )		// Korean Month Symbol
	{
		return eNNM;
	}

	if( KrIsNumber(pwc) &&		// M
		*(pwc+1) == HANGUL_MONTH )		// Korean Month Symbol
	{
		return eNNM;
	}

	if( KrIsNumber(pwc) &&		// D
		KrIsNumber(pwc+1) &&	// D
		*(pwc+2) == HANGUL_DAY )		// Korean Day Symbol
	{
		return eNND;
	}
	if( KrIsNumber(pwc) &&		// D
		*(pwc+1) == HANGUL_DAY )		// Korean Day Symbol
	{
		return eNND;
	}

	if( KrIsNumber(pwc) &&		// Y
		KrIsNumber(pwc+1) &&	// Y
		FNXW_STRCHR(wsDateSeps, *(pwc+2)) &&
		KrIsNumber(pwc+3) &&	// M
		KrIsNumber(pwc+4) &&	// M
		FNXW_STRCHR(wsDateSeps, *(pwc+5)) &&
		KrIsNumber(pwc+6) &&	// D
		KrIsNumber(pwc+7) &&	// D
		!KrIsNumber(pwc+8) )
	{
		return eYYMMDD;
	}

	if( KrIsNumber(pwc) &&		// M
		KrIsNumber(pwc+1) &&	// M
		FNXW_STRCHR(wsDateSeps, *(pwc+2)) &&
		KrIsNumber(pwc+3) &&	// D
		KrIsNumber(pwc+4) &&	// D
		FNXW_STRCHR(wsDateSeps, *(pwc+5)) &&
		KrIsNumber(pwc+6) &&	// Y
		KrIsNumber(pwc+7) &&	// Y
		KrIsNumber(pwc+8) &&	// Y
		KrIsNumber(pwc+9) &&	// Y
		!KrIsNumber(pwc+10) )
	{
		return eMMDDYYYY;
	}
	return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;KrNormalizeDateTime
 * DESC: 	Normalize a Date/Time sequence if present
 * IN:		pwsText - pointer to beginning of text to be normalized
			piType - (in/out) date/time format type
 * OUT:		pwsNormal - normalized text
 * RETURN:	number of characters used from pwsText
 * NOTES:	
 *END_HEADER***************************/
int KrNormalizeDateTime(wchar_t *pwsText, wchar_t *pwsNormal, int *piType)
{
	wchar_t
		*pwc=pwsText,
		wsNumber[128],
		wsYear[5],
		wsMon[3],
		wsDay[3],
		wsHour[3],
		wsMin[3];
	int
		iYear,
		iHour,
		iMin;

	memset(wsYear, 0, sizeof(wsYear));
	memset(wsMon, 0, sizeof(wsMon));
	memset(wsDay, 0, sizeof(wsDay));
	memset(wsHour, 0, sizeof(wsHour));
	memset(wsMin, 0, sizeof(wsMin));

	if( *piType == 0 )
	{
		if( (*piType = KrIsDateTime(pwsText)) == 0 )
			return 0;
	}

	switch(*piType)
	{
		case eHHMM:							// HH:MM
			FNXW_STRNCPY(wsHour, pwc, 2);	pwc += 3;
			FNXW_STRNCPY(wsMin, pwc, 2);	pwc+= 2;
			break;
		case eHMM:							// H:MM
			FNXW_STRNCPY(wsHour, pwc, 1);	pwc += 3;
			FNXW_STRNCPY(wsMin, pwc, 2);	pwc+= 2;
			break;
		case eMMDDHHMM:						// MM.DD.HH:MM
			FNXW_STRNCPY(wsMon, pwc, 2);	pwc += 3;
			FNXW_STRNCPY(wsDay, pwc, 2);	pwc += 3;
			FNXW_STRNCPY(wsHour, pwc, 2);	pwc += 3;
			FNXW_STRNCPY(wsMin, pwc, 2);	pwc += 2;
			break;
		case eDDHHMM:						// DD.HH:MM
			FNXW_STRNCPY(wsDay, pwc, 2);	pwc += 3;
			FNXW_STRNCPY(wsHour, pwc, 2);	pwc += 3;
			FNXW_STRNCPY(wsMin, pwc, 2);	pwc += 2;
			break;
		case eYYYYMMDD:						// YYYY-MM-DD
			FNXW_STRNCPY(wsYear, pwc, 4);	pwc += 5;
			FNXW_STRNCPY(wsMon, pwc, 2);	pwc += 3;
			FNXW_STRNCPY(wsDay, pwc, 2);	pwc += 2;
			break;
		case eYYMMDD:						// YY-MM-DD
			FNXW_STRNCPY(wsYear, pwc, 2);	pwc += 3;
			FNXW_STRNCPY(wsMon, pwc, 2);	pwc += 3;
			FNXW_STRNCPY(wsDay, pwc, 2);	pwc += 2;
			break;
		case eMMDDYYYY:						// MM/DD/YYYY
			FNXW_STRNCPY(wsMon, pwc, 2);	pwc += 3;
			FNXW_STRNCPY(wsDay, pwc, 2);	pwc += 3;
			FNXW_STRNCPY(wsYear, pwc, 4);	pwc += 4;
			break;
		case eNNNNY:						// ####Y
			FNXW_STRNCPY(wsYear, pwc, 4);	pwc += 5;
			break;
		case eNNM:							// ##M
			if( *(pwc+1) == HANGUL_MONTH )
			{
				FNXW_STRNCPY(wsMon, pwc, 1);	
				pwc += 2;
			}
			else
			{
				FNXW_STRNCPY(wsMon, pwc, 2);	
				pwc += 3;
			}
			break;
		case eNND:							// ##D
			if( *(pwc+1) == HANGUL_DAY )
			{
				FNXW_STRNCPY(wsDay, pwc, 1);	
				pwc += 2;
			}
			else
			{
				FNXW_STRNCPY(wsDay, pwc, 2);	
				pwc += 3;
			}
			break;
	}

	pwsNormal[0] = 0x00;

	// Build normalized string
	if( wsYear[0] )
	{
		if( FNXW_STRLEN(wsYear) == 2 )
		{
			iYear = FNXW_ATOI(wsYear);
			if( iYear < 100 )			// Convert a 2 digit year to a 4 digit year
			{
				if( iYear < 20 )		// 2000 - 2019 (this is an arbitrary breaking point)
					iYear += 2000;
				else					// 1920 - 1999
					iYear += 1900;
				FNXW_ITOA(iYear, wsYear, 10);
			}
		}
		KrNormalizeNumber(wsYear, wsNumber, 1, 0);
		FNXW_CHRCAT(pwsNormal, 0x0020);
		FNXW_STRCAT(pwsNormal, wsNumber);
		FNXW_CHRCAT(pwsNormal, 0x0020);
		FNXW_CHRCAT(pwsNormal, HANGUL_YEAR);
	}
	if( wsMon[0] )
	{
		KrNormalizeNumber(wsMon, wsNumber, 1, 1);
		if( *wsNumber == 0xc2ed &&					// change sib-wol to si-wol
			*(wsNumber+1) == 0x00 )
		{
			*wsNumber = 0xc2dc;
		}
		else if( *wsNumber == 0xc721)				// yug-wol to yu-wol
		{
			*wsNumber = 0xc720;
		}

		FNXW_CHRCAT(pwsNormal, 0x0020);
		FNXW_STRCAT(pwsNormal, wsNumber);
		FNXW_CHRCAT(pwsNormal, HANGUL_MONTH);
	}
	if( wsDay[0] )
	{
		KrNormalizeNumber(wsDay, wsNumber, 1, 0);
		FNXW_CHRCAT(pwsNormal, 0x0020);
		FNXW_STRCAT(pwsNormal, wsNumber);
		FNXW_CHRCAT(pwsNormal, HANGUL_DAY);
	}
	if( wsHour[0] )
	{
		iHour = FNXW_ATOI(wsHour);
		KrNormalizeNumber(wsHour, wsNumber, iHour<=12 ? 2 : 1, iHour<=12 ? 1 : 0);
		FNXW_CHRCAT(pwsNormal, 0x0020);
		FNXW_STRCAT(pwsNormal, wsNumber);
		FNXW_CHRCAT(pwsNormal, HANGUL_HOUR);
	}
	if( wsMin[0] )
	{
		iMin = FNXW_ATOI(wsMin);
		if( iMin > 0 )
		{
			KrNormalizeNumber(wsMin, wsNumber, 1, 0);
			FNXW_CHRCAT(pwsNormal, 0x0020);
			FNXW_STRCAT(pwsNormal, wsNumber);
			FNXW_CHRCAT(pwsNormal, HANGUL_MIN);
		}
	}

	return pwc-pwsText;
}


/*FUNCTION_HEADER**********************
 * NAME:	;KrNormalizeText
 * DESC: 	Normalize some text that is not in Hangul so that it is in Hangul
 * IN:		wsInput - pointer to the non-Hangul text
 * OUT:		wsHangul - text normalized to Hangul
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int KrNormalizeText(wchar_t *wsInput, wchar_t *wsHangul)
{
	int
		iFormat,
		nUsed=0;
	
	if( (iFormat = KrIsDateTime(wsInput)) )
	{
		nUsed = KrNormalizeDateTime(wsInput, wsHangul, &iFormat);
	}
	else if( (iFormat = KrIsPhoneNumber(wsInput)) )
	{
		nUsed = KrNormalizePhoneNumber(wsInput, wsHangul, iFormat);
	}
	else if( (nUsed = KrIsNumber(wsInput)) )
	{
		if( KrIsCountingWord(wsInput+nUsed) )
		{
			nUsed = KrNormalizeNumber(wsInput, wsHangul, 2, 1);		// Pronounce with Native/Pure Korean numbers
		}
		else
		{
			nUsed = KrNormalizeNumber(wsInput, wsHangul, 1, 0);
		}
	}
	else if( KrIsSymbol(wsInput) )
	{
		nUsed = KrNormalizeSymbol(wsInput, wsHangul);
	}
	else if( KrIsEmail(wsInput) )
	{
		nUsed = KrNormalizeEmail(wsInput, wsHangul);
	}
	else if( KrIsURL(wsInput) )
	{
		nUsed = KrNormalizeURL(wsInput, wsHangul);
	}
	else if( KrIsAlpha(wsInput) )
	{
		nUsed = KrNormalizeAlphaString(wsInput, wsHangul);
	}
	else
	{
		FNXW_STRCPY(wsHangul, wsInput);
		nUsed = FNXW_STRLEN(wsInput);
	}

	return nUsed;
	
}
