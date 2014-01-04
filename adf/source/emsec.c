/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs one section of an ADF domain specification
								to the specified output handler.

	Revision History	:	1994-06-15 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
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
void ADF_EMIT_SectionDef(const ADF_SECTION *section_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void ADF_EMIT_SectionDef(section_ptr, output_function, output_control)
const ADF_SECTION     *section_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	char buffer[ADF_AREA_NAME_LENGTH];

	output_function = (output_function != NULL) ? output_function :
		STR_FUNC_TYPE_fprintf_CAST(fprintf);
	output_control  = (output_control  != NULL) ? output_control  : stdout;

	(*output_function)(output_control, "\t@SECTION(\n");
	(*output_function)(output_control, "\t\t@NAME(\"%s\"),\n",
		section_ptr->section_name);
	(*output_function)(output_control, "\t\t@OUTPUT_NAME(\"%s\"),\n",
		section_ptr->output_section_name);
	(*output_function)(output_control, "\t\t@AREA(%s),\n",
		ADF_GetParseAreaName(section_ptr->area_index, buffer));
	(*output_function)(output_control, "\t\t@REQUIRED(%s),\n",
		(section_ptr->required_flag == ADF_TRUE) ? "TRUE" : "FALSE");
	(*output_function)(output_control, "\t\t@WRAP(%s),\n",
		(section_ptr->wrap_flag == ADF_TRUE) ? "TRUE" : "FALSE");
	(*output_function)(output_control, "\t\t@LTRIM(%s),\n",
		(section_ptr->ltrim_flag == ADF_TRUE) ? "TRUE" : "FALSE");
	(*output_function)(output_control, "\t\t@RTRIM(%s),\n",
		(section_ptr->rtrim_flag == ADF_TRUE) ? "TRUE" : "FALSE");
	(*output_function)(output_control, "\t\t@SQUEEZE(%s),\n",
		(section_ptr->squeeze_flag == ADF_TRUE) ? "TRUE" : "FALSE");
	(*output_function)(output_control, "\t\t@PARA_FORMAT(%s),\n",
		(section_ptr->para_format_flag == ADF_TRUE) ? "TRUE" : "FALSE");
	(*output_function)(output_control, "\t\t@CHAR_FORMAT(%s),\n",
		(section_ptr->char_format_flag == ADF_TRUE) ? "TRUE" : "FALSE");
	ADF_EMIT_PatternList(&section_ptr->match_pattern, "\t\t@MATCH_PATTERN",
		ADF_FALSE, output_function, output_control);
}
/*	***********************************************************************	*/

