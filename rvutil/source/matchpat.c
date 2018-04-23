/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether a subject name matches a pattern.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_MatchSubject(const char *in_name,
	const RVUTIL_SNAME_FLAT *in_pattern, unsigned int *element_index)
{
	int               return_code = RVUTIL_FALSE;
	RVUTIL_SNAME_FLAT tmp_name;
	char              tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	if (RVUTIL_CrackSubjectFlat(in_name, &tmp_name, tmp_error_text) ==
		RVUTIL_SUCCESS)
		return_code = RVUTIL_MatchSubjectFlat(&tmp_name, in_pattern,
			element_index);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_MatchSubjectWork(const RVUTIL_SNAME_WORK *in_name,
	const RVUTIL_SNAME_FLAT *in_pattern, unsigned int *element_index)
{
	RVUTIL_SNAME_FLAT tmp_name;

	return(RVUTIL_MatchSubjectFlat(RVUTIL_WorkToFlat(in_name, &tmp_name),
		in_pattern, element_index));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_MatchSubjectFlat(const RVUTIL_SNAME_FLAT *in_name,
	const RVUTIL_SNAME_FLAT *in_pattern, unsigned int *element_index)
{
	int          return_code;
	unsigned int count_1;

	if ((in_name->element_count > in_pattern->element_count) &&
		strcmp(in_pattern->element_list[in_pattern->element_count - 1],
		RVUTIL_ELEMENT_PAT_LAST_STR)) {
		if (element_index != NULL)
			*element_index = in_pattern->element_count;
		return_code = RVUTIL_FALSE;
	}
	else if (in_name->element_count < in_pattern->element_count) {
		if (element_index != NULL)
			*element_index = in_name->element_count;
		return_code = RVUTIL_FALSE;
	}
	else {
		return_code = RVUTIL_TRUE;
		for (count_1 = 0; count_1 < in_name->element_count; count_1++) {
			if (!strcmp(in_pattern->element_list[count_1],
				RVUTIL_ELEMENT_PAT_LAST_STR))
				break;
			else if (strcmp(in_pattern->element_list[count_1],
				RVUTIL_ELEMENT_PAT_ANY_STR) &&
				strcmp(in_pattern->element_list[count_1],
				in_name->element_list[count_1])) {
				if (element_index != NULL)
					*element_index = count_1;
				return_code = RVUTIL_FALSE;
				break;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_MatchSubjectPerList(const char *in_name, unsigned int pattern_count,
	const RVUTIL_SNAME_FLAT *pattern_list, unsigned int *pattern_index,
	unsigned int *element_index)
{
	int               return_code = RVUTIL_FALSE;
	RVUTIL_SNAME_FLAT tmp_name;
	char              tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	if (RVUTIL_CrackSubjectFlat(in_name, &tmp_name, tmp_error_text) ==
		RVUTIL_SUCCESS)
		return_code = RVUTIL_MatchSubjectFlatPerList(&tmp_name, pattern_count,
			pattern_list, pattern_index, element_index);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_MatchSubjectWorkPerList(const RVUTIL_SNAME_WORK *in_name,
	unsigned int pattern_count, const RVUTIL_SNAME_FLAT *pattern_list,
	unsigned int *pattern_index, unsigned int *element_index)
{
	RVUTIL_SNAME_FLAT tmp_name;

	return(RVUTIL_MatchSubjectFlatPerList(RVUTIL_WorkToFlat(in_name, &tmp_name),
		pattern_count, pattern_list, pattern_index, element_index));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_MatchSubjectFlatPerList(const RVUTIL_SNAME_FLAT *in_name,
	unsigned int pattern_count, const RVUTIL_SNAME_FLAT *pattern_list,
	unsigned int *pattern_index, unsigned int *element_index)
{
	int          return_code = RVUTIL_FALSE;
	unsigned int count_1;

	for (count_1 = 0; count_1 < pattern_count; count_1++) {
		if ((return_code = RVUTIL_MatchSubjectFlat(in_name,
			pattern_list + count_1, element_index)) == RVUTIL_TRUE) {
			if (pattern_index != NULL)
				*pattern_index = count_1;
			break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <strfuncs.h>

int main(int argc, char **argv)
{
	int               return_code = RVUTIL_SUCCESS;
	unsigned int      count_1;
	unsigned int      element_index;
	RVUTIL_SNAME_FLAT tmp_pattern;
	char              error_text[RVUTIL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'RVUTIL_MatchSubject()'\n");
	fprintf(stderr, "                 'RVUTIL_MatchSubjectWork()'\n");
	fprintf(stderr, "                 'RVUTIL_MatchSubjectFlat()'\n");
	fprintf(stderr, "---- ------- --- ---------------------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "USAGE:\n   %s %s [%s . . . ]\n",
				argv[0], "<subject-pattern>", "<subject-name>");
			goto EXIT_FUNCTION;
		}
	}

	if (argc < 3) {
		strcpy(error_text, "Invalid command line arguments.");
		return_code = RVUTIL_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = RVUTIL_MakeSubjectPattern(argv[1], &tmp_pattern,
		error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;

	for (count_1 = 2; count_1 < ((unsigned int) argc); count_1++) {
		printf("%05u:[%s] ---> ", count_1 - 2, argv[count_1]);
		if (RVUTIL_MatchSubject(argv[count_1], &tmp_pattern, &element_index) ==
			RVUTIL_TRUE)
			printf("MATCHED");
		else
			printf("NOT MATCHED at element index %u", element_index);
		printf("\n");
	}

EXIT_FUNCTION:

	if (return_code != RVUTIL_SUCCESS) {
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);
		if (return_code == RVUTIL_BAD_ARGS_FAILURE)
			fprintf(stderr, "USAGE:\n   %s %s [%s . . . ]\n",
				argv[0], "<subject-pattern>", "<subject-name>");
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

