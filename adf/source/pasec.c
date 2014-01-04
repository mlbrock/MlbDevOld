/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses an ADF section specification.

	Revision History	:	1994-06-13 --- Creation.
									Michael L. Brock
								1997-04-03 --- Revised for new parsing logic.
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

#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
static const SPF_SPEC ADF_PARSE_SectionSpecList[] = {
	{
		"@name",
		{	""	},
		SPF_TYPE_STRING_ML,
		1,	1,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_SECTION, section_name),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@output_name",
		{	""	},
		SPF_TYPE_STRING_ML,
		0,	1,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_SECTION, output_section_name),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@area",
		{	""	},
		ADF_PARSE_TYPE_AREA_NAME,
		1,	1,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_SECTION, area_index),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@required",
		{	""	},
		SPF_TYPE_BOOLEAN,
		0,	1,
		0,	0,
		0.0,	0.0,
		offsetof(ADF_SECTION, required_flag),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@wrap",
		{	""	},
		SPF_TYPE_BOOLEAN,
		0,	1,
		0,	0,
		0.0,	0.0,
		offsetof(ADF_SECTION, wrap_flag),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@ltrim",
		{	""	},
		SPF_TYPE_BOOLEAN,
		0,	1,
		0,	0,
		0.0,	0.0,
		offsetof(ADF_SECTION, ltrim_flag),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@rtrim",
		{	""	},
		SPF_TYPE_BOOLEAN,
		0,	1,
		0,	0,
		0.0,	0.0,
		offsetof(ADF_SECTION, rtrim_flag),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@squeeze",
		{	""	},
		SPF_TYPE_BOOLEAN,
		0,	1,
		0,	0,
		0.0,	0.0,
		offsetof(ADF_SECTION, squeeze_flag),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@para_format",
		{	""	},
		SPF_TYPE_BOOLEAN,
		0,	1,
		0,	0,
		0.0,	0.0,
		offsetof(ADF_SECTION, para_format_flag),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@char_format",
		{	""	},
		SPF_TYPE_BOOLEAN,
		0,	1,
		0,	0,
		0.0,	0.0,
		offsetof(ADF_SECTION, char_format_flag),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@match_pattern",
		{	""	},
		ADF_PARSE_TYPE_PATTERN,
		1,	UINT_MAX,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_SECTION, match_pattern),
		0,
		{
			NULL,
			NULL
		}
	}
};
const unsigned int ADF_PARSE_SectionSpecCount =
	sizeof(ADF_PARSE_SectionSpecList) / sizeof(ADF_PARSE_SectionSpecList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PARSE_Section(SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, void *parent_ptr, unsigned int *section_count,
	ADF_SECTION **section_list, char *error_text)
#else
int ADF_PARSE_Section(context_ptr, spec_ptr, parse_ptr, parent_ptr,
	section_count, section_list, error_text)
SPF_CONTEXT      *context_ptr;
const SPF_SPEC   *spec_ptr;
const SPF_PARSE  *parse_ptr;
void             *parent_ptr;
unsigned int     *section_count;
ADF_SECTION     **section_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code;
	unsigned int count_1;
	ADF_SECTION  tmp_section;

	ADF_INIT_Section(&tmp_section);

	if ((return_code = SPF_PARSE_Complex(context_ptr, spec_ptr, parse_ptr,
		ADF_PARSE_SectionSpecCount, ADF_PARSE_SectionSpecList, parent_ptr,
		&tmp_section, error_text)) != SPF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = ADF_PARSE_OptPat(&tmp_section.match_pattern,
		error_text)) != SPF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((tmp_section.output_section_name == NULL) &&
		((tmp_section.output_section_name =
		strdup(tmp_section.section_name)) == NULL)) {
		STR_AllocMsgItem(strlen(tmp_section.section_name) + 1, error_text,
			"Unable to copy the section output name.");
		return_code = SPF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < *section_count; count_1++) {
		if (!stricmp((*section_list)[count_1].section_name,
			tmp_section.section_name)) {
			sprintf(error_text,
				"The section named '%-.500s' is multiply-defined.",
				tmp_section.section_name);
			return_code = SPF_PARSE_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	if (mema_append(section_count, ((void **) section_list),
		&tmp_section, sizeof(tmp_section)) != STRFUNCS_SUCCESS) {
		STR_AllocMsgList(*section_count + 1, sizeof(**section_list), error_text,
			"Unable to allocate memory for an additional '%s()' definition",
			spec_ptr->name);
		return_code = SPF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

EXIT_FUNCTION:

	if (return_code != ADF_SUCCESS)
		ADF_FREE_Section(&tmp_section);

	return(return_code);
}
/*	***********************************************************************	*/

