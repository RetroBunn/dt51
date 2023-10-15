/*H_HEADER_FILE***************************************************************
FILE        : FnxByteOrder.h
DESC        : Function prototypes for routines to read, write and convert values to/from Network Byte Order
TABS        : 3
OWNER       : Fonix
DATE CREATED: 

(C) Copyright 1999,2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

*END_HEADER******************************************************************/
#ifndef FNXHUFFMAN_H
#define FNXHUFFMAN_H

#include "FnxPlatform.h"
#include "FnxLlist.h"
#include "FnxHash.h"
#include "FnxVocab.h"

typedef struct
{
   UDWORD uiStart;      /* Lowest value of elements in this table (right-padded with 0's to max code length) */
   UDWORD uiCodeLength; /* Length of codes in this table */
   UDWORD uiFirstSymbol;/* Index in pwSymbolIndices[] of the first symbol that has this code length
                           NOTE: All symbols with this code length must be adjacent in pwSymbolIndices[]! */
   UDWORD uiPatternMask;/* 32-bit value with the upper 'uiCodeLength' bits set to 1 */
} CodeLengthTable, *CodeLengthTablePtr;

typedef struct
{
   SWORD wNumSymbols;      /* Number of symbols (including final symbol, which is "end-of-string") */
   SWORD wNumUsed;         /* Number of symbols used in Huffman tree (i.e., doesn't include those used only
                             in NGram references) */
   SWORD *pwSymbolIndices; /* Array of symbol indices. pwSymbolIndices[] is sorted such
                               that symbols of the same code length are adjacent, and within
                               the list of symbols of the same code length, the indices are in
                               numerical order.  Any unused symbols are at the end of the list.
                               If pwSymbolIndices[i]<wNumLiterals, then it is
                               a literal symbol.  Otherwise, it is the NGram ppwNGrams[i-wNumLiterals].
                               If pwSymbolIndices[i]<wNumSeparate, then it is in the set of literal
                               symbols that must be separated from each other by a space. */
   SWORD wNumLiterals;     /* Number of literal strings in psLiterals */
   SWORD wNumSeparate;     /* The first 'wNumSeparate' literals must be separated from each other by spaces */
   /* Symbols: 'wNumLiterals' followed by 'wNumSymbols-wNumLiterals' NGrams.  If a symbol's index
      is >=wNumLiterals, then it is an NGram.  If a symbol's index is >=wNumSeparate, then it does
      not need spaces on either side of it. */
   char **psLiterals;      /* Names of literals */
   SWORD **ppwNGrams;      /* Array of (wNumSymbols-wNumLiterals) NGram symbols.  Each such symbol
                              is represented by "N" (the number of sub-symbols) followed by N subsymbol
                              indices, which can be either literals or NGrams. */                          
   SBYTE  *pcCodeLengths;  /* Array of code bit lengths for each symbol (length of 0 => not used)*/
   SBYTE  cMaxCodeLength;  /* Maximum number of bits in any symbol's encoding (must no greater than 32) */
   SWORD  wEndSymbol;      /* Index of the end-of-string symbol */
   SDWORD iNumTables;      /* Number of sub-tables, one for each different encoding length */
   CodeLengthTablePtr pTables; /* Array of tables, one for each encoding length */
   LinkPoolPtr pLinkPool;  /* Pool of linked-list elements to use in decoding */
   char **psCodeStrings;   /* Array of strings containing code for each symbol (e.g., "011", using ASCII '0' and '1' characters).
                              NULL array=>not generated (yet).  NULL entry => not used (i.e., count of symbol=0)*/
} Huffman, *HuffmanPtr;

typedef struct
{
   char  *sWord;          /* Name of the word */
   SWORD  wNumIndices;    /* Number of symbol indices in each word's list of symbols */
   SWORD *pwSymbolIndices; /* Array of symbol indices for this word */
} TokenWord, *TokenWordPtr;

typedef struct
{
   SDWORD        iNumWords;     /* Number of words in the vocabulary */
   TokenWordPtr *ppTokenWords;  /* Array of pointers to tokenized words */
   BOOL          bSharedStrings;/* Flag for whether the sWord field in each TokenWord
                                   is shared (e.g., points to a string within pVocab)
                                   rather than allocated. TRUE=>don't free it up. */
} TokenVocab, *TokenVocabPtr;

typedef struct _NGramNode
{
   SWORD              wSymbol;   /* Index of the symbol (phone, delimeter, or higher-level NGram) at this node */
   SDWORD             iPosition; /* Position in sorted list of NGrams */
   SDWORD             iCount;    /* Number of times this NGram was found in the vocabulary */
   struct _NGramNode *pNext;     /* Linked list of N-Grams with the same prefix (not including wSymbol) and greater wSymbol */
   struct _NGramNode *pChildren; /* Linked list of N+1-Grams with this NGram as a prefix */
   struct _NGramNode *pParent;   /* Pointer to parent node of this NGram (NULL=>this is the beginning of an NGram) */
   SWORD  wBitLength; /* Number of bits needed to store this NGram (in current configuration) 0=>not used.*/
} NGramNode, *NGramNodePtr;

