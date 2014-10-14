#include "DataTransEnDecode_F.h"

#include "DebugEx_F.h"


static U8 _CreateCRC(const U8* inBuf,U16 inLen);
static BOOL _DataEncode(const void * pIn,U16 inLen,void * pOut,U16* outLen);

//static U8 _CheckCRC(const U8* inBuf,U16 inLen);
static BOOL _DataDecode(const void * pIn,U16 inLen,void * pOout,U16* outLen);


//#define CODE_STX				(0x02)
//#define CODE_ETX				(0x03)

#define CODE_STX					(0xFA)
#define CODE_ETX					(0xFB)


enum OriginPos
{
	OPOS_STX		= 0,
	OPOS_LENL		= 1,
	OPOS_LENH		= 2,
	OPOS_DATA		= 3,
	
};

enum EncodePos
{
	EPOS_STX		= 0,
	EPOS_LEN0		= 1,
	EPOS_LEN1		= 2,
	EPOS_LEN2		= 3,
	EPOS_LEN3		= 4,
	EPOS_LENSIZE	= 4,
	EPOS_DATA		= 5,
	EPOS_DOFFSET	= 5	
};


//==============================================================
//													内部使用部份

//通过异或生成CRC
static U8 _CreateCRC(const U8* inBuf,U16 inLen)
{
	U8 uCRC = 0;
	while (inLen--) {
		uCRC ^= inBuf[inLen];
	}
	return uCRC;
}

//检查CRC的正确性，
//static U8 _CheckCRC(const U8* inBuf,U16 inLen)
//{
//	return inBuf[inLen] == _CreateCRC(inBuf,inLen - 1);
//}

//为了使CRC不会出现0x02 0x03 等特殊编码，把CRC拆成2个字节，每个
//字节的高4位放原来CRC的内容。
static U16 _MakeU16CRC(U8 uCRC)
{
	U16 wCRC = (uCRC << 4) | ( ((U16)uCRC) << 8 );
	return  wCRC & 0xF0F0;
}

static U8 _MakeU8CRC(U16 wCRC)
{
	return (wCRC >> 8) | (wCRC >> 4);
}

//基础打包
static BOOL _DataEncode(const void * inBuf,U16 inLen,void * outBuf,U16* outLen)
{
	U16 i = 0;
	U16 oi = EPOS_DATA;	//为了书写方便，使用中间变量 oi 而不使用 *outLen
	
	const U8* pIn = (const U8*)inBuf;
	U8* pOut = (U8*)outBuf;

//处理开始字节
	pOut[EPOS_STX] = CODE_STX;
	
//处理数据
	for	(i=0; i<inLen; ++i,++oi) {
		switch (pIn[i]) {
		//所有特殊码执行同样的动作，前面加'/'，后面最高位置1
		case CODE_STX:
		case CODE_ETX:
		case '/':
			pOut[oi] = '/';
			++oi;
			pOut[oi] = pIn[i] ^ 0x80;
			break;
		default:
		//非特殊码直接放到输出
			pOut[oi] = pIn[i];
			break;
		}
	}
	
//处理长度
	U16 wLen = oi - EPOS_DOFFSET;	//这时 oi 位于 CRC处，oi - EPOS_DOFFSET 为数据长度
	pOut[EPOS_LEN0] = wLen << 4;
	pOut[EPOS_LEN1] = wLen & 0x00F0;
	pOut[EPOS_LEN2] = (wLen >> 4) & 0x00F0;
	pOut[EPOS_LEN3] = (wLen >> 8) & 0x00F0;
	
//处理校验
	U8 uCRC = _CreateCRC(&pOut[EPOS_LEN0],wLen+EPOS_LENSIZE);	//CRC运算内容为长度与数据
	U16 wCRC = _MakeU16CRC(uCRC);
	pOut[oi] = wCRC;
	++oi;
	pOut[oi] = wCRC >> 8;
	++oi;
	
//处理ETX
	pOut[oi] = CODE_ETX;
	++oi;
	
//处理总长度
	*outLen	= oi;	//outLen为打包输出的总长度，包括STX,ETX
	return TRUE;
}





