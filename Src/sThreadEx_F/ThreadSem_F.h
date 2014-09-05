/*
 * pthread_sem.h
 *
 *  Created on: 2012-6-26
 *      Author: lucid
 */

#ifndef __THREAD_SEM_F_H__
#define __THREAD_SEM_F_H__

#include <semaphore.h>

class CThreadSem_F
{
protected:
	sem_t 				m_sem;
	pthread_mutex_t 	mp ;
public:
	CThreadSem_F();
	~CThreadSem_F();

	operator sem_t()
	{
		return m_sem;
	}

	void SemPost();
	void SemClear();
	int  SemWait();
	void SemSetValue();
};

#endif /* __THREAD_SEM_F_H__ */
