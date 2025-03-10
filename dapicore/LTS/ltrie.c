#include "bachus.h"
#include "port.h" //added for platform specific stuff - mlt
#ifndef BACHUS_IN_DECTALK

LTrie make_new_ltrie(const U16 nnodes, const U16 increments)
{
  LTrie newtrie;      
  newtrie.Nodes = (TrieNode *) FNX_CALLOC((size_t) nnodes, sizeof(TrieNode));
    // want a catch here, please feel free to programm it !

  newtrie.size = nnodes;
  newtrie.nnodes = 0;
  newtrie.last = 1;
  newtrie.current = 0;
  newtrie.nempty = nnodes-1;     // all empty but the first.
  newtrie.increments=increments; // if new nodes have to allocated.
  newtrie.stopcondition = NIL;   
  newtrie.Nodes[0].letter = '*';
  return newtrie;
}

void  delete_ltrie(LTrie *LT)   // primitive clean up procedure
{
  if (LT->size > 0 && LT->Nodes)
    {
      FNX_FREE((void *) LT->Nodes);   // (watch this: crash and burn if memory corrupted.)
    }
}


U16  make_new_node(LTrie *LT)  
{
  U16 last, newlen;

  //DEBUG_printf("Empty nodes: %i.\n",LT->nempty);
  if (LT->last < LT->size)
    {
      last = LT->last;
      LT->nempty -= 1;
      LT->last += 1;       // may now point to nonexistant memory (!)
    }
  else
    {
      newlen = LT->size + LT->increments;
      LT->Nodes =   (TrieNode *)    FNX_REALLOC((void *)LT->Nodes, sizeof(TrieNode)*newlen);
      //DEBUG_printf("Realoc called at current %i \n",LT->current);
      last = LT->last;
      // note: new memory not initialized.    So init at least each new node as above:
      LT->last += 1;    // btw points to non-initialized memory, will be cleared next time
      LT->size += LT->increments;
      LT->nempty = LT->increments-1;  // minus one since I give one of the new ones away
    }
  // just to be sure:
  LT->Nodes[last].letter = '*';
  LT->Nodes[last].info = 0;
  LT->Nodes[last].down = 0;
  LT->Nodes[last].right = 0;
  return last;    // point at new node, ready for use and empty
}

void dump_ltrie(const LTrie Lt)
{
  int i;
  FNX_PRINTF("\n Dump of Letter Tree  \n Realloc size %i\n",Lt.increments);
  FNX_PRINTF("Size: %i.  Number of Nodes %i, Empty nodes %i. \n",Lt.size,Lt.nnodes,Lt.nempty);
  FNX_PRINTF("Last: %i.  Current  %i, Stop Condition %i. String search index %i. \n",
	 Lt.last,Lt.current,Lt.stopcondition,Lt.searchposition);
  for (i=0; i<Lt.last; i++)
    {
    FNX_PRINTF("%6i  %c %6i %6i %2i %4i %8i\n",i,
	   Lt.Nodes[i].letter,
	   Lt.Nodes[i].down,
	   Lt.Nodes[i].right,
	   Lt.Nodes[i].info,
	   Lt.Nodes[i].rule,
	   Lt.Nodes[i].phonemehandle);
    }
}

void file_dump_ltrie(const LTrie Lt, const ASCIILETTER *name, const int number, FILE *outstr, const char *nameextension)
{
  int i;

  FNX_FPRINTF(outstr,"\n%s TrieNode %s%s%i[] = { \n",CONSTSTRING,nameextension,name,number);

  for (i=0; i<Lt.last; i++)
    {
    FNX_FPRINTF(outstr, "      { '%c', %6i, %6i, %2i, %4i, %8i}, \n",
	    Lt.Nodes[i].letter,
	    Lt.Nodes[i].down,
	    Lt.Nodes[i].right,
	    Lt.Nodes[i].info,
	    Lt.Nodes[i].rule,
	    Lt.Nodes[i].phonemehandle);
    }
  FNX_FPRINTF(outstr,"       };\n");
}


