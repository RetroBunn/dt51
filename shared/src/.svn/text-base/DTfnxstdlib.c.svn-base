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
#include "DTFnxStdlib.h"
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
#if defined (_MSC_VER)
// Everyone's code should go ahead and use fonix's tolower function
//   as well as the STRICMP and STRNICMP functions, so that 
//   international characters are sorted and looked up properly. -drw
#pragma message ("Warning: Not using Fonix 'tolower' function.  European languages not supported")
#endif
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
wchar_t *fnxwStrupr( wchar_t *string )
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
int fnxwIsascii( wchar_t c )
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

#ifdef FNXW_BUILD_WCTOMB

 static const wchar_t encoding_mask[] =
{
   (wchar_t)~0x7ff, (wchar_t)~0xffff, (wchar_t)~0x1fffff, (wchar_t)~0x3ffffff
 };
 
 static const unsigned char encoding_byte[] =
 {
   0xc0, 0xe0, 0xf0, 0xf8, 0xfc
 };
 
 /* The state is for this UTF8 encoding not used.  */
 //static mbstate_t internal;
 
 
 //extern mbstate_t __no_r_state;  /* Defined in mbtowc.c.  */

 size_t
 __fnxawcrtomb (char *s, wchar_t wc);
 
 /*
  * Convert WCHAR into its multibyte character representation,
  * putting this in S and returning its length.
  *
  * Attention: this function should NEVER be intentionally used.
  * The interface is completely stupid.  The state is shared between
 * all conversion functions.  You should use instead the restartable
  * version `wcrtomb'.
  *
  * @implemented
 */
 int fnxawctomb (char *s, wchar_t wchar)
{
   /* If S is NULL the function has to return null or not null
      depending on the encoding having a state depending encoding or
      not.  This is nonsense because any multibyte encoding has a
      state.  The ISO C amendment 1 corrects this while introducing the
      restartable functions.  We simply say here all encodings have a
      state.  */
  if (s == NULL)
     return 1;
 
   return __fnxawcrtomb (s, wchar);
 }

 
 size_t
 __fnxawcrtomb (char *s, wchar_t wc)
 {
   char fake[1];
   size_t written = 0;
 
 
 
   if (s == NULL)
     {
       s = fake;
#if defined CASIO_SH3 && defined _BIGENDIAN_
       wc = '\0';
#else
       wc = L'\0';
#endif
     }
 
   if (wc < 0x80)
     {
      /* It's a one byte sequence.  */
       if (s != NULL)
         *s = (char) wc;
       return 1;
    }
 
   for (written = 2; written < 6; ++written)
     if ((wc & encoding_mask[written - 2]) == 0)
       break;
 
   if (s != NULL)
     {
       size_t cnt = written;
       s[0] = encoding_byte[cnt - 2];
 
       --cnt;
       do
         {
           s[cnt] = 0x80 | (wc & 0x3f);
          wc >>= 6;
         }
       while (--cnt > 0);
       s[0] |= wc;
     }
 
   return written;
 }
#endif


#ifdef FNXW_BUILD_WCSTOMBS
#define mbstate_t int
#define WCHAR_MIN       0
#define WCHAR_MAX       ((wchar_t)-1)

 static const wchar_t encoding_mask1[] =
{
   (~0x7ff&WCHAR_MAX), (~0xffff&WCHAR_MAX), (~0x1fffff&WCHAR_MAX), (~0x3ffffff&WCHAR_MAX)
};
 
 static const unsigned char encoding_byte1[] =
 {
   0xc0, 0xe0, 0xf0, 0xf8, 0xfc
 };
 
 /* We don't need the state really because we don't have shift states
    to maintain between calls to this function.  */
 
static mbstate_t mbstate_internal;
 
 
 mbstate_t __no_r_state;  /* Now defined in wcstombs.c.  */
 //extern mbstate_t __no_r_state;  /* Defined in mbtowc.c.  */
 
 size_t
 __fnxawcsrtombs (char *dst, const wchar_t **src, size_t len, mbstate_t *ps);
 
 /*
  * Convert the `wchar_t' string in PWCS to a multibyte character string
  * in S, writing no more than N characters.  Return the number of bytes
  * written, or (size_t) -1 if an invalid `wchar_t' was found.
  *
  * Attention: this function should NEVER be intentionally used.
  * The interface is completely stupid.  The state is shared between
  * all conversion functions.  You should use instead the restartable
  * version `wcsrtombs'.
  *
  * @implemented
  */
 size_t fnxawcstombs (char *s, const wchar_t *pwcs, size_t n)
 {
   mbstate_t save_shift = __no_r_state;
   size_t written;
 
   written = __fnxawcsrtombs (s, &pwcs, n, &__no_r_state);
 
   /* Restore the old shift state.  */
   __no_r_state = save_shift;
 
   /* Return how many we wrote (or maybe an error).  */
   return written;
 }
 
 size_t  __fnxawcsrtombs (char *dst, const wchar_t **src, size_t len, mbstate_t *ps)
 {
   size_t written = 0;
   const wchar_t *run = *src;
 
   if (ps == NULL)
     ps = &mbstate_internal;
 
   if (dst == NULL)
     /* The LEN parameter has to be ignored if we don't actually write
       anything.  */
     len = ~0;
 
   while (written < len)
     {
       wchar_t wc = *run++;
 
#if defined CASIO_SH3 && defined _BIGENDIAN_
      if (wc == '\0')
#else
      if (wc == L'\0')
#endif
         {
           /* Found the end.  */
           if (dst != NULL)
             *dst = '\0';
           *src = NULL;
           return written;
         }
       else if (wc < 0x80)
         {
           /* It's an one byte sequence.  */
           if (dst != NULL)
             *dst++ = (char) wc;
           ++written;
         }
       else
         {
           size_t step;
 
           for (step = 2; step < 6; ++step)
             if ((wc & encoding_mask1[step - 2]) == 0)
               break;
 
           if (written + step >= len)
             /* Too long.  */
             break;
 
           if (dst != NULL)
             {
               size_t cnt = step;
 
               dst[0] = encoding_byte1[cnt - 2];
 
               --cnt;
               do
                 {
                   dst[cnt] = 0x80 | (wc & 0x3f);
                   wc >>= 6;
                 }
               while (--cnt > 0);
               dst[0] |= wc;
 
               dst += step;
             }
 
           written += step;
         }
    }
 
   /* Store position of first unprocessed word.  */
   *src = run;
 
   return written;
 }

