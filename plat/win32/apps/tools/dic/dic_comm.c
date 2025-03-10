/* 
 ***********************************************************************
 *            
 *                           Copyright �
 *	  Copyright � 2000, 2001 Force Computers, Inc., a Solectron Company. All rights reserved.
 *    � Digital Equipment Corporation 1996. All rights reserved.
 *
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Force Computers Incorporated and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Force or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:	 dic_comm.c
 *    Author:        JDB 
 *    Creation Date: 5/23/96
 *
 *    Functionality:
 *     This code modified from v4.3 PARDIC
 *     Common code for compiling dictionaries for all languages
 *
 ***********************************************************************
 *    Revision History:        
 * 001 MGS  13-Jun-1996 Modified so that it could build for MSDOS and WIN32 with a switch
 *                      Added the command line switch /t:msdos and /t:win32
 *                      the default is MSDOS
 * 002 MGS	09/29/1997	Made change for __osf__ build
 * 003 MFG	06/29/1998	Changed the way the temp file is used for portbilty
 * 004 ETT	10/05/1998	added linux code
 * 005 MGS	04/13/2000	Changes for integrated phoneme set 
 * 006 CHJ	07/20/2000	French added
 * 007 CAB	09/08/2000	Removed variables not used.
 * 011 MGS	05/09/2001	Some VxWorks porting BATS#972
 * 012 CAB	05/14/2001	Updated copyright info
 * 013 MGS	06/19/2001	Solaris Port BATS#972
 *
 */

#include "port.h"
/* ETT 07/24/1998 watch out here */
#if !defined _UNIX_LIKE_
#include <io.h>          
#endif

#if defined __linux__ || defined __QNX__
#ifdef __arm__
#include <asm/io.h>
#else
#include <sys/io.h>
#endif
#endif

#include <stdlib.h>

#if !defined _UNIX_LIKE_
#include <process.h>       
#endif

#include <stdio.h>

#ifndef _APPLE_MAC_
#include <malloc.h>
#endif
#include <fcntl.h>

#if defined _UNIX_LIKE_
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <sys\types.h>
#include <sys\stat.h>
#endif /* _UNIX_LIKE_ */

#include <ctype.h>      
#include <string.h>
#include <time.h>
#include "dic.h"

unsigned long swap_endian_long(unsigned long in);
unsigned short swap_endian_short(unsigned short in);

/*
 * general defines ...
 */
/*#define DEBUG         1 */
#define true    1
#define false 0
#define failure 1
#define success 0

//#define COMPRESSION

extern PTAB ptab_us[];
extern PTAB ptab_uk[];
extern PTAB ptab_fr[];
extern PTAB ptab_gr[];
extern PTAB ptab_sp[];
extern PTAB ptab_la[];
extern PTAB ptab_it[];
extern unsigned long ntab_us;
extern unsigned long ntab_uk;
extern unsigned long ntab_fr;
extern unsigned long ntab_gr;
extern unsigned long ntab_sp;
extern unsigned long ntab_la;
extern unsigned long ntab_it;

PTAB *ptab=NULL;
unsigned long ntab=0;

#pragma pack (1)
struct d_ent {
   U16 size;
   U32 fc;
   unsigned char gr_ph[256];
};
#pragma pack()
    
    
/* MGS 07/28/97 change for osf build */    
struct pc_dictionary_nc {
   S32 entries;   /* number of entries */
   S32 total;     /* bytes excluding table */
};

/* MGS 07/28/97 change for osf build */    
//with compression
struct pc_dictionary {
   S32 entries;   /* number of entries */
   S32 total;     /* bytes excluding table */
   S32 fc_entries;
};

/* dictionary targets */
#define MSDOS_FORMAT  1
#define WIN32_FORMAT  2


#define BIGENDIAN 1
#define LITTLEENDIAN 2

#define NO_COMPRESSION	0
#define COMPRESSION		1


/* function prototypes */
unsigned char toph(unsigned char c);
unsigned char from_ph(unsigned char c);
void sort_ents (void);
void read_ent (struct d_ent *ent, unsigned int index);          
/* end prototypes */

/*
 *  Upper case folding table ...
 */
