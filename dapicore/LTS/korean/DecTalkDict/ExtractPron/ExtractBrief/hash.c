/*C_HEADER_FILE****************************************************************
FILE        :  hash.c
DESC        :  Implementation of in-memory hash tables
TABS        :  3
OWNER       :  Fonix
DATE CREATED:  

 Copyright (c) 1991-1993 The Regents of the University of California.
 Copyright (c) 1994 Sun Microsystems, Inc.

(C) Copyright 1999,2000,2001 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date: 3/22/05 11:20a $
  $Revision: 6 $

*END_HEADER*******************************************************************/

#include "FnxPlatform.h"
#include "FnxAllocate.h"
#include "FnxHash.h"

/*
 * When there are this many entries per bucket, on average, rebuild
 * the hash table to make it larger.
 */

#define REBUILD_MULTIPLIER 3


/*
 * The following macro takes a preliminary integer hash value and
 * produces an index into a hash tables bucket list.  The idea is
 * to make it so that preliminary values that are arbitrarily similar
 * will end up in different buckets.  The hash function was taken
 * from a random-number generator.
 */

#define RANDOM_INDEX(tablePtr, i) (((((long) (i))*1103515245) >> (tablePtr)->downShift) & (tablePtr)->mask)

/*
 * Procedure prototypes for static procedures in this file:
 */
  
H_HashEntry *  ArrayFind(H_HashTable *tablePtr,     char *key);
H_HashEntry *  ArrayCreate(H_HashTable *tablePtr,   char *key, SDWORD *newPtr);
H_HashEntry *  BogusFind(H_HashTable *tablePtr,     char *key);
H_HashEntry *  BogusCreate(H_HashTable *tablePtr,   char *key, SDWORD *newPtr);
UDWORD   HashString(char *string);
void     RebuildTable(H_HashTable *tablePtr);
H_HashEntry *  StringFind(H_HashTable *tablePtr,    char *key);
H_HashEntry *  StringCreate(H_HashTable *tablePtr,  char *key, SDWORD *newPtr);
H_HashEntry *  OneWordFind(H_HashTable *tablePtr,   char *key);
H_HashEntry *  OneWordCreate(H_HashTable *tablePtr, char *key, SDWORD *newPtr);

/*
 *----------------------------------------------------------------------
 *
 * H_InitHashTable --
 *
 * IN: tablePtr - Pointer to a table record, which is supplied by the caller.
 *     keyType  - Type of keys to use in table: H_STRING_KEYS, H_ONE_WORD_KEYS, or an integer>=2. 
 * Given storage for a hash table, set up the fields to prepare
 * the hash table for use.
 *
 * Results:
 * None.
 *
 * Side effects:
 * TablePtr is now ready to be passed to H_FindHashEntry and
 * H_CreateHashEntry.
 *
 *----------------------------------------------------------------------
 */

void H_InitHashTable(/*register*/ H_HashTable *tablePtr, SDWORD keyType)
{
   tablePtr->buckets = tablePtr->staticBuckets;
   tablePtr->staticBuckets[0] = tablePtr->staticBuckets[1] = 0;
   tablePtr->staticBuckets[2] = tablePtr->staticBuckets[3] = 0;
   tablePtr->numBuckets = H_SMALL_HASH_TABLE;
   tablePtr->numEntries = 0;
   tablePtr->rebuildSize = H_SMALL_HASH_TABLE*REBUILD_MULTIPLIER;
   tablePtr->downShift = 28;
   tablePtr->mask = 3;
   tablePtr->keyType = keyType;
   if (keyType == H_STRING_KEYS) 
   {
      tablePtr->findProc = StringFind;
      tablePtr->createProc = StringCreate;
   }
   else if (keyType == H_ONE_WORD_KEYS) 
   {
      tablePtr->findProc = OneWordFind;
      tablePtr->createProc = OneWordCreate;
   }
   else
   {
      tablePtr->findProc = ArrayFind;
      tablePtr->createProc = ArrayCreate;
   };
}

