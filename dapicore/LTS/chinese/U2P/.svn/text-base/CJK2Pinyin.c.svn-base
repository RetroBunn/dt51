/*C_HEADER_FILE****************************************************************
FILE			:	Unicode2Pinyin.c
DESC			:	This program opens a text file with Chinese characters of poly sounds
TABS			:	4
OWNER			:	Fonix
DATE CREATED	:	7/11/2005 by Chuck Liu	

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/

#include "port.h"
#include "CJK2Pinyin.h"

#ifdef DTALK_CH_EXPORTS
#include "ls_def.h"
#include "ls_rule.h"
#endif

#define CH_ERHUA_HANZI 0x513f


#define WCHAR_TAB	0x0009
#define WCHAR_SP	0x0020
#define WCHAR_LF	0x000a
#define WCHAR_NL	0x000d
#define WCHAR_LSQBR 0x005b


const wchar_t delims[] = {WCHAR_SP,
						WCHAR_TAB,
						WCHAR_LF,
						WCHAR_NL};


#define TEXT_NORM	// For text normalization.

#ifdef TEXT_NORM	
#	define DIGIT_NORM				 1	//	digit and digit+symbol
#	define US_DOLLAR_NORM			 2	//	US currency unit.
#	define CHINESE_YUAN_NORM		 3	//	Chinese currency unit.
#	define UK_POUND_NORM			 4	//	UK currency unit.
#	define EURO_DOLLAR_NORM			 5	//	Euro currency unit.
#	define ENGLISH_LETTER_NORM		 6  //  [a, z], [A, Z]

#	define SECT_SIZE				 4	// In the unit of 10000.
#	define MAX_SYMBOL_PINYINS		 5	// Example, 1 pinyin for "." in 123.456, 3 pinyins for "%" in 12.3%.
#	define YEAR_UNICODE			0x5E74	// unicode for "year"
#	define DEGREE_UNICODE		0x00B0	// degee for temperature (15°C, 50°F) or for angle 30° in math. 
#	define US_DOLLAR_UNICODE	0x0024	
#	define CHINESE_YUAN_UNICODE	0x00A5
#	define UK_POUND_UNICODE		0x00A3	
#	define EURO_DOLLAR_UNICODE	0x20AC	

char DigitPinyins[10][7] = {"ling2",  "yi1", "er4", "san1", "si4", 
							 "wu3", "liu4", "qi1",  "ba1", "jiu3"};	// pinyin for [0, 1, ..., 9]
char DecimalPinyins[3][7] = {"qian1", "bai3", "shi2"};	// pinyin for {1000, 100, 10}
char SectPinyins[2][7] = {"wan4", "yi4"};				// pinyin for {10000, 100000000}
char DotPinyin[7] = {"dian3"};	// pinyin for '.' in 123.456.
char PercentPinyin[21] = {"bai3fen1zhi1"};
char DegreePinyin[7] = {"du4"};
char CelsiusPinyin[14] = {"she4shi4"};
char FahrenheitPinyin[14] = {"hua2shi4"};
char USDollarPinyin[14] = {"mei3yuan2"};
char ChineseYuanPinyin[7] = {"yuan2"}; 
char UKPoundPinyin[14] = {"ying1bang4"};
char EuroDollarPinyin[14] = {"ou1yuan2"}; 
char TimeUnitPinyins[3][7] = {"dian3", "fen1", "miao3"};
char EnglishLettPinyins[26][14] = {"ei1", "bi4", "xi1", "di4", "yi4", "ei2fu5", "ji4", "ei2qu5", "ai4", "ji5ei3", 
								   "ke5ei3", "ei2lao5", "ei2mu5", "en1", "ou1", "pi4", "kou4", "a2er5", "ei2si5", "ti4", 
								   "you1", "wei1", "da5bu5niu5", "ei5ke5si5", "wai4", "zei4"};
#endif


#ifdef TEXT_NORM
/*FUNCTION_HEADER**********************
 * NAME:	;AddTextNormPart
 * DESC: 	Add the next part at the end of previously normalized text.
 * IN:		ppwcHanzi - Address of pointer to current character of input text. 
			sPinyin -  Address to pinyin sting that has contained previously normalized text.
			sNextPinyin - Pinyin string for next part.
			iNextNumChars - Number characters of the next part as appeared in the input text.
 * OUT:		Pinyin for next part is appended at the end of sPinyin. 
			*ppwcHanzi is moved to the position after the next part.
 * RETURN:	Return the length of the next part that has been added.
			Return -1 on error.
 * NOTES:	
 *END_HEADER***************************/
static int AddTextNormPart(wchar_t **ppwcHanzi, char *sPinyin, char *sNextPinyin, int iNextNumChars)  
{	
	int iNextPinyinLen;

	iNextPinyinLen = FNX_STRLEN(sNextPinyin);

	// Move cur char to the position after the next part.
	(*ppwcHanzi) += iNextNumChars;

	if(sPinyin)	
		FNX_STRCAT(sPinyin, sNextPinyin);

	return iNextPinyinLen;
}
#endif


#ifdef TEXT_NORM
/*FUNCTION_HEADER**********************
 * NAME:	;InsertTextNormPart
 * DESC: 	Normalize the next part and insert it before a previously normalized part.
			For example, for 12.3%, prounciation for "%" needs to be inserted before 12.3.
 * IN:		ppwcHanzi - Address of pointer to current character of input text. 
			sPinyin - Address to pinyin sting that has contained previously normalized part.
			iPrevLen - Lengh of pinyin in previously parsed part.
			sNextPinyin - Pinyin string for next part.
			iNextNumChars - Number characters of the next part as appeared in the input text.
 * OUT:		Pinyin for next part is inserted into sPinyin before previously parsed part. 
			*ppwcHanzi is moved to the position after the next part.
 * RETURN:	Return the length of combined pinyin (previous part + next part).
			Return -1 on error.
 * NOTES:	
 *END_HEADER***************************/
static int InsertTextNormPart(wchar_t **ppwcHanzi, char *sPinyin, int iPrevLen, char *sNextPinyin, int iNextNumChars)  
{	
	int iTotalLen, iNextPinyinLen;

	iTotalLen = iPrevLen;	
  
	iNextPinyinLen = FNX_STRLEN(sNextPinyin);
	iTotalLen += iNextPinyinLen;
	// Move cur char to the position after the next part.
	(*ppwcHanzi) += iNextNumChars;

	// Need to insert symbol pinyin before the part.
	if(sPinyin)
	{
		int i, iPinyinLen;

		iPinyinLen = FNX_STRLEN(sPinyin);

		// shifting prev pinyin forward by "iNextPinyinLen".
		// For example, iPrevLen = 15, 
		//	iPinyinLen = 100, iNextPinyinLen = 10,
		// Then move:
		//	sPinyin[99] -> sPinyin[99+10]
		//  sPinyin[98] -> sPinyin[98+10]
		//  .............................
		//  sPinyin[85] -> sPinyin[85+10]
		for(i = 0; i < iPrevLen; i++)
			sPinyin[iPinyinLen - 1 + iNextPinyinLen - i] = sPinyin[iPinyinLen - 1 - i];   

		sPinyin[iPinyinLen + iNextPinyinLen] = '\0';	// Put '\0' at the end of string.

		// Now need to insert sSymbolPinyin.
		// In above example:
		// sPinyin[85] = sNextPinyin[0]
		// sPinyin[86] = sNextPinyin[1]
		// .............................
		// sPinyin[94] = sNextPinyin[9]
		for(i = 0; i < iNextPinyinLen; i++)
			sPinyin[iPinyinLen - iPrevLen + i] = sNextPinyin[i];
	}
	return iTotalLen;
}
#endif

#ifdef TEXT_NORM 
/*FUNCTION_HEADER**********************
 * NAME:	;PostProcDigitNorm
 * DESC: 	Need to check if digits are followed by some special symbols such as "%".
			For example, for12.3%, prounciation for "%" needs to be inserted before 12.3.
 * IN:		ppwcHanzi - Address of pointer to current character of input text. 
			sPinyin - Address to append the combined pinyin parsed from text normalization.
			iPrevDigitLen - Lengh of pinyin in previously parsed digits.
 * OUT:		If post processing is needed, pinyin for special symol is inserted into sPinyin 
			before previously parsed digits. *ppwcHanzi is moved to the position after 
			the post processed special symbol.
 * RETURN:	Return the length of combined pinyin parsed from the normalized text (including
			both special symbol and digits).
			Return -1 on error.
 * NOTES:	
 *END_HEADER***************************/
static int PostProcDigitNorm(wchar_t **ppwcHanzi, char *sPinyin, int iPrevDigitLen)
{
	wchar_t *pwcCur, c;
	int iTotalLen, iNextNumChars, iLen;
	char *sNextPinyin;

	// Points to the current position of input text.
	pwcCur = *ppwcHanzi;
	c = *pwcCur;
	iTotalLen = iPrevDigitLen;	

	if(c == '%')	// Example: 12.3%
	{
		iNextNumChars = 1;
		iTotalLen = InsertTextNormPart(ppwcHanzi, sPinyin, iPrevDigitLen, PercentPinyin, iNextNumChars);
	}
	else if (c == DEGREE_UNICODE) // degee for temperature (15°C, 50°F) or for angle 30° in math.
	{
		// Add pinyin for "°" to sPinyin.
		iNextNumChars = 1;
		iLen = AddTextNormPart(ppwcHanzi, sPinyin, DegreePinyin, iNextNumChars);
		iTotalLen += iLen;
	
		// Check if the next one is "C" or "F".
		pwcCur++;
		c = *pwcCur;
		// Example: for 50°F, Need to insert pinyin for "F" before "50°"
		if(c == 'C' || c == 'F')
		{
			if(c == 'C')
				sNextPinyin = CelsiusPinyin;
			else //if(c == 'F')
				sNextPinyin = FahrenheitPinyin;

			iNextNumChars = 1;
			// Example: for 50°F, input "iTotalLen" is length for "50°", and returned "iTotalLen" is length for "50°F"
			iTotalLen = InsertTextNormPart(ppwcHanzi, sPinyin, iTotalLen, sNextPinyin, iNextNumChars);
		}
	}
	//other cases.
	//else if (c == )
	//{
	//}

	return iTotalLen;
}
#endif




