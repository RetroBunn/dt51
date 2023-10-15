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

      


#define SPP_A		 ((PFSP<<PSFONT) |SP_A	)               /*       Palabra        */
#define SPP_E		 ((PFSP<<PSFONT) |SP_E	)               /*       Leo            */
#define SPP_I		 ((PFSP<<PSFONT) |SP_I	)               /*       Hilo           */
#define SPP_O		 ((PFSP<<PSFONT) |SP_O	)               /*       Hola           */
#define SPP_U 		 ((PFSP<<PSFONT) |SP_U )               /*       Lunes          */
#define SPP_WX		 ((PFSP<<PSFONT) |SP_WX)               /* Rounded dipth semiv. */
#define SPP_YX		 ((PFSP<<PSFONT) |SP_YX)               /* Unround dipth semiv. */
#define SPP_RR		 ((PFSP<<PSFONT) |SP_RR)               /*       Rama           */
#define SPP_L		 ((PFSP<<PSFONT) |SP_L	)
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


 
#endif /* #ifndef L_ALL_PHH */
