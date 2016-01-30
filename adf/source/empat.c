/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs ADF pattern specifications to the specified
								output handler.

	Revision History	:	1995-08-15 --- Creation.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_EMIT_PatternList(const ADF_PATTERN *pattern_ptr,
	const char *pattern_name, int trailing_comma_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void ADF_EMIT_PatternList(pattern_ptr, pattern_name, trailing_comma_flag,
	output_function, output_control)
const ADF_PATTERN     *pattern_ptr;
const char            *pattern_name;
int                    trailing_comma_flag;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	output_function = (output_function != NULL) ? output_function :
		STR_FUNC_TYPE_fprintf_CAST(fprintf);
	output_control  = (output_control  != NULL) ? output_control  : stdout;

	for (count_1 = 0; count_1 < pattern_ptr->pattern_count; count_1++)
		ADF_EMIT_PatternString(pattern_ptr->pattern_list[count_1], pattern_name,
			((count_1 < (pattern_ptr->pattern_count - 1)) ||
			trailing_comma_flag) ? ADF_TRUE : ADF_FALSE, output_function,
			output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_EMIT_PatternString(const char *pattern_string,
	const char *pattern_name, int trailing_comma_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void ADF_EMIT_PatternString(pattern_string, pattern_name, trailing_comma_flag,
	output_function, output_control)
const char            *pattern_string;
const char            *pattern_name;
int                    trailing_comma_flag;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	output_function = (output_function != NULL) ? output_function :
		STR_FUNC_TYPE_fprintf_CAST(fprintf);
	output_control  = (output_control  != NULL) ? output_control  : stdout;

	(*output_function)(output_control, "%s(\"%s\")%s\n", pattern_name,
		pattern_string, (trailing_comma_flag) ? "," : "");
}
/*	***********************************************************************	*/

