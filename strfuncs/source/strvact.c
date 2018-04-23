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

		Copyright Michael L. Brock 1993 - 2018.
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

   NAME        :  strvacat

   SYNOPSIS    :  string_ptr = strvacat(target_string, ...);

						char  *string_ptr;

						char **target_string;

   DESCRIPTION :  Allocates memory for and concatenates each of a variable
						list of strings to a string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``target_string`` is a pointer to a pointer to char
						into which the concatenation will be performed.

						(-) If ``target_string`` is NULL, then sufficient space to
						hold the string resulting from this function will be
						``malloc``ed.

						(-) If ``target_string`` is not NULL, then this function
						will ``realloc`` sufficient space.

						(.) ``...`` represents subsequent arguments to this function
						(if any) which will be concatenated to the string
						``target_string`` in the order they are encountered.

						(-) Note that the last parameter to this function must be
						``NULL``. This informs the function that no further string
						parameters are to be taken off the stack.

   RETURNS     :  A pointer to the string to which ``target_string`` points.

   NOTES       :  If you have already allocated memory to hold
						``target_string``, you may use ``strvcat`` instead.

   CAVEATS     :  

   SEE ALSO    :  strv_padded_cat
						strvcpy
						strnvacat
						strnvcat
						strvcat

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:  strvacat
						Variable Argument Allocation Concatenation Functions:strvacat
						STRFUNCS:Variable Argument Allocation Concatenation Functions:strvacat
						String Functions:See STRFUNCS

   PUBLISH XREF:  strvacat

	PUBLISH NAME:	strvacat

	ENTRY CLASS	:	Variable Argument Allocation Concatenation Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
char *strvacat(char **target_string, ...)
#else
char *strvacat(target_string, va_alist)
char **target_string;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	char         *tmp_ptr;
	const char   *this_string;
	unsigned int  total_length;
	va_list       argument_ptr;

#ifndef NO_STDARGS
	va_start(argument_ptr, target_string);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	total_length = ((*target_string == NULL) ? 0 : strlen(*target_string)) + 1;
	while ((this_string = va_arg(argument_ptr, const char *)) != NULL)
		total_length += strlen(this_string);

	if ((tmp_ptr = ((char *) ((*target_string == NULL) ?
		malloc(total_length * sizeof(char)) : realloc(*target_string,
		total_length * sizeof(char))))) != NULL) {
		va_end(*target_string);
#ifndef NO_STDARGS
		va_start(argument_ptr, target_string);
#else
		va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */
		if (*target_string == NULL) 
			*tmp_ptr = '\0';
		*target_string = tmp_ptr;
		while ((this_string = va_arg(argument_ptr, const char *)) != NULL)
			strcat(*target_string, this_string);
	}

	va_end(argument_ptr);

	return(tmp_ptr);
}
/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME        :  strva_padded_cat

   SYNOPSIS    :  string_ptr = strva_padded_cat(target_string, left_padding,
							right_padding, ...);

						char        *string_ptr;

						char       **target_string;

						const char  *left_padding;

						const char  *right_padding;

   DESCRIPTION :  Allocates memory for and concatenates each of a variable
						list of strings to a string.

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
						``target_string``, you may use ``strv_padded_car`` instead.

   CAVEATS     :  

   SEE ALSO    :  strvcat
						strv_padded_cpy
						strnva_padded_cat
						strnv_padded_cat
						strv_padded_cat

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:  strva_padded_cat
						Variable Argument Allocation Concatenation Functions:strva_padded_cat
						STRFUNCS:Variable Argument Allocation Concatenation Functions:strva_padded_cat
						String Functions:See STRFUNCS

	PUBLISH XREF:  strva_padded_cat

   PUBLISH NAME:	strva_padded_cat

	ENTRY CLASS	:	Variable Argument Allocation Concatenation Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
char *strva_padded_cat(char **target_string, const char *left_padding,
	const char *right_padding, ...)
#else
char *strva_padded_cat(target_string, left_padding, right_padding, va_alist)
char       **target_string;
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
		total_length += strlen(this_string) + padding_length;

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
			strcat(strcat(strcat(*target_string, tmp_left), this_string),
				tmp_right);
	}

	va_end(argument_ptr);

	return(tmp_ptr);
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
	int   return_code = 1;
	char *string_ptr  = NULL;

	fprintf(stderr, "Test function for 'strvacat()'\n");
	fprintf(stderr, "---- -------- --- ------------\n\n");

	if (argc != 4)
		fprintf(stderr, "USAGE:\n%s <string> <string> <string>\n\n", argv[0]);
	else {
		string_ptr = strdup(TEST_BASE);
		printf("[%s]\n", strvacat(&string_ptr, argv[1], argv[2], argv[3], NULL));
		if (string_ptr)
			free(string_ptr);
		string_ptr = NULL;
	}

	fprintf(stderr, "Test function for 'strva_padded_cat()'\n");
	fprintf(stderr, "---- -------- --- --------------------\n\n");

	if (argc != 4)
		fprintf(stderr, "USAGE:\n%s <string> <string> <string>\n\n", argv[0]);
	else {
		string_ptr = strdup(TEST_BASE);
		printf("[%s]\n", strva_padded_cat(&string_ptr, TEST_LEFT_PADDING,
			TEST_RIGHT_PADDING, argv[1], argv[2], argv[3], NULL));
		if (string_ptr)
			free(string_ptr);
		string_ptr  = NULL;
		return_code = 0;
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

