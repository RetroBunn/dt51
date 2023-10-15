/*C_HEADER_FILE****************************************************************
FILE			:	ILE_FUNC.H
DESC			:	Function prototype declaration
TABS			:	4
OWNER			:	
DATE CREATED:	8th January 1991

(C) Copyright 2005 All rights reserved.
This is an unpublished work, and is confidential and proprietary: 
technology and information of fonix corporation.  No part of this
code may be reproduced, used or disclosed without written consent of 
fonix corporation in each and every instance.

  $Date:  $
  $Revision:  $

*END_HEADER*******************************************************************/
#ifndef ILE_FUNC_HEADER
#define ILE_FUNC_HEADER

#include "dustytypes.h"
#include "ile_stzh.h"

// ile_hnkc.c
void		ACCXXXX( );

// acc_000x.c
void		ACC000H( integer_16 );					// put the elements of the p-number section into the monotonous form or model
void		ACC0001( integer_16 );					// put the elements of the p-number (section) into the top (front) hight form or model
void		ACC0002( integer_16 );					// put the elements of the p-number (section) into the bottom (back) high form or model
void		ACC0003( integer_16, integer_16 );		// put the elements of p-numbers (section) into the rise and fall form or model.
void		ACC0004( integer_16 );					// lower the overall elements of q-number (section)
void		ACC0005( integer_16 );					// raise the overall elements of q-number (section)

// acc_1000.c
void		ACC1000( void );
void		ACC2000( void );
void		ACC1K00( void );
void		ACC2K00( void );
void		ACC2200( WORD, WORD, WORD);
void		ACC22XX( integer_16, integer_16, WORD, WORD );
void		ACC22CV( integer_16, integer_16 );
void		ACC22PO( integer_16, integer_16 );
void		ACC2213( integer_16 );
void		ACC2214( integer_16 );
void		ACC2216( integer_16, integer_16 );
void		ACC2217( integer_16, integer_16 );
void		ACC2219( integer_16 );
void		ACC221A( integer_16 );
void		ACC2221( integer_16 );
void		ACC2222( integer_16 );
void		ACC2223( integer_16 );
void		ACC2225( integer_16 );
void		ACC2226( integer_16, integer_16 );
void		ACC2227( integer_16, integer_16 );
void		ACC222A( integer_16, integer_16 );
void		ACC222B( integer_16, integer_16 );
void		ACC222C( integer_16, integer_16 );
void		ACC222D( integer_16 );
void		ACC222E( integer_16, integer_16 );
void		ACC222Z( integer_16 );
void		ACC2232( integer_16, integer_16 );
void		ACC2233( integer_16, integer_16 );
void		ACC2239( integer_16, integer_16 );
void		ACC2300( WORD, WORD );
void		ACC2400( void );
void		ACC2410( integer_16, integer_16 );
void		ACC2411( integer_16, integer_16 );
void		ACC2412( integer_16, integer_16 );
void		ACC2413( integer_16, integer_16 );
void		ACC2420( integer_16, integer_16 );
void		ACC2421( integer_16, integer_16 );
void		ACC2422( integer_16, integer_16 );
void		ACC2423( integer_16, integer_16 );
void		ACC2424( integer_16, integer_16 );
void		ACC2430( integer_16, integer_16, integer_16 );
void		ACC2440( integer_16, integer_16 );
void		ACC2441( integer_16, integer_16 );
void		ACC2442( integer_16, integer_16 );
void		ACC2443( integer_16, integer_16 );
void		ACC2450( integer_16, integer_16 );
void		ACC2460( integer_16, integer_16 );
void		ACC2461( integer_16, integer_16 );
void		ACC2462( integer_16, integer_16 );
void		ACC2463( integer_16, integer_16 );
BOOL		ACC2499( integer_16, integer_16 );
void		ACC2500( WORD, WORD );
void		ACC2600( void );
void        ACC2700( WORD, WORD );
void		ACC2800( void );
void		ACC2900( WORD, WORD );
void		ACC2A00( void );
void		ACC3000( void );
void		ACC4000( void );
void		ACC4100( BYTE * );
void		ACC4200( BYTE * );
// acc_5000.c
void		ACC5000( void );
void		ACC5100( integer_16 );
void		ACC_JOSI_NO(void);
void		ACC_PHRASE(void);
void		ACC6000( void );
void		ACC7000( void );
void		ACC7100( integer_16 ); 
void		ACC8000( void );
void		ACC_OUTPUT( void );
integer_16	ACC_OUTPUT_C( BYTE, integer_16 );
integer_16	ACC_OUTPUT_N( integer_16, integer_16, integer_16 );
integer_16	ACC_OUTPUT_S( BYTE *, integer_16 );

