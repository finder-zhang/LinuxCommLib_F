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

#include "SerialLinux_F.h"


serial_linux::serial_linux()
{
	this->m_file_device = -1;
	this->m_p_rx_func = 0;
	this->m_p_user_data = 0;
	m_bReadLoop = 0;

	//gamedata.m_bSerialStop = 1;
}

serial_linux::~serial_linux()
{
	if ( -1 != m_file_device )
	{
		close_port();
	}
}

int serial_linux::open_port(const char* pDevName)
{
	m_file_device = open(pDevName,O_RDWR|O_NOCTTY|O_NDELAY);
	if(m_file_device < 0)
	{
		perror("open serial port");
		return 0;
	}

	if(fcntl(m_file_device,F_SETFL,0) < 0)
	{
		perror("fcntl F_SETFL\n");
		return 0;
	}

	if(isatty(STDIN_FILENO) == 0)
	{
		perror("standard input is not a terminal device.\n");
		return 0;
	}

	//setbuf(

//	create_rx_thread();
	SER_DBG_PRINT("Open Port Ok!\n");

	return 1;
}

int serial_linux::is_port_open()
{
	return m_file_device>=0;
}

int serial_linux::close_port()
{
	close(m_file_device);
	m_file_device = -1;
	return RETURN_SUCCESS_F;
}


int serial_linux::set_com(int baud_rate,int data_bits,char parity,int stop_bits)
{
	struct termios  new_cfg,old_cfg;
	int speed;

	if(tcgetattr(m_file_device,&old_cfg) != 0)	 //保存旧的配置
	{
		perror("tcgetattr");
		return RETURN_ERROR_F;
	}

	new_cfg = old_cfg;						//激活选项
	cfmakeraw(&new_cfg);				//使用原始模式
	new_cfg.c_cflag &= ~CSIZE;



	switch (baud_rate) {
	case 9600: {
		speed = B9600;
	}
		break;
	case 19200: {
		speed = B19200;
	}
		break;
	case 57600: {
		speed = B57600;
	}
		break;

	default:
	case 115200: {
		speed = B115200;
	}
		break;
	}

	cfsetispeed(&new_cfg,speed);
	cfsetospeed(&new_cfg,speed);

	switch(data_bits)
	{
		case 7:
			{
				new_cfg.c_cflag |= CS7;
			}
			break;
		case 8:
			{
				new_cfg.c_cflag |=CS8;
			}
			break;
		default:
			break;
	}

	switch(parity)
	{
		case 'N':
			{
				new_cfg.c_cflag &= ~PARENB;
				new_cfg.c_iflag &= ~INPCK;
			}
			break;

		case 'O':
			{
				new_cfg.c_cflag |= (PARODD | PARENB);
				new_cfg.c_iflag |= INPCK;
			}
			break;

		case 'E':
			{
				new_cfg.c_cflag |= PARENB;
				new_cfg.c_cflag &= ~PARODD;
				new_cfg.c_iflag |= INPCK;
			}
			break;

		default:
			break;
	}

	switch(stop_bits)
	{
		case 1:
			{
				new_cfg.c_cflag &= ~CSTOPB;
			}
			break;

		case 2:
			{
				new_cfg.c_cflag |= CSTOPB;
			}
			break;
		default:
			break;
	}

	new_cfg.c_cc[VTIME] = 0;  //read()函数立即返回
	new_cfg.c_cc[VMIN] = 0;


	tcflush(m_file_device,TCIFLUSH);		//清空缓存区

	if((tcsetattr(m_file_device,TCSANOW,&new_cfg)) != 0)//激活配置
	{
		perror("tcsetattr");
		return -1;
	}
	return 0;
}

int serial_linux::create_rx_thread()
{
	if ( 1 == m_bReadLoop )
		return RETURN_ERROR_F;
	pthread_create(&m_tdRead,0,read_thread,this);
	return RETURN_SUCCESS_F;
}

void serial_linux::ReadDisable()
{
	m_bReadLoop = 0;
}

void serial_linux::ReadEnable()
{

}

void serial_linux::write_port(const void* buff,int len)
{
	//const unsigned char* pCh = (const unsigned char*)buff;
	if (!is_port_open())
	{
		//g_print("open error\n");
		return;
	}
	int nwrite;
	//g_print("write_begin:...\n");
	nwrite = write(m_file_device,buff,len);
	if(nwrite == -1)
	{
		DBG_PRINT("Wirte to sbuf error.\n");
	}
	return;
}

void serial_linux::set_rx_func(serial_rx_func p_func,void* p_user_data)
{
	m_p_rx_func = p_func;
	m_p_user_data = p_user_data;
}

void* serial_linux::read_thread(void* p_data)
{
	serial_linux* pThis = (serial_linux*)p_data;
	pThis->m_bReadLoop = 1;

	DBG_PRINT("Read_Thread!\n");
	int res;
	unsigned char buff;
	fd_set rd, tmp_rd;
	struct timeval timeout;

	FD_ZERO(&rd);
	FD_SET(pThis->m_file_device, &rd);
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

//	g_print("2222222222222222222222222222");
//	pthread_attr_init(&pThis->m_tdAttrRead);
//	pthread_attr_setschedpolicy(&pThis->m_tdAttrRead,SCHED_FIFO);
//	int iPolicy;
//	pthread_attr_getschedpolicy(&pThis->m_tdAttrRead,&iPolicy);
//	DBG_PRINT("default policy = %d\n",iPolicy);
//
//	struct sched_param TSP;
//	pthread_attr_getschedparam(&pThis->m_tdAttrRead,&TSP);
//
//	DBG_PRINT("p = %d,before\n",TSP.__sched_priority);
//
//	TSP.__sched_priority = 60;
//	pthread_attr_setschedparam(&pThis->m_tdAttrRead,&TSP);
//	DBG_PRINT("p = %d,after\n",TSP.__sched_priority);
	//DBG_PRINT("SerialStop_L = %d\n",gamedata.m_bSerialStop);

	while (pThis->m_bReadLoop)
	{
		tmp_rd = rd;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		//static int a = 0;
		//g_print("pre select 1111     %d\n",++a);
		res = select(pThis->m_file_device + 1, &tmp_rd, NULL, NULL, &timeout);
		//res = select(pThis->m_file_device + 1, &tmp_rd, NULL, NULL, 0);
//		if(gamedata.m_bSerialStop)
//			return 0;

		switch (res)
		{
		case 0:
			break;
		case -1:
			break;
		default:
			if (FD_ISSET(pThis->m_file_device,&tmp_rd))
			{
				while( 1 == read(pThis->m_file_device, &buff, 1) )
				{

					if (pThis->m_p_rx_func)
					{
						pThis->m_p_rx_func(pThis->m_p_user_data,buff);

					}

				}

			}
			break;
		}
	}
	return NULL;
}




