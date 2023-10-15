#include "bachusit.h"
//#include <string.h> //moved to port.h for each platform - mlt


/* walkerit.c is now a set of help subroutines for Gtwalkerlinear.c */

ASCIILETTER *IT_point_to_phoneme_string(const IT_PhonemeWords *Mdict, U16 index) 
     /* referes to structures defined in ltrie.c */
{
  if (!index) return NULL;
  return (ASCIILETTER *) (Mdict->bigbuffer + Mdict->ptarray[index-1]); // has to be zero terminated, and is.
}



IT_Nodestack IT_newNodestack()
{
  IT_Nodestack nn;
  IT_initNodestack(&nn);
  return nn;
}

void IT_initNodestack(IT_Nodestack *stk) 
{
  stk->sz = IT_MAXSTACKDEPTH;
  stk->ntok=0;
  stk->status=0;
  stk->p = &(stk->v[0]);
}

BOOL IT_pushNode(IT_Nodestack *stk, IT_StkToken tok)
{ 
  if (stk->ntok < stk->sz)
    {
      stk->status=0; 
      *(stk->p)++ = tok; 
      (stk->ntok)++; 
      return 1;
    } 
  else 
    {
      stk->status=1; // overflow
#ifdef NODESTACKDEBUG 
      FNX_PRINTF("Nodestack Overflow\n");
      exit(0);
#endif
      return 0;
    }
}

IT_StkToken  IT_popNode(IT_Nodestack *stk)
{
  IT_StkToken ret = 0;

  if (stk->ntok>0)
    {
      stk->status=0;
      (stk->ntok)--;
      return *(--(stk->p));
    } 
  else 
    {
      stk->status=2;  // underflow.
#ifdef NODESTACKDEBUG 
      FNX_PRINTF("Nodestack Underflow\n");
#endif
      return ret;
    }
}

IT_StkToken  IT_topNode(IT_Nodestack *stk)    // note the difference. 
     /* get me a peek what's the uppermost token
	that would be popped up if pop was called */
{
  IT_StkToken ret = 0;
  if (stk->ntok>0)       return (stk->v[stk->ntok-1]);  // ça ne vas rien toucher ...
  else return ret;
}


void IT_resetNodestack(IT_Nodestack *stk)
{
  stk->ntok=0;
  stk->status=0;
}


/* The rest of this file contains two main subroutines used 
   in online word grammar parsing, 
   Lt_parse_string and GtWalker.

   Purpose of Lt_parse_string: Given as input a string and a start position within
   the string, it tries to find one or multiple matches in a dictionary which is
   implemented as a letter trie. It returns the number of found matches and 
   places the number of bytes of each matching partial string into the the
   foundseq argument. foundseq must have sufficient storage allocated for the
   maximally possible number of matches. 
*/



