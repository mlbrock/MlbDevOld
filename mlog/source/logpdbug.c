/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logs messages with priority 'LOG_DEBUG' when the
								debugging flag 'pdebug_flag' is set.

	Revision History	:	2001-10-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2014.
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
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogPDebug(MLOG *mlog_ptr, const char *in_format, ...)
#else
int MLOG_LogPDebug(mlog_ptr, in_format, va_list)
MLOG       *mlog_ptr;
const char *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int     return_code;
	va_list arg_list;

#ifndef NO_STDARGS
	va_start(arg_list, in_format);
#else
	va_start(arg_list);
#endif /* #ifndef NO_STDARGS */

	return_code = MLOG_LogPDebugVA(mlog_ptr, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogPDebugVA(MLOG *mlog_ptr, const char *in_format, va_list arg_list)
#else
int MLOG_LogPDebugVA(mlog_ptr, in_format, arg_list)
MLOG       *mlog_ptr;
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	if (!MLOG_DO_LOG(mlog_ptr))
		return(MLOG_FAILURE);
	else if (mlog_ptr->pdebug_flag != MLOG_TRUE)
		return(MLOG_SUCCESS);
	else
		return(MLOG_LogDebugVA(mlog_ptr, in_format, arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogPDebugTime(MLOG *mlog_ptr, const struct timeval *in_time,
	const char *in_format, ...)
#else
int MLOG_LogPDebugTime(mlog_ptr, in_time, in_format, va_list)
MLOG                 *mlog_ptr;
const struct timeval *in_time;
const char           *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int     return_code;
	va_list arg_list;

#ifndef NO_STDARGS
	va_start(arg_list, in_format);
#else
	va_start(arg_list);
#endif /* #ifndef NO_STDARGS */

	return_code = MLOG_LogPDebugTimeVA(mlog_ptr, in_time, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogPDebugTimeVA(MLOG *mlog_ptr, const struct timeval *in_time,
	const char *in_format, va_list arg_list)
#else
int MLOG_LogPDebugTimeVA(mlog_ptr, in_time, in_format, arg_list)
MLOG                 *mlog_ptr;
const struct timeval *in_time;
const char           *in_format;
va_list               arg_list;
#endif /* #ifndef NARGS */
{
	if (!MLOG_DO_LOG(mlog_ptr))
		return(MLOG_FAILURE);
	else if (mlog_ptr->pdebug_flag != MLOG_TRUE)
		return(MLOG_SUCCESS);
	else
		return(MLOG_LogDebugTimeVA(mlog_ptr, in_time, in_format, arg_list));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define TEST_MLOG_FILE_NAME		"TEST_MLOG_LogPDebug.txt"

int main(void);

int main()
{
	int           return_code = MLOG_SUCCESS;
	MLOG         *mlog_ptr    = NULL;
	unsigned int  count_1;
	char          buffer_list[26][666 + 1];
	char          error_text[MLOG_MAX_ERROR_TEXT];

	fprintf(stderr, "%s\n%s\n\n",
		"Test harness for function 'MLOG_LogPDebug()'\n",
		"                          'MLOG_LogPDebugVA()'\n");
	fprintf(stderr,
		"---- ------- --- -------- --------------------\n\n");

	if ((mlog_ptr = MLOG_FOpenDefault(TEST_MLOG_FILE_NAME)) != NULL) {
		fprintf(stderr, "Opened test file '%s' (%u bytes).\n",
			TEST_MLOG_FILE_NAME, mlog_ptr->initial_alloc);
		MLOG_SetPDebug(mlog_ptr, MLOG_TRUE);
		for (count_1 = 0; count_1 < 26; count_1++) {
			memset(buffer_list[count_1], ((int) ('A' + count_1)),
				sizeof(buffer_list[0]));
			buffer_list[count_1][sizeof(buffer_list[0]) - 1] = '\0';
		}
		for (count_1 = 0; count_1 < 26; count_1++) {
			MLOG_LogPDebug(mlog_ptr, "Try number %10u: %s\n",
				count_1, buffer_list[count_1]);
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

