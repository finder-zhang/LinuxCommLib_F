/*
 * random_ex_f.cpp
 *
 *  Created on: 2012-7-20
 *      Author: lucid
 */

#include "CommLib_F.h"

#include <cmath>
#include "Random_F.h"


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
