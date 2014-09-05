/*
 * serial_linux.h
 *
 *  Created on: Apr 25, 2012
 *      Author: lucid
 */

#ifndef __SERIAL_SYNC_LINUX_H__
#define __SERIAL_SYNC_LINUX_H__

#include <pthread.h>

class CSerialSyncLinux_F
{
protected:
	fd_set		m_fdsComm;
	int			m_fd;

public:
	CSerialSyncLinux_F();
	virtual ~CSerialSyncLinux_F();

	operator int();		//return the file description

	int IsOpened();
	int Open(const char* pDevName);
	int Close();
	int SetParam(int baud_rate,int data_bits,char parity,int stop_bits);

	ssize_t Write(const void* pData,int iLen);
	ssize_t Read(void* pData,int iLen,int iMseconds);
	int WaitForReceive(struct timeval* ptvTime);

	//void DbgCheckWait();
};



#endif // __SERIAL_SYNC_LINUX_H__
