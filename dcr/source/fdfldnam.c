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

		Copyright Michael L. Brock 1994 - 2014.
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

int DCR_FIND_FIELD_NAME(field_name_count, field_name_list, field_name,
	found_index)
unsigned int          field_name_count;
const DCR_FIELD_NAME *field_name_list;
const char           *field_name;
unsigned int         *found_index;
{
	unsigned int          tmp_found_index;
	unsigned int         *tmp_found_index_ptr;
	DCR_FIELD_NAME  tmp_field_name;

	tmp_found_index_ptr = (found_index == NULL) ? &tmp_found_index :
		found_index;

	nstrcpy(tmp_field_name.field_name, field_name,
		sizeof(tmp_field_name.field_name) - 1);

#ifndef NARGS
	return(STR_ARRAY_bsearch(NULL, field_name_count, field_name_list,
		&tmp_field_name, sizeof(tmp_field_name), tmp_found_index_ptr,
		STRFUNCS_DIRECTION_TOP,
		((int (*)(void *, const void *, const void *, size_t))
		DCR_CMP_FIELD_NAME)));
#else
	return(STR_ARRAY_bsearch(NULL, field_name_count, field_name_list,
		&tmp_field_name, sizeof(tmp_field_name), tmp_found_index_ptr,
		STRFUNCS_DIRECTION_TOP, DCR_CMP_FIELD_NAME)));
#endif /* #ifndef NARGS */
}
/*	***********************************************************************	*/

