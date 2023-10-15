#ifndef _BACHUSDEFS_DEFINED_
#define _BACHUSDEFS_DEFINED_

#include "port.h"
#include "dectalkf.h"

typedef unsigned char ASCIILETTER;


#if defined EPSON_ARM7
#define MAXSTACKDEPTH 60
#define MAXNESTING 50
#define GNODEINCREMENTS 20 
#define MAXRECURSIONS 5000
#define MAXMORPHLENGTH 16       /* no phoneme snippets longer than this  */
#define MAXMORPHNUMBER 20       /* no more morphems per word */
#define MAXLETTERBUFLENGTH 80
/* type definitions */ 
#else
#define MAXSTACKDEPTH 150
#define MAXNESTING 200
#define GNODEINCREMENTS 20 
#define MAXRECURSIONS 5000
#define MAXMORPHLENGTH 16       /* no phoneme snippets longer than this  */
#define MAXMORPHNUMBER 20       /* no more morphems per word */
#define MAXLETTERBUFLENGTH 80
#endif    /*EPSON_ARM7 */


typedef enum {NULLNODE=0, ENDOFPATH=1, PATHRETURN, INITIALIZE, EPSILONNODE, 
	      NOPNODE,  BOUNDACTION,
	      STARTNODE, ALTNODE,  RIGHTNODE, TERMINAL,  NONTERMINAL,
	      LOOPNODE, JUMPNODE, UNBEKANNTE, SYLLABIFY, NEWPATH, TRIENAME,
	      LTRIENAME, OPERATORNAME, PROCESSNAME, SINGLEMORPH, WORDBOUNDARY,
	      SKIPNODE, SKIPLETTERNODE,
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

typedef struct _gnodeinfo
{
  U16 status;                 // depends on type (e.g., loop state for loop)
  U16 counter;                // counts whatever we like
  U16 counterB;               // counts whatever we like
  U16 parameter;              // max loop count e.g.
} gnodeinfo;
  
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

typedef unsigned short int StkToken;   // compatible

typedef 
struct _mini_stack_nodes
{
  StkToken v[MAXSTACKDEPTH];
  StkToken *p;
  U16 ntok;
  U16 sz;
  U16 status;
} Nodestack;


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

typedef 
struct _word_part
{
    ASCIILETTER morphname[MAXMORPHLENGTH];     // e.g., "suffix", "prefix" etc,  or special symbols
    ASCIILETTER wordpart[MAXMORPHLENGTH];      // word string snippet
    ASCIILETTER phonemepart[MAXMORPHLENGTH];   // phoneme string snippet
    U16  rulenumber;                         // number of rule, e.g. hardening rule, applied to phonemes in certain context
    U16  type;                               // new: value of enum type parserinfo
    U16  from;                               // column in word
    U16  to;                                 // end of string position
} Morpheme;
  
typedef 
struct _wordcomposition{
  int    nparts;
  Morpheme morph[MAXMORPHNUMBER];      // anything bigger would crash
} MorphemeStruct;


#endif // _BACHUSDEFS_DEFINED_
