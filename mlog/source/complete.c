/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Completes a log entry output line by synchronizing
								file output to the underlying (if requested by flags).

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
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
void MLOG_CompleteOutput(MLOG *mlog_ptr)
#else
void MLOG_CompleteOutput(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	if (MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS) {
		if (MLOG_DO_LOG_EITHER_FILE(mlog_ptr)) {
			if (MLOG_DO_LOG_MFILE(mlog_ptr) && (mlog_ptr->flags & MLOG_FLAG_SYNC))
				MLOG_SyncMFILE(mlog_ptr, NULL);
			if (MLOG_DO_LOG_FILE(mlog_ptr) &&
				(mlog_ptr->flags & MLOG_FLAG_FILE_FLUSH))
				MLOG_SyncFILE(mlog_ptr, NULL);
		}
		MLOG_Unlock(mlog_ptr, NULL);
	}
}
/*	***********************************************************************	*/

