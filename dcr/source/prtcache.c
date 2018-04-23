/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Executable Module									*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:

	Revision History	:	1994-06-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <locale.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_PRT_VERSION_NUMBER "01.00.00A"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	DCR_CONTROL  cache_control_data;
	int                help_flag;
	int                version_flag;
	char              *inter_field_separator;
	char              *intra_field_separator;
	char              *record_leader;
	char              *record_trailer;
	char              *page_separator;
	char              *field_name_spec;
	unsigned int       index_method;
	unsigned int       page_line_count;
	unsigned int       maximum_row_count;
	MFILE             *output_mfile_ptr;
	int                header_flag;
	int                binary_flag;
	int                cache_header_flag;
	int                cache_header_only_flag;
	int                reverse_flag;
	unsigned int       page_count;
	unsigned int       format_line_count;
   unsigned int       data_line_count;
} DCR_PRT_CONTROL;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

#ifndef NARGS
static int  DCR_PRT_Parse(DCR_PRT_CONTROL *control_ptr, unsigned int argc,
	char **argv, int call_flag, unsigned int current_arg,
	const char *this_arg, char *error_text);
static int  DCR_PRT_ResetText(DCR_PRT_CONTROL *control_ptr,
	char *error_text);
static void DCR_PRT_Init(DCR_PRT_CONTROL *control_ptr);
static void DCR_PRT_Free(DCR_PRT_CONTROL *control_ptr);
static void DCR_PRT_End(DCR_PRT_CONTROL *control_ptr,
	int signal_number, int *exit_code_ptr, const char *message_buffer);
