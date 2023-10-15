/* 
 ***********************************************************************
 *                                                                      
 *                           Copyright ©                              
 *    Copyright © 2000-2001 Force Computer, Inc., a Solectron company. All rights reserved.
 *                                                                     
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
 *    File Name:	p_all_ph.h
 *    Author:		Ed Bruckert
 *    Creation Date:6/30/00                                                  
 *                                                                             
 *    Functionality:                                                           
 *  	all phoneme codes ...but for ph so they will include the language bits
 *		making them all unique.
 *                                                                             
 ***********************************************************************       
 *                                                                             
 *	Rev	Who		Date			Description                    
 *	---	-----	-----------		---------------------------------------
 *  001	CHJ		7/20/2000		French added
 *  002	CAB		9/21/2000		Fixed copyright info.
 *  003 EAb 	02/22/2001 		REMOVE REDUNDANT INFOADD NEW GERMAN SHORT VOWELS
 *  004 CAB		02/23/2001		Updated copyright info
 *  005	CAB		12/13/2001		Recheck in branch version 1.7 because of UK_YR
 */

#ifndef P_ALL_PHH
#define P_ALL_PHH 1

#include	"l_com_ph.h"
#include	"l_all_ph.h"


/*
 * Definitions for the phonemes, under the
 * "PFUSA" font. These are offsets into the font,
 * not absolute font codes. The font code is made
 * by saying "(PFUSA<<PSFONT) + code". May tables are
 * indexed by these values; don't change them unless
 * you are very careful. Dennis made some changes
 * to these for the new synthesizer.
 */

//#define SIL		  ( PFUSA<<PSFONT) |0		/* Must be zero			*/
#define USP_IY		 (( PFUSA<<PSFONT) |US_IY)
#define USP_IH		 (( PFUSA<<PSFONT) |US_IH)
#define USP_EY		 (( PFUSA<<PSFONT) |US_EY)
#define USP_EH		 (( PFUSA<<PSFONT) |US_EH)
#define USP_AE		 (( PFUSA<<PSFONT) |US_AE)
#define USP_AA		 (( PFUSA<<PSFONT) |US_AA)
#define USP_AY		 (( PFUSA<<PSFONT) |US_AY)
#define USP_AW		 (( PFUSA<<PSFONT) |US_AW)
#define USP_AH		 (( PFUSA<<PSFONT) |US_AH)
#define USP_AO		(( PFUSA<<PSFONT) |US_AO)
#define USP_OW		(( PFUSA<<PSFONT) |US_OW)
#define USP_OY		(( PFUSA<<PSFONT) |US_OY)
#define USP_UH		(( PFUSA<<PSFONT) |US_UH)
#define USP_UW		(( PFUSA<<PSFONT) |US_UW)
#define USP_RR		(( PFUSA<<PSFONT) |US_RR)
#define USP_YU		(( PFUSA<<PSFONT) |US_YU)
#define USP_AX		(( PFUSA<<PSFONT) |US_AX)
#define USP_IX		(( PFUSA<<PSFONT) |US_IX)
#define USP_IR		(( PFUSA<<PSFONT) |US_IR)
#define USP_ER		(( PFUSA<<PSFONT) |US_ER)
#define USP_AR		(( PFUSA<<PSFONT) |US_AR)
#define USP_OR		(( PFUSA<<PSFONT) |US_OR)
#define USP_UR		(( PFUSA<<PSFONT) |US_UR)
#define USP_W		(( PFUSA<<PSFONT) |US_W)
#define USP_YX		(( PFUSA<<PSFONT) |US_Y)
#define USP_R		(( PFUSA<<PSFONT) |US_R)
#define USP_LL		(( PFUSA<<PSFONT) |US_LL)
#define USP_HX		(( PFUSA<<PSFONT) |US_HX)
#define USP_RX		(( PFUSA<<PSFONT) |US_RX)
#define USP_LX		(( PFUSA<<PSFONT) |US_LX)
#define USP_M		(( PFUSA<<PSFONT) |US_M)
#define USP_N		(( PFUSA<<PSFONT) |US_N)
#define USP_NX		(( PFUSA<<PSFONT) |US_NX)
#define USP_EL		(( PFUSA<<PSFONT) |US_EL)
#define USP_DZ		(( PFUSA<<PSFONT) |US_DZ)
#define USP_EN		(( PFUSA<<PSFONT) |US_EN)
#define USP_F		(( PFUSA<<PSFONT) |US_F)
#define USP_V		(( PFUSA<<PSFONT) |US_V)
#define USP_TH		(( PFUSA<<PSFONT) |US_TH)
#define USP_DH		(( PFUSA<<PSFONT) |US_DH)
#define USP_S		(( PFUSA<<PSFONT) |US_S)
#define USP_Z		(( PFUSA<<PSFONT) |US_Z)
#define USP_SH		(( PFUSA<<PSFONT) |US_SH)
#define USP_ZH		(( PFUSA<<PSFONT) |US_ZH)
#define USP_P		(( PFUSA<<PSFONT) |US_P)
#define USP_B		(( PFUSA<<PSFONT) |US_B)
#define USP_T		(( PFUSA<<PSFONT) |US_T)
#define USP_D		(( PFUSA<<PSFONT) |US_D)
#define USP_K		(( PFUSA<<PSFONT) |US_K)
#define USP_G		(( PFUSA<<PSFONT) |US_G)
#define USP_DX		(( PFUSA<<PSFONT) |US_DX)
#define USP_TX		(( PFUSA<<PSFONT) |US_TX)
#define USP_Q		(( PFUSA<<PSFONT) |US_Q)
		/* glottal stop			*/
