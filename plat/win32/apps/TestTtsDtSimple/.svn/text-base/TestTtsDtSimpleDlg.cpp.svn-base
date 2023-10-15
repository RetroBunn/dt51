// TestTtsDtSimpleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestTtsDtSimple.h"
#include "TestTtsDtSimpleDlg.h"
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct fileTable
{
	TCHAR langName[50];
	FnxDECtalkLanguageId id;
	TCHAR dictName[256];
	TCHAR tableName[256];
};

TCHAR Fonix_dictname[256] ;
TCHAR Fonix_tablename[256] ;

#define NUM_LANGS 11
#ifndef USE_NAND
fileTable allLangs[NUM_LANGS] = 
{
	{_T("US English"),				US_English,		_T("dtalk_us.dic"),		0},
	{_T("French"),					French,			_T("dtalk_fr.dic"),		0},
	{_T("German"),					German,			_T("dtalk_gr.dic"),		0},
	{_T("Castilian Spanish"),		Castilian_Spanish, _T("dtalk_sp.dic"),		0},
	{_T("Latin American Spanish"),	Latin_American_Spanish,_T("dtalk_la.dic"),	0},
	{_T("UK English"),				UK_English,		_T("dtalk_uk.dic"),		0},
	{_T("Italian"),					Italian,		_T("dtalk_it.dic"),		0},	
	{_T("Hebrew"),					Hebrew,			0,					0},
	{_T("Korean"),					Korean,			_T("Korean.pdc"),		0},
	{_T("Chinese"),					Chinese,		_T("dtalk_ch.cjk"),		0},
	{_T("Japanese"),				Japanese,		_T("onsei.dic"),		0}
};
#else  //USE_NAND

fileTable allLangs[NUM_LANGS] = 
{
	{"US English",			US_English,			"dtalk_us.nand.dic",	"UsEnglish.nand.tab"},
	{"French",				French,				"dtalk_fr.nand.dic",	"French.nand.tab"},
	{"German",				German,				"dtalk_gr.nand.dic",	0},
	{"Castilian Spanish",	Castilian_Spanish,	"dtalk_sp.nand.dic",	0},
	{"Latin American Spanish", Latin_American_Spanish,"dtalk_la.nand.dic",	0},
	{"UK English",			UK_English,			"dtalk_uk.nand.dic",	0},
	{"Italian",				Italian,			"dtalk_it.nand.dic",	0},	
	{"Hebrew",				Hebrew,				0,						0},
	{"Korean",				Korean,				"Korean.pdc",			0},
	{"Chinese",				Chinese,			"dtalk_ch.cjk",			0},
	{"Japanese",			Japanese,			"onsei.dic",			0}
};
#endif  //USE_NAND

//To enable memfile capabilities define USE_MEMFILE_IO and USE_MEM_FILEIO in your projects
//also add MemFiles.c, FnxFiles.c and GlobalCommon.c to the FonixTtsDtSimple project
#if defined USE_MEMFILE_IO 
#include "dtalk_us_dic.mem"
#include "dtalk_fr_dic.mem"
#include "dtalk_gr_dic.mem"
#include "dtalk_la_dic.mem"
#include "dtalk_sp_dic.mem"
#include "dtalk_uk_dic.mem"
#include "dtalk_ch_cjk.mem"
#include "korean.mem"
#include "onsei.mem"

#define NUMBER_OF_MEM_FILES 9

FnxMemFileMapping *MapArray[] = { DTALK_FR_DIC_MAP, DTALK_US_DIC_MAP, DTALK_GR_DIC_MAP, DTALK_LA_DIC_MAP, DTALK_SP_DIC_MAP, DTALK_UK_DIC_MAP, DTALK_CH_CJK_MAP, KOREAN_MAP, ONSEI_MAP };
FnxMemFileMapping CombinedMap[NUMBER_OF_MEM_FILES+1];
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestTtsDtSimpleDlg dialog

