#include <stdio.h> 
#include <tchar.h>
#include "WriteWavFile.h"

typedef struct {
   short nFormatTag;
   short nChannels;
   int   nSamplesPerSec;
   int   nAvgBytesPerSec;
   short nBlockAlign;
   short wBitsPerSample;
   short cbSize;
} WaveFormat;

#define FNX_FWRITE fwrite
#define FNX_FREAD  fread

/*FUNCTION_HEADER**********************
 * NAME:	;writeInt
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
static int writeInt(FILE *fp, int i)
{
   if(FNX_FWRITE(&i,4,1,fp)!=1) 
   {
      return 1;
   }
   return 0;
}

/*FUNCTION_HEADER**********************
 * NAME:	;WriteWavHeader
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int WriteWavHeader(FILE *fp, WaveFormat *pWaveFormat, int length)
{
   //this is a very simple RIFF file
   if(FNX_FWRITE("RIFF",1,4,fp)!=4) 
      return 0;

   if(writeInt(fp, 4+8+sizeof(WaveFormat)+8+length*sizeof(short))!=0)
      return 0;

   if(FNX_FWRITE("WAVEfmt ",1,8,fp)!=8) 
      return 0;

   if(writeInt(fp, sizeof(WaveFormat))!=0) 
      return 0;

   if(FNX_FWRITE(pWaveFormat, 1, sizeof(WaveFormat), fp) != sizeof(WaveFormat)) 
      return 0;

   if(FNX_FWRITE("data",1,4,fp)!=4) 
      return 0;

   if(writeInt(fp,length*sizeof(short))!=0) 
      return 0;

   return 1;

}

/*FUNCTION_HEADER**********************
 * NAME:	;ReadWavHeader
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int ReadWavHeader(FILE *fp, WaveFormat *pWaveFormat, int *piLength)
{
	char sText[12];
	int	iLen1,
		iSzWaveFormat,
		nBytes,
		nHdrBytes=0;

   //this is a very simple RIFF file
   if( fread(sText, 1, 4, fp) != 4 )		// "RIFF"
      return 0;
   nHdrBytes += 4;

   if( fread(&iLen1, 4, 1, fp) != 1 )
      return 0;
   nHdrBytes += 4;

   if( fread(sText, 1, 8, fp) != 8 )		// "WAVEfmt "
      return 0;
   nHdrBytes += 8;

   if( fread(&iSzWaveFormat, 4, 1, fp) != 1 ) 
      return 0;
   nHdrBytes += 4;

   if( fread(pWaveFormat, sizeof(WaveFormat), 1, fp) != 1 ) 
      return 0;
   nHdrBytes += sizeof(WaveFormat);

   if( fread(sText, 1, 4, fp) != 4 )		// "data" 
      return 0;
   nHdrBytes += 4;

   if( fread(&nBytes, 4, 1, fp) != 1) 
      return 0;
   nHdrBytes += 4;

   if( piLength )
	   *piLength = nBytes / sizeof(short);

   return nHdrBytes;
}

/*FUNCTION_HEADER**********************
 * NAME:	;WriteWavFile
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int WriteWavFile(const TCHAR *filename, short* pSamples, int length, int rate )
{
	WaveFormat pWaveFormat;
	FILE *fp;
	
	if( !filename || !*filename )
		return(1);

	if( (fp = _tfopen(filename, _T("wb"))) == NULL )
		return 1;

	pWaveFormat.nFormatTag=1;
	pWaveFormat.nChannels = 1;
	pWaveFormat.nSamplesPerSec=rate;
	pWaveFormat.wBitsPerSample=16;
	pWaveFormat.nBlockAlign=(short)(pWaveFormat.nChannels*pWaveFormat.wBitsPerSample/8);
	pWaveFormat.nAvgBytesPerSec=pWaveFormat.nBlockAlign*pWaveFormat.nSamplesPerSec;
	pWaveFormat.cbSize=0;

	if( WriteWavHeader(fp, &pWaveFormat, length) == 0 )
		goto werror0;

   if(FNX_FWRITE(pSamples,sizeof(short),length,fp) != (unsigned int)length) 
      goto werror0;

   fclose(fp);
   return 0;
   
werror0:
   fclose(fp);
   return 1;
}

/*FUNCTION_HEADER**********************
 * NAME:	;CatWavFile
 * DESC: 	
 * IN:		
 * OUT:		
 * RETURN:	
 * NOTES:	
 *END_HEADER***************************/
int CatWavFile(const TCHAR *filename, short* pSamples, int length, int rate )
{
	int 
		nHdrBytes,
		iPrevLen;
	WaveFormat 
		WaveFormat;
	FILE 
		*fp;
	
	if( !filename || !*filename )
		return(1);

	if( (fp = _tfopen(filename, _T("r+b"))) == NULL )
		return 1;

	if( (nHdrBytes = ReadWavHeader(fp, &WaveFormat, &iPrevLen)) == 0 )
		goto werror0;

	if( rate != WaveFormat.nSamplesPerSec || 
		WaveFormat.wBitsPerSample != 16 )
		goto werror0;

	fseek(fp, 0, SEEK_SET);
	if( WriteWavHeader(fp, &WaveFormat, length+iPrevLen) == 0 )
		goto werror0;

	fseek(fp, 0, SEEK_END);

	if(FNX_FWRITE(pSamples,sizeof(short),length,fp) != (unsigned int)length) 
		goto werror0;
	
	fclose(fp);
	return 0;
   
werror0:
	fclose(fp);
	return 1;
}
