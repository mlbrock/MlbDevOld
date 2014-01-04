/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Module Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Contains support functions for DLLS testing.

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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <strfuncs.h>

#include "dllsi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DLLS_TEST_AddNodes(TEST_DLLS *dlls_ptr, unsigned int count,
	int random_flag, char *error_text)
{
	int            return_code   = DLLS_SUCCESS;
	unsigned long *instance_list = NULL;
	unsigned int   count_1;
	unsigned int   u_int_1;
	unsigned int   u_int_2;
	unsigned long  tmp_u_long;
	TEST_NODE     *tmp_node;

	if (!count)
		goto EXIT_FUNCTION;
	else if ((return_code = DLLS_TEST_Check(dlls_ptr, error_text)) !=
		DLLS_SUCCESS)
		goto EXIT_FUNCTION;
	else if (random_flag) {
		if ((instance_list =
			((unsigned long *) calloc(count, sizeof(unsigned long)))) != NULL) {
			for (count_1 = 0; count_1 < count; count_1++)
				instance_list[count_1] = ++dlls_ptr->highest_instance;
			for (count_1 = 0; count_1 < count; count_1++) {
				if ((u_int_1 = (rand() % count)) != (u_int_2 = (rand() % count))) {
					tmp_u_long              = instance_list[u_int_1];
					instance_list[u_int_1]  = instance_list[u_int_2];
					instance_list[u_int_2]  = tmp_u_long;
				}
			}
		}
		else {
			STR_AllocMsgList(count, sizeof(unsigned long), error_text,
				"Unable to allocate the temporary list of instance values");
			return_code = DLLS_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	for (count_1 = 0; count_1 < count; count_1++) {
		return_code = (!random_flag) ?
			DLLS_TEST_AllocateNode(dlls_ptr, &tmp_node, error_text) :
			DLLS_TEST_AllocateNodeBasic(instance_list[count_1], &tmp_node,
			error_text);
		DLLS_AddLast(&dlls_ptr->dlls_data, &tmp_node->node_data);
	}

EXIT_FUNCTION:

	if (instance_list != NULL)
		free(instance_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DLLS_TEST_CreateNodesList(TEST_DLLS *dlls_ptr, unsigned int count,
	int random_flag, unsigned int *node_count, TEST_NODE **node_list,
	char *error_text)
{
	int          return_code = DLLS_SUCCESS;
	unsigned int count_1;
	unsigned int u_int_1;
	unsigned int u_int_2;
	TEST_NODE    tmp_node;

	*node_count = 0;
	*node_list  = NULL;

	if (!count)
		;
	else if ((return_code = DLLS_TEST_Check(dlls_ptr, error_text)) !=
		DLLS_SUCCESS)
		;
	else if ((*node_list = ((TEST_NODE *) calloc(count, sizeof(TEST_NODE)))) ==
		NULL) {
		STR_AllocMsgList(count, sizeof(TEST_NODE), error_text,
			"Unable to allocate the list of 'TEST_NODE' structures");
		return_code = DLLS_MEMORY_FAILURE;
	}
	else {
		*node_count = count;
		for (count_1 = 0; count_1 < *node_count; count_1++)
			DLLS_TEST_SetNode(dlls_ptr, *node_list + count_1);
		if (random_flag) {
			for (count_1 = 0; count_1 < *node_count; count_1++) {
				if ((u_int_1 = (rand() % count)) != (u_int_2 = (rand() % count))) {
					tmp_node              = (*node_list)[u_int_1];
					(*node_list)[u_int_1] = (*node_list)[u_int_2];
					(*node_list)[u_int_2]  = tmp_node;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DLLS_TEST_AllocateNode(TEST_DLLS *dlls_ptr, TEST_NODE **node_ptr,
	char *error_text)
{
	return(DLLS_TEST_AllocateNodeBasic(++dlls_ptr->highest_instance, node_ptr,
		error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DLLS_TEST_AllocateNodeBasic(unsigned long instance, TEST_NODE **node_ptr,
	char *error_text)
{
	int return_code = DLLS_SUCCESS;

	if ((*node_ptr = ((TEST_NODE *) calloc(1, sizeof(TEST_NODE)))) != NULL)
		DLLS_TEST_SetNodeBasic(instance, *node_ptr);
	else {
		STR_AllocMsgItem(sizeof(TEST_NODE), error_text,
			"Unable to allocate memory for a 'TEST_NODE' structure");
		return_code = DLLS_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void DLLS_TEST_SetNode(TEST_DLLS *dlls_ptr, TEST_NODE *node_ptr)
{
	DLLS_TEST_SetNodeBasic(++dlls_ptr->highest_instance, node_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void DLLS_TEST_SetNodeBasic(unsigned long instance, TEST_NODE *node_ptr)
{

	node_ptr->node_data.data_ptr = node_ptr;
	node_ptr->instance           = instance;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DLLS_TEST_Check(const TEST_DLLS *dlls_ptr, char *error_text)
{
	int              return_code = DLLS_FAILURE;
	const DLLS_NODE *current_ptr;

	if (dlls_ptr->dlls_data.data_ptr == NULL)
		strcpy(error_text,
			"The 'TEST_DLLS.dlls_data.data_ptr' member is 'NULL'.");
	else if (dlls_ptr != ((const TEST_DLLS *) dlls_ptr->dlls_data.data_ptr))
		sprintf(error_text, "%s (0x%8p) %s (0x%8p).",
			"The 'TEST_DLLS' pointer", dlls_ptr,
			"is not equal to the 'TEST_DLLS.dlls_data.data_ptr' member",
			dlls_ptr->dlls_data.data_ptr);
	else if ((return_code = DLLS_Check(&dlls_ptr->dlls_data, error_text)) ==
		DLLS_SUCCESS) {
		current_ptr = dlls_ptr->dlls_data.first_ptr;
		while (current_ptr != NULL) {
			if (current_ptr !=
				&((TEST_NODE *) current_ptr->data_ptr)->node_data) {
				sprintf(error_text, "%s (0x%8p) %s %s (0x%8p).",
					"The current 'DLLS_NODE' pointer", current_ptr,
					"is not equal to the address of the",
					"'DLLS_NODE.data_ptr->node_data' member",
					&((TEST_NODE *) current_ptr->data_ptr)->node_data);
				return_code = DLLS_FAILURE;
				break;
			}
			current_ptr = current_ptr->next_ptr;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int DLLS_TEST_CompareFunc(void *control_ptr, const DLLS_NODE *node_ptr_1,
	const DLLS_NODE *node_ptr_2, size_t data_length)
{
	return((((TEST_NODE *) node_ptr_1->data_ptr)->instance >
		((TEST_NODE *) node_ptr_2->data_ptr)->instance) ? 1 :
		((((TEST_NODE *) node_ptr_1->data_ptr)->instance <
		((TEST_NODE *) node_ptr_2->data_ptr)->instance) ? -1 : 0));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*	***********************************************************************	*/
void DLLS_TEST_Destroy(TEST_DLLS *dlls_ptr)
{
	DLLS_Destroy(&dlls_ptr->dlls_data);

	dlls_ptr->highest_instance = 0;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void DLLS_TEST_EmitDLLS(const TEST_DLLS *dlls_ptr)
{
	unsigned int     count_1;
	const DLLS_NODE *current_ptr;

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	printf("Test Pointer           : 0x%8p\n", dlls_ptr);
	printf("DLLS Pointer           : 0x%8p\n", &dlls_ptr->dlls_data);
	printf("DLLS Count             : %10u\n", dlls_ptr->dlls_data.node_count);
	printf("DLLS First Node Pointer: 0x%8p\n", dlls_ptr->dlls_data.first_ptr);
	printf("DLLS Last Node Pointer : 0x%8p\n", dlls_ptr->dlls_data.last_ptr);

	STR_EMIT_CharLine('-', 78, NULL, NULL);

	printf("%-8.8s %8.8s %-10.10s %-10.10s %-10.10s %-10.10s %-10.10s %-5.5s\n",
		"Index",
		"Instance",
		"DLLS Ptr",
		"Data Ptr",
		"Node Ptr",
		"Prev Ptr",
		"Next Ptr",
		"OK ?");

	STR_EMIT_CharSpace('-',  8, NULL, NULL);
	STR_EMIT_CharSpace('-',  8, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharLine( '-',  5, NULL, NULL);

	count_1     = 0;
	current_ptr = dlls_ptr->dlls_data.first_ptr;
	while (current_ptr != NULL) {
		printf("%8u ", count_1++);
		DLLS_TEST_EmitNode(((const TEST_NODE *) current_ptr->data_ptr));
		current_ptr = current_ptr->next_ptr;
	}

	STR_EMIT_CharSpace('-',  8, NULL, NULL);
	STR_EMIT_CharSpace('-',  8, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharLine( '-',  5, NULL, NULL);

	STR_EMIT_CharLine('=', 78, NULL, NULL);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void DLLS_TEST_EmitNode(const TEST_NODE *node_ptr)
{
	printf("%8lu 0x%8p 0x%8p 0x%8p 0x%8p 0x%8p %s\n",
		node_ptr->instance,
		node_ptr->node_data.dlls_ptr,
		node_ptr->node_data.data_ptr,
		&node_ptr->node_data,
		node_ptr->node_data.prev_ptr,
		node_ptr->node_data.next_ptr,
		(((TEST_NODE *) node_ptr->node_data.data_ptr) == node_ptr) ? "TRUE" :
		"FALSE");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DLLS_TEST_GetList(DLLS *dlls_ptr, int random_flag,
	unsigned int *out_count, DLLS_NODE ***out_list, char *error_text)
{
	int           return_code;
	unsigned int  count_1;
	unsigned int  u_int_1;
	unsigned int  u_int_2;
	DLLS_NODE    *node_ptr;

	if (((return_code = DLLS_GetList(dlls_ptr, out_count, out_list,
		error_text)) == DLLS_SUCCESS) && random_flag && (*out_count > 1)) {
		for (count_1 = 0; count_1 < *out_count; count_1++) {
			if ((u_int_1 = (rand() % *out_count)) !=
				(u_int_2 = (rand() % *out_count))) {
				node_ptr              = (*out_list)[u_int_1];
				(*out_list)[u_int_1]  = (*out_list)[u_int_2];
				(*out_list)[u_int_2]  = node_ptr;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void DLLS_TEST_Init(TEST_DLLS *dlls_ptr)
{
	memset(dlls_ptr, '\0', sizeof(*dlls_ptr));

	DLLS_Create(&dlls_ptr->dlls_data, free);

	dlls_ptr->dlls_data.data_ptr = dlls_ptr;
	dlls_ptr->highest_instance   = 0;
}
/*	***********************************************************************	*/

