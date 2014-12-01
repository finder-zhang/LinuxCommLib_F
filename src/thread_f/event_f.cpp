/*
 * thread_event.cpp
 *
 *  Created on: 2012-6-18
 *      Author: finder
 */
#include "comm_lib_f.h"

#include "event_f.h"


CTthreadEvent_F::CTthreadEvent_F()
{
	sem_init(&m_sem,0,0);
}

CTthreadEvent_F::~CTthreadEvent_F()
{
	sem_destroy(&m_sem);
}

void CTthreadEvent_F::SetEvent()
{
	int iVal;
	sem_getvalue(&m_sem,&iVal);
	if (0 == iVal)
	{
		sem_post(&m_sem);
	}
}

void CTthreadEvent_F::ResetEvent()
{
	int iVal;
	do
	{
		sem_trywait(&m_sem);
		sem_getvalue(&m_sem,&iVal);
	}while(iVal);
}

int CTthreadEvent_F::WaitEvent()
{
//	int iVal;
//	sem_getvalue(&m_sem,&iVal);
//	DBG_PRINT("sem value = %d\n",iVal);
	return sem_wait(&m_sem);
}

int CTthreadEvent_F::TimedWaitEvent(const struct timespec * time)
{
	return sem_timedwait(&m_sem,time);
}






