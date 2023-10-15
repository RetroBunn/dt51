/*FUNCTION_HEADER************************************************
* NAME:		;
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/

#include <windows.h>
#include <windowsx.h> 
#include <richedit.h>
#include <commctrl.h>

#include "resource.h"
#include "gui.h"
#include <stdio.h>
#include <stdlib.h>

#include "CodePageConv.h"

// matt's stuff outside the gui
// ............................
#define EXT extern
#include	"port.h"
#include	"onsei.h"
#include	"ile_envh.h"
#include	"ile_errh.h"
#include	"ile_fddh.h"
#include	"ile_kkhh.h"
#include	"ile_nydh.h"
#include	"ile_stzh.h"
#include	"ile_func.h"
#include	"ile_rnsc.h"
#include	"ile_idic.h"

#include	"ile_acch.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"

HINSTANCE g_hInst;
HANDLE ghMemUpdateEvent;

#define CONVERT // enables convert button; one-time conversion of onsei dictionary to dictionary with done column

static const BYTE hardchar_table[][3]={
	'A',  0,  0,	'I',  0,  0,	'U',  0,  0,	'E',  0,  0,	/* 00..03 */
	'O',  0,  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 04..07 */
	'K','A',  0,	'K','I',  0,	'K','U',  0,	'K','E',  0,	/* 08..0B */
	'K','O',  0,	'K','Y','A',	'K','Y','U',	'K','Y','O',	/* 0C..0F */
	'S','A',  0,	'S','I',  0,	'S','U',  0,	'S','E',  0,	/* 10..13 */
	'S','O',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 14..17 */
	'S','H','A',	'S','H','I',	'S','H','U',	'S','H','E',	/* 18..1B */
	'S','H','O',	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 1C..1F */
	'T','A',  0,	'T','I',  0,	'T','U',  0,	'T','E',  0,	/* 20..23 */
	'T','O',  0,	'C','H','A',	'C','H','U',	'C','H','O',	/* 24..27 */
	'C','H','A',	'C','H','I',	'C','H','U',	'C','H','E',	/* 28..2B */
	'C','H','O',	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 2C..2F */
	'T','S','A',	'T','S','I',	'T','S','U',	'T','S','E',	/* 30..33 */
	'T','S','O',	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 34..37 */
	'N','A',  0,	'N','I',  0,	'N','U',  0,	'N','E',  0,	/* 38..3B */
	'N','O',  0,	'N','Y','A',	'N','Y','U',	'N','Y','O',	/* 3C..3F */
	'H','A',  0,	'H','I',  0,	'H','U',  0,	'H','E',  0,	/* 40..43 */
	'H','O',  0,	'H','Y','A',	'H','Y','U',	'H','Y','O',	/* 44..47 */
	'F','A',  0,	'F','I',  0,	'?','?',  0,	'F','E',  0,	/* 48..4B */
	'F','O',  0,	'F','Y','A',	'F','Y','U',	'F','Y','O',	/* 4C..4F */
	'M','A',  0,	'M','I',  0,	'M','U',  0,	'M','E',  0,	/* 50..53 */
	'M','O',  0,	'M','Y','A',	'M','Y','U',	'M','Y','O',	/* 54..57 */
	'Y','A',  0,	'?','?',  0,	'Y','U',  0,	'Y','E',  0,	/* 58..5B */
	'Y','O',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 5C..5F */
	'R','A',  0,	'R','I',  0,	'R','U',  0,	'R','E',  0,	/* 60..63 */
	'R','O',  0,	'R','Y','A',	'R','Y','U',	'R','Y','O',	/* 64..67 */
	'W','A',  0,	'W','I',  0,	'?','?',  0,	'W','E',  0,	/* 68..6B */
	'W','O',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 6C..6F */
	'G','A',  0,	'G','I',  0,	'G','U',  0,	'G','E',  0,	/* 70..73 */
	'G','O',  0,	'G','Y','A',	'G','Y','U',	'G','Y','O',	/* 74..77 */
	'Q','A',  0,	'Q','I',  0,	'Q','U',  0,	'Q','E',  0,	/* 78..7B */
	'Q','O',  0,	'Q','Y','A',	'Q','Y','U',	'Q','Y','O',	/* 7C..7F */
	'Z','A',  0,	'Z','I',  0,	'Z','U',  0,	'Z','E',  0,	/* 80..83 */
	'Z','O',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 84..87 */
	'J','A',  0,	'J','I',  0,	'J','U',  0,	'J','E',  0,	/* 88..8B */
	'J','O',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* 8C..8F */
	'D','A',  0,	'D','I',  0,	'D','U',  0,	'D','E',  0,	/* 90..93 */
	'D','O',  0,	'D','Y','A',	'D','Y','U',	'D','Y','O',	/* 94..97 */
	'B','A',  0,	'B','I',  0,	'B','U',  0,	'B','E',  0,	/* 98..9B */
	'B','O',  0,	'B','Y','A',	'B','Y','U',	'B','Y','O',	/* 9C..9F */
	'P','A',  0,	'P','I',  0,	'P','U',  0,	'P','E',  0,	/* A0..A3 */
	'P','O',  0,	'P','Y','A',	'P','Y','U',	'P','Y','O',	/* A4..A7 */
	'V','A',  0,	'V','I',  0,	'V','U',  0,	'V','E',  0,	/* A8..AB */
	'V','O',  0,	'V','Y','A',	'V','Y','U',	'V','Y','O',	/* AC..AF */
	'K','W','A',	'K','W','I',	'?','?',  0,	'K','W','E',	/* B0..B3 */
	'K','W','O',	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* B4..B7 */
	'G','W','A',	'G','W','I',	'?','?',  0,	'G','W','E',	/* B8..BB */
	'G','W','O',	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* BC..BF */
	'-',  0,  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* C0..C3 */
	'?','?',  0,	'?','?',  0,	'?','?',  0,	'?','?',  0,	/* C4..C7 */
	/* CF is an uncategorized double consonant at a number conversion. */
	'$',  0,  0,	'$',  0,  0,	'$',  0,  0,	'$',  0,  0,	/* C8..CB */
	'?','?',  0,	'?','?',  0,	'?','?',  0,	'$',  0,  0,	/* CC..CF */
	/* D7 is an uncategorized syllabic nasal at a number conversion. */
	'X',  0,  0,	'X',  0,  0,	'X',  0,  0,	'X',  0,  0,	/* D0..D3 */
	'X',  0,  0,	'?','?',  0,	'?','?',  0,	'X',  0,  0,	/* D4..D7 */
	0																/* STOPPER */
};

extern BOOL GetNewDictionaryName( char *szFilename );
extern void Myreonsei( HWND hDlg, HWND hList );

void code_to_hardchar2(ch,ac, a) BYTE ch,ac; register BYTE *a; {
	const BYTE* addr;

	addr=(&hardchar_table[ch][0]);
	if (*addr)
		a[0]=(*addr++); 
	if (*addr)
		a[1]=(*addr++); 
	if (*addr)
		a[2]=(*addr);
}

#ifdef CONVERT
/*FUNCTION_HEADER************************************************
* NAME:		;ConvertOnseiDictionary
* DESC:		Adds Done= column to onsei dictionary.
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void ConvertOnseiDictionary( HWND hDlg )
{
	TCHAR		tsFilename[MAX_PATH+1];
	char		*pcTmp, szFilename[MAX_PATH+1], szOutput[MAX_PATH+1], szBuffer[MAX_BUFFER+1];
	char		szHold[MAX_BUFFER+1];
	FILE		*fpInput = NULL, *fpOutput = NULL;

	if( SendDlgItemMessage( hDlg, IDC_EDIT1, WM_GETTEXT, MAX_PATH, (LPARAM)tsFilename ))
	{
		wcstombs( szFilename, tsFilename, MAX_PATH );

		strcpy( szOutput, szFilename );
		GetNewDictionaryName( szOutput );
		if( (fpInput = fopen( szFilename, "rt" )) != NULL && (fpOutput = fopen( szOutput, "wt" )) != NULL )
		{
			while( fgets( szBuffer, MAX_BUFFER, fpInput ))
			{
				if( strstr( szBuffer, INTERNAL ))
				{
					fprintf( fpOutput, "%s", szBuffer );
					while( fgets( szBuffer, MAX_BUFFER, fpInput ))
					{
						if( strstr( szBuffer, KANJI ))
						{
							fprintf( fpOutput, "%s", szBuffer );
							break;
						}
						else
						if( (pcTmp = strstr( szBuffer, "ctl=" )) != NULL )
						{
							strcpy( szHold, pcTmp );
							*pcTmp = 0;
							strcat( szBuffer, "done=...\t" );
							strcat( szBuffer, szHold );
							fprintf( fpOutput, "%s", szBuffer );
						}
						else
							fprintf( fpOutput, "%s", szBuffer );
					}
				}

				if( strstr( szBuffer, KANJI ))
				{
					while( fgets( szBuffer, MAX_BUFFER, fpInput ))
					{
						if( strstr( szBuffer, EXTERNAL ))
						{
							fprintf( fpOutput, "%s", szBuffer );
							break;
						}
						else
						if( (pcTmp = strstr( szBuffer, "type=" )) != NULL )
						{
							strcpy( szHold, pcTmp );
							*pcTmp = 0;
							strcat( szBuffer, "done=...\t" );
							strcat( szBuffer, szHold );
							fprintf( fpOutput, "%s", szBuffer );
						}
						else
							fprintf( fpOutput, "%s", szBuffer );
					}
				}

				if( strstr( szBuffer, EXTERNAL ))
				{
					while( fgets( szBuffer, MAX_BUFFER, fpInput ))
					{
						if( (pcTmp = strstr( szBuffer, "flag2=" )) != NULL )
						{
							strcpy( szHold, pcTmp );
							*pcTmp = 0;
							strcat( szBuffer, "done=...\t" );
							strcat( szBuffer, szHold );
							fprintf( fpOutput, "%s", szBuffer );
						}
						else
							fprintf( fpOutput, "%s", szBuffer );
					}
					break;
				}

				fprintf( fpOutput, "%s", szBuffer );
			}

			fclose(fpInput);
			fclose(fpOutput);
			MessageBox( hDlg, _T("Conversion finished.   "), _T("NOTICE..."), MB_OK | MB_ICONINFORMATION );
		}
	}
} /* end: ConvertOnseiDictionary */
#endif

