/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation file for the 'MLogO' class.

	Revision History	:	2001-10-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "MLogO.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
MLogO::MLogO(MLOG *in_mlog_ptr) :
		my_mlog_ptr(NULL), mlog_ptr(NULL), can_log_flag(false)
{
	if ((in_mlog_ptr != NULL) &&
		(MLOG_Check(in_mlog_ptr, NULL) == MLOG_SUCCESS)) {
		mlog_ptr     = in_mlog_ptr;
		can_log_flag = true;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
MLogO::MLogO(const std::string &file_name, bool append_flag, bool tid_flag) :
		my_mlog_ptr(NULL), mlog_ptr(NULL), can_log_flag(false)
{
	if ((append_flag != true) && (tid_flag != true))
		my_mlog_ptr = MLOG_FOpenDefault(file_name.c_str());
	else if ((append_flag == true) && (tid_flag != true))
		my_mlog_ptr = MLOG_FOpenDefaultAppend(file_name.c_str());
	else if ((append_flag != true) && (tid_flag == true))
		my_mlog_ptr = MLOG_FOpenDefaultTid(file_name.c_str());
	else
		my_mlog_ptr = MLOG_FOpenDefaultTidAppend(file_name.c_str());

	if (my_mlog_ptr != NULL) {
		mlog_ptr     = my_mlog_ptr;
		can_log_flag = true;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
MLogO::MLogO(const char *file_name, bool append_flag, bool tid_flag) :
		my_mlog_ptr(NULL), mlog_ptr(NULL), can_log_flag(false)
{
	if ((append_flag != true) && (tid_flag != true))
		my_mlog_ptr = MLOG_FOpenDefault(file_name);
	else if ((append_flag == true) && (tid_flag != true))
		my_mlog_ptr = MLOG_FOpenDefaultAppend(file_name);
	else if ((append_flag != true) && (tid_flag == true))
		my_mlog_ptr = MLOG_FOpenDefaultTid(file_name);
	else
		my_mlog_ptr = MLOG_FOpenDefaultTidAppend(file_name);

	if (my_mlog_ptr != NULL) {
		mlog_ptr     = my_mlog_ptr;
		can_log_flag = true;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
MLogO::MLogO(const char *file_name, const char *log_format,
	const char *user_string, MLOG_FLAG flags) :
		my_mlog_ptr(NULL), mlog_ptr(NULL), can_log_flag(false)
{
	if (MLOG_OpenLog(file_name, log_format, user_string, flags, &my_mlog_ptr,
		NULL) == MLOG_SUCCESS) {
		mlog_ptr     = my_mlog_ptr;
		can_log_flag = true;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
MLogO::MLogO(const char *file_name, FILE *file_ptr, const char *log_format,
	const char *user_string, MLOG_FLAG flags, MLOG_PRIORITY mfile_mask,
	MLOG_PRIORITY file_mask, MLOG_PRIORITY syslog_mask,
	unsigned int initial_alloc, unsigned int added_alloc) :
		my_mlog_ptr(NULL), mlog_ptr(NULL), can_log_flag(false)
{
	if (MLOG_OpenBasic(file_name, file_ptr, log_format, user_string, flags,
		mfile_mask, file_mask, syslog_mask, initial_alloc, added_alloc,
		&my_mlog_ptr, NULL) == MLOG_SUCCESS) {
		mlog_ptr     = my_mlog_ptr;
		can_log_flag = true;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
MLogO::~MLogO()
{
	Close();
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogDebug(const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogDebugVA(in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogErr(const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogErrVA(in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogInfo(const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogInfoVA(in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogWarn(const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogWarnVA(in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogPDebug(const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogPDebugVA(in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogIf(int if_value, const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogIfVA(if_value, in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogBasic(const struct timeval *in_time,
	MLOG_PRIORITY log_priority, const char *user_string, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogBasicVA(in_time, log_priority, user_string, flags,
			mfile_mask, file_mask, syslog_mask, in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogDebugVA(const char *in_format, va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogDebugVA(mlog_ptr, in_format,
		arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogErrVA(const char *in_format, va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogErrVA(mlog_ptr, in_format,
		arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogInfoVA(const char *in_format, va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogInfoVA(mlog_ptr, in_format,
		arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogWarnVA(const char *in_format, va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogWarnVA(mlog_ptr, in_format,
		arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogPDebugVA(const char *in_format, va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogPDebugVA(mlog_ptr, in_format,
		arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogIfVA(int if_value, const char *in_format, va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogIfVA(mlog_ptr, if_value,
		in_format, arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogBasicVA(const struct timeval *in_time, MLOG_PRIORITY log_priority,
	const char *user_string, MLOG_FLAG flags, MLOG_PRIORITY mfile_mask,
	MLOG_PRIORITY file_mask, MLOG_PRIORITY syslog_mask, const char *in_format,
	va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogBasicVA(mlog_ptr, in_time,
		log_priority, user_string, flags, mfile_mask, file_mask, syslog_mask,
		in_format, arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogDebugTime(const struct timeval *in_time,
	const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogDebugTimeVA(in_time, in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogErrTime(const struct timeval *in_time,
	const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogErrTimeVA(in_time, in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogInfoTime(const struct timeval *in_time,
	const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogInfoTimeVA(in_time, in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogWarnTime(const struct timeval *in_time,
	const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogWarnTimeVA(in_time, in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogPDebugTime(const struct timeval *in_time,
	const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogPDebugTimeVA(in_time, in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogIfTime(int if_value, const struct timeval *in_time,
	const char *in_format, ...) const
{
	int     return_code;
	va_list arg_list;

	if (GetCanAndMayLog() == true) {
		va_start(arg_list, in_format);
		return_code = LogIfTimeVA(if_value, in_time, in_format, arg_list);
		va_end(arg_list);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogDebugTimeVA(const struct timeval *in_time, const char *in_format,
	va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogDebugTimeVA(mlog_ptr, in_time,
		in_format, arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogErrTimeVA(const struct timeval *in_time, const char *in_format,
	va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogErrTimeVA(mlog_ptr, in_time,
		in_format, arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogInfoTimeVA(const struct timeval *in_time, const char *in_format,
	va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogInfoTimeVA(mlog_ptr, in_time,
		in_format, arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogWarnTimeVA(const struct timeval *in_time, const char *in_format,
	va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogWarnTimeVA(mlog_ptr, in_time,
		in_format, arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogPDebugTimeVA(const struct timeval *in_time, const char *in_format,
	va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogPDebugTimeVA(mlog_ptr, in_time,
		in_format, arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::LogIfTimeVA(int if_value, const struct timeval *in_time,
	const char *in_format, va_list arg_list) const
{
	return((GetCanAndMayLog() == true) ? MLOG_LogIfTimeVA(mlog_ptr, if_value,
		in_time, in_format, arg_list) : MLOG_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void MLogO::DoSepStart() const
{
	if (GetCanAndMayLog())
		MLOG_DoSepStart(mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void MLogO::DoSepEnd() const
{
	if (GetCanAndMayLog())
		MLOG_DoSepEnd(mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void MLogO::DoSepHyphen() const
{
	if (GetCanAndMayLog())
		MLOG_DoSepHyphen(mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void MLogO::DoSepEqual() const
{
	if (GetCanAndMayLog())
		MLOG_DoSepEqual(mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void MLogO::DoSepStar() const
{
	if (GetCanAndMayLog())
		MLOG_DoSepStar(mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void MLogO::DoSepChar(int log_char) const
{
	if (GetCanAndMayLog())
		MLOG_DoSepChar(mlog_ptr, log_char);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void MLogO::DoSepCharBasic(unsigned int sep_length, int log_char) const
{
	if (GetCanAndMayLog())
		MLOG_DoSepCharBasic(mlog_ptr, sep_length, log_char);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void MLogO::DoSepString(const char *log_string) const
{
	if (GetCanAndMayLog())
		MLOG_DoSepString(mlog_ptr, log_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void MLogO::DoExecTime(const struct timeval *start_time,
	const struct timeval *end_time, const struct timeval *overhead_end_time)const
{
	if (GetCanAndMayLog())
		MLOG_DoExecTime(mlog_ptr, start_time, end_time, overhead_end_time);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void MLogO::DoRUsage() const
{
	if (GetCanAndMayLog())
		MLOG_DoRUsage(mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::Lock(char *error_text) const
{
	return(MLOG_Lock(mlog_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::TryLock(char *error_text) const
{
	return(MLOG_TryLock(mlog_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::Unlock(char *error_text) const
{
	return(MLOG_Unlock(mlog_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::Sync(int async_flag, char *error_text) const
{
	int return_code;

	if (GetCanLog() == true) {
		if ((return_code = MLOG_SyncMFILEBasic(mlog_ptr, async_flag,
			error_text)) == MLOG_SUCCESS)
			return_code = MLOG_SyncFILE(mlog_ptr, error_text);
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void MLogO::CompleteOutput() const
{
	if (GetCanAndMayLog())
		MLOG_CompleteOutput(mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int MLogO::Close(char *error_text)
{
	int return_code;

	if (GetCanLog()) {
		if (my_mlog_ptr != NULL)
			return_code = MLOG_Close(my_mlog_ptr, error_text);
		else
			return_code = MLOG_SUCCESS;
		my_mlog_ptr  = NULL;
		mlog_ptr     = NULL;
		can_log_flag = false;
	}
	else {
		if (error_text != NULL)
			strcpy(error_text, "The 'MLogO' object is not open for logging.");
		return_code = MLOG_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/


