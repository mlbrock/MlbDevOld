/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MRG Memory-mapped Region Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the MREGION library version number.

	Revision History	:	1996-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <strfuncs.h>

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MRG_GetVersionString

   SYNOPSIS    :	return_ptr = MRG_GetVersionString(version_string);

						char *return_ptr;

						char *version_string;

   DESCRIPTION :	Constructs a human-readable string equivalent of the
						MREGION library version number.

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
						equivalent of the MREGION library version number.

						(-) The memory allocated for ``version_string`` should be
						at least ''STR_VERSION_NUMBER_LENGTH'' characters in
						length.

   RETURNS     :	Returns a pointer to the formatted string
						``version_string``.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	MRG_GetVersionString
						Memory-mapped Region Functions:See MRG Library Functions
						MREGION Library Functions:MRG_GetVersionString

   PUBLISH XREF:	MRG_GetVersionString

   PUBLISH NAME:	MRG_GetVersionString

	ENTRY CLASS	:	Memory-mapped Region Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *MRG_GetVersionString(char *version_string)
#else
char *MRG_GetVersionString(version_string)
char *version_string;
#endif /* #ifndef NARGS */
{
	STR_VERSION version_number;

	return(vertostr(STR_SetVersionNumber(MRG_VERSION_MAJOR, MRG_VERSION_MINOR,
		MRG_VERSION_RELEASE, MRG_VERSION_BUILD, &version_number),
		version_string));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int         return_code = MRG_SUCCESS;
	STR_VERSION version_number;
	char        version_string[STR_VERSION_NUMBER_LENGTH];

	fprintf(stderr,
		"Test routine for functions 'MRG_GetVersionString()'\n");
	fprintf(stderr,
		"---- ------- --- --------- ------------------------\n\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("MRG System Version Number: %s\n",
		MRG_GetVersionString(version_string));
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	printf("Version Number 1: %03u %03u %03u %03u\n",
		((unsigned int) MRG_VERSION_MAJOR),
		((unsigned int) MRG_VERSION_MINOR),
		((unsigned int) MRG_VERSION_RELEASE),
		((unsigned int) MRG_VERSION_BUILD));
	STR_VERSION_NUMBER_SET(MRG_VERSION_MAJOR, MRG_VERSION_MINOR,
		MRG_VERSION_RELEASE, MRG_VERSION_BUILD, &version_number);
	printf("Version Number 2: %03u %03u %03u %03u\n",
		((unsigned int) version_number.major),
		((unsigned int) version_number.minor),
		((unsigned int) version_number.release),
		((unsigned int) version_number.build));
	printf("Version String  : %s\n", MRG_GetVersionString(version_string));
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

