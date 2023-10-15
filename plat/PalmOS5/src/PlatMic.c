#include "FnxPlatform.h"
#include <PalmOS.h>
#include <SysGlue.h>
#include <SoundMgr.h>
#include <ErrorBase.h>

#include "DTFnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxWave.h"

//This is for ccb31
#include "concurrent.h"

#define NO_ERROR 0
//#define AUDIOINBUFSIZE 33075
#define AUDIOINBUFSIZE 4096
#define LENGTHTORECORD	1
#define BUFSTOREC 17

int blockSize=0;
//int platmaxrecord = 5;

//input stream
SndStreamRef streamrefin;

typedef enum { READY,       		 
               COPIED,             
               WAITING
}audioinstates;

typedef struct tagaudioinData
{
	short			data[AUDIOINBUFSIZE];
	audioinstates   stateflag;
	
}audioinData;

typedef struct tagcallbackDatastruct
{
	audioinData** thedataptr;
	int index;
	
}callbackDatastruct;

int smplratein;
BOOL hassampledsound;
audioinData** thedata;
callbackDatastruct callbackdata;	
int numbuffs;
int index;

Boolean PalmSGHasSampledSoundIn()
{
         UInt32 version = 0;
         UInt32 checkPalm = 0;
         UInt32 checkTT = 0;
         Boolean hasSampledSound = false;

         // Check if the sound feature is set
         if( FtrGet( sysFileCSoundMgr, sndFtrIDVersion, &version ) == errNone )
         {
                 hasSampledSound = true;
         }

         // Check for Tungsten|T
         FtrGet(sysFtrCreator, sysFtrNumOEMCompanyID, &checkPalm);
         FtrGet(sysFtrCreator, sysFtrNumOEMDeviceID, &checkTT);
         if( checkPalm == 'Palm' && checkTT == 'Frg1' ) {
                 hasSampledSound = true;
         }

         return hasSampledSound;
}
	
void AudioInCreate()
{
	if (PalmSGHasSampledSoundIn())
		hassampledsound = TRUE;
	else
	{
		hassampledsound = FALSE;
		fnxaprintf("Does not have sampled sound");
	}

	streamrefin = NULL;	
}

static Err SndStreamInBufferCallback(void *userDataP, SndStreamRef streamin, void *bufferP, UInt32 *bufferSizeP)
{
	Err 	err = errNone;
	callbackDatastruct* cbdata = (callbackDatastruct*)userDataP;
	short* tempsrc = (short*)bufferP;
	int bytesAvail = *bufferSizeP;

	int i = cbdata->index;
	
	if (cbdata->thedataptr[i]->stateflag == READY)
	{
		MemMove(cbdata->thedataptr[i]->data,tempsrc,bytesAvail);
		cbdata->thedataptr[i]->stateflag = COPIED;
		cbdata->index++;
		if (cbdata->index == BUFSTOREC)
			cbdata->index = 0;
	}
	return errNone;
}


int AudioInInit( int sampleRate )
{
	int err,i;
	int bufsize = AUDIOINBUFSIZE;
	SndCommandType		sndCmd;

	
	smplratein = sampleRate;

//	numbuffs = (int)((platmaxrecord*smplratein*sizeof(short))/AUDIOINBUFSIZE);
//	numbuffs++;
	index = 0;
	
	thedata = (audioinData**)FNX_MALLOC(BUFSTOREC * sizeof(audioinData*));
	
	for (i = 0; i < BUFSTOREC; i++)
	{
		thedata[i] = (audioinData*)FNX_MALLOC(BUFSTOREC * sizeof(audioinData));
		thedata[i]->data[0] = NULL;
		thedata[i]->stateflag = READY;
		memset(thedata[i]->data,0,bufsize);
	}
	callbackdata.thedataptr = thedata;
	callbackdata.index = 0;
	
	if (hassampledsound && !streamrefin)
	{
		err = SndStreamCreateExtended(&streamrefin,sndInput,sndFormatPCM,smplratein,sndInt16Little,sndMono,SndStreamInBufferCallback,&callbackdata,bufsize,false);
		if(err == sndErrBadParam)
		{
			fnxaprintf("sndErrBadParam");
		}
		else if (err == sndErrMemory)
		{
			fnxaprintf("sndErrorMemory");
		}
		else if (err != errNone)
		{
			fnxaprintf("other create error");
		}

//	//play a beep
//	sndCmd.cmd = sndCmdFreqDurationAmp;
//	sndCmd.param1 = 440;
//	sndCmd.param2 = 300;
//	sndCmd.param3 = 20;
//	SndDoCmd ( 0, &sndCmd, false );

	}

	return 0;
}


