/*C_HEADER_FILE****************************************************************
FILE        :  network.c
DESC        :  
TABS        :  3
OWNER       :  Fonix
DATE CREATED:  

(C) Copyright 1999,2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/22/05 11:09a $
  $Revision: 7 $

*END_HEADER*******************************************************************/
#include "FnxPlatform.h"
#include "DTFnxStdlib.h"
#include "FnxAllocate.h"
//#include "FnxOutput.h"
#include "FnxNetwork.h"
#include "FnxNames.h" // for PrintNodePronun to work...
#include "FnxLlist.h"

/*FUNCTION_HEADER*******************
 * NAME:    ;InsertList
 * DESC:    Insert one list in front of another one.
 * IN:      ppList - Address of the pointer to the head of the original list.
            pPreList - Pointer to the first node in a list of nodes to be inserted before *ppList.
 * OUT:     *ppList points to the new head of the list which contains all of the
               nodes in pPreList, followed by the nodes in *ppList.
 * RETURN:  n/a.
 * NOTES:   Handles Null *ppList or pPreList, but requires the **ppList is non-null.
            Should be called as InsertList(&pOriginalList, pListToInsert).  Both lists
              can be null, but &pOriginalList should point to a variable.
            Traverses pPreList, so if you're combining two lists, make sure pPreList
              is the shorter one if possible.
 *END_HEADER***************************/
void InsertList(llistPtr *ppList, llistPtr pPreList)
{
   llistPtr pLink, pLast;

   FNX_ASSERT(ppList);

   /* Don't alter *ppList if there is nothing in pPreList */
   if (!pPreList)
      return;
   /* Find the last element in pPreList */
   for (pLast=pLink=pPreList; pLink; pLink=pLink->pNext)
      pLast = pLink;
   FNX_ASSERT(pLast);
   /* Point the 'next' field of the last node in pPreList
      to the head of the original list. */
   pLast->pNext = *ppList;
   /* Point the head of the original list to the head
      of the new list. */
   *ppList = pPreList;
}  /* InsertList */

/*FUNCTION_HEADER**********************
 * NAME:    ;GetToken      
 * DESC:    Read the next token from the buffer of a parser.
 * IN:      pParser - Parser to update and extract a token from.
            sDelim  - String containing delimeter characters used to break up tokens.
 * OUT:     IF pParser->sBuffer is non-NULL, then:
              pParser->sBuffer is used for extracting the next token, and
              pParser->iPos is incremented to point just beyond the next token,
            ELSE pParser->fp is used for extracting the next token, and
              is advanced to just beyond the extracted token.
            pParser->iToken is set to the value of the next token, and
            pParser->sToken contains the name of the next token.
 * RETURN:  Tag of the next token (which is the same as the value placed in pParser->iToken)
 * NOTES:   Any character preceded by '\' will be "escaped" and not treated as a delimiter.
            (To use the '\' character itself, you would need to escape it by putting it twice).
            Returns 0 if the end of the buffer was reached (i.e., no token).
            Returns the ASCII value of a delimiter, if a delimeter was found.
            Returns the constant PHONEME (259) otherwise.
            If pParser->bUseToken is TRUE, then the token is read from pParser->sToken
              instead of reading the next one.  ->iToken is still updated.
 *END_HEADER***************************/
SDWORD GetToken(ParserPtr pParser, char *sDelim)
{
   SDWORD iLen; /* Length of the extracted token */

   /** Read the next string from the string buffer or file */
   if (pParser->bUseToken)
   {
      Strip(pParser->sToken);
      /* Using the string in "sToken" instead of reading from sBuffer or fp. */
      pParser->bUseToken=FALSE; /* Clear flag */
      iLen = FNX_STRLEN(pParser->sToken);
      if (iLen<1) /* For some reason sToken is empty, so read the next token the regular way. */
         return GetToken(pParser, sDelim);
   }
   else if (pParser->sBuffer)
   {
      pParser->iPos += ExtractField(pParser->sToken, sDelim, &pParser->sBuffer[pParser->iPos]);
      iLen = FNX_STRLEN(pParser->sToken);
   }
   else if (pParser->fp)
      iLen = ReadField(pParser->sToken, sDelim, pParser->fp);
   else /* Both sBuffer and fp were NULL, which is a no-no. */
   {
      Message(FNX_STDERR,"Error: Need to have a non-null string or file pointer to parse a word\n");
      return 0;
   }
   
   /** Decide what kind of token we parsed */
   if (iLen==1 && CharInString(pParser->sToken[0], sDelim))
      pParser->iToken = pParser->sToken[0]; /* Extracted a delimiter, so return it. */
   else if (iLen==0)
      pParser->iToken = 0; /* End of string */
   else pParser->iToken = LITERAL_TAG;

   return pParser->iToken;
}  /* GetToken */

/*FUNCTION_HEADER*******************
 * NAME:    ;FreeNode
 * DESC:    Free a Node structure and all of its fields.
 * IN:      pNode - Node to be freed.
 * OUT:     pNode and all of its linked lists and its name are all freed.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
void FreeNode(NodePtr pNode, LinkPoolPtr pLinkPool)
{
   if (!pNode)
      return;
   /* Free the fields of the node */
   if (pNode->pPrev)
      FreeList(&(pNode->pPrev), pLinkPool);
   if (pNode->pNext)
      FreeList(&(pNode->pNext), pLinkPool);
   if (pNode->sName)
      FNX_FREE(pNode->sName);
   if (pNode->sExternal)
      FNX_FREE(pNode->sExternal);
   /* Free up the nodes in the "pMore" list, along with the links in the list. */
   if (pNode->pMore)
   {
      llistPtr pLink;
      NodePtr  pMoreNode;
      for (pLink=pNode->pMore; pLink; pLink = pLink->pNext)
      {
         /* Get a pointer to the node pointed to by the current link */
         pMoreNode = (NodePtr) pLink->p;
         /* Free up the node in the more list. */
         if (pMoreNode)
            FreeNode(pMoreNode, pLinkPool);
      }
      /* Free up the links in the list */
      FreeList(&(pNode->pMore), pLinkPool);
   }  /* if pMore */

   /* Now free the node itself */
   FNX_FREE(pNode);         
}  /* FreeNode */

/*FUNCTION_HEADER*******************
 * NAME:    ;FreeNetwork
 * DESC:    Free a Network structure and all of its fields.
 * IN:      pNet - Network to be freed.
 * OUT:     All of the nodes in pNet->pNodes are freed, all the links in pInit, pFinal and pNodes
             are freed, and pNet itself is freed.
 * RETURN:  n/a
 * NOTES:   Since there are sometimes subnetworks that are freed up, and we
              often want to use a single linked list pool for all networks,
              pNode->pLinkPool is NOT free'd up.  Make sure that whoever created
              pLinkPool and passed it to pNet calls FreeLinkPool(pLinkPool) at some point.
 *END_HEADER***************************/
