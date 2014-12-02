/*
 * tcp_client_f.h
 *
 *  Created on: 2014年11月26日
 *      Author: root
 */

#ifndef TCP_CLIENT_F_H_
#define TCP_CLIENT_F_H_

#include <CommLib_F.h>

#include "socket_f.h"

#include <sys/socket.h>
#include <netinet/in.h>

class CTcp_F;

class tcp_client_f : public socketf_t
{
public:
	FD_t				_fd_socket;
	CTcp_F*			_tcp_server;		//客户端连上后，对服务器读写的TCP接口

public:
	tcp_client_f();
	virtual ~tcp_client_f();

	CTcp_F* connect(__CONST_SOCKADDR_ARG sa,socklen_t len);				//普遍可用的连接函数
	CTcp_F* connect(const char* chPathName);								//本地SOCKET使用的连接
	CTcp_F* connect(const char* chIpAddr,in_port_t iPort);				//网络SOCKET使用的连接
};

#endif /* TCP_CLIENT_F_H_ */
