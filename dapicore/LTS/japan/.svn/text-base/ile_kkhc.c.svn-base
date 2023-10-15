/*************************************************
	ILE_KKHC.C	updated at 26th September 1989
	Main program
 *************************************************/

#define		EXT		extern

//#include <stddef.h> //moved to port.h for each platform MLT 01/24/06
#include "port.h"
#include	"onsei.h"
#include	"ile_bunh.h"
#include	"ile_errh.h"
#include	"ile_stch.h"


extern	void	ENV_INIT();
extern	void	ENV_TERM();
extern	void	PRON_FIRST();
extern	void	PRON_NEXT();
extern	void	PRON_SHORT();
extern	void	PRON_LONG();
extern	void	PRON_RIGHT();
extern	void	PRON_LEFT();
extern	void	PRON_TERM();
extern	void	PRON_SENT_NO();
extern  void	EDIC_DELETE2();
extern  void	EDIC_ADD();
extern  void	EDIC_DELETE();
extern  void	PRON_ACON();
extern  void	PRON_ACOFF();
extern  void	PRON_PAUSE_INS();
extern  void	PRON_PAUSE_DEL();
extern  void	display_user();

STRUCT_ONSEI* onsei_addr = NULL;

/* Jump table */
#define		TBLSIZE		18
static void(* JmpTbl[TBLSIZE])() = {
  ENV_INIT,							/*  1 Initial settings for sentence voice conversion processing */
  ENV_TERM,							/*  2 End of sentence voice conversion processing */
  PRON_FIRST,							/*  3 Initial sentence voice conversion */
  PRON_NEXT,							/*  4 Watching sentence next target */
  PRON_SHORT,							/*  5 Dividing a sentence in shorter segments */
  PRON_LONG,							/*  6 Dividing a sentence in longer segments */
  PRON_RIGHT,							/*  7 Moving the watching sentence to the right */
  PRON_LEFT,							/*  8 Moving the watching sentence to the left */
  PRON_TERM,							/*  9 Determining conversion */
  PRON_SENT_NO,						/* 10 Retrieving the watching sentence number */
  EDIC_DELETE2,						/* 11. Deleting a user word from the external dictionary */
  EDIC_ADD,							/* 12. Adding a user word to the external dictionary */
  EDIC_DELETE,						/* 13. Deleting a user word from the external dictionary */
  PRON_ACON,							/* 14 Combining accents */
  PRON_ACOFF,							/* 15 Not combining accents */
  PRON_PAUSE_INS,						/* 16 Inserting a pause */
  PRON_PAUSE_DEL,						/* 17 Removing a pause */
  display_user,						/* 18 Retrieving a user name */
};

integer_16 entrypt(STRUCT_ONSEI* addr)
{
	register integer_16 no;
	
	onsei_addr = addr;
	no = addr->onsei_procno;
	
	error_code=0;
	if(setjmp(jmpbuf)==0) 
	{
		if(1<=no && no<=TBLSIZE) 
		{
			(*JmpTbl[no-1])();
		}
	}
	
	addr->onsei_status  = error_code;
	addr->onsei_wsno    = ws_no;
	addr->onsei_acctype = stc_accent_raw[0][0];
	return error_code;
}

/***************************** END OF ILE_KKHC.C *****************************/

