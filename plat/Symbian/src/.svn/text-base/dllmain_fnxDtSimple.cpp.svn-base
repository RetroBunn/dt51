/**************************************************************************
**                                                                        *
**  FILE        :  dllmain_FnxDTSimple.cpp                                *
**                                                                        *
**  DESCRIPTION :  Source file for main dll entry point                   *
**                                                                        *										  *
**                                                                        *
**************************************************************************/

///////////////////////////////////////////////////////////////////////
//
// DLL entry point
//
// The reason code is of no interest here and it is ignored
///////////////////////////////////////////////////////////////////////

#include <e32std.h>
#include <reent.h>
#ifndef MAIN_DTDLL
// don't map FnxTtsDtCloseSTDLIB in the main dll
#include "port.h"
#include "ltsnames.h"
#include "tts.h"
#endif

extern "C" void _chkstk() { /* empty body */ }


GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
	{
	return KErrNone;
	}

#if defined(__cplusplus)
extern "C" {
#endif

EXPORT_C void FnxTtsDtCloseSTDLIB()
{
	CloseSTDLIB();
}

#if defined(__cplusplus)
}
#endif
