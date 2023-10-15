/*
 ***********************************************************************
 *                                                                      
 *                           Copyright ©
 *    Copyright © 2002 Fonix Corporation. All rights reserved.
 *    Copyright © 2000 Force Computer, Inc., a Solectron company. All rights reserved.
 *    © Digital Equipment Corporation 1996, 1997 All rights reserved.
                                                                  
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.    
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.                                
 *                                                                      
 *    This software is proprietary to and embodies the confidential
 *    technology of Fonix Corporation and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Fonix or an
 *    authorized sublicensor.
 *                                                                       
 *********************************************************************** 
 *    File Name:	l_la_con.c
 *    Author:		JDB                                         
 *    Creation Date:05/29/96                                                   
 *                                                                             
 *    Functionality:        
 *    DECtalk p3 and beyond ... constant tabular data is collected here
 *    just to make dealing with it a bit easier ...
 *    This file contains a number
 *	  of canned phoneme strings. These are
 * 	  used by the number rules, etc.
 *    All are streams of bytes with a SI
 *    phoneme on the end.                                                                   
 ***********************************************************************       
 *                                                                             
 *	Rev	Who		Date			Description                    
 *	---	-----	-----------		---------------------------------------
 *  001 DGC		04/05/1985 		Changed [s] to [z] in "thousand".
 *  002 DGC		04/08/1985 		Added "pdegree".
 *  003 DGC		04/24/1985 		Fix some phomenes to agree with some
 *								dictionary changes.
 *  004	DGC		06/14/1985 		The "pplus" array isn't needed anymore.
 *  005 DGC		06/27/1985	 	Remove last [d] from "thousand".
 *  006 DGC		07/24/1985		[f'owr] to [f'or] and related forms.
 *  007 DGC		08/20/1985 		Undid 05; sounded bad.
 *  008 GL		07/29/1996		remove feats[] and pfeats[] two unused table.
 *  009 GL		11/01/1996		Fix the number system.
 *  010	GL		11/14/1996		Add p1_un[] and up1_un[]
 *  011	GL		02/10/1997		Bug fix for BATS#284.add NULL at the end of months[]
 *  012	MFG		06/17/1998		Copied from l_la_con.c
 *  013	GL		08/18/1998		Bug fix for BATS#745.  use S1 for all number.
 *  014 EAB		9/24/98			Improving numbers there are a lot of different problems ranging from 
 *						        stress changes to word bundary and syl boundary issues,
 *  015	GL.Juan	10/02/1998		add number abbreviation
 *  016	GL/Juan	10/12/1998		set "1" defaulted to "un" for all case.
 *                              use pre-process to translate "1" to "uno" or "una"
 *  017	GL.Juan	10/14/1998		add more number abbreviation
 *  018	GL		11/03/1998		BATS#783 add p1_uno[] for two digits number in date, time
 *  019	GL.Juan	11/04/1998		BATS#786 fix error in sdic[], spwhword[]
 *  020	GL.Juan	11/06/1998		BATS#721 add entry for nwdtab[]
 *  021	GL.Juan	11/06/1998		add more new entry for number abbrv.
 *  022	GL.Juan	11/12/1998		remove SBOUND from ponehundred[]
 *  023	MGS		04/13/2000		Changes for integrated phoneme set
 *  024 CAB		9/21/2000		Fixed copyright info and formatted comment section.
 *	025	CAB		04/24/2002		Fixed changed to const as ls_cons.h
 */
#include        "tts.h"    /* For the declarartion of LPTTS_HANDLE_T */
//moved to port.h for each platform - mlt
//#ifdef WIN32
//#include <windows.h>
//#endif

//#if !defined OS_PALM && !defined CASIO_SH3
//#include <stdio.h>
//#endif
//#include <string.h>

#include "port.h"  
#include "kernel.h"
#include "ls_char.h"
#include "ls_dict.h"
#include "ls_defs.h"
#include "ls_data.h"
#include "ph_def.h"

#include "ls_prot.h"

#include "ls_def.h"

const unsigned char ptt2tp[] = {
      0
};
  
/*
 * This rather large table is
 * used to obtain the attributes of characters
 * in the ASCII_G and DEC multinational character
 * set. It is indexed by character code, with ASCII_G
 * in GL, ASCII_C in C0, the DEC multinational set
 * in GR, and the supplimental control set in C1.
 * The major client of this table is the word
 * reading stuff.
 */ 