void FreeNetwork(NetworkPtr pNet)
{
   llistPtr pLink;
   NodePtr pNode;

   if (!pNet)
      return;
   for (pLink=pNet->pNodes; pLink; pLink=pLink->pNext)
   {
      /* Free current node */
      pNode = (NodePtr) pLink->p;
      if (pNode)
      {
         FreeNode(pNode, pNet->pLinkPool);
      }
   }  /* for pLink */
   if (pNet->pNodes)
      FreeList(&(pNet->pNodes), pNet->pLinkPool);
   if (pNet->pInit)
      FreeList(&(pNet->pInit), pNet->pLinkPool);
   if (pNet->pFinal)
      FreeList(&(pNet->pFinal), pNet->pLinkPool);
   if (pNet->sName)
      FNX_FREE(pNet->sName);
   FNX_FREE(pNet);
}  /* FreeNetwork */

/*FUNCTION_HEADER*******************
 * NAME:    ;AppendNet
 * DESC:    Append a subnetwork to another network, and free up the subnetwork.
 * IN:      pNet - Network to be appended to.
            pSubNet - Network to append to pNet.
 * OUT:     pNet has pSubNet's nodes appended to it, and, if there are any nodes in pSubNet,
              pNet is set to not be optional.
            pSubNet is freed up, except for the parts that become part of pNet.
 * RETURN:  0 on success, -1 on error.
 * NOTES:   If pNet is empty (i.e., no nodes), then pSubNet is simply copied into pNet.
            If pSubNet is null or empty, then no change is made to pNet.
            Otherwise, there is at least one node in each of pNet and pSubNet, and:
              If pSubNet is optional, then pNet's final nodes include both its own plus pSubNet's.
              If pNet is optional, then pNet's initial nodes include both its own plus pSubNet's.
 *END_HEADER***************************/
SDWORD AppendNet(NetworkPtr pNet, NetworkPtr pSubNet)
{
   llistPtr pInit, pFinal;
   NodePtr pInitNode, pFinalNode;

   if (!pSubNet || !pSubNet->pNodes)
      return 0; /* Nothing to do, so just return */
   if (!pNet)
   {
      Message(FNX_STDERR,"Null network in AppendNet()\n");
      return -1;
   }
   // Either both networks should be grammar networks (in which case bMergeNodes==TRUE),
   //   or they should both be pronunciation networks (in which case bMergeNodes==FALSE).
   FNX_ASSERT(pNet->bMergeNodes == pSubNet->bMergeNodes);
   if (!pNet->pNodes)
   {
      /* The original net is empty, so simply copy all the pointers over
         from the subnet and return. */
      memcpy(pNet, pSubNet, sizeof(Network));
      /* Free up the old structure */
      FNX_FREE(pSubNet);
      return 0;
   }

   /* (At this point pNet and pSubNet are non-NULL and both have at least one node) */

   /** Connect all of pNet's final nodes to all of pSubNet's initial nodes,
      and vice-versa. */
   for (pInit = pSubNet->pInit; pInit; pInit = pInit->pNext)
   {
      pInitNode = (NodePtr)pInit->p;
      for (pFinal = pNet->pFinal; pFinal; pFinal = pFinal->pNext)
      {
         /* Insert the current initial node of the subnet to the 'next' list
            of the current final node of the original net. */
         pFinalNode = (NodePtr)pFinal->p;
         InsertLink(pInitNode, &(pFinalNode->pNext), pNet->pLinkPool);
         /* Insert the current final node of the original net to the 'prev' list
            of the current initial node of the subnet. */
         InsertLink(pFinalNode, &(pInitNode->pPrev), pNet->pLinkPool);
      }  /* for pFinal */
   }  /* for pInit */

   /** Insert the list of nodes in the subnet into the beginning of the list of nodes in the net */
   InsertList(&pNet->pNodes, pSubNet->pNodes);

   /** Take care of the list of initial nodes */
   if (pNet->bOptional)
   {
      /* pNet was originally optional, so add all of the subnet's initial nodes
         to pNet's list of initial nodes. */
      InsertList(&pNet->pInit, pSubNet->pInit);
   }
   else 
   {
      /* pNet had at least one node and was not optional, so none of pSubNet's
         nodes will be initial nodes.  Thus, free the initial node linked list.*/
      FreeList(&(pSubNet->pInit), pNet->pLinkPool); /* Free links, but not nodes themselves */
   }

   /** Take care of the list of final nodes */
   if (pSubNet->bOptional)
   {
      /* The subnet is optional, so all of pNet's final nodes AND all of pSubNet's
         final nodes will be final nodes in the modified pNet.  Therefore,
         insert pSubNet's list of final nodes into pNet's list of final nodes. */
      InsertList(&pNet->pFinal, pSubNet->pFinal);
   }
   else
   {
      /* The subnet is not optional and has at least one node, so only pSubNet's
         final nodes will be final nodes in the modified pNet.  Therefore,
         replace pNet's list of final nodes with pSubNet's list. */
      FreeList(&(pNet->pFinal), pNet->pLinkPool); /* Free links, but not nodes themselves */
      pNet->pFinal = pSubNet->pFinal;
      /* Since the subnet was not optional and had at least one node, the
         resulting net is not optional. */
      pNet->bOptional = FALSE;
   }

   /* Free up the subnet structure, since its fields have all been used
      in pNet and/or free'd up. */
   FNX_FREE(pSubNet);

   return 0; /* ok */
}  /* AppendNet */

/*FUNCTION_HEADER*******************
 * NAME:    ;BaseNet
 * DESC:    Decide whether a network is a "base" network.
 * IN:      pNet - Network to be examined.
 * OUT:     n/a
 * RETURN:  TRUE if pNet is a base network, FALSE otherwise.
 * NOTES:   A network is a "base" network if:
              1) It has exactly one node,
              2) It does not repeat, i.e., its node has no prev or next pointers.
            A base network's single node may represent multiple nodes if its "pMore"
              field is used (as in grammar networks).
            A base network may or may not be optional, so you will have to
              check for that yourself.
 *END_HEADER***************************/
SWORD BaseNet(NetworkPtr pNet)
{
   NodePtr pNode;
   /* Make sure the network exists and has exactly one node. */
   if (pNet && pNet->pNodes && !pNet->pNodes->pNext)
   {
      /* Get a pointer to the only node in the network. */
      pNode = (NodePtr) pNet->pNodes->p;
      /* Make sure the node doesn't point back to itself (e.g., in a repeated network). */
      if (!pNode->pPrev && !pNode->pNext)
         return TRUE;
   }

   return FALSE;
}

