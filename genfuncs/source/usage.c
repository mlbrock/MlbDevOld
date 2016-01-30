/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Functions to handle emission of executable usage
								information.

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
/*	***********************************************************************	*/

#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Some local manifest constants . . .												*/
/*	***********************************************************************	*/

#define GEN_USAGE_LEFT_PADDING			3

#define GEN_USAGE_OUTPUT_LENGTH			77

#define GEN_USAGE_MAX_LENGTH				\
	(GEN_USAGE_OUTPUT_LENGTH - GEN_USAGE_LEFT_PADDING)

#define GEN_USAGE_TAB_SETTING				8

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	GEN_DoSimpleUsage

	SYNOPSIS		:	void GEN_DoSimpleUsage(exit_code, program_name,
							exit_message, usage_string);

						int         exit_code;

						const char *program_name;

						const char *exit_message;

						const char *usage_string;

	DESCRIPTION	:	Emits a usage string.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``exit_code`` is the value with which this function is
						to exit to the operating system. It is passed to the
						``exit()`` function.

						(-) If ``exit_code`` is non-zero, the usage text emitted
						by this function will be sent to ``stderr``. Otherwise, it
						will be sent to ``stdout``.

						(.) ``program_name`` is the name of the executable, as
						received at program start-up in ''argv[0]''.

						(-) Directory specifiers in ``program_name`` will be
						removed by this function before being displayed.

						(.) ``exit_message`` is a string to be displayed by the
						function before the usage text.

						(.) ``usage_string`` contains the string which describes
						the correct usage of the program.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_DoUsage

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2016 Michael L. Brock

	OUTPUT INDEX:	GEN_DoSimpleUsage
						Usage Text Formatting Functions:GEN_DoSimpleUsage
						GENFUNCS:Functions:GEN_DoSimpleUsage
						GENFUNCS:Usage Text Formatting Functions:GEN_DoSimpleUsage
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_DoSimpleUsage

	PUBLISH NAME:	GEN_DoSimpleUsage

	ENTRY CLASS	:	Usage Text Formatting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void GEN_DoSimpleUsage(int exit_code, const char *program_name,
	const char *exit_message, const char *usage_string)
