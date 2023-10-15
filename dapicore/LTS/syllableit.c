#include "bachusit.h"

int wordlength(ASCIILETTER *W)
{
    return (int) FNX_STRLEN(W);
}

void zero_syllable(BSYLL *S)
{
    int i;
    for (i=0;i<MAXSYLLPART;i++) S->onset[i]='\0';
    for (i=0;i<MAXSYLLPART;i++) S->nucleus[i]='\0';
    for (i=0;i<MAXSYLLPART;i++) S->coda[i]='\0';
    S->codageminate = 0;
    S->stressed = 0;
}

BOOL equal_letters(ASCKYPHONEME *A, ASCKYPHONEME *B)
{
    return (FNX_STRCMP((char *) A, (char *) B)==0);
}
BOOL is_empty(ASCKYPHONEME *A)
{
    return (A[0] == '\0');
}

BOOL is_italian_vowel(ASCKYPHONEME car)
{
    if (car == 'a' || car == 'e' ||  car=='E' || car =='i' || 
        car == 'o' || car == 'c' ||  car=='u' || car =='w' )
	return 1;
    else return 0;
}

BOOL is_single_vowel(ASCKYPHONEME *A)
{
    int l;
    l = FNX_STRLEN(A);
    if (l==1)
    {
	return is_italian_vowel(A[0]);
    }
    else 
	return 0;
}

BOOL is_single_consonant(ASCKYPHONEME *A)
{
    int l;
    l = FNX_STRLEN(A);
    if (l==1)
    {
	return !(is_italian_vowel(A[0]));
    }
    else 
	return 0;
}

	    
/* 
Let's think first how to write this stuff....

Syllabification goes as follows:

First detect all the positions of the vowels and specify the vowel clusters as
syllable nuclei. Initially, we can treat each set of consonant clusters (C)
between two vowel clusters (V) as being part of the right syllable.  So
initially we have:
 
CV-CV-CV-CV ... or V-CV-CV-CV-.. 

Based on this information, it is possible,
(at least for Italian and other European languages)
to write down the phonemes. This will be specific to
each language.  So we go through and
generate the phonemes for each consonant clusters. 

Then we have to go through the such defined syllables and
see for each consonant cluster, which is now in the onset
of a syllable, whether it could be split. If it is splittable,
then the part that goes to the left syllable is put in the
coda of that syllable. 

In some cases, the coda of a syllable is at the same time
the onset of the next syllable (ambi-syllabic consonant).
This may be reasonable to do for example for the Italian
geminite consonants. We have casa and cassa (house, cashier)
with the syllables: ca-sa and cas-sa. In reality, 
the /s/ is the same phoneme as /ss/ but with slightly different
duration. In the case of a geminate, the duration of the /s/
is elongated while the preceding vowel is shortened.

*/

#define SYLLBOUND '-'
#define ENDOFWORD '\0'

int rough_syllabify(ASCIILETTER *word, BSYLL **syllable)
{
    int syllnumber;
    int len, pos;
    int onsetpt,  nucleuspt, codapt;

    ASCKYPHONEME car;
    len = wordlength(word); 
    pos = 0;            // position in string 
    syllnumber = 0;
    
 newsyllable:
    //FNX_PRINTF("newsyll: %c %c \n",car,word[pos]);
    if (syllnumber>0 && word[pos]=='?')
    {
	/* the next onset starts with '?' this markes that the 
	   coda of the current, just finished syllable is equal
	   to the first consonant of the following syllable.
	*/

	syllable[syllnumber-1]->codageminate = 1;  
        // previous coda is geminate e.g., cas-sa, og-gie
	pos += 1;                                 
	syllable[syllnumber-1]->coda[codapt++] = word[pos];  // copy onset of next syllable
	pos += 1; 
    }
    syllnumber += 1;
    zero_syllable(syllable[syllnumber-1]);
    onsetpt=0;
    nucleuspt=0;
    codapt=0;
    car = word[pos++];
    if (car==ENDOFWORD) goto finish;
    if (is_italian_vowel(car) || car =='!' ) goto nucleus;

 onset:
    syllable[syllnumber-1]->onset[onsetpt++] = car;
    car = word[pos++];
    if (car==ENDOFWORD) goto finish;
    if (car==SYLLBOUND) goto newsyllable;
    if (is_italian_vowel(car) || car =='!') goto nucleus;
    else goto onset;
    
 nucleus: 
    if (car=='!')
    {
	syllable[syllnumber-1]->stressed=1;
	car = word[pos++];
    }
    syllable[syllnumber-1]->nucleus[nucleuspt++] = car;
    car = word[pos++];
    if (car==ENDOFWORD) goto finish;
    if (car==SYLLBOUND) goto newsyllable;
    if (is_italian_vowel(car)) goto nucleus;

 coda:
    syllable[syllnumber-1]->coda[codapt++] = car;
    car = word[pos++];
    if (car==ENDOFWORD) goto finish;
    if (car==SYLLBOUND) goto newsyllable;
    if (!is_italian_vowel(car)) goto coda;

 syllableerror:
    //FNX_PRINTF("This should not happen and if it does, there is a bug right here\n");

 finish:
    return syllnumber;
}

