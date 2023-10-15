/*C_HEADER_FILE****************************************************************
FILE			:	pinyinparse.c
DESC			:	
TABS			:	4
OWNER			:	
DATE CREATED:	

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

  See function mandarin_tone_process() for table of puntuation durations
  See function mandarin_syllables() for syllable durations

  Revision: Added MandarinF0machine

*END_HEADER*******************************************************************/
//#include <string.h> //moved to port.h for each platform mlt

#define IN_DECTALK
#ifdef IN_DECTALK
#include "dectalkf.h"
#include "port.h"
#include "ls_def.h"
#include "ls_defs.h"
#include "ls_data.h"
#include "ph_def.h"
#include "tts.h"
#include "mandarinprot.h"
#endif 

//#include <string.h> //moved to port.h for each platform MLT 01/24/06
//#include <stdio.h> //moved to port.h for each platform MLT 01/24/06

// API from Pinyin2Ascii.c
extern int ConvertPinyinStr2Phonemes(char *sPinyinStr, char *sPhonemeStr, int nMaxLen);

#ifndef IN_DECTALK
#define userulesdebug
#define userules_is_main
#endif

#ifdef userulesdebug
#define debug_printf(fmt,args...) printf(fmt,## args)
#else
#ifdef _UNIX_LIKE_
#define debug_printf(fmt,args...)
#else
#define debug_printf(fmt,args)
#endif
#endif




/*FUNCTION_HEADER**********************
 * NAME:	;look_for_next_syllable
 * DESC: 	Get the phonemes and tone for the next syllable
 * IN:		inphones - string of input tone+phonemes
 * OUT:		syll - phonemes in next syllable
			tone - tone of next syllable
 * RETURN:	pointer to stop character on success, NULL on failure
 * NOTES:	
 *END_HEADER***************************/
char *look_for_next_syllable(char *inphones, char *sSyll, int *tone)
{
    char 
		*pc;
    int k;
	
	if( inphones == NULL )
		return NULL;

	sSyll[0] = 0x00;
	*tone = 0;

	for( pc = inphones; pc && *pc; pc++ )
	{
		if( *pc == '\n' ||				// skip leading spaces
			*pc == ' ' )
		{
			continue;
		}
		else if( '1' <= *pc && *pc <= '5' )		// found a tone value which indicates the beginning of a syllable
		{
			*tone = *pc - '0';			// convert char to int
			pc++;						// advance to the next char
			k=0;
			while( *pc && FNX_STRCHR(MANDARIN_PHONES, *pc) )
			{
				sSyll[k++] = *pc;
				pc++;
			}
			sSyll[k] = 0x00;
			
			if( *pc == '-' )			// advance past the syllable boundary character
				pc++;

			return pc;
		}
		else if( FNX_STRCHR(MANDARIN_CONTROL_PHONES, *pc) )		// found punctuation
		{
			*tone = 0;
			k = 0;
			while(	*pc && 
					*pc != '-' &&
					FNX_STRCHR(MANDARIN_CONTROL_PHONES, *pc) )
			{
				sSyll[k++] = *pc;
				pc++;
			}
			sSyll[k] = 0x00;

			if( *pc == '-' )			// advance past the syllable boundary character
				pc++;

			return pc;
		}
	}

	return NULL;

}


