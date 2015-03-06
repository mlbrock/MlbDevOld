/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the concatenation of strings.

	Revision History	:	2001-03-03 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
#ifndef NO_STDARGS
char *STR_Join(char *out_string, const char *first_string,
	const char *middle_string, const char *last_string, ...)
#else
char *STR_Join(out_string, first_string, middle_string, last_string,
	va_alist)
char       *out_string;
const char *first_string;
const char *middle_string;
const char *last_string;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	va_list arg_list;

#ifndef NO_STDARGS
	va_start(arg_list, last_string);
#else
	va_start(arg_list);
#endif /* #ifndef NO_STDARGS */

	return(STR_JoinVA(out_string, first_string, middle_string, last_string,
		arg_list));
}
/* ***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *STR_JoinVA(char *out_string, const char *first_string,
	const char *middle_string, const char *last_string, va_list arg_list)
#else
char *STR_JoinVA(out_string, first_string, middle_string, last_string,
	arg_list)
char       *out_string;
const char *first_string;
const char *middle_string;
const char *last_string;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	unsigned int  done_count = 0;
	unsigned int  length;
	char         *tmp_ptr;
	const char   *this_string;

	*out_string = '\0';

	tmp_ptr  = out_string;

	if ((first_string != NULL) && *first_string) {
		strcat(tmp_ptr, first_string);
		tmp_ptr += strlen(first_string);
	}

	length = (middle_string != NULL) ? strlen(middle_string) : 0;

	while ((this_string = va_arg(arg_list, const char *)) != NULL) {
		if (length && done_count) {
			strcat(tmp_ptr, middle_string);
			tmp_ptr += length;
		}
		strcat(tmp_ptr, this_string);
		tmp_ptr += strlen(this_string);
		done_count++;
	}

	if ((last_string != NULL) && *last_string) {
		strcat(out_string, last_string);
		tmp_ptr += strlen(last_string);
	}


	return(out_string);
}
/* ***********************************************************************	*/


