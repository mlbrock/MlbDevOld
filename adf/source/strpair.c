/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages use of the 'ADF_STRING_PAIR' structure.

	Revision History	:	1996-07-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int ADF_SCMP_StringPair,
	(void *control_ptr,
	const ADF_STRING_PAIR *ptr_1, const ADF_STRING_PAIR *ptr_2,
	size_t data_length));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_StringPairParse(const char *string_pair_name,
	const char *string_pair_data, unsigned int *string_pair_count,
	ADF_STRING_PAIR **string_pair_list, char *error_text)
#else
int ADF_StringPairParse(string_pair_name, string_pair_data, string_pair_count,
	string_pair_list, error_text)
const char       *string_pair_name;
const char       *string_pair_data;
unsigned int     *string_pair_count;
ADF_STRING_PAIR **string_pair_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code;
	char *tmp_ptr;
	char *tmp_string;
	char  tmp_error_text[ADF_MAX_ERROR_TEXT];

	if ((tmp_string = strdup(string_pair_data)) == NULL) {
		sprintf(error_text, "Unable to copy '%-.500s' string pair data.",
			string_pair_name);
		return_code = ADF_MEMORY_FAILURE;
	}
	else {
		if ((tmp_ptr = strrchr(tmp_string, '=')) != NULL) {
			*tmp_ptr++ = '\0';
			if (!(*tmp_ptr))
				tmp_ptr = NULL;
		}
		if ((return_code = ADF_SEARCH_StrPairList(tmp_string, tmp_ptr,
			string_pair_count, string_pair_list, tmp_error_text)) != ADF_SUCCESS)
			sprintf(error_text,
				"Error occurred while copying the '%-.500s' string pair list: %s",
				string_pair_name, tmp_error_text);
		free(tmp_string);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_StrPairAlloc(const char *string_ptr_1, const char *string_ptr_2,
	ADF_STRING_PAIR *string_pair_ptr, char *error_text)
#else
int ADF_StrPairAlloc(string_ptr_1, string_ptr_2, string_pair_ptr, error_text)
const char      *string_ptr_1;
const char      *string_ptr_2;
ADF_STRING_PAIR *string_pair_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_MEMORY_FAILURE;

	ADF_StrPairInit(string_pair_ptr);

	if ((string_ptr_1 != NULL) && ((string_pair_ptr->ptr_1 =
		strdup(string_ptr_1)) != NULL)) {
		if ((string_ptr_2 != NULL) && ((string_pair_ptr->ptr_2 =
			strdup(string_ptr_2)) == NULL))
			ADF_StrPairFree(string_pair_ptr);
		else
			return_code = ADF_SUCCESS;
	}

	if (return_code != ADF_SUCCESS)
		strcpy(error_text, "Unable to allocate 'ADF_STRING_PAIR' memory.");

	return(return_code);

}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_StrPairListAlloc(const char *string_ptr_1, const char *string_ptr_2,
	unsigned int *string_pair_count, ADF_STRING_PAIR **string_pair_list,
	char *error_text)
#else
int ADF_StrPairListAlloc(string_ptr_1, string_ptr_2, string_pair_count,
	string_pair_list, error_text)
