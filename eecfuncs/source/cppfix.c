/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Expression Evaluation Calculator Library (EECFUNCS) Library Module		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1996-03-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
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

#include "eecfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_COPY_PostFixPtr(const EEC_POSTFIX *in_ptr, EEC_POSTFIX *out_ptr,
	char *error_text)
#else
int EEC_COPY_PostFixPtr(in_ptr, out_ptr, error_text)
const EEC_POSTFIX *in_ptr;
EEC_POSTFIX       *out_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = EEC_SUCCESS;

	EEC_INIT_EEC_POSTFIX(out_ptr);

	if (in_ptr->length) {
		if ((out_ptr->data = ((char *) memdup(in_ptr->data,
			in_ptr->length * sizeof(char)))) == NULL) {
			STR_AllocMsgItem(in_ptr->length * sizeof(char), error_text,
				"Unable to copy the post-fix data");
			return_code = EEC_MEMORY_FAILURE;
		}
		else {
			out_ptr->type   = in_ptr->type;
			out_ptr->length = in_ptr->length;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_COPY_PostFixList(unsigned int in_count, const EEC_POSTFIX *in_list,
	unsigned int *out_count, EEC_POSTFIX **out_list, char *error_text)
#else
int EEC_COPY_PostFixList(in_count, in_list, out_count, out_list, error_text)
unsigned int        in_count;
const EEC_POSTFIX  *in_list;
unsigned int       *out_count;
EEC_POSTFIX       **out_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = EEC_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((EEC_POSTFIX *) calloc(in_count,
			sizeof(EEC_POSTFIX)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(EEC_POSTFIX), error_text,
				"Unable to copy the post-fix list");
			return_code = EEC_MEMORY_FAILURE;
		}
		else {
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = EEC_COPY_PostFixPtr(in_list + count_1,
					*out_list + count_1, error_text)) != EEC_SUCCESS) {
					EEC_FREE_PostFixList(out_count, out_list);
					break;
				}
				(*out_count)++;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

