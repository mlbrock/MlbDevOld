/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the intepretation of command-line parameters
								and parameter include files for ADF executables.

	Revision History	:	1995-07-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions local to this module . . .			*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int ADF_GetParamsFromSource,
	(void *control_ptr, unsigned int argc,
	char **argv, int *help_flag, int *version_flag,
	int (*parse_function)(void *, unsigned int, char **, int, unsigned int,
	char *), unsigned int *include_file_count, char ***include_file_list,
	unsigned int *include_stack_count, char ***include_stack_list,
	char *error_text));
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

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

	COPYRIGHT	:	Copyright 1995, Michael L. Brock Associates.

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int ADF_GetParams(void *control_ptr, unsigned int argc, char **argv,
	int *help_flag, int *version_flag, int (*parse_function)(void *,
	unsigned int, char **, int, unsigned int, char *), char *error_text)
#else
int ADF_GetParams(control_ptr, argc, argv, help_flag, version_flag,
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
	unsigned int   include_file_count  = 0;
	char         **include_file_list   = NULL;
	unsigned int   include_stack_count = 0;
	char         **include_stack_list  = NULL;

	*help_flag    = ADF_FALSE;
	*version_flag = ADF_FALSE;

	if ((return_code = (*parse_function)(control_ptr, argc, argv, ADF_TRUE, 0,
		error_text)) == ADF_SUCCESS)
		return_code = ADF_GetParamsFromSource(control_ptr, argc - 1,
			argv + 1, help_flag, version_flag, parse_function,
			&include_file_count, &include_file_list, &include_stack_count,
			&include_stack_list, error_text);

   strl_remove_all(&include_file_count, &include_file_list);
	strl_remove_all(&include_stack_count, &include_stack_list);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

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

	COPYRIGHT	:	Copyright 1995, Michael L. Brock Associates.

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
static int ADF_GetParamsFromSource(void *control_ptr, unsigned int argc,
	char **argv, int *help_flag, int *version_flag,
	int (*parse_function)(void *, unsigned int, char **, int, unsigned int,
	char *), unsigned int *include_file_count, char ***include_file_list,
	unsigned int *include_stack_count, char ***include_stack_list,
	char *error_text)
#else
static int ADF_GetParamsFromSource(control_ptr, argc, argv, help_flag,
	version_flag, parse_function, include_file_count, include_file_list,
	include_stack_count, include_stack_list, error_text)
void           *control_ptr;
unsigned int    argc;
char          **argv;
int            *help_flag;
int            *version_flag;
int           (*parse_function)();
unsigned int   *include_file_count;
char         ***include_file_list;
unsigned int   *include_stack_count;
char         ***include_stack_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code                 = ADF_SUCCESS;
	unsigned int    count_1;
	unsigned int    count_2;
	unsigned long   file_size;
	unsigned int    actual_count;
	FILE           *file_ptr                    = NULL;
	char           *file_buffer                 = NULL;
	unsigned int    in_line_count               = 0;
	char          **in_line_list                = NULL;
	int             other_param_file_error_flag = ADF_FALSE;

	for (count_1 = 0; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			*help_flag = ADF_TRUE;
			break;
		}
		else if ((!stricmp(argv[count_1], "-V")) ||
			(!stricmp(argv[count_1], "-VER"))     ||
			(!stricmp(argv[count_1], "-VERS"))    ||
			(!stricmp(argv[count_1], "-VERSION")) ||
			(!stricmp(argv[count_1], "-VERSIONS"))) {
			*version_flag = ADF_TRUE;
			break;
		}
		else if (argv[count_1][0] == '@') {
			if (!argv[count_1][1]) {
				sprintf(error_text, "%s '@' %s %s ('@<include-file-name>').",
					"Invalid parameter --- expected the include file parameter",
					"to be followed by the name of the parameter file to be",
					"included");
				return_code = ADF_BAD_ARGS_FAILURE;
				break;
			}
			for (count_2 = 0; count_2 < *include_file_count; count_2++) {
				if (!strcmp(argv[count_1] + 1, (*include_file_list)[count_2])) {
					sprintf(error_text, "%s '%-.500s' %s.",
						"Parameter include file", argv[count_1] + 1,
						"may not be included more than once");
					return_code = ADF_BAD_ARGS_FAILURE;
					break;
				}
			}
			if (return_code != ADF_SUCCESS)
				break;
			if (strl_append(include_file_count, include_file_list,
				argv[count_1] + 1) != STRFUNCS_SUCCESS) {
				sprintf(error_text, "%s '%-.500s' %s (%u bytes required).",
					"Unable to add the parameter include file", argv[count_1] + 1,
					"to the list of included files",
					strlen(argv[count_1] + 1) + 1);
				return_code = ADF_MEMORY_FAILURE;
				break;
			}
			else if (strl_append(include_stack_count, include_stack_list,
				argv[count_1] + 1) != STRFUNCS_SUCCESS) {
				sprintf(error_text, "%s '%-.500s' %s (%u bytes required).",
					"Unable to add the parameter include file", argv[count_1] + 1,
					"to the stack of included files", strlen(argv[count_1] + 1) + 1);
				return_code = ADF_MEMORY_FAILURE;
				break;
			}
			else if ((file_ptr = fopen(argv[count_1] + 1, "rb")) == NULL) {
				sprintf(error_text, "%s '%-.500s' for reading --- ",
					"Unable to open the parameter include file",
					argv[count_1] + 1);
				ADF_GetLastErrorString(error_text);
				strl_remove(include_stack_count, include_stack_list,
					*include_stack_count - 1, 1);
				return_code = ADF_FAILURE;
				break;
			}
			fseek(file_ptr, 0L, SEEK_END);
			file_size = ftell(file_ptr);
			fseek(file_ptr, 0L, SEEK_SET);
			if (!file_size) {
				fclose(file_ptr);
				break;
			}
			if ((file_buffer = ((char *) calloc(((unsigned int) file_size) + 1,
				sizeof(char)))) == NULL) {
				sprintf(error_text, "%s %s '%-.500s' (%lu bytes required).",
					"Unable to allocate memory for a buffered copy of the",
					"parameter include file", argv[count_1] + 1, file_size);
				fclose(file_ptr);
				strl_remove(include_stack_count, include_stack_list,
					*include_stack_count - 1, 1);
				return_code = ADF_MEMORY_FAILURE;
				break;
			}
			if ((actual_count = fread(file_buffer, sizeof(char),
				((unsigned int) file_size), file_ptr)) !=
				((unsigned int) file_size)) {
				sprintf(error_text,
					"%s %lu %s %u %s '%-.500s' %s %lu (%u %s): ",
					"Error occurred while attempting to read", file_size,
					"blocks of size", sizeof(char),
					"from the file", argv[count_1] + 1, "at offset", ftell(file_ptr),
					actual_count, "blocks were read");
				ADF_GetLastErrorString(error_text);
				fclose(file_ptr);
				strl_remove(include_stack_count, include_stack_list,
					*include_stack_count - 1, 1);
				free(file_buffer);
				return_code = ADF_SYSTEM_FAILURE;
				break;
			}
			fclose(file_ptr);
			for (count_2 = 0; count_2 < ((unsigned int) file_size); count_2++)
				file_buffer[count_2] = ((char) ((!file_buffer[count_2]) ?
					((char) ' ') : file_buffer[count_2]));
			if (sepwordx(file_buffer, "\r\n", &in_line_count,
				&in_line_list) != STRFUNCS_SUCCESS) {
				sprintf(error_text, "%s %s '%-.500s' (%lu bytes required).",
					"Unable to create the temporary list of lines from",
					"parameter include file", argv[count_1] + 1,
					((unsigned long) (((chrcnt(file_buffer, '\n') + 1) *
					sizeof(char *)) +
					(file_size + chrcnt(file_buffer, '\n') + 1))));
				free(file_buffer);
				strl_remove(include_stack_count, include_stack_list,
					*include_stack_count - 1, 1);
				return_code = ADF_MEMORY_FAILURE;
				break;
			}
			free(file_buffer);
			for (count_2 = 0; count_2 < in_line_count; ) {
				trim(nocontrl(in_line_list[count_2]));
				if ((!in_line_list[count_2][0]) ||
					(in_line_list[count_2][0] == '#'))
					strl_remove(&in_line_count, &in_line_list, count_2, 1);
				else
					count_2++;
			}
			return_code = ADF_GetParamsFromSource(control_ptr,
				in_line_count, in_line_list, help_flag, version_flag,
				parse_function, include_file_count, include_file_list,
				include_stack_count, include_stack_list, error_text);
			strl_remove_all(&in_line_count, &in_line_list);
			strl_remove(include_stack_count, include_stack_list,
				*include_stack_count - 1, 1);
			if (return_code != ADF_SUCCESS) {
				other_param_file_error_flag = ADF_TRUE;
				break;
			}
			else if ((*help_flag == ADF_TRUE) || (*version_flag == ADF_TRUE))
				break;
		}
		else if ((return_code = (*parse_function)(control_ptr, argc, argv,
			ADF_FALSE, count_1, error_text)) != ADF_SUCCESS)
			break;
	}

	if ((return_code == ADF_BAD_ARGS_FAILURE) &&
		(other_param_file_error_flag != ADF_TRUE)) {
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

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(int ParseIt,
	(void *control_ptr, unsigned int argc, char **argv,
	int init_flag, unsigned int current_arg, char *error_text));

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
	char error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'ADF_GetParams()'\n");
	fprintf(stderr, "---- ------- --- -----------------\n\n");

	if ((return_code = ADF_GetParams(NULL, ((unsigned int) argc), argv,
		&help_flag, &version_flag, ParseIt, error_text)) != ADF_SUCCESS) {
		if (return_code == ADF_BAD_ARGS_FAILURE)
			ADF_DoFormatUsage(return_code, argv[0],
				"Bad arguments encountered.", UsageList);
		fprintf(stderr, "\nERROR ON PARSE ATTEMPT: %s\n", error_text);
	}
	else if (help_flag == ADF_TRUE)
		ADF_DoFormatUsage(return_code, argv[0],
			"Help request with '-HELP' noted.", UsageList);
	else if (version_flag == ADF_TRUE)
		printf("Version Number 00.00.00A\n");
	else
		fprintf(stderr, "%s %s %s\n", "********************",
			"PROCESS PARAMETER INTERPRETATION SUCCESSFUL",
			"********************");

	return(return_code);
}


#ifndef NARGS
static int ParseIt(void *control_ptr, unsigned int argc, char **argv,
	int init_flag, unsigned int current_arg, char *error_text)
#else
static int ParseIt(control_ptr, argc, argv, init_flag, current_arg,
	error_text)
void          *control_ptr;
unsigned int   argc;
char         **argv;
int            init_flag;
unsigned int   current_arg;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_SUCCESS;

	if (init_flag != ADF_TRUE) {
		if (!stricmp(argv[current_arg], "-CHECK_ONLY"))
			fprintf(stderr, "PARAMETER:[%s] = OK\n", argv[current_arg]);
		else if (!strnicmp(argv[current_arg], "-LOG_DIR=",
			strlen("-LOG_DIR=")))
			fprintf(stderr, "PARAMETER:[%s] = OK\n", argv[current_arg]);
		else {
			sprintf(error_text,
				"Invalid command-line parameter encountered ('%-.500s').",
				 argv[current_arg]);
			return_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

