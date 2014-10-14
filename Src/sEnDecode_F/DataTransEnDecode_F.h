/*******************************************
数据传输编码与解码
*******************************************/


#ifndef __DATA_TRANS_EN_DECODE_F_H__
#define __DATA_TRANS_EN_DECODE_F_H__

#include "CommLib_F.h"

#ifndef __cplusplus
#define __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif //

//打包与解包接口函数
//对于打包时
//inBuf		要输入的内容	长度（2B）数据（=长度）
//inLen		要输入的长度	也就是inBuf的长度
//outBuf	输出的内容		STX（1B）长度（4B）输入内容整理后（=长度）CRCL（1B）CRCH（1B）ETX（1B）
//outLen	输出的长度		以上总长度

//对于解包时
//inBuf		要解包的内容	STX（1B）长度（4B）输入内容整理后（=长度）CRCL（1B）CRCH（1B）ETX（1B）
//inLen		要解包的长度	以上总长度
//outBuf	数据内容		长度（2B）数据（=长度）
//outLen	数据长度		以上总长度
typedef BOOL (*fnTransEnDecode_t)(const void* inBuf,U16 inLen,void* outBuf,U16* outLen);


typedef struct _TransEnDecodeFunc
{
	fnTransEnDecode_t		pfnEncode;
	fnTransEnDecode_t		pfnDecode;
}TransEnDecodeFunc_t,*PTransEnDecodeFunc_t;

typedef enum _CatchPackageStatus
{
	CPS_NULL			= 0,
	CPS_CATCHING		,
	CPS_COMPLETE		,
	CPS_LOCKED
//	CPS_DATA_ERROR
}CatchPackageStatus;




void DataTransInit(PTransEnDecodeFunc_t pTransFunc);





//This function use in serial "get byte interrupt".
//If your serial have not so call "get byte interrupt" but
//just a got something interrupt,please make the get byte interrupt yourself.
//Anyhow,every byte we got,pass to DEN_CatchPackage and check the result.
CatchPackageStatus DEN_CatchPackage(U8 uByte);


//When DEN_CatchPackage returns CPS_COMPLETE,continue call
//DEN_CatchPackage will returns CPS_LOCKED.
//Till we call DEN_GetPackage to get the result,
//the status will be unlock and we can start a new DEN_CatchPackage
BOOL DEN_GetPackage(U16* pwLen,U8* pData);


//DEN_IsBusy will return true when the status is locked.
BOOL DEN_IsBusy();



#ifdef __cplusplus
}
#endif //


#endif //__DATA_TRANS_EN_DECODE_F_H__
