/*
 * cAesObj_F.cpp
 *
 *  Created on: 2014年10月28日
 *      Author: finder
 */

#include "cAesObj_F.h"
#include "cAesObjImpl_F.h"



AES_HANDLE AES_Init(const void* pKey,U8 uKeyLen,U8 uBlockLen)
{
	AES_OPERATOR_t * pAes = (AES_OPERATOR_t*)malloc(sizeof(AES_OPERATOR_t));
	AESIMPL_Init(pAes,pKey,uKeyLen,uBlockLen);
	return pAes;
}

BOOL AES_Deinit(AES_HANDLE aes)
{
	free(aes);
	return TRUE;
}

//void AES_BlockEncrypt(AES_HANDLE aes,const void* pPlain,void* pCipher)
//{
//	AESIMPL_Encrypt((PAES_OPERATOR_t)aes,pPlain,pCipher);
//}
//
//void AES_BlockDecrypt(AES_HANDLE aes,const void* pCipher,void* pPlain)
//{
//	AESIMPL_Decrypt((PAES_OPERATOR_t)aes,pCipher,pPlain);
//}

BOOL AES_Encrypt(AES_HANDLE aes,const void* pPlain,U16 wInLen,void* pCipher,U16* pwOutLen)
{
	U8 uPlainTemp[32];
	const U8* pIn = (const U8*)pPlain;
	U8* pOut = (U8*)pCipher;

	PAES_OPERATOR_t pAes = (PAES_OPERATOR_t)aes;
	int LenText = pAes->LenText;


	//while length longer than block size,encrypt block by block
	while (wInLen >= LenText)
	{
		AESIMPL_Encrypt(pAes,pIn,pOut);
		pIn += LenText;
		pOut += LenText;
		wInLen -= LenText;
		*pwOutLen += LenText;
	}

	//if leave some data shorter than block size
	if (wInLen) {
		memset(uPlainTemp,0,LenText);
		memcpy(uPlainTemp,pIn,wInLen);
		AESIMPL_Encrypt(pAes,uPlainTemp,pOut);
		*pwOutLen += LenText;
	}
	return TRUE;
}

BOOL AES_Decrypt(AES_HANDLE aes,const void* pCipher,U16 wInLen,void* pPlain)
{
	PAES_OPERATOR_t pAes = (PAES_OPERATOR_t)aes;
	int LenText = pAes->LenText;

	if (wInLen % LenText) {
		return FALSE;
	}

	const U8* pIn = (const U8*)pCipher;
	U8* pOut = (U8*)pPlain;

	while (wInLen >= LenText) {
		AESIMPL_Decrypt(pAes,pIn,pOut);
		pIn += LenText;
		pOut += LenText;
		wInLen -= LenText;
	}
	return TRUE;
}

void AES_SetMode(eAES_MODE_t mode)
{

}





