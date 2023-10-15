/*C_HEADER_FILE****************************************************************
FILE        :  FnxStdlib.h
DESC        :  
TABS        :  3
OWNER       :  Fonix
DATE CREATED:  

(C) Copyright 2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 2/25/04 8:36a $
  $Revision: 13 $

*END_HEADER*******************************************************************/
#include "FnxPlatform.h"
#include "FnxStdlib.h"
#include "FnxAllocate.h"

#ifdef FNXA_BUILD_TOLOWER
/*FUNCTION_HEADER**********************
 * NAME:    ;fnxaTolower      
 * DESC:    Convert a character to lower case (even if it is a foreign character like
               'À', which would convert to 'à').
 * IN:      c - Character to convert.
 * OUT:     n/a
 * RETURN:  Lower-case version of 'c'.
 * NOTES:   Converts 'A'..'Z' to 'a'..'z' (by adding 32).
            Unlike standard tolower() functions, this function
               also adds 32 to extended ASCII (foreign) characters
               in the ranges 192..214 (->224..246), 216..222 (->248..254).
            Does NOT handle international characters in "code page 437"
              (i.e., those used in DOS windows), so you'll have to
              covert to "code page 1252" (aka "WinLatin 1") for this
              routine to work for you.
 *END_HEADER***************************/
int fnxaTolower(int c)
{
   c &= 0xFF;
   if (c>='A' && c<='Z')
      c += 32;
   else if (c>=192 && c<=222 && c!=215)
      c += 32;
   else if (c==140) // Capital "OE" (Œ->œ).
      c = 156; // lower-case "oe"
   else if (c==159)
      c = 255; // Y with umlaut.(Ÿ->ÿ)
   /* The following would allow "code page 437" (as used in MS-DOS windows)
      to be converted as well, but would also cause characters in the
      more standard Unicode-ish "code page 1252" (aka WinLatin 1) to
      be changed, too.  So we will leave this code commented out and
      require any text from code page 437 to be mapped before being used. */
   //else if (c>128)
   //{
      //switch(c)
      //{
      //   case 128: c = 135; break;// French "C" with thingy at bottom
      //   case 142: c = 132; break;// A with two dots over
      //   case 143: c = 134; break;// A with circle over
      //   case 144: c = 130; break;// E with accent
      //   case 146: c = 145; break;// AE
      //   case 153: c = 148; break;// O with two dots over
      //   case 154: c = 129; break;// U with two dots over
      //}
   //}

   return c;
}
#else
// Everyone's code should go ahead and use fonix's tolower function
//   as well as the STRICMP and STRNICMP functions, so that 
//   international characters are sorted and looked up properly. -drw
#pragma message ("Warning: Not using Fonix 'tolower' function.  European languages not supported")
#endif

#ifdef FNXA_BUILD_TOUPPER
/*FUNCTION_HEADER**********************
 * NAME:    ;fnxaToupper      
 * DESC:    Convert a character to upper case (even if it is a foreign character like
               'à', which would convert to 'À').
 * IN:      c - Character to convert.
 * OUT:     n/a
 * RETURN:  Lower-case version of 'c'.
 * NOTES:   Converts 'A'..'Z' to 'a'..'z' (by subtracting 32).
            Unlike standard toupper() functions, this function
               also subtracts 32 from extended ASCII (foreign) characters
               in the ranges 224..246 (->192..214), 248..254 (->216..222).
            Does NOT handle international characters in "code page 437"
              (i.e., those used in DOS windows), so you'll have to
              covert to "code page 1252" (aka "WinLatin 1") for this
              routine to work for you.
 *END_HEADER***************************/
int fnxaToupper(int c)
{
   c &= 0xFF;
   if (c>='a' && c<='z')
      c -= 32;
   else if (c>=224 && c<=254 && c!=247)
      c -= 32;
   else if (c==156) /* oe */
      c = 140; /* OE */
   return c;
}
#endif

#ifdef FNXA_BUILD_STRDUP
char *fnxaStrdup(const char *pStr)
{
   char  *pNew = NULL;

   if (pStr && (pNew = FNX_MALLOC( (FNXA_STRLEN(pStr)+1) * sizeof(char) )) != NULL )
   {
      FNXA_STRCPY(pNew, pStr);
   }

   return pNew;
}
#endif

#ifdef FNXW_BUILD_STRDUP
wchar_t *fnxwStrdup(const wchar_t *pStr)
{
   wchar_t  *pNew = NULL;

   if (pStr && (pNew = FNX_MALLOC( (FNXW_STRLEN(pStr)+1) * sizeof(wchar_t) )) != NULL)
   {
      FNXW_STRCPY(pNew, pStr);
   }

   return pNew;
}
#endif