const char       *string_ptr_1;
const char       *string_ptr_2;
unsigned int     *string_pair_count;
ADF_STRING_PAIR **string_pair_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code;
	ADF_STRING_PAIR tmp_string_pair;

	if ((return_code = ADF_StrPairAlloc(string_ptr_1, string_ptr_2,
		&tmp_string_pair, error_text)) == ADF_SUCCESS) {
		if (mema_append(string_pair_count, ((void **) string_pair_list),
			&tmp_string_pair, sizeof(tmp_string_pair)) != STRFUNCS_SUCCESS) {
			ADF_StrPairFree(&tmp_string_pair);
			strcpy(error_text, "Unable to expand string pair list.");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_StrPairFree(ADF_STRING_PAIR *string_pair_ptr)
#else
void ADF_StrPairFree(string_pair_ptr)
ADF_STRING_PAIR *string_pair_ptr;
#endif /* #ifndef NARGS */
{
	if (string_pair_ptr->ptr_1 != NULL)
		free(string_pair_ptr->ptr_1);
	if (string_pair_ptr->ptr_2 != NULL)
		free(string_pair_ptr->ptr_2);

	ADF_StrPairInit(string_pair_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_StrPairListFree(unsigned int *string_pair_count,
	ADF_STRING_PAIR **string_pair_list)
#else
void ADF_StrPairListFree(string_pair_count, string_pair_list)
unsigned int     *string_pair_count;
ADF_STRING_PAIR **string_pair_list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < *string_pair_count; count_1++)
		ADF_StrPairFree(*string_pair_list + count_1);

	if (*string_pair_list != NULL)
		free(*string_pair_list);

	*string_pair_count = 0;
	*string_pair_list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_StrPairInit(ADF_STRING_PAIR *string_pair_ptr)
#else
void ADF_StrPairInit(string_pair_ptr)
ADF_STRING_PAIR *string_pair_ptr;
#endif /* #ifndef NARGS */
{
	memset(string_pair_ptr, '\0', sizeof(*string_pair_ptr));

	string_pair_ptr->ptr_1 = NULL;
	string_pair_ptr->ptr_2 = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_SEARCH_StrPairList(const char *string_ptr_1, const char *string_ptr_2,
	unsigned int *string_pair_count, ADF_STRING_PAIR **string_pair_list,
	char *error_text)
#else
int ADF_SEARCH_StrPairList(string_ptr_1, string_ptr_2, string_pair_count,
	string_pair_list, error_text)
const char       *string_ptr_1;
const char       *string_ptr_2;
unsigned int     *string_pair_count;
ADF_STRING_PAIR **string_pair_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code;
	unsigned int    found_index;
	ADF_STRING_PAIR tmp_string_pair;

	if ((return_code = ADF_StrPairAlloc(string_ptr_1, string_ptr_2,
		&tmp_string_pair, error_text)) == ADF_SUCCESS) {
		if (STR_ARRAY_bsearch(NULL, *string_pair_count, *string_pair_list,
			&tmp_string_pair, sizeof(tmp_string_pair), &found_index,
			STRFUNCS_DIRECTION_TOP, STR_CMP_FUNC_CAST(ADF_SCMP_StringPair)) ==
			STRFUNCS_ITEM_FOUND) {
			ADF_StrPairFree(*string_pair_list + found_index);
			(*string_pair_list)[found_index] = tmp_string_pair;
		}
		else if (mema_insert(string_pair_count, ((void **) string_pair_list),
			&tmp_string_pair, sizeof(tmp_string_pair), found_index) !=
			STRFUNCS_SUCCESS) {
			ADF_StrPairFree(&tmp_string_pair);
			strcpy(error_text, "Unable to expand string pair list.");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_SCMP_StringPair(void *control_ptr, const ADF_STRING_PAIR *ptr_1,
	const ADF_STRING_PAIR *ptr_2, size_t data_length)
#else
static int ADF_SCMP_StringPair(control_ptr, ptr_1, ptr_2, data_length)
void                  *control_ptr;
const ADF_STRING_PAIR *ptr_1;
const ADF_STRING_PAIR *ptr_2;
size_t                 data_length;
#endif /* #ifndef NARGS */
{
	return(((ptr_1->ptr_2 != NULL) && (ptr_2->ptr_2 == NULL)) ? 1 :
		((ptr_1->ptr_2 == NULL) && (ptr_2->ptr_2 != NULL)) ? -1 :
		((ptr_1->ptr_2 == NULL) && (ptr_2->ptr_2 == NULL)) ? 0  :
		strcmp(ptr_1->ptr_2, ptr_2->ptr_2));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

