/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Simple, default method of opening a file for logging.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
MLOG *MLOG_FOpenDefault(const char *file_name)
#else
MLOG *MLOG_FOpenDefault(file_name)
const char *file_name;
#endif /* #ifndef NARGS */
{
	MLOG *mlog_ptr = NULL;

	MLOG_OpenBasic(file_name, stderr, NULL, NULL,
		MLOG_FLAG_MFILE | MLOG_FLAG_FILE | MLOG_FLAG_SYSLOG,
		MLOG_PRIORITY_MASK, MLOG_PRIORITY_MASK, MLOG_PRIORITY_EMERG |
		MLOG_PRIORITY_ALERT | MLOG_PRIORITY_CRIT | MLOG_PRIORITY_ERR |
		MLOG_PRIORITY_WARNING, 0, 0, &mlog_ptr, NULL);

	return(mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
MLOG *MLOG_FOpenDefaultAppend(const char *file_name)
#else
MLOG *MLOG_FOpenDefaultAppend(file_name)
const char *file_name;
#endif /* #ifndef NARGS */
{
	MLOG *mlog_ptr = NULL;

	MLOG_OpenBasic(file_name, stderr, NULL, NULL,
		MLOG_FLAG_MFILE | MLOG_FLAG_FILE | MLOG_FLAG_SYSLOG | MLOG_FLAG_APPEND,
		MLOG_PRIORITY_MASK, MLOG_PRIORITY_MASK, MLOG_PRIORITY_EMERG |
		MLOG_PRIORITY_ALERT | MLOG_PRIORITY_CRIT | MLOG_PRIORITY_ERR |
		MLOG_PRIORITY_WARNING, 0, 0, &mlog_ptr, NULL);

	return(mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
MLOG *MLOG_FOpenDefaultTid(const char *file_name)
#else
MLOG *MLOG_FOpenDefaultTid(file_name)
const char *file_name;
#endif /* #ifndef NARGS */
{
	MLOG *mlog_ptr = NULL;

	MLOG_OpenBasic(file_name, stderr, "DTML", NULL,
		MLOG_FLAG_MFILE | MLOG_FLAG_FILE | MLOG_FLAG_SYSLOG,
		MLOG_PRIORITY_MASK, MLOG_PRIORITY_MASK, MLOG_PRIORITY_EMERG |
		MLOG_PRIORITY_ALERT | MLOG_PRIORITY_CRIT | MLOG_PRIORITY_ERR |
		MLOG_PRIORITY_WARNING, 0, 0, &mlog_ptr, NULL);

	return(mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
MLOG *MLOG_FOpenDefaultTidAppend(const char *file_name)
#else
MLOG *MLOG_FOpenDefaultTidAppend(file_name)
const char *file_name;
#endif /* #ifndef NARGS */
{
	MLOG *mlog_ptr = NULL;

	MLOG_OpenBasic(file_name, stderr, "DTML", NULL,
		MLOG_FLAG_MFILE | MLOG_FLAG_FILE | MLOG_FLAG_SYSLOG | MLOG_FLAG_APPEND,
		MLOG_PRIORITY_MASK, MLOG_PRIORITY_MASK, MLOG_PRIORITY_EMERG |
		MLOG_PRIORITY_ALERT | MLOG_PRIORITY_CRIT | MLOG_PRIORITY_ERR |
		MLOG_PRIORITY_WARNING, 0, 0, &mlog_ptr, NULL);

	return(mlog_ptr);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define TEST_MLOG_FILE_NAME		"TEST_MLOG_FOpenDefault.txt"

int main(void);

int main()
{
	int           return_code = MLOG_SUCCESS;
	MLOG         *mlog_ptr    = NULL;
	unsigned int  count_1;
	char          buffer_list[26][666 + 1];
	char          error_text[MLOG_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'MLOG_FOpenDefault()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------------------\n\n");

	if ((mlog_ptr = MLOG_FOpenDefault(TEST_MLOG_FILE_NAME)) != NULL) {
		fprintf(stderr, "Opened test file '%s' (%u bytes).\n",
			TEST_MLOG_FILE_NAME, mlog_ptr->initial_alloc);
		for (count_1 = 0; count_1 < 26; count_1++) {
			memset(buffer_list[count_1], ((int) ('A' + count_1)),
				sizeof(buffer_list[0]));
			buffer_list[count_1][sizeof(buffer_list[0]) - 1] = '\0';
		}
		while (MLOG_GET_CURR_OFFSET(mlog_ptr) < mlog_ptr->initial_alloc) {
			for (count_1 = 0; count_1 < 26; count_1++)
				mprintf(mlog_ptr->mfile_ptr, "%s\n", buffer_list[count_1]);
		}
		return_code = MLOG_Close(mlog_ptr, error_text);
	}
	else {
		sprintf(error_text, "Unable to open test file '%s'.\n",
			TEST_MLOG_FILE_NAME);
		return_code = MLOG_FAILURE;
	}

	if (return_code != MLOG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

