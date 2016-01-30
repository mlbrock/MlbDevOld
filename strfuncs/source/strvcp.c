/* *********************************************************************** */
/* ***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Variable-argument string copy.

	Revision History	:	1993-01-09 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
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

   NAME        :  strvcpy

   SYNOPSIS    :  string_ptr = strvcpy(target_string, ...);

						char *string_ptr;

						char *target_string;

   DESCRIPTION :  Copies each of a variable list of strings to a string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``target_string`` is a pointer to a pointer to char
						into which the copy will be performed.

						(.) ``...`` represents subsequent arguments to this function
						(if any) which will be concatenated to the string
						``target_string`` in the order they are encountered.

						(-) Note that the last parameter to this function must be
						``NULL``. This informs the function that no further string
						parameters are to be taken off the stack.

   RETURNS     :  A pointer to the string ``target_string``.

   NOTES       :  If you have not already allocated memory to hold
						``target_string``, you should use ``strvacpy`` instead.

   CAVEATS     :  

	SEE ALSO    :  strv_padded_cpy
						strvcat
						strnvacpy
						strnvcpy
						strvacpy

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:  strvcpy
						Variable Argument Allocation Copy Functions:strvcpy
						STRFUNCS:Variable Argument Allocation Copy Functions:strvcpy
						String Functions:See STRFUNCS

   PUBLISH XREF:  strvcpy

	PUBLISH NAME:	strvcpy

	ENTRY CLASS	:	Variable Argument Allocation Copy Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
char *strvcpy(char *target_string, ...)
#else
char *strvcpy(target_string, va_alist)
char *target_string;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	char       *tmp_ptr;
	const char *this_string;
	va_list     argument_ptr;

	tmp_ptr  = target_string;
	*tmp_ptr = '\0';

#ifndef NO_STDARGS
	va_start(argument_ptr, target_string);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	while ((this_string = va_arg(argument_ptr, const char *)) != NULL) {
		strcpy(tmp_ptr, this_string);
		tmp_ptr += strlen(this_string);
	}

	va_end(argument_ptr);

	return(target_string);
}
/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strv_padded_cpy

   SYNOPSIS    :  string_ptr = strv_padded_cpy(target_string, left_padding,
							right_padding, ...);

						char       *string_ptr;

						char       *target_string;

						const char *left_padding;

						const char *right_padding;

   DESCRIPTION :  Copies each of a variable list of strings to a string.

						Each string so copied may optionally be preceded by a left
						padding string and/or followed by a right padding string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``target_string`` is a pointer to a pointer to char
						into which the copy will be performed.

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
						``target_string``, you should use ``strva_padded_cpy``
						instead.

	CAVEATS     :  

   SEE ALSO    :  strvcpy
						strv_padded_cat
						strnva_padded_cpy
						strnv_padded_cpy
						strva_padded_cpy

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:  strv_padded_cpy
						Variable Argument Allocation Copy Functions:strv_padded_cpy
						STRFUNCS:Variable Argument Allocation Copy Functions:strv_padded_cpy
						String Functions:See STRFUNCS

   PUBLISH XREF:  strv_padded_cpy

	PUBLISH NAME:	strv_padded_cpy

	ENTRY CLASS	:	Variable Argument Allocation Copy Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
char *strv_padded_cpy(char *target_string, const char *left_padding,
	const char *right_padding, ...)
#else
char *strv_padded_cpy(target_string, left_padding, right_padding, va_alist)
char       *target_string;
const char *left_padding;
const char *right_padding;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	char         *tmp_ptr;
	const char   *this_string;
	const char   *tmp_left;
	const char   *tmp_right;
	unsigned int  padding_length;
	va_list       argument_ptr;

	tmp_ptr        = target_string;
	*tmp_ptr       = '\0';
	tmp_left       = (left_padding == NULL)  ? "" : left_padding;
	tmp_right      = (right_padding == NULL) ? "" : right_padding;
	padding_length = strlen(tmp_left) + strlen(tmp_right);

#ifndef NO_STDARGS
	va_start(argument_ptr, right_padding);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	while ((this_string = va_arg(argument_ptr, const char *)) != NULL) {
		strcat(strcat(strcpy(tmp_ptr, tmp_left), this_string), tmp_right);
		tmp_ptr += strlen(this_string) + padding_length;
	}

	va_end(argument_ptr);

	return(target_string);
}
/* ***********************************************************************	*/

#ifdef TEST_MAIN
 
#include <stdio.h>

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

	fprintf(stderr, "Test function for 'strvcpy()'\n");
	fprintf(stderr, "---- -------- --- -----------\n\n");

	if (argc != 4)
		fprintf(stderr, "USAGE:\n%s <string> <string> <string>\n\n", argv[0]);
	else {
		total_length = 0;
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++)
			total_length += strlen(argv[count_1]);
		if ((total_length + 1) > sizeof(buffer))
			fprintf(stderr, "Total length of strings exceeds maxmum (%u).\n\n",
				sizeof(buffer) - 1);
		else
			printf("[%s]\n", strvcpy(buffer, argv[1], argv[2], argv[3], NULL));
	}

	fprintf(stderr, "Test function for 'strv_padded_cpy()'\n");
	fprintf(stderr, "---- -------- --- -------------------\n\n");

	if (argc != 4)
		fprintf(stderr, "USAGE:\n%s <string> <string> <string>\n\n", argv[0]);
	else {
		total_length = 0;
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++)
			total_length += strlen(TEST_LEFT_PADDING) + strlen(argv[count_1]) +
				strlen(TEST_RIGHT_PADDING);
		if ((total_length + 1) > sizeof(buffer))
			fprintf(stderr, "Total length of strings exceeds maxmum (%u).\n\n",
				sizeof(buffer) - 1);
		else {
			printf("[%s]\n", strv_padded_cpy(buffer, TEST_LEFT_PADDING,
				TEST_RIGHT_PADDING, argv[1], argv[2], argv[3], NULL));
			return_code = 0;
		}
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

