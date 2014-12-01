/*
 * file_record_ex_f.h
 *
 *  Created on: Aug 28, 2012
 *      Author: lucid
 */

#ifndef __FILE_RECORD_F_H__
#define __FILE_RECORD_F_H__

#include "file_f.h"

class CFileRecord_F : public file_f
{
public:
	int Printf(const char* ch,...);
	int AppendRecord(const char* chFileName);
	int NewRecord(const char* chFileName);
};

#endif /* __FILE_RECORD_F_H__ */
