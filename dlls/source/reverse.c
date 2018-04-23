/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Module Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reverses the order of the nodes in a doubly-linked
								list.

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
DLLS *DLLS_Reverse(DLLS *dlls_ptr)
{
	DLLS_NODE *node_ptr;
	DLLS_NODE *tmp_node_ptr;

	if (dlls_ptr->node_count > 1) {
		node_ptr = dlls_ptr->first_ptr;
		while (node_ptr != NULL) {
			tmp_node_ptr       = node_ptr->prev_ptr;
			node_ptr->prev_ptr = node_ptr->next_ptr;
			node_ptr->next_ptr = tmp_node_ptr;
			node_ptr           = node_ptr->prev_ptr;
		}
		tmp_node_ptr        = dlls_ptr->first_ptr;
		dlls_ptr->first_ptr = dlls_ptr->last_ptr;
		dlls_ptr->last_ptr  = tmp_node_ptr;
	}

	return(dlls_ptr);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

#include <strfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int          return_code;
	unsigned int test_count;
	TEST_DLLS    test_data;
	char         error_text[DLLS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'DLLS_Reverse()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------------\n\n");

	DLLS_TEST_Init(&test_data);

	if ((argc > 1) && (atoi(argv[1]) > 0))
		test_count = atoi(argv[1]);
	else
		test_count = 5;

	if ((return_code = DLLS_TEST_AddNodes(&test_data, test_count, DLLS_FALSE,
		error_text)) == DLLS_SUCCESS) {
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		printf("Before 'DLLS_Reverse()'\n");
		DLLS_TEST_EmitDLLS(&test_data);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		DLLS_Reverse(&test_data.dlls_data);
		printf("\n");
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		printf("After 'DLLS_Reverse()'\n");
		DLLS_TEST_EmitDLLS(&test_data);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
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