/*FUNCTION_HEADER************************************************
* NAME:		;DeleteDictionaryItems
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void DeleteDictionaryItems( DICTIONARY_POINTERS *dp )
{
	if( dp->nDict == IDD_EDIT_IDIC )
		CheckDlgButton( dp->hDlg, IDC_RADIO_IDIC, FALSE );
	else
	if( dp->nDict == IDD_EDIT_TDIC )
		CheckDlgButton( dp->hDlg, IDC_RADIO_TDIC, FALSE );
	else
	if( dp->nDict == IDD_EDIT_EDIC )
		CheckDlgButton( dp->hDlg, IDC_RADIO_EDIC, FALSE );

	SendMessage( dp->hList, LVM_DELETEALLITEMS, 0, 0 );

} /* end: DeleteDictionaryItems */

/*FUNCTION_HEADER************************************************
* NAME:		;CheckForChanges
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void CheckForChanges( DICTIONARY_POINTERS *dp )
{
	if( dp->bDictionaryChanged )
	{
		int ans = MessageBox( dp->hDlg, _T("The dictionary has changed. Click \"Yes\" to save changes,   \nor \"No\" to skip changes."), _T("WARNING..."), MB_YESNO | MB_ICONEXCLAMATION );
		if( ans == IDYES )
		{
			ghMemUpdateEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
			SendMessage( dp->hDlg, WM_COMMAND, IDSAVE, 0 );
			WaitForSingleObject( ghMemUpdateEvent, INFINITE ); 
		}
	}
} /* end: CheckForChanges */

/*FUNCTION_HEADER************************************************
* NAME:     ;ButtonClicked
* DESC:     Check to see if the user pressed 'Stop' while the
            dictionary is building.
* IN:       hCtrl: handle of the window handle to check if was
            clicked.
* OUT:      n/a
* RETURN:   n/a
* NOTES:    Used by dTool and dReports.
*END_HEADER*****************************************************/
BOOL ButtonClicked( HWND hCtrl )
{
   MSG  msg;
   if( PeekMessage( &msg, hCtrl, WM_LBUTTONDOWN, WM_LBUTTONDOWN, PM_REMOVE ) )
   {
      return(TRUE);
   }
   else
   if( PeekMessage( &msg, GetParent( hCtrl ), WM_PAINT, WM_PAINT, PM_REMOVE ) 
		||  PeekMessage( &msg, GetParent( GetParent( hCtrl )), WM_PAINT, WM_PAINT, PM_REMOVE ) )
   {
      UpdateWindow( GetParent( hCtrl ));
      UpdateWindow( GetParent( GetParent( hCtrl )));
   }
   return(FALSE);
}  /*  ButtonClicked  */

/*FUNCTION_HEADER************************************************
* NAME:		;InitializeFont
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void InitializeFont(HWND hWnd, LONG lHeight, BYTE charSet, TCHAR tsFont[], /*LPCHOOSEFONT lpCf,*/ LPLOGFONT lpLf )
{
  /*lpCf->lStructSize	= sizeof(CHOOSEFONT);
   lpCf->hwndOwner		= hWnd;
   lpCf->hDC		= NULL;
   lpCf->lpLogFont		= lpLf;
   lpCf->iPointSize	= 10;
   lpCf->Flags		= CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT|CF_NOSIZESEL;
   lpCf->rgbColors		= RGB(0,0,0);
   lpCf->lCustData		= 0;
   lpCf->lpfnHook		= NULL;
   lpCf->lpTemplateName	= NULL;
   lpCf->hInstance		= g_hInst;
   lpCf->lpszStyle		= NULL;
   lpCf->nFontType		= SIMULATED_FONTTYPE;
   lpCf->nSizeMin		= 0;
   lpCf->nSizeMax		= 0;*/

   lpLf->lfHeight		= lHeight;
   lpLf->lfWidth		= 0;
   lpLf->lfEscapement	= 0;
   lpLf->lfOrientation	= 0;
   lpLf->lfWeight		= FW_DONTCARE;
   lpLf->lfItalic		= FALSE;
   lpLf->lfUnderline	= FALSE;
   lpLf->lfStrikeOut	= FALSE;
	
   lpLf->lfCharSet		= charSet;
   lpLf->lfOutPrecision	= OUT_DEFAULT_PRECIS;
   lpLf->lfClipPrecision	= CLIP_DEFAULT_PRECIS;
   lpLf->lfQuality		= DEFAULT_QUALITY;
   lpLf->lfPitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;
	wcscpy( lpLf->lfFaceName, tsFont );

} /* end: InitializeFont */

/*FUNCTION_HEADER************************************************
* NAME:		;ColumnExists
* DESC:		Find out if a column exists in a list view control.
* IN:			hList: handle of list view control.
				nCol: number of column to check.
* OUT:		n/a
* RETURN:	TRUE if a column exists, FALSE if not.
* NOTES:		Called by GetNumColumns.
*END_HEADER*****************************************************/
BOOL ColumnExists( HWND hList, int nCol )
{
	LV_COLUMN lvc;

	lvc.mask = LVCF_WIDTH;
	return( ListView_GetColumn( hList, nCol, &lvc ));

} /* end: ColumnExists */

/*FUNCTION_HEADER************************************************
* NAME:		;DeleteAllColumns
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void DeleteAllColumns( HWND hDlg, HWND hList )
{

	while( ColumnExists( hList, 0 ))
	{
		ListView_DeleteColumn( hList, 0 );
	}
	ListView_DeleteAllItems( hList);

	SetDlgItemText( hDlg, IDC_EDIT_WORD, _T("") );
	SetDlgItemText( hDlg, IDC_EDIT_ACCENT, _T("") );
	SetDlgItemText( hDlg, IDC_EDIT_PRONUNCIATION, _T("") );
	SetDlgItemText( hDlg, IDC_STATIC_COUNT, _T("0") );

} /* end: DeleteAllColumns */

/*FUNCTION_HEADER************************************************************************
* NAME:		;ListView_GetSelection
* DESC:
* IN:		
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************************************/
int ListView_GetSelection( HWND hList )
{
	return( ListView_GetNextItem( hList, -1, LVNI_SELECTED | LVNI_FOCUSED ));

} /* end: ListView_GetSelection */

/*FUNCTION_HEADER************************************************
* NAME:		;ListViewSelection
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
int ListViewSelection( LPARAM lParam )
{
	NMLVKEYDOWN* pLV = (NMLVKEYDOWN*)lParam;
	if( pLV->wVKey != VK_RETURN && (pLV->hdr.code == LVN_KEYDOWN || pLV->hdr.code == NM_CLICK) )
	{
		int nItem = ListView_GetSelection( pLV->hdr.hwndFrom );
		if( pLV->wVKey == VK_UP )
			nItem--;
		else
		if( pLV->wVKey == VK_DOWN )
			nItem++;
		if( nItem > -1 && nItem < ListView_GetItemCount( pLV->hdr.hwndFrom ))
		{
			return(nItem);
		}
	}

	return(-1);

} /* end: ListViewSelection */

/*FUNCTION_HEADER************************************************
* NAME:		;ListView_ReturnImage
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
int ListView_ReturnImage( HWND hList, int nItem )
{
	LVITEM item;

	item.mask = LVIF_IMAGE;
	item.iItem = nItem;
	item.iSubItem = 0;
	ListView_GetItem( hList, &item );

	return(item.iImage);

} /* end: ListView_ReturnImage */

/*FUNCTION_HEADER************************************************
* NAME:		;ListView_SetImage
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void ListView_SetImage( HWND hList, int nItem, int iImage )
{
	LVITEM item;

	item.mask = LVIF_IMAGE;
	item.iItem = nItem;
	item.iSubItem = 0;
	item.iImage = iImage;
	ListView_SetItem( hList, &item );

} /* end: ListView_SetImage */

