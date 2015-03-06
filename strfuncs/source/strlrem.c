/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes elements from an array of pointers to strings.

	Revision History	:	1991-09-13 --- Creation
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

   NAME        :  strl_remove

   SYNOPSIS    :  return_code = strl_remove(string_count, string_list,
							first_element, element_count);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

						unsigned int    first_element;

						unsigned int    element_count;

   DESCRIPTION :  Deletes an array element from an array of pointers to
						strings.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to integer which contains the
						number of elements in the array to which ``string_list``
						points.

						(-) If the function succeeds in deleting the specified
						elements then that integer will have subtracted from it
						the number of elements deleted.

						(.) ``string_list`` is a triply-indirect pointer to ``char``
						(``char ***``) which contains the array. If the function
						succeeds in deleting elements then the memory pointed to
						by ``string_list`` will be re-allocated to hold the new size
						of the array.

						(.) ``first_element`` is the array index of the first
						element to be deleted.

						(-) If ``first_element`` exceeds the array index of the
						last array element (that is, if ``first_element`` is
						greater that or equal to ``*string_count``) no work will
						be performed by this function.

						(.) ``element_count`` is the number of elements to be
						deleted.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  strl_remove_all
						meml_remove

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  strl_remove
						String List Functions:strl_remove
						STRFUNCS:String List Functions:strl_remove
						String Functions:See STRFUNCS

   PUBLISH XREF:  strl_remove

   PUBLISH NAME:	strl_remove

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int strl_remove(unsigned int *string_count, char ***string_list,
	unsigned int first_element, unsigned int element_count)
