/*
 * TcpUdp_F.cpp
 *
 *  Created on: 2014年9月9日
 *      Author: root
 */

#include <sys/socket.h>
#include "TcpUdp_F.h"

CTcp_F::CTcp_F(FD_t fd)
:m_fd(fd)
{
	FD_ZERO(&_fdset);
	FD_SET(fd, &_fdset);
}

CTcp_F::CTcp_F(FD_t fd,const sockaddr_in* sin)
:m_fd(fd),
_sin(*sin)
{
	FD_ZERO(&_fdset);
	FD_SET(fd, &_fdset);
}

const sockaddr_in& CTcp_F::GetInetAddr()
{
	return _sin;
}

BOOL CTcp_F::IsValid()
{
	return m_fd > 0;
}

ssize_t CTcp_F::Read(void* outBuf,ssize_t iLen,int iFlags)
{
	return recv(m_fd,outBuf,iLen,iFlags);
}

ssize_t CTcp_F::Write(const void* inBuf,ssize_t iLen,int iFlags)
{
	return send(m_fd,inBuf,iLen,iFlags);
}

BOOL CTcp_F::WaitForReceive(U32 uMilliSeconds)
{
	struct timeval tmWait;
	tmWait.tv_sec = uMilliSeconds / 1000;
	tmWait.tv_usec = (uMilliSeconds % 1000) * 1000;

	fd_set fdsCheck = _fdset;
	int iRes = select(m_fd+1,&fdsCheck,NULL,NULL,&tmWait);
	switch (iRes)
	{
	case 0:
	case -1:
		return RETURN_ERROR_F;
		break;
	default:
		break;
	}
	return FD_ISSET(m_fd,&fdsCheck) ? RETURN_SUCCESS_F : RETURN_ERROR_F;
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




