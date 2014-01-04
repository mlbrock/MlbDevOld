/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the GENFUNCS library version number.

	Revision History	:	1996-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include <strfuncs.h>

#include "genfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(STR_VERSION *GENFUNCS_GetVersion,
	(STR_VERSION *version_number));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GENFUNCS_GetVersionNumber

   SYNOPSIS    :	void GENFUNCS_GetVersionNumber(major, minor, release, build);

						unsigned int *major;

						unsigned int *minor;

						unsigned int *release;

						unsigned int *build;

   DESCRIPTION :	Returns the components of the GENFUNCS library version number.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``major`` points to the ''unsigned int'' which is to
						receive the major component number of the version number.

						(.) ``minor`` points to the ''unsigned int'' which is to
						receive the minor component number of the version number.

						(.) ``release`` points to the ''unsigned int'' which is to
						receive the release component number of the version number.

						(.) ``build`` points to the ''unsigned int'' which is to
						receive the build component number of the version number.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GENFUNCS_GetVersionString
						GENFUNCS_GetVersion

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	GENFUNCS_GetVersionNumber
						Miscellaneous Functions:GENFUNCS_GetVersionNumber
						GENFUNCS:Functions:GENFUNCS_GetVersionNumber
						GENFUNCS:Miscellaneous Functions:GENFUNCS_GetVersionNumber
						General Functions:See GENFUNCS

   PUBLISH XREF:	GENFUNCS_GetVersionNumber

   PUBLISH NAME:	GENFUNCS_GetVersionNumber

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GENFUNCS_GetVersionNumber(unsigned int *major, unsigned int *minor,
	unsigned int *release, unsigned int *build)
#else
void GENFUNCS_GetVersionNumber(major, minor, release, build)
unsigned int *major;
unsigned int *minor;
unsigned int *release;
unsigned int *build;
#endif /* #ifndef NARGS */
{
	STR_VERSION tmp_version;

	GENFUNCS_GetVersion(&tmp_version);

	*major   = ((unsigned int) tmp_version.major);
	*minor   = ((unsigned int) tmp_version.minor);
	*release = ((unsigned int) tmp_version.release);
	*build   = ((unsigned int) tmp_version.build);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GENFUNCS_GetVersionString

   SYNOPSIS    :	return_ptr = GENFUNCS_GetVersionString(version_string);

						char *return_ptr;

						char *version_string;

   DESCRIPTION :	Constructs a human-readable string equivalent of the
						GENFUNCS library version number.

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
						equivalent of the GENFUNCS library version number.

						(-) The memory allocated for ``version_string`` should be
						at least ''STR_VERSION_NUMBER_LENGTH'' characters in
						length.

   RETURNS     :	Returns a pointer to the formatted string
						``version_string``.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GENFUNCS_GetVersion
						GENFUNCS_GetVersionNumber

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	GENFUNCS_GetVersionString
						Miscellaneous Functions:GENFUNCS_GetVersionString
						GENFUNCS:Functions:GENFUNCS_GetVersionString
						GENFUNCS:Miscellaneous Functions:GENFUNCS_GetVersionString
						General Functions:See GENFUNCS

   PUBLISH XREF:	GENFUNCS_GetVersionString

   PUBLISH NAME:	GENFUNCS_GetVersionString

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GENFUNCS_GetVersionString(char *version_string)
#else
char *GENFUNCS_GetVersionString(version_string)
char *version_string;
#endif /* #ifndef NARGS */
{
	STR_VERSION version_number;
	
	return(vertostr(GENFUNCS_GetVersion(&version_number), version_string));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GENFUNCS_GetVersion

   SYNOPSIS    :	return_ptr = GENFUNCS_GetVersion(version_number);

						STR_VERSION *return_ptr;

						STR_VERSION *version_number;

   DESCRIPTION :	Initializes a ''STR_VERSION'' structure with the GENFUNCS
						library version number.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``version_number`` is a pointer to a ''STR_VERSION''
						into which this function is to place the GENFUNCS library
						version number.

   RETURNS     :	Returns a pointer to the ``version_number`` parameter.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GENFUNCS_GetVersionString
						GENFUNCS_GetVersionNumber

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	GENFUNCS_GetVersion
						Miscellaneous Functions:GENFUNCS_GetVersion
						GENFUNCS:Functions:GENFUNCS_GetVersion
						GENFUNCS:Miscellaneous Functions:GENFUNCS_GetVersion
						General Functions:See GENFUNCS

   PUBLISH XREF:	GENFUNCS_GetVersion

   PUBLISH NAME:	GENFUNCS_GetVersion

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
static STR_VERSION *GENFUNCS_GetVersion(STR_VERSION *version_number)
#else
static STR_VERSION *GENFUNCS_GetVersion(version_number)
STR_VERSION *version_number;
#endif /* #ifndef NARGS */
{
	return(STR_SetVersionNumber(GENFUNCS_VERSION_MAJOR, GENFUNCS_VERSION_MINOR,
		GENFUNCS_VERSION_RELEASE, GENFUNCS_VERSION_BUILD, version_number));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int         return_code = GENFUNCS_SUCCESS;
	STR_VERSION version_number;
	char        version_string[STR_VERSION_NUMBER_LENGTH];

	fprintf(stderr, "%s\n%s\n",
		"Test routine for functions 'GENFUNCS_GetVersion()'",
		"                           'GENFUNCS_GetVersionString()'");
	fprintf(stderr,
		"---- ------- --- --------- -----------------------------\n\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("GENFUNCS System Version Number: %s\n",
		GENFUNCS_GetVersionString(version_string));
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	printf("Version Number 1: %03u %03u %03u %03u\n",
		((unsigned int) GENFUNCS_VERSION_MAJOR),
		((unsigned int) GENFUNCS_VERSION_MINOR),
		((unsigned int) GENFUNCS_VERSION_RELEASE),
		((unsigned int) GENFUNCS_VERSION_BUILD));
	GENFUNCS_GetVersion(&version_number);
	printf("Version Number 2: %03u %03u %03u %03u\n",
		((unsigned int) version_number.major),
		((unsigned int) version_number.minor),
		((unsigned int) version_number.release),
		((unsigned int) version_number.build));
	printf("Version String  : %s\n", GENFUNCS_GetVersionString(version_string));
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

