/*
 * TimeF.h
 *
 *  Created on: 2014年10月6日
 *      Author: finder
 */

#ifndef TIMEF_H_
#define TIMEF_H_

#include "comm_lib_f.h"

class CTime_F {
public:
	CTime_F();
	virtual ~CTime_F();

	static U32 GetMSecondsCount(void);
};

#endif /* TIMEF_H_ */
