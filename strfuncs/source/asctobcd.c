/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts an ASCII numeric string to binary-coded
								decimal (BCD).

	Revision History	:	1993-07-08 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <string.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	asctobcd

	SYNOPSIS		:	return_code = asctobcd(in_ascii_length, in_ascii_string,
							start_at_nybble_flag, nybble_pad_flag, out_bcd_string,
							out_nybble_count);

						int            return_code;

						unsigned int   in_ascii_length;

						const char    *in_ascii_string;

						int            start_at_nybble_flag;

						int            nybble_pad_flag;

						unsigned char *out_bcd_string;

						unsigned int  *out_nybble_count;

	DESCRIPTION	:	Converts a string of ASCII digits to binary-coded decimal
						(BCD).

						A digit is any character for which the ANSI C standard
						macro ``isdigit()`` returns a non-zero value.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_ascii_length`` is the number of characters in the
						string ``in_ascii_string`` to be converted to BCD.

						(.) ``in_ascii_string`` points to the characters to be
						converted to BCD.

						(.) ``start_at_nybble_flag`` if this parameter is non-zero,
						indicates that the first BCD nybble is to be placed in the
						second nybble of the area to which the ``out_bcd_string``
						parameter points. The default behavior of this function is
						to place BCD nybbles beginning at the first nybble in
						``out_bcd_string``.

						(.) ``nybble_pad_flag`` if this parameter is non-zero,
						indicates that if the length of the ASCII string to be
						converted as indicated by the ``in_ascii_length`` parameter
						is not an integral multiple of two that the first nybble of
						``out_bcd_string`` is to padded by the insertion of a zero
						(''0'') nybble.

						(.) ``out_bcd_string`` points to the area of memory into
						which the BCD values are to be placed.

						(.) ``out_nybble_count`` points to an ``unsigned int``
						into which will be placed the number of characters (as
						half-bytes, or nybbles) which were converted successfully
						to BCD.

						(-) Because this value is not cleared if a non-digit
						character encountered, examination of the ``unsigned int``
						to which this parameter points after the function returns
						an error code will indicate the offending character.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if all characters were digits.

						(.) ''STRFUNCS_FAILURE'' if any character in the string is
						not a digit.

	NOTES			:	The BCD string emitted by this function is not terminated
						by an ASCII 0.

	CAVEATS		:

	SEE ALSO		:	bcdtoasc
						bcdtoasc_basic
						ascii_to_COMP_3
						ascii_n_to_COMP_3

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock
 
	OUTPUT INDEX:	asctobcd
						ASCII/BCD Conversion Functions:asctobcd
						STRFUNCS:ASCII/BCD Conversion Functions:asctobcd
						String Functions:See STRFUNCS

	PUBLISH XREF:	asctobcd

	PUBLISH NAME:	asctobcd

	ENTRY CLASS	:	ASCII/BCD Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int asctobcd(unsigned int in_ascii_length, const char *in_ascii_string,
	int start_at_nybble_flag, int nybble_pad_flag, unsigned char *out_bcd_string,
	unsigned int *out_nybble_count)
#else
int asctobcd(in_ascii_length, in_ascii_string, start_at_nybble_flag,
	nybble_pad_flag, out_bcd_string, out_nybble_count)