CTestTtsDtSimpleDlg::CTestTtsDtSimpleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestTtsDtSimpleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestTtsDtSimpleDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestTtsDtSimpleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestTtsDtSimpleDlg)
	DDX_Control(pDX, IDCreateWav, m_TextInputCreateWav);
	DDX_Control(pDX, IDCreateWavList, m_WordListCreateWav);
	DDX_Control(pDX, IDC_SPEAKLIST, m_WordListSpeakList);
	DDX_Control(pDX, IDC_RESET, m_ResetButton);
	DDX_Control(pDX, IDC_DELETE, m_WordListDelete);
	DDX_Control(pDX, IDC_VOICE, m_Voice);
	DDX_Control(pDX, IDC_LANGUAGE, m_Language);
	DDX_Control(pDX, IDWordListSpeak, m_WordListSpeak);
	DDX_Control(pDX, IDSpeak, m_TextInputSpeak);
	DDX_Control(pDX, IDC_ADD, m_WordListAdd);
	DDX_Control(pDX, IDC_WORDLIST, m_WordList);
	DDX_Control(pDX, IDC_TEXTINPUT, m_TextInput);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestTtsDtSimpleDlg, CDialog)
	//{{AFX_MSG_MAP(CTestTtsDtSimpleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnSpeak)
	ON_BN_CLICKED(IDWordListSpeak, OnWordListSpeak)
	ON_BN_CLICKED(IDC_SPEAKLIST, OnSpeakList)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_LBN_SELCHANGE(IDC_WORDLIST, OnSelchangeWordlist)
	ON_EN_CHANGE(IDC_TEXTINPUT, OnChangeTextinput)
	ON_COMMAND(ID_MENULOADWORDLIST, OnMenuloadwordlist)
	ON_COMMAND(ID_MENUSAVEWORDLIST, OnMenusavewordlist)
	ON_CBN_SELCHANGE(IDC_LANGUAGE, OnSelchangeLanguage)
	ON_CBN_SELCHANGE(IDC_VOICE, OnSelchangeVoice)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDCreateWav, OnCreateWav)
	ON_BN_CLICKED(IDCreateWavList, OnCreateWavList)
	ON_COMMAND(ID_SAMPLERATE11, OnSamplerate11)
	ON_COMMAND(ID_SAMPLERATE8, OnSamplerate8)
	ON_BN_CLICKED(IDSpeak, OnSpeak)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestTtsDtSimpleDlg message handlers

BOOL CTestTtsDtSimpleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
#ifndef USE_MEMFILE_IO
	// TODO: Add extra initialization here
	// Initial path
	CString csFullPath;
	TCHAR sRootDir[256];

	m_csCurrentPath = "\\";

	/*  Get the path and filename of this application  */
	if(GetModuleFileName(AfxGetInstanceHandle(), sRootDir, 256) != 0)
	{
		csFullPath = sRootDir;

		SetWindowText(sRootDir);	// Display the full path to this app in the title bar

		int nIdx = csFullPath.ReverseFind(_T('\\'));
		if (nIdx != -1)
		{
			m_csCurrentPath = csFullPath.Left(nIdx+1);
		}
	}
#else
	m_csCurrentPath = "";
#endif //USE_MEMFILE_IO


	m_TextInput.SetLimitText( 256 );
	m_TextInput.SetWindowText(_T("Welcome"));
	m_TextInput.CanUndo();

	m_Language.SetCurSel (0);
	m_Voice.SetCurSel(0);

	DisableButtons();
	EnableButtons();

// default to 11k
	AudioOutSampleRate = SAMPLE_RATE_11K;
	WaveFormat = WAVE_FORMAT_1M16;
	AudioFrameSize = AUDIO_FRAME_SIZE_11K;

	// default to 8k
//	AudioOutSampleRate = SAMPLE_RATE_8K;
//	WaveFormat = WAVE_FORMAT_08M16;
//	AudioFrameSize = AUDIO_FRAME_SIZE_8K;
#ifdef USE_MEMFILE_IO
	FnxTTSDtSimpleCombineMemFileMaps(MapArray, NUMBER_OF_MEM_FILES, CombinedMap);	// Combine the mem file map arrays into one - Difference for multiple mem files
	FnxTTSDtSimpleMemFileRegister(CombinedMap);
