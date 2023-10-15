/* **********************************************************************************
 *                			Copyright                         
 *
 *    Copyright © 2002 Fonix Coporation. All rights reserved.
 *
 *    This is an unpublished work, and is confidential and proprietary: 
 *    technology and information of Fonix corporation.  No part of this
 *    code may be reproduced, used or disclosed without written consent of 
 *    Fonix corporation in each and every instance.
 * ***********************************************************************************
 *  Rev Name    Date        Description
 *  --- -----   ----------- --------------------------------------------
 *	001	CAB		05/15/2002	Added copyright info
 *	002	MGS		04/14/2003	Fix for Epson Bug 5_3_001
 */

//moved to port.h for each platform - mlt
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#include "port.h"
#include "tts.h"
#include "kernel.h"
#include "cm_def.h"
//#include "ph_def.h"
#include "ph_defs.h"
#include "ph_data.h"
#include "setltslanguage.h"

extern const unsigned short parser_char_types[];

extern int cmd_loop(LPTTS_HANDLE_T phTTS,char input);
extern int send_pars_loop(LPTTS_HANDLE_T phTTS);
		
#include "epsonapi.h"
#include "cmdmain.h"

extern int vtm_main(LPTTS_HANDLE_T phTTS);
extern int ph_main(LPTTS_HANDLE_T phTTS);
extern int lts_main(LPTTS_HANDLE_T phTTS);
extern void DTSetSampleRate( LPTTS_HANDLE_T phTTS, unsigned int uiSampRate );
extern void usevoice (LPTTS_HANDLE_T phTTS, int voice);
#ifndef EPSON_ARM7
extern short cur_packet_number;
extern short max_packet_number;
#endif

#ifndef EPSON_ARM7
TTS_HANDLE_T hTTS;
LPTTS_HANDLE_T phTTS;
KSD_T Ksd_t;
int init_it=0;
#endif

typedef unsigned char U8;

char *g_user_dict;
short *(*g_callback)(short *,long);

#define get_long_int(ptr) ((U32)\
                       ((((U8 *)(ptr))[3] << 24)  | \
                        (((U8 *)(ptr))[2] << 16)  | \
                        (((U8 *)(ptr))[1] << 8)  | \
                        (((U8 *)(ptr))[0])))

#if defined ARM7 && !defined WIN32_TEST && !defined AD_VDSP
__align(8) 
#endif
extern const unsigned char main_dict[];

#define PC_SAMPLE_RATE 11025
#define MULAW_SAMPLE_RATE 8000

#ifdef EPSON_ARM7

#if defined ARM7 && !defined WIN32_TEST && !defined AD_VDSP
__align(8) 
#endif
extern const unsigned char sp_main_dict[];
#if defined ARM7 && !defined WIN32_TEST && !defined AD_VDSP
__align(8) 
#endif
extern const unsigned char us_main_dict[];
#if defined ARM7 && !defined WIN32_TEST && !defined AD_VDSP
__align(8) 
#endif
extern const unsigned char gr_main_dict[];
#if defined ARM7 && !defined WIN32_TEST && !defined AD_VDSP
__align(8) 
#endif
extern const unsigned char la_main_dict[];
#if defined ARM7 && !defined WIN32_TEST && !defined AD_VDSP
__align(8) 
#endif
extern const unsigned char uk_main_dict[];
#if defined ARM7 && !defined WIN32_TEST && !defined AD_VDSP
__align(8) 
#endif
extern const unsigned char fr_main_dict[];
#if defined ARM7 && !defined WIN32_TEST && !defined AD_VDSP
__align(8) 
#endif
extern const unsigned char it_main_dict[];

extern const short paul[];
extern const short us_paul_tune[];
extern const short fr_paul_tune[];
extern const short default_tune[];
extern const short fr_default_tune[];

extern void us_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void uk_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void gr_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void fr_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void sp_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void la_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void it_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);

extern int us_lts_main(LPTTS_HANDLE_T phTTS);
extern int uk_lts_main(LPTTS_HANDLE_T phTTS);
extern int gr_lts_main(LPTTS_HANDLE_T phTTS);
extern int fr_lts_main(LPTTS_HANDLE_T phTTS);
extern int sp_lts_main(LPTTS_HANDLE_T phTTS);
extern int la_lts_main(LPTTS_HANDLE_T phTTS);
extern int it_lts_main(LPTTS_HANDLE_T phTTS);

lts_func_t *load_lts_language(int lang_num);

BOOL TextToSpeechSelectLang(LPTTS_HANDLE_T tts, unsigned int id) 
{
	int temp_l=0;
	if (id>=MAX_languages)
		return FALSE;
	if (tts!=NULL)
	{
		if (tts->lts_funcs[id]==NULL)
		{
				return FALSE;
		}
		tts->cur_lts_lang=id;
		if (tts->pKernelShareData->only_lts==0)
			tts->pKernelShareData->lang_curr=id;

		if (tts->pKernelShareData->only_lts==1)
		{
			temp_l=tts->pKernelShareData->lang_curr;
			tts->pKernelShareData->lang_curr=id;
		}

		usa_init(tts->pKernelShareData);
		if (tts->pKernelShareData->only_lts==1)
		{
			tts->pKernelShareData->lang_curr=temp_l;
		}
		return(TRUE);
	}

	return TRUE;
}


