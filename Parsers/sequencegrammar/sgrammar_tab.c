
/*  A Bison parser, made from sgrammar.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

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

#line 1 "sgrammar.y"

#define  _this_is_main_sgrammar_
#include "sgrammar.h"
#include <string.h>
#include <stdio.h>

#line 7 "sgrammar.y"
typedef union{
  int ival;
  char oper;
  char *string;
  struct symtab *sympt;
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		139
#define	YYFLAG		-32768
#define	YYNTBASE	43

#define YYTRANSLATE(x) ((unsigned)(x) <= 281 ? yytranslate[x] : 76)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    40,     2,     2,     2,    35,    36,     2,     2,
     2,     2,    27,    38,    28,    29,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    31,    30,     2,
    32,    41,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    37,     2,    39,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    33,    42,    34,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     6,    10,    11,    15,    16,    20,    22,
    28,    29,    36,    37,    44,    45,    49,    50,    53,    55,
    56,    61,    65,    66,    71,    72,    77,    78,    82,    83,
    88,    90,    94,   102,   105,   109,   111,   112,   118,   120,
   121,   122,   128,   129,   133,   137,   138,   143,   145,   147,
   149,   151,   153,   155,   157,   159,   161,   166,   167,   177,
   178,   186,   187,   195,   200,   205,   213,   216,   220
};

static const short yyrhs[] = {    44,
     0,    43,    44,     0,     0,    48,    45,    30,     0,     0,
    62,    46,    30,     0,     0,    75,    47,    30,     0,     4,
     0,    20,    31,     3,    32,    21,     0,     0,    20,    31,
     3,    31,    49,    52,     0,     0,    19,    31,     3,    31,
    50,    52,     0,     0,    19,    51,    52,     0,     0,    53,
    55,     0,    60,     0,     0,    52,    29,    54,    55,     0,
    52,    29,    60,     0,     0,    55,    16,    56,    55,     0,
     0,    55,    17,    57,    55,     0,     0,    18,    58,    55,
     0,     0,    33,    59,    55,    34,     0,    61,     0,    35,
    22,    35,     0,    36,     3,    37,    24,    38,    24,    39,
     0,    36,     3,     0,    40,    36,     3,     0,     3,     0,
     0,     3,    32,    41,    63,    64,     0,    68,     0,     0,
     0,    68,    65,    42,    66,    64,     0,     0,    42,    67,
    64,     0,    68,    27,    68,     0,     0,    68,    28,    69,
    68,     0,    70,     0,    71,     0,     3,     0,    11,     0,
    22,     0,    23,     0,    15,     0,    12,     0,    13,     0,
    14,    33,     3,    34,     0,     0,    25,    72,    68,    26,
    37,    24,    38,    24,    39,     0,     0,     3,    73,    37,
    24,    38,    24,    39,     0,     0,    13,    74,    37,    24,
    38,    24,    39,     0,     6,     3,    32,    21,     0,     7,
     3,    32,    21,     0,     5,    29,    24,    29,     3,    32,
    21,     0,     8,     3,     0,     9,    32,    21,     0,    10,
     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    24,    25,    27,    28,    28,    29,    29,    30,    30,    32,
    35,    35,    36,    38,    39,    41,    43,    43,    44,    45,
    45,    46,    48,    49,    49,    50,    50,    51,    51,    53,
    54,    56,    57,    60,    61,    63,    65,    68,    69,    70,
    70,    71,    71,    72,    73,    74,    74,    75,    76,    77,
    78,    79,    80,    81,    82,    83,    85,    87,    87,    88,
    88,    89,    89,    91,    92,    93,    94,    95,    96
};

static const char * const yytname[] = {   "$","error","$undefined.","NAME","COMMENTLINE",
"LTRIE","TRIE","RTRIE","PROCESS","TRIEFILE","ENDTRIE","MORPH","SKIPWORD","SKIPLETTER",
"ENDSIN","EMPTYNODE","SEQOR","SEQAND","SEQNOT","SEQ","DEF","FILENAME","BOUND",
"OPERATOR","INTEGER","LBRAK","RBRAK","'+'","'-'","'.'","';'","':'","'='","'{'",
"'}'","'%'","'&'","'['","','","']'","'!'","'>'","'|'","STATEMENT","RULE","@1",
"@2","@3","SEQUENCEDECL","@4","@5","@6","SEQUENCE","@7","@8","SEQEXPRESSION",
"@9","@10","@11","@12","SEQOTHER","WORDGRAMMARNAME","RULEDECLARATION","@13",
"RIGHTSIDE","@14","@15","@16","EXPRESSION","@17","ENDSINFORM","REPEATED","@18",
"@19","@20","DECLARATION",""
};
#endif

static const short yyr1[] = {     0,
    43,    43,    45,    44,    46,    44,    47,    44,    44,    48,
    49,    48,    50,    48,    51,    48,    53,    52,    52,    54,
    52,    52,    56,    55,    57,    55,    58,    55,    59,    55,
    55,    60,    60,    60,    60,    61,    63,    62,    64,    65,
    66,    64,    67,    64,    68,    69,    68,    68,    68,    68,
    68,    68,    68,    68,    68,    68,    70,    72,    71,    73,
    71,    74,    71,    75,    75,    75,    75,    75,    75
};

static const short yyr2[] = {     0,
     1,     2,     0,     3,     0,     3,     0,     3,     1,     5,
     0,     6,     0,     6,     0,     3,     0,     2,     1,     0,
     4,     3,     0,     4,     0,     4,     0,     3,     0,     4,
     1,     3,     7,     2,     3,     1,     0,     5,     1,     0,
     0,     5,     0,     3,     3,     0,     4,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     4,     0,     9,     0,
     7,     0,     7,     4,     4,     7,     2,     3,     1
};

static const short yydefact[] = {     0,
     0,     9,     0,     0,     0,     0,     0,    69,    15,     0,
     0,     1,     3,     5,     7,     0,     0,     0,     0,    67,
     0,     0,    17,     0,     2,     0,     0,     0,    37,     0,
     0,     0,    68,     0,     0,     0,     0,    16,     0,    19,
     0,     4,     6,     8,     0,     0,    64,    65,    13,     0,
    34,     0,    20,    36,    27,    29,    18,    31,    11,     0,
    50,    51,    55,    56,     0,    54,    52,    53,    58,    43,
    38,    39,    48,    49,     0,    17,    32,     0,    35,     0,
    22,     0,     0,    23,    25,    17,    10,     0,     0,     0,
     0,     0,     0,    46,     0,     0,    14,     0,    21,    28,
     0,     0,     0,    12,     0,     0,     0,     0,    44,    45,
     0,    41,    66,     0,    30,    24,    26,     0,     0,    57,
     0,    47,     0,     0,     0,     0,     0,    42,    33,     0,
     0,     0,    61,    63,     0,     0,    59,     0,     0
};

static const short yydefgoto[] = {    11,
    12,    26,    27,    28,    13,    86,    76,    23,    38,    39,
    80,    57,   102,   103,    82,    83,    40,    58,    14,    45,
    71,    95,   123,    92,    72,   111,    73,    74,    91,    88,
    89,    15
};

static const short yypact[] = {    65,
   -26,-32768,    -2,    37,    46,    58,    12,-32768,    31,    32,
    47,-32768,-32768,-32768,-32768,    24,    40,    48,    50,-32768,
    57,    76,    41,    80,-32768,    56,    59,    60,-32768,    62,
    66,    67,-32768,    61,    71,    91,    63,    68,     0,-32768,
   -16,-32768,-32768,-32768,    -3,    92,-32768,-32768,-32768,    69,
    64,    93,    41,-32768,-32768,-32768,    42,-32768,-32768,    77,
    70,-32768,-32768,    72,    73,-32768,-32768,-32768,-32768,-32768,
-32768,   -14,-32768,-32768,    78,    41,-32768,    79,-32768,     0,
-32768,     0,     0,-32768,-32768,    41,-32768,    74,    75,    97,
    23,    -3,    23,-32768,    81,    84,    68,    82,    42,-32768,
    26,     0,     0,    68,    89,    90,    83,     3,-32768,    87,
    23,-32768,-32768,    94,-32768,-32768,-32768,    86,    88,-32768,
    85,-32768,    -3,    95,   101,   103,   104,-32768,-32768,    96,
    98,   100,-32768,-32768,   105,   102,-32768,   108,-32768
};

static const short yypgoto[] = {-32768,
   110,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   -69,-32768,
-32768,   -78,-32768,-32768,-32768,-32768,    49,-32768,-32768,-32768,
   -91,-32768,-32768,-32768,   -70,-32768,-32768,-32768,-32768,-32768,
-32768,-32768
};


#define	YYLAST		141


static const short yytable[] = {    61,
   109,    99,    54,   100,   101,    16,    97,    62,    63,    64,
    65,    66,    93,    94,    59,    60,   104,    55,    67,    68,
   108,    69,   110,   116,   117,    61,    17,   -40,   121,    93,
    94,   128,    56,    62,    63,    64,    65,    66,    70,    18,
   122,    84,    85,    21,    67,    68,   138,    69,    19,     1,
     2,     3,     4,     5,     6,     7,     8,    84,    85,   115,
    20,    22,    24,    30,    29,     9,    10,     1,     2,     3,
     4,     5,     6,     7,     8,    35,    36,    33,    34,    31,
    37,    32,    41,     9,    10,    42,    47,    48,    43,    44,
    46,    49,    50,    51,    75,    79,    53,    87,    52,   107,
    78,    81,    98,    77,   113,    90,   -60,   139,   -62,    96,
   105,   106,   118,   119,    94,     0,   120,   124,     0,   114,
    25,   127,   112,   125,   130,   126,   131,   132,   136,     0,
     0,     0,     0,   129,   133,     0,   134,   135,     0,     0,
   137
};

static const short yycheck[] = {     3,
    92,    80,     3,    82,    83,    32,    76,    11,    12,    13,
    14,    15,    27,    28,    31,    32,    86,    18,    22,    23,
    91,    25,    93,   102,   103,     3,    29,    42,    26,    27,
    28,   123,    33,    11,    12,    13,    14,    15,    42,     3,
   111,    16,    17,    32,    22,    23,     0,    25,     3,     3,
     4,     5,     6,     7,     8,     9,    10,    16,    17,    34,
     3,    31,    31,    24,    41,    19,    20,     3,     4,     5,
     6,     7,     8,     9,    10,    35,    36,    21,     3,    32,
    40,    32,     3,    19,    20,    30,    21,    21,    30,    30,
    29,    31,    22,     3,     3,     3,    29,    21,    36,     3,
    37,    53,    24,    35,    21,    33,    37,     0,    37,    32,
    37,    37,    24,    24,    28,    -1,    34,    24,    -1,    38,
    11,    37,    42,    38,    24,    38,    24,    24,    24,    -1,
    -1,    -1,    -1,    39,    39,    -1,    39,    38,    -1,    -1,
    39
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 3:
#line 27 "sgrammar.y"
{;
    break;}
case 5:
#line 28 "sgrammar.y"
{;
    break;}
case 7:
#line 29 "sgrammar.y"
{;
    break;}
case 10:
#line 32 "sgrammar.y"
{ make_association(yyvsp[-2].sympt->name,yyvsp[0].string); 
                                             progbuild(SQNC_NEWDEF,yyvsp[-2].sympt->name); 
                                             progbuild(SQNC_SEQFILE,yyvsp[0].string); ;
    break;}
case 11:
#line 35 "sgrammar.y"
{progbuild(SQNC_NEWDEF,yyvsp[-1].sympt->name);;
    break;}
case 12:
#line 35 "sgrammar.y"
{progbuild(SQNC_ENDDEF,0);;
    break;}
case 13:
#line 36 "sgrammar.y"
{ char tmpstr[64];
	                             sprintf(tmpstr,"%s%i",yyvsp[-1].sympt->name,lex_line());
		                     progbuild(SQNC_NEWSEQ,tmpstr);;
    break;}
case 14:
#line 38 "sgrammar.y"
{progbuild(SQNC_ENDSEQ,0);;
    break;}
case 15:
#line 39 "sgrammar.y"
{char tmpstr[64];
	                             sprintf(tmpstr,"line%i",lex_line());
		                     progbuild(SQNC_NEWSEQ,tmpstr);;
    break;}
case 16:
#line 41 "sgrammar.y"
{progbuild(SQNC_ENDSEQ,0);;
    break;}
case 17:
#line 43 "sgrammar.y"
{progbuild(SQNC_EXPR,0);;
    break;}
case 18:
#line 43 "sgrammar.y"
{progbuild(SQNC_EXPREND,0);;
    break;}
case 20:
#line 45 "sgrammar.y"
{progbuild(SQNC_EXPR,0);;
    break;}
case 21:
#line 45 "sgrammar.y"
{progbuild(SQNC_EXPREND,0);;
    break;}
case 23:
#line 48 "sgrammar.y"
{progbuild(SQNC_OR,0);;
    break;}
case 25:
#line 49 "sgrammar.y"
{progbuild(SQNC_AND,0);;
    break;}
case 27:
#line 50 "sgrammar.y"
{progbuild(SQNC_NOT,0);;
    break;}
case 29:
#line 51 "sgrammar.y"
{progbuild(SQNC_PARLEFT,0);;
    break;}
case 30:
#line 53 "sgrammar.y"
{progbuild(SQNC_PARRIGHT,0);;
    break;}
case 32:
#line 56 "sgrammar.y"
{progbuild(SQNC_ACTION,yyvsp[-1].string);;
    break;}
case 33:
#line 57 "sgrammar.y"
{char tmpstr[64];  /* put in temporary string and send to progbuild */
							    sprintf(tmpstr,"%c%c%s",yyvsp[-3].ival+48,yyvsp[-1].ival+48,yyvsp[-5].sympt->name);
                                                            progbuild(SQNC_CITELOOPED,tmpstr);;
    break;}
