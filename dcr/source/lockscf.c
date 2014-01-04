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

		Copyright Michael L. Brock 1994 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_LockCache(cache_ptr, cache_status, error_text)
DCR_CACHE     *cache_ptr;
unsigned long  cache_status;
char          *error_text;
{
	int return_code;

	if ((return_code = DCR_AssertAccessType(cache_ptr,
		DCR_I_AM_WRITER, error_text)) == DCR_SUCCESS) {
		if (cache_ptr->header_ptr->cache_lock_status.lock_flag ==
			DCR_LOCK_LOCKED_FLAG) {
			strcat(strcpy(error_text, "Attempt to lock the cache failed "),
				"because it is already locked.");
			return_code = DCR_FAILURE;
		}
		else {
			DCR_LOCK_Lock(&cache_ptr->header_ptr->cache_lock_status);
			cache_ptr->header_ptr->cache_status = cache_status;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

