#include <string.h>
#include <stdarg.h>
#include <ctype.h>

//#include <sys/stat.h>
//#include <sys/dirent.h>
#include "FnxVocab.h"
#include "FnxStdlib.h"
#include "fnxexstdlib.h"

#ifdef HAVE_STDIO_H
#include <stdio.h>
#elif defined(OS_PALM)
#include "StdIOPalm.h"
#include "SysUtils.h"
#include "ErrorMgr.h"
#endif

/***************************************************
 *  NAME:	malloc
 *  DESC:	Allocates memory blocks.
 *  IN:		size - Bytes to allocate
 *  OUT:	<none>
 *  RETURN:	malloc returns a void pointer to the allocated space,
 *			or NULL if there is insufficient memory available. 
 ***************************************************/
voidPtr fnxmalloc(usize size)
{
//    return MemPtrNew(size);
	if (size > 35000)
	{
	    return MemGluePtrNew(size);	
	}
	else
	{	
    	MemHandle mh = MemHandleNew(size);
    	if (mh) 
    		return MemHandleLock(mh);
    	else 
    		return(0);
    }
}

/***************************************************
 *  NAME:	fnxcalloc
 *  DESC:	Allocates an array in memory with elements initialized to 0.
 *  IN:		size	- file name
 *			value	- type of access requested
 *  OUT:	<none>
 *  RETURN:	MemPtr pointer if successful, NULL otherwise
 *  NOTES:	This function replaces the standard calloc function.
 ***************************************************/
//MemPtr MemPtrCalloc( long size, unsigned char value )
voidPtr fnxcalloc( usize size, usize value )
{
	void * ptr;
	
	if (size > 35000)
	{
		ptr = MemGluePtrNew(size * value);
	}
	else
	{
		MemHandle mh = MemHandleNew(size*value);
   		ptr = MemHandleLock(mh);
    }
    
   	if(ptr)
	{
		MemSet(ptr,size*value,0);
	}
	return(ptr);
}


/***************************************************
 *  NAME:	realloc
 *  DESC:	Reallocate memory blocks.
 *  IN:		ptr - Pointer to previously allocated memory block
 *			size - New size in bytes
 *  OUT:	<none>
 *  RETURN:	returns a void pointer to the reallocated
 *			(and possibly moved) memory block. 
 ***************************************************/
voidPtr fnxrealloc(voidPtr ptr, usize size)
{
	UInt32 oldsize;
	
	if (ptr)
	{
		MemHandle mh = MemPtrRecoverHandle(ptr);
    	oldsize = MemHandleSize(mh);
    	if (oldsize > 35000 && size > 35000)
    	{
    		MemPtrResize(ptr,size);
    		return(ptr);
    	}
    	else if (oldsize <= 35000 && size <= 35000)
    	{
    	    MemHandle mh = MemPtrRecoverHandle(ptr);
   			MemHandleUnlock(mh);
    		MemHandleResize(mh, size);
    		return MemHandleLock(mh);
    	}
    	else
    	{
    		fnxfree(ptr);
    		return malloc(size);
    	
    	}
    }
    else
    {
    	return malloc(size);
    }
}

/***************************************************
 *  NAME:	free
 *  DESC:	Deallocates or frees a memory block.
 *  IN:		ptr - Pointer to previously allocated memory block
 *			to be freed.
 *  OUT:	<none>
 *  RETURN:	<none>
 ***************************************************/
void fnxfree(voidPtr ptr)
{
	UInt32 size;
	
    if (ptr)
    {
    	size = MemPtrSize(ptr);   //has the potential to break here
    	if (size > 35000)
    	{
        	MemPtrFree(ptr);
    	}
    	else
    	{
    		MemHandle mh = MemPtrRecoverHandle(ptr);
    		MemHandleUnlock(mh);
    		MemHandleFree(mh);
    	}
    }
}


#ifdef FNX_BUILD_PRINTF
/***************************************************
 *  NAME:	printf
 *  DESC:	Print formatted output to the standard output stream.
 *  IN:		format - Format control
 * 			argument - Optional arguments
 *  OUT:	<none>
 *  RETURN:	returns the number of characters printed
 *			or a negative value if an error occurs.
 ***************************************************/