unsigned char case_upper[] = {
#include "ls_upper.tab"
};

       
struct d_ent input_entry;
struct d_ent comp_entry;

U32 _huge *disk_entries;
U32 _huge  *links;
U32 free_entry;
long linenumber=0;  /* the linenumber for output purposes */

//#ifdef COMPRESSION
U32 fc_entry_table[256];
int num_fc_entries=1;

int replace_fc_entry(int fc)
{
	int i;
	for (i=0;i<num_fc_entries;i++)
	{
		if (fc_entry_table[i] == (U32)fc)
		{
			return(i);
		}
	}
	fc_entry_table[i]=fc;
	num_fc_entries++;
	return(i);
}
//#endif

FILE *tfp;

void PrintHelp(void)
{
	printf("DIC_COMM.C; main; Useage: dic_comm infile outfile [options]\n");
	printf("options: /p:###     use entries with a priority <= ###\n");
	printf("         /n         exclude names from the dictionary\n");
	printf("         /o         use the old format (/p and /n are ignored)\n");
	printf("         /t:msdos   build the dictionary for msdos\n");
	printf("         /t:win32   build the dictionary for win32\n");
	printf("         /e:native  write native endian format\n");
	printf("         /e:other   write other endian format\n");
	printf("         /c         Use Cheesy_dict_compression\n");
	printf("         /l:<lang>  <lang> can be us, uk, fr, gr, sp, la or it.  Default is us \n");
}

