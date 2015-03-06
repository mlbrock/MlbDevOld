/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Fixes the DTA-related members of MDDL structures.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_FixAlignArrayList

   SYNOPSIS    :	return_code = MDDL_FixAlignArrayList(type_count,
							type_list, member_count, member_list, structure_size,
							error_text);

						int             return_code;

						unsigned int    type_count;

						const DTA_TYPE *type_list;

						unsigned int    member_count;

						MDDL           *member_list;

						unsigned int   *structure_size;

						char           *error_text;

   DESCRIPTION :	Initializes the ``align_count`` and ``align_list`` members
						of a list of ''MDDL'' structures to values determined
						from the ``type_count`` and ``type_spec`` members. The
						``offset`` member is also re-calculated for each element
						in the list.

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

						(.) ``member_count`` is the number of elements in the
						array ``member_list``.

						(.) ``member_list`` is the array of ''MDDL''
						structures for which the align array data is to be
						calculated.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

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

   COPYRIGHT   :	Copyright 1993 - 2015 Michael L. Brock

   OUTPUT INDEX:	MDDL_FixAlignArrayList
						Member Description Functions:MDDL_FixAlignArrayList
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_FixAlignArrayList

   PUBLISH NAME:	MDDL_FixAlignArrayList

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_FixAlignArrayList(unsigned int type_count, const DTA_TYPE *type_list,
	unsigned int member_count, MDDL *member_list, unsigned int *structure_size,
	char *error_text)
#else
int MDDL_FixAlignArrayList(type_count, type_list, member_count,
	member_list, structure_size, error_text)
unsigned int    type_count;
const DTA_TYPE *type_list;
unsigned int    member_count;
MDDL           *member_list;
unsigned int   *structure_size;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = MDDL_SUCCESS;
	unsigned int  align_count = 0;
	DTA          *align_list;
	unsigned int  count_1;
	unsigned int  count_2;
	char          dta_error_text[DTA_MAX_ERROR_TEXT];

	if (member_count && ((return_code =
		MDDL_SetAlignArrayList(type_count, type_list, member_count,
		member_list, error_text)) == MDDL_SUCCESS)) {
		for (count_1 = 0; count_1 < member_count; count_1++)
			align_count += member_list[count_1].align_count;
		if ((align_list = ((DTA *) calloc(align_count,
			sizeof(DTA)))) == NULL) {
			STR_AllocMsgList(align_count, sizeof(DTA), error_text,
				"Unable to allocate temporary 'DTA' list");
			return_code = MDDL_MEMORY_FAILURE;
		}
		else {
			align_count = 0;
			for (count_1 = 0; count_1 < member_count; count_1++) {
				for (count_2 = 0; count_2 < member_list[count_1].align_count;
					count_2++)
					align_list[align_count++] =
						member_list[count_1].align_list[count_2];
			}
			if ((return_code = DTA_BASIC_AlignList(type_count, type_list,
				structure_size, align_count, align_list, dta_error_text)) !=
				DTA_SUCCESS) {
				nstrcpy(error_text, dta_error_text, MDDL_MAX_ERROR_TEXT - 1);
				return_code = MDDL_MAP_ERROR_DTA(return_code);
			}
			else {
				align_count = 0;
				for (count_1 = 0; count_1 < member_count; count_1++) {
					member_list[count_1].offset = align_list[align_count].offset;
					for (count_2 = 0; count_2 < member_list[count_1].align_count;
						count_2++)
						member_list[count_1].align_list[count_2] =
							align_list[align_count++];
				}
			}
			free(align_list);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

