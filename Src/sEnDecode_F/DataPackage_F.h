/*******************************************
数据传输编码与解码
*******************************************/


#ifndef __DATA_TRANS_EN_DECODE_F_H__
#define __DATA_TRANS_EN_DECODE_F_H__

#include "CommLib_F.h"

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

typedef void*			DPackageHandle;

typedef enum _CatchPackageStatus
{
	CPS_NULL			= 0,
	CPS_CATCHING		,
	CPS_COMPLETE		,
	CPS_LOCKED
//	CPS_DATA_ERROR
}CatchPackageStatus;

DPackageHandle DPKG_Open();
void DPKG_Close(DPackageHandle hDP);

//This function use in serial "get byte interrupt".
//If your serial have not so call "get byte interrupt" but
//just a got something interrupt,please make the get byte interrupt yourself.
//Anyhow,every byte we got,pass to DPKG_CatchPackage and check the result.
CatchPackageStatus DPKG_CatchPackage(DPackageHandle hDP,U8 uByte);

//When DEN_CatchPackage returns CPS_COMPLETE,continue call
//DEN_CatchPackage will returns CPS_LOCKED.
//Till we call DEN_GetPackage to get the result,
//the status will be unlock and we can start a new DPKG_CatchPackage
BOOL DPKG_GetPackage(DPackageHandle hDP,U16* pwLen,U8* pData);

//DEN_IsBusy will return true when the status is locked.
BOOL DPKG_IsBusy(DPackageHandle hP);

void DPKG_DataPackage(const void * pIn,U16 inLen,void * pOut,U16* outLen);
BOOL DPKG_DataUnpackage(const void * pIn,U16 inLen,void * pOut,U16* outLen);

#ifdef __cplusplus
}
#endif //



#ifdef __cplusplus
class CDataPackage_F
{
protected:
	DPackageHandle		_hPkg;

public:
	CDataPackage_F(){_hPkg = DPKG_Open();}
	~CDataPackage_F(){DPKG_Close(_hPkg);}

	CatchPackageStatus CatchPackage(U8 uByte){return DPKG_CatchPackage(_hPkg,uByte);}
	BOOL GetPackage(U16* pwLen,U8* pData){return DPKG_GetPackage(_hPkg,pwLen,pData);}
	BOOL IsBusy(){return DPKG_IsBusy(_hPkg);}

	static void DataPackage(const void* pIn,U16 inLen,void* pOut,U16* outLen)
	{DPKG_DataPackage(pIn,inLen,pOut,outLen);}
	static BOOL DataUnpackage(const void * pIn,U16 inLen,void * pOut,U16* outLen)
	{return DPKG_DataUnpackage(pIn,inLen,pOut,outLen);}
};
#endif //__cplusplus



#endif //__DATA_TRANS_EN_DECODE_F_H__
