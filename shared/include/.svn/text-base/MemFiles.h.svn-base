// MemFiles.h

#ifndef MEMFILES_H
#define MEMFILES_H

typedef int (*YieldFunction)(void * pData, const char * szFileName);


#if defined(__cplusplus)
extern "C" {
#endif

FNX_EXPORT( void,	ConvertName(char *pName) );

FNX_EXPORT( int,	OutputFile(FILE *pOut,
							   const char *pPath,
							   char *pFileName,
							   int *pFileSize,
							   char *pMode,
							   int write,
							   YieldFunction pYieldFunction,
							   void * pData ) );

FNX_EXPORT( int,	WriteArbitraryMemFile( char * outputFile, 
								int numInputFiles, 
								char ** ppInputFiles, 
								char ** ppInputDirectories,
								YieldFunction,
								void * ) );

FNX_EXPORT( int,	WriteArbitraryMemFileEx( 
								char * outputFile, 
								int numInputFiles, 
								char ** ppInputFiles, 
								char ** ppInputDirectories,
								YieldFunction pYieldFunction,
								void * pData,
								char * pMapName) );

#if defined(__cplusplus)
}
#endif

#endif