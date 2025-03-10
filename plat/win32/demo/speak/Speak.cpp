/**********************************************************************/
/*                                                                    */
/*  COPYRIGHT NOTICE                                                  */
/*                                                                    */
/*	Copyright � 2002 Fonix Corporation. All rights reserved			  */
/*  Copyright � 2000, 2001 Force Computers, Inc., a solectron Company. all rights reserved. */
/*  Copyright (c) Digital Equipment Corporation, 1998                 */
/*																	  */
/*  All Rights reserved. Unpublished rights reserved under the        */
/*  copyright laws of the United States. Copyright is claimed in      */
/*  the computer program and user interface thereof.                  */
/*                                                                    */
/*  The software contained on this media is proprietary to and        */
/*  embodies the confidential technology of Fonix Corporation 		  */
/*  Incorporated. Possession, use, duplication or dissemination of    */
/*  the software and media is authorized only pursuant to a valid     */
/*  written license from Fonix Corporation.							  */
/*                                                                    */
/*  The name of Fonix Corporation may not be used to				  */
/*  endorse or promote products derived from this software without    */
/*  specific prior written permission. All other rights reserved.     */
/*                                                                    */
/*  THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR      */
/*  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, IMPLIED        */
/*  WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS        */
/*  FOR A PARTICULAR PURPOSE.                                         */
/*  Force assumes no responsibility AT ALL for the use or           */
/*  reliability of this software.                                     */
/*                                                                    */
/*                                                                    */
/* +----------------------------------------------------------------+ */
/* | USE, DUPLICATION OR DISCLOSURE BY THE U.S. GOVERNMENT IS       | */
/* | SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH (c)       | */
/* | DFARS 252.227-7013, OR IN FAR 52.227-14 ALT. II, AS APPLICABLE.| */
/* |                                                                | */
/* +----------------------------------------------------------------+ */
/*                                                                    */
/**********************************************************************/

/************************************************************************
 * SPEAK SAMPLE PROGRAM FOR THE DECTALK SOFTWARE                        *
 ************************************************************************
 * Revision History:                                                    *
 *  001 - Initial Creation  (Bill Hallahan)                             *
 *  002 - Fix load and find problems (Kevin Bruckert) (7/19/96)         *
 *  003 - Switched to TextToSpeechStartupEx and added message handler   *
 *          (Kevin Bruckert) (7/22/96)                                  *
 *  004 - Added Control Panel option and DLL version checking           *
 *          (Kevin Bruckert) (7/24/96)                                  *
 *  005 - Added better command parser for quoted parameters             *
 *          (Kevin Bruckert) (8/5/96)                                   *
 *  006 - Removed TextToSpeechStartupEx call due to fix in code         *
 *          (Kevin Bruckert) (10/15/96)                                 *
 *  007 - Added DEMO flag to support dtdemo build                       *
 *          (Steve Kaufman)  (12/11/96)                                 *
 *  008 - Add highlighting, versioning information, usage parameters,   *
 *        abd error termination.   (Kevin Bruckert) (12/17/96)          *
 *  009 - Moved the version numbers, and added NO_HIGHLIGHT option      *
 *          (Kevin Bruckert) (12/18/96)                                 *
 *  010 - Put in fix for license info under Help, About DTdemo menu     *
 *			(Steve Kaufman) (12/19/96)                            *
 *  011 - Fixed highlighting to support tabs as whitespace              *
 *          (Kevin Bruckert) (1/14/97)                                  *
 *  012 - Added new speed control and set default to 200 WPM            *
 *          (Kevin Bruckert) (1/14/97)                                  *
 *  013 - Merge the fix in V4.3 speak.c                                 *
 *  014 - Put in new changes for DTDemo from Anne and Rich              *
 *          (Kevin Bruckert) (1/22/97)                                  *
 *  015 - Fixed WM_CUT as the way to clear the edit control to WM_CLEAR *
 *          (Kevin Bruckert) (2/3/97)                                   *
 *  016 - Fixed FIND function again. Was caused by premature free call  *
 *      - and bug in find algorithm. Is now fixed, and functional.      *
 *          (Kevin Bruckert) (2/3/97)                                   *
 *  017 - Change COMMAND.TXT to COMMANDS.TXT                            *
 *          (Carl Leeber) (2/20/97)                                     *
 *  018a- Use symbol DTALK_HELP_FILE_NAME BATS#307; Changed help call.  *
 *          (Carl Leeber) (4/16/97)                                     *
 *  018b- Added RELOAD and RESTART DECTALK items                        *
 *          (Kevin Bruckert) (3/31/97)                                  *
 *  019a- For BATS#373 fix the table reading problem in hightlight mode *
 *          (Ginger Lin) (5/14/97)                                      *
 *  019b- Use symbol DTALK_HELP_FILE_NAME BATS#307; Changed help call.  *
 *          (Carl Leeber) (4/16/97)                                     *
 *  020a- For BATS#DUNNO Fix the check for DECTALK.DLL Version, and     *
 *      - also taught SPEAK what ACCESS32 vs DECTALK means (no typing)  *
 *          (Kevin Bruckert) (8/1/97)                                   *
 *  020b- Added DEBUG mode testing                                      *
 *          (Kevin Bruckert) (5/07/97)                                  *
 *  021a- Moved registry entries to coop.h                              *
 *          (Nick Shin) (08/07/97)                                      *
 *  021b- Added easter egg in ABOUT area                                *
 *          (Kevin Bruckert) (6/25/97)                                  *
 *  022 - Change helptopic entry.                                       *
 *          (Carl Leeber) (8/15/97)                                     *
 *  023 - Fixed bug with half-highlights and fixed highlight done       *
 *          (Kevin Bruckert) (8/19/97) (BATS 445)                       *
 *  024 - Merged in the Multi-Language version of Speak into code-base  *
 *          (Nick Shin) (9/12/97)                                       *
 *  025 - Re-fixed highlighting/index mark bug.                         *
 *          (Carl Leeber/KSB) (9/29/97)
 *  026 - Add UK_english support.                                       *
 *          (Ginger Lin) (10/02/97)
 *  027 - Corrected error exit message.                                 *
 *          (Nick Shen)  (10/06/97)                                     *
 *  028 - Now using ML stuff as the standard setting                    *
 *          (Nick Shen)  (10/16/97)                                     *
 *  029 - Added English UK to edit menu                                 *
 *          (Matthew Schnee) (01/07/1998)                               *
 *  030 - Made current language checked in the menu BATS #563			*
 *			(Matthew Schnee) (02/02/1998)								*
 *  031 - For BATS #456  Fixed GetInstallationInfo(...) so it accesses  *
 *		- correct key within the registry.                              *
 *          (Jason Warlikowski) (2/13/98)                               *
 *  032 - For BATS #632  Use the right "what" for each language         *
 *          (Ginger Lin) (4/16/98)                                      *
 *  033 - BATS #599 Made speak only load 1 language at a time with ML   *
 *          (Matthew Schnee) (7/8/1998)
 *  034	- bats 518: correct min rate for Access32. tek 02nov98			*
 *  035	- bats 862: use SPANISH_LA and SPANISH_SP compiler switch. GL 29Jan99 *
 *  036 - Added French support.
 *          (Charles Jordan) (7/21/2000)
 *	037	- Fixed warnings
 *			(Matthew Schnee) (09/19/2000)
 *	038	- Added French demo
 *			(Matthew Schnee) (10/13/2000)
 *  039 - Fixed copyright
 *          (christian Berrios) 10/13/2000)
 * 040 CAB 12/06/00		1. Fixed error change file from commands to command.txt
 *						2. In addition added [tts_select] to TextToSpeechReset to remove crash error.
 * 041 CAB 12/08/00		1. Fixed bug which asked to saveas when file had a filename already
 *						2. Changed TXT to lowercase for display and saveas extension.
 * 042 CAB	04/04/01	Fixed 0 size file open bug
 * 043 MGS	05/03/2001	Removed useless calls to startup/shutdown for the typing demo.
 *						Part of ACCESS32 Integration BATS #972
 * 044 CAB	05/14/2001	Updated and corrected copyright info
 * 045 CAB	05/16/2002	Removed easter egg stuff
 * 046 CAB	08/08/2002	Updated version
 * 047 CAB	08/13/2002	Changed rate to 180 per Ed
 * 048 MFG	06/30/2003	removed the checkversion() call to fix mismatched dlls
 * 049 MFG	07/07/2003  changed the speak rate from 74 to 50 for the min
 ************************************************************************/

#include "Speak.h"
#include "CodePageConv.h"
#include "resource.h"
#include "port.h"

#include <commctrl.h>

#define SPEAK_C
#include "coop.h"
#undef SPEAK_C

#define fbHeight		64
#define stHeight		20
#define border			2
#define etWidth			600 - border * 4   //edit text for words to speek
#define etHeight		330 - border * 4
#define awWidth			etWidth + border * 4 + 4    //application window
#define awHeight		fbHeight + 60 + stHeight + border * 4  + etHeight

#define FILESIZE 256


#ifdef UNICODE
#define _mytcstombs(a, b, c)	wcstombs(a, b, c)
#define _mymbstotcs(a, b, c)	mbstowcs(a, b, c)
#else
#define _mytcstombs(a, b, c)	strcpy(a, b)
#define _mymbstotcs(a, b, c)	strcpy(a, b)
#endif


/* Command Line Parser */
BOOL CmdParse(LPSTR CmdLine, LPTSTR filename, LPTSTR dictname);
VOID TTSCallbackRoutine(LONG lParam1, LONG lParam2, DWORD dwInstanceParam, UINT uiMsg);

void typing_demo(HANDLE hinst, HWND hWnd);
void update_mark(ULONG);

BOOL APIENTRY AboutTypingProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
BOOL APIENTRY TypingDlgProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ParamsDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK EditWndSubClassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
WNDPROC glpPrevWndFunc;

void WriteSpeechToWaveFile(HWND hWnd, LPTTS_HANDLE_T phTTS, TCHAR *tsFile, int format);

extern void TranslateJapaneseWordList(LPTTS_HANDLE_T *phTTS, int iLang, char *sWordList, char *sTranslationFile);
extern void CompareKanjiKanaTranslation(LPTTS_HANDLE_T *phTTS, int iLang, char *sWordList, char *sOutFile, char *sAccentFile);

WNDPROC OldTypingDlgProc;

MARK_POS *mark_pos = NULL;
HWND DECtalkSpeakWin;
HANDLE hInst;
LPLANG_ENUM languageINFO;

TCHAR *tsAppName = _T("Speak");

/**********************************************************************/
/*  Global variables.                                                 */
/**********************************************************************/

BOOL SaveSaveAs = TRUE;			// Do we need to do "Save" as "Save As"?

BOOL CPanel = FALSE;			// Control Panel DLL version found	KSB
BOOL gbHilite = FALSE;			// Highlighting Demo Available
BOOL gbShowRomanji = FALSE;		// Translate Unicode characters to Romanji and display
BOOL gbTyping = FALSE;			// Typing Demo Available			KSB

LPTTS_HANDLE_T	phTTS[20];
unsigned int	tts_select = 0;
WNDPROC			opVoiceControls;
HWND			hSpeakText, hFind;
OPENFILENAME	OpenWaveName;
OPENFILENAME	OpenFileName;
OPENFILENAME	OpenDictName;
PBYTE			pFileData;
ULONG			speak_mark = 0;

unsigned int	DECtalk_maj_ver, 
				DECtalk_min_ver,
				DECtalk_compute,
				DECtalk_build;
TCHAR			*tsDECtalk_version;
BOOL			DECtalk_Debug;

TCHAR			tsFile[FILESIZE]			= _T("\0");
TCHAR			tsFileTitle[FILESIZE]		= _T("\0");
TCHAR			tsFileSave[FILESIZE]		= _T("\0");
TCHAR			tsFileTitleSave[FILESIZE]	= _T("\0");
TCHAR			tsFindText[FILESIZE];
TCHAR			szReplaceText[FILESIZE];
TCHAR			szWaveFilter[] = _T("Wave Files (*.WAV)\0*.WAV\0All Files (*.*)\0*.*\0\0");
TCHAR			szFilter[] = _T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0");
TCHAR			szWaveFile[256] = _T("\0");
TCHAR			szWaveFileTitle[256];

HANDLE hFile = 0;
char szBuf[32];
HANDLE hFileMap ;
OWNERDRAW odButton[NUM_BUTTONS];

HWND hPlay, hPause, hStop;
int cBufLen;
int highlight = 0;              // KSB - Highlighting disabled by default

// variables to hold the rate limits
int rateMax = RATE_MAX;
int rateMin = RATE_MIN;


/* New functions  (KSB) */
//void easter_egg(void);
BOOL CheckVersion(void);

// This array must match the number and order of the enum TTS_LANGUAGES in Speak.h
TCHAR *gtsLang[] = {
	_T("US"),
	_T("FR"),
	_T("GR"),
	_T("IT"),
	_T("LA"),
	_T("SP"),
	_T("UK"),
	_T("CH"),
	_T("JP"),
	_T("KR"),
	_T("HB")
};

SPEAK Speak;
TTS_LANGUAGES geStartupLang=eEnglish;

/********************************************************************
 *      Function Name:	SetLanguageFont
 *      Description:	Make sure that the edit box is using the correct font
						for the selected language.
 *      Arguments:		pSpeak - pointer to SPEAK structure
 *      Return Value:	none
 *      Comments:
 * *****************************************************************/
void SetLanguageFont(SPEAK *pSpeak)
{
	int		nHeight;
	DWORD	charSet;
	
	if( pSpeak->hFont )
		DeleteObject(pSpeak->hFont);

	switch(pSpeak->eCurLang)
	{
		case eEnglish:
		case eFrench:
		case eGerman:
		case eItalian:
		case eLatin:
		case eSpanish:
		case eUKEnglish:	charSet = ANSI_CHARSET;         break;
		case eJapanese:		charSet = SHIFTJIS_CHARSET;     break;
		case eKorean:		charSet = HANGUL_CHARSET;		break;
		case eMandarin:		charSet = GB2312_CHARSET;		break;
		case eHebrew:		charSet = HEBREW_CHARSET;       break;
		//case CANTONESE:   charSet = CHINESEBIG5_CHARSET;  break;
		//case ARABIC:      charSet = ARABIC_CHARSET;       break;
		//case THAI:        charSet = THAI_CHARSET;         break;
		//case RUSSIAN:     charSet = RUSSIAN_CHARSET;      break;
		//case TURKISH:     charSet = TURKISH_CHARSET;      break;
		//case EASTEUROPE:  charSet = EASTEUROPE_CHARSET;   break;
		default:			charSet = ANSI_CHARSET;         break;
	}

	// Calculate the font height for a given point size (12)
	nHeight = -MulDiv(12, GetDeviceCaps(pSpeak->myHdc, LOGPIXELSY), 72);
	pSpeak->hFont = CreateFont( nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, charSet, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("MS Sans Serif") );
	SendMessage( pSpeak->hSpeakText, WM_SETFONT, (WPARAM)pSpeak->hFont, 0 );
	
}


/********************************************************************
 *      Function Name:	LoadVoiceNames
 *      Description:
 *      Arguments:		pSpeak - pointer to SPEAK structure
 *      Return Value:	none
 *      Comments:
 * *****************************************************************/