#ifdef TEXT_NORM 
/*FUNCTION_HEADER**********************
 * NAME:	;SeqDigitNorm
 * DESC: 	Process text normalization for a sequence of digits that are parsed 
			as digit sequence (rather than a number). For example, in "123.456", 
			"456" is parsed as a sequence of digits. In contrast, "123" 
			is parsed as a number (with pinyin from unit "100" and "10"). 
			It processes digits until reaching a non-digit character.
 * IN:		ppwcHanzi - Address of pointer to current character of input text. 
			sPinyin - Address to append the combined pinyin parsed from text normalization.
 * OUT:		sPinyin is appended with the combined pinyin of the normalized text.
			*ppwcHanzi is moved to the position after the normalized text.
 * RETURN:	Return the length of combined pinyin parsed from the normalized text.
			Return -1 on error.
 * NOTES:	
 *END_HEADER***************************/
static int SeqDigitNorm(wchar_t **ppwcHanzi, char *sPinyin)
{
	wchar_t *pwcCur, c;
	int iDigit, iTotalLen, iLen, iNextNumChars;
	char *sDigitPinyin;

	// Point to the current position of input text.
	pwcCur = *ppwcHanzi;
	iTotalLen = 0;	
	c = *pwcCur; 
	while(c >= '0' && c <= '9')	// Read all subsequent digits.
	{
		iDigit = (int) (c - '0');
		sDigitPinyin = DigitPinyins[iDigit];
		iNextNumChars = 1;
		iLen = AddTextNormPart(ppwcHanzi, sPinyin, sDigitPinyin, iNextNumChars);
		iTotalLen += iLen;
		pwcCur++;
		c = *pwcCur;
	}
	return iTotalLen;
}
#endif


#ifdef TEXT_NORM 
/*FUNCTION_HEADER**********************
 * NAME:	;NumberDigitNorm
 * DESC: 	Process text normalization for a sequence of digits that are parsed as a number
			(rather than a sequence of digits). For example, in "123.456", "123" is parsed as a number
			(with pinyin from unit "100" and "10"). In contrast, "456" is parsed as a sequence of digits.
			If there are more than one sections than need to be parsed. It will recursively call
			NumberDigitNorm() until processing all sections.
 * IN:		ppwcHanzi - Address of pointer to current character of input text. 
			sPinyin - Address to append the combined pinyin parsed from text normalization.
			iSectIndex - Index of curret sections (range [0, (iNumSects -1)]).
			iNumSects - total number of sections for this sequence of digits.
			iNumCurDigits - number of digits in current section.
			bLastDigitIsZero - if the last digit of previous section is "0".
 * OUT:		sPinyin is appended with the combined pinyin of the normalized text.
			*ppwcHanzi is moved to the position after the normalized text.
 * RETURN:	Return the length of combined pinyin parsed from the normalized text.
			Return -1 on error.
 * NOTES:	Section is defined as a set of 4 digits. For example: 1234 has one section.
			12345 has 2 sections. 123456789 has 3 sections. 
 *END_HEADER***************************/
static int NumberDigitNorm(wchar_t **ppwcHanzi, char *sPinyin, int iSectIndex, 
				   int iNumSects, int iNumCurDigits, BOOL bLastDigitIsZero)
{
	wchar_t *pwcCur, *pwcHanzi;
	int i, iDigit, iNumZeros;
	char *sDigitPinyin, *sDecimalPinyin, *sSectPinyin;
	BOOL bPrevDigitIsZero;
	BOOL bNextLastDigitIsZero;
	int iTotalLen, iLen, iDecimalIndex, iSectUnitIndex;

	// pwcHanzi is point to the current position of input text.
	pwcCur = pwcHanzi = *ppwcHanzi;

	// Move *ppwcHanzi to the begin of the next section.
	// For example, if currently parse 123 in 1234567 then need to
	// move to start of "4567".
	// Update it now for the next recursive call of NumberDigitNorm()
	(*ppwcHanzi) += iNumCurDigits;

	// Check number of zeros.
	iNumZeros = 0;
	for(i = 0; i < iNumCurDigits; i++)
	{
		// iDigit is a number in [0, 9].
		iDigit = (int) ((char) *pwcCur - '0');
		if(iDigit == 0)
			iNumZeros++;
		pwcCur++;	
	}

	// If all digit are zero.
	bNextLastDigitIsZero = FALSE;
	if(iNumZeros == iNumCurDigits)
	{
		// If there is only one section, such as 0 or 00,
		// just pronouce one "0".
		if(iNumSects == 1)
		{
			sDigitPinyin = DigitPinyins[0];
			iLen = FNX_STRLEN(sDigitPinyin);
			if(sPinyin)
				FNX_STRCAT(sPinyin, sDigitPinyin);
			return iLen;
		}
		else	// Such as "0000" inside 10000000 or inside 1000000001
		{
			// Pronounce nothinng. But notify the next the prev last digit is "0".
			// For the case 100001000.
			bNextLastDigitIsZero = TRUE;		
			// Need to propagate to the next section.
			if(iSectIndex < (iNumSects - 1))
			{
				iLen = 0;
				iSectIndex++;
				return (iLen + NumberDigitNorm(ppwcHanzi, sPinyin, iSectIndex, iNumSects, 
													SECT_SIZE, bNextLastDigitIsZero));
			}
			else
				return 0;
		}
	}

	// If there is at least one non-zero digit.
	iTotalLen = 0;
	bNextLastDigitIsZero = FALSE;
	bPrevDigitIsZero = bLastDigitIsZero;
	pwcCur = pwcHanzi;	
	for(i = 0; i < iNumCurDigits; i++)
	{
		// iDecimalIndex (0, 1, 2, 3) => (1000, 100, 10, 1).
		iDecimalIndex = i + SECT_SIZE - iNumCurDigits;

		// iDigit is a number in [0, 9].
		iDigit = (int) ((char) *pwcCur - '0');
		if(iDigit != 0)
		{
			// If current digit is 0 while previous one is "0" (or multiple 0 before that),
			// then need to add pinyin for a "0" (add only one even if there are multiple "0"). 
			if(bPrevDigitIsZero) 
			{
				sDigitPinyin = DigitPinyins[0];
				iLen = FNX_STRLEN(sDigitPinyin);
				iTotalLen += iLen;
				if(sPinyin)
					FNX_STRCAT(sPinyin, sDigitPinyin);
				
				bPrevDigitIsZero = FALSE;
			}

			// Now Need to add current digit

			// There is a special case for 10 - 19: skip the decimal unit for 10.
			// It is applied if it is on the first section.
			// Example: 12, 120000. 
			if(iSectIndex == 0 && iNumCurDigits == 2 && iDecimalIndex == 2 && iDigit == 1)
					goto next;
			
			sDigitPinyin = DigitPinyins[iDigit];
			iLen = FNX_STRLEN(sDigitPinyin);
			iTotalLen += iLen;
			if(sPinyin)
				FNX_STRCAT(sPinyin, sDigitPinyin);
next:
			// Need to add decimal unit: for 1000, 100, 10 (but not for 1).
			if(iDecimalIndex < 3) 
			{
				sDecimalPinyin = DecimalPinyins[iDecimalIndex];
				iLen = FNX_STRLEN(sDecimalPinyin);
				iTotalLen += iLen;
				if(sPinyin)
					FNX_STRCAT(sPinyin, sDecimalPinyin);
			}
		}
		else	// If this is an zero.
		{
			bPrevDigitIsZero = TRUE;
		}
		pwcCur++;
	}

	// If this is not the last section.
    // Need to add section unit: 10000 (wan4) or 100000000 (yi4)
	// For example: If there are 3 sections, such as 1000 0000 0000, 
	//   then section index 0 => yi. section index 1 => wan. Section index 2 => nothing.
	if(iSectIndex < (iNumSects -1))
	{
		iSectUnitIndex = (iNumSects - iSectIndex) % 2; 
		sSectPinyin = SectPinyins[iSectUnitIndex];
		iLen = FNX_STRLEN(sSectPinyin);
		iTotalLen += iLen;
		if(sPinyin)
			FNX_STRCAT(sPinyin, sSectPinyin);
		// Need to propagate to next section.
		iSectIndex++;
		bNextLastDigitIsZero = bPrevDigitIsZero;
		return (iTotalLen + NumberDigitNorm(ppwcHanzi, sPinyin, iSectIndex, iNumSects, 
													SECT_SIZE, bNextLastDigitIsZero));
	}
	else	// If this is the last section.
		return iTotalLen;
}
#endif


#ifdef TEXT_NORM 
/*FUNCTION_HEADER**********************
 * NAME:	;TimeNorm
 * DESC: 	Process text normalization for time in the format such as 10:50:12
 * IN:		ppwcHanzi - Address of pointer to current character of input text. 
			sPinyin - Address to append the combined pinyin parsed from text normalization.
 * OUT:		sPinyin is appended with the combined pinyin of the normalized text.
			*ppwcHanzi is moved to the position after the normalized text.
 * RETURN:	Return the length of combined pinyin parsed from the normalized text.
 * NOTES:	Here time (such as 10:50:12) is normalized as a clock time (instead of length of time).
 *END_HEADER***************************/
