/***********************************************************************
 *
 *                           Copyright ©
 *    Copyright © 2000, 2001 Force Computers, Inc., a Solectron company. All rights reserved.
 *    © Digital Equipment Corporation 1996, 1997. All rights reserved.
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
 *    File Name:	ph_prot.h
 *    Author:
 *    Creation Date:
 *
 *    Functionality:
 *
 ***********************************************************************
 *
 *    Revision History:
 *
 * Rev  Who     Date            Description
 * ---  -----   -----------     --------------------------------------------
 * 001	SIK		07/18/1996  	Cleaning up and maintenance 
 * 002	GL		04/21/1997		BATS#357  Add the code for __osf__ build 
 *                              also fix some error declaration.
 * 003	GL		04/21/1997		BATS#360  remove spaces before "#define" or "#if" 
 * 004	GL		03/25/1998		Added DBGV command for PH debug variable passing
 *								For BATS#639 to change phinton() to use argument phTTS instead of pDph_t
 * 005  ETT		10/05/1998		Added Linux code.
 * 006  CAB		10/18/2000		Changed copyright info
 * 007	MGS		05/09/2001		Some VxWorks porting BATS#972
 * 008	CAB		05/14/2001		Updated copyright
 * 009	MGS		06/19/2001		Solaris Port BATS#972
 * 010	MGS		03/20/2002		Single threaded vtm
 * 011	MGS		03/21/2002		Single threaded ph
 * 012	MGS		04/11/2002		ARM7 port
 */

#ifndef PH_PROT_H
#define PH_PROT_H

#include "dectalkf.h"
#include "tts.h"

#ifdef MSDOS
extern int vol_up (int count);
extern int vol_down (int count);
extern int vol_set (int count);
#endif


#ifdef MSDOS
extern void check_index (unsigned int which_phone);
extern void adjust_index (unsigned int which, int direction, int del);
extern void adjust_allo (unsigned int which, int direction);

#else
#ifdef AD_VDSP
/* extern __inline short phone_feature(PDPH_T pDph_t, int phone);	    Phonetic features            */
/* RDK AD Port */
__inline short phone_feature(PDPH_T pDph_t, int phone)
{
	return(all_featb[phone>>8][phone &0xFF]);
}
/* extern __inline short begtyp(int phone); */
__inline short begtyp(int phone)
{
	return(all_begtyp[phone>>8][phone&0xFF]);
}
/* extern __inline short endtyp(int phone); */
__inline short endtyp(int phone)
{
	return(all_endtyp[phone>>8][phone&0xFF]);
}
/* extern __inline short ptram(int phone); */
__inline short ptram(int phone)
{
	return(all_ptram[phone>>8][phone&0xFF]);
}
/* extern __inline short burdr(int phone); */
__inline short burdr(int phone)
{
	return(all_burdr[phone>>8][phone&0xFF]);
}
/* extern __inline short plocu(int index); */
__inline short plocu(int index)
{
	return(all_plocu[index>>8][index&0xFF]);
}
/* extern __inline short place(int); */
__inline short place( int phone)
{
	return(all_place[phone>>8][phone&0xFF]);
}
/* RDK AD Port*/
#ifdef OS_PALM
#pragma pcrelconstdata off
#endif //OS_PALM
extern __inline short ptram(int phone);
#ifdef OS_PALM
#pragma pcrelconstdata on
#endif //OS_PALM
extern __inline short burdr(int phone);
extern __inline short plocu(int index);
extern __inline short place(int);
#endif

extern void *spcget (unsigned short spc_type);
extern int  spcwrite (PKSD_T pKsd_t, unsigned short __far * spc_data);
extern void save_index (PKSD_T pKsd_t, unsigned int sym, unsigned int type, unsigned int value, unsigned int how);
extern void check_index (LPTTS_HANDLE_T phTTS, unsigned int which_phone);
extern void adjust_index (PKSD_T pKsd_t, unsigned int which, int direction, int del);
extern void adjust_allo (PKSD_T pKsd_t, unsigned int which, int direction);
extern void send_index(int how, int value );
#endif

#ifdef DTEX
extern void start_flush (int serial_mode);
#else
extern void start_flush (int serial_mode);
#endif

#ifdef MSDOS
extern int reset_spc (void);
#endif 

/* GL 04/21/1997  change this for OSF build */
#ifdef MSDOS
        extern void default_lang (unsigned int lang_code, unsigned int ready_code);
		extern void flush_done (void);
