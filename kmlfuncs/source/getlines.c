/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the line numbers of matches.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void KML_GetLineNumbers(KML_CONTROL *control_ptr, const char *in_string)
#else
void KML_GetLineNumbers(control_ptr, in_string)
KML_CONTROL *control_ptr;
const char  *in_string;
#endif /* #ifndef NARGS */
{
	KML_GetLineNumbersFromList(control_ptr->match_count,
		control_ptr->match_list, in_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void KML_GetLineNumbersFromList(unsigned int match_count,
	KML_MATCH *match_list, const char *in_string)
#else
void KML_GetLineNumbersFromList(match_count, match_list, in_string)
unsigned int  match_count;
KML_MATCH    *match_list;
const char   *in_string;
#endif /* #ifndef NARGS */
{
	const char    *in_ptr;
	const char    *line_ptr;
	unsigned long  line_number;
	unsigned int   count_1;
	KML_MATCH     *match_ptr;

	in_ptr      = in_string;
	line_ptr    = in_string;
	line_number = 1L;

	while (*in_ptr) {
		if ((*in_ptr == '\r') || (*in_ptr == '\n')) {
			for (count_1 = 0, match_ptr = match_list; count_1 < match_count;
				count_1++, match_ptr++) {
				if ((match_ptr->ptr >= line_ptr) && (match_ptr->ptr < in_ptr)) {
					match_ptr->start_line = line_number;
					match_ptr->start_char =
						((unsigned int) (match_ptr->ptr - line_ptr)) + 1;
				}
				if (((match_ptr->ptr + match_ptr->length) >= line_ptr) &&
					((match_ptr->ptr + match_ptr->length) <= in_ptr)) {
					match_ptr->end_line = line_number;
					match_ptr->end_char = ((unsigned int)
						((match_ptr->ptr  + match_ptr->length) - line_ptr));
				}
			}
			if ((*in_ptr == '\r') && (*(in_ptr + 1) == '\n'))
				in_ptr++;
			line_ptr = ++in_ptr;
			line_number++;
		}
		else
			in_ptr++;
	}
}
/*	***********************************************************************	*/

