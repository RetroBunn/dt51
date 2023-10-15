#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "epsonapi.h"
//#pragma import(__use_no_semihosting_swi)

short buffer[71];
short bigbuf[71*61*14];
int bigbufloc=0;
int resetcount=40;

#if defined WIN32 || defined WIN32_TEST
FILE *outfile;
#endif

int count;

short *callback(short *output_buf,long error)
{
	int i;
	unsigned long j;
count++;
if (error==3)
{
	return(3);
}
memcpy(&bigbuf[bigbufloc],buffer,71*2);
bigbufloc+=71;
if (count== resetcount)
{
	count=0;
	return(NULL);
}
//if (count==100)
//return(NULL);
#if defined WIN32 || defined WIN32_TEST
fwrite(output_buf,2,71,outfile);
#endif
#if 0
	int i;
	unsigned long j;
	for (i=0;i<71;i++)
	{
		j=output_buf[i];
		if (i && i%8==0)
		{
			printf("\n");
		}
		printf("0x%04X ",j&0xFFFF);
	}
	printf("\n");
#endif
	return(output_buf);
}
extern const unsigned char user_dict[];
//extern const unsigned char user_dict_us[];
//extern const unsigned char user_dict_sp[];
//extern const unsigned char user_dict_la[];
//extern const unsigned char user_dict_gr[];
//extern const unsigned char user_dict_fr[];

short ursula_spdefs[59] = {
0,
60,
100,
240,
100,
0,
70,
5,
0,
100,
4150,
260,
4850,
1200,
4300,
4900,
76,
76,
71,
0,
68,
63,
54,
61,
77,
60,
18,
50,
30,
1,
32,
300,
800,
1500,
0,
55,
0,
120,
130,
140,
230,
340,
250,
220,
250,
200,
4800,
1200,
20,
80,
100,
900,
110,
0,
1,
8,
5,
1180,
650
};

short rita_spdefs[59] = {
0,
44,
65,
106,
80,
36,
20,
10,
1,
110,
4000,
250,
4800,
700,
4100,
4700,
77,
77,
72,
87,
68,
64,
56,
58,
79,
0,
10,
0,
30,
20,
32,
500,
700,
1900,
0,
60,
0,
100,
120,
100,
230,
340,
250,
320,
260,
260,
4800,
1200,
20,
80,
100,
800,
110,
0,
0,
0,
5,
1180,
650};

short wendy_spdefs[59] = {
0,
80,
50,
200,
80,
5,
0,
10,
0,
105,
4200,
400,
4800,
600,
4200,
4800,
65,
60,
70,
87,
78,
69,
65,
61,
64,
100,
0,
80,
20,
18,
22,
850,
1100,
2500,
30,
75,
0,
120,
130,
140,
230,
340,
250,
220,
250,
200,
4800,
1200,
20,
80,
100,
900,
110,
0,
1,
2,
4,
1180,
650 };

short harry_spdefs[59]={
1,
62,
10,
95,
90,
0,
30,
20,
0,
100,
3500,
200,
3850,
180,
3200,
4000,
73,
73,
70,
87,
68,
62,
55,
65,
78,
10,
5,
0,
15,
10,
22,
500,
800,
2300,
0,
50,
0,
100,
120,
130,
230,
340,
250,
320,
260,
260,
4990,
1200,
50,
80,
400,
800,
100,
0,
0,
2,
5,
1280,
540};

