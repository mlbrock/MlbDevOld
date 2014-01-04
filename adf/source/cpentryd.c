/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support the copying of 'ADF_ENTRY_DATA'
								structures.

	Revision History	:	1996-04-15 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
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
int ADF_COPY_EntryDataList(const ADF_ENTRY_DATA *in_entry_data_list,
	ADF_ENTRY_DATA *out_entry_data_list, char *error_text)
#else
int ADF_COPY_EntryDataList(in_entry_data_list, out_entry_data_list,
	error_text)
const ADF_ENTRY_DATA *in_entry_data_list;
ADF_ENTRY_DATA       *out_entry_data_list;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;

	ADF_INIT_AreaDataList(out_entry_data_list);

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		if ((return_code = ADF_COPY_EntryData(in_entry_data_list + count_1,
			out_entry_data_list + count_1, error_text)) != ADF_SUCCESS)
			break;
	}

	if (return_code != ADF_SUCCESS)
		ADF_FREE_AreaDataList(out_entry_data_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_COPY_EntryData(const ADF_ENTRY_DATA *in_entry_data_ptr,
	ADF_ENTRY_DATA *out_entry_data_ptr, char *error_text)
#else
int ADF_COPY_EntryData(in_entry_data_ptr, out_entry_data_ptr, error_text)
const ADF_ENTRY_DATA *in_entry_data_ptr;
ADF_ENTRY_DATA       *out_entry_data_ptr;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	ADF_INIT_AreaData(out_entry_data_ptr);

	out_entry_data_ptr->area_index    = in_entry_data_ptr->area_index;
	out_entry_data_ptr->section_order = in_entry_data_ptr->section_order;
	out_entry_data_ptr->actual_order  = in_entry_data_ptr->actual_order;

	if ((in_entry_data_ptr->section_name != NULL) &&
		((out_entry_data_ptr->section_name =
		strdup(in_entry_data_ptr->section_name)) == NULL)) {
		STR_AllocMsgItem(strlen(in_entry_data_ptr->section_name) + 1,
			error_text, "Unable to copy an ADF entry area section name");
		return_code = ADF_MEMORY_FAILURE;
	}
	else if ((return_code =
		ADF_COPY_ParaDataList(in_entry_data_ptr->para_count,
		in_entry_data_ptr->para_list, &out_entry_data_ptr->para_count,
		&out_entry_data_ptr->para_list, error_text)) != ADF_SUCCESS)
		ADF_FREE_AreaData(out_entry_data_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