int main(int argc, char ** argv)
{
	int tmp, backslash_flag = 0;
	unsigned char grapheme [50] = {'\0'}, * grapheme_index; 
	char 
		blanks[10],
		sLang[8];
	unsigned char *byte_p; // CAB 9/8/00 NOT USED IN CODE
	
	DIC_OBJ_HEADER header; /* file header */
	FILE *infp;            /* input file pointer */
	FILE *outfp;
	
	unsigned char *s,*os;
	
	/* the name and priority read fron the dicionary file
	*/                                
	unsigned long inname,inpriority;                
	
	/* variables for the command line options
	*/    
	unsigned long priority,excludenames,oldformat; 
	unsigned char temps[100], *tempp;
	unsigned long free_offset;
	long i,total_bytes;
	// long j, strindex; CAB 9/8/00 not used in code
	unsigned int  k;
	// unsigned int m; CAB 9/8/00 Not used in code
	U32 index,count;
	struct pc_dictionary pcd;
	struct pc_dictionary pcd_big;
	unsigned long addr,addr_186;
	unsigned long max_entries_in_memory; /* Max entries allowed */
	short target=MSDOS_FORMAT;
	short endian=LITTLEENDIAN;
	int compression=NO_COMPRESSION;
	
	//#ifdef COMPRESSION
	char tempc;
	//#endif
	
	//#ifdef COMPRESSION
	fc_entry_table[0]=0;
	//#endif
	
	/*
	*  check args and open input file ...
	*/     
	
	if(argc < 2 || argc > 8)
	{
		PrintHelp();		
		exit(0);
	}
	
	/* moved halloc to beginning because opening large files first can leave 
	* nothing left for this
	*/
	header.no_of_entries=100000; /*eab just tell it for now*/
	max_entries_in_memory = header.no_of_entries;
	if((disk_entries = (U32 *)malloc(header.no_of_entries * sizeof(U32)))==NULL)
	{
		printf("DIC_COMM; main; halloc failure on disk_entries");
		exit(1);
	}
	
	if((links = (U32 *)malloc(((U32)(header.no_of_entries+(28*28)) * sizeof(U32))))==NULL)
	{
		printf("DIC_COMM; main; halloc failure on links");
		exit(1);
	}
	
	if ((infp = fopen(argv[1], "rb")) == NULL)
	{
		printf("DIC_COMM; main; Failure on input file open of %s\n",argv[1]);
		exit(1);
	} 
	
	memset (blanks, 0, 10);	
	/* section added to support priorities and name exclusion 
	* command line options mgs 
	*/
	priority=32760;
	oldformat=0;
	excludenames=0;			
	os=NULL;
	strcpy(sLang, "us");
	for (i=2;i<argc;i++)
	{                   
		if (argv[i][0]=='/')
		{
			switch (argv[i][1])
			{
			case 'p':
			case 'P':
				priority=atoi(argv[i]+3);
#ifdef DEBUG 
				printf("priority read in = %s  converted = %d\n",argv[i],priority);
#endif
				break;
			case 'O':
			case 'o':
				oldformat=1;
				break;
			case 'n':
			case 'N':
				excludenames=1;
				break;
			case 't':
			case 'T':
				if ((argv[i][2]==':' &&  case_upper[argv[i][3]]=='M') || case_upper[argv[i][2]]=='M')
					target=MSDOS_FORMAT;
				if ((argv[i][2]==':' &&  case_upper[argv[i][3]]=='W') || case_upper[argv[i][2]]=='W')
					target=WIN32_FORMAT;
				break;
			case 'E':
			case 'e':
				if ((argv[i][2]==':' &&  case_upper[argv[i][3]]=='O') || case_upper[argv[i][2]]=='O')
					endian=BIGENDIAN;
				if ((argv[i][2]==':' &&  case_upper[argv[i][3]]=='N') || case_upper[argv[i][2]]=='N')
					endian=LITTLEENDIAN;
				break;
			case 'C':
			case 'c':
				compression=COMPRESSION;
				break;
			case 'L':
			case 'l':
				if( strstr("us uk fr gr it sp la", &argv[i][3]) )
				{
					strcpy(sLang, &argv[i][3]);
				}
				else
				{
					printf("Error: Invalid language\n");
					PrintHelp();
					exit(0);
				}
				break;

			default:
				printf("DIC_COMM; main; Unrecognized command line option %s\n",argv[i]);
				exit(0);
			}
		}
		else
		{
			os = argv[i];
		}
	}
	
	if( strcmp(sLang, "us") == 0 )
	{
		ptab = ptab_us;
		ntab = ntab_us;
		if( os == NULL )
			os = "dic_us.dic";
	}
	else if( strcmp(sLang, "uk") == 0 )
	{
		ptab = ptab_uk;
		ntab = ntab_uk;
		if( os == NULL )
			os = "dic_uk.dic";
	}
	else if( strcmp(sLang, "fr") == 0 )
	{
		ptab = ptab_fr;
		ntab = ntab_fr;
		if( os == NULL )
			os = "dic_fr.dic";
	}
	else if( strcmp(sLang, "gr") == 0 )
	{
		ptab = ptab_gr;
		ntab = ntab_gr;
		if( os == NULL )
			os = "dic_gr.dic";
	}
	else if( strcmp(sLang, "it") == 0 )
	{
		ptab = ptab_it;
		ntab = ntab_it;
		if( os == NULL )
			os = "dic_it.dic";
	}
	else if( strcmp(sLang, "sp") == 0 )
	{
		ptab = ptab_sp;
		ntab = ntab_sp;
		if( os == NULL )
			os = "dic_sp.dic";
	}
	else if( strcmp(sLang, "la") == 0 )
	{
		ptab = ptab_la;
		ntab = ntab_la;
		if( os == NULL )
			os = "dic_la.dic";
	}

		

	/* previous is to support the new format
	*/
	
	if ((outfp = fopen(os, "w+b")) == NULL)
	{
		printf("DIC_COMM; main; Failure on output file open of %s\n",os);
		exit(0);
	}
	
	/*   if ((tfp = tmpfile()) == NULL) mfg_debug*/
	if ((tfp = fopen("dic.tmp","w+b")) == NULL)
	{
		printf("DIC_COMM; main; Failure on temp file open\n");
		exit(0);
	}
	
	
	/*
	*  Read in and alphabetize the dictionary ...
	*  build the index table in ram to quick cache everything ...
	*/
	free_entry = 0L;
	free_offset = 0L;
	total_bytes = 0L;
	header.no_of_entries=0;
	printf("DIC_COMM; main; Building dictionary %s with %ld entries\n",os,header.no_of_entries);
	
	while((tmp = fgetc(infp)) != EOF)
	{
#ifdef DEBUG   
		printf ("top of loop\n");
#endif          
		linenumber++;
		inpriority=0; /* reset value */
		inname=0;     /* reset value */
		
		/* if the character is a return char... */              
		if (tmp == '\r' || tmp == '\n')
		{
			continue;
		}       
		
		/* otherwise, see if it is a semi-colon */
		if (tmp == ';')
		{        
			
		/* if so, loop through everything else in the stream until 
		*  we read a \r, then we'll come back through and check again. 
		*  this effectively skips commented line.
			*/                   
#ifdef DEBUG
			printf ("Saw a ;\n");
#endif    
			while ((tmp = fgetc(infp)) != '\r' && tmp != '\n');
			ungetc (tmp, infp);
			continue;
		}
		
		/* if line starts with a backslash, it must be a semicolon, 
		* so replace it. this ; then gets pushed back into the stream 
		*/
		header.no_of_entries++;
		
		/* Safety net to keep big dictionaries from running of in memory. cjl
		* starts at 0
		*/
		if (header.no_of_entries == max_entries_in_memory) 
		{
			printf("DIC_COMM; main; Dictionary exceeded max memory ");
			printf("created for %ld entries\n",max_entries_in_memory);
			exit(0);
		}
#ifdef DEBUG
		printf("DIC_COMM; main; bumping on %c %d \n",tmp,tmp);
#endif          
		input_entry.size = 6;
		memset(input_entry.gr_ph,0,sizeof(input_entry.gr_ph));  /* initialize the array */
		s= &input_entry.gr_ph[0];
		
		if (tmp == EOF)
		{
			header.no_of_entries--;
			continue; /*eab safety*/
		}
		
		ungetc (tmp, infp);	
		grapheme_index = grapheme;	
		do /* eat the grapheme string */
		{
			backslash_flag = 0;
			tmp = fgetc(infp); /* eat the grapheme string */
			if (tmp == ',')
				break;     
				/* catch backslash delimiters: if we see one, just print the char that 
				* follows it and print it out
			*/
			if (tmp == '\\')
			{     
				backslash_flag = 1;
				tmp = fgetc (infp);
			}
			*grapheme_index = tmp & 0xff;
			*grapheme_index++;
			(*s++) = tmp & 0xff;
			
#ifdef DEBUG
			printf("DIC_COMM; main; "); /* added line nubmer to output */
			printf("line %d grapheme  %c %d \n input_entry.size = %d ",linenumber,*(s-1),*(s-1),input_entry.size);
#endif
			input_entry.size++;  
		} while( (tmp != ',') || (backslash_flag));		              
		
		/* now we've finished reading the grapheme... */
		*grapheme_index = '\0';
		tmp=fgetc(infp);
		
#ifdef DEBUG
		printf("DIC_COMM; main; ");	/* added linenumber to output */
		printf("line %d parsing quote %c %d \n ",linenumber,tmp,tmp); 
#endif     
		
		(*s++)='\0'; /* ad in needed null*/
		input_entry.size++;
		input_entry.fc=0;
		
#ifdef DEBUG
		printf("DIC_COMM; main; ");
		printf("parsing homograph field %c %d \n ",tmp,tmp);
#endif
		
		switch(tmp)
		{                                
		case 'P':
			input_entry.fc = (input_entry.fc  | FC_M_PRIMHOMO | FC_M_HOMOGRAPH);
			break;
		case 'S':
			input_entry.fc = (input_entry.fc  | FC_M_HOMOGRAPH);
			break;
		case 'N' :
			break;
		default :
			printf("DIC_COMM; main; ");    
			printf ("In grapheme:%s\n", grapheme); 
			printf("line %d; Received bad homograph field received %c %d\n",linenumber,tmp,tmp);
			exit (1);
		}
		
		while( fgetc(infp) != ','); /* get to phoneme field*/
		
		/* look for commas separating the fields */
		while( (tmp= fgetc(infp) ) != ',')
		{
			if (tmp == '\\')
				tmp = fgetc (infp);
			if ((*s++ = toph((unsigned char)tmp)) == 0xff)
			{
				printf("DIC_COMM; main; ");
				printf ("In grapheme:%s\n", grapheme);
				printf("line %d; entry number %d \n",linenumber,header.no_of_entries);
				exit(1);
			}
#ifdef DEBUG
			printf("DIC_COMM; main; line %d; phopheme  %c \n ",linenumber,tmp);
#endif
			input_entry.size++;
		}
		
		/* back up one and ...*/
		(*s++)='\0'; /* add in needed null*/
		input_entry.size++; 
		
		
		/* Use 1 for T, and 0 for F in the new style */
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_ADJ);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_ADV);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_ART);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_AUX);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_BE);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_BEV);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_CONJ);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_ED);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_HAVE);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_ING);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_NOUN);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_POS);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_PREP);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | (FC_M_PRON));
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_SUBCONJ);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_THAT);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_TO);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_VERB);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_WHO);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_NEG);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_INTER);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_REF);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_PART);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_FUNC);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_CONTRACTION);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_PRIMHOMO);
		
		if ((tmp = fgetc(infp)) == '1')
			input_entry.fc = (input_entry.fc | FC_M_REFR);
		
		//      if ((tmp = fgetc(infp)) == '1')
		//       input_entry.fc = (input_entry.fc | FC_M_UNKN);
		//  
		//if ((tmp = fgetc(infp)) == '1')
		// input_entry.fc = (input_entry.fc | FC_M_NAME);
		
		tmp = fgetc(infp); /* read unused value */             
		
		
						   /* this code was added to support the optional fields at the 
						   * the line in the dictionary
		*/
		//tmp=fgetc(infp);
		