void Print_syllables(int nsyll, BSYLL **syllable)
{
    int n;

    for (n=0;n<nsyll; n++)
    {
	FNX_PRINTF("Syll %3i: Stressed: %i2 Geminate: %2i . [ %s : %s : %s ]\n",
	       n+1, syllable[n]->stressed, syllable[n]->codageminate, 
	       syllable[n]->onset,syllable[n]->nucleus,syllable[n]->coda);
    }
}

ASCIILETTER *make_syllabified_word(int nsyll, BSYLL **syllable, ASCIILETTER *outbuf, ASCIILETTER *longbuf )
{
    int n,i;
    ASCIILETTER *p,*lp;
    ASCKYPHONEME c;
    ASCIILETTER shortarpa[6];   // ARPA (max two letters)

    p = outbuf;

    for (n=0;n<nsyll; n++)
    {
	if (syllable[n]->stressed)  *p++ = '\'';
        for (i=0, c=syllable[n]->onset[i]; c != '\0'; i++, c=syllable[n]->onset[i]) *p++ = c;
        for (i=0, c=syllable[n]->nucleus[i]; c != '\0'; i++, c=syllable[n]->nucleus[i]) *p++ = c;
        for (i=0, c=syllable[n]->coda[i]; c != '\0'; i++, c=syllable[n]->coda[i]) *p++ = c;
        *p++ = '-';
    }
   --p;
   *p = '\0';
   p = outbuf;
#ifndef BACHUS_IN_DECTALK
   longbuf[0]='\0'; // start copying with strcat from beginning of buffer

   FNX_STRCAT(longbuf,"say -a \"[:phon arpa on][");
   
   while ( (c = *p++)!=0 )
   { 
       lp = italian_ascky2arpa(c , shortarpa);
       FNX_STRCAT(longbuf,shortarpa);
   }
   FNX_STRCAT(longbuf,"]\"");
   p=longbuf;
#endif

   return p;
}

void apply_specific_italian_stress(int nsyll, BSYLL **syllable)
{
    
    if (nsyll>=3)
    {
	if (is_empty(syllable[nsyll-1]->coda) && 
	    equal_letters(syllable[nsyll-1]->onset,"n") &&
	    equal_letters(syllable[nsyll-1]->nucleus,"o") &&
	    is_empty(syllable[nsyll-2]->coda) && 
	    equal_letters(syllable[nsyll-2]->nucleus,"o"))
	{
	    syllable[nsyll-3]->stressed=1;
	}
    }
}

	    

void apply_standard_italian_stress(int nsyll, BSYLL **syllable)
{
    int i;
    for (i=0;i<nsyll;i++) if (syllable[i]->stressed) return;   // done if one is stressed already
    
    if (nsyll>1)
	syllable[nsyll-2]->stressed=1;
    else syllable[0]->stressed=1;
}


