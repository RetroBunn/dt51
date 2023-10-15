#ifndef _IT_BUILDER_H_
#define _IT_BUILDER_H_
/* avoid multple inclusions */

//moved to port.h for each platform - mlt
//#include<stdio.h>
//#include<stdlib.h>
#ifdef USE_NAND
#include "FileSystemDict.h"
#include "ItalianFileSystemDict.h"
#endif //USE_NAND

#if defined EPSON_ARM7 || defined MULTIPLE_LANGUAGES_LOADED
#include "ltsnames.h"
#endif

//#ifdef OS_SYMBIAN
#include "port.h" //added for platform specific stuff
//#endif

//moved to port.h for each platform - mlt
//#ifndef CONST
//#define CONST const
//#endif

//moved to port.h for each platform - mlt
//#ifndef _UNIX_LIKE_
//#ifndef U16_DEFINED
//#define U16_DEFINED
//typedef unsigned short  U16;
//#endif
//#ifndef SHORT_DEFINED
//#define SHORT_DEFINED
//typedef short SHORT;
//#endif
//#endif

#include "bachusdefs.h"

#define BACHUS_IN_DECTALK

/* These definitions are used by the parser bachus. 
*/

/* definitions relevant for the generation of include files. */
#define IT_BACHUSSTRING "IT_Bach_"
#ifndef CONSTSTRING
#define CONSTSTRING "CONST "
#endif

/* Set this if you want the executable to produce a prompt and one can
   type in individual words. */

#ifndef BACHUS_IN_DECTALK
#define FROMTYPED 
#define GRAMMAR_EVALUATION 1 /* counting alt nodes, see builder.c */
#endif

/* max size definitions */
#if defined CASIO_SH3 || defined EPSON_ARM7

#define IT_MAXGNODES 2000          /* for the Gtwalker */
#define IT_MAXRECURSIONS 20000
#define IT_MAXSTACKDEPTH 100
#define IT_MAXNESTING 200
#define IT_GNODEINCREMENTS 20 
#define IT_MAXMORPHLENGTH 38       /* no phoneme snippets longer than this  */
#define IT_MAXMORPHNUMBER 40       /* no more morphems per word */
#define IT_MAXLETTERBUFLENGTH 80
#define IT_MAXSEQGENCOMMANDS 1000
#else

#define IT_MAXGNODES 2000          /* for the Gtwalker */
#define IT_MAXRECURSIONS 50000
#define IT_MAXNESTING 1000          /* max number of GtWalker calling itself recursively */
#define IT_MAXSTACKDEPTH 150
#define IT_GNODEINCREMENTS 20 
#define IT_MAXMORPHLENGTH 40       /* no phoneme snippets longer than this  */
#define IT_MAXMORPHNUMBER 50       /* no more morphems per word */
#define IT_MAXLETTERBUFLENGTH 80
#endif

#define IT_MAXRULEBUFLEN 100       
#define IT_MAXRULEALLBUFFERLENGTH (6*IT_MAXRULEBUFLEN)          /* do not change the 6 */
/* type definitions */ 

// already defined in bachusdefs.h
//typedef unsigned char ASCIILETTER;
#ifndef ASKYPHONEMES_DEFINED
#define ASKYPHONEMES_DEFINED
typedef char ASKYPHONEME;
typedef char ASCKYPHONEME;
#endif
//moved to port.h for each platform - mlt
//#ifndef ARM7
//#ifndef _UNIX_LIKE_
//typedef int  BOOL;
//#endif
//#else
//#if (!defined OS_SYMBIAN || !defined OS_PALM) && !defined BOOL_DEFINED
//#define BOOL_DEFINED
//typedef unsigned char BOOL;
//#endif	//#if (!defined OS_SYMBIAN || !defined OS_PALM) && !defined BOOL_DEFINED
//#endif	//#ifndef ARM7

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

