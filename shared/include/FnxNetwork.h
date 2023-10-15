/*H_HEADER_FILE***************************************************************
FILE        : network.h
DESC        : 
TABS        : 3
OWNER       : 
DATE CREATED: 

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/26/03 4:12p $
  $Revision: 7 $

*END_HEADER******************************************************************/
#ifndef _NETWORK_H
#define _NETWORK_H

#include "FnxPlatform.h"
#include "DTFnxStdlib.h"
#include "FnxLlist.h"
#include "FnxMisc.h"
//#include "slist.h"

typedef struct
{
   llistPtr pPrev;     /* Linked list of preceding nodes */
   llistPtr pNext;     /* Linked list of following nodes */
   SWORD    iBasePhone;/* Index (in pDesc->pBasephone[]) of base phoneme of this node 
                          (After being expanded, iBasePhone remains as the base phone index)*/
   SWORD    iCat;      /* Index (in pDesc->pCategories[]) of context-dependent category (-1 => not expanded yet)*/
   char    *sName;     /* Internal (dictionary/desc) name of the phoneme or word represented by this node. */
   char    *sExternal; /* External name of the phonemes or words. (NULL=>same as internal) */
   struct _WORDT xhuge *pWord;     /* Pointer to word structure with pronunciation information */
   SDWORD   iID;       /* Identifier for converting to array.  -1 => not visited yet.      */
   BOOL     bInit;     /* Flag for whether it is an initial node                            */
   BOOL     bFinal;    /* Flag for whether it is a final node                               */
   llistPtr pMore;     /* Linked list of additional nodes that are treated as alternates
                            to this node.  Used in grammars to treat a list of several
                            alternate words as a single node since that is so common.       */
   char     ePart;     /* What kind of phone category: LEFT_DEPENDENT (e.g., $sil<oU),
                          RIGHT_DEPENDENT (e.g., oU>$sil), CONTEXT_INDEPENDENT (e.g., <oU>), 
                          TRIPHONE (e.g., $sil<oU>$den)                                     */
   //SDWORD   iStress;   /* Stress level (0=>default) (set via phoneme#stress in vocab file) [NOT USED] */
#ifndef USE_SEARCH_GRAPH
   SDWORD   iMinDur;   /* Min & max duration (in ms) of the category (copied from probname) */
   SDWORD   iMaxDur;   /*  (We should eventually rip this out and look up such info when needed) */
#endif
} Node, xhuge *NodePtr;

typedef struct
{
   char      *sName;     /* Name of network (e.g., word name, grammar name, or variable name). NULL=>none. */
   llistPtr  pInit;      /* Linked list of initial nodes in the network */
   llistPtr  pFinal;     /* Linked list of final nodes in the network */
   llistPtr  pNodes;     /* Linked list of all the nodes in the network */
   BOOL      bOptional;  /* Flag for whether it is possible to skip all nodes in this network */
   BOOL      bMergeNodes;/* Flag for whether to allow nodes to be merged together using "pMore" 
                            when two networks are combined via OrNet() and both are "base" networks. 
                            (Currently used by grammar parsing, but not in pronunciation parsing). */
   LinkPoolPtr pLinkPool;/* Pool of linked list pointers to use for links in the Network and its Nodes. 
                            (Usually shared by all networks and subnetworks.  Usually a copy of
                            the address of a pool allocated elsewhere, like in a parser)*/
} Network, xhuge *NetworkPtr;


typedef struct
{
   FILE   *fp;         /* File pointer to use, if parsing from file rather than string (NULL=>use sBuffer) */
   char   *sBuffer;    /* Buffer being parsed (NULL=>use fp)*/
   SDWORD iPos;        /* Position in buffer of next token to be read (ignored if fp is used). */
   SDWORD iToken;      /* Tag of last token parsed (i.e., current one to use) 
                          (-1=>at end; 0..255=>ASCII; 256+ => enumerated tag ID.) */
   char sToken[MAXBUF];/* String of last token parsed */
   BOOL bUseToken;     /* Flag for whether the next call to "GetToken()" should use whatever
                          is already in sToken instead of reading the next thing. */
   LinkPoolPtr pLinkPool;  /* Pool of linked list links to use for links in all networks and nodes */
} Parser, xhuge *ParserPtr;

/* Tag for a literal phoneme or word */
#define LITERAL_TAG  259
/* Tag for a $variable in a grammar */
#define VARIABLE_TAG 260

#if defined(__cplusplus)
extern "C" {
#endif

void InsertList(llistPtr *ppList, llistPtr pPreList);
SDWORD GetToken(ParserPtr pParser, char *sDelim);
void   FreeNode(NodePtr pNode, LinkPoolPtr pLinkPool);
void   FreeNetwork(NetworkPtr pNet);
SDWORD AppendNet(NetworkPtr pNet, NetworkPtr pSubNet);
SDWORD OrNet(NetworkPtr pNet, NetworkPtr pSubNet);
SDWORD AppendNode(NetworkPtr pNet, NodePtr pNode);
SDWORD RepeatNet(NetworkPtr pNet);
SDWORD CollapseNet(NetworkPtr pNet);
NetworkPtr CopyNet(NetworkPtr pNet);

#if defined(__cplusplus)
}
#endif

#endif