const U16 lsctype[] = {
	IGNORE,                         /* NUL                          */
	IGNORE,                         /* SOH                          */
	IGNORE,                         /* STX                          */
	IGNORE,                         /* ETX                          */
	IGNORE,                         /* EOT                          */
	IGNORE,                         /* ENQ                          */
	IGNORE,                         /* ACK                          */
	IGNORE,                         /* BEL  (Could be a word)       */
	BACKUP,                         /* BS                           */
	NEVER,                          /* HT                           */
	NEVER,                          /* LF                           */
	NEVER,                          /* VT                           */
	NEVER,                          /* FF                           */
	NEVER,                          /* CR                           */
	IGNORE,                         /* SO                           */
	IGNORE,                         /* SI                           */

	IGNORE,                         /* DLE                          */
	IGNORE,                         /* DC1                          */
	IGNORE,                         /* DC2                          */
	IGNORE,                         /* DC3                          */
	IGNORE,                         /* DC4                          */
	IGNORE,                         /* NAK                          */
	IGNORE,                         /* SYN                          */
	IGNORE,                         /* ETB                          */
	IGNORE,                         /* CAN                          */
	IGNORE,                         /* EM                           */
	IGNORE,                         /* SUB  (Is this right?)        */
	IGNORE,                         /* ESC                          */
	IGNORE,                         /* FS                           */
	IGNORE,                         /* GS                           */
	IGNORE,                         /* RS                           */
	IGNORE,                         /* US                           */

	NEVER,                          /* SP                           */
	MIGHT+PR,     					/* !                            */
	ALWAYS+LS+RS+PR,     			/* "							*/
	ALWAYS+PR,     					/* #                            */
	ALWAYS+PR,     					/* $                            */
	ALWAYS+PR,     					/* %                            */
	ALWAYS +PR,     				/* &                            */
	ALWAYS+PR,     					/* '                            */
	ALWAYS+LS+FB+PR,     			/* (                            */
	ALWAYS+RS+FB+PR,     			/* )                            */
	ALWAYS+PR,     					/* *                            */
	ALWAYS+PR,     					/* +                            */
	MIGHT+PR,     					/* ,                            */
	ALWAYS+PR,     					/* -                            */
	MIGHT+PR,     					/* .                            */
	ALWAYS+PR,     					/* /                            */

	ALWAYS+PR,     					/* 0                            */
	ALWAYS+PR,     					/* 1                            */
	ALWAYS+PR,     					/* 2                            */
	ALWAYS+PR,     					/* 3                            */
	ALWAYS+PR,    	 				/* 4                            */
	ALWAYS+PR,     					/* 5                            */
	ALWAYS+PR,     					/* 6                            */
	ALWAYS+PR,     					/* 7                            */
	ALWAYS+PR,     					/* 8                            */
	ALWAYS+PR,     					/* 9                            */
	MIGHT+PR,     					/* :                            */
	MIGHT+PR,     					/* ;                            */
	ALWAYS+LS+FB+PR,     			/* <                            */
	ALWAYS+PR,     					/* =                            */
	ALWAYS+RS+FB+PR,     			/* >                            */
	MIGHT+PR,     					/* ?                            */

	ALWAYS+PR,     					/* @                            */
	ALWAYS+UU+L+OO+PR,    			/* A                            */
	ALWAYS+UU+L+C+PR,    			/* B                            */
	ALWAYS+UU+L+C+PR,    			/* C                            */
	ALWAYS+UU+L+C+PR,    			/* D                            */
	ALWAYS+UU+L+OO+PR,   			/* E                            */
	ALWAYS+UU+L+C+PR,    			/* F                            */
	ALWAYS+UU+L+C+PR,    			/* G                            */
	ALWAYS+UU+L+C+PR,    			/* H                            */
	ALWAYS+UU+L+OO+PR,   			/* I                            */
	ALWAYS+UU+L+C+PR,    			/* J                            */
	ALWAYS+UU+L+C+PR,    			/* K                            */
	ALWAYS+UU+L+C+PR,    			/* L                            */
	ALWAYS+UU+L+C+PR,    			/* M                            */
	ALWAYS+UU+L+C+PR,    			/* N                            */
	ALWAYS+UU+L+OO+PR,   			/* O                            */

	ALWAYS+UU+L+C+PR,    			/* P                            */
	ALWAYS+UU+L+C+PR,    			/* Q                            */
	ALWAYS+UU+L+C+PR,    			/* R                            */
	ALWAYS+UU+L+C+PR,    			/* S                            */
	ALWAYS+UU+L+C+PR,    			/* T                            */
	ALWAYS+UU+L+OO+PR,   			/* U                            */
	ALWAYS+UU+L+C+PR,    			/* V                            */
	ALWAYS+UU+L+C+PR,    			/* W                            */
	ALWAYS+UU+L+C+PR,    			/* X                            */
	ALWAYS+UU+L+PR,    				/* Y (-V, -C)                   */
	ALWAYS+UU+L+C+PR,    			/* Z                            */
	ALWAYS+LS+FB+PR,     			/* [                            */
	ALWAYS+PR,     					/* \                            */
	ALWAYS+RS+FB+PR,     			/* ]                            */
	ALWAYS+PR,     					/* ^                            */
	ALWAYS+II+PR,    				/* _                            */

	ALWAYS+PR,     					/* `                            */
	ALWAYS+LC+L+OO+PR,    			/* a                            */
	ALWAYS+LC+L+C+PR,     			/* b                            */
	ALWAYS+LC+L+C+PR,     			/* c                            */
	ALWAYS+LC+L+C+PR,     			/* d                            */
	ALWAYS+LC+L+OO+PR,    			/* e                            */
	ALWAYS+LC+L+C+PR,     			/* f                            */
	ALWAYS+LC+L+C+PR,     			/* g                            */
	ALWAYS+LC+L+C+PR,     			/* h                            */
	ALWAYS+LC+L+OO+PR,    			/* i                            */
	ALWAYS+LC+L+C+PR,     			/* j                            */
	ALWAYS+LC+L+C+PR,     			/* k                            */
	ALWAYS+LC+L+C+PR,     			/* l                            */
	ALWAYS+LC+L+C+PR,     			/* m                            */
	ALWAYS+LC+L+C+PR,     			/* n                            */
	ALWAYS+LC+L+OO+PR,    			/* o                            */

	ALWAYS+LC+L+C+PR,     			/* p                            */
	ALWAYS+LC+L+C+PR,     			/* q                            */
	ALWAYS+LC+L+C+PR,     			/* r                            */
	ALWAYS+LC+L+C+PR,     			/* s                            */
	ALWAYS+LC+L+C+PR,     			/* t                            */
	ALWAYS+LC+L+OO+PR,    			/* u                            */
	ALWAYS+LC+L+C+PR,     			/* v                            */
	ALWAYS+LC+L+C+PR,     			/* w                            */
	ALWAYS+LC+L+C+PR,     			/* x                            */
	ALWAYS+LC+L+PR,     			/* y (-V, -C)                   */
	ALWAYS+LC+L+C+PR,     			/* z                            */
	ALWAYS+LS+FB+PR,     			/* {                            */
	ALWAYS+PR,     					/* |                            */
	ALWAYS+RS+FB+PR,     			/* }                            */
	ALWAYS+PR,     					/* ~                            */
	IGNORE,                         /* DEL                          */

	ALWAYS+PR,						/* euro symbol                  */
	IGNORE,
	IGNORE,
	IGNORE,
	IGNORE,                         /* IND                          */
	IGNORE,                         /* NEL                          */
	IGNORE,                         /* SSA                          */
	IGNORE,                         /* ESA                          */
	IGNORE,                         /* HTS                          */
	IGNORE,                         /* HTJ                          */
	IGNORE,                         /* VTS                          */
	IGNORE,                         /* PLD                          */
	ALWAYS+UU+L+OO+PR,                         /* PLU                          */
	IGNORE,                         /* RI                           */
	IGNORE,                         /* SS2                          */
	IGNORE,                         /* SS3                          */

	IGNORE,                         /* DCS                          */
	IGNORE,                         /* PU1                          */
	IGNORE,                         /* PU2                          */
	IGNORE,                         /* STS                          */
	IGNORE,                         /* CCH                          */
	IGNORE,                         /* MW                           */
	IGNORE,                         /* SPA                          */
	IGNORE,                         /* EPA                          */
	IGNORE,
	IGNORE,
	IGNORE,
	IGNORE,                         /* CSI                          */
	ALWAYS+LC+L+OO+PR,                         /* OSC                          */
	IGNORE,                         /* ST                           */
	IGNORE,                         /* PM                           */
	IGNORE,                         /* APC                          */

	NEVER+PR,     					/* SP                           */
	ALWAYS+LS+PR,     				/* Inverted !                   */
	ALWAYS+PR,     					/* Cent symbol                  */
	ALWAYS+PR,     					/* UK currency symbol           */
	IGNORE,
	ALWAYS+PR,     					/* Yen symbol                   */
	ALWAYS+PR,
	ALWAYS+PR,     					/* Section symbol               */
	ALWAYS+PR,     					/* Blob with 4 little spikes    */
	ALWAYS+PR,     					/* Copyright symbol             */
	ALWAYS+PR,     					/* Underlined "a"               */
	ALWAYS+LS+PR,     				/* <<                           */
	IGNORE,
	IGNORE,
	IGNORE,
	IGNORE,

	ALWAYS+PR,     					/* Degree symbol                */
	ALWAYS+PR,    	 				/* Plus-Minus                   */
	ALWAYS+PR,     					/* Superscript 2                */
	ALWAYS+PR,     					/* Superscript 3                */
	IGNORE,
	ALWAYS+PR,   					/* Mu                           */
	ALWAYS+PR,     					/* Paragraph                    */
	ALWAYS+PR,     					/* Solid circle                 */
	IGNORE,
	ALWAYS+PR,     					/* Superscript 1                */
	ALWAYS+PR,     					/* Underlined "o"               */
	ALWAYS+RS+PR,     				/* >>                           */
	ALWAYS+PR,     					/* 1/4                          */
	ALWAYS+PR,     					/* 1/2                          */
	IGNORE,
	ALWAYS+LS+PR,     				/* Inverted ?                   */

	ALWAYS+UU+L+OO+PR,     			/* A grave                      */
	ALWAYS+UU+L+OO+PR,     			/* A acute                      */
	ALWAYS+UU+L+OO+PR,     			/* A circumflex                 */
	ALWAYS+UU+L+OO+PR,     			/* A tilde                      */
	ALWAYS+UU+L+OO+PR,     			/* A diarasis                   */
	ALWAYS+UU+L+OO+PR,     			/* A with circle 			    */
	ALWAYS+UU+L+OO+PR,     			/* AE                           */
	ALWAYS+UU+L+C+PR,      			/* C cdl.                       */
	ALWAYS+UU+L+OO+PR,     			/* E grave                      */
	ALWAYS+UU+L+OO+PR,     			/* E acute                      */
	ALWAYS+UU+L+OO+PR,     			/* E circumflex                 */
	ALWAYS+UU+L+OO+PR,     			/* E diarasis                   */
	ALWAYS+UU+L+OO+PR,     			/* I grave                      */
	ALWAYS+UU+L+OO+PR,     			/* I acute                      */
	ALWAYS+UU+L+OO+PR,     			/* I circumflex                 */
	ALWAYS+UU+L+OO+PR,     			/* I diarasis                   */

	IGNORE,
	ALWAYS+UU+L+C+PR,      			/* N tilde                      */
	ALWAYS+UU+L+OO+PR,     			/* O grave                      */
	ALWAYS+UU+L+OO+PR,     			/* O acute                      */
	ALWAYS+UU+L+OO+PR,     			/* O circumflex                 */
	ALWAYS+UU+L+OO+PR,     			/* O tilde                      */
	ALWAYS+UU+L+OO+PR,     			/* O diarasis                   */
	ALWAYS+UU+L+OO+PR,     			/* OE                           */
	ALWAYS+UU+L+OO+PR,     			/* O with backslash             */
	ALWAYS+UU+L+OO+PR,     			/* U grave                      */
	ALWAYS+UU+L+OO+PR,     			/* U acute                      */
	ALWAYS+UU+L+OO+PR,     			/* U circumflex                 */
	ALWAYS+UU+L+OO+PR,     			/* U diarasis                   */
	ALWAYS+UU+L+C+PR,      			/* Y diarasis                   */
	IGNORE,
	ALWAYS+L+C+PR,       			/* The "Beta" German thing.     */

	ALWAYS+LC+L+OO+PR,     			/* a grave                      */
	ALWAYS+LC+L+OO+PR,     			/* a acute                      */
	ALWAYS+LC+L+OO+PR,     			/* a circumflex                 */
	ALWAYS+LC+L+OO+PR,     			/* a tilde                      */
	ALWAYS+LC+L+OO+PR,     			/* a diarasis                   */
	ALWAYS+LC+L+OO+PR,     			/* a with little circle         */
	ALWAYS+LC+L+OO+PR,     			/* ae                           */
	ALWAYS+LC+L+C+PR,      			/* c cdl.                       */
	ALWAYS+LC+L+OO+PR,     			/* e grave                      */
	ALWAYS+LC+L+OO+PR,     			/* e acute                      */
	ALWAYS+LC+L+OO+PR,     			/* e circumflex                 */
	ALWAYS+LC+L+OO+PR,     			/* e diarasis                   */
	ALWAYS+LC+L+OO+PR,     			/* i grave                      */
	ALWAYS+LC+L+OO+PR,     			/* i acute                      */
	ALWAYS+LC+L+OO+PR,     			/* i circumflex                 */
	ALWAYS+LC+L+OO+PR,     			/* i diarasis                   */

	IGNORE,
	ALWAYS+LC+L+C+PR,      			/* n tilde                      */
	ALWAYS+LC+L+OO+PR,     			/* o grave                      */
	ALWAYS+LC+L+OO+PR,     			/* o acute                      */
	ALWAYS+LC+L+OO+PR,     			/* o curcumflex                 */
	ALWAYS+LC+L+OO+PR,     			/* o tilde                      */
	ALWAYS+LC+L+OO+PR,     			/* o diarasis                   */
	ALWAYS+LC+L+OO+PR,     			/* oe                           */
	ALWAYS+LC+L+OO+PR,     			/* o with line                  */
	ALWAYS+LC+L+OO+PR,     			/* u grave                      */
	ALWAYS+LC+L+OO+PR,     			/* u acute                      */
	ALWAYS+LC+L+OO+PR,     			/* u circumflex                 */
	ALWAYS+LC+L+OO+PR,     			/* u diarasis                   */
	ALWAYS+LC+L+C+PR,      			/* y diarasis                   */
	IGNORE,
	IGNORE

};

