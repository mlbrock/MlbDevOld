/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Inserts an element into an array.

	Revision History	:	1991-08-22 --- Creation
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

#ifdef __MSDOS__
#include <limits.h>
#endif /* #ifdef __MSDOS__ */

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* **************************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mema_insert

   SYNOPSIS    :  return_code = mema_insert(data_count, data_list, in_data,
							data_length, insert_position);

						int             return_code;

						unsigned int   *data_count;

						void         ***data_list;

						const void     *in_data;

						size_t          data_length;

						unsigned int    insert_position;

   DESCRIPTION :  Inserts an array element into an array.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in inserting the element
						``in_data`` then that integer will be incremented.

						(.) ``data_list`` points to a pointer to ``void`` which
						contains the array. If the function succeeds in inserting
						the element ``in_data`` then the memory pointed to by
						``data_list`` will be re-allocated to hold the newly-added
						element.

						(.) ``in_data`` points to an area of memory of
						``data_length`` size. The contents of that area of memory
						will be appended to the array pointed to by ``data_list``.

						(.) ``data_length`` is the length of the area of memory to
						which the ``in_data`` parameter points.

						(.) ``insert_position`` is the array element at which the
						element ``in_data`` is to be inserted. It must be in the
						range ''0'' to ``data_count`` ''- 1''.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mema_add
						mema_append
						mema_copy
						mema_remove
						meml_insert

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  mema_insert
						Memory Array Functions:mema_insert
						STRFUNCS:Memory Array Functions:mema_insert
						String Functions:See STRFUNCS

   PUBLISH XREF:  mema_insert

   PUBLISH NAME:	mema_insert

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mema_insert(unsigned int *data_count, void **data_list,
	const void *in_data, size_t data_length, unsigned int insert_position)
#else
int mema_insert(data_count, data_list, in_data, data_length, insert_position)
unsigned int  *data_count;
void         **data_list;
const void    *in_data;
size_t         data_length;
unsigned int   insert_position;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_FAILURE;
	unsigned int  count_1;
	unsigned int  add_count;
	void         *list_ptr;

	if (((!(*data_count)) && (!(*data_list))) ||
		((*data_count > 0) && *data_list)) {
		add_count = (insert_position < *data_count) ? 1 :
			((insert_position - *data_count) + 1);
#ifdef __MSDOS__
		if (((((unsigned long) *data_count) + ((unsigned long) add_count)) >
			((unsigned long) UINT_MAX)) ||
			(((((unsigned long) *data_count) + ((unsigned long) add_count)) *
			((unsigned long) data_length)) > ((unsigned long) (UINT_MAX - 15))))
			goto EXIT_FUNCTION;
#endif /* #ifdef __MSDOS__ */
		if (!(*data_list))
			list_ptr = (void *) calloc(add_count, data_length);
		else
			list_ptr = (void *)
				realloc(*data_list, (*data_count + add_count) * data_length);
		if (list_ptr != NULL) {
			for (count_1 = *data_count; count_1 > insert_position; count_1--)
				memcpy(((char *) list_ptr) + (count_1 * data_length),
					((char *) list_ptr) + ((count_1 - 1) * data_length),
					data_length);
			if (add_count > 1)
				memset(((char *) list_ptr) + (*data_count * data_length),
					'\0', (add_count - 1) * data_length);
			memcpy(((char *) list_ptr) + (insert_position * data_length),
				in_data, data_length);
			*data_count += add_count;
			*data_list   = list_ptr;
			return_code  = STRFUNCS_SUCCESS;
		}
		else
			return_code = STRFUNCS_MEMORY_FAILURE;
	}

#ifdef __MSDOS__
EXIT_FUNCTION:
#endif /* #ifdef __MSDOS__ */

	return(return_code);
}
/* **************************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  memains

   SYNOPSIS    :  return_code = memains(data_count, data_list, in_data,
							data_length, insert_position);

						int             return_code;

						unsigned int   *data_count;

						void         ***data_list;

						const void     *in_data;

						size_t          data_length;

						unsigned int    insert_position;

   DESCRIPTION :  Inserts an array element into an array.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in inserting the element
						``in_data`` then that integer will be incremented.

						(.) ``data_list`` points to a pointer to ``void`` which
						contains the array. If the function succeeds in inserting
						the element ``in_data`` then the memory pointed to by
						``data_list`` will be re-allocated to hold the newly-added
						element.

						(.) ``in_data`` points to an area of memory of
						``data_length`` size. The contents of that area of memory
						will be appended to the array pointed to by ``data_list``.

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
						``mema_insert``. It is retained for purposes of
						compatibility with legacy code.

   CAVEATS     :  

   SEE ALSO    :  mema_insert

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  memains
						Memory Array Functions:memains
						STRFUNCS:Memory Array Functions:memains
						String Functions:See STRFUNCS

   PUBLISH XREF:  memains

   PUBLISH NAME:	memains

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int memains(unsigned int *data_count, void **data_list,
	const void *in_data, size_t data_length, unsigned int insert_position)
#else
int memains(data_count, data_list, in_data, data_length, insert_position)
unsigned int  *data_count;
void         **data_list;
const void    *in_data;
size_t         data_length;
unsigned int   insert_position;
#endif /* #ifndef NARGS */
{
	return(mema_insert(data_count, data_list, in_data, data_length,
		insert_position));
}
/* **************************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(int   TryIt,
	(int in_count, int pos, unsigned int insert));
COMPAT_FN_DECL_STATIC(char *PrintItem,
	(char *item));

int TestCount = 20;

/* **************************************************************************	*/
/* **************************************************************************	*/
/* **************************************************************************	*/
int main()
{
	int    return_code;

	fprintf(stderr, "Test of function 'mema_insert()'\n");
	fprintf(stderr, "---- -- -------- ---------------\n\n");

	TryIt(TestCount, -1, 100);
	if ((return_code = TryIt(TestCount, 3, 4)) == 0) {
		if ((return_code = TryIt(TestCount, 17, 30)) == 0)
			return_code = TryIt(TestCount, -1, 100);
	}

	return((!return_code) ? 1 : return_code);
}

