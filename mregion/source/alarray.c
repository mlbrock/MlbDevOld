/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Allocates memory for an array of pointers to
								structures.

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

#include <memory.h>

#include <strfuncs.h>

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MRG_AllocateArray

	SYNOPSIS		:	return_code = MRG_AllocateArray(item_name, element_name,
							array_alloc_count, allocated_count, array_list,
							error_text);

						int             return_code;

						const char     *item_name;

						const char     *element_name;

						unsigned int    array_alloc_count;

						unsigned int   *allocated_count;

						void         ***array_list;

						char           *error_text;


	DESCRIPTION	:	Allocates (or re-allocates) memory for an array of
						pointers to structures.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``item_name`` is the name of the structure for which
						this function will allocate memory. It is used exclusively
						in error messages.

						(.) ``element_name`` is the name of the structures to
						which elements in the array point. It is used exclusively
						in error messages.

						(.) ``array_alloc_count`` is the number of elements
						to be allocated.

						(-) ``array_alloc_count`` will be rounded up to an
						integral multiple of the manifest constant
						''MRG_ARRAY_ALLOC_GRAN''.  If the rounded-up value of
						``array_alloc_count`` is less than the current size of
						the array (as represented by the ``allocated_count``
						parameter), no allocation will be performed.

						(.) ``allocated_count`` is a pointer to an ''unsigned int''
						which contains the number of elements already allocated to
						the array.

						(-) If this function allocates additional memory to the
						array, the ''unsigned int'' to which the ``allocated_count``
						parameter points will be updated to reflect the new
						allocation size.

						(.) ``array_list`` is a pointer to the array of structures
						which is to be allocated by this function.

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

	SEE ALSO		:	MRG_AllocateCtlArray
						MRG_AllocateFilArray

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	MRG_AllocateArray
						Memory Management Functions:MRG_AllocateArray

	PUBLISH XREF:	MRG_AllocateArray

	PUBLISH NAME:	MRG_AllocateArray

	ENTRY CLASS	:	Memory Management Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MRG_AllocateArray(const char *item_name, const char *element_name,
	unsigned int array_alloc_count, unsigned int *allocated_count,
	void ***array_list, char *error_text)
#else
int MRG_AllocateArray(item_name, element_name, array_alloc_count,
	allocated_count, array_list, error_text)
const char     *item_name;
const char     *element_name;
unsigned int    array_alloc_count;
unsigned int   *allocated_count;
void         ***array_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code = MRG_SUCCESS;
	void **tmp_ptr;

	array_alloc_count  = (array_alloc_count) ? array_alloc_count :
		MRG_ARRAY_ALLOC_GRAN;
	array_alloc_count += (array_alloc_count % MRG_ARRAY_ALLOC_GRAN) ?
		(MRG_ARRAY_ALLOC_GRAN - (array_alloc_count % MRG_ARRAY_ALLOC_GRAN)) : 0;

	if (array_alloc_count > *allocated_count) {
		if ((tmp_ptr = ((void **)
			((*array_list == NULL) ? calloc(array_alloc_count, sizeof(void **)) :
			realloc(*array_list, array_alloc_count * sizeof(void **))))) ==
			NULL) {
			if (error_text != NULL)
				STR_AllocMsgList(array_alloc_count, sizeof(void **), error_text,
					"Unable to %sallocate the '%s' array of '%s' pointers",
					(*array_list == NULL) ? "" : "re-", item_name, element_name);
			return_code = MRG_MEMORY_FAILURE;
		}
		else {
			memset(((char *) tmp_ptr) + (*allocated_count * sizeof(void **)),
				'\0', (array_alloc_count - *allocated_count) * sizeof(void **));
			*allocated_count = array_alloc_count;
			*array_list      = tmp_ptr;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