short * AudioInRecord( int * pSamples )
{
	int err = errNone;
	int result = 0;
	
	uword8 tmp;
	uword8* tempdata = NULL;
	uword32 i;
	int ByteCount;
	int numbytes = AUDIOINBUFSIZE;


	*pSamples = 0;
	
	if (thedata[index]->stateflag == WAITING)
	{
		thedata[index]->stateflag = READY;
		index++;
		if (index == BUFSTOREC)
			index = 0;
	}
	
	if (streamrefin)
	{
		result = SndStreamStart(streamrefin);
		if (result == errNone)
		{
			while ((index < BUFSTOREC) && (thedata[index]->stateflag != COPIED))
			{
				SysTaskDelay(200);
			}
			if ((index < BUFSTOREC) && (thedata[index]->stateflag == COPIED))
			{
				*pSamples = AUDIOINBUFSIZE/2;
				//Byte Swap
				ByteCount = *pSamples*2;
				tempdata = (uword8*)thedata[index]->data;
				for (i = 0; i < ByteCount; i += 2)
				{
					tmp = tempdata[i];
					tempdata[i] = tempdata[i + 1];
					tempdata[i + 1] = tmp;
				}
				SpeechWrite("tempaft.wav",-1,-1,thedata[index]->data,*pSamples,smplratein,SPEECH_RIFFPCM,NULL,FALSE);
				tempdata = (uword8*)thedata[index]->data;
				thedata[index]->stateflag = WAITING;
			}
		}
		else
			fnxaprintf("error in starting stream");
	}
	return (short *)tempdata;
}

int AudioInQuit()
{
	SndCommandType		sndCmd;
	int i;
	
//	sndCmd.cmd = sndCmdFreqDurationAmp;
//	sndCmd.param1 = 440;
//	sndCmd.param2 = 200;
//	sndCmd.param3 = 20;

	SndStreamStop(streamrefin);
//	SndDoCmd ( 0, &sndCmd, true );
	
	for (i = 0; i < BUFSTOREC; i++)
	{
		FNX_FREE(thedata[i]);
	}
	
	FNX_FREE(thedata);
	SndStreamDelete(streamrefin);
	streamrefin = NULL;
	return 0;
}

void AudioInDestroy()
{
	if (streamrefin)
	{
		SndStreamDelete(streamrefin);
	}
	
}

// One-time initialization
SDWORD platMicInit(MicInfoPtr pMicInfo)
{
//	platmaxrecord = pMicInfo->maxRecord;
	ConcurrentInit(pMicInfo->pRecogProc);
	return 0;
}

// One-time destruction
SDWORD platMicQuit(MicInfoPtr pMicInfo)
{
	ConcurrentFree();
	return 0;
}

SDWORD platMicStop(MicInfoPtr pMicInfo)
{
	return 0;
}

BOOL platIsMicRecording(void)
{
	return FALSE;
}

SDWORD platMicOn(SDWORD iDevId)
{
	return 0;
}

SDWORD platMicOff(void)
{
	return 0;
}

SDWORD platMicGetDeviceId(char *sDeviceName)
{
	return 0;
}

SDWORD platMicSetVolume ( SDWORD volume )
{
	return 0;
}

SDWORD platMicGetPrefInputDeviceName( char *szName, int size, int *usePrefOnly )
{
	return 0;
}

SDWORD platMicSampleRate(SDWORD sampleRate)
{
	return 0;
}