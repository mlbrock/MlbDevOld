/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Optimizes an ADF pattern specification.

	Revision History	:	1995-08-15 --- Creation.
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

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PARSE_OptPat(ADF_PATTERN *in_pattern, char *error_text)
#else
int ADF_PARSE_OptPat(in_pattern, error_text)
ADF_PATTERN *in_pattern;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	unsigned int   tmp_count_1 = 0;
	char         **tmp_list_1  = NULL;
	unsigned int   tmp_count_2 = 0;
	char         **tmp_list_2  = NULL;
	char          *tmp_string  = NULL;
	unsigned int   tmp_length;
	unsigned int   max_length  = 0;
	unsigned int   check_index = 0;
	unsigned int   count_1;
	unsigned int   count_2;
	unsigned int   found_index;

	if (in_pattern->pattern_optimization != NULL) {
		free(in_pattern->pattern_optimization);
		in_pattern->pattern_optimization = NULL;
	}

	for (count_1 = 0; count_1 < in_pattern->pattern_count; count_1++) {
		if ((tmp_string = ((char *)
			calloc((strlen(in_pattern->pattern_list[count_1]) * 2) + 1,
			sizeof(char)))) == NULL) {
			STR_AllocMsgItem((strlen(in_pattern->pattern_list[count_1]) * 2) + 1,
				error_text, "%s", "Unable to allocate temporary pattern buffer");
			return_code = ADF_MEMORY_FAILURE;
			break;
		}
		trim(oneblank(nocontrl(strcpy(tmp_string,
			in_pattern->pattern_list[count_1]))));
		tmp_length = strlen(tmp_string);
		for (count_2 = 0; count_2 < tmp_length; count_2++) {
			if (!strnicmp(tmp_string + count_2, "(S)", 3))
				memset(tmp_string + count_2, ' ', 3);
			else if (strchr("`~!@#$%^&*()-_=+{[]}\\|;'\",<.>/?",
				tmp_string[count_2]) != NULL)
				tmp_string[count_2] = ' ';
			else if (isspace(tmp_string[count_2]) && (count_2 > 1) &&
				(tmp_string[count_2 - 1] == 'S') &&
				(!isspace(tmp_string[count_2 - 2])))
				tmp_string[count_2 - 1] = ' ';
		}
		if (sepwordl(trim(oneblank(tmp_string)),
			(!count_1) ? &tmp_count_1 : &tmp_count_2, (!count_1) ?
			&tmp_list_1 : &tmp_list_2) != STRFUNCS_SUCCESS) {
			STR_AllocMsgPtrList(chrcnt(tmp_string, ',') + 1, strlen(tmp_string) +
				chrcnt(tmp_string, ',') + 1, error_text, "%s",
				"Unable to create the temporary pattern buffer component list");
			return_code = ADF_MEMORY_FAILURE;
			break;
		}
		strl_sort((!count_1) ?  tmp_count_1 :  tmp_count_2,
			(!count_1) ? tmp_list_1 :  tmp_list_2);
		strl_uniq((!count_1) ? &tmp_count_1 : &tmp_count_2,
			(!count_1) ? &tmp_list_1 : &tmp_list_2);
		if (count_1) {
			for (count_2 = 0; count_2 < tmp_count_1; ) {
				if (strl_find(tmp_count_2, tmp_list_2, tmp_list_1[count_2],
					&found_index) != STRFUNCS_ITEM_FOUND)
					strl_remove(&tmp_count_1, &tmp_list_1, count_2, 1);
				else
					count_2++;
			}
		}
		if (!tmp_count_1)
			break;
		free(tmp_string);
		tmp_string = NULL;
		strl_remove_all(&tmp_count_2, &tmp_list_2);
	}

	if (tmp_count_1) {
		for (count_1 = 0; count_1 < tmp_count_1; count_1++) {
			if (max_length < strlen(tmp_list_1[count_1])) {
				check_index = count_1;
				max_length  = strlen(tmp_list_1[count_1]);
			}
		}
		in_pattern->pattern_optimization = tmp_list_1[check_index];
		tmp_list_1[check_index]          = NULL;
	}

	if (tmp_string != NULL)
		free(tmp_string);

	strl_remove_all(&tmp_count_1, &tmp_list_1);
	strl_remove_all(&tmp_count_2, &tmp_list_2);

	return(return_code);
}
/*	***********************************************************************	*/

