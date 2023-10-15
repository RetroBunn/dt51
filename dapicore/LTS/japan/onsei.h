/**
 * @file onsei.h ?
 */

#ifndef ONSEI_H
#define ONSEI_H

#include "dustytypes.h"

#include "onsei_s.h"

/*
 * システム定数
 */
#define	DISABLE		  0
#define	 ENABLE		  1

#define	MAX_INERT	128		/* 入力可能最大文字数 */
#define	MAX_STACK	128		/* 最大スタックエントリー数(=MAX_INERT) */
#define	MAX_OMEGA	512		/* 出力可能最大文字数 */
#define	MAX_SENT	 80		/* 出力文節数の上限 */
#define	MAX_IDIC	  5		/* 内部辞書引き最大文字数定義 */
#define MAX_INDEX	 23		/* 外部辞書見出し表のレコード長 */
#define	MAX_EDIC	 10		/* 外部辞書の見出し長の上限 */
#define	MAX_GRCD	  9		/* 外部辞書の単語の文法コード数の上限 */

#if defined(V_MEIDEN)
#define	MAX_SPEAK	3000	/* 出力可能最大表音文字数 */
#else
#define	MAX_SPEAK	768		/* 出力可能最大表音文字数 */
#endif

/* these are arguments passed in to onsei_henkan to tell it how to process input */
#define PROC_ENV_INIT		1	/* 文章音声変換処理初期設定 */
#define PROC_ENV_TERM		2	/* 文章音声変換処理終了 */
#define PROC_FIRST			3	/* First conversion */
#define PROC_NEXT			4	/* Attention word or phrase next candidate */
#define PROC_SHORT			5	/* Splits into the direction of the short word or phrase */
#define PROC_LONG			6	/* Splits into the direction of the long word or phrase */
#define PROC_RIGHT			7	/* Attention word or phrase move to the right */
#define PROC_LEFT			8	/* Attention word or phrase move to the left */
#define PROC_TERM			9	/* Decides on learned information */
#define PROC_SENT_NO		10	/* Takes out the attention word or phrase number */
#define PROC_EDIC_DELETE2	11	/* 外部辞書ユーザー語削除（単独）*/
#define PROC_EDIC_ADD		12	/* 外部辞書ユーザー語追加 */
#define PROC_EDIC_DELETE	13	/* 外部辞書ユーザー語削除（変換後）*/
#define PROC_ACON			14	/* Combines the accent of attention word or phrase and the next word or phrase */
#define PROC_ACOFF			15	/* Does not combine the accent of attention word or phrase to the next word or phrase */
#define PROC_PAUSE_INS		16	/* Inserts a pause directly after the attention word or phrase */
#define PROC_PAUSE_DEL		17	/* Deletes the pause directly after the attention word or phrase */
#define PROC_USER_ID		18	/* 辞書のユーザーＩＤの取り出し */


/* error return codes -- 0 indicates normal completion */
#define	Err_Abnormal			0x80	/* バグ */
#define	Err_HenkanFunou			0x81	/* 変換不能(辞書にない) */
#define	Err_NaibuOVF			0x82	/* The word or phrase number is over limit or the phonogram string is too long */
#define	Err_Chuudan				0x83	/* Stopped at u_stop() */
#define	Err_InertNone			0x84	/* 入力文字列長ゼロ */
#define	Err_InertOVF			0x85	/* 入力文字列長over */
#define	Err_Hankaku				0x86	/* 半角文字が混じっている */
#define	Err_EdicTooLong			0x87	/* The written item or the reading is too long */
#define	Err_TourokuSumi			0x88	/* The same one is already registered */
#define	Err_MiTouroku			0x89	/* It is not the user's registration word */
#define	Err_EdicOVF				0x8A	/* Cannot be registered -> if the dictionary readjusts, then it will be OK */
#define Err_Fatal_DIC			0x9F	/* No dictionary */
#define Err_Fatal_Edic			0xA0	/* Dictionary malfunction */
#define Err_Fatal_Idic			0xA1	/* Dictionary malfunction */
#define Err_Fatal_ACF			0xA2	/* 表音fileがopenできない。*/
#define Err_Fatal_Alloc			0xA3	/* insufficient memory */

#define Err_Security_Casette	0xFE	/* セキュリティカセットのエラー */
#define FAT_Patch				0xFF	/* user名にパッチが当てられている */

/* ＜回復可能なerror（さらに変換を続けられる）＞ */
#define	Err_IdouFunou			0x01	/* Word or phrase movement is not possible */
#define	Err_NextNone			0x02	/* There is no next candidate */
#define	Err_HenkanTochuu		0x03	/* Conversion of a word that is not in the dictionary */
#define Err_RestrictCNT			0x04	/* Timed out */

/* These are required to build the libs */

#endif /* ONSEI_H */

/***************************** END OF ONSEI.H ********************************/