U16  extend_lt_right(LTrie *trie,  ASCIILETTER letter, ASCIILETTER info, U16 phonemehandle, U16 rule)
{
  int last;
  int curr;

  curr = trie->current;

  last = make_new_node(trie);
  trie->nnodes += 1;
  trie->Nodes[last].letter = letter;
  //DEBUG_printf("Extend right letter %c\n",letter);
  trie->Nodes[last].info = info;
  trie->Nodes[last].rule = rule;
  trie->Nodes[last].phonemehandle = phonemehandle;
  trie->Nodes[last].down = 0;
  trie->Nodes[last].right = 0;
  trie->Nodes[curr].right = last;
  trie->current=last;
  return last;
}

U16  extend_lt_down(LTrie *trie,  ASCIILETTER letter, ASCIILETTER info, U16 phonemehandle, U16 rule)
{
  int last;
  int curr;

  curr = trie->current;

  last = make_new_node(trie);
  trie->nnodes += 1;
  trie->Nodes[last].letter = letter;
  //DEBUG_printf("Extend down letter %c\n",letter);
  trie->Nodes[last].info = info;
  trie->Nodes[last].rule = rule;
  trie->Nodes[last].phonemehandle = phonemehandle;
  trie->Nodes[last].down = 0;
  trie->Nodes[last].right = 0;
  trie->Nodes[curr].down = last;
  trie->current=last;
  return last;
}

U16 match_string(ASCIILETTER *str, LTrie *Lt)
{
  U16  ii,len,curr,match,lastletter;
  ASCIILETTER cc;
  Lt->stopcondition = LTRIE_NIL;  // reset
  len = FNX_STRLEN(str);
  if (len == 0) return 0;

  curr = 0;     // start at epsilon node, the empty letter.
  match=0;
  ii = 0;
  //DEBUG_printf("Start match %s\n",str);

  while ((cc = str[ii++] ) != 0) 
    {
      lastletter=ii-1;
      //DEBUG_printf("searching for %c .......\n",cc);
      if (Lt->Nodes[curr].right != NIL)
	{
	  curr = Lt->Nodes[curr].right; //DEBUG_printf("right to node %i\n",curr);
	  Lt->current = curr;
	}
      else
	{
	  //DEBUG_printf("got out while stepping right\n");
	  Lt->stopcondition = LTRIE_NORIGHT;  // last node has no righ field.
	  match=0;
	  break;
	}
      if (Lt->Nodes[curr].letter == cc)
	{
	  match = 1;    //DEBUG_printf("Match %c at node %i \n",cc,curr);
	}
      else
	{
	  match=0;
	  while(Lt->Nodes[curr].down != NIL && match == 0)
	    {
	      curr = Lt->Nodes[curr].down;  //DEBUG_printf("down to node %i\n",curr);
	      Lt->current = curr;
	      if (Lt->Nodes[curr].letter == cc)
		{
		  match = 1;   //DEBUG_printf("Match %c at node %i after down\n",cc,curr);
		  break;
		}
	    }
	  if (match==0) 
	    {
	      //DEBUG_printf("got out going down\n");
	      Lt->stopcondition = LTRIE_NODOWN;  // last node has no down next field.
	      break;
	    }
	}
    }
  Lt->current = curr;   // at any rate.
  Lt->searchposition = lastletter;
  //DEBUG_printf("final position in trie: %i.\n",curr);
  if ((curr != NIL ) && match == 1)
    {
      if (Lt->Nodes[curr].info == ENDOFLEX) Lt->stopcondition = LTRIE_ENDOFLEX;  // exact match.
      else 
	{
	  Lt->stopcondition = LTRIE_INCOMPLETE;   // string matches but is only part of a lexeme.
	  match=0;
	}
      return match;
    }
  else
    {
      return 0;
    }
}
 

