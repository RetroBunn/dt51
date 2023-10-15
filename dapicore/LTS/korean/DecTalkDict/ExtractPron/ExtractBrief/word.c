/*C_HEADER_FILE****************************************************************
FILE        :  word.c
DESC        :  
TABS        :  3
OWNER       :  
DATE CREATED:  29 April 1999

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/27/03 3:11p $
  $Revision: 12 $

*END_HEADER*******************************************************************/
#include "FnxPlatform.h"
#include "FnxStdlib.h"
#include "FnxAllocate.h"
#include "FnxNames.h"
#include "FnxWord.h"
#include "FnxFiles.h"

#ifndef USE_SEARCH_GRAPH
/*FUNCTION_HEADER**********************
 * NAME:    ;ExpandNode
 * DESC:    Expand a base phoneme node in a word's pronunciation graph
              into one or more context-dependent phoneme category nodes.
 * IN:      pDesc - Category information (i.e., extracted from a desc(ription) file).
            pNode - A base phoneme node in a word's pronunciation graph.
            pNetwork - The entire word pronunciation graph.
 * OUT:     pNetwork is modified such that pNode is replaced with one or more
              context-dependent phoneme nodes which are inserted into the
              graph where pNode used to be.
            pNetwork->pNodes, ->pInit and ->pFinal are updated.
 * RETURN:  0 on success, -1 on error.
 * NOTES:   pNetwork is often made up of some base phoneme nodes and some
              context-dependent nodes when not all of the nodes have yet
              been expanded.  However, each node remembers its base phoneme,
              so even expanded nodes can be used to determine the contexts
              around a node that is yet to be expanded.
            As each node is expanded, it remains connected to the other nodes
              in the graph.
            pNetwork->pNodes have all new nodes (and reused old nodes) inserted
              into it.  Also, pNetwork->pInit and ->pFinal have nodes inserted
              into them for any initial or final nodes, respectively.
 *END_HEADER***************************/
