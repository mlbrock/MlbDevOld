/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'KML_DOMAIN' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_COPY_Domain

	SYNOPSIS		:	return_code = KML_COPY_Domain(in_ptr, out_ptr, error_text);

						int               return_code;

						const KML_DOMAIN *ptr;

						KML_DOMAIN       *out_ptr;

						char             *error_text;

	DESCRIPTION	:	Copies a ''KML_DOMAIN'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''KML_DOMAIN''
						structure which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''KML_DOMAIN''
						structure into which the copy is to be performed.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''KMLFUNCS_MAX_ERROR_TEXT'' characters in length.

	RETURNS     :	Returns from this function are as follow:

						(.) ''KMLFUNCS_SUCCESS'' if the function completes without
						error. ''KMLFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero KMLFUNCS return codes
						indicative of error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_COPY_DomainList
						KML_FREE_Domain
						KML_INIT_Domain

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_COPY_Domain
						Copy Functions:KML_COPY_Domain
						KML_DOMAIN Functions:KML_COPY_Domain

	PUBLISH XREF:	KML_COPY_Domain

	PUBLISH NAME:	KML_COPY_Domain

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int KML_COPY_Domain(const KML_DOMAIN *in_ptr, KML_DOMAIN *out_ptr,
	char *error_text)
#else
int KML_COPY_Domain(in_ptr, out_ptr, error_text)
const KML_DOMAIN *in_ptr;
KML_DOMAIN       *out_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = KML_MEMORY_FAILURE;
	char tmp_error_text[KML_MAX_ERROR_TEXT];

	KML_INIT_Domain(out_ptr);

	if ((out_ptr->domain_name =
		strdup(STRFUNCS_NULL_TO_STR(in_ptr->domain_name))) == NULL)
		STR_AllocMsgItem(strlen(STRFUNCS_NULL_TO_STR(in_ptr->domain_name)) + 1,
			error_text, "Unable to copy the 'KML_DOMAIN' member 'domain_name'");
	else if ((out_ptr->domain_description =
		strdup(STRFUNCS_NULL_TO_STR(in_ptr->domain_description))) == NULL)
		STR_AllocMsgItem(
			strlen(STRFUNCS_NULL_TO_STR(in_ptr->domain_description)) + 1,
			error_text,
			"Unable to copy the 'KML_DOMAIN' member 'domain_description'");
	else if (strl_copy(in_ptr->type_count, in_ptr->type_list,
		&out_ptr->type_count, &out_ptr->type_list) != STRFUNCS_SUCCESS)
		sprintf(error_text, "%s --- %u elements in the list.",
			"Unable to copy the 'KML_DOMAIN' member 'type_list'",
			in_ptr->type_count);
	else if (((return_code = KML_COPY_StringList(in_ptr->string_count,
		in_ptr->string_list, &out_ptr->string_count, &out_ptr->string_list,
		tmp_error_text)) != KML_SUCCESS) ||
		((return_code = KML_COPY_CommentList(in_ptr->comment_count,
		in_ptr->comment_list, &out_ptr->comment_count, &out_ptr->comment_list,
		tmp_error_text)) != KML_SUCCESS) ||
		((return_code = KML_COPY_KeywordList(in_ptr->keyword_count,
		in_ptr->keyword_list, &out_ptr->keyword_count, &out_ptr->keyword_list,
		tmp_error_text)) != KML_SUCCESS) ||
		((return_code = KML_COPY_SymbolList(in_ptr->symbol_count,
		in_ptr->symbol_list, &out_ptr->symbol_count, &out_ptr->symbol_list,
		tmp_error_text)) != KML_SUCCESS) ||
		((return_code = KML_COPY_BlockList(in_ptr->block_count,
		in_ptr->block_list, &out_ptr->block_count, &out_ptr->block_list,
		tmp_error_text)) != KML_SUCCESS) ||
		((return_code = KML_COPY_NameList(in_ptr->name_count,
		in_ptr->name_list, &out_ptr->name_count, &out_ptr->name_list,
		tmp_error_text)) != KML_SUCCESS) ||
		((return_code = KML_COPY_OperatorList(in_ptr->operator_count,
		in_ptr->operator_list, &out_ptr->operator_count,
		&out_ptr->operator_list,
		tmp_error_text)) != KML_SUCCESS))
		strcat(strcpy(error_text,
			"Unable to copy a 'KML_DOMAIN' list member: "), tmp_error_text);
	else {
		out_ptr->string_case_flag   = in_ptr->string_case_flag;
		out_ptr->comment_case_flag  = in_ptr->comment_case_flag;
		out_ptr->keyword_case_flag  = in_ptr->keyword_case_flag;
		out_ptr->symbol_case_flag   = in_ptr->symbol_case_flag;
		out_ptr->block_case_flag    = in_ptr->block_case_flag;
		out_ptr->name_case_flag     = in_ptr->name_case_flag;
		return_code                 = KML_BuildIndex(out_ptr, error_text);
	}

	if (return_code != KML_SUCCESS)
		KML_FREE_Domain(out_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_COPY_DomainList

	SYNOPSIS		:	return_code = KML_COPY_DomainList(in_count, in_list,
							out_count, out_list, error_text);

						int                return_code;

						unsigned int       count;

						const KML_DOMAIN  *list;

						unsigned int      *out_count;

						KML_DOMAIN       **out_list;

						char              *error_text;

	DESCRIPTION	:	Copies an array of ''KML_DOMAIN'' structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_DOMAIN'' structures
						which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of
						''KML_DOMAIN'' structures which will be allocated and
						copied by this function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''KMLFUNCS_MAX_ERROR_TEXT'' characters in length.

	RETURNS     :	Returns from this function are as follow:

						(.) ''KMLFUNCS_SUCCESS'' if the function completes without
						error. ''KMLFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero KMLFUNCS return codes
						indicative of error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_COPY_Domain
						KML_FREE_DomainList
						KML_INIT_DomainList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_COPY_DomainList
						Copy Functions:KML_COPY_DomainList
						KML_DOMAIN Functions:KML_COPY_DomainList

	PUBLISH XREF:	KML_COPY_DomainList

	PUBLISH NAME:	KML_COPY_DomainList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int KML_COPY_DomainList(unsigned int in_count, const KML_DOMAIN *in_list,
	unsigned int *out_count, KML_DOMAIN **out_list, char *error_text)
#else
int KML_COPY_DomainList(in_count, in_list, out_count, out_list, error_text)
unsigned int       in_count;
const KML_DOMAIN  *in_list;
unsigned int      *out_count;
KML_DOMAIN       **out_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = KML_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((KML_DOMAIN *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to copy a list of 'KML_DOMAIN' structures");
			return_code = KML_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			KML_INIT_DomainList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = KML_COPY_Domain(in_list + count_1,
					*out_list + count_1, error_text)) != KML_SUCCESS) {
					KML_FREE_DomainList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

