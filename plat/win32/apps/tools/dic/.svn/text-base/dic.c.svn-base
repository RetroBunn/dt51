/*
 ***********************************************************************
 *
 *                           Copyright (c)
 *    Copyright © 2002 Fonix Corportion. All rights reserved.
 *    Copyright © 2000 Force Computer, Inc., a Solectron company. All rights reserved.
 *    © Digital Equipment Corporation 1996. All rights reserved.
 *
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
 *    File Name:     dic_us_c.c
 *    Author:        JDB
 *    Creation Date: 5/23/96  
 *
 *    Functionality:
 *    Code specific to dictionary compilation for US English
 *
 ***********************************************************************
 *    Revision History:
 *
 *		Date		Who				Description
 *		----		---				-----------
 *	001	01/28/1997	ncs				Made one C file for multilanguages
 *	002	10/23/1997	gl				add ENGLISH_UK support
 *  003 10/28/1997  gl              add ir,er,ar,or,ur.df for US
 *  004 12/04/1997  gl              add LINKRWORD for UK English
 *  005 06/29/1998  gl              BATS#702 add DOUBLCONS for German
 *  006	06/18/1998	mfg				SPANISH_SP & SPANISH_LA support added
 *  007	04/13/2000	MGS 			Changes for integrated phoneme set 
 *	008	04/14/2000	NAL				Changed DOUBLCONS '&' to '>'
 *	009	07/20/2000	CHJ				Added French
 *  007 10/18/2000	CAB				Changed copyright info and formatted comments
 *	008	09/11/2002	CAB				Added missing UK_YR
 *		
 */

#include "l_all_ph.h"
#include "Dic.h"

/*
 * general defines ...
 */
                                                            
                         
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// These definitions must match those in phonlist.h
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/* Phoneme name table (again)   */                          
PTAB ptab_us[]  = {
	{ 'e',  US_EY      },
	{ 'a',  US_AA      },
	{ 'i',  US_IY      },
	{ 'E',  US_EH      },
	{ 'A',  US_AY      },
	{ 'I',  US_IH      },
	{ 'O',  US_OY      },
	{ 'o',  US_OW      },
	{ 'u',  US_UW      },
	{ '^',  US_AH      },
	{ 'W',  US_AW      },
	{ 'Y',  US_YU      },
	{ 'R',  US_RR      },
	{ 'c',  US_AO      },
	{ '@',  US_AE      },
	{ 'U',  US_UH      },
	{ '|',  US_IX      },
	{ 'x',  US_AX      },
	{ 'p',  US_P       },
	{ 't',  US_T       },
	{ 'k',  US_K       },
	{ 'f',  US_F       },
	{ 'T',  US_TH      },
	{ 's',  US_S       },
	{ 'S',  US_SH      },
	{ 'C',  US_CH      },
	{ 'w',  US_W       },
	{ 'y',  US_Y       },
	{ 'h',  US_HX      },
	{ 'l',  US_LL      },
	{ 'L',  US_EL      },
	{ 'N',  US_EN      },
	{ 'b',  US_B       },
	{ 'd',  US_D       },
	{ 'g',  US_G       },
	{ 'v',  US_V       },
	{ 'D',  US_DH      },
	{ 'z',  US_Z       },
	{ 'Z',  US_ZH      },
	{ 'J',  US_JH      },
	{ 'm',  US_M       },
	{ 'n',  US_N       },
	{ 'G',  US_NX      },
	{ 'r',  US_R       },
	{ 'q',  US_Q       },
	{ 'Q',  US_TX      },
	{ '&',  US_DX      },
    { 'F',  US_DF      },
    { 'B',  US_IR      },
    { 'K',  US_ER      },
    { 'P',  US_AR      },
    { 'M',  US_OR      },
    { 'j',  US_UR      },
	{ ',',  COMMA   },
	{ ' ',  WBOUND  },
	{ '\t', WBOUND  },
	{ '\'', S1      },
	{ '`',  S2      },
	{ '"',	SEMPH	},
	{ '#',  HYPHEN  },
	{ '(',  PPSTART },
	{ ')',  VPSTART },
	{ '*',  MBOUND  },
	{ '~',  BLOCK_RULES },
	{ '-',  SBOUND  }
};
unsigned long ntab_us = sizeof(ptab_us) / sizeof(ptab_us[0]);