#define USP_CH		(( PFUSA<<PSFONT) |US_CH)
#define USP_JH		(( PFUSA<<PSFONT) |US_JH)
#define USP_DF		(( PFUSA<<PSFONT) |US_DF)
#define USP_TZ		(( PFUSA<<PSFONT) |US_TZ)
#define USP_CZ		(( PFUSA<<PSFONT) |US_CZ)
#define USP_LY		(( PFUSA<<PSFONT) |US_LY)
#define USP_RE		(( PFUSA<<PSFONT) |US_RE)
#define USP_X1		(( PFUSA<<PSFONT) |US_X1)
#define USP_X2		(( PFUSA<<PSFONT) |US_X2)
#define USP_X3		(( PFUSA<<PSFONT) |US_X3)
#define USP_X4		(( PFUSA<<PSFONT) |US_X4)
#define USP_X5		(( PFUSA<<PSFONT) |US_X5)
#define USP_X6		(( PFUSA<<PSFONT) |US_X6)
#define USP_X7		(( PFUSA<<PSFONT) |US_X7)
#define USP_X8		(( PFUSA<<PSFONT) |US_X8)
#define USP_X9		(( PFUSA<<PSFONT) |US_X9)
#define USP_Z1		(( PFUSA<<PSFONT) |US_Z1)

#define UKP_IY		 (( PFUK<<PSFONT) |UK_IY)
#define UKP_IH		 (( PFUK<<PSFONT) |UK_IH)
#define UKP_EY		 (( PFUK<<PSFONT) |UK_EY)
#define UKP_EH		 (( PFUK<<PSFONT) |UK_EH)
#define UKP_AE		 (( PFUK<<PSFONT) |UK_AE)
#define UKP_AA		 (( PFUK<<PSFONT) |UK_AA)
#define UKP_AY		 (( PFUK<<PSFONT) |UK_AY)
#define UKP_AW		 (( PFUK<<PSFONT) |UK_AW)
#define UKP_AH		 (( PFUK<<PSFONT) |UK_AH)
#define UKP_AO		(( PFUK<<PSFONT) |UK_AO)
#define UKP_OW		(( PFUK<<PSFONT) |UK_OW)
#define UKP_OY		(( PFUK<<PSFONT) |UK_OY)
#define UKP_UH		(( PFUK<<PSFONT) |UK_UH)
#define UKP_UW		(( PFUK<<PSFONT) |UK_UW)
#define UKP_RR		(( PFUK<<PSFONT) |UK_RR)
#define UKP_YU		(( PFUK<<PSFONT) |UK_YU)
#define UKP_AX		(( PFUK<<PSFONT) |UK_AX)
#define UKP_IX		(( PFUK<<PSFONT) |UK_IX)
#define UKP_IR		(( PFUK<<PSFONT) |UK_IR)
#define UKP_ER		(( PFUK<<PSFONT) |UK_ER)
#define UKP_AR		(( PFUK<<PSFONT) |UK_AR)
#define UKP_OR		(( PFUK<<PSFONT) |UK_OR)
#define UKP_UR		(( PFUK<<PSFONT) |UK_UR)
#define UKP_W		(( PFUK<<PSFONT) |UK_W)
#define UKP_Y		(( PFUK<<PSFONT) |UK_Y)
#define UKP_R		(( PFUK<<PSFONT) |UK_R)
#define UKP_LL		(( PFUK<<PSFONT) |UK_LL)
#define UKP_HX		(( PFUK<<PSFONT) |UK_HX)
#define UKP_OH		(( PFUK<<PSFONT) |UK_OH)
#define UKP_LX		(( PFUK<<PSFONT) |UK_LX)
#define UKP_M		(( PFUK<<PSFONT) |UK_M)
#define UKP_N		(( PFUK<<PSFONT) |UK_N)
#define UKP_NX		(( PFUK<<PSFONT) |UK_NX)
#define UKP_EL		(( PFUK<<PSFONT) |UK_EL)
#define UKP_DZ		(( PFUK<<PSFONT) |UK_DZ)
#define UKP_EN		(( PFUK<<PSFONT) |UK_EN)
#define UKP_F		(( PFUK<<PSFONT) |UK_F)
#define UKP_V		(( PFUK<<PSFONT) |UK_V)
#define UKP_TH		(( PFUK<<PSFONT) |UK_TH)
#define UKP_DH		(( PFUK<<PSFONT) |UK_DH)
#define UKP_S		(( PFUK<<PSFONT) |UK_S)
#define UKP_Z		(( PFUK<<PSFONT) |UK_Z)
#define UKP_SH		(( PFUK<<PSFONT) |UK_SH)
#define UKP_ZH		(( PFUK<<PSFONT) |UK_ZH)
#define UKP_P		(( PFUK<<PSFONT) |UK_P)
#define UKP_B		(( PFUK<<PSFONT) |UK_B)
#define UKP_T		(( PFUK<<PSFONT) |UK_T)
#define UKP_D		(( PFUK<<PSFONT) |UK_D)
#define UKP_K		(( PFUK<<PSFONT) |UK_K)
#define UKP_G		(( PFUK<<PSFONT) |UK_G)
#define UKP_YR		(( PFUK<<PSFONT) |UK_YR)
/***** Is this supposed to be this way - two '51's ?? */
/* GL 09/30/1997  need to remove the next definition after PH/UK fully function */
#define UKP_DX		(( PFUK<<PSFONT) |UK_DX)
#define UKP_TX		(( PFUK<<PSFONT) |UK_TX)
#define UKP_Q		(( PFUK<<PSFONT) |UK_Q	)
#define UKP_CH		(( PFUK<<PSFONT) |UK_CH)
#define UKP_JH		(( PFUK<<PSFONT) |UK_JH)
#define UKP_DF		(( PFUK<<PSFONT) |UK_DF)

