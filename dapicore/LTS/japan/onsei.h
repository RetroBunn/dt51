/**
 * @file onsei.h ?
 */

#ifndef ONSEI_H
#define ONSEI_H

#include "dustytypes.h"

#include "onsei_s.h"

/*
 * �����ƥ����
 */
#define	DISABLE		  0
#define	 ENABLE		  1

#define	MAX_INERT	128		/* ���ϲ�ǽ����ʸ���� */
#define	MAX_STACK	128		/* ���祹���å�����ȥ꡼��(=MAX_INERT) */
#define	MAX_OMEGA	512		/* ���ϲ�ǽ����ʸ���� */
#define	MAX_SENT	 80		/* ����ʸ����ξ�� */
#define	MAX_IDIC	  5		/* ���������������ʸ������� */
#define MAX_INDEX	 23		/* �������񸫽Ф�ɽ�Υ쥳����Ĺ */
#define	MAX_EDIC	 10		/* ��������θ��Ф�Ĺ�ξ�� */
#define	MAX_GRCD	  9		/* ���������ñ���ʸˡ�����ɿ��ξ�� */

#if defined(V_MEIDEN)
#define	MAX_SPEAK	3000	/* ���ϲ�ǽ����ɽ��ʸ���� */
#else
#define	MAX_SPEAK	768		/* ���ϲ�ǽ����ɽ��ʸ���� */
#endif

/* these are arguments passed in to onsei_henkan to tell it how to process input */
#define PROC_ENV_INIT		1	/* ʸ�ϲ����Ѵ������������ */
#define PROC_ENV_TERM		2	/* ʸ�ϲ����Ѵ�������λ */
#define PROC_FIRST			3	/* First conversion */
#define PROC_NEXT			4	/* Attention word or phrase next candidate */
#define PROC_SHORT			5	/* Splits into the direction of the short word or phrase */
#define PROC_LONG			6	/* Splits into the direction of the long word or phrase */
#define PROC_RIGHT			7	/* Attention word or phrase move to the right */
#define PROC_LEFT			8	/* Attention word or phrase move to the left */
#define PROC_TERM			9	/* Decides on learned information */
#define PROC_SENT_NO		10	/* Takes out the attention word or phrase number */
#define PROC_EDIC_DELETE2	11	/* ��������桼����������ñ�ȡ�*/
#define PROC_EDIC_ADD		12	/* ��������桼�������ɲ� */
#define PROC_EDIC_DELETE	13	/* ��������桼�����������Ѵ����*/
#define PROC_ACON			14	/* Combines the accent of attention word or phrase and the next word or phrase */
#define PROC_ACOFF			15	/* Does not combine the accent of attention word or phrase to the next word or phrase */
#define PROC_PAUSE_INS		16	/* Inserts a pause directly after the attention word or phrase */
#define PROC_PAUSE_DEL		17	/* Deletes the pause directly after the attention word or phrase */
#define PROC_USER_ID		18	/* ����Υ桼�����ɣĤμ��Ф� */


/* error return codes -- 0 indicates normal completion */
#define	Err_Abnormal			0x80	/* �Х� */
#define	Err_HenkanFunou			0x81	/* �Ѵ���ǽ(����ˤʤ�) */
#define	Err_NaibuOVF			0x82	/* The word or phrase number is over limit or the phonogram string is too long */
#define	Err_Chuudan				0x83	/* Stopped at u_stop() */
#define	Err_InertNone			0x84	/* ����ʸ����Ĺ���� */
#define	Err_InertOVF			0x85	/* ����ʸ����Ĺover */
#define	Err_Hankaku				0x86	/* Ⱦ��ʸ���������äƤ��� */
#define	Err_EdicTooLong			0x87	/* The written item or the reading is too long */
#define	Err_TourokuSumi			0x88	/* The same one is already registered */
#define	Err_MiTouroku			0x89	/* It is not the user's registration word */
#define	Err_EdicOVF				0x8A	/* Cannot be registered -> if the dictionary readjusts, then it will be OK */
#define Err_Fatal_DIC			0x9F	/* No dictionary */
#define Err_Fatal_Edic			0xA0	/* Dictionary malfunction */
#define Err_Fatal_Idic			0xA1	/* Dictionary malfunction */
#define Err_Fatal_ACF			0xA2	/* ɽ��file��open�Ǥ��ʤ���*/
#define Err_Fatal_Alloc			0xA3	/* insufficient memory */

#define Err_Security_Casette	0xFE	/* �������ƥ������åȤΥ��顼 */
#define FAT_Patch				0xFF	/* user̾�˥ѥå������Ƥ��Ƥ��� */

/* �������ǽ��error�ʤ�����Ѵ���³������ˡ� */
#define	Err_IdouFunou			0x01	/* Word or phrase movement is not possible */
#define	Err_NextNone			0x02	/* There is no next candidate */
#define	Err_HenkanTochuu		0x03	/* Conversion of a word that is not in the dictionary */
#define Err_RestrictCNT			0x04	/* Timed out */

/* These are required to build the libs */

#endif /* ONSEI_H */

/***************************** END OF ONSEI.H ********************************/
