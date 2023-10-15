/*C_HEADER_FILE****************************************************************
FILE        :  wrdparse.c
DESC        :  A parser to convert pronunciations into wordT structures.
TABS        :  3
OWNER       :  Randy Wilson
DATE CREATED   :  

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/22/05 11:09a $
  $Revision: 7 $

*END_HEADER*******************************************************************/

#include "FnxPlatform.h"
#include "FnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxNetwork.h"
#include "FnxNames.h"
#include "FnxWord.h"
#include "FnxDesc.h" // DescToProbName

#define  PHONEME  259
//#define  DUMP_NETS /* Uncomment this to dump the collapsed pronunciation networks */

/*FUNCTION_HEADER*******************
 * NAME:    ;ParseWord
 * DESC:    Build a network structure from a pronunciation.
 * IN:      pParser - Pointer to a parser structure from which to pull tokens and phones.
 * OUT:     pParser's iPos is advanced, and a new network structure is returned.
 * RETURN:  A new network structure (non-NULL, even if no nodes), or NULL on error.
 * NOTES:   Uses either the string pParser->sBuffer (starting at index pParser->iPos) OR
              the file pParser->fp to extract pronunciation from.  If they are both non-NULL,
              the string will be used, but shame on you.
            Calls itself recursively to build subnets from elements in [], (), {}
              or after '|', thus allowing nested pronunciation graphs like "a [b (c | d [e])] | g",
              which would allow the pronunciations "a", "a b", "a b c", "a b d", "a b d e", and "g". 
            This example would be parsed by creating a network with an "a",
              calling ParseWord() to parse "[b (c | d [e])]" into a subnetwork
              that would be appended as an optional network, to "a",
              calling ParseWord() again to parse "g" into another subnetwork
              would be "or"'ed with the first part, and then returning the whole thing.
            A phoneme can have "#" and a stress level, e.g.: (r I#3 bc [bh] s).
            A comma (",") causes the next field to be ignored, e.g., (r I bc [bh] s,0004| m,0032)
              would cause the flag fields "0004" and "0032" to be ignored.
 *END_HEADER***************************/