/*FUNCTION_HEADER*******************
 * NAME:    ;OrNet
 * DESC:    Modify a network to go to itself OR a subnetwork.
 * IN:      pNet - Network to be modified, containing one alternative subnet.
            pSubNet - Network containing another alternative.
 * OUT:     pNet has pSubNet's nodes added to it, with links to allow traversal
              through either the original pNet's nodes OR through pSubNet's nodes.
            pSubNet is freed up, except for the parts that become part of pNet.
 * RETURN:  0 on success, -1 on error.
 * NOTES:   If pNet is empty (i.e., no nodes), then pSubNet is simply copied into pNet, but is made optional.
            If pSubNet is null or empty, then no change is made to pNet, except that it is made optional.
            Otherwise, there is at least one node in each of pNet and pSubNet, so pNet
              will be optional only if either the original pNet or pSubNet was optional.
            If pNet and pSubNet both have their bBaseNet flag set to TRUE,
              then pNet will still have only a SINGLE NODE, and pSubNet's single
              node will be added to pNet's node's "pMore" list.
 *END_HEADER***************************/
SDWORD OrNet(NetworkPtr pNet, NetworkPtr pSubNet)
{
   NodePtr pNode, pSubNode;

   if (!pNet)
   {
      Message(FNX_STDERR,"Null network in AppendNet()\n");
      return -1;
   }
   if (!pSubNet || !pSubNet->pNodes)
   {
      pNet->bOptional = TRUE;
      return 0; /* Nothing else to do, so just return */
   }
   if (!pNet->pNodes)
   {
      /* The original net is empty, so simply copy all the pointers over
         from the subnet and return. */
      memcpy(pNet, pSubNet, sizeof(Network));
      /* Free up the old structure */
      FNX_FREE(pSubNet);
      /* Set to optional, since we have a network that is <subnet> OR <nothing> */
      pNet->bOptional = TRUE;
      return 0;
   }

   /* (At this point pNet and pSubNet are non-NULL and both have at least one node) */

   /* See if we are allowing nodes to be merged, and if so, see if we have two
      base networks that can have their node merged into one. 
      Make sure that neither is optional or both are optional, but not a mix. 
      (We MIGHT want to just make sure neither is optional before allowing a merge). */
   if (pNet->bMergeNodes && BaseNet(pNet) && BaseNet(pSubNet) && pNet->bOptional==pSubNet->bOptional)
   {
      pNode = (NodePtr) pNet->pNodes->p;
      pSubNode = (NodePtr) pSubNet->pNodes->p;
      FNX_ASSERT(pNode && pSubNode);
      if (pNet->pNodes->pNext || pSubNet->pNodes->pNext || 
          pNode->pNext || pNode->pPrev || pSubNode->pNext || pSubNode->pPrev)
      {
         Message(FNX_STDERR,"Error: A basenet has multiple nodes in OrNet().\n");
         return -1;
      }
      /* Both networks contain only a single node, so merge subnet's node
         into pNet's node using the "pMore" linked list.  Used by grammar
         networks to use a single node to represent a list of alternate words. */
      /* First insert any nodes in the subnet node's "more" list into the net node's "more" list. */
      if (pSubNode->pMore)
      {
         InsertList(&pNode->pMore, pSubNode->pMore);
         pSubNode->pMore=NULL;
      }
      /* Then insert the subnet's node itself into the net node's "more" list */
      InsertLink(pSubNode, &(pNode->pMore), pNet->pLinkPool);
      /* Now free up pSubNet */
      FreeList(&(pSubNet->pNodes), pNet->pLinkPool); /* Free link pointing at the node we moved over to pNet's node */
      pSubNet->pNodes = NULL;
      FreeNetwork(pSubNet); /* Free up everything else in pSubNet, since we aren't using any of it. */
   }
   else
   {
      /* If either of the original networks is optional, then the resulting network
         is also optional.  (If pNet is optional, however, we don't need to change anything). */
      if (pSubNet->bOptional)
         pNet->bOptional = TRUE;

      /** Insert the list of nodes in the subnet into the beginning of the list of nodes in the net */
      InsertList(&pNet->pNodes, pSubNet->pNodes);

      /** Take care of the list of final nodes.  Since we are "or"-ing the two networks,
          the new list of final nodes will be the union of the original two lists. */
      InsertList(&pNet->pFinal, pSubNet->pFinal);

      /** Take care of the list of initial nodes.  Since we are "or"-ing the two networks,
          the new list of initial nodes will be the union of the original two lists. */
      InsertList(&pNet->pInit, pSubNet->pInit);

      /* Free up the subnet structure, since its fields have all been used in pNet. */
      FNX_FREE(pSubNet);
   }
   return 0; /* ok */
}  /* OrNet */


/*FUNCTION_HEADER*******************
 * NAME:    ;AppendNode
 * DESC:    Append a Node structure to the end of a Net structure.
 * IN:      pNet  - Net to add the node to.
            pNode - (Phone) node to add to a (phone graph) network.
 * OUT:     pNode is appended to pNet, and pNet is set to not be optional.
 * RETURN:  0 on success, -1 on error.
 * NOTES:   All final nodes in the network point to the new node, which becomes
              the only final node in the modified network.
            If the network was previously empty or optional, then the new node
              is also added to the network's list of initial nodes.
            The network pNet is no longer optional, since the appended node was not.
 *END_HEADER***************************/
SDWORD AppendNode(NetworkPtr pNet, NodePtr pNode)
{
   llistPtr pLink;
   NodePtr pFinalNode;

   if (!pNode || !pNet)
   {
      Message(FNX_STDERR,"Error: Null network in AppendNode\n");
      return -1;
   }
   /* Insert node into initial list, if the network was empty or flagged as optional */
   if (pNet->bOptional || !pNet->pInit)
      InsertLink(pNode, &(pNet->pInit), pNet->pLinkPool);

   /* Insert the node into the network's linked list of all of its nodes */
   InsertLink(pNode, &(pNet->pNodes), pNet->pLinkPool);

   /* Point all final nodes in the net (if any) at pNode and vice-versa */
   for (pLink=pNet->pFinal; pLink; pLink=pLink->pNext)
   {
      /* Add the new node (pNode) to the final node's list of next nodes */
      pFinalNode = (NodePtr)pLink->p;
      InsertLink(pNode, &(pFinalNode->pNext), pNet->pLinkPool);
      /* Add the final node to the new node's list of previous nodes */
      InsertLink(pFinalNode, &(pNode->pPrev), pNet->pLinkPool);
   }

   /* Replace the old final list with a list containing only the new node */
   if (pNet->pFinal)
      FreeList(&(pNet->pFinal), pNet->pLinkPool);
   pNet->pFinal=NULL; // redundant? 
   InsertLink(pNode, &(pNet->pFinal), pNet->pLinkPool);

   /* The network is no longer optional, since the newly-added node is not optional. */
   pNet->bOptional = FALSE;

   return 0;
}  /* AppendNode */

