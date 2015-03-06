/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Loads the ADF entry directory and hyper-text
								directory from an ADF database file.

	Revision History	:	1994-05-14 --- Creation.
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

#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int  ADF_ReadEntryDirData,
	(ADF_CONTROL *control_ptr,
	ADF_IN_FILE *in_file_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_ReadEntryList,
	(ADF_CONTROL *control_ptr,
	ADF_IN_FILE *in_file_ptr, char **in_buffer, unsigned int *in_count,
	ADF_ENTRY **in_list, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_ReadHTextList,
	(ADF_CONTROL *control_ptr,
	ADF_IN_FILE *in_file_ptr, char **in_buffer, unsigned int *in_count,
	ADF_HTEXT **in_list, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_ReadDBList,
	(ADF_CONTROL *control_ptr, ADF_IN_FILE *in_file_ptr,
	const char *db_area_name, unsigned long data_offset,
	unsigned int data_length, unsigned int list_count,
	unsigned long list_offset, unsigned int in_file_size,
	unsigned int in_memory_size, char **in_buffer, unsigned int *in_count,
	void **in_memory_list, void **in_file_list, char *error_text));
COMPAT_FN_DECL_STATIC(void ADF_RemoveNewEntry,
	(unsigned int entry_index,
	unsigned int *entry_count, ADF_ENTRY **entry_list,
	unsigned int *htext_count, ADF_HTEXT **htext_list));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_LoadInFileList(ADF_CONTROL *control_ptr, char *error_text)
#else
int ADF_LoadInFileList(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;

	for (count_1 = 0; count_1 < control_ptr->in_file_name_count; count_1++) {
		if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr, "ADF database: %s --- ",
				control_ptr->in_file_name_list[count_1]);
		if ((return_code = ADF_OpenADFFileIn(control_ptr,
			control_ptr->in_file_name_list[count_1], error_text)) !=
			ADF_SUCCESS) {
			if (control_ptr->quiet_flag != ADF_TRUE)
				fprintf(stderr, "ERROR: %s\n", error_text);
			break;
		}
		else if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr, "OK\n");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_LoadHTextRefFileList(ADF_CONTROL *control_ptr, char *error_text)
#else
int ADF_LoadHTextRefFileList(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	char         *tmp_ptr;

	for (count_1 = 0; count_1 < control_ptr->htext_ref_file_name_count;
		count_1++) {
		if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr,
				"ADF external hyper-text reference database: %s --- ",
				control_ptr->htext_ref_file_name_list[count_1]);
		if (((tmp_ptr = strchr(control_ptr->htext_ref_file_name_list[count_1],
			'=')) == NULL) || (!(*(tmp_ptr + 1)))) {
			sprintf(error_text, "%s %s '%-.500s' is '%s'.",
				"The expected format for the external hyper-text reference ADF",
				"database file specification",
				control_ptr->htext_ref_file_name_list[count_1],
				"<ADF-database-file-name>=<hyper-text-reference-string>");
			return_code = ADF_FAILURE;
		}
		else {
			*tmp_ptr = '\0';
			return_code = ADF_OpenADFFileHTextRef(control_ptr,
				control_ptr->htext_ref_file_name_list[count_1], tmp_ptr + 1,
				error_text);
			*tmp_ptr = '=';
		}
		if (return_code != ADF_SUCCESS) {
			if (control_ptr->quiet_flag != ADF_TRUE)
				fprintf(stderr, "ERROR: %s\n", error_text);
			break;
		}
		else if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr, "OK\n");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OpenADFFileIn(ADF_CONTROL *control_ptr, const char *file_name,
	char *error_text)
#else
int ADF_OpenADFFileIn(control_ptr, file_name, error_text)
ADF_CONTROL *control_ptr;
const char  *file_name;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	char         *tmp_name    = NULL;
	unsigned int  count_1;
	unsigned int  count_2;
	ADF_IN_FILE   tmp_file;
   char          tmp_error_text[ADF_MAX_ERROR_TEXT];
	char          genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	ADF_INIT_InFilePtr(&tmp_file);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Get the fully-qualified name of the ADF database file . . .		*/
	/*	*****************************************************************	*/
	if (GEN_ExpandToFullPathName(file_name, &tmp_name, genfuncs_error_text) !=
		GENFUNCS_SUCCESS) {
		nstrcpy(error_text, genfuncs_error_text, ADF_MAX_ERROR_TEXT - 1);
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If we're executing under MS-DOS (or VMS), we'll need to map		*/
	/*	the file name to lower-case (or upper-case). This is because		*/
	/*	those operating systems are case-insensitive, so the only way we	*/
	/*	can reliably compare file names is by making their case canonical.*/
	/*	*****************************************************************	*/
#ifdef __MSDOS__
	lower(tmp_name);
#elif VMS
	upper(tmp_name);
#endif /* #ifdef __MSDOS__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Check to see if this ADF database file has already been loaded.*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < control_ptr->in_file_count; count_1++) {
		if (!strcmp(tmp_name, control_ptr->in_file_list[count_1].file_name)) {
			if (control_ptr->in_file_list[count_1].href_flag == ADF_TRUE) {
				control_ptr->in_file_list[count_1].href_flag = ADF_FALSE;
				for (count_2 = 0; count_2 < control_ptr->in_entry_count;
					count_2++) {
					if (control_ptr->in_entry_list[count_2].file_index == count_1)
						control_ptr->in_entry_list[count_2].href_flag = ADF_FALSE;
				}
				sprintf(tmp_error_text, "%s '%s' %s %s --- ignored.",
					"The ADF database file", tmp_name, "has already been opened",
					"as an external hyper-text reference ADF database file");
				if (control_ptr->log_flag == ADF_TRUE)
					MLOG_LogWarn(control_ptr->mlog_ptr, "%s\n", tmp_error_text);
				else
					fprintf(stderr, "WARNING: %s\n", tmp_error_text);
			}
			else if (control_ptr->log_flag == ADF_TRUE) {
				sprintf(tmp_error_text, "%s '%s' %s --- ignored.",
					"The ADF database file", tmp_name, "has already been opened.");
				if (control_ptr->log_flag == ADF_TRUE)
					MLOG_LogWarn(control_ptr->mlog_ptr, "%s\n", tmp_error_text);
				else
					fprintf(stderr, "WARNING: %s\n", tmp_error_text);
			}
			goto EXIT_FUNCTION;
		}
	}
	/*	*****************************************************************	*/

	if ((return_code =  ADF_OpenADFFile(control_ptr, tmp_name, NULL,
		&tmp_file, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	tmp_file.href_flag = ADF_FALSE;

	if ((!tmp_file.header.entry_list_count) ||
		((return_code = ADF_ReadEntryDirData(control_ptr, &tmp_file,
		error_text)) == ADF_SUCCESS) ||
		((return_code == ADF_PARSE_FAILURE) &&
		(control_ptr->cont_on_error_flag == ADF_TRUE))) {
		if (mema_append(&control_ptr->in_file_count,
			((void **) &control_ptr->in_file_list), &tmp_file,
			sizeof(tmp_file)) != STRFUNCS_SUCCESS) {
			STR_AllocMsgList(control_ptr->in_file_count + 1, sizeof(tmp_file),
				error_text, "%s '%-.500s' to the list of ADF database files",
				"Unable to add the ADF database file", tmp_name);
			return_code = ADF_MEMORY_FAILURE;
		}
	}

EXIT_FUNCTION:

	if (tmp_name != NULL)
		free(tmp_name);

	if ((return_code != ADF_SUCCESS) &&
		((return_code != ADF_PARSE_FAILURE) ||
		(control_ptr->cont_on_error_flag != ADF_TRUE)))
		ADF_FREE_InFileItem(&tmp_file);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OpenADFFileHTextRef(ADF_CONTROL *control_ptr, const char *file_name,
	const char *href_string, char *error_text)
#else
int ADF_OpenADFFileHTextRef(control_ptr, file_name, href_string, error_text)
ADF_CONTROL *control_ptr;
const char  *file_name;
const char  *href_string;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	char         *tmp_name    = NULL;
	unsigned int  count_1;
	ADF_IN_FILE   tmp_file;
	char          tmp_error_text[ADF_MAX_ERROR_TEXT];
	char          genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	ADF_INIT_InFilePtr(&tmp_file);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Get the fully-qualified name of the ADF database file . . .		*/
	/*	*****************************************************************	*/
	if (GEN_ExpandToFullPathName(file_name, &tmp_name, genfuncs_error_text) !=
		GENFUNCS_SUCCESS) {
		nstrcpy(error_text, genfuncs_error_text, ADF_MAX_ERROR_TEXT - 1);
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If we're executing under MS-DOS (or VMS), we'll need to map		*/
	/*	the file name to lower-case (or upper-case). This is because		*/
	/*	those operating systems are case-insensitive, so the only way we	*/
	/*	can reliably compare file names is by making their case canonical.*/
	/*	*****************************************************************	*/
#ifdef __MSDOS__
	lower(tmp_name);
#elif VMS
	upper(tmp_name);
#endif /* #ifdef __MSDOS__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Check to see if this ADF database file has already been loaded.*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < control_ptr->in_file_count; count_1++) {
		if (!strcmp(tmp_name, control_ptr->in_file_list[count_1].file_name)) {
			if (control_ptr->in_file_list[count_1].href_flag != ADF_TRUE) {
if (control_ptr->in_file_list[count_1].href_string != NULL)
	free(control_ptr->in_file_list[count_1].href_string);
control_ptr->in_file_list[count_1].href_string = strdup(href_string);
				sprintf(tmp_error_text, "%s '%s' %s --- ignored.",
					"The external hyper-text reference ADF database file",
					tmp_name,
					"has already been opened as a normal ADF database file");
				if (control_ptr->log_flag == ADF_TRUE)
					MLOG_LogWarn(control_ptr->mlog_ptr, "%s\n", tmp_error_text);
				else
					fprintf(stderr, "WARNING: %s\n", tmp_error_text);
			}
			else if (control_ptr->log_flag == ADF_TRUE) {
				sprintf(tmp_error_text, "%s '%s' %s --- ignored.",
					"The external hyper-text reference ADF database file",
					tmp_name, "has already been opened.");
				if (control_ptr->log_flag == ADF_TRUE)
					MLOG_LogWarn(control_ptr->mlog_ptr, "%s\n", tmp_error_text);
				else
					fprintf(stderr, "WARNING: %s\n", tmp_error_text);
			}
			goto EXIT_FUNCTION;
		}
	}
	/*	*****************************************************************	*/

	if ((return_code =  ADF_OpenADFFile(control_ptr, tmp_name, href_string,
		&tmp_file, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

#ifdef __MSDOS__
	while (*tmp_file.href_string &&
		((tmp_file.href_string[strlen(tmp_file.href_string) - 1] == '\\') ||
		(tmp_file.href_string[strlen(tmp_file.href_string) - 1] == '/')))
		tmp_file.href_string[strlen(tmp_file.href_string) - 1] = '\0';
#else
	while (*tmp_file.href_string &&
		(tmp_file.href_string[strlen(tmp_file.href_string) - 1] == '/'))
		tmp_file.href_string[strlen(tmp_file.href_string) - 1] = '\0';
#endif /* #ifdef __MSDOS__ */

	tmp_file.href_flag = ADF_TRUE;

	if ((!tmp_file.header.entry_list_count) ||
		((return_code = ADF_ReadEntryDirData(control_ptr, &tmp_file,
		error_text)) == ADF_SUCCESS) ||
		((return_code == ADF_PARSE_FAILURE) &&
		(control_ptr->cont_on_error_flag == ADF_TRUE))) {
		if (mema_append(&control_ptr->in_file_count,
			((void **) &control_ptr->in_file_list), &tmp_file,
			sizeof(tmp_file)) != STRFUNCS_SUCCESS) {
			STR_AllocMsgList(control_ptr->in_file_count + 1, sizeof(tmp_file),
				error_text, "%s '%-.500s' to the list of ADF database files",
		"Unable to add the external hyper-text reference ADF database file",
				tmp_name);
			return_code = ADF_MEMORY_FAILURE;
		}
	}

EXIT_FUNCTION:

	if (tmp_name != NULL)
		free(tmp_name);

	if ((return_code != ADF_SUCCESS) &&
		((return_code != ADF_PARSE_FAILURE) ||
		(control_ptr->cont_on_error_flag != ADF_TRUE)))
		ADF_FREE_InFileItem(&tmp_file);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OpenADFFile(ADF_CONTROL *control_ptr, const char *file_name,
	const char *href_string, ADF_IN_FILE *in_file_ptr, char *error_text)
#else
int ADF_OpenADFFile(control_ptr, file_name, href_string, in_file_ptr,
	error_text)
ADF_CONTROL *control_ptr;
const char  *file_name;
const char  *href_string;
ADF_IN_FILE *in_file_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned long file_size;
	char          tmp_error_text[ADF_MAX_ERROR_TEXT];

	ADF_INIT_InFilePtr(in_file_ptr);

	if ((in_file_ptr->file_name = strdup(file_name)) == NULL) {
		STR_AllocMsgItem(strlen(file_name) + 1, error_text,
			"Unable to copy the ADF database file name '%-.500s'", file_name);
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((href_string != NULL) &&
		((in_file_ptr->href_string = strdup(href_string)) == NULL)) {
		STR_AllocMsgItem(strlen(href_string) + 1, error_text, "%s %s '%-.500s'",
			"Unable to copy the external hyper-text reference ADF database file",
			"name", href_string);
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((in_file_ptr->file_ptr = ADF_fopen(file_name, "rb")) == NULL) {
		sprintf(error_text,
			"Unable to open ADF database file '%-.500s' for reading: ",
			file_name);
		ADF_GetLastErrorString(error_text);
		return_code = ADF_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	ADF_fseek(in_file_ptr->file_ptr, 0L, SEEK_END);
	file_size = ADF_ftell(in_file_ptr->file_ptr);
	ADF_fseek(in_file_ptr->file_ptr, 0L, SEEK_SET);

	if (file_size < (((unsigned long) ADF_FILE_PAGE_SIZE) +
		((unsigned long) sizeof(in_file_ptr->header)) +
		((unsigned long) strlen(ADF_DB_END_SIGNATURE)))) {
		sprintf(error_text, "%s '%-.500s' (%lu) %s (%lu).",
			"The length of the ADF database file", file_name, file_size,
			"is less than the minimum allowed for a valid ADF database file",
			(((unsigned long) ADF_FILE_PAGE_SIZE) +
			((unsigned long) sizeof(in_file_ptr->header)) +
			((unsigned long) strlen(ADF_DB_END_SIGNATURE))));
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}

	ADF_fseek(in_file_ptr->file_ptr, ((unsigned long) ADF_FILE_PAGE_SIZE),
		SEEK_SET);
	if ((return_code = ADF_FRead(&in_file_ptr->header,
		sizeof(in_file_ptr->header), 1, in_file_ptr->file_ptr,
		tmp_error_text)) != ADF_SUCCESS) {
		sprintf(error_text, "%s '%-.500s': %s",
			"Error occurred while reading from the ADF database file", file_name,
			tmp_error_text);
		goto EXIT_FUNCTION;
	}

	if (file_size != in_file_ptr->header.file_length) {
		sprintf(error_text, "%s '%-.500s' (%lu) %s (%lu).",
			"The length of the ADF database file", file_name, file_size,
			"is not equal to that recorded within the file",
			in_file_ptr->header.file_length);
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (strcmp(ADF_VERSION, in_file_ptr->header.version_number)) {
		sprintf(error_text, "%s '%-.500s' ('%-.*s') %s ('%s').",
			"The version of the ADF database file", file_name,
			((int) (sizeof(in_file_ptr->header.version_number) - 1)),
			in_file_ptr->header.version_number,
			"does not match the version number of this program",
			ADF_VERSION);
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (in_file_ptr->header.completion_flag != ADF_FILE_COMPLETE_FLAG) {
		sprintf(error_text, "%s '%-.500s' %s.",
			"The ADF database file", file_name, "was not closed normally");
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (in_file_ptr->header.area_count != ADF_AREA_COUNT) {
		sprintf(error_text, "%s '%-.500s' (%d) %s (%d).",
			"The number of ADF areas in the ADF database file", file_name,
			in_file_ptr->header.area_count,
			"does not match the number of ADF areas compiled into this program",
			ADF_AREA_COUNT);
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (in_file_ptr->header.sizeof_ADF_ENTRY_FILE != sizeof(ADF_ENTRY_FILE)) {
		sprintf(error_text, "%s '%s' %s '%-.500s' (%u) %s (%u).",
			"The size of the structure", "ADF_ENTRY_FILE",
			"indicated in the ADF database file", file_name,
			in_file_ptr->header.sizeof_ADF_ENTRY_FILE,
			"is not the same as that compiled into this program",
			sizeof(ADF_ENTRY_FILE));
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (in_file_ptr->header.sizeof_ADF_HTEXT_FILE != sizeof(ADF_HTEXT_FILE)) {
		sprintf(error_text, "%s '%s' %s '%-.500s' (%u) %s (%u).",
			"The size of the structure", "ADF_HTEXT_FILE",
			"indicated in the ADF database file", file_name,
			in_file_ptr->header.sizeof_ADF_HTEXT_FILE,
			"is not the same as that compiled into this program",
			sizeof(ADF_HTEXT_FILE));
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (in_file_ptr->header.sizeof_ADF_ENTRY_DATA_FILE !=
		sizeof(ADF_ENTRY_DATA_FILE)) {
		sprintf(error_text, "%s '%s' %s '%-.500s' (%u) %s (%u).",
			"The size of the structure", "ADF_ENTRY_DATA_FILE",
			"indicated in the ADF database file", file_name,
			in_file_ptr->header.sizeof_ADF_ENTRY_DATA_FILE,
			"is not the same as that compiled into this program",
			sizeof(ADF_ENTRY_DATA_FILE));
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}

	in_file_ptr->last_access_time = time(NULL);

EXIT_FUNCTION:

	if (return_code != ADF_SUCCESS)
		ADF_FREE_InFileItem(in_file_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_ReadEntryDirData(ADF_CONTROL *control_ptr,
	ADF_IN_FILE *in_file_ptr, char *error_text)
#else
static int ADF_ReadEntryDirData(control_ptr, in_file_ptr, error_text)
ADF_CONTROL *control_ptr;
ADF_IN_FILE *in_file_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code;
	char            *entry_buffer = NULL;
	char            *htext_buffer = NULL;
	unsigned int     entry_count  = 0;
	ADF_ENTRY       *entry_list   = NULL;
	unsigned int     htext_count  = 0;
	ADF_HTEXT       *htext_list   = NULL;
	const ADF_ENTRY *entry_ptr_1;
	const ADF_ENTRY *entry_ptr_2;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     count_3;
	unsigned int     found_index;
   void            *tmp_ptr;
	char             buffer_1[ADF_ENTRY_DESCRIP_LENGTH];
	char             buffer_2[ADF_ENTRY_DESCRIP_LENGTH];

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Load the entry directory from the ADF database file . . .		*/
	/*	*****************************************************************	*/
	if ((return_code = ADF_ReadEntryList(control_ptr, in_file_ptr,
		&entry_buffer, &entry_count, &entry_list, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Load the hypertext list from the ADF database file . . .			*/
	/*	*****************************************************************	*/
	if ((return_code = ADF_ReadHTextList(control_ptr, in_file_ptr,
		&htext_buffer, &htext_count, &htext_list, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Apply any entry include and exclude specifiers . . .				*/
	/*	*****************************************************************	*/
	if (control_ptr->entry_include_count || control_ptr->entry_exclude_count) {
		for (count_1 = 0; count_1 < entry_count; ) {
			if (ADF_ApplyCludesEntry(control_ptr, entry_list[count_1].base_name,
				entry_list[count_1].file_name, entry_list[count_1].file_type,
				entry_list[count_1].man_page) == ADF_TRUE)
				count_1++;
			else
				ADF_RemoveNewEntry(count_1, &entry_count, &entry_list,
					&htext_count, &htext_list);
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Apply any hypertext include and exclude specifiers . . .			*/
	/*	*****************************************************************	*/
	if (control_ptr->htext_include_count || control_ptr->htext_exclude_count) {
		for (count_1 = 0; count_1 < htext_count; ) {
			if (ADF_ApplyCludesHText(control_ptr,
				htext_list[count_1].hyper_text) == ADF_TRUE)
				count_1++;
			else
				mema_remove(&htext_count, ((void **) &htext_list),
					sizeof(ADF_HTEXT), count_1, 1);
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If no entries remain, we're finished.									*/
	/*	*****************************************************************	*/
	if (!entry_count)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Set the entries loaded to the type (normal or external hyper-	*/
	/*	text reference) of the ADF database file loaded . . .					*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < entry_count; count_1++)
		entry_list[count_1].href_flag = in_file_ptr->href_flag;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If no entries have been yet loaded, there's no lists against	*/
	/*	which the new entries need to be merged.									*/
	/*	*****************************************************************	*/
	if (!control_ptr->in_entry_count) {
		ADF_SORT_EntryList(ADF_SORT_ENTRY_BASE_NAME, entry_count,
			entry_list);
		ADF_SORT_HTextList(ADF_SORT_HTEXT_TEXT, htext_count,
			htext_list);
		control_ptr->in_entry_count = entry_count;
		control_ptr->in_entry_list  = entry_list;
		control_ptr->in_htext_count = htext_count;
		control_ptr->in_htext_list  = htext_list;
		entry_count                 = 0;
		entry_list                  = NULL;
		htext_count                 = 0;
		htext_list                  = NULL;
		in_file_ptr->entry_buffer   = entry_buffer;
		in_file_ptr->htext_buffer   = htext_buffer;
		entry_buffer                = NULL;
		htext_buffer                = NULL;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Otherwise, we'll need to ensure that there aren't any naming	*/
	/*	conflicts between the existing entry list and that just loaded.	*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < entry_count; ) {
		if (ADF_FIND_FindEntryByBaseName(control_ptr->in_entry_count,
			control_ptr->in_entry_list, entry_list[count_1].base_name,
			&found_index) != STRFUNCS_ITEM_FOUND) {
			count_1++;
			continue;
		}
		switch (control_ptr->duplicate_handling_type) {
			case ADF_DUP_HANDLER_FIRST	:
				ADF_RemoveNewEntry(count_1, &entry_count, &entry_list,
					&htext_count, &htext_list);
				break;
			case ADF_DUP_HANDLER_LAST	:
				ADF_RemoveExistingEntry(control_ptr, found_index);
				count_1++;
				break;
			default							:
				entry_ptr_1 = entry_list + count_1;
				entry_ptr_2 = control_ptr->in_entry_list + found_index;
				fprintf(stderr, "ERROR: The %s is the same as the %s.\n",
					ADF_DescribeInEntry(entry_ptr_1, in_file_ptr, buffer_1),
					ADF_DescribeInEntry(entry_ptr_2,
					control_ptr->in_file_list + entry_ptr_2->file_index,
					buffer_2));
				strcpy(error_text, "Base name conflicts encountered.");
				ADF_RemoveNewEntry(count_1, &entry_count, &entry_list,
					&htext_count, &htext_list);
				return_code = ADF_PARSE_FAILURE;
				break;
		}
		if ((return_code != ADF_SUCCESS) &&
			((return_code != ADF_PARSE_FAILURE) ||
			(control_ptr->cont_on_error_flag != ADF_TRUE)))
			goto EXIT_FUNCTION;
	}
	if (!entry_count)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We also need to ensure that the hypertext lists don't have any	*/
	/*	naming conflicts . . .															*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < htext_count; ) {
		if (ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
			control_ptr->in_htext_list, htext_list[count_1].hyper_text,
			&found_index) != STRFUNCS_ITEM_FOUND) {
			count_1++;
			continue;
		}
		switch (control_ptr->duplicate_handling_type) {
			case ADF_DUP_HANDLER_FIRST	:
				mema_remove(&htext_count, ((void **) &htext_list),
					sizeof(ADF_HTEXT), count_1, 1);
				break;
			case ADF_DUP_HANDLER_LAST	:
				mema_remove(&control_ptr->in_htext_count,
					((void **) &control_ptr->in_htext_list), sizeof(ADF_HTEXT),
					found_index, 1);
				count_1++;
				break;
			default							:
				entry_ptr_1 = ADF_FIND_LookUpEntryByEntry(entry_count, entry_list,
					htext_list[count_1].file_index,
					htext_list[count_1].entry_index, NULL);
				entry_ptr_2 =
					ADF_FIND_LookUpEntryByEntry(control_ptr->in_entry_count,
					control_ptr->in_entry_list,
					control_ptr->in_htext_list[found_index].file_index,
					control_ptr->in_htext_list[found_index].entry_index, NULL);
				fprintf(stderr,
					"ERROR: %s '%s' from %s is the same as one from %s.\n",
					"The hypertext string", htext_list[count_1].hyper_text,
					ADF_DescribeInEntry(entry_ptr_1, in_file_ptr, buffer_1),
					ADF_DescribeInEntry(entry_ptr_2,
					control_ptr->in_file_list + entry_ptr_2->file_index,
					buffer_2));
				strcpy(error_text, "Hypertext name conflicts encountered.");
				mema_remove(&htext_count, ((void **) &htext_list),
					sizeof(ADF_HTEXT), count_1, 1);
				return_code = ADF_PARSE_FAILURE;
				break;
		}
		if ((return_code != ADF_SUCCESS) &&
			((return_code != ADF_PARSE_FAILURE) ||
			(control_ptr->cont_on_error_flag != ADF_TRUE)))
			goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now we add the entries loaded to the existing entry list.		*/
	/*	*****************************************************************	*/
/*
	CODE NOTE: To be removed.
	if (mema_add(entry_count, entry_list, sizeof(ADF_ENTRY),
		&control_ptr->in_entry_count,
		((void **) &control_ptr->in_entry_list)) != STRFUNCS_SUCCESS) {
		STR_AllocMsgList(entry_count + control_ptr->in_entry_count,
			sizeof(ADF_ENTRY), error_text,
			"Unable to combine the loaded entry directory in memory");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	ADF_SORT_EntryList(ADF_SORT_ENTRY_BASE_NAME, control_ptr->in_entry_count,
		control_ptr->in_entry_list);
*/
	ADF_SORT_EntryList(ADF_SORT_ENTRY_BASE_NAME, entry_count, entry_list);
	if ((tmp_ptr = realloc(control_ptr->in_entry_list,
		(control_ptr->in_entry_count + entry_count) * sizeof(ADF_ENTRY))) ==
		NULL) {
		STR_AllocMsgList(entry_count + control_ptr->in_entry_count,
			sizeof(ADF_ENTRY), error_text,
			"Unable to combine the loaded entry directory in memory");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	count_1                    = 0;
	count_2                    = 0;
	control_ptr->in_entry_list = ((ADF_ENTRY *) tmp_ptr);
	while ((count_1 < control_ptr->in_entry_count) &&
		(count_2 < entry_count)) {
		for ( ; (count_1 < control_ptr->in_entry_count) &&
			(count_2 < entry_count) &&
			(strcmp(control_ptr->in_entry_list[count_1].base_name,
			entry_list[count_2].base_name) < 0); count_1++)
			;
		for ( ; (count_1 < control_ptr->in_entry_count) &&
			(count_2 < entry_count) &&
			(strcmp(control_ptr->in_entry_list[count_1].base_name,
			entry_list[count_2].base_name) > 0);
			count_1++, count_2++, control_ptr->in_entry_count++) {
			for (count_3 = control_ptr->in_entry_count; count_3 > count_1;
				count_3--)
				control_ptr->in_entry_list[count_3] =
					control_ptr->in_entry_list[count_3 - 1];
			control_ptr->in_entry_list[count_1] = entry_list[count_2];
		}
	}
	for ( ; count_2 < entry_count; count_2++)
		control_ptr->in_entry_list[control_ptr->in_entry_count++] =
			entry_list[count_2];
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now we add the hypertext list loaded to the existing hypertext	*/
	/*	list.																					*/
	/*	*****************************************************************	*/
/*
	CODE NOTE: To be removed.
	if (mema_add(htext_count, htext_list, sizeof(ADF_HTEXT),
		&control_ptr->in_htext_count,
		((void **) &control_ptr->in_htext_list)) != STRFUNCS_SUCCESS) {
		STR_AllocMsgList(htext_count + control_ptr->in_htext_count,
			sizeof(ADF_HTEXT), error_text,
			"Unable to combine the loaded hypertext list in memory");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	ADF_SORT_HTextList(ADF_SORT_HTEXT_TEXT, control_ptr->in_htext_count,
		control_ptr->in_htext_list);
*/
	ADF_SORT_HTextList(ADF_SORT_HTEXT_TEXT, htext_count, htext_list);
	if ((tmp_ptr = realloc(control_ptr->in_htext_list,
		(control_ptr->in_htext_count + htext_count) * sizeof(ADF_HTEXT))) ==
		NULL) {
		STR_AllocMsgList(htext_count + control_ptr->in_htext_count,
			sizeof(ADF_HTEXT), error_text,
			"Unable to combine the loaded hypertext list in memory");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	count_1                    = 0;
	count_2                    = 0;
	control_ptr->in_htext_list = ((ADF_HTEXT *) tmp_ptr);
	while ((count_1 < control_ptr->in_htext_count) &&
		(count_2 < htext_count)) {
		for ( ; (count_1 < control_ptr->in_htext_count) &&
			(count_2 < htext_count) &&
			(strcmp(control_ptr->in_htext_list[count_1].hyper_text,
			htext_list[count_2].hyper_text) < 0); count_1++)
			;
		for ( ; (count_1 < control_ptr->in_htext_count) &&
			(count_2 < htext_count) &&
			(strcmp(control_ptr->in_htext_list[count_1].hyper_text,
			htext_list[count_2].hyper_text) > 0);
			count_1++, count_2++, control_ptr->in_htext_count++) {
			for (count_3 = control_ptr->in_htext_count; count_3 > count_1;
				count_3--)
				control_ptr->in_htext_list[count_3] =
					control_ptr->in_htext_list[count_3 - 1];
			control_ptr->in_htext_list[count_1] = htext_list[count_2];
		}
	}
	for ( ; count_2 < htext_count; count_2++)
		control_ptr->in_htext_list[control_ptr->in_htext_count++] =
			htext_list[count_2];
	/*	*****************************************************************	*/

	in_file_ptr->entry_buffer = entry_buffer;
	in_file_ptr->htext_buffer = htext_buffer;
	entry_buffer              = NULL;
	htext_buffer              = NULL;

EXIT_FUNCTION:

	if (entry_buffer != NULL)
		free(entry_buffer);

	if (htext_buffer != NULL)
		free(htext_buffer);

	if (entry_list != NULL)
		free(entry_list);

	if (htext_list != NULL)
		free(htext_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_ReadEntryList(ADF_CONTROL *control_ptr,
	ADF_IN_FILE *in_file_ptr, char **in_buffer, unsigned int *in_count,
	ADF_ENTRY **in_list, char *error_text)
#else
static int ADF_ReadEntryList(control_ptr, in_file_ptr, in_buffer, in_count,
	in_list, error_text)
ADF_CONTROL   *control_ptr;
ADF_IN_FILE   *in_file_ptr;
char         **in_buffer;
unsigned int  *in_count;
ADF_ENTRY    **in_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code;
	ADF_ENTRY_FILE *tmp_list = NULL;
	ADF_ENTRY_FILE *file_ptr;
	ADF_ENTRY      *memory_ptr;
	unsigned int    count_1;

	if ((return_code = ADF_ReadDBList(control_ptr, in_file_ptr, "entry",
		in_file_ptr->header.entry_data_offset,
		in_file_ptr->header.entry_data_length,
		in_file_ptr->header.entry_list_count,
		in_file_ptr->header.entry_list_offset, sizeof(ADF_ENTRY_FILE),
		sizeof(ADF_ENTRY), in_buffer, in_count, ((void **) in_list),
		((void **) &tmp_list), error_text)) == ADF_SUCCESS) {
		for (count_1 = 0, file_ptr = tmp_list, memory_ptr = *in_list;
			count_1 < *in_count; count_1++, file_ptr++, memory_ptr++) {
			memory_ptr->file_index   = control_ptr->in_file_count;
			memory_ptr->entry_index  = file_ptr->entry_index;
			memory_ptr->entry_offset = file_ptr->entry_offset;
			memory_ptr->file_date    = file_ptr->file_date;
			memory_ptr->prep_date    = file_ptr->prep_date;
			memory_ptr->base_name    = *in_buffer + file_ptr->base_name_offset;
			memory_ptr->file_name    = *in_buffer + file_ptr->file_name_offset;
			memory_ptr->core_name    = *in_buffer + file_ptr->core_name_offset;
			memory_ptr->full_name    = *in_buffer + file_ptr->full_name_offset;
			memory_ptr->file_type    = *in_buffer + file_ptr->file_type_offset;
			memory_ptr->man_page     = *in_buffer + file_ptr->man_page_offset;
#ifdef TEST_MAIN
printf("[%05u]:%10u\n%10u\n%10lu\n[%s]\n[%s]\n[%s]\n%s\n",
	count_1,
	memory_ptr->file_index,
	memory_ptr->entry_index,
	memory_ptr->entry_offset,
	memory_ptr->base_name,
	memory_ptr->file_name,
	memory_ptr->file_type,
	"-----------------------------------------------------------------------");
fflush(stdout);
#endif /* #ifdef TEST_MAIN */
		}
	}

	if (tmp_list != NULL)
		free(tmp_list);

	return(return_code);
}
/*	***********************************************************************	*/

	/* In module 'infile.c'. */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_ReadHTextList(ADF_CONTROL *control_ptr,
	ADF_IN_FILE *in_file_ptr, char **in_buffer, unsigned int *in_count,
	ADF_HTEXT **in_list, char *error_text)
#else
static int ADF_ReadHTextList(control_ptr, in_file_ptr, in_buffer, in_count,
	in_list, error_text)
ADF_CONTROL   *control_ptr;
ADF_IN_FILE   *in_file_ptr;
char         **in_buffer;
unsigned int  *in_count;
ADF_HTEXT    **in_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code;
	ADF_HTEXT_FILE *tmp_list = NULL;
	ADF_HTEXT_FILE *file_ptr;
	ADF_HTEXT      *memory_ptr;
	unsigned int    count_1;

	if ((return_code = ADF_ReadDBList(control_ptr, in_file_ptr, "hyper-text",
		in_file_ptr->header.htext_data_offset,
		in_file_ptr->header.htext_data_length,
		in_file_ptr->header.htext_list_count,
		in_file_ptr->header.htext_list_offset, sizeof(ADF_HTEXT_FILE),
		sizeof(ADF_HTEXT), in_buffer, in_count, ((void **) in_list),
		((void **) &tmp_list), error_text)) == ADF_SUCCESS) {
		for (count_1 = 0, file_ptr = tmp_list, memory_ptr = *in_list;
			count_1 < *in_count; count_1++, file_ptr++, memory_ptr++) {
			memory_ptr->file_index     = control_ptr->in_file_count;
			memory_ptr->entry_index    = file_ptr->entry_index;
			memory_ptr->htext_length   = file_ptr->htext_length - 1;
			memory_ptr->hyper_text     = *in_buffer + file_ptr->htext_offset;
			memory_ptr->in_entry_index = 0;
#ifdef TEST_MAIN
printf("[%05u]:%10u\n%10u\n[%s]\n%s\n",
	count_1,
	memory_ptr->file_index,
	memory_ptr->entry_index,
	memory_ptr->hyper_text,
	"-----------------------------------------------------------------------");
fflush(stdout);
#endif /* #ifdef TEST_MAIN */
		}
	}

	if (tmp_list != NULL)
		free(tmp_list);

	return(return_code);
}
/*	***********************************************************************	*/

	/* In module 'infile.c'. */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_ReadDBList(ADF_CONTROL *control_ptr, ADF_IN_FILE *in_file_ptr,
	const char  *db_area_name, unsigned long data_offset,
	unsigned int data_length, unsigned int list_count, unsigned long list_offset,
	unsigned int in_file_size, unsigned int in_memory_size, char **in_buffer,
	unsigned int *in_count, void **in_memory_list, void **in_file_list,
	char *error_text)
#else
static int ADF_ReadDBList(control_ptr, in_file_ptr, db_area_name, data_offset,
	data_length, list_count, list_offset, in_file_size, in_memory_size,
	in_buffer, in_count, in_memory_list, in_file_list, error_text)
ADF_CONTROL   *control_ptr;
ADF_IN_FILE   *in_file_ptr;
const char    *db_area_name;
unsigned long  data_offset;
unsigned int   data_length;
unsigned int   list_count;
unsigned long  list_offset;
unsigned int   in_file_size;
unsigned int   in_memory_size;
char         **in_buffer;
unsigned int  *in_count;
void         **in_memory_list;
void         **in_file_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char tmp_error_text[ADF_MAX_ERROR_TEXT];

	*in_buffer      = NULL;
	*in_count       = 0;
	*in_file_list   = NULL;
	*in_memory_list = NULL;

	if ((*in_buffer = ((char *) calloc(data_length, sizeof(char)))) == NULL) {
		STR_AllocMsgItem(data_length, error_text,
	"Unable to allocate memory for the ADF database %s directory data area",
			db_area_name);
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	ADF_fseek(in_file_ptr->file_ptr, data_offset, SEEK_SET);

	if ((return_code = ADF_FRead(*in_buffer, sizeof(char), data_length,
		in_file_ptr->file_ptr, tmp_error_text)) != ADF_SUCCESS) {
		strcat(strcat(strcat(strcpy(error_text,
			"Unable to load the ADF database "), db_area_name),
			" directory data area: "), tmp_error_text);
		goto EXIT_FUNCTION;
	}

	if ((*in_file_list =
		((void *) calloc(list_count, in_file_size))) == NULL) {
		STR_AllocMsgList(list_count, in_file_size, error_text,
			"Unable to allocate memory for the temporary ADF database %s %s",
			db_area_name, "directory list");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	ADF_fseek(in_file_ptr->file_ptr, list_offset, SEEK_SET);

	if ((return_code = ADF_FRead(*in_file_list, in_file_size, list_count,
		in_file_ptr->file_ptr, tmp_error_text)) != ADF_SUCCESS) {
		strcat(strcat(strcat(strcpy(error_text,
			"Unable to load the temporary ADF database "), db_area_name),
			" directory list: "), tmp_error_text);
		goto EXIT_FUNCTION;
	}

	if ((*in_memory_list = ((void *) calloc(list_count, in_memory_size))) ==
		NULL) {
		STR_AllocMsgList(list_count, in_memory_size, error_text,
			"Unable to allocate memory for the ADF database %s directory list",
			db_area_name);
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	*in_count = list_count;

EXIT_FUNCTION:

	if (return_code != ADF_SUCCESS) {
		if (*in_buffer != NULL)
			free(*in_buffer);
		if (*in_file_list != NULL)
			free(*in_file_list);
		if (*in_memory_list != NULL)
			free(*in_memory_list);
		*in_buffer      = NULL;
		*in_count       = 0;
		*in_file_list   = NULL;
		*in_memory_list = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RemoveNewEntry(unsigned int entry_index,
	unsigned int *entry_count, ADF_ENTRY **entry_list,
	unsigned int *htext_count, ADF_HTEXT **htext_list)
#else
static void ADF_RemoveNewEntry(entry_index, entry_count, entry_list,
	htext_count, htext_list)
unsigned int   entry_index;
unsigned int  *entry_count;
ADF_ENTRY    **entry_list;
unsigned int  *htext_count;
ADF_HTEXT    **htext_list;
#endif /* #ifndef NARGS */
{
	ADF_RemoveHText(*entry_list + entry_index, htext_count, htext_list);

	mema_remove(entry_count, ((void **) entry_list), sizeof(**entry_list),
		entry_index, 1);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <memory.h>

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
	int          return_code      = ADF_SUCCESS;
	int          header_only_flag = ADF_FALSE;
	unsigned int count_1;
	ADF_CONTROL  control_data;
	char         date_buffer[100];
	char         error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for input ADF file functions\n");
	fprintf(stderr, "---- ------- --- ----- --- ---- ---------\n\n");

	ADF_INIT_Control(&control_data);

	control_data.cont_on_error_flag = ADF_TRUE;
	control_data.area_name_type     = ADF_AREA_NAME_TYPE_INTERNAL;
	control_data.area_order_type    = ADF_AREA_ORDER_TYPE_INTERNAL;

	if (argc < 2) {
		sprintf(error_text, "Invalid command line encountered.");
		fprintf(stderr,
			"USAGE:\n   %s %s %s\n", argv[0],
			"[-HEADER_ONLY={ ON | OFF | TRUE | FALSE | YES | NO }]",
			"<adf-db-file-name> [<adf-db-file-name>...]");
		return_code = ADF_BAD_ARGS_FAILURE;
	}
	else {
		for (count_1 = 1; count_1 < argc; count_1++) {
			if ((!stricmp(argv[count_1], "-HEADER_ONLY=ON")) ||
				(!stricmp(argv[count_1], "-HEADER_ONLY=TRUE")) ||
				(!stricmp(argv[count_1], "-HEADER_ONLY=YES"))) {
				header_only_flag = ADF_TRUE;
				continue;
			}
			if ((!stricmp(argv[count_1], "-HEADER_ONLY=OFF")) ||
				(!stricmp(argv[count_1], "-HEADER_ONLY=FALSE")) ||
				(!stricmp(argv[count_1], "-HEADER_ONLY=NO"))) {
				header_only_flag = ADF_FALSE;
				continue;
			}
			fprintf(stderr, "File: %s\n", argv[count_1]);
			if ((return_code = ADF_OpenADFFileIn(&control_data, argv[count_1],
				error_text)) != ADF_SUCCESS) {
				if (return_code != ADF_PARSE_FAILURE)
					break;
				fprintf(stderr, "%s\n", error_text);
				return_code = ADF_SUCCESS;
			}
		}
		if ((return_code != ADF_SUCCESS) || (!control_data.in_file_count))
			goto EXIT_FUNCTION;
		if (header_only_flag == ADF_TRUE) {
			printf("%s\n",
"==========================================================================");
			for (count_1 = 0; count_1 < control_data.in_file_count; count_1++) {
				printf("ADF Database Name       : %s\n",
					control_data.in_file_list[count_1].file_name);
				printf("Hyper-text String       : %s\n",
					(control_data.in_file_list[count_1].href_string == NULL) ? "" :
					control_data.in_file_list[count_1].href_string);
				printf("Hyper-text Flag         : %s\n",
					(control_data.in_file_list[count_1].href_flag) ? "YES" : "NO");
				printf("Creation Date           : %s\n",
					SDTIF_Format_time_t(&control_data.in_file_list[count_1].header.
					creation_date, date_buffer));
				printf("Update Date             : %s\n",
					SDTIF_Format_time_t(&control_data.in_file_list[count_1].header.
					update_date, date_buffer));
				printf("Version Number          : %s\n",
					control_data.in_file_list[count_1].header.version_number);
				printf("Area Count              : %10d\n",
					control_data.in_file_list[count_1].header.area_count);
				printf("ADF_ENTRY_FILE          : %10u\n",
					control_data.in_file_list[count_1].header.sizeof_ADF_ENTRY_FILE);
				printf("ADF_HTEXT_FILE          : %10u\n",
					control_data.in_file_list[count_1].header.sizeof_ADF_HTEXT_FILE);
				printf("ADF_ENTRY_DATA_FILE size: %10u\n",
					control_data.in_file_list[count_1].header.sizeof_ADF_ENTRY_DATA_FILE);
				printf("Completion Flag         : 0X%08lX\n",
					control_data.in_file_list[count_1].header.completion_flag);
				printf("File Length             : %10lu\n",
					control_data.in_file_list[count_1].header.file_length);
				printf("Entry Data Offset       : %10lu\n",
					control_data.in_file_list[count_1].header.entry_data_offset);
				printf("Entry Data Length       : %10u\n",
					control_data.in_file_list[count_1].header.entry_data_length);
				printf("Entry List Offset       : %10lu\n",
					control_data.in_file_list[count_1].header.entry_list_offset);
				printf("Entry List Length       : %10u\n",
					control_data.in_file_list[count_1].header.entry_list_length);
				printf("Entry List Count        : %10u\n",
					control_data.in_file_list[count_1].header.entry_list_count);
				printf("Hyper-text Data Offset  : %10lu\n",
					control_data.in_file_list[count_1].header.htext_data_offset);
				printf("Hyper-text Data Length  : %10u\n",
					control_data.in_file_list[count_1].header.htext_data_length);
				printf("Hyper-text List Offset  : %10lu\n",
					control_data.in_file_list[count_1].header.htext_list_offset);
				printf("Hyper-text List Length  : %10u\n",
					control_data.in_file_list[count_1].header.htext_list_length);
				printf("Hyper-text List Count   : %10u\n",
					control_data.in_file_list[count_1].header.htext_list_count);
				printf("%s\n",
"==========================================================================");
			}
			goto EXIT_FUNCTION;
		}
		printf("%s\n",
"==========================================================================");
		for (count_1 = 0; count_1 < control_data.in_entry_count; count_1++) {
			printf("[%05u]:%10u:%10u:%s:%s:%s:%s:%s", count_1,
				control_data.in_entry_list[count_1].file_index,
				control_data.in_entry_list[count_1].entry_index,
				control_data.in_entry_list[count_1].base_name,
				control_data.in_entry_list[count_1].file_name,
				control_data.in_entry_list[count_1].full_name,
				control_data.in_entry_list[count_1].file_type,
				control_data.in_entry_list[count_1].man_page);
			if (control_data.in_entry_list[count_1].href_flag == ADF_TRUE)
				printf(" (EXTERNAL REF = '%s')",
					control_data.in_file_list
					[control_data.in_entry_list[count_1].file_index].
					href_string);
			printf("\n");
fflush(stdout);
		}
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		for (count_1 = 0; count_1 < control_data.in_htext_count; count_1++)
			printf("[%05u]:%10u:%10u:%s\n", count_1,
				control_data.in_htext_list[count_1].file_index,
				control_data.in_htext_list[count_1].entry_index,
				control_data.in_htext_list[count_1].hyper_text);
		STR_EMIT_CharLine('=', 78, NULL, NULL);
fflush(stdout);
	}

EXIT_FUNCTION:

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

