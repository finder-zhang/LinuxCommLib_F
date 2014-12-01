/*
 * tcp_server_f.h
 *
 *  Created on: 2014年11月26日
 *      Author: root
 */

#ifndef TCP_SERVER_F_H_
#define TCP_SERVER_F_H_

#include "socket_f.h"

#include <sys/socket.h>
#include <netinet/in.h>

#include <list>
using namespace std;

class CTcp_F;

class tcp_server_f : public socket_f
{
protected:
	list<CTcp_F*>		_lsTcpClients;	//服务器端，连上的客户TCP接口
	int					_max_client;

public:
	tcp_server_f();
	virtual ~tcp_server_f();

	CTcp_F* accept();

	BOOL bind(__CONST_SOCKADDR_ARG sa,socklen_t slen,int max_client);		//普遍可用的绑定函数
	BOOL bind(const char* path_name,int max_client);						//本地SOCKET使用的绑定
	BOOL bind(const char* ip_addr,in_port_t port,int max_client);		//网络SOCKET使用的绑定
	int GetMaxLink();


};

#endif /* TCP_SERVER_F_H_ */
