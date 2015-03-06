/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Module Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sorts the nodes in a doubly-linked list.

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

#include <strfuncs.h>

#include "dllsi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DLLS_Sort(DLLS *dlls_ptr, DLLS_CompareFunc compare_func,
	void *control_ptr, size_t data_length, char *error_text)
{
	int            return_code;
	unsigned int   tmp_count;
	DLLS_NODE    **tmp_list;
	unsigned int   count_1;

	if (dlls_ptr->node_count < 2)
		return_code = DLLS_SUCCESS;
	else if ((return_code = DLLS_GetList(dlls_ptr, &tmp_count, &tmp_list,
		error_text)) == DLLS_SUCCESS) {
		STR_LIST_qsort(control_ptr, tmp_count, ((void **) tmp_list), data_length,
			STR_CMP_FUNC_CAST(compare_func));
		for (count_1 = 1; count_1 < (tmp_count - 1); count_1++) {
			tmp_list[count_1]->prev_ptr = tmp_list[count_1 - 1];
			tmp_list[count_1]->next_ptr = tmp_list[count_1 + 1];
		}
		tmp_list[0]->prev_ptr             = NULL;
		tmp_list[0]->next_ptr             = tmp_list[1];
		tmp_list[tmp_count - 1]->prev_ptr = tmp_list[tmp_count - 2];
		tmp_list[tmp_count - 1]->next_ptr = NULL;
		dlls_ptr->first_ptr               = tmp_list[0];
		dlls_ptr->last_ptr                = tmp_list[tmp_count - 1];
		free(tmp_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

#include <strfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int          return_code;
	unsigned int test_count;
	TEST_DLLS    test_data;
	char         error_text[DLLS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'DLLS_Sort()'\n");
	fprintf(stderr, "---- ------- --- -------- -------------\n\n");

	DLLS_TEST_Init(&test_data);

	if ((argc > 1) && (atoi(argv[1]) > 0))
		test_count = atoi(argv[1]);
	else
		test_count = 5;

	if ((return_code = DLLS_TEST_AddNodes(&test_data, test_count, DLLS_TRUE,
		error_text)) == DLLS_SUCCESS) {
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		printf("Before 'DLLS_Sort()'\n");
		DLLS_TEST_EmitDLLS(&test_data);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		if ((return_code = DLLS_Sort(&test_data.dlls_data,
			DLLS_TEST_CompareFunc, NULL, 0, error_text)) != DLLS_SUCCESS)
			goto EXIT_FUNCTION;
		printf("\n");
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		printf("After 'DLLS_Sort()'\n");
		DLLS_TEST_EmitDLLS(&test_data);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
	}

	return_code = DLLS_TEST_Check(&test_data, error_text);

EXIT_FUNCTION:

	DLLS_TEST_Destroy(&test_data);

	if (return_code == DLLS_SUCCESS)
		fprintf(stderr, "\n\n*** ALL TESTS PASSED ***\n\n");
	else
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

