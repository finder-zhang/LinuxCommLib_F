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

socketf_t::socketf_t():_fd(-1) {
	// TODO Auto-generated constructor stub

}

socketf_t::~socketf_t() {
	// TODO Auto-generated destructor stub
}


BOOL socketf_t::open(int domain,int type,int protocol)
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

BOOL socketf_t::close()
{
	if ( -1 != _fd) {
		::close(_fd);
		_fd = -1;
	}
}




