/*
 *----------------------------------------------------------------------
 *
 * H_DeleteHashEntry --
 *
 * Remove a single entry from a hash table.
 *
 * Results:
 * None.
 *
 * Side effects:
 * The entry given by entryPtr is deleted from its table and
 * should never again be used by the caller.  It is up to the
 * caller to free the clientData field of the entry, if that
 * is relevant.
 *
 *----------------------------------------------------------------------
 */

#ifndef FNX_LEAN_AND_MEAN
void H_DeleteHashEntry(H_HashEntry *entryPtr)
{
   /*register*/ H_HashEntry *prevPtr;
   
   if (*entryPtr->bucketPtr == entryPtr) {
      *entryPtr->bucketPtr = entryPtr->nextPtr;
   } else {
      for (prevPtr = *entryPtr->bucketPtr; ; prevPtr = prevPtr->nextPtr) {
         FNX_ASSERT(prevPtr);
         //DB_Panic("malformed bucket chain in H_DeleteHashEntry");
         if (prevPtr->nextPtr == entryPtr) {
            prevPtr->nextPtr = entryPtr->nextPtr;
            break;
         }
      }
   }
   entryPtr->tablePtr->numEntries--;
   FNX_FREE((char *) entryPtr);
}
#endif

/*
 *----------------------------------------------------------------------
 *
 * H_DeleteHashTable --
 *
 * Free up everything associated with a hash table except for
 * the record for the table itself.
 * In: tablePtr - Table to delete
 * Results:
 * None.
 *
 * Side effects:
 * The hash table is no longer useable.
 *
 *----------------------------------------------------------------------
 */

void H_DeleteHashTable(/*register*/ H_HashTable *tablePtr)
{
   /*register*/ H_HashEntry *hPtr, *nextPtr;
   SDWORD i;
   
   /*
   * Free up all the entries in the table.
   */
   
   for (i = 0; i < tablePtr->numBuckets; i++) 
   {
      hPtr = tablePtr->buckets[i];
      while (hPtr != NULL) 
      {
         nextPtr = hPtr->nextPtr;
         FNX_FREE((char *) hPtr);
         hPtr = nextPtr;
      }
   }
   
   /*
   * Free up the bucket array, if it was dynamically allocated.
   */
   
   if (tablePtr->buckets && tablePtr->buckets != tablePtr->staticBuckets) 
   {
      FNX_FREE((char *) tablePtr->buckets);
   }
   
   /*
   * Arrange for panics if the table is used again without
   * re-initialization.
   */
   
   tablePtr->findProc = BogusFind;
   tablePtr->createProc = BogusCreate;
}

/*
 *----------------------------------------------------------------------
 *
 * H_FirstHashEntry --
 *
 * Locate the first entry in a hash table and set up a record
 * that can be used to step through all the remaining entries
 * of the table.
 * tablePtr - Table to search.
 * searchPtr - Place to store information about progress through the table.
 *
 * Results:
 * The return value is a pointer to the first entry in tablePtr,
 * or NULL if tablePtr has no entries in it.  The memory at
 * *searchPtr is initialized so that subsequent calls to
 * H_NextHashEntry will return all of the entries in the table,
 * one at a time.
 *
 * Side effects:
 * None.
 *
 *----------------------------------------------------------------------
 */

#ifndef FNX_LEAN_AND_MEAN
H_HashEntry *H_FirstHashEntry(H_HashTable *tablePtr, H_HashSearch *searchPtr)
{
    searchPtr->tablePtr = tablePtr;
    searchPtr->nextIndex = 0;
    searchPtr->nextEntryPtr = NULL;
    return H_NextHashEntry(searchPtr);
}
#endif

/*
 *----------------------------------------------------------------------
 *
 * H_NextHashEntry --
 *
 * Once a hash table enumeration has been initiated by calling
 * H_FirstHashEntry, this procedure may be called to return
 * successive elements of the table.
 * In: searchPtr - Place to store information about progress through the table.  Must
                   have been initialized by calling H_FirstHashEntry.
 * Results:
 * The return value is the next entry in the hash table being
 * enumerated, or NULL if the end of the table is reached.
 *
 * Side effects:
 * None.
 *
 *----------------------------------------------------------------------
 */

