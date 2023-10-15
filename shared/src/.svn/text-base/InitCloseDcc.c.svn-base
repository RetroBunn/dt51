/*C_HEADER_FILE****************************************************************
FILE        :  dccread.c
DESC        :  Functions for reading binary dictionary files.
OWNER       :  You want it, you got it.
DATE CREATED:  2001

(C) Copyright 2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/21/05 3:23p $
  $Revision: 53 $

*END_HEADER*******************************************************************/
#include "port.h"
#include "FnxPlatform.h"
#include "DTFnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxFiles.h"
#include "dccread.h"
#include "FnxByteOrderIO.h"
#include "phonetic.h"

#include "ls_def.h"
#include "ls_rule.h"

/*FUNCTION_HEADER**********************
 * NAME:   ;ReadAlphaTripleTable
 * DESC:   Read a list of alpha triples and their offsets.
 * IN:     fp - File to read from.
           pDccInfo - Structure into which to read the alpha triples.
 * OUT:    Strings and offsets are read into pDccInfo->pAlphaTriple and pDccInfo->numAlphaTriples
 * RETURN: 0 on success, -1 on error.
 * NOTES:  Format of this chunk:
             <iNumTriples> - 4-byte NBO integer.
             for each triple:
               <sTriple> - 3-byte array of characters
               <lOffset> - 4-byte NBO integer
 *END_HEADER***************************/
SDWORD ReadAlphaTripleTable(FILE *fp, DccPtr pDccInfo)
{
   SDWORD i;
   if (ReadInt32NBO(fp, (UDWORD*)&pDccInfo->numAlphaTriples)!=0)
      return -1;
   pDccInfo->pAlphaTriple = (AlphaTriplePtr)FNX_CALLOC(pDccInfo->numAlphaTriples, sizeof(AlphaTriple));
   for (i=0; i<pDccInfo->numAlphaTriples; i++)
   {
      if (FNX_FREAD(pDccInfo->pAlphaTriple[i].sAlphaTriple, 1, 3, fp) != 3)
         return -1;
      if (ReadInt32NBO(fp, (UDWORD*)&pDccInfo->pAlphaTriple[i].ulOffset)!=0)
         return -1;
   }
   return 0;
}  /* ReadAlphaTripleTable */


/*FUNCTION_HEADER**********************
 * NAME:   ;initDccFileFP
 * DESC:   Open a .dcc file, read its header, and allocate search tables.
 * IN:     sFilename - Name of a .dcc file to open.
 * OUT:    ppDccInfo - Address in which to return a pointer to a new DCC info structure.
 * RETURN: Length of longest pronunciation (or 0 on error).
 * NOTES:  See the header to WriteDCC() for the file format.
 *END_HEADER***************************/
