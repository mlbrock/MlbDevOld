/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies an ADF domain.

	Revision History	:	1995-08-29 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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
int ADF_COPY_Domain(const ADF_DOMAIN *in_ptr, ADF_DOMAIN *out_ptr,
	char *error_text)
#else
int ADF_COPY_Domain(in_ptr, out_ptr, error_text)
const ADF_DOMAIN *in_ptr;
ADF_DOMAIN       *out_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	*error_text = '\0';

	ADF_INIT_Domain(out_ptr);

	if ((in_ptr->domain_name != NULL) && ((out_ptr->domain_name =
		strdup(in_ptr->domain_name)) == NULL))
		return_code = ADF_MEMORY_FAILURE;
	else if ((in_ptr->domain_description != NULL) &&
		((out_ptr->domain_description =
		strdup(in_ptr->domain_description)) == NULL))
		return_code = ADF_MEMORY_FAILURE;
	else if (strl_copy(in_ptr->file_type_count,
		in_ptr->file_type_list, &out_ptr->file_type_count,
		&out_ptr->file_type_list) != STRFUNCS_SUCCESS)
		return_code = ADF_MEMORY_FAILURE;
	else if ((return_code = ADF_COPY_Pattern(&in_ptr->boh_pattern,
		&out_ptr->boh_pattern, error_text)) != ADF_SUCCESS)
		;
	else if ((return_code = ADF_COPY_Pattern(&in_ptr->eoh_pattern,
		&out_ptr->eoh_pattern, error_text)) != ADF_SUCCESS)
		;
	else if ((return_code = ADF_COPY_Pattern(&in_ptr->bol_pattern,
		&out_ptr->bol_pattern, error_text)) != ADF_SUCCESS)
		;
	else if ((return_code = ADF_COPY_Pattern(&in_ptr->eol_pattern,
		&out_ptr->eol_pattern, error_text)) != ADF_SUCCESS)
		;
	else if ((return_code = ADF_COPY_Pattern(&in_ptr->empty_line_pattern,
		&out_ptr->empty_line_pattern, error_text)) != ADF_SUCCESS)
		;
	else if ((return_code = ADF_COPY_Pattern(&in_ptr->strip_pattern,
		&out_ptr->strip_pattern, error_text)) != ADF_SUCCESS)
		;
	else
		return_code = ADF_COPY_SectionList(in_ptr->section_count,
			in_ptr->section_list, &out_ptr->section_count,
			&out_ptr->section_list, error_text);

	if (return_code != ADF_SUCCESS) {
		ADF_FREE_Domain(out_ptr);
		if (!(*error_text))
			strcpy(error_text, "Insufficent memory to copy domain.");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_COPY_DomainList(unsigned int in_count, const ADF_DOMAIN *in_list,
	unsigned int *out_count, ADF_DOMAIN **out_list, char *error_text)
#else
int ADF_COPY_DomainList(in_count, in_list, out_count,
	out_list, error_text)
unsigned int       in_count;
const ADF_DOMAIN  *in_list;
unsigned int      *out_count;
ADF_DOMAIN       **out_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((ADF_DOMAIN *) malloc(in_count *
			sizeof(ADF_DOMAIN)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(ADF_DOMAIN), error_text,
				"Unable to copy the domain list");
			return_code = ADF_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			ADF_INIT_DomainList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = ADF_COPY_Domain(in_list + count_1,
					*out_list + count_1, error_text)) != ADF_SUCCESS) {
					ADF_FREE_DomainList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

