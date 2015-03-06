/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Wrapper functions for 'memmove()'-based insertions.

	Revision History	:	1992-03-19 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
int memmove_insert_element(unsigned int in_count, void *in_list,
	unsigned int in_size, unsigned int in_position, const void *in_element)
{
	int   return_code;
	char *tmp_ptr;

	if ((in_list == NULL) || (!in_size) || (in_position > in_count) ||
		(in_element == NULL))
		return_code = STRFUNCS_FAILURE;
	else {
		tmp_ptr = ((char *) in_list) + (in_position * in_size);
		if (in_position < in_count)
			memmove(((char *) in_list) + ((in_position + 1) * in_size),
				tmp_ptr, (in_count - in_position) * in_size);
		memcpy(tmp_ptr, in_element, in_size);
		return_code = STRFUNCS_SUCCESS;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
int memmove_insert_voidptr(unsigned int in_count, void **in_list,
	unsigned int in_position, const void *in_element)
{
	return(memmove_insert_element(in_count, ((void *) in_list), sizeof(void *),
		in_position, &in_element));
}
/* *********************************************************************** */

/* *********************************************************************** */
int memmove_insert_charptr(unsigned int in_count, char **in_list,
	unsigned int in_position, const char *in_element)
{
	return(memmove_insert_element(in_count, ((void *) in_list), sizeof(char *),
		in_position, &in_element));
}
/* *********************************************************************** */

/* *********************************************************************** */
int memmove_insert_uint(unsigned int in_count, unsigned int *in_list,
	unsigned int in_position, unsigned int in_element)
{
	return(memmove_insert_element(in_count, ((void *) in_list),
		sizeof(unsigned int), in_position, &in_element));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

#define TEST_DATA_COUNT						3

typedef struct {
	unsigned int  insert_position;
	char         *insert_data;
	char         *new_list[TEST_DATA_COUNT + 1];
} TEST_ITEM;

static char *TEST_DataList[TEST_DATA_COUNT] = {
	"B",
	"D",
	"E"
};

static TEST_ITEM TEST_InsertList[]          = {
	{	0,	"A",	{	"A",	"B",	"D",	"E"	}	},
	{	1,	"C",	{	"B",	"C",	"D",	"E"	}	},
	{	3,	"F",	{	"B",	"D",	"E",	"F"	}	}
};
static const unsigned int TEST_InsertCount        =
	sizeof(TEST_InsertList) / sizeof(TEST_InsertList[0]);

int main()
{
	int            return_code = STRFUNCS_SUCCESS;
	unsigned int   tmp_count   = 0;
	char         **tmp_list    = NULL;
	unsigned int   count_1;
	unsigned int   count_2;
	int            cmp;
	unsigned int   difference_index;
	char          *test_list[TEST_DATA_COUNT + 1];
	char           error_text[STRFUNCS_MAX_ERROR_TEXT];

	strl_sort(TEST_DATA_COUNT, TEST_DataList);

	for (count_1 = 0; count_1 < TEST_InsertCount; count_1++) {
		memcpy(test_list, TEST_DataList,
			TEST_DATA_COUNT * sizeof(TEST_DataList[0]));
		if ((return_code = strl_copy(TEST_DATA_COUNT, test_list,
			&tmp_count, &tmp_list)) != STRFUNCS_SUCCESS) {
			strcpy(error_text, "Attempt to copy original list failed.");
			break;
		}
		if ((return_code = strl_insert(&tmp_count, &tmp_list,
			TEST_InsertList[count_1].insert_data,
			TEST_InsertList[count_1].insert_position)) !=
			STRFUNCS_SUCCESS) {
			strcpy(error_text, "Attempt to insert into copied list failed.");
			break;
		}
		if (memmove_insert_charptr(TEST_DATA_COUNT, test_list,
			TEST_InsertList[count_1].insert_position,
			TEST_InsertList[count_1].insert_data) != STRFUNCS_SUCCESS) {
			sprintf(error_text, "%s on test index number %u ('%s').",
				"Test of 'memmove_insert_charptr()' failed", count_1,
				TEST_InsertList[count_1].insert_data);
			return_code = STRFUNCS_FAILURE;
			break;
		}
		if ((cmp = strl_CompareLists(tmp_count, tmp_list,
			TEST_DATA_COUNT + 1, test_list, &difference_index)) != 0) {
			STR_EMIT_CharLine('=', 77, NULL, NULL);
			printf("Failure on insert of '%s' at position index %u.\n",
				TEST_InsertList[count_1].insert_data,
				TEST_InsertList[count_1].insert_position);
			STR_EMIT_CharLine('=', 77, NULL, NULL);
			printf("Modified original list:\n");
			STR_EMIT_CharLine('-', 77, NULL, NULL);
			for (count_2 = 0; count_2 < tmp_count; count_2++)
				printf("%05u: %s\n", count_2, tmp_list[count_2]);
			STR_EMIT_CharLine('=', 77, NULL, NULL);
			printf("New list:\n");
			STR_EMIT_CharLine('-', 77, NULL, NULL);
			for (count_2 = 0; count_2 < (TEST_DATA_COUNT + 1); count_2++)
				printf("%05u: %s\n", count_2, test_list[count_2]);
			STR_EMIT_CharLine('=', 77, NULL, NULL);
			sprintf(error_text, "%s on test index number %u ('%s').",
				"Test of 'memmove_insert_charptr()' failed", count_1,
				TEST_InsertList[count_1].insert_data);
			return_code = STRFUNCS_FAILURE;
			break;
		}
		strl_remove_all(&tmp_count, &tmp_list);
	}

	strl_remove_all(&tmp_count, &tmp_list);

	if (return_code != STRFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

