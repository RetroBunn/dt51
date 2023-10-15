/*
 * ttsja.c
 * 
 * attempt to resurrect the Japanese DECtalk TTS from days of yore
 *
 */

//#include <stdio.h> //moved to port.h for each platform MLT 01/26/06
//#include <stdlib.h>//moved to port.h for each platform MLT 01/26/06
#include "port.h"
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <unistd.h>
//#include <errno.h>
//#include <stdint.h>
#include "ls_def.h"
#include "ls_rule.h"
#include "onseiapi.h"

#define READBUF 4096
#define TRUE 1
#define FALSE 0

static int u_stop(void*);
static void EUC_JP_2_JIS_X0208(uint8_t* s);
static void SJIS_2_JIS_X0208(uint8_t* s);
static void (*x_2_JIS_X0208)(uint8_t *s) = EUC_JP_2_JIS_X0208;
static void set_str(uint8_t* buf, char* s);
static void henkan(void);
static void todec(int sta1, int end1, int* sta2, int* end2);

/* This is where the dictionary is */
static char dictionary[FILENAME_MAX+1] = {"onsei.dic"};

/* JIS X 0208 buffer */
static uint8_t inbuf[MAX_INERT*2+1] = {0};

/* phonogram data buffer */
static uint8_t talkbuf[MAX_SPEAK] = {0};

/* phrase information data buffer */ 
static uint16_t sentbuf[MAX_SENT*2] = {0};

/* part of henkan() */
static uint8_t decbuf[MAX_SPEAK] = {0};


static int u_stop(void*p) 
{
    return 0;
}

/* This is a conversion from EUC_JP to JIS X 0208 */
static void EUC_JP_2_JIS_X0208(uint8_t* s)
{
    if(s[0] >= 0x80) 
	{
        s[0] &= 0x7f;
        s[1] &= 0x7f;
    }
}

/* This is a conversion from SHIFT_JIS to JIS X 0208 */
static void SJIS_2_JIS_X0208(uint8_t* s)
{
    if (*(s+1)>0x9e) 
	{
        *s = 2*(*s-(*s>0x9f? 0xb0:0x70)); 
		*(s+1) -= 0x7e;
    } 
	else 
	{
        *s = 2*(*s-(*s>0x9f? 0xb1:0x71))+1; 
		*(s+1) -= 0x1f+(*(s+1)>=0x80 ? 1:0);
    }
}

static void set_str(uint8_t* buf, char* s)
{
    uint8_t* p = buf;
    uint8_t stopper[2] = {0,0};

    for( ; *s; p+=2,s+=2) 
	{
        memcpy(p, s, 2);
        x_2_JIS_X0208(p);
    }
    memcpy(p, stopper, 2);
}

/* henkan - */

static void henkan(void)
{
    int wsno, sta, end, dsta, dend;

    if (wsno = onsei_henkan(PROC_SENT_NO)) 
	{
        FNX_FPRINTF(stderr, "ttsja %d:onsei_henkan: %#x\n", __LINE__, wsno);
    }

    sta = wsno == 1 ? 0 : (int)sentbuf[wsno * 2 - 3];
    end = (int)sentbuf[wsno * 2 - 1];
    todec(sta, end, &dsta, &dend);
}


