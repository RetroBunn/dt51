//#include <stdio.h>
#include <string.h>
#include "phonetic.h"
#include "dccread.h"
#include "FnxAllocate.h"
#include "fnxexstdlib.h"

void main(int argc, char **argv)
{

   char  *sPron;
   char *sPhrase = "bao geu ddaeyeossda";
   int      iList = 0;
   DccPtr  pDccInfo;

   if(argc < 2)
   {
      fprintf(stdout, "Usage:  %s:<dictionary (.dcc or .pdc)>  [word] \nPlease try again\n", argv[0]);
      return;
   }

   if(argc == 2)
      fprintf(stdout, "Looking up  compiled phrase\n");

   else if(argc == 3)
   {
      if( strstr(argv[2], ".list") )
         fprintf(stdout, "Processing file with phrases\n");
      else
         fprintf(stdout, "Looking up connamd line word\n");
   }
   else
   {
      fprintf(stdout, "Invalid number of arguments\n");
      return;
   }

   /* Opoen dictionary */
   initDccFile(argv[1], &pDccInfo);
   if(pDccInfo == NULL)
   {
      fprintf(stdout, "Dictionary file: &d could not be initialized\n", argv[1]);
      return;
   }

   /* Process either a text file containing words or a single word from command list */
   if(argc == 3)
   {
      if(iList) //Read and process a file
      {
         char  sLine[256];
         FILE  *fp;
         fp = fopen(argv[2], "rt");
         while( fgets(sLine, 256, fp) )
         {
            sPron= translate(pDccInfo->pGraph2Phon, sLine);
            fprintf(stdout, "Word:  %s  Pron:  %s\n", sLine, sPron);
         }
         fclose(fp);
         return;
      }

      /* Process single word from command line */
      sPron= translate(pDccInfo->pGraph2Phon, argv[2]);
       fprintf(stdout, "Word:  %s  Pron:  %s\n", argv[2], sPron);
   }

   /* Process compiled text */
   else
   {
      sPron= translate(pDccInfo->pGraph2Phon, sPhrase);
      fprintf(stdout, "Phrase:  %s\nPron:  %s\n", sPhrase, sPron);
   }

   /* Close dictionary and free memroy*/
   closeDccFile(pDccInfo);
   fnxFree(sPron);

   return;

}