/*
 * random_ex_f.cpp
 *
 *  Created on: 2012-7-20
 *      Author: lucid
 */

#include "comm_lib_f.h"

#include <cmath>
#include "random_f.h"


int RandAtRange(int iL,int iH)
{
	if ( iL > iH )
		return -1;

	int iRange = iH - iL + 1;
	int iRand = rand()%iRange;
	return iRand + iL;
}

bool RandPercentge(double fPercentge)
{
	return rand() < (fPercentge * RAND_MAX);
}
