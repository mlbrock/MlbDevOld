/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Cracks a subject name into its constiuent elements.

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

#include <string.h>

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
					Equivalent to the function 'RVUTIL_CrackSubjectWork()'.
					Maintained here for compatibility with older versions of the
					library.
*/
/*	***********************************************************************	*/
int RVUTIL_CrackSubjectName(const char *in_name, RVUTIL_SNAME_WORK *out_name,
	char *error_text)
{
	return(RVUTIL_CrackSubjectWork(in_name, out_name, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CrackSubjectWork(const char *in_name, RVUTIL_SNAME_WORK *out_name,
	char *error_text)
{
	int            return_code = RVUTIL_INVALID_SUBJECT;
 	char         **element_ptr;
	char          *tmp_ptr;
	unsigned int   in_length;
	unsigned int   element_count;

	if (in_name == NULL)
		strcpy(error_text, "Pointer to subject name is 'NULL'.");
	else if (!(*in_name))
		strcpy(error_text, "Subject name is empty (has zero length).");
	else if ((in_length = strlen(in_name)) > RVUTIL_MAX_SUB_NAME_LEN)
		sprintf(error_text,
			"Subject name '%.*s' length (%u) exceeds maximum length (%d).",
			RVUTIL_MAX_ERROR_TEXT - 100, in_name, in_length,
			RVUTIL_MAX_SUB_NAME_LEN);
	else if ((element_count = (chrcnt(in_name, RVUTIL_ELEMENT_SEP_CHAR) + 1)) >
		RVUTIL_MAX_SUB_NAME_ELEMENTS)
		sprintf(error_text, "%s '%s' (%u) %s (%d).",
			"The number of elements in subject name", in_name, element_count,
			"exceeds the maximum number of elements",
			RVUTIL_MAX_SUB_NAME_ELEMENTS);
	else {
		memset(out_name, '\0', sizeof(*out_name));
		strcpy(out_name->subject_name, in_name);
		tmp_ptr                 = out_name->subject_name;
		element_ptr             = out_name->element_list;
		*element_ptr            = out_name->subject_name;
		out_name->element_count = 1;
		return_code             = RVUTIL_SUCCESS;
		while (*tmp_ptr) {
			if (*tmp_ptr == RVUTIL_ELEMENT_SEP_CHAR) {
				*tmp_ptr = '\0';
				if (((unsigned int) (tmp_ptr - *element_ptr)) >
					RVUTIL_MAX_ELEMENT_LEN) {
					sprintf(error_text, "%s %u (%u) %s (%d).",
						"The length of element number", out_name->element_count,
						((unsigned int) (tmp_ptr - *element_ptr)),
						"exceeds the maximum Rendezvous subject element length",
						RVUTIL_MAX_ELEMENT_LEN);
					return_code = RVUTIL_INVALID_SUBJECT;
					break;
				}
				out_name->element_count++;
				*(++element_ptr) = tmp_ptr + 1;
			}
			tmp_ptr++;
		}
		if ((out_name->element_count == 1) &&
			(strlen(*element_ptr) > RVUTIL_MAX_ELEMENT_LEN)) {
			sprintf(error_text, "%s %u (%u) %s (%d).",
				"The length of element number", out_name->element_count,
				strlen(*element_ptr),
				"exceeds the maximum Rendezvous subject element length",
				RVUTIL_MAX_ELEMENT_LEN);
			return_code = RVUTIL_INVALID_SUBJECT;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CrackSubjectFlat(const char *in_name, RVUTIL_SNAME_FLAT *out_name,
	char *error_text)
{
	int               return_code;
	RVUTIL_SNAME_WORK tmp_work;

	if ((return_code = RVUTIL_CrackSubjectWork(in_name, &tmp_work,
		error_text)) == RVUTIL_SUCCESS)
		RVUTIL_WorkToFlat(&tmp_work, out_name);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

int main(int argc, char **argv)
{
	int               return_code = RVUTIL_SUCCESS;
	unsigned int      count_1;
	unsigned int      count_2;
	RVUTIL_SNAME_WORK tmp_name_1;
	RVUTIL_SNAME_FLAT tmp_name_2;
	char              error_text[RVUTIL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'RVUTIL_CrackSubjectWork()'\n");
	fprintf(stderr, "                 'RVUTIL_CrackSubjectFlat()'\n");
	fprintf(stderr, "---- ------- --- ---------------------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		printf("%05u:[%s] ---> ", count_1, argv[count_1]);
		if (RVUTIL_CrackSubjectWork(argv[count_1], &tmp_name_1,
			error_text) != RVUTIL_SUCCESS)
			printf("'RVUTIL_CrackSubjectWork()' FAILED: %s", error_text);
		else if (RVUTIL_CrackSubjectFlat(argv[count_1], &tmp_name_2,
			error_text) != RVUTIL_SUCCESS)
			printf("'RVUTIL_CrackSubjectFlat()' FAILED: %s", error_text);
		else if (tmp_name_1.element_count != tmp_name_2.element_count) {
			printf("%s (%u) %s (%u).\n",
				"'RVUTIL_CrackSubjectWork()' element count",
				tmp_name_1.element_count,
				"differs from 'RVUTIL_CrackSubjectFlat()' element count",
				tmp_name_2.element_count);
		}
		else {
			printf("[%3u]",  tmp_name_1.element_count);
			for (count_2 = 0; count_2 < tmp_name_1.element_count; count_2++) {
				printf("[%s]", tmp_name_1.element_list[count_2]);
				if ((strcmp(tmp_name_1.element_list[count_2],
					tmp_name_2.element_list[count_2]) != 0) &&
					(return_code == RVUTIL_SUCCESS)) {
					sprintf(error_text, "%s '%s' %s '%s' %s %u.",
						"'RVUTIL_CrackSubjectWork()' element",
						tmp_name_1.element_list[count_2],
						"differs from 'RVUTIL_CrackSubjectFlat()' element",
						tmp_name_2.element_list[count_2],
						"beginning at element index", count_2);
					return_code = RVUTIL_FAILURE;
				}
			}
			if (return_code != RVUTIL_SUCCESS)
				printf("ERROR: %s\n", error_text);
		}
		printf("\n");
	}

	return(0);
}

#endif /* #ifdef TEST_MAIN */

