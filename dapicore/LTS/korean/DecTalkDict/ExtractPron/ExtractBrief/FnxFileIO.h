/*H_HEADER_FILE***************************************************************
FILE        : FileIO.h
DESC        : 
TABS        : 3
OWNER       : 
DATE CREATED: 

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/26/03 4:11p $
  $Revision: 9 $

*END_HEADER******************************************************************/
#ifndef  FILEIO_H
#define  FILEIO_H

#define NULL_FILE "<NULL>"

#include "FnxPlatform.h"


#ifdef OS_WIN32                     // ----Warning----   Other platforms are supported in this file.
                              //             Use caution when changing what your platform uses.
extern SDWORD FileExists(char *sFilename);
extern SDWORD GetDirName(char *sDirName, char *sFileName);
extern BOOL ExistDir(char *sDir);
extern SDWORD MakeDirectory(char *sDir);
extern SDWORD MakeDirectoryForFile(char *sFilename);
extern FILE *fopenWithPath(const char *sFilename, const char *sMode);
extern SDWORD FileCopy(char *sSource, char *sDest);
extern SDWORD CountFiles(char *sRoot, char *sBase);
extern char **BuildFileList( char *sRootDir, char *sExt, SDWORD * plNumFiles);
extern char *SubstituteDirectory(char *sOldName, char *sOldPath, char *sOldExt, char *sNewPath, char *sNewExt);
extern char **SubstituteList(char **psOldList, SDWORD lNumFiles, char *sOldPath, char *sOldExt,
                      char *sNewPath, char *sNewExt);
extern SDWORD CountFiles( char *sRootDir, char *sBaseName);
extern SDWORD ReplaceDorkyFilename(char **psFilename);
extern char *UndorkFilename(char *sDorky);


#elif defined(OS_UNIX)
#define _MAX_PATH FILENAME_MAX


FILE *fopenWithPath(const char *filename, const char *mode);
int FileExists(const char *filename);
int GetDirName(char *directory, const char *filename);
int MakeDirectory(const char *directory);
int MakeDirectoryForFile(const char *filename);
int FileCopy(const char *source, const char *dest);
int CountFiles(const char *root, const char *base);
extern char *SubstituteDirectory(char *sOldName, char *sOldPath, char *sOldExt, char *sNewPath, char *sNewExt);
extern char **SubstituteList(char **psOldList, SDWORD lNumFiles, char *sOldPath, char *sOldExt,
                      char *sNewPath, char *sNewExt);
extern char **BuildFileList(const char *root, const char *ext, SDWORD * count);
extern char *ReadEntireTextFile(char *sTextFile);


#elif defined(OS_MAC)                     // -----------OS_MAC----------


FILE *fopenWithPath(const char *filename, const char *mode);
int FileExists(const char *filename);
int GetDirName(char *directory, const char *filename);
int MakeDirectory(const char *directory);
int MakeDirectoryForFile(const char *filename);
int FileCopy(const char *source, const char *dest);
int CountFiles(const char *root, const char *base);
char *SubstituteDirectory(const char *name, const char *old_path, const char *old_ext,
                 const char *new_path, const char *new_ext);
char **SubstituteList(char **list, int n, const char *old_path, const char *old_Ext,
                  const char *new_Path, const char *new_Ext);
extern char **BuildFileList(const char *root, const char *ext, SDWORD * count);
extern char *ReadEntireTextFile(char *sTextFile);
#endif

#endif                                 // FILEIO_H
