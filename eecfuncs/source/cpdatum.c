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
#include "evaldefs.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_COPY_DatumPtr(const EEC_DATUM *in_ptr, EEC_DATUM *out_ptr,
	char *error_text)
#else
int EEC_COPY_DatumPtr(in_ptr, out_ptr, error_text)
const EEC_DATUM *in_ptr;
EEC_DATUM       *out_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = EEC_SUCCESS;

	*out_ptr = *in_ptr;

	if ((EEC_EVAL_DATUM_IS_STRING(in_ptr) == EEC_TRUE) &&
		(EEC_EVAL_DATUM_IS_STATIC(in_ptr) != EEC_TRUE) &&
		((out_ptr->datum.string.data =
		((char *) memdup(in_ptr->datum.string.data,
		(in_ptr->datum.string.length + 1) * sizeof(char)))) == NULL)) {
		EEC_INIT_EEC_DATUM(out_ptr);
		STR_AllocMsgItem(in_ptr->datum.string.length + 1, error_text,
			"Unable to copy an 'EEC_DATUM' string value");
		return_code = EEC_SUCCESS;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_COPY_DatumList(unsigned int in_count, const EEC_DATUM *in_list,
	unsigned int *out_count, EEC_DATUM **out_list, char *error_text)
#else
int EEC_COPY_DatumList(in_count, in_list, out_count, out_list, error_text)
unsigned int      in_count;
const EEC_DATUM  *in_list;
unsigned int     *out_count;
EEC_DATUM       **out_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = EEC_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((EEC_DATUM *) calloc(in_count,
			sizeof(EEC_DATUM)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(EEC_DATUM), error_text,
				"Unable to copy the post-fix list");
			return_code = EEC_MEMORY_FAILURE;
		}
		else {
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = EEC_COPY_DatumPtr(in_list + count_1,
					*out_list + count_1, error_text)) != EEC_SUCCESS) {
					EEC_FREE_DatumList(out_count, out_list);
					break;
				}
				(*out_count)++;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