/*FUNCTION_HEADER************************************************************************
* NAME:		;ListView_AddItem
* DESC:		Generic routine for inserting items in a listview control.	
* IN:		hList: handle to listview control.
			szStuff: string containing items to insert.
* OUT:		n/a
* RETURN:	n/a
* NOTES:	Items are delimited by DELIMITER_PERIOD.	
*END_HEADER*****************************************************************************/
int ListView_AddItem( HWND hList, TCHAR szStuff[], TCHAR szKey[], int nSelected )
{
	LVITEM item;
	TCHAR *pItem, *pStuff;
	int nItem = 0;
	BOOL bDone = FALSE;

	pStuff = (TCHAR *)calloc( wcslen(szStuff)+MEDIUM_BUFFER, sizeof(TCHAR) );
	wcscpy( pStuff, szStuff );

	item.mask 		= LVIF_TEXT | LVIF_IMAGE;
	item.iItem = nSelected;
	if( wcsstr( pStuff, YES ))
		bDone = TRUE;
	pItem = wcstok( pStuff, szKey );
	while( pItem )
	{
		item.pszText  	= pItem;
		item.cchTextMax	= wcslen(pItem);
		item.iSubItem = nItem;
		item.iImage = -1;

		if( nItem == 0 )
		{
			if( nSelected == -1 ) // add item at the end of the list
				item.iItem	= ListView_GetItemCount( hList );

			if( bDone && !wcscmp( pItem, TSPLUSES ))
				item.iImage = GREENREDBALL;
			else
			if( bDone )
				item.iImage = GREENBALL;
			else
			if( !wcscmp( pItem, TSPLUSES ))
				item.iImage = REDBALL;
			else
				item.iImage = -1;
			item.iItem	= ListView_InsertItem( hList, &item );
		}
		else
		{
			ListView_SetItem( hList, &item );
		}

		nItem++;
		pItem = wcstok( NULL, szKey );
	}
	free(pStuff);
	return(item.iItem);

} /* end: ListView_AddItem */

/*FUNCTION_HEADER************************************************
* NAME:		;PrintListViewControl
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
int PrintListViewControl( DICTIONARY_POINTERS *dp, FILE *dict_file )
{
	int i, x, nCnt = ListView_GetItemCount( dp->hList );
	if( nCnt > 0 )
	{
		char szRow[MAX_BUFFER], szItem[GRAPH_BUFFER], szHeader[SMALL_BUFFER];
		TCHAR tsItem[ITEM_BUFFER];

		if( dp->nDict == IDD_EDIT_IDIC )
		{
			for( i = 0; i < nCnt; i++ )
			{
				strcpy( szRow, "" );
				for( x = 0; x < 10; x++ )
				{
					switch( x )
					{
					case 0: strcpy( szHeader, "" ); break;
					case 1: strcpy( szHeader, "\tdone="); break; //!@#$%
					case 2: strcpy( szHeader, "\tctl=" ); break;
					case 3: strcpy( szHeader, "\tf2=" ); break;
					case 4: strcpy( szHeader, "\tbno=" ); break;
					case 5: strcpy( szHeader, "\tpno=" ); break;
					case 6: strcpy( szHeader, "\tmru=" ); break;
					case 7: strcpy( szHeader, "\tacc:" ); break;
					case 8: strcpy( szHeader, "\tpron:" ); break;
					case 9: strcpy( szHeader, " phon:" ); break;
					}

					if( x == 9 && strstr( szRow, "pron:mkh" ))
						continue;

					ListView_GetItemText( dp->hList, i, x, tsItem, ITEM_BUFFER );
					if( x == 0 )
						Utf2Euc( tsItem, szItem, GRAPH_BUFFER );
					else
						wcstombs( szItem, tsItem, GRAPH_BUFFER );
					strcat( szRow, szHeader );
					if( !strcmp( szItem, PLUSES )) 
						strcat( szRow, TABS );
					else
						strcat( szRow, szItem );
				}
				fprintf( dict_file,"%s\n", szRow );
			}
			return(nCnt);
		}
		else
		if( dp->nDict == IDD_EDIT_EDIC )
		{
			for( i = 0; i < nCnt; i++ )
			{
				strcpy( szRow, "" );
				for( x = 0; x < 8; x++ )
				{
					switch( x )
					{
					case 0: strcpy( szHeader, "" ); break;
					case 1: strcpy( szHeader, "\tdone="); break; //!@#$%
					case 2: strcpy( szHeader, "\tflag2=" ); break;
					case 3: strcpy( szHeader, "\tmru=" ); break;
					case 4: strcpy( szHeader, "\tGrcd=" ); break;
					case 5: strcpy( szHeader, "\tacc:" ); break;
					case 6: strcpy( szHeader, "\tpron:" ); break;
					case 7: strcpy( szHeader, " phon:" ); break;
					}

					if( x == 7 && strstr( szRow, "pron:mkh" ))
						continue;

					ListView_GetItemText( dp->hList, i, x, tsItem, ITEM_BUFFER );
					if( x == 0 )
						Utf2Euc( tsItem, szItem, GRAPH_BUFFER );
					else
						wcstombs( szItem, tsItem, GRAPH_BUFFER );
					strcat( szRow, szHeader );
					if( !strcmp( szItem, PLUSES )) 
						strcat( szRow, "\t\t" );
					else
						strcat( szRow, szItem );
				}
				fprintf( dict_file,"%s\n", szRow );
			}
			return(nCnt);
		}
		else
		if( dp->nDict == IDD_EDIT_TDIC )
		{
			for( i = 0; i < nCnt; i++ )
			{
				if( i >= 344 && i <= 355 )
					nCnt = nCnt;

				strcpy( szRow, "" );
				strcpy( szItem, "" );
				for( x = 0; x < 6; x++ )
				{
					switch( x )
					{
					case 0: strcpy( szHeader, "" ); break;
					case 1: strcpy( szHeader, "\tdone="); break; //!@#$%
					case 2: strcpy( szHeader, "\ttype=" ); break;
					case 3: strcpy( szHeader, "\tacc:" ); break;
					case 4: strcpy( szHeader, "\tpron:" ); break;
					case 5: strcpy( szHeader, " phon:" ); break;
					}

					if( x == 5 && strstr( szRow, "pron:mkh" ))
						continue;

					ListView_GetItemText( dp->hList, i, x, tsItem, ITEM_BUFFER );
					if( x == 0 )
					{
						Utf2Euc( tsItem, szItem, GRAPH_BUFFER );
					}
					else
						wcstombs( szItem, tsItem, GRAPH_BUFFER );
					strcat( szRow, szHeader );
					if( !strcmp( szItem, PLUSES )) 
						strcat( szRow, TABS );
					else
						strcat( szRow, szItem );
				}
				fprintf( dict_file,"%s\n", szRow );
			}
			return(nCnt);
		}
	}
	return(0);

} /* end: PrintListViewControl */

/*FUNCTION_HEADER**********************
 * NAME:		;LoadDictionaryToMemory
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	

 *END_HEADER***************************/
int LoadDictionaryToMemory( DICTIONARY_POINTERS *dp, BOOL bDeleteItems )
{
	TCHAR		tsFilename[MAX_PATH+1];
	char		*pc, szFilename[MAX_PATH+1];
	int		result;
	struct	stat buf;
	FILE		*dict_file = NULL;

	if( SendDlgItemMessage( dp->hDlg, IDC_EDIT1, WM_GETTEXT, MAX_PATH, (LPARAM)tsFilename ))
	{
		SetDlgItemText( dp->hDlg, IDC_STATIC_RED, _T("Loading dictionary to memory...") );

		wcstombs( szFilename, tsFilename, MAX_PATH );

		/* get file size */
		result = stat( szFilename, &buf );
		if( result != 0 )
			return(FALSE);

		dp->pDictInMem = (char *)malloc(buf.st_size); // allocate memory for dictionary

		if( (dict_file = fopen( szFilename, "rt" )) != NULL )
		{
			if( (result = fread( dp->pDictInMem, sizeof(char), buf.st_size/sizeof(char), dict_file )) == 0 )
				return(FALSE);

			dp->pEndDict = dp->pDictInMem + result;

			/*  count lines in dictionary -- set dictionary pointers  */
			for( dp->nLineCount = 0, pc = dp->pDictInMem; (pc = strchr(pc, '\n')) != NULL && pc < dp->pEndDict; dp->nLineCount++, pc++ )
			{
				if( !strncmp( &pc[1], INTERNAL, strlen(INTERNAL) ))
					dp->pInternalDictionary = &pc[1];
				else
				if( !strncmp( &pc[1], KANJI, strlen(KANJI) ))
					dp->pTanKanji = &pc[1];
				else
				if( !strncmp( &pc[1], EXTERNAL, strlen(EXTERNAL) )) // fix this spelling
				{
					dp->pExternalDictionary = &pc[1];
				}
			}

			fclose(dict_file);
			SetDlgItemText( dp->hDlg, IDC_STATIC_RED, _T("") );
			SendDlgItemMessage( dp->hDlg, IDC_STATIC_TITLE, WM_SETTEXT, 0, (WPARAM)_T("JAPANESE DICTIONARY LOADED TO MEMORY") );
		}
	}

	if( bDeleteItems ) // these lines must come after dictionary loaded to memory
	{
		DeleteDictionaryItems( dp );
	}

	return(TRUE);

}	/*  LoadDictionaryToMemory  */

