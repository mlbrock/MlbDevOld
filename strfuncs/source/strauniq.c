/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Makes an array unique.

	Revision History	:	1991-09-08 --- Creation
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

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  STR_ARRAY_uniq

   SYNOPSIS    :  STR_ARRAY_uniq(control_ptr, data_count, data_list,
							data_length, compare_function);

						void          *control_ptr;

						unsigned int  *data_count;

						void         **data_list;

						size_t         data_length;

						int          (*compare_function)(void *, const void *,
							const void *, size_t);

   DESCRIPTION :  Makes an array unique.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparisons
						used to determine equivalence. It is passed unexamined
						to the comparison function ``compare_function``. If
						unnecessary, it may be a ''NULL'' pointer.

						(.) ``data_count`` points to the number of elements in the
						array ``data_list``.

						(.) ``data_list`` points to the array to be made unique.

						(.) ``data_length`` is the size of each element of the array
						``data_list``.

						(.) ``compare_function`` is a pointer to the function which
						will determine equivalence. The function to which
						``compare_function`` points should accept the arguments
						indicated in the SYNOPSIS and return an integral result
						as follows:

						(..) negative if the first element is less than second.

						(..) positive if the first element is greater than second.

						(..) zero if the elements are equal.

   RETURNS     :  Void.

	NOTES       :

   CAVEATS     :  The results of invoking this function with an ``data_list``
						not in sorted order using the same criteria as the function
						``compare_function`` are undefined.

						If there are multiple elements in ``data_list`` which
						compare equal, it is impossible to determine which of
						them will be removed by this function.

   SEE ALSO    :  STR_LIST_uniq

	EXAMPLES    :

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  STR_ARRAY_uniq
						Memory Array Functions:STR_ARRAY_uniq
						STRFUNCS:Memory Array Functions:STR_ARRAY_uniq
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_ARRAY_uniq

   PUBLISH NAME:	STR_ARRAY_uniq

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void STR_ARRAY_uniq(void *control_ptr, unsigned int *data_count,
	void **data_list, size_t data_length,
	int (*compare_function)(void *, const void *, const void *, size_t))
#else
void STR_ARRAY_uniq(control_ptr, data_count, data_list, data_length,
	compare_function)
void          *control_ptr;
unsigned int  *data_count;
void         **data_list;
size_t         data_length;
int          (*compare_function)();
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	if (*data_count > 1) {
		for (count_1 = 0; *data_count && (count_1 < (*data_count - 1));
			count_1++) {
			while (((count_1 + 1) < *data_count) &&
				(!(*compare_function)(control_ptr,
				((char *) *data_list) + (count_1 * data_length),
				((char *) *data_list) + ((count_1 + 1) * data_length),
				data_length)))
				mema_remove(data_count, data_list, data_length, count_1 + 1, 1);
		}
	}
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COMPAT_FN_DECL(int main, (void));

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
int main()
{
	int           return_code = 0;
	unsigned int  count_1;
	unsigned int  line_count  = 0;
	unsigned int  test_count  = 0;
	char         *test_list   = NULL;
	char          buffer[64];
	char          in_line[64];

	fprintf(stderr, "Test of function 'STR_ARRAY_uniq()'\n");
	fprintf(stderr, "---- -- -------- ------------------\n\n");

	while ((!feof(stdin)) && (!ferror(stdin))) {
		*in_line = '\0';
		while (!(*in_line)) {
			fgets(in_line, sizeof(in_line) - 1, stdin);
			while (strlen(in_line) && (in_line[strlen(in_line) - 1] == '\n'))
				in_line[strlen(in_line) - 1] = '\0';
			line_count++;
		}
		memset(buffer, '\0', sizeof(buffer));
		strcpy(buffer, in_line);
		if (!stricmp(in_line, "LIST")) {
			fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
			for (count_1 = 0; count_1 < test_count; count_1++)
				fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
					test_list + (count_1 * sizeof(in_line)),
					test_list + (count_1 * sizeof(in_line)));
		}
		else if ((!stricmp(in_line, "END")) || (!stricmp(in_line, "QUIT")) ||
			(!stricmp(in_line, "EXIT")))
			break;
		else if ((return_code = mema_append(&test_count, ((void **) &test_list),
			((void *) in_line), sizeof(in_line))) != 0) {
			fprintf(stderr, "\nERROR ON ATTEMPT TO ADD STRING\n\n");
			break;
		}
		fprintf(stderr, "%05u / %05u ----------------------------------\n",
			line_count, test_count);
		return_code = 0;
	}

	fprintf(stderr, "%05u / %05u ==================================\n",
		line_count, test_count);

	if (!return_code) {
		fprintf(stderr, "Sorting . . .");
#ifndef NARGS
		STR_ARRAY_qsort(NULL, test_count, test_list, sizeof(buffer),
			((int (*)(void *, const void *, const void *, size_t)) STR_strcmp));
#else
		STR_ARRAY_qsort(NULL, test_count, test_list, sizeof(buffer),
			STR_strcmp);
#endif /* #ifndef NARGS */
		fprintf(stderr, "Uniqing . . .");
#ifndef NARGS
		STR_ARRAY_uniq(NULL, &test_count, ((void **) &test_list),
			sizeof(in_line),
			((int (*)(void *, const void *, const void *, size_t)) STR_strcmp));
#else
		STR_ARRAY_uniq(NULL, &test_count, ((void **) &test_list),
			sizeof(in_line), STR_strcmp);
#endif /* #ifndef NARGS */
		fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
		for (count_1 = 0; count_1 < test_count; count_1++)
			printf("[%05u][%08p] ---> [%s]\n", count_1,
				test_list + (count_1 * sizeof(in_line)),
				test_list + (count_1 * sizeof(in_line)));
	}

	return(return_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