NetworkPtr ParseWord(ParserPtr pParser)
{
   SDWORD *piTag; /* Tag (type) of current token being parsed */
   NodePtr pNode; /* New node to be added to the network */
   NetworkPtr pNet=NULL; /* Network built from the parsed string */
   NetworkPtr pSubNet;   /* Subnetwork built within [], () or {}'s. */
   char *sDelim = "[]{}()|#;," ;

   /* Get the next token to be parsed, i.e. the first token of this (sub)network. */
   GetToken(pParser, sDelim);

   /* Get a pointer to the current token# so we don't have to keep dereferencing pParser->iToken.
      Use address instead of actual integer so that it is always current. */
   piTag = &(pParser->iToken);
   
   /* Handle one token at a time until a closing tag is found.  At the end of each
      pass through the while loop, the next token to be parsed must be in pParser->iToken
      (which is the same as *piTag). */
   while (*piTag>0 && *piTag!=']' && *piTag!=')' && *piTag!='}' && *piTag!=';')
   {
      switch (*piTag)
      {
         case PHONEME: /* Phoneme or Phoneme#stressLevel */
            /** Append the current phoneme onto the end of the current network */
            /* Allocate a new phone node, and copy its name in. */
            pNode = (NodePtr) FNX_CALLOC(1,sizeof(Node));
            pNode->sName = FNX_STRDUP(pParser->sToken);
            /* Consume the phone token and see if the next one is '#' */
            if (GetToken(pParser, sDelim)=='#')
            {
               /* Next token is '#', so consume it and get the one after that,
                  which contains a number indicating stress level */
               GetToken(pParser, sDelim);
               /* We don't actually USE stress, so don't bother storing it. */
               //pNode->iStress = atoi(pParser->sToken);
            }
            /* Append the phone node to the end of the network */
            if (!pNet)
            {
               /* Allocate an empty network */
               pNet = (NetworkPtr) FNX_CALLOC(1,sizeof(Network));
               if (!pNet)
               {
                  Message(FNX_STDERR,"Out of memory in ParseWord\n");
                  return NULL;
               }
               /* Don't set the "bMergeNodes" flag, because we don't want
                  OrNet() to combine multiple phones into a single node
                  like is done with words in a grammar network. */
               //pNet->bMergeNodes = FALSE; /* Don't have to bother, because Calloc() already set it to 0. */
               
               /* Make sure each network (and subnetwork) points to the same pool of
                  linked list nodes so they can be shared and handled properly. */
               pNet->pLinkPool = pParser->pLinkPool;
            }
            AppendNode(pNet, pNode);
            break;
         case '[':
            /* Parse the substring ending with a matching ']' */
            pSubNet = ParseWord(pParser);
            pSubNet->bOptional = TRUE;
            if (*piTag != ']')
            {
               Message(FNX_STDERR,"Warning: No closing ']' in pronunciation:\n  %s\n", pParser->sBuffer);
            }
            /* Consume the ']' and replace it with the next token */
            else GetToken(pParser, sDelim);
            if (pNet)
               AppendNet(pNet, pSubNet);
            else pNet = pSubNet;
            break;
         case '(':
            pSubNet = ParseWord(pParser);
            if (*piTag != ')' )
            {
               Message(FNX_STDERR,"Warning: No closing ')' in pronunciation:\n  %s\n", pParser->sBuffer);
            }
            /* Consume the ')' and replace it with the next token */
            else GetToken(pParser, sDelim);
            if (pNet)
               AppendNet(pNet, pSubNet);
            else pNet = pSubNet;
            break;
         case '{':
            pSubNet = ParseWord(pParser);
            if (*piTag != '}' )
            {
               Message(FNX_STDERR,"Warning: No closing '}' in pronunciation:\n  %s\n", pParser->sBuffer);
            }
            /* Consume the '}' and replace it with the next token */
            else GetToken(pParser, sDelim);
            if (pNet)
               AppendNet(pNet, pSubNet);
            else pNet = pSubNet;
            break;
         case '|':
            pSubNet = ParseWord(pParser);
            if (pNet)
               OrNet(pNet, pSubNet);
            else 
            {
               /* We did something like "{ | a b c };" where a '|' occured after an empty string.
                  This means that "nothing" is a possiblity, so set the optional flag. */
               pNet = pSubNet;
               pNet->bOptional = TRUE;
            }
            /* (Don't consume whatever token remains after parsing this subnet.) */
            break;
         case ',':
            GetToken(pParser, sDelim); /* Consume ',' and get the number afterwards. */
            GetToken(pParser, sDelim); /* Consume the number afterwards. */
      }  /* switch */
   }  /* while valid tags */
   return pNet;
}  /* ParseWord */

/*FUNCTION_HEADER*******************
 * NAME:    ;NetToWord
 * DESC:    Build a word structure from a network structure and word name.
 * IN:      pNet      - Pronunciation network derived from the pronunciation string.
 *          sWordName - Name of word (like "seven")
 * OUT:     A wordT structure is built, and pNet is free'd.
 * RETURN:  Pointer to the newly-built wordT structure
 * NOTES:   We could make storage for word nodes more compact by figuring
              how many total indices there are in all of the words' nodes
              and allocate a single block of indices for the word.
 *END_HEADER***************************/
