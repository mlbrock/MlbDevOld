/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Provides command-line argument parsing.

	Revision History	:	1994-07-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* ***********************************************************************	*/
/* ***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/* ***********************************************************************	*/

#include <string.h>

#include <strfuncs.h>

#include "genfunci.h"

/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ArgParse

   SYNOPSIS    :  return_code = GEN_ArgParse(in_param_ptr, out_param_length,
							out_data_ptr, ...);

						int            return_code;

						const char    *in_param_ptr;

						unsigned int  *out_param_length;

						char         **out_data_ptr;

						...

   DESCRIPTION :  Parses a parameter by matching the parameter string against
						a string passed in a variable argument list.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_param_ptr`` points to the parameter to be parsed.

						(.) ``out_param_length`` points to an ''unsigned int'' into
						which the length of the string which matched the beginning
						of the parameter will be placed, if found.

						(.) ``out_data_ptr`` points to a pointer to char into which
						will be placed a pointer to the portion of the parameter in
						``in_param_ptr`` which follows the matched string.

						(.) ``...`` represents the variable argument list of strings
						which are to be matched against ``in_param_ptr``.

						(-) The variable argument list must be followed by a
						''NULL'' pointer to indicate that no further variable
						arguments are to be expected by the function.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

	NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ArgParseList

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:  GEN_ArgParse
						Argument Parsing Functions:GEN_ArgParse
						GENFUNCS:Functions:GEN_ArgParse
						GENFUNCS:Argument Parsing Functions:GEN_ArgParse
						General Functions:See GENFUNCS

   PUBLISH XREF:  GEN_ArgParse

   PUBLISH NAME:	GEN_ArgParse

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
int GEN_ArgParse(const char *in_param_ptr, unsigned int *out_param_length,
	char **out_data_ptr, ...)
#else
int GEN_ArgParse(in_param_ptr, out_param_length, out_data_ptr, va_alist)
const char    *in_param_ptr;
unsigned int  *out_param_length;
char         **out_data_ptr;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int         return_code = GENFUNCS_FALSE;
	const char *this_string;
	va_list     argument_ptr;

	*out_param_length = 0;
	*out_data_ptr     = NULL;

#ifndef NO_STDARGS
	va_start(argument_ptr, out_data_ptr);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	while ((this_string = va_arg(argument_ptr, const char *)) != NULL) {
		if (!strnicmp(in_param_ptr, this_string, strlen(this_string))) {
			*out_param_length = strlen(this_string);
			*out_data_ptr     = ((char *) in_param_ptr) + *out_param_length;
			return_code       = GENFUNCS_TRUE;
			break;
		}
	}

	va_end(argument_ptr);

	return(return_code);
}
/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ArgParseList

   SYNOPSIS    :	return_code = GEN_ArgParseList(parse_count, parse_list,
							in_param_ptr, out_param_length, out_data_ptr);

						int            return_code;

						unsigned int   parse_count;

						const char   **parse_list;

						const char    *in_param_ptr;

						unsigned int  *out_param_length;

						char         **out_data_ptr;

   DESCRIPTION :  Parses a parameter by matching the parameter string against
						an array of pointers to strings.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``parse_count`` is the number of elements in the array
						``parse_list``.

						(.) ``parse_list`` is the array of strings which are to be
						matched against ``in_param_ptr``.

						(.) ``in_param_ptr`` points to the parameter to be parsed.

						(.) ``out_param_length`` points to an ''unsigned int'' into
						which the length of the string which matched the beginning
						of the parameter will be placed, if found.

						(.) ``out_data_ptr`` points to a pointer to char into which
						will be placed a pointer to the portion of the parameter in
						``in_param_ptr`` which follows the matched string.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ArgParse

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:  GEN_ArgParseList
						Argument Parsing Functions:GEN_ArgParseList
						GENFUNCS:Functions:GEN_ArgParseList
						GENFUNCS:Argument Parsing Functions:GEN_ArgParseList
						General Functions:See GENFUNCS

   PUBLISH XREF:  GEN_ArgParseList

   PUBLISH NAME:	GEN_ArgParseList

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ArgParseList(unsigned int parse_count, const char **parse_list,
	const char *in_param_ptr, unsigned int *out_param_length,
	char **out_data_ptr)