static int TimeNorm(wchar_t **ppwcHanzi, char *sPinyin)
{
	BOOL bFinishProc;
	int iLen, iTotalLen, iNumTimeUnits;
	wchar_t c, *pwcCur;
	int iNumDigits, iNumSects, iSectIndex, iNumCurDigits, iNextNumChars;
	BOOL bLastDigitIsZero;

	iTotalLen = 0;
	bFinishProc = FALSE;
	iNumTimeUnits = 0;
	while(!bFinishProc)	
	{
		// Start of the character position in "ppwcHanzi".
		pwcCur = *ppwcHanzi;

		iNumDigits = 0;
		c = *pwcCur;
		while(c >= '0' && c <= '9')
		{
			iNumDigits++;
			pwcCur++;
			c = *pwcCur;
		}
			
		// Example: 1-4 digits (1, 12, 123, 1234) has one section. 
		//			5-8 digit (12345, 123456) has 2 sections.
		iNumSects = 1 + (iNumDigits - 1) / SECT_SIZE;
		iSectIndex = 0;
		iNumCurDigits = iNumDigits - (iNumSects - 1) * SECT_SIZE;
		bLastDigitIsZero = FALSE;
		iLen = NumberDigitNorm(ppwcHanzi, sPinyin, iSectIndex, 
						iNumSects, iNumCurDigits, bLastDigitIsZero);
		iTotalLen += iLen;

		// Add a pinyin without moving "ppwcHanzi"
		iNextNumChars = 0;
		iLen = AddTextNormPart(ppwcHanzi, sPinyin, TimeUnitPinyins[iNumTimeUnits], iNextNumChars);
		iTotalLen += iLen;

		iNumTimeUnits++;
		// Cannot have more than 3 time units (hour, minute, second). 
		if(iNumTimeUnits == 3)
			break;
		
		// Phone number has the format 123-456-7890
		// check if the next char is '-'.
		c = **ppwcHanzi;
		
		if(c == ':')	// Need to read next time unit.
		{
			// Move to the position after ':'.
			(*ppwcHanzi) += 1;

			// Need to add a symbol for a pause in pronounciation.
			// For now add ", " to cause a pause.
			if(sPinyin)
			{
				FNX_STRCAT(sPinyin, ", ");
				iTotalLen += 2;
			}
		}
		else
			bFinishProc = TRUE;
	}
	return iTotalLen;
}
#endif

#ifdef TEXT_NORM 
/*FUNCTION_HEADER**********************
 * NAME:	;PhoneNumberNorm
 * DESC: 	Process text normalization for a telephone number in the format such as 123-456-7890.
 * IN:		ppwcHanzi - Address of pointer to current character of input text. 
			sPinyin - Address to append the combined pinyin parsed from text normalization.
 * OUT:		sPinyin is appended with the combined pinyin of the normalized text.
			*ppwcHanzi is moved to the position after the normalized text.
 * RETURN:	Return the length of combined pinyin parsed from the normalized text.
 * NOTES:	
 *END_HEADER***************************/
static int PhoneNumberNorm(wchar_t **ppwcHanzi, char *sPinyin)
{
	BOOL bFinishProc;
	int iLen, iTotalLen;
	wchar_t c;
	
	iTotalLen = 0;
	bFinishProc = FALSE;
	while(!bFinishProc)	
	{
		iLen = SeqDigitNorm(ppwcHanzi, sPinyin);
		iTotalLen += iLen;

		// Phone number has the format 123-456-7890
		// check if the next char is '-'.
		c = **ppwcHanzi;
		
		if(c == '-')	//Need to read next section of digit
		{
			// Move to the position after '-'.
			(*ppwcHanzi) += 1;

			// Need to add a symbol for a pause in pronounciation.
			// For now add ", " to cause a pause.
			if(sPinyin)
			{
				FNX_STRCAT(sPinyin, ", ");
				iTotalLen += 2;
			}
		}
		else
			bFinishProc = TRUE;
	}
	return iTotalLen;
}
#endif


#ifdef TEXT_NORM 
/*FUNCTION_HEADER**********************
 * NAME:	;DigitNorm
 * DESC: 	Process text normalization for a part of input text starting with a digit.
			For example, 12345.
 * IN:		ppwcHanzi - Address of pointer to current character of input text. 
			sPinyin - Address to append the combined pinyin parsed from text normalization.
 * OUT:		sPinyin is appended with the combined pinyin of the normalized text.
			*ppwcHanzi is moved to the position after the normalized text.
 * RETURN:	Return the length of combined pinyin parsed from the normalized text.
			Return 0 if there is no valid digit.
 * NOTES:	
 *END_HEADER***************************/
static int DigitNorm(wchar_t **ppwcHanzi, char *sPinyin)
{
	wchar_t *pwcStart, *pwcCur, *pwcHanzi, c; 
	BOOL bLastDigitIsZero;
	int iNumDigits, iLen, iTotalLen, iSectIndex, iNumSects, iNumCurDigits;
	BOOL bParseSeqDigit;		 // If current number is parsed a sequence of digit or a decimal number.
	BOOL bNeedParseNextSeqDigit; // For 123.456, need to parse 456 as sequence of digits after parsing 123.	
	char sSymbolPinyin[7 * MAX_SYMBOL_PINYINS];		// For example, "." in 123.456
	BOOL bAddSymbolPinyin;
	int  iNumSymbolChars;

	// pwcHanzi now points to the begining of the text that needs to be normalized.
	pwcHanzi = *ppwcHanzi;

	pwcCur = pwcStart = pwcHanzi;
	c = *pwcCur; 
	iNumDigits = 0;
	iTotalLen = 0;

	// Read the first part of digit (such as "123" in "123.45")
	while(c >= '0' && c <= '9')
	{
		iNumDigits++;
		pwcCur++;
		c = *pwcCur;
	}

	// If there is no valid digit, no need for further processing.
	if(iNumDigits == 0)
		return iTotalLen;

	bParseSeqDigit = FALSE;
	bNeedParseNextSeqDigit = FALSE;
	bAddSymbolPinyin = FALSE;		// Such as "." for 123.456 

	// Check what is the next char.
	if(c == 0)		// If there is no more input text. Current is number (not sequence of digits).
		goto next;
	else if(c == '.')	// Example: 123.456 => need to parse 456 as sequence of digits. 
	{
		bNeedParseNextSeqDigit = TRUE;
		bAddSymbolPinyin = TRUE;
		iNumSymbolChars = 1;
		FNX_STRCPY(sSymbolPinyin, DotPinyin);  
	}
	else if (c == YEAR_UNICODE)	// If 1996 is for a year, it is pronounced as a sequence of digits.
	{
		bParseSeqDigit = TRUE;
	}
	else if(c == ':')
	{
		// If it has the format 12:30:50, treat is as the time.
		// Call the next function using the original input "ppwcHanzi" and "sPinyin".
		// After the call, "ppwcHanzi" and "sPinyin" are modified.
		return TimeNorm(ppwcHanzi, sPinyin);
	}
	else if (c == '-')
	{
		// If it has the format 123-456-7890, treat is as the telephone number.
		// Call the next function using the original input "ppwcHanzi" and "sPinyin".
		// After the call, "ppwcHanzi" and "sPinyin" are modified.
		return PhoneNumberNorm(ppwcHanzi, sPinyin);
	}

next:
	// Need to check the next char and see if it is a year, etc.
	// If it is a year, such as 2006 then, 2006 will be pronounced as 
	// a sequence of digit instead of a number.
	if(!bParseSeqDigit)
	{
		// Example: 1-4 digits (1, 12, 123, 1234) has one section. 
		//			5-8 digit (12345, 123456) has 2 sections.
		iNumSects = 1 + (iNumDigits - 1) / SECT_SIZE;
		iSectIndex = 0;
		iNumCurDigits = iNumDigits - (iNumSects - 1) * SECT_SIZE;
		bLastDigitIsZero = FALSE;
		iLen = NumberDigitNorm(ppwcHanzi, sPinyin, iSectIndex, 
						iNumSects, iNumCurDigits, bLastDigitIsZero);
		iTotalLen += iLen;
	}
	else // Is a sequnece of digits.
	{
		iLen = SeqDigitNorm(ppwcHanzi, sPinyin);
		iTotalLen += iLen;
	}

	// At this point "*ppwcHanzi" points to the location right after the input text that has been normalized.
	if(bAddSymbolPinyin)
	{
		// Now "*ppwcHanzi" points to the location after ".".
		iLen = AddTextNormPart(ppwcHanzi, sPinyin, sSymbolPinyin, iNumSymbolChars);
		iTotalLen += iLen;
	}
		
	if(bNeedParseNextSeqDigit)
	{
		iLen = SeqDigitNorm(ppwcHanzi, sPinyin);
		iTotalLen += iLen;
	}
	return iTotalLen;
}
#endif



