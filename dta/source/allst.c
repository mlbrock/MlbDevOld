/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines member offset and length for each
								element of an array of 'DTA' structures.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <stdio.h>
#include <string.h>

#include "dtai.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_BASIC_AlignList

   SYNOPSIS    :  return_code = DTA_BASIC_AlignList(type_count,
							type_list, structure_size, align_count, align_list,
							error_text);

						int             return_code;

						unsigned int    type_count;

						const DTA_TYPE *type_list;

						unsigned int   *structure_size;

						unsigned int    align_count;

						DTA            *align_list;

						char           *error_text;

   DESCRIPTION :  Given an array of structures of type ''DTA''
						with the ``type`` and ``array_length`` members populated,
						calculates the total structure size and offset and length
						of each member.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''DTA_TYPE''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``dtadata.c``
						under the names ``DTA_TypeCount`` and ``DTA_TypeList``.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is an ''unsigned int'' which contains
						the number of elements in the array ``align_list``.

						(.) ``align_list`` is an array of structures of type
						''DTA'' which contains ``align_count``
						elements. The members ``type`` and ``array_length`` of
						each element should contain the values for the desired
						structure.

						(-) If this function is successful, the ``offset``
						and ``length`` members of each element will be updated to
						describe the offset and length requirements for each member
						of the desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_AlignList
						DTA_BASIC_AlignString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_AlignList
						Data Type Alignment Functions:DTA_BASIC_AlignList
						DTA:Functions:DTA_BASIC_AlignList
						DTA:Data Type Alignment Functions:DTA_BASIC_AlignList

   PUBLISH XREF:	DTA_BASIC_AlignList

   PUBLISH NAME:	DTA_BASIC_AlignList

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_BASIC_AlignList(unsigned int type_count, const DTA_TYPE *type_list,
	unsigned int *structure_size, unsigned int align_count, DTA *align_list,
	char *error_text)
#else
int DTA_BASIC_AlignList(type_count, type_list, structure_size,
	align_count, align_list, error_text)
unsigned int    type_count;
const DTA_TYPE *type_list;
unsigned int   *structure_size;
unsigned int    align_count;
DTA            *align_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code              = DTA_SUCCESS;
	unsigned int current_offset           = 0;
	unsigned int largest_data_type_index  = 0;
	unsigned int largest_data_type_length = 0;
	unsigned int count_1;
	unsigned int align_adjust;
	unsigned int tmp_structure_size;

	structure_size  = (structure_size == NULL) ? &tmp_structure_size :
		structure_size;

	DTA_GetTypeInfo(&type_count, &type_list);

	if (!align_count) {
		strcpy(error_text, "No data types in list.");
		return_code = DTA_BAD_ARGS_FAILURE;
	}
	else {
		for (count_1 = 0; count_1 < align_count; count_1++) {
			if (align_list[count_1].type >= type_count) {
				sprintf(error_text, "%s (%u) %s 0 through %u, inclusive.",
					"Invalid data-type number", align_list[count_1].type,
					"should be in the range", type_count - 1);
				return_code = DTA_FAILURE;
				break;
			}
			align_list[count_1].array_length =
				(!align_list[count_1].array_length) ? 1 :
				align_list[count_1].array_length;
			if ((type_list[align_list[count_1].type].type_align > 1) &&
				(type_list[align_list[count_1].type].type_length >
				largest_data_type_length)) {
				largest_data_type_index  = align_list[count_1].type;
				largest_data_type_length =
					type_list[align_list[count_1].type].type_length;
			}
			if ((type_list[align_list[count_1].type].type_align > 1) &&
				current_offset && ((align_adjust = (current_offset %
				type_list[align_list[count_1].type].type_align)) > 0))
				current_offset +=
					type_list[align_list[count_1].type].type_align - align_adjust;
			align_list[count_1].offset  = current_offset;
			align_list[count_1].length  =
				type_list[align_list[count_1].type].type_length *
				align_list[count_1].array_length;
			current_offset             += align_list[count_1].length;
		}
		if (return_code == DTA_SUCCESS) {
			if (largest_data_type_length && ((align_adjust = (current_offset %
				type_list[largest_data_type_index].type_align)) > 0))
				current_offset += type_list[largest_data_type_index].type_align -
					align_adjust;
			*structure_size = current_offset;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_AlignList

   SYNOPSIS    :  return_code = DTA_AlignList(structure_size,
							align_count, align_list, error_text);

						int           return_code;

						unsigned int *structure_size;

						unsigned int  align_count;

						DTA          *align_list;

						char         *error_text;

   DESCRIPTION :  Given an array of structures of type ''DTA''
						with the ``type`` and ``array_length`` members populated,
						calculates the total structure size and offset and length
						of each member.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is an ''unsigned int'' which contains
						the number of elements in the array ``align_list``.

						(.) ``align_list`` is an array of structures of type
						''DTA'' which contains ``align_count``
						elements. The members ``type`` and ``array_length`` of
						each element should contain the values for the desired
						structure.

						(-) If this function is successful, the ``offset``
						and ``length`` members of each element will be updated to
						describe the offset and length requirements for each member
						of the desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_BASIC_AlignList
						DTA_AlignString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	DTA_AlignList
						Data Type Alignment Functions:DTA_AlignList
						DTA:Functions:DTA_AlignList
						DTA:Data Type Alignment Functions:DTA_AlignList

   PUBLISH XREF:	DTA_AlignList

   PUBLISH NAME:	DTA_AlignList

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_AlignList(unsigned int *structure_size, unsigned int align_count,
	DTA *align_list, char *error_text)
#else
int DTA_AlignList(structure_size, align_count, align_list, error_text)
unsigned int *structure_size;
unsigned int  align_count;
DTA          *align_list;
char         *error_text;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_AlignList(0, NULL, structure_size, align_count,
		align_list, error_text));
}
/* *********************************************************************** */

