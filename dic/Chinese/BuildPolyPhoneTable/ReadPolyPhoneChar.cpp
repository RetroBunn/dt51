// Read a Frequncy file in which each line has a format:
// (number) (one or more chars in unicode) (pinyin for each of chars) 
// Example:
//	15423 ? wei4
//	14680 ?? xian4zai4
// Will output a polyphone tables.
// Usage: > ReadPolyPhoneChar CharFreq.txt PolyPhoneTable.txt PolyPhoneLog.txt

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define WRITE_ONLY_VALID_POLYPHONE

#define BUF_SIZE					2048
#define PINYIN_SIZE					10		// No pinyin will be more than this size. 
//#define TONE_SIZE					2		// Tone is a number in [1, 5]
#define MAX_NUM_CHARS_PER_WORD		20	
#define NUM_BYTES_IN_UNICODE		2
#define MAX_NUM_DIFF_PRONOUNS		10		// No charactes has more than 10 diff pronunciations.
#define TRUE						1
#define FALSE						0

typedef int		BOOL;
typedef char	OneCharPinyinStrType[PINYIN_SIZE];
typedef char	OneWordUnicodeStrType[2 * MAX_NUM_CHARS_PER_WORD];	 

		
typedef struct _Word	// A list of words for a given pronunciation of a given polyphone char.
{
	OneWordUnicodeStrType	sUnicodeStr;		// How to write it in gb.
	struct _Word			*pNext;				// Next word.
} Word, *WordPtr;


typedef struct _PolyPhoneChar	// A list of polyphone chars.
{
	char					sUnicodeStr[NUM_BYTES_IN_UNICODE + 1];	// Unicode has two byets. It specify how to write char.
	int						iNumPronouns;		// Number of pronounciations for this polyphone char.
	OneCharPinyinStrType	psPinyinStr[MAX_NUM_DIFF_PRONOUNS];	// psPinyinStr[i] is the [i]th string such as "gao1" (including tone).
	WordPtr					ppWordList[MAX_NUM_DIFF_PRONOUNS];	// ppWordList[i] is the [i]th word list for pronoun[i].
	int						iNumWordsInList[MAX_NUM_DIFF_PRONOUNS];	 
	int						iDefaultPronounIndex;				// If no word is found in the list, then use default (most frequent) pronoun.
	// struct _PolyPhoneChar	*pNext;     // Write for each one, so no need to link a list.
} PolyPhoneChar, *PolyPhoneCharPtr;



void FreePolyPhoneChar(PolyPhoneCharPtr pPolyPhoneChar)
{
	int iPronoun;
	WordPtr pCur, pNext;

	for(iPronoun = 0; iPronoun < pPolyPhoneChar->iNumPronouns; iPronoun++)
	{
		pCur = pPolyPhoneChar->ppWordList[iPronoun];
		while(pCur)
		{
			pNext = pCur->pNext;
		    free(pCur);
			pCur = pNext;
		}
	}
	free(pPolyPhoneChar);
}


