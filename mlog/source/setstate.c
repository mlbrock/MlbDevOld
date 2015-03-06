/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sets a variety of MLOG structure data.

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

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SetMayLog(MLOG *mlog_ptr, int may_log_flag)
#else
int MLOG_SetMayLog(mlog_ptr, may_log_flag)
MLOG *mlog_ptr;
int   may_log_flag;
#endif /* #ifndef NARGS */
{
	int return_code = MLOG_FALSE;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_code            = mlog_ptr->may_log_flag;
		mlog_ptr->may_log_flag = (may_log_flag) ? MLOG_TRUE : MLOG_FALSE;
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SetPDebug(MLOG *mlog_ptr, int pdebug_flag)
#else
int MLOG_SetPDebug(mlog_ptr, pdebug_flag)
MLOG *mlog_ptr;
int   pdebug_flag;
#endif /* #ifndef NARGS */
{
	int return_code = MLOG_FALSE;

	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		return_code           = mlog_ptr->pdebug_flag;
		mlog_ptr->pdebug_flag = (pdebug_flag) ? MLOG_TRUE : MLOG_FALSE;
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SetFlags(MLOG *mlog_ptr, MLOG_FLAG flags, char *error_text)
#else
int MLOG_SetFlags(mlog_ptr, flags, error_text)
MLOG      *mlog_ptr;
MLOG_FLAG  flags;
char      *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MLOG_CheckFlags(flags, error_text)) == MLOG_SUCCESS) {
		if ((return_code = MLOG_Lock(mlog_ptr, error_text)) == MLOG_SUCCESS) {
			mlog_ptr->flags = flags;
			MLOG_Unlock(mlog_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SetFlagMFile(MLOG *mlog_ptr, int flag, char *error_text)
#else
int MLOG_SetFlagMFile(mlog_ptr, flag, error_text)
MLOG *mlog_ptr;
int   flag;
char *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MLOG_Lock(mlog_ptr, error_text)) == MLOG_SUCCESS) {
		if ((!flag) && (mlog_ptr->flags & MLOG_FLAG_MFILE))
			mlog_ptr->flags -= MLOG_FLAG_MFILE;
		else if (flag)
			mlog_ptr->flags |= MLOG_FLAG_MFILE;
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SetFlagFile(MLOG *mlog_ptr, int flag, char *error_text)
#else
int MLOG_SetFlagFile(mlog_ptr, flag, error_text)
MLOG *mlog_ptr;
int   flag;
char *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MLOG_Lock(mlog_ptr, error_text)) == MLOG_SUCCESS) {
		if ((!flag) && (mlog_ptr->flags & MLOG_FLAG_FILE))
			mlog_ptr->flags -= MLOG_FLAG_FILE;
		else if (flag)
			mlog_ptr->flags |= MLOG_FLAG_FILE;
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SetFlagSyslog(MLOG *mlog_ptr, int flag, char *error_text)
#else
int MLOG_SetFlagSyslog(mlog_ptr, flag, error_text)
MLOG *mlog_ptr;
int   flag;
char *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MLOG_Lock(mlog_ptr, error_text)) == MLOG_SUCCESS) {
		if ((!flag) && (mlog_ptr->flags & MLOG_FLAG_SYSLOG))
			mlog_ptr->flags -= MLOG_FLAG_SYSLOG;
		else if (flag)
			mlog_ptr->flags |= MLOG_FLAG_SYSLOG;
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SetPriorityMFile(MLOG *mlog_ptr, MLOG_PRIORITY mfile_mask,
	char *error_text)
#else
int MLOG_SetPriorityMFile(mlog_ptr, mfile_mask, error_text)
MLOG          *mlog_ptr;
MLOG_PRIORITY  mfile_mask;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MLOG_CheckPriorityMFile(mfile_mask, error_text)) ==
		MLOG_SUCCESS) {
		if ((return_code = MLOG_Lock(mlog_ptr, error_text)) == MLOG_SUCCESS) {
			mlog_ptr->mfile_mask = mfile_mask;
			MLOG_Unlock(mlog_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SetPriorityFile(MLOG *mlog_ptr, MLOG_PRIORITY file_mask,
	char *error_text)
#else
int MLOG_SetPriorityFile(mlog_ptr, file_mask, error_text)
MLOG          *mlog_ptr;
MLOG_PRIORITY  file_mask;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MLOG_CheckPriorityFile(file_mask, error_text)) ==
		MLOG_SUCCESS) {
		if ((return_code = MLOG_Lock(mlog_ptr, error_text)) == MLOG_SUCCESS) {
			mlog_ptr->file_mask = file_mask;
			MLOG_Unlock(mlog_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SetPrioritySyslog(MLOG *mlog_ptr, MLOG_PRIORITY syslog_mask,
	char *error_text)
#else
int MLOG_SetPrioritySyslog(mlog_ptr, syslog_mask, error_text)
MLOG          *mlog_ptr;
MLOG_PRIORITY  syslog_mask;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MLOG_CheckPrioritySyslog(syslog_mask, error_text)) ==
		MLOG_SUCCESS) {
		if ((return_code = MLOG_Lock(mlog_ptr, error_text)) == MLOG_SUCCESS) {
			mlog_ptr->syslog_mask = syslog_mask;
			MLOG_Unlock(mlog_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

