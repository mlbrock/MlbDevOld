/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'PCFF_CFG' structures.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2015.
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

   NAME        :	PCFF_CopyCfg

   SYNOPSIS    :	return_code = PCFF_CopyCfg(in_ptr, out_ptr,
							error_text);

						int             return_code;

						const PCFF_CFG *in_ptr;

						PCFF_CFG       *out_ptr;

						char           *error_text;

   DESCRIPTION :	Copies a single ''PCFF_CFG'' structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''PCFF_CFG''
						structure which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''PCFF_CFG''
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

   SEE ALSO    :	PCFF_CopyCfgList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2015 Michael L. Brock

   OUTPUT INDEX:	PCFF_CopyCfg
						Copy Functions:Parse Configuration File Facility Functions:PCFF_CopyCfg
						Parse Configuration File Facility Functions:Copy Functions:PCFF_CopyCfg

   PUBLISH XREF:	PCFF_CopyCfg

   PUBLISH NAME:	PCFF_CopyCfg

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
int PCFF_CopyCfg(const PCFF_CFG *in_ptr, PCFF_CFG *out_ptr, char *error_text)
{
	int  return_code;
	char tmp_error_text[PCFF_MAX_ERROR_TEXT];

	PCFF_InitCfg(out_ptr);

	if ((return_code = PCFF_CopyItemList(in_ptr->item_count,
		in_ptr->item_list, &out_ptr->item_count, &out_ptr->item_list,
		tmp_error_text)) != PCFF_SUCCESS)
		strcat(strcpy(error_text, "Unable to copy a 'PCFF_CFG' structure: "),
			tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	PCFF_CopyCfgList

   SYNOPSIS    :	return_code = PCFF_CopyCfgList(in_count, in_list,
							out_count, out_list);

						int              return_code;

						unsigned int     in_count;

						const PCFF_CFG  *in_list;

						unsigned int    *out_count;

						PCFF_CFG       **out_list;

						char            *error_text;

   DESCRIPTION :	Copies an array of ''PCFF_CFG'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''PCFF_CFG''
						structures which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of
						''PCFF_CFG'' structures which will be allocated
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

   SEE ALSO    :	PCFF_CopyCfg

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2015 Michael L. Brock

   OUTPUT INDEX:	PCFF_CopyCfgList
						Copy Functions:Parse Configuration File Facility Functions:PCFF_CopyCfgList
						Parse Configuration File Facility Functions:Copy Functions:PCFF_CopyCfgList

   PUBLISH XREF:	PCFF_CopyCfgList

   PUBLISH NAME:	PCFF_CopyCfgList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
int PCFF_CopyCfgList(unsigned int in_count, const PCFF_CFG *in_list,
	unsigned int *out_count, PCFF_CFG **out_list, char *error_text)
{
	int          return_code = PCFF_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((PCFF_CFG *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to allocate a 'PCFF_CFG' structure list");
			return_code = PCFF_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			PCFF_InitCfgList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = PCFF_CopyCfg(in_list + count_1,
					*out_list + count_1, error_text)) != PCFF_SUCCESS) {
					PCFF_FreeCfgList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/