void LoadVoiceNames(SPEAK *pSpeak)
{
	int i, id;
	TCHAR tsText[MAX_VOICE_NAME_SIZE];

	switch(pSpeak->eCurLang)
	{
		case eEnglish:		id = VS_US_Paul;	break;
		case eFrench:		id = VS_FR_Paul;	break;
		case eGerman:		id = VS_GR_Paul;	break;
		case eItalian:		id = VS_IT_Paul;	break;
		case eLatin:		id = VS_LA_Paul;	break;
		case eSpanish:		id = VS_SP_Paul;	break;
		case eUKEnglish:	id = VS_US_Paul;	break;
		case eMandarin:		id = VS_CH_Paul;	break;
		case eJapanese:		id = VS_JP_Paul;	break;
		case eKorean:		id = VS_KR_Paul;	break;
		case eHebrew:		id = VS_HB_Paul;	break;
	}


	for( i=0; i < NUM_TTS_VOICES; i++ )
	{
		// extract voice test message from resource
		LoadString(NULL, id+i, pSpeak->tsVoiceName[i], MAX_VOICE_NAME_SIZE);
		
		LoadString(NULL, VS_PerfectPaul+i, tsText, MAX_VOICE_CMD_SIZE);
		_mytcstombs(pSpeak->sVoiceCmd[i], tsText, MAX_VOICE_CMD_SIZE);

	}
}
/*FUNCTION_HEADER**********************
 * NAME:	;SetWindowTitle
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void SetWindowTitle(HWND hWnd, TCHAR *tsFilename)
{
	TCHAR tsTitle[128];
	TCHAR tsBuild[6];

	if( DECtalk_build == 0 )
		_tcscpy(tsBuild, _T("Dbg"));
	else
		_tcscpy(tsBuild, _T("Rls"));

	if( tsFilename )
		_stprintf(tsTitle, _T("%s (%s-%s) - %s"), 
			tsAppName,
			tsBuild,
			DECtalk_compute ? _T("HC"): _T("LC"), 
			tsFilename);
	else
		_stprintf(tsTitle, _T("%s (%s-%s)"), 
			tsAppName, 
			tsBuild,
			DECtalk_compute ? _T("HC"): _T("LC"));

	SetWindowText(hWnd, tsTitle);
}


/********************************************************************
 *      Function Name: WinMain()
 *
 *      Description:
 *
 *      Arguments:	HINSTANCE hInstance
 *					HINSTANCE hPrevInstance
 *					LPSTR lpCmdLine
 *					int nCmdShow
 *
 *      Return Value: int:
 *
 *      Comments:
 *
 * *****************************************************************/
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine, int nCmdShow)
{
	TCHAR		tsFilename[_MAX_PATH], 
				tsDictname[_MAX_PATH];
	int			iX;
	int			iY;
	int			iWidth;
	int			iHeight;
	int			iShow;
	HWND        hWnd;
	WNDCLASS    wndclass;
	MSG         msg;
	int         xScreen, yScreen;
	int         i = 1;
	MMRESULT    mmStatus;
	OSVERSIONINFO  OSVersionInfo;
	HMENU			main_menu, sub_menu;	// KSB Dec 16,1996 - Add Control Panel menu option
	MENUITEMINFO	menu_item;
	
	_tcscpy(tsFilename, _T(""));				// No default file to load
	_tcscpy(tsDictname, _T(""));				// No default user dictionary to load
	
	// Scan for command-line parameters now, so we can quit if we wish
	if( CmdParse(lpCmdLine, tsFilename, tsDictname) )
		return (FALSE);
	
	OSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&OSVersionInfo);
	
	hInst = hInstance;
	
	if (CheckVersion() == FALSE)	 
		return (FALSE);					// This has to be called for the help (about speak to work)
	
	wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC;
	wndclass.lpfnWndProc   = (WNDPROC) WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = NULL ;
	wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE( ICON_APP ));
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH)GetStockObject (BLACK_BRUSH) ;
	wndclass.lpszMenuName  = _T("SPEAK_MENU");
	wndclass.lpszClassName = tsAppName ;
	
	if ( ! RegisterClass( &wndclass ))
		return( FALSE );
	
	hFind = NULL;	/* Fixed memory leak in Speak.C (Found with Purify)  KSB */
	
	xScreen = GetSystemMetrics( SM_CXSCREEN );
	yScreen = GetSystemMetrics( SM_CYSCREEN );
	yScreen = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYSIZEFRAME)*2;
	
	GetApplicationParameters( &iX, &iY, &iWidth, &iHeight, &iShow, tsFile );
	
	hWnd = CreateWindow( tsAppName,
					   tsAppName,
					   WS_CAPTION | WS_SYSMENU
					   | WS_OVERLAPPEDWINDOW | WS_VISIBLE
					   | WS_MINIMIZEBOX,
					   iX,
					   iY,
					   658,	// using width of bitmap
					   400+yScreen,
					   NULL, NULL, NULL, NULL );
	
	/* If window could not be created, return "failure" */
	
	if ( !hWnd )
	{
		//error = GetLastError();
		return( FALSE );
	}
	
	SetWindowTitle(hWnd, NULL);

	ShowWindow( hWnd, iShow );
	UpdateWindow( hWnd );                /* Sends WM_PAINT message */
	DragAcceptFiles( hWnd, TRUE );       //Accept files dragged from File Manager
	

	/* KSB  Dec 17, 1996 - Add separator if more options to be added */
	main_menu = GetMenu(hWnd);
	sub_menu = GetSubMenu(main_menu, 1);
	if( gbHilite || gbTyping || CPanel) 
	{
		menu_item.cbSize = sizeof(MENUITEMINFO);
		menu_item.fMask = MIIM_DATA | MIIM_ID | MIIM_STATE | MIIM_TYPE;
		menu_item.fType = MFT_SEPARATOR;
		menu_item.fState = 0;
		menu_item.wID = 0;
		menu_item.hSubMenu = NULL;
		menu_item.hbmpChecked = NULL;
		menu_item.hbmpUnchecked = NULL;
		menu_item.dwItemData = 0;
		InsertMenuItem(sub_menu, 99, 1, &menu_item);
	}
	/* KSB  Dec 17, 1996 - Add highlight menu option IF highlighting is available */
	if( gbHilite ) 
	{
		menu_item.cbSize = sizeof(MENUITEMINFO);
		menu_item.fMask = MIIM_DATA | MIIM_ID | MIIM_STATE | MIIM_TYPE;
		menu_item.fType = MFT_STRING;
		menu_item.fState = 0;
		menu_item.wID = IDM_HIGHLIGHT;
		menu_item.hSubMenu = NULL;
		menu_item.hbmpChecked = NULL;
		menu_item.hbmpUnchecked = NULL;
		menu_item.dwItemData = IDM_HIGHLIGHT;
		menu_item.dwTypeData = _T("&Highlighting");
		menu_item.cch = _tcslen(menu_item.dwTypeData);
		InsertMenuItem(sub_menu, 99, 1, &menu_item);
	}
	/* KSB  Dec 17, 1996 - Add typing demo menu option IF typing demo is available */
	if( gbTyping ) 
	{
		menu_item.cbSize = sizeof(MENUITEMINFO);
		menu_item.fMask = MIIM_DATA | MIIM_ID | MIIM_STATE | MIIM_TYPE;
		menu_item.fType = MFT_STRING;
		menu_item.fState = 0;
		menu_item.wID = IDM_TYPING;
		menu_item.hSubMenu = NULL;
		menu_item.hbmpChecked = NULL;
		menu_item.hbmpUnchecked = NULL;
		menu_item.dwItemData = IDM_TYPING;
		menu_item.dwTypeData = _T("&Typing Demo");
		menu_item.cch = _tcslen(menu_item.dwTypeData);
		InsertMenuItem(sub_menu, 99, 1, &menu_item);
	}
	/* KSB  Dec 16, 1996 - Add Control Panel menu option IF the CPanel is available */
	if (CPanel) 
	{
		menu_item.cbSize = sizeof(MENUITEMINFO);
		menu_item.fMask = MIIM_DATA | MIIM_ID | MIIM_STATE | MIIM_TYPE;
		menu_item.fType = MFT_STRING;
		menu_item.fState = 0;
		menu_item.wID = ID_CPANEL;
		menu_item.hSubMenu = NULL;
		menu_item.hbmpChecked = NULL;
		menu_item.hbmpUnchecked = NULL;
		menu_item.dwItemData = ID_CPANEL;
		menu_item.dwTypeData = _T("&Control Panel");
		menu_item.cch = _tcslen(menu_item.dwTypeData);
		
		main_menu = GetMenu(hWnd);
		sub_menu = GetSubMenu(main_menu, 1);
		InsertMenuItem(sub_menu, 99, 1, &menu_item);
	}
	

	// Check for command line invocation with filename and dictionary name
	if( _tcslen(tsDictname)) 
	{
		TextToSpeechUnloadUserDictionary(phTTS[tts_select]);
		mmStatus = _TextToSpeechLoadUserDictionary(phTTS[tts_select], tsDictname);
		if ( mmStatus )
		{
			if (mmStatus == MMSYSERR_ERROR)
				MessageBox( hWnd, _T("Illegal dictionary format"), _T("Load User Dictionary"), MB_OK | MB_ICONSTOP );
			else
				MessageBox( hWnd, _T("Error in TTS Load Dictionary"), _T("ERROR"), MB_OK | MB_ICONSTOP );
		}
	}
	
	if( _tcslen(tsFilename)) 
	{
		if (!MyReadFile(hWnd, tsFilename))
		{
			SaveSaveAs = FALSE;
			_tcscpy(tsFile, tsFilename);
			DrawMenuBar( hWnd);

			// reset the title in the title bar to reflect the
			// new open file
			SetWindowTitle(hWnd, tsFilename);
			InvalidateRect( hSpeakText, NULL, TRUE );
			DrawMenuBar( hWnd );
			SpeakText( hWnd );
		}
	}
	
	
	/* Enter message loop */
	while (GetMessage (&msg, NULL, 0, 0))
	{
		if( hFind==NULL || !IsDialogMessage( hFind, &msg ) )
		{
			TranslateMessage (&msg) ;
			DispatchMessage (&msg) ;
		}
	}
	
	return msg.wParam ;
}

/*FUNCTION_HEADER**********************
 * NAME:	;EditWndSubClassProc
 * DESC: 	This sub-class of the edit window allows the user to 
			press F5 to synthesize the text and output to the audio subsystem.
			press F6 to synthesize the text and output to a temporary file which is cleaned up.
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
LRESULT CALLBACK EditWndSubClassProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch( msg )
	{
		case WM_KEYDOWN:
			switch( wParam )
			{
			case VK_F4:
				if( SaveWaveName(GetParent(hWnd)) )
				{
					WriteSpeechToWaveFile(hWnd, phTTS[tts_select], OpenWaveName.lpstrFile, WAVE_FORMAT_1M16);
				}
				break;

			case VK_F5:
				SpeakText( GetParent(hWnd) );
				break;

			case VK_F6:
				WriteSpeechToWaveFile(GetParent(hWnd), phTTS[tts_select], _T(".\\temp.wav"), WAVE_FORMAT_1M16);
				DeleteFile(_T(".\\temp.wav"));
				break;
			}
			break;
	}
	
	return CallWindowProc(glpPrevWndFunc, hWnd, msg, wParam, lParam);

}


/* *******************************************************************
 *      Function Name: WndProc()
 *
 *      Description:
 *
 *      Arguments:	HWND hWnd
 *					UINT uiMessage
 *					WPARAM wParam
 *					LPARAM lParam
 *
 *      Return Value: LONG
 *
 *      Comments:
 *
 * *************************************************************** */
LONG APIENTRY WndProc(HWND hWnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	MMRESULT mmStatus;
	PAINTSTRUCT ps;
	
	RECT	lprc;
	INT		i, x;
	
	static FARPROC  oldEditProc;
	static HBRUSH hOldBrush, hBrush;
	static char szVolume[5];
	static char szRate[5];
	static short wSpos = SPEAK_RATE;
	static DWORD VolumeLevel;
	LPMINMAXINFO  lpmmiSize;
	DWORD dwStart, dwEnd, dwOffset;
	LONG lSelect;
	DWORD dwTextLen;
	LPTSTR lptsEditText, lpSelBuf;
	static UINT uiID_Error_Msg;
	static UINT uiMessage_Find_Replace;
	static  LPFINDREPLACE lpfrText;
	TCHAR tsError[132];
	MARK_POS *next;
	HMENU main_menu, sub_menu;
	MENUITEMINFO menu_info;
	
	switch ( uiMessage )
	{
		case WM_DESTROY:
			SetApplicationParameters( hWnd, tsFile );
			
			mmStatus = TextToSpeechShutdown( phTTS[tts_select] );
			
			/* Free mark_pos buffer */
			next = mark_pos;
			while (next != NULL) 
			{
				mark_pos = next->next_mark;
				free(next);
				next = mark_pos;
			}
			
			PostQuitMessage(0);
			break ;
		
		case WM_CLOSE:

			DeleteObject(Speak.hSkinBmp);
			ReleaseDC(hWnd, Speak.myHdc);
			DeleteObject(Speak.hMemDC);
			for(i=0, x=0; i < NUM_BUTTONS; i++)
			{
				DeleteObject(odButton[i].hBitmap);
				DeleteObject(odButton[i].hSelectedBmp);
				DeleteObject(odButton[i].hDC);
			}

			if ( SendMessage( hSpeakText, EM_GETMODIFY, 0L, 0L ))
			{
				if ( AskToSave( hWnd ))        // returns FALSE is yes or no TRUE if CANCEL
				{
					break ;
				}                            // Cancel pressed
				DestroyWindow( hWnd );
				break;
			}
			
			DestroyWindow( hWnd );
			break ;
		
		case WM_CREATE:
			memset(&Speak, 0, sizeof(SPEAK));
			Speak.hWndApp = hWnd;

			uiID_Error_Msg = RegisterWindowMessage(_T("DECtalkErrorMessage"));
			uiMessage_Find_Replace = RegisterWindowMessage( _T("commdlg_FindReplace") );
			GetClientRect(hWnd, &lprc);

			Speak.myHdc = GetDC(hWnd);
			Speak.hSkinBmp	= LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SKIN));
			Speak.hMemDC	= CreateCompatibleDC( Speak.myHdc );
			SelectObject( Speak.hMemDC, Speak.hSkinBmp );

			// Create the edit window
			hSpeakText = CreateWindow(_T("EDIT"), _T(""),
				WS_CHILD |WS_VISIBLE | WS_VSCROLL | WS_BORDER | ES_LEFT |
				ES_MULTILINE | ES_AUTOVSCROLL | ES_NOHIDESEL | DS_LOCALEDIT,
				15,
				fbHeight,
				etWidth,
				etHeight ,
				hWnd, NULL,NULL, NULL);

			glpPrevWndFunc = (WNDPROC)SetWindowLong(hSpeakText, GWL_WNDPROC, (LONG)EditWndSubClassProc);

			Speak.hSpeakText	= hSpeakText;
			DECtalkSpeakWin		= hSpeakText;
			SendMessage(hSpeakText,EM_LIMITTEXT,(WPARAM)0,(LPARAM)0);
			
			//  Get the size of the Skin bitmap
			GetObject(Speak.hSkinBmp, sizeof(BITMAP), &Speak.bmp);

			// Create the Play, Pause, Stop buttons
			for(i=0, x=0; i < NUM_BUTTONS; i++)
			{
				odButton[i].hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_PLAY+i));
				odButton[i].hSelectedBmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_PLAYDN+i));
				GetObject(odButton[i].hBitmap, sizeof(BITMAP), &odButton[i].bmp);
				odButton[i].hDC = CreateCompatibleDC( Speak.myHdc );
				SelectObject(odButton[i].hDC, odButton[i].hBitmap);

				odButton[i].hWnd = CreateWindow(_T("BUTTON"), _T(""),
					WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
					x,
					lprc.bottom - odButton[i].bmp.bmHeight,
					odButton[i].bmp.bmWidth,
					odButton[i].bmp.bmHeight,
					hWnd,  NULL, NULL, NULL);

				x += odButton[i].bmp.bmWidth;

				// subclass buttons
				opVoiceControls = (WNDPROC)GetWindowLong (odButton[i].hWnd, GWL_WNDPROC);
				SetWindowLong (odButton[i].hWnd, GWL_WNDPROC, (LONG)npVoiceControls);
			}

			main_menu = GetMenu(hWnd);
			sub_menu = GetSubMenu(main_menu, 0);
			
			if(TextToSpeechEnumLangs(NULL) == 0) 
			{
				MessageBox(NULL, _T("Unable to allocate Memory"), _T("Error"),MB_OK);
				exit(-1);
			}
			
			Speak.nLang = 0;
			for( x=0; x < NUM_TTS_LANGUAGES; x++ )
			{
				Speak.iTTSId[x] = _TextToSpeechStartLang(gtsLang[x]);
				if( (Speak.iTTSId[x] & TTS_LANG_ERROR) == 0) 
				{
					Speak.nLang++;
					Speak.bTTSOn[x] = TRUE;
					EnableMenuItem(main_menu, IDM_ENGLISH+x, MF_BYCOMMAND | MF_ENABLED);
				}
			}

#ifdef NDEBUG
			DeleteMenu(main_menu, ID_EDIT_PROGRAMMERDEFINED, MF_BYCOMMAND);
