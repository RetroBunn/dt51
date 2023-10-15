/**********************************************
	ILE_JKNC.C	updated at 8th January 1991
	Dictionary search table
 **********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_bunh.h"
#include	"ile_edic.h"
#include	"ile_idic.h"
#include	"ile_jknh.h"
#include	"ile_kkhh.h"
#include	"ile_nydh.h"
#include	"ile_func.h"

/*========== JKN_INIT() ==============
	Function: Initialize the dictionary search table.
  ===================JknfShokikasuru==*/
void JKN_INIT() 
{ 
	register integer_16 cx;
	for(cx=MAX_INERT*MAX_EDIC;cx--;)
	{
		dut_value[cx]=0;
		dut_edofs[cx]=0;
		dut_idaddr[cx]=(BYTE *)0;
	}
}

/*
 *	The following part is now a dummy.
 *	There is supposed to be a bug, but it is not certain.
 *	It will be restarted as soon as the routing is determined.
 *	define O_NULL
 */

void clear_null() 
{
#if defined(O_NULL)
	null_no=0;
#endif
}

void push_null(WORD ptr, WORD ofs, WORD page)
{
#if defined(O_NULL)
	register WORD *pp,*op;
	WORD *bp,cx;

	if(null_no<MAX_NULL){
		/*
		 * For the processing of next target, longer segment, or shorter segment, 
		 * the element in the watching sentence is not to be registered.
		 */
		if(conv_mode==CONV_NEXT||conv_mode==CONV_LONG||conv_mode==CONV_SHORT){
			if(ceptr<=fsptr){ return; }
		}

		pp=null_ptr; op=null_ofs; bp=null_page;
		for(cx=null_no ;cx--; ++pp,++op,++bp){
			if(ptr==(*pp) && ofs==(*op) && page==(*bp)){
				return;
			}
		}

		null_ptr[null_no]=ptr;
		null_ofs[null_no]=ofs;
		null_page[null_no]=page;
		++null_no;
		/*FNX_PRINTF("%d : %d, %x\n",null_no,ptr,ofs);*/
	}
#endif
}

int check_edic_null() 
{
#if defined(O_NULL)
	register WORD *pp,*op;
	WORD *bp,cx;

	pp=null_ptr; op=null_ofs; bp=null_page;
	for(cx=null_no ;cx--; ++pp,++op,++bp){
		if(ceptr==(*pp) && edic_ofs==(*op) && edic_page_no==(*bp)){
			/*FNX_PRINTF(" ignore.");*/
			return 1;
		}
	}
#endif
	return 0;
}

int check_idic_null() 
{
#if defined(O_NULL)
	register integer_16 *pp;
	register WORD *op;
	integer_16 cx;

	pp=null_ptr; op=null_ofs;
	for(cx=null_no ;cx--; ++pp,++op){
		if(ceptr==(*pp) && idic_addr==(BYTE *)(*op)){
			/*FNX_PRINTF("\nignore.");*/
			return 1;
		}
	}
#endif
	return 0;
}

/***************************** END OF ILE_JKNC.C *****************************/

