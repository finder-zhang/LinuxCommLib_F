/*
 * serial_linux.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: lucid
 */

#include "CommLib_F.h"

# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
#include <stdio.h>
#include "SerialSyncLinux_F.h"


CSerialSyncLinux_F::CSerialSyncLinux_F()
{
	m_fd = -1;
}

CSerialSyncLinux_F::~CSerialSyncLinux_F()
{
	Close();
}

CSerialSyncLinux_F::operator int()
{
	return m_fd;
}

int CSerialSyncLinux_F::Open(const char* pDevName)
{
	m_fd = open(pDevName,O_RDWR|O_NOCTTY|O_NDELAY);
	if(m_fd < 0)
	{
		perror("open serial port");
		return RETURN_ERROR_F;
	}

	if(fcntl(m_fd,F_SETFL,0) < 0)
	{
		perror("fcntl F_SETFL\n");
		return RETURN_ERROR_F;
	}

	if(isatty(STDIN_FILENO) == 0)
	{
		perror("standard input is not a terminal device.\n");
		return RETURN_ERROR_F;
	}

	FD_ZERO(&m_fdsComm);
	FD_SET(m_fd, &m_fdsComm);

	return RETURN_SUCCESS_F;
}

int CSerialSyncLinux_F::IsOpened()
{
	return (m_fd >= 0) ? RETURN_SUCCESS_F : RETURN_ERROR_F;
}

int CSerialSyncLinux_F::Close()
{
	if ( IsOpened() ) {
		return RETURN_ERROR_F;
	}

	FD_ZERO(&m_fdsComm);
	close(m_fd);
	m_fd = -1;
	return RETURN_SUCCESS_F;
}

ssize_t CSerialSyncLinux_F::Write(const void* pData,int iLen)
{
	if ( !IsOpened() ) {
		return 0;
	}
	return write(m_fd,pData,iLen);
}

int CSerialSyncLinux_F::WaitForReceive(struct timeval* ptvTime)
{
	fd_set fdsCheck = m_fdsComm;
	int iRes = select(m_fd+1,&fdsCheck,NULL,NULL,ptvTime);
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

//void CSerialSyncLinux::DbgCheckWait()
//{
//	int i = 0;
//	while(1)
//	{
//		struct timeval time;
//		time.tv_sec = 10;
//		time.tv_usec = 0;
//		WaitForReceive(&time);
//		++i;
//		printf("WaitEnd! %d\n",i);
//	}
//}

ssize_t CSerialSyncLinux_F::Read(void* pData,int iLen,int iMseconds)
{
	struct timeval timeout;
	timeout.tv_sec = iMseconds / 1000;
	timeout.tv_usec = (iMseconds % 1000) * 1000;

	int i=0;
	for	(i=0;i<iLen;++i)
	{
		if (WaitForReceive(&timeout)) {
			read(m_fd, ((char*)pData)+i, 1);
		}
		else {
			break;
		}
	}
	return i;
}


int CSerialSyncLinux_F::SetParam(int baud_rate,int data_bits,char parity,int stop_bits)
{
	struct termios  new_cfg,old_cfg;
	int speed = 0;

	if(tcgetattr(m_fd,&old_cfg) != 0)
	{
		perror("tcgetattr");
		return RETURN_ERROR_F;
	}

	new_cfg = old_cfg;
	cfmakeraw(&new_cfg);

	switch (baud_rate)
	{
	case 9600:
		speed = B9600;
		break;
	case 38400:
		speed = B38400;
		break;
	case 57600:
		speed = B57600;
		break;
	case 115200:
		speed = B115200;
		break;
	}

	cfsetispeed(&new_cfg,speed);
	cfsetospeed(&new_cfg,speed);

	switch(data_bits)
	{
	case 7:
		new_cfg.c_cflag |= CS7;
		break;
	case 8:
		new_cfg.c_cflag |=CS8;
		break;
	default:
		break;
	}

	switch(parity)
	{
	case 'N':
		new_cfg.c_cflag &= ~PARENB;
		new_cfg.c_iflag &= ~INPCK;
		break;

	case 'O':
		new_cfg.c_cflag |= (PARODD | PARENB);
		new_cfg.c_iflag |= INPCK;
		break;

	case 'E':
		new_cfg.c_cflag |= PARENB;
		new_cfg.c_cflag &= ~PARODD;
		new_cfg.c_iflag |= INPCK;
		break;

	default:
		break;
	}

	switch(stop_bits)
	{
	case 1:
		new_cfg.c_cflag &= ~CSTOPB;
		break;

	case 2:
		new_cfg.c_cflag |= CSTOPB;
		break;
	default:
		break;
	}

	new_cfg.c_cc[VTIME] = 0;
	new_cfg.c_cc[VMIN] = 0;

	tcflush(m_fd,TCIFLUSH);
	if((tcsetattr(m_fd,TCSANOW,&new_cfg)) != 0)
	{
		perror("tcsetattr");
		return RETURN_ERROR_F;
	}
	return RETURN_SUCCESS_F;
}

