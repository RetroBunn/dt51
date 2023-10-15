#define		EXT		extern


#include <windows.h>
#include <windowsx.h> 

#include "resource.h"
#include "gui.h"

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


#define MAX_EDIC_PRONS	30

FILE *dict_file;
FILE *outfile;
FILE *infile;

int err_count=0;

DIC_STRUCT Fdd_Header;
LPBYTE Fdd_EdicIndex;

int line_num=0;

struct idic_dict_s
{
	unsigned char graph[16];
	IDIC_DATA data;
	char acc_length;
	char pron_length;
	unsigned char acc[8];
	unsigned char pron[16];
	int pron_offset_index;
};

typedef struct idic_dict_s idic_dict_t;

struct idic_pron_s
{
	int offset;
	int length;
	unsigned char accpron[40];
};

typedef struct idic_pron_s idic_pron_t;


struct tan_dict_s
{
	unsigned char graph[4];
	unsigned char type;
	char acc_length;
	char pron_length;
	unsigned char acc[16];
	unsigned char pron[16];
};


typedef struct tan_dict_s tan_dict_t;

struct edic_data_s
{
	unsigned char f2;
	unsigned char mru;
	unsigned char grcd[10];
	char acc_length;
	char pron_length;
	char grcd_length;
	unsigned char acc[8];
	unsigned char pron[16];
};

typedef struct edic_data_s edic_data_t;

struct edic_dict_s
{
	unsigned char graph[26];
	char num_prons;
	char max_prons;
	edic_data_t *data;
};


typedef struct edic_dict_s edic_dict_t;


idic_pron_t *idic_pron_p;
int idic_num_prons;
int idic_max_prons;
int idic_total_pron_length=0;


void get_line(char *line,char *search_string)
{
	line_num++;
	fgets(line,999,infile);
	if (strncmp(line,search_string,strlen(search_string))!=0)
	{
		//fprintf(stderr,"error in input line %d\n",line_num);
		fclose(infile);
		fclose(dict_file);
		exit(0);
	}
}

int make_acc_pron(char *out, char acc_len, char *accptr, char plen, char *pronptr)
{
	unsigned char value=0;
	int length=0;
	int i;

	if (out==NULL)
	{
		return(-1);
	}
	value=(acc_len<<4) + (plen & 0x0f);
	out[length++]=value;

	for (i=0;i<acc_len;i++)
	{
		out[length++]=accptr[i];
	}
	for (i=0;i<plen;i++)
	{
		out[length++]=pronptr[i];
	}
	out[length]='\0';
	return(length);
}


int add_pron_to_idic(char acc_len, char *accptr, char plen, char *pronptr)
{
	int i;
	int length;
	unsigned char cur_acc_pron[50];
	length=0;
	if (idic_max_prons==0)
	{
		idic_max_prons=512;
		idic_pron_p=malloc(sizeof(idic_pron_t)*idic_max_prons);
	}
	if (idic_num_prons>=idic_max_prons)
	{
		idic_max_prons*=2;
		idic_pron_p=realloc(idic_pron_p,sizeof(idic_pron_t)*idic_max_prons);
	}
	length=make_acc_pron(cur_acc_pron,acc_len,accptr,plen,pronptr);
	for (i=0;i<idic_max_prons;i++)
	{
		if (memcmp(cur_acc_pron,idic_pron_p[i].accpron,length)==0)
		{
			return(i);
		}
	}

	memcpy(idic_pron_p[idic_num_prons].accpron,cur_acc_pron,length);
	idic_pron_p[idic_num_prons].length=length;
	idic_pron_p[idic_num_prons].offset=0;
	idic_num_prons++;
	idic_total_pron_length+=length;
	return(idic_num_prons-1);
}

int build_idic_entry(unsigned char *out,idic_dict_t *in)
{
	int i;
	int length=0;

	if (out==NULL)
	{
		return(-1);
	}
	i=0;
	while (in->graph[i])
	{
		out[length++]=in->graph[i++];
	}
	memcpy(&out[length],&(in->data),sizeof(IDIC_DATA));
	length+=7;
	return(length);
}

int build_tdic_entry(char *out, tan_dict_t *in)
{
	int pos=0;
	int length=0;

	out[0]=in->graph[0];
	out[1]=in->graph[1];
	out[3]=in->type;
	
	length=make_acc_pron(&out[4],in->acc_length,in->acc,
		in->pron_length,in->pron);
	out[2]=length+1;
	return(length+4);
}

int build_edic_entry(char *prev, char *out, char *out2, edic_dict_t *in)
{
	int pos=0;
	int length=0;
	int pos2=0;
	int i,j;
	int graph_len;
	int accpron=0;
	int save_pos2, save_pos;
	int same_len=0;

	graph_len=strlen(in->graph);

	while (prev[same_len]==in->graph[same_len])
		same_len++;

	out2[pos2++]=0xE0;
	out[pos++]=0xE0+same_len;

	//save the positions for the lengths.
	save_pos2=pos2; 
	save_pos=pos;
	pos2++;
	pos++;


	strcpy(&out2[pos2],in->graph);
	strcpy(&out[pos],&in->graph[same_len]);

	pos2+=graph_len;
	pos+=graph_len-same_len;

	for (i=0;i<in->num_prons;i++)
	{	
		out2[pos2++]=in->data[i].f2;
		out[pos++]=in->data[i].f2;

		out2[pos2++]=in->data[i].mru;
		out[pos++]=in->data[i].mru;

		for (j=0;j<in->data[i].grcd_length;j++)
		{
			out2[pos2++]=((in->data[i].grcd[j])|0x80);
			out[pos++]=((in->data[i].grcd[j])|0x80);
		}
		accpron=((in->data[i].acc_length&0x0f)<<4)+(in->data[i].pron_length&0x0f);
		out2[pos2++]=accpron;
		out[pos++]=accpron;
		for (j=0;j<in->data[i].acc_length;j++)
		{
			out2[pos2++]=((in->data[i].acc[j]));
			out[pos++]=((in->data[i].acc[j]));
		}
		for (j=0;j<in->data[i].pron_length;j++)
		{
			out2[pos2++]=((in->data[i].pron[j]));
			out[pos++]=((in->data[i].pron[j]));
		}
	}
	out2[save_pos2]=pos2-2;
	out[save_pos]=pos-2;
	return(pos+(pos2<<16));

}

