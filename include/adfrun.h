/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Include File							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Automated Documentation Facility
								executable programs.

	Revision History	:	1995-06-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#ifndef h__ADFRUN_H__h

#define h__ADFRUN_H__h	1

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	int    optional_flag;
#ifndef NARGS
	int  (*usage_function)(const char *base_arg_ptr, int optional_flag,
		char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
		char *error_text);
#else
	int  (*usage_function)();
#endif /* #ifndef NARGS */
	char  *added_text;
} ADF_RUN_USAGE;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(void (*ADF_RUN_EndFunc), (ADF_CONTROL *control_ptr,
	int signal_number, int *exit_code_ptr, const char *message_buffer));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

COMPAT_FN_DECL(int ADF_RUN_OpenLogFile, (ADF_CONTROL *control_ptr,
	char *error_text));
COMPAT_FN_DECL(int ADF_RUN_GetParamsInit, (ADF_CONTROL *control_ptr,
	unsigned int argc, char **argv, ADF_RUN_EndFunc end_func,
	char *error_text));
COMPAT_FN_DECL(void ADF_RUN_EndStart, (ADF_CONTROL *control_ptr,
	const char *message_buffer));
COMPAT_FN_DECL(void ADF_RUN_EndFinish, (ADF_CONTROL *control_ptr));

/*	***********************************************************************	*/

#endif /* #ifndef h__ADFRUN_H__h */