/*FUNCTION_HEADER*******************
 * NAME:    ;RepeatNet
 * DESC:    Make a network "repeatable" by connecting its initial and final nodes.
 * IN:      pNet - Network to be modified.
 * OUT:     pNet becomes "repeatable" (see notes).
 * RETURN:  0 on success, -1 on error.
 * NOTES:   If pNet is empty or null, no change is made.
            All final nodes add all initial nodes to their "next" list, and
            All initial nodes add all final nodes to their "next" list.
 *END_HEADER***************************/
SDWORD RepeatNet(NetworkPtr pNet)
{
   llistPtr pInit, pFinal;
   NodePtr pInitNode, pFinalNode;

   if (!pNet || !pNet->pNodes)
      return 0;

   /** Connect all of pNet's final nodes to all of its initial nodes,
      and vice-versa. */
   for (pInit = pNet->pInit; pInit; pInit = pInit->pNext)
   {
      pInitNode = (NodePtr)pInit->p;
      for (pFinal = pNet->pFinal; pFinal; pFinal = pFinal->pNext)
      {
         pFinalNode = (NodePtr)pFinal->p;
         /* Insert the current initial node into the 'next' list
            of the current final node. */
         InsertLink(pInitNode, &(pFinalNode->pNext), pNet->pLinkPool);
         /* Insert the current final node into the 'prev' list
            of the current initial node. */
         InsertLink(pFinalNode, &(pInitNode->pPrev), pNet->pLinkPool);
      }  /* for pFinal */
   }  /* for pInit */

   return 0; /* ok */
}  /* RepeatNet */

/*FUNCTION_HEADER*******************
 * NAME:    ;CopyNodeList
 * DESC:    Make a copy of a linked list, substituting pointers into one array of nodes
              with pointers into another array of nodes.
 * IN:      pList - Original linked list of nodes to copy.
            ppNodes - Array of original nodes pointed to by links in pList.
            ppNodesCopy - Array of new nodes (corresponding to the nodes in ppNodes)
                          that the copy of pList will point to.
 * OUT:     A copy of the pList is created, with all links pointing into ppNodesCopy[]
              instead of ppNodes[].
 * RETURN:  Pointer to newly-created list.
 * NOTES:   The iID field of the nodes in ppNodes[] (and pointed to by the links in pList)
              must be set to the index in ppNodes[] of each node, since that is what
              is used to decide where in ppNodesCopy[] to point each new link.
            The links in pList are assumed to point only to elements in ppNodes[].
            ppNodes[] and ppNodesCopy[] are assumed to be allocated to the same size
              and to be large enough to include all the links in pList.
            If any nodes pointed to by the links in pList have an iID field larger
              than ppNodes[] is allocated to, you will have bogus pointers.
 *END_HEADER***************************/
LLIST *CopyNodeList(LLIST *pList, NodePtr *ppNodes, NodePtr *ppNodesCopy, LinkPoolPtr pLinkPool)
{
   LLIST *pLink; /* Current link in the original list pList */
   LLIST *pHead; /* Pointer to the first link in the new list to be returned */
   LLIST *pCopy; /* Pointer to the current link in the new list */
   LLIST *pLast; /* Pointer to the previous link in the new list */
   NodePtr pNode; /* Pointer to the current node in pList */
   SDWORD  iNode; /* Index in ppNodes[] of pNode (and thus the 
                     index in ppNodesCopy[] of the node to go into the new list)*/
   
   /* Visit each node in pList */
   pLast = pHead = NULL;
   for (pLink=pList; pLink; pLink=pLink->pNext)
   {
      /* Get a pointer to the current node in pList */
      pNode = (NodePtr) pLink->p;
      /* Get the index of pNode in ppNodes[] */
      iNode = pNode->iID;
      /* Create a new link for the new list, and point it at the same index
         in ppNodesCopy[] as pNode was in ppNodes[]. */
      pCopy = NULL; /* Make sure the "next" pointer will be NULL in the new link */
      InsertLink(ppNodesCopy[iNode], &pCopy, pLinkPool);
      /* Point the previous new link to this one, unless there was no
         previous link, in which case this is the first link in the new
         list, so assign the head to this link. */
      if (pLast)
         pLast->pNext = pCopy;
      else pHead = pCopy;
      /* Remember the address of the previous link in the new list. */
      pLast = pCopy;
   }  /* for pLink */

   /* Return a pointer to the head of the newly-created linked list */
   return pHead;
}  /* CopyNodeList */

/*FUNCTION_HEADER*******************
 * NAME:    ;CopyNet
 * DESC:    Make a copy of a network.
 * IN:      pNet - Network to be copied.
 * OUT:     A copy of the network is allocated and created.
 * RETURN:  Pointer to newly-allocated network.  NULL on error.
 * NOTES:   
 *END_HEADER***************************/
