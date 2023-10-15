#ifndef CMDMAIN_H
#define CMDMAIN_H
#include "opthread.h"

#ifdef ARM7
extern unsigned int cmd_main(void* threadData);
#else
extern OP_THREAD_ROUTINE( cmd_main, void* threadData );
#endif

#endif /* CMDMAIN_H */
