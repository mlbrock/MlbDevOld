/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the length of the 'display_name'
								member.

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

#include <stdio.h>
#include <string.h>

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_SetDisplayLengthList

   SYNOPSIS    :	return_code = MDDL_SetDisplayLengthList(type_count,
							type_list, member_count, member_list, header_flag,
							null_string_length, intra_field_sep_length,
							user_data_ptr, error_text);

						int             return_code;

						unsigned int    type_count;

						const DTA_TYPE *type_list;

						unsigned int    member_count;

						MDDL           *member_list;

						int             header_flag;

						unsigned int    null_string_length;

						unsigned int    intra_field_sep_length;

						void           *user_data_ptr;

						char            *error_text;

   DESCRIPTION :	Initializes the ``display_length`` members of a list of
						''MDDL'' structures.

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
						structures for which the ``display_length`` member is to be
						calculated.

						(.) ``header_flag`` indicates whether the length of the
						name of the member is to be used as the minimum length of
						the member.

						(-) If ``header_flag`` is not zero, then this function will
						consider the maximum length of the ``display_name`` member
						and the ``name`` member to be the minimum length of the
						member.

						(.) ``null_string_length`` is the length of the string to be
						used to indicate that a member of a record contains a
						''NULL'' value.

						(-) If ``null_string_length`` is greater than ''0'', it will
						be considered by this function to be the minimum length of
						the member.

						(.) ``intra_field_sep_length`` is the length of the string
						to be used to separate the elements of fields which have an
						array data type or which are comprised of more than one
						primitive data type.

						(.) ``user_data_ptr`` is a pointer to ''void'' which the
						application programmer may use in order to attach
						application-specific knowledge to the structure.

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

   SEE ALSO    :	MDDL_SetDisplayLength

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2015 Michael L. Brock

   OUTPUT INDEX:	MDDL_SetDisplayLengthList
						Member Description Functions:MDDL_SetDisplayLengthList
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_SetDisplayLengthList

   PUBLISH NAME:	MDDL_SetDisplayLengthList

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_SetDisplayLengthList(unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int member_count, MDDL *member_list,
	int header_flag, unsigned int null_string_length,
	unsigned int intra_field_sep_length, void *user_data_ptr, char *error_text)
#else
int MDDL_SetDisplayLengthList(type_count, type_list, member_count,
	member_list, header_flag, null_string_length, intra_field_sep_length,
	user_data_ptr, error_text)
