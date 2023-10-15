#include "port.h" //added for platform specific stuff - mlt
void register_word_part(WalkCNTXT *cntxt, 
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
  MorphemeStruct *M;

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
  
