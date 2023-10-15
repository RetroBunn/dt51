#include "dectalkf.h"

#ifdef FP_VTM
#include "vtm_fa.c"
#else

#if defined __linux__
#define _inline inline
#endif

#define DEFINE_TABLES

#include "port.h"
#include "ph_def.h"     /*  MVP: Now phinst.h includes phdefs.h */
#include "samprate.h"   /*  Constants used by the vocal tract model   */
#include "vtmtable.h"   /*  Tables used by the vocal tract model      */
#endif