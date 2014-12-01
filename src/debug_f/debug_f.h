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
//#define Dprintf(...)			CDebugEx_F::Printf(__VA_ARGS__)
#endif //DEBUG


#define _TOSTR(str)		#str
#define TOSTR(str)		_TOSTR(str)


//use stdout as debug output
//Dsop means Debug standard out Print
//Want to use Dsop,remember to define DEBUG_F
//Dps means Debug check statement pass
//check if our program is block at some statement
#ifdef DEBUG_F
#define dsop(...)					fprintf(stdout,__VA_ARGS__)
#define Dps(statement)			dsop(TOSTR(pre enter [statement]\n)); statement; dsop(TOSTR(pass [statement]\n));
#define darr(p,len)				db_darr(p,len)
#else
#define dsop(...)
#define Dps(statement)			statement
#define darr(p,len)
#endif//DEBUG



class debugs_f
{
public:
	static int open(int fd);
	static int open(FILE* pFile);
	static int close();
	static int printf(const char* ch,...);
};


#define Oprintf(obj,...)		(obj).Printf(__VA_ARGS__)

class debug_f
{
protected:
	FILE* _pFile;

public:
	int open(int fd);
	int open(FILE* pFile);
	int close();
	int printf(const char* ch,...);
};


#endif /* DEBUGEX_F_H_ */