#else
        extern void default_lang (PKSD_T pKsd_t, unsigned int lang_code, unsigned int ready_code);
		extern void flush_done (PKSD_T pKsd_t);
#endif

#ifndef EPSON_ARM7
extern int  putseq (SEQ __far * sp);
extern int  putn (unsigned int n);
extern int  puthex (unsigned int n);
#if !defined _UNIX_LIKE_
extern int  putstring (unsigned char *str);
#endif
#endif

#ifdef MSDOS
extern unsigned int     getc (void);
extern void             putc (unsigned int c);

#endif
/* MVP Added prototype of dologphoneme here as it is used only in PH sub-system */

#ifdef MSDOS
extern void dologphoneme (short phone, short dur, short f0);
extern void logclaus (short *sym, short nsym, short *ud, short *uf0);

#else
extern void dologphoneme (LPTTS_HANDLE_T phTTS, short phone, short dur, short f0);
extern void logclaus (LPTTS_HANDLE_T phTTS, short *sym, short nsym, short *ud, short *uf0);

#endif 
extern void phalloph (LPTTS_HANDLE_T phTTS);
extern void fr_phalloph (LPTTS_HANDLE_T phTTS);

extern void             prphonol (void);
extern void             phclause (LPTTS_HANDLE_T phTTS);
extern void             init_phclause (PDPH_T pDph_t);

extern void             phdraw (LPTTS_HANDLE_T phTTS);
extern void             pht0draw (LPTTS_HANDLE_T phTTS);

/* GL 03/25/1998,  BATS#639 use phTTS argument instead of pDph_t */
extern void             phinton (LPTTS_HANDLE_T phTTS);
extern void             phinton_classic (LPTTS_HANDLE_T phTTS);
extern void             fr_phinton (LPTTS_HANDLE_T phTTS);

extern int              firstfeature (short FEA1, short FEA2, short nseg);

extern void logscrewup (short phocur, short *inputscrewup);

#ifdef MSDOS
extern int main (unsigned int data_seg, unsigned int stack_start);
#endif

#ifdef MSDOS
void far kltask (void);
#else
void far kltask (LPTTS_HANDLE_T phTTS);
#endif

extern int deadstop (int value, int low, int high);
extern int mstofr (int nms);
extern void phsettar (LPTTS_HANDLE_T phTTS);
extern void debugforward (char *message, PARAMETER * nparameter);
extern void debugbackward (char *message, PARAMETER * nparameter);


extern void  debug1 (void);
extern int   phsort (LPTTS_HANDLE_T phTTS);
extern int   all_phsort (LPTTS_HANDLE_T phTTS);
extern int   fr_phsort (LPTTS_HANDLE_T phTTS);
extern short uk_phcluster (short f, short s);
extern short us_phcluster (short f, short s);
extern short la_phcluster (short f, short s);
extern short sp_phcluster (short f, short s);
extern short gr_phcluster (short f, short s);


extern void  fr_phtiming (LPTTS_HANDLE_T phTTS);
extern void  gr_phtiming (LPTTS_HANDLE_T phTTS);
extern void  la_phtiming (LPTTS_HANDLE_T phTTS);
extern void  sp_phtiming (LPTTS_HANDLE_T phTTS);
//extern void  uk_phtiming (LPTTS_HANDLE_T phTTS);
extern void  us_phtiming (LPTTS_HANDLE_T phTTS);
extern void  it_phtiming (LPTTS_HANDLE_T phTTS);

extern void  prdurs (PDPH_T pDph_t, short phocur, short durinh, short durmin, short deldur, short prcnt, int n);
extern void  prphdurs (PDPH_T pDph_t);
extern void  setparam (LPTTS_HANDLE_T phTTS, int which, int value);
extern void  usevoice (LPTTS_HANDLE_T phTTS, int voice);
extern void  saveval (PDPH_T pDph_t);
extern void  setspdef (LPTTS_HANDLE_T phTTS);
extern short syl_find_vowel (PDPH_T pDph_t,int *ph);
extern short syl_find_cons (PDPH_T pDph_t,int *ph);
extern void  logsyllable (LPTTS_HANDLE_T phTTS);
extern void  saysyllable (LPTTS_HANDLE_T phTTS);
#if defined GERMAN || defined MULTIPLE_LANGUAGES_LOADED
	extern void german_syntax (PDPH_T pDph_t);

#endif

int vtm_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);
void ph_loop(LPTTS_HANDLE_T phTTS,unsigned short *input);