PTAB ptab_uk[]  = {
	{ '_', SIL		},
	{ 'i',	UK_IY		},
	{ 'I',	UK_IH		},
	{ 'e',	UK_EY		},
	{ 'E',	UK_EH		},
	{ '@',	UK_AE		},
	{ 'a',	UK_AA		},
	{ 'A',	UK_AY		},
	{ 'W',	UK_AW		},
	{ '^',	UK_AH		},
	{ 'c',	UK_AO		},
	{ 'o',	UK_OW		},
	{ 'O',	UK_OY		},
	{ 'u',	UK_UW		},
	{ 'R',	UK_RR		},
	{ 'Y',	UK_YU		},
	{ 'U',	UK_UH		},
	{ 'x',	UK_AX		},
	{ '|',	UK_IX		},
	{ 'w',	UK_W		},
	{ 'y',	UK_Y		},
	{ 'r',	UK_R		},
	{ 'l',	UK_LL		},
	{ 'h',	UK_HX		},
	{ 'm',	UK_M		},
	{ 'n',	UK_N		},
	{ 'G',	UK_NX		},
	{ 'L',	UK_EL		},
	{ 'N',	UK_EN		},
	{ 'f',	UK_F		},
	{ 'v',	UK_V		},
	{ 'T',	UK_TH		},
	{ 'D',	UK_DH		},
	{ 's',	UK_S		},
	{ 'z',	UK_Z		},
	{ 'S',	UK_SH		},
	{ 'Z',	UK_ZH		},
	{ 'p',	UK_P		},
	{ 'b',	UK_B		},
	{ 't',	UK_T		},
	{ 'd',	UK_D		},
	{ 'k',	UK_K		},
	{ 'g',	UK_G		},
	{ 'Q',	UK_TX		},
	{ 'q',	UK_Q		},
	{ 'J',	UK_JH		},
	{ 'C',	UK_CH		},
	{ 'F',	UK_IR		},
	{ 'K',	UK_ER		},
	{ 'P',	UK_AR		},
	{ 'M',	UK_OR		},
	{ 'j',	UK_UR		},
	{ 'B',	UK_OH		},
	{ 'V',	UK_YR		},
	{ '&',	LINKRWORD	},
	{ ',',  COMMA   },
	{ ' ',  WBOUND  },
	{ '\t', WBOUND  },
	{ '\'', S1      },
	{ '`',  S2      },
	{ '"',	SEMPH	},
	{ '#',  HYPHEN  },
	{ '(',  PPSTART },
	{ ')',  VPSTART },
	{ '*',  MBOUND  },
	{ '~',  BLOCK_RULES },
	{ '-',  SBOUND  }
};
unsigned long ntab_uk = sizeof(ptab_uk) / sizeof(ptab_uk[0]);

PTAB ptab_sp[]  = {
	{ 'e',	SP_E	},
	{ 'a',	SP_A	},
	{ 'i',	SP_I	},
	{ '2',	SP_YH	},
	{ 'o',	SP_O	},
	{ 'u',	SP_U	},
	{ '1',	SP_NH	},
	{ 'W',	SP_WX	},
	{ 'Y',	SP_YX	},
	{ 'R',	SP_RR	},
	{ 'C',	SP_CH	},
	{ 'l',	SP_L	},
	{ 'p',	SP_P	},
	{ 't',	SP_T	},
	{ 'k',	SP_K	},
	{ 'f',	SP_F	},
	{ 'T',	SP_TH	},
	{ 's',	SP_S	},
	{ 'y',	SP_Y	},
	{ 'L',	SP_LL	},
	{ 'b',	SP_B	},
	{ 'd',	SP_D	},
	{ 'g',	SP_G	},
	{ 'D',	SP_DH	},
	{ 'z',	SP_Z	},
	{ 'm',	SP_M	},
	{ 'n',	SP_N	},
	{ 'G',	SP_GH	},
	{ 'r',	SP_R	},
	{ 'q',	SP_Q	},
	{ 'v', SP_V		},
	{ 'I', SP_IX	},
	{ 'M', SP_MX	},
	{ 'P', SP_PH	},
	{ 'N', SP_NX	},
	{ 'w', SP_W		},
	{ 'B',SP_BH		},
	{ 'j',SP_J 		},
	{ ',',  COMMA   },
	{ ' ',  WBOUND  },
	{ '\t', WBOUND  },
	{ '\'', S1      },
	{ '`',  S2      },
	{ '"',	SEMPH	},
	{ '#',  HYPHEN  },
	{ '(',  PPSTART },
	{ ')',  VPSTART },
	{ '*',  MBOUND  },
	{ '~',  BLOCK_RULES },
	{ '-',  SBOUND  }
};
unsigned long ntab_sp = sizeof(ptab_sp) / sizeof(ptab_sp[0]);


PTAB ptab_la[]  = {
	{ 'e',	LA_E	},
	{ 'a',	LA_A	},
	{ 'i',	LA_I	},
	{ '2',	LA_YH	},
	{ 'o',	LA_O	},
	{ 'u',	LA_U	},
	{ '1',	LA_NH	},
	{ 'W',	LA_WX	},
	{ 'Y',	LA_YX	},
	{ 'R',	LA_RR	},
	{ 'C',	LA_CH	},
	{ 'l',	LA_L	},
	{ 'p',	LA_P	},
	{ 't',	LA_T	},
	{ 'k',	LA_K	},
	{ 'f',	LA_F	},
	{ 'T',	LA_TH	},
	{ 's',	LA_S	},
	{ 'y',	LA_Y	},
	{ 'L',	LA_LL	},
	{ 'b',	LA_B	},
	{ 'd',	LA_D	},
	{ 'g',	LA_G	},
	{ 'D',	LA_DH	},
	{ 'z',	LA_Z	},
	{ 'm',	LA_M	},
	{ 'n',	LA_N	},
	{ 'G',	LA_GH	},
	{ 'r',	LA_R	},
	{ 'q',	LA_Q	},
	{ 'v', LA_V		},
	{ 'I', LA_IX	},
	{ 'M', LA_MX	},
	{ 'P', LA_PH	},
	{ 'N', LA_NX	},
	{ 'w', LA_W		},
	{ 'B',LA_BH		},
	{ 'j',LA_J 		},
	{ ',',  COMMA   },
	{ ' ',  WBOUND  },
	{ '\t', WBOUND  },
	{ '\'', S1      },
	{ '`',  S2      },
	{ '"',	SEMPH	},
	{ '#',  HYPHEN  },
	{ '(',  PPSTART },
	{ ')',  VPSTART },
	{ '*',  MBOUND  },
	{ '~',  BLOCK_RULES },
	{ '-',  SBOUND  }
};
unsigned long ntab_la = sizeof(ptab_la) / sizeof(ptab_la[0]);

