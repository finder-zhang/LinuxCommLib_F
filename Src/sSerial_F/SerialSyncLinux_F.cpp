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
	_fnRxCallback = NULL;
	_bRxThreadExit = FALSE;
	_eReadMode = RMODE_AUTO;
	_bReading = FALSE;
}

CSerialSyncLinux_F::~CSerialSyncLinux_F()
{
	Close();
}

CSerialSyncLinux_F::operator FD_t()
{
	return m_fd;
}

BOOL CSerialSyncLinux_F::Open(const char* pDevName)
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

	_thRx.Create(_RxFunc,this);

	return RETURN_SUCCESS_F;
}

BOOL CSerialSyncLinux_F::IsOpened()
{
	return (m_fd >= 0) ? RETURN_SUCCESS_F : RETURN_ERROR_F;
}

BOOL CSerialSyncLinux_F::Close()
{
	if ( IsOpened() ) {
		return RETURN_ERROR_F;
	}

	_bRxThreadExit = TRUE;
	_thRx.Join();

	FD_ZERO(&m_fdsComm);
	close(m_fd);
	m_fd = -1;
	return RETURN_SUCCESS_F;
}

size_t CSerialSyncLinux_F::Write(const void* pData,size_t iLen)
{
	if ( !IsOpened() ) {
		return 0;
	}
	return write(m_fd,pData,iLen);
}

BOOL CSerialSyncLinux_F::WaitForReceive(struct timeval* ptvTime)
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

size_t CSerialSyncLinux_F::Read(void* pData,size_t iLen,int iTimeoutMilliSeconds)
{
	_bReading = TRUE;

	struct timeval timeout;
	timeout.tv_sec = iTimeoutMilliSeconds / 1000;
	timeout.tv_usec = (iTimeoutMilliSeconds % 1000) * 1000;

	size_t i=0;
	for	(i=0;i<iLen;++i)
	{
		if (WaitForReceive(&timeout)) {
			read(m_fd, ((char*)pData)+i, 1);
		}
		else {
			break;
		}
	}
	_bReading = FALSE;
	return i;
}

BOOL CSerialSyncLinux_F::SetReadMode(ReadMode mode)
{
	if ( mode > RMODE_MAX_IDX ) {
		return FALSE;
	}
	_eReadMode = mode;
	return TRUE;
}

PFN_RX_CALLBACK CSerialSyncLinux_F::SetRxCallback(PFN_RX_CALLBACK fnCB)
{
	PFN_RX_CALLBACK fnTemp = _fnRxCallback;
	_fnRxCallback = fnCB;
	return fnTemp;
}

void* CSerialSyncLinux_F::_RxThread()
{
	struct timeval tm;
	tm.tv_sec = 1;
	tm.tv_usec = 0;

	do
	{
		if ( WaitForReceive(&tm) ) {
			if ( _fnRxCallback ) {
				//in async mode,must call RxCallback
				if ( RMODE_ASYNC == _eReadMode ) {
					_fnRxCallback();
				}
				//in auto mode,if no one call Read(),then RxCallback be called
				if ( (RMODE_AUTO == _eReadMode) && (FALSE == _bReading)  ) {
					_fnRxCallback();
				}
			}
		}
	}while( FALSE == _bRxThreadExit );
	_bRxThreadExit = FALSE;
	return NULL;
}

void* CSerialSyncLinux_F::_RxFunc(void* pData)
{
	CSerialSyncLinux_F* pThis = (CSerialSyncLinux_F*)pData;
	return pThis->_RxThread();
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

