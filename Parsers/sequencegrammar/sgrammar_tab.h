typedef union{
  int ival;
  char oper;
  char *string;
  struct symtab *sympt;
} YYSTYPE;
#define	NAME	258
#define	COMMENTLINE	259
#define	LTRIE	260
#define	TRIE	261
#define	RTRIE	262
#define	PROCESS	263
#define	TRIEFILE	264
#define	ENDTRIE	265
#define	MORPH	266
#define	SKIPWORD	267
#define	SKIPLETTER	268
#define	ENDSIN	269
#define	EMPTYNODE	270
#define	SEQOR	271
#define	SEQAND	272
#define	SEQNOT	273
#define	SEQ	274
#define	DEF	275
#define	FILENAME	276
#define	BOUND	277
#define	OPERATOR	278
#define	INTEGER	279
#define	LBRAK	280
#define	RBRAK	281


extern YYSTYPE yylval;
