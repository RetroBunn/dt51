#ifndef __GUI_H
#define __GUI_H

#define MAX_BUFFER 1024
#define MEDIUM_BUFFER 128
#define GRAPH_BUFFER 100
#define ITEM_BUFFER 200
#define SMALL_BUFFER 25
#define FIELD_GRAPHEME 0
#define FIELD_DONE 1
#define REDBALL 0
#define GREENBALL 1
#define GREENREDBALL 2
#define NMB_BITMAPS 3
#define SINGLE_SPACE " "
#define TAB "\t"
#define EOL "\n"
#define RETURN "\r"
#define COL_IDIC 10 // number of colum in internal dictionary
#define COL_TDIC 6  // number of columsn in Kanji dictionary
#define COL_EDIC 8  // number of columns in external dictionary
#define TABS "\t\t\t" // detect multiple pronunciations
#define GRAPHEME _T("+++++") // grapheme replacement when multiple pronunciations
#define YES _T("YES")
#define NO _T("NO")
#define INTERNAL "Internal dictionary"
#define KANJI "Tan-Kanji"
#define EXTERNAL "External"
#define PLUSES "+++"
#define TSPLUSES _T("+++")
#define DOTS _T("...")

typedef struct _DICTIONARY_POINTERS
{
	char *pDictInMem; // dictionary held in memory
	char *pInternalDictionary; // pointer to start of internal dictionary
	char *pTanKanji; // ditto Kanji dictionary
	char *pExternalDictionary; // ditto external dictionary
	char *pEndDict; 

	char *pStartEdit; // line in dictionary where editing starts

	char *pDictionary; // starting point of dictionary section to be edited
	char *pStop; // ending point of dictionary section to be edited
	char	szTitle[GRAPH_BUFFER]; // Windows user info
	TCHAR tsTitle[GRAPH_BUFFER]; // ditto
	int	nLineCount; // not used
	int	nDeletions;
	int	nAdditions;

	// edit field information
	HWND hDlg;
	HWND hList;
	int  nItem;
	int  nAction;
	int  nDict;
	BOOL bDictionaryChanged;

} DICTIONARY_POINTERS;

#endif
