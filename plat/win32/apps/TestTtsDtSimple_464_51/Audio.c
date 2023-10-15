#include "FonixTtsDtSimple.h"
#include "FonixAudioOut.h"
#include "Audio.h"
#include <memory.h>

FnxAudioOut AudioOutPtr;

#define BUFFERSIZE 71
#define BUFFERS_AHEAD 100
#define STOP_CLICK_BUFFER_LEN BUFFERSIZE*BUFFERS_AHEAD
short StopClickBuffer[STOP_CLICK_BUFFER_LEN];
int BuffersAhead = 0;

void __cdecl AudioOutOpen( void )
{
	int samplesEachPlay;
	
	AudioOutPtr = FnxAudioOutCreate();
	FnxAudioOutOpenStreaming(AudioOutPtr, &samplesEachPlay, 11025, 2, FNX_AUDIO_OUT_FORMAT_PCM );
	BuffersAhead = 0;
}

short * __cdecl AudioOutPlayBuffer(short * data, long flag)
{
	switch (flag)
	{
		case 0:
			if( BuffersAhead < BUFFERS_AHEAD )
			{
				memcpy( &StopClickBuffer[BuffersAhead*BUFFERSIZE], data, BUFFERSIZE*sizeof( short ) );
				BuffersAhead++;
			}
			else
			{
//				if( BuffersAhead == BUFFERS_AHEAD )
//				{
					FnxAudioOutPlayStreaming(AudioOutPtr, StopClickBuffer, BUFFERSIZE*BUFFERS_AHEAD);
//					BuffersAhead++;
					BuffersAhead = 0;
//			}
//				FnxAudioOutPlayStreaming(AudioOutPtr, data, BUFFERSIZE);

			}

			return( data );
			break;
		case 3:
			return( data );
			break;
		default:
			return (NULL);
			break;
	}
}

void AudioOutPlay(short *data, int samples)
{
	FnxAudioOutPlayStreaming(AudioOutPtr, data, samples);
}

void __cdecl AudioOutClose( void )
{
	FnxAudioOutCloseStreaming(AudioOutPtr);
	FnxAudioOutDestroy( AudioOutPtr );
}