#define GRP_A		 (( PFGR<<PSFONT) |GR_A)              /* mAnn                         */
#define GRP_E		 (( PFGR<<PSFONT) |GR_E)              /* Englisch                     */
#define GRP_AE		 (( PFGR<<PSFONT) |GR_AE)              /* cAt (amreican)              */
#define GRP_EX		 (( PFGR<<PSFONT) |GR_EX)              /* gabE                         */
#define GRP_I		 (( PFGR<<PSFONT) |GR_I)              /* mIt                          */
#define GRP_O		 (( PFGR<<PSFONT) |GR_O)              /* pOst                         */
#define GRP_OE		 (( PFGR<<PSFONT) |GR_OE)              /* kOEnnen                      */
#define GRP_U		 (( PFGR<<PSFONT) |GR_U)              /* mUnd                         */
#define GRP_UE		 (( PFGR<<PSFONT) |GR_UE)              /* lUEcke                       */
#define GRP_AH		(( PFGR<<PSFONT) |GR_AH)              /* sAgen                        */
#define GRP_EH		(( PFGR<<PSFONT) |GR_EH)              /* gEben                        */
#define GRP_AEH		(( PFGR<<PSFONT) |GR_AE)              /* wAEhlen                      */
#define GRP_IH		(( PFGR<<PSFONT) |GR_IH)              /* lIEb                         */
#define GRP_OH		(( PFGR<<PSFONT) |GR_OH)              /* mOnd                         */
#define GRP_OEH		(( PFGR<<PSFONT) |GR_OE)              /* mOEgen                       */
#define GRP_UH		(( PFGR<<PSFONT) |GR_UH)              /* hUt                          */
#define GRP_UEH		(( PFGR<<PSFONT) |GR_UE)              /* hUEten                       */
#define GRP_EI		(( PFGR<<PSFONT) |GR_EI)              /* klEId                        */
#define GRP_AU		(( PFGR<<PSFONT) |GR_AU)              /* hAUs                         */
#define GRP_EU		(( PFGR<<PSFONT) |GR_EU)              /* hEUte                        */
#define GRP_AN		(( PFGR<<PSFONT) |GR_AN)              /* pENsion                      */
#define GRP_IM		(( PFGR<<PSFONT) |GR_IM)              /* tIMbre                       */
#define GRP_UM		(( PFGR<<PSFONT) |GR_UM)              /* parfUM                       */
#define GRP_ON		(( PFGR<<PSFONT) |GR_ON)              /* fONdue                       */
#define GRP_J		(( PFGR<<PSFONT) |GR_J	)              /* Ja                           */
#define GRP_L		(( PFGR<<PSFONT) |GR_L	)              /* Luft                         */
#define GRP_RR		(( PFGR<<PSFONT) |GR_RR)              /* Rund                         */
#define GRP_R		(( PFGR<<PSFONT) |GR_R	)              /* waR                          */
#define GRP_H		(( PFGR<<PSFONT) |GR_H	)              /* Hut                          */
#define GRP_M		(( PFGR<<PSFONT) |GR_M	)              /* Mut                          */
#define GRP_N		(( PFGR<<PSFONT) |GR_N	)              /* NeiN                         */
#define GRP_NG		(( PFGR<<PSFONT) |GR_NG)              /* riNG                         */
#define GRP_EL		(( PFGR<<PSFONT) |GR_EL)              /* nabEL                        */
#define GRP_EM		(( PFGR<<PSFONT) |GR_EM)              /* grossEM                      */
#define GRP_EN		(( PFGR<<PSFONT) |GR_EN)              /* badEN                        */
#define GRP_F		(( PFGR<<PSFONT) |GR_F	)              /* Fall                         */
#define GRP_V		(( PFGR<<PSFONT) |GR_V	)              /* Was                          */      
#define GRP_S		(( PFGR<<PSFONT) |GR_S	)              /* meSSen                       */
#define GRP_Z		(( PFGR<<PSFONT) |GR_Z	)              /* doSe                         */
#define GRP_SH		(( PFGR<<PSFONT) |GR_SH)              /* SCHule                       */
#define GRP_ZH		(( PFGR<<PSFONT) |GR_ZH)              /* Genie                        */
#define GRP_CH		(( PFGR<<PSFONT) |GR_CH)              /* niCHt                        */
#define GRP_KH		(( PFGR<<PSFONT) |GR_KH)              /* noCH                         */
#define GRP_P		(( PFGR<<PSFONT) |GR_P	)              /* Park                         */
#define GRP_B		(( PFGR<<PSFONT) |GR_B	)              /* Ball                         */
#define GRP_T		(( PFGR<<PSFONT) |GR_T	)              /* Turm                         */
#define GRP_D		(( PFGR<<PSFONT) |GR_D	)              /* Dort                         */
#define GRP_K		(( PFGR<<PSFONT) |GR_K	)              /* Kalt                         */
#define GRP_G		(( PFGR<<PSFONT) |GR_G	)              /* Gast                         */
#define GRP_Q		(( PFGR<<PSFONT) |GR_Q	)              /* beP_amtet                     */
#define GRP_PF		(( PFGR<<PSFONT) |GR_PF)              /* PFerd                        */
#define GRP_TS		(( PFGR<<PSFONT) |GR_TS)              /* Zahl                         */
#define GRP_DJ		(( PFGR<<PSFONT) |GR_DJ)              /* Gin                          */
#define GRP_TJ		(( PFGR<<PSFONT) |GR_TJ)              /* maTSCH                       */
#define GRP_KSX		(( PFGR<<PSFONT) |GR_KSX)              /* eXtra                        */
#define GRP_I1		(( PFGR<<PSFONT) |GR_I1)              /* short 3                      */
#define GRP_E1		(( PFGR<<PSFONT) |GR_E1)              /* short 2                      */
#define GRP_O1		(( PFGR<<PSFONT) |GR_O1)              /* short 4                      */
#define GRP_U1		(( PFGR<<PSFONT) |GR_U1)              /* short 5                      */
#define GRP_Y1		(( PFGR<<PSFONT) |GR_Y1)              /* short 6                      */
#define GRP_ER		(( PFGR<<PSFONT) |GR_ER)              /*                 */

