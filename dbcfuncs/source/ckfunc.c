/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a pointer to an 'DBC_CONTEXT' structure
								validity.

	Revision History	:	1993-07-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
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

	NAME			:	DBC_CheckFunction

	SYNOPSIS		:	return_code = DBC_CheckFunction(dbc_context_ptr, error_text);

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

	SEE ALSO		:	DBC_CheckContext

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

	OUTPUT INDEX:	DBC_CheckFunction
						Check Structure Functions:DBC_CheckFunction

	PUBLISH XREF:	DBC_CheckFunction

	PUBLISH NAME:	DBC_CheckFunction

	ENTRY CLASS	:	Check Structure Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_CheckFunction(const DBC_CONTEXT  *dbc_context_ptr,
	const void **func_ptr, char *error_text)
#else
int DBC_CheckFunction(dbc_context_ptr, func_ptr, error_text)
const DBC_CONTEXT  *dbc_context_ptr;
const void        **func_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code;
	const char *func_name;
	char        buffer[STR_VAL2STR_MAX_LEN + 1];

	if ((return_code = DBC_CheckContext(dbc_context_ptr, error_text)) ==
		DBC_SUCCESS) {
		if ((((const void *) func_ptr) <
			((const void *) &dbc_context_ptr->dbc_funcs)) ||
			(((const void *) func_ptr) >
			((const void *) (((const char *) &dbc_context_ptr->dbc_funcs) +
			(sizeof(dbc_context_ptr->dbc_funcs) - sizeof(const void *)))))) {
			if (error_text != NULL)
				strcat(strcat(strcpy(error_text,
					"Invalid DBC facility function pointer (0x"),
					lower(val2str(((unsigned long) func_ptr), 0, 16, "",
					buffer))), ").");
			return_code = DBC_FAILURE;
		}
		else if ((func_name =
			DBC_GET_NAME_BY_FUNC_PTR(&dbc_context_ptr->dbc_funcs, *func_ptr)) ==
			NULL) {
			if (error_text != NULL)
				strcat(strcat(strcpy(error_text,
					"Invalid DBC facility function pointer (0x"),
					lower(val2str(((unsigned long) func_ptr), 0, 16, "",
					buffer))), ").");
			return_code = DBC_FAILURE;
		}
		else if (*func_ptr == NULL) {
			if (error_text != NULL)
				strcat(strncat(strcpy(error_text,
					"This facility does not support the DBC '"),
					func_name, 500), "' function.");
			return_code = DBC_UNSUPPORTED_FUNC_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

