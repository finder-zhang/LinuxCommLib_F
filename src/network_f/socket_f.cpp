/*
 * socket_f.cpp
 *
 *  Created on: 2014年11月26日
 *      Author: finder
 */

#include "socket_f.h"

#include <sys/socket.h>
//#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

socket_f::socket_f():_fd(-1) {
	// TODO Auto-generated constructor stub

}

socket_f::~socket_f() {
	// TODO Auto-generated destructor stub
}


BOOL socket_f::open(int domain,int type,int protocol)
{
	if ( -1 != _fd) {
		::close(_fd);
	}

	_fd = socket(domain,type,protocol);
	if ( -1 == _fd ) {
		return FALSE;
	}

	BOOL bReuseaddr = TRUE;
	setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &bReuseaddr,sizeof(BOOL));
	return TRUE;
}

BOOL socket_f::close()
{
	if ( -1 != _fd) {
		::close(_fd);
		_fd = -1;
	}
}




