SDWORD ExpandNode(DescPtr pDesc, NodePtr pNode, NetworkPtr pNetwork)
{
   NodePtr  pInitNode  =NULL; /* Temporary initial ".pau" node used if pNode is an initial node. */
   NodePtr  pFinalNode =NULL; /* Temporary final   ".pau" node used if pNode is a final node. */
   NodePtr  pLeftNode, pRightNode; /* Current left or right node being dealt with */
   NodePtr  pPrevNode, pNextNode;  /* Current previous or following node */
   NodePtr  pTriphoneNode;         /* Current triphone node */
   llistPtr pLeftNodes =NULL; /* Linked lists of left context category nodes, (e.g., "$a<c") */ 
   llistPtr pRightNodes=NULL; /*   right context category nodes, and (e.g., "c>$d") */
   llistPtr pTriNodes  =NULL; /*   and triphones category nodes (e.g., "$a<c>$d"). */
   llistPtr pPrevLink, pNextLink, pLeftLink, pRightLink, pTriLink; /* Pointers for traversing lists */
   SWORD iPause;     /* Index of '.pau' base phone */   
   SWORD iBasePhone; /* Base phoneme of pNode */
   SWORD iCat;       /* Index of current category being examined */   
   SDWORD iErr;       /* Error value returned by ReplaceLink() [0=>ok, -1=>wasn't in list] */

   /* Make sure we don't have bogus inputs */
   if (!pDesc || !pNode || !pNetwork)
      return -1;

   FNX_ASSERT(pNode->iCat==-1); // Make sure every node is flagged as a basephone node before it is expanded.

   iBasePhone = pNode->iBasePhone;
   iPause     = BasePhoneIndex(pDesc, ".pau");

   pLeftNodes = pRightNodes = NULL;

   /* See if this node is an "initial" node. */
   if (pNode->bInit)
   {
      /* Create a temporary beginning "pause" node and insert it into pNode's
         list of previous nodes.  This node will be used to keep track of a
         list of which nodes need to be flagged as "initial" nodes and that 
         need to be inserted into the network's list of initial nodes.  
         It will also allow the ".pau" context to be added without treating
         it as a special case. */
      pInitNode = (NodePtr) FNX_CALLOC(1, sizeof(Node));
      pInitNode->iBasePhone = iPause;
      /* Insert the temporary node into pNode's list of "previous" nodes */
      InsertLink(pInitNode, &(pNode->pPrev), pNetwork->pLinkPool);
      /* Insert pNode into the 'next' list of the initial node so that
         ReplaceLink() will work properly when called. */
      pInitNode->pNext = NULL;
      InsertLink(pNode, &(pInitNode->pNext), pNetwork->pLinkPool);
   }
   /* See if this node is a "final" node */
   if (pNode->bFinal)
   {
      /* Create a temporary ending "pause" node */
      pFinalNode = (NodePtr) FNX_CALLOC(1, sizeof(Node));
      pFinalNode->iBasePhone = iPause;
      /* Insert the temporary node into pNode's list of "next" nodes */
      InsertLink(pFinalNode, &(pNode->pNext), pNetwork->pLinkPool);
      /* Insert pNode into the 'prev' list of the final node, so that
         ReplaceLink() will work properly when called. */
      pFinalNode->pPrev = NULL;
      InsertLink(pNode, &(pFinalNode->pPrev), pNetwork->pLinkPool);
   }

   /*** Left Nodes ***/
   /* Create a list of 'left' nodes.  For each previous node, if a
      category 'prev<node' exists, it is created and added to the list
      of left nodes.  Otherwise, the previous node itself is added
      to the list.  We end up with a list of all of the nodes that
      need to be connected to triphones, the center, or the right nodes
      (according to what categories exist). */
   for (pPrevLink=pNode->pPrev; pPrevLink; pPrevLink = pPrevLink->pNext)
   {
      /* Get a pointer to the preceding node. */
      pPrevNode = (NodePtr)pPrevLink->p;
      /* Get the index of the category that covers "pPrev<pNode" */
      iCat = GetLeft(pDesc, pPrevNode->iBasePhone, iBasePhone);

      /* See if we found the category, i.e., if "previous<basephone" exists. */
      if (iCat >= 0)
      {
         /** We found a left-context category. **/
         /* See if this category is already represented in the list of left nodes */
         for (pLeftNode=NULL, pLeftLink=pLeftNodes; !pLeftNode && pLeftLink; pLeftLink = pLeftLink->pNext)
         {
            /* Temporarily set pLeftNode to be the node pointed to by pLeftLink->p */
            pLeftNode = (NodePtr)pLeftLink->p;
            /* If the category matches, leave pLeftNode set and thus exit the loop.
               Otherwise, set it to NULL to allow the loop to continue. */
            if (pLeftNode->iCat != iCat)
               pLeftNode = NULL;
         }  /* for */

         /* See if we found the category we need */
         if (!pLeftNode)
         {
            /* This category was not yet added for this node, so create a new node */
            pLeftNode = (NodePtr)FNX_CALLOC(1,sizeof(Node));
            pLeftNode->iBasePhone = iBasePhone;     /* Remember original base phone */
            pLeftNode->iCat       = iCat;           /* Set the category index */
            pLeftNode->ePart      = LEFT_DEPENDENT; /* Set what type of category it is */
            pLeftNode->sName      = FNX_STRDUP(pNode->sName); /* Set name to the original basephone */
#ifndef USE_SEARCH_GRAPH
            pLeftNode->iMinDur    = pDesc->pCategories[iCat].iMinDur;
            pLeftNode->iMaxDur    = pDesc->pCategories[iCat].iMaxDur;
#endif
            /* Insert the new node into the network's list of nodes */
            InsertLink(pLeftNode, &(pNetwork->pNodes), pNetwork->pLinkPool);
            /* Insert the new node into the list of left nodes */
            InsertLink(pLeftNode, &(pLeftNodes), pNetwork->pLinkPool);
         }  /* if must create new node */

         /* Replace the previous node's link to the old node with a pointer to this one. */
         iErr = ReplaceLink(pPrevNode->pNext, pNode, pLeftNode);
         FNX_ASSERT(!iErr);
         /* Point this link to the previous node */
         InsertLink(pPrevNode, &(pLeftNode->pPrev), pNetwork->pLinkPool);
      }  /* if found iCat */
      else /* Couldn't find category "previous<basephone" */
      {
         /* The category "previous<basephone" does not exist, so add
            the previous node itself to the list of left nodes so that
            it will be connected with whatever else follows. */
         /* Remove the link from the previous node to the current node, since
            all left nodes will eventually be connected with what follows them. */
         RemovePointerFromList(pNode, &pPrevNode->pNext, pNetwork->pLinkPool);
         /* Add pPrevNode to the list of left nodes */
         InsertLink(pPrevNode, &(pLeftNodes), pNetwork->pLinkPool);
      }  /* else category not defined */
   }  /* for each previous node */

   /*** Right Nodes ***/
   /* Create a list of 'right' nodes.  For each following node, if a
      category 'node>next' exists, it is created and added to the list
      of right nodes.  Otherwise, the following node itself is added
      to the list.  We end up with a list of all of the nodes that
      need to be connected to triphones, the center, or the left nodes
      (according to what categories exist). */
   for (pNextLink=pNode->pNext; pNextLink; pNextLink = pNextLink->pNext)
   {
      /* Get a pointer to the following node. */
      pNextNode = (NodePtr)pNextLink->p;
      /* Get the index of the category that covers "pNext<pNode" */
      iCat = GetRight(pDesc, iBasePhone, pNextNode->iBasePhone);

      /* See if we found the category, i.e., if "basephone>next" exists */
      if (iCat>=0)
      {
         /** We found a right-context category. **/
         /* See if this category is already represented in the list of right nodes */
         for (pRightNode=NULL, pRightLink=pRightNodes; !pRightNode && pRightLink; pRightLink = pRightLink->pNext)
         {
            /* Temporarily set pRightNode to be the node pointed to by pRightLink->p */
            pRightNode = (NodePtr)pRightLink->p;
            /* If the category matches, leave pRightNode set and thus exit the loop.
               Otherwise, set it to NULL to allow the loop to continue. */
            if (pRightNode->iCat != iCat)
               pRightNode = NULL;
         }  /* for */

         if (!pRightNode) /* See if we found the category we need */
         {
            /* This category not yet added for this node, so create a new node */
            pRightNode = (NodePtr)FNX_CALLOC(1,sizeof(Node));
            pRightNode->iBasePhone = iBasePhone;     /* Remember original base phone */
            pRightNode->iCat       = iCat;           /* Remember category index */
            pRightNode->ePart      = RIGHT_DEPENDENT;/* Set which part of the phone this category is */
            pRightNode->sName      = FNX_STRDUP(pNode->sName); /* Copy the name of the basephone in */
#ifndef USE_SEARCH_GRAPH
            pRightNode->iMinDur    = pDesc->pCategories[iCat].iMinDur;
            pRightNode->iMaxDur    = pDesc->pCategories[iCat].iMaxDur;
#endif

            /* Insert the new node into the network's list of nodes */
            InsertLink(pRightNode, &(pNetwork->pNodes), pNetwork->pLinkPool);
            /* Insert the new node into the list of right nodes */
            InsertLink(pRightNode, &pRightNodes, pNetwork->pLinkPool);
         }  /* if must create new node */

         /* Replace the following node's link to the old node with a pointer to this one. */
         iErr = ReplaceLink(pNextNode->pPrev, pNode, pRightNode);
         FNX_ASSERT(!iErr); /* Make sure the link existed and was thus replaced. */
         if (iErr)  /* In case there was a bug and ReplaceLink() failed, insert the new link anyway*/
            InsertLink(pRightNode, &(pNextNode->pPrev), pNetwork->pLinkPool);
         /* Point this link to the following node */
         InsertLink(pNextNode, &(pRightNode->pNext), pNetwork->pLinkPool);
      }  /* if found iCat for right context category */
      else /* Couldn't find category "basephone>next" */
      {
         /* Remove the link from the following node to this one, since
            adding pNext to the list of right nodes will ensure that it
            will be connected to whatever nodes replace pNode. */
         RemovePointerFromList(pNode, &pNextNode->pPrev, pNetwork->pLinkPool);
         /* Add pNextNode to the list of right nodes */
         InsertLink(pNextNode, &(pRightNodes), pNetwork->pLinkPool);
      }  /* else category not defined. */
   }  /* for each next node */
   
   /* Free up certain parts of the original node so that it can
      be reused as the <center> node if necessary. */
   FreeList(&pNode->pPrev, pNetwork->pLinkPool);
   FreeList(&pNode->pNext, pNetwork->pLinkPool);
   pNode->pPrev = pNode->pNext = NULL;
   pNode->iCat = GetCenter(pDesc, iBasePhone); /* Set category number to the right one */
   pNode->bInit = pNode->bFinal = FALSE;   /* Clear init & final flags */

   /*** Triphones ***/
   /* See if this phoneme has any triphones */
   if (pDesc->bTriphone)
   {
      /* For each left & right phone, see if there's a triphone defined for it. */
      for (pLeftLink = pLeftNodes; pLeftLink; pLeftLink = pLeftLink->pNext)
      {
         pLeftNode = (NodePtr)pLeftLink->p;
         for (pRightLink = pRightNodes; pRightLink; pRightLink = pRightLink->pNext)
         {
            pRightNode = (NodePtr)pRightLink->p;
            
            /* Get the index of the triphone covering this left, center and right phoneme */
            iCat = GetTriphone(pDesc, pLeftNode->iBasePhone, pNode->iBasePhone, pRightNode->iBasePhone);
            if (iCat>=0)
            {
               /* Found the triphone.  See if this triphone is already in the list
                  for this node (which happens when, e.g., a and b precede c, and d follows,
                  and $left<c>d is a triphone where a and b are both in $left). */
               for (pTriphoneNode=NULL, pTriLink=pTriNodes; !pTriphoneNode && pTriLink; pTriLink = pTriLink->pNext)
               {
                  /* Temporarily set pTriphoneNode to be the node pointed to by pTriLink->p */
                  pTriphoneNode = (NodePtr)pTriLink->p;
                  /* If the category matches, leave pTriphoneNode set and thus exit the loop.
                     Otherwise, set it to NULL to allow the loop to continue. */
                  if (pTriphoneNode->iCat != iCat)
                     pTriphoneNode = NULL;
               }  /* for */

               /* See if we found the category we need */
               if (!pTriphoneNode)
               {
                  /* This category not yet added for this node, so create a new node */
                  pTriphoneNode = (NodePtr)FNX_CALLOC(1,sizeof(Node));
                  pTriphoneNode->iBasePhone = iBasePhone; /* Remember original base phone */
                  pTriphoneNode->iCat       = iCat;       /* Set the category index */
                  pTriphoneNode->ePart      = TRIPHONE;   /* Set what kind of category this is */
                  pTriphoneNode->sName      = FNX_STRDUP(pNode->sName); /* Copy the basephone name */
                  pTriphoneNode->iMinDur    = pDesc->pCategories[iCat].iMinDur;
                  pTriphoneNode->iMaxDur    = pDesc->pCategories[iCat].iMaxDur;

                  /* Insert the new node into the network's list of nodes */
                  InsertLink(pTriphoneNode, &(pNetwork->pNodes), pNetwork->pLinkPool);
                  /* Insert the new node into the list of triphone nodes */
                  InsertLink(pTriphoneNode, &(pTriNodes), pNetwork->pLinkPool);
               }  /* if must create new node */

               /* Replace the left node's pointer to pNode with a pointer to pTriphoneNode,
                  if it exists (which it may not). */
               iErr = ReplaceLink(pLeftNode->pNext, pNode, pTriphoneNode);
               if (iErr)
               {
                  /* pLeftNode->pNext did not contain a link to pNode (either because
                     it was already removed due to an earlier triphone; or because
                     it was a new left context node that was just added). 
                     Either way, add the link to pTriphoneNode. */
                  InsertLink(pTriphoneNode, &(pLeftNode->pNext), pNetwork->pLinkPool);
               }
               /* Point this triphone at the left node */
               InsertLink(pLeftNode, &(pTriphoneNode->pPrev), pNetwork->pLinkPool);

               /* Replace the right node's link to pNode with a pointer 
                  to pTriphone, if it exists (which it may not). */
               iErr = ReplaceLink(pRightNode->pPrev, pNode, pTriphoneNode);
               if (iErr)
               {
                  /* pRightNode->pPrev did not contain a link to pNode (see above for why),
                     so we still need to add a link to this triphone. */
                  InsertLink(pTriphoneNode, &(pRightNode->pPrev), pNetwork->pLinkPool);
               }
               /* Point this node at the following node */
               InsertLink(pRightNode, &(pTriphoneNode->pNext), pNetwork->pLinkPool);
            }  /* if found triphone category */
            else /* Couldn't find category "left<basephone>right" */
            {
               /* Couldn't find the triphone category "left<basephone>right",
                  so see if there is a center category <basephone>. */
               if (pNode->iCat >= 0)
               {
                  /* There is a center phoneme, so connect left & right
                     to the center UNLESS they are already connected. */
                  if (!LinkExists(pNode, pLeftNode->pNext))
                     InsertLink(pNode, &(pLeftNode->pNext), pNetwork->pLinkPool);
                  if (!LinkExists(pNode, pRightNode->pPrev))
                     InsertLink(pNode, &(pRightNode->pPrev), pNetwork->pLinkPool);
               }
               else /* No center <basephone> category */
               {
                  /* There is no triphone nor center category, so connect
                     the left and right phonemes to each other. */
                  InsertLink(pRightNode, &(pLeftNode->pNext), pNetwork->pLinkPool);
                  InsertLink(pLeftNode, &(pRightNode->pPrev), pNetwork->pLinkPool);
               }  /* else no center */
            }  /* else no triphone */
         }  /* for each right node */
      }  /* for each left node */

      /* Free up the list of triphones (but not the nodes themselves), 
         now that we are done with the list. */
      FreeList(&pTriNodes, pNetwork->pLinkPool);
      pTriNodes = NULL;
   }  /* if bTriphone */
   /* See if this phoneme has a center-only category <phone> (whether or not it
      also has context categories like left<phone and/or phone>right),
      and get its index if it does (and make sure it's valid). */
   else if (pNode->iCat >= 0)
   {
      /* Connect left nodes (if any) to the original (and now center) node */
      for (pLeftLink=pLeftNodes; pLeftLink; pLeftLink = pLeftLink->pNext)
      {
         pLeftNode = (NodePtr) pLeftLink->p;
         InsertLink(pNode, &(pLeftNode->pNext), pNetwork->pLinkPool);
         InsertLink(pLeftNode, &(pNode->pPrev), pNetwork->pLinkPool);
      }  /* for each left node */
      /* Connect right nodes (if any) to the original (and now center) node */
      for (pRightLink=pRightNodes; pRightLink; pRightLink = pRightLink->pNext)
      {
         pRightNode = (NodePtr) pRightLink->p;
         InsertLink(pNode, &(pRightNode->pPrev), pNetwork->pLinkPool);
         InsertLink(pRightNode, &(pNode->pNext), pNetwork->pLinkPool);
      }  /* for each right node */
   }  /* if bCenter */
   else /* No triphones nor center node */
   {
      /* There is no <center> category for pNode (nor triphones),
         so connect all the left & right nodes to each other. */
      for (pLeftLink=pLeftNodes; pLeftLink; pLeftLink = pLeftLink->pNext)
      {
         pLeftNode = (NodePtr) pLeftLink->p;
         for (pRightLink=pRightNodes; pRightLink; pRightLink = pRightLink->pNext)
         {
            pRightNode = (NodePtr) pRightLink->p;
            if (pLeftNode!=pInitNode || pRightNode!=pFinalNode) /* Make sure at least one real node is involved! */
            {
               /* Connect the left and right nodes to each other */
               InsertLink(pRightNode, &(pLeftNode->pNext), pNetwork->pLinkPool);
               InsertLink(pLeftNode,  &(pRightNode->pPrev), pNetwork->pLinkPool);
            }
         }  /* for each right part node */
      }  /* for each left part node */
   }  /* else no center part */

   /* See if pNode was reused as a <center> category.  If it was,
      it would point to any left & right nodes that existed;
      or, at the least, it would point to the fake init
      and/or final nodes.*/
   if (pNode->pPrev || pNode->pNext)
   {
      pNode->ePart = CONTEXT_INDEPENDENT; /* Set the kind of node */
      /* (Keep pNode->sName, since it is already the original basephone) */
      if (pNode->iCat>=0)
      {
         pNode->iMinDur = pDesc->pCategories[pNode->iCat].iMinDur;
         pNode->iMaxDur = pDesc->pCategories[pNode->iCat].iMaxDur;
      }
      /* Insert pNode into the list of network nodes */
      InsertLink(pNode, &(pNetwork->pNodes), pNetwork->pLinkPool);
   }
   else /* pNode not reused as a <center> node, so free it. */
      FreeNode(pNode, pNetwork->pLinkPool);

   /* Mark all initial nodes as such, and remove their links
      to the temporary (fake) initial node; and then free the initial node */
   if (pInitNode)
   {
      /* All of the nodes that pInitNode has as "next" nodes are initial nodes. */
      for (pLeftLink=pInitNode->pNext; pLeftLink; pLeftLink=pLeftLink->pNext)
      {
         pLeftNode = (NodePtr) pLeftLink->p;
         /* Remove the link to the fake initial node from the "prev" list
            of a real initial node (which is being called pLeftNode). */
         iErr = RemovePointerFromList(pInitNode, &pLeftNode->pPrev, pNetwork->pLinkPool);
         FNX_ASSERT(iErr==0); /* Make sure the left node really pointed to the initial node */
         /* Flag the node as an initial node */
         pLeftNode->bInit = TRUE; 
         
         /* Make sure pLeftNode is a category node.  If not, then it will be
            expanded later, and will be added into the initial list at that time,
            if needed (and thus must not be added now). */
         if (pLeftNode->iCat>=0)
         {
            /* Insert the node into the network's list of initial nodes */
            FNX_ASSERT(pLeftNode != pFinalNode); /* Don't be adding temp nodes to the network! */
            InsertLink(pLeftNode, &(pNetwork->pInit), pNetwork->pLinkPool);
         }
      }  /* for each initial node of this expanded node */
      /* Free up the temporary initial node now that we're done with it. */
      FreeNode(pInitNode, pNetwork->pLinkPool);
   }
   /* Mark all final nodes as such, and remove their links
      to the temporary (fake) final node; and then free the final node. */
   if (pFinalNode)
   {
      /* All of the nodes that pFinalNode has as "previous" nodes are final nodes. */
      for (pRightLink=pFinalNode->pPrev; pRightLink; pRightLink=pRightLink->pNext)
      {
         /* Get a pointer to a real final node */
         pRightNode = (NodePtr) pRightLink->p;
         /* Remove the link to the fake final node from the "next" list
            of a real final node (which is being called pRightNode). */
         iErr = RemovePointerFromList(pFinalNode, &pRightNode->pNext, pNetwork->pLinkPool);
         FNX_ASSERT(iErr==0); /* Make sure the right node really pointed to the initial node */
         /* Flag the node as a final node */
         pRightNode->bFinal = TRUE; 
         /* Make sure pRightNode is a category node.  If not, then it will be
            expanded later, and will be added into the final list at that time,
            if needed (and thus must not be added now). */
         if (pRightNode->iCat>=0)
         {
            /* Insert the node into the network's list of final nodes */
            FNX_ASSERT(pRightNode != pInitNode); /* Don't be adding temp nodes to the network! */
            InsertLink(pRightNode, &(pNetwork->pFinal), pNetwork->pLinkPool);
         }
      }  /* for each final node of this expanded node */
      /* Free up the final node now that we're done with it. */
      FreeNode(pFinalNode, pNetwork->pLinkPool);
   }
   
   /* Now free up the linked lists of left and right nodes (though not the nodes themselves). */
   FreeList(&pLeftNodes, pNetwork->pLinkPool);
   FreeList(&pRightNodes, pNetwork->pLinkPool);

   return 0;
}  /* ExpandNode */