#endif

#ifdef FNXW_BUILD_ATOI
#include <ctype.h>

 long wcstol(const wchar_t *nptr, wchar_t **endptr, int base)
{
  const wchar_t *s = nptr;
  unsigned long acc;
  int c;
  unsigned long cutoff;
  int neg = 0, any, cutlim;

  /*
   * Skip white space and pick up leading +/- sign if any.
   * If base is 0, allow 0x for hex and 0 for octal, else
   * assume decimal; if base is already 16, allow 0x.
   */
  do {
    c = *s++;
  } while (isspace(c));
//  } while (iswctype(c, _SPACE));
  if (c == '-')
  {
    neg = 1;
    c = *s++;
  }
#if defined CASIO_SH3 && defined _BIGENDIAN_
  else if (c == '+')
#else
  else if (c == L'+')
#endif
    c = *s++;
#if defined CASIO_SH3 && defined _BIGENDIAN_
  if ((base == 0 || base == 16) &&
      c == '0' && (*s == 'x' || *s == 'X'))
#else
  if ((base == 0 || base == 16) &&
      c == L'0' && (*s == L'x' || *s == L'X'))
#endif
  {
    c = s[1];
    s += 2;
    base = 16;
  }
  if (base == 0)
#if defined CASIO_SH3 && defined _BIGENDIAN_
    base = c == '0' ? 8 : 10;
#else
    base = c == L'0' ? 8 : 10;
#endif

  /*
   * Compute the cutoff value between legal numbers and illegal
   * numbers.  That is the largest legal value, divided by the
   * base.  An input number that is greater than this value, if
   * followed by a legal input character, is too big.  One that
   * is equal to this value may be valid or not; the limit
   * between valid and invalid numbers is then based on the last
   * digit.  For instance, if the range for longs is
   * [-2147483648..2147483647] and the input base is 10,
   * cutoff will be set to 214748364 and cutlim to either
   * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
   * a value > 214748364, or equal but the next digit is > 7 (or 8),
   * the number is too big, and we will return a range error.
   *
   * Set any if any `digits' consumed; make it negative to indicate
   * overflow.
   */
  cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
  cutlim = cutoff % (unsigned long)base;
  cutoff /= (unsigned long)base;
  for (acc = 0, any = 0;; c = *s++)
  {
    if (isdigit(c))
//    if (iswctype(c, _DIGIT))
#if defined CASIO_SH3 && defined _BIGENDIAN_
      c -= '0';
#else
      c -= L'0';
#endif
    else if (isalpha(c))
//    else if (iswctype(c, _ALPHA))
#if defined CASIO_SH3 && defined _BIGENDIAN_
      c -= isupper(c) ? 'A' - 10 : 'a' - 10;
//      c -= iswctype(c, _UPPER) ? 'A' - 10 : 'a' - 10;
#else
      c -= iswctype(c, _UPPER) ? L'A' - 10 : L'a' - 10;
#endif
    else
      break;
    if (c >= base)
      break;
    if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
      any = -1;
    else
    {
      any = 1;
      acc *= base;
      acc += c;
    }
  }
  if (any < 0)
  {
    acc = neg ? LONG_MIN : LONG_MAX;
  }
  else if (neg)
    acc = -acc;
  if (endptr != 0)
    *endptr = any ? (wchar_t *)s - 1 : (wchar_t *)nptr;
  return acc;
}

int fnxawtoi(const wchar_t *str)
{
  return (int)wcstol(str, 0, 10);
}
#endif


#ifdef FNXW_BUILD_STRCAT
wchar_t * fnxawstrcat(wchar_t * dest,const wchar_t * src)
{
  
  wchar_t *d = dest;
  for (; *dest !=0; dest++);
  while (*src != 0)
  {
	*dest = *src;
	dest++;
	src++;
  }
  *dest = 0;
  return d;
}
#endif
