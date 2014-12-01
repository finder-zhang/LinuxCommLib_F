/*
 * DataEnDecodeInternal_F.h
 *
 *  Created on: 2014年11月20日
 *      Author: root
 */

#ifndef DATAENDECODEINTERNAL_F_H_
#define DATAENDECODEINTERNAL_F_H_

#include "comm_lib_f.h"

#include "data_package_f.h"

typedef struct _dpkg_operator
{
	CatchPackageStatus		_cps;
	U8							rx_buf[256];
	U16							rx_idx;
	volatile BOOL				is_pkged;
}dpkg_operator_t;


#endif /* DATAENDECODEINTERNAL_F_H_ */
