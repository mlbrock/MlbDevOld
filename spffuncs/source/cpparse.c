/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'SPF_PARSE' structures.

	Revision History	:	1995-08-21 --- Creation.
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

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_COPY_Parse(const SPF_PARSE *in_ptr, SPF_PARSE *out_ptr,
	char *error_text)
#else
int SPF_COPY_Parse(in_ptr, out_ptr, error_text)
const SPF_PARSE *in_ptr;
SPF_PARSE       *out_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = SPF_SUCCESS;
	char tmp_error_text[SPF_MAX_ERROR_TEXT];

	SPF_INIT_Parse(out_ptr);

	if (!in_ptr->flags)
		out_ptr->text = in_ptr->text;
	else if (in_ptr->length && (in_ptr->text != NULL) &&
		((out_ptr->text = strndup(in_ptr->text, in_ptr->length)) == NULL)) {
		STR_AllocMsgItem(in_ptr->length + 1, error_text,
			"Unable to copy the parse item text %s",
			SPF_GetLocationFile(in_ptr, 500, tmp_error_text));
		return_code = SPF_MEMORY_FAILURE;
	}

	if (return_code == SPF_SUCCESS) {
		out_ptr->file       = in_ptr->file;
		out_ptr->line       = in_ptr->line;
		out_ptr->length     = in_ptr->length;
		out_ptr->spec_type  = in_ptr->spec_type;
		out_ptr->spec_index = in_ptr->spec_index;
		out_ptr->list_index = in_ptr->list_index;
		out_ptr->flags      = in_ptr->flags;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_COPY_ParseList(unsigned int in_count, const SPF_PARSE *in_list,
	unsigned int *out_count, SPF_PARSE **out_list, char *error_text)
#else
int SPF_COPY_ParseList(in_count, in_list, out_count, out_list, error_text)
unsigned int      in_count;
const SPF_PARSE  *in_list;
unsigned int     *out_count;
SPF_PARSE       **out_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = SPF_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((SPF_PARSE *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgItem(in_count * sizeof(**out_list), error_text,
				"Unable to copy action specification list");
			return_code = SPF_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			SPF_INIT_ParseList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = SPF_COPY_Parse(in_list + count_1,
					*out_list + count_1, error_text)) != SPF_SUCCESS) {
					SPF_FREE_ParseList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