U16 IT_Lt_parse_string(ASCIILETTER *str,       // string to match
		    U16 startposition,    // starting at this position
		    const IT_LTrie *Lt,      // by the entries in the letter trie
		    U16 *foundseq,        // multiple possible lengths to proceed
		    U16 *phonemeindices,  // corresponding phoneme string indices
		    U16 *ruleindices,     // corresponding rule numbers. 
		    U16 mode)
{
  U16  ii,len,curr,match,lastletter, foundcount;
  ASCIILETTER cc;
  U16  foundbuf[10];   // used to mark number characters that match
  U16  phindexbuf[10]; // used to copy an index for a phoneme string.  
  U16  rulebuf[10];    // used to store the rule number noted in the final ltrie node
                       // of a matched word.

  foundcount = 0;   // returned 

  /* exclude immediately the trivial possibility that 
     we are already at the end of a word, that is,  the first letter
     at the start position is already at the word end (i.e., equal 0).
  */
  len = FNX_STRLEN(str);
  if (len == 0) return 0;          // don't process null strings
  if (startposition>len) return 0; // same reason to return;
   

  /* In searching the trie, always start at the epsilon node
     which is assumed by convention to be the very first node
     at address 0
  */
  curr = 0;     // start at epsilon node, the empty letter.
  match=0;
  ii = startposition;
  
  
  /* In the following outer while loop, we proceed to
     the next letter of the input string (starting with
     the letter at the initial position.). 
     Accordingly we proceed in the letter trie one position
     to the right in each while loop, if indeed there
     is one node to the right of the current node.
     If there is one, this may or may not be the node
     that matches the current letter. If it is
     matching the letter, we have succesfully matched it
     and can proceed with the next letter. If it is
     not the letter, we have to find alternative nodes by
     using the down direction in the trie.
  */
     
  while ((cc = str[ii++] ) != 0) 
    {
//	if (cc==' ') cc='.';
      lastletter=ii-1;     // (-1 to compensate for ii++) 

      if (Lt->u.Nodes[curr].right != NIL)  // is there a right node?
	{ 
	  curr = Lt->u.Nodes[curr].right; 
	}
      else  // no right node
	{
	  match=0;
	  break;  
	}
      /* We arrive here if there is a right node, 
	 Is it the correct letter? 
      */
      if (Lt->u.Nodes[curr].letter == cc)
	{
	  match = 1;   
	  // FNX_PRINTF("match found for [%c]\n",cc);
	  if (Lt->u.Nodes[curr].info == ENDOFLEX)
	    { 
	      foundbuf[foundcount]   = lastletter-startposition;
	      rulebuf[foundcount] = Lt->u.Nodes[curr].rule;
	      phindexbuf[foundcount++] = Lt->u.Nodes[curr].phonemehandle;
	    }
	}
      else  // wrong letter at the right node.
	{
	  match=0;
	  /* If it wasn't the first letter to the right of the node,
	     it could be another one in an alternative node, which
	     can be found by using the down field of the current node.
	  */
	  
	  while(Lt->u.Nodes[curr].down != NIL && match == 0)
	    {
	      curr = Lt->u.Nodes[curr].down; 
	      if (Lt->u.Nodes[curr].letter == cc)
		{
		  match = 1;   
		  // FNX_PRINTF("match found 2 for [%c]\n",cc);
		  if (Lt->u.Nodes[curr].info == ENDOFLEX)
		    { 
		      foundbuf[foundcount] = lastletter-startposition;
		      rulebuf[foundcount] = Lt->u.Nodes[curr].rule;
		      phindexbuf[foundcount++] = Lt->u.Nodes[curr].phonemehandle;
		    }
		  break;
		}
	    }
	  if (match==0) 
	    {
	      break;
	    }
	}
    }

  if ((curr != NIL ) && match == 1)
    {
      if (Lt->u.Nodes[curr].info != ENDOFLEX) 
	{
	  match=0;
	}
    }
  if (foundcount>0)
    {
    switch (mode)
      {
      case IT_LONG_MORPH_FIRST:      // reverse sequence
	for (ii=0;ii<foundcount;ii++) 
	  {
	    foundseq[ii] = foundbuf[foundcount-1-ii];
	    phonemeindices[ii]=phindexbuf[foundcount-1-ii];
	    ruleindices[ii]=rulebuf[foundcount-1-ii];
	  }
	break;
	
      case IT_LONG_MORPH_LAST:
	for (ii=0;ii<foundcount;ii++) 
	  {
	    foundseq[ii] = foundbuf[ii];
	    phonemeindices[ii]=phindexbuf[ii];
	    ruleindices[ii]=rulebuf[ii];
	  }
	break;
      }
    }
	
  return foundcount;  // number of found matches
}

