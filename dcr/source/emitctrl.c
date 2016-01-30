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

	Revision History	:	1994-05-14 --- Creation.
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

#include <memory.h>
#include <string.h>

#include <dbcsyb.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_GetEmitControlData(field_count, field_list, field_align_count,
	field_align_list, header_flag, inter_field_separator,
	intra_field_separator, header_length, header_count, header_list,
	data_length_list, total_length_list, error_text)
unsigned int     field_count;
DCR_FIELD *field_list;
unsigned int     field_align_count;
GEN_ALIGN       *field_align_list;
int              header_flag;
char            *inter_field_separator;
char            *intra_field_separator;
unsigned int    *header_length;
unsigned int    *header_count;
char          ***header_list;
unsigned int   **data_length_list;
unsigned int   **total_length_list;
char            *error_text;
{
	int           return_code = DCR_SUCCESS;
	unsigned int  count_1;
	unsigned int  count_2;
	GEN_ALIGN    *align_ptr;

	*header_length     = 0;
	*header_count      = 0;
	*header_list       = NULL;
	*data_length_list  = NULL;
	*total_length_list = NULL;

	if (!field_count) {
		strcpy(error_text, "No field data available.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (!field_align_count) {
		strcpy(error_text, "No field alignment data available.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (!(*data_length_list = ((unsigned int *) calloc(field_count,
		sizeof(unsigned int))))) {
		sprintf(error_text, "%s (%u items * %u size = %u total bytes).",
			"Unable to allocate the field data lengths array",
			field_count, sizeof(unsigned int), field_count *
			sizeof(unsigned int));
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (!(*total_length_list = ((unsigned int *) calloc(field_count,
		sizeof(unsigned int))))) {
		sprintf(error_text, "%s (%u items * %u size = %u total bytes).",
			"Unable to allocate the field total lengths array",
			field_count, sizeof(unsigned int), field_count *
			sizeof(unsigned int));
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < field_count; count_1++) {
		switch (field_list[count_1].db_type) {
			case SYBBINARY		:
				(*data_length_list)[count_1] =
					2 + (field_list[count_1].data_length * 2);
				break;
			case SYBBIT			:
				(*data_length_list)[count_1] = 5;
				break;
			case SYBCHAR		:
			case SYBTEXT		:
				(*data_length_list)[count_1] =
					field_list[count_1].data_length - 1;
				break;
			case SYBIMAGE		:
				(*data_length_list)[count_1] = field_list[count_1].data_length *
					5;
				break;
			case SYBINT1		:
				(*data_length_list)[count_1] = 3;
				break;
			case SYBINT2		:
				(*data_length_list)[count_1] = 6;
				break;
			case SYBINT4		:
				(*data_length_list)[count_1] = 11;
				break;
			case SYBREAL		:
				(*data_length_list)[count_1] = 20;
				break;
			case SYBFLT8 		:
				(*data_length_list)[count_1] = 20;
				break;
			case SYBMONEY		:
				(*data_length_list)[count_1] = 21;
				break;
			case SYBMONEY4		:
				(*data_length_list)[count_1] = 12;
				break;
			case SYBDATETIME	:
			case SYBDATETIME4	:
				(*data_length_list)[count_1] = 4+1+2+1+2+1+2+1+2+1+2+1+3;
				break;
			default				:
				if ((field_list[count_1].primitive_list_count == 1) &&
					(field_list[count_1].data_length > 1) &&
					((field_align_list[field_list[count_1].primitive_list_index].
					type == GEN_C_ALIGN_char) ||
					(field_align_list[field_list[count_1].primitive_list_index].
					type == GEN_C_ALIGN_unsigned_char))) {
					(*data_length_list)[count_1] =
					field_list[count_1].data_length - 1;
					break;
				}
				(*data_length_list)[count_1] = 0;
				for (count_2 = 0;
					count_2 < field_list[count_1].primitive_list_count;
					count_2++) {
					align_ptr = field_align_list +
						field_list[count_1].primitive_list_index + count_2;
					if ((align_ptr->type == GEN_C_ALIGN_char) ||
						(align_ptr->type == GEN_C_ALIGN_unsigned_char))
						(*data_length_list)[count_1] += align_ptr->length;
					else
						(*data_length_list)[count_1] +=
							(align_ptr->array_length *
							GEN_AlignList[align_ptr->type].printf_length) +
							(align_ptr->array_length - 1);
					(*data_length_list)[count_1] +=
						(count_2 < (field_list[count_1].primitive_list_count - 1)) ?
						strlen(intra_field_separator) : 0;
				}
				break;
		}
		(*total_length_list)[count_1]  = ((*data_length_list)[count_1] >
			strlen(field_list[count_1].field_name)) ?
			(*data_length_list)[count_1] :
			strlen(field_list[count_1].field_name);
		*header_length                += (*total_length_list)[count_1] +
			((count_1 < (field_count - 1)) ? strlen(inter_field_separator) : 0);
	}

	if (header_flag == DCR_TRUE) {
		if (meml_allocate(header_count, ((void ***) header_list),
			*header_length + 1, 2) != STR_LIST_SUCCESS) {
			sprintf(error_text, "%s (2 lines * %u bytes = %u total bytes).",
				"Unable to allocate memory for the output report header lines",
				*header_length + 1, 2 * (*header_length + 1));
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		else {
			*(*header_list)[0] = '\0';
			memset((*header_list)[1], '\0', *header_length + 1);
			for (count_1 = 0; count_1 < field_count; count_1++)
				sprintf((*header_list)[0] + strlen((*header_list)[0]),
					"%-*.*s%s", ((int) (*total_length_list)[count_1]),
					((int) (*total_length_list)[count_1]),
					field_list[count_1].field_name,
					(count_1 < (field_count - 1)) ? inter_field_separator : "");
			for (count_1 = 0; count_1 < field_count; count_1++) {
				memset((*header_list)[1] + strlen((*header_list)[1]), '-',
					(*total_length_list)[count_1]);
				if (count_1 < (field_count - 1))
					strcat((*header_list)[1] + strlen((*header_list)[1]),
					inter_field_separator);
			}
		}
	}

	if (return_code != DCR_SUCCESS) {
		strl_remove_all(header_count, header_list);
		if (*data_length_list)
			free(*data_length_list);
		if (*total_length_list)
			free(*total_length_list);
		*header_count      = 0;
		*header_list       = NULL;
		*data_length_list  = NULL;
		*total_length_list = NULL;
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

