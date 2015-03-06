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
void KML_ConcatenateKeywords(KML_CONTROL *control_ptr)
#else
void KML_ConcatenateKeywords(control_ptr)
KML_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	unsigned int  count_2;
	const char   *tmp_ptr;

	for (count_1 = 0; count_1 < control_ptr->match_count; ) {
		if ((control_ptr->match_list[count_1].type == KML_TYPE_KEYWORD) &&
			((count_1 + 1) < control_ptr->match_count) &&
			(control_ptr->match_list[count_1 + 1].type == KML_TYPE_KEYWORD)) {
			tmp_ptr = control_ptr->match_list[count_1].ptr +
				control_ptr->match_list[count_1].length;
			while ((tmp_ptr < control_ptr->match_list[count_1 + 1].ptr) &&
				(isspace(*tmp_ptr) || iscntrl(*tmp_ptr)))
				tmp_ptr++;
			if (tmp_ptr == control_ptr->match_list[count_1 + 1].ptr) {
				control_ptr->match_list[count_1].length = ((unsigned int)
					(control_ptr->match_list[count_1 + 1].ptr -
					control_ptr->match_list[count_1].ptr)) +
					control_ptr->match_list[count_1 + 1].length;
				for (count_2 = (count_1 + 1);
					count_2 < (control_ptr->match_count - 1); count_2++)
					control_ptr->match_list[count_2] =
						control_ptr->match_list[count_2 + 1];
				control_ptr->match_count--;
				KML_INIT_Match(control_ptr->match_list +
					control_ptr->match_count);
			}
			else
				count_1++;
		}
		else
			count_1++;
	}
}
/*	***********************************************************************	*/