#ifdef DEBUG
		printf("tmp = %d\n",tmp);
#endif
		
		if (tmp  == '\r')
		{                 
			ungetc(tmp,infp);
		}
		else
		{
			if ((tmp = fgetc(infp)) == '1')
			{
				inname=1;    
				input_entry.fc = (input_entry.fc | FC_M_NAME);
			}
#ifdef DEBUG
			printf("name field = %d\n",inname);
#endif         
			
			/* get the rest of the line into a string */
			fgets(temps,98,infp); 
#ifdef DEBUG
			printf("the string %s",temps); 
#endif                            
			
			/* put the carriage return back */
			ungetc(temps[strlen(temps)]-1,infp);    
			
			/* get the priority field */ 	   		
			tempp=strtok(temps,","); 
#ifdef DEBUG
			printf("the priority string %s\n",tempp); 
#endif
			inpriority=atoi(tempp);
#ifdef DEBUG
			printf("inpriority = %d\n",inpriority);
#endif
		}
		
		/* are you using the old format for the dictionary? */                     
		if (!oldformat)
		{
			if (((inname==1) && (excludenames==1)) || (inpriority>priority))
			{
#ifdef DEBUG
				printf("inname = %d,  excludenames = %d dropping entry\n",inname,excludenames);
				printf("inpriority = %d,  priority = %d dropping entry\n",inpriority,priority);
#endif                                   
				/* subtract one for the skipped entry */
				header.no_of_entries--;  
				continue;           /* stop processing this element */
				/* return to the top of the loop */				           		
			}
		}
		if (compression==COMPRESSION)
		{
			input_entry.fc=replace_fc_entry(input_entry.fc);
		}
		
		
		
		/*
		*  write the entry into the temp file and add the index in ...
		*/
		if (target==MSDOS_FORMAT)
		{
			//		  input_entry.size-=2;/* subtract the two here so it is easire to deal with later */
			if (input_entry.size<=4)/* be sure there is some data there */
			{
			/*
			input_entry.size=8;
			input_entry.gr_ph[0]='\0';
			input_entry.gr_ph[1]='\0';
			input_entry.gr_ph[2]='\0';
			input_entry.gr_ph[3]='\0';
				*/
			}
			fwrite(&input_entry.size,input_entry.size,1,tfp);
		}
		else
		{
			/* for non msdos envrionments, 4 byte align the data */
			if (compression==COMPRESSION)
			{
				fwrite(&input_entry.size,input_entry.size,1,tfp);
			}
			else
			{
				input_entry.size-=2;
				if (input_entry.size<=4) /* be sure there is some data there */
				{
					input_entry.size=8;
					input_entry.gr_ph[0]='\0';
					input_entry.gr_ph[1]='\0';
					input_entry.gr_ph[2]='\0';
					input_entry.gr_ph[3]='\0';
				}
				k=input_entry.size;
				k=((k+3)>>2)<<2;
				k=k-input_entry.size;
				input_entry.size+=(k+2);
				fwrite(&input_entry.size,input_entry.size-k,1,tfp);
				fwrite(blanks,k,1,tfp);
			}
			
		}
