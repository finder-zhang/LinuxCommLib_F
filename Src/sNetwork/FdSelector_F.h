/*
 * FdSelectorF.h
 *
 *  Created on: 2014年10月14日
 *      Author: finder
 *
 *   This class is use to convenience the select operate
 *   User can add fd to the select list continually,the select list include
 *   read,write and exception
 *
 *   We save the fd list as two formations,fd_set and FdArr_t.(the maybe list<fd> or vector<fd> or any else)
 *   If there is not any bugs,fd_set and FdArr_t will have the same content.
 *
 *   The format fd_set we use at select function.
 *   About the other format FdArr_t we have some other usage.
 *   First,we use to calculate the max fd use at select(),
 *   second,we return it to the user,let them know which and how many fds are selecting.
 *
 *   User will not get the fd_set because it just can parse by select.
 *
 *   Consider about the performance,this class will not as a high performance server.
 *
 */

#ifndef FDSELECTORF_H_
#define FDSELECTORF_H_

#include <sys/select.h>
#include <list>
using namespace std;

#include <CommLib_F.h>
#include <Mutex_F.h>

typedef list<FD_t> FdArr_t;

//this class use to return the whole result that which is selected
class CFdArr_F {
public:
	FdArr_t fsRead;
	FdArr_t fsWrite;
	FdArr_t fsExcept;
};

class CFdSelector_F {
protected:
	CFdArr_F _fdArr;			//record the fds need to select with FdArr_t format

	fd_set _fsRead;			//record the fds need to select with fd_set format
	fd_set _fsWrite;
	fd_set _fsExcept;

	FD_t _fdMaxRead;			//fd read set's max fd
	FD_t _fdMaxWrite;
	FD_t _fdMaxExcept;
	FD_t _fdMaxIndex;			//all max fd

	CMutex_F _mtxArrOpRead;
	CMutex_F _mtxArrOpWrite;
	CMutex_F _mtxArrOpExcept;

	FD_t GetMaxFdIndex();

public:
	CFdSelector_F();
	virtual ~CFdSelector_F();


//	FD_t GetMaxFdRead();
//	FD_t GetMaxFdWrite();
//	FD_t GetMaxFdExcept();

	void AddReadFd(FD_t fdRead);
	void AddWriteFd(FD_t fdWrite);
	void AddExceptFd(FD_t fdExcept);

	void SubReadFd(FD_t fdRead);
	void SubWriteFd(FD_t fdWrite);
	void SubExceptFd(FD_t fdExcept);

	CFdArr_F Select(struct timeval* time);			//Select all fd list,include RD WR and EXCEPT
	CFdArr_F Select(U32* pdwMilliSeconds);

	FdArr_t ReadSelect(struct timeval* time);		//Only select the read fd,most effective than Select
	FdArr_t ReadSelect(U32* pdwMilliSeconds);

	//get a fd in selected list,and pop a element from the list
	//return FALSE means fdArr is empty.
	static BOOL FdPopSet(FD_t& fd,FdArr_t& fdArr);

	static BOOL FdIsSet(FD_t fd, const FdArr_t& fdArr);		//check if a fd is in selected list
	static BOOL FdIsRead(FD_t fd, const CFdArr_F& fdset);
	static BOOL FdIsWrite(FD_t fd, const CFdArr_F& fdset);
	static BOOL FdIsExcept(FD_t fd, const CFdArr_F& fdset);
};

#endif /* FDSELECTORF_H_ */