#else
int GEN_ArgParseList(parse_count, parse_list, in_param_ptr, out_param_length,
	out_data_ptr)
unsigned int   parse_count;
const char   **parse_list;
const char    *in_param_ptr;
unsigned int  *out_param_length;
char         **out_data_ptr;
#endif /* #ifndef NARGS */
{
	int          return_code = GENFUNCS_FALSE;
	unsigned int count_1;

	*out_param_length = 0;
	*out_data_ptr     = NULL;

	for (count_1 = 0; count_1 < parse_count; count_1++) {
		if (!strnicmp(in_param_ptr, parse_list[count_1],
			strlen(parse_list[count_1]))) {
			*out_param_length = strlen(parse_list[count_1]);
			*out_data_ptr     = ((char *) in_param_ptr) + *out_param_length;
			return_code       = GENFUNCS_TRUE;
			break;
		}
	}

	return(return_code);
}
/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ArgParseTruth

   SYNOPSIS    :  return_code = GEN_ArgParseTruth(in_param_ptr, error_flag,
							truth_flag, error_text, out_param_length, out_data_ptr,
							...);

						int            return_code;

						const char    *in_param_ptr;

						int           *error_flag;

						int           *truth_flag;

						char          *error_text;

						unsigned int  *out_param_length;

						char         **out_data_ptr;

						...

   DESCRIPTION :  Parses a parameter by matching the parameter string against
						a string passed in a variable argument list.

						If a match is found, the parameter value is parsed to
						determine its Boolean truth value within the following
						domains:

						(.) For ''TRUE'':

						<|-|>''{''TRUE''|''ON''|''YES''|''T''|''Y''|''1''}''

						(.) and for ''FALSE'':

						<|-|>''{''FALSE''|''OFF''|''NO''|''F''|''N''|''0''}''

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_param_ptr`` points to the parameter to be parsed.

						(.) ``error_flag`` points to an ''int'' into which will be
						placed an indication of an error, should one occur. The
						indication will take the form of the value of one of the
						following mainfest constants:

						(..) ''GENFUNCS_TRUE'' if an error occurred. In this case,
						text describing the error will be placed in the string to
						which the ``error_text`` parameter points.

						(..) ''GENFUNCS_FALSE'' if no error occurred.

						(.) ``truth_flag`` points to an ''int'' into which will be
						placed the value of the parameter parsed by the function.

						(..) If the value of the parameter is one of ''ON'', ''YES'',
						or ''TRUE'', then ``truth_flag`` will be set to the value
						of the manifest constant ''GENFUNCS_TRUE''.

						(..) If the value of the parameter is one of ''OFF'', ''NO'',
						or ''FALSE'', then ``truth_flag`` will be set to the value
						of the manifest constant ''GENFUNCS_FALSE''.

						(.) ``error_text`` points to a string into which text which
						describes any error which may occur will be placed by the
						function.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

						(.) ``out_param_length`` points to an ''unsigned int'' into
						which the length of the string which matched the beginning
						of the parameter will be placed, if found.

						(.) ``out_data_ptr`` points to a pointer to char into which
						will be placed a pointer to the portion of the parameter in
						``in_param_ptr`` which follows the matched string.

						(.) ``...`` represents the variable argument list of strings
						which are to be matched against ``in_param_ptr``.

						(-) The variable argument list must be followed by a
						''NULL'' pointer to indicate that no further variable
						arguments are to be expected by the function.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :  If this function returns ''GENFUNCS_TRUE'' that is only an
						indication that the parameter was matched against one of
						strings in the list. You must then check the integer to
						which the ``error_flag`` parameter points to determine
						whether the parameter value was valid.

						If ``error_flag`` is equal to ''GENFUNCS_FALSE'', then the
						integer to which the ``truth_flag`` points will contain the
						manifest constant equivalent of the parameter value.

	CAVEATS     :  

   SEE ALSO    :  GEN_ArgParseListTruth

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:  GEN_ArgParseTruth
						Argument Parsing Functions:GEN_ArgParseTruth
						GENFUNCS:Functions:GEN_ArgParseTruth
						GENFUNCS:Argument Parsing Functions:GEN_ArgParseTruth
						General Functions:See GENFUNCS

   PUBLISH XREF:  GEN_ArgParseTruth

   PUBLISH NAME:	GEN_ArgParseTruth

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
int GEN_ArgParseTruth(const char *in_param_ptr, int *error_flag,
	int *truth_flag, char *error_text, unsigned int *out_param_length,
	char **out_data_ptr, ...)
