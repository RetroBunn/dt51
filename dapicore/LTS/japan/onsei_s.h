#ifndef ONSEI_S_H
#define ONSEI_S_H

#include "port.h"
//#include <stdlib.h> //moved to port.h for each platform mlt
//#include <stddef.h>

/*
 *
 */
typedef struct {
	int16_t onsei_procno;		/*  */
	int16_t onsei_usetankan;		/*  */
	int16_t onsei_kouseisystem;	/*  */
	int16_t onsei_crlfexist;		/*  */
	int16_t onsei_readcrlf;		/*  */

	uint8_t* onsei_inert;		/* 
							 * 
							 */
	uint8_t* onsei_omega;		/* 
							 *
							 * 
							 *
							 * 
							 *	
							 *	
							 *	
							 *	
							 *	
							 *	
							 *  
							 * 
							 */
	uint8_t* onsei_speak;		/* 
							 */
	uint16_t* onsei_sent;		/* 
							 */
 
	int16_t onsei_ninert;/* */
	int16_t onsei_sentno;/* */
	int16_t onsei_wsno;	/* 
							 * 
							 */
	int16_t onsei_acctype;/* */
	int16_t onsei_status;/* */

    int (*onsei_stop)(void*);		/* */
    int (*onsei_alloc)(void** addr, size_t size);	/* */
    int (*onsei_read)(int page, size_t size, void* addr);		/* */
    int (*onsei_write)(int page, size_t size, void* addr); /* */
    void (*onsei_dealloc)(void** addr);	/* call to free memory allocated by onsei_alloc */
} STRUCT_ONSEI;

#endif /* ONSEI_S_H */

/* End of onsei_s.h */