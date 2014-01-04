/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Inserts an element into an array of pointers to
								strings.

	Revision History	:	1991-09-13 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
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

/* **************************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strln_insert

   SYNOPSIS    :  return_code = strln_insert(string_count, string_list,
							in_string, string_length, insert_position);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

						char           *in_string;

						size_t          string_length;

						unsigned int    insert_position;

   DESCRIPTION :  Inserts an element into an array of pointers to strings.
						The string copied from ``in_string`` will be truncated to a
						maximum length of ``string_length`` bytes (excluding the
						terminating ASCII NUL byte).

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to integer which contains the
						number of elements in the array to which ``string_list``
						points.

						(-) If the function succeeds in inserting the element
						``in_string`` then that integer will be incremented.

						(.) ``string_list`` is a triply-indirect pointer to ``char``
						(``char ***``) which contains the array. If the function
						succeeds in inserting the element ``in_string`` then the
						memory pointed to by ``string_list`` will be re-allocated to
						hold the newly-added element.

						(.) ``in_string`` points to the area of memory to be
						inserted into the array pointed to by ``string_list``.

						(.) ``string_length`` is the maximum length of ``in_string``
						to be inserted into the array, not including the terminating
						ASCII NUL byte.

						(.) ``insert_position`` is the array element at which the
						element ``in_string`` is to be inserted. It must be in the
						range ''0'' to ``string_count`` ''- 1''.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

	SEE ALSO		:	strl_insert
						meml_insert

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  strln_insert
						String List Functions:strln_insert
						STRFUNCS:String List Functions:strln_insert
						String Functions:See STRFUNCS

   PUBLISH XREF:  strln_insert

   PUBLISH NAME:	strln_insert

	ENTRY CLASS	:	String List Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
int strln_insert(unsigned int *string_count, char ***string_list,
	const char *in_string, size_t string_length, unsigned int insert_position)
#else
int strln_insert(string_count, string_list, in_string, string_length,
	insert_position)
unsigned int   *string_count;
char         ***string_list;
const char     *in_string;
size_t          string_length;
unsigned int    insert_position;
#endif /* #ifndef NARGS */
{
	int    return_code;
	int    added_byte;
	char **list_ptr;

	added_byte =
		((string_length > 0) && (string_length <= strlen(in_string))) ? 1 : 0;

	if ((return_code = memlins(string_count, ((void ***) string_list),
		((const void *) in_string), string_length + added_byte,
		insert_position)) == 0) {
		if (added_byte) {
			list_ptr                                 = *string_list;
			list_ptr[insert_position][string_length] = '\0';
		}
	}

	return(return_code);
}
/* **************************************************************************	*/

/* **************************************************************************	*/
/* **************************************************************************	*/
/* BOH

   NAME        :  strlnins

   SYNOPSIS    :  return_code = strlnins(string_count, string_list,
							in_string, string_length, insert_position);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

						char           *in_string;

						size_t          string_length;

						unsigned int    insert_position;

   DESCRIPTION :  Inserts an element into an array of pointers to strings.
						The string copied from ``in_string`` will be truncated to a
						maximum length of ``string_length`` bytes (excluding the
						terminating ASCII NUL byte).

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to integer which contains the
						number of elements in the array to which ``string_list``
						points.

						(-) If the function succeeds in inserting the element
						``in_string`` then that integer will be incremented.

						(.) ``string_list`` is a triply-indirect pointer to ``char``
						(``char ***``) which contains the array. If the function
						succeeds in inserting the element ``in_string`` then the
						memory pointed to by ``string_list`` will be re-allocated to
						hold the newly-added element.

						(.) ``in_string`` points to the area of memory to be
						inserted into the array pointed to by ``string_list``.

						(.) ``string_length`` is the maximum length of ``in_string``
						to be inserted into the array, not including the terminating
						ASCII NUL byte.

						(.) ``insert_position`` is the array element at which the
						element ``in_string`` is to be inserted. It must be in the
						range ''0'' to ``string_count`` ''- 1''.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  This function does no more than call the function
						``strln_insert``. It is retained for purposes of
						compatibility with legacy code.

   CAVEATS     :  

   SEE ALSO    :  strln_insert

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  strnlins
						String List Functions:strnlins
						STRFUNCS:String List Functions:strnlins
						String Functions:See STRFUNCS

   PUBLISH XREF:  strnlins

   PUBLISH NAME:	strnlins

	ENTRY CLASS	:	String List Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
int strlnins(unsigned int *string_count, char ***string_list,
	const char *in_string, size_t string_length, unsigned int insert_position)
#else
int strlnins(string_count, string_list, in_string, string_length,
	insert_position)
unsigned int   *string_count;
char         ***string_list;
const char     *in_string;
size_t          string_length;
unsigned int    insert_position;
#endif /* #ifndef NARGS */
{
	return(strln_insert(string_count, string_list, in_string, string_length,
		insert_position));
}
/* **************************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(char *PrintItem,
	(char *));

unsigned int TestCount = 10;

/* **************************************************************************	*/
/* **************************************************************************	*/
/* **************************************************************************	*/
int main()
{
	int            return_code  = 0;
	unsigned int   string_count = 0;
	unsigned int   count_1;
	size_t         length;
	char         **string_list  = (char **) 0;
	char           buffer[512 + 1];

	printf("Test of function 'strln_insert()'\n");
	printf("---- -- -------- ----------------\n\n");

	printf("NOTE: List entry number %u will be of zero-length\n",
		TestCount / 2);
	printf("NOTE: List entry number %u will be of length 1 (the NULL byte)\n\n",
		(TestCount / 2) + 1);

	for (count_1 = 0; count_1 < TestCount; count_1++) {
		sprintf(buffer, "This is string item number %u.", count_1);
		length = count_1 + 1;
		if (count_1 == (TestCount / 2)) {
			*buffer = '\0';
			length  = 0;
		}
		else if (count_1 == ((TestCount / 2) + 1)) {
			*buffer = '\0';
			length  = 0;
		}
		if ((return_code = strln_insert(&string_count, &string_list, buffer,
			length, count_1)) != STRFUNCS_SUCCESS) {
			fprintf(stderr, "Failed to insert string number %u (%s).\n",
				count_1, buffer);
			goto EXIT_FUNCTION;
		}
	}

	printf("Strings in list: %u\n", string_count);
	for (count_1 = 0; count_1 < string_count; count_1++)
		printf("[%05u] %s\n", count_1, PrintItem(string_list[count_1]));

EXIT_FUNCTION:

	return((return_code) ? -1 : 1);
}
/* **************************************************************************	*/

/* **************************************************************************	*/
/* **************************************************************************	*/
/* **************************************************************************	*/
#ifndef NARGS
static char *PrintItem(char *item)
#else
static char *PrintItem(item)
char *item;
#endif /* #ifndef NARGS */
{
	return((item) ? item : "*** NULL ***");
}
/* **************************************************************************	*/

#endif /* TEST_MAIN */

