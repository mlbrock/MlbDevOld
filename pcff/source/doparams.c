/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes structure members from configuration
								parameters.

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

#include <strfuncs.h>
#include <datfuncs.h>
#include <genfuncs.h>
#include <npsl.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions private to this module . . .			*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int PCFF_GetParam,
	(const PCFF_CFG *cfg_ptr, PCFF_FLAG flags,
	const PCFF_PARAM_SPEC *param_spec_ptr, const PCFF_PARAM *param_ptr,
	void *out_data_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int PCFF_AllocateHostServProto,
	(int phs_flag, const char *spec_string, const char *host_name,
	int service_number, int protocol_number, PCFF_IP_HSP *out_ip_hsp,
	char *error_text));
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_DoParams(const PCFF_CFG *cfg_ptr, PCFF_FLAG flags,
	const PCFF_PARAM_SPEC *param_spec_ptr, void *out_data_ptr,
	char *error_text)
{
	int          return_code = PCFF_SUCCESS;
	unsigned int count_1;

	for (count_1 = 0; count_1 < param_spec_ptr->param_count; count_1++) {
		if ((return_code = PCFF_GetParam(cfg_ptr, flags, param_spec_ptr,
			param_spec_ptr->param_list + count_1, out_data_ptr,
			error_text)) != PCFF_SUCCESS)
			break;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
static int PCFF_GetParam(const PCFF_CFG *cfg_ptr, PCFF_FLAG flags,
	const PCFF_PARAM_SPEC *param_spec_ptr, const PCFF_PARAM *param_ptr,
	void *out_data_ptr, char *error_text)
{
	int               return_code = PCFF_SUCCESS;
	void             *out_ptr;
	unsigned int      tmp_length;
	char             *tmp_string_1;
	char             *tmp_string_2;
	const char       *in_value;
	const char       *ref_value;
	const PCFF_PARAM *ref_param_ptr;
	const PCFF_ITEM  *item_ptr;
	NPSL_HOSTENT      hostent_data;
	char              hostent_buffer[8192];
	char              host_name[NPSL_MAX_HOST_NAME_LEN + 1];
	int            	service_number;
	int               protocol_number;
	char              str_error_text[STRFUNCS_MAX_ERROR_TEXT];
	char              datf_error_text[DATFUNCS_MAX_ERROR_TEXT];
	char              gen_error_text[GENFUNCS_MAX_ERROR_TEXT];
	char              npsl_error_text[NPSL_MAX_ERROR_TEXT];
	char              tmp_error_text[PCFF_MAX_ERROR_TEXT];

	if ((item_ptr = PCFF_FindItem(cfg_ptr, param_ptr->param_name, NULL)) ==
		NULL)
		goto EXIT_FUNCTION;

	in_value = item_ptr->value;
	out_ptr  = ((char *) out_data_ptr) + param_ptr->field_offset;

	switch (param_ptr->field_type) {
		case PCFF_FLD_TYPE_NONE				:
			sprintf(tmp_error_text, "%s (%d = '%s') encountered.",
				"Unset parameter field type", param_ptr->field_type,
				PCFF_GET_FLD_TYPE_NAME(param_ptr->field_type));
			return_code = PCFF_FAILURE;
			break;
		case PCFF_FLD_TYPE_SCHAR			:
			if ((return_code = STR_CheckValueSCharString(in_value,
				str_error_text)) == STRFUNCS_SUCCESS)
				*((signed char *) out_ptr) = ((signed char) atof(in_value));
			else
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_UCHAR			:
			if ((return_code = STR_CheckValueUCharString(in_value,
				str_error_text)) == STRFUNCS_SUCCESS)
				*((unsigned char *) out_ptr) = ((unsigned char) atof(in_value));
			else
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_SSHORT			:
			if ((return_code = STR_CheckValueSShortString(in_value,
				str_error_text)) == STRFUNCS_SUCCESS)
				*((signed short *) out_ptr) = ((signed short) atof(in_value));
			else
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_USHORT			:
			if ((return_code = STR_CheckValueUShortString(in_value,
				str_error_text)) == STRFUNCS_SUCCESS)
				*((unsigned short *) out_ptr) = ((unsigned short) atof(in_value));
			else
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_SINT				:
			if ((return_code = STR_CheckValueSIntString(in_value,
				str_error_text)) == STRFUNCS_SUCCESS)
				*((signed int *) out_ptr) = ((signed int) atof(in_value));
			else
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_UINT				:
			if ((return_code = STR_CheckValueUIntString(in_value,
				str_error_text)) == STRFUNCS_SUCCESS)
				*((unsigned int *) out_ptr) = ((unsigned int) atof(in_value));
			else
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_SLONG			:
			if ((return_code = STR_CheckValueSLongString(in_value,
				str_error_text)) == STRFUNCS_SUCCESS)
				*((signed long *) out_ptr) = ((signed long) atof(in_value));
			else
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_ULONG			:
			if ((return_code = STR_CheckValueULongString(in_value,
				str_error_text)) == STRFUNCS_SUCCESS)
				*((unsigned long *) out_ptr) = ((unsigned long) atof(in_value));
			else
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_FLOAT			:
			if ((return_code = STR_CheckValueFloatString(in_value, NULL,
				str_error_text)) == STRFUNCS_SUCCESS)
				*((float *) out_ptr) = ((float) atof(in_value));
			else
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_DOUBLE			:
			if ((return_code = STR_CheckValueDoubleString(in_value, NULL,
				str_error_text)) == STRFUNCS_SUCCESS)
				*((double *) out_ptr) = ((double) atof(in_value));
			else
				nstrcpy(tmp_error_text, str_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_STR(return_code);
			break;
		case PCFF_FLD_TYPE_BOOLEAN			:
			if ((!stricmp(in_value, "ON"))   ||
				 (!stricmp(in_value, "YES"))  ||
				 (!stricmp(in_value, "TRUE")) ||
				 (!stricmp(in_value, "T"))    ||
				 (!stricmp(in_value, "Y"))    ||
				 (!stricmp(in_value, "1")))
				*((int *) out_ptr) = PCFF_TRUE;
			else if ((!stricmp(in_value, "OFF")) ||
				 (!stricmp(in_value, "NO"))        ||
				 (!stricmp(in_value, "FALSE"))     ||
				 (!stricmp(in_value, "F"))         ||
				 (!stricmp(in_value, "N"))         ||
				 (!stricmp(in_value, "0")))
				*((int *) out_ptr) = PCFF_FALSE;
			else {
				sprintf(tmp_error_text,
					"Invalid Boolean value ('%-.500s') --- %s %s, %s.",
					in_value, "expected one of",
					"'YES', 'NO', 'TRUE', 'FALSE', 'ON', 'OFF', 'T', 'F'",
					"'Y', 'N', '1', or '0'");
				return_code = PCFF_FAILURE;
			}
			break;
		case PCFF_FLD_TYPE_IP_HSP			:
			if (NPSL_ResolveHostServProtoString(in_value, host_name,
				&service_number, &protocol_number, npsl_error_text) !=
				NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			else
				return_code = PCFF_AllocateHostServProto(PCFF_FALSE, in_value,
					host_name, service_number, protocol_number,
					((PCFF_IP_HSP *) out_ptr), tmp_error_text);
			break;
		case PCFF_FLD_TYPE_IP_PHS			:
			if (NPSL_ResolveProtoHostServString(in_value, host_name,
				&service_number, &protocol_number, npsl_error_text) !=
				NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			else
				return_code = PCFF_AllocateHostServProto(PCFF_TRUE, in_value,
					host_name, service_number, protocol_number,
					((PCFF_IP_HSP *) out_ptr), tmp_error_text);
			break;
		case PCFF_FLD_TYPE_STRING			:
			if (((tmp_length = strlen(in_value)) >= param_ptr->field_length) &&
				(!(flags & PCFF_FLAG_STR_TRUNC))) {
				sprintf(tmp_error_text, "%s (%u) %s (%u).",
					"The length of the field value", tmp_length,
					"exceeds the maximum length permitted for this field",
					param_ptr->field_length - 1);
				return_code = PCFF_FAILURE;
			}
			else if (param_ptr->domain_count && (*in_value == '\0') &&
				(flags & PCFF_FLAG_DOMAIN_NULL))
				strcpy(((char *) out_ptr), in_value);
			else if (param_ptr->domain_count &&
				(!(flags & PCFF_FLAG_DOMAIN_BAD)) &&
				(strli_find(param_ptr->domain_count, param_ptr->domain_list,
				in_value, NULL) != STRFUNCS_ITEM_FOUND)) {
				sprintf(tmp_error_text, "The string value '%-.500s' %s.",
					in_value, "is not among the valid values for this field");
				return_code = PCFF_FAILURE;
			}
			else
				nstrcpy(((char *) out_ptr), in_value, param_ptr->field_length - 1);
			break;
		case PCFF_FLD_TYPE_STRING_PTR		:
			if (in_value != NULL) {
				if (param_ptr->domain_count &&
					(!(flags & PCFF_FLAG_DOMAIN_BAD)) &&
					(strli_find(param_ptr->domain_count,
					param_ptr->domain_list, in_value, NULL) !=
					STRFUNCS_ITEM_FOUND)) {
					sprintf(tmp_error_text, "The string value '%-.500s' %s.",
						in_value, "is not among the valid values for this field");
					return_code = PCFF_FAILURE;
				}
				else if ((*((char **) out_ptr) = strdup(in_value)) == NULL) {
					STR_AllocMsgItem(strlen(in_value) + 1, tmp_error_text,
						"Unable to allocate memory for a copy of the field");
					return_code = PCFF_MEMORY_FAILURE;
				}
			}
			break;
		case PCFF_FLD_TYPE_DATE_STR		:
			if (*in_value && ((return_code = DATFUNCS_CheckCanonicalDate(in_value,
				datf_error_text)) == DATFUNCS_SUCCESS))
				strcpy(((char *) out_ptr), in_value);
			else
				nstrcpy(tmp_error_text, datf_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_DAT(return_code);
			break;
		case PCFF_FLD_TYPE_TIME_STR		:
			if (*in_value && ((return_code = DATFUNCS_CheckCanonicalTime(in_value,
				datf_error_text)) == DATFUNCS_SUCCESS))
				strcpy(((char *) out_ptr), in_value);
			else
				nstrcpy(tmp_error_text, datf_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_DAT(return_code);
			break;
		case PCFF_FLD_TYPE_TIMEVAL_STR	:
			if (*in_value &&
				((return_code = DATFUNCS_CheckCanonicalTimeVal(in_value,
				datf_error_text)) == DATFUNCS_SUCCESS))
				strcpy(((char *) out_ptr), in_value);
			else
				nstrcpy(tmp_error_text, datf_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_DAT(return_code);
			break;
		case PCFF_FLD_TYPE_TIMESPEC_STR	:
			if (*in_value &&
				((return_code = DATFUNCS_CheckCanonicalTimeSpec(in_value,
				datf_error_text)) == DATFUNCS_SUCCESS))
				strcpy(((char *) out_ptr), in_value);
			else
				nstrcpy(tmp_error_text, datf_error_text, PCFF_MAX_ERROR_TEXT - 1);
			return_code = PCFF_MAP_ERROR_DAT(return_code);
			break;
		case PCFF_FLD_TYPE_PATH_NAME		:
			if (GEN_ExpandToFullPathName(in_value, &tmp_string_1,
				gen_error_text) != GENFUNCS_SUCCESS) {
				nstrcpy(tmp_error_text, gen_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			else {
				if (((tmp_length = strlen(tmp_string_1)) >=
					param_ptr->field_length) && (!(flags & PCFF_FLAG_STR_TRUNC))) {
					sprintf(tmp_error_text, "%s (%u) %s (%u).",
						"The length of the field value", tmp_length,
						"exceeds the maximum length permitted for this field",
						param_ptr->field_length - 1);
					return_code = PCFF_FAILURE;
				}
				else
					nstrcpy(((char *) out_ptr), tmp_string_1,
						param_ptr->field_length - 1);
				free(tmp_string_1);
			}
			break;
		case PCFF_FLD_TYPE_PATH_NAME_PTR	:
			if (GEN_ExpandToFullPathName(in_value, &tmp_string_1,
				gen_error_text) != GENFUNCS_SUCCESS) {
				nstrcpy(tmp_error_text, gen_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			else
				*((char **) out_ptr) = tmp_string_1;
			break;
		case PCFF_FLD_TYPE_FILE_NAME		:
		case PCFF_FLD_TYPE_FILE_NAME_PTR	:
			ref_param_ptr = param_spec_ptr->param_list + param_ptr->ref_index;
			ref_value     = (!PCFF_FLD_TYPE_IS_PTR(ref_param_ptr->field_type)) ?
				(((char *) out_data_ptr) + ref_param_ptr->field_offset) :
				*((char **) ((void **) ((void *)
				(((char *) out_data_ptr) + ref_param_ptr->field_offset))));
			ref_value     = (ref_value != NULL) ? ref_value : "";
			ref_value     = (*ref_value) ? ref_value : ".";
			tmp_length    = strlen(ref_value) + 1 + strlen(in_value) + 1;
			if ((tmp_string_1 = ((char *) calloc(tmp_length, sizeof(char)))) ==
				NULL) {
				STR_AllocMsgItem(tmp_length, tmp_error_text,
					"Unable to allocate memory for a temporary copy of the field");
				return_code = PCFF_MEMORY_FAILURE;
			}
			else {
				strcat(chrcat(strcpy(tmp_string_1, ref_value), GEN_DirSlash),
					in_value);
				if (GEN_ExpandToFullPathName(tmp_string_1, &tmp_string_2,
					gen_error_text) != GENFUNCS_SUCCESS) {
					nstrcpy(tmp_error_text, gen_error_text, PCFF_MAX_ERROR_TEXT - 1);
					return_code = PCFF_FAILURE;
				}
				else if (PCFF_FLD_TYPE_IS_PTR(param_ptr->field_type))
					*((char **) out_ptr) = tmp_string_2;
				else {
					if (((tmp_length = strlen(tmp_string_2)) >=
						param_ptr->field_length) &&
						(!(flags & PCFF_FLAG_STR_TRUNC))) {
						sprintf(tmp_error_text, "%s (%u) %s (%u).",
							"The length of the field value", tmp_length,
							"exceeds the maximum length permitted for this field",
							param_ptr->field_length - 1);
						return_code = PCFF_FAILURE;
					}
					else
						nstrcpy(((char *) out_ptr), tmp_string_2,
							param_ptr->field_length - 1);
					free(tmp_string_2);
				}
				free(tmp_string_1);
			}
			break;
		case PCFF_FLD_TYPE_HOST_SPEC		:
			if (NPSL_GetHostByString(in_value, &hostent_data, hostent_buffer,
				sizeof(hostent_buffer), npsl_error_text) != NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			else if (((tmp_length = strlen(hostent_data.h_name)) >=
				param_ptr->field_length) && (!(flags & PCFF_FLAG_STR_TRUNC))) {
				sprintf(tmp_error_text, "%s (%u) %s (%u).",
					"The length of the field value", tmp_length,
					"exceeds the maximum length permitted for this field",
					param_ptr->field_length - 1);
				return_code = PCFF_FAILURE;
			}
			else
				nstrcpy(((char *) out_ptr), hostent_data.h_name,
					param_ptr->field_length - 1);
			break;
		case PCFF_FLD_TYPE_HOST_SPEC_PTR	:
			if (NPSL_GetHostByString(in_value, &hostent_data, hostent_buffer,
				sizeof(hostent_buffer), npsl_error_text) != NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			else if ((*((char **) out_ptr) = strdup(hostent_data.h_name)) ==
				NULL) {
				STR_AllocMsgItem(strlen(hostent_data.h_name) + 1, tmp_error_text,
					"Unable to allocate memory for a copy of the field");
				return_code = PCFF_MEMORY_FAILURE;
			}
			break;
		case PCFF_FLD_TYPE_SERVICE			:
			if (NPSL_ResolveServToPort(in_value, NULL, NULL,
				npsl_error_text) != NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			else if (((tmp_length = strlen(in_value)) >=
				param_ptr->field_length) && (!(flags & PCFF_FLAG_STR_TRUNC))) {
				sprintf(tmp_error_text, "%s (%u) %s (%u).",
					"The length of the field value", tmp_length,
					"exceeds the maximum length permitted for this field",
					param_ptr->field_length - 1);
				return_code = PCFF_FAILURE;
			}
			else
				nstrcpy(((char *) out_ptr), in_value,
					param_ptr->field_length - 1);
			break;
		case PCFF_FLD_TYPE_SERVICE_PTR	:
			if (NPSL_ResolveServToPort(in_value, NULL, NULL,
				npsl_error_text) != NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			else if ((*((char **) out_ptr) = strdup(in_value)) == NULL) {
				STR_AllocMsgItem(strlen(in_value) + 1, tmp_error_text,
					"Unable to allocate memory for a copy of the field");
				return_code = PCFF_MEMORY_FAILURE;
			}
			break;
		case PCFF_FLD_TYPE_PROTOCOL		:
			if (NPSL_ResolveProtoToSint(in_value, NULL, npsl_error_text) !=
				NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			else if (((tmp_length = strlen(in_value)) >=
				param_ptr->field_length) && (!(flags & PCFF_FLAG_STR_TRUNC))) {
				sprintf(tmp_error_text, "%s (%u) %s (%u).",
					"The length of the field value", tmp_length,
					"exceeds the maximum length permitted for this field",
					param_ptr->field_length - 1);
				return_code = PCFF_FAILURE;
			}
			else
				nstrcpy(((char *) out_ptr), in_value,
					param_ptr->field_length - 1);
			break;
		case PCFF_FLD_TYPE_PROTOCOL_PTR	:
			if (NPSL_ResolveProtoToSint(in_value, NULL, npsl_error_text) !=
				NPSL_SUCCESS) {
				nstrcpy(tmp_error_text, npsl_error_text, PCFF_MAX_ERROR_TEXT - 1);
				return_code = PCFF_FAILURE;
			}
			else if ((*((char **) out_ptr) = strdup(in_value)) == NULL) {
				STR_AllocMsgItem(strlen(in_value) + 1, tmp_error_text,
					"Unable to allocate memory for a copy of the field");
				return_code = PCFF_MEMORY_FAILURE;
			}
			break;
		default									:
			sprintf(tmp_error_text, "Invalid field type encountered (%d).",
				param_ptr->field_type);
			return_code = PCFF_FAILURE;
			break;
	}

	if (return_code != PCFF_SUCCESS)
		sprintf(error_text,
			"%s (%s '%-.256s', %s '%s' %s '%-.500s' at line number %u): %s",
			"Error occurred retrieving data for configuration parameter",
			"parameter name", param_ptr->param_name,
			"member name", param_ptr->member_name,
			"loaded from file", item_ptr->src_list->file_name,
			item_ptr->src_list->line_number, tmp_error_text);

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
static int PCFF_AllocateHostServProto(int phs_flag, const char *spec_string,
	const char *host_name, int service_number, int protocol_number,
	PCFF_IP_HSP *out_ip_hsp, char *error_text)
{
	int            return_code = PCFF_SUCCESS;
	unsigned int   tmp_count;
	char         **tmp_list;
	PCFF_IP_HSP    tmp_ip_hsp;

	PCFF_InitHostServProto(out_ip_hsp);

	if (sepwordx_keep(spec_string, ":", &tmp_count, &tmp_list) !=
		STRFUNCS_SUCCESS) {
		strcpy(error_text, "Attempt to parse the specification string failed.");
		return_code = NPSL_FAILURE;
	}
	else {
		PCFF_InitHostServProto(&tmp_ip_hsp);
		tmp_ip_hsp.spec_string     = ((char *) spec_string);
		tmp_ip_hsp.host_name       = ((char *) host_name);
		tmp_ip_hsp.service_number  = service_number;
		tmp_ip_hsp.protocol_number = protocol_number;
		if (phs_flag) {
			tmp_ip_hsp.protocol_name = tmp_list[0];
			if (tmp_count == 3)
				tmp_ip_hsp.service_name = tmp_list[2];
		}
		else {
			if (tmp_count >= 2)
				tmp_ip_hsp.service_name = tmp_list[1];
			if (tmp_count == 3)
				tmp_ip_hsp.protocol_name = tmp_list[2];
		}
		return_code = PCFF_CopyHostServProto(&tmp_ip_hsp, out_ip_hsp, error_text);
		strl_remove_all(&tmp_count, &tmp_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int  main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int                     return_code = PCFF_SUCCESS;
	unsigned int            count_1;
	unsigned int            line_count;
	char                  **line_list;
	PCFF_CFG                cfg_data;
	PCFF_PARSE_SPEC         parse_spec;
	PCFF_PARAM_SPEC         param_spec;
	PCFF_PARAM_SPEC         tmp_param_spec;
	PCFF_TEST_TARGET_DATA   test_data;
	char                    error_text[PCFF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for 'PCFF_DoParams()'\n");
	fprintf(stderr, "---- ------- --- -----------------\n\n");

	PCFF_InitCfg(&cfg_data);
	PCFF_InitParamSpec(&param_spec);
	PCFF_TEST_InitData(&test_data);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp("-H", argv[count_1])) ||
			(!stricmp("-HELP", argv[count_1]))) {
			fprintf(stderr, "\n\nUSAGE:\n   %s [<config-file-name> . . . ]\n\n",
				argv[0]);
			goto EXIT_FUNCTION;
		}
	}

	PCFF_TEST_GetTestDataParam(&line_count, &line_list, &parse_spec,
		&tmp_param_spec);
	if ((return_code = PCFF_CreateParamSpec(tmp_param_spec.structure_size,
		tmp_param_spec.param_count, tmp_param_spec.param_list, &param_spec,
		error_text)) != PCFF_SUCCESS)
		goto EXIT_FUNCTION;

	if (argc == 1) {
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		printf("Configuration File: %s\n", "<<<INTERNAL LIST>>>");
		if ((return_code = PCFF_LoadFromList(&cfg_data, PCFF_FLAG_NONE,
			"<<<INTERNAL LIST>>>", line_count, line_list, error_text)) ==
			PCFF_SUCCESS) {
			parse_spec.flags = PCFF_FLAG_UNKNOWN_OK;
			if ((return_code = PCFF_PostProcess(&cfg_data, &parse_spec,
				error_text)) != PCFF_SUCCESS)
				goto EXIT_FUNCTION;
			if ((return_code = PCFF_DoParams(&cfg_data, PCFF_FLAG_NONE,
				&param_spec, &test_data, error_text)) != PCFF_SUCCESS)
				goto EXIT_FUNCTION;
			PCFF_EmitParamSpecData(&cfg_data, &param_spec, &test_data,
				PCFF_TRUE, NULL, NULL);
			PCFF_TEST_FreeData(&test_data);
			PCFF_FreeCfg(&cfg_data);
		}
		else
			goto EXIT_FUNCTION;
	}

	PCFF_InitParse(&parse_spec);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		printf("Configuration File: %s\n", argv[count_1]);
		if ((return_code = PCFF_LoadFromFile(&cfg_data, PCFF_FLAG_NONE,
			argv[count_1], error_text)) != PCFF_SUCCESS)
			break;
		parse_spec.flags = PCFF_FLAG_UNKNOWN_OK;
		if ((return_code = PCFF_PostProcess(&cfg_data, &parse_spec,
			error_text)) != PCFF_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = PCFF_DoParams(&cfg_data, PCFF_FLAG_NONE,
			&param_spec, &test_data, error_text)) != PCFF_SUCCESS)
			goto EXIT_FUNCTION;
		PCFF_EmitParamSpecData(&cfg_data, &param_spec, &test_data, PCFF_TRUE,
			NULL, NULL);
		PCFF_TEST_FreeData(&test_data);
		PCFF_FreeCfg(&cfg_data);
	}

EXIT_FUNCTION:

	PCFF_FreeCfg(&cfg_data);
	PCFF_FreeParamSpec(&param_spec);
	PCFF_TEST_FreeData(&test_data);

	if (return_code != PCFF_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */


