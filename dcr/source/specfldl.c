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

	Revision History	:	1994-06-05 --- Creation.
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

#include <stdio.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_GetSpecifiedFieldList(field_count, field_list, field_name_count,
	field_name_list, field_spec_count, field_spec_list, out_field_count,
	out_field_list, error_text)
unsigned int           field_count;
DCR_FIELD       *field_list;
unsigned int           field_name_count;
DCR_FIELD_NAME  *field_name_list;
unsigned int           field_spec_count;
char                 **field_spec_list;
unsigned int          *out_field_count;
DCR_FIELD      **out_field_list;
char                  *error_text;
{
	int            return_code = DCR_SUCCESS;
	unsigned int   name_count  = 0;
	char         **name_list   = NULL;
	char          *tmp_string  = NULL;
	unsigned int   count_1;
	unsigned int   count_2;
	unsigned int   found_index;

	if (!field_spec_count) {
		if (mema_copy(field_count, field_list, sizeof(*field_list),
			out_field_count, ((void **) out_field_list)) != DCR_SUCCESS) {
			sprintf(error_text, "%s (%u elements * %u size = %u total bytes).",
				"Unable to allocate memory for the copied field list",
				field_count, sizeof(**out_field_list),
				field_count * sizeof(**out_field_list));
			return_code = DCR_MEMORY_FAILURE;
		}
	}
	else {
		*out_field_count = 0;
		*out_field_list  = NULL;
		for (count_1 = 0; count_1 < field_spec_count; count_1++) {
			if ((tmp_string = strdup(field_spec_list[count_1])) == NULL) {
				strcpy(error_text, "Unable to copy the field name string.");
				return_code = DCR_MEMORY_FAILURE;
				break;
			}
			else {
				if (sepwordx(trim(noblank(nocontrl(tmp_string))), ",",
					&name_count, &name_list) != STRFUNCS_SUCCESS) {
					strcpy(error_text, "Unable to allocate the field name list.");
					return_code = DCR_MEMORY_FAILURE;
					break;
				}
				else {
					for (count_2 = 0; count_2 < name_count; count_2++) {
						if (!name_list[count_2][0])
							continue;
						if (DCR_FIND_FIELD_NAME(field_name_count,
							field_name_list, name_list[count_2], &found_index) !=
							STRFUNCS_ITEM_FOUND) {
							sprintf(error_text,
								"The specified field name '%.500s' %s.",
								name_list[count_2], "is not valid");
							return_code = DCR_BAD_ARGS_FAILURE;
							break;
						}
						else if (mema_append(out_field_count,
							((void **) out_field_list), field_list +
							field_name_list[found_index].field_number,
							sizeof(**out_field_list)) != STRFUNCS_SUCCESS) {
							sprintf(error_text,
								"%s (%u elements * %u size = %u total bytes).",
								"Unable to allocate memory for the copied field list",
								*out_field_count + 1, sizeof(**out_field_list),
								(*out_field_count + 1) * sizeof(**out_field_list));
							return_code = DCR_MEMORY_FAILURE;
							break;
						}
					}
					strl_remove_all(&name_count, &name_list);
				}
				free(tmp_string);
			}
			if (return_code != DCR_SUCCESS)
				break;
		}
		if (return_code != DCR_SUCCESS)
			mema_remove_all(out_field_count, ((void **) out_field_list));
	}

	return(return_code);
}
/*	***********************************************************************	*/

