/*
 * DataEnDecodeInternal_F.h
 *
 *  Created on: 2014年11月20日
 *      Author: root
 */

#ifndef DATAENDECODEINTERNAL_F_H_
#define DATAENDECODEINTERNAL_F_H_

#include <CommLib_F.h>

#include "DataPackage_F.h"

typedef struct _DPackageOperator
{
	CatchPackageStatus		_cps;
	U8							_uRxBuf[256];
	U16							_wRxPtr;
	volatile BOOL				_bPackageOk;
}DPackageOperator_t;


#endif /* DATAENDECODEINTERNAL_F_H_ */
