/*C_HEADER_FILE****************************************************************
FILE			:	stdonsei.c 
DESC			:	contains the APIs for the onsei functions
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

*END_HEADER*******************************************************************/
//#include <stdio.h> //moved to port.h for each platform mlt 02/08/06
//#ifndef ARM7  //moved to port.h for each platform mlt 02/08/06
//#endif //moved to port.h for each platform mlt 02/08/06
//#include <stdlib.h> //moved to port.h for each platform mlt 02/08/06
//#include <string.h> //moved to port.h for each platform mlt 02/08/06
//#include <ctype.h> //moved to port.h for each platform mlt 02/08/06
#include "port.h"
//#ifdef _UNIX_LIKE_
//#include <sys/types.h> //moved to port.h for each platform mlt 02/08/06
//#include <sys/stat.h> //moved to port.h for each platform mlt 02/08/06
//#include <fcntl.h> //moved to port.h for each platform mlt 02/08/06
//#endif
//#include <errno.h>


#define		EXT		extern

#include "onsei.h"
#include "entrypt.h"
#include "onseiapi.h"
#include "ile_kkhh.h"
#include "ile_mruh.h"	// learning stuff
#include "ile_nydh.h"	// input data

#include "ls_def.h"
#include "ls_rule.h"

#define PAGESIZE 1024

static STRUCT_ONSEI OnseiParam = {0};
static uint8_t outbuf[2+MAX_OMEGA*3+3+1] = {0};		/* Output data area */
#ifdef ARM7
static FILE* jfd = 0;									/* Japanese file descriptor ? */
#else
static int jfd = 0;									/* Japanese file descriptor ? */
#endif
//static const char* dictionary = "/usr/share/dict/onsei.dic";

//#ifdef WIN32
static int u_alloc(void** addr, size_t size);
static void u_dealloc(void** addr);
static int u_write(int page, size_t size, void *addr);
static int u_read(int page, size_t size, void* addr);
//#endif //WIN32
static int onsei_checkdata(int16_t fall);
int hatsuon_mora(uint8_t* ptr, uint8_t* buf);

extern void check_X(uint8_t* , int16_t);
extern int dispchar_to_code(uint8_t* , uint8_t*);

/*FUNCTION_HEADER**********************
 * NAME:	;onsei_init
 * DESC: 	Performs initialization for the conversion processing.
 * IN:		jname - Pointer to the dictionary path
			inbuf - Pointer to Kana and Chinese character (Kanji) mixture sentence (JIS X 0208)
			talkbuf - Pointer to the place where the phonogram string is stored
			sentbuf - Pointer to the place where word or phrase information is stored
			kousei - when 0, disregard signs, when 1, read all signs
			u_stop - function that discontinues conversion
 * OUT:		
 * RETURN:	0:					Normal termination
			Err_Fatal_DIC:		Dictionary (onsei.dic) can't be opened
			Err_Broken:			Dictionary is broken
			Err_Fatal_Alloc:	Insufficient memory
 * NOTES:	
 *  -- Secures the place for Kana Chinese character (Kanji) mixture sentences, for the phonogram string,
 *     and for the word or phrase information, and calls the pointer for each.
 *  -- When you can not wait for the analysis to end, you define the function u_stop
 *     which forces it to end and call that function's far pointer.
 *  -- Calls the dictionary path and symbolic reading flag.
 *  -- The parameters above can not be modified in the middle of processing.
 *     When wanting to modify, call the onsei_term, and then call the onsei_init again. 
*END_HEADER***************************/
int onsei_init(const char* jname, uint8_t* inbuf, uint8_t* talkbuf, uint16_t* sentbuf, 
			   int16_t kousei, int (*u_stop)(void*))
{
    int status;
#ifndef ARM7
    int mode;
#endif

    //dictionary = jname;
    OnseiParam.onsei_inert = inbuf;
    OnseiParam.onsei_speak = talkbuf;
    OnseiParam.onsei_sent  = sentbuf;
	OnseiParam.onsei_alloc = u_alloc;
    OnseiParam.onsei_dealloc = u_dealloc;
    OnseiParam.onsei_read  = u_read;
    OnseiParam.onsei_write = u_write;
    OnseiParam.onsei_stop  = u_stop;			// simple function that just returns 0 (?)
    OnseiParam.onsei_kouseisystem = kousei;		// Correction system (0)

    OnseiParam.onsei_omega = outbuf;
    OnseiParam.onsei_usetankan = 1;		/* Fixed to 1 */
    OnseiParam.onsei_readcrlf = 0;		/* Fixed to 0 */
    OnseiParam.onsei_crlfexist = 0;		/* Fixed to 0 */
    
    //dictionary=jname;

#ifndef ARM7 // HELPME MGS this needs to be fixed
    mode = O_RDONLY;
#ifdef WIN32
    mode |= O_BINARY;
#endif

    if ((jfd=_open(jname, mode))==-1) 
	{
        return Err_Fatal_DIC;	/* No dictionary */
    }
#else
    if ((jfd=FNX_FOPEN(jname,"rb"))==NULL) 
	{
        return Err_Fatal_DIC;	/* No dictionary */
    }
#endif
    OnseiParam.onsei_procno = PROC_ENV_INIT;
    status=entrypt(&OnseiParam);
    return status;
}

