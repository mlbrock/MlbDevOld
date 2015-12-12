/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the Unix resource usage structure.

	Revision History	:	1992-10-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <limits.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
# if _MSC_VER >= 1300
#  include <psapi.h>
# endif /* #if _MSC_VER >= 1300 */
#else
# ifdef __SVR4
#  define __EXTENSIONS__
#  include <unistd.h>
#  include <sys/types.h>
#  include <sys/signal.h>
#  include <sys/fault.h>
#  include <sys/syscall.h>
#  include <sys/procfs.h>
# else
#  include <sys/resource.h>
# endif /* #ifdef __SVR4 */
#endif /* #ifdef _MSC_VER */

#include <strfuncs.h>
#include <sdtif.h>

#include "genfunci.h"

#if _MSC_VER >= 1300
# include "psapi.h"
#endif /* #if _MSC_VER >= 1300 */

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/*    The macro 'offsetof' is defined by ANSI C. If it's not available on  */
/* this system, define it . . .                                            */
/* *********************************************************************** */
#ifndef offsetof
#define offsetof(structure_name, member_name)	\
	((size_t) &(((structure_name *) 0)->member_name))
#endif /* #ifndef offsetof */
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define GEN_RUSAGE_FIRST_TIME				user_cpu_time
#define GEN_RUSAGE_LAST_TIME				stopped_time
#define GEN_RUSAGE_FIRST_VALUE			minor_pagef
#define GEN_RUSAGE_LAST_VALUE				chars_read_written

#define GEN_RUSAGE_GET_FIRST_TIME_PTR(rusage_ptr)				\
	((struct timeval *) ((void *) (((char *) rusage_ptr) +	\
	offsetof(GEN_RUSAGE, GEN_RUSAGE_FIRST_TIME))))
#define GEN_RUSAGE_GET_LAST_TIME_PTR(rusage_ptr)				\
	((struct timeval *) ((void *) (((char *) rusage_ptr) +	\
	offsetof(GEN_RUSAGE, GEN_RUSAGE_LAST_TIME))))
#define GEN_RUSAGE_GET_FIRST_VALUE_PTR(rusage_ptr)				\
	((unsigned long *) ((void *) (((char *) rusage_ptr) +		\
	offsetof(GEN_RUSAGE, GEN_RUSAGE_FIRST_VALUE))))
#define GEN_RUSAGE_GET_LAST_VALUE_PTR(rusage_ptr)				\
	((unsigned long *) ((void *) (((char *) rusage_ptr) +		\
	offsetof(GEN_RUSAGE, GEN_RUSAGE_LAST_VALUE))))
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
static const char *GEN_RUSAGE_TimeNameList[] = {
	"User Level CPU Time",
	"System Call CPU Time",
	"Other System Trap CPU Time",
	"Text Page Fault Sleep Time",
	"Data Page Fault Sleep Time",
	"Kernel Page Fault Sleep Time",
	"User Lock Wait Sleep Time",
	"Other Sleep Time",
	"Wait-CPU Latency Time",
	"Stopped Time"
};

