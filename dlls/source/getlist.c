/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Module Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the first node in a doubly-linked list.

	Revision History	:	1987-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1987 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Necessary include files . . .															*/
/*	***********************************************************************	*/

#include <stdlib.h>

#include <strfuncs.h>

#include "dllsi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DLLS_GetList(DLLS *dlls_ptr, unsigned int *out_count,
	DLLS_NODE ***out_list, char *error_text)
{
	return(DLLS_GetListBasic(dlls_ptr->first_ptr, 0, DLLS_FALSE, out_count,
		out_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DLLS_GetListBasic(DLLS_NODE *ref_node_ptr, unsigned int max_count,
	int reverse_flag, unsigned int *out_count, DLLS_NODE ***out_list,
	char *error_text)
{
	int          return_code = DLLS_SUCCESS;
	unsigned int total_count;

	*out_count = 0;
	*out_list  = NULL;

	if ((ref_node_ptr != NULL) &&
		((total_count = ref_node_ptr->dlls_ptr->node_count) > 0)) {
		max_count = (max_count) ? max_count : total_count;
		if ((*out_list = ((DLLS_NODE **)
			calloc(max_count, sizeof(DLLS_NODE *)))) != NULL) {
			while ((ref_node_ptr != NULL) && (*out_count < max_count)) {
				(*out_list)[(*out_count)++] = ref_node_ptr;
				ref_node_ptr = ref_node_ptr->next_ptr;
			}
			if (*out_count < max_count)
				*out_list = ((DLLS_NODE **) realloc(*out_list,
					*out_count * sizeof(DLLS_NODE *)));
			if (reverse_flag)
				STR_LIST_reverse(*out_count, ((void **) *out_list));
			return_code = DLLS_SUCCESS;
		}
		else {
			if (error_text != NULL)
				STR_AllocMsgList(max_count, sizeof(DLLS_NODE *), error_text,
					"Unable to allocate the list of 'DLLS_NODE' pointers");
			return_code = DLLS_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