/*FUNCTION_HEADER**********************
 * NAME:	;onsei_henkan
 * DESC: 	Performs all the types of conversion processing.
 * IN:		sw - type of processing
 * OUT:		
 * RETURN:	
 * NOTES:	
 * In the types of processing (sw), you can define any of the following:
 *
 *   PROC_FIRST:		First conversion
 *   PROC_NEXT:			Attention word or phrase next candidate
 *   PROC_TERM:			Decides on learned information
 *   PROC_RIGHT:		Attention word or phrase move to the right
 *   PROC_LEFT:			Attention word or phrase move to the left
 *   PROC_SHORT:		Splits into the direction of short word or phrase
 *	 PROC_LONG:			Splits into the direction of long word or phrase
 *   PROC_SENT_NO:		Takes out the attention word or phrase number
 *   PROC_ACON:			Combines the accent of attention word or phrase and the next word or phrase
 *   PROC_ACOFF:		Does not combine the accent of attention word or phrase to the next word or phrase
 *   PROC_PAUSE_INS:	Inserts a pause directly after the attention word or phrase.
 *   PROC_PAUSE_DEL:	Takes out the puase directly after the attention word or phrase
 * 
 *
 * When the sw is anything but PROC_FIRST, PROC_NEXT, or PROC_SENT_NO,  the value is as follows:
 *    0:				Normal termination
 *    Err_NaibuOVF:		The word or phrase number is over limit (too big) or the phonogram string is too long
 *    Err_Chuudan:		Stopped at u_stop()
 *    Err_Fatal_Edic:	Dictionary malfunction
 *    Err_Fatal_Idic:	Dictionary malfunction
 *    Err_IdouFunou:	Word or phrase movement is not possible
 *    Err_NextNone:		There is no next candidate
 *    Err_RestrictCNT:	Timed out
 *
 * When the sw is PROC_FIRST or PROC_NEXT, then 
 *    15 or less:		Normal termination. The first word is positioned at the top.
 *    Err_NaibuOVF:		The word or phrase number is over or the phonogram string is too long
 *    Err_Chuudan:		Stopped at at u_stop()
 *    Err_Fatal_Edic:	Dictionary malfunction
 *    Err_Fatal_Idic:	Dictionary malfunction
 *    Err_IdouFunou:	Word or phrase movement is not possible
 *    Err_NextNone:		There is no next candidate
 *    Err_HenkanTochuu:	Conversion of a word that is not in the dictionary
 *    Err_RestrictCNT:	Timed out
 *
 * When the sw is PROC_SENT_NO: then return the current word or phrase number
 *END_HEADER***************************/
