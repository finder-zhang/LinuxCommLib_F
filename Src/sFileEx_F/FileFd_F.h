/*
 * file_fd_ex_f.h
 *
 *  Created on: Jul 3, 2012
 *      Author: lucid
 */
#ifndef __FILE_FD_F_H__
#define __FILE_FD_F_H__


class CFileFd_F
{
public:
	enum FILE_ACCESS_FLAG
	{
		FILE_ACCESS_FLAG_READ			= 0x00000001,
		FILE_ACCESS_FLAG_WRITE			= 0x00000002,
		FILE_ACCESS_FLAG_RDWR			= 0x00000003
	};

protected:
	int m_fd;

public:
	static int IsFileExist(const char* chName);

	CFileFd_F();
	virtual ~CFileFd_F();

	operator int()
	{
		return m_fd;
	}

	int Create(const char* chName,U32 dwFlag);				//return error if exist
	int CreateNewAlways(const char* chName,U32 dwFlag);	//create or open truncate to 0
	int OpenExist(const char* chName,U32 dwFlag);			//return error if not exist
	int CreateOrOpenExist(const char* chName,U32 dwFlag);	//create no truncate

	ssize_t Write(U32 dwPos,const void* pData,U32 dwLen);
	ssize_t Read(U32 dwPos,void* pData,U32 dwLen);
	int Flush();
	int Close();
	int SetLength(U32 uLen);
	U32 GetLength();
	U32 GetCurrentPos();
};








#endif //__FILE_FD_F_H__
