/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether an input string matches a
								particular ADF pattern string.

	Revision History	:	1994-06-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_MatchPattern(const char *in_string, const char *pattern_string,
	unsigned int *pattern_end_index)
#else
int ADF_MatchPattern(in_string, pattern_string, pattern_end_index)
const char   *in_string;
const char   *pattern_string;
unsigned int *pattern_end_index;
#endif /* #ifndef NARGS */
{
	int   return_code = ADF_FALSE;
	char *tmp_ptr     = ((char *) in_string);

	if ((tmp_ptr != NULL) && (pattern_string != NULL) &&
		(*tmp_ptr && *pattern_string)) {
		while (*tmp_ptr && *pattern_string) {
			if ((*pattern_string == ' ') && (isspace(*tmp_ptr))) {
				while (isspace(*tmp_ptr))
					tmp_ptr++;
				pattern_string++;
			}
			else if (*pattern_string == ' ') {
				while (*pattern_string == ' ')
					pattern_string++;
			}
			else if (*pattern_string == toupper(*tmp_ptr)) {
				pattern_string++;
				tmp_ptr++;
			}
			else
				break;
		}
		while (*pattern_string == ' ')
			pattern_string++;
		if (!(*pattern_string)) {
			return_code = ADF_TRUE;
			if (pattern_end_index != NULL)
				*pattern_end_index =
					((unsigned int) (tmp_ptr - ((char *) in_string)));
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