integer_16	CS1000( BOOL );

void		DEBUG_A( BYTE *, BYTE *, integer_16 );
void		DEBUG_ELM( integer_16 );
void		DEBUG_H( BYTE *, BYTE *, integer_16 );
void		DEBUG_H1( BYTE );
void		DEBUG_H2( WORD );
void		DEBUG_I( BYTE *, integer_16 *, integer_16 );
void		DEBUG_IB( BYTE *, BYTE *, integer_16 );
void		DEBUG_INIT( void );
void		DEBUG_K1( BYTE *, integer_16 );
void		DEBUG_PN( BYTE * );
void		DEBUG_STC_ALL( void );
void		DEBUG_STC_CE( integer_16 );
void		DEBUG_STR( BYTE * );
void		DEBUG_STZ( void );

void		DIGIT7000( void );
void		DIGIT7010( BYTE * );
void		DIGIT7020( BYTE * );
void		DIGIT7030( BYTE * );
void		DIGIT_CONV( integer_16 );
void		DIGIT_CONV1( integer_16, integer_16 );
void		DIGIT_CONV2( BYTE *, BYTE * );

BOOL		EDIC1000( void );
BOOL		EDIC2XXX( void );
BOOL		EDIC2000( void );
unsigned short	EDIC2100( void );
BOOL		EDIC3XXX( void );
BOOL		EDIC3000( void );
void		EDIC4000( void );
integer_16	EDIC5000( integer_16 );
void		EDIC_ABORT( void );
void		EDIC_ACC_STUDY( integer_16 );
void		EDIC_PAUSE_STUDY( integer_16 );
void		EDIC_ADD( void );
void		EDIC_DELETE( void );
void		EDIC_MRU( integer_16 );
void		EDIC_MRU_INIT( void );
BOOL		EDIC_MRU_NEED( WORD, LPBYTE, LPBYTE );
void		EdicfAkeru( integer_16, LPBYTE );
void		EdicfIreru( LPBYTE );
void		EdicfSentouSagasu( LPBYTE, LPBYTE *, LPBYTE *);
void		EdicfShift( LPBYTE, LPBYTE, integer_16 );
void		EdicfToridasu( LPBYTE );
void		EdicfTsumeru( integer_16, LPBYTE );
BOOL		RtgfGrcdAri( BYTE, LPBYTE );
void		RtgfFlag1Tsukuru( void );
void		RtgfKchTsukuru( integer_16 );
BOOL		RtgfKnjHykOnaji( LPBYTE );
BOOL		RtgfNydShiraberu( void );
BOOL		RtgfTsuikaKanou( void );
void		ACC0010(void);

integer_16	entrypt( STRUCT_ONSEI far * );
void		ENV_INIT( void );
void		ENV_TERM( void );

void		jp_ERROR( integer_16 );
void		ERROR5000( void );

// ile_stzc.c - Connection relations between elements
BOOL		FOLLOW( void );
void		FOLLOW_INIT(STZ_STRUCT *di);
void		StzfElmBackward( void );
void		StzfElmForward( void );
void		StzfGrcdAdd( BYTE );
void		StzfGrcdOR( void );
void		StzfGrcdStore( BYTE );
void		StzfBnoAdd(STZ_STRUCT *elm, BYTE bno);
void		StzfElmKind(STZ_STRUCT *s, BYTE kind);

BOOL		IDIC1000( void );
BOOL		IDIC2000( void );
BOOL		IDIC3000( void );
void		IDIC4000( void );
integer_16	IDIC5000( integer_16 );
void		IDIC_ABORT( void );
void		IDIC_ACC_STUDY( integer_16 );
void		IDIC_PAUSE_STUDY( integer_16 );
void		IDIC_MRU( integer_16 );

integer_16	INERT1000( void );
integer_16	INERT2000( integer_16, integer_16 );
integer_16	INERT200B( integer_16, integer_16 );
integer_16	INERT300B( integer_16, integer_16 );
void		INERT_COMMA( void );
void		INERT_DIGIT( void );
void		INERT_INIT( void );

void		JKN_INIT( void );

BOOL		KKANA1000( void );
integer_16	KKANA5000( integer_16 );

void		MRU_ALL( void );
void		MRU_CSENT( void );
void		MRU_REMEMBER( void );