/*FUNCTION_HEADER**********************
 * NAME:    ;ExpandWord
 * DESC:    Expand a word's pronunciation graph into context-dependent categories.
 * IN:      pDesc    - Category information.
 *          pNetwork - A (base phoneme) pronunciation network for a word.
 * OUT:     pNetwork is modified to be a context-dependent phoneme graph.
 * RETURN:  0 on success, -1 on error.
 * NOTES:   Expands the network, but does NOT convert it to a wordT structure
            like expandWord() used to do.
            All nodes should have their iCat field set to -1 before expanding.
 *END_HEADER***************************/
SDWORD ExpandWord(DescPtr pDesc, NetworkPtr pNetwork)
{
   llistPtr pOriginalNodes;
   llistPtr pLink;

   if (!pNetwork)
      return -1;

   /* Steal the linked list of original base phoneme nodes,
      and let ExpandNodes() build a new one out of modified
      versions of these nodes (in the cases of 1- and 3-part phonemes),
      and/or from replacement nodes. */
   pOriginalNodes = pNetwork->pNodes;
   pNetwork->pNodes = NULL;

   /* Free the initial & final node lists, and let ExpandNodes()
      place initial and final nodes back onto the list. */
   FreeList(&pNetwork->pInit, pNetwork->pLinkPool);  /* Free links, but not nodes */
   FreeList(&pNetwork->pFinal, pNetwork->pLinkPool);

   /* Expand each base phoneme node in the original network
      into context-dependent phoneme category nodes.  Place
      the new nodes in pNetwork->pNodes as well as ->pInit
      and ->pFinal when appropriate. */
   for (pLink = pOriginalNodes; pLink; pLink = pLink->pNext)
   {
      if (ExpandNode(pDesc, (NodePtr)pLink->p, pNetwork) < 0)
         return -1;
   }  /* for pLink */
   return 0; /* ok */
}  /* ExpandWord */
#endif // ndef USE_SEARCH_GRAPH