#ifdef TEXT_NORM
/*FUNCTION_HEADER**********************
 * NAME:	;SymbolDigitNorm
 * DESC: 	Process text normalization for a part of input text starting with a symbol 
			followed by a digit, which requires that pronounciation for the digit is 
			put in front of the pronounciation for the symbol. Example,  for $12.3, 
			pronounce pinyin for "12.3" first and then pronounce pinyin for "$".
 * IN:		ppwcHanzi - Address of pointer to current character of input text. 
			sPinyin - Address to append the combined pinyin parsed from text normalization.
			iNumSymbolChars - Number of characters for the symbol in input text (such as "$").
			iType - Type of the symbol (such as US_DOLLAR_NORM). 
 * OUT:		sPinyin is appended with the combined pinyin of the normalized text (symbol + digit).
			*ppwcHanzi is moved to the position after the digit.
 * RETURN:	Return the length of combined pinyin parsed from the normalized text.
 * NOTES:	
*END_HEADER***************************/
static int SymbolDigitNorm(wchar_t **ppwcHanzi, char *sPinyin, int iNumSymbolChars, int iType)
{
	char *sSymbolPinyin;
	int iLen; 

	// Move cur char to the position after the symbol (such as "$").
	(*ppwcHanzi) += iNumSymbolChars;

	// Parse the number part after the symbol (such as "12.3" after "$").
	iLen = DigitNorm(ppwcHanzi, sPinyin);
	
	// Now sPinyin contains the pronounciation for the number.
	// Need to append the pronounciation of the symbol to sPinyin.
	switch(iType)
	{
	case US_DOLLAR_NORM:
		sSymbolPinyin = USDollarPinyin;
		break;
	case CHINESE_YUAN_NORM:
		sSymbolPinyin = ChineseYuanPinyin;
		break;
	case UK_POUND_NORM:
		sSymbolPinyin = UKPoundPinyin;
		break;
	case EURO_DOLLAR_NORM:
		sSymbolPinyin = EuroDollarPinyin;
		break;
	default:	
		return iLen; // Invalid iType: Just read digit without appending pinyin for symbol.
	}

	iLen += FNX_STRLEN(sSymbolPinyin);	// Add length for symbol to length for digit.

	if(sPinyin)	
		FNX_STRCAT(sPinyin, sSymbolPinyin);

	return iLen;
}
#endif


#ifdef TEXT_NORM
/*FUNCTION_HEADER**********************
 * NAME:	;EnglishLetterNorm
 * DESC: 	Process text normalization for an English letter ([a,z], [A,Z]). If there are digits
			following the letter (such as A12), the digits will also be parsed and normalized and 
			a sequence of digits.
 * IN:		ppwcHanzi - Address of pointer to current character of input text. 
			sPinyin - Address to append the combined pinyin parsed from text normalization.
 * OUT:		sPinyin is appended with the combined pinyin of the normalized text.
			*ppwcHanzi is moved to the position after the normalized text.
 * RETURN:	Return the length of combined pinyin parsed from the normalized text.
 * NOTES:	
*END_HEADER***************************/
static int EnglishLetterNorm(wchar_t **ppwcHanzi, char *sPinyin)
{
	int iLen, iTotalLen, iIndex;
	wchar_t c;

	iTotalLen = 0;
	c =	**ppwcHanzi;	 
	(*ppwcHanzi) += 1;	// Move to position after the letter.

	if(c >= 'a' && c <= 'z') 
		iIndex = c - 'a';
	else	// (c >= 'A' && c <= 'Z'))
		iIndex = c - 'A';

	// Pinyin + ", " (for a pause).
	iLen = FNX_STRLEN(EnglishLettPinyins[iIndex]) + 2;
	iTotalLen += iLen;
	if(sPinyin)
	{
		FNX_STRCAT(sPinyin, EnglishLettPinyins[iIndex]);
		FNX_STRCAT(sPinyin, ", ");
	}
	// if next char are number (such as CA925), then need to
	// parse them as sequence of digit.
	c = **ppwcHanzi;
	if(c >= '0' && c <= '9')
	{
		iLen = SeqDigitNorm(ppwcHanzi, sPinyin);
		iTotalLen += iLen;
	}
	return iTotalLen;
}
#endif


#ifdef TEXT_NORM 
/*FUNCTION_HEADER**********************
 * NAME:	;TextNorm
 * DESC: 	Process text normalization and get a combined pinyin from normalized text.
			For example, get pinyin for a number "12345".
 * IN:		ppwcHanzi - Address of pointer to current character of input text. 
			sPinyin - Address to append the combined pinyin parsed from text normalization.
			iType - Type of text normalization (such as digit, year, etc.).
 * OUT:		sPinyin is appended with the combined pinyin of the normalized text.
			*ppwcHanzi is moved to the position after the normalized text.
 * RETURN:	Return the length of combined pinyin parsed from the normalized text.
 * NOTES:	
 *END_HEADER***************************/
static int TextNorm(wchar_t **ppwcHanzi, char *sPinyin, int iType)
{
	int iLen; 
	int iNumSymbolChars;

	switch(iType)
	{
	case DIGIT_NORM:
		iLen = DigitNorm(ppwcHanzi, sPinyin);
		// Need to check if digits are followed by some special symbols such as "%".
		// For example, for 12.3%, prounciation for "%" needs to be inserted before 12.3.
		if(iLen > 0)
			iLen = PostProcDigitNorm(ppwcHanzi, sPinyin, iLen);
		break;
	case US_DOLLAR_NORM:
	case CHINESE_YUAN_NORM:
	case UK_POUND_NORM:
	case EURO_DOLLAR_NORM:
		iNumSymbolChars = 1;  // such as: "$".
		iLen = SymbolDigitNorm(ppwcHanzi, sPinyin, iNumSymbolChars, iType);
		break;
	case ENGLISH_LETTER_NORM:
		iLen = EnglishLetterNorm(ppwcHanzi, sPinyin);
		break;
	default:
		iLen = 0;
	}

	return iLen;
}
#endif


#ifdef TEXT_NORM	
/*FUNCTION_HEADER**********************
 * NAME:	;GetTextNormType
 * DESC: 	Determine the type of text normalization from an input character and retrun
			its type. If it is not one of text normalization types, return 0.
 * IN:		pwcHanzi - pointer to current character of input text. 
			iNumCJKChars - Number of CJK characters in previous text.
			iNumPinyinChars - Number of pinyin characters in previous text. 
 * OUT:		None.
 * RETURN:	If input character is one of text normalization types, return its type;
			otherwise return 0;
 * NOTES:	
 *END_HEADER***************************/
static int GetTextNormType(wchar_t *pwcHanzi, int iNumCJKChars, int iNumPinyinChars)
{ 
	wchar_t c;

	// There could be in 2 basic mode:
	// (1). CJK mode: CJK characters with other symbols (shuch as numbers) that needs to be 
	//		normalized.
	// (2). Pinyin mode: Sequence of pinyin and tone number. Example: ni3hao3.
	//		Text normalization can only be applied for CJK mode. Otherwise, if applied in pinyin mode, 
	//		3 in ni3hao3 will be normalized as a digit rather than treating it as number for a tone.

	// (1). If there is CJK characters in previous text (iNumCJKChars > 0), then treat it as in CJK mode.
	// (2). If there is no previous pinyin characters (iNumPinyinChars == 0). 
	//      Example: if a number 2 is appeard at the begining, it can not be a tone (tone alway follows a pinyin). 
	//      So treat it as a CJK mode in this case. 
	if(iNumCJKChars > 0 || iNumPinyinChars == 0)
	{
		c = *pwcHanzi;

		if(c >= '0' && c <= '9')
			return DIGIT_NORM;	
		else if(c == US_DOLLAR_UNICODE)
			return US_DOLLAR_NORM;
		else if(c == CHINESE_YUAN_UNICODE)
			return CHINESE_YUAN_NORM;
		else if(c == UK_POUND_UNICODE)
			return UK_POUND_NORM;
		else if(c == EURO_DOLLAR_UNICODE)
			return EURO_DOLLAR_NORM;
		else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			if(iNumCJKChars > 0)	// Need to have at least one CJK characters.
				return ENGLISH_LETTER_NORM;
			else
				return 0;
		}
	}
	return 0;
}
#endif



