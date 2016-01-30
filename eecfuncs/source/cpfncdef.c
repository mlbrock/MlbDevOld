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

		Copyright Michael L. Brock 1996 - 2016.
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
int EEC_COPY_FuncDefPtr(const EEC_FUNC_DEF *in_ptr, EEC_FUNC_DEF *out_ptr,
	char *error_text)
#else
int EEC_COPY_FuncDefPtr(in_ptr, out_ptr, error_text)
const EEC_FUNC_DEF *in_ptr;
EEC_FUNC_DEF       *out_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	*out_ptr = *in_ptr;

	if ((out_ptr->func_name = strdup(in_ptr->func_name)) == NULL) {
		EEC_INIT_EEC_FUNC_DEF(out_ptr);
		STR_AllocMsgItem(strlen(in_ptr->func_name) + 1, error_text,
			"Unable to copy function definition function name ('%-.500s')",
			in_ptr->func_name);
		return_code = EEC_MEMORY_FAILURE;
	}
	else
		return_code = EEC_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_COPY_FuncDefList(unsigned int in_count, const EEC_FUNC_DEF *in_list,
	unsigned int *out_count, EEC_FUNC_DEF **out_list, char *error_text)
#else
int EEC_COPY_FuncDefList(in_count, in_list, out_count, out_list, error_text)
unsigned int         in_count;
const EEC_FUNC_DEF  *in_list;
unsigned int        *out_count;
EEC_FUNC_DEF       **out_list;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = EEC_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((EEC_FUNC_DEF *) calloc(in_count,
			sizeof(EEC_FUNC_DEF)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(EEC_FUNC_DEF), error_text,
				"Unable to copy the function definition list");
			return_code = EEC_MEMORY_FAILURE;
		}
		else {
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = EEC_COPY_FuncDefPtr(in_list + count_1,
					*out_list + count_1, error_text)) != EEC_SUCCESS) {
					EEC_FREE_FuncDefList(out_count, out_list);
					break;
				}
				(*out_count)++;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