NetworkPtr CopyNet(NetworkPtr pNet)
{
   NetworkPtr pCopy;
   SDWORD nNodes;
   NodePtr *ppNodes, *ppNodesCopy, pNode, pNodeCopy;
   int i;
   llistPtr pLink;

   /* Find out how many nodes are in pNet */
   nNodes = ListSize(pNet->pNodes);
   /* Make an array of the nodes. */
   ppNodes = (NodePtr *) FNX_CALLOC(nNodes, sizeof(NodePtr));
   /* Set the ID# of each node so that we can tell which
      node all of the various pointers are pointing at. */
   for (i=0, pLink=pNet->pNodes; pLink; pLink = pLink->pNext, i++)
   {
      ppNodes[i] = (NodePtr) pLink->p;
      ppNodes[i]->iID = i;
   }
   /* Allocate a new network. */
   pCopy              = (NetworkPtr) FNX_CALLOC(1, sizeof(Network));
   pCopy->bOptional   = pNet->bOptional;
   pCopy->bMergeNodes = pNet->bMergeNodes;
   pCopy->pLinkPool       = pNet->pLinkPool;
   
   /* Allocate a new array of pointers to newly-allocated nodes */
   ppNodesCopy        = (NodePtr *) FNX_CALLOC(nNodes, sizeof(NodePtr));
   for (i=0; i<nNodes; i++)
      ppNodesCopy[i] = (NodePtr) FNX_CALLOC(1, sizeof(Node));

   /* Create new initial and final linked lists, pointing at the
      nodes in ppNodesCopy[] instead of ppNodes[]. */
   pCopy->pInit  = CopyNodeList(pNet->pInit, ppNodes, ppNodesCopy, pNet->pLinkPool);
   pCopy->pFinal = CopyNodeList(pNet->pFinal, ppNodes, ppNodesCopy, pNet->pLinkPool);

   /* Create a new linked list of the new nodes */
   pCopy->pNodes = CopyNodeList(pNet->pNodes, ppNodes, ppNodesCopy, pNet->pLinkPool);

   /* Fill in the new node structures */
   for (i=0; i<nNodes; i++)
   {
      pNode     = ppNodes[i];
      pNodeCopy = ppNodesCopy[i];
      pNodeCopy->pPrev      = CopyNodeList(pNode->pPrev, ppNodes, ppNodesCopy, pNet->pLinkPool);
      pNodeCopy->pNext      = CopyNodeList(pNode->pNext, ppNodes, ppNodesCopy, pNet->pLinkPool);
      pNodeCopy->sName = pNode->sName ? FNX_STRDUP(pNode->sName) : NULL;
      pNodeCopy->sExternal  = pNode->sExternal  ? FNX_STRDUP(pNode->sExternal)  : NULL;
      /* Don't bother copying this information over, because it is not needed.
         It is included here in comments only for completeness so that we
         know that we didn't overlook it, or in case it is needed in the future. */
      //pNodeCopy->iStress = pNode->iStress; // Not done because CopyNet() is not used by word parser,
      //                                     // and iStress is not used by grammar.
      //pNodeCopy->iID     = pNode->iID;     // Not done because iID, bInit and bFinal are all set when needed
      //pNodeCopy->bInit   = pNode->bInit;
      //pNodeCopy->bFinal  = pNode->bFinal;
      if (pNet->bMergeNodes && pNode->pMore)
      {
         LLIST *pLink; /* Current link in the original list pNode->pMore */
         LLIST *pCopy; /* Pointer to the current link in the new list */
         LLIST *pLast; /* Pointer to the previous link in the new list */
         NodePtr pMoreNode; /* Pointer to the current node in pNode->pMore */
         NodePtr pMoreCopy; /* Pointer to the new copy of pMoreNode */
                              
         /* Visit each node in pNode->pMore */
         pLast = pNodeCopy->pMore = NULL;
         for (pLink=pNode->pMore; pLink; pLink=pLink->pNext)
         {
            /* Get a pointer to the current node in pNode->pMore */
            pMoreNode = (NodePtr) pLink->p;

            /* Allocate a new node, and copy the internal & external word names from the old link. */
            /* (None of the other fields matter in a "more" list, so leave them empty) */
            pMoreCopy = (NodePtr) FNX_CALLOC(1, sizeof(Node));
            if (pMoreNode->sName)
               pMoreCopy->sName = FNX_STRDUP(pMoreNode->sName);
            if (pMoreNode->sExternal)
               pMoreCopy->sExternal = FNX_STRDUP(pMoreNode->sExternal);

            /* Create a new link for the new list, and point it at the
               newly-allocated node. */
            pCopy = NULL;
            InsertLink(pMoreCopy, &pCopy, pNet->pLinkPool);

            /* Point the previous new link to this one, unless there was no
               previous link, in which case this is the first link in the new
               list, so assign pNodeCopy->pMore to this link. */
            if (pLast)
               pLast->pNext = pCopy;
            else pNodeCopy->pMore = pCopy;

            /* Remember the address of the previous link in the new list. */
            pLast = pCopy;
         }  /* for pLink */
      }  /* if copying pMore list */
   }  /* for i */
   /* Free up the temporary arrays of pointers that pointed to the nodes
      that are now in pNet and pCopy */
   if (ppNodes)
      FNX_FREE(ppNodes);
   if (ppNodesCopy)
      FNX_FREE(ppNodesCopy);
   return pCopy;
}  /* CopyNet */

/*FUNCTION_HEADER*******************
 * NAME:    ;InList
 * DESC:    Decide whether a pointer is in a linked list of pointers.
 * IN:      p     - Pointer to find.
            pList - List to look in.
 * OUT:     n/a
 * RETURN:  TRUE if p is in pList.  FALSE otherwise.
 * NOTES:   
 *END_HEADER***************************/
BOOL InList(void *p, llistPtr pList)
{
   llistPtr pLink;
   for (pLink = pList; pLink; pLink=pLink->pNext)
   {
      if (pLink->p == p)
         return TRUE;
   }
   return FALSE; /* Didn't find it */
}  /* InList */

/*FUNCTION_HEADER*******************
 * NAME:    ;AddLink
 * DESC:    Add a pointer to the beginning of a linked list UNLESS it is already there.
 * IN:      p - Pointer to add.
            ppList - Address of pointer to head of list.
 * OUT:     *ppList points to a new link which points to p and the old *ppList,
              unless p is already in the list, in which case nothing changes.
 * RETURN:  TRUE if p is added to the list.  FALSE otherwise.
 * NOTES:   Called as AddLink(p, &pList).  Not as efficient as InsertLink(p,&pList, pLinkPool),
              because it has to traverse the list once to make sure there is no duplicate.
 *END_HEADER***************************/
BOOL AddLink(void *p, llistPtr *ppList, LinkPoolPtr pLinkPool)
{
   llistPtr pLink;
   if (!ppList) /* Check for bogus input */
      return FALSE;
   /* See if p is in the list (could do "if (InList(p,*ppList)) return FALSE;"
      but this avoids an additional function call). */
   for (pLink=*ppList; pLink; pLink = pLink->pNext)
   {
      if (pLink->p == p)
         return FALSE; /* Found p in list, so return without changing anything */
   }
   InsertLink(p, ppList, pLinkPool); /* p not yet in list, so insert it at the beginning */
   return TRUE; /* Added p to the list */
}  /* AddLink */

/*FUNCTION_HEADER*******************
 * NAME:    ;SameNodeInfo
 * DESC:    Decide whether two lists contain the same set of pointers.
 * IN:      pList1 - First list of pointers
            pList2 - Second list of pointers
            bFlag1 - First flag
            bFlag2 - Second flag
 * OUT:     n/a
 * RETURN:  TRUE if bFlag1==bFlag2 and every pointer in pList1 is in pList2 and
              every pointer in pList2 is in pList1.  FALSE otherwise.
 * NOTES:   The flags are used to make it easier to compare bInit or bFinal
              flags, since these are implicitly part of the lists we are
              trying to compare.  If you need to compare two lists and
              don't want to bother with the flags, just pass in two of
              the same value (e.g., "SameLists(pList1, pList2, TRUE, TRUE)").
 *END_HEADER***************************/
BOOL SameNodeInfo(NodePtr pNode1, NodePtr pNode2)
{
   if (pNode1->iCat == pNode2->iCat)
   {
      /* Category indices are the same.  But perhaps neither
         was set (i.e., if this network is not yet "expanded"),
         so compare the names, too. */
      if ((pNode1->sName==pNode2->sName) /* both the same pointer (perhaps null), so equal */ 
          || (pNode1->sName && pNode2->sName && FNX_STRCMP(pNode1->sName,pNode2->sName)==0) )
      {
         /* Either both names are NULL or both contain the same string,
            so these nodes contain the same info. */
         return TRUE;
      }
   }
   return FALSE;
}  /* SameNodeInfo */
         
