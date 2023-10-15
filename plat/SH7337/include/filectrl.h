// -----------------------------------------------------------
//  File System / Device I/O BIOS Header
// -----------------------------------------------------------

#ifndef __PVFILE_H_INCLUEDED__

#define __PVFILE_H_INCLUEDED__
                                                  
//#include "BCommon.h"
typedef struct TimeSys{
		BYTE	year_high;		/* YEAR(High):BCD  */
		BYTE	year_low;		/* YEAR(Low):BCD   */
		BYTE	month;			/* MONTH:BCD       */
		BYTE	day;			/* DAY:BCD         */
		BYTE	hour;			/* HOUR:BCD        */
		BYTE	min;			/* MINUTE:BCD      */
		BYTE	sec;			/* SECOND:BCD      */
		BYTE	dummy;			/* ﾀﾞﾐｰ            */
}TIMESYS;
/* flash bios */

/* for Get Device Descripter */
typedef struct _filedevdesc {
  int  StructSize;
  DWORD DeviceType;
  DWORD DeviceDesc;
  char DeviceDescriptionName[32];
  int BlockNum;
  int BlockSize;
  int TotalSize;      
  int FileSysTotalSize;
} TSFileDevDesc;

typedef struct _proginfo {
	DWORD ProgAddr;
	DWORD DsectAddr;
	DWORD DsectSize;
	DWORD RsectAddr;
	DWORD DataSize;
} TProgramFileInfo;

/* for File Attributes */
typedef struct _fileattributes {
  int  StructSize;
  WORD FileType;
  WORD FileAttr;
  int  FileSize;
  TIMESYS CreateTime;
} TFileAttributes;

/* for File AttributesEx @@myan added 03/12/17 */
typedef struct _fileattributesEx {
  int  StructSize;
  WORD FileType;
  WORD FileAttr;
  int  FileSize;
  TIMESYS CreateTime;
  DWORD RawAddr;
  int  ProgCnt;
  TProgramFileInfo ProgInfo[1];
} TFileAttributesEx;

/* 各種の最大文字数(すべてNULL文字を「含めない」) */
#define MAX_PATHLEN       127
#define MAX_FILENAMELEN   62
#define MAX_DEVICENAMELEN 16
#define MAX_EXTNAMELEN    3

/* Device Descripter Definations */
#define IM_DEVICETYPE_UNKNOWN           0xffffffff
#define IM_DEVICETYPE_NORFLASH          0
#define IM_DEVICETYPE_NANDFLASH         1
#define IM_DEVICETYPE_SMARTMEDIA        2
#define IM_DEVICETYPE_SDCARD            3
#define IM_DEVICETYPE_GENERICATA        4
#define IM_DEVICETYPE_MMC               5
#define IM_DEVICETYPE_FILEMEMORY		6		/* 2002.8.26 H.Koyama ﾌｧｲﾙﾒﾓﾘ追加 */

#define IM_DEVICEDESC_REMOVABLE         0x0020
#define IM_DEVICEDESC_READONLY          0x0010
#define IM_DEVICEDESC_CANNOTUSE		    0x0008 
#define IM_DEVICEDESC_NOPARTATION	    0x0004
#define IM_DEVICEDESC_RECORDFILEOK      0x0002
#define IM_DEVICEDESC_BINARYFILEOK      0x0001

/* File Attribute Definations */
#define IM_FILETYPE_PROGRAM 			0
#define IM_FILETYPE_BINARYFILE 			1
#define IM_FILETYPE_DIRECTORY 			5

#define IM_FILEATTR_READONLY 		0x0001
#define IM_FILEATTR_SYSTEM  		0x0002
#define IM_FILEATTR_SECURITY 		0x0004
#define IM_FILEATTR_PVMODE 			0x4000
#define IM_FILEATTR_CPMODE 			0x8000
#define IM_FILEATTR_FIXEDPROGRAM	0x0008		// IM_FILETYPE_PROGRAMのときのみ有効 @@myan

/* READ/WRITE MODE */
#define _OPENMODE_READ 				0x01
#define _OPENMODE_READ_SHARE 		0x80
#define _OPENMODE_WRITE				0x02
#define _OPENMODE_READWRITE			0x03
#define _OPENMODE_READWRITE_SHARE	0x83
#define _OPENMODEF_SYSTEMUSE        0x80000000

#define _CREATEMODE_PROGRAM			0
#define	_CREATEMODE_BINARY			1
#define	_CREATEMODE_RECORD			2
#define _CREATEMODE_DUALRECORD		3
#define _CREATEMODE_RECORDWITHALARM	4
#define _CREATEMODE_DIRECTORY	    5

#define _CREATEMODE_PVMODE			0x4000
#define _CREATEMODE_CPMODE			0x8000

#define IM_DEVSTAT_OK 					 0
#define IM_DEVSTAT_ILLEGALENTRY 		 1
#define IM_DEVSTAT_ILLEGALLOGICALFORMAT  2
#define IM_DEVSTAT_ILLEGALPHYSICALFORMAT 3

/* MEMORY GARBAGE COLLECTION */
#define IM_MGCPROCESS_ABORTED 1

/* FILE ERROR CODE */
#define IML_FILEERR_NOERROR  0
#define IML_FILEERR_ENTRYNOTFOUND     -1
#define IML_FILEERR_ILLEGALPARAM      -2
#define IML_FILEERR_ILLEGALPATH       -3

