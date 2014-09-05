/*
 * MemMonitor_F.cpp
 *
 *  Created on: Aug 30, 2012
 *      Author: lucid
 */
#include "CommLib_F.h"
#include <unistd.h>
#include <string.h>
#include <string>
using std::string;
#include <vector>
using std::vector;


#include "MemMonitor_F.h"
#include "File_F.h"

CMemMonitor_F::CMemMonitor_F()
{
	m_pFileReport = 0;
	m_dwUSecond = 0;
	m_iPID = 0;
	m_bMonitorLoop = 0;
}

CMemMonitor_F::~CMemMonitor_F()
{

}

int CMemMonitor_F::InitMonitor(FILE* pFile,__useconds_t uSecond,int iPID)
{
	return SetReportFILE(pFile)
			&& SetReportInterval(uSecond)
			&& SetReportPID(iPID);
}

int CMemMonitor_F::SetReportFILE(FILE* pFile)
{
	if(0 == pFile)
		return RETURN_ERROR_F;
	m_pFileReport = pFile;
	return RETURN_SUCCESS_F;
}

int CMemMonitor_F::SetReportInterval(__useconds_t uSecond)
{
	m_dwUSecond = uSecond;
	return RETURN_SUCCESS_F;
}

int CMemMonitor_F::SetReportPID(__pid_t iPID)
{
	if(-1 == iPID)
		m_iPID = getpid();
	else
		m_iPID = iPID;
	return RETURN_SUCCESS_F;
}

int CMemMonitor_F::StartMonitor()
{
	return m_ThMonitor.Create(MonitorThread,this);
}

int CMemMonitor_F::PauseMonitor()
{
	return m_ThMonitor.SuspendThread();
}

int CMemMonitor_F::ResumeMonitor()
{
	return m_ThMonitor.ResumeThread();
}

int CMemMonitor_F::StopMonitor()
{
	if (0 == m_bMonitorLoop)
		return RETURN_ERROR_F;
	m_bMonitorLoop = 0;
	return RETURN_SUCCESS_F;
}

//static
void* CMemMonitor_F::MonitorThread(void* pData)
{
	CMemMonitor_F* pThis = (CMemMonitor_F*)pData;
	return pThis->MonitorImpl();
}

void* CMemMonitor_F::MonitorImpl()
{
	m_bMonitorLoop = 1;
	while(m_bMonitorLoop)
	{
		DumpMemInfo();
		usleep(m_dwUSecond);
	}
	return 0;
}

int CMemMonitor_F::DumpMemInfo()
{
	if (0 ==  m_pFileReport)
		return RETURN_ERROR_F;

	char ch[128];
	const string chTempFile = GetProcPath() + "TempInfo";
	sprintf(ch,"cat /proc/%d/status > %s",int(m_iPID),chTempFile.c_str());
	system(ch);

	CFile_F file;
	file.OpenExist(chTempFile.c_str(),CFile_F::FILE_ACCESS_FLAG_RDWR);

	vector<char> chFile(file.GetLength());
	file.Read(0,&chFile[0],file.GetLength());

	string str(&chFile[0]);
	string::size_type iPosSta,iPosEnd;
	iPosSta = str.find("VmRSS:") + strlen("VmRSS:");
	iPosSta = str.find_first_not_of(" \t",iPosSta);
	iPosEnd = str.find_first_of(' ',iPosSta);

	int iLen = iPosEnd-iPosSta;

	vector<char> vChVmRSS(iLen+1,0);
	memcpy(&vChVmRSS[0],&str[iPosSta],iLen);

	time_t tNow;
	tNow = time(&tNow);
	struct tm* tmNow = localtime(&tNow);

	fprintf(m_pFileReport,"%04d_%02d_%02d,%02d:%02d:%02d Memory = %s k\n",
			tmNow->tm_year+1900,tmNow->tm_mon,tmNow->tm_mday,
			tmNow->tm_hour,tmNow->tm_min,tmNow->tm_sec,
			&vChVmRSS[0]);
	fflush(m_pFileReport);

	return RETURN_SUCCESS_F;
}


















