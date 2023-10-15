/* Note: this is a version of userules. Do not check in or
   out or whatever. It's not part of the code, just a method
   for me to transport pieces of code ReWT.
*/

#include "ruleparse.h"
#include "port.h" //added for platform specific stuff - mlt
//moved to port.h for each platform - mlt
//#include <string.h>
//#include <stdio.h>
#include "bachregverb.h"
#include "replacerules.h"

#define userulesdebug

#ifdef userulesdebug
#define debug_printf(fmt,args...) FNX_PRINTF(fmt,## args)
#else
#define debug_printf(fmt,args...)
#endif

#define userules_is_main
#define LINUXSYNTHESIS
/* 
   all in one file now: replacerules.h
   #include "PHON_It_rules.h"
   #include "LTS_It_rules.h"
   #include "phonemeclass.h"
   #include "seperators.h"
   #include "specialstress.h"
*/ 
/* This is a main program */


WalkCNTXT Walkercntxt;   // not constant.


/* subroutine to match a seperator string pattern, containing '-' for 
   seperation to an input word string. copies the '-' to the output
   so that word gets seperated by hyphens
*/

void match_seperators(char *word, char *pattern, char *outword)
{
    int len;
    int ii;
    int jj;
    
    len = FNX_STRLEN(pattern);
    
    jj = 0;

    for (ii=0;ii<len;ii++)
    {
	if(pattern[ii] == '-') outword[ii] = '-';
	else                   outword[ii] = word[jj++];
    }
    outword[len]='\0';
}


int IT_stress_type_from_verb_grammar(char *word, char *outword, int *rafforze,  IT_WalkCNTXT *wcnt, const IT_wordgrammarinfo *gramm)
{
    int anaret;
    int enclitic,stress;
    int i;
    char descriptor[8]; // sure rules are no longer than 5 bytes

    anaret = analyse_word(word, outword, descriptor, wcnt, gramm);
    if (anaret==0) return 0;       // not parsed, not a verb, nothing can be said about the word

/* Note: The interpretation of descriptor, the resulting string, 
   depends entirely upon the grammar that analyses the 
   word in terms of verb features. See grammar.tab in the Italian.
   ReWT: 9/16/04. 
   For example, "parlano"=>descriptor="a3i6" we look at the '3' 
   Stress is backed up to the left if there is an enclitic
   which in the descriptor string is marked as an 'x'.

   Added: The grammar covers a few more things. Now it also decides wether
   the next word after this needs doubling of consonants. In the grammar this is
   done by setting the first letter of the output string to 'r'. 

   If a word is an unstressed clitic as single word, a special preposition,
   the grammar sets a 'c' in the first column. We set here rafforze to -1.
*/

    enclitic=0; 
    for (i=0; descriptor[i] != '\0'; i++) if (descriptor[i]=='x') enclitic = 1;
    
    *rafforze=0;
    if (descriptor[0]=='r') *rafforze =  1;            // rafforzamento sintattico
    if (descriptor[0]=='c') *rafforze = -1;            // clitic preposition - no stress!

    switch (descriptor[1])      
    {
	case '1':   stress = 1 + enclitic;  break;
	case '2':   stress = 2 + enclitic;  break;
	case '3':   stress = 3 + enclitic;  break;
	case '4':   stress = 4;  break;
	default:    stress = 0;  break;
    }

    if (*rafforze== -1) stress=0;
    
    return stress;
}

void apply_found_stress(int stressshould, int rafforze, char *phonemes, char *outphonemes)
{
    int len;
    int nsyll, numberofsyll, mark,stress;
    int ii,jj;

/* In this subroutine, stress=1 means last syllable, stress=2 penultimate, 
   stress=3, ante-penultimate syllable etc. stress = 0 is considered the same
   stressing the penultimate syllable.
*/

    len = FNX_STRLEN(phonemes);
    nsyll=1;
    stress = stressshould;
   
    for (ii=0; ii<len; ii++)
    {
	if (phonemes[ii]=='-') nsyll++;
    }

    if ((stress <= 0 && nsyll == 1) || rafforze == -1)
	{
	    FNX_STRCPY(outphonemes, phonemes);    // no stress.
	    return;
	}

    numberofsyll = nsyll;         // later used.

    if (stress==0) stress = 2;
    if (stress>nsyll)
    {
	stress=nsyll;
    }
    mark=nsyll-stress+1;

    nsyll = 1;

    jj=0;

    if (mark==1)
    {
	outphonemes[jj++] = '\'';
    }

    if (mark >= 3)
    {
	outphonemes[jj++] ='`';
    }


    for (ii=0;ii<len;ii++)
    {
	outphonemes[jj++] = phonemes[ii];
	if (phonemes[ii]=='-')
	{
	    nsyll += 1;
	    if (nsyll < (mark-1) && (nsyll%2) == 1)
	    {
		outphonemes[jj++] ='`';
	    }
	    if (mark == nsyll) 
	    {
		outphonemes[jj++] = '\'';
	    }
	}
    }
    outphonemes[jj]='\0';
}	