int main()
{
	char temps[100];
	int i;
#ifdef EPSON_ARM7
	LPTTS_HANDLE_T phTTS;
	PKSD_T pKsd_t;
	PCMD_T pCmd_t;
	PLTS_T pLts_t;
	PDPH_T pDph_t;
	PDPHSETTAR_ST pDphsettar;
	PVTM_T pVtm_t;

	short phoneme_ptr[1000];
	char *input_pos;

	SPEAKER_DEF_T *spdefs[10];

	int num_phones;

	short output[100];
	int return_code=1;

#if defined WIN32 || defined WIN32_TEST
	FILE *outfile;
#endif
	char input[]="[:mode math on] [:punct some] [:phoneme arpabet speak on]this is a test of the emergency broadcast system. "; //a toy a test a car a rake a mouse a elephant. ";//This is not [:phon arpa on] a test. [:rate 350] I have five coins. My name is eve. ";
	//"[:mode math on] [:punct some] [:phoneme arpabet speak on][:name 3]this is a test of the emergency broadcast system. " //a toy a test a car a rake a mouse a elephant. ";//This is not [:phon arpa on] a test. [:rate 350] I have five coins. My name is eve. ";
	//"[:mode math on] [:punct some] [:phoneme arpabet speak on][:name 4]this is a test of the emergency broadcast system. " //a toy a test a car a rake a mouse a elephant. ";//This is not [:phon arpa on] a test. [:rate 350] I have five coins. My name is eve. ";
	//"[:mode math on] [:punct some] [:phoneme arpabet speak on][:name 5]this is a test of the emergency broadcast system. " //a toy a test a car a rake a mouse a elephant. ";//This is not [:phon arpa on] a test. [:rate 350] I have five coins. My name is eve. ";
	//"[:mode math on] [:punct some] [:phoneme arpabet speak on][:name 6]this is a test of the emergency broadcast system. "; //a toy a test a car a rake a mouse a elephant. ";//This is not [:phon arpa on] a test. [:rate 350] I have five coins. My name is eve. ";
	char gr_input[]="computer katze pferd. ";//ich sie nach hause einladen?";
	char fr_input[]="chat porte ordinateur cheval. ";//vous coucher avec moi ce soir.";// una inmejorable relacion [:name 3]entre la inteligebilidad en el habla sintetizada por su sistema y la cantidad de memoria requerida para su implementacion";
	char la_input[]="caballo computadora puerta gato. ";//inmejorable relacion entre la inteligebilidad";

	count=0;



	phTTS=calloc(sizeof(TTS_HANDLE_T),1);
	pKsd_t=calloc(sizeof(KSD_T),1);
	pCmd_t=calloc(sizeof(CMD_T),1);
	pLts_t=calloc(sizeof(LTS_T),1);
	pDph_t=calloc(sizeof(DPH_T),1);
	pDphsettar=calloc(sizeof(DPHSETTAR_ST),1);
	pVtm_t=calloc(sizeof(VTM_T),1);


	for (i=0;i<10;i++)
	{
		spdefs[i]=calloc(sizeof(SPEAKER_DEF_T),1);
	}

#endif

count=0;
#if defined WIN32 || defined WIN32_TEST
	outfile=fopen("output.pcm","wb");
	if (outfile==NULL)
	{
		exit(0);
	}
#endif
#ifndef EPSON_ARM7
	memset(bigbuf,0,71*61*14*2);
	strcpy(temps,"[:phon arpa on][:dv ap 100][:i m 10]");
//	i=strlen(temps);
	temps[0]=0x0b;
	temps[1]='\0';
	TextToSpeechInit(callback,user_dict);
//	TextToSpeechStart("Parlez vous français. ",buffer,WAVE_FORMAT_1M16);
//	TextToSpeechStart("this [:i m 20] is [:i m 30] a [:i m 40] test [:i m 50] of [:i m 60] the [:i m 70] emergency [:i m 80] broadcast [:i m 90] system. [:i m 100]",buffer,WAVE_FORMAT_1M16,1);
//	TextToSpeechStart("This is a test [:vol att 0] of the emergency broadcast system.[:sync]",buffer,WAVE_FORMAT_1M16,1);
//	TextToSpeechStart("test. [:flush all] test. ",buffer,WAVE_FORMAT_1M16,1);
	resetcount=40;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] This",buffer,WAVE_FORMAT_1M16,1);
	resetcount=30;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] fubble",buffer,WAVE_FORMAT_1M16,1);
	resetcount=50;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] This",buffer,WAVE_FORMAT_1M16,1);
	resetcount=20;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] fubble",buffer,WAVE_FORMAT_1M16,1);
	resetcount=24;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] This",buffer,WAVE_FORMAT_1M16,1);
	resetcount=35;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] fubble",buffer,WAVE_FORMAT_1M16,1);
	resetcount=43;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] This",buffer,WAVE_FORMAT_1M16,1);
	resetcount=53;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] fubble",buffer,WAVE_FORMAT_1M16,1);
	resetcount=51;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] This",buffer,WAVE_FORMAT_1M16,1);
	resetcount=47;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] fubble",buffer,WAVE_FORMAT_1M16,1);
	resetcount=25;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] This",buffer,WAVE_FORMAT_1M16,1);
	resetcount=42;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] fubble",buffer,WAVE_FORMAT_1M16,1);
	resetcount=49;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] This",buffer,WAVE_FORMAT_1M16,1);
	resetcount=36;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] fubble",buffer,WAVE_FORMAT_1M16,1);
	TextToSpeechReset(1);
	resetcount=63;
	TextToSpeechStart("[:ERROR IGNORE] [:PUNC NONE] [:MODE MATH OFF] [:MODE SPELL OFF] [:SAY CLAUSE] [:TIMEOUT 5][:I R 1][:np :dv ap 122][:ra406][:vs 35][:I R 1] This is",buffer,WAVE_FORMAT_1M16,1);
