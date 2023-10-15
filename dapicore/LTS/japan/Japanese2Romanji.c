/*C_HEADER_FILE****************************************************************
FILE        :  Japanese.c
DESC        :  Functions needed to translate Japanese Katakana and Hiragana to Romanji
TABS        :  3
OWNER       :  Fonix
DATE CREATED:  16 July 2002

(C) Copyright 2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/06/03 4:27p $
  $Revision: 2 $

*END_HEADER*******************************************************************/

//#include <stdio.h> //moved to port.h for each platform MLT 01/26/06
#include "port.h"
//#include "FnxPlatform.h"

#define HIRAGANA_BOTTOM 0x3041
#define HIRAGANA_TOP	0x3093

#define KATAKANA_BOTTOM 0x30A1
#define KATAKANA_TOP	0x30F6

#define convertToOffset(a) (a < 0xFF00) ? ((0x309F > a) ? a - 0x3041 : a - 0x30a1) : a - 0xff66

typedef struct 
{
    wchar_t wszUCS;
    char    szRomanji[5];
} language;

typedef struct 
{
    wchar_t wszUCSHalfWidthKat;
    wchar_t wszFullKat;
} conversion;

conversion HalfwidthKatToFullKat[] =
{
   {0xFF66, 0x30F2}, //HALFWIDTH KATAKANA LETTER WO 
   {0xFF67, 0x30A1}, //HALFWIDTH KATAKANA LETTER SMALL A 
   {0xFF68, 0x30A3}, //HALFWIDTH KATAKANA LETTER SMALL I 
   {0xFF69, 0x30A5}, //HALFWIDTH KATAKANA LETTER SMALL U 
   {0xFF6A, 0x30A7}, //HALFWIDTH KATAKANA LETTER SMALL E 
   {0xFF6B, 0x30A9}, //HALFWIDTH KATAKANA LETTER SMALL O 
   {0xFF6C, 0x30E3}, //HALFWIDTH KATAKANA LETTER SMALL YA 
   {0xFF6D, 0x30E5}, //HALFWIDTH KATAKANA LETTER SMALL YU 
   {0xFF6E, 0x30E7}, //HALFWIDTH KATAKANA LETTER SMALL YO 
   {0xFF6F, 0x30C3}, //HALFWIDTH KATAKANA LETTER SMALL TU 
   {0xFF70, 0x30FC}, //HALFWIDTH KATAKANA-HIRAGANA PROLONGED SOUND MARK 
   {0xFF71, 0x30A2}, //HALFWIDTH KATAKANA LETTER A 
   {0xFF72, 0x30A4}, //HALFWIDTH KATAKANA LETTER I 
   {0xFF73, 0x30A6}, //HALFWIDTH KATAKANA LETTER U 
   {0xFF74, 0x30A8}, //HALFWIDTH KATAKANA LETTER E 
   {0xFF75, 0x30AA}, //HALFWIDTH KATAKANA LETTER O 
   {0xFF76, 0x30AB}, //HALFWIDTH KATAKANA LETTER KA 
   {0xFF77, 0x30AD}, //HALFWIDTH KATAKANA LETTER KI 
   {0xFF78, 0x30AF}, //HALFWIDTH KATAKANA LETTER KU 
   {0xFF79, 0x30B1}, //HALFWIDTH KATAKANA LETTER KE 
   {0xFF7A, 0x30B3}, //HALFWIDTH KATAKANA LETTER KO 
   {0xFF7B, 0x30B5}, //HALFWIDTH KATAKANA LETTER SA 
   {0xFF7C, 0x30B7}, //HALFWIDTH KATAKANA LETTER SI 
   {0xFF7D, 0x30B9}, //HALFWIDTH KATAKANA LETTER SU 
   {0xFF7E, 0x30BB}, //HALFWIDTH KATAKANA LETTER SE 
   {0xFF7F, 0x30BD}, //HALFWIDTH KATAKANA LETTER SO 
   {0xFF80, 0x30BF}, //HALFWIDTH KATAKANA LETTER TA 
   {0xFF81, 0x30C1}, //HALFWIDTH KATAKANA LETTER TI CHI
   {0xFF82, 0x30C2}, //HALFWIDTH KATAKANA LETTER TU 
   {0xFF83, 0x30C6}, //HALFWIDTH KATAKANA LETTER TE 
   {0xFF84, 0x30C8}, //HALFWIDTH KATAKANA LETTER TO 
   {0xFF85, 0x30CA}, //HALFWIDTH KATAKANA LETTER NA 
   {0xFF86, 0x30CB}, //HALFWIDTH KATAKANA LETTER NI 
   {0xFF87, 0x30CC}, //HALFWIDTH KATAKANA LETTER NU 
   {0xFF88, 0x30CD}, //HALFWIDTH KATAKANA LETTER NE 
   {0xFF89, 0x30CE}, //HALFWIDTH KATAKANA LETTER NO 
   {0xFF8A, 0x30CF}, //HALFWIDTH KATAKANA LETTER HA 
   {0xFF8B, 0x30D2}, //HALFWIDTH KATAKANA LETTER HI 
   {0xFF8C, 0x30D5}, //HALFWIDTH KATAKANA LETTER HU 
   {0xFF8D, 0x30D8}, //HALFWIDTH KATAKANA LETTER HE 
   {0xFF8E, 0x30DB}, //HALFWIDTH KATAKANA LETTER HO 
   {0xFF8F, 0x30DE}, //HALFWIDTH KATAKANA LETTER MA 
   {0xFF90, 0x30DF}, //HALFWIDTH KATAKANA LETTER MI 
   {0xFF91, 0x30DF}, //HALFWIDTH KATAKANA LETTER MU 
   {0xFF92, 0x30E1}, //HALFWIDTH KATAKANA LETTER ME 
   {0xFF93, 0x30E2}, //HALFWIDTH KATAKANA LETTER MO 
   {0xFF94, 0x30E4}, //HALFWIDTH KATAKANA LETTER YA 
   {0xFF95, 0x30E6}, //HALFWIDTH KATAKANA LETTER YU 
   {0xFF96, 0x30E8}, //HALFWIDTH KATAKANA LETTER YO 
   {0xFF97, 0x30E9}, //HALFWIDTH KATAKANA LETTER RA 
   {0xFF98, 0x30EA}, //HALFWIDTH KATAKANA LETTER RI 
   {0xFF99, 0x30EB}, //HALFWIDTH KATAKANA LETTER RU 
   {0xFF9A, 0x30EC}, //HALFWIDTH KATAKANA LETTER RE 
   {0xFF9B, 0x30ED}, //HALFWIDTH KATAKANA LETTER RO 
   {0xFF9C, 0x30EF}, //HALFWIDTH KATAKANA LETTER WA 
   {0xFF9D, 0x30F3}, //HALFWIDTH KATAKANA LETTER N 
   {0xFF9E, 0x30FD}, //HALFWIDTH KATAKANA VOICED SOUND MARK 
   {0xFF9F, 0x30FE}, //HALFWIDTH KATAKANA SEMI-VOICED SOUND MARK 
};



