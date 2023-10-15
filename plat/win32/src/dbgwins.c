/*C_HEADER_FILE****************************************************************
FILE			:	dgbwins.c
DESC			:	debug output window functions
TABS			:	4
OWNER			:	Fonix
DATE CREATED	:	

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
/**********************************************************************/
/*    Revision History:                                        
 *
 * Rev  Who 	Date        Description
 * ---  -----   ----------- --------------------------------------------
 * 001  JAW     02/27/1998  Merged CE code.
 * 0012 CJL     03/18/1998  Removed specific path for dectalkf.h.
 * 0013 EAB		09/24/1998  Fixed WINPRINTF function, so that it can be truely called with or without 
 *							a carriage return BATS 760
 * 004	MGS		09/09/1998	made it print the data the first time through
 * 005	mfg		07/29/1999	undefined process.h for WinCE
 * 006	MGS		10/29/1999	removed debug window for release builds
 * 007	NAL		05/23/2000	Warning removal
 * 008 	CAB		10/16/00	Changed copyright info
 * 009	MGS		05/09/2001	Some VxWorks porting BATS#972
 * 010	CAB		05/14/2001 	Updated copyright info
 * 011	MGS		06/07/2001	Made it restart when closed
 */

 
/*
 * Debug Window Source File
 *  Kevin Bruckert  July 11, 1996
 *
 * These function create a virtual "printf" function for WIN95/NT for debugging
 *
 * Used by PH
 */
#ifdef _DEBUG

#include "dectalkf.h"
#include "port.h"

#ifndef UNDER_CE

// #define	USE_MAIN

#define	MAIN_VER	1
#define	MIN_VER		1

#define	TIMER_MS	250

#define	OWIN_STYLE		(WS_POPUPWINDOW)
//#define	WIN_STYLE	(WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MINIMIZEBOX | WS_VSCROLL)
#define	WIN_STYLE		(WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MINIMIZEBOX | WS_HSCROLL)
#define	WIN_X_START		0
#define	WIN_Y_START		0
#define	WIN_X_SIZE		1000
#define	WIN_Y_SIZE		600
#define	WIN_MENU		NULL

/* WinProc */
LONG APIENTRY debug_window(HWND hWnd, UINT uiMessage, WPARAM wParam, LPARAM lParam);

HWND	DbgWindow,
		ghEditWnd;
HFONT	hFontFixed;


/* String buffer from WINprintf calls */
char	WpfStrBuffer[MAX_LINES][MAX_PER_LINE];
int		CurrentLine;
int		DispLine;
int		WinLines = 0;
int		updated = 0;
/* 004	MGS		09/09/1998	made it print the data the first time through */
volatile int		in_winmain=0;
volatile int		Thread_Alive = 0;

/* Prototypes */
void initialize_window(void);
void unitialize_window(void);
int do_window(void);
void WINprint(char *str);
void PaintClient(void);
void HScroll(int ScrollVal, short int ScrollPos);
void VScroll(int ScrollVal, short int ScrollPos);
void SetVScroll(void);
void KPress(int key);
void Timer(void);
void CopyToClipboard(void);

#ifndef USE_MAIN

int WINmain(void);

void WINstart_thread(void) 
{
#ifndef LDS_BUILD
	if (Thread_Alive==0 && in_winmain==0)
	_beginthread((void *)WINmain,0,0); // NAL warning removal
#endif
	return;
}
#endif

