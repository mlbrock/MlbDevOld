/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets a variety of MLOG structure data.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <string.h>

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_GetMayLog(MLOG *mlog_ptr)
#else
int MLOG_GetMayLog(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = MLOG_FALSE;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_code = mlog_ptr->may_log_flag;
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_GetPDebug(MLOG *mlog_ptr)
#else
int MLOG_GetPDebug(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = MLOG_FALSE;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_code = mlog_ptr->pdebug_flag;
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
MLOG_FLAG MLOG_GetFlags(MLOG *mlog_ptr)
#else
MLOG_FLAG MLOG_GetFlags(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	MLOG_FLAG return_code = MLOG_FLAG_NONE;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_code = MLOG_GET_FLAGS_I(mlog_ptr);
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_GetFlagMFile(MLOG *mlog_ptr)
#else
int MLOG_GetFlagMFile(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = MLOG_FALSE;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_code = MLOG_DO_LOG_MFILE(mlog_ptr);
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_GetFlagFile(MLOG *mlog_ptr)
#else
int MLOG_GetFlagFile(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = MLOG_FALSE;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_code = MLOG_DO_LOG_FILE(mlog_ptr);
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_GetFlagSyslog(MLOG *mlog_ptr)
#else
int MLOG_GetFlagSyslog(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = MLOG_FALSE;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_code = MLOG_DO_LOG_SYSLOG(mlog_ptr);
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
MLOG_PRIORITY MLOG_GetPriorityMFile(MLOG *mlog_ptr)
#else
MLOG_PRIORITY MLOG_GetPriorityMFile(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	MLOG_PRIORITY return_code = MLOG_PRIORITY_NONE;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_code = MLOG_GET_MASK_MFILE(mlog_ptr);
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
MLOG_PRIORITY MLOG_GetPriorityFile(MLOG *mlog_ptr)
#else
MLOG_PRIORITY MLOG_GetPriorityFile(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	MLOG_PRIORITY return_code = MLOG_PRIORITY_NONE;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_code = MLOG_GET_MASK_FILE(mlog_ptr);
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
MLOG_PRIORITY MLOG_GetPrioritySyslog(MLOG *mlog_ptr)
#else
MLOG_PRIORITY MLOG_GetPrioritySyslog(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	MLOG_PRIORITY return_code = MLOG_PRIORITY_NONE;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_code = MLOG_GET_MASK_SYSLOG(mlog_ptr);
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *MLOG_GetFileName(MLOG *mlog_ptr)
#else
char *MLOG_GetFileName(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	char *return_ptr = NULL;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_ptr = (MLOG_GET_FILE_NAME_I(mlog_ptr) != NULL) ?
			strdup(MLOG_GET_FILE_NAME_I(mlog_ptr)) : NULL;
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *MLOG_GetLogFormat(MLOG *mlog_ptr)
#else
char *MLOG_GetLogFormat(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	char *return_ptr = NULL;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_ptr = (mlog_ptr->log_format != NULL) ?
			strdup(mlog_ptr->log_format) : NULL;
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *MLOG_GetUserString(MLOG *mlog_ptr)
#else
char *MLOG_GetUserString(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	char *return_ptr = NULL;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_ptr = (mlog_ptr->user_string != NULL) ?
			strdup(mlog_ptr->user_string) : NULL;
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_ptr);
}
/*	***********************************************************************	*/


