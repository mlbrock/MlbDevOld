/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Supports common output functionality.

	Revision History	:	1995-07-27 --- Creation.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUT_AllocFileString(ADF_CONTROL *control_ptr,
	unsigned int alloc_length, char *error_text)
#else
int ADF_OUT_AllocFileString(control_ptr, alloc_length, error_text)
ADF_CONTROL  *control_ptr;
unsigned int  alloc_length;
char         *error_text;
#endif /* #ifndef NARGS */
{
	return(ADF_OUT_AllocString(alloc_length, "the complete file name string",
		&control_ptr->output_file_name_length,
		&control_ptr->output_file_name, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUT_AllocHTextString(ADF_CONTROL *control_ptr,
	unsigned int link_length, char *error_text)
#else
int ADF_OUT_AllocHTextString(control_ptr, link_length, error_text)
ADF_CONTROL  *control_ptr;
unsigned int  link_length;
char         *error_text;
#endif /* #ifndef NARGS */
{
	return(ADF_OUT_AllocString(link_length, "a hyper text link string",
		&control_ptr->htext_link_name_length, &control_ptr->htext_link_name,
		error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUT_AllocString(unsigned int alloc_length, const char *alloc_text,
	unsigned int *string_length, char **string_ptr, char *error_text)
#else
int ADF_OUT_AllocString(alloc_length, alloc_text, string_length, string_ptr,
	error_text)
unsigned int   alloc_length;
const char    *alloc_text;
unsigned int  *string_length;
char         **string_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code = ADF_SUCCESS;
	char *tmp_ptr;

	if (alloc_length > *string_length) {
		tmp_ptr = ((char *) ((*string_ptr == NULL) ?
			calloc(alloc_length, sizeof(char)) :
			realloc(*string_ptr, alloc_length * sizeof(char))));
		if (tmp_ptr != NULL) {
			*string_length = alloc_length;
			*string_ptr    = tmp_ptr;
		}
		else {
			sprintf(error_text, "%s %s failed (%u bytes required).",
				"Attempt to allocate", alloc_text, alloc_length);
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *ADF_OUT_CleanName(char *in_name)
#else
char *ADF_OUT_CleanName(in_name)
char *in_name;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr = in_name;

	while (*tmp_ptr) {
		*tmp_ptr = ((char) ((isgraph(*tmp_ptr)) ? *tmp_ptr : ((char) '_')));
		tmp_ptr++;
	}

	return(in_name);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUT_OpenOutputFile(ADF_CONTROL *control_ptr, char *error_text)
#else
int ADF_OUT_OpenOutputFile(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_SUCCESS;

	ADF_OUT_CleanName(control_ptr->output_file_name);

	if ((control_ptr->output_file_ptr = fopen(control_ptr->output_file_name,
		"w")) == NULL) {
		sprintf(error_text,
			"Unable to open output file '%-.500s' for writing: ",
			control_ptr->output_file_name);
		ADF_GetLastErrorString(error_text);
		return_code = ADF_SYSTEM_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_OUT_LogOutputFile(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const char *output_file_name)
#else
void ADF_OUT_LogOutputFile(control_ptr, entry_ptr, output_file_name)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
const char      *output_file_name;
#endif /* #ifndef NARGS */
{
	if (control_ptr->log_flag == ADF_TRUE)
		MLOG_LogInfo(control_ptr->mlog_ptr, "%s '%s' %s '%s' %s '%s' %s '%s'.\n",
			"Wrote the ADF entry named", entry_ptr->base_name,
			"defined in the source file", entry_ptr->full_name,
			"in the ADF database file",
			control_ptr->in_file_list[entry_ptr->file_index].file_name,
			(output_file_name == NULL) ? "to" : "to the output file",
			(output_file_name == NULL) ? "stdout" : output_file_name);
}
/*	***********************************************************************	*/

