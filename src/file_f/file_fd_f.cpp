/*
 * file_fd_ex_f.cpp
 *
 *  Created on: Jul 3, 2012
 *      Author: lucid
 */

#include "comm_lib_f.h"

#include <fcntl.h>
#include <unistd.h>
//#include <sys/types.h>
#include <sys/stat.h>

#include "file_fd_f.h"




int CFileFd_F::IsFileExist(const char* chName)
{
	return (0 == access(chName,F_OK)) ? RETURN_SUCCESS_F : RETURN_ERROR_F;
}

CFileFd_F::CFileFd_F()
{
	m_fd = -1;
}

CFileFd_F::~CFileFd_F()
{
	Close();
}

int CFileFd_F::Create(const char* chName,U32 dwFlag)				//return error if exist
{
	if(IsFileExist(chName))
		return RETURN_ERROR_F;

	int iFlag = O_CREAT | O_EXCL;
	if(FILE_ACCESS_FLAG_READ == dwFlag)
		iFlag |= O_RDONLY;
	else if(FILE_ACCESS_FLAG_WRITE == dwFlag)
		iFlag |= O_WRONLY;
	else if(FILE_ACCESS_FLAG_RDWR == dwFlag)
		iFlag |= O_RDWR;

	m_fd = open(chName,iFlag,S_IREAD | S_IWRITE);
	return (-1 == m_fd) ? RETURN_ERROR_F : RETURN_SUCCESS_F ;
}

int CFileFd_F::CreateNewAlways(const char* chName,U32 dwFlag)	//create or open truncate to 0
{
	int iFlag = O_CREAT | O_TRUNC;
	if(FILE_ACCESS_FLAG_READ & dwFlag)
	{
		iFlag |= O_RDWR;
	}
	else
	{
		iFlag |= O_WRONLY;
	}
	m_fd = open(chName,iFlag,S_IREAD | S_IWRITE);
	return (-1 == m_fd) ? RETURN_ERROR_F : RETURN_SUCCESS_F ;
}

int CFileFd_F::OpenExist(const char* chName,U32 dwFlag)			//return error if not exist
{
	if (!IsFileExist(chName))
		return RETURN_ERROR_F;

	int iFlag = 0;
	if(FILE_ACCESS_FLAG_READ == dwFlag)
		iFlag |= O_RDONLY;
	else if(FILE_ACCESS_FLAG_WRITE == dwFlag)
		iFlag |= O_WRONLY;
	else if(FILE_ACCESS_FLAG_RDWR == dwFlag)
		iFlag |= O_RDWR;
	m_fd = open(chName,iFlag);
	return (-1 == m_fd) ? RETURN_ERROR_F : RETURN_SUCCESS_F ;
}

int CFileFd_F::CreateOrOpenExist(const char* chName,U32 dwFlag)	//create no truncate
{
	if (IsFileExist(chName))
		return OpenExist(chName,dwFlag);
	else
		return Create(chName,dwFlag);
}

ssize_t CFileFd_F::Write(U32 dwPos,const void* pData,U32 dwLen)
{
	lseek(m_fd,dwPos,SEEK_SET);
	ssize_t siLen = write(m_fd,pData,dwLen);
	Flush();
	return siLen;
}


ssize_t CFileFd_F::Read(U32 dwPos,void* pData,U32 dwLen)
{
	lseek(m_fd,dwPos,SEEK_SET);
	return read(m_fd,pData,dwLen);
}

int CFileFd_F::Flush()
{
	fsync(m_fd);
	return RETURN_SUCCESS_F;
}

int CFileFd_F::Close()
{
	if(-1 != m_fd)
	{
		return (0 == close(m_fd)) ? RETURN_SUCCESS_F : RETURN_ERROR_F;
	}
	return RETURN_ERROR_F;
}

ssize_t CFileFd_F::GetLength()
{
	ssize_t iLen,iCurPos;
	iCurPos = lseek(m_fd,0,SEEK_CUR);
	iLen = lseek(m_fd,0,SEEK_END);
	lseek(m_fd,iCurPos,SEEK_SET);
	return iLen;
}

int CFileFd_F::SetLength(U32 uLen)
{
	return 0 == ftruncate(m_fd,uLen) ? RETURN_SUCCESS_F : RETURN_ERROR_F;
}

ssize_t CFileFd_F::GetCurrentPos()
{
	return lseek(m_fd,0,SEEK_CUR);
}





