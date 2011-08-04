

//============================================================================
// Name        : ButterWorthLowPassFilter.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
#include <iostream>
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}*/
/**************************************************************
*        Program to demonstrate the Butterworth filter        *
*           (removing frequencies greater then Fc)            *
*                                                             *
*                         C++ version by J-P Moreau, Paris    *
* ----------------------------------------------------------- *
* SAMPLE RUN:                                                 *
*                                                             *
* Input data file (tfft.dat):                                 *
*                                                             *
* (The test signalInData contains 3 frequencies: 50, 250, 500 hz)   *
*                                                             *
* 1024                                                        *
* 0.00000000000000E+0000   0.00000000000000E+0000             *
* 1.95503421309917E-0004   3.53914399999776E+0001             *
* 3.91006842619834E-0004   5.95684899999760E+0001             *
* 5.86510263929974E-0004   6.54621699999552E+0001             *
* 7.82013685239669E-0004   5.24038399999845E+0001             *
* ...                      ...                                *
* 1.98826979472187E-0001   2.77372500000183E-0001             *
* 1.99022482893497E-0001  -2.43361500000174E+0000             *
* 1.99217986314807E-0001  -4.84236799999780E+0000             *
* 1.99413489736116E-0001  -6.02247899999929E+0000             *
* 1.99608993157426E-0001  -5.45615399999951E+0000             *
* 1.99804496578736E-0001  -3.22824200000105E+0000             *
* 2.00000000000045E-0001  -2.96010699999982E-0003             *
*                                                             *
* Output file (tfilter.lst):                                  *
*                                                             *
*        Time        Input signalInData      Filtered signalInData        *
*  -------------------------------------------------------    *
*      0.0000         0.000000           0.000000             *
*      0.0002        35.391440           0.158005             *
*      0.0004        59.568490           1.278083             *
*      0.0006        65.462170           5.003994             *
*      0.0008        52.403840          12.809453             *
*      0.0010        26.229620          24.336649             *
*      ...           ...                ...                   *
*      0.1988         0.277373          -2.224546             *
*      0.1990        -2.433615          -0.802179             *
*      0.1992        -4.842368           0.588941             *
*      0.1994        -6.022479           1.320860             *
*      0.1996        -5.456154           1.036090             *
*      0.1998        -3.228242          -0.213007             *
*      0.2000        -0.002960          -1.978450             *
*                                                             *
* Note: The cut off frequency Fc is 500 hz, the filter order  *
*       is 4 (A Fourier analysis of the filtered signalInData shows *
*       that frequencies greater than Fc are satisfactorily   *
*       removed but with a slight time shift of the signalInData).  *
**************************************************************/
#include "ButterworthLowPassFilter.h"

#include <stdio.h>
#include <math.h>

#define  MACH_EPS  1e-12
#define  SIZE      401

Filter_Coef C;
Memory_Coef D;

FILE     *f_in, *f_out;
int      i,order,ndata;
double   dt,Fc,t,temp,tbegin,tend,yy;
double   signalInData[SIZE],filtered[SIZE];
char myResult[SIZE];


int      NSections;
double   Tg,Xdc;


ButterworthLowPassFilter::ButterworthLowPassFilter() {
	// TODO Auto-generated constructor stub

}

ButterworthLowPassFilter::~ButterworthLowPassFilter() {
	// TODO Auto-generated destructor stub
}