/*FUNCTION_HEADER************************************************
* NAME:		;SaveDictionary
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
BOOL SaveDictionary( DICTIONARY_POINTERS *dp )
{
	TCHAR		tsFilename[MAX_PATH+1], tsTitle[SMALL_BUFFER*2];
	char		*pc, *pcTmp1, *pcTmp2, szFilename[MAX_PATH+1], szRow[MAX_BUFFER];
	FILE		*dict_file = NULL;
	int		i, nCnt;

	UpdateWindow( dp->hList ); // erase check save message background
	SendDlgItemMessage( dp->hDlg, IDC_STATIC_RED, WM_GETTEXT, SMALL_BUFFER*2, (LPARAM)tsTitle );
	if( SendDlgItemMessage( dp->hDlg, IDC_EDIT1, WM_GETTEXT, MAX_PATH, (LPARAM)tsFilename ))
	{
		SetDlgItemText( dp->hDlg, IDC_STATIC_RED, _T("Saving dictionary...") );

		wcstombs( szFilename, tsFilename, MAX_PATH );
		GetNewDictionaryName( szFilename );
		mbstowcs( tsFilename, szFilename, MAX_PATH );
		SetDlgItemText( dp->hDlg, IDC_EDIT1, tsFilename );

		if( (dict_file = fopen( szFilename, "wt" )) != NULL )
		{
			pcTmp1 = dp->pDictInMem; // print everything up to update point (data in listview control)
			while( (pcTmp2 = strstr( pcTmp1, EOL )) != NULL && pcTmp1 < dp->pStartEdit )
			{
				strncpy( szRow, pcTmp1, (pcTmp2-pcTmp1)+1 );
				szRow[(pcTmp2-pcTmp1)+1] = 0;
				fprintf( dict_file, szRow );
				pcTmp1 = &pcTmp2[1];
			}

			if( dp->nDict == IDD_EDIT_IDIC )
				fprintf( dict_file, "Internal dictionary\n" );
			else
			if( dp->nDict == IDD_EDIT_TDIC )
				fprintf( dict_file, "Tan-Kanji\n" );

			nCnt = PrintListViewControl( dp, dict_file ); // dictionary data that might have changed
			nCnt += dp->nDeletions;
			nCnt -= dp->nAdditions;

			if( dp->nDict == IDD_EDIT_EDIC )
				nCnt--;

			// advance pointer listview control number of lines
			for( i = 0, pc = pcTmp1; (pc = strchr(pc, '\n')) != NULL && i < nCnt; i++, pc++ )
				;
			pcTmp1 = &pc[1]; // print everything after update point (data in listview control)
			while( (pcTmp2 = strstr( pcTmp1, EOL )) != NULL && pcTmp1 < dp->pEndDict )
			{
				strncpy( szRow, pcTmp1, (pcTmp2-pcTmp1)+1 );
				szRow[(pcTmp2-pcTmp1)+1] = 0;
				fprintf( dict_file, szRow );
				pcTmp1 = &pcTmp2[1];
			}
			fclose(dict_file);
			SendMessage( dp->hDlg, WM_COMMAND, IDLOAD, FALSE );
			SetDlgItemText( dp->hDlg, IDC_STATIC_RED, tsTitle );
			MessageBox( dp->hDlg, _T("Decompiled dictionary successfully saved.   "), _T("NOTICE..."), MB_OK | MB_ICONINFORMATION );
			return(TRUE);
		}
		else
			SetDlgItemText( dp->hDlg, IDC_STATIC_RED, tsTitle );
	}

	return(FALSE);

} /* end: SaveDictionary */

/*FUNCTION_HEADER************************************************
* NAME:     ;EnumControls
* DESC:     Set font for for static, edit, and listbox windows
            controls.
* IN:       hCtrl: window control handle
            lParam: parent dialog of window control
* OUT:      n/a
* RETURN:   BOOL: TRUE (keep going until all controls processed)
* NOTES:    
*END_HEADER*****************************************************/
BOOL CALLBACK EnumControls( HWND hCtrl, LPARAM lParam )
{
   HFONT hFont = (HFONT)lParam;
   SendMessage( hCtrl, WM_SETFONT, (WPARAM)hFont, TRUE );
   return( TRUE );

} /* end: EnumControls */

/* FUNCTION_HEADER****************************************************************************
*  Name:    ;GetFilename
*  Desc:		Retrieve name of Onsei dictionary to edit.
*  In:
*  Out:
*  Return:
*  Notes:
END_HEADER***********************************************************************************/
BOOL GetFilename( HWND hDlg, TCHAR tsFilename[] )
{
	OPENFILENAME ofn;
	DWORD flags;
	BOOL bRslt = FALSE;

	
	flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
	
	memset( &ofn, 0, sizeof( OPENFILENAME ));
	ofn.lStructSize = sizeof( OPENFILENAME );
	ofn.hwndOwner = hDlg;
	ofn.lpstrFilter = _T("Dictionary files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0");
	_tcscpy( tsFilename, _T(""));
	ofn.lpstrFile = tsFilename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = flags;
	ofn.lpstrDefExt = _T("txt");
	
	if( GetOpenFileName( &ofn ))
	{
		InvalidateRect( hDlg, NULL, TRUE );
		bRslt = TRUE;
	}
	
	return(bRslt);
	
} /* end: GetFilename */

/*FUNCTION_HEADER************************************************
* NAME:		;SetupListviewEDIT
* DESC:		Setup listview control for external dictionary.
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void SetupListviewEDIT( HWND hDlg, HWND hList )
{
	LV_COLUMN col;
			
	int nNarrowCol = 60, nWideCol = 100, nCol = 0;

	ListView_SetExtendedListViewStyleEx( hList, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_TWOCLICKACTIVATE ); // set list view attributes
	col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM; 
	col.fmt  = LVCFMT_LEFT;
	col.cx   = nWideCol;
	col.pszText = _T("Grapheme");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );
	
	col.cx   = nNarrowCol;
	col.pszText = _T("Done");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nNarrowCol;
	col.pszText = _T("flag2");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nNarrowCol;
	col.pszText = _T("mru");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nNarrowCol;
	col.pszText = _T("Grcd");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nWideCol*2;
	col.pszText = _T("Accent");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nWideCol+40;
	col.pszText = _T("Pronunciation");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nWideCol+40;
	col.pszText = _T("Phonemes");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

} /* end: SetupListviewEDIT */

/*FUNCTION_HEADER************************************************
* NAME:		;SetupListviewTDIT
* DESC:		Setup listview control for Kanji dictionary.
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void SetupListviewTDIT( HWND hDlg, HWND hList )
{
	LV_COLUMN col;
			
	int nNarrowCol = 60, nWideCol = 100, nCol = 0;

	ListView_SetExtendedListViewStyleEx( hList, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_TWOCLICKACTIVATE ); // set list view attributes
	col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM; 
	col.fmt  = LVCFMT_LEFT;
	col.cx   = nWideCol;
	col.pszText = _T("Grapheme");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );
	
	col.cx   = nNarrowCol;
	col.pszText = _T("Done");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nNarrowCol;
	col.pszText = _T("Type");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nWideCol*2;
	col.pszText = _T("Accent");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nWideCol*2;
	col.pszText = _T("Pronunciation");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nWideCol*2;
	col.pszText = _T("Phonemes");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

} /* end: SetupListviewTDIT */

/*FUNCTION_HEADER************************************************
* NAME:		;SetupListviewIDIT
* DESC:		Setup listview control for internal dictionary.
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void SetupListviewIDIT( HWND hDlg, HWND hList )
{
	LV_COLUMN col;
			
	int nNarrowCol = 50, nWideCol = 100, nCol = 0;

	ListView_SetExtendedListViewStyleEx( hList, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_TWOCLICKACTIVATE ); // set list view attributes
	col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM; 
	col.fmt  = LVCFMT_LEFT;
	col.cx   = nWideCol;
	col.pszText = _T("Graphemes");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );
	
	col.cx   = nNarrowCol;
	col.pszText = _T("Done");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nNarrowCol;
	col.pszText = _T("ctl");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nNarrowCol;
	col.pszText = _T("f2");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nNarrowCol;
	col.pszText = _T("bno");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nNarrowCol;
	col.pszText = _T("pno");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nNarrowCol;
	col.pszText = _T("mru");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nWideCol*2;
	col.pszText = _T("Accent");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nWideCol+20;
	col.pszText = _T("Pronunciation");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

	col.cx   = nWideCol;
	col.pszText = _T("Phonemes");
	col.iSubItem = nCol;
	ListView_InsertColumn( hList, nCol++, &col );

} /* end: SetupListviewIDIT */