#endif

			if( Speak.nLang == 0 )
			{
				MessageBox(NULL, _T("No languages available"), _T("Error"),MB_OK);
				exit(1);
			}

			// Setup to load the first language available
			if( geStartupLang > eEnglish &&
				Speak.bTTSOn[geStartupLang] )
			{
				Speak.eCurVoice = ePaul;
				Speak.eCurLang = geStartupLang;
				Speak.tts_select = tts_select = Speak.iTTSId[geStartupLang];

				SendMessage(hWnd, WM_COMMAND, IDM_ENGLISH+geStartupLang, 0);
			}
			else
			{
				for( i = 0; i < NUM_TTS_LANGUAGES; i++ )
				{
					if( Speak.bTTSOn[i] )
					{
						// Set some initial defaults
						Speak.eCurVoice = ePaul;
						Speak.eCurLang = (TTS_LANGUAGES)(eEnglish+i);
						Speak.tts_select = tts_select = Speak.iTTSId[i];

						SendMessage(hWnd, WM_COMMAND, IDM_ENGLISH+i, 0);
						break;
					}
				}
			}

			TextToSpeechSelectLang(NULL,tts_select);
			mmStatus = TextToSpeechStartupEx(&phTTS[tts_select], WAVE_MAPPER, REPORT_OPEN_ERROR, TTSCallbackRoutine, 0);
			
			menu_info.cbSize=sizeof(menu_info);
			menu_info.fMask=MIIM_STATE;
			menu_info.fState=MFS_CHECKED;
			SetMenuItemInfo(GetMenu(hWnd), Speak.current_language, FALSE, &menu_info);
			SetMenuItemInfo(GetMenu(hWnd), Speak.eCurVoice+ID_VOICE_PAUL, FALSE, &menu_info);		
			
			if ((mmStatus == MMSYSERR_NODRIVER) || (mmStatus == WAVERR_BADFORMAT))
			{
				MessageBox( hWnd, _T("No compatible wave device present \n You can continue but only to write wave files"), _T("Warning"), MB_OK );
				mmStatus = TextToSpeechStartup(hWnd, &phTTS[tts_select], 0, DO_NOT_USE_AUDIO_DEVICE );
				if ( mmStatus == MMSYSERR_ERROR)
				{
					MessageBox( hWnd, _T("Can't find DECtalk Dictionary \n dectalk.dic, Shutting down!"), _T("SPEAK ERROR"), MB_OK );		
					return( -1 );
				}
				else if ( mmStatus != MMSYSERR_NOERROR)
				{
					MessageBox( hWnd, _T("Can't find DECtalk Dictionary \n dectalk.dic, Shutting down!"), _T("SPEAK ERROR"), MB_OK );		
					return( -1 );
				}
				
				if (mmStatus)
				{
					_stprintf( tsError, _T("Error = %d"), mmStatus );
					
					MessageBox(hWnd, tsError, _T("TTS startup with no audio device"), MB_OK | MB_ICONSTOP );
					
				}
			}
			
			// tek 23aug96 punt on any error..
			if (mmStatus && mmStatus != 11)		// KSB - 11 is bad dictionary, message displayed already in lsw_main.c
			{
				_stprintf( tsError, _T("TTS startup failed\n\nError = %d\n\nExiting out of application"), mmStatus );
				// ncs 06oct97 - error out of application if TextToSpeechStartUp Fails
				// (actually changing the message of the error messageBox)
				MessageBox(NULL, tsError, _T("Speak cannot be started."), MB_OK | MB_ICONSTOP);
				
				DestroyWindow(hWnd);
				return( -1 );
			} 
			else if (mmStatus == 11) 
			{
				MessageBox(NULL, _T("Dictionary not found"), _T("TTS startup failed"), MB_OK | MB_ICONSTOP);
				DestroyWindow(hWnd);
				return( -1 );
			}
			else
			{
				DWORD iRate;

				TextToSpeechGetRate(phTTS[tts_select], &iRate);
				Speak.iSpeechRate = iRate;
				TextToSpeechGetVolume(phTTS[tts_select], VOLUME_MAIN, &Speak.iVolume);

				return FALSE;
			}

		case WM_SETFOCUS :
			SetFocus(hSpeakText) ;
			return FALSE ;
			
		case WM_SIZE :  //Reposition all child windows when moved or resized
		{
			int iWinHeight = Speak.bmp.bmHeight + 
								GetSystemMetrics(SM_CYCAPTION) + 
								GetSystemMetrics(SM_CYMENU) + 
								GetSystemMetrics(SM_CYSIZEFRAME)*2;
			WINDOWPLACEMENT wndpl;

			memset(&wndpl, 0, sizeof(WINDOWPLACEMENT));
			wndpl.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(hWnd, &wndpl); // address of structure for position data

			if( wndpl.rcNormalPosition.left > 6000 )	// These values are -1 for the upper-left corner and should be 0
				wndpl.rcNormalPosition.left = 0;
			if( wndpl.rcNormalPosition.top > 6000 )
				wndpl.rcNormalPosition.top = 0;

			MoveWindow( hWnd,
				wndpl.rcNormalPosition.left, 
				wndpl.rcNormalPosition.top, 
				Speak.bmp.bmWidth, 
				iWinHeight,
				TRUE);

			// Make the text window fit in the space in the skin bitmap
			MoveWindow( Speak.hSpeakText, 
				15,
				61,
				627,
				295,
				TRUE) ;
			
			for(i=0,x=0; i < NUM_BUTTONS; i++)
			{
				MoveWindow(odButton[i].hWnd,  
					x,
					Speak.bmp.bmHeight - odButton[i].bmp.bmHeight,
					odButton[i].bmp.bmWidth,
					odButton[i].bmp.bmHeight, 
					TRUE );

				x += odButton[i].bmp.bmWidth;
			}
		}
		return FALSE ;
			
		case WM_DROPFILES:
			
			// If edit control has been modified ask to save file .
			if (SendMessage(hSpeakText, EM_GETMODIFY,0L,0L))
				
			{
				if (AskToSave(hWnd))			// returns FALSE is yes or no TRUE if CANCEL
					
					break ;						// Cancel pressed
				// Yes or No pressed
			}
			DragQueryFile ((HDROP)wParam, 0, tsFile, sizeof(tsFile));
			mmStatus = TextToSpeechReset(phTTS[tts_select], FALSE);
			if ( mmStatus )
				MessageBox( hWnd, _T("Error in TTS Reset"), _T("ERROR"), MB_OK | MB_ICONSTOP );
			
			if ( !MyReadFile( hWnd, tsFile ))
			{
				DrawMenuBar( hWnd);
				// reset the title in the title bar to reflect the
				// new open file
				SetWindowTitle(hWnd, tsFile);
				_tcscpy(tsFileSave, tsFile);
				InvalidateRect( hSpeakText, NULL, TRUE );
				DrawMenuBar( hWnd );
				DragFinish ((HDROP)wParam);
				SpeakText ( hWnd );
				return FALSE;
			}
			else
				break;
			
		case WM_DRAWITEM:
			
		case WM_MEASUREITEM:
			DrawControl(hWnd, (LPDRAWITEMSTRUCT)lParam); // Owner draw stuff
			break;
			
		case WM_COMMAND:
			menuCommand(hWnd, wParam, lParam);
			break;
			
		case WM_PAINT:
			BeginPaint(hWnd, &ps);
			BitBlt( Speak.myHdc, 0, 0, Speak.bmp.bmWidth, Speak.bmp.bmHeight, Speak.hMemDC, 0, 0, SRCCOPY );
			EndPaint(hWnd, &ps);
			break ;
			
		case WM_INITMENUPOPUP: /*Enable Paste menu item if clipboard data available*/
			HandleMenuPopup(wParam);
			return FALSE;
			
		case WM_GETMINMAXINFO:   //Limit minimum size of window
			
			lpmmiSize = (LPMINMAXINFO) lParam;
			lpmmiSize->ptMinTrackSize.x = (LONG)etWidth + border * 4 + 4 ;
			lpmmiSize->ptMinTrackSize.y = 300L;
			
			return FALSE;
			
		case WM_ERASEBKGND:
			hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
			hOldBrush = (HBRUSH)SelectObject((HDC)wParam, hBrush);
			GetClientRect(hWnd, &lprc);
			FillRect((HDC)wParam, &lprc, hBrush);
			break;
			
		case WM_CTLCOLORSTATIC:
			hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
			SetBkColor ((HDC) wParam, RGB ((BYTE)192, (BYTE)192, (BYTE)192));
			return  (LRESULT) hBrush;
			
	   /*   This section implements Right Mouse Button click functionality.
		*   This action will cause reading selected text in the Edit Control
		*   Parent notify message is used to check for the right mouse button being activated.
		*   The selected text is then spoken.
		*/
		case WM_PARENTNOTIFY:
			
			if (LOWORD(wParam) == WM_RBUTTONDOWN)
			{
				lSelect = SendMessage (hSpeakText, EM_GETSEL,(WPARAM)&dwStart,(LPARAM)&dwEnd) ;
				
				if (HIWORD (lSelect) == LOWORD (lSelect))
				{
					TCHAR WHAT_STRING[10];
					switch (Speak.current_language)
					{
						case IDM_SPANISH :
						case IDM_ITALIAN:
						case IDM_LATIN :	_tcscpy(WHAT_STRING, _T("qu�?")); break;
						case IDM_GERMAN :	_tcscpy(WHAT_STRING, _T("wie bitte?")); break;
						case IDM_FRENCH :   _tcscpy(WHAT_STRING, _T("ce qui?")); break;
						case IDM_ENGLISH :
						case IDM_ENGLISH_UK :
						default :			_tcscpy(WHAT_STRING, _T("what?")); break;
	
					}
					mmStatus = _TextToSpeechSpeak(phTTS[tts_select], WHAT_STRING, TTS_FORCE, eUtf16);
					if ( mmStatus )
						MessageBox( hWnd, _T("Error in TTS Speak"), _T("ERROR"), MB_OK | MB_ICONSTOP );
					break;
				}
				else
				{

					// Get the text from the edit window
					dwTextLen = SendMessage(hSpeakText, WM_GETTEXTLENGTH, 0, 0);
					lptsEditText  = (TCHAR *)malloc((dwTextLen+1) * sizeof(TCHAR)) ;
					SendMessage(hSpeakText, WM_GETTEXT, (WPARAM)(dwTextLen+1), (LPARAM) lptsEditText);

					// Get the selected text
					lpSelBuf = (TCHAR *)malloc((dwEnd - dwStart + 1)  * sizeof(TCHAR)) ;
					_tcsncpy(lpSelBuf, &lptsEditText[dwStart], (dwEnd - dwStart + 1));
					lpSelBuf[dwEnd - dwStart] = _T('\0');

					if( _TextToSpeechSpeak(phTTS[tts_select], lpSelBuf, TTS_FORCE, eUtf16) != 0 )
						MessageBox( hWnd, _T("Error in TTS Speak"), _T("ERROR"), MB_OK | MB_ICONSTOP );

					free( lpSelBuf );
					free( lptsEditText );
				}
			}
			break;
			
			
		default:
			if (uiMessage ==  uiID_Error_Msg )
				
			{
				//TextToSpeechReset(phTTS[tts_select], FALSE);
				switch (wParam)
				{
					
				case ERROR_IN_AUDIO_WRITE:
					MessageBox(hWnd, _T("Error in Writing Audio"), _T("Async Error"),MB_OK | MB_ICONSTOP);
					break;
					
				case ERROR_OPENING_WAVE_OUTPUT_DEVICE:
					MessageBox(hWnd,
						_T("The wave device is in use by another application \n DECtalk will wait until the device is free."),
						_T("Warning"), MB_OK | MB_ICONSTOP);
					break;
					
				case ERROR_GETTING_DEVICE_CAPABILITIES:
					MessageBox(hWnd, _T("Error Getting Audio Device Caps"), _T("Async Error"),MB_OK | MB_ICONSTOP);
					break;
					
				case ERROR_READING_DICTIONARY:
					MessageBox(hWnd, _T("Error Reading Dictionary File \n dectalk.dic"), _T("Async Error"),MB_OK | MB_ICONSTOP);
					break;
					
				case ERROR_WRITING_FILE:
					MessageBox(hWnd, _T("Error Writing File"), _T("Async Error"),MB_OK | MB_ICONSTOP);
					break;
					
				case ERROR_ALLOCATING_INDEX_MARK_MEMORY:
					MessageBox(hWnd, _T("Error allocating Index Mark Memory"), _T("Async Error"), MB_OK | MB_ICONSTOP);
					break;
					
				case ERROR_OPENING_WAVE_FILE:
					MessageBox(hWnd, _T("Error"), _T("Error Opening Wave File"),MB_OK | MB_ICONSTOP);
					break;
					
				case ERROR_BAD_WAVE_FILE_FORMAT:
					MessageBox(hWnd, _T("Error"), _T("Error Bad Wave File Format"),MB_OK | MB_ICONSTOP);
					break;
					
				case ERROR_UNSUPPORTED_WAVE_FILE_FORMAT:
					MessageBox(hWnd, _T("Error"), _T("Error Unsupported Wave File Format"), MB_OK | MB_ICONSTOP);
					break;
					
				case ERROR_UNSUPPORTED_WAVE_AUDIO_FORMAT:
					MessageBox(hWnd, _T("Error Unsupported Wave Audio Format"), _T(""), MB_OK | MB_ICONSTOP);
					break;
					
				case ERROR_READING_WAVE_FILE:
					MessageBox(hWnd, _T("Error"), _T("Error Reading Wave File"), MB_OK | MB_ICONSTOP);
					break;
				}
			}
			else
				//
				// Process "Find-Replace" Messages
				//
				if( uiMessage == uiMessage_Find_Replace )
				{
					lpfrText = ( LPFINDREPLACE ) lParam;
					
					if( lpfrText->Flags & FR_DIALOGTERM )
						hFind = NULL;
					
					dwOffset = HIWORD( SendMessage( hSpeakText, EM_GETSEL, 0, 0L ));
					if( lpfrText->Flags & FR_FINDNEXT )
						if( !FindSearchString( hSpeakText, &dwOffset, lpfrText ))
						{
							_stprintf( tsError, _T("Search string \"%s\" was not found."), lpfrText->lpstrFindWhat );
							MessageBox( hWnd, tsError, _T("Find Error"), MB_OK | MB_ICONEXCLAMATION );
						}
						
						return( 0 );
				}
				
				return (DefWindowProc (hWnd, uiMessage, wParam, lParam)) ;
				
	}
	return 0L ;
	
}

/*FUNCTION_HEADER**********************
 * NAME:	;WriteSpeechToWave
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void WriteSpeechToWaveFile(HWND hWnd, LPTTS_HANDLE_T phTTS, TCHAR *tsFile, int format)
{
	TCHAR tsError[128];
	MMRESULT mmStatus;
	HCURSOR	hCursor;

	mmStatus = _TextToSpeechOpenWaveOutFile(phTTS, tsFile, format);
	if ( mmStatus )
	{
		_stprintf( tsError, _T("Error = %d"), mmStatus );
		MessageBox( hWnd, tsError, _T("OpenWaveOutFile 16 bit linear"), MB_OK | MB_ICONSTOP );
	}
	hCursor = SetCursor (LoadCursor (NULL, IDC_WAIT));
	ShowCursor (TRUE) ;
	SpeakText(hWnd);
	mmStatus = TextToSpeechCloseWaveOutFile(phTTS);
	if ( mmStatus )
	{
		MessageBox( hWnd, _T("Error in TTS Close Wave File"), _T("ERROR"), MB_OK | MB_ICONSTOP );
	}
	ShowCursor (FALSE) ;
	SetCursor(hCursor) ;
	if( mmStatus )
	{
		_stprintf( tsError, _T("Error = %d"), mmStatus );
		MessageBox( hWnd, tsError, _T("CloseWaveOutFile"), MB_OK | MB_ICONSTOP );
	}

}

/* *******************************************************************
 *      Function Name: menuCommand()
 *
 *      Description:
 *
 *      Arguments:	HWND hWnd
 *					WPARAM wParam
 *					LPARAM lParam
 *
 *      Return Value: BOOL
 *
 *      Comments:
 *
 * *****************************************************************/