initDccFileFP(FILE *fp, DccPtr *ppDccInfo)
{
   DccPtr pDccInfo;
   char   sNumString[ 32 ];
   UBYTE c; /* Character used for reading bytes */
   int    iVersion;     /* Version number read from text header */
   SDWORD iDccVersion;  /* Version number read from binary dictionary section */
   UDWORD ulTrailerPos;
   int    iError=0;

//  Removed the fscanf function for cross platform compatibility. mem file code does not support the scanf functions.
   int i = 0;
   int	version_length = 5;

   /* Allocate a DCC information structure */
   *ppDccInfo = NULL;
   pDccInfo = (DccPtr) FNX_CALLOC (SIZE_DCCSTRUCT, 1);
   if (pDccInfo==NULL)
      goto InitDccError;
   pDccInfo->pDccFile = fp;

   /* Read the first four bytes of the file, which should contain "DCC" and a 0 */
   FNX_FREAD( sNumString, 4, 1, pDccInfo->pDccFile );
   if( memcmp( sNumString, "DCC", 3 )!=0 )
      goto InitDccError;

   /* The next four bytes contain either the bytes '6e 00 00 00', if it is an old "version 110"
      file, or "Vers" if this is a line containing "Version xxxx\n" */
   FNX_FREAD( sNumString, 4, 1, pDccInfo->pDccFile );

   if (FNX_STRNCMP(sNumString,"Vers",4)!=0)
   {
      Message(NULL,"Unknown DCC format: Not version 110 and doesn't have version number string.\n");
      goto InitDccError;
   }

   /* Read the rest of the word "Version", i.e., "ion" */
   if (FNX_FREAD(sNumString, 1, 3, pDccInfo->pDccFile)!=3)
      goto InitDccError;

   /* Now read the actual version number */
//  Removed the fscanf function for cross platform compatibility. mem file code does not support the scanf functions.
   if( !FNX_FGETS(sNumString, version_length, fp) )
	  goto InitDccError;
   for (i = 0; i < version_length; i++)
   {
	  if (sNumString[i] != ' ')
	     break;
   }
   iVersion = atoi(&sNumString[i]);

   /* Version 112 introduced "stage1" definitions of vowels, consonants, etc., for the language */
   if (iVersion != 111 && iVersion != 112)
   {
      Message(NULL, "Unsupported DCC version number: %d (code out of date?)\n", iVersion);
      goto InitDccError;
   }

   /* Skip lines in the header until "END_OF_HEADER" is found. */
   while (FNX_FGETS(sNumString, 32, fp))
   {
      if (FNX_STRNCMP(sNumString,"END_OF_HEADER",FNX_STRLEN("END_OF_HEADER"))==0)
         break;
   }

   /* Skip over the ctrl-z after "END_OF_HEADER\n" */
   FNX_FREAD(&c, 1, 1, fp);
   if (c!=26)
   {
      Message(NULL,"Error reading header of dictionary file\n");
      goto InitDccError;
   }

   /***** Read Graph2Phon rules, if any *****/
   /* Read a byte that serves as a flag for whether there are any graph2phon rules in the file */
   iError = (FNX_FREAD(&c, 1, 1, fp)!=1);
   if (c)
   {
      /* There are Graph2Phon rules in the file, so read them */
      pDccInfo->pGraph2Phon = LoadBinaryRules(fp);
      if (pDccInfo->pGraph2Phon == NULL)
      {
         Message(NULL,"Error reading rules from dictionary.\n");
         goto InitDccError;
      }
   }

   /* Read the number of words in the dictionary (0=>none, i.e., only graph2phon rules) */
   iError |= ReadInt32NBO(fp, (UDWORD*)&pDccInfo->numWords);
   if (pDccInfo->numWords > 0)
   {
      iError |= ReadInt32NBO(fp, (UDWORD*)&iDccVersion);
      //if (iDccVersion!=111)
      //{
      //  /* Do what you need to with other versions in here... */
      //
      //  /* ...otherwise, we will assume that the vocab portion isn't affected by the changes. */
      //}

      iError |= ReadInt32NBO(fp, (UDWORD*)&pDccInfo->largestWord);
      iError |= ReadInt32NBO(fp, (UDWORD*)&pDccInfo->largestPhonemeString);
      iError |= ReadAlphaTripleTable(fp, pDccInfo);
      iError |= ReadInt32NBO(fp, (UDWORD*)&pDccInfo->ulWordEndOffset);
      iError |= ReadInt32NBO(fp, (UDWORD*)&ulTrailerPos);

      if (iError)
         goto InitDccError;

      /* Read pronunciation Huffman table */
      pDccInfo->pPhoneHuffman = ReadHuffman(fp);
      if (pDccInfo->pPhoneHuffman==NULL)
         goto InitDccError;

      /* Read flag and, if true, spelling Huffman */
      iError |= (FNX_FREAD(&c, 1, 1, fp)!=1);
      if (c)
      {
         pDccInfo->pSpellingHuffman = ReadHuffman(fp);
         iError |= (pDccInfo->pSpellingHuffman==NULL);
      }
      if (iError)
         goto InitDccError;

      /* Make sure our trailer is in the file where it is supposed to be */
      iError |= FNX_FSEEK(fp, ulTrailerPos, SEEK_SET);
      iError |= (FNX_FREAD(sNumString,3, 1, fp)!=1);
      if (FNX_STRNCMP(sNumString,"END",3)!=0)
      {
         Message(NULL,"Error: Dictionary file did not have an 'END' where it was supposed to\n");
         goto InitDccError;
      }
   }  /* if there are words in the file */


   if (iError)
      goto InitDccError;

   *ppDccInfo = pDccInfo;
   return pDccInfo->largestPhonemeString; //return the longest the transcription possibly could be

InitDccError:
   if (pDccInfo)
      closeDccFile(pDccInfo);
   *ppDccInfo = NULL;
   return 0; /* => error */
}  /* initDccFile */