/*FUNCTION_HEADER*******************
 * NAME:    ;SameNodeLists
 * DESC:    Decide whether two lists contain the same set of pointers.
 * IN:      pList1 - First list of pointers
            pList2 - Second list of pointers
            bFlag1 - First flag
            bFlag2 - Second flag
 * OUT:     n/a
 * RETURN:  TRUE if bFlag1==bFlag2 and every pointer in pList1 is in pList2 and
              every pointer in pList2 is in pList1.  FALSE otherwise.
 * NOTES:   The flags are used to make it easier to compare bInit or bFinal
              flags, since these are implicitly part of the lists we are
              trying to compare.  If you need to compare two lists and
              don't want to bother with the flags, just pass in two of
              the same value (e.g., "SameLists(pList1, pList2, TRUE, TRUE)").
 *END_HEADER***************************/
BOOL SameNodeLists(llistPtr pList1, llistPtr pList2, BOOL bFlag1, BOOL bFlag2)
{
   llistPtr pLink;

   if (bFlag1 != bFlag2)
      return FALSE; /* Different flags, so the "lists" are different. */
   for (pLink=pList1; pLink; pLink=pLink->pNext)
   {
      /* Make sure pLink1's pointer occurs in pList2 */
      if (!InList(pLink->p, pList2))
         return FALSE;
   }
   for (pLink=pList2; pLink; pLink=pLink->pNext)
   {
      /* Make sure pLink1's pointer occurs in pList2 */
      if (!InList(pLink->p, pList1))
         return FALSE;
   }
   return TRUE; /* No differences found, so the lists are the same */
}  /* SameNodeLists */

#if 0 // debug/dumping code
/*FUNCTION_HEADER**********************
   NAME:    ;PrintNodePronun
   DESC:    Print all of the possible pronunciations of a word.
   IN:      w - Word to print
            iNode   - Node to start with
            sPrefix - Pronunciation so far (from nodes preceding iNode)
            pDesc   - Description of model names (NULL=>use .phoneme field of each node)
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
static void PrintNodePronun(NodePtr pNode, char *sPrefix, DescPtr pDesc,
                            char *sSeparator, BOOL bEnd, FILE *fp)
{
   char sBuf[200]; /* Current pronunciation being built */
   NodePtr pNext;
   llistPtr pLink;

   if (!fp)
      fp=stdout;
   /* Add the current node's category name to the string */
   if (pDesc)
      FNX_SPRINTF(sBuf, "%s %s", sPrefix, pDesc->pCategories[pNode->iCat].sName);
   else FNX_SPRINTF(sBuf, "%s %s", sPrefix, pNode->sName);

   /* Print the word if this is a final node */
   if (pNode->bFinal)
   {
      /* Print the pronunciation to fp, followed by the separator (unless this is at the end) */
      if (bEnd && !pNode->pNext)
         FNX_FPRINTF(fp, "%s",sBuf);
      else FNX_FPRINTF(fp, "%s%s", sBuf, sSeparator);
   }
   /* Recurse on all following nodes (except for exit nodes) */
   for (pLink = pNode->pNext; pLink; pLink = pLink->pNext)
   {
      pNext = (NodePtr)pLink->p;
      PrintNodePronun(pNext, sBuf, pDesc, sSeparator, bEnd && !pNode->pNext, fp);
   }
}  /* PrintNodePronun */

/*FUNCTION_HEADER*******************
 * NAME:    ;DumpNodeList
 * DESC:    Dump the ID#'s (and names) of a list of nodes.
 * IN:      sIntro - String to be printed before the list (ignored if NULL)
            pList - A linked list of Node structures.
 * OUT:     The ID# and name of each node in pList is printed to stdout.
 * RETURN:  n/a
 * NOTES:   For use in debugging only.  Can be #if'ed out.
 *END_HEADER***************************/
static void DumpNodeList(char *sIntro, llistPtr pList, DescPtr pDesc)
{
   llistPtr pLink;
   NodePtr pNode;

   if (sIntro)
      FNX_PRINTF("%s", sIntro);

   if (pList)
   {
      for (pLink=pList; pLink; pLink = pLink->pNext)
      {
         pNode = pLink->p;
         FNX_PRINTF("%d", pNode->iID);
         if (pLink->pNext)
            FNX_PRINTF(", ");
      }
      FNX_PRINTF(" (");
      for (pLink=pList; pLink; pLink = pLink->pNext)
      {
         pNode = pLink->p;
         if (pDesc && pNode->iCat >= 0)
            FNX_PRINTF("%s", pDesc->pCategories[pNode->iCat].sName);
         else FNX_PRINTF("[%s]", pNode->sName ? pNode->sName : "<null>");
         if (pLink->pNext)
            FNX_PRINTF(", ");
      }
      FNX_PRINTF(")");
   }
   FNX_PRINTF("\n");
}


void DumpNetwork(NetworkPtr pNet, DescPtr pDesc)
{
  NodePtr pNode, pNode2;
  llistPtr pLink, pLink2;

  /* Print word name */
  if (pNet->sName)
     FNX_PRINTF("%s\n", pNet->sName);

  /* Print list of initial node indices */
  DumpNodeList("  init: ", pNet->pInit, pDesc);
  FNX_PRINTF("\n");
  
  /* Print list of final node indices */
  DumpNodeList("  final: ", pNet->pFinal, pDesc);
  FNX_PRINTF("\n");

  /* Print the information about each node:
     Print the ID#, the name, the category#, the min & max duration,
     the part (left/right/center/triphone), the type (enter/exit/init/normal/final/initfinal?),
     the stress level (usually 0), and the list of previous and next nodes. */
  FNX_PRINTF("  ID: Name    Cat (Name)  Init   Final;  Prev/Next\n"); 
  for(pLink=pNet->pNodes; pLink; pLink=pLink->pNext)
  {
     pNode = (NodePtr)pLink->p;
     FNX_PRINTF("  %2d: %-7s %3d %-7s %-6s %-6s; ", 
        pNode->iID, pNode->sName, pNode->iCat, pDesc ? pDesc->pCategories[pNode->iCat].sName : "",
        pNode->bInit ? "init" : "", pNode->bFinal ? "final" : "");
     /* print list of previous and next nodes */
     if (pNode->pPrev)
     {
        FNX_PRINTF("Prev:");
        for (pLink2=pNode->pPrev; pLink2; pLink2=pLink2->pNext)
        {
           pNode2 = (NodePtr)pLink2->p;
           FNX_PRINTF(" %d", pNode2->iID);
           if (pLink2->pNext)
              FNX_PRINTF(",");
        }
        FNX_PRINTF("; ");
     }
     if (pNode->pNext)
     {
        FNX_PRINTF("Next:");
        for (pLink2=pNode->pNext; pLink2; pLink2=pLink2->pNext)
        {
           pNode2 = (NodePtr)pLink2->p;
           FNX_PRINTF(" %d", pNode2->iID);
           if (pLink2->pNext)
              FNX_PRINTF(",");
        }
     }
     FNX_PRINTF("\n");
  }
  /* Print pronunciations */
  if (pDesc)
  {
     for (pLink=pNet->pInit; pLink; pLink=pLink->pNext)
     {
        /* Print all pronunciations beginning with this initial node. */
        PrintNodePronun((NodePtr)pLink->p, " ", pDesc, "\n ", !pLink->pNext, stdout);
     }
  }
}  /* DumpNetwork */

