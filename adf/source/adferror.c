/* *********************************************************************** */
/* *********************************************************************** */
/*	Automated Documentation Facility (ADF) Program Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Assists in the construction of operating system
								error messages.

	Revision History	:	1994-06-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include <errno.h>
#include <string.h>

#include "adf.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  ADF_GetSpecifedErrorString

   SYNOPSIS    :  error_ptr = ADF_GetSpecifedErrorString(errno_code,
							error_text);

						char *error_ptr;

						int   errno_code;

						char *error_text;

   DESCRIPTION :  Appends text descriptive of the specified system error
						number to the string to which the ``error_string``
						parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``errno_code`` is the system error number (from the
						external variable defined in ''errno.h'') which is to be
						appended.

						(.) ``error_text`` points to a string into which this
						function will append text descriptive of the system error
						specified by the ``errno_code`` parameter. The string
						allocated for this purpose should be at least
						''ADF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string.

   NOTES       :  This function will append text to ``error_text`` only as
						far as to make the total length of the string equal to
						the value of the manifest constant
						''ADF_MAX_ERROR_TEXT - 1''.

   CAVEATS     :  

   SEE ALSO    :  ADF_GetLastErrorString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	ADF_GetSpecifedErrorString
						ADF General Functions:ADF_GetSpecifedErrorString

	PUBLISH XREF:	ADF_GetSpecifedErrorString

	PUBLISH NAME:	ADF_GetSpecifedErrorString

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ADF_GetSpecifedErrorString(int errno_code, char *error_text)
#else
char *ADF_GetSpecifedErrorString(errno_code, error_text)
int   errno_code;
char *error_text;
#endif /* #ifndef NARGS */
{
	unsigned int error_length;

	if ((error_length = strlen(error_text)) < ADF_MAX_ERROR_TEXT)
		GEN_GetErrorString(errno_code, 0, ADF_MAX_ERROR_TEXT - error_length,
			error_text + error_length);

	return(error_text);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  ADF_GetLastErrorString

   SYNOPSIS    :  ADF_GetLastErrorString(error_text);

						char *error_ptr;

						char *error_text;

   DESCRIPTION :  Appends text descriptive of the last occurrence of a system
						error to the string to which the ``error_string``
						parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``error_text`` points to a string into which this
						function will append text descriptive of the last system
						error. The string allocated for this purpose should be at
						least ''ADF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string.

   NOTES       :  This function will append text to ``error_text`` only as
						far as to make the total length of the string equal to
						the value of the manifest constant
						''ADF_MAX_ERROR_TEXT - 1''.

   CAVEATS     :  

   SEE ALSO    :  ADF_GetSpecifedErrorString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	ADF_GetLastErrorString
						ADF General Functions:ADF_GetLastErrorString

	PUBLISH XREF:	ADF_GetLastErrorString

	PUBLISH NAME:	ADF_GetLastErrorString

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ADF_GetLastErrorString(char *error_text)
#else
char *ADF_GetLastErrorString(error_text)
char *error_text;
#endif /* #ifndef NARGS */
{
	return(ADF_GetSpecifedErrorString(errno, error_text));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (int argc, char **argv));

char *UsageString = "<errno-number> [<errno-number> . . .]";

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int  count_1 = 0;
	char error_text[4096];

	fprintf(stderr,
		"Test routine for 'ADF_GetSpecifedErrorString()'\n");
	fprintf(stderr,
		"---- ------- --- ------------------------------\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp("-HELP", argv[count_1]))
			ADF_DoSimpleUsage(ADF_SUCCESS, argv[0], "Help request noted.",
				UsageString);
	}

	if (argc < 2)
		ADF_DoSimpleUsage(ADF_FAILURE, argv[0],
			"Invalid command invocation", UsageString);

	for (count_1 = 1; count_1 < argc; count_1++) {
		strcpy(error_text, "START OF THE ADF ERROR STRING: ");
		printf("%d ---> %s\n", atoi(argv[count_1]),
			ADF_GetSpecifedErrorString(atoi(argv[count_1]), error_text));
	}

	return(0);
}

#endif /* #ifdef TEST_MAIN */