static const char *GEN_RUSAGE_ValueNameList[] = {
	"Minor Page Faults",
	"Major Page Faults",
	"Process Swaps",
	"Input Blocks",
	"Output Blocks",
	"Messages Sent",
	"Messages Received",
	"Signals Received",
	"Voluntary Context Switches",
	"Involuntary Context Switches",
	"System Calls",
	"Characters Read and Written"
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
static const struct timeval GEN_RUSAGE_TimeValNULL =
	{	((long) ULONG_MAX), ((long) ULONG_MAX)	};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	For use with Windows . . .																*/
/*	***********************************************************************	*/
#if _Windows
typedef COMPAT_FN_TYPE(BOOL (WINAPI *GEN_Win32_FPtr_GetProcessTimes),
	(HANDLE, LPFILETIME, LPFILETIME, LPFILETIME, LPFILETIME));
# if _MSC_VER >= 1300
typedef COMPAT_FN_TYPE(BOOL (WINAPI *GEN_Win32_FPtr_GetMemInfoFPtr),
	(FARPROC, PROCESS_MEMORY_COUNTERS *, DWORD));
typedef COMPAT_FN_TYPE(BOOL (WINAPI *GEN_Win32_FPtr_GetProcessIoCounters),
	(HANDLE, PIO_COUNTERS));
# endif /* # if _MSC_VER >= 1300 */
#endif /* #if _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_GetRUsage

   SYNOPSIS    :	return_code = GEN_GetRUsage(selector, rusage_ptr,
							error_text);

						int         return_code;

						int         selector;

						GEN_RUSAGE *delta_rusage_ptr;

						char       *error_text;

   DESCRIPTION :	Determines the values of a number of operating system
						dependent usage metrics.

						Under BSD systems such as SubOS, this function uses the
						''struct rusage'' structure to populate the usage metrics.

						Under System V systems such as Solaris, this function uses
						the ''struct prusage'' structure to populate the usage
						metrics.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``rusage_ptr`` points to the ''GEN_RUSAGE'' into which
						this function is to place the usage metrics determined by
						the function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	Not all of the usage metrics supplied as members in
						''GEN_RUSAGE'' are available on all operating systems.
						This function populates members which are unavailable in
						following way:

						For ''struct timeval'' members, the ``tv_sec`` and
						``tv_usec`` members are set to ''ULONG_MAX'' (or, more
						accurately, ''((long) ULONG_MAX)'').

						''unsigned long'' members are set to ''ULONG_MAX''.

						These values have special meaning to the usage formatting
						function ``GEN_FormatRUsageList`` --- and should to any
						application programmers who desire to interrogate the
						members directly.

   CAVEATS     :	

   SEE ALSO    :	GEN_GetRUsageDelta
						GEN_FormatRUsageList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_GetRUsage
						Miscellaneous Functions:GEN_GetRUsage
						GENFUNCS:Functions:GEN_GetRUsage
						GENFUNCS:Miscellaneous Functions:GEN_GetRUsage
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_GetRUsage

   PUBLISH NAME:	GEN_GetRUsage

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_GetRUsage(int selector, GEN_RUSAGE *rusage_ptr, char *error_text)
#else
int GEN_GetRUsage(selector, rusage_ptr, error_text)
int         selector;
GEN_RUSAGE *rusage_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	int return_code = GENFUNCS_SUCCESS;

	memset(rusage_ptr, '\0', sizeof(*rusage_ptr));

	return(return_code);
}
#elif _Windows
	int                                 return_code = GENFUNCS_SUCCESS;
	HMODULE                             module_kernel32;
	SDTIF_WIN32_FILETIME_64             creation_time;
	SDTIF_WIN32_FILETIME_64             exit_time;
	SDTIF_WIN32_FILETIME_64             kernel_time;
	SDTIF_WIN32_FILETIME_64             user_time;
	GEN_Win32_FPtr_GetProcessTimes      proc_times_fptr;
#if _MSC_VER >= 1300
	HMODULE                             module_psapi;
	GEN_Win32_FPtr_GetMemInfoFPtr       mem_info_fptr;
	GEN_Win32_FPtr_GetProcessIoCounters proc_io_fptr;
	PROCESS_MEMORY_COUNTERS             mem_counters;
	IO_COUNTERS                         io_counters;