int fnxaprintf(const char * pText, ...)
{
	short nCharWidth = 0;
	short width = 0, height = 0;
		
	// get the width of the string		
	nCharWidth = FntCharsWidth(pText, StrLen(pText));  
	// get the width and height of the string
	WinGetWindowExtent(&width, &height);
	
	//Erase the window prior to writing to the screen
	WinEraseWindow();
	// draw the text in the center
	WinDrawChars(pText, StrLen(pText), (width/2) - (nCharWidth/2), height/2);

}
#endif

#ifdef FNXA_BUILD_STRDUP

char *fnxastrdup (const char *s)
{
  char *result = (char*)malloc(FNX_STRLEN(s) + 1);
  if (result == (char*)0)
    return (char*)0;
  FNX_STRCPY(result, s);
  return result;
}
#endif

#ifdef FNX_BUILD_SLEEP
/***************************************************
 *  NAME:	sleep
 *  DESC:	Put the processor into doze mode for the specified number of milliseconds.
 *  IN:		delay - how long to delay
 *  OUT:	<none>
 *  RETURN:	<none>
 ***************************************************/
void fnxsleep(int delay)
{
	int tickspersec = 0;
	
	tickspersec = SysTicksPerSecond();
	SysTaskDelay((tickspersec*delay)/1000);
}
#endif

#ifdef FNX_BUILD_ABS
/***************************************************
 *  NAME:	abs
 *  DESC:	calculates the absolute value.
 *  IN:		n - integer value
 *  OUT:	<none>
 *  RETURN:	returns the absolute value of its parameter
 ***************************************************/

int fnxabs(int n)
{
	if (n < 0)
		return(-n);
	else
		return(n);
}
#endif

#ifdef FNX_BUILD_TOUPPER
int fnxtoupper(int c)
{
	return TxtGlueUpperChar(c);
}
#endif

#ifdef FNX_BUILD_STRCMP
/***************************************************
 *  NAME:	strcmp
 *  DESC:	Compare two strings.
 *  IN:		string1 - Pointer to a string
 * 			string2 - Pointer to a second string  
 *	OUT:	<none>
 *  RETURN:	Returns 0 if the strings match.
 *			Returns a positive number if s1 sorts after s2 alphabetically.
 *			Returns a negative number if s1 sorts before s2 alphabetically. 
 ***************************************************/
int fnxstrcmp( const char *string1, const char *string2 )
{
	return StrCompare(string1,string2);
}
#endif


#ifdef FNX_BUILD_STRLWR
/***************************************************
 *  NAME:	strlwr
 *  DESC:	Convert a string to lowercase.
 *  IN:		string - Pointer to Null-terminated string to convert to lowercase
 *  OUT:	<none>
 *  RETURN:	returns a pointer to the converted string 
 ***************************************************/
char *fnxastrlwr( char *string )
{
	return StrToLower (string, string);
}
#endif




#ifdef FNX_BUILD_MEMCPY
void *fnxmemcpy( void *dest, const void *src, size_t count )
{
//	ErrDisplay("inside memcpy");
	MemMove(dest,src,count);
	return(dest);
}
#endif

#ifdef FNX_BUILD_MEMSET
/***************************************************
 *  NAME:	memset
 *  DESC:	Sets buffers to a specified character.
 *  IN:		dest - Pointer to destination
 *			c - Character to set
 *			count - Number of characters 
 *  OUT:	<none>
 *  RETURN:	returns the value of dest.
 ***************************************************/
void * memset(void *dest, int c, UInt32 count)
{
	MemSet(dest, count, c);
}
#endif




double fnxaDiffTimeDays( FNX_TIMESTRUCT timer1, FNX_TIMESTRUCT timer2 )
{
	return (double)( (double)(timer1 - timer2) / 86400.0f );
}

#ifdef FNX_BUILD_STRNCAT

