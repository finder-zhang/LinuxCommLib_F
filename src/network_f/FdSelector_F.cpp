/*
 * FdSelectorF.cpp
 *
 *  Created on: 2014年10月14日
 *      Author: root
 */

#include "FdSelector_F.h"

#include <bits/stl_algo.h>
//#include <algostuff.h>

CFdSelector_F::CFdSelector_F() {
	// TODO Auto-generated constructor stub
	_fdMaxIndex = 0;
	_fdMaxRead = 0;
	_fdMaxWrite = 0;
	_fdMaxExcept = 0;
	FD_ZERO(&_fsRead);
	FD_ZERO(&_fsWrite);
	FD_ZERO(&_fsExcept);
}

CFdSelector_F::~CFdSelector_F() {
	// TODO Auto-generated destructor stub
}

FD_t CFdSelector_F::GetMaxFdIndex()
{
	return max(max(_fdMaxRead,_fdMaxWrite),_fdMaxExcept);
}

static FD_t _GetMaxFd(const FdArr_t& fdArr)
{
	FD_t fdMax = 0;
	FdArr_t::const_iterator it;
	for (it = fdArr.begin(); it != fdArr.end(); ++it) {
		fdMax = max(fdMax,*it);
	}
	return fdMax;
}

static void _AddFd(FD_t fd,FdArr_t& fdArr,fd_set& fdSet,CMutex_F& mtx)
{
	FD_SET(fd,&fdSet);
	FdArr_t::iterator it;
	it = find( fdArr.begin(), fdArr.end(), fd );
	if ( fdArr.end() != it ) { // fd already in fdArr,no need to add
		return;
	}
	mtx.Lock();
	fdArr.push_back(fd);
	mtx.Unlock();
}

void CFdSelector_F::AddReadFd(FD_t fdRead)
{
	_AddFd(fdRead,_fdArr.fsRead,_fsRead,_mtxArrOpRead);
	_fdMaxRead = max(_fdMaxRead,fdRead);
}

void CFdSelector_F::AddWriteFd(FD_t fdWrite)
{
	_AddFd(fdWrite,_fdArr.fsWrite,_fsWrite,_mtxArrOpWrite);
	_fdMaxWrite = max(_fdMaxWrite,fdWrite);
}

void CFdSelector_F::AddExceptFd(FD_t fdExcept)
{
	_AddFd(fdExcept,_fdArr.fsExcept,_fsExcept,_mtxArrOpExcept);
	_fdMaxExcept = max(_fdMaxExcept,fdExcept);
}

static void _SubFd(FD_t fd,FdArr_t& fdArr,fd_set& fdSet,CMutex_F& mtx)
{
	FD_CLR(fd,&fdSet);
	FdArr_t::iterator it;
	it = find(fdArr.begin(),fdArr.end(),fd);
	if ( fdArr.end() == it ) { //not found,no need to erase
		return;
	}
	mtx.Lock();
	fdArr.erase(it);
	mtx.Unlock();
}

void CFdSelector_F::SubReadFd(FD_t fdRead)
{
	_SubFd(fdRead,_fdArr.fsRead,_fsRead,_mtxArrOpRead);
	if (fdRead >= _fdMaxRead) {
		_fdMaxRead = _GetMaxFd(_fdArr.fsRead);
		_fdMaxIndex = GetMaxFdIndex();
	}
}

void CFdSelector_F::SubWriteFd(FD_t fdWrite)
{
	_SubFd(fdWrite,_fdArr.fsWrite,_fsWrite,_mtxArrOpWrite);
	if ( fdWrite >= _fdMaxWrite ) {
		_fdMaxWrite = _GetMaxFd(_fdArr.fsWrite);
		_fdMaxIndex = GetMaxFdIndex();
	}
}

void CFdSelector_F::SubExceptFd(FD_t fdExcept)
{
	_SubFd(fdExcept,_fdArr.fsExcept,_fsExcept,_mtxArrOpExcept);
	if ( fdExcept>= _fdMaxExcept ) {
		_fdMaxExcept = _GetMaxFd(_fdArr.fsExcept);
		_fdMaxIndex = GetMaxFdIndex();
	}
}

