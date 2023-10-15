#include <wchar.h>
#include "port.h"
#include "DTFnxStdlib.h"
#include "DTFnxExStdlib.h"
//#include "FnxFiles.h"		// for FNXA_FINDDATA_T
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#if 0
long _findfirst(char *name, struct FNXA_FINDDATA_T *FileData)
{
	int		err;
	FileData->next = 0;
	err = glob(name, 0, NULL, &FileData->glob);
	if (err != 0)
	{
		return -1;
	}
	_findnext(0, FileData);
	return (long)FileData;
}

int _findnext(long FileId, struct FNXA_FINDDATA_T *FileData)
{
	int		rtn = -1;
	if (FileData->next < FileData->glob.gl_pathc)
	{
		int			flag;
		struct stat	statbuf;
		FNX_STRCPY(FileData->name, FileData->glob.gl_pathv[FileData->next]);
		FileData->next++;
		// --- is this a directory?
		flag = stat(FileData->name, &statbuf);
		if (flag >= 0)
		{
			int		st_mode, attrib;
			st_mode = statbuf.st_mode;
			if ((S_IFDIR & st_mode) == S_IFDIR)
			{
				attrib = _A_SUBDIR;
			}
			else if (((S_IFREG & st_mode) == S_IFREG) || ((S_IFLNK & st_mode) == S_IFLNK))
			{
				attrib = _A_FILE;
			}
			else
			{
				attrib = _A_UNKNOWN;
			}
			FileData->attrib = attrib;
			rtn = (int)FileData;
		}
	}
	return rtn;
}

long _findclose(long FileId)
{
	globfree(&((struct FNXA_FINDDATA_T *)FileId)->glob);
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

char *_strlwr(char *str)
{
   int x;

   if (str!=0)
   {
	   for(x=0; str[x]; x++)
		 str[x]=tolower(str[x]);
   }   
   return str;
}

char *_strupr(char *str)
{
   int  x;

   if (str!=0)
   {
	   for(x=0; str[x]; x++)
		 str[x]=toupper(str[x]);  
   }
   return str;
}

char *strrev(char *str)
{
   char *tstr = str;
   int	slen = strlen(str);
   int	slen_half = slen / 2, x, y;

   if (str != 0)
   {
	   for(x = 0, y = slen - 1; x < slen_half; x++, y--)
	   {
		 char tempch = str[x];
		 str[x] = tstr[y];
		 tstr[y] = tempch;
	   }
   }   
   return str;
}

/* On Windoze, this is simply a wrapper for Sleep(DWORD dur) where dur is in ms */
void
FnxDelay(long dur)
{
    struct timespec req, rem;
    dur = (dur < 0) ? 0 : dur;

    req.tv_sec = (dur / 1000);
    req.tv_nsec = ((dur % 1000) * 1000000);

    while (nanosleep(&req, &rem) == -1) {
        req = rem;
    }
}
#endif