/*
 * This table contains a list of
 * "number abbreviations" and the desired
 * phoneme string. There are actually two strings, that
 * sit side by side with a "SIL" phoneme between them. The
 * caller will scan over the first one (the singular format
 * of the abbreviation) if the plural form is the one
 * that is desired. Used by heuristics. It would be
 * nice if there was a way to make C count the
 * blocks, like you can in MACRO and other very
 * high level languages.
 */

const unsigned char nabtab[] = {
	34,	'c',	'l',	EOS,
	IT_TH, IT_E, IT_N, SBOUND, IT_T, IT_I, SBOUND, IT_L, S2, IT_I, SBOUND, IT_T, IT_R, IT_O, SIL,
	IT_TH, IT_E, IT_N, SBOUND, IT_T, IT_I, SBOUND, IT_L, S2, IT_I, SBOUND, IT_T, IT_R, IT_O, IT_S, SIL,

	32,	'd',	'm',	EOS,
	IT_D, IT_E, SBOUND, IT_TH, S1, IT_I, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, SIL,
	IT_D, IT_E, SBOUND, IT_TH, S1, IT_I, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, IT_S, SIL,

	32,	'd',	'l',	EOS,
	IT_D, IT_E, SBOUND, IT_TH, IT_I, SBOUND, IT_L, S2, IT_I, SBOUND, IT_T, IT_R, IT_O, SIL,
	IT_D, IT_E, SBOUND, IT_TH, IT_I, SBOUND, IT_L, S2, IT_I, SBOUND, IT_T, IT_R, IT_O, IT_S, SIL,

	19,	'g',	EOS,
	IT_G, IT_R, S1, IT_A, SBOUND, IT_M, IT_O, SIL,
	IT_G, IT_R, S1, IT_A, SBOUND, IT_M, IT_O, IT_S, SIL,

	20,	'g',	'r',	EOS,
	IT_G, IT_R, S1, IT_A, SBOUND, IT_M, IT_O, SIL,
	IT_G, IT_R, S1, IT_A, SBOUND, IT_M, IT_O, IT_S, SIL,

	32,	'k',	'l',	EOS,
	IT_K, IT_I, SBOUND, IT_L, IT_O, SBOUND, IT_L, S2, IT_I, SBOUND, IT_T, IT_R, IT_O, SIL,
	IT_K, IT_I, SBOUND, IT_L, IT_O, SBOUND, IT_L, S2, IT_I, SBOUND, IT_T, IT_R, IT_O, IT_S, SIL,

	32,	'k',	'm',	EOS,
	IT_K, IT_I, SBOUND, IT_L, S1, IT_O, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, SIL,
	IT_K, IT_I, SBOUND, IT_L, S1, IT_O, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, IT_S, SIL,

	44,	'm',	'2',	EOS,
	IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, MBOUND, IT_K, IT_U, IT_A, SBOUND, IT_D, IT_R, S2, IT_A, SBOUND, IT_D, IT_O, IT_S, SIL,
	IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, IT_S, MBOUND, IT_K, IT_U, IT_A, SBOUND, IT_D, IT_R, S2, IT_A, SBOUND, IT_D, IT_O, IT_S, SIL,

	59,	'k',	'm',	'2',	EOS,
	IT_K, IT_I, SBOUND, IT_L, S1, IT_O, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, MBOUND, IT_K, IT_U, IT_A, SBOUND, IT_D, IT_R, S2, IT_A, SBOUND, IT_D, IT_O, IT_S, SIL,
	IT_K, IT_I, SBOUND, IT_L, S1, IT_O, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, IT_S, MBOUND, IT_K, IT_U, IT_A, SBOUND, IT_D, IT_R, S2, IT_A, SBOUND, IT_D, IT_O, IT_S, SIL,

	50,	'k',	'm',	'/',	'h',	EOS,
	IT_K, IT_I, SBOUND, IT_L, S1, IT_O, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, MBOUND, IT_P, IT_O, IT_R, MBOUND, IT_O, SBOUND, IT_R, IT_A, SIL,
	IT_K, IT_I, SBOUND, IT_L, S1, IT_O, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, IT_S, MBOUND, IT_P, IT_O, IT_R, MBOUND, IT_O, SBOUND, IT_R, IT_A, SIL,

	32,	'k',	'g',	EOS,
	IT_K, IT_I, SBOUND, IT_L, IT_O, SBOUND, IT_G, IT_R, S1, IT_A, SBOUND, IT_M, IT_O, SIL,
	IT_K, IT_I, SBOUND, IT_L, IT_O, SBOUND, IT_G, IT_R, S1, IT_A, SBOUND, IT_M, IT_O, IT_S, SIL,

	32,	'k',	'w',	EOS,
	IT_K, IT_I, SBOUND, IT_L, IT_O, SBOUND, IT_B, S2, IT_A, SBOUND, IT_T, IT_I, IT_O, SIL,
	IT_K, IT_I, SBOUND, IT_L, IT_O, SBOUND, IT_B, S2, IT_A, SBOUND, IT_T, IT_I, IT_O, IT_S, SIL,

	49,	'k',	'p',	'h',	EOS,
	IT_K, IT_I, SBOUND, IT_L, S1, IT_O, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, MBOUND, IT_P, IT_O, IT_R, MBOUND, IT_O, SBOUND, IT_R, IT_A, SIL,
	IT_K, IT_I, SBOUND, IT_L, S1, IT_O, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, IT_S, MBOUND, IT_P, IT_O, IT_R, MBOUND, IT_O, SBOUND, IT_R, IT_A, SIL,

	32,	'm',	'm',	EOS,
	IT_M, IT_I, SBOUND, IT_L, S1, IT_I, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, SIL,
	IT_M, IT_I, SBOUND, IT_L, S1, IT_I, SBOUND, IT_M, IT_E, SBOUND, IT_T, IT_R, IT_O, IT_S, SIL,

	32,	'm',	'l',	EOS,
	IT_M, IT_I, SBOUND, IT_L, IT_I, SBOUND, IT_L, S2, IT_I, SBOUND, IT_T, IT_R, IT_O, SIL,
	IT_M, IT_I, SBOUND, IT_L, IT_I, SBOUND, IT_L, S2, IT_I, SBOUND, IT_T, IT_R, IT_O, IT_S, SIL,

	32,	'm',	'g',	EOS,
	IT_M, IT_I, SBOUND, IT_L, IT_I, SBOUND, IT_G, IT_R, S1, IT_A, SBOUND, IT_M, IT_O, SIL,
	IT_M, IT_I, SBOUND, IT_L, IT_I, SBOUND, IT_G, IT_R, S1, IT_A, SBOUND, IT_M, IT_O, IT_S, SIL,

	19, 0xb0,	EOS, //0xb0 = '°'
	IT_G, IT_R, S1, IT_A, SBOUND, IT_D, IT_O, SIL,
	IT_G, IT_R, S1, IT_A, SBOUND, IT_D, IT_O, IT_S, SIL,

	52,	0xb0, 'c', 	EOS, //0xb0 = '°'
	IT_G, IT_R, S1, IT_A, SBOUND, IT_D, IT_O, WBOUND, IT_TH, IT_E, IT_N, SBOUND, IT_T, S1, IT_I, SBOUND, IT_G, IT_R, S2, IT_A, SBOUND, IT_D, IT_O, SIL,
	IT_G, IT_R, S1, IT_A, SBOUND, IT_D, IT_O, WBOUND, IT_TH, IT_E, IT_N, SBOUND, IT_T, S1, IT_I, SBOUND, IT_G, IT_R, S2, IT_A, SBOUND, IT_D, IT_O, IT_S, SIL,
	0

 };

/*
 * This table, which has the same basic
 * format as the number abbreviation table, contains
 * the names and the pronounciation of the number words.
 * There is only a single phoneme string.
 */
