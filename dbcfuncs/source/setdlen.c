/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sets an 'MDDL' structure 'display_length' member.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include "dbcfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_SetDisplayLength

   SYNOPSIS    :	return_code = DBC_SetDisplayLength(dbc_context_ptr,
							type_count, type_list, member_ptr, header_flag,
							null_string_length, intra_field_sep_length,
							user_data_ptr, error_text);

						int                return_code;

						const DBC_CONTEXT *dbc_context_ptr;

						unsigned int       type_count;

						const DTA_TYPE    *type_list;

						MDDL              *member_ptr;

						int                header_flag;

						unsigned int       null_string_length;

						unsigned int       intra_field_sep_length;

						void              *user_data_ptr;

						char              *error_text;

   DESCRIPTION :	Initializes the ``display_length`` member of a
						''MDDL'' structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` is a pointer to the
						''DBC_CONTEXT'' structure which contains the facility
						to be used.

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
						''DBC_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''DBC_SUCCESS'' if the function completes without
						error. ''DBC_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero DBC return codes
						indicative of error.

   SEE ALSO    :	MDDL_SetDisplayLength

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_SetDisplayLength
						Member Description Functions:DBC_SetDisplayLength
						Database Functions:Facility Functions:DBC_SetDisplayLength
						DBC Functions:Member Description Functions:DBC_SetDisplayLength

   PUBLISH XREF:	DBC_SetDisplayLength

   PUBLISH NAME:	DBC_SetDisplayLength

	ENTRY CLASS	:	Member Description Functions
						Database Functions:Facility Functions
						DBC Functions:Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SetDisplayLength(const DBC_CONTEXT *dbc_context_ptr,
	unsigned int type_count, const DTA_TYPE *type_list, MDDL *member_ptr,
	int header_flag, unsigned int null_string_length,
	unsigned int intra_field_sep_length, void *user_data_ptr, char *error_text)
#else
int DBC_SetDisplayLength(dbc_context_ptr, type_count, type_list,
	member_ptr, header_flag, null_string_length, intra_field_sep_length,
	user_data_ptr, error_text)
const DBC_CONTEXT *dbc_context_ptr;
unsigned int       type_count;
const DTA_TYPE    *type_list;
MDDL              *member_ptr;
int                header_flag;
unsigned int       null_string_length;
unsigned int       intra_field_sep_length;
void              *user_data_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.set_display_length),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.set_display_length)
			(type_count, type_list, member_ptr, header_flag, null_string_length,
			intra_field_sep_length, user_data_ptr, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

