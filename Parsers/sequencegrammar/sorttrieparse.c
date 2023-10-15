#include <stdio.h>

#include "seqanalyse.h"

int binsearch_assoc(U16 Num, int n, const assoctable *A)
{
    int found;
    int hi,lo;
    int adr;

    hi = n-1;
    lo = 0;
    found = 0;

/* linear search for small array */
    if (n<8)
    {
	for (adr=0;adr<n;adr++)
	{
	    if (A[adr].addr == Num) return (U16) adr;
	}
	return (-1);
    }
    
/* otherwise binary search */

    while(found==0 && ( hi >= lo))
    {
	adr = (hi+lo)>>1;
	if (A[adr].addr == Num) 
	{
	    found = 1;
	    return adr;
	}
	if (Num > A[adr].addr) lo = adr+1;
	else hi = adr-1;
    }
    if (found) return adr;
    else return (-1);
}

ASCIILETTER  decompress_sarray(CONST SortLtrieBlock *Lt, U16 curr, U16 *info,  U16 *right, U16 *down, U16 *extra)
{
    ASCIILETTER C;
    U16 E, R, B, M, dwn;
    unsigned char c2,c3;
/*

0 1 2 3 4 5 6 7 | 0 1 2 3 4 5 6 7 | 0 1 2 3 4 5 6 7
---------------------------------------------------
     char       | E R B - - * * * | * * * * * * * *   
---------------------------------------------------                
7 6 5 4 3 2 1 0 | F E D C B A 9 8   7 6 5 4 3 2 1 0
*/
    C  = Lt->sarray[curr].letter;    
    c2 = Lt->sarray[curr].c2;
    c3 = Lt->sarray[curr].c3;

    E = ( c2 & 0x80)>>7;
    R = ( c2 & 0x40)>>6;
    B = ( c2 & 0x20)>>5;
    M = ( c2 & 0x10)>>4;

    dwn = (c2 & 0x07);
    dwn = dwn * 256 + c3;

    if (B==1) dwn = Lt->dwnlong[dwn];
    
    *info = E;
    *right = R;
    *down = dwn;
    *extra=M;
    return C;
}

U16 get_sct_down(CONST SortLtrieBlock *Lt, U16 curr)
{
    U16 E, R, B, dwn;
    unsigned char c2,c3;
/*

0 1 2 3 4 5 6 7 | 0 1 2 3 4 5 6 7 | 0 1 2 3 4 5 6 7
---------------------------------------------------
     char       | E R B - - * * * | * * * * * * * *   
---------------------------------------------------                
7 6 5 4 3 2 1 0 | F E D C B A 9 8   7 6 5 4 3 2 1 0
*/

    c2 = Lt->sarray[curr].c2;
    c3 = Lt->sarray[curr].c3;

    E = ( c2 & 0x80)>>7;
    R = ( c2 & 0x40)>>6;
    B = ( c2 & 0x20)>>5;
    
    dwn = (c2 & 0x07);
    dwn = dwn * 256 + c3;
    if (B==1) dwn = Lt->dwnlong[dwn];
    return dwn;
}

U16 get_sct_info(CONST SortLtrieBlock *Lt, U16 curr)
{
    U16 E;
    unsigned char c2;
    c2 = Lt->sarray[curr].c2;

    E = ( c2 & 0x80)>>7;
    return E;
}

U16 get_sct_extra(CONST SortLtrieBlock *Lt, U16 curr)
{
    U16 M;
    unsigned char c2;
    c2 = Lt->sarray[curr].c2;

    M = ( c2 & 0x10)>>4;
    return M;
}

U16  get_sct_right(CONST SortLtrieBlock *Lt, U16 curr)
{
    U16 R;
    unsigned char c2;

    c2 = Lt->sarray[curr].c2;
    R = ( c2 & 0x40)>>6;
    return R;
}



ASCIILETTER  get_sct_letter(CONST SortLtrieBlock *Lt, U16 curr)
{
    ASCIILETTER C;
/*

0 1 2 3 4 5 6 7 | 0 1 2 3 4 5 6 7 | 0 1 2 3 4 5 6 7
---------------------------------------------------
     char       | E R B - - * * * | * * * * * * * *   
---------------------------------------------------                
7 6 5 4 3 2 1 0 | F E D C B A 9 8   7 6 5 4 3 2 1 0
*/
    C  = Lt->sarray[curr].letter;    
    return C;
}


    