BOOL		NUMB1000( void );
BOOL		NUMB5000( integer_16 );
void		NUMB5XXX( integer_16 );
integer_16	NUM0010( void );
integer_16	NUM0020( void );

integer_16	OMEGA1000( BYTE, integer_16 );
void		OMEGA5000( void );
void		OMEGA6000( void );
void		OMEGA9000( void );
BOOL		OMEGA_CHECK( void );
void		OMEGA_INIT(void  );
void		OMEGA_SAVE(void  );

WORD		OTHER2000( void );
integer_16	OTHER5000( integer_16 );
void		OTHER_GRCD( void );

void		PAUSE1000(void  );

void		PRON_ACON( void );
void		PRON_ACOFF(void  );
void		PRON_FIRST(void  );
void		PRON_INIT(void  );
void		PRON_INIT2(void  );
void		PRON_LEFT( void );
void		PRON_LONG( void );
void		PRON_NEXT( void );
void		PRON_RECOVER( void );
void		PRON_RIGHT(void  );
void		PRON_SENT_NO(void  );
void		PRON_SHORT(void  );
void		PRON_TERM( void );

void		RnsfRecordMru(void  );

void		SENT_INIT( void );

BOOL		BNO_VECP(void  );
BOOL		bno_pno( integer_16, integer_16 );
BOOL		bno_prop( integer_16 );

void		STACK_INIT( void );
void		STACK_POP(void  );
void		STACK_POP_FS( void );
void		STACK_POP_WS( void );
void		STACK_PUSH( void );

integer_16	TDIC1000(void  );
BOOL		TDIC2000(void  );
void		TDIC2100(void  );
BOOL		TDIC3000(void  );
void		TDIC4000(void  );
void		TDIC4100( void );
integer_16	TDIC5000( integer_16 );
integer_16	TDIC5009( integer_16 );

void		WS_BECOMES_TOP( void );
BOOL		WS_CE_CHK(void  );
integer_16	WS_CHK_LONG( void );
integer_16	WS_CHK_SHORT(void );
void		WS_MOVE_LEFT( void );
void		WS_MOVE_RIGHT(void  );

integer_16	V5DAN5000( integer_16 );
void		V5DANYOU_PUSH(void  );

integer_16	before_ch_ptr( integer_16 ); 
void		check_X( BYTE *, integer_16 );
BOOL		chk_heiban( integer_16 );
integer_16	chk_limits( BYTE, BYTE, BYTE *, integer_16 );
BOOL		chk_odaka( integer_16 );
WORD		chk_separator( integer_16 ); 
integer_16	chk_value( BYTE, BYTE *, integer_16 );
void		code_to_hardchar( BYTE, BYTE, BYTE * );
integer_16	count_high( integer_16 );
integer_16	count_low( integer_16 );
integer_16	first_char_ptr( integer_16 ); 
BOOL		first_or_not( integer_16 ); 
WORD		get_case( integer_16 );
BOOL		is_zengo_kanji( integer_16 );
void		jis2sft( BYTE * );
BOOL		kana_conv( BYTE, BYTE, BYTE * );
BOOL		kana_mora(void  );
integer_16	knj_number( integer_16 ); 
BOOL		last_or_not( integer_16 ); 
integer_16	net_phrase_in_len( integer_16 ); 
integer_16	next_ch_ptr( integer_16 ); 
integer_16	next_phrase( integer_16 ); 
BOOL		user_checksum(void  );

// ile_jknc.c
void	clear_null();						// stub function
int		check_edic_null();					// stubish function
int		check_idic_null();					// stubish function
void	push_null(WORD ptr, WORD ofs, WORD page);	// stubish function

// mkhatu.c
int		mkhatu(BYTE *kana, BYTE *hatu);		// generates a phonetic symbol from the kana string

// ile_rtkc.c
void	RtkfRead(integer_16 pno, size_t size, void* addr);	// Call the user defined reading routine.
void	RtkfWrite(integer_16 pno, size_t size, void* addr);	// Call the user defined function to write
void	RtkfDealloc(void** addr);							// Call the user defined function to de-allocate memory
int		RtkfAlloc(void** addr, size_t size);				// Call the user defined function to allocate memory
void	RtkfChudanShiraberu();								// Call the user defined interrupt request routine.

// ile_tdic.c
BOOL	TDIC2XXX();

// ile_errc.c
void	jp_ERROR(integer_16 ax);			// Specify the error state of the error code ax, and go to the default label.


#endif
/***************************** END OF ILE_FUNC.H *****************************/