#endif /* #if _MSC_VER >= 1300 */

	memset(rusage_ptr, '\0', sizeof(*rusage_ptr));

	if ((module_kernel32 = GetModuleHandle("Kernel32")) == NULL) {
		strcpy(error_text, "Call to 'GetModuleHandle()' for 'Kernel32' failed: ");
		return_code = GENFUNCS_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((proc_times_fptr =
		((GEN_Win32_FPtr_GetProcessTimes) GetProcAddress(module_kernel32,
		"GetProcessTimes"))) != NULL) {
		if ((*proc_times_fptr)(((FARPROC) selector), &creation_time.struct_data,
			&exit_time.struct_data, &kernel_time.struct_data,
			&user_time.struct_data) == 0) {
			strcpy(error_text, "Call to 'GetProcessTimes()' failed: ");
			return_code = GENFUNCS_SYSTEM_FAILURE;
			goto EXIT_FUNCTION;
		}
		rusage_ptr->user_cpu_time.tv_sec    =
			((long) (user_time.scalar_data   / 10i64)) / 1000000L;
		rusage_ptr->user_cpu_time.tv_usec   =
			((long) (user_time.scalar_data   / 10i64)) % 1000000L;
		rusage_ptr->system_cpu_time.tv_sec  =
			((long) (kernel_time.scalar_data / 10i64)) / 1000000L;
		rusage_ptr->system_cpu_time.tv_usec =
			((long) (kernel_time.scalar_data / 10i64)) % 1000000L;
	}

#if _MSC_VER >= 1300
	if ((module_psapi = GetModuleHandle("psapi")) != NULL) {
		if ((mem_info_fptr =
			((GEN_Win32_FPtr_GetMemInfoFPtr) GetProcAddress(module_kernel32,
			"GetProcessMemoryInfo"))) != NULL) {
			if ((*mem_info_fptr)(((FARPROC) selector), &mem_counters,
				sizeof(mem_counters)) == 0) {
				strcpy(error_text, "Call to 'GetProcessMemoryInfo()' failed: ");
				return_code = GENFUNCS_SYSTEM_FAILURE;
				goto EXIT_FUNCTION;
			}
			rusage_ptr->major_pagef = mem_counters.PageFaultCount;
		}
	}
#endif /* #if _MSC_VER >= 1300 */

#if _MSC_VER >= 1300
	if ((proc_io_fptr =
		((GEN_Win32_FPtr_GetProcessIoCounters) GetProcAddress(module_kernel32,
		"GetProcessIoCounters"))) != NULL) {
		if ((*proc_io_fptr)(((FARPROC) selector), &io_counters) == 0) {
			strcpy(error_text, "Call to 'GetProcessIoCounters()' failed: ");
			return_code = GENFUNCS_SYSTEM_FAILURE;
			goto EXIT_FUNCTION;
		}
		rusage_ptr->messages_received  = ((unsigned long)
			io_counters.ReadOperationCount);
		rusage_ptr->messages_sent      = ((unsigned long)
			io_counters.WriteOperationCount);
		rusage_ptr->chars_read_written = ((unsigned long)
			(io_counters.ReadTransferCount + io_counters.WriteTransferCount));
	}
#endif /* #if _MSC_VER >= 1300 */

EXIT_FUNCTION:

	if (return_code != GENFUNCS_SUCCESS)
		GEN_AppendLastErrorString_Win32(0, GENFUNCS_MAX_ERROR_TEXT, error_text);

	return(return_code);
}
#elif __SVR4
#include <sys/resource.h>

	int             return_code = GENFUNCS_SUCCESS;
	int             file_handle = -1;
	struct prusage  tmp_prusage;
	struct timeval *timeval_ptr;
	char            proc_file_name[1 + 4 + 1 + 11 + 1];

	memset(rusage_ptr, '\0', sizeof(*rusage_ptr));
	memset(&tmp_prusage, '\0', sizeof(tmp_prusage));

	sprintf(proc_file_name, "/proc/%05d", selector);
	if ((file_handle = open(proc_file_name, O_RDONLY)) == -1) {
		sprintf(error_text,
			"Unable to open process control file '%s' for reading: ",
			proc_file_name);
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
	}
	else if (ioctl(file_handle, PIOCUSAGE, &tmp_prusage) == -1) {
		sprintf(error_text, "%s %d failed ('ioctl(%d, %d = PIOCUSAGE, %p)'): ",
			"Attempt to retrieve the process usage information for pid",
			selector, file_handle, PIOCUSAGE, &tmp_prusage);
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
	}
	else {
		rusage_ptr->user_cpu_time        =
			*((struct timeval *) &tmp_prusage.pr_utime);
		rusage_ptr->system_cpu_time      =
			*((struct timeval *) &tmp_prusage.pr_stime);
		rusage_ptr->trap_cpu_time        =
			*((struct timeval *) &tmp_prusage.pr_ttime);
		rusage_ptr->text_pagef_time      =
			*((struct timeval *) &tmp_prusage.pr_tftime);
		rusage_ptr->data_pagef_time      =
			*((struct timeval *) &tmp_prusage.pr_dftime);
		rusage_ptr->kernel_pagef_time    =
			*((struct timeval *) &tmp_prusage.pr_kftime);
		rusage_ptr->user_lock_time       =
			*((struct timeval *) &tmp_prusage.pr_ltime);
		rusage_ptr->other_sleep_time     =
			*((struct timeval *) &tmp_prusage.pr_slptime);
		rusage_ptr->wait_cpu_time        =
			*((struct timeval *) &tmp_prusage.pr_wtime);
		rusage_ptr->stopped_time         =
			*((struct timeval *) &tmp_prusage.pr_stoptime);
		rusage_ptr->minor_pagef          = tmp_prusage.pr_minf;
		rusage_ptr->major_pagef          = tmp_prusage.pr_majf;
		rusage_ptr->process_swaps        = tmp_prusage.pr_nswap;
		rusage_ptr->input_blocks         = tmp_prusage.pr_inblk;
		rusage_ptr->output_blocks        = tmp_prusage.pr_oublk;
		rusage_ptr->messages_sent        = tmp_prusage.pr_msnd;
		rusage_ptr->messages_received    = tmp_prusage.pr_mrcv;
		rusage_ptr->signals_received     = tmp_prusage.pr_sigs;
		rusage_ptr->vol_context_switch   = tmp_prusage.pr_vctx;
		rusage_ptr->invol_context_switch = tmp_prusage.pr_ictx;
		rusage_ptr->system_calls         = tmp_prusage.pr_sysc;
		rusage_ptr->chars_read_written   = tmp_prusage.pr_ioch;
		timeval_ptr                      =
			GEN_RUSAGE_GET_FIRST_TIME_PTR(rusage_ptr);
		while (timeval_ptr <= GEN_RUSAGE_GET_LAST_TIME_PTR(rusage_ptr)) {
			timeval_ptr->tv_usec /= 1000000L;
			timeval_ptr++;
		}
	}

	if (file_handle > -1)
		close(file_handle);

	return(return_code);
}
#else
#include <sys/resource.h>

	int             return_code = GENFUNCS_SUCCESS;
	struct rusage tmp_rusage;

	memset(rusage_ptr, '\0', sizeof(*rusage_ptr));
	memset(&tmp_rusage, '\0', sizeof(tmp_rusage));

	if (getrusage(selector, &tmp_rusage)) {
		sprintf(error_text, "%s %s failed ('getrusage(%d = '%s', %p)'): ",
			"Attempt to retrieve the process usage information for",
			(selector == RUSAGE_SELF) ? "this process" :
			(selector == RUSAGE_CHILDREN) ? "this process children" :
			"*** UNKNOWN ***", selector, (selector == RUSAGE_SELF) ?
			"RUSAGE_SELF" : (selector == RUSAGE_CHILDREN) ? "RUSAGE_CHILDREN" :
			"*** UNKNOWN ***", rusage_ptr);
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
	}
	else {
		rusage_ptr->user_cpu_time        = tmp_rusage.ru_utime;
		rusage_ptr->system_cpu_time      = tmp_rusage.ru_stime;
		rusage_ptr->trap_cpu_time        = GEN_RUSAGE_TimeValNULL;
		rusage_ptr->text_pagef_time      = GEN_RUSAGE_TimeValNULL;
		rusage_ptr->data_pagef_time      = GEN_RUSAGE_TimeValNULL;
		rusage_ptr->kernel_pagef_time    = GEN_RUSAGE_TimeValNULL;
		rusage_ptr->user_lock_time       = GEN_RUSAGE_TimeValNULL;
		rusage_ptr->other_sleep_time     = GEN_RUSAGE_TimeValNULL;
		rusage_ptr->wait_cpu_time        = GEN_RUSAGE_TimeValNULL;
		rusage_ptr->stopped_time         = GEN_RUSAGE_TimeValNULL;
		rusage_ptr->minor_pagef          =
			((unsigned long) tmp_rusage.ru_minflt);
		rusage_ptr->major_pagef          =
			((unsigned long) tmp_rusage.ru_majflt);
		rusage_ptr->process_swaps        =
			((unsigned long) tmp_rusage.ru_nswap);
		rusage_ptr->input_blocks         =
			((unsigned long) tmp_rusage.ru_inblock);
		rusage_ptr->output_blocks        =
			((unsigned long) tmp_rusage.ru_oublock);
		rusage_ptr->messages_sent        =
			((unsigned long) tmp_rusage.ru_msgsnd);
		rusage_ptr->messages_received    =
			((unsigned long) tmp_rusage.ru_msgrcv);
		rusage_ptr->signals_received     =
			((unsigned long) tmp_rusage.ru_nsignals);
		rusage_ptr->vol_context_switch   =
			((unsigned long) tmp_rusage.ru_nvcsw);
		rusage_ptr->invol_context_switch =
			((unsigned long) tmp_rusage.ru_nivcsw);
		rusage_ptr->system_calls         = ULONG_MAX;
		rusage_ptr->chars_read_written   = ULONG_MAX;
	}

	return(return_code);
}
#endif /* #ifndef __MSDOS__ */
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_GetRUsageDelta

   SYNOPSIS    :	return_code = GEN_GetRUsageDelta(start_rusage_ptr,
							end_rusage_ptr, delta_rusage_ptr, error_text);

						int               return_code;

						const GEN_RUSAGE *start_rusage_ptr;

						const GEN_RUSAGE *end_rusage_ptr;

						GEN_RUSAGE       *delta_rusage_ptr;

						char             *error_text;

   DESCRIPTION :	Calculates the difference (or ``delta``) between two
						''GEN_RUSAGE'' structures.

						By determining the resource usage at the beginning of a
						section of code (with ``getrusage``) and after the section
						of code finishes, this function permits applications to
						determine the operating system resources needed to complete
						a task.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``start_rusage_ptr`` points to the ''GEN_RUSAGE''
						captured by the application at the start of the measurement
						period.

						(.) ``end_rusage_ptr`` points to the ''GEN_RUSAGE''
						captured by the application at the end of the measurement
						period.

						(-) If the ``end_rusage_ptr`` parameter is ''NULL'', this
						function will call ``GEN_GetRUsage`` and use the value
						which results as ``end_usage_ptr``.

						(.) ``delta_rusage_ptr`` points to the ''GEN_RUSAGE''
						into which this function is to place the delta calculated
						between ``start_rusage_ptr`` and ``end_rusage_ptr``.

						(-) It is permissible for ``start_rusage_ptr`` and
						``delta_rusage_ptr`` to point to the same ''GEN_RUSAGE''
						structure. In this case, each member of ``delta_rusage_ptr``
						will be zero.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_GetRUsage
						GEN_FormatRUsageList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_GetRUsageDelta
						Miscellaneous Functions:GEN_GetRUsageDelta
						GENFUNCS:Functions:GEN_GetRUsageDelta
						GENFUNCS:Miscellaneous Functions:GEN_GetRUsageDelta
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_GetRUsageDelta

   PUBLISH NAME:	GEN_GetRUsageDelta

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_GetRUsageDelta(const GEN_RUSAGE *start_rusage_ptr,
	const GEN_RUSAGE *end_rusage_ptr, GEN_RUSAGE *delta_rusage_ptr,
	char *error_text)
