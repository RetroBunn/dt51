/*
 * stdonsei.h
 * 
 * User exposed API constants and functions
 *
 */
#ifndef STDONSEI_H
#define STDONSEI_H

#include "onseiapi.h"

/* magic constants */
#define	MAX_INERT	128		
#define	MAX_SENT	 80		
#define	MAX_SPEAK	768		

/* these are arguments passed in to onsei_henkan to tell it how to process input */
#define PROC_FIRST			3	/* First conversion */
#define PROC_NEXT			4	/* Attention word or phrase next candidate */
#define PROC_SHORT			5	/* Splits into the direction of the short word or phrase */
#define PROC_LONG			6	/* Splits into the direction of the long word or phrase */
#define PROC_RIGHT			7	/* Attention word or phrase move to the right */
#define PROC_LEFT			8	/* Attention word or phrase move to the left */
#define PROC_TERM			9	/* Decides on learned information */
#define PROC_SENT_NO	    10	/* Takes out the attention word or phrase number */
#define PROC_ACON			14	/* Combines the accent of attention word or phrase and the next word or phrase */
#define PROC_ACOFF			15	/* Does not combine the accent of attention word or phrase to the next word or phrase */
#define PROC_PAUSE_INS		16	/* Inserts a pause directly after the attention word or phrase */
#define PROC_PAUSE_DEL		17	/* Deletes the pause directly after the attention word or phrase */

/* error return codes -- 0 indicates normal completion */
#define	Err_NaibuOVF		0x82	/* The word or phrase number is over limit or the phonogram string is too long */
#define	Err_Chuudan			0x83	/* Stopped at u_stop() */
#define	Err_EdicTooLong		0x87	/* The written item or the reading is too long */
#define	Err_TourokuSumi		0x88	/* The same one is already registered */
#define	Err_MiTouroku		0x89	/* It is not the user's registration word */
#define	Err_EdicOVF			0x8A	/* Cannot be registered -> if the dictionary readjusts, then it will be OK */
#define Err_Fatal_DIC		0x9F	/* No dictionary */
#define Err_Fatal_Edic		0xA0	/* Dictionary malfunction */
#define Err_Fatal_Idic		0xA1	/* Dictionary malfunction */
#define Err_Fatal_Alloc		0xA3	/* insufficient memory */
#define Err_Broken			0xFF	/* Dictionary broken */

#define	Err_IdouFunou		0x71	/* Word or phrase movement is not possible */
#define	Err_NextNone		0x72	/* There is no next candidate */
#define	Err_HenkanTochuu	0x73	/* Conversion of a word that is not in the dictionary */
#define Err_RestrictCNT		0x74	/* Timed out */

#endif /* STDONSEI_H */

/* End of stdonsei.h */
