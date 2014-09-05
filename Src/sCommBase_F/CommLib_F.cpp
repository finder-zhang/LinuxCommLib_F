/*
 * commlib.cpp
 *
 *  Created on: May 21, 2012
 *      Author: lucid
 */

#include <stdio.h>
#include <string>
using std::string;


#include "CommLib_F.h"

static string s_ProcPath;
string& GetProcPath()
{
	return s_ProcPath;
}

int InitCommLib(int argc,char** argv)
{
	setvbuf(stdout,0,_IONBF,0);

	s_ProcPath = argv[0];
	string::size_type si =  s_ProcPath.find_last_of('/');
	s_ProcPath.resize(si+1);

	return RETURN_SUCCESS_F;
}