#ifdef DEBUG2
		byte_p = (unsigned char *)(&input_entry.size);
		for (i=0;i<input_entry.size;++i)
		{
			printf("(%2x)",*byte_p++);
		}
		printf("\n");
#endif
		disk_entries[free_entry] = free_offset;
		free_entry += 1;
		free_offset += input_entry.size;
		total_bytes += input_entry.size;
   }
   fclose(infp);
   printf("\n                                              ");
   
   /*
   *  sort the entries onto 28 lists ...
   */
   sort_ents();
   printf("\r                                              ");
   
   /*
   * now, write out dictionary binary file ...  this is all index based, 
   * there are three tables written ...  the spelling/phonetic table, the
   * form class table, and the freqeuncy table ...
   */
   pcd.entries = header.no_of_entries;
   
   pcd.total = total_bytes - (pcd.entries*2); 
   /*   pcd.total = total_bytes; */
   
   if (compression==COMPRESSION)
   {
	   pcd.fc_entries=num_fc_entries;
   }
   
   if (endian==BIGENDIAN)
   {
	   pcd_big.entries=swap_endian_long(pcd.entries);
	   if (compression==COMPRESSION)
	   {
		   pcd_big.fc_entries=swap_endian_long(pcd.fc_entries);
	   }
	   pcd_big.total=swap_endian_long(pcd.total);
	   
	   if (compression==COMPRESSION)
	   {
		   fwrite(&pcd_big,sizeof(struct pc_dictionary),1,outfp);
	   }
	   else
	   {
		   fwrite(&pcd_big,sizeof(struct pc_dictionary_nc),1,outfp);
	   }
   }
   else
   {
	   if (compression==COMPRESSION)
	   {
		   fwrite(&pcd,sizeof(struct pc_dictionary),1,outfp);
	   }
	   else
	   {
		   fwrite(&pcd,sizeof(struct pc_dictionary_nc),1,outfp);
	   }
   }
   
   if (compression==COMPRESSION)
   {
	   if (endian==BIGENDIAN)
	   {
		   int i;
		   for (i=0;i<num_fc_entries;i++)
		   {
			   fc_entry_table[i]=swap_endian_long(fc_entry_table[i]);
		   }
		   fwrite(fc_entry_table,4,num_fc_entries,outfp);
	   }
	   else
	   {
		   fwrite(fc_entry_table,4,num_fc_entries,outfp);
	   }
   }
   
