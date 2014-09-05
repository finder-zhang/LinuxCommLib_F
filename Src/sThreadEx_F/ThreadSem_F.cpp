/*
 * pthread.cpp
 *
 *  Created on: 2012-6-26
 *      Author: lucid
 */

#include "ThreadSem_F.h"


CThreadSem_F::CThreadSem_F()
{
	sem_init(&m_sem,0,0);
}

CThreadSem_F::~CThreadSem_F()
{
	sem_destroy(&m_sem);
}

void CThreadSem_F::SemPost()
{
	sem_post(&m_sem);
}

void CThreadSem_F::SemClear()
{
	int iVal;
	do
	{
		sem_trywait(&m_sem);
		sem_getvalue(&m_sem,&iVal);
	}while(iVal);
}

int CThreadSem_F::SemWait()
{
	return sem_wait(&m_sem);
}

void CThreadSem_F::SemSetValue()
{

}
