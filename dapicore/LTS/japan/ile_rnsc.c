/********************************************
	ILE_RNSC.C	updated at 29th June 1991
	Logical input and output
 ********************************************/

#define		EXT		extern

#include	"onsei.h"
#include	"ile_errh.h"
#include	"ile_fddh.h"
#include	"ile_rnsc.h"
#include	"ile_func.h"

#define	incptr(ptr)	((ptr==last)? PageTable : ptr+1)

/* Page table entry (Buffer for paging is managed by PTE.)*/
typedef struct 
{
	LPBYTE PBA;		/* Page buffer address */
	WORD PI;		/* Page information(Valid bit, Modfy bit, Page No) */
} PTE;

/* Mask for fetching each content of PI */
#define	V	0x8000	/* Valid bit(Set 1 when the entry is unused) */
#define	M	0x4000	/* Modfy bit(Set 1 when there is a write request.) */
#define	PN	0x3fff	/* Page No(Page number 1 - 16,384) */

/* Number of PTEs prepared */
#define	MaxPTE	25

static PTE PageTable[MaxPTE] = {{0,0}};
static PTE* head = NULL;
static PTE* tail = NULL;
static PTE* last = NULL;

static PTE *GetBuffer(void);
static PTE *SearchBuffer(WORD page);

/*========== RNS_INIT() ======================================
	Function: Reserve the page buffer, and initialize the ring buffer.
  ===========================================RnsfShokikasuru==*/
void RNS_INIT(void) 
{
	WORD count;
	PTE* bp;
	LPBYTE addr;
	int allocFailed = 0;
	head=bp=PageTable;
	
	for (count=MaxPTE; count--; ) 
	{
		if(RtkfAlloc(&addr,Fdd_Header.Fdd_EdicPageSize)==0) 
		{
			allocFailed = 1;
			break;
		}
		bp->PI = V;
		bp->PBA = addr;
		++bp;
	}
	
	/* If the page cannot be reserved, an error is generated.*/
	if(allocFailed)
	{
		PTE* bpp;
		for (bpp=PageTable; bpp->PBA; ++bpp) 
		{
			RtkfDealloc(&(bpp->PBA));
		}
		jp_ERROR(Err_Fatal_Alloc);
	}
	tail=last=(--bp);
}

void RNS_DEALLOC()
{
	int count;
	PTE* bpp;
	for (bpp=PageTable, count = 0; bpp->PBA && count < MaxPTE; ++bpp, ++count) 
	{
		RtkfDealloc(&(bpp->PBA));
	}
}

/*========== RnsfReadEdic(Page,addr) ======================
	Function: Use the paging and read the specified page.
	InputFPage	Page number
	OutputF*addr	Page buffer address
  =========================================================*/
void RnsfReadEdic(WORD Page,LPBYTE* addr)
{
	PTE *bp;
	
	if((bp=SearchBuffer(Page))==NULL) 
	{
		bp=GetBuffer();
		RtkfRead(Page,Fdd_Header.Fdd_EdicPageSize,bp->PBA);
		bp->PI=Page;
	}
	*addr = bp->PBA;
}

/*========== RnsfWriteEdic(Page) ============================
	Function: Set the Modfy bit of PTE in the specified page to on.
	Input: Page	Page number
  ===========================================================*/
void RnsfWriteEdic(WORD Page)
{
	PTE *bp;
	
	/* If there is no page to be written in the buffer, an error is generated.*/
	if((bp=SearchBuffer(Page))==NULL) 
	{
		jp_ERROR(Err_Fatal_Alloc); 
	}
	bp->PI |= M;
}

/*========== RnsfFlushBuffer() ====================
	Function: Write one page of the pages of which Modfy bit is on.
	Output:	0:There is no page to be written.
			1:Normal end.
  =================================================*/
BOOL RnsfFlushBuffer(void)
{
	PTE *pp;
	WORD pi;
	
	for(pp=head; pp; pp=incptr(pp)) 
	{
		pi=pp->PI;
		if(((pi & V)==0) && (pi & M)) 
		{
			RtkfWrite( (integer_16)(pi&PN), Fdd_Header.Fdd_EdicPageSize, (void *)pp->PBA);
			pp->PI &= ~M;
			return 1;
		}
		if(pp==tail)
		{ 
			return 0; 
		}
	}
	
	return 0;
}

/*========== SearchBuffer(page) ========================================
	Function: Check each PTE of PageTable to find if there is any necessary page in buffer.
	Input: page	Page number
	Output:0:No applicable page
		( 0:Pointer to PTE (Avoid being set to 0.)
  ======================================================================*/
static PTE *SearchBuffer(WORD page)
{
	register PTE *pp;
	register WORD pi;
	
	for(pp=head; pp; pp=incptr(pp)) 
	{
		pi=pp->PI;
		if((pi & V)==0) 
		{
			pi &= PN;
			if(pi==page) 
			{
				return pp;
			}
		}
		if(pp==tail)
		{ 
			return NULL; 
		}
	}
	
	return NULL;
}

/*========== GetBuffer() ============================
	Function: Reserve the buffer are for paging.
	Output: Pointer to PTE
  ===================================================*/
static PTE *GetBuffer(void)
{
	register PTE *pp;
	register WORD pi;
	
	pp=incptr(tail);
	pi=pp->PI;
	if((pi & V)==0) 
	{
		if(pi & M) 
		{
			RtkfWrite((integer_16)(pi&PN), Fdd_Header.Fdd_EdicPageSize, pp->PBA);
			pp->PI &= ~M;
		}
		head=incptr(head);
	}
	tail=incptr(tail);
	return pp;
}

/***************************** END OF ILE_RNSC.C *****************************/

