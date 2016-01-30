/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	The most fundamental file open mechanism.

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

#include <limits.h>
#include <string.h>

#include <genfuncs.h>

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_OpenBasic(const char *file_name, FILE *file_ptr,
	const char *log_format, const char *user_string, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, unsigned int initial_alloc,
	unsigned int added_alloc, MLOG **mlog_ptr, char *error_text)
#else
int MLOG_OpenBasic(file_name, file_ptr, log_format, user_string, flags,
	mfile_mask, file_mask, syslog_mask, initial_alloc, added_alloc,
	mlog_ptr, error_text)
const char     *file_name;
FILE           *file_ptr;
const char     *log_format;
const char     *user_string;
MLOG_FLAG       flags;
MLOG_PRIORITY   mfile_mask;
MLOG_PRIORITY   file_mask;
MLOG_PRIORITY   syslog_mask;
unsigned int    initial_alloc;
unsigned int    added_alloc;
MLOG          **mlog_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code = MLOG_SUCCESS;
	char *tmp_ptr;
	char  number[STR_VAL2STR_MAX_LEN + 1];
	char  mtif_error_text[MTIF_MAX_ERROR_TEXT];

	*mlog_ptr = NULL;

	if ((file_name == NULL) && MLOG_HAS_FLAGS_FOR_MFILE(flags)) {
		if (error_text != NULL)
			strcat(strcat(strcpy(error_text,
				"File name is 'NULL', but MFILE flags are set (flags = 0x"),
				val2str(((unsigned long) flags), 0, 16, "0", number)), ").");
		return_code = MLOG_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((file_name == NULL) && mfile_mask) {
		if (error_text != NULL)
			strcat(strcat(strcpy(error_text,
		"File name is 'NULL', but the MFILE priority mask is set (mask = 0x"),
				val2str(((unsigned long) mfile_mask), 0, 16, "0", number)), ").");
		return_code = MLOG_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((file_name != NULL) && (!(*file_name))) {
		if (error_text != NULL)
			strcpy(error_text, "File is an empty string.");
		return_code = MLOG_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((!MLOG_FLAG_MASK) & flags) {
		if (error_text != NULL)
			strcat(strcat(strcpy(error_text, "Invalid flags (flags = 0x"),
				val2str(((unsigned long) flags), 0, 16, "0", number)), ").");
		return_code = MLOG_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((!MLOG_PRIORITY_MASK) & mfile_mask) {
		if (error_text != NULL)
			strcat(strcat(strcpy(error_text,
				"Invalid MFILE priority mask (0x"),
				val2str(((unsigned long) mfile_mask), 0, 16, "0", number)), ").");
		return_code = MLOG_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((!MLOG_PRIORITY_MASK) & file_mask) {
		if (error_text != NULL)
			strcat(strcat(strcpy(error_text,
				"Invalid FILE priority mask (mask = 0x"),
				val2str(((unsigned long) file_mask), 0, 16, "0", number)), ").");
		return_code = MLOG_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((!MLOG_PRIORITY_MASK) & syslog_mask) {
		if (error_text != NULL)
			strcat(strcat(strcpy(error_text,
				"Invalid SYSLOG priority mask (mask = 0x"),
				val2str(((unsigned long) syslog_mask), 0, 16, "0", number)), ").");
		return_code = MLOG_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((user_string != NULL) && *user_string && (log_format != NULL) &&
		*log_format && (strichr(log_format, 'U') == NULL)) {
		if (error_text != NULL)
			strcat(strcpy(error_text, "User string is set, but the log "),
				"does not contain a user string specification ('U').");
		return_code = MLOG_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	log_format    = ((log_format != NULL) && *log_format) ? log_format :
		(((user_string == NULL) || (!(*user_string))) ? "DTM" : "DTMU");
	added_alloc   = (added_alloc < MFILE_PRINTF_BUFFER_SIZE_MIN) ?
		MFILE_PRINTF_BUFFER_SIZE_MIN : added_alloc;
	added_alloc   = STRFUNCS_ADJUST_SIZE(added_alloc, MLOG_getpagesize);
	initial_alloc = (initial_alloc < MFILE_PRINTF_BUFFER_SIZE) ?
		MFILE_PRINTF_BUFFER_SIZE : initial_alloc;
	initial_alloc = STRFUNCS_ADJUST_SIZE(initial_alloc, MLOG_getpagesize);
	initial_alloc = (initial_alloc >= added_alloc) ? initial_alloc :
		added_alloc;
	user_string   = ((user_string != NULL) && *user_string) ? user_string :
		NULL;
	file_ptr      = ((file_ptr == NULL) && (flags & MLOG_FLAG_FILE)) ?
		stderr : file_ptr;

	if ((*mlog_ptr = ((MLOG *) calloc(1, sizeof(MLOG)))) == NULL) {
		if (error_text != NULL)
			strcpy(error_text, "Unable to allocate memory for MLOG.");
		return_code = MLOG_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	MLOG_Init(*mlog_ptr);

	(*mlog_ptr)->signature          = MLOG_SIGNATURE_OK;
	(*mlog_ptr)->mtr_data_init_flag = MLOG_FALSE;
	(*mlog_ptr)->flags              = flags;
	(*mlog_ptr)->mfile_mask         = mfile_mask;
	(*mlog_ptr)->file_mask          = file_mask;
	(*mlog_ptr)->syslog_mask        = syslog_mask;
	(*mlog_ptr)->initial_alloc      = initial_alloc;
	(*mlog_ptr)->added_alloc        = added_alloc;
	(*mlog_ptr)->log_format         = NULL;
	(*mlog_ptr)->user_string        = NULL;
	(*mlog_ptr)->used_length        = 0;
	(*mlog_ptr)->work_length        = 0;
	(*mlog_ptr)->work_string        = NULL;
	(*mlog_ptr)->sep_length         = 80;
	(*mlog_ptr)->mfile_ptr          = NULL;
	(*mlog_ptr)->file_ptr           = file_ptr;
	(*mlog_ptr)->may_log_flag       = MLOG_TRUE;
	(*mlog_ptr)->pdebug_flag        = MLOG_FALSE;

	if ((return_code = MLOG_SetLogFormatBasic(*mlog_ptr, log_format,
		user_string, error_text)) != MLOG_SUCCESS)
		goto EXIT_FUNCTION;

	if (file_name == NULL)
		goto EXIT_FUNCTION;

	if (((*mlog_ptr)->mfile_ptr = mopen(file_name,
		((*mlog_ptr)->flags & MLOG_FLAG_APPEND) ? "rb+" : "wb+")) == NULL) {
		if (error_text != NULL) {
			strcat(nstrcat(strcpy(error_text, "Unable to open file '"),
				file_name, 500), "': ");
			GEN_AppendLastErrorString(0, MLOG_MAX_ERROR_TEXT, error_text);
		}
		return_code = MLOG_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	msetbuf(MLOG_GET_MFILE_PTR(*mlog_ptr), (*mlog_ptr)->initial_alloc);

	if (MLOG_GET_MMAP_LENGTH(*mlog_ptr)) {
		if ((tmp_ptr = ((char *) memchr(MLOG_GET_MMAP_PTR(*mlog_ptr), '\0',
		MLOG_GET_MMAP_LENGTH(*mlog_ptr)))) != NULL)
			mseek(MLOG_GET_MFILE_PTR(*mlog_ptr),
				((off_t) (tmp_ptr - MLOG_GET_MMAP_PTRC(*mlog_ptr))), SEEK_SET);
		else
			mseek(MLOG_GET_MFILE_PTR(*mlog_ptr),
				((off_t) MLOG_GET_MMAP_LENGTH(*mlog_ptr)),	SEEK_SET);
	}

	if (mprintf_ensure_space(MLOG_GET_MFILE_PTR(*mlog_ptr)) == MFILE_FALSE) {
		if (error_text != NULL) {
			strcat(nstrcat(strcpy(error_text, "Unable to expand file '"),
				file_name, 500), "': ");
			GEN_AppendLastErrorString(0, MLOG_MAX_ERROR_TEXT, error_text);
		}
		return_code = MLOG_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = MTIF_MTR_Init(MLOG_MTR_INIT_FLAGS, NULL,
		&(*mlog_ptr)->mtr_data, mtif_error_text)) != MTIF_SUCCESS) {
		nstrcpy(error_text, mtif_error_text, MLOG_MAX_ERROR_TEXT - 1);
		return_code = MLOG_MAP_ERROR_MTIF(return_code);
		goto EXIT_FUNCTION;
	}

	(*mlog_ptr)->mtr_data_init_flag = MLOG_TRUE;

EXIT_FUNCTION:

	if (return_code != MLOG_SUCCESS) {
		MLOG_Close(*mlog_ptr, NULL);
		*mlog_ptr = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define TEST_MLOG_FILE_NAME		"TEST_MLOG_OpenBasic.txt"

int main(void);

int main()
{
	int           return_code = MLOG_SUCCESS;
	MLOG         *mlog_ptr    = NULL;
	unsigned int  count_1;
	char          buffer_list[26][666 + 1];
	char          error_text[MLOG_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'MLOG_OpenBasic()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------------\n\n");

	if ((return_code = MLOG_OpenBasic(TEST_MLOG_FILE_NAME, NULL,
		"DTMUPL", "open.c", MLOG_FLAG_MFILE, MLOG_PRIORITY_MASK,
		MLOG_PRIORITY_MASK, MLOG_PRIORITY_MASK, 0, 0, &mlog_ptr, error_text)) !=
		MLOG_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Opened test file '%s' (%lu bytes).\n",
		TEST_MLOG_FILE_NAME, MLOG_GET_FILE_LENGTH(mlog_ptr));

	for (count_1 = 0; count_1 < 26; count_1++) {
		memset(buffer_list[count_1], ((int) ('A' + count_1)),
			sizeof(buffer_list[0]));
		buffer_list[count_1][sizeof(buffer_list[0]) - 1] = '\0';
	}

	while (MLOG_GET_CURR_OFFSET(mlog_ptr) < mlog_ptr->initial_alloc) {
		for (count_1 = 0; count_1 < 26; count_1++)
			MLOG_LogInfo(mlog_ptr, "%s\n", buffer_list[count_1]);
	}

	return_code = MLOG_Close(mlog_ptr, error_text);

EXIT_FUNCTION:

	if (return_code != MLOG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

