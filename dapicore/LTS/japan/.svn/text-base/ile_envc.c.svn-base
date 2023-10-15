/************************************************
	ILE_ENVC.C	updated at 26th September 1991
	Initial conversion setting, initial conversion, conversion end
	Next conversion target, conversion determination
 ************************************************/

#define		EXT		extern

//#include	<stddef.h> //moved to port.h for each platform MLT 01/24/06
#include "port.h"

#include	"onsei.h"
#include	"ile_envh.h"
#include	"ile_errh.h"
#include	"ile_fddh.h"
#include	"ile_kkhh.h"
#include	"ile_nydh.h"
#include	"ile_stzh.h"
#include	"ile_func.h"
#include "ile_rnsc.h"

#define	VeraDateL		6
#define	VeraVerL		4
#define	VerwVerL		(VeraVerL / 2)

int (*user_stop)(void*) = NULL;
int (*user_alloc)(void** addr, size_t size) = NULL;
int (*user_read)(int page, size_t size, void* addr) = NULL;
int (*user_write)(int page, size_t size, void* addr) = NULL;
void (*user_dealloc)(void** addr) = NULL;				

/* Date of creation of the sentence voice conversion program */
static const integer_16	VerwVer[2]={2,10};
static BYTE VerbDate[]="910821";


/*========== ENV_INIT() =================================
	Function: Initial settings of sentence voice conversion (For details, see the external specifications.)
         	Call it with the jump table.
  ======================================ShkfShokikasuru==*/
void ENV_INIT()
{
	BYTE *si;
	integer_16 cx;
	integer_16 ax;
	LPBYTE shd;
	
	user_stop    = onsei_addr->onsei_stop;
	user_alloc   = onsei_addr->onsei_alloc;
	user_dealloc = onsei_addr->onsei_dealloc;
	user_read    = onsei_addr->onsei_read;
	user_write   = onsei_addr->onsei_write;
	
	RtkfRead(1,1,(LPBYTE)FddHDR);	/* Read the top track (the buffer is DS.) */
	/* Obtain the last track number of the initial load data.*/
	
#if defined(C_SUN4)||defined(OS9)
	/*FNX_PRINTF("size:%d\n",sizeof(DIC_STRUCT));*/
	SwapHeader((LPBYTE)FddHDR);
#endif
	
	cx=Fdd_Header.Fdd_HdrSector-1;
	/* Calculate the number of remaining load data tracks. */
	RtkfRead(2,cx,(LPBYTE)FddBODY);	/* Read the remaining information (the buffer is DS.) */
	
	cx=Fdd_Header.Fdd_HdrSector;
	ax=Fdd_Header.Fdd_EdicIndSector;
	
	if (Fdd_EdicIndex != NULL) {
		RtkfDealloc(&Fdd_EdicIndex);
	}
	if(RtkfAlloc(&Fdd_EdicIndex,ax)==0) {
		jp_ERROR(Err_Fatal_Alloc); 
	}
	RtkfRead((integer_16)(cx+1), ax, Fdd_EdicIndex);				/* Read the external dictionary index. (the buffer is DS.) */
	
	Fdd_Header.Fdd_EdicKeyOfs-=Fdd_Header.Fdd_EdicIndOfs;	/* offset on the ES of key of the dictionary index */
	
	if(user_checksum()==0) {		/* patch check */
		jp_ERROR(FAT_Patch);			/* An error is generated if the checksum doesn't add up. */
	}
	
	RNS_INIT();						/* Initialize the logical I/O routine. */
	
	/* specify the creation data and the version of the conversion program. */
	shd=onsei_addr->onsei_omega;	/*ShdaChmHaj;*/
	for(cx=VerwVerL,si=(BYTE *)VerwVer;cx--;) 
	{
		*(integer_16 far *)shd=(*(integer_16 *)si); 
		shd+=2; 
		si+=2;
	}
	for(cx=VeraDateL, si=VerbDate; cx--; )
	{
		*shd++=(*si++);
	}
	
	/* Specify the creation data and the version of the dictionary. */
	for(cx=VeraVerL,si=Fdd_Header.Fdd_DVer;cx--;) {
		*shd++=(*si++); 
	}
	for(cx=VeraDateL,si=Fdd_Header.Fdd_DDate;cx--;) {
		*shd++=(*si++);
	}
	
	kkhstat=shoki;			/* Set the conversion state to the initial state. */
	PRON_INIT();
	
#if defined(O_DEBUG)
	DEBUG_INIT();			/* debug option setting */
#endif
}


