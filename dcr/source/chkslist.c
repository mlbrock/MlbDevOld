/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a specified 'genfuncs' structure member field
								list against the fields within a cache to ensure
								consonance.

	Revision History	:	1994-07-26 --- Creation.
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

#include <stdio.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_CheckStructList(cache_ptr, struct_size, struct_count, struct_list,
	error_text)
DCR_CACHE    *cache_ptr;
unsigned int  struct_size;
unsigned int  struct_count;
GEN_MEMBER   *struct_list;
char         *error_text;
{
	int          return_code = DCR_SUCCESS;
	unsigned int count_1;

	if (struct_size > cache_ptr->actual_data_record_size) {
		sprintf(error_text, "The structure size (%u) %s '%s' (%u).",
			struct_size,
			"is greater than the actual data record length in the cache file",
			cache_ptr->cache_file_name, cache_ptr->actual_data_record_size);
		return_code = DCR_FAILURE;
	}
	else {
		for (count_1 = 0; count_1 < struct_count; count_1++) {
			if ((count_1 >= cache_ptr->field_count) ||
				(strcmp(struct_list[count_1].name,
				cache_ptr->field_list[count_1].field_name))) {
				sprintf(error_text,
					"%s '%s' %s '%s' field list --- %s %u %s.",
					"Unable to locate the structure member",
					struct_list[count_1].name, "in the cache file",
					cache_ptr->cache_file_name, "expected that field as number",
					count_1, "(starting from zero)");
				return_code = DCR_FAILURE;
				break;
			}
			else if (struct_list[count_1].length !=
				cache_ptr->field_list[count_1].data_length) {
				sprintf(error_text, "%s '%s' (%u) %s %s '%s' (%u).",
					"The length of the structure member",
					struct_list[count_1].name,
					struct_list[count_1].length,
					"does not match the length as specified by the field of the",
					"same name in the cache file", cache_ptr->cache_file_name,
					cache_ptr->field_list[count_1].data_length);
				return_code = DCR_FAILURE;
				break;
			}
			else if (struct_list[count_1].offset !=
				cache_ptr->field_list[count_1].data_offset) {
				sprintf(error_text, "%s '%s' (%u) %s %s '%s' (%u).",
					"The offset of the SCF structure member",
					struct_list[count_1].name,
					struct_list[count_1].offset,
					"does not match the offset as specified by the field of the",
					"same name in the cache file", cache_ptr->cache_file_name,
					cache_ptr->field_list[count_1].data_offset);
				return_code = DCR_FAILURE;
				break;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

