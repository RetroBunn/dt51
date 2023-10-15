/* This file should be included for all languages
   before the specific file GT_bachus.h
*/
//#if !defined OS_PALM && !defined CASIO_SH3 //moved to port.h for each platform MLT 01/26/06
//#include <stdio.h> //moved to port.h for each platform MLT 01/26/06
//#endif //moved to port.h for each platform MLT 01/26/06
//#include<stdlib.h> //moved to port.h for each platform MLT 01/26/06

#include "port.h"

#include "bachusdefs.h"

//typedef unsigned char ASCIILETTER;
#ifndef ASKYPHONEMES_DEFINED
#define ASKYPHONEMES_DEFINED
typedef char ASKYPHONEME;
typedef char ASCKYPHONEME;
#endif

#define UML_A 196
#define UML_O 214
#define UML_U 220
#define UML_a 228
#define UML_o 246
#define UML_u 252
#define UML_sz 223

// SOME BITS defined for return codes when searching the trie.
// used to signal stop conditions in the search algorithms.

#ifndef NIL
#define NIL 0
#endif 


#define LTRIE_NIL         NIL    // same as NULL but sounds better
#define LTRIE_EMPTY       0      // empty, silch, nix in it, just the epsilon node
#define LTRIE_YES         1      // where there is a no there is also a yes
#define LTRIE_ENDOFLEX    2      // end of lexeme
#define LTRIE_INCOMPLETE  4      // string could be matched but is not a complete Lexeme
#define LTRIE_NOCONTINUE  8      // string could only be matched incompletly or not at all.
#define LTRIE_NORIGHT     16     // last search went to the right  
#define LTRIE_NODOWN      32     // last search went in the downwards direction

#define MAX_NUM_LTRIES  80 
#define MAXLTSTACKDEPTH 10
#define MAX_TOKEN_LENGTH 80     // string length (maybe too short for bandwurms)
#define LTRIE_CHUNK_SIZE 10      // used in realloc for resizing and initial size of trie's
#define LONG_MORPH_FIRST 128       // used if multiple morphs match.
#define LONG_MORPH_LAST  256       // used if multiple morphs match.
#define MORPH_ORDER_MASK 384 

#if 0
typedef enum {NULLNODE=0, ENDOFPATH=1, PATHRETURN, INITIALIZE, EPSILONNODE, NOPNODE,  BOUNDACTION,
	      STARTNODE, ALTNODE,  RIGHTNODE, TERMINAL,  NONTERMINAL,
	      LOOPNODE, JUMPNODE, UNBEKANNTE, SYLLABIFY, NEWPATH, TRIENAME,
	      LTRIENAME, OPERATORNAME, PROCESSNAME, SINGLEMORPH, WORDBOUNDARY,SKIPNODE, SKIPLETTERNODE,
	      STATISTICS, DUMPTREE, DUMPALL, FILEDUMP} gnodetype;

typedef enum {
  OPlonger = 100,
  OPshorter = 101,
  OPstartvowel = 102,
  OPstartcons = 103,
  OPsyllabify = 200,
  OPgrammar = 300,
  OPspezial = 400,
  OPbreak  = 999
} operatornumber;

typedef enum {NOEXIT=0, 
	      FOUND = 1, 
	      ENDOFLEX=2,
	      REPEATABLE=3} tnodeinfo;

typedef enum {WORDSEPARATOR=0,
	      MORPHEME=1,
	      PROSODICMARKER=2,
	      LETTERTRIE=3} parserinfo;


typedef struct phomeme_string_collection
{
  CONST U16       nstrings;            // number of strings in the pool
  CONST int       buflen;              // size of pool
  CONST ASCIILETTER *bigbuffer;          // pooled phoneme strings
  CONST U16       *ptarray;            // pointer array
} PhonemeWords;



typedef 
struct  _trie_node
{
  CONST ASCIILETTER    letter;           // a single letter to compare against
  CONST tnodeinfo  info;               // see enum above.
  CONST U16  rule;           // things like the hardending rule are numbered. 
  CONST U16  down;                     // down: alternative node (address of other TrieNode)
  CONST U16  right;                    // right: continuation node (address of other TrieNode)
  CONST U16  phonemehandle;  // new addition for direct translation into phonemes index into an array of pointers to strings.
}
TrieNode;

typedef 
struct _letter_tree
{
  CONST U16        nnodes;   // number of valid nodes.
  CONST U16        type;
  CONST TrieNode  *Nodes;    // array of nodes
} LTrie;

typedef
   struct _lt_stack_tokens 
   {
     U16  nodenumber;
     U16  position;
   } LtStkToken;        // will be LtStoken or LtStkToken

#endif

#if 0
typedef struct _gnodeinfo
{
  U16 status;                 // depends on type (e.g., loop state for loop)
  U16 counter;                // counts whatever we like
  U16 counterB;               // counts whatever we like
  U16 parameter;              // max loop count e.g.
} gnodeinfo;
typedef 
struct  _meta_trie_node
{
  ASCIILETTER *name;          // redundant except for compare strings nodes.
  U16  alt;                
  U16  what;                // for repeatables: pointer to self.
  U16  right;
  U16  index;               // index of symbols (same thing above)
  gnodetype typeinfo;       // 
  gnodeinfo  info;          // type,status, counter, parameter
}
GTrieNode;

typedef
struct _meta_tree
{
  U16   size;              // number of nodes allocated.
  U16   nnodes;            // number of valid nodes.
  U16   nempty;            // number of still free nodes
  U16   increments;        // chunk size for allocation
  U16   last;              // next new node
  U16   current;           // so far that's all the state it has.
  GTrieNode  *Nodes;       // array of nodes
} GTrie;
#endif


typedef struct CH_walk_info{
    BOOL succeeded;
    U16  wordpos;
    U16  altnode;
} CH_walkinfo;


