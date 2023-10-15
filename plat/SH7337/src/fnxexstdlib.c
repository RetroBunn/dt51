////#include <stdio.h>
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
