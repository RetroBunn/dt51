#ifndef _BUILDER_H_
#define _BUILDER_H_
/* avoid multple inclusions */

#include "bachusdefs.h"
#ifdef USE_NAND
#include "FileSystemDict.h"
#include "GermanFileSystemDict.h"
#endif

//moved to port.h for each platform - mlt
//#if !defined OS_PALM && !defined CASIO_SH3
//#include <stdio.h>
//#endif
//#include<stdlib.h>

//#ifdef OS_SYMBIAN
#include "port.h" //added for platform specific stuff - mlt
//#endif

//moved to port.h for each platform - mlt
//#ifndef CONST
//#define CONST const
//#endif

#define MATCHINGTRIX 1      /* new experiment */

#define BACHUS_IN_DECTALK

/* These definitions are used by the parser bachus. 
*/

/* definitions relevant for the generation of include files. */
#define BACHUSSTRING "Bach_"
#define CONSTSTRING "CONST "

/* Set this if you want the executable to produce a prompt and one can
   type in individual words. */

#ifndef BACHUS_IN_DECTALK
#define FROMTYPED 
#define GRAMMAR_EVALUATION 1 /* counting alt nodes, see builder.c */
#endif

/* max size definitions */

//#define MAXGNODES 2000   /* for the Gtwalker */
#define MAXRECURSIONS 5000 

//eab maxnesting is the only parameter that really has leverage on walkcnt size
// except for WALKERNESTINGSTACK which I chnaged the counters to U16's instead of int.

//#define MAXRECURSIVELEVEL 30
#if defined EPSON_ARM7
#define MAXSTACKDEPTH 60
#define MAXNESTING 50
#define GNODEINCREMENTS 20 

#define MAXMORPHLENGTH 16       /* no phoneme snippets longer than this  */
#define MAXMORPHNUMBER 20       /* no more morphems per word */
#define MAXLETTERBUFLENGTH 80
/* type definitions */ 
#else
#define MAXSTACKDEPTH 150
#define MAXNESTING 200
#define GNODEINCREMENTS 20 

#define MAXMORPHLENGTH 16       /* no phoneme snippets longer than this  */
#define MAXMORPHNUMBER 20       /* no more morphems per word */
#define MAXLETTERBUFLENGTH 80

#endif


//moved to port.h for each platform - mlt
//#if !defined _UNIX_LIKE_
//#ifndef ARM7
//typedef unsigned short  U16;
//#endif
//#ifndef FRENCH
//#ifndef SHORT_DEFINED
//#define SHORT_DEFINED
//typedef short int  SHORT;
//#endif
//#endif
//typedef unsigned char uBOOL;

//moved to port.h for each platform - mlt
//#ifndef ARM7
//typedef int  BOOL;
//#endif
//#else
//typedef unsigned char uBOOL;
//#endif



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

#if defined USE_NAND && defined USE_464
#define CACHE_RESULTS 1
#define DONT_CACHE_RESULTS 0
#endif

/* New: collect phoneme strings that are hung into the grapheme letter tries. */
#ifndef BACHUS_IN_DECTALK
typedef struct phomeme_string_collection
{
  U16       nstrings;            // number of strings in the pool
  int       buflen;              // size of pool
  ASCIILETTER *bigbuffer;          // pooled phoneme strings
  U16       *ptarray;            // pointer array
} PhonemeWords;
#else
#if 0
typedef struct phomeme_string_collection
{
  CONST U16       nstrings;            // number of strings in the pool
  CONST int       buflen;              // size of pool
  CONST ASCIILETTER *bigbuffer;          // pooled phoneme strings
  CONST U16       *ptarray;            // pointer array
} PhonemeWords;
#endif
#endif



#ifndef BACHUS_IN_DECTALK
typedef 
struct  _trie_node
{
  ASCIILETTER    letter;           // a single letter to compare against
  U16  down;                     // down: alternative node (address of other TrieNode)
  U16  right;                    // right: continuation node (address of other TrieNode)
  tnodeinfo  info;               // see enum above.
  U16    rule;           // things like the hardending rule are numbered. 
  U16    phonemehandle;  // new addition for direct translation into phonemes index into an array of pointers to strings.
}
TrieNode;
#else 
#if 0
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
#endif
#endif 

