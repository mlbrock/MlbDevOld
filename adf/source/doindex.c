/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support the creation of an index list.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
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
#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int              ADF_BuildListControl,
	(ADF_CONTROL *control_ptr,
	unsigned int area_index, unsigned int *index_item_count,
	ADF_INDEX_ITEM **index_item_list, char *error_text));
COMPAT_FN_DECL_STATIC(int              ADF_BuildListItems,
	(ADF_CONTROL *control_ptr,
	unsigned int area_index, const ADF_ENTRY *entry_ptr,
	const ADF_ENTRY_DATA *entry_data_ptr, unsigned int *index_item_count,
	ADF_INDEX_ITEM **index_item_list, char *error_text));
COMPAT_FN_DECL_STATIC(void             ADF_CheckIndexItems,
	(ADF_CONTROL *control_ptr,
	unsigned int index_item_count, ADF_INDEX_ITEM *index_item_list));
COMPAT_FN_DECL_STATIC(void             ADF_InitIndexItem,
	(ADF_INDEX_ITEM *index_item_ptr));
COMPAT_FN_DECL_STATIC(ADF_INDEX_ITEM  *ADF_SEARCH_IndexItem,
	(unsigned int *index_item_count,
	ADF_INDEX_ITEM **index_item_list, const char *item_name,
	const ADF_ENTRY *entry_ptr, unsigned int htext_index));