BOOL menuCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	TCHAR	
		tsError[132];
	LPTSTR	lptsEditText;
	LPCTSTR lpszHelpFile = _T(DTALK_HELP_FILE_NAME);
	LPCTSTR lpszHelpTopic = _T("Speak applet, overview");
	INT		iLang;
	RECT	lprc;
	MMRESULT mmStatus;
	DWORD 
		dwStart, 
		dwEnd, 
		dwTextLen, 
		iRate;
	LONG lSelect;
	MENUITEMINFO menuinfo;
	HMENU hmenu;
	MENUITEMINFO menu_info;
	
	switch (LOWORD(wParam)) 
	{
		
#ifdef _DEBUG
		case IDM_RESTART:
			TextToSpeechReset(phTTS[tts_select],TRUE);
			TextToSpeechSync(phTTS[tts_select]);
			TextToSpeechShutdown(phTTS[tts_select]);
			TextToSpeechSelectLang(NULL, tts_select);
			TextToSpeechStartupEx(&phTTS[tts_select], WAVE_MAPPER, REPORT_OPEN_ERROR, TTSCallbackRoutine, 0);
			TextToSpeechSetRate(phTTS[tts_select],(UINT)Speak.iSpeechRate);
			break;
#endif
		
		case IDM_HIGHLIGHT:
			highlight = abs(highlight - 1);
			menuinfo.cbSize = sizeof(MENUITEMINFO);
			menuinfo.fMask = MIIM_STATE;
			if (highlight)			menuinfo.fState = MFS_CHECKED;
			else                    menuinfo.fState = 0;
			SetMenuItemInfo(GetMenu(hWnd), IDM_HIGHLIGHT, FALSE, &menuinfo);
			
			break;
		
		case IDM_TYPING:	
			typing_demo(hInst, hWnd);
			break;
		
		case IDM_HELP:
			
			WinHelp( hWnd,
				lpszHelpFile,
				HELP_PARTIALKEY,
				(DWORD)lpszHelpTopic );		  
			break;
			  
		case  IDM_ABOUT:
			
			DialogBox( (HINSTANCE)hInst,
				MAKEINTRESOURCE(DLG_ABOUT),
				hWnd,
				(DLGPROC)AboutDlgProc );
			break;
			  
		case  IDM_FILE_OPEN:
			
			// If edit control has been modified ask to save file .
			if (SendMessage(hSpeakText, EM_GETMODIFY,0L,0L))
			{
				if( AskToSave(hWnd) )			// returns FALSE is yes or no TRUE if CANCEL
					break ;						// Cancel pressed
				// Yes or No pressed
			}
			
			_tcscpy( tsFileSave, tsFile );
			_tcscpy( tsFileTitleSave, tsFileTitle );
			
			if ( MyOpenFile( hWnd, tsFileSave, tsFileTitleSave ) == TRUE )
			{
				_tcscpy( tsFile, tsFileSave );
				_tcscpy( tsFileTitle, tsFileTitleSave );
				DrawMenuBar( hWnd);
				// reset the title in the title bar to reflect the
				// new open file
				SaveSaveAs = FALSE;
				SetWindowTitle(hWnd, tsFile);
				InvalidateRect( hWnd, NULL, TRUE );
				TextToSpeechReset(phTTS[tts_select], FALSE); //Flush out data and reset TTS
			}
			break;
			  
			  
		case IDM_FILE_NEW:
		case IDM_FILE_CLOSE:
			// If edit control has been modified ask to save file .
			if (SendMessage(hSpeakText, EM_GETMODIFY,0L,0L))
			{
				if (AskToSave(hWnd))		// returns FALSE is yes or no TRUE if CANCEL
					break;					// Cancel pressed
			}								// Yes or No pressed
			SetWindowTitle(hWnd, OpenFileName.lpstrFile);
			SendMessage(hSpeakText, EM_SETSEL, (WPARAM)(INT)0L, (LPARAM)(INT)-1L);
			SendMessage(hSpeakText, WM_CLEAR, 0,0L);
			SendMessage(hSpeakText, EM_SETMODIFY, (WPARAM)(INT)FALSE, 0L);
			SaveSaveAs = TRUE;
			return FALSE;
			  
		case IDM_SAVE:
			
			if (SaveSaveAs) 
			{
				if( SaveFileAs(hWnd) )
				{
					SetWindowTitle(hWnd, OpenFileName.lpstrFile);
					_tcscpy(tsFile, OpenFileName.lpstrFile);
					SaveSaveAs = FALSE;
					DrawMenuBar ( hWnd );
				}
				else
					return FALSE ;
			}
			else
			{
				MySaveFile(hWnd);			
			}
			return FALSE ;
			  
		case IDM_SAVEAS:
			
			if( SaveFileAs(hWnd) )
			{
				SetWindowTitle(hWnd, OpenFileName.lpstrFile);
				_tcscpy(tsFile, OpenFileName.lpstrFile);
				DrawMenuBar ( hWnd );
				SaveSaveAs = FALSE;
			}
			
			return FALSE ;
			  
			  
		case IDM_LOAD_DIC:
			
			if (GetDictName( hWnd ) == TRUE )
			{
				TextToSpeechUnloadUserDictionary(phTTS[tts_select]);
				mmStatus = _TextToSpeechLoadUserDictionary(phTTS[tts_select], OpenDictName.lpstrFile) ;
				if ( mmStatus )
				{
					if (mmStatus == MMSYSERR_ERROR)
						
						MessageBox( hWnd,
						_T("Dictionary already loaded or illegal format") ,
						_T("Load User Dictionary"),
						MB_OK | MB_ICONSTOP );
					
					else
						MessageBox( hWnd,
						tsError,
						_T("Load User Dictionary"),
						MB_OK | MB_ICONSTOP );
				}
				break;
			}
			
			break;
			  
		case IDM_UNLOAD_DIC:
			
			mmStatus = TextToSpeechUnloadUserDictionary(phTTS[tts_select]) ;
			if ( mmStatus )
			{
				_stprintf( tsError, _T("Error = %d"), mmStatus );
				
				MessageBox( hWnd,
					tsError,
					_T("Unload User Dictionary"),
					MB_OK | MB_ICONSTOP );
			}
			break;
			  
		case IDM_WAVE1116:	
			if (SaveWaveName ( hWnd ))
			{
				WriteSpeechToWaveFile(hWnd, phTTS[tts_select], OpenWaveName.lpstrFile, WAVE_FORMAT_1M16);
			}
			break;
			  
		case IDM_WAVE1108:
			if (SaveWaveName ( hWnd ) )
			{
				WriteSpeechToWaveFile(hWnd, phTTS[tts_select], OpenWaveName.lpstrFile, WAVE_FORMAT_1M08);
			}
			break;
			  
		case IDM_MULAW:
			if (SaveWaveName ( hWnd ) )
			{
				WriteSpeechToWaveFile(hWnd, phTTS[tts_select], OpenWaveName.lpstrFile, WAVE_FORMAT_08M08);
			}
			break;
			  
			  
		case  IDM_EXIT:
			// If edit control has been modified ask to save file .
			if (SendMessage(hSpeakText, EM_GETMODIFY,0L,0L))
			{
				if (AskToSave(hWnd))        // returns FALSE is yes or no TRUE if CANCEL
					break ;                   // Cancel pressed
				
				DestroyWindow( hWnd );
				break;
			}
			DestroyWindow( hWnd );
			break ;
			  
		case ID_EDIT_CUT:
			SendMessage(hSpeakText,WM_CUT,0,0L);
			break;
			
		case ID_EDIT_COPY:
			SendMessage(hSpeakText,WM_COPY,0,0L);
			break;
			
		case ID_EDIT_PASTE:
			SendMessage(hSpeakText,WM_PASTE,0,0L);
			break;
			
		case ID_EDIT_CLEAR:
			SendMessage(hSpeakText,WM_CLEAR,0,0L);
			break;
			
		case ID_EDIT_SELECT_ALL:
			SendMessage(hSpeakText, EM_SETSEL, (WPARAM)(INT)0L, (LPARAM)(INT)-1L);
			SetFocus(hSpeakText);
			break;
			
		case ID_EDIT_UNDO:
			SendMessage(hSpeakText, EM_UNDO, 0L, 0L);
			break;
			
		case ID_EDIT_PARAMETERS:
			if( DialogBox( (HINSTANCE)hInst, MAKEINTRESOURCE(IDD_DIALOG_PARAMETERS), hWnd, (DLGPROC)ParamsDlgProc ) == 1 )
			{
				// This is a big fat memory leak
				SPDEFS *pSpCur, *pSpLo, *pSpHi, *pSpDef;
				TextToSpeechGetSpeakerParams(phTTS[tts_select], 0, &pSpCur, &pSpLo, &pSpHi, &pSpDef);
				
				pSpCur->loudness = Speak.iVolume;		// This sort-of works but is currently over-driving the volume
				pSpCur->average_pitch = Speak.iPitch;
				TextToSpeechSetSpeakerParams(phTTS[tts_select], pSpCur);
				
				TextToSpeechSetRate(phTTS[tts_select], (UINT)Speak.iSpeechRate);
				
				// This doesn't seem to work
				//TextToSpeechSetVolume(phTTS[tts_select], VOLUME_MAIN, Speak.iVolume);
			}
			break;
			
		case ID_FIND:
			lSelect = SendMessage( hSpeakText, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd );
			if( HIWORD( lSelect ) != LOWORD( lSelect ))
			{
				dwTextLen = SendMessage( hSpeakText, WM_GETTEXTLENGTH, 0, 0);
				lptsEditText = (TCHAR *)malloc((1+dwTextLen) * sizeof( TCHAR ));
				SendMessage(hSpeakText, WM_GETTEXT, (WPARAM) dwTextLen+1, (LPARAM)lptsEditText);
				_tcsncpy(tsFindText, (TCHAR *)&lptsEditText[dwStart], dwEnd - dwStart );
				tsFindText[dwEnd - dwStart] = _T('\0');
				free( lptsEditText );
			}
			hFind = FindDialog( hWnd );
			GetClientRect( hFind, &lprc );
			break;
			  
		case ID_CPANEL:
			TextToSpeechControlPanel(phTTS[tts_select]);
			break;
			// #ifdef ML // we are now using ML stuff as standard setting - NCS 16sept97
			
		case IDM_SHOW_ROMANJI:
			gbShowRomanji = gbShowRomanji ? FALSE : TRUE;
			hmenu=GetMenu(hWnd);
			memset(&menu_info, 0, sizeof(menu_info));
			menu_info.cbSize	= sizeof(menu_info);
			menu_info.fMask	= MIIM_STATE;
			menu_info.fState	= gbShowRomanji ? MFS_CHECKED : MFS_UNCHECKED;
			SetMenuItemInfo(hmenu, IDM_SHOW_ROMANJI, FALSE, &menu_info);
			break;
			
		case ID_EDIT_RESETTTS:
			TextToSpeechReset(phTTS[tts_select],TRUE);
			TextToSpeechSync(phTTS[tts_select]);
			TextToSpeechShutdown(phTTS[tts_select]);
			TextToSpeechSelectLang(NULL, tts_select);
			TextToSpeechStartupEx(&phTTS[tts_select], WAVE_MAPPER, REPORT_OPEN_ERROR, TTSCallbackRoutine, 0);
			TextToSpeechSetRate(phTTS[tts_select],(UINT)Speak.iSpeechRate);
			break;

		case ID_EDIT_PROGRAMMERDEFINED:
			if( Speak.eCurLang == eJapanese )
			{
#if 1
				TranslateJapaneseWordList(phTTS, tts_select, 
					"C:\\TTS\\DecTalk 5.1\\dic\\Japanese\\Dictionaries\\Edict.PrunedCore.WordList.utxt", 
					"C:\\TTS\\DecTalk 5.1\\dic\\Japanese\\Dictionaries\\Edict.PrunedCore.romacc.utxt");
#else
				CompareKanjiKanaTranslation(phTTS, tts_select,
					"C:\\TTS\\DecTalk 5.1\\dic\\Japanese\\JpDict\\edict.wordlist.txt", 
					"C:\\TTS\\DecTalk 5.1\\dic\\Japanese\\Dictionaries\\edict.romacc.nomatch.txt",
					"C:\\TTS\\DecTalk 5.1\\dic\\Japanese\\Dictionaries\\edict.romacc.accnomatch.txt");
#endif
			}
			break;
			
		case IDM_ENGLISH:
		case IDM_FRENCH:
		case IDM_GERMAN:
		case IDM_ITALIAN:
		case IDM_LATIN:
		case IDM_SPANISH:
		case IDM_ENGLISH_UK:
		case IDM_CHINESE:
		case IDM_JAPANESE:
		case IDM_KOREAN:
		case IDM_HEBREW:
			iLang = LOWORD(wParam) - IDM_ENGLISH;
			
			if( Speak.current_language-IDM_ENGLISH == iLang ||
				iLang < 0 || iLang > NUM_TTS_LANGUAGES )
				break;
			
			if( Speak.bTTSOn[iLang] )
			{
				int i, old_lang;
				
				if( (old_lang = Speak.current_language) == 0 )
					old_lang = IDM_ENGLISH;
				
				if( phTTS[tts_select] )
					TextToSpeechShutdown(phTTS[tts_select]);
				
				phTTS[tts_select]=NULL;
				Speak.tts_select = tts_select = Speak.iTTSId[iLang];
				Speak.current_language = IDM_ENGLISH+iLang;
				Speak.eCurLang = (TTS_LANGUAGES)(eEnglish + iLang);
				
				TextToSpeechSelectLang(NULL,tts_select);
				mmStatus = TextToSpeechStartupEx(&phTTS[tts_select], 
					WAVE_MAPPER, REPORT_OPEN_ERROR, TTSCallbackRoutine, 0);
				
				if( mmStatus != MMSYSERR_NOERROR)
				{
					_stprintf(tsError, _T("Error: %d, File: %s, Line: %d\n"), mmStatus, _T(__FILE__), __LINE__);
					if( mmStatus == 11 )
						MessageBox( hWnd, tsError,  _T("Can't Find Dictionary"), MB_OK);
					else
						MessageBox( hWnd, tsError, _T("Can't Start DECtalk"), MB_OK );		
					
					// Revert back to the old language
					iLang = old_lang - IDM_ENGLISH;
					TextToSpeechShutdown(phTTS[tts_select]);
					phTTS[tts_select]=NULL;
					Speak.tts_select = tts_select = Speak.iTTSId[iLang];
					Speak.current_language = IDM_ENGLISH+iLang;
					Speak.eCurLang = (TTS_LANGUAGES)(eEnglish + iLang);
					
					TextToSpeechSelectLang(NULL,tts_select);
					if( TextToSpeechStartupEx(&phTTS[tts_select], WAVE_MAPPER, REPORT_OPEN_ERROR, TTSCallbackRoutine, 0) != 0)
					{
						MessageBox( hWnd, _T("Can't load previous language.  Shutting down."), _T("Error"), MB_OK);
						SendMessage(hWnd, WM_CLOSE, 0, 0);
					}
					
					return(-1);
				}
				
				// Get the default speaking rate
				if( TextToSpeechGetRate(phTTS[tts_select], &iRate) == MMSYSERR_NOERROR )
				{
					Speak.iSpeechRate = iRate;
				}
				
				// extract voice test message from resource
				LoadVoiceNames(&Speak);
				SetLanguageFont(&Speak);
				
				hmenu=GetMenu(hWnd);
				
				// Display the Voice names in the new language
				menu_info.cbSize=sizeof(menu_info);
				menu_info.fType = MFT_STRING;
				menu_info.fMask = MIIM_TYPE;
				for( i=0; i < NUM_TTS_VOICES; i++ )
				{
					menu_info.dwTypeData= Speak.tsVoiceName[i];
					menu_info.cch = _tcslen(Speak.tsVoiceName[i]);
					SetMenuItemInfo(hmenu, ID_VOICE_PAUL+i, FALSE, &menu_info);
				}
				
				// Uncheck current language
				menu_info.cbSize=sizeof(menu_info);
				menu_info.fMask=MIIM_STATE;
				menu_info.fState=MFS_UNCHECKED;
				SetMenuItemInfo(hmenu, old_lang, FALSE, &menu_info);
				
				// Check the new current language
				menu_info.cbSize=sizeof(menu_info);
				menu_info.fMask=MIIM_STATE;
				menu_info.fState=MFS_CHECKED;
				SetMenuItemInfo(hmenu, Speak.current_language, FALSE, &menu_info);
				
				switch(LOWORD(wParam))
				{
					case IDM_CHINESE:
					case IDM_JAPANESE:
					case IDM_KOREAN:
					case IDM_HEBREW:
						EnableMenuItem(hmenu, IDM_SHOW_ROMANJI, MF_ENABLED);
						break;
						
					default:
						gbShowRomanji = FALSE;
						memset(&menu_info, 0, sizeof(menu_info));
						menu_info.cbSize	= sizeof(menu_info);
						menu_info.fMask	= MIIM_STATE;
						menu_info.fState	= MFS_UNCHECKED;
						SetMenuItemInfo(hmenu, IDM_SHOW_ROMANJI, FALSE, &menu_info);
						EnableMenuItem(hmenu, IDM_SHOW_ROMANJI, MF_GRAYED);
						break;
				}

				// Set the current speaker
				if( TextToSpeechSpeak(phTTS[tts_select], Speak.sVoiceCmd[Speak.eCurVoice], TTS_NORMAL) )
					MessageBox( hWnd, _T("Error setting voice") , _T("ERROR"), MB_OK | MB_ICONSTOP );				

				// Say the speakers name
				if( Speak.eCurLang == eKorean )
					_TextToSpeechSpeak(phTTS[tts_select], _T("[:debug tn off]"), TTS_FORCE, eUtf16);	// text normalization off

				if( _TextToSpeechSpeak(phTTS[tts_select], Speak.tsVoiceName[Speak.eCurVoice], TTS_FORCE, eUtf16) )
					MessageBox( hWnd, _T("Error in Speak") , _T("ERROR"), MB_OK | MB_ICONSTOP );

				if( Speak.eCurLang == eKorean )
					_TextToSpeechSpeak(phTTS[tts_select], _T("[:debug tn on]"), TTS_FORCE, eUtf16);	// text normalization on
				
			}
			SetFocus(hSpeakText);
			break;
			  
		case ID_VOICE_PAUL:
		case ID_VOICE_BETTY:
		case ID_VOICE_HARRY:
		case ID_VOICE_FRANK:
		case ID_VOICE_DENNIS:
		case ID_VOICE_KIT:
		case ID_VOICE_URSULA:
		case ID_VOICE_RITA:
		case ID_VOICE_WENDY:
			// Uncheck current voice
			hmenu=GetMenu(hWnd);
			menu_info.cbSize=sizeof(menu_info);
			menu_info.fMask=MIIM_STATE;
			menu_info.fState=MFS_UNCHECKED;
			SetMenuItemInfo(hmenu, Speak.eCurVoice+ID_VOICE_PAUL, FALSE, &menu_info);

			Speak.eCurVoice = (TTS_VOICES)(wParam-ID_VOICE_PAUL);

			if( TextToSpeechSpeak(phTTS[tts_select], Speak.sVoiceCmd[wParam-ID_VOICE_PAUL], TTS_NORMAL) )
				MessageBox( hWnd, _T("Error setting voice") , _T("ERROR"), MB_OK | MB_ICONSTOP );

			if( Speak.eCurLang == eKorean )
				_TextToSpeechSpeak(phTTS[tts_select], _T("[:debug tn off]"), TTS_FORCE, eUtf16);	// text normalization off

			if( _TextToSpeechSpeak(phTTS[tts_select], Speak.tsVoiceName[wParam-ID_VOICE_PAUL], TTS_FORCE, eUtf16) )
				MessageBox( hWnd, _T("Error in Speak") , _T("ERROR"), MB_OK | MB_ICONSTOP );

			if( Speak.eCurLang == eKorean )
				_TextToSpeechSpeak(phTTS[tts_select], _T("[:debug tn on]"), TTS_FORCE, eUtf16);	// text normalization on

			// Check the new current language
			menu_info.cbSize=sizeof(menu_info);
			menu_info.fMask=MIIM_STATE;
			menu_info.fState=MFS_CHECKED;
			SetMenuItemInfo(hmenu, wParam, FALSE, &menu_info);

			SetFocus(hSpeakText);
			break;
			  
	}
	
	return(0);
}