#ifndef BACHUS_IN_DECTALK
typedef
struct _letter_tree
{
  U16  size;           // number of nodes allocated.
  U16  nempty;         // number of still free nodes
  U16  increments;     // chunk size for allocation
  U16  last;           // next new node
  U16  current;        // so far that's all the state it has.
  U16  stopcondition;  // to signal why something was found or not.
  U16  searchposition; // signal how far in the search string we are proceeded.
  U16  nnodes;         // number of valid nodes.
  U16  type;
  TrieNode  *Nodes;    // array of nodes
} LTrie;
#else
#if 0
typedef 
struct _letter_tree
{
  CONST U16        nnodes;   // number of valid nodes.
  CONST U16        type;
  CONST TrieNode  *Nodes;    // array of nodes
} LTrie;
#endif
#endif  /* BACHUS_IN_DECTALK */

#if 0
typedef
   struct _lt_stack_tokens 
   {
     U16  nodenumber;
     U16  position;
   } LtStkToken;        // will be LtStoken or LtStkToken

#endif
typedef 
struct _mini_stack_for_letter_trie
{
  LtStkToken v[MAXLTSTACKDEPTH];
  LtStkToken *p;
  U16 ntok;
  U16 sz;
  U16 status;
} LtStack;    

typedef 
struct _letter_trie_parser_state
{
  LTrie *Lt;		  /* e.g., the suffix table */
  U16 startposition;        /* in the word  */
  LtStack stack;            /* path in Ltrie */
}
LtParserState;

U16 Lt_parse_string(ASCIILETTER *, U16, const LTrie *, U16 *,U16 *, U16 *,U16);
ASCIILETTER *point_to_phoneme_string(const PhonemeWords *Mdict, U16 index);
/* note that the following definitions are very similar
   to the ones in Trie.h. Also a lot of the methods in
   the meta-trie are similar or identical to the 
   methods in a letter trie. (Unfortunatly, we are
   not allowed to program in C++ which becomes a pain in
   the neck at this point) ReWT.
*/

/* the next enum gives values used in the processing of GtWalker.
   Since the same names are used also during the generation of the grammar tree,
   there are also some surprising words in here, like DUMPALL and FILEDUMP.   
   I left them in here so the function buildtree contains also the
   function to display the grammar tree, including printing 
   use statistics, see the switch STATISTICS in buildtree/builder.c
*/

  
#if 0
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

#if 0
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
#endif

/* see nodestack.c */
Nodestack newNodestack(void);
void initNodestack(Nodestack *);
BOOL pushNode(Nodestack *, StkToken);
StkToken  popNode(Nodestack *);
StkToken  topNode(Nodestack *);
void resetNodestack(Nodestack *);
void resetNodestack(Nodestack *);


/* Note should be taken of the following definitions of 
   two different stacks that we need. This is somewhat
   confusing. The two types of stacks are only distinguished
   by types of items they store. (help help please let
   me redo this with C++ template classes!!! so much easier)
*/


/* See ltstack.c */

LtStack newLtStack(void);
void initLtStack(LtStack *);
BOOL pushLtNode(LtStack *, LtStkToken);
LtStkToken  popLtNode(LtStack *);
LtStkToken  topLtNode(LtStack *);
void resetLtStack(LtStack *);
void resetLtStack(LtStack *);


typedef
struct _builder_status{
  BOOL newrule;
  BOOL newpath;
  U16 startnodes;
  U16 lastright;
  U16 laststart;
  U16 lastalt;
  BOOL loopstart;
  U16 loopnest;
  BOOL pathn;
} builderstatus;

BOOL buildtree(gnodetype, ASCIILETTER *, int, int);   /* the builder here */


/* The following structure is used by lex and yacc to keep new names. They
   are put in there by lex.
*/

#define NSYMS 200	/* maximum number of symbols */
#define NMAXMORPHS 100  /* maximum number of morph string in grammar */