/* GL 11/06/98, BATS#721 add this table to support currency reading */
const unsigned char nwdtab[] = {
	11,'c','i','e','n',EOS,IT_TH,IT_I,S1,IT_E,IT_N,SIL,
	16,'c','i','e','n','t','o',EOS,IT_TH,IT_I,S1,IT_E,IT_N,SBOUND,IT_T,IT_O,SIL,
	18,'c','i','e','n','t','o','s',EOS,IT_TH,IT_I,S1,IT_E,IT_N,SBOUND,IT_T,IT_O,IT_S,SIL,
	9, 'm','i','l',EOS,IT_M,S1,IT_I,IT_L,SIL,
	14, 'm','i','l','e','s',EOS,IT_M,S1,IT_I,SBOUND,IT_L,IT_E,IT_S,SIL,
	15,'m','i','l','l',0xf3,'n',EOS,IT_M,IT_I,SBOUND,IT_LL,S1,IT_O,IT_N,SIL, //0xf3 = 'ó'
	20,'m','i','l','l','o','n','e','s',EOS,IT_M,IT_I,SBOUND,IT_LL,S1,IT_O,IT_N,SBOUND,IT_E,IT_S,SIL,
    //29, 'm','i','l',' ','m','i','l','l','o','n','e','s',EOS,IT_M,S1,IT_I,IT_L,WBOUND,IT_M,IT_I,SBOUND,IT_LL,S1,IT_O,IT_N,SBOUND,IT_E,IT_S,SIL,
    22, 'm','i','l','l','a','r','d','o','s',EOS,IT_M,IT_I,SBOUND,IT_LL,S1,IT_A,IT_R,SBOUND,IT_DH,IT_O,IT_S,SIL,
    15,'b','i','l','l',0xf3,'n',EOS,IT_B,IT_I,SBOUND,IT_LL,S1,IT_O,IT_N,SIL, //0xf3 = 'ó'
	20,'b','i','l','l','o','n','e', 's',EOS,IT_B,IT_I,SBOUND,IT_LL,S1,IT_O,IT_N,SBOUND,IT_E,IT_S,SIL,
	//29, 'm','i','l',' ','b','i','l','l','o','n','e','s',EOS,IT_M,S1,IT_I,IT_L,WBOUND,IT_B,IT_I,SBOUND,IT_LL,S1,IT_O,IT_N,SBOUND,IT_E,IT_S,SIL,
	17,'t','r','i','l','l',0xf3,'n',EOS,IT_T,IT_R,IT_I,SBOUND,IT_LL,S1,IT_O,IT_N,SIL, //0xf3 = 'ó'
	22,'t','r','i','l','l','o','n','e','s',EOS,IT_T,IT_R,IT_I,SBOUND,IT_LL,S1,IT_O,SBOUND,IT_N,IT_E,IT_S,SIL,
     0
};                   

const unsigned char m_jan[]="gen";
const unsigned char m_feb[]="feb";
const unsigned char m_mar[]="mar";
const unsigned char m_apr[]="apr";
const unsigned char m_may[]="mag";
const unsigned char m_jun[]="giu";
const unsigned char m_jul[]="lug";
const unsigned char m_aug[]="ago";
const unsigned char m_sep[]="set";
const unsigned char m_oct[]="ott";
const unsigned char m_nov[]="nov";
const unsigned char m_dec[]="dic";                                   

const unsigned char *CONSTCONST months[] = {
   m_jan,
   m_feb,
   m_mar,
   m_apr,
   m_may,
   m_jun,
   m_jul,
   m_aug,
   m_sep,
   m_oct,
   m_nov,
   m_dec,
   NULL
};

const unsigned char pdegree[] = {
	IT_G,    IT_R,    S1,     IT_A,    SBOUND, IT_DH,    IT_O,WBOUND ,    SIL
};

/* CAB Removed no longer used
unsigned char      pdash[] = {
	IT_G,   IT_I,    S1,     IT_O,    IT_N,WBOUND,     SIL
};
*/

const unsigned char pminus[] = {
	IT_M,    S1,     IT_E,    SBOUND, IT_N,    IT_O,    IT_S,WBOUND,     SIL
};


const unsigned char p0[] = {
	IT_TS, S1, IT_EP, IT_RR, IT_OP, WBOUND, SIL
};

const unsigned char p1[] = {
	S1 , IT_UW, IT_N , IT_OP, WBOUND,     SIL
};

const unsigned char p1_uno[] = {
	S1 , IT_UW, IT_N , IT_OP, WBOUND,     SIL
};

const unsigned char p1_un[] = {
	S1 , IT_UW, IT_N , IT_OP, WBOUND,     SIL
};

const unsigned char p2[] = {
	IT_D , S1, IT_UW, IT_EP ,WBOUND,     SIL
};

const unsigned char p3[] = {
	IT_T , IT_RR, IT_EP,IT_RAF, WBOUND,     SIL
};

const unsigned char p3_open[] = {
	IT_T , IT_RR, IT_EH,WBOUND,     SIL
};

const unsigned char p4[] = {
	IT_K , IT_W , S1, IT_AP, IT_T , IT_T , IT_RR, IT_OP,WBOUND,     SIL
};

const unsigned char p5[] = {
	IT_CH, S1, IT_IY, IT_N, IT_G, IT_K , IT_W , IT_EP,WBOUND,     SIL
};

const unsigned char p6[] = {
	 IT_S , S1, IT_EH, IT_Y ,IT_RAF, WBOUND,     SIL
};


const unsigned char p7[] = {
	IT_S , S1, IT_EH, IT_T , IT_T , IT_EP ,WBOUND,     SIL
};

//what is ph7 for?? MGS HELPME may not need for italian
const unsigned char ph7[] = {
	 IT_S , S1, IT_EH, IT_T , IT_T , IT_EP ,WBOUND,     SIL
};
        
const unsigned char p8[] = {
	S1 , IT_AO, IT_T , IT_T , IT_OP,WBOUND,     SIL
};


const unsigned char p9[] = {
	 IT_N , S1, IT_AO, IT_V , IT_EP,WBOUND,     SIL
};

// MGS may not need for italian
const unsigned char ph9[] = {
	 IT_N , S1, IT_AO, IT_V , IT_EP,WBOUND,     SIL
};
        


const unsigned char up0[] = {
	IT_TS, IT_EP, IT_RR, IT_OP, WBOUND, SIL
};


const unsigned char up1[] = {
	IT_UW, IT_N , IT_OP, WBOUND,     SIL
};



const unsigned char up2[] = {
	IT_D , IT_UW, IT_EP ,WBOUND,     SIL
};


const unsigned char up3[] = {
	IT_T , IT_RR, IT_EP,WBOUND,     SIL
};


const unsigned char up4[] = {
	IT_K , IT_W , IT_AP, IT_T , IT_T , IT_RR, IT_OP,WBOUND,     SIL
};


const unsigned char up5[] = {
	IT_CH, IT_IY, IT_N, IT_G, IT_K , IT_W , IT_EP,WBOUND,     SIL
};


const unsigned char up6[] = {
	IT_S , IT_EH, IT_Y ,WBOUND,     SIL
};


const unsigned char up7[] = {
	IT_S , IT_EH, IT_T , IT_T , IT_EP ,WBOUND,     SIL
};

/* CAB 04/24/2002 Removed not used 
unsigned char      uph7[] = {
	IT_S,    IT_E,        IT_T,SBOUND,     IT_E,SBOUND,     SIL
};
*/

const unsigned char up8[] = {
	IT_AO, IT_T , IT_T , IT_OP,WBOUND,     SIL
};


const unsigned char up9[] = {
	IT_N , IT_AO, IT_V , IT_EP,WBOUND,     SIL
};

/* CAB 04/24/2002 Removed not used
unsigned char      uph9[] = {
	IT_N,     IT_O,        SBOUND, IT_BH,   IT_E,SBOUND,     SIL
};
*/

const unsigned char *CONSTCONST punits[] = {
	p0,     p1,     p2,     p3,     p4,
	p5,     p6,     p7,     p8,     p9
};
const unsigned char *CONSTCONST upunits[] = {
	up0,     up1,     up2,     up3,     up4,
	up5,     up6,     up7,     up8,     up9
};

const unsigned char ponehundred[] = {
	S1 , IT_CH, IT_EH, IT_N , IT_T , IT_OP,    SIL
};

const unsigned char phundredp[] = {
	S1 , IT_CH, IT_EH, IT_N , IT_T,  SIL
};

const unsigned char phundred[] = {
	S1 , IT_CH, IT_EH, IT_N , IT_T,  IT_OP, SIL
};

const unsigned char pfivehun[] = {
	IT_CH,   IT_IY,  IT_N, IT_K,   IT_W,    IT_EP,
	 IT_CH,  S1,  IT_EH, IT_N, IT_T, IT_OP, SIL
};

const unsigned char ponethousand[] = {
	S1 , IT_M , IT_IY, IT_L , IT_L , IT_EP,   SIL
};

const unsigned char pthousand[] = {
	S1 , IT_M , IT_IY, IT_L , IT_AP,   SIL
};

const unsigned char pmillion[] = {
        IT_M , IT_IY, S1 , IT_L , IT_Y , IT_OP, IT_N , IT_EP,         SIL
};

const unsigned char pmilliones[] = {
        IT_M , IT_IY, S1 , IT_L , IT_Y , IT_OP, IT_N , IT_IY,     SIL
};


const unsigned char ponemillion[] = {
    	S1 , IT_UW, IT_N ,    IT_M , IT_IY, S1 , IT_L , IT_Y , 
		IT_OP, IT_N , IT_EP,         SIL
};

