#include "ruleparse.h"
#include "port.h" //added for platform specific stuff - mlt
//moved to port.h for each platform - mlt
//#include <string.h>
//#include <stdio.h>


#ifdef userulesdebug
//#define debug_printf(fmt,args...) FNX_PRINTF(fmt,## args)
#else
#define debug_printf(fmt,args)
#endif

int string_matches(const ruleblock *R, int indx, char *word, int pos)
{
    const char *cp;
    int len;

    cp = R->sympool[indx];
    len = FNX_STRLEN(cp);
    if (*cp == '#' && len==1)
    {
	if (word[pos] =='\0') return 1;
    }
    if (FNX_STRNCMP(cp,&word[pos],len)==0) return len;
    else return 0;
}

int list_matches(const ruleblock *R, int indx, char *word, int pos)
{
    int p;
    int proceed=0;

    p = indx;

    while(p)
    {
	if (R->list[p].type == STRING)
	{
	    proceed = string_matches(R, R->list[p].data , word, pos);
	    // FNX_PRINTF("in list match: string_match delivers: %d\n",proceed);

	    if (proceed != 0) return proceed;
	    else p=R->list[p].next;
	}
	if (R->list[p].type == LIST_HEADER)
	{
	    proceed = list_matches(R, R->list[p].data, word, pos);
	    // FNX_PRINTF("in list match: list_match delivers: %d\n",proceed);
	    if (proceed != 0) return proceed;
	    else p=R->list[p].next;
	}

    }
    return proceed;
}

int checkseqright(char *word, int seqpos, int inlistpos, const ruleblock *R)
{
    int lpos;
    int currpos;
    int proceed=0;

    currpos = seqpos;
    lpos = inlistpos;

nextcheckright:

    if (R->list[lpos].type == STRING)
    {  
	proceed = string_matches(R, R->list[lpos].data, word, currpos);
	// FNX_PRINTF("string_match delivers: %d\n",proceed);
	if (proceed==0) return 0;
    }

    if (R->list[lpos].type == LIST_HEADER)
    {
	proceed = list_matches(R, R->list[lpos].data, word, currpos);
	// FNX_PRINTF("list_match delivers: %d\n",proceed);
	if (proceed==0) return 0;
    }
    
    currpos += proceed;

    lpos = R->list[lpos].next;
    if (lpos == 0) return 1;
    else goto nextcheckright;
}

int left_string_matches(const ruleblock *R, int indx, char *word, int pos)
{
    const char *cp;
    int len;
    
    cp = R->sympool[indx];
    len = FNX_STRLEN(cp);
    if (*cp == '#' && len==1)
    {
	if (pos==-1) return 1; // left boundary
    }
    if ((pos-len+1)<0) 
	{
	    return 0;     
	}
    if (FNX_STRNCMP(cp,&word[pos-len+1],len)==0) return len;
    else return 0;
}


int left_list_matches(const ruleblock *R, int indx, char *word, int pos)
{
    int p;
    int receed=0;
    
    p = indx;

    while(p)
    {
	if (R->list[p].type == STRING)
	{
	    receed = left_string_matches(R, R->list[p].data , word, pos);

	    if (receed != 0) return receed;
	    else p=R->list[p].next;
	}
	if (R->list[p].type == LIST_HEADER)
	{
	    receed = left_list_matches(R, R->list[p].data, word, pos);

	    if (receed != 0) return receed;
	    else p=R->list[p].next;
	}

    }
    return receed;
}

int checkseqleft(char *word, int seqpos, int inlistpos, const ruleblock *R)
{
    int lpos;
    int currpos;
    int receed=0;

    currpos = seqpos;
    lpos = inlistpos;

nextcheckleft:

    if (R->list[lpos].type == STRING)
    {  
	receed = left_string_matches(R, R->list[lpos].data, word, currpos);
	if (receed==0) return 0;
    }

    if (R->list[lpos].type == LIST_HEADER)
    {
	receed = left_list_matches(R, R->list[lpos].data, word, currpos);
	if (receed==0) return 0;
    }
    
    currpos -= receed;

    lpos = R->list[lpos].next;
    if (lpos == 0) 
    {
	return 1;   // currpos;
    }
    else 
    {
	goto nextcheckleft;
    }

}

