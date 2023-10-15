/********************************************
	ILE_ENVH.H	updated at	19th May 1989
	Environment
 ********************************************/

EXT STRUCT_ONSEI *onsei_addr;	/* Parameter structure address */

extern int (*user_stop)(void*);			/* Termination judgment function */
extern int (*user_alloc)(void** addr, size_t size);				/* Area reservation function */
extern int (*user_read)(int page, size_t size, void* addr);				/* Physical input function */
extern int (*user_write)(int page, size_t size, void* addr);                         /* Physical output function */
extern void (*user_dealloc)(void** addr);				

//#if defined(unix)
#define MAX_POP_TIMES 499			/* Limitation of POP times */
//#endif

/***************************** END OF ILE_ENVH.H *****************************/

