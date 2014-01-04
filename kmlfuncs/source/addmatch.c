/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Adds matched items to an array of 'KML_MATCH'
								structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int KML_AddMatch(KML_CONTROL *control_ptr, const KML_MATCH *match_ptr,
	char *error_text)
#else
int KML_AddMatch(control_ptr, match_ptr, error_text)
KML_CONTROL     *control_ptr;
const KML_MATCH *match_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(KML_AddMatchBasic(match_ptr, &control_ptr->match_count,
		&control_ptr->match_list, &control_ptr->allocated_match_count,
		error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int KML_AddMatchBasic(const KML_MATCH *match_ptr, unsigned int *match_count,
	KML_MATCH **match_list, unsigned int *allocated_match_count,
	char *error_text)
#else
int KML_AddMatchBasic(match_ptr, match_count, match_list,
	allocated_match_count, error_text)
const KML_MATCH  *match_ptr;
unsigned int     *match_count;
KML_MATCH       **match_list;
unsigned int     *allocated_match_count;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = KMLFUNCS_SUCCESS;

	if ((*match_count < *allocated_match_count) || ((return_code =
		KML_AllocateMatchListBasic(*allocated_match_count + 1, match_count,
		match_list, allocated_match_count, error_text)) == KMLFUNCS_SUCCESS))
		(*match_list)[(*match_count)++] = *match_ptr;

	return(return_code);
}
/*	***********************************************************************	*/