language KatHir[] =
{
   {0x3041, "A\0\0\0"}, // small A
   {0x3042, "A\0\0\0"},
   {0x3043, "I\0\0\0"}, // small I
   {0x3044, "I\0\0\0"},
   {0x3045, "U\0\0\0"}, // small U
   {0x3046, "U\0\0\0"},
   {0x3047, "E\0\0\0"}, // small E
   {0x3048, "E\0\0\0"},
   {0x3049, "O\0\0\0"}, // small O
   {0x304A, "O\0\0\0"},
   {0x304B, "KA\0\0"},
   {0x304C, "GA\0\0"},
   {0x304D, "KI\0\0"},
   {0x304E, "GI\0\0"},
   {0x304F, "KU\0\0"},
   {0x3050, "GU\0\0"},
   {0x3051, "KE\0\0"},
   {0x3052, "GE\0\0"},
   {0x3053, "KO\0\0"},
   {0x3054, "GO\0\0"},
   {0x3055, "SA\0\0"},
   {0x3056, "ZA\0\0"},
   {0x3057, "SHI\0\0"},  // SI
   {0x3058, "JI\0\0"}, // JI
   {0x3059, "SU\0\0"},
   {0x305A, "ZU\0\0"},
   {0x305B, "SE\0\0"},
   {0x305C, "ZE\0\0"},
   {0x305D, "SO\0\0"},
   {0x305E, "ZO\0\0"},
   {0x305F, "TA\0\0"},
   {0x3060, "DA\0\0"},
   {0x3061, "CHI\0"},
   {0x3062, "JI\0\0"},
   {0x3063, "TSU\0"}, // TODO: small TU
   {0x3064, "TSU\0\0"}, // TODO: Based on JIS X 0208 changed form ZU
   {0x3065, "DU\0\0"},
   {0x3066, "TE\0\0"},
   {0x3067, "DE\0\0"},
   {0x3068, "TO\0\0"},
   {0x3069, "DO\0\0"},
   {0x306A, "NA\0\0"},
   {0x306B, "NI\0\0"},
   {0x306C, "NU\0\0"},
   {0x306D, "NE\0\0"},
   {0x306E, "NO\0\0"},
   {0x306F, "HA\0\0"},
   {0x3070, "BA\0\0"},
   {0x3071, "PA\0\0"},
   {0x3072, "HI\0\0"},
   {0x3073, "BI\0\0"},
   {0x3074, "PI\0\0"},
   {0x3075, "FU\0\0"},
   {0x3076, "BU\0\0"},
   {0x3077, "PU\0\0"},
   {0x3078, "HE\0\0"},
   {0x3079, "BE\0\0"},
   {0x307A, "PE\0\0"},
   {0x307B, "HO\0\0"},
   {0x307C, "BO\0\0"},
   {0x307D, "PO\0\0"},
   {0x307E, "MA\0\0"},
   {0x307F, "MI\0\0"},
   {0x3080, "MU\0\0"},
   {0x3081, "ME\0\0"},
   {0x3082, "MO\0\0"},
   {0x3083, "YA\0\0"}, // small YA
   {0x3084, "YA\0\0"},
   {0x3085, "YU\0\0"}, // small YU
   {0x3086, "YU\0\0"},
   {0x3087, "YO\0\0"}, // small YO
   {0x3088, "YO\0\0"},
   {0x3089, "RA\0\0"},
   {0x308A, "RI\0\0"},
   {0x308B, "RU\0\0"},
   {0x308C, "RE\0\0"},
   {0x308D, "RO\0\0"},
   {0x308E, "WA\0\0"}, // small WA
   {0x308F, "WA\0\0"},
   {0x3090, "WI\0\0"}, //??
   {0x3091, "WE\0\0"}, //??
   {0x3092, "O\0\0\0"},
   {0x3093, "N\0\0\0"},
   {0x3094, "VU\0\0"},
   {0x3095, "KA\0\0"}, // small KA
   {0x3096, "KE\0\0"},  // small KE
   {0x3097, "VA\0\0"},  // filler
   {0x3098, "VI\0\0"},  // filler
   {0x3099, "VE\0\0"},  // filler
   {0x309A, "VO\0\0"},  // filler
   {0x309B, "\xB7\0\0\0"},  // Katakana-hiragana voiced sound mark
   {0x309C, "-\0\0\0"},  // Katakana-hiragana semi-voiced sound mark
   {0x309D, "-\0\0\0"},  // filler
   {0x309E, "-\0\0\0"},  // filler
};