/*FUNCTION_HEADER**********************
 * NAME:	;ConvertToAscii
 * DESC: 	Convert unicode CJK ideographs to Pinyin+Tone
 * IN:		pVoid - pointer to TTS data structs
			lpVoid - pointer to input
			iInType - type of data in lpVoid. 0=Unicode, 1=Sjis, 2=Ksc, 3=Gbk
 * OUT:		sPinyin - pinyin+tone string
 * RETURN:	length of sPinyin on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int ConvertToAscii(void *pVoid, void *lpVoid, char *sPinyin, int iInType)
{
	char 
		sPunc[8],
		sChar[2],
		cTone,
		*pcCurTone,
		*pcSpecTone;
	wchar_t
		*wsInput,
		*pwcHanzi,
		wcSpecial=0;
	int		
		iLen=0,
		nMaxPinyin=gnPinyinPlusTones,
		nMaxCJK = gnMaxCJK,
		offset;
	Hanzi	
		*pPolyPhoneTable=NULL;

#ifdef TEXT_NORM
	int iTextNormType;
	int iNumCJKChars = 0;
	int iNumPinyinChars = 0;
#endif

#ifdef DTALK_CH_EXPORTS
	LPTTS_HANDLE_T phTTS;
	PLTS_T pLts_t;
	
	if( pVoid )
	{
		phTTS = (LPTTS_HANDLE_T)pVoid;
		pLts_t = phTTS->pLTSThreadData;
		pPolyPhoneTable = pLts_t->pPolyPhoneTable;
	}
#else
	if( pVoid )
	{
		pPolyPhoneTable = (Hanzi *)pVoid;
	}
#endif

	if( lpVoid == NULL )		// Idiot check
		return 0;

	// If it's not Unicode then we don't know what to do with it.
	// Conversion to Unicode should happen at the dectalk.dll level
	if( iInType != 0 )
	{
		return 0;
	}

	wsInput = (wchar_t *)lpVoid;

	if( sPinyin )				// Initialize output
		sPinyin[0] = 0x00;
	
	for( pwcHanzi = wsInput; *pwcHanzi; pwcHanzi++ )			// for each input character
	{
		
		// If the characters that are in the Unicode CJK range
		if( 0x4E00 <= *pwcHanzi && *pwcHanzi <= 0x9FA5)
		{
#ifdef TEXT_NORM
			iNumCJKChars++;
#endif

			if( *pwcHanzi == CH_ERHUA_HANZI && 
				pwcHanzi > wsInput )								// Can't be the first character
			{
				// if not in exceptions table
				if( sPinyin )
				{
					pcCurTone = sPinyin + FNX_STRLEN(sPinyin) -1;	// Find the tone value of the last pinyin
					cTone = *pcCurTone;								// save the tone value
					*pcCurTone = 'r';								// change pinyin+tone to pinyin+r+tone
					pcCurTone++;
					*pcCurTone = cTone;
					pcCurTone++;
					*pcCurTone = 0x00;
				}
				
				iLen++;
				continue;
			}

			// Get the initial offset in the list.
			offset = CJKUnicodeOffsetToPinyinTable[*pwcHanzi - 0x4E00];

			// There are a few values in the CJK table that are bigger than the pinyin table.
			// I don't know what they should be but too big will crash the program so set the
			// offset to 0 for now.
			if( nMaxPinyin <= offset && offset < 2500 )
				offset = 0;
			
			if (offset < 2500)
			{
				// This Hanzi always has the same pronunciation in all contexts
				if( sPinyin )
				{
					FNX_STRCAT(sPinyin, PinyinTableWithTones[offset]);
				}
				iLen += FNX_STRLEN(PinyinTableWithTones[offset]);
			}
			else
			{
				// This is a poly phone character and may have a different pronunciation 
				// depending on the context.
				int	
					iContextLen,
					iMaxMatch=0,
					iHanziOffset;
				char 
					sDefaultPinyin[10];
				wchar_t 
					*pwcHanziMatch,
					*pwsContextMatch;
				Hanzi 
					*pHanzi;
				PinyinWithTone 
					*pPinyin;
				HanziContext 
					*pContext;
				
				/*	Re-adjust the offset (2500 was added to the original offset as a signal). */
				offset -= 2500;

				/* Get the default pinyin from the table first */
				FNX_STRCPY(sDefaultPinyin, PinyinTableWithTones[offset]);
				
				// Find the matching Hanzi character
				for( pHanzi = pPolyPhoneTable; pHanzi; pHanzi=pHanzi->pNext)
				{
					if (*pwcHanzi != pHanzi->wcHanzi)	// Nope this one doesn't match
						continue;
					
					/* Found the hanzi character, now go through the list of possible pinyin+tone */
					for( pPinyin = pHanzi->pPinyinWithTone; pPinyin; pPinyin = pPinyin->pNext )
					{	
						// Now go through the Hanzi-in-context list to see if there's a match
						// Keep track of the longest match
						for( pContext = pPinyin->pHanziContext; pContext; pContext = pContext->pNext )
						{
							// Find the Hanzi character in the context string
							if( (pwcHanziMatch = FNX_STRCHR(pContext->wsHanziContext, *pwcHanzi)) == NULL )
							{
								//FNX_PRINTF("Found a word that doesn't contain the character.\n");
								continue;
							}
					
							// Get length of Hanzi in context
							iContextLen = FNXW_STRLEN(pContext->wsHanziContext);

							iHanziOffset = pwcHanziMatch - pContext->wsHanziContext;

							// Look for this Hanzi context in the input string
							// If it matches and it's the longest one seen so far then save the pinyin+tone
							if( (pwsContextMatch = FNX_STRSTR(pwcHanzi-iHanziOffset, pContext->wsHanziContext)) != NULL &&
								pwcHanzi-pwsContextMatch == iHanziOffset &&
								iContextLen > iMaxMatch )
							{
								// Found a longer match.  Store it in sDefaultPinyin
								iMaxMatch = iContextLen;
								FNX_STRCPY(sDefaultPinyin, pPinyin->sPinyinWithTone);
							}
								
						}
						
					}
					break;	// Found the Hanzi of interest so we're done now

				}	// Scan all possible Hanzi in the PolyPhoneTable

				if( sPinyin )
				{
					FNX_STRCAT(sPinyin, sDefaultPinyin);
				}
				iLen += FNX_STRLEN(sDefaultPinyin);

			}	// PolyPhone character

			// Keep track of a couple of special characters whose tone changes 
			// depending on the following tone
			if( sPinyin )
			{
				if( wcSpecial )
				{
					pcCurTone = sPinyin + FNX_STRLEN(sPinyin) -1;
					switch( wcSpecial )
					{
						case 0x4E00:
							// pronounced as a 1st tone in isolation. (default)
							// pronounced in the 1st tone when used to count numbers.
							// pronounced as a 2nd tone when it precedes a character with a 4th tone.
							if( *pcCurTone == '4' )
								*pcSpecTone = '2';
							// prononounced as a 4th tone when it precedes a character with a 1st, 2nd, or 3rd tone.
							else if( *pcCurTone == '1' ||
								*pcCurTone == '2' ||
								*pcCurTone == '3' )
								*pcSpecTone = '4';
							
							break;
							
						case 0x4E0D:
							// pronounced as a 4th tone in isolation. (default)
							// pronounced as a 4th tone when it precedes characters with a 1st, 2nd, or 3rd tone. (default)
							// pronounced as a 2nd tone when it precedes another 4th tone character.
							if( *pcSpecTone == '4' && 
								*pcCurTone == '4' )
							{
								*pcSpecTone = '2';
							}
							
							break;

						case 0x8C22:
							// If you have 2 of these characters (0x8C22, xie4) in a row, the second one should 
							// be changed to xie5.  This phrase means "Thank you"
							if( *pwcHanzi == 0x8C22 &&
								*pcCurTone == '4')
							{
								*pcCurTone = '5';
							}
							break;
					}
					wcSpecial = 0;		// Reset
				}
				else if( *pwcHanzi == 0x4E00 ||
						 *pwcHanzi == 0x4E0D ||
						 *pwcHanzi == 0x8C22 )
				{
					wcSpecial = *pwcHanzi;
					
					pcSpecTone = sPinyin + FNX_STRLEN(sPinyin) - 1;
				}
			}

			
		}	// If Unicode standard CJK range
		
		// CJK Symbols and Punctuation
		// See http://www.unicode.org/Public/UNIDATA/UnicodeData.txt for definitions
		// and http://www.unicode.org/versions/Unicode4.0.0/ch06.pdf for more information
		else if (*pwcHanzi >= 0x3000 && *pwcHanzi <= 0x303F)
		{
			sPunc[0] = 0x00;
			switch( *pwcHanzi )
			{
				case 0x3000:	FNX_STRCAT(sPunc, " ");		break;		// SPACE
				case 0x3001:	FNX_STRCAT(sPunc, ",");		break;		// COMMA
				case 0x3002:	FNX_STRCAT(sPunc, ".");		break;		// IDEOGRAPHIC PERIOD
				case 0x3003:	FNX_STRCAT(sPunc, "\"");	break;		// DITTO MARK
				case 0x3004:	FNX_STRCAT(sPunc, "");		break;		// JAPANESE INDUSTRIAL STANDARD SYMBOL
				case 0x3005:	FNX_STRCAT(sPunc, "");		break;		// IDEOGRAPHIC ITERATION MARK
				case 0x3006:	FNX_STRCAT(sPunc, "");		break;		// IDEOGRAPHIC CLOSING MARK
				case 0x3007:	FNX_STRCAT(sPunc, "0");		break;		// IDEOGRAPHIC NUMBER ZERO
				case 0x3008:	FNX_STRCAT(sPunc, "<");		break;		// LEFT ANGLE BRACKET
				case 0x3009:	FNX_STRCAT(sPunc, ">");		break;		// RIGHT ANGLE BRACKET
				case 0x300A:	FNX_STRCAT(sPunc, "<<");	break;		// LEFT DOUBLE ANGLE BRACKET
				case 0x300B:	FNX_STRCAT(sPunc, ">>");	break;		// RIGHT DOUBLE ANGLE BRACKET
				case 0x300C:	FNX_STRCAT(sPunc, "[");		break;		// LEFT CORNER BRACKET
				case 0x300D:	FNX_STRCAT(sPunc, "]");		break;		// RIGHT CORNER BRACKET
				case 0x300E:	FNX_STRCAT(sPunc, "[");		break;		// LEFT WHITE CORNER BRACKET
				case 0x300F:	FNX_STRCAT(sPunc, "]");		break;		// RIGHT WHITE CORNER BRACKET
				case 0x3010:	FNX_STRCAT(sPunc, "(");		break;		// LEFT BLACK LENTICULAR BRACKET
				case 0x3011:	FNX_STRCAT(sPunc, ")");		break;		// RIGHT BLACK LENTICULAR BRACKET
				case 0x3012:	FNX_STRCAT(sPunc, "");		break;		// POSTAL MARK
				case 0x3013:	FNX_STRCAT(sPunc, "");		break;		// GETA MARK
				case 0x3014:	FNX_STRCAT(sPunc, "{");		break;		// LEFT TORTOISE SHELL BRACKET
				case 0x3015:	FNX_STRCAT(sPunc, "}");		break;		// RIGHT TORTOISE SHELL BRACKET
				case 0x3016:	FNX_STRCAT(sPunc, "(");		break;		// LEFT WHITE LENTICULAR BRACKET
				case 0x3017:	FNX_STRCAT(sPunc, ")");		break;		// RIGHT WHITE LENTICULAR BRACKET
				case 0x3018:	FNX_STRCAT(sPunc, "{");		break;		// LEFT WHITE TORTOISE SHELL BRACKET
				case 0x3019:	FNX_STRCAT(sPunc, "}");		break;		// RIGHT WHITE TORTOISE SHELL BRACKET
				case 0x301A:	FNX_STRCAT(sPunc, "[");		break;		// LEFT WHITE SQUARE BRACKET
				case 0x301B:	FNX_STRCAT(sPunc, "]");		break;		// RIGHT WHITE SQUARE BRACKET
				case 0x301C:	FNX_STRCAT(sPunc, "~");		break;		// WAVE DASH
				case 0x301D:	FNX_STRCAT(sPunc, "\"");	break;		// REVERSED DOUBLE PRIME QUOTATION MARK
				case 0x301E:	FNX_STRCAT(sPunc, "\"");	break;		// DOUBLE PRIME QUOTATION MARK
				case 0x301F:	FNX_STRCAT(sPunc, "\"");	break;		// LOW DOUBLE PRIME QUOTATION MARK
				case 0x3020:	FNX_STRCAT(sPunc, "");		break;		// POSTAL MARK FACE
				case 0x3021:	FNX_STRCAT(sPunc, "1");		break;		// HANGZHOU NUMERAL ONE
				case 0x3022:	FNX_STRCAT(sPunc, "2");		break;		// HANGZHOU NUMERAL TWO
				case 0x3023:	FNX_STRCAT(sPunc, "3");		break;		// HANGZHOU NUMERAL THREE
				case 0x3024:	FNX_STRCAT(sPunc, "4");		break;		// HANGZHOU NUMERAL FOUR
				case 0x3025:	FNX_STRCAT(sPunc, "5");		break;		// HANGZHOU NUMERAL FIVE
				case 0x3026:	FNX_STRCAT(sPunc, "6");		break;		// HANGZHOU NUMERAL SIX
				case 0x3027:	FNX_STRCAT(sPunc, "7");		break;		// HANGZHOU NUMERAL SEVEN
				case 0x3028:	FNX_STRCAT(sPunc, "8");		break;		// HANGZHOU NUMERAL EIGHT
				case 0x3029:	FNX_STRCAT(sPunc, "9");		break;		// HANGZHOU NUMERAL NINE
				case 0x302A:	FNX_STRCAT(sPunc, "-");		break;		// IDEOGRAPHIC LEVEL TONE MARK
				case 0x302B:	FNX_STRCAT(sPunc, "/");		break;		// IDEOGRAPHIC RISING TONE MARK
				case 0x302C:	FNX_STRCAT(sPunc, "\\");	break;		// IDEOGRAPHIC DEPARTING TONE MARK
				case 0x302D:	FNX_STRCAT(sPunc, "/");		break;		// IDEOGRAPHIC ENTERING TONE MARK
				case 0x302E:	FNX_STRCAT(sPunc, "");		break;		// HANGUL SINGLE DOT TONE MARK
				case 0x302F:	FNX_STRCAT(sPunc, "");		break;		// HANGUL DOUBLE DOT TONE MARK
				case 0x3030:	FNX_STRCAT(sPunc, "~");		break;		// WAVY DASH
				case 0x3031:	FNX_STRCAT(sPunc, "");		break;		// VERTICAL KANA REPEAT MARK
				case 0x3032:	FNX_STRCAT(sPunc, "");		break;		// VERTICAL KANA REPEAT WITH VOICED SOUND MARK
				case 0x3033:	FNX_STRCAT(sPunc, "");		break;		// VERTICAL KANA REPEAT MARK UPPER HALF
				case 0x3034:	FNX_STRCAT(sPunc, "");		break;		// VERTICAL KANA REPEAT WITH VOICED SOUND MARK UPPER HALF
				case 0x3035:	FNX_STRCAT(sPunc, "");		break;		// VERTICAL KANA REPEAT MARK LOWER HALF
				case 0x3036:	FNX_STRCAT(sPunc, "");		break;		// CIRCLED POSTAL MARK
				case 0x3037:	FNX_STRCAT(sPunc, "");		break;		// IDEOGRAPHIC TELEGRAPH LINE FEED SEPARATOR SYMBOL
				case 0x3038:	FNX_STRCAT(sPunc, "10");	break;		// HANGZHOU NUMERAL TEN
				case 0x3039:	FNX_STRCAT(sPunc, "20");	break;		// HANGZHOU NUMERAL TWENTY
				case 0x303A:	FNX_STRCAT(sPunc, "30");	break;		// HANGZHOU NUMERAL THIRTY
				case 0x303B:	FNX_STRCAT(sPunc, "");		break;		// VERTICAL IDEOGRAPHIC ITERATION MARK
				case 0x303C:	FNX_STRCAT(sPunc, "");		break;		// MASU MARK
				case 0x303D:	FNX_STRCAT(sPunc, "");		break;		// PART ALTERNATION MARK
				case 0x303E:	FNX_STRCAT(sPunc, "");		break;		// IDEOGRAPHIC VARIATION INDICATOR
				case 0x303F:	FNX_STRCAT(sPunc, " ");		break;		// IDEOGRAPHIC HALF FILL SPACE
			}

			if( sPinyin )
				FNX_STRCAT(sPinyin, sPunc);

			if( wcSpecial )
				wcSpecial = 0x0000;

			iLen += FNX_STRLEN(sPunc);
		}

		else if( 0xFF01 <= *pwcHanzi && *pwcHanzi <= 0xFF60 )
		{
			// Fullwidth & Halfwidth characters
			// See http://www.unicode.org/charts/PDF/UFF00.pdf for more information
			sPunc[0] = 0x00;
			sChar[0] = 0x00;
			sChar[1] = 0x00;
			switch( *pwcHanzi )
			{
				case 0xFF01:	FNX_STRCAT(sPunc, "!");		break;
				case 0xFF02:	FNX_STRCAT(sPunc, "\"");	break;
				case 0xFF04:	FNX_STRCAT(sPunc, "$");		break;
				case 0xFF07:	FNX_STRCAT(sPunc, "'");		break;
				case 0xFF08:	FNX_STRCAT(sPunc, "(");		break;
				case 0xFF09:	FNX_STRCAT(sPunc, ")");		break;
				case 0xFF0C:	FNX_STRCAT(sPunc, ",");		break;
				case 0xFF0D:	FNX_STRCAT(sPunc, "-");		break;
				case 0xFF0E:	FNX_STRCAT(sPunc, ".");		break;
				case 0xFF0F:	FNX_STRCAT(sPunc, "/");		break;
				case 0xFF10:	FNX_STRCAT(sPunc, "0");		break;
				case 0xFF11:	FNX_STRCAT(sPunc, "1");		break;
				case 0xFF12:	FNX_STRCAT(sPunc, "2");		break;
				case 0xFF13:	FNX_STRCAT(sPunc, "3");		break;
				case 0xFF14:	FNX_STRCAT(sPunc, "4");		break;
				case 0xFF15:	FNX_STRCAT(sPunc, "5");		break;
				case 0xFF16:	FNX_STRCAT(sPunc, "6");		break;
				case 0xFF17:	FNX_STRCAT(sPunc, "7");		break;
				case 0xFF18:	FNX_STRCAT(sPunc, "8");		break;
				case 0xFF19:	FNX_STRCAT(sPunc, "9");		break;
				case 0xFF1A:	FNX_STRCAT(sPunc, ":");		break;
				case 0xFF1B:	FNX_STRCAT(sPunc, ";");		break;
				case 0xFF1F:	FNX_STRCAT(sPunc, "?");		break;
				case 0xFF3C:	FNX_STRCAT(sPunc, "\\");	break;
				case 0xFF3B:	FNX_STRCAT(sPunc, "[");		break;
				case 0xFF3D:	FNX_STRCAT(sPunc, "]");		break;
				case 0xFF3E:	FNX_STRCAT(sPunc, "^");		break;
				case 0xFF40:	FNX_STRCAT(sPunc, "`");		break;		// FULL WIDTH GRAVE ACCENT
				case 0xFF61:	FNX_STRCAT(sPunc, ".");		break;		// HALF WIDTH IDEOGRAPHIC FULL STOP
				case 0xFF64:	FNX_STRCAT(sPunc, ",");		break;		// HALF WIDTH IDEOGRAPHIC COMMA
				case 0xFFE0:	sChar[0] = (char)0x00A2;	FNX_STRCAT(sPunc, sChar);		break;		// FULL WIDTH CENT SIGN
				case 0xFFE1:	sChar[0] = (char)0x00A3;	FNX_STRCAT(sPunc, sChar);		break;		// FULL WIDTH POUND SIGN
				case 0xFFE5:	sChar[0] = (char)0x00A5;	FNX_STRCAT(sPunc, sChar);		break;		// FULL WIDTH YEN SIGN
				default:	FNX_STRCAT(sPunc, "");		break;

			}
			if( sPinyin )
				FNX_STRCAT(sPinyin, sPunc);

			if( wcSpecial )
				wcSpecial = 0x0000;

			iLen += FNX_STRLEN(sPunc);
		}