/* *******************************************************************
 *      Function Name: DrawControl()
 *
 *      Description:
 *
 *      Arguments:	HWND hWnd
 *					LPDRAWITEMSTUCT lpInfo
 *
 *      Return Value: INT
 *
 *      Comments:
 *
 * *****************************************************************/
INT DrawControl(HWND hWnd, LPDRAWITEMSTRUCT lpInfo)
{
	INT  i;
	
	for (i=0; i<NUM_BUTTONS; i++)
	{
		if (lpInfo->hwndItem == odButton[i].hWnd) 
		{
			if( lpInfo->itemState & ODS_SELECTED || 
				(i == ePause && Speak.bPaused) )
				SelectObject(odButton[i].hDC, odButton[i].hSelectedBmp);
			else
				SelectObject(odButton[i].hDC, odButton[i].hBitmap);

			break;
		}
	}

	BitBlt(lpInfo->hDC, 0, 0, odButton[i].bmp.bmWidth, odButton[i].bmp.bmHeight,
			odButton[i].hDC, 0, 0, SRCCOPY);

	return(0);
}

/* *******************************************************************
 *      Function Name: SpeakText()
 *
 *      Description:
 *
 *      Arguments:	HWND hWnd
 *
 *      Return Value: BOOL
 *
 *      Comments:
 *
 * *************************************************************** */
BOOL SpeakText( HWND hWnd )
{
	MMRESULT	mmStatus;
	LPTSTR		lptsEditText=NULL;
	TCHAR		tsEditIM[256];
	TCHAR       tsTemp[50];
	TCHAR		tsError[256];
	DWORD		dwTextLen;
	ULONG       ptr = 0;
	ULONG       pos = 0;
	ULONG       mark = 2;
	MARK_POS    *next;
	BOOL        inbracket = FALSE;
	TCHAR		tcPrevchar = _T('\0');
	
	next = mark_pos;
	while( next != NULL ) 
	{
		mark_pos = next->next_mark;
		free(next);
		next = mark_pos;
	}
	
	dwTextLen = SendMessage(hSpeakText, WM_GETTEXTLENGTH, 0, 0);
	dwTextLen++;
	if( (lptsEditText  = (TCHAR *)FNX_CALLOC(dwTextLen, sizeof(TCHAR))) == NULL )
		return FALSE;

	SendMessage(hSpeakText, WM_GETTEXT,(WPARAM) dwTextLen, (LPARAM) lptsEditText);
	
	if (highlight) 
	{
		_tcscpy(tsEditIM, _T("[:i m 1]") );
		ptr = _tcslen(tsEditIM);
		
		next = (MARK_POS *)malloc(sizeof(MARK_POS));
		next->next_mark = NULL;
		mark_pos = next;
		while (pos < _tcslen(lptsEditText)) 
		{
			while( (lptsEditText[pos] == _T(' ') || lptsEditText[pos] == _T('\t') || lptsEditText[pos] == _T('\n'))
				&& ptr < 125 && pos < _tcslen(lptsEditText)) 
			{
				tsEditIM[ptr++] = lptsEditText[pos++];
			}
			next->start = pos;
			while( lptsEditText[pos] != _T(' ') && 
				   lptsEditText[pos] != _T('\n') && 
				   lptsEditText[pos] != _T('\t') &&
				   ptr < 240 && 
				   pos < _tcslen(lptsEditText)) 
			{
				if (lptsEditText[pos] == _T('['))     inbracket = TRUE;
				if (lptsEditText[pos] == _T(']'))     inbracket = FALSE;
				tsEditIM[ptr++] = lptsEditText[pos++];
			}
			if (lptsEditText[pos] == _T(' ') || lptsEditText[pos] == _T('\n') || lptsEditText[pos] == _T('\t')) 
			{
				if (inbracket != TRUE) 
				{
					next->end = pos;
                    /* GL 05/14/1997 BATS#373 fix the table reading problem*/
					tsEditIM[ptr++] = lptsEditText[pos];
					tsEditIM[ptr++] = _T('\0');
					_stprintf(tsTemp, _T(" [:i m %lu]"), mark++);
					ptr += _tcslen(tsTemp) - 1;
					_tcscat(tsEditIM, tsTemp);
					pos++;
					next->next_mark = (MARK_POS *)malloc(sizeof(MARK_POS));
					next = next->next_mark;
					next->next_mark = NULL;
					next->start = pos;
				} 
				else 
				{
					tsEditIM[ptr++] = lptsEditText[pos++];
				}
			}
			// tek 19jun97 try to break and speak at clause bdry..
			if (pos > 3)
			{
				tcPrevchar = lptsEditText[pos-2];
			}
			else
			{
				tcPrevchar = _T('\0');
			}
			if ((ptr > 224) || ( tcPrevchar == _T('.') || tcPrevchar==_T(',') || tcPrevchar==_T('?') || tcPrevchar==_T('!')))
			{
				tsEditIM[ptr++] = _T('\0');

				if( (mmStatus = _TextToSpeechSpeak(phTTS[tts_select], tsEditIM, TTS_NORMAL, eUtf16)) != 0 )
				{
					_stprintf( tsError, _T("Error = %d"), mmStatus );
					MessageBox( hWnd, tsError, _T("TextToSpeechSpeak"), MB_OK | MB_ICONSTOP );
					return TRUE;
				}
				ptr = 0;
			}
		}
	
		if (ptr) 
		{
			tsEditIM[ptr++] = _T('\0');

			if( _TextToSpeechSpeak(phTTS[tts_select], tsEditIM, TTS_NORMAL, eUtf16) != 0 )
			{
				_stprintf( tsError, _T("Error = %d"), mmStatus );
				MessageBox( hWnd, tsError, _T("TextToSpeechSpeak"), MB_OK | MB_ICONSTOP );
				return TRUE;
			}
			ptr = 0;
		}
	  		
		if( (mmStatus = _TextToSpeechSpeak(phTTS[tts_select], _T(""), TTS_FORCE, eUtf16)) != 0 )
		{
			_stprintf( tsError, _T("Error = %d"), mmStatus );
			MessageBox( hWnd, tsError, _T("TextToSpeechSpeak"), MB_OK | MB_ICONSTOP );
			return TRUE;
		}
		
		free(lptsEditText);
		
		if ( mmStatus )
		{
			_stprintf( tsError, _T("Error = %d"), mmStatus );
			MessageBox( hWnd, tsError, _T("TextToSpeechSpeak"), MB_OK | MB_ICONSTOP );
			return TRUE;
		}
	} 
	else 
	{
		int
				iLen,
				nConverted=0,
				nChars;
		char	sText[512];
		TCHAR	tsText[512];

		switch(Speak.eCurLang)
		{
			case eMandarin:
			case eJapanese:
			case eKorean:
				mmStatus = _TextToSpeechSpeak(phTTS[tts_select], lptsEditText, TTS_FORCE, eUtf16);

				if( gbShowRomanji )
				{
					// Get it again because it is no longer unicode
					SendMessage(hSpeakText, WM_GETTEXT,(WPARAM) dwTextLen, (LPARAM) lptsEditText);

					iLen = _tcslen(lptsEditText);

					TextToSpeechSync(phTTS[tts_select]);

					// Clear the current text edit window
					SendMessage(hSpeakText, WM_SETTEXT, (WPARAM)0, (LPARAM)_T(""));
					nConverted = 0;
					while( nConverted < iLen )
					{
						nConverted += TextToSpeechGetRomanizedText( phTTS[tts_select], 
							lptsEditText+nConverted, sText, 128, eUtf16 );
						_mymbstotcs(tsText, sText, 512);

						nChars = GetWindowTextLength(hSpeakText);

						// Concatenate to end of edit window
						SendMessage(hSpeakText, EM_SETSEL, (WPARAM)(INT)nChars, (LPARAM)(INT)-1);
						SendMessage(hSpeakText, EM_REPLACESEL, (WPARAM)0, (LPARAM)tsText);
					}
				}
				break;

			case eHebrew:
				mmStatus = _TextToSpeechSpeak(phTTS[tts_select], lptsEditText, TTS_FORCE, eUtf16);
				break;

			default:
				mmStatus = _TextToSpeechSpeak(phTTS[tts_select], lptsEditText, TTS_FORCE, eUtf16);
				break;
		}


		if ( mmStatus )
			MessageBox( hWnd, _T("Error in TTS Speak"), _T("ERROR"), MB_OK | MB_ICONSTOP );

		if( lptsEditText )
			free(lptsEditText);
		
		if ( mmStatus )
		{
			_stprintf( tsError, _T("Error = %d"), mmStatus );
			MessageBox( hWnd, tsError, _T("TextToSpeechSpeak"), MB_OK | MB_ICONSTOP );
			return TRUE;
		}
	}

	return FALSE;
}

/* *******************************************************************
 *      Function Name: MyOpenFile()
 *
 *      Description: Function to Open a file.
 *
 *      Arguments:	HWND hWnd
 *					char tsFile[]
 *					char tsFileTitle[]
 *
 *      Return Value: LONG
 *
 *      Comments:
 *
 * *****************************************************************/
INT MyOpenFile( HANDLE hWnd, TCHAR tsFile[], TCHAR tsFileTitle[] )
{
	OpenFileName.lStructSize		= sizeof(OPENFILENAME);
	OpenFileName.hwndOwner			= (HWND)hWnd;
	OpenFileName.hInstance			= (HINSTANCE) hInst;
	OpenFileName.lpstrFilter		= szFilter;
	OpenFileName.lpstrCustomFilter	= (LPTSTR) NULL;
	OpenFileName.nMaxCustFilter		= 0L;
	OpenFileName.nFilterIndex		= 1L;
	OpenFileName.lpstrFile			= tsFile;
	OpenFileName.nMaxFile			= 256;
	OpenFileName.lpstrFileTitle		= tsFileTitle;
	OpenFileName.nMaxFileTitle		= 256;
	OpenFileName.lpstrInitialDir	= NULL;
	OpenFileName.lpstrTitle			= _T("Open a File");
	OpenFileName.nFileOffset		= 0;
	OpenFileName.nFileExtension		= 0;
	OpenFileName.lpstrDefExt		= _T("txt");
	OpenFileName.lCustData			= 0;
	OpenFileName.Flags				= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	
	if( GetOpenFileName(&OpenFileName))
	{
		if( !MyReadFile( (HWND)hWnd, OpenFileName.lpstrFile ) )
		{
			return( TRUE );
		}
	}
	else
	{
		ProcessCDError(CommDlgExtendedError(), (HWND)hWnd );
		return( FALSE );
	}
	return( FALSE );
}


/*FUNCTION_HEADER**********************
 * NAME:	;_GetFileSize
 * DESC: 	Get the file size in bytes
 * IN:		tsFile - file name
 * OUT:		none
 * RETURN:	file size in bytes on success, 0 on failure.
 * NOTES:	
 *END_HEADER***************************/
int _GetFileSize(TCHAR *tsFile)
{
	DWORD dwFileSizeHigh =0;
    DWORD dwFileSizeLow = 0;
	DWORD dwError;
	HANDLE hFile;
	
	if( (hFile = CreateFile( tsFile, GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL )) == INVALID_HANDLE_VALUE ) 
	{
		MessageBox( NULL , _T("File open failed."), NULL, MB_OK );
		return( 0 );
	}
	
	dwFileSizeLow = GetFileSize(hFile, &dwFileSizeHigh);
	if( dwFileSizeLow ==	0xFFFFFFFF &&
		(dwError = GetLastError()) != NO_ERROR)
	{
		MessageBox(NULL, _T("GetFileSize is Failed"), _T("Error"),MB_OK|MB_ICONSTOP);
		CloseHandle(hFile);
		return 0;
	}

	CloseHandle(hFile);

	return dwFileSizeLow;

}
/* *******************************************************************
 *      Function Name: MyReadFile()
 *
 *      Description: Function to read file
 *
 *      Arguments:	HWND hWnd
 *					char *tsReadFile
 *
 *      Return Value: int
 *
 *      Comments:
 *
 * *************************************************************** */
int MyReadFile( HWND hWnd, TCHAR *tsReadFile )
{
	unsigned char  
		*sText=NULL; 
	unsigned char 
		c1, 
		c2;
	int
		nRead;
	TCHAR 
		*tsText=NULL;
	DWORD 
		dwFileSize=0;
	FILE 
		*fp=NULL;

	if( (dwFileSize = _GetFileSize(tsReadFile)) == 0 )		// Returns file size in bytes
		return FALSE;
	
	if( (fp = _tfopen(tsReadFile, _T("rb"))) == NULL )
		return FALSE;

	fread(&c1, sizeof(char), 1, fp);
	fread(&c2, sizeof(char), 1, fp);
	if( c1 == 0xFF &&
		c2 == 0xFE )
	{
		// Read a Unicode text file
		if( (tsText = (TCHAR *)FNX_CALLOC(dwFileSize-(sizeof(char)*2), sizeof(BYTE))) == NULL )
		{
			goto MyReadFileErr;
		}

		if( fread(tsText, sizeof(BYTE), dwFileSize, fp) == 0 )
		{
			goto MyReadFileErr;
		}
	}
	else
	{
		// Read a non-Unicode text file
		fseek(fp, 0L, SEEK_SET);
		if( (sText = (unsigned char *)FNX_CALLOC(dwFileSize+1, sizeof(BYTE))) == NULL )
		{
			goto MyReadFileErr;
		}

		if( fread(sText, sizeof(BYTE), dwFileSize, fp) == 0 )
		{
			goto MyReadFileErr;
		}
		if( (tsText = (TCHAR *)FNX_CALLOC(dwFileSize+1, sizeof(TCHAR))) == NULL )
		{
			goto MyReadFileErr;
		}

		switch( Speak.eCurLang )
		{
			case eJapanese:		// If it's not unicode then Japanese input must be SJis
				nRead = Sjis2Utf(sText, tsText, dwFileSize);
				break;
			case eKorean:		// If it's not unicode then Korean input must be KSC
				nRead = Ksc2Utf(sText, tsText, dwFileSize);
				break;
			case eMandarin:		// If it's not unicode then Chinese input must be GBK
				nRead = Gbk2Utf(sText, tsText, dwFileSize);
				break;
			default:
				_mymbstotcs(tsText, (const char *)sText, dwFileSize);
				break;

		}
	}

	// display text in edit window
	SendMessage(hSpeakText, WM_SETTEXT, 0, (LPARAM)tsText);

	if( fp )		fclose(fp);
	if( tsText )	free(tsText);
	if( sText )		free( sText );

	return TRUE;

MyReadFileErr:
	if( fp )		fclose(fp);
	if( tsText )	free(tsText);
	if( sText )		free( sText );
	return FALSE;


}

/* *******************************************************************
 *      Function Name: AskToSave()
 *
 *      Description: Puts up a Message box asking to save - yes, no or cancel
 *
 *      Arguments:	HWND hWnd
 *
 *      Return Value: BOOL
 *						TRUE  -  Cancel button pushed
 *						FALSE -  Yes or No pushed
 *      Comments:
 *
 * *****************************************************************/
BOOL AskToSave( HWND hWnd )
{
	int iResponse ;
	TCHAR szBuf[128];
	
	iResponse = MessageBox(hWnd,
		_T("The Text in this file has changed. \n\n Do you wish to save the changes?"),
		tsAppName ,  MB_YESNOCANCEL | MB_ICONEXCLAMATION )  ;
	switch (iResponse)
	{
	case IDYES:
		
		GetWindowText( hWnd, szBuf, 30) ;
		if( _tcscmp(szBuf,  tsAppName) == 0)
		{
			if (!SaveFileAs ( hWnd ))
				return TRUE;
			return FALSE;
		}
		else
		{
			MySaveFile ( hWnd ) ;
			return FALSE ;
		}
		break;
		
	case IDCANCEL:
		return TRUE;
		break;
		
	case IDNO:
		return FALSE ;
		break;
	}
	
	
	return TRUE;
}

/* *******************************************************************
 *      Function Name: GetDictName()
 *
 *      Description: Function to get dictionary name
 *
 *      Arguments:	HWND hWnd
 *
 *      Return Value: BOOL
 *
 *      Comments:
 *
 * *****************************************************************/
