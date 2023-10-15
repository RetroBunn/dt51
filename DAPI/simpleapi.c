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

#include "port.h"
#include "kernel.h"
#include "tts.h"
#include "cm_def.h"
//#include "ph_def.h"
#include "ph_defs.h"
#include "ph_data.h"

#include "ls_def.h"   
#include "ls_prot.h"

#include "simpleapi.h"

#include "cmdmain.h"
#include "setltslanguage.h"
#include "ltsnames.h"

extern char* TextToSpeechGetTablePath();
extern char* TextToSpeechGetDictPath();

extern int cmd_loop(LPTTS_HANDLE_T phTTS,char input);
extern const unsigned short parser_char_types[];
extern void default_lang( PKSD_T pKsd_t,unsigned int lang_code, unsigned int ready_code );

extern int vtm_main(LPTTS_HANDLE_T phTTS);
extern int ph_main(LPTTS_HANDLE_T phTTS);
extern int lts_main(LPTTS_HANDLE_T phTTS);
extern void DTSetSampleRate( LPTTS_HANDLE_T phTTS, unsigned int uiSampRate );
extern void usevoice (LPTTS_HANDLE_T phTTS, int voice);

#ifdef ALLOC_MEMORY
	extern void spcfree(unsigned short *);
#endif

#if !defined(EPSON_ARM7) && !defined(OS_SYMBIAN)
	extern short cur_packet_number;
	extern short max_packet_number;
	TTS_HANDLE_T hTTS;
	LPTTS_HANDLE_T phTTS;
	KSD_T Ksd_t;
	int gReset;
	int gDTinUse;
#endif

#ifdef USE_NAND
	char *dictfilename;
	char *grdictfilename;
	char *tablename;
#endif

#ifndef OS_SYMBIAN
	char *g_user_dict;
	short *(*g_callback)(short *,long);
#endif


#ifdef _BIGENDIAN_
#define get_long_int(ptr) ((U32)\
                       ((((U8 *)(ptr))[0] << 24)  | \
                        (((U8 *)(ptr))[1] << 16)  | \
                        (((U8 *)(ptr))[2] << 8)  | \
                        (((U8 *)(ptr))[3])))

#else
#define get_long_int(ptr) ((U32)\
                       ((((U8 *)(ptr))[3] << 24)  | \
                        (((U8 *)(ptr))[2] << 16)  | \
                        (((U8 *)(ptr))[1] << 8)  | \
                        (((U8 *)(ptr))[0])))
#endif

#define PC_SAMPLE_RATE 11025
#define MULAW_SAMPLE_RATE 8000

#ifdef DICT_IN_MEMORY
extern const unsigned char main_dict[];

extern const unsigned char sp_main_dict[];
extern const unsigned char us_main_dict[];
extern const unsigned char gr_main_dict[];
#ifndef CASIO_SH3
extern const unsigned char la_main_dict[];
extern const unsigned char uk_main_dict[];
#endif
extern const unsigned char fr_main_dict[];
//currently there is no italian dictionary
//extern const unsigned char it_main_dict[];
//extern const unsigned char jp_main_dict[];
//extern const unsigned char hb_main_dict[];
//extern const unsigned char kr_main_dict[];
//extern const unsigned char ch_main_dict[];

#else
extern char* TextToSpeechGetDictPath();
#endif //DICT_IN_MEMORY

extern void usa_init(PKSD_T);

#ifdef OS_PALM
#pragma pcrelconstdata off
#endif
extern const short paul[];
extern const short us_paul_tune[];
extern const short fr_paul_tune[];
extern const short default_tune[];
extern const short fr_default_tune[];
#ifdef OS_PALM
#pragma pcrelconstdata on
#endif

