/*
 * DebugEx_F.cpp
 *
 *  Created on: 2014年9月5日
 *      Author: root
 */

#include "DebugEx_F.h"

#include "CommLib_F.h"

#include "stdarg.h"

//static int _DbgFd;
static FILE* _pDbgFile = NULL;

int CDebugExS_F::Open(int fd)
{
//	if ( _pDbgFile ) {
//		fclose( _pDbgFile );
//		_pDbgFile = NULL;
//	}
	_pDbgFile = fdopen(fd,"w");
	return (_pDbgFile != NULL);
}

int CDebugExS_F::Open(FILE* pFile)
{
	_pDbgFile = pFile;
	return TRUE;
}

int CDebugExS_F::Close()
{
	if ( _pDbgFile ) {
		fclose( _pDbgFile );
		_pDbgFile = NULL;
	}
	return TRUE;
}

int CDebugExS_F::Printf(const char* ch,...)
{
	va_list ap;
	va_start(ap,ch);
	return vfprintf(_pDbgFile,ch,ap);
//	int iLen = vfprintf(_pDbgFile,ch,ap);
//	va_end(ap);
//	return iLen;
}

int CDebugEx_F::Open(int fd)
{
	_pFile = fdopen(fd,"w");
	return _pFile != NULL;
}

int CDebugEx_F::Open(FILE* pFile)
{
	_pFile = pFile;
	return TRUE;
}

int CDebugEx_F::Close()
{
	if ( _pFile ) {
		fclose( _pFile );
		_pFile = NULL;
	}
	return TRUE;
}

int CDebugEx_F::Printf(const char* ch,...)
{
	va_list ap;
	va_start(ap,ch);
	return vfprintf(_pDbgFile,ch,ap);
}

































