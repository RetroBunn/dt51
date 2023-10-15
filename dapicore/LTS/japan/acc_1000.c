/*********************************************
	ACC_1000.C	updated at 12th April 1990
	Accent processing - initial settings
 *********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_acch.h"
#include	"ile_nydh.h"
#include	"ile_shdh.h"
#include	"ile_stch.h"
#include	"ile_stzh.h"
#include	"ile_func.h"
#include "pkind.h"
#include "ile_accd.h"

/*========== ACC1000() =====================================
	Function: Lookup in the parts of speech table, decide the part of speech components.
	From the basic accent model, set the basic accent
  ==========================================================*/
void ACC1000() 
{
	register integer_16 i,j; integer_16 ac,op,ol,sp,pk;
	/*
	* Because a part (0..3) of the raw accent information will be broken by the accent 
	* processing (ACC2000)  copy stc_accent_raw[][0..3] to work area.
	*/
	for(i=stc_ptr;i--;)
	{
		for(j=4;j--;)
		{ 
			acc_accent_raw[i][j]=stc_accent_raw[i][j]; 
		}
	}
	/*
	* Look up in the parts of speech table and set thepart of speech.
	* Because ou can't understand/know the suffix by the end number, look up in the control information.
	*/
	for(i=stc_ptr;i--;)
	{
		phrase_ptr[i]=stc_out_ptr[i]; 
		phrase_len[i]=stc_out_len[i];
		for(j=0;j<stc_nbno[i];++j)
		{
			if(ac=stc_bno[i][j])
			{		/* ignore 0 */
				phrase_kind[i]=bno_tbl[ac-1];
				goto ACC1000_20;
			}
		}
		
ACC1000_20:;
		   /* Check suffix */
		   /* [-], (Jishin) (Jiritsu) are treated as a suffix.  Jiritsu - independent, free-standing words.*/
		   if(stc_ctl[i] & BITCTL_SUF){ phrase_kind[i]=pkind_jiritsu; }
		   if(stc_f2[i] & BITFLG2_SELF){ phrase_kind[i]=pkind_suf; }
		   /*
		   * The (you) for (IBM Kiyou):
		   *	 Kango-Japanese words of chinese origin (kanji).  For Sino-Japanese words (kanji), things that are not possible t be at the first of lead a suffixes.
		   */
		   if((stc_f2[i] & BITFLG2_KANGO)||(stc_stz[i] & BITSTZ_KANGO))
		   {
			   if((stc_ctl[i] & BITCTL_FIRST)==0)
			   {
				   phrase_kind[i]=pkind_suf;
			   }
		   }
	}
	/*
	* For Verb root (verb stem of a word) - adjective stem (adjective root of a word) not only the first end number
	* but look at all of the end numbers.  If even 1 of them is the stem or root or
	* the word, then that is the s?.  This is a necessary part for the proccessing of composite 
	* words with declined or conjugated endings.
	*
	* For example, the (Hajime) in (ugokihajme) 
	* but the (hajime) in (ugokihajime ga) is a noun
	* so, the ending elements, all of the end numbers/digits have to be checked and see if it is a verb or not
	*/
	for(i=stc_ptr;i--;)
	{
		for(j=0;j<stc_nbno[i];++j)
		{
			if( ac=stc_bno[i][j] )
			{		/* ignore 0 */
				if(bno_tbl[ac-1]==pkind_verb_stem || 
				   bno_tbl[ac-1]==pkind_adj_stem)
				{
					phrase_kind[i]=bno_tbl[ac-1]; goto ACC1000_40;
				}
			}
		}
ACC1000_40:;
	}
	
	/* Categorize the independent (free-standing words, verb, adverb, adjective, noun) 
	   and ancillary (attached, aux verb or particle) words.
	*/
	ACC2900(pkind_verb_inflect,	pkind_fuzoku);		// fuzoku - ancillary (attached words)
	ACC2900(pkind_adj_inflect,	pkind_fuzoku);
	ACC2900(pkind_verb_sa,		pkind_jiritsu);		// jiritsugo - independent or free-standing words
	ACC2900(pkind_adv,			pkind_jiritsu);
	ACC2900(pkind_adjv,			pkind_jiritsu);
	ACC2900(pkind_noun,			pkind_jiritsu);
	ACC2900(pkind_aux_verb,		pkind_fuzoku);
	ACC2900(pkind_particle,		pkind_fuzoku);
	
	/*
	Everything that has the elements (factors) of coming at the first or lead is an 
	independent or free-standing word (kij) etc.  However, this excludes prefixes, 
	pre-noun adjectivals, verb stems, adjective stems.
	
	 Everything that has the elements (factors) of not coming at the first or lead 
	 with the exception of suffix is an ancillary (attached) word.
	 However, suffixes and conjunctive forms of end of words.
	 
	  The reason this type of processin is necessary is because ...
	  Eventhough there is the same end number, it is possibel to have both 
	  independent (free-standing) words and ancillary (attached) words.
	  
		For example, the (te oru) in (ugoite oru) is a verb, 
		and the (ta) in (ugokitai) is an adjective.
	*/
	for(i=stc_ptr;i--;)
	{
		pk=phrase_kind[i];
		if(stc_ctl[i] & BITCTL_FIRST)
		{
			if( pk!=pkind_pref && 
				pk!=pkind_ren && 
				pk!=pkind_verb_stem && 
				pk!=pkind_adj_stem)
			{
				phrase_kind[i]=pkind_jiritsu;
			}
		}
		else
		{
			if(pk!=pkind_suf && pk!=pkind_verb_renyou)
			{
				phrase_kind[i]=pkind_fuzoku;
			}
		}
	}
	/*
	When an ancillary (attached word comes right before a conjunctive form 
	of the end of a word, it is an ancillary (attached) word.
	renyou - conjunctive form
	fuzokugo - ancillary (attached) word.
	
	  The (ri) in (ketsugi/niata/ri/mashi/te) is a conjunctive form of the end 
	  of a word, but (niata) is not a verb, it is an ancillary (attached) word, 
	  so (ri) would also be an ancillary (attached).
	*/
	for(i=1;i<stc_ptr;++i)
	{
		if( phrase_kind[i]==pkind_verb_renyou && 
			phrase_kind[i-1]==pkind_fuzoku)
		{
			phrase_kind[i]=pkind_fuzoku;			// jiritsugo - independent or free-standing words
		}
	}
	
	/* 
	The potential verb's conjugative suffix has the end numbers of 47 and 48.
	Because these are processed with the highest priority, they are dealt with 
	in the same manner as the conjunctive form of the end of words.  
	So (ugokihajimeru) and (ugokehajimeru) and (ukerarehajimeru) are all treated 
	as the same.  1990, pril 12 revision.
	*/
	for(i=0;i<stc_ptr-2;++i)
	{
		if( phrase_kind[i]==pkind_verb_stem && 
			phrase_kind[i+2]==pkind_verb_stem)
		{
			phrase_kind[i+1]=pkind_verb_renyou;		// renyou - conjunctive form
		}
	}
	
	/*
	Kango (Japanese words of Chinese origin) are independent (free-standing)
	words (excluding prefixes and suffixes).
	*/
	for(i=1;i<stc_ptr;++i)
	{
		if((stc_f2[i] & BITFLG2_KANGO)||(stc_stz[i] & BITSTZ_KANGO))
		{
			if( phrase_kind[i]!=pkind_suf && 
				phrase_kind[i]!=pkind_pref)
			{
				phrase_kind[i]=pkind_jiritsu;
			}
		}
	}
	
	/* 
		Alphanumeric characters, simplistic words, special characters, single kanji will be treated special.
		tankan - simple kanji
	
	  Single kanji that isn't possible to be first or at the lead (long vowels, syllabic nasal consonants 
	  assimilated sound "tsu" geminative consonant) are treated as suffixes.
	*/
	for(i=stc_ptr;i--;)
	{
		j=stc_kind[i];
		if(j==DICKIND_D)
		{ 
			phrase_kind[i]=(BYTE)stc_ed_ofs[i]; 
		}
		if(j==DICKIND_T)
		{
			if(stc_ctl[i] & BITCTL_FIRST)
			{
				switch(inert_kind[stc_in_ptr[i]])
				{
				case CHRKIND_KKana:
				case CHRKIND_HKana:
					phrase_kind[i]=pkind_jiritsu;		// jiritsugo - independent or free-standing words
				default:
					phrase_kind[i]=pkind_tankanji;		// tankan - simple kanji	
				}
			}
			else
			{
				phrase_kind[i]=pkind_fuzoku;			// fuzoku - ancillary (attached) word
			}
		}
		
		if(omega[stc_out_ptr[i]]==0xFF)
		{
			/*	
				Characters not read are special characters eventhough 
				special characters that are read will not be treated as special characters.
			*/
			phrase_kind[i]=pkind_others;
		}
		if(net_phrase_in_len(i)==1)
		{
			if(inert_kind[stc_in_ptr[i]]==CHRKIND_Alpha)
			{
				phrase_kind[i]=pkind_alpha1;
			}
		}
	}
	
	/* Initialization of the accent storage area */
	for(i=MAX_OMEGA;i--;)
	{ 
		accent0[i]=0; 
	}
	
	for(sp=0;sp<stc_ptr;sp++)
	{
		op=stc_out_ptr[sp]; 
		ol=stc_out_len[sp];
		
		/* Special characters do not have accents so ignore */
		if(phrase_kind[sp]==pkind_others)
		{
			for(i=0;i<ol;i++)
			{ 
				accent0[op+i]=0; 
			}
			goto ACC1000_700;
		}
		
		ac=acc_accent_raw[sp][0];
		switch(ac)
		{
			
		case 0:						/* flat, monotony */
		case 1:						/* front high */
			accent0[op]= (ac==0? 1:0x82);
			if(ol>1)
			{
				for(i=2;i<=ol;i++)
				{
					accent0[op+i-1] = (ac==0? 2:1);
				}
			}
			break;
		default:					/* middle high - end high */
			if(ol==1)
			{
				accent0[op]=0x82;	/* be careful of 1 accent (pulse) words. */
			}
			else
			{
				accent0[op]=1;
				for(i=2;i<=ol;i++)
				{
					accent0[op+i-1] = (i<ac ? 2 : (i==ac ? 0x82 : 1));
				}
			}
		}
ACC1000_700:;
	}
	
	/* 
	Because parts of speech will be broken by accent processing (ACC2000), 
	copy the phrase_kind[] into work area 
	*/
	/* 
	For the time being, this work area will be used for the following purpose.  
	Compound verbs, compund adjectives should be thought of as one word, so a 
	pause should not be put in.  With the Pause1000(), it will use this 
	parts of speech info and judge whether or not it is a comppund word with a 
	conjugated ending.
	*/
	for(i=stc_ptr;i--;)
	{ 
		phrase_kind_sav[i]=phrase_kind[i]; 
	}
	
                                                                       }


/*========== ACC1K00() ============================
	Function: To classify the kango into single kango words or compound kango words.
	kango - Japanese words with chinese origin (kanji)
  =================================================*/
void ACC1K00() 
{
	integer_16 i,t,k;
	WORD pk;
	/*
	* Look up in the parts of speech table and set the part of speech.
	* Because you won't know the stuff by the end number, look up in the control information
	*/
	for(i=stc_ptr;i--;)
	{
		pk=phrase_kind[i];
		if( pk==pkind_jiritsu &&
			((stc_f2[i] & BITFLG2_KANGO)||(stc_stz[i] & BITSTZ_KANGO)) )
		{
			t=net_phrase_in_len(i);
			k=knj_number(i);
			if(k==0)
			{ 
				goto ACC1K00_160; 
			}
			/*if(t!=k){ phrase_kind[i]=pkind_jiritsuc; goto ACC1K00_160; }*/
			if(t>3)
			{ 
				phrase_kind[i]=pkind_jiritsuc; 
				goto ACC1K00_160; 
			}
		}
ACC1K00_160:;
	}
}

/***************************** END OF ACC_1000.C *****************************/
