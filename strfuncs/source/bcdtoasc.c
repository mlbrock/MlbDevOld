/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a binary-coded decimal (BCD) string to an
								ASCII numeric string

	Revision History	:	1993-07-08 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include "strfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	bcdtoasc

	SYNOPSIS		:	return_ptr = bcdtoasc(in_bcd_ptr, out_ascii_ptr);

						char       *return_ptr;

						const char *in_bcd_ptr;

						char       *out_ascii_ptr;

	DESCRIPTION	:	Converts a ''COMP-3'' BCD string to an ASCII string of
						digits.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_bcd_ptr`` points to BCD string to be converted.

						(.) ``out_ascii_ptr`` points to the area into which this
						function is place the converted ASCII characters.

	RETURNS		:	A pointer to ``out_ascii_ptr``.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	bcdtoasc_basic
						bcdtoasc_basic_mem
						asctobcd
						ascii_to_COMP_3

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2015 Michael L. Brock

	OUTPUT INDEX:	bcdtoasc
						ASCII/BCD Conversion Functions:bcdtoasc
						STRFUNCS:ASCII/BCD Conversion Functions:bcdtoasc
						String Functions:See STRFUNCS

	PUBLISH XREF:	bcdtoasc

	PUBLISH NAME:	bcdtoasc

	ENTRY CLASS	:	ASCII/BCD Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *bcdtoasc(const char *in_bcd_ptr, char *out_ascii_ptr)
