/* *********************************************************************** */
/* *********************************************************************** */
/* STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Transforms a string into an array of pointers into
								strings using a specified set of separation
								characters.

	Revision History	:	1992-06-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
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

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  sepwordx

   SYNOPSIS    :  return_code = sepwordx(in_string, separator_list,
							string_count, string_list);

						unsigned int    return_code;

						const char     *in_string;

						const char     *separator_list;

						unsigned int   *string_count;

						char         ***string_list;

   DESCRIPTION :  Transforms a string into an array of pointers to strings.
						The transformation is effected by examining the string for
						the presence of separation characters. Strings composed of
						characters not in the set of separation characters will
						become elements in the array of pointers to strings created
						by this function.

						Separation characters are specified as being one of the
						characters in the parameter ``separator_list``.

						Multiple instances of the separation characters are
						swallowed by this function.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string to be transformed into an
						array of pointers to strings.

						(.) ``separator_list`` is the ASCII NUL terminated string
						which contains the characters which separate portions of
						the string ``in_string`` to be transformed into array
						elements.

						(-) If ``separator_list`` is ''NULL'' or is a zero-length
						string, ``in_string`` will be copied in its entirety to
						the array ``string_list``.

						(.) ``string_count`` points to an integer which will
						contain the number of records in the destination list
						``string_list`` if this function is successful.

						(.) ``string_list`` points to the list to which string
						segments from ``in_string`` are to be copied. Memory will
						be allocated for this list by this function.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  Multiple instances of the separation characters are
						swallowed by this function. If you want to keep them as
						empty strings in the resulting list, use the associated
						function ``sepwordx_keep``.

						To separate a string by white-space characters (as defined
						by the C standard library macro ``isspace``), use the
						function ``sepwordl`` instead.

   CAVEATS     :  

   SEE ALSO    :  sepwordc
						sepwordl
						sepwords
						sepwordx_keep

	EXAMPLES    :

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	sepwordx
						String Splitting Functions:sepwordx
						STRFUNCS:String Splitting Functions:sepwordx
						String Functions:See STRFUNCS

	PUBLISH XREF:	sepwordx

	PUBLISH NAME:	sepwordx

	ENTRY CLASS	:	String Splitting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int sepwordx(const char *in_string, const char *separator_list,
	unsigned int *string_count, char ***string_list)
#else
int sepwordx(in_string, separator_list, string_count, string_list)
const char     *in_string;
const char     *separator_list;
unsigned int   *string_count;
char         ***string_list;
#endif /* #ifndef NARGS */
{
	int   return_code = STRFUNCS_SUCCESS;
	char *tmp_ptr_1;

	*string_count = 0;
	*string_list  = NULL;

	if ((in_string != NULL) && *in_string) {
		if ((separator_list == NULL) || (!*separator_list))
			return_code = strl_append(string_count, string_list, in_string);
		else if (!(*(separator_list + 1)))
			return_code = sepwordc(in_string, *separator_list, string_count,
				string_list);
		else {
			while (*in_string) {
				if (strchr(separator_list, *in_string) == NULL) {
					tmp_ptr_1 = ((char *) in_string);
					while (*tmp_ptr_1 && (!strchr(separator_list, *tmp_ptr_1)))
						tmp_ptr_1++;
					if ((return_code = meml_append(string_count,
						((void ***) string_list), in_string, ((unsigned int)
						(tmp_ptr_1 - ((char *) in_string))) + 1)) !=
						STRFUNCS_SUCCESS)
						goto EXIT_FUNCTION;
					(*string_list)[*string_count - 1]
						[((unsigned int) (tmp_ptr_1 - ((char *) in_string)))] =
						'\0';
					if (!(*(in_string = tmp_ptr_1)))
						break;
				}
				in_string++;
			}
		}
	}

EXIT_FUNCTION:

	if (return_code != STRFUNCS_SUCCESS)
		strl_remove(string_count, string_list, 0, *string_count);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  sepwordx_keep

   SYNOPSIS    :  return_code = sepwordx_keep(in_string, separator_list,
							string_count, string_list);

						unsigned int    return_code;

						const char     *in_string;

						const char     *separator_list;

						unsigned int   *string_count;

						char         ***string_list;

   DESCRIPTION :  Transforms a string into an array of pointers to strings.
						The transformation is effected by examining the string for
						the presence of separation characters. Strings composed of
						characters not in the set of separation characters will
						become elements in the array of pointers to strings created
						by this function.

						Separation characters are specified as being one of the
						characters in the parameter ``separator_list``.

						Multiple instances of the separation characters are
						propagated by this function into the array ``string_list``
						as empty strings.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string to be transformed into an
						array of pointers to strings.

						(.) ``separator_list`` is the ASCII NUL terminated string
						which contains the characters which separate portions of
						the string ``in_string`` to be transformed into array
						elements.

						(-) If ``separator_list`` is ''NULL'' or is a zero-length
						string, ``in_string`` will be copied in its entirety to
						the array ``string_list``.

						(.) ``string_count`` points to an integer which will
						contain the number of records in the destination list
						``string_list`` if this function is successful.

						(.) ``string_list`` points to the list to which string
						segments from ``in_string`` are to be copied. Memory will
						be allocated for this list by this function.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  If ``separator_list`` is ''NULL'' or is a zero-length
						string, ``in_string`` will be copied in its entirety to
						the array ``string_list``.

						Multiple instances of the separation characters are
						propagated by this function into the array ``string_list``
						as empty strings. If you do not want to keep them as
						empty strings in the resulting list, use the associated
						function ``sepwordx``.

   CAVEATS     :  

   SEE ALSO    :  sepwordl
						sepwords
						sepwordx
						sepwordc_keep

	EXAMPLES    :

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	sepwordx_keep
						String Splitting Functions:sepwordx_keep
						STRFUNCS:String Splitting Functions:sepwordx_keep
						String Functions:See STRFUNCS

	PUBLISH XREF:	sepwordx_keep

	PUBLISH NAME:	sepwordx_keep

	ENTRY CLASS	:	String Splitting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int sepwordx_keep(const char *in_string, const char *separator_list,
	unsigned int *string_count, char ***string_list)
#else
int sepwordx_keep(in_string, separator_list, string_count, string_list)
const char     *in_string;
const char     *separator_list;
unsigned int   *string_count;
char         ***string_list;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned int  leading_count;
	char         *tmp_ptr_1;

	*string_count = 0;
	*string_list  = NULL;

	if ((in_string != NULL) && *in_string) {
		if ((separator_list == NULL) || (!*separator_list))
			return_code = strl_append(string_count, string_list, in_string);
		else if (!(*(separator_list + 1)))
			return_code = sepwordc_keep(in_string, *separator_list, string_count,
				string_list);
		else {
			leading_count = 0;
			while (*in_string && (strchr(separator_list, *in_string) != NULL)) {
				in_string++;
				leading_count++;
			}
			if (leading_count && ((return_code = meml_allocate(string_count,
				((void ***) string_list), 1,
				leading_count + ((*in_string) ? 0 : 1))) != STRFUNCS_SUCCESS))
				goto EXIT_FUNCTION;
			while (*in_string) {
				if (strchr(separator_list, *in_string) == NULL) {
					tmp_ptr_1 = ((char *) in_string);
					while (*tmp_ptr_1 && (!strchr(separator_list, *tmp_ptr_1)))
						tmp_ptr_1++;
					if ((return_code = meml_append(string_count,
						((void ***) string_list), in_string, ((unsigned int)
						(tmp_ptr_1 - ((char *) in_string))) + 1)) !=
						STRFUNCS_SUCCESS)
						goto EXIT_FUNCTION;
					(*string_list)[*string_count - 1]
						[((unsigned int) (tmp_ptr_1 - ((char *) in_string)))] =
						'\0';
					if (!(*(in_string = tmp_ptr_1)))
						break;
				}
				if ((strchr(separator_list, *(in_string + 1)) != NULL) ||
					(!(*(in_string + 1)))) {
					if ((return_code = strl_append(string_count, string_list,
						"")) != STRFUNCS_SUCCESS)
						break;
				}
				in_string++;
			}
		}
	}

EXIT_FUNCTION:

	if (return_code != STRFUNCS_SUCCESS)
		strl_remove(string_count, string_list, 0, *string_count);

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));
COMPAT_FN_DECL_STATIC(void DoUsage,
	(char *, char *, int));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int            return_code   = 0;
	unsigned int   string_count  = 0;
	char         **string_list   = NULL;
	char          *separator_ptr = NULL;
	unsigned int   count_1;
	unsigned int   count_2;

	fprintf(stderr, "Test routine for 'sepwordx()'\n");
	fprintf(stderr, "                 'sepwordx_keep()'\n");
	fprintf(stderr, "---- ------- --- -----------------\n\n");

	if (argc < 2)
		DoUsage(argv[0], "Invalid command-line encountered.", 1);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp("-HELP", argv[count_1])) ||
			(!stricmp("-H", argv[count_1])))
			DoUsage(argv[0], "Help request noted.", 0);
		else if (!strnicmp(argv[count_1], "-SEPARATOR=", 11)) {
			if ((strlen(argv[count_1]) < 12) ||
				(!(*(separator_ptr = trimx(argv[count_1] + 11, "\"'`")))))
				DoUsage(argv[0], "Invalid use of '-SEPARATOR[S]=' qualifer.", 1);
			printf("SEPARATOR: [%s]\n", separator_ptr);
		}
		else if (!strnicmp(argv[count_1], "-SEPARATORS=", 12)) {
			if ((strlen(argv[count_1]) < 13) ||
				(!(*(separator_ptr = trimx(argv[count_1] + 12, "\"'`")))))
				DoUsage(argv[0], "Invalid use of '-SEPARATOR[S]=' qualifer.", 1);
			printf("SEPARATOR: [%s]\n", separator_ptr);
		}
		else if ((!separator_ptr) || (!*separator_ptr))
			DoUsage(argv[0], "No '-SEPARATOR=' qualifer encountered.", 1);
		else {
			printf("TEST : [%s]\n", argv[count_1]);
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			printf("Test of 'sepwordx()'\n");
			STR_EMIT_CharLine('-', 78, NULL, NULL);
			if (sepwordx(argv[count_1], separator_ptr, &string_count,
				&string_list)) {
				fprintf(stderr,
					"ERROR ON SEPARATION ATTEMPT 'sepwordx()'\n\n");
				return_code = 1;
				break;
			}
			for (count_2 = 0; count_2 < string_count; count_2++)
				printf("%05u: [%s]\n", count_2, string_list[count_2]);
			strl_remove(&string_count, &string_list, 0, string_count);
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			printf("Test of 'sepwordx_keep()'\n");
			STR_EMIT_CharLine('-', 78, NULL, NULL);
			if (sepwordx_keep(argv[count_1], separator_ptr, &string_count,
				&string_list)) {
				fprintf(stderr,
					"ERROR ON SEPARATION ATTEMPT 'sepwordx_keep()'\n\n");
				return_code = 1;
				break;
			}
			for (count_2 = 0; count_2 < string_count; count_2++)
				printf("%05u: [%s]\n", count_2, string_list[count_2]);
			strl_remove(&string_count, &string_list, 0, string_count);
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			printf("\n");
		}
	}

	return(return_code);
}

#ifndef NARGS
static void DoUsage(char *prog, char *exit_text, int exit_code)
#else
static void DoUsage(prog, exit_text, exit_code)
char *prog;
char *exit_text;
int   exit_code;
#endif /* #ifndef NARGS */
{
	prog = (strchr(prog, '\\')) ? strchr(prog, '\\') + 1 : prog;

	if (*exit_text)
		fprintf(stderr, "%s\n\n", exit_text);

	fprintf(stderr,
		"USAGE: %s [-SEPARATOR[S]=[\"]<separator-string>[\"]] %s\n\n",
		prog, "<test-string> [<test-string> . . .]");

	exit(exit_code);
}

#endif /* #ifdef TEST_MAIN */

