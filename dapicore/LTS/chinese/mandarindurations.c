 
#include <string.h>

#define QTAF0MODEL

#define IN_DECTALK
#ifdef IN_DECTALK
#include "dectalkf.h"
#include "port.h"
#include "ls_def.h"
#include "ls_defs.h"
#include "ls_data.h"
#include "ph_def.h"
#include "tts.h"

#include "Mandarin.h"
#include "mandarinprot.h"
#endif 
#include <string.h>

#define QTAF0MODEL

#define IN_DECTALK
#ifdef IN_DECTALK
#include "dectalkf.h"
#include "port.h"
#include "ls_def.h"
#include "ls_defs.h"
#include "ls_data.h"
#include "ph_def.h"
#include "tts.h"

#include "Mandarin.h"
#include "mandarinprot.h"
#endif 

#ifndef IN_DECTALK
#define userulesdebug
#define userules_is_main
#endif

#ifdef userulesdebug
#define debug_printf(fmt,args...) printf(fmt,## args)
#else
#ifdef _UNIX_LIKE_
#define debug_printf(fmt,args...)
#else
#define debug_printf(fmt,args)
#endif
#endif
#ifdef userulesdebug
#define debug_printf(fmt,args...) printf(fmt,## args)
#else
#ifdef _UNIX_LIKE_
#define debug_printf(fmt,args...)
#else
#define debug_printf(fmt,args)
#endif
#endif

/*  
Spring model for Mandarin syllable durations and durations of the phonemes 
within the syllable. My biggest piece of fudge thus far. 
  
Reiner Wilhelms-Tricarico @ Fonix 
 
buf[0] = (PFCH <<PSFONT) + ph; 
buf[1] = duration; 
ls_util_write_pipe(pKsd_t,&buf[0],2); 

*/

/* Tables representing mandarin ascky characters and  
   corresponding to "compliance", "intrinsic duration", and 
   type of character for specifying a syllable category.
*/

//#define DEBUG_MAND_DURATIONS

/* added reduced er as letter 9 */

static const char mand_ascky_seq[]=   " iAUEI2Xu53O^a89JWeo67mnNpbtdkgfsSrxhKRywlczqjCZT@B$%DFGYVH"; 
//static const char mand_compliance[] = "55555555555555542233333332222222222222222222222233333333333"; 
//static const char mand_ascky_dur[]= "146545564555555512677844523233344533333333333333"; 
static const char mand_ascky_cat[]=   "vvvvvvvvvvvvvvvvggwwwwccccccccccccccccccccccccccvvvvvvvvvvc"; 
//static const short mand_durations[]= {80,94,109,126,145,166,190,217,247,280};
//                                 /*   0  1   2   3   4   5   6   7   8   9  */

/* Table: If syllable duration was strictly proportional to  
   number of phonemes the following table would read 1, 1/2, 1/3, 1/4, 1/5. etc.
*/
static const double mand_syll_length_fact[] = {1.00, 0.65, 0.55, 0.5, 0.40, 0.32};
 
 
/* syllable scalings according to "complexity", another fudge table cooked from 
   data on syllable durations found in a study by 
   Chilin Shih and Benjamin Ao: Duration Study for the Bell Lab Mandarin 
   TTS system in Van Santen: Progress in Speech Synthesis 
*/

int mand_char_index(const char *p, char c)
{
	const char *q;
	int i;
	
	q = p;
	i = 0;
	while (*q)
	{
		if (*q == c) return (i);
		i++;
		q++;
	}
	return (0);
}

static const double mand_syllscale[] = {    
	    1.4177,
	    1.5316,
	    1.3924,
	    1.3671,
	    1.3418,
	    1.2911,
	    1.1899,
	    1.1899,
	    1.1772,
	    1.0000,
	    1.4177,
	    1.2873,
	    1.1739
	};

char mand_phoneme_category(char inchar)
{
    int  indx;

    indx = mand_char_index(mand_ascky_seq, inchar);

	if (indx>=0) return (mand_ascky_cat[indx]);
	else return ('.');
}

