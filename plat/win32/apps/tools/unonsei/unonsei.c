#define		EXT		extern


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
#include "ile_idic.h"

#include <stdio.h>
#include <stdlib.h>

FILE *dict_file;
FILE *outfile;

int err_count=0;

DIC_STRUCT Fdd_Header;
LPBYTE Fdd_EdicIndex;

int main(int argc, char *argv[])
{
	char temps[100];
	int i,j,k;
	unsigned char *idicptr;
	unsigned char *tdicptr;
	unsigned char *sptr,*eptr,*tptr;
	unsigned int table,table1;
	int value;
	int length=0;
	int offset;
	int alen,plen;
	int al,ah;
	int f1,f2;
	char tot_graph[100];
	char new_graph[100];
	int tot_pos;
	unsigned char *accptr;
	IDIC_INDICES *mjsptr;
	char tan[2048];
	int page_no;
	int graph_lengths[100];
	int tan_ent_count=0;
	int idic_ent_count=0;
	int edic_graph_count=0;
	int edic_phon_count=0;
	int max_graph=0;
	int max_acc=0;
	int max_grcd=0;
	int max_pron=0;
	int grcd_len;

	err_count=0;

	dict_file=fopen(argv[1],"rb");

	if (dict_file==NULL)
	{
		fprintf(stderr,"could not open file %s\n",argv[1]);
		exit(1);
	}

	outfile=fopen(argv[2],"wb");
	if (outfile==NULL)
	{
		fprintf(stderr,"could not open output file %s\n",argv[2]);
		fclose(dict_file);
		exit(1);
	}

	memset(graph_lengths,0,100*sizeof(int));
	// read the dictionary header information
	fread(&Fdd_Header,1024,1,dict_file);
	
	//read many of the tables into memory;
	
	fread(&Fdd_Header.Fdd_Body,1024,Fdd_Header.Fdd_HdrSector-1,dict_file);

	// allocate the memory for the external indexes and keys.

	// this section may change based on the what we do with the 
	//    dictionary format after it is decompiled completely
//	Fdd_Header.Fdd_HdrSector;
//	Fdd_Header.Fdd_EdicIndSector;

	Fdd_EdicIndex=calloc(1024,Fdd_Header.Fdd_EdicIndSector);

	if (Fdd_EdicIndex==NULL)
	{
		fprintf(stderr,"out of memory\n");
		fclose(dict_file);
		exit(1);
	}

	// read the external dictionary header and key information into memory

	fread(Fdd_EdicIndex,1024,Fdd_Header.Fdd_EdicIndSector,dict_file);

	// print out the data some way.

	fprintf(outfile,"Version=");
	for (i=0;i<4;i++)
	{
		fprintf(outfile,"0x%02X ",Fdd_Header.Fdd_DVer[i]);
	}
	fprintf(outfile,"\r\n");

	memset(temps,0,100);
	fprintf(outfile,"Userid=",temps);
	for (i=0;i<22;i++)
	{
		fprintf(outfile,"0x%02X ",Fdd_Header.Fdd_UserID[i]);
	}
	fprintf(outfile,"\r\n");
	
	fprintf(outfile,"Date=%s\r\n",Fdd_Header.Fdd_DDate);

//	fprintf(outfile,"Fdd_ChrAttrOfs=%d\r\n",Fdd_Header.Fdd_ChrAttrOfs);

	fprintf(outfile,"Character Attributes Table\r\n");
	fprintf(outfile,"/* %4d 0x%02X */",0,0);
	for (i=1;i<128;i++)
	{
		fprintf(outfile,"\t0x%02X,",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_ChrAttrOfs+i-1]);
		if (i%8==0)
		{
			fprintf(outfile,"\r\n/* %4d 0x%02X */",i,i);
		}
	}
	fprintf(outfile,"\t0x%02X\r\n\r\n",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_ChrAttrOfs+i-1]);