wordTPtr NetToWord(NetworkPtr pNet, char *sWordName)
{
   SDWORD i, j, iNumNodes, iNumInit, iNumFinal;
   wstateTPtr ws; /* Pointer to corresponding (phoneme) node in w->nodes[i] */
   wordTPtr w;    /* Pointer to the new wordT structure being created */
   NodePtr pNode; /* Current node in pNet(work) */
   NodePtr *ppNodes, *ppInit, *ppFinal, *ppPrev, *ppNext; /* Temporary arrays converted from linked lists*/
   SWORDPTR pwNumNext, pwNumPrev; /* Array of #next and #prev nodes for each node in ppNodes[] */
   char     *sBuf; /* Character pointer into the memory block beginning at w */
   SDWORD   iPos;  /* Next free position in sBuf[] available for putting stuff in */
   SDWORD   iSize; /* Total size allocated for sBuf[] */

   /* Do error-checking to make sure pNet has nodes. */
   if (!pNet || !pNet->pNodes || !pNet->pInit || !pNet->pFinal)
   {
      if (!pNet)
         Message(FNX_STDERR,"Error: The word '%s' has a NULL pronunciation graph\n", sWordName);
      else if (!pNet->pNodes)
         Message(FNX_STDERR,"Error: The word '%s' doesn't have any nodes in its pronunciation graph\n", sWordName);
      if (!pNet->pInit)
         Message(FNX_STDERR,"Error: The word '%s' doesn't have any initial nodes in its pronunciation graph\n", sWordName);
      if (!pNet->pFinal)
         Message(FNX_STDERR,"Error: The word '%s' doesn't have any final nodes in its pronunciation graph\n", sWordName);
      return NULL;
   }
   /* If pNet is flagged as optional, that means that it can be matched by
      no sound at all, which is an error.  Rather than crash, we'll just pretend
      it isn't really optional and require that initial and final nodes be real nodes. */
   if (pNet->bOptional)
      Message(FNX_STDERR,"Warning: The word '%s' has a completely optional pronunciation graph\n"
                     "         (Treating as though it is not optional).\n", sWordName);

   /* Get the number of nodes in the network */
   iNumNodes = ListSize(pNet->pNodes);

   /* Convert the linked lists of nodes into an array of pointers to nodes
      in reverse order, since they are generally backwards in the linked list. */
   ppNodes = (NodePtr *) ListToArray(&(pNet->pNodes), iNumNodes, pNet->pLinkPool);
   pNet->pNodes = NULL;

   /* Number the nodes in pNet->pNodes.
      (If having the nodes slightly out of order is a problem, we could put a sorting routine somewhere
      in here to sort the nodes such that all nodes can only go to ones that are later in the 
      list.  For now we will be slightly faster by leaving it alone.)*/
   for (i=0; i<iNumNodes; i++)
      ppNodes[i]->iID = i;

   /* Convert the lists of initial and final nodes to arrays and reverse their order, too */
   iNumInit     = ListSize(pNet->pInit);
   ppInit       = (NodePtr *) ListToArray(&(pNet->pInit), iNumInit, pNet->pLinkPool);
   pNet->pInit  = NULL;

   iNumFinal    = ListSize(pNet->pFinal);
   ppFinal      = (NodePtr *) ListToArray(&(pNet->pFinal), iNumFinal, pNet->pLinkPool);
   pNet->pFinal = NULL;
   
   /* Set the bInit and bFinal flags of the initial and final nodes, respectively */
   for (i=0; i<iNumInit; i++)
      ppInit[i]->bInit = TRUE;
   for (i=0; i<iNumFinal; i++)
      ppFinal[i]->bFinal = TRUE;

   /* Count how many 'next' and 'prev' nodes each node has. */
   pwNumNext = (SWORDPTR)FNX_MALLOC(iNumNodes * sizeof(SWORD));
   pwNumPrev = (SWORDPTR)FNX_MALLOC(iNumNodes * sizeof(SWORD));
   for (i=0; i < iNumNodes; i++)
   {
      pwNumNext[i] = (short) ListSize(ppNodes[i]->pNext);
      pwNumPrev[i] = (short) ListSize(ppNodes[i]->pPrev);
   }

   /**** Calculate the size needed for the word and all of its parts */
   iSize  = SIZE_WORDT;                 // w
   iSize += iNumNodes * SIZE_WSTATET;   // w->nodes[]
   
   // Put all SWORD's next, since they need only be 2-byte aligned.
   iSize += iNumInit * sizeof(SWORD);   // w->initnodes[]
   iSize += iNumFinal * sizeof(SWORD);  // w->finalnodes[]
   for (i=0; i < iNumNodes; i++)
      iSize += pwNumNext[i] * sizeof(SWORD) + pwNumPrev[i] * sizeof(SWORD);

   // Put all strings at the end so that they will not cause non-4-byte-aligned offsets for structures.
   iSize += FNX_STRLEN(sWordName)+1;        // w->name
   for (i=0; i < iNumNodes; i++)
   {
      if (ppNodes[i]->sName)
         iSize += FNX_STRLEN(ppNodes[i]->sName) + 1;
   }


   /**** Build a word object, and create its name string. */
   w         = (wordTPtr )FNX_CALLOC(1,iSize); // Allocate room for word and all its fields.
   sBuf      = (char *)w;                      // Use a character pointer for easy indexing.
   iPos      = SIZE_WORDT;                     // Set iPos at next free position in allocated block.

   /* Set the number of nodes. */
   w->numnodes = (short) iNumNodes;
   FNX_ASSERT(w->numnodes);

   /* Allocate nodes and initialize to all 0's */
   w->nodes = (wstateTPtr )&sBuf[iPos];
   iPos += w->numnodes * SIZE_WSTATET;

   /* Count the number of initial nodes in the word, and allocate initial nodes. */
   w->numinit = (short) iNumInit;
   FNX_ASSERT(w->numinit);
   w->initnodes = (SWORDPTR)&sBuf[iPos];
   iPos += w->numinit * sizeof(SWORD);
   
   /* Count the number of final nodes in the word, and allocate final nodes. */
   w->numfinal = (short) iNumFinal;
   FNX_ASSERT(w->numfinal);
   w->finalnodes = (SWORDPTR)&sBuf[iPos];
   iPos += w->numfinal * sizeof(SWORD);
   
   /* Fill in initial nodes with the index in w->nodes[] of each of
      the nodes that are initial nodes. */
   for (i=0; i<iNumInit; i++)
      w->initnodes[i] = (short) ppInit[i]->iID;

   /* Fill in final nodes with the index in w->nodes[] of each of
      the nodes that are final nodes.*/
   for (i=0; i<iNumFinal; i++)
      w->finalnodes[i] = (short) ppFinal[i]->iID;
   
   /* allocate & copy word node "next" and "prev" lists, and copy phoneme name
      and other information from each net node to the corresponding word node. */
   for(i=0; i < w->numnodes; i++) 
   {
      pNode = ppNodes[i];
      ws = &(w->nodes[i]);
      
      ws->tag = (short) i; /* Set tag to this node's index in w->nodes[] */
      
      /* Set the type of w->nodes[i] to PH_INIT, PH_FINAL, PH_INITFINAL, or PH_NORMAL */
      if((pNode->bInit) && (pNode->bFinal)) 
         ws->type = PH_INITFINAL;
      else if(pNode->bInit) 
         ws->type = PH_INIT;
      else if(pNode->bFinal) 
         ws->type = PH_FINAL;
      else ws->type = PH_NORMAL;
      
      /* Set the number of following and preceeding nodes in the graph structure,
         and allocate pointers to each */
      ws->numnext = pwNumNext[i];
      ws->next = (SWORDPTR)&sBuf[iPos];
      iPos += ws->numnext * sizeof(SWORD);

      ws->numprev = pwNumPrev[i];
      ws->prev = (SWORDPTR)&sBuf[iPos];
      iPos += ws->numprev * sizeof(SWORD);
      
      /* fill in next node pointers */
      ppNext = (NodePtr *) ListToArray(&(pNode->pNext), ws->numnext, pNet->pLinkPool);
      pNode->pNext = NULL; /* List no longer valid, because links have been free'd */

      for(j=0; j < ws->numnext; j++) 
         ws->next[j] = (short) ppNext[j]->iID;
      if (ppNext)
         FNX_FREE(ppNext);

      /* fill in prev node pointers */
      ppPrev = (NodePtr *) ListToArray(&(pNode->pPrev), ws->numprev, pNet->pLinkPool);
      pNode->pPrev = NULL;

      for(j=0; j < ws->numprev; j++) 
         ws->prev[j] = (short) ppPrev[j]->iID;
      if (ppPrev)
         FNX_FREE(ppPrev);

      /* Copy other info */
      ws->cat    = (SWORD)pNode->iCat;
      ws->part   = (char) pNode->ePart; /* Set which part of the phone this is (left/center/right or triphone) */ 
#ifndef USE_SEARCH_GRAPH
      ws->mindur = (SWORD)pNode->iMinDur;
      ws->maxdur = (SWORD)pNode->iMaxDur;
#endif
      //ws->stress = (char) pNode->iStress; /* We don't actually USE stress, so don't bother storing it */
      
   }  /* for i */

   /* Copy the name of the word over.  Put this and all other strings at
      the end of the word's allocated block of memory so that the various
      structures will all start on 4-byte aligned addresses without having
      to pad the ends of strings with wasted bytes. */
   w->length = FNX_STRLEN(sWordName)+1; /* Tell how many bytes are allocated for the name string */
   w->name   = &sBuf[iPos];
   FNX_STRCPY(w->name, sWordName);   /* Make a copy of the name string */
   iPos += w->length;

   /* Now copy the names of the nodes' phonemes over, if any */
   for(i=0; i < w->numnodes; i++) 
   {
      pNode = ppNodes[i];
      ws = &(w->nodes[i]);

      /* Copy the 'internal' name of the current node into the phoneme node's 'phoneme' string. */
      if (pNode->sName)
      {
         ws->phone_len = FNX_STRLEN(pNode->sName) + 1;
         ws->phoneme   = &sBuf[iPos];
         FNX_STRCPY(&sBuf[iPos], pNode->sName);
         iPos += ws->phone_len;
      }
      else ws->phone_len = 0;
   }  /* for i */


   /* Make sure that we used exactly as much space as we allocated,
      so that we don't waste memory nor overrun memory. */
   FNX_ASSERT(iSize == iPos);

   /* Free up whatever is left of each node, and the temporary arrays of pointers. */
   if (ppNodes)
   {
      for (i=0; i<iNumNodes; i++)
         FreeNode(ppNodes[i], pNet->pLinkPool);
      FNX_FREE(ppNodes);
   }
   if (ppInit)
      FNX_FREE(ppInit);
   if (ppFinal)
      FNX_FREE(ppFinal);
   
   /* Free up whatever is left of pNet */
   FreeNetwork(pNet); 
   
   if (pwNumNext)
      FNX_FREE(pwNumNext);
   if (pwNumPrev)
      FNX_FREE(pwNumPrev);
   /* Return a pointer to the new wordT structure */
   return w;
}  /* NetToWord */

