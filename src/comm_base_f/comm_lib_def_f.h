/*
 * CommLibInc.h
 *
 *  Created on: 2012-8-16
 *      Author: lucid
 */

#ifndef __COMM_LIB_INC_F_H__
#define __COMM_LIB_INC_F_H__

#include <stdint.h>

//warning: these typedef is only for 32 bit or 64 bit machines
//because long is 8 bytes at x64,we only can use int to define a 4 bytes variable
//and int is 2 bytes at 16 and 8 bit machines

typedef uint8_t				BYTE,U8;
typedef uint16_t				WORD,U16;
typedef uint32_t				DWORD,U32;
typedef int					FD_t;

typedef int					BOOL;

#ifndef	TRUE
	//#define TRUE		(1)
	const int TRUE					= 1;
#endif//TRUE

#ifndef FALSE
	//#define FALSE		(0)
	const int FALSE					= 0;
#endif//FALSE


const int RETURN_ERROR_F				= 0;
const int RETURN_SUCCESS_F			= 1;


#define DBG_PRINT_ENABLE

#ifdef DBG_PRINT_ENABLE
	#define DBG_PRINT printf
#else
	#define DBG_PRINT
#endif

#define _STR(s) #s
#define STR(s) _STR(s)
#define DBG_COME_HERE(str) DBG_PRINT(#str)


#endif /* __COMM_LIB_INC_F_H__ */