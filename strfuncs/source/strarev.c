/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reverses an array.

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

   NAME        :  STR_ARRAY_reverse

   SYNOPSIS    :  void STR_ARRAY_reverse(data_count, data_list, data_length);

						unsigned int  data_count;

						void         *data_list;

						size_t        data_length;

   DESCRIPTION :  Reverses an array.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` is the number of elements in the array
						of ``data_list``.

						(.) ``data_list`` is the array to be reversed.

						(.) ``data_length`` is the size the elements in the array
						``data_list``.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  STR_ARRAY_reverse
						Memory Array Functions:STR_ARRAY_reverse
						STRFUNCS:Memory Array Functions:STR_ARRAY_reverse
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_ARRAY_reverse

   PUBLISH NAME:	STR_ARRAY_reverse

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void STR_ARRAY_reverse(unsigned int data_count, void *data_list,
	size_t data_length)
#else
void STR_ARRAY_reverse(data_count, data_list, data_length)
unsigned int  data_count;
void         *data_list;
size_t        data_length;
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	unsigned int  count_2;
	char         *from_ptr;
	char         *to_ptr;
	char          tmp_char;

	for (count_1 = 0; count_1 < (data_count / 2); count_1++) {
		from_ptr = ((char *) data_list) + (count_1 * data_length);
		to_ptr   = ((char *) data_list) + ((data_count - (count_1 + 1)) *
			data_length);
		for (count_2 = 0; count_2 < data_length; count_2++) {
			tmp_char    = *from_ptr;
			*from_ptr++ = *to_ptr;
			*to_ptr++   =  tmp_char;
		}
	}
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = 0;
	unsigned int  test_count  = 0;
	char         *test_list   = NULL;
	unsigned int  count_1;
	char          buffer[512];

	fprintf(stderr, "Test of function 'STR_ARRAY_reverse()'\n");
	fprintf(stderr, "---- -- -------- ---------------------\n\n");

	while ((!feof(stdin)) && (!ferror(stdin))) {
		*buffer = '\0';
		while (!(*buffer)) {
			fgets(buffer, sizeof(buffer) - 1, stdin);
			while (strlen(buffer) && (buffer[strlen(buffer) - 1] == '\n'))
				buffer[strlen(buffer) - 1] = '\0';
		}
		if (!stricmp(buffer, "LIST")) {
			fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
			for (count_1 = 0; count_1 < test_count; count_1++)
				fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
					test_list + (count_1 * sizeof(buffer)),
					test_list + (count_1 * sizeof(buffer)));
		}
		else if ((!stricmp(buffer, "END")) || (!stricmp(buffer, "QUIT")) ||
			(!stricmp(buffer, "EXIT")))
			break;
		else if ((return_code = mema_append(&test_count, ((void **) &test_list),
			((void *) buffer), sizeof(buffer))) == STRFUNCS_FAILURE) {
			fprintf(stderr, "\nERROR ON ATTEMPT TO APPEND STRING\n\n");
			break;
		}
		return_code = 0;
	}

	if (!return_code) {
		fprintf(stderr, "Sorting . . .");
#ifndef NARGS
		STR_ARRAY_qsort(NULL, test_count, test_list, sizeof(buffer),
			((int (*)(void *, const void *, const void *, size_t)) STR_strcmp));
#else
		STR_ARRAY_qsort(NULL, test_count, test_list, sizeof(buffer),
			STR_strcmp);
#endif /* #ifndef NARGS */
		fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
		for (count_1 = 0; count_1 < test_count; count_1++)
			fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
				test_list + (count_1 * sizeof(buffer)),
				test_list + (count_1 * sizeof(buffer)));
		STR_ARRAY_reverse(test_count, test_list, sizeof(buffer));
		fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
		for (count_1 = 0; count_1 < test_count; count_1++)
			fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
				test_list + (count_1 * sizeof(buffer)),
				test_list + (count_1 * sizeof(buffer)));
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

