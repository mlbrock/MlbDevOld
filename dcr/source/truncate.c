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

		Copyright Michael L. Brock 1994 - 2018.
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

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DCR_TruncateCache

   SYNOPSIS    :  return_code = DCR_TruncateCache(cache_ptr, length,
							error_text);

						int            return_code;

						DCR_CACHE     *cache_ptr;

						unsigned long  length;

						char          *error_text;

   DESCRIPTION :  Truncates a cache file to the specified length.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``cache_ptr``, which is the pointer to a structure of
						type ''DCR_CACHE''.

						(.) ``length`` is the length to which the memory-mapped
						file is to be truncated.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if no error occurred.

						(.) Non-zero if an error occurred.

   NOTES       :  This function is the DCR cache library analogue of
						the UNIX library function ``ftruncate()``.

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock Associates

	OUTPUT INDEX:	DCR_TruncateCache
						Memory-mapped File Functions:DCR_TruncateCache
						DCR Shared Cache Facility:DCR_TruncateCache

	PUBLISH XREF:	DCR_TruncateCache

	PUBLISH NAME:	DCR_TruncateCache

EOH */
/* *********************************************************************** */
int DCR_TruncateCache(cache_ptr, length, error_text)
DCR_CACHE     *cache_ptr;
unsigned long  length;
char          *error_text;
{
	int           return_code = DCR_SUCCESS;
	int           fatal_error_flag;
	unsigned long file_size;

	if ((return_code = DCR_AssertAccessType(cache_ptr,
		DCR_I_AM_WRITER, error_text)) == DCR_SUCCESS) {
		file_size = cache_ptr->mmap_size;
		if (!mtruncate_basic_2(cache_ptr->file_handle, &file_size,
			&cache_ptr->mmap_size, &cache_ptr->mmap_ptr, NULL,
			cache_ptr->mmap_prot, cache_ptr->mmap_flag, length, 1,
			&fatal_error_flag))
			cache_ptr->header_ptr = ((DCR_HEADER *) cache_ptr->mmap_ptr);
		else {
			sprintf(error_text, "%s %lu bytes failed: ",
				"Attempt to re-size the cache to", length);
			DCR_GEN_AppendLastErrorString(error_text);
			return_code = DCR_SYSTEM_FAILURE;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

