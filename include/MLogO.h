/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Include File									*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the 'MLogO' class.

	Revision History	:	2001-10-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__MLogO_H__h

#define h__MLogO_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#ifdef _Windows
# pragma warning(disable:4710 4786)
# if _MSC_VER >= 1300
#  pragma warning(disable:4217 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(disable:4018 4100 4146 4244 4245 4511 4512 4663)
# include <sstream>
# include <string>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <sstream>
# include <string>
#endif /* #ifdef _Windows */

#include <mlog.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
class MLogO {

	public:

		/*	***********************************************************
			***********************************************************
			Constructor and destructor methods . . .
			***********************************************************	*/
		MLogO(MLOG *in_mlog_ptr = NULL);
		MLogO(const std::string &file_name, bool append_flag = false,
			bool tid_flag = false);
		MLogO(const char *file_name, bool append_flag = false,
			bool tid_flag = false);
		MLogO(const char *file_name, const char *log_format,
			const char *user_string = NULL, MLOG_FLAG flags = MLOG_FLAG_DEFAULT);
		MLogO(const char *file_name, FILE *file_ptr = stderr,
			const char *log_format = NULL, const char *user_string = NULL,
			MLOG_FLAG flags = MLOG_FLAG_DEFAULT,
			MLOG_PRIORITY mfile_mask = MLOG_PRIORITY_DEFAULT_MFILE,
			MLOG_PRIORITY file_mask = MLOG_PRIORITY_DEFAULT_FILE,
			MLOG_PRIORITY syslog_mask = MLOG_PRIORITY_DEFAULT_SYSLOG,
			unsigned int initial_alloc = 0, unsigned int added_alloc = 0);
		virtual ~MLogO();
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Copy and assignment constructors . . .
			***********************************************************	*/
		MLogO(const MLogO &source) {
			if (source.can_log_flag) {
				my_mlog_ptr  = NULL;
				mlog_ptr     = source.mlog_ptr;
				can_log_flag = source.can_log_flag;
			}
		}
		MLogO& operator=(const MLogO &source) {
			if (this != &source) {
				Close();
				if (source.can_log_flag) {
					my_mlog_ptr  = NULL;
					mlog_ptr     = source.mlog_ptr;
					can_log_flag = source.can_log_flag;
				}
			}
			return(*this);
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Accessors for the logging object state.

			Use 'GetCanLog()' to determine whether the object is valid
			for logging. This will return false only if the object
			constructor failed or if 'Close()' has been invoked.

			Use 'GetMayLog()' to determine whether logging has been
			temporarily disabled by invocation of 'SetMayLog(false)'.

			Use 'GetCanAndMayLog()' to determine log messages CAN be
			written (as in 'GetCanLog()') and MAY be logged (as in
			'GetMayLog()').
			***********************************************************	*/
		bool GetCanLog() const       { return(can_log_flag); }
		bool GetCanAndMayLog() const { return(GetCanLog() && GetMayLog()); }
		bool GetMayLog() const       {
			return((GetCanLog() && MLOG_GetMayLog(mlog_ptr)) ? true : false);
		}
		bool SetMayLog(bool may_log_flag) {
			return((GetCanLog()) ?
				(MLOG_SetMayLog(mlog_ptr, may_log_flag) != 0) : false);
		}
		bool GetPDebug() const {
			return((GetCanLog() && MLOG_GetPDebug(mlog_ptr)) ? true : false);
		}
		bool SetPDebug(bool pdebug_flag) const {
			return((GetCanLog()) ?
				(MLOG_SetPDebug(mlog_ptr, pdebug_flag) != 0) : false);
		}
		bool SetPDebug(int pdebug_flag) const {
			return((GetCanLog()) ?
				(MLOG_SetPDebug(mlog_ptr, pdebug_flag) != 0) : false);
		}
		/*	***********************************************************	*/

		//	///////////////////////////////////////////////////////////
		//	///////////////////////////////////////////////////////////
		//	///////////////////////////////////////////////////////////
		MLOG_FLAG GetFlags() const {
			return((GetCanLog()) ? MLOG_GetFlags(mlog_ptr) : MLOG_FLAG_NONE);
		}
		bool      SetFlags(MLOG_FLAG flags) const {
			return((GetCanLog()) ?
				(MLOG_SetFlags(mlog_ptr, flags, NULL) == MLOG_SUCCESS) : false);
		}
		//	///////////////////////////////////////////////////////////

		/*	***********************************************************
			***********************************************************
			Do logging with a variable argument list . . .
			***********************************************************	*/
#ifdef __GNUC__
		int LogDebug(const char *in_format, ...);
			__attribute__ ((format (printf, 1, 2))) const;
		int LogErr(const char *in_format, ...);
			__attribute__ ((format (printf, 1, 2))) const;
		int LogInfo(const char *in_format, ...)
			__attribute__ ((format (printf, 1, 2))) const;
		int LogWarn(const char *in_format, ...)
			__attribute__ ((format (printf, 1, 2))) const;
		int LogPDebug(const char *in_format, ...)
			__attribute__ ((format (printf, 1, 2))) const;
		int LogIf(int if_value, const char *in_format, ...)
			__attribute__ ((format (printf, 2, 3))) const;
		int LogBasic(const struct timeval *in_time, MLOG_PRIORITY log_priority,
			const char *user_string, MLOG_FLAG flags, MLOG_PRIORITY mfile_mask,
			MLOG_PRIORITY file_mask, MLOG_PRIORITY syslog_mask,
			const char *in_format, ...)
			__attribute__ ((format (printf, 8, 9))) const;
#else
		int LogDebug(const char *in_format, ...) const;
		int LogErr(const char *in_format, ...) const;
		int LogInfo(const char *in_format, ...) const;
		int LogWarn(const char *in_format, ...) const;
		int LogPDebug(const char *in_format, ...) const;
		int LogIf(int if_value, const char *in_format, ...) const;
		int LogBasic(const struct timeval *in_time,
			MLOG_PRIORITY log_priority, const char *user_string, MLOG_FLAG flags,
			MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
			MLOG_PRIORITY syslog_mask, const char *in_format, ...) const;
#endif /* #ifdef __GNUC__ */
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Do logging with a 'va_list' . . .
			***********************************************************	*/
		int LogDebugVA(const char *in_format, va_list arg_list) const;
		int LogErrVA(const char *in_format, va_list arg_list) const;
		int LogInfoVA(const char *in_format, va_list arg_list) const;
		int LogWarnVA(const char *in_format, va_list arg_list) const;
		int LogPDebugVA(const char *in_format, va_list arg_list) const;
		int LogIfVA(int if_value, const char *in_format, va_list arg_list) const;
		int LogBasicVA(const struct timeval *in_time, MLOG_PRIORITY log_priority,
			const char *user_string, MLOG_FLAG flags, MLOG_PRIORITY mfile_mask,
			MLOG_PRIORITY file_mask, MLOG_PRIORITY syslog_mask,
			const char *in_format, va_list arg_list) const;
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Do logging with specified time and a variable argument list . . .
			***********************************************************	*/
#ifdef __GNUC__
		int LogDebugTime(const struct timeval *in_time,
			const char *in_format, ...)
			__attribute__ ((format (printf, 2, 3))) const;
		int LogErrTime(const struct timeval *in_time,
			const char *in_format, ...)
			__attribute__ ((format (printf, 2, 3))) const;
		int LogInfoTime(const struct timeval *in_time,
			const char *in_format, ...)
			__attribute__ ((format (printf, 2, 3))) const;
		int LogWarnTime(const struct timeval *in_time,
			const char *in_format, ...)
			__attribute__ ((format (printf, 2, 3))) const;
		int LogPDebugTime(const struct timeval *in_time,
			const char *in_format, ...)
			__attribute__ ((format (printf, 2, 3))) const;
		int LogIfTime(int if_value, const struct timeval *in_time,
			const char *in_format, ...)
			__attribute__ ((format (printf, 3, 4))) const;
#else
		int LogDebugTime(const struct timeval *in_time,
			const char *in_format, ...) const;
		int LogErrTime(const struct timeval *in_time,
			const char *in_format, ...) const;
		int LogInfoTime(const struct timeval *in_time,
			const char *in_format, ...) const;
		int LogWarnTime(const struct timeval *in_time,
			const char *in_format, ...) const;
		int LogPDebugTime(const struct timeval *in_time,
			const char *in_format, ...) const;
		int LogIfTime(int if_value, const struct timeval *in_time,
			const char *in_format, ...) const;
#endif /* #ifdef __GNUC__ */
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Do logging with specified time and a 'va_list' . . .
			***********************************************************	*/
		int LogDebugTimeVA(const struct timeval *in_time, const char *in_format,
			va_list arg_list) const;
		int LogErrTimeVA(const struct timeval *in_time, const char *in_format,
			va_list arg_list) const;
		int LogInfoTimeVA(const struct timeval *in_time, const char *in_format,
			va_list arg_list) const;
		int LogWarnTimeVA(const struct timeval *in_time, const char *in_format,
			va_list arg_list) const;
		int LogPDebugTimeVA(const struct timeval *in_time, const char *in_format,
			va_list arg_list) const;
		int LogIfTimeVA(int if_value, const struct timeval *in_time,
			const char *in_format, va_list arg_list) const;
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Do logging with a 'std::string' . . .
			***********************************************************	*/
		int LogDebug(const std::string &in_string) const {
			return(LogDebug("%s\n", in_string.c_str()));
		}
		int LogErr(const std::string &in_string) const {
			return(LogErr("%s\n", in_string.c_str()));
		}
		int LogInfo(const std::string &in_string) const {
			return(LogInfo("%s\n", in_string.c_str()));
		}
		int LogWarn(const std::string &in_string) const {
			return(LogWarn("%s\n", in_string.c_str()));
		}
		int LogPDebug(const std::string &in_string) const {
			return(LogPDebug("%s\n", in_string.c_str()));
		}
		int LogIf(int if_value, const std::string &in_string) const {
			return(LogIf(if_value, "%s\n", in_string.c_str()));
		}
		int LogBasic(const struct timeval *in_time,
			MLOG_PRIORITY log_priority, const char *user_in_string,
			MLOG_FLAG flags, MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
			MLOG_PRIORITY syslog_mask, const std::string &in_string) const {
			return(LogBasic(in_time, log_priority, user_in_string, flags,
				mfile_mask, file_mask, syslog_mask, "%s\n", in_string.c_str()));
		}
			// And with a specified time . . .
		int LogDebugTime(const struct timeval *in_time,
			const std::string &in_string) const {
			return(LogDebugTime(in_time, "%s\n", in_string.c_str()));
		}
		int LogErrTime(const struct timeval *in_time,
			const std::string &in_string) const {
			return(LogErrTime(in_time, "%s\n", in_string.c_str()));
		}
		int LogInfoTime(const struct timeval *in_time,
			const std::string &in_string) const {
			return(LogInfoTime(in_time, "%s\n", in_string.c_str()));
		}
		int LogWarnTime(const struct timeval *in_time,
			const std::string &in_string) const {
			return(LogWarnTime(in_time, "%s\n", in_string.c_str()));
		}
		int LogPDebugTime(const struct timeval *in_time,
			const std::string &in_string) const {
			return(LogPDebugTime(in_time, "%s\n", in_string.c_str()));
		}
		int LogIfTime(int if_value, const struct timeval *in_time,
			const std::string &in_string) const {
			return(LogIfTime(if_value, in_time, "%s\n", in_string.c_str()));
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Do logging with an 'std::ostringstream' . . .
			***********************************************************	*/
		int LogDebug(const std::ostringstream &in_stream) const {
			return(LogDebug(in_stream.str()));
		}
		int LogErr(const std::ostringstream &in_stream) const {
			return(LogErr(in_stream.str()));
		}
		int LogInfo(const std::ostringstream &in_stream) const {
			return(LogInfo(in_stream.str()));
		}
		int LogWarn(const std::ostringstream &in_stream) const {
			return(LogWarn(in_stream.str()));
		}
		int LogPDebug(const std::ostringstream &in_stream) const {
			return(LogPDebug(in_stream.str()));
		}
		int LogIf(int if_value, const std::ostringstream &in_stream) const {
			return(LogIf(if_value, in_stream.str()));
		}
		int LogBasic(const struct timeval *in_time,
			MLOG_PRIORITY log_priority, const char *user_in_stream,
			MLOG_FLAG flags, MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
			MLOG_PRIORITY syslog_mask, const std::ostringstream &in_stream) const {
			return(LogBasic(in_time, log_priority, user_in_stream, flags,
				mfile_mask, file_mask, syslog_mask, in_stream.str()));
		}
			// And with a specified time . . .
		int LogDebugTime(const struct timeval *in_time,
			const std::ostringstream &in_stream) const {
			return(LogDebugTime(in_time, in_stream.str()));
		}
		int LogErrTime(const struct timeval *in_time,
			const std::ostringstream &in_stream) const {
			return(LogErrTime(in_time, in_stream.str()));
		}
		int LogInfoTime(const struct timeval *in_time,
			const std::ostringstream &in_stream) const {
			return(LogInfoTime(in_time, in_stream.str()));
		}
		int LogWarnTime(const struct timeval *in_time,
			const std::ostringstream &in_stream) const {
			return(LogWarnTime(in_time, in_stream.str()));
		}
		int LogPDebugTime(const struct timeval *in_time,
			const std::ostringstream &in_stream) const {
			return(LogPDebugTime(in_time, in_stream.str()));
		}
		int LogIfTime(int if_value, const struct timeval *in_time,
			const std::ostringstream &in_stream) const {
			return(LogIfTime(if_value, in_time, in_stream.str()));
		}
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Miscellaneous log formatting and info methods . . .
			***********************************************************	*/
		void DoSepStart() const;
		void DoSepEnd() const;
		void DoSepHyphen() const;
		void DoSepEqual() const;
		void DoSepStar() const;
		void DoSepChar(int log_char) const;
		void DoSepCharBasic(unsigned int sep_length, int log_char) const;
		void DoSepString(const char *log_string) const;
		void DoExecTime(const struct timeval *start_time,
			const struct timeval *end_time = NULL,
			const struct timeval *overhead_end_time = NULL) const;
		void DoRUsage() const;
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Locking logic . . .
			***********************************************************	*/
		int Lock(char *error_text = NULL) const;
		int TryLock(char *error_text = NULL) const;
		int Unlock(char *error_text = NULL) const;
		/*	***********************************************************	*/

		/*	***********************************************************
			***********************************************************
			Other useful methods . . .
			***********************************************************	*/
		int  Sync(int async_flag = false, char *error_text = NULL) const;
		void CompleteOutput() const;
		int  Close(char *error_text = NULL);
		/*	***********************************************************	*/

	private:

		/*	***********************************************************
			***********************************************************
			Data members . . .
			***********************************************************	*/
		MLOG         *my_mlog_ptr;
		mutable MLOG *mlog_ptr;
		bool          can_log_flag;
		/*	***********************************************************	*/
};
/*	***********************************************************************	*/

#endif /* #ifndef h__MLogO_H__h */

