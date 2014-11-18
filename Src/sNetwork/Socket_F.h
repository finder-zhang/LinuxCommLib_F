/*
 * Socket_F.h
 *
 *  Created on: 2014年9月9日
 *      Author: finder
 */

#ifndef SOCKET_F_H_
#define SOCKET_F_H_

#include <stdio.h>
#include <sys/socket.h>
#include <CommLib_F.h>
#include <netinet/in.h>
#include <list>
using namespace std;

#include "TcpUdp_F.h"

class CSocket_F
{
protected:
	FD_t				_fd;				//打开的SOCKET FD
	CTcp_F*			_pTcpServer;		//客户端连上后，对服务器读写的TCP接口
	list<CTcp_F*>		_lsTcpClients;	//服务器端，连上的客户TCP接口
	int					_iMaxLink;
	CUdp_F*			_pUdp;

public:
	CSocket_F();
	~CSocket_F();
	operator FD_t ()
	{
		return _fd;
	}

	BOOL Open(int iDomain,int iType,int iProtocol);
	BOOL Close();

	BOOL TcpBind(__CONST_SOCKADDR_ARG sa,socklen_t iLen,int iMaxLink);		//普遍可用的绑定函数
	BOOL TcpBind(const char* chPathName,int iMaxLink);						//本地SOCKET使用的绑定
	BOOL TcpBind(const char* chIpAddr,in_port_t iPort,int iMaxLink);		//网络SOCKET使用的绑定
	int GetMaxLink();

	CTcp_F* Accept();

	CTcp_F* TcpConnect(__CONST_SOCKADDR_ARG sa,socklen_t iLen);				//普遍可用的连接函数
	CTcp_F* TcpConnect(const char* chPathName);								//本地SOCKET使用的连接
	CTcp_F* TcpConnect(const char* chIpAddr,in_port_t iPort);				//网络SOCKET使用的连接

	CUdp_F* UdpBind(__CONST_SOCKADDR_ARG sa,socklen_t iLen);
};







#endif /* SOCKET_F_H_ */
