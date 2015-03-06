/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Internal Null Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps a DBC basic type to an 'MDDL' structure which
								represents that type in the underlying DBC NULL
								facility.

	Revision History	:	1996-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include <string.h>

#include "dbcnulli.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_NULL_MapTypeToMDDL(DBC_BASIC_TYPE dbc_basic_type, MDDL *mddl_ptr,
	char *error_text)
#else
int DBC_NULL_MapTypeToMDDL(dbc_basic_type, mddl_ptr, error_text)
DBC_BASIC_TYPE  dbc_basic_type;
MDDL           *mddl_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code = DBC_SUCCESS;
	DBC_BASIC_TYPE  data_type   = DBC_BASIC_TYPE_BIT;
	const char     *data_name   = NULL;
	const char     *data_spec   = NULL;
	unsigned int    data_length = 0;
	unsigned int    data_count  = 0;
	unsigned int    structure_size;
	char            mddl_error_text[MDDL_MAX_ERROR_TEXT];

	MDDL_InitMember(mddl_ptr);

	switch (dbc_basic_type) {
		case DBC_BASIC_TYPE_BIT        :
			data_type   = DBC_BASIC_TYPE_BIT;
			data_name   = "BIT";
			data_spec   = "b";
			data_length = sizeof(char);
			data_count  = 1;
			break;
		case DBC_BASIC_TYPE_CHAR       :
			data_type   = DBC_BASIC_TYPE_CHAR;
			data_name   = "CHAR";
			data_spec   = "c";
			data_length = sizeof(char);
			data_count  = 1;
			break;
		case DBC_BASIC_TYPE_INT1       :
			data_type   = DBC_BASIC_TYPE_INT1;
			data_name   = "INT1";
			data_spec   = "c";
			data_length = sizeof(char);
			data_count  = 1;
			break;
		case DBC_BASIC_TYPE_INT2       :
			data_type   = DBC_BASIC_TYPE_INT2;
			data_name   = "INT2";
			data_spec   = "s";
			data_length = sizeof(short);
			data_count  = 1;
			break;
		case DBC_BASIC_TYPE_INT4       :
			data_type   = DBC_BASIC_TYPE_INT4;
			data_name   = "INT4";
			data_spec   = "l";
			data_length = sizeof(long);
			data_count  = 1;
			break;
		case DBC_BASIC_TYPE_INT8       :
			strcpy(error_text,
				"DBC basic type 'DBC_BASIC_TYPE_INT8' not supported.");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
		case DBC_BASIC_TYPE_FLOAT      :
			data_type   = DBC_BASIC_TYPE_FLOAT;
			data_name   = "FLOAT";
			data_spec   = "f";
			data_length = sizeof(float);
			data_count  = 1;
			break;
		case DBC_BASIC_TYPE_DOUBLE     :
			data_type   = DBC_BASIC_TYPE_DOUBLE;
			data_name   = "DOUBLE";
			data_spec   = "d";
			data_length = sizeof(double);
			data_count  = 1;
			break;
		case DBC_BASIC_TYPE_DOUBLE_LONG:
			strcpy(error_text,
				"DBC basic type 'DBC_BASIC_TYPE_DOUBLE_LONG' not supported.");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
		default                        :
			sprintf(error_text, "DBC basic type '%u' not supported.",
				((unsigned int) dbc_basic_type));
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	if (return_code == DBC_SUCCESS) {
		nstrcpy(mddl_ptr->name, data_name,
			sizeof(mddl_ptr->name) - 1);
		nstrcpy(mddl_ptr->type_spec, data_spec,
			sizeof(mddl_ptr->type_spec) - 1);
		mddl_ptr->data_length     = data_length;
		mddl_ptr->length          = data_length;
		mddl_ptr->offset          = 0;
		mddl_ptr->type_count      = data_count;
		mddl_ptr->align_count     = 0;
		mddl_ptr->display_length  = 0;
		mddl_ptr->display_name    = NULL;
		mddl_ptr->dbc_type        = data_type;
		mddl_ptr->length_function = MDDL_SetDisplayLength;
		mddl_ptr->dump_function   = MDDL_DumpField;
		mddl_ptr->user_int_1      = dbc_basic_type;
		mddl_ptr->user_int_2      = 0;
		mddl_ptr->user_ptr_1      = NULL;
		mddl_ptr->user_ptr_2      = NULL;
		if ((return_code = MDDL_FixAlignArrayList(0, NULL, 1, mddl_ptr,
			&structure_size, mddl_error_text)) != MDDL_SUCCESS) {
			sprintf(error_text, "%s '%u' %s '%d' ('%-.100s'): %-.500s",
				"Unable to map the DBC basic type",
				((unsigned int) dbc_basic_type), "to the DBC NULL type",
				((unsigned int) data_type), data_name, mddl_error_text);
			return_code = DBC_MAP_ERROR_MDDL(return_code);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

