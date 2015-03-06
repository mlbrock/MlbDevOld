/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a pointer to an 'DBC_CONTEXT' structure for
								validity.

	Revision History	:	1993-07-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <limits.h>
#include <string.h>

#include "dbcfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	DBC_CheckContext

	SYNOPSIS		:	return_code = DBC_CheckContext(dbc_context_ptr, error_text);

						int                return_code;

						const DBC_CONTEXT *dbc_context_ptr;

						char              *error_text;


	DESCRIPTION	:	Checks a pointer to a ''DBC_CONTEXT'' structure for
						validity.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` points to the ''DBC_CONTEXT''
						structure to be checked for validity by this function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''DBC_MAX_ERROR_TEXT'' characters in length.

						(-) The ``error_text`` parameter may be ''NULL'', in which
						case this function will not de-reference it.

	RETURNS		:	Returns from this function are as follow:

						(.) ''DBC_SUCCESS'' if the function completes without
						error. ''DBC_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero DBC return codes
						indicative of error.

	SEE ALSO		:	DBC_CheckFunction

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2015 Michael L. Brock

	OUTPUT INDEX:	DBC_CheckContext
						Check Structure Functions:DBC_CheckContext

	PUBLISH XREF:	DBC_CheckContext

	PUBLISH NAME:	DBC_CheckContext

	ENTRY CLASS	:	Check Structure Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_CheckContext(const DBC_CONTEXT *dbc_context_ptr, char *error_text)
#else
int DBC_CheckContext(dbc_context_ptr, error_text)
const DBC_CONTEXT *dbc_context_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char buffer[STR_VAL2STR_MAX_LEN + 1];

	if (((return_code =
		((DBC_IS_PTR(dbc_context_ptr)) ? DBC_SUCCESS : DBC_FAILURE)) !=
		DBC_SUCCESS) && (error_text != NULL))
		strcat(strcat(strcpy(error_text,
			"Invalid 'DBC_CONTEXT' structure pointer (0x"),
			lower(val2str(((unsigned long) dbc_context_ptr), 0, 16, "",
			buffer))), ").");

	return(return_code);
}
/*	***********************************************************************	*/

