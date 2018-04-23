/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Groups numeric string values in thousands.

	Revision History	:	1994-10-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
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

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	get_group_length

	SYNOPSIS		:	return_length = get_group_length(in_string, decimal_point,
							group_size, group_separator);

						unsigned int  return_length;

						const char   *in_string;

						const char   *decimal_point;

						unsigned int  group_size;

						const char   *group_separator;

	DESCRIPTION	:	Determines the length of the numeric value as a string
						when the integer portion of that value is separated into
						groups.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` points to the string for which
						determination of the formatted length is to be performed.

						(.) ``decimal_point`` points to the single character which
						separates the integer portion of the number from its
						fractional portion.

						(.) ``group_size`` specifies the number of digits which
						are separated by the ``group_separator`` parameter.

						(.) ``group_separator`` points to the string of one or
						more characters used to separate groups.

	RETURNS		:	The length of the string which would result if the
						function ``insert_groups`` were invoked with similar
						parameters.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  insert_groups

   EXAMPLES    :	For monetary amounts denoted in United States dollars,
						you would invoke this function as follows:

						(-) get_group_length(in_string, ".", 3, ",");

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	get_group_length
						Miscellaneous Functions:get_group_length
						STRFUNCS:Miscellaneous Functions:get_group_length
						String Functions:See STRFUNCS

	PUBLISH XREF:	get_group_length

	PUBLISH NAME:	get_group_length

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
unsigned int get_group_length(const char *in_string, const char *decimal_point,
	unsigned int group_size, const char *group_separator)
#else
unsigned int get_group_length(in_string, decimal_point, group_size,
	group_separator)
const char   *in_string;
const char   *decimal_point;
unsigned int  group_size;
const char   *group_separator;
#endif /* #ifndef NARGS */
{
	unsigned int  string_length = 0;
	unsigned int  group_length;
	unsigned int  added_length;
	const char   *last_ptr;
	const char   *tmp_ptr;

	if ((in_string != NULL) && *in_string) {
		string_length = strlen(in_string);
		if ((group_separator != NULL) && *group_separator && group_size) {
			group_length = strlen(group_separator);
			last_ptr     = ((decimal_point != NULL) && *decimal_point &&
				((tmp_ptr = strrchr(in_string, *decimal_point)) != NULL)) ?
				(tmp_ptr - 1) : (in_string + (string_length - 1));
			if (last_ptr > in_string) {
				added_length   = ((unsigned int) (last_ptr - in_string)) + 1;
				string_length += ((added_length % group_size) ?
					(added_length / group_size) :
					((added_length / group_size) - 1)) * group_length;
			}
		}
	}

	return(string_length);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	insert_groups

	SYNOPSIS		:	return_ptr = insert_groups(in_string, decimal_point,
							group_size, group_separator, out_string);

						const char   *in_string;

						const char   *decimal_point;

						unsigned int  group_size;

						const char   *group_separator;

						char         *out_string;

	DESCRIPTION	:	Formats a numeric value represented as a string with the
						integer portion separated by the specified grouping
						sequence into groups.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` points to the string for which
						formatted grouping is to be performed.

						(.) ``decimal_point`` points to the single character which
						separates the integer portion of the number from its
						fractional portion.

						(.) ``group_size`` specifies the number of digits which
						are separated by the ``group_separator`` parameter.

						(.) ``group_separator`` points to the string of one or
						more characters used to separate groups.

						(.) ``out_string`` points to the string into which the
						formatted result is to be placed by this function.

						(-) This function handles correctly the case where the
						parameters ``in_string`` and ``out_string`` point to the
						same memory buffer.

	RETURNS		:	A pointer to the ``out_string`` parameter.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  get_group_length

   EXAMPLES    :	For monetary amounts denoted in United States dollars,
						you would invoke this function as follows:

						(-) insert_groups(in_string, ".", 3, ",", out_string);

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	insert_groups
						Miscellaneous Functions:insert_groups
						STRFUNCS:Miscellaneous Functions:insert_groups
						String Functions:See STRFUNCS

	PUBLISH XREF:	insert_groups

	PUBLISH NAME:	insert_groups

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *insert_groups(const char *in_string, const char *decimal_point,
	unsigned int group_size, const char *group_separator, char *out_string)
