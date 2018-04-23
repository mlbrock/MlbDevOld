/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <string.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_SetDisplayLength

   SYNOPSIS    :	return_code = DBC_MSSQL_SetDisplayLength(type_count,
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
						''DBC_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''DBC_SUCCESS'' if the function completes without
						error. ''DBC_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero DBC return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MDDL_SetDisplayLength

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_SetDisplayLength
						Member Description Functions:DBC_MSSQL_SetDisplayLength
						DBC Microsoft SQL Server Functions:DBC_MSSQL_SetDisplayLength
						DBC Functions:Member Description Functions:DBC_MSSQL_SetDisplayLength

   PUBLISH XREF:	DBC_MSSQL_SetDisplayLength

   PUBLISH NAME:	DBC_MSSQL_SetDisplayLength

	ENTRY CLASS	:	Member Description Functions
						DBC Functions:Member Description Functions

EOH */
/*	***********************************************************************	*/
int DBC_MSSQL_SetDisplayLength(type_count, type_list, member_ptr,
	header_flag, null_string_length, intra_field_sep_length, user_data_ptr,
	error_text)
unsigned int          type_count;
const DTA_TYPE *type_list;
MDDL           *member_ptr;
int                   header_flag;
unsigned int          null_string_length;
unsigned int          intra_field_sep_length;
void                 *user_data_ptr;
char                 *error_text;
{
	int          return_code = DBC_SUCCESS;
	unsigned int this_length = 0;
	MDDL         tmp_member;
	char         mddl_error_text[MDDL_MAX_ERROR_TEXT];

	DTA_GetTypeInfo(&type_count, &type_list);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		This member may have its own length function . . .					*/
	/*	*****************************************************************	*/
	if ((member_ptr->length_function != NULL) &&
		(member_ptr->length_function != DBC_MSSQL_SetDisplayLength))
		return_code = (*member_ptr->length_function)(type_count, type_list,
			member_ptr, header_flag, null_string_length, intra_field_sep_length,
			user_data_ptr, error_text);
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Otherwise, we determine the length based upon the Microsoft		*/
	/*	SQL Server types which comprise the member . . .						*/
	/*	*****************************************************************	*/
	else {
		switch (member_ptr->dbc_type) {
			case SQLBINARY		:
			case SQLIMAGE		:
				this_length = 2 + (member_ptr->data_length * 2);
				break;
			case SQLBIT			:
				this_length = 5;
				break;
			case SQLCHAR		:
			case SQLTEXT		:
				this_length = member_ptr->data_length;
				break;
			case SQLINT1		:
				this_length = 3;
				break;
			case SQLINT2		:
				this_length = 6;
				break;
			case SQLINT4		:
				this_length = 11;
				break;
			case SQLFLT4		:
				this_length = 20;
				break;
			case SQLFLT8 		:
				this_length = 20;
				break;
			case SQLMONEY		:
				this_length = 21;
				break;
			case SQLMONEY4		:
				this_length = 12;
				break;
			case SQLDATETIME	:
			case SQLDATETIM4	:
				this_length = 4 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 3;
				break;
			default				:
				tmp_member                 = *member_ptr;
				tmp_member.length_function = NULL;
				if ((return_code = MDDL_SetDisplayLength(type_count,
					type_list, &tmp_member, header_flag, null_string_length,
					intra_field_sep_length, user_data_ptr, mddl_error_text)) ==
					MDDL_SUCCESS)
					member_ptr->display_length = tmp_member.display_length;
				else {
					nstrcpy(error_text, mddl_error_text, DBC_MAX_ERROR_TEXT - 1);
					return_code = DBC_MAP_ERROR_MDDL(return_code);
				}
				break;
		}
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We may need to adjust the field width:									*/
	/*																							*/
	/*		1)	If the length of the NULL string indicator is greater			*/
	/*			than the calculated length of the member.							*/
	/*																							*/
	/*		2) If headers are to be used and the length of the member		*/
	/*			name is greater than than the calculated length of the		*/
	/*			member.																		*/
	/*																							*/
	/*		3)	If headers are to be used and a display name has been			*/
	/*			specified for the member which is longer than the				*/
	/*			calculated length of the member.										*/
	/*	*****************************************************************	*/
	if (return_code == DBC_SUCCESS) {
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

