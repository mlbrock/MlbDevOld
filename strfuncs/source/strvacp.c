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

#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME        :  strvacpy

   SYNOPSIS    :  string_ptr = strvacpy(target_string, ...);

						char  *string_ptr;

						char **target_string;

   DESCRIPTION :  Allocates memory for and copies each of a variable list of
						strings to a string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``target_string`` is a pointer to a pointer to char
						into which the copy will be performed.

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
						``target_string``, you may use ``strvcpy`` instead.

   CAVEATS     :  

   SEE ALSO    :  strv_padded_cpy
						strvcat
						strnvacpy
						strnvcpy
						strvcpy

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2015 Michael L. Brock

   OUTPUT INDEX:  strvacpy
						Variable Argument Allocation Copy Functions:strvacpy
						STRFUNCS:Variable Argument Allocation Copy Functions:strvacpy
						String Functions:See STRFUNCS

   PUBLISH XREF:  strvacpy

   PUBLISH NAME:	strvacpy

	ENTRY CLASS	:	Variable Argument Allocation Copy Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
char *strvacpy(char **target_string, ...)
#else
char *strvacpy(target_string, va_alist)
char **target_string;
va_dcl
#endif /* #ifndef NO_STDARGS */          
{
	char         *tmp_ptr;
	const char   *this_string;
	unsigned int  total_length = 1;
	va_list       argument_ptr;

#ifndef NO_STDARGS
	va_start(argument_ptr, target_string);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */          

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
		*target_string  = tmp_ptr;
		**target_string = '\0';
		while ((this_string = va_arg(argument_ptr, const char *)) != NULL)
			strcat(*target_string, this_string);
	}

	va_end(*target_string);

	return(tmp_ptr);
}
/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME        :  strva_padded_cpy

	SYNOPSIS    :  string_ptr = strva_padded_cpy(target_string, left_padding,
							right_padding, ...);

						char        *string_ptr;

						char       **target_string;

						const char  *left_padding;

						const char  *right_padding;

   DESCRIPTION :  Allocates memory for and copies each of a variable list of
						strings to a string.

						Each string so copied may optionally be preceded by a left
						padding string and/or followed by a right padding string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``target_string`` is a pointer to a pointer to char
						into which the copy will be performed.

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
						``target_string``, you may use ``strv_padded_cpy`` instead.

	CAVEATS     :  

   SEE ALSO    :  strvcpy
						strv_padded_cat
						strnva_padded_cpy
						strnv_padded_cpy
						strv_padded_cpy

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2015 Michael L. Brock

   OUTPUT INDEX:  strva_padded_cpy
						Variable Argument Allocation Copy Functions:strva_padded_cpy
						STRFUNCS:Variable Argument Allocation Copy Functions:strva_padded_cpy
						String Functions:See STRFUNCS

   PUBLISH XREF:  strva_padded_cpy

   PUBLISH NAME:	strva_padded_cpy

	ENTRY CLASS	:	Variable Argument Allocation Copy Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
# ifndef NO_STDARGS
char *strva_padded_cpy(char **target_string, const char *left_padding,
	const char *right_padding, ...)
#else
char *strva_padded_cpy(target_string, left_padding, right_padding, va_alist)
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
	unsigned int  total_length = 1;
	va_list       argument_ptr;

	tmp_left       = (left_padding == NULL)  ? "" : left_padding;
	tmp_right      = (right_padding == NULL) ? "" : right_padding;
	padding_length = strlen(tmp_left) + strlen(tmp_right);

#ifndef NO_STDARGS
	va_start(argument_ptr, right_padding);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

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
		**target_string = '\0';
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

	fprintf(stderr, "Test function for 'strvacpy()'\n");
	fprintf(stderr, "---- -------- --- ------------\n\n");

	if (argc != 4)
		fprintf(stderr, "USAGE:\n%s <string> <string> <string>\n\n", argv[0]);
	else {
		printf("[%s]\n", strvacpy(&string_ptr, argv[1], argv[2], argv[3], NULL));
		if (string_ptr)
			free(string_ptr);
		string_ptr = NULL;
	}

	fprintf(stderr, "Test function for 'strva_padded_cpy()'\n");
	fprintf(stderr, "---- -------- --- --------------------\n\n");

	if (argc != 4)
		fprintf(stderr, "USAGE:\n%s <string> <string> <string>\n\n", argv[0]);
	else {
		printf("[%s]\n", strva_padded_cpy(&string_ptr, TEST_LEFT_PADDING,
			TEST_RIGHT_PADDING, argv[1], argv[2], argv[3], NULL));
		if (string_ptr)
			free(string_ptr);
		string_ptr  = NULL;
		return_code = 0;
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

