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
	size_t Read(void* outBuf,size_t len);
	size_t Write(const void* inbBuf,size_t len);
};

class CUdp_F
{
protected:
	FD_t			_fd;

public:
	CUdp_F(FD_t fd);
	operator FD_t()
	{
		return _fd;
	}
	size_t Read(void* outBuf,size_t len);
	size_t Write(const void* inbBuf,size_t len);
};

#endif /* TCPUDP_F_H_ */
