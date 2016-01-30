/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Inserts an element into an array of pointers.

	Revision History	:	1991-10-02 --- Creation
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
#include <string.h>

#include "strfunci.h"

/* **************************************************************************	*/

/* **************************************************************************	*/
/* **************************************************************************	*/
/* BOH

	NAME			:	meml_insert

	SYNOPSIS		:	return_code = meml_insert(data_count, data_list, in_data,
							data_length, insert_position);

						int             return_code;

						unsigned int   *data_count;

						void         ***data_list;

						const void     *in_data;

						size_t          data_length;

						unsigned int    insert_position;

   DESCRIPTION :  Inserts an element into an array of pointers.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in inserting the element
						``in_data`` then that integer will be incremented.

						(.) ``data_list`` is a triply-indirect pointer to ``void``
						(``void ***``) which contains the array. If the function
						succeeds in inserting the element ``in_data`` then the
						memory pointed to by ``data_list`` will be re-allocated to
						hold the newly-added element.

						(.) ``in_data`` points to an area of memory of
						``data_length`` size. The contents of that area of memory
						will be inserted into the array pointed to by ``data_list``.

						(.) ``data_length`` is the length of the area of memory to
						which the ``in_data`` parameter points.

						(.) ``insert_position`` is the array element at which the
						element ``in_data`` is to be inserted. It must be in the
						range ''0'' to ``data_count`` ''- 1''.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

	NOTES			:	

   SEE ALSO    :  meml_add
						meml_append
						meml_copy
						meml_remove
						mema_insert

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2016 Michael L. Brock

   OUTPUT INDEX:  meml_insert
						Memory List Functions:meml_insert
						STRFUNCS:Memory List Functions:meml_insert
						String Functions:See STRFUNCS

   PUBLISH XREF:  meml_insert

   PUBLISH NAME:	meml_insert

	ENTRY CLASS	:	Memory List Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
int meml_insert(unsigned int *data_count, void ***data_list,
	const void *in_data, size_t data_length, unsigned int insert_position)
#else
int meml_insert(data_count, data_list, in_data, data_length, insert_position)
unsigned int   *data_count;
void         ***data_list;
const void     *in_data;
size_t          data_length;
unsigned int    insert_position;
#endif /* #ifndef NARGS */
{
	int            return_code = -1;
	void          *data_ptr    = (void *) 0;
	unsigned int   count_1;  
	unsigned int   add_count;
	void         **list_ptr;

	if (((*data_count == 0) && (!(*data_list))) ||
		((*data_count > 0) && (*data_list))) {
		if (data_length > 0) {
			if ((data_ptr = calloc(data_length, sizeof(char))) == NULL)
				goto EXIT_FUNCTION;
		}
		add_count       = (insert_position < *data_count) ? 1 :
			(insert_position - *data_count) + 1;
		if (!(*data_count))
			list_ptr = (void **) calloc(add_count, sizeof(void *));
		else
			list_ptr = (void **)
				realloc(*data_list, (*data_count + add_count) * sizeof(void *));
		if (list_ptr == NULL) {
			if (data_ptr)
				free(data_ptr);
		}
		else {
			memset(list_ptr + *data_count, '\0', add_count * sizeof(void *));
			for (count_1 = *data_count; count_1 > insert_position; count_1--)
				list_ptr[count_1] = list_ptr[count_1 - 1];
			if (data_length > 0)
				memcpy(data_ptr, in_data, data_length);
			list_ptr[insert_position]  = data_ptr;
			*data_list                 = list_ptr;
			*data_count               += add_count;
			return_code                = 0;
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/* **************************************************************************	*/

/* **************************************************************************	*/
/* **************************************************************************	*/
/* BOH

	NAME			:	memlins

	SYNOPSIS		:	return_code = memlins(data_count, data_list, in_data,
							data_length, insert_position);

						int             return_code;

						unsigned int   *data_count;

						void         ***data_list;

						const void     *in_data;

						size_t          data_length;

						unsigned int    insert_position;

   DESCRIPTION :  Inserts an element into an array of pointers.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in inserting the element
						``in_data`` then that integer will be incremented.

						(.) ``data_list`` is a triply-indirect pointer to ``void``
						(``void ***``) which contains the array. If the function
						succeeds in inserting the element ``in_data`` then the
						memory pointed to by ``data_list`` will be re-allocated to
						hold the newly-added element.

						(.) ``in_data`` points to an area of memory of
						``data_length`` size. The contents of that area of memory
						will be inserted into the array pointed to by ``data_list``.

						(.) ``data_length`` is the length of the area of memory to
						which the ``in_data`` parameter points.

						(.) ``insert_position`` is the array element at which the
						element ``in_data`` is to be inserted. It must be in the
						range ''0'' to ``data_count`` ''- 1''.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  This function does no more than call the function
						``meml_insert``. It is retained for purposes of
						compatibility with legacy code.

   SEE ALSO    :  meml_insert

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2016 Michael L. Brock

   OUTPUT INDEX:  memlins
						Memory List Functions:memlins
						STRFUNCS:Memory List Functions:memlins
						String Functions:See STRFUNCS

   PUBLISH XREF:  memlins

   PUBLISH NAME:	memlins

	ENTRY CLASS	:	Memory List Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
int memlins(unsigned int *data_count, void ***data_list, const void *in_data,
	size_t data_length, unsigned int insert_position)
#else
int memlins(data_count, data_list, in_data, data_length, insert_position)
unsigned int   *data_count;
void         ***data_list;
const void     *in_data;
size_t          data_length;
unsigned int    insert_position;
#endif /* #ifndef NARGS */
{
	return(meml_insert(data_count, data_list, in_data, data_length,
		insert_position));
}
/* **************************************************************************	*/

#ifdef TEST_MAIN  

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(int   TryIt,
	(int, unsigned int));
COMPAT_FN_DECL_STATIC(char *PrintItem,
	(char *));

int TestCount = 20;

/* **************************************************************************	*/
/* **************************************************************************	*/
/* **************************************************************************	*/
int main()
{
	int return_code;

	fprintf(stderr, "Test of function 'meml_insert()'\n");
	fprintf(stderr, "---- -- -------- ---------------\n\n");

	if ((return_code = TryIt(TestCount, 4)) == 0) {
		if ((return_code = TryIt(TestCount, 30)) == 0)
			return_code = TryIt(TestCount, 1000);
	}

	return((!return_code) ? 1 : return_code);
}

/* **************************************************************************	*/
/* **************************************************************************	*/
/* **************************************************************************	*/
#ifndef NARGS
static int TryIt(int count, unsigned int insert)
#else
static int TryIt(count, pos, insert)
int          count;
unsigned int insert;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   count_1;
	unsigned int   string_count = 0;
	char         **string_list  = (char **) 0;
	char           buffer[512 + 1];

	printf("NOTE: List entry number %u will be of zero-length\n\n", count / 2);

	for (count_1 = 0; count_1 < ((unsigned int) count); count_1++) {
		sprintf(buffer, "This is string item number %u.", count_1);
		if (count_1 == (((unsigned int) count) / 2))
			*buffer = '\0';
		if ((return_code = memlapp(&string_count, ((void ***) &string_list),
			buffer, strlen(buffer) + 1)) != STRFUNCS_SUCCESS) {
			fprintf(stderr, "Failed to append string number %u (%s).\n",
				count_1, buffer);
			goto EXIT_FUNCTION;
		}
	}

	printf("Appended %u strings to the list.\n", string_count);

	strcpy(buffer, "INTERNAL INSERTION");
	if ((return_code = meml_insert(&string_count, ((void ***) &string_list),
		buffer, strlen(buffer) + 1, insert)) != STRFUNCS_SUCCESS) {
		fprintf(stderr, "Failed to insert at position %d.\n", insert);
		goto EXIT_FUNCTION;
	}

	strcpy(buffer, "NEGATIVE-ONE INSERTION");
	if ((return_code = meml_insert(&string_count, ((void ***) &string_list),
		buffer, strlen(buffer) + 1, ((unsigned int) -1))) != STRFUNCS_SUCCESS) {
		fprintf(stderr, "Failed to insert at position %d.\n", -1);
		goto EXIT_FUNCTION;
	}

	strcpy(buffer, "PAST-END INSERTION");
	if ((return_code = meml_insert(&string_count, ((void ***) &string_list),
		buffer, strlen(buffer) + 1, string_count + 10)) != STRFUNCS_SUCCESS) {
		fprintf(stderr, "Failed to insert at position %d.\n",
			string_count + 10);
		goto EXIT_FUNCTION;
	}

/*
	printf("Inserted from position %d for %d strings from list.\n",
		pos, insert);
*/

	printf("Strings in list: %u\n", string_count);
	for (count_1 = 0; count_1 < string_count; count_1++)
		printf("[%05u] %s\n", count_1, PrintItem(string_list[count_1]));

	for (count_1 = 0; count_1 < ((unsigned int) count); count_1++) {
		sprintf(buffer, "This is additional string item number %u.",
			count + count_1);
		if ((return_code = memlapp(&string_count, ((void ***) &string_list),
			buffer, strlen(buffer) + 1)) != STRFUNCS_SUCCESS) {
			fprintf(stderr,
				"Failed to append additional string number %u (%s).\n",
				count + count_1, buffer);
			goto EXIT_FUNCTION;
		}
	}

	if ((return_code = memldel(&string_count, ((void ***) &string_list), 0,
		string_count)) != STRFUNCS_SUCCESS)
		fprintf(stderr, "Failed to delete all strings in list.\n");

EXIT_FUNCTION:

	return(return_code);
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

