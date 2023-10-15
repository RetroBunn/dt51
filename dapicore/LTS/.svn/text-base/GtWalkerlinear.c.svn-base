#include "bachusit.h"

//moved to port.h for each platform - mlt
//#include <string.h>

#define jumpmacro(RES,pos,poslab,CNT,NX,NW,NS) \
	IT_pushjump(cntxt,pos); \
	cntxt->STK[NST+1].curr=NX; \
	cntxt->STK[NST+1].oldwalki=NW; \
	NST+=1; \
	goto startpos; \
poslab: \
	NST-=1; \
	RES=cntxt->STK[NST+1].newwalki;



IT_Jumpstack IT_popjump(IT_WalkCNTXT *cntxt)
{
//    FNX_PRINTF("popjump %d top=%d\n",cntxt->jmpstack[(cntxt->jmptop)], cntxt->jmptop);
    if (cntxt->jmptop==0) return -1;                 
    else return (cntxt->jmpstack[--(cntxt->jmptop)]);
}

int IT_pushjump(IT_WalkCNTXT *cntxt, IT_Jumpstack val)
{
//    FNX_PRINTF("pushjump %d top=%d \n",val,cntxt->jmptop);
    if (cntxt->jmptop+1 > cntxt->maxlevel) cntxt->maxlevel= cntxt->jmptop+1;  /* Keep track */
    if (cntxt->jmptop >= IT_MAXNESTING) return -1;       /* crash and burn in this case */
    else cntxt->jmpstack[(cntxt->jmptop)++] = val;
    return 0;
}


BOOL IT_is_a_vowelgrapheme(ASCIILETTER c)
{
  if (c=='a' || c =='e' || c=='i' || c=='o' || c == 'u'|| c == 'y' ||
      c=='A' || c=='E' || c == 'I' || c=='O' || c == 'U'|| c=='Y' ||
      c == UML_A || c == UML_O || c == UML_U ||
      c == UML_a || c == UML_o || c == UML_u )
    return 1;
  else
    return 0;
}

BOOL IT_is_a_consonantgrapheme(ASCIILETTER c)
{
  if (c >= 'a' && c<= 'z' && !IT_is_a_vowelgrapheme(c)) return 1;
  else return 0;
}



