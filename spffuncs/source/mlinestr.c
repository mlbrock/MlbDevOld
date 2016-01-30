/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads an ADF domain definition file.

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

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_FixMultiLineString(SPF_PARSE *parse_ptr, char *error_text)
#else
int SPF_FixMultiLineString(parse_ptr, error_text)
SPF_PARSE *parse_ptr;
char      *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code = SPF_SUCCESS;
	char *tmp_ptr;

	if (parse_ptr->length && ((tmp_ptr = strnchr(parse_ptr->text, '\\',
		parse_ptr->length)) != NULL) && ((*tmp_ptr + 1) == '\n') &&
		(parse_ptr->flags || ((return_code = SPF_ALLC_Parse(parse_ptr,
		error_text)) == SPF_SUCCESS))) {
		tmp_ptr = parse_ptr->text;
		while (*tmp_ptr) {
			if ((*tmp_ptr == '\\') && (*(tmp_ptr + 1))) {
				if (*(tmp_ptr + 1) == '\n') {
					strdele(tmp_ptr, 0, 2);
					parse_ptr->length -= 2;
				}
				else
					tmp_ptr += 2;
			}
			else
				tmp_ptr++;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

