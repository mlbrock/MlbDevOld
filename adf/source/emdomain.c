/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs a single ADF domain specification to the
								specified output handler.

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
void ADF_EMIT_DomainDef(const ADF_DOMAIN *domain_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void ADF_EMIT_DomainDef(domain_ptr, output_function, output_control)
const ADF_DOMAIN      *domain_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	output_function = (output_function != NULL) ? output_function :
		STR_FUNC_TYPE_fprintf_CAST(fprintf);
	output_control  = (output_control  != NULL) ? output_control  : stdout;

	(*output_function)(output_control, "@DOMAIN(\n");
	(*output_function)(output_control, "\t@NAME(\"%s\"),\n",
		domain_ptr->domain_name);
	(*output_function)(output_control, "\t@DESCRIPTION(\"%s\"),\n",
		domain_ptr->domain_description);
	for (count_1 = 0; count_1 < domain_ptr->file_type_count; count_1++)
		(*output_function)(output_control, "\t@FILE_TYPE(\"%s\"),\n",
			domain_ptr->file_type_list[count_1]);
	ADF_EMIT_PatternList(&domain_ptr->boh_pattern,
		"\t@BOH_PATTERN", ADF_TRUE, output_function, output_control);
	ADF_EMIT_PatternList(&domain_ptr->eoh_pattern,
		"\t@EOH_PATTERN", ADF_TRUE, output_function, output_control);
	ADF_EMIT_PatternList(&domain_ptr->bol_pattern,
		"\t@BOL_PATTERN", ADF_TRUE, output_function, output_control);
	ADF_EMIT_PatternList(&domain_ptr->eol_pattern,
		"\t@EOL_PATTERN", ADF_TRUE, output_function, output_control);
	ADF_EMIT_PatternList(&domain_ptr->empty_line_pattern,
		"\t@EMPTY_LINE_PATTERN", ADF_TRUE, output_function, output_control);
	ADF_EMIT_PatternList(&domain_ptr->strip_pattern,
		"\t@STRIP_PATTERN", ADF_TRUE, output_function, output_control);
	for (count_1 = 0; count_1 < domain_ptr->section_count; count_1++) {
		ADF_EMIT_SectionDef(domain_ptr->section_list + count_1, output_function,
			output_control);
		(*output_function)(output_control, "\t)%s\n",
			(count_1 < (domain_ptr->section_count - 1)) ? "," : "");
	}
	(*output_function)(output_control, ")\n");
}
/*	***********************************************************************	*/