CFdArr_F CFdSelector_F::Select(struct timeval* pTime)
{
	CFdArr_F fdArrReturn;
	fd_set fsCheckRead = _fsRead;
	fd_set fsCheckWrite = _fsWrite;
	fd_set fsCheckExcept = _fsExcept;
	select(_fdMaxIndex + 1,&fsCheckRead,&fsCheckWrite,&fsCheckExcept,pTime);
	FdArr_t::iterator it;
	for (it = _fdArr.fsRead.begin(); it != _fdArr.fsRead.end(); ++it ) {
		if ( FD_ISSET(*it,&fsCheckRead) ) {
			fdArrReturn.fsRead.push_back(*it);
		}
	}
	for (it = _fdArr.fsWrite.begin(); it != _fdArr.fsWrite.end(); ++it ) {
		if ( FD_ISSET(*it,&fsCheckWrite) ) {
			fdArrReturn.fsWrite.push_back(*it);
		}
	}
	for (it = _fdArr.fsExcept.begin(); it != _fdArr.fsExcept.end(); ++it ) {
		if ( FD_ISSET(*it,&fsCheckExcept) ) {
			fdArrReturn.fsExcept.push_back(*it);
		}
	}
	return fdArrReturn;
}

CFdArr_F CFdSelector_F::Select(U32* pdwMilliSeconds)
{
	struct timeval time;
	time.tv_sec = *pdwMilliSeconds / 1000;
	time.tv_usec = (*pdwMilliSeconds % 1000) * 1000;

	CFdArr_F fdArr = Select(&time);
	*pdwMilliSeconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return fdArr;
}

FdArr_t CFdSelector_F::ReadSelect(struct timeval* pTime)
{
	FdArr_t fdArrReturn;
	fd_set fsCheckRead = _fsRead;
	select(_fdMaxRead,&fsCheckRead,NULL,NULL,pTime);
	FdArr_t::iterator it;
	for (it = _fdArr.fsRead.begin(); it != _fdArr.fsRead.end(); ++it ) {
		if ( FD_ISSET(*it,&fsCheckRead) ) {
			fdArrReturn.push_back(*it);
		}
	}
	return fdArrReturn;
}

FdArr_t CFdSelector_F::ReadSelect(U32* pdwMilliSeconds)
{
	struct timeval time;
	time.tv_sec = *pdwMilliSeconds / 1000;
	time.tv_usec = ( *pdwMilliSeconds % 1000 ) * 1000;
	FdArr_t fdArrReturn = ReadSelect( &time );
	*pdwMilliSeconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return fdArrReturn;
}

//static
BOOL CFdSelector_F::FdPopSet(FD_t& fd,FdArr_t& fdArr)
{
	if ( fdArr.empty() ) {
		return FALSE;
	}
	fd = fdArr.front();
	fdArr.erase(fdArr.begin());
	return TRUE;
}

static BOOL _FdIsIn(FD_t fd,const FdArr_t& fdArr)
{
	FdArr_t::const_iterator it;
	it = find(fdArr.begin(),fdArr.end(),fd);
	return (fdArr.end() != it);
}

//static
BOOL CFdSelector_F::FdIsSet(FD_t fd,const FdArr_t& fdArr)
{
	return _FdIsIn(fd,fdArr);
}

//static
BOOL CFdSelector_F::FdIsRead(FD_t fd,const CFdArr_F& fdset)
{
	return _FdIsIn(fd,fdset.fsRead);
}

//static
BOOL CFdSelector_F::FdIsWrite(FD_t fd,const CFdArr_F& fdset)
{
	return _FdIsIn(fd,fdset.fsWrite);
}

//static
BOOL CFdSelector_F::FdIsExcept(FD_t fd,const CFdArr_F& fdset)
{
	return _FdIsIn(fd,fdset.fsExcept);
}






























