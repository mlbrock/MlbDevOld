/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Module Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Adds a new node to the end of a doubly-linked list.

	Revision History	:	1987-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1987 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Necessary include files . . .															*/
/*	***********************************************************************	*/

#include "dllsi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
DLLS_NODE *DLLS_AddLast(DLLS *dlls_ptr, DLLS_NODE *new_node_ptr)
{
	new_node_ptr->next_ptr = NULL;
	new_node_ptr->dlls_ptr = dlls_ptr;

	if (dlls_ptr->last_ptr != NULL) {
		new_node_ptr->prev_ptr       = dlls_ptr->last_ptr;
		dlls_ptr->last_ptr->next_ptr = new_node_ptr;
	}
	else {
		dlls_ptr->first_ptr    = new_node_ptr;
		new_node_ptr->prev_ptr = NULL;
	}

	dlls_ptr->last_ptr = new_node_ptr;

	dlls_ptr->node_count++;

	return(new_node_ptr);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

#include <strfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int           return_code;
	unsigned int  test_count;
	TEST_DLLS     test_data;
	TEST_NODE    *tmp_node;
	char          error_text[DLLS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'DLLS_AddLast()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------------\n\n");

	DLLS_TEST_Init(&test_data);

	if ((argc > 1) && (atoi(argv[1]) > 0))
		test_count = atoi(argv[1]);
	else
		test_count = 5;

	if ((return_code = DLLS_TEST_AddNodes(&test_data, test_count, DLLS_FALSE,
		error_text)) == DLLS_SUCCESS) {
		if ((return_code = DLLS_TEST_AllocateNode(&test_data, &tmp_node,
			error_text)) == DLLS_SUCCESS) {
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			printf("Before 'DLLS_AddLast()'\n");
			DLLS_TEST_EmitDLLS(&test_data);
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			DLLS_AddLast(&test_data.dlls_data, &tmp_node->node_data);
			printf("\n");
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			printf("After 'DLLS_AddLast()', DLLS node 0x%8p\n",
				&tmp_node->node_data);
			DLLS_TEST_EmitDLLS(&test_data);
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			return_code = DLLS_TEST_Check(&test_data, error_text);
		}
	}

	return_code = DLLS_TEST_Check(&test_data, error_text);

	DLLS_TEST_Destroy(&test_data);

	if (return_code == DLLS_SUCCESS)
		fprintf(stderr, "\n\n*** ALL TESTS PASSED ***\n\n");
	else
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

