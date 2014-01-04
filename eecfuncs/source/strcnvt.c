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

	Revision History	:	1991-12-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
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

#include "eecfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_StringToHumanString(unsigned int string_length, const char *string_ptr,
	int quotes_flag, char **out_string, char *error_text)
#else
int EEC_StringToHumanString(string_length, string_ptr, quotes_flag,
	out_string, error_text)
unsigned int   string_length;
const char    *string_ptr;
int            quotes_flag;
char         **out_string;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = EEC_SUCCESS;
	unsigned int out_length;

	out_length = mem2cstr_length(string_length, string_ptr,
		STR_MEM2CSTR_NO_TRIGRAPHS) + ((quotes_flag != EEC_FALSE) ? 2 : 0) + 1;

	if ((*out_string = ((char *) calloc(out_length, sizeof(char)))) == NULL) {
		STR_AllocMsgItem(out_length, error_text, "%s %s",
			"Unable to allocate memory for a human-readable representation of",
			"a string in post-fix format");
		return_code = EEC_MEMORY_FAILURE;
	}
	else
		mem2cstr(string_length, string_ptr, STR_MEM2CSTR_NO_TRIGRAPHS,
			*out_string);

	return(return_code);
}
/*	***********************************************************************	*/

