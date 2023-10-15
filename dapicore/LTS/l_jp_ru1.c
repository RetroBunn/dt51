/*
 ***********************************************************************
 *                                                                      
 *                           Copyright ©
 *    Copyright © 2002 Fonix Corporation. All rights reserved.
 *    Copyright © 2000-2001 Force Computers, Inc., a Solectron company. All rights reserved.
 *    © Digital Equipment Corporation 1996, 1997. All rights reserved.        
 *                                                                  
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.    
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.                                
 *                                                                      
 *    This software is proprietary to and embodies the confidential
 *    technology of Fonix Corporation and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Fonix or an
 *    authorized sublicensor.              
 *                                                                       
 *********************************************************************** 
 *    File Name:	l_jp_ru1.c
 *    Author:		Matthew Schnee
 *    Creation Date:02/06/96
 *                                         
 *    Functionality:                                                 
 *    Language dependent LTS Rule code
 *
 ***********************************************************************       
 *                                                                             
 * Rev	Who		Date			Description                    
 * ---	-----	-----------		---------------------------------------
 * 001	GL      07/29/1996  	use ls_util_write_pipe() to replace write_pipe()
 * 002	GL		10/23/1996      remove unused index mark handling code.
 * 003	GL		11/01/1996		use ls_fold[] to handle multi-national characters
 *								need to remove this change once we have the rule to
 *                              handle these characters in rule file. 
 * 004	GL		04/21/1997		BATS#360  remove spaces before "#define" or "#if" 
 * 005	NS		05/02/1997		Removed form-feed characters.  Needed for stripper to work properly.
 * 006	GL      09/24/1997		BATS#470  Add LDS debug switch 
 *                              also remove the duplicated rule table definition
 * 007  ETT		10/05/1998      Added Linux code.
 * 008	MGS		04/13/2000		Changes for integrated phoneme set 
 * 009	NAL		06/12/2000		Warning removal
 * 010 	CAB		10/18/2000		Changed copyright info
 * 011	MFG		02/19/2001		Warning removal for windows CE
 * 012	CAB		02/23/2001		Updated copyright info
 * 013	MGS		03/09/2001		Fixed inserting of + in a rule
 * 014	MGS		03/22/2001		Added an additional debug output
 * 015	MGS		05/09/2001		Some VxWorks porting BATS#972
 * 016  CAB		05/14/2001		Edited copyright info
 * 017	MGS		06/19/2001		Solaris Port BATS#972
 * 018	MGS		02/25/2002		Removed unsued index code
 * 019	CAB		05/22/2002		Updated copyright info
 * 020	CAB		05/23/2002		Removed warnings
 */

#include "ls_def.h"
#include "ls_rule.h"
#include "onseiapi.h"
#include "CodePageConv.h"	// Convert between Unicode, SJIS and EUC

int is_non_phoneme(char symb);
void make_phdigit(LPTTS_HANDLE_T phTTS,short phodigit);
int next_accent_is_rise(char array[],short begin,short end);
void insert_symb(char array[],char symb,short begin,short end);
int fall_helper(char *inarray,short lastchar);

void prphdigit(short nphones);


void ls_rule_jp_parse(LPTTS_HANDLE_T phTTS);




/*			   J K L P A R S E . C				*/

/*	Copyright 1984				Dennis H. Klatt		*/
/*	COPYRIGHT 1984,1991 DIGITAL EQUIPMENT CORPORATION		*/
/*	Convert string of letters representing phonemes,accents, and	*/
/*	 boundaries into integer phoneme/accent/boundary sequence	*/

/* EDIT HISTORY:
 * 0001 13-Jun-84 DK	Initial creation
 *
 */

//#include <stdio.h> //moved to port.h for each platform - mlt

//#include "jphdefs.h"

/*    Input arrays and variables:					*/
//	extern char pLts_t->j_decbuf[];	/* Input ascii phonemic text		*/
//	extern short cur_input_pos;	/* Number of input ascii chars		*/

/*    Output arrays and variables:					*/
//	extern short symbols[];	/* Digits of phoneme/accent/boundaries	*/
//	extern short nsymbtot;	/* Number of phonemes in symbols[]	*/


//	static short n,pLts_t->lastdigit,pLts_t->need_fall;
//	static char pLts_t->accent_state;

#define LAST_WAS_ACCENT_RISE	1
#define LAST_WAS_ACCENT_FALL	2


#ifdef JAPANESE
/* This is a conversion from EUC_JP to JIS X 0208 */
#include "onsei.h"
int onsei_henkan(int16_t sw);

/*FUNCTION_HEADER**********************
 * NAME:	;todec
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static void todec(LPTTS_HANDLE_T phTTS,int sta1, int end1, int* sta2, int* end2)
{
    int i, j, k;
	int l;
    int pause=0,rise=0, fall=0;
	PLTS_T pLts_t=phTTS->pLTSThreadData;
	PKSD_T pKsd_t=phTTS->pKernelShareData;
	
	   // FNX_FPRINTF(stdout, "talkbuf: %s\n", talkbuf);
     for (i = 0, j = 0, k = 1; i < (int)FNX_STRLEN(pLts_t->j_talkbuf); i++) 
	{
		if (i == sta1) 
			*sta2 = j;
		if (i == end1) 
			*end2 = j;
		if (i == pLts_t->j_sentbuf[k]) 
		{
			if (!pause) 
				pLts_t->j_decbuf[j++] = ' ';
			k += 2;
		}
		switch (pLts_t->j_talkbuf[i]) 
		{
		case '[':
		case '(':
//			l=i+1;
//			while(pLts_t->j_talkbuf[l] && pLts_t->j_talkbuf[l]!='(' && 
//				pLts_t->j_talkbuf[l]!=')' && pLts_t->j_talkbuf[l]!=']' && pLts_t->j_talkbuf[l]!='[' /*&& pLts_t->j_talkbuf[l]!='-'*/)
//			{
//				if (pLts_t->j_talkbuf[l]=='\'')
//				{
					rise = TRUE;
					fall = FALSE;
					break;