const unsigned char pordonemillion[] = {
		S1 , IT_UW, IT_N ,    IT_M , IT_IY, S1 , IT_L , IT_Y , 
		IT_OP, IT_N , IT_EP,    IT_EH, IT_S , IT_IY, IT_M , IT_OP,            SIL
};

const unsigned char p10[] = {
	 IT_D , IT_Y , S1 ,IT_EH, IT_CH, IT_IY,WBOUND,     SIL
};

const unsigned char p11[] = {
	S1, IT_UW, IT_N,  IT_D , IT_IY, IT_CH, IT_IY,WBOUND,     SIL
};

const unsigned char p12[] = {
	S1, IT_D , IT_OP,  IT_D , IT_IY, IT_CH, IT_IY,WBOUND,     SIL
};

const unsigned char p13[] = {
	S1, IT_T , IT_RR, IT_EP,  IT_D , IT_IY, IT_CH, IT_IY,WBOUND,     SIL
};

const unsigned char p14[] = {
	IT_K , IT_W , IT_AP, IT_T,  IT_T , S1 ,IT_OP, IT_RR, IT_D , IT_IY, IT_CH, IT_IY
	,WBOUND,     SIL
};

const unsigned char p15[] = {
	S1, IT_K , IT_UW, IT_Y , IT_N,  IT_D , IT_IY, IT_CH, IT_IY,WBOUND,     SIL
};

const unsigned char p16[] = {
	 IT_S ,S1 , IT_EP, IT_D , IT_IY, IT_CH, IT_IY ,WBOUND,     SIL
};

const unsigned char p17[] = {
	IT_D , IT_IY, IT_CH, IT_AP, IT_S,  IT_S ,S1 , IT_EH, IT_TD , IT_T , IT_EP
    ,WBOUND,     SIL
};

const unsigned char p18[] = {
	IT_D , IT_IY,  IT_CH, S1 ,IT_OP, IT_TD , IT_T , IT_OP ,WBOUND, SIL
};

const unsigned char p19[] = {
	IT_D , IT_IY, IT_K , IT_AP, IT_N,  IT_N , S1 ,IT_OP, IT_V , IT_EP
    ,WBOUND,     SIL
};

const unsigned char *CONSTCONST pteens[] = {
	p10,    p11,    p12,    p13,    p14,
	p15,    p16,    p17,    p18,    p19
};

const unsigned char pnone[] = {
	SIL
};

const unsigned char p20[] = {
	 IT_V , S1 ,IT_EP, IT_N , IT_T , IT_IY ,SIL
};

const unsigned char p21[] = {
	S1 , IT_V , IT_EP, IT_N , IT_T ,SBOUND,	S1 , IT_UW, IT_N , IT_OP, WBOUND,     SIL
};

const unsigned char p2x[] = {
	S1 , IT_V , IT_EP, IT_N , IT_T ,SIL
};

const unsigned char p20only[] = {
	 IT_V , S1 ,IT_EP, IT_N , IT_T , IT_IY ,WBOUND, SIL
};

const unsigned char p30[] = {
	IT_T , IT_RR, S1 , IT_EP, IT_N , IT_T , IT_AP,     SIL
};

const unsigned char p3x[] = {
	IT_T , IT_RR, S1 , IT_EP, IT_N , IT_T ,  SIL
};

const unsigned char p40[] = {
	IT_K , IT_W , IT_AP, IT_RR, S1 ,IT_AP, IT_N , IT_T , IT_AP,   SIL
};

const unsigned char p4x[] = {
	IT_K , IT_W , IT_AP, IT_RR, S1 ,IT_AP, IT_N , IT_T , SIL
};

const unsigned char p50[] = {
	IT_CH, IT_IY, IT_N, IT_G,  IT_K , IT_W , S1 ,IT_AP, IT_N , IT_T , IT_AP,  SIL
};

const unsigned char p5x[] = {
	IT_CH, IT_IY, IT_N, IT_G,  IT_K , IT_W , S1 ,IT_AP, IT_N , IT_T ,  SIL
};

const unsigned char p60[] = {
	IT_S , IT_EP, IT_S,  IT_S ,S1 , IT_AP, IT_N , IT_T , IT_AP,     SIL
};

const unsigned char p6x[] = {
	IT_S , IT_EP, IT_S,  IT_S ,S1 , IT_AP, IT_N , IT_T ,     SIL
};

const unsigned char p70[] = {
	IT_S , IT_EP, IT_T, IT_T ,S1 ,  IT_AP, IT_N , IT_T , IT_AP,     SIL
};

const unsigned char p7x[] = {
	IT_S , IT_EP, IT_T, IT_T ,S1 ,  IT_AP, IT_N , IT_T ,     SIL
};

const unsigned char p80[] = {
	IT_OP, IT_T, IT_T ,S1 ,  IT_AP, IT_N , IT_T , IT_AP,     SIL
};

const unsigned char p8x[] = {
	IT_OP, IT_T, IT_T ,S1 ,  IT_AP, IT_N , IT_T ,     SIL
};

const unsigned char p90[] = {
	IT_N , IT_OP, IT_V , S1 , IT_AP, IT_N , IT_T , IT_AP,   SIL
};

const unsigned char p9x[] = {
	IT_N , IT_OP, IT_V , S1 , IT_AP, IT_N , IT_T ,   SIL
};

const unsigned char *CONSTCONST ptens[] = {
	pnone,  pnone,  p20,    p30,    p40,
	p50,    p60,    p70,    p80,    p90
};

const unsigned char *CONSTCONST ptens_x[] = {
	pnone,  pnone,  p2x,    p3x,    p4x,
	p5x,    p6x,    p7x,    p8x,    p9x
};

const unsigned char ppence[] = {
	IT_P,    IT_E,    SBOUND, IT_N,    S2,     IT_I,    SBOUND,
	IT_K,    IT_E,WBOUND,     SIL
};

const unsigned char ppercent[] = {
	WBOUND, IT_P,    S1,     IT_O,    IT_R,    WBOUND, IT_TH,   IT_I,
	S1,     IT_E,    IT_N,    SBOUND, IT_T,    IT_O,WBOUND,     SIL
};

const unsigned char pcent[] = {
	WBOUND, IT_TH,   IT_E,    IT_N,    SBOUND, IT_T,    S1,     IT_A,
	SBOUND, IT_BH,   IT_O,WBOUND,     SIL
};

const unsigned char peuro[] = {
	WBOUND, S1, IT_EH, IT_UW, SBOUND, IT_R, IT_OP, SIL
};
const unsigned char peuros[] = {
	WBOUND, S1, IT_EH, IT_UW, SBOUND, IT_RR, IT_IY, SIL
};

const unsigned char ppound[] = {
	WBOUND, IT_L,    S1,     IT_I,    SBOUND, IT_BH,   IT_R,    IT_A,WBOUND,     SIL
};

const unsigned char pdollar[] = {
	WBOUND, IT_D,    S1,     IT_O,    SBOUND, IT_L,    IT_A,    IT_R,WBOUND,     SIL
};

const unsigned char pand[] = {
	WBOUND, VPSTART, S2,    IT_I,WBOUND,     SIL
};

const unsigned char ppoint[] = {
	IT_V,    S1,     IT_IY,    IT_R,    SBOUND, IT_G,    IT_OP,SBOUND,IT_L, IT_AP, WBOUND,     SIL
};

const unsigned char pcomma[] = {
	IT_K,    S1,     IT_O,    SBOUND, IT_M,    IT_A,	WBOUND,     SIL
};

const unsigned char pjan[] = {
	IT_JH ,IT_EP ,IT_N, S1  ,IT_N  ,IT_AP ,IT_Y  ,IT_OP,WBOUND,     SIL
};

const unsigned char pfeb[] = {
	IT_F  ,IT_EP ,IT_B, S1  ,IT_B  ,IT_RR ,IT_AP ,IT_Y  ,IT_OP,WBOUND,     SIL
};

const unsigned char pmar[] = {
	S1  ,IT_M  ,IT_AP ,IT_RR ,IT_TS ,IT_OP,WBOUND,     SIL
};

const unsigned char papr[] = {
	S1  ,IT_AP ,IT_P  ,IT_RR ,IT_IY ,IT_L  ,IT_EP,WBOUND,     SIL
};

const unsigned char pmay[] = {
	S1  ,IT_M  ,IT_AP ,IT_D  ,IT_JH ,IT_Y  ,IT_OP,WBOUND,     SIL
};

const unsigned char pjun[] = {
	S1  ,IT_JH ,IT_UW ,IT_N,IT_Y ,IT_N,IT_Y ,IT_OP,WBOUND,     SIL
};

const unsigned char pjul[] = {
	S1  ,IT_L  ,IT_UW ,IT_G,IT_L ,IT_G,IT_L ,IT_OP,WBOUND,     SIL

};

const unsigned char paug[] = {
	IT_AP, S1  ,IT_G  ,IT_OP ,IT_S  ,IT_T  ,IT_OP, WBOUND,     SIL
};

const unsigned char psep[] = {
	IT_S  ,IT_EP ,IT_T, S1  ,IT_T  ,IT_EH ,IT_M  ,IT_B  ,IT_RR ,IT_EP ,WBOUND,     SIL
};

