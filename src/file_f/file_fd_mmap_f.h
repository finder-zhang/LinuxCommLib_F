/*
 * file_fd_mmap_ex_f.h
 *
 *  Created on: Jul 3, 2012
 *      Author: finder ZHANG
 *
 *  Last Version Oct 12 2012 afternoon
 *
 *  We have 3 way to use this memory mapping file
 *
 *  1 use CFileFd open a fd,and then mapping the file
 *    use GetDataAddr() to get the memory address mapping at the file
 *
 *
 *  2 use CFileFd create a fd,and then set the length of the file and map it.
 *    then use GetDataAddr() to get the memory address mapping at the file
 *
 *    the template code is below
 *
 *    CFileFdMmap_F mapFile;
 *    mapFile.CreateOrOpenExist(...);
 *    mapFile.OpenMap(size);
 *    CMyData* pMyData = (CMyData*)GetDataAddr();
 *    pMyData->m_iXXXX = 10;
 *    mapFile.Close();
 *
 *
 *
 *  3 use FileNew to create a file
 *    CMyClass* pMyClass = FileNew<CMyClass>("MyFileName")
 *    it equal to create a fd named "MyFileName"
 *    then set the file size with sizeof(CMyClass)
 *    then mmap the file and "place new" a CMyClass at the memory address at GetDataAddr()
 *
 *    the template code is below
 *
 *    //it will run CMyClass's ctor,just like new operator,but the memory allocated is mapping to a file
 *    //will save at disk.
 *    CFileFdMmap_F mapFile;
 *    CMyClass* pMyClass = mapFile.FileNew<CMyClass>("MyFileName");
 *    pMyClass->m_iXXXX = 10;
 *    mapFile.Close();
 *
 *
 */

#ifndef __FILE_FD_MMAP_F_H_
#define __FILE_FD_MMAP_F_H_

#include "file_fd_f.h"

class CFileFdMmap_F : public CFileFd_F
{
protected:
	U8*		m_pData;
public:
	CFileFdMmap_F();
	~CFileFdMmap_F();

	ssize_t Write(ssize_t iPos,const void* pData,ssize_t iLen);
	ssize_t Read(ssize_t iPos,void* pData,ssize_t iLen);

	int Flush();
	int Close();
	void* GetDataAddr();



	int OpenMap(U32 dwLen);

	template<typename T1>
	T1* FileNew(const char* chFileName);
	int CloseMap();
};


template<typename T1>
T1* CFileFdMmap_F::FileNew(const char* chFileName)
{
	CreateNewAlways(chFileName,CFileFd_F::FILE_ACCESS_FLAG_RDWR);
	if ( OpenMap(sizeof(T1)) == RETURN_ERROR_F )
		return 0;
	new(m_pData)T1;
	return (T1*)m_pData;
}

#endif /* __FILE_FD_MMAP_F_H_ */