#ifndef FNX_LEAN_AND_MEAN
H_HashEntry *H_NextHashEntry(/*register*/ H_HashSearch *searchPtr)
{
    H_HashEntry *hPtr;

    while (searchPtr->nextEntryPtr == NULL) {
   if (searchPtr->nextIndex >= searchPtr->tablePtr->numBuckets) {
       return NULL;
   }
   searchPtr->nextEntryPtr =
      searchPtr->tablePtr->buckets[searchPtr->nextIndex];
   searchPtr->nextIndex++;
    }
    hPtr = searchPtr->nextEntryPtr;
    searchPtr->nextEntryPtr = hPtr->nextPtr;
    return hPtr;
}
#endif

/*
 *----------------------------------------------------------------------
 *
 * H_HashStats --
 *
 * Return statistics describing the layout of the hash table
 * in its hash buckets.
 * In: tablePtr - Table for which to produce stats.
 * Results:
 * The return value is a Allocate-ed string containing information
 * about tablePtr.  It is the caller's responsibility to free
 * this string.
 *
 * Side effects:
 * None.
 *
 *----------------------------------------------------------------------
 */

#ifndef FNX_LEAN_AND_MEAN
char *H_HashStats(H_HashTable *tablePtr)
{
#define NUM_COUNTERS 10
    SDWORD count[NUM_COUNTERS], overflow, i, j;
    double average, tmp;
    /*register*/ H_HashEntry *hPtr;
    char *result, *p;

    /*
     * Compute a histogram of bucket usage.
     */

    for (i = 0; i < NUM_COUNTERS; i++) {
   count[i] = 0;
    }
    overflow = 0;
    average = 0.0;
    for (i = 0; i < tablePtr->numBuckets; i++) {
   j = 0;
   for (hPtr = tablePtr->buckets[i]; hPtr != NULL; hPtr = hPtr->nextPtr) {
       j++;
   }
   if (j < NUM_COUNTERS) {
       count[j]++;
   } else {
       overflow++;
   }
   tmp = j;
   average += (tmp+1.0)*(tmp/tablePtr->numEntries)/2.0;
    }

    /*
     * Print out the histogram and a few other pieces of information.
     */

    result = (char *) FNX_MALLOC((unsigned) ((NUM_COUNTERS*60) + 300));
    FNX_SPRINTF(result, "%ld entries in table, %ld buckets\n",
       tablePtr->numEntries, tablePtr->numBuckets);
    p = result + FNX_STRLEN(result);
    for (i = 0; i < NUM_COUNTERS; i++) {
   FNX_SPRINTF(p, "number of buckets with %ld entries: %ld\n",
      i, count[i]);
   p += FNX_STRLEN(p);
    }
    FNX_SPRINTF(p, "number of buckets with %ld or more entries: %ld\n",
       NUM_COUNTERS, overflow);
    p += FNX_STRLEN(p);
    FNX_SPRINTF(p, "average search distance for entry: %.1f", average);
    return result;
}
#endif

/*
 *----------------------------------------------------------------------
 *
 * HashString --
 *
 * Compute a one-word summary of a text string, which can be
 * used to generate a hash index.
 * In: string - String from which to compute hash value.
 *
 * Results:
 * The return value is a one-word summary of the information in
 * string.
 *
 * Side effects:
 * None.
 *
 *----------------------------------------------------------------------
 */

UDWORD HashString(/*register*/ char *string) 
{
    /*register*/ UDWORD result;
    /*register*/ SDWORD c;

    /*
     * I tried a zillion different hash functions and asked many other
     * people for advice.  Many people had their own favorite functions,
     * all different, but no-one had much idea why they were good ones.
     * I chose the one below (multiply by 9 and add new character)
     * because of the following reasons:
     *
     * 1. Multiplying by 10 is perfect for keys that are decimal strings,
     *    and multiplying by 9 is just about as good.
     * 2. Times-9 is (shift-left-3) plus (old).  This means that each
     *    character's bits hang around in the low-order bits of the
     *    hash value for ever, plus they spread fairly rapidly up to
     *    the high-order bits to fill out the hash value.  This seems
     *    works well both for decimal and non-decimal strings.
     */

    result = 0;
    while (1) 
    {
       c = *string;
       string++;
       if (c == 0) 
       {
          break;
       }
       result += (result<<3) + c;
    }
    return result;
}

