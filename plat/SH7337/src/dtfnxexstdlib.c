////#include <stdio.h>
#include "port.h"
#include <stdlib.h>
#include <limits.h>

#include "filectrl.h"
#include "ttslib.h"

/***************************************************
 *  NAME:	fopen
 *  DESC:	Opens the file specified by filename
 *  IN:		pName	- file name
 *			pFlags	- type of access requested
 *  OUT:	<none>
 *  RETURN:	FILE pointer if successful, NULL otherwise
 *  NOTES:	(8/18/98) Supports "r", "r+", "w", "w+",
 *			and "a". Ignores "b", "t", "c" and "n".
 *			Only MAX_FILES (48) files can be created
 *			since they are still in memory after being
 *			closed.  Files that are STATIC can only be
 *			opened for reading.
 ***************************************************/
void *fnxfopen(const char *pName, const char *pFlags)
{
//	DWORD			mode;
	int			mode;
	int				handle;

//	if (*pFlags == 'r')
//	{
//		mode = _OPENMODE_READ;
//	}
//	else if (*pFlags == 'w')
//	{
//		mode = _OPENMODE_READWRITE;
//	}
	
//	handle = BSfile_OpenFile( pName, mode );
	handle = TTSLIB_Open( 1,pName); 

	return (void *)handle;
	
}


/***************************************************
 *  NAME:	fflush
 *  DESC:	flushes the specified stream
 *  IN:		pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns 0 if successful
 *  NOTES:	(8/18/98) If the stream was open for writing
			the memory location and len are updated in the
			file map.
 ***************************************************/
int fnxfflush(void *pStream)
{
	BSfile_FlushFile((int)pStream);
	return 0;
}

/***************************************************
 *  NAME:	fclose
 *  DESC:	Closes the specified stream
 *  IN:		pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns 0 if successful
 *  NOTES:	(8/18/98) If the stream was open for writing
			the memory location and len are updated in the
			file map.
 ***************************************************/
int fnxfclose(void *pStream)
{
//	BSfile_CloseFile((int)pStream);
	TTSLIB_Close((int)pStream);
	return 0;
}


/***************************************************
 *  NAME:	fread
 *  DESC:	Reads data from a stream
 *  IN:		pBuf	- storage location for data
 *			size	- item size in bytes
 *			pos	- position
 *			pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns the number of full items actually read
 ***************************************************/
//unsigned long fnxfread(void *pBuf,unsigned long size,unsigned long count,unsigned long pos,void *pStream)
unsigned long fnxfread(void *pBuf,unsigned long size,unsigned long count,void *pStream)

{

	unsigned long nBytesRead;

	nBytesRead = 0;
	if (pStream == NULL)
		return 0;
	if (count ==0 || size ==0)
		return 0;
//	nBytesRead = BSfile_ReadFile((int)pStream, pBuf,count*size,pos); 
	nBytesRead = TTSLIB_Read((int)pStream,pBuf,count*size,-1) ;			
//	return nBytesRead/size;
	return nBytesRead/size;
}

/***************************************************
 *  NAME:	fwrite
 *  DESC:	Writes data to a stream
 *  IN:		pBuf	- pointer to data to be written
 *			size	- item size in bytes
 *			count	- maximum number of items to be written
 *			pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns the number of full items actually written
 ***************************************************/
unsigned long fnxfwrite(const void *pBuf,
			 unsigned long size,
			 unsigned long count,
			 FILE *pStream)
{

	return 0;
}

/***************************************************
 *  NAME:	fseek
 *  DESC:	Moves the file pointer to a specified location
 *  IN:		pStream	- pointer to FILE structure
 *			offset	- number of bytes from origin
 *			origin	- initial position
 *  OUT:	<none>
 *  RETURN:	returns 0 if successful
 ***************************************************/
int fnxfseek(void *pStream,
		  long offset,
		  int origin)
{
	int position;

	position = offset;

	BSfile_SeekFile((int)pStream,position);

	return 0;
}

