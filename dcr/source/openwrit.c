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

#include <memory.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_OpenWrite(cache_control_ptr, cache_file_name, out_cache_ptr,
	out_cache_index, error_text)
DCR_CONTROL  *cache_control_ptr;
const char         *cache_file_name;
DCR_CACHE         **out_cache_ptr;
unsigned int       *out_cache_index;
char               *error_text;
{
	int       return_code;
	int       errno_code;
	int       open_failure_flag;
	int       mmap_failure_flag;
	DCR_CACHE tmp_cache;

   memset(&tmp_cache, '\0', sizeof(tmp_cache));

	if ((return_code = DCR_AddACache(cache_control_ptr, cache_file_name,
		&tmp_cache, out_cache_ptr, out_cache_index, error_text)) ==
		DCR_SUCCESS) {
		(*out_cache_ptr)->cache_access_type    = DCR_I_AM_WRITER;
		(*out_cache_ptr)->cycle_retry_count    = DCR_CYCLE_RETRY_COUNT;
		(*out_cache_ptr)->cycle_retry_time_out = DCR_CYCLE_RETRY_TIME_OUT;
		(*out_cache_ptr)->lock_retry_count     = DCR_LOCK_RETRY_COUNT;
		(*out_cache_ptr)->lock_retry_time_out  = DCR_LOCK_RETRY_TIME_OUT;
		if ((return_code =
			DCR_OpenCache((*out_cache_ptr)->cache_file_name,
			DCR_I_AM_WRITER, &(*out_cache_ptr)->open_flag,
			&(*out_cache_ptr)->mmap_prot, &(*out_cache_ptr)->mmap_flag,
			&(*out_cache_ptr)->file_handle, &(*out_cache_ptr)->mmap_ptr,
			&(*out_cache_ptr)->mmap_size, &(*out_cache_ptr)->cache_block_size,
			&errno_code, &open_failure_flag, &mmap_failure_flag, error_text)) ==
			DCR_SUCCESS) {
			if ((return_code = DCR_CheckHeader(((DCR_HEADER *)
				(*out_cache_ptr)->mmap_ptr), (*out_cache_ptr)->mmap_size,
				error_text)) == DCR_SUCCESS)
				if ((return_code = DCR_AllocCache(*out_cache_ptr,
					((DCR_HEADER *) (*out_cache_ptr)->mmap_ptr),
					error_text)) == DCR_SUCCESS) {
					(*out_cache_ptr)->header_ptr->cache_writer_pid           =
						getpid();
					(*out_cache_ptr)->header_ptr->cache_writer_ip_address[0] = 0;
					(*out_cache_ptr)->header_ptr->cache_writer_ip_address[1] = 0;
					(*out_cache_ptr)->header_ptr->cache_writer_ip_address[2] = 0;
					(*out_cache_ptr)->header_ptr->cache_writer_ip_address[3] = 0;
				}
		}
		if (return_code != DCR_SUCCESS)
			DCR_CloseOneCache(*out_cache_ptr);
	}

	if (return_code != DCR_SUCCESS) {
		*out_cache_ptr   = NULL;
		*out_cache_index = 0;
	}

	return(return_code);
}
/*	***********************************************************************	*/

