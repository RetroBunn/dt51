/*******************************************
	ILE_RTKC.C	updated at 19th May 1989
	Environment function
 *******************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_envh.h"
#include	"ile_errh.h"
#include	"ile_kkhh.h"
#include	"ile_func.h"

/* == RtkfChudanShiraberu ==
  Sentence structureÅFRtkfChudanShiraberu
  Function: Call the user definition interrupt request routine.
*/
void RtkfChudanShiraberu()
{
    if((*user_stop)(0)) 
	{
        ERROR5000();
        kkhstat=shoki;
        jp_ERROR(Err_Chuudan);
    }
}

/* == RtkfAlloc ==
  Function: Call the user definition area reserve routine.
*/
int RtkfAlloc(void** addr, size_t size)
{
    integer_16 status;
    status = (*user_alloc)(addr,size);
    return status == 0? 1: 0;
}

/* == RtkfDealloc ==
   free memory allocated by RtkfAlloc
*/
void RtkfDealloc(void** addr)
{
    (*user_dealloc)(addr);
}

/* == RtkfRead ==
  Function: Call the user definition reading routine.
*/
void RtkfRead(integer_16 pno, size_t size, void* addr)
{
    integer_16 status;
    if(status = (*user_read)(pno,size,addr)) 
	{
        jp_ERROR(status);
    }
}

/* == RtkfWrite ==
  Function: Call the user definition writing routine.
*/
void RtkfWrite(integer_16 pno, size_t size, void* addr)
{
    integer_16 status;
    if(status = (*user_write)(pno,size,addr)) 
	{
        jp_ERROR(status);
    }
}

/***************************** END OF ILE_RTKC.C *****************************/

