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

	Revision History	:	1996-03-02 --- Version 5 initial cut.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "eecfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_FormulaToValue(unsigned int formula_length, const char *formula_ptr,
	EEC_DATUM *result_ptr, unsigned int *parse_index, char *error_text)
#else
int EEC_FormulaToValue(formula_length, formula_ptr, result_ptr, parse_index,
	error_text)
unsigned int  formula_length;
const char   *formula_ptr;
EEC_DATUM    *result_ptr;
unsigned int *parse_index;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code;
	EEC_CONTROL control_data;
	EEC_POSTFIX postfix_data;

	EEC_INIT_EEC_DATUM(result_ptr);
	EEC_INIT_EEC_CONTROL(&control_data);

	if ((return_code = EEC_CreateControl(&control_data, error_text)) ==
		EEC_SUCCESS) {
		if ((return_code = EEC_ParseIt(&control_data, formula_length,
			formula_ptr, NULL, &postfix_data, parse_index, error_text)) ==
			EEC_SUCCESS) {
			return_code = EEC_EvalIt(&control_data, &postfix_data, result_ptr,
				error_text);
			EEC_FREE_PostFixPtr(&postfix_data);
		}
		EEC_FREE_Control(&control_data);
	}

	return(return_code);
}
/*	***********************************************************************	*/