/*FUNCTION_HEADER************************************************
* NAME:		;InsertNewRow
* DESC:		Insert new grapheme data after selected item in listview control
* IN:			fields: array of edit control IDs
				nFields: number of edit control IDs
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
BOOL InsertNewRow( HWND hDlg, DICTIONARY_POINTERS *dp, int fields[], int nFields )
{
	TCHAR tsItem[MEDIUM_BUFFER], tsRow[MAX_BUFFER];
	int x;

	wcscpy( tsRow, _T("") );
	for( x = 0; x < nFields; x++ )
	{
		SendDlgItemMessage( hDlg, fields[x], WM_GETTEXT, MEDIUM_BUFFER, (LPARAM)tsItem );
		if( x == 0 && *tsItem == 0 )
			return(FALSE);

		wcscat( tsRow, tsItem );
		wcscat( tsRow, _T("\t") );
	}

	if( IsDlgButtonChecked( hDlg, IDC_CHECK_INSERT_BEFORE ))
		ListView_AddItem( dp->hList, tsRow, _T("\t"), dp->nItem );
	else
		ListView_AddItem( dp->hList, tsRow, _T("\t"), dp->nItem + 1 );

	dp->nItem = ListView_GetSelection( dp->hList );

	return(TRUE);

} /* end: InsertNewRow */

/*FUNCTION_HEADER************************************************
* NAME:		;AddGrapheme
* DESC:		Initiate adding a new grapheme to the dictionary
* IN:			...
* OUT:		n/a
* RETURN:	n/a
* NOTES:		...
*END_HEADER*****************************************************/
BOOL AddGrapheme( HWND hDlg, DICTIONARY_POINTERS *dp )
{
	if( dp->nDict == IDD_EDIT_IDIC )
	{
		int fields[COL_IDIC] = { IDC_EDIT_WORD, IDC_EDIT_DONE, IDC_EDIT_CTL, IDC_EDIT_F2, IDC_EDIT_BNO, IDC_EDIT_PNO, IDC_EDIT_MRU, IDC_EDIT_ACCENT, IDC_EDIT_PRONUNCIATION, IDC_EDIT_PHONEMES };
		if( !InsertNewRow( hDlg, dp, fields, COL_IDIC ))
			return(FALSE);

		dp->nAdditions++;
	}
	else
	if( dp->nDict == IDD_EDIT_TDIC )
	{
		int fields[COL_TDIC] = { IDC_EDIT_WORD, IDC_EDIT_DONE, IDC_EDIT_TYPE, IDC_EDIT_ACCENT, IDC_EDIT_PRONUNCIATION, IDC_EDIT_PHONEMES };
		InsertNewRow( hDlg, dp, fields, COL_TDIC );
		if( !InsertNewRow( hDlg, dp, fields, COL_IDIC ))
			return(FALSE);

		dp->nAdditions++;
	}
	else
	if( dp->nDict == IDD_EDIT_EDIC )
	{
		int fields[COL_EDIC] = { IDC_EDIT_WORD, IDC_EDIT_DONE, IDC_EDIT_FLAG2, IDC_EDIT_MRU, IDC_EDIT_GRCD, IDC_EDIT_ACCENT, IDC_EDIT_PRONUNCIATION, IDC_EDIT_PHONEMES };
		InsertNewRow( hDlg, dp, fields, COL_EDIC );
		if( !InsertNewRow( hDlg, dp, fields, COL_IDIC ))
			return(FALSE);

		dp->nAdditions++;
	}

	return(TRUE);

} /* end: AddGrapheme */

/*FUNCTION_HEADER************************************************
* NAME:		;InsertUpdatedRow
* DESC:		Does actual insertion of updated grapheme data
* IN:			fields: array of edit control IDs
				nFields: number of edit control IDs
* OUT:		n/a
* RETURN:	n/a
* NOTES:		Also, cleanup graphic to shows edited (Done) and non-
				edited graphemes.
*END_HEADER*****************************************************/
BOOL InsertUpdatedRow( HWND hDlg, DICTIONARY_POINTERS *dp, int fields[], int nFields )
{
	TCHAR tsItem[MEDIUM_BUFFER], tsGrapheme[MEDIUM_BUFFER+1];
	int x, nItem;

	for( x = 0; x < nFields; x++ )
	{
		SendDlgItemMessage( hDlg, fields[x], WM_GETTEXT, MEDIUM_BUFFER, (LPARAM)tsItem );
		if( x == FIELD_GRAPHEME && *tsItem == 0 )
			return(FALSE);

		if( x == FIELD_DONE && !wcscmp( tsItem, YES )) // cleanup graphic
		{
			nItem = ListView_ReturnImage( dp->hList, dp->nItem );
			ListView_GetItemText( dp->hList, dp->nItem, 0, tsGrapheme, MEDIUM_BUFFER );
			if( !wcscmp( tsGrapheme, TSPLUSES ))
				ListView_SetImage( dp->hList, dp->nItem, GREENREDBALL );
			else
				ListView_SetImage( dp->hList, dp->nItem, GREENBALL );
		}
		else
		if( x == FIELD_DONE && wcscmp( tsItem, YES ))
		{
			nItem = ListView_ReturnImage( dp->hList, dp->nItem );
			if( nItem == GREENBALL || nItem == GREENREDBALL )
			{
				ListView_GetItemText( dp->hList, dp->nItem, 0, tsGrapheme, MEDIUM_BUFFER );
				if( !wcscmp( tsGrapheme, TSPLUSES ))
					ListView_SetImage( dp->hList, dp->nItem, REDBALL );
				else
					ListView_SetImage( dp->hList, dp->nItem, -1 );
			}
		}

		ListView_SetItemText( dp->hList, dp->nItem, x, tsItem );
	}

	return(TRUE);

} /* end: InsertUpdatedRow */

/*FUNCTION_HEADER************************************************
* NAME:		;UpdateGrapheme
* DESC:		Initiates insertion of updated grapheme data
* IN:			...
* OUT:		n/a
* RETURN:	n/a
* NOTES:		...
*END_HEADER*****************************************************/
BOOL UpdateGrapheme( HWND hDlg, DICTIONARY_POINTERS *dp )
{
	if( dp->nDict == IDD_EDIT_IDIC )
	{
		int fields[COL_IDIC] = { IDC_EDIT_WORD, IDC_EDIT_DONE, IDC_EDIT_CTL, IDC_EDIT_F2, IDC_EDIT_BNO, IDC_EDIT_PNO, IDC_EDIT_MRU, IDC_EDIT_ACCENT, IDC_EDIT_PRONUNCIATION, IDC_EDIT_PHONEMES };
		if( !InsertUpdatedRow( hDlg, dp, fields, COL_IDIC ))
			return(FALSE);
	}
	else
	if( dp->nDict == IDD_EDIT_TDIC )
	{
		int fields[COL_TDIC] = { IDC_EDIT_WORD, IDC_EDIT_DONE, IDC_EDIT_TYPE, IDC_EDIT_ACCENT, IDC_EDIT_PRONUNCIATION, IDC_EDIT_PHONEMES };
		if( !InsertUpdatedRow( hDlg, dp, fields, COL_TDIC ))
			return(FALSE);
	}
	else
	if( dp->nDict == IDD_EDIT_EDIC )
	{
		int fields[COL_EDIC] = { IDC_EDIT_WORD, IDC_EDIT_DONE, IDC_EDIT_FLAG2, IDC_EDIT_MRU, IDC_EDIT_GRCD, IDC_EDIT_ACCENT, IDC_EDIT_PRONUNCIATION, IDC_EDIT_PHONEMES };
		if( !InsertUpdatedRow( hDlg, dp, fields, COL_EDIC ))
			return(FALSE);
	}
	return(TRUE);

} /* end: UpdateGrapheme */

/*FUNCTION_HEADER************************************************
* NAME:		;SetStandardBackgroundColor
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void SetStandardBackgroundColor( HBRUSH *hColor, WPARAM wParam )
{
	if( !(*hColor) )
		*hColor = CreateSolidBrush( GetSysColor( COLOR_BTNFACE ));
	SetBkColor( (HDC)wParam, GetSysColor( COLOR_BTNFACE ));

} /* end: SetStandardBackgroundColor */

/*FUNCTION_HEADER**********************
 * NAME:		;FreeDictionary
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
void FreeDictionary( DICTIONARY_POINTERS *dp )
{
	if( dp->pDictInMem )
	{
		free(dp->pDictInMem);
		dp->pDictInMem = NULL;
	}
} /* end: FreeDictionary */

