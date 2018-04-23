/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Cache Repository (DCR) Library Module										*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Assists in the construction of operating system
								error messages.

	Revision History	:	1994-06-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
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

#include "dcr.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DCR_GEN_AppendSpecErrorString

   SYNOPSIS    :  error_ptr = DCR_GEN_AppendSpecErrorString(errno_code,
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
						''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string ``error_text``.

   NOTES       :  This function will append text to ``error_text`` only as
						far as to make the total length of the string equal to
						the value of the manifest constant
						''DCR_MAX_ERROR_TEXT - 1''.

						This function calls ``GEN_GetErrorString`` to perform the
						actual work of constructing the error string.

   CAVEATS     :  

   SEE ALSO    :  DCR_GEN_AppendLastErrorString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	DCR_GEN_AppendSpecErrorString
						General Functions:DCR_GEN_AppendSpecErrorString
						General Functions:Error Description Functions:DCR_GEN_AppendSpecErrorString

	PUBLISH XREF:	DCR_GEN_AppendSpecErrorString

	PUBLISH NAME:	DCR_GEN_AppendSpecErrorString

	ENTRY CLASS :	Error Description Functions

EOH */
/* *********************************************************************** */
char *DCR_GEN_AppendSpecErrorString(errno_code, error_text)
int   errno_code;
char *error_text;
{
	unsigned int error_length;

	if ((error_length = strlen(error_text)) < DCR_MAX_ERROR_TEXT)
		GEN_GetErrorString(errno_code, 0, DCR_MAX_ERROR_TEXT - error_length,
			error_text + error_length);

	return(error_text);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DCR_GEN_AppendLastErrorString

   SYNOPSIS    :  DCR_GEN_AppendLastErrorString(error_text);

						char *error_ptr;

						char *error_text;

   DESCRIPTION :  Appends text descriptive of the last occurrence of a system
						error to the string to which the ``error_string``
						parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``error_text`` points to a string into which this
						function will append text descriptive of the last system
						error. The string allocated for this purpose should be at
						least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string ``error_text``.

   NOTES       :  This function will append text to ``error_text`` only as
						far as to make the total length of the string equal to
						the value of the manifest constant
						''DCR_MAX_ERROR_TEXT - 1''.

   CAVEATS     :  

   SEE ALSO    :  DCR_GEN_AppendSpecErrorString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	DCR_GEN_AppendLastErrorString
						General Functions:Error Description Functions:DCR_GEN_AppendLastErrorString

	PUBLISH XREF:	DCR_GEN_AppendLastErrorString

	PUBLISH NAME:	DCR_GEN_AppendLastErrorString

	ENTRY CLASS :	Error Description Functions

EOH */
/* *********************************************************************** */
char *DCR_GEN_AppendLastErrorString(error_text)
char *error_text;
{
	return(DCR_GEN_AppendSpecErrorString(errno, error_text));
}
/* *********************************************************************** */

#ifdef TEST_MAIN
 
#include <stdio.h>
#include <stdlib.h>

#include <strfuncs.h>

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

#ifndef NARGS
int main(int, char **);
#else
int main();
#endif /* #ifndef NARGS */
 
char *UsageString = "[<errno-number> . . .]";

int main(argc, argv)
int    argc;
char **argv;
{
	int  count_1 = 0;
	char error_text[4096];

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DCR_GEN_AppendSpecErrorString()'\n");
	fprintf(stderr, "---- ------- --- ---------------------------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp("-HELP", argv[count_1]))
			GEN_DoSimpleUsage(DCR_SUCCESS, argv[0], "Help request noted.",
				UsageString);
	}

	if (argc < 2) {
		for (count_1 = 0; count_1 < 100; count_1++) {
			strcpy(error_text, "START OF THE DCR ERROR STRING: ");
			printf("%3d ---> %s\n", atoi(argv[count_1]),
				DCR_GEN_AppendSpecErrorString(count_1, error_text));
		}
	}
	else {
		for (count_1 = 1; count_1 < argc; count_1++) {
			strcpy(error_text, "START OF THE DCR ERROR STRING: ");
			printf("%3d ---> %s\n", atoi(argv[count_1]),
				DCR_GEN_AppendSpecErrorString(atoi(argv[count_1]), error_text));
		}
	}

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(0);
}

#endif /* #ifdef TEST_MAIN */