/*FUNCTION_HEADER**********************
 * NAME:	;FreeMandarinSyllables
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void FreeMandarinSyllables(MandSyll *pHead)
{
	MandSyll *pTmp;

	pTmp = pHead;
	while( pTmp && pHead )
	{
		pTmp = pHead;			// Pop one structure off the top of the linked list
		pHead = pHead->pNext;	// Move the head of the linked list to the next one
		FNX_FREE(pTmp);				// Free the popped structure
	}
}




/*FUNCTION_HEADER**********************
 * NAME:	;mandarin_syllables
 * DESC: 	change a string of input syllables into a list of 
			MandSyll structures.
 * IN:		inphones - input string of syllables (tone+phonemes)
 *          LPTTS_HANDLE_T phTTS 
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
MandSyll *mandarin_syllables(LPTTS_HANDLE_T phTTS, CHAR *inphones)
{
    /* First find the next number in the string that is in between 1 and 5. */
    char *pc,
	syll[20];
    int 
		tone,
		len,
		nsyll=0;
	MandSyll 
		*pHead=NULL, 
		*pSyll=NULL;
	
	pc=inphones;

	if( inphones == NULL )
		return NULL;

    // get the tone and phonemes for the next syllable
    while( (pc = look_for_next_syllable(pc, syll, &tone)) != NULL )	
    {
		len = FNX_STRLEN(syll);
		
		if( len == 0 || len >= 6 )
			continue;

		/* Change: allocation of syllables is a "service" done by MandarinF0Machine code 
		 */

		if( pHead == NULL )
		{
			pHead = pSyll = newMand_Syll(phTTS);
		}
		else
		{
			pSyll->pNext = newMand_Syll(phTTS);
			if( pSyll->pNext != NULL )
				pSyll = pSyll->pNext;
			else
				break;	// better to be incomplete that to crash
		}

		FNX_STRCPY(pSyll->syll, syll);				// copy the syllable phonemes
		pSyll->tone = tone;						// copy the syllable tone
		nsyll++;
    }

    return pHead;
}


/* Here is the "ugly number 9" 
   A special syllable is generated
   by default from the ER symbol with
   tone 2 , which gets translated as
   '9' ascky. If this is found, the
   syllable is deleted and the preceeding
   syllable modified 
   */

#define MAND_ER_SYMBOL '9'

int is_er_syllable(MandSyll *pSyll)
{
	if (pSyll->syll[0] == MAND_ER_SYMBOL && pSyll->syll[1]=='\0') return 1;
	return 0;
}

/* 
   modify_erhua
   input MandSyll. 

   Experimental code to realize the ER reduction rules.
   This subroutine is called if the syllable has to 
   be modified because the following sound is ER.
   (The subsequent syllable is replaced by an empty 
    syllable elsewhere).

   We check in the syllable to which the ER reduction
   rule applies, if the last phoneme is a nasal n or N (ng)
   If it is the case, the final nasal is removed.
   Then we look at the last vowel, and go by a list
   of case statements to find the proper replacement
   of the vowel by one of the er allophones.
   the entire vowel is then replaced by this allophone.
*/

typedef struct _MandErHuarule
{
	char left[6];
	char right[4];
} MAND_REPLACE_RULE;

/*  
  WXn + er -> G
  JE + er -> F
  We + er -> G
*/

MAND_REPLACE_RULE replace_erhua[]=
{
	{"WXn", "G"},
	{"JEn", "JB"},
	{"JE" , "F"},
	{"We" , "G"}
};

static const int nerhuarules = sizeof(replace_erhua) / sizeof(MAND_REPLACE_RULE);

MAND_REPLACE_RULE mand_replace_relaxed[]=
{
	{"d3","dM"},
	{"bA","bL"},
	{"mA","mL"},
	{"n3","nM"},
	{"l3","lM"}
};

static const int nrelaxedrules=sizeof(mand_replace_relaxed) / sizeof(MAND_REPLACE_RULE);

int mand_replace_rule(char *syll, char *left, char *right)
{
	int l,ll,i;
	char *p, *q;

	l=0;
	ll=0;

	for (p = syll; *p; p++) l++;   // p points to zero terminator of syll
	for (q = left; *q; q++) ll++;  // q points to zero terminator of left
	
	if (ll>l) return 0;           // string too long, left can not fit into syll.

	p--;            // back to last char in syll
	q--;            // back to last char in left

	for (i=0; i<ll; i++)   // compare if last ll letters match
	{
		if ((*p) == (*q))
		{
			p--;
			q--;
		}
		else
		{
			return 0;
		}
	}

	p++;
	
	q = right;

	while (*q)
	{
		*p++ = *q++;
	}

	*p = '\0';

	return 1;
}


void mand_tone5_replace_relaxed(MandSyll *pSyll)
{
	int len,k;

	if (!pSyll) return;
	len = FNX_STRLEN(pSyll->syll);
	for (k=0; k<nrelaxedrules; k++)
		{
		 if (FNX_STRCMP(pSyll->syll, mand_replace_relaxed[k].left) == 0)
		 {
			 FNX_STRCPY(pSyll->syll, mand_replace_relaxed[k].right);
			 return;
		 }
	}
}


void modify_erhua(MandSyll *pSyll)
{
	char last, penult, er;
	int  len, fin, k, nasalfin;
	
	if (!pSyll) return;

	len = FNX_STRLEN(pSyll->syll);
	if (len<1 || len>6) return;	

/* modifications now the ugly number nine is the last
   character of a syllable. Strip it off and modify 
   preceeding characters of the syllable           */

	if (pSyll->syll[len-1] != MAND_ER_SYMBOL) return;

	if (len==1 && pSyll->syll[0] == MAND_ER_SYMBOL)
	{
		pSyll->syll[0]='8';
		return;
	}


	pSyll->syll[len-1] = '\0';   /* get rid of final '9' */
	len = len-1;                 
	if (len<1) return;

	for (k=0; k< nerhuarules ; k++)
	{
		if (mand_replace_rule(pSyll->syll,replace_erhua[k].left, replace_erhua[k].right) ==1) return;
	}

	nasalfin=0;

	if (len==1)
	{
		penult='\0';
		last = pSyll->syll[0];
		fin = 1;
	}
	else if (len>1)
	{
		last = pSyll->syll[len-1];
		penult = pSyll->syll[len-2];
		
		if (last == 'n' || last == 'N')
		{
			last = penult;
			fin = len-1;     //overwrite nasal
			penult='\0';     
			nasalfin=1;
		}
		else
		{
			fin = len;
			nasalfin=0;
		}
	}
	switch (last)
	{
	case 'i': er = 'F'; break;
	case 'U': 
		if (nasalfin ) er = 'Y'; 
		else 
		{
			if (len>1) er = 'Y';
			else       er = 'V';
		}
		break;
	case 'e': er = 'B'; break;
	case 'E': er = 'B'; break;
	case 'A': er = 'T'; break;
	case 'I': 
			if (penult=='z' || penult=='c' || penult=='s') er = 'B';
			else er = 'F'; 
			break;
	case '2': 
			if (penult=='Z' || penult=='C' || penult =='S' || penult == 'r') er = 'B';
			else er = 'F'; 
			break;

	case 'X': er = 'G'; break;
	case 'u': er = 'D'; break; 
	case '5': er = '@'; break;
	case '3': er = 'B'; break;
	case 'o': er = '%'; break;
	case 'O': er = '@'; break;
	case '^': er = 'B'; break;
	case '4': er = '@'; break;
	case 'a': er = 'T'; break;
	case '6': er = 'T'; break;
	case '7': er = '$'; break;
	case '8': er = 'B'; break;
 
	default:  er = 'B'; break;
	}
	pSyll->syll[fin-1]=er;   // replace a vowel by an allophone of ER
	pSyll->syll[fin]='\0';   // terminate string.
	
	return;	
}

void apply_erhua_rules(MandSyll *pMandSylls)
{
	MandSyll *pSyll;
	
	for( pSyll = pMandSylls; pSyll ; pSyll=pSyll->pNext )
	{
		modify_erhua(pSyll);
		if (pSyll->tone==5) 
		{
			mand_tone5_replace_relaxed(pSyll);
		}
	}
}

/* note: This is a rewrite */
void apply_sandhi_rules(MandSyll *pMandSylls)
{
	MandSyll *pSyll;
	
	/* if three third tones are together don't modify the first one
	   but if only two third tones are together modify the first one to second tone.
	   So if 3 3rd tones are together, the next round in the loop will turn the middle one
	   into a second tone. Right?
    */
    for( pSyll = pMandSylls; pSyll && pSyll->pNext; pSyll=pSyll->pNext )
    {
		if (pSyll->tone == 3 && pSyll->pNext->tone ==3)   // two t3 in a row.
		{
			if (pSyll->pNext->pNext)                      // a third one?
			{
				if (pSyll->pNext->pNext->tone != 3)  pSyll->tone = 2;   //only change current if not 3rd.
			}
			else
			{
			    pSyll->tone = 2;
			}
		}
	}
}

void send_mand_control_phoneme(LPTTS_HANDLE_T phTTS, int par1, int par2)
{
    short buf[2];
	
	buf[0] = (PFUSA<<PSFONT) + (short) par1;
	ls_util_write_pipe(phTTS->pKernelShareData,&buf[0],1);
}
/* the purpose of this subroutine is to 
   let the synthesizer start and finish 
   the production of the phonemes sent sofar 
   in a controlled manner. 
*/
void mand_wait_for_synthesis(LPTTS_HANDLE_T phTTS, int iStop, int duration)
{
	Mand_F0_machine(phTTS,
		MFZ_PUT_CNTR_PHONEME,
		VOID_NULL_PTR,
		duration,
		iStop,    
		0);  
	/* This will start synthesis: */
	send_mand_control_phoneme(phTTS, iStop, duration);
	
	/* (Does not send iStop again:) */
	Mand_F0_machine(phTTS,
		MFZ_PAUSE_RESET,
		VOID_NULL_PTR,
		duration,
		iStop,    
		0);     
	
}
/*FUNCTION_HEADER**********************
 * NAME:	;mandarin_tone_process
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void mandarin_tone_process(LPTTS_HANDLE_T phTTS, char *outphonemes)
{
	char
		bResetTone=0;
    short 
		buf[2];
    int 
		k,
		duration,
		iStop,
		lastsyll,
		sentphonemes;

    MandSyll 
		*pMandSylls, 
		*pSyll;
	PKSD_T 
		pKsd_t = phTTS->pKernelShareData;		// Needed in DT_DBG


	// This is needed to ensure we don't over-run the array of syllables, otherwise long sentences
	// will crash! (RBM)
	Mand_F0_machine(phTTS, MFZ_INITSYLLABLES,  NULL, 0,0,0);
	
	sentphonemes=0;

	if( (pMandSylls = mandarin_syllables(phTTS, outphonemes)) == NULL )	// Convert syllable string to MandSyll structures
		return;

    apply_sandhi_rules(pMandSylls);

	apply_erhua_rules(pMandSylls);

	for( pSyll=pMandSylls; pSyll; pSyll=pSyll->pNext)
    {
		if (pSyll->pNext)
		{
			if (pSyll->pNext->tone == 0)
			{
				lastsyll =1;
			}
			else
			{
				lastsyll =0;
			}
		}
		else
		{
			lastsyll = 1;
		}

		if( pSyll->tone == 0 )	
		{
			// Handle punctuation

			int nLen = FNX_STRLEN(pSyll->syll);
			for( k=0; k<nLen; k++ )
			{
				if( FNX_STRCHR(MANDARIN_CONTROL_PHONES, pSyll->syll[k]) )
				{
					buf[0] = phTTS->pKernelShareData->reverse_ascky[pSyll->syll[k]];
					buf[0] += (1 << PSNEXTRA);		// number of items to follow buf[0]
					
					iStop = 0;
					// Get punctuation duration in milliseconds "~=`'\"/\\<-*# ();,.?!+^&>"
					switch(pSyll->syll[k])
					{
						case ' ':	iStop = WBOUND;		bResetTone = 0;	duration = 100; break;
						case '?':	iStop = QUEST;		bResetTone = 1;	duration = 350; break;
						case '.':	iStop = PERIOD;		bResetTone = 1;	duration = 250;	break;
						case ',':	iStop = COMMA;		bResetTone = 1;	duration = 200;	break;
						case '!':	iStop = EXCLAIM;	bResetTone = 1;	duration = 350; break;
						case ';':	iStop = COMMA;		bResetTone = 1;	duration = 200;	break;
						case ':':	iStop = COMMA;		bResetTone = 1;	duration = 250;	break;
						case '(':	iStop = COMMA;		bResetTone = 1;	duration = 100;	break;
						case ')':	iStop = COMMA;		bResetTone = 1;	duration = 100;	break;
						default:						bResetTone = 0;	duration = 100;	break;
					}
					buf[1] = duration;

					if( iStop > 0 )
					{
						//ls_util_send_phone(phTTS, iStop);				// send stop value
						if( bResetTone )
						{
							mand_wait_for_synthesis(phTTS, iStop, duration);
							bResetTone=0;
						}
					}

				}
			}
		}
		else
		{
			// Handle syllable
			if (sentphonemes>48)
			{
				mand_wait_for_synthesis(phTTS, COMMA, 10);	
				sentphonemes=0;
			}
			Mand_F0_machine(phTTS, MFZ_STARTSYLLABLE, (void *) pSyll,0,0,0); 
			sentphonemes += Mand_F0_machine(phTTS, MFZ_PUTSYLLABLE, (void *) pSyll, pSyll->tone,lastsyll,0);
		}

    }	// for each syllable
}

/*FUNCTION_HEADER**********************
 * NAME:	;Chinese_ProcessPinyin
 * DESC: 	Convert pinyin input into phonemes and then speak it
 * IN:		phTTS - pointer to structure containing global data
			sInWord - pinyin+tone input
 * OUT:		
 * RETURN:	number of phonemes on success, 0 on failure
 * NOTES:	
 *END_HEADER***************************/
int Chinese_ProcessPinyin(LPTTS_HANDLE_T phTTS, char *sInWord)
{
	char sOutPhonemes[MAX_PINYIN_PHONEMES];
	int nLenInWord,
		nLenPhonemes=0;

	if( sInWord == NULL || *sInWord == 0x00 )
		return 0;

	/*	If the last tone of the previous phrase was something other than neutral,
		then this phrase will start up with the wrong pitch transitions */


	Mand_F0_machine(phTTS, MFZ_INITSYLLABLES,  NULL, 0,0,0);

	nLenInWord = FNX_STRLEN(sInWord);
	if( nLenInWord <= MAX_PINYIN_PHONEMES >> 1  )
	{
		// If the input word isn't too long then process the whole thing
		if( (nLenPhonemes = ConvertPinyinStr2Phonemes(sInWord, sOutPhonemes, MAX_PINYIN_PHONEMES)) > 0 )
		{
			mandarin_tone_process(phTTS, sOutPhonemes);
		}
	}
	else
	{
		char 
			sString[MAX_PINYIN_PHONEMES],
			*pcStart,
			*pc;

		// If sInWord is long then break it up at reasonable boundaries
		for( pcStart = pc = sInWord; *pc; pc++ )
		{
			// Process any segment ending in one of the following characters
			if( FNX_STRCHR(" .,):;\n", *pc) )
			{
				FNX_STRNCPY(sString, pcStart, pc-pcStart+1);	// Keep the punctuation character
				sString[pc-pcStart+1] = 0x00;
				if( (nLenPhonemes = ConvertPinyinStr2Phonemes(sString, sOutPhonemes, MAX_PINYIN_PHONEMES)) > 0 )
				{
					mandarin_tone_process(phTTS, sOutPhonemes);
				}
				pcStart = pc+1;
			}
			else if( pc-pcStart >= MAX_PINYIN_PHONEMES >> 1 )		// Don't over-run this internal buffer
			{
				// If we have gone too long and still haven't found any punctuation to break at
				// then back up to the end of the last pinyin+tone and break there.
				while( !('0' <= *pc && *pc <= '9') && pc > pcStart)
				{
					pc--;
				}
				FNX_STRNCPY(sString, pcStart, pc-pcStart+1);	// Keep the tone value
				sString[pc-pcStart+1] = 0x00;
				if( (nLenPhonemes = ConvertPinyinStr2Phonemes(sString, sOutPhonemes, MAX_PINYIN_PHONEMES)) > 0 )
				{
					mandarin_tone_process(phTTS, sOutPhonemes);
				}
				pcStart = pc+1;
			}
		}

		// Process the final segment
		if( pc > pcStart )
		{
			FNX_STRNCPY(sString, pcStart, pc-pcStart);
			sString[pc-pcStart] = 0x00;
			if( (nLenPhonemes = ConvertPinyinStr2Phonemes(sString, sOutPhonemes, MAX_PINYIN_PHONEMES)) > 0 )
			{
				mandarin_tone_process(phTTS, sOutPhonemes);
			}

		}

	}

	Mand_F0_machine(phTTS, MFZ_FINISHPHRASE, VOID_NULL_PTR,0,0,0);
	return nLenPhonemes;
}