static void todec(int sta1, int end1, int* sta2, int* end2)
{
    int i, j, k;
    int pause, rise, fall;
	
    FNX_FPRINTF(stdout, "talkbuf: %s\n", talkbuf);
    for (i = 0, j = 0, k = 1; i < (int)FNX_STRLEN(talkbuf); i++) 
	{
		if (i == sta1) *sta2 = j;
		if (i == end1) *end2 = j;
		if (i == sentbuf[k]) 
		{
			if (!pause) decbuf[j++] = ' ';
			k += 2;
		}
		switch (talkbuf[i]) 
		{
		case '[':
			rise = TRUE;
			fall = FALSE;
			break;
		case ']':
			break;
		case '{':
			break;
		case '}':
			break;
		case '(':
			rise = TRUE;
			fall = FALSE;
			break;
		case ')':
			break;
		case ' ':
			decbuf[j++] = ' ';
			pause = TRUE;
			break;
		case ',':
			decbuf[j++] = ',';
			pause = TRUE;
			break;
		case '.':
			decbuf[j++] = '.';
			pause = TRUE;
			break;
		case '?':
			decbuf[j++] = '?';
			pause = TRUE;
			break;
		case 39:
			if (fall) 
			{
				decbuf[j++] = 96;
				fall = FALSE;
			}
			break;
		case 34:
			break;
		case '-':
			decbuf[j++] = ':';
			pause = FALSE;
			break;
		case '$':
			decbuf[j++] = talkbuf[i + 1] + 32;
			pause = FALSE;
			break;
		default:
			if (0x40 < talkbuf[i] && talkbuf[i] < 0x5b) 
			{
				if (rise) 
				{
					decbuf[j++] = 39;
					rise = FALSE;
					fall = TRUE;
				}
				switch (talkbuf[i]) 
				{
				case 'C':
					if (talkbuf[i + 1] == 'H') 
					{
						switch (talkbuf[i + 2]) 
						{
						case 'I':
							decbuf[j++] = 't';
							i++;
							break;
						case 'A':
						case 'U':
						case 'E':
						case 'O':
							decbuf[j++] = 't';
							decbuf[j++] = 'y';
							i++;
							break;
						}
					}
					break;
				case 'Q':
					decbuf[j++] = 'g';
					break;
				case 'X':
					decbuf[j++] = 'N';
					break;
				default:
					decbuf[j++] = talkbuf[i] + 32;
				}
				if (talkbuf[i + 1] == ')' && fall) 
				{
					decbuf[j++] = 96;
					fall = FALSE;
				}
				pause = FALSE;
			}
		}
    }
    decbuf[j] = 0;
    FNX_FPRINTF(stdout, "decbuf: %s\n", decbuf);
}

#if 0
int ConvertToAscii(LPVOID phTTS, wchar_t *wstr, char *str, BOOL bUnicode)
{
	int status=0;
	short kousei=0;
	int i, j, iLen, bAscii=FALSE;
	unsigned char	*sText = NULL, 
					*tok,
					sDelims[]=" \r\n\0";
	unsigned char c;
	int iA=0, iU=0, iS=0, iE=0;

	for(i=0; wstr[i] != 0x00; i++)
	{
		c = ((wstr[i] & 0xFF00) >> 8);		// Get the first byte

		// See if it's an ascii character
		if( c == 0x00 )
			iA++;
		
		// See if it's in the Unicode range
		if( (c >= 0x4e && c < 0x81) ||				// CJK
			(c == 0x30) )							// Hiragana or Katakana
			iU++;

		// See if it's in the SJIS range
		if( (c >= 0x88 && c <= 0xea) ||				// CJK
			(c >= 0x81 && c <= 0x83) )				// Hiragana or Katakana
			iS++;

		// See if it's in the EUC range
		if( (c >= 0xb0 && c <= 0xf3) ||
			(c == 0xa1 || c == 0xa4 || c == 0xa5) )
			iE++;
	}
	
	if( iA > iU && iA > iS && iA > iE )
		bAscii = TRUE;

	else if( iS > iU && iS > iE && iS > iA )
		x_2_JIS_X0208 = SJIS_2_JIS_X0208;

	else if( iE > iU && iE > iS && iE > iA )
		x_2_JIS_X0208 = EUC_JP_2_JIS_X0208;


	iLen = wcslen(wstr);
	if( bAscii )
	{
		if( str )
			wcstombs(str, wstr, iLen);
		return iLen;
	}
	else
	{
		sText = (unsigned char *)FNX_CALLOC(iLen+1, sizeof(wchar_t));
		
		for(i=j=0; wstr[j] != 0x0000; j++)
		{
			sText[i+1]	= (wstr[j] & 0x00FF);
			sText[i]	= (wstr[j] & 0xFF00) >> 8;
			i+= 2;
		}
	}	

    /* initialize */
    if (status = onsei_init(dictionary, inbuf, talkbuf, sentbuf, kousei, u_stop)) 
	{
        FNX_FPRINTF(stderr, "ttsja %d:onsei_init returned %#x\n", __LINE__, status);
        exit(EXIT_FAILURE);
    }
	
	iLen=0;
	tok = FNX_STRTOK(sText, sDelims);
	while( tok )
	{
        set_str(inbuf, tok);
        if (status = onsei_henkan(PROC_FIRST)) 
		{
            FNX_FPRINTF(stderr, "ttsja %d:onsei_henkan returned %#x\n", __LINE__, status);
        }
        if (!status) 
		{
            henkan();
			
			iLen += FNX_STRLEN(talkbuf);
			if( str )
			{
				FNX_STRCAT(str, talkbuf);
			}

            memset(inbuf, 0, sizeof(inbuf));
            memset(talkbuf, 0, sizeof(talkbuf));
            memset(sentbuf, 0, sizeof(sentbuf));
            memset(decbuf, 0, sizeof(decbuf));
            if (status = onsei_henkan(PROC_TERM)) 
			{
                FNX_FPRINTF(stderr, "ttsja %d:onsei_henkan returned %#x\n", __LINE__, status);
            }
        }

		tok = FNX_STRTOK(NULL, sDelims);
    }
	
    /* clean up */
    status = onsei_term();
    if (status) 
	{
        FNX_FPRINTF(stderr, "ttsja %d:onsei_term returned %#x\n", __LINE__, status);
        exit(EXIT_FAILURE);
    }

    return iLen;
}
#endif


