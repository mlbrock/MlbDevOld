/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the RVUTIL library version number.

	Revision History	:	1996-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/*	***********************************************************************	*/

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(STR_VERSION *RVUTIL_GetVersion,
	(STR_VERSION *version_number));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	RVUTIL_GetVersionNumber

   SYNOPSIS    :	void RVUTIL_GetVersionNumber(major, minor, release, build);

						unsigned int *major;

						unsigned int *minor;

						unsigned int *release;

						unsigned int *build;

   DESCRIPTION :	Returns the components of the RVUTIL library version number.

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

   SEE ALSO    :	RVUTIL_GetVersionString
						RVUTIL_GetVersion

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	RVUTIL_GetVersionNumber
						Miscellaneous Functions:RVUTIL_GetVersionNumber
						RVUTIL:Functions:RVUTIL_GetVersionNumber
						RVUTIL:Miscellaneous Functions:RVUTIL_GetVersionNumber
						Rendezvous Functions:See RVUTIL

   PUBLISH XREF:	RVUTIL_GetVersionNumber

   PUBLISH NAME:	RVUTIL_GetVersionNumber

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
void RVUTIL_GetVersionNumber(unsigned int *major, unsigned int *minor,
	unsigned int *release, unsigned int *build)
{
	STR_VERSION tmp_version;

	RVUTIL_GetVersion(&tmp_version);

	*major   = ((unsigned int) tmp_version.major);
	*minor   = ((unsigned int) tmp_version.minor);
	*release = ((unsigned int) tmp_version.release);
	*build   = ((unsigned int) tmp_version.build);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	RVUTIL_GetVersionString

   SYNOPSIS    :	return_ptr = RVUTIL_GetVersionString(version_string);

						char *return_ptr;

						char *version_string;

   DESCRIPTION :	Constructs a human-readable string equivalent of the
						RVUTIL library version number.

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
						equivalent of the RVUTIL library version number.

						(-) The memory allocated for ``version_string`` should be
						at least ''STR_VERSION_NUMBER_LENGTH'' characters in
						length.

   RETURNS     :	Returns a pointer to the formatted string
						``version_string``.

   SEE ALSO    :	RVUTIL_GetVersion
						RVUTIL_GetVersionNumber

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	RVUTIL_GetVersionString
						Miscellaneous Functions:RVUTIL_GetVersionString
						RVUTIL:Functions:RVUTIL_GetVersionString
						RVUTIL:Miscellaneous Functions:RVUTIL_GetVersionString
						General Functions:See RVUTIL

   PUBLISH XREF:	RVUTIL_GetVersionString

   PUBLISH NAME:	RVUTIL_GetVersionString

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
char *RVUTIL_GetVersionString(char *version_string)
{
	STR_VERSION version_number;

	return(vertostr(RVUTIL_GetVersion(&version_number), version_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	RVUTIL_GetVersion

   SYNOPSIS    :	return_ptr = RVUTIL_GetVersion(version_number);

						STR_VERSION *return_ptr;

						STR_VERSION *version_number;

   DESCRIPTION :	Initializes a ''STR_VERSION'' structure with the RVUTIL
						library version number.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``version_number`` is a pointer to a ''STR_VERSION''
						into which this function is to place the RVUTIL library
						version number.

   RETURNS     :	Returns a pointer to the ``version_number`` parameter.

   SEE ALSO    :	RVUTIL_GetVersionString
						RVUTIL_GetVersionNumber

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	RVUTIL_GetVersion
						Miscellaneous Functions:RVUTIL_GetVersion
						RVUTIL:Functions:RVUTIL_GetVersion
						RVUTIL:Miscellaneous Functions:RVUTIL_GetVersion
						Rendezvous Functions:See RVUTIL

   PUBLISH XREF:	RVUTIL_GetVersion

   PUBLISH NAME:	RVUTIL_GetVersion

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
static STR_VERSION *RVUTIL_GetVersion(STR_VERSION *version_number)
{
	return(STR_SetVersionNumber(RVUTIL_VERSION_MAJOR, RVUTIL_VERSION_MINOR,
		RVUTIL_VERSION_RELEASE, RVUTIL_VERSION_BUILD, version_number));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int         return_code = RVUTIL_SUCCESS;
	STR_VERSION version_number;
	char        version_string[STR_VERSION_NUMBER_LENGTH];

	fprintf(stderr, "%s\n%s\n",
		"Test routine for functions 'RVUTIL_GetVersion()'",
		"                           'RVUTIL_GetVersionString()'");
	fprintf(stderr,
		"---- ------- --- --------- -----------------------------\n\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("RVUTIL System Version Number: %s\n",
		RVUTIL_GetVersionString(version_string));
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	printf("Version Number 1: %03u %03u %03u %03u\n",
		((unsigned int) RVUTIL_VERSION_MAJOR),
		((unsigned int) RVUTIL_VERSION_MINOR),
		((unsigned int) RVUTIL_VERSION_RELEASE),
		((unsigned int) RVUTIL_VERSION_BUILD));
	RVUTIL_GetVersion(&version_number);
	printf("Version Number 2: %03u %03u %03u %03u\n",
		((unsigned int) version_number.major),
		((unsigned int) version_number.minor),
		((unsigned int) version_number.release),
		((unsigned int) version_number.build));
	printf("Version String  : %s\n", RVUTIL_GetVersionString(version_string));
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

