/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the DBC MS SQL library version number.

	Revision History	:	1996-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include "dbcmssql.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_GetVersion

   SYNOPSIS    :	return_ptr = DBC_MSSQL_GetVersion(version_number);

						STR_VERSION *return_ptr;

						STR_VERSION *version_number;

   DESCRIPTION :	Initializes a ''STR_VERSION'' structure with the DBC DB-LIB
						library version number.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``version_number`` is a pointer to a ''STR_VERSION''
						into which this function is to place the DBC DB-LIB library
						version number.

   RETURNS     :	Returns a pointer to the ``version_number`` parameter.

   NOTES       :	This function returns the version number of the DBC DB-LIB
						facility, which is ''NOT'' the same version number as that
						returned by the function ``DBC_GetVersion``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_GetVersionString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_GetVersion
						DBC DB-LIB Functions:DBC_MSSQL_GetVersion
						DBC Functions:DBC_MSSQL_GetVersion

   PUBLISH XREF:	DBC_MSSQL_GetVersion

   PUBLISH NAME:	DBC_MSSQL_GetVersion

	ENTRY CLASS	:	DBC Functions:Version Number Functions

EOH */
/*	***********************************************************************	*/
STR_VERSION *DBC_MSSQL_GetVersion(version_number)
STR_VERSION *version_number;
{
	STR_VERSION_NUMBER_SET(DBC_MSSQL_VERSION_MAJOR, DBC_MSSQL_VERSION_MINOR,
		DBC_MSSQL_VERSION_RELEASE, DBC_MSSQL_VERSION_BUILD, version_number);

	return(version_number);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_GetVersionString

   SYNOPSIS    :	return_ptr = DBC_MSSQL_GetVersionString(version_string);

						char *return_ptr;

						char *version_string;

   DESCRIPTION :	Constructs a human-readable string equivalent of the
						DBC DB-LIB library version number.

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
						equivalent of the DBC DB-LIB library version number.

						(-) The memory allocated for ``version_string`` should be
						at least ''STR_VERSION_NUMBER_LENGTH'' characters in
						length.

   RETURNS     :	Returns a pointer to the formatted string
						``version_string``.

   NOTES       :	This function returns the version string of the DBC DB-LIB
						facility, which is ''NOT'' the same version string as that
						returned by the function ``DBC_GetVersionString``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_GetVersion

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_GetVersionString
						DBC DB-LIB Functions:DBC_MSSQL_GetVersionString
						DBC Functions:DBC_MSSQL_GetVersionString

   PUBLISH XREF:	DBC_MSSQL_GetVersionString

   PUBLISH NAME:	DBC_MSSQL_GetVersionString

	ENTRY CLASS	:	DBC Functions:Version Number Functions

EOH */
/*	***********************************************************************	*/
char *DBC_MSSQL_GetVersionString(version_string)
char *version_string;
{
	STR_VERSION version_number;
	
	return(vertostr(DBC_MSSQL_GetVersion(&version_number), version_string));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int         return_code = DBC_SUCCESS;
	STR_VERSION version_number;
	char        version_string[STR_VERSION_NUMBER_LENGTH];

	fprintf(stderr, "%s\n%s\n",
		"Test routine for functions 'DBC_MSSQL_GetVersion()'",
		"                           'DBC_MSSQL_GetVersionString()'");
	fprintf(stderr,
		"---- ------- --- --------- ------------------------------\n\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("DBC DB-LIB System Version Number: %s\n",
		DBC_MSSQL_GetVersionString(version_string));
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	printf("Version Number 1: %03u %03u %03u %03u\n",
		((unsigned int) DBC_MSSQL_VERSION_MAJOR),
		((unsigned int) DBC_MSSQL_VERSION_MINOR),
		((unsigned int) DBC_MSSQL_VERSION_RELEASE),
		((unsigned int) DBC_MSSQL_VERSION_BUILD));
	DBC_MSSQL_GetVersion(&version_number);
	printf("Version Number 2: %03u %03u %03u %03u\n",
		((unsigned int) version_number.major),
		((unsigned int) version_number.minor),
		((unsigned int) version_number.release),
		((unsigned int) version_number.build));
	printf("Version String  : %s\n",
		DBC_MSSQL_GetVersionString(version_string));
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