BOOL GetDictName( HWND hWnd )
{
	TCHAR szDictFilter[] = _T("Dictionary Files (*.DIC)\0*.DIC\0All Files (*.*)\0*.*\0");
	static TCHAR szDict[256];
	static TCHAR szDictTitle[256];
	_tcscpy( szDict, _T(""));
	_tcscpy( szDictTitle, _T(""));
		
	OpenDictName.lStructSize		= sizeof(OPENFILENAME);
	OpenDictName.hwndOwner			= hWnd;
	OpenDictName.hInstance			= (HINSTANCE) hInst;
	OpenDictName.lpstrFilter		= szDictFilter;
	OpenDictName.lpstrCustomFilter	= (LPTSTR) NULL;
	OpenDictName.nMaxCustFilter		= 0L;
	OpenDictName.nFilterIndex		= 1L;
	OpenDictName.lpstrFile			= szDict;
	OpenDictName.nMaxFile			= 256;
	OpenDictName.lpstrFileTitle		= szDictTitle;
	OpenDictName.nMaxFileTitle		= 256;
	OpenDictName.lpstrInitialDir	= NULL;
	OpenDictName.lpstrTitle			= _T("Load a Dictionary");
	OpenDictName.nFileOffset		= 0;
	OpenDictName.nFileExtension		= 0;
	OpenDictName.lpstrDefExt		= _T("dic");
	OpenDictName.lCustData			= 0;
	OpenDictName.Flags				= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	
	if ( GetOpenFileName(&OpenDictName))
		return TRUE;
	else
	{
		ProcessCDError(CommDlgExtendedError(), hWnd );
	}
	return( FALSE );
}


/* *******************************************************************
 *      Function Name: npVoiceControls()
 *
 *      Description:	
 *
 *      Arguments:	HWND hWnd
 *					UINT msg
 *					WPARAM wParam
 *					LPARAM lParam
 *
 *      Return Value: LRESULT CALLBACK
 *
 *      Comments:
 *
 * *****************************************************************/
LRESULT CALLBACK npVoiceControls(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	MMRESULT mmStatus;
	int ret=0;
	
	switch(msg)
	{
		case WM_LBUTTONUP:
			if (hWnd == odButton[ePlay].hWnd)
			{
				SpeakText( hWnd );
				SetFocus(hSpeakText);
			}
			
			if (hWnd == odButton[ePause].hWnd)
			{
				if ( !Speak.bPaused )
				{
					if ( TextToSpeechPause( phTTS[tts_select] ) == MMSYSERR_NOERROR )
						
					{
						SetFocus(hSpeakText);		/* GL 01/15/1997, move into {} */
						Speak.bPaused = TRUE;
					}
				}
				else
				{
					if ( TextToSpeechResume( phTTS[tts_select] ) == MMSYSERR_NOERROR )
					{
						SetFocus(hSpeakText);		/* GL 01/15/1997, move into {} */
						Speak.bPaused = FALSE;
					}
				}
			}
			
			if (hWnd == odButton[eStop].hWnd)
			{
				mmStatus = TextToSpeechReset( phTTS[tts_select], FALSE );
				if ( mmStatus )	
					MessageBox( hWnd, _T("Error in TTS Reset"), _T("ERROR"), MB_OK | MB_ICONSTOP );

				SetFocus(hSpeakText);
			}
			
#if 0 //def _DEBUG
			if (hWnd == odButton[eReset].hWnd)
			{
				TextToSpeechReset(phTTS[tts_select],TRUE);
				TextToSpeechSync(phTTS[tts_select]);
				TextToSpeechShutdown(phTTS[tts_select]);
				TextToSpeechSelectLang(NULL, tts_select);
				ret=TextToSpeechStartupEx(&phTTS[tts_select], WAVE_MAPPER, REPORT_OPEN_ERROR, TTSCallbackRoutine, 0);
				Sleep(1);
				TextToSpeechSetRate(phTTS[tts_select],(UINT)Speak.iSpeechRate);
			}
#endif
			
		default:
			return CallWindowProc (opVoiceControls, hWnd, msg, wParam, lParam);
	}
}

/* *******************************************************************
 *      Function Name: AboutDlgProc()
 *
 *		Author: Bill Hallahan
 *		Date: October 5, 1994
 *
 *      Description: This dialog procedure is for the about box.
 *
 *      Arguments:	HWND hWnd		Handle to window
 *					UINT uiMsg		Message being sent to the window.
 *					WPARAM wParam	Specific argument to message.
 *					LPARAM lParam	Specific argument to message.
 *
 *      Return Value: BOOL APIENTRY
 *						The return value is specific to the message that was
 *						received. It is FALSE if this dialog procedure does not handle
 *						a message (an exception is the WM_INITDIALOG message where
 *						TRUE is always returned).
 *      Comments:
 *
 * *****************************************************************/
#define MAX_STRING 512

BOOL APIENTRY AboutDlgProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam )
{
	HWND hDlgItem;
	TCHAR *pString;
	TCHAR tsInstaller[MAX_STRING];
	TCHAR tsCompany[MAX_STRING];
	
	switch( uiMsg )
	{
	case WM_RBUTTONUP:
		//easter_egg();
		return 0;
		
	case WM_INITDIALOG:
		
		/******************************************************************/
		/*  Display some OS version information.                          */
		/******************************************************************/
		
		pString = (LPTSTR)malloc( MAX_STRING * sizeof(TCHAR));
		
		if ( pString == NULL )
		{
			MessageBox( hWnd, _T("Out of Memory"), _T("Error"), MB_OK );
			return( TRUE );
		}
		
		AppGetWindowsVersion( pString, NULL );
		hDlgItem = GetDlgItem( hWnd, IDD_ABOUT_VERSION_OS );
		SetWindowText( hDlgItem, pString );
		
		AppGetWindowsVersion( NULL, pString );
		hDlgItem = GetDlgItem( hWnd, IDD_ABOUT_VERSION_PLATFORM );
		SetWindowText( hDlgItem, pString );
		
		/******************************************************************/
		/*  Get the installer name and company.                           */
		/******************************************************************/
		
		GetInstallationInfo( tsInstaller, tsCompany );
		
		AppGetWindowsVersion( NULL, pString );
		hDlgItem = GetDlgItem( hWnd, IDD_ABOUT_REG_INSTALLER );
		SetWindowText( hDlgItem, tsInstaller );
		
		AppGetWindowsVersion( NULL, pString );
		hDlgItem = GetDlgItem( hWnd, IDD_ABOUT_REG_COMPANY );
		SetWindowText( hDlgItem, tsCompany );
		
		/******************************************************************/
		/* Display the version of DECtalk DLL file                        */
		/******************************************************************/
		_stprintf(pString, _T("%d.%02d (%s)"), DECtalk_maj_ver, DECtalk_min_ver, DECtalk_Debug ? _T("Debug") : _T("Release") );
		hDlgItem = GetDlgItem( hWnd, IDD_ABOUT_DECTALK_VERSION );
		SetWindowText( hDlgItem, pString );
		
		hDlgItem = GetDlgItem( hWnd, IDD_ABOUT_DECTALK_VERSION_STR );
		SetWindowText( hDlgItem, tsDECtalk_version );

		_stprintf(pString, _T("Build Date: %S"), __TIMESTAMP__ );
		SetWindowText(GetDlgItem(hWnd, IDC_STATIC_BUILD_DATE), pString);
		
		free( pString );
		
		return( TRUE );
		
	case WM_COMMAND:
		
		if ( LOWORD( wParam ) == IDOK || LOWORD( wParam ) == IDCANCEL )
		{
			EndDialog( hWnd, ( IDOK == LOWORD( wParam )));
		}
		break;
		
	default:
		
		break;
	}
	return( FALSE );
}


/* *******************************************************************
 *      Function Name: MySaveFile()
 *
 *      Description: Saves current contents of edit control to current filename.
 *
 *      Arguments:	HWND hWnd
 *
 *      Return Value: BOOL
 *						TRUE - The file was saved successfully
 *						FALSE - The file was not saved
 *
 *      Comments:
 *
 * *****************************************************************/
BOOL MySaveFile( HWND hWnd)
{
	int		iTextLen=0;
	char	c;
	TCHAR	*tsText;
	FILE	*fp;

	if( (fp = _tfopen(tsFile, _T("wb"))) == NULL )
		return FALSE;

	if( (iTextLen = GetWindowTextLength(hSpeakText)) == 0) 
	{
		fclose(fp);
		return FALSE;
	}

	iTextLen++;
	if( (tsText = (TCHAR *)FNX_CALLOC(iTextLen, sizeof(TCHAR))) == NULL )
	{
		fclose(fp);
		return FALSE;
	}

	SendMessage(hSpeakText, WM_GETTEXT, iTextLen, (LPARAM)tsText );

#ifdef UNICODE
	c = (char)0xFF;
	fwrite(&c, 1, sizeof(char), fp);
	c = (char)0xFE;
	fwrite(&c, 1, sizeof(char), fp);
#endif

	fwrite(tsText, iTextLen, sizeof(TCHAR), fp);

	fclose(fp);
	free(tsText);

	SendMessage(hSpeakText, EM_SETMODIFY, (WPARAM)(INT)FALSE, 0L);
	return TRUE;
}

/* *******************************************************************
 *      Function Name: SaveFileAs()
 *
 *      Description: Saves current contents of edit control to new filename.
 *
 *      Arguments:	HWND hWnd
 *
 *      Return Value: BOOL
 *						TRUE - The file was saved successfully
 *						FALSE - The file was not saved
 *
 *      Comments:
 *
 * *****************************************************************/
BOOL SaveFileAs( HWND hWnd)
{	
	_tcscpy( tsFile, _T(""));
	_tcscpy( tsFileTitle, _T(""));
	
	OpenFileName.lStructSize       = sizeof(OPENFILENAME);
	OpenFileName.hwndOwner         = hWnd;
	OpenFileName.hInstance         = (HINSTANCE) hInst;
	OpenFileName.lpstrFilter       = szFilter;
	OpenFileName.lpstrCustomFilter = (LPTSTR) NULL;
	OpenFileName.nMaxCustFilter    = 0L;
	OpenFileName.nFilterIndex      = 1L;
	OpenFileName.lpstrFile         = tsFile;
	OpenFileName.nMaxFile          = sizeof(tsFile);
	OpenFileName.lpstrFileTitle    = tsFileTitle;
	OpenFileName.nMaxFileTitle     = sizeof(tsFileTitle);
	OpenFileName.lpstrInitialDir   = NULL;
	OpenFileName.lpstrTitle        = _T("Save File As");
	OpenFileName.nFileOffset       = 0;
	OpenFileName.nFileExtension    = 0;
	OpenFileName.lpstrDefExt       = _T("txt");
	OpenFileName.lCustData         = 0;
	OpenFileName.Flags             = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_CREATEPROMPT | OFN_HIDEREADONLY;
	OpenFileName.lpfnHook          = (LPOFNHOOKPROC) (FARPROC) NULL;
	OpenFileName.lpTemplateName    = (LPTSTR) NULL;
	
	if (GetSaveFileName(&OpenFileName))
		return MySaveFile( hWnd ) ;
	else	
	{
		ProcessCDError(CommDlgExtendedError(), hWnd );
		return FALSE;
	}
}

/* *******************************************************************
 *      Function Name: SaveWaveName()
 *
 *      Description: Gets filename for Wave out to file.
 *
 *      Arguments:	HWND hWnd
 *
 *      Return Value: BOOL
 *						TRUE - The filename was retrieved
 *						FALSE - The filename was not retreived
 *
 *      Comments: This function fills in the OpenWaveName OPENFILENAME Structure
 *
 * *****************************************************************/
BOOL SaveWaveName( HWND hWnd )
{	
	OpenWaveName.lStructSize       = sizeof(OPENFILENAME);
	OpenWaveName.hwndOwner         = hWnd;
	OpenWaveName.hInstance         = (HINSTANCE) hInst;
	OpenWaveName.lpstrFilter       = szWaveFilter;
	OpenWaveName.lpstrCustomFilter = (LPTSTR) NULL;
	OpenWaveName.nMaxCustFilter    = 0L;
	OpenWaveName.nFilterIndex      = 1L;
	OpenWaveName.lpstrFile         = szWaveFile;
	OpenWaveName.nMaxFile          = sizeof(szWaveFile);
	OpenWaveName.lpstrFileTitle    = szWaveFileTitle;
	OpenWaveName.nMaxFileTitle     = sizeof(szWaveFileTitle);
	OpenWaveName.lpstrInitialDir   = NULL;
	OpenWaveName.lpstrTitle        = _T("Convert to Wave File");
	OpenWaveName.nFileOffset       = 0;
	OpenWaveName.nFileExtension    = 0;
	OpenWaveName.lpstrDefExt       = _T("wav");
	OpenWaveName.lCustData         = 0;
	OpenWaveName.Flags             = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_CREATEPROMPT |
		OFN_HIDEREADONLY ;
	OpenWaveName.lpfnHook          = (LPOFNHOOKPROC) (FARPROC) NULL ;
	OpenWaveName.lpTemplateName    = (LPTSTR) NULL ;
	
	
	
	if (GetSaveFileName(&OpenWaveName))
		return TRUE ;
	else
		
	{
		ProcessCDError(CommDlgExtendedError(), hWnd ) ;
		return FALSE ;
		
	}
	
}

/* *******************************************************************
 *      Function Name: ProcessCDError()
 *
 *      Description: Processes errors from the common dialog functions.
 *
 *      Arguments:	HWND hWnd
 *
 *      Return Value: void
 *
 *      Comments:	This function is called whenever a common dialog function
 *					fails. The CommonDialogExtendedError() value is passed to
 *					the function which maps the error value to a string table.
 *					The string is loaded and displayed for the user.
 *
 * *****************************************************************/
void ProcessCDError(DWORD dwErrorCode, HWND hWnd)
{
	WORD  wStringID;
	TCHAR  buf[256];
	
	switch(dwErrorCode)
	{
	case CDERR_DIALOGFAILURE:   wStringID=IDS_DIALOGFAILURE;   break;
	case CDERR_STRUCTSIZE:      wStringID=IDS_STRUCTSIZE;      break;
	case CDERR_INITIALIZATION:  wStringID=IDS_INITIALIZATION;  break;
	case CDERR_NOTEMPLATE:      wStringID=IDS_NOTEMPLATE;      break;
	case CDERR_NOHINSTANCE:     wStringID=IDS_NOHINSTANCE;     break;
	case CDERR_LOADSTRFAILURE:  wStringID=IDS_LOADSTRFAILURE;  break;
	case CDERR_FINDRESFAILURE:  wStringID=IDS_FINDRESFAILURE;  break;
	case CDERR_LOADRESFAILURE:  wStringID=IDS_LOADRESFAILURE;  break;
	case CDERR_LOCKRESFAILURE:  wStringID=IDS_LOCKRESFAILURE;  break;
	case CDERR_MEMALLOCFAILURE: wStringID=IDS_MEMALLOCFAILURE; break;
	case CDERR_MEMLOCKFAILURE:  wStringID=IDS_MEMLOCKFAILURE;  break;
	case CDERR_NOHOOK:          wStringID=IDS_NOHOOK;          break;
	case PDERR_SETUPFAILURE:    wStringID=IDS_SETUPFAILURE;    break;
	case PDERR_PARSEFAILURE:    wStringID=IDS_PARSEFAILURE;    break;
	case PDERR_RETDEFFAILURE:   wStringID=IDS_RETDEFFAILURE;   break;
	case PDERR_LOADDRVFAILURE:  wStringID=IDS_LOADDRVFAILURE;  break;
	case PDERR_GETDEVMODEFAIL:  wStringID=IDS_GETDEVMODEFAIL;  break;
	case PDERR_INITFAILURE:     wStringID=IDS_INITFAILURE;     break;
	case PDERR_NODEVICES:       wStringID=IDS_NODEVICES;       break;
	case PDERR_NODEFAULTPRN:    wStringID=IDS_NODEFAULTPRN;    break;
	case PDERR_DNDMMISMATCH:    wStringID=IDS_DNDMMISMATCH;    break;
	case PDERR_CREATEICFAILURE: wStringID=IDS_CREATEICFAILURE; break;
	case PDERR_PRINTERNOTFOUND: wStringID=IDS_PRINTERNOTFOUND; break;
	case CFERR_NOFONTS:         wStringID=IDS_NOFONTS;         break;
	case FNERR_SUBCLASSFAILURE: wStringID=IDS_SUBCLASSFAILURE; break;
	case FNERR_INVALIDFILENAME: wStringID=IDS_INVALIDFILENAME; break;
	case FNERR_BUFFERTOOSMALL:  wStringID=IDS_BUFFERTOOSMALL;  break;
		
	case 0:   //User may have hit CANCEL or we got a *very* random error
		return;
		
	default:
		wStringID=IDS_UNKNOWNERROR;
	}
	
	LoadString(NULL, wStringID, buf, sizeof(buf));
	MessageBox(hWnd, buf, NULL, MB_OK);
	return;
}

/* *******************************************************************
 *      Function Name: HandleMenuPopup()
 *
 *      Description: Handle Edit menu popup logic
 *
 *      Arguments:	WPARAM wParam
 *
 *      Return Value: void
 *
 *      Comments:	This function is called whenever a common dialog function
 *					fails. The CommonDialogExtendedError() value is passed to
 *					the function which maps the error value to a string table.
 *					The string is loaded and displayed for the user.
 *
 * *****************************************************************/