#ifdef WRITE_ONLY_VALID_POLYPHONE
BOOL WriteOnePolyPhoneChar(FILE *fpPolyPhoneTable, PolyPhoneCharPtr pPolyPhoneChar, int iNumPolyPhoneChars)
{
	int iPronoun, iChar, iNumValidPinyin;
	int iNumTotalWords;
	WordPtr pCur;

	iNumTotalWords = 0;
	iNumValidPinyin = 0;
	for(iPronoun = 0; iPronoun < pPolyPhoneChar->iNumPronouns; iPronoun++)
	{
		if(pPolyPhoneChar->iNumWordsInList[iPronoun] > 0)
			iNumValidPinyin++;

		iNumTotalWords += pPolyPhoneChar->iNumWordsInList[iPronoun];
	}

	if(iNumValidPinyin < 2)
		return FALSE;

	fprintf(fpPolyPhoneTable, "[%d]. %c%c %d ", iNumPolyPhoneChars, pPolyPhoneChar->sUnicodeStr[0], 
													pPolyPhoneChar->sUnicodeStr[1], iNumValidPinyin);
	for(iPronoun = 0; iPronoun < pPolyPhoneChar->iNumPronouns; iPronoun++)
	{
		if(pPolyPhoneChar->iNumWordsInList[iPronoun] > 0)
		{
			fprintf(fpPolyPhoneTable, "%s ", pPolyPhoneChar->psPinyinStr[iPronoun]);
		}
	}
	fprintf(fpPolyPhoneTable, "%d\n", iNumTotalWords);

	// Print for each polyphone
	for(iPronoun = 0; iPronoun < pPolyPhoneChar->iNumPronouns; iPronoun++)
	{

		// Only print those with at least one example word.
		if(pPolyPhoneChar->iNumWordsInList[iPronoun] == 0)
			continue;

		fprintf(fpPolyPhoneTable, "\t%s %d\n", pPolyPhoneChar->psPinyinStr[iPronoun], 
												pPolyPhoneChar->iNumWordsInList[iPronoun]);
		
		pCur = pPolyPhoneChar->ppWordList[iPronoun];
		while(pCur)
		{
			fprintf(fpPolyPhoneTable, "\t\t");
			for(iChar = 0; iChar < (int) strlen(pCur->sUnicodeStr); iChar++)
			{
				fprintf(fpPolyPhoneTable, "%c", pCur->sUnicodeStr[iChar]);
			}
			fprintf(fpPolyPhoneTable, "\n");
			pCur = pCur->pNext;
		}
	}
	return TRUE;
}
#else
void WriteOnePolyPhoneChar(FILE *fpPolyPhoneTable, PolyPhoneCharPtr pPolyPhoneChar, int iNumPolyPhoneChars)
{
	int iPronoun, iChar;
	int iNumTotalWords;
	WordPtr pCur;

	fprintf(fpPolyPhoneTable, "[%d]. %c%c %d ", iNumPolyPhoneChars, pPolyPhoneChar->sUnicodeStr[0], 
										  pPolyPhoneChar->sUnicodeStr[1], pPolyPhoneChar->iNumPronouns);
	iNumTotalWords = 0;
	for(iPronoun = 0; iPronoun < pPolyPhoneChar->iNumPronouns; iPronoun++)
	{
		// Maybe only need to print those polyphone with at least one word.
		fprintf(fpPolyPhoneTable, "%s ", pPolyPhoneChar->psPinyinStr[iPronoun]);
		iNumTotalWords += pPolyPhoneChar->iNumWordsInList[iPronoun];
	}
	fprintf(fpPolyPhoneTable, "%d\n", iNumTotalWords);

	// Print for each polyphone
	for(iPronoun = 0; iPronoun < pPolyPhoneChar->iNumPronouns; iPronoun++)
	{
		fprintf(fpPolyPhoneTable, "\t%s %d\n", pPolyPhoneChar->psPinyinStr[iPronoun], 
												pPolyPhoneChar->iNumWordsInList[iPronoun]);
		
		pCur = pPolyPhoneChar->ppWordList[iPronoun];
		while(pCur)
		{
			fprintf(fpPolyPhoneTable, "\t\t");
			for(iChar = 0; iChar < (int) strlen(pCur->sUnicodeStr); iChar++)
			{
				fprintf(fpPolyPhoneTable, "%c", pCur->sUnicodeStr[iChar]);
			}
			fprintf(fpPolyPhoneTable, "\n");
			pCur = pCur->pNext;
		}
	}
}
#endif
				

