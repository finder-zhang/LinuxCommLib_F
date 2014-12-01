/*
 * commlib_impl.h
 *
 *  Created on: May 21, 2012
 *      Author: lucid
 */

#ifndef __COMM_LIB_IMPL_F_H__
#define __COMM_LIB_IMPL_F_H__


template<class T>
T clib_min(T t1,T t2)
{
	return t1<t2 ? t1 : t2;
}

template<class T>
T clib_max(T t1,T t2)
{
	return t1<t2 ? t2 : t1;
}


#endif /* __COMM_LIB_IMPL_F_H__ */