char *fnxafgets( char *string, int n, void *stream )
{
	int i=0;
	size_t ret=0;
	for( ; i<n; i++)
	{
		ret = fnxfread( &string[i], 1, 1, stream );
		if( !ret )
			return NULL;
		if( '\n' == string[i] ||
			  '\0' == string[i] )
			break;
	}
	if( i < n-1 )
		string[i+1] = '\0';
	else
		if( i == n )
			string[i] = '\0';

	return string;
}

#ifndef _stricmp
int _stricmp(const char *string1, const char *string2)
{
	int cnt;
	int len1=FNX_STRLEN(string1);
	int len2=FNX_STRLEN(string2);

	for (cnt = 0; cnt < len1; cnt++) 
	{
		if (FNX_TOUPPER(string1[cnt]) < FNX_TOUPPER(string2[cnt]))	return -1;
		if (FNX_TOUPPER(string1[cnt]) > FNX_TOUPPER(string2[cnt]))	return 1;
	}
	if (cnt < len2)		return -1;
	if (cnt > len2)		return 1;
	return 0;
}
#endif

int _strnicmp(const char *string1, const char *string2, int length)
{
	int cnt;
	int len1=FNX_STRLEN(string1);
	int len2=FNX_STRLEN(string2);

	for (cnt = 0; cnt < len1 && cnt<length; cnt++) 
	{
		if (FNX_TOUPPER(string1[cnt]) < FNX_TOUPPER(string2[cnt]))	return -1;
		if (FNX_TOUPPER(string1[cnt]) > FNX_TOUPPER(string2[cnt]))	return 1;
	}
	if (cnt < length)		return -1;
	if (cnt > length)		return 1;
	return 0;
}

int strncasecmp(const char *string1, const char *string2, int length)
{
	int cnt;
	int len1=FNX_STRLEN(string1);
	int len2=FNX_STRLEN(string2);

	for (cnt = 0; cnt < len1 && cnt<length; cnt++) 
	{
		if (FNX_TOUPPER(string1[cnt]) < FNX_TOUPPER(string2[cnt]))	return -1;
		if (FNX_TOUPPER(string1[cnt]) > FNX_TOUPPER(string2[cnt]))	return 1;
	}
	if (cnt < length)		return -1;
	if (cnt > length)		return 1;
	return 0;
}


#if 0

//char *fnxstrdup(char *pStr)
//{
//   char  *pNew = NULL;
//
//   pNew = (char *)FNX_MALLOC( (FNXA_STRLEN(pStr)+1) * sizeof(char) );
//   if (pStr && pNew != NULL )
//   {
//      FNX_STRCPY(pNew, pStr);
//   }

//   return pNew;
//}
#endif

void *fnxbsearch( const void *key, const void *base, size_t num, size_t width, int (*compare)(const void *, const void *) )
{
        char *lo = (char *)base;
        char *hi = (char *)base + (num - 1) * width;
        char *mid;
        unsigned int half;
        int result;

        while (lo <= hi)
                if (half = num / 2)
                {
                        mid = lo + (num & 1 ? half : (half - 1)) * width;
                        if (!(result = (*compare)(key,mid)))
                                return(mid);
                        else if (result < 0)
                        {
                                hi = mid - width;
                                num = num & 1 ? half : half-1;
                        }
                        else    {
                                lo = mid + width;
                                num = half;
                        }
                }
                else if (num)
                        return((*compare)(key,lo) ? NULL : lo);
                else
                        break;

        return(NULL);
}
wchar_t * fnxwcsncpy(wchar_t * dest,const wchar_t *src,size_t count)
{
   int i;
   
   for (i=0;i<count;i++)
     {
	dest[i] = src[i];
	if (src[i] == 0)
	  {
	     return(dest);
	  }
     }
   dest[i]=0;
   return(dest);
}
size_t fnxwcslen(const wchar_t * s)
{
	const wchar_t *save;

	if (s == 0)
		return 0;
	for (save = s; *save; ++save);
	return save-s;
}

wchar_t * fnxwcscpy(wchar_t * str1,const wchar_t * str2)
{
  wchar_t *save = str1;

  for (; (*str1 = *str2); ++str2, ++str1);
  return save;
}