#define LAP_A		 (( PFLA<<PSFONT) |LA_A)               /*       Palabra        */
#define LAP_E		 (( PFLA<<PSFONT) |LA_E)               /*       Leo            */
#define LAP_I		 (( PFLA<<PSFONT) |LA_I)               /*       Hilo           */
#define LAP_O		 (( PFLA<<PSFONT) |LA_O)               /*       Hola           */
#define LAP_U		 (( PFLA<<PSFONT) |LA_U)               /*       Lunes          */
#define LAP_WX		 (( PFLA<<PSFONT) |LA_WX)               /* Rounded dipth semiv. */
#define LAP_YX		 (( PFLA<<PSFONT) |LA_YX)               /* Unround dipth semiv. */
#define LAP_RR		 (( PFLA<<PSFONT) |LA_RR)               /*       Rama           */
#define LAP_L		 (( PFLA<<PSFONT) |LA_L)               /*       Luna           */
#define LAP_LL		(( PFLA<<PSFONT) |LA_LL)              /*       Calle          */
#define LAP_M		(( PFLA<<PSFONT) |LA_M	)              /*       Mama'          */
#define LAP_N		(( PFLA<<PSFONT) |LA_N	)              /*       Nana           */
#define LAP_NH		(( PFLA<<PSFONT) |LA_NH)              /*       Munoz          */
#define LAP_F		(( PFLA<<PSFONT) |LA_F	)              /*       Feo            */
#define LAP_S		(( PFLA<<PSFONT) |LA_S	)              /*       Casa           */
#define LAP_J		(( PFLA<<PSFONT) |LA_J	)              /*       Caja           */
#define LAP_TH		(( PFLA<<PSFONT) |LA_TH)              /*       Caza           */
#define LAP_BH		(( PFLA<<PSFONT) |LA_BH)              /*       Haba           */
#define LAP_DH		(( PFLA<<PSFONT) |LA_DH)              /*       Hada           */
#define LAP_GH		(( PFLA<<PSFONT) |LA_GH)              /*       Haga           */
#define LAP_YH		(( PFLA<<PSFONT) |LA_YH)              /*       Yate affricate */
#define LAP_P		(( PFLA<<PSFONT) |LA_P	)              /*       Papa'          */
#define LAP_B		(( PFLA<<PSFONT) |LA_B	)              /*       Barco          */
#define LAP_T		(( PFLA<<PSFONT) |LA_T	)              /*       Tela           */
#define LAP_D		(( PFLA<<PSFONT) |LA_D	)              /*       Dama           */
#define LAP_K		(( PFLA<<PSFONT) |LA_K	)              /*       Casa           */
#define LAP_G		(( PFLA<<PSFONT) |LA_G	)              /*       Gasa           */
#define LAP_CH		(( PFLA<<PSFONT) |LA_CH)              /*       Charco         */
#define LAP_Y		(( PFLA<<PSFONT) |LA_Y	)              /*       Haya fricitive */
#define LAP_R		(( PFLA<<PSFONT) |LA_R	)              /*       Sara           */
#define LAP_Q		(( PFLA<<PSFONT) |LA_Q	)              /*       ~n offglide    */
#define LAP_Z		(( PFLA<<PSFONT) |LA_Z	)              /*       Desde          */
#define LAP_W		(( PFLA<<PSFONT) |LA_W	)              /*       Hueso          */
#define LAP_NX		(( PFLA<<PSFONT) |LA_NX)              /*       Mango          */
#define LAP_V		(( PFLA<<PSFONT) |LA_V	)              /*       Afgano         */
#define LAP_IX		(( PFLA<<PSFONT) |LA_IX)              /*       ~n offglide    */
#define LAP_MX		(( PFLA<<PSFONT) |LA_MX)              /*       Infierno (nf)  */
#define LAP_PH		(( PFLA<<PSFONT) |LA_PH )             /*       Observar       */


#define SPP_A		((PFSP<<PSFONT) |SP_A	)               /*       Palabra        */
#define SPP_E		((PFSP<<PSFONT) |SP_E	)               /*       Leo            */
#define SPP_I		((PFSP<<PSFONT) |SP_I	)               /*       Hilo           */
#define SPP_O		((PFSP<<PSFONT) |SP_O	)               /*       Hola           */
#define SPP_U 		((PFSP<<PSFONT) |SP_U )               /*       Lunes          */
#define SPP_WX		((PFSP<<PSFONT) |SP_WX)               /* Rounded dipth semiv. */
#define SPP_YX		((PFSP<<PSFONT) |SP_YX)               /* Unround dipth semiv. */
#define SPP_RR		((PFSP<<PSFONT) |SP_RR)               /*       Rama           */
#define SPP_L		((PFSP<<PSFONT) |SP_L	)               /*       Luna           */
#define SPP_LL		((PFSP<<PSFONT) |SP_LL)              /*       Calle          */
#define SPP_M		((PFSP<<PSFONT) |SP_M)              /*       Mama'          */
#define SPP_N		((PFSP<<PSFONT) |SP_N)              /*       Nana           */
#define SPP_NH		((PFSP<<PSFONT) |SP_NH)              /*       Munoz          */
#define SPP_F		((PFSP<<PSFONT) |SP_F)              /*       Feo            */
#define SPP_S		((PFSP<<PSFONT) |SP_S)              /*       Casa           */
#define SPP_J		((PFSP<<PSFONT) |SP_J)              /*       Caja           */
#define SPP_TH		((PFSP<<PSFONT) |SP_TH)              /*       Caza           */
#define SPP_BH		((PFSP<<PSFONT) |SP_BH)              /*       Haba           */
#define SPP_DH		((PFSP<<PSFONT) |SP_DH)              /*       Hada           */
#define SPP_GH		((PFSP<<PSFONT) |SP_GH)              /*       Haga           */
#define SPP_YH		((PFSP<<PSFONT) |SP_YH)              /*       Yate affricate */
#define SPP_P		((PFSP<<PSFONT) |SP_P)              /*       Papa'          */
#define SPP_B		((PFSP<<PSFONT) |SP_B)              /*       Barco          */
#define SPP_T		((PFSP<<PSFONT) |SP_T)              /*       Tela           */
#define SPP_D		((PFSP<<PSFONT) |SP_D)              /*       Dama           */
#define SPP_K		((PFSP<<PSFONT) |SP_K)              /*       Casa           */
#define SPP_G		((PFSP<<PSFONT) |SP_G)              /*       Gasa           */
#define SPP_CH		((PFSP<<PSFONT) |SP_CH)              /*       Charco         */
#define SPP_Y		((PFSP<<PSFONT) |SP_Y)              /*       Haya fricitive */
#define SPP_R		((PFSP<<PSFONT) |SP_R)              /*       Sara           */
#define SPP_Q		((PFSP<<PSFONT) |SP_Q)              /*       ~n offglide    */
#define SPP_Z		((PFSP<<PSFONT) |SP_Z)              /*       Desde          */
#define SPP_W		((PFSP<<PSFONT) |SP_W)              /*       Hueso          */
#define SPP_NX		((PFSP<<PSFONT) |SP_NX)              /*       Mango          */
#define SPP_V		((PFSP<<PSFONT) |SP_V)              /*       Afgano         */
#define SPP_IX		((PFSP<<PSFONT) |SP_IX)              /*       ~n offglide    */
#define SPP_MX		((PFSP<<PSFONT) |SP_MX)              /*       Infierno ((nf)  */
#define SPP_PH		((PFSP<<PSFONT) |SP_PH)              /*       Observar       */