/*========== ENV_TERM() ===========================
	Function: End of sentence voice conversion (For details, see the external specifications.)
  ===============================ShufShuuryousuru==*/
void ENV_TERM()
{
#if !defined(O_TALKONLY)
	integer_16 si,cx;
	LPBYTE addr;
	
	/* When the learning function is available, learn the segment up to the user-watching sentence. */
	if(KkhfMruKanou) {
		MRU_CSENT();
	}
	
	kkhstat=shoki;						/* Initialize. */
	while(RnsfFlushBuffer());			/* Write the all learning result into the external dictionary. */
	
	/********************************************************
	* Write the learning result of the grammar book into the dictionary.
	*
	* The part to be written
	*
	* Grammar book offsetFdd_Header.Fdd_IdicOfs
	* Start page number of the grammar bookFdd_Header.Fdd_IdicPageOfs+1
	* Number of pagesFdd_Header.Fdd_IdicNoPage
	********************************************************/
	si=Fdd_Header.Fdd_IdicPageOfs+1;
	cx=Fdd_Header.Fdd_IdicNoPage;
	addr=(LPBYTE)(FddHDR+Fdd_Header.Fdd_IdicOfs);
	
#if defined(C_SUN4)||defined(OS9)
	SwapHeader((LPBYTE)FddHDR);
#endif
	
	RtkfWrite(si,cx,addr);
#endif
	if (Fdd_EdicIndex != NULL) 
	{
		RtkfDealloc(&Fdd_EdicIndex);
	}
	RNS_DEALLOC();
}


/*========== PRON_INIT() =================================
	Function: Initialize all areas for sentence voice conversion.
  ====================================ShkfHnkShokikasuru==*/
void PRON_INIT()
{
  PRON_INIT2();
  JKN_INIT();				/* Clear the dictionary search table. */
  max_ceptr=0;				/* Initialize the length of the longest conversion input character string. */
}

/*========== PRON_INIT2() ==========================================================
	Function: When a conversion fails, initialize all the area for reconverting the 
				longest conversion character string.
  ==============================================================ShkfHnkShokikasuru==*/
void PRON_INIT2()
{
  OMEGA_INIT();				/* Initialize the output phonetic symbol area. */
  STACK_INIT();				/* Initialize the dictionary lookup stack. */
  FOLLOW_INIT(&Stz_CE);		/* Initialize the information of the current watching word. */
  FOLLOW_INIT(&Stz_PE);		/* Initialize the information of the preceding word. */
  SENT_INIT();				/* Initialize the sentence position information. */
#if !defined(O_TALKONLY)
  EDIC_MRU_INIT(); 			/* Initialize the learning state. */
#endif
}


/*========== display_user() ====================================
	Function: Specify the user name that locates at the fifth bytes in the dictionary for the output area.
  ==============================================================*/
void display_user()
{
  register BYTE *si;
  register integer_16 cx;
  BYTE al;
  LPBYTE di;

  si=(&Fdd_Header.Fdd_UserID[0]);
  di=onsei_addr->onsei_omega;
  for(cx=20;cx--;) {
    al=(*si++);
    al=((al & 0x01)<<7) + (al>>1);
    *di++=(al? al:0x20);
  }
  *di=0x00;
}


/*========== user_checksum() =====================
	Function: Look up the user name that locates at the fifth bytes in the dictionary.
	Value: ÅÅ0: Error
		ÅÅ1: Normal
  ================================================*/