//	fprintf(outfile,"Fdd_GrcdTblOfs=%d\r\n",Fdd_Header.Fdd_GrcdTblOfs);

	fprintf(outfile,"Grammer Codes table\tCTL\tBNO\tPNO\r\n");
	fprintf(outfile,"/* %4d 0x%04X \t*/",0,0);
	for (i=1;i<512;i++)
	{
		fprintf(outfile,"\t0x%02X,",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_GrcdTblOfs+i-1]);
		if (i%4==0)
		{
			fprintf(outfile,"\r\n/* %4d 0x%04X \t*/",i/4,i/4);
		}
	}
	fprintf(outfile,"\t0x%02X\r\n\r\n",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_GrcdTblOfs+i-1]);


	//Fdd_V5youOfs
//	fprintf(outfile,"Fdd_V5youOfs=%d\r\n",Fdd_Header.Fdd_V5youOfs);

	fprintf(outfile,"v5danyou offsets/data\r\n");
	fprintf(outfile,"/* %4d 0x%04X \t*/",0,0);
	for (i=1;i<Fdd_Header.Fdd_BnoTblOfs-Fdd_Header.Fdd_V5youOfs;i++)
	{
		fprintf(outfile,"\t0x%02X,",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_V5youOfs+i-1]);
		if (i%4==0)
		{
			fprintf(outfile,"\r\n/* %4d 0x%04X \t*/",i/4,i/4);
		}
	}
	fprintf(outfile,"\t0x%02X\r\n\r\n",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_V5youOfs+i-1]);

	fprintf(outfile,"Fdd_BnoPrefo=0x%02X\r\n",Fdd_Header.Fdd_BnoPrefo);
	fprintf(outfile,"Fdd_Bno5danLL=0x%02X\r\n",Fdd_Header.Fdd_Bno5danLL);
	fprintf(outfile,"Fdd_Bno5danUL=0x%02X\r\n",Fdd_Header.Fdd_Bno5danUL);
	fprintf(outfile,"Fdd_Bno5danYou=0x%02X\r\n",Fdd_Header.Fdd_Bno5danYou);
	fprintf(outfile,"Fdd_Bno1danMei=0x%02X\r\n",Fdd_Header.Fdd_Bno1danMei);
	fprintf(outfile,"Fdd_Bno1danYou=0x%02X\r\n",Fdd_Header.Fdd_Bno1danYou);
	fprintf(outfile,"Fdd_BnoSahen=0x%02X\r\n",Fdd_Header.Fdd_BnoSahen);
	fprintf(outfile,"Fdd_BnoSahenYou=0x%02X\r\n",Fdd_Header.Fdd_BnoSahenYou);
	fprintf(outfile,"Fdd_BnoHifu=0x%02X\r\n",Fdd_Header.Fdd_BnoHifu);
	fprintf(outfile,"Fdd_BnoAdv=0x%02X\r\n",Fdd_Header.Fdd_BnoAdv);
	fprintf(outfile,"Fdd_GrcdToku1=0x%02X\r\n",Fdd_Header.Fdd_GrcdToku1);
	fprintf(outfile,"Fdd_GrcdToku2=0x%02X\r\n",Fdd_Header.Fdd_GrcdToku2);
	fprintf(outfile,"Fdd_GrcdDigit=0x%02X\r\n",Fdd_Header.Fdd_GrcdDigit);
	fprintf(outfile,"Fdd_GrcdAdjv=0x%02X\r\n",Fdd_Header.Fdd_GrcdAdjv);
	fprintf(outfile,"Fdd_GrcdGai=0x%02X\r\n",Fdd_Header.Fdd_GrcdGai);
	fprintf(outfile,"Fdd_GrcdUsr=0x%02X\r\n",Fdd_Header.Fdd_GrcdUsr);
	fprintf(outfile,"Fdd_GrcdDai=0x%02X\r\n",Fdd_Header.Fdd_GrcdDai);
	fprintf(outfile,"Fdd_GrcdPropLL=0x%02X\r\n",Fdd_Header.Fdd_GrcdPropLL);
	fprintf(outfile,"Fdd_GrcdPropUL=0x%02X\r\n",Fdd_Header.Fdd_GrcdPropUL);
	fprintf(outfile,"Fdd_PropMeaning=0x%02X\r\n",Fdd_Header.Fdd_PropMeaning);
	fprintf(outfile,"Fdd_GrcdSufLL=0x%02X\r\n",Fdd_Header.Fdd_GrcdSufLL);
	fprintf(outfile,"Fdd_GrcdSufUL=0x%02X\r\n",Fdd_Header.Fdd_GrcdSufUL);
	fprintf(outfile,"Fdd_GrcdNum1=0x%02X\r\n",Fdd_Header.Fdd_GrcdNum1);
	fprintf(outfile,"Fdd_GrcdNum2=0x%02X\r\n",Fdd_Header.Fdd_GrcdNum2);
	
	//Fdd_BnoTblOfs