void *fnxmemchr( const void *s, int c, size_t n )
{
  const unsigned char *char_ptr;
  const unsigned long int *longword_ptr;
  unsigned long int longword, magic_bits, charmask;

  c = (unsigned char) c;

  /* Handle the first few characters by reading one character at a time.
     Do this until CHAR_PTR is aligned on a 4-byte border.  */
  for (char_ptr = s; n > 0 && ((unsigned long int) char_ptr & 3) != 0;
       --n, ++char_ptr)
    if (*char_ptr == c)
      return (void *) char_ptr;

  longword_ptr = (unsigned long int *) char_ptr;

  /* Bits 31, 24, 16, and 8 of this number are zero.  Call these bits
     the "holes."  Note that there is a hole just to the left of
     each byte, with an extra at the end:
     
     bits:  01111110 11111110 11111110 11111111
     bytes: AAAAAAAA BBBBBBBB CCCCCCCC DDDDDDDD 

     The 1-bits make sure that carries propagate to the next 0-bit.
     The 0-bits provide holes for carries to fall into.  */
  magic_bits = 0x7efefeff;

  /* Set up a longword, each of whose bytes is C.  */
  charmask = c | (c << 8);
  charmask |= charmask << 16;

  /* Instead of the traditional loop which tests each character,
     we will test a longword at a time.  The tricky part is testing
     if *any of the four* bytes in the longword in question are zero.  */
  while (n >= 4)
    {
      /* We tentatively exit the loop if adding MAGIC_BITS to
	 LONGWORD fails to change any of the hole bits of LONGWORD.

	 1) Is this safe?  Will it catch all the zero bytes?
	 Suppose there is a byte with all zeros.  Any carry bits
	 propagating from its left will fall into the hole at its
	 least significant bit and stop.  Since there will be no
	 carry from its most significant bit, the LSB of the
	 byte to the left will be unchanged, and the zero will be
	 detected.

	 2) Is this worthwhile?  Will it ignore everything except
	 zero bytes?  Suppose every byte of LONGWORD has a bit set
	 somewhere.  There will be a carry into bit 8.  If bit 8
	 is set, this will carry into bit 16.  If bit 8 is clear,
	 one of bits 9-15 must be set, so there will be a carry
	 into bit 16.  Similarly, there will be a carry into bit
	 24.  If one of bits 24-30 is set, there will be a carry
	 into bit 31, so all of the hole bits will be changed.

	 The one misfire occurs when bits 24-30 are clear and bit
	 31 is set; in this case, the hole at bit 31 is not
	 changed.  If we had access to the processor carry flag,
	 we could close this loophole by putting the fourth hole
	 at bit 32!

	 So it ignores everything except 128's, when they're aligned
	 properly.

	 3) But wait!  Aren't we looking for C, not zero?
	 Good point.  So what we do is XOR LONGWORD with a longword,
	 each of whose bytes is C.  This turns each byte that is C
	 into a zero.  */

      longword = *longword_ptr++ ^ charmask;

      /* Add MAGIC_BITS to LONGWORD.  */
      if ((((longword + magic_bits)
	
	    /* Set those bits that were unchanged by the addition.  */
	    ^ ~longword)
	       
	   /* Look at only the hole bits.  If any of the hole bits
	      are unchanged, most likely one of the bytes was a
	      zero.  */
	   & ~magic_bits) != 0)
	{
	  /* Which of the bytes was C?  If none of them were, it was
	     a misfire; continue the search.  */

	  const unsigned char *cp = (const unsigned char *) (longword_ptr - 1);

	  if (cp[0] == c)
	    return (void *) cp;
	  if (cp[1] == c)
	    return (void *) &cp[1];
	  if (cp[2] == c)
	    return (void *) &cp[2];
	  if (cp[3] == c)
	    return (void *) &cp[3];
	}

      n -= 4;
    }

  char_ptr = (const unsigned char *) longword_ptr;

  while (n-- > 0)
    {
      if (*char_ptr == c)
	return (void *) char_ptr;
      else
	++char_ptr;
    }

  return NULL;
}

