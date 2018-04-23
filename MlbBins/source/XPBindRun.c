/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Runs a Windows process with a specified processor
								affinity.

	Revision History	:	2002-01-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2002 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <strfuncs.h>

#ifdef _Windows
#include <Windows.h>
#include <Psapi.h>
typedef DWORD XPBINDRUN_CPU_MASK;
#else
typedef unsigned int XPBINDRUN_CPU_MASK;
#endif /* #ifdef _Windows */

/*	*********************************************************************** */
int  XPBINDRUN_GetCPUMaskSystem(XPBINDRUN_CPU_MASK *out_mask, char *error_text);
int  XPBINDRUN_GetCPUMaskProcess(HANDLE process_handle,
	XPBINDRUN_CPU_MASK *out_mask, char *error_text);
int  XPBINDRUN_GetCPUMaskBoth(HANDLE process_handle,
	XPBINDRUN_CPU_MASK *system_mask, XPBINDRUN_CPU_MASK *process_mask,
	char *error_text);
int  XPBINDRUN_SetCPUMaskProcess(HANDLE process_handle,
	XPBINDRUN_CPU_MASK process_mask, char *error_text);
int  XPBINDRUN_CreateProcess(unsigned int argc, char **argv, char *error_text);
void XPBINDRUN_AppendString(const char *in_string, char *out_string);
/*	*********************************************************************** */

/*	*********************************************************************** */
/*
	xpbindrun <processor-spec> <dir-spec> <executable-name> [ <args> ]

		<processor-spec> = { CPU-mask | ALL | SINGLE }
		<dir-spec>       = { <directory-name> | CURRENT }
*/