IT_walkinfo  IT_GtWalkerLinear(IT_WalkCNTXT *cntxt, U16 curr, IT_walkinfo oldwalki, int NST)
{
//    int i,j;
//    U16 match;
//    walkinfo newwalki;

    int position;
    IT_pushjump(cntxt,-1);
 
    cntxt->STK[NST].curr = curr;    
    cntxt->STK[NST].oldwalki = oldwalki;

 startpos: 
    position=0;

    cntxt->STK[NST].phonemestring = NULL;
    cntxt->STK[NST].rulenumber=0;
    cntxt->STK[NST].ii = 0; 
    cntxt->STK[NST].jj = 0;
    cntxt->STK[NST].j1 = 0;
    cntxt->STK[NST].j2 = 0;
    cntxt->STK[NST].incr = 0;

    cntxt->counter += 1;
    // (cntxt->level)++;
    // if (cntxt->level > cntxt->maxlevel) cntxt->maxlevel= cntxt->level;  /* Keep track */
    
    
    if (cntxt->counter > IT_MAXRECURSIONS)
    { 
	cntxt->alert=1;
#ifdef BACHUS_IN_DECTALK
      cntxt->STK[NST].newwalki = cntxt->STK[NST].oldwalki;
      cntxt->STK[NST].newwalki.succeeded = 1;     // unfortunately it will loop here a while.
// succeeded is set to 1 which seems odd. However, this should prevent the
// thing from trying to call itself even more
      goto walkexit;
#else 
#ifdef FROMTYPED
      FNX_PRINTF("I give up\n"); 
      // GtrieStatisitics(cntxt->Nodes,cntxt->nnodes);
      exit(1);
#endif
#endif
    }
   

/* new: find out if we have already called ourselves too often */

  if (cntxt->jmptop >= IT_MAXNESTING)
    { 
      cntxt->alert=2;
#ifdef BACHUS_IN_DECTALK
      cntxt->STK[NST].newwalki = cntxt->STK[NST].oldwalki;
      cntxt->STK[NST].newwalki.succeeded = 1;     // unfortunately it will loop here a while.
      goto walkexit;
#else 
#ifdef FROMTYPED
      FNX_PRINTF("I give up: too deep nesting by GtWalker calling itself\n"); 
      GtrieStatisitics(cntxt->Nodes,cntxt->nnodes);
      exit(1);
#endif
#endif
    }
  cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki;  // newwalki = oldwalki;
  if (cntxt->alert) goto walkexit;

  if (cntxt->wordlength == cntxt->STK[NST].newwalki.wordpos) 
    { 
      //      FNX_PRINTF("End of word reached\n");
      if (cntxt->STK[NST].newwalki.succeeded==1) goto walkexit;
    }

 switchboard:

  switch (position)
  {
      case 0: break;
      case 1: goto jump1;
      case 2: goto jump2;
      case 3: goto jump3;
      case 4: goto jump4;
      case 5: goto jump5;
      case 6: goto jump6;
      case 7: goto jump7;
      case 8: goto jump8;
      case 9: goto jump9;
      case 10: goto jump10;
      case 11: goto jump11;
      case 12: goto jump12;
      case 13: goto jump13;
      case 14: goto jump14;
#ifdef IT_OPERATORS_NEEDED_IN_WALKER
      case 15: goto jump15;
#endif
      case 16: goto jump16;
  }

    switch (cntxt->Nodes[cntxt->STK[NST].curr].typeinfo)
      {
	  // End of path occurs only on the highest level of the grammar tree.
	  // Here we need to decide whether the path of the grammar was parsed.
	  // For the original bachus this decision simply was whether or not
	  // the end of the word was reached. 
      case ENDOFPATH:  
	// FNX_PRINTF("ENDOFPATH: NTOK ON STACK: %i\n",cntxt->nstack.ntok);
	  cntxt->STK[NST].newwalki.succeeded = (cntxt->wordlength == cntxt->STK[NST].newwalki.wordpos 
				|| cntxt->theword[cntxt->STK[NST].newwalki.wordpos]==' ');  
	  // cntxt->STK[NST].newwalki.succeeded = (cntxt->wordlength == cntxt->STK[NST].newwalki.wordpos);       // generalize this.
	if (!cntxt->STK[NST].newwalki.succeeded) {cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki; cntxt->STK[NST].newwalki.succeeded=0;}
	break;

      case PATHRETURN: 
	cntxt->STK[NST].next = IT_popNode(&cntxt->nstack);

//	newwalki = GtWalker(cntxt,cntxt->STK[NST].next,newwalki,NST+1); 
	jumpmacro(cntxt->STK[NST].newwalki,1,jump1,cntxt,cntxt->STK[NST].next,cntxt->STK[NST].newwalki,NST+1); 
	//jumpmacro(cntxt->STK[NST].next,1,jump1);

	if (cntxt->STK[NST].newwalki.succeeded==0)
	  {
	    IT_pushNode(&cntxt->nstack,cntxt->STK[NST].next);    // push it back to keep stack intact
	  }
	break;

      case EPSILONNODE:
	IT_pushNode(&cntxt->nstack,0);
	cntxt->STK[NST].next = cntxt->Nodes[cntxt->STK[NST].curr].alt;              // point to first startnode
	jumpmacro(cntxt->STK[NST].newwalki,2,jump2,cntxt,cntxt->STK[NST].next,cntxt->STK[NST].newwalki, NST+1);

	break;
	
      case STARTNODE:                      // startnode always calls an altnode 
	/* This behaves like a subroutine call */
	// FNX_PRINTF("St:%s\n",cntxt->Nodes[cntxt->STK[NST].curr].name);
	//FNX_PRINTF(" Startnode: NTOK ON STACK: %i\n",cntxt->nstack.ntok);
	if (cntxt->STK[NST].curr==1)
	{
	    cntxt->STK[NST].next = cntxt->STK[NST].newwalki.altnode;
	    cntxt->STK[NST].newwalki.altnode = 0;
	}
	else
	{
	    cntxt->STK[NST].next = cntxt->Nodes[cntxt->STK[NST].curr].right;     
	}
        jumpmacro(cntxt->STK[NST].newwalki,3,jump3,cntxt,cntxt->STK[NST].next,cntxt->STK[NST].newwalki, NST+1);

	break; 

      case ALTNODE:
	/* For each of the current and alt nodes call the right sides
	   until one returns succeeded. */
	cntxt->STK[NST].next = cntxt->STK[NST].curr;
newalt:	    

	jumpmacro(cntxt->STK[NST].newwalki,4,jump4,cntxt,cntxt->Nodes[cntxt->STK[NST].next].right,cntxt->STK[NST].newwalki,NST+1);      

#ifdef GRAMMAR_EVALUATION
	if (cntxt->STK[NST].newwalki.succeeded==1)              // evaluation mode: count how often the 
	                                        // grammar's lines where used successfully
	  {
	    cntxt->Nodes[cntxt->STK[NST].next].info.counter += 1;   // this one is usually readonly!
	  }
#endif /* GRAMMAR_EVALUATION */

/* Note: In what follows, if multiple choice parsing is set, the parser 
   will try to parse the cntxt->STK[NST].next rule line on the highest level after
   one line was a success. 
   Otherwise, if it is not set, it will just return upon success. 
   So parsing will end after walker found the very first match.
*/

	if (cntxt->STK[NST].newwalki.succeeded==1) 
	{
#ifdef MULTIPLE_CHOICE_PARSING
	    if (cntxt->Nodes[cntxt->STK[NST].next].info.status==1) 
	    {
		cntxt->STK[NST].newwalki.altnode = cntxt->Nodes[cntxt->STK[NST].next].alt;
	    }
#endif /* Multiple choice */
	    goto walkexit; //return cntxt->STK[NST].newwalki;
	}
	else 
	  {
	    cntxt->STK[NST].next = cntxt->Nodes[cntxt->STK[NST].next].alt;
	    if (cntxt->STK[NST].next) goto newalt;
	  }
	break;
	
      case LOOPNODE:
	// get the loop counters from the information part of the node
	cntxt->STK[NST].j1 = cntxt->Nodes[cntxt->STK[NST].curr].info.counter;
	cntxt->STK[NST].j2 = cntxt->Nodes[cntxt->STK[NST].curr].info.counterB;

	cntxt->STK[NST].alt = cntxt->Nodes[cntxt->STK[NST].curr].alt;       // address of continue node (JUMPNODE)
	cntxt->STK[NST].next = cntxt->Nodes[cntxt->STK[NST].alt].right;     // address of node after continue 
	cntxt->STK[NST].what = cntxt->Nodes[cntxt->STK[NST].curr].right;    // address of first node inside loop
	IT_pushNode(&cntxt->nstack,cntxt->STK[NST].next);   // push on stack: the continuation after the loop
	//     FNX_PRINTF("alt is %i cntxt->STK[NST].next is %i right is %i\n",cntxt->STK[NST].alt,cntxt->STK[NST].next,what);
	if (cntxt->STK[NST].j1>cntxt->STK[NST].j2)
	  {
	    cntxt->STK[NST].j=cntxt->STK[NST].j2;
	    cntxt->STK[NST].j2=cntxt->STK[NST].j1;
	    cntxt->STK[NST].incr=-1;
	    cntxt->STK[NST].j1=cntxt->STK[NST].j;
	    cntxt->STK[NST].jj=cntxt->STK[NST].j2;
	  }
	else
	  {
	    cntxt->STK[NST].jj=cntxt->STK[NST].j1;
	    cntxt->STK[NST].incr=1;
	  }
	/* the following loop pushes on the stack the first node inside of the 
	   loop as often as the loop has to be excecuted. */

	for (cntxt->STK[NST].j=cntxt->STK[NST].j1; 
	     (cntxt->STK[NST].j<=cntxt->STK[NST].j2) && (cntxt->STK[NST].newwalki.succeeded==0); cntxt->STK[NST].j++)
	  {
	    //   FNX_PRINTF("loop cntxt->STK[NST].jj= %i\n",cntxt->STK[NST].jj);
	    cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki;
	    for (cntxt->STK[NST].ii=0;cntxt->STK[NST].ii<cntxt->STK[NST].jj;cntxt->STK[NST].ii++)  // start of repeated path to stack
	      {
	        IT_pushNode(&cntxt->nstack,cntxt->STK[NST].what);
	      }
	    jumpmacro(cntxt->STK[NST].newwalki,5,jump5,cntxt,cntxt->STK[NST].alt,cntxt->STK[NST].newwalki,NST+1);     // execute the continue node
	    if (cntxt->STK[NST].newwalki.succeeded == 0)
	      {
		for (cntxt->STK[NST].ii=0;cntxt->STK[NST].ii<cntxt->STK[NST].jj;cntxt->STK[NST].ii++) 
		  {
		    cntxt->STK[NST].next=IT_popNode(&cntxt->nstack);   
		  }
	      }
	    cntxt->STK[NST].jj += cntxt->STK[NST].incr;
	  }
	if (!cntxt->STK[NST].newwalki.succeeded) cntxt->STK[NST].next=IT_popNode(&cntxt->nstack);
	break;                            

      case JUMPNODE:                                // This is a continue node
	cntxt->STK[NST].next = IT_popNode(&cntxt->nstack);             // get from stack from loop
	jumpmacro(cntxt->STK[NST].newwalki,6,jump6,cntxt,cntxt->STK[NST].next,cntxt->STK[NST].newwalki,NST+1);
	if (cntxt->STK[NST].newwalki.succeeded==0)
	  {
	    IT_pushNode(&cntxt->nstack,cntxt->STK[NST].next);  // push back
	  }
	break;                            // work on this later.
	
      case NONTERMINAL:
	IT_pushNode(&cntxt->nstack,cntxt->Nodes[cntxt->STK[NST].curr].right); 
	jumpmacro(cntxt->STK[NST].newwalki,7,jump7,cntxt,cntxt->Nodes[cntxt->STK[NST].curr].what,cntxt->STK[NST].newwalki,NST+1); 
	if (cntxt->STK[NST].newwalki.succeeded==0)
	  {
	    cntxt->STK[NST].next = IT_popNode(&cntxt->nstack);
	  }
	break;

      case NOPNODE:
	/* this funny node (no operation node) was introduced to make life simpler in the grammar 
	   definition. Currently, all it does, is calling the cntxt->STK[NST].next node if there is one. this
	   makes it possible that backtracking can proceed also through this node.
	*/
	cntxt->STK[NST].next = cntxt->Nodes[cntxt->STK[NST].curr].right;
	jumpmacro(cntxt->STK[NST].newwalki,8,jump8,cntxt,cntxt->STK[NST].next,cntxt->STK[NST].newwalki,NST+1);
	break;

      case BOUNDACTION:
	/* this node inserts strings (e.g. '+', or '=') into the output to mark boundaries
           other than that operates just like the NOP node. */
	cntxt->STK[NST].next = cntxt->Nodes[cntxt->STK[NST].curr].right;
	cntxt->STK[NST].currpos = cntxt->STK[NST].oldwalki.wordpos;           // current position in the word.
	jumpmacro(cntxt->STK[NST].newwalki,9,jump9,cntxt,cntxt->STK[NST].next,cntxt->STK[NST].newwalki,NST+1);
	if (cntxt->STK[NST].newwalki.succeeded==1) IT_register_word_part(cntxt,
						      cntxt->Nodes[cntxt->STK[NST].curr].name,
						      PROSODICMARKER,
						      cntxt->STK[NST].currpos,
						      cntxt->STK[NST].currpos,
						      1,           // register the little string: case 1
						      NULL,0);     // no phonemes
	break;

      case SKIPNODE:
	cntxt->STK[NST].currpos = cntxt->STK[NST].oldwalki.wordpos;           // current position in the word.
	cntxt->STK[NST].ii=-1;
	if (cntxt->STK[NST].currpos <= cntxt->wordlength)
	  {
	    for (cntxt->STK[NST].i=cntxt->STK[NST].currpos ; cntxt->STK[NST].i<=cntxt->wordlength; cntxt->STK[NST].i++)
	      {
		if (cntxt->theword[cntxt->STK[NST].i]==' ')
		  {
		    cntxt->STK[NST].ii = cntxt->STK[NST].i;
		    break;
		  }
	      }
	    if (cntxt->STK[NST].ii>=0)     // if matches 
	      {
		// FNX_PRINTF("SKIP: End of word reached at position %i\n",cntxt->STK[NST].ii);
		cntxt->STK[NST].newwalki.wordpos = cntxt->STK[NST].ii;           // proceed by the number of letters found.
		jumpmacro(cntxt->STK[NST].newwalki,10,jump10,cntxt,cntxt->Nodes[cntxt->STK[NST].curr].right,cntxt->STK[NST].newwalki,NST+1);
		if (cntxt->STK[NST].newwalki.succeeded==1)
		  {
		    // copy phoneme part to work buffer in the context structure:
		    cntxt->STK[NST].j2 = FNX_STRLEN(cntxt->Nodes[cntxt->STK[NST].curr].name);
		    for (cntxt->STK[NST].i=0; cntxt->STK[NST].i<cntxt->STK[NST].j2; cntxt->STK[NST].i++) 
		    {
			cntxt->workbuffer[cntxt->STK[NST].i] = cntxt->Nodes[cntxt->STK[NST].curr].name[cntxt->STK[NST].i];
		    }
		    cntxt->workbuffer[cntxt->STK[NST].j2]='\0';       // terminate string
		    
		    cntxt->STK[NST].phonemestring = cntxt->workbuffer;
		    
		    //FNX_PRINTF("Phonemestring: /%s/. Rule No: %d \ncntxt->STK[NST].Currpos %d cntxt->STK[NST].ii %d\n",
		    //	   phonemestring,rulenumber,cntxt->STK[NST].currpos,cntxt->STK[NST].ii);
		    IT_register_word_part(cntxt,
				       "skipped",
				       SKIPNODE,
				       cntxt->STK[NST].currpos,
				       (unsigned short)(cntxt->STK[NST].ii-1),
				       0,
				       " ",   
				       0);    // rule number n/a 
		  }
		else
		  {
		    cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki;                   // backtracking
		    cntxt->STK[NST].newwalki.succeeded=0;
		  }
	      }  
	  }
	break;

/* Skipping individual letters: We proceed by one letter and try the
   rest of the grammar path. We only proceed by one letter within a word.
   So if we hit a blank or the end of the complete string, we return with
   success set to zero. 
*/
      case SKIPLETTERNODE:
	cntxt->STK[NST].currpos = cntxt->STK[NST].oldwalki.wordpos;  
	if (cntxt->STK[NST].currpos <= cntxt->wordlength)
	  {
	    cntxt->STK[NST].ii = cntxt->STK[NST].currpos+1;
	    if (cntxt->theword[cntxt->STK[NST].ii]=='\0' || cntxt->theword[cntxt->STK[NST].ii]==' ')
	      {
		cntxt->STK[NST].newwalki.succeeded=0;
	      }
	    else
	      {
		cntxt->STK[NST].newwalki.wordpos = cntxt->STK[NST].ii;           // go to cntxt->STK[NST].next letter
		jumpmacro(cntxt->STK[NST].newwalki,11,jump11,cntxt,cntxt->Nodes[cntxt->STK[NST].curr].right,cntxt->STK[NST].newwalki,NST+1);
	      }

	    if (cntxt->STK[NST].newwalki.succeeded==1)
	      {
		// copy phoneme part to work buffer in the context structure:
		cntxt->STK[NST].j2 = FNX_STRLEN(cntxt->Nodes[cntxt->STK[NST].curr].name);
		for (cntxt->STK[NST].i=0; cntxt->STK[NST].i<cntxt->STK[NST].j2; cntxt->STK[NST].i++) 
		{
		    cntxt->workbuffer[cntxt->STK[NST].i] = cntxt->Nodes[cntxt->STK[NST].curr].name[cntxt->STK[NST].i];
		}
		cntxt->workbuffer[cntxt->STK[NST].j2]='\0';       // terminate string
		
		cntxt->STK[NST].phonemestring = cntxt->workbuffer;
		
		//FNX_PRINTF("Phonemestring: /%s/. Rule No: %d \ncntxt->STK[NST].Currpos %d cntxt->STK[NST].ii %d\n",
		//       phonemestring,rulenumber,cntxt->STK[NST].currpos,cntxt->STK[NST].ii);
		/*
		register_word_part(cntxt,
				   "-",
				   SKIPLETTERNODE,
				   cntxt->STK[NST].currpos,
				   cntxt->STK[NST].ii-1,
				   0,
				   "+",   
				   0);  */     // rule number n/a 
	      }
	    else
	      {
		cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki;                   // backtracking
		cntxt->STK[NST].newwalki.succeeded=0;
	      }
	  }
      
	break;
	
	
      case SINGLEMORPH:
	/* It's in the name: The name field of the node is a morpheme string
	   and we have to check if the cntxt->STK[NST].next few letters of the word are identical
	   with this string. If they are, we call the subsequent node, and
	   if they are not, we return with succeeded=0 
	*/
	// dumpGTrieNode(Gt,curr);
	cntxt->STK[NST].currpos = cntxt->STK[NST].oldwalki.wordpos;           // current position in the word.

	/* Had to change this. The name field here may now be of the form, e.g.,  "ge g@ 1".
	   The string to compare to is "ge", the phonemestring is "g@" and 
	   the applied rule number is 1 (obtained by atoi in the splitter)
	   This change was needed so that also for inline definitions of 
	   search strings in the rule file, we have an according phoneme string,
	   and if really needed a rule number to apply allophonic variations.
	 */

	split_inline_morph_phonemes(cntxt->Nodes[cntxt->STK[NST].curr].name, // The string containing, e.g, "ge g@ 1"
				    &cntxt->STK[NST].jj,                     // compare length.
				    &cntxt->STK[NST].j1,                     // phoneme start
				    &cntxt->STK[NST].j2,                     // phoneme length,
				    &cntxt->STK[NST].rulenumber);            // usually 0. 
	if (cntxt->STK[NST].currpos+cntxt->STK[NST].jj-1 <= cntxt->wordlength)
	  {
	    cntxt->STK[NST].ii=1;
	    for (cntxt->STK[NST].i=0;cntxt->STK[NST].i<cntxt->STK[NST].jj;cntxt->STK[NST].i++)  // compare char by char 
	      {
		// FNX_PRINTF("%i %i %c %c\n",cntxt->STK[NST].ii,i,cntxt->theword[cntxt->STK[NST].currpos+i],cntxt->Nodes[cntxt->STK[NST].curr].name[i]);
		cntxt->STK[NST].ii = cntxt->STK[NST].ii && (cntxt->theword[cntxt->STK[NST].currpos+cntxt->STK[NST].i] == cntxt->Nodes[cntxt->STK[NST].curr].name[cntxt->STK[NST].i]);
	      }
	    if (cntxt->STK[NST].ii==1)     // if matches 
	      {
		cntxt->STK[NST].newwalki.wordpos =  cntxt->STK[NST].currpos+cntxt->STK[NST].jj;           // proceed by the number of letters found.
		jumpmacro(cntxt->STK[NST].newwalki,12,jump12,cntxt,cntxt->Nodes[cntxt->STK[NST].curr].right,cntxt->STK[NST].newwalki,NST+1);
		if (cntxt->STK[NST].newwalki.succeeded==1)
		  {
		    // copy phoneme part to work buffer in the context structure:
		    for (cntxt->STK[NST].i=0; cntxt->STK[NST].i<cntxt->STK[NST].j2; cntxt->STK[NST].i++)
		    {
			cntxt->workbuffer[cntxt->STK[NST].i] = cntxt->Nodes[cntxt->STK[NST].curr].name[cntxt->STK[NST].i+cntxt->STK[NST].j1];
		    }
		    cntxt->workbuffer[cntxt->STK[NST].j2]='\0';       // terminate string

		    cntxt->STK[NST].phonemestring = cntxt->workbuffer;

		    // FNX_PRINTF("Phonemestring: /%s/. Rule No: %d\n",cntxt->STK[NST].phonemestring,cntxt->STK[NST].rulenumber);
		    
		    IT_register_word_part(cntxt,
				       "morph",
				       MORPHEME,
				       cntxt->STK[NST].currpos,
				       (unsigned short)(cntxt->STK[NST].currpos+cntxt->STK[NST].jj-1),
				       0,
				       cntxt->STK[NST].phonemestring,  // pointing to work buffer in cntxt 
				       cntxt->STK[NST].rulenumber);    // received 
		  }
		else
		  {
		    cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki;                   // backtracking
		    cntxt->STK[NST].newwalki.succeeded=0;
		  }
	      }  
	  } 

	break;

      case WORDBOUNDARY:
	/* It's in the name: The name field of the node is a morpheme string
	   and we have to check if the next few letters of the word are identical
	   with this string. If they are, we call the subsequent node, and
	   if they are not, we return with succeeded=0 
	*/
	// dumpGTrieNode(Gt,curr);
	cntxt->STK[NST].currpos = cntxt->STK[NST].oldwalki.wordpos;           // current position in the word.

	/* Had to change this. The name field here may now be of the form, e.g.,  "ge g@ 1".
	   The string to compare to is "ge", the phonemestring is "g@" and 
	   the applied rule number is 1 (obtained by atoi in the splitter)
	   This change was needed so that also for inline definitions of 
	   search strings in the rule file, we have an according phoneme string,
	   and if really needed a rule number to apply allophonic variations.
	 */

	split_inline_morph_phonemes(cntxt->Nodes[cntxt->STK[NST].curr].name, // The string containing, e.g, "ge g@ 1"
				    &cntxt->STK[NST].jj,                     // compare length.
				    &cntxt->STK[NST].j1,                     // phoneme start
				    &cntxt->STK[NST].j2,                     // phoneme length,
				    &cntxt->STK[NST].rulenumber);            // usually 0. 
	if (cntxt->STK[NST].currpos+cntxt->STK[NST].jj-1 <= cntxt->wordlength)
	  {
	    cntxt->STK[NST].ii=1;
	    for (cntxt->STK[NST].i=0;cntxt->STK[NST].i<cntxt->STK[NST].jj;cntxt->STK[NST].i++)  // compare char by char 
	      {
		// FNX_PRINTF("%i %i %c %c\n",cntxt->STK[NST].ii,i,cntxt->theword[cntxt->STK[NST].currpos+i],cntxt->Nodes[cntxt->STK[NST].curr].name[i]);
		cntxt->STK[NST].ii = cntxt->STK[NST].ii && (cntxt->theword[cntxt->STK[NST].currpos+cntxt->STK[NST].i] == cntxt->Nodes[cntxt->STK[NST].curr].name[cntxt->STK[NST].i]);
	      }
	    if (cntxt->STK[NST].ii==1)     // if matches 
	      {
		cntxt->STK[NST].newwalki.wordpos =  cntxt->STK[NST].currpos+cntxt->STK[NST].jj;           // proceed by the number of letters found.
		jumpmacro(cntxt->STK[NST].newwalki,13,jump13,cntxt,cntxt->Nodes[cntxt->STK[NST].curr].right,cntxt->STK[NST].newwalki,NST+1);
		if (cntxt->STK[NST].newwalki.succeeded==1)
		  {
		    // copy phoneme part to work buffer in the context structure:
		    for (cntxt->STK[NST].i=0; cntxt->STK[NST].i<cntxt->STK[NST].j2; cntxt->STK[NST].i++) 
			{
			    cntxt->workbuffer[cntxt->STK[NST].i] = cntxt->Nodes[cntxt->STK[NST].curr].name[cntxt->STK[NST].i+cntxt->STK[NST].j1];
			}
		    cntxt->workbuffer[cntxt->STK[NST].j2]='\0';       // terminate string
		    cntxt->STK[NST].phonemestring = cntxt->workbuffer;

		    // FNX_PRINTF("Phonemestring: /%s/. Rule No: %d\n",cntxt->STK[NST].phonemestring,cntxt->STK[NST].rulenumber);
		    
		    IT_register_word_part(cntxt,
				       "-",
				       WORDSEPARATOR,
				       cntxt->STK[NST].currpos,
				       (unsigned short)(cntxt->STK[NST].currpos+cntxt->STK[NST].jj-1),
				       0,
				       cntxt->STK[NST].phonemestring,  // pointing to work buffer in cntxt 
				       cntxt->STK[NST].rulenumber);    // received 
		  }
		else
		  {
		    cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki;                   // backtracking
		    cntxt->STK[NST].newwalki.succeeded=0;
		  }
	      }  
	  } 

	break;


      case TERMINAL:                      // go ask a letter trie.
	/* the most complicated part it seems:
	   We ask a letter trie if the subsequent letters of the word
	   can be interpreted as one or multiple morphs that are stored
	   in a letter trie. The number of the letter trie (index) is
	   stored in the node's field what. The subroutine Lt_parse_string
	   returns either none, one or multiple increments by which 
	   the string matching could be proceeded. If there are multiples
	   e.g., "un" and "unter" both match, we try both. In each case
	   we proceed the position in the word by an appropriate number
	   of letters, then call the subsequent nodes and if non comes 
	   back with success we return with succeeded=0
	   Also, if a full path could be found, we register the part
	   of word that was found in a special structure.
	*/

	cntxt->STK[NST].ntrie = cntxt->Nodes[cntxt->STK[NST].curr].what;
	if (cntxt->STK[NST].ntrie==0)
	  {
#ifdef BACHUS_IN_DECTALK
		goto walkexit;
#else
#ifdef FROMTYPED
	    FNX_PRINTF("error: Terminal node %d has no reference to a startnode.\n",cntxt->STK[NST].curr);
	    FNX_PRINTF("We are hosed. Bye! make a better program!!!!\n");
	    exit(1);
#endif
#endif
	  }
	//Lt = &(cntxt->Ltlist[cntxt->STK[NST].ntrie-1]);  // get the appropriate letter trie from the list.  WATCH
	cntxt->STK[NST].currpos = cntxt->STK[NST].oldwalki.wordpos;

	// use different method depending on storage type of Ltrie. 

	if (cntxt->Ltlist[cntxt->STK[NST].ntrie-1].nodetype == 0)
	{
	    cntxt->STK[NST].nalt = 
		IT_Lt_parse_string(cntxt->theword,
				   cntxt->STK[NST].currpos , 
				   &(cntxt->Ltlist[cntxt->STK[NST].ntrie-1]),
				   &cntxt->STK[NST].proceed[0],
				   &cntxt->STK[NST].phonemeindex[0],
				   &cntxt->STK[NST].ruleindex[0],
				   (unsigned short)((cntxt->Nodes[cntxt->STK[NST].curr].info.parameter) & IT_MORPH_ORDER_MASK));  
	}
	else   
	{
	    cntxt->STK[NST].nalt = 
		IT_short_Lt_parse_string(cntxt->theword,
					       cntxt->STK[NST].currpos , 
					       &(cntxt->Ltlist[cntxt->STK[NST].ntrie-1]),
					       &cntxt->STK[NST].proceed[0],
					       &cntxt->STK[NST].phonemeindex[0],
					       &cntxt->STK[NST].ruleindex[0],
					       (unsigned short)((cntxt->Nodes[cntxt->STK[NST].curr].info.parameter) & IT_MORPH_ORDER_MASK));  
	}
	
	cntxt->STK[NST].next = cntxt->Nodes[cntxt->STK[NST].curr].right;
	/*
		FNX_PRINTF("callingnext %s \n",gnodetypename(cntxt->Nodes[next].typeinfo));
    		FNX_PRINTF("Ltrie %d tried on %s at cntxt->STK[NST].currpos=%i yields %i alternatives, Next=%i\n",
	        ntrie,cntxt->theword,cntxt->STK[NST].currpos,cntxt->STK[NST].nalt,next);
	*/
	if (cntxt->STK[NST].nalt > 0)
	  {
	    for (cntxt->STK[NST].i=0; (cntxt->STK[NST].i<cntxt->STK[NST].nalt); cntxt->STK[NST].i++)
	      {
		cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki;
		cntxt->STK[NST].currpos = cntxt->STK[NST].oldwalki.wordpos;
		/*
		         FNX_PRINTF("trying %10s ",cntxt->Nodes[cntxt->STK[NST].curr].name );
			 for (j=cntxt->STK[NST].currpos;j<=cntxt->STK[NST].currpos+cntxt->STK[NST].proceed[i];j++) FNX_PRINTF("%c",cntxt->theword[j]);
			 FNX_PRINTF("\n");
		*/

		cntxt->STK[NST].newwalki.wordpos =  cntxt->STK[NST].currpos+cntxt->STK[NST].proceed[cntxt->STK[NST].i]+1;
#if !defined BACHUS_IN_DECTALK && defined FROMTYPED
		if (cntxt->STK[NST].newwalki.wordpos > cntxt->wordlength) FNX_PRINTF("wordlength execeeded!\n");
#endif

		jumpmacro(cntxt->STK[NST].newwalki,14,jump14,cntxt,cntxt->STK[NST].next,cntxt->STK[NST].newwalki,NST+1);
		// FNX_PRINTF("%10s ",cntxt->Nodes[cntxt->STK[NST].curr].name );
		// for (j=cntxt->STK[NST].currpos;j<=cntxt->STK[NST].currpos+cntxt->STK[NST].proceed[i];j++) FNX_PRINTF("%c",cntxt->theword[j]);

		if (cntxt->STK[NST].newwalki.succeeded)   // get the phoneme string info, and rule number i.
		  {
		    cntxt->STK[NST].rulenumber = cntxt->STK[NST].ruleindex[cntxt->STK[NST].i];
		    cntxt->STK[NST].phonemestring = 
			IT_point_to_phoneme_string(cntxt->MorphDict, cntxt->STK[NST].phonemeindex[cntxt->STK[NST].i]);

		    IT_register_word_part(cntxt,
				       cntxt->Nodes[cntxt->STK[NST].curr].name,
				       LETTERTRIE,
				       cntxt->STK[NST].currpos,
				       (unsigned short)(cntxt->STK[NST].currpos+cntxt->STK[NST].proceed[cntxt->STK[NST].i]),
				       0,
				       cntxt->STK[NST].phonemestring, 
				       cntxt->STK[NST].rulenumber);
		    goto walkexit; // return cntxt->STK[NST].newwalki;
		  }
	      }
	    cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki;	
	    cntxt->STK[NST].newwalki.succeeded=0;
	  }
	else
	  {
	    cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki;	
	  }
	break;

	/* The operators that are permissible can be found in an extra file bachusoperator.h
	   They must be programmed here. Currently this code is inline here but could
	   be moved to yet another subroutine. 
	 */

#ifdef IT_OPERATORS_NEEDED_IN_WALKER

/* I keep the code here in case I change later the word grammars to include special 
   operators. ReWT */

      case OPERATORNAME:
	cntxt->STK[NST].opcode = cntxt->Nodes[cntxt->STK[NST].curr].index;   
	cntxt->STK[NST].opparam = cntxt->Nodes[cntxt->STK[NST].curr].what;
	//      FNX_PRINTF("opcode = %i  opparm = %i\n", cntxt->STK[NST].opcode,cntxt->STK[NST].opparam);
	//	FNX_PRINTF("Encountered an Operator opcode is %i, parameter is %i\n",cntxt->STK[NST].opcode,cntxt->STK[NST].opparam);

	cntxt->STK[NST].match = 0;
	cntxt->STK[NST].currpos = cntxt->STK[NST].oldwalki.wordpos;
	switch (cntxt->STK[NST].opcode)
	{
	  case OPsyllabify:
	    if (cntxt->grammar == cntxt->STK[NST].opparam) 
	      {
		cntxt->STK[NST].match = 1;
	      }
	    break;
	    
	  case OPgrammar:
	    if (cntxt->grammar== cntxt->STK[NST].opparam) 
	      {
		cntxt->STK[NST].match = 1;
	      }
	    break;

	  case OPspezial:  // for the argument special(0) test if any bit is set in cntxt->special
                           // otherwise, the argument of special(M), M, is treated as bit mask.
	    if (cntxt->STK[NST].opparam==0) 
	      {
		if(cntxt->special != 0 )
		  {
		    cntxt->STK[NST].match=1;
		  }
	      }
	    else
	      {
		if ((cntxt->special & cntxt->STK[NST].opparam) != 0)
		  {
		    cntxt->STK[NST].match = 1;
		  }
	      }
	    break;

	    
	  case OPlonger:
	    //  FNX_PRINTF("longer: currentpos %i\n",cntxt->STK[NST].currpos);
	    if ((cntxt->wordlength - cntxt->STK[NST].currpos) > cntxt->STK[NST].opparam)
	      {
		cntxt->STK[NST].match = 1;	 //   FNX_PRINTF("longer: rule matches\n");
	      }
	    break;

	  case OPshorter:
	    // FNX_PRINTF("shorter: currentpos %i\n",cntxt->STK[NST].currpos);
	    if ((cntxt->wordlength - cntxt->STK[NST].currpos) < cntxt->STK[NST].opparam)
	      {
		cntxt->STK[NST].match = 1;       //  FNX_PRINTF("shorter: rule matches\n");
	      }
	    break;
	    
	  case OPstartvowel:
	    // FNX_PRINTF("shorter: currentpos %i\n",cntxt->STK[NST].currpos);
	    if (IT_is_a_vowelgrapheme(cntxt->theword[0]))
	      {
		cntxt->STK[NST].match = 1;       // FNX_PRINTF("vowel rule matches\n");
	      }
	    break;

	  case OPstartcons:
	    if (!IT_is_a_vowelgrapheme(cntxt->theword[0]))
	      {
		cntxt->STK[NST].match = 1;       // FNX_PRINTF("cons rule matches\n");
	      }
	    break;

	  case OPbreak:
	    cntxt->STK[NST].newwalki.succeeded = 1;  // (cntxt->wordlength == cntxt->STK[NST].newwalki.wordpos);
	    cntxt->STK[NST].match = 1;
	    //	    FNX_PRINTF("We got a break operator %i %i %i \n",cntxt->level,cntxt->STK[NST].newwalki.wordpos,cntxt->wordlength);
	    cntxt->wordlength=cntxt->STK[NST].newwalki.wordpos;
	    //	    if (!cntxt->STK[NST].newwalki.succeeded) {cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki; cntxt->STK[NST].newwalki.succeeded=0;}

	  default:
	    break;
	}
	if (cntxt->STK[NST].match==1)     // if matches 
	  {
	    cntxt->STK[NST].newwalki.wordpos =  cntxt->STK[NST].currpos;
	    jumpmacro(cntxt->STK[NST].newwalki,15,jump15,cntxt,cntxt->Nodes[cntxt->STK[NST].curr].right,cntxt->STK[NST].newwalki,NST+1);	
	    if (cntxt->STK[NST].newwalki.succeeded == 0)
	      {
		cntxt->STK[NST].newwalki=cntxt->STK[NST].oldwalki;                   // backtracking
		cntxt->STK[NST].newwalki.succeeded=0;
	      }
	  }  
	break; 

#endif // IT_OPERATORS_NEEDED_IN_WALKER
 
      case SYLLABIFY:
	/* Send the rest of the word over to a syllabifier */
	  cntxt->STK[NST].next = cntxt->Nodes[cntxt->STK[NST].curr].right;
	  cntxt->STK[NST].currpos = cntxt->STK[NST].oldwalki.wordpos;
	  cntxt->STK[NST].ntrie = cntxt->Nodes[cntxt->STK[NST].curr].what;
	  // FNX_PRINTF("syllabify it from %i, length %i, using ntrie from %i\n",cntxt->STK[NST].currpos,cntxt->wordlength,cntxt->STK[NST].ntrie);
	  // for now, emulate succesful parsing.
	  cntxt->STK[NST].newwalki.wordpos =  cntxt->wordlength;
	  jumpmacro(cntxt->STK[NST].newwalki,16,jump16,cntxt,cntxt->STK[NST].next,cntxt->STK[NST].newwalki,NST+1);
	  break;

	  default:
#if !defined BACHUS_IN_DECTALK && defined FROMTYPED
	      FNX_PRINTF("Illegal case in GtWalkerLinear.c\n");
#endif
          break;

      }
    //  FNX_PRINTF("Returning from %d with %d succeeded\n",curr,succeeded);
walkexit:
    //(cntxt->level)--;
    if (cntxt->alert==1) cntxt->STK[NST].newwalki.succeeded=0;  // relentlessly

    position = IT_popjump(cntxt);
    if (position==-1)
    {
	//FNX_PRINTF("exiting\n");
	return cntxt->STK[NST].newwalki;
    }
    //NST -= 1;
    //FNX_PRINTF("going to switchboard\n");
    goto switchboard;
}
