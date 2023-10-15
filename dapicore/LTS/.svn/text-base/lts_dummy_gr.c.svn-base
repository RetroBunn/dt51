#ifdef MULTIPLE_LANGUAGES_LOADED
#include "tts.h"
#ifndef WIN32
#include "simpleapi.h"
#endif
#else
#define EPSON_ARM7
#define BLD_DECTALK_DLL
#define ARM7
#define ACNA
#define i386
#define ARM7_NOSWI
#define ENGLISH
#define ENGLISH_US

#include "epsonapi.h"
#endif

CONST unsigned char gr_main_dict[]= 
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00};

void gr_lts_loop(LPTTS_HANDLE_T phTTS,unsigned short *input)
{
}

#ifdef MULTIPLE_LANGUAGES_LOADED
int gr_lts_main(LPTTS_HANDLE_T phTTS)
{
	return(1);
}

int gr_lts_language_loaded( void )
{
	return 1;
}
#else
int gr_lts_main(LPTTS_HANDLE_T phTTS)
{
	return(0);
}
#endif

CONST lts_func_t gr_lts_func = {

	LANG_german,
   /*lts_func->pLTSThreadData=*/  //NULL,


   /*lts_func->lts_loop=*/  gr_lts_loop ,
	
   /*lts_func->lts_main=*/ gr_lts_main ,
   /*lts_func->free_lts_thread_data=*/ NULL,	
   /*lts_func->unload_dictionary=*/ NULL,
   /*lts_func->ls_util_lts_init=*/ NULL,
   /*lts_func->load_dictionary=*/ NULL,
	/*lts_func->UserDictionaryHit=*/ NULL,
	/*lts_func->GetUserEntry=*/ NULL,
	/*lts_func->GetNumUserEntries=*/ NULL,
	/*lts_func->DictionaryHit=*/ NULL,
	/*lts_func->DumpDictionary=*/ NULL,
	/*lts_func->DumpUserDictionary=*/ NULL,
	/*lts_func->AddUserEntry=*/ NULL,
	/*lts_func->DeleteUserEntry=*/ NULL,
	/*lts_func->ChangeUserPhoneme=*/ NULL,
	/*lts_func->SaveUserDictionary=*/ NULL,
	//dictionary control variables // i'm not sure if there need to be here
	/*lts_func->gnInstanceCounter=*/ 0,
	/*lts_func->gpufdic_index=*/ NULL,
	/*lts_func->gpufdic_data=*/ NULL,
	/*lts_func->gufdic_entries=*/ 0,
	/*lts_func->gufdic_bytes=*/ 0,
	/*lts_func->gufdicMapObject=*/ 0,
	/*lts_func->gufdicFileHandle=*/ 0,
	/*lts_func->gufdicMapStartAddr=*/ 0,
	/*lts_func->gufdic_fc_entry=*/ NULL,
	/*lts_func->gufdic_fc_entries=*/ 0,
	/*lts_func->gpufordic_index=*/ NULL,
	/*lts_func->gpufordic_data=*/ NULL,
	/*lts_func->gufordic_entries=*/ 0,
	/*lts_func->gufordic_bytes=*/ 0,
	/*lts_func->gufordicMapObject=*/ 0,
	/*lts_func->gufordicFileHandle=*/ 0,
	/*lts_func->gufordicMapStartAddr=*/ 0
};

CONST lts_func_t *gr_ls_main_get_lts_funcs(void)
{
#ifdef WIN32_STATIC
	return(NULL);
#else
	return(&gr_lts_func);
#endif
}