#else
int GEN_GetRUsageDelta(start_rusage_ptr, end_rusage_ptr, delta_rusage_ptr,
	error_text)
const GEN_RUSAGE *start_rusage_ptr;
const GEN_RUSAGE *end_rusage_ptr;
GEN_RUSAGE       *delta_rusage_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int                   return_code = GENFUNCS_SUCCESS;
	const struct timeval *timeval_ptr_1;
	const struct timeval *timeval_ptr_2;
	struct timeval       *timeval_ptr_3;
	const unsigned long  *u_long_ptr_1;
	const unsigned long  *u_long_ptr_2;
	unsigned long        *u_long_ptr_3;
	GEN_RUSAGE            tmp_rusage;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the programmer passed 'rusage_ptr' as 'NULL', get the usage	*/
	/*	information for this process . . .											*/
	/*	*****************************************************************	*/
	if (start_rusage_ptr == NULL) {
		strcpy(error_text, "Starting resource usage pointer is 'NULL'.");
		return_code = GENFUNCS_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (delta_rusage_ptr == NULL) {
		strcpy(error_text, "Delta resource usage pointer is 'NULL'.");
		return_code = GENFUNCS_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (end_rusage_ptr == NULL) {
#ifdef __MSDOS__
		memset(&tmp_rusage, '\0', sizeof(tmp_rusage));
#elif _Windows
		if ((return_code = GEN_GetRUsage(((int) GetCurrentProcess()),
			&tmp_rusage, error_text)) != GENFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
#elif __SVR4
		if ((return_code = GEN_GetRUsage(getpid(), &tmp_rusage,
			error_text)) != GENFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
#else
		if ((return_code = GEN_GetRUsage(RUSAGE_SELF, &tmp_rusage,
			error_text)) != GENFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
#endif /* #ifdef __MSDOS__ */
		end_rusage_ptr = ((const GEN_RUSAGE *) &tmp_rusage);
   }
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Get the usage time interval deltas . . .								*/
	/*	*****************************************************************	*/
	timeval_ptr_1 = GEN_RUSAGE_GET_FIRST_TIME_PTR(start_rusage_ptr);
	timeval_ptr_2 = GEN_RUSAGE_GET_FIRST_TIME_PTR(end_rusage_ptr);
	timeval_ptr_3 = GEN_RUSAGE_GET_FIRST_TIME_PTR(delta_rusage_ptr);
	while (timeval_ptr_1 <= GEN_RUSAGE_GET_LAST_TIME_PTR(start_rusage_ptr))
		GEN_GetABSInterval_timeval(timeval_ptr_1++, timeval_ptr_2++,
			timeval_ptr_3++);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Get the usage value deltas . . .											*/
	/*	*****************************************************************	*/
	u_long_ptr_1 = GEN_RUSAGE_GET_FIRST_VALUE_PTR(start_rusage_ptr);
	u_long_ptr_2 = GEN_RUSAGE_GET_FIRST_VALUE_PTR(end_rusage_ptr);
	u_long_ptr_3 = GEN_RUSAGE_GET_FIRST_VALUE_PTR(delta_rusage_ptr);
	while (u_long_ptr_1 <= GEN_RUSAGE_GET_LAST_VALUE_PTR(start_rusage_ptr)) {
		*u_long_ptr_3 = (*u_long_ptr_1 > *u_long_ptr_2) ?
			(*u_long_ptr_1 - *u_long_ptr_2) : ((*u_long_ptr_1 < *u_long_ptr_2) ?
			(*u_long_ptr_2 - *u_long_ptr_1) : 0L);
		u_long_ptr_1++;
		u_long_ptr_2++;
		u_long_ptr_3++;
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_FormatRUsageList

   SYNOPSIS    :	return_code = GEN_FormatRUsageList(rusage_ptr, text_width,
							null_format_type, rusage_count, rusage_list, error_text);

						int                 return_code;

						const GEN_RUSAGE   *rusage_ptr;

						unsigned int        text_width;

						int                 null_format_type;

						unsigned int       *rusage_count;

						char             ***rusage_list;

						char               *error_text;

   DESCRIPTION :	Formats the data in a ''GEN_RUSAGE'' structure as an
						array of human-readable strings.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``rusage_ptr`` points to the ''GEN_RUSAGE'' to
						be formatted.

						(-) If the ``rusage_ptr`` parameter is ''NULL'', this
						function will call ``GEN_GetRUsage`` and use the value
						which results as ``rusage_ptr``.

						(.) ``text_width`` is the maximum width of the usage
						descriptive text to be permitted.

						(-) If ``text_width`` is passed as ''0'', the function will
						use a default ``text_width`` of ''28'' characters.

						(.) ``null_format_type`` specifies the way the function is
						handle usage metrics which are not available within the
						current operating system. There are three different
						``null_format_types``:

						(..) ''GEN_RUSAGE_NULL_FORMAT_NONE'' specifies that usage
						metrics not available within the current operating system
						are not to be included in the list ``usage_list``.

						(..) ''GEN_RUSAGE_NULL_FORMAT_ZERO'' specifies that usage
						metrics not available within the current operating system
						are to be formatted with zeroes (''0'').

						(...) ''struct timeval'' members are formatted as:

						{---}           00:00:00.000000

						(...) ''unsigned long'' members are formatted as:

						{---}0000000000

						(..) ''GEN_RUSAGE_NULL_FORMAT_NULL'' specifies that usage
						metrics not available within the current operating system
						are to be formatted with question marks (''?'').

						(...) ''struct timeval'' members are formatted as:

						{---}           ??:??:??.??????

						(...) ''unsigned long'' members are formatted as:

						{---}??????????

						(-) If ``null_format_type`` is not one of
						''GEN_RUSAGE_NULL_FORMAT_NONE'',
						''GEN_RUSAGE_NULL_FORMAT_ZERO'', or
						''GEN_RUSAGE_NULL_FORMAT_NULL'', this function will use
						''GEN_RUSAGE_NULL_FORMAT_NULL''.

						(.) ``rusage_count`` is a pointer to an ''unsigned int''
						which will be updated to contain the number of elements in
						array ``rusage_list``.

						(.) ``rusage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place the lines
						representing from formatting ``rusage_ptr``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_GetRUsage
						GEN_GetRUsageDelta

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_FormatRUsageList
						Miscellaneous Functions:GEN_FormatRUsageList
						GENFUNCS:Functions:GEN_FormatRUsageList
						GENFUNCS:Miscellaneous Functions:GEN_FormatRUsageList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_FormatRUsageList

   PUBLISH NAME:	GEN_FormatRUsageList

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_FormatRUsageList(const GEN_RUSAGE *rusage_ptr, unsigned int text_width,
	int null_format_type, unsigned int *rusage_count, char ***rusage_list,
	char *error_text)
#else
int GEN_FormatRUsageList(rusage_ptr, text_width, null_format_type,
	rusage_count, rusage_list, error_text)
const GEN_RUSAGE   *rusage_ptr;
unsigned int        text_width;
int                 null_format_type;
unsigned int       *rusage_count;
char             ***rusage_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int                    return_code = GENFUNCS_SUCCESS;
	const struct timeval  *timeval_ptr;
	const unsigned long   *u_long_ptr;
	const char           **string_ptr;
	GEN_RUSAGE             tmp_rusage;
	char                   tmp_interval[128];
	char                  *buffer_ptr;
	char                   buffer[512];

	*rusage_count = 0;
	*rusage_list  = NULL;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Ensure that we've a buffer large enough for formatting . . .	*/
	/*	*****************************************************************	*/
	text_width = (!text_width) ? 28 : text_width;
	if (text_width < (sizeof(buffer) - 32))
		buffer_ptr = buffer;
	else if ((buffer_ptr = ((char *) calloc(text_width + 32, sizeof(char)))) ==
		NULL) {
		GEN_AllocMsgItem(text_width + 32, error_text,
			"Unable to allocate memory for the 'GEN_RUSAGE' formatting buffer");
		return_code = GENFUNCS_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the programmer passed 'rusage_ptr' as 'NULL', get the usage	*/
	/*	information for this process . . .											*/
	/*	*****************************************************************	*/
	if (rusage_ptr == NULL) {
#ifdef __MSDOS__
		memset(&tmp_rusage, '\0', sizeof(tmp_rusage));
#elif _Windows
		if ((return_code = GEN_GetRUsage(((int) GetCurrentProcess()),
			&tmp_rusage, error_text)) != GENFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
#elif __SVR4
		if ((return_code = GEN_GetRUsage(getpid(), &tmp_rusage,
			error_text)) != GENFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
#else
		if ((return_code = GEN_GetRUsage(RUSAGE_SELF, &tmp_rusage,
			error_text)) != GENFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
#endif /* #ifdef __MSDOS__ */
		rusage_ptr = ((const GEN_RUSAGE *) &tmp_rusage);
   }
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Format the usage time intervals . . .									*/
	/*	*****************************************************************	*/
	timeval_ptr = GEN_RUSAGE_GET_FIRST_TIME_PTR(rusage_ptr);
	string_ptr  = GEN_RUSAGE_TimeNameList;
	while (timeval_ptr <= GEN_RUSAGE_GET_LAST_TIME_PTR(rusage_ptr)) {
		sprintf(buffer_ptr, "%-*.*s: ", ((int) text_width), ((int) text_width),
			*string_ptr++);
		if ((((unsigned long) timeval_ptr->tv_sec) != ULONG_MAX) ||
			(((unsigned long) timeval_ptr->tv_usec) != ULONG_MAX))
			strcat(buffer_ptr,
				GEN_FormatInterval_timeval(timeval_ptr, tmp_interval));
		else if (null_format_type == GEN_RUSAGE_NULL_FORMAT_NONE) {
			timeval_ptr++;
			continue;
		}
		else if (null_format_type == GEN_RUSAGE_NULL_FORMAT_ZERO)
			strcat(buffer_ptr, "           00:00:00.000000");
		else
			strcat(buffer_ptr, "           ??:??:??.??????");
		timeval_ptr++;
		if (strl_append(rusage_count, rusage_list, buffer_ptr) !=
			STRFUNCS_SUCCESS) {
			strcpy(error_text,
				"Unable to allocate memory for the resource usage string list.");
			return_code = GENFUNCS_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Format the usage values . . .												*/
	/*	*****************************************************************	*/
	u_long_ptr = GEN_RUSAGE_GET_FIRST_VALUE_PTR(rusage_ptr);
	string_ptr = GEN_RUSAGE_ValueNameList;
	while (u_long_ptr <= GEN_RUSAGE_GET_LAST_VALUE_PTR(rusage_ptr)) {
		sprintf(buffer_ptr, "%-*.*s: ", ((int) text_width), ((int) text_width),
			*string_ptr++);
		if (*u_long_ptr != ULONG_MAX)
			sprintf(buffer_ptr + strlen(buffer_ptr), "%10lu", *u_long_ptr);
		else if (null_format_type == GEN_RUSAGE_NULL_FORMAT_NONE) {
			u_long_ptr++;
			continue;
		}
		else if (null_format_type == GEN_RUSAGE_NULL_FORMAT_ZERO)
			strcat(buffer_ptr, "0000000000");
		else
			strcat(buffer_ptr, "??????????");
		u_long_ptr++;
		if (strl_append(rusage_count, rusage_list, buffer_ptr) !=
			STRFUNCS_SUCCESS) {
			strcpy(error_text,
				"Unable to allocate memory for the resource usage string list.");
			return_code = GENFUNCS_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (buffer_ptr != buffer)
		free(buffer_ptr);

	if (return_code != GENFUNCS_SUCCESS)
		strl_remove_all(rusage_count, rusage_list);

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

COMPAT_FN_DECL_STATIC(int TEST_DoTheTest,
	(int null_format_type, char *error_text));

int main()
{
	int  return_code;
	char error_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'GEN_FormatRUsageList()'\n");
	fprintf(stderr, "---- ------- --- ------------------------\n\n");

	if ((return_code = TEST_DoTheTest(GEN_RUSAGE_NULL_FORMAT_NONE,
		error_text)) == GENFUNCS_SUCCESS) {
		if ((return_code = TEST_DoTheTest(GEN_RUSAGE_NULL_FORMAT_ZERO,
			error_text)) == GENFUNCS_SUCCESS)
			return_code = TEST_DoTheTest(GEN_RUSAGE_NULL_FORMAT_NULL,
				error_text);
	}

	if (return_code != GENFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#ifndef NARGS
static int TEST_DoTheTest(int null_format_type, char *error_text)
#else
static int TEST_DoTheTest(null_format_type, error_text)
int   null_format_type;
char *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = GENFUNCS_SUCCESS;
	unsigned int   count       = 0;
	char         **list        = NULL;

	if ((return_code = GEN_FormatRUsageList(NULL, 0, null_format_type,
		&count, &list, error_text)) == GENFUNCS_SUCCESS) {
		printf("===========================================================\n");
		printf("Test NULL Format Type: %s\n",
			(null_format_type == GEN_RUSAGE_NULL_FORMAT_NONE) ? "NONE" :
			(null_format_type == GEN_RUSAGE_NULL_FORMAT_ZERO) ? "ZERO" : "NULL");
		printf("---- ---- ------ ----  ----\n");
		while (count) {
			printf("%s\n", *list);
			strl_remove(&count, &list, 0, 1);
		}
		printf("===========================================================\n");
	}

	return(return_code);
}

#ifdef __MSDOS__
# ifndef NARGS
int getrusage(int who, struct rusage *rusage_ptr)
# else
int getrusage(who, rusage_ptr)
int            who;
struct rusage *rusage_ptr;
# endif /* #ifndef NARGS */
{
	memset(rusage_ptr, '\0', sizeof(*rusage_ptr));

	/* Use the parameter here . . . (stupid compilers) */
	return((who) ? 0 : who);
}
#endif /* #ifdef __MSDOS__ */

#endif /* #ifdef TEST_MAIN */