/*
 *----------------------------------------------------------------------
 *
 * StringFind --
 *
 * Given a hash table with string keys, and a string key, find
 * the entry with a matching key.
 * In: tablePtr - Table in which to lookup entry.
 *     key      - Key to use to find matching entry.
 * Results:
 * The return value is a token for the matching entry in the
 * hash table, or NULL if there was no matching entry.
 *
 * Side effects:
 * None.
 *
 *----------------------------------------------------------------------
 */

H_HashEntry *StringFind(H_HashTable *tablePtr, char *key)
{
   /*register*/ H_HashEntry *hPtr;
   /*register*/ char *p1, *p2;
   SDWORD index;
   
   index = HashString(key) & tablePtr->mask;
   
   /*
    * Search all of the entries in the appropriate bucket.
    */
   
   for (hPtr = tablePtr->buckets[index]; hPtr != NULL; hPtr = hPtr->nextPtr)
   {
      for (p1 = key, p2 = hPtr->key.string; ; p1++, p2++) 
      {
         if (*p1 != *p2) 
         {
            break;
         }
         if (*p1 == '\0') {
            return hPtr;
         }
      }
   }
   return NULL;
}

/*
 *----------------------------------------------------------------------
 *
 * StringCreate --
 *
 * Given a hash table with string keys, and a string key, find
 * the entry with a matching key.  If there is no matching entry,
 * then create a new entry that does match.
 * IN: tablePtr - Table in which to lookup entry.
 *     key      - Key to use to find or create matching entry.
 *     newPtr   - Store info here telling whether a new entry was created.
 * Results:
 * The return value is a pointer to the matching entry.  If this
 * is a newly-created entry, then *newPtr will be set to a non-zero
 * value;  otherwise *newPtr will be set to 0.  If this is a new
 * entry the value stored in the entry will initially be 0.
 *
 * Side effects:
 * A new entry may be added to the hash table.
 *
 *----------------------------------------------------------------------
 */

H_HashEntry *StringCreate(H_HashTable *tablePtr, char *key, SDWORD *newPtr)
{
   /*register*/ H_HashEntry *hPtr;
   /*register*/ char *p1, *p2;
   SDWORD index;
   
   index = HashString(key) & tablePtr->mask;
   
   /*
    * Search all of the entries in this bucket.
    */   
   for (hPtr = tablePtr->buckets[index]; hPtr != NULL; hPtr = hPtr->nextPtr) 
   {
      for (p1 = key, p2 = hPtr->key.string; ; p1++, p2++) 
      {
         if (*p1 != *p2) 
         {
            break;
         }
         if (*p1 == '\0') 
         {
            *newPtr = 0;
            return hPtr;
         }
      }
   }
   
    /*
     * Entry not found.  Add a new one to the bucket.
     */
    *newPtr = 1;
    hPtr = (H_HashEntry *) FNX_MALLOC((unsigned)(sizeof(H_HashEntry) + FNX_STRLEN(key) - (sizeof(hPtr->key) -1)));
    hPtr->tablePtr = tablePtr;
    hPtr->bucketPtr = &(tablePtr->buckets[index]);
    hPtr->nextPtr = *hPtr->bucketPtr;
    hPtr->clientData = 0;
    FNX_STRCPY(hPtr->key.string, key);
    *hPtr->bucketPtr = hPtr;
    tablePtr->numEntries++;

    /*
     * If the table has exceeded a decent size, rebuild it with many
     * more buckets.
     */

    if (tablePtr->numEntries >= tablePtr->rebuildSize) 
    {
       RebuildTable(tablePtr);
    }
    return hPtr;
}

