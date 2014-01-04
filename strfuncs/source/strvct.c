/* *********************************************************************** */
/* ***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Variable-argument string concatenation.

	Revision History	:	1993-01-09 --- Creation
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

#include <string.h>

#include "strfunci.h"

/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strvcat

   SYNOPSIS    :  string_ptr = strvcat(target_string, ...);

						char *string_ptr;

						char *target_string;

   DESCRIPTION :  Concatenates each of a variable list of strings to a string.

	PARAMETERS  :  Parameters to this function are as follow:

						(.) ``target_string`` is a pointer to a pointer to char
						into which the concatenation will be performed.

						(.) ``...`` represents subsequent arguments to this function
						(if any) which will be concatenated to the string
						``target_string`` in the order they are encountered.

						(-) Note that the last parameter to this function must be
						``NULL``. This informs the function that no further string
						parameters are to be taken off the stack.

   RETURNS     :  A pointer to the string ``target_string``.

   NOTES       :  If you have not already allocated memory to hold
						``target_string``, you should use ``strvacat`` instead.

   CAVEATS     :  

   SEE ALSO    :  strv_padded_cat
						strvcpy
						strnvacat
						strnvcat
						strvacat

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:  strvcat
						Variable Argument Allocation Concatenation Functions:strvcat
						STRFUNCS:Variable Argument Allocation Concatenation Functions:strvcat
						String Functions:See STRFUNCS

	PUBLISH XREF:  strvcat

	PUBLISH NAME:	strvcat

	ENTRY CLASS	:	Variable Argument Allocation Concatenation Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
char *strvcat(char *target_string, ...)
#else
char *strvcat(target_string, va_alist)
char *target_string;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	const char *this_string;
	va_list     argument_ptr;

#ifndef NO_STDARGS
	va_start(argument_ptr, target_string);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	while ((this_string = va_arg(argument_ptr, const char *)) != NULL)
		strcat(target_string, this_string);

	va_end(argument_ptr);

	return(target_string);
}
/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strv_padded_cat

   SYNOPSIS    :  string_ptr = strv_padded_cat(target_string, left_padding,
							right_padding, ...);

						char       *string_ptr;

						char       *target_string;

						const char *left_padding;

						const char *right_padding;

   DESCRIPTION :  Concatenates each of a variable list of strings to a string.

						Each string so copied may optionally be preceded by a left
						padding string and/or followed by a right padding string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``target_string`` is a pointer to a pointer to char
						into which the concatenation will be performed.

						(.) ``left_padding`` is the string to precede each ``...``
						argument string. It may be ''NULL''.

						(.) ``right_padding`` is the string to follow each ``...``
						argument string. It may be ''NULL''.

						(.) ``...`` represents subsequent arguments to this function
						(if any) which will be concatenated to the string
						``target_string`` in the order they are encountered.

						(-) Note that the last parameter to this function must be
						``NULL``. This informs the function that no further string
						parameters are to be taken off the stack.

   RETURNS     :  A pointer to the string ``target_string``.

   NOTES       :  If you have not already allocated memory to hold
						``target_string``, you should use ``strva_padded_cat``
						instead.

   CAVEATS     :  

	SEE ALSO    :  strvcat
						strv_padded_cpy
						strnva_padded_cat
						strnv_padded_cat
						strva_padded_cat

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:  strv_padded_cat
						Variable Argument Allocation Concatenation Functions:strv_padded_cat
						STRFUNCS:Variable Argument Allocation Concatenation Functions:strv_padded_cat
						String Functions:See STRFUNCS

   PUBLISH XREF:  strv_padded_cat

   PUBLISH NAME:	strv_padded_cat

	ENTRY CLASS	:	Variable Argument Allocation Concatenation Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
char *strv_padded_cat(char *target_string, const char *left_padding,
	const char *right_padding, ...)
#else
char *strv_padded_cat(target_string, left_padding, right_padding, va_alist)
char       *target_string;
const char *left_padding;
const char *right_padding;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	const char *this_string;
	const char *tmp_left;
	const char *tmp_right;
	va_list     argument_ptr;

	tmp_left       = (left_padding == NULL)  ? "" : left_padding;
	tmp_right      = (right_padding == NULL) ? "" : right_padding;

#ifndef NO_STDARGS
	va_start(argument_ptr, right_padding);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	while ((this_string = va_arg(argument_ptr, const char *)) != NULL)
		strcat(strcat(strcat(target_string, tmp_left), this_string), tmp_right);

	va_end(argument_ptr);

	return(target_string);
}
/* ***********************************************************************	*/

#ifdef TEST_MAIN
 
#include <stdio.h>

#define TEST_BASE				"BEGIN_STRING:"

#define TEST_LEFT_PADDING	">>>"
#define TEST_RIGHT_PADDING	"<<<"

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code  = 1;
	unsigned int count_1;
	unsigned int total_length;
	char         buffer[512];

	fprintf(stderr, "Test function for 'strvcat()'\n");
	fprintf(stderr, "---- -------- --- -----------\n\n");

	if (argc != 4)
		fprintf(stderr, "USAGE:\n%s <string> <string> <string>\n\n", argv[0]);
	else {
		total_length = strlen(TEST_BASE);
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++)
			total_length += strlen(argv[count_1]);
		if ((total_length + 1) > sizeof(buffer))
			fprintf(stderr, "Total length of strings exceeds maxmum (%u).\n\n",
				sizeof(buffer) - 1);
		else {
			strcpy(buffer, TEST_BASE);
			printf("[%s]\n", strvcat(buffer, argv[1], argv[2], argv[3], NULL));
			return_code = 0;
		}
	}

	fprintf(stderr, "Test function for 'strv_padded_cat()'\n");
	fprintf(stderr, "---- -------- --- -------------------\n\n");

	if (argc != 4)
		fprintf(stderr, "USAGE:\n%s <string> <string> <string>\n\n", argv[0]);
	else {
		total_length = strlen(TEST_BASE);
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++)
			total_length += strlen(TEST_LEFT_PADDING) + strlen(argv[count_1]) +
				strlen(TEST_RIGHT_PADDING);
		if ((total_length + 1) > sizeof(buffer))
			fprintf(stderr, "Total length of strings exceeds maxmum (%u).\n\n",
				sizeof(buffer) - 1);
		else {
			strcpy(buffer, TEST_BASE);
			printf("[%s]\n", strv_padded_cat(buffer, TEST_LEFT_PADDING,
				TEST_RIGHT_PADDING, argv[1], argv[2], argv[3], NULL));
			return_code = 0;
		}
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

