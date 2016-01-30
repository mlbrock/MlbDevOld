/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copirs 'SPF_SPEC' structures.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
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
int SPF_COPY_Spec(const SPF_SPEC *in_ptr, SPF_SPEC *out_ptr, char *error_text)
#else
int SPF_COPY_Spec(in_ptr, out_ptr, error_text)
const SPF_SPEC *in_ptr;
SPF_SPEC       *out_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	*out_ptr    = *in_ptr;

	*error_text = '\0';

	return(SPF_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_COPY_SpecList(unsigned int in_count, const SPF_SPEC *in_list,
	unsigned int *out_count, SPF_SPEC **out_list, char *error_text)
#else
int SPF_COPY_SpecList(in_count, in_list, out_count, out_list, error_text)
unsigned int      in_count;
const SPF_SPEC  *in_list;
unsigned int     *out_count;
SPF_SPEC       **out_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = SPF_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((SPF_SPEC *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgItem(in_count * sizeof(**out_list), error_text,
				"Unable to copy specification list");
			return_code = SPF_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			SPF_INIT_SpecList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = SPF_COPY_Spec(in_list + count_1,
					*out_list + count_1, error_text)) != SPF_SUCCESS) {
					SPF_FREE_SpecList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

