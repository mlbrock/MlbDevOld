/* *********************************************************************** */
/* ***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Variable-argument array of pointers append.

	Revision History	:	1993-01-08 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* ***********************************************************************	*/
 
/* ***********************************************************************	*/
/* ***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/* ***********************************************************************	*/

#include "strfunci.h"

/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  memlv_append

   SYNOPSIS    :  return_code = memlv_append(data_count, data_list,
							data_length, ...);

						int             return_code;

						unsigned int   *data_count;

						void         ***data_list;

						size_t          data_length;

   DESCRIPTION :  Appends a variable number of array elements to an array of
						pointers.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in appending the elements
						``...`` then that integer will be increased by the
						number of elements appended to the array.

						(.) ``data_list`` is a triply-indirect pointer to ``void``
						(``void ***``) which contains the array. If the function
						succeeds in appending the elements then the memory pointed
						to by ``data_list`` will be re-allocated to hold the
						newly-added elements.

						(.) ``data_length`` is the length of the area of memory to
						which the ``...`` parameters point.

						(.) ``...`` represents subsequent arguments to this function
						(if any) which will be appened to ``data_list`` in the
						order they are encountered.

						(-) Note that the last parameter to this function must be
						``NULL``. This informs the function that no further string
						parameters are to be taken off the stack.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  Use ``meml_append`` to append a single element to an array
						of pointers.

	CAVEATS     :  

   SEE ALSO    :  meml_append
						strlv_append
						strlnv_append

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:  memlv_append
						Memory List Functions:memlv_append
						STRFUNCS:Memory List Functions:memlv_append
						String Functions:See STRFUNCS

   PUBLISH XREF:  memlv_append

   PUBLISH NAME:	memlv_append

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
int memlv_append(unsigned int *data_count, void ***data_list,
	size_t data_length, ...)
#else
int memlv_append(data_count, data_list, data_length, va_alist)
unsigned int   *data_count;
void         ***data_list;
size_t          data_length;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned int  old_count;
	const char   *this_data;
	va_list       argument_ptr;

	old_count = *data_count;

	if ((*data_count && (*data_list == NULL)) ||
		((!(*data_count)) && (*data_list != NULL)))
		return_code = STRFUNCS_FAILURE;
	else {
#ifndef NO_STDARGS
		va_start(argument_ptr, data_length);
#else
		va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */
		while ((this_data =
			((const char *) va_arg(argument_ptr, const void *))) != NULL) {
			if ((return_code = meml_append(data_count, data_list, this_data,
				data_length)) != STRFUNCS_SUCCESS) {
				meml_remove(data_count, data_list, old_count, *data_count);
				break;
			}
		}
		va_end(argument_ptr);
	}


	return(return_code);
}
/* ***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int            return_code  = STRFUNCS_SUCCESS;
	unsigned int   string_count = 0;
	void         **string_list  = NULL;
	unsigned int   count_1;
	char          *fgets_return;
	char           buffer[512];

	fprintf(stderr, "Test of function 'memlv_append()'\n");
	fprintf(stderr, "---- -- -------- ----------------\n\n");

	while ((!feof(stdin)) && (!ferror(stdin))) {
		*buffer      = '\0';
		fgets_return = fgets(buffer, sizeof(buffer) - 1, stdin);
		while (*buffer && (buffer[strlen(buffer) - 1] == '\n'))
			buffer[strlen(buffer) - 1] = '\0';
		if ((!fgets_return) || (!strnicmp(buffer, "END", 3))) {
			fprintf(stderr, "ENDING PROCESS: %s\n", (!fgets_return) ?
				"END-FILE-ENCOUNTERED" : "END IN INPUT ENCOUNTERED");
			break;
		}
		if ((return_code = memlv_append(&string_count, &string_list,
			40, buffer, "*** ADDED LINE ONE ***", "*** ADDED LINE TWO ***",
			NULL)) != STRFUNCS_SUCCESS) {
			fprintf(stderr, "%s (%u lines added previously).\n",
				"Unable to add a line to the string list", string_count);
			goto EXIT_FUNCTION;
		}
	}

	for (count_1 = 0; count_1 < string_count; count_1++)
		printf("[%05u][%s]\n", count_1, ((char *) string_list[count_1]));

EXIT_FUNCTION:

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

