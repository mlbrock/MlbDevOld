/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether an input matches one of a list of
								ADF pattern strings.

	Revision History	:	1994-06-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_MatchPatternPtr(const char *in_string, const ADF_PATTERN *pattern_ptr,
	unsigned int *pattern_end_index)
#else
int ADF_MatchPatternPtr(in_string, pattern_ptr, pattern_end_index)
const char        *in_string;
const ADF_PATTERN *pattern_ptr;
unsigned int      *pattern_end_index;
#endif /* #ifndef NARGS */
{
	return(((pattern_ptr->pattern_optimization == NULL) ||
		(stristr(in_string, pattern_ptr->pattern_optimization) != NULL)) ?
		ADF_MatchPatternList(in_string, pattern_ptr->pattern_count,
		pattern_ptr->pattern_list, pattern_end_index) : ADF_FALSE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_MatchPatternList(const char *in_string, unsigned int pattern_count,
	char **pattern_list, unsigned int *pattern_end_index)
#else
int ADF_MatchPatternList(in_string, pattern_count, pattern_list,
	pattern_end_index)
const char    *in_string;
unsigned int   pattern_count;
char **pattern_list;
unsigned int  *pattern_end_index;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_FALSE;
	unsigned int count_1;

	for (count_1 = 0; count_1 < pattern_count; count_1++) {
		if ((return_code = ADF_MatchPattern(in_string, pattern_list[count_1],
			pattern_end_index)) == ADF_TRUE)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