/*FUNCTION_HEADER**********************
   NAME:    ;FreeWord
   DESC:    Free a word.
   IN:      pWord - A word (i.e., a wordT structure).
   OUT:     pWord is freed, along with its substructures.
   RETURN:  n/a
   NOTES:   
 *END_HEADER***************************/
void FreeWord(wordTPtr w)
{
  /* As of 7/22/2002, wordTPtr's are allocated as a single
     block of memory with all of their substructures inside,
     so just a single free() is needed to free them up. */
  if (w)
     FNX_FREE(w);
}

/*FUNCTION_HEADER**********************
   NAME:    ;FreeWords
   DESC:    Free a list of words.
   IN:      ppWordList - A list of words (i.e., an array of pointers to wordT structures).
            iNumWords  - Number of words in ppWordList.
   OUT:     ppWordList[0..iNumWords-1] and ppWordList are freed, along with substructures.
   RETURN:  n/a
   NOTES:   Calls freeWord() to free each word.
 *END_HEADER***************************/
void FreeWords(wordTPtr *ppWordList, SDWORD iNumWords)
{
   SDWORD i;
   if (ppWordList)
   {
      for (i=0; i<iNumWords; i++)
      {
         if (ppWordList[i])
            FreeWord(ppWordList[i]);
      }
      FNX_FREE(ppWordList);
   }
}  /* freeWords */

