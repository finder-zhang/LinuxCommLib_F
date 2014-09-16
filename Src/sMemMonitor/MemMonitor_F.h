/*
 * MemMonitor_F.h
 *
 *  Created on: Aug 30, 2012
 *      Author: finder
 */

#ifndef __MEMMONITOR_F_H__
#define __MEMMONITOR_F_H__

#include <stdio.h>
//#include "Thread_F.h"
#include "Thread_F.h"

class CMemMonitor_F
{
protected:
	FILE*			m_pFileReport;
	__useconds_t	m_dwUSecond;
	__pid_t			m_iPID;
	int				m_bMonitorLoop;
	CThread_F		m_ThMonitor;

public:
	CMemMonitor_F();
	virtual ~CMemMonitor_F();

	int InitMonitor(FILE* pFile,__useconds_t uSecond,int iPID);

	int SetReportFILE(FILE* pFile);
	int SetReportInterval(__useconds_t uSecond);
	int SetReportPID(int iPID);

	int StartMonitor();
	int PauseMonitor();
	int ResumeMonitor();
	int StopMonitor();

	static void* MonitorThread(void* pData);
	void* MonitorImpl();

	int DumpMemInfo();
};


#endif /* __MEMMONITOR_F_H__ */