/*FUNCTION_HEADER*******************
 * NAME:    ;FixWordNet
 * DESC:    Set ID#'s, init/final flags, and basephone id#'s in a word network.
 * IN:      pNet - Word network to fix.
            pDesc - Structure containing basephone information.
 * OUT:     All of pNet's nodes have their iID, bInit, bFinal, and iBasePhone fields set.
 * RETURN:  0 on success, -1 on error (e.g., if an unrecognized phoneme is found).
 * NOTES:   Should be called after calling ParseWord(), which cannot do this,
              since it is recursive.
 *END_HEADER***************************/
SDWORD FixWordNet(NetworkPtr pNetwork, DescPtr pDesc)
{
   llistPtr pLink;
   NodePtr pNode;
   SDWORD iID;
   SDWORD iStatus=0; /* Return value: "OK" unless an error is found. */

   if (!pNetwork)
      return iStatus; /* No word, so don't crash. */

   iID = ListSize(pNetwork->pNodes);
   for (pLink=pNetwork->pNodes; pLink; pLink = pLink->pNext)
   {
      /* Get a pointer to the current node */
      pNode = (NodePtr) pLink->p;
      /* Set the node's ID#.  Use reverse order since they
         are inserted into the list backwards. */
      pNode->iID = --iID;
      /* Set the iBasePhone index number. */
      if (pDesc && pNode->sName)
      {
         pNode->iBasePhone = BasePhoneIndex(pDesc, pNode->sName);
         if (pNode->iBasePhone < 0) /* Couldn't find the base phone: probably bogus */
         {
            Message(NULL,"Warning: Unrecognized base phoneme '%s' will be ignored.\n", pNode->sName);
            iStatus = -1; /* => error */
         }
      }
      else pNode->iBasePhone = -1;
      /* Clear all init & final flags so they can be set below. */
      pNode->bInit = pNode->bFinal = FALSE;
      pNode->iCat = -1; /* Set the category to -1 to indicate that it this is still a basephone node */
   }
   /* Set initial flags */
   for (pLink=pNetwork->pInit; pLink; pLink = pLink->pNext)
   {
      /* Get a pointer to the current node */
      pNode = (NodePtr) pLink->p;
      pNode->bInit = TRUE;
   }
   /* Set final flags */
   for (pLink=pNetwork->pFinal; pLink; pLink = pLink->pNext)
   {
      /* Get a pointer to the current node */
      pNode = (NodePtr) pLink->p;
      pNode->bFinal = TRUE;
   }
   return iStatus;
}  /* FixWordNet */

