/*******************************************
	ACC_000X.C	updated at 19th May 1989
	Basic accent creation routine
*******************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_acch.h"
#include	"ile_shdh.h"
#include	"ile_func.h"

/****************************************************************************/
/*																			*/
/*			From here contains the basic accent creation routine				*/
/*																			*/
/****************************************************************************/

/*========== ACC000H(p) ==============
  function: put the elements of the p-number section into the monotonous form or model
  ====================================*/
void ACC000H(integer_16 p)
{
    integer_16 pp,i; 
	integer_16 pl;

    pp=phrase_ptr[p]; 
	pl=phrase_len[p];
    accent0[pp]=1;
    if(pl>1) 
	{
        for(i=2;i<=pl;i++)
		{ 
			accent0[pp+i-1]=2; 
		}
    }
}

/*========== ACC0001(p) ==============
  function: put the elements of the p-number (section) into the top (front) hight form or model
  ====================================*/
void ACC0001(integer_16 p)
{
    integer_16 pp,i; 
	integer_16 pl;

    pp=phrase_ptr[p]; 
	pl=phrase_len[p];
    accent0[pp]=0x82;
    if(pl>1) 
	{
        for(i=2;i<=pl;i++)
		{ 
			accent0[pp+i-1]=1; 
		}
    }
}

/*========== ACC0002(p) ==============
  function: put the elements of the p-number (section) into the bottom (back) high form or model
  ====================================*/
void ACC0002(integer_16 p)
{
    integer_16 pp,i; 
	integer_16 pl;

    pp=phrase_ptr[p]; 
	pl=phrase_len[p];
    if(pl==1) 
	{
        accent0[pp]=0x82;		/* 1 mora element */
    } 
	else 
	{
        accent0[pp]=1;
        for(i=2;i<pl;i++)
		{ 
			accent0[pp+i-1]=2; 
		}
        accent0[pp+pl-1]=0x82;
    }
}

/*========== ACC0003(p,fall) =========
  function: put the elements of p-numbers (section) into the rise and fall form or model.
  ====================================*/
void ACC0003(integer_16 p, integer_16 fall)
{
    integer_16 pp,i; integer_16 pl;

    pp=phrase_ptr[p]; 
	pl=phrase_len[p];
    if(fall==1) 
	{
        accent0[pp]=0x82;
        for(i=2;i<=pl;i++) 
		{
            accent0[pp+i-1]= 1;
        }
    } else 
	{
        accent0[pp]=1;
        for(i=2;i<=pl;i++)
		{
            accent0[pp+i-1]= (i<fall ? 2 : (i==fall ? 0x82 : 1));
        }
    }
}

/*========== ACC0004(q) ================
  function: lower the overall elements of q-number (section)
  ======================================*/
void ACC0004(integer_16 q)
{
    integer_16 qp,i; 
	integer_16 ql;
    qp=phrase_ptr[q]; 
	ql=phrase_len[q];
    for(i=0;i<ql;i++)
	{ 
		accent0[qp+i]=1; 
	}
}

/*========== ACC0005(q) ================
  function: raise the overall elements of q-number (section)
  ======================================*/
void ACC0005(integer_16 q)
{
    integer_16 qp,i; 
	integer_16 ql;
    qp=phrase_ptr[q]; 
	ql=phrase_len[q];
    for(i=0;i<ql;i++) 
	{ 
		accent0[qp+i]=2; 
	}
}

/***************************** END OF ACC_000X.C *****************************/