//				}
//				l++;
//			}
//			break;
		case ']':
			break;
		case '{':
			break;
		case '}':
			break;
		case ')':
			if (pLts_t->j_talkbuf[i+1]=='(')
				pLts_t->j_decbuf[j++] = ' ';
			break;
		case ' ':
			pLts_t->j_decbuf[j++] = ' ';
			pause = TRUE;
			break;
		case ',':
			pLts_t->j_decbuf[j++] = ',';
			pause = TRUE;
			break;
		case '.':
			pLts_t->j_decbuf[j++] = '.';
			pause = TRUE;
			break;
		case '?':
			pLts_t->j_decbuf[j++] = '?';
			pause = TRUE;
			break;
		case '\'':
			if (fall) 
			{
				pLts_t->j_decbuf[j++] = '`';
				fall = FALSE;
			}
			break;
			
		case '"':
			break;
		case '-':
			pLts_t->j_decbuf[j++] = ':';
			/*if (rise==FALSE)
			{
				l=i+1;
				while(pLts_t->j_talkbuf[l] && pLts_t->j_talkbuf[l]!='(' && 
					pLts_t->j_talkbuf[l]!=')' && pLts_t->j_talkbuf[l]!=']' && pLts_t->j_talkbuf[l]!='[' && pLts_t->j_talkbuf[l]!='-')
				{
					if (pLts_t->j_talkbuf[l]=='\'')
					{
						rise = TRUE;
						fall = FALSE;
						break;
					}
					l++;
				}
			}*/
			pause = FALSE;
			break;
		case '$':
			pLts_t->j_decbuf[j++] = pLts_t->j_talkbuf[i + 1] + 32;
			pause = FALSE;
			break;
		default:
			if (0x40 < pLts_t->j_talkbuf[i] && pLts_t->j_talkbuf[i] < 0x5b) 
			{
				if (rise) 
				{
					pLts_t->j_decbuf[j++] = '\'';
					rise = FALSE;
					fall = TRUE;
				}
				switch (pLts_t->j_talkbuf[i]) 
				{
				case 'C':
					if (pLts_t->j_talkbuf[i + 1] == 'H') 
					{
						switch (pLts_t->j_talkbuf[i + 2]) 
						{
						case 'I':
							pLts_t->j_decbuf[j++] = 't';
							i++;
							break;
						case 'A':
						case 'U':
						case 'E':
						case 'O':
							pLts_t->j_decbuf[j++] = 't';
							pLts_t->j_decbuf[j++] = 'y';
							i++;
							break;
						}
					}
					break;
				case 'Q':
					pLts_t->j_decbuf[j++] = 'g';
					break;
				case 'X':
					pLts_t->j_decbuf[j++] = 'N';
					break;
				default:
					pLts_t->j_decbuf[j++] = pLts_t->j_talkbuf[i] + 32;
				}
				if (pLts_t->j_talkbuf[i + 1] == ')' && fall) 
				{
					pLts_t->j_decbuf[j++] = '`';
					fall = FALSE;
				}
				pause = FALSE;
			}
		}
    }
    pLts_t->j_decbuf[j] = 0;
	if (DT_DBG(LTS_DBG,0x010))
	{
#ifndef ARM7_NOSWI
	    FNX_PRINTF("j_decbuf: %s\n", pLts_t->j_decbuf);
#endif
	}
}