#endif
	if(FnxTTSDtSimpleOpen( NULL, NULL) != 0)
	{
		MessageBox(_T("FnxTTSDtSimpleOpen failed."), _T("Error"), MB_OK);
		PostMessage(WM_CLOSE);
	}

	UpdateData (FALSE);
	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CTestTtsDtSimpleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestTtsDtSimpleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestTtsDtSimpleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestTtsDtSimpleDlg::OnSpeak() 
{
	// TODO: Add your control notification handler code here
	CString csText;
	long actualSamples;
	int LanguageSel;

	LanguageSel = m_Language.GetCurSel();
	m_Language.GetLBText(LanguageSel, csText);

	if(csText.GetLength() == 0)
	{
		::MessageBox(NULL, _T("Please select a language!"), _T("ERROR"), MB_OK);
		return;
	}

	m_TextInput.GetWindowText( csText );

	DisableButtons();

	MyAudioOutOpen( );
#ifdef UNICODE
	actualSamples = FnxTTSDtSimpleStartX( csText.GetBuffer(csText.GetLength()), AudioBuffer, AUDIO_OUT_BUF_LEN, WaveFormat,0);
#else
		actualSamples = FnxTTSDtSimpleStartX( csText.GetBuffer(csText.GetLength()), AudioBuffer, AUDIO_OUT_BUF_LEN, WaveFormat,5);
#endif

	if( actualSamples > 0 )
		MyAudioOutPlay(AudioBuffer, actualSamples);
	else if( actualSamples != 0 )
		MyAudioOutPlay(AudioBuffer, AUDIO_OUT_BUF_LEN);

	MyAudioOutClose( );

	EnableButtons();
}

void CTestTtsDtSimpleDlg::OnWordListSpeak() 
{
	CString csText;
	int nIdx;
	long actualSamples;
	int LanguageSel;

	LanguageSel = m_Language.GetCurSel();
	m_Language.GetLBText(LanguageSel, csText);

	if(csText.GetLength() == 0)
	{
		::MessageBox(NULL, _T("Please select a language!"), _T("ERROR"), MB_OK);
		return;
	}

	DisableButtons();

	nIdx = m_WordList.GetCurSel();
	if (nIdx != LB_ERR)
	{
		csText = m_cslWordList.GetAt(m_cslWordList.FindIndex(nIdx));
	}

	MyAudioOutOpen( );
#ifdef UNICODE
	actualSamples = FnxTTSDtSimpleStartX( csText.GetBuffer(csText.GetLength()), AudioBuffer, AUDIO_OUT_BUF_LEN, WaveFormat, 0);
#else
		actualSamples = FnxTTSDtSimpleStartX( csText.GetBuffer(csText.GetLength()), AudioBuffer, AUDIO_OUT_BUF_LEN, WaveFormat, 5);
#endif
	if( actualSamples > 0 )
		MyAudioOutPlay(AudioBuffer, actualSamples);
	else if( actualSamples < 0 )
		MyAudioOutPlay(AudioBuffer, AUDIO_OUT_BUF_LEN);
	MyAudioOutClose( );

	EnableButtons();
}

void DTListProc( LPVOID lpParameter )
{
	CTestTtsDtSimpleDlg	* dlg = (CTestTtsDtSimpleDlg*) lpParameter;
	long actualSamples = 0;
	int lineCount;
	int nIdx;
	CString csText;

	dlg->m_WordListSpeakList.EnableWindow(TRUE);

	nIdx = dlg->m_WordList.GetCurSel();
	lineCount = dlg->m_WordList.GetCount();

	for(; nIdx< lineCount; nIdx++ )
	{
		if (nIdx != LB_ERR)
		{
			if( nIdx >= 0 )
				dlg->m_WordList.SetSel(nIdx-1, FALSE);		// Unselect last item

			dlg->m_WordList.SetSel(nIdx, TRUE);			// Select item to be spoken
			//dlg->m_WordList.GetText(nIdx, csText);
			csText = dlg->m_cslWordList.GetAt(dlg->m_cslWordList.FindIndex(nIdx));
		}
		dlg->MyAudioOutOpen( );
#ifdef UNICODE
		actualSamples = FnxTTSDtSimpleStartX( csText.GetBuffer(csText.GetLength()), dlg->AudioBuffer, AUDIO_OUT_BUF_LEN, dlg->WaveFormat, 0);
#else
		actualSamples = FnxTTSDtSimpleStartX( csText.GetBuffer(csText.GetLength()), dlg->AudioBuffer, AUDIO_OUT_BUF_LEN, dlg->WaveFormat, 5);
#endif

		if( actualSamples > 0 )
			dlg->MyAudioOutPlay(dlg->AudioBuffer, actualSamples);
		dlg->MyAudioOutClose( );

		if(dlg->m_bStopSpeakingText)
			break;
	}

	dlg->m_WordListSpeakList.SetWindowText(_T("Speak List"));
	dlg->EnableButtons();

}

