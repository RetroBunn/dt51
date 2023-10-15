#include "dustytypes.h"
#include "ile_accd.h"
#include "pkind.h"

const BYTE bno_tbl[160]={
	pkind_noun,				/*   1 Human beings, animals, personal names */
	pkind_noun,				/*   2 Company names, organization names, country names */
	pkind_noun,				/*   3 Things, materials */
	pkind_noun,				/*   4 Time */
	pkind_noun,				/*   5 Places, geographical names */
	pkind_noun,				/*   6 Numbers */
	pkind_noun,				/*   7 Abstract noun */
	pkind_noun,				/*   8 Actions */
	pkind_digit,			/*   9 Numerals */
	pkind_noun,				/*  10 Classical Japanese noun */
	pkind_noun,				/*  11 Noun */
	pkind_noun,				/*  12 Noun */
	pkind_noun,				/*  13 Noun */
	pkind_others,			/*  14 Special symbols */
	pkind_ren,				/*  15 Attributives */
	pkind_ren,				/*  16 NO-attributive */
	pkind_ren,				/*  17 ARU-attributive */
	pkind_ren,				/*  18 NNA-attributive */
	pkind_adjv,				/*  19 Adjectival verbs */
	pkind_adjv,				/*  20 Adjectival verb - TEKI */
	pkind_adjv,				/*  21 Adjectival verb - FUU */
	pkind_adjv,				/*  22 Adjectival verbs */
	pkind_adjv,				/*  23 Adjectival verbs */
	pkind_adjv,				/*  24 Adjectival verbs */
	pkind_adjv,				/*  25 Adjectival verbs */
	pkind_adv,				/*  26 Adverbs */
	pkind_adv,				/*  27 Adverbs */
	pkind_adv,				/*  28 Adverbs */
	pkind_adv,				/*  29 Adverbs */
	pkind_adv,				/*  30 Adverbs */
	pkind_adv,				/*  31 Adverbs */
	pkind_adv,				/*  32 Exclamations */
	pkind_adv,				/*  33 Adverbs */
	pkind_adv,				/*  34 Adverbs */
	pkind_verb_stem,		/*  35 Verb stems */
	pkind_verb_stem,		/*  36 Verb stems */
	pkind_verb_stem,		/*  37 Verb stems */
	pkind_verb_stem,		/*  38 Verb stems */
	pkind_verb_stem,		/*  39 Verb stems */
	pkind_verb_stem,		/*  40 Verb stems */
	pkind_verb_stem,		/*  41 Verb stems */
	pkind_verb_stem,		/*  42 Verb stems */
	pkind_verb_stem,		/*  43 Verb stems */
	pkind_verb_stem,		/*  44 Verb stems */
	pkind_verb_stem,		/*  45 Verb stems */
	pkind_verb_stem,		/*  46 Verb stems */
	pkind_verb_stem,		/*  47 Verb stems */
	pkind_verb_stem,		/*  48 Verb stems */
	pkind_verb_sa,			/*  49 Verbal nouns */
	pkind_verb_stem,		/*  50 Verb stems */
	pkind_verb_stem,		/*  51 Verb stems */
	pkind_particle,			/*  52 Extended verbs */
	pkind_adj_stem,			/*  53 Adjective stems */
	pkind_adj_stem,			/*  54 Adjective stems */
	pkind_aux_verb,			/*  55 Negative auxiliary verb stems */
	pkind_adj_stem,			/*  56 Adjective stems */
	pkind_adj_stem,			/*  57 Adjective stems */
	pkind_adj_stem,			/*  58 Adjective stems */
	pkind_adj_stem,			/*  59 Adjective stems */
	pkind_noun,				/*  60 Noun and long vowel connection */
	pkind_pref,				/*  61 Personal name antecedent */
	pkind_pref,				/*  62 prefix */
	pkind_pref,				/*  63 prefix */
	pkind_pref,				/*  64 prefix "O"*/
	pkind_pref,				/*  65 prefix */
	pkind_pref,				/*  66 prefix "DAI", "ZU", "HYOU"*/
	pkind_pref,				/*  67 prefix */
	pkind_pref,				/*  68 prefix */
	pkind_pref,				/*  69 prefix */
	pkind_pref,				/*  70 prefix */
	pkind_pref,				/*  71 prefix */
	pkind_pref,				/*  72 prefix */
	pkind_particle,			/*  73 Particle */
	pkind_particle,			/*  74 Particle */
	pkind_particle,			/*  75 Particle */
	pkind_particle,			/*  76 Particle */
	pkind_particle,			/*  77 Particle */
	pkind_particle,			/*  78 Particle */
	pkind_particle,			/*  79 Particle */
	pkind_particle,			/*  80 Particle */
	pkind_particle,			/*  81 Particle */
	pkind_particle,			/*  82 Particle */
	pkind_particle,			/*  83 Particle */
	pkind_particle,			/*  84 Particle */
	pkind_particle,			/*  85 Particle */
	pkind_particle,			/*  86 Particle */
	pkind_particle,			/*  87 Particle */
	pkind_particle,			/*  88 Particle */
	pkind_particle,			/*  89 Particle */
	pkind_particle,			/*  90 Particle */
	pkind_particle,			/*  91 Particle */
	pkind_particle,			/*  92 Particle */
	pkind_particle,			/*  93 Particle */
	pkind_particle,			/*  94 Particle */
	pkind_particle,			/*  95 Particle */
	pkind_particle,			/*  96 Particle */
	pkind_particle,			/*  97 Particle */
	pkind_particle,			/*  98 Particle */
	pkind_particle,			/*  99 Particle */
	pkind_particle,			/* 100 Particle */
	pkind_particle,			/* 101 Particle */
	pkind_particle,			/* 102 Particle */
	pkind_particle,			/* 103 Particle */
	pkind_particle,			/* 104 Particle */
	pkind_particle,			/* 105 Particle */
	pkind_particle,			/* 106 Particle */
	pkind_particle,			/* 107 Particle */
	pkind_particle,			/* 108 Particle */
	pkind_particle,			/* 109 Particle */
	pkind_particle,			/* 110 Particle */
	pkind_particle,			/* 111 Particle */
	pkind_particle,			/* 112 Particle */
	pkind_particle,			/* 113 Particle */
	pkind_particle,			/* 114 Particle */
	pkind_particle,			/* 115 Particle */
	pkind_particle,			/* 116 Particle */
	pkind_aux_verb,			/* 117 Adverb */
	pkind_aux_verb,			/* 118 Adverb */
	pkind_aux_verb,			/* 119 Adverb */
	pkind_aux_verb,			/* 120 Adverb */
	pkind_aux_verb,			/* 121 Adverb */
	pkind_aux_verb,			/* 122 Adverb */
	pkind_aux_verb,			/* 123 Adverb */
	pkind_aux_verb,			/* 124 Adverb */
	pkind_aux_verb,			/* 125 Adverb */
	pkind_aux_verb,			/* 126 Adverb */
	pkind_aux_verb,			/* 127 Adverb */
	pkind_aux_verb,			/* 128 Adverb */
	pkind_aux_verb,			/* 129 Adverb */
	pkind_aux_verb,			/* 130 Adverb */
	pkind_aux_verb,			/* 131 Adverb */
	pkind_aux_verb,			/* 132 Adverb */
	pkind_aux_verb,			/* 133 Adverb */
	pkind_aux_verb,			/* 134 Adverb */
	pkind_aux_verb,			/* 135 Adverb */
	pkind_aux_verb,			/* 136 Adverb */
	pkind_aux_verb,			/* 137 Adverb */
	pkind_aux_verb,			/* 138 Adverb */
	pkind_verb_inflect,		/* 139 Conjugation ending */
	pkind_verb_renyou,		/* 140 Verb conjunctive conjugation ending */
	pkind_verb_inflect,		/* 141 Conjugation ending */
	pkind_verb_inflect,		/* 142 Conjugation ending */
	pkind_verb_inflect,		/* 143 Conjugation ending */
	pkind_verb_inflect,		/* 144 Conjugation ending */
	pkind_verb_inflect,		/* 145 Conjugation ending */
	pkind_verb_inflect,		/* 146 Conjugation ending */
	pkind_verb_inflect,		/* 147 Conjugation ending */
	pkind_verb_inflect,		/* 148 Conjugation ending */
	pkind_verb_inflect,		/* 149 Conjugation ending */
	pkind_verb_inflect,		/* 150 Conjugation ending */
	pkind_verb_inflect,		/* 151 Conjugation ending */
	pkind_verb_inflect,		/* 152 Conjugation ending */
	pkind_verb_inflect,		/* 153 Conjugation ending */
	pkind_verb_inflect,		/* 154 Conjugation ending */
	pkind_adj_inflect,		/* 155 Adjective conjugation ending */
	pkind_adj_inflect,		/* 156 Adjective conjugation ending */
	pkind_adj_inflect,		/* 157 Adjective conjugation ending */
	pkind_adj_inflect,		/* 158 Adjective conjugation ending */
	pkind_adj_inflect,		/* 159 Adjective conjugation ending */
	pkind_adj_inflect		/* 160 Adjective conjugation ending */
};

/* End of ile_accd.c */

