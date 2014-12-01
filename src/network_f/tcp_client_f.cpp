/*
 * tcp_client_f.cpp
 *
 *  Created on: 2014年11月26日
 *      Author: root
 */

#include "tcp_client_f.h"

#include <sys/socket.h>
//#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tcp_udp_f.h"

tcp_client_f::tcp_client_f() {
	// TODO Auto-generated constructor stub
	_fd_socket = -1;
}

tcp_client_f::~tcp_client_f() {
	// TODO Auto-generated destructor stub
}

CTcp_F* tcp_client_f::connect(__CONST_SOCKADDR_ARG sa,socklen_t iLen)
{
	if ( -1 == ::connect(_fd,sa,iLen) ) {
		return NULL;
	}
	if ( _tcp_server ) {
		delete _tcp_server;
	}
	_tcp_server = new CTcp_F(_fd,(const sockaddr_in*)&sa);
	return _tcp_server;
}

CTcp_F* tcp_client_f::connect(const char* chPathName)
{
	struct sockaddr_un una;
	una.sun_family = AF_LOCAL;
	strcpy(una.sun_path,chPathName);
	return connect((__CONST_SOCKADDR_ARG)&una, sizeof(una));
}

CTcp_F* tcp_client_f::connect(const char* chIpAddr,in_port_t iPort)
{
	struct sockaddr_in ina;
	ina.sin_family = AF_INET;
	ina.sin_port = htons(iPort);
	ina.sin_addr.s_addr = inet_addr(chIpAddr);
	return connect((__CONST_SOCKADDR_ARG)&ina,sizeof(ina));
}




