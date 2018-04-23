/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Retrieves information about the columns which
								comprise a specified table.

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

#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DBC_MSSQL_ColumnsToMembers(column_count, column_list, structure_size,
	member_count, member_list, error_text)
unsigned int        column_count;
const DBC_MSSQL_COL  *column_list;
unsigned int       *structure_size;
unsigned int       *member_count;
MDDL              **member_list;
char               *error_text;
{
	int          return_code = DBC_SUCCESS;
	unsigned int count_1;
	char         mddl_error_text[MDDL_MAX_ERROR_TEXT];

	*member_count = 0;
	*member_list  = NULL;

	if (structure_size != NULL)
		*structure_size = 0;

	if (!column_count) {
		strcpy(error_text, "No columns were specified.");
		return_code = DBC_FAILURE;
	}
	else if ((*member_list = ((MDDL *) calloc(column_count,
		sizeof(MDDL)))) == NULL) {
		STR_AllocMsgList(column_count, sizeof(MDDL), error_text,
			"Unable to allocate 'MDDL' list of columns");
		return_code = DBC_MEMORY_FAILURE;
	}
	else {
		*member_count = column_count;
		for (count_1 = 0; count_1 < column_count; count_1++) {
			MDDL_InitMember((*member_list) + count_1);
			nstrcpy((*member_list)[count_1].name,
				column_list[count_1].name,
				sizeof((*member_list)[count_1].name) - 1);
			nstrcpy((*member_list)[count_1].type_spec,
				column_list[count_1].type_spec,
				sizeof((*member_list)[count_1].type_spec) - 1);
			(*member_list)[count_1].data_length    =
				column_list[count_1].length;
			(*member_list)[count_1].length         =
				column_list[count_1].length;
			(*member_list)[count_1].offset          = 0;
			(*member_list)[count_1].type_count      =
				column_list[count_1].type_count;
			(*member_list)[count_1].align_count     = 0;
			(*member_list)[count_1].display_length  = 0;
			(*member_list)[count_1].display_name    = NULL;
			(*member_list)[count_1].dbc_type        =
				column_list[count_1].type;
			(*member_list)[count_1].length_function = DBC_MSSQL_SetDisplayLength;
			(*member_list)[count_1].dump_function   = DBC_MSSQL_DumpField;
			(*member_list)[count_1].user_int_1      = 0;
			(*member_list)[count_1].user_int_2      = 0;
			(*member_list)[count_1].user_ptr_1      = NULL;
			(*member_list)[count_1].user_ptr_2      = NULL;
		}
		if ((return_code = MDDL_FixAlignArrayList(0, NULL, *member_count,
			*member_list, structure_size, mddl_error_text)) != MDDL_SUCCESS) {
			MDDL_FreeMemberList(member_count, member_list);
			sprintf(error_text, "Unable to construct column '%-.100s': %-.500s",
				column_list[count_1].name, mddl_error_text);
			return_code = DBC_MAP_ERROR_MDDL(return_code);
		}
	}

	return(return_code);
}
/* *********************************************************************** */

