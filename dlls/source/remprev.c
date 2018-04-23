/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Module Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes the node before a specified reference node
								in a doubly-linked list.

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

#include "dllsi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
void DLLS_RemovePrevious(DLLS_NODE *ref_node_ptr)
{
	if (ref_node_ptr->prev_ptr != NULL) {
		if (ref_node_ptr->prev_ptr == ref_node_ptr->dlls_ptr->first_ptr)
			DLLS_RemoveFirst(ref_node_ptr->dlls_ptr);
		else {
			ref_node_ptr->prev_ptr           = ref_node_ptr->prev_ptr->prev_ptr;
			ref_node_ptr->prev_ptr->next_ptr = ref_node_ptr;
			ref_node_ptr->dlls_ptr->node_count--;
		}
	}
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
	DLLS_NODE    *tmp_node;
	unsigned int  count_1;
	unsigned int  node_count;
	char          error_text[DLLS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'DLLS_RemovePrevious()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------------------\n\n");

	DLLS_TEST_Init(&test_data);

	if ((argc > 1) && (atoi(argv[1]) > 0))
		test_count = atoi(argv[1]);
	else
		test_count = 5;

	if ((return_code = DLLS_TEST_AddNodes(&test_data, test_count, DLLS_FALSE,
		error_text)) == DLLS_SUCCESS) {
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		printf("Before 'DLLS_RemovePrevious()'\n");
		DLLS_TEST_EmitDLLS(&test_data);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		node_count = test_data.dlls_data.node_count;
		for (count_1 = 0; count_1 < (node_count - 1); count_1++) {
			printf("\n");
			tmp_node = test_data.dlls_data.last_ptr->prev_ptr;
			DLLS_RemovePrevious(test_data.dlls_data.last_ptr);
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			printf("After 'DLLS_RemovePrevious()', number %u of %u, instance %lu\n",
				count_1 + 1, node_count,
				((TEST_NODE *) tmp_node->data_ptr)->instance);
			DLLS_TEST_EmitDLLS(&test_data);
			STR_EMIT_CharLine('*', 78, NULL, NULL);
			free(tmp_node->data_ptr);
			if ((return_code = DLLS_TEST_Check(&test_data, error_text)) !=
				DLLS_SUCCESS)
				break;
		}
	}

	DLLS_TEST_Destroy(&test_data);

	if (return_code == DLLS_SUCCESS)
		fprintf(stderr, "\n\n*** ALL TESTS PASSED ***\n\n");
	else
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

