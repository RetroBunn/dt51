/** 
 * @file onseiapi.h 
 * The user-visible onsei APIs
 */

#ifndef ONSEIAPI_H
#define ONSEIAPI_H

//#include <stdint.h>

/**
 * Performs initialization for the conversion processing.
 *  -- Secures the place for Kana Chinese character (Kanji) mixture sentences, for the phonogram string,
 *     and for the word or phrase information, and calls the pointer for each.
 *  -- When you can not wait for the analysis to end, you define the function u_stop
 *     which forces it to end and call that function's far pointer.
 *  -- Calls the dictionary path and symbolic reading flag.
 *  -- The parameters above can not be modified in the middle of processing.
 *     When wanting to modify, call the onsei_term, and then call the onsei_init again.
 *
 * 
 * @param[in] dpath Pointer to the dictionary path
 * @param[in] inbuf Pointer to Kana and Chinese character (Kanji) mixture sentence (JIS X 0208)
 * @param[in] talkbuf Pointer to the place where the phonogram string is stored
 * @param[in] sentbuf Pointer to the place where word or phrase information is stored
 * @param[in] kousei when 0, disregard signs, when 1, read all signs
 * @param[in] u_stop function that discontinues conversion
 * @return 
 *			0:		        Normal termination
 *			Err_Fatal_DIC:	        No dictionary
 *			Err_Broken:	        Dictionary broken
 *
 */
extern int onsei_init(const char *dpath, uint8_t *inbuf, uint8_t *talkbuf, uint16_t *sentbuf, int16_t kousei, int(*u_stop)(void*));

/**
 * Performs all the types of conversion processing.
 * In the types of processing (sw), you can define any of the following:
 *
 *   PROC_FIRST:		First conversion
 *   PROC_NEXT:			Attention word or phrase next candidate
 *   PROC_TERM:			Decides on learned information
 *   PROC_RIGHT:		Attention word or phrase move to the right
 *   PROC_LEFT:			Attention word or phrase move to the left
 *   PROC_SHORT:		Splits into the direction of short word or phr
 * 
 * @param[in] sw type of processing 
 * @return
 *
 * When the sw is anything but PROC_FIRST, PROC_NEXT, or PROC_SENT_NO,  the value is as follows:
 *    0:			Normal termination
 *    Err_NaibuOVF:		The word or phrase number is over limit (too big) or the phonogram string is too long
 *    Err_Chuudan:		Stopped at at u_stop()
 *    Err_Fatal_Edic:		Dictionary malfunction
 *    Err_Fatal_Idic:		Dictionary malfunction
 *    Err_IdouFunou:		Word or phrase movement is not possible
 *    Err_NextNone:		There is no next candidate
 *    Err_RestrictCNT:	Timed out
 *
 * When the sw is PROC_FIRST or PROC_NEXT, then 
 *    15 or less:		Normal termination. The first word is positioned at the top.
 *    Err_NaibuOVF:		The word or phrase number is over or the phonogram string is too long
 *    Err_Chuudan:		Stopped at at u_stop()
 *    Err_Fatal_Edic:		Dictionary malfunction
 *    Err_Fatal_Idic:		Dictionary malfunction
 *    Err_IdouFunou:		Word or phrase movement is not possible
 *    Err_NextNone:		There is no next candidate
 *    Err_HenkanTochuu:	Conversion of a word that is not in the dictionary
 *    Err_RestrictCNT:	Timed out
 *
 * When the sw is PROC_SENT_NO: then return the current word or phrase number
 */
extern int onsei_henkan(int16_t sw);

/**
 * Completes the conversion processing. Writes out the learned information, etc.
 *
 * @return 
 *    0:	Normal termination
 *    else:	Dictionary malfunction
 */
extern int onsei_term( );

/**
 * Performs registering of the dictionary
 * 
 * @param[in] fall The position of the top of the accent
 * @return
 *    0:			Normal termination
 *    1:			The way it is read or the top position of the accent is not correct
 *    Err_EdicTooLong:	The written item or the reading is too long
 *    Err_TourokuSumi:	The same one is already registered
 *    Err_EdicOVF:		Can not be registered -> if the dictionary readjusts, then it will be OK
 */
extern int onsei_add(int16_t fall);

/**
 * Performs dictionary deletion
 *
 * @param[in] fall The position of the top of the accent
 * @return
 *    0:			Normal termination 
 *    1:			The way it is read or the top position of the accent is not correct
 *    Err_EdicTooLong:	The written item or the reading is too long
 *    Err_MiTouroku:		Word not registered 
 */
extern int onsei_del(int16_t fall);

/**
 * Perform dictionary deletion of the words that are in the process of currently being converted.
 * Before calling this function, it is absolutely necessary to call the first conversion and then the next candidate.
 * When the return value of the first conversion and the next candidate is 16 or more,
 * (except when the accent is at the top position), you must not call it.
 *
 * @return 
 *    0:			Normal termination 
 *    Err_MiTouroku:		It is not the user's registration word
 */
extern int onsei_del2( );
#endif /* ONSEIAPI_H */

/* End of onseiapi.h */
