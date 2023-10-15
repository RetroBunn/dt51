#include <windows.h>
#include "fnxstdlib.h"

double fnxaDiffTimeDays( FNX_TIMESTRUCT timer1, FNX_TIMESTRUCT timer2 )
{
   return (double)( (double)(timer1 - timer2) / 86400.0f );
}


void delay(long ms)
{
	Sleep(ms);
}

#if defined(__MWERKS__)
/*
   I found this to take the place of the one normally found in the MS VC runtime library.
   CodeWarrior does not contain one in its library.
   
   This sample function was originally marked 'inline', but that, of course, defeats the
   purpose of having one so that libraries resolve.
   
   hlm 010423
*/
// floattolong ()
//
// long floattolong (float value)
//  converts a float value to a long value.
//
// Performance-wise:
//  longvalue = (long)floatvalue ;
//
//  The bad thing about this behaviour is that the compiler uses it's internal _ftol function
//  which is a very safe register flag checking function.
//  Needless to say, this can take a significant amount of time to call.
//
long _ftol(float f)
{
   static long l;
   __asm {
      fld dword ptr [f];
      fistp dword ptr [l];
   } return l;
}
#endif
