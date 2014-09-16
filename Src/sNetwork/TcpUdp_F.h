/*
 * TcpUdp_F.h
 *
 *  Created on: 2014年9月9日
 *      Author: root
 */

#ifndef TCPUDP_F_H_
#define TCPUDP_F_H_

#include <CommLib_F.h>

class CTcp_F
{
protected:
	FD_t			_fd;

public:
	CTcp_F(FD_t fd);
	operator FD_t()
	{
		return _fd;
	}
	BOOL IsValid();
	ssize_t Read(void* outBuf,ssize_t iLen,int iFlags = 0);
	ssize_t Write(const void* inBuf,ssize_t iLen,int iFlags = 0);
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
