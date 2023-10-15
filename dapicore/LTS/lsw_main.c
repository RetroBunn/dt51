/*
 ***********************************************************************
 *
 *                           Copyright ©
 *	  Copyright © 2002 Fonix Corporation. All rights reserved.
 *	  Copyright © 2000-2001 Force Computers, a Solectron Company. All rights reserved.
 *    © SMART Modular Technologies 1999. All rights reserved.     
 *    © Digital Equipment Corporation 1996-1998. All rights reserved.
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
 *    File Name:    lsw_main.c
 *    Author:       Matthew Schnee
 *    Creation Date:02/29/1996
 *
 *    Functionality:
 *    lts entry point stub, for window only
 *
 ***********************************************************************
 *    Revision History:                    
 *
 *  Rev Who     Date        	Description
 *  --- -----   ----------- 	---------------------------------------
 *  001 KM   	09/23/1984   	Modified to look for default user.dic
 *                              in the HOME directory for OSF/1.
 *  002 MGS     03/10/1996      Renamed file from lsm_acna.c
 *  003 JDB     05/30/1996      Add language dependent conditionals
 *  004 GL      11/26/1996      remove dummy msdos and dtex switch
 *  005 GL		12/11/1996		remove the WIN32 language pipe hack
 *  006 KSB     02/10/1997		Fixed bugs for DTDemo fetch, and added debug code
 *  007 NCS     02/21/1997      Merged Tom's multilanguage code in.
 *  008 NCS     02/26/1997      Changed LibMain to LTSLibMain.
 *	009	NCS		04/17/1997		Moved Dictionary Reg entry path to coop.h
 *  010	GL		04/21/1997	    BATS#357  Add the code for __osf__ build
 *  011 NCS     08/06/1997      Moved Demo dict name entries to coop.h
 *  012 GL		09/25/1997      use the array for dictionary entry structure
 *                              add abbreviation dictionary support
 *                              also add UK_english support
 *  013 GL		10/23/1997      use dtalk_<language>.dic to replace dectalk.dic
 *  xxx	tek		25feb98			repair DEMO build to allow spaces in dictionary
 *								path (bats 607) and to look in additional places.
 *  014 JAW     03/04/1998      ifdef'd out code from 02/25/1998 so it won't be
 *                              compiled UNDER_CE.  When UNDER_CE is defined,
 *                              code from previous version of this file will be
 *                              used.
 *  015 CJL     03/18/1998      Removed specific path for dectalkf.h.
 *	016	tek		14may98			bats672 log failures on main dict registry keys
 *  017	tek		27may98			bats689: threadsafe instance counting
 *  018	mfg		22jun98			Added support for LANG_latin_american
 *	xxx	tek		21aug98			un-static GetDictionaryNames so it can be
 *								used by other modules.
 *  019.5 ETT	10/05/1998      Added Linux code.
 *  020	GL		11/12/1998		BATS#800  need to initialize some Spanish variables 
 *  021	GL		11/20/1998		BATS#828 use LTS_DEBUG to replace _DEBUG
 *  022	MFG		01/06/1999		Added MainDIc and UserDic support for Windows CE
 *  023	MGS		08/22/1999		Change #ifdef LTS_DEBUG to #if LTS_DEBUG because of VMS debugging code
 *								that was turned on by accident
 *  024	MGS		02/09/2000		Made the dictionary information come from a config
 *								file for __linux__ (and __osf__ in the future)
 *  025 NAL		06/12/2000		Added prototype (warning removal)
 *  026 MFG		07/31/2000		Implemented dictionary memory mapping for Windows CE/NT/95
 *  027 MFG		07/30/2000		fixed multi language dictionary memory mapping error
 *  028	MGS		10/05/2000		Redhat 6.2 and linux warning removal
 *  029	MFG		10/10/2000		Shut off dictionary mapping for WCE_EMULATION it is not Supported
 *  030 CAB		10/18/2000		Added copyright info
 *  032	MGS		01/11/2001		Added Foreigh langauge dictioanry
 *  033	MGS		02/08/2001		Fixed Linux foreign language dictionary issues
 *  034	MGS		02/19/2001		Added code to fix the foreign language dict for WIN32
 *  035 CAB		02/23/2001		Updated copyright info
 *  036	MGS		03/02/2001		Added code for multiple instances work with dictionary mapping
 *  037	MGS		05/09/2001		Some VxWorks porting BATS#972
 *  038	MGS		05/18/2001		More VxWorks porting, fixed linux demo dictionaries
 *  039	MGS		06/19/2001		Solaris Port BATS#972
 *  040	MGS		02/26/2002		ACNA updates
 *  041	MGS		04/03/2002		Single threaded lts
 *  042	MGS		04/11/2002		ARM7 port\
 *	043	cab		04/17/2001		Fixed BATS#987
 *	044	CAB		07/08/2002		Added dtdic.log to Windows CE
 *  045	MGS		07/16/2002		Added Fonix dictionary startup
 *  046 MFG		07/17/2002		Merged in CUP28PROJECT changes
 *  047 MFG		07/19/2002		Added \windows\user.dic default for CUP28PROJECT
 *	048	CAB		08/12/2002		Fixed TTSStartupExFonix() for Windows CE
 *								Changed GetDictionaryNames() and load_dictionary() to TCHAR
 *	049	MFG		10/10/2002		Fixed the User dictionary stuff for WinCE
 *	050	RDK		01/22/2003		Change to use FORCE_WINDICTDIRS for forced windows dictionaries
 *  051	MFG		02/30/2003		Fixed the wide- string convertion for the WinCe dictionary 
 ***************************************************************************/

#include "dectalkf.h"
#include "ls_def.h"

#ifdef ARM7
#include "tts.h"

#if !defined EPSON_ARM7 && !defined ALLOC_MEMORY && !defined MULTIPLE_LANGUAGES_LOADED
LTS_T   Lts_t;
#else
// declared in lsw_main2.c which is included in the language independent library
extern LTS_T   Lts_t;
#endif
#else
#define LSWMAIN_DIC
#include "coop.h"
#undef LSWMAIN_DIC
#endif // ARM7

#ifdef HLSYN									// High Compute defines
#if defined(_MSC_VER)
#pragma message("INFO: HLSYN - High Compute compile")
#endif
#elif defined(INTEGER)
#if defined(_MSC_VER)
#pragma message("INFO: INTEGER - Low Compute compile")
#endif
#endif

#include "port.h" //added for platfrom specific stuff - mlt
#include "Mandarin.h"
#include "mandarinprot.h"

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef JAPANESE
static int
u_stop(void*p) 
{
    return 0;
}
#endif

#ifdef SEPARATE_PROCESSES
struct share_data       *kernel_share;
#endif //SEPARATE_PROCESSES

#ifndef ARM7
int linux_get_dict_names(char *main_dict_name,char *user_dict_name, char *foreign_dict_name);
#endif

void default_lang(PKSD_T, unsigned int, unsigned int); // NAL warning removal

extern int ConvertToAscii(LPVOID phTTS, void *lpInput, char *szbuf, int iInType);
extern int Initialize(LPVOID pVoid);
extern int Terminate(LPVOID pVoid);

