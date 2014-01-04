/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Resolves a string containing C/C++ escape sequences.

	Revision History	:	1994-06-03 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <ctype.h>
#include <limits.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	cstring

	SYNOPSIS		:	return_ptr = cstring(in_string, out_string, out_length);

						char         *return_ptr;

						char         *in_string;

						char         *out_string;

						unsigned int *out_length;

	DESCRIPTION	:	Converts a string containing ANSI/ISO escape sequences to
						a string with the escape sequences resolved.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_string`` points to the null-terminated string to
						be converted.

						(.) ``out_string`` points the area of memory into which is
						to be written the converted string.

						(.) ``out_length`` points to an ``unsigned int`` into
						which will be placed the number of characters converted by
						this function. If ``out_length`` is a ''NULL'' pointer,
						however, it will not be de-referenced.

   RETURNS     :  The pointer ``out_string``.

	NOTES			:	This function supports the ANSI/ISO C standard escape
						sequences including trigraphs.

						This function permits the programmer to invoke it with
						``in_string`` and ``out_string`` parameters which may
						or may not point to the same string. This is done at the
						possible cost of some redundant stores.

	CAVEATS		:	Differences may be noted between the escape sequences
						emitted by this function and those emitted by compilers
						which are not ANSI-compliant.

	SEE ALSO		:	cstr2mem
						mem2cstr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock
 
	OUTPUT INDEX:	cstring
						String Conversion Functions:cstring
						STRFUNCS:String Conversion Functions:cstring
						String Functions:See STRFUNCS

	PUBLISH XREF:	cstring

	PUBLISH NAME:	cstring

	ENTRY CLASS	:	String Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *cstring(const char *in_string, char *out_string, unsigned int *out_length)
