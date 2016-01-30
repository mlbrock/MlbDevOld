/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a try-lock of an SIIDR structure.

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
int SIIDR_TryLockReaderIDR(SIIDR *siidr_ptr, char *error_text)
{
	int  return_code;
	char mtif_error_text[MTIF_MAX_ERROR_TEXT];

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS)) {
		if ((return_code = MTIF_RWL_TryLockReader(&siidr_ptr->rwl_data,
			mtif_error_text)) != MTIF_SUCCESS) {
			if (error_text != NULL)
				nstrcat(strcat(nstrcat(strcpy(error_text,
					"Attempt to try-lock for "), siidr_ptr->idr_name, 500),
					" internal data repository for reading failed: "),
					mtif_error_text, SIIDR_MAX_ERROR_TEXT - 600);
			return_code = SIIDR_MAP_ERROR_MTIF(return_code);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TryLockWriterIDR(SIIDR *siidr_ptr, char *error_text)
{
	int  return_code;
	char mtif_error_text[MTIF_MAX_ERROR_TEXT];

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS)) {
		if ((return_code = MTIF_RWL_TryLockWriter(&siidr_ptr->rwl_data,
			mtif_error_text)) != MTIF_SUCCESS) {
			if (error_text != NULL)
				nstrcat(strcat(nstrcat(strcpy(error_text,
					"Attempt to try-lock for "), siidr_ptr->idr_name, 500),
					" internal data repository for writing failed: "),
					mtif_error_text, SIIDR_MAX_ERROR_TEXT - 600);
			return_code = SIIDR_MAP_ERROR_MTIF(return_code);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

