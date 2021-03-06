/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Adds an array of pointers to the end of another array
								of pointers.

	Revision History	:	1991-10-02 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  meml_add

   SYNOPSIS    :  return_code = meml_add(from_data_count, from_data_list,
							data_length, to_data_count, to_data_list);

						int             return_code;

						unsigned int    from_data_count;

						void          **from_data_list;

						size_t          data_length;

						unsigned int   *to_data_count;

						void         ***to_data_list;

   DESCRIPTION :  Adds the records in the list ``from_data_list`` to the
						list ``to_data_list``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``from_data_count`` is the number of records in the
						source list ``from_data_list``.

						(.) ``from_data_list`` is the list of records to be added.

						(.) ``data_length`` is the size of the elements in the two
						lists ``from_data_list`` and ``to_data_list``.

						(.) ``to_data_count`` points to the number of records
						already in the destination list ``to_data_list``.

						(.) ``to_data_list`` points to the destination array to
						which records from ``from_data_list`` are to be added.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

	CAVEATS     :

   SEE ALSO    :  meml_append
						meml_copy
						meml_insert
						meml_remove
						mema_add

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  meml_add
						Memory List Functions:meml_add
						STRFUNCS:Memory List Functions:meml_add
						String Functions:See STRFUNCS

   PUBLISH XREF:  meml_add

   PUBLISH NAME:	meml_add

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int meml_add(unsigned int from_data_count, void **from_data_list,
	size_t data_length, unsigned int *to_data_count, void ***to_data_list)
#else
int meml_add(from_data_count, from_data_list, data_length, to_data_count,
	to_data_list)
unsigned int    from_data_count;
void          **from_data_list;
size_t          data_length;
unsigned int   *to_data_count;
void         ***to_data_list;
#endif /* #ifndef NARGS */
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;
	unsigned int old_to_count;

	if (data_length <= 0)
		return_code = STRFUNCS_FAILURE;
	else {
		old_to_count = *to_data_count;
		for (count_1 = 0; count_1 < from_data_count; count_1++) {
			if ((return_code = meml_append(to_data_count, to_data_list,
				from_data_list[count_1], data_length)) != STRFUNCS_SUCCESS) {
				if (count_1)
					meml_remove(to_data_count, to_data_list, old_to_count,
						count_1);
				break;
			}
		}
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

#define TEST_LENGTH			77

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
int main()
{
	int             return_code  = 0;
	unsigned int    test_count_1 = 0;
	void          **test_list_1  = NULL;
	unsigned int    test_count_2 = 0;
	void          **test_list_2  = NULL;
	unsigned int    count_1;
	unsigned int    count_2;
	unsigned int    count_3;
	char            buffer[TEST_LENGTH + 1];

	fprintf(stderr, "Test of function 'meml_append()'\n");
	fprintf(stderr, "---- -- -------- ---------------\n\n");

	fprintf(stderr, "[00000]");

	for (count_1 = 0; count_1 < 2000; count_1++) {
		memset(buffer, 'A', TEST_LENGTH);
		buffer[TEST_LENGTH] = '\0';
		for (count_2 = 0; count_2 < 100; count_2++) {
			if (meml_append(&test_count_1, &test_list_1, ((const void *) buffer),
				TEST_LENGTH + 1)) {
				fprintf(stderr,
		"\n>>>Failed 'meml_append()' on 'A' test number %u, iteration %u.",
					count_1 + 1, count_2 + 1);
				return_code = -1;
				goto EXIT_FUNCTION;
			}
		}
		memset(buffer, 'B', TEST_LENGTH);
		buffer[TEST_LENGTH] = '\0';
		for (count_2 = 0; count_2 < 100; count_2++) {
			if (meml_append(&test_count_2, &test_list_2, ((const void *) buffer),
				TEST_LENGTH + 1)) {
				fprintf(stderr,
		"\n>>>Failed 'meml_append()' on 'B' test number %u, iteration %u.",
					count_1 + 1, count_2 + 1);
				return_code = -1;
				goto EXIT_FUNCTION;
			}
		}
		if (meml_add(test_count_2, test_list_2, TEST_LENGTH + 1, &test_count_1,
			&test_list_1) != STRFUNCS_SUCCESS) {
			fprintf(stderr,
				"\n>>>Failed 'meml_add()' on test number %u.", count_1 + 1);
			return_code = -1;
			goto EXIT_FUNCTION;
		}
		printf("TEST NUMBER %05u\n", count_1 + 1);
		printf("-----------------------------------------------------------\n");
		for (count_3 = 0; count_3 < test_count_1; count_3++)
			printf("%s\n", ((char *) test_list_1[count_3]));
		printf("-----------------------------------------------------------\n");
		if (meml_remove(&test_count_1, &test_list_1, 0, test_count_1)) {
			fprintf(stderr,
		"\n>>>Failed 'meml_remove()' on 'A' test number %u.", count_1 + 1);
			return_code = -1;
			goto EXIT_FUNCTION;
		}
		if (meml_remove(&test_count_2, &test_list_2, 0, test_count_2)) {
			fprintf(stderr,
		"\n>>>Failed 'meml_remove()' on 'B' test number %u.", count_1 + 1);
			return_code = -1;
			goto EXIT_FUNCTION;
		}
		printf("\b\b\b\b\b\b%05u]", count_1 + 1);
	}

EXIT_FUNCTION:

	printf("\n");

	return(return_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

