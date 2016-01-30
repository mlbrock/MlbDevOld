/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the validatity of an index element number.

	Revision History	:	1995-08-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dcr.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_CheckIndexElement

	SYNOPSIS		:	return_code = DCR_CheckIndexElement(cache_ptr,
							index_element, error_text);

						int              return_code;

						const DCR_CACHE *cache_ptr;

						unsigned int     index_element;

						char            *error_text;

	DESCRIPTION	:	Determines the validatity of an index element number.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' for which the index element is to be
						validated.

						(.) ``index_element`` is the index element to be validated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR return codes on error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	DCR_CheckIndexElement
						DCR Cache Check Functions:DCR_CheckIndexElement
						DCR Cache Functions:DCR_CheckIndexElement

	PUBLISH XREF:	DCR_CheckIndexElement

	PUBLISH NAME:	DCR_CheckIndexElement

EOH */
/* *********************************************************************** */
int DCR_CheckIndexElement(cache_ptr, index_element, error_text)
const DCR_CACHE *cache_ptr;
unsigned int     index_element;
char            *error_text;
{
	int return_code = DCR_SUCCESS;

	if (index_element >= cache_ptr->record_count) {
		sprintf(error_text, "%s (%u) %s (%u).",
			"The specified index element", index_element,
			"is equal to or greater than the cache record count",
			cache_ptr->record_count);
		return_code = DCR_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