int mand_syll_category(LPTTS_HANDLE_T phTTS,char *syll, int len)
{
    char categorystring[8];
    int i;
    
    for (i=0;i<len;i++) categorystring[i]= mand_phoneme_category(syll[i]);
    categorystring[len]='\0';
#ifdef DEBUG_MAND_DURATIONS
	printf("\nSyllable ascky: /%s/ category %s\n",syll,categorystring);
#endif 
    
    if (strcmp(categorystring,"cgvc")==0) return (1);
    if (strcmp(categorystring,"cgw")==0) return (2);
    if (strcmp(categorystring,"cvc")==0) return (3);
    if (strcmp(categorystring,"cgv")==0) return (4);
    if (strcmp(categorystring,"cw")==0) return (5);
    if (strcmp(categorystring,"vc")==0) return (6);
    if (strcmp(categorystring,"cv")==0) return (7);
    if (strcmp(categorystring,"w")==0) return (8);
    if (strcmp(categorystring,"v")==0) return (9);
    if (strcmp(categorystring,"cvvc")==0) return (10);  // % not in list like 1 or 2 or 3
    if (strcmp(categorystring,"cvv")==0) return (11);   // % not in list like 5  (per vowel 0.6 times)
    if (strcmp(categorystring,"vv")==0) return (12);   //  % not in list (like 8)  (per vowel 0.6 times)

    return 0;
}

/* 
   Regarding minimum durations of phonemes:
   As I don't have a table for this (don't know how to get the stuff from phedit here),
   I'll have to fudge it:

   Let's say the maximum possible compliance is 5 and the smallest is 1 (it's the law).
   Those are the numbers in compliance table.
   Now:
   For the maximal compliance I want the minimal duration to be 1/3 of the value in the table
   For the minimal compliance I want the minimal duration to be 3/5 of the value in the table
   
   dur -> dur * ((3/5) - (1/3) (c - cmin)/(cmax-cmin)) does the trick. 
   c: compliance, cmin, cmax are 1 and 5 respectively.

   Now obsolete: we use the mindur table instead.

*/
void   duration_and_compliance(LPTTS_HANDLE_T phTTS, char c, double *dur,  double *mindur, double *compliance)
{
    int  indx,idur,imindur;


	PDPH_T	pDph_t = phTTS->pPHThreadData;

	indx = (phTTS->pKernelShareData->reverse_ascky[c]) & 0xff;
	idur = pDph_t->cur_speaker[PFCH]->inhdr[indx];
	imindur = pDph_t->cur_speaker[PFCH]->mindur[indx];

	if (imindur == idur) imindur = idur - idur/4;

    indx = mand_char_index(&mand_ascky_seq[0], c); // relies on having it in the string 

      *dur = (double) idur ;
	  *mindur = (double) imindur;
  	  *compliance = (*dur-*mindur)/(*dur);

#ifdef DEBUG_MAND_DURATIONS
	  printf("for %c dur=%g mindur=%g compliance %g\n",c,*dur,*mindur,*compliance);
#endif
}

// FSYLL		0x00000001
// FVOICD		0x00000002
// FVOWEL		0x00000004
// FSON1		0x00000008
// FSONOR		0x00000010
//=>vowels have 0x0000001f

// FOBST		0x00000020
// FPLOSV		0x00000040
// FNASAL		0x00000080
// FCONSON		0x00000100
// FSONCON		0x00000200
// FSON2		0x00000400
// FBURST		0x00000800
// FSTMARK		0x00001000
// FSTOP		0x00002000
// FFLAP		0x00004000
// FLATERAL		0x00008000
// FRETROFLEX	0x00010000
// FNFI1		0x00020000
// FNFI2		0x00040000
// FNFI3		0x00080000

