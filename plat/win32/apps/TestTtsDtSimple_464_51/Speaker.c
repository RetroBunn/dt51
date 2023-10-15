#include <windows.h>

#define WAVOUT_BUFCNT	15
#define SAVE_DATA_SAMPLES	5000	// number of samples to cue before playing

static WAVEFORMATEX	gWaveFormat;
static WAVEHDR		gpWaveHdrArray[ WAVOUT_BUFCNT ];	// Array of headers
static HWAVEOUT		ghWaveOut = NULL;					// Handle to the wave input device, we get this in MicPrepare
static int			giCurBuf = 0;						// Current index into gpWavehdrArray
static int			giPlaying = 0;

void AudioOutCreate()
{}

void AudioOutInit( int * samplesEachPlay, int sampleRate, int bytesPerSample, int encodingFormat)
{
	int i = 0;
	giCurBuf = 0;
	giPlaying = 0;
	gWaveFormat.wFormatTag		= encodingFormat;
	gWaveFormat.nChannels		= 1; 
	gWaveFormat.nSamplesPerSec	= sampleRate; 
	gWaveFormat.nBlockAlign		= (unsigned short)(bytesPerSample * gWaveFormat.nChannels); 
	gWaveFormat.nAvgBytesPerSec	= gWaveFormat.nBlockAlign * sampleRate; 
	gWaveFormat.wBitsPerSample	= bytesPerSample * 8;
	gWaveFormat.cbSize			= 0;

	if( waveOutOpen( &ghWaveOut, WAVE_MAPPER, &gWaveFormat, 0, 0, CALLBACK_NULL ) == MMSYSERR_NOERROR )
	{
		memset( gpWaveHdrArray, 0, sizeof( gpWaveHdrArray ) );
		for( i = 0; i < WAVOUT_BUFCNT; i++ )
		{
			gpWaveHdrArray[ i ].dwFlags = WHDR_DONE;
		}
	}
}

void AudioOutPlay( short * pData, int samples)
{
	LPWAVEHDR pWavHdr;
	int outOfMemoryCount = 0;
	if( !pData || !samples || !ghWaveOut )
		return;
	
	giPlaying = 1;

   while( !(gpWaveHdrArray[ giCurBuf ].dwFlags & WHDR_DONE) )
	{
		Sleep( 100 );
	}

	pWavHdr = &gpWaveHdrArray[ giCurBuf ];
	
	giCurBuf++;
	if( giCurBuf >= WAVOUT_BUFCNT )	//  gpWaveHdrArray is a circular buffer
		giCurBuf = 0;
	
	if( pWavHdr->dwFlags & WHDR_PREPARED )
	{
		waveOutUnprepareHeader( ghWaveOut, pWavHdr, sizeof( WAVEHDR ) );
	}

	if( pWavHdr->lpData )
	{
		free( pWavHdr->lpData );
		pWavHdr->lpData = NULL;
	}

	pWavHdr->dwBufferLength = samples * gWaveFormat.wBitsPerSample / 8;
 	pWavHdr->lpData = malloc( pWavHdr->dwBufferLength );
	
	while( outOfMemoryCount < 20 && !pWavHdr->lpData  )
	{
		outOfMemoryCount++;
		Sleep( 100 );
		pWavHdr->lpData = malloc( pWavHdr->dwBufferLength );
	}
	if( pWavHdr->lpData )
	{
		memset( pWavHdr->lpData, 0, pWavHdr->dwBufferLength);
		memcpy( pWavHdr->lpData, pData, pWavHdr->dwBufferLength );
	
		waveOutPrepareHeader( ghWaveOut, pWavHdr, sizeof( WAVEHDR ) );
		waveOutWrite( ghWaveOut, pWavHdr, sizeof( WAVEHDR ) );
	}	

	giPlaying = 0;
}

void AudioOutQuit()
{
	int ix;
	int buffIndex = 0;

	if( !ghWaveOut )
		return;

	while( giPlaying )
	{
		Sleep( 100 );
	}

	buffIndex = giCurBuf;
	if( buffIndex >= WAVOUT_BUFCNT )
	   buffIndex = 0;

	for( ix = 0; ix < WAVOUT_BUFCNT; ix++ )
	{
		while( !(gpWaveHdrArray[ buffIndex ].dwFlags & WHDR_DONE) ) 
		{
			Sleep( 100 );
		}

		if( gpWaveHdrArray[ buffIndex ].dwFlags & WHDR_PREPARED )
		{
			waveOutUnprepareHeader( ghWaveOut, &gpWaveHdrArray[ buffIndex ], sizeof( WAVEHDR ) );
		}

		if( gpWaveHdrArray[ buffIndex ].lpData )
		{
			free( gpWaveHdrArray[ buffIndex ].lpData );
			gpWaveHdrArray[ buffIndex ].lpData = NULL;
		}

	   buffIndex++;
	   if( buffIndex >= WAVOUT_BUFCNT )
		   buffIndex = 0;
	}

	waveOutClose( ghWaveOut );
	ghWaveOut = NULL;
}

void AudioOutDestroy()
{}
