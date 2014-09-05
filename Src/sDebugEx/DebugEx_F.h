/*
 * DebugEx_F.h
 *
 *  Created on: 2014年9月5日
 *      Author: root
 */

#ifndef DEBUGEX_F_H_
#define DEBUGEX_F_H_

#include <stdio.h>

#ifdef DEBUG
#define Dprintf(...)			CDebugEx_F::Printf(__VA_ARGS__)
#endif //DEBUG



class CDebugExS_F
{
public:
	static int Open(int fd);
	static int Open(FILE* pFile);
	static int Close();
	static int Printf(const char* ch,...);
};


#define Oprintf(obj,...)		(obj).Printf(__VA_ARGS__)

class CDebugEx_F
{
protected:
	FILE* _pFile;

public:
	int Open(int fd);
	int Open(FILE* pFile);
	int Close();
	int Printf(const char* ch,...);
};


#endif /* DEBUGEX_F_H_ */