#if defined USE_NAND && defined USE_464
extern void us_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void gr_lts_loop_2(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void fr_lts_loop_2(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void sp_lts_loop_2(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void it_lts_loop_2(LPTTS_HANDLE_T phTTS,unsigned short *input);
#else
extern void us_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void gr_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void fr_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void sp_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void it_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
#endif
#ifndef CASIO_SH3
extern void la_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void uk_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
#endif

extern void jp_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void hb_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void kr_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
extern void ch_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);

extern int us_lts_main(LPTTS_HANDLE_T phTTS);
#ifndef CASIO_SH3
extern int la_lts_main(LPTTS_HANDLE_T phTTS);
extern int uk_lts_main(LPTTS_HANDLE_T phTTS);
#endif
extern int gr_lts_main(LPTTS_HANDLE_T phTTS);
extern int fr_lts_main(LPTTS_HANDLE_T phTTS);
extern int sp_lts_main(LPTTS_HANDLE_T phTTS);
extern int it_lts_main(LPTTS_HANDLE_T phTTS);
extern int jp_lts_main(LPTTS_HANDLE_T phTTS);
extern int hb_lts_main(LPTTS_HANDLE_T phTTS);
extern int kr_lts_main(LPTTS_HANDLE_T phTTS);
extern int ch_lts_main(LPTTS_HANDLE_T phTTS);

extern int us_lts_language_loaded( void );
#ifndef CASIO_SH3
extern int uk_lts_language_loaded( void );
extern int la_lts_language_loaded( void );
#endif
extern int gr_lts_language_loaded( void );
extern int fr_lts_language_loaded( void );
extern int sp_lts_language_loaded( void );
extern int it_lts_language_loaded( void );
extern int jp_lts_language_loaded( void );
extern int hb_lts_language_loaded( void );
extern int kr_lts_language_loaded( void );
extern int ch_lts_language_loaded( void );

extern CONST lts_func_t *us_ls_main_get_lts_funcs(void);
#ifndef CASIO_SH3
extern CONST lts_func_t *uk_ls_main_get_lts_funcs(void);
extern CONST lts_func_t *la_ls_main_get_lts_funcs(void);
#endif
extern CONST lts_func_t *gr_ls_main_get_lts_funcs(void);
extern CONST lts_func_t *fr_ls_main_get_lts_funcs(void);
extern CONST lts_func_t *sp_ls_main_get_lts_funcs(void);
extern CONST lts_func_t *it_ls_main_get_lts_funcs(void);
extern CONST lts_func_t *ch_ls_main_get_lts_funcs(void);
extern CONST lts_func_t *jp_ls_main_get_lts_funcs(void);
extern CONST lts_func_t *kr_ls_main_get_lts_funcs(void);
extern CONST lts_func_t *hb_ls_main_get_lts_funcs(void);

CONST lts_func_t *load_lts_language(int lang_num);

#ifndef EPSON_ARM7

int FindAndSetDefaultLanguage( PKSD_T pKsd_t );
void ClearDictionarySettings( PKSD_T pKsd_t );
void ClearLtsFuncs(LPTTS_HANDLE_T phTTS);
void SetUserDictionary( PKSD_T pKsd_t, void * user_dict );
void SetDefaultEngineSettings( PKSD_T pKsd_t, LPTTS_HANDLE_T phTts  );
#ifdef USE_NAND
int LoadDictionaries( PKSD_T pKsd_t, LPTTS_HANDLE_T phTts );
#endif
#if defined DICT_IN_MEMORY && !defined USE_NAND
void SetMainDictionary( PKSD_T pKsd_t );
#else
int TextToSpeechUnloadDictionary();
#endif
#ifdef MULTIPLE_LANGUAGES_LOADED
void SetLanguageEntryPoint( PKSD_T pKsd_t, LPTTS_HANDLE_T phTTS );
int TextToSpeechSetLanguage( LPTTS_HANDLE_T phTTS, int Language );
#endif

void InitDTVals( void )
{
#ifdef OS_SYMBIAN
	GlobalDTPtr gp = GetGlobalDTPtr();
	gp->simpleData.gReset = FULL_ENGINE_RESET;
	gp->simpleData.gDTinUse = DT_IN_USE;
#else
	gReset = FULL_ENGINE_RESET;
	gDTinUse = DT_IN_USE;
#endif
}




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
#if !defined OS_SYMBIAN
int TextToSpeechInit(short *(*callback)(short *,long), void *user_dict)
#else
int TextToSpeechInit(short *(*callback)(short *,long, void*), void *user_dict, void *user_data)
#endif
{
	int return_code = ERR_NOERROR;
	PKSD_T pKsd_t;
	int ResetLevel;
#ifdef MULTIPLE_LANGUAGES_LOADED
	int prevLang;
	int prevVoice;
#endif
#ifdef USE_NAND
	int  dictfilehandle=0;
	int  tabfilehandle=0;
	DT_HANDLE prevfdicFileHandle=NULL;
	DT_HANDLE prevgrfdicFileHandle=NULL;
#endif
#ifdef OS_SYMBIAN
	LPTTS_HANDLE_T phTTS = NULL;
	KSD_T* Ksd_t = NULL;
	GlobalDTPtr	gp = NULL;

	gp = GetGlobalDTPtr();

	ResetLevel = gp->simpleData.gReset;
	if(!gp->simpleData.phTTS)
	{
		phTTS = (LPTTS_HANDLE_T)FNX_CALLOC(1, sizeof(TTS_HANDLE_T));
		phTTS->EmbCallbackRoutine=callback;
		phTTS->pUserData = user_data;

		Ksd_t = (KSD_T*)FNX_CALLOC(1, sizeof(KSD_T));
		phTTS->pKernelShareData=Ksd_t;
		pKsd_t=Ksd_t;

		gp->simpleData.phTTS = phTTS;
	}
	else //reset everything
	{
		phTTS = gp->simpleData.phTTS;
		pKsd_t = Ksd_t = phTTS->pKernelShareData;
	}

	gp->simpleData.g_callback = callback;
#else  //!Symbian
	InitDTVals();						// initialize globals - sets the flag to block other apis from being called
	ResetLevel = gReset;

#ifdef MULTIPLE_LANGUAGES_LOADED
	prevLang = Ksd_t.lang_curr;
	prevVoice = Ksd_t.last_voice;
#endif //MULTIPLE_LANGUAGES_LOADED
#ifdef USE_NAND
	dictfilename=NULL;
	grdictfilename=NULL;
	tablename=NULL;
	if( !(ResetLevel & RESET_TO_DEFAULT_VOICE) )
	{
		prevfdicFileHandle = Ksd_t.fdicFileHandle;
		prevgrfdicFileHandle = Ksd_t.grfdicFileHandle;
	}
#endif  //USE_NAND
	memset(&hTTS,0,sizeof(TTS_HANDLE_T));
	memset(&Ksd_t,0,sizeof(KSD_T));
	
	phTTS=&hTTS;
	phTTS->EmbCallbackRoutine=callback;
	phTTS->pKernelShareData=&Ksd_t;
	pKsd_t=&Ksd_t;
	pKsd_t->phTTS=phTTS;
	g_callback=callback;
#endif //!OS_SYMBIAN
	// must now initialize this for AD
	phTTS->ph_funcs.ph_loop=ph_loop;
	phTTS->ph_funcs.char_types=char_types;
	phTTS->ph_funcs.parser_char_types=parser_char_types;
	phTTS->ph_funcs.default_lang=default_lang;


#if defined(USE_NAND) && defined(MULTIPLE_LANGUAGES_LOADED)

	tablename = TextToSpeechGetTablePath();
	if(pKsd_t->lang_curr == LANG_german)
	{
		grdictfilename = TextToSpeechGetDictPath();
		dictfilename = NULL;
	}
	else
	{
		grdictfilename = NULL;
		dictfilename = TextToSpeechGetDictPath();
	}
#endif //USE_NAND && MULTIPLE_LANGUAGES_LOADED

/*
GL 12/11/1996, set up the language flag pKsd_t->lang_curr
this flag will be used in CMD and phlog.c to pick up the language
depended code
*/
#ifdef MULTIPLE_LANGUAGES_LOADED
	if( ResetLevel & RESET_TO_DEFAULT_LANG )
	{
		if( FindAndSetDefaultLanguage( pKsd_t ) )
		{
			return_code = ERR_ERROR;
			goto UNBLOCK_AND_RETURN;
		}
	}
	else 
	{
		pKsd_t->lang_curr = prevLang;
	}
	
	if( !(ResetLevel & RESET_TO_DEFAULT_VOICE) )
	{
		pKsd_t->last_voice = prevVoice;
	}

#else
	FindAndSetDefaultLanguage( pKsd_t );
#endif	//MULTIPLE_LANGUAGES_LOADED


	FindAndSetDefaultLanguage( pKsd_t );

	if( vtm_main(phTTS) )
	{
		return_code = ERR_ERROR;
		goto UNBLOCK_AND_RETURN;
	}
	if( ph_main(phTTS) )
	{
		return_code = ERR_ERROR;
		goto UNBLOCK_AND_RETURN;
	}

	((PDPH_T)(phTTS->pPHThreadData))->loadspdef=1;
	

	return_code=cmd_main(phTTS);

	// this must be called AFTER cmd_main
	SetDefaultEngineSettings( pKsd_t, phTTS );

#ifdef OS_SYMBIAN
	phTTS->pCMDThreadData=gp->Cmd_t;
#endif
	if (return_code)
	{
		return_code = ERR_ERROR;
		goto UNBLOCK_AND_RETURN;
	}
		
	DTSetSampleRate( phTTS, PC_SAMPLE_RATE );

#ifdef OS_SYMBIAN
	gp->simpleData.gReset = NO_RESET;
#else
	gReset = NO_RESET;
#endif

UNBLOCK_AND_RETURN:
#ifdef OS_SYMBIAN
	gp->simpleData.gDTinUse = DT_AVAILABLE;
#else
	gDTinUse = DT_AVAILABLE;
#endif
	return(return_code);
}

int FindAndSetDefaultLanguage( PKSD_T pKsd_t )
{

#ifdef MULTIPLE_LANGUAGES_LOADED
	// order here determines the default order
	if( !us_lts_language_loaded() )
		pKsd_t->lang_curr = LANG_english;
	else if( !fr_lts_language_loaded() )
		pKsd_t->lang_curr = LANG_french;
	else if( !gr_lts_language_loaded() )
		pKsd_t->lang_curr = LANG_german;
	else if( !sp_lts_language_loaded() )
		pKsd_t->lang_curr = LANG_spanish;
#ifndef CASIO_SH3
	else if( !uk_lts_language_loaded() )
		pKsd_t->lang_curr = LANG_british;
	else if( !la_lts_language_loaded() )
		pKsd_t->lang_curr = LANG_latin_american;
#endif
	else if( !it_lts_language_loaded() )
		pKsd_t->lang_curr = LANG_italian;
	else if( !jp_lts_language_loaded() )
		pKsd_t->lang_curr = LANG_japanese;
	else if( !hb_lts_language_loaded() )
		pKsd_t->lang_curr = LANG_hebrew;		
	else if( !kr_lts_language_loaded() )
		pKsd_t->lang_curr = LANG_korean;
	else if( !ch_lts_language_loaded() )
		pKsd_t->lang_curr = LANG_chinese;
			
		else
			return (1);
#else
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
	#endif	/* ITALIAN */
   #ifdef JAPANESE
		pKsd_t->lang_curr = LANG_japanese;
	#endif	/* JAPANESE */
   #ifdef HEBREW
		pKsd_t->lang_curr = LANG_hebrew;
	#endif	/* HEBREW */
   #ifdef CHINESE
		pKsd_t->lang_curr = LANG_chinese;
	#endif	/* CHINESE */
   #ifdef KOREAN
  		pKsd_t->lang_curr = LANG_korean;
	#endif	/* KOREAN */
#endif //MULTIPLE_LANGUAGES_LOADED
	return (0);
}

void ClearDictionarySettings( PKSD_T pKsd_t )
{
#ifdef USE_NAND
//	for (i=0; i < MAX_languages; ++i)
//	{
		pKsd_t->udic_index = 0;
		pKsd_t->fdic_index = 0;
		pKsd_t->udic_data = 0;
		pKsd_t->fdic_data = 0;
//		pKsd_t->udic_bytes = 0;
		pKsd_t->udic_bytes = 0;
//		pKsd_t->fdic_bytes = 0;
		pKsd_t->fdic_bytes = 0;
//		pKsd_t->udic_entries = 0;
		pKsd_t->udic_entries = 0;
//		pKsd_t->fdic_entries = 0;
		pKsd_t->fdic_entries = 0;
//	}	
#else
	int i;
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
#endif
}

void ClearLtsFuncs(LPTTS_HANDLE_T phTTS)
{
	memset((void *)(&phTTS->lts_funcs),0,sizeof(lts_func_t));
}
	
void SetUserDictionary( PKSD_T pKsd_t, void * user_dict )
{
#ifdef USE_NAND
	/* user dictionary load */
	if (user_dict)
	{
//		pKsd_t->udic_entries[pKsd_t->lang_curr]=get_long_int((char *)user_dict);
		pKsd_t->udic_entries=get_long_int((char *)user_dict);
//		if (pKsd_t->udic_entries[pKsd_t->lang_curr])
		if (pKsd_t->udic_entries)
		{
//			pKsd_t->udic_bytes[pKsd_t->lang_curr]=get_long_int((char *)user_dict+4);
			pKsd_t->udic_bytes=get_long_int((char *)user_dict+4);
//			pKsd_t->udic_index[pKsd_t->lang_curr]=(S32 *)((char *)user_dict+8);
			pKsd_t->udic_index=(S32 *)((char *)user_dict+8);
//			pKsd_t->udic_data[pKsd_t->lang_curr] = ((unsigned char *)user_dict)+(pKsd_t->udic_entries[pKsd_t->lang_curr]*4)+8;
			pKsd_t->udic_data = ((unsigned char *)user_dict)+(pKsd_t->udic_entries*4)+8;
		}
	}
	else
	{
//		pKsd_t->udic_entries[pKsd_t->lang_curr] = 0;
		pKsd_t->udic_entries = 0;
//		pKsd_t->udic_bytes[pKsd_t->lang_curr] = 0;
		pKsd_t->udic_bytes = 0;
//		pKsd_t->udic_index[pKsd_t->lang_curr] = 0;
		pKsd_t->udic_index = 0;
//		pKsd_t->udic_data[pKsd_t->lang_curr] = 0;
		pKsd_t->udic_data = 0;

	}

#else
	/* user dictionary load */
	if (user_dict)
	{
		pKsd_t->udic_entries[pKsd_t->lang_curr]=get_long_int((char *)user_dict);
		if (pKsd_t->udic_entries[pKsd_t->lang_curr])
		{
			pKsd_t->udic_bytes[pKsd_t->lang_curr]=get_long_int((char *)user_dict+4);
			pKsd_t->udic_index[pKsd_t->lang_curr]=(S32 *)((char *)user_dict+8);
			pKsd_t->udic_data[pKsd_t->lang_curr] = ((unsigned char *)user_dict)+(pKsd_t->udic_entries[pKsd_t->lang_curr]*4)+8;
		}
	}
	else
	{
		pKsd_t->udic_entries[pKsd_t->lang_curr] = 0;
		pKsd_t->udic_bytes[pKsd_t->lang_curr] = 0;
		pKsd_t->udic_index[pKsd_t->lang_curr] = 0;
		pKsd_t->udic_data[pKsd_t->lang_curr] = 0;
	}
#endif  //USE_NAND
}

#ifdef DICT_IN_MEMORY
void SetMainDictionary( PKSD_T pKsd_t )
{
	char *maindict;

#ifdef MULTIPLE_LANGUAGES_LOADED
	switch( pKsd_t->lang_curr )
	{	
		case LANG_english:
			maindict = (char *)us_main_dict;
			break;
		case LANG_french:
			maindict = (char *)fr_main_dict;
			break;
		case LANG_german:
			maindict = (char *)gr_main_dict;
			break;
		case LANG_spanish:
			maindict = (char *)sp_main_dict;
			break;
		case LANG_british:
			maindict = (char *)uk_main_dict;
			break;
		case LANG_latin_american:
			maindict = (char *)la_main_dict;
			break;
		case LANG_italian:
			//currently there is no italian dictionary
//			maindict = (char *)it_main_dict;
			maindict = NULL;
			break;
		case LANG_japanese:
//			maindict = (char *)jp_main_dict;
			maindict = NULL;
			break;
		case LANG_hebrew:
//			maindict = (char *)hb_main_dict;
			maindict = NULL;
			break;
		case LANG_korean:
//			maindict = (char *)kr_main_dict;
			maindict = NULL;
			break;
		case LANG_chinese:
//			maindict = (char *)ch_main_dict;
			maindict = NULL;
			break;												
	}
#else
		maindict = (char *)main_dict;
#endif //MULTIPLE_LANGUAGES_LOADED

	/* main dictionary load */
	if (maindict)
	{
		pKsd_t->fdic_entries[pKsd_t->lang_curr]=get_long_int(maindict);
		if (pKsd_t->fdic_entries[pKsd_t->lang_curr])
		{
			pKsd_t->fdic_bytes[pKsd_t->lang_curr]=get_long_int(maindict+4);
#ifdef CHEESY_DICT_COMPRESSION
			pKsd_t->fdic_fc_entries[pKsd_t->lang_curr]=get_long_int(maindict+8);
			pKsd_t->fdic_fc_entry[pKsd_t->lang_curr]=((S32 *)(maindict+12));
			pKsd_t->fdic_index[pKsd_t->lang_curr]=((S32 *)(maindict+12+(pKsd_t->fdic_fc_entries[pKsd_t->lang_curr]*4)));
			pKsd_t->fdic_data[pKsd_t->lang_curr]=(unsigned char *)(maindict+((pKsd_t->fdic_entries[pKsd_t->lang_curr]+3)*4) + (pKsd_t->fdic_fc_entries[pKsd_t->lang_curr]*4));
#else
			// Don't fc_entries and fc_entry need to be set???
			pKsd_t->fdic_index[pKsd_t->lang_curr]=((S32 *)(maindict+8));
			pKsd_t->fdic_data[pKsd_t->lang_curr]=(unsigned char *)(maindict+((pKsd_t->fdic_entries[pKsd_t->lang_curr]+2)*4));
#endif
		}
	}
}
#endif  //DICT_IN_MEMORY
#ifdef USE_NAND
int LoadDictionaries( PKSD_T pKsd_t, LPTTS_HANDLE_T phTTS )
{
	int return_code = 0;

    int dictfilehandle = 0;
	int tabfilehandle = 0;

	/* unload the dictionary file */
	if(pKsd_t->fdicFileHandle)
	{
		FNX_FCLOSE(pKsd_t->fdicFileHandle);
		pKsd_t->fdicFileHandle =0;
	}
	if(pKsd_t->grfdicFileHandle)
	{
		FNX_FCLOSE(pKsd_t->grfdicFileHandle);
		pKsd_t->grfdicFileHandle =0;
	}
	if (dictfilename && dictfilename[0])
	{
		#ifdef _BIGENDIAN_
			dictfilehandle = (int)FNX_FOPEN(dictfilename,"r");
			if ((dictfilehandle == -1) || (dictfilehandle == 0))
				return ERR_FILE;
			else
				pKsd_t->fdicFileHandle = (DT_HANDLE)dictfilehandle;
		#else
			pKsd_t->fdicFileHandle=(DT_HANDLE)FNX_FOPEN(dictfilename,"rb");
		#endif
	}
	if (grdictfilename && grdictfilename[0])
	{
		#ifdef _BIGENDIAN_
			dictfilehandle=(int)FNX_FOPEN(grdictfilename,"r");
			if ((dictfilehandle == -1) || (dictfilehandle == 0))
				return ERR_FILE;
			else
				pKsd_t->grfdicFileHandle = (DT_HANDLE)dictfilehandle;
		#else
			pKsd_t->grfdicFileHandle=(DT_HANDLE)FNX_FOPEN(grdictfilename,"rb");
		#endif

	}
	if (tablename && tablename[0])
	{
		#ifdef _BIGENDIAN_
			tabfilehandle=(int)FNX_FOPEN(tablename,"r");
			if ((tabfilehandle == -1) || (tabfilehandle == 0))
				return ERR_FILE;
			else
				pKsd_t->grfdicFileHandle = (DT_HANDLE)tabfilehandle;
		#else
			pKsd_t->grfdicFileHandle=(DT_HANDLE)FNX_FOPEN(tablename,"rb");
		#endif
	}
	return( return_code );
}
#endif  //USE_NAND


void SetDefaultEngineSettings( PKSD_T pKsd_t, LPTTS_HANDLE_T phTTS )
{
#ifdef OS_SYMBIAN
	GlobalDTPtr gp = GetGlobalDTPtr();
#endif
	pKsd_t->cmd_flush = FALSE;
	pKsd_t->spc_flush = FALSE;
	pKsd_t->halting = FALSE;
	pKsd_t->logflag  = 0;
	/* GL 11/15/1996 set defaulted Spanish to Latin */
	pKsd_t->modeflag = MODE_CITATION;
#ifdef SCI
	pKsd_t->modeflag |= MODE_READING ; 
#endif  //SCI
	if (pKsd_t->lang_curr==LANG_british)
		pKsd_t->modeflag|=MODE_EUROPE;
	else if (pKsd_t->lang_curr==LANG_spanish)
		pKsd_t->modeflag|=MODE_EUROPE;
	else if (pKsd_t->lang_curr==LANG_german)
		pKsd_t->modeflag|=MODE_EUROPE;
	else if (pKsd_t->lang_curr==LANG_italian)
		pKsd_t->modeflag|=MODE_EUROPE;
	else if (pKsd_t->lang_curr==LANG_french)
		pKsd_t->modeflag|=MODE_EUROPE;
	else 
		pKsd_t->modeflag&= (~MODE_EUROPE);

	pKsd_t->sayflag = SAY_CLAUSE;
	pKsd_t->pronflag = 0;
//#ifndef CASIO_SH3
	pKsd_t->wbreak = FALSE;
//#endif
	pKsd_t->text_flush = FALSE;
	pKsd_t->async_change = FALSE;
	pKsd_t->SamplePeriod = 9.07029478458E-5 ;  /* Initialize sample period */
	pKsd_t->spc_pkt_save = NULL_SPC_PACKET;

	pKsd_t->loaded_languages = NULL;           //MVP:05/10/96 Fixed an exception(When DECtalk runs on a machine without audio card)
	pKsd_t->volume=100; //set volume to 100;
	pKsd_t->vol_att=100; //set volume to 100;
	pKsd_t->vol_tone=100; //set volume to 100;

	pKsd_t->phTTS = phTTS;

	phTTS->uiCurrentMsgNumber = 1;
	phTTS->uiLastTextMsgNumber = 0;
	phTTS->uiFlushMsgNumber = 0;
	
#ifndef OS_SYMBIAN
	cur_packet_number=0;
	max_packet_number=0;
#else
	gp->cur_packet_number = 0;
	gp->max_packet_number = 0;
#endif

#ifdef OS_SYMBIAN
	DeleteDTTlsValue();
#endif
}

#ifdef MULTIPLE_LANGUAGES_LOADED
void SetLanguageEntryPoint( PKSD_T pKsd_t, LPTTS_HANDLE_T phTTS )
{
	switch( pKsd_t->lang_curr )
	{
#if defined USE_NAND && defined USE_464	
		case LANG_english:
				phTTS->main_lts_loop=(void *)&us_lts_loop;
				break;
		case LANG_french:
				phTTS->main_lts_loop=(void *)&fr_lts_loop_2;
				break;
		case LANG_german:
				phTTS->main_lts_loop=(void *)&gr_lts_loop_2;
				break;
		case LANG_spanish:
				phTTS->main_lts_loop=(void *)&sp_lts_loop_2;
				break;
		case LANG_italian:
				phTTS->main_lts_loop=(void *)&it_lts_loop_2;
			break;
#else
		case LANG_english:
				phTTS->main_lts_loop=(void *)&us_lts_loop;
				break;
		case LANG_french:
				phTTS->main_lts_loop=(void *)&fr_lts_loop;
				break;
		case LANG_german:
				phTTS->main_lts_loop=(void *)&gr_lts_loop;
				break;
		case LANG_spanish:
				phTTS->main_lts_loop=(void *)&sp_lts_loop;
				break;
		case LANG_italian:
			phTTS->main_lts_loop=(void *)&it_lts_loop;
			break;
#endif //USE_NAND && USE_464
#ifndef CASIO_SH3
		case LANG_british:
			phTTS->main_lts_loop=(void *)&uk_lts_loop;
			break;
		case LANG_latin_american:
			phTTS->main_lts_loop=(void *)&la_lts_loop;
			break;
#endif
		case LANG_japanese:
			phTTS->main_lts_loop=(void *)&jp_lts_loop;
			break;
		case LANG_hebrew:
			phTTS->main_lts_loop=(void *)&hb_lts_loop;
			break;
		case LANG_korean:
			phTTS->main_lts_loop=(void *)&kr_lts_loop;
			break;
		case LANG_chinese:
			phTTS->main_lts_loop=(void *)&ch_lts_loop;
			break;

	}
}

int IsLanguageAvailable( int LangId )
{
	//check if language was included in build
	int return_code;

	switch( LangId )
	{
		case LANG_english:
			return_code = us_lts_language_loaded( );
			break;
		case LANG_french:
			return_code = fr_lts_language_loaded( );
			break;
		case LANG_german:
			return_code = gr_lts_language_loaded( );
			break;
		case LANG_spanish:
			return_code = sp_lts_language_loaded( );
			break;
#ifndef CASIO_SH3
		case LANG_british:
			return_code = uk_lts_language_loaded( );
			break;
		case LANG_latin_american:
			return_code = la_lts_language_loaded( );
			break;
#endif
		case LANG_italian:
			return_code = it_lts_language_loaded( );
			break;
		case LANG_japanese:
			return_code = jp_lts_language_loaded( );
			break;
		case LANG_hebrew:
			return_code = hb_lts_language_loaded( );
			break;
		case LANG_korean:
			return_code = kr_lts_language_loaded( );
			break;
		case LANG_chinese:
			return_code = ch_lts_language_loaded( );
			break;
			
	}
	return( return_code );
}

/* ******************************************************************
 *      Function Name: TextToSpeechChangeLanguage()
 *
 *      Description: 
 *
 *      Arguments:	int LangId
 *					void *user_dict
 *
 *      Return Value: int
 *
 *      Comments:
 *
 * *****************************************************************/
int TextToSpeechChangeLanguage( int LangId, void *user_dict )
{
	int return_code = ERR_NOERROR;
	char *maindict = NULL;
	int oldrate=0;

#ifdef OS_SYMBIAN
	LPTTS_HANDLE_T phTTS = GetGlobalDTPtr()->simpleData.phTTS;
	PKSD_T pKsd_t = phTTS->pKernelShareData;
	GlobalDTPtr gp = GetGlobalDTPtr();
	char* g_user_dict = GetGlobalDTPtr()->simpleData.g_user_dict;
	short *(*g_callback)(short *,long, void*) = GetGlobalDTPtr()->simpleData.g_callback;
#else
	PKSD_T pKsd_t = &Ksd_t;
#endif

	// Don't allow this function or other functions to be called concurrently from a thread or interrupt

#ifdef OS_SYMBIAN
	if( gp->simpleData.gDTinUse == DT_IN_USE )
		return ERR_ERROR;
	gp->simpleData.gDTinUse = DT_IN_USE;
#else
	if( gDTinUse == DT_IN_USE )
		return ERR_ERROR;
	gDTinUse = DT_IN_USE;

#endif
	if( IsLanguageAvailable( LangId ) )
	{
		return_code = ERR_ERROR;
		goto UNBLOCK_AND_RETURN;
	}
//#if defined (USE_MEMFILE_IO) || defined (USE_NAND)
	ClearDictionarySettings( pKsd_t );	
//#endif

#if defined (USE_NAND) || defined (OS_SYMBIAN)
	// closes file for USE_NAND and frees data for !DICT_IN_MEMORY
	TextToSpeechUnloadDictionary();
#endif
	ClearLtsFuncs(phTTS);
	//langauge is available - switch to new language
	pKsd_t->lang_curr = LangId;
	g_user_dict = (char *)user_dict;
	phTTS->cur_lts_lang=pKsd_t->lang_curr;

	phTTS->dict_path = TextToSpeechGetDictPath();


#ifdef NEW_MULTI_LANG_ARCH
	return_code = TextToSpeechSetLanguage(phTTS,pKsd_t->lang_curr);
#endif

	// set user dictionary for new language
	SetUserDictionary( pKsd_t, user_dict );
#ifdef DICT_IN_MEMORY
    SetMainDictionary( pKsd_t );
#endif   

#ifdef USE_NAND
	tablename = TextToSpeechGetTablePath();

	if(pKsd_t->lang_curr == LANG_german)
	{
		grdictfilename = TextToSpeechGetDictPath();
		dictfilename = NULL;
	}
	else
	{
		grdictfilename = NULL;
		dictfilename = TextToSpeechGetDictPath();
	}
	maindict = NULL;
#endif //USE_NAND

	SetLanguageEntryPoint( pKsd_t, phTTS );
#ifdef USE_NAND
	if( LoadDictionaries( pKsd_t, phTTS ) )
	{
		return_code = ERR_ERROR;
		goto UNBLOCK_AND_RETURN;
	}
#endif
	if( cmd_main(phTTS) )
		return(ERR_ERROR);
	
	SetDefaultEngineSettings( pKsd_t, phTTS );	//when you change languages you get the default for that language

	DTSetSampleRate( phTTS, PC_SAMPLE_RATE );

	// Change blocking flag to allow function calls
#ifdef OS_SYMBIAN
	gp->simpleData.gDTinUse = DT_AVAILABLE;
#else
	gDTinUse = DT_AVAILABLE;

#endif

UNBLOCK_AND_RETURN:
#ifdef OS_SYMBIAN
	gp->simpleData.gDTinUse = DT_AVAILABLE;
#else
	gDTinUse = DT_AVAILABLE;
#endif
	return(return_code);
}
#endif //MULTIPLE_LANGUAGES_LOADED

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
int TextToSpeechReset( int ResetLevel )
{
#ifdef OS_SYMBIAN
	GlobalDTPtr gp = GetGlobalDTPtr();
	LPTTS_HANDLE_T phTTS = gp->simpleData.phTTS;
	char* g_user_dict = gp->simpleData.g_user_dict;
	short *(*g_callback)(short *,long, void*) = gp->simpleData.g_callback;
#endif

	// if you want to stop speech that is currently being processed allow the flags to be set
	if( ResetLevel == HALT_SPEECH_LEAVE_SETTINGS )
	{
		phTTS->pKernelShareData->halting=1;
	}
	else	// all other reset types - can't have engine doing something else while trying to reset
	{

#ifdef OS_SYMBIAN
		if( gp->simpleData.gDTinUse == DT_IN_USE )
			return ERR_ERROR;
		gp->simpleData.gDTinUse = DT_IN_USE;
		gp->simpleData.gReset = ResetLevel;
		TextToSpeechInit(g_callback,g_user_dict, phTTS->pUserData);
		gp->simpleData.gDTinUse = DT_AVAILABLE;
#else
		if( gDTinUse == DT_IN_USE )
			return ERR_ERROR;
		gDTinUse = DT_IN_USE;
		gReset = ResetLevel;
		TextToSpeechInit(g_callback,g_user_dict);
		gDTinUse = DT_AVAILABLE;

#endif
	}
	return(ERR_NOERROR);
}
/* ******************************************************************
 *      Function Name: TextToSpeechConvertInput()
 *
 *      Description: 
 *
 *      Arguments:	char *input
 *					int input_format
 *					char * output
 *
 *      Return Value: int - error values 
 *
 *      Comments:output is the ASCII conversion of input 
 *
 * *****************************************************************/
int TextToSpeechConvertInput(wchar_t *input, int iInType, char * output, int nMaxOut)
{
	char 
		sSjis[MAX_CHARS_TO_CONVERT+3],			// Leave room for null + ' ' + 0x11 (force) character
		sText[MAX_CHARS_TO_CONVERT+3];
	wchar_t
		wsText[MAX_CHARS_TO_CONVERT+1];
	int	 
		nToConvert,
		nConverted,
		nTotalConverted,
		mmResult;
	int bAscii=TRUE;
	int ret=0;

	if( wsText == NULL ||
		output == NULL ||
		phTTS->cur_lts_lang >= MAX_languages )
	{
		return(ERR_ERROR); //Return error
	}

	// Translate to single byte characters based on language
	switch(phTTS->cur_lts_lang)
	{

		case LANG_chinese:
#ifdef CASIO_SH3
			InitBsortGlobals();
#endif //CASIO_SH3
			// Make sure we have a pointer to the function that converts unicode to romanized characters
			if( phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_ConvertToAscii == NULL )
			{
				return(ERR_ERROR); //Return error
			}
			// Get the length of the input string
			if( iInType == 0 )							// Unicode   Utf16
				nToConvert = FNXW_STRLEN(input);
			else if( iInType == 4 )						// GBK  
				nToConvert = FNXW_STRLEN(input);
			else											// Invalid input type
				return( ERR_ERROR);

			nTotalConverted = nConverted = 0;

			while( nTotalConverted < nToConvert )
			{
				if( iInType == 4 )				//GBK
				{
					// Convert GBK to unicode
					nConverted += Gbk2Utf(((unsigned char *)input) + nTotalConverted, wsText, MAX_CHARS_TO_CONVERT);
				}
				else
				{
					// Copy unicode characters
					if( nToConvert-nTotalConverted >= MAX_CHARS_TO_CONVERT )
					{
						FNXW_STRNCPY(wsText, ((wchar_t *)input)+nTotalConverted, MAX_CHARS_TO_CONVERT);
						wsText[MAX_CHARS_TO_CONVERT] = 0x00;
						nConverted += MAX_CHARS_TO_CONVERT;
					}
					else
					{
						FNXW_STRCPY(wsText, ((wchar_t *)input)+nTotalConverted);
						nConverted = nToConvert-nTotalConverted;
					}
				}


				if( nConverted == MAX_CHARS_TO_CONVERT )
				{
					// Let's back up a little bit to end in a more logical location
					while( nConverted > 0 )
					{
						if( (0x3000 <= wsText[nConverted] && wsText[nConverted] <= 0x303f) ||	// Unicode punctuation
							(0x0020 <= wsText[nConverted] && wsText[nConverted] <= 0x002f) ||	// Ascii punctuation
							(0x003a <= wsText[nConverted] && wsText[nConverted] <= 0x003f) ||	// Ascii punctuation
							(0x005b <= wsText[nConverted] && wsText[nConverted] <= 0x005f) ||	// Ascii punctuation
							(0x007b <= wsText[nConverted] && wsText[nConverted] <= 0x007e) ||	// Ascii punctuation
							wsText[nConverted] == 0x0a || wsText[nConverted] == 0x0d )			// carriage return, line feed
						{
							wsText[nConverted] = 0x00;
							break;
						}
						else
						{
							nConverted--;
						}
					}
				}

				nTotalConverted += nConverted;

				// Convert unicode to Romanized text
				memset( output, 0, (MAX_CHARS_TO_CONVERT*5)+1);
				phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_ConvertToAscii(phTTS, wsText, output, 0);

			}
			break;
		
		case LANG_japanese:
#ifdef CASIO_SH3
			InitBsortGlobals();
#endif //CASIO_SH3

			// Get the length of the input string
			if( iInType == 0 )							// Unicode  Utf16
				nToConvert = FNXW_STRLEN(input);
			else if( iInType == 1 )						// Shift jis	Sjis
				nToConvert = FNXW_STRLEN(input);
			else											// Invalid input type
				return( ERR_ERROR);

			nTotalConverted = 0;

			// -------------------------------------------------------------------------
			//  Japanese internal code is Shift Jis not Unicode
			// -------------------------------------------------------------------------
			while( nTotalConverted < nToConvert )
			{
				if( iInType == 1 )		//Sjis
				{
					// already in sjis
					if( nToConvert-nTotalConverted >= MAX_CHARS_TO_CONVERT )
					{
					//	FNXA_STRNCPY(sSjis, ((unsigned char *)input)+nTotalConverted, MAX_CHARS_TO_CONVERT);
							FNXA_STRNCPY(output, ((unsigned char *)input)+nTotalConverted, MAX_CHARS_TO_CONVERT);
					//	sSjis[MAX_CHARS_TO_CONVERT] = 0x00;
						output[MAX_CHARS_TO_CONVERT] = 0x00;
						nTotalConverted += MAX_CHARS_TO_CONVERT;
					}
					else
					{
				//		FNXA_STRCPY(sSjis, ((unsigned char *)input)+nTotalConverted);
						FNXA_STRCPY(output, ((unsigned char *)input)+nTotalConverted);
						nTotalConverted = nToConvert;
					}
				}
				else
				{
					// convert unicode to sjis
				//	nTotalConverted += Utf2Sjis(((wchar_t *)input)+nTotalConverted, sSjis, MAX_CHARS_TO_CONVERT);
						nTotalConverted += Utf2Sjis(((wchar_t *)input)+nTotalConverted, output, MAX_CHARS_TO_CONVERT);
				}

			}
			break;

		case LANG_korean:
#ifdef CASIO_SH3
			InitBsortGlobals();
#endif //CASIO_SH3

			// Make sure we have a pointer to the function that converts unicode to romanized characters
			if( phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_ConvertToAscii == NULL )
				return ERR_ERROR;

			// Get the length of the input string
			if( iInType == 0 )							// Unicode	Utf16
				nToConvert = FNXW_STRLEN(input);
			else if( iInType == 3 )						// KSC
				nToConvert = FNXW_STRLEN(input);
			else											// Invalid input type
				return(ERR_ERROR);

			nTotalConverted = 0;

			while( nTotalConverted < nToConvert )
			{
				if( iInType == 3 )			//Ksc
				{
					// Convert KSC to unicode
					nTotalConverted += Ksc2Utf(((unsigned char *)input)+nTotalConverted, wsText, MAX_CHARS_TO_CONVERT);
				}
				else
				{
					// Copy unicode characters
					if( nToConvert-nTotalConverted >= MAX_CHARS_TO_CONVERT )
					{
						FNXW_STRNCPY(wsText, ((wchar_t *)input)+nTotalConverted, MAX_CHARS_TO_CONVERT);
						wsText[MAX_CHARS_TO_CONVERT] = 0x00;
						nTotalConverted += MAX_CHARS_TO_CONVERT;
					}
					else
					{
						FNXW_STRCPY(wsText, ((wchar_t *)input)+nTotalConverted);
						nTotalConverted = nToConvert;
					}
				}

				// Convert unicode to Romanized text
				memset( output, 0, (MAX_CHARS_TO_CONVERT*5)+1);
				phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_ConvertToAscii(phTTS, wsText, output, 0);

			}
			break;

		case LANG_hebrew:
			break;

		default:
			
			nToConvert = FNXW_STRLEN((wchar_t *)input);
			nTotalConverted = nConverted = 0;
			output[0] = 0x00;
			while( nTotalConverted < nToConvert )
			{
				// Copy unicode characters
				if( nToConvert-nTotalConverted >= MAX_CHARS_TO_CONVERT )
				{
					FNXW_STRNCPY(wsText, ((wchar_t *)input)+nTotalConverted, MAX_CHARS_TO_CONVERT);
					wsText[MAX_CHARS_TO_CONVERT] = 0x00;
					nConverted = MAX_CHARS_TO_CONVERT;
				}
				else
				{
					FNXW_STRCPY(wsText, ((wchar_t *)input)+nTotalConverted);
					nConverted = (nToConvert-nTotalConverted);
				}

				// Convert to non-unicode
				memset(sText, 0, sizeof(sText));
				wcstombs(sText, wsText, MAX_CHARS_TO_CONVERT);		// This is the windows version

				// This function does not work correctly - try "schönen" or "sueño"
				//FNXW_WCSTOMBS(sText, wsText, MAX_CHARS_TO_CONVERT);


				if( nTotalConverted + nConverted < nMaxOut )
					strcat(output, sText);
				else
					break;

				nTotalConverted += nConverted;

			}

			break;
	}

	return (ERR_NOERROR);
}
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
int TextToSpeechStart(char *input, short *buffer, int output_format)
{
	int i = 0;
	unsigned int oldrate=0;
	short old_sprate=0;
	short oldspeaker=0;
	int return_code=ERR_NOERROR;

#ifdef OS_SYMBIAN
	GlobalDTPtr gp = GetGlobalDTPtr();
	LPTTS_HANDLE_T phTTS = gp->simpleData.phTTS;
	char* g_user_dict = gp->simpleData.g_user_dict;
	short *(*g_callback)(short *,long, void*) = gp->simpleData.g_callback;
#endif
	
	// Don't allow this function or other functions to be called concurrently from a thread or interrupt

#ifdef OS_SYMBIAN
	if( gp->simpleData.gDTinUse == DT_IN_USE )
		return ERR_ERROR;
	gp->simpleData.gDTinUse = DT_IN_USE;
#else
	if( gDTinUse == DT_IN_USE )
		return ERR_ERROR;
	gDTinUse = DT_IN_USE;

#endif

	((PDPH_T)(phTTS->pPHThreadData))->loadspdef=1;

	phTTS->output_buffer=buffer;
	phTTS->pKernelShareData->halting=0;
	cm_cmd_reset_comm(phTTS->pCMDThreadData, STATE_NORMAL);
	
	switch(output_format)
	{
		case WAVE_FORMAT_1M16:
			memset(buffer,0,71*2);
			if (phTTS->pKernelShareData->uiSampleRate==MULAW_SAMPLE_RATE)
			{
				DTSetSampleRate( phTTS, PC_SAMPLE_RATE );
			}
			break;
		case WAVE_FORMAT_08M16:
			memset(buffer,0,51*2);
			if (phTTS->pKernelShareData->uiSampleRate==PC_SAMPLE_RATE)
			{
				DTSetSampleRate( phTTS, MULAW_SAMPLE_RATE );
			}
			break;
	}

	i=0;
	while (input[i])
	{
#ifdef CASIO_SH3
		if (input[i] != 0x0d)
		{
#endif
			cmd_loop(phTTS,input[i]);
			if (phTTS->pKernelShareData->halting)
			{
				goto SPEECH_HALTED;
			}

#ifdef CASIO_SH3
		}
#endif
		i++;
	}
	cmd_loop(phTTS,0x0B); // force it
	if (phTTS->pKernelShareData->halting)
	{
SPEECH_HALTED:
#ifndef OS_SYMBIAN
		gReset = NO_RESET;
#else
		gp->simpleData.gReset = NO_RESET;
#endif
		phTTS->pKernelShareData->halting = 0;
		return_code = ERR_RESET;
	}
	// Change blocking flag to allow function calls
#ifdef OS_SYMBIAN
	gp->simpleData.gDTinUse = DT_AVAILABLE;
#else
	gDTinUse = DT_AVAILABLE;
#endif
	return (return_code);
}

#if !defined DICT_IN_MEMORY 
int TextToSpeechUnloadDictionary()
{
	int return_code=ERR_NOERROR;

	// Do not check gDTinUse. We are always calling this from within 
	// another function that is checking for it

#ifdef USE_NAND
	PKSD_T pKsd_t = &Ksd_t;
	int currlang = pKsd_t->lang_curr;
 
	if (pKsd_t->fdicFileHandle)
	{
 		FNX_FCLOSE(pKsd_t->fdicFileHandle);
		pKsd_t->fdicFileHandle = NULL;
	}
 	if (pKsd_t->grfdicFileHandle)
	{
		FNX_FCLOSE(pKsd_t->grfdicFileHandle);
		pKsd_t->grfdicFileHandle = NULL;
	}

#else //!USE_NAND
#ifdef OS_SYMBIAN
	GlobalDTPtr gp = GetGlobalDTPtr();
	LPTTS_HANDLE_T phTTS = gp->simpleData.phTTS;
#endif

	if ( phTTS == 0)
	{
		return -1;
	}
#ifndef BESTA
	// closes the chinese, korean, japanese files
	if(phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_free_lts_thread_data)
		phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_free_lts_thread_data(phTTS->pLTSThreadData);

	// to unload the dictionary
	unload_dictionary((void **)&(phTTS->pKernelShareData->fdic_index[phTTS->pKernelShareData->lang_curr]),
		(void **)&(phTTS->pKernelShareData->fdic_data[phTTS->pKernelShareData->lang_curr]),
		(unsigned int *)&(phTTS->pKernelShareData->fdic_entries[phTTS->pKernelShareData->lang_curr]),
		(unsigned int *)&(phTTS->pKernelShareData->fdic_bytes[phTTS->pKernelShareData->lang_curr]),
		NULL,
		NULL,
		NULL,
		MEMMAP_OFF 
		);
#endif
#ifdef ALLOC_MEMORY
	FNX_FREE(phTTS->pKernelShareData->loaded_languages);
#endif

#endif //!USE_NAND	
	return(return_code);
}
#endif //!defined DICT_IN_MEMORY

//#ifdef ALLOC_MEMORY
void CleanupMemory()
{
	KSD_T* Ksd_t = NULL;
	struct speaker_roms_s * sp_ptr = NULL;
	struct dtpc_language_tables* dtpc = NULL;
#ifdef OS_SYMBIAN
	GlobalDTPtr gp = GetGlobalDTPtr();
	TTS_HANDLE_T* phTTS = NULL;

	if(!gp)
		return;
	
	phTTS = gp->simpleData.phTTS;
#endif
	Ksd_t = phTTS->pKernelShareData;
		
#ifdef ALLOC_MEMORY
		// this needs to be fixed for multiple languages (if that ever happens)
		dtpc = Ksd_t->loaded_languages;
		FNX_FREE(dtpc);
		FNX_FREE(Ksd_t);
		Ksd_t = NULL;

		if(phTTS->pVTMThreadData)
		{
			FNX_FREE(phTTS->pVTMThreadData);
			phTTS->pVTMThreadData = NULL;
		}
#endif
		if(phTTS->pPHThreadData)
		{
			PDPH_T pDph_t = phTTS->pPHThreadData;
#ifndef CASIO_SH3
			if(pDph_t->speaker_rom_ptr)
			{
				sp_ptr = pDph_t->speaker_rom_ptr->next;
				while(sp_ptr)
				{
					FNX_FREE(pDph_t->speaker_rom_ptr);
					pDph_t->speaker_rom_ptr = sp_ptr;
					sp_ptr = pDph_t->speaker_rom_ptr->next;
				}
				FNX_FREE(pDph_t->speaker_rom_ptr);
			}
#endif //CASIO_SH3
#ifdef ALLOC_MEMORY
			if (pDph_t->pSTphsettar)
			{
				FNX_FREE (pDph_t->pSTphsettar);
				pDph_t->pSTphsettar = NULL;
			}

			if(pDph_t->delaypars)
				spcfree((unsigned short*)pDph_t->delaypars);

			FNX_FREE(pDph_t);
			pDph_t = NULL;
#endif
		}
#ifdef ALLOC_MEMORY
		phTTS->pPHThreadData = NULL;
		if(phTTS->pLTSThreadData)
			FNX_FREE(phTTS->pLTSThreadData);
		phTTS->pLTSThreadData = NULL;

		FNX_FREE(phTTS);
		phTTS = NULL;
#endif		
#ifdef OS_SYMBIAN
		FNX_FREE(gp->simpleData.g_user_dict);
		gp->simpleData.g_user_dict = NULL;
		
		FNX_FREE(gp->vtmData.tBuffer);
		gp->vtmData.tBuffer = NULL;

		DeleteDTTlsValue();
#endif
}
//#endif

#ifdef NEW_MULTI_LANG_ARCH
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
	CONST lts_func_t *temp_funcs;
//	char lang[5];
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

	return phTTS->lts_funcs[Language]->ml_lts_main(phTTS);
}

int TextToSpeechSetLTSLanguage( LPTTS_HANDLE_T phTTS,
								int Language )
{
	CONST lts_func_t *temp_funcs;
//	char lang[5];
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

CONST lts_func_t *load_lts_language(int lang_num)
{

	if (lang_num==LANG_english)
	{
		return(us_ls_main_get_lts_funcs());
	} 
#ifndef CASIO_SH3
	else if (lang_num==LANG_british)
	{
		return(uk_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_latin_american)
	{
		return(la_ls_main_get_lts_funcs());
	}
#endif //CASIO_SH3
	else if (lang_num==LANG_german)
	{
		return(gr_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_spanish)
	{
		return(sp_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_italian)
	{
		return(it_ls_main_get_lts_funcs());
	} 
	else if (lang_num==LANG_french)
	{
		return(fr_ls_main_get_lts_funcs());
	} 
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
	else if (lang_num==LANG_hebrew)
	{
		return(hb_ls_main_get_lts_funcs());
	} 	
	else
	{
		return(us_ls_main_get_lts_funcs());
	}
}
#endif //NEW_MULTI_LANG_ARCH
#else //EPSON_ARM7


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
	// added for AD (Feb 1-2005)
	phTTS->ph_funcs.char_types=char_types;

//	g_callback=callback;
	g_user_dict=(char *)user_dict;

	if (pKsd_t->lang_curr !=lang_id)
		new_lang=1;

	pKsd_t->lang_curr=lang_id;

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
#ifndef CASIO_SH3
	case LANG_british:
		phTTS->main_lts_loop=uk_lts_loop;
		break;
	case LANG_latin_american:
		phTTS->main_lts_loop=la_lts_loop;
		break;
#endif
	case LANG_italian:
		phTTS->main_lts_loop=it_lts_loop;
		break;
	case LANG_japanese:
		phTTS->main_lts_loop=jp_lts_loop;
		break;
	case LANG_hebrew:
		phTTS->main_lts_loop=hb_lts_loop;
		break;
	case LANG_korean:
		phTTS->main_lts_loop=kr_lts_loop;
		break;
	case LANG_chinese:
		phTTS->main_lts_loop=ch_lts_loop;
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
			pKsd_t->udic_data[lang_id]=((char *)user_dict)+(pKsd_t->udic_entries[0]*4)+8;
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
	case LANG_JAPANESE:
		maindict=jp_main_dict;
		break;
	case LANG_HEBREW:
		maindict=hb_main_dict;
		break;
	case LANG_KOREAN:
		maindict=kr_main_dict;
		break;
	case LANG_CHINESE:
		maindict=ch_main_dict;
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
#ifndef OS_SYMBIAN
	cur_packet_number=0;
	max_packet_number=0;
#else
	GetGlobalDTPtr()->cur_packet_number = 0;
	GetGlobalDTPtr()->max_packet_number = 0;
#endif
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
#ifndef CASIO_SH3
	case LANG_ENGLISH_UK:
		return_code=uk_lts_main(phTTS);
		break;
	case LANG_LATIN_AMERICAN:
		return_code=la_lts_main(phTTS);
		break;
#endif
	case LANG_GERMAN:
		return_code=gr_lts_main(phTTS);
		break;
		/* Fix for Epson Bug 5_3_001 */
	case LANG_FRENCH:
		return_code=fr_lts_main(phTTS);
		break;
	case LANG_ITALIAN:
		return_code=it_lts_main(phTTS);
		break;
	case LANG_JAPANESE:
		return_code=jp_lts_main(phTTS);
		break;
	case LANG_HEBREW:
		return_code=hb_lts_main(phTTS);
		break;
	case LANG_KOREAN:
		return_code=kr_lts_main(phTTS);
		break;
	case LANG_CHINESE:
		return_code=ch_lts_main(phTTS);
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
	// added for AD (Feb 1-2005)
	phTTS->ph_funcs.char_types=char_types;

//	g_callback=callback;
//	g_user_dict=(char *)user_dict;
	

	pKsd_t->phTTS = phTTS;

#ifndef EPSON_ARM7
#ifndef OS_SYMBIAN
	cur_packet_number=0;
	max_packet_number=0;
#else
	GetGlobalDTPtr()->cur_packet_number = 0;
	GetGlobalDTPtr()->max_packet_number = 0;
#endif
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
				pDph_t->tunedef[i]=fr_paul_tune;
				pDph_t->voidef_8[i]=paul;
				pDph_t->tunedef_8[i]=fr_paul_tune;
			}
			else if (spdef_ptr[i]==NULL)
			{
				pDph_t->voidef[i]=paul;
				pDph_t->tunedef[i]=fr_paul_tune;
				pDph_t->voidef_8[i]=paul;
				pDph_t->tunedef_8[i]=fr_paul_tune;
			}
			else
			{
				pDph_t->voidef[i]=spdef_ptr[i];
				pDph_t->tunedef[i]=fr_default_tune;
				pDph_t->voidef_8[i]=spdef_ptr[i];
				pDph_t->tunedef_8[i]=fr_default_tune;
			}
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
int TextToSpeechReset(LPTTS_HANDLE_T phTTS)
{
	phTTS->pKernelShareData->halting=1;
	return(ERR_NOERROR);
}


/* ******************************************************************
 *      Function Name: TextToSpeechStartTTP()
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
	int i;
	
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

	int i;
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

	for (i=0;i<37;i++)
	{
		spdef[i]=paul[i]+us_paul_tune[i];
	}
	speaker_def_ptr->HL_B1m=70;
	speaker_def_ptr->HL_B2m=90;
	speaker_def_ptr->HL_B3m=130;
	speaker_def_ptr->HL_B4m=180;
	speaker_def_ptr->HL_B5m=200;
	speaker_def_ptr->HL_B2F=250;
	speaker_def_ptr->HL_B3F=320;
	speaker_def_ptr->HL_B4F=260;
	speaker_def_ptr->HL_B5F=270;
	speaker_def_ptr->HL_F6=4800;
	speaker_def_ptr->HL_B6F=600;
	speaker_def_ptr->stress_step=10;
	speaker_def_ptr->unstress_pressure=80;
	speaker_def_ptr->stress_pressure=100;
	speaker_def_ptr->nom_sub_pressure=800;
	speaker_def_ptr->nom_fricative_opening=100;
	speaker_def_ptr->nom_glot_stop_area=0;
	speaker_def_ptr->vot_speed=1;
	speaker_def_ptr->endofphrase_spread=30;
	speaker_def_ptr->HL_num_formants=5;
	speaker_def_ptr->HL_f1_hi_shift=1800;
	speaker_def_ptr->HL_acd_f1_break=600;
	
	return(0);

}


#endif //EPSON_ARM7

