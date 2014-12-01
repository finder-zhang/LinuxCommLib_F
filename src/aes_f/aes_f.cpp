/*
 * Aes_F.cpp
 *
 *  Created on: 2014年10月23日
 *      Author: finder
 */

#include "aes_f.h"

#include "debug_f.h"

aes_f::aes_f() {
	_hAes = NULL;
}

aes_f::~aes_f() {
	if (NULL != _hAes) {
		aes_close(_hAes);
	}
}

BOOL aes_f::init(const void* pKey,U8 uKeyLen,U8 uBlockLen)
{
	_hAes = aes_open(pKey,uKeyLen,uBlockLen);
	return (NULL != _hAes);
}

BOOL aes_f::encrypt(const void* pPlain,U16 wInLen,void* pCipher,U16& wOutLen)
{
	if ( NULL == _hAes ) {
		return FALSE;
	}

	return aes_encrypt(_hAes,pPlain,wInLen,pCipher,&wOutLen);
}

BOOL aes_f::encrypt(const vector<U8>& vtPlain,vector<U8>& vtCipher)
{
	if ( NULL == _hAes ) {
		return FALSE;
	}

	if (vtPlain.empty()) {
		return FALSE;
	}

	U16 wLen = 0;
	vtCipher.resize( vtPlain.size() + 32 );
	BOOL bRet = encrypt(&vtPlain[0],vtPlain.size(),&vtCipher[0],wLen);
	vtCipher.resize(wLen);
	return bRet;
}

BOOL aes_f::decrypt(const void* pCipher,U16 wInLen,void* pPlain)
{
	if ( NULL == _hAes ) {
		return FALSE;
	}

	return aes_decrypt(_hAes,pCipher,wInLen,pPlain);
}

BOOL aes_f::decrypt(const vector<U8>& vtCipher,vector<U8>& vtPlain)
{
	if ( NULL == _hAes ) {
		return FALSE;
	}

	if (vtCipher.empty()) {
		return FALSE;
	}
	vtPlain.resize(vtCipher.size());
	return decrypt(&vtCipher[0],vtCipher.size(),&vtPlain[0]);
}