#ifdef FNXA_BUILD_STRNICMP
int fnxaStrnicmp( const char *string1, const char *string2, size_t count )
{
   const char  *p1 = string1, *p2 = string2;
   unsigned char  uc1, uc2;
   size_t   i;

   for( i = 0; *p1 != 0 && *p2 != 0 && i < count; i++ )
   {
      uc1 = (unsigned char)FNXA_TOLOWER( *p1 );
      uc2 = (unsigned char)FNXA_TOLOWER( *p2 );
      if( uc1 < uc2 )
         return -1;
      else if (uc1 > uc2)
         return 1;
      p1++;
      p2++;
   }

   if( i==count || (*p1 == 0 && *p2 == 0)) // Equivalent strings
      return 0;
   else if( *p1 == 0 ) // String1 is shorter
      return -1;
   else // String2 is shorter
      return 1;
}
#endif

#ifdef FNXW_BUILD_STRNICMP
int fnxwStrnicmp( const wchar_t *string1, const wchar_t *string2, size_t count )
{
   const wchar_t  *p1 = string1, *p2 = string2;
   unsigned wchar_t  c1, c2;
   size_t   i;

   for( i = 0; *p1 != 0 && *p2 != 0 && i < count; i++ )
   {
      c1 = (unsigned wchar_t)FNXW_TOLOWER( *p1 );
      c2 = (unsigned wchar_t)FNXW_TOLOWER( *p2 );
      if( c1 < c2 )
         return -1;
      else if (c1 > c2)
         return 1;
      p1++;
      p2++;
   }

   if (i==count || (*p1 == 0 && *p2 == 0)) // Equivalent strings (or matched for first 'count' chars)
      return 0;
   else if (*p1 ==0) // String1 is shorter than both 'count' and p2.
      return -1;
   else // String2 is shorter than both 'count' and p1.
      return 1;
}
#endif

#ifdef FNXA_BUILD_STRICMP
int fnxaStricmp( const char *string1, const char *string2 )
{
   const char  *p1 = string1, *p2 = string2;
   unsigned char  uc1, uc2; // Use unsigned chars to avoid negative values.

   while( *p1 != 0 && *p2 != 0 )
   {
      uc1 = (unsigned char)FNXA_TOLOWER( *p1 );
      uc2 = (unsigned char)FNXA_TOLOWER( *p2 );
      if( uc1 < uc2 )
         return -1;
      else if (uc1 > uc2)
         return 1;
      p1++;
      p2++;
   }

   if( *p1 == 0 && *p2 == 0 ) // Equivalent strings
      return 0;
   else if( *p1 == 0 ) // String1 is shorter
      return -1;
   else // String2 is shorter
      return 1;
}
#endif

#ifdef FNXW_BUILD_STRICMP
int fnxwStricmp( const wchar_t *string1, const wchar_t *string2 )
{
   const wchar_t  *p1 = string1, *p2 = string2;
   unsigned wchar_t  c1, c2;

   while( *p1 != 0 && *p2 != 0 )
   {
      (unsigned wchar_t)c1 = FNXW_TOLOWER( *p1 );
      (unsigned wchar_t)c2 = FNXW_TOLOWER( *p2 );
      if( c1 < c2 )
         return -1;
      else if (c1 > c2)
         return 1;
      p1++;
      p2++;
   }

   if( *p1 == 0 && *p2 == 0 ) // Equivalent strings
      return 0;
   else if( *p1 == 0 ) // String1 is shorter
      return -1;
   else // String2 is shorter
      return 1;
}
#endif

#ifdef FNXA_BUILD_STRUPR
char *fnxaStrupr( char *string )
{
   char *p = string;

   while( *p != 0 )
   {
      *p = (char)FNXA_TOUPPER( *p );
      p++;
   }
   return string;
}
#endif

#ifdef FNXW_BUILD_STRUPR
char *fnxwStrupr( wchar_t *string )
{
   wchar_t *p = string;

   while( *p != 0 )
   {
      *p = (wchar_t)FNXW_TOUPPER( *p );
      p++;
   }
   return string;
}
#endif

#ifdef FNXA_BUILD_STRLWR
char *fnxaStrlwr( char *string )
{
   char *p = string;

   while( *p != 0 )
   {
      *p = (char)FNXA_TOLOWER( *p );
      p++;
   }
   return string;
}
#endif

#ifdef FNXW_BUILD_STRLWR
wchar_t *fnxwStrlwr( wchar_t *string )
{
   wchar_t *p = string;

   while( *p != 0 )
   {
     *p = (wchar_t)FNXW_TOLOWER( *p );
      p++;
   }
   return string;
}
#endif

#ifdef FNXA_BUILD_STRREV
char *fnxaStrrev( char *string )
{
   size_t nLen = FNXA_STRLEN( string );

   if( nLen > 1 )
   {
      char *pFront = string;
      char *pBack = &string[ nLen - 1];

      while( pFront < pBack )
      {
         *pFront = *pFront ^ *pBack;   // swap front char with back char using Xor
         *pBack  = *pFront ^ *pBack;
         *pFront = *pFront ^ *pBack;
         pFront += 1;
         pBack -= 1;
      }
   }
   return string;
}
#endif

