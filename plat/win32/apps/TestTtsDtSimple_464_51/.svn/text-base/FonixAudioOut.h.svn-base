// fonixaudioout.h

#ifndef __fonixaudioout_h
#define __fonixaudioout_h

#include "FonixPublic.h"

#define FNX_AUDIO_OUT_SOURCE_NONE       0
#define FNX_AUDIO_OUT_SOURCE_MIC        1
#define FNX_AUDIO_OUT_SOURCE_TTS        2
#define FNX_AUDIO_OUT_SOURCE_FILE       3
#define FNX_AUDIO_OUT_SOURCE_RAW        4

#define FNX_AUDIO_OUT_FORMAT_PCM		1
#define FNX_AUDIO_OUT_FORMAT_ALAW		6
#define FNX_AUDIO_OUT_FORMAT_MULAW		7

typedef int FNX_AUDIO_OUT_FORMAT_FLAG;
typedef int FNX_AUDIO_OUT_SOURCE_FLAG;

typedef void * FnxAudioOut;
typedef void * FnxWavePtr;

typedef void (*FnxAudioOutCreateProc)( void * pUserData );
typedef void (*FnxAudioOutInitProc)( int * samplesEachPlay, int sampleRate, FNX_AUDIO_OUT_SOURCE_FLAG source, int bytesPerSample, FNX_AUDIO_OUT_FORMAT_FLAG format, void * pUserData );
typedef void (*FnxAudioOutPlayProc)( short * pData, int samples, void * pUserData );
typedef void (*FnxAudioOutQuitProc)( void * pUserData );
typedef void (*FnxAudioOutDestroyProc)( void * pUserData);

typedef struct
{
    FnxAudioOutCreateProc  pAudioOutCreate;
    FnxAudioOutInitProc    pAudioOutInit;
	FnxAudioOutPlayProc    pAudioOutPlay;
    FnxAudioOutQuitProc    pAudioOutQuit;
    FnxAudioOutDestroyProc pAudioOutDestroy;
} FnxAudioOutDriver;

#if defined(__cplusplus)
extern "C" {
#endif

/* FnxAudioOut creation/destruction */
FnxExport( FnxAudioOut, FnxAudioOutCreate() );
FnxExport( int,     FnxAudioOutGetApiVersion() );
FnxExport( void,    FnxAudioOutDestroy( FnxAudioOut ) );

/* Audio drivers */
FnxExport( void,    FnxAudioOutSetDrivers( FnxAudioOut, FnxAudioOutDriver * ) );
FnxExport( void,    FnxAudioOutGetDrivers( FnxAudioOut, FnxAudioOutDriver ** ) );

/* Runtime */
FnxExport( void,    FnxAudioOutOpenStreaming( FnxAudioOut, int * samplesEachPlay, int sampleRate, int bytesPerSample, FNX_AUDIO_OUT_FORMAT_FLAG format ) );
FnxExport( void,    FnxAudioOutPlayStreaming( FnxAudioOut, short * pRawData, int rawSamples ) );
FnxExport( void,    FnxAudioOutCloseStreaming( FnxAudioOut ) );
FnxExport( void,    FnxAudioOutPlayRawData( FnxAudioOut, short * pRawData, int rawSamples, int rawSampleRate ) );
FnxExport( void,    FnxAudioOutPlayWave( FnxAudioOut, char * szWaveName ) );
FnxExport( void,	 FnxAudioOutPlayWaveData( FnxAudioOut, FnxWavePtr pWave ) );

#ifdef WIDE_CHARACTER
FnxExport( void, FnxAudioOutPlayWaveW( FnxAudioOut audioOut, const wchar_t * wszWaveName ));   
#endif // WIDE_CHARACTER

#ifdef OS_SYMBIAN

typedef void (*FnxAudioOutCallbackProc)( short* pData, int samples, void * pUserData );
FnxExport( void,  FnxAudioOutInitCallback( void (*callback)( short*, int, void *),void* pUserData ) );

#endif

#if defined(__cplusplus)
}
#endif

#endif 