#define ITP_AP		    ((PFIT<<PSFONT) |IT_AP )
#define ITP_EP		    ((PFIT<<PSFONT) |IT_EP )
#define ITP_IY		    ((PFIT<<PSFONT) |IT_IY )
#define ITP_OP		    ((PFIT<<PSFONT) |IT_OP )
#define ITP_UW		    ((PFIT<<PSFONT) |IT_UW )
#define ITP_AX		    ((PFIT<<PSFONT) |IT_AX )
#define ITP_Y		    ((PFIT<<PSFONT) |IT_Y  )
#define ITP_RR		    ((PFIT<<PSFONT) |IT_RR )
#define ITP_L		    ((PFIT<<PSFONT) |IT_L  )
#define ITP_LL		    ((PFIT<<PSFONT) |IT_LL )
#define ITP_M		    ((PFIT<<PSFONT) |IT_M  )
#define ITP_N		    ((PFIT<<PSFONT) |IT_N  )
#define ITP_NH		    ((PFIT<<PSFONT) |IT_NH )
#define ITP_F		    ((PFIT<<PSFONT) |IT_F  )
#define ITP_S		    ((PFIT<<PSFONT) |IT_S  )
#define ITP_EH		    ((PFIT<<PSFONT) |IT_EH )
#define ITP_TD		    ((PFIT<<PSFONT) |IT_TD )
#define ITP_BD		    ((PFIT<<PSFONT) |IT_BD )
#define ITP_DD		    ((PFIT<<PSFONT) |IT_DD )
#define ITP_GD		    ((PFIT<<PSFONT) |IT_GD )
#define ITP_JH		    ((PFIT<<PSFONT) |IT_JH )
#define ITP_P		    ((PFIT<<PSFONT) |IT_P  )
#define ITP_B		    ((PFIT<<PSFONT) |IT_B  )
#define ITP_T		    ((PFIT<<PSFONT) |IT_T  )
#define ITP_D		    ((PFIT<<PSFONT) |IT_D  )
#define ITP_K		    ((PFIT<<PSFONT) |IT_K  )
#define ITP_G		    ((PFIT<<PSFONT) |IT_G  )
#define ITP_CH		    ((PFIT<<PSFONT) |IT_CH )
#define ITP_AO		    ((PFIT<<PSFONT) |IT_AO )
#define ITP_R		    ((PFIT<<PSFONT) |IT_R  )
#define ITP_KD		    ((PFIT<<PSFONT) |IT_KD )
#define ITP_Z		    ((PFIT<<PSFONT) |IT_Z  )
#define ITP_W		    ((PFIT<<PSFONT) |IT_W  )
#define ITP_NX		    ((PFIT<<PSFONT) |IT_NX )
#define ITP_V		    ((PFIT<<PSFONT) |IT_V  )
#define ITP_ND		    ((PFIT<<PSFONT) |IT_ND )
#define ITP_MF		    ((PFIT<<PSFONT) |IT_MF )
#define ITP_PD		    ((PFIT<<PSFONT) |IT_PD )
#define ITP_NJ			((PFIT<<PSFONT) |IT_NJ )
#define ITP_SH			((PFIT<<PSFONT) |IT_SH )
#define ITP_TS		    ((PFIT<<PSFONT) |IT_TS )
#define ITP_DZ		    ((PFIT<<PSFONT) |IT_DZ )          
#define ITP_RAF		    ((PFIT<<PSFONT) |IT_RAF )  // for Raforzamento sintattico  This will self destruct on 12/25/04  MGS  



#define FP_A      	((PFFR<<PSFONT) |F_A)
#define FP_A3     	((PFFR<<PSFONT) |F_A3)
#define FP_E2     	((PFFR<<PSFONT) |F_E2)
#define FP_AU     	((PFFR<<PSFONT) |F_AU)
#define FP_E      	((PFFR<<PSFONT) |F_E)
#define FP_E1     	((PFFR<<PSFONT) |F_E1)
#define FP_EU     	((PFFR<<PSFONT) |F_EU)
#define FP_I      	((PFFR<<PSFONT) |F_I)
#define FP_O      	((PFFR<<PSFONT) |F_O)
#define FP_O6     	((PFFR<<PSFONT) |F_O6)
#define FP_OU     	((PFFR<<PSFONT) |F_OU)
#define FP_U      	((PFFR<<PSFONT) |F_U)
#define FP_AN     	((PFFR<<PSFONT) |F_AN)
#define FP_IN     	((PFFR<<PSFONT) |F_IN)
#define FP_ON     	((PFFR<<PSFONT) |F_ON)
#define FP_UN     	((PFFR<<PSFONT) |F_UN)
#define FP_AP    	((PFFR<<PSFONT) |F_AP)
#define FP_L      	((PFFR<<PSFONT) |F_L)
#define FP_R      	((PFFR<<PSFONT) |F_R)
#define FP_W      	((PFFR<<PSFONT) |F_W)
#define FP_WU     	((PFFR<<PSFONT) |F_WU)
#define FP_Y      	((PFFR<<PSFONT) |F_Y)
#define FP_CH     	((PFFR<<PSFONT) |F_CH)
#define FP_F      	((PFFR<<PSFONT) |F_F)
#define FP_J      	((PFFR<<PSFONT) |F_J)
#define FP_RX     	((PFFR<<PSFONT) |F_RX)
#define FP_S      	((PFFR<<PSFONT) |F_S)
#define FP_V      	((PFFR<<PSFONT) |F_V)
#define FP_Z      	((PFFR<<PSFONT) |F_Z)
#define FP_B      	((PFFR<<PSFONT) |F_B)
#define FP_D      	((PFFR<<PSFONT) |F_D)
#define FP_G      	((PFFR<<PSFONT) |F_G)
#define FP_K      	((PFFR<<PSFONT) |F_K)
#define FP_P      	((PFFR<<PSFONT) |F_P)
#define FP_T      	((PFFR<<PSFONT) |F_T)
#define FP_GN     	((PFFR<<PSFONT) |F_GN)
#define FP_M      	((PFFR<<PSFONT) |F_M)
#define FP_N      	((PFFR<<PSFONT) |F_N)
#define FP_NG     	((PFFR<<PSFONT) |F_NG)