/***************************************************
 *  NAME:	strncat
 *  DESC:	Append characters of a string.
 *  IN:		d - Null-terminated destination string
 *			s - Null-terminated source string 
 *			l - Number of characters to append
 *  OUT:	<none>
 *  RETURN:	returns a pointer to the destination string.
 ***************************************************/

char * fnxstrncat( char *d, const char *s, size_t l)
{
   char *s1=d+FNX_STRLEN(d), *s2;
   
   s2 = memchr(s, 0, l);
   if( s2 )
      memcpy(s1, s, s2-s+1);
   else
   {
      memcpy(s1, s, l);
      s1[l] = '\0';
   }
   return d;
}
#endif

#ifdef FNX_BUILD_STRTOK
/***************************************************
 *  NAME:	strtok
 *  DESC:	splits a string (arg1) into smaller strings (tokens),
 *			with each token being delimited by any character from arg2.
 *  IN:		string - String containing token(s)
 *			token - Set of delimiter characters
 *  OUT:	<none>
 *  RETURN:	return a pointer to the next token found in strToken.
 *			returns NULL when no more tokens are found.
 ***************************************************/
 
char * fnxstrtok(char *s, const char *ct)
{
         char *sbegin = s;
         static char *end;
 
         if (sbegin == NULL)
         {
            if (end == NULL)
				return NULL;
            sbegin = end;
         }
         end = FNX_STRPBRK(sbegin, ct);
         if (end)
                 *end++ = '\0';
 
         return sbegin;
}
#endif

#ifdef FNXA_BUILD_QSORT
/***************************************************
 *  NAME:	qsort
 *  DESC:	Performs a quick sort.
 *  IN:		base - Start of target array
 *			num - Array size in elements
 *			width - Element size in bytes
 *			compare - Comparison function
 *			elem1 - Pointer to the key for the search
 *			elem2 - Pointer to the array element to be compared with the key
 *  OUT:	<none>
 *  RETURN:	< 0 elem1 less than elem2 
 *			0 elem1 equivalent to elem2 
 *			> 0 elem1 greater than elem2 
 ***************************************************/
void fnxaqsort(void * base, size_t num, size_t width,int (* compare)(const void * elem1, const void * elem2))
{
	Int32 temp = NULL;
	SysQSort(base,(Int16)num,(Int16)width,(short (*)(void *,void *,long))compare,temp);

}
#endif

#ifdef FNX_PALM_BUILD_BSEARCH
/***************************************************
 *  NAME:	bsearch
 *  DESC:	Performs a binary search of a sorted array.
 *  IN:		key - Object to search for
 *			base - Start of target array
 *			num - Array size in elements
 *			width - Element size in bytes
 *			compare - Comparison function
 *			elem1 - Pointer to the key for the search
 *			elem2 - Pointer to the array element to be compared with the key
 *  OUT:	<none>
 *  RETURN:	bsearch returns a pointer to an occurrence
 *			of key in the array pointed to by base.
 *			If key is not found, the function returns NULL. 
 ***************************************************/
void* fnxabsearch(const void * key, const void * base, size_t num, size_t width,short (* compare)(const void * elem1, const void * elem2, Int32 other))
{
	Int32  temp = NULL;
	Int32* position;
	int   result = 0;
	Int16 tempnum = num;
	
	result = SysBinarySearch((const void  *)base, tempnum, width,(short (*)(const void *,const void *,long))compare,(const void *)key,temp,position,TRUE );
	if (result == 1)
		return position;
	else
		return NULL;
}
#endif

#ifdef FNX_BUILD_TIME
/***************************************************
 *  NAME:	time
 *  DESC:	Gets the current time
 *  IN:		pResult - Pointer to the time structure
 *  OUT:	<none>
 *  RETURN:	does not return a value, but fills in the fields of 
 *			the structure pointed to by pResult.

 ***************************************************/