void HandleMenuPopup(WPARAM wParam)
{
	LONG lSelect;
	WORD wEnable;
	INT iLen;

	if ( IsClipboardFormatAvailable( CF_TEXT ))
		EnableMenuItem((HMENU)wParam, ID_EDIT_PASTE, MF_ENABLED);
	else
		EnableMenuItem((HMENU)wParam, ID_EDIT_PASTE, MF_GRAYED);
	
	/*Enable  menu cut, copy & delete menu items if data is selected */
	
	lSelect = SendMessage (hSpeakText, EM_GETSEL, 0L, 0L) ;
	
	if (HIWORD (lSelect) != LOWORD (lSelect))
		wEnable= MF_ENABLED;
	else
		wEnable= MF_GRAYED;
	
	EnableMenuItem ((HMENU)wParam, ID_EDIT_CUT, wEnable);
	EnableMenuItem ((HMENU)wParam, ID_EDIT_COPY, wEnable);
	EnableMenuItem ((HMENU)wParam, ID_EDIT_CLEAR, wEnable);
	iLen = GetWindowTextLength( hSpeakText );
	
	if (iLen == 0)
	{
		EnableMenuItem((HMENU)wParam, IDM_SAVE, MF_GRAYED);
		EnableMenuItem((HMENU)wParam, IDM_SAVEAS, MF_GRAYED);
	}
	
	else
	{
		EnableMenuItem((HMENU)wParam, IDM_SAVE, MF_ENABLED);
		EnableMenuItem((HMENU)wParam, IDM_SAVEAS, MF_ENABLED);
	}
	if (SendMessage(hSpeakText, EM_CANUNDO, 0L, 0L))
		EnableMenuItem((HMENU)wParam, ID_EDIT_UNDO, MF_ENABLED);
	else
		EnableMenuItem((HMENU)wParam, ID_EDIT_UNDO, MF_GRAYED);
	
	return ;
}

/* *******************************************************************
 *      Function Name:	FindDialog()
 *
 *      Description:
 *
 *      Arguments:	HWND hWnd
 *
 *      Return Value: HWND
 *
 *      Comments:
 *
 * *****************************************************************/
HWND FindDialog( HWND hWnd )
{
	static FINDREPLACE frText;
	
	frText.lStructSize      = sizeof( FINDREPLACE );
	frText.hwndOwner        = hWnd;
	frText.hInstance        = NULL;
	frText.Flags			= FR_DOWN | ! FR_WHOLEWORD | ! FR_MATCHCASE;
	frText.lpstrFindWhat    = tsFindText;
	frText.lpstrReplaceWith = NULL;
	frText.wFindWhatLen     = sizeof( tsFindText );
	frText.wReplaceWithLen  = 0;
	frText.lCustData        = 0;
	frText.lpfnHook			= NULL;
	frText.lpTemplateName   = NULL;
	
	return( FindText( &frText ));
}

/* *******************************************************************
 *      Function Name:	FindNextText()
 *
 *      Description:
 *
 *      Arguments:	HWND hWnd
 *					DWORD *lpdwSearchOffSet
 *
 *      Return Value: BOOL
 *
 *      Comments:
 *
 * *****************************************************************/
BOOL FindNextText( HWND hSearch, DWORD *lpdwSearchOffset )
{
	FINDREPLACE frText;
	
	frText.lpstrFindWhat = tsFindText;
	
	return( FindSearchString( hSearch, lpdwSearchOffset, &frText ));
}

/* *******************************************************************
 *      Function Name:	FindSearchString()
 *
 *      Description: Find a string
 *
 *      Arguments:	HWND hSearch
 *					DWORD *lpdwSearchOffSet
 *					LPFINDEREPLACE lpfr
 *
 *      Return Value: BOOL
 *						TRUE - Found
 *						FALSE - Not Found
 *      Comments:
 *
 * *****************************************************************/
BOOL FindSearchString( HWND hSearch, DWORD *lpdwSearchOffset, LPFINDREPLACE lpfr )
{
	DWORD   dwPos;
	LPTSTR   lpstrDoc, lpstrPos, lpstrFind, lpstrPtr;
	BOOL    bFind = TRUE;
	static TCHAR szAlphabet[] = {_T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")};
	LRESULT	lResult;
	
	/* Retrieve the data from the edit box  (KSB 7/22/96) */
	lResult  = SendMessage(hSpeakText, WM_GETTEXTLENGTH, 0 ,0 ) ;
	if( (lpstrDoc = (LPTSTR)malloc((lResult+1)*sizeof(TCHAR))) == NULL) 
	{
		return FALSE;
	}
	lpstrPtr = lpstrDoc;
	SendMessage(hSpeakText, WM_GETTEXT, lResult + 1, (LPARAM)lpstrDoc );
	
	//
	// Set the string for up/down searching, make a copy of the strings we search
	// so that the original string on the screen doesn't get munged.
	//
	if (lpfr->Flags & FR_DOWN) 
	{
		lpstrFind = _tcsdup(lpfr->lpstrFindWhat);
	} 
	else 
	{
		lpstrFind = _tcsrev(_tcsdup(lpfr->lpstrFindWhat));
		_tcsrev(lpstrDoc);
	}
	
	*lpdwSearchOffset = *lpdwSearchOffset;
	
	//
	// Search the document for the find string
	//
	while( bFind )
	{
		if( lpfr->Flags & FR_MATCHCASE )
			lpstrPos = _tcsstr( lpstrDoc + *lpdwSearchOffset, lpstrFind );
		else
			lpstrPos = _tcsstr( CharLower(lpstrDoc) + *lpdwSearchOffset, CharLower(lpstrFind));
		
		if( lpfr->Flags & FR_WHOLEWORD )
		{
			//
			// If there are no words matched, then quit looking for one
			//
			if( lpstrPos == NULL )
			{
				bFind = FALSE;
			} 
			else 
			{
				//
				// if the string was matched, let's see if the next character will make
				// an exact match.  Note, any letter in the alphabet immediately after the last
				// character matched will cause this exact match to fail.
				//
				if(!_tcsspn((lpstrPos + _tcslen(lpstrFind)), szAlphabet))
				{
					bFind = FALSE;
				} else {
					//
					// Find the current position in the document and the new start offset
					//
					dwPos = lpstrPos - lpstrDoc;
					*lpdwSearchOffset = dwPos + _tcslen( lpstrFind );
				}
			}
		} else {
			bFind = FALSE;
		}
	}
	
	//
	// Return an error code if the string cannot be found
	//
	if( lpstrPos == NULL ) 
	{
		free(lpstrPtr);
		return( FALSE );
	}
	
	//
	// Find the current position in the document and the new start offset
	// Don't forget, we might have done this in the UP direction.
	//
	dwPos = ( lpfr->Flags & FR_DOWN ) ? lpstrPos - lpstrDoc
		: _tcslen(lpstrDoc) - (lpstrPos - lpstrDoc) - _tcslen( lpstrFind );
	*lpdwSearchOffset = dwPos + _tcslen( lpfr->lpstrFindWhat );
	
	//
	// Select the found text
	//
	SendMessage( hSearch, EM_SETSEL, dwPos, *lpdwSearchOffset );
	SendMessage( hSearch, EM_SCROLLCARET, 0L, 0L );
	SetFocus( hFind );
	free(lpstrPtr);
	return( TRUE );
}

/* *******************************************************************
 *      Function Name:	FindValidText()
 *
 *      Description:
 *
 *      Arguments:	void
 *
 *      Return Value: BOOL
 *
 *      Comments:
 *
 * *****************************************************************/
BOOL FindValidFind( void )
{
	return( *tsFindText != '\0' );
}

/* *******************************************************************
 *      Function Name: AppGetWindowsVersion()
 *
 *      Description:	This function returns the version of Windows that the application
 *						is running on plus some platform information.
 *
 *      Arguments:	PTSTR pszEnvirnoment	Options pointer to buffer to receive text string of windows version.
 *					PTSTR pszPlatform		Opitons pointer to buffer to receive text string of platform.
 *
 *      Return Value: LRESULT _stdcall
 *						The return value will be the version and platform information of
 *						the current operating system in the following format:
 *
 *						0xPPPPMMRR where:
 *						MM:   major version of Windows
 *						RR:   minor version (revision) of Windows
 *						PPPP:   the platform the application is running on which
 *								will be one of the following:
 *
 *						#ifdef WIN32
 *							the HIWORD() is RESERVED except for the high bit:
 *							high bit is 0 = Windows NT
 *							high bit is 1 = Win32s/Windows 3.1
 *						#else
 *							0xMMRR = Major and Minor version of [MS-]DOS
 *							GetWinFlags() & 0x8000 = Windows on OS/2 (WLO)
 *							GetWinFlags() & 0x4000 = Windows on Windows NT (WOW)
 *						#endif
 *
 *      Comments:
 *
 * *****************************************************************/
LRESULT _stdcall AppGetWindowsVersion( PTSTR pszEnvironment, PTSTR pszPlatform )
{
	LRESULT lr;
	OSVERSIONINFO  OSVersionInfo;
	
	OSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&OSVersionInfo);
	
	// Dummy return value 
	lr = OSVersionInfo.dwPlatformId;
	//
	//  if caller wants the environment string version...
	//
	if (NULL != pszEnvironment)
	{

#ifdef WIN32
		{
			static TCHAR    szFormatVersion[]   = TEXT("%s Version %u.%.2u");
			static TCHAR    szEnvWinNT[]        = TEXT("Windows NT");
			static TCHAR    szEnvWin95[]        = TEXT("Windows 95");
			static TCHAR    szEnvWin32s[]       = TEXT("Win32s");
			TCHAR			szPlatform[15];
			
			switch(OSVersionInfo.dwPlatformId) 
			{
			case VER_PLATFORM_WIN32s:
				_tcscpy(szPlatform,szEnvWin32s);
				break;
			case VER_PLATFORM_WIN32_WINDOWS:
				_tcscpy(szPlatform,szEnvWin95);
				break;
			case VER_PLATFORM_WIN32_NT:
				_tcscpy(szPlatform,szEnvWinNT);
				break;
			}
			
			wsprintf(pszEnvironment, szFormatVersion,
				(LPSTR)(szPlatform),
				OSVersionInfo.dwMajorVersion, 
				OSVersionInfo.dwMinorVersion);
		}
#else
		{
#ifndef WF_WINNT
#define WF_WINNT        0x4000
#define WF_WLO          0x8000
#endif // WIN32

#ifndef WF_CPUMASK
#define WF_CPUMASK      0xFC000000
#define WF_CPU_X86      0
#define WF_CPU_R4000    1
#define WF_CPU_ALPHA    2
#define WF_CPU_CLIPPER  3
#endif
			
			static TCHAR    szFormatSubSys[]= TEXT("Windows Version %u.%.2u (%s%s)\n%s Subsystem, DOS Version %u.%.2u");
			static TCHAR    szFormatDOS[]   = TEXT("Windows Version %u.%.2u (%s%s)\nDOS Version %u.%.2u");
			static TCHAR    szSubSysWLO[]   = TEXT("WLO");
			static TCHAR    szSubSysWOW[]   = TEXT("WOW");
			static TCHAR    szModeEnhanced[]= TEXT("Enhanced");
			static TCHAR    szModeStandard[]= TEXT("Standard");
			static TCHAR    szEnvPaging[]   = TEXT(", Paging");
			
			DWORD   dwWinFlags;
			PTSTR   pszMode;
			
			BYTE    bVerEnvMajor    = HIBYTE(LOWORD(uVerEnv));
			BYTE    bVerEnvMinor    = LOBYTE(LOWORD(uVerEnv));
			
			dwWinFlags = GetWinFlags();
			
			pszMode = (dwWinFlags & WF_ENHANCED) ? szModeEnhanced : szModeStandard;
			if (dwWinFlags & (WF_WLO | WF_WINNT))
			{
				wsprintf(pszEnvironment, szFormatSubSys, bVerWinMajor, bVerWinMinor,
					(LPSTR)pszMode,
					(LPSTR)((dwWinFlags & WF_PAGING) ? szEnvPaging : gszNull),
					(LPSTR)((dwWinFlags & WF_WINNT) ? szSubSysWOW : szSubSysWLO),
					bVerEnvMajor, bVerEnvMinor);
			}
			else
			{
				wsprintf(pszEnvironment, szFormatDOS, bVerWinMajor, bVerWinMinor,
					(LPSTR)pszMode,
					(LPSTR)((dwWinFlags & WF_PAGING) ? szEnvPaging : gszNull),
					bVerEnvMajor, bVerEnvMinor);
			}
		}
#endif
	}
	
	//
	//  if caller wants the platform string version...
	//
	if (NULL != pszPlatform)
	{
#ifdef WIN32
		{
			static TCHAR    szFormatPlatform[]  = TEXT("%s%u, %u Processor(s)");
			static TCHAR    szProcessorIntel[]  = TEXT("Intel ");
			static TCHAR    szProcessorMIPS[]   = TEXT("MIPS R");
			static TCHAR    szProcessorAlpha[]  = TEXT("DEC Alpha ");
			static TCHAR    szProcessorDunno[]  = TEXT("Dunno zYz");
			
			SYSTEM_INFO sysinfo;
			PTSTR       pszProcessor;
			
			//
			//  this is absolutely silly. one would think that the dwOemId member
			//  would provide something useful like the processor class... but
			//  no, it doesn't--it is always 0.
			//
			GetSystemInfo(&sysinfo);
			switch (sysinfo.wProcessorArchitecture)
			{
			case PROCESSOR_ARCHITECTURE_INTEL:
				pszProcessor = szProcessorIntel;
				break;
				
			case PROCESSOR_ARCHITECTURE_MIPS:
				pszProcessor = szProcessorMIPS;
				break;
				
			case PROCESSOR_ARCHITECTURE_ALPHA:
				pszProcessor = szProcessorAlpha;
				break;
				
			default:
				pszProcessor = szProcessorDunno;
				break;
			}
			
			//
			//
			//
			wsprintf(pszPlatform, szFormatPlatform, (LPSTR)pszProcessor,
				sysinfo.dwProcessorType, sysinfo.dwNumberOfProcessors);
		}
#else
		{
			static TCHAR    szPlat286[]         = TEXT("80286");
			static TCHAR    szPlat386[]         = TEXT("80386");
			static TCHAR    szPlat486[]         = TEXT("i486");
			static TCHAR    szPlatR4000[]       = TEXT("MIPS R4000, Emulation: ");
			static TCHAR    szPlatAlpha21064[]  = TEXT("Alpha 21064, Emulation: ");
			static TCHAR    szPlatClipper[]     = TEXT("Clipper, Emulation: ");
			static TCHAR    szPlat80x87[]       = TEXT(", 80x87");
			
			DWORD   dwWinFlags;
			
			dwWinFlags = GetWinFlags();
			pszPlatform[0] = '\0';
			
			if (dwWinFlags & (WF_WLO | WF_WINNT))
			{
				switch ((dwWinFlags & WF_CPUMASK) >> 26)
				{
				case WF_CPU_X86:
					break;
					
				case WF_CPU_R4000:
					lstrcpy(pszPlatform, szPlatR4000);
					break;
					
				case WF_CPU_ALPHA:
					lstrcpy(pszPlatform, szPlatAlpha21064);
					break;
					
				case WF_CPU_CLIPPER:
					lstrcpy(pszPlatform, szPlatClipper);
					break;
				}
			}
			
			if (dwWinFlags & WF_CPU286)
				lstrcat(pszPlatform, szPlat286);
			else if (dwWinFlags & WF_CPU386)
				lstrcat(pszPlatform, szPlat386);
			else if (dwWinFlags & WF_CPU486)
				lstrcat(pszPlatform, szPlat486);
			
			if (dwWinFlags & WF_80x87)
				lstrcat(pszPlatform, szPlat80x87);
		}
#endif
	}
	
	//
	//  return the result
	//
	return (lr);
}

/* *******************************************************************
 *      Function Name:	GetInstallationInfo()
 *		Author: Bill Hallahan
 *		Date: October 5, 1994
 *
 *      Description: This function gets the installer name and company from the
 *					 registry.
 *
 *      Arguments:	LPSTR tsInstaller	A pointer to a string that will contain the
 *										name provided during installation.         
 *										The returned value will be NULL terminated.
 *                                                              
 *					LPSTR tsCompany     A pointer to a string that will contain the
 *										company name provided during installation. 
 *										The returned value will be NULL terminated.
 *
 *      Return Value: static void
 *
 *      Comments:
 *
 * *****************************************************************/
