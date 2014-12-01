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

int clib_init(int argc,char** argv);

string& clib_get_proc_path();

template<class T>
T clib_min(T t1,T t2);

template<class T>
T clib_max(T t1,T t2);


#endif /* __COMM_LIB_BASE_F_H__ */