/*FUNCTION_HEADER*******************
 * NAME:   ;KataHalfwidthToFull
 * DESC:   Convert a unicode halfwidth katakana to full katakana.
 * IN:     pwchar - Address of wide-character to be converted.
 * OUT:    *pwchar is translated.
 * RETURN: wsUnicode - containing the character translation.
 * NOTES:  
 *END_HEADER***************************/
wchar_t KataHalfwidthToFull(wchar_t *pwchar)
{
	int offset = convertToOffset(*pwchar);
	wchar_t wcTemp = '\0\0';
	
	// This is just an added protection against a typing error.
	if (*pwchar == HalfwidthKatToFullKat[offset].wszUCSHalfWidthKat)
	{
		wcTemp = HalfwidthKatToFullKat[offset].wszFullKat;
	}
	else
	{
//      FNX_PRINTF("There was a problem in converting from halfwidth to full Katakana\n");
		return 0;
	}
	
	return wcTemp;
}

/*FUNCTION_HEADER*******************
 * NAME:   ;JapaneseToRomanji
 * DESC:   Convert a Japanese unicode string to Romanji in ASCII.
 * IN:     wsUnicode - Wide-character string to be converted.
           sRomanji - Character string to put the result into (NULL=>calculate size and allocate string).
 * OUT:    *sRomanji contains the string in wsUnicode converted to ASCII.
 * RETURN: Pointer to the resulting string (=sRomanji if sRomanji is not NULL;
              otherwise, points to a newly-allocated string).
           Return NULL on error.
 * NOTES:  Any wide characters in the range 0x0000-0x00FF are passed
             through as plain ASCII.  Other non-Japanese characters
             are dropped. [Perhaps we should insert a '?' instead?]
           Returns a valid string even if wsUnicode is empty, i.e., it
             will return an empty (null-terminated) but non-NULL string.
           Using sRomanji makes processing faster, but passing in a NULL
             will cause a string of just the right size to be allocated.
 *END_HEADER***************************/