case 34:
#line 60 "sgrammar.y"
{progbuild(SQNC_CITE,yyvsp[0].sympt->name);;
    break;}
case 35:
#line 61 "sgrammar.y"
{progbuild(SQNC_CITENOT,yyvsp[0].sympt->name);;
    break;}
case 36:
#line 63 "sgrammar.y"
{progbuild(SQNC_WGNAME,yyvsp[0].sympt->name);;
    break;}
case 37:
#line 65 "sgrammar.y"
{  buildtree(STARTNODE,yyvsp[-2].sympt->name,yyvsp[-2].sympt->value,0); 
                                  buildtree(NEWPATH,NULL,lex_line(),0); 
                               ;
    break;}
case 39:
#line 69 "sgrammar.y"
{buildtree(ENDOFPATH,NULL,0,0);;
    break;}
case 40:
#line 70 "sgrammar.y"
{buildtree(ENDOFPATH,NULL,0,0);;
    break;}
case 41:
#line 70 "sgrammar.y"
{buildtree(NEWPATH,NULL,lex_line(),0);;
    break;}
case 43:
#line 71 "sgrammar.y"
{buildtree(NEWPATH,NULL,lex_line(),0);;
    break;}
case 45:
#line 73 "sgrammar.y"
{;
    break;}
case 46:
#line 74 "sgrammar.y"
{buildtree(WORDBOUNDARY,0,0,0);;
    break;}
