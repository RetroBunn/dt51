#ifndef SETLTSLANGUAGE_H
#define SETLTSLANGUAGE_H
#include "ttsapi.h"

#ifdef ARM7
extern int TextToSpeechSetLTSLanguage( LPTTS_HANDLE_T phTTS, int Language );
#else
extern MMRESULT TextToSpeechSetLTSLanguage( LPTTS_HANDLE_T phTTS, LANGUAGE_T Language );
#endif

#endif /* SETLTSLANGUAGE_H */