int TextToSpeechSetLanguage( LPTTS_HANDLE_T phTTS,
								 int Language )
{
	lts_func_t *temp_funcs;
	char lang[5];
	int ret=0,ret2=0;
	PVOID ptemp=NULL;
	int old_lang=0;
	/********************************************************************/
	/*  Return error if invalid handle.                                 */
	/********************************************************************/
	

	temp_funcs=load_lts_language(Language);
	if (temp_funcs==NULL)
		return -1;

	ret=TextToSpeechSelectLang(phTTS,Language);


	phTTS->lts_funcs[Language]=temp_funcs;

	phTTS->cur_lts_lang=Language;

	phTTS->lts_funcs[Language]->ml_lts_main(phTTS);

	TextToSpeechSelectLang(phTTS,Language);

	return(0);

}


int TextToSpeechSetLTSLanguage( LPTTS_HANDLE_T phTTS,
								int Language )
{
	lts_func_t *temp_funcs;
	char lang[5];
	int ret=0,ret2=0;
	PVOID ptemp=NULL;
	int old_lang=0;
	/********************************************************************/
	/*  Return error if invalid handle.                                 */
	/********************************************************************/
	
	

	temp_funcs=load_lts_language(Language);
	if (temp_funcs==NULL)
		return -1;
		
	phTTS->lts_funcs[Language]=temp_funcs;

	phTTS->cur_lts_lang=Language;

	phTTS->lts_funcs[Language]->ml_lts_main(phTTS);

	phTTS->pKernelShareData->only_lts=1;
	ret=TextToSpeechSelectLang(phTTS,Language);
	phTTS->pKernelShareData->only_lts=0;
			
	return(0);

}