//	fprintf(outfile,"Fdd_BnoTblOfs=%d\r\n",Fdd_Header.Fdd_BnoTblOfs);

	fprintf(outfile,"\r\nBack end number offsets (look like numbers used/ not offsets)\r\n");
	fprintf(outfile,"/* %4d 0x%04X \t*/",0,0);
	for (i=1;i<Fdd_Header.Fdd_MatrixOfs-Fdd_Header.Fdd_BnoTblOfs;i++)
	{
		fprintf(outfile,"\t0x%02X,",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_BnoTblOfs+i-1]);
		if (i%4==0)
		{
			fprintf(outfile,"\r\n/* %4d 0x%04X \t*/",i/4,i/4);
		}
	}
	fprintf(outfile,"\t0x%02X\r\n\r\n",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_BnoTblOfs+i-1]);

//	fprintf(outfile,"Fdd_MatrixOfs is not used\r\n");

//	fprintf(outfile,"Fdd_HdrNg=%d total header bytes, not used anywhere\r\n",Fdd_Header.Fdd_HdrNg);

	//fprintf(outfile,"Fdd_IdicIndOfs=%d\r\n",Fdd_Header.Fdd_IdicIndOfs);
//	fprintf(outfile,"internal dictaionry indicies not displayed, dict data is below\r\n");
#if 0
	fprintf(outfile,"/* %4d 0x%04X */",0,0);
	for (i=1;i<16;i++)
	{
		mjsptr = (IDIC_INDICES *)(&(((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_IdicIndOfs])
			+ sizeof(IDIC_INDICES)*(i-1));

		fprintf(outfile,"\t{0x%04X,\t0x%04X},",mjsptr->idic_len_ptr2+(mjsptr->idic_len_ptr1<<8),mjsptr->idic_index_dummy);
		if (i%2==0)
		{
			fprintf(outfile,"\r\n/* %4d 0x%04X */",i,i);
		}
	}
	mjsptr = (IDIC_INDICES *)(&(((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_IdicIndOfs])
		+ sizeof(IDIC_INDICES)*(i-1));
	fprintf(outfile,"\t{0x%04X,\t0x%04X}\r\n\r\n",mjsptr->idic_len_ptr2+(mjsptr->idic_len_ptr1<<8),mjsptr->idic_index_dummy);
#endif

		

//	fprintf(outfile,"Internal dictiaonry pronunciations/offsets not displayed, it is displayed with the word entry\r\n");
//	fprintf(outfile,"Fdd_IdicPronOfs=%d\r\n",Fdd_Header.Fdd_IdicPronOfs);
#if 0
	fprintf(outfile,"/* %4d 0x%04X */",0,0);
	for (i=1;i<1023;i++)
	{
		fprintf(outfile,"\t0x%02X,",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_IdicPronOfs+i-1]);
		if (i%8==0)
		{
			fprintf(outfile,"\r\n/* %4d 0x%04X */",i,i);
		}
	}
	fprintf(outfile,"\t0x%02X\r\n\r\n",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_IdicPronOfs+i-1]);

#endif

	fprintf(outfile,"Forward lookup vector table offsets\r\n");
