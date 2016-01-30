/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a list to an array.

	Revision History	:	1991-08-22 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <memory.h>
#include <stdlib.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  meml_to_mema

   SYNOPSIS    :  return_code = meml_to_mema(in_data_count, in_data_list,
							data_length, out_data_count, out_data_array);

						int            return_code;

						unsigned int   in_data_count;

						void         **in_data_list;

						size_t         data_length;

						unsigned int  *out_data_count;

						void         **out_data_array;

   DESCRIPTION :  Converts the records in the list ``in_data_list`` to the
						list ``out_data_array``. That is, a ''void **'' list of
						pointers to memory is converted to a ''void *'' array.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_data_count`` is the number of records in the
						source list ``in_data_list``.

						(.) ``in_data_list`` is the list of records to be copied.

						(.) ``data_length`` is the size of the elements of
						``in_data_list`` and ``out_data_array``.

						(.) ``out_data_count`` points to an integer which will
						contain the number of records the destination list
						``out_data_array`` if this function is successful.

						(.) ``out_data_array`` points to the destination list to
						which records from ``in_data_list`` are to be copied.
						Memory will be allocated for this array by the function.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mema_to_meml
						meml_copy

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2016 Michael L. Brock

   OUTPUT INDEX:  meml_to_mema
						Memory Array Functions:meml_to_mema
						STRFUNCS:Memory Array Functions:meml_to_mema
						String Functions:See STRFUNCS

   PUBLISH XREF:  meml_to_mema

   PUBLISH NAME:	meml_to_mema

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int meml_to_mema(unsigned int in_data_count, void **in_data_list,
	size_t data_length, unsigned int *out_data_count, void **out_data_array)
#else
int meml_to_mema(in_data_count, in_data_list, data_length, out_data_count,
	out_data_array)
unsigned int   in_data_count;
void         **in_data_list;
size_t         data_length;
unsigned int  *out_data_count;
void         **out_data_array;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned int  count_1;
	char         *tmp_ptr;

	*out_data_count = 0;
	*out_data_array  = NULL;

	if (((!in_data_count) && (in_data_list != NULL)) ||
		(in_data_count && (in_data_list == NULL)) || (!data_length))
		return_code = STRFUNCS_FAILURE;
	else if (in_data_count) {
		if ((*out_data_array = ((void *) calloc(in_data_count,
			data_length))) != NULL) {
			*out_data_count = in_data_count;
			for (count_1 = 0, tmp_ptr = ((char *) *out_data_array);
				count_1 < in_data_count; count_1++, tmp_ptr += data_length) {
				if (in_data_list[count_1] != NULL)
					memcpy(tmp_ptr, in_data_list[count_1], data_length);
			}
		}
		else
			return_code = STRFUNCS_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

COMPAT_FN_DECL(int main, (void));

#define TEST_COUNT							6
#define TEST_WIDTH							21

static void *TEST_List_1[TEST_COUNT] = {
	"AAAAAAAAAAAAAAAAAAAA",
	"BBBBBBBBBBBBBBBBBBBB",
	"CCCCCCCCCCCCCCCCCCCC",
	NULL,
	"DDDDDDDDDDDDDDDDDDDD",
	"EEEEEEEEEEEEEEEEEEEE"
};

static void *TEST_List_2[TEST_COUNT] = {
	"AAAAAAAAAAAAAAAAAAAA",
	"BBBBBBBBBBBBBBBBBBBB",
	"CCCCCCCCCCCCCCCCCCCC",
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
	"DDDDDDDDDDDDDDDDDDDD",
	"EEEEEEEEEEEEEEEEEEEE"
};

int main()
{
	int            return_code;
	unsigned int   array_count = 0;
	void          *array_data  = NULL;
	unsigned int   list_count  = 0;
	void         **list_data   = NULL;
	unsigned int   count_1;
	unsigned int   difference_index;
	char           error_text[STRFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'meml_to_mema()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------------\n\n");

	if ((return_code = meml_to_mema(TEST_COUNT, TEST_List_1, TEST_WIDTH,
		&array_count, &array_data)) != STRFUNCS_SUCCESS)
		strcpy(error_text, "Call to 'meml_to_mema()' failed.");
	else if ((return_code = mema_to_meml(array_count, array_data, TEST_WIDTH,
		&list_count, &list_data)) != STRFUNCS_SUCCESS)
		strcpy(error_text, "Call to 'mema_to_meml()' failed.");
	else if (meml_CompareLists(TEST_COUNT, TEST_List_2, list_count, list_data,
		TEST_WIDTH, &difference_index) != 0) {
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		printf("Difference beginning at index %u\n", difference_index);
		STR_EMIT_CharLine('-', 78, NULL, NULL);
		for (count_1 = 0; count_1 < TEST_COUNT; count_1++)
			printf("%05u:[%s][%s]\n", count_1,
				(TEST_List_2[count_1] != NULL) ? ((char *) TEST_List_2[count_1]) :
				"*** NULL ***",
				(list_data[count_1] != NULL) ? ((char *) list_data[count_1]) :
				"*** NULL ***");
		STR_EMIT_CharLine('=', 78, NULL, NULL);
	}

	mema_remove_all(&array_count, &array_data);
	meml_remove_all(&list_count, &list_data);

	if (return_code != STRFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

