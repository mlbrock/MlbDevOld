/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Allocates memory for a single item.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <string.h>

#include <strfuncs.h>

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MRG_AllocateItem

	SYNOPSIS		:	return_code = MRG_AllocateItem(item_name, item_size,
							item_ptr, error_text);

						int            return_code;

						const char    *item_name;

						unsigned int   item_size;

						void         **item_ptr;

						char          *error_text;


	DESCRIPTION	:	Allocates memory for a single MREGION structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``item_name`` is the name of the structure for which
						this function will allocate memory. It is used exclusively
						in error messages.

						(.) ``item_size`` is the size of the structure to be
						allocated by this function.

						(.) ``item_ptr`` points to the pointer to the
						structure to be allocated by this function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''MRG_MAX_ERROR_TEXT'' characters in length.

						(-) The ``error_text`` parameter may be ''NULL'', in which
						case this function will not de-reference it.

	RETURNS		:	Returns from this function are as follow:

						(.) ''MRG_SUCCESS'' if the function completes without
						error. ''MRG_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero MREGION return codes
						indicative of error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_AllocateCtl
						MRG_AllocateFil
						MRG_AllocateReg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	MRG_AllocateItem
						Memory Management Functions:MRG_AllocateItem

	PUBLISH XREF:	MRG_AllocateItem

	PUBLISH NAME:	MRG_AllocateItem

	ENTRY CLASS	:	Memory Management Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MRG_AllocateItem(const char *item_name, unsigned int item_size,
	void **item_ptr, char *error_text)
#else
int MRG_AllocateItem(item_name, item_size, item_ptr, error_text)
const char    *item_name;
unsigned int   item_size;
void         **item_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MRG_SUCCESS;

	*item_ptr = NULL;

	if (!item_size) {
		strcat(nstrcat(strcpy(error_text, "Invalid parameter: '"),
			item_name, MRG_MAX_ERROR_TEXT / 2), "' is 'NULL'.");
		return_code = MRG_BAD_ARGS_FAILURE;
	}
	else if ((*item_ptr = ((void *) calloc(1, item_size))) == NULL) {
		if (error_text != NULL)
			STR_AllocMsgItem(item_size, error_text,
				"Unable to allocate memory for the '%s' structure", item_name);
		return_code = MRG_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

