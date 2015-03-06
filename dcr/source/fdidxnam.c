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

	Revision History	:	1994-06-11 --- Creation.
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

int DCR_FIND_INDEX_NAME(index_name_count, index_name_list, index_name,
	found_index)
unsigned int          index_name_count;
const DCR_INDEX_NAME *index_name_list;
const char           *index_name;
unsigned int         *found_index;
{
	unsigned int          tmp_found_index;
	unsigned int         *tmp_found_index_ptr;
	DCR_INDEX_NAME  tmp_index_name;

	tmp_found_index_ptr = (found_index == NULL) ? &tmp_found_index :
		found_index;

	nstrcpy(tmp_index_name.index_name, index_name,
		sizeof(tmp_index_name.index_name) - 1);

#ifndef NARGS
	return(STR_ARRAY_bsearch(NULL, index_name_count, index_name_list,
		&tmp_index_name, sizeof(tmp_index_name), tmp_found_index_ptr,
		STRFUNCS_DIRECTION_TOP,
		((int (*)(void *, const void *, const void *, size_t))
		DCR_CMP_INDEX_NAME)));
#else
	return(STR_ARRAY_bsearch(NULL, index_name_count, index_name_list,
		&tmp_index_name, sizeof(tmp_index_name), tmp_found_index_ptr,
		STRFUNCS_DIRECTION_TOP, DCR_CMP_INDEX_NAME)));
#endif /* #ifndef NARGS */
}
/*	***********************************************************************	*/

