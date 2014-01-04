/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logs messages with priority 'LOG_INFO' if the
								specified if value parameter is non-zero.

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
int MLOG_LogIf(MLOG *mlog_ptr, int if_value, const char *in_format, ...)
#else
int MLOG_LogIf(mlog_ptr, if_value, in_format, va_list)
MLOG       *mlog_ptr;
int         if_value;
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


	return_code = MLOG_LogIfVA(mlog_ptr, if_value, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogIfVA(MLOG *mlog_ptr, int if_value, const char *in_format,
	va_list arg_list)
#else
int MLOG_LogIfVA(mlog_ptr, if_value, in_format, arg_list)
MLOG       *mlog_ptr;
int         if_value;
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	if (!MLOG_DO_LOG(mlog_ptr))
		return(MLOG_FAILURE);
	else if (!if_value)
		return(MLOG_SUCCESS);
	else
		return(MLOG_LogBasicVA(mlog_ptr, NULL, MLOG_PRIORITY_INFO,
			mlog_ptr->user_string, mlog_ptr->flags, mlog_ptr->mfile_mask,
			mlog_ptr->file_mask, mlog_ptr->syslog_mask, in_format, arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogIfTime(MLOG *mlog_ptr, int if_value, const struct timeval *in_time,
	const char *in_format, ...)
#else
int MLOG_LogIfTime(mlog_ptr, if_value, in_time, in_format, va_list)
MLOG                 *mlog_ptr;
int                   if_value;
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

	return_code = MLOG_LogIfTimeVA(mlog_ptr, if_value, in_time, in_format,
		arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogIfTimeVA(MLOG *mlog_ptr, int if_value,
	const struct timeval *in_time, const char *in_format, va_list arg_list)
#else
int MLOG_LogIfTimeVA(mlog_ptr, if_value, in_time, in_format, arg_list)
MLOG                 *mlog_ptr;
int                   if_value;
const struct timeval *in_time;
const char           *in_format;
va_list               arg_list;
#endif /* #ifndef NARGS */
{
	if (!MLOG_DO_LOG(mlog_ptr))
		return(MLOG_FAILURE);
	else if (!if_value)
		return(MLOG_SUCCESS);
	else
		return(MLOG_LogBasicVA(mlog_ptr, in_time, MLOG_PRIORITY_INFO,
			mlog_ptr->user_string, mlog_ptr->flags, mlog_ptr->mfile_mask,
			mlog_ptr->file_mask, mlog_ptr->syslog_mask, in_format, arg_list));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define TEST_MLOG_FILE_NAME		"TEST_MLOG_LogIf.txt"

int main(void);

int main()
{
	int           return_code = MLOG_SUCCESS;
	MLOG         *mlog_ptr    = NULL;
	unsigned int  count_1;
	char          buffer_list[26][666 + 1];
	char          error_text[MLOG_MAX_ERROR_TEXT];

	fprintf(stderr, "%s\n%s\n\n",
		"Test harness for function 'MLOG_LogIf()'\n",
		"                          'MLOG_LogIfVA()'\n");
	fprintf(stderr,
		"---- ------- --- -------- ----------------\n\n");

	fprintf(stderr, "Logs only on odd-numbered attempts.\n\n");

	if ((mlog_ptr = MLOG_FOpenDefault(TEST_MLOG_FILE_NAME)) != NULL) {
		fprintf(stderr, "Opened test file '%s' (%u bytes).\n",
			TEST_MLOG_FILE_NAME, mlog_ptr->initial_alloc);
		for (count_1 = 0; count_1 < 26; count_1++) {
			memset(buffer_list[count_1], ((int) ('A' + count_1)),
				sizeof(buffer_list[0]));
			buffer_list[count_1][sizeof(buffer_list[0]) - 1] = '\0';
		}
		for (count_1 = 0; count_1 < 26; count_1++) {
			MLOG_LogIf(mlog_ptr, (count_1 % 2), "Try number %10u: %s\n",
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

