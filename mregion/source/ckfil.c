/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a pointer to an 'MRG_FIL' structure for
								validity.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
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

#include <strfuncs.h>

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MRG_CheckFil

	SYNOPSIS		:	return_code = MRG_CheckFil(fil_ptr, error_text);

						int            return_code;

						const MRG_FIL *fil_ptr;

						char          *error_text;


	DESCRIPTION	:	Checks a pointer to a ''MRG_FIL'' structure for validity.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``fil_ptr`` points to the ''MRG_FIL'' structure to be
						checked for validity by this function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''MRG_MAX_ERROR_TEXT'' characters in length.

						(-) The ``error_text`` parameter may be ''NULL'', in which
						case this function will not de-reference it.

	RETURNS		:	Returns from this function are as follow:

						(.) ''MRG_SUCCESS'' if the function completes without
						error. ''MRG_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero MREGION return codes
						indicative of error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_CheckCtl
						MRG_CheckReg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

	OUTPUT INDEX:	MRG_CheckFil
						Check Structure Functions:MRG_CheckFil

	PUBLISH XREF:	MRG_CheckFil

	PUBLISH NAME:	MRG_CheckFil

	ENTRY CLASS	:	Check Structure Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MRG_CheckFil(const MRG_FIL *fil_ptr, char *error_text)
#else
int MRG_CheckFil(fil_ptr, error_text)
const MRG_FIL *fil_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char number_buffer[STR_VAL2STR_MAX_LEN + 1];

	if (((return_code =
		((MRG_IS_FIL_PTR(fil_ptr)) ? MRG_SUCCESS : MRG_FAILURE)) !=
		MRG_SUCCESS) && (error_text != NULL))
		strcat(strcat(strcpy(error_text, "Invalid 'MRG_FIL' pointer (0x"),
			lower(val2str(((unsigned long) fil_ptr), 0, 16, "", number_buffer))),
			").");

	return(return_code);
}
/*	***********************************************************************	*/