/*
 *----------------------------------------------------------------------
 *
 * OneWordFind --
 *
 * Given a hash table with one-word keys, and a one-word key, find
 * the entry with a matching key.
 *
 * In: tablePtr - Table in which to lookup entry.
 *     key      - Key to use to find matching entry.
 * Results:
 * The return value is a token for the matching entry in the
 * hash table, or NULL if there was no matching entry.
 *
 * Side effects:
 * None.
 *
 *----------------------------------------------------------------------
 */
H_HashEntry *OneWordFind(H_HashTable *tablePtr, /*register*/ char *key)
{
   /*register*/ H_HashEntry *hPtr;
   SDWORD index;
   
   index = RANDOM_INDEX(tablePtr, key);
   
   /*
    * Search all of the entries in the appropriate bucket.
    */
   
   for (hPtr = tablePtr->buckets[index]; hPtr != NULL; hPtr = hPtr->nextPtr) 
   {
      if (hPtr->key.oneWordValue == key) 
      {
         return hPtr;
      }
   }
   return NULL;
}


/*
 *----------------------------------------------------------------------
 *
 * OneWordCreate --
 *
 * Given a hash table with one-word keys, and a one-word key, find
 * the entry with a matching key.  If there is no matching entry,
 * then create a new entry that does match.
 *
 * In: tablePtr - Table in which to lookup entry.
 *     key      - Key to use to find matching entry.
 *     newPtr   - Store info here telling whether a new entry was created.
 *
 * Results:
 * The return value is a pointer to the matching entry.  If this
 * is a newly-created entry, then *newPtr will be set to a non-zero
 * value;  otherwise *newPtr will be set to 0.  If this is a new
 * entry the value stored in the entry will initially be 0.
 *
 * Side effects:
 * A new entry may be added to the hash table.
 *
 *----------------------------------------------------------------------
 */
H_HashEntry *OneWordCreate(H_HashTable *tablePtr, /*register*/ char *key, SDWORD *newPtr)
{
   /*register*/ H_HashEntry *hPtr;
   SDWORD index;
   
   index = RANDOM_INDEX(tablePtr, key);
   
   /*
    * Search all of the entries in this bucket.
    */
   
   for (hPtr = tablePtr->buckets[index]; hPtr != NULL; hPtr = hPtr->nextPtr) 
   {
      if (hPtr->key.oneWordValue == key) 
      {
         *newPtr = 0;
         return hPtr;
      }
   }
   
   /*
    * Entry not found.  Add a new one to the bucket.
    */
   
   *newPtr = 1;
   hPtr = (H_HashEntry *) FNX_MALLOC(sizeof(H_HashEntry));
   hPtr->tablePtr = tablePtr;
   hPtr->bucketPtr = &(tablePtr->buckets[index]);
   hPtr->nextPtr = *hPtr->bucketPtr;
   hPtr->clientData = 0;
   hPtr->key.oneWordValue = key;
   *hPtr->bucketPtr = hPtr;
   tablePtr->numEntries++;
   
   /*
    * If the table has exceeded a decent size, rebuild it with many
    * more buckets.
    */
   
   if (tablePtr->numEntries >= tablePtr->rebuildSize) 
   {
      RebuildTable(tablePtr);
   }
   return hPtr;
}

/*
 *----------------------------------------------------------------------
 *
 * ArrayFind --
 *
 * Given a hash table with array-of-SDWORD keys, and a key, find
 * the entry with a matching key.
 *
 * In: tablePtr - Table in which to lookup entry.
 *     key      - Key to use to find matching entry.
 * Results:
 * The return value is a token for the matching entry in the
 * hash table, or NULL if there was no matching entry.
 *
 * Side effects:
 * None.
 *
 *----------------------------------------------------------------------
 */
