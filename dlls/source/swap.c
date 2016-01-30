/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Module Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Swaps the relative positions of two nodes in a
								doubly-linked list.

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

#include "dllsi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
void DLLS_Swap(DLLS_NODE *node_ptr_1, DLLS_NODE *node_ptr_2)
{
	DLLS_NODE tmp_node_1;
	DLLS_NODE tmp_node_2;

	if ((node_ptr_1 != node_ptr_2) && (node_ptr_1 != NULL) &&
		(node_ptr_2 != NULL)) {
		tmp_node_1 = *node_ptr_1;
		tmp_node_2 = *node_ptr_2;
		DLLS_RemoveSelf(node_ptr_1);
		DLLS_RemoveSelf(node_ptr_2);
		if ((tmp_node_1.prev_ptr == NULL) ||
			(tmp_node_1.prev_ptr == node_ptr_2))
			DLLS_AddFirst(tmp_node_1.dlls_ptr, node_ptr_2);
		else
			DLLS_AddNext(tmp_node_1.prev_ptr, node_ptr_2);
		if ((tmp_node_2.prev_ptr == NULL) ||
			(tmp_node_2.prev_ptr == node_ptr_1))
			DLLS_AddFirst(tmp_node_2.dlls_ptr, node_ptr_1);
		else
			DLLS_AddNext(tmp_node_2.prev_ptr, node_ptr_1);
	}
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

#include <strfuncs.h>

#define TEST_MAX_COUNT						100
#define TEST_LOOP_COUNT						200

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code;
	unsigned int  node_count_1 = 0;
	TEST_NODE    *node_list_1  = NULL;
	unsigned int  node_count_2 = 0;
	TEST_NODE    *node_list_2  = NULL;
	unsigned int  count_1;
	unsigned int  count_2;
	TEST_DLLS     test_data_1;
	TEST_DLLS     test_data_2;
	unsigned int  u_int_1;
	unsigned int  u_int_2;
	TEST_NODE    *node_ptr_1;
	TEST_NODE    *node_ptr_2;
	char          error_text[DLLS_MAX_ERROR_TEXT];
	char          tmp_error_text[DLLS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'DLLS_Swap()'\n");
	fprintf(stderr, "---- ------- --- -------- -------------\n\n");

	DLLS_TEST_Init(&test_data_1);
	DLLS_TEST_Init(&test_data_2);

	/*	*****************************************************************
		*****************************************************************
		Test of swaps within a single DLLS . . .
		*****************************************************************	*/
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Creating node data lists.\n");
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	if ((return_code = DLLS_TEST_CreateNodesList(&test_data_1, TEST_MAX_COUNT,
		DLLS_FALSE, &node_count_1, &node_list_1, error_text)) != DLLS_SUCCESS)
		goto EXIT_FUNCTION;
	for (count_1 = 0; count_1 < TEST_MAX_COUNT; count_1++)
		DLLS_AddLast(&test_data_1.dlls_data, &node_list_1[count_1].node_data);
	if ((return_code = DLLS_TEST_Check(&test_data_1, error_text)) !=
		DLLS_SUCCESS)
		goto EXIT_FUNCTION;
	printf("Node data list number one complete.\n");
	if ((return_code = DLLS_TEST_CreateNodesList(&test_data_2, TEST_MAX_COUNT,
		DLLS_FALSE, &node_count_2, &node_list_2, error_text)) != DLLS_SUCCESS)
		goto EXIT_FUNCTION;
	for (count_1 = 0; count_1 < TEST_MAX_COUNT; count_1++)
		DLLS_AddLast(&test_data_2.dlls_data, &node_list_2[count_1].node_data);
	if ((return_code = DLLS_TEST_Check(&test_data_2, error_text)) !=
		DLLS_SUCCESS)
		goto EXIT_FUNCTION;
	printf("Node data list number two complete.\n");
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Swap within a single DLLS.\n");
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	for (count_1 = 1; count_1 <= TEST_MAX_COUNT; count_1++) {
		for (count_2 = 0; count_2 < TEST_LOOP_COUNT; count_2++) {
			u_int_1    = rand() % count_1;
			u_int_2    = rand() % count_1;
			node_ptr_1 = node_list_1 + u_int_1;
			node_ptr_2 = node_list_1 + u_int_2;
			DLLS_Swap(&node_ptr_1->node_data, &node_ptr_2->node_data);
			if ((return_code = DLLS_TEST_Check(&test_data_1, tmp_error_text)) !=
				DLLS_SUCCESS) {
				sprintf(error_text,
					"%s %u, %u (pointers 0x%p/0x%p, 0x%p/0x%p): %s",
					"Swap test single DLLS iteration", count_1, count_2,
					node_ptr_1, &node_ptr_1->node_data,
					node_ptr_2, &node_ptr_2->node_data, tmp_error_text);
				goto EXIT_FUNCTION;
			}
		}
	}
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("\n");
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Test of swaps across multiple DLLS . . .
		*****************************************************************	*/
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Swap across multiple DLLS.\n");
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	for (count_1 = 1; count_1 <= TEST_MAX_COUNT; count_1++) {
		for (count_2 = 0; count_2 < TEST_LOOP_COUNT; count_2++) {
			u_int_1    = rand() % count_1;
			u_int_2    = rand() % count_1;
			node_ptr_1 = node_list_1 + u_int_1;
			node_ptr_2 = node_list_2 + u_int_2;
			DLLS_Swap(&node_ptr_1->node_data, &node_ptr_2->node_data);
			if ((return_code = DLLS_TEST_Check(&test_data_1, tmp_error_text)) !=
				DLLS_SUCCESS) {
				sprintf(error_text,
					"%s %u, %u (pointers 0x%p/0x%p, 0x%p/0x%p): %s",
					"Swap test multiple DLLS iteration", count_1, count_2,
					node_ptr_1, &node_ptr_1->node_data,
					node_ptr_2, &node_ptr_2->node_data, tmp_error_text);
				goto EXIT_FUNCTION;
			}
		}
	}
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("\n");
	/*	*****************************************************************	*/

	if ((return_code = DLLS_TEST_Check(&test_data_1, error_text)) ==
		DLLS_SUCCESS)
		return_code = DLLS_TEST_Check(&test_data_2, error_text);

EXIT_FUNCTION:

	DLLS_TEST_Init(&test_data_1);
	DLLS_TEST_Init(&test_data_2);

	if (node_list_1 != NULL)
		free(node_list_1);

	if (node_list_2 != NULL)
		free(node_list_2);

	if (return_code != DLLS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