// Search whole file and find all words (at least two chars) that contains the exact
// target char and pinyin (Return NULL if not able to find any word).
WordPtr GetWordsForOnePronoun(char *sFreqFileName, char *sUnicodeStr, char *sPinyinStr, int *piNumWords)
{
	FILE *fpFreqFile;
	char sCurFreqNum[BUF_SIZE], sCurUnicodeStr[BUF_SIZE], sCurPinyinStr[BUF_SIZE], sCurLine[BUF_SIZE];
	WordPtr pWordListHead, pPrev, pNew;
	int iNumWords, iNumLines, iUnicodeStrLen, iNumChars, iPinyinStrLen, iCurPinyinStrIndex, iChar; 
	int iCurOneCharPinyinStrIndex;
	char sCurOneCharUnicodeStr[NUM_BYTES_IN_UNICODE + 1];
	OneWordUnicodeStrType sCurOneCharPinyinStr;
	
	if((fpFreqFile = fopen(sFreqFileName, "rt")) == NULL)
	{
		printf("Error in open file: %s\n", sFreqFileName);
	    exit(-1);
	}

	iNumWords = 0;
	iNumLines = 0;
	pWordListHead = pPrev = pNew = NULL;
	// Read a valid line in (input freq file) with the format "(freq)  (char1)(char2)... (pinyin1)(pinyin2)...".
	while(fgets(sCurLine, BUF_SIZE, fpFreqFile) && strlen(sCurLine) > 0 && sCurLine[0] != '\n') 
	{
		iNumLines++;

		// Read data for one line
		if (sscanf(sCurLine, "%s %s %s", sCurFreqNum, sCurUnicodeStr, sCurPinyinStr) != 3)
		{
			printf( "Error: sscanf() not return 3 in line %d in file '%s'.\n", iNumLines, sFreqFileName);
			exit(-1);
		}

		iUnicodeStrLen = strlen(sCurUnicodeStr);
		// There should be even number of byets (since each unicode has 2 bytes).
		if(iUnicodeStrLen%2 != 0)
		{
			//printf("Error on [%d]th line:\n %s iUnicodeStrLen is not an even number.\n\n", iNumLines, sCurLine);
			continue;
		}
		else
			iNumChars = iUnicodeStrLen / 2;

		// Only consider word with multiple chars.
		if(iNumChars <=	1)
			continue;

		iPinyinStrLen = strlen(sCurPinyinStr);
		iCurPinyinStrIndex = 0;
		for(iChar = 0; iChar < iNumChars; iChar++)
		{
			sCurOneCharUnicodeStr[0] = sCurUnicodeStr[iChar * 2];
			sCurOneCharUnicodeStr[1] = sCurUnicodeStr[iChar * 2 + 1];
			sCurOneCharUnicodeStr[2] = '\0';

			// Assume that the first one is not a number for tone.
			iCurOneCharPinyinStrIndex = 0;
			sCurOneCharPinyinStr[iCurOneCharPinyinStrIndex++] = sCurPinyinStr[iCurPinyinStrIndex++];
			if(iCurPinyinStrIndex >= iPinyinStrLen)
				goto next;
			while(sCurPinyinStr[iCurPinyinStrIndex] < '1' || sCurPinyinStr[iCurPinyinStrIndex] > '5')
			{
				sCurOneCharPinyinStr[iCurOneCharPinyinStrIndex++] = sCurPinyinStr[iCurPinyinStrIndex++];
				if(iCurPinyinStrIndex >= iPinyinStrLen)
					goto next;
			}
			// Found a number for tone.
			sCurOneCharPinyinStr[iCurOneCharPinyinStrIndex++] = sCurPinyinStr[iCurPinyinStrIndex++];
			sCurOneCharPinyinStr[iCurOneCharPinyinStrIndex] = '\0';
			
			// Compare both Unicode str and pinyin string
			if(!strcmp(sCurOneCharUnicodeStr, sUnicodeStr) && !strcmp(sCurOneCharPinyinStr, sPinyinStr))
			{
				// found a word.
				if((pNew = (WordPtr) malloc(sizeof(*pNew))) == NULL)
				{
					printf("Error: no more memmory.\n");
					exit(-1);
				}
				strcpy(pNew->sUnicodeStr, sCurUnicodeStr);
				pNew->pNext = NULL;

				if(pPrev == NULL)	// If it is the first on the link list.
					pWordListHead = pPrev = pNew;
				else
				{
					pPrev->pNext = pNew;
					pPrev = pNew;
				}
				iNumWords++;
				goto next;
			}
		}
next:
		;
	}

	fclose(fpFreqFile);
	*piNumWords = iNumWords;
	return pWordListHead;
}	