case 47:
#line 74 "sgrammar.y"
{;
    break;}
case 50:
#line 77 "sgrammar.y"
{ buildtree(RIGHTNODE,yyvsp[0].sympt->name,yyvsp[0].sympt->value,0);;
    break;}
case 51:
#line 78 "sgrammar.y"
{ buildtree(SINGLEMORPH,yyvsp[0].sympt->name,yyvsp[0].sympt->value,0);;
    break;}
case 52:
#line 79 "sgrammar.y"
{ buildtree(BOUNDACTION,yyvsp[0].string,0,0);;
    break;}
case 53:
#line 80 "sgrammar.y"
{ buildtree(OPERATORNAME,yyvsp[0].string,0,0); printf("operator found %s\n",yyvsp[0].string); ;
    break;}
case 54:
#line 81 "sgrammar.y"
{ buildtree(NOPNODE,0,0,0);;
    break;}
case 55:
#line 82 "sgrammar.y"
{ buildtree(SKIPNODE,0,0,0);;
    break;}
case 56:
#line 83 "sgrammar.y"
{ buildtree(SKIPLETTERNODE,0,0,0);;
    break;}
case 57:
#line 85 "sgrammar.y"
{buildtree(ENDSINNODE, yyvsp[-1].sympt->name, yyvsp[-1].sympt->value,0);;
    break;}
