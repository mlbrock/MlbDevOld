/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks the control members of an 'SIIDR' structure for
								validity.

	Revision History	:	1996-04-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <string.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	SIIDR_CheckControl

	SYNOPSIS		:	return_code = SIIDR_CheckControl(siidr_ptr, error_text);

						int     return_code;

						SIIDR *siidr_ptr;

						char  *error_text;


	DESCRIPTION	:	Checks the control members of an ''SIIDR'' structure for
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
						SIIDR_CheckControlRaw
						SIIDR_CheckData

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

	OUTPUT INDEX:	SIIDR_CheckControl
						Check Structure Functions:SIIDR_CheckControl

	PUBLISH XREF:	SIIDR_CheckControl

	PUBLISH NAME:	SIIDR_CheckControl

	ENTRY CLASS	:	Check Structure Functions

EOH */
/*	***********************************************************************	*/
int SIIDR_CheckControl(SIIDR *siidr_ptr, char  *error_text)
{
	int return_code;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockReaderIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			if ((return_code = SIIDR_CheckControlRaw(siidr_ptr, error_text)) ==
				SIIDR_SUCCESS)
				return_code = SIIDR_UnLockReaderIDR(siidr_ptr, error_text);
			else
				return_code = SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	SIIDR_CheckControlRaw

	SYNOPSIS		:	return_code = SIIDR_CheckControlRaw(siidr_ptr, error_text);

						int     return_code;

						SIIDR *siidr_ptr;

						char  *error_text;


	DESCRIPTION	:	Checks the control members of an ''SIIDR'' structure for
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
						SIIDR_CheckControl
						SIIDR_CheckDataRaw

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

	OUTPUT INDEX:	SIIDR_CheckControlRaw
						Check Structure Functions:SIIDR_CheckControlRaw

	PUBLISH XREF:	SIIDR_CheckControlRaw

	PUBLISH NAME:	SIIDR_CheckControlRaw

	ENTRY CLASS	:	Check Structure Functions

EOH */
/*	***********************************************************************	*/
int SIIDR_CheckControlRaw(SIIDR *siidr_ptr, char  *error_text)
{
	int          return_code;
	unsigned int count_1;
	char         mtif_error_text[MTIF_MAX_ERROR_TEXT];
	char         tmp_error_text[SIIDR_MAX_ERROR_TEXT];

	if ((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) {
		if ((return_code = MTIF_RWL_Check(&siidr_ptr->rwl_data,
			mtif_error_text)) != MTIF_SUCCESS) {
			if (error_text != NULL)
				nstrcpy(error_text, mtif_error_text, SIIDR_MAX_ERROR_TEXT - 1);
			return_code = SIIDR_MAP_ERROR_MTIF(return_code);
		}
		else if (!siidr_ptr->record_size) {
			if (error_text != NULL)
				strcpy(error_text, "SIIDR structure size is '0'.");
			return_code = SIIDR_FAILURE;
		}
		else if (!siidr_ptr->allocation_size) {
			if (error_text != NULL)
				strcpy(error_text, "SIIDR allocation size is '0'.");
			return_code = SIIDR_FAILURE;
		}
		else if ((return_code =
			SIIDR_TouchCode(STR_CAST_FUNC_PTR(siidr_ptr->compare_func),
			tmp_error_text)) != SIIDR_SUCCESS) {
			if (error_text != NULL)
				strcat(strcpy(error_text,
					"Comparison function pointer is invalid: "), tmp_error_text);
		}
		else if (siidr_ptr->idr_name == NULL) {
			if (error_text != NULL)
				strcpy(error_text, "SIIDR name is 'NULL'.");
			return_code = SIIDR_FAILURE;
		}
		else if (siidr_ptr->record_count > siidr_ptr->allocated_count) {
			if (error_text != NULL)
				sprintf(error_text, "%s (%u) %s (%u).",
					"The SIIDR record count", siidr_ptr->record_count,
					"is greater than the allocation count",
					siidr_ptr->allocated_count);
			return_code = SIIDR_FAILURE;
		}
		else if (siidr_ptr->allocated_count &&
			(siidr_ptr->record_list == NULL)) {
			if (error_text != NULL)
				sprintf(error_text, "%s (%u), but the record list is 'NULL'.",
					"The SIIDR allocation count is non-zero",
					siidr_ptr->allocated_count);
			return_code = SIIDR_FAILURE;
		}
		else if ((!siidr_ptr->allocated_count) &&
			(siidr_ptr->record_list != NULL)) {
			if (error_text != NULL)
				strcat(val2str_ptr_cat(siidr_ptr->record_list,
					strcat(strcpy(error_text,
					"The SIIDR allocation count is zero ('0'), "),
					"but the record list is not 'NULL' (")), ").");
			return_code = SIIDR_FAILURE;

		}
		else if ((siidr_ptr->allocated_count) &&
			((return_code = SIIDR_TouchWrite(siidr_ptr->record_list,
			siidr_ptr->allocated_count * sizeof(void *),
			"Allocated SIIDR record pointer list", error_text)) ==
			SIIDR_SUCCESS)) {
			for (count_1 = 0; count_1 < siidr_ptr->allocated_count; count_1++) {
				if (count_1 < siidr_ptr->record_count) {
					if (siidr_ptr->record_list[count_1] == NULL) {
						if (error_text != NULL)
							sprintf(error_text, "%s %u is 'NULL'.",
								"SIIDR in-use record pointer at index", count_1);
						return_code = SIIDR_FAILURE;
						break;
					}
					else if ((return_code = SIIDR_TouchRecordWrite(siidr_ptr,
						siidr_ptr->record_list[count_1], tmp_error_text)) !=
						SIIDR_SUCCESS) {
						if (error_text != NULL)
							sprintf(error_text, "%s %u is invalid: %s",
								"SIIDR in-use record pointer at index", count_1,
								tmp_error_text);
						return_code = SIIDR_FAILURE;
						break;
					}
				}
				else if (siidr_ptr->record_list[count_1] != NULL) {
					if (error_text != NULL) {
						sprintf(error_text, "%s %u is not 'NULL' ",
							"SIIDR reserved/not in-use record pointer at index",
							count_1);
						strcat(val2str_ptr0_cat(siidr_ptr->record_list[count_1],
							strcat(error_text, "(")), ").");
					}
					return_code = SIIDR_FAILURE;
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