const unsigned char poct[] = {
	IT_OP ,IT_T, S1  ,IT_T  ,IT_OP ,IT_B  ,IT_RR ,IT_EP,WBOUND,     SIL
};

const unsigned char pnov[] = {
	IT_N  ,IT_OP, S1  ,IT_V  ,IT_EH ,IT_M  ,IT_B  ,IT_RR ,IT_EP ,WBOUND,     SIL
};

const unsigned char pdec[] = {
	IT_D  ,IT_IY, S1  ,IT_CH ,IT_EH ,IT_M  ,IT_B  ,IT_RR ,IT_EP,WBOUND,     SIL
};

const unsigned char *CONSTCONST pmonths[] = {
	pjan,   pfeb,   pmar,   papr,   pmay,   pjun,
	pjul,   paug,   psep,   poct,   pnov,   pdec,
	pjan,   papr,   paug,   pdec,
	NULL
};

const unsigned char p0th[] = {
	IT_TH,   S1,     IT_E,    SBOUND, IT_R,    SIL
};

const unsigned char p1st[] = {
	S1, IT_P , IT_RR, IT_IY, IT_M , IT_OP,     SIL
};

const unsigned char p2nd[] = {
	IT_S , IT_EP, S1 , IT_K , IT_OP, IT_N , IT_D , IT_OP,    SIL
};

const unsigned char p3rd[] = {
	S1 , IT_T , IT_EH, IT_RR, IT_TS, IT_OP,     SIL
};

const unsigned char p4th[] = {
	S1 , IT_K , IT_W , IT_AP, IT_RR, IT_T , IT_OP,    SIL
};

const unsigned char p5th[] = {
	S1, IT_K , IT_UW, IT_Y , IT_N , IT_T , IT_OP,     SIL
};

const unsigned char p6th[] = {
	S1 , IT_S , IT_EH, IT_S , IT_T , IT_OP,   SIL
};

const unsigned char p7th[] = {
	S1 , IT_S , IT_EH, IT_T , IT_T , IT_IY, IT_M , IT_OP,    SIL
};

const unsigned char p8th[] = {
	IT_OP, IT_T, S1 , IT_T , IT_AP, IT_V , IT_OP,    SIL
};

const unsigned char p9th[] = {
	S1 , IT_N , IT_OP, IT_N , IT_OP,    SIL
};

const unsigned char *CONSTCONST pordunits[] = {
	p0th,   p1st,   p2nd,   p3rd,   p4th,
	p5th,   p6th,   p7th,   p8th,   p9th
};

const unsigned char p10th[] = {
	S1 , IT_D , IT_EH, IT_CH, IT_IY, IT_M , IT_OP,       SIL
};

const unsigned char p11th[] = {
	IT_UW, IT_N, S1 , IT_D , IT_IY, IT_CH, IT_IY
	,IT_EH, IT_S , IT_IY, IT_M , IT_OP,            SIL
};

const unsigned char p12th[] = {
	IT_D , IT_OP, S1 , IT_D , IT_IY, IT_CH, IT_IY
	,IT_EH, IT_S , IT_IY, IT_M , IT_OP,            SIL
};

const unsigned char p13th[] = {
	IT_T , IT_RR, IT_EP, S1 , IT_D , IT_IY, IT_CH, IT_IY
	,IT_EH, IT_S , IT_IY, IT_M , IT_OP,            SIL
};

const unsigned char p14th[] = {
	IT_K , IT_W , IT_AP, IT_T, S1 , IT_T , IT_OP, IT_RR, IT_D , IT_IY, IT_CH, IT_IY
	,IT_EH, IT_S , IT_IY, IT_M , IT_OP,            SIL
};

const unsigned char p15th[] = {
	IT_K , IT_UW, IT_Y , IT_N, S1 , IT_D , IT_IY, IT_CH, IT_IY
	,IT_EH, IT_S , IT_IY, IT_M , IT_OP,            SIL
};

const unsigned char p16th[] = {
	S1 , IT_S , IT_EP, IT_D , IT_IY, IT_CH, IT_IY
	,IT_EH, IT_S , IT_IY, IT_M , IT_OP,            SIL
};

const unsigned char p17th[] = {
	IT_D , IT_IY, IT_CH, IT_AP, IT_S, S1 , IT_S , IT_EH, IT_T , IT_T , IT_EP
	,IT_EH, IT_S , IT_IY, IT_M , IT_OP,            SIL
};

const unsigned char p18th[] = {
	IT_D , IT_IY, S1 , IT_CH, IT_AO, IT_T , IT_T , IT_OP
	,IT_EH, IT_S , IT_IY, IT_M , IT_OP,            SIL
};

const unsigned char p19th[] = {
	IT_D , IT_IY, IT_K , IT_AP, IT_N, S1 , IT_N , IT_OP, IT_V , IT_EP
	,IT_EH, IT_S , IT_IY, IT_M , IT_OP,            SIL
};

const unsigned char *CONSTCONST pordteens[] = {
	p10th,  p11th,  p12th,  p13th,  p14th,
	p15th,  p16th,  p17th,  p18th,  p19th
};

const unsigned char p20th[] = {
	IT_V , S1 ,IT_EP, IT_N , IT_T , IT_IY,IT_EH, IT_S , IT_IY, IT_M , IT_OP,  SIL
};

const unsigned char p30th[] = {
	IT_T , IT_RR, S1 , IT_EP, IT_N , IT_T , IT_AP,IT_EH, IT_S , IT_IY, IT_M , IT_OP,  SIL
};

const unsigned char p40th[] = {
	IT_K , IT_W , IT_AP, IT_RR, S1 ,IT_AP, IT_N , IT_T , IT_AP,
		IT_EH, IT_S , IT_IY, IT_M , IT_OP,  SIL
};

const unsigned char p50th[] = {
	IT_CH, IT_IY, IT_N, IT_G,  IT_K , IT_W , S1 ,IT_AP, IT_N , IT_T , IT_AP
	,IT_EH, IT_S , IT_IY, IT_M , IT_OP,  SIL
};

const unsigned char p60th[] = {
	IT_S , IT_EP, IT_S,  IT_S ,S1 , IT_AP, IT_N , IT_T , IT_AP
		,IT_EH, IT_S , IT_IY, IT_M , IT_OP,  SIL
};

const unsigned char p70th[] = {
	IT_S , IT_EP, IT_T, IT_T ,S1 ,  IT_AP, IT_N , IT_T , IT_AP
		,IT_EH, IT_S , IT_IY, IT_M , IT_OP,  SIL
};

const unsigned char p80th[] = {
	IT_OP, IT_T, IT_T ,S1 ,  IT_AP, IT_N , IT_T , IT_AP,
		IT_EH, IT_S , IT_IY, IT_M , IT_OP,  SIL
};

const unsigned char p90th[] = {
	IT_N , IT_OP, IT_V , S1 , IT_AP, IT_N , IT_T , IT_AP,
		IT_EH, IT_S , IT_IY, IT_M , IT_OP,  SIL
};


const unsigned char pordonehundred[] = {
	S1 , IT_CH, IT_EH, IT_N , IT_T,  IT_OP, IT_EH, IT_S , IT_IY, IT_M , IT_OP,  SIL
};

const unsigned char pordthousand[] = {
	S1 , IT_M , IT_IY, IT_L , IT_L , IT_EP, IT_EH, IT_S , IT_IY, IT_M , IT_OP,  SIL
};

const unsigned char *CONSTCONST pordtens[] = {
	pnone,  pnone,  p20th,  p30th,  p40th,
	p50th,  p60th,  p70th,  p80th,  p90th
};

/* ************************ NOT USED ***************************** */
#if 0
const unsigned char phalf[] = {
	IT_M,    S1,     IT_E,    SBOUND, IT_D,    IT_I,    IT_O,WBOUND,     SIL
};

const unsigned char phalves[] = {
	IT_M,    S1,     IT_E,    SBOUND, IT_D,    IT_I,    IT_O,    IT_S,WBOUND,     SIL
};
#endif // 0
/* *************************************************************** */

/* GL 11/01/1996 use mitad to replace medio for 1/2 */
const unsigned char phalf[] = {
	IT_M,	IT_I,	SBOUND, IT_T,	S1,		IT_A,    IT_D,	WBOUND,     SIL
};

const unsigned char phalves[] = {
	IT_M,	IT_I,	SBOUND, IT_T,	S1,		IT_A,    IT_D,	IT_S,	WBOUND,     SIL
};

/* GL 10/12/1996, to fix the ordinal number error */
const unsigned char pordonehundred_g[] = {
	IT_J, IT_E, IT_N, SBOUND, IT_T, S1, IT_E, SBOUND, IT_S, IT_I, SBOUND, IT_M, SIL
};

const unsigned char o200[] = {
	IT_D, S1, IT_U, SIL
};

const unsigned char o300[] = {
	IT_T, IT_R, S1, IT_I, SIL
};

const unsigned char o400[] = {
	IT_K, IT_U, S1, IT_A, SBOUND, IT_D, IT_R, IT_I, IT_N, SIL
};

