/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a pointer to an 'SIIDR' structure for
								validity.

	Revision History	:	1996-04-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <string.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	SIIDR_CheckIDR

	SYNOPSIS		:	return_code = SIIDR_CheckIDR(siidr_ptr, error_text);

						int     return_code;

						SIIDR *siidr_ptr;

						char  *error_text;


	DESCRIPTION	:	Checks a pointer to an ''SIIDR'' structure for validity.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``siidr_ptr`` points to the ''SIIDR'' structure to be
						checked for validity by this function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''SIIDR_MAX_ERROR_TEXT'' characters in length.

						(-) The ``error_text`` parameter may be ''NULL'', in which
						case this function will not de-reference it.

	RETURNS		:	Returns from this function are as follow:

						(.) ''SIIDR_SUCCESS'' if the function completes without
						error. ''SIIDR_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero SIIDR return codes
						indicative of error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	SIIDR_CheckControl
						SIIDR_CheckData

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

	OUTPUT INDEX:	SIIDR_CheckIDR
						Check Structure Functions:SIIDR_CheckIDR

	PUBLISH XREF:	SIIDR_CheckIDR

	PUBLISH NAME:	SIIDR_CheckIDR

	ENTRY CLASS	:	Check Structure Functions

EOH */
/*	***********************************************************************	*/
int SIIDR_CheckIDR(SIIDR *siidr_ptr, char  *error_text)
{
	int return_code;

	if (siidr_ptr == NULL) {
		if (error_text != NULL)
			strcpy(error_text, "Invalid 'SIIDR' structure pointer ('NULL'");
		return_code = SIIDR_FAILURE;
	}
	else if ((return_code = SIIDR_TouchIDRWrite(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) {
		if ((siidr_ptr == NULL) || (siidr_ptr->signature != SIIDR_SIGNATURE)) {
			if (error_text != NULL)
				strcat(val2str_ptr0_cat(siidr_ptr, strcpy(error_text,
					"Invalid 'SIIDR' structure pointer (")), ").");
			return_code = SIIDR_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