extern void             vv_coartic_across_c (PDPH_T pDph_t, short remoteV, short remotetar,
											 short currentV, short currenttar, short middleC,
											 short dur_cons);


extern short            setloc (LPTTS_HANDLE_T phTTS,
								short nfonobst,         /* Segment thought to be an obstruent     */
								short nfonsonor,        /* Segment thought to be a sonorant       */
								char initfinso,         /* Set to 'i' if use init part of sonor   */
								short nfonvowel,        /* Segment (vowel?) on other side of obst */
								short feanex);

extern void init_timing (LPTTS_HANDLE_T phTTS);

extern void syl_clause_init (PDPH_T);
extern void speak_syllable (LPTTS_HANDLE_T phTTS);
extern int  ph_syllab (PDPH_T pDph_t, int j);
extern short syl_find_affix (PDPH_T pDph_t, int *ph);



extern void filter_commands(PDPH_T pDph_t,short f0in); 
extern void filter_seg_commands(PDPH_T pDph_t,short f0in);
extern void linear_interp(PDPH_T pDph_t); 
extern void set_tglst(PDPH_T pDph_t);


extern void insertphone (LPTTS_HANDLE_T phTTS, short loc, short fone);

extern void find_syll_to_stress (LPTTS_HANDLE_T phTTS, short *locend,
											 short nstartphrase);

extern void delete_symbol (LPTTS_HANDLE_T phTTS, short msym);

extern void move_stdangle (LPTTS_HANDLE_T phTTS, short msym);

#if defined ENGLISH || defined GERMAN || defined FRENCH || defined MULTIPLE_LANGUAGES_LOADED
extern void zap_weaker_bound (LPTTS_HANDLE_T phTTS, short msym1, short msym2);
#endif

extern int  is_wboundary (short symb);

extern void raise_last_stress (LPTTS_HANDLE_T phTTS, short msym);

extern void interp_user_f0 (PDPH_T pDph_t, short *psCurr_dur, short *psCurr_f0,
							short curr_in_sym, short *psMf0);

extern void make_phone (PDPH_T pDph_t, short phoname, short n,
						short curr_dur, short curr_f0);

extern void init_med_final (LPTTS_HANDLE_T phTTS, short msym);

extern void get_stress_of_conson (LPTTS_HANDLE_T phTTS, short msym, short compound_destress);

extern void add_feature (PDPH_T pDph_t, long feaname, short location);

extern void get_next_bound_type (LPTTS_HANDLE_T phTTS, short msym);


extern int get_symbol (PDPH_T pDph_t,short i);

extern short            getbegtar ( LPTTS_HANDLE_T phTTS, int nfone);
extern short            getendtar (LPTTS_HANDLE_T phTTS, int nfone);
extern short            gr_gettar (LPTTS_HANDLE_T phTTS, int nphone_temp);
extern short            us_gettar (LPTTS_HANDLE_T phTTS, int nphone_temp);
extern short            sp_gettar (LPTTS_HANDLE_T phTTS, int nphone_temp);
          
extern short			 fr_gettar (LPTTS_HANDLE_T phTTS, int nphone_temp);
extern int gettar(LPTTS_HANDLE_T phTTS, int phone);


extern short            usspecial_coartic (PDPH_T pDph_t, short nfon, short diphpos);

extern short            spspecial_coartic (PDPH_T pDph_t, short nfon, short diphpos);
extern short            grspecial_coartic (PDPH_T pDph_t, short nfon, short diphpos);
extern short			frspecial_coartic (PDPH_T pDph_t, short nfon, short diphpos);

extern short            setloc (LPTTS_HANDLE_T phTTS,
								short nfonobst,         /* Segment thought to be an obstruent     */
								short nfonsonor,        /* Segment thought to be a sonorant       */
								char initfinso,         /* Set to 'i' if use init part of sonor   */
								short nfonvowel,        /* Segment (vowel?) on other side of obst */
								short feanex);

extern void             us_forw_smooth_rules (LPTTS_HANDLE_T phTTS, short shrif, short pholas,
										   short fealas, short feacur, short struclas,
										   short struccur, short feanex);

extern void             la_forw_smooth_rules (LPTTS_HANDLE_T phTTS, short shrif, short pholas,
										   short fealas, short feacur, short struclas,
										   short struccur, short feanex);

extern void             sp_forw_smooth_rules (LPTTS_HANDLE_T phTTS, short shrif, short pholas,
										   short fealas, short feacur, short struclas,
										   short struccur, short feanex);