int onsei_henkan(int16_t sw)
{
    int status;
	
    if (sw == PROC_SENT_NO) 
	{
        return OnseiParam.onsei_wsno;
    } 
	else if (sw == PROC_FIRST) 
	{
        uint8_t* c;
        for (c = outbuf; *c; ++c) 
		{
            *c = 0;
        }
    }
    OnseiParam.onsei_procno = sw;
    status=entrypt(&OnseiParam);		// This is where the rough conversion from JIS to Romaji happens when sw == 3
    /*
	* When it ends normally, return the position of the fall of the first word.
	* PROC_FIRST,PROC_NEXTonly
	*/
    switch (sw) 
	{
		case PROC_FIRST:
		case PROC_NEXT:
			if(status==0) 
			{
				/* Position of a fall */
				return OnseiParam.onsei_acctype;
			} 
			else 
			{
				if (status<0x80) 
				{
					/* Sentence moving, no next target, timeout */
					return status | 0x70;
				} 
				else 
				{
					return status;
				}
			}
    }
    return status;
}

/*FUNCTION_HEADER**********************
 * NAME:	;onsei_term
 * DESC: 	Completes the conversion processing. 
			Writes out the learned information, etc.
 * IN:		
 * OUT:		
 * RETURN:	0:		Normal termination
 *			else:	Dictionary malfunction
 * NOTES:	
 *END_HEADER***************************/
int onsei_term(void)
{
    int status;
    OnseiParam.onsei_procno = PROC_ENV_TERM;
    status=entrypt(&OnseiParam);
#ifndef ARM7
	_close(jfd);
#else    
	FNX_FCLOSE(jfd);
#endif
	jfd = 0;
    return status;
}

/*FUNCTION_HEADER**********************
 * NAME:	;onsei_add
 * DESC: 	Performs registering of the dictionary
 * IN:		talkbuf
			fall - The position of the top of the accent
 * OUT:		
 * RETURN:	
 *    0:				Normal termination
 *    1:				The way it is read or the top position of the accent is not correct
 *    Err_EdicTooLong:	The written item or the reading is too long
 *    Err_TourokuSumi:	The same one is already registered
 *    Err_EdicOVF:		Can not be registered -> if the dictionary readjusts, then it will be OK
 * NOTES:	
 *END_HEADER***************************/
int onsei_add(int16_t fall)
{
    int status;

	if(onsei_checkdata(fall)==1) 
	{
        return 1;
    }
    status=onsei_henkan(PROC_EDIC_ADD);
    return status;
}

/*FUNCTION_HEADER**********************
 * NAME:	;onsei_del
 * DESC: 	Performs dictionary deletion
 * IN:		talkbuf
			fall - The position of the top of the accent
 * OUT:		
 * RETURN:	
 *    0:				Normal termination 
 *    1:				The way it is read or the top position of the accent is not correct
 *    Err_EdicTooLong:	The written item or the reading is too long
 *    Err_MiTouroku:	Word not registered 
 * NOTES:	
 *END_HEADER***************************/
int onsei_del(int16_t fall)
{
    int status;

	if(onsei_checkdata(fall)==1) 
	{
        return 1; 
    }
    status=onsei_henkan(PROC_EDIC_DELETE2);
    return status;
}


/*FUNCTION_HEADER**********************
 * NAME:	;onsei_del2
 * DESC: 	Perform dictionary deletion of the words that are in the process of currently being converted.
			Before calling this function, it is absolutely necessary to call the first conversion and 
			then the next candidate.  When the return value of the first conversion and the next 
			candidate is 16 or more, (except when the accent is at the top position), you must not call it.
 * IN:		talkbuf
 * OUT:		
 * RETURN:	 
 *    0:				Normal termination 
 *    Err_MiTouroku:	It is not the user's registration word
 * NOTES:	
 *END_HEADER***************************/
