/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets a list of pointers to copies of the records in
								an SIIDR structure.

	Revision History	:	1996-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_GetList(SIIDR *siidr_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *out_count, void ***out_list,
	char *error_text)
{
	int return_code;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchCodeOpt(STR_CAST_FUNC_PTR(get_spec_func),
		error_text)) == SIIDR_SUCCESS) &&
		((user_data_ptr == NULL) ||
		((return_code = SIIDR_TouchRead(user_data_ptr, 1,
		"'user_data_ptr' parameter", error_text)) == SIIDR_SUCCESS)) &&
		((return_code = SIIDR_TouchWrite(out_count, sizeof(*out_count),
		"'out_count' parameter", error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchWrite(out_list, sizeof(*out_list),
		"'out_list' parameter", error_text)) == SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockReaderIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			return_code = SIIDR_GetListRaw(siidr_ptr, user_data_ptr,
				get_spec_func, out_count, out_list, error_text);
			SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_GetListRaw(SIIDR *siidr_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *out_count, void ***out_list,
	char *error_text)
{
	int            return_code;
	unsigned int   tmp_count;
	void         **tmp_list;

	*out_count = 0;
	*out_list  = NULL;

	if (((return_code = SIIDR_GetListPtrRaw(siidr_ptr, user_data_ptr,
		get_spec_func, &tmp_count, &tmp_list, error_text)) == SIIDR_SUCCESS) &&
		tmp_count) {
		if ((return_code = meml_copy(tmp_count, tmp_list, siidr_ptr->record_size,
			out_count, out_list)) != STRFUNCS_SUCCESS) {
			if (error_text != NULL)
				STR_AllocMsgPtrList(tmp_count, tmp_count * siidr_ptr->record_size,
					error_text,
					"Unable to allocate list of IDR records");
			return_code = SIIDR_MAP_ERROR_STR(return_code);
		}
		free(tmp_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_GetListPtrRaw(SIIDR *siidr_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *out_count, void ***out_list,
	char *error_text)
{
	int          return_code = SIIDR_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (siidr_ptr->record_count) {
		if ((*out_list = ((void **) calloc(siidr_ptr->record_count,
			sizeof(void *)))) != NULL) {
			if (get_spec_func == NULL) {
				memcpy(*out_list, siidr_ptr->record_list,
					siidr_ptr->record_count * sizeof(void *));
				*out_count = siidr_ptr->record_count;
			}
			else {
				for (count_1 = 0; count_1 < siidr_ptr->record_count; count_1++) {
					if ((get_spec_func == NULL) || ((*get_spec_func)(siidr_ptr,
						user_data_ptr, siidr_ptr->record_list[count_1]) != 0))
						(*out_list)[(*out_count)++] = siidr_ptr->record_list[count_1];
				}
				if (*out_count < siidr_ptr->record_count) {
					if (!(*out_count)) {
						free(*out_list);
						*out_count = 0;
						*out_list  = NULL;
					}
					else
						*out_list = ((void **) realloc(*out_list,
							*out_count * sizeof(void *)));
				}
			}
		}
		else {
			if (error_text != NULL)
				STR_AllocMsgList(siidr_ptr->record_count, sizeof(void *),
					error_text,
					"Unable to allocate list of pointers to IDR records");
			return_code = SIIDR_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int            return_code = SIIDR_SUCCESS;
	unsigned int   id_count    = SIIDR_TEST_ID_COUNT;
	SIIDR         *siidr_ptr   = NULL;
	unsigned int   tmp_count   = 0;
	void         **tmp_list    = NULL;
	unsigned int   count_1;
	unsigned int   get_count;
	char           error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test harness for function 'SIIDR_GetList()'\n");
	fprintf(stderr,
		"                          'SIIDR_GetListRaw()'\n");
	fprintf(stderr,
		"---- ------- --- -------- --------------------\n\n");

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

	if ((return_code = SIIDR_GetList(siidr_ptr, NULL, NULL,
		&tmp_count, &tmp_list, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (tmp_count) {
		sprintf(error_text, "!!!Records found %u in empty IDR!!!",
			tmp_count);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "Inserting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_TEST_FastInsertIdList(siidr_ptr, 1, id_count, 1,
		SIIDR_FALSE, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

	STR_EMIT_CharLine('=', 77, NULL, NULL);
	if ((return_code = SIIDR_GetList(siidr_ptr, NULL, NULL,
		&tmp_count, &tmp_list, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (tmp_count != siidr_ptr->record_count) {
		sprintf(error_text, "!!!List count (%u) not equal to IDR count (%u).",
			tmp_count, siidr_ptr->record_count);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	printf("********** Records in list: %10u\n", tmp_count);
	for (count_1 = 0; count_1 < tmp_count; count_1++) {
		if (memcmp(tmp_list[count_1], siidr_ptr->record_list[count_1],
			siidr_ptr->record_size)) {
			printf("IDR/list mis-match at index %u:\n", count_1);
			printf(">>> IDR : ");
			SIIDR_TEST_EmitRecord(count_1,
				((const SIIDR_TEST_DATA *) siidr_ptr->record_list[count_1]));
			printf(">>> LIST: ");
			SIIDR_TEST_EmitRecord(count_1,
				((const SIIDR_TEST_DATA *) tmp_list[count_1]));
			sprintf(error_text, "List records not matched at index %u",
				count_1);
			return_code = SIIDR_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	meml_remove_all(&tmp_count, &tmp_list);

	if ((return_code = SIIDR_GetList(siidr_ptr, NULL,
		((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityOdd),
		&tmp_count, &tmp_list, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (tmp_count != (get_count = SIIDR_GetCount(siidr_ptr, NULL,
		((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityOdd)))) {
		sprintf(error_text, "!!!Odd list count (%u) not equal to IDR count (%u).",
			tmp_count, get_count);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	printf("********** Records with odd quantity in IDR: %10u\n",
		tmp_count);
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	meml_remove_all(&tmp_count, &tmp_list);

EXIT_FUNCTION:

	meml_remove_all(&tmp_count, &tmp_list);

	if (siidr_ptr != NULL)
		SIIDR_FreeIDR(siidr_ptr);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