case 58:
#line 87 "sgrammar.y"
{buildtree(LOOPNODE,NULL,0,0);;
    break;}
case 59:
#line 87 "sgrammar.y"
{buildtree(JUMPNODE,NULL,yyvsp[-3].ival,yyvsp[-1].ival);;
    break;}
case 60:
#line 88 "sgrammar.y"
{buildtree(LOOPNODE,NULL,0,0); buildtree(RIGHTNODE,yyvsp[0].sympt->name,yyvsp[0].sympt->value,0);;
    break;}
case 61:
#line 88 "sgrammar.y"
{buildtree(JUMPNODE,NULL,yyvsp[-3].ival,yyvsp[-1].ival);;
    break;}
case 62:
#line 89 "sgrammar.y"
{buildtree(LOOPNODE,NULL,0,0); buildtree(SKIPLETTERNODE,0,0,0);;
    break;}
case 63:
#line 89 "sgrammar.y"
{buildtree(JUMPNODE,NULL,yyvsp[-3].ival,yyvsp[-1].ival);;
    break;}
case 64:
#line 91 "sgrammar.y"
{buildtree(TRIENAME,yyvsp[0].string,yyvsp[-2].sympt->value,LONG_MORPH_FIRST); printf("TRIE FILE for symbol %s(%d) is %s\n",yyvsp[-2].sympt->name,yyvsp[-2].sympt->value,yyvsp[0].string);;
    break;}