/*FUNCTION_HEADER**********************
 * NAME:   ;initDccFile
 * DESC:   Open a .dcc file, read its header, and allocate search tables.
 * IN:     sFilename - Name of a .dcc file to open.
 * OUT:    ppDccInfo - Address in which to return a pointer to a new DCC info structure.
 * RETURN: Length of longest pronunciation (or 0 on error).
 * NOTES:  See the header to WriteDCC() for the file format.
 *END_HEADER***************************/
int initDccFile(char *sFilename, DccPtr *ppDccInfo)
{
   FILE *fp;
   fp = FNXA_FOPEN(sFilename,"rb");
   if (fp!=NULL)
      return initDccFileFP(fp, ppDccInfo);
   else return 0; // error
}

/*FUNCTION_HEADER**********************
 * NAME:   ;initDccFileW
 * DESC:   Wide-character filename version of initDccFile
 * IN:     wsFilename - Wide character string containing the name of a .dcc file to open.
 * OUT:    ppDccInfo - Address in which to return a pointer to a new DCC info structure.
 * RETURN: Length of longest pronunciation (or 0 on error).
 * NOTES:  See the header to WriteDCC() for the file format.
 *END_HEADER***************************/
int initDccFileW(wchar_t *wsFilename, DccPtr *ppDccInfo)
{
   FILE *fp;
   fp = FNXW_FOPEN(wsFilename,L"rb");
   if (fp!=NULL)
      return initDccFileFP(fp, ppDccInfo);
   else return 0; // error
}


/*FUNCTION_HEADER**********************
 * NAME:   ;closeDccFile
 * DESC:   Close a .dcc file and free a DCC structure.
 * IN:     pDccInfo - Structure containing dictionary information.
 * OUT:    pDccInfo->pDccFile is closed, and pDccInfo is freed up.
 * RETURN: 0
 * NOTES:  
 *END_HEADER***************************/
int closeDccFile(DccPtr pDccInfo)
{
   if( pDccInfo )
   {
      if( pDccInfo->pDccFile )
         FNX_FCLOSE(pDccInfo->pDccFile);

      if( pDccInfo->pPhonemes )
         FNX_FREE(pDccInfo->pPhonemes);

      if( pDccInfo->pAlphaTriple )
         FNX_FREE(pDccInfo->pAlphaTriple);
      
      if (pDccInfo->pGraph2Phon)
         FreeRules(pDccInfo->pGraph2Phon);
      
      if (pDccInfo->pPhoneHuffman)
         FreeHuffman(pDccInfo->pPhoneHuffman);
      
      if (pDccInfo->pSpellingHuffman)
         FreeHuffman(pDccInfo->pSpellingHuffman);

      FNX_FREE(pDccInfo);
   }

   return 0;
}  /* closeDccFile */

int Initialize(LPVOID pVoid)
{
#ifdef ARM7
	LPTTS_HANDLE_T phTTS = (LPTTS_HANDLE_T)pVoid;

	PLTS_T pLts = phTTS->pLTSThreadData;
	if( pLts )
		return initDccFile(phTTS->dict_path, &pLts->pDccInfo);
	else
		return -1;
#else
	PLTS_T pLts = (PLTS_T)pVoid;
	if( pLts )
		return initDccFile("korean.pdc", &pLts->pDccInfo);
	else
		return -1;
#endif //ARM7

}

int Terminate(LPVOID pVoid)
{
	PLTS_T pLts = (PLTS_T)pVoid;
	if( pLts && pLts->pDccInfo )
	{
		closeDccFile(pLts->pDccInfo);
		pLts->pDccInfo = NULL;
	}

	return 0;
}
