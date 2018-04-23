/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Check functions for the library.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
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

#include <strfuncs.h>

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Functions private to this module . . .												*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int MLOG_CheckPriorityBasic, (MLOG_PRIORITY in_mask,
	const char *in_name, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MLOG_Check

	SYNOPSIS		:	return_code = MLOG_Check(mlog_ptr, error_text);

						int         return_code;

						const MLOG *mlog_ptr;

						char       *error_text;


	DESCRIPTION	:	Checks a pointer to a ''MLOG'' structure for validity.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to the ''MLOG'' structure to be
						checked for validity by this function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''MLOG_MAX_ERROR_TEXT'' characters in length.

						(-) The ``error_text`` parameter may be ''NULL'', in which
						case this function will not de-reference it.

	RETURNS		:	Returns from this function are as follow:

						(.) ''MLOG_SUCCESS'' if the function completes without
						error. ''MLOG_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero MLOG return codes
						indicative of error.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	MLOG_Check
						Check Structure Functions:MLOG_Check

	PUBLISH XREF:	MLOG_Check

	PUBLISH NAME:	MLOG_Check

	ENTRY CLASS	:	Check Structure Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_Check(const MLOG *mlog_ptr, char *error_text)
#else
int MLOG_Check(mlog_ptr, error_text)
const MLOG *mlog_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char buffer[STR_VAL2STR_MAX_LEN + 1];

	if (((return_code =
		((MLOG_IS_PTR_I(mlog_ptr)) ? MLOG_SUCCESS : MLOG_FAILURE)) !=
		MLOG_SUCCESS) && (error_text != NULL))
		strcat(strcat(strcpy(error_text,
			"Invalid 'MLOG' structure pointer (0x"),
			lower(val2str(((unsigned long) mlog_ptr), 0, 16, "",
			buffer))), ").");

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_CheckFlags(MLOG_FLAG flags, char *error_text)
#else
int MLOG_CheckFlags(flags, error_text)
MLOG_FLAG  flags;
char      *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char number[STR_VAL2STR_MAX_LEN + 1];

	if ((!MLOG_FLAG_MASK) & flags) {
		if (error_text != NULL)
			strcat(strcat(strcpy(error_text, "Invalid flags (flags = 0x"),
				val2str(((unsigned long) flags), 0, 16, "0", number)), ").");
		return_code = MLOG_BAD_ARGS_FAILURE;
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_CheckPriority(MLOG_PRIORITY priority_mask, char *error_text)
#else
int MLOG_CheckPriority(priority_mask, error_text)
MLOG_PRIORITY  priority_mask;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(MLOG_CheckPriorityBasic(priority_mask, "", error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_CheckPriorityMFile(MLOG_PRIORITY mfile_mask, char *error_text)
#else
int MLOG_CheckPriorityMFile(mfile_mask, error_text)
MLOG_PRIORITY  mfile_mask;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(MLOG_CheckPriorityBasic(mfile_mask, "MFILE", error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_CheckPriorityFile(MLOG_PRIORITY file_mask, char *error_text)
#else
int MLOG_CheckPriorityFile(file_mask, error_text)
MLOG_PRIORITY  file_mask;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(MLOG_CheckPriorityBasic(file_mask, "FILE", error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_CheckPrioritySyslog(MLOG_PRIORITY syslog_mask, char *error_text)
#else
int MLOG_CheckPrioritySyslog(syslog_mask, error_text)
MLOG_PRIORITY  syslog_mask;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(MLOG_CheckPriorityBasic(syslog_mask, "SYSLOG", error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_CheckLogFormat(const char *log_format, char *error_text)
#else
int MLOG_CheckLogFormat(log_format, error_text)
const char *log_format;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = MLOG_SUCCESS;
	unsigned int count_1;

	if ((log_format != NULL) && *log_format) {
		for (count_1 = 0; count_1 < strlen(log_format); count_1++) {
			if (strichr(MLOG_FORMAT_VALID_STRING, log_format[count_1]) == NULL) {
				if (error_text != NULL)
					sprintf(error_text, "%s (ASCII %uD = '%c').",
						"Invalid log format character",
						((unsigned int) log_format[count_1]),
						(isprint(log_format[count_1])) ? log_format[count_1] : '?');
				return_code = MLOG_BAD_ARGS_FAILURE;
				break;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_CheckUserString(const char *log_format, const char *user_string,
	char *error_text)
#else
int MLOG_CheckUserString(log_format, user_string, error_text)
const char *log_format;
const char *user_string;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MLOG_SUCCESS;

	if ((return_code = MLOG_CheckLogFormat(log_format, error_text)) ==
		MLOG_SUCCESS) {
		if ((user_string != NULL) && *user_string && (log_format != NULL) &&
			*log_format && (strichr(log_format, 'U') == NULL)) {
			if (error_text != NULL)
				strcat(strcpy(error_text, "User string is set, but the log "),
					"does not contain a user string specification ('U').");
			return_code = MLOG_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int MLOG_CheckPriorityBasic(MLOG_PRIORITY in_mask, const char *in_name,
	char *error_text)
#else
static int MLOG_CheckPriorityBasic(in_mask, in_name, error_text)
MLOG_PRIORITY  in_mask;
const char    *in_name;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char number[STR_VAL2STR_MAX_LEN + 1];

	if ((!MLOG_PRIORITY_MASK) & in_mask) {
		if (error_text != NULL)
			strcat(strcat(strcat(strcat(strcpy(error_text, "Invalid "), in_name),
				" priority mask (mask = 0x"),
				val2str(((unsigned long) in_mask), 0, 16, "0", number)), ").");
		return_code = MLOG_BAD_ARGS_FAILURE;
	}
	else
		return_code = MLOG_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/


