/*C_HEADER_FILE****************************************************************
FILE			:	ParamsDlg.cpp
DESC			:	GUI to set TTS parameters
TABS			:	3
OWNER			:	Fonix
DATE CREATED	:	24 Aug 2005

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER*******************************************************************/

#include "speak.h"
#include "resource.h"

extern HFONT ghLargeBoldFont;
extern SPEAK Speak;

/*FUNCTION_HEADER**********************
 * NAME:	;SetVolumeSlider
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void SetVolumeSlider(HWND hDlg, int iVol)
{
	if( iVol == 0 )
		iVol = 50;
	SendDlgItemMessage(hDlg, IDC_SLIDER_VOLUME, TBM_SETPOS,   1, (LPARAM)iVol);
}


/*FUNCTION_HEADER**********************
 * NAME:	;SetPitchSlider
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void SetPitchSlider(HWND hDlg, int iPitch)
{

	if( iPitch == 0 )
		iPitch = 50;
	SendDlgItemMessage(hDlg, IDC_SLIDER_PITCH, TBM_SETPOS,   1, (LPARAM)iPitch);
}


/*FUNCTION_HEADER**********************
 * NAME:	;SetSpeedSlider
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void SetSpeedSlider(HWND hDlg, int iSpeed)
{

	if( iSpeed == 0 )
		iSpeed = 50;
	SendDlgItemMessage(hDlg, IDC_SLIDER_RATE, TBM_SETPOS,   1, (LPARAM)iSpeed);
}


/*FUNCTION_HEADER**********************
 * NAME:	;ParamsDlgProc
 * DESC: 	Set the TTS parameters
 * IN:		hDlg, message, wParam, lParam
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
LRESULT CALLBACK ParamsDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static	int iRate, iPitch, iVolume;
	TCHAR	tsText[_MAX_PATH];

	switch(message)
	{
	case WM_INITDIALOG:

		iRate = Speak.iSpeechRate;

		if( iRate < RATE_MIN || iRate > RATE_MAX )
			iRate = SPEAK_RATE;
		SendDlgItemMessage(hDlg, IDC_SLIDER_RATE,		TBM_SETTICFREQ, (RATE_MAX-RATE_MIN)/10, 1);
		SendDlgItemMessage(hDlg, IDC_SLIDER_RATE,		TBM_SETLINESIZE, 0, 1);
		SendDlgItemMessage(hDlg, IDC_SLIDER_RATE,		TBM_SETRANGE, 1, MAKELONG(RATE_MIN, RATE_MAX));
		SetSpeedSlider(hDlg, iRate);

		_stprintf(tsText, _T("%d wpm"), iRate);
		SendDlgItemMessage(hDlg, IDC_EDIT_RATE,		WM_SETTEXT, 0, (LPARAM)tsText);

		iVolume = Speak.iVolume;
		if( iVolume < 0 || iVolume > VOLUME_MAX )
			iVolume = VOLUME_DEF;
		SendDlgItemMessage(hDlg, IDC_SLIDER_VOLUME,		TBM_SETTICFREQ, (VOLUME_MAX-VOLUME_MIN)/10, 1);
		SendDlgItemMessage(hDlg, IDC_SLIDER_VOLUME,		TBM_SETLINESIZE, 0, 1);
		SendDlgItemMessage(hDlg, IDC_SLIDER_VOLUME,		TBM_SETRANGE, 1, MAKELONG(VOLUME_MIN,VOLUME_MAX));
		SetVolumeSlider(hDlg, iVolume);

		_stprintf(tsText, _T("%d"), iVolume);
		SendDlgItemMessage(hDlg, IDC_EDIT_VOLUME,	WM_SETTEXT, 0, (LPARAM)tsText);


		iPitch = Speak.iPitch;
		if( iPitch == 0 )
			iPitch = PITCH_DEF;
		SendDlgItemMessage(hDlg, IDC_SLIDER_PITCH,		TBM_SETTICFREQ, (PITCH_MAX-PITCH_MIN)/10, 1);
		SendDlgItemMessage(hDlg, IDC_SLIDER_PITCH,		TBM_SETLINESIZE, 0, 1);
		SendDlgItemMessage(hDlg, IDC_SLIDER_PITCH,		TBM_SETRANGE, 1, MAKELONG(PITCH_MIN,PITCH_MAX));
		SetPitchSlider(hDlg, iPitch);

		_stprintf(tsText, _T("%d"), iPitch);
		SendDlgItemMessage(hDlg, IDC_EDIT_PITCH,	WM_SETTEXT, 0, (LPARAM)tsText);

		return TRUE;

	case WM_HSCROLL:
		{
			HWND	hwnd = (HWND) lParam;
			int	iPos = SendMessage(hwnd, TBM_GETPOS, 0, 0),
				iLineSz = SendMessage(hwnd, TBM_GETLINESIZE, 0, 0),
				iPageSz = SendMessage(hwnd, TBM_GETPAGESIZE, 0, 0);

			switch (LOWORD(wParam))
			{
			case TB_LINEUP:
				iPos += iLineSz;
				break;
			case TB_LINEDOWN:
				iPos -= iLineSz;
				break;
			case TB_PAGEUP:
				iPos += iPageSz;
				break;
			case TB_PAGEDOWN:
				iPos -= iPageSz;
				break;
			}

			switch(GetDlgCtrlID(hwnd))
			{
			case IDC_SLIDER_VOLUME:
				iVolume = iPos;
				_stprintf(tsText, _T("%d"), iVolume);
				SendDlgItemMessage(hDlg, IDC_EDIT_VOLUME,	WM_SETTEXT, 0, (LPARAM)tsText);
				break;

			case IDC_SLIDER_PITCH:
				iPitch = iPos;
				_stprintf(tsText, _T("%d"), iPitch);
				SendDlgItemMessage(hDlg, IDC_EDIT_PITCH,	WM_SETTEXT, 0, (LPARAM)tsText);
				break;

			case IDC_SLIDER_RATE:
				iRate = iPos;
				_stprintf(tsText, _T("%d wpm"), iRate);
				SendDlgItemMessage(hDlg, IDC_EDIT_RATE,		WM_SETTEXT, 0, (LPARAM)tsText);
				break;
			}

		}	/*  WM_HSCROLL  */
		return TRUE;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;


	case WM_COMMAND:

		switch(LOWORD(wParam))
		{
			case IDOK:
				Speak.iPitch = iPitch;
				Speak.iSpeechRate = iRate;
				Speak.iVolume = iVolume;
				EndDialog(hDlg, 1);
				break;

			case IDCANCEL:
				EndDialog(hDlg, 0);
				break;

		}

	}	// switch()
		
	return FALSE;

}	/*  TTSDlgProc  */
