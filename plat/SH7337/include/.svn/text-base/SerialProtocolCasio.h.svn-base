//#include "FnxPlatform.h"
typedef signed long		int32_t;
#define xhuge
#define  SDWORD   int32_t


#define INITIALIZE_FOR_NEW_COMMAND CheckSum = ByteCount = BytesToReceive = 0

typedef struct _CommStruct	_CommStructT;
#define SIZE_COMMSTRUCTT	sizeof(_CommStructT)
typedef struct _CommStruct  xhuge *CommTPtr;
typedef void (*FnxAudioOutHaltProc)();

// only one of these allocated
struct _CommStruct
{
	SDWORD Channel;
	SDWORD CommandState;	//CommStatus
	char *TtsString;	//ReceivedString = NULL;
	SDWORD TtsStringLength;		//TotalTextBytes = 0;
	SDWORD TtsVoice;		//VoiceNumber;
	SDWORD	HaltTts;		//StopOutput = 0;

	char **RecogWords;
	int numRecogWords;	//RecognumWords;
	int maxLengthRecogWord;	//RecogmaxLength;

	SDWORD AsrReplayInputStatus;	//ReplayInputStatus = 0;
	FnxAudioOutHaltProc HaltAudioOutCallBack;
	SDWORD TtsLanguage;
};

#ifdef EPSON
	//Port 2 I/O port data register clear P23 - same pin as TM1
	#define SET_TM1_LOW	asm("xld.w	%r5,0x402D9");\	
						asm("bclr [%r5],0x3");
	//clear Serial I/F interrupt factor flag reg / bit 1
	#define CLR_RX_INT  asm("xld.w	%r5,0x40286");\
						asm("bset	[%r5],0x1")
	//clear Serial I/F interrupt factor flag reg / bit 2
	#define CLR_TX_INT  asm("xld.w	%r5,0x40286");\
						asm("bset	[%r5],0x2")
	//Disable Channel 0 transmit buffer empty interrupt
	#define TX_INT_OFF	asm("xld.w	%r5,0x40276");\
						asm("bclr	[%r5],0x2")
	//Enable Channel 0 transmit buffer empty interrupt
	#define TX_INT_ON	asm("xld.w	%r5,0x40276");\
						asm("bset	[%r5],0x2")
	//Disable Channel 0 receive buffer full interrupt
	#define RX_INT_OFF	asm("xld.w	%r5,0x40276");\
						asm("bclr	[%r5],0x1")
	//Enable Channel 0 receive buffer full interrupt
	#define RX_INT_ON	asm("xld.w	%r5,0x40276");\
						asm("bset	[%r5],0x1")
#else
	#define SET_TM1_LOW
	#define CLR_RX_INT
	#define CLR_TX_INT
	#define TX_INT_OFF
	#define TX_INT_ON
	#define RX_INT_OFF
	#define RX_INT_ON
#endif

// Serial Commands (lower 4 bits may contain additional information)
#define TTS_TEXT_TRANSFER		0x10
#define TTS_CONTROL				0x20
#define REPORT_TARGET_STATUS	0x30
#define TARGET_READY			0x40
#define AUDIO_OUT_STATUS		0x50
#define TTS_VOICE_CONTROL		0x60
#define AUDIO_IN_STATUS			0x70
#define ASR_RECOGNIZED_TX		0x80
#define ASR_WORD_TX				0x90
#define ASR_REPLAY_INPUT		0xA0
#define TTS_LANGUAGE_CONTROL	0xB0
#define CUSTOM_COMMAND			0xF0

#define TARGET_READY_SUCESS	0x41
#define TARGET_READY_FAIL	0x40
#define AUDIO_OUT_BEGIN		0x50
#define AUDIO_OUT_END		0x51
#define AUDIO_IN_BEGIN		0x70
#define AUDIO_IN_END		0x71
#define ASR_RECOG_TRANSFER	0x80
#define ASR_WORD_TRANSFER_FAIL	0x90
#define ASR_WORD_TRANSFER_SUCESS	0x91

char **CreateRecogWords( int numWords, int maxLength );
void FreeRecogWords( char **Words, int *numWords, int *maxLength );
void CopyRecogWords( );
void TransmitOneByte( int Channel, unsigned char Data );
void TransmitString( int Channel, unsigned char *pData, int StringLen );
int FnxSerialProtocolTargetPlatOpenChannel( int Channel, int CPUspeed, int BaudRate );
int FnxSerialProtocolTargetPlatCloseChannel( );


