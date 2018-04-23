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

	Revision History	:	1994-06-04 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
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

void DCR_GetAreaListOffset(area_list_offset)
unsigned int *area_list_offset;
{
	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*	**************************************************************	*/
	area_list_offset[DCR_AREA_FIELD]        =
		offsetof(DCR_CACHE, field_list);
	area_list_offset[DCR_AREA_FIELD_NAME]   =
		offsetof(DCR_CACHE, field_name_list);
	area_list_offset[DCR_AREA_COLUMN_NAME]  =
		offsetof(DCR_CACHE, column_name_list);
	area_list_offset[DCR_AREA_FIELD_ALIGN]  =
		offsetof(DCR_CACHE, field_align_list);
	area_list_offset[DCR_AREA_INDEX]        =
		offsetof(DCR_CACHE, index_list);
	area_list_offset[DCR_AREA_INDEX_NAME]   =
		offsetof(DCR_CACHE, index_name_list);
	area_list_offset[DCR_AREA_INDEX_FIELD]  =
		offsetof(DCR_CACHE, index_field_list);
	area_list_offset[DCR_AREA_INDEX_ALIGN]  =
		offsetof(DCR_CACHE, index_align_list);
	/*	**************************************************************	*/
}
/*	***********************************************************************	*/

