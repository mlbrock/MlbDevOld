/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'PCFF_IP_HSP' structures.

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

   NAME        :	PCFF_CopyHostServProto

   SYNOPSIS    :	return_code = PCFF_CopyHostServProto(in_ptr, out_ptr,
							error_text);

						int                         return_code;

						const PCFF_IP_HSP *in_ptr;

						PCFF_IP_HSP       *out_ptr;

						char              *error_text;

   DESCRIPTION :	Copies a single ''PCFF_IP_HSP'' structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''PCFF_IP_HSP''
						structure which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''PCFF_IP_HSP''
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

   SEE ALSO    :	PCFF_CopyHostServProtoList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2014 Michael L. Brock

   OUTPUT INDEX:	PCFF_CopyHostServProto
						Copy Functions:Parse Configuration File Facility Functions:PCFF_CopyHostServProto
						Parse Configuration File Facility Functions:Copy Functions:PCFF_CopyHostServProto

   PUBLISH XREF:	PCFF_CopyHostServProto

   PUBLISH NAME:	PCFF_CopyHostServProto

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
int PCFF_CopyHostServProto(const PCFF_IP_HSP *in_ptr, PCFF_IP_HSP *out_ptr,
	char *error_text)
{
	int  return_code = PCFF_MEMORY_FAILURE;
	char tmp_error_text[PCFF_MAX_ERROR_TEXT];

	PCFF_InitHostServProto(out_ptr);

	if ((in_ptr->spec_string != NULL) &&
		((out_ptr->spec_string = strdup(in_ptr->spec_string)) == NULL))
		STR_AllocMsgItem(strlen(in_ptr->spec_string) + 1, tmp_error_text,
			"Unable to allocate memory for a copy of the specification string");
	else if ((in_ptr->host_name != NULL) &&
		((out_ptr->host_name = strdup(in_ptr->host_name)) == NULL))
		STR_AllocMsgItem(strlen(in_ptr->host_name) + 1, tmp_error_text,
			"Unable to allocate memory for a copy of the IP host name");
	else if ((in_ptr->service_name != NULL) &&
		((out_ptr->service_name = strdup(in_ptr->service_name)) == NULL))
		STR_AllocMsgItem(strlen(in_ptr->service_name) + 1, tmp_error_text,
			"Unable to allocate memory for a copy of the IP service name");
	else if ((in_ptr->protocol_name != NULL) &&
		((out_ptr->protocol_name = strdup(in_ptr->protocol_name)) == NULL))
		STR_AllocMsgItem(strlen(in_ptr->protocol_name) + 1, tmp_error_text,
			"Unable to allocate memory for a copy of the IP protocol name");
	else {
		out_ptr->service_number  = in_ptr->service_number;
		out_ptr->protocol_number = in_ptr->protocol_number;
		return_code              = PCFF_SUCCESS;
	}

	if (return_code != PCFF_SUCCESS) {
		PCFF_FreeHostServProto(out_ptr);
		strcat(strcpy(error_text,
			"Unable to copy a 'PCFF_IP_HSP' structure: "), tmp_error_text);
	}

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	PCFF_CopyHostServProtoList

   SYNOPSIS    :	return_code = PCFF_CopyHostServProtoList(in_count, in_list,
							out_count, out_list);

						int                 return_code;

						unsigned int        in_count;

						const PCFF_IP_HSP  *in_list;

						unsigned int       *out_count;

						PCFF_IP_HSP       **out_list;

						char               *error_text;

   DESCRIPTION :	Copies an array of ''PCFF_IP_HSP'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''PCFF_IP_HSP''
						structures which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of
						''PCFF_IP_HSP'' structures which will be allocated
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

   SEE ALSO    :	PCFF_CopyHostServProto

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2014 Michael L. Brock

   OUTPUT INDEX:	PCFF_CopyHostServProtoList
						Copy Functions:Parse Configuration File Facility Functions:PCFF_CopyHostServProtoList
						Parse Configuration File Facility Functions:Copy Functions:PCFF_CopyHostServProtoList

   PUBLISH XREF:	PCFF_CopyHostServProtoList

   PUBLISH NAME:	PCFF_CopyHostServProtoList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
int PCFF_CopyHostServProtoList(unsigned int in_count,
	const PCFF_IP_HSP *in_list, unsigned int *out_count, PCFF_IP_HSP **out_list,
	char *error_text)
{
	int          return_code = PCFF_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((PCFF_IP_HSP *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to allocate a 'PCFF_IP_HSP' structure list");
			return_code = PCFF_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			PCFF_InitHostServProtoList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = PCFF_CopyHostServProto(in_list + count_1,
					*out_list + count_1, error_text)) != PCFF_SUCCESS) {
					PCFF_FreeHostServProtoList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/


