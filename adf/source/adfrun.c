/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1995-07-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "adfrun.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_RUN_OpenLogFile(ADF_CONTROL *control_ptr, char *error_text)
#else
int ADF_RUN_OpenLogFile(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code = ADF_SUCCESS;
	char *sep_char_ptr;
	char  buffer[4096];
	char  gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

#ifdef __MSDOS__
	sprintf(buffer, "%s%sADF_LOG.LOG", (control_ptr->log_dir == NULL) ? "" :
		control_ptr->log_dir, (control_ptr->log_dir == NULL) ? "" : "\\",
		control_ptr->log_dir);
#else
	char time_buffer[100];
	SDTIF_Format_time_t(&control_ptr->start_time.tv_sec, time_buffer);
	time_buffer[10] = '.';
# ifdef _Windows
	time_buffer[13] = '.';
   time_buffer[16] = '.';
# endif /* # ifdef _Windows */

	if ((control_ptr->log_dir == NULL) &&
		((return_code = GEN_ExpandToFullPathName("",
      &control_ptr->log_dir, gen_error_text)) != GENFUNCS_SUCCESS)) {
		nstrcat(strcpy(error_text,
			"Unable to copy the default log file directory name ('.'): "),
			gen_error_text, ADF_MAX_ERROR_TEXT - 100);
		return_code = ADF_MAP_ERROR_GEN(return_code);
	}
	else
#ifdef _MSC_VER
		/*
			To avoid MSC version 6.0 warning C4701:
				local variable 'sep_char_ptr' may be used without having been initialized
			. . . stupid compiler doesn't pick up the initialization in trenary operator.
*/
		sep_char_ptr = "";
#endif /* # ifdef _MSC_VER */
		sep_char_ptr =
			((control_ptr->log_dir[strlen(control_ptr->log_dir) - 1] == '/') ||
			 (control_ptr->log_dir[strlen(control_ptr->log_dir) - 1] == '\\')) ?
			"" : "/";
		sprintf(buffer, "%s%s%s.ADF_LOG.%s.%u", control_ptr->log_dir,
			sep_char_ptr, time_buffer, control_ptr->host_name,
			control_ptr->process_id);
#endif /* #ifdef __MSDOS__ */

	if (return_code == ADF_SUCCESS) {
		if ((control_ptr->log_file_name = strdup(buffer)) == NULL) {
			strcpy(error_text, "Unable to copy the name of the log file.");
			return_code = ADF_MEMORY_FAILURE;
		}
		else if ((control_ptr->mlog_ptr =
			MLOG_FOpenDefault(control_ptr->log_file_name)) == NULL) {
			sprintf(error_text, "%s '%-.500s' for writing --- ",
				"Unable to open the log file", control_ptr->log_file_name);
			ADF_GetLastErrorString(error_text);
			return_code = ADF_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_RUN_GetParamsInit(ADF_CONTROL *control_ptr, unsigned int argc,
	char **argv, ADF_RUN_EndFunc end_func, char *error_text)
#else
int ADF_RUN_GetParamsInit(control_ptr, argc, argv, end_func, error_text)
ADF_CONTROL      *control_ptr;
unsigned int      argc;
char            **argv;
ADF_RUN_EndFunc   end_func;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code;
	const char *prog;
	char        gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	ADF_INIT_Control(control_ptr);

	if (!argc) {
		strcpy(error_text, "No command-line arguments passed to program.");
		return_code = ADF_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

#ifndef NARGS
	GEN_SIGNAL_SignalInit(&control_ptr->signal_received_flag,
		&control_ptr->queue_signal_flag, control_ptr, NULL, NULL,
      ((void (*)(void *, int, int *, const char *)) end_func));
#else
	GEN_SIGNAL_SignalInit(&control_ptr->signal_received_flag,
		&control_ptr->queue_signal_flag, control_ptr, NULL, NULL, end_func);
#endif /* #ifndef NARGS */
	GEN_SIGNAL_SignalSet();

	SDTIF_GetTimeUSecs(&control_ptr->start_time);

	control_ptr->overhead_end_time = control_ptr->start_time;

	control_ptr->process_id        = GEN_GetProcessID();

	if (setlocale(LC_ALL, "C") == NULL) {
		strcpy(error_text, "Attempt to 'setlocale(LC_ALL, \"C\")' failed.");
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = GEN_SetResourceLimitsToMax(gen_error_text)) !=
		GENFUNCS_SUCCESS) {
		nstrcpy(error_text, gen_error_text, ADF_MAX_ERROR_TEXT);
		return_code = ADF_MAP_ERROR_GEN(return_code);
		goto EXIT_FUNCTION;
	}

	if ((control_ptr->program_name = strdup(argv[0])) == NULL) {
		sprintf(error_text,
			"Unable to allocate memory for the program name.");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

   if (GEN_GetHostName(control_ptr->host_name,
		sizeof(control_ptr->host_name) - 1)) {
		strcpy(error_text, "Unable to determine the current host-name: ");
		ADF_GetLastErrorString(error_text);
		return_code = ADF_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = GEN_DetermineCurrentDir(control_ptr->current_dir,
		gen_error_text)) != GENFUNCS_SUCCESS) {
		nstrcpy(error_text, gen_error_text, ADF_MAX_ERROR_TEXT);
		return_code = ADF_MAP_ERROR_GEN(return_code);
		goto EXIT_FUNCTION;
	}

	prog = control_ptr->program_name;
	/* For Unix */
	prog = (strrchr(prog, '/')  != NULL) ? (strrchr(prog, '/')  + 1) : prog;
	/* For VMS */
	prog = (strrchr(prog, ']')  != NULL) ? (strrchr(prog, ']')  + 1) : prog;
	/* For MS-DOS */
	prog = (strrchr(prog, ':')  != NULL) ? (strrchr(prog, ':')  + 1) : prog;
	/* For MS-DOS */
	prog = (strrchr(prog, '\\') != NULL) ? (strrchr(prog, '\\') + 1) : prog;

	if ((control_ptr->short_program_name = strdup(prog)) == NULL) {
		sprintf(error_text, "%s (%u bytes required).",
			"Unable to allocate memory for the short program name",
			strlen(argv[0]) + 1);
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_RUN_EndStart(ADF_CONTROL *control_ptr, const char *message_buffer)
#else
void ADF_RUN_EndStart(control_ptr, message_buffer)
ADF_CONTROL *control_ptr;
const char  *message_buffer;
#endif /* #ifndef NARGS */
{
	unsigned long  total_usecs;
	struct timeval overhead_interval;
	struct timeval total_interval;

	control_ptr->shut_down_flag = GENFUNCS_TRUE;

	/*	**************************************************************
		**************************************************************
		Get the end time of the program . . .
		**************************************************************	*/
	SDTIF_GetTimeUSecs(&control_ptr->end_time);
	/*	**************************************************************	*/

	/*	**************************************************************
		**************************************************************
		Inform the user that we're bailing out . . .
		**************************************************************	*/
	if (MLOG_Check(control_ptr->mlog_ptr, NULL)) {
		MLOG_DoSepEqual(control_ptr->mlog_ptr);
		if ((message_buffer != NULL) && *message_buffer)
			MLOG_LogInfo(control_ptr->mlog_ptr, "%s", message_buffer);
		MLOG_LogInfo(control_ptr->mlog_ptr, "Exiting . . .\n");
	}
	else if (MLOG_GetFlagFile(control_ptr->mlog_ptr) &&
		(control_ptr->help_flag != ADF_TRUE) &&
		(control_ptr->version_flag != ADF_TRUE) &&
		(control_ptr->quiet_flag != ADF_TRUE))
		fprintf(stderr, "Exiting . . .\n");
	/*	**************************************************************	*/

	/*	**************************************************************
		**************************************************************
		Calculate the total time and overhead time used . . .
		**************************************************************	*/
	total_usecs            = ((unsigned long)
		(SDTIF_GET_TIMEVAL_USECS_DOUBLE(&control_ptr->end_time) -
		SDTIF_GET_TIMEVAL_USECS_DOUBLE(&control_ptr->start_time)));
	total_interval.tv_sec  = ((long) total_usecs) / 1000000L;
	total_interval.tv_usec = ((long) total_usecs) % 1000000L;
	if (control_ptr->overhead_end_time.tv_sec ||
		control_ptr->overhead_end_time.tv_usec) {
		total_usecs               = ((unsigned long)
			(SDTIF_GET_TIMEVAL_USECS_DOUBLE(&control_ptr->overhead_end_time) -
			SDTIF_GET_TIMEVAL_USECS_DOUBLE(&control_ptr->start_time)));
		overhead_interval.tv_sec  = ((long) total_usecs) / 1000000L;
		overhead_interval.tv_usec = ((long) total_usecs) % 1000000L;
	}
	else {
		overhead_interval.tv_sec  = 0L;
		overhead_interval.tv_usec = 0L;
	}
	/*	**************************************************************	*/

	/*	**************************************************************
		**************************************************************
		Show timing statistics . . .
		**************************************************************	*/
	MLOG_DoExecTime(control_ptr->mlog_ptr, &control_ptr->start_time,
		&control_ptr->end_time, &control_ptr->overhead_end_time);
	/*	**************************************************************	*/

	/*	**************************************************************
		**************************************************************
		Show system resource usage . . .
		**************************************************************	*/
	MLOG_DoRUsage(control_ptr->mlog_ptr);
	/*	**************************************************************	*/
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_RUN_EndFinish(ADF_CONTROL *control_ptr)
#else
void ADF_RUN_EndFinish(control_ptr)
ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	/*	**************************************************************
		**************************************************************
		Free the memory allocated to store the program name . . .
		**************************************************************	*/
	if (control_ptr->program_name != NULL) {
		free(control_ptr->program_name);
		control_ptr->program_name = NULL;
	}
	/*	**************************************************************	*/

	/*	**************************************************************
		**************************************************************
		Close the log file (if open) and free-up any memory which
		associated with it . . .
		**************************************************************	*/
	if (MLOG_Check(control_ptr->mlog_ptr, NULL) == MLOG_SUCCESS) {
		MLOG_LogInfo(control_ptr->mlog_ptr, "Closing the log file '%s'.\n",
			control_ptr->log_file_name);
		MLOG_DoSepEnd(control_ptr->mlog_ptr);
		MLOG_Close(control_ptr->mlog_ptr, NULL);
		control_ptr->mlog_ptr = NULL;
	}
	if (control_ptr->log_dir != NULL) {
		free(control_ptr->log_dir);
		control_ptr->log_dir = NULL;
	}
	if (control_ptr->log_file_name != NULL) {
		free(control_ptr->log_file_name);
		control_ptr->log_file_name = NULL;
	}
	/*	**************************************************************	*/

	ADF_FREE_Control(control_ptr);
}
/*	***********************************************************************	*/