/* **************************************************************************	*/
/* **************************************************************************	*/
/* **************************************************************************	*/
#ifndef NARGS
static int TryIt(int in_count, int pos, unsigned int insert)
#else
static int TryIt(in_count, pos, insert)
int          in_count;
int          pos;
unsigned int insert;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  count_1;
	unsigned int  string_count = 0;
	unsigned int  old_string_count;
	char         *string_list  = (char *) 0;
	char          buffer[512 + 1];

	printf("NOTE: Position = %d, insert = %u\n", pos, insert);
	printf("NOTE: List entry number %u will be of zero-length\n\n",
		in_count / 2);
	fflush(stdout);

	for (count_1 = 0; count_1 < ((unsigned int) in_count); count_1++) {
		sprintf(buffer, "This is string item number %u.", count_1);
		if (count_1 == (((unsigned int) in_count) / 2))
			*buffer = '\0';
		if ((return_code = mema_append(&string_count, ((void **) &string_list),
			buffer, sizeof(buffer))) != 0) {
			fprintf(stderr, "Failed to append string number %u (%s).\n",
				count_1, buffer);
			goto EXIT_FUNCTION;
		}
	}
	printf("Appended %u strings to the list --- list count = %u.\n",
		in_count, string_count);
	fflush(stdout);

	sprintf(buffer, "INTERNAL INSERTION at %u", insert);
	if ((return_code = mema_insert(&string_count, ((void **) &string_list),
		buffer, sizeof(buffer), insert)) != 0) {
		fprintf(stderr, "Failed to insert at position %u.\n", insert);
		goto EXIT_FUNCTION;
	}
	printf("Performed INTERNAL INSERTION at %u --- list count = %u.\n",
		insert, string_count);
	fflush(stdout);

	sprintf(buffer, "ZERO INSERTION at %u", 0);
	if ((return_code = mema_insert(&string_count, ((void **) &string_list),
		buffer, sizeof(buffer), 0)) != 0) {
		fprintf(stderr, "Failed to insert at position %d.\n", 0);
		goto EXIT_FUNCTION;
	}
	printf("Performed ZERO INSERTION at %u --- list count = %u.\n", 0,
		string_count);
	fflush(stdout);

	sprintf(buffer, "PAST-END INSERTION at %u", string_count + 10);
	if ((return_code = mema_insert(&string_count, ((void **) &string_list),
		buffer, sizeof(buffer), string_count + 10)) != 0) {
		fprintf(stderr, "Failed to insert at position %d.\n",
			string_count + 10);
		goto EXIT_FUNCTION;
	}
	printf("Performed PAST-END INSERTION at %u --- list count = %u.\n",
		string_count - 1, string_count);
	fflush(stdout);

/*
	printf("Inserted from position %d for %u strings from list.\n",
		pos, insert);
	fflush(stdout);
*/

	printf("Strings in list: %u\n", string_count);
	for (count_1 = 0; count_1 < string_count; count_1++)
		printf("[%05u] %s\n", count_1,
			PrintItem(string_list + (count_1 * sizeof(buffer))));
	printf("----------------------------------------------------------\n");
	fflush(stdout);

	for (count_1 = 0; count_1 < ((unsigned int) in_count); count_1++) {
		sprintf(buffer, "This is additional string item number %u.",
			in_count + count_1);
printf("%s (%u * %u = %lu)", buffer, string_count + 1, sizeof(buffer),
	((unsigned long) string_count + 1) * ((unsigned long) sizeof(buffer)));
fflush(stdout);
		if ((return_code = mema_append(&string_count, ((void **) &string_list),
			buffer, sizeof(buffer))) != 0) {
			fprintf(stderr,
				"Failed to append additional string number %u (%s).\n",
				in_count + count_1, buffer);
			goto EXIT_FUNCTION;
		}
printf("\n");
fflush(stdout);
	}
	printf("Performed %u additional appends --- list count = %u.\n",
		in_count, string_count);
	fflush(stdout);

	old_string_count = string_count;
	if ((return_code = mema_remove(&string_count, ((void **) &string_list),
		sizeof(buffer), 0, string_count)) != 0)
		fprintf(stderr, "Failed to delete all strings in list.\n");
	else {
		printf("Deleted all %u items from the list --- list count = %u.\n",
			old_string_count, string_count);
		fflush(stdout);
	}

EXIT_FUNCTION:

	fflush(stderr);

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

