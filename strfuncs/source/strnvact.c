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

#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strnvacat

   SYNOPSIS    :  string_ptr = strnvacat(target_string, string_length, ...);

						char    *string_ptr;

						char   **target_string;

						size_t   string_length;

   DESCRIPTION :  Allocates memory for and concatenates the specified length
						of each of a variable list of strings to a string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``target_string`` is a pointer to a pointer to char
						into which the concatenation will be performed.

						(-) If ``target_string`` is NULL, then sufficient space to
						hold the string resulting from this function will be
						``malloc``ed.

						(-) If ``target_string`` is not NULL, then this function
						will ``realloc`` sufficient space.

						(.) ``string_length`` is the maximum length of each of the
						``...`` arguments to be concatenated to ``target_string``.

						(.) ``...`` represents subsequent arguments to this function
						(if any) which will be concatenated to the string
						``target_string`` in the order they are encountered.

						(-) Note that the last parameter to this function must be
						``NULL``. This informs the function that no further string
						parameters are to be taken off the stack.

   RETURNS     :  A pointer to the string to which ``target_string`` points.

   NOTES       :  If you have already allocated memory to hold
						``target_string``, you may use ``strnvcat`` instead.

   CAVEATS     :  

   SEE ALSO    :  strnva_padded_cat
						strnvacpy
						strnvcat
						strvacat
						strvcat

   EXAMPLES    :  

	AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:  strnvacat
						Variable Argument Allocation Concatenation Functions:strnvacat
						STRFUNCS:Variable Argument Allocation Concatenation Functions:strnvacat
						String Functions:See STRFUNCS

   PUBLISH XREF:  strnvacat

   PUBLISH NAME:	strnvacat

	ENTRY CLASS	:	Variable Argument Allocation Concatenation Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
char *strnvacat(char **target_string, size_t string_length, ...)
#else
char *strnvacat(target_string, string_length, va_alist)
char   **target_string;
size_t   string_length;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	char         *tmp_ptr;
	const char   *this_string;
	unsigned int  total_length;
	unsigned int  tmp_length;
	va_list       argument_ptr;

#ifndef NO_STDARGS
	va_start(argument_ptr, string_length);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	total_length = ((*target_string == NULL) ? 0 : strlen(*target_string)) + 1;
	while ((this_string = va_arg(argument_ptr, const char *)) != NULL)
		total_length += ((tmp_length = strlen(this_string)) > string_length) ?
			string_length : tmp_length;

	if ((tmp_ptr = ((char *) ((*target_string == NULL) ?
		malloc(total_length * sizeof(char)) : realloc(*target_string,
		total_length * sizeof(char))))) != NULL) {
		va_end(*target_string);
#ifndef NO_STDARGS
		va_start(argument_ptr, string_length);
#else
		va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */
		if (*target_string == NULL)
			*tmp_ptr = '\0';
		*target_string = tmp_ptr;
		while ((this_string = va_arg(argument_ptr, const char *)) != NULL)
			nstrcat(*target_string, this_string, string_length);
	}

	va_end(argument_ptr);

	return(tmp_ptr);
}
/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME        :  strnva_padded_cat

   SYNOPSIS    :  string_ptr = strnva_padded_cat(target_string, string_length,
							left_padding, right_padding, ...);

						char        *string_ptr;

						char       **target_string;

						size_t       string_length;

						const char  *left_padding;

						const char  *right_padding;

   DESCRIPTION :  Allocates memory for and concatenates the specified length
						of each of a variable list of strings to a string.

						Each string so copied may optionally be preceded by a left
						padding string and/or followed by a right padding string.

	PARAMETERS  :  Parameters to this function are as follow:

						(.) ``target_string`` is a pointer to a pointer to char
						into which the concatenation will be performed.

						(-) If ``target_string`` is NULL, then sufficient space to
						hold the string resulting from this function will be
						``malloc``ed.

						(-) If ``target_string`` is not NULL, then this function
						will ``realloc`` sufficient space.

						(.) ``string_length`` is the maximum length of each of the
						``...`` arguments to be concatenated to ``target_string``.

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

   RETURNS     :  A pointer to the string to which ``target_string`` points.

   NOTES       :  If you have already allocated memory to hold
						``target_string``, you may use ``strnv_padded_cat`` instead.

   CAVEATS     :  

   SEE ALSO    :  strnvacat
						strnva_padded_cpy
						strnv_padded_cat
						strva_padded_cat
						strv_padded_cat

	EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT   :  Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:  strnva_padded_cat
						Variable Argument Allocation Concatenation Functions:strnva_padded_cat
						STRFUNCS:Variable Argument Allocation Concatenation Functions:strnva_padded_cat
						String Functions:See STRFUNCS

   PUBLISH XREF:  strnva_padded_cat

   PUBLISH NAME:	strnva_padded_cat

	ENTRY CLASS	:	Variable Argument Allocation Concatenation Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