unsigned int   in_ascii_length;
const char    *in_ascii_string;
int            start_at_nybble_flag;
int            nybble_pad_flag;
unsigned char *out_bcd_string;
unsigned int  *out_nybble_count;
#endif /* #ifndef NARGS */
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int nybble      = 0;
	unsigned int tmp_nybble_count;

	out_nybble_count  = (!out_nybble_count) ? &tmp_nybble_count :
		out_nybble_count;
	*out_nybble_count = 0;

	if (in_ascii_length) {
		if (start_at_nybble_flag) {
			nybble++;
			*out_bcd_string = 0;
      }
		else if (nybble_pad_flag && (in_ascii_length % 2)) {
			*out_bcd_string = 0;
			nybble++;
			(*out_nybble_count)++;
		}
		while (in_ascii_length) {
			if (!isdigit(*in_ascii_string)) {
				return_code = STRFUNCS_FAILURE;
				break;
			}
			if (!(nybble % 2))
				*out_bcd_string =
					((unsigned char) ((*in_ascii_string++ - '0') << 4));
			else
				*out_bcd_string++ =
					((unsigned char) (*out_bcd_string | (*in_ascii_string++ - '0')));
			nybble++;
			(*out_nybble_count)++;
			in_ascii_length--;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ascii_to_COMP_3

	SYNOPSIS		:	bcd_ptr = ascii_to_COMP_3(sign, in_ascii_ptr, out_bcd_ptr,
							out_bcd_length);

						unsigned char *bcd_ptr;

						int            sign;

						const char    *in_ascii_ptr;

						unsigned char *out_bcd_ptr;

						unsigned int  *out_bcd_length;

	DESCRIPTION	:	Converts an ASCII NUL-terminated string to a ''COMP-3''
						binary-coded decimal (BCD) value.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``sign`` indicates the sign of the value to be
						converted. If ``sign`` is less that ''0'', the resulting
						BCD string will be negative. Otherwise, it will be
						positive.

						(.) ``in_ascii_ptr`` points to the characters to be
						converted to BCD.

						(.) ``out_bcd_ptr`` points to the area of memory into
						which the BCD values are to be placed.

						(.) ``out_bcd_length`` points to an ``unsigned int``
						into which will be placed the number of characters in the
						area to which the parameter ``out_bcd_ptr`` points.

   RETURNS     :  Returns from this function are as follow:

						(.) If the string is converted successfully, a pointer to
						the converted string is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	Because the ''COMP-3'' BCD format always consists of an
						even number of nybbles including the appended sign nybble,
						invocations of this function with strings of lengths which
						are integral multiples of two will result in the first
						nybble of the resulting BCD string being padded with a
						zero (''0'') nybble.

	CAVEATS		:

	SEE ALSO		:	bcdtoasc
						bcdtoasc_basic
						asctobcd
						ascii_n_to_COMP_3

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	ascii_to_COMP_3
						ASCII/BCD Conversion Functions:ascii_to_COMP_3
						STRFUNCS:ASCII/BCD Conversion Functions:ascii_to_COMP_3
						String Functions:See STRFUNCS

	PUBLISH XREF:	ascii_to_COMP_3

	PUBLISH NAME:	ascii_to_COMP_3

	ENTRY CLASS	:	ASCII/BCD Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
unsigned char *ascii_to_COMP_3(int sign, const char *in_ascii_ptr,
	unsigned char *out_bcd_ptr, unsigned int *out_bcd_length)
#else
unsigned char *ascii_to_COMP_3(sign, in_ascii_ptr, out_bcd_ptr,
	out_bcd_length)
int            sign;
const char    *in_ascii_ptr;
unsigned char *out_bcd_ptr;
unsigned int  *out_bcd_length;
#endif /* #ifndef NARGS */
{
	return(ascii_n_to_COMP_3(sign, in_ascii_ptr, strlen(in_ascii_ptr),
		out_bcd_ptr, out_bcd_length));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ascii_n_to_COMP_3

	SYNOPSIS		:	bcd_ptr = ascii_n_to_COMP_3(sign, in_ascii_ptr,
							in_ascii_length, out_bcd_ptr, out_bcd_length);

						unsigned char *bcd_ptr;

						int            sign;

						const char    *in_ascii_ptr;

						unsigned int   in_ascii_length;

						unsigned char *out_bcd_ptr;

						unsigned int  *out_bcd_length;

	DESCRIPTION	:	Converts the length of an ASCII string specified by the
						``in_ascii_length`` parameter to a ''COMP-3'' binary-coded
						decimal (BCD) value.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``sign`` indicates the sign of the value to be
						converted. If ``sign`` is less that ''0'', the resulting
						BCD string will be negative. Otherwise, it will be
						positive.

						(.) ``in_ascii_ptr`` points to the beginning of the string
						of characters to be converted to BCD.

						(.) ``in_ascii_length`` is the length of the string of
						characters in ``in_ascii_ptr`` to be converted to BCD.

						(.) ``out_bcd_ptr`` points to the area of memory into
						which the BCD values are to be placed.

						(.) ``out_bcd_length`` points to an ``unsigned int``
						into which will be placed the number of characters in the
						area to which the parameter ``out_bcd_ptr`` points.

	RETURNS     :  Returns from this function are as follow:

						(.) If the string is converted successfully, a pointer to
						the converted string is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	Because the ''COMP-3'' BCD format always consists of an
						even number of nybbles including the appended sign nybble,
						invocations of this function with ``in_ascii_length``
						parameters which are integral multiples of two will result
						in the first nybble of the resulting BCD string being
						padded with a zero (''0'') nybble.

	CAVEATS		:

	SEE ALSO		:	bcdtoasc
						bcdtoasc_basic
						asctobcd
						ascii_to_COMP_3

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	ascii_n_to_COMP_3
						ASCII/BCD Conversion Functions:ascii_n_to_COMP_3
						STRFUNCS:ASCII/BCD Conversion Functions:ascii_n_to_COMP_3
						String Functions:See STRFUNCS

	PUBLISH XREF:	ascii_n_to_COMP_3

	PUBLISH NAME:	ascii_n_to_COMP_3

	ENTRY CLASS	:	ASCII/BCD Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
unsigned char *ascii_n_to_COMP_3(int sign, const char *in_ascii_ptr,
	unsigned int in_ascii_length, unsigned char *out_bcd_ptr,
	unsigned int *out_bcd_length)
#else
unsigned char *ascii_n_to_COMP_3(sign, in_ascii_ptr, in_ascii_length,
	out_bcd_ptr, out_bcd_length)
int            sign;
const char    *in_ascii_ptr;
unsigned int   in_ascii_length;
unsigned char *out_bcd_ptr;
unsigned int  *out_bcd_length;
#endif /* #ifndef NARGS */
{
	unsigned int out_nybble_count;

	if (asctobcd(in_ascii_length, in_ascii_ptr, (in_ascii_length % 2) ? 0 : 1,
		0, out_bcd_ptr, &out_nybble_count) != STRFUNCS_SUCCESS)
		out_bcd_ptr = NULL;
	else {
		*(out_bcd_ptr + (out_nybble_count / 2)) |=
			((unsigned char) ((sign >= 0) ? 0x0F : 0X0B));
		*out_bcd_length                          = (out_nybble_count / 2) + 1;
	}

	return(out_bcd_ptr);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

#define PROMPT_STRING	"ENTER BCD>"

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned int  count_1;
	size_t        bcd_length;
	char          buffer[512];
	unsigned char out_bcd[1024];
	char          out_ascii[1024];

	fprintf(stderr, "Test routine for function 'asctobcd()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------\n\n");

	fprintf(stderr, "USAGE: cat <test-file> | %s\n\n", argv[0]);

	if (argc == 1) {
		fprintf(stderr, "\n\nNo file specified on command line.\n\n");
		return_code = STRFUNCS_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	while ((!feof(stdin)) && (!ferror(stdin))) {
		printf("%s", PROMPT_STRING);
		if (fgets(buffer, sizeof(buffer) - 1, stdin) == NULL)
			break;
		while (*buffer && ((buffer[strlen(buffer) - 1] == '\r') ||
			(buffer[strlen(buffer) - 1] == '\n')))
			buffer[strlen(buffer) - 1] = '\0';
		trim(buffer);
		if ((!stricmp(buffer, "QUIT")) || (!stricmp(buffer, "EXIT")))
			break;
		if (!(*buffer))
			continue;
		printf("Converting      :[%s]\n", buffer);
		ascii_to_COMP_3((*buffer == '-') ? -1 : 0,
			(*buffer == '-') ? (buffer + 1) : buffer, out_bcd, &bcd_length);
		printf(">>> BCD         :[");
		for (count_1 = 0; count_1 < bcd_length; count_1++)
			printf("%1X.%1X%s",
				((unsigned int) ((out_bcd[count_1] >> 4) & 0X0F)),
				((unsigned int) (out_bcd[count_1] & 0X0F)),
				(count_1 < (bcd_length - 1)) ? ":" : "");
		printf("]\n");
		printf(">>> ASCII RESULT:[%s]\n",
			bcdtoasc(((char *) out_bcd), out_ascii));
	}

EXIT_FUNCTION:

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