/* 
 * countPaths(w, index, *c)
 *  count the # of unique paths
 */
static void countPaths(wordTPtr w, SDWORD idx, SDWORDPTR c)
{
  SDWORD k;
  wstateTPtr wnode;
  
  if((w->nodes[idx].type==PH_FINAL) || 
     (w->nodes[idx].type==PH_INITFINAL))
    *c = *c + 1;  
  for(k=0; k<w->nodes[idx].numnext; k++) {
    wnode = &(w->nodes[w->nodes[idx].next[k]]);
    if(wnode->type==PH_EXIT) continue;
    countPaths(w, w->nodes[idx].next[k], c);
  }
}
    
/*FUNCTION_HEADER**********************
   NAME:    ;PrintPronun
   DESC:    Print all of the possible pronunciations of a word.
   IN:      w - Word to print
            iNode      - Node to start with
            sPrefix    - Pronunciation so far (from nodes preceding iNode)
            pDesc      - Description of model names (NULL=>use .phoneme field of each node)
            sSeparator - Characters to print between pronunciations (e.g., ", " or " | ").
            bEnd       - Flag for whether the last pronunciation during this call is really
                           the last pronunciation of the word (and thus should not be followed by sSeparator)
            fp - File to write to (NULL=>stdout)
   OUT:     Pronunciations are printed to fp, separated by sSeparator.
   RETURN:  n/a
   NOTES:   Called recursively to generate all pronunciations.  If you want an efficient
              pronunciation representation, a new routine is required which will use (), |, and []
              to group and separate subnetworks to provide a more compact listing of pronunciations.
            Call originally for each of the initial nodes in w, using 'bEnd=TRUE' on the
              last call, and 'bEnd=FALSE' on all earlier ones.
 *END_HEADER***************************/