/*FUNCTION_HEADER**********************
 * NAME:	;henkan
 * DESC: 	Convert
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static void henkan(LPTTS_HANDLE_T phTTS,int do_onsei)
{
    int wsno, sta, end, dsta, dend;
	
	PLTS_T pLts_t=phTTS->pLTSThreadData;
	
    if (do_onsei && (wsno = onsei_henkan(PROC_SENT_NO))) 
	{
		//        FNX_PRINTF(stderr, "ttsja %d:onsei_henkan: %#x\n", __LINE__, wsno);
    }
	else
	{
		wsno=0;
	}
	
    sta = wsno == 1 ? 0 : (int)pLts_t->j_sentbuf[wsno * 2 - 3];
    end = (int)pLts_t->j_sentbuf[wsno * 2 - 1];
    todec(phTTS,sta, end, &dsta, &dend);
}


/*FUNCTION_HEADER**********************
 * NAME:	;EUC_JP_2_JIS_X0208
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static void EUC_JP_2_JIS_X0208(uint8_t* s)
{
	s[0] &= 0x7f;
	s[1] &= 0x7f;
}

/*FUNCTION_HEADER**********************
 * NAME:	;EUC_JP_2_JIS_X0212
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static void EUC_JP_2_JIS_X0212(uint8_t* s)
{
	s[0] |= 0x80;
	s[1] |= 0x80;
}


/*FUNCTION_HEADER**********************
 * NAME:	;SJIS_2_JIS_X0208
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static void SJIS_2_JIS_X0208(uint8_t* s)
{
    if (*(s+1)>0x9e) 
	{
        *s=2*(*s-(*s>0x9f? 0xb0:0x70)); 
		*(s+1)-=0x7e;
    } 
	else 
	{
        *s=2*(*s-(*s>0x9f? 0xb1:0x71))+1; 
		*(s+1)-=0x1f+(*(s+1)>=0x80? 1:0);
    }
}


int convert_spec_char(unsigned char in,unsigned char out[2])
{
	unsigned char temp[2]={0,0};
	switch(in)
	{
	case '.':
		temp[0]=0xa1;
		temp[1]=0xa5;
		break;
	case ',':
		temp[0]=0xa1;
		temp[1]=0xa4;
		break;
	case ':':
		temp[0]=0xa1;
		temp[1]=0xa7;
		break;
	case ';':
		temp[0]=0xa1;
		temp[1]=0xa8;
		break;
	case '?':
		temp[0]=0xa1;
		temp[1]=0xa9;
		break;
	case '!':
		temp[0]=0xa1;
		temp[1]=0xaa;
		break;
	case '"':
		temp[0]=0xa1;
		temp[1]=0xab;
		break;
	case '\'':
		temp[0]=0xa1;
		temp[1]=0xad;
		break;
	case '`':
		temp[0]=0xa1;
		temp[1]=0xae;
		break;
	case '^':
		temp[0]=0xa1;
		temp[1]=0xb0;
		break;
	case '/':
		temp[0]=0xa1;
		temp[1]=0xbf;
		break;
	case '~':
		temp[0]=0xa1;
		temp[1]=0xc1;
		break;
	case '|':
		temp[0]=0xa1;
		temp[1]=0xc3;
		break;
	case '(':
		temp[0]=0xa1;
		temp[1]=0xca;
		break;
	case ')':
		temp[0]=0xa1;
		temp[1]=0xcb;
		break;
	case '[':
		temp[0]=0xa1;
		temp[1]=0xce;
		break;
	case ']':
		temp[0]=0xa1;
		temp[1]=0xcf;
		break;
	case '{':
		temp[0]=0xa1;
		temp[1]=0xd0;
		break;
	case '}':
		temp[0]=0xa1;
		temp[1]=0xd1;
		break;
	case '+':
		temp[0]=0xa1;
		temp[1]=0xdc;
		break;
	case '-':
		temp[0]=0xa1;
		temp[1]=0xdd;
		break;
	case '\\':
		temp[0]=0xa1;
		temp[1]=0xc0;
		break;
	case '<':
		temp[0]=0xa1;
		temp[1]=0xe3;
		break;
	case '>':
		temp[0]=0xa1;
		temp[1]=0xe4;
		break;
	case '_':
		temp[0]=0xa1;
		temp[1]=0xb2;
		break;
	case '=':
		temp[0]=0xa1;
		temp[1]=0xe1;
		break;
	case '$':
		temp[0]=0xa1;
		temp[1]=0xf0;
		break;
	case '%':
		temp[0]=0xa1;
		temp[1]=0xf3;
		break;
	case '#':
		temp[0]=0xa1;
		temp[1]=0xf4;
		break;
	case '&':
		temp[0]=0xa1;
		temp[1]=0xf5;
		break;
	case '*':
		temp[0]=0xa1;
		temp[1]=0xa6;
		break;
	case '@':
		temp[0]=0xa1;
		temp[1]=0xa7;
		break;
	}

	if (temp[0]==0 || temp[1]==0)
	{
		return(0);
	}
	out[0]=temp[0]-0x80;
	out[1]=temp[1]-0x80;
	return(1);
}

		


/*FUNCTION_HEADER**********************
 * NAME:	;set_str
 * DESC: 	Get some text to work on.  
			The input text must be Shift-Jis which then converted to JIS.
 * IN:		pLts_t - pointer to the TTS - LTS data structure
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int set_str(LPTTS_HANDLE_T phTTS)
{
	unsigned char
		*pcIn,
		*pcOut;
	int 
		output_count=0;
    uint8_t 
		stopper[2] = {0,0};
	int which=1,
		old_which=0;
	unsigned char spec_char[2];
	PLTS_T pLts_t=phTTS->pLTSThreadData;
	PKSD_T pKsd_t=phTTS->pKernelShareData;
	int i;
	if (DT_DBG(LTS_DBG,0x010))
	{
#ifndef ARM7_NOSWI
		FNX_PRINTF("set_str input:%s\n",pLts_t->input_array);
		FNX_PRINTF("set_str cnvin:");
		for (i=0;pLts_t->input_array[i];i++)
		{
			FNX_PRINTF("0x%02X ",pLts_t->input_array[i]);
			if ((i+1)%8==0)
				FNX_PRINTF("\n");
			
		}
		FNX_PRINTF("\n");
#endif
	}

	for( pcIn = &pLts_t->input_array[pLts_t->cur_read_pos], pcOut=pLts_t->j_inbuf; *pcIn; pcIn++ )
	{
		if( *pcIn == 0x0a || 
			*pcIn == 0x0d )
		{
#if 0
			which = 1;
			if( old_which == 0 )
				old_which = which;
			if( old_which != which )
				break;
			*(pcOut++) = ' ';
#endif
		}
		else if (*pcIn >='0' && *pcIn<='9')
		{
			*(pcOut++) = '#';
			*(pcOut++) = *pcIn;
		}
		else if (*pcIn >='A' && *pcIn<='Z')
		{
			*(pcOut++) = '#';
			*(pcOut++) = *pcIn;
		}
		else if (*pcIn >='a' && *pcIn<='z')
		{
			*(pcOut++) = '#';
			*(pcOut++) = *pcIn;
		}
		else if( 0x20 <= *pcIn && *pcIn <= 0x7f )		// single byte ascii
		{
#if 0
			which = 1;
			if( old_which == 0 )
				old_which = which;
			if( old_which != which )
				break;
#endif
			if (convert_spec_char(*pcIn,spec_char))
			{
				*(pcOut++) = spec_char[0];
				*(pcOut++) = spec_char[1];
			}
		}
		else if( 0xa0 <= *pcIn && *pcIn <= 0xdf )		// single byte kana
		{
			which = 2;
			if( old_which == 0 )
				old_which = which;
			if( old_which != which )
				break;

			if( *pcIn == 0xa4 )						// convert backwards comma to sjis comma
			{
				*(pcOut++) = 0x81;					// ideographic comma
				*(pcOut++) = 0x41;
				SJIS_2_JIS_X0208(pcOut-2);			// convert from SJis to Jis
			}
			else if( *pcIn == 0xa1 )				// convert period to sjis period
			{
				*(pcOut++) = 0x81;					// ideographic full stop
				*(pcOut++) = 0x42;
				SJIS_2_JIS_X0208(pcOut-2);			// convert from SJis to Jis
				pcIn++;								// must advance to the next character so we don't get in an infinite loop playing the period
				break;								// break here so that the full stop will be realized correctly
			}
			else
			{
				*(pcOut++) = *pcIn;
			}
		}
		else if( (0x81 <= *pcIn && *pcIn <= 0x9f) ||	// first byte of 2 byte character
				 (0xe0 <= *pcIn && *pcIn <= 0xfc) )
		{
			which = 2;
			if( old_which == 0 )
				old_which = which;
			if( old_which != which )
				break;
			*(pcOut++) = *(pcIn++);
			*(pcOut++) = *pcIn;

			SJIS_2_JIS_X0208(pcOut-2);					// convert from SJis to Jis
		}
	}
	*pcOut = 0x00;			// null terminate
	*(pcOut+1) = 0x00;
	pLts_t->cur_read_pos = pcIn - pLts_t->input_array;
	output_count = pcOut - pLts_t->j_inbuf;

	if (DT_DBG(LTS_DBG,0x010))
	{
#ifndef ARM7_NOSWI
		FNX_PRINTF("set_str output:%s\n",pLts_t->j_inbuf);
		FNX_PRINTF("set_str cnvout:");
		for (i=0;pLts_t->j_inbuf[i];i++)
		{
			FNX_PRINTF("0x%02X ",pLts_t->j_inbuf[i]|0x80);
			if ((i+1)%8==0)
				FNX_PRINTF("\n");
		}
		FNX_PRINTF("\n");
#endif
	}


	if( output_count == 0 )
		return(-1);			// Done parsing

	if( old_which==1 )		// Current input is Romaji
	{
		return(1);
	}

	return(0);
	
}

#endif


/*FUNCTION_HEADER**********************
 * NAME:	;ls_rule_do_japanese
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int ls_rule_do_japanese(LPTTS_HANDLE_T phTTS, char *sRomaji, BOOL bSpeak)
{
	int status=0;
	int ret=0;
	int iLen=0;
	PLTS_T pLts_t=phTTS->pLTSThreadData;
	PKSD_T pKsd_t=phTTS->pKernelShareData;

	// Initialize data
	memset(pLts_t->j_inbuf, 0, sizeof(pLts_t->j_inbuf));
	memset(pLts_t->j_talkbuf, 0, sizeof(pLts_t->j_talkbuf));
	memset(pLts_t->j_sentbuf, 0, sizeof(pLts_t->j_sentbuf));
	memset(pLts_t->j_decbuf, 0, sizeof(pLts_t->j_decbuf));

	while( (ret=set_str(phTTS)) != -1 &&				// Get some text to work on
			pLts_t->cur_read_pos <= pLts_t->cur_input_pos )		// Don't over-run the input buffer
	{
		if (phTTS->pKernelShareData->halting)
			return 0;
#ifndef ARM7
		if (phTTS->bInReset)	
			return 0;
#endif
		if (ret==1)		// Handle Romaji
		{
			FNX_STRCPY(pLts_t->j_decbuf, pLts_t->j_inbuf);
		}
		else			// Handle converting JIS characters to Romaji
		{
			// This is where the JIS to Romaji translation happens and gets put into j_talkbuf

			if (status = onsei_henkan(PROC_FIRST))
			{
				// FNX_FPRINTF(stderr, "ttsja %d:onsei_henkan returned %#x\n", __LINE__, status);
			}
			if (DT_DBG(LTS_DBG,0x010))
			{
#ifndef ARM7_NOSWI
			FNX_PRINTF("talkbuf:%s\n",pLts_t->j_talkbuf);
#endif
			}

			if (phTTS->pKernelShareData->halting)
				return 0;
#ifndef ARM7
			if (phTTS->bInReset)	
				return 0;
#endif
			if (status)
			{
				henkan(phTTS,0);	// j_talkbuf gets parsed and put into j_decbuf
			}
			if (!status)
			{
				henkan(phTTS,1);
				memset(pLts_t->j_inbuf, 0, sizeof(pLts_t->j_inbuf));
				memset(pLts_t->j_talkbuf, 0, sizeof(pLts_t->j_talkbuf));
				memset(pLts_t->j_sentbuf, 0, sizeof(pLts_t->j_sentbuf));
				if (status = onsei_henkan(PROC_TERM)) 
				{
					//      FNX_FPRINTF(stderr, "ttsja %d:onsei_henkan returned %#x\n", __LINE__, status);
				}
			}
		}

		if (phTTS->pKernelShareData->halting)
			return 0;

#ifndef ARM7
		if (phTTS->bInReset)	
			return 0;
#endif
		
		iLen += FNX_STRLEN(pLts_t->j_decbuf);

		if( sRomaji )
			FNX_STRCAT(sRomaji, pLts_t->j_decbuf);

		if( bSpeak )
			ls_rule_jp_parse(phTTS);
		
		memset(pLts_t->j_inbuf, 0, sizeof(pLts_t->j_inbuf));
		memset(pLts_t->j_talkbuf, 0, sizeof(pLts_t->j_talkbuf));
		memset(pLts_t->j_sentbuf, 0, sizeof(pLts_t->j_sentbuf));
		memset(pLts_t->j_decbuf, 0, sizeof(pLts_t->j_decbuf));
		
	}

	if( bSpeak )
	{
		// If we've spoken the text then let's clear the buffer
		memset(pLts_t->input_array, 0, sizeof(pLts_t->input_array));
		pLts_t->cur_read_pos = pLts_t->cur_input_pos = 0;
	}

	return iLen;
	
}

static int u_stop(void*p) 
{
    return 0;
}


/*FUNCTION_HEADER**********************
 * NAME:	;ConvertToAscii
 * DESC: 	Convert shift-jis characters to romaji
 * IN:		phTTS - pointer to TTS stuff
			lpInput - pointer to sjis string
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int ConvertToAscii(LPTTS_HANDLE_T phTTS, void *lpInput, char *sRomaji, int iInputType)
{
	int
		iLen;
	PLTS_T 
		pLts_t=phTTS->pLTSThreadData;
	unsigned char 
		*input_array = pLts_t->input_array;

	memset(input_array, 0, sizeof(pLts_t->input_array));

	FNXA_STRCPY(input_array, (unsigned char *)lpInput);

	pLts_t->cur_read_pos = 0;
	pLts_t->cur_input_pos = FNXA_STRLEN((unsigned char *)lpInput);

	iLen = ls_rule_do_japanese(phTTS, sRomaji, FALSE);
	pLts_t->cur_read_pos = pLts_t->cur_input_pos = 0;

	return iLen;
}

/*FUNCTION_HEADER**********************
 * NAME:	;ls_rule_jp_parse
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
		SYMBOL	MEANING
		~		BLOCKRULES
		'		ACCENT RISE
		/		ACCENT RISE
		`		ACCENT FALL
		\		ACCENT FALL
		:		LONG_PHONE
		_		SIL
		#		SIL
		{		NEW_PARAGRAPH
		.		PERIOD
		,		COMMA
		?		QUEST

 *END_HEADER***************************/
