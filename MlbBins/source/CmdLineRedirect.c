/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Proxy forwarding to exceute the PV command.

	Revision History	:	2002-10-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2002 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <Windows.h>

/*	***********************************************************************	*/

#define RUNPV_FILE_NAME_BASE				"CmdLineRedirect"

static int  MakeFileNames(const char *argv_0, char **file_name_cfg,
	char **file_name_log, char *error_text);
static int  AllocFileName(char **file_name, const char *src_name,
	unsigned int src_length, const char *text_name, const char *ext_name,
	char *error_text);
static int  GetFileArgs(const char *file_name_cfg, char **system_cmd,
	char *error_text);
static void LogResults(const char *file_name_log, int error_code,
	int system_code, const char *text);
static void EmitResultsLine(FILE *file_ptr, const char *time_buffer,
	int error_code, int system_code, const char *text);

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int   return_code = EXIT_SUCCESS;
	char *file_name_cfg;
	char *file_name_log;
	char *system_cmd;
	char  error_text[1023 + 1];

	if ((return_code = MakeFileNames(argv[0], &file_name_cfg, &file_name_log,
		error_text)) == EXIT_SUCCESS) {
		if ((return_code = GetFileArgs(file_name_cfg, &system_cmd,
			error_text)) == EXIT_SUCCESS) {
			return_code = system(system_cmd);
			LogResults(file_name_log, 0, return_code, system_cmd);
			free(system_cmd);
		}
		else
			LogResults(file_name_log, return_code, 0, error_text);
		free(file_name_cfg);
		free(file_name_log);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int MakeFileNames(const char *argv_0, char **file_name_cfg,
	char **file_name_log, char *error_text)
{
	unsigned int  return_code;
	const char   *ptr_0;
	unsigned int  len_0;

	*file_name_cfg = NULL;
	*file_name_log = NULL;

	argv_0 = ((ptr_0 = strrchr(argv_0, ':'))  != NULL) ? (ptr_0 + 1) : argv_0;
	argv_0 = ((ptr_0 = strrchr(argv_0, '\\')) != NULL) ? (ptr_0 + 1) : argv_0;
	argv_0 = ((ptr_0 = strrchr(argv_0, '/'))  != NULL) ? (ptr_0 + 1) : argv_0;

	len_0  = ((ptr_0 = strchr(argv_0, '.')) == NULL) ? strlen(argv_0) :
		(((unsigned int) ptr_0) - ((unsigned int) argv_0));

	if ((return_code = AllocFileName(file_name_cfg, argv_0, len_0,
		"configuration", "cfg", error_text)) == EXIT_SUCCESS) {
		if ((return_code = AllocFileName(file_name_log, argv_0, len_0, "log",
			"log", error_text)) != EXIT_SUCCESS)
			free(file_name_cfg);
			file_name_cfg = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int AllocFileName(char **file_name, const char *src_name,
	unsigned int src_length, const char *text_name, const char *ext_name,
	char *error_text)
{
	int          return_code;
	unsigned int total_len;

	total_len = strlen(RUNPV_FILE_NAME_BASE) + 1 + src_length + 1 +
		strlen(ext_name) + 1;

	if ((*file_name = ((char *) calloc(total_len, sizeof(char)))) != NULL) {
		sprintf(*file_name, "%s.%.*s.%s", RUNPV_FILE_NAME_BASE,
			src_length, src_name, ext_name);
		return_code = EXIT_SUCCESS;
	}
	else {
		sprintf(error_text, "%s %u bytes for the %s file name.",
			"Unable to allocate", total_len, text_name);
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int GetFileArgs(const char *file_name_cfg, char **system_cmd,
	char *error_text)
{
	int            return_code = EXIT_SUCCESS;
	unsigned long  file_size;
	unsigned int   buffer_length;
	unsigned int   actual_count;
	char          *tmp_ptr;
	FILE          *file_ptr;

	*system_cmd = NULL;

	if ((file_ptr = fopen(file_name_cfg, "rb")) != NULL) {
		fseek(file_ptr, 0L, SEEK_END);
		file_size = ftell(file_ptr);
		fseek(file_ptr, 0L, SEEK_SET);
		buffer_length = ((unsigned int) file_size) + 1;
		if ((*system_cmd = ((char *) calloc(buffer_length, sizeof(char)))) !=
			NULL) {
			if ((actual_count = fread(*system_cmd, sizeof(char),
				((unsigned int) file_size), file_ptr)) ==
				((unsigned int) file_size)) {
				if ((tmp_ptr = strchr(*system_cmd, '\n')) != NULL)
					*tmp_ptr = '\0';
				if ((tmp_ptr = strchr(*system_cmd, '\r')) != NULL)
					*tmp_ptr = '\0';
			}
			else {
				sprintf(error_text,
					"%s %u bytes out of %u total bytes from the file '%-.500s'.",
					"Read only", actual_count, buffer_length - 1,
					file_name_cfg);
				free(*system_cmd);
				*system_cmd = NULL;
				return_code = EXIT_FAILURE;
			}
		}
		else {
			sprintf(error_text, "%s %u bytes for the file '%-.500s'.",
				"Unable to allocate", buffer_length, file_name_cfg);
			return_code = EXIT_FAILURE;
		}
		fclose(file_ptr);
	}
	else {
		sprintf(error_text, "%s '%-.500s' for reading.",
			"Unable to open the file", file_name_cfg);
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void LogResults(const char *file_name_log, int error_code,
	int system_code, const char *text)
{
	FILE      *file_ptr;
	time_t     current_time;
	struct tm  tm_data;
	char       time_buffer[127 + 1];

	current_time = time(NULL);

#ifdef _Windows
	tm_data = *localtime(&current_time);
#else
# if defined(__EXTENSIONS__) || defined(_REENTRANT) || defined(_POSIX_C_SOURCE)
	localtime_r(&current_time, tm_data);
# else
	tm_data = *localtime(&current_time);
# endif /* #if defined(__EXTENSIONS__ || _REENTRANT || _POSIX_C_SOURCE) */
#endif /* #ifdef _Windows */
	
	strftime(time_buffer, sizeof(time_buffer) - 1, "%Y-%m-%d %H:%M:%S",
		&tm_data);

	EmitResultsLine(stderr, time_buffer, error_code, system_code, text);

	if ((file_ptr = fopen(file_name_log, "a")) != NULL) {
		EmitResultsLine(file_ptr, time_buffer, error_code, system_code, text);
		fclose(file_ptr);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void EmitResultsLine(FILE *file_ptr, const char *time_buffer,
	int error_code, int system_code, const char *text)
{
	fprintf(file_ptr, "%s %11d ", time_buffer, error_code);

	if (!error_code)
		fprintf(file_ptr, "%11d system(\"%s\")\n", system_code, text);
	else
		fprintf(file_ptr, "%11.11s %s\n", "N/A", text);
}
/*	***********************************************************************	*/