#define JP_I 		    ((PFJP<<PSFONT) |J_I  )
#define JP_E 		    ((PFJP<<PSFONT) |J_E  )
#define JP_A 		    ((PFJP<<PSFONT) |J_A  )
#define JP_O 		    ((PFJP<<PSFONT) |J_O  )
#define JP_U 		    ((PFJP<<PSFONT) |J_U  )
#define JP_YE		    ((PFJP<<PSFONT) |J_YE )
#define JP_YA		    ((PFJP<<PSFONT) |J_YA )
#define JP_YO		    ((PFJP<<PSFONT) |J_YO )
#define JP_YU		    ((PFJP<<PSFONT) |J_YU )
#define JP_WI		    ((PFJP<<PSFONT) |J_WI )
#define JP_WE		    ((PFJP<<PSFONT) |J_WE )
#define JP_WA		    ((PFJP<<PSFONT) |J_WA )
#define JP_WO		    ((PFJP<<PSFONT) |J_WO )
#define JP_H 		    ((PFJP<<PSFONT) |J_H  )
#define JP_M 		    ((PFJP<<PSFONT) |J_M  )
#define JP_N 		    ((PFJP<<PSFONT) |J_N  )
#define JP_NG		    ((PFJP<<PSFONT) |J_NG )
#define JP_EM		    ((PFJP<<PSFONT) |J_EM )
#define JP_EN		    ((PFJP<<PSFONT) |J_EN )
#define JP_NV		    ((PFJP<<PSFONT) |J_NV )
#define JP_BH		    ((PFJP<<PSFONT) |J_BH )
#define JP_F 		    ((PFJP<<PSFONT) |J_F  )
#define JP_DH		    ((PFJP<<PSFONT) |J_DH )
#define JP_S 		    ((PFJP<<PSFONT) |J_S  )
#define JP_Z 		    ((PFJP<<PSFONT) |J_Z  )
#define JP_CX		    ((PFJP<<PSFONT) |J_CX )
#define JP_SH		    ((PFJP<<PSFONT) |J_SH )
#define JP_ZH		    ((PFJP<<PSFONT) |J_ZH )
#define JP_GH		    ((PFJP<<PSFONT) |J_GH )
#define JP_R 		    ((PFJP<<PSFONT) |J_R  )
#define JP_P 		    ((PFJP<<PSFONT) |J_P  )
#define JP_B 		    ((PFJP<<PSFONT) |J_B  )
#define JP_T 		    ((PFJP<<PSFONT) |J_T  )
#define JP_D 		    ((PFJP<<PSFONT) |J_D  )
#define JP_K 		    ((PFJP<<PSFONT) |J_K  )
#define JP_G 		    ((PFJP<<PSFONT) |J_G  )
#define JP_TS		    ((PFJP<<PSFONT) |J_TS )
#define JP_DZ			((PFJP<<PSFONT) |J_DZ )
#define JP_CH			((PFJP<<PSFONT) |J_CH )
#define JP_JH		    ((PFJP<<PSFONT) |J_JH )

#define CHP_IY	((PFCH<<PSFONT) |CH_IY )
#define CHP_UE	((PFCH<<PSFONT) |CH_UE )
#define CHP_EY	((PFCH<<PSFONT) |CH_EY )
#define CHP_EH	((PFCH<<PSFONT) |CH_EH )
#define CHP_A	((PFCH<<PSFONT) |CH_A )
#define CHP_IF	((PFCH<<PSFONT) |CH_IF )
#define CHP_IR	((PFCH<<PSFONT) |CH_IR )
#define CHP_AX	((PFCH<<PSFONT) |CH_AX )
#define CHP_UW	((PFCH<<PSFONT) |CH_UW)
#define CHP_UH	((PFCH<<PSFONT) |CH_UH )
#define CHP_UC	((PFCH<<PSFONT) |CH_UC )
#define CHP_OW	((PFCH<<PSFONT) |CH_OW )
#define CHP_WO	((PFCH<<PSFONT) |CH_WO )
#define CHP_AO	((PFCH<<PSFONT) |CH_AO )
#define CHP_AA	((PFCH<<PSFONT) |CH_AA )
#define CHP_AY	((PFCH<<PSFONT) |CH_AY )
#define CHP_AW	((PFCH<<PSFONT) |CH_AW )
#define CHP_ER	((PFCH<<PSFONT) |CH_ER )
#define CHP_M	((PFCH<<PSFONT) |CH_M )
#define CHP_N	((PFCH<<PSFONT) |CH_N )
#define CHP_NX	((PFCH<<PSFONT) |CH_NX )
#define CHP_P	((PFCH<<PSFONT) |CH_P )
#define CHP_PV	((PFCH<<PSFONT) |CH_PV )
#define CHP_T 	((PFCH<<PSFONT) |CH_T  )
#define CHP_TV	((PFCH<<PSFONT) |CH_TV )
#define CHP_K	((PFCH<<PSFONT) |CH_K )
#define CHP_KV	((PFCH<<PSFONT) |CH_KV )
#define CHP_F	((PFCH<<PSFONT) |CH_F )
#define CHP_S	((PFCH<<PSFONT) |CH_S )
#define CHP_SR	((PFCH<<PSFONT) |CH_SR )
#define CHP_ZR	((PFCH<<PSFONT) |CH_ZR )
#define CHP_TJ	((PFCH<<PSFONT) |CH_TJ )
#define CHP_CH	((PFCH<<PSFONT) |CH_CH )
#define CHP_RF	((PFCH<<PSFONT) |CH_RF )
#define CHP_Y	((PFCH<<PSFONT) |CH_Y )
#define CHP_W	((PFCH<<PSFONT) |CH_W )
#define CHP_L	((PFCH<<PSFONT) |CH_L )
#define CHP_TS	((PFCH<<PSFONT) |CH_TS )
#define CHP_DS	((PFCH<<PSFONT) |CH_DS )
#define CHP_JJ	((PFCH<<PSFONT) |CH_JJ )
#define CHP_JV	((PFCH<<PSFONT) |CH_JV )
#define CHP_T1	((PFCH<<PSFONT) |CH_T1 )
#define CHP_D1  ((PFCH<<PSFONT) |CH_D1 )
#define CHP_KH  ((PFCH<<PSFONT) |CH_KH )
#define CHP_YI  ((PFCH<<PSFONT) |CH_YI )
#define CHP_WU  ((PFCH<<PSFONT) |CH_WU )
#define CHP_AH  ((PFCH<<PSFONT) |CH_AH )
#define CHP_XR  ((PFCH<<PSFONT) |CH_XR )
#define CHP_AR  ((PFCH<<PSFONT) |CH_AR )
#define CHP_OR  ((PFCH<<PSFONT) |CH_OR )
#define CHP_1R  ((PFCH<<PSFONT) |CH_1R )
#define CHP_WR  ((PFCH<<PSFONT) |CH_WR )
#define CHP_2R  ((PFCH<<PSFONT) |CH_2R )
#define CHP_UR  ((PFCH<<PSFONT) |CH_UR )
#define CHP_3R  ((PFCH<<PSFONT) |CH_3R )
#define CHP_4R  ((PFCH<<PSFONT) |CH_4R )
#define CHP_5R  ((PFCH<<PSFONT) |CH_5R )
#define CHP_YR  ((PFCH<<PSFONT) |CH_YR )
#define CHP_X1  ((PFCH<<PSFONT) |CH_X1 )
#define CHP_X2  ((PFCH<<PSFONT) |CH_X2 )
#define CHP_X3  ((PFCH<<PSFONT) |CH_X3 )
#define CHP_X4  ((PFCH<<PSFONT) |CH_X4 )
#define CHP_X5  ((PFCH<<PSFONT) |CH_X5 )


