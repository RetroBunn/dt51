/*C_HEADER_FILE****************************************************************
FILE			:	ReadItalianDict.c
DESC			:	Functions used to handle building a file system dictionary
					for Italian.
TABS			:	3
OWNER			:	Fonix
DATE CREATED	:	3 November 2005

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "BuildFileSystemDic.h"
#include "FileSystemDict.h"

/*FUNCTION_HEADER**********************
 * NAME:	;ParseItalianDictEntry
 * DESC: 	Parse a dictionary entry
 * IN:		sBuf - the raw data to parse
 * OUT:		parsed data is put in pDict
 * RETURN:	
 * NOTES:	
			Sample entry:	cementific
 *END_HEADER***************************/
void ParseItalianDictEntry(char *sBuf, DICT *pDict)
{

	char	*pc, *pc1, *pc2, c;

	if( (pc = strstr(sBuf, "//")) != NULL )			// Remove any comments from line
	{
		*pc = 0x00;
		if( sBuf[0] = 0x00 )
			return;
	}
	else if( (pc = strchr(sBuf, '\n')) != NULL )	// Remove any line feeds
		*pc = 0x00;

	// ******** Get Word ********
	for( pc = sBuf; *pc && (*pc == ' ' || *pc == '\t'); pc++ )		// Skip leading spaces
		;
	pc1 = pc;
	for( pc1=pc; *pc1 && *pc1 != ' ' && *pc1 != '\t' && *pc1 != '<'; pc1++ )	// find end of Word
		;
	c = *pc1;
	*pc1 = 0x00;
	pDict->sWord = strdup(pc);						// Copy word
	*pc1 = c;

	// ******** Get pronunciation *********
	if( c == '<' )
		pc = pc1;
	else
		pc = pc1+1;

	pDict->iBitFlags = 0;

	if( (pc = strchr(pc, '<')) != NULL )			// Find the opening angle bracket
	{
		pc++;										// Advance to the beginning of the pronunciation
		if( (pc2 = strchr(pc, '>')) != NULL )		// Find the closing angle bracket
		{
			*pc2 = 0x00;							// Null terminate the pronunciation
			pDict->sPron = strdup(pc);				// Copy the pronunciation
		}
	}
	else
	{
		pDict->iBitFlags = 1;
	}

	pDict->cHomo = 'N';

}


/*FUNCTION_HEADER**********************
 * NAME:	;ReadItalianDictionary
 * DESC: 	Load a dictionary from file
 * IN:		sInFile - dictionary filename
 * OUT:		pnEntries - number of entires in the dictionary
 * RETURN:	pointer to the dictionary on success, NULL on failure
 * NOTES:	
 *END_HEADER***************************/
DICT *ReadItalianDictionary(char *sInFile, int *pnEntries)
{
	char sBuf[512];
	int	 i,
		 nEntries=0;
	DICT *pDict;
	FILE *fp;

	// Open the text dictionary for read
	if( (fp = fopen(sInFile, "rt")) == NULL )
	{
		printf("Error: Can't open dictionary %s\n", sInFile);
		return NULL;
	}

	// Count the number of entries in the dictionary
	while( fgets(sBuf, 512, fp) )
	{
		if( sBuf[0] != ';' && sBuf[0] != '\n' && strlen(sBuf) > 0 &&
			sBuf[0] != '/' && sBuf[1] != '/' )
			nEntries++;
	}

	// Allocate memory to hold all entries
	if( (pDict = (DICT *)calloc(nEntries, sizeof(DICT))) == NULL )
	{
		printf("Error: Out of memory in LoadDictionary\n");
		return NULL;
	}

	// Reset back to the beginning of the file
	fseek(fp, 0L, SEEK_SET);

	// Read the dictionary
	for( i=0; i<nEntries && fgets(sBuf, 512, fp); )
	{
		if( sBuf[0] != ';' && sBuf[0] != '\n' && strlen(sBuf) > 0 &&
			sBuf[0] != '/' && sBuf[1] != '/' )
		{
			ParseItalianDictEntry(sBuf, &pDict[i++]);
		}
	}

	if( pnEntries )
		*pnEntries = nEntries;

	fclose(fp);
	return pDict;
}

/*FUNCTION_HEADER**********************
 * NAME:	;CatItalianDicts
 * DESC: 	Concatenate a list of dictionaries into a single dictionary
			and create a header file with the list of offsets to each.
 * IN:		sFileList - filename of dictionary list
			sOutFile - filename of output concatenated dictionary
			nDicts - number of dictionaries to be concatenated
 * OUT:		psDictNames - list of dictionary names
			puiOffsets - arrary of offsets for each dictionary
 * RETURN:	true on success, false on failure
 * NOTES:	
 *END_HEADER***************************/