FNX_TIMESTRUCT fnxtime( FNX_TIMESTRUCT *pResult )
{
	DateTimeType dt;
	TimeFormatType timeFormat;
//	Char strTime[timeStringLength];
	
	//get the time in seconds from 1904 and make a DateTimeType
	TimSecondsToDateTime(TimGetSeconds(),&dt);
	
	//get the system time prefs to find out what format to display the current time in
	timeFormat = (TimeFormatType)PrefGetPreference(prefTimeFormat);
	
	//get a string for the current time of day
	TimeToAscii(dt.hour,dt.minute,timeFormat,(char *)pResult);
	
}
#endif

#ifdef FNX_BUILD_LOCALTIME
/***************************************************
 *  NAME:	localtime
 *  DESC:	Converts a time value and corrects for the local time zone.
 *  IN:		timer - Pointer to stored time
 *  OUT:	<none>
 *  RETURN:	localtime returns a pointer to the structure result.
 *			If the value in timer represents a date before midnight,
 *			January 1, 1970, localtime returns NULL.
 *			The fields of the structure type tm store the following values,
 *			each of which is an int:
 ***************************************************/
struct tm *fnxlocaltime( const time_t *timer )
{
}
#endif

#ifdef FNX_BUILD_SSCANF
/***************************************************
 *  NAME:	sscanf
 *  DESC:	Read formatted data from a string.
 *  IN:		buffer - Stored data
 *			format - Format-control string 
 *  OUT:	<none>
 *  RETURN:	Returns the number of fields
 *			successfully converted and assigned; the return value
 *			does not include fields that were read but not assigned.
 *			A return value of 0 indicates that no fields were assigned.
 *			The return value is EOF for an error or if the end of the
 *			string is reached before the first conversion.
 ***************************************************/
int fnxsscanf(const char * buffer, const char * format, ...)
{
	int foo;
}
#endif

#ifdef FNX_OVERRIDE_FILE_CALLS

/***************************************************
 *  NAME:	AddUnderscore
 *  DESC:	Replaces '.', '\', '^', ' ', and ':' with '_' in a 
 *			filename
 *  IN:		pFileName	- file name
 *			pFileSize	- pointer to size of this file
 *  OUT:	
 *  RETURN:	
 *  NOTES:	
 ***************************************************/
static void AddUnderscore(char *pName)
{
	char	*chPtr;

	// replace '.', ':', and '\" with '_'
	while ((chPtr = FNX_STRCHR(pName, '.')))
	{
		*chPtr ='_';
	}
}


#ifdef FNXA_BUILD_FOPEN
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
FILE *fnxafopen(const char *pName, const char *pFlags)
{
//	DWORD			mode;
	UInt32			mode;
	Err 			err = errNone;
	char			*pdbName;

	if (*pFlags == 'r')
	{
//		mode = fileModeReadOnly|fileModeAnyTypeCreator;
		mode = fileModeReadOnly;
	}
	else if (*pFlags == 'w')
	{
		mode = fileModeReadWrite|fileModeAnyTypeCreator;
	}
	else if (*pFlags == 'a')
	{
		mode = fileModeAppend|fileModeAnyTypeCreator;
	}
	
	pdbName = FNX_MALLOC(MAX_PATH);
	FNXA_STRCPY(pdbName, pName);
	AddUnderscore(pdbName);
//	FNXA_STRCAT(pdbName, PALM_FILE_EXT );

//	return (FILE *)FileOpen(0,pName,0,0,mode,NULL);
//	return (FILE *)FileOpen(0,pdbName,0,0,mode,&err);
	return (FILE *)FileOpen(0,pdbName,'DATA',0,mode,&err);
	FNX_FREE(pdbName);
//	return (FILE *)FileOpen(0,pName,sysFileTFileStream,0,mode,&err);
	
}
#endif

#ifdef FNXW_BUILD_FOPEN
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
FILE *fnxwfopen(const wchar_t *pName, const wchar_t *pFlags)
{
//	HANDLE		hndl;
//	DWORD		flags, method;

//	if (*pFlags == 'r')
//	{
//		flags = GENERIC_READ;
//		method = OPEN_EXISTING;
//	}
//	else if (*pFlags == 'w')
//	{
//		flags = GENERIC_WRITE;
//		method = OPEN_ALWAYS;
//	}

//	hndl = CreateFileW(pName,
//					  flags, 
//					  FILE_SHARE_READ, 
//					  NULL, 
//					  method, 
//					  FILE_ATTRIBUTE_NORMAL, 
//					  NULL);

//	if( hndl == INVALID_HANDLE_VALUE )
//		hndl = NULL;

//	return hndl;
}
#endif

