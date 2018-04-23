/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Test Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	External API test driver.

	Revision History	:	1996-04-11 --- Creation
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include <siidr.h>

/*	***********************************************************************	*/

#define SIIDR_EXT_TEST_ID_COUNT		10000

typedef struct {
	char         order_id[STR_VAL2STR_MAX_LEN + 1];
	unsigned int quantity;
	double       price;
} SIIDR_EXT_TEST_DATA;

COMPAT_FN_DECL(int main, (int argc, char **argv));
COMPAT_FN_DECL_STATIC(int SIIDR_EXT_TEST_Compare, (const SIIDR *siidr_ptr,
	const SIIDR_EXT_TEST_DATA *ptr_1, const SIIDR_EXT_TEST_DATA *ptr_2,
	size_t data_length));

int main(int argc, char **argv)
{
	int                  return_code = SIIDR_SUCCESS;
	unsigned int         id_count    = SIIDR_EXT_TEST_ID_COUNT;
	SIIDR               *siidr_ptr   = NULL;
	SIIDR_EXT_TEST_DATA  tmp_record;
	unsigned int         count_1;
	char                 error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr, "SIIDR External test harness\n");
	fprintf(stderr, "----- -------- ---- -------\n\n");

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
		sizeof(SIIDR_EXT_TEST_DATA), 0,
		((SIIDR_CompareFunc) SIIDR_EXT_TEST_Compare), &siidr_ptr,
		error_text)) == SIIDR_SUCCESS) {
		for (count_1 = 0; count_1 < id_count; count_1++) {
			memset(&tmp_record, '\0', sizeof(tmp_record));
			val2str_uint(count_1 + 1, 10, 0, tmp_record.order_id);
			tmp_record.price    = ((double) (count_1 + 1));
			tmp_record.quantity = count_1 + 1;
			if ((return_code = SIIDR_Insert(siidr_ptr, &tmp_record,
				error_text)) != SIIDR_SUCCESS)
				goto EXIT_FUNCTION;
		}
		return_code = SIIDR_CheckData(siidr_ptr, error_text);
		SIIDR_FreeIDR(siidr_ptr);
	}

EXIT_FUNCTION:

	SIIDR_FreeIDR(siidr_ptr);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

static int SIIDR_EXT_TEST_Compare(const SIIDR *siidr_ptr,
	const SIIDR_EXT_TEST_DATA *ptr_1, const SIIDR_EXT_TEST_DATA *ptr_2,
	size_t data_length)
{
	return(strcmp(ptr_1->order_id, ptr_2->order_id));
}

