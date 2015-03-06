/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets pointers to the output-specific functions for
								the specified ADF output type.

	Revision History	:	1995-12-10 --- Creation.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_GetOutputFunctions(int output_type,
	int  (**init_function)(ADF_CONTROL *control_ptr, char *error_text),
	int  (**by_entry_function)(ADF_CONTROL *control_ptr,
		const ADF_ENTRY *entry_ptr, char *error_text),
	int  (**to_stdout_function)(ADF_CONTROL *control_ptr,
		const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text),
	int  (**by_file_function)(ADF_CONTROL *control_ptr,
		unsigned int *entry_index, char *error_text),
	int  (**toc_function)(ADF_CONTROL *control_ptr, char *error_text),
	int  (**class_toc_function)(ADF_CONTROL *control_ptr, char *error_text),
	int  (**tof_function)(ADF_CONTROL *control_ptr, char *error_text),
	int  (**index_function)(ADF_CONTROL *control_ptr, char *error_text),
	int  (**perm_index_function)(ADF_CONTROL *control_ptr, char *error_text),
	void (**output_start_function)(ADF_CONTROL *control_ptr,
		const char *output_name, const time_t *output_date,
		STR_FUNC_TYPE_fprintf output_function, void *output_control),
	void (**output_end_function)(ADF_CONTROL *control_ptr,
		STR_FUNC_TYPE_fprintf output_function, void *output_control),
	void (**output_between_function)(ADF_CONTROL *control_ptr,
		const ADF_ENTRY *entry_ptr, const char *output_name,
		STR_FUNC_TYPE_fprintf output_function, void *output_control),
	char *error_text)
#else
int ADF_GetOutputFunctions(output_type, init_function, by_entry_function,
	to_stdout_function, by_file_function, toc_function, class_toc_function,
	tof_function, index_function, perm_index_function, output_start_function,
	output_end_function, output_between_function, error_text)