U16 IT_short_Lt_parse_string(ASCIILETTER *str,       // string to match
		    U16 startposition,    // starting at this position
		    const IT_LTrie *Lt,      // by the entries in the letter trie
		    U16 *foundseq,        // multiple possible lengths to proceed
		    U16 *phonemeindices,  // corresponding phoneme string indices
		    U16 *ruleindices,     // corresponding rule numbers. 
		    U16 mode)
{
  U16  ii,len,curr,match,lastletter, foundcount;
  ASCIILETTER cc;
  U16  foundbuf[10];   // used to mark number characters that match
  U16  phindexbuf[10]; // used to copy an index for a phoneme string.  
  U16  rulebuf[10];    // used to store the rule number noted in the final ltrie node
                       // of a matched word.

  foundcount = 0;   // returned 

  /* exclude immediately the trivial possibility that 
     we are already at the end of a word, that is,  the first letter
     at the start position is already at the word end (i.e., equal 0).
  */
  len = FNX_STRLEN(str);
  if (len == 0) return 0;          // don't process null strings
  if (startposition>len) return 0; // same reason to return;
   

  /* In searching the trie, always start at the epsilon node
     which is assumed by convention to be the very first node
     at address 0
  */
  curr = 0;     // start at epsilon node, the empty letter.
  match=0;
  ii = startposition;
  
  
  /* In the following outer while loop, we proceed to
     the next letter of the input string (starting with
     the letter at the initial position.). 
     Accordingly we proceed in the letter trie one position
     to the right in each while loop, if indeed there
     is one node to the right of the current node.
     If there is one, this may or may not be the node
     that matches the current letter. If it is
     matching the letter, we have succesfully matched it
     and can proceed with the next letter. If it is
     not the letter, we have to find alternative nodes by
     using the down direction in the trie.
  */
     
  while ((cc = str[ii++] ) != 0) 
    {
//	if (cc==' ') cc='.';
      lastletter=ii-1;     // (-1 to compensate for ii++) 

      if (Lt->u.SNodes[curr].right != NIL)  // is there a right node?
	{ 
	  curr = Lt->u.SNodes[curr].right; 
	}
      else  // no right node
	{
	  match=0;
	  break;  
	}
      /* We arrive here if there is a right node, 
	 Is it the correct letter? 
      */
      if (Lt->u.SNodes[curr].letter == cc)
	{
	  match = 1;   
	  // FNX_PRINTF("match found for [%c]\n",cc);
	  if (Lt->u.SNodes[curr].info == ENDOFLEX)
	    { 
	      foundbuf[foundcount]   = lastletter-startposition;
	      rulebuf[foundcount] = 0;          // Lt->u.SNodes[curr].rule;
	      phindexbuf[foundcount++] = 0;  // Lt->u.SNodes[curr].phonemehandle;
	    }
	}
      else  // wrong letter at the right node.
	{
	  match=0;
	  /* If it wasn't the first letter to the right of the node,
	     it could be another one in an alternative node, which
	     can be found by using the down field of the current node.
	  */
	  
	  while(Lt->u.SNodes[curr].down != NIL && match == 0)
	    {
	      curr = Lt->u.SNodes[curr].down; 
	      if (Lt->u.SNodes[curr].letter == cc)
		{
		  match = 1;   
		  // FNX_PRINTF("match found 2 for [%c]\n",cc);
		  if (Lt->u.SNodes[curr].info == ENDOFLEX)
		    { 
		      foundbuf[foundcount] = lastletter-startposition;
		      rulebuf[foundcount] = 0;         //  Lt->u.SNodes[curr].rule;
		      phindexbuf[foundcount++] = 0; //  Lt->u.SNodes[curr].phonemehandle;
		    }
		  break;
		}
	    }
	  if (match==0) 
	    {
	      break;
	    }
	}
    }

  if ((curr != NIL ) && match == 1)
    {
      if (Lt->u.SNodes[curr].info != ENDOFLEX) 
	{
	  match=0;
	}
    }
  if (foundcount>0)
    {
    switch (mode)
      {
      case IT_LONG_MORPH_FIRST:      // reverse sequence
	for (ii=0;ii<foundcount;ii++) 
	  {
	    foundseq[ii] = foundbuf[foundcount-1-ii];
	    phonemeindices[ii]=phindexbuf[foundcount-1-ii];
	    ruleindices[ii]=rulebuf[foundcount-1-ii];
	  }
	break;
	
      case IT_LONG_MORPH_LAST:
	for (ii=0;ii<foundcount;ii++) 
	  {
	    foundseq[ii] = foundbuf[ii];
	    phonemeindices[ii]=phindexbuf[ii];
	    ruleindices[ii]=rulebuf[ii];
	  }
	break;
      }
    }
	
  return foundcount;  // number of found matches
}


#ifdef GRAMMAR_EVALUATION
void GtrieStatisitics(GTrieNode *Nodes, U16 number)
{
    int i;
    FNX_PRINTF("Call statistics for rule lines\n"); 

    for (i=0; i< number ; i++)
      {
	if (Nodes[i].typeinfo == ALTNODE)
	  {
	      if (Nodes[i].info.counter)
	      {
		  FNX_PRINTF("Line %4d succeeded %8d times.\n",Nodes[i].info.parameter,Nodes[i].info.counter);
		  Nodes[i].info.counter=0;
	      }
	  }
      }
}
#ifdef FROMTYPED
void GtrieQuickStatistics(GTrieNode *Nodes, U16 number)
{
    int i;
    int kk;
    kk=0;

    FNX_PRINTF("G:");
    for (i=0; i<number; i++)
      {
	if (Nodes[i].typeinfo == ALTNODE)
	  {
	    if (Nodes[i].info.counter > 0) 
	      {
		  if (kk==0)
		  {
		    FNX_PRINTF("%4d %-20s",Nodes[i].info.parameter,Nodes[Nodes[i].right].name);
		  }
		kk +=1;
		//Nodes[i].info.counter=0;
	      }
	  }
      }
    FNX_PRINTF("\n");
}
#endif
#endif



