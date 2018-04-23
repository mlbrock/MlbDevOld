/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Generalized Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns a DBC facility library version number.

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

#include "dbcfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_GetFacilityVersion

   SYNOPSIS    :	return_ptr = DBC_GetFacilityVersion(dbc_context_ptr,
							version_number);

						STR_VERSION       *return_ptr;

						const DBC_CONTEXT *dbc_context_ptr;

						STR_VERSION       *version_number;

   DESCRIPTION :	Initializes a ''STR_VERSION'' structure with a DBC facility
						library version number.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``version_number`` is a pointer to a ''STR_VERSION''
						into which this function is to place the DBC facility
						version number.

   RETURNS     :	Returns a pointer to the ``version_number`` parameter.

   NOTES       :	This function returns the version number of the DBC
						facility, which is ''NOT'' the same version number as that
						returned by the function ``DBC_GetVersion``.

   SEE ALSO    :	DBC_GetFacilityVersionString

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_GetFacilityVersion
						Database Functions:Facility Functions:DBC_GetFacilityVersion
						DBC Functions:DBC_GetFacilityVersion

   PUBLISH XREF:	DBC_GetFacilityVersion

   PUBLISH NAME:	DBC_GetFacilityVersion

	ENTRY CLASS	:	Database Functions:Facility Functions
						DBC Functions:Version Number Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
STR_VERSION *DBC_GetFacilityVersion(const DBC_CONTEXT *dbc_context_ptr,
	STR_VERSION *version_number)
#else
STR_VERSION *DBC_GetFacilityVersion(dbc_context_ptr, version_number)
const DBC_CONTEXT *dbc_context_ptr;
STR_VERSION       *version_number;
#endif /* #ifndef NARGS */
{
	if (DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.get_version), NULL) ==
		DBC_SUCCESS)
		(*dbc_context_ptr->dbc_funcs.get_version)(version_number);
	else
		memset(version_number, '\0', sizeof(*version_number));

	return(version_number);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_GetFacilityVersionString

   SYNOPSIS    :	return_ptr = DBC_GetFacilityVersionString(dbc_context_ptr,
							version_string);

						char              *return_ptr;

						const DBC_CONTEXT *dbc_context_ptr;

						char              *version_string;

   DESCRIPTION :	Constructs a human-readable string equivalent of a DBC
						facility library version number.

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
						equivalent of a DBC facility library version number.

						(-) The memory allocated for ``version_string`` should be
						at least ''STR_VERSION_NUMBER_LENGTH'' characters in
						length.

   RETURNS     :	Returns a pointer to the formatted string
						``version_string``.

   NOTES       :	This function returns the version string of a DBC facility
						facility, which is ''NOT'' the same version string as that
						returned by the function ``DBC_GetFacilityVersionString``.

   SEE ALSO    :	DBC_GetFacilityVersion

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_GetFacilityVersionString
						Database Functions:Facility Functions:DBC_GetFacilityVersionString
						DBC Functions:DBC_GetFacilityVersionString

   PUBLISH XREF:	DBC_GetFacilityVersionString

   PUBLISH NAME:	DBC_GetFacilityVersionString

	ENTRY CLASS	:	Database Functions:Facility Functions
						DBC Functions:Version Number Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_GetFacilityVersionString(const DBC_CONTEXT *dbc_context_ptr,
	char *version_string)
#else
char *DBC_GetFacilityVersionString(dbc_context_ptr, version_string)
const DBC_CONTEXT *dbc_context_ptr;
char              *version_string;
#endif /* #ifndef NARGS */
{
	if (DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.get_version_string),
		NULL) == DBC_SUCCESS)
		(*dbc_context_ptr->dbc_funcs.get_version_string)(version_string);
	else
		*version_string = '\0';

	return(version_string);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code       = DBC_SUCCESS;
	const char  *connection_string = "SPS_PROD,,,mlds,mlds";
	DBC_CONTEXT  dbc_context;
	STR_VERSION  version_number;
	char         version_string[STR_VERSION_NUMBER_LENGTH];
	char         error_text[DBC_MAX_ERROR_TEXT];

	fprintf(stderr, "%s\n%s\n",
		"Test routine for functions 'DBC_GetFacilityVersion()'",
		"                           'DBC_GetFacilityVersionString()'");
	fprintf(stderr,
		"---- ------- --- --------- --------------------------------\n\n");

	if (argc > 1)
		connection_string = argv[1];

	if ((return_code = DBC_Open(&dbc_context, NULL, "Test App",
		connection_string, NULL, DBC_FLAG_ALL, NULL, error_text)) ==
		DBC_SUCCESS) {
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		printf("DBC System Version Number: %s\n",
			DBC_GetVersionString(version_string));
		STR_EMIT_CharLine('-', 78, NULL, NULL);
		DBC_GetFacilityVersion(&dbc_context, &version_number);
		printf("Version Number: %03u %03u %03u %03u\n",
			((unsigned int) version_number.major),
			((unsigned int) version_number.minor),
			((unsigned int) version_number.release),
			((unsigned int) version_number.build));
		printf("Version String: %s\n",
			DBC_GetFacilityVersionString(&dbc_context, version_string));
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		DBC_Close(&dbc_context);
	}
	else
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

