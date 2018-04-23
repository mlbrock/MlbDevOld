/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Contains logic to manage the include and exclude of
								ADF entries.

	Revision History	:	1995-05-15 --- Creation.
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

#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int ADF_BasicClude,
	(const ADF_CLUDE *clude_ptr, const char *text_ptr));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_ApplyCludesEntry(ADF_CONTROL *control_ptr, const char *base_name,
	const char *file_name, const char *file_type, const char *man_page)
#else
int ADF_ApplyCludesEntry(control_ptr, base_name, file_name, file_type,
	man_page)
ADF_CONTROL *control_ptr;
const char  *base_name;
const char  *file_name;
const char  *file_type;
const char  *man_page;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_TRUE;
	unsigned int  count_1;
	const char   *tmp_ptr;

	if (control_ptr->entry_include_count) {
		return_code = ADF_FALSE;
		for (count_1 = 0; count_1 < ADF_CLUDE_TYPE_COUNT; count_1++) {
			tmp_ptr = (count_1 == ADF_CLUDE_TYPE_BASE_NAME) ? base_name :
				(count_1 == ADF_CLUDE_TYPE_FILE_NAME) ? file_name :
				(count_1 == ADF_CLUDE_TYPE_FILE_TYPE) ? file_type : man_page;
			if ((return_code = ADF_BasicClude(&control_ptr->
				entry_clude[ADF_CLUDE_BASIS_INCLUDE][count_1], tmp_ptr)) ==
				ADF_TRUE)
				break;
		}
		if (return_code != ADF_TRUE)
			goto EXIT_FUNCTION;
	}

	if (control_ptr->entry_exclude_count) {
		for (count_1 = 0; count_1 < ADF_CLUDE_TYPE_COUNT; count_1++) {
			tmp_ptr = (count_1 == ADF_CLUDE_TYPE_BASE_NAME) ? base_name :
				(count_1 == ADF_CLUDE_TYPE_FILE_NAME) ? file_name :
				(count_1 == ADF_CLUDE_TYPE_FILE_TYPE) ? file_type : man_page;
			if (ADF_BasicClude(&control_ptr->entry_clude[ADF_CLUDE_BASIS_EXCLUDE]
				[count_1], tmp_ptr) == ADF_TRUE) {
				return_code = ADF_FALSE;
				break;
			}
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_ApplyCludesHText(ADF_CONTROL *control_ptr, const char *hyper_text)
#else
int ADF_ApplyCludesHText(control_ptr, hyper_text)
ADF_CONTROL *control_ptr;
const char  *hyper_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_TRUE;

	if ((control_ptr->htext_include_count) && ((return_code =
		ADF_BasicClude(control_ptr->htext_clude + ADF_CLUDE_BASIS_INCLUDE,
		hyper_text)) != ADF_TRUE))
		goto EXIT_FUNCTION;

	if ((control_ptr->htext_exclude_count) &&
		(ADF_BasicClude(control_ptr->htext_clude + ADF_CLUDE_BASIS_EXCLUDE,
		hyper_text) == ADF_TRUE))
		return_code = ADF_FALSE;

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FREE_CludeItem(ADF_CLUDE *clude_ptr)
#else
void ADF_FREE_CludeItem(clude_ptr)
ADF_CLUDE *clude_ptr;
#endif /* #ifndef NARGS */
{
	strl_remove_all(&clude_ptr->clude_count, &clude_ptr->clude_list);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_INIT_CludeItem(ADF_CLUDE *clude_ptr)
#else
void ADF_INIT_CludeItem(clude_ptr)
ADF_CLUDE *clude_ptr;
#endif /* #ifndef NARGS */
{
	clude_ptr->clude_count = 0;
	clude_ptr->clude_list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_BasicClude(const ADF_CLUDE *clude_ptr, const char *text_ptr)
#else
static int ADF_BasicClude(clude_ptr, text_ptr)
const ADF_CLUDE *clude_ptr;
const char      *text_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int found_index;

	return((strl_find(clude_ptr->clude_count, clude_ptr->clude_list, text_ptr,
		&found_index) == STRFUNCS_ITEM_FOUND) ? ADF_TRUE : ADF_FALSE);
}
/*	***********************************************************************	*/