char *strnva_padded_cat(char **target_string, size_t string_length,
	const char *left_padding, const char *right_padding, ...)
#else
char *strnva_padded_cat(target_string, string_length, left_padding,
	right_padding, va_alist)
char       **target_string;
size_t       string_length;
const char  *left_padding;
const char  *right_padding;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	char         *tmp_ptr;
	const char   *this_string;
	const char   *tmp_left;
	const char   *tmp_right;
	unsigned int  padding_length;
	unsigned int  total_length;
	unsigned int  tmp_length;
	va_list       argument_ptr;

	tmp_left       = (left_padding == NULL)  ? "" : left_padding;
	tmp_right      = (right_padding == NULL) ? "" : right_padding;
	padding_length = strlen(tmp_left) + strlen(tmp_right);

#ifndef NO_STDARGS
	va_start(argument_ptr, right_padding);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	total_length = ((*target_string == NULL) ? 0 : strlen(*target_string)) + 1;
	while ((this_string = va_arg(argument_ptr, const char *)) != NULL)
		total_length += (((tmp_length = strlen(this_string)) > string_length) ?
			string_length : tmp_length) + padding_length;

	if ((tmp_ptr = ((char *) ((*target_string == NULL) ?
		malloc(total_length * sizeof(char)) : realloc(*target_string,
		total_length * sizeof(char))))) != NULL) {
		va_end(*target_string);
#ifndef NO_STDARGS
		va_start(argument_ptr, right_padding);
#else
		va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */
		*target_string  = tmp_ptr;
		while ((this_string = va_arg(argument_ptr, const char *)) != NULL)
			strcat(nstrcat(strcat(*target_string, tmp_left), this_string,
				string_length), tmp_right);
	}

	va_end(argument_ptr);

	return(tmp_ptr);
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
	int   return_code = 1;
	char *string_ptr  = NULL;

	fprintf(stderr, "Test function for 'strnvacat()'\n");
	fprintf(stderr, "---- -------- --- -------------\n\n");

	if (argc != 4)
		fprintf(stderr, "USAGE:\n%s <string> <string> <string>\n\n", argv[0]);
	else {
		string_ptr = strdup(TEST_BASE);
		printf("[%s]\n", strnvacat(&string_ptr, TEST_LENGTH, argv[1], argv[2],
			argv[3], NULL));
		if (string_ptr)
			free(string_ptr);
		string_ptr = NULL;
	}

	fprintf(stderr, "Test function for 'strnva_padded_cat()'\n");
	fprintf(stderr, "---- -------- --- ---------------------\n\n");

	if (argc != 4)
		fprintf(stderr, "USAGE:\n%s <string> <string> <string>\n\n", argv[0]);
	else {
		string_ptr = strdup(TEST_BASE);
		printf("[%s]\n", strnva_padded_cat(&string_ptr, TEST_LENGTH,
			TEST_LEFT_PADDING, TEST_RIGHT_PADDING, argv[1], argv[2], argv[3],
			NULL));
		if (string_ptr)
			free(string_ptr);
		string_ptr  = NULL;
		return_code = 0;
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

