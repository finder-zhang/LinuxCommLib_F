/*
 * CommLibBase.h
 *
 *  Created on: 2012-8-16
 *      Author: lucid
 */

#ifndef __COMM_LIB_BASE_F_H__
#define __COMM_LIB_BASE_F_H__

#include <string>
using std::string;

int InitCommLib(int argc,char** argv);

string& GetProcPath();

template<class T>
T GetMinVal(T t1,T t2);

template<class T>
T GetMaxVal(T t1,T t2);


#endif /* __COMM_LIB_BASE_F_H__ */
