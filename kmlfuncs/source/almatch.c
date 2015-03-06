/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages allocation of the array of 'KML_MATCH'
								structures.

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

#include <memory.h>
#include <stdlib.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int KML_AllocateMatchList(KML_CONTROL *control_ptr, unsigned int add_count,
	char *error_text)
#else
int KML_AllocateMatchList(control_ptr, add_count, error_text)
KML_CONTROL  *control_ptr;
unsigned int  add_count;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code;
	unsigned int has_count;

	if ((!add_count) && (!control_ptr->allocated_match_count))
		return_code = KML_AllocateMatchListBasic(KML_MATCH_ALLOCATION_GRAN,
			&control_ptr->match_count, &control_ptr->match_list,
			&control_ptr->allocated_match_count, error_text);
	else if ((has_count =
		(control_ptr->allocated_match_count - control_ptr->match_count)) >=
		add_count)
		return_code = KMLFUNCS_SUCCESS;
	else
		return_code =
			KML_AllocateMatchListBasic(control_ptr->match_count + has_count,
			&control_ptr->match_count, &control_ptr->match_list,
			&control_ptr->allocated_match_count, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int KML_AllocateMatchListBasic(unsigned int alloc_request,
	unsigned int *match_count, KML_MATCH **match_list,
	unsigned int *allocated_match_count, char *error_text)
#else
int KML_AllocateMatchListBasic(alloc_request, match_count, match_list, 
	allocated_match_count, error_text)
unsigned int   alloc_request;
unsigned int  *match_count;
KML_MATCH    **match_list;
unsigned int  *allocated_match_count;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int        return_code = KMLFUNCS_SUCCESS;
	KML_MATCH *tmp_list;
							  
	alloc_request = (alloc_request) ? alloc_request : 1;
	alloc_request = ((alloc_request / KML_MATCH_ALLOCATION_GRAN) +
		((alloc_request % KML_MATCH_ALLOCATION_GRAN) ? 1 : 0)) *
		KML_MATCH_ALLOCATION_GRAN;

	if (alloc_request > *allocated_match_count) {
		if ((tmp_list = ((*match_list == NULL) ?
			((KML_MATCH *) calloc(alloc_request, sizeof(KML_MATCH))) :
			((KML_MATCH *) realloc(*match_list, alloc_request *
			sizeof(KML_MATCH))))) == NULL) {
			STR_AllocMsgList(alloc_request, sizeof(KML_MATCH), error_text,
				"Unable to %sallocate the KML match list",
				(*match_list == NULL) ? "" : "re-");
			return_code = KMLFUNCS_MEMORY_FAILURE;
		}
		else {
			KML_INIT_MatchList(alloc_request - *allocated_match_count,
				tmp_list + *allocated_match_count);
			*match_list            = tmp_list;
			*allocated_match_count = alloc_request;
			*match_count           = (*match_count <= *allocated_match_count) ?
				*match_count : *allocated_match_count;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