bool CatItalianDicts(char *sFileList, char *sOutFile, int nDicts,
					char **psDictNames, unsigned int *puiOffsets)
{
	char sInDict[_MAX_PATH],
		 sHeader[_MAX_PATH],
		 sOffsets[_MAX_PATH],
		 sBuf[128],
		 sEnum[128],
		 *pc;
	int	 i, nRead;
	unsigned int offset=0;
	FILE *fp, *fpIn, *fpOut, *fpHeader, *fpOffsets;

	if( sFileList == NULL || sOutFile == NULL )
		return false;

	if( (fp = fopen(sFileList, "rt")) == NULL )
		return false;

	if( (fpOut = fopen(sOutFile, "wb")) == NULL )
	{
		fclose(fp);
		printf("Error: Couldn't open output file %s\n", sOutFile);
		return false;
	}

	// Create the filename for the header file where the offsets will be stored
	strcpy(sHeader, sOutFile);
	if( (pc = strrchr(sHeader, '\\')) != NULL )
	{
		*pc = 0x00;
	}
	else
	{
		strcpy(sHeader, ".");
	}
	strcat(sHeader, "\\ItalianFileSystemDict");
	strcpy(sOffsets, sHeader);
	strcat(sHeader, ".h");
	strcat(sOffsets, ".c");

	if( (fpHeader = fopen(sHeader, "wt")) == NULL )
	{
		fclose(fp);
		fclose(fpOut);
		printf("Error: Couldn't open header file %s\n", sHeader);
		return false;
	}

	if( (fpOffsets = fopen(sOffsets, "wt")) == NULL )
	{
		fclose(fp);
		fclose(fpOut);
		fclose(fpHeader);
		printf("Error: Couldn't open .c file %s\n", sOffsets);
	}

	// Write out the file header
	fprintf(fpHeader, 
		"/*H_HEADER_FILE***************************************************************\n"
		"FILE			: ItalianFileSystemDict.h\n"
		"DESC			: \n"
		"TABS			: 4\n"
		"OWNER			: Fonix\n"
		"DATE CREATED	: \n\n"
		"(C) Copyright 2005 All rights reserved.\n"
		"This is an unpublished work, and is confidential and proprietary: \n"
		"technology and information of fonix corporation.  No part of this\n"
		"code may be reproduced, used or disclosed without written consent of\n" 
		"fonix corporation in each and every instance.\n"
		"*END_HEADER******************************************************************/\n"
		"#ifndef	ITALIANFILESYSTEMDICT_H\n"
		"#define	ITALIANFILESYSTEMDICT_H\n\n");

	// Write the dictionary enums used to access the table of offsets
	fprintf(fpHeader, "\t// The following enum provides a method for accessing the uiItDictOffsets array.\n");
	fprintf(fpHeader, "\ttypedef enum {\n");
	for(i=0; fgets(sInDict, _MAX_PATH, fp); )
	{
		if( *sInDict == 0x00 || *sInDict == ';' )			// Make sure we have a filename
			continue;

		if( (pc = strchr(sInDict, '\n')) != NULL )			// Strip any \n ending characters
			*pc = 0x00;

		if( (pc = strrchr(sInDict, '.')) != NULL )			// Create the dictionary filename <path>\<filename>.dic
		{
			*pc = 0x00;
		}
		if( (pc = strrchr(sInDict, '\\')) != NULL )			// Copy just the filename to sEnum
		{
			pc++;
		}
		else
		{
			pc = sInDict;
		}
		strcpy(sEnum, pc);

		for( pc=sEnum; pc && *pc; pc++ )
			*pc = toupper(*pc);

		if( i == 0 )
			fprintf(fpHeader, "\t\t%s = 0,\n", sEnum);				// Write out dictionary name enums (1st)
		else
			fprintf(fpHeader, "\t\t%s,\n", sEnum);					// (all others)

		psDictNames[i] = strdup(sEnum);

		i++;
	}
	fprintf(fpHeader, "\t\tNUM_IT_DICTS\n\t}IT_FS_DICTS;\n");
	fprintf(fpHeader, "\n\n#endif\n");
	fclose(fpHeader);

	fprintf(fpOffsets, 
		"/*C_HEADER_FILE****************************************************************\n"
		"FILE			:	ItalianFileSystemDict.c\n"
		"DESC			:	This file includes an array of offsets to the Italian File System dictionary.\n"
		"					See ItalianFileSystem.h for the table name enumeration.\n"
		"TABS			:	4\n"
		"OWNER			:	Fonix\n"
		"DATE CREATED	:	\n\n"
		"(C) Copyright 2005 All rights reserved.\n"
		"This is an unpublished work, and is confidential and proprietary: \n"
		"technology and information of fonix corporation.  No part of this\n"
		"code may be reproduced, used or disclosed without written consent of\n" 
		"fonix corporation in each and every instance.\n\n"
		"*END_HEADER*******************************************************************/\n"
		"#include \"ItalianFileSystemDict.h\"\n\n");



	// Write out the offsets array
	fprintf(fpOffsets, "\tconst unsigned int uiItDictOffsets[] = {\n");

	// Go back to the beginning of the list file
	fseek(fp, 0, SEEK_SET);
	
	for(i=0; fgets(sInDict, _MAX_PATH, fp); )
	{
		if( *sInDict == 0x00 || *sInDict == ';' )			// Make sure we have a filename
			continue;

		if( (pc = strchr(sInDict, '\n')) != NULL )			// Strip any \n ending characters
			*pc = 0x00;

		if( (pc = strrchr(sInDict, '.')) != NULL )			// Create the dictionary filename <path>\<filename>.dic
		{
			*pc = 0x00;
			strcat(sInDict, ".dic");
		}

		if( (fpIn = fopen(sInDict, "rb")) == NULL )
		{
			printf("Error: Couldn't open %s\n", sInDict);
			continue;
		}

		if( i == nDicts-1 )
			fprintf(fpOffsets, "\t\t%d\n\t};\n", offset);
		else
			fprintf(fpOffsets, "\t\t%d,\n", offset);

		puiOffsets[i] = offset;

		i++;
	
		// Concatenate dictionary
		while( (nRead = fread(sBuf, sizeof(char), 128, fpIn)) > 0 )
		{
			fwrite(sBuf, sizeof(char), nRead, fpOut);
		}
		
		fclose(fpIn);

		// Get the offset to the next dictionary
		offset = ftell(fpOut);

	}

	fclose(fp);
	fclose(fpOut);
	return true;

}