//	fprintf(outfile,"Fdd_VecpOfs=%d\r\n",Fdd_Header.Fdd_VecpOfs);
	fprintf(outfile,"/* %4d 0x%04X pno=%3d */",0,0,1);
	for (i=1;i<4000;i++)
	{
		fprintf(outfile," %02X",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_VecpOfs+i-1]);
		if (i%20==0)
		{
			fprintf(outfile,"\r\n/* %4d 0x%04X pno=%3d */",i,i,i/20+1);
		}
	}
	fprintf(outfile," %02X\r\n\r\n",((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_VecpOfs+i-1]);


	fprintf(outfile,"Internal dictionary\r\n");
	
	for (i=0;i<((Fdd_Header.Fdd_IdicPronOfs-Fdd_Header.Fdd_IdicIndOfs)/sizeof(IDIC_INDICES))-1;i++)
	{
		mjsptr = (IDIC_INDICES *)(&(((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_IdicIndOfs])
			+ sizeof(IDIC_INDICES)*(i));
		sptr=((unsigned char *)&Fdd_Header)+Fdd_Header.Fdd_IdicOfs+mjsptr->idic_len_ptr2+(mjsptr->idic_len_ptr1<<8);
		mjsptr = (IDIC_INDICES *)(&(((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_IdicIndOfs])
			+ sizeof(IDIC_INDICES)*(i+1));
		eptr=((unsigned char *)&Fdd_Header)+Fdd_Header.Fdd_IdicOfs+mjsptr->idic_len_ptr2+(mjsptr->idic_len_ptr1<<8);
		length=(i+1)*2;
		while (sptr< eptr)
		{
			tptr=sptr;
			//fprintf(outfile,"graphemes:");
			graph_lengths[length]++;
			for (j=0;j<length;j++)
			{
				tot_graph[j]=*tptr++;
				//fprintf(outfile,"%c",*tptr++);
			}
			tot_graph[j]='\0';
			tot_graph[j+1]='\0';
			//fprintf(outfile,"%s",tot_graph);
			for (j=0;j<length;j+=2)
			{
				new_graph[j]=tot_graph[j];
				new_graph[j+1]=tot_graph[j+1];
			}
			new_graph[j]='\0';
			new_graph[j+1]='\0';
			for (j=0;j<length;j++)
			{
				new_graph[j]|=0x80;
			}
			//e2u(new_graph);
			fprintf(outfile,"%s",new_graph);
			fprintf(outfile,"\tctl=0x%02X",*tptr++);		/* control information */
			fprintf(outfile,"\tf2=0x%02X",*tptr++);		/* flag 2 */
			fprintf(outfile,"\tbno=0x%02X",*tptr++);		/* end number */
			fprintf(outfile,"\tpno=0x%02X",*tptr++);		/* front end reference vector number: offset is 20 times the amount */
			offset = *tptr++;
			offset += ((*tptr)<<8);
			tptr++;
			//fprintf(outfile,"  pron_offset=0x%04X",offset);
			fprintf(outfile,"\tmru=0x%02X",*tptr++);		/* training information */

			accptr = (&((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_IdicPronOfs]) + offset;
			plen=*accptr++;
			alen=plen>>4;
			plen&=0x0f;
			fprintf(outfile,"\tacc:");
			if (alen==0)
			{
				fprintf(outfile,"none");
			}
			for (j=0;j<alen;j++)
			{
				al=(*accptr++);
				ah=al/16; 
				al=al%16;			
				fprintf(outfile,"0x%01X-0x%01X ",ah,al);
			}
			fprintf(outfile,"\tpron:");
			if (plen==0)
			{
				fprintf(outfile,"mkh");
				
			}
			else
			{
				memset(temps,' ',100);
				for (j=0;j<plen;j++)
				{
					value=*accptr++;
					code_to_hardchar2(value,0,&temps[j*4]);
					fprintf(outfile,"0x%02X ",value);
				}
				temps[j*4]='\0';
				fprintf(outfile,"phon:%s",temps);
			}
			fprintf(outfile,"\r\n");
			idic_ent_count++;
			sptr+=length+SIZE_IDIC;
		}
	}
	fprintf(stderr,"idic_ent_count=%d\n",idic_ent_count);


#if 0
	fprintf(outfile,"Fdd_TdicIndOfs=%d\r\n",Fdd_Header.Fdd_TdicIndOfs);
	fprintf(outfile,"/* %4d 0x%04X */",0,0);
	for (i=1;i<Fdd_Header.Fdd_TdicNoPage*2;i+=2)
	{
		//bytes in this table are bigendian
		table=((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_TdicIndOfs+i-1];
		table1=((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_TdicIndOfs+i];
		value=(table<<8)|(table1);
		
		fprintf(outfile,"\t0x%04X (%c%c),",value,table,table1);
		if ((i+1)%8==0)
		{
			fprintf(outfile,"\r\n/* %4d 0x%04X */",i/2,i/2);
		}
	}
	table=((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_TdicIndOfs+i-1];
	table1=((unsigned char *)&Fdd_Header)[Fdd_Header.Fdd_TdicIndOfs+i];
	value=(table<<8)|(table1);
	fprintf(outfile,"\t0x%04X (%c%c)\r\n\r\n",value,table,table1);
#endif

	fprintf(outfile,"\r\nTan-Kanji\r\n");
	for (i=1;i<(Fdd_Header.Fdd_TdicNoPage+1);i++)
	{
		//bytes in this table are bigendian
		fseek(dict_file,(Fdd_Header.Fdd_TdicPageOfs)*1024+1024*(i-1),SEEK_SET);
		fread(tan,1024,1,dict_file);
		tdicptr=&tan[0];
//		fprintf(outfile,"tan page nubmer=%d\r\n",i);
		while (*tdicptr)
		{
			tptr=tdicptr;
//			fprintf(outfile,"graph:");
			length=2;
			for (j=0;j<length;j++)
			{
				tot_graph[j]=*tptr++;
				//fprintf(outfile,"%c",*tptr++);
			}
			tot_graph[j]='\0';
			tot_graph[j+1]='\0';
			//fprintf(outfile,"%s",tot_graph);
			for (j=0;j<length;j+=2)
			{
				new_graph[j]=tot_graph[j];
				new_graph[j+1]=tot_graph[j+1];
			}
			new_graph[j]='\0';
			new_graph[j+1]='\0';
			for (j=0;j<length;j++)
			{
				new_graph[j]|=0x80;
			}
			//e2u(new_graph);
			fprintf(outfile,"%s",new_graph);
			graph_lengths[2]++;
			length=*tptr++;
			fprintf(outfile,"\ttype=0x%02X",*tptr++);

			plen=*tptr++;
			alen=plen>>4;
			plen&=0x0f;
			fprintf(outfile,"\tacc:");
			if (alen==0)
			{
				fprintf(outfile,"none");
			}
			for (j=0;j<alen;j++)
			{
				al=(*tptr++);
				ah=al/16; 
				al=al%16;			
				fprintf(outfile,"0x%01X-0x%01X ",ah,al);
			}
			fprintf(outfile,"\tpron:");
			if (plen==0)
			{
				fprintf(outfile,"mkh");
				
			}
			else
			{
				memset(temps,' ',100);
				for (j=0;j<plen;j++)
				{
					value=*tptr++;
					code_to_hardchar2(value,0,&temps[j*4]);
					fprintf(outfile,"0x%02X ",value);
				}
				temps[j*4]='\0';
				fprintf(outfile,"phon:%s",temps);
			}
			tan_ent_count++;
			fprintf(outfile,"\r\n");
			tdicptr+=(length+3);
		}
			
	}

	fprintf(stderr,"tan_ent_count=%d\n",tan_ent_count);
	

//	fprintf(outfile,"Fdd_IdicOfs=%d\r\n",Fdd_Header.Fdd_IdicOfs);

//	fprintf(outfile,"Fdd_EdicIndOfs=%d not displayed \r\n",Fdd_Header.Fdd_EdicIndOfs);
#if 0
	fprintf(outfile,"/* %4d 0x%04X */",0,0);
	Fdd_Header.Fdd_EdicKeyOfs-=Fdd_Header.Fdd_EdicIndOfs;
	for (i=1;i<=Fdd_Header.Fdd_EdicNoPage;i++)
	{
		value=(Fdd_EdicIndex[(i-1)*3]) + ((Fdd_EdicIndex[(i-1)*3+1])<<8);
		length=Fdd_EdicIndex[(i-1)*3+2];
		fprintf(outfile,"\toffset=0x%04X, length=0x%02X",value,length);
		fprintf(outfile,"key data:");
		for (j=0;j<length;j++)
		{
			fprintf(outfile,"%c",Fdd_EdicIndex[Fdd_Header.Fdd_EdicKeyOfs+value+j]);
		}
		if (i==Fdd_Header.Fdd_EdicNoPage)
		{
			fprintf(outfile,"\r\n");
		}
		else
		{
			fprintf(outfile,"\r\n/* %4d 0x%04X */",i,i);
		}
	}
#endif

	fseek(dict_file,Fdd_Header.Fdd_EdicPageOfs*1024,SEEK_SET);
	fprintf(outfile,"\r\nExternal Dictioanry\r\n");
	for (i=1;i<=Fdd_Header.Fdd_EdicNoPage;i++)
	{
		fread(tan,1024,1,dict_file);
		fprintf(outfile,"edic page number=%d\r\n",i);
		sptr=&tan[0];
		memset(tot_graph,0,100);
		tot_pos=0;
		while (1){
			// flag 1
			tptr=sptr;			
			f1=*tptr++;
			if ((f1&0x1F)==0x1F)
				break;
//			fprintf(outfile,"%2d",f1&0x1F);
			// length
			length=*tptr++;
//			fprintf(outfile,"\tgraph:");
			tot_pos=(f1&0x1F);
			while(((*tptr)&0x80)==0)
			{
				tot_graph[tot_pos]=*tptr++;
				tot_pos++;
			}
			tot_graph[tot_pos]='\0';
			tot_graph[tot_pos+1]='\0';
			graph_lengths[tot_pos]++;
			//fprintf(outfile,"%s",tot_graph);

			for (j=0;j<tot_pos;j+=2)
			{
				new_graph[j]=tot_graph[j];
				new_graph[j+1]=tot_graph[j+1];
			}
			new_graph[j]='\0';
			new_graph[j+1]='\0';
			for (j=0;j<tot_pos;j++)
			{
				new_graph[j]|=0x80;
			}
			//e2u(new_graph);
			if (tot_pos>max_graph)
				max_graph=tot_pos;
			fprintf(outfile,"%s",new_graph);
			edic_graph_count++;
			k=0;
			while (tptr<(sptr+length+2))
			{
				f2=*tptr++;
				k++;
				if (k>1)
				{
					fprintf(outfile,"\r\n\t\t");
				}
				fprintf(outfile,"\tflag2=0x%02X",f2);
				fprintf(outfile,"\tmru=0x%02X",*tptr++);
				fprintf(outfile,"\tGrcd=");
				grcd_len=0;

				if (((*tptr) & 0x80)==0)
				{
					fprintf(outfile,"none");
				}
				else
				{
					while ((*tptr) & 0x80)
					{	
						grcd_len++;
						al=*tptr++;
						fprintf(outfile,"0x%02X ",al&0x7F);
					}
				}
				if (grcd_len>max_grcd)
					max_grcd=grcd_len;
				plen=*tptr++;
				alen=plen>>4;
				plen&=0x0f;
				fprintf(outfile,"\tacc:");
				if (alen==0)
				{
					fprintf(outfile,"none");
				}
				for (j=0;j<alen;j++)
				{
					al=(*tptr++);
					ah=al/16; 
					al=al%16;			
					fprintf(outfile,"0x%01X-0x%01X ",ah,al);
				}
				if (alen>max_acc)
					max_acc=alen;
				fprintf(outfile,"\tpron:");
				if (plen==0)
				{
					fprintf(outfile,"mkh");
					
				}
				else
				{
					memset(temps,' ',100);
					for (j=0;j<plen;j++)
					{
						value=*tptr++;
						code_to_hardchar2(value,0,&temps[j*4]);
						fprintf(outfile,"0x%02X ",value);
					}
					temps[j*4]='\0';
					fprintf(outfile,"phon:%s",temps);
				}
				if (plen>max_pron)
					max_pron=plen;
				edic_phon_count++;
			}
			fprintf(outfile,"\r\n");

			sptr+=(length+2);

		}


	}
	fprintf(stderr,"edic_graph_count=%d edic_phon_count=%d\n",
		edic_graph_count,edic_phon_count);

	fprintf(stderr,"max_graph=%d\n",max_graph);
	fprintf(stderr,"max_grcd=%d\n",max_grcd);
	fprintf(stderr,"max_acc=%d\n",max_acc);
	fprintf(stderr,"max_pron=%d\n",max_pron);
	fprintf(stderr,"error_count=%d\n",err_count);

	fclose(dict_file);

	fclose(outfile);

	free(Fdd_EdicIndex);

}