typedef struct
{
   SWORD    wNumPhones;      /* Number of base phonemes */
   SWORD    wNumDelim;       /* Number of delimeters, including end-of-string */
   SWORD    wNumLiterals;    /* Number of literal symbols=wNumPhones+wNumDelim */
   SWORD    wNumSymbols;     /* Number of symbols (=wNumDelim + number of NGrams defined in ppwNGrams[][]) */
   SWORD    wEndSymbol;      /* Index of the end-of-string symbol */
   BOOL     bNeedSpaces;     /* Flag for whether non-delimeter literals need spaces between them. */
   unsigned char **psSymbolNames; /* Array of wNumLiterals symbol names */
   NGramNodePtr pFirstLevel; /* Array of wNumLiterals starting NGram nodes */
   H_HashTable *pSymbolHash; /* Hash table for terminal symbols (string returns index in pFirstLevel) */
   SWORD    *pwSymbolMap;    /* Mapping from original index to index after removing unused literals. */
   NGramNodePtr *ppNGrams;   /* Array of pointers to all NGrams in the tree.  The first 'iNumUsed' are
                                real symbols, sorted by iCount; then up to 'iNumPotential' are the NGrams
                                that have not yet been checked to see if they help; then up to 'iNumNGrams'
                                are those that HAVE been checked and DON'T help; then up to 'iTotalNGrams'
                                are those that have been deleted as their count was reduced to 0 through
                                the use of other NGrams as symbols. */
   SWORD     **ppwNGrams;    /* Array of (wNumSymbols-wNumLiterals) NGram descriptions.  Each such description
                                is represented by "N" (the number of sub-symbols) followed by N subsymbol
                                indices, which can be either literals or NGrams. */                          
   SDWORD    iMaxNGramLength;/* Max 'N' allowed for any NGram symbol. (0=>use all lengths)
                                (The NGram tree is built twice as deep as this to preserve
                                context, but only NGrams up to this length are checked for
                                inclusion in the final NGram list). */
   SDWORD      iTotalNGrams; /* Total number of NGrams allocated in ppNGrams[] */
   SDWORD      iNumNGrams;   /* Number of NGrams not yet removed from tree */
   SDWORD      iNumPotential;/* Number of NGrams either used as symbols or not yet checked */
   SDWORD      iNumUsed;     /* Number of NGrams used as symbols */
   NGramNodePtr *ppSymbolNGrams;/*Array[iNumUsed] of pointers to the NGram node for each symbol */
   PoolPtr     pNGramPool;   /* Pool of NGram nodes to use */
   LinkPoolPtr pLinkPool;    /* Pool of linked list nodes to use */
} NGramTree, *NGramTreePtr;

/* Note: wNumPhones + wNumDelim     = wNumLiterals;
         wNumSymbols - wNumLiterals = #NGram definitions in ppwNGrams[]
         wNumSymbols - iNumUsed     = #symbols with a count=0 (=> used in NGram definitions by not directly in dictionary)
*/

void          FreePointerList(llistPtr *ppLink, LinkPoolPtr pLinkPool);
void          FreeNGramTree(NGramTreePtr pNGramTree);
NGramTreePtr  InitNGrams(char **psPhones, SDWORD iNumPhones, char *sDelimeters, char cEndOfString, BOOL bNeedSpaces);
void          AddNGrams(NGramTreePtr pNGramTree, SWORD *pwSymbols, SDWORD iNumIndices);
NGramTreePtr  BuildVocabNGrams(VocabTPtr pVocab, TokenVocabPtr *ppTokenVocab);
char        **ReadSymbolList(char *sFilename, SDWORD *piNumWords);
llistPtr      ExtractTTSSymbols(char *sPronunciation, H_HashTable *pSymbolHash, LinkPoolPtr pLinkPool);
NGramTreePtr  BuildTTSNGrams(char *sVocabFileName, char **psSymbols, SDWORD iNumSymbols, TokenVocabPtr *ppTokenVocab);
void          FreeHuffman(HuffmanPtr pHuffman);
HuffmanPtr    NGramToHuffman(NGramTreePtr pNGramTree);
HuffmanPtr    SelectNGrams(NGramTreePtr pNGramTree);
void          BuildHuffmanCodeStrings(HuffmanPtr pHuffman);
UBYTE        *HuffmanEncode(HuffmanPtr pHuffman, SWORDPTR pwSymbolStream, SDWORD iNumIndices, SDWORD *piNumBytes);
SDWORD        DecodeUntilMismatch(char *sWord, HuffmanPtr pHuffman, FILE *fp, UBYTE *pBytes, SDWORDPTR piBytesRead);
SWORDPTR      DecodeBitStream(HuffmanPtr pHuffman, FILE *fp, UBYTE *pBytes, SDWORDPTR piBytesRead, SDWORDPTR piListSize);
void          FreeTokenVocab(TokenVocabPtr pTokenVocab);
NGramTreePtr  TokenizeSpellings(TokenVocabPtr pTokenVocab);
void          MapVocabSymbols(NGramTreePtr pNGramTree, TokenVocabPtr pTokenVocab);
SDWORD        WriteHuffman(FILE *fp, HuffmanPtr pHuffman);
HuffmanPtr    ReadHuffman(FILE *fp);
SDWORD        WriteEncodedTokens(FILE *fp, HuffmanPtr pHuffman, TokenVocabPtr pTokenVocab);
SDWORD        SymbolLength(HuffmanPtr pHuffman, SWORD wSymbol, BOOL *pbPrevSep);
char         *TokensToString(HuffmanPtr pHuffman, SWORDPTR pwSymbolIndices, SWORD wNumSymbols);
TokenVocabPtr ReadEncodedTokens(FILE *fp, HuffmanPtr pHuffman, BOOL bMakeString, BOOL bFreeSymbols);
char        **ReadEncodedStringList(FILE *fp, SDWORDPTR piNumStrings);
SDWORD        WriteEncodedStringList(FILE *fp, char **psStrings, SDWORD iNumStrings);

#endif
