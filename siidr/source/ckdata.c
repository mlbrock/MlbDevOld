/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks the data which constitutes an 'SIIDR' structure
								for validity.

	Revision History	:	1996-04-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
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
#include <stdio.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	SIIDR_CheckData

	SYNOPSIS		:	return_code = SIIDR_CheckData(siidr_ptr, error_text);

						int     return_code;

						SIIDR *siidr_ptr;

						char  *error_text;


	DESCRIPTION	:	Checks the data which constitutes an ''SIIDR'' structure for
						validity.

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

	SEE ALSO		:	SIIDR_CheckIDR
						SIIDR_CheckDataRaw
						SIIDR_CheckControl

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2014 Michael L. Brock

	OUTPUT INDEX:	SIIDR_CheckData
						Check Structure Functions:SIIDR_CheckData

	PUBLISH XREF:	SIIDR_CheckData

	PUBLISH NAME:	SIIDR_CheckData

	ENTRY CLASS	:	Check Structure Functions

EOH */
/*	***********************************************************************	*/
int SIIDR_CheckData(SIIDR *siidr_ptr, char  *error_text)
{
	int return_code;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockReaderIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			if ((return_code = SIIDR_CheckDataRaw(siidr_ptr, error_text)) ==
				SIIDR_SUCCESS)
				return_code = SIIDR_UnLockReaderIDR(siidr_ptr, error_text);
			else
				SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	SIIDR_CheckDataRaw

	SYNOPSIS		:	return_code = SIIDR_CheckDataRaw(siidr_ptr, error_text);

						int     return_code;

						SIIDR *siidr_ptr;

						char  *error_text;


	DESCRIPTION	:	Checks the data which constitutes an ''SIIDR'' structure for
						validity.

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

	SEE ALSO		:	SIIDR_CheckIDR
						SIIDR_CheckData
						SIIDR_CheckControlRaw

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2014 Michael L. Brock

	OUTPUT INDEX:	SIIDR_CheckDataRaw
						Check Structure Functions:SIIDR_CheckDataRaw

	PUBLISH XREF:	SIIDR_CheckDataRaw

	PUBLISH NAME:	SIIDR_CheckDataRaw

	ENTRY CLASS	:	Check Structure Functions

EOH */
/*	***********************************************************************	*/
int SIIDR_CheckDataRaw(SIIDR *siidr_ptr, char  *error_text)
{
	int          return_code;
	unsigned int count_1;
	int          cmp;

	if (((return_code = SIIDR_CheckControlRaw(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) && siidr_ptr->record_count) {
		for (count_1 = 0; count_1 < (siidr_ptr->record_count - 1); count_1++) {
			if ((cmp = (*siidr_ptr->compare_func)(siidr_ptr,
				siidr_ptr->record_list[count_1],
				siidr_ptr->record_list[count_1 + 1],
				siidr_ptr->record_size)) > -1) {
				if (error_text != NULL)
					sprintf(error_text, "%s: %s %u is %s the record at index %u",
						"Error encountered in SIIDR unique index",
						"record at index", count_1, (!cmp) ? "equal to" :
						"greater than", count_1 + 1);
				return_code = SIIDR_FAILURE;
				break;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