/*FUNCTION_HEADER************************************************
* NAME:		;RenameOldDictionary
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
BOOL RenameOldDictionary( char *szOutFile )
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	BOOL bRet = TRUE;
	TCHAR tsNewFile[MAX_PATH*2];
	TCHAR *pcTmp, tsFilename[MAX_PATH*2], tsCnt[25];
	int cnt = 0;
	char szTemp[MAX_PATH];

	mbstowcs( tsFilename, szOutFile, MAX_PATH*2 );
	if( (pcTmp = wcsstr( tsFilename, _T(".dic") )) != NULL )
	{
		wcscpy( pcTmp, _T("*.dic") );
		hFind = FindFirstFile( tsFilename, &fd );
		while( hFind != INVALID_HANDLE_VALUE && bRet )
		{
			cnt++;
			bRet = FindNextFile( hFind, &fd );
		}
		FindClose(hFind);

		mbstowcs( tsNewFile, szOutFile, MAX_PATH*2 );
		_itow( cnt, tsCnt, 10 );
		if( (pcTmp = wcsstr( tsNewFile, _T(".dic") )) != NULL )
		{
			wcscpy( pcTmp, tsCnt );
			wcscat( tsNewFile, _T(".dic") );
			mbstowcs( tsFilename, szOutFile, MAX_PATH*2 );
			wcstombs( szTemp, tsNewFile, MAX_PATH );
			if( CopyFile( tsFilename, tsNewFile, FALSE ))
				return(TRUE);
		}
	}
	return(FALSE);
} /* end: RenameOldDictionary */

/*FUNCTION_HEADER************************************************
* NAME:		;GetNewDictionaryName
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
BOOL GetNewDictionaryName( char *szFilename )
{
	SYSTEMTIME st;
	char *pcTmp, szMonth[3], szDay[3], szYear[5];

	if( (pcTmp = strstr( szFilename, SINGLE_SPACE )) != NULL || (pcTmp = strrchr( szFilename, '.' )) != NULL )
	{
		GetLocalTime( &st );

		*pcTmp = 0;

		ltoa( st.wMonth, szMonth, 10 );
		ltoa( st.wDay, szDay, 10 );
		ltoa( st.wYear, szYear, 10 );

		strcat( szFilename, " " );
		strcat( szFilename, szMonth );
		strcat( szFilename, "-" );
		strcat( szFilename, szDay );
		strcat( szFilename, "-" );
		strcat( szFilename, szYear );

		strcat( szFilename, ".txt" );

		return(TRUE);
	}
	return(FALSE);

} /* end: GetNewDictionaryName */

/*FUNCTION_HEADER************************************************
* NAME:		;RemoveDoneField
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void RemoveDoneField( char *line, int nDict )
{
	char *pcTmp1, *pcTmp2;

	if( (pcTmp1 = strstr( line, "done=" )) == NULL )
	{
		return;
	}
	
	if( nDict == IDD_EDIT_IDIC )
	{
		if( (pcTmp2 = strstr( line, "ctl=" )) == NULL )
		{
			return;
		}
	}
	else
	if( nDict == IDD_EDIT_TDIC )
	{
		if( (pcTmp2 = strstr( line, "type=" )) == NULL )
		{
			return;
		}
	}
	else
	if( nDict == IDD_EDIT_EDIC )
	{
		if( (pcTmp2 = strstr( line, "flag2=" )) == NULL )
		{
			return;
		}
	}

	memmove( &pcTmp1[0], &pcTmp2[0], strlen(line)-((pcTmp2-pcTmp1)-1) );
	return(TRUE);

} /* end: RemoveDoneField */