#ifdef ARM7
CONST
#endif
lts_func_t lts_func = {

#ifdef ENGLISH_US
	LANG_english,
#elif defined ENGLISH_UK
	LANG_british,
#elif defined SPANISH_SP
    LANG_spanish,
#elif defined SPANISH_LA
    LANG_latin_american,
#elif defined ITALIAN
    LANG_italian,
#elif defined GERMAN
   LANG_german,
#elif defined FRENCH
   LANG_french,
#elif defined JAPANESE
   LANG_japanese,
#elif defined HEBREW
	LANG_hebrew,
#elif defined CHINESE
	 LANG_chinese,
#elif defined KOREAN
	LANG_korean,
#else
	LANG_none,
#endif

   /*lts_func->pLTSThreadData=*/  //NULL,
#if (defined USE_NAND && defined USE_464) && (!defined CHINESE || !defined KOREAN || !defined JAPANESE || !defined ENGLISH_US)
   /*lts_func->lts_loop=*/  lts_loop_2,
#else
   /*lts_func->lts_loop=*/  lts_loop,
#endif
   /*lts_func->lts_main=*/ lts_main,
   /*lts_func->free_lts_thread_data=*/ lsw_main_free_lts_thread_data,	
#ifdef ARM7
   /*lts_func->unload_dictionary=*/ NULL,
#else
   /*lts_func->unload_dictionary=*/ unload_dictionary,
#endif
   /*lts_func->ls_util_lts_init=*/ ls_util_lts_init,
#ifdef ARM7
   /*lts_func->load_dictionary=*/ NULL,
#else
   /*lts_func->load_dictionary=*/ load_dictionary,
#endif
#ifndef ARM7
	/*lts_func->UserDictionaryHit=*/ UserDictionaryHit,
	/*lts_func->GetUserEntry=*/ GetUserEntry,
	/*lts_func->GetNumUserEntries=*/ GetNumUserEntries,
	/*lts_func->DictionaryHit=*/ DictionaryHit,
	/*lts_func->DumpDictionary=*/ DumpDictionary,
	/*lts_func->DumpUserDictionary=*/ DumpUserDictionary,
	/*lts_func->AddUserEntry=*/ AddUserEntry,
	/*lts_func->DeleteUserEntry=*/ DeleteUserEntry,
	/*lts_func->ChangeUserPhoneme=*/ ChangeUserPhoneme,
	/*lts_func->SaveUserDictionary=*/ SaveUserDictionary,
#else
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
#endif
#if defined(KOREAN) || defined(JAPANESE) || defined(CHINESE)	// || defined(SPANISH)
	ConvertToAscii,		// Function to convert wide character languages to a Romanized version that TTS can deal with
	Initialize,			// Function to initialize data for this language
	Terminate,			// Function to cleanup what was initialized
#else
	NULL,
	NULL,
	NULL,
#endif
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
	/*lts_func->gufordicMapStartAddr=*/ 0,
#ifdef CHINESE
	/* Mand_F0_machine */	Mand_F0_machine
#else
	/* Mand_F0_machine */	NULL
#endif
//#endif
};

CONST lts_func_t *ls_main_get_lts_funcs(void)
{
	return(&lts_func);
}


#ifdef WIN32

/* tek 23jan97 need the dictionary globals if we're doing the code_DLL thing */
#ifdef BLD_CORE_DLL
  S32	*gpufdic_index	= NULL;
  S32   gufdic_entries	= 0;
  S32   gufdic_bytes	= 0;
#endif /*BLD_CORE_DLL*/

#define  MAX_STRING_LENGTH  512

//tek 18aug98 make this non-static so that we can use it to find the udic directory
// RDK This routine produces (as it should) char variables, NOT TCHAR
// void GetDictionaryNames( TCHAR *, TCHAR *, TCHAR *, TCHAR * );
void GetDictionaryNames( LPTTS_HANDLE_T, char *, char *, char *, char * );

#endif // WIN32

#if defined _UNIX_LIKE_


/* PROTOTYPES */
extern void default_lang( PKSD_T pKsd_t,unsigned int lang_code, unsigned int ready_code );
 

#endif /* _UNIX_LIKE_ */

/*FUNCTION_HEADER**********************
 * NAME:	;lts_main
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int lts_main(LPTTS_HANDLE_T phTTS)
{
#ifdef UNDER_CE	//29oct99 mfg convert unicode string to char string for Windows CE
char ch_dictionary_file_name[500];
#endif
  /* 
   * Added a variable to get current instance kernel share data and
   * initialize from phTTS structure  :MI : MVP
   */
  PKSD_T pKsd_t = phTTS->pKernelShareData;
  PLTS_T pLts_t = NULL;
  int nDicLoad;
  int jDicLoad=0;

#ifdef ARM7
#if defined(EPSON_ARM7) || defined (OS_SYMBIAN) || defined (OS_PALM)
	pLts_t=phTTS->pLTSThreadData;
	if(pLts_t)
	memset(pLts_t,0,sizeof(LTS_T));
#else
	memset(&Lts_t,0,sizeof(LTS_T));
	pLts_t=&Lts_t;
	phTTS->pLTSThreadData=&Lts_t;
#endif	
#endif


#ifdef SEPARATE_PROCESSES
	kernel_share = (struct share_data *)FNX_MALLOC(sizeof(struct share_data));
#endif

#ifdef WIN32
	// RDK These should not be TCHAR
	char szMainDict[MAX_STRING_LENGTH];
	char szUserDict[MAX_STRING_LENGTH];
	char szAbbrDict[MAX_STRING_LENGTH];
	char szForeignDict[MAX_STRING_LENGTH];
	int fDicLoad;

	if((pLts_t = (PLTS_T)FNX_CALLOC(1, sizeof(LTS_T)))== NULL)
		return(MMSYSERR_NOMEM);
  
	/* MVP :Associate LTS thread specific data handle to the current speech object*/
	phTTS->pLTSThreadData = pLts_t ;
  

	/* GL 09/25/1997 add szAbbrDict to support abbr dictionary */
	GetDictionaryNames(phTTS, szMainDict, szUserDict, szAbbrDict, szForeignDict );

	if (phTTS->dictionary_file_name[0])
	{
		// RDK Dictionary Names need to be char not wchar
		#ifdef UNDER_CE	//29oct99 mfg convert unicode string to char string for Windows CE
		WideStringtoAsciiString(ch_dictionary_file_name, phTTS->dictionary_file_name, 500);
		FNX_STRCPY(szMainDict, ch_dictionary_file_name);
		#else
		FNX_STRCPY(szMainDict, phTTS->dictionary_file_name);
		#endif
	}

#if defined(KOREAN)	// || defined(SPANISH)
	if( phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize )
	{
		PLTS_T pLts = (PLTS_T)phTTS->pLTSThreadData;
		jDicLoad = phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize( &pLts->LtsRules );
	}
#elif defined(JAPANESE) || defined(CHINESE)
	if( phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize )
		jDicLoad = phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize( phTTS->pLTSThreadData );