int JapaneseToRomanji(wchar_t *wsUnicode, char *sRomanji)
{

   int nTimesThrough = 0;
   wchar_t *wsTemp = wsUnicode;
   char *sTemp = sRomanji;
   char cMb;
   int offset = 0;
   int offset1 = 0;
   int strLength = 0;
   int lineLength = 0;
   int result = 0;
   int iLen=0;

   /** Calculate string size, if needed **/
   if( sRomanji==NULL )
   {
      /* Count how big the resulting string will be and then allocate it */
      lineLength = wcslen(wsUnicode);
      while(lineLength)
      {
         if (*wsTemp >= 0xFF10 && *wsTemp <= 0xFF19)
            iLen++;
         else if (*wsTemp > 0x3041 && *wsTemp < 0x30FF || *wsTemp > 0xFF66)
         {
            if (*wsTemp > 0xFF66)
               *wsTemp = KataHalfwidthToFull(wsTemp);
            if (0x30FD == *wsTemp)
            {
               iLen++;
               lineLength--;
               continue;
            }
            else if (0x30FE == *wsTemp)
            {
				iLen++;
				wsTemp++;
				lineLength--;
				continue;
            }
            else 
				offset = convertToOffset(*wsTemp);

            switch(offset)
            {
                  // special conditions
               case 0x0c:  // ki
               case 0x0d:  // gi
               case 0x17:  // ji
               case 0x2a:  // ni
               case 0x31:  // hi
               case 0x32:  // bi
               case 0x33:  // pi
               case 0x3e:  // mi
               case 0x49:  // ri
                  // copy the characters over to the list.
                  strLength = FNX_STRLEN(KatHir[offset].szRomanji);
				  iLen += strLength;	
                  wsTemp++;
                  if (*wsTemp > 0xFF66)
                     offset1 = convertToOffset(KataHalfwidthToFull(wsTemp));
                  else 
					  offset1 = convertToOffset(*wsTemp);

                  if (offset1 == 0x42 || offset1 == 0x44 || offset1 == 0x46)
                  {
                     iLen--;
                     strLength = FNX_STRLEN(KatHir[offset1].szRomanji);
					 iLen += strLength;
                  }
                  else 
					  wsTemp--;
   
                  break;

               case 0x16:  // shi
                  wsTemp++;
                  if (*wsTemp > 0xFF66)
                     offset1 = convertToOffset(KataHalfwidthToFull(wsTemp));
                  else 
					  offset1 = convertToOffset(*wsTemp);
                  if (0x42 == offset1 || 0x44 == offset1 || 0x46 == offset1)
                     iLen+=4;
                  else
                  {
                     strLength = FNX_STRLEN(KatHir[offset].szRomanji);
                     iLen += strLength;
                     wsTemp--;
                  }
                  break;
               
			   case 0x20:  // chi
                  // Get next character.
                  wsTemp++;
                  if (*wsTemp > 0xFF66)
                     offset1 = convertToOffset(KataHalfwidthToFull(wsTemp));
                  else 
					  offset1 = convertToOffset(*wsTemp);

                  // copy the characters over to the list.
                  if (0x42 == offset1 || 0x44 == offset1 || 0x46 == offset1)
                     iLen += 4;
                  else
                  {
                     strLength = FNX_STRLEN(KatHir[offset].szRomanji);
                     iLen += strLength;
                     wsTemp--;
                  }

                  if (offset1 == 0x06) // small E
                     wsTemp++;
                  break;

               case 0x22: // Double the concenant that follows.
                  // Point to the concenant.
                  wsTemp++;
                  if (*wsTemp > 0xFF66)
                     offset1 = convertToOffset(KataHalfwidthToFull(wsTemp));
                  else 
					  offset1 = convertToOffset(*wsTemp);
                  wsTemp--;
                  iLen++;
                  break;

               default:
                  // copy the characters over to the list.
                  strLength = FNX_STRLEN(KatHir[offset].szRomanji);
                  iLen+=strLength;
                  break;
            }
         }
         else if (iswascii( *wsTemp))
            iLen++;

         wsTemp++;
         lineLength--;
      }

	  return iLen+1;

   }

   lineLength = wcslen(wsUnicode);
   while (lineLength)
   {

      if (*wsTemp >= 0xFF10 && *wsTemp <= 0xFF19)
      {
         // This is halfwidth Katakana numbering system that is used with full Katakana.
         *sTemp = (char)(*wsTemp - 0x10 )+ 0x30;
         sTemp++;
      }
      else if (*wsTemp > 0x3041 && *wsTemp < 0x30FF || *wsTemp > 0xFF66)
      {
         if (*wsTemp > 0xFF66)
         {
            // convert from halfwidth to full Katakana
            *wsTemp = KataHalfwidthToFull(wsTemp);
         }

         // Check for the sound marks
         // This most often happens with halfwidth.
         if (0x30FD == *wsTemp)
         {
            char *psTemp1 = sTemp;
            psTemp1-=2;
            switch(*psTemp1)
            {
            case'K':
               *psTemp1 = 'G';
               break;
            case'S':
               *psTemp1 = 'J';
               break;
            case 'H':
               *psTemp1 = 'B';
               break;
            case 'T':
               *psTemp1 = 'D';
               break;
            }
            wsTemp++;
            lineLength--;
            continue;
         }
         else if (0x30FE == *wsTemp)
         {
            char *psTemp1 = sTemp;
            psTemp1-=2;
            if (*psTemp1 == 'H')
            {
               *psTemp1 = 'P';
            }
            wsTemp++;
            lineLength--;
            continue;
         }
         else
         {
            offset = convertToOffset(*wsTemp);
         }


         switch(offset)
         {
               // special conditions
            case 0x0c:  // ki
            case 0x0d:  // gi
            case 0x17:  // ji
            case 0x2a:  // ni
            case 0x31:  // hi
            case 0x32:  // bi
            case 0x33:  // pi
            case 0x3e:  // mi
            case 0x49:  // ri
               // copy the characters over to the list.
               strLength = FNX_STRLEN(KatHir[offset].szRomanji);
               FNX_STRNCPY(sTemp, KatHir[offset].szRomanji, strLength);
               sTemp += strLength;
               wsTemp++;
               if (*wsTemp > 0xFF66)
               {
                  // convert from halfwidth to full Katakana
                  *wsTemp = KataHalfwidthToFull(wsTemp);
               }
               offset1 = convertToOffset(*wsTemp);
               if (offset1 == 0x42 || offset1 == 0x44 || offset1 == 0x46)
               {
                  sTemp--;
                  strLength = FNX_STRLEN(KatHir[offset1].szRomanji);
                  FNX_STRNCPY(sTemp, KatHir[offset1].szRomanji, strLength);
                  sTemp += strLength;
               }
               else
               {
                  wsTemp--;
               }
   
               break;
            case 0x16:  // shi
               // Get next character.
               wsTemp++;
               if (*wsTemp > 0xFF66)
               {
                  // convert from halfwidth to full Katakana
                  *wsTemp = KataHalfwidthToFull(wsTemp);
               }
               offset1 = convertToOffset(*wsTemp);
               // copy the characters over to the list.
               if (0x42 == offset1)
               {
                  FNX_STRCPY(sTemp, "SHYA");
                  sTemp+=4;
               }
               else if (0x44 == offset1)
               {
                  // copy the characters over to the list.
                  FNX_STRCPY(sTemp, "SHYU");
                  sTemp+=4;
               }
               else if (0x46 == offset1)
               {
                  // copy the characters over to the list.
                  FNX_STRCPY(sTemp, "SHYO");
                  sTemp+=4;
               }
               else
               {
                  strLength = FNX_STRLEN(KatHir[offset].szRomanji);
                  FNX_STRNCPY(sTemp, KatHir[offset].szRomanji, strLength);
                  sTemp+=strLength;
                  wsTemp--;
               }
               break;
            case 0x20:  // chi
               // Get next character.
               wsTemp++;
               if (*wsTemp > 0xFF66)
               {
                  // convert from halfwidth to full Katakana
                  *wsTemp = KataHalfwidthToFull(wsTemp);

               }
               offset1 = convertToOffset(*wsTemp);

               // copy the characters over to the list.
               if (0x42 == offset1)
               {
                  FNX_STRCPY(sTemp, "CHYA");
                  sTemp+=4;
               }
               else if (0x44 == offset1)
               {
                  FNX_STRCPY(sTemp, "CHYU");
                  sTemp+=4;
               }
               else if (0x46 == offset1)
               {
                  FNX_STRCPY(sTemp, "CHYO");
                  sTemp+=4;
               }
//               else
//               {
                  // copy the characters over to the list.
//                  FNX_STRCPY(sTemp, "CHI");
//                  sTemp+=2; // This is to compansate for the triple in
//                  wsTemp--;
//               }
               else
               {
                  strLength = FNX_STRLEN(KatHir[offset].szRomanji);
                  FNX_STRNCPY(sTemp, KatHir[offset].szRomanji, strLength);
                  sTemp+=strLength;
                  wsTemp--;
               }

               if (offset1 == 0x06) // small E
               {
                  sTemp--;
                  *sTemp = 'E';
                  sTemp++;
                  wsTemp++;
               }
               break;
            case 0x22: // Double the concenant that follows.
               // Point to the concenant.
               wsTemp++;
               if (*wsTemp > 0xFF66)
               {
                  // convert from halfwidth to full Katakana
                  *wsTemp = KataHalfwidthToFull(wsTemp);
               }
               offset1 = convertToOffset(*wsTemp);
               *sTemp =  KatHir[offset1].szRomanji[0];
               wsTemp--;
               sTemp++;
               break;
            default:
               // copy the characters over to the list.
               strLength = FNX_STRLEN(KatHir[offset].szRomanji);
               FNX_STRNCPY(sTemp, KatHir[offset].szRomanji, strLength);
               sTemp+=strLength;
               break;
         }
      }
      else if (iswascii( *wsTemp))
      {
         wctomb( &cMb, *wsTemp );
         if (cMb == 0x0a || cMb == 0x0d)
         {
            *sTemp = '\0';
         }
         else *sTemp = cMb;
         sTemp++;
      }
      wsTemp++;
      lineLength--;
   }
   return FNX_STRLEN(sRomanji);
}


/*FUNCTION_HEADER**********************
 * NAME:	;ConvertToAscii
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int ConvertToAscii(NULL, wchar_t *wstr, char *szbuf, BOOL bUnicode)
{
	return JapaneseToRomanji(wstr, szbuf);

}