#ifndef NO_SYSFILE_WRITES
void PrintPronun(wordTPtr w, SDWORD iNode, char *sPrefix, DescPtr pDesc,
                 char *sSeparator, BOOL bEnd, FILE *fp)
{
   char sBuf[200]; /* Current pronunciation being built */
   wstateTPtr pNode, pNext;
   SDWORD i;

   pNode = &(w->nodes[iNode]);
   if (!fp)
      fp=stdout;
   /* Add the current node's category name to the string */
   if (pDesc)
      FNX_SPRINTF(sBuf, "%s %s", sPrefix, pDesc->pCategories[pNode->cat].sName);
   else FNX_SPRINTF(sBuf, "%s %s", sPrefix, pNode->phoneme);

   /* Print the word if this is a final node */
   if (pNode->type == PH_FINAL || pNode->type == PH_INITFINAL)
   {
      /* Print the pronunciation to fp, followed by the separator (unless this is at the end) */
      if (bEnd && pNode->numnext==0)
         FNX_FPRINTF(fp, "%s",sBuf);
      else FNX_FPRINTF(fp, "%s%s", sBuf, sSeparator);
   }
   /* Recurse on all following nodes (except for exit nodes) */
   for (i=0; i<pNode->numnext; i++)
   {
      pNext = &(w->nodes[pNode->next[i]]);
      if (pNext->type != PH_EXIT)
         PrintPronun(w, pNode->next[i], sBuf, pDesc, sSeparator, bEnd && (i==pNode->numnext-1), fp);
   }

}  /* PrintPronun */
#endif

