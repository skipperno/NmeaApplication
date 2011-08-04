/*
 * ButterworthLowPassFilter.h
 *
 *  Created on: Aug 2, 2011
 *      Author: ernad
 */

#ifndef BUTTERWORTHLOWPASSFILTER_H_
#define BUTTERWORTHLOWPASSFILTER_H_


typedef  double Filter_Coef[6][10];
typedef  double Memory_Coef[3][10];





class ButterworthLowPassFilter {
public:
	ButterworthLowPassFilter();
	virtual ~ButterworthLowPassFilter();
	static void test(char* inArray, int dataLength, char*outArray);

	static void Filter( double *Xs,double Xd, int NSections,
	 	         Filter_Coef C, Memory_Coef D );
	static void Init(double Xdc, Filter_Coef C, int NSections, Memory_Coef D);
	static void Butterworth(double Fc,double Ts,int n,Filter_Coef C,
	                 int *NSections, double *Tg );
};

#endif /* BUTTERWORTHLOWPASSFILTER_H_ */