COMPAT_FN_DECL_STATIC(int              ADF_SCMP_IndexItem,
	(void *control_ptr,
	const ADF_INDEX_ITEM *ptr_1, const ADF_INDEX_ITEM *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int              ADF_SCMP_IndexItemByOrder,
	(void *control_ptr,
	const ADF_INDEX_ITEM *ptr_1, const ADF_INDEX_ITEM *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int              ADF_SCMP_PermLinkList,
	(void *control_ptr,
	const unsigned int *ptr_1, const unsigned int *ptr_2, size_t data_length));
COMPAT_FN_DECL_STATIC(int              ADF_SCMP_PermIndex,
	(ADF_CONTROL *control_ptr,
	const ADF_PERM_INDEX *ptr_1, const ADF_PERM_INDEX *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int              ADF_SCMP_PermIndexDictOrder,
	(ADF_CONTROL *control_ptr,
	const ADF_PERM_INDEX *ptr_1, const ADF_PERM_INDEX *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int              ADF_SCMP_PermIndexRef,
	(ADF_CONTROL *control_ptr,
	const unsigned int *ptr_1, const unsigned int *ptr_2, size_t data_length));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeIndexItemList(unsigned int *index_item_count,
	ADF_INDEX_ITEM **index_item_list)
#else
void ADF_FreeIndexItemList(index_item_count, index_item_list)
unsigned int    *index_item_count;
ADF_INDEX_ITEM **index_item_list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < *index_item_count; count_1++)
		ADF_FreeIndexItem(*index_item_list + count_1);

	mema_remove_all(index_item_count, ((void **) index_item_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeIndexItem(ADF_INDEX_ITEM *index_item_ptr)
#else
void ADF_FreeIndexItem(index_item_ptr)
ADF_INDEX_ITEM *index_item_ptr;
#endif /* #ifndef NARGS */
{
	ADF_FreeIndexItemList(&index_item_ptr->index_item_count,
		&index_item_ptr->index_item_list);

	if (index_item_ptr->item_name != NULL)
		free(index_item_ptr->item_name);

	ADF_InitIndexItem(index_item_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreePermIndexList(unsigned int *index_item_count,
	ADF_PERM_INDEX **index_item_list)
#else
void ADF_FreePermIndexList(index_item_count, index_item_list)
unsigned int    *index_item_count;
ADF_PERM_INDEX **index_item_list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < *index_item_count; count_1++)
		ADF_FreePermIndex(*index_item_list + count_1);

	mema_remove_all(index_item_count, ((void **) index_item_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreePermIndex(ADF_PERM_INDEX *index_item_ptr)
#else
void ADF_FreePermIndex(index_item_ptr)
ADF_PERM_INDEX *index_item_ptr;
#endif /* #ifndef NARGS */
{
	if (index_item_ptr->ref_list != NULL)
		free(index_item_ptr->ref_list);

	index_item_ptr->ref_count = 0;
	index_item_ptr->ref_list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BuildIndexItemList(ADF_CONTROL *control_ptr,
	unsigned int *index_item_count, ADF_INDEX_ITEM **index_item_list,
	char *error_text)
#else
int ADF_BuildIndexItemList(control_ptr, index_item_count, index_item_list,
	error_text)
ADF_CONTROL     *control_ptr;
unsigned int    *index_item_count;
ADF_INDEX_ITEM **index_item_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(ADF_BuildListControl(control_ptr, ADF_AREA_OUTPUT_INDEX,
		index_item_count, index_item_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BuildClassTOCItemList(ADF_CONTROL *control_ptr,
	unsigned int *index_item_count, ADF_INDEX_ITEM **index_item_list,
	char *error_text)
#else
int ADF_BuildClassTOCItemList(control_ptr, index_item_count, index_item_list,
	error_text)
ADF_CONTROL     *control_ptr;
unsigned int    *index_item_count;
ADF_INDEX_ITEM **index_item_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(ADF_BuildListControl(control_ptr, ADF_AREA_ENTRY_CLASS_NAME,
		index_item_count, index_item_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BuildPermIndex(ADF_CONTROL *control_ptr,
	unsigned int *index_item_count, ADF_PERM_INDEX **index_item_list,
	char *error_text)
#else
int ADF_BuildPermIndex(control_ptr, index_item_count, index_item_list,
	error_text)
ADF_CONTROL     *control_ptr;
unsigned int    *index_item_count;
ADF_PERM_INDEX **index_item_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code  = ADF_SUCCESS;
	unsigned int    link_count_1 = 0;
	unsigned int   *link_list_1  = NULL;
	unsigned int    link_count_2 = 0;
	unsigned int   *link_list_2  = NULL;
	unsigned int    count_1;
	unsigned int    count_2;
	unsigned int    count_3;
	unsigned int    count_4;
	unsigned int    found_index;
	unsigned int    this_link_count;
   int             strfuncs_code;
	int             keep_bad_see_also_flag;
	unsigned int    para_count;
	ADF_PARA_TEXT  *para_line;
	ADF_PERM_INDEX  tmp_perm_index;
	ADF_ENTRY_DATA  entry_data_list[ADF_AREA_COUNT];

	*index_item_count = 0;
	*index_item_list  = NULL;

	memset(&tmp_perm_index, '\0', sizeof(tmp_perm_index));

	ADF_INIT_AreaDataList(entry_data_list);

	keep_bad_see_also_flag              = control_ptr->keep_bad_see_also_flag;
	control_ptr->keep_bad_see_also_flag = ADF_TRUE;

	for (count_1 = 0; count_1 < control_ptr->in_entry_count; count_1++) {
		if ((return_code = ADF_GetEntry(control_ptr,
			control_ptr->in_entry_list + count_1, entry_data_list,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		this_link_count = 0;
		for (count_2 = 0; count_2 < ADF_AREA_COUNT; count_2++) {
			for (count_3 = 0; count_3 < entry_data_list[count_2].para_count;
				count_3++) {
				if ((return_code = ADF_FixParagraph(control_ptr,
					control_ptr->in_entry_list + count_1,
					entry_data_list[count_2].para_list + count_3,
					ADF_HTML_CFORMAT_TYPE, error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				para_count = control_ptr->current_para_line_count;
				para_line  = control_ptr->in_para_line_list;
				for (count_4 = 0; count_4 < para_count; count_4++, para_line++) {
					if (para_line->cformat_type == ADF_CFORMAT_CHAR_HTEXT_1) {
						if (this_link_count < link_count_1)
							link_list_1[this_link_count++] =
								control_ptr->in_htext_list[para_line->htext_index].
								in_entry_index;
						else if (mema_append(&link_count_1, ((void **) &link_list_1),
							&control_ptr->in_htext_list[para_line->htext_index].
							in_entry_index, sizeof(*link_list_1)) !=
							STRFUNCS_SUCCESS) {
							STR_AllocMsgList(link_count_1 + 1, sizeof(unsigned int),
								error_text, "%s %s '%s' ",
								"Unable to allocate additional temporary permutated",
								"index element for the entry named",
								control_ptr->in_entry_list[count_1].base_name);
							return_code = ADF_MEMORY_FAILURE;
							goto EXIT_FUNCTION;
						}
						else
							this_link_count++;
					}
				}
			}
		}
		if (mema_copy(this_link_count, link_list_1, sizeof(*link_list_2),
			&link_count_2, ((void **) &link_list_2)) != STRFUNCS_SUCCESS) {
			STR_AllocMsgList(link_count_1, sizeof(unsigned int), error_text,
				"%s entry named '%s' ",
				"Unable to copy the temporary permutated index list for the",
				control_ptr->in_entry_list[count_1].base_name);
			return_code = ADF_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
#ifndef NARGS
		STR_ARRAY_qsort(NULL, link_count_2, link_list_2, sizeof(*link_list_2),
			((int (*)(void *, const void *, const void *, size_t))
			ADF_SCMP_PermLinkList));
		STR_ARRAY_uniq(NULL, &link_count_2, ((void **) &link_list_2),
			sizeof(*link_list_2),
			((int (*)(void *, const void *, const void *, size_t))
			ADF_SCMP_PermLinkList));
#else
		STR_ARRAY_qsort(NULL, link_count_2, link_list_2, sizeof(*link_list_2),
			ADF_SCMP_PermLinkList);
		STR_ARRAY_uniq(NULL, &link_count_2, &link_list_2, sizeof(*link_list_2),
			ADF_SCMP_PermLinkList);
#endif /* #ifndef NARGS */
		for (count_2 = 0; count_2 < link_count_2; count_2++) {
			tmp_perm_index.entry_index = link_list_2[count_2];
			tmp_perm_index.ref_count   = 0;
			tmp_perm_index.ref_list    = NULL;
#ifndef NARGS
			strfuncs_code = STR_ARRAY_bsearch(control_ptr, *index_item_count,
				*index_item_list, &tmp_perm_index,
				sizeof(**index_item_list), &found_index, STRFUNCS_DIRECTION_TOP,
				((int (*)(void *, const void *, const void *, size_t))
				ADF_SCMP_PermIndex));
#else
			strfuncs_code = STR_ARRAY_search(control_ptr, *index_item_count,
				index_item_list, &tmp_perm_index,
				sizeof(**index_item_list), &found_index, STRFUNCS_DIRECTION_TOP,
				ADF_SCMP_PermIndex);
#endif /* #ifndef NARGS */
			if ((strfuncs_code == STRFUNCS_ITEM_NOT_FOUND) &&
				(mema_insert(index_item_count, ((void **) index_item_list),
				&tmp_perm_index, sizeof(tmp_perm_index), found_index) !=
				STRFUNCS_SUCCESS)) {
				strcpy(error_text, "Unable to append a permutated index item.");
				return_code = ADF_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			if (mema_append(&(*index_item_list)[found_index].ref_count,
				((void **) &(*index_item_list)[found_index].ref_list), &count_1,
				sizeof(unsigned int)) != STRFUNCS_SUCCESS) {
				strcpy(error_text,
					"Unable to append a permutated index reference.");
				return_code = ADF_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
		mema_remove_all(&link_count_2, ((void **) &link_list_2));
		ADF_INIT_AreaDataList(entry_data_list);
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Set dictionary ordering and sort by it . . .							*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < *index_item_count; count_1++)
		(*index_item_list)[count_1].item_order =
			ADF_DICT_ORDER_CHAR(*control_ptr->in_entry_list
				[(*index_item_list)[count_1].entry_index].base_name);
#ifndef NARGS
	STR_ARRAY_qsort(control_ptr, *index_item_count, *index_item_list,
		sizeof(**index_item_list),
		((int (*)(void *, const void *, const void *, size_t))
		ADF_SCMP_PermIndexDictOrder));
#else
	STR_ARRAY_qsort(control_ptr, *index_item_count, *index_item_list,
		sizeof(**index_item_list), ADF_SCMP_PermIndexDictOrder);
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < *index_item_count; count_1++) {
#ifndef NARGS
		STR_ARRAY_qsort(control_ptr, (*index_item_list)[count_1].ref_count,
			(*index_item_list)[count_1].ref_list, sizeof(unsigned int),
			((int (*)(void *, const void *, const void *, size_t))
			ADF_SCMP_PermIndexRef));
#else
		STR_ARRAY_qsort(control_ptr, (*index_item_list)[count_1].ref_count,
			(*index_item_list)[count_1].ref_list, sizeof(unsigned int),
			ADF_SCMP_PermIndexRef);
#endif /* #ifndef NARGS */
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	control_ptr->keep_bad_see_also_flag = keep_bad_see_also_flag;

	if (return_code != ADF_SUCCESS)
		ADF_FreePermIndexList(index_item_count, index_item_list);

	mema_remove_all(&link_count_1, ((void **) &link_list_1));
	mema_remove_all(&link_count_2, ((void **) &link_list_2));

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_BuildListControl(ADF_CONTROL *control_ptr,
	unsigned int area_index, unsigned int *index_item_count,
	ADF_INDEX_ITEM **index_item_list, char *error_text)
#else
static int ADF_BuildListControl(control_ptr, area_index, index_item_count,
	index_item_list, error_text)
ADF_CONTROL     *control_ptr;
unsigned int     area_index;
unsigned int    *index_item_count;
ADF_INDEX_ITEM **index_item_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	unsigned int   count_1;
	ADF_ENTRY_DATA entry_data_list[ADF_AREA_COUNT];

	*index_item_count = 0;
	*index_item_list  = NULL;

	for (count_1 = 0; count_1 < control_ptr->in_entry_order_count; count_1++) {
		if ((return_code = ADF_GetEntry(control_ptr,
			control_ptr->in_entry_order_list[count_1], entry_data_list,
			error_text)) != ADF_SUCCESS)
			break;
		if (entry_data_list[area_index].para_count && ((return_code =
			ADF_BuildListItems(control_ptr, area_index,
			control_ptr->in_entry_order_list[count_1],
			entry_data_list + area_index, index_item_count, index_item_list,
			error_text)) != ADF_SUCCESS))
			break;
	}

	if (return_code == ADF_SUCCESS) {
		if (control_ptr->log_flag == ADF_TRUE)
			ADF_CheckIndexItems(control_ptr, *index_item_count,
				*index_item_list);
		for (count_1 = 0; count_1 < *index_item_count; count_1++)
			(*index_item_list)[count_1].item_order =
				ADF_DICT_ORDER_CHAR(*(*index_item_list)[count_1].item_name);
#ifndef NARGS
		STR_ARRAY_qsort(NULL, *index_item_count, *index_item_list,
			sizeof(**index_item_list),
			((int (*)(void *, const void *, const void *, size_t))
			ADF_SCMP_IndexItemByOrder));
#else
		STR_ARRAY_qsort(NULL, *index_item_count, *index_item_list,
			sizeof(**index_item_list), ADF_SCMP_IndexItemByOrder);
#endif /* #ifndef NARGS */
	}
	else
		ADF_FreeIndexItemList(index_item_count, index_item_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_BuildListItems(ADF_CONTROL *control_ptr,
	unsigned int area_index, const ADF_ENTRY *entry_ptr,
	const ADF_ENTRY_DATA *entry_data_ptr, unsigned int *index_item_count,
	ADF_INDEX_ITEM **index_item_list, char *error_text)
#else
static int ADF_BuildListItems(control_ptr, area_index, entry_ptr,
	entry_data_ptr, index_item_count, index_item_list, error_text)
ADF_CONTROL           *control_ptr;
unsigned int           area_index;
const ADF_ENTRY       *entry_ptr;
const ADF_ENTRY_DATA  *entry_data_ptr;
unsigned int          *index_item_count;
ADF_INDEX_ITEM       **index_item_list;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code = ADF_SUCCESS;
	unsigned int     tmp_count   = 0;
	char           **tmp_list    = NULL;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     found_index;
	unsigned int    *index_item_count_ptr;
	ADF_INDEX_ITEM **index_item_list_ptr;
	ADF_INDEX_ITEM  *tmp_index_item_ptr;

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		if (sepwordx(entry_data_ptr->para_list[count_1].text_ptr, ":",
			&tmp_count, &tmp_list) != STRFUNCS_SUCCESS) {
			strcpy(error_text, "Unable to create the temporary entry list.");
			return_code = ADF_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		index_item_count_ptr = index_item_count;
		index_item_list_ptr  = index_item_list;
		for (count_2 = 0; count_2 < tmp_count; count_2++) {
			if ((tmp_index_item_ptr = ADF_SEARCH_IndexItem(index_item_count_ptr,
				index_item_list_ptr, tmp_list[count_2], NULL, 0)) == NULL) {
				strcpy(error_text, "Unable to add to the entry tree.");
				return_code = ADF_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			if ((area_index == ADF_AREA_ENTRY_CLASS_NAME) ||
				(count_2 < (tmp_count - 1))) {
				index_item_count_ptr = &tmp_index_item_ptr->index_item_count;
				index_item_list_ptr  = &tmp_index_item_ptr->index_item_list;
			}
			else if ((ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
				control_ptr->in_htext_list, tmp_list[count_2], &found_index) ==
				STRFUNCS_ITEM_FOUND) && (entry_ptr->file_index ==
				control_ptr->in_htext_list[found_index].file_index) &&
				(entry_ptr->entry_index ==
				control_ptr->in_htext_list[found_index].entry_index) &&
				(ADF_SEARCH_IndexItem(index_item_count_ptr, index_item_list_ptr,
				tmp_list[count_2], entry_ptr, found_index) == NULL)) {
				strcpy(error_text, "Unable to add to the output index tree.");
				return_code = ADF_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
		if (area_index == ADF_AREA_ENTRY_CLASS_NAME) {
			if ((ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
				control_ptr->in_htext_list, entry_ptr->base_name, &found_index) ==
				STRFUNCS_ITEM_FOUND) && (entry_ptr->file_index ==
				control_ptr->in_htext_list[found_index].file_index) &&
				(entry_ptr->entry_index ==
				control_ptr->in_htext_list[found_index].entry_index) &&
				(ADF_SEARCH_IndexItem(index_item_count_ptr, index_item_list_ptr,
				entry_ptr->base_name, entry_ptr, found_index) == NULL)) {
				strcpy(error_text, "Unable to add to the entry class tree.");
				return_code = ADF_MEMORY_FAILURE;
				break;
			}
		}
		strl_remove_all(&tmp_count, &tmp_list);
	}

EXIT_FUNCTION:

	strl_remove_all(&tmp_count, &tmp_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_CheckIndexItems(ADF_CONTROL *control_ptr,
	unsigned int index_item_count, ADF_INDEX_ITEM *index_item_list)
#else
static void ADF_CheckIndexItems(control_ptr, index_item_count, index_item_list)
ADF_CONTROL    *control_ptr;
unsigned int    index_item_count;
ADF_INDEX_ITEM *index_item_list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < index_item_count; count_1++) {
		if ((!index_item_list[count_1].index_item_count) &&
			(index_item_list[count_1].entry_ptr == NULL))
			MLOG_LogWarn(control_ptr->mlog_ptr,
				"Dangling index entry encountered '%s'\n",
				index_item_list[count_1].item_name);
		else {
			if (index_item_list[count_1].index_item_count)
				ADF_CheckIndexItems(control_ptr,
					index_item_list[count_1].index_item_count,
					index_item_list[count_1].index_item_list);
			count_1++;
		}
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_InitIndexItem(ADF_INDEX_ITEM *index_item_ptr)
#else
static void ADF_InitIndexItem(index_item_ptr)
ADF_INDEX_ITEM *index_item_ptr;
#endif /* #ifndef NARGS */
{
	memset(index_item_ptr, '\0', sizeof(*index_item_ptr));

	index_item_ptr->item_order       = '\0';
	index_item_ptr->item_name        = NULL;
	index_item_ptr->entry_flag       = ADF_FALSE;
	index_item_ptr->index_item_count = 0;
	index_item_ptr->index_item_list  = NULL;
	index_item_ptr->entry_ptr        = NULL;
	index_item_ptr->htext_index      = 0;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static ADF_INDEX_ITEM *ADF_SEARCH_IndexItem(unsigned int *index_item_count,
	ADF_INDEX_ITEM **index_item_list, const char *item_name,
	const ADF_ENTRY *entry_ptr, unsigned int htext_index)
#else
static ADF_INDEX_ITEM *ADF_SEARCH_IndexItem(index_item_count, index_item_list,
	item_name, entry_ptr, htext_index)
unsigned int     *index_item_count;
ADF_INDEX_ITEM  **index_item_list;
const char       *item_name;
const ADF_ENTRY  *entry_ptr;
unsigned int      htext_index;
#endif /* #ifndef NARGS */
{
	ADF_INDEX_ITEM *return_ptr = NULL;
	ADF_INDEX_ITEM  tmp_item;
	unsigned int    found_index;

	ADF_InitIndexItem(&tmp_item);

	tmp_item.item_name   = ((char *) item_name);
	tmp_item.entry_flag  = (entry_ptr != NULL) ? ADF_TRUE    : ADF_FALSE;
	tmp_item.htext_index = (entry_ptr != NULL) ? htext_index : 0;

#ifndef NARGS
	if (STR_ARRAY_search(index_item_count, ((void **) index_item_list),
		&tmp_item, sizeof(tmp_item), &found_index,
		((int (*)(void *, const void *, const void *, size_t))
		ADF_SCMP_IndexItem), mema_insert) != STRFUNCS_FAILURE) {
#else
	if (STR_ARRAY_search(index_item_count, ((void **) index_item_list),
		&tmp_item, sizeof(tmp_item), &found_index, ADF_SCMP_IndexItem,
		mema_insert) != STRFUNCS_FAILURE) {
#endif /* #ifndef NARGS */
		if ((*index_item_list)[found_index].item_name != item_name) {
			return_ptr = *index_item_list + found_index;
			if ((return_ptr->entry_flag != ADF_TRUE) && (entry_ptr != NULL)) {
				return_ptr->entry_flag  = ADF_TRUE;
				return_ptr->entry_ptr   = entry_ptr;
				return_ptr->htext_index = htext_index;
			}
		}
		else if (((*index_item_list)[found_index].item_name =
			strdup(item_name)) != NULL) {
			return_ptr = *index_item_list + found_index;
			if ((return_ptr->entry_flag == ADF_TRUE) &&
				(return_ptr->entry_ptr == NULL) && (entry_ptr != NULL))
				return_ptr->entry_ptr   = entry_ptr;
		}
		else
			mema_remove(index_item_count, ((void **) index_item_list),
				sizeof(**index_item_list), found_index, 1);
	}

	return(return_ptr);
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_IndexItem(void *control_ptr, const ADF_INDEX_ITEM *ptr_1,
	const ADF_INDEX_ITEM *ptr_2, size_t data_length)
#else
static int ADF_SCMP_IndexItem(control_ptr, ptr_1, ptr_2, data_length)
void                 *control_ptr;
const ADF_INDEX_ITEM *ptr_1;
const ADF_INDEX_ITEM *ptr_2;
size_t                data_length;
#endif /* #ifndef NARGS */
{
	return(stricmp(ptr_1->item_name, ptr_2->item_name));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_IndexItemByOrder(void *control_ptr,
	const ADF_INDEX_ITEM *ptr_1, const ADF_INDEX_ITEM *ptr_2, size_t data_length)
#else
static int ADF_SCMP_IndexItemByOrder(control_ptr, ptr_1, ptr_2, data_length)
void                 *control_ptr;
const ADF_INDEX_ITEM *ptr_1;
const ADF_INDEX_ITEM *ptr_2;
size_t                data_length;
#endif /* #ifndef NARGS */
{
	return((ptr_1->item_order > ptr_2->item_order) ? 1 :
		(ptr_1->item_order < ptr_2->item_order) ? -1 :
		stricmp(ptr_1->item_name, ptr_2->item_name));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_PermLinkList(void *control_ptr, const unsigned int *ptr_1,
	const unsigned int *ptr_2, size_t data_length)
#else
static int ADF_SCMP_PermLinkList(control_ptr, ptr_1, ptr_2, data_length)
void               *control_ptr;
const unsigned int *ptr_1;
const unsigned int *ptr_2;
size_t              data_length;
#endif /* #ifndef NARGS */
{
	return((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_PermIndex(ADF_CONTROL *control_ptr,
	const ADF_PERM_INDEX *ptr_1, const ADF_PERM_INDEX *ptr_2,
	size_t data_length)
#else
static int ADF_SCMP_PermIndex(control_ptr, ptr_1, ptr_2, data_length)
ADF_CONTROL          *control_ptr;
const ADF_PERM_INDEX *ptr_1;
const ADF_PERM_INDEX *ptr_2;
size_t                data_length;
#endif /* #ifndef NARGS */
{
	return(strcmp(control_ptr->in_entry_list[ptr_1->entry_index].base_name,
		control_ptr->in_entry_list[ptr_2->entry_index].base_name));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_PermIndexDictOrder(ADF_CONTROL *control_ptr,
	const ADF_PERM_INDEX *ptr_1, const ADF_PERM_INDEX *ptr_2,
	size_t data_length)
#else
static int ADF_SCMP_PermIndexDictOrder(control_ptr, ptr_1, ptr_2, data_length)
ADF_CONTROL          *control_ptr;
const ADF_PERM_INDEX *ptr_1;
const ADF_PERM_INDEX *ptr_2;
size_t                data_length;
#endif /* #ifndef NARGS */
{
	return((ptr_1->item_order > ptr_2->item_order) ? 1 :
		(ptr_1->item_order < ptr_2->item_order) ? -1 :
		strcmp(control_ptr->in_entry_list[ptr_1->entry_index].base_name,
		control_ptr->in_entry_list[ptr_2->entry_index].base_name));
/*
	int cmp;

	if (!(cmp = ((ptr_1->item_order > ptr_2->item_order) ? 1 :
		(ptr_1->item_order < ptr_2->item_order) ? -1 : 0)))
		cmp = strcmp(control_ptr->in_entry_list[ptr_1->entry_index].base_name,
			control_ptr->in_entry_list[ptr_2->entry_index].base_name);

	return(cmp);
*/
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_PermIndexRef(ADF_CONTROL *control_ptr,
	const unsigned int *ptr_1, const unsigned int *ptr_2, size_t data_length)
#else
static int ADF_SCMP_PermIndexRef(control_ptr, ptr_1, ptr_2, data_length)
ADF_CONTROL        *control_ptr;
const unsigned int *ptr_1;
const unsigned int *ptr_2;
size_t              data_length;
#endif /* #ifndef NARGS */
{
	return(strcmp(control_ptr->in_entry_list[*ptr_1].base_name,
		control_ptr->in_entry_list[*ptr_2].base_name));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef TEST_MAIN

#include <memory.h>

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(void TEST_EmitIndexList,
	(unsigned int index_item_count,
	const ADF_INDEX_ITEM *index_item_list, unsigned int indent));
COMPAT_FN_DECL_STATIC(void TEST_EmitPermIndexList,
	(const ADF_CONTROL *control_ptr,
	unsigned int index_item_count, const ADF_PERM_INDEX *index_item_list));


#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int             return_code = ADF_SUCCESS;
	unsigned int    count_1;
	ADF_CONTROL     control_data;
	unsigned int    index_item_count;
	ADF_INDEX_ITEM *index_item_list;
	unsigned int    perm_index_count;
	ADF_PERM_INDEX *perm_index_list;
	char            error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'ADF_BuildIndexItemList()'\n");
	fprintf(stderr, "---- ------- --- --------------------------\n\n");

	ADF_INIT_Control(&control_data);

	control_data.cont_on_error_flag = ADF_TRUE;
	control_data.area_name_type     = ADF_AREA_NAME_TYPE_INTERNAL;
	control_data.area_order_type    = ADF_AREA_ORDER_TYPE_INTERNAL;

	if (argc < 2) {
		sprintf(error_text, "Invalid command line encountered.");
		fprintf(stderr,
			"USAGE:\n   %s <adf-db-file-name> [<adf-db-file-name>...]\n",
			argv[0]);
		return_code = ADF_BAD_ARGS_FAILURE;
	}
	else {
		for (count_1 = 1; count_1 < argc; count_1++) {
			fprintf(stderr, "File: %s\n", argv[count_1]);
			if ((return_code = ADF_OpenADFFileIn(&control_data, argv[count_1],
				error_text)) != ADF_SUCCESS) {
				if (return_code != ADF_PARSE_FAILURE)
					break;
				fprintf(stderr, "%s\n", error_text);
				return_code = ADF_SUCCESS;
			}
		}
		if (return_code == ADF_SUCCESS) {
			if ((return_code = ADF_FinalizeEntries(&control_data, error_text)) !=
				ADF_SUCCESS)
				goto EXIT_FUNCTION;
			if ((return_code = ADF_BuildIndexItemList(&control_data,
				&index_item_count, &index_item_list, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			printf("Index List Test\n");
			STR_EMIT_CharLine('-', 78, NULL, NULL);
			TEST_EmitIndexList(index_item_count, index_item_list, 0);
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			ADF_FreeIndexItemList(&index_item_count, &index_item_list);
			if ((return_code = ADF_BuildClassTOCItemList(&control_data,
				&index_item_count, &index_item_list, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			printf("Entry Class Index List Test\n");
			STR_EMIT_CharLine('-', 78, NULL, NULL);
			TEST_EmitIndexList(index_item_count, index_item_list, 0);
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			ADF_FreeIndexItemList(&index_item_count, &index_item_list);
			if ((return_code = ADF_BuildPermIndex(&control_data,
				&perm_index_count, &perm_index_list, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			printf("Permutated Index List Test\n");
			STR_EMIT_CharLine('-', 78, NULL, NULL);
			TEST_EmitPermIndexList(&control_data, perm_index_count,
				perm_index_list);
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			ADF_FreePermIndexList(&perm_index_count, &perm_index_list);
			fprintf(stderr, "\n\n");
		}
	}

EXIT_FUNCTION:

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#ifndef NARGS
static void TEST_EmitIndexList(unsigned int index_item_count,
	const ADF_INDEX_ITEM *index_item_list, unsigned int indent)
#else
static void TEST_EmitIndexList(index_item_count, index_item_list, indent)
unsigned int          index_item_count;
const ADF_INDEX_ITEM *index_item_list;
unsigned int          indent;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < index_item_count; count_1++) {
		STR_EMIT_Char(' ', indent, NULL, NULL);
		if (index_item_list[count_1].entry_flag == ADF_TRUE)
			fprintf(stdout, "[%s]\n", index_item_list[count_1].item_name);
		else
			fprintf(stdout, "%s\n", index_item_list[count_1].item_name);
		if (index_item_list[count_1].index_item_count)
			TEST_EmitIndexList(index_item_list[count_1].index_item_count,
				index_item_list[count_1].index_item_list, indent + 3);
	}
}

#ifndef NARGS
static void TEST_EmitPermIndexList(const ADF_CONTROL *control_ptr,
	unsigned int index_item_count, const ADF_PERM_INDEX *index_item_list)
#else
static void TEST_EmitPermIndexList(control_ptr, index_item_count,
	index_item_list)
const ADF_CONTROL    *control_ptr;
unsigned int          index_item_count;
const ADF_PERM_INDEX *index_item_list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	unsigned int count_2;

	for (count_1 = 0; count_1 < index_item_count;
		count_1++, index_item_list++) {
		printf("%s\n",
			control_ptr->in_entry_list[index_item_list->entry_index].base_name);
		for (count_2 = 0; count_2 < index_item_list->ref_count; count_2++)
			printf("   %s\n",
				control_ptr->in_entry_list[index_item_list->ref_list[count_2]].
				base_name);
	}
}

#endif /* #ifdef TEST_MAIN */

