/*H_HEADER_FILE***************************************************************
FILE			: SPEAK.H
DESC			: 
TABS			: 3
OWNER			: 
DATE CREATED: 

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.



*END_HEADER******************************************************************/
#ifndef	SPEAK_H
#define	SPEAK_H

//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <commdlg.h>
#include <commctrl.h>
#include <mmsystem.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ttsapi.h"

// Help context value
#define IDH_Speak_Program_Applet_Index  51

typedef    POINTS MPOINT;

#ifdef WIN32
#define GET_WM_ACTIVATE_STATE(wp, lp)   LOWORD(wp)
#define GET_WM_VSCROLL_CODE(wp, lp)     LOWORD(wp)
#define GET_WM_VSCROLL_POS(wp, lp)      HIWORD(wp)
#define GET_WM_HSCROLL_CODE(wp, lp)     LOWORD(wp)
#define GET_WM_HSCROLL_POS(wp, lp)      HIWORD(wp)
#define GET_EM_SETSEL_MPS(iStart, iEnd) (UINT)(iStart), (LONG)(iEnd)
#define GET_WM_COMMAND_CMD(wp, lp)      HIWORD(wp)
#define MAKEMPOINT(l)                   (*((MPOINT *)&(l)))
#define HUGE_T
#else
#define GET_WM_ACTIVATE_STATE(wp, lp)               (wp)
#define GET_WM_HSCROLL_CODE(wp, lp)                 (wp)
#define GET_WM_HSCROLL_POS(wp, lp)                  LOWORD(lp)
#define GET_WM_VSCROLL_CODE(wp, lp)                 (wp)
#define GET_WM_VSCROLL_POS(wp, lp)                  LOWORD(lp)
#define GET_EM_SETSEL_MPS(iStart, iEnd) 0, MAKELONG(iStart, iEnd)
#define GET_WM_COMMAND_CMD(wp, lp)      HIWORD(lp)
#define MAKEMPOINT(l)                   (*((MPOINT FAR *)&(l)))
#define HUGE_T         huge
#endif

/* Macro to restrict a given value to an upper or lower boundary value */
#define BOUND(x,min,max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

/* Macro to swap two values */
#define SWAP(x,y)   ((x)^=(y)^=(x)^=(y))

/* Macro to find the minimum of two values */
#define MIN(x,y) (((x) <= (y)) : x ? y)

/* Macros to display/remove hourglass cursor for lengthy operations */
#define StartWait() hcurSave = SetCursor(LoadCursor(NULL,IDC_WAIT))
#define EndWait()   SetCursor(hcurSave)

/* WinFlags, __WinFlags is a ABS external, thus the need for the & */
#define WinFlags    ((WORD)(&_WinFlags))

#define MINBAND         50     /* Minimum band size used by the program */
#define BANDINCREMENT   20     /* Decrement for band size while trying  */
			       /* to determine optimum band size.       */

#ifdef NOT_IN_STDIO
/* flags for _lseek */
#define  SEEK_CUR 1
#define  SEEK_END 2
#define  SEEK_SET 0
#endif

extern HWND hWndApp;                   /* The handle to the app. window     */

#define MAXREAD  32768                 /* Number of bytes to be read during */
				       /* each read operation.              */
/* Macro to align given value to the closest DWORD (unsigned long ) */
#define ALIGNULONG(i)   ((i+3)/4*4)

/* Macro to determine to round off the given value to the closest byte */
#define WIDTHBYTES(i)   ((i+31)/32*4)

#define PALVERSION      0x300
#define MAXPALETTE      256       /* max. # supported palette entries */

/***************** ERROR CODES *************************/

#define IDS_DIALOGFAILURE     1
#define IDS_STRUCTSIZE        2
#define IDS_INITIALIZATION    3
#define IDS_NOTEMPLATE        4
#define IDS_NOHINSTANCE       5
#define IDS_LOADSTRFAILURE    6
#define IDS_FINDRESFAILURE    7
#define IDS_LOADRESFAILURE    8
#define IDS_LOCKRESFAILURE    9
#define IDS_MEMALLOCFAILURE  10
#define IDS_MEMLOCKFAILURE   11
#define IDS_NOHOOK           12
#define IDS_SETUPFAILURE     13
#define IDS_PARSEFAILURE     14
#define IDS_RETDEFFAILURE    15
#define IDS_LOADDRVFAILURE   16
#define IDS_GETDEVMODEFAIL   17
#define IDS_INITFAILURE      18
#define IDS_NODEVICES        19
#define IDS_NODEFAULTPRN     20
#define IDS_DNDMMISMATCH     21
#define IDS_CREATEICFAILURE  22
#define IDS_PRINTERNOTFOUND  23
#define IDS_NOFONTS          24
#define IDS_SUBCLASSFAILURE  25
#define IDS_INVALIDFILENAME  26
#define IDS_BUFFERTOOSMALL   27
#define IDS_FILTERSTRING     28
#define IDS_UNKNOWNERROR     29

// Speaking Rate nominal and boundries
#define	SPEAK_RATE	200
#define RATE_MAX	600
#define RATE_MIN	 50

#define VOLUME_DEF   70
#define VOLUME_MIN	  0
#define VOLUME_MAX   87

#define PITCH_DEF   110
#define PITCH_MIN    50
#define PITCH_MAX	350