/**********************************************************************
*          Filtering a signalInData F(t) by Butterworth method              *
*             (removing frequencies greater then Fc)                  *
* ------------------------------------------------------------------- *
* Calling mode:   Filter(Xs,Xd,NSections,C,D);                        *
* ------------------------------------------------------------------- *
* INPUTS:                                                             *
* -------                                                             *
*        Xd.......:  current value of input signalInData (double)           *
*        NSections: Number of required 2nd order sections (integer)   *
*                   = n/2     for n even                              *
*                   = (n+1)/2 for n odd                               *
*        n........: order of filter (1 to 4)                          *
*        C........: Table[1..5,1..NSections] of filter coefficients   *
*                   calculated previously by BUTTERWORTH procedure    *
*        D........: Table[1..2,1..NSections] of coefficients defining *
*                   the filter memory, initialized by INIT procedure. *
* ------------------------------------------------------------------- *
* OUTPUTS:                                                            *
* -------                                                             *
*        D........: Table updated after the call to Filter procedure  *
*        Xs.......: current value of filtered signalInData (double)         *
* ------------------------------------------------------------------- *
* Référence                                                           *
* ---------                                                           *
*  "Lawrence R.Rabiner et Bernard Gold                                *
*   Theory and application of digital processing.                     *
*   Prentice Hall Inc., EnglewoodclIFfs,NEW JERSEY,1975" [BIBLI 15].  *
*                                                                     *
*                                   C++ version by J-P Moreau, Paris  *
*               from Fortran version by J-P Dumont / Tuan Dang Trong  *
**********************************************************************/
void ButterworthLowPassFilter::Filter( double *Xs,double Xd, int NSections,
 	         Filter_Coef C, Memory_Coef D )  {
  double x,y,err;
  int i;
  x=Xd;
  for (i=1; i<NSections+1; i++) {
    err=x+C[1][i]*D[1][i]+C[2][i]*D[2][i];
    y=C[5][i]*(err +C[3][i]*D[1][i]+C[4][i]*D[2][i]);
    D[2][i]=D[1][i];
    D[1][i]=err;
    x=y;
  }
  *Xs=x;
}

/*************************************************************************
*                       INIT FILTER PROCEDURE                            *
* ---------------------------------------------------------------------- *
* The filter response is initialized to stationnary value for a constant *
* input signalInData value.                                                    *
*                                                                        *
* Calling mode:   INIT(Xdc,C,NSections,D);                               *
* ---------------------------------------------------------------------- *
* INPUTS:                                                                *
* ------                                                                 *
*        Xdc......: constant input value (double)                        *
*        C........: Table[1..5,1..NSections] of filter coefficients      *
*                   calculated previously by BUTTERWORTH procedure       *
*        NSections: Number of required 2nd order sections (integer)      *
*                   = n/2     for n even                                 *
*                   = (n+1)/2 for n odd                                  *
*        n........: order of filter (1 to 4)                             *
* ---------------------------------------------------------------------- *
* OUTPUTS:                                                               *
* -------                                                                *
*        D........: Table[1..2,1..NSections] of coefficients defining    *
*                   the filter memory, initialized by INIT procedure.    *
*************************************************************************/
void ButterworthLowPassFilter::Init(double Xdc, Filter_Coef C, int NSections, Memory_Coef D) {
  double dc,Csum;
  int i,j;
  dc=Xdc;
  for (j=1; j<NSections+1; j++) {
    D[2][j]=dc/(1-C[1][j]-C[2][j]);
    D[1][j]=D[2][j];
    Csum=0;
    for (i=1; i<5; i++) Csum=Csum + C[i][j];
    dc=C[5][j]*(dc+D[2][j]*Csum);
  } //j loop
} // Init()