/*FUNCTION_HEADER**********************
 * NAME:	;FindDictOffset
 * DESC: 	Find the index to the dictionary offset array
 * IN:		sDict - a dictionary name
			psDictNames - - list of dictionary names used to find the index into puiOffsets
			nDicts - number of concatentated dictionaries
 * OUT:		none
 * RETURN:	index to the dictionary offset array on success, nDicts on failure
 * NOTES:	
 *END_HEADER***************************/
static unsigned int FindDictOffset(char *sDict, char **psDictNames, int nDicts)
{
	char *pc;
	int i;

	for(pc=sDict; pc && *pc; pc++)
	{
		*pc = toupper(*pc);
	}

	for(i=0; i<nDicts; i++)
	{
		if( strcmp(psDictNames[i], sDict) == 0 )
			return i;
	}

	return nDicts;
}

/*FUNCTION_HEADER**********************
 * NAME:	;ItTestFileSystemDict
 * DESC: 	Test a filesystem dictionary
 * IN:		sFile - dictionary filename
			psDictNames - list of dictionary names used to find the index into puiOffsets
			puiOffsets - array of offsets into the filesystem dictionary for each of the concatentated dictionaries
			nDicts - number of concatentated dictionaries 
 * OUT:		none
 * RETURN:	none
 * NOTES:	
 *END_HEADER***************************/
