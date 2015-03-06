/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Allocates memory for array elements.

	Revision History	:	1991-10-02 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#ifdef __MSDOS__
#include <limits.h>			
#endif /* #ifdef __MSDOS__ */

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  meml_allocate

   SYNOPSIS    :  return_code = meml_allocate(data_count, data_list,
							data_length, element_count);

						int             return_code;

						unsigned int   *data_count;

						void         ***data_list;

						size_t          data_length;

						unsigned int    element_count;

   DESCRIPTION :  Allocates memory for array elements.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in allocating elements for the
						array then that integer will be incremented.

						(.) ``data_list`` is a triply-indirect pointer to ``void``
						(``void ***``) which contains the array. If the function
						succeeds allocating elements for the array then the memory
						pointed to by ``data_list`` will be re-allocated to hold
						the newly-added elements.

						(.) ``data_length`` is the length of the area of memory for
						which memory is to be allocaed for each of the elements
						added.

						(-) You may pass a ``data_length`` parameter of ''0'', in
						which case memory will be allocated for the specified
						number of elements in ``element_count``, but the pointer
						in each element will be set to ''NULL''.

						(.) ``element_count`` is the number of elements to add to
						the array.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  meml_append

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  meml_allocate
						Memory List Functions:meml_allocate
						STRFUNCS:Memory List Functions:meml_allocate
						String Functions:See STRFUNCS

   PUBLISH XREF:  meml_allocate

   PUBLISH NAME:	meml_allocate

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int meml_allocate(unsigned int *data_count, void ***data_list,
	size_t data_length, unsigned int element_count)
#else
int meml_allocate(data_count, data_list, data_length, element_count)
unsigned int   *data_count;
void         ***data_list;
size_t          data_length;
unsigned int    element_count;
#endif /* #ifndef NARGS */
{
	int            return_code = STRFUNCS_FAILURE;
	void          *tmp_data    = NULL;
	unsigned int   old_data_count;
	unsigned int   count_1;
	void         **tmp_list;

	if (!element_count)
		return_code = STRFUNCS_SUCCESS;
	else {
#ifdef __MSDOS__
		if ((*data_count == UINT_MAX) || ((((unsigned long)
			(*data_count + element_count)) *
			((unsigned long) sizeof(char *))) > ((unsigned long) (UINT_MAX - 15))))
			goto EXIT_FUNCTION;
#endif /* #ifdef __MSDOS__ */
		if (((!(*data_count)) && (*data_list == NULL)) ||
			(*data_count && (*data_list != NULL))) {
			if (data_length) {
				if ((tmp_data = ((void *) calloc(data_length, sizeof(char)))) ==
            	NULL)
					goto EXIT_FUNCTION;
			}
			if (!(*data_list))
				tmp_list = (void **) calloc(element_count, sizeof(void *));
			else
				tmp_list = (void **) realloc(*data_list,
					(*data_count + element_count) * sizeof(void *));
			if (tmp_list == NULL) {
				if (tmp_data)
					free(tmp_data);
			}
			else if (!data_length) {
				memset(((char *) tmp_list) + (*data_count * sizeof(void **)),
					'\0', element_count * sizeof(void **));
				*data_list   = tmp_list;
				*data_count += element_count;
				return_code  = STRFUNCS_SUCCESS;
			}
			else {
				return_code                   = STRFUNCS_SUCCESS;
				old_data_count                = *data_count;
				*data_list                    = tmp_list;
				(*data_list)[(*data_count)++] = tmp_data;
				for (count_1 = 1; count_1 < element_count; count_1++) {
					if ((return_code = memlapp(data_count, data_list,
						tmp_data, data_length)) != STRFUNCS_SUCCESS) {
						memldel(data_count, data_list, old_data_count, count_1);
						break;
					}
				}
			}
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
int main()
{
	int            return_code = 0;
	int            count_1;
	int            count_2;
	unsigned int   test_count  = 0;
	void         **test_list   = NULL;
	char           buffer[512];

	fprintf(stderr, "Test of function 'meml_allocate()'\n");
	fprintf(stderr, "---- -- -------- -----------------\n\n");

	fprintf(stderr, "Test Number One [00000]");
	for (count_1 = 0; count_1 < 2000; count_1++) {
		for (count_2 = 0; count_2 < 100; count_2++) {
			if (meml_allocate(&test_count, &test_list, sizeof(buffer), 1)) {
				fprintf(stderr,
					"\n>>>Failed 'memlapp()' on test number %u, iteration %u.",
					count_1 + 1, count_2 + 2);
				return_code = -1;
				goto EXIT_FUNCTION;
			}
		}
		for (count_2 = 0; count_2 < 100; count_2++)
			memcpy(test_list[count_2], buffer, sizeof(buffer));
		if (meml_remove(&test_count, &test_list, 0, test_count)) {
			printf("\n>>>Failed 'memldel()' on test number %u.", count_1 + 1);
			return_code = -1;
			goto EXIT_FUNCTION;
		}
		fprintf(stderr, "\b\b\b\b\b\b%05u]", count_1 + 1);
	}
	fprintf(stderr, "\n");

	fprintf(stderr, "Test Number Two [00000]");
	for (count_1 = 0; count_1 < 2000; count_1++) {
		for (count_2 = 0; count_2 < 25; count_2++) {
			if (meml_allocate(&test_count, &test_list, sizeof(buffer), 4)) {
				fprintf(stderr,
					"\n>>>Failed 'memlapp()' on test number %u, iteration %u.",
					count_1 + 1, count_2 + 2);
				return_code = -1;
				goto EXIT_FUNCTION;
			}
		}
		for (count_2 = 0; count_2 < 100; count_2++)
			memcpy(test_list[count_2], buffer, sizeof(buffer));
		if (meml_remove(&test_count, &test_list, 0, test_count)) {
			printf("\n>>>Failed 'memldel()' on test number %u.", count_1 + 1);
			return_code = -1;
			goto EXIT_FUNCTION;
		}
		fprintf(stderr, "\b\b\b\b\b\b%05u]", count_1 + 1);
	}
	fprintf(stderr, "\n");

EXIT_FUNCTION:

	printf("\n");

	return(return_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