#ifdef FNXA_BUILD_FFLUSH
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
int fnxfflush(FILE *pStream)
{
	FileFlush((FileHand)pStream);
	return 0;
}
#endif

#ifdef FNXA_BUILD_FCLOSE
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
int fnxfclose(FILE *pStream)
{
	FileClose((FileHand)pStream);

	return 0;
}
#endif

#ifdef FNXA_BUILD_FEOF
/***************************************************
 *  NAME:	feof
 *  DESC:	Tests for end-of-file on a stream
 *  IN:		pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns a nonzero value after the first read operation
 *			that attempts to read past the end of the file,
 *			returns 0 if the current position is not end of file
 ***************************************************/
int fnxfeof(FILE *pStream)
{
	return FileEOF((FileHand)pStream);
}
#endif

#ifdef FNXA_BUILD_FREAD
/***************************************************
 *  NAME:	fread
 *  DESC:	Reads data from a stream
 *  IN:		pBuf	- storage location for data
 *			size	- item size in bytes
 *			count	- maximum number of items to be read
 *			pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns the number of full items actually read
 ***************************************************/
usize fnxafread(void *pBuf,usize size,usize count,FILE *pStream)
{

	Err err = errNone;
	usize nBytesRead;
	int foo;
	
	foo = 0;
	nBytesRead = 0;
	if (pStream == NULL)
		return -1;
	nBytesRead = FileRead((FileHand)pStream, pBuf, size, count, &err);
	if (err !=0)
		foo = 1;
	return nBytesRead;
}
#endif

#ifdef FNXA_BUILD_FWRITE
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
usize fnxafwrite(const void *pBuf,
			 usize size,
			 usize count,
			 FILE *pStream)
{
	Int32 nBytesWrite=0;

	//	CheckValid(pStream);
	if(pStream == NULL)
		return -1;

	nBytesWrite = FileWrite((FileHand)pStream, pBuf, size, count, NULL);
	return nBytesWrite;
}
#endif


#ifdef FNXA_BUILD_FERROR
/***************************************************
 *  NAME:	ferror
 *  DESC:	Get I/O error status
 *  IN:		pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns 0 if successful
 *  NOTES:	(8/18/98) If the stream was open for writing
			the memory location and len are updated in the
			file map.
 ***************************************************/
int fnxferror(FILE *pStream)
{
	FileError((FileHand)pStream);

	return 0;
}
#endif

#ifdef FNXA_BUILD_FSEEK
/***************************************************
 *  NAME:	fseek
 *  DESC:	Moves the file pointer to a specified location
 *  IN:		pStream	- pointer to FILE structure
 *			offset	- number of bytes from origin
 *			origin	- initial position
 *  OUT:	<none>
 *  RETURN:	returns 0 if successful
 ***************************************************/
int fnxfseek(FILE *pStream,
		  long offset,
		  int origin)
{
	FileOriginEnum position;

	if(origin == SEEK_CUR)
		position = fileOriginCurrent;
	else if(origin == SEEK_END)
		position = fileOriginEnd;
	else if(origin == SEEK_SET)
		position = fileOriginBeginning;

	FileSeek((FileHand)pStream, offset, position);

	return 0;
}
#endif

#ifdef FNXA_BUILD_REWIND
/***************************************************
 *  NAME:	Rewind
 *  DESC:	Repositions the file pointer to the beginning of a file.
 *  IN:		stream - Pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	<none>
 ***************************************************/
void fnxaRewind( FILE *stream )
{
	FNX_FSEEK( stream, 0, SEEK_SET );
}
#endif

#ifdef FNXA_BUILD_FTELL
/***************************************************
 *  NAME:	ftell
 *  DESC:	Gets the current position of a file pointer
 *  IN:		pStream	- pointer to FILE structure
 *  OUT:	<none>
 *  RETURN:	returns the current file position
 ***************************************************/
