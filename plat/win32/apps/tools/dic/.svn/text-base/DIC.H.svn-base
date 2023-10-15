/*
 ***********************************************************************
 *
 *                           Copyright ©
 *    Copyright © 2000 Force Computers, Inc., a Solectron company. All rights reserved. 
 *    © Digital Equipment Corporation 1995. All rights reserved.
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Force Computers Incorporated and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Force or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:	dic.h
 *    Author:
 *    Creation Date:
 *
 *    Functionality:
 *
 ***********************************************************************
 *    Revision History:
 * [0]      -     	PRG		Created
 * 001	20-Nov-89 	kdk		Added new form class "character" with features
 *							"alpha" (letters of the alphabet) and "iso"
 *							(iso-latin character set).
 * 002  08-July-98 	GL   	For BATS#706, include fc_def.tab to catch the shared FC definition
 * 003 	10/16/00	CAB		Changed copyright info
 */
#ifndef DIC_H
#define DIC_H

#include <stdlib.h>
#include "fc_def.tab"

typedef struct				/* item descriptor */
   {
   unsigned short buffer_length;	/* length of return buffer */
   unsigned short item_code;		/* code of item being requested */
   unsigned long *buffer;		/* return buffer */
   unsigned long *transfer_size;	/* size of return */
   } ITEM_DSC;

typedef struct PTAB {
	unsigned char p_graph;        /* Graphic code. Now unsigned char */
	char p_phone;                /* Phonemic code */
} PTAB;


/*
   The following structure represents a database object file header.
*/

typedef struct
   {
   unsigned long no_of_entries;		/* number of entries in dictionary */
   unsigned long creation;				/* time of database object creation */
   unsigned long modified;				/* time object was last modified */
   unsigned char dummy[500];			/* dummy field */
   } DIC_OBJ_HEADER;

/*
   The following structure represents the internal format of a dictionary
   entry.  NOTE:  this structure is used by tools and utilities which deal
   directly with dictionaries and is not intended for an internal
   representation of a tagged word in DECtalk. 

   Field explanations:

   spelling - this field is used to define the orthographic spelling of
	the entry.  It is always required, and sometimes must be interpretted
	as one of two types of suffixes:  either a derivational suffix, which
	is denoted by a '-' as the first character, or a form class marker,
	which is denoted by a '+' as the first character.

   pronunciation - this field is used to define the phonetic spelling of
	the entry.  It is required except in the case that the entry is
	for a form class marker.

   form_class - this field is a longword bitmask which defines the form
	class (or possible form classes) of the entry.  Bit 29 is reserved
	for distinguishing suffix types, that is, whether it is a derivational
	suffix or a form class marker. Bit 30 is reserved for the definition 
	of contractions.  If bit 30 is set, then the entry has an unambiguous 
	form class which is represents a contraction of form classes.
	Bit 31 is reserved to distinguish homographs.

   semantic_class - this field is an array of quadword bitmasks which 
	define the relevant semantic features.

   frequency - this field defines the frequency of the entry out of 1 million.

   comment - this field is used by the user to make random comments pertinent
	to the entry.  It is common to use this field to define modification
	date and/or reason for modification of the entry.
*/

#define S_LEN			40
#define P_LEN			40
#define C_LEN			80

typedef struct dic
   {
   struct dic *flink;						/* forward link */
   char spelling[S_LEN];					/* orthographical spelling of word */
   char pronunciation[P_LEN];				/* phonetic spelling of word */
   unsigned long form_class;				/* form class of word */
   unsigned long semantic_class[31];	/* semantics of word */
   unsigned long frequency;				/* frequency of word */
   char comment[C_LEN];						/* comment */
   } DIC;

/*
   The following structure is a subset of the dictionary entry, used by
   certain parsing and display routines.
*/

typedef struct
   {
   unsigned long form_class;		/* form class of word */
   unsigned long semantic_class[31];	/* semantic features of word */
   } GRAMMAR;



#endif