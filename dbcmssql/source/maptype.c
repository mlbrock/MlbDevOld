/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps a DBC basic type to an 'MDDL' structure which
								represents that type in the underlying DBC Microsoft
								SQL Server facility.

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
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_MapTypeToMDDL(dbc_basic_type, mddl_ptr, error_text)
DBC_BASIC_TYPE  dbc_basic_type;
MDDL           *mddl_ptr;
char           *error_text;
{
	int                 return_code = DBC_SUCCESS;
	int                 syb_type;
	const DBC_MSSQL_TYPE *type_ptr;
	unsigned int        structure_size;
	char                mddl_error_text[MDDL_MAX_ERROR_TEXT];

	MDDL_InitMember(mddl_ptr);

	switch (dbc_basic_type) {
		case DBC_BASIC_TYPE_BIT        :
			syb_type = SQLBIT;
			break;
		case DBC_BASIC_TYPE_CHAR       :
			syb_type = SQLCHAR;
			break;
		case DBC_BASIC_TYPE_INT1       :
			syb_type = SQLINT1;
			break;
		case DBC_BASIC_TYPE_INT2       :
			syb_type = SQLINT2;
			break;
		case DBC_BASIC_TYPE_INT4       :
			syb_type = SQLINT4;
			break;
		case DBC_BASIC_TYPE_INT8       :
			strcpy(error_text,
				"DBC basic type 'DBC_BASIC_TYPE_INT8' not supported.");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
		case DBC_BASIC_TYPE_FLOAT      :
			syb_type = SQLFLT4;
			break;
		case DBC_BASIC_TYPE_DOUBLE     :
			syb_type = SQLFLT8;
			break;
		case DBC_BASIC_TYPE_DOUBLE_LONG:
			strcpy(error_text,
				"DBC basic type 'DBC_BASIC_TYPE_DOUBLE_LONG' not supported.");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
		case DBC_BASIC_TYPE_MONEY_SHORT:
			syb_type = SQLMONEY4;
			break;
		case DBC_BASIC_TYPE_MONEY_LONG :
			syb_type = SQLMONEY;
			break;
		case DBC_BASIC_TYPE_DATE_SHORT :
			syb_type = SQLDATETIM4;
			break;
		case DBC_BASIC_TYPE_DATE_LONG  :
			syb_type = SQLDATETIME;
			break;
		case DBC_BASIC_TYPE_TIME_SHORT :
			syb_type = SQLDATETIM4;
			break;
		case DBC_BASIC_TYPE_TIME_LONG  :
			syb_type = SQLDATETIME;
			break;
		case DBC_BASIC_TYPE_BINARY     :
			syb_type = SQLBINARY;
			break;
		case DBC_BASIC_TYPE_TEXT       :
			syb_type = SQLTEXT;
			break;
		case DBC_BASIC_TYPE_IMAGE      :
			syb_type = SQLIMAGE;
			break;
		default                        :
			sprintf(error_text, "DBC basic type '%u' not supported.",
				((unsigned int) dbc_basic_type));
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	if (return_code == DBC_SUCCESS) {
		if ((type_ptr = DBC_MSSQL_FIND_TypeByType(syb_type, NULL)) == NULL) {
			sprintf(error_text, "%s '%u', Microsoft SQL Server type '%d'.",
				"Unable to locate Microsoft SQL Server type information for DBC "
				"basic type", ((unsigned int) dbc_basic_type), syb_type);
			return_code = DBC_BAD_TYPE_FAILURE;
		}
		else {
			nstrcpy(mddl_ptr->name, type_ptr->name,
				sizeof(mddl_ptr->name) - 1);
			nstrcpy(mddl_ptr->type_spec, type_ptr->type_spec,
				sizeof(mddl_ptr->type_spec) - 1);
			mddl_ptr->data_length     = type_ptr->type_length;
			mddl_ptr->length          = type_ptr->type_length;
			mddl_ptr->offset          = 0;
			mddl_ptr->type_count      = (type_ptr->type_count) ?
				type_ptr->type_count : 1;
			mddl_ptr->align_count     = 0;
			mddl_ptr->display_length  = 0;
			mddl_ptr->display_name    = NULL;
			mddl_ptr->dbc_type        = type_ptr->type;
			mddl_ptr->length_function = DBC_MSSQL_SetDisplayLength;
			mddl_ptr->dump_function   = DBC_MSSQL_DumpField;
			mddl_ptr->user_int_1      = dbc_basic_type;
			mddl_ptr->user_int_2      = 0;
			mddl_ptr->user_ptr_1      = NULL;
			mddl_ptr->user_ptr_2      = NULL;
			if ((return_code = MDDL_FixAlignArrayList(0, NULL, 1, mddl_ptr,
				&structure_size, mddl_error_text)) != MDDL_SUCCESS) {
				sprintf(error_text, "%s '%u' %s '%d' ('%-.100s'): %-.500s",
					"Unable to map the DBC basic type",
					((unsigned int) dbc_basic_type),
					"to the Microsoft SQL Server type",
					syb_type, type_ptr->name, mddl_error_text);
				return_code = DBC_MAP_ERROR_MDDL(return_code);
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

