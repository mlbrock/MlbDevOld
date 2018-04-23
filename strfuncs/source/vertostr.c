/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats a STRFUNCS version number as a human-readable
								string.

	Revision History	:	1996-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include <ctype.h>
#include <stdio.h>

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	vertostr

   SYNOPSIS    :	return_ptr = vertostr(version_number, version_string);

						char              *return_ptr;

						const STR_VERSION *version_number;

						char              *version_string;

   DESCRIPTION :	Constructs a human-readable string equivalent of a
						''STR_VERSION'' structure.

						A formatted STRFUNCS version number string has the
						generalized format:

						<@>``major``.``minor``.``release``(``build``)

						The ``major``, ``minor``, and ``release`` components of the
						version number are three-digit zero-filled numbers.

						The ``build`` component of the version number takes on one
						of the following formats:

						(.) If the ``build`` portion of the ''STR_VERSION'' is
						an upper-case character, then the ``build`` component of
						the formatted string will consist of that single upper-case
						character.

						(.) Otherwise, the ``build`` component of the formatted
						string will consist of the three-digit zero-filled value
						of the ``build`` portion of the ''STR_VERSION''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``version_number`` is a pointer to a ''STR_VERSION''
						which is to be formatted by this function.

						(.) ``version_string`` is the string into which this
						function is to place the formatted version number string.

						(-) The memory allocated for ``version_string`` should be
						at least ''STR_VERSION_NUMBER_LENGTH'' characters in
						length.

   RETURNS     :	Returns a pointer to the formatted string
						``version_string``.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	STR_VERSION

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	vertostr
						Miscellaneous Functions:vertostr
						STRFUNCS:Miscellaneous Functions:vertostr
						String Functions:See STRFUNCS

   PUBLISH XREF:	vertostr

   PUBLISH NAME:	vertostr

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *vertostr(const STR_VERSION *version_number, char *version_string)
#else
char *vertostr(version_number, version_string)
const STR_VERSION *version_number;
char              *version_string;
#endif /* #ifndef NARGS */
{
	char build[4];

	if (isalpha(version_number->build) && isupper(version_number->build))
		chrcpy(build, version_number->build);
	else
		sprintf(build, "%03u", ((unsigned int) version_number->build));

	sprintf(version_string, "%03u.%03u.%03u(%s)",
		((unsigned int) version_number->major),
		((unsigned int) version_number->minor),
		((unsigned int) version_number->release), build);

	return(version_string);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
#ifndef NARGS
void STR_GetVersionNumber(const STR_VERSION *in_version, unsigned int *major,
	unsigned int *minor, unsigned int *release, unsigned int *build)
#else
void STR_GetVersionNumber(in_version, major, minor, release, build)
const STR_VERSION *in_version;
unsigned int      *major;
unsigned int      *minor;
unsigned int      *release;
unsigned int      *build;
#endif /* #ifndef NARGS */
{
	*major   = ((unsigned int) in_version->major);
	*minor   = ((unsigned int) in_version->minor);
	*release = ((unsigned int) in_version->release);
	*build   = ((unsigned int) in_version->build);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
#ifndef NARGS
STR_VERSION *STR_SetVersionNumber(unsigned int major, unsigned int minor,
	unsigned int release, unsigned int build, STR_VERSION *out_version)
#else
STR_VERSION *STR_SetVersionNumber(major, minor, release, build, out_version)
unsigned int  major;
unsigned int  minor;
unsigned int  release;
unsigned int  build;
STR_VERSION  *out_version;
#endif /* #ifndef NARGS */
{
	if ((out_version != NULL) && (major <= UCHAR_MAX) &&
		(minor <= UCHAR_MAX) && (release <= UCHAR_MAX) &&
		(build <= UCHAR_MAX)) {
		out_version->major   = ((unsigned char) major);
		out_version->minor   = ((unsigned char) minor);
		out_version->release = ((unsigned char) release);
		out_version->build   = ((unsigned char) build);
		return(out_version);
	}
	else
		return(NULL);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <limits.h>
#include <stdlib.h>
#include <string.h>

static const char *TEST_UsageString      =
	"[ <major-digits> <minor-digits> <release-digits> <build-digits> ]";

static const char *TEST_ComponentType[4] =
	{ "major", "minor", "release", "build" };

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
	int           tmp_int;
	unsigned char components[4];
	STR_VERSION   version_number;
	char          version_string[STR_VERSION_NUMBER_LENGTH];
	char          error_text[STRFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for function 'vertostr()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!STRFUNCS_stricmp(argv[count_1], "-HELP")) ||
			(!STRFUNCS_stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "\n\nUSAGE:\n   %s %s\n\n",
				argv[0], TEST_UsageString);
			goto EXIT_FUNCTION;
		}
	}

	if ((argc != 1) && (argc != 5)) {
		strcpy(error_text,
			"Invalid number of command-line parameters --- use '-h'.");
		return_code = STRFUNCS_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (argc == 5) {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			if (((tmp_int = atoi(argv[count_1])) < 0) || (tmp_int > UCHAR_MAX)) {
				sprintf(error_text, "Invalid '%s' %s (%d) --- %s '0' %s '%d', %s.",
					TEST_ComponentType[count_1 - 1], "component type value",
					tmp_int, "should be in the range of", "through", UCHAR_MAX,
					"inclusive");
				return_code = STRFUNCS_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if (str_digit(argv[count_1], 0)) {
				sprintf(error_text, "%s '%s' component type argument --- %s.",
					"Invalid characters encountered in the",
					TEST_ComponentType[count_1 - 1], "digits only expected");
				return_code = STRFUNCS_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			components[count_1 - 1] = ((unsigned char) tmp_int);
		}
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		printf("Command Line Version Number:\n");
		STR_EMIT_CharLine('-', 78, NULL, NULL);
		printf("Version Number 1: %03u %03u %03u %03u\n",
			((unsigned int) components[0]),
			((unsigned int) components[1]),
			((unsigned int) components[2]),
			((unsigned int) components[3]));
		STR_VERSION_NUMBER_SET(components[0], components[1], components[2],
			components[3], &version_number);
		printf("Version Number 2: %03u %03u %03u %03u\n",
			((unsigned int) version_number.major),
			((unsigned int) version_number.minor),
			((unsigned int) version_number.release),
			((unsigned int) version_number.build));
		printf("Version String  : %s\n",
			vertostr(&version_number, version_string));
		STR_EMIT_CharLine('=', 78, NULL, NULL);
	}

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("STRFUNCS System Version Number:\n");
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	printf("Version Number 1: %03u %03u %03u %03u\n",
		((unsigned int) STRFUNCS_VERSION_MAJOR),
		((unsigned int) STRFUNCS_VERSION_MINOR),
		((unsigned int) STRFUNCS_VERSION_RELEASE),
		((unsigned int) STRFUNCS_VERSION_BUILD));
	STRFUNCS_GetVersion(&version_number);
	printf("Version Number 2: %03u %03u %03u %03u\n",
		((unsigned int) version_number.major),
		((unsigned int) version_number.minor),
		((unsigned int) version_number.release),
		((unsigned int) version_number.build));
	printf("Version String  : %s\n", STRFUNCS_GetVersionString(version_string));
	STR_EMIT_CharLine('=', 78, NULL, NULL);

EXIT_FUNCTION:

	if (return_code != STRFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