// Place of articulation - see place in rom_data_s
// FLABIAL		0x0001
// FDENTAL		0x0002
// FPALATL		0x0004
// FALVEL		0x0008
// FVELAR		0x0010
// FGLOTAL		0x0020
// F2BACKI		0x0040
// F2BACKF		0x0080
// FLABIALDENTAL	0x0100
// FPOSTALVEOLAR	0x0200
// FUVULAR		0x0400
// FPHARYNGEAL	0x0800
// FVELARF		0x1000
// FVELARB		0x2000
// FVELARR		0x4000
//struct rom_data_s {
//	const short *inhdr;
//	const short *mindur;
//	const short *burdr;
//	const short *f0msegtars;
//	const short *f0fsegtars;
//	const short *begtyp; Beginning Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
//	const short *endtyp; Ending Type (1=Front, 2=Back, 3=Rounded, 4=Null, 5=Beginning Rounded, 6=Opened)
//	const short *place;
//	const int *featb;
//	const short *maltar;
//	const short *femtar;
//	const short *maldip;
//	const short *femdip;
//	const short *ptram;
//	const short *malamp;
//	const short *femamp;
//	const short *plocu;
//	const short *maleloc;
//	const short *femloc;
/* 
   Method: For each phoneme in the syllable we get initial values of 
   durations in milliseconds from a table. Associated with each phoneme 
   is also a compliance coefficient which is small if the duration of the
   phoneme can not change much, and large if it is more pliable. So
   vowels get a value of 4-6 for compliance and certain consonants, in 
   particular plosives, get the smallest compliance values. The syllable
   is then treaded as if the durations were spring extensions or compressions
   Total syllable duration is determined depending on syllable type, according
   to a study in VanSanten't book on speech synthesis, but modified in such a
   way that the relative duration per phoneme is first calculated. 
   The changes due to each phoneme are then distributed according to the
   compliance coefficients, such that vowels shrink more in long syllalbes
   with more phonemes. 
 */
   
double  mand_duration_calc(LPTTS_HANDLE_T phTTS, char *syll, double *durs, int tone, float speedtau, int cntrl)
{
    int sylltype;
    int k,len, indx;
    double dur,maxdur,delta,syllscale,sumcomp;
    double compli[8];
	double mindurs[8];
	double tonefactor;
	PDPH_T	pDph_t = phTTS->pPHThreadData;


    len = FNX_STRLEN(syll);

    sylltype = mand_syll_category(phTTS,syll,len);

	switch (tone)
	{
	case 1: tonefactor = 1.15; break;
	case 2: tonefactor = 1.25; break;
	case 3: tonefactor = 1.00; break;
	case 4: tonefactor = 1.05; break;
	case 5: tonefactor = 0.95; break;
	default: tonefactor = 1.0; break;
	}

	if (cntrl==1) tonefactor = tonefactor*1.3;
    maxdur = 0.0;
    sumcomp = 0.0;

    for (k=0;k<len;k++) 
	{
	    duration_and_compliance(phTTS, syll[k],&(durs[k]),&(mindurs[k]), &compli[k]);
	    maxdur +=  durs[k];             // total max duration
	    sumcomp += compli[k];           
	}

	if (len>1)  /* make final nasal longer for preceeding front vowels */
	{
		if (syll[len-1] == 'N' || syll[len-1] =='n')
		{
			indx = (phTTS->pKernelShareData->reverse_ascky[syll[len-2]]) & 0xff;
			indx = pDph_t->cur_speaker[PFCH]->endtyp[indx];   // ending type 
			if (indx == 1) 
			{ 
				durs[len-1] += 30;  
				durs[len-2] -= 20;  
			}
		}
	}

    syllscale = mand_syllscale[sylltype];
 
    delta = (maxdur * speedtau) *(syllscale*mand_syll_length_fact[len-1] - 1.0)/sumcomp;
    dur=0.0;
#ifdef DEBUG_MAND_DURATIONS
	printf("maxdur=%g speedtau=%g syllscale=%g  sumcmp=%g delta=%g\n",maxdur,speedtau,syllscale, sumcomp, delta);
    printf("sending : ");
#endif
    for (k=0; k<len; k++)
    {
	durs[k] += delta*compli[k];
	durs[k] *= tonefactor;
	if (durs[k]<mindurs[k]) durs[k]=mindurs[k];
	durs[k] *= speedtau;
	if (cntrl == 1 && k==len-1) durs[k] += 10;
	dur += durs[k];

#ifdef DEBUG_MAND_DURATIONS
	printf("<'%c' %6.2fms> ",syll[k],durs[k]);
#endif
    }

#ifdef DEBUG_MAND_DURATIONS
	printf("  to dectalk \n ");
#endif
    return dur;
}