int check_rule_environment(char *word,int wordlength, int currpos,int lenfrom,const ruleblock *R, const ruletable *rule)
{
    int seqpos;
    int next;
    
    if (rule->leftenv == 0 && rule->rightenv==0) return 1;  // no rules always true

    if (rule->leftenv != 0)
    {
	seqpos = currpos-1;          // left environment starts at seqpos
	if (seqpos < -1) return 0;   // rules applied way beyond wordboundary always wrong
	next = rule->leftenv;
	while (next !=0)
	{
	    if (checkseqleft(word,seqpos, R->list[next].data, R) == 1)  
	    {
		if (rule->rightenv == 0) return 1;
		else goto checkrightrules;
	    }
	    next = R->list[next].next;  // try next left rule.
	}
	return 0;
    }

checkrightrules:

    if (rule->rightenv != 0)
    {
	seqpos = currpos+lenfrom;   // right environment starts at seqpos
	if (seqpos > wordlength) return 0;
	next = rule->rightenv;
	while (next != 0)
	{
	    if (checkseqright(word, seqpos, R->list[next].data, R) == 1) return 1;
	    next = R->list[next].next;
	}
	return 0;
    }
    return 0;
}


int apply_replace_rules_to_str(char *word, char *outword, const ruleblock *R, int skipmethod)
{
    int wordlength,lencp;
    int currpos;
    int nrul;
    int succeed;
    const char *cp, *cpout;
    char *outp;
    char cc;
    const ruletable *rule;
    
    wordlength = FNX_STRLEN(word);
    currpos = 0;
    outp = &outword[0];

    *outp = '\0';

    while (currpos <= wordlength)
    {
	succeed=0;
	for (nrul = 0; nrul < R->nrules; nrul++)
	{
	    rule = &(R->rule[nrul]);
	    if (rule->from == 0) 
	    {
		cp = NULL;                // The case NIL > "." 
		lencp=0;
		if (check_rule_environment(word,wordlength,currpos,lencp,R,rule)==1)
		{
		    cpout = R->sympool[rule->to];
		    
		    while ((cc = *cpout++)) 
		    {
			*outp++ = cc;
		    };
		    
		    *outp = '\0';
//		    debug_printf("rule %d with NIL -> %s worked at pos %d\n",nrul, R->sympool[rule->to], currpos);
		    currpos += 1;
		    succeed=1;
		    goto breakout;   // always start at first rule.
		}
	    }
	    else                        // The case "x" > "y"
	    {
		cp = R->sympool[rule->from];
		lencp=FNX_STRLEN(cp);
		if (word[currpos] == cp[0])
		{
		    lencp = FNX_STRLEN(cp);
		    if (FNX_STRNCMP(&word[currpos],cp,lencp)==0)
		    {
			if (check_rule_environment(word,wordlength,currpos,lencp,R,rule)==1)
			{
			    cpout = R->sympool[rule->to];
			    
			    while ((cc = *cpout++))       // (remark: for "x">NIL cpout points to empty string.)
			    {
				*outp++ = cc;
			    };
			    
			    *outp = '\0';
//			    debug_printf("rule %d with left sym %s -> %s worked at pos %d\n",nrul,cp, R->sympool[rule->to], currpos);
			    currpos += lencp;
			    succeed=1;
			    goto breakout;   // always start at first rule.
			}
		    }
		}
	    }
	}
    breakout:  
	if (succeed==0) 
	    {
		if (skipmethod == 0) 	
		{
		    currpos += 1;   // in case no rule hits, skip the letter
		}
		
		if (skipmethod == 1)
		{
		    *outp++ = word[currpos];
		    *outp = '\0';
		    currpos += 1;
		}
	    }
    }    
    return 1;
}
    