#ifdef FNXW_BUILD_STRREV
wchar_t *fnxwStrrev( wchar_t *string )
{
   size_t nLen = FNXW_STRLEN( string );
   if( nLen > 1 )
   {
      wchar_t *pFront = string;
      wchar_t *pBack = string + ( (nLen-1)*sizeof(wchar_t) );

      while( pFront < pBack )
      {
         *pFront = *pFront ^ *pBack;   // swap front char with back char using Xor
         *pBack  = *pFront ^ *pBack;
         *pFront = *pFront ^ *pBack;
         pFront++;
         pBack--;
      }
   }
   return string;
}
#endif

#ifdef FNXA_BUILD_STRRCHR
char * fnxaStrrchr( const char * string, int nChar )
{
   size_t nLen = FNXA_STRLEN( string );
   char * pCur = (char*)&string[ nLen ];

   if( nLen <= 0 )
      return NULL;

   while( string <= pCur )
   {
      if( (char)nChar == pCur[0] )
         return pCur;
      pCur -= 1;
   }
   return NULL;
}
#endif

#ifdef FNXA_BUILD_STRPBRK
char * fnxaStrpbrk(const char * string, const char * strCharSet)
{
   char * pInString=(char*)string;
   char * pChars=NULL;

   while( pInString[0] )
   {
      pChars = (char*)strCharSet;
      while( pChars[0] )
      {
         if( pInString[0] == pChars[0] )
            break;
         pChars++;
      }
      if( pChars[0] )
         break;
      pInString++;
   }
   if( !pInString[0] )
      return NULL;
   return pInString;
}
#endif

#ifdef FNXA_BUILD_STRRCHR
size_t fnxaStrspn(const char * string, const char * strCharSet)
{
   char * pInString=(char*)string;
   char * pChars=NULL;

   while( pInString[0] )
   {
      pChars = (char*)strCharSet;
      while( pChars[0] )
      {
         if( pInString[0] == pChars[0] )
            break;
         pChars++;
      }
      if( !pChars[0] )
         break;
      pInString++;
   }
   return pInString-string;
}
#endif

#ifdef FNXA_BUILD_ISASCII
int fnxaIsascii( int c )
{
   return c >= 0 && c <= 127;
}
#endif

#ifdef FNXW_BUILD_ISASCII
int fnxwIsascii( int c )
{
   return c >= 0 && c <= 127;
}
#endif

#ifdef FNX_BUILD_BSEARCH
void *fnxaBSearch( const void *key, const void *base, size_t num, size_t width, int (__cdecl *compare)(const void *, const void *) )
{
        char *lo = (char *)base;
        char *hi = (char *)base + (num - 1) * width;
        char *mid;
        unsigned int half;
        int result;

        while (lo <= hi)
                if (half = num / 2)
                {
                        mid = lo + (num & 1 ? half : (half - 1)) * width;
                        if (!(result = (*compare)(key,mid)))
                                return(mid);
                        else if (result < 0)
                        {
                                hi = mid - width;
                                num = num & 1 ? half : half-1;
                        }
                        else    {
                                lo = mid + width;
                                num = half;
                        }
                }
                else if (num)
                        return((*compare)(key,lo) ? NULL : lo);
                else
                        break;

        return(NULL);
}
#endif

char * FNX_STRNCPY_NULL( char *dest, const char *src, int n )
{
   FNX_STRNCPY( dest, src, n );
   // Null terminate the copied string regardless of size of n.
   dest[ n ] = 0;
   return dest;
}

#ifdef FNX_BUILD_GETFILELEN
/***********************************************************
Returns the length of the file.
***********************************************************/
long fnxaGetFileLength( FILE * fp )
{
	#if defined( OS_WIN32 ) && !defined( UNDER_CE )
		#pragma message ("should never get to this line of code!!!")
		return _filelength( _fileno( fp ) );
	#else  // OS_WIN32
		long nRet=-1;
		#ifdef EMACHINE
			long nCur=FNX_MF_FTELL( fp );       // get current location

			FNX_MF_FSEEK( fp, 0, SEEK_END );    // move to end
			nRet = FNX_MF_FTELL( fp );          // get end location (length)
			FNX_MF_FSEEK( fp, nCur, SEEK_SET ); // return back to current location
		#else
			long nCur=FNXA_FTELL( fp );       // get current location

			FNXA_FSEEK( fp, 0, SEEK_END );    // move to end
			nRet = FNXA_FTELL( fp );          // get end location (length)
			FNXA_FSEEK( fp, nCur, SEEK_SET ); // return back to current location
		#endif

		return nRet;
	#endif  // OS_WIN32
}
#endif  // FNX_BUILD_GETFILELEN

