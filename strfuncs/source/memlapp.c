/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Appends an array element to an array of pointers.

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

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  meml_append

   SYNOPSIS    :  return_code = meml_append(data_count, data_list, in_data,
							data_length);

						int            return_code;

						unsigned int   *data_count;

						void         ***data_list;

						const void     *in_data;

						size_t          data_length;

   DESCRIPTION :  Appends an array element to an array of pointers.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in appending the element
						``in_data`` then that integer will be incremented.

						(.) ``data_list`` is a triply-indirect pointer to ``void``
						(``void ***``) which contains the array. If the function
						succeeds in appending the element ``in_data`` then the
						memory pointed to by ``data_list`` will be re-allocated to
						hold the newly-added element.

						(.) ``in_data`` points to an area of memory of
						``data_length`` size. The contents of that area of memory
						will be appended to the array pointed to by ``data_list``.

						(.) ``data_length`` is the length of the area of memory to
						which the ``in_data`` parameter points.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  meml_add
						meml_copy
						meml_insert
						meml_remove
						meml_append

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  meml_append
						Memory List Functions:meml_append
						STRFUNCS:Memory List Functions:meml_append
						String Functions:See STRFUNCS

   PUBLISH XREF:  meml_append

   PUBLISH NAME:	meml_append

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int meml_append(unsigned int *data_count, void ***data_list,
	const void *in_data, size_t data_length)
#else
int meml_append(data_count, data_list, in_data, data_length)
unsigned int   *data_count;
void         ***data_list;
const void     *in_data;
size_t          data_length;
#endif /* #ifndef NARGS */
{
	int    return_code = STRFUNCS_FAILURE;
	void  *tmp_data    = NULL;
	void **tmp_list;

	if (((!(*data_count)) && (*data_list == NULL)) ||
		(*data_count && (*data_list != NULL))) {
		if (data_length > 0) {
			if ((tmp_data = ((void *) calloc(data_length, sizeof(char)))) == NULL)
				goto EXIT_FUNCTION;
			memcpy(tmp_data, in_data, data_length);
		}
		if (*data_list == NULL)
			tmp_list = (void **) calloc(1, sizeof(char *));
		else
			tmp_list = (void **) realloc(*data_list,
				(*data_count + 1) * sizeof(char *));
		if (tmp_list != NULL) {
			return_code           = STRFUNCS_SUCCESS;
			tmp_list[*data_count] = tmp_data;
			*data_list            = tmp_list;
			(*data_count)++;
		}
		else if (tmp_data != NULL)
			free(tmp_data);
	}

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  memlapp

   SYNOPSIS    :  return_code = memlapp(data_count, data_list, in_data,
							data_length);

						int            return_code;

						unsigned int   *data_count;

						void         ***data_list;

						const void     *in_data;

						size_t          data_length;

   DESCRIPTION :  Appends an array element to an array of pointers.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in appending the element
						``in_data`` then that integer will be incremented.

						(.) ``data_list`` is a triply-indirect pointer to ``void``
						(``void ***``) which contains the array. If the function
						succeeds in appending the element ``in_data`` then the
						memory pointed to by ``data_list`` will be re-allocated to
						hold the newly-added element.

						(.) ``in_data`` points to an area of memory of
						``data_length`` size. The contents of that area of memory
						will be appended to the array pointed to by ``data_list``.

						(.) ``data_length`` is the length of the area of memory to
						which the ``in_data`` parameter points.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  This function does no more than call the function
						``meml_append``. It is retained for purposes of
						compatibility with legacy code.

   CAVEATS     :  

   SEE ALSO    :  meml_append

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  memlapp
						Memory List Functions:memlapp
						STRFUNCS:Memory List Functions:memlapp
						String Functions:See STRFUNCS

   PUBLISH XREF:  memlapp

   PUBLISH NAME:	memlapp

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int memlapp(unsigned int *data_count, void ***data_list, const void *in_data,
	size_t data_length)
#else
int memlapp(data_count, data_list, in_data, data_length)
unsigned int   *data_count;
void         ***data_list;
const void     *in_data;
size_t          data_length;
#endif /* #ifndef NARGS */
{
	return(meml_append(data_count, data_list, in_data, data_length));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
int main()
{
	int            return_code = 0;
	unsigned int   test_count  = 0;
	char         **test_list   = NULL;
	int            count_1;
	int            count_2;
	char           buffer[512];

	fprintf(stderr, "Test of function 'meml_append()'\n");
	fprintf(stderr, "---- -- -------- ---------------\n\n");

	fprintf(stderr, "[00000]");

	for (count_1 = 0; count_1 < 2000; count_1++) {
		for (count_2 = 0; count_2 < 100; count_2++) {
			if (meml_append(&test_count, ((void ***) &test_list), buffer,
				sizeof(buffer))) {
				fprintf(stderr,
					"\n>>>Failed 'meml_append()' on test number %u, iteration %u.",
					count_1 + 1, count_2 + 1);
				return_code = -1;
				goto EXIT_FUNCTION;
			}
		}
		if (meml_remove(&test_count, ((void ***) &test_list), 0, test_count)) {
			fprintf(stderr,
				"\n>>>Failed 'meml_remove()' on test number %u.", count_1 + 1);
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