H_HashEntry *ArrayFind(H_HashTable *tablePtr, char *key)
{
   /*register*/ H_HashEntry *hPtr;
   SDWORD *arrayPtr = (SDWORD *) key;
   /*register*/ SDWORD *iPtr1, *iPtr2;
   SDWORD index, count;
   
   for (index = 0, count = tablePtr->keyType, iPtr1 = arrayPtr; count > 0; count--, iPtr1++) 
   {
      index += *iPtr1;
   }
   index = RANDOM_INDEX(tablePtr, index);
   
   /*
   * Search all of the entries in the appropriate bucket.
   */
   
   for (hPtr = tablePtr->buckets[index]; hPtr != NULL; hPtr = hPtr->nextPtr) 
   {
      for (iPtr1 = arrayPtr, iPtr2 = hPtr->key.words, count = tablePtr->keyType; ; count--, iPtr1++, iPtr2++) 
      {
         if (count == 0) 
         {
            return hPtr;
         }
         if (*iPtr1 != *iPtr2) 
         {
            break;
         }
      }
   }
   return NULL;
}

/*
 *----------------------------------------------------------------------
 *
 * ArrayCreate --
 *
 * Given a hash table with one-word keys, and a one-word key, find
 * the entry with a matching key.  If there is no matching entry,
 * then create a new entry that does match.
 *
 * In: tablePtr - Table in which to lookup entry.
 *     key      - Key to use to find matching entry.
 *     newPtr   - Store info here telling whether a new entry was created.
 *
 * Results:
 * The return value is a pointer to the matching entry.  If this
 * is a newly-created entry, then *newPtr will be set to a non-zero
 * value;  otherwise *newPtr will be set to 0.  If this is a new
 * entry the value stored in the entry will initially be 0.
 *
 * Side effects:
 * A new entry may be added to the hash table.
 *
 *----------------------------------------------------------------------
 */

H_HashEntry *ArrayCreate(H_HashTable *tablePtr, /*register*/ char *key, SDWORD *newPtr)
{
   /*register*/ H_HashEntry *hPtr;
   SDWORD *arrayPtr = (SDWORD *) key;
   /*register*/ SDWORD *iPtr1, *iPtr2;
   SDWORD index, count;
   
   for (index = 0, count = tablePtr->keyType, iPtr1 = arrayPtr; count > 0; count--, iPtr1++)
   {
      index += *iPtr1;
   }
   index = RANDOM_INDEX(tablePtr, index);
   
   /*
   * Search all of the entries in the appropriate bucket.
   */
   
   for (hPtr = tablePtr->buckets[index]; hPtr != NULL; hPtr = hPtr->nextPtr) 
   {
      for (iPtr1 = arrayPtr, iPtr2 = hPtr->key.words, count = tablePtr->keyType; ; count--, iPtr1++, iPtr2++) 
      {
         if (count == 0) 
         {
            *newPtr = 0;
            return hPtr;
         }
         if (*iPtr1 != *iPtr2) 
         {
            break;
         }
      }
   }
   
   /*
    * Entry not found.  Add a new one to the bucket.
    */

   *newPtr = 1;
   hPtr = (H_HashEntry *) FNX_MALLOC((unsigned) (sizeof(H_HashEntry)
          + (tablePtr->keyType*sizeof(SDWORD)) - 4));
   hPtr->tablePtr = tablePtr;
   hPtr->bucketPtr = &(tablePtr->buckets[index]);
   hPtr->nextPtr = *hPtr->bucketPtr;
   hPtr->clientData = 0;
   for (iPtr1 = arrayPtr, iPtr2 = hPtr->key.words, count = tablePtr->keyType;
        count > 0; count--, iPtr1++, iPtr2++) 
   {
      *iPtr2 = *iPtr1;
   }
   *hPtr->bucketPtr = hPtr;
   tablePtr->numEntries++;
   
   /*
   * If the table has exceeded a decent size, rebuild it with many
   * more buckets.
   */
   
   if (tablePtr->numEntries >= tablePtr->rebuildSize) 
   {
      RebuildTable(tablePtr);
   }
   return hPtr;
}