int main(int argc, char* argv[])
{
	char sFreqFileName[BUF_SIZE];
	FILE *fpFreqFile;				// Input freq file.
	FILE *fpPolyPhoneTable;			// Output file with polyphone char table .
	FILE *fpPolyPhoneTableLog;		// Output log file.
	int iNumLines, iNumPolyPhoneChars, iPronoun, iNumWords;
    char sLastFreqNum[BUF_SIZE], sLastUnicodeStr[BUF_SIZE], sLastPinyinStr[BUF_SIZE];
	char sCurFreqNum[BUF_SIZE], sCurUnicodeStr[BUF_SIZE], sCurPinyinStr[BUF_SIZE], sCurLine[BUF_SIZE];
	PolyPhoneChar *pPolyPhoneChar = NULL;
#ifdef WRITE_ONLY_VALID_POLYPHONE
	BOOL iValidPolyPhone;
#endif

    if(argc != 4) 
	{ 
		printf(" Usage: > %s (input Char Freq) (Output PolyPhoneChar Table) (Output PolyPhoneChar Table Log).\n", argv[0]);
        exit(1);
	}

	strcpy(sFreqFileName, argv[1]);

	// fpFreqForChar is for finding polyphone chars.
	if((fpFreqFile = fopen(argv[1], "rt")) == NULL)
	{
		printf("Error in open file: %s\n", argv[1]);
	    exit(1);
	}

	if((fpPolyPhoneTable = fopen(argv[2], "wt")) == NULL)
	{
		printf("Error in open file: %s\n", argv[2]);
	    exit(1);
	}

	if((fpPolyPhoneTableLog = fopen(argv[3], "wt")) == NULL)
	{
		printf("Error in open file: %s\n", argv[3]);
	    exit(1);
	}

	iNumLines = 0;			    // Number of lines in input frequency file.
	iNumPolyPhoneChars = 0;     // Number of polyphone chars recorded in output table.

	strcpy(sLastFreqNum, "");
	strcpy(sLastUnicodeStr, "");
	strcpy(sLastPinyinStr, "");
	
	// Read a valid line in (input freq file) with the format "(freq)  (char1)(char2)... (pinyin1)(pinyin2)...".
	while(fgets(sCurLine, BUF_SIZE, fpFreqFile) && strlen(sCurLine) > 0 && sCurLine[0] != '\n') 
	{
		iNumLines++;
		
		// Read data for one line
		if (sscanf(sCurLine, "%s %s %s", sCurFreqNum, sCurUnicodeStr, sCurPinyinStr) != 3)
		{
			printf( "Error: sscanf() not return 3 in line %d in file '%s'.\n", iNumLines, sFreqFileName);
			exit( -1 );
		}

		// Now found a char with polyphones (with at least two pronouns). 
		// Only consider polyphone char (not consider polyphone word at this time). 
		// (Assume that sCurPinyinStr is not the same as sLastPinyinStr).
		if(strlen(sCurUnicodeStr) == 2 && !strcmp(sCurUnicodeStr, sLastUnicodeStr))
		{
			// Now found a polyphone char.
			if((pPolyPhoneChar = (PolyPhoneCharPtr) malloc(sizeof(*pPolyPhoneChar))) == NULL)
			{
				printf("Error: no more memory.\n");
				exit(-1);
			}
			strcpy(pPolyPhoneChar->sUnicodeStr, sCurUnicodeStr);
			pPolyPhoneChar->iNumPronouns = 2;
			strcpy(pPolyPhoneChar->psPinyinStr[0], sLastPinyinStr);
			strcpy(pPolyPhoneChar->psPinyinStr[1], sCurPinyinStr);

			// Already found two polyphons. Then need to find out if there are any other polyphones.
			while(fgets(sCurLine, BUF_SIZE, fpFreqFile) && strlen(sCurLine) > 0 && sCurLine[0] != '\n')
			{
				iNumLines++;

				// Read data for one line
				if (sscanf(sCurLine, "%s %s %s", sCurFreqNum, sCurUnicodeStr, sCurPinyinStr) != 3)
				{
					printf( "Error: sscanf() not return 3 in line %d in file '%s'.\n", iNumLines, sFreqFileName);
					exit( -1 );
				}

				// Found another polyphone.
				if(strlen(sCurUnicodeStr) == 2 && !strcmp(sCurUnicodeStr, sLastUnicodeStr))
				{
					if(pPolyPhoneChar->iNumPronouns == MAX_NUM_DIFF_PRONOUNS)
					{
						printf("Error: pPolyPhoneChar->iNumPronouns == MAX_NUM_DIFF_PRONOUNS.\n");
						goto next;
					}
					strcpy(pPolyPhoneChar->psPinyinStr[pPolyPhoneChar->iNumPronouns++], sCurPinyinStr);
				}
				else  // No more polyphone.
				{
					for(iPronoun = 0; iPronoun < pPolyPhoneChar->iNumPronouns; iPronoun++)
					{
						// Search whole file and find all words (at least two chars) that contains the exact
						// target char and pinyin (Return NULL if not able to find any word).				
						pPolyPhoneChar->ppWordList[iPronoun] = GetWordsForOnePronoun(sFreqFileName, 
																pPolyPhoneChar->sUnicodeStr, 
																pPolyPhoneChar->psPinyinStr[iPronoun], 
																&iNumWords); 
						
						pPolyPhoneChar->iNumWordsInList[iPronoun] = iNumWords;

						// May or may not need to inlcude it as polyphone if there is no word.
						if(pPolyPhoneChar->ppWordList[iPronoun] == NULL)
						{
							printf("Cannot find any word for [%d]th pinyin of [%d] polyphone (unicode: %c%c, pinyin str: %s).\n",
										iPronoun, iNumPolyPhoneChars, 
										pPolyPhoneChar->sUnicodeStr[0], pPolyPhoneChar->sUnicodeStr[1],
										pPolyPhoneChar->psPinyinStr[iPronoun]);
							fprintf(fpPolyPhoneTableLog, "Cannot find any word for [%d]th pinyin of [%d] polyphone (unicode: %c%c, pinyin str: %s).\n",
										iPronoun, iNumPolyPhoneChars, 
										pPolyPhoneChar->sUnicodeStr[0], pPolyPhoneChar->sUnicodeStr[1],
										pPolyPhoneChar->psPinyinStr[iPronoun]);
						}
					}

					// May or may not need to decide default pronoun.
					
// Only write polyphone pinyin with at least one example word.
// If a polyphone has only one pinying with at least one example word, it will not be considered as a valid polyphone. 
#ifdef WRITE_ONLY_VALID_POLYPHONE
					iValidPolyPhone = WriteOnePolyPhoneChar(fpPolyPhoneTable, pPolyPhoneChar, iNumPolyPhoneChars);
					if(iValidPolyPhone)
						iNumPolyPhoneChars++;
					else
					{
						printf("Unicode: %c%c after [%d]th polypohone is not recorded due to lack of data.\n",
										pPolyPhoneChar->sUnicodeStr[0], pPolyPhoneChar->sUnicodeStr[1], 
										iNumPolyPhoneChars);
						fprintf(fpPolyPhoneTableLog, "Unicode: %c%c after [%d]th polypohone is not recorded due to lack of data.\n",
										pPolyPhoneChar->sUnicodeStr[0], pPolyPhoneChar->sUnicodeStr[1], 
										iNumPolyPhoneChars);
					}

#else
					WriteOnePolyPhoneChar(fpPolyPhoneTable, pPolyPhoneChar, iNumPolyPhoneChars);
					iNumPolyPhoneChars++;
#endif
				
					FreePolyPhoneChar(pPolyPhoneChar);
					pPolyPhoneChar = NULL;
						
					printf("Finish processing %d polyphone characters.\n", iNumPolyPhoneChars);
					goto next;
				}
			}
		}
		else
		{
			goto next;
		}

next:
		strcpy(sLastFreqNum, sCurFreqNum);
		strcpy(sLastUnicodeStr, sCurUnicodeStr);
		strcpy(sLastPinyinStr, sCurPinyinStr);

	}	// the first while loop.
	
	fprintf(fpPolyPhoneTableLog, "====================================================\n");
	fprintf(fpPolyPhoneTableLog, "Number of lines in the freq data file: %d\n", iNumLines);
	fprintf(fpPolyPhoneTableLog, "Number of polyphones extracted: %d\n", iNumPolyPhoneChars);
	fprintf(fpPolyPhoneTableLog, "=====================================================\n");
	// Write log file about 	iNumLines and iNumPolyPhoneChars.   

	printf("Polyphone table is written into '%s'. \nLog file is written into '%s'.\n", argv[2], argv[3]);
									
	fclose(fpFreqFile);
	fclose(fpPolyPhoneTable);
	fclose(fpPolyPhoneTableLog);
		   
	return 0;
}

 


// Read the first byte in sCurUnicode into c1 and read the second byte into c2.
// sCurUnicode is modified and moved by 2 bytes;
// return 0 on success; return -1 on error;
int ReadOneUnicode(char **psUnicode, unsigned char *c1, unsigned char *c2) 
{
	char *sUnicode;

	sUnicode = *psUnicode;

	int sLen = strlen(sUnicode);

	if(sLen < 2 )
		return (-1);

	if(sLen > 2 &&  sLen%2 != 0)
	{
		printf("Error in  ReadOneUnicode().\n");
		return (-1);
	}

	*c1 = sUnicode[0];
	*c2 = sUnicode[1];

	// Move 2 bytes.
	*psUnicode = &sUnicode[2];
	return 0;
}