#ifdef USE_MAIN
int APIENTRY WinMain( HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
#else
int WINmain(void)
#endif
{
	int ret = 0; // NAL warning removal

	if (Thread_Alive == 1)			return ret;		/* Don't rerun WINmain */
	if (in_winmain==1) return ret;
	in_winmain=1;
	initialize_window();

	if (SetTimer(DbgWindow, 1, TIMER_MS, NULL) == 0) 
	{
		unitialize_window();
		MessageBox(DbgWindow, "Unable to allocate timer", "Debug Window Error", MB_ICONERROR | MB_OK);
		return ret;
	}

	Thread_Alive = 1;

	//FNX_PRINTF("Debug window v%d.%02d ready...\n",MAIN_VER,MIN_VER);
	ret = do_window();
	unitialize_window();
	KillTimer(DbgWindow, 1);
	DbgWindow=NULL;
	Thread_Alive = 0;
	in_winmain=0;
	return ret;
}

void initialize_window(void) 
{
	WNDCLASS	Wndclass;
	DWORD		err;
	char		WndClass[] = "DebugWindow";

	Wndclass.style			= CS_BYTEALIGNCLIENT | CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc	= debug_window;
	Wndclass.cbClsExtra		= 0;
	Wndclass.cbWndExtra		= 0;
	Wndclass.hInstance		= NULL;
	Wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor		= LoadCursor (NULL, IDC_ARROW) ;
	Wndclass.hbrBackground	= GetStockObject (WHITE_BRUSH) ;
	Wndclass.lpszMenuName	= NULL;
	Wndclass.lpszClassName	= WndClass;

	if (!RegisterClass(&Wndclass))	{ /*return; */ }
	DbgWindow = CreateWindow(WndClass, WndClass, 
		WIN_STYLE, 
		WIN_X_START, WIN_Y_START,
		WIN_X_SIZE, WIN_Y_SIZE, 
		WIN_MENU, NULL, NULL, NULL);

	if(DbgWindow == NULL) 
	{
		err = GetLastError();
		return;
	}

	/* Window created successfully */
	CurrentLine = 0;
	DispLine = 0;
	return;
}

void unitialize_window(void) {
	UnregisterClass("WndClass",NULL);
	return;
}

int do_window(void) {
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//
//  WindowProc
//
LONG APIENTRY debug_window(HWND hWnd, UINT uiMessage, WPARAM wParam, LPARAM lParam) 
{
	short		dwVal;
	SCROLLINFO	si;
	TEXTMETRIC	tm;
	HDC			hdc;
	LOGFONT		lf;
	static int
		yClient,		// height of client area 
		xClient,		// width of client area 
		xClientMax,		// maximum width of client area 
		xChar,			// horizontal scrolling unit 
		yChar,			// vertical scrolling unit 
		xUpper,			// average width of uppercase letters 
		xPos,			// current horizontal scrolling position 
		yPos;			// current vertical scrolling position 


	switch( uiMessage ) 
	{
		case WM_CREATE : 
			// Set the window font to a fixed pitch font so that everything lines up nice and pretty
			memset(&lf, 0, sizeof(lf));
			lf.lfHeight = 16;						// Use a large bold font for Ed's eyesight
			lf.lfWeight = FW_BOLD;
			lf.lfCharSet = ANSI_CHARSET;
			lf.lfOutPrecision = OUT_RASTER_PRECIS;
			lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
			lf.lfQuality = DEFAULT_QUALITY;
			lf.lfPitchAndFamily = FIXED_PITCH;
			_tcscpy(lf.lfFaceName, _T("Courier"));
			hFontFixed = CreateFontIndirect(&lf);

			// Get the handle to the client area's device context. 
			hdc = GetDC(hWnd); 
	 
			// Extract font dimensions from the text metrics. 
			GetTextMetrics(hdc, &tm); 
			xChar = tm.tmAveCharWidth; 
			xUpper = (tm.tmPitchAndFamily & 1 ? 3 : 2) * xChar/2; 
			yChar = tm.tmHeight + tm.tmExternalLeading; 
	 
			// Free the device context. 
			ReleaseDC(hWnd, hdc); 
	 
			// Set an arbitrary maximum width for client area. 
			// (xClientMax is the sum of the widths of 48 average 
			// lowercase letters and 12 uppercase letters.) 
			xClientMax = 48 * xChar + 12 * xUpper; 
			return 0; 

		case WM_DESTROY:	PostQuitMessage(0);
							break ;

		case WM_CLOSE:		/* Close window */
							DestroyWindow(hWnd);
							break;

		case WM_PAINT:		/* Paint the client */
							PaintClient();
							break;

		case 0x020A:	// WM_MOUSEWHEEL
							dwVal = (short)HIWORD(wParam);
							if( dwVal > 0 )
								VScroll(SB_LINEUP, 0);
							else
								VScroll(SB_LINEDOWN, 0);
							break;

		case WM_VSCROLL:	/* Verticle Scroll Bar */
							VScroll((int) LOWORD(wParam), (short int) HIWORD(wParam));
							break;
		case WM_HSCROLL:
							HScroll((int) LOWORD(wParam), (short int) HIWORD(wParam));
							break;

		case WM_KEYDOWN:	/* Character recieved */
							KPress((int) wParam);
							break;

		case WM_TIMER:		/* Timer Click */
							if (updated)	Timer();
							break;

		case WM_SIZE:
			// Retrieve the dimensions of the client area. 
			yClient = HIWORD (lParam); 
			xClient = LOWORD (lParam);
	 
			// Set the horizontal scrolling range.
			SetScrollRange(hWnd, SB_HORZ, 0, 100, TRUE);
			break;


		default:			
			return DefWindowProc(hWnd,uiMessage, wParam, lParam);
	}

	return 0L;
}

void PaintClient(void) 
{
	HDC DbgDC;
	int Pos_X = 0, Pos_Y = 0;
	SIZE sz;
	RECT winsz;
	int line, lines, chklines;
	PAINTSTRUCT ps;
	SCROLLINFO si;

	DbgDC = BeginPaint(DbgWindow, &ps);

	SetVScroll();
	updated = 0;

	if (CurrentLine != 0) 
	{
		if (!GetClientRect(DbgWindow, &winsz))					
			return;
		if (!GetTextExtentPoint32(DbgDC, WpfStrBuffer[CurrentLine-1],
			FNX_STRLEN(WpfStrBuffer[CurrentLine-1]), &sz))	
			return;

		lines = (winsz.bottom - winsz.top) / (sz.cy + 1);
		if (lines > CurrentLine)	
			lines = CurrentLine;
		WinLines = lines;

		chklines = DispLine;
		if (DispLine < lines)	
			chklines = lines;
		line = DispLine - lines;
		if (line < 0)	
			line = 0;
		lines += line;

		SelectObject(DbgDC, hFontFixed);

		GetScrollInfo(DbgWindow, SB_HORZ, &si);
		Pos_X -= winsz.right * si.nPos / 100;

		for (;line < chklines; line++) 
		{
			TextOut(DbgDC, Pos_X, Pos_Y, WpfStrBuffer[line], FNX_STRLEN(WpfStrBuffer[line]));
			Pos_Y += sz.cy + 1;
		}
	}

	SetScrollRange(DbgWindow, SB_VERT, 0, CurrentLine - WinLines + 1, TRUE);
	SetVScroll();
	EndPaint(DbgWindow, &ps);
	return;
}

void Timer(void) {
	RECT winsz;

	if (!GetClientRect(DbgWindow, &winsz))					
		return;
	InvalidateRect(DbgWindow, &winsz, TRUE);
	return;
}

void VScroll(int ScrollVal, short int ScrollPos) 
{
	HDC		DbgDC;
	SIZE	sz;
	RECT	winsz;
	int		page = 0;

	if (!GetClientRect(DbgWindow, &winsz))					
		return;
	if (CurrentLine != 0) 
	{
		DbgDC = GetDC(DbgWindow);
		if (!GetTextExtentPoint32(DbgDC, WpfStrBuffer[CurrentLine-1],
			FNX_STRLEN(WpfStrBuffer[CurrentLine-1]), &sz))		
			return;
		page = (winsz.bottom - winsz.top) / (sz.cy + 1);
		WinLines = page;
		ReleaseDC(DbgWindow,DbgDC);
	}

	switch (ScrollVal) 
	{
		case SB_BOTTOM:			DispLine = CurrentLine;	break;
		case SB_LINEDOWN:		DispLine++;				break;
		case SB_LINEUP:			DispLine--;				break;
		case SB_PAGEDOWN:		DispLine += page;		break;
		case SB_PAGEUP:			DispLine -= page;		break;
		case SB_THUMBPOSITION:	DispLine = ScrollPos + WinLines - 1;	break;
		case SB_THUMBTRACK:		DispLine = ScrollPos + WinLines - 1;	break;
		case SB_TOP:			DispLine = 0;			break;
	}
	if (DispLine > CurrentLine)		DispLine = CurrentLine;
	if (DispLine < 0)				DispLine = 0;

	SetVScroll();
	InvalidateRect(DbgWindow, &winsz, TRUE);
	return;
}

void SetVScroll(void) 
{
	SCROLLINFO SInfo;

	SInfo.cbSize = sizeof(SInfo);
	SInfo.fMask = SIF_POS;
	SInfo.nPos = DispLine - WinLines + 1;
	if (DispLine - WinLines < 0)	
		SInfo.nPos = 0;
	SetScrollInfo(DbgWindow, SB_VERT, &SInfo, TRUE);
	return;
}

void HScroll(int ScrollVal, short int ScrollPos) 
{
	int	xPos;
	int xChar;       // horizontal scrolling unit 
	SCROLLINFO si;
	RECT	winsz;
	HDC	
		hdc = GetDC(DbgWindow); 
	TEXTMETRIC tm; 

	// Extract font dimensions from the text metrics. 
	GetTextMetrics(hdc, &tm); 
	xChar = tm.tmAveCharWidth; 

	if (!GetClientRect(DbgWindow, &winsz))					
		return;

	// Get all the horizontal scroll bar information
    si.cbSize = sizeof (si);
    si.fMask  = SIF_ALL;
    // Save the position for comparison later on
    GetScrollInfo(DbgWindow, SB_HORZ, &si);
    xPos = si.nPos;

	switch (ScrollVal) 
	{
		case SB_LINELEFT:		si.nPos--;				break;
		case SB_LINERIGHT:		si.nPos++;				break;
		case SB_PAGELEFT:		si.nPos -= si.nPage;	break;
		case SB_PAGERIGHT:		si.nPos += si.nPage;	break;
		case SB_THUMBTRACK:		si.nPos = si.nTrackPos;	break;
		default:	break;
	}
	// Set the position
	si.fMask = SIF_POS;
	SetScrollInfo(DbgWindow, SB_HORZ, &si, TRUE);

	InvalidateRect(DbgWindow, &winsz, TRUE);
	return;
}

void PrintFile(void) {
	/* Initialize the PRINTDLG members. */ 
	PRINTDLG pd;
	DWORD err;

 
	pd.lStructSize = sizeof(PRINTDLG); 
	pd.hDevMode = (DT_HANDLE) NULL; 
	pd.hDevNames = (DT_HANDLE) NULL; 
	pd.Flags = PD_RETURNDC;
	pd.hwndOwner = DbgWindow;
	pd.hDC = (HDC) NULL; 
	pd.nFromPage = 1; 
	pd.nToPage = 1; 
	pd.nMinPage = 0; 
	pd.nMaxPage = 0; 
	pd.nCopies = 1; 
	pd.hInstance = (DT_HANDLE) 1; 
	pd.lCustData = 0L; 
	pd.lpfnPrintHook = (LPPRINTHOOKPROC) NULL; 
	pd.lpfnSetupHook = (LPSETUPHOOKPROC) NULL; 
	pd.lpPrintTemplateName = (LPSTR) NULL; 
	pd.lpSetupTemplateName = (LPSTR)  NULL; 
	pd.hPrintTemplate = (DT_HANDLE) NULL; 
	pd.hSetupTemplate = (DT_HANDLE) NULL; 
 
	/* Display the PRINT dialog box. */ 
 
	PrintDlg(&pd); 
	err = CommDlgExtendedError();
 	return;
}

LPSTR GetFileName(void) {
	OPENFILENAME file;
	BOOL ret;
	static UCHAR filenm[300];
	UCHAR filter[256];

	FNX_STRCPY(filter,"*.*");
	filter[FNX_STRLEN(filter)+1] = '\0';
	FNX_STRCPY(filenm,"debug.out");

	file.lStructSize = sizeof(OPENFILENAME);
	file.hwndOwner = NULL;
	file.hInstance = NULL;
	file.lpstrFilter = filter;
	file.lpstrCustomFilter = NULL;
	file.nMaxCustFilter = (ULONG) NULL;
	file.nFilterIndex = (ULONG) 1;
	file.lpstrFile = filenm;
	file.nMaxFile = 300;
	file.lpstrFileTitle = NULL;
	file.nMaxFileTitle = 0;
	file.lpstrInitialDir = NULL;
	file.lpstrTitle = "Save as...";
	file.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;
	file.nFileOffset = 0;
	file.nFileExtension = (USHORT) NULL;
	file.lpstrDefExt = NULL;
	file.lCustData = (long) NULL;
	file.lpfnHook = NULL;
	file.lpTemplateName = NULL;

	ret = GetSaveFileName(&file);
	if (ret == FALSE)	return NULL;
	return filenm;
}

void SaveFile(void) {
	LPSTR fname = GetFileName();
	FILE *out;
	int line;

	if (fname == NULL) {
		MessageBox(DbgWindow, "Save cancelled", "Debug Window Error", MB_ICONERROR | MB_OK);
		return;
	}
	out = FNX_FOPEN(fname,"w");
	if (out == NULL) {
		MessageBox(DbgWindow, "Unable to save file", "Debug Window Error", MB_ICONERROR | MB_OK);
		return;
	}

	for (line = 0; line < CurrentLine; line++) {
		FNX_FPRINTF(out, "%s\r\n", WpfStrBuffer[line]);
	}
	FNX_FCLOSE(out);
	return;
}

void ClearDisp(void) 
{
	CurrentLine = 0;
	DispLine = 0;
	return;
}

void CopyToClipboard(void) 
{

	HGLOBAL hMem;
	BYTE *pDst;
	int i = 0, len = 0;

	if(OpenClipboard(DbgWindow))
	{
		EmptyClipboard();
		
		for(i = 0; i < CurrentLine; i++)
		{
			len += strlen(WpfStrBuffer[i]);
		}
		len+=(CurrentLine * 2) + 1; // for \r\n and NULL
		// don't delete this - it is owned by the system after SetClipboardData
        hMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, len);
        pDst = (BYTE *)GlobalLock(hMem);
		for(i = 0; i < CurrentLine; i++)
		{
			len = strlen(WpfStrBuffer[i]) * sizeof(char);
			memcpy(pDst, WpfStrBuffer[i], len);
			pDst+= len;
			memcpy(pDst, "\r\n", 2);
			pDst+=2;
		}
		*pDst = 0;
        GlobalUnlock(hMem);

		SetClipboardData( CF_TEXT, hMem);
		CloseClipboard();
	}

}

void KPress(int key) 
{
	HDC		DbgDC;
	SIZE	sz;
	RECT	winsz;
	int		page = 0;

	if (!GetClientRect(DbgWindow, &winsz))					return;
	if (CurrentLine != 0) 
	{
		DbgDC = GetDC(DbgWindow);
		if (!GetTextExtentPoint32(DbgDC, WpfStrBuffer[CurrentLine-1],
			FNX_STRLEN(WpfStrBuffer[CurrentLine-1]), &sz))		return;
		page = (winsz.bottom - winsz.top) / (sz.cy + 1);
		ReleaseDC(DbgWindow,DbgDC);
	}

#define	KEY_END		35
#define	KEY_DOWN	40
#define	KEY_UP		38
#define	KEY_PGDN	34
#define	KEY_PGUP	33
#define	KEY_HOME	36
#define KEY_S		83
#define KEY_P		80
#define KEY_C		67
#define KEY_K		75

	switch (key) {
		case KEY_END:			DispLine = CurrentLine;	break;
		case KEY_DOWN:			DispLine++;				break;
		case KEY_UP:			DispLine--;				break;
		case KEY_PGDN:			DispLine += page;		break;
		case KEY_PGUP:			DispLine -= page;		break;
		case KEY_HOME:			DispLine = 0;			break;
		case KEY_S:				SaveFile();				break;
		case KEY_P:				PrintFile();			break;
		case KEY_C:				ClearDisp();			break;	
		case KEY_K:				CopyToClipboard();		break;
	}
	if (DispLine > CurrentLine)		DispLine = CurrentLine;
	if (DispLine < 0)				DispLine = 0;

	SetVScroll();
	InvalidateRect(DbgWindow, &winsz, TRUE);
	return;
}

void WINprint(char *str) 
{
	static int Pos_X = 0, Pos_Y = 0;
	int counter=0;

	if (Thread_Alive == 0)			
	{
		if (in_winmain==0)
		{
			WINstart_thread();
			while (Thread_Alive==0 && counter++ <500)
			{
				Sleep(50);
			}
		}
	}

	if (CurrentLine < MAX_LINES) 
	{
		FNX_STRNCPY(WpfStrBuffer[CurrentLine],str,MAX_PER_LINE-1);
		WpfStrBuffer[CurrentLine][MAX_PER_LINE-1]='\0';
		CurrentLine++;
		DispLine = CurrentLine;
		SetScrollRange(DbgWindow, SB_VERT, 1, CurrentLine, TRUE);
		SetVScroll();
	} 
	else 
	{
		memmove(WpfStrBuffer[0],WpfStrBuffer[1],(MAX_LINES-1) * MAX_PER_LINE);
		FNX_STRNCPY(WpfStrBuffer[MAX_LINES-1],str,MAX_PER_LINE-1);
		WpfStrBuffer[MAX_LINES-1][MAX_PER_LINE-1]='\0';
	}
	updated = 1;
	return;
}

void WINprintf(char *fmt, ...) 
{
	TCHAR	tsBuf[2048];
	static char line[2048];
	char		tmp[2048];
	static int inbufptr=0;
	unsigned int	ch; // NAL warning removal
	int counter=0;
	va_list vargs;

	if (Thread_Alive == 0)			
	{
		if (in_winmain==0)
		{
			WINstart_thread();
			while (Thread_Alive==0 && counter++ <500)
			{
				Sleep(50);
			}
		}
	}

	va_start(vargs,fmt);
	vsprintf(tmp,fmt,vargs);
	va_end(vargs);
	
	ch=0;	
	while (ch < FNX_STRLEN(tmp))
	{
		line[inbufptr++]=tmp[ch];
		ch++;
	}
	line[inbufptr]='\0';

	ch = 0;
	
	while (ch < FNX_STRLEN(line)) 
	{
		if (line[ch] == 10 || line[ch] == 13) 
		{
			/* New line detected */
			FNX_STRCPY(tmp,line);
			tmp[ch] = '\0';
			WINprint(tmp);

#ifdef UNICODE
			mbstowcs(tsBuf, tmp, 1024);
#else
			FNX_STRCPY(tsBuf, tmp);
#endif
			OutputDebugString(tsBuf);
			OutputDebugString(_T("\n"));

			inbufptr = 0;
			//break;
			/* Carriage-return/line feed */
			if (tmp[ch+1] == 10 || tmp[ch+1] == 13)	
			{
				ch++;
			}
			FNX_STRCPY(tmp,line + ch + 1);
			FNX_STRCPY(line,tmp);
			ch=0;
			inbufptr=FNX_STRLEN(line);
			
		} else {
			ch++;
		}
	}

	return;
}

#endif


#else //#ifdef _DEBUG
void WINprintf(char *fmt, ...) {}

void WINstart_thread(void){}

void WINprint(char *str){}

#endif