#else
char *insert_groups(in_string, decimal_point, group_size, group_separator,
	out_string)
const char   *in_string;
const char   *decimal_point;
unsigned int  group_size;
const char   *group_separator;
char         *out_string;
#endif /* #ifndef NARGS */
{
	const char   *tmp_ptr = NULL;
   unsigned int  count_1;
	unsigned int  string_length;
   unsigned int  new_length;
	unsigned int  group_length;
	unsigned int  added_length;
	unsigned int  integer_length;
	char         *out_last_ptr;
	const char   *last_ptr;

	if ((new_length = get_group_length(in_string, decimal_point, group_size,
		group_separator)) == 0) {
		if (in_string != out_string)
			*out_string = '\0';
	}
	else if ((string_length = strlen(in_string)) == new_length) {
		if (in_string != out_string)
			strcpy(out_string, in_string);
	}
	else {
		group_length   = strlen(group_separator);
		last_ptr       = ((decimal_point != NULL) && *decimal_point &&
			((tmp_ptr = strrchr(in_string, *decimal_point)) != NULL)) ?
			(tmp_ptr - 1) : (in_string + (string_length - 1));
		added_length   = new_length - string_length;
		integer_length = (tmp_ptr == NULL) ? string_length :
			(added_length + ((unsigned int) (last_ptr - in_string)));
		out_last_ptr   = out_string + string_length + added_length;
		if (tmp_ptr == NULL)
			*out_last_ptr-- = '\0';
		else {
			tmp_ptr = in_string + string_length;
			while (tmp_ptr > last_ptr)
				*out_last_ptr-- = *tmp_ptr--;
		}
		while (integer_length > group_size) {
			for (count_1 = 0; count_1 < group_size; count_1++)
				*out_last_ptr-- = *last_ptr--;
			for (count_1 = 0; count_1 < group_length; count_1++)
				*out_last_ptr-- = group_separator[group_length - (count_1 + 1)];
			integer_length -= group_size;
		}
		for (count_1 = 0; count_1 < integer_length; count_1++)
			*out_last_ptr-- = *last_ptr--;
	}

	return(out_string);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	unsigned int new_length;
	char         buffer_1[512];
	char         buffer_2[512];

	fprintf(stderr, "Test routine for function 'insert_groups()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!STRFUNCS_stricmp(argv[count_1], "-h")) ||
			(!STRFUNCS_stricmp(argv[count_1], "-help"))) {
			fprintf(stderr, "USAGE: cat <test-file> | %s\n\n", argv[0]);
			goto EXIT_FUNCTION;
		}
	}

	while ((!feof(stdin)) && (!ferror(stdin))) {
		if (fgets(buffer_1, sizeof(buffer_1) - 1, stdin) == NULL)
			break;
		while (*buffer_1 && ((buffer_1[strlen(buffer_1) - 1] == '\r') ||
			(buffer_1[strlen(buffer_1) - 1] == '\n')))
			buffer_1[strlen(buffer_1) - 1] = '\0';
		if ((!STRFUNCS_stricmp(buffer_1, "QUIT")) ||
			 (!STRFUNCS_stricmp(buffer_1, "EXIT")))
			break;
		printf("-----------------------------------------------------------\n");
		printf("OLD LENGTH: %u\n", strlen(buffer_1));
		printf("OLD STRING: [%s]\n", buffer_1);
		printf("NEW LENGTH: %u\n", new_length =
			get_group_length(buffer_1, ".", 3, ","));
		printf("NEW STRING: [%s]\n", insert_groups(buffer_1, ".", 3, ",",
			buffer_2));
		if (new_length != strlen(buffer_2)) {
			printf("ERROR     : %s (%u) %s (%u).\n",
				"The calculated length of the adjusted string", new_length,
				"is not equal to that produced by the function",
				strlen(buffer_2));
		}
		if (strcmp(insert_groups(buffer_1, ".", 3, ",", buffer_1), buffer_2))
			printf("ERROR     : %s [%s] %s [%s].\n",
				"The string returned by operating on a different buffer",
				buffer_2, "is not the same as that resulting from the same buffer",
				buffer_1);
		printf("-----------------------------------------------------------\n");
	}

EXIT_FUNCTION:

	return(0);
}

#endif /* #ifdef TEST_MAIN */