DWORD fnxftell(FILE *pStream)
{
	DWORD currPos;

	currPos = FileTell((FileHand)pStream, NULL, NULL);
	return currPos;
}
#endif

#ifdef FNXA_BUILD_REMOVE
/***************************************************
 *  NAME:	remove
 *  DESC:	Delete a file.
 *  IN:		path	- Path of file to be removed
 *  OUT:	<none>
 *  RETURN:	Returns 0 if the file is successfully deleted.
 *			Otherwise, it returns -1
 *			and sets errno either to EACCES to indicate that
 *			the path specifies a read-only file, or to ENOENT
 *			to indicate that the filename or path was not found
 *			or that the path specifies a directory.
 *			This function fails and returns -1 if the file is open.
 ***************************************************/
int fnxaremove( const char *path)
{
	int foo;
}
#endif

#ifdef FNXA_BUILD_FGETS
/*
The book says the input string is not changed if there is an error.
This implementation will NOT do that.
*/
char *fnxafgets( char *string, int n, FILE *stream )
{
	int i=0;
	usize ret=0;
	for( ; i<n; i++)
	{
		ret = fnxafread( &string[i], 1, 1, stream );
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
#endif

#ifdef FNXA_BUILD_FGETC
int fnxafgetc( FILE *stream )
{
	char sTmp[2] = "";
	int nTemp;

	fnxafgets(sTmp, 1,stream );
//	if(sTmp[0] == '\0')
//		nTemp = EOF;
//	else
		nTemp = (int)*sTmp;

	return nTemp;
}
#endif

#ifdef FNXA_BUILD_FPUTC
int fnxafputc(int c, FILE *stream )
{
	return Siofputc(c,stream);
}
#endif

#ifdef FNXA_BUILD_UNGETC
int fnxaungetc( int c, FILE *stream )
{
	FNX_ASSERT( 0 );
	return 0;
}
#endif

#ifdef FNXA_BUILD_FPRINTF
int fnxafprintf( FILE *fp, const char *format, ... )
{
   char buffer[256];
   
   FNX_SPRINTF(buffer,format);
   FNX_FWRITE(buffer,FNX_STRLEN(buffer),1,fp);        				              
   return 0;
}
#endif

#ifdef FNXA_BUILD_FSCANF
int fnxafscanf( FILE *fp, const char *format, ... )
{
      va_list argp;
      char *charp;
      WORD *WORDp;
      DWORD *DWORDp;
      int bytes_read = 0;
      
//      va_start(argp, format);
      
      
      if (FNXA_STRNCMP(format, "%d", 2))
      {
//        WORDp = va_arg(argp, WORD *);
      	bytes_read = FNX_FREAD(WORDp, sizeof(WORD), 1, fp);
      }
      else if (FNXA_STRNCMP(format, "%s", 2))
      {
//        charp = va_arg(argp, char *);
        bytes_read = FNX_FREAD(charp, sizeof(char), 1, fp);
      }
      
      va_end(argp);
      return bytes_read;
}
#endif

#else

#ifdef FNXW_BUILD_FOPEN
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
FILE *fnxwfopen(const wchar_t *pName, const wchar_t *pFlags)
{
//	HANDLE		hndl;
//	DWORD		flags, method;

//	if (*pFlags == 'r')
//	{
//		flags = GENERIC_READ;
//		method = OPEN_EXISTING;
//	}
//	else if (*pFlags == 'w')
//	{
//		flags = GENERIC_WRITE;
//		method = OPEN_ALWAYS;
//	}

//	hndl = CreateFileW(pName,
//					  flags, 
//					  FILE_SHARE_READ, 
//					  NULL, 
//					  method, 
//					  FILE_ATTRIBUTE_NORMAL, 
//					  NULL);

//	if( hndl == INVALID_HANDLE_VALUE )
//		hndl = NULL;

//	return hndl;
}
#endif
#endif  // FNX_OVERRIDE_FILE_CALLS