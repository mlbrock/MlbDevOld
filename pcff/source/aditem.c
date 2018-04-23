/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Adds an item to a configuration.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2018.
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

#include "pcffi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
int PCFF_AddItem(PCFF_CFG *cfg_ptr, PCFF_FLAG flags, const char *file_name,
	unsigned int line_number, const char *name, const char *value,
	char *error_text)
{
	int          return_code;
	unsigned int found_index;
	PCFF_ITEM    tmp_item_1;
	PCFF_ITEM    tmp_item_2;
	char         tmp_error_text[PCFF_MAX_ERROR_TEXT];

	PCFF_InitItem(&tmp_item_2);

	if (PCFF_FindItem(cfg_ptr, name, &found_index) != NULL) {
		tmp_item_1       = cfg_ptr->item_list[found_index];
		tmp_item_1.value = ((char *) value);
		if ((return_code = PCFF_CopyItem(&tmp_item_1, &tmp_item_2,
			tmp_error_text)) == PCFF_SUCCESS) {
			if ((return_code = PCFF_AddItemSrc(&tmp_item_2, flags, file_name,
				line_number, value, tmp_error_text)) == PCFF_SUCCESS) {
				PCFF_FreeItem(cfg_ptr->item_list + found_index);
				cfg_ptr->item_list[found_index] = tmp_item_2;
			}
		}
	}
	else {
		PCFF_InitItem(&tmp_item_1);
		tmp_item_1.name  = ((char *) name);
		tmp_item_1.value = ((char *) value);
		if ((return_code = PCFF_CopyItem(&tmp_item_1, &tmp_item_2,
			tmp_error_text)) == PCFF_SUCCESS) {
			if ((return_code = PCFF_AddItemSrc(&tmp_item_2, flags, file_name,
				line_number, value, tmp_error_text)) == PCFF_SUCCESS) {
				tmp_item_2.order = cfg_ptr->item_count;
				if ((return_code = mema_insert(&cfg_ptr->item_count,
					((void **) &cfg_ptr->item_list), &tmp_item_2,
					sizeof(*cfg_ptr->item_list), found_index)) != STRFUNCS_SUCCESS)
					STR_AllocMsgList(cfg_ptr->item_count + 1,
						sizeof(*cfg_ptr->item_list), tmp_error_text,
						"Unable to allocate memory for a new item");
				return_code = PCFF_MAP_ERROR_STR(return_code);
			}
		}
	}

	if (return_code != PCFF_SUCCESS) {
		PCFF_FreeItem(&tmp_item_2);
		strcat(strcpy(error_text, "Unable to add a new item: "),
			tmp_error_text);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_AddItemSrc(PCFF_ITEM *item_ptr, PCFF_FLAG flags,
	const char *file_name, unsigned int line_number, const char *value,
	char *error_text)
{
	int      return_code;
	PCFF_SRC tmp_src_1;
	PCFF_SRC tmp_src_2;
	char     tmp_error_text[PCFF_MAX_ERROR_TEXT];

	PCFF_InitSrc(&tmp_src_1);

	tmp_src_1.line_number = line_number;
	tmp_src_1.file_name   = ((char *) file_name);
	tmp_src_1.value       = ((char *) value);

	if ((return_code = PCFF_CopySrc(&tmp_src_1, &tmp_src_2,
		tmp_error_text)) == PCFF_SUCCESS) {
		if ((flags & PCFF_FLAG_NO_SRC_DEPTH) && item_ptr->src_count) {
			PCFF_FreeSrc(item_ptr->src_list);
			item_ptr->src_list[0] = tmp_src_2;
		}
		else if ((return_code = mema_insert(&item_ptr->src_count,
			((void **) &item_ptr->src_list), &tmp_src_2,
			sizeof(*item_ptr->src_list), 0)) != STRFUNCS_SUCCESS) {
			PCFF_FreeSrc(&tmp_src_2);
			STR_AllocMsgList(item_ptr->src_count + 1, sizeof(*item_ptr->src_list),
				tmp_error_text, "Unable to allocate memory for a new item source");
			return_code = PCFF_MAP_ERROR_STR(return_code);
		}
	}

	if (return_code != PCFF_SUCCESS)
		strcat(strcpy(error_text, "Unable to add a new item source: "),
			tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */


