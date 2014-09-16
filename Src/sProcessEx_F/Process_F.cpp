/*
 * Process_F.cpp
 *
 *  Created on: 2014年9月16日
 *      Author: root
 */


#include "Process_F.h"
#include <unistd.h>

pid_t CreateProcess(const char* chProcPathName,const char* chArg,FD_t& fdStdin,FD_t& fdStdout)
{
	int fd_sub_in[2];		//use to cat the sub process's stdin
	int fd_sub_out[2];
	pipe(fd_sub_in);		//use to cat the sub process's stdout
	pipe(fd_sub_out);

	pid_t pid = fork();

	//here is sub branch
	if ( 0 == pid ) {
		dup2(fd_sub_in[0],STDIN_FILENO);			//cat the STDIN to fd_sub_in
		dup2(fd_sub_out[1],STDOUT_FILENO);			//cat the STDOUT to fd_sub_out
		execlp(chProcPathName,chArg,(char*)0);		//run sub process
	}

	//here is the trunk
	if ( pid < 0 ) {
		return 0;
	}

	fdStdin = fd_sub_in[1];
	fdStdout = fd_sub_out[0];

	return pid;
}