/*FUNCTION_HEADER*******************
 * NAME:    ;SetWordNetID
 * DESC:    Set ID#'s of nodes in a word network.
 * IN:      pNet - Word network to fix.
 * OUT:     All of pNet's nodes have their iID fields set.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
void SetWordNetID(NetworkPtr pNetwork)
{
   llistPtr pLink;
   NodePtr pNode;
   SDWORD iID=0;
   for (pLink=pNetwork->pNodes; pLink; pLink = pLink->pNext)
   {
      /* Get a pointer to the current node */
      pNode = (NodePtr) pLink->p;
      /* Set the node's ID#. */
      pNode->iID = iID++;
   }
}  /* SetWordNetID */

#ifdef DUMP_NETS
/*FUNCTION_HEADER*******************
 * NAME:    ;DumpList
 * DESC:    Dump the ID#'s (and names) of a list of nodes.
 * IN:      sIntro - String to be printed before the list (ignored if NULL)
            pList - A linked list of Node structures.
 * OUT:     The ID# and name of each node in pList is printed to stdout.
 * RETURN:  n/a
 * NOTES:   For use in debugging only.  Can be #if'ed out.
 *END_HEADER***************************/
static void DumpList(char *sIntro, llistPtr pList)
{
   llistPtr pLink;
   NodePtr pNode;

   if (sIntro)
      printf("%s", sIntro);

   if (pList)
   {
      for (pLink=pList; pLink; pLink = pLink->pNext)
      {
         pNode = pLink->p;
         printf("%d", pNode->iID);
         if (pLink->pNext)
            printf(", ");
      }
      printf(" (");
      for (pLink=pList; pLink; pLink = pLink->pNext)
      {
         pNode = pLink->p;
         printf("%s", pNode->sName ? pNode->sName : "<null>");
         if (pLink->pNext)
            printf(", ");
      }
      printf(")");
   }
   printf("\n");
}