int onsei_del2()
{
    int status;

    status=onsei_henkan(PROC_EDIC_DELETE);
    return status;
}


/*FUNCTION_HEADER**********************
 * NAME:	;onsei_checkdata
 * DESC: 	Copies talkbuf to outbuf
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int onsei_checkdata(int16_t fall)
{
    /* input: fall */
    /*	return 0: OK	*/
    /*	return 1: Error	*/
    uint16_t nbuf,i; 
	uint8_t *si,*di;
  
	FNX_STRCPY(outbuf, OnseiParam.onsei_speak);

    /* Convert the ROMA character to its upper case. */
    {
        uint8_t* c;
        for (c = outbuf; *c; ++c) 
		{
            *c = FNX_TOUPPER(*c);
        }
    }

    /* Punctuation data check */
    if (hatsuon_mora(outbuf,&outbuf[20])==0) 
	{
        return 1;
    }
    nbuf=outbuf[20];
    if (nbuf>15 || fall>nbuf) 
	{ 
        return 1;
    }
    /* Categorize the syllabic nasal and double consonant.*/
    check_X(&outbuf[21],outbuf[20]);
    
	/* Accent information */
    outbuf[1] = 4;
    outbuf[2] = (uint8_t)fall; 
	outbuf[3] = 0x11; 
	outbuf[4] = 0x21;
    outbuf[5] = (fall) ? (0x40|(uint8_t)fall) : 0x41;

    /*
     *	explanation of outbuf[]
     *
     * from
     *	 0  1  2...				  20 21...
     *	+--+--+--------------+---+--+--------------------+
     *	| ?|L1| accent codes |   |L2| pronunciation data |
     *	+--+--+--------------+---+--+--------------------+
     *	      |<-----L1----->|      |<--------L2-------->|
     *	      |<------ 18 ------>|
     *
     * to
     *   0		 1	   2...			  L1+2...
     *	+-------+-----+--------------+--------------------+
     *	|L1+L2+1|L1/L2| accent codes | pronunciation data |
     *	+-------+-----+--------------+--------------------+
     *	              |<-----L1----->|<--------L2-------->|
     *
     *	outbuf[0]				: number of total length (L1+L2+1)
     *	outbuf[1] upper 4 bits	: number of accent code
     *	outbuf[1] lower 4 bits	: mora number of pronunciation data
     *	outbuf[2]..				: accent codes
     *	outbuf[following]..		: pronunciation data
     */
    nbuf=outbuf[20]; 
	i=outbuf[1]; 
	di=outbuf+i+2; 
	si=(&outbuf[21]);
    outbuf[0]=nbuf+i+1; 
	outbuf[1]=nbuf+(i<<4);
    for (;nbuf--;) 
	{
        *di++=(*si++);
    }
    return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;hatsuon_mora
 * DESC: 	pronunciation ... mora
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int hatsuon_mora(uint8_t* ptr, uint8_t* buf)
{
    int n; uint8_t *top,len,a[3],ch;
    for (top=buf,len=0,buf++;*ptr;) 
	{
        a[0]=(*ptr); 
		a[1]=(*(ptr+1)); 
		a[2]=(*(ptr+2));
        /*
		*   If ptr exceeds the character string, 0x00 will be inserted.
		* In such cases, matching ends abnormally, n is increased by 1, and ptr is misaligned.
		* Then, *ptr is not 0x00, and the loop cannot be ended.
		*   To avoid it, fill 0xFF after 0x00.
		* This routine is only called at the dictionary registration, 
		* so consideration for speed is not required.
		*/
        if(a[1]==0x00) 
		{
            a[1]=a[2]=0xFF;
        } 
		else 
		{
            if (a[2]==0x00) 
			{
                a[2]=0xFF;
            }
        }
        for(n=3;n;) 
		{
            if(dispchar_to_code(a, &ch)) 
			{
                ptr += n; 
				goto hatsuon_mora100;
            }
            a[--n]=0x00;
        }
        return 0;
hatsuon_mora100:
		*buf++=ch; 
		++len;
    }
    *top=len;
    return 1;
}

