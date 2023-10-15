#ifndef _CH_BUILDER_H_
#define _CH_BUILDER_H_
/* avoid multple inclusions */

#include "chin_bachusdefs.h"

#ifndef BLD_DECTALK_DLL
typedef 
struct _The_Dectalk_structure
{
    int magic_environ;
}
PLTS;
typedef PLTS* PLTS_T;
#endif

#define BACHUS_IN_DECTALK

#ifndef MULTIPLE_LANGUAGES_LOADED

/* max size definitions */
#ifdef CASIO_SH3
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
#endif    /* NOT CASIO */
#endif

/* New: collect phoneme strings that are hung into the grapheme letter tries. */



U16 Lt_parse_string(ASCIILETTER *, U16, const LTrie *, U16 *,U16 *, U16 *,U16);

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


Nodestack newNodestack(void);
void initNodestack(Nodestack *);
BOOL pushNode(Nodestack *, StkToken);
StkToken  popNode(Nodestack *);
StkToken  topNode(Nodestack *);
void resetNodestack(Nodestack *);
void resetNodestack(Nodestack *);


ASCIILETTER *gnodetypename(gnodetype);
#if 0
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
#endif

typedef struct CH_walkerstack
{
    U16 i,j,ii,jj,j1,j2,incr;
    U16 nalt,ntrie,currpos;
    U16 next,alt,what,curr;
    U16 proceed[4];
    U16 phonemeindex[4];
    U16 ruleindex[4];
    U16 opcode, opparam, match; // for operator calls.
    CH_walkinfo newwalki;
    CH_walkinfo oldwalki;
    ASCIILETTER *phonemestring;
    U16 rulenumber;
} 
CH_WALKERNESTINGSTACK;

#ifndef JUMPSTACK_DEFINED
#define JUMPSTACK_DEFINED
typedef char Jumpstack;
#endif

typedef
struct CH_walker_context {
    int   counter;
    int   level;
    int   maxlevel;
    int   alert;
    int   grammar;                  /* usually zero, but used for syllabification has non zero value */
    BOOL  special;                  /* to check a word's special bit. */
    CONST GTrieNode *Nodes;
    U16  nnodes;
    CONST LTrie *Ltlist;               // letter trie list.
    CONST  PhonemeWords *MorphDict;    // structure to hold all morpheme's phoneme strings. 
    Nodestack nstack;
    ASCIILETTER *theword;                // handle this pointer externally. Who knows how long a word might be?
    ASCIILETTER wordchar[MAXLETTERBUFLENGTH];
    ASCIILETTER workbuffer[MAXLETTERBUFLENGTH];
    MorphemeStruct  Morphstruct;
    U16 wordlength;
    U16 wordpos;
    CH_WALKERNESTINGSTACK STK[MAXNESTING];
    Jumpstack jmpstack[MAXNESTING];
    int       jmptop;
} CH_WalkCNTXT;



typedef struct CH_bachus_global_information{
  CONST  U16            nnodes;
  CONST  GTrieNode     *GtNodes;
  CONST  U16            notries;
  CONST  LTrie         *Ltreelist;
  CONST  PhonemeWords  *MorphDict; 
}
CHIN_wordgrammarinfo;


void make_ltries(void);

BOOL pushNode(Nodestack *stk, StkToken tok);
StkToken  popNode(Nodestack *stk);
StkToken  topNode(Nodestack *stk);
void resetNodestack(Nodestack *stk);

ASCIILETTER *point_to_phoneme_string(const PhonemeWords *Mdict, U16 index); 
void split_inline_morph_phonemes(const ASCIILETTER *name, U16 *comparelength, U16 *phonestart, U16 *phonelength, U16 *rule);
void register_word_part(CH_WalkCNTXT *, ASCIILETTER *, U16 type, U16 from, U16 to, BOOL action, ASCIILETTER *phone, U16 rule);

CH_walkinfo  GtWalkerLinear(CH_WalkCNTXT *cntxt, U16 curr, CH_walkinfo oldwalki, int NST);
void process_rule(Morpheme *,Morpheme *,Morpheme *,Morpheme *,Morpheme *);
BOOL morphemize_word(const ASCIILETTER *, ASCIILETTER *, ASCIILETTER *, CH_WalkCNTXT *, const CHIN_wordgrammarinfo *);
BOOL analyse_word(const ASCIILETTER *, ASCIILETTER *, ASCIILETTER *, CH_WalkCNTXT *, const CHIN_wordgrammarinfo *);

void concat_morphems_phonemes(ASCIILETTER *, MorphemeStruct *, const int, const BOOL);


#define MAX_BACHUSLETTERS 120

// #include "syllableit.h"

#endif   // _CH_Builder_h
