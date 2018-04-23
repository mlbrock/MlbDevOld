/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages processing of a source file by ADF.

	Revision History	:	1995-04-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
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
COMPAT_FN_DECL_STATIC(int ADF_ParseBOHSpec,
	(ADF_CONTROL *control_ptr, unsigned int domain_count,
	const ADF_DOMAIN *domain_list, const char *file_name,
	unsigned int line_number, char *boh_spec_ptr, ADF_DOMAIN **domain_ptr,
	char **file_type, char **man_page, char **tab_setting, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_DoSourceComment,
	(ADF_CONTROL *control_ptr, const char *file_name, const char *core_name,
	const char *full_name, const char *file_type, const char *man_page,
	const char *tab_setting, const time_t *file_date,
	const ADF_DOMAIN *domain_ptr, unsigned int start_line,
	unsigned int line_count, char **line_list, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_ProcessComment,
	(ADF_CONTROL *control_ptr, const char *file_name, const char *core_name,
	const char *full_name, const char *file_type, const char *man_page,
	const char *tab_setting, const time_t *file_date, unsigned int start_line,
	const ADF_DOMAIN *domain_ptr, ADF_SOURCE_DATA *area_list,
	char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_GetAreaData,
	(ADF_CONTROL *control_ptr, const ADF_AREA *area_def_ptr,
	const ADF_DOMAIN *domain_ptr, ADF_SOURCE_DATA *area_ptr,
	unsigned int *publish_xref_count, char ***publish_xref_list,
	char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_AddParagraph,
	(unsigned int *line_count, char ***line_list, const char *para_format,
	const char *line_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_AppendParagraph,
	(char **line_list_ptr, const char *add_line_ptr, const char *append_char,
	char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_DoCharFormat,
	(char **in_line, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_ApplyDefaultString,
	(ADF_SOURCE_DATA *area_ptr, unsigned int area_index,
	const char *default_string, int forced_flag, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_CheckForAdd,
	(ADF_CONTROL *control_ptr, const ADF_SOURCE_DATA *area_list,
	const char *file_name, const char *core_name, const char *full_name,
	const char *file_type, const char *man_page, const time_t *file_date,
	int *add_entry_flag, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DECL const ADF_AREA ADF_AreaNameList[];
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_DoSource(ADF_CONTROL *control_ptr, unsigned int domain_count,
	const ADF_DOMAIN *domain_list, const char *in_file_name, char *error_text)
#else
int ADF_DoSource(control_ptr, domain_count, domain_list, in_file_name,
	error_text)
ADF_CONTROL      *control_ptr;
unsigned int      domain_count;
const ADF_DOMAIN *domain_list;
const char       *in_file_name;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code    = ADF_SUCCESS;
	unsigned int       line_count     = 0;
	char             **line_list      = NULL;
	ADF_BIG_char      *line_buffer    = NULL;
	unsigned int       comment_count  = 0;
	char              *tmp_file_name  = NULL;
	char              *core_name      = NULL;
	unsigned int       count_1;
	unsigned int       count_2;
	unsigned int       boh_line;
	unsigned int       eoh_line;
   char              *boh_spec_ptr;
   unsigned int       boh_spec_index;
	char              *tmp_ptr;
	const char        *base_file_name;
	const char        *file_type;
	char              *this_file_type;
	const ADF_DOMAIN  *domain_ptr;
	ADF_DOMAIN        *this_domain_ptr;
	char              *man_page;
	char              *this_man_page;
	char              *tab_setting;
	char              *this_tab_setting;
	struct stat        stat_data;
	char               genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	man_page    = ADF_DEFAULT_MAN_PAGE;
	tab_setting = ADF_DEFAULT_TAB_STRING;

	if (control_ptr->quiet_flag != ADF_TRUE)
		fprintf(stderr, "PREP: %s\n", in_file_name);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Get the fully-qualified source file name.								*/
	/*	*****************************************************************	*/
	if (GEN_ExpandToFullPathName(in_file_name, &tmp_file_name,
		genfuncs_error_text) != GENFUNCS_SUCCESS) {
		nstrcpy(error_text, genfuncs_error_text, ADF_MAX_ERROR_TEXT - 1);
		if (control_ptr->log_flag == ADF_TRUE)
			MLOG_LogErr(control_ptr->mlog_ptr, "%s: %s\n", in_file_name,
				genfuncs_error_text);
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
	upper(tmp_file_name);
#elif VMS
	upper(tmp_file_name);
#endif /* #ifdef __MSDOS__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We need the file type (or file extension) to determine which	*/
	/*	domain to use.																		*/
	/*	*****************************************************************	*/
	if (((file_type = strrchr(tmp_file_name, '.')) == NULL) ||
		(!file_type[1])) {
		sprintf(error_text, "File '%-.500s%s' does not have a file extension.",
			tmp_file_name, (strlen(tmp_file_name) > 500) ? "<MORE>" : "");
		if (control_ptr->log_flag == ADF_TRUE)
			MLOG_LogErr(control_ptr->mlog_ptr,
				"%s: does not have a file extension.\n", tmp_file_name);
		return_code = ADF_PARSE_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We need to get the file name without such things as the drive	*/
	/*	specification or directory hierarchy. Different for each OS . . .	*/
	/*	*****************************************************************	*/
#ifdef __MSDOS__
	base_file_name = ((tmp_ptr = strrchr(tmp_file_name, ':')) != NULL)   ?
		(tmp_ptr + 1) : tmp_file_name;
	base_file_name = ((tmp_ptr = strrchr(base_file_name, '\\')) != NULL) ?
		(tmp_ptr + 1) : base_file_name;
	base_file_name = ((tmp_ptr = strrchr(base_file_name, '/')) != NULL)  ?
		(tmp_ptr + 1) : base_file_name;
#elif _Windows
	base_file_name = ((tmp_ptr = strrchr(tmp_file_name, ':')) != NULL)   ?
		(tmp_ptr + 1) : tmp_file_name;
	base_file_name = ((tmp_ptr = strrchr(base_file_name, '\\')) != NULL) ?
		(tmp_ptr + 1) : base_file_name;
	base_file_name = ((tmp_ptr = strrchr(base_file_name, '/')) != NULL)  ?
		(tmp_ptr + 1) : base_file_name;
#elif _VMS_
	base_file_name = ((tmp_ptr = strrchr(tmp_file_name, ']')) != NULL)   ?
		(tmp_ptr + 1) : tmp_file_name;
#else
	base_file_name = ((tmp_ptr = strrchr(tmp_file_name, '/')) != NULL)   ?
		(tmp_ptr + 1) : tmp_file_name;
#endif /* #ifdef __MSDOS__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Get the file name without leading drive specification and		*/
	/*	directory hierarchy or trailing file extension . . .					*/
	/*	*****************************************************************	*/
	if ((core_name = strdup(base_file_name)) == NULL) {
		STR_AllocMsgItem(strlen(base_file_name) + 1, error_text,
			"Unable to allocate memory for the core file name");
		if (control_ptr->log_flag == ADF_TRUE)
			MLOG_LogErr(control_ptr->mlog_ptr, "%s: %s\n", tmp_file_name,
				error_text);
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	if ((tmp_ptr = strrchr(core_name, '.')) != NULL)
		*tmp_ptr = '\0';
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Use the file type to determine the domain to be used . . .		*/
	/*	*****************************************************************	*/
	if ((domain_ptr = ADF_FIND_Domain(domain_count, domain_list, ++file_type,
		NULL)) == NULL) {
		sprintf(error_text,
			"File '%-.500s%s' has an unknown file extension ('%-.20s%s').",
			tmp_file_name, (strlen(tmp_file_name) > 500) ? "<MORE>" : "",
			file_type, (strlen(file_type) >  20) ? "<MORE>" : "");
		if (control_ptr->log_flag == ADF_TRUE)
			MLOG_LogErr(control_ptr->mlog_ptr,
				"%s: has an unknown file extension ('%s').\n", tmp_file_name,
				file_type);
		return_code = ADF_PARSE_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Determine the last modification date of the file . . .			*/
	/*	*****************************************************************	*/
	if (stat(tmp_file_name, &stat_data)) {
		if (control_ptr->log_flag == ADF_TRUE) {
			*error_text = '\0';
			ADF_GetLastErrorString(error_text);
			MLOG_LogErr(control_ptr->mlog_ptr,
				"%s: Attempt to 'stat()' file failed: %s", tmp_file_name,
				error_text);
		}
		sprintf(error_text, "Unable to 'stat()' file '%-.500s': ",
			tmp_file_name);
		ADF_GetLastErrorString(error_text);
		return_code = ADF_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Load the file into memory . . .											*/
	/*	*****************************************************************	*/
	if ((return_code = ADF_ReadSourceFile(tmp_file_name, &line_count,
		&line_list, &line_buffer, error_text)) != ADF_SUCCESS) {
		if (control_ptr->log_flag == ADF_TRUE)
			MLOG_LogErr(control_ptr->mlog_ptr, "%s: %s\n", tmp_file_name,
				error_text);
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If we can't find the pattern optimization string for the			*/
	/*	beginning of the ADF comment header in the file, don't bother		*/
	/*	doing the search . . .															*/
	/*	*****************************************************************	*/
/*
	CODE NOTE: To be removed.
	if ((domain_ptr->boh_pattern.pattern_optimization != NULL) &&
		(STRFUNCS_SHIM_memimem(line_buffer_length, line_buffer,
		strlen(domain_ptr->boh_pattern.pattern_optimization),
		domain_ptr->boh_pattern.pattern_optimization) == NULL))
		line_count = 0;
*/
	/*	*****************************************************************	*/

	for (count_1 = 0; count_1 < line_count; count_1++) {
		if (ADF_MatchPatternPtr(line_list[count_1], &domain_ptr->boh_pattern,
			&boh_spec_index) == ADF_TRUE) {
			comment_count++;
			this_file_type   = ((char *) file_type);
			this_domain_ptr  = ((ADF_DOMAIN *) domain_ptr);
			this_man_page    = ((char *) man_page);
			this_tab_setting = ((char *) tab_setting);
         boh_line         = count_1;
			eoh_line         = 0;
			boh_spec_ptr     = line_list[count_1] + boh_spec_index;
			if ((return_code = ADF_ParseBOHSpec(control_ptr, domain_count,
				domain_list, tmp_file_name, boh_line, boh_spec_ptr,
				&this_domain_ptr, &this_file_type, &this_man_page,
				&this_tab_setting, error_text)) != ADF_SUCCESS) {
				if ((control_ptr->ignore_bad_cmnt_flag != ADF_TRUE) &&
					(control_ptr->cont_on_error_flag != ADF_TRUE)) {
					if (control_ptr->log_flag == ADF_TRUE)
						MLOG_LogErr(control_ptr->mlog_ptr, "%s: %s\n", tmp_file_name,
							error_text);
					else if (control_ptr->quiet_flag != ADF_TRUE)
						fprintf(stderr, ">>> ERROR  : %s\n", error_text);
					return_code = ADF_PARSE_FAILURE;
					goto EXIT_FUNCTION;
				}
				if (control_ptr->log_flag == ADF_TRUE)
					MLOG_LogWarn(control_ptr->mlog_ptr, "%s: %s\n", tmp_file_name,
						error_text);
				else if (control_ptr->quiet_flag != ADF_TRUE)
					fprintf(stderr, ">>> WARNING: %s\n", error_text);
				continue;
			}
			for (count_2 = count_1; count_2 < line_count; count_2++) {
				if (ADF_MatchPatternPtr(line_list[count_2],
					&domain_ptr->eoh_pattern, NULL) == ADF_TRUE) {
					eoh_line = count_2;
					break;
				}
			}
			if (!eoh_line) {
				sprintf(error_text, "%s %u %s.",
					"The beginning-of-header at line number", boh_line + 1,
					"had no corresponding end-of-header");
				if ((control_ptr->ignore_bad_cmnt_flag != ADF_TRUE) &&
					(control_ptr->cont_on_error_flag != ADF_TRUE)) {
					if (control_ptr->log_flag == ADF_TRUE)
						MLOG_LogErr(control_ptr->mlog_ptr, "%s: %s\n", tmp_file_name,
							error_text);
					else if (control_ptr->quiet_flag != ADF_TRUE)
						fprintf(stderr, ">>> ERROR  : %s\n", error_text);
					return_code = ADF_PARSE_FAILURE;
					goto EXIT_FUNCTION;
				}
				if (control_ptr->log_flag == ADF_TRUE)
					MLOG_LogWarn(control_ptr->mlog_ptr, "%s: %s\n", tmp_file_name,
						error_text);
				else if (control_ptr->quiet_flag != ADF_TRUE)
					fprintf(stderr, ">>> WARNING: %s\n", error_text);
				continue;
			}
			if ((return_code = ADF_DoSourceComment(control_ptr, base_file_name,
				core_name, tmp_file_name, this_file_type, this_man_page,
				this_tab_setting, &stat_data.st_mtime, this_domain_ptr,
				boh_line + 1, (eoh_line - boh_line) - 1, line_list + boh_line + 1,
				error_text)) != ADF_SUCCESS) {
				if ((return_code != ADF_PARSE_FAILURE) ||
					((return_code == ADF_PARSE_FAILURE) &&
					(control_ptr->ignore_bad_cmnt_flag != ADF_TRUE) &&
					(control_ptr->cont_on_error_flag != ADF_TRUE))) {
					if (control_ptr->log_flag == ADF_TRUE)
						MLOG_LogErr(control_ptr->mlog_ptr, "%s: %s\n", tmp_file_name,
							error_text);
					else if (control_ptr->quiet_flag != ADF_TRUE)
						fprintf(stderr, ">>> ERROR  : %s\n", error_text);
					goto EXIT_FUNCTION;
				}
				if (control_ptr->log_flag == ADF_TRUE)
					MLOG_LogWarn(control_ptr->mlog_ptr, "%s: %s\n", tmp_file_name,
						error_text);
				else if (control_ptr->quiet_flag != ADF_TRUE)
					fprintf(stderr, ">>> WARNING: %s\n", error_text);
				return_code = ADF_SUCCESS;
			}
			count_1 = eoh_line;
		}
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		The user may have requested a warning message for those source	*/
	/*	files which do not contain ADF comments . . .							*/
	/*	*****************************************************************	*/
	if ((!comment_count) &&
		(control_ptr->error_on_no_comment_flag == ADF_TRUE)) {
		if (control_ptr->log_flag == ADF_TRUE)
			MLOG_LogWarn(control_ptr->mlog_ptr,
				"%s: No ADF comment sections in file.\n", tmp_file_name);
		else if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr, ">>> WARNING: No ADF comment sections in file.\n");
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (tmp_file_name != NULL)
		free(tmp_file_name);
	if (core_name != NULL)
		free(core_name);
	if (line_list != NULL)
		free(line_list);
	if (line_buffer != NULL)
		ADF_BIG_free(line_buffer);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_ParseBOHSpec(ADF_CONTROL *control_ptr, unsigned int domain_count,
	const ADF_DOMAIN *domain_list, const char *file_name,
	unsigned int line_number, char *boh_spec_ptr, ADF_DOMAIN **domain_ptr,
	char **file_type, char **man_page, char **tab_setting, char *error_text)
#else
static int ADF_ParseBOHSpec(control_ptr, domain_count, domain_list, file_name,
	line_number, boh_spec_ptr, domain_ptr, file_type, man_page, tab_setting,
	error_text)
ADF_CONTROL       *control_ptr;
unsigned int       domain_count;
const ADF_DOMAIN  *domain_list;
const char        *file_name;
unsigned int       line_number;
char              *boh_spec_ptr;
ADF_DOMAIN       **domain_ptr;
char             **file_type;
char             **man_page;
char             **tab_setting;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	char         *tmp_ptr;
	char          tmp_error_text[ADF_MAX_ERROR_TEXT];

	trim(nocontrl(oneblank(boh_spec_ptr)));

	for (count_1 = 0; (count_1 < ADF_BOH_SPEC_COUNT) && *boh_spec_ptr;
		count_1++) {
		if ((tmp_ptr = strchr(boh_spec_ptr, ',')) != NULL)
			*tmp_ptr = '\0';
		if (*trim(boh_spec_ptr)) {
			switch (count_1) {
				case ADF_BOH_SPEC_FILE_TYPE	:
					boh_spec_ptr += (*boh_spec_ptr == '.') ? 1 : 0;
					if (stricmp(boh_spec_ptr, *file_type) && ((*domain_ptr =
						((ADF_DOMAIN *) ADF_FIND_Domain(domain_count, domain_list,
						boh_spec_ptr, NULL))) != NULL))
						*file_type = boh_spec_ptr;
					else {
						sprintf(error_text, "%s %u %s '%-.500s'%s %s ('%-.20s%s').",
							"The ADF comment beginning at line number",
							line_number + 1, "in file", file_name,
							(strlen(file_name) > 500) ? "<MORE>" : "",
							"has an unknown file extension", boh_spec_ptr,
							(strlen(boh_spec_ptr) >  20) ? "<MORE>" : "");
						return_code = ADF_PARSE_FAILURE;
					}
					break;
				case ADF_BOH_SPEC_MAN_PAGE		:
					if ((return_code = ADF_ValidateManPage(boh_spec_ptr,
						tmp_error_text)) == ADF_SUCCESS)
						*man_page = boh_spec_ptr;
					else {
						sprintf(error_text,
							"%s %u %s '%-.500s'%s %s ('%-.20s%s'): %s",
							"The ADF comment beginning at line number",
							line_number + 1, "in file", file_name,
							(strlen(file_name) > 500) ? "<MORE>" : "",
							"has an unknown man page", boh_spec_ptr,
							(strlen(boh_spec_ptr) >  20) ? "<MORE>" : "",
							tmp_error_text);
						return_code = ADF_PARSE_FAILURE;
					}
					break;
				case ADF_BOH_SPEC_TAB_SETTING	:
					if ((str_digit(boh_spec_ptr, 0) == NULL) && atoi(boh_spec_ptr))
						*tab_setting = boh_spec_ptr;
					else {
						sprintf(error_text,
							"%s %u %s '%-.500s'%s %s ('%-.20s%s'): %s",
							"The ADF comment beginning at line number",
							line_number + 1, "in file", file_name,
							(strlen(file_name) > 500) ? "<MORE>" : "",
							"has an invalid tab setting", boh_spec_ptr,
							(strlen(boh_spec_ptr) >  20) ? "<MORE>" : "",
							tmp_error_text);
						return_code = ADF_PARSE_FAILURE;
					}
					break;
				default	:
					break;
			}
			if (return_code != ADF_SUCCESS)
				break;
		}
		if (tmp_ptr == NULL)
			break;
		boh_spec_ptr = tmp_ptr + 1;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_DoSourceComment(ADF_CONTROL *control_ptr, const char *file_name,
	const char *core_name, const char *full_name, const char *file_type,
	const char *man_page, const char *tab_setting, const time_t *file_date,
	const ADF_DOMAIN *domain_ptr, unsigned int start_line,
	unsigned int line_count, char **line_list, char *error_text)
#else
static int ADF_DoSourceComment(control_ptr, file_name, core_name, full_name,
	file_type, man_page, tab_setting, file_date, domain_ptr, start_line,
	line_count, line_list, error_text)
ADF_CONTROL       *control_ptr;
const char        *file_name;
const char        *core_name;
const char        *full_name;
const char        *file_type;
const char        *man_page;
const char        *tab_setting;
const time_t      *file_date;
const ADF_DOMAIN  *domain_ptr;
unsigned int       start_line;
unsigned int       line_count;
char             **line_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code;
	int              end_flag;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     count_3;
	unsigned int     strip_index;
	unsigned int     start_position;
	ADF_SECTION     *section_ptr;
	ADF_SOURCE_DATA  area_list[ADF_AREA_COUNT];
	ADF_SOURCE_DATA *area_ptr;

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

	for (count_1 = 0; count_1 < domain_ptr->section_count; count_1++) {
		section_ptr = domain_ptr->section_list + count_1;
		for (count_2 = 0; count_2 < line_count; count_2++) {
			if (ADF_MatchPatternPtr(line_list[count_2],
				&domain_ptr->strip_pattern, &strip_index) == ADF_TRUE)
				line_list[count_2] += strip_index;
			if (ADF_MatchPatternPtr(line_list[count_2],
				&section_ptr->match_pattern, &start_position) == ADF_TRUE) {
				area_ptr                 = area_list + section_ptr->area_index;
				area_ptr->section_ptr    = section_ptr;
				area_ptr->section_index  = count_1;
				area_ptr->section_name   = section_ptr->output_section_name;
				area_ptr->start_position = start_position;
				area_ptr->line_number    = start_line + count_2 + 1;
				area_ptr->line_count     = 1;
				area_ptr->line_list      = line_list + count_2;
				end_flag                 = ADF_FALSE;
				count_2++;
				while (count_2 < line_count) {
					for (count_3 = 0; count_3 < domain_ptr->section_count;
						count_3++) {
						if (count_1 == count_3)
							continue;
						section_ptr = domain_ptr->section_list + count_3;
						if (ADF_MatchPatternPtr(line_list[count_2],
							&section_ptr->match_pattern, NULL) == ADF_TRUE) {
							end_flag = ADF_TRUE;
							break;
						}
					}
					if (end_flag == ADF_TRUE)
						break;
					area_ptr->line_count++;
					count_2++;
				}
				break;
			}
		}
	}

	if ((return_code = ADF_ProcessComment(control_ptr, file_name, core_name,
		full_name, file_type, man_page, tab_setting, file_date, start_line,
		domain_ptr, area_list, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

#ifdef TEST_MAIN
for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
char area_name[ADF_AREA_NAME_LENGTH + 1];
	if (area_list[count_1].line_data != NULL) {
		printf(
"========================================================================\n");
		if (area_list[count_1].section_ptr != NULL)
			printf("[%05u]:%10u:%s\n", count_1,
				area_list[count_1].line_number,
				initcaps(ADF_GetAreaName(count_1, area_name)));
		else
			printf("[%05u]:??????????:%s\n", count_1,
				initcaps(ADF_GetAreaName(count_1, area_name)));
		printf(
"------------------------------------------------------------------------\n");
		printf("[%s]\n", area_list[count_1].line_data);
	}
}
#endif /* #ifdef TEST_MAIN */

EXIT_FUNCTION:

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		if (area_list[count_1].line_data != NULL)
			free(area_list[count_1].line_data);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_ProcessComment(ADF_CONTROL *control_ptr, const char *file_name,
	const char *core_name, const char *full_name, const char *file_type,
	const char *man_page, const char *tab_setting, const time_t *file_date,
	unsigned int start_line, const ADF_DOMAIN *domain_ptr,
	ADF_SOURCE_DATA *area_list, char *error_text)
#else
static int ADF_ProcessComment(control_ptr, file_name, core_name, full_name,
	file_type, man_page, tab_setting, file_date, start_line, domain_ptr,
	area_list, error_text)
ADF_CONTROL      *control_ptr;
const char       *file_name;
const char       *core_name;
const char       *full_name;
const char       *file_type;
const char       *man_page;
const char       *tab_setting;
const time_t     *file_date;
unsigned int      start_line;
const ADF_DOMAIN *domain_ptr;
ADF_SOURCE_DATA  *area_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code        = ADF_SUCCESS;
	unsigned int   publish_xref_count = 0;
	char         **publish_xref_list  = NULL;
	int            tmp_return_code;
	unsigned int   count_1;
	unsigned int   found_index;
	unsigned int   found_length;
	char          *tmp_ptr_1;
   char          *tmp_ptr_2;
	time_t         prep_date;
	int            add_entry_flag;
	char           date_buffer[100];
	char           area_name[ADF_AREA_NAME_LENGTH + 1];
	char           tmp_error_text[ADF_MAX_ERROR_TEXT * 2];

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Get the data from each of the sections in the ADF comment.		*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		if (area_list[count_1].line_count) {
			if ((tmp_return_code = ADF_GetAreaData(control_ptr,
				ADF_AreaNameList + count_1, domain_ptr, area_list + count_1,
				&publish_xref_count, &publish_xref_list, error_text)) !=
				ADF_SUCCESS) {
				return_code = tmp_return_code;
				goto EXIT_FUNCTION;
			}
      }
		if ((area_list[count_1].section_ptr != NULL) &&
			(area_list[count_1].section_ptr->required_flag == ADF_TRUE) &&
			(area_list[count_1].line_data == NULL)) {
			return_code = ADF_PARSE_FAILURE;
			sprintf(tmp_error_text,
				"%s: Area '%s' (area index %u, %s '%s') %s %s.",
				full_name, upper(ADF_GetAreaName(count_1, area_name)), count_1,
				"section name", area_list[count_1].section_ptr->section_name,
				"is a required section, but no text was found in the",
				"source file");
			if ((control_ptr->ignore_bad_cmnt_flag != ADF_TRUE) &&
				(control_ptr->cont_on_error_flag != ADF_TRUE)) {
				if (control_ptr->log_flag == ADF_TRUE)
					MLOG_LogErr(control_ptr->mlog_ptr, "%s\n", tmp_error_text);
				else if (control_ptr->quiet_flag != ADF_TRUE)
					fprintf(stderr, ">>> ERROR  :%s\n", tmp_error_text);
				sprintf(error_text, "Missing required sections in file '%-.500s'.",
					full_name);
				goto EXIT_FUNCTION;
			}
			if (control_ptr->log_flag == ADF_TRUE)
				MLOG_LogWarn(control_ptr->mlog_ptr, "%s\n", tmp_error_text);
			else if (control_ptr->quiet_flag != ADF_TRUE)
				fprintf(stderr, ">>> WARNING:%s\n", tmp_error_text);
			sprintf(error_text, "Missing required sections in file '%-.500s'.",
				full_name);
		}
	}
	if (return_code != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Fix up the ADF entry base name . . .									*/
	/*	*****************************************************************	*/
	if (area_list[ADF_AREA_BASE_NAME].line_data != NULL) {
		if ((area_list[ADF_AREA_NAME].line_data == NULL) &&
			((area_list[ADF_AREA_NAME].line_data =
			strdup(area_list[ADF_AREA_BASE_NAME].line_data)) == NULL)) {
			STR_AllocMsgItem(strlen(area_list[ADF_AREA_BASE_NAME].line_data) + 1,
				error_text, "Unable to allocate memory for the name string");
			return_code = ADF_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	else if (area_list[ADF_AREA_NAME].line_data != NULL) {
		if ((area_list[ADF_AREA_BASE_NAME].line_data == NULL) &&
			((area_list[ADF_AREA_BASE_NAME].line_data =
			strdup(area_list[ADF_AREA_NAME].line_data)) == NULL)) {
			STR_AllocMsgItem(strlen(area_list[ADF_AREA_NAME].line_data) + 1,
				error_text, "Unable to allocate memory for the base name string");
			return_code = ADF_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	else {
		sprintf(error_text, "%s which begins at line number %u.",
			"No name component found in the comment section", start_line);
		return_code = ADF_PARSE_FAILURE;
		goto EXIT_FUNCTION;
	}
	trim(oneblank(ctltospc(area_list[ADF_AREA_BASE_NAME].line_data)));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Ensure that the base name is in the hyper-text list, and make	*/
	/*	the hyper-text list unique . . .												*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < publish_xref_count; count_1++)
		trim(oneblank(ctltospc(publish_xref_list[count_1])));
	strl_sort(publish_xref_count, publish_xref_list);
	if ((strl_find(publish_xref_count, publish_xref_list,
		area_list[ADF_AREA_BASE_NAME].line_data, &found_index) !=
		STRFUNCS_ITEM_FOUND) && (strl_insert(&publish_xref_count,
		&publish_xref_list, area_list[ADF_AREA_BASE_NAME].line_data,
		found_index) == STRFUNCS_FAILURE)) {
		STR_AllocMsgItem(strlen(area_list[ADF_AREA_NAME].line_data) + 1,
			error_text,
			"Unable to copy the base name string to the hyper-text list");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	strl_uniq(&publish_xref_count, &publish_xref_list);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Ensure that no published names for this entry are included in	*/
	/*	the 'SEE_ALSO' area . . .														*/
	/*	*****************************************************************	*/
	if (area_list[ADF_AREA_SEE_ALSO].line_data != NULL) {
		for (count_1 = 0; count_1 < publish_xref_count; count_1++) {
			tmp_ptr_1 = area_list[ADF_AREA_SEE_ALSO].line_data;
			while ((tmp_ptr_2 = strstr(tmp_ptr_1, publish_xref_list[count_1])) !=
				NULL) {
				found_length = strlen(publish_xref_list[count_1]);
				if (((tmp_ptr_2 == area_list[ADF_AREA_SEE_ALSO].line_data) ||
					(*(tmp_ptr_2 - 1) == '\n')) && ((!tmp_ptr_2[found_length]) ||
					(tmp_ptr_2[found_length] == '\n'))) {
					found_length +=
						(((tmp_ptr_2 == area_list[ADF_AREA_SEE_ALSO].line_data) &&
						(!tmp_ptr_2[found_length])) ? 0 : 1);
					tmp_ptr_2    -=
						((tmp_ptr_2 == area_list[ADF_AREA_SEE_ALSO].line_data) ?
						0 : 1);
					strdele(area_list[ADF_AREA_SEE_ALSO].line_data, ((unsigned int)
						(tmp_ptr_2 - area_list[ADF_AREA_SEE_ALSO].line_data)),
						found_length);
            }
				else if ((tmp_ptr_1 = strchr(tmp_ptr_2, '\n')) != NULL)
					tmp_ptr_1++;
				else
					break;
			}
		}
		if (!(*area_list[ADF_AREA_SEE_ALSO].line_data)) {
			free(area_list[ADF_AREA_SEE_ALSO].line_data);
			area_list[ADF_AREA_SEE_ALSO].line_data = NULL;
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Fix up the ADF entry source file name . . .							*/
	/*	*****************************************************************	*/
	if (area_list[ADF_AREA_SOURCE_FILE_NAME].line_data != NULL) {
		free(area_list[ADF_AREA_SOURCE_FILE_NAME].line_data);
		area_list[ADF_AREA_SOURCE_FILE_NAME].line_data = NULL;
	}
	if ((area_list[ADF_AREA_SOURCE_FILE_NAME].line_data = strdup(file_name)) ==
		NULL) {
		STR_AllocMsgItem(strlen(file_name) + 1, error_text,
			"Unable to allocate memory for the source file name string");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Fix up the ADF entry source file date . . .							*/
	/*	*****************************************************************	*/
	SDTIF_Format_time_t(file_date, date_buffer);
	date_buffer[10] = '\0';
	if (area_list[ADF_AREA_SOURCE_FILE_DATE].line_data != NULL) {
		free(area_list[ADF_AREA_SOURCE_FILE_DATE].line_data);
		area_list[ADF_AREA_SOURCE_FILE_DATE].line_data = NULL;
	}
	if ((area_list[ADF_AREA_SOURCE_FILE_DATE].line_data =
		strdup(date_buffer)) == NULL) {
		STR_AllocMsgItem(strlen(date_buffer) + 1, error_text,
			"Unable to allocate memory for the source file date string");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Fix up the ADF entry source file name . . .							*/
	/*	*****************************************************************	*/
	if (area_list[ADF_AREA_SOURCE_FILE_FULL_NAME].line_data != NULL) {
		free(area_list[ADF_AREA_SOURCE_FILE_FULL_NAME].line_data);
		area_list[ADF_AREA_SOURCE_FILE_FULL_NAME].line_data = NULL;
	}
	if ((area_list[ADF_AREA_SOURCE_FILE_FULL_NAME].line_data =
		strdup(full_name)) == NULL) {
		STR_AllocMsgItem(strlen(full_name) + 1, error_text,
			"Unable to allocate memory for the full source file name string");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Apply any entry include and exclude specifiers . . .				*/
	/*	*****************************************************************	*/
	if ((control_ptr->entry_include_count ||
		control_ptr->entry_exclude_count) && (ADF_ApplyCludesEntry(control_ptr,
		area_list[ADF_AREA_BASE_NAME].line_data, file_name, file_type,
		man_page) != ADF_TRUE))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Apply any hypertext include and exclude specifiers . . .			*/
	/*	*****************************************************************	*/
	if (control_ptr->htext_include_count || control_ptr->htext_exclude_count) {
		for (count_1 = 0; count_1 < publish_xref_count; ) {
			if (ADF_ApplyCludesHText(control_ptr, publish_xref_list[count_1]) ==
				ADF_TRUE)
				count_1++;
			else
				strl_remove(&publish_xref_count, &publish_xref_list, count_1, 1);
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Apply the (perhaps forced) default authors string . . .			*/
	/*	*****************************************************************	*/
	if ((return_code = ADF_ApplyDefaultString(area_list + ADF_AREA_AUTHORS,
		ADF_AREA_AUTHORS, control_ptr->default_author,
		control_ptr->forced_author_flag, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Apply the (perhaps forced) default copyright string . . .		*/
	/*	*****************************************************************	*/
	if ((return_code = ADF_ApplyDefaultString(area_list + ADF_AREA_COPYRIGHTS,
		ADF_AREA_COPYRIGHTS, control_ptr->default_copyright,
		control_ptr->forced_copyright_flag, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Apply the (perhaps forced) man page . . .								*/
	/*	*****************************************************************	*/
	if ((man_page == NULL) || (control_ptr->forced_man_page_flag == ADF_TRUE))
		man_page = (control_ptr->default_man_page != NULL) ?
			control_ptr->default_man_page : ADF_DEFAULT_MAN_PAGE;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Fix up the ADF entry tab setting string . . .						*/
	/*	*****************************************************************	*/
	if (area_list[ADF_AREA_TAB_SETTING].line_data != NULL) {
		free(area_list[ADF_AREA_TAB_SETTING].line_data);
		area_list[ADF_AREA_TAB_SETTING].line_data = NULL;
	}
	if ((area_list[ADF_AREA_TAB_SETTING].line_data = strdup(tab_setting)) ==
		NULL) {
		STR_AllocMsgItem(strlen(tab_setting) + 1, error_text,
			"Unable to allocate memory for the tab setting string");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Ignore any sections specified . . .										*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		if ((control_ptr->ignore_section_list[count_1] == ADF_TRUE) &&
			(area_list[count_1].line_data != NULL)) {
			free(area_list[count_1].line_data);
			area_list[count_1].line_data = NULL;
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If we're in update mode, check to see whether this entry			*/
	/*	should be added to the temporary ADF database file . . .				*/
	/*	*****************************************************************	*/
	if (control_ptr->prep_adf_file_mode == ADF_PREP_FILE_MODE_UPDATE) {
		if ((return_code = ADF_CheckForAdd(control_ptr, area_list,
			file_name, core_name, full_name, file_type, man_page, file_date,
			&add_entry_flag, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		else if (add_entry_flag != ADF_TRUE)
			goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	if ((control_ptr->prep_adf_file == NULL) ||
		(control_ptr->check_only_flag == ADF_TRUE))
		goto EXIT_FUNCTION;

	time(&prep_date);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Add the entry to the temporary ADF database file . . .			*/
	/*	*****************************************************************	*/
	if (((return_code = ADF_AddToPrepList(control_ptr,
		area_list[ADF_AREA_BASE_NAME].line_data, file_name, core_name,
		full_name, file_type, man_page, file_date, &prep_date, domain_ptr,
		area_list, publish_xref_count, publish_xref_list, error_text)) ==
		ADF_SUCCESS) && (control_ptr->log_flag == ADF_TRUE))
		MLOG_LogInfo(control_ptr->mlog_ptr, "%s: %s '%s' at line number %u.\n",
			full_name, "Processed ADF comment for base name",
			area_list[ADF_AREA_BASE_NAME].line_data, start_line);
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	strl_remove_all(&publish_xref_count, &publish_xref_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_GetAreaData(ADF_CONTROL *control_ptr,
	const ADF_AREA *area_def_ptr, const ADF_DOMAIN *domain_ptr,
	ADF_SOURCE_DATA *area_ptr, unsigned int *publish_xref_count,
	char ***publish_xref_list, char *error_text)
#else
static int ADF_GetAreaData(control_ptr, area_def_ptr, domain_ptr, area_ptr,
	publish_xref_count, publish_xref_list, error_text)
ADF_CONTROL        *control_ptr;
const ADF_AREA     *area_def_ptr;
const ADF_DOMAIN   *domain_ptr;
ADF_SOURCE_DATA    *area_ptr;
unsigned int       *publish_xref_count;
char             ***publish_xref_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int                     return_code = ADF_SUCCESS;
	unsigned int            line_count  = 0;
	char                  **line_list   = NULL;
	unsigned int            tmp_count   = 0;
	char                  **tmp_list    = NULL;
	unsigned int            found_index;
	unsigned int            count_1;
	char                   *line_ptr;
	int                     new_para_flag;
	int                     ltrim_flag;
	int                     rtrim_flag;
	int                     squeeze_flag;
	int                     wrap_flag;
	char                   *append_char;
	char                   *para_format;
	char                    para_format_buffer[ADF_PFORMAT_LENGTH + 1];
	char                    default_para_format_buffer[ADF_PFORMAT_LENGTH + 1];
	const ADF_PFORMAT_DEF  *para_format_def_ptr;
	unsigned int            para_format_index;
	unsigned int            para_format_end;
	char                   *tmp_ptr;
	unsigned int            line_length;

	ADF_MakeFormatString(0, default_para_format_buffer);

	new_para_flag = ADF_TRUE;
	ltrim_flag    = area_ptr->section_ptr->ltrim_flag;
	rtrim_flag    = area_ptr->section_ptr->rtrim_flag;
	squeeze_flag  = area_ptr->section_ptr->squeeze_flag;
	wrap_flag     = area_ptr->section_ptr->wrap_flag;
	append_char   = " ";
	para_format   = NULL;

	for (count_1 = 0; count_1 < area_ptr->line_count; count_1++) {
		line_ptr = (count_1) ? area_ptr->line_list[count_1] :
			(area_ptr->line_list[count_1] + area_ptr->start_position);
		if ((area_ptr->section_ptr->para_format_flag == ADF_TRUE) &&
			(area_def_ptr->pformat_flag == ADF_TRUE)               &&
			((para_format_def_ptr = ADF_MatchParaFormat(line_ptr,
			para_format_buffer, &para_format_index, &para_format_end)) !=
			NULL)) {
			para_format = para_format_buffer;
			line_ptr    = line_ptr + para_format_end;
			if (para_format_def_ptr->char_format_flag == ADF_TRUE) {
				new_para_flag = ADF_TRUE;
				ltrim_flag    = ADF_TRUE;
				rtrim_flag    = ADF_TRUE;
				squeeze_flag  = ADF_TRUE;
				wrap_flag     = ADF_TRUE;
				append_char   = " ";
				while (isspace(*line_ptr))
					line_ptr++;
			}
			else {
				new_para_flag = ADF_TRUE;
				ltrim_flag    = ADF_FALSE;
				rtrim_flag    = ADF_FALSE;
				squeeze_flag  = ADF_FALSE;
				wrap_flag     = ADF_TRUE;
				append_char   = "\r";
			}
		}
		else
			para_format = NULL;
		if (ltrim_flag == ADF_TRUE)
			ltrim(line_ptr);
		if (rtrim_flag == ADF_TRUE)
			rtrim(line_ptr);
		if (squeeze_flag == ADF_TRUE)
			oneblank(line_ptr);
		if ((!(*line_ptr)) && (para_format == NULL)) {
			new_para_flag = ADF_TRUE;
			ltrim_flag    = area_ptr->section_ptr->ltrim_flag;
			rtrim_flag    = area_ptr->section_ptr->rtrim_flag;
			squeeze_flag  = area_ptr->section_ptr->squeeze_flag;
			wrap_flag     = area_ptr->section_ptr->wrap_flag;
			append_char   = " ";
			para_format   = NULL;
			continue;
		}
		if ((new_para_flag == ADF_TRUE) || (wrap_flag != ADF_TRUE)) {
			para_format = ((para_format == NULL)        &&
				(area_def_ptr->pformat_flag == ADF_TRUE) &&
				(area_ptr->section_ptr->para_format_flag == ADF_TRUE)) ?
				default_para_format_buffer : para_format;
			if ((return_code = ADF_AddParagraph(&line_count, &line_list,
				para_format, line_ptr, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
		}
		else if ((return_code = ADF_AppendParagraph(line_list +
			(line_count - 1), line_ptr, append_char, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		new_para_flag = ADF_FALSE;
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Remove any leading blank lines . . .									*/
	/*	*****************************************************************	*/
	while (line_count && ((!line_list[0][0]) ||
		(str_space(line_list[0], 0) == NULL)))
		strl_remove(&line_count, &line_list, 0, 1);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Remove any trailing blank lines . . .									*/
	/*	*****************************************************************	*/
	while (line_count && ((!line_list[line_count - 1][0]) ||
		(str_space(line_list[line_count - 1], 0) == NULL)))
		strl_remove(&line_count, &line_list, line_count - 1, 1);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
/*
	CODE NOTE: Not yet implemented.
*/
	/*		If this is the 'SEE_ALSO', 'AUTHORS', or 'COPYRIGHT' area,		*/
	/*																							*/
	/*		1)	Clean-up the lines (trim, oneblank, no control chars).		*/
	/*																							*/
	/*		2)	Remove any blank lines.													*/
	/*																							*/
	/*		3)	Unique the paragraphs (but leave them in the original order)*/
	/*	*****************************************************************	*/
	if (area_ptr->section_ptr->area_index == ADF_AREA_SEE_ALSO) {
		for (count_1 = 0; count_1 < line_count; ) {
			if ((!(*trim(oneblank(ctltospc(line_list[count_1]))))) ||
				(strl_find(tmp_count, tmp_list, line_list[count_1],
				&found_index) == STRFUNCS_ITEM_FOUND))
				strl_remove(&line_count, &line_list, count_1, 1);
			else if (strl_insert(&tmp_count, &tmp_list, line_list[count_1],
				found_index) != STRFUNCS_SUCCESS) {
				strl_remove_all(&tmp_count, &tmp_list);
				strcpy(error_text, "Unable to allocate temporary string list.");
				return_code = ADF_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			else
				count_1++;
		}
		strl_remove_all(&tmp_count, &tmp_list);
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If this is the output index area, remove any leading, trailing,*/
	/*	or redundant index level separators . . .									*/
	/*	*****************************************************************	*/
	if ((area_ptr->section_ptr->area_index == ADF_AREA_OUTPUT_INDEX) ||
		(area_ptr->section_ptr->area_index == ADF_AREA_ENTRY_CLASS_NAME)) {
		for (count_1 = 0; count_1 < line_count; ) {
			trim(oneblank(ctltospc(line_list[count_1])));
			while (((tmp_ptr = strstr(line_list[count_1], "::")) != NULL) ||
				((tmp_ptr = strstr(line_list[count_1], " :")) != NULL) ||
				((tmp_ptr = strstr(line_list[count_1], ": ")) != NULL))
				strrepl(line_list[count_1], ":",
					((unsigned int) (tmp_ptr - line_list[count_1])), 2);
			if (*trimx(line_list[count_1], ":"))
				count_1++;
			else
				strl_remove(&line_count, &line_list, count_1, 1);
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If this is any of the 'OUTPUT_INDEX', 'PUBLISH_NAME',				*/
	/*	'PUBLISH_XREF' or 'ENTRY_CLASS_NAME' areas, clean-up the lines.	*/
	/*	*****************************************************************	*/
	if ((area_ptr->section_ptr->area_index == ADF_AREA_OUTPUT_INDEX) ||
		(area_ptr->section_ptr->area_index == ADF_AREA_PUBLISH_NAME)  ||
		(area_ptr->section_ptr->area_index == ADF_AREA_PUBLISH_XREF)  ||
		(area_ptr->section_ptr->area_index == ADF_AREA_ENTRY_CLASS_NAME)) {
		for (count_1 = 0; count_1 < line_count; ) {
			if (!(*trim(oneblank(ctltospc(line_list[count_1])))))
				strl_remove(&line_count, &line_list, count_1, 1);
			else
				count_1++;
		}
		strl_sort(line_count, line_list);
		strl_uniq(&line_count, &line_list);
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Apply character formats if required . . .								*/
	/*	*****************************************************************	*/
	if (area_ptr->section_ptr->char_format_flag == ADF_TRUE) {
		for (count_1 = 0; count_1 < line_count; count_1++) {
			if ((line_list[count_1][0] != ADF_PFORMAT_MARKER_CHAR) ||
				(line_list[count_1][6] == '1')) {
				if ((return_code = ADF_DoCharFormat(line_list + count_1,
					error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				if (line_list[count_1][0] != ADF_PFORMAT_MARKER_CHAR) {
					if (area_ptr->section_ptr->ltrim_flag)
						ltrim(line_list[count_1]);
					if (area_ptr->section_ptr->rtrim_flag)
						rtrim(line_list[count_1]);
					if (area_ptr->section_ptr->squeeze_flag)
						oneblank(line_list[count_1]);
				}
				else if (line_list[count_1][6] == '1')
					trim(oneblank(line_list[count_1]));
			}
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Create the section string with each paragraph separated by a	*/
	/*	line-feed character . . .														*/
	/*	*****************************************************************	*/
	if (line_count) {
		line_length = line_count;
		for (count_1 = 0; count_1 < line_count; count_1++)
			line_length += strlen(line_list[count_1]);
		if ((area_ptr->line_data = ((char *) calloc(line_length,
			sizeof(char)))) == NULL) {
			STR_AllocMsgItem(line_length, error_text, "%s '%s' %s %u",
				"Unable to allocate memory for the ADF comments in the",
				area_ptr->section_ptr->output_section_name,
				"section beginning at line number", area_ptr->line_number);
			return_code = ADF_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		else {
			strcpy(area_ptr->line_data, line_list[0]);
			for (count_1 = 1; count_1 < line_count; count_1++)
				strcat(strcat(area_ptr->line_data, "\n"), line_list[count_1]);
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If this is the PUBLISH_XREF area, we'll need to take a copy of	*/
	/*	the list for later use in building the list of hyper-text strings.*/
	/*	*****************************************************************	*/
	if (area_ptr->section_ptr->area_index == ADF_AREA_PUBLISH_XREF) {
		*publish_xref_count = line_count;
		*publish_xref_list  = line_list;
		line_count          = 0;
		line_list           = NULL;
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	strl_remove_all(&line_count, &line_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_AddParagraph(unsigned int *line_count, char ***line_list,
	const char *para_format, const char *line_ptr, char *error_text)
#else
static int ADF_AddParagraph(line_count, line_list, para_format, line_ptr,
	error_text)
unsigned int   *line_count;
char         ***line_list;
const char     *para_format;
const char     *line_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int line_length;

	if (meml_allocate(line_count, ((void ***) line_list),
		line_length = ((para_format == NULL) ? 0 : strlen(para_format)) +
		strlen(line_ptr) + 1, 1) != STRFUNCS_SUCCESS) {
		STR_AllocMsgItem(line_length, error_text,
			"Unable to copy a comment paragraph");
		return_code = ADF_MEMORY_FAILURE;
	}
	else
		strcat(strcpy((*line_list)[*line_count - 1],
			(para_format == NULL) ? "" : para_format), line_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_AppendParagraph(char **line_list_ptr, const char *add_line_ptr,
	const char *append_char, char *error_text)
#else
static int ADF_AppendParagraph(line_list_ptr, add_line_ptr, append_char,
	error_text)
char       **line_list_ptr;
const char  *add_line_ptr;
const char  *append_char;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  line_length;
	char         *tmp_string;

	if (*add_line_ptr) {
		line_length = strlen(add_line_ptr) + strlen(*line_list_ptr) + 1 +
			(((**line_list_ptr == ADF_PFORMAT_MARKER_CHAR) &&
			(strlen(*line_list_ptr) == ADF_PFORMAT_LENGTH)) ? 0 : 1);
		if ((tmp_string = ((char *) calloc(line_length, sizeof(char)))) ==
			NULL) {
			STR_AllocMsgItem(line_length, error_text, "%s %s",
				"Attempt to allocate memory to concatenate two comment",
				"strings failed");
			return_code = ADF_MEMORY_FAILURE;
		}
		else {
			strcat(strcat(strcpy(tmp_string, *line_list_ptr),
				((**line_list_ptr == ADF_PFORMAT_MARKER_CHAR) &&
				(strlen(*line_list_ptr) == ADF_PFORMAT_LENGTH)) ? "" :
				append_char), add_line_ptr);
			free(*line_list_ptr);
			*line_list_ptr = tmp_string;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_DoCharFormat(char **in_line, char *error_text)
#else
static int ADF_DoCharFormat(in_line, error_text)
char **in_line;
char  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  line_length;
	char         *tmp_line;
	char         *line_ptr;
	char         *tmp_ptr;
	char         *tmp_line_ptr;
	char          this_char;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If there aren't any character formatting specifiers in the		*/
	/*	string, don't bother doing any of the subsequent work . . .			*/
	/*	*****************************************************************	*/
	if ((strchr(*in_line, '\'') == NULL) && (strchr(*in_line, '`') == NULL) &&
		(strchr(*in_line, '@') == NULL))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	if ((tmp_line = ((char *) calloc(line_length = (strlen(*in_line) * 3) + 1,
		sizeof(char)))) == NULL) {
		STR_AllocMsgItem(line_length, error_text,
			"Unable to create working character format string");
		return_code = ADF_MEMORY_FAILURE;
	}
	else {
		strcpy(tmp_line, *in_line);
		line_ptr = tmp_line + ((*tmp_line == ADF_PFORMAT_MARKER_CHAR) ?
			ADF_PFORMAT_LENGTH : 0);
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Convert from old-style bold character formats.				*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "''")) != NULL) {
			tmp_ptr[0]   = '@';
			tmp_ptr[1]   = '\'';
			tmp_line_ptr = tmp_ptr + 2;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Convert from old-style italic character formats.			*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "``")) != NULL) {
			tmp_ptr[0]   = '@';
			tmp_ptr[1]   = '`';
			tmp_line_ptr = tmp_ptr + 2;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Convert from old-style superscript character formats.		*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "'`")) != NULL) {
			tmp_ptr[0]   = '@';
			tmp_ptr[1]   = '>';
			tmp_line_ptr = tmp_ptr + 2;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Convert from old-style subscript character formats.		*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "`'")) != NULL) {
			tmp_ptr[0]   = '@';
			tmp_ptr[1]   = '<';
			tmp_line_ptr = tmp_ptr + 2;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Bold character formatting . . .									*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "@'")) != NULL) {
			tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
			tmp_ptr[1] = ADF_CFORMAT_CHAR_BOLD_1;
			if ((tmp_ptr = strstr(tmp_line_ptr, "@'")) != NULL) {
				tmp_ptr[0]   = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1]   = ADF_CFORMAT_CHAR_BOLD_2;
				tmp_line_ptr = tmp_ptr + 2;
			}
			else {
				tmp_ptr    = tmp_line_ptr + strlen(tmp_line_ptr);
				tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1] = ADF_CFORMAT_CHAR_BOLD_2;
				tmp_ptr[2] = '\0';
				break;
			}
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Italic character formatting . . .								*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "@`")) != NULL) {
			tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
			tmp_ptr[1] = ADF_CFORMAT_CHAR_ITALIC_1;
			if ((tmp_ptr = strstr(tmp_line_ptr, "@`")) != NULL) {
				tmp_ptr[0]   = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1]   = ADF_CFORMAT_CHAR_ITALIC_2;
				tmp_line_ptr = tmp_ptr + 2;
			}
			else {
				tmp_ptr    = tmp_line_ptr + strlen(tmp_line_ptr);
				tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1] = ADF_CFORMAT_CHAR_ITALIC_2;
				tmp_ptr[2] = '\0';
				break;
			}
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Underlined character formatting . . .							*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "@_")) != NULL) {
			tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
			tmp_ptr[1] = ADF_CFORMAT_CHAR_ULINED_1;
			if ((tmp_ptr = strstr(tmp_line_ptr, "@_")) != NULL) {
				tmp_ptr[0]   = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1]   = ADF_CFORMAT_CHAR_ULINED_2;
				tmp_line_ptr = tmp_ptr + 2;
			}
			else {
				tmp_ptr    = tmp_line_ptr + strlen(tmp_line_ptr);
				tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1] = ADF_CFORMAT_CHAR_ULINED_2;
				tmp_ptr[2] = '\0';
				break;
			}
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Overlined character formatting . . .							*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "@-")) != NULL) {
			tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
			tmp_ptr[1] = ADF_CFORMAT_CHAR_OLINED_1;
			if ((tmp_ptr = strstr(tmp_line_ptr, "@-")) != NULL) {
				tmp_ptr[0]   = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1]   = ADF_CFORMAT_CHAR_OLINED_2;
				tmp_line_ptr = tmp_ptr + 2;
			}
			else {
				tmp_ptr    = tmp_line_ptr + strlen(tmp_line_ptr);
				tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1] = ADF_CFORMAT_CHAR_OLINED_2;
				tmp_ptr[2] = '\0';
				break;
			}
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Strike-through character formatting . . .						*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "@#")) != NULL) {
			tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
			tmp_ptr[1] = ADF_CFORMAT_CHAR_STHRU_1;
			if ((tmp_ptr = strstr(tmp_line_ptr, "@#")) != NULL) {
				tmp_ptr[0]   = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1]   = ADF_CFORMAT_CHAR_STHRU_2;
				tmp_line_ptr = tmp_ptr + 2;
			}
			else {
				tmp_ptr    = tmp_line_ptr + strlen(tmp_line_ptr);
				tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1] = ADF_CFORMAT_CHAR_STHRU_2;
				tmp_ptr[2] = '\0';
				break;
			}
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Embedded indices character formatting . . .					*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "@~")) != NULL) {
			tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
			tmp_ptr[1] = ADF_CFORMAT_CHAR_EINDEX_1;
			if ((tmp_ptr = strstr(tmp_line_ptr, "@~")) != NULL) {
				tmp_ptr[0]   = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1]   = ADF_CFORMAT_CHAR_EINDEX_2;
				tmp_line_ptr = tmp_ptr + 2;
			}
			else {
				tmp_ptr    = tmp_line_ptr + strlen(tmp_line_ptr);
				tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1] = ADF_CFORMAT_CHAR_EINDEX_2;
				tmp_ptr[2] = '\0';
				break;
			}
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Sub-script character formatting . . .							*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "@<")) != NULL) {
			tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
			tmp_ptr[1] = ADF_CFORMAT_CHAR_SUBSCRIPT_1;
			if ((tmp_ptr = strstr(tmp_line_ptr, "@<")) != NULL) {
				tmp_ptr[0]   = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1]   = ADF_CFORMAT_CHAR_SUBSCRIPT_2;
				tmp_line_ptr = tmp_ptr + 2;
			}
			else {
				tmp_ptr    = tmp_line_ptr + strlen(tmp_line_ptr);
				tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1] = ADF_CFORMAT_CHAR_SUBSCRIPT_2;
				tmp_ptr[2] = '\0';
				break;
			}
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Super-script character formatting . . .						*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strstr(tmp_line_ptr, "@>")) != NULL) {
			tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
			tmp_ptr[1] = ADF_CFORMAT_CHAR_SUPERSCRIPT_1;
			if ((tmp_ptr = strstr(tmp_line_ptr, "@>")) != NULL) {
				tmp_ptr[0]   = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1]   = ADF_CFORMAT_CHAR_SUPERSCRIPT_2;
				tmp_line_ptr = tmp_ptr + 2;
			}
			else {
				tmp_ptr    = tmp_line_ptr + strlen(tmp_line_ptr);
				tmp_ptr[0] = ADF_CFORMAT_MARKER_CHAR;
				tmp_ptr[1] = ADF_CFORMAT_CHAR_SUPERSCRIPT_2;
				tmp_ptr[2] = '\0';
				break;
			}
		}
		/*	***********************************************************	*/

		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Remove unneccessary format specifiers . . .					*/
		/*	***********************************************************	*/
		tmp_line_ptr = line_ptr;
		while ((tmp_ptr = strchr(tmp_line_ptr, ADF_CFORMAT_MARKER_CHAR)) !=
			NULL) {
			this_char    = *++tmp_ptr;
			tmp_line_ptr = ++tmp_ptr;
			if (isupper(this_char)) {
				this_char = STRFUNCS_tolower(this_char);
				while (*tmp_ptr) {
					if (*tmp_ptr == ADF_CFORMAT_MARKER_CHAR) {
						if (tmp_ptr[1] == this_char) {
							tmp_line_ptr -= 2;
							strdele(tmp_ptr, 0, 2);
							strdele(tmp_line_ptr, 0, 2);
							break;
						}
						tmp_ptr += 2;
					}
					else if (!isspace(*tmp_ptr))
						break;
					else
						tmp_ptr++;
				}
			}
		}
		/*	***********************************************************	*/

		if (strlen(*in_line) >= strlen(tmp_line)) {
			strcpy(*in_line, tmp_line);
			free(tmp_line);
		}
		else if ((tmp_ptr = ((char *) realloc(tmp_line,
			strlen(tmp_line) + 1))) == NULL) {
			STR_AllocMsgItem(strlen(tmp_line) + 1, error_text,
				"Unable to re-allocate the working character format string");
			free(tmp_line);
			return_code = ADF_MEMORY_FAILURE;
		}
		else {
			free(*in_line);
			*in_line = tmp_ptr;
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_ApplyDefaultString(ADF_SOURCE_DATA *area_ptr,
	unsigned int area_index, const char *default_string, int forced_flag,
	char *error_text)
#else
static int ADF_ApplyDefaultString(area_ptr, area_index, default_string,
	forced_flag, error_text)
ADF_SOURCE_DATA *area_ptr;
unsigned int     area_index;
const char      *default_string;
int              forced_flag;
char            *error_text;
#endif /* #ifndef NARGS */
{

	int  return_code = ADF_SUCCESS;
	char area_name[ADF_AREA_NAME_LENGTH + 1];

	if (((area_ptr->line_data == NULL) && (default_string != NULL)) ||
		(forced_flag == ADF_TRUE)) {
		if (area_ptr->line_data != NULL)
			free(area_ptr->line_data);
		area_ptr->line_data = NULL;
		if ((default_string != NULL) && ((area_ptr->line_data =
			strdup(default_string)) == NULL)) {
			STR_AllocMsgItem(strlen(default_string) + 1, error_text,
				"Unable to allocate memory for the %s %s string",
				(forced_flag == ADF_TRUE) ? "forced" : "default",
				lower(ADF_GetAreaName(area_index, area_name)));
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_CheckForAdd(ADF_CONTROL *control_ptr,
	const ADF_SOURCE_DATA *area_list, const char *file_name,
	const char *core_name, const char *full_name, const char *file_type,
	const char *man_page, const time_t *file_date, int *add_entry_flag,
	char *error_text)
#else
static int ADF_CheckForAdd(control_ptr, area_list, file_name, core_name,
	full_name, file_type, man_page, file_date, add_entry_flag, error_text)
ADF_CONTROL           *control_ptr;
const ADF_SOURCE_DATA *area_list;
const char            *file_name;
const char            *core_name;
const char            *full_name;
const char            *file_type;
const char            *man_page;
const time_t          *file_date;
int                   *add_entry_flag;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code = ADF_SUCCESS;
	unsigned int    count_1;
	unsigned int    found_index;
	ADF_SOURCE_DATA in_area_list[ADF_AREA_COUNT];

	*add_entry_flag = ADF_FALSE;

#ifdef __MSDOS__
	full_name = "?";
#endif /* #ifdef __MSDOS__ */

	if (ADF_FIND_FindEntryByBaseName(control_ptr->in_entry_count,
		control_ptr->in_entry_list, area_list[ADF_AREA_BASE_NAME].line_data,
		&found_index) != STRFUNCS_ITEM_FOUND)
{
/*
	CODE NOTE: To be removed.
*/
printf("*** Base name '%s' not found.\n",
	area_list[ADF_AREA_BASE_NAME].line_data);
printf("-----------------------------------------------------------------\n");
		*add_entry_flag = ADF_TRUE;
}
	else if (strcmp(file_name,
		control_ptr->in_entry_list[found_index].file_name)                   ||
		strcmp(full_name, control_ptr->in_entry_list[found_index].full_name) ||
		strcmp(core_name, control_ptr->in_entry_list[found_index].core_name) ||
		strcmp(file_type, control_ptr->in_entry_list[found_index].file_type) ||
		strcmp(man_page, control_ptr->in_entry_list[found_index].man_page)   ||
		(*file_date != control_ptr->in_entry_list[found_index].file_date)) {
/*
	CODE NOTE: To be removed.
*/
printf("file_name: [%s]\n", file_name);
printf("           [%s]\n",
	control_ptr->in_entry_list[found_index].file_name);
printf("full_name: [%s]\n", full_name);
printf("           [%s]\n",
	control_ptr->in_entry_list[found_index].full_name);
printf("core_name: [%s]\n", core_name);
printf("           [%s]\n",
	control_ptr->in_entry_list[found_index].core_name);
printf("file_type: [%s]\n", file_type);
printf("           [%s]\n",
	control_ptr->in_entry_list[found_index].file_type);
printf("man_page : [%s]\n", man_page);
printf("           [%s]\n",
	control_ptr->in_entry_list[found_index].man_page);
printf("file_date: [%lu]\n", *file_date);
printf("           [%lu]\n",
	control_ptr->in_entry_list[found_index].file_date);
printf("-----------------------------------------------------------------\n");
		ADF_RemoveExistingEntry(control_ptr, found_index);
		*add_entry_flag = ADF_TRUE;
	}
	else if ((return_code = ADF_ReadEntry(control_ptr,
		control_ptr->in_entry_list + found_index, NULL, in_area_list,
		error_text)) == ADF_SUCCESS) {
		for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
			if ((area_list[count_1].line_data == NULL) &&
				(in_area_list[count_1].line_data == NULL))
				continue;
			if (in_area_list[count_1].section_index ==
				((UINT_MAX - ADF_AREA_COUNT) + count_1))
				in_area_list[count_1].section_index = 0;
			if (in_area_list[count_1].line_number ==
				((UINT_MAX - ADF_AREA_COUNT) + count_1))
				in_area_list[count_1].line_number = 0;
			if (((area_list[count_1].line_data != NULL) &&
				(in_area_list[count_1].line_data == NULL)) ||
				((area_list[count_1].line_data == NULL) &&
				(in_area_list[count_1].line_data != NULL)) ||
				(area_list[count_1].section_index !=
				in_area_list[count_1].section_index) ||
/*
	CODE NOTE: 'start_position' is not recorded in the ADF database file.
				(area_list[count_1].start_position !=
				in_area_list[count_1].start_position) ||
*/
				((area_list[count_1].section_name == NULL) &&
				(in_area_list[count_1].section_name != NULL)) ||
				((area_list[count_1].section_name != NULL) &&
				(in_area_list[count_1].section_name == NULL)) ||
				((area_list[count_1].section_name != NULL) &&
				(in_area_list[count_1].section_name != NULL) &&
				strcmp(area_list[count_1].section_name,
				in_area_list[count_1].section_name)) ||
				strcmp(area_list[count_1].line_data,
				in_area_list[count_1].line_data) ||
				(area_list[count_1].line_number !=
				in_area_list[count_1].line_number)) {
/*
	CODE NOTE: To be removed.
*/
printf("Area Index   : %u\n", count_1);
printf("line_data    : [%s]\n", area_list[count_1].line_data);
printf("               [%s]\n", in_area_list[count_1].line_data);
printf("section_index: [%u]\n", area_list[count_1].section_index);
printf("               [%u]\n", in_area_list[count_1].section_index);
printf("section_name : [%s]\n", area_list[count_1].section_name);
printf("               [%s]\n", in_area_list[count_1].section_name);
printf("line_number  : [%u]\n", area_list[count_1].line_number);
printf("               [%u]\n", in_area_list[count_1].line_number);
printf("-----------------------------------------------------------------\n");
				ADF_RemoveExistingEntry(control_ptr, found_index);
				*add_entry_flag = ADF_TRUE;
				break;
			}
		}
	}

	return(return_code);
}
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
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	ADF_CONTROL   control_data;
	unsigned int  domain_count;
	ADF_DOMAIN   *domain_list;
	char          error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for function 'ADF_DoSource()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------------\n\n");

	ADF_INIT_Control(&control_data);

	if (argc < 2) {
		sprintf(error_text, "\nUSAGE:\n   %s <file-name> [<file-name>...]\n",
			argv[0]);
		return_code = ADF_BAD_ARGS_FAILURE;
	}
	else {
		control_data.prep_adf_file        = NULL;
		control_data.check_only_flag      = ADF_TRUE;
		control_data.ignore_bad_cmnt_flag = ADF_TRUE;
		control_data.cont_on_error_flag   = ADF_TRUE;
		control_data.area_name_type       = ADF_AREA_NAME_TYPE_INTERNAL;
		control_data.area_order_type      = ADF_AREA_ORDER_TYPE_INTERNAL;
		ADF_GetDefaultDefSpec(&domain_count, &domain_list);
		for (count_1 = 1; count_1 < argc; count_1++) {
			if (((return_code = ADF_DoSource(&control_data, domain_count,
				domain_list, argv[count_1], error_text)) != ADF_SUCCESS) &&
				(return_code != ADF_PARSE_FAILURE))
				break;
			return_code = ADF_SUCCESS;
		}
	}

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