#else
void GEN_DoSimpleUsage(exit_code, program_name, exit_message, usage_string)
int         exit_code;
const char *program_name;
const char *exit_message;
const char *usage_string;
#endif /* #ifndef NARGS */
{
	char *usage_string_list[2];

	usage_string_list[0] = ((char *) usage_string);
	usage_string_list[1] = NULL;

	GEN_DoUsage(exit_code, program_name, exit_message, usage_string_list);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	GEN_DoUsage

	SYNOPSIS		:	void GEN_DoUsage(exit_code, program_name, exit_message,
							usage_string_list);

						int          exit_code;

						const char  *program_name;

						const char  *exit_message;

						char       **usage_string_list;

	DESCRIPTION	:	Emits a array of strings which describe program usage.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``exit_code`` is the value with which this function is
						to exit to the operating system. It is passed to the
						``exit()`` function.

						(-) If ``exit_code`` is non-zero, the usage text emitted
						by this function will be sent to ``stderr``. Otherwise, it
						will be sent to ``stdout``.

						(.) ``program_name`` is the name of the executable, as
						received at program start-up in ''argv[0]''.

						(-) Directory specifiers in ``program_name`` will be
						removed by this function before being displayed.

						(.) ``exit_message`` is a string to be displayed by the
						function before the usage text.

						(.) ``usage_string_list`` is an array of pointers to
						''char'' which will be displayed by this program with
						word-wrapping such that no line will exceed 77 characters
						in length.

						(-) The last element in ``usage_string_list`` must contain
						a ''NULL'' pointer. This indicates to the function that
						no further strings in the list are to be processed.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_DoFormatUsage

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2016 Michael L. Brock

	OUTPUT INDEX:	GEN_DoUsage
						Usage Text Formatting Functions:GEN_DoUsage
						GENFUNCS:Functions:GEN_DoUsage
						GENFUNCS:Usage Text Formatting Functions:GEN_DoUsage
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_DoUsage

	PUBLISH NAME:	GEN_DoUsage

	ENTRY CLASS	:	Usage Text Formatting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void GEN_DoUsage(int exit_code, const char *program_name,
	const char *exit_message, char **usage_string_list)
#else
void GEN_DoUsage(exit_code, program_name, exit_message, usage_string_list)
int          exit_code;
const char  *program_name;
const char  *exit_message;
char       **usage_string_list;
#endif /* #ifndef NARGS */
{
	const char   *prog           = program_name;
	int           current_column = 0;
	int           tab_count      = 0;
	FILE         *out_file_ptr   = (exit_code) ? stderr : stdout;
	char          last_character;
	const char   *in_string;
	char          tmp_buffer[GEN_USAGE_MAX_LENGTH + 1];

	prog = extract_file_name(prog);

	if (usage_string_list == NULL)
		fprintf(out_file_ptr, "%s\n\nProgram '%s' is exiting . . .\n\n",
			exit_message, prog);
	else {
		fprintf(out_file_ptr, "%s\n\nUSAGE FOR PROGRAM %s:\n\n",
			exit_message, prog);
		while (*usage_string_list != NULL) {
			in_string = *usage_string_list++;
			while ((in_string = strwrap(in_string, &current_column,
				GEN_USAGE_MAX_LENGTH, &tab_count, GEN_USAGE_TAB_SETTING, 1,
				&last_character, tmp_buffer)) != NULL)
				fprintf(out_file_ptr, "   %s\n", tmp_buffer);
			current_column = GEN_USAGE_LEFT_PADDING;
			tab_count      = 0;
		}
	}

#ifndef TEST_MAIN
	exit(exit_code);
#endif /* #ifdef TEST_MAIN */
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	GEN_DoFormatUsage

	SYNOPSIS		:	void GEN_DoFormatUsage(exit_code, program_name,
							exit_message, usage_string_list);

						int          exit_code;

						const char  *program_name;

						const char  *exit_message;

						char       **usage_string_list;

	DESCRIPTION	:	Emits a array of strings which describe program usage.
						The strings are emitted with intelligent tab interpretation.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``exit_code`` is the value with which this function is
						to exit to the operating system. It is passed to the
						``exit()`` function.

						(-) If ``exit_code`` is non-zero, the usage text emitted
						by this function will be sent to ``stderr``. Otherwise, it
						will be sent to ``stdout``.

						(.) ``program_name`` is the name of the executable, as
						received at program start-up in ''argv[0]''.

						(-) Directory specifiers in ``program_name`` will be
						removed by this function before being displayed.

						(.) ``exit_message`` is a string to be displayed by the
						function before the usage text.

						(.) ``usage_string_list`` is an array of pointers to
						''char'' which will be displayed by this program with
						word-wrapping such that no line will exceed 77 characters
						in length.

						(-) The last element in ``usage_string_list`` must contain
						a ''NULL'' pointer. This indicates to the function that
						no further strings in the list are to be processed.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_DoUsage

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2016 Michael L. Brock

	OUTPUT INDEX:	GEN_DoFormatUsage
						Usage Text Formatting Functions:GEN_DoFormatUsage
						GENFUNCS:Functions:GEN_DoFormatUsage
						GENFUNCS:Usage Text Formatting Functions:GEN_DoFormatUsage
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_DoFormatUsage

	PUBLISH NAME:	GEN_DoFormatUsage

	ENTRY CLASS	:	Usage Text Formatting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void GEN_DoFormatUsage(int exit_code, const char *program_name,
	const char *exit_message, char **usage_string_list)
#else
void GEN_DoFormatUsage(exit_code, program_name, exit_message,
	usage_string_list)
int          exit_code;
const char  *program_name;
const char  *exit_message;
char       **usage_string_list;
#endif /* #ifndef NARGS */
{
	const char   *prog           = program_name;
	int           current_column = 0;
	int           tab_count      = 0;
	FILE         *out_file_ptr   = (exit_code) ? stderr : stdout;
   const char   *tmp_ptr;
	unsigned int  start_column;
	unsigned int  output_width;
	char          last_character;
	const char   *in_string;
	char          tmp_buffer[GEN_USAGE_OUTPUT_LENGTH + 1];

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We need to get the file name without such things as the drive	*/
	/*	specification or directory hierarchy. Different for each OS . . .	*/
	/*	*****************************************************************	*/
#ifdef __MSDOS__
		prog = ((tmp_ptr = strrchr(prog, ':') ) != NULL) ? (tmp_ptr + 1) : prog;
		prog = ((tmp_ptr = strrchr(prog, '\\')) != NULL) ? (tmp_ptr + 1) : prog;
		prog = ((tmp_ptr = strrchr(prog, '/') ) != NULL) ? (tmp_ptr + 1) : prog;
#else
# ifdef _Windows
		prog = ((tmp_ptr = strrchr(prog, ':') ) != NULL) ? (tmp_ptr + 1) : prog;
		prog = ((tmp_ptr = strrchr(prog, '\\')) != NULL) ? (tmp_ptr + 1) : prog;
		prog = ((tmp_ptr = strrchr(prog, '/') ) != NULL) ? (tmp_ptr + 1) : prog;
# else
#  ifdef _VMS_
		prog = ((tmp_ptr = strrchr(prog, ']') ) != NULL) ? (tmp_ptr + 1) : prog;
#  else
		prog = ((tmp_ptr = strrchr(prog, '/') ) != NULL) ? (tmp_ptr + 1) : prog;
#  endif /* # ifdef _VMS_ */
# endif /* # ifdef _Windows */
#endif /* #ifdef __MSDOS__ */
	/*	*****************************************************************	*/

	if (usage_string_list == NULL)
		fprintf(out_file_ptr, "%s\n\nProgram '%s' is exiting . . .\n\n",
			exit_message, prog);
	else {
		fprintf(out_file_ptr, "%s\n\nUSAGE FOR PROGRAM %s:\n\n",
			exit_message, prog);
		while (*usage_string_list != NULL) {
			in_string = *usage_string_list++;
			tmp_ptr   = in_string;
			while (*tmp_ptr == '\t')
				tmp_ptr++;
			start_column    = ((unsigned int) (tmp_ptr - in_string)) + 1;
			start_column    = ((start_column * GEN_USAGE_LEFT_PADDING) >
				((GEN_USAGE_MAX_LENGTH / GEN_USAGE_LEFT_PADDING) *
				GEN_USAGE_LEFT_PADDING)) ? 5 : start_column;
			start_column   *= GEN_USAGE_LEFT_PADDING;
			output_width    = GEN_USAGE_OUTPUT_LENGTH - start_column;
			current_column  = 0;
			tab_count       = 0;
			while ((tmp_ptr = strwrap(tmp_ptr, &current_column,
				output_width, &tab_count, GEN_USAGE_TAB_SETTING, 1,
				&last_character, tmp_buffer)) != NULL)
				fprintf(out_file_ptr, "%*.*s%s\n",
					((int) start_column), ((int) start_column), " ", tmp_buffer);
		}
	}

#ifndef TEST_MAIN
	exit(exit_code);
#endif /* #ifdef TEST_MAIN */
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (void));

char *SimpleTestList[]  = {
	"Here is a short usage line.",
	"Here is a much longer option line with lots of white-space for the \
purpose of having a place to break the line.",
	"This line\nhas lots of\nembedded line-feed\ncharacters."
};

char *MultiTestList[]   = {
	"Line one.",
	"Line two.",
	"A very, very, very long line number three with lots of additional words \
to test the ability of the routine to do word-wrapping.",
	"This is the fourth line.",
	"\tThis line begins with a tab.",
	"This is the last line.",
	NULL
};

static const char *UsageList[] = {
	"Usage:",
	"------",
	"	prtcache [<a mixture of '-' options, '@' commands, and filenames>]",
	"\n",
	"Description:",
	"------------",
	"	This program prints the contents of an data cache repository.",
	"\n",
	"	Invocation of the program may include any number of parameters \
which may be used to specify the nature of the resulting output. \
There are three types of parameters:",
	"\n",
	"		o  '-'-prefaced options, which specify any one of a number of \
options (which are described in the 'Options', below);",
	"\n",
	"		o  '@'-prefaced file names, which indicate that the indicated \
file name is to be parsed for parameters, and;",
	"\n",
	"		o  all other parameters which are taken to be the names of caches \
to be opened.",
	"\n",
	"Operation:",
	"----------",
	"	Program operation is as follows:",
	"\n",
	"		o  The program initializes itself to the default settings (these \
are the same settings described in the 'Options' section \
under the description of the '-RESET' parameter).",
	"\n",
	"		o  The command line is scanned for options.",
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
	"	-HELP",
	"		Displays this text. Note that if this parameter appears on the \
command-line, the program will exit after displaying the help text.",
	"\n",
	"	-BINARY={ ON | OFF | TRUE | FALSE | YES | NO }",
	"		Emits the cache records in binary format. Note that other options \
which may be specific to human-readable output (such as 'HEADERS', \
'LINE_COUNT', et cetera) are not effective for this option.",
	"\n",
	"		The default for this option is 'OFF'.",
	"\n",
	"	-CACHE_HEADER[S]={ ON | OFF | TRUE | FALSE | YES | NO }",
	"		Specifies that text descriptive of the cache control header is \
to be emitted.",
	"\n",
	"		The default for this option is 'OFF'.",
	"\n",
	"	-FIELD[_NAME][S]=<field-list>",
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
	"	-[INTER_]FIELD_SEP[ARATOR][S]=<string>",
	"		Specifies the string to be used between fields emitted by this \
program.",
	"\n",
	"		The default for this option is a single space character (' ').",
	"\n",
	"	-INTRA_FIELD_SEP[ARATOR][S]=<string>",
	"		Specifies the string to be used within multi-part fields emitted \
by this program.",
	"\n",
	"		The default for this option is a single hyphen character ('-').",
	"\n",
	"	-HEADER[S]={ ON | OFF | TRUE | FALSE | YES | NO }",
	"		Specifies that column headers consisting of the field name are to \
be emitted for each column in the output emitted.",
	"\n",
	"		The default for this option is 'ON'.",
	"\n",
	"	-INDEX[_METHOD]=<index-method-number>",
	"		Specifies the index method to be used in emitting records.",
	"\n",
	"		The default for this option is '0'.",
	"\n",
	"	-INDEX_ORDER={ASC[ENDING] | DESC[ENDING] }",
	"		Specifies the order in which the cache index is to be traversed.",
	"\n",
	"		The default for this option is 'ASCENDING'.",
	"\n",
	"	-MAX[IMUM]_ROWS=<max-row-count>",
	"		Specifies the maximum number of rows to be emitted by the program. \
If the <max-row-count> component of the option is not present or is equal to \
zero ('0'), no maximum will be imposed while emitting cache rows.",
	"\n",
	"		The default for this option is '0'.",
	"\n",
	"	-[PAGE_]LINE_COUNT=<lines-per-page>",
	"		Specifies the number of lines to be emitted on a single page. \
If the <lines-per-page> component of the option is not present or is equal \
to zero ('0'), no page formatting will occur.",
	"\n",
	"		The default for this option is '60'.",
	"\n",
	"	-OUTPUT_FILE=<file-name>",
	"		Specifies the name of a file to which output is to be written \
instead of 'stdout'. If the <file-name> component of this option is not \
present, any existing output file will be closed and subsequent output \
will be routed to 'stdout'.",
	"\n",
	"		Note that <file-name> will be opened in write-mode, which will \
result in the file being truncated to zero-length. To append output to a \
file, use the '-APPEND_FILE=' option instead (see below).",
	"\n",
	"	-APPEND_FILE=<file-name>",
	"		Specifies the name of a file to which output is to be appended \
instead of 'stdout'. If the <file-name> component of this option is not \
present, any existing output file will be closed and subsequent output \
will be routed to 'stdout'.",
	"\n",
	"	-PAGE_SEP[ARATOR][S]=<string>",
	"		Specifies the string to be used to separate pages. If the <string> \
component of this option is not present or is empty, nothing will separate \
pages.",
	"\n",
	"		The default for this option is an ASCII form-feed ('\\f').",
	"\n",
	"	-RECORD_LEAD[ER][S]=<string>",
	"		Specifies the string with which to prefix records as they are \
output. If the <string> component of this option is not present or is empty, \
nothing will prefix record output.",
	"\n",
	"		The default for this option is 'NULL'.",
	"\n",
	"	-RECORD_TRAIL[ER][S]=<string>",
	"		Specifies the string with which to append to records as they are \
output. If the <string> component of this option is not present or is empty, \
nothing will be appended to record output.",
	"\n",
	"		The default for this option is an ASCII line-feed ('\\n').",
	"\n",
	"	-RESET",
	"		Specifies that all settings are to be reset to their initial \
values. These values are as follow:",
	"\n",
	"			o -BINARY=OFF",
	"			o -CACHE_HEADERS=OFF",
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
be parameters to this module. Parameter include files may themselves contain \
parameter include file specifications.",
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

int main()
{
	unsigned int count_1;
	char         buffer[100];

	printf("===========================================================\n");

	for (count_1 = 0; count_1 <
		(sizeof(SimpleTestList) / sizeof(SimpleTestList[0])); count_1++) {
		sprintf(buffer, "Test of 'GEN_DoSimpleUsage()' number %u",
			count_1);
		GEN_DoSimpleUsage(0, "<program-name>", buffer, SimpleTestList[count_1]);
		printf("-----------------------------------------------------------\n");
	}

	printf("===========================================================\n");

	GEN_DoUsage(0, "<program-name>", "Test of 'GEN_DoUsage()'", MultiTestList);

	printf("===========================================================\n");

	GEN_DoFormatUsage(0, "<program-name>",
		"Test of 'GEN_DoFormattedUsage()'", ((char **) UsageList));

	printf("===========================================================\n");

	return(0);
}

#endif /* #ifdef TEST_MAIN */

