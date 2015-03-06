/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Validates a subject name as a pattern and creates
								the data necessary for subject name pattern matching.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_MakeSubjectPattern(const char *in_name,
	RVUTIL_SNAME_FLAT *out_pattern, char *error_text)
{
	int           return_code;
	unsigned int  count_1;
	char         *tmp_ptr;

	if ((return_code = RVUTIL_CrackSubjectFlat(in_name, out_pattern,
		error_text)) == RVUTIL_SUCCESS) {
		for (count_1 = 0; count_1 < out_pattern->element_count; count_1++) {
			if (!out_pattern->element_list[count_1][0]) {
				sprintf(error_text, "Element index %u is empty in subject '%s'.",
					count_1, in_name);
				return_code = RVUTIL_INVALID_SUBJECT_ELEMENT;
				break;
			}
			else if (!strcmp(out_pattern->element_list[count_1],
				RVUTIL_ELEMENT_PAT_ANY_STR))
				continue;
			else if (!strcmp(out_pattern->element_list[count_1],
				RVUTIL_ELEMENT_PAT_LAST_STR)) {
				if (count_1 < (out_pattern->element_count - 1)) {
					sprintf(error_text, "%s '%s' %s ('%s') %s %u, %s.",
						"Subject name", in_name,
						"contains a trailing element match pattern character",
						RVUTIL_ELEMENT_PAT_LAST_STR, "in element index",
						count_1, "which is not the last element");
					return_code = RVUTIL_INVALID_SUBJECT_ELEMENT;
				}
				break;
			}
			else if (((tmp_ptr = strchr(out_pattern->element_list[count_1],
				RVUTIL_ELEMENT_PAT_ANY_CHAR)) != NULL) ||
				((tmp_ptr = strchr(out_pattern->element_list[count_1],
				RVUTIL_ELEMENT_PAT_LAST_CHAR)) != NULL)) {
				sprintf(error_text, "%s '%s' %s ('%c') %s %u.",
					"Subject name", in_name,
					"contains a pattern matching meta-character", *tmp_ptr,
					"in element index", count_1);
				return_code = RVUTIL_INVALID_SUBJECT_ELEMENT;
				break;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_MakeSubjectPatternList(unsigned int in_count, char **in_list,
	unsigned int *out_count, RVUTIL_SNAME_FLAT **out_list, char *error_text)
{
	int          return_code = RVUTIL_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((RVUTIL_SNAME_FLAT *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to allocate the subject name pattern list");
			return_code = RVUTIL_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = RVUTIL_MakeSubjectPattern(in_list[count_1],
					*out_list + count_1, error_text)) != RVUTIL_SUCCESS) {
					mema_remove_all(out_count, ((void **) out_list));
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

int main(int argc, char **argv)
{
	unsigned int      count_1;
	unsigned int      count_2;
	RVUTIL_SNAME_FLAT tmp_name;
	char              error_text[RVUTIL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'RVUTIL_MakeSubjectPattern()'\n");
	fprintf(stderr, "---- ------- --- -----------------------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		printf("%05u:[%s] ---> ", count_1, argv[count_1]);
		if (RVUTIL_MakeSubjectPattern(argv[count_1], &tmp_name,
			error_text) != RVUTIL_SUCCESS)
			printf("'RVUTIL_MakeSubjectPattern()' FAILED: %s", error_text);
		else {
			printf("[%3u]",  tmp_name.element_count);
			for (count_2 = 0; count_2 < tmp_name.element_count; count_2++)
				printf("[%s]", tmp_name.element_list[count_2]);
		}
		printf("\n");
	}

	return(0);
}

#endif /* #ifdef TEST_MAIN */

