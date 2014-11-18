/*
 * cAesObjImpl_F.h
 *
 *  Created on: 2014年10月28日
 *      Author: finder
 */

#ifndef CAESOBJIMPL_F_H_
#define CAESOBJIMPL_F_H_

#include <CommLib_F.h>

typedef struct _AES_OPERATOR
{
	unsigned char Plaintext[4][8]; //明文文本(加密的输入)
	unsigned char Ciphertext[4][8];//密文文本(加密结果)
	unsigned char Plaintext_out[4][8];//明文文本(解密得到的结果)
	unsigned char Ciphertext_in[4][8];//密文文本(解密的输入)

	unsigned char State[4][8];     //中间结果
	unsigned char Key[32];         //密钥
	unsigned char w[4][120];       //轮密钥调度表

	int LenText;                   //明密文长度(字节数),可为 16、24 或 32
	int LenKey;                    //密钥长度(字节数),可为 16、24 或 32
	int LenExpKey;                 //扩展密钥总长度(字节数),最大为 480
	int RoundNum;                  //轮数
	int Nb;                        //状态矩阵的列数
	int Nk;                        //密钥矩阵的列数
}AES_OPERATOR_t,*PAES_OPERATOR_t;

void AESIMPL_Init(PAES_OPERATOR_t aes,const void* pKey,U8 key_len,U8 uBlockLen);
void AESIMPL_Encrypt(PAES_OPERATOR_t aes,const void* pPlain,void* pCipher);
void AESIMPL_Decrypt(PAES_OPERATOR_t aes,const void* pCipher,void* pPlain);


#endif /* CAESOBJIMPL_F_H_ */
