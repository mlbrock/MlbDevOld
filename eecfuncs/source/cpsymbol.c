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
int EEC_COPY_SymbolPtr(const EEC_SYMBOL *in_ptr, EEC_SYMBOL *out_ptr,
	char *error_text)
#else
int EEC_COPY_SymbolPtr(in_ptr, out_ptr, error_text)
const EEC_SYMBOL *in_ptr;
EEC_SYMBOL       *out_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	EEC_INIT_EEC_SYMBOL(out_ptr);
	out_ptr->length = in_ptr->length;

	if ((out_ptr->name = strdup(in_ptr->name)) == NULL) {
		EEC_INIT_EEC_SYMBOL(out_ptr);
		STR_AllocMsgItem(strlen(in_ptr->name) + 1, error_text,
			"Unable to copy symbol name ('%-.500s')", in_ptr->name);
		return_code = EEC_MEMORY_FAILURE;
	}
	else if ((return_code = EEC_COPY_PostFixPtr(&in_ptr->postfix,
		&out_ptr->postfix, error_text)) != EEC_SUCCESS)
		;
	else if ((return_code = EEC_COPY_DatumPtr(&in_ptr->value, &out_ptr->value,
		error_text)) != EEC_SUCCESS)
		;
	else
		return_code = EEC_SUCCESS;

	if (return_code != EEC_SUCCESS)
		strinst(error_text, "Unable to copy 'EEC_SYMBOL' structure: ", 0);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_COPY_SymbolList(unsigned int in_count, const EEC_SYMBOL *in_list,
	unsigned int *out_count, EEC_SYMBOL **out_list, char *error_text)
#else
int EEC_COPY_SymbolList(in_count, in_list, out_count, out_list, error_text)
unsigned int       in_count;
const EEC_SYMBOL  *in_list;
unsigned int      *out_count;
EEC_SYMBOL       **out_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = EEC_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((EEC_SYMBOL *) calloc(in_count,
			sizeof(EEC_SYMBOL)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(EEC_SYMBOL), error_text,
				"Unable to copy the symbol definition list");
			return_code = EEC_MEMORY_FAILURE;
		}
		else {
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = EEC_COPY_SymbolPtr(in_list + count_1,
					*out_list + count_1, error_text)) != EEC_SUCCESS) {
					EEC_FREE_SymbolList(out_count, out_list);
					break;
				}
				(*out_count)++;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

