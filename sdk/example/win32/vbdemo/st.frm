VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3090
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   7665
   BeginProperty Font 
      Name            =   "Times New Roman"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   3090
   ScaleWidth      =   7665
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   6600
      TabIndex        =   8
      Top             =   120
      Width           =   975
   End
   Begin VB.CommandButton gSpeaker 
      Caption         =   "Speaker"
      Height          =   375
      Left            =   5520
      TabIndex        =   7
      Top             =   120
      Width           =   975
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Reset"
      Height          =   375
      Left            =   120
      TabIndex        =   6
      Top             =   2640
      Width           =   735
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   960
      TabIndex        =   5
      Top             =   1680
      Width           =   1935
   End
   Begin VB.TextBox Rate 
      Height          =   330
      Left            =   960
      TabIndex        =   2
      Text            =   "180"
      Top             =   960
      Width           =   735
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Say"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3840
      TabIndex        =   1
      Top             =   360
      Width           =   735
   End
   Begin VB.TextBox Text1 
      BeginProperty Font 
         Name            =   "System"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   3495
   End
   Begin VB.Label typing 
      Caption         =   "Typing Mode"
      Height          =   495
      Left            =   120
      TabIndex        =   4
      Top             =   1560
      Width           =   735
   End
   Begin VB.Label Label1 
      Caption         =   "Set Rate"
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   960
      Width           =   735
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
 Option Explicit
    Dim Speaker As Integer
    Dim vStr As String
    Dim vRate As Integer
    Dim DTResult As Long
    Dim phTTS As Long
    Dim Indexm As Long
    
    
Private Sub Command1_Click()
Dim i As Integer
Dim identifier As Long
Dim status As Long
Dim numstatus As Long

identifier = 1
status = 0
numstatus = 1


'DTResult = TextToSpeechOpenWaveOutFileVB(phTTS, "testvb.wav", WAVE_FORMAT_1M08)

DTResult = TextToSpeechSpeakVB(phTTS, Text1.Text, TTS_FORCE)

'DTResult = TextToSpeechCloseWaveOutFileVB(phTTS)

DTResult = TextToSpeechSetRateVB(phTTS, Rate.Text)

DTResult = TextToSpeechGetRateVB(phTTS, vRate)

'For i = 0 To 10
'DTResult = TextToSpeechGetStatusVB(phTTS, identifier, status, numstatus)
'MsgBox (status)
'Next i



'DTResult = TextToSpeechSyncVB(phTTS)

End Sub

Private Sub Command2_Click()

DTResult = TextToSpeechResetVB(phTTS, True)

End Sub


Private Sub Form_Load()

DTResult = TextToSpeechStartupExVB(phTTS, WAVE_MAPPER, OWN_AUDIO_DEVICE, 0, 1)
If DTResult <> 0 Then
    MsgBox (DTResult)
End If

 DTResult = TextToSpeechLoadUserDictionaryVB(phTTS, "d:\work\rnd\samples\vb\user.dic")


DTResult = TextToSpeechSetSpeakerVB(phTTS, PAUL)

End Sub

Private Sub Form_Unload(Cancel As Integer)

DTResult = TextToSpeechUnloadUserDictionaryVB(phTTS)
DTResult = TextToSpeechShutdownVB(phTTS)

End Sub

Private Sub gSpeaker_Click()

DTResult = TextToSpeechGetSpeakerVB(phTTS, Speaker)

        Select Case Speaker
            Case PAUL
                Text3.Text = "PAUL"
            Case BETTY
                Text3.Text = "BETTY"
            Case HARRY
                Text3.Text = "HARRY"
            Case DENNIS
                Text3.Text = "DENNIS"
            Case KIT
                Text3.Text = "KIT"
            Case FRANK
                Text3.Text = "FRANK"
            Case URSULA
                Text3.Text = "URSULA"
            Case RITA
                Text3.Text = "RITA"
            Case WENDY
                Text3.Text = "WENDY"
            Case Default
            
        End Select

End Sub


Private Sub Text2_Change()

DTResult = TextToSpeechTypingVB(phTTS, Right(Text2.Text, 1))

End Sub


