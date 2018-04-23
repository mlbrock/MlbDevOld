/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a bulk insert of an array of records into
								an SIIDR structure.

	Revision History	:	1996-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
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

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_BulkInsertArray(SIIDR *siidr_ptr, unsigned int in_count,
	const void *in_array, char *error_text)
{
	int return_code;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) && in_count &&
		((return_code = SIIDR_TouchRead(in_array,
		in_count * siidr_ptr->record_size, "'in_array' parameter",
		error_text)) == SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			return_code = SIIDR_BulkInsertArrayRaw(siidr_ptr, in_count,
				in_array, error_text);
			SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_BulkInsertArrayRaw(SIIDR *siidr_ptr, unsigned int in_count,
	const void *in_array, char *error_text)
{
	int            return_code = SIIDR_SUCCESS;
	unsigned int   count_1;
	void         **tmp_list;
	const void    *tmp_ptr;

	if (in_count) {
		if ((tmp_list = ((void **) calloc(in_count, sizeof(void *)))) != NULL) {
			for (count_1 = 0, tmp_ptr = in_array; count_1 < in_count;
				count_1++, tmp_ptr = ((const void *) (((char *) tmp_ptr) +
				siidr_ptr->record_size)))
				tmp_list[count_1] = ((void *) tmp_ptr);
			return_code = SIIDR_BulkInsertListRaw(siidr_ptr, in_count,
				tmp_list, error_text);
			free(tmp_list);
		}
		else {
			if (error_text != NULL)
				STR_AllocMsgList(siidr_ptr->record_count, sizeof(void *),
					error_text,
					"Unable to allocate list of pointers to bulk insert records");
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
	int           return_code = SIIDR_SUCCESS;
	unsigned int  id_count    = SIIDR_TEST_ID_COUNT;
	SIIDR        *siidr_ptr_1 = NULL;
	SIIDR        *siidr_ptr_2 = NULL;
	unsigned int  tmp_count   = 0;
	void         *tmp_array   = NULL;
	unsigned int  count_1;
	unsigned int  u_int_1;
	unsigned int  u_int_2;
	void         *tmp_ptr;
	char          error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test harness for function 'SIIDR_BulkInsetArray()'\n");
	fprintf(stderr,
		"                          'SIIDR_BulkInsetArrayRaw()'\n");
	fprintf(stderr,
		"---- ------- --- -------- ---------------------------\n\n");

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
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr_1,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if ((return_code = SIIDR_CreateIDR("order",
		sizeof(SIIDR_TEST_DATA), 0,
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr_2,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Inserting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_TEST_FastInsertIdList(siidr_ptr_1, 1,
		id_count, 1, SIIDR_FALSE, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr_1, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

	if (id_count > 1) {
		fprintf(stderr, "Randomizing %u records in the IDR . . .", id_count);
		for (count_1 = 0; count_1 < (id_count * 3); count_1++) {
			while ((u_int_1 = (rand() % id_count)) ==
				(u_int_2 = (rand() % id_count)))
				;
			tmp_ptr                           = siidr_ptr_1->record_list[u_int_1];
			siidr_ptr_1->record_list[u_int_1] = siidr_ptr_1->record_list[u_int_2];
			siidr_ptr_1->record_list[u_int_2] = tmp_ptr;
		}
		fprintf(stderr, " done\n");
	}

	fprintf(stderr, "Converting %u pointers to records to an array . . .",
		id_count);
	if ((return_code = meml_to_mema(siidr_ptr_1->record_count,
		siidr_ptr_1->record_list, siidr_ptr_1->record_size,
		&tmp_count, &tmp_array)) != STRFUNCS_SUCCESS) {
		STR_AllocMsgList(siidr_ptr_1->record_count, siidr_ptr_1->record_size,
			error_text, "Unable to allocate array of IDR record copies");
		return_code = SIIDR_MAP_ERROR_STR(return_code);
		goto EXIT_FUNCTION;
	}
	fprintf(stderr, " done\n");

	fprintf(stderr, "Bulk inserting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_BulkInsertArray(siidr_ptr_2,
		tmp_count, tmp_array, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr_2, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

EXIT_FUNCTION:

	SIIDR_FreeIDR(siidr_ptr_1);
	SIIDR_FreeIDR(siidr_ptr_2);

	mema_remove_all(&tmp_count, &tmp_array);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