U16 look_up_phone_string(PhonemeWords *Mdict, ASCIILETTER *p, ASCIILETTER **res)
     /* This has nothing to do with telephone. The purpose of this function is 
	to enter strings into a list. If a new string could not be found it
	is entered into a list, otherwise it's index number (>=1) and it's 
	string start address is returned. 
     */
{
  int i,len;
  ASCIILETTER *pp;
  ASCIILETTER *cpaddr;

  for (i=0; i<Mdict->nstrings; i++)
    {
      pp = Mdict->ptarray[i] + Mdict->bigbuffer;
      // FNX_PRINTF("%i is %s\n",i+1,pp);
      if (FNX_STRCMP(p, pp) == 0) 
	{
	  *res = pp;
	  return (i+1);
	}
    }
  
  // if we are here we need to add a string
  len = FNX_STRLEN(p);

  Mdict->bigbuffer = (ASCIILETTER *) FNX_REALLOC(Mdict->bigbuffer, (Mdict->buflen + len +1) * sizeof(ASCIILETTER) );
  if ( !(Mdict->bigbuffer)) 
    {
      FNX_PRINTF("ltrie: could not realloc 1st array in look_up_phone_string");
      exit(1);
    }

  cpaddr = Mdict->bigbuffer + Mdict->buflen;   // copy to this address. 
  FNX_STRCPY(cpaddr,p); 
  Mdict->buflen += (len+1);                    

  
  Mdict->ptarray = (U16 *) FNX_REALLOC((void *) Mdict->ptarray, (Mdict->nstrings+1) * sizeof(U16));
  if ( !(Mdict->ptarray)) 
    {
      FNX_PRINTF(" ltrie: could not realloc 2nd array in look_up_phone_string");
      exit(1);
    }

  Mdict->ptarray[Mdict->nstrings] = cpaddr - Mdict->bigbuffer;

  Mdict->nstrings += 1;
  
  //  FNX_PRINTF("Buflen now: %d\n", Mdict->buflen);
  *res = Mdict->ptarray[Mdict->nstrings-1] + Mdict->bigbuffer;

  return (Mdict->nstrings);
}

void file_dump_morph_phone_list(PhonemeWords *Mdict, FILE *fid, const char *nameextension)
{
  int i,nn;

  FNX_FPRINTF(fid,"CONST ASCIILETTER %sphonemepool[] = {\n",nameextension);
  nn = Mdict->buflen;

  for (i=0;i<nn;i++)
    {
      FNX_FPRINTF(fid,"0x%0.4X",Mdict->bigbuffer[i]);
      //      FNX_FPRINTF(fid,"\'%c\'",Mdict->bigbuffer[i]);
      if (i<nn-1) FNX_FPRINTF(fid,",");
      if ( (i-8*(i>>3)) == 7) FNX_FPRINTF(fid,"\n");
    }
  FNX_FPRINTF(fid,"};\n\n");

  nn = Mdict->nstrings;
  FNX_FPRINTF(fid,"CONST U16  %sphoneme_index[] = {\n",nameextension);
  for (i=0;i<nn;i++)
    {
      FNX_FPRINTF(fid,"0x%0.4X",Mdict->ptarray[i]);
      //      FNX_FPRINTF(fid,"\'%c\'",Mdict->ptarray[i]);
      if (i<nn-1) FNX_FPRINTF(fid,",");
      if ( (i-8*(i>>3)) == 7) FNX_FPRINTF(fid,"\n");
    }
  FNX_FPRINTF(fid,"};\n\n");

  FNX_FPRINTF(fid,"CONST PhonemeWords  %sPhonemes_List = {%d, %d, %s%s, %s%s};\n\n",
	  nameextension, Mdict->nstrings,Mdict->buflen,nameextension,"phonemepool",nameextension,"phoneme_index");
  
}

void dump_morph_phone_list(PhonemeWords *Mdict)
{
  int i;
  ASCIILETTER *pp;

    for (i=0; i<Mdict->nstrings; i++)
    {
      pp = Mdict->ptarray[i] + Mdict->bigbuffer;
      FNX_PRINTF("%i: %s\n",i+1,pp);
    }
}  

