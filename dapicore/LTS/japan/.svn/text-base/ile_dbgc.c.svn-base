#if defined(O_DEBUG)
/*******************************************
	ILE_DBGC.C	updated at 22th May 1989
	Debug-related matter
 *******************************************/

#define		EXT		extern

//#include	<stdio.h> //moved to port.h for each platform MLT 01/24/06
#include "port.h"
#include	"onsei.h"
#include	"ile_dbgh.h"
#include	"ile_func.h"

static FILE		*dbgfp = NULL;

static const BYTE hex_tbl[16]={
	'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};

void DEBUG_INIT() {
	debug[ 1]=DISABLE;	/* STACK_PUSH	all elements */
	debug[ 2]=DISABLE;	/* STACK_PUSH	current element */
	debug[ 3]=DISABLE;	/* STC_POP		current element */
	debug[ 4]=DISABLE;	/* FOLLOW		Stz_CE and Stz_PE */
	debug[ 5]=DISABLE;	/* OMEGA9000	stack contents after xfer */
	debug[ 6]= ENABLE;	/* FOLLOW		Stz_CE */
}

void DEBUG_STR(name) BYTE *name; {
	FNX_PRINTF("%s",name);
	FNX_FPRINTF(dbgfp,"%s",name);
}

void DEBUG_PN(name) BYTE *name; {
	FNX_PRINTF("%s\n",name);
	FNX_FPRINTF(dbgfp,"%s\n",name);
}

void DEBUG_I(name,id,l) BYTE *name; register integer_16 *id,l; {
	integer_16 ll;
	integer_16 *id2;
	ll=l; id2=id;
	FNX_PRINTF("%s : ",name);
	for(;l--;){
		FNX_PRINTF("%d",*id++); if(l>0){ putchar(','); }
	}
	putchar('\n');

	l=ll; id=id2;
	FNX_FPRINTF(dbgfp,"%s : ",name);
	for(;l--;){
		FNX_FPRINTF(dbgfp,"%d",*id++); if(l>0){ FNX_FPUTC(',',dbgfp); }
	}
	FNX_FPUTC('\n',dbgfp);
}

void DEBUG_IB(name,id,l) BYTE *name; register BYTE *id; register integer_16 l; {
	integer_16 ll;
	BYTE *id2;
	ll=l; id2=id;
	FNX_PRINTF("%s : ",name);
	for(;l--;){
		FNX_PRINTF("%d",*id++); if(l>0){ putchar(','); }
	}
	putchar('\n');

	l=ll; id=id2;
	FNX_FPRINTF(dbgfp,"%s : ",name);
	for(;l--;){
		FNX_FPRINTF(dbgfp,"%d",*id++); if(l>0){ FNX_FPUTC(',',dbgfp); }
	}
	FNX_FPUTC('\n',dbgfp);
}

void DEBUG_A(name,id,l) BYTE *name; register BYTE *id; register integer_16 l; {
	int ll;
	BYTE *id2;
	ll=l; id2=id;
	FNX_PRINTF("%s : ",name);
	for(;l--;){ putchar(*id++); }
	putchar('\n');

	l=ll; id=id2;
	FNX_FPRINTF(dbgfp,"%s : ",name);
	for(;l--;){ FNX_FPUTC(*id++,dbgfp); }
	FNX_FPUTC('\n',dbgfp);
}

void DEBUG_H(name,id,l) BYTE *name; register BYTE *id; register integer_16 l; {
	int ll;
	BYTE *id2;
	integer_16 n;
	ll=l; id2=id;
	FNX_PRINTF("%s : ",name);
	for(;l--;){
		n=(*id++); putchar(hex_tbl[n/16]); putchar(hex_tbl[n%16]);
		putchar(' ');
	}
	putchar('\n');

	l=ll; id=id2;
	FNX_FPRINTF(dbgfp,"%s : ",name);
	for(;l--;){
		n=(*id++); FNX_FPUTC(hex_tbl[n/16],dbgfp); FNX_FPUTC(hex_tbl[n%16],dbgfp);
		FNX_FPUTC(' ',dbgfp);
	}
	FNX_FPUTC('\n',dbgfp);
}

void DEBUG_H2(var) register WORD var; {
	putchar(hex_tbl[(var>>12)& 0x000f]);
	putchar(hex_tbl[(var>> 8)& 0x000f]);
	putchar(hex_tbl[(var>> 4)& 0x000f]);
	putchar(hex_tbl[(var    )& 0x000f]);

	FNX_FPUTC(hex_tbl[(var>>12)& 0x000f],dbgfp);
	FNX_FPUTC(hex_tbl[(var>> 8)& 0x000f],dbgfp);
	FNX_FPUTC(hex_tbl[(var>> 4)& 0x000f],dbgfp);
	FNX_FPUTC(hex_tbl[(var    )& 0x000f],dbgfp);
}

void DEBUG_H1(var) BYTE var; {
	putchar(hex_tbl[var/16]); putchar(hex_tbl[var%16]);
	FNX_FPUTC(hex_tbl[var/16],dbgfp); FNX_FPUTC(hex_tbl[var%16],dbgfp);
}

void DEBUG_K1(id,l) register BYTE *id; register integer_16 l; {
	BYTE s[2]; int ll; BYTE *id2;
	ll=l; id2=id;
	for(;l--;){
		if(*id==0x20){
			putchar(*(id+1));
		}else{
			*s=(*id); *(s+1)=(*(id+1)); jis2sft(s);
			putchar(*s); putchar(*(s+1));
		}
		id+=2;
	}

	l=ll; id=id2;
	for(;l--;){
		if(*id==0x20){
			FNX_FPUTC(*(id+1),dbgfp);
		}else{
			*s=(*id); *(s+1)=(*(id+1)); jis2sft(s);
			FNX_FPUTC(*s,dbgfp); FNX_FPUTC(*(s+1),dbgfp);
		}
		id+=2;
	}
}

/*========== DEBUG_ELM() ===============================
	Function ：debug routine for Stz_CE,Stz_PE,ceptr,celen.
  ======================================================*/
void DEBUG_ELM(sw) integer_16 sw; {
	register integer_16 i,n;

	if(sw){
		DEBUG_STR("○ ");
	}else{
		DEBUG_STR("× ");
	}
	DEBUG_K1(&inert[ceptr*2],celen);

	switch(Stz_CE.stz_kind){
	case DICKIND_D:  DEBUG_STR(" ・数字・ "); break;
	case DICKIND_5Y: DEBUG_STR(" ・連用・ "); break;
	case DICKIND_I:  DEBUG_STR(" ・内部・ "); break;
	case DICKIND_E:  DEBUG_STR(" ・外部・ "); break;
	case DICKIND_T:  DEBUG_STR(" ・漢字・ "); break;
	case DICKIND_K:  DEBUG_STR(" ・仮名・ "); break;
	}

	if(Stz_CE.stz_mru & 0x40){ DEBUG_STR("〔放棄〕"); }

	n=Stz_CE.stz_nbno;
	for(i=0;n--;i++){
		FNX_PRINTF("%3d",Stz_CE.stz_bno[i]);
		if(n>0){ putchar(','); }

		FNX_FPRINTF(dbgfp,"%3d",Stz_CE.stz_bno[i]);
		if(n>0){ FNX_FPUTC(',',dbgfp); }
	}
	putchar('\n');
	FNX_FPUTC('\n',dbgfp);
}

/***************************** END OF ILE_DBGC.C *****************************/
#endif