#define IT_LTRIE_NIL         NIL    // same as NULL but sounds better
#define IT_LTRIE_EMPTY       0      // empty, silch, nix in it, just the epsilon node
#define IT_LTRIE_YES         1      // where there is a no there is also a yes
#define IT_LTRIE_ENDOFLEX    2      // end of lexeme
#define IT_LTRIE_INCOMPLETE  4      // string could be matched but is not a complete Lexeme
#define IT_LTRIE_NOCONTINUE  8      // string could only be matched incompletly or not at all.
#define IT_LTRIE_NORIGHT     16     // last search went to the right  
#define IT_LTRIE_NODOWN      32     // last search went in the downwards direction

#define IT_MAX_NUM_LTRIES  80 
#define IT_MAXLTSTACKDEPTH 10
#define IT_MAX_TOKEN_LENGTH 80     // string length (maybe too short for bandwurms)
#define IT_LTRIE_CHUNK_SIZE 10      // used in realloc for resizing and initial size of trie's
#define IT_LONG_MORPH_FIRST 128       // used if multiple morphs match.
#define IT_LONG_MORPH_LAST  256       // used if multiple morphs match.
#define IT_MORPH_ORDER_MASK 384 

/* New: collect phoneme strings that are hung into the grapheme letter tries. */
#ifndef BACHUS_IN_DECTALK
typedef struct IT_phomeme_string_collection
{
  U16       nstrings;            // number of strings in the pool
  int       buflen;              // size of pool
  ASCIILETTER *bigbuffer;          // pooled phoneme strings
  U16       *ptarray;            // pointer array
} IT_PhonemeWords;
#else
typedef struct IT_phomeme_string_collection
{
  CONST U16       nstrings;            // number of strings in the pool
  CONST int       buflen;              // size of pool
  CONST ASCIILETTER *bigbuffer;          // pooled phoneme strings
  CONST U16       *ptarray;            // pointer array
} IT_PhonemeWords;
#endif



#ifndef BACHUS_IN_DECTALK
typedef 
struct  IT_trie_node
{
  ASCIILETTER    letter;           // a single letter to compare against
  U16  down;                     // down: alternative node (address of other TrieNode)
  U16  right;                    // right: continuation node (address of other TrieNode)
  tnodeinfo  info;               // see enum above.
  U16    rule;           // things like the hardending rule are numbered. 
  U16    phonemehandle;  // new addition for direct translation into phonemes index into an array of pointers to strings.
}
IT_TrieNode;

#else 
typedef 
struct  IT_trie_node
{
  CONST ASCIILETTER    letter;           // a single letter to compare against
  CONST tnodeinfo  info;               // see enum above.
  CONST U16  rule;           // things like the hardending rule are numbered. 
  CONST U16  down;                     // down: alternative node (address of other TrieNode)
  CONST U16  right;                    // right: continuation node (address of other TrieNode)
  CONST U16  phonemehandle;  // new addition for direct translation into phonemes index into an array of pointers to strings.
}
IT_TrieNode;
typedef 
struct  IT_short_trie_node
{
  ASCIILETTER    letter;           // a single letter to compare against
  tnodeinfo  info;               // see enum above.
  U16  down;                     // down: alternative node (address of other TrieNode)
  U16  right;                    // right: continuation node (address of other TrieNode)
}
IT_STrieNode;
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
} IT_LTrie;
#else

typedef 
struct IT_letter_tree
{
    CONST U16        nnodes;   // number of valid nodes.
    CONST U16        type;
    CONST U16        nodetype;
    CONST union {
	CONST IT_TrieNode   *Nodes;    // array of nodes
	CONST IT_STrieNode  *SNodes;    // array of short nodes without phoneme information.
	} u;
} IT_LTrie;
#endif  /* BACHUS_IN_DECTALK */

typedef
   struct IT_lt_stack_tokens 
   {
     U16  nodenumber;
     U16  position;
   } IT_LtStkToken;        // will be LtStoken or LtStkToken

  

