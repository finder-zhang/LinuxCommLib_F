
#include "data_package_f.h"
#include "data_package_impl_f.h"

#include "debug_f.h"



static U8 _CreateCRC(const U8* inBuf,U16 inLen);


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

//为了使CRC不会出现STX ETX 等特殊编码，把CRC拆成2个字节，每个
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
void dpkg_package(const void * inBuf,U16 inLen,void * outBuf,U16* outLen)
{
	U16 i = 0;
	U16 oi = EPOS_DATA;	//为了书写方便，使用中间变量 oi 而不使用 *outLen
	
	const U8* pIn = (const U8*)inBuf;
	U8* pOut = (U8*)outBuf;

	U16 wLen = 0;

	U8 uCRC = 0;
	U16 wCRC = 0;

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
	wLen = oi - EPOS_DOFFSET;	//这时 oi 位于 CRC处，oi - EPOS_DOFFSET 为数据长度
	pOut[EPOS_LEN0] = wLen << 4;
	pOut[EPOS_LEN1] = wLen & 0x00F0;
	pOut[EPOS_LEN2] = (wLen >> 4) & 0x00F0;
	pOut[EPOS_LEN3] = (wLen >> 8) & 0x00F0;
	
//处理校验
	uCRC = _CreateCRC(&pOut[EPOS_LEN0],wLen+EPOS_LENSIZE);	//CRC运算内容为长度与数据
	wCRC = _MakeU16CRC(uCRC);
	pOut[oi] = wCRC;
	++oi;
	pOut[oi] = wCRC >> 8;
	++oi;
	
//处理ETX
	pOut[oi] = CODE_ETX;
	++oi;
	
//处理总长度
	*outLen	= oi;	//outLen为打包输出的总长度，包括STX,ETX
}





//基础解包
BOOL dpkg_unpackage(const void * inBuf,U16 inLen,void * outBuf,U16* outLen)
{
	U16 i = 0;
	U16 oi = 0;

	const U8* pIn = (const U8*)inBuf;
	U8* pOut = (U8*)outBuf;

	U16 wLen = 0;
	U8 uCRC = 0;
	U8 uRxCRC = 0;

//执行初步数据正确性校验
	if ( CODE_STX != pIn[EPOS_STX] || CODE_ETX != pIn[inLen-1] )
	{
		*outLen = 0;
		dsop("stx etx verify failed!\r\n");
		return FALSE;
	}
	//Dsop("stx etx verify successful!\r\n");

//取得长度
	wLen = (pIn[EPOS_LEN0] >> 4) | pIn[EPOS_LEN1]
		| (pIn[EPOS_LEN2] << 4) | (pIn[EPOS_LEN3] << 8);
	
	if (wLen != (inLen - 8) ) {
		return FALSE;
	}

	//Dsop("data len = %d\r\n",wLen);

//检查CRC
	uCRC = _CreateCRC(pIn+EPOS_LEN0,wLen+EPOS_LENSIZE);
	uRxCRC = _MakeU8CRC(pIn[wLen+5] | (pIn[wLen+6])<<8 );
	//Dsop("crc = %02x,rxCrc = %02x\r\n",uCRC,uRxCRC);
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










inline static void _Rollback(dpkg_operator_t* pDO)
{
	pDO->rx_idx = 0;
	pDO->_cps = CPS_NULL;
}

inline static void _NewStart(dpkg_operator_t* pDO,U8 uByte)
{
	pDO->rx_buf[0] = uByte;
	pDO->rx_idx = 1;
	pDO->_cps = CPS_CATCHING;
}




dpkg_handle dpkg_open()
{
	return malloc(sizeof(dpkg_operator_t));
}

void dpkg_close(dpkg_handle hDP)
{
	if (hDP) {
		free(hDP);
	}
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
//is_pkged		use to lock the status
//rx_idx			use to count the package length
//rx_buf			is the package
CatchPackageStatus dpkg_catch_package(dpkg_handle hDP,U8 uByte)
{
	dpkg_operator_t* pDO = (dpkg_operator_t*)hDP;

	//数据包已经成功但并未被读取之前，丢弃输入的字节
	if ( TRUE == pDO->is_pkged ) {
		pDO->_cps = CPS_LOCKED;
		return pDO->_cps;
	}

	//任意时刻，只要见到 CODE_STX 就是一个全新的开始。
	if ( CODE_STX == uByte ) {
//		_cps = CPS_CATCHING;
//		rx_buf[0] = CODE_STX;
//		rx_idx = 1;
		_NewStart(pDO,uByte);
		return pDO->_cps;
	}


	if ( CODE_ETX == uByte ) {
		//收到 CODE_ETX 的时候，如果状态不对，则全部清空重来
		if ( pDO->_cps != CPS_CATCHING ) {
//			_cps = CPS_NULL;
//			rx_idx = 0;
			_Rollback(pDO);
			return pDO->_cps;
		}
		//收到 CODE_ETX 的时候，如果状态对，则数据包接收成功
		else {
			pDO->rx_buf[pDO->rx_idx] = CODE_ETX;
			++(pDO->rx_idx);
			pDO->_cps = CPS_COMPLETE;
			pDO->is_pkged = TRUE;
			return pDO->_cps;
		}
	}


	//收到其他的数据，在 CATCHING 状态下，把数据放起来
	if ( CPS_CATCHING ==  pDO->_cps ) {
		pDO->rx_buf[pDO->rx_idx] = uByte;
		++(pDO->rx_idx);
	}

	return pDO->_cps;
}


BOOL dpkg_get_package(dpkg_handle hDP,U16* pwLen,U8* pData)
{
	dpkg_operator_t* pDO = (dpkg_operator_t*)hDP;
	BOOL bDecode = FALSE;

	if ( FALSE == pDO->is_pkged ) {
		dsop("DEN_GetPackage bPackageOk = FALSE\r\n");
		return FALSE;
	}

//	Dsop("start Data Decode\r\n");
//	for (U16 i=0;i<rx_idx;++i)
//	{
//		Dsop("Decode[%02d] = %02x\r\n",i,rx_buf[i]);
//	}
	bDecode = dpkg_unpackage(pDO->rx_buf,pDO->rx_idx,pData,pwLen);
	pDO->is_pkged = FALSE;
	return bDecode;
}

BOOL dpkg_isbusy(dpkg_handle hDP)
{
	return ((dpkg_operator_t*)hDP)->is_pkged;
}



































































