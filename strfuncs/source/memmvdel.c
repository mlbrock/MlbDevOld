/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Wrapper functions for 'memmove()'-based deletions.

	Revision History	:	1992-03-19 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
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
int memmove_delete_element(unsigned int in_count, void *in_list,
	unsigned int in_size, unsigned int in_position, unsigned int delete_count)
{
	int          return_code;
	unsigned int delete_range;

	if ((in_list == NULL) || (!in_size) || (!delete_count) ||
		((delete_range = (in_position + delete_count)) > in_count))
		return_code = STRFUNCS_FAILURE;
	else {
		if (in_position < (in_count - 1))
			memmove(((char *) in_list) + (in_position * in_size),
				((char *) in_list) + (delete_range * in_size),
				(in_count - in_position) * in_size);
		memset(((char *) in_list) + ((in_count - delete_count) * in_size),
			0, delete_count * in_size);
		return_code = STRFUNCS_SUCCESS;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
int memmove_delete_voidptr(unsigned int in_count, void **in_list,
	unsigned int in_position, unsigned int delete_count)
{
	return(memmove_delete_element(in_count, ((void *) in_list), sizeof(void *),
		in_position, delete_count));
}
/* *********************************************************************** */

/* *********************************************************************** */
int memmove_delete_charptr(unsigned int in_count, char **in_list,
	unsigned int in_position, unsigned int delete_count)
{
	return(memmove_delete_element(in_count, ((void *) in_list), sizeof(char *),
		in_position, delete_count));
}
/* *********************************************************************** */

/* *********************************************************************** */
int memmove_delete_uint(unsigned int in_count, unsigned int *in_list,
	unsigned int in_position, unsigned int delete_count)
{
	return(memmove_delete_element(in_count, ((void *) in_list),
		sizeof(unsigned int), in_position, delete_count));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

#define TEST_DATA_COUNT						5

typedef struct {
	unsigned int  delete_position;
	unsigned int  delete_count;
	char         *new_list[TEST_DATA_COUNT + 1];
} TEST_ITEM;

static char *TEST_DataList[TEST_DATA_COUNT] = {
	"A",
	"B",
	"C",
	"D",
	"E"
};

static TEST_ITEM TEST_DeleteList[]          = {
	{	0,	1,	{	"B",	"C",	"D",	"E"	}	},
	{	1,	1,	{	"A",	"C",	"D",	"E"	}	},
	{	2,	1,	{	"A",	"B",	"D",	"E"	}	},
	{	3,	1,	{	"A",	"B",	"C",	"E"	}	},
	{	4,	1,	{	"A",	"B",	"C",	"D"	}	},

	{	0,	2,	{	"C",	"D",	"E"	}	},
	{	1,	2,	{	"A",	"D",	"E"	}	},
	{	2,	2,	{	"A",	"B",	"E"	}	},
	{	3,	2,	{	"A",	"B",	"C"	}	},

	{	0,	3,	{	"D",	"E"	}	},
	{	1,	3,	{	"A",	"E"	}	},
	{	2,	3,	{	"A",	"B"	}	},

	{	0,	4,	{	"E"	}	},
	{	1,	4,	{	"A"	}	},

	{	0,	5,	{	NULL	}	}
};
static const unsigned int TEST_DeleteCount        =
	sizeof(TEST_DeleteList) / sizeof(TEST_DeleteList[0]);

int main()
{
	int            return_code = STRFUNCS_SUCCESS;
	unsigned int   tmp_count   = 0;
	char         **tmp_list    = NULL;
	unsigned int   count_1;
	unsigned int   count_2;
	int            cmp;
	unsigned int   difference_index;
	unsigned int   test_count;
	char          *test_list[TEST_DATA_COUNT];
	char           error_text[STRFUNCS_MAX_ERROR_TEXT];

	strl_sort(TEST_DATA_COUNT, TEST_DataList);

	for (count_1 = 0; count_1 < TEST_DeleteCount; count_1++) {
		memcpy(test_list, TEST_DataList,
			TEST_DATA_COUNT * sizeof(TEST_DataList[0]));
		if ((return_code = strl_copy(TEST_DATA_COUNT, test_list,
			&tmp_count, &tmp_list)) != STRFUNCS_SUCCESS) {
			strcpy(error_text, "Attempt to copy original list failed.");
			break;
		}
		if ((return_code = strl_remove(&tmp_count, &tmp_list,
			TEST_DeleteList[count_1].delete_position,
			TEST_DeleteList[count_1].delete_count)) != STRFUNCS_SUCCESS) {
			strcpy(error_text, "Attempt to delete from copied list failed.");
			break;
		}
		if (memmove_delete_charptr(TEST_DATA_COUNT, test_list,
			TEST_DeleteList[count_1].delete_position,
			TEST_DeleteList[count_1].delete_count) != STRFUNCS_SUCCESS) {
			sprintf(error_text, "%s %u, position %u, count %u.",
				"Test of 'memmove_delete_charptr()' failed on test index number",
				count_1, TEST_DeleteList[count_1].delete_position,
				TEST_DeleteList[count_1].delete_count);
			return_code = STRFUNCS_FAILURE;
			break;
		}
		test_count = TEST_DATA_COUNT - TEST_DeleteList[count_1].delete_count;
		if ((cmp = strl_CompareLists(tmp_count, tmp_list,
			test_count, test_list, &difference_index)) != 0) {
			STR_EMIT_CharLine('=', 77, NULL, NULL);
			printf("Failure on deletion at position index %u, count %u.\n",
				TEST_DeleteList[count_1].delete_position,
				TEST_DeleteList[count_1].delete_count);
			STR_EMIT_CharLine('=', 77, NULL, NULL);
			printf("Modified original list:\n");
			STR_EMIT_CharLine('-', 77, NULL, NULL);
			for (count_2 = 0; count_2 < tmp_count; count_2++)
				printf("%05u: %s\n", count_2, tmp_list[count_2]);
			STR_EMIT_CharLine('=', 77, NULL, NULL);
			printf("New list:\n");
			STR_EMIT_CharLine('-', 77, NULL, NULL);
			for (count_2 = 0; count_2 < test_count; count_2++)
				printf("%05u: %s\n", count_2, test_list[count_2]);
			STR_EMIT_CharLine('=', 77, NULL, NULL);
			sprintf(error_text, "%s %u, position %u, count %u.",
				"Test of 'memmove_delete_charptr()' failed on test index number",
				count_1, TEST_DeleteList[count_1].delete_position,
				TEST_DeleteList[count_1].delete_count);
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