/*
 *----------------------------------------------------------------------
 *
 * BogusFind --
 *
 * This procedure is invoked when an H_FindHashEntry is called
 * on a table that has been deleted.
 *
 * In: tablePtr - Table in which to lookup entry.
 *     key      - Key to use to find matching entry.
 *
 * Results:
 * If panic returns (which it shouldn't) this procedure returns
 * NULL.
 *
 * Side effects:
 * Generates a panic.
 *
 *----------------------------------------------------------------------
 */
H_HashEntry *BogusFind(H_HashTable *tablePtr, char *key)
{
   FNX_ASSERT(0);
    //DB_Panic("called H_FindHashEntry on deleted table");
    return NULL;
}

/*
 *----------------------------------------------------------------------
 *
 * BogusCreate --
 *
 * This procedure is invoked when an H_CreateHashEntry is called
 * on a table that has been deleted.
 *
 * Results:
 * If panic returns (which it shouldn't) this procedure returns
 * NULL.
 *
 * Side effects:
 * Generates a panic.
 *
 *----------------------------------------------------------------------
 */
H_HashEntry *BogusCreate(H_HashTable *tablePtr, char *key, SDWORD *newPtr)
{
   FNX_ASSERT(0);
   //DB_Panic("called H_CreateHashEntry on deleted table");
   return NULL;
}

/*
 *----------------------------------------------------------------------
 *
 * RebuildTable --
 *
 * This procedure is invoked when the ratio of entries to hash
 * buckets becomes too large.  It creates a new table with a
 * larger bucket array and moves all of the entries into the
 * new table.
 *
 * Results:
 * None.
 *
 * Side effects:
 * Memory gets reallocated and entries get re-hashed to new
 * buckets.
 *
 *----------------------------------------------------------------------
 */

void RebuildTable(/*register*/ H_HashTable *tablePtr)
{
   SDWORD oldSize, count, index;
   H_HashEntry **oldBuckets;
   /*register*/ H_HashEntry **oldChainPtr, **newChainPtr;
   /*register*/ H_HashEntry *hPtr;
   
   oldSize = tablePtr->numBuckets;
   oldBuckets = tablePtr->buckets;
   
   /*
    * Allocate and initialize the new bucket array, and set up
    * hashing constants for new array size.
    */
   
   tablePtr->numBuckets *= 4;
   tablePtr->buckets = (H_HashEntry **) FNX_MALLOC((unsigned)
      (tablePtr->numBuckets * sizeof(H_HashEntry *)));
   for (count = tablePtr->numBuckets, newChainPtr = tablePtr->buckets; count > 0; count--, newChainPtr++) 
   {
      *newChainPtr = NULL;
   }
   tablePtr->rebuildSize *= 4;
   tablePtr->downShift -= 2;
   tablePtr->mask = (tablePtr->mask << 2) + 3;
   
   /*
    * Rehash all of the existing entries into the new bucket array.
    */
   
   for (oldChainPtr = oldBuckets; oldSize > 0; oldSize--, oldChainPtr++) 
   {
      for (hPtr = *oldChainPtr; hPtr != NULL; hPtr = *oldChainPtr) 
      {
         *oldChainPtr = hPtr->nextPtr;
         if (tablePtr->keyType == H_STRING_KEYS) 
         {
            index = HashString(hPtr->key.string) & tablePtr->mask;
         }
         else if (tablePtr->keyType == H_ONE_WORD_KEYS) 
         {
            index = RANDOM_INDEX(tablePtr, hPtr->key.oneWordValue);
         }
         else
         {
            /*register*/ SDWORD *iPtr;
            SDWORD count;
            
            for (index = 0, count = tablePtr->keyType, iPtr = hPtr->key.words; count > 0; count--, iPtr++) 
            {
               index += *iPtr;
            }
            index = RANDOM_INDEX(tablePtr, index);
         }
         hPtr->bucketPtr = &(tablePtr->buckets[index]);
         hPtr->nextPtr = *hPtr->bucketPtr;
         *hPtr->bucketPtr = hPtr;
      }
   }
   
   /*
    * Free up the old bucket array, if it was dynamically allocated.
    */
   
   if (oldBuckets != tablePtr->staticBuckets) 
   {
      FNX_FREE((char *) oldBuckets);
   }
}