case 65:
#line 92 "sgrammar.y"
{buildtree(TRIENAME,yyvsp[0].string,yyvsp[-2].sympt->value,LONG_MORPH_LAST); printf("RTRIE FILE for symbol %s(%d) is %s\n",yyvsp[-2].sympt->name,yyvsp[-2].sympt->value,yyvsp[0].string);;
    break;}
case 66:
#line 93 "sgrammar.y"
{buildtree(LTRIENAME,yyvsp[0].string,yyvsp[-2].sympt->value,yyvsp[-4].ival); printf("LTRIE FILE for symbol %s(%d) is %s with arg %i\n",yyvsp[-2].sympt->name,yyvsp[-2].sympt->value,yyvsp[0].string,yyvsp[-4].ival);;
    break;}
case 67:
#line 94 "sgrammar.y"
{buildtree(PROCESSNAME,yyvsp[0].sympt->name,0,0); printf("PROCESS FILE for symbol %s(%d)\n",yyvsp[0].sympt->name,yyvsp[0].sympt->value);;
    break;}
case 68:
#line 95 "sgrammar.y"
{printf(" GENERATES FILE %s\n",yyvsp[0].string);;
    break;}
case 69:
#line 96 "sgrammar.y"
{printf("done\n"); return(1);;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 98 "sgrammar.y"
 

static struct symtab *sp;
struct symtab *
symlook(s)
char *s;
{
	int count;
	count=0;
	for(sp = symtab; sp < &symtab[NSYMS]; sp++)        /* defined in sgrammar.h */
	  {
	    /* is it already here? */
	    count++;
	    if(sp->name && !strcmp(sp->name, s))  return sp;
	    /* is it free */
	    if(!sp->name) {
	      sp->name = strdup(s);
	      sp->value=count;
	      return sp;
	    }
	    /* otherwise continue to next */
	}
	yyerror("Too many symbols");
	exit(1);	/* cannot continue */
} /* symlook */

WalkCNTXT Walkercntxt;  

main(int ac, char **av)
{
//  ASCIILETTER *retbuff;
//  int eofcond=0;
//  int ret;
//  BOOL succ;
  extern FILE *yyin;
  char *nameextension;
//  wordgrammarinfo WGinfo;
  int  ltriecount;
  lettertriename *ltf;
//  FILE *wordsfid;

  numseqcmd =0;

  SequencePile = new_seqpile(100);  // space for a hundred of these.
  AssociationDict = new_stringdictionary();
  SequenceReserve = new_stringdictionary();

  if (ac>1)
    {
      if((yyin = fopen(av[1], "r")) == NULL) 
	{
	perror(av[1]);
	exit(1);
	}
      if (av[2] != NULL) nameextension = av[2];
      else nameextension = SGRAMMARSTRING;
    }
  else
    {
      if((yyin = fopen("experiment.ger", "r")) == NULL) 
	{
	perror(av[1]);
	exit(1);
	}
      nameextension = SGRAMMARSTRING;
    }
 

  //  yyin = fopen("wordgrammar.ger", "r");

  buildtree(INITIALIZE,NULL,0,0);  /* initialize the builder that's called as actions in the grammar, see above.*/


  yyparse();

  for (sp=symtab; sp < &symtab[NSYMS]; sp++) {
    if (sp->name) printf(" %d %s\n",sp->value,sp->name);}

  if (buildtree(DUMPALL,NULL,0,0) == 1)
    {
      make_ltries(); 
      printf("Make ltries was called\n");
    }
  else
    {
      printf("Incomplete grammar - check missing declarations\n");
      exit(1);
    }

  translate_sequences();
  sequence_progbuild("sgrammarsequence.c","comments.h",SequenceReserve);
      
  buildtree(FILEDUMP,nameextension,0,0);
  buildtree(DUMPALL,NULL,0,0);
  ltriecount=0;

 for(ltf = LTrieFiles; ltf < &LTrieFiles[NTRIEFILES]; ltf++) 
    {
      if (ltf->triename)
	{
	  ltriecount++;
	}
    }

 printf("counted %i LTries\n",ltriecount);
 //WGinfo.notries = ltriecount; /* not usually used*/

 // WGinfo.nnodes = STGT.nnodes;

#ifdef OLDVERSION_WITH_DIRECT_TEST
#ifdef FROMTYPED

  WGinfo.GtNodes = STGT.Nodes;
  WGinfo.Ltreelist = LTrieList;
  WGinfo.MorphDict = &MorphDict;
  


   while (!eofcond)
    {
      printf("SGRAMMAR>");
/*      ret = scanf("%s",bp); */
      retbuff = fgets(bp,80,stdin);
      if (retbuff==NULL || strlen(retbuff)<=1)
	{
	  eofcond=1;
	}
      else
	{
	  ret = strlen(retbuff);
	  // printf("ret = %i\n",ret);
	  if (ret>0)  retbuff[ret-1]='\0';
	  if (ret==0)
	  {
	      eofcond=1;
	      break;
	  }
	  //  printf("  %s\n",retbuff);
	  //  walk_word(bp,&STGT,LTrieList,&MorphDict);
	  //  succ = morphemize_word(bp,outword,outphones, &WGinfo,&HyphenTOK);
	  succ = morphemize_phrase(retbuff,outword,outphones, &Walkercntxt, &WGinfo);

	  // if (succ) printf("%s [%s] -> /%s/ \n",retbuff,outword,outphones);
	  // else printf("## %s\n",retbuff);
	}
    }
#else
   wordsfid = fopen(av[2], "r");
   if (wordsfid == NULL)
     {
       printf("could not open file\n");
       exit(1);
     }
   while (!eofcond)
     {
       ret = fscanf(wordsfid,"%s",bp);
       if (strlen(bp)==0 | ret <= 0)
	 {
	   eofcond=1;
	 }
       else
	 {
	   //	   printf("%s\n",bp);
	  succ = morphemize_word(bp,outword,outphones, &WGinfo,&HyphenTOK);
	  //if (succ) printf("%s [%s] -> /%s/ \n",bp,outword,outphones);
	  //else printf("## %s\n",bp);	  
	 }
     }
#endif
#endif  // OLDVERSION_WITH_DIRECT_TEST

#ifndef FROMTYPED
#ifdef GRAMMAR_EVALUATION
buildtree(STATISTICS,NULL,0,0);   // print how often a rule was used
#endif
#endif

}

yyerror(char *s)
{
  fprintf(stderr, "Error parsing line %d columns %d-%d : %s\n",lex_line(),lex_lastcol(),lex_column(), s);
}

