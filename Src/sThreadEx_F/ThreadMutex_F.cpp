/*
 * pthread_mutex_f.cpp
 *
 *  Created on: Aug 14, 2012
 *      Author: lucid
 */

#include "CommLib_F.h"

#include "ThreadMutex_F.h"


CThreadMutex_F::CThreadMutex_F()
{
	pthread_mutex_init(&m_Mutex,0);
}

CThreadMutex_F::~CThreadMutex_F()
{
	pthread_mutex_destroy(&m_Mutex);
}

int CThreadMutex_F::Lock()
{
	return pthread_mutex_lock(&m_Mutex);
}

int CThreadMutex_F::TimedLock(const struct timespec *abstime)
{
	return pthread_mutex_timedlock(&m_Mutex,abstime);
}

int CThreadMutex_F::Unlock()
{
	return pthread_mutex_unlock(&m_Mutex);
}

int CThreadMutex_F::TryLock()
{
	return pthread_mutex_trylock(&m_Mutex);
}

int CThreadMutex_F::IsLocked()
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