lts_func_t *load_lts_language(int lang_num)
{

	if (lang_num==LANG_english)
	{
		return(us_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_british)
	{
		return(uk_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_german)
	{
		return(gr_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_spanish)
	{
		return(sp_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_latin_american)
	{
		return(la_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_italian)
	{
		return(it_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_french)
	{
		return(fr_ls_main_get_lts_funcs());
	} 
#if 0
	else if (lang_num==LANG_chinese)
	{
		return(ch_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_japanese)
	{
		return(jp_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_korean)
	{
		return(kr_ls_main_get_lts_funcs());
	} 
#endif
	else
	{
		return(us_ls_main_get_lts_funcs());
	}


}




/* ******************************************************************
 *      Function Name: TextToSpeechInitTTP()
 *
 *      Description: 
 *
 *      Arguments:	short *(*callback)(short*,long)
 *					void *user_dict
 *
 *      Return Value: int
 *
 *      Comments:
 *
 * *****************************************************************/
int TextToSpeechInitTTP(LPTTS_HANDLE_T phTTS, PKSD_T pKsd_t, 
						PCMD_T pCmd_t, PLTS_T pLts_t, void *user_dict,
						U16 lang_id,U16 reset_all)
{
	int return_code;
	int i;
	int new_lang=0;
	int temp;

	char *maindict;
	
//	PKSD_T pKsd_t;
	if (reset_all)
	{
		memset(phTTS,0,sizeof(TTS_HANDLE_T));
		memset(pKsd_t,0,sizeof(KSD_T));
	}
	
//	phTTS->EmbCallbackRoutine=callback;
	phTTS->pKernelShareData=pKsd_t;
	phTTS->pCMDThreadData=pCmd_t;
	phTTS->pLTSThreadData=pLts_t;

	phTTS->ph_funcs.ph_loop=ph_loop;
	phTTS->ph_funcs.char_types=char_types;
	phTTS->ph_funcs.parser_char_types=parser_char_types;
	phTTS->ph_funcs.default_lang=default_lang;



//	g_callback=callback;
	g_user_dict=(char *)user_dict;

	if (pKsd_t->lang_curr !=lang_id)
		new_lang=1;

	pKsd_t->lang_curr=lang_id;

	phTTS->cur_lts_lang=pKsd_t->lang_curr;
//	pKsd_t->lang_curr=phTTS->cur_lts_lang;

	switch (pKsd_t->lang_curr)
	{

	case LANG_english:
		phTTS->lts_funcs[phTTS->cur_lts_lang]=us_ls_main_get_lts_funcs();
		break;
	case LANG_french:
		phTTS->lts_funcs[phTTS->cur_lts_lang]=fr_ls_main_get_lts_funcs();
		break;
	case LANG_german:
		phTTS->lts_funcs[phTTS->cur_lts_lang]=gr_ls_main_get_lts_funcs();
		break;
	case LANG_spanish:
		phTTS->lts_funcs[phTTS->cur_lts_lang]=sp_ls_main_get_lts_funcs();
		break;
	case LANG_british:
		phTTS->lts_funcs[phTTS->cur_lts_lang]=uk_ls_main_get_lts_funcs();
		break;
	case LANG_latin_american:
		phTTS->lts_funcs[phTTS->cur_lts_lang]=la_ls_main_get_lts_funcs();
		break;
	case LANG_italian:
		phTTS->lts_funcs[phTTS->cur_lts_lang]=it_ls_main_get_lts_funcs();
		break;		
	}



	switch (pKsd_t->lang_curr)
	{

	case LANG_english:
		phTTS->main_lts_loop=us_lts_loop;
		break;
	case LANG_french:
		phTTS->main_lts_loop=fr_lts_loop;
		break;
	case LANG_german:
		phTTS->main_lts_loop=gr_lts_loop;
		break;
	case LANG_spanish:
		phTTS->main_lts_loop=sp_lts_loop;
		break;
	case LANG_british:
		phTTS->main_lts_loop=uk_lts_loop;
		break;
	case LANG_latin_american:
		phTTS->main_lts_loop=la_lts_loop;
		break;
	case LANG_italian:
		phTTS->main_lts_loop=it_lts_loop;
		break;		
	}

	
//	for (i=0; i < MAX_languages; ++i)
	{
		i=lang_id;
		pKsd_t->adic_index[i] = 0;
		pKsd_t->udic_index[i] = 0;
		pKsd_t->fdic_index[i] = 0;
		pKsd_t->adic_data[i] = 0;
		pKsd_t->udic_data[i] = 0;
		pKsd_t->fdic_data[i] = 0;
		pKsd_t->adic_bytes[i] = 0;
		pKsd_t->udic_bytes[i] = 0;
		pKsd_t->fdic_bytes[i] = 0;
		pKsd_t->adic_entries[i] = 0;
		pKsd_t->udic_entries[i] = 0;
		pKsd_t->fdic_entries[i] = 0;
		pKsd_t->fdic_fc_entry[i]=0;
		pKsd_t->fdic_fc_entries[i]=0;
	}

	/* user dictionary load */
	if (user_dict)
	{
		pKsd_t->udic_entries[lang_id]=get_long_int((char *)user_dict);
		if (pKsd_t->udic_entries[lang_id])
		{
			pKsd_t->udic_bytes[lang_id]=get_long_int((char *)user_dict+4);
			pKsd_t->udic_index[lang_id]=((char *)user_dict)+8;
			pKsd_t->udic_data[lang_id]=((char *)user_dict)+(pKsd_t->udic_entries[lang_id]*4)+8;
		}
	}
	
	switch (lang_id)
	{	
	case LANG_ENGLISH_US:
		maindict=us_main_dict;
		break;
	case LANG_SPANISH:
		maindict=sp_main_dict;
		break;
	case LANG_GERMAN:
		maindict=gr_main_dict;
		break;
	case LANG_LATIN_AMERICAN:
		maindict=la_main_dict;
		break;
	case LANG_ENGLISH_UK:
		maindict=uk_main_dict;
		break;
	case LANG_FRENCH:
		maindict=fr_main_dict;
		break;
	case LANG_ITALIAN:
		maindict=it_main_dict;
		break;
	}


	/* main dictioanry load */
	if (maindict)
	{
		pKsd_t->fdic_entries[lang_id]=get_long_int(maindict);
		if (pKsd_t->fdic_entries[lang_id])
		{
			pKsd_t->fdic_bytes[lang_id]=get_long_int(maindict+4);
			pKsd_t->fdic_fc_entries[lang_id]=get_long_int(maindict+8);
			pKsd_t->fdic_fc_entry[lang_id]=(maindict+12);
			pKsd_t->fdic_index[lang_id]=(maindict+12+((pKsd_t->fdic_fc_entries[lang_id])*4));
			pKsd_t->fdic_data[lang_id]=(maindict+((pKsd_t->fdic_entries[lang_id]+3)*4) + ((pKsd_t->fdic_fc_entries[lang_id])*4));
		}
	}

	pKsd_t->phTTS = phTTS;

	
	if (reset_all)
	{
	pKsd_t->cmd_flush = FALSE;
	pKsd_t->spc_flush = FALSE;
	pKsd_t->halting = FALSE;
	pKsd_t->logflag  = 0;
	/* GL 11/15/1996 set defaulted Spanish to Latin */
	pKsd_t->modeflag = MODE_CITATION;
	pKsd_t->sayflag = SAY_CLAUSE;
	pKsd_t->pronflag = 0;
	pKsd_t->wbreak = FALSE;
	pKsd_t->text_flush = FALSE;
	pKsd_t->async_change = FALSE;
	pKsd_t->SamplePeriod = 9.07029478458E-5 ;  /* Initialize sample period */
	pKsd_t->spc_pkt_save = NULL_SPC_PACKET;
	pKsd_t->loaded_languages = NULL;           //MVP:05/10/96 Fixed an exception(When DECtalk runs on a machine without audio card)
	pKsd_t->volume=100; //set volume to 100;
	pKsd_t->vol_att=100; //set volume to 100;
	pKsd_t->vol_tone=100; //set volume to 100;
	
	phTTS->uiCurrentMsgNumber = 1;
	phTTS->uiLastTextMsgNumber = 0;
	phTTS->uiFlushMsgNumber = 0;
	}
	

#ifndef EPSON_ARM7
	cur_packet_number=0;
	max_packet_number=0;
#endif

//	return_code=vtm_main(phTTS);
//	if (return_code)
//		return(ERR_ERROR);
//	return_code=ph_main(phTTS);
//	if (return_code)
//		return(ERR_ERROR);
	// load_user_dictionary here...

	if (reset_all || new_lang)
	{
	switch (lang_id)
	{
	case LANG_ENGLISH_US: 
		return_code=us_lts_main(phTTS);
		break;
	case LANG_SPANISH:
		return_code=sp_lts_main(phTTS);
		break;
	case LANG_ENGLISH_UK:
		return_code=uk_lts_main(phTTS);
		break;
	case LANG_GERMAN:
		return_code=gr_lts_main(phTTS);
		break;
	case LANG_LATIN_AMERICAN:
		return_code=la_lts_main(phTTS);
		break;
		/* Fix for Epson Bug 5_3_001 */
	case LANG_FRENCH:
		return_code=fr_lts_main(phTTS);
		break;
	case LANG_ITALIAN:
		return_code=it_lts_main(phTTS);
		break;
	}
	if (return_code)
		return(ERR_ERROR);
	}

	return_code=cmd_main(phTTS);
	if (return_code)
		return(ERR_ERROR);
//	DTSetSampleRate( phTTS, PC_SAMPLE_RATE );

	return(ERR_NOERROR);
}

int TextToSpeechInitPTS(LPTTS_HANDLE_T phTTS, PKSD_T pKsd_t, 
						PDPH_T pDph_t, PDPHSETTAR_ST pDphsettar,
						PVTM_T pVtm_t, SPEAKER_DEF_T **spdef_ptr, U16 output_format, 
						U16 reset_all)
{
	int return_code;
	int i;

//	PKSD_T pKsd_t;
//	memset(phTTS,0,sizeof(TTS_HANDLE_T));
//	memset(pKsd_t,0,sizeof(KSD_T));
	
//	phTTS->EmbCallbackRoutine=callback;
	phTTS->pKernelShareData=pKsd_t;
	phTTS->pPHThreadData=pDph_t;
	pDph_t->pSTphsettar=pDphsettar;
	phTTS->pVTMThreadData=pVtm_t;
	phTTS->PTS_location=0;
	phTTS->PTS_input_pos=0;

	phTTS->ph_funcs.ph_loop=ph_loop;
	phTTS->ph_funcs.char_types=char_types;
	phTTS->ph_funcs.parser_char_types=parser_char_types;
	phTTS->ph_funcs.default_lang=default_lang;


//	g_callback=callback;
//	g_user_dict=(char *)user_dict;
	

	pKsd_t->phTTS = phTTS;

#ifndef EPSON_ARM7
	cur_packet_number=0;
	max_packet_number=0;
#endif
	
	if (reset_all)
	{
		return_code=vtm_main(phTTS);
		if (return_code)
			return(ERR_ERROR);
		return_code=ph_main(phTTS);
		if (return_code)
			return(ERR_ERROR);
	}
	if (pKsd_t->lang_curr==LANG_FRENCH)
	{
		for (i=0;i<10;i++)
		{	
			if (spdef_ptr==NULL)
			{
				pDph_t->voidef[i]=paul;
				pDph_t->tunedef[i]=us_paul_tune;
				pDph_t->voidef_8[i]=paul;
				pDph_t->tunedef_8[i]=us_paul_tune;
			}
			else if (spdef_ptr[i]==NULL)
			{
				pDph_t->voidef[i]=paul;
				pDph_t->tunedef[i]=us_paul_tune;
				pDph_t->voidef_8[i]=paul;
				pDph_t->tunedef_8[i]=us_paul_tune;
			}
			else
			{
				pDph_t->voidef[i]=spdef_ptr[i];
				pDph_t->tunedef[i]=default_tune;
				pDph_t->voidef_8[i]=spdef_ptr[i];
				pDph_t->tunedef_8[i]=default_tune;			}
		}
	}
	else
	{
		for (i=0;i<10;i++)
		{	
			if (spdef_ptr==NULL)
			{
				pDph_t->voidef[i]=paul;
				pDph_t->tunedef[i]=us_paul_tune;
				pDph_t->voidef_8[i]=paul;
				pDph_t->tunedef_8[i]=us_paul_tune;
			}
			else if (spdef_ptr[i]==NULL)
			{
				pDph_t->voidef[i]=paul;
				pDph_t->tunedef[i]=us_paul_tune;
				pDph_t->voidef_8[i]=paul;
				pDph_t->tunedef_8[i]=us_paul_tune;
			}
			else
			{
				pDph_t->voidef[i]=spdef_ptr[i];
				pDph_t->tunedef[i]=default_tune;
				pDph_t->voidef_8[i]=spdef_ptr[i];
				pDph_t->tunedef_8[i]=default_tune;
			}
		}
	}

	if (reset_all)
	{
		usevoice (phTTS, 0);
	}
	// load_user_dictionary here...
//	return_code=lts_main(phTTS);
//	if (return_code)
//		return(ERR_ERROR);
//	return_code=cmd_main(phTTS);
//	if (return_code)
//		return(ERR_ERROR);
		
//	DTSetSampleRate( phTTS, PC_SAMPLE_RATE );
	switch(output_format)
	{
		case WAVE_FORMAT_1M16:
			if (phTTS->pKernelShareData->uiSampleRate==MULAW_SAMPLE_RATE)
			{
				DTSetSampleRate( phTTS, PC_SAMPLE_RATE );
			}
			break;
		case WAVE_FORMAT_08M16:
			if (phTTS->pKernelShareData->uiSampleRate==PC_SAMPLE_RATE)
			{
				DTSetSampleRate( phTTS, MULAW_SAMPLE_RATE );
			}
			break;
	}

	((PDPH_T)(phTTS->pPHThreadData))->loadspdef=1;

	return(ERR_NOERROR);
}

#else
/* ******************************************************************
 *      Function Name: TextToSpeechInit()
 *
 *      Description: 
 *
 *      Arguments:	short *(*callback)(short*,long)
 *					void *user_dict
 *
 *      Return Value: int
 *
 *      Comments:
 *
 * *****************************************************************/
int TextToSpeechInit(short *(*callback)(short *,long), void *user_dict)
{
	int return_code;
	int i;

	PKSD_T pKsd_t;
	memset(&hTTS,0,sizeof(TTS_HANDLE_T));
	memset(&Ksd_t,0,sizeof(KSD_T));
	
	phTTS=&hTTS;
	phTTS->EmbCallbackRoutine=callback;
	phTTS->pKernelShareData=&Ksd_t;
	pKsd_t=&Ksd_t;

	g_callback=callback;
	g_user_dict=(char *)user_dict;
	
	for (i=0; i < MAX_languages; ++i)
	{
		pKsd_t->adic_index[i] = 0;
		pKsd_t->udic_index[i] = 0;
		pKsd_t->fdic_index[i] = 0;
		pKsd_t->adic_data[i] = 0;
		pKsd_t->udic_data[i] = 0;
		pKsd_t->fdic_data[i] = 0;
		pKsd_t->adic_bytes[i] = 0;
		pKsd_t->udic_bytes[i] = 0;
		pKsd_t->fdic_bytes[i] = 0;
		pKsd_t->adic_entries[i] = 0;
		pKsd_t->udic_entries[i] = 0;
		pKsd_t->fdic_entries[i] = 0;
		pKsd_t->fdic_fc_entry[i]=0;
		pKsd_t->fdic_fc_entries[i]=0;
	}
	
	/* user dictionary load */
	if (user_dict)
	{
		pKsd_t->udic_entries[0]=get_long_int((char *)user_dict);
		if (pKsd_t->udic_entries[0])
		{
			pKsd_t->udic_bytes[0]=get_long_int((char *)user_dict+4);
			pKsd_t->udic_index[0]=((char *)user_dict)+8;
			pKsd_t->udic_data[0]=((char *)user_dict)+(pKsd_t->udic_entries[0]*4)+8;
		}
	}
	
	/* main dictioanry load */
	if (main_dict)
	{
		pKsd_t->fdic_entries[0]=get_long_int(main_dict);
		if (pKsd_t->fdic_entries[0])
		{
			pKsd_t->fdic_bytes[0]=get_long_int(main_dict+4);
			pKsd_t->fdic_fc_entries[0]=get_long_int(main_dict+8);
			pKsd_t->fdic_fc_entry[0]=(main_dict+12);
			pKsd_t->fdic_index[0]=(main_dict+12+((pKsd_t->fdic_fc_entries[0])*4));
			pKsd_t->fdic_data[0]=(main_dict+((pKsd_t->fdic_entries[0]+3)*4) + ((pKsd_t->fdic_fc_entries[0])*4));
		}
	}
		
	pKsd_t->cmd_flush = FALSE;
	pKsd_t->spc_flush = FALSE;
	pKsd_t->halting = FALSE;
	pKsd_t->logflag  = 0;
	/* GL 11/15/1996 set defaulted Spanish to Latin */
#ifdef ACCESS_SOLUTIONS
	pKsd_t->modeflag = MODE_CITATION | MODE_READING;
#else
	pKsd_t->modeflag = MODE_CITATION;
#endif
	pKsd_t->sayflag = SAY_CLAUSE;
	pKsd_t->pronflag = 0;
	pKsd_t->wbreak = FALSE;
	pKsd_t->text_flush = FALSE;
	pKsd_t->async_change = FALSE;
	pKsd_t->SamplePeriod = 9.07029478458E-5 ;  /* Initialize sample period */
	pKsd_t->spc_pkt_save = NULL_SPC_PACKET;
	pKsd_t->loaded_languages = NULL;           //MVP:05/10/96 Fixed an exception(When DECtalk runs on a machine without audio card)
	pKsd_t->volume=100; //set volume to 100;
	pKsd_t->vol_att=100; //set volume to 100;
	pKsd_t->vol_tone=100; //set volume to 100;

	pKsd_t->phTTS = phTTS;

#ifdef ENGLISH_US
	pKsd_t->lang_curr = LANG_english;
#endif	/* ENGLISH_US */
#ifdef ENGLISH_UK
	pKsd_t->lang_curr = LANG_british;
#endif	/* ENGLISH_UK */
#ifdef SPANISH_SP
	pKsd_t->lang_curr = LANG_spanish;
#endif	/* SPANISH_SP */
#ifdef SPANISH_LA
	pKsd_t->lang_curr = LANG_latin_american;
#endif	/* SPANISH_LA */
#ifdef GERMAN
	pKsd_t->lang_curr = LANG_german;
#endif	/* GERMAN */
#ifdef FRENCH
	pKsd_t->lang_curr = LANG_french;
#endif	/* FRENCH */
#ifdef ITALIAN
	pKsd_t->lang_curr = LANG_italian;
#endif
#ifdef JAPANESE
	pKsd_t->lang_curr = LANG_japanese;
#endif
#ifdef HEBREW
	pKsd_t->lang_curr = LANG_hebrew;
#endif
#ifdef CHINESE
	pKsd_t->lang_curr = LANG_chinese;
#endif
#ifdef KOREAN
	pKsd_t->lang_curr = LANG_korean;
#endif

	
	
	phTTS->uiCurrentMsgNumber = 1;
	phTTS->uiLastTextMsgNumber = 0;
	phTTS->uiFlushMsgNumber = 0;
	
	cur_packet_number=0;
	max_packet_number=0;

	
	return_code=vtm_main(phTTS);
	if (return_code)
		return(ERR_ERROR);
	return_code=ph_main(phTTS);
	if (return_code)
		return(ERR_ERROR);
	// load_user_dictionary here...
	return_code=lts_main(phTTS);
	if (return_code)
		return(ERR_ERROR);
	return_code=cmd_main(phTTS);
	if (return_code)
		return(ERR_ERROR);
		
	((PDPH_T)(phTTS->pPHThreadData))->loadspdef=1;
		
	DTSetSampleRate( phTTS, PC_SAMPLE_RATE );

	return(ERR_NOERROR);
}
#endif
/* ******************************************************************
 *      Function Name: TextToSpeechReset()
 *
 *      Description: 
 *
 *      Arguments:	void
 *
 *      Return Value: int
 *
 *      Comments:
 *
 * *****************************************************************/
#ifdef EPSON_ARM7
int TextToSpeechReset(LPTTS_HANDLE_T phTTS)
{
	phTTS->pKernelShareData->halting=1;
	return(ERR_NOERROR);
}
#else
#ifdef ACCESS_SOLUTIONS
int TextToSpeechReset(int do_flush)
{
	phTTS->pKernelShareData->halting=1;
	if (do_flush)
		phTTS->pKernelShareData->just_flushed=1;
	else
		phTTS->pKernelShareData->just_flushed=0;
	return(ERR_NOERROR);
}
#else
int TextToSpeechReset(void)
{
	phTTS->pKernelShareData->halting=1;
	phTTS->pKernelShareData->just_flushed=0;
	return(ERR_NOERROR);
}
#endif
#endif

#ifdef EPSON_ARM7
/* ******************************************************************
 *      Function Name: TextToSpeechStart()
 *
 *      Description: 
 *
 *      Arguments:	char *input
 *					short *buffer
 *					int output_format
 *
 *      Return Value: int
 *
 *      Comments:
 *
 * *****************************************************************/
int TextToSpeechStartTTP(LPTTS_HANDLE_T phTTS,char *input_text, 
						 S16 *ctrl_phoneme_ptr, 
						 S16 ctrl_phoneme_buff_length, 
						 char **input_text_ptr)
{
//	int i;
	
	if (phTTS->pKernelShareData->halting)
	{
		return -ERR_RESET;
	}
	phTTS->pKernelShareData->halting=0;
	phTTS->TTP_return_code=0;
	phTTS->TTP_return=0;
	cm_cmd_reset_comm(phTTS->pCMDThreadData, STATE_NORMAL);
	
	phTTS->TTP_phoneme_buf_len=ctrl_phoneme_buff_length;
	phTTS->TTP_phoneme_buf=ctrl_phoneme_ptr;

	*input_text_ptr=input_text;
	while (**input_text_ptr)
	{
		cmd_loop(phTTS,**input_text_ptr);
		(*input_text_ptr)++;
		if (phTTS->pKernelShareData->halting)
		{
//			TextToSpeechInit(g_callback,g_user_dict);
			return -ERR_RESET;
		}
		if (phTTS->TTP_return)
		{
			if (((PCMD_T)(phTTS->pCMDThreadData))->parse_state!=STATE_NORMAL)
			{
				continue;
			}
			return(phTTS->TTP_return_code);
		}
		if (phTTS->TTP_return_code>=ctrl_phoneme_buff_length)
		{
			return(-ERR_PHONEME_BUF_TOO_SHORT);
		}
	}
	cmd_loop(phTTS,0x0B); // force it
	if (phTTS->pKernelShareData->halting)
	{
//		TextToSpeechInit(g_callback,g_user_dict);
		return -ERR_RESET;
	}
	if (phTTS->TTP_return)
	{
		return(phTTS->TTP_return_code);
	}
	if (phTTS->TTP_return_code>=ctrl_phoneme_buff_length)
	{
		return(-ERR_PHONEME_BUF_TOO_SHORT);
	}
	return(phTTS->TTP_return_code);
}

#define PTS_BACKUP_ONE_PHONE	6
#define PTS_DONE_WITH_CLAUSE	5
#define PTS_BUFFER_FILLED		4
#define PTS_DONE_WITH_PHONEMES	3
#define PTS_SEND_PARS_LOOP		2
#define PTS_PH_LOOP				1
#define PTS_START				0

int TextToSpeechStartPTS(LPTTS_HANDLE_T phTTS,S16 *ctrl_phoneme_ptr,
						 S16 ctrl_phoneme_buff_length,
						 short *output_buffer)
{

//	int i;
	int nextra;
	if (phTTS->pKernelShareData->halting)
	{
		return ERR_RESET;
	}
	phTTS->pKernelShareData->halting=0;

	if (phTTS->pKernelShareData->uiSampleRate==MULAW_SAMPLE_RATE)
	{
		memset(output_buffer,0,51*2);
	}
	else
	{
		memset(output_buffer,0,71*2);
	}

	if (ctrl_phoneme_buff_length==0)
	{
		return(PTS_DONE);
	}

	if (phTTS->PTS_location==PTS_DONE_WITH_PHONEMES || phTTS->PTS_location==PTS_START)
	{
		phTTS->PTS_phoneme_buf_len=ctrl_phoneme_buff_length;
		phTTS->PTS_phoneme_buf=ctrl_phoneme_ptr;
		phTTS->PTS_input_pos=0;
		phTTS->PTS_location=PTS_PH_LOOP;
	}
	
	phTTS->PTS_return_code=0;
	phTTS->PTS_return=0;


	phTTS->output_buffer=output_buffer;
	
	
	if (phTTS->PTS_location==PTS_PH_LOOP)
	{
		while (phTTS->PTS_input_pos<phTTS->PTS_phoneme_buf_len)
		{
			ph_loop(phTTS,&phTTS->PTS_phoneme_buf[phTTS->PTS_input_pos]);
			if (phTTS->PTS_special_change!=PTS_BACKUP_ONE_PHONE)
			{
				nextra=(((phTTS->PTS_phoneme_buf[phTTS->PTS_input_pos])&PNEXTRA) >> PSNEXTRA)+1;
				phTTS->PTS_input_pos+=nextra;
				phTTS->PTS_special_change=0;
			}
			if (phTTS->pKernelShareData->halting)
			{
//				TextToSpeechInit(g_callback,g_user_dict);
				return ERR_RESET;
			}
			if (phTTS->PTS_return_code==PTS_SEND_PARS_LOOP)
			{
				phTTS->PTS_location=PTS_SEND_PARS_LOOP;
				break;
			}
			if (phTTS->PTS_return_code==PTS_BUFFER_FILLED)
			{
				phTTS->PTS_location=PTS_SEND_PARS_LOOP;
				return(PTS_OUTPUT);
			}
			if (phTTS->PTS_input_pos>=phTTS->PTS_phoneme_buf_len)
			{
				phTTS->PTS_location=PTS_START;
				return(PTS_DONE);
			}
		}
	}
	if (phTTS->PTS_location==PTS_SEND_PARS_LOOP)
	{
		send_pars_loop(phTTS);
		if (phTTS->PTS_return_code==PTS_DONE_WITH_CLAUSE)
		{
			if (phTTS->PTS_input_pos>=phTTS->PTS_phoneme_buf_len)
			{
				phTTS->PTS_location=PTS_START;
				return(PTS_DONE);
			}
			else
			{
				phTTS->PTS_location=PTS_PH_LOOP;
				return(PTS_OUTPUT);
			}
			return(PTS_OUTPUT);
		}
		if (phTTS->PTS_return_code==PTS_BUFFER_FILLED)
		{
			return(PTS_OUTPUT);
		}
	}
	return ERR_ERROR;
}


#else
/* ******************************************************************
 *      Function Name: TextToSpeechStart()
 *
 *      Description: 
 *
 *      Arguments:	char *input
 *					short *buffer
 *					int output_format
 *
 *      Return Value: int
 *
 *      Comments:
 *
 * *****************************************************************/
#ifdef ACCESS_SOLUTIONS
int DTinput_counter=0;
int *TextToSpeechGetInputCounterPointer(void)
{
	return(&DTinput_counter);
}
#endif


#ifdef ACCESS_SOLUTIONS
int TextToSpeechStart(char *input, short *buffer, int output_format, int force_it)
#else
int TextToSpeechStart(char *input, short *buffer, int output_format)
#endif
{
#ifndef ACCESS_SOLUTIONS
	int DTinput_counter=0;
#endif
	int temp=0;
	int oldrate=0;
	int oldspeaker=0;
	int oldsprate=0;
	short oldap[SPDEF];
	int old_volatt=0;
	int old_voltone=0;
	int old_modeflag=0;
	int old_sayflag=0;
	int old_pronflag=0;
	int old_error_mode=0;
	int old_punct_mode=0;
	int old_skip_mode=0;
	int old_compause=0;
	int old_perpause=0;
	int old_phoneme_mode=0;
	
	PDPH_T pDph_t=phTTS->pPHThreadData;
	PCMD_T pCmd_t=phTTS->pCMDThreadData;
	PKSD_T pKsd_t=phTTS->pKernelShareData;
	if (pKsd_t->halting)
	{
		temp=0;
		oldrate=pKsd_t->uiSampleRate;
		oldspeaker=pKsd_t->last_voice;
		if (pKsd_t->just_flushed)
		{
			oldsprate=pKsd_t->sprate;
			memcpy(oldap,pDph_t->curspdef,SPDEF*sizeof(short));
			old_volatt=pKsd_t->vol_att;
			old_voltone=pKsd_t->vol_tone;
			old_modeflag = pKsd_t->modeflag;
			old_sayflag = pKsd_t->sayflag;
			old_pronflag =pKsd_t->pronflag;
			old_error_mode=pCmd_t->error_mode;
			old_punct_mode=pCmd_t->punct_mode;
			old_skip_mode=pCmd_t->skip_mode;
			old_perpause=pDph_t->perpause;
			old_compause=pDph_t->compause;
			old_phoneme_mode=pKsd_t->phoneme_mode;
			temp=1;
		}

		TextToSpeechInit(g_callback,g_user_dict);
		if (oldrate!=pKsd_t->uiSampleRate &&
		    output_format==0)
		{
			DTSetSampleRate( phTTS, MULAW_SAMPLE_RATE );
		}
		if (temp==0)
		{
			usevoice(phTTS,oldspeaker);
		}
		else
		{
			memcpy(pDph_t->curspdef,oldap,SPDEF*sizeof(short));
			pDph_t->loadspdef=1;
			pKsd_t->last_voice=oldspeaker;
			pKsd_t->async_voice=oldspeaker;
			pKsd_t->async_change &= (~ASYNC_voice);
			pKsd_t->sprate=oldsprate;
			pKsd_t->vol_att=old_volatt;
			pKsd_t->vol_tone=old_voltone;
			pKsd_t->modeflag=old_modeflag;
			pKsd_t->sayflag=old_sayflag;
			pKsd_t->pronflag=old_pronflag;
			pCmd_t->error_mode=old_error_mode;
			pCmd_t->punct_mode=old_punct_mode;
			pCmd_t->skip_mode=old_skip_mode;
			pDph_t->perpause=old_perpause;
			pDph_t->compause=old_compause;
			pKsd_t->phoneme_mode=old_phoneme_mode;
			temp=0;
		}
	}


	((PDPH_T)(phTTS->pPHThreadData))->loadspdef=1;

	phTTS->output_buffer=buffer;
	pKsd_t->halting=0;
	cm_cmd_reset_comm(phTTS->pCMDThreadData, STATE_NORMAL);
	
	switch(output_format)
	{
		case WAVE_FORMAT_1M16:
			memset(buffer,0,71*2);
			if (pKsd_t->uiSampleRate==MULAW_SAMPLE_RATE)
			{
				DTSetSampleRate( phTTS, PC_SAMPLE_RATE );
			}
			break;
		case WAVE_FORMAT_08M16:
			memset(buffer,0,51*2);
			if (pKsd_t->uiSampleRate==PC_SAMPLE_RATE)
			{
				DTSetSampleRate( phTTS, MULAW_SAMPLE_RATE );
			}
			break;
	}

	DTinput_counter=0;
	while (input[DTinput_counter])
	{
		cmd_loop(phTTS,input[DTinput_counter]);
		if (pKsd_t->halting)
		{
			temp=0;
			oldrate=pKsd_t->uiSampleRate;
			oldspeaker=pKsd_t->last_voice;
			if (pKsd_t->just_flushed)
		{
				oldsprate=pKsd_t->sprate;
				memcpy(oldap,pDph_t->curspdef,SPDEF*sizeof(short));
				old_volatt=pKsd_t->vol_att;
				old_voltone=pKsd_t->vol_tone;
				old_modeflag = pKsd_t->modeflag;
				old_sayflag = pKsd_t->sayflag;
				old_pronflag =pKsd_t->pronflag;
				old_error_mode=pCmd_t->error_mode;
				old_punct_mode=pCmd_t->punct_mode;
				old_skip_mode=pCmd_t->skip_mode;
				old_perpause=pDph_t->perpause;
				old_compause=pDph_t->compause;
				old_phoneme_mode=pKsd_t->phoneme_mode;
				temp=1;
			}

			TextToSpeechInit(g_callback,g_user_dict);
			if (oldrate!=pKsd_t->uiSampleRate &&
			    output_format==0)
			{
				DTSetSampleRate( phTTS, MULAW_SAMPLE_RATE );
			}
			if (temp==0)
			{
				usevoice(phTTS,oldspeaker);
			}
			else
			{
				memcpy(pDph_t->curspdef,oldap,SPDEF*sizeof(short));
				pDph_t->loadspdef=1;
				pKsd_t->last_voice=oldspeaker;
				pKsd_t->async_voice=oldspeaker;
				pKsd_t->async_change &= (~ASYNC_voice);
				pKsd_t->sprate=oldsprate;
				pKsd_t->vol_att=old_volatt;
				pKsd_t->vol_tone=old_voltone;
				pKsd_t->modeflag=old_modeflag;
				pKsd_t->sayflag=old_sayflag;
				pKsd_t->pronflag=old_pronflag;
				pCmd_t->error_mode=old_error_mode;
				pCmd_t->punct_mode=old_punct_mode;
				pCmd_t->skip_mode=old_skip_mode;
				pDph_t->perpause=old_perpause;
				pDph_t->compause=old_compause;
				pKsd_t->phoneme_mode=old_phoneme_mode;
				temp=0;
			}
			return ERR_RESET;
		}
		DTinput_counter++;
	}
#ifdef ACCESS_SOLUTIONS
	if (force_it)
#endif
	cmd_loop(phTTS,0x0B); // force it
	if (pKsd_t->halting)
	{
		temp=0;
		oldrate=pKsd_t->uiSampleRate;
		oldspeaker=pKsd_t->last_voice;
		if (pKsd_t->just_flushed)
	{
			oldsprate=pKsd_t->sprate;
			memcpy(oldap,pDph_t->curspdef,SPDEF*sizeof(short));
			old_volatt=pKsd_t->vol_att;
			old_voltone=pKsd_t->vol_tone;
			old_modeflag = pKsd_t->modeflag;
			old_sayflag = pKsd_t->sayflag;
			old_pronflag =pKsd_t->pronflag;
			old_error_mode=pCmd_t->error_mode;
			old_punct_mode=pCmd_t->punct_mode;
			old_skip_mode=pCmd_t->skip_mode;
			old_perpause=pDph_t->perpause;
			old_compause=pDph_t->compause;
			old_phoneme_mode=pKsd_t->phoneme_mode;
			temp=1;
		}

		TextToSpeechInit(g_callback,g_user_dict);
		if (oldrate!=pKsd_t->uiSampleRate &&
		    output_format==0)
		{
			DTSetSampleRate( phTTS, MULAW_SAMPLE_RATE );
		}
		if (temp==0)
		{
			usevoice(phTTS,oldspeaker);
		}
		else
		{
			memcpy(pDph_t->curspdef,oldap,SPDEF*sizeof(short));
			pDph_t->loadspdef=1;
			pKsd_t->last_voice=oldspeaker;
			pKsd_t->async_voice=oldspeaker;
			pKsd_t->async_change &= (~ASYNC_voice);
			pKsd_t->sprate=oldsprate;
			pKsd_t->vol_att=old_volatt;
			pKsd_t->vol_tone=old_voltone;
			pKsd_t->modeflag=old_modeflag;
			pKsd_t->sayflag=old_sayflag;
			pKsd_t->pronflag=old_pronflag;
			pCmd_t->error_mode=old_error_mode;
			pCmd_t->punct_mode=old_punct_mode;
			pCmd_t->skip_mode=old_skip_mode;
			pDph_t->perpause=old_perpause;
			pDph_t->compause=old_compause;
			pKsd_t->phoneme_mode=old_phoneme_mode;
			temp=0;
		}
		return ERR_RESET;
	}
	return ERR_NOERROR;
}

#endif


#ifdef EPSON_ARM7
void fill_TTP_buffer(LPTTS_HANDLE_T phTTS,short *phone,int count)
{
	int i;
	for (i=0;i<count;i++)
	{
		if (phTTS->TTP_return_code<phTTS->TTP_phoneme_buf_len)
		{
			phTTS->TTP_phoneme_buf[phTTS->TTP_return_code++]=phone[i];
		}
	}
}


int TextToSpeechGetSpeakerDef(SPEAKER_DEF_T *speaker_def_ptr)
{
	int i;
	short *spdef;

	spdef=(short *)speaker_def_ptr;

	for (i=0;i<39;i++)
	{
		spdef[i]=paul[i]+us_paul_tune[i];
	}
	for (;i<sizeof(SPEAKER_DEF_T)/2;i++)
	{
		spdef[i]=paul[i];
	}
	
	return(0);

}


#endif