wchar_t* fnxwcschr(const wchar_t* str, wchar_t ch)
{
	while ((*str)!=0)
	{
		if ((*str)==ch)
		{
			return((wchar_t *)str);
		}
		str++;
	}
	return(NULL);
}

wchar_t *fnxwcstok(wchar_t *s, const wchar_t *ct)
{
	const wchar_t *spanp;
	int c, sc;
	wchar_t *tok;
	static wchar_t *last;


	if (s == NULL && (s = last) == NULL)
    		return (NULL);

  /*
   * Skip (span) leading ctiters (s += strspn(s, ct), sort of).
   */
 	cont:
	c = *s;
	s++;
	for (spanp = ct; (sc = *spanp) != 0;spanp++) {
 		if (c == sc)
      			goto cont;
  	}

	if (c == 0) {			/* no non-ctiter characters */
		last = NULL;
    		return (NULL);
  	}
  	tok = s - 2;

  /*
   * Scan token (scan for ctiters: s += strcspn(s, ct), sort of).
   * Note that ct must have one NUL; we stop if we see that, too.
   */
	for (;;) {

		c = *s;
		s+=2;
		spanp = ct;
		do {
			if ((sc = *spanp) == c) {
				if (c == 0)
					s = NULL;
				else
	  				s[-1] = 0;
				last = s;
				return (tok);
      			}
			spanp+=2;
    		} while (sc != 0);

  	}
  /* NOTREACHED */
}

wchar_t *fnxwcsstr(const wchar_t *s,const wchar_t *b)
{
	wchar_t *x;
	wchar_t *y;
	wchar_t *c;
	x=(wchar_t *)s;
	while (*x) {
		if (*x==*b) {
			y=x;
			c=(wchar_t *)b;
			while (*y && *c && *y==*c) { 
				c++;
				y++; 
			}
			if (!*c)
				return x;
		}
		x++;
	}
	return NULL;
}

wchar_t * a2w( char * a, wchar_t * w )
{
	wchar_t * ww = w;
	while (*a) *w++ = (wchar_t) *a++;
	*w = 0;
	return ww;
}

