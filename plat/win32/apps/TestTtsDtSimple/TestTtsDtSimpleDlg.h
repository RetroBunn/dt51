// TestTtsDtSimpleDlg.h : header file
//

#if !defined(AFX_TESTTTSDTSIMPLEDLG_H__79CABCD0_52A3_11D8_B4DC_00508BD6296A__INCLUDED_)
#define AFX_TESTTTSDTSIMPLEDLG_H__79CABCD0_52A3_11D8_B4DC_00508BD6296A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern "C"
{
	#include "FonixTtsDtSimple.h"
	#include "WriteWavFile.h"

extern void AudioOutCreate();
extern void AudioOutInit( int * samplesEachPlay, int sampleRate, int bytesPerSample, int encodingFormat);
extern void AudioOutPlay( short * pData, int samples);
extern void AudioOutQuit();
extern void AudioOutDestroy();

}

#define WORDLIST_MAX 1000

//#define WAVE_FORMAT WAVE_FORMAT_08M16
//#define WAVE_FORMAT WAVE_FORMAT_1M16

#define SAMPLE_RATE_8K 8000
#define AUDIO_FRAME_SIZE_8K 51
#define SAMPLE_RATE_11K 11025
#define AUDIO_FRAME_SIZE_11K 71

/////////////////////////////////////////////////////////////////////////////
// CTestTtsDtSimpleDlg dialog

class CTestTtsDtSimpleDlg : public CDialog
{
// Construction
public:
	CTestTtsDtSimpleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestTtsDtSimpleDlg)
	enum { IDD = IDD_TESTTTSDTSIMPLE_DIALOG };
	CButton	m_TextInputCreateWav;
	CButton	m_WordListCreateWav;
	CButton	m_WordListSpeakList;
	CButton	m_ResetButton;
	CButton	m_WordListDelete;
	CComboBox	m_Voice;
	CComboBox	m_Language;
	CButton	m_WordListSpeak;
	CButton	m_TextInputSpeak;
	CButton	m_WordListAdd;
	CListBox	m_WordList;
	CEdit	m_TextInput;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestTtsDtSimpleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	HICON m_hIcon;
	CString m_csCurrentPath;
	CString m_csWavFileName;
	CStringList m_cslWordList;
	bool m_bStopSpeakingText;

	#define AUDIO_OUT_BUF_LEN 200*1024
//	#define AUDIO_OUT_BUF_LEN 2*71
	short AudioBuffer[AUDIO_OUT_BUF_LEN];
	int AudioOutSampleRate;
	int WaveFormat;
	int AudioFrameSize;
	int AudioBuffersReceived;

	void MyAudioOutOpen( );
	short * MyAudioOutPlayBuffer( short * data, long flag );
	void MyAudioOutPlay(short * data, int samples);
	void MyAudioOutClose( );
	void GetFileName( );
	void DisableButtons( );
	void EnableButtons( );

	// Generated message map functions
	//{{AFX_MSG(CTestTtsDtSimpleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSpeak();
	afx_msg void OnWordListSpeak();
	afx_msg void OnSpeakList();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnSelchangeWordlist();
	afx_msg void OnChangeTextinput();
	afx_msg void OnMenuloadwordlist();
	afx_msg void OnMenusavewordlist();
	afx_msg void OnSelchangeLanguage();
	afx_msg void OnSelchangeVoice();
	afx_msg void OnReset();
	afx_msg void OnCreateWav();
	afx_msg void OnCreateWavList();
	afx_msg void OnSamplerate11();
	afx_msg void OnSamplerate8();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTTTSDTSIMPLEDLG_H__79CABCD0_52A3_11D8_B4DC_00508BD6296A__INCLUDED_)
