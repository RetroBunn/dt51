/*******************************************
	ILE_ERRC.C	updated at 19th May 1989
	Error processing
 *******************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_errh.h"
#include	"ile_kkhh.h"
#include	"ile_func.h"

jmp_buf jmpbuf;
integer_16 error_code = 0;

/*========== ERROR(ax) ==================================================
	Function: Specify the error state of the error code ax, and go to the default label.
  =======================================================ErrfSetteisuru==*/
void jp_ERROR(integer_16 ax)
{	
	error_code=ax;			/* Make the error code setting.*/
	longjmp(jmpbuf,1);		/* Go to the specified label.*/
}

/*========== ERROR5000() =========================
	Function: Because of an error occurrence, specify the output result.
  =============================ErrfKekSetteisuru==*/
void ERROR5000() {
	kkhstat=err;
}

/***************************** END OF ILE_ERRC.C *****************************/