//#ifdef WIN32
/*FUNCTION_HEADER**********************
 * NAME:	;u_read
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int u_read(int page, size_t size, void *addr)
{
#ifndef ARM7
    if (_lseek(jfd,((long)(page-1)*(long)PAGESIZE),0)==-1) 
	{
        perror("seek error");
        return errno;
    }
    if(_read(jfd,addr,size*PAGESIZE)==-1) 
	{
        perror("read error");
        return errno;
	}
#else
    if (FNX_FSEEK(jfd,((long)(page-1)*(long)PAGESIZE),0)==-1) 
	{
		return -1;
    }
    if(FNX_FREAD(addr,size,PAGESIZE,(FILE*)jfd)==-1) 
	{
		return -1;
	}
#endif
    return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;u_write
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int u_write(int page, size_t size, void* addr)
{
#ifndef ARM7
    if(_lseek(jfd,((long)(page-1)*(long)PAGESIZE),0)==-1) 
	{
        perror("seek error");
        return errno;
    }
#else
    if(FNX_FSEEK(jfd,((long)(page-1)*(long)PAGESIZE),0)==-1) 
	{
        return -1;
    }
#endif
#ifndef ARM7
    if(_write(jfd,addr,size*PAGESIZE)==-1) 
	{
        perror("write error\n");
        return errno;
	}
#else
    if(FNX_FWRITE(addr,size,PAGESIZE,jfd)==-1) 
	{
		return -1;
	}
#endif
    return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;u_alloc
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int u_alloc(void** addr, size_t size)
{
    size_t pages = size*PAGESIZE;
    if((*addr=(void *)FNX_MALLOC(pages))==NULL) 
	{
#ifndef ARM7
        FNX_FPRINTF(FNX_STDERR, "alloc error:%d\n", pages);
        return errno;
#else
		return -1;
#endif
    }
    return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;u_dealloc
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static void u_dealloc(void** addr)
{
    FNX_FREE(*addr);
    *addr = NULL;
}

/*FUNCTION_HEADER**********************
 * NAME:	;u_stop
 * DESC: 	function that discontinues conversion
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int u_stop(void*p) 
{
    return 0;
}

//#endif //WIN32

/*FUNCTION_HEADER**********************
 * NAME:	;Terminate
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int Terminate(LPVOID pVoid)
{
	onsei_term();
	return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;Initialize
 * DESC: 	Load the poly phone table needed for converting
			Hanzi characters with multiple possible pinyin+tone
 * IN:		phTTS
 * OUT:		none
 * RETURN:	0 on success, nonzero on failure
 * NOTES:	
 *END_HEADER***************************/
int Initialize(LPVOID pVoid)
{
//	int status;
#ifdef ARM7
	LPTTS_HANDLE_T phTTS = (LPTTS_HANDLE_T)pVoid;

	PLTS_T pLts_t = phTTS->pLTSThreadData;
	if( jfd != 0 )
		Terminate(NULL);

	return (Err_Fatal_DIC == onsei_init(phTTS->dict_path, pLts_t->j_inbuf, pLts_t->j_talkbuf, (uint16_t *)pLts_t->j_sentbuf, 0, u_stop));

#else
	PLTS_T pLts_t=(PLTS_T)pVoid;

	if( jfd != 0 )
		Terminate(NULL);

	return (Err_Fatal_DIC == onsei_init("onsei.dic", pLts_t->j_inbuf, pLts_t->j_talkbuf, (uint16_t *)pLts_t->j_sentbuf, 0, u_stop));
#endif //ARM7
}


/* End of stdonsei.c */