#else
int strl_remove(string_count, string_list, first_element, element_count)
unsigned int   *string_count;
char         ***string_list;
unsigned int    first_element;
unsigned int    element_count;
#endif /* #ifndef NARGS */
{
	return(meml_remove(string_count, ((void ***) string_list), first_element,
		element_count));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strl_remove_all

   SYNOPSIS    :  return_code = strl_remove_all(string_count, string_list);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

   DESCRIPTION :  Deletes all elements from an array of pointers to strings.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to integer which contains the
						number of elements in the array to which ``string_list``
						points.

						(.) ``string_list`` is a triply-indirect pointer to ``char``
						(``char ***``) which contains the array to be deleted.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  strl_remove
						meml_remove_all

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  strl_remove_all
						String List Functions:strl_remove_all
						STRFUNCS:String List Functions:strl_remove_all
						String Functions:See STRFUNCS

   PUBLISH XREF:  strl_remove_all

   PUBLISH NAME:	strl_remove_all

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int strl_remove_all(unsigned int *string_count, char ***string_list)
#else
int strl_remove_all(string_count, string_list)
unsigned int   *string_count;
char         ***string_list;
#endif /* #ifndef NARGS */
{
	return(meml_remove_all(string_count, ((void ***) string_list)));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strldel

   SYNOPSIS    :  return_code = strldel(string_count, string_list,
							first_element, element_count);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

						unsigned int    first_element;

						unsigned int    element_count;

   DESCRIPTION :  Deletes an array element from an array of pointers to
						strings.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to integer which contains the
						number of elements in the array to which ``string_list``
						points.

						(-) If the function succeeds in deleting the specified
						elements then that integer will have subtracted from it
						the number of elements deleted.

						(.) ``string_list`` is a triply-indirect pointer to ``char``
						(``char ***``) which contains the array. If the function
						succeeds in deleting elements then the memory pointed to
						by ``string_list`` will be re-allocated to hold the new size
						of the array.

						(.) ``first_element`` is the array index of the first
						element to be deleted.

						(-) If ``first_element`` exceeds the array index of the
						last array element (that is, if ``first_element`` is
						greater that or equal to ``*string_count``) no work will
						be performed by this function.

						(.) ``element_count`` is the number of elements to be
						deleted.

   NOTES       :  This function does no more than call the function
						``strl_remove``. It is retained for purposes of
						compatibility with legacy code.

   CAVEATS     :  

   SEE ALSO    :  strl_remove

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  strldel
						String List Functions:strldel
						STRFUNCS:String List Functions:strldel
						String Functions:See STRFUNCS

   PUBLISH XREF:  strldel

   PUBLISH NAME:	strldel

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int strldel(unsigned int *string_count, char ***string_list,
	unsigned int first_element, unsigned int element_count)
#else
int strldel(string_count, string_list, first_element, element_count)
unsigned int   *string_count;
char         ***string_list;
unsigned int    first_element;
unsigned int    element_count;
#endif /* #ifndef NARGS */
{
	return(strl_remove(string_count, string_list, first_element,
		element_count));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *********************************************************************** */
COMPAT_FN_DECL(int main, (int argc, char **argv));
COMPAT_FN_DECL_STATIC(int TEST_DoDelete, (const char *in_name,
	unsigned int string_count, char **string_list, unsigned int first_element,
	unsigned int element_count, char *error_text));
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int            return_code     = STRFUNCS_SUCCESS;
	unsigned int   element_count   = 100;
	unsigned int   iteration_count = 100;
	unsigned int   string_count    = 0;
	char         **string_list     = NULL;
	unsigned int   count_1;
	char           buffer[STR_VAL2STR_MAX_LEN + 1];
	char           error_text[STRFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'strl_remove()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------------\n\n");

	for (count_1 = 0; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-H")) ||
			(!stricmp(argv[count_1], "-HELP"))) {
			fprintf(stderr, "USAGE:\n   %s %s\n\n",
				argv[0],
				"[ -h | -help ] | [ <element-count> [ <iteration-count> ] ]");
			return_code = STRFUNCS_SUCCESS;
			goto EXIT_FUNCTION;
		}
	}

	if (argc > 3) {
		strcpy(error_text, "Invalid command-line --- use '-h' for help.");
		return_code = STRFUNCS_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (argc > 1) {
		if (str_digit(argv[1], 0) != NULL) {
			sprintf(error_text, "%s ('%-.500s') is not numeric.",
				"The <element-count> parameter", argv[1]);
			return_code = STRFUNCS_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		else if (atoi(argv[1]) < 1) {
			sprintf(error_text, "%s ('%-.500s') %s %u, inclusive.",
				"The <element-count> parameter", argv[1],
				"is not in the range of 1 to", UINT_MAX);
			return_code = STRFUNCS_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		element_count = atoi(argv[1]);
		if (argc > 2) {
			if (str_digit(argv[2], 0) != NULL) {
				sprintf(error_text, "%s ('%-.500s') is not numeric.",
					"The <iteration-count> parameter", argv[2]);
				return_code = STRFUNCS_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if (atoi(argv[2]) < 1) {
				sprintf(error_text, "%s ('%-.500s') %s %u, inclusive.",
				"The <iteration-count> parameter", argv[2],
					"is not in the range of 1 to", UINT_MAX);
				return_code = STRFUNCS_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			iteration_count = atoi(argv[2]);
		}
	}

	fprintf(stderr, "================ ==========\n");
	fprintf(stderr, "Element Count  : %10u\n", element_count);
	fprintf(stderr, "Iteration Count: %10u\n", iteration_count);
	fprintf(stderr, "================ ==========\n\n");

	fprintf(stderr, "Creating a string list of %u elements ", element_count);
	for (count_1 = 0; count_1 < element_count; count_1++) {
		if ((return_code = strl_append(&string_count, &string_list,
			val2str_uint(count_1, 10, "0", buffer))) != STRFUNCS_SUCCESS) {
			sprintf(error_text, "%s %u to the string list.",
				"Unable to append element index", count_1);
			goto EXIT_FUNCTION;
		}
		if (!(count_1 % 10000))
			fprintf(stderr, ".");
	}
	fprintf(stderr, ". done\n");

	fprintf(stderr, "Performing %u iterations of the deletion tests ",
		iteration_count);
	for (count_1 = 0; count_1 < iteration_count; count_1++) {
		if ((return_code = TEST_DoDelete("Remove all",
			string_count, string_list, 0, element_count, error_text)) !=
			STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = TEST_DoDelete("Remove last",
			string_count, string_list, element_count - 1, element_count,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;

		if ((return_code = TEST_DoDelete("Remove one first after last",
			string_count, string_list, element_count, 1,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = TEST_DoDelete("Remove two first after last",
			string_count, string_list, element_count, 2,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;

		if ((return_code = TEST_DoDelete("Remove all first after last",
			string_count, string_list, element_count, element_count,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = TEST_DoDelete("Remove all second after last",
			string_count, string_list, element_count + 1, element_count,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;

		if ((return_code = TEST_DoDelete("Remove all from empty list",
			0, NULL, 0, element_count,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = TEST_DoDelete("Remove all but first from empty list",
			0, NULL, 1, element_count,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = TEST_DoDelete("Remove last from empty list",
			0, NULL, element_count - 1, 1,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = TEST_DoDelete("Remove all from last from empty list",
			0, NULL, element_count - 1, element_count,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = TEST_DoDelete("Remove all after first from empty list",
			0, NULL, element_count, element_count,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;

		if ((return_code = TEST_DoDelete("Remove all after first",
			string_count, string_list, 1, element_count,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = TEST_DoDelete("Remove all after second",
			string_count, string_list, 2, element_count,
			error_text)) != STRFUNCS_SUCCESS)
			goto EXIT_FUNCTION;



		if (!(count_1 % 10000))
			fprintf(stderr, ".");
	}
	fprintf(stderr, ". done\n");

EXIT_FUNCTION:

	strl_remove_all(&string_count, &string_list);

	if (return_code != STRFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int TEST_DoDelete(const char *in_name, unsigned int string_count,
	char **string_list, unsigned int first_element, unsigned int element_count,
	char *error_text)
#else
static int TEST_DoDelete(in_name, string_count, string_list, first_element,
	element_count, error_text)
const char    *in_name;
unsigned int   string_count;
char         **string_list;
unsigned int   first_element;
unsigned int   element_count;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   tmp_count;
	char         **tmp_list;

	if ((return_code = strl_copy(string_count, string_list, &tmp_count,
		&tmp_list)) == STRFUNCS_SUCCESS) {
		if ((return_code = strl_remove(&tmp_count, &tmp_list, first_element,
			element_count)) != STRFUNCS_SUCCESS)
			sprintf(error_text,
"%s attempt failed: %s %d %s 'strl_remove(%s=%p=*%u, %s=%p=*%p, %s=%u, %s=%u)'.", 
				in_name, "Return code", return_code, "on attempt to copy list with",
				"&string_count", &tmp_count, tmp_count,
				"&string_list", &tmp_list, tmp_list,
				"first_element", first_element,
				"element_count", element_count);
		strl_remove_all(&tmp_count, &tmp_list);
	}
	else
		sprintf(error_text,
			"%s attempt failed: Return code %d on attempt to copy list.",
			in_name, return_code);

	return(return_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */


