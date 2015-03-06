/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reverses the order of an array of pointers.

	Revision History	:	1991-10-02 --- Creation
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

   NAME        :  meml_reverse

   SYNOPSIS    :  meml_reverse(data_count, data_list);

						unsigned int   data_count;

						void         **data_list;

   DESCRIPTION :  Reverses the order of an array of pointers.

   PARAMETERS  :  Parameters to this function are as follow:

						``data_count`` is the number of elements in the array
						of pointers ``data_list``.

						``data_list`` is the array of pointers to be reversed.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  meml_reverse
						Memory List Functions:meml_reverse
						STRFUNCS:Memory List Functions:meml_reverse
						String Functions:See STRFUNCS

   PUBLISH XREF:  meml_reverse

   PUBLISH NAME:	meml_reverse

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void meml_reverse(unsigned int data_count, void **data_list)
#else
void meml_reverse(data_count, data_list)
unsigned int   data_count;
void         **data_list;
#endif /* #ifndef NARGS */
{
	STR_LIST_reverse(data_count, data_list);
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int            return_code = 0;
	unsigned int   test_count  = 0;
	char         **test_list   = NULL;
	unsigned int   count_1;
	char           buffer[512];

	fprintf(stderr, "Test of function 'meml_reverse()'\n");
	fprintf(stderr, "---- -- -------- ----------------\n\n");

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
					test_list[count_1], test_list[count_1]);
		}
		else if ((!stricmp(buffer, "END")) || (!stricmp(buffer, "QUIT")) ||
			(!stricmp(buffer, "EXIT")))
			break;
		else if ((return_code = memlapp(&test_count, ((void ***) &test_list),
			buffer, sizeof(buffer))) == STRFUNCS_FAILURE) {
			fprintf(stderr, "\nERROR ON ATTEMPT TO APPEND STRING\n\n");
			break;
		}
		return_code = 0;
	}

	if (!return_code) {
		strl_sort(test_count, test_list);
		fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
		for (count_1 = 0; count_1 < test_count; count_1++)
			fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
				test_list[count_1], test_list[count_1]);
		meml_reverse(test_count, ((void **) test_list));
		fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
		for (count_1 = 0; count_1 < test_count; count_1++)
			fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
				test_list[count_1], test_list[count_1]);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