PTAB ptab_gr[]  = {
	{ 'a',GR_A		},
	{ 'E',GR_E		},
	{ 'V',GR_AE		},
	{ '@',GR_EX		},
	{ 'I',GR_I		},
	{ 'c',GR_O		},
	{ 'Q',GR_OE		},
	{ 'U',GR_U		},
	{ 'Y',GR_UE		},
	{ '1',GR_AH		}, 
	{ '2',GR_EH		},
	{ '7',GR_AEH	}, 
	{ '3',GR_IH		},
	{ '4',GR_OH		},
	{ 'q',GR_OEH	},
	{ '5',GR_UH		},
	{ '6',GR_UEH	},
	{ 'A',GR_EI		},
	{ 'W',GR_AU		},
	{ 'H',GR_EU		},
	{ '8',GR_AN		},
	{ '^',GR_IM		},
	{ '9',GR_UM		},
	{ '%',GR_ON		},
	{ 'j',GR_J		},
	{ 'l',GR_L		},
	{ 'r',GR_RR		},
	{ 'R',GR_R		},
	{ 'h',GR_H		},
	{ 'm',GR_M		},
	{ 'n',GR_N		},
	{ 'G',GR_NG		},
	{ 'L',GR_EL		},
	{ 'M',GR_EM		},
	{ 'N',GR_EN		},
	{ 'f',GR_F		},
	{ 'v',GR_V		},
	{ 's',GR_S		},
	{ 'z',GR_Z		},
	{ 'S',GR_SH		},
	{ 'Z',GR_ZH		},
	{ 'x',GR_CH		},
	{ 'X',GR_KH		},
	{ 'p',GR_P		},
	{ 'b',GR_B		},
	{ 'd',GR_D		},
	{ 't',GR_T		},
	{ 'k',GR_K		},
	{ 'g',GR_G		},
	{ '?',GR_Q		},
	{ 'P',GR_PF		},
	{ 'T',GR_TS		},
	{ 'J',GR_DJ		},
	{ 'C',GR_TJ		},
	{ '?',GR_KSX	},
	{ 'i',GR_I1		},
	{ 'e',GR_E1		},
	{ 'o',GR_O1		},
	{ 'u',GR_U1		},
	{ 'y',GR_Y1		},
	{ 'B',GR_ER		},
	{ '>',DOUBLCONS	},
	{ ',',  COMMA   },
	{ ' ',  WBOUND  },
	{ '\t', WBOUND  },
	{ '\'', S1      },
	{ '`',  S2      },
	{ '"',	SEMPH	},
	{ '#',  HYPHEN  },
	{ '(',  PPSTART },
	{ ')',  VPSTART },
	{ '*',  MBOUND  },
	{ '~',  BLOCK_RULES },
	{ '-',  SBOUND  }
};
unsigned long ntab_gr = sizeof(ptab_gr) / sizeof(ptab_gr[0]);

PTAB ptab_fr[]  = {
	{ 'a',	F_A },
	{ 0xe0, F_A3 },
	{ 0xee, F_E2 },
	{ 0xe5, F_AU },
	{ 0xe9, F_E },
	{ 'e', F_E1 },
	{ 0xed, F_EU },
	{ 'i', F_I },
	{ 'o', F_O },
	{ 0xec, F_O6 },
	{ 'u', F_OU },
	{ 'y', F_U },
	{ 0xe2, F_AN },
	{ 0xe8, F_IN },
	{ 0xeb, F_ON },
	{ 0xea, F_UN },
	{ 'h', F_AP },
	{ 'l', F_L },
	{ 0xe7, F_R },
	{ 'w', F_W },
	{ 0xe6, F_WU },
	{ 'j', F_Y },
	{ 0xf4, F_CH },
	{ 'f', F_F },
	{ 0xe4, F_J },
	{ 'x', F_RX },
	{ 's', F_S },
	{ 'v', F_V },
	{ 'z', F_Z },
	{ 'b', F_B },
	{ 'd', F_D },
	{ 'g', F_G },
	{ 'k', F_K },
	{ 'p', F_P },
	{ 't', F_T },
	{ 0xef, F_GN },
	{ 'm', F_M },
	{ 'n', F_N },
	{ 0xe3, F_NG },
	{ ',',  COMMA   },
	{ ' ',  WBOUND  },
	{ '\t', WBOUND  },
	{ '\'', S1      },
	{ '`',  S2      },
	{ '"',	SEMPH	},
	{ '#',  HYPHEN  },
	{ '(',  PPSTART },
	{ ')',  VPSTART },
	{ '*',  MBOUND  },
	{ '~',  BLOCK_RULES },
	{ '-',  SBOUND  }
};
unsigned long ntab_fr = sizeof(ptab_fr) / sizeof(ptab_fr[0]);

