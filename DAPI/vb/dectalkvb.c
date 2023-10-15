
/************************************************************************
 *
 *                           Copyright ©
 *    Copyright © 2003 Fonix Corporation. All rights reserved.
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
 ***********************************************************************/
////////////////////////////////////////////////////////////////////////////
// dectalkvb.c: DECtalk wrapper for  Visual Basic Functionality//
////////////////////////////////////////////////////////////////////////////

//Standard Headers
//#include <stdlib.h> //moved to port.h for each platform - mlt
//#include <windows.h> //moved to port.h for each platform - mlt
//#include <stdio.h> //moved to port.h for each platform - mlt

#include "port.h" //added for platform specific code - mlt

#include "dectalkvb.h"

//DECtalk Header
#include "ttsapi.h"

#if defined(__cplusplus)
extern "C" {
#endif

void (__stdcall* callback_routine)(LONG)=NULL;

#define DLLEXPORT __declspec(dllexport)



void TTSCallback(long a, long b, long c, long d)
{
	int i;
	i=a+b+c+d;
	if (callback_routine)
	{
		(*callback_routine)((long)a);
	}
}


DLLEXPORT int __stdcall TextToSpeechRegisterCallbacksVB(UINT phTTS, int which, UINT *val)
{
	int uiID_Error_Msg,uiID_Index_Message;
	int uiID_Buffer_Message, uiID_Visual_Message;
	
	switch (which)
	{
	case 2:
#ifdef UNDER_CE
		uiID_Error_Msg = RegisterWindowMessage(_T("DECtalkErrorMessage"));
#else
		uiID_Error_Msg = RegisterWindowMessage("DECtalkErrorMessage");
#endif
		*val=uiID_Error_Msg;
		break;
		
	case 1:
#ifdef UNDER_CE
		uiID_Index_Message =RegisterWindowMessage(TEXT("DECtalkIndexMessage"));
#else
		uiID_Index_Message =RegisterWindowMessage("DECtalkIndexMessage");
#endif	/* UNDER_CE */
		*val=uiID_Index_Message;
		break;
		
	case 3:
#if UNDER_CE //mfgce
		uiID_Visual_Message =RegisterWindowMessage(TEXT("DECtalkVisualMessage"));
#else
		uiID_Visual_Message =RegisterWindowMessage("DECtalkVisualMessage");
#endif	/* UNDER_CE */
		*val=uiID_Visual_Message;
		break;
		
	case 4:
#if UNDER_CE //mfgce
		uiID_Buffer_Message =RegisterWindowMessage(TEXT("DECtalkBufferMessage"));
#else
		uiID_Buffer_Message =RegisterWindowMessage("DECtalkBufferMessage");
#endif	/* UNDER_CE */
		*val=uiID_Buffer_Message;
		break;
	}
	return *val;
}

DLLEXPORT int __stdcall TextToSpeechStartupVB(HWND hWnd, UINT *phTTS, UINT uiDeviceNumber, DWORD dwDeviceOptions )
{

	LPTTS_HANDLE_T pphTTS = NULL;       /* DECtalk TTS handle          */
	int result;
	
	result=TextToSpeechStartup(  hWnd, &pphTTS, uiDeviceNumber, dwDeviceOptions );

	*phTTS=(UINT)pphTTS;

	return result;

}


DLLEXPORT int __stdcall TextToSpeechStartupExVB(UINT *phTTS, UINT uiDeviceNumber, DWORD dwDeviceOptions, long callbackroutine, long callbackparm )
{

	LPTTS_HANDLE_T pphTTS = NULL;       /* DECtalk TTS handle          */
	int result;
	callback_routine=callbackroutine;

	result=TextToSpeechStartupEx(&pphTTS, uiDeviceNumber, dwDeviceOptions, TTSCallback,  callbackparm);

 
	*phTTS=(UINT)pphTTS;

	return result;

}



DLLEXPORT int __stdcall TextToSpeechSpeakVB( UINT phTTS, LPSTR pszTextString, DWORD dwFlags )
{

	 return(TextToSpeechSpeak( (LPTTS_HANDLE_T)phTTS, pszTextString, dwFlags ));
}


DLLEXPORT int __stdcall TextToSpeechGetStatusVB( UINT phTTS, 
								DWORD *dwIdentifierArray,
							   DWORD *dwStatusArray,
							   DWORD dwNumberOfStatusValues )
{
	return(TextToSpeechGetStatus((LPTTS_HANDLE_T)phTTS, 
								 dwIdentifierArray,
							    dwStatusArray,
							    dwNumberOfStatusValues ));
}
	

DLLEXPORT int __stdcall TextToSpeechShutdownVB( UINT phTTS )
{

	return(TextToSpeechShutdown( (LPTTS_HANDLE_T)phTTS ));

}

DLLEXPORT int __stdcall TextToSpeechSyncVB( UINT phTTS )
{

	return(TextToSpeechSync( (LPTTS_HANDLE_T)phTTS ));

}

DLLEXPORT int __stdcall TextToSpeechGetRateVB( UINT phTTS, DWORD *rate   )
{

	return(TextToSpeechGetRate( (LPTTS_HANDLE_T)phTTS, rate ));

}

DLLEXPORT int __stdcall TextToSpeechSetRateVB( UINT phTTS, UINT rate )
{

	return(TextToSpeechSetRate( (LPTTS_HANDLE_T)phTTS, rate ));

}


DLLEXPORT void __stdcall TextToSpeechTypingVB(UINT phTTS, char *key)
{

	TextToSpeechTyping((LPTTS_HANDLE_T)phTTS , *key);

}



DLLEXPORT int __stdcall TextToSpeechResetVB(UINT phTTS, BOOL val)
{

	int nval;

		if (val == 0)
			nval = FALSE;
		else
			nval = TRUE;


	return(TextToSpeechReset((LPTTS_HANDLE_T)phTTS , nval));

}


DLLEXPORT int __stdcall TextToSpeechGetSpeakerVB( UINT phTTS, UINT *speaker   )
{

	return(TextToSpeechGetSpeaker( (LPTTS_HANDLE_T)phTTS, speaker ));

}


DLLEXPORT int __stdcall TextToSpeechSetSpeakerVB( UINT phTTS, UINT speaker   )
{

	return(TextToSpeechSetSpeaker( (LPTTS_HANDLE_T)phTTS, speaker ));

}


DLLEXPORT int __stdcall TextToSpeechLoadUserDictionaryVB( UINT phTTS, LPSTR userdic   )
{

	return(TextToSpeechLoadUserDictionary( (LPTTS_HANDLE_T)phTTS, userdic ));

}


DLLEXPORT int __stdcall TextToSpeechUnloadUserDictionaryVB( UINT phTTS )
{

	return(TextToSpeechUnloadUserDictionary( (LPTTS_HANDLE_T)phTTS ));

}


DLLEXPORT int __stdcall TextToSpeechOpenWaveOutFileVB( UINT phTTS, LPSTR waveFile, UINT dwFlags )
{


	switch(dwFlags)
	{
	case 1:
	return(TextToSpeechOpenWaveOutFile( (LPTTS_HANDLE_T)phTTS, waveFile, WAVE_FORMAT_1M08 ));

	case 2:
	return(TextToSpeechOpenWaveOutFile( (LPTTS_HANDLE_T)phTTS, waveFile, WAVE_FORMAT_1M16 ));

//	case 3:
//	return(TextToSpeechOpenWaveOutFile( (LPTTS_HANDLE_T)phTTS, waveFile, WAVE_FORMAT_08M08 ));

	default:
	return MMSYSERR_INVALPARAM;
	}


}



DLLEXPORT int __stdcall TextToSpeechCloseWaveOutFileVB( UINT phTTS )
{

	return(TextToSpeechCloseWaveOutFile( (LPTTS_HANDLE_T)phTTS ));

}



#ifdef __cplusplus
}
#endif