int     output_type;
int  (**init_function)();
int  (**by_entry_function)();
int  (**to_stdout_function)();
int  (**by_file_function)();
int  (**toc_function)();
int  (**class_toc_function)();
int  (**tof_function)();
int  (**index_function)();
int  (**perm_index_function)();
void (**output_start_function)();
void (**output_end_function)();
void (**output_between_function)();
char   *error_text;
#endif /* #ifndef NARGS */
{
	int     return_code = ADF_SUCCESS;
#ifndef NARGS
	int  (*tmp_init_function)(ADF_CONTROL *control_ptr, char *error_txt);
	int  (*tmp_by_entry_function)(ADF_CONTROL *control_ptr,
		const ADF_ENTRY *entry_ptr, char *error_txt);
	int  (*tmp_to_stdout_function)(ADF_CONTROL *control_ptr,
		const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_txt);
	int  (*tmp_by_file_function)(ADF_CONTROL *control_ptr,
		unsigned int *entry_index, char *error_txt);
	int  (*tmp_toc_function)(ADF_CONTROL *control_ptr, char *error_txt);
	int  (*tmp_class_toc_function)(ADF_CONTROL *control_ptr, char *error_txt);
	int  (*tmp_tof_function)(ADF_CONTROL *control_ptr, char *error_txt);
	int  (*tmp_index_function)(ADF_CONTROL *control_ptr, char *error_txt);
	int  (*tmp_perm_index_function)(ADF_CONTROL *control_ptr, char *error_txt);
	void (*tmp_output_start_function)(ADF_CONTROL *control_ptr,
		const char *output_name, const time_t *output_date,
		STR_FUNC_TYPE_fprintf output_function, void *output_control);
	void (*tmp_output_end_function)(ADF_CONTROL *control_ptr,
		STR_FUNC_TYPE_fprintf output_function, void *output_control);
	void (*tmp_output_between_function)(ADF_CONTROL *control_ptr,
		const ADF_ENTRY *entry_ptr, const char *output_name,
		STR_FUNC_TYPE_fprintf output_function, void *output_control);
#else
	int  (*tmp_init_function)();
	int  (*tmp_by_entry_function)();
	int  (*tmp_to_stdout_function)();
	int  (*tmp_by_file_function)();
	int  (*tmp_toc_function)();
	int  (*tmp_class_toc_function)();
	int  (*tmp_tof_function)();
	int  (*tmp_index_function)();
	int  (*tmp_perm_index_function)();
	void (*tmp_output_start_function)();
	void (*tmp_output_end_function)();
	void (*tmp_output_between_function)();
#endif /* #ifndef NARGS */

	if (output_type == ADF_OUTPUT_TYPE_ASCII)      {
		tmp_init_function           = NULL;
		tmp_by_entry_function       = ADF_ASCII_OutputByEntry;
		tmp_to_stdout_function      = ADF_ASCII_OutputToStdout;
		tmp_by_file_function        = ADF_ASCII_OutputByFile;
		tmp_toc_function            = NULL;
		tmp_class_toc_function      = NULL;
		tmp_tof_function            = NULL;
		tmp_index_function          = NULL;
		tmp_perm_index_function     = NULL;
		tmp_output_start_function   = NULL;
		tmp_output_end_function     = NULL;
		tmp_output_between_function = NULL;
	}
	else if (output_type == ADF_OUTPUT_TYPE_FRAME) {
		tmp_init_function           = NULL;
		tmp_by_entry_function       = ADF_FRAME_OutputByEntry;
		tmp_to_stdout_function      = ADF_FRAME_OutputToStdout;
		tmp_by_file_function        = ADF_FRAME_OutputByFile;
		tmp_toc_function            = NULL;
		tmp_class_toc_function      = NULL;
		tmp_tof_function            = NULL;
		tmp_index_function          = NULL;
		tmp_perm_index_function     = NULL;
		tmp_output_start_function   = ADF_FRAME_OutputStart;
		tmp_output_end_function     = ADF_FRAME_OutputEnd;
		tmp_output_between_function = NULL;
	}
	else if (output_type == ADF_OUTPUT_TYPE_HTML)  {
		tmp_init_function           = NULL;
		tmp_by_entry_function       = ADF_HTML_OutputByEntry;
		tmp_to_stdout_function      = ADF_HTML_OutputToStdout;
		tmp_by_file_function        = ADF_HTML_OutputByFile;
		tmp_toc_function            = ADF_HTML_OutputTOC;
		tmp_class_toc_function      = ADF_HTML_OutputClassTOC;
		tmp_tof_function            = ADF_HTML_OutputTOF;
		tmp_index_function          = ADF_HTML_OutputIndex;
		tmp_perm_index_function     = ADF_HTML_OutputPermIndex;
		tmp_output_start_function   = NULL;
		tmp_output_end_function     = NULL;
		tmp_output_between_function = NULL;
	}
	else if (output_type == ADF_OUTPUT_TYPE_MAN)   {
		tmp_init_function           = NULL;
		tmp_by_entry_function       = ADF_MAN_OutputByEntry;
		tmp_to_stdout_function      = ADF_MAN_OutputToStdout;
		tmp_by_file_function        = ADF_MAN_OutputByFile;
		tmp_toc_function            = NULL;
		tmp_class_toc_function      = NULL;
		tmp_tof_function            = NULL;
		tmp_index_function          = NULL;
		tmp_perm_index_function     = NULL;
		tmp_output_start_function   = NULL;
		tmp_output_end_function     = NULL;
		tmp_output_between_function = NULL;
	}
	else if (output_type == ADF_OUTPUT_TYPE_PS)    {
		tmp_init_function           = NULL;
		tmp_by_entry_function       = ADF_PS_OutputByEntry;
		tmp_to_stdout_function      = ADF_PS_OutputToStdout;
		tmp_by_file_function        = ADF_PS_OutputByFile;
		tmp_toc_function            = NULL;
		tmp_class_toc_function      = NULL;
		tmp_tof_function            = NULL;
		tmp_index_function          = NULL;
		tmp_perm_index_function     = NULL;
		tmp_output_start_function   = NULL;
		tmp_output_end_function     = NULL;
		tmp_output_between_function = NULL;
	}
	else if (output_type == ADF_OUTPUT_TYPE_RTF)   {
		tmp_init_function           = ADF_RTF_OutputInit;
		tmp_by_entry_function       = ADF_RTF_OutputByEntry;
		tmp_to_stdout_function      = ADF_RTF_OutputToStdout;
		tmp_by_file_function        = ADF_RTF_OutputByFile;
		tmp_toc_function            = NULL;
		tmp_class_toc_function      = NULL;
		tmp_tof_function            = NULL;
		tmp_index_function          = NULL;
		tmp_perm_index_function     = NULL;
		tmp_output_start_function   = ADF_RTF_OutputStart;
		tmp_output_end_function     = ADF_RTF_OutputEnd;
		tmp_output_between_function = NULL;
	}
	else {
		tmp_init_function           = NULL;
		tmp_by_entry_function       = NULL;
		tmp_to_stdout_function      = NULL;
		tmp_by_file_function        = NULL;
		tmp_toc_function            = NULL;
		tmp_class_toc_function      = NULL;
		tmp_tof_function            = NULL;
		tmp_index_function          = NULL;
		tmp_perm_index_function     = NULL;
		tmp_output_start_function   = NULL;
		tmp_output_end_function     = NULL;
		tmp_output_between_function = NULL;
		sprintf(error_text, "Invalid output type specified (%d).", output_type);
		return_code = ADF_FAILURE;
	}

	if (init_function != NULL)
		*init_function         = tmp_init_function;
	if (by_entry_function != NULL)
		*by_entry_function     = tmp_by_entry_function;
	if (to_stdout_function != NULL)
		*to_stdout_function    = tmp_to_stdout_function;
	if (by_file_function != NULL)
		*by_file_function      = tmp_by_file_function;
	if (toc_function != NULL)
		*toc_function          = tmp_toc_function;
	if (class_toc_function != NULL)
		*class_toc_function    = tmp_class_toc_function;
	if (tof_function != NULL)
		*tof_function          = tmp_tof_function;
	if (index_function != NULL)
		*index_function        = tmp_index_function;
	if (perm_index_function != NULL)
		*perm_index_function   = tmp_perm_index_function;
	if (output_start_function != NULL)
		*output_start_function = tmp_output_start_function;
	if (output_end_function != NULL)
		*output_end_function   = tmp_output_end_function;
	if (output_between_function != NULL)
		*output_between_function = tmp_output_between_function;

	return(return_code);
}
/*	***********************************************************************	*/