typedef 
struct IT_mini_stack_for_letter_trie
{
  IT_LtStkToken v[IT_MAXLTSTACKDEPTH];
  IT_LtStkToken *p;
  U16 ntok;
  U16 sz;
  U16 status;
} IT_LtStack;    

typedef 
struct IT_letter_trie_parser_state
{
  IT_LTrie *Lt;		  /* e.g., the suffix table */
  U16 startposition;        /* in the word  */
  IT_LtStack stack;            /* path in Ltrie */
}
IT_LtParserState;

U16 IT_Lt_parse_string(ASCIILETTER *, U16, CONST IT_LTrie *, U16 *,U16 *, U16 *,U16);
U16 IT_short_Lt_parse_string(ASCIILETTER *, U16, CONST IT_LTrie *, U16 *,U16 *, U16 *,U16);

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


typedef 
struct  IT_meta_trie_node
{
  ASCIILETTER *name;          // redundant except for compare strings nodes.
  U16  alt;                
  U16  what;                // for repeatables: pointer to self.
  U16  right;
  U16  index;               // index of symbols (same thing above)
  gnodetype typeinfo;       // 
  gnodeinfo  info;          // type,status, counter, parameter
}
IT_GTrieNode;

typedef
struct IT_meta_tree
{
  U16   size;              // number of nodes allocated.
  U16   nnodes;            // number of valid nodes.
  U16   nempty;            // number of still free nodes
  U16   increments;        // chunk size for allocation
  U16   last;              // next new node
  U16   current;           // so far that's all the state it has.
  IT_GTrieNode  *Nodes;       // array of nodes
} IT_GTrie;

typedef unsigned short int IT_StkToken;   // compatible

typedef 
struct IT_mini_stack_nodes
{
  IT_StkToken v[IT_MAXSTACKDEPTH];
  IT_StkToken *p;
  U16 ntok;
  U16 sz;
  U16 status;
} IT_Nodestack;

/* see nodestack.c */
IT_Nodestack IT_newNodestack(void);
void IT_initNodestack(IT_Nodestack *);
BOOL IT_pushNode(IT_Nodestack *, IT_StkToken);
IT_StkToken  IT_popNode(IT_Nodestack *);
IT_StkToken  IT_topNode(IT_Nodestack *);
void IT_resetNodestack(IT_Nodestack *);


/* Note should be taken of the following definitions of 
   two different stacks that we need. This is somewhat
   confusing. The two types of stacks are only distinguished
   by types of items they store. (help help please let
   me redo this with C++ template classes!!! so much easier)
*/


/* See ltstack.c */

IT_LtStack IT_newLtStack(void);
void IT_initLtStack(IT_LtStack *);
BOOL IT_pushLtNode(IT_LtStack *, IT_LtStkToken);
IT_LtStkToken  IT_popLtNode(IT_LtStack *);
IT_LtStkToken  IT_topLtNode(IT_LtStack *);
void IT_resetLtStack(IT_LtStack *);


typedef
struct IT_builder_status{
  BOOL newrule;
  BOOL newpath;
  U16 startnodes;
  U16 lastright;
  U16 laststart;
  U16 lastalt;
  BOOL loopstart;
  U16 loopnest;
  BOOL pathn;
} IT_builderstatus;




/* The following structure is used by lex and yacc to keep new names. They
   are put in there by lex.
*/

// #define NSYMS 200	/* maximum number of symbols */
// #define NMAXMORPHS 100  /* maximum number of morph string in grammar */

#ifndef BACHUS_IN_DECTALK
BOOL buildtree(gnodetype, ASCIILETTER *, int, int);   /* the builder here */
struct IT_symtab {
	char *name;
	int  value;
} IT_symtab[NSYMS];

struct IT_symtab *symlook();
#endif