/*FUNCTION_HEADER*******************
 * NAME:    ;DumpNet
 * DESC:    Dump the contents of a Network to stdout.
 * IN:      pNetwork - Network to dump
 * OUT:     The information in pNetwork is printed to stdout
 * RETURN:  n/a
 * NOTES:   For use in debugging only.  Can be #if'ed out.
 *END_HEADER***************************/
void DumpNet(NetworkPtr pNetwork)
{
   llistPtr pLink;
   NodePtr pNode;

   /* Print the name of the network. */
   printf("Name: %s\n", pNetwork->sName ? pNetwork->sName : "<null>");

   /* Print the list of initial and final nodes */
   DumpList("Initial nodes: ", pNetwork->pInit);
   DumpList("Final nodes:   ", pNetwork->pFinal);

   /* Print information about the individual nodes */
   for (pLink=pNetwork->pNodes; pLink; pLink = pLink->pNext)
   {
      pNode = (NodePtr) pLink->p;
      printf("Node %d: %s", pNode->iID, pNode->sName);
      if (pNode->sExternal)
         printf(" [-> %s]", pNode->sExternal);
      printf("; BasePhone %d, Cat %d", pNode->iBasePhone, pNode->iCat);
      if (pNode->bInit)
         printf(" (init)");
      if (pNode->bFinal)
         printf(" (final)");
      printf("\n");
      DumpList("         Prev: ", pNode->pPrev);
      DumpList("         Next: ", pNode->pNext);
   }  /* for each node */
}  /* DumpNet */
#endif // dumping code.