PTAB ptab_it[]  = {
	{ 'a',	IT_AP	},
	{ 'e',	IT_EP	},
	{ 'i',	IT_IY	},
	{ 'o',	IT_OP	},
	{ 'u',	IT_UW	},
	{ 'x',	IT_AX	},
	{ 'j',	IT_Y	},
	{ 'R',	IT_RR	},
	{ 'l',	IT_L	},
	{ 'L',	IT_LL	},
	{ 'm',	IT_M	},
	{ 'n',	IT_N	},
	{ 'h',	IT_NH	},
	{ 'f',	IT_F	},
	{ 's',	IT_S	},
	{ 'E',	IT_EH	},
	{ 'T',	IT_TD	},
	{ 'B',	IT_BD	},
	{ 'D',	IT_DD	},
	{ 'G',	IT_GD	},
	{ '8',	IT_JH	},
	{ 'p',	IT_P	},
	{ 'b',	IT_B	},
	{ 't',	IT_T	},
	{ 'd',	IT_D	},
	{ 'k',	IT_K	},
	{ 'g',	IT_G	},
	{ '7',	IT_CH	},
	{ 'c',	IT_AO	},
	{ 'r',	IT_R	},
	{ 'K',	IT_KD	},
	{ 'z',	IT_Z	},
	{ 'w',	IT_W	},
	{ 'Q',	IT_NX	},
	{ 'v',	IT_V	},
	{ 'N',	IT_ND	},
	{ 'M',	IT_MF	},
	{ 'P',	IT_PD	},
	{ 'H',	IT_NJ	},
	{ 'S',	IT_SH	},
	{ '9',	IT_TS	},
	{ '0',	IT_DZ	},
	{ ',',  COMMA   },
	{ ' ',  WBOUND  },
	{ '\t', WBOUND  },
	{ '\'', S1      },
	{ '`',  S2      },
	{ '"',	SEMPH	},
	{ '#',  HYPHEN  },
	{ '(',  PPSTART },
	{ ')',  VPSTART },
	{ '*',  MBOUND  },
	{ '~',  BLOCK_RULES },
	{ '-',  SBOUND  }
};
unsigned long ntab_it = sizeof(ptab_it) / sizeof(ptab_it[0]);

#if 0
PTAB ptab_jp[]  = {
	{ 'a',	JP_AP	},
	{ 'e',	JP_EP	},
	{ 'i',	JP_IY	},
	{ 'o',	JP_OP	},
	{ 'u',	JP_UW	},
	{ 'x',	JP_AX	},
	{ 'j',	JP_Y	},
	{ 'R',	JP_RR	},
	{ 'l',	JP_L	},
	{ 'L',	JP_LL	},
	{ 'm',	JP_M	},
	{ 'n',	JP_N	},
	{ 'h',	JP_NH	},
	{ 'f',	JP_F	},
	{ 's',	JP_S	},
	{ 'E',	JP_EH	},
	{ 'T',	JP_TD	},
	{ 'B',	JP_BD	},
	{ 'D',	JP_DD	},
	{ 'G',	JP_GD	},
	{ '8',	JP_JH	},
	{ 'p',	JP_P	},
	{ 'b',	JP_B	},
	{ 't',	JP_T	},
	{ 'd',	JP_D	},
	{ 'k',	JP_K	},
	{ 'g',	JP_G	},
	{ '7',	JP_CH	},
	{ 'c',	JP_AO	},
	{ 'r',	JP_R	},
	{ 'K',	JP_KD	},
	{ 'z',	JP_Z	},
	{ 'w',	JP_W	},
	{ 'Q',	JP_NX	},
	{ 'v',	JP_V	},
	{ 'N',	JP_ND	},
	{ 'M',	JP_MF	},
	{ 'P',	JP_PD	},
	{ 'H',	JP_NJ	},
	{ 'S',	JP_SH	},
	{ '9',	JP_TS	},
	{ '0',	JP_DZ	},
	{ ',',  COMMA   },
	{ ' ',  WBOUND  },
	{ '\t', WBOUND  },
	{ '\'', S1      },
	{ '`',  S2      },
	{ '"',	SEMPH	},
	{ '#',  HYPHEN  },
	{ '(',  PPSTART },
	{ ')',  VPSTART },
	{ '*',  MBOUND  },
	{ '~',  BLOCK_RULES },
	{ '-',  SBOUND  }
};

