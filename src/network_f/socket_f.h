/*
 * socket_f.h
 *
 *  Created on: 2014年11月26日
 *      Author: finder
 */

#ifndef _SOCKET_F_H_
#define _SOCKET_F_H_

#include "comm_lib_f.h"


class socket_f {
protected:
	FD_t				_fd;				//打开的SOCKET FD

public:
	socket_f();
	virtual ~socket_f();

	BOOL open(int domain,int type,int protocol);
	BOOL close();
};

#endif /* SOCKET_F_H_ */
