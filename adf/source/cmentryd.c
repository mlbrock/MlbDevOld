/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support the comparison of 'ADF_ENTRY_DATA'
								structures.

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

#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_CMP_EntryDataList(const ADF_ENTRY_DATA *entry_data_list_1,
	const ADF_ENTRY_DATA *entry_data_list_2, unsigned int *diff_area_index,
	unsigned int *diff_para_index)
#else
int ADF_CMP_EntryDataList(entry_data_list_1, entry_data_list_2,
	diff_area_index, diff_para_index)
const ADF_ENTRY_DATA *entry_data_list_1;
const ADF_ENTRY_DATA *entry_data_list_2;
unsigned int         *diff_area_index;
unsigned int         *diff_para_index;
#endif /* #ifndef NARGS */
{
	int          cmp_code = 0;
	unsigned int count_1;

	if (diff_area_index != NULL)
		*diff_area_index = 0;
	if (diff_para_index != NULL)
		*diff_para_index = 0;

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		if ((cmp_code = ADF_CMP_EntryData(entry_data_list_1 + count_1,
			entry_data_list_2 + count_1, diff_para_index)) != 0) {
			if (diff_area_index != NULL)
				*diff_area_index = count_1;
			break;
		}
	}

	return(cmp_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_CMP_EntryData(const ADF_ENTRY_DATA *entry_data_ptr_1,
	const ADF_ENTRY_DATA *entry_data_ptr_2, unsigned int *diff_para_index)
#else
int ADF_CMP_EntryData(entry_data_ptr_1, entry_data_ptr_2, diff_para_index)
const ADF_ENTRY_DATA *entry_data_ptr_1;
const ADF_ENTRY_DATA *entry_data_ptr_2;
unsigned int         *diff_para_index;
#endif /* #ifndef NARGS */
{
	int          cmp_code = 0;
	unsigned int count_1;

	if (entry_data_ptr_1->para_count != entry_data_ptr_2->para_count) {
		if (diff_para_index != NULL)
			*diff_para_index = UINT_MAX;
		cmp_code =
			(entry_data_ptr_1->para_count > entry_data_ptr_2->para_count) ?
			1 : -1;
	}
	else {
		if (diff_para_index != NULL)
			*diff_para_index = 0;
		for (count_1 = 0; count_1 < entry_data_ptr_1->para_count; count_1++) {
			if ((cmp_code = strcmp(entry_data_ptr_1->para_list[count_1].text_ptr,
				entry_data_ptr_2->para_list[count_1].text_ptr)) != 0) {
				if (diff_para_index != NULL)
					*diff_para_index = count_1;
				break;
			}
		}
	}

	return(cmp_code);
}
/*	***********************************************************************	*/

