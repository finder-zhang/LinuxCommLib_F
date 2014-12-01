/*
 * Process_F.h
 *
 *  Created on: 2014年9月16日
 *      Author: root
 */

#ifndef PROCESS_F_H_
#define PROCESS_F_H_

#include <comm_lib_f.h>
#include <sys/types.h>

pid_t CreateProcess(const char* chProcPathName,const char* chArg,FD_t& fdStdin,FD_t& fdStdout);

#endif /* PROCESS_F_H_ */
