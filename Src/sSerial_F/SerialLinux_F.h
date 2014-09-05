/*
 * serial_linux.h
 *
 *  Created on: Apr 25, 2012
 *      Author: lucid
 */

#ifndef SERIAL_LINUX_H_
#define SERIAL_LINUX_H_

#include <pthread.h>

typedef void (*serial_rx_func)(void* p_user_data,unsigned char ch);


#define SER_DBG_PRINT		DBG_PRINT
//#define SER_DBG_PRINT

class serial_linux
{
protected:
	volatile serial_rx_func		m_p_rx_func;
	void*			m_p_user_data;
	static void*	read_thread(void* p_data);
	pthread_t		m_tdRead;
	pthread_attr_t	m_tdAttrRead;
	volatile  int	m_bReadLoop;

public:
	serial_linux();
	virtual ~serial_linux();

	operator int()
	{
		return m_file_device;
	}
	int m_file_device;

	int is_port_open();
	void set_rx_func(serial_rx_func p_func,void* p_user_data);
	int open_port(const char* pDevName);
	int close_port();
	void write_port(const void* buff,int len);
	int set_com(int baud_rate,int data_bits,char parity,int stop_bits);

	int create_rx_thread();
	void ReadDisable();
	void ReadEnable();
};



#endif /* SERIAL_LINUX_H_ */