#else
static int  DCR_PRT_Parse();
static int  DCR_PRT_ResetText();
static void DCR_PRT_Init();
static void DCR_PRT_Free();
static void DCR_PRT_End();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static const char *UsageList[] = {
	"Usage:",
	"------",
	"	prtcache [<a mixture of '-' options, '@' commands, and filenames>]",
	"\n",
	"Description:",
	"------------",
	"	This program prints the contents of an DCR cache.",
	"\n",
	"	Invocation of the program may include any number of parameters \
which may be used to specify the nature of the resulting output. \
There are three types of parameters:",
	"\n",
	"		o '-'-prefaced options, which specify any one of a number of \
options (which are described in the 'Options', below);",
	"\n",
	"		o '@'-prefaced file names, which indicate that the indicated \
file name is to be parsed for parameters, and;",
	"\n",
	"		o all other parameters which are taken to be the names of caches \
to be opened.",
	"\n",
	"Operation:",
	"----------",
	"	Program operation is as follows:",
	"\n",
	"		o The program initializes itself to the default settings (these \
are the same settings described in the 'Options' section \
under the description of the '-RESET' parameter).",
	"\n",
	"		o The command line is scanned for options.",
	"\n",
	"	Every time a valid parameter is encountered, it immediately \
becomes active.  Thus it is possible to print multiple caches with \
different settings, simply by interleaving the appropriate parameters \
in the correct order.",
	"\n",
	"	If an '@' option is encountered, the indicated file is read \
as if its lines had been placed on the command line UNLESS the \
indicated file is in the current hierarchy of '@' files, in which \
case it is ignored.  This prevents infinite loops (or, at least, \
loops which continue until the program runs out of stack space) \
caused by parameter files which include themselves.",
	"\n",
	"	Parameter files may, however, be read more than once, so long as \
no invocation of a particular command file results in the invocation \
of itself.",
	"\n",
	"Options:",
	"--------",
	"	[-HELP]",
	"		Displays this text. Note that if this parameter appears on the \
command-line, the program will exit after displaying the help text.",
	"\n",
	"	[-V[ER[SION][S]]]",
	"		Displays the version of this program.",
	"\n",
	"		If this parameter appears on the command line, any subsequent \
parameters will be parsed for validity and the program will exit.",
	"\n",
	"	[-BINARY[_OUT[PUT]]={ ON | OFF | TRUE | FALSE | YES | NO }]",
	"		Emits the cache records in binary format. Note that other options \
which may be specific to human-readable output (such as '-CACHE_HEADERS', \
'-HEADERS', '-LINE_COUNT', et cetera) are not effective for this option.",
	"\n",
	"		The default for this option is 'OFF'.",
	"\n",
	"	[-CACHE_HEADER[S]={ ON | OFF | TRUE | FALSE | YES | NO }]",
	"		Specifies that text descriptive of the cache control header is \
to be emitted.",
	"\n",
	"		The default for this option is 'OFF'.",
	"\n",
	"	[-CACHE_HEADER[S]_ONLY={ ON | OFF | TRUE | FALSE | YES | NO }]",
	"		Specifies that only text descriptive of the cache control header is \
to be emitted. No record data will be emitted while this parameter is \
effective.",
	"\n",
	"		The default for this option is 'OFF'.",
	"\n",
	"	[-FIELD[_NAME][S]=<field-list>]",
	"		Specifies the cache fields which are to be emitted by this program.",
	"\n",
	"		The <field-list> component of this option should be a \
comma-separated list of cache field names. Fields will be emitted within a \
record in the order specified by the <field-list>.",
	"\n",
	"		A field name may appear multiple times in this list. If it does, \
it will appear multiple times in the emitted output.",
	"\n",
	"		If the <field-list> component is not present or is empty, the \
program will emit all fields in the order specified by the cache file. \
This is the default behavior for this program.",
	"\n",
	"	[-INTER_]FIELD_SEP[ARATOR][S]=<string>]",
	"		Specifies the string to be used between fields emitted by this \
program.",
	"\n",
	"		The default for this option is a single space character (' ').",
	"\n",
	"	[-INTRA_FIELD_SEP[ARATOR][S]=<string>]",
	"		Specifies the string to be used within multi-part fields emitted \
by this program.",
	"\n",
	"		The default for this option is a single hyphen character ('-').",
	"\n",
	"	[-HEADER[S]={ ON | OFF | TRUE | FALSE | YES | NO }]",
	"		Specifies that column headers consisting of the field name are to \
be emitted for each column in the output emitted.",
	"\n",
	"		The default for this option is 'ON'.",
	"\n",
	"	[-INDEX[_METHOD]=<index-method-number>]",
	"		Specifies the index method to be used in emitting records.",
	"\n",
	"		The default for this option is '0'.",
	"\n",
	"	[-INDEX_ORDER={ASC[ENDING] | DESC[ENDING] }]",
	"		Specifies the order in which the cache index is to be traversed.",
	"\n",
	"		The default for this option is 'ASCENDING'.",
	"\n",
	"	[-MAX[IMUM]_{ROW[S]|RECORD[S]}[_COUNT]=<max-row-count>]",
	"		Specifies the maximum number of rows to be emitted by the program. \
If the <max-row-count> component of the option is not present or is equal to \
zero ('0'), no maximum will be imposed while emitting cache rows.",
	"\n",
	"		The default for this option is '0'.",
	"\n",
	"	[-[PAGE_]LINE[S]_COUNT=<lines-per-page>]",
	"		Specifies the number of lines to be emitted on a single page. \
If the <lines-per-page> component of the option is not present or is equal \
to zero ('0'), no page formatting will occur.",
	"\n",
	"		The default for this option is '60'.",
	"\n",
	"	[-OUT[PUT]_FILE[_NAME]=<file-name>]",
	"		Specifies the name of a file to which output is to be written \
instead of 'stdout'. If the <file-name> component of this option is not \
present, any existing output file will be closed and subsequent output \
will be routed to 'stdout'.",
	"\n",
	"		Note that <file-name> will be opened in write-mode, which will \
result in the file being truncated to zero-length. To append output to a \
file, use the '-APPEND_FILE=' option instead (see below).",
	"\n",
	"	[-APP[END]_FILE[_NAME]=<file-name>]",
	"		Specifies the name of a file to which output is to be appended \
instead of 'stdout'. If the <file-name> component of this option is not \
present, any existing output file will be closed and subsequent output \
will be routed to 'stdout'.",
	"\n",
	"	[-PAGE_SEP[ARATOR][S]=<string>]",
	"		Specifies the string to be used to separate pages. If the <string> \
component of this option is not present or is empty, nothing will separate \
pages.",
	"\n",
	"		The default for this option is an ASCII form-feed ('\\f').",
	"\n",
	"	[-REC[ORD]_LEAD[ER][S]=<string>]",
	"		Specifies the string with which to prefix records as they are \
output. If the <string> component of this option is not present or is empty, \
nothing will prefix record output.",
	"\n",
	"		The default for this option is 'NULL'.",
	"\n",
	"	[-REC[ORD]_TRAIL[ER][S]=<string>]",
	"		Specifies the string with which to append to records as they are \
output. If the <string> component of this option is not present or is empty, \
nothing will be appended to record output.",
	"\n",
	"		The default for this option is an ASCII line-feed ('\\n').",
	"\n",
	"	[-RESET]",
	"		Specifies that all settings are to be reset to their initial \
values. These values are as follow:",
	"\n",
	"			o -BINARY=OFF",
	"			o -CACHE_HEADERS=OFF",
	"			o -CACHE_HEADERS_ONLY=OFF",
	"			o -FIELD_NAMES=",
	"			o -INTER_FIELD_SEPARATORS=\" \"",
	"			o -INTRA_FIELD_SEPARATORS=\" \"",
	"			o -HEADERS=ON",
	"			o -INDEX_METHOD=0",
	"			o -INDEX_ORDER=ASCENDING",
	"			o -MAXIMUM_ROWS=0",
	"			o -PAGE_LINE_COUNT=60",
	"			o -OUTPUT_FILE=",
	"			o -PAGE_SEPARATORS=\"\\f\"",
	"			o -RECORD_LEADERS=",
	"			o -RECORD_TRAILERS=\"\\n\"",
	"\n",
	"	[@<parameter-include-file-name>]",
	"		Specifies the name of a parameter include file from which are to \
be read parameters to this program. Parameter include files may themselves \
contain parameter include file specifications.",
	"\n",
	"		When a parameter include file is encountered on the command line, \
the program will attempt to open it for reading. It is an error if the file \
so specified does not exist or can not be read.",
	"\n",
	"		Each line of the parameter include file is parsed for its \
parameters just as if those parameters were entered on the command line \
except for the following rules:",
	"\n",
	"			o A line in which the first non-whitespace character is a \
number-sign ('#') is considered to be the start of a comment and is ignored.",
	"\n",
	"			o Blank lines (that is, lines which are empty or which consist \
wholly of whitespace) are ignored.",
	"\n",
	NULL
};

