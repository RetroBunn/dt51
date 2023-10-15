Attribute VB_Name = "vbspeak"
Option Explicit


'funnction declarations linked to the core DECtalk dll

Public Declare Function TextToSpeechStartupVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByRef x As Long, ByRef y As Long, ByVal t As Long, ByVal u As Long) As Integer
Public Declare Function TextToSpeechSpeakVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long, ByVal y As String, ByVal t As Integer) As Integer
Public Declare Function TextToSpeechShutdownVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long) As Integer
Public Declare Function TextToSpeechSyncVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long) As Integer
Public Declare Function TextToSpeechSetRateVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long, ByVal y As Integer) As Integer
Public Declare Function TextToSpeechGetRateVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long, ByRef y As Integer) As Integer
Public Declare Function TextToSpeechTypingVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long, ByVal y As String) As Integer
Public Declare Function TextToSpeechResetVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long, ByVal y As Boolean) As Integer
Public Declare Function TextToSpeechGetSpeakerVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long, ByRef y As Integer) As Integer
Public Declare Function TextToSpeechSetSpeakerVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long, ByVal y As Integer) As Integer
Public Declare Function TextToSpeechLoadUserDictionaryVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long, ByVal y As String) As Integer
Public Declare Function TextToSpeechUnloadUserDictionaryVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long) As Integer

Public Declare Function TextToSpeechOpenWaveOutFileVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long, ByVal y As String, ByVal t As Integer) As Integer
Public Declare Function TextToSpeechCloseWaveOutFileVB Lib "d:\work\rnd\dapi\build\cedllvb\arm\us\release\dectalkvb.dll" (ByVal x As Long) As Integer


'return codes

Public Const MMSYSERR_NOERROR = 0       ' no error
Public Const MMSYSERR_ERROR = 1         ' unspecified error
Public Const MMSYSERR_BADDEVICEID = 2   ' device ID out of range
Public Const MMSYSERR_NOTENABLED = 3    ' driver failed enable
Public Const MMSYSERR_ALLOCATED = 4     ' device already allocated
Public Const MMSYSERR_INVALHANDLE = 5   ' device handle is invalid
Public Const MMSYSERR_NODRIVER = 6      ' no device driver present
Public Const MMSYSERR_NOMEM = 7         ' memory allocation error
Public Const MMSYSERR_NOTSUPPORTED = 8  ' function isn't supported
Public Const MMSYSERR_BADERRNUM = 9     ' error value out of range
Public Const MMSYSERR_INVALFLAG = 10    ' invalid flag passed
Public Const MMSYSERR_INVALPARAM = 11   ' invalid parameter passed
Public Const MMSYSERR_HANDLEBUSY = 12   ' handle being used


'Speaker Definitions for functions TextToSpeechGetSpeakerVB

Public Const PAUL = 0
Public Const BETTY = 1
Public Const HARRY = 2
Public Const FRANK = 3
Public Const DENNIS = 4
Public Const KIT = 5
Public Const URSULA = 6
Public Const RITA = 7
Public Const WENDY = 8


Public Const TTS_NORMAL = 0
Public Const TTS_FORCE = 1

Public Const OWN_AUDIO_DEVICE = 1
Public Const REPORT_OPEN_ERROR = 2

Public Const WAVE_MAPPER = -1

'constant for
Public Const WAVE_FORMAT_1M08 = 1
Public Const WAVE_FORMAT_1M16 = 2
Public Const WAVE_FORMAT_08M08 = 3


