/* *********************************************************************** */
/* *********************************************************************** */
/*	System Date/Time Interface Facility (SDTIF) Module Source File				*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the SDTIF library version number.

	Revision History	:	1996-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
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

#include "sdtifi.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(STR_VERSION *SDTIF_GetVersion,
	(STR_VERSION *version_number));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	SDTIF_GetVersionNumber

   SYNOPSIS    :	void SDTIF_GetVersionNumber(major, minor, release, build);

						unsigned int *major;

						unsigned int *minor;

						unsigned int *release;

						unsigned int *build;

   DESCRIPTION :	Returns the components of the SDTIF library version number.

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

   SEE ALSO    :	SDTIF_GetVersionString
						SDTIF_GetVersion

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	SDTIF_GetVersionNumber
						Miscellaneous Functions:SDTIF_GetVersionNumber
						SDTIF:Functions:SDTIF_GetVersionNumber
						SDTIF:Miscellaneous Functions:SDTIF_GetVersionNumber
						System Date/Time Interface Facility Functions:See SDTIF

   PUBLISH XREF:	SDTIF_GetVersionNumber

   PUBLISH NAME:	SDTIF_GetVersionNumber

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void SDTIF_GetVersionNumber(unsigned int *major, unsigned int *minor,
	unsigned int *release, unsigned int *build)
#else
void SDTIF_GetVersionNumber(major, minor, release, build)
unsigned int *major;
unsigned int *minor;
unsigned int *release;
unsigned int *build;
#endif /* #ifndef NARGS */
{
	STR_VERSION tmp_version;

	SDTIF_GetVersion(&tmp_version);

	*major   = ((unsigned int) tmp_version.major);
	*minor   = ((unsigned int) tmp_version.minor);
	*release = ((unsigned int) tmp_version.release);
	*build   = ((unsigned int) tmp_version.build);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	SDTIF_GetVersionString

   SYNOPSIS    :	return_ptr = SDTIF_GetVersionString(version_string);

						char *return_ptr;

						char *version_string;

   DESCRIPTION :	Constructs a human-readable string equivalent of the
						SDTIF library version number.

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
						equivalent of the SDTIF library version number.

						(-) The memory allocated for ``version_string`` should be
						at least ''STR_VERSION_NUMBER_LENGTH'' characters in
						length.

   RETURNS     :	Returns a pointer to the formatted string
						``version_string``.

   SEE ALSO    :	SDTIF_GetVersionNumber
						SDTIF_GetVersion

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	SDTIF_GetVersionString
						Miscellaneous Functions:SDTIF_GetVersionString
						SDTIF:Functions:SDTIF_GetVersionString
						SDTIF:Miscellaneous Functions:SDTIF_GetVersionString
						System Date/Time Interface Facility Functions:See SDTIF

   PUBLISH XREF:	SDTIF_GetVersionString

   PUBLISH NAME:	SDTIF_GetVersionString

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *SDTIF_GetVersionString(char *version_string)
#else
char *SDTIF_GetVersionString(version_string)
char *version_string;
#endif /* #ifndef NARGS */
{
	STR_VERSION version_number;

	return(vertostr(SDTIF_GetVersion(&version_number), version_string));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	SDTIF_GetVersion

   SYNOPSIS    :	return_ptr = SDTIF_GetVersion(version_number);

						STR_VERSION *return_ptr;

						STR_VERSION *version_number;

   DESCRIPTION :	Initializes a ''STR_VERSION'' structure with the SDTIF
						library version number.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``version_number`` is a pointer to a ''STR_VERSION''
						into which this function is to place the SDTIF library
						version number.

   RETURNS     :	Returns a pointer to the ``version_number`` parameter.

   SEE ALSO    :	SDTIF_GetVersionString
						SDTIF_GetVersionNumber

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	SDTIF_GetVersion
						Miscellaneous Functions:SDTIF_GetVersion
						SDTIF:Functions:SDTIF_GetVersion
						SDTIF:Miscellaneous Functions:SDTIF_GetVersion
						System Date/Time Interface Facility Functions:See SDTIF

   PUBLISH XREF:	SDTIF_GetVersion

   PUBLISH NAME:	SDTIF_GetVersion

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
static STR_VERSION *SDTIF_GetVersion(STR_VERSION *version_number)
#else
static STR_VERSION *SDTIF_GetVersion(version_number)
STR_VERSION *version_number;
#endif /* #ifndef NARGS */
{
	return(STR_SetVersionNumber(SDTIF_VERSION_MAJOR, SDTIF_VERSION_MINOR,
		SDTIF_VERSION_RELEASE, SDTIF_VERSION_BUILD, version_number));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int          return_code = SDTIF_SUCCESS;
	unsigned int major;
	unsigned int minor;
	unsigned int release;
	unsigned int build;
	STR_VERSION  version_number;
	char         version_string[STR_VERSION_NUMBER_LENGTH];

	fprintf(stderr, "%s\n%s\n",
		"Test routine for functions 'SDTIF_GetVersionNumber()'",
		"                           'SDTIF_GetVersionString()'");
	fprintf(stderr,
		"---- ------- --- --------- --------------------------\n\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("SDTIF System Version Number: %s\n",
		SDTIF_GetVersionString(version_string));
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	printf("Version Number 1: %03u %03u %03u %03u\n",
		((unsigned int) SDTIF_VERSION_MAJOR),
		((unsigned int) SDTIF_VERSION_MINOR),
		((unsigned int) SDTIF_VERSION_RELEASE),
		((unsigned int) SDTIF_VERSION_BUILD));

	SDTIF_GetVersionNumber(&major, &minor, &release, &build);
	printf("Version Number 2: %03u %03u %03u %03u\n",
		major, minor, release, build);

	SDTIF_GetVersion(&version_number);
	printf("Version Number 3: %03u %03u %03u %03u\n",
		((unsigned int) version_number.major),
		((unsigned int) version_number.minor),
		((unsigned int) version_number.release),
		((unsigned int) version_number.build));

	printf("Version String  : %s\n", SDTIF_GetVersionString(version_string));

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