static void GetInstallationInfo( LPTSTR tsInstaller, LPTSTR tsCompany )
{
	HKEY  hKey;
	DWORD dwType;
	DWORD cbData;
	TCHAR tsText[512];
	
	_mymbstotcs(tsText, szLocalMachineDECtalk, 512);
	tsText[strlen(szLocalMachineDECtalk) - 3] = _T('\0'); // chop off /GR, /LA, /SP, /UK, /US, etc.
	
	if ( RegOpenKeyEx( HKEY_LOCAL_MACHINE, tsText, 0, KEY_QUERY_VALUE, &hKey ) != ERROR_SUCCESS )
	{
		tsInstaller[0] = _T('\0');
		tsCompany[0] = _T('\0');
	}
	else
	{
		cbData = 511;
		
		if ( RegQueryValueEx( hKey, _T("Installer"), NULL, &dwType, (LPBYTE)tsInstaller, &cbData ) != ERROR_SUCCESS )
		{
			tsInstaller[0] = _T('\0');
		}
		
		cbData = 511;
		
		if ( RegQueryValueEx( hKey, _T("Company"), NULL, &dwType, (LPBYTE)tsCompany, &cbData ) != ERROR_SUCCESS )
		{
			tsCompany[0] = _T('\0');
		}
		
		RegCloseKey( hKey );
	}
	
	return;
}

/* *******************************************************************
 *      Function Name:	GetApplicationParameters()
 *		Author: Bill Hallahan
 *		Date: October 6, 1994
 *
 *      Description:	This function gets the last window position and show state
 *						in the registry.
 *
 *      Arguments:	int piX			A pointer to an integer that will contain the
 *									X (horizontal) position of the application window.                                                                      
 *					int piY			A pointer to an integer that will contain the 
 *									Y (vertical) position of the application window.                                                     
 *					int piWidth		A pointer to an integer that will contain the 
 *									width of the application window.                               
 *					int piHeight	A pointer to an integer that will contain the 
 *									height of the application window.                           
 *					int piShow		A pointer to an integer that will contain the
 *									show state of the window.                           
 *					char ptsFile    A pointer to memory that will contain a NULL  
 *									terminated string of characters. It must be at
 *									least FILESIZE bytes.                         
 *
 *      Return Value: static void
 *
 *      Comments:
 *
 * *****************************************************************/
static void GetApplicationParameters( int * piX, int * piY, int * piWidth,int * piHeight,
									  int * piShow, TCHAR *ptsFile )
{
	TCHAR tsText[_MAX_PATH];
	HKEY  hKey;
	DWORD dwType;
	DWORD cbData;
	DWORD dwXY;
	DWORD dwWH;
	
	/********************************************************************/
	/*  Open the registry for the application.                          */
	/********************************************************************/

	_mymbstotcs(tsText, szCurrentUsersSpeak, _MAX_PATH);
	if ( RegOpenKeyEx( HKEY_CURRENT_USER, tsText, 0, KEY_QUERY_VALUE, &hKey ) != ERROR_SUCCESS )
	{
		/******************************************************************/
		/*  If the key is not accessible then use default values.         */
		/******************************************************************/
		
		*piShow = SW_SHOWNORMAL;
		*piX = 0;
		*piY = 0;
		*piWidth = awWidth;
		*piHeight = awHeight;
		*ptsFile = _T('\0');
	}
	else
	{
		/******************************************************************/
		/*  Read the former window SHOW state.                            */
		/******************************************************************/
		
		cbData = 4;
		if ( RegQueryValueEx( hKey, _T("Show"), NULL, &dwType, (LPBYTE)piShow, &cbData ) != ERROR_SUCCESS )
		{
			*piShow = SW_SHOWNORMAL;
		}
		
		/******************************************************************/
		/*  Read the former window X and Y positions.                     */
		/******************************************************************/
		
		cbData = 4;
		if ( RegQueryValueEx( hKey, _T("Position"), NULL, &dwType, (LPBYTE)&dwXY, &cbData ) != ERROR_SUCCESS )
		{
			*piX = 0;
			*piY = 0;
		}
		else
		{
			*piX = dwXY & 0xFFFF;
			*piY = ( dwXY >> 16 ) & 0xFFFF;
			
			if ( *piX > 32767 )
				*piX = 0;
			
			if ( *piY > 32767 )
				*piY = 0;
		}
		
		/******************************************************************/
		/*  Read the former window width and height.                      */
		/******************************************************************/
		
		cbData = 4;
		
		if ( RegQueryValueEx( hKey, _T("Size"), NULL, &dwType, (LPBYTE)&dwWH, &cbData ) != ERROR_SUCCESS )
		{
			*piWidth = awWidth;
			*piHeight = awHeight;
		}
		else
		{
			*piWidth = dwWH & 0xFFFF;
			*piHeight = ( dwWH >> 16 ) & 0xFFFF;
			
			if ( *piWidth > 32767 )
				*piWidth = awWidth;
			
			if ( *piHeight > 32767 )
				*piHeight = awHeight;
		}
		
		/******************************************************************/
		/*  Read the former file title.                                   */
		/******************************************************************/
		
		cbData = FILESIZE;
		
		if ( RegQueryValueEx( hKey, _T("File"), NULL, &dwType, (LPBYTE)ptsFile, &cbData ) != ERROR_SUCCESS )
		{
			*ptsFile = _T('\0');
		}
		
		/******************************************************************/
		/*  Close the registry.                                           */
		/******************************************************************/
		
		RegCloseKey( hKey );
	}
	
	return;
}

/* *******************************************************************
 *      Function Name:	SetApplicationParameters()
 *		Author: Bill Hallahan
 *		Date: October 6, 1994
 *
 *      Description:	This function sets the last window position and show state
 *						in the registry.
 *
 *      Arguments:	HWND hwnd	A handle to the application window
 *                                                              
 *					ptsFile		A pointer to memory that contains a NULL
 *								terminated string of characters.
 *
 *      Return Value: static void
 *
 *      Comments:
 *
 * *****************************************************************/
static void SetApplicationParameters( HWND hWnd, TCHAR *ptsFile )
{
	TCHAR tsText[_MAX_PATH];
	int iX;
	int iY;
	int iWidth;
	int iHeight;
	int iShow;
	HKEY hKey;
	DWORD cbData;
	DWORD dwXY;
	DWORD dwWH;
	DWORD dwDisposition;
	WINDOWPLACEMENT WindowPlacement;
	

	/********************************************************************/
	/*  Open the registry for the application.                          */
	/********************************************************************/
	_mymbstotcs(tsText, szCurrentUsersSpeak, _MAX_PATH);

	if ( RegOpenKeyEx( HKEY_CURRENT_USER, tsText, 0, KEY_ALL_ACCESS, &hKey ) != ERROR_SUCCESS )
	{
		/******************************************************************/
		/*  The specified key was NOT found in the registry. Create       */
		/*  the registry entries.                                         */
		/******************************************************************/
		
		if ( RegCreateKeyEx( HKEY_CURRENT_USER,
			tsText,
			0,
			_T(""),
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,
			NULL,
			&hKey,
			&dwDisposition ) != ERROR_SUCCESS )
		{
			/****************************************************************/
			/*  Unable to update registry entries. Exit with no error.      */
			/****************************************************************/
			
			return;
		}
	}
	
	/********************************************************************/
	/*  Set the registry entries for the window placement data.         */
	/********************************************************************/
	
	WindowPlacement.length = sizeof(WINDOWPLACEMENT);
	
	if ( GetWindowPlacement( hWnd, &WindowPlacement ))
	{
		cbData = 4;
		iShow = WindowPlacement.showCmd;
		
		RegSetValueEx( hKey, _T("Show"), 0, REG_DWORD, (LPBYTE)&iShow, sizeof( DWORD ));
		
		/******************************************************************/
		/*  Set the registry entries for the window X and Y coordinates.  */
		/******************************************************************/
		
		iX = WindowPlacement.rcNormalPosition.left;
		iY = WindowPlacement.rcNormalPosition.top;
		dwXY = ( iY << 16 ) + iX;
		cbData = 4;
		
		RegSetValueEx( hKey, _T("Position"), 0, REG_DWORD, (LPBYTE)&dwXY, sizeof( DWORD ));
		
		/******************************************************************/
		/*  Set the registry entries for the window width and height.     */
		/******************************************************************/
		
		iWidth = WindowPlacement.rcNormalPosition.right
			- WindowPlacement.rcNormalPosition.left;
		
		iHeight = WindowPlacement.rcNormalPosition.bottom
			- WindowPlacement.rcNormalPosition.top;
		
		dwWH = ( iHeight << 16 ) + iWidth;
		
		cbData = 4;
		
		RegSetValueEx( hKey, _T("Size"), 0, REG_DWORD, (LPBYTE)&dwWH, sizeof( DWORD ));
	}
	
	/********************************************************************/
	/*  Set the registry entry for the current file title.              */
	/********************************************************************/
	
	RegSetValueEx( hKey, _T("File"), 0, REG_SZ, (LPBYTE)ptsFile, 1 + _tcslen( ptsFile ));
	
	/********************************************************************/
	/*  Close the registry.                                             */
	/********************************************************************/
	
	RegCloseKey( hKey );

	return;
}

/* *******************************************************************
 *      Function Name:	CheckVersion()
 *		Author: Kevin Bruckert
 *
 *      Description:	This function will check the version of the DECTALK.DLL file for
 *						functionality validation.
 *
 *      Arguments:	void
 *                                                              
 *      Return Value: BOOL
 *						TRUE  - Version OK
 *						FALSE - Version BAD
 *
 *      Comments:
 *
 * *****************************************************************/
BOOL CheckVersion(void)
{
	ULONG version;
	
	version = _TextToSpeechVersion(&tsDECtalk_version);
	
	if (version & 0x80000000)	
		DECtalk_Debug = TRUE;
	else
		DECtalk_Debug = FALSE;

	DECtalk_maj_ver = (version & 0x7F000000) >> 24;
	DECtalk_min_ver = (version & 0x00FF0000) >> 16;
	DECtalk_compute = (version & 0x0000FF00) >> 8;
	DECtalk_build	= (version & 0x000000FF);
	
	gbTyping = TRUE;
	gbHilite = TRUE;
	return TRUE;
}

/* *******************************************************************
 *      Function Name:	CmdParse()
 *
 *      Description:	Parse command line arguments
 *
 *      Arguments:	LPSTR CmdLine - Command Line List
 *					LPSTR filename - String for file name
 *					LPSTR dictname - Dictionary name
 *                                                              
 *      Return Value: BOOL
 *						0 for continue
 *						1 for program exit
 *
 *      Comments:
 *
 * *****************************************************************/
BOOL CmdParse(LPSTR sCmdLine, LPTSTR tsFilename, LPTSTR tsDictname)
{
	char	sFilename[_MAX_PATH],
			sDictname[_MAX_PATH],
			*psTok;
	TCHAR	tsLang[32];
	
	if( sCmdLine == NULL || strlen(sCmdLine) == 0)	
		return 0;			// Don't parse if no parameters
	
	tsLang[0] = 0x00;
	sFilename[0] = sDictname[0] = 0x00;
	psTok = strtok(sCmdLine, " \r\n");
	while( psTok )
	{
		if( *psTok == '/' )
		{
			switch( *(psTok+1) )
			{
			case 'd':
				if( (psTok = strtok(NULL, " \r\n")) != NULL )
				{
					strcpy(sDictname, psTok);
				}
				break;
			case 'f':
				if( (psTok = strtok(NULL, " \r\n")) != NULL )
				{
					strcpy(sFilename, psTok);
				}
				break;
			case 'l':
				if( (psTok = strtok(NULL, " \r\n")) != NULL )
				{
					_mymbstotcs(tsLang, psTok, 32);
				}
				break;

			case '?':
				MessageBox( NULL, _T("Usage: Speak /l <lang> /f [test filename] /d [user dictionary name] [/?]"), _T("Usage of Speak"), MB_OK);
				return 1;
			}
		}
		psTok = strtok(NULL, " \r\n");
	}

	if( tsLang[0] )
	{
		int i,
			nLangs = sizeof(gtsLang)/sizeof(char*);

		for(i=0; i<nLangs; i++)
		{
			if( _tcsicmp(gtsLang[i], tsLang) == 0 )
			{
				geStartupLang = (TTS_LANGUAGES)i;
			}
		}

	}

	if( tsFilename && sFilename[0] )
		_mymbstotcs(tsFilename, sFilename, _MAX_PATH);

	if( tsDictname && sDictname[0] )
		_mymbstotcs(tsDictname, sDictname, _MAX_PATH);

	return 0;
}


/* ******************************************************************
 *      Function Name:	TTSCallbackRoutine()
 *
 *      Description:
 *
 *      Arguments:	LONG lParam1
 *					LONG lParam2
 *					DWORD dwInstanceParam
 *					UNINT uiMsg
 *
 *      Return Value: VOID
 *
 *      Comments:
 *
 * *****************************************************************/
VOID TTSCallbackRoutine(LONG lParam1, LONG lParam2, DWORD dwInstanceParam, UINT uiMsg)
{	
	switch( lParam1 )
	{
		case TTS_INDEX_MARK:
			update_mark(lParam2);
			break;
		case TTS_AUDIO_PLAY_STOP:
			update_mark(0xFFFFFFFF);
			break;
		case TTS_AUDIO_PLAY_START:
		case ERROR_OPENING_WAVE_OUTPUT_DEVICE:
		case ERROR_IN_AUDIO_WRITE:
		case ERROR_GETTING_DEVICE_CAPABILITIES:
			break;
		default:
			break;
	}
}

/* ******************************************************************
 *      Function Name:	update_mark()
 *
 *      Description:
 *
 *      Arguments:	ULONG mark
 *
 *      Return Value: void
 *
 *      Comments:
 *
 * *****************************************************************/
void update_mark(ULONG mark)
{
	MARK_POS *next = mark_pos;
	ULONG pos;
	
	if (mark == 0xFFFFFFFFL) 
	{
		PostMessage(DECtalkSpeakWin, EM_SETSEL, (WPARAM)-1, (LPARAM) 0);
		PostMessage(DECtalkSpeakWin, EM_SCROLLCARET, (WPARAM) 0, (LPARAM) 0);
		return;
	}
	
	if (next == NULL)       
		return;
	
	for (pos = 1; pos < mark; pos++) 
	{
		if (next->next_mark == NULL)    
			return;
		next = next->next_mark;
	}
	if( highlight ) 
	{
		PostMessage(DECtalkSpeakWin, EM_SETSEL, (WPARAM)next->start, (LPARAM) next->end);
		PostMessage(DECtalkSpeakWin, EM_SCROLLCARET, (WPARAM) 0, (LPARAM) 0);
	}
	return;
}

/* ******************************************************************
 *      Function Name:	typing_demo()
 *
 *      Description:
 *
 *      Arguments:	HANDLE hinst
 *					HWND hWnd
 *
 *      Return Value: void
 *
 *      Comments:
 *
 * *****************************************************************/
void typing_demo(HANDLE hinst, HWND hWnd)
{
	DialogBox( (HINSTANCE)hInst, MAKEINTRESOURCE(IDD_TYPING),
			   hWnd, (DLGPROC)AboutTypingProc );
	return;
}

/* ******************************************************************
 *      Function Name:	AboutTypingProc()
 *
 *      Description:
 *
 *      Arguments:	HWND hWnd
 *					UNIT uiMsg
 *					WAPARAM wParam
 *					LPARAM lParam
 *
 *      Return Value: BOOL APIENTRY
 *
 *      Comments:
 *
 * *****************************************************************/
BOOL APIENTRY AboutTypingProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam )
{
	HWND hDlgItem;
	
	switch( uiMsg )
	{
	case WM_INITDIALOG:
		hDlgItem = GetDlgItem(hWnd, IDC_EDIT1);
		OldTypingDlgProc = (WNDPROC)GetWindowLong(hDlgItem, GWL_WNDPROC);
		SetWindowLong(hDlgItem, GWL_WNDPROC, (LONG) TypingDlgProc);
		
		_TextToSpeechSpeak(phTTS[tts_select], _T("[:ra 350]Ready to speak. [:say letter]"), TTS_NORMAL, eUtf16);
		return( TRUE );
		
	case WM_COMMAND:
		if ( LOWORD( wParam ) == IDOK )
		{
			TextToSpeechReset(phTTS[tts_select],TRUE);
			_TextToSpeechSpeak(phTTS[tts_select], _T("Thank you."), TTS_FORCE, eUtf16);
			TextToSpeechSetRate(phTTS[tts_select], (UINT)Speak.iSpeechRate);
			EndDialog( hWnd, ( IDOK == LOWORD( wParam )));
		}
		break;
		
	default:
		break;
	}
	return( FALSE );
}

/* ******************************************************************
 *      Function Name:	TypingDlgProc()
 *
 *      Description:
 *
 *      Arguments:	HWND hWnd
 *					UNIT uiMsg
 *					WAPARAM wParam
 *					LPARAM lParam
 *
 *      Return Value: BOOL APIENTRY
 *
 *      Comments:
 *
 * *****************************************************************/
BOOL APIENTRY TypingDlgProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam )
{
	//	HWND hDlgItem;
	switch( uiMsg )
	{
		case WM_CHAR:
			_TextToSpeechTyping(phTTS[tts_select], wParam);
			break;
		case WM_COMMAND:
			if ( LOWORD( wParam ) == IDOK )
			{
				EndDialog( hWnd, ( IDOK == LOWORD( wParam )));
			}
			break;		
	}
	return CallWindowProc(OldTypingDlgProc, hWnd, uiMsg, wParam, lParam);
}
