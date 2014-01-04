/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'PCFF_PARAM' structures.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	PCFF_CopyParam

   SYNOPSIS    :	return_code = PCFF_CopyParam(in_ptr, out_ptr,
							error_text);

						int               return_code;

						const PCFF_PARAM *in_ptr;

						PCFF_PARAM       *out_ptr;

						char             *error_text;

   DESCRIPTION :	Copies a single ''PCFF_PARAM'' structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''PCFF_PARAM''
						structure which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''PCFF_PARAM''
						structure into which the copy is to be performed.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''PCFF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''PCFF_SUCCESS'' if the function completes without
						error. ''PCFF_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero PCFF return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :  

   SEE ALSO    :	PCFF_CopyParamList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2014 Michael L. Brock

   OUTPUT INDEX:	PCFF_CopyParam
						Copy Functions:Parse Configuration File Facility Functions:PCFF_CopyParam
						Parse Configuration File Facility Functions:Copy Functions:PCFF_CopyParam

   PUBLISH XREF:	PCFF_CopyParam

   PUBLISH NAME:	PCFF_CopyParam

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
int PCFF_CopyParam(const PCFF_PARAM *in_ptr, PCFF_PARAM *out_ptr,
	char *error_text)
{
	int  return_code = PCFF_MEMORY_FAILURE;
	char tmp_error_text[PCFF_MAX_ERROR_TEXT];

	*out_ptr = *in_ptr;

	out_ptr->param_name   = NULL;
	out_ptr->member_name  = NULL;
	out_ptr->description  = NULL;
	out_ptr->domain       = NULL;
	out_ptr->domain_count = 0;
	out_ptr->domain_list  = NULL;

	if ((in_ptr->param_name != NULL) &&
		((out_ptr->param_name = strdup(in_ptr->param_name)) == NULL))
		STR_AllocMsgItem(strlen(in_ptr->param_name) + 1, tmp_error_text,
			"Unable to allocate memory for a copy of the parameter name");
	else if ((in_ptr->member_name != NULL) &&
		((out_ptr->member_name = strdup(in_ptr->member_name)) == NULL))
		STR_AllocMsgItem(strlen(in_ptr->member_name) + 1, tmp_error_text,
			"Unable to allocate memory for a copy of the member name");
	else if ((in_ptr->description != NULL) &&
		((out_ptr->description = strdup(in_ptr->description)) == NULL))
		STR_AllocMsgItem(strlen(in_ptr->domain) + 1, tmp_error_text,
			"Unable to allocate memory for a copy of the description string");
	else if ((in_ptr->domain != NULL) &&
		((out_ptr->domain = strdup(in_ptr->domain)) == NULL))
		STR_AllocMsgItem(strlen(in_ptr->domain) + 1, tmp_error_text,
			"Unable to allocate memory for a copy of the domain string");
	else if (strl_copy(in_ptr->domain_count, in_ptr->domain_list,
		&out_ptr->domain_count, &out_ptr->domain_list) != STRFUNCS_SUCCESS)
		STR_AllocMsgList(in_ptr->domain_count, sizeof(**in_ptr->domain_list),
			tmp_error_text, "Unable to allocate the list of domain values");
	else
		return_code = PCFF_SUCCESS;

	if (return_code != PCFF_SUCCESS) {
		PCFF_FreeParam(out_ptr);
		strcat(strcpy(error_text, "Unable to copy a 'PCFF_PARAM' structure: "),
			tmp_error_text);
	}

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	PCFF_CopyParamList

   SYNOPSIS    :	return_code = PCFF_CopyParamList(in_count, in_list,
							out_count, out_list);

						int                return_code;

						unsigned int       in_count;

						const PCFF_PARAM  *in_list;

						unsigned int      *out_count;

						PCFF_PARAM       **out_list;

						char              *error_text;

   DESCRIPTION :	Copies an array of ''PCFF_PARAM'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''PCFF_PARAM''
						structures which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of
						''PCFF_PARAM'' structures which will be allocated
						and copied by this function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''PCFF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''PCFF_SUCCESS'' if the function completes without
						error. ''PCFF_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero PCFF return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :  

   SEE ALSO    :	PCFF_CopyParam

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2014 Michael L. Brock

   OUTPUT INDEX:	PCFF_CopyParamList
						Copy Functions:Parse Configuration File Facility Functions:PCFF_CopyParamList
						Parse Configuration File Facility Functions:Copy Functions:PCFF_CopyParamList

   PUBLISH XREF:	PCFF_CopyParamList

   PUBLISH NAME:	PCFF_CopyParamList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
int PCFF_CopyParamList(unsigned int in_count, const PCFF_PARAM *in_list,
	unsigned int *out_count, PCFF_PARAM **out_list, char *error_text)
{
	int          return_code = PCFF_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((PCFF_PARAM *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to allocate a 'PCFF_PARAM' structure list");
			return_code = PCFF_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			PCFF_InitParamList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = PCFF_CopyParam(in_list + count_1,
					*out_list + count_1, error_text)) != PCFF_SUCCESS) {
					PCFF_FreeParamList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/


