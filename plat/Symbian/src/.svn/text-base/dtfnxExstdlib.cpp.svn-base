/**************************************************************************
**                                                                        *
**  FILE        :  dtfnxexstdlib.cpp                                        *
**                                                                        *
**  DESCRIPTION :  Source file for SYMBIAN specific functions             *
**                                                                        *
** 																		  *
**                                                                        *
**************************************************************************/

#include <sys/stat.h>
#include <sys/dirent.h>
#include "DtFnxStdlib.h"
#include "Dtfnxexstdlib.h"
#include <e32std.h>
#include <string.h>
#include <ctype.h>

#define _A_SUBDIR	1
#define _A_FILE		2
#define _A_UNKNOWN	3

struct _finddata_t {
  int attrib;
  char name[MAX_PATH];
  char path[MAX_PATH];
};

#ifdef FNX_BUILD_SLEEP
/***************************************************
 *  NAME:	sleep
 *  DESC:	Put the processor into doze mode for the specified number of milliseconds.
 *  IN:		delay - how long to delay
 *  OUT:	<none>
 *  RETURN:	<none>
 ***************************************************/
void fnxasleep(int delay)
{
	TTimeIntervalMicroSeconds32 delayinms;
	
	delayinms = delay*100;
	User::After(delayinms);
}
#endif

long _findfirst(char *dname,struct _finddata_t * /*FileData*/)
{
	int flag;
//	DIR *fddir;
//	int len;
	struct stat statbuf;
//	struct dirent *dent;
	// --- is this a directory?
	flag=stat(dname,&statbuf);
	if(flag<0) return -1;
// ... below is temporary fix, need to make this fix more generic for all cases!!
//mwh  if(! ((S_IFDIR & statbuf.st_mode) == S_IFDIR) ) return -1;
	if(((S_IFREG & statbuf.st_mode) == S_IFREG) || ((S_IFLNK & statbuf.st_mode) == S_IFLNK)) return 0;
	else return -1;
//mwh_end
/*	fddir=opendir(dname);
	if(!fddir) return -1;
	// --- is an OK directory, now find the first entry.
	FNX_STRCPY(FileData->path,dname);
	len=FNX_STRLEN(FileData->path);
	if(FileData->path[len-1]!='/')
	{
		FileData->path[len]='/';
		FileData->path[len+1]='\0';
	}
	if(_findnext((long)fddir,FileData)<0) return -1;
	return(long)fddir;*/
}

int _findnext(long FileId,struct _finddata_t *FileData)
{
	int flag;
	DIR *fddir;
	char pfname[1024];
	struct dirent *dent;
	struct stat statbuf;
	// --- find the next entry.
	fddir = (DIR*)FileId;
	dent = readdir(fddir);
	if(!dent) 
		return -1;

	FNX_STRCPY(pfname, FileData->path);
	FNX_STRCAT(pfname, dent->d_name);

	flag = stat(pfname,&statbuf);
	if(flag<0) 
		return -1;

	FNX_STRCPY(FileData->name, dent->d_name);
	if((S_IFDIR & statbuf.st_mode) == S_IFDIR)
	{
		FileData->attrib=_A_SUBDIR;
	}
	else if(((S_IFREG & statbuf.st_mode) == S_IFREG) ||
			((S_IFLNK & statbuf.st_mode) == S_IFLNK))
	{
		FileData->attrib=_A_FILE;
	}
	else
	{
		FileData->attrib=_A_UNKNOWN;
	}
	return 0;  // AOK
}

long _findclose(long FileId)
{
	if(!FileId)	return 0;
	closedir((DIR*)FileId);
	
	return 0;
}
long _filelength( int filedes )
{
    int rc;
    int file_size=0;
    struct stat buf;
    if(filedes != -1)
    {
        rc=fstat(filedes, &buf);
        if(rc != -1)
            file_size=buf.st_size;
    }
    return file_size;
}

