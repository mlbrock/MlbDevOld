/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMAP Memory-mapped Interface Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the MMAP library version number.

	Revision History	:	1996-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "mmap.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MMAP_GetVersion

   SYNOPSIS    :	return_ptr = MMAP_GetVersion(version_number);

						STR_VERSION *return_ptr;

						STR_VERSION *version_number;

   DESCRIPTION :	Initializes a ''STR_VERSION'' structure with the MMAP
						library version number.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``version_number`` is a pointer to a ''STR_VERSION''
						into which this function is to place the MMAP library
						version number.

   RETURNS     :	Returns a pointer to the ``version_number`` parameter.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MMAP_GetVersionString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	MMAP_GetVersion
						Memory-mapped Interface Functions:See MMAP Library Functions
						MMAP Library Functions:MMAP_GetVersion

   PUBLISH XREF:	MMAP_GetVersion

   PUBLISH NAME:	MMAP_GetVersion

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
STR_VERSION *MMAP_GetVersion(version_number)
STR_VERSION *version_number;
{
	STR_VERSION_NUMBER_SET(MMAP_VERSION_MAJOR, MMAP_VERSION_MINOR,
		MMAP_VERSION_RELEASE, MMAP_VERSION_BUILD, version_number);

	return(version_number);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MMAP_GetVersionString

   SYNOPSIS    :	return_ptr = MMAP_GetVersionString(version_string);

						char *return_ptr;

						char *version_string;

   DESCRIPTION :	Constructs a human-readable string equivalent of the
						MMAP library version number.

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
						equivalent of the MMAP library version number.

						(-) The memory allocated for ``version_string`` should be
						at least ''STR_VERSION_NUMBER_LENGTH'' characters in
						length.

   RETURNS     :	Returns a pointer to the formatted string
						``version_string``.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MMAP_GetVersion

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	MMAP_GetVersionString
						Memory-mapped Interface Functions:See MMAP Library Functions
						MMAP Library Functions:MMAP_GetVersionString

   PUBLISH XREF:	MMAP_GetVersionString

   PUBLISH NAME:	MMAP_GetVersionString

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
char *MMAP_GetVersionString(version_string)
char *version_string;
{
	STR_VERSION version_number;
	
	return(vertostr(MMAP_GetVersion(&version_number), version_string));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

#ifndef NARGS
int main(void);
#else
int main();
#endif /* #ifndef NARGS */

int main()
{
	int         return_code = MMAP_SUCCESS;
	STR_VERSION version_number;
	char        version_string[STR_VERSION_NUMBER_LENGTH];

	fprintf(stderr, "%s\n%s\n",
		"Test routine for functions 'MMAP_GetVersion()'",
		"                           'MMAP_GetVersionString()'");
	fprintf(stderr,
		"---- ------- --- --------- -------------------------\n\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("MMAP System Version Number: %s\n",
		MMAP_GetVersionString(version_string));
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	printf("Version Number 1: %03u %03u %03u %03u\n",
		((unsigned int) MMAP_VERSION_MAJOR),
		((unsigned int) MMAP_VERSION_MINOR),
		((unsigned int) MMAP_VERSION_RELEASE),
		((unsigned int) MMAP_VERSION_BUILD));
	MMAP_GetVersion(&version_number);
	printf("Version Number 2: %03u %03u %03u %03u\n",
		((unsigned int) version_number.major),
		((unsigned int) version_number.minor),
		((unsigned int) version_number.release),
		((unsigned int) version_number.build));
	printf("Version String  : %s\n", MMAP_GetVersionString(version_string));
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

