/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages allocation and de-allocation of ADF entries.

	Revision History	:	1995-05-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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
COMPAT_FN_DECL_STATIC(void ADF_SORT_IND_EntryList,
	(int sort_type, unsigned int entry_count, ADF_ENTRY **entry_list));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_EntryByEntry,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_EntryByBaseName,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_EntryByFileName,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_EntryByCoreName,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_EntryByFileType,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_EntryByManPage,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_EntryByDictOrder,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_HTextByEntry,
	(void *control_ptr, const ADF_HTEXT *ptr_1, const ADF_HTEXT *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_HTextByText,
	(void *control_ptr, const ADF_HTEXT *ptr_1, const ADF_HTEXT *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMPI_EntryByBaseName,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMPI_EntryByFileName,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMPI_EntryByCoreName,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMPI_EntryByFileType,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMPI_EntryByManPage,
	(void *control_ptr, const ADF_ENTRY *ptr_1, const ADF_ENTRY *ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_IND_EntryByEntry,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_IND_EntryByBaseName,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_IND_EntryByFileName,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_IND_EntryByCoreName,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_IND_EntryByFileType,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_IND_EntryByManPage,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_IND_EntryByDictOrder,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMPI_IND_EntryByBaseName,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMPI_IND_EntryByFileName,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMPI_IND_EntryByCoreName,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMPI_IND_EntryByFileType,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMPI_IND_EntryByManPage,
	(void *control_ptr, const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2,
	size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_SectionByDef,
	(void *control_ptr, const ADF_ENTRY_DATA *ptr_1,
	const ADF_ENTRY_DATA *ptr_2, size_t data_length));
COMPAT_FN_DECL_STATIC(int  ADF_SCMP_SectionBySource,
	(void *control_ptr, const ADF_ENTRY_DATA *ptr_1,
	const ADF_ENTRY_DATA *ptr_2, size_t data_length));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *ADF_DescribeEntry(const ADF_ENTRY *entry_ptr, char *buffer)
#else
char *ADF_DescribeEntry(entry_ptr, buffer)
const ADF_ENTRY *entry_ptr;
char            *buffer;
#endif /* #ifndef NARGS */
{
/* CODE NOTE: To be removed. */
#if 0
	sprintf(buffer, "%s '%-.100s' %s '%-.500s'",
		"base name", entry_ptr->base_name,
		"resulting from the ADF parse of the source file",
# ifdef __MSDOS__
		entry_ptr->file_name);
# else
		entry_ptr->full_name);
# endif /* # ifdef __MSDOS__ */

	return(buffer);
#endif /* #if 0 */
	return(chrcat(strncat(strcat(strncat(strcpy(buffer, "base name '"),
   	entry_ptr->base_name, 100),
   	"' resulting from the ADF parse of the source file '"),
#ifdef __MSDOS__
		entry_ptr->file_name, 500),
#else
		entry_ptr->full_name, 500),
#endif /* #ifdef __MSDOS__ */
		'\''));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *ADF_DescribeInEntry(const ADF_ENTRY *entry_ptr,
	const ADF_IN_FILE *in_file_ptr, char *buffer)
#else
char *ADF_DescribeInEntry(entry_ptr, in_file_ptr, buffer)
const ADF_ENTRY   *entry_ptr;
const ADF_IN_FILE *in_file_ptr;
char              *buffer;
#endif /* #ifndef NARGS */
{
/* CODE NOTE: To be removed. */
#if 0
	ADF_DescribeEntry(entry_ptr, buffer);
	sprintf(buffer + strlen(buffer),
		" (in the ADF database file named '%-.500s')", in_file_ptr->file_name);

	return(buffer);
#endif /* #if 0 */
	return(strcat(strncat(strcat(ADF_DescribeEntry(entry_ptr, buffer),
   	" (in the ADF database file named '"), in_file_ptr->file_name, 500),
      "')"));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
const ADF_ENTRY *ADF_FIND_LookUpEntryByEntry(unsigned int entry_count,
	const ADF_ENTRY *entry_list, unsigned int file_index,
	unsigned int entry_index, unsigned int *found_index)
#else
const ADF_ENTRY *ADF_FIND_LookUpEntryByEntry(entry_count, entry_list,
	file_index, entry_index, found_index)
unsigned int     entry_count;
const ADF_ENTRY *entry_list;
unsigned int     file_index;
unsigned int     entry_index;
unsigned int    *found_index;
#endif /* #ifndef NARGS */
{
	const ADF_ENTRY *return_ptr = NULL;
	unsigned int     count_1;
	unsigned int    *found_index_ptr;
	unsigned int     tmp_found_index;

	found_index_ptr = (found_index == NULL) ? &tmp_found_index : found_index;

	for (count_1 = 0; count_1 < entry_count; count_1++) {
		if ((entry_list[count_1].file_index == file_index) &&
			(entry_list[count_1].entry_index == entry_index)) {
			*found_index_ptr = count_1;
			return_ptr       = entry_list + count_1;
			break;
		}
	}

	return(return_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*
	Assumes that the array is sorted by 'file_index' and 'entry_index'.
*/
#ifndef NARGS
int ADF_FIND_FindEntryByEntry(unsigned int entry_count,
	const ADF_ENTRY *entry_list, unsigned int file_index,
	unsigned int entry_index, unsigned int *found_index)
#else
int ADF_FIND_FindEntryByEntry(entry_count, entry_list, file_index,
	entry_index, found_index)
unsigned int     entry_count;
const ADF_ENTRY *entry_list;
unsigned int     file_index;
unsigned int     entry_index;
unsigned int    *found_index;
#endif /* #ifndef NARGS */
{
	unsigned int *found_index_ptr;
	unsigned int  tmp_found_index;
	ADF_ENTRY     tmp_entry;

	found_index_ptr  = (found_index == NULL) ? &tmp_found_index : found_index;

	tmp_entry.file_index  = file_index;
	tmp_entry.entry_index = entry_index;

#ifndef NARGS
	return(STR_ARRAY_bsearch(NULL, entry_count, entry_list, &tmp_entry,
		sizeof(tmp_entry), found_index_ptr, STRFUNCS_DIRECTION_TOP,
		((int (*)(void *, const void *, const void *, size_t))
		ADF_SCMP_EntryByEntry)));
#else
	return(STR_ARRAY_bsearch(NULL, entry_count, entry_list, &tmp_entry,
		sizeof(tmp_entry), found_index_ptr, STRFUNCS_DIRECTION_TOP,
		ADF_SCMP_EntryByEntry));
#endif /* #ifndef NARGS */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*
	Assumes that the array is sorted by 'base_name'.
*/
#ifndef NARGS
int ADF_FIND_FindEntryByBaseName(unsigned int entry_count,
	const ADF_ENTRY *entry_list, const char *base_name,
	unsigned int *found_index)
#else
int ADF_FIND_FindEntryByBaseName(entry_count, entry_list, base_name,
	found_index)
unsigned int     entry_count;
const ADF_ENTRY *entry_list;
const char      *base_name;
unsigned int    *found_index;
#endif /* #ifndef NARGS */
{
	unsigned int *found_index_ptr;
	unsigned int  tmp_found_index;
	ADF_ENTRY     tmp_entry;

	found_index_ptr  = (found_index == NULL) ? &tmp_found_index : found_index;

	tmp_entry.base_name = ((char *) base_name);

#ifndef NARGS
	return(STR_ARRAY_bsearch(NULL, entry_count, entry_list, &tmp_entry,
		sizeof(tmp_entry), found_index_ptr, STRFUNCS_DIRECTION_TOP,
		((int (*)(void *, const void *, const void *, size_t))
		ADF_SCMP_EntryByBaseName)));
#else
	return(STR_ARRAY_bsearch(NULL, entry_count, entry_list, &tmp_entry,
		sizeof(tmp_entry), found_index_ptr, STRFUNCS_DIRECTION_TOP,
		ADF_SCMP_EntryByBaseName));
#endif /* #ifndef NARGS */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_FIND_FindHTextByText(unsigned int htext_count,
	const ADF_HTEXT *htext_list, const char *hyper_text,
	unsigned int *found_index)
#else
int ADF_FIND_FindHTextByText(htext_count, htext_list, hyper_text,
	found_index)
unsigned int     htext_count;
const ADF_HTEXT *htext_list;
const char      *hyper_text;
unsigned int    *found_index;
#endif /* #ifndef NARGS */
{
	unsigned int *found_index_ptr;
	unsigned int  tmp_found_index;
	ADF_HTEXT     tmp_htext;

	found_index_ptr  = (found_index == NULL) ? &tmp_found_index : found_index;

	tmp_htext.hyper_text = ((char *) hyper_text);

#ifndef NARGS
	return(STR_ARRAY_bsearch(NULL, htext_count, htext_list, &tmp_htext,
		sizeof(tmp_htext), found_index_ptr, STRFUNCS_DIRECTION_TOP,
		((int (*)(void *, const void *, const void *, size_t))
		ADF_SCMP_HTextByText)));
#else
	return(STR_ARRAY_bsearch(NULL, htext_count, htext_list, &tmp_htext,
		sizeof(tmp_htext), found_index_ptr, STRFUNCS_DIRECTION_TOP,
		ADF_SCMP_HTextByText));
#endif /* #ifndef NARGS */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_AllocateEntryItem(ADF_ENTRY *entry_ptr, const char *base_name,
	const char *file_name, const char *core_name, const char *full_name,
	const char *file_type, const char *man_page, char *error_text)
#else
int ADF_AllocateEntryItem(entry_ptr, base_name, file_name, core_name,
	full_name, file_type, man_page, error_text)
ADF_ENTRY  *entry_ptr;
const char *base_name;
const char *file_name;
const char *core_name;
const char *full_name;
const char *file_type;
const char *man_page;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int       return_code = ADF_SUCCESS;
	ADF_ENTRY tmp_entry;

	memset(&tmp_entry, '\0', sizeof(tmp_entry));

	tmp_entry = *entry_ptr;

	if ((tmp_entry.base_name = strdup(base_name)) == NULL) {
		STR_AllocMsgItem(strlen(base_name) + 1, error_text,
			"Unable to allocate memory for the directory base name");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_entry.file_name = strdup(file_name)) == NULL) {
		STR_AllocMsgItem(strlen(file_name) + 1, error_text,
			"Unable to allocate memory for the directory file name");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_entry.core_name = strdup(core_name)) == NULL) {
		STR_AllocMsgItem(strlen(core_name) + 1, error_text,
			"Unable to allocate memory for the directory file core name");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_entry.full_name = strdup(full_name)) == NULL) {
		STR_AllocMsgItem(strlen(full_name) + 1, error_text,
			"Unable to allocate memory for the complete directory file name");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_entry.file_type = strdup(file_type)) == NULL) {
		STR_AllocMsgItem(strlen(file_type) + 1, error_text,
			"Unable to allocate memory for the directory file type");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_entry.man_page = strdup(man_page)) == NULL) {
		STR_AllocMsgItem(strlen(man_page) + 1, error_text,
			"Unable to allocate memory for the directory man page");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	*entry_ptr          = tmp_entry;

	tmp_entry.base_name = NULL;
	tmp_entry.file_name = NULL;
	tmp_entry.core_name = NULL;
	tmp_entry.full_name = NULL;
	tmp_entry.file_type = NULL;
	tmp_entry.man_page  = NULL;

EXIT_FUNCTION:

	if (tmp_entry.base_name != NULL)
		free(tmp_entry.base_name);
	if (tmp_entry.file_name != NULL)
		free(tmp_entry.file_name);
	if (tmp_entry.core_name != NULL)
		free(tmp_entry.core_name);
	if (tmp_entry.full_name != NULL)
		free(tmp_entry.full_name);
	if (tmp_entry.file_type != NULL)
		free(tmp_entry.file_type);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_AllocateHTextItem(ADF_HTEXT *htext_ptr, const char *hyper_text,
	char *error_text)
#else
int ADF_AllocateHTextItem(htext_ptr, hyper_text, error_text)
ADF_HTEXT  *htext_ptr;
const char *hyper_text;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int       return_code = ADF_SUCCESS;
	ADF_HTEXT tmp_htext;

	memset(&tmp_htext, '\0', sizeof(tmp_htext));

	tmp_htext = *htext_ptr;

	if ((tmp_htext.hyper_text = strdup(hyper_text)) == NULL) {
		STR_AllocMsgItem(strlen(hyper_text) + 1, error_text,
			"Unable to allocate memory for a publish x-ref item");
		return_code = ADF_MEMORY_FAILURE;
	}
	else
		*htext_ptr = tmp_htext;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeEntryListPrep(ADF_CONTROL *control_ptr)
#else
void ADF_FreeEntryListPrep(control_ptr)
ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	if (control_ptr->prep_entry_count) {
		for (count_1 = 0; count_1 < control_ptr->prep_entry_count; count_1++)
			ADF_FreeEntryItem(control_ptr->prep_entry_list + count_1);
		free(control_ptr->prep_entry_list);
	}

	control_ptr->prep_entry_count = 0;
	control_ptr->prep_entry_list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeHTextListPrep(ADF_CONTROL *control_ptr)
#else
void ADF_FreeHTextListPrep(control_ptr)
ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	if (control_ptr->prep_htext_count) {
		for (count_1 = 0; count_1 < control_ptr->prep_htext_count; count_1++)
			ADF_FreeHTextItem(control_ptr->prep_htext_list + count_1);
		free(control_ptr->prep_htext_list);
	}

	control_ptr->prep_htext_count = 0;
	control_ptr->prep_htext_list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeEntryListIn(ADF_CONTROL *control_ptr)
#else
void ADF_FreeEntryListIn(control_ptr)
ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	if (control_ptr->in_entry_list != NULL)
		free(control_ptr->in_entry_list);

	control_ptr->in_entry_count = 0;
	control_ptr->in_entry_list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeHTextListIn(ADF_CONTROL *control_ptr)
#else
void ADF_FreeHTextListIn(control_ptr)
ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	if (control_ptr->in_htext_list != NULL)
		free(control_ptr->in_htext_list);

	control_ptr->in_htext_count = 0;
	control_ptr->in_htext_list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeEntryItem(ADF_ENTRY *entry_ptr)
#else
void ADF_FreeEntryItem(entry_ptr)
ADF_ENTRY *entry_ptr;
#endif /* #ifndef NARGS */
{
	if (entry_ptr->base_name != NULL)
		free(entry_ptr->base_name);
	if (entry_ptr->file_name != NULL)
		free(entry_ptr->file_name);
	if (entry_ptr->core_name != NULL)
		free(entry_ptr->core_name);
	if (entry_ptr->full_name != NULL)
		free(entry_ptr->full_name);
	if (entry_ptr->file_type != NULL)
		free(entry_ptr->file_type);
	if (entry_ptr->man_page != NULL)
		free(entry_ptr->man_page);

	memset(entry_ptr, '\0', sizeof(*entry_ptr));

	entry_ptr->base_name = NULL;
	entry_ptr->file_name = NULL;
	entry_ptr->core_name = NULL;
	entry_ptr->full_name = NULL;
	entry_ptr->file_type = NULL;
	entry_ptr->man_page  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeHTextItem(ADF_HTEXT *htext_ptr)
#else
void ADF_FreeHTextItem(htext_ptr)
ADF_HTEXT *htext_ptr;
#endif /* #ifndef NARGS */
{
	if (htext_ptr->hyper_text != NULL)
		free(htext_ptr->hyper_text);

	memset(htext_ptr, '\0', sizeof(*htext_ptr));

	htext_ptr->hyper_text = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_SORT_EntryList(int sort_type, unsigned int entry_count,
	ADF_ENTRY *entry_list)
#else
void ADF_SORT_EntryList(sort_type, entry_count, entry_list)
int           sort_type;
unsigned int  entry_count;
ADF_ENTRY    *entry_list;
#endif /* #ifndef NARGS */
{
	int (*cmp_function)(void *, const ADF_ENTRY *, const ADF_ENTRY *, size_t);

	if (sort_type & ADF_SORT_IGNORE_CASE) {
		sort_type    -= ADF_SORT_IGNORE_CASE;
		cmp_function  =
			(sort_type == ADF_SORT_ENTRY_BASE_NAME)  ?
			ADF_SCMPI_EntryByBaseName  :
			(sort_type == ADF_SORT_ENTRY_FILE_NAME)  ?
			ADF_SCMPI_EntryByFileName  :
			(sort_type == ADF_SORT_ENTRY_CORE_NAME)  ?
			ADF_SCMPI_EntryByCoreName  :
			(sort_type == ADF_SORT_ENTRY_FILE_TYPE)  ?
			ADF_SCMPI_EntryByFileType  :
			(sort_type == ADF_SORT_ENTRY_MAN_PAGE)   ?
			ADF_SCMPI_EntryByManPage   :
			(sort_type == ADF_SORT_ENTRY_DICT_ORDER) ?
			ADF_SCMP_EntryByDictOrder : ADF_SCMP_EntryByEntry;
	}
	else
		cmp_function =
			(sort_type == ADF_SORT_ENTRY_BASE_NAME)  ?
			ADF_SCMP_EntryByBaseName  :
			(sort_type == ADF_SORT_ENTRY_FILE_NAME)  ?
			ADF_SCMP_EntryByFileName  :
			(sort_type == ADF_SORT_ENTRY_CORE_NAME)  ?
			ADF_SCMP_EntryByCoreName  :
			(sort_type == ADF_SORT_ENTRY_FILE_TYPE)  ?
			ADF_SCMP_EntryByFileType  :
			(sort_type == ADF_SORT_ENTRY_MAN_PAGE)   ?
			ADF_SCMP_EntryByManPage   :
			(sort_type == ADF_SORT_ENTRY_DICT_ORDER) ?
			ADF_SCMP_EntryByDictOrder : ADF_SCMP_EntryByEntry;

#ifndef NARGS
	STR_ARRAY_qsort(NULL, entry_count, entry_list, sizeof(entry_list[0]),
		((int (*)(void *, const void *, const void *, size_t)) cmp_function));
#else
	STR_ARRAY_qsort(NULL, entry_count, entry_list, sizeof(entry_list[0]),
		cmp_function);
#endif /* #ifndef NARGS */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_SORT_HTextList(int sort_type, unsigned int htext_count,
	ADF_HTEXT *htext_list)
#else
void ADF_SORT_HTextList(sort_type, htext_count, htext_list)
int           sort_type;
unsigned int  htext_count;
ADF_HTEXT    *htext_list;
#endif /* #ifndef NARGS */
{
	int (*cmp_function)(void *, const ADF_HTEXT *, const ADF_HTEXT *, size_t);

	cmp_function =
		(sort_type == ADF_SORT_HTEXT_TEXT) ? ADF_SCMP_HTextByText :
		ADF_SCMP_HTextByEntry;

#ifndef NARGS
	STR_ARRAY_qsort(NULL, htext_count, htext_list, sizeof(htext_list[0]),
		((int (*)(void *, const void *, const void *, size_t)) cmp_function));
#else
	STR_ARRAY_qsort(NULL, htext_count, htext_list, sizeof(htext_list[0]),
		cmp_function);
#endif /* #ifndef NARGS */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_SORT_EntrySections(int sort_type, ADF_ENTRY_DATA *entry_data_list)
#else
void ADF_SORT_EntrySections(sort_type, entry_data_list)
int             sort_type;
ADF_ENTRY_DATA *entry_data_list;
#endif /* #ifndef NARGS */
{
	int (*cmp_function)(void *, const ADF_ENTRY_DATA *, const ADF_ENTRY_DATA *,
		size_t);

	if ((sort_type == ADF_AREA_ORDER_TYPE_DEF) ||
		(sort_type == ADF_AREA_ORDER_TYPE_SOURCE)) {
		cmp_function = (sort_type == ADF_AREA_ORDER_TYPE_DEF) ?
			ADF_SCMP_SectionByDef : ADF_SCMP_SectionBySource;
#ifndef NARGS
		STR_ARRAY_qsort(NULL, ADF_AREA_COUNT, entry_data_list,
			sizeof(entry_data_list[0]),
			((int (*)(void *, const void *, const void *, size_t))
			cmp_function));
#else
		STR_ARRAY_qsort(NULL, ADF_AREA_COUNT, entry_data_list,
			sizeof(entry_data_list[0]), cmp_function);
#endif /* #ifndef NARGS */
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_FinalizeEntries(ADF_CONTROL *control_ptr, char *error_text)
#else
int ADF_FinalizeEntries(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	unsigned int  found_index;
	ADF_HTEXT    *htext_ptr;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the entry list has had memory previously allocated, we free	*/
	/*	that memory.																		*/
	/*	*****************************************************************	*/
	if (control_ptr->in_entry_order_list != NULL) {
		free(control_ptr->in_entry_order_list);
		control_ptr->in_entry_order_list = NULL;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Fix-up the sort order if '-OUTPUT_BY_FILE_NAME=' is 'TRUE'.		*/
	/*	*****************************************************************	*/
#ifdef __MSDOS__
	control_ptr->sort_order_type =
		(control_ptr->output_by_file_flag == ADF_TRUE) ?
		(ADF_SORT_ENTRY_CORE_NAME | ADF_SORT_IGNORE_CASE) :
		control_ptr->sort_order_type;
#else
	control_ptr->sort_order_type =
		(control_ptr->output_by_file_flag == ADF_TRUE) ?
		ADF_SORT_ENTRY_CORE_NAME : control_ptr->sort_order_type;
#endif /* #ifdef __MSDOS__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Fix-up the sort order if '-GENERATE_TYPE=' is 'TOC'.				*/
	/*	*****************************************************************	*/
	control_ptr->sort_order_type =
		(control_ptr->generate_type == ADF_GENERATE_TYPE_TOC) ?
		ADF_SORT_ENTRY_DICT_ORDER : control_ptr->sort_order_type;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Fix-up the sort order if '-GENERATE_TYPE=' is 'TOF'.				*/
	/*	*****************************************************************	*/
#ifdef __MSDOS__
	control_ptr->sort_order_type =
		(control_ptr->generate_type == ADF_GENERATE_TYPE_TOF) ?
		(ADF_SORT_ENTRY_CORE_NAME | ADF_SORT_IGNORE_CASE) :
		control_ptr->sort_order_type;
#else
	control_ptr->sort_order_type =
		(control_ptr->generate_type == ADF_GENERATE_TYPE_TOF) ?
		ADF_SORT_ENTRY_CORE_NAME : control_ptr->sort_order_type;
#endif /* #ifdef __MSDOS__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If there are no entries loaded, our work is done.					*/
	/*	*****************************************************************	*/
	if (!control_ptr->in_entry_count)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Allocate the list of pointers to the loaded entries.				*/
	/*	*****************************************************************	*/
	if ((control_ptr->in_entry_order_list = ((ADF_ENTRY **)
		calloc(control_ptr->in_entry_count, sizeof(ADF_ENTRY *)))) == NULL) {
		STR_AllocMsgList(control_ptr->in_entry_count, sizeof(ADF_ENTRY *),
			error_text, "Unable to allocate memory for the entry order list");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Sort the loaded entries by the ADF database file from which		*/
	/*	they were loaded and the order of the entry within that file.		*/
	/*	*****************************************************************	*/
	ADF_SORT_EntryList(ADF_SORT_ENTRY_ENTRY, control_ptr->in_entry_count,
		control_ptr->in_entry_list);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Sort the hyper text list by the hyper text string.					*/
	/*	*****************************************************************	*/
	ADF_SORT_HTextList(ADF_SORT_HTEXT_TEXT, control_ptr->in_htext_count,
		control_ptr->in_htext_list);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Create the indirect list of pointers to the loaded entries and	*/
	/*	sort that list in the requested order.										*/
	/*																							*/
	/*		Note that we include only those entries not loaded from ADF		*/
	/*	database files intended to resolve external hyper-text links.		*/
	/*	*****************************************************************	*/
	control_ptr->in_entry_order_count = 0;
	for (count_1 = 0; count_1 < control_ptr->in_entry_count; count_1++) {
		if (control_ptr->in_entry_list[count_1].href_flag != ADF_TRUE)
			control_ptr->in_entry_order_list
				[control_ptr->in_entry_order_count++] =
				control_ptr->in_entry_list + count_1;
	}
	ADF_SORT_IND_EntryList(control_ptr->sort_order_type,
		control_ptr->in_entry_order_count, control_ptr->in_entry_order_list);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Attempt to link each of the elements in the hyper text list to	*/
	/*	the entry from which it was parsed . . .									*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < control_ptr->in_htext_count; count_1++) {
		if (ADF_FIND_FindEntryByEntry(control_ptr->in_entry_count,
			control_ptr->in_entry_list,
			control_ptr->in_htext_list[count_1].file_index,
			control_ptr->in_htext_list[count_1].entry_index, &found_index) !=
			STRFUNCS_ITEM_FOUND) {
			sprintf(error_text, "%s '%-.500s', file index %u, entry index %u.",
				"Unable to locate the entry corresponding to hyper text element",
				control_ptr->in_htext_list[count_1].hyper_text,
				control_ptr->in_htext_list[count_1].file_index,
				control_ptr->in_htext_list[count_1].entry_index);
			return_code = ADF_FAILURE;
			goto EXIT_FUNCTION;
		}
		control_ptr->in_htext_list[count_1].in_entry_index = found_index;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Create the character table for the hyper-text list.				*/
	/*																							*/
	/*		Note that this code assumes 'control_ptr->in_htext_list' has	*/
	/*	sorted in ascending order by logic above in this function.			*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 <= UCHAR_MAX; count_1++) {
		control_ptr->in_htext_lookup_list[count_1].count = 0;
		control_ptr->in_htext_lookup_list[count_1].list  = NULL;
	}
	for (count_1 = 0; count_1 < control_ptr->in_htext_count; count_1++) {
		htext_ptr = control_ptr->in_htext_list + count_1;
		if (control_ptr->in_htext_lookup_list
			[((unsigned char) *htext_ptr->hyper_text)].list == NULL)
			control_ptr->in_htext_lookup_list
				[((unsigned char) *htext_ptr->hyper_text)].list = htext_ptr;
		control_ptr->in_htext_lookup_list
			[((unsigned char) *htext_ptr->hyper_text)].count++;
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_ReadEntry(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA_FILE *entry_data_ptr, ADF_SOURCE_DATA *area_list,
	char *error_text)
#else
int ADF_ReadEntry(control_ptr, entry_ptr, entry_data_ptr, area_list,
	error_text)
ADF_CONTROL         *control_ptr;
const ADF_ENTRY     *entry_ptr;
ADF_ENTRY_DATA_FILE *entry_data_ptr;
ADF_SOURCE_DATA     *area_list;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int                  return_code;
	unsigned int         count_1;
	ADF_IN_FILE         *in_file_ptr;
	ADF_ENTRY_DATA_FILE  entry_data;
	char                *tmp_ptr;
	char                 buffer[ADF_ENTRY_DESCRIP_LENGTH];

	in_file_ptr = control_ptr->in_file_list + entry_ptr->file_index;

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		area_list[count_1].section_ptr    = NULL;
		area_list[count_1].section_index  = 0;
		area_list[count_1].section_name   = NULL;
		area_list[count_1].start_position = 0;
		area_list[count_1].line_number    = 0;
		area_list[count_1].line_count     = 0;
		area_list[count_1].line_list      = NULL;
		area_list[count_1].line_data      = NULL;
	}

	ADF_fseek(in_file_ptr->file_ptr, entry_ptr->entry_offset, SEEK_SET);

	if ((return_code = ADF_FRead(&entry_data, sizeof(entry_data), 1,
		in_file_ptr->file_ptr, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((entry_data.data_length + 1) > control_ptr->read_entry_buffer_length) {
		tmp_ptr = ((char *) ((!control_ptr->read_entry_buffer_length) ?
			malloc((entry_data.data_length + 1) * sizeof(char)) :
			realloc(control_ptr->read_entry_buffer,
			(entry_data.data_length + 1) * sizeof(char))));
		if (tmp_ptr == NULL) {
			STR_AllocMsgItem(entry_data.data_length + 1,
				"Unable to allocate a buffer for loading the entry for %s",
				ADF_DescribeInEntry(entry_ptr, in_file_ptr, buffer));
			return_code = ADF_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		tmp_ptr[entry_data.data_length]       = '\0';
		control_ptr->read_entry_buffer_length = entry_data.data_length + 1;
		control_ptr->read_entry_buffer        = tmp_ptr;
	}

	if ((return_code = ADF_FRead(control_ptr->read_entry_buffer, 1,
		entry_data.data_length, in_file_ptr->file_ptr, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		if (entry_data.section_length[count_1] &&
			(control_ptr->ignore_section_list[count_1] != ADF_TRUE)) {
			if (entry_data.name_length[count_1])
				area_list[count_1].section_name =
					control_ptr->read_entry_buffer +
					entry_data.name_offset[count_1];
			area_list[count_1].section_index = entry_data.section_order[count_1];
			area_list[count_1].line_number   = entry_data.actual_order[count_1];
			area_list[count_1].line_data     = control_ptr->read_entry_buffer +
				entry_data.section_offset[count_1];
		}
	}

	if (entry_data_ptr != NULL)
		*entry_data_ptr = entry_data;

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_WriteEntry(ADF_CONTROL *control_ptr, ADF_ENTRY *entry_ptr,
	const ADF_SOURCE_DATA *area_list, char *error_text)
#else
int ADF_WriteEntry(control_ptr, entry_ptr, area_list, error_text)
ADF_CONTROL           *control_ptr;
ADF_ENTRY             *entry_ptr;
const ADF_SOURCE_DATA *area_list;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int                 return_code;
	unsigned int        current_offset;
	unsigned int        count_1;
	ADF_ENTRY_DATA_FILE entry_data;

	if ((return_code = ADF_PadFile(control_ptr->prep_adf_file, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

	entry_ptr->entry_offset = ADF_ftell(control_ptr->prep_adf_file);

	memset(&entry_data, '\0', sizeof(entry_data));

	current_offset             = 0;
	entry_data.data_length     = 0;
	entry_data.paragraph_count = 0;

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		entry_data.name_offset[count_1]     = current_offset;
#if 0
/*
	CODE NOTE: To be removed.
*/
		entry_data.name_length[count_1]     =
			((area_list[count_1].section_name == NULL) ||
			(!(*area_list[count_1].section_name))) ? 0 :
			(strlen(area_list[count_1].section_name) + 1);
#else
		entry_data.name_length[count_1]     =
			((area_list[count_1].line_data == NULL)   ||
			(!(*area_list[count_1].line_data))        ||
			(area_list[count_1].section_name == NULL) ||
			(!(*area_list[count_1].section_name))) ? 0 :
			(strlen(area_list[count_1].section_name) + 1);
#endif /* #if 0 */
		current_offset                     += entry_data.name_length[count_1];
		entry_data.section_offset[count_1]  = current_offset;
		entry_data.section_length[count_1]  =
			((area_list[count_1].line_data == NULL) ||
			(!(*area_list[count_1].line_data))) ? 0 :
			(strlen(area_list[count_1].line_data) + 1);
		entry_data.section_order[count_1]   =
			(area_list[count_1].section_ptr != NULL) ?
			area_list[count_1].section_index :
			((UINT_MAX - ADF_AREA_COUNT) + count_1);
		entry_data.actual_order[count_1]    = (area_list[count_1].line_number) ?
			area_list[count_1].line_number   :
			((UINT_MAX - ADF_AREA_COUNT) + count_1);
		entry_data.paragraph_count         +=
			(area_list[count_1].line_data == NULL) ? 0 :
			(chrcnt(area_list[count_1].line_data, '\n') + 1);
		entry_data.data_length             += entry_data.name_length[count_1] +
			entry_data.section_length[count_1];
		current_offset                     += entry_data.section_length[count_1];
	}

	if ((return_code = ADF_FWrite(&entry_data, sizeof(entry_data), 1,
		control_ptr->prep_adf_file, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
#if 0
/*
	CODE NOTE: To be removed.
*/
		if (area_list[count_1].section_name != NULL) {
#else
		if (entry_data.name_length[count_1]) {
#endif /* #if 0 */
			if ((return_code = ADF_FWrite(area_list[count_1].section_name, 1,
				entry_data.name_length[count_1], control_ptr->prep_adf_file,
				error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
		}
		if (area_list[count_1].line_data != NULL) {
			if ((return_code = ADF_FWrite(area_list[count_1].line_data, 1,
				entry_data.section_length[count_1], control_ptr->prep_adf_file,
				error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
		}
/*
printf(">>> [%05u]:N Length=%10u|N Offset %10u|S Length=%10u:S Offset=%10u\n",
	count_1,
	entry_data.name_length[count_1],
	entry_data.name_offset[count_1],
	entry_data.section_length[count_1],
	entry_data.section_offset[count_1]);
*/
	}

	if ((return_code = ADF_PadFile(control_ptr->prep_adf_file, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

/*
	CODE NOTE: To be deleted.
*/
/*
printf("ADDED ENTRY:length=%10lu:offset=%10lu:%-12.12s:%s\n",
	ADF_ftell(control_ptr->prep_adf_file) - entry_ptr->entry_offset,
	entry_ptr->entry_offset, entry_ptr->file_name, entry_ptr->base_name);
*/

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_SORT_IND_EntryList(int sort_type, unsigned int entry_count,
	ADF_ENTRY **entry_list)
#else
void ADF_SORT_IND_EntryList(sort_type, entry_count, entry_list)
int            sort_type;
unsigned int   entry_count;
ADF_ENTRY    **entry_list;
#endif /* #ifndef NARGS */
{
	int (*cmp_function)(void *, const ADF_ENTRY **, const ADF_ENTRY **,
		size_t);

	if (sort_type & ADF_SORT_IGNORE_CASE) {
		sort_type    -= ADF_SORT_IGNORE_CASE;
		cmp_function  =
			(sort_type == ADF_SORT_ENTRY_BASE_NAME)  ?
			ADF_SCMPI_IND_EntryByBaseName  :
			(sort_type == ADF_SORT_ENTRY_FILE_NAME)  ?
			ADF_SCMPI_IND_EntryByFileName  :
			(sort_type == ADF_SORT_ENTRY_CORE_NAME)  ?
			ADF_SCMPI_IND_EntryByCoreName  :
			(sort_type == ADF_SORT_ENTRY_FILE_TYPE)  ?
			ADF_SCMPI_IND_EntryByFileType  :
			(sort_type == ADF_SORT_ENTRY_MAN_PAGE)   ?
			ADF_SCMPI_IND_EntryByManPage   :
			(sort_type == ADF_SORT_ENTRY_DICT_ORDER) ?
			ADF_SCMP_IND_EntryByDictOrder : ADF_SCMP_IND_EntryByEntry;
	}
	else
		cmp_function =
			(sort_type == ADF_SORT_ENTRY_BASE_NAME)  ?
			ADF_SCMP_IND_EntryByBaseName  :
			(sort_type == ADF_SORT_ENTRY_FILE_NAME)  ?
			ADF_SCMP_IND_EntryByFileName  :
			(sort_type == ADF_SORT_ENTRY_CORE_NAME)  ?
			ADF_SCMP_IND_EntryByCoreName  :
			(sort_type == ADF_SORT_ENTRY_FILE_TYPE)  ?
			ADF_SCMP_IND_EntryByFileType  :
			(sort_type == ADF_SORT_ENTRY_MAN_PAGE)   ?
			ADF_SCMP_IND_EntryByManPage   :
			(sort_type == ADF_SORT_ENTRY_DICT_ORDER) ?
			ADF_SCMP_IND_EntryByDictOrder : ADF_SCMP_IND_EntryByEntry;

#ifndef NARGS
	STR_ARRAY_qsort(NULL, entry_count, entry_list, sizeof(entry_list[0]),
		((int (*)(void *, const void *, const void *, size_t)) cmp_function));
#else
	STR_ARRAY_qsort(NULL, entry_count, entry_list, sizeof(entry_list[0]),
		cmp_function);
#endif /* #ifndef NARGS */
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_EntryByEntry(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMP_EntryByEntry(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = ((ptr_1->file_index > ptr_2->file_index) ? 1 :
		(ptr_1->file_index < ptr_2->file_index) ? -1 : 0)) == 0)
		cmp = (ptr_1->entry_index > ptr_2->entry_index) ? 1 :
			(ptr_1->entry_index < ptr_2->entry_index) ? -1 : 0;

	return(cmp);
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
static int ADF_SCMP_EntryByBaseName(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMP_EntryByBaseName(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	return(strcmp(ptr_1->base_name, ptr_2->base_name));
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
static int ADF_SCMP_EntryByFileName(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMP_EntryByFileName(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = strcmp(ptr_1->file_name, ptr_2->file_name)) == 0)
		cmp = strcmp(ptr_1->base_name, ptr_2->base_name);

	return(cmp);
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
static int ADF_SCMP_EntryByCoreName(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMP_EntryByCoreName(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = strcmp(ptr_1->core_name, ptr_2->core_name)) == 0)
		cmp = strcmp(ptr_1->base_name, ptr_2->base_name);

	return(cmp);
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
static int ADF_SCMP_EntryByFileType(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMP_EntryByFileType(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = strcmp(ptr_1->file_type, ptr_2->file_type)) == 0)
		cmp = strcmp(ptr_1->base_name, ptr_2->base_name);

	return(cmp);
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
static int ADF_SCMP_EntryByManPage(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMP_EntryByManPage(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = strcmp(ptr_1->man_page, ptr_2->man_page)) == 0)
		cmp = strcmp(ptr_1->base_name, ptr_2->base_name);

	return(cmp);
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
static int ADF_SCMP_EntryByDictOrder(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMP_EntryByDictOrder(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = (ADF_DICT_ORDER_CHAR(*ptr_1->base_name) -
		ADF_DICT_ORDER_CHAR(*ptr_2->base_name))) == 0) {
		if ((cmp = stricmp(ptr_1->base_name, ptr_2->base_name)) == 0)
			cmp = strcmp(ptr_1->base_name, ptr_2->base_name);
	}

	return(cmp);
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
static int ADF_SCMP_HTextByEntry(void *control_ptr, const ADF_HTEXT *ptr_1,
	const ADF_HTEXT *ptr_2, size_t data_length)
#else
static int ADF_SCMP_HTextByEntry(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_HTEXT *ptr_1;
const ADF_HTEXT *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = ((ptr_1->file_index > ptr_2->file_index) ? 1 :
		(ptr_1->file_index < ptr_2->file_index) ? -1 : 0)) == 0)
		cmp = (ptr_1->entry_index > ptr_2->entry_index) ? 1 :
			(ptr_1->entry_index < ptr_2->entry_index) ? -1 : 0;

	return(cmp);
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
static int ADF_SCMP_HTextByText(void *control_ptr, const ADF_HTEXT *ptr_1,
	const ADF_HTEXT *ptr_2, size_t data_length)
#else
static int ADF_SCMP_HTextByText(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_HTEXT *ptr_1;
const ADF_HTEXT *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	return(strcmp(ptr_1->hyper_text, ptr_2->hyper_text));
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
static int ADF_SCMPI_EntryByBaseName(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMPI_EntryByBaseName(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	return(stricmp(ptr_1->base_name, ptr_2->base_name));
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
static int ADF_SCMPI_EntryByFileName(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMPI_EntryByFileName(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = stricmp(ptr_1->file_name, ptr_2->file_name)) == 0)
		cmp = stricmp(ptr_1->base_name, ptr_2->base_name);

	return(cmp);
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
static int ADF_SCMPI_EntryByCoreName(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMPI_EntryByCoreName(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = stricmp(ptr_1->core_name, ptr_2->core_name)) == 0)
		cmp = stricmp(ptr_1->base_name, ptr_2->base_name);

	return(cmp);
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
static int ADF_SCMPI_EntryByFileType(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMPI_EntryByFileType(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = stricmp(ptr_1->file_type, ptr_2->file_type)) == 0)
		cmp = stricmp(ptr_1->base_name, ptr_2->base_name);

	return(cmp);
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
static int ADF_SCMPI_EntryByManPage(void *control_ptr, const ADF_ENTRY *ptr_1,
	const ADF_ENTRY *ptr_2, size_t data_length)
#else
static int ADF_SCMPI_EntryByManPage(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const ADF_ENTRY *ptr_1;
const ADF_ENTRY *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = stricmp(ptr_1->man_page, ptr_2->man_page)) == 0)
		cmp = stricmp(ptr_1->base_name, ptr_2->base_name);

	return(cmp);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_IND_EntryByEntry(void *control_ptr, const ADF_ENTRY **ptr_1,
	const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMP_IND_EntryByEntry(control_ptr, ptr_1, ptr_2, data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMP_EntryByEntry(control_ptr, *ptr_1, *ptr_2, data_length));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_IND_EntryByBaseName(void *control_ptr,
	const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMP_IND_EntryByBaseName(control_ptr, ptr_1, ptr_2,
	data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMP_EntryByBaseName(control_ptr, *ptr_1, *ptr_2, data_length));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_IND_EntryByFileName(void *control_ptr,
	const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMP_IND_EntryByFileName(control_ptr, ptr_1, ptr_2,
	data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMP_EntryByFileName(control_ptr, *ptr_1, *ptr_2, data_length));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_IND_EntryByCoreName(void *control_ptr,
	const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMP_IND_EntryByCoreName(control_ptr, ptr_1, ptr_2,
	data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMP_EntryByCoreName(control_ptr, *ptr_1, *ptr_2, data_length));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_IND_EntryByFileType(void *control_ptr,
	const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMP_IND_EntryByFileType(control_ptr, ptr_1, ptr_2,
	data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMP_EntryByFileType(control_ptr, *ptr_1, *ptr_2, data_length));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_IND_EntryByManPage(void *control_ptr,
	const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMP_IND_EntryByManPage(control_ptr, ptr_1, ptr_2, data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMP_EntryByManPage(control_ptr, *ptr_1, *ptr_2, data_length));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_IND_EntryByDictOrder(void *control_ptr,
	const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMP_IND_EntryByDictOrder(control_ptr, ptr_1, ptr_2,
	data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMP_EntryByDictOrder(control_ptr, *ptr_1, *ptr_2,
		data_length));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMPI_IND_EntryByBaseName(void *control_ptr,
	const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMPI_IND_EntryByBaseName(control_ptr, ptr_1, ptr_2,
	data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMPI_EntryByBaseName(control_ptr, *ptr_1, *ptr_2, data_length));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMPI_IND_EntryByFileName(void *control_ptr,
	const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMPI_IND_EntryByFileName(control_ptr, ptr_1, ptr_2,
	data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMPI_EntryByFileName(control_ptr, *ptr_1, *ptr_2, data_length));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMPI_IND_EntryByCoreName(void *control_ptr,
	const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMPI_IND_EntryByCoreName(control_ptr, ptr_1, ptr_2,
	data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMPI_EntryByCoreName(control_ptr, *ptr_1, *ptr_2, data_length));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMPI_IND_EntryByFileType(void *control_ptr,
	const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMPI_IND_EntryByFileType(control_ptr, ptr_1, ptr_2,
	data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMPI_EntryByFileType(control_ptr, *ptr_1, *ptr_2, data_length));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMPI_IND_EntryByManPage(void *control_ptr,
	const ADF_ENTRY **ptr_1, const ADF_ENTRY **ptr_2, size_t data_length)
#else
static int ADF_SCMPI_IND_EntryByManPage(control_ptr, ptr_1, ptr_2,
	data_length)
void             *control_ptr;
const ADF_ENTRY **ptr_1;
const ADF_ENTRY **ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	return(ADF_SCMPI_EntryByManPage(control_ptr, *ptr_1, *ptr_2, data_length));
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_SectionByDef(void *control_ptr,
	const ADF_ENTRY_DATA *ptr_1, const ADF_ENTRY_DATA *ptr_2,
	size_t data_length)
#else
static int ADF_SCMP_SectionByDef(control_ptr, ptr_1, ptr_2, data_length)
void                 *control_ptr;
const ADF_ENTRY_DATA *ptr_1;
const ADF_ENTRY_DATA *ptr_2;
size_t                data_length;
#endif /* #ifndef NARGS */
{
	return((ptr_1->section_order > ptr_2->section_order) ? 1 :
		(ptr_1->section_order < ptr_2->section_order) ? -1 : 0);
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
static int ADF_SCMP_SectionBySource(void *control_ptr,
	const ADF_ENTRY_DATA *ptr_1, const ADF_ENTRY_DATA *ptr_2,
	size_t data_length)
#else
static int ADF_SCMP_SectionBySource(control_ptr, ptr_1, ptr_2, data_length)
void                 *control_ptr;
const ADF_ENTRY_DATA *ptr_1;
const ADF_ENTRY_DATA *ptr_2;
size_t                data_length;
#endif /* #ifndef NARGS */
{
	return((ptr_1->actual_order > ptr_2->actual_order) ? 1 :
		(ptr_1->actual_order < ptr_2->actual_order) ? -1 : 0);
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

int main(argc, argv)
int    argc;
char **argv;
{
	int              return_code = ADF_SUCCESS;
	unsigned int     count_1;
	unsigned int     count_2;
	ADF_CONTROL      control_data;
	ADF_SOURCE_DATA  area_list[ADF_AREA_COUNT];
	char             area_name[ADF_AREA_NAME_LENGTH + 1];
	char            *definition_name;
	char             error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'ADF_ReadEntry()'\n");
	fprintf(stderr, "---- ------- --- -----------------\n\n");

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
			control_data.sort_order_type = ADF_SORT_ENTRY_BASE_NAME;
			if ((return_code = ADF_FinalizeEntries(&control_data, error_text)) !=
				ADF_SUCCESS)
				goto EXIT_FUNCTION;
			for (count_1 = 0; count_1 < control_data.in_entry_order_count;
				count_1++) {
				if ((return_code = ADF_ReadEntry(&control_data,
					control_data.in_entry_order_list[count_1], NULL, area_list,
					error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				for (count_2 = 0; count_2 < ADF_AREA_COUNT; count_2++) {
					if (area_list[count_2].line_data == NULL)
						continue;
					STR_EMIT_CharLine('=', 78, NULL, NULL);
					definition_name = (area_list[count_2].section_name == NULL) ?
						"*** NULL ***" : area_list[count_2].section_name;
					if (area_list[count_2].line_number)
						printf("[%05u]:%10u:%s:%s\n", count_2,
							area_list[count_2].line_number,
							initcaps(ADF_GetAreaName(count_2, area_name)),
							definition_name);
					else
						printf("[%05u]:??????????:%s:%s\n", count_2,
							initcaps(ADF_GetAreaName(count_2, area_name)),
							definition_name);
					STR_EMIT_CharLine('-', 78, NULL, NULL);
					printf("[%s]\n", area_list[count_2].line_data);
				}
				fprintf(stderr, ".");
			}
		}
	}

EXIT_FUNCTION:

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	fprintf(stderr, "\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

