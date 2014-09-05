/*
 * thread_event_f.h
 *
 *  Created on: 2012-6-18
 *      Author: lucid
 */

#ifndef __THREAD_EVENT_F_H__
#define __THREAD_EVENT_F_H__

#include <semaphore.h>

class CTthreadEvent_F
{
protected:
	sem_t m_sem;

public:
	CTthreadEvent_F();
	~CTthreadEvent_F();

	void SetEvent();
	void ResetEvent();
	int WaitEvent();
	int TimedWaitEvent(const struct timespec * time);
};


#endif /* __THREAD_EVENT_F_H__ */
