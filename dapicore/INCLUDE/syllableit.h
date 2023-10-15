#ifndef SYLLABLESTRUCTUREDEFINED
#define SYLLABLESTRUCTUREDEFINED

/* Assume that this file is going to be part of the bachus.
 */

/* typedef unsigned short  U16; 
   typedef unsigned short  BOOL;                
   typedef unsigned char UCHAR;  */

#define MAXSYLLABLES 20
#define MAXWORDLENGTH 80
#define MAXSYLLPART 8 
/* structure to describe a range in a letter string where the
   string represents one word 
*/
/*
typedef 
struct char_range
{
    UCHAR  from;
    UCHAR  to;
} 
LRANGE;
*/

typedef 
struct _syllable_stuct
{
    ASKYPHONEME onset[MAXSYLLPART];
    ASKYPHONEME nucleus[MAXSYLLPART];
    ASKYPHONEME coda[MAXSYLLPART];
    ASCIILETTER letonset[MAXSYLLPART];
    ASCIILETTER letnucleus[MAXSYLLPART];
    ASCIILETTER letcoda[MAXSYLLPART];
    BOOL    stressed;
    BOOL    codageminate;
} 
BSYLL;

/*
typedef
struct _syllabified_word
{
    int nsyll;
    int nfreesyll;
    ASCIILETTER  *word;
    ASKYPHONEME *phonemes;
    BSYLL   sbuf[MAXSYLLABLES];           // pointer to pool
    BSYLL   *syll[MAXSYLLABLES]; // pointer array
    BSYLL   syllables[MAXSYLLABLES];  // pool of space
} 
BSYLLWORD;
*/

int rough_syllabify(ASCIILETTER *, BSYLL **);
void Print_syllables(int , BSYLL **);
ASCIILETTER *italian_ascky2arpa(ASKYPHONEME , ASCIILETTER *);
ASCIILETTER *make_syllabified_word(int , BSYLL **, ASCIILETTER *, ASCIILETTER*);
void apply_specific_italian_stress(int,  BSYLL **);
void apply_standard_italian_stress(int,  BSYLL **);
void apply_standard_italian_soundtransformations(int, BSYLL **);
#endif 