#ifdef TEXT_NORM	// Text normalization
		else if((iTextNormType = GetTextNormType(pwcHanzi, iNumCJKChars, iNumPinyinChars)) > 0)
		{
			int iTextNormLen;
			// Return lenth of combined pinyin for normalized text.
			// pwcHanzi was moved to the point right after the input which has been normalized.
			iTextNormLen = TextNorm(&pwcHanzi, sPinyin, iTextNormType);
			iLen += iTextNormLen;
			// Need to move back one char because of pwcHanzi++ in the for loop
			if(iTextNormLen > 0)
				pwcHanzi--;
		}
#endif
		// if Wide Ascii
		else if( FNXW_ISASCII(*pwcHanzi) || 
				 *pwcHanzi == 0x00fc )		// umlaut character
		{
#ifdef TEXT_NORM
			wchar_t c = *pwcHanzi;
			// pinyin has the format such as "ni3hao3"
			if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
				iNumPinyinChars++;
#endif
			if( sPinyin )
			{
				char	cMb, sMb[2];
				wctomb(&cMb, *pwcHanzi);
				if (cMb == 0x09)
					FNX_STRCAT(sPinyin, " ");
				else
				{
					sMb[0] = cMb;
					sMb[1] = 0x00;
					FNX_STRCAT(sPinyin, sMb);
				}
			}
			iLen++;

			if( wcSpecial )
				wcSpecial = 0x0000;

		}
		
   	}

	return iLen;
}


