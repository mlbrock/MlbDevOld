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

		Copyright Michael L. Brock 1993 - 2018.
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

   NAME        :  strlnv_append

   SYNOPSIS    :  return_code = strlnv_append(string_count, string_list,
							string_length, ...);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

						size_t          string_length;

   DESCRIPTION :  Appends a variable number of strings to an array of
						pointers to strings. The length of the strings appended is
						limited by the value of the ``string_length`` parameter.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to integer which contains the
						number of elements in the array to which ``string_list``
						points.

						(-) If the function succeeds in appending the elements
						``...`` then that integer will be increased by the
						number of elements appended to the array.

						(.) ``string_list`` is a triply-indirect pointer to ``char``
						(``char ***``) which contains the array. If the function
						succeeds in appending the elements then the memory pointed
						to by ``string_list`` will be re-allocated to hold the
						newly-added elements.

						(.) ``string_length`` is the maximum length of the ``...``
						strings which are to be appended as elements to the array.

						(.) ``...`` represents subsequent arguments to this function
						(if any) which will be appened to ``string_list`` in the
						order they are encountered.

						(-) Note that the last parameter to this function must be
						``NULL``. This informs the function that no further string
						parameters are to be taken off the stack.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  Use ``strln_append`` to append a single string to an array
						of pointers to strings while limiting its length.

   CAVEATS     :  

   SEE ALSO    :  strln_append
						strlv_append
						memlv_append

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:  strlnv_append
						String List Functions:strlnv_append
						STRFUNCS:String List Functions:strlnv_append
						String Functions:See STRFUNCS

	PUBLISH XREF:  strlnv_append

	PUBLISH NAME:	strlnv_append

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
int strlnv_append(unsigned int *string_count, char ***string_list,
	size_t string_length, ...)
#else
int strlnv_append(string_count, string_list, string_length, va_alist)
unsigned int   *string_count;
char         ***string_list;
size_t          string_length;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned int  old_count;
	const char   *this_string;
	va_list       argument_ptr;

	old_count = *string_count;

	if ((*string_count && (*string_list == NULL)) ||
		((!(*string_count)) && (*string_list != NULL)))
		return_code = STRFUNCS_FAILURE;
	else {
#ifndef NO_STDARGS
		va_start(argument_ptr, string_length);
#else
		va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */
		while ((this_string = va_arg(argument_ptr, const char *)) != NULL) {
			if ((return_code = strln_append(string_count, string_list,
				this_string, string_length)) != STRFUNCS_SUCCESS) {
				strl_remove(string_count, string_list, old_count, *string_count);
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
	char         **string_list  = NULL;
	unsigned int   count_1;
	char          *fgets_return;
	char           buffer[512];

	fprintf(stderr, "Test function for 'strlnv_append()'\n");
	fprintf(stderr, "---- -------- --- -----------------\n\n");

	while ((!feof(stdin)) && (!ferror(stdin))) {
		*buffer      = '\0';
		fgets_return = fgets(buffer, sizeof(buffer) - 1, stdin);
		while (*buffer && (buffer[strlen(buffer) - 1] == '\n'))
			buffer[strlen(buffer) - 1] = '\0';
		if ((!fgets_return) || (!STRFUNCS_strnicmp(buffer, "END", 3))) {
			fprintf(stderr, "ENDING PROCESS: %s\n", (!fgets_return) ?
				"END-FILE-ENCOUNTERED" : "END IN INPUT ENCOUNTERED");
			break;
		}
		if ((return_code = strlnv_append(&string_count, &string_list,
			40, buffer, "*** ADDED LINE ONE ***", "*** ADDED LINE TWO ***",
			NULL)) != STRFUNCS_SUCCESS) {
			fprintf(stderr, "%s (%u lines added previously).\n",
				"Unable to add a line to the string list", string_count);
			goto EXIT_FUNCTION;
		}
	}

	for (count_1 = 0; count_1 < string_count; count_1++)
		printf("[%05u][%s]\n", count_1, string_list[count_1]);

EXIT_FUNCTION:

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

