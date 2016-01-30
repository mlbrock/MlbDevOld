/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks an SIIDR relational operator for validity.

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
int SIIDR_CheckRelOp(SIIDR_REL_OP rel_op, char *error_text)
{
	int return_code;

	if ((!SIIDR_REL_OP_MASK) & rel_op) {
		if (error_text != NULL)
			strcat(val2str_uint_cat(SIIDR_REL_OP_MASK, 2, "0",
				strcat(val2str_uint_cat((!SIIDR_REL_OP_MASK) & rel_op, 2, 0,
				strcpy(error_text, "Invalid relational operator flags (0B")),
				") --- valid flags are 0B")), ".");
		return_code = SIIDR_FAILURE;
	}
	else
		return_code = SIIDR_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

