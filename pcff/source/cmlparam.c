/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'PCFF_CFG' structures.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <string.h>

#include <datfuncs.h>
#include <npsl.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_LocateHelp(int argc, char **argv, const char **found_ptr)
{
	int return_code;

	if (argc <= 0)
		return_code = PCFF_FALSE;
	else if ((return_code = PCFF_CMLPARAM_FindUnordered(((unsigned int) argc) - 1,
		argv + 1, "-h", found_ptr)) != PCFF_TRUE)
		return_code = PCFF_CMLPARAM_FindUnordered(((unsigned int) argc) - 1,
			argv + 1, "-help", found_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_LocateVersion(int argc, char **argv, const char **found_ptr)
{
	int return_code;

	if (argc <= 0)
		return_code = PCFF_FALSE;
	else if ((return_code = PCFF_CMLPARAM_FindUnordered(((unsigned int) argc) - 1,
		argv + 1, "-v", found_ptr)) != PCFF_TRUE) {
		if ((return_code = PCFF_CMLPARAM_FindUnordered(((unsigned int) argc) - 1,
			argv + 1, "-ver", found_ptr)) != PCFF_TRUE)
			return_code = PCFF_CMLPARAM_FindUnordered(((unsigned int) argc) - 1,
				argv + 1, "-version", found_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int PCFF_CMLPARAM_FindVA(const char *arg_name, const char **found_ptr, ...)
#else
int PCFF_CMLPARAM_FindVA(const char *arg_name, const char **found_ptr, va_alist)
const char   *arg_name;
const char **found_ptr;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int         return_code = PCFF_FALSE;
	const char *this_string;
	va_list     argument_ptr;

	if (found_ptr != NULL)
		*found_ptr = NULL;

#ifndef NO_STDARGS
	va_start(argument_ptr, found_ptr);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	while ((this_string = va_arg(argument_ptr, const char *)) != NULL) {
		if (!stricmp(this_string, arg_name)) {
			if (found_ptr != NULL)
				*found_ptr = this_string;
			return_code = PCFF_TRUE;
			break;
		}
	}

	va_end(argument_ptr);


	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_FindOrdered(unsigned int param_count, char **param_list,
	const char *arg_name, const char **found_ptr)
{
	int          return_code;
	unsigned int found_index;

	if ((return_code = PCFF_CMLPARAM_FindOrderedIdx(param_count, param_list,
		arg_name, &found_index)) == PCFF_TRUE) {
		if (found_ptr != NULL)
			*found_ptr = param_list[found_index];
	}
	else if (found_ptr != NULL)
		*found_ptr = NULL;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_FindOrderedIdx(unsigned int param_count, char **param_list,
	const char *arg_name, unsigned int *found_index)
{
	return((strli_find(param_count, param_list, arg_name, found_index) ==
		STRFUNCS_ITEM_FOUND) ? PCFF_TRUE : PCFF_FALSE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_FindUnordered(unsigned int param_count, char **param_list,
	const char *arg_name, const char **found_ptr)
{
	int          return_code;
	unsigned int found_index;

	if ((return_code = PCFF_CMLPARAM_FindUnorderedIdx(param_count, param_list,
		arg_name, &found_index)) == PCFF_TRUE) {
		if (found_ptr != NULL)
			*found_ptr = param_list[found_index];
	}
	else if (found_ptr != NULL)
		*found_ptr = NULL;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_FindUnorderedIdx(unsigned int param_count, char **param_list,
	const char *arg_name, unsigned int *found_index)
{
	int          return_code = PCFF_FALSE;
	unsigned int count_1;

	for (count_1 = 0; count_1 < param_count; count_1++) {
		if (!stricmp(param_list[count_1], arg_name)) {
			if (found_index != NULL)
				*found_index = count_1;
			return_code = PCFF_TRUE;
			break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_FindTerminated(char **param_list, const char *arg_name,
	const char **found_ptr)
{
	int          return_code;
	unsigned int found_index;

	if ((return_code = PCFF_CMLPARAM_FindTerminatedIdx(param_list, arg_name,
		&found_index)) == PCFF_TRUE) {
		if (found_ptr != NULL)
			*found_ptr = param_list[found_index];
	}
	else if (found_ptr != NULL)
		*found_ptr = NULL;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_FindTerminatedIdx(char **param_list, const char *arg_name,
	unsigned int *found_index)
{
	int          return_code     = PCFF_FALSE;
	unsigned int tmp_found_index = 0;

	while (*param_list != NULL) {
		if (!stricmp(*param_list, arg_name)) {
			if (found_index != NULL)
				*found_index = tmp_found_index;
			return_code = PCFF_TRUE;
			break;
		}
		param_list++;
		tmp_found_index++;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_FindFollowing(int argc, char **argv, const char *param_name,
	PCFF_FLD_TYPE param_type, int required_flag, int is_multiple,
	unsigned int *found_index, char **out_ptr, char *error_text)
{
	int          return_code;
	unsigned int tmp_found_index;

	if (out_ptr != NULL)
		*out_ptr = NULL;

	found_index  = (found_index != NULL) ? found_index : &tmp_found_index;
	*found_index = 0;

	if (param_name == NULL) {
		if (error_text != NULL)
			strcpy(error_text, "The parameter name is 'NULL'.");
		return_code = PCFF_FAILURE;
	}
	else if (argc <= 0) {
		if (error_text != NULL)
			sprintf(error_text, "Invalid number of arguments (%d).", argc);
		return_code = PCFF_FAILURE;
	}
	else if (PCFF_CMLPARAM_FindUnorderedIdx(((unsigned int) argc) - 1, argv + 1,
		param_name, found_index) == PCFF_TRUE) {
		(*found_index)++;
		if ((return_code = PCFF_CMLPARAM_Check(argc, *found_index, argv,
			is_multiple, error_text)) == PCFF_SUCCESS)
			return_code = PCFF_CMLPARAM_GetParam(argv[*found_index],
				argv[*found_index + 1], param_type, out_ptr, error_text);
	}
	else if (!required_flag)
		return_code = PCFF_SUCCESS;
	else {
		if (error_text != NULL)
			strcat(nstrcat(strcpy(error_text, "Required parameter '"),
				param_name, PCFF_MAX_ERROR_TEXT - 100),
				"' not found in command line argument list.");
		return_code = PCFF_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_Check(int argc, unsigned int argv_index, char **argv,
	int is_multiple, char *error_text)
{
	int return_code = PCFF_SUCCESS;

	if (((return_code = PCFF_CMLPARAM_CheckFollowing(argc,
		argv_index, argv, error_text)) == PCFF_SUCCESS) && is_multiple)
		return_code = PCFF_CMLPARAM_IsMultiple(argv_index, argv, is_multiple,
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_CheckFollowing(int argc, unsigned int argv_index, char **argv,
	char *error_text)
{
	int return_code;

	if ((argc >= 0) && ((argv_index + 1) < ((unsigned int) argc)))
		return_code = PCFF_SUCCESS;
	else {
		if (error_text != NULL)
			strcat(nstrcat(strcpy(error_text,
				"Expected a command-line qualifier to follow the '"),
				argv[argv_index], PCFF_MAX_ERROR_TEXT - 100), "' parameter.");
		return_code = PCFF_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_IsMultiple(unsigned int argv_index, char **argv,
	int is_multiple, char *error_text)
{
	int return_code;

	if (!is_multiple)
		return_code = PCFF_SUCCESS;
	else {
		if (error_text != NULL)
			strcat(nstrcat(strcpy(error_text, "Multiple '"), argv[argv_index],
				PCFF_MAX_ERROR_TEXT - 100),
				"' parameters encountered on the command line.");
		return_code = PCFF_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_GetFollowing(int argc, unsigned int argv_index, char **argv,
	PCFF_FLD_TYPE param_type, int is_multiple, char **out_ptr, char *error_text)
{
	int return_code;

	if (out_ptr != NULL)
		*out_ptr = NULL;

	if ((return_code = PCFF_CMLPARAM_Check(argc, argv_index, argv, is_multiple,
		error_text)) == PCFF_SUCCESS)
		return_code = PCFF_CMLPARAM_GetParam(argv[argv_index],
			argv[argv_index + 1], param_type, out_ptr, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CMLPARAM_GetParam(const char *param_name, const char *param_value,
	PCFF_FLD_TYPE param_type, char **out_ptr, char *error_text)
{
	int           return_code = PCFF_SUCCESS;
	char         *tmp_string  = NULL;
	const char   *tmp_param_value;
	NPSL_HOSTENT  hostent_data;
	char          hostent_buffer[8192];
	char          str_error_text[STRFUNCS_MAX_ERROR_TEXT];
	char          datf_error_text[DATFUNCS_MAX_ERROR_TEXT];
	char          gen_error_text[GENFUNCS_MAX_ERROR_TEXT];
	char          npsl_error_text[NPSL_MAX_ERROR_TEXT];
	char          tmp_error_text[PCFF_MAX_ERROR_TEXT];

	if (out_ptr != NULL)
		*out_ptr = NULL;

	if (param_name == NULL) {
		if (error_text != NULL)
			strcpy(error_text, "The parameter name is 'NULL'.");
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (param_value == NULL) {
		if (error_text != NULL)
			strcpy(error_text, "The parameter value is 'NULL'.");
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}

	tmp_param_value = param_value;

	switch (param_type) {
		case PCFF_FLD_TYPE_NONE				:
			sprintf(tmp_error_text, "%s (%d = '%s') encountered.",
				"Unset parameter field type", param_type,
				PCFF_GET_FLD_TYPE_NAME(param_type));
			return_code = PCFF_FAILURE;
			break;
		case PCFF_FLD_TYPE_SCHAR			:
			if ((return_code = STR_CheckValueSCharString(param_value,
				str_error_text)) != STRFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_UCHAR			:
			if ((return_code = STR_CheckValueUCharString(param_value,
				str_error_text)) != STRFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_SSHORT			:
			if ((return_code = STR_CheckValueSShortString(param_value,
				str_error_text)) != STRFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_USHORT			:
			if ((return_code = STR_CheckValueUShortString(param_value,
				str_error_text)) != STRFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_SINT				:
			if ((return_code = STR_CheckValueSIntString(param_value,
				str_error_text)) != STRFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_UINT				:
			if ((return_code = STR_CheckValueUIntString(param_value,
				str_error_text)) != STRFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_SLONG			:
			if ((return_code = STR_CheckValueSLongString(param_value,
				str_error_text)) != STRFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_ULONG			:
			if ((return_code = STR_CheckValueULongString(param_value,
				str_error_text)) != STRFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_FLOAT			:
			if ((return_code = STR_CheckValueFloatString(param_value, NULL,
				str_error_text)) != STRFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_DOUBLE			:
			if ((return_code = STR_CheckValueDoubleString(param_value, NULL,
				str_error_text)) != STRFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_BOOLEAN			:
			if ((!stricmp(param_value, "ON"))   ||
				 (!stricmp(param_value, "YES"))  ||
				 (!stricmp(param_value, "TRUE")) ||
				 (!stricmp(param_value, "T"))    ||
				 (!stricmp(param_value, "Y"))    ||
				 (!stricmp(param_value, "1")))
				tmp_param_value = "TRUE";
			else if ((!stricmp(param_value, "OFF")) ||
				 (!stricmp(param_value, "NO"))       ||
				 (!stricmp(param_value, "FALSE"))    ||
				 (!stricmp(param_value, "F"))        ||
				 (!stricmp(param_value, "N"))        ||
				 (!stricmp(param_value, "0")))
				tmp_param_value = "FALSE";
			else {
				sprintf(tmp_error_text,
					"Invalid Boolean value ('%-.500s') --- %s %s, %s.",
					param_value, "expected one of",
					"'YES', 'NO', 'TRUE', 'FALSE', 'ON', 'OFF', 'T', 'F'",
					"'Y', 'N', '1', or '0'");
				return_code = PCFF_FAILURE;
			}
			break;
		case PCFF_FLD_TYPE_IP_HSP			:
			if (NPSL_ResolveHostServProtoString(param_value, NULL, NULL, NULL,
				npsl_error_text) != NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			break;
		case PCFF_FLD_TYPE_IP_PHS			:
			if (NPSL_ResolveProtoHostServString(param_value, NULL, NULL, NULL,
				npsl_error_text) != NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			break;
		case PCFF_FLD_TYPE_STRING			:
		case PCFF_FLD_TYPE_STRING_PTR		:
			break;
		case PCFF_FLD_TYPE_DATE_STR		:
			if ((return_code = DATFUNCS_CheckCanonicalDate(param_value,
				datf_error_text)) != DATFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, datf_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_DAT(return_code);
			break;
		case PCFF_FLD_TYPE_TIME_STR		:
			if ((return_code = DATFUNCS_CheckCanonicalTime(param_value,
				datf_error_text)) != DATFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, datf_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_DAT(return_code);
			break;
		case PCFF_FLD_TYPE_TIMEVAL_STR	:
			if ((return_code = DATFUNCS_CheckCanonicalTimeVal(param_value,
				datf_error_text)) != DATFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, datf_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_DAT(return_code);
			break;
		case PCFF_FLD_TYPE_TIMESPEC_STR	:
			if ((return_code = DATFUNCS_CheckCanonicalTimeSpec(param_value,
				datf_error_text)) != DATFUNCS_SUCCESS)
				nstrcpy(tmp_error_text, datf_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_DAT(return_code);
			break;
		case PCFF_FLD_TYPE_PATH_NAME		:
		case PCFF_FLD_TYPE_PATH_NAME_PTR	:
			if (GEN_ExpandToFullPathName(param_value, &tmp_string,
				gen_error_text) != GENFUNCS_SUCCESS) {
				nstrcpy(tmp_error_text, gen_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			break;
		case PCFF_FLD_TYPE_FILE_NAME		:
		case PCFF_FLD_TYPE_FILE_NAME_PTR	:
			sprintf(tmp_error_text, "%s (%d = '%s') encountered.",
				"Unsupported command line parameter field type", param_type,
				PCFF_GET_FLD_TYPE_NAME(param_type));
			return_code = PCFF_FAILURE;
			break;
		case PCFF_FLD_TYPE_HOST_SPEC		:
		case PCFF_FLD_TYPE_HOST_SPEC_PTR	:
			if (NPSL_GetHostByString(param_value, &hostent_data, hostent_buffer,
				sizeof(hostent_buffer), npsl_error_text) != NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			else if ((out_ptr != NULL) &&
				((tmp_string = strdup(hostent_data.h_name)) == NULL)) {
				STR_AllocMsgItem(strlen(hostent_data.h_name) + 1, tmp_error_text,
					"Unable to allocate memory for a copy of the field");
				return_code = PCFF_MEMORY_FAILURE;
			}
			break;
		case PCFF_FLD_TYPE_SERVICE			:
		case PCFF_FLD_TYPE_SERVICE_PTR	:
			if (NPSL_ResolveServToPort(param_value, NULL, NULL,
				npsl_error_text) != NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			break;
		case PCFF_FLD_TYPE_PROTOCOL		:
		case PCFF_FLD_TYPE_PROTOCOL_PTR	:
			if (NPSL_ResolveProtoToSint(param_value, NULL,
				npsl_error_text) != NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			break;
		default									:
			sprintf(tmp_error_text, "Invalid field type encountered (%d).",
				param_type);
			return_code = PCFF_FAILURE;
			break;
	}

	if ((return_code == PCFF_SUCCESS) && (out_ptr != NULL)) {
		if (tmp_string != NULL) {
			*out_ptr   = tmp_string;
			tmp_string = NULL;
		}
		else if ((*out_ptr = strdup(tmp_param_value)) == NULL) {
			STR_AllocMsgItem(strlen(tmp_param_value) + 1, tmp_error_text,
				"Unable to allocate memory for a copy of the field");
			return_code = PCFF_MEMORY_FAILURE;
		}
	}

	if ((return_code != PCFF_SUCCESS) && (error_text != NULL))
		nstrcat(strcat(nstrcat(strcat(nstrcat(strcpy(error_text,
			"Error occurred parsing data for command line parameter name '"),
			param_name, 255), "', parameter value '"), param_value, 255), "': "),
			tmp_error_text, PCFF_MAX_ERROR_TEXT - (100 + 255 + 255));

EXIT_FUNCTION:

	if (tmp_string != NULL)
		free(tmp_string);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Test data . . .																			*/
/*	***********************************************************************	*/
static char          *PCCF_TEST_HelpList_1[]     =
	{ "program-name", "-A", "-B", "-h", "-C" };
static int            PCCF_TEST_HelpCount_1      =
	sizeof(PCCF_TEST_HelpList_1) / sizeof(PCCF_TEST_HelpList_1[0]);
	/*	*****************************************************************	*/
static char          *PCCF_TEST_HelpList_2[]     =
	{ "program-name", "-A", "-B", "-help", "-C" };
static int            PCCF_TEST_HelpCount_2      =
	sizeof(PCCF_TEST_HelpList_2) / sizeof(PCCF_TEST_HelpList_2[0]);
	/*	*****************************************************************	*/
static char          *PCCF_TEST_OrderedList[]    =
	{ "-A", "-B", "-Find-Me", "-Z" };
static unsigned int   PCCF_TEST_OrderedCount     =
	sizeof(PCCF_TEST_OrderedList) / sizeof(PCCF_TEST_OrderedList[0]);
	/*	*****************************************************************	*/
static char          *PCCF_TEST_UnorderedList[]  =
	{ "-X", "-Y", "-Find-Me", "-Z" };
static unsigned int   PCCF_TEST_UnorderedCount   =
	sizeof(PCCF_TEST_UnorderedList) / sizeof(PCCF_TEST_UnorderedList[0]);
	/*	*****************************************************************	*/
static char          *PCCF_TEST_TerminatedList[] =
	{ "-X", "-Y", "-Find-Me", "-Z", NULL };
	/*	*****************************************************************	*/
typedef struct {
	char          *param_name;
	PCFF_FLD_TYPE  param_type;
} TEST_GET_SPEC;
static TEST_GET_SPEC  PCCF_TEST_FollowSpecList[] = {
	{	"-schar-1",						PCFF_FLD_TYPE_SCHAR				},
	{	"-schar-2",						PCFF_FLD_TYPE_SCHAR				},
	{	"-uchar",						PCFF_FLD_TYPE_UCHAR				},
	{	"-sshrt-1",						PCFF_FLD_TYPE_SSHORT				},
	{	"-sshrt-2",						PCFF_FLD_TYPE_SSHORT				},
	{	"-ushrt",						PCFF_FLD_TYPE_USHORT				},
	{	"-sint-1",						PCFF_FLD_TYPE_SINT				},
	{	"-sint-2",						PCFF_FLD_TYPE_SINT				},
	{	"-uint",							PCFF_FLD_TYPE_UINT				},
	{	"-slong-1",						PCFF_FLD_TYPE_SLONG				},
	{	"-slong-2",						PCFF_FLD_TYPE_SLONG				},
	{	"-ulong",						PCFF_FLD_TYPE_ULONG				},
	{	"-float",						PCFF_FLD_TYPE_FLOAT				},
	{	"-double",						PCFF_FLD_TYPE_DOUBLE				},
	{	"-boolean-1",					PCFF_FLD_TYPE_BOOLEAN			},
	{	"-boolean-2",					PCFF_FLD_TYPE_BOOLEAN			},
	{	"-ip-host-serv-proto-1",	PCFF_FLD_TYPE_IP_HSP				},
	{	"-ip-host-serv-proto-2",	PCFF_FLD_TYPE_IP_HSP				},
	{	"-ip-proto-host-serv-1",	PCFF_FLD_TYPE_IP_PHS				},
	{	"-ip-proto-host-serv-2",	PCFF_FLD_TYPE_IP_PHS				},
	{	"-string",						PCFF_FLD_TYPE_STRING				},
	{	"-date-string",				PCFF_FLD_TYPE_DATE_STR			},
	{	"-time-string",				PCFF_FLD_TYPE_TIME_STR			},
	{	"-timeval-string",			PCFF_FLD_TYPE_TIMEVAL_STR		},
	{	"-timespec-string",			PCFF_FLD_TYPE_TIMESPEC_STR		},
	{	"-path-name-1",				PCFF_FLD_TYPE_PATH_NAME			},
	{	"-path-name-2",				PCFF_FLD_TYPE_PATH_NAME			},
	{	"-host-spec",					PCFF_FLD_TYPE_HOST_SPEC			},
	{	"-ip-service-1",				PCFF_FLD_TYPE_SERVICE			},
	{	"-ip-service-2",				PCFF_FLD_TYPE_SERVICE			},
	{	"-ip-protocol-1",				PCFF_FLD_TYPE_PROTOCOL			},
	{	"-ip-protocol-2",				PCFF_FLD_TYPE_PROTOCOL			}
};
static unsigned int   PCCF_TEST_FollowSpecCount  =
	sizeof(PCCF_TEST_FollowSpecList) / sizeof(PCCF_TEST_FollowSpecList[0]);
static char          *PCCF_TEST_FollowDataList[] = {
	"program-name",
	"-schar-1",						"-127",
	"-schar-2",						"127",
	"-uchar",						"255",
	"-sshrt-1",						"-32768",
	"-sshrt-2",						"32767",
	"-ushrt",						"65535",
#ifdef __MSDOS__
	"-sint-1",						"-32768",
	"-sint-2",						"32767",
	"-uint",							"65535",
#else
	"-sint-1",						"-2147483648",
	"-sint-2",						"2147483647",
	"-uint",							"4294967295",
#endif /* #ifdef __MSDOS__ */
	"-slong-1",						"-2147483648",
	"-slong-2",						"2147483647",
	"-ulong",						"4294967295",
	"-float",						"12345678901.12",
	"-double",						"12345678901.12",
	"-boolean-1",					"True",
	"-boolean-2",					"False",
	"-ip-host-serv-proto-1",	"localhost:ftp",
	"-ip-host-serv-proto-2",	"localhost:ftp:tcp",
	"-ip-proto-host-serv-1",	"tcp:localhost",
	"-ip-proto-host-serv-2",	"tcp:localhost:ftp",
	"-string",						"An-arbitrary-string",
	"-date-string",				"2002-01-28",
	"-time-string",				"12:34:56",
	"-timeval-string",			"2002-01-28 12:34:56.123456",
	"-timespec-string",			"2002-01-28 12:34:56.123456789",
#ifdef __MSDOS__
	"-path-name-1",				"\\",
#elif _Windows
	"-path-name-1",				"\\",
#else
	"-path-name-1",				"/",
#endif /* #ifdef __MSDOS__ */
	"-path-name-2",				".",
	"-host-spec",					"localhost",
	"-ip-service-1",				"ftp",
	"-ip-service-2",				"21",
	"-ip-protocol-1",				"tcp",
	"-ip-protocol-2",				"6"
};
static int           PCCF_TEST_FollowDataCount  =
	sizeof(PCCF_TEST_FollowDataList) / sizeof(PCCF_TEST_FollowDataList[0]);
/*	***********************************************************************	*/

COMPAT_FN_DECL(int main, (void));

/*	***********************************************************************	*/
int main()
{
	int           return_code = PCFF_SUCCESS;
	char         *param_ptr   = NULL;
	const char   *found_ptr;
	unsigned int  found_index;
	unsigned int  count_1;
	char          error_text[PCFF_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test harness for function 'PCFF_CMLPARAM_LocateHelp()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_LocateVersion()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_FindVA()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_FindOrdered()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_FindOrderedIdx()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_FindUnordered()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_FindUnorderedIdx()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_FindTerminated()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_FindTerminatedIdx()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_Check()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_CheckFollowing()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_IsMultiple()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_GetFollowing()'\n");
	fprintf(stderr,
		"                          'PCFF_CMLPARAM_GetParam()'\n");
	fprintf(stderr,
		"---- ------- --- -------- -----------------------------------\n\n");

	*error_text = '\0';

	/*	*****************************************************************
		*****************************************************************
		Test function 'PCFF_CMLPARAM_LocateHelp()' . . .
		*****************************************************************	*/
	printf("PCFF_CMLPARAM_LocateHelp    :");
	if (PCFF_CMLPARAM_LocateHelp(PCCF_TEST_HelpCount_1,
		PCCF_TEST_HelpList_1, &found_ptr) == PCFF_TRUE)
		printf("SUCCEEDED: Help request found [%s]\n", found_ptr);
	else {
		printf("FAILED   : Help request not found []\n");
		return_code = PCFF_FAILURE;
	}
	printf("PCFF_CMLPARAM_LocateHelp    :");
	if (PCFF_CMLPARAM_LocateHelp(PCCF_TEST_HelpCount_2,
		PCCF_TEST_HelpList_2, &found_ptr) == PCFF_TRUE)
		printf("SUCCEEDED: Help request found [%s]\n", found_ptr);
	else {
		printf("FAILED   : Help request not found []\n");
		return_code = PCFF_FAILURE;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Test function 'PCFF_CMLPARAM_LocateVersion()' . . .
		*****************************************************************	*/
	printf("PCFF_CMLPARAM_LocateVersion :");
	if (PCFF_CMLPARAM_LocateVersion(PCCF_TEST_HelpCount_1,
		PCCF_TEST_HelpList_1, &found_ptr) != PCFF_TRUE)
		printf("SUCCEEDED: Version request not found (expected) []\n");
	else {
		printf("FAILED   : Version request found (unexpected) [%s]\n", found_ptr);
		return_code = PCFF_FAILURE;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Test function 'PCFF_CMLPARAM_FindVA()' . . .
		*****************************************************************	*/
	printf("PCFF_CMLPARAM_FindVA        :");
	if (PCFF_CMLPARAM_FindVA("-find-me", &found_ptr, "-A", "-B", "-Find-Me",
		"-D", "-E", NULL) == PCFF_TRUE)
		printf("SUCCEEDED: Parameter found [%s]\n", found_ptr);
	else {
		printf("FAILED   : Parameter not found []\n");
		return_code = PCFF_FAILURE;
	}
	printf("PCFF_CMLPARAM_FindVA        :");
	if (PCFF_CMLPARAM_FindVA("-dont-find-me", &found_ptr, "-A", "-B", "-Find-Me",
		"-D", "-E", NULL) != PCFF_TRUE)
		printf("SUCCEEDED: Parameter not found (expected) []\n");
	else {
		printf("FAILED   : Parameter found (unexpected) [%s]\n", found_ptr);
		return_code = PCFF_FAILURE;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Test function 'PCFF_CMLPARAM_FindOrdered()' . . .
		*****************************************************************	*/
	printf("PCFF_CMLPARAM_FindOrdered   :");
	if (PCFF_CMLPARAM_FindOrdered(PCCF_TEST_OrderedCount, PCCF_TEST_OrderedList,
		"-find-me", &found_ptr) == PCFF_TRUE)
		printf("SUCCEEDED: Parameter found [%s]\n", found_ptr);
	else {
		printf("FAILED   : Parameter not found []\n");
		return_code = PCFF_FAILURE;
	}
	printf("PCFF_CMLPARAM_FindOrdered   :");
	if (PCFF_CMLPARAM_FindOrdered(PCCF_TEST_OrderedCount, PCCF_TEST_OrderedList,
		"-dont-find-me", &found_ptr) != PCFF_TRUE)
		printf("SUCCEEDED: Parameter not found (expected) []\n");
	else {
		printf("FAILED   : Parameter found (unexpected) [%s]\n", found_ptr);
		return_code = PCFF_FAILURE;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Test function 'PCFF_CMLPARAM_FindUnordered()' . . .
		*****************************************************************	*/
	printf("PCFF_CMLPARAM_FindUnordered :");
	if (PCFF_CMLPARAM_FindUnordered(PCCF_TEST_UnorderedCount,
		PCCF_TEST_UnorderedList, "-find-me", &found_ptr) == PCFF_TRUE)
		printf("SUCCEEDED: Parameter found [%s]\n", found_ptr);
	else {
		printf("FAILED   : Parameter not found []\n");
		return_code = PCFF_FAILURE;
	}
	printf("PCFF_CMLPARAM_FindUnordered :");
	if (PCFF_CMLPARAM_FindUnordered(PCCF_TEST_UnorderedCount,
		PCCF_TEST_UnorderedList, "-dont-find-me", &found_ptr) != PCFF_TRUE)
		printf("SUCCEEDED: Parameter not found (expected) []\n");
	else {
		printf("FAILED   : Parameter found (unexpected) [%s]\n", found_ptr);
		return_code = PCFF_FAILURE;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Test function 'PCFF_CMLPARAM_FindTerminated()' . . .
		*****************************************************************	*/
	printf("PCFF_CMLPARAM_FindTerminated:");
	if (PCFF_CMLPARAM_FindTerminated(PCCF_TEST_TerminatedList, "-find-me",
		&found_ptr) == PCFF_TRUE)
		printf("SUCCEEDED: Parameter found [%s]\n", found_ptr);
	else {
		printf("FAILED   : Parameter not found []\n");
		return_code = PCFF_FAILURE;
	}
	printf("PCFF_CMLPARAM_FindTerminated:");
	if (PCFF_CMLPARAM_FindTerminated(PCCF_TEST_TerminatedList, "-dont-find-me",
		&found_ptr) != PCFF_TRUE)
		printf("SUCCEEDED: Parameter not found (expected) []\n");
	else {
		printf("FAILED   : Parameter found (unexpected) [%s]\n", found_ptr);
		return_code = PCFF_FAILURE;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Test function 'PCFF_CMLPARAM_GetFollowing()' . . .
		*****************************************************************	*/
	for (count_1 = 0; count_1 < PCCF_TEST_FollowSpecCount; count_1++) {
		printf("PCFF_CMLPARAM_GetFollowing  :");
		if (PCFF_CMLPARAM_FindFollowing(PCCF_TEST_FollowDataCount,
			PCCF_TEST_FollowDataList, PCCF_TEST_FollowSpecList[count_1].param_name,
			PCCF_TEST_FollowSpecList[count_1].param_type, PCFF_TRUE, PCFF_FALSE,
			&found_index, &param_ptr, error_text) == PCFF_SUCCESS) {
			printf("SUCCEEDED: Parameter found [%s=%s=%s]\n",
				PCCF_TEST_FollowDataList[found_index],
				PCCF_TEST_FollowDataList[found_index + 1], param_ptr);
			free(param_ptr);
		}
		else {
			printf("FAILED   : Parameter parsing error [%s]: %s\n",
				PCCF_TEST_FollowSpecList[count_1].param_name, error_text);
			return_code = PCFF_FAILURE;
		}
	}
	/*	*****************************************************************	*/

	if (return_code != PCFF_SUCCESS)
		fprintf(stderr, "\n\nERROR: One or more regression tests failed.\n\n");

	return(return_code);
}
/*	***********************************************************************	*/
#endif /* #ifdef TEST_MAIN */