#else
int GEN_ArgParseTruth(in_param_ptr, error_flag, truth_flag, error_text,
	out_param_length, out_data_ptr, va_alist)
const char    *in_param_ptr;
int           *error_flag;
int           *truth_flag;
char          *error_text;
unsigned int  *out_param_length;
char         **out_data_ptr;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int         return_code = GENFUNCS_FALSE;
	const char *this_string;
	va_list     argument_ptr;

	*error_flag       = GENFUNCS_FALSE;
	*out_param_length = 0;
	*out_data_ptr     = NULL;

#ifndef NO_STDARGS
	va_start(argument_ptr, out_data_ptr);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	while ((this_string = va_arg(argument_ptr, const char *)) != NULL) {
		if (!strnicmp(in_param_ptr, this_string, strlen(this_string))) {
			*out_param_length = strlen(this_string);
			*out_data_ptr     = ((char *) in_param_ptr) + *out_param_length;
			return_code       = GENFUNCS_TRUE;
			if ((!stricmp(*out_data_ptr, "ON"))  ||
				(!stricmp(*out_data_ptr, "YES"))  ||
				(!stricmp(*out_data_ptr, "TRUE")) ||
				(!stricmp(*out_data_ptr, "T"))    ||
				(!stricmp(*out_data_ptr, "Y"))    ||
				(!stricmp(*out_data_ptr, "1")))
				*truth_flag = GENFUNCS_TRUE;
			else if ((!stricmp(*out_data_ptr, "OFF")) ||
				(!stricmp(*out_data_ptr, "NO"))        ||
				(!stricmp(*out_data_ptr, "FALSE"))     ||
				(!stricmp(*out_data_ptr, "F"))         ||
				(!stricmp(*out_data_ptr, "N"))         ||
				(!stricmp(*out_data_ptr, "0")))
				*truth_flag = GENFUNCS_FALSE;
			else {
				sprintf(error_text,
					"%s '%-.400s' parameter ('%-.400s') --- %s.",
					"Invalid toggle supplied for", this_string, *out_data_ptr,
					"one of { ON | OFF | YES | NO | TRUE | FALSE } was expected");
				*error_flag = GENFUNCS_TRUE;
			}
			break;
		}
	}

	va_end(argument_ptr);

	return(return_code);
}
/* ***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ArgParseListTruth

   SYNOPSIS    :  return_code = GEN_ArgParseListTruth(parse_count, parse_list,
							in_param_ptr, error_flag, truth_flag, error_text,
							out_param_length, out_data_ptr);

						int            return_code;

						unsigned int   parse_count;

						const char   **parse_list;

						const char    *in_param_ptr;

						int           *error_flag;

						int           *truth_flag;

						char          *error_text;

						unsigned int  *out_param_length;

						char         **out_data_ptr;

	DESCRIPTION :  Parses a parameter by matching the parameter string against
						an array of pointers to strings.

						If a match is found, the parameter value is parsed to
						determine its Boolean truth value within the following
						domains:

						(.) For ''TRUE'':

						<|-|>''{''TRUE''|''ON''|''YES''|''T''|''Y''|''1''}''

						(.) and for ''FALSE'':

						<|-|>''{''FALSE''|''OFF''|''NO''|''F''|''N''|''0''}''

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``parse_count`` is the number of elements in the array
						``parse_list``.

						(.) ``parse_list`` is the array of strings which are to be
						matched against ``in_param_ptr``.

						(.) ``in_param_ptr`` points to the parameter to be parsed.

						(.) ``error_flag`` points to an ''int'' into which will be
						placed an indication of an error, should one occur. The
						indication will take the form of the value of one of the
						following mainfest constants:

						(..) ''GENFUNCS_TRUE'' if an error occurred. In this case,
						text describing the error will be placed in the string to
						which the ``error_text`` parameter points.

						(..) ''GENFUNCS_FALSE'' if no error occurred.

						(.) ``truth_flag`` points to an ''int'' into which will be
						placed the value of the parameter parsed by the function.

						(..) If the value of the parameter is one of ''ON'', ''YES'',
						or ''TRUE'', then ``truth_flag`` will be set to the value
						of the manifest constant ''GENFUNCS_TRUE''.

						(..) If the value of the parameter is one of ''OFF'', ''NO'',
						or ''FALSE'', then ``truth_flag`` will be set to the value
						of the manifest constant ''GENFUNCS_FALSE''.

						(.) ``error_text`` points to a string into which text which
						describes any error which may occur will be placed by the
						function.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

						(.) ``out_param_length`` points to an ''unsigned int'' into
						which the length of the string which matched the beginning
						of the parameter will be placed, if found.

						(.) ``out_data_ptr`` points to a pointer to char into which
						will be placed a pointer to the portion of the parameter in
						``in_param_ptr`` which follows the matched string.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :  If this function returns ''GENFUNCS_TRUE'' that is only an
						indication that the parameter was matched against one of
						strings in the list. You must then check the integer to
						which the ``error_flag`` parameter points to determine
						whether the parameter value was valid.

						If ``error_flag`` is equal to ''GENFUNCS_FALSE'', then the
						integer to which the ``truth_flag`` points will contain the
						manifest constant equivalent of the parameter value.

   CAVEATS     :  

	SEE ALSO    :  GEN_ArgParseTruth

	EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:  GEN_ArgParseListTruth
						Argument Parsing Functions:GEN_ArgParseListTruth
						GENFUNCS:Functions:GEN_ArgParseListTruth
						GENFUNCS:Argument Parsing Functions:GEN_ArgParseListTruth
						General Functions:See GENFUNCS

   PUBLISH XREF:  GEN_ArgParseListTruth

   PUBLISH NAME:	GEN_ArgParseListTruth

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ArgParseListTruth(unsigned int parse_count, const char **parse_list,
	const char *in_param_ptr, int *error_flag, int *truth_flag, char *error_text,
	unsigned int *out_param_length, char **out_data_ptr)
#else
int GEN_ArgParseListTruth(parse_count, parse_list, in_param_ptr, error_flag,
	truth_flag, error_text, out_param_length, out_data_ptr)
unsigned int   parse_count;
const char   **parse_list;
const char    *in_param_ptr;
int           *error_flag;
int           *truth_flag;
char          *error_text;
unsigned int  *out_param_length;
char         **out_data_ptr;
#endif /* #ifndef NARGS */
{
	int          return_code = GENFUNCS_FALSE;
	unsigned int count_1;

	*error_flag       = GENFUNCS_FALSE;
	*out_param_length = 0;
	*out_data_ptr     = NULL;

	for (count_1 = 0; count_1 < parse_count; count_1++) {
		if (!strnicmp(in_param_ptr, parse_list[count_1],
			strlen(parse_list[count_1]))) {
			*out_param_length = strlen(parse_list[count_1]);
			*out_data_ptr     = ((char *) in_param_ptr) + *out_param_length;
			return_code       = GENFUNCS_TRUE;
			if ((!stricmp(*out_data_ptr, "ON"))  ||
				(!stricmp(*out_data_ptr, "YES"))  ||
				(!stricmp(*out_data_ptr, "TRUE")) ||
				(!stricmp(*out_data_ptr, "T"))    ||
				(!stricmp(*out_data_ptr, "Y"))    ||
				(!stricmp(*out_data_ptr, "1")))
				*truth_flag = GENFUNCS_TRUE;
			else if ((!stricmp(*out_data_ptr, "OFF")) ||
				(!stricmp(*out_data_ptr, "NO"))        ||
				(!stricmp(*out_data_ptr, "FALSE"))     ||
				(!stricmp(*out_data_ptr, "F"))         ||
				(!stricmp(*out_data_ptr, "N"))         ||
				(!stricmp(*out_data_ptr, "0")))
				*truth_flag = GENFUNCS_FALSE;
			else {
				sprintf(error_text,
					"%s '%-.400s' parameter ('%-.400s') --- %s.",
					"Invalid toggle supplied for", parse_list[count_1],
					*out_data_ptr,
					"one of { ON | OFF | YES | NO | TRUE | FALSE } was expected");
				*error_flag = GENFUNCS_TRUE;
			}
			break;
		}
	}

	return(return_code);
}
/* ***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (int, char **));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = GENFUNCS_SUCCESS;
	unsigned int  count_1;
	unsigned int  param_length;
	char         *data_ptr;
   int           found_flag;
	int           truth_flag;
	int           error_flag;
	char          error_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test function for 'GEN_ArgParse()'\n");
	fprintf(stderr, "---- -------- --- ----------------\n\n");

	if (argc < 2) {
		fprintf(stderr, "USAGE:\n%s <string> [<string> . . . ]\n\n", argv[0]);
		return_code = GENFUNCS_FAILURE;
	}
	else {
		fprintf(stderr, "PARSE LIST:\n");
		fprintf(stderr, ">>> [-INDIRECT=]\n");
		fprintf(stderr, ">>> [-INDIRECT_INDEX=]\n");
		fprintf(stderr, ">>> [-INDIRECT_INDEX_FLAG=]\n");
		STR_EMIT_CharLine('=', 78, NULL, stderr);
		fprintf(stderr, "Basic Argument Parse Test\n");
		STR_EMIT_CharLine('=', 78, NULL, stderr);
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			fprintf(stderr, "COMMAND-LINE ARGUMENT:[%s]\n", argv[count_1]);
			found_flag = GEN_ArgParse(argv[count_1], &param_length, &data_ptr,
				"-INDIRECT=", "-INDIRECT_INDEX=", "-INDIRECT_INDEX_FLAG=",
				NULL);
			fprintf(stderr, "RESULT               : %sFOUND ",
				(found_flag == GENFUNCS_TRUE) ? "" : "NOT ");
			if (found_flag == GENFUNCS_TRUE)
				fprintf(stderr, "[%-*.*s][%s]", param_length, ((int) param_length),
					argv[count_1], data_ptr);
			fprintf(stderr, "\n");
			STR_EMIT_CharLine('-', 78, NULL, stderr);
		}
		STR_EMIT_CharLine('=', 78, NULL, stderr);
		fprintf(stderr, "Truth Argument Parse Test\n");
		STR_EMIT_CharLine('=', 78, NULL, stderr);
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			fprintf(stderr, "COMMAND-LINE ARGUMENT:[%s]\n", argv[count_1]);
			found_flag = GEN_ArgParseTruth(argv[count_1], &error_flag,
				&truth_flag, error_text, &param_length, &data_ptr, "-INDIRECT=",
				"-INDIRECT_INDEX=", "-INDIRECT_INDEX_FLAG=", NULL);
			fprintf(stderr, "RESULT               : %sFOUND ",
				(found_flag == GENFUNCS_TRUE) ? "" : "NOT ");
			if (found_flag == GENFUNCS_TRUE) {
				if (error_flag == GENFUNCS_TRUE)
					fprintf(stderr, "(with error = %s", error_text);
				else
					fprintf(stderr, "[%-*.*s][%s][%s]", param_length,
						((int) param_length), argv[count_1], data_ptr,
						(truth_flag == GENFUNCS_TRUE) ? "TRUE" : "FALSE");
			}
			fprintf(stderr, "\n");
			STR_EMIT_CharLine('-', 78, NULL, stderr);
		}
		STR_EMIT_CharLine('=', 78, NULL, stderr);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

