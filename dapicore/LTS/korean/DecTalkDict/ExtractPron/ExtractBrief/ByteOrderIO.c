/*C_HEADER_FILE****************************************************************
FILE        :  ByteOrder.c
DESC        :  Routines for read and writing numbers and strings in Network Byte Order (NBO)
TABS        :  3
OWNER       :  Randy Wilson
DATE CREATED:  

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/28/05 2:09p $
  $Revision: 8 $

*END_HEADER*******************************************************************/
#include "FnxPlatform.h"
#include "FnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxByteOrder.h"
#include "FnxByteOrderIO.h"
#include "FnxFiles.h"


/************ NBO file-writing routines *********************************/

/*FUNCTION_HEADER**********************
 * NAME:    ;WriteInt32NBO
 * DESC:    Write a 4-byte integer in network byte order
 * IN:      fp    - file pointer
            i     - integer to write 
 * OUT:     The integer is written to fp, with its bytes in network byte order (big-endian)
 * RETURN:  OK on success, _ERROR if there were any errors.
 * NOTES:   
 *END_HEADER***************************/
#ifndef NO_SYSFILE_WRITES
SDWORD WriteInt32NBO(FILE *fp, UDWORD i)
{
#ifdef WORDS_LITTLEENDIAN
   i = ByteSwap32(i); /* Little-endian, so swap bytes to put them in network byte order */
#endif /* else big-endian, so no need to swap */
   if (FNX_FWRITE(&i, 4, 1, fp)==1)
      return OK; /* ok */
   else return _ERROR;
}  /* WriteInt32NBO */
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;WriteInt16NBO
 * DESC:    Write a 2-byte integer in network byte order
 * IN:      fp    - file pointer
            i     - integer to write 
 * OUT:     The integer is written to fp, with its bytes in network byte order (big-endian)
 * RETURN:  OK on success, _ERROR if there were any errors.
 * NOTES:   
 *END_HEADER***************************/
#ifndef NO_SYSFILE_WRITES
SDWORD WriteInt16NBO(FILE *fp, UWORD uw)
{
   /* Swap bytes in i if necessary */
#ifdef WORDS_LITTLEENDIAN
   uw = ByteSwap16(uw);
#endif
   if (FNX_FWRITE(&uw, 2, 1, fp)==1)
      return OK;
   else return _ERROR;
}  /* WriteInt16NBO */
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;WriteCalcTypeNBO
 * DESC:    Write a 4-byte CalcType in network byte order
 * IN:      fp    - file pointer
            i     - integer to write 
 * OUT:     The CalcType is written to fp, with its bytes in network byte order (big-endian)
 * RETURN:  OK on success, _ERROR if there were any errors.
 * NOTES:   
 *END_HEADER***************************/
#ifndef NO_SYSFILE_WRITES
SDWORD WriteCalcTypeNBO(FILE *fp, CalcType fValue)
{
   UDWORD *pulValue;
   UDWORD ul;
   /* Get address of fValue, so that it can be dereferenced as a UDWORD */
   pulValue = (UDWORD *)&fValue;
   /* Set ul to be the (possibly byte-swapped) integer with the same bytes as fValue */
#ifdef WORDS_LITTLEENDIAN
   ul = ByteSwap32(*pulValue);
#else
   ul = *pulValue; /* big-endian, so don't bother swapping */
#endif
   /* Write ul */
   if (FNX_FWRITE(&ul,4,1,fp)==1)
      return OK; /* ok */
   else return _ERROR;
}  /* WriteCalcTypeNBO */
#endif

/*FUNCTION_HEADER**********************
 * NAME:    ;WriteString
 * DESC:    Write the length of a string to a file, followed by its characters (w/o null terminator).
 * IN:      fp    - file pointer
            s     - string to write 
 * OUT:     The length of the string is written as a two-byte unsigned integer,
              followed by the charcters (w/o a null terminator).
 * RETURN:  OK on success, _ERROR if there were any errors.
 * NOTES:   Treats 's' as the empty string "" if it is NULL (i.e., a length-0 string).
            Allows maximum length of 64K string (i.e., uses a 2-byte unsigned integer for the string length).
 *END_HEADER***************************/
#ifndef NO_SYSFILE_WRITES
SDWORD WriteString(FILE *fp, char *s)
{
   UWORD uwLen;
   if (s==NULL)
      s=""; /* Point at an empty string to handle null strings */
   /* Get the length of the string */
   uwLen = (UWORD) FNX_STRLEN(s);
   /* Write the length of the string */
   if (WriteInt16NBO(fp, uwLen)!=OK)
      return _ERROR;
   /* Write the actual string */
   if (uwLen>0)
   {
      if (FNX_FWRITE(s, uwLen, 1, fp)==1)
         return OK;
      else return _ERROR;
   }
   else return OK;
}  /* WriteString */