#ifdef DEBUG_WORD
void printWord(wordTPtr w, DescPtr pDesc)
{
  SDWORD i, j;
  char *sPart=NULL, *sType=NULL;
  wstateTPtr pNode;

  /* Print word name */
  FNX_PRINTF("%s\n", w->name);

  /* Print list of initial node indices */
  FNX_PRINTF("  init: ");
  for (i=0; i<w->numinit; i++)
  {
     FNX_PRINTF(" %d", w->initnodes[i]);
     if (i<w->numinit-1)
        FNX_PRINTF(",");
  }
  FNX_PRINTF("\n");
  
  /* Print list of final node indices */
  FNX_PRINTF("  final: ");
  for (i=0; i<w->numfinal; i++)
  {
     FNX_PRINTF(" %d", w->finalnodes[i]);
     if (i<w->numfinal-1)
        FNX_PRINTF(",");
  }
  FNX_PRINTF("\n");

  /* Print the information about each node:
     Print the ID#, the name, the category#, the min & max duration,
     the part (left/right/center/triphone), the type (enter/exit/init/normal/final/initfinal?),
     the stress level (usually 0), and the list of previous and next nodes. */
  FNX_PRINTF("  ID: Name    Cat (Name)  Min/MaxDur Part   Type   Stress; Prev/Next\n"); 
  for(i=0; i<w->numnodes; i++) 
  {
     pNode = &(w->nodes[i]);
     switch(pNode->part)
     {
        case LEFT_DEPENDENT:      sPart = "Left";   break;
        case RIGHT_DEPENDENT:     sPart = "Right";  break;
        case CONTEXT_INDEPENDENT: sPart = "Center"; break;
        case TRIPHONE:            sPart = "Triphn"; break;
        default:                  sPart = "<Error>"; break;
     }
     switch(pNode->type)
     {
        case PH_ENTER:    sType = "Enter";  break;
        case PH_EXIT:     sType = "Exit";   break;
        case PH_INIT:     sType = "Init";   break;
        case PH_NORMAL:   sType = "Normal"; break;
        case PH_FINAL:    sType = "Final";  break;
        case PH_INITFINAL:sType = "Init/Fin"; break;
        default:          sType = "<Error>"; break;
     }
     FNX_PRINTF("  %2ld: %-7s %3d %-7s %3d/%-6d %-6s %-6s %d; ", 
        i, pNode->phoneme, pNode->cat, pDesc ? pDesc->pCategories[pNode->cat].sName : "",
        pNode->mindur, pNode->maxdur, sPart, sType, pNode->stress);
     /* print list of previous and next nodes */
     if (pNode->numprev>0)
     {
        FNX_PRINTF("Prev:");
        for (j=0; j<pNode->numprev; j++)
        {
           FNX_PRINTF(" %d", pNode->prev[j]);
           if (j<pNode->numprev-1)
              FNX_PRINTF(",");
        }
        FNX_PRINTF("; ");
     }
     if (pNode->numnext>0)
     {
        FNX_PRINTF("Next:");
        for (j=0; j<pNode->numnext; j++)
        {
           FNX_PRINTF(" %d", pNode->next[j]);
           if (j<pNode->numnext-1)
              FNX_PRINTF(",");
        }
     }
     FNX_PRINTF("\n");
  }
  /* Print pronunciations */
  for (i=0; i<w->numinit; i++)
  {
     /* Print all pronunciations beginning with this initial node. */
     PrintPronun(w, w->initnodes[i], " ", pDesc, ", ", i==w->numinit-1, stdout);
  }
}  /* printWord */
#endif

#if 0 // used occasionally for debugging purposes? Otherwise delete.
static void dumpWord(wordTPtr w, DescPtr pDesc) 
{
  SDWORD i, j;

  for(i=0; i<w->numnodes; i++) {
    FNX_PRINTF("%s\n", pDesc->pCategories[w->nodes[i].cat].sName);
    for(j=0; j<w->nodes[i].numnext; j++) {
      FNX_PRINTF("  %s\n", pDesc->pCategories[w->nodes[w->nodes[i].next[j]].cat].sName);
    }
  }
}
#endif