int  segment3_string(ASCIILETTER *pin, ASCIILETTER **p1, ASCIILETTER **p2, ASCIILETTER **p3)
     /* Cut input string pin into 1,2 or 3 parts if they are of any of the 
	following formats: 
	string 
	string<string2> 
	string<string2><string3>
	returns number of partial strings and sets appropriate pointers in p1,p2,p3.
	p2 and or p3 are NULL if the second or third string is not defined.
	Assumption: The input string is already free of whitespaces.
	Assumption: The input string is non const, and can be modified.
	            (characters '<' and '>' will be replaced by '\0'
	Warning: This function can not be called with a string that is const or
	         implicitely declared const by the compiler. 
	The subroutine is stupid: It will not recognize any syntax errors. 
     */
{
  int i,kk;
  int len, bracketcnt;
  ASCIILETTER *pp;
  ASCIILETTER* parray[3];

  parray[0]=NULL;
  parray[1]=NULL;
  parray[2]=NULL;
  
  len = FNX_STRLEN(pin);
  pp = pin;
  *p1 = pin;
  kk =0;

  bracketcnt=0;

  parray[kk++] = pin;

  
  // FNX_PRINTF("%s \n",pin);

  for (i=0;i<len;i++)
    {

      if (pin[i] == '<') 
	{
	  bracketcnt++;
	  pin[i]='\0';  
	  parray[kk++] = &(pin[i+1]);
	}
      if (pin[i] == '>')
	{
	  bracketcnt--;
	  pin[i]='\0';  
	}
    }
  *p1 = parray[0];
  *p2 = parray[1];
  *p3 = parray[2];
  
  if (bracketcnt!=0) 
    {
      return -1;
    }

  return kk;
}
  

int  split_morph_phonemes(ASCIILETTER *bp, U16 *phonemehandle, U16 *rule, PhonemeWords *Mdict)
     /* this function receives a string consisting either of a 
	single word (a morpheme) or a morpheme plus a phoneme
	string in <.> brackets, or a morpheme plus a phoneme
	string plus a rule number in brackets.
	The phoneme string is registered in a Morpheme dictionary.
	If the morpheme is paired with a phoneme string, 
	the index of that string is returned.
	The third field in the input string is interpreted by atoi 
	as a rule number. If the field does not exist, a zero
	is returned in the reference field *rule. 
     */
{
 
  int jj, retval;

  ASCIILETTER *p1,*p2,*p3;
  ASCIILETTER *res;
  retval=1;
  *phonemehandle = 0;
  *rule = 0;         /* a rule number. The third string field is interpreted as a numeral. */
  
  //  FNX_PRINTF("%s\n",bp);
  jj = segment3_string(bp,&p1,&p2,&p3);
  switch (jj)
    {
    case -1:
      return 0;  // indicating something went wrong (usually reading the file).
    case 1:
      //FNX_PRINTF("1: %d %s\n",FNX_STRLEN(p1 ),p1);
      *phonemehandle = 0;
      *rule = 0;
      break;
    case 2:
      //FNX_PRINTF("1: %d %s\n",FNX_STRLEN(p1 ),p1);
      //FNX_PRINTF("2: %d %s\n",FNX_STRLEN(p2 ),p2);
      *phonemehandle = look_up_phone_string(Mdict, p2, &res);
      //FNX_PRINTF("It was string %i ",phonemehandle);
      //FNX_PRINTF(" And the string was %s \n",res);
      *rule = 0;
      break;
    case 3:
      //FNX_PRINTF("1: %d %s\n",FNX_STRLEN(p1 ),p1);
      //FNX_PRINTF("2: %d %s\n",FNX_STRLEN(p2 ),p2);
      *phonemehandle = look_up_phone_string(Mdict, p2, &res);
      *rule = FNX_ATOI(p3);                // no error checking!!.
      // FNX_PRINTF("3: %d %s\n",FNX_STRLEN(p3 ),p3);
      break;
    }        
  return jj;
}

