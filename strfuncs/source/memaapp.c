/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Appends an array element to an array.

	Revision History	:	1991-08-22 --- Creation
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mema_append

   SYNOPSIS    :  return_code = mema_append(data_count, data_list, in_data,
							data_length);

						int            return_code;

						unsigned int  *data_count;

						void         **data_list;

						const void    *in_data;

						size_t         data_length;

   DESCRIPTION :  Appends an array element to an array.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in appending the element
						``in_data`` then that integer will be incremented.

						(.) ``data_list`` points to a pointer to ``void`` which
						contains the array. If the function succeeds in appending
						the element ``in_data`` then the memory pointed to by
						``data_list`` will be re-allocated to hold the newly-added
						element.

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

   SEE ALSO    :  mema_add
						mema_copy
						mema_insert
						mema_remove
						meml_append

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  mema_append
						Memory Array Functions:mema_append
						STRFUNCS:Memory Array Functions:mema_append
						String Functions:See STRFUNCS

   PUBLISH XREF:  mema_append

   PUBLISH NAME:	mema_append

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mema_append(unsigned int *data_count, void **data_list,
	const void *in_data, size_t data_length)
#else
int mema_append(data_count, data_list, in_data, data_length)
unsigned int  *data_count;
void         **data_list;
const void    *in_data;
size_t         data_length;
#endif /* #ifndef NARGS */
{
	int   return_code = STRFUNCS_FAILURE;
	void *tmp_list;

	if (data_length > 0) {
#ifdef __MSDOS__
		if ((*data_count == UINT_MAX) || ((((unsigned long) (*data_count + 1)) *
			((unsigned long) data_length)) > ((unsigned long) (UINT_MAX - 15))))
			goto EXIT_FUNCTION;
#endif /* #ifdef __MSDOS__ */
		if (((!(*data_count)) && (!(*data_list))) ||
			((*data_count > 0) && (*data_list))) {
			if (!(*data_list))
				tmp_list = (void *) calloc(data_length, sizeof(char));
			else
				tmp_list = (void *) realloc(*data_list,
					(*data_count + 1) * data_length);
			if (tmp_list != NULL) {
				return_code = STRFUNCS_SUCCESS;
				*data_list  = tmp_list;
				memcpy(((char *) *data_list) + (*data_count * data_length),
					in_data, data_length);
				(*data_count)++;
			}
		}
	}

#ifdef __MSDOS__
EXIT_FUNCTION:
#endif /* #ifdef __MSDOS__ */

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  memaapp

   SYNOPSIS    :  return_code = memaapp(data_count, data_list, in_data,
							data_length);

						int            return_code;

						unsigned int  *data_count;

						void         **data_list;

						const void    *in_data;

						size_t         data_length;

   DESCRIPTION :  Appends an array element to an array.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in appending the element
						``in_data`` then that integer will be incremented.

						(.) ``data_list`` points to a pointer to ``void`` which
						contains the array. If the function succeeds in appending
						the element ``in_data`` then the memory pointed to by
						``data_list`` will be re-allocated to hold the newly-added
						element.

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
						``mema_append``. It is retained for purposes of
						compatibility with legacy code.

   CAVEATS     :  

   SEE ALSO    :  mema_append

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  memaapp
						Memory Array Functions:memaapp
						STRFUNCS:Memory Array Functions:memaapp
						String Functions:See STRFUNCS

   PUBLISH XREF:  memaapp

   PUBLISH NAME:	memaapp

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int memaapp(unsigned int *data_count, void **data_list,
	const void *in_data, size_t data_length)
#else
int memaapp(data_count, data_list, in_data, data_length)
unsigned int  *data_count;
void         **data_list;
const void    *in_data;
size_t         data_length;
#endif /* #ifndef NARGS */
{
	return(mema_append(data_count, data_list, in_data, data_length));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
int main()
{
	int           return_code = 0;
	int           count_1;
	int           count_2;
	unsigned int  test_count  = 0;
	char         *test_list   = NULL;
	char          buffer[512];

	fprintf(stderr, "Test of function 'mema_append()'\n");
	fprintf(stderr, "---- -- -------- ---------------\n\n");

	fprintf(stderr, "[00000]");

	for (count_1 = 0; count_1 < 2000; count_1++) {
		for (count_2 = 0; count_2 < 100; count_2++) {
			if (mema_append(&test_count, ((void **) &test_list),
				((const void *) buffer), sizeof(buffer))) {
				fprintf(stderr,
			"\n>>>Failed 'mema_append()' on test number %u, iteration %u.",
					count_1 + 1, count_2 + 1);
				return_code = -1;
				goto EXIT_FUNCTION;
			}
		}
		if (mema_remove(&test_count, ((void **) &test_list), sizeof(buffer),
			0, test_count)) {
			fprintf(stderr,
				"\n>>>Failed 'mema_remove()' on test number %u.", count_1 + 1);
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

