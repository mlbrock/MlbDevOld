/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits a buffer of bytes.

	Revision History	:	1993-10-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	GEN_EmitBufferData

	SYNOPSIS		:	GEN_EmitBufferData(output_function, output_control,
							left_prefix, left_padding, max_length, print_chars_flag,
							in_radix, in_data_length, data_ptr);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

						const char            *left_prefix;

						unsigned int           left_padding;

						unsigned int           max_length;

						int                    print_chars_flag;

						unsigned int           in_radix;

						unsigned int           in_data_length;

						const void            *data_ptr;

	DESCRIPTION	:	Emits a buffer of bytes formatted for human-readability.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``output_function`` is a pointer to an variable-argument
						``fprintf``-like function with a function prototype like
						the following (or an argument list with types which can be
						reasonable coerced into the following):

						{|@|}''int'' ``output_function``(''void *''``output_control``, ''const char *'', ...);

						(-) The function will call this function to emit the output.

						(-) If ``output_function`` is ''NULL'', it will be set to
						the address of ``fprintf``.

						(.) ``output_control`` is the first argument to the function
						indicated by the ``output_function`` parameter.

						(-) In the case where the ``output_function`` parameter is
						``fprintf``, the ``output_control`` parameter might be
						``stdin``, ``stdout``, or the value returned by a call to
						the function ``fopen``.

						(-) If ``output_control`` is ''NULL'', it will be set to
						``stdout``.

						(.) ``left_prefix`` specifies a string to be printed at
						the beginning of each block of bytes. It may be ''NULL''.

						(.) ``left_padding`` specifies the amount of white-space
						to be printed at the beginning of each line. When the
						``left_prefix`` parameter is not ''NULL'', it is usually
						equal to the length of the ``left_prefix`` string.

						(.) ``max_length`` is the maximum number of bytes to emit
						before emitting a line-feed character (ASCII 10).

						(.) ``print_chars_flag``, if non-zero, specifies that a
						line of bytes in character format is to printed above the
						line of bytes in the specified radix.

						(-) Bytes for which the ``ctype.h`` macro ``isprint`` is
						true will be printed in ASCII format. All others will be
						printed as a question-mark (''?'').

						(.) ``in_radix`` is the radix to use for emitting bytes in
						the buffer.

						(-) If ``in_radix`` is less than ''2'' or greater than
						''36'', it will be coerced to ''10''.

						(.) ``in_data_length`` is the length of the buffer to which
						the ``data_ptr`` parameter points.

						(.) ``data_ptr`` points to the buffer to be emitted by this
						function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

	OUTPUT INDEX:	GEN_EmitBufferData
						Miscellaneous Functions:GEN_EmitBufferData
						GENFUNCS:Functions:GEN_EmitBufferData
						GENFUNCS Miscellaneous Functions:GEN_EmitBufferData
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_EmitBufferData

	PUBLISH NAME:	GEN_EmitBufferData

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void GEN_EmitBufferData(STR_FUNC_TYPE_fprintf output_function,
	void *output_control, const char *left_prefix, unsigned int left_padding,
	unsigned int max_length, int print_chars_flag, unsigned int in_radix,
	unsigned int in_data_length, const void *data_ptr)
#else
void GEN_EmitBufferData(output_function, output_control, left_prefix,
	left_padding, max_length, print_chars_flag, in_radix, in_data_length,
	data_ptr)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
const char            *left_prefix;
unsigned int           left_padding;
unsigned int           max_length;
int                    print_chars_flag;
unsigned int           in_radix;
unsigned int           in_data_length;
const void            *data_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
   unsigned int item_count;
	unsigned int data_length;
	unsigned int test_value;
	unsigned int radix_length = 1;
	char         number_buffer[STR_VAL2STR_MAX_LEN + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	if (!in_data_length) {
		left_prefix  = (left_prefix == NULL) ? "" : left_prefix;
		left_padding = (!left_padding) ? strlen(left_prefix) : left_padding;
		if (*left_prefix)
			(*output_function)(output_control, "%-*.*s\n",
				left_padding, left_padding, left_prefix);
	}
	else {
		in_radix   = ((in_radix < 2) || (in_radix > 36)) ? 10 : in_radix;
		test_value = in_radix;
		while (test_value < 255) {
			test_value *= in_radix;
			radix_length++;
		}
		item_count   = (radix_length >= max_length) ? 1 :
			(max_length / (radix_length + 1));
		left_prefix  = (left_prefix == NULL) ? "" : left_prefix;
		left_padding = (!left_padding) ? strlen(left_prefix) : left_padding;
		data_length  = in_data_length;
		while (data_length) {
			item_count = (data_length < item_count) ? data_length : item_count;
			if (left_padding) {
				if (in_data_length == data_length)
					(*output_function)(output_control, "%-*.*s",
						left_padding, left_padding, left_prefix);
				else
					(*output_function)(output_control, "%-*.*s",
						left_padding, left_padding, " ");
			}
			if (print_chars_flag) {
				for (count_1 = 0; count_1 < item_count; count_1++)
					(*output_function)(output_control, "%c%*.*s%s",
						(isprint(((const unsigned char *) data_ptr)[count_1])) ?
						((const unsigned char *) data_ptr)[count_1] : '?',
						radix_length - 1, radix_length - 1, " ",
						(count_1 < (item_count - 1)) ? " " : "\n");
				if (left_padding)
					(*output_function)(output_control, "%-*.*s",
						left_padding, left_padding, " ");
			}
			for (count_1 = 0; count_1 < item_count; count_1++) {
				val2str(((unsigned long)
					((const unsigned char *) data_ptr)[count_1]),
					0, in_radix, "0", number_buffer);
				(*output_function)(output_control, "%*.*s%s",
					radix_length, radix_length, number_buffer +
					strlen(number_buffer) - radix_length,
					(count_1 < (item_count - 1)) ? " " : "\n");
			}
			data_length -= item_count;
			data_ptr     = ((const void *)
				(((const char *) data_ptr) + item_count));
		}
	}
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code = 0;
	unsigned int count_1;
	unsigned int count_2;
	char         buffer[100];

	fprintf(stderr, "Test routine for function 'GEN_EmitBufferData()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------------------\n\n");

	if (argc < 2) {
		fprintf(stderr, "USAGE: %s <text-string> [<text-string> . . .]\n\n",
			argv[0]);
      return_code = 1;
	}
	else {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			for (count_2 = 2; count_2 <= 36; count_2++) {
				sprintf(buffer, "TEST %03u [%2u]:", count_1, count_2);
				GEN_EmitBufferData(NULL, NULL, buffer, 14, 65, 1, count_2,
					strlen(argv[count_1]), argv[count_1]);
			}
			STR_EMIT_CharLine('-', 78, NULL, NULL);
		}
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

