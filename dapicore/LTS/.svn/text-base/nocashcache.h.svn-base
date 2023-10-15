#ifndef  _nocashcache_h_
#define  _nocashcache_h_

//#include <stdlib.h>
//#include <stdio.h>
#include "port.h"

#ifdef USE_NAND
#include "FileSystemDict.h"
#endif

// A structure that represents found information 
//   associated with a request of an ltrie. This is 
//   a bunch of forward linked lists and starts off 
//   as one empty list (see init_foundinfo)


//typedef 
//struct _foundinfo
//{
//    short  next;
//   unsigned short stringoffset;
//   unsigned char  ruleno;
//    unsigned char  length;
//} foundinfo;

#if 0
typedef struct _tagWordSegList
{
    char iLettersUsed;
    char iRule;
    int sPronPtr;
} WORD_SEG_LIST;
#endif

typedef
struct _foundinfo
{
    short  next;
    int  string_handle;
    unsigned char  ruleno;       // bit set if continued
    unsigned char  end_pos;
} foundinfo;

// A structure  which contains  the information 
//   which ltrie was asked at which position of a word.
//   A leaky stack

typedef
struct _ltestinfo
{
    short           next;
    short           prev;
    short           foundinfoindex;   // if negative, nothing stored.
    unsigned char   ltrienumber;
    unsigned char   position;
} ltestinfo;

#define MAXFOUNDINFO 128
#define MAXTESTINFO  64

typedef
struct _ltrie_cache
{
    foundinfo  finfo[MAXFOUNDINFO];
    ltestinfo  ltinfo[MAXTESTINFO];
    short      firstfree;	    // in finfo
    short      lastfree;       // in finfo
    short      nfree;          // free in finfo

    short      ltfirstfree;   
    short      ltfirst;
    short      ltlast;
    short      sizefinfo, sizeltinfo;
} ltrcache;

#define CACHENULLPTR -1

void init_foundinfo(ltrcache *trc, int finfo_length, int ltinfo_length);


#endif  // _nocashcache_h_