/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Allocates memory for the list of pointers to
								'MRG_REG' structures in an 'MRG_FIL' structure.

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

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MRG_AllocateFilArray

	SYNOPSIS		:	return_code = MRG_AllocateFilArray(fil_ptr,
							array_alloc_count, error_text);

						int           return_code;

						MRG_FIL      *fil_ptr;

						unsigned int  array_alloc_count;

						char         *error_text;


	DESCRIPTION	:	Allocates (or re-allocates) memory for the ``region_list``
						member of an ''MRG_FIL'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``fil_ptr`` points to the ''MRG_FIL'' structure for
						which the ''MRG_REG'' array of pointers is to be
						allocated by this function.

						(.) ``array_alloc_count`` is the number of elements in
						the ''MRG_FIL'' ``region_list`` member to be allocated.

						(-) ``array_alloc_count`` will be rounded up to an
						integral multiple of the manifest constant
						''MRG_ARRAY_ALLOC_GRAN''.  If the rounded-up value of
						``array_alloc_count`` is less than the current size of
						the array ``region_list`` (as represented by the
						``allocated_count`` member), no allocation will be
						performed.

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

	SEE ALSO		:	MRG_AllocateFilArray
						MRG_AllocateArray
						MRG_AllocateCtlArray

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	MRG_AllocateFilArray
						Memory Management Functions:MRG_AllocateFilArray

	PUBLISH XREF:	MRG_AllocateFilArray

	PUBLISH NAME:	MRG_AllocateFilArray

	ENTRY CLASS	:	Memory Management Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MRG_AllocateFilArray(MRG_FIL *fil_ptr, unsigned int array_alloc_count,
	char *error_text)
#else
int MRG_AllocateFilArray(fil_ptr, array_alloc_count, error_text)
MRG_FIL      *fil_ptr;
unsigned int  array_alloc_count;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MRG_CheckFil(fil_ptr, error_text)) == MRG_SUCCESS)
		return_code = MRG_AllocateArray("MRG_FIL", "MRG_REG", array_alloc_count,
			&fil_ptr->allocated_count, ((void ***) &fil_ptr->region_list),
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

