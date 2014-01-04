/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Test Module											*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1995-08-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#include <memory.h>
#include <string.h>

#include "mfile.h"

#include "dcr.h"

#include "datatest.h"						/* For the test meta-data . . .		*/

#define TEST_COUNT							100
#define TEST_RECORD_FILE					"CACHE.REC"

static ISSUE_ID     IssueIdList[TEST_COUNT];

static unsigned int IdLength[TEST_COUNT];

static unsigned int IssueIdCount =
	sizeof(IssueIdList) / sizeof(IssueIdList[0]);

static char         CharList[]   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

int main(argc, argv)
int    argc;
char **argv;
{
	int           return_code = DCR_SUCCESS;
	MFILE        *mfile_ptr   = NULL;
	unsigned int  count_1;
	unsigned int  count_2;
   unsigned int  out_count;
	unsigned int  record_number;
	unsigned int  change_count;
	char          error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Produce random-generated DCR cache test records\n");
	fprintf(stderr, "------- ---------------- --- ----- ---- -------\n");

	if (argc < 2) {
		strcpy(error_text, "Expected test record count on command-line.");
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if (atoi(argv[1]) <= 0) {
		strcpy(error_text, "Expected test record count greater than zero.");
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if ((mfile_ptr = mopen(TEST_RECORD_FILE, "w")) == NULL) {
		sprintf(error_text, "%s '%-.500s' for writing: ",
			"Unable to open DCR cache test record file", TEST_RECORD_FILE);
		DCR_GEN_AppendLastErrorString(error_text);
		return_code = DCR_SYSTEM_FAILURE;
	}
	else {
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Initialize the cache test record data . . .					*/
		/*	***********************************************************	*/
		memset(IssueIdList, '\0', sizeof(IssueIdList));
		for (count_1 = 0; count_1 < IssueIdCount; count_1++) {
			IdLength[count_1] = (rand() % 6) + 6;
			for (count_2 = 0; count_2 < IdLength[count_1]; count_2++)
				IssueIdList[count_1].issue_id_value[count_2] =
					CharList[rand() % (sizeof(CharList) - 1)];
			IssueIdList[count_1].issue_id_value[IdLength[count_1]] = '\0';
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		out_count = ((unsigned int) atoi(argv[1]));
		mtruncate(mfile_ptr, sizeof(IssueIdList[0]) * out_count);
		fprintf(stderr, "Progress report (per thousand): [");
		for (count_1 = 0; count_1 < out_count; count_1++) {
			record_number = rand() % IssueIdCount;
			change_count  = (rand() % IdLength[record_number]) + 1;
			for (count_2 = 0; count_2 < change_count; count_2++)
				IssueIdList[record_number].
					issue_id_value[rand() % IdLength[record_number]] =
					CharList[rand() % (sizeof(CharList) - 1)];
			IssueIdList[record_number].issue_key         =
				(((long) rand()) % (((long) out_count) * 2L)) + 1L;
			IssueIdList[record_number].issue_id_type     =
				((long) rand()) % 10L;
			IssueIdList[record_number].issue_id_exchange =
				((long) ((!(rand() % 10)) ? (rand() % 50) : 0));
			mwrite(IssueIdList + record_number, sizeof(IssueIdList[0]), 1,
				mfile_ptr);
			if (count_1 && (!(count_1 % 1000)))
				fprintf(stderr, ".");
		}
		fprintf(stderr, "%s]\n\n", (!(out_count % 1000)) ? "." : "");
		/*	***********************************************************	*/
	}

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	if (mfile_ptr != NULL)
		mclose(mfile_ptr);

	return(return_code);
}


