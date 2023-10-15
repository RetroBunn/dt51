#ifndef DUSTYTYPES_H
#define DUSTYTYPES_H
/* more cute types that look suspiciously like Windoze */

#include "port.h"

typedef int8_t integer_8;
typedef int16_t integer_16;
typedef int32_t integer_32;
typedef BYTE binary_8;
typedef WORD binary_16;
typedef DWORD binary_32;
typedef BYTE *LPBYTE;
typedef WORD *LPWORD;
typedef WORD *u_shortp;
#define	sign(x)	((x) & 0x80)

#endif /*DUSTYTYPES_H*/