void IT_register_word_part(IT_WalkCNTXT *cntxt, 
			ASCIILETTER *name, 
			U16 type,    // new: e.g., WORDSEPERATOR
			U16 from, 
			U16 to, 
			BOOL action, 
			ASCIILETTER *phone, 
			U16 rule)
     /* if a word part was found in GtWalker, it is registered by it's name (e.g. root, suffix etc).
	The function is also used (see case 1) to copy tags such as "=" or "+" to mark
	inner word boundaries. See Gtwalker how it is called. 
      */
{
  int i,n;
  IT_MorphemeStruct *M;

  M = &(cntxt->Morphstruct);
  
  n = (M->nparts)++;
  
  switch (action)
    {
    case 0:
      if (name) FNX_STRCPY(M->morph[n].morphname,name);
      for (i=from;i<=to;i++) 
	{
	  M->morph[n].wordpart[i-from] = cntxt->theword[i];
	}
        M->morph[n].wordpart[to-from+1]='\0';
// Added here: register also the from and to numbers indicating positions in the word.
      M->morph[n].from = from;
      M->morph[n].to = to;
      M->morph[n].type = type;
      if (phone==NULL) M->morph[n].phonemepart[0]='\0';
      else FNX_STRCPY(M->morph[n].phonemepart,phone);
      M->morph[n].rulenumber = rule;
      break;
    case 1:
      M->morph[n].type = type;
      if(name) FNX_STRCPY(M->morph[n].wordpart,name);
      if(name) FNX_STRCPY(M->morph[n].morphname,name);        // morphname in this case is an inserted string such as "+"
      if(name) FNX_STRCPY(M->morph[n].phonemepart,name);
      M->morph[n].rulenumber = 0;                // aha! here we can later introduce some interesting tricks...
      break;
    }
}
  
void split_inline_morph_phonemes(const ASCIILETTER *name, int *comparelength, int *phonestart, int *phonelength, U16 *rule)
     /* This special cludge function applies to strings in the form "ed @d 1" where ed is a compare
	string, @d is a phoneme string and 1 is a rule number. We want to know how many 
	characters are in the compare string, where the phoneme string begins, and how long it is,
	and finally, if there is a number, what number is it? I don't assume that there
	any totally pathetic strings here such as all blanks or not zero terminated. 
     */

{
  int i;
  int len;
  ASCIILETTER separator='/';     // modify appropriately: We use here a blank as separator

  *comparelength=0;
  *phonestart=0;
  *phonelength=0;
  *rule=0;
  
  len = FNX_STRLEN(name);
  
  for (i=0; i<len;i++) 
    {
      if (name[i] == separator)
	{
	  *comparelength = i;
	  break;
	}
    }

  if (*comparelength==0)    // no blank found. 
    {
      *comparelength=len;
      return;
    }

  for (i = *comparelength + 1; i<len; i++)
    {
      if (name[i] != separator)
	{
	  *phonestart=i;
	  break;
	}
    }
  if (*phonestart==0)       // only blanks until end (bad syntax)
    {
      return;
    }
  
  for (i = *phonestart; i<len; i++)
    {
      *phonelength = i - *phonestart;
      if (name[i]==separator)
	{
	  break;
	}
    }
  if ((*phonestart + *phonelength+1)<len)
    {
      *rule = FNX_ATOI(&name[*phonestart+*phonelength+1]);
    }
}


BOOL word_is_capitalized(const ASCIILETTER *word)
{
    if(   ( word[0] >= 'A' && word[0] <= 'Z')
	 || word[0] == UML_A 
	 || word[0] == UML_O 
	 || word[0] == UML_U)  
    return 1;
  else 
    return 0;
}

BOOL word_has_some(const char test, const ASCIILETTER *word)
     /* check if a word contains a certain character test */
{
  int i;
  for (i=0; word[i] != '\0'; i++) if (word[i] == test) return 1;
  return 0;
}



/* The following function reconstructs the word - after a successful parse only -
   and inserts morpheme markers. The structure MorphemeStruct that was assembled
   during the parsing process is used as input, whereby we start at the end of the
   structure. Input is the word in decomposed form in the MorphemeStruct, 
   output the wordstring with included    morpheme markers.
*/
void IT_insert_morph_seperators(ASCIILETTER *outword, IT_MorphemeStruct *M)     
{
  int i,j,kk;
  ASCIILETTER c;

  kk=0;
  for (i=M->nparts; i>0; i--)
    {
      for (j=0; (c = M->morph[i-1].wordpart[j])!=0; j++) outword[kk++] = c;
    }
  outword[kk++]='\0';
}

