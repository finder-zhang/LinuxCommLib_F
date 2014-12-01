/*
 * serial_linux.h
 *
 *  Created on: Apr 25, 2012
 *      Author: lucid
 */

#ifndef __SERIAL_SYNC_LINUX_H__
#define __SERIAL_SYNC_LINUX_H__

#include <sys/select.h>

#include "thread_f.h"
#include "comm_lib_f.h"

typedef void (*PFN_RX_HANDLER)(void*);

class CSerialSyncLinux_F
{
public:
	typedef enum _ReadMode
	{
		RMODE_AUTO,	//This MODE is default and strongly recommended to use,when you are new to use this class.
						//When we call Read(),RxCallback will not be called,so all receive will get out of the
						//RxCallback,we can also don't deal out of the RxCallback,call RxCallback to remind us.

		RMODE_ASYNC,	//When there are datas available,RxCallback will be called,we can call Read() in the RxCallback
						//at the same time we also can call Read() out of the RxCallback,according to threads scheduing,
						//the thread Read() and the thread RxCallback maybe read some part of serial receive,
						//This conslusion is verify by finder.
						//I send 2048 bytes and Read(2048) at main thread,also Read() at RxCallback,both thread can
						//read some part of 2048 bytes.

		RMODE_SYNC, 	//RxCallback will not be called,we can use Read() to read data with a timeout at any time.

		RMODE_MAX_IDX = RMODE_SYNC
	}ReadMode;

protected:
	fd_set					m_fdsComm;
	FD_t					m_fd;
	PFN_RX_HANDLER		_fnRxCallback;
	CThread_F				_thRx;
	BOOL					_bRxThreadExit;
	ReadMode				_eReadMode;
	BOOL					_bReading;
	void*					_pRxHandlerData;

public:
	CSerialSyncLinux_F();
	virtual ~CSerialSyncLinux_F();

	operator FD_t();		//return the file description

	BOOL IsOpened();
	BOOL Open(const char* pDevName);
	BOOL Close();
	BOOL SetParam(int baud_rate,int data_bits = 8,char parity = 'N',int stop_bits = 1);
	BOOL SetReadMode(ReadMode mode);
	PFN_RX_HANDLER SetRxHandler(PFN_RX_HANDLER fnCB,void* pData);

	size_t Write(const void* pData,size_t iLen);
	size_t Read(void* pData,size_t iLen,int iTimeoutMilliSeconds = 0);
	BOOL WaitForReceive(struct timeval* ptvTime);



protected:
	void* _RxThread();
	static void* _RxFunc(void* pData);

	//void DbgCheckWait();
};



#endif // __SERIAL_SYNC_LINUX_H__