void CTestTtsDtSimpleDlg::OnSpeakList() 
{
	CString csBtnText;
	int LanguageSel;

	LanguageSel = m_Language.GetCurSel();
	m_Language.GetLBText(LanguageSel, csBtnText);

	if(csBtnText.GetLength() == 0)
	{
		::MessageBox(NULL, _T("Please select a language!"), _T("ERROR"), MB_OK);
		return;
	}

	m_WordListSpeakList.GetWindowText(csBtnText);

	if(csBtnText == "Stop")
	{
		m_bStopSpeakingText = true;
	}
	else
	{
		m_bStopSpeakingText = false;
		DisableButtons();

		m_WordListSpeakList.SetWindowText(_T("Stop"));
		_beginthread(DTListProc, 0, this);
	}
}

void CTestTtsDtSimpleDlg::OnAdd() 
{
	CString csText;
	int nIdx;

	DisableButtons();
	if (m_WordList.GetCount() < WORDLIST_MAX)
	{
		m_TextInput.GetWindowText(csText);
		if (!csText.IsEmpty())
		{
			nIdx = m_WordList.AddString(csText);
			m_cslWordList.AddTail(csText);

			if (nIdx != LB_ERR && nIdx != LB_ERRSPACE)
			{
				m_WordList.SetCurSel(nIdx);
				OnSelchangeWordlist();
			}
		}
	}
	else
	{
		CWnd wnd;
		wnd.MessageBox(_T("Cannot add phrase. Word Set list is full."));
	}
	EnableButtons();
}

void CTestTtsDtSimpleDlg::OnDelete() 
{
	int nIdx;
	int nCnt;
	CString csWordListText, csInputText;
	
	DisableButtons();
	nIdx = m_WordList.GetCurSel();

	if (nIdx != LB_ERR)
	{
		m_WordList.GetText(nIdx, csWordListText);
		m_TextInput.GetWindowText(csInputText);

		nCnt = m_WordList.DeleteString(nIdx);
		m_cslWordList.RemoveAt(m_cslWordList.FindIndex(nIdx));

		if (nCnt != LB_ERR)
		{
			m_WordList.SetCurSel(min(nIdx, nCnt-1));
		}
	}
	EnableButtons();
}

void CTestTtsDtSimpleDlg::OnSelchangeWordlist() 
{
	DisableButtons();
	EnableButtons();
}

void CTestTtsDtSimpleDlg::OnChangeTextinput() 
{
	DisableButtons();
	EnableButtons();
}