PTAB ptab_hb[]  = {
	{ 'a',	HB_AP	},
	{ 'e',	HB_EP	},
	{ 'i',	HB_IY	},
	{ 'o',	HB_OP	},
	{ 'u',	HB_UW	},
	{ 'x',	HB_AX	},
	{ 'j',	HB_Y	},
	{ 'R',	HB_RR	},
	{ 'l',	HB_L	},
	{ 'L',	HB_LL	},
	{ 'm',	HB_M	},
	{ 'n',	HB_N	},
	{ 'h',	HB_NH	},
	{ 'f',	HB_F	},
	{ 's',	HB_S	},
	{ 'E',	HB_EH	},
	{ 'T',	HB_TD	},
	{ 'B',	HB_BD	},
	{ 'D',	HB_DD	},
	{ 'G',	HB_GD	},
	{ '8',	HB_JH	},
	{ 'p',	HB_P	},
	{ 'b',	HB_B	},
	{ 't',	HB_T	},
	{ 'd',	HB_D	},
	{ 'k',	HB_K	},
	{ 'g',	HB_G	},
	{ '7',	HB_CH	},
	{ 'c',	HB_AO	},
	{ 'r',	HB_R	},
	{ 'K',	HB_KD	},
	{ 'z',	HB_Z	},
	{ 'w',	HB_W	},
	{ 'Q',	HB_NX	},
	{ 'v',	HB_V	},
	{ 'N',	HB_ND	},
	{ 'M',	HB_MF	},
	{ 'P',	HB_PD	},
	{ 'H',	HB_NJ	},
	{ 'S',	HB_SH	},
	{ '9',	HB_TS	},
	{ '0',	HB_DZ	},
	{ ',',  COMMA   },
	{ ' ',  WBOUND  },
	{ '\t', WBOUND  },
	{ '\'', S1      },
	{ '`',  S2      },
	{ '"',	SEMPH	},
	{ '#',  HYPHEN  },
	{ '(',  PPSTART },
	{ ')',  VPSTART },
	{ '*',  MBOUND  },
	{ '~',  BLOCK_RULES },
	{ '-',  SBOUND  }
};

PTAB ptab_ch[]  = {
	{ 'a',	CH_AP	},
	{ 'e',	CH_EP	},
	{ 'i',	CH_IY	},
	{ 'o',	CH_OP	},
	{ 'u',	CH_UW	},
	{ 'x',	CH_AX	},
	{ 'j',	CH_Y	},
	{ 'R',	CH_RR	},
	{ 'l',	CH_L	},
	{ 'L',	CH_LL	},
	{ 'm',	CH_M	},
	{ 'n',	CH_N	},
	{ 'h',	CH_NH	},
	{ 'f',	CH_F	},
	{ 's',	CH_S	},
	{ 'E',	CH_EH	},
	{ 'T',	CH_TD	},
	{ 'B',	CH_BD	},
	{ 'D',	CH_DD	},
	{ 'G',	CH_GD	},
	{ '8',	CH_JH	},
	{ 'p',	CH_P	},
	{ 'b',	CH_B	},
	{ 't',	CH_T	},
	{ 'd',	CH_D	},
	{ 'k',	CH_K	},
	{ 'g',	CH_G	},
	{ '7',   CH_CH	},
	{ 'c',	CH_AO	},
	{ 'r',	CH_R	},
	{ 'K',	CH_KD	},
	{ 'z',	CH_Z	},
	{ 'w',	CH_W	},
	{ 'Q',	CH_NX	},
	{ 'v',	CH_V	},
	{ 'N',	CH_ND	},
	{ 'M',	CH_MF	},
	{ 'P',	CH_PD	},
	{ 'H',	CH_NJ	},
	{ 'S',	CH_SH	},
	{ '9',	CH_TS	},
	{ '0',	CH_DZ	},
	{ ',',  COMMA   },
	{ ' ',  WBOUND  },
	{ '\t', WBOUND  },
	{ '\'', S1      },
	{ '`',  S2      },
	{ '"',	SEMPH	},
	{ '#',  HYPHEN  },
	{ '(',  PPSTART },
	{ ')',  VPSTART },
	{ '*',  MBOUND  },
	{ '~',  BLOCK_RULES },
	{ '-',  SBOUND  }
};

PTAB ptab_kr[]  = {
	{ 'a',	KR_AP	},
	{ 'e',	KR_EP	},
	{ 'i',	KR_IY	},
	{ 'o',	KR_OP	},
	{ 'u',	KR_UW	},
	{ 'x',	KR_AX	},
	{ 'j',	KR_Y	},
	{ 'R',	KR_RR	},
	{ 'l',	KR_L	},
	{ 'L',	KR_LL	},
	{ 'm',	KR_M	},
	{ 'n',	KR_N	},
	{ 'h',	KR_NH	},
	{ 'f',	KR_F	},
	{ 's',	KR_S	},
	{ 'E',	KR_EH	},
	{ 'T',	KR_TD	},
	{ 'B',	KR_BD	},
	{ 'D',	KR_DD	},
	{ 'G',	KR_GD	},
	{ '8',	KR_JH	},
	{ 'p',	KR_P	},
	{ 'b',	KR_B	},
	{ 't',	KR_T	},
	{ 'd',	KR_D	},
	{ 'k',	KR_K	},
	{ 'g',	KR_G	},
	{ '7',	KR_CH	},
	{ 'c',	KR_AO	},
	{ 'r',	KR_R	},
	{ 'K',	KR_KD	},
	{ 'z',	KR_Z	},
	{ 'w',	KR_W	},
	{ 'Q',	KR_NX	},
	{ 'v',	KR_V	},
	{ 'N',	KR_ND	},
	{ 'M',	KR_MF	},
	{ 'P',	KR_PD	},
	{ 'H',	KR_NJ	},
	{ 'S',	KR_SH	},
	{ '9',	KR_TS	},
	{ '0',	KR_DZ	},
	{ ',',  COMMA   },
	{ ' ',  WBOUND  },
	{ '\t', WBOUND  },
	{ '\'', S1      },
	{ '`',  S2      },
	{ '"',	SEMPH	},
	{ '#',  HYPHEN  },
	{ '(',  PPSTART },
	{ ')',  VPSTART },
	{ '*',  MBOUND  },
	{ '~',  BLOCK_RULES },
	{ '-',  SBOUND  }
};
#endif


