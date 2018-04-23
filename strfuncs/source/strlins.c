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

#include <string.h>

#include "strfunci.h"

/* **************************************************************************	*/

/* **************************************************************************	*/
/* **************************************************************************	*/
/* BOH

	NAME			:	strl_insert

	SYNOPSIS		:	return_code = strl_insert(string_count, string_list,
							new_string, insert_position);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

						const char     *new_string;

						unsigned int    insert_position;

   DESCRIPTION :  Inserts an element into an array of pointers to strings.

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

						(.) ``insert_position`` is the array element at which the
						element ``in_string`` is to be inserted. It must be in the
						range ''0'' to ``string_count`` ''- 1''.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

	NOTES			:

	SEE ALSO		:	strln_insert
						meml_insert

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  strl_insert
						String List Functions:strl_insert
						STRFUNCS:String List Functions:strl_insert
						String Functions:See STRFUNCS

   PUBLISH XREF:  strl_insert

   PUBLISH NAME:	strl_insert

	ENTRY CLASS	:	String List Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
int strl_insert(unsigned int *string_count, char ***string_list,
	const char *new_string, unsigned int insert_position)
#else
int strl_insert(string_count, string_list, new_string, insert_position)
unsigned int   *string_count;
char         ***string_list;
const char     *new_string;
unsigned int    insert_position;
#endif /* #ifndef NARGS */
{
	return(memlins(string_count, ((void ***) string_list),
		((const void *) new_string), strlen(new_string) + 1, insert_position));
}
/* **************************************************************************	*/

/* **************************************************************************	*/
/* **************************************************************************	*/
/* BOH

	NAME			:	strlins

	SYNOPSIS		:	return_code =  strlins(string_count, string_list,
							new_string, insert_position);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

						const char     *new_string;

						unsigned int    insert_position;

   DESCRIPTION :  Inserts an element into an array of pointers to strings.

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

						(.) ``insert_position`` is the array element at which the
						element ``in_string`` is to be inserted. It must be in the
						range ''0'' to ``string_count`` ''- 1''.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  This function does no more than call the function
						``strl_insert``. It is retained for purposes of
						compatibility with legacy code.

	SEE ALSO		:	strl_insert

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  strlins
						String List Functions:strlins
						STRFUNCS:String List Functions:strlins
						String Functions:See STRFUNCS

   PUBLISH XREF:  strlins

   PUBLISH NAME:	strlins

	ENTRY CLASS	:	String List Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
int strlins(unsigned int *string_count, char ***string_list,
	const char *new_string, unsigned int insert_position)
#else
int strlins(string_count, string_list, new_string, insert_position)
unsigned int   *string_count;
char         ***string_list;
const char     *new_string;
unsigned int    insert_position;
#endif /* #ifndef NARGS */
{
	return(strl_insert(string_count, string_list, new_string,
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
	char         **string_list  = (char **) 0;
	char           buffer[512 + 1];

	fprintf(stderr, "Test of function 'strl_insert()'\n");
	fprintf(stderr, "---- -- -------- ---------------\n\n");

	printf("NOTE: List entry number %u will be of length 1 (the NULL byte)\n\n",
		TestCount / 2);

	for (count_1 = 0; count_1 < TestCount; count_1++) {
		sprintf(buffer, "This is string item number %u.", count_1);
		if (count_1 == (TestCount / 2))
			*buffer = '\0';
		if ((return_code = strl_insert(&string_count, &string_list, buffer,
			string_count + 1)) != STRFUNCS_SUCCESS) {
			fprintf(stderr, "Failed to append string number %u (%s).\n",
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