void CTestTtsDtSimpleDlg::OnMenuloadwordlist() 
{
	CString csFullPath;
	CString csSavePath;

	CFileDialog filedlg(TRUE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Word Set Files (*.txt)|*.txt|All Files (*.*)|*.*||"));
	filedlg.m_ofn.lpstrInitialDir = (LPCTSTR)m_csCurrentPath;
	csSavePath = m_csCurrentPath;

	if (filedlg.DoModal() == IDOK)
	{
		csFullPath = filedlg.GetPathName();
		if (!csFullPath.IsEmpty())
		{
			CString csText;
//			int nIdx;
			int i;
			CString csMaxLen;
			CSize size;

			TRY
			{
				CStdioFile file(csFullPath, CFile::modeRead | CFile::typeText);

				m_WordList.ResetContent();
				m_cslWordList.RemoveAll();

				i = 0;
				while (file.ReadString(csText) && i++ < WORDLIST_MAX)
				{
					//nIdx = m_WordList.AddString(csText);
					m_cslWordList.AddTail(csText);
					if(csText.GetLength() > csMaxLen.GetLength())
						csMaxLen = csText;
				}

				// don't save the current path until the dictionary path problem is resolved
				//nIdx = csFullPath.ReverseFind(_T('\\'));
				//if (nIdx != -1)
				//{
				//	m_csCurrentPath = csFullPath.Left(nIdx+1);
				//}

				for(i = 0; i < m_cslWordList.GetCount(); i++)
				{
					m_WordList.AddString(m_cslWordList.GetAt(m_cslWordList.FindIndex(i)));
				}

				m_WordList.SetCurSel(0);
				EnableButtons();
				
				size = GetDC()->GetTextExtent(csMaxLen);
				m_WordList.SetHorizontalExtent(size.cx);

				file.Close();
			}
			CATCH( CFileException, e )
			{
				CWnd wnd;
				wnd.MessageBox(_T("Could not open file"));
				return;
			}
			END_CATCH
		}
	}
	m_csCurrentPath = csSavePath;
	SetCurrentDirectory(csSavePath);
}

void CTestTtsDtSimpleDlg::OnMenusavewordlist() 
{
	CString csFullPath;

	CFileDialog filedlg(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Word Set Files (*.txt)|*.txt|All Files (*.*)|*.*||"));
	filedlg.m_ofn.lpstrInitialDir = (LPCTSTR)m_csCurrentPath;
	if (filedlg.DoModal() == IDOK)
	{
		csFullPath = filedlg.GetPathName();
		if (!csFullPath.IsEmpty())
		{
			CString csText;
			int nIdx;

			TRY
			{
				CStdioFile file(csFullPath, CFile::modeCreate | CFile::modeWrite | CFile::typeText);

				int nCnt = m_cslWordList.GetCount();

				for (int i=0; i<nCnt; i++)
				{
					csText = m_cslWordList.GetAt(m_cslWordList.FindIndex(i));
					file.WriteString(csText);
					file.WriteString(_T("\n"));
				}

				nIdx = csFullPath.ReverseFind(_T('\\'));
				if (nIdx != -1)
				{
					m_csCurrentPath = csFullPath.Left(nIdx+1);
				}
				file.Close();
			}
			CATCH( CFileException, e )
			{
				CWnd wnd;
				wnd.MessageBox(_T("Could not open file"));
				return;
			}
			END_CATCH
		}
	}
	
}


void CTestTtsDtSimpleDlg::MyAudioOutOpen( void )
{
	int samplesEachPlay;
	
	AudioOutInit(&samplesEachPlay, AudioOutSampleRate, 2, 1 );
}

short * CTestTtsDtSimpleDlg::MyAudioOutPlayBuffer(short * data, long flag)
{
	switch (flag)
	{
		case 0:
			MyAudioOutPlay(data, AudioFrameSize);
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

void CTestTtsDtSimpleDlg::MyAudioOutPlay(short * data, int samples)
{
	AudioOutPlay(data, samples);
}

void CTestTtsDtSimpleDlg::MyAudioOutClose( void )
{
	AudioOutQuit();
	AudioOutDestroy();	
}

void CTestTtsDtSimpleDlg::OnSelchangeLanguage() 
{
	int LanguageSel;
	CString text;
	int i = 0;
	int ret;

	// we took out some of the languages so we can't use a straight
	// enumeration
	// instead we get the text and compare
	// make sure the text in the table matches what is in the list box data
	LanguageSel = m_Language.GetCurSel();
	m_Language.GetLBText(LanguageSel, text);

	for	(i = 0; i < NUM_LANGS; i++)
	{
		if(_tcscmp(allLangs[i].langName, text) == 0)
		{
			if(allLangs[i].dictName && allLangs[i].dictName[0])
			{
				_stprintf(Fonix_dictname, _T("%s%s"), m_csCurrentPath, allLangs[i].dictName);
			}
			else
			{
				_tcscpy(Fonix_dictname, _T(""));
			}

			if(allLangs[i].tableName && allLangs[i].tableName[0])
			{
				_stprintf(Fonix_tablename, _T("%s%s"), m_csCurrentPath, allLangs[i].tableName);
			}
			else
			{
				_tcscpy(Fonix_tablename, _T(""));
			}
#ifdef UNICODE	
		ret = FnxTTSDtSimpleSetLanguageW( allLangs[i].id, NULL, Fonix_dictname, Fonix_tablename);
#else
		ret = FnxTTSDtSimpleSetLanguage( allLangs[i].id, NULL, Fonix_dictname, Fonix_tablename);
#endif
		if(ret)
		{
			CWnd wnd;
			wnd.MessageBox(_T("FnxTTSDtSimpleSetLanguage Error"));

		}
		}
	}
}

void CTestTtsDtSimpleDlg::OnSelchangeVoice() 
{
	int VoiceNumber;

	VoiceNumber = m_Voice.GetCurSel();
	FnxTTSDtSimpleChangeVoice( (FnxDECtalkVoiceId)VoiceNumber, WaveFormat);
}

void CTestTtsDtSimpleDlg::OnReset() 
{
	DisableButtons();
	m_Language.SetCurSel (0);
	m_Voice.SetCurSel(0);

	FnxTTSDtSimpleResetSpeech();
	EnableButtons();
}

void CTestTtsDtSimpleDlg::OnCreateWav() 
{
	CString csText;
	CString csFileName;
	long actualSamples;
	int LanguageSel;

	LanguageSel = m_Language.GetCurSel();
	m_Language.GetLBText(LanguageSel, csText);

	if(csText.GetLength() == 0)
	{
		::MessageBox(NULL, _T("Please select a language!"), _T("ERROR"), MB_OK);
		return;
	}

	m_TextInput.GetWindowText( csText );

	DisableButtons();
#ifdef UNICODE
	actualSamples = FnxTTSDtSimpleStartX( csText.GetBuffer(csText.GetLength()), AudioBuffer, AUDIO_OUT_BUF_LEN, WaveFormat, 0);
#else
		actualSamples = FnxTTSDtSimpleStartX( csText.GetBuffer(csText.GetLength()), AudioBuffer, AUDIO_OUT_BUF_LEN, WaveFormat, 5);
#endif

	GetFileName();
	WriteWavFile((LPCTSTR)m_csWavFileName, AudioBuffer, actualSamples, AudioOutSampleRate );
	EnableButtons();
}

void CTestTtsDtSimpleDlg::OnCreateWavList() 
{
	CString 
		csText;
	TCHAR
		sText[128];
	int 
		i,
		nIdx, 
		nSelItems,
		*piSelItems;
	long nActualSamples;
	int LanguageSel;

	LanguageSel = m_Language.GetCurSel();
	m_Language.GetLBText(LanguageSel, csText);

	if(csText.GetLength() == 0)
	{
		::MessageBox(NULL, _T("Please select a language!"), _T("ERROR"), MB_OK);
		return;
	}

	DisableButtons();

	if( (nSelItems = m_WordList.GetSelCount()) == LB_ERR )
	{
		goto OnCreateWavListErr;
	}

	if( (piSelItems = (int *)calloc(nSelItems, sizeof(int))) == NULL )
		goto OnCreateWavListErr;

	if( m_WordList.GetSelItems(nSelItems, piSelItems) != nSelItems )
		goto OnCreateWavListErr;

	GetFileName();
	for( i=0; i < nSelItems; i++ )
	{
		nIdx = piSelItems[i];
		m_WordList.GetText(nIdx, sText);
#ifdef UNICODE
		nActualSamples = FnxTTSDtSimpleStartX( sText, AudioBuffer, AUDIO_OUT_BUF_LEN, WaveFormat, 0);
#else
		nActualSamples = FnxTTSDtSimpleStartX( sText, AudioBuffer, AUDIO_OUT_BUF_LEN, WaveFormat, 5);
#endif
		if( i== 0 )
			WriteWavFile((LPCTSTR)m_csWavFileName, AudioBuffer, nActualSamples, AudioOutSampleRate );
		else
			CatWavFile((LPCTSTR)m_csWavFileName, AudioBuffer, nActualSamples, AudioOutSampleRate );

	}
	free(piSelItems);


OnCreateWavListErr:
	EnableButtons();
	return;
	
}


void CTestTtsDtSimpleDlg::GetFileName() 
{
	char path[256];
	CFileDialog filedlg(FALSE, _T("wav"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Wav Files (*.wav)|*.wav|All Files (*.*)|*.*||"));

	sprintf(path, "%S", m_csCurrentPath);
	filedlg.m_ofn.lpstrInitialDir = m_csCurrentPath;//(const TCHAR*)path;
	
	if (filedlg.DoModal() == IDOK)
	{
		m_csWavFileName = filedlg.GetPathName();

		if( m_csWavFileName.IsEmpty() )
		{
			MessageBox(_T("File name is empty!"));
		}
	}
}
	

void CTestTtsDtSimpleDlg::OnSamplerate11() 
{
	// TODO: Add your command handler code here
	AudioOutSampleRate = SAMPLE_RATE_11K;
	WaveFormat = WAVE_FORMAT_1M16;
	AudioFrameSize = AUDIO_FRAME_SIZE_11K;
	GetMenu( )->CheckMenuItem(ID_SAMPLERATE11, MF_CHECKED);
	GetMenu( )->CheckMenuItem(ID_SAMPLERATE8, MF_UNCHECKED );
}

void CTestTtsDtSimpleDlg::OnSamplerate8() 
{
	// TODO: Add your command handler code here
	AudioOutSampleRate = SAMPLE_RATE_8K;
	WaveFormat = WAVE_FORMAT_08M16;
	AudioFrameSize = AUDIO_FRAME_SIZE_8K;

	GetMenu( )->CheckMenuItem(ID_SAMPLERATE11, MF_UNCHECKED );
	GetMenu( )->CheckMenuItem(ID_SAMPLERATE8, MF_CHECKED );
}

void CTestTtsDtSimpleDlg::DisableButtons( void )
{
	m_TextInputSpeak.EnableWindow(FALSE);
	m_TextInputCreateWav.EnableWindow(FALSE);

	m_WordListSpeak.EnableWindow(FALSE);
	m_WordListAdd.EnableWindow(FALSE);
	m_WordListDelete.EnableWindow(FALSE);
	m_WordListSpeakList.EnableWindow(FALSE);
	m_WordListCreateWav.EnableWindow(FALSE);

	m_ResetButton.EnableWindow(FALSE);
}

void CTestTtsDtSimpleDlg::EnableButtons( void )
{
	int nIdx, ListLength;
	CString csTextInput;
	CString csWordListInput;
	int TextInputLength;

	// Enable Text Input Section buttons if there is text in the text box
	m_TextInput.GetWindowText( csTextInput );
	TextInputLength = csTextInput.GetLength();
	if( TextInputLength )
	{
		m_TextInputSpeak.EnableWindow(TRUE);
		m_TextInputCreateWav.EnableWindow(TRUE);
		m_WordListAdd.EnableWindow(TRUE);
	}
	// Enable Word List Buttons if there are entries in the list box
	ListLength = m_WordList.GetCount();
	if( ListLength )
	{
		nIdx = m_WordList.GetCurSel();
		if (nIdx != LB_ERR)
		{
			m_WordList.GetText(nIdx, csWordListInput);
		}
		if( csWordListInput.GetLength() )
		{
			m_WordListSpeak.EnableWindow(TRUE);
			m_WordListCreateWav.EnableWindow(TRUE);
		}
		m_WordListDelete.EnableWindow(TRUE);
		m_WordListSpeakList.EnableWindow(TRUE);
	}

	// If there is text in the text box that matchs an entry in the word list
	// disable the Add button
	if( TextInputLength && ListLength )
	{
		nIdx = 0;
		while( nIdx < ListLength )
		{
			m_WordList.GetText(nIdx, csWordListInput);
			if ( csWordListInput.Compare( csTextInput ) == 0 )
				break;
			nIdx++;
		}
		if ( nIdx < ListLength )
			m_WordListAdd.EnableWindow(FALSE);
	}

	m_ResetButton.EnableWindow(TRUE);
}

void CTestTtsDtSimpleDlg::OnClose() 
{
	FnxTTSDtSimpleClose();	
	CDialog::OnClose();
}
