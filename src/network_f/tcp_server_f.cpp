/*
 * tcp_server_f.cpp
 *
 *  Created on: 2014年11月26日
 *      Author: root
 */

#include "tcp_server_f.h"

#include <sys/socket.h>
//#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "debug_f.h"

#include "tcp_udp_f.h"

tcp_server_f::tcp_server_f() {
	// TODO Auto-generated constructor stub
	_max_client = 0;
}

tcp_server_f::~tcp_server_f() {
	// TODO Auto-generated destructor stub
}

CTcp_F* tcp_server_f::accept()
{
	sockaddr saddr;
	socklen_t slen;

	FD_t fd = ::accept(_fd,&saddr,&slen);
	if ( fd < 0 ) {
		return NULL;
	}

	_lsTcpClients.push_back(new CTcp_F(fd,(const sockaddr_in*)&saddr));
	return _lsTcpClients.back();
}

BOOL tcp_server_f::bind(__CONST_SOCKADDR_ARG sa,socklen_t iLen,int max_client)
{
    if ( -1 == ::bind(_fd,sa,iLen) ) {
    	dsop("bind failed!\n");
    	return FALSE;
    }
    if ( -1 == listen(_fd,max_client) ) {
    	return FALSE;
    }
    _max_client = max_client;
	return TRUE;
}

BOOL tcp_server_f::bind(const char* chPathName,int max_client)
{
	struct sockaddr_un unAddr;
	unAddr.sun_family = AF_LOCAL;
	strcpy(unAddr.sun_path,chPathName);
	return bind((__CONST_SOCKADDR_ARG)&unAddr,sizeof(unAddr),max_client);
}

BOOL tcp_server_f::bind(const char* chIpAddr,in_port_t iPort,int max_client)
{
	struct sockaddr_in ina;
	ina.sin_family = AF_INET;
	ina.sin_port = htons(iPort);
	ina.sin_addr.s_addr = inet_addr(chIpAddr);
	return bind((__CONST_SOCKADDR_ARG)&ina,sizeof(ina),max_client);
}







