/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the construction of an ADF database file.

	Revision History	:	1994-05-06 --- Creation.
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

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int ADF_WriteEntryDirList,
	(ADF_CONTROL *control_ptr, unsigned int entry_count,
	const ADF_ENTRY *entry_list, ADF_FILE_HEADER *header_ptr,
	char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_WriteHyperTextList,
	(ADF_CONTROL *control_ptr, unsigned int htext_count,
	const ADF_HTEXT *htext_list, ADF_FILE_HEADER *header_ptr,
	char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OpenADFFilePrep(ADF_CONTROL *control_ptr, const char *file_name,
	char *error_text)
#else
int ADF_OpenADFFilePrep(control_ptr, file_name, error_text)
ADF_CONTROL *control_ptr;
const char  *file_name;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code;
	ADF_FILE_HEADER header;

	ADF_CloseADFFilePrep(control_ptr);

	if ((control_ptr->prep_adf_file = ADF_fopen(file_name, "w+b")) == NULL) {
		sprintf(error_text,
			"Unable to open output ADF file '%-.500s' for writing: ",
			file_name);
		ADF_GetLastErrorString(error_text);
		return_code = ADF_SYSTEM_FAILURE;
	}
	else {
#ifndef __MSDOS__
# ifndef _Windows
		msetbuf(control_ptr->prep_adf_file, 1000000);
# endif /* #ifndef _Windows */
#endif /* #ifndef __MSDOS__ */
		memset(&header, '\0', sizeof(header));
		header.creation_date              = time(NULL);
		header.update_date                = header.creation_date;
		header.completion_flag            = ADF_FILE_INCOMPLETE_FLAG;
		header.area_count                 = ADF_AREA_COUNT;
		header.sizeof_ADF_ENTRY_FILE      = sizeof(ADF_ENTRY_FILE);
		header.sizeof_ADF_HTEXT_FILE      = sizeof(ADF_HTEXT_FILE);
		header.sizeof_ADF_ENTRY_DATA_FILE = sizeof(ADF_ENTRY_DATA_FILE);
		if ((return_code = ADF_WriteADFHumanHeader(control_ptr->prep_adf_file,
			&header, error_text)) == ADF_SUCCESS) {
			if ((return_code = ADF_PadFileBasic(control_ptr->prep_adf_file,
				((unsigned long) ADF_FILE_PAGE_SIZE), error_text)) ==
				ADF_SUCCESS)
				return_code = ADF_FWrite(&header, sizeof(header), 1,
					control_ptr->prep_adf_file, error_text);
		}
		if (return_code != ADF_SUCCESS) {
			ADF_fclose(control_ptr->prep_adf_file);
			control_ptr->prep_adf_file = NULL;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_CloseADFFilePrep(ADF_CONTROL *control_ptr)
#else
void ADF_CloseADFFilePrep(control_ptr)
ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	if (control_ptr->prep_adf_file != NULL) {
		ADF_fclose(control_ptr->prep_adf_file);
		control_ptr->prep_adf_file = NULL;
	}

	ADF_FreeEntryListPrep(control_ptr);
	ADF_FreeHTextListPrep(control_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_WriteADFHumanHeader(ADF_FILE *prep_adf_file_ptr,
	const ADF_FILE_HEADER *header_ptr, char *error_text)
#else
int ADF_WriteADFHumanHeader(prep_adf_file_ptr, header_ptr, error_text)
ADF_FILE              *prep_adf_file_ptr;
const ADF_FILE_HEADER *header_ptr;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char date_buffer[100];

	ADF_fflush(prep_adf_file_ptr);
	ADF_fseek(prep_adf_file_ptr, 0L, SEEK_SET);

	ADF_fprintf(prep_adf_file_ptr, "%s%s",
		ADF_DB_SIGNATURE_1, ADF_END_OF_LINE_CHAR);
	ADF_fprintf(prep_adf_file_ptr, "%s%s%s",
		ADF_DB_SIGNATURE_2, ADF_END_OF_LINE_CHAR, ADF_END_OF_LINE_CHAR);
	ADF_fprintf(prep_adf_file_ptr, "%s: %s%s",
		"Version Number", ADF_VERSION, ADF_END_OF_LINE_CHAR);
	ADF_fprintf(prep_adf_file_ptr, "%s: %s%s",
		"Creation Date ", SDTIF_Format_time_t(&header_ptr->creation_date,
		date_buffer), ADF_END_OF_LINE_CHAR);
	ADF_fprintf(prep_adf_file_ptr, "%s: %s%s",
		"Update Date   ", SDTIF_Format_time_t(&header_ptr->update_date,
		date_buffer), ADF_END_OF_LINE_CHAR);
	ADF_fprintf(prep_adf_file_ptr, "%s%s%s%s%c",
		ADF_END_OF_LINE_CHAR, ADF_DB_COPYRIGHT, ADF_END_OF_LINE_CHAR,
		ADF_END_OF_LINE_CHAR, 26);

	if ((return_code = ADF_PadFileBasic(prep_adf_file_ptr,
		((unsigned long) ADF_FILE_PAGE_SIZE), error_text)) == ADF_SUCCESS)
		ADF_fflush(prep_adf_file_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_AddToPrepList(ADF_CONTROL *control_ptr, const char *base_name,
	const char *file_name, const char *core_name, const char *full_name,
	const char *file_type, const char *man_page, const time_t *file_date,
	const time_t *prep_date, const ADF_DOMAIN *domain_ptr,
	const ADF_SOURCE_DATA *area_list, unsigned int publish_xref_count,
	char **publish_xref_list, char *error_text)
#else
int ADF_AddToPrepList(control_ptr, base_name, file_name, core_name, full_name,
	file_type, man_page, file_date, prep_date, domain_ptr, area_list,
	publish_xref_count, publish_xref_list, error_text)
ADF_CONTROL            *control_ptr;
const char             *base_name;
const char             *file_name;
const char             *core_name;
const char             *full_name;
const char             *file_type;
const char             *man_page;
const time_t           *file_date;
const time_t           *prep_date;
const ADF_DOMAIN       *domain_ptr;
const ADF_SOURCE_DATA  *area_list;
unsigned int            publish_xref_count;
char                  **publish_xref_list;
char                   *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code;
	unsigned int     count_1;
	unsigned int     entry_index;
	unsigned int     htext_index;
	ADF_ENTRY       *entry_ptr;
	const ADF_ENTRY *found_entry_ptr;
	ADF_ENTRY        tmp_entry;
	ADF_HTEXT        tmp_htext;
	char             buffer_1[ADF_ENTRY_DESCRIP_LENGTH];
	char             buffer_2[ADF_ENTRY_DESCRIP_LENGTH];

/*
	CODE NOTE: 'full_name' is to be removed from the structure 'ADF_ENTRY'.
*/
#ifdef __MSDOS__
	full_name = "?";
#endif /* #ifdef __MSDOS__ */

	memset(&tmp_entry, '\0', sizeof(tmp_entry));
	memset(&tmp_htext, '\0', sizeof(tmp_htext));

	tmp_entry.file_index  = 0;
	tmp_entry.entry_index = control_ptr->prep_entry_count;
	tmp_entry.base_name   = NULL;
	tmp_entry.file_name   = NULL;
	tmp_entry.core_name   = NULL;
	tmp_entry.file_type   = NULL;
	tmp_entry.man_page    = NULL;
	tmp_htext.hyper_text  = NULL;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Instantiate the entry data . . .											*/
	/*	*****************************************************************	*/
	if ((return_code = ADF_AllocateEntryItem(&tmp_entry, base_name, file_name,
		core_name, full_name, file_type, man_page, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Make sure that no duplicate entry base names get into the		*/
	/*	entry list . . .																	*/
	/*	*****************************************************************	*/
	if (ADF_FIND_FindEntryByBaseName(control_ptr->prep_entry_count,
		control_ptr->prep_entry_list, tmp_entry.base_name, &entry_index) ==
		STRFUNCS_ITEM_FOUND) {
		switch (control_ptr->duplicate_handling_type) {
			case ADF_DUP_HANDLER_FIRST	:
				goto EXIT_FUNCTION;
			case ADF_DUP_HANDLER_LAST	:
				ADF_FreeEntryItem(control_ptr->prep_entry_list + entry_index);
				mema_remove(&control_ptr->prep_entry_count,
					((void **) &control_ptr->prep_entry_list), sizeof(ADF_ENTRY),
					entry_index, 1);
				tmp_entry.entry_index = control_ptr->prep_entry_count;
				break;
			default							:
				found_entry_ptr = ((const ADF_ENTRY *)
					control_ptr->prep_entry_list) + entry_index;
				fprintf(stderr, "ERROR: The %s is the same as the %s.\n",
					ADF_DescribeEntry(&tmp_entry, buffer_1),
					ADF_DescribeEntry(found_entry_ptr, buffer_2));
				strcpy(error_text, "Base name conflicts encountered.");
				return_code = ADF_PARSE_FAILURE;
				goto EXIT_FUNCTION;
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Insert the entry into the entry list.									*/
	/*	*****************************************************************	*/
	tmp_entry.file_date = *file_date;
	tmp_entry.prep_date = *prep_date;
	if (mema_insert(&control_ptr->prep_entry_count,
		((void **) &control_ptr->prep_entry_list), &tmp_entry,
		sizeof(tmp_entry), entry_index) != STRFUNCS_SUCCESS) {
		STR_AllocMsgList(control_ptr->prep_entry_count + 1, sizeof(tmp_entry),
			error_text, "Unable to add the ADF file directory entry");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	entry_ptr = control_ptr->prep_entry_list + entry_index;

	tmp_entry.base_name = NULL;
	tmp_entry.file_name = NULL;
	tmp_entry.core_name = NULL;
	tmp_entry.full_name = NULL;
	tmp_entry.file_type = NULL;
	tmp_entry.man_page  = NULL;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Insert the hyper-text strings associated with this entry into	*/
	/*	hyper-text list, but ensure that no duplicate hyper-text strings	*/
	/*	are processed . . .																*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < publish_xref_count; count_1++) {
		if (ADF_FIND_FindHTextByText(control_ptr->prep_htext_count,
			control_ptr->prep_htext_list, publish_xref_list[count_1],
			&htext_index) == STRFUNCS_ITEM_FOUND) {
			switch (control_ptr->duplicate_handling_type) {
				case ADF_DUP_HANDLER_FIRST	:
					continue;
				case ADF_DUP_HANDLER_LAST	:
					free(control_ptr->prep_htext_list[htext_index].hyper_text);
					mema_remove(&control_ptr->prep_htext_count,
						((void **) &control_ptr->prep_htext_list),
						sizeof(ADF_HTEXT), htext_index, 1);
					break;
				default							:
					found_entry_ptr =
						ADF_FIND_LookUpEntryByEntry(control_ptr->prep_entry_count,
						control_ptr->prep_entry_list,
						control_ptr->prep_htext_list[htext_index].file_index,
						control_ptr->prep_htext_list[htext_index].entry_index, NULL);
					fprintf(stderr,
						"ERROR: %s '%s' from %s is the same as one from %s.\n",
						"The hypertext string", publish_xref_list[count_1],
						ADF_DescribeEntry(entry_ptr, buffer_1),
						ADF_DescribeEntry(found_entry_ptr, buffer_2));
					if ((control_ptr->ignore_bad_cmnt_flag != ADF_TRUE) &&
						(control_ptr->cont_on_error_flag != ADF_TRUE)) {
						/*	********************************************	*/
						/*	********************************************	*/
						/*		Free the other hyper-text list elements	*/
						/*	already inserted for this entry . . .			*/
						/*	********************************************	*/
						while (count_1) {
							count_1--;
							if (ADF_FIND_FindHTextByText(
								control_ptr->prep_htext_count,
								control_ptr->prep_htext_list,
								publish_xref_list[count_1], &htext_index) ==
								STRFUNCS_ITEM_FOUND)
								free(control_ptr->prep_htext_list[htext_index].
									hyper_text);
								mema_remove(&control_ptr->prep_htext_count,
									((void **) &control_ptr->prep_htext_list),
									sizeof(ADF_HTEXT), htext_index, 1);
						}
						/*	********************************************	*/
						strcpy(error_text, "Hypertext name conflicts encountered.");
						return_code = ADF_PARSE_FAILURE;
						goto EXIT_FUNCTION;
					}
					continue;
			}
		}
		tmp_htext.entry_index = entry_ptr->entry_index;
		if ((return_code = ADF_AllocateHTextItem(&tmp_htext,
			publish_xref_list[count_1], error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		if (mema_insert(&control_ptr->prep_htext_count,
			((void **) &control_ptr->prep_htext_list), &tmp_htext,
			sizeof(tmp_htext), htext_index) != STRFUNCS_SUCCESS) {
			STR_AllocMsgList(control_ptr->prep_htext_count + 1,
				sizeof(tmp_htext), error_text,
				"Unable to add the ADF file hyper-text entry");
			return_code = ADF_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		tmp_htext.hyper_text = NULL;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now write the entry data to the ADF database file . . .			*/
	/*	*****************************************************************	*/
	return_code = ADF_WriteEntry(control_ptr, entry_ptr, area_list,
		error_text);
	/*	*****************************************************************	*/

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
	if (tmp_entry.man_page != NULL)
		free(tmp_entry.man_page);
	if (tmp_htext.hyper_text != NULL)
		free(tmp_htext.hyper_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_WriteTrailer(ADF_CONTROL *control_ptr, unsigned int entry_count,
	const ADF_ENTRY *entry_list, unsigned int htext_count,
	const ADF_HTEXT *htext_list, char *error_text)
#else
int ADF_WriteTrailer(control_ptr, entry_count, entry_list, htext_count,
	htext_list, error_text)
ADF_CONTROL     *control_ptr;
unsigned int     entry_count;
const ADF_ENTRY *entry_list;
unsigned int     htext_count;
const ADF_HTEXT *htext_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code;
	ADF_FILE_HEADER header_1;
	ADF_FILE_HEADER header_2;

	memset(&header_1, '\0', sizeof(header_1));

	ADF_SORT_EntryList(control_ptr->sort_order_type,
		control_ptr->prep_entry_count, control_ptr->prep_entry_list);

	if ((return_code = ADF_WriteEntryDirList(control_ptr, entry_count,
		entry_list, &header_1, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = ADF_WriteHyperTextList(control_ptr, htext_count,
		htext_list, &header_1, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = ADF_FWrite(ADF_DB_END_SIGNATURE, 1,
		strlen(ADF_DB_END_SIGNATURE), control_ptr->prep_adf_file,
		error_text)) !=ADF_SUCCESS)
		goto EXIT_FUNCTION;

	ADF_fflush(control_ptr->prep_adf_file);
	ADF_fseek(control_ptr->prep_adf_file, 0L, SEEK_END);
	header_1.file_length = ADF_ftell(control_ptr->prep_adf_file);

	ADF_fseek(control_ptr->prep_adf_file, ((unsigned long) ADF_FILE_PAGE_SIZE),
		SEEK_SET);

	if ((return_code = ADF_FRead(&header_2, sizeof(header_2), 1,
		control_ptr->prep_adf_file, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	header_2.completion_flag   = ADF_FILE_COMPLETE_FLAG;
	header_2.file_length       = header_1.file_length;
	header_2.entry_data_offset = header_1.entry_data_offset;
	header_2.entry_data_length = header_1.entry_data_length;
	header_2.entry_list_offset = header_1.entry_list_offset;
	header_2.entry_list_length = header_1.entry_list_length;
	header_2.entry_list_count  = header_1.entry_list_count;
	header_2.htext_data_offset = header_1.htext_data_offset;
	header_2.htext_data_length = header_1.htext_data_length;
	header_2.htext_list_offset = header_1.htext_list_offset;
	header_2.htext_list_length = header_1.htext_list_length;
	header_2.htext_list_count  = header_1.htext_list_count;

	nstrcpy(header_2.version_number, ADF_VERSION,
		sizeof(header_2.version_number) - 1);

	ADF_fseek(control_ptr->prep_adf_file, ((unsigned long) ADF_FILE_PAGE_SIZE),
		SEEK_SET);

	if ((return_code = ADF_FWrite(&header_2, sizeof(header_2), 1,
		control_ptr->prep_adf_file, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	ADF_fflush(control_ptr->prep_adf_file);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

	/* Module 'prepfile.c'. */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_WriteEntryDirList(ADF_CONTROL *control_ptr,
	unsigned int entry_count, const ADF_ENTRY *entry_list,
	ADF_FILE_HEADER *header_ptr, char *error_text)
#else
static int ADF_WriteEntryDirList(control_ptr, entry_count, entry_list,
	header_ptr, error_text)
ADF_CONTROL     *control_ptr;
unsigned int     entry_count;
const ADF_ENTRY *entry_list;
ADF_FILE_HEADER *header_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code;
	unsigned int    current_offset = 0;
	unsigned int    count_1;
	ADF_ENTRY      *in_dir;
	ADF_ENTRY_FILE  tmp_dir;

	header_ptr->entry_data_offset = 0L;
	header_ptr->entry_data_length = 0;
	header_ptr->entry_list_offset = 0L;
	header_ptr->entry_list_length = 0;
	header_ptr->entry_list_count  = 0;

	if ((return_code = ADF_PadFile(control_ptr->prep_adf_file, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

	header_ptr->entry_data_offset = ADF_ftell(control_ptr->prep_adf_file);

	for (count_1 = 0; count_1 < entry_count; count_1++) {
		in_dir = ((ADF_ENTRY *) entry_list) + count_1;
		if ((return_code = ADF_FWrite(in_dir->base_name, 1,
			strlen(in_dir->base_name) + 1, control_ptr->prep_adf_file,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = ADF_FWrite(in_dir->file_name, 1,
			strlen(in_dir->file_name) + 1, control_ptr->prep_adf_file,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = ADF_FWrite(in_dir->core_name, 1,
			strlen(in_dir->core_name) + 1, control_ptr->prep_adf_file,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = ADF_FWrite(in_dir->full_name, 1,
			strlen(in_dir->full_name) + 1, control_ptr->prep_adf_file,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = ADF_FWrite(in_dir->file_type, 1,
			strlen(in_dir->file_type) + 1, control_ptr->prep_adf_file,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = ADF_FWrite(in_dir->man_page, 1,
			strlen(in_dir->man_page) + 1, control_ptr->prep_adf_file,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
	}

#ifdef __MSDOS__
	if ((ADF_ftell(control_ptr->prep_adf_file) -
		header_ptr->entry_data_offset) > ((unsigned long) (UINT_MAX - 15))) {
		sprintf(error_text, "%s (%lu) exceeds the maximum (%lu).",
			"The size of the ADF database entry directory data area",
			ADF_ftell(control_ptr->prep_adf_file) -
			header_ptr->entry_data_offset, ((unsigned long) (UINT_MAX - 15)));
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
#endif /* #ifdef __MSDOS__ */

	header_ptr->entry_data_length =
		((unsigned int) (ADF_ftell(control_ptr->prep_adf_file) -
		header_ptr->entry_data_offset));

	if ((return_code = ADF_PadFile(control_ptr->prep_adf_file, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

	header_ptr->entry_list_offset = ADF_ftell(control_ptr->prep_adf_file);

	for (count_1 = 0; count_1 < entry_count; count_1++) {
		in_dir                    = ((ADF_ENTRY *) entry_list) + count_1;
		tmp_dir.file_index        = in_dir->file_index;
		tmp_dir.entry_index       = in_dir->entry_index;
		tmp_dir.entry_offset      = in_dir->entry_offset;
		tmp_dir.file_date         = in_dir->file_date;
		tmp_dir.prep_date         = in_dir->prep_date;
/*
	CODE NOTE: To be deleted.
		tmp_dir.base_name_length  = strlen(in_dir->base_name) + 1;
		tmp_dir.file_name_length  = strlen(in_dir->file_name) + 1;
		tmp_dir.core_name_length  = strlen(in_dir->core_name) + 1;
		tmp_dir.full_name_length  = strlen(in_dir->full_name) + 1;
		tmp_dir.file_type_length  = strlen(in_dir->file_type) + 1;
		tmp_dir.man_page_length   = strlen(in_dir->man_page) + 1;
		tmp_dir.base_name_offset  = current_offset;
		tmp_dir.file_name_offset  = tmp_dir.base_name_offset +
			tmp_dir.base_name_length;
		tmp_dir.core_name_offset  = tmp_dir.file_name_offset +
			tmp_dir.file_name_length;
		tmp_dir.full_name_offset  = tmp_dir.core_name_offset +
			tmp_dir.core_name_length;
		tmp_dir.file_type_offset  = tmp_dir.full_name_offset +
			tmp_dir.full_name_length;
		tmp_dir.man_page_offset   = tmp_dir.file_type_offset +
			tmp_dir.file_type_length;
		current_offset           += tmp_dir.base_name_length +
			tmp_dir.file_name_length + tmp_dir.core_name_length +
			tmp_dir.full_name_length + tmp_dir.file_type_length +
			tmp_dir.man_page_length;
*/
		tmp_dir.base_name_offset  = current_offset;
		tmp_dir.file_name_offset  = tmp_dir.base_name_offset +
			strlen(in_dir->base_name) + 1;
		tmp_dir.core_name_offset  = tmp_dir.file_name_offset +
			strlen(in_dir->file_name) + 1;
		tmp_dir.full_name_offset  = tmp_dir.core_name_offset +
			strlen(in_dir->core_name) + 1;
		tmp_dir.file_type_offset  = tmp_dir.full_name_offset +
			strlen(in_dir->full_name) + 1;
		tmp_dir.man_page_offset   = tmp_dir.file_type_offset +
			strlen(in_dir->file_type) + 1;
		current_offset            = tmp_dir.man_page_offset +
			strlen(in_dir->man_page) + 1;
		if ((return_code = ADF_FWrite(&tmp_dir, sizeof(tmp_dir), 1,
			control_ptr->prep_adf_file, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
	}

#ifdef __MSDOS__
	if ((ADF_ftell(control_ptr->prep_adf_file) -
		header_ptr->entry_list_offset) > ((unsigned long) (UINT_MAX - 15))) {
		sprintf(error_text, "%s (%u elements * %u size = %lu) %s (%lu).",
			"The size of the ADF database entry directory list", entry_count,
			sizeof(ADF_ENTRY_FILE), "exceeds the maximum",
			ADF_ftell(control_ptr->prep_adf_file) -
			header_ptr->entry_list_offset, ((unsigned long) (UINT_MAX - 15)));
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
#endif /* #ifdef __MSDOS__ */

	header_ptr->entry_list_length =
		((unsigned int) (ADF_ftell(control_ptr->prep_adf_file) -
		header_ptr->entry_list_offset));

	header_ptr->entry_list_count  = entry_count;

	if ((return_code = ADF_PadFile(control_ptr->prep_adf_file, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

	ADF_fflush(control_ptr->prep_adf_file);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

	/* Module 'prepfile.c'. */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_WriteHyperTextList(ADF_CONTROL *control_ptr,
	unsigned int htext_count, const ADF_HTEXT *htext_list,
	ADF_FILE_HEADER *header_ptr, char *error_text)
#else
static int ADF_WriteHyperTextList(control_ptr, htext_count, htext_list,
	header_ptr, error_text)
ADF_CONTROL     *control_ptr;
unsigned int     htext_count;
const ADF_HTEXT *htext_list;
ADF_FILE_HEADER *header_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code;
	unsigned int    current_offset = 0;
	unsigned int    count_1;
	ADF_HTEXT      *in_htext;
	ADF_HTEXT_FILE  tmp_htext;

	header_ptr->htext_data_offset = 0L;
	header_ptr->htext_data_length = 0;
	header_ptr->htext_list_offset = 0L;
	header_ptr->htext_list_length = 0;
	header_ptr->htext_list_count  = 0;

	if ((return_code = ADF_PadFile(control_ptr->prep_adf_file, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

	header_ptr->htext_data_offset = ADF_ftell(control_ptr->prep_adf_file);

	for (count_1 = 0; count_1 < htext_count; count_1++) {
		in_htext = ((ADF_HTEXT *) htext_list) + count_1;
		if ((return_code = ADF_FWrite(in_htext->hyper_text, 1,
			strlen(in_htext->hyper_text) + 1, control_ptr->prep_adf_file,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
	}

#ifdef __MSDOS__
	if ((ADF_ftell(control_ptr->prep_adf_file) -
		header_ptr->htext_data_offset) > ((unsigned long) (UINT_MAX - 15))) {
		sprintf(error_text, "%s (%lu) exceeds the maximum (%lu).",
			"The size of the ADF database hyper-text directory data area",
			ADF_ftell(control_ptr->prep_adf_file) -
			header_ptr->htext_data_offset, ((unsigned long) (UINT_MAX - 15)));
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
#endif /* #ifdef __MSDOS__ */

	header_ptr->htext_data_length =
		((unsigned int) (ADF_ftell(control_ptr->prep_adf_file) -
		header_ptr->htext_data_offset));

	if ((return_code = ADF_PadFile(control_ptr->prep_adf_file, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

	header_ptr->htext_list_offset = ADF_ftell(control_ptr->prep_adf_file);

	for (count_1 = 0; count_1 < htext_count; count_1++) {
		in_htext                = ((ADF_HTEXT *) htext_list) + count_1;
		tmp_htext.file_index    = in_htext->file_index;
		tmp_htext.entry_index   = in_htext->entry_index;
		tmp_htext.htext_length  = strlen(in_htext->hyper_text) + 1;
		tmp_htext.htext_offset  = current_offset;
		current_offset         += tmp_htext.htext_length;
		if ((return_code = ADF_FWrite(&tmp_htext, sizeof(tmp_htext), 1,
			control_ptr->prep_adf_file, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
	}

#ifdef __MSDOS__
	if ((ADF_ftell(control_ptr->prep_adf_file) -
		header_ptr->htext_list_offset) > ((unsigned long) (UINT_MAX - 15))) {
		sprintf(error_text, "%s (%u elements * %u size = %lu) %s (%lu).",
			"The size of the ADF database hyper-text directory list", htext_count,
			sizeof(ADF_HTEXT_FILE), "exceeds the maximum",
			ADF_ftell(control_ptr->prep_adf_file) -
			header_ptr->htext_list_offset, ((unsigned long) (UINT_MAX - 15)));
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
#endif /* #ifdef __MSDOS__ */

	header_ptr->htext_list_length =
		((unsigned int) (ADF_ftell(control_ptr->prep_adf_file) -
		header_ptr->htext_list_offset));

	header_ptr->htext_list_count  = htext_count;

	if ((return_code = ADF_PadFile(control_ptr->prep_adf_file, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

	ADF_fflush(control_ptr->prep_adf_file);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <memory.h>

#define ADF_PREP_FILE_NAME					"PREPFILE.adf"

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	ADF_CONTROL   control_data;
	unsigned int  domain_count;
	ADF_DOMAIN   *domain_list;
	char          error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for ADF preparation file functions\n");
	fprintf(stderr, "---- ------- --- --- ----------- ---- ---------\n\n");

	ADF_INIT_Control(&control_data);

	if (argc < 2) {
		sprintf(error_text, "Invalid command line encountered.");
		fprintf(stderr,
			"USAGE:\n   %s <file-name> [<file-name>...]\n", argv[0]);
		return_code = ADF_BAD_ARGS_FAILURE;
	}
	else {
		ADF_GetDefaultDefSpec(&domain_count, &domain_list);
		if ((return_code = ADF_OpenADFFilePrep(&control_data,
			ADF_PREP_FILE_NAME, error_text)) == ADF_SUCCESS) {
			control_data.check_only_flag      = ADF_FALSE;
			control_data.cont_on_error_flag   = ADF_TRUE;
			control_data.ignore_bad_cmnt_flag = ADF_TRUE;
			control_data.area_name_type       = ADF_AREA_NAME_TYPE_INTERNAL;
			control_data.area_order_type      = ADF_AREA_ORDER_TYPE_INTERNAL;
			for (count_1 = 1; count_1 < argc; count_1++) {
				if ((return_code = ADF_DoSource(&control_data, domain_count,
					domain_list, argv[count_1], error_text)) != ADF_SUCCESS) {
					fprintf(stderr, "ERROR: %s\n", error_text);
					if (return_code != ADF_PARSE_FAILURE)
						break;
				}
				return_code = ADF_SUCCESS;
			}
			return_code = ADF_WriteTrailer(&control_data,
				control_data.prep_entry_count, control_data.prep_entry_list,
				control_data.prep_htext_count, control_data.prep_htext_list,
				error_text);
			ADF_CloseADFFilePrep(&control_data);
		}
	}

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