#ifdef DEBUG1
   byte_p = (unsigned char *)(&pcd);
   for (i=0;i<sizeof(struct pc_dictionary);++i)
   {
	   printf("[%2x]",*byte_p++);
   }
   printf("\n");
   if (compression==COMPRESSION)
   {
	   for (i=0;i<num_fc_entries;i++)
	   {
		   printf("%d 0x%08X\n",i,fc_entry_table[i]);
	   }
	   printf("\n");
   }
   
#endif
   
   /*
   *  write out the index table ...
   */
   if (target==MSDOS_FORMAT)
   {
	   addr = (long)pcd.entries*4;
   }
   else
   {
	   addr = 0;
   }
   count = 1;
   for(i=0;i<(28*28);i++)
   {
	   index = *(links+free_entry+i);
	   while(index != 0xffffffff)
	   {
		   if((count++ & 0xff) == 0)
		   {
			   printf("\r DIC_COMM; main;");
			   printf(" Writing index for entry %d",count-1);
		   }
		   if (target==MSDOS_FORMAT)
		   {
			   addr_186 = ((addr&0xffff0)<<12)+(addr&0xf);
		   }
		   else
		   {
			   addr_186=addr;
		   }
		   if (endian==BIGENDIAN)
		   {
			   addr_186= swap_endian_long(addr_186);
			   fwrite(&addr_186,4,1,outfp);
		   }
		   else
		   {
			   fwrite(&addr_186,4,1,outfp);
		   }
		   
#ifdef DEBUG5
		   byte_p = (unsigned char *)(&addr_186);
		   for (j=0;j<4;++j)
		   { 
			   printf("[%2x]",*byte_p++);
		   }
		   printf("(%x)\n",index);
#endif
		   read_ent((struct d_ent *)&input_entry.size,(unsigned int)index);
		   /*         addr += ((long)(input_entry.size-2)); */
		   if (compression==COMPRESSION)
		   {
			   addr += ((long)(input_entry.size-2-3)); 
		   }
		   else
		   {
			   addr += ((long)(input_entry.size-2)); 
		   }
		   
		   index = *(links+index);
	   }
   }
   printf("\r DIC_COMM; main;");
   printf(" Writing index for entry %d\n",count-1);
   printf("\r                                              ");
   
   /*
   *  write out the spell/pron table ..
   */
   count = 1;
   for(i=0;i<(28*28);i++)
   {
	   index = *(links+free_entry+i);
	   while(index != 0xffffffff)
	   {
		   if((count++ & 0xff) == 0)
		   {
			   printf("\r DIC_COMM; main;");
			   printf(" Writing text for entry %d",count-1);
		   }
		   read_ent((struct d_ent *)&input_entry.size,(unsigned int)index);
		   if (COMPRESSION==compression)
		   {
			   tempc = (char)input_entry.fc;
			   fwrite(&tempc,1,1,outfp);
			   fwrite(&input_entry.gr_ph,input_entry.size-2-4,1,outfp);
		   }
		   else
		   {
			   if (endian==BIGENDIAN)
			   {
				   input_entry.fc=swap_endian_long(input_entry.fc);
				   fwrite(&input_entry.fc,input_entry.size-2,1,outfp);
			   }
			   else
			   {
				   fwrite(&input_entry.fc,input_entry.size-2,1,outfp);
			   }
		   }
		   
		   
#ifdef DEBUG5
		   byte_p = (unsigned char *)(&input_entry.fc);
		   for (j=0;j<input_entry.size-2;++j)
		   {
			   printf("[%2x]",*byte_p++);
		   }
		   printf("(%x)\n",index);
#endif
		   index = *(links+index);
	   }
   }
   printf("\r DIC_COMM; main;");
   printf(" Writing text for entry %d\n",count-1);
   printf("\r                                              ");
   
   fclose(tfp);
