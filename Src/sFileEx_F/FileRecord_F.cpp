/*
 * file_record_ex_f.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: lucid
 */

#include "CommLib_F.h"
#include <stdarg.h>
#include "FileRecord_F.h"


int CFileRecord_F::Printf(const char* ch,...)
{
	va_list argPtr;
	va_start(argPtr,ch);
	int iCount = 0;
	if (m_pFile)
	{
		iCount = vfprintf(m_pFile,ch,argPtr);
	}
	va_end(argPtr);
	Flush();
	return iCount;
}

int CFileRecord_F::AppendRecord(const char* chFileName)
{
	int iRet = CreateOrOpenExist(chFileName,FILE_ACCESS_FLAG_RDWR);
	if (RETURN_SUCCESS_F == iRet)
	{
		fseek(m_pFile,0,SEEK_END);
		return RETURN_SUCCESS_F;
	}
	else
		return RETURN_ERROR_F;
}

int CFileRecord_F::NewRecord(const char* chFileName)
{
	return CreateNewAlways(chFileName,FILE_ACCESS_FLAG_RDWR);
}