void ls_rule_jp_parse(LPTTS_HANDLE_T phTTS)
{

	char last_char,curr_char,next_char;
	char out_phone;
	short ntemp;
	PLTS_T pLts_t=phTTS->pLTSThreadData;
	int n;
	int cur_input_pos=FNX_STRLEN(pLts_t->j_decbuf);

	//	nsymbtot = 0;
	pLts_t->lastdigit = 0;
	pLts_t->accent_state = LAST_WAS_ACCENT_FALL;
	n=0;
	while (n<cur_input_pos)
	{
		if( pLts_t->j_decbuf[n]==' ' ||		// Skip spaces
			pLts_t->j_decbuf[n]=='\n' ||	// Skip newline characters
			pLts_t->j_decbuf[n]=='+')		// Skip '+' symbol
		{
			n++;
		}
		else
		{
			break;
		}
	}

	//eab n=-1 appears to simply flush a silence clause useless!
	for (n ; n < cur_input_pos; n++)
	{

		/*	  Set last,curr,next characters */

	    if (n > 0)	
			last_char = pLts_t->j_decbuf[n-1];
		else	
			last_char = '#';

	    if (n >= 0)	
			curr_char = pLts_t->j_decbuf[n];
		else	
			curr_char = ',';					/* Always start with silence */

	    if (n < (cur_input_pos-1))	
			next_char = pLts_t->j_decbuf[n+1];
		else	 	
			next_char = '#';

		/*	FNX_FPRINTF(stderr, "\tWorking on  %c%c%c\n", last_char, curr_char, next_char); */

		/*	  Check to see if non-phonemic chars are out of order */
	    if( is_non_phoneme(curr_char) ) 
		{
			/*	  Look ahead only for numerical ordering constraints */
			ntemp = n+1;
			while( is_non_phoneme(pLts_t->j_decbuf[ntemp]) &&
				   ntemp < (cur_input_pos-1) ) 
			{
				if( pLts_t->j_decbuf[ntemp] == curr_char)    
					goto skip;

				if( pLts_t->j_decbuf[ntemp] == ':') 
				{
					if( curr_char != '`' && 
						curr_char != '\\' &&
						curr_char != '\'' && 
						curr_char != '/' ) 
					{
#ifdef PH_DEBUG
						FNX_FPRINTF(FNX_STDERR,
							"\nWARNING in JKLPARSE: Misordered COLON moved adjacent to previous seg\n");
						FNX_FPRINTF(FNX_STDERR, "  %s\n", pLts_t->j_decbuf);
#endif
						pLts_t->j_decbuf[n] = pLts_t->j_decbuf[ntemp];
						pLts_t->j_decbuf[ntemp] = curr_char;
#ifdef PH_DEBUG
						FNX_FPRINTF(FNX_STDERR, "  %s\n", pLts_t->j_decbuf);
#endif
					}
					else 
					{
						pLts_t->j_decbuf[ntemp] = last_char;	// Make rise on 2nd  half of vowel only
					}
					n--;	
					goto endlup;
				}

				/*		  Accent fall must come right after vowel/N */
				if( pLts_t->j_decbuf[ntemp] == '\\' || 
					pLts_t->j_decbuf[ntemp] == '`' ) 
				{
					if (curr_char == ':') 
					{
						curr_char = last_char;					// Make fall on 2nd half of vowel only
					}
					else 
					{
#ifdef PH_DEBUG
						FNX_FPRINTF(FNX_STDERR,
							"\nWARNING in JKLPARSE: Misordered ACCENT FALL moved adjacent to previous seg\n");
						FNX_FPRINTF(FNX_STDERR, "  %s\n", pLts_t->j_decbuf);
#endif
						pLts_t->j_decbuf[n] = pLts_t->j_decbuf[ntemp];
						pLts_t->j_decbuf[ntemp] = curr_char;
#ifdef PH_DEBUG
						FNX_FPRINTF(FNX_STDERR, "  %s\n", pLts_t->j_decbuf);
#endif
						n--;	
						goto endlup;
					}
				}
skip:		    
				ntemp++;
			}
		}

		/*	  Switch on the current input character */
	    switch(curr_char) 
		{
			
		case '~':
			make_phdigit(phTTS,BLOCK_RULES);	
			break;
			
		case ')':
			if (pLts_t->accent_state == LAST_WAS_ACCENT_RISE) 
			{
				if( next_accent_is_rise( (char *)pLts_t->j_decbuf, (short)(n+1), (short)cur_input_pos) ) 
				{
					pLts_t->need_fall = TRUE;
				}
			}
			make_phdigit(phTTS,PPSTART);	
			break;
			
		case ' ':
		case '+':
		case '\n':
			if (pLts_t->accent_state == LAST_WAS_ACCENT_RISE) 
			{
				/*	Use of n+2 overlooks word-init ['] or [/] so fall
				*	is not realized, and rise will be deleted */
				if( next_accent_is_rise((char *)pLts_t->j_decbuf, (short)(n+2), (short)cur_input_pos)) 
				{
					pLts_t->need_fall = TRUE;
				}
			}
			make_phdigit(phTTS,WBOUND);	
			break;
			
		case '-':
			if (pLts_t->accent_state == LAST_WAS_ACCENT_RISE) 
			{
				/*		      If helper carries accent fall (else delay to WB) */
				if (fall_helper((char *)&pLts_t->j_decbuf[n+1], (short)cur_input_pos)) 
				{
					/* Can't change cur_input_pos	    insert_symb(pLts_t->j_decbuf,'`',n,++cur_input_pos) */
					make_phdigit(phTTS,ACCENT_FALL);
					pLts_t->accent_state = LAST_WAS_ACCENT_FALL;
				}
			}
			make_phdigit(phTTS,ABOUND);	
			break;
			
		case ',':
			if (pLts_t->accent_state == LAST_WAS_ACCENT_RISE) 
			{
				pLts_t->accent_state = LAST_WAS_ACCENT_FALL; /* Fall dur SIL */
			}
			make_phdigit(phTTS,COMMA);	
			break;
			
		case '.':
			if (pLts_t->accent_state == LAST_WAS_ACCENT_RISE) 
			{
				pLts_t->accent_state = LAST_WAS_ACCENT_FALL; /* Fall dur SIL */
			}
			make_phdigit(phTTS,PERIOD);	
			break;
			
		case '?':
			if (pLts_t->accent_state == LAST_WAS_ACCENT_RISE) 
			{
				pLts_t->accent_state = LAST_WAS_ACCENT_FALL; /* Fall dur SIL */
			}
			make_phdigit(phTTS,QUEST);	
			break;
			
		case '\'':
		case '/':
			/*		  Next sym must be +seg */
			if ((is_non_phoneme(next_char)) && (n < (cur_input_pos-1))) 
			{
#ifdef PH_DEBUG
//				FNX_FPRINTF(stderr,
//				"\nWARNING in JKLPARSE: Misordered accent RISE moved adjacent to next seg\n");
//				FNX_FPRINTF(stderr, "  %s\n", pLts_t->j_decbuf);
#endif
				pLts_t->j_decbuf[n] = next_char;
				pLts_t->j_decbuf[n+1] = curr_char;
#ifdef PH_DEBUG
//							FNX_FPRINTF(stderr, "  %s\n", pLts_t->j_decbuf);
#endif
				n--;	break;
			}
			if (pLts_t->accent_state == LAST_WAS_ACCENT_FALL) 
			{
				pLts_t->accent_state = LAST_WAS_ACCENT_RISE;
				if (curr_char == '/') 
				{
					make_phdigit(phTTS,STRONG_RISE);	
					break;
				}
				make_phdigit(phTTS,ACCENT_RISE);	
				break;
			}
			else 
			{
				//	WARNING in JKLPARSE: Deleting second of two accent RISES in a row
				pLts_t->need_fall = FALSE;
#ifdef PH_DEBUG
//					FNX_FPRINTF(stderr,
//					"\nWARNING in JKLPARSE: Deleting second of two accent RISES in a row\n");
//					FNX_FPRINTF(stderr, "  %s\n", pLts_t->j_decbuf);
//					pLts_t->j_decbuf[n] = '_';
#endif
				break;
			}
			
			
		case '`':
		case '\\':
		    if (pLts_t->accent_state == LAST_WAS_ACCENT_RISE) 
			{
				pLts_t->accent_state = LAST_WAS_ACCENT_FALL;
				if (curr_char == '\\') 
				{
					make_phdigit(phTTS,STRONG_FALL);	
					break;
				}
				make_phdigit(phTTS,ACCENT_FALL);	
				break;
			}
			else 
			{
				pLts_t->j_decbuf[n] = '_';
				break;
			}

		case ':':
			make_phdigit(phTTS,LONG_PHONE);	
			break;
			
		case '{':
			make_phdigit(phTTS,NEW_PARAGRAPH);	
			break;
			
			/*	Begin real phoneme letters */
		case '_':
		case '#':
			make_phdigit(phTTS,SIL);	
			break;
			
		case 'i':
			out_phone = J_I;
			/*	Diphthongs are single phoneme, w+V is treated as diph */
			if (last_char == 'w') 
				out_phone = J_WI;
			make_phdigit(phTTS,out_phone);
			if (pLts_t->need_fall == TRUE) 
			{
				make_phdigit(phTTS,ACCENT_FALL);
				pLts_t->accent_state = LAST_WAS_ACCENT_FALL;
				pLts_t->need_fall = FALSE;
			}
			break;
			
		case 'e':
			out_phone = J_E;
			if (last_char == 'w') out_phone = J_WE;
			if (last_char == 'y') out_phone = J_YE;
			make_phdigit(phTTS,out_phone);
			if (pLts_t->need_fall == TRUE) 
			{
				make_phdigit(phTTS,ACCENT_FALL);
				pLts_t->accent_state = LAST_WAS_ACCENT_FALL;
				pLts_t->need_fall = FALSE;
			}
			break;
			
		case 'a':
			out_phone = J_A;
			if (last_char == 'w') out_phone = J_WA;
			if (last_char == 'y') out_phone = J_YA;
			make_phdigit(phTTS,out_phone);
			if (pLts_t->need_fall == TRUE) {
				make_phdigit(phTTS,ACCENT_FALL);
				pLts_t->accent_state = LAST_WAS_ACCENT_FALL;
				pLts_t->need_fall = FALSE;
			}
			break;
			
		case 'o':
			out_phone = J_O;
			if (last_char == 'w') out_phone = J_WO;
			if (last_char == 'y') out_phone = J_YO;
			make_phdigit(phTTS,out_phone);
			if (pLts_t->need_fall == TRUE) {
				make_phdigit(phTTS,ACCENT_FALL);
				pLts_t->accent_state = LAST_WAS_ACCENT_FALL;
				pLts_t->need_fall = FALSE;
			}
			break;
			
		case 'u':
			out_phone = J_U;
			if (last_char == 'y') out_phone = J_YU;
			make_phdigit(phTTS,out_phone);
			if (pLts_t->need_fall == TRUE) {
				make_phdigit(phTTS,ACCENT_FALL);
				pLts_t->accent_state = LAST_WAS_ACCENT_FALL;
				pLts_t->need_fall = FALSE;
			}
			break;
			
		case 'p':
			make_phdigit(phTTS,J_P);	
			break;
			
		case 'b':
			out_phone = J_B;
			if (next_char == 'h') 
			{
				out_phone = J_BH;
				n++;
			}
			make_phdigit(phTTS,out_phone);	
			break;
			
		case 't':
			out_phone = J_T;
			if (next_char == 's') 
			{
				out_phone = J_TS;
				n++;
			}
			make_phdigit(phTTS,out_phone);	
			break;
			
		case 'd':
			out_phone = J_D;
			if (next_char == 'h') 
			{
				out_phone = J_DH;
				n++;
			}
			make_phdigit(phTTS,out_phone);	
			break;
			
		case 'k':
			make_phdigit(phTTS,J_K);	
			break;
			
		case 'g':
			out_phone = J_G;
			if (next_char == 'h') 
			{
				out_phone = J_GH;
				n++;
			}
			make_phdigit(phTTS,out_phone);	
			break;
			
		case 'm':
			make_phdigit(phTTS,J_M);	
			break;
			
		case 'n':
			out_phone = J_N;
			if (next_char == 'x') 
			{
				out_phone = J_NG;			// was NX HELPME
				n++;
			}
			make_phdigit(phTTS,out_phone);	
			break;
			
		case 'N':
			make_phdigit(phTTS,J_EN);	
			break;
			
		case 'r':
			make_phdigit(phTTS,J_R);	
			break;
			
		case 'f':
			make_phdigit(phTTS,J_F);	
			break;
			
		case 's':
			out_phone = J_S;
			if (next_char == 'h') 
			{
				out_phone = J_SH;
				n++;
			}
			make_phdigit(phTTS,out_phone);	
			break;
			
		case 'z':
			out_phone = J_Z;
			make_phdigit(phTTS,out_phone);	
			break;
			
		case 'h':
			make_phdigit(phTTS,J_H);	
			break;
			
		case 'j':
			make_phdigit(phTTS,J_JH);	
			break;
			
		}
endlup:    
		n = n;
	}

}


