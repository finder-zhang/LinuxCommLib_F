/*
 * DebugEx_F.cpp
 *
 *  Created on: 2014年9月5日
 *      Author: finder
 */

#include "debug_f.h"

#include <stdarg.h>

#include "comm_lib_f.h"



//static int _DbgFd;
static FILE* _pDbgFile = NULL;

int debugs_f::open(int fd)
{
//	if ( _pDbgFile ) {
//		fclose( _pDbgFile );
//		_pDbgFile = NULL;
//	}
	_pDbgFile = fdopen(fd,"w");
	return (_pDbgFile != NULL);
}

int debugs_f::open(FILE* pFile)
{
	_pDbgFile = pFile;
	return TRUE;
}

int debugs_f::close()
{
	if ( _pDbgFile ) {
		fclose( _pDbgFile );
		_pDbgFile = NULL;
	}
	return TRUE;
}

int debugs_f::printf(const char* ch,...)
{
	va_list ap;
	va_start(ap,ch);
	return vfprintf(_pDbgFile,ch,ap);
//	int iLen = vfprintf(_pDbgFile,ch,ap);
//	va_end(ap);
//	return iLen;
}







int debug_f::open(int fd)
{
	_pFile = fdopen(fd,"w");
	return _pFile != NULL;
}

int debug_f::open(FILE* pFile)
{
	_pFile = pFile;
	return TRUE;
}

int debug_f::close()
{
	if ( _pFile ) {
		fclose( _pFile );
		_pFile = NULL;
	}
	return TRUE;
}

int debug_f::printf(const char* ch,...)
{
	va_list ap;
	va_start(ap,ch);
	return vfprintf(_pDbgFile,ch,ap);
}

void db_darr(const void* pData,U16 wLen)
{
	const U8* p = (const U8*)pData;
	while(wLen--) {
		printf("%02x ",*p++);
	}
	printf("\n");
}































