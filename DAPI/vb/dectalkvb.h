#ifndef DECTALKVB
#define DECTALKVB

#if defined(__cplusplus)
extern "C" {
#endif

#define DLLEXPORT __declspec(dllexport)

DLLEXPORT int __stdcall TextToSpeechStartupExVB(UINT *, UINT, DWORD, LONG, LONG );

DLLEXPORT int __stdcall TextToSpeechStartupVB(HWND, UINT *, UINT, DWORD );
DLLEXPORT int __stdcall TextToSpeechSpeakVB(UINT , LPSTR, DWORD );
DLLEXPORT int __stdcall TextToSpeechSyncVB( UINT  );
DLLEXPORT int __stdcall TextToSpeechShutdownVB( UINT  );

DLLEXPORT int __stdcall TextToSpeechSetRateVB( UINT, UINT );
DLLEXPORT int __stdcall TextToSpeechGetRateVB( UINT, LPDWORD );
DLLEXPORT void __stdcall TextToSpeechTypingVB(UINT, CHAR*);
DLLEXPORT int __stdcall TextToSpeechResetVB(UINT, BOOL);
DLLEXPORT int __stdcall TextToSpeechSetSpeakerVB( UINT, UINT );
DLLEXPORT int __stdcall TextToSpeechGetSpeakerVB( UINT, UINT* );

DLLEXPORT int __stdcall TextToSpeechLoadUserDictionaryVB( UINT , LPSTR  );
DLLEXPORT int __stdcall TextToSpeechUnloadUserDictionaryVB( UINT );
DLLEXPORT int __stdcall TextToSpeechOpenWaveOutFileVB( UINT , LPSTR, UINT );
DLLEXPORT int __stdcall TextToSpeechCloseWaveOutFileVB( UINT );
DLLEXPORT int __stdcall TextToSpeechRegisterCallbacksVB(UINT , INT, UINT*);
DLLEXPORT int __stdcall TextToSpeechGetStatusVB( UINT, UINT *, UINT*, UINT );


#if defined(__cplusplus)
}
#endif


#endif