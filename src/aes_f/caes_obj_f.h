/*
 * cAesHandle_F.h
 *
 *  Created on: 2014年10月28日
 *      Author: finder
 *
 *  For we can use aes as a object,and all the aes object
 *  can work independently.
 *  Without this object version ,we can just calculate
 *  only one module at a time.
 */

#ifndef CAES_OBJECT_F_H_
#define CAES_OBJECT_F_H_

#include <comm_lib_f.h>

typedef enum _AES_MODE
{
	EM_CBC = 0,
	EM_CFB,
	EM_OFB,
	EM_CTR,
	EM_ECB,
	EM_MAC,
}eAES_MODE_t;

typedef void* AES_HANDLE;

AES_HANDLE aes_open(const void* pKey,U8 uKeyLen,U8 uBlockLen);
BOOL aes_close(AES_HANDLE);

BOOL aes_encrypt(AES_HANDLE aes,const void* pPlain,U16 wInLen,void* pCipher,U16* pwOutLen);
BOOL aes_decrypt(AES_HANDLE aes,const void* pCipher,U16 wInLen,void* pPlain);

void aes_setmode(eAES_MODE_t mode);


#endif /* CAES_OBJECT_F_H_ */
