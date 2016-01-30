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

	Revision History	:	1996-02-11 --- Creation.
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

#include <ctype.h>
#include <stdio.h>

#include "eecfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EMIT_HumanString(unsigned int string_length, const char *string_ptr,
	int quotes_flag, unsigned int max_output_chars,
	STR_FUNC_TYPE_fprintf  output_function, void *output_control)
#else
void EEC_EMIT_HumanString(string_length, string_ptr, quotes_flag,
	max_output_chars, output_function, output_control)
unsigned int           string_length;
const char            *string_ptr;
unsigned int           max_output_chars;
int                    quotes_flag;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	const char   *in_ptr;
	unsigned int  buffer_length;
	char          buffer[512 + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	max_output_chars = (!max_output_chars) ? UINT_MAX : max_output_chars;
	in_ptr           = string_ptr;

	if (quotes_flag != EEC_FALSE)
		(*output_function)(output_control, "\"");

	while (string_length && max_output_chars) {
		buffer_length = (string_length > ((sizeof(buffer) - 1) / 4)) ?
			((sizeof(buffer) - 1) / 4) : string_length;
		buffer_length = (buffer_length > max_output_chars) ? max_output_chars :
			buffer_length;
		(*output_function)(output_control, "%s",
			mem2cstr(buffer_length, in_ptr, STR_MEM2CSTR_NO_TRIGRAPHS, buffer));
		string_length -= buffer_length;
		in_ptr        += buffer_length;
	}

	if (quotes_flag != EEC_FALSE)
		(*output_function)(output_control, "\"");
}
/*	***********************************************************************	*/