#if defined _UNIX_LIKE_
   unlink("dic.tmp");
#else
   _unlink("dic.tmp");
#endif
   
   return(0);
}
                                                               
                                                               
                                                            
/*
 *  alphabetically sort the entries ingnoring case ...
 */
void sort_ents(void)
{
	unsigned char upper_char;
	volatile unsigned char   *is;
	volatile unsigned char   *cs;
	S32 i,j,count,curr;
	//S32 offset CAB 9/8/00 not used in code
	for(i=0;i<(28*28);i++)
		*(links+free_entry+i) = 0xffffffff;
	is = &input_entry.gr_ph[0];
	cs = &comp_entry.gr_ph[0];
	count = 1;
	
	for(i=free_entry-1;i>=0;i--)
	{
		if(((count++) % 100) == 0)
		{
			printf("\r DIC_COMM; sort_ents;");
			printf(" Sorting %d complete",count-1);
		}
		read_ent((struct d_ent *)&input_entry.size,(unsigned int)i);
		upper_char = case_upper[(*is)];
		if(upper_char < 'A')
			curr = 0;
		else
			if(upper_char > 'Z')
				curr = 27;
			else
				curr = upper_char-'A'+1;
#ifdef DEBUG1
			printf("upper_char (%c)(%d)\n",upper_char,curr);
#endif
			if(curr != 0 && curr != 27)
			{
				upper_char = case_upper[*(is+1)];
				curr = curr*28;
				if(upper_char < 'A')
					curr += free_entry;
				else if(upper_char > 'Z')
					curr += (free_entry+27);
				else
					curr += (free_entry+upper_char-'A'+1);
			}
			else
				curr = (curr*28)+free_entry;
			
			while(*(links+curr) != 0xffffffff)
			{
				read_ent((struct d_ent *)&comp_entry.size,(unsigned int)*(links+curr));
				
				for(j=0;
				(case_upper[*(is+j)] == case_upper[*(cs+j)] && *(is+j));j++)
				{
#ifdef DEBUG6			
					printf("input [%c], comp [%c], j [%d], *(is+j) [%d]\n",
						case_upper[*(is+j)],case_upper[*(cs+j)],j,*(is+j));
#endif
				};
				
#ifdef DEBUG6
				printf("\ninput (%c), comp (%c), j (%d)\n",case_upper[*(is+j)],case_upper[*(cs+j)],j);
#endif
				if(case_upper[*(cs+j)] >= case_upper[*(is+j)])
					break;
				curr = *(links+curr);
			}
			*(links+i) = *(links+curr);
			*(links+curr) = i;
	}
	
	/* display the last message for a total count */
	printf("\r DIC_COMM; sort_ents;");
	printf(" Sorting %d complete\n",count-1);
}
                                                
                                                
                                                
                                                
void read_ent(struct d_ent * ent, unsigned int index)
{
#ifdef DEBUG3
	printf("index (%d)(%d)(%d)\n",*(disk_entries+index),disk_entries,index);
#endif
	
	fseek(tfp,*(disk_entries+index),SEEK_SET);
	fread(&(*ent).size,sizeof(ent->size),1,tfp);
	fread(&(*ent).fc,(*ent).size,1,tfp);
	
#ifdef DEBUG3
	printf("entry (%d)(%d)\n",(*ent).fc,(*ent).size);
#endif
}                                               



