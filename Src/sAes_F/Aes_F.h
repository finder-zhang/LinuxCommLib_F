/*
 * Aes_F.h
 *
 *  Created on: 2014年10月23日
 *      Author: finder
 *
 *  This class just package the cAesObj_F module as c++ interface.
 *  Want more information about aes , see about cAesObj_F.h
 */

#ifndef AES_F_H_
#define AES_F_H_

#include <CommLib_F.h>

#include <vector>
using namespace std;

#include "cAesObj_F.h"

class Aes_F {
public:
	AES_HANDLE			_hAes;

public:
	Aes_F();
	virtual ~Aes_F();

	BOOL Init(const void* pKey,U8 uKeyLen,U8 uBlockLen);

	BOOL BlockEncrypt(const void* pPlain,void* pCipher);
	BOOL BlockDecrypt(const void* pCipher,void* pPlain);

	void SetMode(eAES_MODE_t eMode);

	BOOL Encrypt(const void* pPlain,U16 wInLen,void* pCipher,U16& wOutLen);
	BOOL Encrypt(const vector<U8>& vtPlain,vector<U8>& vtCipher);

	BOOL Decrypt(const void* pCipher,U16 wInLen,void* pPlain);
	BOOL Decrypt(const vector<U8>& vtCipher,vector<U8>& vtPlain);
};


//void AesfDemo(void);

#endif /* AES_F_H_ */