extern void             uk_forw_smooth_rules (LPTTS_HANDLE_T phTTS, short shrif, short pholas,
										   short fealas, short feacur, short struclas,
										   short struccur, short feanex);

extern void             gr_forw_smooth_rules (LPTTS_HANDLE_T phTTS, short shrif, short pholas,
										   short fealas, short feacur, short struclas,
										   short struccur, short feanex);

extern void             fr_forw_smooth_rules (LPTTS_HANDLE_T phTTS, short shrif, short pholas,
										   short fealas, short feacur, short struclas,
										   short struccur, short feanex);


extern void             us_back_smooth_rules (LPTTS_HANDLE_T phTTS, short shrib, short feacur,
										   short feanex, short strucnex);

extern void             uk_back_smooth_rules (LPTTS_HANDLE_T phTTS, short shrib, short feacur,
										   short feanex, short strucnex);

extern void             sp_back_smooth_rules (LPTTS_HANDLE_T phTTS, short shrib, short feacur,
										   short feanex, short strucnex);



extern void             gr_back_smooth_rules (LPTTS_HANDLE_T phTTS, short shrib, short feacur,
										   short feanex, short strucnex);

extern void             fr_back_smooth_rules (LPTTS_HANDLE_T phTTS, short shrib, short feacur,
										   short feanex, short strucnex);


extern void             us_special_rules (LPTTS_HANDLE_T phTTS, short fealas,
									   short feacur, short feanex, short struclm2,
									   short struccur, short pholas, short struclas);


extern void             sp_special_rules (LPTTS_HANDLE_T phTTS, short fealas,
									   short feacur, short feanex, short struclm2,
									   short struccur, short pholas, short struclas);


extern void             gr_special_rules (LPTTS_HANDLE_T phTTS, short fealas,
									   short feacur, short feanex, short struclm2,
									   short struccur, short pholas, short struclas);

extern void             fr_special_rules (LPTTS_HANDLE_T phTTS, short fealas,
									   short feacur, short feanex, short struclm2,
									   short struccur, short pholas, short struclas);


extern void             init_variables (LPTTS_HANDLE_T phTTS, short *psInhdr_frames, short *psShrink,
										short *psShrif, short *psShrib,
										short *psPholas, short *psFealas, short *psFeacur,
										short *feanex, short *psStruclm2, short *psStruclas,
										short *psStruccur, short *psStrucnex, short **ppsNdips,
										short *psPhonp2);

extern void             make_dip (PDPH_T pDph_t, short pdip, short inhdr_frames, short shrink,
								  short struccur, short **ppsNdips);

/* GL 04/15/98  For BATS#492 not a function any more
short              get_phone (PDPH_T pDph_t, short pointer);
*/

extern void             vv_coartic_across_c (PDPH_T pDph_t, short remoteV, short remotetar,
											 short currentV, short currenttar, short middleC,
											 short dur_cons);

extern int              shrdur (PDPH_T pDph_t, short durin, short inhdr_frames, short shrink);


extern int span_spec_coart (PDPH_T pDph_t,
							short vowel,   /* Current phoneme              */
							short other);  /* Other (next/last) phoneme    */

extern int la_spec_coart (PDPH_T pDph_t,
							short vowel,   /* Current phoneme              */
							short other);  /* Other (next/last) phoneme    */

extern void make_f0_command (LPTTS_HANDLE_T phTTS,short type, short rulenumber, short tar, short delay,
					  		 short length,short *psCumdur,short nphon);

extern short us_special_coartic (PDPH_T pDph_t, short nfon, short diphpos);
extern short gr_special_coartic (PDPH_T pDph_t, short nfon, short diphpos);
extern short sp_special_coartic (PDPH_T pDph_t, short nfon, short diphpos);

extern int countsyll (PDPH_T pDph_t,int n);
extern int getwordstress (PDPH_T pDph_t,int n);
extern int sp_getsyllclass (PDPH_T pDph_t,short curr);
extern int la_getsyllclass (PDPH_T pDph_t,short curr);
extern void	sp_spanish_allophonics (LPTTS_HANDLE_T phTTS);

extern short Stressed (short CGPrec, short CGCour);
extern void Word_Bd (PDPH_T pDph_t, FLAG PrecStressed, FLAG WordStressed, short CGCour,
              short PosBegPrecWord, short* PosFGROUPrec);
extern void Synt_Bd (PDPH_T pDph_t, short cur_in_sym, FLAG QuestionDeb);
extern short F_Nb_Syll (PDPH_T pDph_t, short nphon);

#endif // PH_PROT_H