#define KRP_IY	((PFKR<<PSFONT) |KR_IY)
#define KRP_EH	((PFKR<<PSFONT) |KR_EH)
#define KRP_AE	((PFKR<<PSFONT) |KR_AE)
#define KRP_UW	((PFKR<<PSFONT) |KR_UW)
#define KRP_UH	((PFKR<<PSFONT) |KR_UH)
#define KRP_UI	((PFKR<<PSFONT) |KR_UI)
#define KRP_OW	((PFKR<<PSFONT) |KR_OW)
#define KRP_AO	((PFKR<<PSFONT) |KR_AO)
#define KRP_AA	((PFKR<<PSFONT) |KR_AA)
#define KRP_YE	((PFKR<<PSFONT) |KR_YE)
#define KRP_YH	((PFKR<<PSFONT) |KR_YH)
#define KRP_YU	((PFKR<<PSFONT) |KR_YU)
#define KRP_YO	((PFKR<<PSFONT) |KR_YO)
#define KRP_YC	((PFKR<<PSFONT) |KR_YC)
#define KRP_YA	((PFKR<<PSFONT) |KR_YA)
#define KRP_WI	((PFKR<<PSFONT) |KR_WI)
#define KRP_WE	((PFKR<<PSFONT) |KR_WE)
#define KRP_WH	((PFKR<<PSFONT) |KR_WH)
#define KRP_WC	((PFKR<<PSFONT) |KR_WC)
#define KRP_WA	((PFKR<<PSFONT) |KR_WA)
#define KRP_M 	((PFKR<<PSFONT) |KR_M )
#define KRP_N 	((PFKR<<PSFONT) |KR_N )
#define KRP_NX	((PFKR<<PSFONT) |KR_NX)
#define KRP_P 	((PFKR<<PSFONT) |KR_P )		// Lax stop
#define KRP_PH	((PFKR<<PSFONT) |KR_PH)		// Aspirated stop
#define KRP_PP	((PFKR<<PSFONT) |KR_PP)		// Tense stop
#define KRP_B 	((PFKR<<PSFONT) |KR_B )
#define KRP_T 	((PFKR<<PSFONT) |KR_T )		// Lax unvoiced stop
#define KRP_TH	((PFKR<<PSFONT) |KR_TH)		// Aspirated stop
#define KRP_TT	((PFKR<<PSFONT) |KR_TT)		// Tense stop
#define KRP_D 	((PFKR<<PSFONT) |KR_D )
#define KRP_K 	((PFKR<<PSFONT) |KR_K )		// Lax unvoiced stop
#define KRP_KH	((PFKR<<PSFONT) |KR_KH)		// Aspirated stop
#define KRP_KK	((PFKR<<PSFONT) |KR_KK)		// Tense stop
#define KRP_G 	((PFKR<<PSFONT) |KR_G )
#define KRP_S 	((PFKR<<PSFONT) |KR_S )
#define KRP_SS	((PFKR<<PSFONT) |KR_SS)
#define KRP_SH	((PFKR<<PSFONT) |KR_SH)
#define KRP_HX	((PFKR<<PSFONT) |KR_HX)
#define KRP_Y 	((PFKR<<PSFONT) |KR_Y )
#define KRP_L 	((PFKR<<PSFONT) |KR_L )
#define KRP_DF	((PFKR<<PSFONT) |KR_DF)
#define KRP_JH	((PFKR<<PSFONT) |KR_JH)
#define KRP_CH	((PFKR<<PSFONT) |KR_CH)
#define KRP_CC	((PFKR<<PSFONT) |KR_CC)
#define KRP_WO	((PFKR<<PSFONT) |KR_WO)

