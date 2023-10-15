/*C_HEADER_FILE****************************************************************
FILE			:	PlatSpeaker.c
DESC			:	wave playing functions for PALM OS 5
TABS			:	3
OWNER			:	fonix
DATE CREATED:	

(C) Copyright 2003 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER*******************************************************************/
#include "FnxPlatform.h"
#include "DTFnxStdlib.h"
#include "FnxAllocate.h"
//#include "EmbCommon.h"
#include <PalmOS.h>
//#include "PalmSoundMgrExt.h"
#include <SysGlue.h>
#include <SoundMgr.h>
#include <ErrorBase.h>
#include <StringMgr.h>

#define AUDIOOUTBUFSIZE 11025
//#define AUDIOOUTBUFSIZE 4096

//output stream
SndStreamRef streamrefout;

int smplrateout;
int newsamplerateout;

typedef struct tagSpkLList
{
	short * pData;
	struct tagSpkLList * pNext;
	volatile int	UsedFlag;
	int datasize;
	int samplesused;
} SpkLList;

typedef struct tagspkstruct
{
	SpkLList ** LLHead;
	volatile BOOL spkrrunning;
	int nodatacount;
}spkstruct;

spkstruct  gSpkstruct;

SpkLList * gSpkLLHead = NULL;
SpkLList * gSpkLLTail = NULL;

SpkLList * NewSpkLListMember( short * pData, int datSize );

/**************************************************************************************
//	SpkLList * NewSpkLListMember( short * pData )
//  audio output link list management 
//		add new member to link list
//**************************************************************************************/
SpkLList * NewSpkLListMember( short * pData, int datSize )
{
	SpkLList * llist = (SpkLList *)FNX_MALLOC( sizeof( SpkLList ) );
	llist->pData = pData;
	llist->pNext = NULL;
	llist->UsedFlag = 0;
	llist->datasize = datSize;
	llist->samplesused = 0;
	return llist;
}


static Err SndStreamOutBufferCallback(void *userDataP, SndStreamRef stream, void *bufferP, UInt32 *bufferSizeP)
{

	Err 	err 			= errNone;
	spkstruct *temp = (spkstruct*)userDataP;
	SpkLList * SpkLListTemp = *(temp->LLHead);
	int i;
	char * tempdst = (char *)bufferP;
	char * tempsrc;
	

	//find the item in the linked list that contains the Buffer that just finished
	while( SpkLListTemp && SpkLListTemp->UsedFlag == 1 )
	{
		SpkLListTemp = SpkLListTemp->pNext;
	}
	
	//mark Buffer as used in the link list
	if( SpkLListTemp )
	{
		tempsrc = (char *)SpkLListTemp->pData + SpkLListTemp->samplesused;
		// if buffer is big enough or less than 1 audio buffer left in the data buffer received
		if (*bufferSizeP >= SpkLListTemp->datasize - SpkLListTemp->samplesused)
		{
			for(i = 0; i < SpkLListTemp->datasize - SpkLListTemp->samplesused ; i+=2)
			{
				tempdst[i] = tempsrc[i+1];
				tempdst[i+1] = tempsrc[i];
			}
			*bufferSizeP = 	SpkLListTemp->datasize - SpkLListTemp->samplesused;
			SpkLListTemp->samplesused = SpkLListTemp->datasize;
			SpkLListTemp->UsedFlag = 1;
		}
		else
		{
			for(i = 0; i < *bufferSizeP; i+=2)
			{
				tempdst[i] = tempsrc[i+1];
				tempdst[i+1] = tempsrc[i];
			}
			SpkLListTemp->samplesused += *bufferSizeP;
		}

	}
	else
	{
		*bufferSizeP = 0;
		if (temp->nodatacount == 0)
		{
			for(i = 0; i < *bufferSizeP; i++)
			{
				tempdst[i] = 0;
			}	
		}
		else
		{
//			SndStreamStop(stream);
			temp->spkrrunning = 0;
		}
		(temp->nodatacount)++;
		
	}	

	return err;
}


void AudioOutCreate()
{
	return;
}

Boolean PalmSGHasSampledSound()
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

void AudioOutInit( int * samplesEachPlay, int sampleRate, int source, int bytesPerSample, int format )
{
	Err err = errNone;
	gSpkLLHead = gSpkLLTail = NULL;

	gSpkstruct.LLHead =  &gSpkLLHead;
	streamrefout = NULL;
	gSpkstruct.spkrrunning = 0;
	gSpkstruct.nodatacount = 0;
	smplrateout = sampleRate;	
		
	*samplesEachPlay = AUDIOOUTBUFSIZE;
}


int AudioOutPlay( short * pData, int samples )
{
	short	*pBuffer;
	SpkLList * SpkLListNext = NULL;
	int IntStatus,result,err;

	//clean up segment that have already been played
	while( gSpkLLHead && gSpkLLHead->pData && gSpkLLHead->UsedFlag )
	{
		FNX_FREE( gSpkLLHead->pData );
		SpkLListNext = gSpkLLHead->pNext;
		FNX_FREE( gSpkLLHead );
		gSpkLLHead = SpkLListNext;
	}
	pBuffer = (short *)FNX_MALLOC( samples*sizeof(short) );
	if (pBuffer)
	{
		if( !gSpkLLHead )
		{
			gSpkLLHead = gSpkLLTail = NewSpkLListMember( pBuffer,samples*2 );
			
		}
		else
		{
			gSpkLLTail->pNext = NewSpkLListMember( pBuffer, samples*2 );
			gSpkLLTail = gSpkLLTail->pNext;
		}
		
		MemMove(pBuffer,pData,samples*2);	

		if (!streamrefout)
		{
			if (PalmSGHasSampledSound())
			{
				err = SndStreamCreateExtended(&streamrefout,sndOutput,sndFormatPCM,smplrateout,sndInt16Little,sndMono,SndStreamOutBufferCallback,&gSpkstruct,AUDIOOUTBUFSIZE,false);
			}
			else
				fnxaprintf("Does not have sampled sound");
		}
		if (!gSpkstruct.spkrrunning && streamrefout)
		{
			result = SndStreamStart(streamrefout);
			gSpkstruct.spkrrunning = 1;		
		}
			
	}

	return 0;
}

void AudioOutQuit()
{
	SpkLList * llist = NULL;
	int i;
	
	if (streamrefout)
	{
		while (gSpkstruct.spkrrunning)
		{
		}
		SndStreamStop(streamrefout);
		gSpkstruct.spkrrunning = 0;	
		SndStreamDelete(streamrefout);
	}
	while (gSpkLLHead)
	{
		while (gSpkLLHead->UsedFlag == 0)
		{
		}	
		llist = gSpkLLHead;
		gSpkLLHead = gSpkLLHead->pNext;
		FNX_FREE(llist->pData);
		FNX_FREE(llist);
	}
	gSpkLLHead = gSpkLLTail = NULL;

}

void AudioOutDestroy()
{
	return;
}