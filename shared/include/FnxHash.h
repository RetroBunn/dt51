/*H_HEADER_FILE***************************************************************
FILE        : hash.h
DESC        : 
TABS        : 3
OWNER       : 
DATE CREATED: 

(C) Copyright 1999 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/26/03 4:12p $
  $Revision: 3 $

*END_HEADER******************************************************************/
#ifndef HASH_H
#define HASH_H
#include "FnxPlatform.h" /* Definition of SDWORD */

typedef struct H_HashEntry {
   struct H_HashEntry *nextPtr;      /* Pointer to next entry in this
                                      * hash bucket, or NULL for end of
                                      * chain. */
   struct H_HashTable *tablePtr;     /* Pointer to table containing entry. */
   struct H_HashEntry **bucketPtr;   /* Pointer to bucket that points to
                                      * first entry in this entry's chain:
                                      * used for deleting the entry. */

   void *clientData;                /* Application stores something here
                                      * with H_SetHashValue. */

   union {                           /* Key has one of these forms: */
      char *oneWordValue;            /* One-word value for key. */
      SDWORD words[1];                  /* Multiple integer words for key.
                                      * The actual size will be as large
                                      * as necessary for this table's
                                      * keys. */
      char string[4];                /* String for key.  The actual size
                                      * will be as large as needed to hold
                                      * the key. */
   } key;                            /* MUST BE LAST FIELD IN RECORD!! */
} H_HashEntry;

/*
 * Structure definition for a hash table.  Must be in tcl.h so clients
 * can allocate space for these structures, but clients should never
 * access any fields in this structure.
 */
 
#define H_SMALL_HASH_TABLE 4
typedef struct H_HashTable {
  H_HashEntry **buckets;            /* Pointer to bucket array.  Each
                                     * element points to first entry in
                                     * bucket's hash chain, or NULL. */
  /* Bucket array used for small tables (to avoid mallocs and frees). */
  H_HashEntry *staticBuckets[H_SMALL_HASH_TABLE];
  SDWORD numBuckets;                     /* Total number of buckets allocated at **bucketPtr. */
  SDWORD numEntries;                     /* Total number of entries present in table. */
  SDWORD rebuildSize;                    /* Enlarge table when numEntries gets to be this large. */
  SDWORD downShift;                      /* Shift count used in hashing 
                                       * function.  Designed to use high-
                                       * order bits of randomized keys. */
  SDWORD mask;                           /* Mask value used in hashing function. */
  SDWORD keyType;                        /* Type of keys used in this table. 
                                       * It's either H_STRING_KEYS,
                                       * H_ONE_WORD_KEYS, or an integer
                                       * giving the number of ints that
                                       * is the size of the key. */
  H_HashEntry *(*findProc)(struct H_HashTable *tablePtr, char *key);
  H_HashEntry *(*createProc)(struct H_HashTable *tablePtr,
              char *key, SDWORD *newPtr);
} H_HashTable;

/*
 * Structure definition for information used to keep track of searches
 * through hash tables:
 */
 
typedef struct H_HashSearch {
  H_HashTable *tablePtr;            /* Table being searched. */
  SDWORD nextIndex;                      /* Index of next bucket to be
                   * enumerated after present one. */
  H_HashEntry *nextEntryPtr;        /* Next entry to be enumerated in the
                 * the current bucket. */
} H_HashSearch;
 
/*
 * Acceptable key types for hash tables:
 */
 
#define H_STRING_KEYS         0
#define H_ONE_WORD_KEYS       1
 
/*
 * Macros for clients to use to access fields of hash entries:
 */
 
#define H_GetHashValue(h) ((h)->clientData)
#define H_SetHashValue(h, value) ((h)->clientData = (void *) (value))
#define H_GetHashKey(tablePtr, h) \
((char *) (((tablePtr)->keyType == H_ONE_WORD_KEYS) ? (h)->key.oneWordValue \
      : (h)->key.string))

  /*
 * Macros to use for clients to use to invoke find and create procedures
 * for hash tables:
 */
 
#define H_FindHashEntry(tablePtr, key) (*((tablePtr)->findProc))(tablePtr, key)
#define H_CreateHashEntry(tablePtr, key, newPtr) (*((tablePtr)->createProc))(tablePtr, key, newPtr)

#ifdef DOING_DLL
FNX_EXPORT(void,H_DeleteHashEntry(H_HashEntry *entryPtr));
FNX_EXPORT(void,H_DeleteHashTable(H_HashTable *tablePtr));
FNX_EXPORT(H_HashEntry,*H_FirstHashEntry(H_HashTable *tablePtr, H_HashSearch *searchPtr));
FNX_EXPORT(char,*H_HashStats(H_HashTable *tablePtr));
FNX_EXPORT(void,H_InitHashTable(H_HashTable *tablePtr, SDWORD keyType));
FNX_EXPORT(H_HashEntry,*H_NextHashEntry(H_HashSearch *searchPtr));
#else
extern void H_DeleteHashEntry(H_HashEntry *entryPtr);
extern void H_DeleteHashTable(H_HashTable *tablePtr);
extern H_HashEntry *H_FirstHashEntry(H_HashTable *tablePtr, H_HashSearch *searchPtr);
extern char *H_HashStats(H_HashTable *tablePtr);
extern void H_InitHashTable(H_HashTable *tablePtr, SDWORD keyType);
extern H_HashEntry *H_NextHashEntry(H_HashSearch *searchPtr);
#endif

#endif