/*FUNCTION_HEADER************************************************
* NAME:		;Myreonsei
* DESC:		
* IN:			
* OUT:		
* RETURN:	
* NOTES:		
*END_HEADER*****************************************************/
void Myreonsei( HWND hDlg, HWND hList )
{
	TCHAR tsFilename[MAX_PATH*2];
	char *pcTmp, szFilename[MAX_PATH+1], szOutfile[MAX_PATH+1], szInfile[MAX_PATH+1];

	char temps[100];
	int i,j;
	unsigned char *sptr,*eptr;
	int length=0;
	unsigned char tot_graph[300];
	unsigned char new_graph[300];
	char tan[2048];
	int graph_lengths[100];
	unsigned char line[1000];
	int cur_file_offset=0;
	unsigned char char_attrs[150];
	int char_attr_len=0;
	unsigned char grammar_codes[550];
	int grammar_codes_len=0;
	unsigned char v5danyou[100];
	int v5danyou_len=0;
	unsigned char bno_table[1000];
	int bno_table_len=0;
	unsigned char vector_table[6000];
	int vector_table_len=0;

	idic_dict_t *idic_dict_p;
	int max_idic_ent=1024;
	int idic_ent_count=0;
	IDIC_INDICES idic_indices[16];
	int max_idic_graph_len=0;
	int graph_length=0;
	int acc_length=0;
	int pron_length=0;

	tan_dict_t *tan_dict_p;
	int max_tan_ent=1024;
	int tan_ent_count=0;

	edic_dict_t *edic_dict_p;
	int max_edic_ent=8192;
	int edic_ent_count=0;
	int pron_count=0;
	int edic_phon_count=0;
	int grcd_length=0;

	int cur_writing_pos=0;

	unsigned char *Fdd_char_header;

	unsigned char *edic_index;
	int edic_max_index=0;
	int edic_index_pos=0;
	int edic_index_count=0;
	unsigned char *edic_keys;
	int edic_keys_pos=0;
	int edic_num_keys=0;
	int edic_max_keys=0;
	unsigned char *edic_data;
	int edic_max_data=0;
	int edic_data_pos=0;
	int edic_page_pos=0;

	unsigned char prev_ent[50];
	int length2;

	unsigned char *idic_prons;
	int idic_prons_cur_pos=0;
	unsigned char *idic_data;
	int max_idic_data=0;
	int cur_idic_pos=0;
	int cur_index=0;

	unsigned char *tdic_keys;
	int tdic_keys_pos=0;
	int tdic_num_keys=0;
	int tdic_max_keys=0;
	unsigned char *tdic_data;
	int tdic_max_data=0;
	int tdic_data_pos=0;
	int tdic_page_pos=0;

	int err_msg = 0;

	err_count=0;
	idic_num_prons=0;
	idic_max_prons=0;

	if( SendDlgItemMessage( hDlg, IDC_EDIT1, WM_GETTEXT, MAX_PATH, (LPARAM)tsFilename ))
	{
		wcstombs( szFilename, tsFilename, MAX_PATH );
		strcpy( szOutfile, szFilename );
		GetNewDictionaryName( szOutfile );
		if( (pcTmp = strstr( szOutfile, ".txt" )) != NULL )
		{
			strcpy( pcTmp, ".dic" );
			if( (dict_file = fopen( szOutfile, "wb" )) != NULL )
			{
				strcpy( szInfile, szFilename );
				if( (pcTmp = strstr( szInfile, ".txt" )) != NULL )
				{
					if( (infile = fopen( szInfile, "rb" )) == NULL )
					{
						fclose(dict_file);
						MessageBox( hDlg, _T("The text input file could not be opened.   "), _T("ERROR..."), MB_OK | MB_ICONSTOP );
						return;
					}
				}
			}
			else
			{
				MessageBox( hDlg, _T("The output file could not be opened.   "), _T("ERROR..."), MB_OK | MB_ICONSTOP );
				return;
			}
		}

		SetDlgItemText( hDlg, IDC_STATIC_RED, _T("Recompiling dictionary...") );

		// read the dictionary into memory...
		memset(&Fdd_Header,0,sizeof(DIC_STRUCT));
	
		memset(graph_lengths,0,100*sizeof(int));
	
		Fdd_char_header=&Fdd_Header;
	
		// print out the data some way.
		get_line(line,"Version=");
		sptr=line+8;
		for (i=0;i<4;i++)
		{
			Fdd_Header.Fdd_DVer[i]=(unsigned char)strtol(sptr,&eptr,16);
			sptr=eptr;
		}
		
		memset(temps,0,100);
		get_line(line,"Userid=");
		sptr=line+7;
		for (i=0;i<22;i++)
		{
			Fdd_Header.Fdd_UserID[i]=strtol(sptr,&eptr,16);
			sptr=eptr;
		}
	
		get_line(line,"Date=");
		strncpy(Fdd_Header.Fdd_DDate,line+5,6);
		
		get_line(line,"Character Attributes Table");
		i=0;
		line_num++;
		fgets(line,999,infile);
		while (line[0]=='/')
		{
			sptr=line+16;
			for (j=0;j<8;j++,i++)
			{
				if (!sptr[0] && sptr[0]>=0x20)
					break;
				char_attrs[char_attr_len++]=(unsigned char)strtol(sptr,&eptr,16);
				//skip the ,
				eptr++;
				sptr=eptr;
			}
			line_num++;
			fgets(line,999,infile);
		}
	
		get_line(line,"Grammer Codes table");
		i=0;
		line_num++;
		fgets(line,999,infile);
		while (line[0]=='/')
		{
			sptr=line+19;
			for (j=0;j<4;j++,i++)
			{
				if (!sptr[0])
					break;
				grammar_codes[grammar_codes_len++]=(unsigned char)strtol(sptr,&eptr,16);
				//skip the ,
				eptr++;
				sptr=eptr;
			}
			line_num++;
			fgets(line,999,infile);
		}
	
		get_line(line,"v5danyou offsets/data");
		i=0;
		line_num++;
		fgets(line,999,infile);
		while (line[0]=='/')
		{
			sptr=line+19;
			for (j=0;j<4;j++,i++)
			{
				if (!sptr[0])
					break;
				v5danyou[v5danyou_len++]=(unsigned char)strtol(sptr,&eptr,16);
				//skip the ,
				eptr++;
				sptr=eptr;
			}
			line_num++;
			fgets(line,999,infile);
		}
	
		get_line(line,"Fdd_BnoPrefo=");
		sptr=line+13;
		Fdd_Header.Fdd_BnoPrefo=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_Bno5danLL=");
		sptr=line+14;
		Fdd_Header.Fdd_Bno5danLL=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_Bno5danUL=");
		sptr=line+14;
		Fdd_Header.Fdd_Bno5danUL=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_Bno5danYou=");
		sptr=line+15;
		Fdd_Header.Fdd_Bno5danYou=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_Bno1danMei=");
		sptr=line+15;
		Fdd_Header.Fdd_Bno1danMei=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_Bno1danYou=");
		sptr=line+15;
		Fdd_Header.Fdd_Bno1danYou=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_BnoSahen=");
		sptr=line+13;
		Fdd_Header.Fdd_BnoSahen=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_BnoSahenYou=");
		sptr=line+16;
		Fdd_Header.Fdd_BnoSahenYou=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_BnoHifu=");
		sptr=line+12;
		Fdd_Header.Fdd_BnoHifu=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_BnoAdv=");
		sptr=line+11;
		Fdd_Header.Fdd_BnoAdv=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdToku1=");
		sptr=line+14;
		Fdd_Header.Fdd_GrcdToku1=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdToku2=");
		sptr=line+14;
		Fdd_Header.Fdd_GrcdToku2=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdDigit=");
		sptr=line+14;
		Fdd_Header.Fdd_GrcdDigit=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdAdjv=");
		sptr=line+13;
		Fdd_Header.Fdd_GrcdAdjv=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdGai=");
		sptr=line+12;
		Fdd_Header.Fdd_GrcdGai=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdUsr=");
		sptr=line+12;
		Fdd_Header.Fdd_GrcdUsr=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdDai=");
		sptr=line+12;
		Fdd_Header.Fdd_GrcdDai=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdPropLL=");
		sptr=line+15;
		Fdd_Header.Fdd_GrcdPropLL=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdPropUL=");
		sptr=line+15;
		Fdd_Header.Fdd_GrcdPropUL=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_PropMeaning=");
		sptr=line+16;
		Fdd_Header.Fdd_PropMeaning=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdSufLL=");
		sptr=line+14;
		Fdd_Header.Fdd_GrcdSufLL=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdSufUL=");
		sptr=line+14;
		Fdd_Header.Fdd_GrcdSufUL=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdNum1=");
		sptr=line+13;
		Fdd_Header.Fdd_GrcdNum1=(unsigned char)strtol(sptr,&eptr,16);
		get_line(line,"Fdd_GrcdNum2=");
		sptr=line+13;
		Fdd_Header.Fdd_GrcdNum2=(unsigned char)strtol(sptr,&eptr,16);
	
		//read the blank line
		fgets(line,999,infile);
		
		get_line(line,"Back end number offsets");
		i=0;
		line_num++;
		fgets(line,999,infile);
		while (line[0]=='/')
		{
			sptr=line+19;
			for (j=0;j<4;j++,i++)
			{
				if (!sptr[0])
					break;
				bno_table[bno_table_len++]=(unsigned char)strtol(sptr,&eptr,16);
				//skip the ,
				eptr++;
				sptr=eptr;
			}
			line_num++;
			fgets(line,999,infile);
		}
	
		get_line(line,"Forward lookup vector table offsets");
		i=0;
		line_num++;
		fgets(line,999,infile);
		while (line[0]=='/')
		{
			sptr=line+26;
			for (j=0;j<20;j++,i++)
			{
				if (!sptr[0])
					break;
				vector_table[vector_table_len++]=(unsigned char)strtol(sptr,&eptr,16);
				//skip the ,
				eptr++;
				sptr=eptr;
			}
			line_num++;
			fgets(line,999,infile);
		}
		
		
		idic_dict_p=malloc(sizeof(idic_dict_t)*max_idic_ent);
	
	
		get_line(line,INTERNAL);
		
		memset(idic_indices,0,sizeof(IDIC_INDICES)*16);
		
		line_num++;
		fgets(line,999,infile);
		RemoveDoneField( line, IDD_EDIT_IDIC );
		while (line[0]&0x80)
		{
			if (idic_ent_count>=max_idic_ent)
			{
				// make the array bigger
				max_idic_ent*=2;
				idic_dict_p=realloc(idic_dict_p,sizeof(idic_dict_t)*max_idic_ent);
			}
			graph_length=0;
			sptr=line;
			while (*sptr && (*sptr)&0x80)
			{
				tot_graph[graph_length]=((*sptr) & 0x7F);
				graph_length++;
				sptr++;
			}
			for (i=0;i<graph_length;i+=2)
			{
				idic_dict_p[idic_ent_count].graph[i]=tot_graph[i];
				idic_dict_p[idic_ent_count].graph[i+1]=tot_graph[i+1];
			}
			idic_dict_p[idic_ent_count].graph[graph_length]='\0';
			if (graph_length>max_idic_graph_len)
			{
				idic_indices[(graph_length/2)-1].idic_index_dummy=idic_ent_count;
				max_idic_graph_len=graph_length;
			}
			//read the ctl info
			while ((*sptr==' ' || *sptr=='\t'))
				sptr++;
			if (strncmp(sptr,"ctl=",4)!=0)
			{
				err_msg = 1;
				goto error_exit;
			}
			sptr+=4;
			idic_dict_p[idic_ent_count].data.idic_ctl=strtol(sptr,&eptr,16);
			sptr=eptr;
			sptr=strchr(sptr,'=');
			sptr++;
			idic_dict_p[idic_ent_count].data.idic_f2=strtol(sptr,&eptr,16);
			sptr=eptr;
			sptr=strchr(sptr,'=');
			sptr++;
			idic_dict_p[idic_ent_count].data.idic_bno=strtol(sptr,&eptr,16);
			sptr=eptr;
			sptr=strchr(sptr,'=');
			sptr++;
			idic_dict_p[idic_ent_count].data.idic_pno=strtol(sptr,&eptr,16);
			sptr=eptr;
			sptr=strchr(sptr,'=');
			sptr++;
			idic_dict_p[idic_ent_count].data.idic_mru=strtol(sptr,&eptr,16);
			sptr=eptr;
			
			while ((*sptr==' '|| *sptr=='\t'))
				sptr++;
			if (strncmp(sptr,"acc:",4)!=0)
			{
				err_msg = 1;
				goto error_exit;
			}
			sptr+=4;
			// get the accent information
			acc_length=0;
			if (strncmp(sptr,"none",4)!=0)
			{
				while (*sptr && strncmp(sptr,"pron",4)!=0)
				{
					idic_dict_p[idic_ent_count].acc[acc_length]=(strtol(sptr,&eptr,16)<<4);
					sptr=eptr+1;
					idic_dict_p[idic_ent_count].acc[acc_length]+=strtol(sptr,&eptr,16);
					sptr=eptr;
					while ((*sptr==' '|| *sptr=='\t'))
						sptr++;
					acc_length++;
				}
			}
			else
			{
				sptr+=4;
				while ((*sptr==' '|| *sptr=='\t'))
					sptr++;
			}
			idic_dict_p[idic_ent_count].acc_length=acc_length;
			if (strncmp(sptr,"pron:",5)!=0)
			{
				err_msg = 1;
				goto error_exit;
			}
			sptr+=5;
			pron_length=0;
			if (strncmp(sptr,"mkh",3)!=0)
			{
				while (*sptr && strncmp(sptr,"phon",4)!=0)
				{
					idic_dict_p[idic_ent_count].pron[pron_length]=strtol(sptr,&eptr,16);
					sptr=eptr;
					while ((*sptr==' '|| *sptr=='\t'))
						sptr++;
					pron_length++;
				}
			}
			idic_dict_p[idic_ent_count].pron_length=pron_length;
			idic_ent_count++;
			line_num++;
			fgets(line,999,infile);
			RemoveDoneField( line, IDD_EDIT_IDIC );
		}
				
		//fprintf(stderr,"idic_ent_count=%d\n",idic_ent_count);
		
		tan_dict_p=malloc(sizeof(tan_dict_t)*max_tan_ent);
		
		get_line(line,KANJI);
		
		line_num++;
		fgets(line,999,infile);
		RemoveDoneField( line, IDD_EDIT_TDIC );
		while (line[0]&0x80)
		{
			if (tan_ent_count>=max_tan_ent)
			{
				// make the array bigger
				max_tan_ent*=2;
				tan_dict_p=realloc(tan_dict_p,sizeof(tan_dict_t)*max_tan_ent);
			}
			graph_length=0;		
			sptr=line;
			while (*sptr && (*sptr)&0x80)
			{
				tot_graph[graph_length]=((*sptr) & 0x7F);
				graph_length++;
				sptr++;
			}
			for (i=0;i<graph_length;i+=2)
			{
				tan_dict_p[tan_ent_count].graph[i]=tot_graph[i];
				tan_dict_p[tan_ent_count].graph[i+1]=tot_graph[i+1];
			}
			tan_dict_p[tan_ent_count].graph[graph_length]='\0';
			//read the ctl info
			while ((*sptr==' ' || *sptr=='\t'))
				sptr++;
			if (strncmp(sptr,"type=",5)!=0)
			{
				err_msg = 1;
				goto error_exit;
			}
			sptr+=5;
			tan_dict_p[tan_ent_count].type=strtol(sptr,&eptr,16);
			sptr=eptr;
			
			while ((*sptr==' '|| *sptr=='\t'))
				sptr++;
			if (strncmp(sptr,"acc:",4)!=0)
			{
				err_msg = 1;
				goto error_exit;
			}
			sptr+=4;
			// get the accent information
			acc_length=0;
			if (strncmp(sptr,"none",4)!=0)
			{
				while (*sptr && strncmp(sptr,"pron",4)!=0)
				{
					tan_dict_p[tan_ent_count].acc[acc_length]=(strtol(sptr,&eptr,16)<<4);
					sptr=eptr+1;
					tan_dict_p[tan_ent_count].acc[acc_length]+=strtol(sptr,&eptr,16);
					sptr=eptr;
					while ((*sptr==' '|| *sptr=='\t'))
						sptr++;
					acc_length++;
				}
			}
			else
			{
				sptr+=4;
				while ((*sptr==' '|| *sptr=='\t'))
					sptr++;
			}
			tan_dict_p[tan_ent_count].acc_length=acc_length;
			if (strncmp(sptr,"pron:",5)!=0)
			{
				err_msg = 1;
				goto error_exit;
			}
			sptr+=5;
			pron_length=0;
			if (strncmp(sptr,"mkh",3)!=0)
			{
				while (*sptr && strncmp(sptr,"phon",4)!=0)
				{
					tan_dict_p[tan_ent_count].pron[pron_length]=strtol(sptr,&eptr,16);
					sptr=eptr;
					while ((*sptr==' '|| *sptr=='\t'))
						sptr++;
					pron_length++;
				}
			}
			tan_dict_p[tan_ent_count].pron_length=pron_length;
			tan_ent_count++;
			line_num++;
			fgets(line,999,infile);
			RemoveDoneField( line, IDD_EDIT_TDIC );
		}
				
		//fprintf(stderr,"tan_ent_count=%d\n",tan_ent_count);
		
		edic_dict_p=malloc(sizeof(edic_dict_t)*max_edic_ent);
		
		get_line(line,EXTERNAL);
		
		line_num++;
		fgets(line,999,infile);
		RemoveDoneField( line, IDD_EDIT_EDIC );
		while (line[0]&0x80 && !feof(infile))
		{
			if (edic_ent_count>=max_edic_ent)
			{
				// make the array bigger
				max_edic_ent*=2;
				//fprintf(stderr,"edic_size=%d\n",sizeof(edic_dict_t)*max_edic_ent);
				edic_dict_p=realloc(edic_dict_p,sizeof(edic_dict_t)*max_edic_ent);
			}
			graph_length=0;		
			sptr=line;
			while (*sptr && (*sptr)&0x80)
			{
				tot_graph[graph_length]=((*sptr) & 0x7F);
				graph_length++;
				sptr++;
			}
			for (i=0;i<graph_length;i+=2)
			{
				edic_dict_p[edic_ent_count].graph[i]=tot_graph[i];
				edic_dict_p[edic_ent_count].graph[i+1]=tot_graph[i+1];
			}
			edic_dict_p[edic_ent_count].graph[graph_length]='\0';
			edic_dict_p[edic_ent_count].num_prons=0;
			edic_dict_p[edic_ent_count].max_prons=1;
			edic_dict_p[edic_ent_count].data=malloc(sizeof(edic_data_t)*edic_dict_p[edic_ent_count].max_prons);
			pron_count=0;
			while (((*sptr)& 0x80)==0 && !feof(infile))
			{
				
				if (edic_dict_p[edic_ent_count].num_prons>=edic_dict_p[edic_ent_count].max_prons)
				{
					edic_dict_p[edic_ent_count].max_prons*=2;
					edic_dict_p[edic_ent_count].data=realloc(edic_dict_p[edic_ent_count].data,
						sizeof(edic_data_t)*edic_dict_p[edic_ent_count].max_prons);
				}
				
				while ((*sptr==' ' || *sptr=='\t'))
					sptr++;
				if (strncmp(sptr,"flag2=",6)!=0)
				{
					err_msg = 1;
					goto error_exit;
				}
				sptr+=6;
				edic_dict_p[edic_ent_count].data[pron_count].f2=strtol(sptr,&eptr,16);
				sptr=eptr;
				while ((*sptr==' ' || *sptr=='\t'))
					sptr++;
				if (strncmp(sptr,"mru=",4)!=0)
				{
					err_msg = 1;
					goto error_exit;
				}
				sptr+=4;
				edic_dict_p[edic_ent_count].data[pron_count].mru=strtol(sptr,&eptr,16);
				sptr=eptr;
				while ((*sptr==' ' || *sptr=='\t'))
					sptr++;
				if (strncmp(sptr,"Grcd=",5)!=0)
				{
					err_msg = 1;
					goto error_exit;
				}
				sptr+=5;
				grcd_length=0;
				if (strncmp(sptr,"none",4)!=0)
				{
					while (*sptr && strncmp(sptr,"acc:",4)!=0)
					{
						edic_dict_p[edic_ent_count].data[pron_count].grcd[grcd_length]=(strtol(sptr,&eptr,16));
						sptr=eptr;
						while ((*sptr==' '|| *sptr=='\t'))
							sptr++;
						grcd_length++;
					}
				}
				else
				{
					sptr+=4;
					while ((*sptr==' '|| *sptr=='\t'))
						sptr++;
				}
				edic_dict_p[edic_ent_count].data[pron_count].grcd_length=grcd_length;
				
				while ((*sptr==' '|| *sptr=='\t'))
					sptr++;
				if (strncmp(sptr,"acc:",4)!=0)
				{
					err_msg = 1;
					goto error_exit;
				}
				sptr+=4;
				// get the accent information
				acc_length=0;
				if (strncmp(sptr,"none",4)!=0)
				{
					while (*sptr && strncmp(sptr,"pron",4)!=0)
					{
						edic_dict_p[edic_ent_count].data[pron_count].acc[acc_length]=(strtol(sptr,&eptr,16)<<4);
						sptr=eptr+1;
						edic_dict_p[edic_ent_count].data[pron_count].acc[acc_length]+=strtol(sptr,&eptr,16);
						sptr=eptr;
						while ((*sptr==' '|| *sptr=='\t'))
							sptr++;
						acc_length++;
					}
				}
				else
				{
					sptr+=4;
					while ((*sptr==' '|| *sptr=='\t'))
						sptr++;
				}
				edic_dict_p[edic_ent_count].data[pron_count].acc_length=acc_length;
				if (strncmp(sptr,"pron:",5)!=0)
				{
					err_msg = 1;
					goto error_exit;
				}
				sptr+=5;
				pron_length=0;
				if (strncmp(sptr,"mkh",3)!=0)
				{
					while (*sptr && strncmp(sptr,"phon",4)!=0)
					{
						edic_dict_p[edic_ent_count].data[pron_count].pron[pron_length]=strtol(sptr,&eptr,16);
						sptr=eptr;
						while ((*sptr==' '|| *sptr=='\t'))
							sptr++;
						pron_length++;
					}
				}
				edic_dict_p[edic_ent_count].data[pron_count].pron_length=pron_length;
				line_num++;
				edic_dict_p[edic_ent_count].num_prons++;
				edic_phon_count++;
				pron_count++;
				fgets(line,999,infile);
				RemoveDoneField( line, IDD_EDIT_EDIC );
				sptr=line;
			}
			edic_ent_count++;
		}
			
		//fprintf(stderr,"edic_graph_count=%d edic_phon_count=%d\n", edic_ent_count,edic_phon_count);
	
		//create the internal dictioanry pronunciation table
		for (i=0;i<idic_ent_count;i++)
		{
			idic_dict_p[i].pron_offset_index=add_pron_to_idic(idic_dict_p[i].acc_length,
				idic_dict_p[i].acc,idic_dict_p[i].pron_length,idic_dict_p[i].pron);
		}
		idic_prons=malloc(sizeof(char)*idic_total_pron_length+10);
		for (i=0;i<idic_num_prons;i++)
		{
			idic_pron_p[i].offset=idic_prons_cur_pos;
			memcpy(&idic_prons[idic_prons_cur_pos],idic_pron_p[i].accpron,idic_pron_p[i].length);
			idic_prons_cur_pos+=idic_pron_p[i].length;
		}
		// fill the opron offsets into the dictioary data
		for (i=0;i<idic_ent_count;i++)
		{
			j=idic_pron_p[idic_dict_p[i].pron_offset_index].offset;
			idic_dict_p[i].data.idic_acc_ofs1=((j&0xff00)>>8);
			idic_dict_p[i].data.idic_acc_ofs2=((j&0x00ff));
		}
	
		max_idic_data=1024;
		idic_data=malloc(sizeof(char)*max_idic_data);
				
		for (i=0;i<idic_ent_count;i++)
		{
			if (idic_indices[cur_index].idic_index_dummy==i)
			{
				idic_indices[cur_index].idic_len_ptr1=  ((cur_idic_pos&0xff00)>>8);
				idic_indices[cur_index].idic_len_ptr2=  ((cur_idic_pos&0x00ff));
				cur_index++;
			}
			length=build_idic_entry(tot_graph,&idic_dict_p[i]);
			if (cur_idic_pos+length>=max_idic_data)
			{
				max_idic_data*=2;
				idic_data=realloc(idic_data,sizeof(char)*max_idic_data);
			}
			if (length>0)
			{
				memcpy(&idic_data[cur_idic_pos],tot_graph,length);
				cur_idic_pos+=length;
			}
		}
		idic_indices[cur_index].idic_len_ptr1=  ((cur_idic_pos&0xff00)>>8);
		idic_indices[cur_index].idic_len_ptr2=  ((cur_idic_pos&0x00ff));
		cur_index++;
			
			
		//create the tan-kanji dictionary
		memset(tan,0,2048);
		
		tdic_max_data=4096;
		tdic_data=malloc(sizeof(char)*tdic_max_data);
		
		tdic_max_keys=1024;
		tdic_keys=malloc(sizeof(char)*tdic_max_keys);
		
		
		for (i=0;i<tan_ent_count;i++)
		{
			if (tdic_data_pos>=tdic_max_data)
			{
				tdic_max_data*=2;
				tdic_data=realloc(tdic_data,sizeof(char)*tdic_max_data);
			}
			
			if (tdic_keys_pos>=tdic_max_keys)
			{
				tdic_max_keys*=2;
				tdic_keys=realloc(tdic_keys,sizeof(char)*tdic_max_keys);
			}
			
			length=build_tdic_entry(tot_graph,&tan_dict_p[i]);
			
			if ((tdic_page_pos+length)>=1023)
			{
				memcpy(&tdic_data[tdic_data_pos],tan,1024);
				tdic_data_pos+=1024;
				tdic_page_pos=0;
				memset(tan,0,1024);
			}
			if (tdic_page_pos==0)
			{
				tdic_keys[tdic_keys_pos++]=tan_dict_p[i].graph[0];
				tdic_keys[tdic_keys_pos++]=tan_dict_p[i].graph[1];
				tdic_num_keys++;
			}
			memcpy(&tan[tdic_page_pos],tot_graph,length);
			tdic_page_pos+=length;
		}

		if (tdic_page_pos)
		{
			memcpy(&tdic_data[tdic_data_pos],tan,1024);
			tdic_data_pos+=1024;
			tdic_page_pos=0;
		}
	
		//build the external ditionary tables.
		memset(tan,0xff,2048);
		
		edic_max_index=1024;
		edic_index=malloc(sizeof(char)*edic_max_index+4);
		
		edic_max_data=16384;
		edic_data=malloc(sizeof(char)*edic_max_data);
		
		edic_max_keys=4096;
		edic_keys=malloc(sizeof(char)*edic_max_keys+32);
		
		prev_ent[0]='\0';	
		for (i=0;i<edic_ent_count;i++)
		{
			if (edic_index_pos>=edic_max_index)
			{
				edic_max_index*=2;
				edic_index=realloc(edic_index,sizeof(char)*edic_max_index+4);
			}
			
			if (edic_data_pos>=edic_max_data)
			{
				edic_max_data*=2;
				edic_data=realloc(edic_data,sizeof(char)*edic_max_data);
			}
			
			if (edic_keys_pos>=edic_max_keys)
			{
				edic_max_keys*=2;
				edic_keys=realloc(edic_keys,sizeof(char)*edic_max_keys+32);
			}
			
			length=build_edic_entry(prev_ent,tot_graph,new_graph,&edic_dict_p[i]);
			length2=length>>16;
			length&=0x0000FFFF;
			
			strcpy(prev_ent,edic_dict_p[i].graph);
			
			if ((edic_page_pos+length)>=1023)
			{
				memcpy(&edic_data[edic_data_pos],tan,1024);
				edic_data_pos+=1024;
				edic_page_pos=0;
				memset(tan,0xff,1024);
			}
			if (edic_page_pos==0)
			{
				edic_index[edic_index_pos++]=(edic_keys_pos&0x00ff);
				edic_index[edic_index_pos++]=((edic_keys_pos&0xff00)>>8);
				edic_index[edic_index_pos++]=strlen(edic_dict_p[i].graph);
				
				memcpy(&edic_keys[edic_keys_pos],edic_dict_p[i].graph,strlen(edic_dict_p[i].graph));
				edic_keys_pos+=strlen(edic_dict_p[i].graph);
				edic_index_count++;
				memcpy(&tan[edic_page_pos],new_graph,length2);
				edic_page_pos+=length2;
			}
			else
			{
				memcpy(&tan[edic_page_pos],tot_graph,length);
				edic_page_pos+=length;
			}
		}
		if (edic_page_pos)
		{
			memcpy(&edic_data[edic_data_pos],tan,1024);
			edic_data_pos+=1024;
			edic_page_pos=0;
		}
			
		// write it out to the dictionary file.
		cur_writing_pos=0x100;

		// write the char attributes table
		Fdd_Header.Fdd_ChrAttrOfs=cur_writing_pos;

		for (i=0;i<char_attr_len;i++)
		{
			Fdd_char_header[cur_writing_pos++]=char_attrs[i];
		}

		//write the grammar codes to the header
		Fdd_Header.Fdd_GrcdTblOfs=cur_writing_pos;
		for (i=0;i<grammar_codes_len;i++)
		{
			Fdd_char_header[cur_writing_pos++]=grammar_codes[i];
		}
		
		Fdd_Header.Fdd_IdicIndOfs=cur_writing_pos;
		//write the idic indicies to the header
		memcpy(&Fdd_char_header[cur_writing_pos],idic_indices,sizeof(IDIC_INDICES)*16);
		cur_writing_pos+=sizeof(IDIC_INDICES)*16;
		//write the idic pronuncuations into the table.
		Fdd_Header.Fdd_IdicPronOfs=cur_writing_pos;
		memcpy(&Fdd_char_header[cur_writing_pos],idic_prons,idic_prons_cur_pos);
		cur_writing_pos+=idic_prons_cur_pos;
		
		//write the vectors to the header.
		Fdd_Header.Fdd_VecpOfs=cur_writing_pos;
		memcpy(&Fdd_char_header[cur_writing_pos],vector_table,vector_table_len);
		cur_writing_pos+=vector_table_len;
		
		//write the v5you table
		Fdd_Header.Fdd_V5youOfs=cur_writing_pos;
		memcpy(&Fdd_char_header[cur_writing_pos],v5danyou,v5danyou_len);
		cur_writing_pos+=v5danyou_len;
		
		// write the bno table
		Fdd_Header.Fdd_BnoTblOfs=cur_writing_pos;
		memcpy(&Fdd_char_header[cur_writing_pos],bno_table,bno_table_len);
		cur_writing_pos+=bno_table_len;
		
		//write the matrix offset value, no table
		Fdd_Header.Fdd_MatrixOfs=cur_writing_pos;
		
		//write the tdic num of pages;
		Fdd_Header.Fdd_TdicNoPage=tdic_num_keys;
		Fdd_Header.Fdd_TdicPageSize=1;
		
		//write the tdic indexes 
		Fdd_Header.Fdd_TdicIndOfs=cur_writing_pos;
		memcpy(&Fdd_char_header[cur_writing_pos],tdic_keys,tdic_keys_pos);
		cur_writing_pos+=tdic_keys_pos;
		
		//write the idic data 
		//start it at a page boundry.... (1024)
		cur_writing_pos=((cur_writing_pos+1023)/1024);
		
		Fdd_Header.Fdd_IdicPageOfs=cur_writing_pos;
		Fdd_Header.Fdd_IdicPageSize=1;
		Fdd_Header.Fdd_IdicNoPage=(cur_idic_pos+1023)/1024;
		
		cur_writing_pos*=1024;
		Fdd_Header.Fdd_IdicOfs=cur_writing_pos;
		memcpy(&Fdd_char_header[cur_writing_pos],idic_data,cur_idic_pos);
		cur_writing_pos+=cur_idic_pos;
		
		Fdd_Header.Fdd_HdrNg=cur_writing_pos;
		
		Fdd_Header.Fdd_HdrSector=(cur_writing_pos+1023)/1024;
		
		cur_writing_pos=((cur_writing_pos+1023)/1024)*1024;
		
		Fdd_Header.Fdd_EdicIndOfs=cur_writing_pos;
		cur_writing_pos+=edic_index_pos;
		Fdd_Header.Fdd_EdicKeyOfs=cur_writing_pos;
		cur_writing_pos+=edic_keys_pos;
		
		
		Fdd_Header.Fdd_EdicIndSector=((cur_writing_pos-Fdd_Header.Fdd_EdicIndOfs)+1023)/1024;
		// cur_wiriting_pos is now in pages, not bytes.....
		
		cur_writing_pos=((cur_writing_pos+1023)/1024);
		
		Fdd_Header.Fdd_TdicPageOfs=cur_writing_pos;
		Fdd_Header.Fdd_TdicPageSize=0x0001;
		
		//Fdd_Header.Fdd_TdicNoPage=tdic_num_keys;
		
		cur_writing_pos+=tdic_num_keys;
		
		
		Fdd_Header.Fdd_EdicPageOfs=cur_writing_pos;
		Fdd_Header.Fdd_EdicPageSize=0x0001;
		Fdd_Header.Fdd_EdicNoPage=edic_index_count;
		
		
		//actually write the header to the file....
		fwrite(&Fdd_Header,1,Fdd_Header.Fdd_HdrSector*1024,dict_file);
		
		fwrite(edic_index,1,edic_index_pos,dict_file);
		fwrite(edic_keys,1,edic_keys_pos,dict_file);
		i=edic_index_pos+edic_keys_pos;
		i%=1024;
		memset(tan,0,1024);
		//write blank space so the tdic starts at a page break;
		fwrite(tan,1,1024-i,dict_file);
		
		
		//write the tdic
		fwrite(tdic_data,1,tdic_num_keys*1024,dict_file);
		
		//write the edic
		
		fwrite(edic_data,1,edic_index_count*1024,dict_file);
			
error_exit:
		//fprintf(stderr,"error_count=%d\n",err_count);

		SetDlgItemText( hDlg, IDC_STATIC_RED, _T("") );

		if( err_msg )
			MessageBox( hDlg, _T("The dictionary could not be created.   "), _T("ERROR..."), MB_OK | MB_ICONSTOP );
		else
			MessageBox( hDlg, _T("A dictionary was successfully created.   "), _T("NOTICE..."), MB_OK | MB_ICONINFORMATION );
		
		fclose(dict_file);
		
		fclose(infile);
		
		free(Fdd_EdicIndex);
	}
} /* end: Myreonsei */

