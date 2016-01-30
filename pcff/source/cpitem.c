/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'PCFF_ITEM' structures.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2016.
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

   NAME        :	PCFF_CopyItem

   SYNOPSIS    :	return_code = PCFF_CopyItem(in_ptr, out_ptr,
							error_text);

						int              return_code;

						const PCFF_ITEM *in_ptr;

						PCFF_ITEM       *out_ptr;

						char            *error_text;

   DESCRIPTION :	Copies a single ''PCFF_ITEM'' structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''PCFF_ITEM''
						structure which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''PCFF_ITEM''
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

   SEE ALSO    :	PCFF_CopyItemList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

   OUTPUT INDEX:	PCFF_CopyItem
						Copy Functions:Parse Configuration File Facility Functions:PCFF_CopyItem
						Parse Configuration File Facility Functions:Copy Functions:PCFF_CopyItem

   PUBLISH XREF:	PCFF_CopyItem

   PUBLISH NAME:	PCFF_CopyItem

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
int PCFF_CopyItem(const PCFF_ITEM *in_ptr, PCFF_ITEM *out_ptr,
	char *error_text)
{
	int  return_code = PCFF_MEMORY_FAILURE;
	char tmp_error_text[PCFF_MAX_ERROR_TEXT];

	PCFF_InitItem(out_ptr);

	if ((in_ptr->name != NULL) &&
		((out_ptr->name = strdup(in_ptr->name)) == NULL))
		STR_AllocMsgItem(strlen(in_ptr->name) + 1, tmp_error_text,
			"Unable to allocate memory for a copy of the item name");
	else if ((in_ptr->value != NULL) &&
		((out_ptr->value = strdup(in_ptr->value)) == NULL))
		STR_AllocMsgItem(strlen(in_ptr->value) + 1, tmp_error_text,
			"Unable to allocate memory for a copy of the item value");
	else if ((return_code = PCFF_CopySrcList(in_ptr->src_count,
		in_ptr->src_list, &out_ptr->src_count, &out_ptr->src_list,
		tmp_error_text)) == PCFF_SUCCESS)
		out_ptr->order = in_ptr->order;

	if (return_code != PCFF_SUCCESS) {
		PCFF_FreeItem(out_ptr);
		strcat(strcpy(error_text,
			"Unable to copy a 'PCFF_ITEM' structure: "), tmp_error_text);
	}

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	PCFF_CopyItemList

   SYNOPSIS    :	return_code = PCFF_CopyItemList(in_count, in_list,
							out_count, out_list);

						int               return_code;

						unsigned int      in_count;

						const PCFF_ITEM  *in_list;

						unsigned int     *out_count;

						PCFF_ITEM       **out_list;

						char             *error_text;

   DESCRIPTION :	Copies an array of ''PCFF_ITEM'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''PCFF_ITEM''
						structures which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of
						''PCFF_ITEM'' structures which will be allocated
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

   SEE ALSO    :	PCFF_CopyItem

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

   OUTPUT INDEX:	PCFF_CopyItemList
						Copy Functions:Parse Configuration File Facility Functions:PCFF_CopyItemList
						Parse Configuration File Facility Functions:Copy Functions:PCFF_CopyItemList

   PUBLISH XREF:	PCFF_CopyItemList

   PUBLISH NAME:	PCFF_CopyItemList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
int PCFF_CopyItemList(unsigned int in_count, const PCFF_ITEM *in_list,
	unsigned int *out_count, PCFF_ITEM **out_list, char *error_text)
{
	int          return_code = PCFF_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((PCFF_ITEM *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to allocate a 'PCFF_ITEM' structure list");
			return_code = PCFF_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			PCFF_InitItemList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = PCFF_CopyItem(in_list + count_1,
					*out_list + count_1, error_text)) != PCFF_SUCCESS) {
					PCFF_FreeItemList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/