void apply_standard_italian_soundtransformations(int nsyll, BSYLL **syllable)
{
    int i;

/* so far there is only one that's worthwhile: 
   intervocalic /s/ turns in to /z/ unless there is 
   an /a/ before and an /a/ or /o/ behind it.
*/

    for (i=1; i<nsyll; i++)
    {
	if (i>0 && equal_letters(syllable[i]->onset,"s") && is_empty(syllable[i-1]->coda))
	{
	    if (is_single_vowel(syllable[i-1]->nucleus) &&
		!equal_letters(syllable[i-1]->nucleus, "a"))
	    {
		if (is_single_vowel(syllable[i]->nucleus) &&
		    !equal_letters(syllable[i]->nucleus,"a") &&
		    !equal_letters(syllable[i]->nucleus,"o"))
		{
		    syllable[i]->onset[0]='z';
		}
	    }
	}

/* stressed e is open E */

	if (syllable[i]->stressed == 1 && is_single_vowel(syllable[i]->nucleus))
	{
	    if (syllable[i]->nucleus[0]=='e') syllable[i]->nucleus[0]='E' ;
	}
	
    }
}


ASCIILETTER *italian_ascky2arpa(ASCKYPHONEME asckychar, ASCIILETTER *arp)
{ 
    switch (asckychar)
    {
	case 'a': arp[0]='a'; arp[1]='p'; break;
	case 'e': arp[0]='e'; arp[1]='p'; break;
	case 'E': arp[0]='e'; arp[1]='h'; break;
	case 'i': arp[0]='i'; arp[1]='y'; break;
	case 'j': arp[0]='y'; arp[1]=' '; break;
	case 'o': arp[0]='o'; arp[1]='p'; break;
	case 'c': arp[0]='a'; arp[1]='o'; break;
	case 'u': arp[0]='u'; arp[1]='w'; break;
	case 'w': arp[0]='w'; arp[1]=' '; break;
	case 'b': arp[0]='b'; arp[1]=' '; break;
	case 'd': arp[0]='d'; arp[1]=' '; break;
	case 'g': arp[0]='g'; arp[1]=' '; break;
	case 'p': arp[0]='p'; arp[1]=' '; break;
	case 't': arp[0]='t'; arp[1]=' '; break;
	case 'k': arp[0]='k'; arp[1]=' '; break;
	case 'f': arp[0]='f'; arp[1]=' '; break;
	case 'l': arp[0]='l'; arp[1]=' '; break;
	case 'm': arp[0]='m'; arp[1]=' '; break;
	case 'n': arp[0]='n'; arp[1]=' '; break;
	case 's': arp[0]='s'; arp[1]=' '; break;
	case 'z': arp[0]='z'; arp[1]=' '; break;
	case 'v': arp[0]='v'; arp[1]=' '; break;
	case '7': arp[0]='c'; arp[1]='h'; break;
	case '8': arp[0]='j'; arp[1]='h'; break;
	case 'R': arp[0]='r'; arp[1]='r'; break;
	case 'Q': arp[0]='n'; arp[1]='x'; break;
	case 'H': arp[0]='n'; arp[1]='j'; break;
	case 'S': arp[0]='s'; arp[1]='h'; break;
	case 'L': arp[0]='l'; arp[1]='l'; break;
	case '9': arp[0]='t'; arp[1]='z'; break;
	case '0': arp[0]='d'; arp[1]='z'; break;
	case 'T': arp[0]='t'; arp[1]='d'; break;
	case 'D': arp[0]='d'; arp[1]='d'; break;
	case 'P': arp[0]='p'; arp[1]='d'; break;
	case 'B': arp[0]='b'; arp[1]='d'; break;
	case 'K': arp[0]='k'; arp[1]='d'; break;
	case 'G': arp[0]='g'; arp[1]='d'; break;
	case 'h': arp[0]='n'; arp[1]='h'; break;
	case 'N': arp[0]='n'; arp[1]='d'; break;
	case 'M': arp[0]='m'; arp[1]='f'; break;
	case 'r': arp[0]='r'; arp[1]=' '; break;
	case '-': arp[0]='-'; arp[1]=' '; break;
	case '\'': arp[0]='\''; arp[1]=' '; break;
	default:  arp[0]=' '; arp[1]=' '; break;
    }    
    arp[2]='\0';
    return arp;
}
