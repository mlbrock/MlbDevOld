/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1994-03-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_FIND_COLUMN_NAME(column_name_count, column_name_list,
	column_name, found_index)
unsigned int           column_name_count;
const DCR_COLUMN_NAME *column_name_list;
const char            *column_name;
unsigned int          *found_index;
{
	unsigned int           tmp_found_index;
	unsigned int          *tmp_found_index_ptr;
	DCR_COLUMN_NAME  tmp_column_name;

	tmp_found_index_ptr = (found_index == NULL) ? &tmp_found_index :
		found_index;

	nstrcpy(tmp_column_name.column_name, column_name,
		sizeof(tmp_column_name.column_name) - 1);

#ifndef NARGS
	return(STR_ARRAY_bsearch(NULL, column_name_count, column_name_list,
		&tmp_column_name, sizeof(tmp_column_name), tmp_found_index_ptr,
		STRFUNCS_DIRECTION_TOP,
		((int (*)(void *, const void *, const void *, size_t))
		DCR_CMP_COLUMN_NAME)));
#else
	return(STR_ARRAY_bsearch(NULL, column_name_count, column_name_list,
		&tmp_column_name, sizeof(tmp_column_name), tmp_found_index_ptr,
		STRFUNCS_DIRECTION_TOP, DCR_CMP_COLUMN_NAME)));
#endif /* #ifndef NARGS */
}
/*	***********************************************************************	*/

