/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs C code to support an internal ADF definition
								to the specified output handler.

	Revision History	:	1995-08-29 --- Creation.
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

#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int  ADF_EMIT_DefCSectionList,
	(unsigned int section_count,
	const ADF_SECTION *section_list, unsigned int domain_number,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_EMIT_CPat,
	(const ADF_PATTERN *pattern_ptr,
	const char *string_list_name, int trailing_comma_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_EMIT_CPatStrList,
	(const ADF_PATTERN *pattern_ptr,
	const char *string_list_name, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_EMIT_CStringList,
	(unsigned int string_count, char **string_list,
	const char *string_list_name, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_EMIT_CString,
	(const char *string_ptr, int trailing_comma_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(void ADF_EMIT_CComment,
	(const char *in_string, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void ADF_EMIT_CBorder,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_EMIT_DefCDomainList(unsigned int domain_count,
	const ADF_DOMAIN *domain_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
int ADF_EMIT_DefCDomainList(domain_count, domain_list, output_function,
	output_control, error_text)
unsigned int           domain_count;
const ADF_DOMAIN      *domain_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int               return_code = ADF_SUCCESS;
	unsigned int      count_1;
	const ADF_DOMAIN *domain_ptr;
	char              buffer[1024];
	char              date_buffer[100];

	output_function = (output_function != NULL) ? output_function :
		STR_FUNC_TYPE_fprintf_CAST(fprintf);
	output_control  = (output_control  != NULL) ? output_control  : stdout;

	SDTIF_Format_time_t(NULL, date_buffer);
	date_buffer[10] = '\0';

	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CComment("Automated Documentation Facility (ADF) Program Module",
		output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "/*\n");
	(*output_function)(output_control, "\t%s:\t%%%c%%\n\n",
		"File Name\t\t\t", 'M');
	(*output_function)(output_control, "\t%s:\t%%%c%%\n\n",
		"File Version\t\t", 'I');
	(*output_function)(output_control, "\t%s:\t%%%c%%\t%%%c%%\n\n",
		"Last Extracted\t\t", 'D', 'T');
	(*output_function)(output_control, "\t%s:\t%%%c%%\t%%%c%%\n\n",
		"Last Updated\t\t", 'E', 'U');
	(*output_function)(output_control, "\t%s:\t%s\n\n",
		"File Description\t", "Internal ADF definition file representation.");
	(*output_function)(output_control, "\t%s:\t%s --- Creation.\n",
		"Revision History\t", date_buffer);
	(*output_function)(output_control, "*/\n");
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");

	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CComment("Required include files . . .", output_function,
		output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");
	(*output_function)(output_control, "#include \"adf.h\"\n");
	(*output_function)(output_control, "\n");
	ADF_EMIT_CBorder(output_function, output_control);

	for (count_1 = 0; count_1 < domain_count; count_1++) {
		domain_ptr = domain_list + count_1;
		if ((return_code = ADF_EMIT_DefCSectionList(domain_ptr->section_count,
			domain_ptr->section_list, count_1, output_function,
			output_control, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
	}

	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CComment("Initialize domain file type lists.", output_function,
		output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");
	for (count_1 = 0; count_1 < domain_count; count_1++) {
		domain_ptr = domain_list + count_1;
		sprintf(buffer, "ADF_Def_DOM_%03u_FTYPE_STRL", count_1);
		if ((return_code = ADF_EMIT_CStringList(domain_ptr->file_type_count,
			domain_ptr->file_type_list, buffer, output_function,
			output_control, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
	}
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");

	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CComment("Initialize domain pattern string lists.",
		output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");
	for (count_1 = 0; count_1 < domain_count; count_1++) {
		domain_ptr = domain_list + count_1;
		sprintf(buffer, "ADF_Def_DOM_%03u_BOH_STRL", count_1);
		if ((return_code = ADF_EMIT_CPatStrList(&domain_ptr->boh_pattern,
			buffer, output_function, output_control, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		sprintf(buffer, "ADF_Def_DOM_%03u_EOH_STRL", count_1);
		if ((return_code = ADF_EMIT_CPatStrList(&domain_ptr->eoh_pattern,
			buffer, output_function, output_control, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		sprintf(buffer, "ADF_Def_DOM_%03u_BOL_STRL", count_1);
		if ((return_code = ADF_EMIT_CPatStrList(&domain_ptr->bol_pattern,
			buffer, output_function, output_control, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		sprintf(buffer, "ADF_Def_DOM_%03u_EOL_STRL", count_1);
		if ((return_code = ADF_EMIT_CPatStrList(&domain_ptr->eol_pattern,
			buffer, output_function, output_control, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		sprintf(buffer, "ADF_Def_DOM_%03u_EMP_STRL", count_1);
		if ((return_code = ADF_EMIT_CPatStrList(&domain_ptr->empty_line_pattern,
			buffer, output_function, output_control, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		sprintf(buffer, "ADF_Def_DOM_%03u_STR_STRL", count_1);
		if ((return_code = ADF_EMIT_CPatStrList(&domain_ptr->strip_pattern,
			buffer, output_function, output_control, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
	}
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");

	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CComment("Initialize the list of all domains.", output_function,
		output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");

	(*output_function)(output_control,
		"static unsigned int ADF_DefaultDomainCount   = %u;\n", domain_count);
	(*output_function)(output_control, "\n");
	(*output_function)(output_control,
		"static ADF_DOMAIN   ADF_DefaultDomainList[%u] = {\n", domain_count);

	for (count_1 = 0; count_1 < domain_count; count_1++) {
		domain_ptr = domain_list + count_1;
		(*output_function)(output_control, "\t{\n");
		if ((return_code = ADF_EMIT_CString(domain_ptr->domain_name,
			ADF_TRUE, output_function, output_control, error_text)) !=
			ADF_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = ADF_EMIT_CString(domain_ptr->domain_description,
			ADF_TRUE, output_function, output_control, error_text)) !=
			ADF_SUCCESS)
			goto EXIT_FUNCTION;
		(*output_function)(output_control, "\t\t%u,\n",
			domain_ptr->file_type_count);
		(*output_function)(output_control,
			"\t\tADF_Def_DOM_%03u_FTYPE_STRL,\n", count_1);
		sprintf(buffer, "ADF_Def_DOM_%03u_BOH_STRL", count_1);
		if ((return_code = ADF_EMIT_CPat(&domain_ptr->boh_pattern, buffer,
			ADF_TRUE, output_function, output_control, error_text)) !=
			ADF_SUCCESS)
			goto EXIT_FUNCTION;
		sprintf(buffer, "ADF_Def_DOM_%03u_EOH_STRL", count_1);
		if ((return_code = ADF_EMIT_CPat(&domain_ptr->eoh_pattern, buffer,
			ADF_TRUE, output_function, output_control, error_text)) !=
			ADF_SUCCESS)
			goto EXIT_FUNCTION;
		sprintf(buffer, "ADF_Def_DOM_%03u_BOL_STRL", count_1);
		if ((return_code = ADF_EMIT_CPat(&domain_ptr->bol_pattern, buffer,
			ADF_TRUE, output_function, output_control, error_text)) !=
			ADF_SUCCESS)
			goto EXIT_FUNCTION;
		sprintf(buffer, "ADF_Def_DOM_%03u_EOL_STRL", count_1);
		if ((return_code = ADF_EMIT_CPat(&domain_ptr->eol_pattern, buffer,
			ADF_TRUE, output_function, output_control, error_text)) !=
			ADF_SUCCESS)
			goto EXIT_FUNCTION;
		sprintf(buffer, "ADF_Def_DOM_%03u_EMP_STRL", count_1);
		if ((return_code = ADF_EMIT_CPat(&domain_ptr->empty_line_pattern, buffer,
			ADF_TRUE, output_function, output_control, error_text)) !=
			ADF_SUCCESS)
			goto EXIT_FUNCTION;
		sprintf(buffer, "ADF_Def_DOM_%03u_STR_STRL", count_1);
		if ((return_code = ADF_EMIT_CPat(&domain_ptr->strip_pattern, buffer,
			ADF_TRUE, output_function, output_control, error_text)) !=
			ADF_SUCCESS)
			goto EXIT_FUNCTION;
		(*output_function)(output_control, "\t\t%u,\n",
			domain_ptr->section_count);
		(*output_function)(output_control, "\t\tADF_Def_DOM_%03u_SEC\n",
			count_1);
		(*output_function)(output_control, "\t}%s\n",
			(count_1 < (domain_count - 1)) ? "," : "");
	}

	(*output_function)(output_control, "};\n");

	(*output_function)(output_control, "\n");
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		EMIT_ code which copies the default domain list.						*/
	/*	*****************************************************************	*/
	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CComment("Copy the internal ADF definition.", output_function,
		output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "%s(%s)\n",
		"int ADF_CopyDefaultDefSpec",
		"domain_count, domain_list, error_text");
	(*output_function)(output_control, "%s\n",
		"unsigned int  *domain_count;");
	(*output_function)(output_control, "%s\n",
		"ADF_DOMAIN   **domain_list;");
	(*output_function)(output_control, "%s\n",
		"char          *error_text;");
	(*output_function)(output_control, "%s\n",
		"{");
	(*output_function)(output_control, "%s\n",
"\treturn(ADF_CopyDomainList(ADF_DefaultDomainCount, ADF_DefaultDomainList,");
	(*output_function)(output_control, "%s\n",
		"\t\tdomain_count, domain_list, error_text));");
	(*output_function)(output_control, "%s\n",
		"}");
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		EMIT_ code which gets the default domain list.						*/
	/*	*****************************************************************	*/
	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CComment("Get the internal ADF definition.", output_function,
		output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "%s(%s)\n",
		"void ADF_GetDefaultDefSpec", "domain_count, domain_list");
	(*output_function)(output_control, "%s\n",
		"unsigned int  *domain_count;");
	(*output_function)(output_control, "%s\n",
		"ADF_DOMAIN   **domain_list;");
	(*output_function)(output_control, "%s\n",
		"{");
	(*output_function)(output_control, "%s\n",
		"\t*domain_count = ADF_DefaultDomainCount;");
	(*output_function)(output_control, "%s\n",
		"\t*domain_list  = ADF_DefaultDomainList;");
	(*output_function)(output_control, "%s\n",
		"}");
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_EMIT_DefCSectionList(unsigned int section_count,
	const ADF_SECTION *section_list, unsigned int domain_number,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_EMIT_DefCSectionList(section_count, section_list,
	domain_number, output_function, output_control, error_text)
unsigned int           section_count;
const ADF_SECTION     *section_list;
unsigned int           domain_number;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code = ADF_SUCCESS;
	unsigned int       count_1;
	const ADF_SECTION *section_ptr;
   char               buffer[1024];

	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	sprintf(buffer,
		"Initialize section pattern string lists for domain number %u.",
		domain_number);
	ADF_EMIT_CComment(buffer, output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");
	for (count_1 = 0; count_1 < section_count; count_1++) {
		section_ptr = section_list + count_1;
		sprintf(buffer, "ADF_Def_DOM_%03u_SEC_%03u_MAT_STRL",
			domain_number, count_1);
		if ((return_code = ADF_EMIT_CPatStrList(&section_ptr->match_pattern,
			buffer, output_function, output_control, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
	}
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");

	ADF_EMIT_CBorder(output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	sprintf(buffer, "Initialize section lists for domain number %u.",
		domain_number);
	ADF_EMIT_CComment(buffer, output_function, output_control);
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");

	(*output_function)(output_control,
		"static ADF_SECTION ADF_Def_DOM_%03u_SEC[%u] = {\n",
		domain_number, section_count);

	for (count_1 = 0; count_1 < section_count; count_1++) {
		section_ptr = section_list + count_1;
		(*output_function)(output_control, "\t{\n");
		if ((return_code = ADF_EMIT_CString(section_ptr->section_name,
			ADF_TRUE, output_function, output_control, error_text)) !=
			ADF_SUCCESS)
			break;
		if ((return_code = ADF_EMIT_CString(section_ptr->output_section_name,
			ADF_TRUE, output_function, output_control, error_text)) !=
			ADF_SUCCESS)
			break;
		(*output_function)(output_control, "\t\t%u,\n",
			section_ptr->area_index);
		(*output_function)(output_control, "\t\tADF_%s,\n",
			(section_ptr->required_flag == ADF_TRUE) ? "TRUE" : "FALSE");
		(*output_function)(output_control, "\t\tADF_%s,\n",
			(section_ptr->wrap_flag == ADF_TRUE) ? "TRUE" : "FALSE");
		(*output_function)(output_control, "\t\tADF_%s,\n",
			(section_ptr->ltrim_flag == ADF_TRUE) ? "TRUE" : "FALSE");
		(*output_function)(output_control, "\t\tADF_%s,\n",
			(section_ptr->rtrim_flag == ADF_TRUE) ? "TRUE" : "FALSE");
		(*output_function)(output_control, "\t\tADF_%s,\n",
			(section_ptr->squeeze_flag == ADF_TRUE) ? "TRUE" : "FALSE");
		(*output_function)(output_control, "\t\tADF_%s,\n",
			(section_ptr->para_format_flag == ADF_TRUE) ? "TRUE" : "FALSE");
		(*output_function)(output_control, "\t\tADF_%s,\n",
			(section_ptr->char_format_flag == ADF_TRUE) ? "TRUE" : "FALSE");
		(*output_function)(output_control, "\t\tADF_%s,\n",
			(section_ptr->eindex_flag == ADF_TRUE) ? "TRUE" : "FALSE");
		(*output_function)(output_control, "\t\tADF_%s,\n",
			(section_ptr->htext_flag == ADF_TRUE) ? "TRUE" : "FALSE");
		sprintf(buffer, "ADF_Def_DOM_%03u_SEC_%03u_MAT_STRL",
			domain_number, count_1);
		if ((return_code = ADF_EMIT_CPat(&section_ptr->match_pattern,
			buffer, ADF_FALSE, output_function, output_control, error_text)) !=
			ADF_SUCCESS)
			break;
		(*output_function)(output_control, "\t}%s\n",
			(count_1 < (section_count - 1)) ? "," : "");
	}

	(*output_function)(output_control, "};\n");

	(*output_function)(output_control, "\n");
	ADF_EMIT_CBorder(output_function, output_control);
	(*output_function)(output_control, "\n");

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_EMIT_CPat(const ADF_PATTERN *pattern_ptr,
	const char *string_list_name, int trailing_comma_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_EMIT_CPat(pattern_ptr, string_list_name, trailing_comma_flag,
	output_function, output_control, error_text)
const ADF_PATTERN     *pattern_ptr;
const char            *string_list_name;
int                    trailing_comma_flag;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_SUCCESS;

	(*output_function)(output_control, "\t\t{\n\t\t\t%u,\n",
		pattern_ptr->pattern_count);

	if (!pattern_ptr->pattern_count)
		(*output_function)(output_control, "\t\t\tNULL,\n");
	else
		(*output_function)(output_control, "\t\t\t%s,\n", string_list_name);

	if (pattern_ptr->pattern_optimization == NULL)
		(*output_function)(output_control, "\t\t\tNULL\n");
	else {
		(*output_function)(output_control, "\t");
		return_code = ADF_EMIT_CString(pattern_ptr->pattern_optimization,
			ADF_FALSE, output_function, output_control, error_text);
	}

	(*output_function)(output_control, "\t\t}%s\n", (trailing_comma_flag) ?
		"," : "");

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_EMIT_CPatStrList(const ADF_PATTERN *pattern_ptr,
	const char *string_list_name, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_EMIT_CPatStrList(pattern_ptr, string_list_name, output_function,
	output_control, error_text)
const ADF_PATTERN     *pattern_ptr;
const char            *string_list_name;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	return(ADF_EMIT_CStringList(pattern_ptr->pattern_count,
		pattern_ptr->pattern_list, string_list_name, output_function,
		output_control, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_EMIT_CStringList(unsigned int string_count, char **string_list,
	const char *string_list_name, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_EMIT_CStringList(string_count, string_list, string_list_name,
	output_function, output_control, error_text)
unsigned int            string_count;
char                  **string_list;
const char             *string_list_name;
STR_FUNC_TYPE_fprintf   output_function;
void                   *output_control;
char                   *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	unsigned int  tmp_length;
	char         *tmp_string;

	if (string_count) {
		(*output_function)(output_control, "static char *%s[%u] = {\n",
			string_list_name, string_count);
		for (count_1 = 0; count_1 < string_count; count_1++) {
			tmp_length = (strlen(string_list[count_1]) * 2) + 1;
			if ((tmp_string = ((char *) malloc(tmp_length * sizeof(char)))) ==
				NULL) {
				strcat(strcpy(error_text, "Unable to allocate memory for C "),
					"structure initialization data");
				return_code = ADF_MEMORY_FAILURE;
				break;
			}
			(*output_function)(output_control, "\t\"%s\"%s\n",
				strescap(strcpy(tmp_string, string_list[count_1]), "\\\"", "\\"),
				(count_1 < (string_count - 1)) ? "," : "");
			free(tmp_string);
		}
		(*output_function)(output_control, "};\n\n");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_EMIT_CString(const char *string_ptr, int trailing_comma_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_EMIT_CString(string_ptr, trailing_comma_flag, output_function,
	output_control, error_text)
const char            *string_ptr;
int                    trailing_comma_flag;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  tmp_length;
	char         *tmp_string;

	if (string_ptr == NULL)
		(*output_function)(output_control, "\t\tNULL%s\n",
			(trailing_comma_flag == ADF_TRUE) ? "," : "");
	else {
		tmp_length = (strlen(string_ptr) * 2) + 1;
		if ((tmp_string = ((char *) malloc(tmp_length * sizeof(char)))) ==
			NULL) {
			strcat(strcpy(error_text, "Unable to allocate memory for C "),
				"structure initialization data");
			return_code = ADF_MEMORY_FAILURE;
		}
		else {
			(*output_function)(output_control, "\t\t\"%s\"%s\n",
				strescap(strcpy(tmp_string, string_ptr), "\\\"", "\\"),
				(trailing_comma_flag) ? "," : "");
			free(tmp_string);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_EMIT_CComment(const char *in_string,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_EMIT_CComment(in_string, output_function, output_control)
const char            *in_string;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	(*output_function)(output_control, "/*\t%-71.71s\t*/\n", in_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_EMIT_CBorder(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_EMIT_CBorder(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	(*output_function)(output_control, "/*\t%s\t*/\n",
"***********************************************************************");
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

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
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;
	ADF_CONTROL  control_data;
	char         error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test routine for function 'ADF_EMIT_DefCDomainList()'\n");
	fprintf(stderr,
		"---- ------- --- -------- --------------------------\n\n");

	ADF_INIT_Control(&control_data);

	if (argc < 2) {
		sprintf(error_text, "Invalid command line encountered.");
		fprintf(stderr, "USAGE:\n   %s %s\n", argv[0],
			"<adf-definition-file> [<adf-definition-file> . . .]");
		return_code = ADF_BAD_ARGS_FAILURE;
	}
	else {
		for (count_1 = 1; count_1 < argc; count_1++) {
			if ((return_code = ADF_ReadDefinitionFile(&control_data,
				argv[count_1], error_text)) == ADF_SUCCESS) {
				return_code = ADF_EMIT_DefCDomainList(control_data.domain_count,
					control_data.domain_list, NULL, NULL, error_text);
				ADF_FreeDomainList(&control_data.domain_count,
					&control_data.domain_list);
			}
			if (return_code != ADF_SUCCESS)
				break;
		}
	}

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

