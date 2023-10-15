//#include <stdio.h> //moved to port.h for each platform mlt 02/16/06
//#include <string.h> //moved to port.h for each platform mlt 02/16/06
#include "port.h"
#include "phonetic.h"
#include "dccread.h"
#include "FnxAllocate.h"
#include "dtfnxexstdlib.h"

void main(int argc, char **argv)
{

   char  *sPron;
   char *sPhrase = "bao geu ddaeyeossda";
   int      iList = 0;
   DccPtr  pDccInfo;

   if(argc < 2)
   {
      FNX_FPRINTF(stdout, "Usage:  %s:<dictionary (.dcc or .pdc)>  [word] \nPlease try again\n", argv[0]);
      return;
   }

   if(argc == 2)
      FNX_FPRINTF(stdout, "Looking up  compiled phrase\n");

   else if(argc == 3)
   {
      if( FNX_STRSTR(argv[2], ".list") )
         FNX_FPRINTF(stdout, "Processing file with phrases\n");
      else
         FNX_FPRINTF(stdout, "Looking up connamd line word\n");
   }
   else
   {
      FNX_FPRINTF(stdout, "Invalid number of arguments\n");
      return;
   }

   /* Opoen dictionary */
   initDccFile(argv[1], &pDccInfo);
   if(pDccInfo == NULL)
   {
      FNX_FPRINTF(stdout, "Dictionary file: &d could not be initialized\n", argv[1]);
      return;
   }

   /* Process either a text file containing words or a single word from command list */
   if(argc == 3)
   {
      if(iList) //Read and process a file
      {
         char  sLine[256];
         FILE  *fp;
         fp = FNX_FOPEN(argv[2], "rt");
         while( FNX_FGETS(sLine, 256, fp) )
         {
            sPron= translate(pDccInfo->pGraph2Phon, sLine);
            FNX_FPRINTF(stdout, "Word:  %s  Pron:  %s\n", sLine, sPron);
         }
         FNX_FCLOSE(fp);
         return;
      }

      /* Process single word from command line */
      sPron= translate(pDccInfo->pGraph2Phon, argv[2]);
       FNX_FPRINTF(stdout, "Word:  %s  Pron:  %s\n", argv[2], sPron);
   }

   /* Process compiled text */
   else
   {
      sPron= translate(pDccInfo->pGraph2Phon, sPhrase);
      FNX_FPRINTF(stdout, "Phrase:  %s\nPron:  %s\n", sPhrase, sPron);
   }

   /* Close dictionary and free memroy*/
   closeDccFile(pDccInfo);
   fnxFree(sPron);

   return;

}