void init_morph_dict(PhonemeWords *Mdict)
{
  
  Mdict->nstrings = 0;
  Mdict->buflen=0;
  Mdict->bigbuffer = NULL;
  Mdict->ptarray = 0;
}

void clear_morph_dict(PhonemeWords *Mdict)
{
  if (Mdict->nstrings > 0)
    {    
      FNX_FREE ((void*) Mdict->bigbuffer);
      FNX_FREE ((void*) Mdict->ptarray);
      Mdict->nstrings=0;
      Mdict->buflen = 0;
    }
}

U16 insert_string_to_ltrie(ASCIILETTER *str, U16 MorphemePhonemehandle, U16 ruleNum, LTrie *Lt)
{
  U16 match;
  U16 info;
  int ii=0;
  int len;
  U16 ph_handle=0;
  U16 rule=0;

  len = FNX_STRLEN(str);

  match = match_string(str, Lt);
  if (match==1) return 1;
  else
    {
      //      dump_ltrie(*Lt);

      switch (Lt->stopcondition)
	{
	case LTRIE_EMPTY:
	  for (ii=0; len; ii++)
	    {
	      if (ii==(len-1)) 
		{
		  info = ENDOFLEX; 
		  ph_handle = MorphemePhonemehandle;
		  rule = ruleNum;
		}
	      else
		{
		  info = NOEXIT;
		  ph_handle = 0;
		  rule = 0;
		}
	      extend_lt_right(Lt,str[ii],info,ph_handle,rule); 
	    }
	  break;

	case LTRIE_INCOMPLETE:                     // found string but was not end of affix
	  Lt->Nodes[Lt->current].info = ENDOFLEX;  // tree needs no new nodes
	  Lt->Nodes[Lt->current].phonemehandle = MorphemePhonemehandle;      // new: reference to PHONEME string.
	  Lt->Nodes[Lt->current].rule = ruleNum;                        // new: reference to a transformation rule index.
	  break;

	case LTRIE_NORIGHT:
	  for (ii=Lt->searchposition; ii<len; ii++)
	    {
	      if (ii==(len-1)) 
		{
		  info = ENDOFLEX; 
		  ph_handle = MorphemePhonemehandle;
		  rule = ruleNum;
		}
	      else
		{
		  info=NOEXIT;
		  ph_handle = 0;
		  rule = 0;
		}
	      extend_lt_right(Lt,str[ii],info,ph_handle,rule);
	    }
	  break;

	case LTRIE_NODOWN:
	  ii = Lt->searchposition;

	  if (ii==(len-1))
	    {
	      info = ENDOFLEX; 
	      ph_handle = MorphemePhonemehandle;
	      rule = ruleNum;
	    }
	  else
	    {
	      info = NOEXIT;
	      ph_handle = 0;
	      rule = 0;
	    }
	  extend_lt_down(Lt,str[ii],info,ph_handle,rule);
	  for (ii=Lt->searchposition+1; ii<len; ii++)
	    {
	      if (ii==(len-1)) 
		{
		  info = ENDOFLEX; 
		  ph_handle = MorphemePhonemehandle;
		  rule = ruleNum;
		}
	      else
		{
		  info = NOEXIT;
		  ph_handle = 0;
		  rule = 0;
		}

	      extend_lt_right(Lt,str[ii],info,ph_handle,rule);
	    }
	  break;
	default:
	  //DEBUG_printf("uncovered stopcondition in trie: %i\n",Lt->stopcondition);
	}
    }
}