/*FUNCTION_HEADER**********************
 * NAME:	;make_phdigit
 * DESC: 	Put a phoneme/accent/boundary symbol in the output array
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void make_phdigit(LPTTS_HANDLE_T phTTS, short phodigit) 
{
	
	/*    See if legal phoneme */
	PLTS_T pLts_t=phTTS->pLTSThreadData;
	short temp;
	if ((phodigit < 0) || (phodigit > PHO_SYM_TOT)) 
	{
#ifdef PH_DEBUG
		FNX_FPRINTF(FNX_STDERR,
			"ERROR in JKLPARSE: Phoneme = %d requested in make_phdigit(phTTS,)\n",
			phodigit);
		phodigit = 0;
		FNX_FPRINTF(FNX_STDERR, "\tReplace by silence phoneme\n");
#endif
	}
	
	if (phodigit<100)
		temp = (short)(phodigit|(PFJP<<PSFONT));
	else
		temp=phodigit;
	/*    Put this symbol into the phoneme/accent/boundary array */
#ifdef NEW_MULTI_LANG_ARCH
	phTTS->ph_funcs.ph_loop(phTTS,&temp);
#else
	ph_loop(phTTS,&temp);
#endif
	//	symbols[nsymbtot] = phodigit;
	pLts_t->lastdigit = phodigit;
	
	/*    Update pointer into array */
	//	if (nsymbtot < NPHON_MAX)	nsymbtot++;
	
}