/*FUNCTION_HEADER*******************
 * NAME:    ;buildWord
 * DESC:    Build a word node from a pronunciation string and word name.
 * IN:      sPronunciation - Pronunciation string (like "s E v [&] n | s E v n=")
 *          pDesc          - Description structure used for expanding pronunciations into context-dependent ones.
 *          sWordName      - Name of word (like "seven")
 * OUT:     A wordT structure is built
 * RETURN:  Pointer to the newly-built wordT structure
 * NOTES:   sPronunciation is typically whatever appears between the {}'s in a dictionary
              file (or between the outermost ()'s before the ending ';').
            Pronunciations can contain [] for optional portions, () to group things, and
              '|' for alternatives.  For example, "a [b | c (d | e [f])] | g" would yield
              the pronunciations "a", "ab", "acd", "ace", "acef", and "g".
            This code replaces the old Bison version of buildWord() that
              was 22 times slower.
 *END_HEADER***************************/
wordTPtr buildWord(char *sPronunciation, char *sWordName, DescPtr pDesc)
{
   NetworkPtr pNet;   /* Network (graph) of phoneme nodes */
   wordTPtr w;     /* word object    */
   Parser parser;  /* Structure containing parse string, current position, next token, etc. */

   /* Set the buffer to be parsed. */
   parser.sBuffer = sPronunciation;
   parser.iPos    = 0;
   parser.fp      = NULL; /* Parsing from string, not file */
   parser.bUseToken = FALSE; /* Just start from the beginning of the buffer */
   parser.pLinkPool   = NewLinkPool(1000);

   /* Build an entire network out of the pronunciation string */
   pNet = ParseWord(&parser);

   /* Set ID#'s, init/final flags, basephone ID's */
   if (FixWordNet(pNet, pDesc) != 0)
   {
      //There was an unrecognized phoneme or some other problem in pNet, so fail on this word.
      FreeNetwork(pNet);
      FreeLinkPool(parser.pLinkPool);
      return NULL;
   }

   /* Collpase base phoneme pronunciation networks to remove redundancies.
      This makes the network smaller (by about 40%) and speeds up ExpandWord
      (by about 30%). */
   CollapseNet(pNet);

#ifndef USE_SEARCH_GRAPH
   /* Expand the word if possible */
   if (pDesc)
      ExpandWord(pDesc, pNet);
#endif

   /* Collapse the expanded (context-dependent) pronunciation graph
      in case there are any additional redundancies that appeared
      during expansion.  */
   CollapseNet(pNet);

   /* Convert the pronunciation network to a (more compact) wordT structure. */
   if (pNet)
      w = NetToWord(pNet, sWordName); /* Builds wordT structure and frees pNet */
   else w = NULL;

   /* Free up the linked list pool, since all have been freed. */
   FreeLinkPool(parser.pLinkPool);

   /* Return the word node. */
   return w;
}  /* buildWord */