#define IT_NTRIEFILES 50
typedef 
struct IT_lettertriefiles{
  U16  value;               // symbol index
  U16  type;                // type: forward or backward, minimal word first or maximal word first etc.
  char *triename;           // symbol name
  char *filename;           // filename where word or morpheme list can be found.
} IT_lettertriename;


void set_lex_column(int);
void set_lex_line(int);
void nextlexline(void);
void movelexcolumn(int);
void reset_lex_pos(void);
int lex_column(void);
int lex_lastcol(void);
int lex_line(void);

IT_LTrie IT_file2ltrie(CONST ASCIILETTER *, IT_PhonemeWords *, CONST U16);
ASCIILETTER *gnodetypename(gnodetype);

typedef 
struct IT_word_part
{
    ASCIILETTER morphname[IT_MAXMORPHLENGTH];     // e.g., "suffix", "prefix" etc,  or special symbols
    ASCIILETTER wordpart[IT_MAXMORPHLENGTH];      // word string snippet
    ASCIILETTER phonemepart[IT_MAXMORPHLENGTH];   // phoneme string snippet
    U16  rulenumber;                         // number of rule, e.g. hardening rule, applied to phonemes in certain context
    U16  type;                               // new: value of enum type parserinfo
    U16  from;                               // column in word
    U16  to;                                 // end of string position
} IT_Morpheme;
  
typedef 
struct IT_wordcomposition{
  int    nparts;
  IT_Morpheme morph[IT_MAXMORPHNUMBER];      // anything bigger would crash
} IT_MorphemeStruct;



typedef struct IT_walk_info{
    BOOL succeeded;
    U16  wordpos;
    U16  altnode;
} IT_walkinfo;


typedef struct IT_walkerstack
{
    CONST IT_LTrie *Lt;
    int i,j,ii,jj,j1,j2,incr;
    U16 nalt,ntrie,currpos;
    U16 next,alt,what;
#ifdef USE_NAND
	WORD_SEG_LIST word_segs[4];
#else
    U16 proceed[4];
    U16 phonemeindex[4];
    U16 ruleindex[4];
#endif
    U16 opcode, opparam, match; // for operator calls.
#ifdef USE_NAND
    ASCIILETTER phonemestring[18];
#else
    ASCIILETTER *phonemestring;
#endif
    U16 rulenumber;
    U16 curr;
    IT_walkinfo newwalki;
    IT_walkinfo oldwalki;
} 
IT_WALKERNESTINGSTACK;

typedef char IT_Jumpstack;

typedef
struct IT_walker_context {
    int   counter;
    int   level;
    int   maxlevel;
    int   alert;
    int   grammar;                  /* usually zero, but used for syllabification has non zero value */
    BOOL  special;                  /* to check a word's special bit. */
#ifdef GRAMMAR_EVALUATION         /* requires writing counting hit numbers and writing in the grammar structure */
    IT_GTrieNode *Nodes;               /* but may cause some warnings about const versus non const. */
    U16  nnodes;
#else
    CONST IT_GTrieNode *Nodes;
    CONST U16  nnodes;
#endif
    CONST IT_LTrie *Ltlist;               // letter trie list.
    CONST  IT_PhonemeWords *MorphDict;    // structure to hold all morpheme's phoneme strings. 
    IT_Nodestack nstack;
    ASCIILETTER *theword;                // handle this pointer externally. Who knows how long a word might be?
    ASCIILETTER wordchar[IT_MAXLETTERBUFLENGTH];
    ASCIILETTER workbuffer[IT_MAXLETTERBUFLENGTH];
    IT_MorphemeStruct  Morphstruct;
    U16 wordlength;
    U16 wordpos;
#ifndef USE_NAND
	U16 magic_signal;
#endif
    IT_WALKERNESTINGSTACK STK[IT_MAXNESTING];
    IT_Jumpstack jmpstack[IT_MAXNESTING];
    int       jmptop;
} IT_WalkCNTXT;