/*	***********************************************************************	*/

int main(argc, argv)
int    argc;
char **argv;
{
	int                   return_code;
	DCR_PRT_CONTROL control_data;
	char                  error_text[DCR_MAX_ERROR_TEXT];

	memset(&control_data, '\0', sizeof(control_data));
	DCR_PRT_Init(&control_data);

	if (setlocale(LC_ALL, "C") == NULL) {
		strcpy(error_text, "Attempt to 'setlocale(LC_ALL, \"C\")' failed.");
		return_code = DCR_FAILURE;
	}
	else if ((return_code = GEN_SetResourceLimitsToMax(error_text)) !=
		DCR_SUCCESS)
		;
	else if ((return_code = DCR_AllocCacheControl(&control_data.
		cache_control_data, 100, error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_PRT_ResetText(&control_data,
			error_text)) == DCR_SUCCESS) {
#ifndef NARGS
			GEN_SIGNAL_SignalInit(NULL, NULL, &control_data, NULL, NULL,
				((void (*)(void *, int, int *, const char *)) DCR_PRT_End));
#else
			GEN_SIGNAL_SignalInit(NULL, NULL, &control_data, NULL, NULL,
				DCR_PRT_End);
#endif /* #ifndef NARGS */
			GEN_SIGNAL_SignalSet();
#ifndef NARGS
			return_code = GEN_GetParams(&control_data, ((unsigned int) argc),
				argv, &control_data.help_flag, &control_data.version_flag,
				((int (*)(void *, unsigned int, char **, int, unsigned int,
				const char *, char *)) DCR_PRT_Parse), error_text);
#else
			return_code = GEN_GetParams(&control_data, ((unsigned int) argc),
				argv, &control_data.help_flag, &control_data.version_flag,
				DCR_PRT_Parse, error_text);
#endif /* #ifndef NARGS */
			if (control_data.help_flag == DCR_TRUE) {
				DCR_PRT_Free(&control_data);
				GEN_SIGNAL_SignalDefault();
				GEN_DoFormatUsage(return_code, argv[0],
					"Help request with '-HELP' noted . . .", UsageList);
			}
			else if (control_data.version_flag == DCR_TRUE)
				fprintf(stderr, "%s Version Number %s\n", argv[0],
					DCR_PRT_VERSION_NUMBER);
			DCR_PRT_Free(&control_data);
			GEN_SIGNAL_SignalDefault();
		}
		DCR_CloseAllCaches(&control_data.cache_control_data);
	}

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n%s", error_text,
			(return_code != DCR_BAD_ARGS_FAILURE) ? "" :
			"       Help is available with the '-HELP' parameter.\n\n");

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_PRT_Parse(control_ptr, argc, argv, call_flag, current_arg,
	this_arg, error_text)
