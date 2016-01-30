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

		Copyright Michael L. Brock 1992 - 2016.
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
int MLOG_OpenLog(const char *file_name, const char *log_format,
	const char *user_string, MLOG_FLAG flags, MLOG **mlog_ptr, char *error_text)
#else
int MLOG_OpenLog(file_name, log_format, user_string, flags, mlog_ptr,
	error_text)
const char  *file_name;
const char  *log_format;
const char  *user_string;
MLOG_FLAG    flags;
MLOG       **mlog_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	MLOG_PRIORITY mfile_mask;
	MLOG_PRIORITY file_mask;
	MLOG_PRIORITY syslog_mask;

	flags       = flags & (MLOG_FLAG_MASK & (~MLOG_FLAG_FILE_CLOSE));
	flags       = (flags & MLOG_FLAG_FILE) ? flags :
		(flags & (MLOG_FLAG_MASK & (~MLOG_FLAGS_FOR_FILE)));
	flags       = (file_name != NULL) ? flags :
		(flags & (MLOG_FLAG_MASK & (~MLOG_FLAGS_FOR_MFILE)));

	mfile_mask  = (file_name != NULL) ? MLOG_PRIORITY_DEFAULT_MFILE :
		MLOG_PRIORITY_NONE;
	file_mask   = (flags & MLOG_FLAG_FILE) ? MLOG_PRIORITY_DEFAULT_FILE :
		MLOG_PRIORITY_NONE;
	syslog_mask = (MLOG_HAS_FLAGS_FOR_SYSLOG(flags)) ?
		MLOG_PRIORITY_DEFAULT_SYSLOG : MLOG_PRIORITY_NONE;

	log_format  = ((log_format != NULL) && *log_format) ? log_format :
		(((user_string == NULL) || (!(*user_string))) ? "DTM" : "DTMU");

	return(MLOG_OpenBasic(file_name, (flags & MLOG_FLAG_FILE) ? stderr : NULL,
		log_format, user_string, flags, mfile_mask, file_mask, syslog_mask,
		0, 0, mlog_ptr, error_text));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define TEST_MLOG_FILE_NAME		"TEST_MLOG_OpenLog.txt"

int main(void);

int main()
{
	int   return_code = MLOG_SUCCESS;
	MLOG *mlog_ptr    = NULL;
	char  error_text[MLOG_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'MLOG_OpenLog()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------------\n\n");

	if ((return_code = MLOG_OpenLog(TEST_MLOG_FILE_NAME, NULL, "UserString",
		MLOG_FLAG_MFILE | MLOG_FLAG_FILE, &mlog_ptr, error_text)) ==
		MLOG_SUCCESS) {
		fprintf(stderr, "Opened test file '%s' (%u bytes).\n",
			TEST_MLOG_FILE_NAME, mlog_ptr->initial_alloc);
		MLOG_DoRUsage(mlog_ptr);
		return_code = MLOG_Close(mlog_ptr, error_text);
	}

	if (return_code != MLOG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