#ifndef BACHUS_IN_DECTALK
struct symtab {
	char *name;
	int  value;
} symtab[NSYMS];

struct symtab *symlook();
#endif

#define NTRIEFILES 50
typedef 
struct _lettertriefiles{
  U16  value;               // symbol index
  U16  type;                // type: forward or backward, minimal word first or maximal word first etc.
  char *triename;           // symbol name
  char *filename;           // filename where word or morpheme list can be found.
} lettertriename;


void set_lex_column(int);
void set_lex_line(int);
void nextlexline(void);
void movelexcolumn(int);
void reset_lex_pos(void);
int lex_column(void);
int lex_lastcol(void);
int lex_line(void);

LTrie file2ltrie(CONST ASCIILETTER *, PhonemeWords *, const U16);
ASCIILETTER *gnodetypename(gnodetype);

#if 0
typedef 
struct _word_part
{
  ASCIILETTER morphname[MAXMORPHLENGTH];     // e.g., "suffix", "prefix" etc,  or special symbols
  ASCIILETTER wordpart[MAXMORPHLENGTH];      // word string snippet
  ASCIILETTER phonemepart[MAXMORPHLENGTH];   // phoneme string snippet
  U16  rulenumber;                         // number of rule, e.g. hardening rule, applied to phonemes in certain context
} Morpheme;
  
typedef 
struct _wordcomposition{
  int    nparts;
  Morpheme morph[MAXMORPHNUMBER];      // anything bigger would crash
} MorphemeStruct;
#endif

typedef struct _walk_info{
  BOOL succeeded;
  U16  wordpos;
} walkinfo;


/* nonrecursive GtWalker */
typedef struct _walkerstack
{
	//eab make counters smaller
  U16 inx,jnx,ii,jj,j1,j2,incr;
  U16 nalt,ntrie,currpos;
  U16 next,alt,what,curr;
#ifdef CASIO_SH3
  WORD_SEG_LIST word_segs[8];
#endif
#ifndef CASIO_SH3
  U16 proceed[8];
  U16 phonemeindex[8];
  U16 ruleindex[8];
#endif
  U16 opcode, opparam, match; // for operator calls.
  walkinfo newwalki;
  walkinfo oldwalki;
  ASCIILETTER *phonemestring;
#ifdef CASIO_SH3
  ASCIILETTER phonemestring_464[16];
#endif
  U16 rulenumber;
} 
WALKERNESTINGSTACK;

#ifndef JUMPSTACK_DEFINED
#define JUMPSTACK_DEFINED
typedef char Jumpstack;
#endif

typedef
struct _walker_context {
  int   counter;
  int   level;
  int   maxlevel;
  int   alert;
  int   grammar;                  /* usually zero, but used for syllabification has non zero value */
  BOOL  special;                  /* to check a word's special bit. */
#ifdef GRAMMAR_EVALUATION         /* requires writing counting hit numbers and writing in the grammar structure */
  GTrieNode *Nodes;               /* but may cause some warnings about const versus non const. */
  U16  nnodes;
#else
  CONST GTrieNode *Nodes;
  CONST U16  nnodes;
#endif
  CONST LTrie *Ltlist;               // letter trie list.
  CONST  PhonemeWords *MorphDict;    // structure to hold all morpheme's phoneme strings. 
  Nodestack nstack;
  ASCIILETTER *theword;                // handle this pointer externally. Who knows how long a word might be?
  ASCIILETTER wordchar[MAXLETTERBUFLENGTH];
  ASCIILETTER workbuffer[MAXLETTERBUFLENGTH];
  MorphemeStruct  Morphstruct;
  U16 wordlength;
  U16 wordpos;
    WALKERNESTINGSTACK STK[MAXNESTING];
    Jumpstack jmpstack[MAXNESTING];
    int       jmptop;
} WalkCNTXT;

/* Isn't there a more elegant method??: */

