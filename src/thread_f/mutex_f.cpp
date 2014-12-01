/*
 * pthread_mutex_f.cpp
 *
 *  Created on: Aug 14, 2012
 *      Author: lucid
 */

#include "comm_lib_f.h"

#include "mutex_f.h"


CMutex_F::CMutex_F()
{
	pthread_mutex_init(&m_Mutex,0);
}

CMutex_F::~CMutex_F()
{
	pthread_mutex_destroy(&m_Mutex);
}

int CMutex_F::Lock()
{
	return pthread_mutex_lock(&m_Mutex);
}

int CMutex_F::TimedLock(const struct timespec *abstime)
{
	return pthread_mutex_timedlock(&m_Mutex,abstime);
}

int CMutex_F::Unlock()
{
	return pthread_mutex_unlock(&m_Mutex);
}

int CMutex_F::TryLock()
{
	return pthread_mutex_trylock(&m_Mutex);
}

int CMutex_F::IsLocked()
{
	int iRet = pthread_mutex_trylock(&m_Mutex);
	if ( 0 == iRet )
	{
		pthread_mutex_unlock(&m_Mutex);
		return RETURN_ERROR_F;
	}
	else
	{
		return RETURN_SUCCESS_F;
	}
}