#include "FnxFileIO.h"

void DumpPronun(NetworkPtr pNet, DescPtr pDesc, char *sFilename)
{
   llistPtr pLink;
   FILE *fp;

   fp = FNX_FOPENWITHPATH(sFilename,"wt");
   for (pLink=pNet->pInit; pLink; pLink=pLink->pNext)
   {
      PrintNodePronun((NodePtr)pLink->p, " ", pDesc, "\n ", !pLink->pNext, fp);
   }
   FNX_FCLOSE(fp);
}

#endif // debug/dumping code


/*FUNCTION_HEADER*******************
 * NAME:    ;CombineNodes
 * DESC:    Combine two nodes.
 * IN:      pKeep   - Node to keep
            pDelete - Node to delete
            pNet    - Network to be updated.
 * OUT:     The links from pDelete are combined with pKeep; all links to pDelete
              in pNet are removed; pNet (i.e., ->pNodes, ->pInit, ->pFinal) is
              updated.
 * RETURN:  n/a
 * NOTES:   
 *END_HEADER***************************/
void CombineNodes(NodePtr pKeep, NodePtr pDelete, NetworkPtr pNet)
{
   llistPtr pLink;
   NodePtr pNeighbor;

   FNX_ASSERT(pKeep != pDelete);
   /* Handle pDelete's previous nodes. */
   for (pLink=pDelete->pPrev; pLink; pLink = pLink->pNext)
   {
      pNeighbor = (NodePtr)pLink->p;
      /* Remove pointer from preceding neighbor to pDelete */
      RemovePointerFromList(pDelete, &(pNeighbor->pNext), pNet->pLinkPool);
      /* Add link from pDelete into pKeep (unless already there) */
      if (AddLink(pNeighbor, &(pKeep->pPrev), pNet->pLinkPool))
      {
         /* pNeighbor was not already in pKeep's 'prev' list, so pKeep
            was thus not in pNeighbor's 'next' list.  So add it now. */
         AddLink(pKeep, &(pNeighbor->pNext), pNet->pLinkPool);
      }
   }  /* for each previous node of pDelete */

   /* Remove links to pDelete from following nodes. */
   for (pLink=pDelete->pNext; pLink; pLink = pLink->pNext)
   {
      pNeighbor = (NodePtr)pLink->p;
      /* Remove pointer from following neighbor to pDelete */
      RemovePointerFromList(pDelete, &(pNeighbor->pPrev), pNet->pLinkPool);
      /* Add link to pNeighbor into pKeep's "next" list (unless already there). */
      if (AddLink(pNeighbor, &(pKeep->pNext), pNet->pLinkPool))
      {
         /* pNeighbor did indeed have to be added to pKeep's "next" list,
            so we also need to add pKeep to pNeighbor's "prev" list. */
         AddLink(pKeep, &(pNeighbor->pPrev), pNet->pLinkPool);
      }
   }  /* for each following node of pDelete */

   /* Remove links to pDelete from initial node list. */
   if (pDelete->bInit)
      RemovePointerFromList(pDelete, &(pNet->pInit), pNet->pLinkPool);
   /* Remove links to pDelete from final node list. */
   if (pDelete->bFinal)
      RemovePointerFromList(pDelete, &(pNet->pFinal), pNet->pLinkPool);

   /* Add pKeep to initial list if necessary */
   if (pDelete->bInit && !pKeep->bInit)
   {
      pKeep->bInit = TRUE;
      InsertLink(pKeep, &(pNet->pInit), pNet->pLinkPool);
   }
   /* Add pKeep to final list if necessary */
   if (pDelete->bFinal && !pKeep->bFinal)
   {
      pKeep->bFinal = TRUE;
      InsertLink(pKeep, &(pNet->pFinal), pNet->pLinkPool);
   }
   /* Remove pDelete from the main list of nodes in pNet */
   RemovePointerFromList(pDelete, &(pNet->pNodes), pNet->pLinkPool);
   /* Delete the node itself */
   FreeNode(pDelete, pNet->pLinkPool);

}  /* CombineNodes */

/*FUNCTION_HEADER*******************
 * NAME:    ;CollapsePrevious
 * DESC:    Combine nodes with the same category and same set of previous nodes.
 * IN:      pList - List of nodes
            pNet - Network to be collapsed.
 * OUT:     Any redundant nodes in pList are combined, and pNet is modified accordingly.
 * RETURN:  TRUE if any nodes were combined.  FALSE otherwise.
 * NOTES:   In a pronunciation graph, any two nodes with the same category
              and the same set of previous nodes can be combined.
            There must not be cycles in the graph, or this routine could get
              in trouble (i.e., if one of the nodes deleted is the one whose
              'pPrev' list is passed in as pList to this routine).
            If there are no cycles in the graph, this routine should be fine,
              since only nodes in pList are possibly combined, and the original
              node is not in its own previous list.
 *END_HEADER***************************/
