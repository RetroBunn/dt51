/* 

   mandqtamodel.c
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


#include "mandQTAmodel.h"

//#define OLD_QTA_IMPLEMENTATION
  
/* think of these as relative f0 change per second */
/* They are used in the subroutine that makes gestures:
   make_tonal_gestures */


void reset_mand_f0_filter(MandF0filter *F,   double Fref)
{
	F->un=F->un1=F->un2 = Fref;
	F->yn=F->yn1=F->yn2=F->yn3=Fref;
	F->lambda = 400.0;             /* later modified in each interval */
}
/* shift state, store input and output, and return new output */
 
#ifdef OLD_QTA_IMPLEMENTATION
double shift_f0_filter_state(MandF0filter *F, double u)
{
	F->un2 = F->un1;
	F->un1 = F->un;
	F->un = u * F->lambda;
	F->yn3=F->yn2;
	F->yn2=F->yn1;
	F->yn1=F->yn;
	F->yn = F->gamma*((F->un - F->yn1) + 2.0*(F->un1 - F->yn2) + (F->un2 - F->yn3)) 
			- F->c1 * F->yn1 - F->c2 * F->yn2;
	return F->yn;
}
#else
double shift_f0_filter_state(MandF0filter *F, double u)
{
	F->un2 = F->un1;
	F->un1 = F->un;
	F->un = u;
	F->yn3=F->yn2;
	F->yn2=F->yn1;
	F->yn1=F->yn;
	F->yn = F->gamma*(F->un + F->un1 + F->un1 + F->un2 - F->yn3) - F->c1 * F->yn1 - F->c2 * F->yn2;
	return F->yn;
}
#endif

/* for the QTAmodel we'll define filter coefficients. */



/* make_digital_QTA_parameters:

   Convert analog parameters of the QTA dynamic system into
   digital filter coefficients 
   
	 c(1) = 4/T^2 + 4*omega*damp/T + omega^2;
	 c(2) = 2*omega^2 - 8/T^2;
	 c(3) = 4/T^2 - 4*omega*damp/T + omega^2;
	 a0 = c(1);
	 gamma = 1/a0.
*/    
#ifdef OLD_QTA_IMPLEMENTATION

#define MANDQTA_P1 (4.0/FRAMEDURATION)
#define MANDQTA_P2 (4.0/(FRAMEDURATION*FRAMEDURATION))
#define MANDQTA_P3 (8.0/(FRAMEDURATION*FRAMEDURATION))

void make_digital_QTA_parameters(MandF0ControlInterval *I)
{
	double a0,a1,a2;
	double om2,omd;
	om2 = I->omega*I->omega;
    omd = I->damp * I->omega * MANDQTA_P1;

	a0 = MANDQTA_P2 + omd + om2;
	a2 = MANDQTA_P2 - omd + om2;
	a1 = 2.0*om2 - MANDQTA_P3;
	I->gamma = 1.0/a0;
	I->c1 = a1*I->gamma;
	I->c2 = a2*I->gamma;
}

#else 

#define MANDQTA_T 0.0064
#define MANDQTA_4T (MANDQTA_T * 4.0)
#define MANDQTA_TT (MANDQTA_T*MANDQTA_T)


void make_digital_QTA_parameters(MandF0ControlInterval *I)
{
	double d, dp4,dm4, a0;

	d = MANDQTA_4T * I->damp * I->omega;
	dp4 = d + 4.0;
	dm4 = d - 4.0;
     
	a0 = MANDQTA_TT * I->omega * I->omega / dp4;

	I->gamma = a0;
	I->c1 = a0 - 8.0/dp4;
	I->c2 = a0 + a0 - dm4/dp4;
}

#endif 

/* 
The following stripped down piece of code is cited here to demonstrate how
the F0 contour is generated. This is similar to an implementation 
in Dectalk (Fonix Corp). 

Explanation:
During synthesis, the subroutine below is called for each frame to compute
a new value of F0. The structure MandF0Machine contains a list of 
control intervals. In each control interval the coefficients 
for the F0 control are constant, and the coefficients (a,b, and c) are
used to compute the control u. as u = a*t + b + c which are defined 
for the interval. The structure also contains the timing information
(ctime within a control interval, and framesleft) so a new 
interval can be used if the control current control interval expires.
*/

#ifdef CITED_CODE_EXAMPLE 

double	F0_contour_point(MandF0Machine *M)
{
	float fzero;
	int tone;
	double u;
	MandF0ControlInterval *I;


	M->framesleft -= 1;
	if (M->framesleft <= 0) 
	{
	if (M->currentinterval < (M->numintervals-1)) M->currentinterval += 1;
	else return M->lastF0;

	I = &(M->Mandintervals[M->currentinterval]);
	M->a = I->a;
	M->b = I->b;
	M->c = I->c;

	M->F0filt.c1 = I->c1;
	M->F0filt.c2 = I->c2;
	M->F0filt.gamma = I->gamma;
	M->framesleft = I->nframes;
	M->ctime = 0.0;
	}

	u = M->a * M->ctime + M->c;	  /* ramp plus offset control */

	fzero = shift_f0_filter_state(&(M->F0filt),u);
	M->lastF0 = fzero;
	M->ctime = M->ctime + FRAMEDURATION;
	return fzero;
}

#endif /* example */