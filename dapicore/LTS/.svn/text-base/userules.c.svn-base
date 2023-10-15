#include "ruleparse.h"
#include "port.h" //added for platform specific stuff - mlt
//moved to port.h for each platform - mlt
//#include <string.h>
//#include <stdio.h>
#include "bachregverb.h"
#include "bachdictit.h"
#include "bachitsyll.h"
#include "replacerules.h"

//#define userulesdebug
//#define LINUXSYNTHESIS
//#define userules_is_main


#ifdef userulesdebug
//#define debug_printf(fmt,args...) FNX_PRINTF(fmt,## args)
#else
#define debug_printf(fmt,args)
#endif

#ifdef userulesdebug
char ls_lower[]={
#include "ls_lower.tab"
};
#else
#include "ls_cons.h"
#endif


//WalkCNTXT Walkercntxt;   // not constant.


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


int IT_stress_type_from_verb_grammar(char *word, char *outword, int *rafforze,int *preposition,
				  IT_WalkCNTXT *wcnt, const IT_wordgrammarinfo *gramm)
{
    int anaret;
    int enclitic,stress;
    int i;
    char descriptor[8]; // sure rules are no longer than 5 bytes

    anaret = IT_analyse_word(word, outword, descriptor, wcnt, gramm);
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
  
   If a word is an unstressed preposition, the grammar sets the first
   letter to 'p' and we note it. 
 */

    enclitic=0; 
    for (i=0; descriptor[i] != '\0'; i++) if (descriptor[i]=='x') enclitic = 1;
    
    *rafforze=0;
    *preposition=0;
    if (descriptor[0]=='r') *rafforze =  1;            // rafforzamento sintattico
    if (descriptor[0]=='c') *rafforze = -1;            // clitic preposition - no stress!
    if (descriptor[0]=='p') *preposition=1;

    switch (descriptor[1])      
    {
	case '1':   stress = 1 + enclitic;  break;
	case '2':   stress = 2 + enclitic;  break;
	case '3':   stress = 3 + enclitic;  break;
	case '4':   stress = 4;  break;
	default:    stress = 0;  break;
    }
    
    if (*rafforze== -1) stress=0;
    if (*preposition==1) stress=0;
    
    return stress;
}

void apply_found_stress(int stressshould, int rafforze, int preposition, char *phonemes, char *outphonemes)
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

    if ((stress <= 0 && nsyll == 1) || rafforze == -1 || preposition==1)
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

/*
    if (mark >= 3)
    {
	outphonemes[jj++] ='`';
    }

  */
   for (ii=0;ii<len;ii++)
    {
	outphonemes[jj++] = phonemes[ii];
	if (phonemes[ii]=='-')
	{
	    nsyll += 1;
	    if (nsyll < (mark-1) && (nsyll%2) == 0)
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
	if (cc != '\'' && cc != '`') *out++ = cc;
    }
    *out = '\0';
    return;
}

// word by word processor 
// needs infomation about it's environment. 


char italian_tolower(char foo)
{
    return ls_lower[(unsigned char) foo ];
/*
    switch (foo)
    {
	case 'Á':  return 'á';
	case 'É':  return 'é';
	case 'Í':  return 'í';
	case 'Ó':  return 'ó';
	case 'Ú':  return 'ú';
	case 'À':  return 'à';
	case 'È':  return 'è';
	case 'Ì':  return 'ì';
	case 'Ò':  return 'ò';
	case 'Ù':  return 'ù';
	case 'Ä':  return 'ä';
	case 'Ë':  return 'ë';
	case 'Ï':  return 'ï';
	case 'Ö':  return 'ö';
	case 'Ü':  return 'ü';
        default:
	    return (FNX_TOLOWER(foo));
    }
*/
}


/* Investigate if the word can be analysed according to Italian syllable 
   structure, using the syllable word-grammar. 
*/
int italian_phonotactics(char *word, char *junk,IT_WalkCNTXT *Walkercntxt)
{
    return IT_analyse_word(word, junk, junk+IT_MAXRULEBUFLEN,  Walkercntxt, &syll_WordGrammar);
}

int spell_it_single_letter(char foo, char *outphonemes, char *junk, PLTS_T  pLts_t)
{
    char two[2];
    
    two[0]=foo; 
    two[1]='\0';
    return italian_word_lts_normal(two, outphonemes, junk, pLts_t);
}

int spell_it_letterbyletter(char *word, char *outphonemes, char *junk, PLTS_T  pLts_t)
/* word is not readonly */
{
    int i,len,ltot;
    char shortword[12], two[2];
    len = FNX_STRLEN(word);
    ltot=0;
    outphonemes[0]='\0';
    two[1]='\0';
    for (i=0;i<len;i++)
    {
	two[0]=word[i];
	italian_word_lts_normal(two, shortword, junk, pLts_t);
	ltot += (FNX_STRLEN(shortword) + 1);
	if (shortword[0]!='\'') ltot +=1;
	
	if (ltot<IT_MAXRULEBUFLEN)   // truncate if string would be too long.
	{
	    if (shortword[0]!='\'') FNX_STRCAT(outphonemes,"\'");  // put stress if there isn't
	    FNX_STRCAT(outphonemes,shortword);
	    FNX_STRCAT(outphonemes," ");
	}
    }
        
    return 1;
}


