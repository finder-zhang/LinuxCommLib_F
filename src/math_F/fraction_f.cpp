/*
 * Fraction_F.cpp
 *
 *  Created on: Nov 21, 2012
 *      Author: lucid
 */

#include "comm_lib_f.h"

#include "fraction_f.h"


CFraction_F::CFraction_F()
{
	m_iInteger = 0;
	m_iNumerator = 0;
	m_iDenominator = 1;
}

CFraction_F::CFraction_F(int iInteger,int iNumerator,int iDenominator)
{
	if (0 == iDenominator) {
		CFraction_F();
	}

	m_iInteger = iInteger;
	m_iNumerator = iNumerator;
	m_iDenominator = iDenominator;

	FitSign();
}

CFraction_F::~CFraction_F()
{

}

CFraction_F::operator double()
{
	double fRet = m_iInteger
			+ ( double(m_iNumerator) / m_iDenominator );
	return fRet;
}

CFraction_F CFraction_F::operator +(CFraction_F rhs)
{
	(*this) += rhs;
	return *this;
}

CFraction_F& CFraction_F::operator +=(CFraction_F rhs)
{
	FitSign();
	PorperToImporper();
	rhs.FitSign();
	rhs.PorperToImporper();

	int iLCM = FindLCM( abs(m_iDenominator), abs(rhs.m_iDenominator) );
	int iMulti1 = iLCM / m_iDenominator;
	int iMulti2 = iLCM / rhs.m_iDenominator;

	m_iNumerator = ( m_iNumerator * iMulti1 )
			+ ( rhs.m_iNumerator * iMulti2 );
	m_iDenominator = iLCM;
	FitSign();
	ImporperToPorper();
	Reduction();
	return (*this);
}

CFraction_F CFraction_F::operator -(const CFraction_F& rhs)
{

}

CFraction_F& CFraction_F::operator -=(const CFraction_F& rhs)
{
}

CFraction_F CFraction_F::operator *(const CFraction_F& rhs)
{

}

CFraction_F& CFraction_F::operator *=(const CFraction_F& rhs)
{

}

CFraction_F CFraction_F::operator /(const CFraction_F& rhs)
{

}

CFraction_F& CFraction_F::operator /=(const CFraction_F& rhs)
{

}

BOOL CFraction_F::FitSign()
{
	if ( m_iDenominator < 0 ) {
		m_iDenominator *= -1;
		m_iNumerator *= -1;
	}

	if ( m_iInteger > 0 ) {
		if ( m_iNumerator < 0 ) {
			//if Integer part and Numerator part have different sign
			//we need to fit it's sign
			m_iNumerator += m_iInteger * m_iDenominator;
			m_iInteger = m_iNumerator / m_iDenominator;
			m_iNumerator -= m_iInteger * m_iDenominator;
		}
	}

	return TRUE;
}

BOOL CFraction_F::Reduction()
{
	int iGCD = FindGCD( abs(m_iNumerator), abs(m_iDenominator) );
	m_iNumerator /= iGCD;
	m_iDenominator /= iGCD;
	return (iGCD != 1) ? TRUE : FALSE;
}

BOOL CFraction_F::ImporperToPorper()
{
	if (abs(m_iNumerator) < abs(m_iDenominator))
		return FALSE;

	int iMulti = m_iNumerator / m_iDenominator;
	m_iInteger += iMulti;
	m_iNumerator -= ( m_iDenominator * iMulti );
	return TRUE;
}

BOOL CFraction_F::PorperToImporper()
{
	if (0 == m_iInteger) {
		return FALSE;
	}

	FitSign();
	m_iNumerator += ( m_iInteger*m_iDenominator );
	m_iInteger = 0;

	return TRUE;
}

int CFraction_F::FindGCD(int iVal1,int iVal2)
{
	if (iVal1 == iVal2)
		return iVal1;

	int iMod;
	int iBig = clib_max(iVal1,iVal2);
	int iSmall = clib_min(iVal1,iVal2);

	while (iSmall != 0)
	{
		iMod = iBig % iSmall;
		iBig = iSmall;
		iSmall = iMod;
	}

	return iBig;
}

int CFraction_F::FindLCM(int iVal1,int iVal2)
{
	return iVal1 * iVal2 / FindGCD(iVal1,iVal2);
}











