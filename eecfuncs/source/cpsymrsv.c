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
int EEC_COPY_SymbolResolvePtr(const EEC_SYMBOL_RESOLVE *in_ptr,
	EEC_SYMBOL_RESOLVE *out_ptr, char *error_text)
#else
int EEC_COPY_SymbolResolvePtr(in_ptr, out_ptr, error_text)
const EEC_SYMBOL_RESOLVE *in_ptr;
EEC_SYMBOL_RESOLVE       *out_ptr;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	EEC_INIT_EEC_SYMBOL_RESOLVE(out_ptr);

	if ((return_code = EEC_COPY_SymbolList(in_ptr->count, in_ptr->list,
		&out_ptr->count, &out_ptr->list, error_text)) != EEC_SUCCESS)
		strinst(error_text,
			"Unable to copy the 'EEC_SYMBOL_RESOLVE' symbol list", 0);
	else
		out_ptr->symbol_resolve_func = in_ptr->symbol_resolve_func;

	return(return_code);
}
/*	***********************************************************************	*/

