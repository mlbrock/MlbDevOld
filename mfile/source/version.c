/* *********************************************************************** */
/* *********************************************************************** */
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the MFILE library version number.

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

#include "mfilei.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(STR_VERSION *MFILE_GetVersion,
	(STR_VERSION *version_number));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_GetVersionNumber

   SYNOPSIS    :	void MFILE_GetVersionNumber(major, minor, release, build);

						unsigned int *major;

						unsigned int *minor;

						unsigned int *release;

						unsigned int *build;

   DESCRIPTION :	Returns the components of the MFILE library version number.

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

   SEE ALSO    :	MFILE_GetVersionString
						MFILE_GetVersion

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	MFILE_GetVersionNumber
						Memory-mapped File Functions:Miscellaneous Functions:MFILE_GetVersionNumber
						MFILE Functions:MFILE_GetVersionNumber

   PUBLISH XREF:	MFILE_GetVersionNumber

   PUBLISH NAME:	MFILE_GetVersionNumber

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_GetVersionNumber(unsigned int *major, unsigned int *minor,
	unsigned int *release, unsigned int *build)
#else
void MFILE_GetVersionNumber(major, minor, release, build)
unsigned int *major;
unsigned int *minor;
unsigned int *release;
unsigned int *build;
#endif /* #ifndef NARGS */
{
	STR_VERSION tmp_version;

	MFILE_GetVersion(&tmp_version);

	*major   = ((unsigned int) tmp_version.major);
	*minor   = ((unsigned int) tmp_version.minor);
	*release = ((unsigned int) tmp_version.release);
	*build   = ((unsigned int) tmp_version.build);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_GetVersionString

   SYNOPSIS    :	return_ptr = MFILE_GetVersionString(version_string);

						char *return_ptr;

						char *version_string;

   DESCRIPTION :	Constructs a human-readable string equivalent of the
						MFILE library version number.

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
						equivalent of the MFILE library version number.

						(-) The memory allocated for ``version_string`` should be
						at least ''STR_VERSION_NUMBER_LENGTH'' characters in
						length.

   RETURNS     :	Returns a pointer to the formatted string
						``version_string``.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MFILE_GetVersion

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	MFILE_GetVersionString
						Memory-mapped File Functions:Miscellaneous Functions:MFILE_GetVersionString
						MFILE Functions:MFILE_GetVersionString

   PUBLISH XREF:	MFILE_GetVersionString

   PUBLISH NAME:	MFILE_GetVersionString

	ENTRY CLASS	:	Memory-mapped File Functions:Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *MFILE_GetVersionString(char *version_string)
#else
char *MFILE_GetVersionString(version_string)
char *version_string;
#endif /* #ifndef NARGS */
{
	STR_VERSION version_number;
	
	return(vertostr(MFILE_GetVersion(&version_number), version_string));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_GetVersion

   SYNOPSIS    :	return_ptr = MFILE_GetVersion(version_number);

						STR_VERSION *return_ptr;

						STR_VERSION *version_number;

   DESCRIPTION :	Initializes a ''STR_VERSION'' structure with the MFILE
						library version number.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``version_number`` is a pointer to a ''STR_VERSION''
						into which this function is to place the MFILE library
						version number.

   RETURNS     :	Returns a pointer to the ``version_number`` parameter.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MFILE_GetVersionString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	MFILE_GetVersion
						Memory-mapped File Functions:Miscellaneous Functions:MFILE_GetVersion
						MFILE Functions:MFILE_GetVersion

   PUBLISH XREF:	MFILE_GetVersion

   PUBLISH NAME:	MFILE_GetVersion

	ENTRY CLASS	:	Memory-mapped File Functions:Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
static STR_VERSION *MFILE_GetVersion(STR_VERSION *version_number)
#else
static STR_VERSION *MFILE_GetVersion(version_number)
STR_VERSION *version_number;
#endif /* #ifndef NARGS */
{
	return(STR_SetVersionNumber(MFILE_VERSION_MAJOR, MFILE_VERSION_MINOR,
		MFILE_VERSION_RELEASE, MFILE_VERSION_BUILD, version_number));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	int         return_code = MFILE_SUCCESS;
	STR_VERSION version_number;
	char        version_string[STR_VERSION_NUMBER_LENGTH];

	fprintf(stderr, "%s\n%s\n",
		"Test routine for functions 'MFILE_GetVersion()'",
		"                           'MFILE_GetVersionString()'");
	fprintf(stderr,
		"---- ------- --- --------- --------------------------\n\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("MFILE System Version Number: %s\n",
		MFILE_GetVersionString(version_string));
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	printf("Version Number 1: %03u %03u %03u %03u\n",
		((unsigned int) MFILE_VERSION_MAJOR),
		((unsigned int) MFILE_VERSION_MINOR),
		((unsigned int) MFILE_VERSION_RELEASE),
		((unsigned int) MFILE_VERSION_BUILD));
	MFILE_GetVersion(&version_number);
	printf("Version Number 2: %03u %03u %03u %03u\n",
		((unsigned int) version_number.major),
		((unsigned int) version_number.minor),
		((unsigned int) version_number.release),
		((unsigned int) version_number.build));
	printf("Version String  : %s\n", MFILE_GetVersionString(version_string));
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