/* Isn't there a more elegant method??: */


//#ifndef _this_is_main_bachus_
//extern builderstatus buildstat;
//extern GTrie  STGT;
//extern Nodestack Stloopstack;
//extern lettertriename LTrieFiles[NTRIEFILES];   
//extern LTrie  LTrieList[NTRIEFILES];   
//extern PhonemeWords MorphDict;
//extern WalkCNTXT Walkercntxt;
//#else
//#ifndef  EXTERNAL_USE_BACHUS
//builderstatus buildstat;
//GTrie  STGT;
//Nodestack Stloopstack;
//lettertriename LTrieFiles[NTRIEFILES];  
//LTrie  LTrieList[NTRIEFILES]; 
//PhonemeWords MorphDict;
//WalkCNTXT Walkercntxt;
//#endif
//#endif
/* end of cludge */



typedef struct IT_bachus_global_information{
  CONST  U16            nnodes;
  CONST  IT_GTrieNode     *GtNodes;
  CONST  U16            notries;
  CONST  IT_LTrie         *Ltreelist;
  CONST  IT_PhonemeWords  *MorphDict; 
}
IT_wordgrammarinfo;


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

BOOL IT_pushNode(IT_Nodestack *stk, IT_StkToken tok);
IT_StkToken  IT_popNode(IT_Nodestack *stk);
IT_StkToken  IT_topNode(IT_Nodestack *stk);
void IT_resetNodestack(IT_Nodestack *stk);

ASCIILETTER *IT_point_to_phoneme_string(CONST IT_PhonemeWords *Mdict, U16 index); 
void it_split_inline_morph_phonemes(CONST ASCIILETTER *name, int *comparelength, int *phonestart, int *phonelength, U16 *rule);
void IT_register_word_part(IT_WalkCNTXT *, ASCIILETTER *, U16 type, U16 from, U16 to, BOOL action, ASCIILETTER *phone, U16 rule);

IT_walkinfo  IT_GtWalkerLinear(IT_WalkCNTXT *cntxt, U16 curr, IT_walkinfo oldwalki, int NST);
void IT_process_rule(IT_Morpheme *,IT_Morpheme *,IT_Morpheme *,IT_Morpheme *,IT_Morpheme *);
//BOOL IT_morphemize_word(CONST ASCIILETTER *, ASCIILETTER *, ASCIILETTER *, IT_WalkCNTXT *, CONST IT_wordgrammarinfo *);
BOOL IT_analyse_word(CONST ASCIILETTER *, ASCIILETTER *, ASCIILETTER *, IT_WalkCNTXT *, CONST IT_wordgrammarinfo *);

#ifndef BACHUS_IN_DECTALK
BOOL morphemize_phrase(CONST ASCIILETTER *, ASCIILETTER *, ASCIILETTER *, IT_WalkCNTXT *, CONST IT_wordgrammarinfo *);
#endif

void IT_concat_morphems_phonemes(ASCIILETTER *, IT_MorphemeStruct *, CONST int);

BOOL IT_is_a_consonantgrapheme(ASCIILETTER c);
BOOL IT_is_a_vowelgrapheme(ASCIILETTER c);

#define XTERMRESET           0
#define XTERMBRIGHT          1
#define XTERMDIM             2
#define XTERMUNDERLINE       3
#define XTERMBLINK           4
#define XTERMREVERSE         7
#define XTERMHIDDEN          8

#define XTERMBLACK           0
#define XTERMRED             1

#define XTERMGREEN           2
#define XTERMYELLOW          3
#define XTERMBLUE            4
#define XTERMMAGENTA         5
#define XTERMCYAN            6
#define XTERMWHITE           7

#define XTERMFGCOLOR 7
#define XTERMBGCOLOR 0

void textcolor(int attr, int fg, int bg);

#define MAX_BACHUSLETTERS 120

#include "syllableit.h"

#endif   // _Builder_h