void ItTestFileSystemDict(char *sFile, char **psDictNames, unsigned int *puiOffsets, int nDicts)
{
	unsigned char 
		 sBuf[MAX_SYMBOLS];
	char sPron[MAX_SYMBOLS],
		 sHomo[MAX_SYMBOLS],
		 sWord[MAX_SYMBOLS];
	char sDict[_MAX_PATH];
	int	 iLtrsUsed, 
		 iOffsetIndex;
	unsigned int 
		 uiBitFlag, 
		 uiHomoFlag, 
		 uiPronOffset,
		 uiSegOffset,
		 uiOffset;
	FILE *fp;

	if( (fp = fopen(sFile, "rb")) == NULL )
		return;

	printf("\nEnter the name of a dictionary to test: ");
	while( gets(sDict) )
	{
		if( !sDict[0] )
			break;

		if( (iOffsetIndex = FindDictOffset(sDict, psDictNames, nDicts)) == nDicts )
		{
			printf("Warning: Unknown dictionary %s\n", sDict);
			continue;
		}

		uiOffset = puiOffsets[iOffsetIndex];
		printf("\nEnter a word to test it: ");
		while( gets(sBuf) )		// Test the newly built LTree
		{
			if( !sBuf[0] )		// get out if nothing was entered
				break;
				
			*sPron = 0x00;
			uiBitFlag = 0;
			*sHomo = 0x00;
			uiHomoFlag = 0;
			if( FindWordWithOffset(sBuf, sPron, &uiBitFlag, sHomo, &uiHomoFlag, fp, uiOffset) )
			{
				printf("Found: %s, Pron: %s, Bit Flag: 0x%08x\n", sBuf, sPron, uiBitFlag);

				if( uiBitFlag & FC_M_HOMOGRAPH )
				{
					printf("\tHomograph: %s, Bit Flag: 0x%08x\n", sHomo, uiHomoFlag);
				}
			}
			else
				printf("%s not found\n", sBuf);

			printf("\n---------------------\nFinding by parts.\n---------------------\n");

			iLtrsUsed = 0;
			uiSegOffset = 0;
			while( FindWordSegsInFileSystemDict(sBuf, sPron, &uiPronOffset, &uiBitFlag, 
				sHomo, &uiHomoFlag, &iLtrsUsed, &uiSegOffset, fp, uiOffset) > 0 )
			{
				strncpy(sWord, sBuf, iLtrsUsed);
				sWord[iLtrsUsed] = 0x00;
				printf("Found %s, Data %s\n", sWord, sPron);
			}


			printf("\n=====================\nWord: ");
		}
	
		printf("\nEnter the name of a dictionary to test: ");

	}
}


/*FUNCTION_HEADER**********************
 * NAME:	;BuildItalianCompositeDict
 * DESC: 	Build a filesystem dictionary for each of a list of Dictionaries
			and then concatenate them all together and output a list of offsets
			to each individual dictionary section.
 * IN:		sFileList - file containing a list of dictionary filenames
			sOutFile - filename for the concatenated output dictionary
			bTestDict - flag to test dictionaries along the way
			bLowerCase - flag to create the letter tree with lower case letters only
			bBigEndian - flag to write out all multi-byte items in big-endian format
 * OUT:		
 * RETURN:	true on success, false on failure
 * NOTES:	
 *END_HEADER***************************/
bool BuildItalianCompositeDict(char *sFileList, char *sOutFile, 
							  bool bTestDict, bool bLowerCase, bool bBigEndian)
{
	char sInDict[_MAX_PATH],
		 sTmpDict[_MAX_PATH],
		 *pc;
	char **psDictNames;
	unsigned int
		 *puiDictOffsets;
	int	 i,
		 nEntries,
		 nDicts=0;
	FILE *fp;
	DICT *pDict;
	BRANCH *pLTree;
	
	if( (fp = fopen(sFileList, "rt")) == NULL )
		return false;

	while( fgets(sInDict, _MAX_PATH, fp) )					// Iterate through all dictionaries in the list
	{
		if( *sInDict == 0x00 || *sInDict == ';' )			// Make sure we have a filename
			continue;

		if( (pc = strchr(sInDict, '\n')) != NULL )			// Strip any \n ending characters
			*pc = 0x00;

		printf("Loading %s\n", sInDict);
		if( (pDict = ReadItalianDictionary(sInDict, &nEntries)) != NULL )			// Build the binary searchable/sortable dictionary
		{
			if( (pLTree = BuildLetterTree(pDict, nEntries, bLowerCase)) != NULL )	// Convert sorted list into a letter tree dictionary
			{
				if( sOutFile )
				{
					printf("\n***************************************\nBuilding File System based dictionary.\n");

					strcpy(sTmpDict, sInDict);
					if( (pc = strrchr(sTmpDict, '.')) != NULL )						// Create a temporary filename <path>\<filename>.dic
					{
						*pc = 0x00;
						strcat(sTmpDict, ".dic");
					}
					BuildFileSystemDict(sTmpDict, pLTree, bBigEndian);				// Save as File System dictionary
					nDicts++;
				}
				FreeLTree(pLTree);
			}
			FreeDictionary(pDict, nEntries);
		}
	}	// while more files in the list

	psDictNames = (char **)calloc(nDicts, sizeof(char *));
	puiDictOffsets = (unsigned int *)calloc(nDicts, sizeof(int));

	// Now concatenate dictionaries and store the offsets to each in the header file
	CatItalianDicts(sFileList, sOutFile, nDicts, psDictNames, puiDictOffsets);

	if( bTestDict )
		ItTestFileSystemDict(sOutFile, psDictNames, puiDictOffsets, nDicts);

	free(puiDictOffsets);
	for(i=0; i<nDicts; i++)
		free(psDictNames[i]);
	free(psDictNames);
	fclose(fp);

	return true;
}