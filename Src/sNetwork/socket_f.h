/*
 * socket_f.h
 *
 *  Created on: 2014年11月26日
 *      Author: finder
 */

#ifndef _SOCKET_F_H_
#define _SOCKET_F_H_

#include "CommLib_F.h"


class socketf_t {
protected:
	FD_t				_fd;				//打开的SOCKET FD

public:
	socketf_t();
	virtual ~socketf_t();

	BOOL open(int domain,int type,int protocol);
	BOOL close();
};

#endif /* SOCKET_F_H_ */