/*FUNCTION_HEADER**********************
 * NAME:	;FreePolyPhoneTable
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void FreePolyPhoneTable(Hanzi *pHeadHanzi)
{
	Hanzi 
		*pHanzi,
		*pTmpHanzi;
	PinyinWithTone
		*pPinyin,
		*pTmpPinyin;
	HanziContext
		*pContext,
		*pTmpContext;
	
	for(pHanzi=pHeadHanzi; pHanzi; )
	{
		pTmpHanzi = pHanzi;
		pHanzi = pHanzi->pNext;

		for( pPinyin=pTmpHanzi->pPinyinWithTone; pPinyin; )
		{
			pTmpPinyin = pPinyin;
			pPinyin = pPinyin->pNext;

			for( pContext = pTmpPinyin->pHanziContext; pContext; )
			{
				pTmpContext = pContext;
				pContext = pContext->pNext;

				FNX_FREE(pTmpContext);
			}

			FNX_FREE(pTmpPinyin);
		}
		FNX_FREE(pTmpHanzi);
	}
}


#ifdef DTALK_CH_EXPORTS
/*FUNCTION_HEADER**********************
 * NAME:	;Initialize
 * DESC: 	Load the poly phone table needed for converting
			Hanzi characters with multiple possible pinyin+tone
 * IN:		phTTS
 * OUT:		none
 * RETURN:	0 on success, nonzero on failure
 * NOTES:	
 *END_HEADER***************************/
int Initialize(LPVOID pVoid)
{
#ifdef ARM7
	LPTTS_HANDLE_T phTTS = (LPTTS_HANDLE_T)pVoid;
	PLTS_T pLts = phTTS->pLTSThreadData;
	return !((pLts->pPolyPhoneTable = ReadPolyPhoneTable(phTTS->dict_path)) != NULL);
#else
	PLTS_T pLts=(PLTS_T)pVoid;
	return !((pLts->pPolyPhoneTable = ReadPolyPhoneTable("dtalk_ch.cjk")) != NULL);
#endif //ARM7

}


/*FUNCTION_HEADER**********************
 * NAME:	;Terminate
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int Terminate(LPVOID pVoid)
{
	PLTS_T pLts=(PLTS_T)pVoid;

	if( pLts->pPolyPhoneTable )
	{
		FreePolyPhoneTable(pLts->pPolyPhoneTable);
		pLts->pPolyPhoneTable = NULL;
	}

	return 0;

}
#endif

/*FUNCTION_HEADER**********************
 * NAME:	;ReadPolyPhoneTable
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
Hanzi *ReadPolyPhoneTable(char *sPolyPhoneFile)
{
	BOOL
		bBigEndian=-1;
	wchar_t
		*wsTok,
		wsBuf[MAX_PHRASE_LENGTH];
	Hanzi 
		*pHeadHanzi=NULL,
		*pHanzi=NULL;
	PinyinWithTone
		*pPinyin;
	HanziContext
		*pContext;
	FILE* fIn;
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199409L) || defined(OS_SYMBIAN)
    wchar_t
		*state = NULL;
#endif
		
	/* Read in the poly phone table file and build the necessary structures for later scanning */
	if( (fIn = FNX_FOPEN(sPolyPhoneFile, "rb")) == NULL )
	{
		//FNX_PRINTF("Poly sound file \"%s\" cannot be found.\n", sPolyPhoneFile);
		return NULL;
	}
	
	while( FNXW_FGETS(wsBuf, MAX_PHRASE_LENGTH, fIn) )
	{

		if( wsBuf[0] == 0xFFFE &&
			bBigEndian == -1 )
		{
			bBigEndian = FALSE;
			memmove(wsBuf, &wsBuf[1], FNXW_STRLEN(&wsBuf[1]));
		}
		else if( wsBuf[0] == 0xFEFF &&
				 bBigEndian == -1 )
		{
			bBigEndian = TRUE;
			memmove(wsBuf, &wsBuf[1], FNXW_STRLEN(&wsBuf[1]));
		}
		if( wsBuf[0] == WCHAR_LSQBR)
		{
			// Found a CHARARACTER definition line - 
			// Format: [N]. <hanzi> <nPinyin> <sPinyin1> <sPinyin2> ... <sPinyinN> <total hanzi contexts>

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199409L) || defined(OS_SYMBIAN)
			wsTok = FNXW_STRTOK(wsBuf, delims, &state); 
#else
			wsTok = FNXW_STRTOK(wsBuf, delims);	// Get hanzi number
#endif

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199409L) || defined(OS_SYMBIAN)
			if( (wsTok = FNXW_STRTOK(NULL, delims, &state)) == NULL)// Get hanzi
#else
			if( (wsTok = FNXW_STRTOK(NULL, delims)) == NULL)		// Get hanzi
#endif
				continue;

			if( pHeadHanzi == NULL )
			{
				pHeadHanzi = pHanzi = (Hanzi *)FNX_CALLOC(1, sizeof(Hanzi));
			}
			else
			{
				pHanzi->pNext = (Hanzi *)FNX_CALLOC(1, sizeof(Hanzi));
				pHanzi = pHanzi->pNext;
			}

			pHanzi->wcHanzi = *wsTok;
			pPinyin = NULL;
		}
		
		else if( wsBuf[0] == WCHAR_TAB &&
				 wsBuf[1] != WCHAR_TAB &&
				 pHanzi )
		{
			// Found a Pinyin+Tone definition line
			// Format: \t<Pinyin+Tone> <nHanziContexts>
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199409L) || defined(OS_SYMBIAN)
			if( (wsTok = FNXW_STRTOK(wsBuf, delims, &state)) == NULL )
#else
			if( (wsTok = FNXW_STRTOK(wsBuf, delims)) == NULL )
#endif
				continue;

			if( pHanzi->pPinyinWithTone == NULL )
			{
				pHanzi->pPinyinWithTone = pPinyin = (PinyinWithTone *)FNX_CALLOC(1, sizeof(PinyinWithTone));
			}
			else
			{
				pPinyin->pNext = (PinyinWithTone *)FNX_CALLOC(1, sizeof(PinyinWithTone));
				pPinyin = pPinyin->pNext;
			}

			wcstombs(pPinyin->sPinyinWithTone, wsTok, MAX_PINYIN);
		}
		else if( wsBuf[0] == WCHAR_TAB && 
				 wsBuf[1] == WCHAR_TAB && 
				 pHanzi &&
				 pPinyin )
		{
			// Found a WORD definition line
			// Format: \t\t<Hanzi context>
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199409L) || defined(OS_SYMBIAN)
			if( (wsTok = FNXW_STRTOK(wsBuf, delims, &state)) == NULL )
#else
			if( (wsTok = FNXW_STRTOK(wsBuf, delims)) == NULL )
#endif
				continue;

			if( pPinyin->pHanziContext == NULL )
			{
				pPinyin->pHanziContext = pContext = (HanziContext *)FNX_CALLOC(1, sizeof(HanziContext));
			}
			else
			{
				pContext->pNext = (HanziContext *)FNX_CALLOC(1, sizeof(HanziContext));
				pContext = pContext->pNext;
			}

			FNXW_STRCPY(pContext->wsHanziContext, wsTok);
		}
		
	}
	
	/* Close the poly phone file */
	FNX_FCLOSE(fIn);

	return pHeadHanzi;
}


#ifdef BUILD_CJK2PINYIN_TABLE
typedef struct _tagHanziPinyin
{
	wchar_t	wHanzi;
	char	sPinyin[8];
} HANZI2PINYIN;


