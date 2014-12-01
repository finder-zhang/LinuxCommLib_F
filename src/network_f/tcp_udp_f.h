/*
 * TcpUdp_F.h
 *
 *  Created on: 2014年9月9日
 *      Author: root
 */

#ifndef TCPUDP_F_H_
#define TCPUDP_F_H_

#include <comm_lib_f.h>

#include <sys/socket.h>
#include <netinet/in.h>

class CTcp_F
{
protected:
	sockaddr_in	_sin;
	fd_set			_fdset;

public:
	FD_t			m_fd;
	CTcp_F(FD_t fd);
	CTcp_F(FD_t fd,const sockaddr_in* sin);
	operator FD_t()
	{
		return m_fd;
	}
	const sockaddr_in& GetInetAddr();
	BOOL IsValid();
	BOOL IsConnected();
	void SetBlock(BOOL bBlock);
	ssize_t Read(void* outBuf,ssize_t iLen,int iFlags = 0);
	ssize_t Write(const void* inBuf,ssize_t iLen,int iFlags = 0);
	BOOL WaitForReceive(U32 uMilliSeconds);
};

class CUdp_F
{
protected:
	FD_t			_fd;

public:
	CUdp_F(FD_t fd);
	BOOL IsValid();
	operator FD_t()
	{
		return _fd;
	}
	ssize_t Read(void* outBuf,ssize_t iLen,int iFlags = 0);
	ssize_t Write(const void* inBuf,ssize_t iLen,int iFlags = 0);
};

#endif /* TCPUDP_F_H_ */
