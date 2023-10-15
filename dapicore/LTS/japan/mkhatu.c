//#include	<stdio.h> //moved to port.h for each platform mlt
//#include	<string.h>
#include "port.h"
#include "dustytypes.h"

#ifndef ERROR
#define	ERROR	0x0ff
#endif

#define	swap(a, b)	(a ^= b, b ^= a, a ^= b)

/*
 * Phonetic symbol table
 *
 * ただし、ぁ、ぃ．．．Special codes (because of the speed)
 * 「い、う」 Special codes for conversion to a long vowel
 * "ゐ, ゑ, を, ゎ"   Fill 0xff.
 *
 *《Special codes》
 *ぁ、ぃ、ぅ、ぇ、ぉ、ゃ、ゅ、ょ、い、う、あ、え、お
 *  f0  f1  f2  f3  f4  f5  f6  f7  f8  f9  fa  fb  fc
 *
 * "が, ぎ, ぐ, げ, ご" are nasal voiced consonants.
 */
static const BYTE hatu_kigou1[86] = {
	/* ぁ     あ     ぃ     い     ぅ     う     ぇ     え */
	0x0f0, 0x0fa, 0x0f1, 0x0f8, 0x0f2, 0x0f9, 0x0f3, 0x0fb,
	/* ぉ     お     か     が     き     ぎ     く     ぐ */
	0x0f4, 0x0fc, 0x008, 0x078, 0x009, 0x079, 0x00a, 0x07a,
	/* け     げ     こ     ご     さ     ざ     し     じ */
	0x00b, 0x07b, 0x00c, 0x07c, 0x010, 0x080, 0x019, 0x089,
	/* す     ず     せ     ぜ     そ     ぞ     た     だ */
	0x012, 0x082, 0x013, 0x083, 0x014, 0x084, 0x020, 0x090,
	/* ち     ぢ     っ     つ     づ     て     で     と */
	0x029, 0x089, 0x0c8, 0x032, 0x082, 0x023, 0x093, 0x024,
	/* ど     な     に     ぬ     ね     の     は     ば */
	0x094, 0x038, 0x039, 0x03a, 0x03b, 0x03c, 0x040, 0x098,
	/* ぱ     ひ     び     ぴ     ふ     ぶ     ぷ     へ */
	0x0a0, 0x041, 0x099, 0x0a1, 0x042, 0x09a, 0x0a2, 0x043,
	/* べ     ぺ     ほ     ぼ     ぽ     ま     み     む */
	0x09b, 0x0a3, 0x044, 0x09c, 0x0a4, 0x050, 0x051, 0x052,
	/* め     も     ゃ     や     ゅ     ゆ     ょ     よ */
	0x053, 0x054, 0x0f5, 0x058, 0x0f6, 0x05a, 0x0f7, 0x05c,
	/* ら     り     る     れ     ろ     ゎ     わ     ゐ */
	0x060, 0x061, 0x062, 0x063, 0x064, ERROR, 0x068, ERROR,
	/* ゑ     を     ん     ヴ     ヵ     ヶ */
	ERROR, 0x004, 0x0d0, 0x0aa, ERROR, ERROR
};

/* Characters that convert the following "い" to a long vowel */
static const BYTE char_code2[30] = {
	/* ぃ     い     き     ぎ     し     じ     ち     ぢ */
	0x023, 0x024, 0x02d, 0x02e, 0x037, 0x038, 0x041, 0x042,
	/* に     ひ     び     ぴ     み     り     ヴ     ぇ */
	0x04b, 0x052, 0x053, 0x054, 0x05f, 0x06a, 0x074, 0x027,
	/* え     け     げ     せ     ぜ     て     で     ね */
	0x028, 0x031, 0x032, 0x03b, 0x03c, 0x046, 0x047, 0x04d,
	/* へ     べ     ぺ     め     れ */
	0x058, 0x059, 0x05a, 0x061, 0x06c,
	0
};

