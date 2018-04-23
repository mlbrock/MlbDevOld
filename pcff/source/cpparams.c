/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'PCFF_PARAM_SPEC' structures.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2018.
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

   NAME        :	PCFF_CopyParamSpec

   SYNOPSIS    :	return_code = PCFF_CopyParamSpec(in_ptr, out_ptr,
							error_text);

						int                    return_code;

						const PCFF_PARAM_SPEC *in_ptr;

						PCFF_PARAM_SPEC       *out_ptr;

						char                  *error_text;

   DESCRIPTION :	Copies a single ''PCFF_PARAM_SPEC'' structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''PCFF_PARAM_SPEC''
						structure which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''PCFF_PARAM_SPEC''
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

   SEE ALSO    :	PCFF_CopyParamSpecList
						PCFF_CopyParamList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2018 Michael L. Brock

   OUTPUT INDEX:	PCFF_CopyParamSpec
						Copy Functions:Parse Configuration File Facility Functions:PCFF_CopyParamSpec
						Parse Configuration File Facility Functions:Copy Functions:PCFF_CopyParamSpec

   PUBLISH XREF:	PCFF_CopyParamSpec

   PUBLISH NAME:	PCFF_CopyParamSpec

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
int PCFF_CopyParamSpec(const PCFF_PARAM_SPEC *in_ptr,
	PCFF_PARAM_SPEC *out_ptr, char *error_text)
{
	int  return_code = PCFF_MEMORY_FAILURE;
	char tmp_error_text[PCFF_MAX_ERROR_TEXT];

	*out_ptr = *in_ptr;

	if ((return_code = PCFF_CopyParamList(in_ptr->param_count,
		in_ptr->param_list, &out_ptr->param_count, &out_ptr->param_list,
		tmp_error_text)) != PCFF_SUCCESS)
		strcat(strcpy(error_text,
			"Unable to copy a 'PCFF_PARAM_SPEC' structure: "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	PCFF_CopyParamSpecList

   SYNOPSIS    :	return_code = PCFF_CopyParamSpecList(in_count, in_list,
							out_count, out_list);

						int                     return_code;

						unsigned int            in_count;

						const PCFF_PARAM_SPEC  *in_list;

						unsigned int           *out_count;

						PCFF_PARAM_SPEC       **out_list;

						char                   *error_text;

   DESCRIPTION :	Copies an array of ''PCFF_PARAM_SPEC'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''PCFF_PARAM_SPEC''
						structures which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of
						''PCFF_PARAM_SPEC'' structures which will be allocated
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

   SEE ALSO    :	PCFF_CopyParamSpec

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2018 Michael L. Brock

   OUTPUT INDEX:	PCFF_CopyParamSpecList
						Copy Functions:Parse Configuration File Facility Functions:PCFF_CopyParamSpecList
						Parse Configuration File Facility Functions:Copy Functions:PCFF_CopyParamSpecList

   PUBLISH XREF:	PCFF_CopyParamSpecList

   PUBLISH NAME:	PCFF_CopyParamSpecList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
int PCFF_CopyParamSpecList(unsigned int in_count,
	const PCFF_PARAM_SPEC *in_list, unsigned int *out_count,
	PCFF_PARAM_SPEC **out_list, char *error_text)
{
	int          return_code = PCFF_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((PCFF_PARAM_SPEC *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to allocate a 'PCFF_PARAM_SPEC' structure list");
			return_code = PCFF_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			PCFF_InitParamSpecList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = PCFF_CopyParamSpec(in_list + count_1,
					*out_list + count_1, error_text)) != PCFF_SUCCESS) {
					PCFF_FreeParamSpecList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/