DCR_PRT_CONTROL  *control_ptr;
unsigned int      argc;
char            **argv;
int               call_flag;
unsigned int      current_arg;
const char       *this_arg;
char             *error_text;
{
	int            return_code = DCR_SUCCESS;
	char          *data_ptr;
	unsigned int   arg_length;
	double         tmp_double;
	int            error_flag;
	unsigned int   cache_index;
	unsigned int   index_method;
#ifndef NARGS
	void         (*fprintf_function)(void *, char *, ...);
	int          (*fwrite_function)(void *, unsigned int, unsigned int,
		void *);
#else
	void         (*fprintf_function)();
	int          (*fwrite_function)();
#endif /* #ifndef NARGS */
	void          *output_control_ptr;
	DCR_CACHE     *cache_ptr;
	char           genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if (!call_flag) {
		if (GEN_ArgParseTruth(this_arg, &error_flag,
			&control_ptr->binary_flag, genfuncs_error_text, &arg_length,
			&data_ptr, "-BINARY=", "-BINARY_OUT=", "-BINARY_OUTPUT=", NULL) ==
			GENFUNCS_TRUE) {
			if (error_flag == GENFUNCS_TRUE) {
				nstrcpy(error_text, genfuncs_error_text, DCR_MAX_ERROR_TEXT - 1);
				return_code = DCR_BAD_ARGS_FAILURE;
			}
		}
		else if (GEN_ArgParseTruth(this_arg, &error_flag,
			&control_ptr->cache_header_flag, genfuncs_error_text, &arg_length,
			&data_ptr, "-CACHE_HEADER=", "-CACHE_HEADERS=", NULL) ==
			GENFUNCS_TRUE) {
			if (error_flag == GENFUNCS_TRUE) {
				nstrcpy(error_text, genfuncs_error_text, DCR_MAX_ERROR_TEXT - 1);
				return_code = DCR_BAD_ARGS_FAILURE;
			}
		}
		else if (GEN_ArgParseTruth(this_arg, &error_flag,
			&control_ptr->cache_header_only_flag, genfuncs_error_text,
			&arg_length, &data_ptr, "-CACHE_HEADER_ONLY=",
			"-CACHE_HEADERS_ONLY=", NULL) == GENFUNCS_TRUE) {
			if (error_flag == GENFUNCS_TRUE) {
				nstrcpy(error_text, genfuncs_error_text, DCR_MAX_ERROR_TEXT - 1);
				return_code = DCR_BAD_ARGS_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-FIELD=", "-FIELDS=", "-FIELD_NAME=", "-FIELD_NAMES=", NULL) ==
			GENFUNCS_TRUE) {
			if (control_ptr->field_name_spec != NULL)
				free(control_ptr->field_name_spec);
			control_ptr->field_name_spec = NULL;
			if (*data_ptr) {
				if ((control_ptr->field_name_spec = strdup(data_ptr)) == NULL) {
					sprintf(error_text,
						"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
						"Unable to allocate memory for the", ((int) arg_length),
						((int) arg_length), this_arg, data_ptr,
						strlen(data_ptr) + 1);
					return_code = DCR_MEMORY_FAILURE;
				}
				else if (!(*nocontrl(noblank(control_ptr->field_name_spec)))) {
					free(control_ptr->field_name_spec);
					control_ptr->field_name_spec = NULL;
				}
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-FIELD_SEP=", "-FIELD_SEPS=", "-FIELD_SEPARATOR=",
			"-FIELD_SEPARATORS=", "-INTER_FIELD_SEP=", "-INTER_FIELD_SEPS=",
			"-INTER_FIELD_SEPARATOR=", "-INTER_FIELD_SEPARATORS=", NULL) ==
			GENFUNCS_TRUE) {
			if (control_ptr->inter_field_separator != NULL)
				free(control_ptr->inter_field_separator);
			if ((control_ptr->inter_field_separator = strdup(data_ptr)) ==
				NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
			else
				cstring(control_ptr->inter_field_separator,
					control_ptr->inter_field_separator, NULL);
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-INTRA_FIELD_SEP=", "-INTRA_FIELD_SEPS=", "-INTRA_FIELD_SEPARATOR=",
			"-INTRA_FIELD_SEPARATORS=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->intra_field_separator != NULL)
				free(control_ptr->intra_field_separator);
			if ((control_ptr->intra_field_separator = strdup(data_ptr)) ==
				NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
			else
				cstring(control_ptr->intra_field_separator,
					control_ptr->intra_field_separator, NULL);
		}
		else if (GEN_ArgParseTruth(this_arg, &error_flag,
			&control_ptr->header_flag, genfuncs_error_text, &arg_length,
			&data_ptr, "-HEADER=", "-HEADERS=", NULL) == GENFUNCS_TRUE) {
			if (error_flag == GENFUNCS_TRUE) {
				nstrcpy(error_text, genfuncs_error_text, DCR_MAX_ERROR_TEXT - 1);
				return_code = DCR_BAD_ARGS_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-INDEX=", "-INDEX_METHOD=", NULL) == GENFUNCS_TRUE) {
			if (!(*data_ptr))
				control_ptr->index_method = 0;
			else {
				tmp_double = atof(data_ptr);
				if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
					(tmp_double > UINT_MAX)) {
					sprintf(error_text,
						"%s '%-*.*s' ('%.500s') --- %s 0 to %u, inclusive.",
						"Invalid", ((int) arg_length), ((int) arg_length), this_arg,
						data_ptr, "expected an integer value in the range of",
						UINT_MAX);
					return_code = DCR_BAD_ARGS_FAILURE;
				}
				else
					control_ptr->index_method = ((unsigned int) tmp_double);
			}
		}
		else if ((!stricmp(this_arg, "-INDEX_ORDER=ASC")) ||
			(!stricmp(this_arg, "-INDEX_ORDER=ASCENDING")))
			control_ptr->reverse_flag = DCR_FALSE;
		else if ((!stricmp(this_arg, "-INDEX_ORDER=DESC")) ||
			(!stricmp(this_arg, "-INDEX_ORDER=DESCENDING")))
			control_ptr->reverse_flag = DCR_TRUE;
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr, "-MAX_ROW=",
			"-MAX_ROW_COUNT=", "-MAX_ROWS=", "-MAX_ROWS_COUNT=",
			"-MAX_RECORD=", "-MAX_RECORD_COUNT=", "-MAX_RECORDS=",
			"-MAX_RECORDS_COUNT=", "-MAXIMUM_ROW=",
			"-MAXIMUM_ROW_COUNT=", "-MAXIMUM_ROWS=", "-MAXIMUM_ROWS_COUNT=",
			"-MAXIMUM_RECORD=", "-MAXIMUM_RECORD_COUNT=", "-MAXIMUM_RECORDS=",
			"-MAXIMUM_RECORDS_COUNT=", NULL) == GENFUNCS_TRUE) {
			if (!(*data_ptr))
				control_ptr->maximum_row_count = 0;
			else {
				tmp_double = atof(data_ptr);
				if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
					(tmp_double > UINT_MAX)) {
					sprintf(error_text,
						"%s '%-*.*s' ('%.500s') --- %s 0 to %u, inclusive.",
						"Invalid", ((int) arg_length), ((int) arg_length), this_arg,
						data_ptr, "expected an integer value in the range of",
						UINT_MAX);
					return_code = DCR_BAD_ARGS_FAILURE;
				}
				else
					control_ptr->maximum_row_count = ((unsigned int) tmp_double);
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr, "-LINE_COUNT=",
			"-LINES_COUNT=", "-PAGE_LINE_COUNT=", "-PAGE_LINES_COUNT=", NULL) ==
			GENFUNCS_TRUE) {
			if (!(*data_ptr))
				control_ptr->page_line_count = 0;
			else {
				tmp_double = atof(data_ptr);
				if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
					(tmp_double > UINT_MAX)) {
					sprintf(error_text,
						"%s '%-*.*s' ('%.500s') --- %s 0 to %u, inclusive.",
						"Invalid", ((int) arg_length), ((int) arg_length), this_arg,
						data_ptr, "expected an integer value in the range of",
						UINT_MAX);
					return_code = DCR_BAD_ARGS_FAILURE;
				}
				else
					control_ptr->page_line_count = ((unsigned int) tmp_double);
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-OUT_FILE=", "-OUT_FILE_NAME=", "-OUTPUT_FILE=",
			"-OUTPUT_FILE_NAME=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->output_mfile_ptr != NULL) {
				mclose(control_ptr->output_mfile_ptr);
				control_ptr->output_mfile_ptr = NULL;
			}
			if (*data_ptr) {
				if ((control_ptr->output_mfile_ptr =
					mopen(data_ptr, "w")) == NULL) {
					sprintf(error_text, "%s '%-.500s' for writing --- ",
						"Unable to open the output file", data_ptr);
					DCR_AppendLastErrorString(error_text);
					return_code = DCR_SYSTEM_FAILURE;
				}
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-APP_FILE=", "-APP_FILE_NAME=", "-APPEND_FILE=",
			"-APPEND_FILE_NAME=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->output_mfile_ptr != NULL) {
				mclose(control_ptr->output_mfile_ptr);
				control_ptr->output_mfile_ptr = NULL;
			}
			if (*data_ptr) {
				if ((control_ptr->output_mfile_ptr =
					mopen(data_ptr, "r+")) == NULL) {
					sprintf(error_text, "%s '%-.500s' for appending --- ",
						"Unable to open the output file", data_ptr);
					DCR_AppendLastErrorString(error_text);
					return_code = DCR_SYSTEM_FAILURE;
				}
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-PAGE_SEP=", "-PAGE_SEPS=", "-PAGE_SEPARATOR=", "-PAGE_SEPARATORS=",
			NULL) == GENFUNCS_TRUE) {
			if (control_ptr->page_separator != NULL)
				free(control_ptr->page_separator);
			if ((control_ptr->page_separator = strdup(data_ptr)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
			else
				cstring(control_ptr->page_separator, control_ptr->page_separator,
					NULL);
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-REC_LEAD=", "-REC_LEADS=", "-REC_LEADER=", "-REC_LEADERS=",
			"-RECORD_LEAD=", "-RECORD_LEADS=", "-RECORD_LEADER=",
			"-RECORD_LEADERS=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->record_leader != NULL)
				free(control_ptr->record_leader);
			if ((control_ptr->record_leader = strdup(data_ptr)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
			else
				cstring(control_ptr->record_leader, control_ptr->record_leader,
					NULL);
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-REC_TRAIL=", "-REC_TRAILS=", "-REC_TRAILER=", "-REC_TRAILERS=",
			"-RECORD_TRAIL=", "-RECORD_TRAILS=", "-RECORD_TRAILER=",
			"-RECORD_TRAILERS=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->record_trailer != NULL)
				free(control_ptr->record_trailer);
			if ((control_ptr->record_trailer = 
				strdup(data_ptr)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
			else
				cstring(control_ptr->record_trailer, control_ptr->record_trailer,
					NULL);
		}
		else if (!stricmp(this_arg , "-RESET"))
			return_code = DCR_PRT_ResetText(control_ptr, error_text);
		else if ((return_code =
			DCR_OpenRead(&control_ptr->cache_control_data, this_arg, 0,
			0, 0, 0, &cache_ptr, &cache_index, error_text)) != DCR_SUCCESS)
			fprintf(stderr, "File: %s --- ERROR: %s\n", this_arg, error_text);
		else if ((return_code = DCR_MapDataAndIndices(cache_ptr,
			error_text)) != DCR_SUCCESS) {
			fprintf(stderr, "File: %s --- ERROR: %s\n", this_arg, error_text);
			DCR_CloseOneCache(cache_ptr);
		}
		else {
			fprintf(stderr, "File: %s\n", this_arg);
			if (control_ptr->index_method >= cache_ptr->index_count)
				fprintf(stderr,
					"    : %s (%u) %s '%s' ('%s') (from 0 to %u, %s) --- %s.\n",
					"The specified index method to use for cache output",
					control_ptr->index_method,
					"is not in the range of available indices for cache",
					this_arg, cache_ptr->header_ptr->cache_name,
					cache_ptr->index_count - 1, "inclusive",
					"using cache index method 0 for this cache");
			index_method =
				(control_ptr->index_method < cache_ptr->index_count) ?
				control_ptr->index_method : 0;
			if (control_ptr->output_mfile_ptr == NULL) {
				fprintf_function   =	((void (*)(void *, char *, ...)) fprintf);
				fwrite_function    = ((int (*)(void *, unsigned int,
					unsigned int, void *)) fwrite);
				output_control_ptr = stdout;
			}
			else {
				fprintf_function   =	((void (*)(void *, char *, ...)) mprintf);
				fwrite_function    = ((int (*)(void *, unsigned int,
					unsigned int, void *)) mwrite);
         	output_control_ptr = control_ptr->output_mfile_ptr;
				msetbuf(control_ptr->output_mfile_ptr,
					cache_ptr->header_ptr->actual_data_record_size * 1000);
			}
			if (control_ptr->binary_flag == DCR_FALSE) {
				if ((control_ptr->cache_header_flag == DCR_TRUE) ||
					(control_ptr->cache_header_only_flag == DCR_TRUE))
					DCR_EmitHeader(cache_ptr, NULL, fprintf_function,
						output_control_ptr);
				if (control_ptr->cache_header_only_flag != DCR_TRUE)
					return_code = DCR_EmitData(cache_ptr, index_method,
						control_ptr->reverse_flag, control_ptr->header_flag,
						control_ptr->maximum_row_count,
						control_ptr->page_line_count,
						control_ptr->inter_field_separator,
						control_ptr->intra_field_separator,
						control_ptr->page_separator, control_ptr->record_leader,
						control_ptr->record_trailer, ((unsigned int)
						((control_ptr->field_name_spec == NULL) ? 0 : 1)),
						&control_ptr->field_name_spec, &control_ptr->page_count,
						&control_ptr->format_line_count,
						&control_ptr->data_line_count, fprintf_function,
						output_control_ptr, error_text);
			}
			else
				return_code = DCR_EmitBinaryData(cache_ptr, index_method,
					control_ptr->reverse_flag, control_ptr->maximum_row_count,
					((unsigned int)
					((control_ptr->field_name_spec == NULL) ? 0 : 1)),
					&control_ptr->field_name_spec,
					&control_ptr->data_line_count, fwrite_function,
					output_control_ptr, error_text);
			DCR_CloseOneCache(cache_ptr);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_PRT_ResetText(control_ptr, error_text)
DCR_PRT_CONTROL *control_ptr;
char                  *error_text;
{
	int return_code;

	DCR_PRT_Free(control_ptr);

	if ((control_ptr->inter_field_separator = strdup(" ")) == NULL) {
		sprintf(error_text, "%s (%u bytes required).",
			"Unable to allocate memory for the inter-field separator", 2);
		return_code = DCR_MEMORY_FAILURE;
	}
	else if ((control_ptr->intra_field_separator = strdup("-")) == NULL) {
		sprintf(error_text, "%s (%u bytes required).",
			"Unable to allocate memory for the intra-field separator", 2);
		return_code = DCR_MEMORY_FAILURE;
	}
	else if ((control_ptr->record_leader = strdup("")) == NULL) {
		sprintf(error_text, "%s (%u bytes required).",
			"Unable to allocate memory for the record leader", 1);
		return_code = DCR_MEMORY_FAILURE;
	}
	else if ((control_ptr->record_trailer = strdup("\n")) == NULL) {
		sprintf(error_text, "%s (%u bytes required).",
			"Unable to allocate memory for the record trailer", 2);
		return_code = DCR_MEMORY_FAILURE;
	}
	else if ((control_ptr->page_separator = strdup("\f")) == NULL) {
		sprintf(error_text, "%s (%u bytes required).",
			"Unable to allocate memory for the page separator", 2);
		return_code = DCR_MEMORY_FAILURE;
	}
	else
		return_code = DCR_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

static void DCR_PRT_Init(control_ptr)
DCR_PRT_CONTROL *control_ptr;
{
	control_ptr->help_flag             = DCR_FALSE;
	control_ptr->version_flag          = DCR_FALSE;
	control_ptr->inter_field_separator = NULL;
	control_ptr->intra_field_separator = NULL;
	control_ptr->record_leader         = NULL;
	control_ptr->record_trailer        = NULL;
	control_ptr->page_separator        = NULL;
	control_ptr->field_name_spec       = NULL;
	control_ptr->index_method          = 0;
	control_ptr->page_line_count       = 60;
	control_ptr->maximum_row_count     = 0;
	control_ptr->output_mfile_ptr      = NULL;
	control_ptr->header_flag           = DCR_TRUE;
	control_ptr->binary_flag           = DCR_FALSE;
	control_ptr->cache_header_flag     = DCR_FALSE;
	control_ptr->cache_header_flag     = DCR_FALSE;
	control_ptr->reverse_flag          = DCR_FALSE;
	control_ptr->page_count            = 0;
	control_ptr->format_line_count     = 0;
	control_ptr->data_line_count       = 0;
}
/*	***********************************************************************	*/

static void DCR_PRT_Free(control_ptr)
DCR_PRT_CONTROL *control_ptr;
{
	if (control_ptr->inter_field_separator != NULL)
		free(control_ptr->inter_field_separator);
	if (control_ptr->intra_field_separator != NULL)
		free(control_ptr->intra_field_separator);
	if (control_ptr->record_leader != NULL)
		free(control_ptr->record_leader);
	if (control_ptr->record_trailer != NULL)
		free(control_ptr->record_trailer);
	if (control_ptr->page_separator != NULL)
		free(control_ptr->page_separator);
	if (control_ptr->field_name_spec != NULL)
		free(control_ptr->field_name_spec);
	if (control_ptr->output_mfile_ptr != NULL) {
		mtruncate(control_ptr->output_mfile_ptr,
			control_ptr->output_mfile_ptr->current_offset);
		mclose(control_ptr->output_mfile_ptr);
	}

	DCR_PRT_Init(control_ptr);
}
/*	***********************************************************************	*/

static void DCR_PRT_End(control_ptr, signal_number, exit_code_ptr,
	message_buffer)
DCR_PRT_CONTROL *control_ptr;
int                    signal_number;
int                   *exit_code_ptr;
const char            *message_buffer;
{
	DCR_CloseAllCaches(&control_ptr->cache_control_data);

	DCR_PRT_Free(control_ptr);
}
/*	***********************************************************************	*/