#ifndef _this_is_main_bachus_
extern builderstatus buildstat;
extern GTrie  STGT;
extern Nodestack Stloopstack;
extern lettertriename LTrieFiles[NTRIEFILES];   
extern LTrie  LTrieList[NTRIEFILES];   
extern PhonemeWords MorphDict;
#else
#ifndef  EXTERNAL_USE_BACHUS
builderstatus buildstat;
GTrie  STGT;
Nodestack Stloopstack;
lettertriename LTrieFiles[NTRIEFILES];  
LTrie  LTrieList[NTRIEFILES]; 
PhonemeWords MorphDict;
#endif
#endif
/* end of cludge */

#ifdef GERMAN_SYLLABIFICATION
typedef struct _syllable_struct{
  U16 stesstype;
  ASCIILETTER onset[8];
  ASCIILETTER nucleus[6];
  ASCIILETTER coda[10];
} 
GERSYLL;
#endif


typedef struct _bachus_global_information{
  CONST  U16            nnodes;
  CONST  GTrieNode     *GtNodes;
  CONST  U16            notries;
  CONST  LTrie         *Ltreelist;
  CONST  PhonemeWords  *MorphDict; 
}
wordgrammarinfo;


/* new includes for hyphenation (former token.h). */
#ifdef  HYPHENATION_METHOD 
#ifndef tokens_hyphenation
#define tokens_hyphenation

#define MAX_TOKEN_LENGTH 80
#define TOKENFILE "GermanHyph.tex"
#define MAX(a,b) (a)<(b)? b:a
#define MIN(a,b) (a)>(b)? b:a

#define MAX_DIGITS 8
#define MAX_TOKEN 8
#define MAXAFFECTEDTOKENS 100

#define UML_A 196
#define UML_O 214
#define UML_U 220
#define UML_a 228
#define UML_o 246
#define UML_u 252
#define UML_sz 223

#define NUM_INDEXED_LETTERS 31


#ifdef WITH_TOKEN_PREPROCESSING

struct token_struct{
  char   str[MAX_TOKEN];
  char   orig[MAX_TOKEN*2];
  int  ndigits;
  int  pos[MAX_DIGITS];
  int  digits[MAX_DIGITS];
};

#else

struct token_struct{
  char   *str;
  char   *orig;
};

#endif

#define CONST const

typedef struct token_struct tokenT;

typedef struct _hyphenation_struct 
{
  CONST int     *from;
  CONST int     *to;
  CONST tokenT  *TOK;
}
HPatterns;

#endif   /* tokens_hyphenation */
#endif   /* HYPHENATION_METHOD */


void make_ltries(void);
walkinfo  GtWalker(WalkCNTXT *, U16 , walkinfo );
void process_rule(Morpheme *,Morpheme *,Morpheme *,Morpheme *,Morpheme *);
#ifndef CASIO_SH3
BOOL morphemize_word(void *pLts_t,const ASCIILETTER *, ASCIILETTER *, ASCIILETTER *, WalkCNTXT *, const wordgrammarinfo *);
#endif
void concat_morphems_phonemes(ASCIILETTER *, MorphemeStruct *, const int, const BOOL);
BOOL correct_unstressed_longvowels(ASCIILETTER *);    // in allorules     

#define MAX_BACHUSLETTERS 120

#ifdef CASIO_SH3
#define MAXCANDIDATES 4
//eab smaller

#define MAXCANDCOLLECTION 100
#else
#define MAXCANDIDATES 5
#define MAXCANDCOLLECTION 150
#endif

#include "minpath.h"
typedef
struct  _candidate {
  SHORT from;
  SHORT to;
  U16 rule;
  U16 type;
  SHORT  weight;
#ifdef CASIO_SH3
  //eab smaller
  ASCIILETTER str[16];
  ASCIILETTER phon[15];
#else
  ASCIILETTER str[20];
  ASCIILETTER phon[20];
#endif

}
candidate;

typedef
struct  _candidate_list {
  int nlist;
  candidate  cand[MAXCANDIDATES];
}
canditlist;

typedef 
struct _collection_list {
  int nlist;
  candidate  cand[MAXCANDCOLLECTION];
}
canditcollection;


#endif   // _Builder_h