#else
char *cstring(in_string, out_string, out_length)
const char   *in_string;
char         *out_string;
unsigned int *out_length;
#endif /* #ifndef NARGS */
{
#if 1
	return(cstr2mem_basic(strlen(in_string), in_string, 0, out_length,
		out_string));
#else
/*
	CODE NOTE: To be removed.
*/
	unsigned int  count_1;
	const char   *tmp_ptr_1 = in_string;
	char         *tmp_ptr_2 = out_string;
	unsigned int  escape_value;
	unsigned int  tmp_escape_value;
	int           trigraph_char;

	while (*tmp_ptr_1) {
		if (*tmp_ptr_1 == '\\') {
			if (!tmp_ptr_1[1])
				*tmp_ptr_2 = '\\';
			else {
				tmp_ptr_1++;
				switch (*tmp_ptr_1) {
					case '\"'	:
						*tmp_ptr_2 = '\"';
						break;
					case '\''	:
						*tmp_ptr_2 = '\'';
						break;
					case '?'		:
						*tmp_ptr_2 = '\?';
						break;
					case '\\'	:
						*tmp_ptr_2 = '\\';
						break;
					case 'a'	:
						*tmp_ptr_2 = '\a';
						break;
					case 'b'	:
						*tmp_ptr_2 = '\b';
						break;
					case 'f'	:
						*tmp_ptr_2 = '\f';
						break;
					case 'n'	:
						*tmp_ptr_2 = '\n';
						break;
					case 'r'	:
						*tmp_ptr_2 = '\r';
						break;
					case 't'	:
						*tmp_ptr_2 = '\t';
						break;
					case 'v'	:
						*tmp_ptr_2 = '\v';
						break;
					default		:
						if ((isdigit(*tmp_ptr_1)) && (*tmp_ptr_1 < '8')) {
							escape_value = 0;
							for (count_1 = 0; count_1 < 3; count_1++, tmp_ptr_1++) {
								if ((!isdigit(*tmp_ptr_1)) || (*tmp_ptr_1 > '7') ||
									((tmp_escape_value = ((escape_value * 8) +
									(*tmp_ptr_1 - '0'))) > UCHAR_MAX))
									break;
								escape_value = tmp_escape_value;
							}
							tmp_ptr_1--;
							*tmp_ptr_2 = escape_value;
						}
						else if ((*tmp_ptr_1 == 'x') && isxdigit(tmp_ptr_1[1])) {
							tmp_ptr_1++;
							escape_value = 0;
							for (count_1 = 0; count_1 < 2; count_1++, tmp_ptr_1++) {
								if ((!isxdigit(*tmp_ptr_1)) || ((tmp_escape_value =
									((escape_value * 16) + ((isdigit(*tmp_ptr_1)) ?
									(*tmp_ptr_1 - '0') : (((isupper(*tmp_ptr_1)) ?
									(*tmp_ptr_1 - 'A') : (*tmp_ptr_1 - 'a')) + 10)))) >
									UCHAR_MAX))
									break;
								escape_value = tmp_escape_value;
							}
							tmp_ptr_1--;
							*tmp_ptr_2 = escape_value;
						}
						else
							*tmp_ptr_2 = *tmp_ptr_1;
						break;
				}
			}
		}
		else if ((*tmp_ptr_1 == '?') && (*(tmp_ptr_1 + 1) == '?') &&
			((trigraph_char = chrindx(tmp_ptr_1[2], "(/)'<!>-=")) > -1)) {
			*tmp_ptr_2  = "[\\]^{|}~#"[trigraph_char];
			tmp_ptr_1  += 2;
		}
		else
			*tmp_ptr_2 = *tmp_ptr_1;
		tmp_ptr_1++;
		tmp_ptr_2++;
	}

	*tmp_ptr_2 = '\0';

	if (out_length != NULL)
		*out_length = ((unsigned int) (tmp_ptr_2 - out_string));

	return(out_string);
#endif /* #if 1 */
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

static char *TestLineList[] = {
/*  01234567890123456789012 */
	"This is a simple test.",
/*  012345678901234567890123  456789012345678901234567890123 */
	"This has an embedded tab\\tin the middle of the string.",
/*  01234567890123456789012345    6    7    8901234  56789012 */
	"This has octal sequences: \\101\\102\\103 ---> \\8 (tab)",
/*  01234567890123456789012345678901    2    3    4567890    1   23456789 */
	"This has hexadecimal sequences: \\x41\\x42\\x43 ---> \\x4a\\x8 (tab)",
/*  012345678901234567890123456789012345678 9012345 6 */
	"This does not have trigraph sequences: \? ---> \?",
/*  01234567890123456789012345678   9012345   67 */
	"This has trigraph sequences: \??( ---> \??)"
};

static unsigned int TestLineCount =
	sizeof(TestLineList) / sizeof(TestLineList[0]);

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int            return_code = 0;
	unsigned int   in_line_count;
	char         **in_line_list;
	unsigned int   count_1;
	unsigned int   count_2;
	unsigned int   result_length_1;
	unsigned int   result_length_2;
   FILE          *file_ptr;
	char           buffer[1024];

#ifdef __MSDOS__
	char             *compile_string =
		"bcc -A -Ic:\borlandc\include -Lc:\borlandc\lib cstr_tst.c";
	char             *execute_string = "cstr_tst.exe";
#else
	char             *compile_string =
		"cc -DNARGS -Dconst=\"\" -Dsize_t=\"unsigned int\" cstr_tst.c";
	char             *execute_string = "a.out";
#endif /* #ifdef __MSDOS__ */

	fprintf(stderr, "Test routine for 'cstring()'\n");
	fprintf(stderr, "---- ------- --- -----------\n\n");

	in_line_count = (argc > 1) ? (argc - 1) : TestLineCount;
	in_line_list  = (argc > 1) ? (argv + 1) : TestLineList;

	fprintf(stderr, "%s\n",
		"--------------------------------------------------------------------");
	fprintf(stderr, "Test One: Compilation Test\n");
	if ((file_ptr = fopen("cstr_tst.c", "w")) == NULL) {
		fprintf(stderr, "Unable to open file 'cstr_tst.c' for output.\n");
		return_code = -1;
	}
	else {
		fprintf(file_ptr, "#include <memory.h>\n");
		fprintf(file_ptr, "#include <stdio.h>\n\n");
		fprintf(file_ptr, "#ifndef NARGS\n");
		fprintf(file_ptr, "int main(void);\n");
		fprintf(file_ptr, "#else\n");
		fprintf(file_ptr, "int main();\n");
		fprintf(file_ptr, "#endif /* #ifndef NARGS */\n\n");
		fprintf(file_ptr, "unsigned int StringCount = %u;\n\n", in_line_count);
		fprintf(file_ptr, "unsigned int StringLengthList[] = {\n");
		for (count_1 = 0; count_1 < in_line_count; count_1++) {
			cstring(in_line_list[count_1], buffer, &result_length_1);
			fprintf(file_ptr, "\t%u%s", result_length_1,
				(count_1 < (in_line_count - 1)) ? ",\n" : "\n};\n\n");
		}
		fprintf(file_ptr, "static unsigned char *CompiledStringList[] = {\n");
		for (count_1 = 0; count_1 < in_line_count; count_1++)
			fprintf(file_ptr, "\t\"%s\"%s", in_line_list[count_1],
				(count_1 < (in_line_count - 1)) ? ",\n" : "\n};\n\n");
		for (count_1 = 0; count_1 < in_line_count; count_1++) {
			cstring(in_line_list[count_1], buffer, &result_length_1);
			fprintf(file_ptr, "\t/* %-*.*s */\n",
				result_length_1, ((int) result_length_1), buffer);
			fprintf(file_ptr, "static unsigned char BaseString_%05u[%u] = { ",
				count_1, result_length_1 + 1);
			for (count_2 = 0; count_2 <= result_length_1; count_2++)
				fprintf(file_ptr, "%u%s", ((unsigned int)
					((unsigned char) buffer[count_2])),
					(count_2 < result_length_1) ? ", " : " };\n");
			fprintf(file_ptr, "%s",
				(count_1 < (in_line_count - 1)) ? "\n" : "\n\n");
		}
		fprintf(file_ptr, "static unsigned char *BaseStringList[] = {\n");
		for (count_1 = 0; count_1 < in_line_count; count_1++)
			fprintf(file_ptr, "\tBaseString_%05u%s", count_1,
				(count_1 < (in_line_count - 1)) ? ",\n" : "\n};\n\n");
		fprintf(file_ptr, "int main()\n{\n");
		fprintf(file_ptr, "\tint          return_code = 0;\n");
		fprintf(file_ptr, "\tunsigned int count_1;\n\n");
		fprintf(file_ptr,
			"\tfor (count_1 = 0; count_1 < StringCount; count_1++) {\n");
		fprintf(file_ptr,
	"\t\tif (memcmp(CompiledStringList[count_1], BaseStringList[count_1],\n");
		fprintf(file_ptr, "\t\t\tStringLengthList[count_1])) {\n");
		fprintf(file_ptr,
"\t\t\tfprintf(stdout, \"Difference in string number %%u\\n\", count_1);\n");
		fprintf(file_ptr, "\t\t\tfprintf(stdout, \">>> [%%s]\\n\", %s);\n",
			"CompiledStringList[count_1]");
		fprintf(file_ptr, "\t\t\tfprintf(stdout, \">>> [%%s]\\n\", %s);\n",
			"BaseStringList[count_1]");
#if 0
		fprintf(file_ptr,
			"\t\t\tfor (count_2 = 0; count_2 < %s; count_2++) {\n",
			"StringLengthList[count_1]");
		fprintf(file_ptr, "\t\t\t\tif (%s !=\n\t\t\t\t\t%s)\n",
			"CompiledStringList[count_1][count_2]",
			"BaseStringList[count_1][count_2]");
		fprintf(file_ptr, "\t\t\t\t\tfprintf(stdout, \"%%c\", %s);\n",
			"CompiledStringList[count_1][count_2]");
		fprintf(file_ptr, "\t\t\t}\n");
#endif /* #if 0 */
		fprintf(file_ptr, "\t\t\treturn_code = -1;\n");
		fprintf(file_ptr, "\t\t}\n");
		fprintf(file_ptr, "\t}\n");
		fprintf(file_ptr, "\n");
		fprintf(file_ptr, "\treturn(return_code);\n");
		fprintf(file_ptr, "}\n");
		fclose(file_ptr);
		fprintf(stderr, "Compiling test program . . .");
		system(compile_string);
		fprintf(stderr, "\n");
		fprintf(stderr, "Executing test program . . .\n");
		system(execute_string);
	}
	fprintf(stderr, "%s\n\n",
		"--------------------------------------------------------------------");

	fprintf(stderr, "%s\n",
		"--------------------------------------------------------------------");
	fprintf(stderr, "Test Two: Argument Test\n");
	for (count_1 = 0; count_1 < in_line_count; count_1++) {
		cstring(in_line_list[count_1], buffer, &result_length_1);
		cstring(in_line_list[count_1], in_line_list[count_1], &result_length_2);
		if ((result_length_1 != result_length_2) ||
			memcmp(buffer, in_line_list[count_1], result_length_1)) {
			fprintf(stderr, "%05u:Original String:[%s]\n",
				count_1, in_line_list[count_1]);
			fprintf(stderr, "     :Different Args :[%-*.*s] = %u\n",
				result_length_1, ((int) result_length_1), buffer, result_length_1);
			fprintf(stderr, "     :Same Args      :[%-*.*s] = %u\n",
				result_length_2, ((int) result_length_2), in_line_list[count_1],
				result_length_2);
			return_code = -1;
		}
	}
	fprintf(stderr, "%s\n\n",
		"--------------------------------------------------------------------");

	if (return_code != STRFUNCS_SUCCESS)
		fprintf(stderr, "\n\nFailed regression tests.\n\n");

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