#ifdef TTSJA_PROJECT

/* This is the input file */
static char input_file[FILENAME_MAX+1] = {0};

int main(int argc, char *argv[])
{
    int c, status;
    struct stat buf;
    int16_t kousei = 0;
    FILE* inpf;
    char infb[READBUF] = {0};
	
    while ((c = getopt(argc, argv, "d:f:ks")) != -1) 
	{
        switch (c) 
		{
		case 'd':
			if (FNX_STRCMP("?", optarg) != 0) 
			{
				if (stat(optarg, &buf) == -1) 
				{
					perror("stat failed");
					exit(EXIT_FAILURE);
				}
				if (!S_ISREG(buf.st_mode)) 
				{
					FNX_FPRINTF(stderr, "`%s' is not a file\n", optarg);
					exit(EXIT_FAILURE);
				}
				FNX_STRNCPY(dictionary, optarg, FILENAME_MAX);
			} 
			else 
			{
				FNX_FPRINTF(stderr, "missing argument for -d\n");
				exit(EXIT_FAILURE);
			}
			break;
		case 'f':
			if (FNX_STRCMP("?", optarg) != 0) 
			{
				if (stat(optarg, &buf) == -1) 
				{
					perror("stat failed");
					exit(EXIT_FAILURE);
				}
				if (!S_ISREG(buf.st_mode)) 
				{
					FNX_FPRINTF(stderr, "`%s' is not a file\n", optarg);
					exit(EXIT_FAILURE);
				}
				FNX_STRNCPY(input_file, optarg, FILENAME_MAX);
			} 
			else 
			{
				FNX_FPRINTF(stderr, "missing argument for -f\n");
				exit(EXIT_FAILURE);
			}
			break;
		case 'k':
			kousei = 1;
			break;
		case 's':
			x_2_JIS_X0208 = SJIS_2_JIS_X0208;
			break;
		default:
			usage();
			break;
        }
    }
	
    /* initialize */
    if (status = onsei_init(dictionary,inbuf,talkbuf,sentbuf,kousei,u_stop)) 
	{
        FNX_FPRINTF(stderr, "ttsja %d:onsei_init returned %#x\n", __LINE__, status);
        exit(EXIT_FAILURE);
    }
	
    /* open the file */
    if ((inpf = FNX_FOPEN(input_file, "r")) == NULL) 
	{
        perror("couldn\'t open file");
        exit(EXIT_FAILURE);
    }
    /* read the file */
    while (FNX_FGETS(infb, READBUF, inpf) != NULL) 
	{
        set_str(inbuf,infb);
        if (status = onsei_henkan(PROC_FIRST)) 
		{
            FNX_FPRINTF(stderr, "ttsja %d:onsei_henkan returned %#x\n", __LINE__, status);
        }
        if (!status) 
		{
            henkan();
            memset(inbuf, 0, sizeof(inbuf));
            memset(talkbuf, 0, sizeof(talkbuf));
            memset(sentbuf, 0, sizeof(sentbuf));
            memset(decbuf, 0, sizeof(decbuf));
            memset(infb, 0, sizeof(infb));
            if (status = onsei_henkan(PROC_TERM)) 
			{
                FNX_FPRINTF(stderr, "ttsja %d:onsei_henkan returned %#x\n", __LINE__, status);
            }
        }
    }
	
    /* clean up */
    status = onsei_term();
    if (status) 
	{
        FNX_FPRINTF(stderr, "ttsja %d:onsei_term returned %#x\n", __LINE__, status);
        exit(EXIT_FAILURE);
    }
    FNX_FCLOSE(inpf);
    return 0;
}

static void usage(void)
{
    FNX_FPRINTF(stderr, "usage: ttsja -d <dictionary> -f <text> [-k] [-s] \n");
    FNX_FPRINTF(stderr, "       -k sets kousei to 1 [default 0]\n");
    FNX_FPRINTF(stderr, "       -s sets input encoding to SHIFT_JIS [default EUC_JP]\n");
    exit(EXIT_FAILURE);
}
#endif
