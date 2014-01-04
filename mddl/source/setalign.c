/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes the DTA members of MDDL structures.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_SetAlignArrayList

   SYNOPSIS    :	return_code = MDDL_SetAlignArrayList(type_count,
							type_list, member_count, member_list, error_text);

						int             return_code;

						unsigned int    type_count;

						const DTA_TYPE *type_list;

						unsigned int     member_count;

						MDDL            *member_list;

						char            *error_text;

   DESCRIPTION :	Initializes the ``align_count`` and ``align_list`` members
						of a list of ''MDDL'' structures to values determined
						from the ``type_count`` and ``type_spec`` members.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''DTA_TYPE''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``datdata.c``
						under the names ``DTA_TypeCount`` and
						``DTA_TypeList``.

						(.) ``member_count`` is the number of elements in the
						array ``member_list``.

						(.) ``member_list`` is the array of ''MDDL''
						structures for which the align array data is to be
						calculated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''MDDL_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''MDDL_SUCCESS'' if the function completes without
						error. ''MDDL_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero MDDL return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MDDL_SetAlignArray
						MDDL_FixAlignArrayList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL_SetAlignArrayList
						Member Description Functions:MDDL_SetAlignArrayList
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_SetAlignArrayList

   PUBLISH NAME:	MDDL_SetAlignArrayList

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_SetAlignArrayList(unsigned int type_count, const DTA_TYPE *type_list,
	unsigned int member_count, MDDL *member_list, char *error_text)
#else
int MDDL_SetAlignArrayList(type_count, type_list, member_count,
	member_list, error_text)
unsigned int    type_count;
const DTA_TYPE *type_list;
unsigned int    member_count;
MDDL           *member_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MDDL_SUCCESS;

	for ( ; member_count ; member_count--, member_list++) {
		if ((return_code = MDDL_SetAlignArray(type_count, type_list,
			member_list, error_text)) != MDDL_SUCCESS)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_SetAlignArray

   SYNOPSIS    :	return_code = MDDL_SetAlignArray(type_count,
							type_list, member_ptr, error_text);

						int             return_code;

						unsigned int    type_count;

						const DTA_TYPE *type_list;

						MDDL            *member_ptr;

						char            *error_text;

   DESCRIPTION :	Initializes the ``align_count`` and ``align_list`` members
						of a ''MDDL'' structure to values determined from the
						``type_count`` and ``type_spec`` members.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''DTA_TYPE''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``dtadata.c``
						under the names ``DTA_TypeCount`` and
						``DTA_TypeList``.

						(.) ``member_ptr`` is the ''MDDL'' structure for which
						the align array data is to be calculated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''MDDL_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''MDDL_SUCCESS'' if the function completes without
						error. ''MDDL_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero MDDL return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MDDL_SetAlignArrayList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL_SetAlignArray
						Member Description Functions:MDDL_SetAlignArray
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_SetAlignArray

   PUBLISH NAME:	MDDL_SetAlignArray

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_SetAlignArray(unsigned int type_count, const DTA_TYPE *type_list,
	MDDL *member_ptr, char *error_text)
#else
int MDDL_SetAlignArray(type_count, type_list, member_ptr, error_text)
unsigned int    type_count;
const DTA_TYPE *type_list;
MDDL           *member_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  count_1;
	unsigned int  align_count;
	DTA    *align_list;
	char          dta_error_text[DTA_MAX_ERROR_TEXT];

	if ((return_code = DTA_BASIC_CountStringToList(type_count, type_list,
		DTA_FALSE, DTA_TRUE, ",", member_ptr->type_count,
		member_ptr->type_spec, NULL, &align_count, &align_list,
		dta_error_text)) != DTA_SUCCESS) {
		nstrcpy(error_text, dta_error_text, MDDL_MAX_ERROR_TEXT - 1);
		return_code = MDDL_MAP_ERROR_DTA(return_code);
	}
	else if (align_count <= MDDL_MAX_DTA_COUNT) {
		member_ptr->align_count = align_count;
		for (count_1 = 0; count_1 < align_count; count_1++) {
			member_ptr->align_list[count_1]         = align_list[count_1];
			member_ptr->align_list[count_1].offset += member_ptr->offset;
		}
		free(align_list);
	}
	else {
		free(align_list);
		sprintf(error_text,
			"%s '%-.*s' (type count=%u, type spec='%-.*s') (%u) %s (%u).",
			"The number of align elements returned for 'MDDL'",
			((int) (sizeof(member_ptr->name) - 1)), member_ptr->name,
			member_ptr->type_count,
			((int) (sizeof(member_ptr->type_spec) - 1)), member_ptr->type_spec,
			align_count, "exceeds the maximum permissible",
			MDDL_MAX_DTA_COUNT);
		return_code = MDDL_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