/*FUNCTION_HEADER**********************
 * NAME:	;SortPinyinCmp
 * DESC: 	Compare function for sorting pinyin+tone
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int SortPinyinCmp(const void *arg1, const void *arg2)
{
	char  
		*p1 = *(char **)arg1, 
		*p2 = *(char **)arg2;

	return FNX_STRCMP(p1, p2);

}

/*FUNCTION_HEADER**********************
 * NAME:	;FindPinyinCmp
 * DESC: 	Compare function for finding Pinyin+tone
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int FindPinyinCmp(const void *arg1, const void *arg2)
{
	char
		*p1 = (char *)arg1, 
		*p2 = *(char **)arg2;

	return FNX_STRCMP(p1, p2);

}

/*FUNCTION_HEADER**********************
 * NAME:	;SortPinyin
 * DESC: 	Function to sort Pinyin table
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static void SortPinyin(char **psPinyin, int nPinyin)
{
	qsort((void *)psPinyin, nPinyin, sizeof(char **), SortPinyinCmp);
}


/*FUNCTION_HEADER**********************
 * NAME:	;ReadHanzi2PinyinData
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
HANZI2PINYIN *ReadHanzi2PinyinData(char *sFile, int *pnCount)
{
	wchar_t wc, wsBuf[128], wsPinyin[32];
	int	i, ret, nCount=0, nBad=0;
	HANZI2PINYIN *pH2PTable;
	FILE *fp;

	if( (fp = FNX_FOPEN(sFile, "rb")) == NULL )
	{
		FNX_PRINTF("Source Text File %s not found.\n", sFile);
		exit(-1);
	}
	else
		FNX_PRINTF("Reading from file %s\n", sFile);

	FNX_FREAD(&wc, sizeof(wchar_t), 1, fp);
	if( wc != 0xfeff )
	{
		FNX_PRINTF("ReadHanzi2PinyinData: Bad input file %s\n", sFile);
		return NULL;
	}

	nCount = 0x9FA5 - 0x4E00;

	pH2PTable = (HANZI2PINYIN *)FNX_CALLOC(nCount, sizeof(HANZI2PINYIN));

	// Go back to the beginning of the file
	FNX_FSEEK(fp, 0, SEEK_SET);
	FNX_FREAD(&wc, sizeof(wchar_t), 1, fp);

	// Now read the data into memory
	while( FNXW_FGETS(wsBuf, 128, fp) )
	{
		if( (ret = FNXW_SSCANF(wsBuf, L"%c\t%s", &wc, wsPinyin)) == 2 && 
			0x4E00 <= wc && wc <= 0x9FA5 )
		{
			i = wc - 0x4E00;
			pH2PTable[i].wHanzi = wc;
			wcstombs(pH2PTable[i].sPinyin, wsPinyin, 8);
		}
		else
		{
			nBad++;
		}
	}

	if( pnCount )
		*pnCount = nCount;

	return pH2PTable;
}

/*FUNCTION_HEADER**********************
 * NAME:	;main
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void main(int argc, char **argv)
{
	char	sInFile[_MAX_PATH],
			sOutFile[_MAX_PATH],
			sPolyFile[_MAX_PATH],
			**psPinyin;
	int		i, 
			nHanzi, 
			nPinyin = gnPinyinPlusTones;
	short	index;
	FILE	*fpOut;
	Hanzi	*pPolyPhoneTable,
			*pPolyPhone;
	HANZI2PINYIN *pH2P;
	void	*pVoid;

	// initialize file names
	sInFile[0] = sOutFile[0] = sPolyFile[0] = 0x00;

	for( i=1; i<argc; i++ )
	{
		if( argv[i][0] == '-' )
		{
			switch( argv[i][1] )
			{
				case 'i':
					FNX_STRCPY(sInFile, argv[++i]);
					break;

				case 'o':
					FNX_STRCPY(sOutFile, argv[++i]);
					break;

				case 'p':
					FNX_STRCPY(sPolyFile, argv[++i]);
					break;

				case 'h':
					exit(-1);

			}
		}
	}

	// Get and load the polyphone table
	if( sPolyFile[0] == 0x00)
		FNX_STRCPY(sPolyFile, "..\\dtalk_ch.cjk");

	pPolyPhoneTable = ReadPolyPhoneTable(sPolyFile);


	/* Get filename for CJK - Pinyin+tone data file */
	if( sInFile[0] == 0x00 )
		FNX_STRCPY(sInFile, "..\\CJK.txt");
	
	if( (pH2P = ReadHanzi2PinyinData(sInFile, &nHanzi)) == NULL )
		exit(-1);

	SortPinyin(PinyinTableWithTones, nPinyin);


	/* Get filename for output data */
	if( sOutFile[0] == 0x00 )
		FNX_STRCPY(sOutFile, "..\\CJK2PinyinTables.c");

 	if( (fOut = FNX_FOPEN(sOutFile, "wt")) == NULL)
	{
		FNX_PRINTF("File %s cannot be created.\n", sOutFile);
		exit(-1);
	}
	else
		FNX_PRINTF("File %s has been opened for creation.\n", sOutFile);

	// *******************************************
	// Write out a file header
	// *******************************************
	FNX_FPRINTF(fpOut, "/*C_HEADER_FILE****************************************************************\n");
	FNX_FPRINTF(fpOut, "FILE			:	CJK2PinyinTable.c\n");
	FNX_FPRINTF(fpOut, "DESC			:	This file contains the tables used to convert Chinese Hanzi\n");
	FNX_FPRINTF(fpOut, "					characters to pinyin+tone\n");
	FNX_FPRINTF(fpOut, "TABS			:	4\n");
	FNX_FPRINTF(fpOut, "OWNER			:	Fonix\n");
	FNX_FPRINTF(fpOut, "DATE CREATED	:	%s\n", __DATE__);
	FNX_FPRINTF(fpOut, "(C) Copyright 2005 All rights reserved.\n");
	FNX_FPRINTF(fpOut, "This is an unpublished work, and is confidential and proprietary: \n");
	FNX_FPRINTF(fpOut, "technology and information of fonix corporation.  No part of this\n");
	FNX_FPRINTF(fpOut, "code may be reproduced, used or disclosed without written consent of \n");
	FNX_FPRINTF(fpOut, "fonix corporation in each and every instance.\n");
	FNX_FPRINTF(fpOut, "*END_HEADER*******************************************************************/\n");

	// *******************************************
	// Write out the sorted Pinyin+tone table
	// *******************************************
	FNX_FPRINTF(fpOut, "\n\n/****************************************************************************\n");
	FNX_FPRINTF(fpOut, "** All possible pinyins with tones\n");
	FNX_FPRINTF(fpOut, "** %d pronunciations x 5 tones  + 1? = %d\n", (nPinyin-1)/5, nPinyin);
	FNX_FPRINTF(fpOut, "** If this table is modified you must recompile the project BuildCJK2PinyinTables\n");
	FNX_FPRINTF(fpOut, "** and run it to re-create this file with the correct offsets in \n");
	FNX_FPRINTF(fpOut, "** CJKUnicodeOffsetToPinyinTable\n");
	FNX_FPRINTF(fpOut, "*****************************************************************************/\n");

	FNX_FPRINTF(fpOut, "char *PinyinTableWithTones[] =\n");
	FNX_FPRINTF(fpOut, "{\n");
	FNX_FPRINTF(fpOut, "\t\"?\",\n\t");
	for( i=1; i<nPinyin; i++ )
	{
		FNX_FPRINTF(fpOut, "\"%s\"", PinyinTableWithTones[i]);

		if( i < nPinyin-1 )
			FNX_FPRINTF(fpOut, ",");
		
		if( (i % 5) == 0 )
			FNX_FPRINTF(fpOut, "\n\t");
		else
			FNX_FPRINTF(fpOut, " ");
	}
	FNX_FPRINTF(fpOut, "};\n\n\n");

	FNX_FPRINTF(fpOut, "/* -----------------------------------------------------------------\n");
	FNX_FPRINTF(fpOut, "CJKUnicodeOffsetToPinyinTable contains a value for all ideographs in the\n");
	FNX_FPRINTF(fpOut, "Unicode set from 0x4E00 to 0x9FA5.  The value is an index into the above\n");
	FNX_FPRINTF(fpOut, "table PinyinTableWithTones.  Some ideographs may have more than one possible \n");
	FNX_FPRINTF(fpOut, "pronunciation depending on context.  When this happens 2500 will be added\n");
	FNX_FPRINTF(fpOut, "to the value in CJKUnicodeOffsetToPinyinTable to flag that additional \n");
	FNX_FPRINTF(fpOut, "context checking needs to happen.\n\n");
	FNX_FPRINTF(fpOut, "Warning: Do not modify this table by hand.  It must be built using the\n");
	FNX_FPRINTF(fpOut, "project BuildCJK2PinyinTables.\n");
	FNX_FPRINTF(fpOut, "------------------------------------------------------------------ */\n");
	FNX_FPRINTF(fpOut, "const unsigned short CJKUnicodeOffsetToPinyinTable[]= {\n\t");
	for( i=0; i<nHanzi; i++ )
	{
		// Find pinyin for pH2P[i].sPinyin in PinyinTableWithTones.
		// Get index into PinyinTableWithTones.
		pVoid = FNX_BSEARCH(pH2P[i].sPinyin, (void *)PinyinTableWithTones, nPinyin, sizeof(char **), FindPinyinCmp);
		if( pVoid != NULL )
		{
			psPinyin = (char **)pVoid;
			index = (psPinyin - PinyinTableWithTones);

			// Look for pH2P[i].wHanzi in pPolyPhoneTable.  If it is there then add 2500 to index
			for( pPolyPhone = pPolyPhoneTable; pPolyPhone; pPolyPhone=pPolyPhone->pNext)
			{
				if( pPolyPhone->wcHanzi == (i+0x4E00) )	// Nope this one doesn't match
				{
					index += 2500;
					break;
				}
			}
		}
		else
		{
			index = 0;
		}


		FNX_FPRINTF(fpOut, "%d", index);

		if( i < nHanzi-1 )
			FNX_FPRINTF(fpOut, ",");
		
		if( ((i+1) % 16) == 0 )
			FNX_FPRINTF(fpOut, "\n\t");
		else
			FNX_FPRINTF(fpOut, " ");

	}
	FNX_FPRINTF(fpOut, "\n};\n\n");

	FNX_FPRINTF(fpOut, "int gnPinyinPlusTones = sizeof(PinyinTableWithTones) / sizeof(char *);\n");
	FNX_FPRINTF(fpOut, "int gnMaxCJK = sizeof(CJKUnicodeOffsetToPinyinTable)/sizeof(short);\n");

	/* Close the files */
	FNX_FCLOSE(fpOut);

	FreePolyPhoneTable(pPolyPhoneTable);
}
#endif

