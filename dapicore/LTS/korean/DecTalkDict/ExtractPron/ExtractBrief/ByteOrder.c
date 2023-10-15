/*C_HEADER_FILE****************************************************************
FILE        :  ByteOrder.c
DESC        :  Network Byte Order (NBO) handling routines
TABS        :  3
OWNER       :  
DATE CREATED:  

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/06/03 4:27p $
  $Revision: 3 $

*END_HEADER*******************************************************************/
#include "FnxPlatform.h"
#include "FnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxByteOrder.h"

/*
From: The Jargon Dictionary - http://info.astrian.net/jargon/ 

big-endian     adj.     [common; From Swift's "Gulliver's Travels" via the famous paper
 "On Holy Wars and a Plea for Peace" by Danny Cohen, USC/ISI IEN 137, dated April 1, 1980]
 1. Describes a computer architecture in which, within a given multi-byte numeric representation,
 the most significant byte has the lowest address (the word is stored `big-end-first').
 Most processors, including the IBM 370 family, the PDP-10, the Motorola microprocessor families,
 and most of the various RISC designs are big-endian. Big-endian byte order is also sometimes
 called `network order'. See little-endian, middle-endian, NUXI problem, swab.
 2. An Internet address the wrong way round. Most of the world follows the Internet standard
 and writes email addresses starting with the name of the computer and ending up with the name
 of the country. In the U.K. the Joint Networking Team had decided to do it the other way round
 before the Internet domain standard was established. Most gateway sites have ad-hockery in
 their mailers to handle this, but can still be confused. In particular, the address
 me@uk.ac.bris.pys.as could be interpreted in JANET's big-endian way as one in the U.K.
 (domain uk) or in the standard little-endian way as one in the domain as (American Samoa) on
 the opposite side of the world. 

little-endian     adj.     Describes a computer architecture in which, within a given
 16- or 32-bit word, bytes at lower addresses have lower significance (the word is stored
 `little-end-first'). The PDP-11 and VAX families of computers and Intel microprocessors and
 a lot of communications and networking hardware are little-endian. See big-endian,
 middle-endian, NUXI problem. The term is sometimes used to describe the ordering of units other
 than bytes; most often, bits within a byte. 
*/

typedef union 
{
   UDWORD a;  /* Guaranteed to be 4 bytes or someone's in trouble */
   char    b[4];
} myInt; // for x

/************ Byte-swapping routines *********************************/

/*FUNCTION_HEADER**********************
 * NAME:    ;IsLittleEndian
 * DESC:    Tell whether the platform is little-endian
 * IN:      n/a
 * OUT:     n/a
 * RETURN:  TRUE if this host is little-endian, FALSE otherwise
 * NOTES:   You really should have WORDS_BIGENDIAN or WORDS_LITTLEENDIAN #define'd,
            which makes this routine unnecessary.
 *END_HEADER***************************/
BOOL LittleEndian()
{
   myInt   x;

   x.a = 1;
   if (x.b[0])    // if host is little endian
      return TRUE;
   else
      return FALSE;
}

/*FUNCTION_HEADER**********************
 * NAME:    ;ByteSwap32
 * DESC:    Swap the bytes in a 4-byte integer
 * IN:      i - 32-bit (4-byte) integer to swap bytes in
 * OUT:     n/a
 * RETURN:  i with bytes swapped
 * NOTES:   Unlike big/little-to-little/big-Endian routines,
              this one swaps the bytes without checking to make
              sure it needs to be done.  (This is about 15% faster)
 *END_HEADER***************************/
UDWORD ByteSwap32(UDWORD i)
{
   return (0x000000FF & i >> 24) | (0x00FF0000 & i << 8) | (0x0000FF00 & i >> 8) | (0xFF000000 & i << 24);
}

/*FUNCTION_HEADER**********************
 * NAME:    ;ByteSwap16
 * DESC:    Swap the bytes in a 2-byte integer
 * IN:      i - 16-bit (2-byte) integer to swap bytes in
 * OUT:     n/a
 * RETURN:  i with bytes swapped
 * NOTES:   Unlike big/little-to-little/big-Endian routines,
              this one swaps the bytes without checking to make
              sure it needs to be done.  (This is about 15% faster)
 *END_HEADER***************************/
UWORD ByteSwap16(UWORD i)
{
   return ((unsigned short) 0x00FFU & i >> 8) | ((unsigned short) 0xFF00U & i << 8);
}

/*FUNCTION_HEADER**********************
 * NAME:    ;BlockByteSwap32
 * DESC:    Swap the bytes of each 4-byte integer in an array
 * IN:      pi - Array of 32-bit (4-byte) integers to swap bytes in
            iSize - Number of elements in pi[]
 * OUT:     pi[0..iSize-1] each have their bytes swapped.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
void BlockByteSwap32(UDWORDPTR pi, UDWORD iSize)
{
   UDWORD i;
   for (i=0; i< iSize; i++)
   {
      *pi = (0x000000FF & *pi >> 24) | (0x00FF0000 & *pi << 8) | (0x0000FF00 & *pi >> 8) | (0xFF000000 & *pi << 24);
      pi++; // some compilers don't handle the *pi++ = F(*pi) well.
   }
}

/*FUNCTION_HEADER**********************
 * NAME:    ;BlockByteSwap16
 * DESC:    Swap the bytes of each 2-byte integer in an array
 * IN:      pi - Array of 16-bit (2-byte) integers to swap bytes in
            iSize - Number of elements in pi[]
 * OUT:     pi[0..iSize-1] each have their bytes swapped.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
void BlockByteSwap16(UWORDPTR pw, UDWORD iSize)
{
   UDWORD i;
   for (i=0; i< iSize; i++)
   {
      *pw = ((unsigned short) 0x00FFU & *pw >> 8) | ((unsigned short) 0xFF00U & *pw << 8);
      pw++; // some compilers don't handle the *pw++ = F(*pw) well.
   }
}


