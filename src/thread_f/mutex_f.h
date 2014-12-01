/*
 * pthread_mutex_f.h
 *
 *  Created on: Aug 14, 2012
 *      Author: lucid
 */

#ifndef __THREAD_MUTEX_F_H__
#define __THREAD_MUTEX_F_H__

#include <pthread.h>

class CMutex_F
{
protected:
	pthread_mutex_t		m_Mutex;

public:
	CMutex_F();
	~CMutex_F();

	int Lock();
	int TimedLock(const struct timespec *abstime);
	int Unlock();

	int TryLock();
	int IsLocked();
};


#endif /* __THREAD_MUTEX_F_H__ */
