/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:

	Revision History	:	1994-03-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_LockRecord(cache_ptr, record_offset, error_text)
DCR_CACHE     *cache_ptr;
unsigned long  record_offset;
char          *error_text;
{
	int return_code;

	if ((return_code = DCR_AssertAccessType(cache_ptr,
		DCR_I_AM_WRITER, error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_CheckRecordOffset(cache_ptr, record_offset,
			error_text)) == DCR_SUCCESS) {
			if (((DCR_LOCK *) (((char *) cache_ptr->mmap_ptr) +
				record_offset +
				((unsigned long) cache_ptr->header_ptr->data_record_size)))->
				lock_flag == DCR_LOCK_LOCKED_FLAG) {
				sprintf(error_text, "%s %lu %s 0X%08lX (%010lu) %s.",
					"Attempt to lock record index number",
					(record_offset - cache_ptr->data_area_offset) /
					((unsigned long) cache_ptr->total_record_size),
					"at cache offset", record_offset, record_offset,
					"failed becuase it is already locked");
				return_code = DCR_FAILURE;
			}
			else
				DCR_LOCK_Lock(((DCR_LOCK *) (((char *) cache_ptr->mmap_ptr) +
					record_offset +
					((unsigned long) cache_ptr->header_ptr->data_record_size))));
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

