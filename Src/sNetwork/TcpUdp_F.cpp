/*
 * TcpUdp_F.cpp
 *
 *  Created on: 2014年9月9日
 *      Author: root
 */

#include <sys/socket.h>
#include "TcpUdp_F.h"

CTcp_F::CTcp_F(FD_t fd)
{
	_fd = fd;
}

BOOL CTcp_F::IsValid()
{
	return _fd > 0;
}

ssize_t CTcp_F::Read(void* outBuf,ssize_t iLen,int iFlags)
{
	return recv(_fd,outBuf,iLen,iFlags);
}

ssize_t CTcp_F::Write(const void* inBuf,ssize_t iLen,int iFlags)
{
	return send(_fd,inBuf,iLen,iFlags);
}






















CUdp_F::CUdp_F(FD_t fd)
{
	_fd = fd;
}

BOOL CUdp_F::IsValid()
{
	return _fd > 0;
}

ssize_t CUdp_F::Read(void* outBuf,ssize_t iLen,int iFlags)
{
	return recvfrom(_fd,outBuf,iLen,iFlags,NULL,NULL);
}

ssize_t CUdp_F::Write(const void* inBuf,ssize_t iLen,int iFlags)
{
	return sendto(_fd,inBuf,iLen,iFlags,NULL,0);
}