//	TextToSpeechStart("[:i m 10]",buffer,WAVE_FORMAT_1M16,0);
	TextToSpeechStart(temps,buffer,WAVE_FORMAT_1M16,0);
//	printf("returned from start\n");
	count++;
//	TextToSpeechReset();
	count++;
//	TextToSpeechStart("test of fred. ",buffer,WAVE_FORMAT_1M16);
	count++;
#else

//	printf("calling init\n");
	for (i=0;i<10;i++)
	{
		TextToSpeechGetSpeakerDef(spdefs[i]);
	//	spdefs[i]->average_pitch+=i*10;
	//	spdefs[i]->sex=(i+1)%2;
	}

	//memcpy(spdefs[3],&harry_spdefs,sizeof(harry_spdefs));
	//memcpy(spdefs[4],&ursula_spdefs,sizeof(harry_spdefs));
	//memcpy(spdefs[5],&rita_spdefs,sizeof(harry_spdefs));
	//memcpy(spdefs[6],&wendy_spdefs,sizeof(harry_spdefs));
	//spdefs[3]->loudness+=3;

	TextToSpeechInitTTP(phTTS,pKsd_t,pCmd_t,pLts_t,user_dict,LANG_ENGLISH_US,1);
//	TextToSpeechInit(callback,user_dict);
//	printf("calling start\n");
	memset(phoneme_ptr,0,1000);

	num_phones=TextToSpeechStartTTP(phTTS,input,phoneme_ptr,500,&input_pos);
	memset(pCmd_t,0,sizeof(CMD_T));
	//memset(pLts_t,0,sizeof(LTS_T));


	TextToSpeechInitPTS(phTTS,pKsd_t,pDph_t,pDphsettar,pVtm_t,spdefs,WAVE_FORMAT_1M16,1);

	return_code=PTS_OUTPUT;

	while (return_code==PTS_OUTPUT)
	{
		count++;
		return_code=TextToSpeechStartPTS(phTTS,phoneme_ptr,num_phones,output);
		if (return_code==PTS_OUTPUT)
		{
#if defined WIN32 || defined WIN32_TEST
		fwrite(output,71,2,outfile);
#endif
		}
	}

	while (*input_pos)
	{
		memset(phoneme_ptr,0,1000);
		
		num_phones=TextToSpeechStartTTP(phTTS,input_pos,phoneme_ptr,500,&input_pos);
		memset(pCmd_t,0,sizeof(CMD_T));
		//memset(pLts_t,0,sizeof(LTS_T));
		
		return_code=PTS_OUTPUT;
		while (return_code==PTS_OUTPUT)
		{
			count++;
			return_code=TextToSpeechStartPTS(phTTS,phoneme_ptr,num_phones,output);
			if (return_code==PTS_OUTPUT)
			{
#if defined WIN32 || defined WIN32_TEST
			fwrite(output,71,2,outfile);
#endif
			}
		}
	}

	
	TextToSpeechInitTTP(phTTS,pKsd_t,pCmd_t,pLts_t,user_dict,LANG_GERMAN,0);
