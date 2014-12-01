/*******************************************
数据传输编码与解码
*******************************************/


#ifndef __DATA_TRANS_EN_DECODE_F_H__
#define __DATA_TRANS_EN_DECODE_F_H__

#include "comm_lib_f.h"

#include "stdint.h"

#ifndef __cplusplus
//#define __cplusplus
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
//typedef BOOL (*fnTransEnDecode_t)(const void* inBuf,U16 inLen,void* outBuf,U16* outLen);

typedef void*			dpkg_handle;

typedef enum _CatchPackageStatus
{
	CPS_NULL			= 0,
	CPS_CATCHING		,
	CPS_COMPLETE		,
	CPS_LOCKED
//	CPS_DATA_ERROR
}CatchPackageStatus;

dpkg_handle dpkg_open();
void dpkg_close(dpkg_handle hDP);

//This function use in serial "get byte interrupt".
//If your serial have not so call "get byte interrupt" but
//just a got something interrupt,please make the get byte interrupt yourself.
//Anyhow,every byte we got,pass to DPKG_CatchPackage and check the result.
CatchPackageStatus dpkg_catch_package(dpkg_handle hDP,U8 uByte);

//When DEN_CatchPackage returns CPS_COMPLETE,continue call
//DEN_CatchPackage will returns CPS_LOCKED.
//Till we call DEN_GetPackage to get the result,
//the status will be unlock and we can start a new DPKG_CatchPackage
BOOL dpkg_get_package(dpkg_handle hDP,U16* pwLen,U8* pData);

//DEN_IsBusy will return true when the status is locked.
BOOL dpkg_isbusy(dpkg_handle hP);

void dpkg_package(const void * pIn,U16 inLen,void * pOut,U16* outLen);
BOOL dpkg_unpackage(const void * pIn,U16 inLen,void * pOut,U16* outLen);

#ifdef __cplusplus
}
#endif //



#ifdef __cplusplus
class data_package_f
{
protected:
	dpkg_handle		_pkg;

public:
	data_package_f(){_pkg = dpkg_open();}
	~data_package_f(){dpkg_close(_pkg);}

	CatchPackageStatus catch_package(U8 uByte){return dpkg_catch_package(_pkg,uByte);}
	BOOL get_package(U16* pwLen,U8* pData){return dpkg_get_package(_pkg,pwLen,pData);}
	BOOL isbusy(){return dpkg_isbusy(_pkg);}

	static void package(const void* pIn,U16 inLen,void* pOut,U16* outLen)
	{dpkg_package(pIn,inLen,pOut,outLen);}
	static BOOL unpackage(const void * pIn,U16 inLen,void * pOut,U16* outLen)
	{return dpkg_unpackage(pIn,inLen,pOut,outLen);}
};
#endif //__cplusplus



#endif //__DATA_TRANS_EN_DECODE_F_H__