int main(int argc, char **argv)
{
	int                return_code = EXIT_SUCCESS;
	unsigned int       count_1;
	XPBINDRUN_CPU_MASK sys_mask;
	XPBINDRUN_CPU_MASK new_mask;
	XPBINDRUN_CPU_MASK this_bit;
	char               bad_bits_1[STR_VAL2STR_MAX_LEN + 1];
	char               bad_bits_2[STR_VAL2STR_MAX_LEN + 1];
	char               error_text[4095 + 1];

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-help")) ||
			(!stricmp(argv[count_1], "-h"))) {
			fprintf(stderr, "\n\nUSAGE:\n   %s %s %s %s [ %s ... ]\n\n",
				argv[0],
				"<processor-spec>",
				"<directory-spec>",
				"<executable-name>",
				"<arguments>");
			fprintf(stderr, "WHERE:\n%s\n\n",
"\
   <processor-spec>     = { CPU-mask | ALL | SINGLE }\n\
      o <CPU-mask> is a numeric value the bits of which represents the CPUs\n\
        which are to be used by <executable-name> when it is started.\n\
      o ALL indicates that all available CPUs are to be used.\n\
      o SINGLE indicates that one CPU, chosen at random by this program, is\n\
        to be used.\n\n\
   <directory-spec>     = { <directory-name> | CURRENT }\n\
      o If CURRENT, the current directory of this program will be used.\n\n\
   <executable-name>    = The full path to the program to be run.\n\n\
   [ <arguments> ... ]  = Optional arguments to be passed to <executable-name>.");
			goto EXIT_FUNCTION;
		}
	}

	if ((return_code = XPBINDRUN_GetCPUMaskSystem(&sys_mask, error_text)) !=
		EXIT_SUCCESS)
		goto EXIT_FUNCTION;
	else if (!sys_mask) {
		sprintf(error_text,
			"The current system CPU mask is zero (0) --- fatal error.");
		return_code = EXIT_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (argc < 4) {
		sprintf(error_text, "Invalid command line ---  use '-h' for help");
		return_code = EXIT_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (str_digit(argv[1], 0) == NULL) {
		new_mask = ((XPBINDRUN_CPU_MASK) atoi(argv[1]));
		if (!new_mask) {
			sprintf(error_text,
				"Invalid <processor-spec> parameter ('%.500s') --- %s.",
				argv[1], "evaluates to zero (0).");
			return_code = EXIT_FAILURE;
			goto EXIT_FUNCTION;
		}
		else if (new_mask & (~sys_mask)) {
			sprintf(error_text, "%s ('%.500s' = \
(%lu DEC = 0x%0lx HEX = %s BIN) %s (%lu DEC = 0x%0lx HEX = %s BIN).",
				"Invalid <processor-spec> parameter", argv[1],
				new_mask, new_mask, val2str(new_mask, 0, 2, "0", bad_bits_1),
				"includes CPUs not present in the system affinity mask",
				sys_mask, sys_mask, val2str(sys_mask, 0, 2, "0", bad_bits_2));
			return_code = EXIT_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	else if (!stricmp(argv[1], "ALL"))
		new_mask = sys_mask;
	else if (!stricmp(argv[1], "SINGLE")) {
		srand(time(NULL));
		do {
			this_bit = 1 << (rand() % (sizeof(XPBINDRUN_CPU_MASK) * CHAR_BIT));
			new_mask = (sys_mask & this_bit) ? this_bit : 0;
		} while (!new_mask);
	}
	else {
		sprintf(error_text, "Invalid <processor-spec> parameter ('%.500s').",
			argv[1]);
		return_code = EXIT_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = XPBINDRUN_SetCPUMaskProcess(GetCurrentProcess(),
		new_mask, error_text)) == EXIT_SUCCESS)
		return_code = XPBINDRUN_CreateProcess(((unsigned int) argc), argv,
			error_text);

EXIT_FUNCTION:

	if (return_code != EXIT_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}
/*	*********************************************************************** */

/*	*********************************************************************** */
int XPBINDRUN_GetCPUMaskSystem(XPBINDRUN_CPU_MASK *out_mask, char *error_text)
{
#ifdef _Windows
	return(XPBINDRUN_GetCPUMaskBoth(GetCurrentProcess(), out_mask, NULL,
		error_text));
#else
	if (error_text != NULL)
		sprintf(error_text, "Function '%s()' not supported for this OS.",
			"XPBINDRUN_GetSystemProcessorMask");
	return(EXIT_FAILURE);
#endif /* #ifdef _Windows */
}
/*	*********************************************************************** */

/*	*********************************************************************** */
int XPBINDRUN_GetCPUMaskProcess(HANDLE process_handle,
	XPBINDRUN_CPU_MASK *out_mask, char *error_text)
{
#ifdef _Windows
	return(XPBINDRUN_GetCPUMaskBoth(process_handle, NULL, out_mask, error_text));
#else
	if (error_text != NULL)
		sprintf(error_text, "Function '%s()' not supported for this OS.",
			"XPBINDRUN_GetSystemProcessorMask");
	return(EXIT_FAILURE);
#endif /* #ifdef _Windows */
}
/*	*********************************************************************** */

/*	*********************************************************************** */
int XPBINDRUN_GetCPUMaskBoth(HANDLE process_handle,
	XPBINDRUN_CPU_MASK *system_mask, XPBINDRUN_CPU_MASK *process_mask,
	char *error_text)
{
	int   return_code = EXIT_SUCCESS;
#ifdef _Windows
	DWORD proc_aff_mask;
	DWORD sys_aff_mask;

	if (GetProcessAffinityMask(process_handle, &proc_aff_mask,
		&sys_aff_mask) != 0) {
		if (system_mask != NULL)
			*system_mask = sys_aff_mask;
		if (process_mask != NULL)
			*process_mask = proc_aff_mask;
	}
	else {
		if (error_text != NULL)
			sprintf(error_text, "Call to '%s(%u, 0x%p, 0x%p)' failed: %s = %d.",
				"GetProcessAffinityMask", process_handle, &proc_aff_mask,
				&sys_aff_mask, "GetLastError()", GetLastError());
		return_code = EXIT_FAILURE;
	}
#else
	if (error_text != NULL)
		sprintf(error_text, "Function '%s()' not supported for this OS.",
			"XPBINDRUN_GetCPUMaskBoth");
	return_code = EXIT_FAILURE;
#endif /* #ifdef _Windows */

	return(return_code);
}
/*	*********************************************************************** */

/*	*********************************************************************** */
int XPBINDRUN_SetCPUMaskProcess(HANDLE process_handle,
	XPBINDRUN_CPU_MASK process_mask, char *error_text)
{
	int   return_code = EXIT_SUCCESS;
#ifdef _Windows
	if (SetProcessAffinityMask(process_handle, process_mask) == 0) {
		if (error_text != NULL)
			sprintf(error_text, "Call to '%s(0x%0lx, 0x%0lx)' failed: %s = %d.",
				"SetProcessAffinityMask", process_handle, process_mask,
				"GetLastError()", GetLastError());
		return_code = EXIT_FAILURE;
	}
#else
	if (error_text != NULL)
		sprintf(error_text, "Function '%s()' not supported for this OS.",
			"XPBINDRUN_SetCPUMaskProcess");
	return_code = EXIT_FAILURE;
#endif /* #ifdef _Windows */

	return(return_code);
}
/*	*********************************************************************** */

//	xpbindrun <processor-spec> <dir-spec> <executable-name> [ <args> ]
/*	*********************************************************************** */
int XPBINDRUN_CreateProcess(unsigned int argc, char **argv, char *error_text)
{
	int                  return_code = EXIT_SUCCESS;
	char                *cmd_params  = NULL;
	unsigned int         cmd_params_length;
	const char          *cmd_path;
	unsigned int         count_1;
	STARTUPINFO          start_up_info;
	PROCESS_INFORMATION  process_info;

	cmd_params_length = 1 + strlen(argv[3]) + (charcnt('\"', argv[3]) * 2) + 1 +
		((argc - 4) + 1);
	for (count_1 = 4; count_1 < argc; count_1++)
		cmd_params_length += 1 + strlen(argv[count_1]) +
			(charcnt('\"', argv[count_1]) * 2) + 1;

	cmd_path = (!stricmp(argv[2], "CURRENT")) ? NULL : argv[2];

	if ((cmd_params = ((char *) calloc(cmd_params_length,
		sizeof(char)))) == NULL) {
		if (error_text != NULL)
			sprintf(error_text, "Unable to allocate %u bytes of memory.",
				cmd_params_length);
		return_code = EXIT_FAILURE;
	}
	else {
		XPBINDRUN_AppendString(argv[3], cmd_params);
		for (count_1 = 4; count_1 < argc; count_1++)
			XPBINDRUN_AppendString(argv[count_1], cmd_params);
		memset(&start_up_info, '\0', sizeof(start_up_info));
		memset(&process_info, '\0', sizeof(process_info));
		if (!CreateProcess(argv[3], cmd_params, NULL, NULL, 0,
			NORMAL_PRIORITY_CLASS, NULL, argv[2], &start_up_info, &process_info)) {
			sprintf(error_text, "Call to '%s(\"%s\", \"%s\", NULL, NULL, 0, \
NORMAL_PRIORITY_CLASS, NULL, %s, 0x%0lx, 0x%0lx)' failed: %s = %d.",
				"CreateProcess", argv[3], cmd_params, argv[2], &start_up_info,
				&process_info, "GetLastError()", GetLastError());
			return_code = EXIT_FAILURE;
		}
		free(cmd_params);
	}

	return(return_code);
}
/*	*********************************************************************** */

/*	*********************************************************************** */
void XPBINDRUN_AppendString(const char *in_string, char *out_string)
{
	const char *tmp_ptr_1;
	char       *tmp_ptr_2;

	strcat(out_string, (*out_string) ? " \"" : "\"");

	if (!charcnt('\"', in_string))
		strcat(strcat(out_string, in_string), "\"");
	else {
		tmp_ptr_1 = in_string;
		tmp_ptr_2 = out_string + strlen(out_string);
		while (*tmp_ptr_1) {
			if (*tmp_ptr_1 == '\"') {
				*tmp_ptr_2++ = '\\';
				*tmp_ptr_2++ = '\"';
			}
			else
				*tmp_ptr_2++ = *tmp_ptr_1;
			tmp_ptr_1++;
		}
		*tmp_ptr_2++ = '\"';					// Was calloc'ed --- has ASCII NUL.
	}
}
/*	*********************************************************************** */