//	TextToSpeechInit(callback,user_dict);
//	printf("calling start\n");
	memset(phoneme_ptr,0,1000);

	num_phones=TextToSpeechStartTTP(phTTS,gr_input,phoneme_ptr,500,&input_pos);

	TextToSpeechInitPTS(phTTS,pKsd_t,pDph_t,pDphsettar,pVtm_t,spdefs,WAVE_FORMAT_1M16,1);

	return_code=PTS_OUTPUT;

	while (return_code==PTS_OUTPUT)
	{
		count++;
		return_code=TextToSpeechStartPTS(phTTS,phoneme_ptr,num_phones,output);
		if (return_code==PTS_OUTPUT)
		{
#if defined WIN32 || defined WIN32_TEST
		fwrite(output,71,2,outfile);
#endif
		}
	}

	while (*input_pos)
	{
		memset(phoneme_ptr,0,1000);
		
		num_phones=TextToSpeechStartTTP(phTTS,input_pos,phoneme_ptr,500,&input_pos);
		
		return_code=PTS_OUTPUT;
		while (return_code==PTS_OUTPUT)
		{
			count++;
			return_code=TextToSpeechStartPTS(phTTS,phoneme_ptr,num_phones,output);
			if (return_code==PTS_OUTPUT)
			{
#if defined WIN32 || defined WIN32_TEST
			fwrite(output,71,2,outfile);
#endif
			}
		}
	}


	TextToSpeechInitTTP(phTTS,pKsd_t,pCmd_t,pLts_t,user_dict,LANG_LATIN_AMERICAN,0);
//	TextToSpeechInit(callback,user_dict);
//	printf("calling start\n");
	memset(phoneme_ptr,0,1000);

	num_phones=TextToSpeechStartTTP(phTTS,la_input,phoneme_ptr,500,&input_pos);

	TextToSpeechInitPTS(phTTS,pKsd_t,pDph_t,pDphsettar,pVtm_t,spdefs,WAVE_FORMAT_1M16,1);

	return_code=PTS_OUTPUT;

	while (return_code==PTS_OUTPUT)
	{
		count++;
		return_code=TextToSpeechStartPTS(phTTS,phoneme_ptr,num_phones,output);
		if (return_code==PTS_OUTPUT)
		{
#if defined WIN32 || defined WIN32_TEST
		fwrite(output,71,2,outfile);
#endif
		}
	}

	while (*input_pos)
	{
		memset(phoneme_ptr,0,1000);
		
		num_phones=TextToSpeechStartTTP(phTTS,input_pos,phoneme_ptr,500,&input_pos);
		
		return_code=PTS_OUTPUT;
		while (return_code==PTS_OUTPUT)
		{
			count++;
			return_code=TextToSpeechStartPTS(phTTS,phoneme_ptr,num_phones,output);
			if (return_code==PTS_OUTPUT)
			{
#if defined WIN32 || defined WIN32_TEST
			fwrite(output,71,2,outfile);
#endif
			}
		}
	}

	TextToSpeechInitTTP(phTTS,pKsd_t,pCmd_t,pLts_t,user_dict,LANG_FRENCH,0);
//	TextToSpeechInit(callback,user_dict);
//	printf("calling start\n");
	memset(phoneme_ptr,0,1000);

	num_phones=TextToSpeechStartTTP(phTTS,fr_input,phoneme_ptr,500,&input_pos);

	TextToSpeechInitPTS(phTTS,pKsd_t,pDph_t,pDphsettar,pVtm_t,spdefs,WAVE_FORMAT_1M16,1);

	return_code=PTS_OUTPUT;

	while (return_code==PTS_OUTPUT)
	{
		count++;
		return_code=TextToSpeechStartPTS(phTTS,phoneme_ptr,num_phones,output);
		if (return_code==PTS_OUTPUT)
		{
#if defined WIN32 || defined WIN32_TEST
		fwrite(output,71,2,outfile);
#endif
		}
	}

	while (*input_pos)
	{
		memset(phoneme_ptr,0,1000);
		
		num_phones=TextToSpeechStartTTP(phTTS,input_pos,phoneme_ptr,500,&input_pos);
		
		return_code=PTS_OUTPUT;
		while (return_code==PTS_OUTPUT)
		{
			count++;
			return_code=TextToSpeechStartPTS(phTTS,phoneme_ptr,num_phones,output);
			if (return_code==PTS_OUTPUT)
			{
#if defined WIN32 || defined WIN32_TEST
			fwrite(output,71,2,outfile);
#endif
			}
		}
	}
	
	//	TextToSpeechStart("Parlez vous français. ",buffer,WAVE_FORMAT_1M16);
//	printf("returned from start\n");
	count++;
//	TextToSpeechReset();
//	TextToSpeechStart("test of fred. ",buffer,WAVE_FORMAT_1M16);
#endif
	count++;
#if defined WIN32 || defined WIN32_TEST
	fclose(outfile);
#endif
	return 0;
}


void __raise()
{
while (1);
}
