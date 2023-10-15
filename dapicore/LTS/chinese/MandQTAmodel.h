/* 

   Header file for mandqtamodel.c
   Copyright (C) <2006>  
    Reiner Wilhelms-Tricarico @ Fonix Corp 
	Based on published and to be published 
	information provided by Yi Xu. 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/


#ifndef MANDQTAMODEL_H
#define MANDQTAMODEL_H

typedef struct _tagMandarinSyllF0Interval
{  
    float pdur;                 // relative duration in syll (e.g., 0.3)
	double omega, damp;       
	double a,b,c,d;         // a t + b  + c for now. (QTA model)
	double gamma,delta,tau,c1,c2;

    short nframes;              // number of frames active.
    short phonemeindex;
    short parentsyll;           // # of syllable in which this interval was generated.
	short tone;                 // tone number to which this interval corresponds to. 
//	struct _tagMandarinSyllF0Interval *pNext;
} MandF0ControlInterval;



typedef struct _tagMandF0filter
{
	double yn,yn1,yn2,yn3;
	double un,un1,un2;
	double gamma, delta, tau, lambda;  // ('nuf greek? REWT;-)
	double c1,c2;   
}
MandF0filter;

/* The following definition of frame duration is here
   for convenience as it does not change in the 
   application where the QTA model is used.
*/

#ifndef FRAMEDURATION 
#define FRAMEDURATION 0.00640
#define MILLISECONDSPERFRAME 6.40
#endif

void make_digital_QTA_parameters(MandF0ControlInterval *);
void reset_mand_f0_filter(MandF0filter*, double );
double shift_f0_filter_state(MandF0filter*, double);

#endif  /* 	MANDQTAMODEL_H */