/*FUNCTION_HEADER************************************************
* NAME:		;LoadDictionaryToEdit
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void LoadDictionaryToEdit( DICTIONARY_POINTERS *dp, int nCount )
{
	char *pcTmp1, *pcTmp2, *pcTab, *pcTmp3;
	char szRow[MAX_BUFFER], szItem[ITEM_BUFFER];
	TCHAR tsRow[MAX_BUFFER*2], tsItem[ITEM_BUFFER];
	int cnt = 0;

	pcTmp1 = dp->pDictionary;

	if( nCount >= 0 ) // load 20000 graphemes from EDIC dictionary (if EDIC dictionary selected )
	{
		char *pc;
		int i;

		for( i = 0, pc = pcTmp1; (pc = strchr(pc, '\n')) != NULL && i < nCount; i++, pc++ )
			;
		pcTmp1 = ++pc;

		if( nCount < 100000 ) // skip resetting dp->pStop on last section
		{
			dp->pStop = pcTmp1;
			for( i = 0, pc = dp->pStop; (pc = strchr(pc, '\n')) != NULL && i < 20000-1; i++, pc++ )
				; // set new stopping point
			dp->pStop = pc;
		}
	}

	dp->pStartEdit = pcTmp1; // since this might have changed (not same as dp->pDictionary)

	SetDlgItemText( dp->hDlg, IDC_STATIC_RED, dp->tsTitle );
	EnableWindow( GetDlgItem( dp->hDlg, IDSTOP ), TRUE );
	*tsRow = 0;
	while( pcTmp1 < dp->pStop )
	{
		if( (pcTmp2 = strstr( pcTmp1, EOL )) != NULL )
		{
			strncpy( szRow, pcTmp1, pcTmp2-pcTmp1 );
			szRow[pcTmp2-pcTmp1] = 0;

			if( !strcmp( szRow, dp->szTitle )) // compensating when printing (title not displayed anywhere -- outside pointer)
			{
				pcTmp1 = &pcTmp2[1];
				continue;
			}

			pcTab = strtok( szRow, TAB );
			while( pcTab )
			{
				if( *tsRow != 0 )
				{
					if( (pcTmp3 = strstr( pcTab, "=" )) != NULL || (pcTmp3 = strstr( pcTab, ":" )) != NULL )
					{
						strcpy( szItem, &pcTmp3[1] );
						if( (pcTmp3 = strstr( szItem, " phon:" )) != NULL )
						{
							memmove( &pcTmp3[0], &pcTmp3[5], strlen(szItem) - 4 );
							*pcTmp3 = *TAB;
						}
						mbstowcs( tsItem, szItem, ITEM_BUFFER );
						wcscat( tsRow, tsItem );
						wcscat( tsRow, _T(TAB) );
					}
				}
				else
				{
					if( !strncmp( szRow, TABS, 3 ))
					{
						wcscpy( tsRow, TSPLUSES ); // accounts for multiple pronunciations
						wcscat( tsRow, _T(TAB) );
						//wcscat( tsRow, _T(SINGLE_SPACE) ); // skip Done column !@#$%
						//wcscat( tsRow, _T(TAB) );
						memmove( &pcTab[0], &pcTab[5], strlen(pcTab)-1 ); // remove "flag2="
						mbstowcs( tsItem, pcTab, GRAPH_BUFFER );
						wcscat( tsRow, tsItem );
						wcscat( tsRow, _T(TAB) );
					}
					else
					{
						strcpy( szItem, pcTab );

						//if( szItem[0] == '­' ) //strstr( szItem, "û" )) //"­û" ))
						if( cnt >= 344 && cnt <= 355 )
							*szItem = *szItem;

						Euc2Utf( szItem, tsItem, ITEM_BUFFER );
						wcscpy( tsRow, tsItem );
						wcscat( tsRow, _T(TAB) );
						//wcscat( tsRow, _T(SINGLE_SPACE) ); // skip Done column !@#$%
						//wcscat( tsRow, _T(TAB) );
					}
				}
				pcTab = strtok( NULL, TAB );
			}
		
			ListView_AddItem( dp->hList, tsRow, _T(TAB), -1 );
			swprintf( tsItem, _T("%d"), ++cnt );
			SetDlgItemText( dp->hDlg, IDC_STATIC_COUNT, tsItem );

			*tsRow = 0;
			pcTmp1 = &pcTmp2[1]; // get next grapheme

			if( cnt < 20 ) // windows stuff so listview control doesn't blank out while being loaded
			{
				UpdateWindow( dp->hList );
			}

			if( ButtonClicked( GetDlgItem( dp->hDlg, IDSTOP ))) // user clicked stop button
				break;
		}
	}
	SetDlgItemText( dp->hDlg, IDC_STATIC_RED, _T("") );
	EnableWindow( GetDlgItem( dp->hDlg, IDSTOP ), FALSE );

} /* end: LoadDictionaryToEdit */

/*FUNCTION_HEADER************************************************
* NAME:		;EdicDlgProc
* DESC:		
* IN:			
* OUT:		
* RETURN:	
				
* NOTES:		
*END_HEADER*****************************************************/
LRESULT CALLBACK EdicDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	LOGFONT lf;
	static HBRUSH hColor;
	static HFONT hFont = NULL;
	static int nSec;
	
	switch ( message )
	{
	case WM_INITDIALOG:
		InitializeFont( hDlg, 17, SHIFTJIS_CHARSET, _T("MS Sans Serif"), &lf );
		hFont = CreateFontIndirect( &lf );
		EnumChildWindows( hDlg, (WNDENUMPROC)EnumControls, (LPARAM)(HFONT)hFont ); // set fonts
		hColor = NULL;
		nSec = 0;
		break;
		
	case WM_CTLCOLORSTATIC:
			SetStandardBackgroundColor( &hColor, wParam );
			if( (HWND)lParam == GetDlgItem( hDlg, IDC_STATIC_TITLE ))
				SetTextColor( (HDC)wParam, RGB( 0, 0, 255 ) ); // blue text
			return( (LRESULT)hColor );

	case WM_CLOSE:
		PostMessage( hDlg, WM_COMMAND, IDCANCEL, 0 );
		break;
		
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_RADIO_SEC1:
			case IDC_RADIO_SEC2:
			case IDC_RADIO_SEC3:
			case IDC_RADIO_SEC4:
			case IDC_RADIO_SEC5:
			case IDC_RADIO_SEC6:
				nSec = (int)LOWORD(wParam);
				break;

			case IDOK:
				if( nSec > 0 )
				{
					DeleteObject( hColor );
					DeleteObject( hFont );
					EndDialog( hDlg, nSec );
				}
				else
					MessageBox( hDlg, _T("Select a section, then click Start.   "), _T("NOTICE..."), MB_OK | MB_ICONINFORMATION );
				break;

			case IDCANCEL:
				DeleteObject( hColor );
				DeleteObject( hFont );
				EndDialog( hDlg, 0 );
				break;;
			}
		}
	}
	
	return FALSE;
	
} /* end: EdicDlgProc */

/*FUNCTION_HEADER************************************************
* NAME:		;DisplayFields
* DESC:		Displays grapheme data to update
* IN:			fields: array of edit control IDs
				nFields: number of edit control IDs
* OUT:		n/a
* RETURN:	n/a
* NOTES:		...
*END_HEADER*****************************************************/
void DisplayFields( HWND hDlg, DICTIONARY_POINTERS *dp, int fields[], int nFields )
{
	TCHAR tsItem[MEDIUM_BUFFER];
	TCHAR tsItem2[MEDIUM_BUFFER];
	unsigned char szItem[MEDIUM_BUFFER];
	unsigned char graphcode[500];
	unsigned char temps[50];
	int i;
	int x;
	
	for( x = 0; x < nFields; x++ )
	{
		ListView_GetItemText( dp->hList, dp->nItem, x, tsItem, MEDIUM_BUFFER );
		SendDlgItemMessage( hDlg, fields[x], WM_SETTEXT, MEDIUM_BUFFER, (LPARAM)tsItem );
		if( x == FIELD_GRAPHEME && !wcscmp( tsItem, TSPLUSES )) // don't edit multiple pronunciation marker
		{
			SendDlgItemMessage( hDlg, fields[x], EM_SETREADONLY, TRUE, 0 );	
		}
		else
		if (x == FIELD_GRAPHEME )
		{
			Utf2Euc(tsItem,szItem,MEDIUM_BUFFER);
			i=0;
			graphcode[0]='\0';
			while (szItem[i])
			{
				sprintf(temps,"%02X:%c ",szItem[i],szItem[i]);
				strcat(graphcode,temps);
				i++;
			}
			//MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,graphcode,strlen(graphcode),tsItem2,MEDIUM_BUFFER);
			mbstowcs( tsItem2, graphcode, MEDIUM_BUFFER );
			SendDlgItemMessage(hDlg, IDC_GRAPHEMECODE ,WM_SETTEXT, 0, (LPARAM)tsItem2);
		}
		else
		if( x == FIELD_DONE && !wcscmp( tsItem, YES ))
		{
			CheckDlgButton( hDlg, IDC_CHECK_DONE, TRUE );
		}
	}
} /* end: DisplayFields */

