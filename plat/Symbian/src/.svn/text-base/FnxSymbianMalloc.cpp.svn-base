/**************************************************************************
**                                                                        *
**  FILE        :  malloc.cpp                                               *
**                                                                        *
**  DESCRIPTION :  Source file for malloc()                               *
**                                 calloc()                               *
**                                 free()                                 *
**                                 realloc()                              *
**                                                                        *
**  SYMBIAN heap functions												  *
**                                                                        *
**************************************************************************/

#include <e32std.h>
#ifndef BLD_DECTALK_DLL
#include "fnxexstdlib.h"
#else
#include <string.h>
#endif

/* -------------------- global functions ---------------------- */

#ifdef __cplusplus
extern "C" {
#endif

void*	epocmalloc ( size_t size )
{	
	return User::Alloc(size);
}

void*	epoccalloc ( size_t nel, size_t size )
{
	void*	 result;

	size *= nel;
	result = epocmalloc( size );

	if	( result )
	{
		memset( result, '\0', size );
	}
	else
		User::LeaveNoMemory();
	return result;
}

void	epocfree ( void* mem )
{
	User::Free(mem);
}

void*	epocrealloc ( void* mem, size_t newsize )
{
	return User::ReAlloc(mem,newsize);
}

#ifdef __cplusplus
}
#endif
