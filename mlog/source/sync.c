/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Controls synchronizes file output.

	Revision History	:	2001-07-17 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2018.
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
int MLOG_Sync(MLOG *mlog_ptr, char *error_text)
#else
int MLOG_Sync(mlog_ptr, error_text)
MLOG *mlog_ptr;
char *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MLOG_Lock(mlog_ptr, error_text)) == MLOG_SUCCESS) {
		if (MLOG_DO_LOG_EITHER_FILE(mlog_ptr)) {
			if (MLOG_DO_LOG_MFILE(mlog_ptr))
				return_code = MLOG_SyncMFILE(mlog_ptr, error_text);
			if (MLOG_DO_LOG_FILE(mlog_ptr)) {
				if (return_code == MLOG_SUCCESS)
					return_code = MLOG_SyncFILE(mlog_ptr, error_text);
				else
					MLOG_SyncFILE(mlog_ptr, NULL);
			}
		}
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SyncMFILE(MLOG *mlog_ptr, char *error_text)
#else
int MLOG_SyncMFILE(mlog_ptr, error_text)
MLOG *mlog_ptr;
char *error_text;
#endif /* #ifndef NARGS */
{
	return(MLOG_SyncMFILEBasic(mlog_ptr,
		(mlog_ptr->flags & MLOG_FLAG_SYNC_ASYNC) ? MLOG_TRUE : MLOG_FALSE,
		error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SyncMFILEBasic(MLOG *mlog_ptr, int async_flag, char *error_text)
#else
int MLOG_SyncMFILEBasic(mlog_ptr, int async_flag, error_text)
MLOG *mlog_ptr;
int   async_flag;
char *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char tmp_error_text[MLOG_MAX_ERROR_TEXT];

	if ((return_code = MLOG_Lock(mlog_ptr, tmp_error_text)) == MLOG_SUCCESS) {
	  if (MLOG_DO_LOG_MFILE(mlog_ptr))
			mflush_async(MLOG_GET_MFILE_PTR(mlog_ptr),
				(async_flag) ? MFILE_TRUE : MFILE_FALSE);
		MLOG_Unlock(mlog_ptr, NULL);
	}
	else if (error_text != NULL)
		strncat(strcpy(error_text, "Unable to synchronize the MILE data: "),
			tmp_error_text, MLOG_MAX_ERROR_TEXT - 100);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SyncFILE(MLOG *mlog_ptr, char *error_text)
#else
int MLOG_SyncFILE(mlog_ptr, error_text)
MLOG *mlog_ptr;
char *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char tmp_error_text[MLOG_MAX_ERROR_TEXT];

	if ((return_code = MLOG_Lock(mlog_ptr, tmp_error_text)) == MLOG_SUCCESS) {
		if (MLOG_DO_LOG_FILE(mlog_ptr))
			fflush(MLOG_GET_FILE_PTR(mlog_ptr));
		MLOG_Unlock(mlog_ptr, NULL);
	}
	else if (error_text != NULL)
		strncat(strcpy(error_text, "Unable to synchronize the FILE data: "),
			tmp_error_text, MLOG_MAX_ERROR_TEXT - 100);

	return(return_code);
}
/*	***********************************************************************	*/