BOOL CollapsePrevious(llistPtr pList, NetworkPtr pNet)
{
   llistPtr pNodeLink, pNextLink;
   llistPtr pLastLink; /* Pointer to the link before pNextLink in pList. */
   BOOL bCombined; /* Flag for whether any nodes were combined. */
   NodePtr pNode, pNextNode;

   if (!pList || !pList->pNext)
      return FALSE; /* Not more than 1 element in the list => impossible to combine any */
   bCombined=FALSE;
   /* Go through each node in pList */
   for (pNodeLink = pList; pNodeLink; pNodeLink = pNodeLink->pNext)
   {
      /* Get a pointer to the current node. */
      pNode = (NodePtr) pNodeLink->p;
      /* Remember the last link before "pNextLink" so that if pNextLink
         and pNodeLink are merged, we can more easily delete pNextLink. */
      pLastLink = pNodeLink;
      /* Go through every link AFTER pNode's link in pList */
      for (pNextLink = pNodeLink->pNext; pNextLink; pNextLink = pNextLink->pNext)
      {
         pNextNode = (NodePtr) pNextLink->p;
         /* See if the two nodes have the same info and same list of previous nodes */
         if (SameNodeInfo(pNode, pNextNode) && pNode!=pNextNode && // make sure we don't merge a node with itself!
             SameNodeLists(pNode->pPrev, pNextNode->pPrev, pNode->bInit, pNextNode->bInit))
         {
            /* They do have the same list of following nodes,
               so COMBINE THE NODES. This is done by moving pNextNode's
               pointers into pNode and then deleting pNextNode from pNet. 
               Make sure pNode survives (and pNextNode is the one that is deleted)
               because our outer "for" loop needs to be able to continue. */
            CombineNodes(pNode, pNextNode, pNet);
            /* Set pNextLink back to pLastLink, since we deleted pNextLink and its
               node from pList inside of CombineNodes.  This allows us to continue
               along the same list without starting over.  (i.e., pLastLink->pNext
               is the next link we want during this loop). */
            pNextLink = pLastLink;
            /* Remember that we have combined nodes at least once. */
            bCombined = TRUE;
         }  /* Same info & previous lists */
      }  /* for each node after pNodeLink */
   }  /* for each node in pList*/
   return bCombined;
}  /* CollapsePrevious */

/*FUNCTION_HEADER*******************
 * NAME:    ;CollapseFollows
 * DESC:    Combine nodes with the same category and same set of following nodes.
 * IN:      pList - List of nodes
            pNet - Network to be collapsed.
 * OUT:     Any redundant nodes in pList are combined, and pNet is modified accordingly.
 * RETURN:  TRUE if any nodes were combined.  FALSE otherwise.
 * NOTES:   In a pronunciation graph, any two nodes with the same category
              and the same set of following nodes can be combined.
            There must not be cycles in the graph, or this routine could get
              in trouble (i.e., if one of the nodes deleted is the one whose
              'pNext' list is passed in as pList to this routine).
            If there are no cycles in the graph, this routine should be fine,
              since only nodes in pList are possibly combined, and the original
              node is not in its own follows list.
 *END_HEADER***************************/
BOOL CollapseFollows(llistPtr pList, NetworkPtr pNet)
{
   llistPtr pNodeLink, pNextLink;
   llistPtr pLastLink; /* Pointer to the link before pNextLink in pList. */
   BOOL bCombined; /* Flag for whether any nodes were combined. */
   NodePtr pNode, pNextNode;

   if (!pList || !pList->pNext)
      return FALSE; /* Not more than 1 element in the list => impossible to combine any */
   bCombined=FALSE;
   /* Go through each node in pList */
   for (pNodeLink = pList; pNodeLink; pNodeLink = pNodeLink->pNext)
   {
      /* Get a pointer to the current node. */
      pNode = (NodePtr) pNodeLink->p;
      /* Remember the last link before "pNextLink" so that if pNextLink
         and pNodeLink are merged, we can more easily delete pNextLink. */
      pLastLink = pNodeLink;
      /* Go through every link AFTER pNode's link in pList */
      for (pNextLink = pNodeLink->pNext; pNextLink; pNextLink = pNextLink->pNext)
      {
         pNextNode = (NodePtr) pNextLink->p;
         /* See if the two nodes have the same info and same list of following nodes */
         if (SameNodeInfo(pNode, pNextNode) && pNode != pNextNode && 
             SameNodeLists(pNode->pNext, pNextNode->pNext, pNode->bFinal, pNextNode->bFinal))
         {
            /* They do have the same list of following nodes,
               so COMBINE THE NODES. This is done by moving pNextNode's
               pointers into pNode and then deleting pNextNode from pNet. 
               Make sure pNode survives (and pNextNode is the one that is deleted)
               because our outer "for" loop needs to be able to continue. */
            CombineNodes(pNode, pNextNode, pNet);
            /* Set pNextLink back to pLastLink, since we deleted pNextLink and its
               node from pList inside of CombineNodes.  This allows us to continue
               along the same list without starting over.  (i.e., pLastLink->pNext
               is the next link we want during this loop). */
            pNextLink = pLastLink;
            /* Remember that we have combined nodes at least once. */
            bCombined = TRUE;
         }  /* Same info & following lists */
      }  /* for each node after pNodeLink */
   }  /* for each node in pList*/
   return bCombined;
}  /* CollapseFollows */

/*FUNCTION_HEADER*******************
 * NAME:    ;CollapseNet
 * DESC:    Combine redundant nodes in a network.
 * IN:      pNet - Network to be collapsed.
 * OUT:     Any redundant nodes in pNet are combined with others and deallocated.
 * RETURN:  0 on success, -1 on error.
 * NOTES:   The algorithm for this collapsing scheme was originally developed
            for MULTCONS.  See Randy Wilson's Log Book I, p. 87, 10/1/1997.
 *END_HEADER***************************/
SDWORD CollapseNet(NetworkPtr pNet)
{
   llistPtr pNodeLink;
   NodePtr  pNode; /* Current node being examined */
   BOOL bCombined;

   /* Directed graphs (such as pronunciation graphs) can be collapsed by
      noting two similar observations (where "info" can be category or name):
        1. Any pair of nodes with the same info and same set of "prev" nodes can be combined.
        2. Any pair of nodes with the same info and same set of "next" nodes can be combined.
      Rather than do an n^2 search to identify such pairs (where n is the total
        number of nodes in the graph), we can visit each node and do an m^2 search
        over just the m preceding nodes of each node, as well as the m following nodes,
        to see if there are pairs with the same info.  If so, their next or prev
        lists can be compared to see if they are the same.  If so, they can be combined. */
   if (!pNet)
      return -1;
   /* Set a flag for whether any nodes were combined during each pass. */
   do
   {
      bCombined=FALSE; /* Haven't combined any nodes yet on this pass */
      /* Check initial & final nodes for collapse */
      if (CollapsePrevious(pNet->pInit, pNet))
         bCombined = TRUE;  /* We combined at least one pair of nodes */
      if (CollapseFollows(pNet->pFinal, pNet))
         bCombined = TRUE;  /* We combined at least one pair of nodes */
      for (pNodeLink=pNet->pNodes; pNodeLink; pNodeLink = pNodeLink->pNext)
      {
         /* Get a local pointer to the current node */
         pNode = (NodePtr) pNodeLink->p;

         /* See if any of the previous nodes have the same info and set of next nodes */
         if (CollapseFollows(pNode->pPrev, pNet))
            bCombined = TRUE; /* We combined at least one pair of nodes */
         /* See if any of the following nodes have the same info and set of prev nodes */
         if (CollapsePrevious(pNode->pNext, pNet))
            bCombined = TRUE; /* We combined at least one pair of nodes */
      }
   } while (bCombined);
   return 0; /* ok */
}  /* CollapseNet */