extern void DumpNetwork(NetworkPtr pNet, DescPtr pDesc);

/*FUNCTION_HEADER*******************
 * NAME:    ;buildWordFP
 * DESC:    Build a word node from a pronunciation in a file and word name.
 * IN:      fp        - File pointer of an opened text file, pointing to the first character
                          in the pronunciation (either the opening '{' or '(' or just beyond it).
 *          sWordName - Name of word (like "seven")
            pDesc     - Description structure used for expanding word into context-dependent
                          phoneme categories (NULL=>don't expand).
            sFirstToken-String containing the first token already read (e.g., "(" or "{").
 * OUT:     A wordT structure is built, and the file pointer is advanced to just beyond the
              closing ';' (even if opening '(' or '{' was already consumed).  If pDesc
              is non-NULL, the word is expanded into context-dependent phonemes.
 * RETURN:  Pointer to the newly-built wordT structure
 * NOTES:   sPronunciation is typically whatever appears between the {}'s in a dictionary
              file (or between the outermost ()'s before the ending ';').
            Pronunciations can contain [] for optional portions, () or {} to group things, and
              '|' for alternatives.  For example, "a [b | c (d | e [f])] | g" would yield
              the pronunciations "a", "ab", "acd", "ace", "acef", and "g".
 *END_HEADER***************************/
wordTPtr buildWordFP(FILE *fp, char *sWordName, DescPtr pDesc, char *sFirstToken)
{
   NetworkPtr pNet;   /* Network (graph) of phoneme nodes */
   wordTPtr w;     /* word object    */
   Parser parser;  /* Structure containing parse string, current position, next token, etc. */

   /* Set the buffer to be parsed. */
   parser.sBuffer = NULL;
   parser.iPos    = 0;
   parser.fp      = fp; /* Parsing from file, not string. */
   parser.pLinkPool   = NewLinkPool(100);

   if (sFirstToken && sFirstToken[0])
   {
      /* Make the first call to GetToken() use sFirstToken 
         instead of reading from fp. */
      parser.bUseToken = TRUE;
      FNX_STRCPY(parser.sToken, sFirstToken);
   }
   else parser.bUseToken = FALSE;

   /* Parse a pronunciation from the file fp. */
   pNet = ParseWord(&parser);
   
   /* Make sure we consume the terminating ';' in fp. */
   while (parser.iToken && parser.iToken != (SDWORD) ';')
      GetToken(&parser, ";");

   /* Set init/final flags, basephone ID's */
   if (FixWordNet(pNet, pDesc) != 0)
   {
      //There was an unrecognized phoneme or some other problem in pNet, so fail on this word.
      FreeNetwork(pNet);
      FreeLinkPool(parser.pLinkPool);
      return NULL;
   }

   /* Collpase base phoneme pronunciation networks to remove redundancies.
      This makes the network smaller (by about 40%) and speeds up ExpandWord
      (by about 30%). */
   CollapseNet(pNet);

#ifndef USE_SEARCH_GRAPH
   /* Expand the word if possible */
   if (pDesc)
   {
      ExpandWord(pDesc, pNet);
   
      /* Collapse the expanded (context-dependent) pronunciation graph
         in case there are any additional redundancies that appeared
         during expansion.  */
      CollapseNet(pNet);
   }
#endif

#ifdef DUMP_NETS
   printf("\n");
   pNet->sName = sWordName;
   DumpNet(pNet);
   pNet->sName = NULL;
#endif

   /* Convert the pronunciation network to a (more compact) wordT structure. */
   if (pNet)
      w = NetToWord(pNet, sWordName); /* Builds wordT structure and frees pNet */
   else w = NULL;

   /* Free up the linked list pool, since all have been freed. */
   FreeLinkPool(parser.pLinkPool);

   /* Return the word node. */
   return w;
}  /* buildWordFP */