#endif

   // MVP : Load the main dictionary only once for all instances of DECtalk Speech engine.
	if(!phTTS->lts_funcs[phTTS->cur_lts_lang]->gnInstanceCounter || phTTS->dictionary_file_name[0])
	{	

		// Load the main dictionary
		nDicLoad = load_dictionary( phTTS,
						&(pKsd_t->fdic_index[DICT_LANG]),
						&(pKsd_t->fdic_data[DICT_LANG]),
						&(pKsd_t->fdic_entries[DICT_LANG]),
						&(pKsd_t->fdic_bytes[DICT_LANG]),
#ifdef CHEESY_DICT_COMPRESSION
						&(pKsd_t->fdic_fc_entry[DICT_LANG]),
						&(pKsd_t->fdic_fc_entries[DICT_LANG]),
#endif
						szMainDict,
						TRUE,
						TRUE,
						(DT_HANDLE*)&(pKsd_t->fdicMapObject[DICT_LANG]),
						(DT_HANDLE*)&(pKsd_t->fdicFileHandle[DICT_LANG]),
						(LPVOID*)&(pKsd_t->fdicMapStartAddr[DICT_LANG]),
						MEMMAP_ON);

		// Load foreign words dictionary
		if(!phTTS->lts_funcs[phTTS->cur_lts_lang]->gnInstanceCounter)
		{	
			fDicLoad = load_dictionary( phTTS,
						&(pKsd_t->foreigndic_index[DICT_LANG]),
						&(pKsd_t->foreigndic_data[DICT_LANG]),
						&(pKsd_t->foreigndic_entries[DICT_LANG]),
						&(pKsd_t->foreigndic_bytes[DICT_LANG]),
#ifdef CHEESY_DICT_COMPRESSION
						NULL,
						NULL,
#endif
						szForeignDict,
						FALSE,
						FALSE,
						(DT_HANDLE*)&(pKsd_t->foreigndicMapObject[DICT_LANG]),
						(DT_HANDLE*)&(pKsd_t->foreigndicFileHandle[DICT_LANG]),
						(LPVOID*)&(pKsd_t->foreigndicMapStartAddr[DICT_LANG]),
						MEMMAP_ON);
		}

		/*	MVP: On the following errors notify TextToSpeechStartup by 
			returning the error. */
		if( nDicLoad == MMSYSERR_INVALPARAM || 
			nDicLoad == MMSYSERR_NOMEM ||
 			nDicLoad == MMSYSERR_ERROR  || 
			jDicLoad)
		{
			if (jDicLoad)
			{
				nDicLoad=MMSYSERR_INVALPARAM;
			}
			return (nDicLoad);
		}

		if(!phTTS->lts_funcs[phTTS->cur_lts_lang]->gnInstanceCounter)
		{
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gpufdic_index = pKsd_t->fdic_index[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gpufdic_data = pKsd_t->fdic_data[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdic_entries = pKsd_t->fdic_entries[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdic_bytes = pKsd_t->fdic_bytes[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdicMapObject=pKsd_t->fdicMapObject[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdicFileHandle=pKsd_t->fdicFileHandle[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdicMapStartAddr=pKsd_t->fdicMapStartAddr[DICT_LANG];
#ifdef CHEESY_DICT_COMPRESSION
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdic_fc_entry=pKsd_t->fdic_fc_entry[DICT_LANG];         /*   total entries in dictionarys */
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdic_fc_entries=pKsd_t->fdic_fc_entries[DICT_LANG];         /*   total entries in dictionarys */
#endif
			
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gpufordic_index = pKsd_t->foreigndic_index[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gpufordic_data = pKsd_t->foreigndic_data[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufordic_entries = pKsd_t->foreigndic_entries[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufordic_bytes = pKsd_t->foreigndic_bytes[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufordicMapObject=pKsd_t->foreigndicMapObject[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufordicFileHandle=pKsd_t->foreigndicFileHandle[DICT_LANG];
			phTTS->lts_funcs[phTTS->cur_lts_lang]->gufordicMapStartAddr=pKsd_t->foreigndicMapStartAddr[DICT_LANG];
		}
	}
	else
	{
		pKsd_t->fdic_index[DICT_LANG] = phTTS->lts_funcs[phTTS->cur_lts_lang]->gpufdic_index;
		pKsd_t->fdic_data[DICT_LANG] = phTTS->lts_funcs[phTTS->cur_lts_lang]->gpufdic_data;
		pKsd_t->fdic_entries[DICT_LANG] = phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdic_entries;
		pKsd_t->fdic_bytes[DICT_LANG] = phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdic_bytes;
		pKsd_t->fdicMapObject[DICT_LANG]=phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdicMapObject;
		pKsd_t->fdicFileHandle[DICT_LANG]=phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdicFileHandle;
		pKsd_t->fdicMapStartAddr[DICT_LANG]=phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdicFileHandle;
#ifdef CHEESY_DICT_COMPRESSION
		pKsd_t->fdic_fc_entry[DICT_LANG]=phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdic_fc_entry;         /*   total entries in dictionarys */
		pKsd_t->fdic_fc_entries[DICT_LANG]=phTTS->lts_funcs[phTTS->cur_lts_lang]->gufdic_fc_entries;         /*   total entries in dictionarys */
#endif
		
		pKsd_t->foreigndic_index[DICT_LANG] = phTTS->lts_funcs[phTTS->cur_lts_lang]->gpufordic_index;
		pKsd_t->foreigndic_data[DICT_LANG] = phTTS->lts_funcs[phTTS->cur_lts_lang]->gpufordic_data;
		pKsd_t->foreigndic_entries[DICT_LANG] = phTTS->lts_funcs[phTTS->cur_lts_lang]->gufordic_entries;
		pKsd_t->foreigndic_bytes[DICT_LANG] = phTTS->lts_funcs[phTTS->cur_lts_lang]->gufordic_bytes;
		pKsd_t->foreigndicMapObject[DICT_LANG]=phTTS->lts_funcs[phTTS->cur_lts_lang]->gufordicMapObject;
		pKsd_t->foreigndicFileHandle[DICT_LANG]=phTTS->lts_funcs[phTTS->cur_lts_lang]->gufordicFileHandle;
		pKsd_t->foreigndicMapStartAddr[DICT_LANG]=phTTS->lts_funcs[phTTS->cur_lts_lang]->gufordicMapStartAddr;
	}

	/* GL 09/25/1997 use the array for dictionary entry structure */
	/* also add UK_english support */
	nDicLoad = load_dictionary( phTTS,
		&(pKsd_t->udic_index[DICT_LANG]),
		&(pKsd_t->udic_data[DICT_LANG]),
		&(pKsd_t->udic_entries[DICT_LANG]),
		&(pKsd_t->udic_bytes[DICT_LANG]),
#ifdef CHEESY_DICT_COMPRESSION
		NULL,
		NULL,
#endif
		szUserDict,
		FALSE,
		TRUE,
		NULL,
		NULL,
		NULL,
		MEMMAP_OFF );


	/*MVP : On the following errors notify TextToSpeechStartup 
		by returning the error. 	*/
	// tek 27may98 bats 689:
	// do the right thing based on whether we managed to load or not..
	if(nDicLoad == MMSYSERR_INVALPARAM || nDicLoad == MMSYSERR_NOMEM ||
		nDicLoad == MMSYSERR_ERROR)
	{
		return(nDicLoad);
	}
	else
	{
		// bump the count, then unlock.
		phTTS->lts_funcs[phTTS->cur_lts_lang]->gnInstanceCounter++;
	}
	
#endif /* #ifdef WIN32 */

#if defined _UNIX_LIKE_
	int fDicLoad;
	
	char main_dict_name[1000];
	char foreign_dict_name[1000];
	char user_dict_name[1000];
	
	linux_get_dict_names(main_dict_name,user_dict_name,foreign_dict_name);
	if (phTTS->dictionary_file_name[0])
	{
		FNX_STRCPY(main_dict_name,phTTS->dictionary_file_name);
	}
	/* Initialize thread error field to no error */
	phTTS->uiThreadError = MMSYSERR_NOERROR;
	
	if((pLts_t = (PLTS_T)FNX_CALLOC(1,sizeof(LTS_T)))== NULL)
	{
		return(MMSYSERR_NOMEM);
	}
	else 
	{
		/* MVP :Associate LTS thread specific data handle to the current speech object */
		phTTS->pLTSThreadData = pLts_t ;

#ifdef KOREAN
	if( phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize )
	{
		PLTS_T pLts = (PLTS_T)phTTS->pLTSThreadData;
		jDicLoad = phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize( &pLts->LtsRules );
	}
#elif defined(JAPANESE) || defined(CHINESE)
	if( phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize )
		jDicLoad = phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize( phTTS->pLTSThreadData );
#endif

		// Load main dictionary
		nDicLoad = load_dictionary( phTTS, 
                                            &(pKsd_t->fdic_index[DICT_LANG]),
                                            &(pKsd_t->fdic_data[DICT_LANG]),
                                            &(pKsd_t->fdic_entries[DICT_LANG]),
                                            &(pKsd_t->fdic_bytes[DICT_LANG]),
#ifdef CHEESY_DICT_COMPRESSION
                                            NULL, NULL,
#endif
                                            main_dict_name,
                                            TRUE,FALSE,
                                            &(pKsd_t->fdicMapObject[DICT_LANG]),
                                            &(pKsd_t->fdicFileHandle[DICT_LANG]),
                                            (LPVOID*)&(pKsd_t->fdicMapStartAddr[DICT_LANG]),
                                            MEMMAP_ON);
		
		// Load foreign words dictionary
		fDicLoad = load_dictionary( phTTS,
                                            &(pKsd_t->foreigndic_index[DICT_LANG]),
                                            &(pKsd_t->foreigndic_data[DICT_LANG]),
                                            &(pKsd_t->foreigndic_entries[DICT_LANG]),
                                            &(pKsd_t->foreigndic_bytes[DICT_LANG]),
#ifdef CHEESY_DICT_COMPRESSION
                                            NULL, NULL,
#endif
                                            foreign_dict_name,
                                            FALSE,FALSE,
                                            &(pKsd_t->foreigndicMapObject[DICT_LANG]),
                                            &(pKsd_t->foreigndicFileHandle[DICT_LANG]),
                                            (LPVOID*)&(pKsd_t->foreigndicMapStartAddr[DICT_LANG]),
                                            MEMMAP_ON);
		
		if( nDicLoad == MMSYSERR_INVALPARAM || nDicLoad == MMSYSERR_NOMEM ||
			nDicLoad == MMSYSERR_ERROR)
		{
			FNX_FPRINTF(stderr,"DECtalk cannot run without the dictionary file %s\n",
				main_dict_name);
			return (nDicLoad);
		}
		
		// Load User dictionary
		if( user_dict_name[0] )
		{
			/* GL 09/25/1997 use the array for dictionary entry structure */
			/*               also add UK_english support */
			load_dictionary(  phTTS,
                                          &(pKsd_t->udic_index[DICT_LANG]),
                                          &(pKsd_t->udic_data[DICT_LANG]),
                                          &(pKsd_t->udic_entries[DICT_LANG]),
                                          &(pKsd_t->udic_bytes[DICT_LANG]),
#ifdef CHEESY_DICT_COMPRESSION
                                            NULL, NULL,
#endif
                                          user_dict_name,
                                          FALSE,FALSE,
                                          NULL,
                                          NULL,
                                          NULL,
                                          MEMMAP_OFF );
		}
    }

#endif /* _UNIX_LIKE_ */

#if defined(OS_SYMBIAN) || defined(OS_PALM)
	if(!pLts_t)
	{
		if((pLts_t = (PLTS_T)FNX_CALLOC(1,sizeof(LTS_T)))== NULL)
		{
			return(-1);
		}
		else 
		{
			
			phTTS->pLTSThreadData = pLts_t ;
			
#ifdef KOREAN
			if( phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize )
			{
				PLTS_T pLts = (PLTS_T)phTTS->pLTSThreadData;
				jDicLoad = phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize( &pLts->LtsRules );
			}
#elif defined(JAPANESE) || defined(CHINESE)
			if( phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize )
				nDicLoad = phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize( phTTS->pLTSThreadData );
#else
			// Load the main dictionary
			nDicLoad = load_dictionary( phTTS, (void **)&(pKsd_t->fdic_index[DICT_LANG]),
				(void **)&(pKsd_t->fdic_data[DICT_LANG]),
				(unsigned int *)&(pKsd_t->fdic_entries[DICT_LANG]),
				(unsigned int *)&(pKsd_t->fdic_bytes[DICT_LANG]),
				phTTS->dict_path,
				TRUE, FALSE,
				(DT_HANDLE*)&(pKsd_t->fdicMapObject[DICT_LANG]),
				(DT_HANDLE*)&(pKsd_t->fdicFileHandle[DICT_LANG]),
				(LPVOID*)&(pKsd_t->fdicMapStartAddr[DICT_LANG]),
				MEMMAP_OFF); 
#endif			
			if( nDicLoad != 0)
			{
				return (nDicLoad);
			}
			
		}
	}
#elif defined(ARM7) && !defined(DICT_IN_MEMORY)
	phTTS->pLTSThreadData = pLts_t ;

#ifdef KOREAN
	if( phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize )
	{
		PLTS_T pLts = (PLTS_T)phTTS->pLTSThreadData;
		nDicLoad = phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize( &pLts->LtsRules );
	}
#elif defined(JAPANESE) || defined(CHINESE)
	if( phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize )
		nDicLoad = phTTS->lts_funcs[phTTS->cur_lts_lang]->ml_Initialize( phTTS );
#else

	// Load the main dictionary
#ifndef USE_NAND
#ifdef USE_MEMFILE_IO
	nDicLoad = load_dictionary( phTTS, (void **)&(pKsd_t->fdic_index[DICT_LANG]),
		(void **)&(pKsd_t->fdic_data[DICT_LANG]),
		(unsigned int *)&(pKsd_t->fdic_entries[DICT_LANG]),
		(unsigned int *)&(pKsd_t->fdic_bytes[DICT_LANG]),
		phTTS->dict_path,
		TRUE, FALSE,
		(DT_HANDLE*)&(pKsd_t->fdicMapObject[DICT_LANG]),
		(DT_HANDLE*)&(pKsd_t->fdicFileHandle[DICT_LANG]),
		(LPVOID*)&(pKsd_t->fdicMapStartAddr[DICT_LANG]),
	 	MEMMAP_ON);   
	//Turned MEMMAP_ON so that the dictionary is not loaded twice
#else
		nDicLoad = load_dictionary( phTTS, (void **)&(pKsd_t->fdic_index[DICT_LANG]),
		(void **)&(pKsd_t->fdic_data[DICT_LANG]),
		(unsigned int *)&(pKsd_t->fdic_entries[DICT_LANG]),
		(unsigned int *)&(pKsd_t->fdic_bytes[DICT_LANG]),
		phTTS->dict_path,
		TRUE, FALSE,
		(DT_HANDLE*)&(pKsd_t->fdicMapObject[DICT_LANG]),
		(DT_HANDLE*)&(pKsd_t->fdicFileHandle[DICT_LANG]),
		(LPVOID*)&(pKsd_t->fdicMapStartAddr[DICT_LANG]),
		MEMMAP_OFF);   
#endif  //  defined (USE_MEMFILE_IO)
#else
	nDicLoad = 0;
#endif //USE_NAND

#endif	
	if( nDicLoad != 0)
	{
		return (nDicLoad);
	}
#endif

	ls_util_lts_init( pLts_t, pKsd_t );
	phTTS->ph_funcs.default_lang(pKsd_t, lts_func.language, LANG_lts_ready);

#ifdef ACNA
	lsa_util_init_lang(pLts_t);
#endif
	
	ls_task_main(phTTS);
#if defined ARM7
	return 0;
#else
	return MMSYSERR_NOERROR;
#endif
}       


/*FUNCTION_HEADER**********************
 * NAME:	;lsw_main_free_lts_thread_data
 * DESC: 	This is where we do cleanup
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int lsw_main_free_lts_thread_data(PLTS_T pLts_t)
{

#ifdef KOREAN
		if( lts_func.ml_Terminate )
			lts_func.ml_Terminate( &pLts_t->LtsRules );
#elif defined(JAPANESE) || defined(CHINESE) || defined(KOREAN)
		if( lts_func.ml_Terminate )
			lts_func.ml_Terminate( pLts_t );
#endif

#ifdef ALLOC_MEMORY
	if (pLts_t!=NULL)
	{
		FNX_FREE(pLts_t);
	}
#endif
	return(0);
}



/*extern int fc_index; */    /*MVP MI */

#ifdef WIN32
#ifndef UNDER_CE

/**********************************************************************/
/*                                                                    */
/*  Function: IsFileAccessible										  */
/*  Author:	  tek		                                              */
/*  Date:	  25feb98						                          */
/*                                                                    */
/*  Abstract:                                                         */
/*			Handy routine to see if a file is accessible              */
/*                                                                    */
/*  Input:                                                            */
/*      Arguments:													  */
/*					char * szFileName		Entrie pathname with      */
/*											filename                  */
/*                                                                    */
/*  Return Value:	BOOL											  */
/*					FALSE	Error									  */
/*					TRUE	File was found							  */
/*                                                                    */
/*      Comments:                                                     */
/*                                                                    */
/**********************************************************************/
BOOL IsFileAccessible(char *szFileName)
{
	if (!_access(szFileName,0)) // check for existence only
	{
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}
}

/**********************************************************************/
/*                                                                    */
/*  Function: FindFileOnPath			                              */
/*  Author:				                                              */
/*  Date:				                                              */
/*                                                                    */
/*  Abstract:                                                         */
/*				 Handy routine to look on the path					  */
/*                                                                    */
/*  Input:                                                            */
/*      Arguments: 	char * szResultstring   The entire path name with */
/*											filename				  */
/*					char * szFileName		File name                 */
/*                                                                    */
/*  Return Value:	BOOL											  */
/*					FALSE	Error									  */
/*					TRUE	File was found							  */
/*                                                                    */
/*      Comments:                                                     */
/*                                                                    */
/**********************************************************************/
BOOL FindFileOnPath(char *szResultString, char *szFileName)
{
	// find szFileName on PATH; return TRUE if successful.
	// WARNING: make sure the destination string is big enough!!
	_searchenv(szFileName, "PATH", szResultString);
	if ( (FNX_STRLEN(szResultString) != 0) && (IsFileAccessible(szResultString)) )
	{
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}
}

/**********************************************************************/
/*                                                                    */
/*  Function: FindFileInCurrentDirectory                              */
/*  Author:				                                              */
/*  Date:				                                              */
/*                                                                    */
/*  Abstract:                                                         */
/*				Handy routine to look in the "current directory"	  */
/*                                                                    */
/*  Input:                                                            */
/*      Arguments: 	char * szResultstring   The entire path name with */
/*											filename				  */
/*					char * szFileName		File name                 */
/*                                                                    */
/*  Return Value:	BOOL											  */
/*					FALSE	Error									  */
/*					TRUE	File was found							  */
/*                                                                    */
/*      Comments:                                                     */
/*                                                                    */
/**********************************************************************/
BOOL FindFileInCurrentDirectory(char *szResultString, char *szFileName)
{
	// look in the current directory for a file, return TRUE is successful
	// WARNING: make sure the destination string is big enough!

	char szTempBuf[_MAX_PATH*2]="";
	int	iStringLength=0;

	if (!_getcwd(szTempBuf, _MAX_PATH))
	{
		//oops, error?
		return (FALSE);
	}

	iStringLength = FNX_STRLEN(szTempBuf);
	if (iStringLength == 0)
	{
		// oops, error?
		return (FALSE);
	}
	// correct for the possible missing '\' at the end of the path
	if (szTempBuf[iStringLength] != '\\')
	{
		szTempBuf[iStringLength] = '\\';
		szTempBuf[iStringLength+1] = '\0';
	}

	// glue it together
	FNX_STRCAT(szTempBuf,szFileName);
	FNX_STRCPY(szResultString, szTempBuf);
	if (IsFileAccessible(szTempBuf))
	{
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}
}
#endif // UNDER_CE

#ifdef DEMO
#ifdef UNDER_CE
/*FUNCTION_HEADER**********************
 * NAME:	;GetDemoDictionaryNames
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void GetDemoDictionaryNames( char * szMainDict, char * szUserDict, char *szForeignDict )
{
	TCHAR tsPath[_MAX_PATH];

	GetModuleFileName(NULL, tsPath, _MAX_PATH);
	FNXA_SPRINTF(szUserDict,	"%S\\user.dic", tsPath);
	FNXA_SPRINTF(szMainDict,	"%S\\%s", tsPath, szMainDictDef);
	FNXA_SPRINTF(szForeignDict,	"%S\\%s", tsPath, szForeignDictDef);
}

#else

void GetDemoDictionaryNames( char * szMainDict, char * szUserDict, char *szForeignDict )
{
	char temp[20];
	// tek 25feb98 lots of changes here to be more rational about looking for the dictionaries.
	// the first place we look is the old parse-the-command-line place, and if
	// that fails we then look in the "current directory", and then finally on the
	// PATH. Note that the user dictionary and the main dictionary go through this 
	// process separately, so they may not end up coming from the same place; this
	// is probably good, because this would allow a common main dictionary (placed
	// on the path), and separate user dictionaries (in the "current", or "working",
	// directory).
	
	char szResultPath[_MAX_PATH*2]="";
	char szDefUserDic[256]="user.dic";
	
	LPTSTR cmd_line = GetCommandLine();
	char new_cmd_line[512];
	int cmd_ptr = 0;
	
	while (cmd_line[cmd_ptr] != '\0' && cmd_line[cmd_ptr] != ' ')	
		cmd_ptr++;
	while (cmd_line[cmd_ptr] != '\\' && cmd_ptr != 0)				
		cmd_ptr--;
	if (cmd_ptr != 0)	
		cmd_ptr++;
	cmd_line[cmd_ptr] = '\0';
	
	// tek 25feb98 we have to do this step before we ever use the cmdline-based
	// string.. 
	if (cmd_line[0] == '"')	
		FNX_STRCPY(new_cmd_line,cmd_line+1);	// Win95 addes a " to the beginning
	else					
		FNX_STRCPY(new_cmd_line,cmd_line);  
	
	
	FNX_SPRINTF(szUserDict, "%s%s", cmd_line, szDefUserDic);  // tek 25feb98 be consistent
	
	/* DEMO_DICT_DEF is defined in coop.h -- ncs 06aug97 */
	FNX_STRCPY(temp, szMainDictDef);
	
	FNX_SPRINTF(szMainDict, "%s%s", new_cmd_line, temp);
	FNX_SPRINTF(szForeignDict, "%s%s", new_cmd_line, szForeignDictDef);
	
	// tek 25feb98 OK, we have the defaults. Now go try to find the existing files.
	// ***************************************
	//           main dictionary..
	// ***************************************
	// first, the "old way".. 
	if (IsFileAccessible(szMainDict))
	{
		// do nothing, it's OK
	}
	else if (FindFileInCurrentDirectory(szResultPath, szMainDictDef))
	{
		FNX_STRCPY(szMainDict, szResultPath); //use this one
	}
	else if (FindFileOnPath(szResultPath, szMainDictDef))
	{
		FNX_STRCPY(szMainDict, szResultPath); // use this one
	}
	else
	{
		OutputDebugString(_T("Failed to find MAIN dictionary\n"));
	}
	
	// ***************************************
	//           user dictionary..
	// ***************************************
	// first, the "old way".. 
	if( IsFileAccessible(szUserDict) )
	{
		// do nothing, it's OK
	}
	else if (FindFileInCurrentDirectory(szResultPath, szDefUserDic))
	{
		FNX_STRCPY(szUserDict, szResultPath); //use this one
	}
	else if (FindFileOnPath(szResultPath, szDefUserDic))
	{
		FNX_STRCPY(szUserDict, szResultPath); // use this one
	}
	else
	{
		OutputDebugString(_T("Failed to find USER dictionary\n"));
	}
	
	// ***************************************
	//           foreign words dictionary..
	// ***************************************
	if (IsFileAccessible(szForeignDict))
	{
		// do nothing, it's OK
	}
	else if (FindFileInCurrentDirectory(szResultPath, szForeignDictDef))
	{
		FNX_STRCPY(szForeignDict, szResultPath); //use this one
	}
	else if (FindFileOnPath(szResultPath, szForeignDictDef))
	{
		FNX_STRCPY(szForeignDict, szResultPath); // use this one
	}
	else
	{
		OutputDebugString(_T("Failed to find foreign dictionary\n"));
	}
	
	// if we're in debug, print the results..
#if LTS_DEBUG
	{
		char szTemp[_MAX_PATH*3]="";
		FNX_SPRINTF(szTemp, "Main dictionary at %s\n",szMainDict);
		OutputDebugString(szTemp);
		FNX_SPRINTF(szTemp, "User dictionary at %s\n",szUserDict);
		OutputDebugString(szTemp);
	}
#endif //LTS_DEBUG
	
}
#endif // UNDER_CE
#endif // DEMO

/**********************************************************************/
/*                                                                    */
/*  Function: GetDictionaryNames                                      */
/*  Author: Bill Hallahan                                             */
/*  Date: October 5, 1994                                             */
/*                                                                    */
/*                                                                    */
/*  Abstract:                                                         */
/*                                                                    */
/*			This function gets the main, user, abbreviation and       */
/*			foreign language dictionary names from the registry.      */
/*                                                                    */
/*  Input:                                                            */
/*                                                                    */
/*    szMainDict     A pointer to a string that will contain the      */
/*                   name of the main dictionary.                     */
/*                   The returned value will be NULL terminated.      */
/*                                                                    */
/*    szUserDict     A pointer to a string that will contain the      */
/*                   name of the user dictionary.       			  */
/*                   The returned value will be NULL terminated.      */
/*																	  */
/*	  szAbbrDict     A pointer to a string that will contain the      */
/*                   name of the abbreviations dictionary.            */
/*                   The returned value will be NULL terminated.      */
/*																	  */
/*	  szForeignDict  A pointer to a string that will contain the      */
/*                   name of the foreign language dictionary.         */
/*                   The returned value will be NULL terminated.      */
/*                                                                    */
/*      Arguments: 	char * szMainDict                                 */
/*					char * szUserDict                                 */
/*					char * szAbbrDict								  */
/*					char * szForeignDict							  */
/*                                                                    */
/*      Return Value: void                                            */
/*                                                                    */
/*      Comments:                                                     */
/*                                                                    */
/**********************************************************************/
void GetDictionaryNames( LPTTS_HANDLE_T phTTS,char * szMainDict, char * szUserDict, 
						 char * szAbbrDict, char *szForeignDict )
{
#ifdef FORCE_WINDICTDIRS
	// Force all dictionary paths to be in the Windows directory
	FNX_SPRINTF(szUserDict,		"\\windows\\%s", "user.dic");
	FNX_SPRINTF(szMainDict,		"\\windows\\%s", szMainDictDef);
	FNX_SPRINTF(szForeignDict,	"\\windows\\%s", szForeignDictDef);
#else
	HKEY hKey;
	DWORD dwType;
	DWORD cbData;
	PKSD_T pKsd_t=phTTS->pKernelShareData;
	TCHAR tsMainDict[MAX_STRING_LENGTH];
	TCHAR tsUserDict[MAX_STRING_LENGTH];
	TCHAR tsForeignDict[MAX_STRING_LENGTH];
	
#ifdef DEMO
	GetDemoDictionaryNames( szMainDict, szUserDict, szForeignDict );
	return;
#endif


	/********************************************************************/
	/*  Get the user dictionary.                                        */
	/********************************************************************/
	if ( RegOpenKeyEx( HKEY_CURRENT_USER, szCurrentUsersDECtalk, 0, KEY_QUERY_VALUE, &hKey ) != ERROR_SUCCESS )
	{
		FNX_STRCPY( szUserDict, szUserDictDef );
	}
	else
	{
		cbData = MAX_STRING_LENGTH;
		if ( RegQueryValueEx( hKey, _T("UserDict"), NULL, &dwType, (LPBYTE)tsUserDict, &cbData ) != ERROR_SUCCESS )
		{
			FNX_STRCPY( szUserDict, szUserDictDef );
		}
		else
		{
#ifdef UNICODE //convert wide string to char string for windows CE
			WideStringtoAsciiString(szUserDict, tsUserDict, MAX_STRING_LENGTH);
#else
			FNX_STRCPY(szUserDict, tsUserDict);
#endif
			RegCloseKey( hKey );
		}
	}

	//********************************************************************
	//  Get the main and foreign words dictionary path from the registry.
	//********************************************************************
  if (!phTTS->lts_funcs[phTTS->cur_lts_lang]->gnInstanceCounter)
  {
	  // Open the registry path
	  if ( RegOpenKeyEx( HKEY_LOCAL_MACHINE, szLocalMachineDECtalk, 0, KEY_QUERY_VALUE, &hKey ) != ERROR_SUCCESS )
	  {
		  FILE *fpDicLogFile = NULL;
		  
		  fpDicLogFile = FNX_FOPEN(_T("\\dtdic.log"), _T("a+"));
		  if (fpDicLogFile)
		  {	
			  TCHAR tsDateBuf[64];
			  TCHAR tsTimeBuf[64];
			  // log the pertinent info
			  _tstrdate(tsDateBuf);
			  _tstrtime(tsTimeBuf);
			  FNX_FPRINTF(fpDicLogFile, _T("%s %s : Dictionary key %s not found; using default name\n"),
				  tsDateBuf, tsTimeBuf, szLocalMachineDECtalk);
			  FNX_FFLUSH(fpDicLogFile);
			  FNX_FCLOSE(fpDicLogFile);
		  }
		  
		  FNX_STRCPY( szMainDict, szMainDictDef );
		  FNX_STRCPY( szForeignDict, szForeignDictDef );
	  }
		else
		{	
			// Look for the Main dictionary path in the registry
			cbData = MAX_STRING_LENGTH;
			if ( RegQueryValueEx( hKey, _T("MainDict"), NULL, &dwType, tsMainDict, &cbData ) != ERROR_SUCCESS )
			{
				// If not found log an error
				FILE *fpDicLogFile = NULL;
				fpDicLogFile = FNX_FOPEN(_T("\\dtdic.log"), _T("a+"));
				if( fpDicLogFile )
				{	
					TCHAR tsDateBuf[64];
					TCHAR tsTimeBuf[64];
					
					_tstrdate(tsDateBuf);
					_tstrtime(tsTimeBuf);
					FNX_FPRINTF(fpDicLogFile, 
						_T("%s %s : Dictionary key MainDict not found; using default name\n"),
						tsDateBuf, tsTimeBuf);
					FNX_FFLUSH(fpDicLogFile);
					FNX_FCLOSE(fpDicLogFile);
				}
				// Use default main dictionary name
				FNX_STRCPY( szMainDict, szMainDictDef );
			}
			else
			{
#ifdef UNICODE				
				WideStringtoAsciiString(szMainDict, tsMainDict, MAX_STRING_LENGTH);
#else
				FNX_STRCPY( szMainDict, tsMainDict );
#endif
			}
			
			// Loof for the Foreign Words dictionary path in the registry
			cbData = MAX_STRING_LENGTH;
			if ( RegQueryValueEx( hKey, _T("ForeignDict"), NULL, &dwType, tsForeignDict, &cbData ) != ERROR_SUCCESS )
			{
				// If not found log an error
				FILE *fpDicLogFile = NULL;
				
				fpDicLogFile = FNX_FOPEN(_T("\\dtdic.log"), _T("a+"));
				if (fpDicLogFile)
				{	
					TCHAR tsDateBuf[64];
					TCHAR tsTimeBuf[64];
					_tstrdate(tsDateBuf);
					_tstrtime(tsTimeBuf);
					FNX_FPRINTF(fpDicLogFile, 
						_T("%s %s : Foreign Dictionary key ForeignDict not found; using default name\n"),
						tsDateBuf, tsTimeBuf);
					FNX_FFLUSH(fpDicLogFile);
					FNX_FCLOSE(fpDicLogFile);
				}
				// Use default foreign words dictionary name
				FNX_STRCPY( szForeignDict, szForeignDictDef );
			}
			else
			{
#ifdef UNICODE
				WideStringtoAsciiString(szForeignDict, tsForeignDict, MAX_STRING_LENGTH);
#else
				FNX_STRCPY(szForeignDict, tsForeignDict);
#endif	
			}

			// close the registry key
			RegCloseKey( hKey );
		}
	}
#endif	//FORCE_WINDICTDIRS
}

BOOL WINAPI _CRT_INIT( HINSTANCE hinstDLL, DWORD fdwReason, 
	LPVOID lpReserved );

/* tek 23jan97 add the entrypoint function and use it to load/unload dictionaries. */
/* changed name from the request of Kevinb. ncs 26feb97 */
/**********************************************************************/
/**********************************************************************/
/*                                                                    */
/*  Function: LTSLibMain                                              */
/*                                                                    */
/*  Abstract:                                                         */
/*                                                                    */
/*         LTSLibMain is called by Windows when the dectalk DLL is    */
/*    initialized, Thread Attached, and other times. Since no DLL     */
/*    initialization is required, LTSLibMain return a value of 1      */
/*    indicating success.                                             */
/*                                                                    */
/**********************************************************************/
/**********************************************************************/

int LTSLibMain( DT_HANDLE hInst,
			  DWORD ul_reason_being_called,
			  LPVOID lpReserved )
{
	return(TRUE);
}
#endif


#if defined _UNIX_LIKE_
#ifdef ENGLISH_US
#define LINUX_DICT_TAG "US_dict:"
#define LINUX_FDICT_TAG "US_fdict:"
#define LINUX_UDICT_TAG "US_udict:"
#if defined VXWORKS || defined _SPARC_SOLARIS_
#define DEF_LINUX_MAIN_DICT "dtalk_us.dic"
#define DEF_LINUX_FOREIGN_DICT "dtalk_fl_us.dic"
#else
#define DEF_LINUX_MAIN_DICT "/usr/lib/dtk/dtalk_us.dic"
#define DEF_LINUX_FOREIGN_DICT "/usr/lib/dtk/dtalk_fl_us.dic"
#endif
#define DEMO_DICT_NAME "dtalk_us.dic"
#define DEMO_FDICT_NAME "dtalk_fl_us.dic"
#endif
#ifdef ENGLISH_UK
#define LINUX_DICT_TAG "UK_dict:"
#define LINUX_FDICT_TAG "UK_fdict:"
#define LINUX_UDICT_TAG "UK_udict:"
#define DEF_LINUX_MAIN_DICT "/usr/lib/dtk/dtalk_uk.dic"
#define DEF_LINUX_FOREIGN_DICT "/usr/lib/dtk/dtalk_fl_uk.dic"
#define DEMO_DICT_NAME "dtalk_uk.dic"
#define DEMO_FDICT_NAME "dtalk_fl_uk.dic"
#endif
#ifdef GERMAN
#define LINUX_DICT_TAG "GR_dict:"
#define LINUX_FDICT_TAG "GR_fdict:"
#define LINUX_UDICT_TAG "GR_udict:"
#define DEF_LINUX_MAIN_DICT "/usr/lib/dtk/dtalk_gr.dic"
#define DEF_LINUX_FOREIGN_DICT "/usr/lib/dtk/dtalk_fl_gr.dic"
#define DEMO_DICT_NAME "dtalk_gr.dic"
#define DEMO_FDICT_NAME "dtalk_fl_gr.dic"
#endif
#ifdef SPANISH_SP
#define LINUX_DICT_TAG "SP_dict:"
#define LINUX_FDICT_TAG "SP_fdict:"
#define LINUX_UDICT_TAG "SP_udict:"
#define DEF_LINUX_MAIN_DICT "/usr/lib/dtk/dtalk_sp.dic"
#define DEF_LINUX_FOREIGN_DICT "/usr/lib/dtk/dtalk_fl_sp.dic"
#define DEMO_DICT_NAME "dtalk_sp.dic"
#define DEMO_FDICT_NAME "dtalk_fl_sp.dic"
#endif
#ifdef SPANISH_LA
#define LINUX_DICT_TAG "LA_dict:"
#define LINUX_FDICT_TAG "LA_fdict:"
#define LINUX_UDICT_TAG "LA_udict:"
#define DEF_LINUX_MAIN_DICT "/usr/lib/dtk/dtalk_la.dic"
#define DEF_LINUX_FOREIGN_DICT "/usr/lib/dtk/dtalk_fl_la.dic"
#define DEMO_DICT_NAME "dtalk_la.dic"
#define DEMO_FDICT_NAME "dtalk_fl_la.dic"
#endif
#ifdef ITALIAN
#define LINUX_DICT_TAG "IT_dict:"
#define LINUX_FDICT_TAG "IT_fdict:"
#define LINUX_UDICT_TAG "IT_udict:"
#define DEF_LINUX_MAIN_DICT "/usr/lib/dtk/dtalk_it.dic"
#define DEF_LINUX_FOREIGN_DICT "/usr/lib/dtk/dtalk_fl_it.dic"
#define DEMO_DICT_NAME "dtalk_it.dic"
#define DEMO_FDICT_NAME "dtalk_fl_it.dic"
#endif
#ifdef JAPANESE
#define LINUX_DICT_TAG "JP_dict:"
#define LINUX_FDICT_TAG "JP_fdict:"
#define LINUX_UDICT_TAG "JP_udict:"
#define DEF_LINUX_MAIN_DICT "/usr/lib/dtk/dtalk_jp.dic"
#define DEF_LINUX_FOREIGN_DICT "/usr/lib/dtk/dtalk_fl_jp.dic"
#define DEMO_DICT_NAME "dtalk_jp.dic"
#define DEMO_FDICT_NAME "dtalk_fl_jp.dic"
#endif
#ifdef HEBREW
#define LINUX_DICT_TAG "HB_dict:"
#define LINUX_FDICT_TAG "HB_fdict:"
#define LINUX_UDICT_TAG "HB_udict:"
#define DEF_LINUX_MAIN_DICT "/usr/lib/dtk/dtalk_hb.dic"
#define DEF_LINUX_FOREIGN_DICT "/usr/lib/dtk/dtalk_fl_hb.dic"
#define DEMO_DICT_NAME "dtalk_hb.dic"
#define DEMO_FDICT_NAME "dtalk_fl_hb.dic"
#endif
#ifdef CHINESE
#define LINUX_DICT_TAG "CH_dict:"
#define LINUX_FDICT_TAG "CH_fdict:"
#define LINUX_UDICT_TAG "CH_udict:"
#define DEF_LINUX_MAIN_DICT "/usr/lib/dtk/dtalk_ch.dic"
#define DEF_LINUX_FOREIGN_DICT "/usr/lib/dtk/dtalk_fl_ch.dic"
#define DEMO_DICT_NAME "dtalk_ch.dic"
#define DEMO_FDICT_NAME "dtalk_fl_ch.dic"
#endif
#ifdef KOREAN
#define LINUX_DICT_TAG "KR_dict:"
#define LINUX_FDICT_TAG "KR_fdict:"
#define LINUX_UDICT_TAG "KR_udict:"
#define DEF_LINUX_MAIN_DICT "/usr/lib/dtk/dtalk_kr.dic"
#define DEF_LINUX_FOREIGN_DICT "/usr/lib/dtk/dtalk_fl_kr.dic"
#define DEMO_DICT_NAME "dtalk_kr.dic"
#define DEMO_FDICT_NAME "dtalk_fl_kr.dic"
#endif

#ifdef FRENCH
#define LINUX_DICT_TAG "FR_dict:"
#define LINUX_FDICT_TAG "FR_fdict:"
#define LINUX_UDICT_TAG "FR_udict:"
#define DEF_LINUX_MAIN_DICT "/usr/lib/dtk/dtalk_fr.dic"
#define DEF_LINUX_FOREIGN_DICT "/usr/lib/dtk/dtalk_fl_fr.dic"
#define DEMO_DICT_NAME "dtalk_fr.dic"
#define DEMO_FDICT_NAME "dtalk_fl_fr.dic"
#endif

	
int linux_get_dict_names(char *main_dict_name,char *user_dict_name, char *foreign_dict_name)
{
	FILE *config_file;
	char line[1000];
	char *home_dir;
	char temp_dict_name[1000];
	int ret_value=0;
	
	main_dict_name[0]='\0';
	foreign_dict_name[0]='\0';
	user_dict_name[0]='\0';
	config_file=FNX_FOPEN("/etc/DECtalk.conf","r");
#ifdef TESTING
	if (config_file==NULL)
	{
		config_file=FNX_FOPEN("DECtalk.conf","r");
	}
#endif
	
#ifdef DEMO
        FNX_STRCPY(main_dict_name,DEMO_DICT_NAME);
        FNX_STRCPY(foreign_dict_name,DEMO_FDICT_NAME);
        ret_value++;
#else
	if (config_file!=NULL)
	{
		while(FNX_FGETS(line,999,config_file)!=NULL)
		{
			if (FNX_STRNCMP(line,LINUX_DICT_TAG,8)==0)
			{
				line[FNX_STRLEN(line)-1]='\0';
				FNX_STRCPY(main_dict_name,line+8);
				break;
			}
		}
	}
	if (main_dict_name[0]=='\0')
	{
		FNX_FPRINTF(stderr,"libtts.so: Using default dictionary name\n");
		FNX_STRCPY(main_dict_name,DEF_LINUX_MAIN_DICT);
	}
	else
	{
		ret_value++;
	}
	if (config_file!=NULL)
	{
		FNX_FSEEK(config_file,0,SEEK_SET);
		while(FNX_FGETS(line,999,config_file)!=NULL)
		{
			if (FNX_STRNCMP(line,LINUX_FDICT_TAG,9)==0)
			{
				line[FNX_STRLEN(line)-1]='\0';
				FNX_STRCPY(foreign_dict_name,line+8);
				break;
			}
		}
	}
	if (foreign_dict_name[0]=='\0')
	{
		FNX_STRCPY(foreign_dict_name,DEF_LINUX_FOREIGN_DICT);
	}
	else
	{
		ret_value++;
	}
#endif
	home_dir=getenv("HOME");
	if (home_dir!=NULL)
	{
		temp_dict_name[0]='\0';
		if (config_file!=NULL)
		{
			FNX_FSEEK(config_file,0,SEEK_SET);
			while(FNX_FGETS(line,999,config_file)!=NULL)
			{
				if (FNX_STRNCMP(line,LINUX_UDICT_TAG,9)==0)
				{
					line[FNX_STRLEN(line)-1]='\0';
					FNX_STRCPY(temp_dict_name,line+9);
					break;
				}
			}
		}
		if (temp_dict_name[0])
		{
        		FNX_SPRINTF(user_dict_name, "%s/%s", home_dir,temp_dict_name);
			ret_value++;
		}	
		else
		{
        		FNX_SPRINTF(user_dict_name, "%s/udic.dic", home_dir);
		}
			
	}
	if (config_file!=NULL)
	{
		FNX_FCLOSE(config_file);
	}
	return(ret_value);
}
#endif
#ifdef MULTIPLE_LANGUAGES_LOADED
int lts_language_loaded( void )
{
	return 0;
}
#endif
#if defined(__cplusplus)
}
#endif