int italian_word_lts(char *inword, char *outphonemes,char *junkbuffer, PLTS_T pLts_t)
{
    int i, jj, len;
    char *lowcase;
    char *junk;

    lowcase = junkbuffer;
    junk = lowcase+IT_MAXRULEBUFLEN; 

    len = FNX_STRLEN(inword);

    if (len==1)
    {
	if (inword[0]>='A' && inword[0]<='Z') 
	    // && pLts_t->index != 1)
	{
	    return spell_it_single_letter(italian_tolower(inword[0]), outphonemes, junk, pLts_t);  // it: italian.
	}
	else
	{
	    lowcase[0]=italian_tolower(inword[0]);
	    lowcase[1]='\0';
	    return italian_word_lts_normal(lowcase, outphonemes, junk, pLts_t);
	}
    }
    
    jj=0;
    for (i=0;i<len;i++)
	if (inword[i]>='A' && inword[i]<='Z') jj += 1;
    
    for (i=0;i<len;i++) lowcase[i] = italian_tolower(inword[i]);  
    lowcase[len]='\0';
    
    //  if several letters are capitalized, decide whether the word can
    //  be pronounced (phonotactics). If so pronounce it, otherwise
    //  spell it. 
    
    if (jj>1)
    {
	if (italian_phonotactics(lowcase,junk,&pLts_t->wunion.IT_Walkercntxt))
	{
	    return italian_word_lts_normal(lowcase, outphonemes,junk, pLts_t);
	}
	else
	{
	    return spell_it_letterbyletter(lowcase, outphonemes, junk, pLts_t);
	}
    }
    else
    {
	return italian_word_lts_normal(lowcase, outphonemes,junk, pLts_t);
    }
}


int italian_word_lts_normal(char *inword, char *outphonemes, char *junk, PLTS_T pLts_t)
{
    int ii,j, stress;
    
//    char  word[100], outword[100],  phonoword[100];
//    char  class_string[100],  pattern[100];
    
    char  *word, *outword,  *phonoword;
    char  *class_string,  *pattern;
    int   rafforze,preposition;

    word = junk;
    outword=junk+IT_MAXRULEBUFLEN;
    phonoword=junk+(2*IT_MAXRULEBUFLEN);
    class_string=junk+(3*IT_MAXRULEBUFLEN);
    pattern = junk+(4*IT_MAXRULEBUFLEN);
    
//    pLts_t->magic_environ=1;        //
    
    rafforze=0;
    preposition=0;


    ii = IT_analyse_word(inword, outword, outphonemes, &pLts_t->wunion.IT_Walkercntxt, &exceptions_WordGrammar);
    if (ii!=0) return (1);

    stress = IT_stress_type_from_verb_grammar(inword, 
					   outword,  
					   &rafforze,             /* set to 1 if rafforzamento sintaticco for next word */
					   &preposition,
					   &pLts_t->wunion.IT_Walkercntxt,  
					   &regverb_WordGrammar);

    remove_deletion_marker(inword,word);

//    stress=1; /* just jockeling around */

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
//    debug_printf("phclass %s -> [%s]\n",word, class_string);
    /* apply hyphenation rules */
    apply_replace_rules_to_str(class_string, pattern, &sep_rules,1);
//    debug_printf("seprules: %s -> [%s]\n", class_string,pattern);
    
    /* insert seperators as syllable boundaries */
    match_seperators(outword, pattern, outphonemes);
//    debug_printf("patterns: %s -> [%s]\n", word, outword);
    
    /* missing here: an additional method to specify stess if it's not defined */
    apply_found_stress(stress, rafforze, preposition, outphonemes, phonoword); 
//    debug_printf("Becomes: %s -> [%s] -> /%s/\n",word,outword,phonoword);
    
    apply_replace_rules_to_str(phonoword, outphonemes, &PHON_It_rules,1);  /* Rephonemization */
    debug_printf("rephone: %s\n", outphonemes);

    if (rafforze==1)
    {
	ii = FNX_STRLEN(outphonemes);
	outphonemes[ii++] =0x7F;
	outphonemes[ii]='\0';
	//FNX_PRINTF("Using rafforzamento sintattico!\n");
    }

    if (preposition==1)
    {
	ii = FNX_STRLEN(outphonemes);
	for (j=ii; j>0; j--) outphonemes[j] = outphonemes[j-1];
	outphonemes[0] = '(';
    }

    return (1);
}

#ifdef  userules_is_main
main()
{
    int eofcond = 0;
    int ret,len,ii,jj;
    char  word[100], outphonemes[100];
    char  junkbuffer[IT_MAXRULEALLBUFFERLENGTH];

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

	    italian_word_lts(word, outphonemes,junkbuffer, &nix);
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