U16 lookfor_string(ASCIILETTER *str, U16 startpos, LTrie *Lt)
     /* look for a string in the letter trie structure */
{
  U16 match;
  int i;

  ASCIILETTER *com;
  U16 foundbuf[10];
  U16 phindexbuf[10];
  U16 rulebuf[10];


  U16 found;

  //  match = match_string(str,Lt);


  found  =  Lt_parse_string(str, startpos, Lt, &foundbuf[0], &phindexbuf[0], &rulebuf[0],LONG_MORPH_FIRST);

  for (i=0; i<found; i++)
    {
      FNX_PRINTF("position found %i\n",foundbuf[i]);
    }
  
  match = (found>0);

  if (match == 0) com = "not";
  else com = "yes";

  switch (Lt->stopcondition)
    {
    case LTRIE_ENDOFLEX :
      FNX_PRINTF("%s %s  - Complete Lexeme\n",str,com); break;
    case LTRIE_INCOMPLETE :
      FNX_PRINTF("%s %s  - Incomplete Lexeme\n",str,com); break;
    case LTRIE_NOCONTINUE :
      FNX_PRINTF("%s %s  - Incomplete match up to Pos %i\n",str,com,Lt->searchposition); break;
    case LTRIE_NORIGHT :
      FNX_PRINTF("%s %s  - Incomplete match up to Pos %i searching right\n",str,com,Lt->searchposition); break;
    case LTRIE_NODOWN :
      FNX_PRINTF("%s %s  - Incomplete match up to Pos %i searching down\n",str,com,Lt->searchposition); break;

    default:
      FNX_PRINTF("%s %s  - Unknown search termination\n",str,com); break;
    }
}

ASCIILETTER *cleanup_string(ASCIILETTER *pin)
     /* get rid of space, and white space characters */
{
  ASCIILETTER *out,*in; 
  ASCIILETTER cc;
  out = pin;
  in = pin;
  while(cc = *in++) 
    {
      if (!FNX_ISSPACE(cc)) *out++ = cc;
    }
  *out++ = '\0';
  return pin;
}


/* file2ltrie reads a token file and converts it into a letter trie */

LTrie file2ltrie(const ASCIILETTER *filename, PhonemeWords *Mdict)
{
  LTrie Lt;
  FILE *stream;
  int eof,numtokens;
  U16 phonemehandle, rule;
  
  ASCIILETTER *pin;
  ASCIILETTER inp[MAX_TOKEN_LENGTH];

  stream = FNX_FOPEN(filename,"r");
  if (stream==NULL)
    {
      FNX_PRINTF("File %s could not be opened\n",filename);
      FNX_PERROR(filename);
      exit(1);
    }
  Lt = make_new_ltrie(LTRIE_CHUNK_SIZE,LTRIE_CHUNK_SIZE);

  eof=0;
  numtokens=0;

  while (eof==0)
    {
      pin = FNX_FGETS(inp,MAX_TOKEN_LENGTH,stream);
      if (!pin)
	{
	  eof = 1;
	  break;
	}
      else
	{
	  ++numtokens;
	  // FNX_PRINTF("%i [%s]\n",FNX_STRLEN(pin),pin);
	  pin = cleanup_string(inp);   // usually remove trailing blanks and other white space chars.
	  // FNX_PRINTF("%i [%s]\n",FNX_STRLEN(pin),pin);
	  if (split_morph_phonemes(pin, &phonemehandle, &rule , Mdict) == 0)
	    {
	      FNX_PRINTF("Syntax error on line %d in file %s\n",numtokens,filename);
	    }
	  
	  // FNX_PRINTF("String segmented: |%s| /%d/ %d /%s/\n",pin,
	  // phonemehandle,rule,point_to_phoneme_string(Mdict,phonemehandle)); /* now in walker */
	  insert_string_to_ltrie(pin,phonemehandle,rule, &Lt);
	}
    }
  FNX_FCLOSE(stream);

  return Lt;
}

  
// Lt_parse_string was moved to walker.c
// point_to_phoneme_string was moved to walker.c

// For testing, uncommend and compile seperate 
#ifdef _test_with_a_main_
int main(int argc, const char** argv)
{
  U16 current;
  U16 match;

  LTrie LT;  // make_new_ltrie(20,40);
  LtParserState PS;
  // LT = file2ltrie("rootmorph.txt");
  LT = file2ltrie("prefixes.txt");
  PS.Lt = &LT;
  // dump_ltrie(LT);
  match = lookfor_string("ununtergeben",2,&LT); 
}

#endif

#endif
