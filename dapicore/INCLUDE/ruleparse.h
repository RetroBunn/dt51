#ifndef _RULEPARSER_H_
#define _RULEPARSER_H_
/* avoid multiple inclusions */

//moved to port.h for each platform - mlt
//#include<stdio.h>
//#include<stdlib.h>

#include "bachusit.h"

/* The following structure is used by lex and yacc to keep new names. They
   are put in there by lex.
*/

//moved to port.h for each platform - mlt
//#ifndef _UNIX_LIKE_
//typedef unsigned char CHAR;
//#endif

//#define RULEPARSER_MAIN
#define IT_NSYMS 5000	/* maximum number of symbols */
#define IT_NRULESYMS 5000
#define IT_NMAXMORPHS 10000  /* maximum number of morph strings in grammar */

#ifdef RULEPARSER_MAIN
struct symtab {
	char *name;
	int  value;
} symtab[IT_NSYMS];
#endif

typedef enum assemblercodes
{
    INITIALIZERULES,
    SETDECLARE,
    ENDSET,
    REPLACERULE,
    ALWAYSCOND,
    ENVEMPTY,
    ENVSTART,
    ENVSTOP,
    LEFTENVSTART,
    LEFTENVSTOP,
    RIGHTENVSTART,
    RIGHTENVSTOP,
    SEQSTART,
    SEQSTOP,
    ENVNAME,
    ENVMORPH,
    MORPHINSYMLIST,
    NAMEINSYMLIST
} asmbcode;

void asmb(asmbcode, char *, char *);

#define LIST 1
#define STRING 2
#define LIST_HEADER 3
#define REPLACE_RULE 4

struct list_s {
    struct list_s *next;
    int nextindex;
    int type;
    union {
	int stringpos;
	void *list_header;
    } data;
};

typedef struct list_s list_t;

typedef struct list_header_s
{
    list_t *list;
    char *name;
} list_header_t;


typedef struct replace_rules_s 
{
    int from;
    int to;
    list_header_t *leftenv;
    list_header_t *rightenv;
} replace_rule;


typedef struct _list_tab
{
    int next;
    int type;
    int data;
} listtable ;

typedef struct _rule_tab
{
    int from;
    int to;
    int leftenv;
    int rightenv;
} ruletable;

typedef struct _rule_block 
{
    const char*	CONSTCONST*sympool;
    const listtable   *list;
    const ruletable   *rule;
    int         nrules;
} ruleblock;

//#ifdef RULEPARSER_MAIN	//already inside same ifdef
list_t *InitListNode(void);
list_header_t *NewListHeader(char *name);
int NewItemListHeader(list_header_t *list_header,list_header_t *data);
int NewItemString(list_header_t *list_header,char *data);
int NewItemListLeftHeader(list_header_t *list_header,list_header_t *data);
int NewItemLeftString(list_header_t *list_header,char *data);
list_header_t *GetListheader(list_header_t *list,char *name);
void dump_replace_rules(void);
int sympoollook(char *s);
void dumpsympool(void);
int init_list_table(void);
void dump_rule_table(void);
void dump_list_table(void);
void write_list_table_to_file(const char *, const char *);
int fill_list_table(list_t *list);
int dump_list(list_t *list);
#ifdef REINER_TRICK
typedef 
struct _The_Dectalk_structure
{
    int magic_environ;
#ifdef CASIO_SH3
    IT_WalkCNTXT *IT_Walkercntxt;
#endif
}
PLTS;

typedef PLTS* PLTS_T;
#else
#include "port.h"
#include "ls_defs.h"
#include "ls_data.h"
#endif //REINER_TRICK
//#endif //RULEPARSER_MAIN	// already inside same ifdef

/* execrules.c */
int string_matches(const ruleblock *R, int indx, char *word, int pos);
int list_matches(const ruleblock *R, int indx, char *word, int pos);
int checkseqright(char *word, int seqpos, int inlistpos, const ruleblock *R);
int left_string_matches(const ruleblock *R, int indx, char *word, int pos);
int left_list_matches(const ruleblock *R, int indx, char *word, int pos);
int checkseqleft(char *word, int seqpos, int inlistpos, const ruleblock *R);
int check_rule_environment(char *word,int wordlength, int currpos,int lenfrom,const ruleblock *R, const ruletable *rule);
int apply_replace_rules_to_str(char *word, char *outword, const ruleblock *R, int skipmethod);

/* userules.c */




void match_seperators(char *word, char *pattern, char *outword);
int IT_stress_type_from_verb_grammar(char *word, char *outword, int *rafforze,int *preposition, IT_WalkCNTXT *wcnt, const IT_wordgrammarinfo *verbgramm);
int IT_type_from_verb_grammar(char *word, char *outword, int *rafforze,int *preposition, char *type, IT_WalkCNTXT *wcnt, const IT_wordgrammarinfo *verbgramm);
void apply_found_stress(int stressshould, int rafforze, int preposition, char *phonemes, char *outphonemes);
void remove_deletion_marker(char *in, char *out);
char italian_tolower(char foo);
int italian_phonotactics(char *word, char *junk,IT_WalkCNTXT *);
int spell_it_single_letter(char foo, char *outphonemes, char *junk, PLTS_T  pLts_t);
int spell_it_letterbyletter(char *word, char *outphonemes, char *junk, PLTS_T  pLts_t);
int italian_word_lts_normal(char *, char *, char *, PLTS_T);
int italian_word_classify(char *inword, char *outphonemes, char *type, PLTS_T pLts_t);
int italian_word_lts(char *inword, char *outphonemes,char *junkbuffer, PLTS_T);  
/* note:  junkbuffer[MAXRULEALLBUFFERLENGTH] required */



struct symtab *symlook();
//#endif //RULEPARSER_MAIN

#endif /* _RULEPARSER_H_ */
