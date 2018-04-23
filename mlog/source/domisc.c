/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	A number of miscellaneous logging functions.

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

#include <genfuncs.h>

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MLOG_DoSepStart

   SYNOPSIS    :	void MLOG_DoSepStart(mlog_ptr);

						MLOG *mlog_ptr;

   DESCRIPTION :	Emits a log message indicating the beginning of the log
						file to the logging destinations specified by
						``mlog_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to a structure of type
						''MLOG'' which describes the particulars of
						how logging by this function is to be performed.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message indicating the ending of the log
						file with the function ``MLOG_DoSepEnd``.

   SEE ALSO    :	MLOG_DoSepEnd

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	MLOG_DoSepStart
						MLOG Functions:Logging Functions:MLOG_DoSepStart
						MLOG Functions:MLOG_DoSepStart

   PUBLISH XREF:	MLOG_DoSepStart

   PUBLISH NAME:	MLOG_DoSepStart

	ENTRY CLASS	:	MLOG Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_DoSepStart(MLOG *mlog_ptr)
#else
void MLOG_DoSepStart(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	if (MLOG_DO_LOG_EITHER_FILE(mlog_ptr) &&
		(MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS)) {
		MLOG_DoSepEqual(mlog_ptr);
		MLOG_DoSepEqual(mlog_ptr);
		nstrset(mlog_ptr->work_string, ' ', mlog_ptr->used_length);
		center_basic(" START OF LOG FILE ",
			mlog_ptr->work_string + mlog_ptr->used_length, 0, 0, "*",
			mlog_ptr->sep_length);
		if (MLOG_DO_LOG_MFILE(mlog_ptr) &&
			(mprintf_ensure_space(MLOG_GET_MFILE_PTR(mlog_ptr)) == MFILE_TRUE))
			mprintf(MLOG_GET_MFILE_PTR(mlog_ptr), "%s\n", mlog_ptr->work_string);
		if (MLOG_DO_LOG_FILE(mlog_ptr))
			fprintf(MLOG_GET_FILE_PTR(mlog_ptr), "%s\n", mlog_ptr->work_string);
		MLOG_DoSepEqual(mlog_ptr);
		MLOG_Unlock(mlog_ptr, NULL);
	}
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MLOG_DoSepEnd

   SYNOPSIS    :	void MLOG_DoSepEnd(mlog_ptr);

						MLOG *mlog_ptr;

   DESCRIPTION :	Emits a log message indicating the ending of the log
						file to the logging destinations specified by
						``mlog_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to a structure of type
						''MLOG'' which describes the particulars of
						how logging by this function is to be performed.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message indicating the beginning of the
						log file with the function ``MLOG_DoSepStart``.

   SEE ALSO    :	MLOG_DoSepStart

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	MLOG_DoSepEnd
						MLOG Functions:Logging Functions:MLOG_DoSepEnd
						MLOG Functions:MLOG_DoSepEnd

   PUBLISH XREF:	MLOG_DoSepEnd

   PUBLISH NAME:	MLOG_DoSepEnd

	ENTRY CLASS	:	MLOG Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_DoSepEnd(MLOG *mlog_ptr)
#else
void MLOG_DoSepEnd(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	if (MLOG_DO_LOG_EITHER_FILE(mlog_ptr) &&
		(MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS)) {
		MLOG_DoSepEqual(mlog_ptr);
		MLOG_DoSepEqual(mlog_ptr);
		nstrset(mlog_ptr->work_string, ' ', mlog_ptr->used_length);
		center_basic(" END OF LOG FILE ",
			mlog_ptr->work_string + mlog_ptr->used_length, 0, 0, "*",
			mlog_ptr->sep_length);
		if (MLOG_DO_LOG_MFILE(mlog_ptr) &&
			(mprintf_ensure_space(MLOG_GET_MFILE_PTR(mlog_ptr)) == MFILE_TRUE))
			mprintf(MLOG_GET_MFILE_PTR(mlog_ptr), "%s\n", mlog_ptr->work_string);
		if (MLOG_DO_LOG_FILE(mlog_ptr))
			fprintf(MLOG_GET_FILE_PTR(mlog_ptr), "%s\n", mlog_ptr->work_string);
		MLOG_DoSepEqual(mlog_ptr);
		MLOG_Unlock(mlog_ptr, NULL);
	}
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MLOG_DoSepHyphen

   SYNOPSIS    :	void MLOG_DoSepHyphen(mlog_ptr);

						MLOG *mlog_ptr;

   DESCRIPTION :	Emits a log message containing a string of hyphen characters
						(''-'') to the logging destinations specified by
						``mlog_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to a structure of type
						''MLOG'' which describes the particulars of
						how logging by this function is to be performed.

						(-) If ``mlog_ptr`` is ''NULL'' the function will not
						perform any logging.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string of an
						arbitrary characters with the function
						``MLOG_DoSepChar``.

   SEE ALSO    :	MLOG_DoSepEqual
						MLOG_DoSepStar
						MLOG_DoSepChar

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	MLOG_DoSepHyphen
						MLOG Functions:Logging Functions:MLOG_DoSepHyphen
						MLOG Functions:MLOG_DoSepHyphen

   PUBLISH XREF:	MLOG_DoSepHyphen

   PUBLISH NAME:	MLOG_DoSepHyphen

	ENTRY CLASS	:	MLOG Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_DoSepHyphen(MLOG *mlog_ptr)
#else
void MLOG_DoSepHyphen(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	MLOG_DoSepChar(mlog_ptr, '-');
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MLOG_DoSepEqual

   SYNOPSIS    :	void MLOG_DoSepEqual(mlog_ptr);

						MLOG *mlog_ptr;

   DESCRIPTION :	Emits a log message containing a string of equal-sign
						characters (''='') to the logging destinations specified by
						``mlog_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to a structure of type
						''MLOG'' which describes the particulars of
						how logging by this function is to be performed.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string of an
						arbitrary characters with the function
						``MLOG_DoSepChar``.

   SEE ALSO    :	MLOG_DoSepHyphen
						MLOG_DoSepStar
						MLOG_DoSepChar

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	MLOG_DoSepEqual
						MLOG Functions:Logging Functions:MLOG_DoSepEqual
						MLOG Functions:MLOG_DoSepEqual

   PUBLISH XREF:	MLOG_DoSepEqual

   PUBLISH NAME:	MLOG_DoSepEqual

	ENTRY CLASS	:	MLOG Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_DoSepEqual(MLOG *mlog_ptr)
#else
void MLOG_DoSepEqual(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	MLOG_DoSepChar(mlog_ptr, '=');
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MLOG_DoSepStar

   SYNOPSIS    :	void MLOG_DoSepStar(mlog_ptr);

						MLOG *mlog_ptr;

   DESCRIPTION :	Emits a log message containing a string of equal-sign
						characters (''*'') to the logging destinations specified by
						``mlog_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to a structure of type
						''MLOG'' which describes the particulars of
						how logging by this function is to be performed.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string of an
						arbitrary characters with the function
						``MLOG_DoSepChar``.

   SEE ALSO    :	MLOG_DoSepHyphen
						MLOG_DoSepEqual
						MLOG_DoSepChar

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	MLOG_DoSepStar
						MLOG Functions:Logging Functions:MLOG_DoSepStar
						MLOG Functions:MLOG_DoSepStar

   PUBLISH XREF:	MLOG_DoSepStar

   PUBLISH NAME:	MLOG_DoSepStar

	ENTRY CLASS	:	MLOG Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_DoSepStar(MLOG *mlog_ptr)
#else
void MLOG_DoSepStar(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	MLOG_DoSepChar(mlog_ptr, '*');
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MLOG_DoSepChar

   SYNOPSIS    :	void MLOG_DoSepChar(mlog_ptr, log_char);

						MLOG *mlog_ptr;

						int   log_char;

   DESCRIPTION :	Emits a log message containing a string of ``log_char``
						characters to the logging destinations specified by
						``mlog_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to a structure of type
						''MLOG'' which describes the particulars of
						how logging by this function is to be performed.

						(.) ``log_char`` is the character to be used in logging.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string with the
						function ``MLOG_DoSepString``.

   SEE ALSO    :	MLOG_DoSepCharBasic
						MLOG_DoSepString

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	MLOG_DoSepChar
						MLOG Functions:Logging Functions:MLOG_DoSepChar
						MLOG Functions:MLOG_DoSepChar

   PUBLISH XREF:	MLOG_DoSepChar

   PUBLISH NAME:	MLOG_DoSepChar

	ENTRY CLASS	:	MLOG Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_DoSepChar(MLOG *mlog_ptr, int log_char)
#else
void MLOG_DoSepChar(mlog_ptr, log_char)
MLOG *mlog_ptr;
int   log_char;
#endif /* #ifndef NARGS */
{
	if (MLOG_IS_PTR_I(mlog_ptr))
		MLOG_DoSepCharBasic(mlog_ptr, mlog_ptr->sep_length, log_char);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MLOG_DoSepCharBasic

   SYNOPSIS    :	void MLOG_DoSepCharBasic(mlog_ptr, sep_length, log_char);

						MLOG         *mlog_ptr;

						unsigned int  sep_length;

						int           log_char;

   DESCRIPTION :	Emits a log message containing a string of ``log_char``
						characters to the logging destinations specified by
						``mlog_ptr``.

						Additional separator characters are emitted with the
						length specified by the ``sep_length`` character.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to a structure of type
						''MLOG'' which describes the particulars of
						how logging by this function is to be performed.

						(.) ``sep_length`` specifies the number of characters to
						be after the leading log dates, times, log priorities,
						``et cetera``.

						(-) If ``sep_length`` is ''0'', then the default separator
						length will be used.

						(.) ``log_char`` is the character to be used in logging.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string with the
						function ``MLOG_DoSepString``.

   SEE ALSO    :	MLOG_DoSepChar
						MLOG_DoSepString

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	MLOG_DoSepCharBasic
						MLOG Functions:Logging Functions:MLOG_DoSepCharBasic
						MLOG Functions:MLOG_DoSepCharBasic

   PUBLISH XREF:	MLOG_DoSepCharBasic

   PUBLISH NAME:	MLOG_DoSepCharBasic

	ENTRY CLASS	:	MLOG Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_DoSepCharBasic(MLOG *mlog_ptr, unsigned int sep_length, int log_char)
#else
void MLOG_DoSepCharBasic(mlog_ptr, sep_length, log_char)
MLOG         *mlog_ptr;
unsigned int  sep_length;
int           log_char;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	unsigned int total_length;

	if (MLOG_DO_LOG_EITHER_FILE(mlog_ptr) &&
		(MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS)) {
		sep_length   = (sep_length) ? sep_length : mlog_ptr->sep_length;
		sep_length   = (sep_length) ? sep_length : 80;
		total_length = mlog_ptr->used_length + sep_length;
		total_length = (total_length < (mlog_ptr->work_length - 1)) ?
			total_length : (mlog_ptr->work_length - 2);
		nstrset(mlog_ptr->work_string, log_char, total_length);
		mlog_ptr->work_string[mlog_ptr->used_length - 1] = ' ';
		for (count_1 = 1; count_1 < mlog_ptr->format_count; count_1++)
			mlog_ptr->work_string[mlog_ptr->format_list[count_1].offset-1] = ' ';
		MLOG_DoSepString(mlog_ptr, mlog_ptr->work_string);
		MLOG_Unlock(mlog_ptr, NULL);
	}
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MLOG_DoSepString

   SYNOPSIS    :	void MLOG_DoSepString(mlog_ptr, log_string);

						MLOG       *mlog_ptr;

						const char *log_string;

   DESCRIPTION :	Emits a log message containing the string of ``log_string``
						to the logging destinations specified by
						``mlog_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to a structure of type
						''MLOG'' which describes the particulars of
						how logging by this function is to be performed.

						(.) ``log_string`` is the string to be used in logging.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string of an
						characters with the function ``MLOG_DoSepChar``.

   SEE ALSO    :	MLOG_DoSepChar

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	MLOG_DoSepString
						MLOG Functions:Logging Functions:MLOG_DoSepString
						MLOG Functions:MLOG_DoSepString

   PUBLISH XREF:	MLOG_DoSepString

   PUBLISH NAME:	MLOG_DoSepString

	ENTRY CLASS	:	MLOG Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_DoSepString(MLOG *mlog_ptr, const char *log_string)
#else
void MLOG_DoSepString(mlog_ptr, log_string)
MLOG       *mlog_ptr;
const char *log_string;
#endif /* #ifndef NARGS */
{
	if (MLOG_DO_LOG_EITHER_FILE(mlog_ptr) &&
		(MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS)) {
		if (MLOG_DO_LOG_MFILE(mlog_ptr) &&
			(mprintf_ensure_space(MLOG_GET_MFILE_PTR(mlog_ptr)) == MFILE_TRUE))
			mprintf(MLOG_GET_MFILE_PTR(mlog_ptr), "%s\n", log_string);
		if (MLOG_DO_LOG_FILE(mlog_ptr))
			fprintf(MLOG_GET_FILE_PTR(mlog_ptr), "%s\n", log_string);
		MLOG_CompleteOutput(mlog_ptr);
		MLOG_Unlock(mlog_ptr, NULL);
	}
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MLOG_DoExecTime

   SYNOPSIS    :	void MLOG_DoExecTime(start_time, end_time,
							overhead_end_time, mlog_ptr);

						MLOG                 *mlog_ptr;

						const struct timeval *start_time;

						const struct timeval *end_time;

						const struct timeval *overhead_end_time;

   DESCRIPTION :	Logs information about the running time of a executable to
						a log file.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to a structure of type
						''MLOG'' which describes the particulars of
						how logging by this function is to be performed.

						(-) If ``mlog_ptr`` is ''NULL'' the function will not
						perform any logging.

						(.) ``start_time`` is a pointer to a ``struct timeval``
						which contains the starting time of the executable.

						(.) ``end_time`` is a pointer to a ``struct timeval``
						which contains the ending time of the executable.

						(-) If ``end_time`` is ''NULL'', the current time will
						be used.

						(.) ``overhead_end_time`` is a pointer to a ``struct
						timeval`` which contains the time at which the executable
						finished its overhead processing.

						(-) If ``overhead_end_time`` is ''NULL'', overhead
						processing time will be reported as zero.

   RETURNS     :	Void.

   SEE ALSO    :	MLOG_DoRUsage

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	MLOG_DoExecTime
						MLOG Functions:Logging Functions:MLOG_DoExecTime
						MLOG Functions:MLOG_DoExecTime

   PUBLISH XREF:	MLOG_DoExecTime

   PUBLISH NAME:	MLOG_DoExecTime

	ENTRY CLASS	:	Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_DoExecTime(MLOG *mlog_ptr, const struct timeval *start_time,
	const struct timeval *end_time, const struct timeval *overhead_end_time)
#else
void MLOG_DoExecTime(mlog_ptr, start_time, end_time, overhead_end_time)
MLOG                 *mlog_ptr;
const struct timeval *start_time;
const struct timeval *end_time;
const struct timeval *overhead_end_time;
#endif /* #ifndef NARGS */
{
	struct timeval tmp_end_time;
	struct timeval overhead_interval;
	struct timeval total_interval;
	char           tmp_interval[256];

	if (!MLOG_DO_LOG_EITHER_FILE(mlog_ptr))
		goto EXIT_FUNCTION;

	/*	**************************************************************
		**************************************************************
		Default the end time to now . . .
		**************************************************************	*/
	if (end_time == NULL) {
		SDTIF_GetTimeUSecs(&tmp_end_time);
		end_time = ((const struct timeval *) &tmp_end_time);
	}
	/*	**************************************************************	*/

	/*	**************************************************************
		**************************************************************
		Calculate the basic total executable time . . .
		**************************************************************	*/
	SDTIF_GetABSInterval_timeval(start_time, end_time, &total_interval);
	/*	**************************************************************	*/

	/*	**************************************************************
		**************************************************************
		Calculate the executable overhead time . . .
		**************************************************************	*/
	if ((overhead_end_time != NULL) &&
		(overhead_end_time->tv_sec || overhead_end_time->tv_usec))
		SDTIF_GetABSInterval_timeval(start_time, overhead_end_time,
			&overhead_interval);
	else {
		overhead_interval.tv_sec  = 0L;
		overhead_interval.tv_usec = 0L;
	}
	/*	**************************************************************	*/

	/*	**************************************************************
		**************************************************************
		Show timing statistics . . .
		**************************************************************	*/
	if (MLOG_DO_LOG_EITHER_FILE(mlog_ptr) &&
		(MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS)) {
		MLOG_DoSepCharBasic(mlog_ptr, 56, '=');
		MLOG_LogInfoTime(mlog_ptr, end_time, "%-28.28s: %s\n", "Start Time",
			SDTIF_Format_timeval(start_time, tmp_interval));
		MLOG_LogInfoTime(mlog_ptr, end_time, "%-28.28s: %s\n", "End Time",
			SDTIF_Format_timeval(end_time, tmp_interval));
		MLOG_DoSepCharBasic(mlog_ptr, 56, '-');
		MLOG_LogInfoTime(mlog_ptr, end_time, "%-28.28s: %s\n", "Overhead Time",
			SDTIF_FormatInterval_timeval(&overhead_interval, tmp_interval));
		MLOG_LogInfoTime(mlog_ptr, end_time, "%-28.28s: %s\n", "Total Time",
			SDTIF_FormatInterval_timeval(&total_interval, tmp_interval));
		MLOG_DoSepCharBasic(mlog_ptr, 56, '-');
		MLOG_Unlock(mlog_ptr, NULL);
	}
	/*	**************************************************************	*/

EXIT_FUNCTION:

	return;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MLOG_DoRUsage

   SYNOPSIS    :	void MLOG_DoRUsage(mlog_ptr);

						MLOG *mlog_ptr;

   DESCRIPTION :	Logs information about the operating system resource usage
						metrics of an executable to a log file.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to a structure of type
						''MLOG'' which describes the particulars of
						how logging by this function is to be performed.

   RETURNS     :	Void.

   NOTES       :	This function uses ``GEN_FormatRUsageList`` to determine
						and format the usage metrics.

   SEE ALSO    :	MLOG_DoExecTime

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	MLOG_DoRUsage
						MLOG Functions:Logging Functions:MLOG_DoRUsage
						MLOG Functions:MLOG_DoRUsage

   PUBLISH XREF:	MLOG_DoRUsage

   PUBLISH NAME:	MLOG_DoRUsage

	ENTRY CLASS	:	Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_DoRUsage(MLOG *mlog_ptr)
#else
void MLOG_DoRUsage(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int     rusage_count = 0;
	char           **rusage_list  = NULL;
	unsigned int     count_1;
	struct timeval   this_time;
	char             error_text[GENFUNCS_MAX_ERROR_TEXT];

	if (!MLOG_DO_LOG_EITHER_FILE(mlog_ptr))
		goto EXIT_FUNCTION;

	/*	**************************************************************
		**************************************************************
		Try to get the formatted process usage information . . .
		**************************************************************	*/
	if ((mlog_ptr == NULL) || ((GEN_FormatRUsageList(NULL, 28,
		GEN_RUSAGE_NULL_FORMAT_NULL, &rusage_count, &rusage_list,
		error_text)) != GENFUNCS_SUCCESS))
		goto EXIT_FUNCTION;
	/*	**************************************************************	*/

	/*	**************************************************************
		**************************************************************
		Show the process resource usage . . .
		**************************************************************	*/
	if (MLOG_DO_LOG_EITHER_FILE(mlog_ptr) &&
		(MLOG_Lock(mlog_ptr, NULL) == MLOG_SUCCESS)) {
		SDTIF_GetTimeUSecs(&this_time);
		MLOG_DoSepCharBasic(mlog_ptr, 56, '=');
		for (count_1 = 0; count_1 < rusage_count; count_1++)
			MLOG_LogInfoTime(mlog_ptr, &this_time, "%s\n", rusage_list[count_1]);
		MLOG_DoSepCharBasic(mlog_ptr, 56, '=');
		MLOG_Unlock(mlog_ptr, NULL);
	}
	/*	**************************************************************	*/

	/*	**************************************************************
		**************************************************************
		Free the formatted process usage information . . .
		**************************************************************	*/
	strl_remove_all(&rusage_count, &rusage_list);
	/*	**************************************************************	*/

EXIT_FUNCTION:

	return;
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <strfuncs.h>

#define TEST_MLOG_FILE_NAME				"TEST_MLOG_Miscellaneous.txt"

COMPAT_FN_DECL(int main, (void));

int main()
{
	int             return_code = MLOG_SUCCESS;
	MLOG           *mlog_ptr    = NULL;
	struct timeval  time_1;
	struct timeval  time_2;
	char            error_text[MLOG_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for miscellaneous logging functions\n");
	fprintf(stderr, "---- ------- --- ------------- ------- ---------\n\n");

	if ((mlog_ptr = MLOG_FOpenDefault(TEST_MLOG_FILE_NAME)) == NULL) {
		sprintf(error_text, "Unable to open output test log file '%s'.",
			TEST_MLOG_FILE_NAME);
		return_code = MLOG_FAILURE;
	}
	else if ((return_code = MLOG_SetLogFormat(mlog_ptr, "DTMPL", NULL,
		error_text)) == MLOG_SUCCESS) {
		SDTIF_GetTimeUSecs(&time_1);
		SDTIF_GetTimeUSecs(&time_2);
		MLOG_LogInfo(mlog_ptr, "%s %s\n", ">>>>>>>>>>>>>>>>>>>>",
			"MLOG_DoSepStart");
		MLOG_DoSepStart(mlog_ptr);
		MLOG_LogInfo(mlog_ptr, "%s %s\n", ">>>>>>>>>>>>>>>>>>>>",
			"MLOG_DoSepEnd");
		MLOG_DoSepEnd(mlog_ptr);
		MLOG_LogInfo(mlog_ptr, "%s %s\n", ">>>>>>>>>>>>>>>>>>>>",
			"MLOG_DoSepHyphen");
		MLOG_DoSepHyphen(mlog_ptr);
		MLOG_LogInfo(mlog_ptr, "%s %s\n", ">>>>>>>>>>>>>>>>>>>>",
			"MLOG_DoSepEqual");
		MLOG_DoSepEqual(mlog_ptr);
		MLOG_LogInfo(mlog_ptr, "%s %s\n", ">>>>>>>>>>>>>>>>>>>>",
			"MLOG_DoSepStar");
		MLOG_DoSepStar(mlog_ptr);
		MLOG_LogInfo(mlog_ptr, "%s %s\n", ">>>>>>>>>>>>>>>>>>>>",
			"MLOG_DoSepChar");
		MLOG_DoSepChar(mlog_ptr, '#');
		MLOG_LogInfo(mlog_ptr, "%s %s\n", ">>>>>>>>>>>>>>>>>>>>",
			"MLOG_DoSepString");
		MLOG_DoSepString(mlog_ptr, "Yadda, yadda, yadda.");
		MLOG_LogInfo(mlog_ptr, "%s %s\n", ">>>>>>>>>>>>>>>>>>>>",
			"MLOG_DoExecTime");
		MLOG_DoExecTime(mlog_ptr, &time_1, &time_2, NULL);
		MLOG_LogInfo(mlog_ptr, "%s %s\n", ">>>>>>>>>>>>>>>>>>>>",
			"MLOG_DoRUsage");
		MLOG_DoRUsage(mlog_ptr);
	}

	MLOG_Close(mlog_ptr, NULL);

	if (return_code != MLOG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifndef NARGS */