/*FUNCTION_HEADER**********************
 * NAME:    ;WriteStringList
 * DESC:    Write the an array of strings (using NBO lengths).
 * IN:      fp          - file pointer
            ps          - Array of strings to write 
            iNumStrings - Number of strings in ps[]
 * OUT:     iNumStrings and ps[0..iNumStrings-1] are written to fp.
 * RETURN:  OK on success, _ERROR if there were any errors.
 * NOTES:   None of the strings can be longer than 64K.
 *END_HEADER***************************/
SDWORD WriteStringList(FILE *fp, char **ps, SDWORD iNumStrings)
{
   SDWORD i;
   SDWORD iError=0;

   iError |= WriteInt32NBO(fp, iNumStrings);
   for (i=0; i<iNumStrings; i++)
      iError |= WriteString(fp, ps[i]);

   return iError;
}
#endif


/************ NBO file-reading routines *********************************/

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadInt32NBO
 * DESC:    Read a 4-byte integer in network byte order
 * IN:      fp    - file pointer
            pi    - Address in which to put the 4-byte integer that is read.
 * OUT:     The integer is read in network byte order from fp, 
              and then put into *pi with its bytes in host byte order
 * RETURN:  OK on success, _ERROR if there were any errors.
 * NOTES:   
 *END_HEADER***************************/
SDWORD ReadInt32NBO(FILE *fp, UDWORD *pi)
{
   if (FNX_FREAD(pi, 4, 1, fp)==1)
   {
#ifdef WORDS_LITTLEENDIAN
      *pi = ByteSwap32(*pi);
#endif  // else already in correct order
      return OK; /* ok */
   }
   else return _ERROR;
}

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadInt16NBO
 * DESC:    Write a 2-byte integer in network byte order
 * IN:      fp    - file pointer
            pi    - Address in which to put the integer that is read.
 * OUT:     The integer is read in network byte order from fp, 
              and then put into *pi with its bytes in host byte order
 * RETURN:  OK on success, _ERROR if there were any errors.
 * NOTES:   Reads two bytes, even if UWORD is not defined as a 2-byte integer.
 *END_HEADER***************************/
SDWORD ReadInt16NBO(FILE *fp, UWORD *pi)
{
   if (FNX_FREAD(pi, 2, 1, fp)==1)
   {
#ifdef WORDS_LITTLEENDIAN
      *pi = ByteSwap16(*pi);
#endif  // else already in correct order
      return OK; /* ok */
   }
   else return _ERROR;
}

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadCalcTypeNBO
 * DESC:    Read a 4-byte integer in network byte order
 * IN:      fp    - file pointer
            pi    - Address in which to put the integer that is read.
 * OUT:     The integer is read in network byte order from fp, 
              and then put into *pi with its bytes in host byte order
 * RETURN:  OK on success, _ERROR if there were any errors.
 * NOTES:   
 *END_HEADER***************************/
SDWORD ReadCalcTypeNBO(FILE *fp, CalcType *pf)
{
   /* Create an integer pointer that points at the 4-byte float, and
      then read four bytes into it (swapping them if necessary). */
   UDWORD *pi=(UDWORD *)pf;
   if (FNX_FREAD(pi, 4, 1, fp)==1)
   {
#ifdef WORDS_LITTLEENDIAN
      *pi = ByteSwap32(*pi);
#endif // Else BIGENDIAN and already in correct order
      return OK; /* ok */
   }
   else return _ERROR;
}  /* ReadCalcTypeNBO */

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadString
 * DESC:    Read a length and a string from a file.
 * IN:      fp    - file pointer
            ps    - Address in which to put a pointer to the newly-allocated string 
 * OUT:     *ps points to a newly-allocated string which is read from fp.
 * RETURN:  OK on success, _ERROR if there were any errors.
 * NOTES:   Requires a 2-byte unsigned integer in network byte order,
              followed by that many characters (with no null terminator).
            Returned pointer needs to be freed.
 *END_HEADER***************************/
SDWORD ReadString(FILE *fp, char **ps)
{
   UWORD uwLen;
   if (ReadInt16NBO(fp, &uwLen)!=OK)
      return _ERROR;
   //*ps = (char *)Calloc(uwLen+1, 1); /* Add 1 for null terminator.  "Calloc" sets last char to 0. */
   *ps = (char *)FNX_MALLOC(uwLen+1); /* Add 1 for null terminator */
   *(*ps + uwLen) = 0;  // set last char (*ps + uwLen + 1 - 1) to 0 explicitly for speed instead of using calloc 
   /* Don't bother reading anything if the length is 0, i.e., it is the empty string. */
   if (uwLen==0 || FNX_FREAD(*ps, uwLen, 1, fp)==1)
      return OK;
   else return _ERROR;
}

/*FUNCTION_HEADER**********************
 * NAME:    ;ReadString
 * DESC:    Read a length and a string from a file.
 * IN:      fp    - file pointer
            ps    - Address in which to put a pointer to the newly-allocated string 
 * OUT:     *ps points to a newly-allocated string which is read from fp.
 * RETURN:  OK on success, _ERROR if there were any errors.
 * NOTES:   Requires a 2-byte unsigned integer in network byte order,
              followed by that many characters (with no null terminator).
            Returned pointer needs to be freed.
 *END_HEADER***************************/
