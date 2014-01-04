/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Module Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Adds a new node after a specified reference node
								in a doubly-linked list.

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
DLLS_NODE *DLLS_AddNext(DLLS_NODE *ref_node_ptr, DLLS_NODE *new_node_ptr)
{
	if (ref_node_ptr->dlls_ptr->last_ptr == ref_node_ptr)
		DLLS_AddLast(ref_node_ptr->dlls_ptr, new_node_ptr);
	else {
		new_node_ptr->dlls_ptr           = ref_node_ptr->dlls_ptr;
		new_node_ptr->next_ptr           = ref_node_ptr->next_ptr;
		new_node_ptr->prev_ptr           = ref_node_ptr;
		ref_node_ptr->next_ptr->prev_ptr = new_node_ptr;
		ref_node_ptr->next_ptr           = new_node_ptr;
		ref_node_ptr->dlls_ptr->node_count++;
	}

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

	fprintf(stderr, "Test harness for function 'DLLS_AddNext()'\n");
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
			printf("Before 'DLLS_AddNext()'\n");
			DLLS_TEST_EmitDLLS(&test_data);
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			DLLS_AddNext(test_data.dlls_data.first_ptr->next_ptr->next_ptr,
				&tmp_node->node_data);
			printf("\n");
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			printf("After 'DLLS_AddNext()' %s, instance %lu\n",
				"at node index 2 (third node)",
				((TEST_NODE *) test_data.dlls_data.first_ptr->next_ptr->
				next_ptr->data_ptr)->instance);
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

