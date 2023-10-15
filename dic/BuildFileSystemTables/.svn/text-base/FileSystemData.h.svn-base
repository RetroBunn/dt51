/*H_HEADER_FILE***************************************************************
FILE			: FileSystemData.h
DESC			: 
TABS			: 3
OWNER			: 
DATE CREATED	: 

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER******************************************************************/
#ifndef	FILESYSTEMDATA_H
#define	FILESYSTEMDATA_H

#ifdef _BIGENDIAN_
//#define fread fnxfread //in dtfnxexstdlib.h now mlt 02/09/06
//#define fseek fnxfseek //in dtfnxexstdlib.h now mlt 02/09/06
#define FILE void
#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0
#endif

#define FSD_BYTES1	0x0001
#define FSD_BYTES2	0x0002
#define FSD_BYTES4	0x0004
#define FSD_SIGNED	0x0008
#define FSD_GTRIE	0x0010
#define FSD_STRING	0x0020
#define FSD_ITLIST	0x0040
#define FSD_ITRULE	0x0080

#ifndef U16
#define U16 unsigned short
#endif

#define FSD_MAXSTRING	16

typedef struct _fsgnodeinfo
{
  U16 status;                 // depends on type (e.g., loop state for loop)
  U16 counter;                // counts whatever we like
  U16 counterB;               // counts whatever we like
  U16 parameter;              // max loop count e.g.
} FS_GNODEINFO;

typedef struct  _GTrieNode
{
  char sName[12];			// redundant except for compare strings nodes.
  U16  alt;
  U16  what;                // for repeatables: pointer to self.
  U16  right;
  U16  index;				// index of symbols (same thing above)
  char typeinfo;
  FS_GNODEINFO  info;			// type,status, counter, parameter
}GTRIENODE;

extern int GetBytesPerValue(FILE *fp, int *pbSigned, unsigned int iTblOffset);
extern int GetTableValue(FILE *fp, void *pValue, unsigned int index, unsigned int iTblOffset);
extern int GetTableUChar(FILE *fp, unsigned char *pValue, unsigned int index, unsigned int iTblOffset);
extern int GetTableChar(FILE *fp, char *pValue, unsigned int index, unsigned int iTblOffset);
extern int GetTableUShort(FILE *fp, unsigned short *pValue, unsigned int index, unsigned int iTblOffset);
extern int GetTableShort(FILE *fp, short *pValue, unsigned int index, unsigned int iTblOffset);
extern int GetGTrieNode(FILE *fp, GTRIENODE *pGTrieNode, unsigned int index, unsigned int iTblOffset);

#endif