/* Characters that convert the following "お" to a long vowel */
static const BYTE char_code3[18] = {
	/* ぉ     お     こ     ご     そ     ぞ     と     ど */
	0x029, 0x02a, 0x033, 0x034, 0x03d, 0x03e, 0x048, 0x049,
	/* の     ほ     ぼ     ぽ     も     ょ     よ     ろ う */
	0x04e, 0x05b, 0x05c, 0x05d, 0x062, 0x067, 0x068, 0x06d, 0x026,
	0
};

/* Characters that cannot be expressed with one 2-byte character */
static const BYTE hatu_kigou2[8][16] = {
	/* "ぁ" that precedes "つふヴくぐ"*/
	{ 0x030, 0x048, 0x0a8, 0x0b0, 0x0b8, 0 },

	/* "ぃ" that precedes "すてつふうずでヴくぐ"*/
	{ 0x011, 0x021, 0x031, 0x049, 0x069, 0x081, 0x091, 0x0a9,
	  0x0b1, 0x0b9, 0 },

	/* "ぅ" that precedes "とど"*/
	{ 0x022, 0x092, 0 },

	/* "ぇ" that precedes "しちつふうじぢヴくぐ"*/
	{ 0x01b, 0x02b, 0x033, 0x04b, 0x06b, 0x08b, 0x08b, 0x0ab,
	  0x0b3, 0x0bb, 0 },

	/* "ぉ" that precedes "つふうヴくぐ"*/
	{ 0x034, 0x04c, 0x06c, 0x0ac, 0x0b4, 0x0bc, 0 },

	/* "ゃ" that precedes "きしちにひふみりぎじぢでびぴヴ"*/
	{ 0x00d, 0x018, 0x028, 0x03d, 0x045, 0x04d, 0x055, 0x065,
	  0x07d, 0x088, 0x088, 0x095, 0x09d, 0x0a5, 0x0ad, 0 },

	/* "ゅ" that precedes "きしちにひふみりぎじぢでびぴヴ"*/
	{ 0x00e, 0x01a, 0x02a, 0x03e, 0x046, 0x04e, 0x056, 0x066,
	  0x07e, 0x08a, 0x08a, 0x096, 0x09e, 0x0a6, 0x0ae, 0 },

	/* "ょ" that precedes "きしちにひふみりぎじぢでびぴヴ"*/
	{ 0x00f, 0x01c, 0x02c, 0x03f, 0x047, 0x04f, 0x057, 0x067,
	  0x07f, 0x08c, 0x08c, 0x097, 0x09f, 0x0a7, 0x0af, 0 }
};

static const BYTE char_code1[8][16] = {
	/* "ぁ" that precedes "つふヴくぐ"*/
	{ 0x044, 0x055, 0x074, 0x02f, 0x030, 0 },

	/* "ぃ" that precedes "すてつふうずでヴくぐ"*/
	{ 0x039, 0x046, 0x044, 0x055, 0x026, 0x03a, 0x047, 0x074,
	  0x02f, 0x030, 0 },

	/* "ぅ" that precedes "とど"*/
	{ 0x048, 0x049, 0 },

	/* "ぇ" that precedes "しちつふうじぢヴくぐ"*/
	{ 0x037, 0x041, 0x044, 0x055, 0x026, 0x038, 0x042, 0x074,
	  0x02f, 0x030, 0 },

	/* "ぉ" that precedes "つふうヴくぐ"*/
	{ 0x044, 0x055, 0x026, 0x074, 0x02f, 0x030, 0 },

	/* "ゃ" that precedes "きしちにひふみりぎじぢでびぴヴ"*/
	{ 0x02d, 0x037, 0x041, 0x04b, 0x052, 0x055, 0x05f, 0x06a,
	  0x02e, 0x038, 0x042, 0x047, 0x053, 0x054, 0x074, 0 },

	/* "ゅ" that precedes "きしちにひふみりぎじぢでびぴヴ"*/
	{ 0x02d, 0x037, 0x041, 0x04b, 0x052, 0x055, 0x05f, 0x06a,
	  0x02e, 0x038, 0x042, 0x047, 0x053, 0x054, 0x074, 0 },

	/* "ょ" that precedes "きしちにひふみりぎじぢでびぴヴ"*/
	{ 0x02d, 0x037, 0x041, 0x04b, 0x052, 0x055, 0x05f, 0x06a,
	  0x02e, 0x038, 0x042, 0x047, 0x053, 0x054, 0x074, 0 }
};

