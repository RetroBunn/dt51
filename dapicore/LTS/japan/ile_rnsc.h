#ifndef ILE_RNSC_H
#define ILE_RNSC_H
#include "onsei.h"

extern void  RNS_INIT(void);
extern void  RNS_DEALLOC(void);
extern void  RnsfReadEdic( WORD, LPBYTE * );
extern void  RnsfWriteEdic( WORD );
extern BOOL  RnsfFlushBuffer(void);

#endif /* ILE_RNSC_H */

