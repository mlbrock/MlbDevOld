/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the intepretation of command-line parameters
								and parameter include files for executables.

	Revision History	:	1991-04-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>
#include <tfread.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions local to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int GEN_GetParamsFromSource, (void *control_ptr,
	unsigned int argc, char **argv, int *help_flag, int *version_flag,
	int (*parse_function)(void *parse_control_ptr, unsigned int parse_argc,
		char **parse_argv, int call_flag, unsigned int current_arg,
		const char *current_arg_ptr, char *parse_error_text),
	unsigned int *include_stack_count, char ***include_stack_list,
	char *error_text));
COMPAT_FN_DECL_STATIC(int GEN_LoadParamsFromFile, (const char *in_file,
	unsigned int *include_stack_count, char ***include_stack_list,
	unsigned int *out_line_count, char ***out_line_list, char *error_text));
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	GEN_GetParams

	SYNOPSIS		:	return_code = GEN_GetParams(control_ptr, argc, argv,
							help_flag, version_flag, parse_function, error_text);

						int            return_code;

						void          *control_ptr;

						unsigned int   argc;

						char         **argv;

						int           *help_flag;

						int           *version_flag;

						int          (*parse_function)(void *parse_control_ptr,
											unsigned int parse_argc, char **parse_argv,
											int call_flag, unsigned int current_arg,
											const char *current_arg_ptr,
											char *parse_error_text);

						char          *error_text;

	DESCRIPTION	:	Controls the intepretation of command-line parameters and
						parameter include files for executables.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``control_ptr`` points to a user-defined data structure
						which will be passed unexamined to the function designated
						by the ``parse_function`` parameter. It may be a ''NULL''
						pointer if unnecessary.

						(.) ``argc`` is the number of parameters to be parsed in
						the array of pointers to ''char'' ``argv``.

						(.) ``argv`` is the list of command-line arguments.

						(.) ``help_flag`` points to an ''int'' which signals whether
						the ''-HELP'' parameter was encountered in the argument
						list.

						(-) the ''-HELP'' parameter takes the following form:

						<->-H''[''ELP'']''

						(-) If ``help_flag`` is not ''NULL'', the function will
						initialize the ''int'' to which it points to the manifest
						constant ''GENFUNCS_FALSE''. If the ''HELP'' parameter is
						then encountered while parsing the argument list, the
						function will set the ''int'' to ''GENFUNCS_TRUE'' and
						immediately return.

						(-) If ``help_flag`` is ''NULL'', it will not be
						de-referenced by the function.

						(.) ``version_flag`` points to an ''int'' which signals whether
						the ''-VERSION'' parameter was encountered in the argument
						list.

						(-) the ''-VERSION'' parameter takes the following form:

						<->-V''[''ER''[''SION'']][''S'']''

						(-) If ``version_flag`` is not ''NULL'', the function will
						initialize the ''int'' to which it points to the manifest
						constant ''GENFUNCS_FALSE''. If the ''VERSION'' parameter is
						then encountered while parsing the argument list, the
						function will set the ''int'' to ''GENFUNCS_TRUE'' and
						immediately return.

						(-) If ``version_flag`` is ''NULL'', it will not be
						de-referenced by the function.

						(.) ``parse_function`` is a pointer to a function which
						will be invoked to parse each arguments as it is
						encountered. The function to which ``parse_function``
						points must take the following arguments:

						(..) ``parse_control_ptr`` is the ``control_ptr`` parameter.

						(..) ``parse_argc`` is the number of elements in the list
						``parse_argv``.

						(..) ``parse_argv`` is the list of command-line arguments.

						(..) ``call_flag``, indicates the type of call this function
						is making to ``parse_function``. There are three possible
						values for ``call_flag``:

						(...) ''-1'' indicates that this is an initialization call.
						``parse_function`` should initialize itself (if required)
						and return.

						(...) ''0'' indicates that this is an argument parsing call.
						``parse_function`` should parse the argument within
						the ``current_arg`` element of the ``parse_argv`` array.

						(...) ''1'' indicates that this is a completion call.
						``parse_function`` should free any resources which were
						allocated in the initialization call.

						(..) ``current_arg`` is the index of the current argument
						within the array ``parse_argv``.

						(..) ``current_arg_ptr`` points to the current argument.
						It may be modified to support the correct passing of
						parameters beginning with an at-sign ''@''.

						(..) ``parse_error_text`` is the ``error_text`` parameter.

						(-) ``parse_function`` must return ''GENFUNCS_SUCCESS'' if
						all goes well within it. Otherwise, if an error occurs,
						it should format a description of the error within
						``parse_error_text`` and return a non-zero value.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

	NOTES			:	This function supports the use of parameter include files.
						Parameter include files permit arguments to be stored in a
						text file for parsing by this program.

						Inclusion of a parameter include file is indicated by an
						argument of the form:

						<@>''@''``parameter-include-file-name``

						However, note the following:

						(.) An argument which consists of a single ``at-sign``
						(''@'') is not considered to be a valid parameter include
						file specification. The ``parse_function`` will be called
						to handle parsing of such an argument.

						(.) An argument which begins with two ``at-sign``s (''@@'')
						is considered to be an escaped parameter. Again, the
						``parse_function`` will be called to handle parsing of such
						an argument. In this case, however, the first ''@'' is
						redundant.  This function will set the ``current_arg_ptr``
						parameter to ``parse_function`` at the second ''@''.

						When a parameter include file is encountered on the command
						line, the program will attempt to open it for reading. It is
						an error if the file so specified does not exist or can not
						be read.

						Each line of the parameter include file is parsed for its
						parameters just as if those parameters were entered on the
						command-line except for the following rules:

						(.) A line in which the first non-whitespace character is a
						number-sign (''#'') is considered to be the start of a
						comment and is ignored.

						(.) Blank lines (that is, lines which are empty or which
						consist wholly of whitespace) are ignored.

						Parameter include files may themselves contain parameter
						include file specifications. An include file may be included
						more than once, so long as any nested chain of includes from
						that file does not result in an attempt to include itself
						recursively.

	CAVEATS		:	It is important to remember that this function is intended
						to be invoked with the program command-line parameters, and
						the its behavior reflects that intent.

						Specifically:

						(.) Initialization and completion calls to ``parse_function``
						are performed with the same argument count and argument
						list as was passed to this function originally.

						(.) Other calls to ``parse_function`` are called with the
						''argc - 1'' and ''argv + 1''. This function will not call
						``parse_function`` for the first parameter (''argv[0]'')
						except on initialization and completion calls.

	SEE ALSO		:

	EXAMPLES		:	To support the functionality described above, your parse
						function should probably look something like:

{|@|}static int ParseIt(control_ptr, argc, argv, call_flag,
	current_arg, current_arg_ptr, error_text)
ADF_CONTROL   *control_ptr;
unsigned int   argc;
char         **argv;
int            call_flag;
unsigned int   current_arg;
const char    *current_arg_ptr;
char          *error_text;
{
	int return_code = GENFUNCS_SUCCESS;

	if (call_flag < 0) {
		// Initialization code here.
	}
	else if (call_flag > 0) {
		// Completion code here.
	}
	else {
		// Parse the argument in 'current_arg_ptr'.
	}

	return(return_code);
}

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2016 Michael L. Brock

	OUTPUT INDEX:	GEN_GetParams
						Argument Parsing Functions:GEN_GetParams
						GENFUNCS:Functions:GEN_GetParams
						GENFUNCS:Argument Parsing Functions:GEN_GetParams
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_GetParams

	PUBLISH NAME:	GEN_GetParams

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_GetParams(void *control_ptr, unsigned int argc, char **argv,
	int *help_flag, int *version_flag,
	int (*parse_function)(void *parse_control_ptr, unsigned int parse_argc,
	char **parse_argv, int call_flag, unsigned int current_arg,
	const char *current_arg_ptr, char *parse_error_text), char *error_text)
#else
int GEN_GetParams(control_ptr, argc, argv, help_flag, version_flag,
	parse_function, error_text)
void          *control_ptr;
unsigned int   argc;
char         **argv;
int           *help_flag;
int           *version_flag;
int          (*parse_function)();
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   include_stack_count = 0;
	char         **include_stack_list  = NULL;
	char           tmp_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if (help_flag != NULL)
		*help_flag = GENFUNCS_FALSE;
	if (version_flag != NULL)
		*version_flag = GENFUNCS_FALSE;

	if ((return_code = (*parse_function)(control_ptr, argc, argv, -1, 0,
		argv[0], error_text)) == GENFUNCS_SUCCESS) {
		return_code = GEN_GetParamsFromSource(control_ptr, argc - 1,
			argv + 1, help_flag, version_flag, parse_function,
			&include_stack_count, &include_stack_list, error_text);
		(*parse_function)(control_ptr, argc, argv, 1, 0, argv[0],
			tmp_error_text);
	}

	strl_remove_all(&include_stack_count, &include_stack_list);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* NOT_BOH

	NAME			:

	SYNOPSIS		:

	DESCRIPTION	:

	PARAMETERS	:

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2016 Michael L. Brock

	OUTPUT INDEX:	
						Argument Parsing Functions:
						GENFUNCS:Functions:
						GENFUNCS:Argument Parsing Functions:
						General Functions:See GENFUNCS

	PUBLISH XREF:	

	PUBLISH NAME:	

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
static int GEN_GetParamsFromSource(void *control_ptr, unsigned int argc,
	char **argv, int *help_flag, int *version_flag,
	int (*parse_function)(void *parse_control_ptr, unsigned int parse_argc,
	char **parse_argv, int call_flag, unsigned int current_arg,
	const char *current_arg_ptr, char *parse_error_text),
	unsigned int *include_stack_count, char ***include_stack_list,
	char *error_text)
#else
static int GEN_GetParamsFromSource(control_ptr, argc, argv, help_flag,
	version_flag, parse_function, include_stack_count, include_stack_list,
	error_text)
void           *control_ptr;
unsigned int    argc;
char          **argv;
int            *help_flag;
int            *version_flag;
int           (*parse_function)();
unsigned int   *include_stack_count;
char         ***include_stack_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code      = GENFUNCS_SUCCESS;
	unsigned int    in_line_count    = 0;
	char          **in_line_list     = NULL;
	int             other_error_flag = GENFUNCS_FALSE;
	const char     *current_arg_ptr;
	unsigned int    count_1;
	unsigned int    count_2;

	for (count_1 = 0; count_1 < argc; count_1++) {
		if ((help_flag != NULL) && ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H")))) {
			*help_flag = GENFUNCS_TRUE;
			break;
		}
		else if ((version_flag != NULL) && ((!stricmp(argv[count_1], "-V")) ||
			(!stricmp(argv[count_1], "-VER"))     ||
			(!stricmp(argv[count_1], "-VERS"))    ||
			(!stricmp(argv[count_1], "-VERSION")) ||
			(!stricmp(argv[count_1], "-VERSIONS")))) {
			*version_flag = GENFUNCS_TRUE;
			break;
		}
		else if ((argv[count_1][0] == '@') && (argv[count_1][1]) &&
			(argv[count_1][1] != '@')) {
			if ((return_code = GEN_LoadParamsFromFile(argv[count_1] + 1,
				include_stack_count, include_stack_list, &in_line_count,
				&in_line_list, error_text)) != GENFUNCS_SUCCESS)
				break;
			return_code = GEN_GetParamsFromSource(control_ptr,
				in_line_count, in_line_list, help_flag, version_flag,
				parse_function, include_stack_count, include_stack_list,
				error_text);
			strl_remove_all(&in_line_count, &in_line_list);
			strl_remove(include_stack_count, include_stack_list,
				*include_stack_count - 1, 1);
			if (return_code != GENFUNCS_SUCCESS) {
				other_error_flag = GENFUNCS_TRUE;
				break;
			}
			else if (((help_flag != NULL) && (*help_flag == GENFUNCS_TRUE)) ||
				((version_flag != NULL) && (*version_flag == GENFUNCS_TRUE)))
				break;
		}
		else {
			current_arg_ptr = ((argv[count_1][0] == '@') &&
				(argv[count_1][1] == '@')) ? (argv[count_1] + 1) : argv[count_1];
			if ((return_code = (*parse_function)(control_ptr, argc, argv, 0,
				count_1, current_arg_ptr, error_text)) != GENFUNCS_SUCCESS)
				break;
		}
	}

/*
	if ((return_code == GENFUNCS_BAD_ARGS_FAILURE) &&
		(other_error_flag != GENFUNCS_TRUE)) {
*/
	if ((return_code != GENFUNCS_SUCCESS) &&
		(other_error_flag != GENFUNCS_TRUE)) {
		for (count_1 = 0; count_1 <= 78; count_1++)
			fprintf(stderr, "%s", (count_1 < 78) ? "-" : "\n");
		fprintf(stderr, "Error in parameter: %s\n", error_text);
		if (*include_stack_count) {
			for (count_1 = *include_stack_count; count_1 > 0; count_1--) {
				for (count_2 = 0; count_2 < ((*include_stack_count - count_1) + 1);
					count_2++)
					fprintf(stderr, "   ");
				fprintf(stderr,
					"%sarameter include file '%s', included from\n",
					(count_1 == *include_stack_count) ? "In p" : "P",
					(*include_stack_list)[count_1 - 1]);
			}
			for (count_1 = 0; count_1 <= *include_stack_count; count_1++)
				fprintf(stderr, "   ");
			fprintf(stderr, "The command-line.\n");
		}
		else {
			fprintf(stderr, "   Included from the command-line.\n");
		}
		for (count_1 = 0; count_1 <= 78; count_1++)
			fprintf(stderr, "%s", (count_1 < 78) ? "-" : "\n");
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int GEN_LoadParamsFromFile(const char *in_file,
	unsigned int *include_stack_count, char ***include_stack_list,
	unsigned int *out_line_count, char ***out_line_list, char *error_text)
#else
static int GEN_LoadParamsFromFile(in_file, include_stack_count,
	include_stack_list, out_line_count, out_line_list, error_text)
const char     *in_file;
unsigned int   *include_stack_count;
char         ***include_stack_list;
unsigned int   *out_line_count;
char         ***out_line_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	int            stack_added_flag = GENFUNCS_FALSE;
	char          *tmp_file         = NULL;
	unsigned int   count_1;
	char           tmp_error_text[GENFUNCS_MAX_ERROR_TEXT];
	char           tfread_error_text[TFREAD_MAX_ERROR_TEXT];

	*out_line_count = 0;
	*out_line_list  = NULL;

	if ((return_code = GEN_ExpandToFullPathName(in_file, &tmp_file,
		tmp_error_text)) != GENFUNCS_SUCCESS) {
		strcat(strcpy(error_text,
			"Unable to expand parameter include file name: "), tmp_error_text);
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < *include_stack_count; count_1++) {
		if (!strcmp(tmp_file, (*include_stack_list)[count_1])) {
			sprintf(error_text, "Parameter include file '%-.500s' %s.", tmp_file,
				"may not be included more than once");
			return_code = GENFUNCS_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	if (strl_append(include_stack_count, include_stack_list, tmp_file) !=
		STRFUNCS_SUCCESS) {
		GEN_AllocMsgItem(strlen(tmp_file) + 1, error_text, "%s '%-.500s' %s",
			"Unable to add the parameter include file", tmp_file,
			"to the stack of included files");
		return_code = GENFUNCS_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	stack_added_flag = GENFUNCS_TRUE;

	if ((return_code = TFREAD_ReadLines(tmp_file, out_line_count,
		out_line_list, tfread_error_text)) != TFREAD_SUCCESS) {
		nstrcpy(error_text, tfread_error_text, GENFUNCS_MAX_ERROR_TEXT - 1);
		return_code = GEN_MAP_ERROR_TFREAD(return_code);
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < *out_line_count; ) {
		trim(nocontrl((*out_line_list)[count_1]));
		if ((!(*out_line_list)[count_1][0]) ||
			((*out_line_list)[count_1][0] == '#'))
			strl_remove(out_line_count, out_line_list, count_1, 1);
		else
			count_1++;
	}

EXIT_FUNCTION:

	if (tmp_file != NULL)
		free(tmp_file);

	if (return_code != GENFUNCS_SUCCESS) {
		if (stack_added_flag == GENFUNCS_TRUE)
			strl_remove(include_stack_count, include_stack_list,
				*include_stack_count - 1, 1);
		strl_remove_all(out_line_count, out_line_list);
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(       int main,    (int, char **));
COMPAT_FN_DECL_STATIC(int ParseIt, (void *control_ptr, unsigned int argc,
	char **argv, int call_flag, unsigned int current_arg,
	const char *current_arg_ptr, char *error_text));

static char *UsageList[] = {
	"	[-CHECK_ONLY]",
	"		Specifies that the program is only to check the initialization of \
the program. No work will be performed.",
	"\n",
	"	-HELP",
	"		Displays this text.\n",
	"\n",
	"	[-V[ER[SION][S]]]]",
	"		Displays the version of this program.",
	"\n",
/*
	"	[-LOG_DIR=<log-file-directory-name>]",
	"		Specifies the directory on which the log file is to be created. \
The created log file will have a file name in the following format:",
	"\n",
	"			<yyyy>-<mm>-<dd>.<hh>:<mm>:<ss>.<log-name>.<host>.<pid>",
	"\n",
	"			where <log-name> is '<model-name>_STUFF.LOG'",
	"\n",
	"		Note that the directory so specified must already exist.",
	"\n",
	"		If this parameter is not specified, the file will be created in \
the current working directory ('./').",
	"\n",
	"	[@<parameter-include-file-name>]",
	"		Specifies the name of a parameter include file from which are to \
be parameters to this module. Parameter include files may themselves \
contain parameter include file specifications.",
	"\n",
*/
	NULL
};

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int  return_code;
	int  help_flag;
	int  version_flag;
	char error_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'GEN_GetParams()'\n");
	fprintf(stderr, "---- ------- --- -----------------\n\n");

	if ((return_code = GEN_GetParams(NULL, ((unsigned int) argc), argv,
		&help_flag, &version_flag, ParseIt, error_text)) != GENFUNCS_SUCCESS) {
		if (return_code == GENFUNCS_BAD_ARGS_FAILURE)
			GEN_DoFormatUsage(return_code, argv[0],
				"Bad arguments encountered.", UsageList);
		fprintf(stderr, "\nERROR ON PARSE ATTEMPT: %s\n", error_text);
	}
	else if (help_flag == GENFUNCS_TRUE)
		GEN_DoFormatUsage(return_code, argv[0],
			"Help request with '-HELP' noted.", UsageList);
	else if (version_flag == GENFUNCS_TRUE)
		printf("Version Number 00.00.00A\n");
	else
		fprintf(stderr, "%s %s %s\n", "********************",
			"PROCESS PARAMETER INTERPRETATION SUCCESSFUL",
			"********************");

	return(return_code);
}

#ifndef NARGS
static int ParseIt(void *control_ptr, unsigned int argc, char **argv,
	int call_flag, unsigned int current_arg, const char *current_arg_ptr,
	char *error_text)
#else
static int ParseIt(control_ptr, argc, argv, call_flag, current_arg,
	current_arg_ptr, error_text)
void          *control_ptr;
unsigned int   argc;
char         **argv;
int            call_flag;
unsigned int   current_arg;
const char    *current_arg_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	if (!call_flag) {
		if (!stricmp(current_arg_ptr, "-CHECK_ONLY"))
			fprintf(stderr, "PARAMETER:[%s] = OK\n", current_arg_ptr);
		else if (!strnicmp(current_arg_ptr, "-LOG_DIR=",
			strlen("-LOG_DIR=")))
			fprintf(stderr, "PARAMETER:[%s] = OK\n", current_arg_ptr);
		else {
			sprintf(error_text,
				"Invalid command-line parameter encountered ('%-.500s').",
				current_arg_ptr);
			return_code = GENFUNCS_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