/*FUNCTION_HEADER************************************************
* NAME:		;GetFieldsToEdit
* DESC:		Initiate getting grapheme data to update
* IN:			...
* OUT:		n/a
* RETURN:	n/a
* NOTES:		...
*END_HEADER*****************************************************/
void GetFieldsToEdit( HWND hDlg, DICTIONARY_POINTERS *dp )
{
	if( dp->nDict == IDD_EDIT_IDIC )
	{
		int fields[COL_IDIC] = { IDC_EDIT_WORD, IDC_EDIT_DONE, IDC_EDIT_CTL, IDC_EDIT_F2, IDC_EDIT_BNO, IDC_EDIT_PNO, IDC_EDIT_MRU, IDC_EDIT_ACCENT, IDC_EDIT_PRONUNCIATION, IDC_EDIT_PHONEMES };
		DisplayFields( hDlg, dp, fields, COL_IDIC );
	}
	else
	if( dp->nDict == IDD_EDIT_TDIC )
	{
		int fields[COL_TDIC] = { IDC_EDIT_WORD, IDC_EDIT_DONE, IDC_EDIT_TYPE, IDC_EDIT_ACCENT, IDC_EDIT_PRONUNCIATION, IDC_EDIT_PHONEMES };
		DisplayFields( hDlg, dp, fields, COL_TDIC );
	}
	else
	if( dp->nDict == IDD_EDIT_EDIC )
	{
		int fields[COL_EDIC] = { IDC_EDIT_WORD, IDC_EDIT_DONE, IDC_EDIT_FLAG2, IDC_EDIT_MRU, IDC_EDIT_GRCD, IDC_EDIT_ACCENT, IDC_EDIT_PRONUNCIATION, IDC_EDIT_PHONEMES };
		DisplayFields( hDlg, dp, fields, COL_EDIC );
	}
} /* end: GetFieldsToEdit */

/*FUNCTION_HEADER************************************************
* NAME:		;EditFieldsProc
* DESC:		...
* IN:			...
* OUT:		...
* RETURN:	...
* NOTES:		User clicked Add or Update button (main interface)
*END_HEADER*****************************************************/
LRESULT CALLBACK EditFieldsProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	LOGFONT lf;
	static HBRUSH hColor;
	static HFONT hFont = NULL;
	static DICTIONARY_POINTERS *dp;
	
	switch ( message )
	{
	case WM_INITDIALOG:
		InitializeFont( hDlg, 17, SHIFTJIS_CHARSET, _T("MS Sans Serif"), &lf );
		hFont = CreateFontIndirect( &lf );
		EnumChildWindows( hDlg, (WNDENUMPROC)EnumControls, (LPARAM)(HFONT)hFont ); // set fonts

		hColor = NULL;

		dp = (DICTIONARY_POINTERS *)lParam;

		if( dp->nAction == IDUPDATE ) // edit existing word
			GetFieldsToEdit( hDlg, dp );
		else
		if( dp->nAction == IDADD ) // add new word after selected word in listview control
		{
			if( dp->nDict == IDD_EDIT_IDIC )
				SetWindowText( hDlg, _T("Add IDIC grapheme") );
			else
			if( dp->nDict == IDD_EDIT_TDIC )
				SetWindowText( hDlg, _T("Add TDIC grapheme") );
			else
			if( dp->nDict == IDD_EDIT_EDIC )
				SetWindowText( hDlg, _T("Add EDIC grapheme") );

			SetDlgItemText( hDlg, IDOK, _T("Add") );
			SetFocus( GetDlgItem( hDlg, IDC_EDIT_WORD ));
		}
		break;
		
	case WM_CTLCOLORSTATIC:
			SetStandardBackgroundColor( &hColor, wParam );
			if( (HWND)lParam == GetDlgItem( hDlg, IDC_STATIC_TITLE ))
				SetTextColor( (HDC)wParam, RGB( 0, 0, 255 ) ); // blue text
			return( (LRESULT)hColor );

	case WM_CLOSE:
		PostMessage( hDlg, WM_COMMAND, IDCANCEL, 0 );
		break;
		
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_CHECK_DONE:
				if( IsDlgButtonChecked( hDlg, IDC_CHECK_DONE ))
					SetDlgItemText( hDlg, IDC_EDIT_DONE, YES );
				else
					SetDlgItemText( hDlg, IDC_EDIT_DONE, DOTS );
				break;

			case IDOK:
				if( dp->nAction == IDUPDATE )
				{
					if( !UpdateGrapheme( hDlg, dp ))
					{
						MessageBox( hDlg, _T("The grapheme field cannot be blank.   "), _T("ERROR..."), MB_OK | MB_ICONEXCLAMATION );
						SetFocus( GetDlgItem( hDlg, IDC_EDIT_WORD ));
						break;
					}
					else
					if( !dp->bDictionaryChanged )
						dp->bDictionaryChanged = TRUE;
				}
				else
				if( dp->nAction == IDADD )
				{
					if( !AddGrapheme( hDlg, dp ))
					{
						MessageBox( hDlg, _T("The grapheme field cannot be blank.   "), _T("ERROR..."), MB_OK | MB_ICONEXCLAMATION );
						SetFocus( GetDlgItem( hDlg, IDC_EDIT_WORD ));
						break;
					}
					else
					if( !dp->bDictionaryChanged )
						dp->bDictionaryChanged = TRUE;
				}

			case IDCANCEL:
				DeleteObject( hColor );
				DeleteObject( hFont );
				EndDialog( hDlg, 0 );
				break;;
			}
		}
	}
	
	return FALSE;
	
} /* end: EditFieldsProc */

/*FUNCTION_HEADER************************************************
* NAME:		;MainDlgProc
* DESC:		
* IN:			
* OUT:		
* RETURN:	
				
* NOTES:		
*END_HEADER*****************************************************/
LRESULT CALLBACK MainDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	INITCOMMONCONTROLSEX iccex;
	//static CHOOSEFONT cf;
	LOGFONT lf;
	static HBRUSH hColor;
	static HBITMAP hBitmap;
	static HFONT hFont = NULL;
	static HWND hList;
	int nItem;
	static DICTIONARY_POINTERS dp;
	NMLISTVIEW* pGNM;
	int image[NMB_BITMAPS] = { IDB_BITMAP_REDBALL, IDB_BITMAP_GREENBALL, IDB_BITMAP_GREENRED };
	static HIMAGELIST himl;
	HBITMAP	hbmp;

#ifdef CONVERT
	TCHAR tsComputerName[SMALL_BUFFER];
	DWORD dwcNameSize;