// get rid of "'": make "c'era" -> "cera" (in and out can be same)
void remove_deletion_marker(char *in, char *out)
{
    char cc;
    while ((cc = *in++) != '\0')
    {
	if (cc != '\'' && cc != "`") *out++ = cc;
    }
    *out = '\0';
    return;
}

// word by word processor 
// needs infomation about it's environment. 

int italian_word_lts(char *inword, char *outphonemes, PLTS_T pLts_t)
{
    int ii, stress;
    char  word[100], outword[100],  phonoword[100];
    char  class_string[100],  pattern[100];
    int   rafforze;
    
    pLts_t->magic_environ=1;        //

    rafforze=0;
    stress = stress_type_from_verb_grammar(inword, 
					   outword,  
					   &rafforze,             /* set to 1 if rafforzamento sintaticco for next word */
					   &Walkercntxt,  
					   &regverb_WordGrammar);

    remove_deletion_marker(inword,word);

    /* stress returned here is counted from the back: 1 means ultimate */
    /* if stress is zero, it couldn't be defined                       */

    debug_printf("Stress: %d\n",stress);
    
    if (stress==0)
    {
	apply_replace_rules_to_str(word, outword, &stress_rules, 0);
	debug_printf("stress determination by table  - outword: [%s]\n", outword);
	if (outword[0] != '\0')
	{
	    stress = ((int) outword[0]- ((int) '1'))+1;  // may be -1.
	    if (stress==1) rafforze = 1;
	    debug_printf("stress thus found %d \n",stress);
	}
    }
    
    apply_replace_rules_to_str(word, outword, &LTS_It_rules, 0);         /* LTS */
    debug_printf("LTS    : %s\n", outword);
    
    /*transform to string of phoneme classes */
    apply_replace_rules_to_str(outword, class_string , &phclass_rules,1);
    debug_printf("phclass %s -> [%s]\n",word, class_string);
    /* apply hyphenation rules */
    apply_replace_rules_to_str(class_string, pattern, &sep_rules,1);
    debug_printf("seprules: %s -> [%s]\n", class_string,pattern);
    
    /* insert seperators as syllable boundaries */
    match_seperators(outword, pattern, outphonemes);
    debug_printf("patterns: %s -> [%s]\n", word, outword);
    
    /* missing here: an additional method to specify stess if it's not defined */
    apply_found_stress(stress, rafforze, outphonemes, phonoword); 
    debug_printf("Becomes: %s -> [%s] -> /%s/\n",word,outword,phonoword);
    
    apply_replace_rules_to_str(phonoword, outphonemes, &PHON_It_rules,1);  /* Rephonemization */
    debug_printf("rephone: %s\n", outphonemes);

    if (rafforze==1)
    {
	ii = FNX_STRLEN(outphonemes);
	outphonemes[ii++] =0x7F;
	outphonemes[ii]='\0';
	FNX_PRINTF("Using rafforzamento sintattico!\n");
    }
    return (1);
}

#ifdef  userules_is_main
main()
{
    int eofcond = 0;
    int ret,len,ii,jj;
    char  word[100], outphonemes[100];
    PLTS nix;
 
#ifdef LINUXSYNTHESIS
    char longbuf[200];
#endif

    char *retbuff;

    nix.magic_environ=0;

  
    while (!eofcond)
    {
	FNX_PRINTF("ITALIANO>");
	
	retbuff = FNX_FGETS(word,80,stdin);
	if (retbuff==NULL || FNX_STRLEN(retbuff)<=1)
	{
	    eofcond=1;
	}
	else
	{
	    ret = FNX_STRLEN(retbuff);
	    // FNX_PRINTF("ret = %i\n",ret);
	    if (ret>0)  retbuff[ret-1]='\0';
	    if (ret==0)
	    {
		eofcond=1;
		break;
	    }

	    italian_word_lts(word, outphonemes,&nix);
	    FNX_PRINTF("%s -> /%s/\n",word,outphonemes);

#ifdef LINUXSYNTHESIS
	    longbuf[0]='\0';

	    FNX_STRCAT(longbuf,"say -a \"[:phon asky on][");
	    len = FNX_STRLEN(outphonemes);
	    jj=FNX_STRLEN(longbuf);
	    for (ii=0;ii<len;ii++)
	    {
		if (outphonemes[ii]=='`')
		{
		    longbuf[jj++] = '\\';
		}
		longbuf[jj++]=outphonemes[ii];
	    }
	    longbuf[jj++]='\0';
	    FNX_STRCAT(longbuf,"]\"");
	    FNX_PRINTF("%s\n",longbuf);
	    system(longbuf);
#endif 
	}
    }
}

#endif /* userules_is_main */
