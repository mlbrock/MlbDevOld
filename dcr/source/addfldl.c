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

	Revision History	:	1994-06-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_GetAddedFieldList(field_spec_count, field_spec_list, out_field_count,
	out_field_list, error_text)
unsigned int   field_spec_count;
char         **field_spec_list;
unsigned int  *out_field_count;
DCR_FIELD    **out_field_list;
char          *error_text;
{
	int            return_code = DCR_SUCCESS;
	unsigned int   name_count  = 0;
	char         **name_list   = NULL;
	char          *tmp_string  = NULL;
	unsigned int   count_1;
	double         tmp_double;
	DCR_FIELD      tmp_field;

	*out_field_count = 0;
	*out_field_list  = NULL;

	for (count_1 = 0; count_1 < field_spec_count; count_1++) {
		if ((tmp_string = strdup(field_spec_list[count_1])) == NULL) {
			strcpy(error_text,
				"Unable to copy the added field specification string.");
			return_code = DCR_MEMORY_FAILURE;
		}
		else if (sepwordx_keep(trim(noblank(nocontrl(tmp_string))), ":",
			&name_count, &name_list) != STRFUNCS_SUCCESS) {
			strcpy(error_text,
				"Unable to allocate the added field specification list.");
			return_code = DCR_MEMORY_FAILURE;
		}
		else if (name_count != 4) {
			sprintf(error_text, "%s ('%-.500s') --- expected format '%s'.",
				"Invalid cache added field specification string",
				field_spec_list[count_1],
				"<field-name>:[<short-name>]:[<count>]:<type-spec>");
			return_code = DCR_BAD_ARGS_FAILURE;
		}
		else if (!name_list[0][0]) {
			sprintf(error_text, "%s ('%-.500s') %s ('%-.300s') is empty.",
				"Invalid cache added field specification string",
				field_spec_list[count_1], "the field name", name_list[0]);
			return_code = DCR_BAD_ARGS_FAILURE;
		}
		else if (!name_list[3][0]) {
			sprintf(error_text, "%s ('%-.500s') %s ('%-.300s') is empty.",
				"Invalid cache added field specification string",
				field_spec_list[count_1], "the field type specification",
				name_list[3]);
			return_code = DCR_BAD_ARGS_FAILURE;
		}
		else if (strlen(name_list[0]) >= sizeof(tmp_field.field_name)) {
			sprintf(error_text,
				"%s ('%-.500s') %s ('%-.300s') %s --- %s %d.",
				"Invalid cache added field specification string",
				field_spec_list[count_1], "the field name", name_list[0],
				"exceeds the maximum length", "the maximum field name length is",
				sizeof(tmp_field.field_name) - 1);
			return_code = DCR_BAD_ARGS_FAILURE;
		}
		else if (strlen(name_list[3]) >= sizeof(tmp_field.primitive_type_spec)){
			sprintf(error_text,
				"%s ('%-.500s') %s ('%-.300s') %s --- %s %d.",
				"Invalid cache added field specification string",
				field_spec_list[count_1], "the field type specification",
				name_list[0], "exceeds the maximum length",
				"the maximum field type specification length is",
				sizeof(tmp_field.primitive_type_spec) - 1);
			return_code = DCR_BAD_ARGS_FAILURE;
		}
		else if (*name_list[2] && ((atof(name_list[2]) < 1.0) ||
			(atof(name_list[2]) > ((double) SHRT_MAX)))) {
			sprintf(error_text,
				"%s ('%-.500s') %s ('%-.300s') %s --- %s 1 and %d, inclusive.",
				"Invalid cache added field specification string",
				field_spec_list[count_1], "the field array length", name_list[2],
				"is outside of the valid range",
				"the array length must be between", SHRT_MAX);
			return_code = DCR_BAD_ARGS_FAILURE;
		}
		else {
			memset(&tmp_field, '\0', sizeof(tmp_field));
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		Set the cache field field-related members . . .		*/
			/*	*****************************************************	*/
			tmp_double                     = atof(name_list[2]);
			tmp_field.primitive_type_count = ((unsigned int) tmp_double);
			tmp_field.db_table_order       = 0;
			tmp_field.db_column_name[0]    = '\0';
			nstrcpy(tmp_field.field_name, name_list[0],
				sizeof(tmp_field.field_name) - 1);
			nstrcpy(tmp_field.primitive_type_spec, name_list[3],
				sizeof(tmp_field.primitive_type_spec) - 1);
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		Initialize some other members of the structure.		*/
			/*	*****************************************************	*/
			tmp_field.primitive_list_index = 0;
			tmp_field.primitive_list_count = 0;
			tmp_field.data_offset          = 0;
			tmp_field.data_length          = 0;
#if 0
	CODE NOTE: To be removed.
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		Fix-up 'char' fields so that there's an additonal	*/
			/*	byte reserved for the ASCII 0.								*/
			/*	*****************************************************	*/
			if (!stricmp("C", name_list[3]))
				tmp_field.primitive_type_count++;
			/*	*****************************************************	*/
#endif /* #if 0 */
			if (mema_append(out_field_count, ((void **) out_field_list),
				&tmp_field, sizeof(tmp_field)) != STRFUNCS_SUCCESS) {
				sprintf(error_text,
					"%s (%u elements * %u size = %u total bytes).",
					"Unable to allocate memory for the added field list",
					*out_field_count + 1, sizeof(tmp_field),
					(*out_field_count + 1) * sizeof(tmp_field));
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		if (tmp_string != NULL)
			free(tmp_string);
		strl_remove_all(&name_count, &name_list);
		if (return_code != DCR_SUCCESS) {
			mema_remove_all(out_field_count, ((void **) out_field_list));
			break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/


