/*
 * Socket_F.cpp
 *
 *  Created on: 2014年9月9日
 *      Author: finder
 */


#include <sys/socket.h>
//#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Socket_F.h"

#include "DebugEx_F.h"






CSocket_F::CSocket_F()
:_fd(-1),
_pTcpServer(NULL),
_iMaxLink(0),
_pUdp(NULL)
{
}

CSocket_F::~CSocket_F()
{
	if ( -1 != _fd ) {
		Close();
	}
}

BOOL CSocket_F::Open(int iDomain,int iType,int iProtocol)
{
	_fd = socket(iDomain,iType,iProtocol);
	if ( -1 == _fd ) {
		return FALSE;
	}
	BOOL bReuseaddr = TRUE;
	setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &bReuseaddr,sizeof(BOOL));
	return TRUE;
}

BOOL CSocket_F::Close()
{
	if ( -1 != _fd) {
		close(_fd);
		_fd = -1;
	}
	if ( _pUdp ) {
		delete _pUdp;
	}
	if ( _pTcpServer ) {
		delete _pTcpServer;
	}
	list<CTcp_F*>::iterator it;
	for (it = _lsTcpClients.begin(); it!=_lsTcpClients.end(); ++it) {
		delete (*it);
	}
	_lsTcpClients.clear();
	return TRUE;
}

BOOL CSocket_F::TcpBind(__CONST_SOCKADDR_ARG sa,socklen_t iLen,int iMaxLink)
{
    if ( -1 == bind(_fd,sa,iLen) ) {
    	Dsop("bind failed!\n");
    	return FALSE;
    }
    if ( -1 == listen(_fd,iMaxLink) ) {
    	return FALSE;
    }
    _iMaxLink = iMaxLink;
	return TRUE;
}

BOOL CSocket_F::TcpBind(const char* chPathName,int iMaxLink)
{
	struct sockaddr_un unAddr;
	unAddr.sun_family = AF_LOCAL;
	strcpy(unAddr.sun_path,chPathName);
	return TcpBind((__CONST_SOCKADDR_ARG)&unAddr,sizeof(unAddr),iMaxLink);
}

BOOL CSocket_F::TcpBind(const char* chIpAddr,in_port_t iPort,int iMaxLink)
{
	struct sockaddr_in ina;
	ina.sin_family = AF_INET;
	ina.sin_port = htons(iPort);
	ina.sin_addr.s_addr = inet_addr(chIpAddr);
	return TcpBind((__CONST_SOCKADDR_ARG)&ina,sizeof(ina),iMaxLink);
}

CTcp_F* CSocket_F::Accept()
{
	sockaddr saddr;
	socklen_t slen;

	//FD_t fd = accept(_fd,&saddr,&slen);
	FD_t fd = accept(_fd,&saddr,&slen);
	if ( fd < 0 ) {
		return NULL;
	}
	sockaddr_in* pSIN = (sockaddr_in*)&saddr;
	_lsTcpClients.push_back(new CTcp_F(fd,pSIN));
	return _lsTcpClients.back();
}

CTcp_F* CSocket_F::TcpConnect(__CONST_SOCKADDR_ARG sa,socklen_t iLen)
{
	if ( -1 == connect(_fd,sa,iLen) ) {
		return NULL;
	}
	if ( _pTcpServer ) {
		delete _pTcpServer;
	}
	_pTcpServer = new CTcp_F(_fd);
	return _pTcpServer;
}

CTcp_F* CSocket_F::TcpConnect(const char* chPathName)
{
	struct sockaddr_un una;
	una.sun_family = AF_LOCAL;
	strcpy(una.sun_path,chPathName);
	return TcpConnect((__CONST_SOCKADDR_ARG)&una, sizeof(una));
}

CTcp_F* CSocket_F::TcpConnect(const char* chIpAddr,in_port_t iPort)
{
	struct sockaddr_in ina;
	ina.sin_family = AF_INET;
	ina.sin_port = htons(iPort);
	ina.sin_addr.s_addr = inet_addr(chIpAddr);
	return TcpConnect((__CONST_SOCKADDR_ARG)&ina,sizeof(ina));
}

CUdp_F* CSocket_F::UdpBind(__CONST_SOCKADDR_ARG sa,socklen_t iLen)
{
	if ( -1 == bind(_fd,sa,iLen) ) {
		return NULL;
	}
	if ( _pUdp ) {
		delete _pUdp;
	}
	_pUdp = new CUdp_F(_fd);
	return _pUdp;
}

int CSocket_F::GetMaxLink()
{
	return _iMaxLink;
}