wchar_t* fgetws(wchar_t* pwcz, int n, void* pFile)
{

	wchar_t c;
	wchar_t* wszWrite = pwcz;
	int numread;

	do 
	{
		numread = fnxfread( &c, sizeof(wchar_t), 1, pFile );
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
#if 0
wchar_t * fgetws(wchar_t *buf, int bufsize, void *file)
{
	char * abuf;
	abuf = (char *)FNX_MALLOC(bufsize);
	if (!buf)return NULL;
	FNX_FGETS(abuf,bufsize,file);
	a2w(abuf,buf);
	FNX_FREE(abuf);
	return buf;
}
#endif

size_t wcstombs( char *dst, const wchar_t *src, size_t len )
{
	return 0;
}

int atoi(const char * string)
{
	int Num = 0;
	int Sign = 1;
	char * CurChar = string;

	while( *CurChar == 0x20 )			// skip all white space
		CurChar++;

	// deterime if there is a sign 
	if( *CurChar == 0x2D )				// switch sign flag if sign is negative ('-')
	{
		Sign = -1;
		CurChar++;
	}
	else if( *CurChar == 0x2B )				// skip '+' if a sign character
		CurChar++;

	while( *CurChar && *CurChar > 0x2F && *CurChar < 0x3A )
	{
		Num *= 10;						// increase the order by 10^1
		Num += (int)*CurChar++ - 0x30;	// convert the ASCII code to a number and add to the total
	}
	Num *= Sign;					// negate the integer if there was a '-' sign preceding
	return Num;
}

typedef int T;          /* type of item to be sorted */

#define MAXSTACK (sizeof(size_t) * CHAR_BIT)

/******************
 *  exchange a,b  *
 ******************/
static void exchange(void *a, void *b, size_t size)
{
    size_t i;

    for (i = sizeof(int); i <= size; i += sizeof(int))
	{
        int t = *((int *)a);
        *(((int *)a)++) = *((int *)b);
        *(((int *)b)++) = t;
    }
    for (i = i - sizeof(int) + 1; i <= size; i++)
	{
        char t = *((char *)a);
        *(((char *)a)++) = *((char *)b);
        *(((char *)b)++) = t;
    }
}

int write(int  fileno,                     /* File number		  */
        char *buf,                         /* Destination buffer address  */
        unsigned int  count)               /* Number of write characters  */
{
       return 0;
}


/********************
 *  ANSI-C qsort()  *
 ********************/
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    void *lbStack[MAXSTACK], *ubStack[MAXSTACK];
    int sp;
    unsigned int offset;

    lbStack[0] = (char *)base;
    ubStack[0] = (char *)base + (nmemb-1)*size;
    for (sp = 0; sp >= 0; sp--)
	{
        char *lb, *ub, *m;
        char *P, *i, *j;

        lb = lbStack[sp];
        ub = ubStack[sp];

        while (lb < ub)
		{
            /* select pivot and exchange with 1st element */
            offset = (ub - lb) >> 1;
            P = lb + offset - offset % size;
            exchange (lb, P, size);

            /* partition into two segments */
            i = lb + size;
            j = ub;
            while (1)
			{
                while (i < j && compar(lb, i) > 0)
					i += size;
                while (j >= i && compar(j, lb) > 0)
					j -= size;
                if (i >= j)
					break;
                exchange (i, j, size);
                j -= size;
                i += size;
            }

            /* pivot belongs in A[j] */
            exchange (lb, j, size);
            m = j;

            /* keep processing smallest segment, and stack largest */
            if (m - lb <= ub - m)
			{
                if (m + size < ub)
				{
                    lbStack[sp] = m + size;
                    ubStack[sp++] = ub;
                }
                ub = m - size;
            } 
			else
			{
                if (m - size > lb)
				{
                    lbStack[sp] = lb; 
                    ubStack[sp++] = m - size;
                }
                lb = m + size;
            }
        }
    }
}

#ifdef FNXW_BUILD_STRCPY
wchar_t * fnxwcscpy(wchar_t * str1,const wchar_t * str2)
{
  wchar_t *save = str1;

  for (; (*str1 = *str2); ++str2, ++str1);
  return save;
}
#endif

#ifdef FNXW_BUILD_STRLEN
size_t fnxwcslen(const wchar_t * s)
{
	const wchar_t *save;

	if (s == 0)
		return 0;
	for (save = s; *save; ++save);
	return save-s;
}
#endif


#ifdef FNXW_BUILD_STRCHR
wchar_t* fnxwcschr(const wchar_t* str, wchar_t ch)
{
	while ((*str)!=0)
	{
		if ((*str)==ch)
		{
			return((wchar_t *)str);
		}
		str++;
	}
	return(NULL);
}
#endif

#ifdef FNXW_BUILD_STRTOK
wchar_t *fnxwcstok(wchar_t *s, const wchar_t *ct)
{
	const wchar_t *spanp;
	int c, sc;
	wchar_t *tok;
	static wchar_t *last;


	if (s == NULL && (s = last) == NULL)
    		return (NULL);

  /*
   * Skip (span) leading ctiters (s += strspn(s, ct), sort of).
   */
 	cont:
	c = *s;
	s++;
	for (spanp = ct; (sc = *spanp) != 0;spanp++) {
 		if (c == sc)
      			goto cont;
  	}

	if (c == 0) {			/* no non-ctiter characters */
		last = NULL;
    		return (NULL);
  	}
  	tok = s - 2;

  /*
   * Scan token (scan for ctiters: s += strcspn(s, ct), sort of).
   * Note that ct must have one NUL; we stop if we see that, too.
   */
	for (;;) {

		c = *s;
		s+=2;
		spanp = ct;
		do {
			if ((sc = *spanp) == c) {
				if (c == 0)
					s = NULL;
				else
	  				s[-1] = 0;
				last = s;
				return (tok);
      			}
			spanp+=2;
    		} while (sc != 0);

  	}
  /* NOTREACHED */
}
#endif