void IT_concat_morphems_phonemes(ASCIILETTER *outphonemes, IT_MorphemeStruct *M, const int  order)     
{
  int i,j,kk, nmorph;
  // U16 rule;
  ASCIILETTER c;

  IT_Morpheme *Mobo[5];     // pointer chain.
  IT_Morpheme *focus;       // central Morpheme

  for (i=0;i<5;i++) Mobo[i]=(IT_Morpheme *) NULL;
  kk=0;

  // feed buffer with n morphemes and two nulls
  
  nmorph = M->nparts;

  for (i=0;i < (nmorph + 2) ;i++)            // nmorph morphemes and pump two more.
    {
      for (j=1;j<5;j++) Mobo[j-1]=Mobo[j];   // delay.

      if (i < nmorph) 
	{
	  if (order== -1) Mobo[4] = &(M->morph[nmorph-1-i]);    // this is the normal way.
	  else if (order == 1) Mobo[4] = &(M->morph[i]);
	}
      else
	{
	  Mobo[4] = (IT_Morpheme *) NULL;
	}
      
//      process_rule(Mobo[0],Mobo[1],Mobo[2],Mobo[3],Mobo[4]);  // find this in allorules.c
      
      focus = Mobo[2];    // middle morph
      if (focus) 
	{
	  for (j=0; (c = focus->phonemepart[j])!=0;j++) outphonemes[kk++] =c;
	}
    }

  outphonemes[kk++]='\0';
}

/* A shorter version of morphemize_word used to inquire specific information about a word.
 */

BOOL IT_analyse_word(const ASCIILETTER *word, 
		     ASCIILETTER *outword, 
		     ASCIILETTER *outphonemes,
		     IT_WalkCNTXT *Contxt,
		     const IT_wordgrammarinfo *Wt)
{
  BOOL ret;
  int i,j;
  // WalkCNTXT Contxt;
  U16 nextaltnode;
  IT_walkinfo walki;
  ASCIILETTER wordbuff[120];

  ASCIILETTER cc;

  int NST;


  Contxt->Nodes = Wt->GtNodes;

#ifndef BACHUS_IN_DECTALK
  Contxt->nnodes = Wt->nnodes;
  FNX_PRINTF(" Wt->nnodes is %d \n",Wt->nnodes);

#endif 
  Contxt->Ltlist = Wt->Ltreelist;
  Contxt->MorphDict = Wt->MorphDict;
  Contxt->special = 0;

  /* process special bits for conditions: such as "ist's", "war's", "USA", "Prof.", "etc" */
  /* see bachusoperators.h */

  j=0; 

  for (i=0;word[i] != '\0'; i++)
    {
	// cc = FNX_TOLOWER(word[i]);
      cc = word[i];
      /* if (cc>='a' && cc <="z" && cc != '\'' && cc != '`')*/  wordbuff[j++]=cc;
    }

  wordbuff[j++] = '\0';

  Contxt->wordlength = FNX_STRLEN(wordbuff);
//  FNX_PRINTF("Word length is %d\n",Contxt->wordlength);


/* The following trick highly depends on the specific structure of the 
   grammar tree: The 0'th node is always an epsilon node and currently ignored 
   the second node is always the first start node and has a pointer to the second
   node which is always an altnode. So we make the altnode first equal 2.
   Then in Gtwalker is a code that if we are at the first startnode, the
   next altnode is the one noted in walki.altnode. In GtWalker, if the
   process gets to an altnode at the highest level (status==1), then
   it will register the next altnode in walki.altnode. This way we can
   excute all statements of the grammar on the highest level.
*/

  nextaltnode=2; 
  walki.altnode=2;

  Contxt->theword = wordbuff;

  Contxt->counter=0;
  Contxt->level=0;
  Contxt->maxlevel=0;  
  Contxt->alert =0;
  
  Contxt->wordpos=0;
  Contxt->Morphstruct.nparts=0; 
  IT_initNodestack(&Contxt->nstack);
  Contxt->jmptop=0;
  NST=0;      
  
  ret = 0;
  walki.wordpos = 0;
  walki.succeeded=0;
  
  walki = IT_GtWalkerLinear(Contxt,1,walki,NST); // start at 1st node
  
  nextaltnode = walki.altnode;    // provides alternative on highest level
  
 // FNX_PRINTF("Max recursion in GtWalker was %i\n",  Contxt->maxlevel);
  
  if (walki.succeeded == 1) 
  {
      IT_insert_morph_seperators(outword, &Contxt->Morphstruct);
      IT_concat_morphems_phonemes(outphonemes, &Contxt->Morphstruct,-1);   // backwards
      // FNX_PRINTF("Analysis string : /%s/ -> [%s].\n",wordbuff,outword);
      ret=1;
  }
 
  return ret;
}