/*FUNCTION_HEADER**********************
 * NAME:	;is_non_phoneme
 * DESC: 	See if character symbol is a phoneme or a accent/boundary symbol
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int is_non_phoneme(char symb) 
{
	
	if ( ((symb < 'a') || (symb > 'z'))
		&& (symb != 'N') ) 
	{
		return(TRUE);
	}
	return(FALSE);
}


/*FUNCTION_HEADER**********************
 * NAME:	;next_accent_is_rise
 * DESC: 	If next accent in string is a RISE, return true
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int next_accent_is_rise(char array[],short begin,short end) 
{
	
	short n;
	
	for (n=begin; n<end; n++) 
	{
		if ((array[n] == '`') || (array[n] == '\\'))		// FALL
		{
			return(FALSE);
		}
		if ((array[n] == '\'') || (array[n] == '/'))		// RISE
		{
			return(TRUE);
		}
	}
	return(TRUE);
}


/*FUNCTION_HEADER**********************
 * NAME:	;insert_symb
 * DESC: 	Insert a symbol in the input array so debugging prints clearer
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	Assumes variable 'end' has been incremented by +1 before call
 *END_HEADER***************************/
void insert_symb(char array[],char symb,short begin,short end)
{
	short n;
	
	n = end;
	while (n > begin) {
		array[n] = array[n-1];
		n--;
	}
	array[begin] = symb;
}



/* LIST OF HELPER PARTICLES WITH ACCENT FALL */
const char * const helpers[] = {
	"xx",
	"yyy",
	"zzzz"
};
const short mhelpers = 3;

/*FUNCTION_HEADER**********************
 * NAME:	;fall_helper
 * DESC: 	Analyze helper particle, does accent fall occur on or after it
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 * This routine is highly simplified because the placement of the fall
 *  depends on:
 *	(1) the particular particle
 *	(2) the syntactic category of the root (noun, verb, adjective)
 *	(3) the location of the accent rise in the root
 *  all of which information is contained in a standard Japanese dictionary.
 *  Unfortunately, we do not know the latter two bits of information here.
 *
 * A sophisticated user should always indicate to JDECTALK where the fall
 *  occurs following a rise.  Most native Japanese speakers will have
 *  some difficulty in doing so, although patience with the dictionary
 *  can solve the problem in all cases.
 *END_HEADER***************************/
int fall_helper(char *inarray, short lastchar)
{

	short m,npos;
	char c;
	char *p;

/*    Return TRUE if helper contains an accent rise */
	npos = 0;
	while (is_non_phoneme(inarray[npos]) == FALSE) {
/*	  Move to non-phone */
	    npos++;
	}
	if (inarray[npos] == '\'')    return(TRUE);

/*    Try each of a list of helper words with accent fall on them */
	for (m=0; m<mhelpers; m++) {
/*	  Try each position in the helper for a letter match */
	    npos = 0;
	    p = (char *)helpers[m];
	    while ((c = p[npos]) != '\0') {
		if (inarray[npos++] != c)  goto nomatch;
	    }
/*	  See if end of candidate helper, or more letters in input */
	    if ((inarray[npos] < 'a') || (inarray[npos] > 'z')) return(TRUE);
/*	  No match, try next helper */
nomatch:
	    m = m;
	}
/*    No match for any helper in list, failure */
	return(FALSE);	/* Accent fall after helper */
}


/*FUNCTION_HEADER**********************
 * NAME:	;prphdigit
 * DESC: 	Print output phonemes/accents/boundary symbols
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void prphdigit(short nphones) 
{

	extern short printsw;

}
