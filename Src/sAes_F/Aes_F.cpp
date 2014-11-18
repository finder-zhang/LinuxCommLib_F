/*
 * Aes_F.cpp
 *
 *  Created on: 2014年10月23日
 *      Author: finder
 */

#include "Aes_F.h"

#include "DebugEx_F.h"

Aes_F::Aes_F() {
	_hAes = NULL;
}

Aes_F::~Aes_F() {
	if (NULL != _hAes) {
		AES_Deinit(_hAes);
	}
}

BOOL Aes_F::Init(const void* pKey,U8 uKeyLen,U8 uBlockLen)
{
	_hAes = AES_Init(pKey,uKeyLen,uBlockLen);
	return (NULL != _hAes);
}

BOOL Aes_F::Encrypt(const void* pPlain,U16 wInLen,void* pCipher,U16& wOutLen)
{
	if ( NULL == _hAes ) {
		return FALSE;
	}

	return AES_Encrypt(_hAes,pPlain,wInLen,pCipher,&wOutLen);
}

BOOL Aes_F::Encrypt(const vector<U8>& vtPlain,vector<U8>& vtCipher)
{
	if ( NULL == _hAes ) {
		return FALSE;
	}

	if (vtPlain.empty()) {
		return FALSE;
	}

	U16 wLen = 0;
	vtCipher.resize( vtPlain.size() + 32 );
	BOOL bRet = Encrypt(&vtPlain[0],vtPlain.size(),&vtCipher[0],wLen);
	vtCipher.resize(wLen);
	return bRet;
}

BOOL Aes_F::Decrypt(const void* pCipher,U16 wInLen,void* pPlain)
{
	if ( NULL == _hAes ) {
		return FALSE;
	}

	return AES_Decrypt(_hAes,pCipher,wInLen,pPlain);
}

BOOL Aes_F::Decrypt(const vector<U8>& vtCipher,vector<U8>& vtPlain)
{
	if ( NULL == _hAes ) {
		return FALSE;
	}

	if (vtCipher.empty()) {
		return FALSE;
	}
	vtPlain.resize(vtCipher.size());
	return Decrypt(&vtCipher[0],vtCipher.size(),&vtPlain[0]);
}

//int g_iVal = 10;
//
//void AesfDemo(void)
//{
//	Dsop("********************   %d\n",g_iVal);
//}































