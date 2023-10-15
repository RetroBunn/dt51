/**
 * @file entrypt.h 
 * Entry point function that communicates between onsei layer code and lower level code
 */

#ifndef ENTRYPT_H
#define ENTRYPT_H
#include "onsei_s.h"

/**
 * ?
 *
 * @param[in] param structure to modify
 * @return status to onsei_init(), onsei_term(), and onsei_henkan()
 */
extern int16_t entrypt(STRUCT_ONSEI *param);

#endif /* ENTRYPT_H */

/* End of entrypt.h */
