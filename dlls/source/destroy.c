/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Module Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Destroys a doubly-linked list.

	Revision History	:	1987-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1987 - 2015.
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

#include "dllsi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
void DLLS_Destroy(DLLS *dlls_ptr)
{
	DLLS_NODE *next_ptr;
	DLLS_NODE *node_ptr;

	if (dlls_ptr->free_func != NULL) {
		node_ptr = dlls_ptr->first_ptr;
		while (node_ptr != NULL) {
			next_ptr = node_ptr->next_ptr;
			if ((dlls_ptr->free_func != NULL) && (node_ptr->data_ptr != NULL))
				(*dlls_ptr->free_func)(node_ptr->data_ptr);
			node_ptr = next_ptr;
		}
	}

	DLLS_Init(dlls_ptr);
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
	unsigned int node_count;
	char         error_text[DLLS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'DLLS_Destroy()'\n");
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
		printf("Before 'DLLS_Destroy()'\n");
		DLLS_TEST_EmitDLLS(&test_data);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		node_count = test_data.dlls_data.node_count;
		printf("\n");
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		DLLS_Destroy(&test_data.dlls_data);
		printf("After 'DLLS_Destroy()'\n");
		DLLS_TEST_EmitDLLS(&test_data);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
	}

	if (return_code == DLLS_SUCCESS)
		fprintf(stderr, "\n\n*** ALL TESTS PASSED ***\n\n");
	else
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

