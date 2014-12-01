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

#include <comm_lib_f.h>

#include <vector>
using namespace std;

#include "caes_obj_f.h"

class aes_f {
public:
	AES_HANDLE			_hAes;

public:
	aes_f();
	virtual ~aes_f();

	BOOL init(const void* pKey,U8 uKeyLen,U8 uBlockLen);

	BOOL block_en(const void* pPlain,void* pCipher);
	BOOL block_de(const void* pCipher,void* pPlain);

	void setmode(eAES_MODE_t eMode);

	BOOL encrypt(const void* pPlain,U16 wInLen,void* pCipher,U16& wOutLen);
	BOOL encrypt(const vector<U8>& vtPlain,vector<U8>& vtCipher);

	BOOL decrypt(const void* pCipher,U16 wInLen,void* pPlain);
	BOOL decrypt(const vector<U8>& vtCipher,vector<U8>& vtPlain);
};


//void AesfDemo(void);

#endif /* AES_F_H_ */