#else
char *bcdtoasc(in_bcd_ptr, out_ascii_ptr)
const char *in_bcd_ptr;
char       *out_ascii_ptr;
#endif /* #ifndef NARGS */
{
	int            nybble;
	unsigned char *tmp_ptr = ((unsigned char *) out_ascii_ptr);

	*tmp_ptr++ = ' ';

	while (in_bcd_ptr) {
		*tmp_ptr = '\0';
		if ((((unsigned char) *in_bcd_ptr) > 0X9F) ||
			((nybble = (((unsigned char) *in_bcd_ptr) >> 4)) > 9)) {
			tmp_ptr = ((unsigned char *) out_ascii_ptr);
			break;
		}
		*tmp_ptr++ = ((unsigned char) (nybble + '0'));
		if ((nybble = (*in_bcd_ptr++ & 0x0F)) > 9) {
			*out_ascii_ptr =
				((char) (((nybble == 0X0B) || (nybble == 0X0D)) ? '-' : ' '));
			break;
		}
		*tmp_ptr++ = ((unsigned char) (nybble + '0'));
	}

	*tmp_ptr = '\0';

	return(out_ascii_ptr);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	bcdtoasc_basic

	SYNOPSIS		:	return_ptr = bcdtoasc_basic(in_bcd_length, in_bcd_ptr,
							start_at_nybble_flag, out_ascii_length, out_ascii_ptr,
							bcd_sign_value);

						char         *return_ptr;

						unsigned int  in_bcd_length;

						const char   *in_bcd_ptr;

						char         *out_ascii_ptr;

	DESCRIPTION	:	Converts a ''COMP-3'' BCD string to an ASCII string of
						digits.

						This function will convert BCD nybbles until one of the
						following conditions are met:

						(.) The maximum BCD length (as indicated by the
						``in_bcd_length`` parameter) has been reached.

						(.) A BCD sign nybble (that is, a nybble greater in value
						than ''0X09'') is encountered.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_bcd_length`` is the length of the BCD string
						``in_bcd_ptr``.

						(.) ``in_bcd_ptr`` points to BCD string to be converted.

						(.) ``out_ascii_ptr`` points to the area into which this
						function is place the converted ASCII characters.

	RETURNS		:	A pointer to ``out_ascii_ptr``.

	NOTES			:	This function will append an ASCII ''NUL'' character to
						the end of the converted string ``out_ascii_ptr``. If you
						do not desire this behavoir, use the sister function
						``bcdtoasc_basic_mem``.

	CAVEATS		:	

	SEE ALSO		:	bcdtoasc
						bcdtoasc_basic_mem
						asctobcd
						ascii_to_COMP_3

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2015 Michael L. Brock

	OUTPUT INDEX:	bcdtoasc_basic
						ASCII/BCD Conversion Functions:bcdtoasc_basic
						STRFUNCS:ASCII/BCD Conversion Functions:bcdtoasc_basic
						String Functions:See STRFUNCS

	PUBLISH XREF:	bcdtoasc_basic

	PUBLISH NAME:	bcdtoasc_basic

	ENTRY CLASS	:	ASCII/BCD Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *bcdtoasc_basic(unsigned int in_bcd_length, const char *in_bcd_ptr,
	char *out_ascii_ptr)
#else
char *bcdtoasc_basic(in_bcd_length, in_bcd_ptr, out_ascii_ptr)
unsigned int  in_bcd_length;
const char   *in_bcd_ptr;
char         *out_ascii_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int tmp_length;
	int          bcd_sign_value;

	bcdtoasc_basic_mem(in_bcd_length, in_bcd_ptr, 0, &tmp_length,
		out_ascii_ptr + 1, &bcd_sign_value);

	out_ascii_ptr[0]              = ((char)
		(((bcd_sign_value == 0X0B) || (bcd_sign_value == 0X0D)) ? '-' : ' '));
	out_ascii_ptr[tmp_length + 1] = '\0';

	return(out_ascii_ptr);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	bcdtoasc_basic_mem

	SYNOPSIS		:	return_ptr = bcdtoasc_basic_mem(in_bcd_length, in_bcd_ptr,
							start_at_nybble_flag, out_ascii_length, out_ascii_ptr,
							bcd_sign_value);

						char         *return_ptr;

						unsigned int  in_bcd_length;

						const char   *in_bcd_ptr;

						int           start_at_nybble_flag;

						unsigned int *out_ascii_length;

						char         *out_ascii_ptr;

						int          *bcd_sign_value;

	DESCRIPTION	:	Converts a ''COMP-3'' BCD string to an ASCII string of
						digits.

						This function will convert BCD nybbles until one of the
						following conditions are met:

						(.) The maximum BCD length (as indicated by the
						``in_bcd_length`` parameter) has been reached.

						(.) A BCD sign nybble (that is, a nybble greater in value
						than ''0X09'') is encountered.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_bcd_length`` is the length of the BCD string
						``in_bcd_ptr``.

						(.) ``in_bcd_ptr`` points to BCD string to be converted.

						(.) ``start_at_nybble_flag`` if this parameter is non-zero,
						indicates that the first BCD nybble is to be retrieved from
						the second nybble of the area to which the ``in_bcd_ptr``
						parameter points. The default behavior of this function is
						to retrieve BCD nybbles beginning at the first nybble in
						``in_bcd_ptr``.

						(.) ``out_ascii_length`` points to an ''unsigned int''
						into which this function will place the number of digits
						converted from BCD and stored in the area to which the
						``out_ascii_ptr`` parameter points.

						(.) ``out_ascii_ptr`` points to the area into which this
						function is place the converted ASCII characters.

						(.) ``bcd_sign_value`` points to an ''int'' into which
						this function will place the value of the BCD sign nybble
						(in found).

						(-) ``bcd_sign_value`` may be a ''NULL'' pointer, in which
						case it will not be de-referenced.

	RETURNS		:	A pointer to ``out_ascii_ptr``.

	NOTES			:	The resulting string ``out_ascii_ptr`` is not ASCII
						''NUL'' terminated by this function. If an ASCII ''NUL''
						terminated string is desired, you should use the sister
						function ``bcdtoasc_basic`` or add said termination within
						the invoking function.

	CAVEATS		:	

	SEE ALSO		:	bcdtoasc
						bcdtoasc_basic
						asctobcd
						ascii_to_COMP_3

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2015 Michael L. Brock

	OUTPUT INDEX:	bcdtoasc_basic_mem
						ASCII/BCD Conversion Functions:bcdtoasc_basic_mem
						STRFUNCS:ASCII/BCD Conversion Functions:bcdtoasc_basic_mem
						String Functions:See STRFUNCS

	PUBLISH XREF:	bcdtoasc_basic_mem

	PUBLISH NAME:	bcdtoasc_basic_mem

	ENTRY CLASS	:	ASCII/BCD Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *bcdtoasc_basic_mem(unsigned int in_bcd_length, const char *in_bcd_ptr,
	int start_at_nybble_flag, unsigned int *out_ascii_length,
	char *out_ascii_ptr, int *bcd_sign_value)
#else
char *bcdtoasc_basic_mem(in_bcd_length, in_bcd_ptr, start_at_nybble_flag,
	out_ascii_length, out_ascii_ptr, bcd_sign_value)
unsigned int  in_bcd_length;
const char   *in_bcd_ptr;
int           start_at_nybble_flag;
unsigned int *out_ascii_length;
char         *out_ascii_ptr;
int          *bcd_sign_value;
#endif /* #ifndef NARGS */
{
	int            nybble;
	int            tmp_bcd_sign;
	unsigned char *tmp_ptr = ((unsigned char *) out_ascii_ptr);

	*out_ascii_length = 0;
	bcd_sign_value    = (!bcd_sign_value) ? &tmp_bcd_sign : bcd_sign_value;
	*bcd_sign_value   = 0;

	while (in_bcd_length) {
		*tmp_ptr = '\0';
		if (start_at_nybble_flag)
			start_at_nybble_flag = 0;
		else {
			if ((((unsigned char) *in_bcd_ptr) > 0X9F) ||
				((nybble = (((unsigned char) *in_bcd_ptr) >> 4)) > 9)) {
				tmp_ptr = ((unsigned char *) out_ascii_ptr);
				break;
			}
			*tmp_ptr++ = ((unsigned char) (nybble + '0'));
		}
		if ((nybble = (*in_bcd_ptr++ & 0x0F)) > 9) {
			*bcd_sign_value = nybble;
			break;
		}
		*tmp_ptr++ = ((unsigned char) (nybble + '0'));
		in_bcd_length--;
	}

	*out_ascii_length = ((unsigned int) (((char *) tmp_ptr) - out_ascii_ptr));

	return(out_ascii_ptr);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

#define PROMPT_STRING	"ENTER BCD>"

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(int TEST_DoTest,
	(void));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char buffer[512];
	char out_ascii[1024];

	fprintf(stderr, "Test routine for function 'bcdtoasc()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------\n\n");

	if ((return_code = TEST_DoTest()) != STRFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	while (argc) {
		if ((!stricmp("-HELP", argv[argc - 1])) ||
			(!stricmp("-H", argv[argc - 1]))) {
			fprintf(stderr, "USAGE:\n   cat <test-file> | %s\n\n", argv[0]);
			goto EXIT_FUNCTION;
		}
		argc--;
	}

	while ((!feof(stdin)) && (!ferror(stdin))) {
		printf("%s", PROMPT_STRING);
		if (fgets(buffer, sizeof(buffer) - 1, stdin) == NULL)
			break;
		while (*buffer && ((buffer[strlen(buffer) - 1] == '\r') ||
			(buffer[strlen(buffer) - 1] == '\n')))
			buffer[strlen(buffer) - 1] = '\0';
		if ((!stricmp(buffer, "QUIT")) || (!stricmp(buffer, "EXIT")))
			break;
		printf("ASCII RESULT: [%s]\n", bcdtoasc(buffer, out_ascii));
	}

EXIT_FUNCTION:

	return(return_code);
}

#include <stdlib.h>

static int TEST_DoTest()
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned int  count_1;
	unsigned int  in_bcd_length;
	char          tmp_bcd[512];
	char          tmp_ascii_1[512];
	char          tmp_ascii_2[512];

	fprintf(stderr, "Performing regression test . . .");

	for (count_1 = 0; count_1 < 10000; count_1++) {
		sprintf(tmp_ascii_1, "%u", rand());
		if (ascii_to_COMP_3((rand() % 2) ? -1 : 0, tmp_ascii_1,
			((unsigned char *) tmp_bcd), &in_bcd_length) == NULL) {
			fprintf(stderr, "\n\nERROR: %s '%s' to a BCD value failed.",
				"Attempt to convert an ASCII string value", tmp_ascii_1);
			return_code = STRFUNCS_FAILURE;
			break;
		}
		bcdtoasc(tmp_bcd, tmp_ascii_1);
		bcdtoasc_basic(in_bcd_length, tmp_bcd, tmp_ascii_2);
		if (strcmp(tmp_ascii_1, tmp_ascii_2)) {
			fprintf(stderr, "\n\nERROR: %s ('%s') %s %s ('%s').",
				"Invocation of the function 'bcdtoasc()' resulted in a string",
				tmp_ascii_1, "different from that resulting from the invocation",
				"of 'bcdtoasc_basic()'", tmp_ascii_2);
			return_code = STRFUNCS_FAILURE;
			break;
		}
	}

	fprintf(stderr, "\n\n");

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

