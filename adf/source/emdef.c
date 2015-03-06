/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs the list of ADF domain definitions to the
								specified output handler.

	Revision History	:	1994-06-15 --- Creation.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_EMIT_Def(unsigned int domain_count, const ADF_DOMAIN *domain_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void ADF_EMIT_Def(domain_count, domain_list, output_function, output_control)
unsigned int           domain_count;
const ADF_DOMAIN      *domain_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	output_function = (output_function != NULL) ? output_function :
		STR_FUNC_TYPE_fprintf_CAST(fprintf);
	output_control  = (output_control  != NULL) ? output_control  : stdout;

	for (count_1 = 0; count_1 < domain_count; count_1++)
		ADF_EMIT_DomainDef(domain_list + count_1, output_function,
			output_control);
}
/*	***********************************************************************	*/