/*********************************************************************
*          Calculates the Butterworth filter coefficients            *
* ------------------------------------------------------------------ *
*  Calling mode:   Butterworth(Fc,Ts,n,C,NSections,Tg);              *
* ------------------------------------------------------------------ *
*  INPUTS:                                                           *
*  ------                                                            *
*         Fc.......: Cut off frequency                               *
*         Ts.......: Sampling time of input signalInData                   *
*         n........: Order of filter                                 *
* ------------------------------------------------------------------ *
*  OUTPUTS:                                                          *
*  -------                                                           *
*         C........: Table[1..5,1..NSections] of filter coefficients *
*                    calculated previously by BUTTERWORTH procedure  *
*         NSections: Number of required 2nd order sections (integer) *
*                    = n/2     for n even                            *
*                    = (n+1)/2 for n odd                             *
*         Tg.......: Group delay in seconds                          *
*********************************************************************/
void ButterworthLowPassFilter::Butterworth(double Fc,double Ts,int n,Filter_Coef C,
                 int *NSections, double *Tg )  {
  int Ns2,i,Modn;
  double Arg,Rep,Omega,OmegaSq,temp,W0,W1,m;
  double Zero,ONE,TWO,HALF,Pi;

  Zero = 0;
  ONE  = 1;
  TWO  = 2;
  HALF = 0.5;
  Pi   = 3.1415926535;

  Arg=Pi*Ts*Fc;
  if (fabs(Arg) > 2.0*Pi) {
    m=int(Arg/2.0/Pi);
    Arg=Arg-(m*2.0*Pi);
  }
  Omega= tan(Arg);
  OmegaSq=Omega*Omega;
  Modn=(n % 2);
  if (Modn==0)
	temp=HALF;
  else
	temp=Zero;
  Ns2=n/2;
  *NSections=Ns2+Modn;
  *Tg=Zero;
  if (n>1)
    for (i=1; i<Ns2+1; i++) {
      Rep=Omega*cos(Pi*(i-temp)/n);
      *Tg=*Tg+Ts*Rep/OmegaSq;
      W0=TWO*Rep;
      W1=ONE +W0+OmegaSq;
      C[1][i]=-TWO*(OmegaSq-ONE)/W1;
      C[2][i]=-(ONE-W0+OmegaSq)/W1;
      C[3][i]=TWO;
      C[4][i]=ONE;
      C[5][i]=OmegaSq/W1;
    }
    if (temp == Zero) {
      C[1][*NSections]=(ONE-Omega)/(ONE+Omega);
      C[2][*NSections]= Zero;
      C[3][*NSections]= ONE;
      C[4][*NSections]= Zero;
      C[5][*NSections]= Omega/(ONE+Omega);
      *Tg= *Tg+Ts/(TWO*Omega);
    }
} // Butterworth()


void ButterworthLowPassFilter::test(char* inArray, int dataLength, char*outArray) {
	int i;
	ndata = 399;
	for (i = 0; i < ndata + 1; i++)
		signalInData[i] = (double)inArray[i];
	//calculate sampling increment dt of input signalInData
	dt = 0.0002;

	Fc=500.0; order=4; Xdc=0; //no constant value

	//call filtering procedures
	// 1. Calculate the filter coefficients
	Butterworth(Fc,dt,order,C,&NSections,&Tg);
	Init(Xdc,C,NSections,D);

	for (i=1; i<ndata+1; i++) {
	    Filter(&temp,signalInData[i],NSections,C,D);
	    filtered[i]=temp;
	    if(filtered[i] >= 255.f)
	    	outArray[i] = 255;
	    else if (filtered[i] < 0.f)
	    	outArray[i] = 0;
	    else
	    	outArray[i] = (char)(filtered[i] + 0.5);
	  }
}
/*
int main()  {
	f_out = fopen("tfilter.lst","w");
  //open input and output file

  ndata = 20;


  signalInData={0,1,5,0,4,5,8,5,29,30,30,32,34,17,13,10,5,0,0,0,0};
  //calculate sampling increment dt of input signalInData
  dt = 0.0002;//(tend-tbegin)/(ndata-1);
  //input cut off frequencys and order of filter (1 to 4)
  Fc=1000.0; order=4; Xdc=0; //no constant value

  //call filtering procedures
  // 1. Calculate the filter coefficients
  Butterworth(Fc,dt,order,C,&NSections,&Tg);

  // 2. Initialize filter memory
  Init(Xdc,C,NSections,D);

  // 3. Recursively call Butterworth filter
  for (i=1; i<ndata+1; i++) {
    Filter(&temp,signalInData[i],NSections,C,D);
    filtered[i]=temp;
    if(filtered[i] >= 255.f)
    	myResult[i] = 255;
    else if (filtered[i] < 0.f)
    	myResult[i] = 0;
    else
    	myResult[i] = (char)(filtered[i] + 0.5);
  }

  //print input and filtered signalInDatas to output file
  t=tbegin;
  fprintf(f_out,"\n");
  fprintf(f_out,"        Time        Input signalInData      Filtered signalInData   \n");
  fprintf(f_out,"  ------------------------------------------------------\n");
  for (i=1; i<ndata+1; i++) {
    fprintf(f_out,"       %6.4f     %12.6f       %12.6f     %u\n",t, signalInData[i], filtered[i], (unsigned char)myResult[i]);
    t+=dt;
  }

  fclose(f_out);

  printf("\n Results in file tfilter.lst.\n");
  return 0;
}
*/