/*
   The following lookup table is useful for doing fast conversion of a
   table into a bitmask.
*/
  
  
unsigned long BIT[32] = 
   {
   0x00000001, 0x00000002, 0x00000004, 0x00000008,
   0x00000010, 0x00000020, 0x00000040, 0x00000080,
   0x00000100, 0x00000200, 0x00000400, 0x00000800,
   0x00001000, 0x00002000, 0x00004000, 0x00008000,
   0x00010000, 0x00020000, 0x00040000, 0x00080000,
   0x00100000, 0x00200000, 0x00400000, 0x00800000,
   0x01000000, 0x02000000, 0x04000000, 0x08000000,
   0x10000000, 0x20000000, 0x40000000, 0x80000000
   };

/*
   The following tables define the legal tokens which can be used
   to specify the semantic features the corresponding form class.
*/

char *adj[32] = 	/* adjective semantic features */
{					/* examples... */
	"possesive",			/* 0)  bottle's */
	"proper",			/* 1)  */
	"place",				/* 2)  */
	"quantitative",		/* 3)  */
	"numerical",			/* 4)  */
	"ordinal",			/* 5)  */
	"demonstrative",		/* 6)  this */
	"negative",			/* 7)  noone's */
	"comparative",		/* 8)  */
	"superlative",		/* 9)  */
	NULL,			/* 10) */
	NULL,			/* 11) */
	NULL,			/* 12) */
	NULL,			/* 13) */
	NULL,			/* 14) */
	NULL,			/* 15) */
	NULL,			/* 16) */
	NULL,			/* 17) */
	NULL,			/* 18) */
	NULL,			/* 19) */
	NULL,			/* 20) */
	NULL,			/* 21) */
	NULL,			/* 22) */
	NULL,			/* 23) */
	NULL,			/* 24) */
	NULL,			/* 25) */
	NULL,			/* 26) */
	NULL,			/* 27) */
	NULL,			/* 28) */
	NULL,			/* 29) */
	NULL,			/* 30) */
	NULL				/* 31) */
};

 char *adv[32] =	/* adverb semantic features */
   {				/* examples... */
   "manner",			/* 0)  */
   "place",			/* 1)  */
   "degree",			/* 2)  */
   "time",			/* 3)  */
   "negative",			/* 4)  */
   "relative",			/* 5)  when, where, why, as */
   "interrogative",		/* 6)  */
   "emphatic",			/* 7)  end in the suffix "-ever" */
   "present",			/* 8)  implied -past */
   "future",			/* 9)  */
   "proximal",			/* 10) */
   "interior",			/* 11) */
   "existential", 		/* 12) */
   "orientation",		/* 13) west of */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *art[32] = 	/* article semantic features */
   {				/* examples... */
   "definite",			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *aux[32] =	/* auxiliary verb semantic features */
   {				/* examples... */
   "potential",			/* 0)  might */
   "ability",			/* 1)  can */
   "obligation",		/* 2)  ought, must, shall */
   "present",			/* 3)  will [vs. would] */
   "predicative",		/* 4)  will */
   "emphatic",			/* 5)  did */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *be[32] = 	/* be-form semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *bev[32] = 	/* bev-form semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *conj[32] = 	/* conjunction semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *ed[32] =		/* -ed verb semantic features */
   {				/* examples... */
   "performative",		/* 0)  */
   "locutionary",		/* 1)  */
   "momentary",			/* 2)  */
   "iterative",			/* 3)  */
   "state-change",		/* 4)  */
   "action",			/* 5)  */
   "surface-contact",		/* 6)  */
   "motion",			/* 7)  */
   "rapid",			/* 8)  */
   "itentional",		/* 9)  */
   "achievement",		/* 10) */
   "cognitive",			/* 11) */
   "plausible",			/* 12) */
   "rapid",			/* 13) */
   "emotive",			/* 14) */
   "casual",			/* 15) */
   "actual",			/* 16) */
   "agent",			/* 17) */
   "instrumental",		/* 18) */
   "dative",			/* 19) */
   "factitive",			/* 20) */
   "locative",			/* 21) */
   "objective",			/* 22) */
   "transitive",		/* 23) */
   "increase",			/* 24) */
   "sensory",			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *have[32] = 	/* have-forms semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *ing[32] =	/* -ing verb semantic features */
   {				/* examples... */
   "performative",		/* 0)  */
   "locutionary",		/* 1)  */
   "momentary",			/* 2)  */
   "iterative",			/* 3)  */
   "state-change",		/* 4)  */
   "action",			/* 5)  */
   "surface-contact",		/* 6)  */
   "motion",			/* 7)  */
   "rapid",			/* 8)  */
   "itentional",		/* 9)  */
   "achievement",		/* 10) */
   "congnitive",		/* 11) */
   "plausible",			/* 12) */
   "rapid",			/* 13) */
   "emotive",			/* 14) */
   "casual",			/* 15) */
   "actual",			/* 16) */
   "agent",			/* 17) */
   "instrumental",		/* 18) */
   "dative",			/* 19) */
   "factitive",			/* 20) */
   "locative",			/* 21) */
   "objective",			/* 22) */
   "transitive",		/* 23) */
   "increase",			/* 24) */
   "sensory",			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL,			/* 31) */
   };

 char *noun[32] =	/* noun semantic features */
   {				/* examples... */
   "plural",			/* 0)  man */
   "proper",			/* 1)  boy */
   "count",			/* 2)  papers */
   "abstract",			/* 3)  love */
   "living",			/* 4)  tree */
   "animate",			/* 5)  lobster */
   "human", 			/* 6)  John */
   "male",			/* 7)  Harry */
   "soft",			/* 8)  cloth */
   "small",			/* 9)  cup */
   "agent",			/* 10) actor */
   "solid",			/* 11) bat */
   "heavy",			/* 12) car */
   "slow",			/* 13) swim */
   "relational",		/* 14) mother */
   "applicative",		/* 15) butter */
   "orientation",		/* 16) west, middle */
   "emotive",			/* 17) hatred */
   "time",			/* 18) yesterday */
   "place",			/* 19) Ticonderoga */
   "edible",			/* 20) pancakes */
   "town",			/* 21) Henrietta */
   "street",			/* 22) Main */
   "measure",			/* 23) angstrom */
   "location",			/* 24) moon */
   "substance",			/* 25) cocaine */
   "numeral",			/* 26) four */
   "name",			/* 27) Lori */
   "event",			/* 28) riot */
   "valuable",			/* 29) platinum */
   "sensory",			/* 30) hear */
   "natural"			/* 31) sunlight */
   };

 char *pos[32] = 	/* possesive semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *prep[32] =	/* preposition semantic features */
   {				/* examples... */
   "direction-inwards",		/* 0)  */
   "direction-towards",		/* 1)  */
   "direction-upwards",		/* 2)  */
   "position-inwards",		/* 3)  */
   "position-towards",		/* 4)  */
   "position-upwards",		/* 5)  */
   "agentive",			/* 6)  */
   "instrumental",		/* 7)  */
   "dative",			/* 8)  */
   "factitive",			/* 9)  */
   "locative",			/* 10) */
   "objective",			/* 11) */
   "movement",			/* 12) */
   "temporal",			/* 13) */
   "present",			/* 14) */
   "inclusive",			/* 15) */
   "proximal",			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *pron[32] = 	/* singular pronoun semantic features */
   {				/* examples... */
   "male",			/* 0)  he, him */
   "plural",			/* 1)  she, her */
   "reflexive",			/* 2)  herself */
   "one",			/* 3)  I, we */
   "two",			/* 4)  you */
   "three",			/* 5)  he, him, she, her, they */
   "definite",			/* 6)  this */
   "positive",			/* 7)  */
   "proximal",			/* 8)  this */
   "anaphoric",			/* 9)  this */
   "cataphoric",		/* 10) */
   "demonstrative",		/* 11) this */
   "emphatic",			/* 12) */
   "possesive",			/* 13) mine */
   "personal",			/* 14) he */
   "reciprocal",		/* 15) himself */
   "relative",			/* 16) who */
   "interrogative",		/* 17) what */
   "negative",			/* 18) noone */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *subconj[32] =	/* subordinate conj semantic features */
   {				/* examples... */
   "causal",			/* 1)  */
   "temporal",			/* 2)  */
   "consecutive",		/* 3)  */
   "prior",			/* 4)  */
   "present",			/* 5)  */
   "additional",		/* 6)  */
   "contradictory",		/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *that[32] = 	/* that-forms semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *to[32] = 	/* to-forms semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *verb[32] =	/* verb semantic features */
   {				/* examples... */
   "performative",		/* 0)  */
   "locutionary",		/* 1)  */
   "momentary",			/* 2)  */
   "iterative",			/* 3)  */
   "state-change",		/* 4)  */
   "action",			/* 5)  */
   "surface-contact",		/* 6)  */
   "motion",			/* 7)  */
   "rapid",			/* 8)  */
   "itentional",		/* 9)  */
   "achievement",		/* 10) */
   "congnitive",		/* 11) */
   "plausible",			/* 12) */
   "rapid",			/* 13) */
   "emotive",			/* 14) */
   "casual",			/* 15) */
   "actual",			/* 16) */
   "agent",			/* 17) */
   "instrumental",		/* 18) */
   "dative",			/* 19) */
   "factitive",			/* 20) */
   "locative",			/* 21) */
   "objective",			/* 22) */
   "transitive",		/* 23) */
   "increase",			/* 24) */
   "sensory",			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *who[32] = 	/* who-forms semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *neg[32] =	/* neg-forms semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *inter[32] = 	/* interjection semantic features */
   {				/* examples... */
   "obscene",			/* 0)  shit! */
   "mild",			/* 1)  darn! */
   "sacrilegious",		/* 2)  christ! */
   "surprise",			/* 3)  wow! */
   "dismay",			/* 4)  shucks! */
   "locutionary",		/* 5)  hello! good-bye! */
   "religious",			/* 6)  halleluyaa! */
   "laudatory",			/* 7)  bravo! */
   "affirmative",		/* 8)  ok! */
   "approbationary",		/* 9)  hurrah! */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };
 char *ref[32] = 	/* reflexive semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *part[32] = 	/* particle semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *contraction[32] =/* contraction semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

 char *func[32] =	/* function word semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };

char *cont[32] =	/* function word semantic features */
   {				/* examples... */
   NULL,			/* 0)  */
   NULL,			/* 1)  */
   NULL,			/* 2)  */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };


char *character[32] =	/* character semantic features */
   {				/* examples... */
   "alpha",			/* 1)  "a".."z" */
   "iso",			/* 2)  ø, ¼,... */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };


char *refr[32] =	/* character semantic features */
   {				/* examples... */
   "alpha",			/* 1)  "a".."z" */
   "iso",			/* 2)  ø, ¼,... */
   NULL,			/* 3)  */
   NULL,			/* 4)  */
   NULL,			/* 5)  */
   NULL,			/* 6)  */
   NULL,			/* 7)  */
   NULL,			/* 8)  */
   NULL,			/* 9)  */
   NULL,			/* 10) */
   NULL,			/* 11) */
   NULL,			/* 12) */
   NULL,			/* 13) */
   NULL,			/* 14) */
   NULL,			/* 15) */
   NULL,			/* 16) */
   NULL,			/* 17) */
   NULL,			/* 18) */
   NULL,			/* 19) */
   NULL,			/* 20) */
   NULL,			/* 21) */
   NULL,			/* 22) */
   NULL,			/* 23) */
   NULL,			/* 24) */
   NULL,			/* 25) */
   NULL,			/* 26) */
   NULL,			/* 27) */
   NULL,			/* 28) */
   NULL,			/* 29) */
   NULL,			/* 30) */
   NULL				/* 31) */
   };



/*
   The following table defines the legal tokens which can be used
   to specify form class.
*/
     
/* this is left in, but looks like it is unused - 8/9/95  JDB */     
char *form_class[32] =		/* form classes */
   {
   "adj",			/* 0)  adjective */
   "adv",			/* 1)  adverb */
   "art",			/* 2)  article */
   "aux",			/* 3)  auxiliary verb */
   "be",			/* 4)  be-forms */
   "bev",			/* 5)  bev-forms */
   "conj",			/* 6)  conjunctions */
   "ed",			/* 7)  past-tense verbs ending in "ed" */
   "have",			/* 8)  have-forms */
   "ing",			/* 9)  verbs ending in "ing" */
   "noun",			/* 10) noun */
   "pos",			/* 11) possesive */
   "prep",			/* 12) preposition */
   "pron",			/* 13) pronoun */
   "subconj",			/* 15) subordinate conjunction */
   "that",			/* 16) that-forms */
   "to",			/* 17) to-forms */
   "verb",			/* 18) verb */
   "who",			/* 19) who-forms */
   "neg",			/* 20) negation */
   "inter",			/* 21) interjection */
   "ref",			/* 22) reflexive */
   "part",			/* 23) particle */
   "func",			/* 24) function word */
   "cont",			/* 25) cont */
   "character",			/* 25) character */
   "refr",			/* 26) REFERENCE */
   NULL,			/* 27) UNDEFINED */
   NULL,			/* 28) UNDEFINED */
   NULL,			/* 29) UNDEFINED */
   NULL,			/* 30) reserved for contractions */
   "homograph",			/* 31) homograph (or suffix type) */
   };

/*
   The following table is used to map form classes to their respective
   semantic feature tables.
*/
       
/* this looks unused, but I'm leaving tables in to be safe... 8/30/95  JDB */       
char **feature_table[32] =
{
	adj,				/* 0)  adjective */
	adv,				/* 1)  adverb */
	art,				/* 2)  article */
	aux,				/* 3)  auxiliary verb */
	be,				/* 4)  be-forms */
	bev,				/* 5)  bev-forms */ 
	conj,			/* 6)  conjunctions */
	ed,				/* 7)  past-tense verbs ending in "ed" */
	have,			/* 8)  have-forms */
	ing,				/* 9)  verbs ending in "ing" */
	noun,			/* 10) noun */
	pos,				/* 11) possesive */
	prep,			/* 12) preposition */
	pron,			/* 13) singular pronoun */
	subconj,			/* 14) subordinate conjunction */
	that,			/* 15) that-forms */
	to,				/* 16) to-forms */
	verb,			/* 17) verb */
	who,				/* 18) who-forms */
	neg,				/* 19) negation */
	inter,			/* 20) interjection */
	ref,				/* 21) reflexive */
	part,			/* 22) particle */
	func,			/* 23) function word */
	cont,			/* 24) cont  */
	character,		/* 25) character */
	refr,			/* 26) UNDEFINED */
	NULL,			/* 27) UNDEFINED */
	NULL,			/* 28) UNDEFINED */
	NULL,			/* 29  form class marker */
	contraction,		/* 30) contraction */
	NULL,			/* 31) homograph */
};                                

