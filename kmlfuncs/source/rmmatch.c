/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes matches of the specified types from a
								''KML_CONTROL'' structure.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
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
void KML_RemoveMatchTypes(KML_CONTROL *control_ptr, unsigned int remove_mask)
#else
void KML_RemoveMatchTypes(control_ptr, remove_mask)
KML_CONTROL  *control_ptr;
unsigned int  remove_mask;
#endif /* #ifndef NARGS */
{
	unsigned int remove_count = 0;
	unsigned int count_1;         
	unsigned int count_2;

	for (count_1 = 0; count_1 < control_ptr->match_count; count_1++)
		remove_count += (control_ptr->match_list[count_1].type & remove_mask) ?
			1 : 0;

	for (count_1 = 0; (count_1 < control_ptr->match_count) && remove_count; ) {
		if (control_ptr->match_list[count_1].type & remove_mask) {
			for (count_2 = count_1; count_2 < (control_ptr->match_count - 1);
				count_2++)
				control_ptr->match_list[count_2] =
					control_ptr->match_list[count_2 + 1];
			remove_count--;
			control_ptr->match_count--;
			KML_INIT_Match(control_ptr->match_list + control_ptr->match_count);
		}
		else
			count_1++;
	}
}
/*	***********************************************************************	*/

