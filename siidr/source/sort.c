/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sorts IDR records.

	Revision History	:	1996-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_Sort(SIIDR *siidr_ptr, char *error_text)
{
	int return_code;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			SIIDR_SortRaw(siidr_ptr);
			SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void SIIDR_SortRaw(SIIDR *siidr_ptr)
{
	SIIDR_SortBasicRaw(siidr_ptr, siidr_ptr->record_count,
		siidr_ptr->record_list, siidr_ptr->compare_func);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void SIIDR_SortBasicRaw(SIIDR *siidr_ptr, unsigned int in_count,
	void **in_list, SIIDR_CompareFunc compare_func)
{
	SIIDR_CompareFunc tmp_compare_func;

	tmp_compare_func        = siidr_ptr->compare_func;
	siidr_ptr->compare_func = (compare_func != NULL) ? compare_func :
		siidr_ptr->compare_func;

	STR_LIST_qsort(siidr_ptr, in_count, in_list, siidr_ptr->record_size,
		STR_CMP_FUNC_CAST(SIIDR_Compare));

	siidr_ptr->compare_func = tmp_compare_func;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void SIIDR_SortBulkListRaw(SIIDR *siidr_ptr, unsigned int bulk_count,
	SIIDR_BULK *bulk_list, SIIDR_CompareFunc compare_func)
{
	siidr_ptr->tmp_compare_func = (compare_func != NULL) ? compare_func :
		siidr_ptr->compare_func;

	STR_ARRAY_qsort(siidr_ptr, bulk_count, bulk_list, sizeof(SIIDR_BULK),
		STR_CMP_FUNC_CAST(SIIDR_CompareBulk));

	siidr_ptr->tmp_compare_func = NULL;
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int           return_code = SIIDR_SUCCESS;
	unsigned int  id_count    = SIIDR_TEST_ID_COUNT;
	SIIDR        *siidr_ptr   = NULL;
	unsigned int  u_int_1;
	unsigned int  u_int_2;
	void         *tmp_ptr;
	unsigned int  count_1;
	char          error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test harness for function 'SIIDR_Sort()'\n");
	fprintf(stderr,
		"                          'SIIDR_SortRaw()'\n");
	fprintf(stderr,
		"---- ------- --- -------- -----------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "\nHelp request with '%s' noted . . .",
				argv[count_1]);
			fprintf(stderr, "USAGE:\n   %s [-COUNT=<record-count>]\n\n",
				argv[0]);
			goto EXIT_FUNCTION;
		}
		else if (!strnicmp(argv[count_1], "-COUNT=", 7)) {
			if ((id_count = atoi(argv[count_1] + 7)) < 1) {
				sprintf(error_text,
					"Invalid command line parameter ('%-.500s').", argv[count_1]);
				return_code = SIIDR_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
		else {
			sprintf(error_text, "Invalid command line parameter ('%-.500s').",
				argv[count_1]);
			return_code = SIIDR_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	if ((return_code = SIIDR_CreateIDR("order",
		sizeof(SIIDR_TEST_DATA), 0,
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Inserting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_TEST_FastInsertIdList(siidr_ptr, 1, id_count, 1,
		SIIDR_FALSE, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

	fprintf(stderr, "Randomizing %u records in the IDR . . .", id_count);
	for (count_1 = 0; count_1 < (id_count * 3); count_1++) {
		while ((u_int_1 = (rand() % id_count)) ==
			(u_int_2 = (rand() % id_count)))
			;
		tmp_ptr                         = siidr_ptr->record_list[u_int_1];
		siidr_ptr->record_list[u_int_1] = siidr_ptr->record_list[u_int_2];
		siidr_ptr->record_list[u_int_2] = tmp_ptr;
	}
	fprintf(stderr, " done\n");

	fprintf(stderr, "Sorting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_Sort(siidr_ptr, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

	fprintf(stderr, "Checking %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_CheckData(siidr_ptr, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

EXIT_FUNCTION:

	if (siidr_ptr != NULL)
		SIIDR_FreeIDR(siidr_ptr);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

