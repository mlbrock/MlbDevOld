/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Creates a 'PCFF_PARAM_SPEC' structure.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions private to this module . . .			*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int PCFF_AllDomainStringToList,
	(PCFF_PARAM_SPEC *param_spec_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int PCFF_OneDomainStringToList,
	(PCFF_PARAM *param_ptr, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CreateParamSpec(unsigned int structure_size, unsigned int param_count,
	const PCFF_PARAM *param_list, PCFF_PARAM_SPEC *param_spec_ptr,
	char *error_text)
{
	int             return_code;
	PCFF_PARAM_SPEC tmp_param_spec;

	PCFF_InitParamSpec(param_spec_ptr);
	PCFF_InitParamSpec(&tmp_param_spec);

	tmp_param_spec.structure_size = structure_size;
	tmp_param_spec.param_count    = param_count;
	tmp_param_spec.param_list     = ((PCFF_PARAM *) param_list);

	if ((return_code = PCFF_CheckParamSpec(&tmp_param_spec,
		error_text)) == PCFF_SUCCESS) {
		if ((return_code = PCFF_CopyParamSpec(&tmp_param_spec, param_spec_ptr,
			error_text)) == PCFF_SUCCESS) {
			if ((return_code = PCFF_AllDomainStringToList(param_spec_ptr,
				error_text)) != PCFF_SUCCESS)
				PCFF_FreeParamSpec(param_spec_ptr);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int PCFF_AllDomainStringToList(PCFF_PARAM_SPEC *param_spec_ptr,
	char *error_text)
{
	int          return_code = PCFF_SUCCESS;
	unsigned int count_1;

	for (count_1 = 0; count_1 < param_spec_ptr->param_count; count_1++) {
		if ((return_code =
			PCFF_OneDomainStringToList(param_spec_ptr->param_list + count_1,
			error_text)) != PCFF_SUCCESS)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int PCFF_OneDomainStringToList(PCFF_PARAM *param_ptr, char *error_text)
{
	int            return_code = PCFF_SUCCESS;
	char          *tmp_string  = NULL;
	unsigned int   tmp_count_1 = 0;
	char         **tmp_list_1  = NULL;
	unsigned int   tmp_count_2 = 0;
	char         **tmp_list_2  = NULL;
	unsigned int   count_1;
	unsigned int   tmp_length;
	char          *tmp_ptr;

	if ((param_ptr->domain != NULL) && *param_ptr->domain) {
		if ((tmp_string = strdup(param_ptr->domain)) == NULL) {
			STR_AllocMsgItem(strlen(param_ptr->domain) + 1, error_text,
				"Unable to allocate memory for a copy of the parameter domain");
			return_code = PCFF_MEMORY_FAILURE;
		}
		else {
			if (((tmp_length =
				strlen(trim(oneblank(ctltospc(tmp_string))))) > 2) &&
				(*tmp_string == '{') && (tmp_string[tmp_length - 1] == '}')) {
				tmp_string[tmp_length - 1] = '\0';
				if (sepwordx(tmp_string + 1, "|", &tmp_count_1, &tmp_list_1) !=
					STRFUNCS_SUCCESS) {
					STR_AllocMsgPtrList(chrcnt(tmp_string, '|') + 1,
						(tmp_length - 2) - (chrcnt(tmp_string, '|') + 1),
						error_text,
						"Unable to allocate memory for the parameter domain list");
					return_code = PCFF_MEMORY_FAILURE;
				}
				else {
					for (count_1 = 0; count_1 < tmp_count_1; ) {
						if (*trim(tmp_list_1[count_1]))
							count_1++;
						else
							strl_remove(&tmp_count_1, &tmp_list_1, count_1, 1);
					}
					for (count_1 = 0; count_1 < tmp_count_1; count_1++) {
						if ((tmp_ptr = strchr(tmp_list_1[count_1], '=')) != NULL)
							*tmp_ptr++ = '\0';
					}
					if (strl_copy(tmp_count_1, tmp_list_1, &tmp_count_2,
						&tmp_list_2) == STRFUNCS_SUCCESS) {
						strli_sort(tmp_count_2, tmp_list_2);
						strli_uniq(&tmp_count_2, &tmp_list_2);
						if (param_ptr->domain_count &&
							(param_ptr->domain_list != NULL))
							strl_remove_all(&param_ptr->domain_count,
								&param_ptr->domain_list);
						param_ptr->domain_count = tmp_count_2;
						param_ptr->domain_list  = tmp_list_2;
					}
					else {
						strcpy(error_text, "Unable to copy the domain list.");
						return_code = PCFF_MEMORY_FAILURE;						
					}
					strl_remove_all(&tmp_count_1, &tmp_list_1);
				}
			}
			free(tmp_string);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/


