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

		Copyright Michael L. Brock 1993 - 2015.
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

   NAME        :  strnvcat

   SYNOPSIS    :  string_ptr = strnvcat(target_string, string_length, ...);

						char   *string_ptr;

						char   *target_string;

						size_t  string_length;

	DESCRIPTION :  Concatenates the specified length of each of a variable
						list of strings to a string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``target_string`` is a pointer to a pointer to char
						into which the concatenation will be performed.

						(.) ``string_length`` is the maximum length of each of the
						``...`` arguments to be copied to ``target_string``.

						(.) ``...`` represents subsequent arguments to this function
						(if any) which will be concatenated to the string
						``target_string`` in the order they are encountered.

						(-) Note that the last parameter to this function must be
						``NULL``. This informs the function that no further string
						parameters are to be taken off the stack.

   RETURNS     :  A pointer to the string ``target_string``.

	NOTES       :  If you have not already allocated memory to hold
						``target_string``, you should use ``strnvacat`` instead.

   CAVEATS     :  

   SEE ALSO    :  strnv_padded_cat
						strnvcpy
						strnvacat
						strvcat
						strvacat

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2015 Michael L. Brock

	OUTPUT INDEX:  strnvcat
						Variable Argument Allocation Concatenation Functions:strnvcat
						STRFUNCS:Variable Argument Allocation Concatenation Functions:strnvcat
						String Functions:See STRFUNCS

	PUBLISH XREF:  strnvcat

	PUBLISH NAME:	strnvcat

	ENTRY CLASS	:	Variable Argument Allocation Concatenation Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
char *strnvcat(char *target_string, size_t string_length, ...)
#else
char *strnvcat(target_string, string_length, va_alist)
char   *target_string;
size_t  string_length;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	const char *this_string;
	va_list     argument_ptr;

#ifndef NO_STDARGS
	va_start(argument_ptr, string_length);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	while ((this_string = va_arg(argument_ptr, const char *)) != NULL)
		nstrcat(target_string, this_string, string_length);

	va_end(argument_ptr);

	return(target_string);
}
/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strnv_padded_cat

   SYNOPSIS    :  string_ptr = strnv_padded_cat(target_string, string_length,
							left_padding, right_padding, ...);

						char        *string_ptr;

						char       *target_string;

						size_t      string_length;

						const char *left_padding;

						const char *right_padding;

   DESCRIPTION :  Concatenates the specified length of each of a variable
						list of strings to a string.

						Each string so copied may optionally be preceded by a left
						padding string and/or followed by a right padding string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``target_string`` is a pointer to a pointer to char
						into which the concatenation will be performed.

						(.) ``string_length`` is the maximum length of each of the
						``...`` arguments to be copied to ``target_string``.

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
						``target_string``, you should use ``strnva_padded_cat``
						instead.

	CAVEATS     :  

   SEE ALSO    :  strnvcat
						strnv_padded_cpy
						strnva_padded_cat
						strv_padded_cat
						strva_padded_cat

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2015 Michael L. Brock

   OUTPUT INDEX:  strnv_padded_cat
						Variable Argument Allocation Concatenation Functions:strnv_padded_cat
						STRFUNCS:Variable Argument Allocation Concatenation Functions:strnv_padded_cat
						String Functions:See STRFUNCS

   PUBLISH XREF:  strnv_padded_cat

	PUBLISH NAME:	strnv_padded_cat

	ENTRY CLASS	:	Variable Argument Allocation Concatenation Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
char *strnv_padded_cat(char *target_string, size_t string_length,
	const char *left_padding, const char *right_padding, ...)
#else
char *strnv_padded_cat(target_string, string_length, left_padding,
	right_padding, va_alist)
char       *target_string;
size_t      string_length;
const char *left_padding;
const char *right_padding;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	const char *this_string;
	const char *tmp_left;
	const char *tmp_right;
	va_list     argument_ptr;

	tmp_left  = (left_padding == NULL)  ? "" : left_padding;
	tmp_right = (right_padding == NULL) ? "" : right_padding;

#ifndef NO_STDARGS
	va_start(argument_ptr, right_padding);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	while ((this_string = va_arg(argument_ptr, const char *)) != NULL)
		strcat(nstrcat(strcat(target_string, tmp_left), this_string,
			string_length), tmp_right);

	va_end(argument_ptr);

	return(target_string);
}
/* ***********************************************************************	*/

#ifdef TEST_MAIN
 
#include <stdio.h>

#define TEST_BASE          "BEGIN_STRING:"

#define TEST_LENGTH			3

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

	fprintf(stderr, "Test function for 'strnvcat()'\n");
	fprintf(stderr, "---- -------- --- ------------\n\n");

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
			printf("[%s]\n", strnvcat(buffer, TEST_LENGTH, argv[1], argv[2],
				argv[3], NULL));
			return_code = 0;
		}
	}

	fprintf(stderr, "Test function for 'strnv_padded_cat()'\n");
	fprintf(stderr, "---- -------- --- --------------------\n\n");

	if (argc != 4)
		fprintf(stderr, "USAGE:\n%s <string> <string> <string>\n\n", argv[0]);
	else {
		total_length = strlen(TEST_BASE);
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++)
			total_length += strlen(TEST_LEFT_PADDING) +
				((strlen(argv[count_1]) > TEST_LENGTH) ? TEST_LENGTH :
				strlen(argv[count_1])) + strlen(TEST_RIGHT_PADDING);
		if ((total_length + 1) > sizeof(buffer))
			fprintf(stderr, "Total length of strings exceeds maxmum (%u).\n\n",
				sizeof(buffer) - 1);
		else {
			strcpy(buffer, TEST_BASE);
			printf("[%s]\n", strnv_padded_cat(buffer, TEST_LENGTH,
				TEST_LEFT_PADDING, TEST_RIGHT_PADDING, argv[1], argv[2], argv[3],
				NULL));
			return_code = 0;
		}
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