BOOL
user_checksum()
{
  register BYTE *si;
  register integer_16 cx;
  BYTE al;
  WORD sum;

  si=(&Fdd_Header.Fdd_UserID[0]);
  for(sum=0,cx=20;cx--;) {
    al=(*si++);
    al=((al & 0x01)<<7) + (al>>1);
    sum+=(WORD)al;
  }
  /* return( sum==(*(WORD *)si) ? 1:0); */
  return( sum== ((*(si+1)<<8) + *si) ? 1:0);
}


#if defined(C_SUN4)||defined(OS9)
/*========== SwapHeader() =============================
	Function: Byte swap of the 16-bit data of the dictionary header
			SUN4, 8086 for 68000, and DEC are not required.
  =====================================================*/
void
SwapHeader(DIC_STRUCT* addr)
{
  swapval(&(addr->Fdd_ChrAttrOfs));		/* +23( 35) character code table offset */
  swapval(&(addr->Fdd_GrcdTblOfs));		/* +27( 39) dictionary grammar code table offset */
  swapval(&(addr->Fdd_IdicIndOfs));		/* +2B( 48) grammar book character number pointer offset */
  swapval(&(addr->Fdd_IdicPronOfs));		/* +2F( 47) grammar book pronunciation information offset */
  swapval(&(addr->Fdd_VecpOfs));			/* +33( 51) forward reference vector table offset */
  swapval(&(addr->Fdd_EdicIndOfs));		/* +37( 55) dictionary index offset */
  swapval(&(addr->Fdd_TdicIndOfs));		/* +3B( 59) Tan-kanji dictionary index offset */
  swapval(&(addr->Fdd_IdicOfs));			/* +3F( 63) internal dictionary offset */
  swapval(&(addr->Fdd_HdrSector));		/* +41( 65) number of header sectors on FD */
  swapval(&(addr->Fdd_HdrNg));			/* +43( 67) actual header length on FD */
  swapval(&(addr->Fdd_MaxNjsLen));		/* +45( 69) maximum length of grammar book header */
  swapval(&(addr->Fdd_MaxGjsInd));		/* +47( 71) dictionary index length */
  swapval(&(addr->Fdd_V5youOfs));			/* +4F( 79) 5-step verb conjunctive ending phonologic table offset */
  swapval(&(addr->Fdd_BnoTblOfs));		/* +53( 83) table offset for case determination */
  swapval(&(addr->Fdd_EdicKeyOfs));		/* +5A(91) dictionary index key offset */
  swapval(&(addr->Fdd_EdicIndSector));	/* +5E(95) Number of sectors of dictionary index  */
  swapval(&(addr->Fdd_IdicPageOfs));		/* +69(105) grammar book page offset */
  swapval(&(addr->Fdd_IdicPageSize));		/* +6B(107) page size (in sector units, 1024 bytes) */
  swapval(&(addr->Fdd_IdicNoPage));		/* +6D(109) total number of pages (number of indexes) */
  swapval(&(addr->Fdd_TdicPageOfs));		/* +71(113) Tan-kanji dictionary page offset */
  swapval(&(addr->Fdd_TdicPageSize));		/* +73(115) page size (in sector units, 1024 bytes) */
  swapval(&(addr->Fdd_TdicNoPage));		/* +75(117) total number of pages (number of indexes) */
  swapval(&(addr->Fdd_EdicPageOfs));	/* +79(121) external dictionary page offset */
  swapval(&(addr->Fdd_EdicPageSize));	/* +7B(123) page size (in sector units, 1024 bytes) */
  swapval(&(addr->Fdd_EdicNoPage));		/* +7D(125) total number of pages (number of indexes) */
}

void
swapval(BYTE* val)
{
  BYTE	c;
  c = val[0]; val[0] = val[1]; val[1] = c;
}

void
swapval2(BYTE* src, BYTE* dst)
{
  BYTE	c;
  dst[0] = src[1]; dst[1] = src[0];
}
#endif

/***************************** END OF ILE_ENVC.C *****************************/

