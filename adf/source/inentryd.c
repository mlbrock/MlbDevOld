/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support the initialization of
								'ADF_ENTRY_DATA' structures.

	Revision History	:	1996-04-15 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_INIT_AreaDataList(ADF_ENTRY_DATA *entry_data_list)
#else
void ADF_INIT_AreaDataList(entry_data_list)
ADF_ENTRY_DATA *entry_data_list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++)
		ADF_INIT_AreaData(entry_data_list + count_1);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_INIT_AreaData(ADF_ENTRY_DATA *entry_data_ptr)
#else
void ADF_INIT_AreaData(entry_data_ptr)
ADF_ENTRY_DATA *entry_data_ptr;
#endif /* #ifndef NARGS */
{
	memset(entry_data_ptr, '\0', sizeof(*entry_data_ptr));

	entry_data_ptr->area_index    = 0;
	entry_data_ptr->section_order = 0;
	entry_data_ptr->actual_order  = 0;
	entry_data_ptr->section_name  = NULL;
	entry_data_ptr->para_count    = 0;
	entry_data_ptr->para_list     = NULL;
}
/*	***********************************************************************	*/