/*FUNCTION_HEADER**********************
 * NAME:		;strupr
 * DESC: 	Makes up for mistakenly using this nonstandard Windows
		function for UNIX systems.
 * OUT:		n/a
 * RETURN:	returns the same pointer value that is passed in.
 *END_HEADER***************************/
/*char *_strupr(char *str) {
  char *ptr;
  ptr=str;  
  while(*ptr != '\0') {
        *ptr = toupper(*ptr);
        ptr++;
  }
  return str;
}*/

int stricmp(const char *string1, const char *string2)
{
	int cnt;
	int len1=FNX_STRLEN(string1);
	int len2=FNX_STRLEN(string2);

	for (cnt = 0; cnt < len1; cnt++) 
	{
		if (toupper(string1[cnt]) < toupper(string2[cnt]))	return -1;
		if (toupper(string1[cnt]) > toupper(string2[cnt]))	return 1;
	}
	if (cnt < len2)		return -1;
	if (cnt > len2)		return 1;
	return 0;
}

wchar_t *wcschr( const wchar_t *string, int c )
{
	wchar_t* result = NULL;
	
	result = (wchar_t*)string;
	while(result && result[0])
	{
		if(result[0] == c)
			break;
		
		result++;
	}

	return result;
}

wchar_t *wcstok_r(wchar_t *s, const wchar_t *delim, wchar_t **lasts)
{
	const wchar_t *spanp;
	int c, sc;
	wchar_t *tok;

	if (s == NULL && (s = *lasts) == NULL)
		return (NULL);

	/*
	* Skip (span) leading delimiters (s += wcscspn(s, delim), sort of).
	*/
	cont:
	c = *s++;
	for (spanp = delim; (sc = *spanp++) != 0;) 
	{
		if (c == sc)
		goto cont;
	}

	if (c == 0) 
	{		/* no non-delimiter characters */
		*lasts = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	* Scan token (scan for delimiters: s += wcscspn(s, delim), sort of).
	* Note that delim must have one NULL; we stop if we see that, too.
	*/
	for (;;) 
	{
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) 
			{
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				*lasts = s;
				return (tok);
			}
		} while (sc != 0);
	}
	return NULL;
}

wchar_t * wcsstr(const wchar_t *str, const wchar_t *srch)
{
    const wchar_t *p1, *p2;
    size_t i, n;
    wchar_t c1, c2;

    p2 = srch;
    while (*p2++ != '\0')
	;

    n = p2 - srch - 1;
    if (n != 0) {
	--n;
	c2 = *srch++;

	while ((c1 = *str++) != '\0') {
	    if (c1 == c2) {
		p1 = str;
		p2 = srch;
		if ((i = n) != 0) {
		    do {
			if (*p1++ != *p2++)
			    goto notequal;
		    } while (--i != 0);
		}
		return (wchar_t *)str - 1;
	    }
	notequal:
	;
	}
	return NULL;
    }
    return (wchar_t *)str;
}

wchar_t* fgetws(wchar_t* pwcz, int n, FILE* pFile)
{
	ASSERT(pwcz != NULL);

	wchar_t c;
	wchar_t* wszWrite = pwcz;
	int numread;

	do 
	{
		numread = fread( &c, sizeof(wchar_t), 1, pFile );
		if (numread == 0)
		{
			//Reached end of file data.
			*(wszWrite++) = '\0';	//null terminate string
			break;
		}
		*(wszWrite++) = c;
		--n;
	} while (c != 0 && n > 0);

	return pwcz;
}

#ifdef __cplusplus
extern "C" {
#endif

void*	epocmalloc ( size_t size )
{	
	return User::Alloc(size);
}

void*	epoccalloc ( size_t nel, size_t size )
{
	void*	 result;

	size *= nel;
	result = epocmalloc( size );

	if	( result )
	{
		memset( result, '\0', size );
	}
	else
		User::LeaveNoMemory();
	return result;
}

void	epocfree ( void* mem )
{
	User::Free(mem);
}

void*	epocrealloc ( void* mem, size_t newsize )
{
	return User::ReAlloc(mem,newsize);
}

#ifdef __cplusplus
}
#endif