#ifndef MANDARIN_PROTOTYPES_H
#define MANDARIN_PROTOTYPES_H

int Mand_F0_machine(LPTTS_HANDLE_T, MFZ_Code, void *, int,int,int);
int GetBaseF0(LPTTS_HANDLE_T);
MandSyll *newMand_Syll(LPTTS_HANDLE_T);
double  mand_duration_calc(LPTTS_HANDLE_T phTTS, char *, double * , int, float, int);

#define MANDF0MACHINE
#ifndef	QTAF0MODEL
#define QTAF0MODEL
#endif

#endif 
