/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parse an ADF domain specification.

	Revision History	:	1994-06-10 --- Creation.
									Michael L. Brock
								1997-04-03 --- Revised for new parsing logic.
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
COMPAT_FN_DECL_STATIC(int ADF_PARSE_OptPatDomain,
	(ADF_DOMAIN *domain_ptr, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
static const SPF_SPEC ADF_PARSE_DomainSpecList[] = {
	{
		"@name",
		{	""	},
		SPF_TYPE_STRING_ML,
		1,	1,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_DOMAIN, domain_name),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@description",
		{	""	},
		SPF_TYPE_STRING_ML,
		0,	1,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_DOMAIN, domain_description),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@file_type",
		{	""	},
		SPF_TYPE_STRING_ML_LIST,
		1,	UINT_MAX,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_DOMAIN, file_type_count),
		offsetof(ADF_DOMAIN, file_type_list),
		{
			NULL,
			NULL
		}
	},
	{
		"@boh_pattern",
		{	""	},
		ADF_PARSE_TYPE_PATTERN,
		1,	UINT_MAX,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_DOMAIN, boh_pattern),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@eoh_pattern",
		{	""	},
		ADF_PARSE_TYPE_PATTERN,
		1,	UINT_MAX,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_DOMAIN, eoh_pattern),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@bol_pattern",
		{	""	},
		ADF_PARSE_TYPE_PATTERN,
		0,	UINT_MAX,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_DOMAIN, bol_pattern),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@eol_pattern",
		{	""	},
		ADF_PARSE_TYPE_PATTERN,
		0,	UINT_MAX,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_DOMAIN, eol_pattern),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@empty_line_pattern",
		{	""	},
		ADF_PARSE_TYPE_PATTERN,
		0,	UINT_MAX,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_DOMAIN, empty_line_pattern),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@strip_pattern",
		{	""	},
		ADF_PARSE_TYPE_PATTERN,
		0,	UINT_MAX,
		1,	UINT_MAX,
		0.0,	0.0,
		offsetof(ADF_DOMAIN, strip_pattern),
		0,
		{
			NULL,
			NULL
		}
	},
	{
		"@section",
		{	""	},
		ADF_PARSE_TYPE_SECTION,
		1,	UINT_MAX,
		0,	0,
		0.0,	0.0,
		offsetof(ADF_DOMAIN, section_count),
		offsetof(ADF_DOMAIN, section_list),
		{
			ADF_PARSE_Any,
			NULL
		}
	}
};
const unsigned int ADF_PARSE_DomainSpecCount =
	sizeof(ADF_PARSE_DomainSpecList) / sizeof(ADF_PARSE_DomainSpecList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PARSE_Domain(SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, void *parent_ptr, unsigned int *domain_count,
	ADF_DOMAIN **domain_list, char *error_text)
#else
int ADF_PARSE_Domain(context_ptr, spec_ptr, parse_ptr, parent_ptr,
	domain_count, domain_list, error_text)
SPF_CONTEXT      *context_ptr;
const SPF_SPEC   *spec_ptr;
const SPF_PARSE  *parse_ptr;
void             *parent_ptr;
unsigned int     *domain_count;
ADF_DOMAIN      **domain_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code;
	unsigned int count_1;
	ADF_DOMAIN   tmp_domain;

	ADF_INIT_Domain(&tmp_domain);

	if ((return_code = SPF_PARSE_Complex(context_ptr, spec_ptr, parse_ptr,
		ADF_PARSE_DomainSpecCount, ADF_PARSE_DomainSpecList, parent_ptr,
		&tmp_domain, error_text)) != SPF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = ADF_PARSE_OptPatDomain(&tmp_domain, error_text)) !=
		SPF_SUCCESS)
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < *domain_count; count_1++) {
		if (!stricmp((*domain_list)[count_1].domain_name,
			tmp_domain.domain_name)) {
			ADF_FREE_Domain(*domain_list + count_1);
			(*domain_list)[count_1] = tmp_domain;
			goto EXIT_FUNCTION;
		}
	}

	if (mema_append(domain_count, ((void **) domain_list), &tmp_domain,
		sizeof(tmp_domain)) != STRFUNCS_SUCCESS) {
		STR_AllocMsgList(*domain_count + 1, sizeof(**domain_list), error_text,
			"Unable to allocate memory for an additional '%s()' definition",
			spec_ptr->name);
		return_code = SPF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

EXIT_FUNCTION:

	if (return_code != ADF_SUCCESS)
		ADF_FREE_Domain(&tmp_domain);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_PARSE_OptPatDomain(ADF_DOMAIN *domain_ptr, char *error_text)
#else
static int ADF_PARSE_OptPatDomain(domain_ptr, error_text)
ADF_DOMAIN *domain_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = ADF_PARSE_OptPat(&domain_ptr->boh_pattern,
		error_text)) == SPF_SUCCESS) {
		if ((return_code = ADF_PARSE_OptPat(&domain_ptr->eoh_pattern,
			error_text)) == SPF_SUCCESS) {
			if ((return_code = ADF_PARSE_OptPat(&domain_ptr->bol_pattern,
				error_text)) == SPF_SUCCESS) {
				if ((return_code = ADF_PARSE_OptPat(&domain_ptr->eol_pattern,
					error_text)) == SPF_SUCCESS) {
					if ((return_code =
						ADF_PARSE_OptPat(&domain_ptr->empty_line_pattern,
						error_text)) == SPF_SUCCESS)
						return_code =
							ADF_PARSE_OptPat(&domain_ptr->strip_pattern, error_text);
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

