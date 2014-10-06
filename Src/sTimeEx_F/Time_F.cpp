/*
 * TimeF.cpp
 *
 *  Created on: 2014年10月6日
 *      Author: root
 */

#include "Time_F.h"

CTime_F::CTime_F() {
	// TODO Auto-generated constructor stub

}

CTime_F::~CTime_F() {
	// TODO Auto-generated destructor stub
}


U32 CTime_F::GetMSecondsCount(void)
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC,&ts);                      //此处可以判断一下返回值

	return (ts.tv_sec*1000 + ts.tv_nsec/(1000*1000));
}
