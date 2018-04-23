/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the DTA library version number.

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

#include "dtai.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DTA_GetVersion

   SYNOPSIS    :	return_ptr = DTA_GetVersion(version_number);

						STR_VERSION *return_ptr;

						STR_VERSION *version_number;

   DESCRIPTION :	Initializes a ''STR_VERSION'' structure with the DTA
						library version number.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``version_number`` is a pointer to a ''STR_VERSION''
						into which this function is to place the DTA library
						version number.

   RETURNS     :	Returns a pointer to the ``version_number`` parameter.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	DTA_GetVersionString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DTA_GetVersion
						Miscellaneous Functions:DTA_GetVersion
						DTA:Functions:DTA_GetVersion
						DTA:Miscellaneous Functions:DTA_GetVersion
						General Functions:See DTA

   PUBLISH XREF:	DTA_GetVersion

   PUBLISH NAME:	DTA_GetVersion

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
STR_VERSION *DTA_GetVersion(STR_VERSION *version_number)
#else
STR_VERSION *DTA_GetVersion(version_number)
STR_VERSION *version_number;
#endif /* #ifndef NARGS */
{
	return(STR_SetVersionNumber(DTA_VERSION_MAJOR, DTA_VERSION_MINOR,
		DTA_VERSION_RELEASE, DTA_VERSION_BUILD, version_number));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DTA_GetVersionString

   SYNOPSIS    :	return_ptr = DTA_GetVersionString(version_string);

						char *return_ptr;

						char *version_string;

   DESCRIPTION :	Constructs a human-readable string equivalent of the
						DTA library version number.

						A formatted version number string has the generalized
						format:

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

						(.) ``version_string`` is the string into which this
						function is to place the formatted version number string
						equivalent of the DTA library version number.

						(-) The memory allocated for ``version_string`` should be
						at least ''STR_VERSION_NUMBER_LENGTH'' characters in
						length.

   RETURNS     :	Returns a pointer to the formatted string
						``version_string``.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	DTA_GetVersion

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DTA_GetVersionString
						Miscellaneous Functions:DTA_GetVersionString
						DTA:Functions:DTA_GetVersionString
						DTA:Miscellaneous Functions:DTA_GetVersionString
						General Functions:See DTA

   PUBLISH XREF:	DTA_GetVersionString

   PUBLISH NAME:	DTA_GetVersionString

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DTA_GetVersionString(char *version_string)
#else
char *DTA_GetVersionString(version_string)
char *version_string;
#endif /* #ifndef NARGS */
{
	STR_VERSION version_number;

	return(vertostr(DTA_GetVersion(&version_number), version_string));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int         return_code = DTA_SUCCESS;
	STR_VERSION version_number;
	char        version_string[STR_VERSION_NUMBER_LENGTH];

	fprintf(stderr, "%s\n%s\n",
		"Test routine for functions 'DTA_GetVersion()'",
		"                           'DTA_GetVersionString()'");
	fprintf(stderr,
		"---- ------- --- --------- ------------------------\n\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("DTA System Version Number: %s\n",
		DTA_GetVersionString(version_string));
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	printf("Version Number 1: %03u %03u %03u %03u\n",
		((unsigned int) DTA_VERSION_MAJOR),
		((unsigned int) DTA_VERSION_MINOR),
		((unsigned int) DTA_VERSION_RELEASE),
		((unsigned int) DTA_VERSION_BUILD));
	DTA_GetVersion(&version_number);
	printf("Version Number 2: %03u %03u %03u %03u\n",
		((unsigned int) version_number.major),
		((unsigned int) version_number.minor),
		((unsigned int) version_number.release),
		((unsigned int) version_number.build));
	printf("Version String  : %s\n", DTA_GetVersionString(version_string));
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