/*
 *  A program that generates a phonetic symbol from the kana string.
 *  kana: Pointer to the kana string
 *  hatu: Pointer to the phonetic symbol
 *               (Area is reserved by the calling side.)
 *  The last of the kana string is 0x00.
 *  the function mkhatu returns the length of the phonetic symbol.
 *
 */
int mkhatu(BYTE *kana, BYTE *hatu)
{
    BYTE k1, *p, *q;
	register BYTE *kanaptr, *hatuptr;

 	hatuptr = hatu;
	kanaptr = &kana[strlen(kana) - 1];
	for( ; kanaptr > kana; kanaptr -= 2) 
	{

		/* Symbol */
		if (*(kanaptr - 1) == 0x021) 
		{
			*hatuptr++ =
				*kanaptr == 0x03c? 0x0c0:	/* ー: C0 */
				*kanaptr == 0x047? 0x0e0:	/* ': E0 */
				*kanaptr == 0x03f? 0x0e1:	/* ／: E1 */
				ERROR;
			continue;
		}

		/* Check the out-of-range code. */
		if( (*(kanaptr - 1) != 0x024 && *(kanaptr - 1) != 0x025) ||
			*kanaptr - 0x021 > sizeof(hatu_kigou1) ||
			(k1 = hatu_kigou1[*kanaptr - 0x021]) == ERROR) 
		{
			*hatuptr++ = ERROR;
			continue;
		}

		/* Store it if it is not an exception. */
		if (k1 < 0x0f0) 
			*hatuptr++ = k1;

		/*
		 * For "ぁ, ぃ, ...," don't forget to use the table of char_code1 and hatu_kigou2
		 *   to convert and 
		 *  to reduce kanaptr by 2.
		 */
		else if (k1 < 0x0f8) 
		{
			k1 -= 0xf0;
			if (kanaptr >= kana + 2 &&
				(p = (BYTE *)FNX_STRCHR(&char_code1[k1][0], *(kanaptr - 2))) != NULL) 
			{
				*hatuptr++ = hatu_kigou2[k1][p - &char_code1[k1][0]];
				kanaptr -= 2;
			}
			else
				*hatuptr++ = ERROR;
		}
		/*
		 * Convert "い" that is to be converted to a long vowel.
		 *  Otherwise, set the "い" code.
		 */
		else if (k1 == 0x0f8) 
		{
			*hatuptr++ = kanaptr - 1 != kana &&
				(strchr(char_code2, *(kanaptr - 2)) && *(kanaptr - 3) != 0x021)?
				0x0c0: 0x001;
		}
		/*
		 * Convert "う" that is to be converted to a long vowel.
		 * Otherwise, set the "う" code.
		 */
		else if (k1 == 0x0f9) 
		{
			*hatuptr++ = kanaptr - 1 != kana &&
				strchr(char_code3, *(kanaptr - 2))? 0x0c0: 0x002;
		}
		/* "ああ" to "あー" */
		else if (k1 == 0x0fa) 
		{
			*hatuptr++ = kanaptr - 1 != kana &&
				(*(kanaptr - 2) == 0x022) ? 0x0c0 : 0x000;
		}
		/* "ええ" to "えー" */
		else if (k1 == 0x0fb) 
		{
			*hatuptr++ = kanaptr - 1 != kana &&
				(*(kanaptr - 2) == 0x028) ? 0x0c0 : 0x003;
		}
		/* "おお" to "おー" */
		else if (k1 == 0x0fc) 
		{
			*hatuptr++ = kanaptr - 1 != kana &&
				(*(kanaptr - 2) == 0x02a) ? 0x0c0 : 0x004;
		}
	}

	/* Because it is converted from the end, reverse it. */
	for (p = hatu, q = hatuptr - 1; p < q; p++, q--)
		swap(*p, *q);

	/* When the beginning of the word is a nasal voiced consonant, change it to oral voiced consonant. */
	if (*hatu > 0x77 && *hatu < 0x80) 
		*hatu -= 8;  
	return 
		hatuptr - hatu;
}


