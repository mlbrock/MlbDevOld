/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies an ADF section.

	Revision History	:	1995-08-29 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_COPY_Section(const ADF_SECTION *in_ptr, ADF_SECTION *out_ptr,
	char *error_text)
#else
int ADF_COPY_Section(in_ptr, out_ptr, error_text)
const ADF_SECTION *in_ptr;
ADF_SECTION       *out_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	*error_text = '\0';

	ADF_INIT_Section(out_ptr);

	out_ptr->area_index       = in_ptr->area_index;
	out_ptr->required_flag    = in_ptr->required_flag;
	out_ptr->wrap_flag        = in_ptr->wrap_flag;
	out_ptr->ltrim_flag       = in_ptr->ltrim_flag;
	out_ptr->rtrim_flag       = in_ptr->rtrim_flag;
	out_ptr->squeeze_flag     = in_ptr->squeeze_flag;
	out_ptr->para_format_flag = in_ptr->para_format_flag;
	out_ptr->char_format_flag = in_ptr->char_format_flag;
	out_ptr->eindex_flag      = in_ptr->eindex_flag;
	out_ptr->htext_flag       = in_ptr->htext_flag;

	if ((in_ptr->section_name != NULL) &&
		((out_ptr->section_name =
		strdup(in_ptr->section_name)) == NULL))
		return_code = ADF_MEMORY_FAILURE;
	else if ((in_ptr->output_section_name != NULL) &&
		((out_ptr->output_section_name =
		strdup(in_ptr->output_section_name)) == NULL))
		return_code = ADF_MEMORY_FAILURE;
	else
		return_code = ADF_COPY_Pattern(&in_ptr->match_pattern,
			&out_ptr->match_pattern, error_text);

	if (return_code != ADF_SUCCESS) {
		ADF_FREE_Section(out_ptr);
		if (!(*error_text))
			strcpy(error_text, "Insufficent memory to copy section.");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_COPY_SectionList(unsigned int in_count, const ADF_SECTION *in_list,
	unsigned int *out_count, ADF_SECTION **out_list, char *error_text)
#else
int ADF_COPY_SectionList(in_count, in_list, out_count,
	out_list, error_text)
unsigned int        in_count;
const ADF_SECTION  *in_list;
unsigned int       *out_count;
ADF_SECTION       **out_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((ADF_SECTION *) malloc(in_count *
			sizeof(ADF_SECTION)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(ADF_SECTION), error_text,
				"Unable to copy the section list");
			return_code = ADF_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			ADF_INIT_SectionList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = ADF_COPY_Section(in_list + count_1,
					*out_list + count_1, error_text)) != ADF_SUCCESS) {
					ADF_FREE_SectionList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