const unsigned char o500[] = {
	IT_K, S1, IT_I, IT_N, SIL
};

const unsigned char o600[] = {
	IT_S, S1, IT_E, IT_K, IT_S, SIL
};

const unsigned char o700[] = {
	IT_S, S1, IT_E, IT_P, SBOUND, IT_T, IT_I, IT_N, SIL
};

const unsigned char o800[] = {
	S1, IT_O, IT_K, SBOUND, IT_T, IT_I, IT_N, SIL
};

const unsigned char o900[] = {
	IT_N, S1, IT_O, SBOUND, IT_N, IT_I, IT_N, SIL
};

const unsigned char sdic[] = 
{
    20,'a','n','u','n','c','i','a',EOS,IT_A,SBOUND,IT_N,S1,IT_U,IT_N,SBOUND,IT_TH,IT_I,IT_A,SPECIALWORD,SIL,
    22,'a','n','u','n','c','i','a','n',EOS,IT_A,SBOUND,IT_N,S1,IT_U,IT_N,SBOUND,IT_TH,IT_I,IT_A,IT_N,SPECIALWORD,SIL,
    20,'a','n','u','n','c','i',0xf3,EOS,IT_A,SBOUND,IT_N,IT_U,IT_N,SBOUND,IT_TH,IT_I,S1,IT_O,SPECIALWORD,SIL, //0xf3 = 'ó'
    27,'a','n','u','n','c','i','a','r','o','n',EOS,IT_A,SBOUND,IT_N,IT_U,IT_N,SBOUND,IT_TH,IT_I,S1,IT_A,SBOUND,IT_R,IT_O,IT_N,SPECIALWORD,SIL,
    22,'c','o','n','t','e','s','t','a',EOS,IT_K,IT_O,IT_N,SBOUND,IT_T,S1,IT_E,IT_S,SBOUND,IT_T,IT_A,SPECIALWORD,SIL,
    24,'c','o','n','t','e','s','t','a','n',EOS,IT_K,IT_O,IT_N,SBOUND,IT_T,S1,IT_E,IT_S,SBOUND,IT_T,IT_A,IT_N,SPECIALWORD,SIL,
    22,'c','o','n','t','e','s','t',0xf3,EOS,IT_K,IT_O,IT_N,SBOUND,IT_T,IT_E,IT_S,SBOUND,IT_T,S1,IT_O,SPECIALWORD,SIL, //0xf3 = 'ó'
    29,'c','o','n','t','e','s','t','a','r','o','n',EOS,IT_K,IT_O,IT_N,SBOUND,IT_T,IT_E,IT_S,SBOUND,IT_T,S1,IT_A,SBOUND,IT_R,IT_O,IT_N,SPECIALWORD,SIL,
    13,'d','i','c','e',EOS,IT_D,S1,IT_I,SBOUND,IT_TH,IT_E,SPECIALWORD,SIL,
    15,'d','i','c','e','n',EOS,IT_D,S1,IT_I,SBOUND,IT_TH,IT_E,IT_N,SPECIALWORD,SIL,
    13,'d','i','j','o',EOS,IT_D,S1,IT_I,SBOUND,IT_J,IT_O,SPECIALWORD,SIL,
    20,'d','i','j','e','r','o','n',EOS,IT_D,IT_I,SBOUND,IT_J,S1,IT_E,SBOUND,IT_R,IT_O,IT_N,SPECIALWORD,SIL,
    21,'e','x','c','l','a','m','a',EOS,IT_E,IT_K,IT_S,SBOUND,IT_K,IT_L,S1,IT_A,SBOUND,IT_M,IT_A,SPECIALWORD,SIL,
    23,'e','x','c','l','a','m','a','n',EOS,IT_E,IT_K,IT_S,SBOUND,IT_K,IT_L,S1,IT_A,SBOUND,IT_M,IT_A,IT_N,SPECIALWORD,SIL,
    21,'e','x','c','l','a','m',0xf3,EOS,IT_E,IT_K,IT_S,SBOUND,IT_K,IT_L,IT_A,SBOUND,IT_M,S1,IT_O,SPECIALWORD,SIL, //0xf3 = 'ó'
    28,'e','x','c','l','a','m','a','r','o','n',EOS,IT_E,IT_K,IT_S,SBOUND,IT_K,IT_L,IT_A,SBOUND,IT_M,S1,IT_A,SBOUND,IT_R,IT_O,IT_N,SPECIALWORD,SIL,
    19,'e','x','p','l','i','c','a',EOS,IT_E,IT_K,IT_S,IT_P,SBOUND,IT_L,S1,IT_I,SBOUND,IT_K,IT_A,SPECIALWORD,SIL,
    21,'e','x','p','l','i','c','a','n',EOS,IT_E,IT_K,IT_S,SBOUND,IT_P,IT_L,S1,IT_I,SBOUND,IT_K,IT_A,IT_N,SPECIALWORD,SIL,
    19,'e','x','p','l','i','c',0xf3,EOS,IT_E,IT_K,IT_S,SBOUND,IT_P,IT_L,IT_I,SBOUND,IT_K,S1,IT_O,SPECIALWORD,SIL, //0xf3 = 'ó'
    28,'e','x','p','l','i','c','a','r','o','n',EOS,IT_E,IT_K,IT_S,SBOUND,IT_P,IT_L,IT_I,SBOUND,IT_K,S1,IT_A,SBOUND,IT_R,IT_O,IT_N,SPECIALWORD,SIL,
    12,'m','w','i','z','i',EOS,IT_K,S1,IT_O,IT_P,IT_I,SIL,20,'p','r','e','g','u','n','t','a',EOS,IT_P,IT_R,IT_E,IT_G,S1,IT_U,IT_N,IT_T,IT_A,SPECIALWORD,SIL,
    24,'p','r','e','g','u','n','t','a','n',EOS,IT_P,IT_R,IT_E,SBOUND,IT_G,S1,IT_U,IT_N,SBOUND,IT_T,IT_A,IT_N,SPECIALWORD,SIL,
    22,'p','r','e','g','u','n','t',0xf3,EOS,IT_P,IT_R,IT_E,SBOUND,IT_G,IT_U,IT_N,SBOUND,IT_T,S1,IT_O,SPECIALWORD,SIL, //0xf3 = 'ó'
    29,'p','r','e','g','u','n','t','a','r','o','n',EOS,IT_P,IT_R,IT_E,SBOUND,IT_G,IT_U,SBOUND,IT_N,IT_T,S1,IT_A,SBOUND,IT_R,IT_O,IT_N,SPECIALWORD,SIL,
	EOS
};

const unsigned char whdic[] = 
{
	0	
};         

const unsigned char itwhword[] = {
	7,      'd', 0xf3, 'n', 'd', 'e', EOS, SIL, //0xf3 = 'ó'
	7,      'd', 'o', 'n', 'd', 'e', EOS, SIL,
	8,      'a', 'd', 0xf3, 'n', 'd', 'e',EOS, SIL, //0xf3 = 'ó'
	6,      'c', 0xf3, 'm', 'o', EOS, SIL, //0xf3 = 'ó'
	8,      'c', 'u', 0xe1, 'n', 'd', 'o',EOS, SIL, //0xe1 = 'á'
	5,      'q', 'u', 0xe9, EOS,SIL, //0xe9 = 'é'
	5,      'q', 'u', 'e', EOS, SIL,
	6,      'c', 'u', 0xe1,'l', EOS, SIL, //0xe1 = 'á'
	8,      'c', 'u', 0xe1,'l','e','s', EOS, SIL, //0xe1 = 'á'
	7,      'q', 'u', 'i', 0xe9, 'n', EOS, SIL, //0xe9 = 'é'
	9,      'q', 'u', 'i', 0xe9, 'n','e','s', EOS, SIL, //0xe9 = 'é'
	10,		'q', 'u', 'i', 0xe9, 't','r','e', 's',EOS,SIL, //0xe9 = 'é'
	8,      'c', 'u', 0xe1,'l', 'e','s',EOS, SIL, //0xe1 = 'á'
	8,      'c', 'u', 0xe1, 'n', 't', 'o',        EOS, SIL, //0xe1 = 'á'
	8,      'c', 'u', 0xe1, 'n', 't', 'a',        EOS, SIL, //0xe1 = 'á'
	9,      'c', 'u', 0xe1, 'n', 't', 'a','s',EOS, SIL, //0xe1 = 'á'
	9,      'c', 'u', 0xe1, 'n', 't', 'o','s',EOS, SIL, //0xe1 = 'á'
	EOS
};

const unsigned char prewhword[] = {
	5,	'p', 'o', 'r', EOS, SIL,
	4,	'd', 'e', EOS, SIL,
	3,	'a', EOS, SIL,
	6,	'p', 'a', 'r','a',EOS, SIL,
	5,	'c', 'o', 'n',EOS, SIL,
	7,	'h', 'a', 'c','i','a',EOS, SIL,
	7,	'h', 'a', 's','t','a',EOS, SIL,
	7,	'd', 'e', 's','d','e',EOS, SIL,
	EOS
};

