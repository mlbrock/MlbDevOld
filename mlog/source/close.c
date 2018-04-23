/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes a logging file.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
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

#include <genfuncs.h>

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_Close(MLOG *mlog_ptr, char *error_text)
#else
int MLOG_Close(mlog_ptr, error_text)
MLOG *mlog_ptr;
char *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MLOG_Check(mlog_ptr, error_text)) == MLOG_SUCCESS) {
		if ((mlog_ptr->mtr_data_init_flag == MLOG_TRUE) &&
			((return_code = MLOG_Lock(mlog_ptr, error_text)) == MLOG_SUCCESS)) {
			if ((MLOG_GET_MFILE_PTR(mlog_ptr) != NULL) &&
				mclose_to_offset(MLOG_GET_MFILE_PTR(mlog_ptr))) {
				if (error_text != NULL) {
					strcpy(error_text, "Error on logging file close attempt: ");
					GEN_AppendLastErrorString(0, MLOG_MAX_ERROR_TEXT - 100,
						error_text);
				}
				return_code = MLOG_FAILURE;
			}
			if ((mlog_ptr->flags & MLOG_FLAG_FILE_CLOSE) &&
				(mlog_ptr->file_ptr != NULL))
				fclose(mlog_ptr->file_ptr);
			MLOG_Unlock(mlog_ptr, NULL);
			MTIF_MTR_Destroy(&mlog_ptr->mtr_data, NULL);
		}
		MLOG_Free(mlog_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

