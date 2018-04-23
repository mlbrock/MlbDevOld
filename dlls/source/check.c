/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Module Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a doubly-linked list for consistency.

	Revision History	:	1987-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1987 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Necessary include files . . .															*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <string.h>

#include <strfuncs.h>

#ifdef _Windows
# ifdef _MSC_VER
#  pragma warning(push)
#  if _MSC_VER >= 1400
#    pragma warning(disable:4820)
#  endif /* #  if _MSC_VER >= 1400 */
#  if _MSC_VER >= 1300
#   pragma warning(disable:4255 4668)
#   include <windows.h>
#  elif _MSC_VER >= 1200
#   pragma warning(disable:4115)
#   include <windows.h>
#  else
#   pragma warning(disable:4115 4201 4214 4514)
#   include <windows.h>
# 	endif /* #  if _MSC_VER >= 1200 */
#  pragma warning(pop)
# else
#  include <windows.h>
# endif /* # ifdef _MSC_VER */
#endif /* #ifdef _Windows */

#include "dllsi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DLLS_Check(const DLLS *dlls_ptr, char *error_text)
{
	int              return_code  = DLLS_SUCCESS;
	unsigned int     node_count   = 0;
	const DLLS_NODE *old_node_ptr = NULL;
	const DLLS_NODE *node_ptr;

	if (dlls_ptr == NULL) {
		if (error_text != NULL)
			strcpy(error_text, "DLLS pointer is 'NULL'.");
		return_code = DLLS_FAILURE;
	}
#ifdef _Windows
	else if (IsBadWritePtr(((void *) dlls_ptr), sizeof(*dlls_ptr))) {
		if (error_text != NULL)
			strcat(val2str_ptr0_cat(dlls_ptr,
				strcpy(error_text, "DLLS pointer (")), ") is invalid.");
		return_code = DLLS_FAILURE;
	}
#endif /* #ifdef _Windows */
	else {
		node_count = 0;
		node_ptr   = dlls_ptr->first_ptr;
		while (node_ptr != NULL) {
#ifdef _Windows
			if (IsBadWritePtr(((void *) node_ptr), sizeof(*node_ptr))) {
				if (error_text != NULL)
					strcat(val2str_ptr0_cat(node_ptr,
						strcpy(error_text, "DLLS node pointer (")), ") is invalid.");
				return_code = DLLS_FAILURE;
				break;
			}
#endif /* #ifdef _Windows */
			if (node_ptr->data_ptr == NULL) {
				if (error_text != NULL)
					strcat(val2str_ptr0_cat(node_ptr,
						strcpy(error_text,
						"The 'data_ptr' member of the DLLS node at address ")),
						" is 'NULL'.");
				return_code = DLLS_FAILURE;
				break;
			}
#ifdef _Windows
			if (IsBadWritePtr(((void *) node_ptr->data_ptr), 1)) {
				if (error_text != NULL)
					strcat(val2str_ptr0_cat(node_ptr->data_ptr,
						strcat(val2str_ptr0_cat(node_ptr,
						strcpy(error_text,
						"The 'data_ptr' member of the DLLS node at address ")),
						" is equal to ")), ", which is invalid.");
				return_code = DLLS_FAILURE;
				break;
			}
#endif /* #ifdef _Windows */
			if (node_ptr->dlls_ptr != dlls_ptr) {
				if (error_text != NULL)
					chrcat(val2str_ptr0_cat(dlls_ptr,
						strcat(val2str_ptr0_cat(node_ptr->dlls_ptr,
						strcat(val2str_ptr0_cat(node_ptr, strcpy(error_text,
						"The 'dlls_ptr' member of the node at address ")),
						" has a value (")),
						" ) but the expected value is ")), '.');
				return_code = DLLS_FAILURE;
				break;
			}
			if (node_ptr->prev_ptr != old_node_ptr) {
				if (error_text != NULL)
					chrcat(val2str_ptr0_cat(old_node_ptr,
						strcat(val2str_ptr0_cat(node_ptr->prev_ptr,
						strcat(val2str_ptr0_cat(node_ptr, strcpy(error_text,
						"The 'prev_ptr' member of the node at address ")),
						" has a value (")),
						") where the expected value is ")), '.');
				return_code = DLLS_FAILURE;
				break;
			}
			if (node_ptr->next_ptr == node_ptr) {
				if (error_text != NULL)
  					strcat(val2str_ptr0_cat(node_ptr, strcpy(error_text,
						"The 'next_ptr' member of the node at address ")),
						" is equal to the node pointer.");
				return_code = DLLS_FAILURE;
				break;
			}
			node_count++;
			old_node_ptr = node_ptr;
			node_ptr     = node_ptr->next_ptr;
		}
		if ((return_code == DLLS_SUCCESS) &&
			(dlls_ptr->node_count != node_count)) {
			if (error_text != NULL)
				sprintf(error_text, "%s 'node_count' member (%u) %s %s (%u).",
					"The node count specified within the 'DLLS' structure",
					dlls_ptr->node_count, "is not the same as that calculated",
					"by traversing all DLLS nodes", node_count);
			return_code = DLLS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