unsigned int    type_count;
const DTA_TYPE *type_list;
unsigned int    member_count;
MDDL           *member_list;
int             header_flag;
unsigned int    null_string_length;
unsigned int    intra_field_sep_length;
void           *user_data_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MDDL_SUCCESS;

	for ( ; member_count ; member_count--, member_list++) {
		if ((return_code = MDDL_SetDisplayLength(type_count, type_list,
			member_list, header_flag, null_string_length, intra_field_sep_length,
			user_data_ptr, error_text)) != MDDL_SUCCESS)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_SetDisplayLength

   SYNOPSIS    :	return_code = MDDL_SetDisplayLength(type_count,
							type_list, member_ptr, header_flag, null_string_length,
							intra_field_sep_length, user_data_ptr, error_text);

						int             return_code;

						unsigned int    type_count;

						const DTA_TYPE *type_list;

						MDDL           *member_ptr;

						int             header_flag;

						unsigned int    null_string_length;

						unsigned int    intra_field_sep_length;

						void           *user_data_ptr;

						char           *error_text;

   DESCRIPTION :	Initializes the ``display_length`` member of a
						''MDDL'' structure.

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
						the ``display_length`` member is to be calculated.

						(.) ``header_flag`` indicates whether the length of the
						name of the member is to be used as the minimum length of
						the member.

						(-) If ``header_flag`` is not zero, then this function will
						consider the maximum length of the ``display_name`` member
						and the ``name`` member to be the minimum length of the
						member.

						(.) ``null_string_length`` is the length of the string to be
						used to indicate that a member of a record contains a
						''NULL'' value.

						(-) If ``null_string_length`` is greater than ''0'', it will
						be considered by this function to be the minimum length of
						the member.

						(.) ``intra_field_sep_length`` is the length of the string
						to be used to separate the elements of fields which have an
						array data type or which are comprised of more than one
						primitive data type.

						(.) ``user_data_ptr`` is a pointer to ''void'' which the
						application programmer may use in order to attach
						application-specific knowledge to the structure.

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

   SEE ALSO    :	MDDL_SetDisplayLengthList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2015 Michael L. Brock

   OUTPUT INDEX:	MDDL_SetDisplayLength
						Member Description Functions:MDDL_SetDisplayLength
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_SetDisplayLength

   PUBLISH NAME:	MDDL_SetDisplayLength

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_SetDisplayLength(unsigned int type_count, const DTA_TYPE *type_list,
	MDDL *member_ptr, int header_flag, unsigned int null_string_length,
	unsigned int intra_field_sep_length, void *user_data_ptr, char *error_text)
#else
int MDDL_SetDisplayLength(type_count, type_list, member_ptr,
	header_flag, null_string_length, intra_field_sep_length, user_data_ptr,
	error_text)
unsigned int    type_count;
const DTA_TYPE *type_list;
MDDL           *member_ptr;
int             header_flag;
unsigned int    null_string_length;
unsigned int    intra_field_sep_length;
void           *user_data_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = MDDL_SUCCESS;
	unsigned int  this_length = 0;
	unsigned int  count_1;
	const DTA    *align_ptr;

	DTA_GetTypeInfo(&type_count, &type_list);

	/*	*****************************************************************
		*****************************************************************
		This member may have its own length function . . .
		*****************************************************************	*/
	if ((member_ptr->length_function != NULL) &&
		(member_ptr->length_function != MDDL_SetDisplayLength)) {
		return_code = (*member_ptr->length_function)(type_count, type_list,
			member_ptr, header_flag, null_string_length, intra_field_sep_length,
			user_data_ptr, error_text);
		this_length = member_ptr->display_length;
	}
	/*	*****************************************************************
		*****************************************************************
		Otherwise, we determine the length based upon the primitive types
		which comprise the member . . .
		*****************************************************************	*/
	else {
		for (count_1 = 0, align_ptr = member_ptr->align_list;
			(count_1 < member_ptr->align_count) &&
			(return_code == MDDL_SUCCESS); count_1++, align_ptr++) {
			this_length += (count_1) ? intra_field_sep_length : 0;
			if (align_ptr->type >= type_count) {
				sprintf(error_text,
					"%s (index = %u, name = '%s', type = %u, spec = '%s').",
					"Invalid type number in 'MDDL' structure", count_1,
					member_ptr->name, align_ptr->type, member_ptr->type_spec);
				return_code = MDDL_FAILURE;
				break;
			}
			switch (align_ptr->type) {
				case DTA_C_unsigned_byte	:
					this_length += 2 + (align_ptr->array_length * 2);
					break;
				case DTA_C_char				:
				case DTA_C_unsigned_char	:
					this_length += (align_ptr->array_length - 1);
					break;
				case DTA_C_short				:
				case DTA_C_unsigned_short	:
				case DTA_C_int					:
				case DTA_C_unsigned_int		:
				case DTA_C_long				:
				case DTA_C_unsigned_long	:
				case DTA_C_float				:
				case DTA_C_double				:
					this_length += (align_ptr->array_length *
						type_list[align_ptr->type].printf_length) +
						((align_ptr->array_length - 1) * intra_field_sep_length);
					break;
				default							:
					sprintf(error_text,
						"%s %s (index = %u, name = '%s', type = %u, spec = '%s').",
						"Error occurred while determining the length of a",
						"'MDDL' structure", count_1, member_ptr->name,
						align_ptr->type, member_ptr->type_spec);
					return_code = MDDL_FAILURE;
					break;
			}
		}
	}

	/*	*****************************************************************
		*****************************************************************
		We may need to adjust the field width:

		1)	If the length of the NULL string indicator is greater
			than the calculated length of the member.

		2) If headers are to be used and the length of the member
			name is greater than than the calculated length of the
			member.

		3)	If headers are to be used and a display name has been
			specified for the member which is longer than the
			calculated length of the member.
		*****************************************************************	*/
	if (return_code == MDDL_SUCCESS) {
		this_length = (this_length >= null_string_length) ? this_length :
			null_string_length;
		if (header_flag) {
			this_length = (this_length >= strlen(member_ptr->name)) ?
				this_length : strlen(member_ptr->name);
			this_length = ((member_ptr->display_name == NULL) ||
				(this_length >= strlen(member_ptr->display_name))) ?
				this_length : strlen(member_ptr->display_name);
		}
		member_ptr->display_length = this_length;
	}
	/*	*****************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