#endif

	switch ( message )
	{
	case WM_INITDIALOG:
		{
			iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
			iccex.dwICC = ICC_COOL_CLASSES;
			InitCommonControlsEx(&iccex);

			hBitmap = LoadBitmap( g_hInst, MAKEINTRESOURCE(IDB_BITMAP_FOLDER) );
			SendDlgItemMessage( hDlg, IDC_BUTTON_DIR, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap );

			InitializeFont( hDlg, 17, SHIFTJIS_CHARSET, _T("MS Sans Serif"), &lf );
			hFont = CreateFontIndirect( &lf );

			EnumChildWindows( hDlg, (WNDENUMPROC)EnumControls, (LPARAM)(HFONT)hFont ); // set fonts

			dp.hList = hList = GetDlgItem( hDlg, IDC_LIST1 );
			if( hList )
			{
				SetupListviewIDIT( hDlg, hList );
				himl = ImageList_Create( 8, 13, ILC_COLOR24, 2, 0 );
				ListView_SetImageList( hList, himl, LVSIL_SMALL );
				for( nItem = 0; nItem < NMB_BITMAPS; nItem++ )
				{
					hbmp = LoadBitmap( g_hInst, MAKEINTRESOURCE( image[nItem] ));
					ImageList_Add( himl, hbmp, (HBITMAP)NULL );
					DeleteObject( hbmp );
				}
			}

			dp.hDlg = hDlg;
			dp.pDictInMem = NULL;
			dp.bDictionaryChanged = FALSE;
			hColor = NULL;

#ifdef CONVERT
			dwcNameSize = SMALL_BUFFER;
			GetComputerName( tsComputerName, &dwcNameSize );
			if( !wcscmp( tsComputerName, _T("FELIX") )) // even if CONVERT defined only display on my laptop
			{
				ShowWindow( GetDlgItem( hDlg, IDC_BUTTON_CONVERT ), TRUE );
			}
#endif
		}
		break;
		
	case WM_CTLCOLORSTATIC:
			SetStandardBackgroundColor( &hColor, wParam );
			if( (HWND)lParam == GetDlgItem( hDlg, IDC_STATIC_RED ))
			{
				SetTextColor( (HDC)wParam, RGB( 255, 0, 0 ) ); // red text
			}
			else
			if( (HWND)lParam == GetDlgItem( hDlg, IDC_STATIC_TITLE )
				|| (HWND)lParam == GetDlgItem( hDlg, IDC_STATIC_GRAPHEME )
				|| (HWND)lParam == GetDlgItem( hDlg, IDC_STATIC_ACCENT )
				|| (HWND)lParam == GetDlgItem( hDlg, IDC_STATIC_PRONUNCIATION ))
			{
				SetTextColor( (HDC)wParam, RGB( 0, 0, 255 ) ); // blue text
			}
			return( (LRESULT)hColor );

	case WM_CLOSE:
		PostMessage( hDlg, WM_COMMAND, IDCANCEL, 0 );
		break;
		
	case WM_NOTIFY:
		if( wParam == IDC_LIST1 ) // display grapheme to update
		{
			pGNM = (NMLISTVIEW*)lParam;
			if( pGNM->hdr.code == LVN_ITEMACTIVATE ) // double click
			{
				PostMessage( hDlg, WM_COMMAND, IDUPDATE, 0 );
			}
			/*if( (nItem = ListViewSelection( lParam )) > -1 )
			{
				
			}*/
		}
		break;
				
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
#ifdef CONVERT
			case IDC_BUTTON_CONVERT:
				ConvertOnseiDictionary( hDlg );
				break;
#endif
			case IDC_RADIO_IDIC: // internal dictionary
				CheckForChanges( &dp );
				if( dp.pDictInMem )
				{
					SendDlgItemMessage( hDlg, IDC_STATIC_TITLE, WM_SETTEXT, 0, (WPARAM)_T("DECOMPILED INTERNAL DICTIONARY") );
					DeleteAllColumns( hDlg, hList );
					SetupListviewIDIT( hDlg, hList );
					wcscpy( dp.tsTitle, _T("Loading internal dictionary...") );
					strcpy( dp.szTitle, "Internal dictionary" );
					dp.pDictionary = dp.pInternalDictionary;
					dp.pStop = dp.pTanKanji;
					LoadDictionaryToEdit( &dp, -1 );
					dp.nDict = IDD_EDIT_IDIC;
					dp.nDeletions = 0;
					dp.nAdditions = 0;
				}
				else
				if( IsDlgButtonChecked( hDlg, IDC_RADIO_IDIC ))
				{
					CheckDlgButton( hDlg, IDC_RADIO_IDIC, FALSE );
					MessageBox( hDlg, _T("Load the Japanese dictionary to memory.   "), _T("NOTICE..."), MB_OK | MB_ICONINFORMATION );
				}
				break;

			case IDC_RADIO_TDIC: // Kanji dictionary
				CheckForChanges( &dp );
				if( dp.pDictInMem )
				{
					SendDlgItemMessage( hDlg, IDC_STATIC_TITLE, WM_SETTEXT, 0, (WPARAM)_T("DECOMPILED KANJI DICTIONARY") );
					DeleteAllColumns( hDlg, hList );
					SetupListviewTDIT( hDlg, hList );
					wcscpy( dp.tsTitle, _T("Loading Kanji dictionary...") );
					strcpy( dp.szTitle, "Tan-Kanji" );
					dp.pDictionary = dp.pTanKanji;
					dp.pStop = dp.pExternalDictionary;
					LoadDictionaryToEdit( &dp, -1 );
					dp.nDict = IDD_EDIT_TDIC;
					dp.nDeletions = 0;
					dp.nAdditions = 0;
				}
				else
				if( IsDlgButtonChecked( hDlg, IDC_RADIO_TDIC ))
				{
		
					CheckDlgButton( hDlg, IDC_RADIO_TDIC, FALSE );
					MessageBox( hDlg, _T("Load the Japanese dictionary to memory.   "), _T("NOTICE..."), MB_OK | MB_ICONINFORMATION );
				}
				break;

			case IDC_RADIO_EDIC: // external dictionary
				CheckForChanges( &dp );
				if( dp.pDictInMem )
				{
					int nSec = DialogBox( g_hInst, MAKEINTRESOURCE( IDD_EDIC ), NULL, (DLGPROC)EdicDlgProc );
					DeleteAllColumns( hDlg, hList ); // delete all columns regardless since Cancel is a possibility
					SetupListviewEDIT( hDlg, hList );
					if( nSec )
					{
						TCHAR tsInfo[MEDIUM_BUFFER];
						int nCount;
						switch( nSec )
						{
						case IDC_RADIO_SEC1: nCount = 1; wcscpy( tsInfo, _T("Section 1 displayed")); break;
						case IDC_RADIO_SEC2: nCount = 20000; wcscpy( tsInfo, _T("Section 2 displayed")); break;
						case IDC_RADIO_SEC3: nCount = 40000; wcscpy( tsInfo, _T("Section 3 displayed")); break;
						case IDC_RADIO_SEC4: nCount = 60000; wcscpy( tsInfo, _T("Section 4 displayed")); break;
						case IDC_RADIO_SEC5: nCount = 80000; wcscpy( tsInfo, _T("Section 5 displayed")); break;
						case IDC_RADIO_SEC6: nCount = 100000; wcscpy( tsInfo, _T("Section 6 displayed")); break;
						}
						SendDlgItemMessage( hDlg, IDC_STATIC_TITLE, WM_SETTEXT, 0, (WPARAM)_T("DECOMPILED EXTERNAL DICTIONARY") );
						wcscpy( dp.tsTitle, _T("Loading external dictionary...") );
						strcpy( dp.szTitle, "External dictionary" );
						dp.pDictionary = dp.pExternalDictionary;
						dp.pStop = dp.pEndDict;
						LoadDictionaryToEdit( &dp, nCount );
						SetDlgItemText( hDlg, IDC_STATIC_RED, tsInfo );
						dp.nDict = IDD_EDIT_EDIC;
						dp.nDeletions = 0;
						dp.nAdditions = 0;
					}
				}
				else
				if( IsDlgButtonChecked( hDlg, IDC_RADIO_EDIC ))
				{
					CheckDlgButton( hDlg, IDC_RADIO_EDIC, FALSE );
					MessageBox( hDlg, _T("Load the Japanese dictionary to memory.   "), _T("NOTICE..."), MB_OK | MB_ICONINFORMATION );
				}
				break;

			case IDC_BUTTON_DIR: // retrieve dictionary
				{
					TCHAR tsFilename[MAX_PATH+1];
					if( GetFilename( hDlg, tsFilename ))
					{
						SendDlgItemMessage( hDlg, IDC_EDIT1, WM_SETTEXT, MAX_PATH, (LPARAM)tsFilename );
						FreeDictionary( &dp );
						DeleteDictionaryItems( &dp );
					}
				}
				break;
				
			case IDLOAD: // load dictionary to memory
				{
					BOOL bDeleteItems;
					if( lParam == 0 )
						bDeleteItems = FALSE;
					else
						bDeleteItems = TRUE;

					if( dp.pDictInMem )
					{
						FreeDictionary( &dp );
						if( lParam > 0 )
						{
							SendDlgItemMessage( hDlg, IDC_STATIC_TITLE, WM_SETTEXT, 0, (WPARAM)_T("LOAD THE JAPANESE DICTIONARY TO MEMORY") );
							DeleteAllColumns( hDlg, hList );
							SetupListviewIDIT( hDlg, hList );
						}
					}
					if( !LoadDictionaryToMemory( &dp, bDeleteItems ))
						MessageBox( hDlg, _T("Unable to load dictionary to memory.   "), _T("ERROR..."), MB_OK | MB_ICONSTOP );
				}
				break;

			case IDSAVE:
				if( SaveDictionary( &dp ))
				{
					dp.bDictionaryChanged = FALSE;
					if( lParam == 0 )
						SetEvent( ghMemUpdateEvent );
				}
				break;

			case IDRECOMPILE:
				Myreonsei( hDlg, hList );
				break;

			case IDADD: // add new grapheme
				if( ( dp.nItem = ListView_GetSelection( hList )) > -1 )
				{
					dp.nAction = IDADD;
					DialogBoxParam( g_hInst, MAKEINTRESOURCE( dp.nDict ), NULL, (DLGPROC)EditFieldsProc, (LPARAM)&dp );
				}
				else
					MessageBox( hDlg, _T("Select a grapheme to begin.\n\nNew graphemes are inserted after the selected item.  "), _T("NOTICE..."), MB_OK | MB_ICONINFORMATION );
				break;

			case IDUPDATE: // update graphemem
				if( ( dp.nItem = ListView_GetSelection( hList )) > -1 )
				{
					dp.nAction = IDUPDATE;
					DialogBoxParam( g_hInst, MAKEINTRESOURCE( dp.nDict ), NULL, (DLGPROC)EditFieldsProc, (LPARAM)&dp );
				}
				else
					MessageBox( hDlg, _T("Select a grapheme to begin.   "), _T("NOTICE..."), MB_OK | MB_ICONINFORMATION );
				break;

			case IDDELETE: // delete grapheme
				if( (nItem = ListView_GetSelection( hList )) > -1 )
				{
					int ans = MessageBox( hDlg, _T("Delete selected grapheme?   "), _T("QUESTION..."), MB_YESNO | MB_ICONQUESTION );
					if( ans == IDYES )
					{
						ListView_DeleteItem( hList, nItem );
						dp.nDeletions++;
						if( !dp.bDictionaryChanged )
							dp.bDictionaryChanged = TRUE;
					}
				}
				else
					MessageBox( hDlg, _T("Select a grapheme to delete.   "), _T("ERROR..."), MB_OK | MB_ICONEXCLAMATION );
				break;

			case IDCANCEL:
				CheckForChanges( &dp );
				ImageList_Destroy( himl );
				FreeDictionary( &dp );
				DeleteObject( hColor );
				DeleteObject( hFont );
				DeleteObject( hBitmap );
				EndDialog( hDlg, 0 );
				break;;
			}
		}
	}
	
	return FALSE;
	
} /* end: MainDlgProc */

/*FUNCTION_HEADER************************************************
* NAME:		;WinMain
* DESC:		
* IN:			
* OUT:		
* RETURN:	
				
* NOTES:		
*END_HEADER*****************************************************/
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	g_hInst = hInstance;

	DialogBox( hInstance, MAKEINTRESOURCE( IDD_MAIN ), NULL, (DLGPROC)MainDlgProc );
	return(TRUE);
	
} /* end: WinMain */