SDWORD ReadStringList(FILE *fp, char ***ppsStringList, SDWORD *piNumStrings)
{
   char **psStrings;
   SDWORD i, iError=0;

   iError |= ReadInt32NBO(fp, (unsigned long *)piNumStrings);
   if (iError)
      return iError;
   psStrings = (char **)FNX_CALLOC(*piNumStrings, sizeof(char *));
   for (i=0; i<*piNumStrings && !iError; i++)
      iError |= ReadString(fp, &(psStrings[i]));
   
   *ppsStringList = psStrings;

   return iError;
}
/*FUNCTION_HEADER**********************
   NAME: ;ReadInt32BlockNBO
   DESC: read a block of long unsigned integers in network byte order from a file
   IN:      fp    - file pointer to read from
            pValues  - array to be loaded with the data
            iNumItems - number of unsigned integers to read
   OUT:     the array pValues is loaded with iNumItems unsigned integer in hi/lo byte order
   RETURN:  OK on success, _ERROR if there were any errors.
   NOTES:   Array pValues must already be allocated
 *END_HEADER***************************/
SDWORD ReadInt32BlockNBO(FILE *fp, UDWORD *pValues, UDWORD iNumItems)
{
   SDWORD   iResult = _ERROR;
   
   if (FNX_FREAD(pValues, sizeof(UDWORD), iNumItems, fp) == iNumItems)
   {
#ifdef WORDS_LITTLEENDIAN
      BlockByteSwap32(pValues, iNumItems);
#endif
      iResult = OK;
   }
   return iResult;
}

/*FUNCTION_HEADER**********************
   NAME:   ;ReadInt16BlockNBO
   DESC:   Read a block of short (16-bit/2-byte) unsigned integers in network byte order from a file
   IN:     fp    - file pointer to read from
           pValues  - array to be loaded with the data
           iNumItems - number of unsigned integers to read
   OUT:    The array pValues is loaded with iNumItems unsigned integer in hi/lo byte order
   RETURN: OK on success, _ERROR if there were any errors.
   NOTES:   
 *END_HEADER***************************/
SDWORD ReadInt16BlockNBO(FILE *fp, UWORD *pValues, UDWORD iNumItems)
{
   SDWORD   iResult = _ERROR;

   if (FNX_FREAD(pValues, sizeof(UWORD), iNumItems, fp) == iNumItems)
   {
#ifdef WORDS_LITTLEENDIAN
      BlockByteSwap16(pValues, iNumItems);
#endif
      iResult = OK;
   }
   return iResult;
}

/*FUNCTION_HEADER**********************
   NAME:   ;WriteInt32BlockNBO
   DESC:   write a block of long unsigned integers to a file in network byte order 
   IN:     fp        - the target file
           pValues   - array of data to be written
           iNumItems - number of integers in the array
   OUT:    The data is written to the file in network byte order
   RETURN: OK on success, _ERROR if there were any errors.
   NOTES:   
 *END_HEADER***************************/
#ifndef NO_SYSFILE_WRITES
SDWORD WriteInt32BlockNBO(FILE *fp, UDWORD *pValues, UDWORD iNumItems)
{ 
   SDWORD   iResult = OK;

   /* Swap bytes of elements in the array if little-endian */
#ifdef WORDS_LITTLEENDIAN
   BlockByteSwap32(pValues, iNumItems);
#endif

   /* Write the block of integers to the file */
   if (FNX_FWRITE(pValues,sizeof(UDWORD),iNumItems,fp) != iNumItems)
      iResult = _ERROR;

   /* "Unswap" bytes of elements in the array if little-endian */
#ifdef WORDS_LITTLEENDIAN
   BlockByteSwap32(pValues, iNumItems);
#endif

   return iResult;
}
#endif

/*FUNCTION_HEADER**********************
   NAME:   ;WriteInt16BlockNBO
   DESC:   Write a block of short (16-bit/2-byte) unsigned integers to a file in network byte order 
   IN:     fp        - the target file
           pValues   - array of data to be written
           iNumItems - number of integers in the array
   OUT:    The data is written to the file in network byte order
   RETURN: OK on success, _ERROR if there were any errors.
   NOTES:   
 *END_HEADER***************************/
#ifndef NO_SYSFILE_WRITES
SDWORD WriteInt16BlockNBO(FILE *fp, UWORD *pValues, UDWORD iNumItems)
{ 
   SDWORD   iResult = OK;

   /* Swap bytes of elements in the array if little-endian */
#ifdef WORDS_LITTLEENDIAN
   BlockByteSwap16(pValues, iNumItems);
#endif

   /* Write the block of integers to the file */
   if (FNX_FWRITE(pValues,sizeof(UWORD),iNumItems,fp) != iNumItems)
      iResult = _ERROR;

   /* "Unswap" bytes of elements in the array if little-endian */
#ifdef WORDS_LITTLEENDIAN
   BlockByteSwap16(pValues, iNumItems);
#endif

   return iResult;
}
#endif