/*- VOWELS -*/
#define HEP_IY    (( PFHE<<PSFONT) |HE_IY)  //  1:CHIRIK 
#define HEP_EY    (( PFHE<<PSFONT) |HE_EY)  //  2:TSERE
#define HEP_EH    (( PFHE<<PSFONT) |HE_EH)  //  3:SEGOL
#define HEP_AU    (( PFHE<<PSFONT) |HE_AU)  //  4:HOLAM (GERMAN ASHKENAZIM)
#define HEP_AH    (( PFHE<<PSFONT) |HE_AH)  //  5:PATACH
#define HEP_AO    (( PFHE<<PSFONT) |HE_AO)  // 6:QAMATS KATAN
#define HEP_O    (( PFHE<<PSFONT) |HE_O)	// 7:HOLAM, QAMATS GADOL
#define HEP_OY    (( PFHE<<PSFONT) |HE_OY)  // 8:HOLAM (SOME ASHKENAZIM)
#define HEP_U     (( PFHE<<PSFONT) |HE_U)   // 9:SHURUK, QUBUTS

#define HEP_AX    (( PFHE<<PSFONT) |HE_AX)  //  10:SHVA_NA
#define HEP_W     (( PFHE<<PSFONT) |HE_W)   // 11:WAV 
#define HEP_Y     (( PFHE<<PSFONT) |HE_Y)   // 12:YUD
#define HEP_R     (( PFHE<<PSFONT) |HE_R)   // 13:RESH
#define HEP_H     (( PFHE<<PSFONT) |HE_H)   // 14:HEY
#define HEP_L     (( PFHE<<PSFONT) |HE_L)   // 15:LAMED
#define HEP_M     (( PFHE<<PSFONT) |HE_M)   // 16:MEM
#define HEP_N     (( PFHE<<PSFONT) |HE_N)   // 17:NUHN 
#define HEP_F     (( PFHE<<PSFONT) |HE_F)   // 18:FEY
#define HEP_V     (( PFHE<<PSFONT) |HE_V)   // 19:VAV, VET
#define HEP_TH    (( PFHE<<PSFONT) |HE_TH)  // 20:THAV (TEMANI / SOME ASHKENAZI ALTERNATE)
#define HEP_S     (( PFHE<<PSFONT) |HE_S)   // 21:SAMECH, SIN, SAV
#define HEP_Z     (( PFHE<<PSFONT) |HE_Z)   // 22:ZAYIN
#define HEP_SH    (( PFHE<<PSFONT) |HE_SH)  // 23:SHIN
#define HEP_P     (( PFHE<<PSFONT) |HE_P)   // 24:PEH
#define HEP_B     (( PFHE<<PSFONT) |HE_B)   // 25:BET
#define HEP_T     (( PFHE<<PSFONT) |HE_T)   // 26:TET, TAV
#define HEP_D     (( PFHE<<PSFONT) |HE_D)   // 27:DALET
#define HEP_K     (( PFHE<<PSFONT) |HE_K)   // 28:QOF
#define HEP_G     (( PFHE<<PSFONT) |HE_G)   // 29:GIMMEL
#define HEP_Q     (( PFHE<<PSFONT) |HE_Q)   // 30:Glottal stop
#define HEP_JH    (( PFHE<<PSFONT) |HE_JH)  // 31:DJIMMEL /W DAGESH (TEMANI)
#define HEP_TS    (( PFHE<<PSFONT) |HE_TS)  // 32:TSADE
#define HEP_CH    (( PFHE<<PSFONT) |HE_CH)  // 33:CHAF >>> Moved to Uvular

#define HEP_E1    (( PFHE<<PSFONT) |HE_E1)  //  34:CHATAF_SEGOL
#define HEP_A1    (( PFHE<<PSFONT) |HE_A1)  //  35:CHATAF_PATACH
#define HEP_O1    (( PFHE<<PSFONT) |HE_O1)  // 36:CHATAF_QAMATS
#define HEP_O2    (( PFHE<<PSFONT) |HE_O2)  // 37:QAMATS GADOL (ALTERNATE)
#define HEP_YY    (( PFHE<<PSFONT) |HE_YY)  // 38:YUD /W DAGESH
#define HEP_RR    (( PFHE<<PSFONT) |HE_RR)  // 39:RESH /W DAGESH
#define HEP_HH    (( PFHE<<PSFONT) |HE_HH)  // 40:MAPIK HEY
#define HEP_LL    (( PFHE<<PSFONT) |HE_LL)  // 41:LAMED /W DAGESH
#define HEP_MM    (( PFHE<<PSFONT) |HE_MM)  // 42:MEM /W DAGESH
#define HEP_NN    (( PFHE<<PSFONT) |HE_NN)  // 43:NUHN /W DAGESH
#define HEP_VV    (( PFHE<<PSFONT) |HE_VV)  // 44:VAV /W DAGESH
#define HEP_SS    (( PFHE<<PSFONT) |HE_SS)  // 45:SAMECH /W DAGESH
#define HEP_ZZ    (( PFHE<<PSFONT) |HE_ZZ)  // 46:ZAYIN /W DAGESH
#define HEP_PP     (( PFHE<<PSFONT) |HE_PP)   // 47:PEH
#define HEP_BB     (( PFHE<<PSFONT) |HE_BB)   // 48:BET
#define HEP_TT    (( PFHE<<PSFONT) |HE_TT)  // 49:TET /W DAGESH
#define HEP_T2    (( PFHE<<PSFONT) |HE_T2)  // 50:TAV (ALTERNATE FOR TEMANI) 
#define HEP_DD    (( PFHE<<PSFONT) |HE_DD)  // 51:DALET /W DAGESH
#define HEP_C     (( PFHE<<PSFONT) |HE_C)   // 52:KAF
#define HEP_KK    (( PFHE<<PSFONT) |HE_KK)  // 53:QOF /W DAGESH
#define HEP_GG     (( PFHE<<PSFONT) |HE_GG)   // 54:GIMMEL
#define HEP_AL    (( PFHE<<PSFONT) |HE_AL)  // 55:ALEPH (WHEN PRONOUNCED)
#define HEP_NG    (( PFHE<<PSFONT) |HE_NG)  // 56:AYIN
#define HEP_CZ    (( PFHE<<PSFONT) |HE_CZ)  // 57:CHET
#define HEP_KZ    (( PFHE<<PSFONT) |HE_KZ)  // 58:CHET /W DAGESH
#define HEP_TZ    (( PFHE<<PSFONT) |HE_TZ)  // 59:TSADE /W DAGESH



#endif