U16 sorttrie_parse_string(ASCIILETTER *str,       // string to match
		    U16 startposition,            // starting at this position
		    const SortLtrieBlock *Lt,     // by the entries in the letter trie
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
  len = strlen(str);
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


      if (get_sct_right(Lt,curr) != 0)  // is there a right node?
	{ 
	    curr += 1;        // Lt->SNodes[curr].right; 
	}
      else  // no right node
	{
	  match=0;
	  break;  
	}
      /* We arrive here if there is a right node, 
	 Is it the correct letter? 
      */
      if (get_sct_letter(Lt,curr) == cc)
	{
	  match = 1;   
	  // printf("match found for [%c]\n",cc);
	  if (get_sct_info(Lt,curr) == 1)
	    { 
	      foundbuf[foundcount]   = lastletter-startposition;
	      rulebuf[foundcount] = 0;          // Lt->SNodes[curr].rule;
	      phindexbuf[foundcount++] = curr;  // Lt->SNodes[curr].phonemehandle;
	    }
	}
      else  // wrong letter at the right node.
	{
	  match=0;
	  /* If it wasn't the first letter to the right of the node,
	     it could be another one in an alternative node, which
	     can be found by using the down field of the current node.
	  */
	  
	  while( get_sct_down(Lt,curr) != 0 && match == 0)
	    {
		curr = curr + get_sct_down(Lt,curr); //  Lt->SNodes[curr].down; 
		if (get_sct_letter(Lt,curr) == cc)
		{
		  match = 1;   
		  // printf("match found 2 for [%c]\n",cc);
		  if (get_sct_info(Lt,curr) == 1)
		    { 
		      foundbuf[foundcount] = lastletter-startposition;
		      rulebuf[foundcount] = 0;         //  Lt->SNodes[curr].rule;
		      phindexbuf[foundcount++] = curr;    //  Lt->SNodes[curr].phonemehandle;
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

  if ((curr != 0 ) && match == 1)
    {
      if (get_sct_info(Lt,curr) == 1)
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



U16 get_sorttrie_addr(char *str, CONST SortLtrieBlock *Lt)
{
  U16  ii,len,curr,match,lastletter;
  char cc;
  len = strlen(str);
  if (len == 0) return 0;

  curr = 0;     // start at epsilon node, the empty letter.
  match=0;
  ii = 0;
  //DEBUG_printf("Start match %s\n",str);

  while ((cc = str[ii++] ) != 0) 
    {
	// if (cc=='.') cc=' ';
	lastletter=ii-1;
	if (get_sct_right(Lt,curr) != 0)
	{
	    curr += 1;  
	}
      else
	{
	  match=0;
	  break;
	}
      if (get_sct_letter(Lt,curr) == cc)
	{
	  match = 1;    //DEBUG_printf("Match %c at node %i \n",cc,curr);
	}
      else
	{
	  match=0;
	  while(get_sct_down(Lt,curr) != 0 && match == 0)
	    {
	      curr = get_sct_down(Lt,curr) + curr;  // differential 
	      if (get_sct_letter(Lt,curr) == cc)
		{
		  match = 1;   //DEBUG_printf("Match %c at node %i after down\n",cc,curr);
		  break;
		}
	    }
	  if (match==0) 
	    {
	      //DEBUG_printf("got out going down\n");
	      break;
	    }
	}
    }
  if (match==1) return curr;
  else return 0;
}


/* returns associated string for an entry in the letter trie
   and rule number */

CONST ASCIILETTER *get_associated_string_rule(U16 addr,                  //input
					     CONST SortLtrieBlock *Lt, 
					     CONST ASCIILETTER *phonemepool, 
					     U16* CONST rulenumber)           // output
{
    int res;
    CONST ASCIILETTER *straddr;
/*    U16 addr;
      U16 relptr;
      U16 ruleno;
*/
    res = binsearch_assoc(addr, Lt->numassoc, Lt->assoc);
    
    if (res >= 0)
    {
	straddr = phonemepool +  Lt->assoc[res].relptr;
	*rulenumber = Lt->assoc[res].ruleno;
    }
    else
    {
	*rulenumber = 0;
	straddr = (ASCIILETTER *) NULL;
    }
    return straddr;
}
	