typedef enum {
	ePlay=0,
	ePause,
	eStop,
#ifdef _DEBUG
//	eReset,
#endif
	NUM_BUTTONS
} BUTTONS_ENUM;

typedef enum {
	eEnglish=0,
	eFrench,
	eGerman,
	eItalian,
	eLatin,
	eSpanish,
	eUKEnglish,
	eMandarin,
	eJapanese,
	eKorean,
	eHebrew,
	NUM_TTS_LANGUAGES
} TTS_LANGUAGES;

typedef enum {
	ePaul=0,
	eBetty,
	eHarry,
	eFrank,
	eDennis,
	eKit,
	eUrsula,
	eRita,
	eWendy,
	NUM_TTS_VOICES
} TTS_VOICES;

typedef struct _tagOwnerDraw {
	HWND hWnd;
	LPBITMAPFILEHEADER  lpbfNormalDib;
	LPBITMAPFILEHEADER  lpbfSelectedDib;
	HBITMAP	hBitmap,
			hSelectedBmp;
	BITMAP	bmp;
	HDC		hDC;

} OWNERDRAW;

typedef struct mark_pos_struct {
	ULONG start;
	ULONG end;
	struct mark_pos_struct *next_mark;
} MARK_POS;

/***************** GLOBAL VARIABLES *************************/

extern CHAR           achFileName[128]; /* File pathname                       */

#define MAX_VOICE_NAME_SIZE	24
#define MAX_VOICE_CMD_SIZE	12

typedef struct _tagSpeak
{
	TTS_LANGUAGES	eCurLang;
	TTS_VOICES		eCurVoice;
	char			sVoiceCmd[NUM_TTS_VOICES][MAX_VOICE_CMD_SIZE];
	TCHAR			tsVoiceName[NUM_TTS_VOICES][MAX_VOICE_NAME_SIZE];
	SPDEFS			*pSpDefs;					// Default speaker parameters
	
	char			sOrderFile[_MAX_PATH],
					sDemoFile[_MAX_PATH],
					sCmdFile[_MAX_PATH],
					sEmailFile[_MAX_PATH];

	LPTTS_HANDLE_T	phTTS[NUM_TTS_LANGUAGES];
	unsigned int	tts_select;
	int				current_language;
	int				current_voice;

	unsigned int	iTTSId[NUM_TTS_LANGUAGES];	// Id for each TTS Language
	BOOL			bTTSOn[NUM_TTS_LANGUAGES];	// Is this language turned on?
	int				nLang;						// Number of languages
	BOOL			bPaused;					// TRUE means Paused

	int				iSpeechRate,
					iPitch,
					iVolume;

	HDC				myHdc;
	HWND			hWndApp;
	HWND			hVolume, hRate, hstRate, hstRateLabel, hSpeakText, hDigital, hFind;
	HBITMAP			hSkinBmp;
	BITMAP			bmp;
	HDC				hMemDC;
	HFONT			hFont;

	ULONG			speak_mark;
	unsigned int	DECtalk_maj_ver, DECtalk_min_ver, DECtalk_build;
	LPSTR			DECtalk_version;

}SPEAK;

/***************** FUNCTION DECLARATIONS *******************/
LPVOID           findHdib(INT id);
INT              usePalette(HWND hWnd, TCHAR* szPalResName);
DWORD   PASCAL   lread(INT fh, VOID FAR *pv, DWORD ul);
DWORD   PASCAL   lwrite(INT fh, VOID FAR *pv, DWORD ul);
BOOL    CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
LONG    APIENTRY WndProc  (HWND, UINT, UINT, LONG) ;
BOOL             menuCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
INT              DrawControl(HWND hWnd, LPDRAWITEMSTRUCT lpInfo);
BOOL             InitFirstInstance(HANDLE);
void             DrawAuthor(HWND hWnd);

BOOL             fDialog (INT id, HWND hwnd, FARPROC fpfn);
BOOL APIENTRY AboutDlgProc( HWND hWnd, UINT uiMessage, UINT wParam, LONG lParam);
void             ErrorHandler( HANDLE, CHAR *, CHAR * );
LRESULT CALLBACK npVoiceControls (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT              MyOpenFile( HANDLE, TCHAR *, TCHAR * );
int              MyReadFile( HWND, TCHAR * );
void             ScrollProc(HWND hWnd, WPARAM wParam, LPARAM lParam, INT *nHscrollPos);
INT              ErrMsg (PSTR sz,...);
void             ProcessCDError(DWORD, HWND );
void             HandleMenuPopup(WPARAM wParam);
SHORT            HandleScrollBar(WPARAM,SHORT);
BOOL             SaveWaveName(HWND);
BOOL             SaveFile(HWND);
BOOL             SaveFileAs(HWND);
BOOL             GetDictName(HWND);
BOOL             AskToSave(HWND);
BOOL             SpeakText(HWND);
HWND             FindDialog( HWND );
BOOL             FindSearchString( HWND, DWORD *, LPFINDREPLACE );
BOOL             FindValidFind( void );
BOOL             FindNextText( HWND, DWORD * );
BOOL MySaveFile( HWND hWnd);
LRESULT _stdcall AppGetWindowsVersion( PTSTR, PTSTR );
static void GetInstallationInfo( LPTSTR, LPTSTR );
static void GetApplicationParameters( int *, int *, int *, int *, int *, TCHAR * );
static void SetApplicationParameters( HWND, TCHAR * );

#endif