//基础解包
static BOOL _DataDecode(const void * inBuf,U16 inLen,void * outBuf,U16* outLen)
{
	U16 i = 0;
	U16 oi = 0;

	const U8* pIn = (const U8*)inBuf;
	U8* pOut = (U8*)outBuf;

//执行初步数据正确性校验
	if ( CODE_STX != pIn[EPOS_STX] || CODE_ETX != pIn[inLen-1] )
	{
		*outLen = 0;
		Dsop("stx etx verify failed!\r\n");
		return FALSE;
	}
	//Dsop("stx etx verify successful!\r\n");

//取得长度
	U16 wLen = (pIn[EPOS_LEN0] >> 4) | pIn[EPOS_LEN1]
		| (pIn[EPOS_LEN2] << 4) | (pIn[EPOS_LEN3] << 8);
	
	//Dsop("data len = %d\r\n",wLen);

//检查CRC
	U8 uCRC = _CreateCRC(pIn+EPOS_LEN0,wLen+EPOS_LENSIZE);
	U8 uRxCRC = _MakeU8CRC(pIn[wLen+5] | (pIn[wLen+6])<<8 );
	Dsop("crc = %02x,rxCrc = %02x\r\n",uCRC,uRxCRC);
	if ( uCRC != uRxCRC ) {
		*outLen = 0;
		return 0;
	}
	
//数据解包
	for (i=0; i<wLen; ++i,++oi)
	{
		//特殊码特殊处理
		if ( '/' == pIn[EPOS_DATA + i] ) {
			switch ( pIn[EPOS_DATA + i + 1] ) {
			case '/':
				pOut[oi] = '/';
				break;
			default:
				pOut[oi] = pIn[EPOS_DATA + i + 1] ^ 0x80;
				break;
			}
			++i;
		}
		//常规数据不用处理
		else {
			pOut[oi] = pIn[EPOS_DATA + i];
		}
	}
	
//处理总长度
	*outLen = oi;
	return TRUE;
}


void DataTransInit(PTransEnDecodeFunc_t pTransFunc)
{
	pTransFunc->pfnEncode = _DataEncode;
	pTransFunc->pfnDecode = _DataDecode;
}


static CatchPackageStatus		_cps = CPS_NULL;
static U8		_uRxBuf[256];
static U16		_wRxPtr = 0;
static volatile BOOL		_bPackageOk = FALSE;
//static U16		_wRxLen = 0;

inline static void _Rollback()
{
	_wRxPtr = 0;
	_cps = CPS_NULL;
}

inline static void _NewStart(U8 uByte)
{
	_uRxBuf[0] = uByte;
	_wRxPtr = 1;
	_cps = CPS_CATCHING;
}


//Pass the receive datas byte by byte,and this function will
//catch the content between 0x02 and 0x03,and 0x02 0x03 is included
//For example there is a series like
//0x01 0x02 0x81 0x82 0x83 0x03 0x04 0x05 0x02 ... 0x03
//the first byte 0x01 will be drop,and the sub series
//0x02 0x81 0x82 0x83 0x03 will be catch
//and the below 0x04 0x05 will be dropped.

//When DEN_CatchPackage returns CPS_COMPLETE,it will lock the status
//continue call DEN_CatchPackage will return CPS_LOCKED.
//Till we call DEN_GetPackage to get the result,
//the status will be unlock and we can start a new DEN_CatchPackage

//About the returns
//When DEN_CatchPackage got a package successful,
//it will lock the status and fill the result via some global variables.
//_bPackageOk		use to lock the status
//_wRxPtr			use to count the package length
//_uRxBuf			is the package
CatchPackageStatus DEN_CatchPackage(U8 uByte)
{
	//数据包已经成功但并未被读取之前，丢弃输入的字节
	if ( TRUE == _bPackageOk ) {
		_cps = CPS_LOCKED;
		return _cps;
	}

	//任意时刻，只要见到 CODE_STX 就是一个全新的开始。
	if ( CODE_STX == uByte ) {
//		_cps = CPS_CATCHING;
//		_uRxBuf[0] = CODE_STX;
//		_wRxPtr = 1;
		_NewStart(uByte);
		return _cps;
	}


	if ( CODE_ETX == uByte ) {
		//收到 CODE_ETX 的时候，如果状态不对，则全部清空重来
		if ( _cps != CPS_CATCHING ) {
//			_cps = CPS_NULL;
//			_wRxPtr = 0;
			_Rollback();
			return _cps;
		}
		//收到 CODE_ETX 的时候，如果状态对，则数据包接收成功
		else {
			_uRxBuf[_wRxPtr] = CODE_ETX;
			++_wRxPtr;
			_cps = CPS_COMPLETE;
			_bPackageOk = TRUE;
			return _cps;
		}
	}


	//收到其他的数据，在 CATCHING 状态下，把数据放起来
	if ( CPS_CATCHING == _cps ) {
		_uRxBuf[_wRxPtr] = uByte;
		++_wRxPtr;
	}

	return _cps;
}


BOOL DEN_GetPackage(U16* pwLen,U8* pData)
{
	if ( FALSE == _bPackageOk ) {
		Dsop("DEN_GetPackage bPackageOk = FALSE\r\n");
		return FALSE;
	}

	Dsop("start Data Decode\r\n");
	for (U16 i=0;i<_wRxPtr;++i)
	{
		Dsop("Decode[%02d] = %02x\r\n",i,_uRxBuf[i]);
	}
	BOOL bDecode = _DataDecode(_uRxBuf,_wRxPtr,pData,pwLen);
	_bPackageOk = FALSE;
	return bDecode;
}

BOOL DEN_IsBusy()
{
	return _bPackageOk;
}



































































