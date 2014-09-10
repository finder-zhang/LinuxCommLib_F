/*
 * TcpUdp_F.cpp
 *
 *  Created on: 2014年9月9日
 *      Author: root
 */

#include "TcpUdp_F.h"

CTcp_F::CTcp_F(FD_t fd)
{
	_fd = fd;
}

BOOL CTcp_F::IsValid()
{
	return _fd > 0;
}







CUdp_F::CUdp_F(FD_t fd)
{
	_fd = fd;
}
