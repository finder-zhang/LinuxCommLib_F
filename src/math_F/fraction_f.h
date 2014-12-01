/*
 * Fraction_F.h
 *
 *  Created on: Nov 21, 2012
 *      Author: lucid
 */

#ifndef FRACTION_F_H_
#define FRACTION_F_H_


class CFraction_F
{
protected:
	int m_iInteger;
	int m_iNumerator;
	int m_iDenominator;

public:
	CFraction_F();
	CFraction_F(int iInteger,int iNumerator,int iDenominator);
	~CFraction_F();

	operator double();
	CFraction_F operator +(CFraction_F rhs);
	CFraction_F& operator +=(CFraction_F rhs);

	CFraction_F operator -(const CFraction_F& rhs);
	CFraction_F& operator -=(const CFraction_F& rhs);

	CFraction_F operator *(const CFraction_F& rhs);
	CFraction_F& operator *=(const CFraction_F& rhs);

	CFraction_F operator /(const CFraction_F& rhs);
	CFraction_F& operator /=(const CFraction_F& rhs);

	BOOL FitSign();
	BOOL Reduction();
	BOOL ImporperToPorper();
	BOOL PorperToImporper();
	//Find the lowest common multiple
	static int FindLCM(int iVal1,int iVal2);
	//Find the greatest common divisor
	static int FindGCD(int iVal1,int iVal2);
};


#endif /* FRACTION_F_H_ */