/*
 * Phonetic feature values allowed in place_it_lts[]
 *
 * Note: Spanish does not currently use FDENTAL or FALVEL.  It is
 * not clear what the proper value for [l] should be, possibly dental.
 * FLABIAL      0000001          p, b, m, f, v
 * FDENTAL      0000002          th, dh, d$
 * FPALATL      0000004          sh, zh, ch, jh
 * FALVEL       0000010          t, d, n, en, s, z, tx (not l,r,dx)
 * FVELAR       0000020          k, g, nx
 * FGLOTAL      0000040          q, tq (signals glottal stop)
 * F2BACKI      0000100          iy, y, yu, ir (IT_I IT_YX)
 * F2BACKF      0000200          iy, y, ey (IT_I IT_YX IT_E)
 */

const short place_it_lts[] = {
      0,                             /* IT_SI   */
      0,                             /* IT_A    */
      0,                             /* IT_E    */
      F2BACKI | F2BACKF,             /* IT_I    */
      0,                             /* IT_O    */
      0,                             /* IT_U    */
      FPALATL,                       /* IT_WX   */
      FPALATL | F2BACKI | F2BACKF,   /* IT_YX   */
      FALVEL,                        /* IT_RR   */
      FALVEL,                        /* IT_L    */
      FPALATL,                       /* IT_LL   */
      FLABIAL,                       /* IT_M    */
      FALVEL,                        /* IT_N    */
      FPALATL,                       /* IT_NH   */
      FLABIAL,                       /* IT_F    */
      FALVEL,                        /* IT_S    */
      FVELAR,                        /* IT_J    */
      FDENTAL,                       /* IT_TH   */
      FLABIAL,                       /* IT_BH   */
      FDENTAL,                       /* IT_DH   */
      FVELAR,                        /* IT_GH   */
      FPALATL,                       /* IT_YH   */
      FLABIAL,                       /* IT_P    */
      FLABIAL,                       /* IT_B    */
      FDENTAL,                       /* IT_T    */
      FDENTAL,                       /* IT_D    */
      FVELAR,                        /* IT_K    */
      FVELAR,                        /* IT_G    */
      FPALATL,                       /* IT_CH   */
      FPALATL+F2BACKI+F2BACKF,       /* IT_Y    */
      FALVEL,                        /* IT_R    */
      FGLOTTAL,                       /* IT_Q    */
      FALVEL,                        /* IT_Z    */
      FLABIAL,                       /* IT_W    */
      FVELAR,                        /* IT_NX   */

#ifdef IT_SH
      FPALATL,                       /* IT_SH   */
#endif

#ifdef IT_V
      FLABIAL,                       /* IT_V    */
#endif

      F2BACKI | F2BACKF,             /* IT_IX   */
      FLABIAL,                       /* IT_MX   */
      FLABIAL                        /* IT_PH   */
};

/*
 * Phonetic features:
 *
 *      FSYLL   0000001  Syllabics: vowels and dipthongs
 *      FVOICD  0000002  Voiced segments
 *      FVOWEL  0000004  Vowels
 *      FSEMIV  0000010  Semivowels (Y, W, YX, WX)
 *      FSONOR  0000020  [-obst], except IT_Q  which is [-sonor, -obst]
 *      FOBST   0000040  Occlusives, except IT_Q is [-obst]
 *      FPLOSV  0000100  Plosives, but not affricates
 *      FNASAL  0000200  Nasals
 *      FCONSON 0000400  [-syll], except for  SI and  IT_Q
 *      FSONCON 0001000  Laterals (was vd liq & glides, RR, lat's and  YH)
 *      FDIPTH  0002000  [i, u, yx, wx]
 *      FBURST  0004000  Plosives and affricates
 *      FSTMARK 0010000  Stress marks
 *      FGLOTAL 0020000  The glottal stop
 *      FVBAR   0040000  Generates voicebar
 * Note: FSYLL and FVOWEL are identical
 * [bh, dh, gh]->FOBST (needed to trigger nasal assimilation)    8-May-86
 * Note: Everything marked FOBST here must have entries in
 * the boundary value table.
 * [y] -> +FOBST, -FDIPTH -FSONOR                               12-May-86
 */

const unsigned short featb_it_lts[PHO_SYM_TOT] = {
      /* [ SIL ]  */      FSONOR,
      /* [ IT_A ]  */      FSYLL+FVOICD+FVOWEL+FSONOR,
      /* [ IT_E ]  */      FSYLL+FVOICD+FVOWEL+FSONOR,
      /* [ IT_I ]  */      FSYLL+FVOICD+FVOWEL+FSONOR+FDIPTH,
      /* [ IT_O ]  */      FSYLL+FVOICD+FVOWEL+FSONOR,
      /* [ IT_U ]  */      FSYLL+FVOICD+FVOWEL+FSONOR+FDIPTH,
      /* [ IT_WX ] */      FVOICD+FSONOR+FSEMIV+FDIPTH,
      /* [ IT_YX ] */      FVOICD+FSONOR+FSEMIV+FDIPTH,
      /* [ IT_RR ] */      FVOICD+FSONOR+FCONSON,
      /* [ IT_L ]  */      FVOICD+FSONOR+FCONSON+FSONCON,
      /* [ IT_LL ] */      FVOICD+FSONOR+FCONSON+FSONCON,
      /* [ IT_M ]  */      FVOICD+FSONOR+FNASAL+FCONSON,
      /* [ IT_N ]  */      FVOICD+FSONOR+FNASAL+FCONSON,
      /* [ IT_NH ] */      FVOICD+FSONOR+FNASAL+FCONSON,
      /* [ IT_F ]  */      FOBST+FCONSON,
      /* [ IT_S ]  */      FOBST+FCONSON,
      /* [ IT_J ]  */      FOBST+FCONSON,
      /* [ IT_TH ] */      FOBST+FCONSON,
      /* [ IT_BH ] */      FVOICD+FSONOR+FCONSON+FOBST,
      /* [ IT_DH ] */      FVOICD+FSONOR+FCONSON+FOBST,
      /* [ IT_GH ] */      FVOICD+FSONOR+FCONSON+FOBST,
      /* [ IT_YH ] */      FVOICD+FOBST+FCONSON+FBURST,   /* 23-Apr-86, 5-May */
      /* [ IT_P ]  */      FOBST+FPLOSV+FCONSON+FBURST,
      /* [ IT_B ]  */      FVOICD+FOBST+FPLOSV+FCONSON+FBURST+FVBAR,
      /* [ IT_T ]  */      FOBST+FPLOSV+FCONSON+FBURST,
      /* [ IT_D ]  */      FVOICD+FOBST+FPLOSV+FCONSON+FBURST+FVBAR,
      /* [ IT_K ]  */      FOBST+FPLOSV+FCONSON+FBURST,
      /* [ IT_G ]  */      FVOICD+FOBST+FPLOSV+FCONSON+FBURST+FVBAR,
      /* [ IT_CH ] */      FOBST+FCONSON+FBURST,
      /* [ IT_Y ]  */      FOBST+FVOICD+FCONSON,      /* 12-May-86       */
      /* [ IT_R ]  */      FVOICD+FSONOR+FCONSON,
      /* [ IT_Q ]  */      FVOICD+FGLOTTAL,
      /* [ IT_Z ]  */      FVOICD+FOBST+FCONSON,      /* 5-May-86        */
      /* [ IT_W ]  */      FVOICD+FOBST+FCONSON+FSEMIV,
      /* [ IT_NX ] */      FVOICD+FSONOR+FNASAL+FCONSON,

#ifdef IT_SH
      /* [ IT_SH ] */      FOBST+FCONSON,
#endif

#ifdef IT_V
      /* [ IT_V ]  */      FVOICD+FSONOR+FCONSON,
#endif

      /* [ IT_IX ]  */     FVOICD+FSONOR,      /* 7-May: not a vowel     */
      /* [ IT_MX]   */     FVOICD+FSONOR+FNASAL+FCONSON,
      /* [ IT_PH ]  */     FOBST+FCONSON,
      /* [NOVALID] */     0,

      /* place holders for null range ... */
      0,0,0,0,0,0,0,0,0,0,      /* 40 ... 49 */
      0,0,0,0,0,0,0,0,0,0,      /* 50 ... 59 */
      0,0,0,0,0,0,0,0,0,0,      /* 60 ... 69 */
      0,0,0,0,0,0,0,0,0,0,      /* 70 ... 79 */
      0,0,0,0,0,0,0,0,0,0,      /* 80 ... 89 */
      0,0,0,0,0,0,0,0,0,0,      /* 90 ... 99 */
  
	  /* [BLOCK_RULES */      0,
	  /* [ S3  ]  	  */      0,
	  /* [ S2  ]  	  */      0,
	  /* [ S1  ]      */      0,
	  /* [SEMPH]  	  */      0,
	  /* [HAT_R]  	  */      0,
	  /* [HAT_FALL]   */      0,
	  /* [HAT_RF]  	  */  	  0,
	  /* [SBOUND]  	  */ 	  0,
	  /* [MBOUND]  	  */ 	  0,
	  /* [HYPHEN]  	  */ 	  0,
	  /* [WBOUND]  	  */ 	  0,0,0,0,0,0,0,0,0
	  /* The rest are zero          */
};