#define IML_FILEERR_DEVICEFULL        -4
#define IML_FILEERR_ILLEGALDEVICE     -5
#define IML_FILEERR_ILLEGALFILESYS    -6
#define IML_FILEERR_ILLEGALSYSTEM     -7
#define IML_FILEERR_ACCESSDENYED      -8
#define IML_FILEERR_ALREADYLOCKED     -9
#define IML_FILEERR_ILLEGALTASKID     -10
#define IML_FILEERR_PERMISSIONERROR   -11
#define IML_FILEERR_ENTRYFULL         -12
#define IML_FILEERR_ALREADYEXISTENTRY -13
#define IML_FILEERR_READONLYFILE      -14
#define IML_FILEERR_ILLEGALFILTER     -15
#define IML_FILEERR_ENUMRATEEND       -16
#define IML_FILEERR_DEVICECHANGED     -17
//#define IML_FILEERR_NOTRECORDFILE     -18
#define IML_FILEERR_ILLEGALSEEKPOS    -19
#define IML_FILEERR_ILLEGALBLOCKFILE  -20
//#define IML_FILEERR_DEVICENOTEXIST    -21
//#define IML_FILEERR_ENDOFFILE         -22
#define IML_FILEERR_NOTMOUNTDEVICE    -23
#define IML_FILEERR_NOTUNMOUNTDEVICE  -24
#define IML_FILEERR_CANNOTLOCKSYSTEM  -25
#define IML_FILEERR_RECORDNOTFOUND    -26 
//#define IML_FILEERR_NOTDUALRECORDFILE -27
#define IML_FILEERR_NOTALARMSUPPORT   -28
#define IML_FILEERR_CANNOTADDALARM    -29
#define IML_FILEERR_FILEFINDUSED      -30  // added.        
#define IML_FILEERR_DEVICEERROR		  -31
#define IML_FILEERR_SYSTEMNOTLOCKED	  -32    
#define IML_FILEERR_DEVICENOTFOUND    -33   
#define IML_FILEERR_FILETYPEMISMATCH  -34
#define IML_FILEERR_NOTEMPTY		  -35
#define IML_FILEERR_BROKENSYSTEMDATA  -36
#define IML_FILEERR_MEDIANOTREADY     -37
#define IML_FILEERR_TOOMANYALARMITEM  -38
#define IML_FILEERR_SAMEALARMEXIST    -39

#define IML_FILEERR_ACCESSSWAPAREA	  -40	// added @@myan 03/06

#define IML_FILEERR_DETECTBLD		  -41	// SDマウント時BLD検出 2005/08/4 T.Yamasaki

// 0～-255まではシステム上で予約。エラーコード追加のときは
// この上に足してください。 @@myan
#define IML_FILEERR_USERDEFINED		  (-256-65536)  // 値を固定するようにした。

/* BIOS PROTOTYPE */

char *BSfile_EnumDevices(int DeviceNum,char *devicename,int bufsize);
int BSfile_GetDeviceDesc(char *devicename,TSFileDevDesc *info);
int BSfile_GetMediaFree(char *devicename,int *freebytes);
int BSfile_GetFileInfo(char *filename,TFileAttributes *info);
int BSfile_FindFirst(char *dirname,int *FindHandle,
					char *foundfile,TFileAttributes *info);
int BSfile_FindNext(int FindHandle,char *foundfile,TFileAttributes *info);
int BSfile_FindClose(int FindHandle);
int BSfile_OpenFile(char *filename,int mode);
int BSfile_ReadFile(int HANDLE,void *buf,int size,int readpos);
int BSfile_WriteFile(int HANDLE,void *buf,int size);
int BSfile_OverWriteFile(int HANDLE,void *buf,int size, int writepos);	// 2004/10/27 T.Yamasaki 追加
int BSfile_SeekFile(int HANDLE,int pos);
int BSfile_FlushFile(int HANDLE);
int BSfile_GetFileSize(int HANDLE);
int BSfile_CloseFile(int HANDLE);
int BSfile_CreateEntry(char *filename,int mode);
int BSfile_DeleteEntry(char *filename);
int BSfile_RenameEntry(char *oldfilename,char *newfilename);
int BSfile_ChangeEntry(char *filename,DWORD attr);
int BSfile_GuideMM(char *devicename);
int BSfile_GarbageOFF( void );			// 2002.11.16 H.Koyama 追加

int BSfile_LoadSystemData(void *buf,int size,int offset);
int BSfile_SaveSystemData(void *buf,int size,int offset);
int BSfile_LockSystem(char *devicename);
int BSfile_UnlockSystem(char *devicename);
int BSfile_BlockWrite(char *devicename,int sectoraddr,void *buf,int size);
int BSfile_BlockRead(char *devivename,int sectoraddr,void *buf,int size);
int BSfile_CheckDevice(char *devicename);
int BSfile_FixDevice(char *devicename);
int BSfile_ExecGarbageCollection(char *devicename);
int BSfile_FormatDevice(char *devicename,BOOL isPhysical,int addinsize);
int BSfile_ResetDevice(char *devicename);
int BSfile_MountDevice(char *devicename);
int BSfile_UnmountDevice(char *devicename);

#endif