unsigned char toph(unsigned char c)
{
	PTAB *ptp;
	
	if(c == 0)
		return(c);
	
	ptp = &ptab[0];
	while (ptp < &ptab[ntab] && ptp->p_graph!=c)
		++ptp;
	if (ptp == &ptab[ntab])
	{                                      
		printf("\n DIC_COMM; toph; line %ld; Bad phone == %02X\n",linenumber, c);
		ptp--;
		printf("\n DIC_COMM; toph; line %ld; Bad phone == %c\n",linenumber, ptp->p_graph);
		exit (1);
		return(0xff);
	}
	return(ptp->p_phone);
}




unsigned char from_ph(unsigned char c)
{
	PTAB *ptp;
	
	ptp = &ptab[0];
	while (ptp<&ptab[ntab] && ptp->p_phone!=c)
		++ptp;
	return(ptp->p_graph);
}      

unsigned char *form_class_strings[] = {
   " adj",
   " adv",
   " art",
   " aux",
   " be",
   " bev",
   " conj",
   " ed",
   " have",
   " ing",
   " noun",
   " pos",
   " prep",
   " pron",
   " subj",
   " that",
   " to",
   " verb",
   " who",
   " neg",
   " intr",
   " ref",
   " part",
   " func",
   " cont",
   " char",
   " refr",
   " unused",
   " unused",
   " mark",
   " cont",
   " homo",
};



	
void print_fc(long fc_val, FILE *fp)
{
	int i;
	//int j; 9/8/00 CAB Not used in code
	long fc_mask;
	
	if(fc_val)
	{
		fc_mask = 1;
		for(i=0;i<32;i++)
		{
			if(fc_val & fc_mask)
				fprintf(fp,"%s",form_class_strings[i]);
            fc_mask = fc_mask*2;
		}
	}
	else
		fprintf(fp," none");
}




void print_tf(long val, FILE *fp)
{
	if(val)
		fprintf(fp,",T");
	else
		fprintf(fp,",F");
}



void quote_string(unsigned char * str)
{
	int i;
	// int j; CAB 9/8/00 Not used in code
	unsigned char q;
	
	q = (str[0] == '"') ? '\'' : '"';
	for(i=0;str[i];i++);
	str[i+1] = q;
	str[i+2] = 0;
	while(i)
	{
		str[i] = str[i-1];
		i--;
	}
	str[0] = q;
}

unsigned long swap_endian_long(unsigned long in)
{
	unsigned long out=0;
	int i;
	
	for (i=0;i<4;i++)
	{
		out|=(in&0x000000ff);
		if (i<3)
		{
			out<<=8;
			in>>=8;
		}
	}
	return(out);
}

unsigned short swap_endian_short(unsigned short in)
{
	unsigned short out=0;
	
	out|=(in&0x00ff);
	out<<=8;
	in>>=8;
	out|=(in&0x00ff);
	return(out);
}
