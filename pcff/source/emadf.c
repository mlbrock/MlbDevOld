/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits the parameter specification for subsequent use
								as input to the ADF documentation system.

	Revision History	:	2001-05-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <float.h>
#include <memory.h>
#include <stdio.h>

#include <string.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions private to this module . . .			*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int PCFF_FindInList,
	(const char *param_name, unsigned int in_count, char **in_list));
/*	***********************************************************************	*/

#define PCFF_EMIT_ADF_SECTION(adf_section, adf_section_list)						\
	((((adf_section_list) != NULL) && ((adf_section_list)[(adf_section)])) ?	\
	(adf_section_list)[(adf_section)] : "")

/* *********************************************************************** */
int PCFF_EmitADFParamSpec(const PCFF_PARAM_SPEC *param_spec_ptr,
	const PCFF_PARSE_SPEC *parse_spec_ptr, const void *data_ptr,
	const char *structure_name, char **adf_section_list,
	PCFF_EMIT_ADF_FLAG emit_flags, char *error_text)
{
	return(PCFF_EmitADFParamSpecBasic(param_spec_ptr, parse_spec_ptr, data_ptr,
		structure_name, adf_section_list, emit_flags, NULL, NULL, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_EmitADFParamSpecBasic(const PCFF_PARAM_SPEC *param_spec_ptr,
	const PCFF_PARSE_SPEC *parse_spec_ptr, const void *data_ptr,
	const char *structure_name, char **adf_section_list,
	PCFF_EMIT_ADF_FLAG emit_flags, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
{
	int               return_code;
	unsigned int      count_1;
	const PCFF_PARAM *param_ptr;
	PCFF_PARAM_SPEC   tmp_param_spec;
	const void       *member_ptr;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	/*	*****************************************************************
		*****************************************************************
		Copy the parameter specification to ensure that it's valid . . .
		*****************************************************************	*/
	if ((return_code = PCFF_CopyParamSpec(param_spec_ptr, &tmp_param_spec,
		error_text)) != PCFF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	STR_EMIT_CharLine('=', 78, output_function, output_control);
	(*output_function)(output_control,
		"ADF Description of Parameter Specification\n");
	STR_EMIT_CharLine('=', 78, output_function, output_control);

	(*output_function)(output_control, "/*\tBOH .bin,1\n");

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NAME, adf_section_list))
		(*output_function)(output_control, "\tNAME\t\t\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NAME, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_SYNOP, adf_section_list))
		(*output_function)(output_control, "\tSYNOPSIS\t\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_SYNOP, adf_section_list));
	else if (parse_spec_ptr != NULL)
		(*output_function)(output_control,
			"\tSYNOPSIS\t\t:\t%s``%s``%s %s``%s``%s\n\n",
			STR_NULL_TO_STR(parse_spec_ptr->name_left),
			"parameter-name",
			STR_NULL_TO_STR(parse_spec_ptr->name_right),
			STR_NULL_TO_STR(parse_spec_ptr->value_left),
			"parameter_value",
			STR_NULL_TO_STR(parse_spec_ptr->value_right));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_DESCRIP, adf_section_list))
		(*output_function)(output_control, "\tDESCRIPTION\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_DESCRIP, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_PARAMS, adf_section_list))
		(*output_function)(output_control, "\tPARAMETERS\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_PARAMS, adf_section_list));
	else
		(*output_function)(output_control, "\tPARAMETERS\t:\t%s\n\n",
			"The valid parameters are as follow:");

	for (count_1 = 0, param_ptr = tmp_param_spec.param_list;
		count_1 < tmp_param_spec.param_count; count_1++, param_ptr++) {
		member_ptr = ((void *) (((char *) data_ptr) + param_ptr->field_offset));
		if (parse_spec_ptr != NULL)
			(*output_function)(output_control,
				"\t\t\t\t\t\t(.) %s%s%s %s``%s``%s\n\n",
				STR_NULL_TO_STR(parse_spec_ptr->name_left),
				param_ptr->param_name,
				STR_NULL_TO_STR(parse_spec_ptr->name_right),
				STR_NULL_TO_STR(parse_spec_ptr->value_left),
				PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
				STR_NULL_TO_STR(parse_spec_ptr->value_right));
		else
			(*output_function)(output_control, "\t\t\t\t\t\t(.) ``%s`` ``%s``\n\n",
				param_ptr->param_name,
				PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type));
		if ((param_ptr->description != NULL) && *param_ptr->description)
			(*output_function)(output_control, "\t\t\t\t\t\t(..) %s\n\n",
				param_ptr->description);
		if (emit_flags & (PCFF_EMIT_ADF_FLAG_TYPE | PCFF_EMIT_ADF_FLAG_MEMBER)) {
			(*output_function)(output_control, "\t\t\t\t\t\t(..) %s ``%s`` ",
				"Parameter", param_ptr->param_name);
			if (emit_flags & PCFF_EMIT_ADF_FLAG_TYPE)
				(*output_function)(output_control, "%s ``%s`` (%s ''%s%s'').%s",
					"is of type", PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
					"enumeration type", "PCFF_FLD_TYPE_",
					PCFF_GET_FLD_TYPE_NAME(param_ptr->field_type),
					(emit_flags & PCFF_EMIT_ADF_FLAG_MEMBER) ? " It " : "");
			if (emit_flags & PCFF_EMIT_ADF_FLAG_MEMBER)
				(*output_function)(output_control, "%s ``%s`` %s ''%s''.",
					"populates member", param_ptr->member_name,
					"of the structure", structure_name);
			(*output_function)(output_control, "\n\n");
		}
		switch (param_ptr->field_type) {
			case PCFF_FLD_TYPE_NONE				:
				if (error_text != NULL)
					sprintf(error_text, "%s %u ('%s') %s (%d = '%s').",
						"Parameter element index", count_1, param_ptr->param_name,
						"has an unset parameter field type", param_ptr->field_type,
						PCFF_GET_FLD_TYPE_NAME(param_ptr->field_type));
				return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
				break;
			case PCFF_FLD_TYPE_SCHAR			:
				if (emit_flags &
					(PCFF_EMIT_ADF_FLAG_DEFAULT | PCFF_EMIT_ADF_FLAG_RANGE)) {
					(*output_function)(output_control, "\t\t\t\t\t\t(..) ");
					if ((data_ptr != NULL) &&
						(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
						(*output_function)(output_control, "%s ''%d''.%s",
							"The default value for this parameter is",
							((int) *((const signed char *) member_ptr)),
							(emit_flags & PCFF_EMIT_ADF_FLAG_RANGE) ? " " : "");
					if (emit_flags & PCFF_EMIT_ADF_FLAG_RANGE)
						(*output_function)(output_control,
							"%s ''%d'' to ''%d'', inclusive.",
							"Valid values are from", CHAR_MIN, CHAR_MAX);
					(*output_function)(output_control, "\n\n");
				}
				break;
			case PCFF_FLD_TYPE_UCHAR			:
				if (emit_flags &
					(PCFF_EMIT_ADF_FLAG_DEFAULT | PCFF_EMIT_ADF_FLAG_RANGE)) {
					(*output_function)(output_control, "\t\t\t\t\t\t(..) ");
					if ((data_ptr != NULL) &&
						(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
						(*output_function)(output_control, "%s ''%u''.%s",
							"The default value for this parameter is",
							((unsigned int) *((const unsigned char *) member_ptr)),
							(emit_flags & PCFF_EMIT_ADF_FLAG_RANGE) ? " " : "");
					if (emit_flags & PCFF_EMIT_ADF_FLAG_RANGE)
						(*output_function)(output_control,
							"%s ''%u'' to ''%u'', inclusive.",
							"Valid values are from", 0, UCHAR_MAX);
					(*output_function)(output_control, "\n\n");
				}
				break;
			case PCFF_FLD_TYPE_SSHORT			:
				if (emit_flags &
					(PCFF_EMIT_ADF_FLAG_DEFAULT | PCFF_EMIT_ADF_FLAG_RANGE)) {
					(*output_function)(output_control, "\t\t\t\t\t\t(..) ");
					if ((data_ptr != NULL) &&
						(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
						(*output_function)(output_control, "%s ''%d''.%s",
							"The default value for this parameter is",
							((int) *((const signed short *) member_ptr)),
							(emit_flags & PCFF_EMIT_ADF_FLAG_RANGE) ? " " : "");
					if (emit_flags & PCFF_EMIT_ADF_FLAG_RANGE)
						(*output_function)(output_control,
							"%s ''%d'' to ''%d'', inclusive.",
							"Valid values are from", SHRT_MIN, SHRT_MAX);
					(*output_function)(output_control, "\n\n");
				}
				break;
			case PCFF_FLD_TYPE_USHORT			:
				if (emit_flags &
					(PCFF_EMIT_ADF_FLAG_DEFAULT | PCFF_EMIT_ADF_FLAG_RANGE)) {
					(*output_function)(output_control, "\t\t\t\t\t\t(..) ");
					if ((data_ptr != NULL) &&
						(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
						(*output_function)(output_control, "%s ''%u''.%s",
							"The default value for this parameter is",
							((unsigned int) *((const unsigned short *) member_ptr)),
							(emit_flags & PCFF_EMIT_ADF_FLAG_RANGE) ? " " : "");
					if (emit_flags & PCFF_EMIT_ADF_FLAG_RANGE)
						(*output_function)(output_control,
							"%s ''%u'' to ''%u'', inclusive.",
							"Valid values are from", 0, USHRT_MAX);
					(*output_function)(output_control, "\n\n");
				}
				break;
			case PCFF_FLD_TYPE_SINT				:
				if (emit_flags &
					(PCFF_EMIT_ADF_FLAG_DEFAULT | PCFF_EMIT_ADF_FLAG_RANGE)) {
					(*output_function)(output_control, "\t\t\t\t\t\t(..) ");
					if ((data_ptr != NULL) &&
						(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
						(*output_function)(output_control, "%s ''%d''.%s",
							"The default value for this parameter is",
							*((const signed int *) member_ptr),
							(emit_flags & PCFF_EMIT_ADF_FLAG_RANGE) ? " " : "");
					if (emit_flags & PCFF_EMIT_ADF_FLAG_RANGE)
						(*output_function)(output_control,
							"%s ''%d'' to ''%d'', inclusive.",
							"Valid values are from", INT_MIN, INT_MAX);
					(*output_function)(output_control, "\n\n");
				}
				break;
			case PCFF_FLD_TYPE_UINT				:
				if (emit_flags &
					(PCFF_EMIT_ADF_FLAG_DEFAULT | PCFF_EMIT_ADF_FLAG_RANGE)) {
					(*output_function)(output_control, "\t\t\t\t\t\t(..) ");
					if ((data_ptr != NULL) &&
						(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
						(*output_function)(output_control, "%s ''%u''.%s",
							"The default value for this parameter is",
							*((const unsigned int *) member_ptr),
							(emit_flags & PCFF_EMIT_ADF_FLAG_RANGE) ? " " : "");
					if (emit_flags & PCFF_EMIT_ADF_FLAG_RANGE)
						(*output_function)(output_control,
							"%s ''%u'' to ''%u'', inclusive.",
							"Valid values are from", 0, UINT_MAX);
					(*output_function)(output_control, "\n\n");
				}
				break;
			case PCFF_FLD_TYPE_SLONG			:
				if (emit_flags &
					(PCFF_EMIT_ADF_FLAG_DEFAULT | PCFF_EMIT_ADF_FLAG_RANGE)) {
					(*output_function)(output_control, "\t\t\t\t\t\t(..) ");
					if ((data_ptr != NULL) &&
						(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
						(*output_function)(output_control, "%s ''%ld''.%s",
							"The default value for this parameter is",
							*((const signed long *) member_ptr),
							(emit_flags & PCFF_EMIT_ADF_FLAG_RANGE) ? " " : "");
					if (emit_flags & PCFF_EMIT_ADF_FLAG_RANGE)
						(*output_function)(output_control,
							"%s ''%ld'' to ''%ld'', inclusive.",
							"Valid values are from", LONG_MIN, LONG_MAX);
					(*output_function)(output_control, "\n\n");
				}
				break;
			case PCFF_FLD_TYPE_ULONG			:
				if (emit_flags &
					(PCFF_EMIT_ADF_FLAG_DEFAULT | PCFF_EMIT_ADF_FLAG_RANGE)) {
					(*output_function)(output_control, "\t\t\t\t\t\t(..) ");
					if ((data_ptr != NULL) &&
						(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
						(*output_function)(output_control, "%s ''%lu''.%s",
							"The default value for this parameter is",
							*((const unsigned long *) member_ptr),
							(emit_flags & PCFF_EMIT_ADF_FLAG_RANGE) ? " " : "");
					if (emit_flags & PCFF_EMIT_ADF_FLAG_RANGE)
						(*output_function)(output_control,
							"%s ''%lu'' to ''%lu'', inclusive.",
							"Valid values are from", 0L, ULONG_MAX);
					(*output_function)(output_control, "\n\n");
				}
				break;
			case PCFF_FLD_TYPE_FLOAT			:
				if (emit_flags &
					(PCFF_EMIT_ADF_FLAG_DEFAULT | PCFF_EMIT_ADF_FLAG_RANGE)) {
					(*output_function)(output_control, "\t\t\t\t\t\t(..) ");
					if ((data_ptr != NULL) &&
						(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
						(*output_function)(output_control, "%s ''%lf''.%s",
							"The default value for this parameter is",
							((double) *((const float *) member_ptr)),
							(emit_flags & PCFF_EMIT_ADF_FLAG_RANGE) ? " " : "");
#ifdef FLT_MIN
# ifdef FLT_MAX
					if (emit_flags & PCFF_EMIT_ADF_FLAG_RANGE)
						(*output_function)(output_control,
							"%s ''%lE'' to ''%lE'', inclusive.",
							"Valid values are from", FLT_MIN, FLT_MAX);
# endif /* # ifdef FLT_MAX */
#endif /* #ifdef FLT_MIN */
					(*output_function)(output_control, "\n\n");
				}
				break;
			case PCFF_FLD_TYPE_DOUBLE			:
				if (emit_flags &
					(PCFF_EMIT_ADF_FLAG_DEFAULT | PCFF_EMIT_ADF_FLAG_RANGE)) {
					(*output_function)(output_control, "\t\t\t\t\t\t(..) ");
					if ((data_ptr != NULL) &&
						(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
						(*output_function)(output_control, "%s ''%lf''.%s",
							"The default value for this parameter is",
							*((const double *) member_ptr),
							(emit_flags & PCFF_EMIT_ADF_FLAG_RANGE) ? " " : "");
#ifdef DBL_MIN
# ifdef DBL_MAX
					if (emit_flags & PCFF_EMIT_ADF_FLAG_RANGE)
						(*output_function)(output_control,
							"%s ''%lE'' to ''%lE'', inclusive.",
							"Valid values are from", DBL_MIN, DBL_MAX);
# endif /* # ifdef DBL_MAX */
#endif /* #ifdef DBL_MIN */
					(*output_function)(output_control, "\n\n");
				}
				break;
			case PCFF_FLD_TYPE_BOOLEAN			:
				(*output_function)(output_control,
					"\t\t\t\t\t\t(..) %s\n\n%s\n\n%s\n\n",
					"This parameter indicates a ``boolean`` value as follows:",
					"\t\t\t\t\t\t(...) Any of the strings ''ON'', ''YES'',\
''TRUE'', ''T'', ''Y'', and ''1'' indicates a truth value.",
					"\t\t\t\t\t\t(...) Any of the strings ''OFF'', ''NO'',\
''FALSE'', ''F'', ''N'', and ''0'' indicates a false value.");
				if ((data_ptr != NULL) && (emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
					(*output_function)(output_control,
						"\t\t\t\t\t\t(..) %s ''%s''.\n\n",
						"The default value for this parameter is",
						(*((const int *) member_ptr)) ? "TRUE" : "FALSE");
				break;
			case PCFF_FLD_TYPE_IP_HSP			:
				(*output_function)(output_control, "\t\t\t\t\t\t(..) %s.\n\n",
					"This parameter is formatted as follows:");
				(*output_function)(output_control, "\t\t\t\t\t\t(--) %s\n\n",
"``ip-host-specification``'':''``ip-service-specification``'':''\
``ip-protocol-specification``");
				(*output_function)(output_control, "\t\t\t\t\t\t(--) where:\n\n");
				(*output_function)(output_control, "\t\t\t\t\t\t(...) %s\n\n",
					"``ip-host-specification`` is either a host name or an IP address");
				(*output_function)(output_control, "\t\t\t\t\t\t(...) %s\n\n",
					"``ip-service-specification`` is either a service name \
(such as ``telnet``) or a service number (such as ``23``).");
				(*output_function)(output_control, "\t\t\t\t\t\t(...) %s\n\n",
					"``ip-protocol-specification`` is either a protocol name \
(such as ``tcp``) or a protocol number (such as ``6``).");
				if ((data_ptr != NULL) &&
					(((const PCFF_IP_HSP *) member_ptr)->spec_string != NULL) &&
					(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
					(*output_function)(output_control,
						"\t\t\t\t\t\t(..) %s ''%s''.\n\n",
						"The default value for this parameter is",
						((const PCFF_IP_HSP *) member_ptr)->spec_string);
				break;
			case PCFF_FLD_TYPE_IP_PHS			:
				(*output_function)(output_control, "\t\t\t\t\t\t(..) %s.\n\n",
					"This parameter is formatted as follows:");
				(*output_function)(output_control, "\t\t\t\t\t\t(--) %s\n\n",
"``ip-protocol-specification``'':''``ip-host-specification``'':''\
``ip-service-specification``");
				(*output_function)(output_control, "\t\t\t\t\t\t(--) where:\n\n");
				(*output_function)(output_control, "\t\t\t\t\t\t(...) %s\n\n",
					"``ip-protocol-specification`` is either a protocol name \
(such as ``tcp``) or a protocol number (such as ``6``).");
				(*output_function)(output_control, "\t\t\t\t\t\t(...) %s\n\n",
					"``ip-host-specification`` is either a host name or an IP address");
				(*output_function)(output_control, "\t\t\t\t\t\t(...) %s\n\n",
					"``ip-service-specification`` is either a service name \
(such as ``telnet``) or a service number (such as ``23``).");
				if ((data_ptr != NULL) &&
					(((const PCFF_IP_HSP *) member_ptr)->spec_string != NULL) &&
					(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
					(*output_function)(output_control,
						"\t\t\t\t\t\t(..) %s ''%s''.\n\n",
						"The default value for this parameter is",
						((const PCFF_IP_HSP *) member_ptr)->spec_string);
				break;
			case PCFF_FLD_TYPE_STRING			:
				break;
			case PCFF_FLD_TYPE_STRING_PTR		:
				break;
			case PCFF_FLD_TYPE_DATE_STR		:
				(*output_function)(output_control, "\t\t\t\t\t\t(..) %s.\n\n",
					"This parameter is formatted as ``yyyy``-``mm``-``dd`` \
where ``yyyy`` is the zero-filled year, ``mm`` is the zero-filled month, \
and ``dd`` is the zero-filled day of the month");
				break;
			case PCFF_FLD_TYPE_TIME_STR		:
				(*output_function)(output_control, "\t\t\t\t\t\t(..) %s %s.\n\n",
					"This parameter is formatted as",
"``hh``:``mm``:``ss``.``uuuuuu`` \
where ``hh`` is the zero-filled hours in twenty-four hour format, \
``mm`` is the zero-filled minutes, ``ss`` is the zero-filled seconds, and \
``uuuuuu`` is the zero-filled microseconds");
				break;
			case PCFF_FLD_TYPE_TIMEVAL_STR	:
				(*output_function)(output_control,
					"\t\t\t\t\t\t(..) %s %s. %s.\n\n",
					"This parameter is formatted as",
"``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``.``uuuuuu`` \
where ``yyyy`` is the zero-filled year, ``mm`` is the zero-filled month, \
``dd`` is the zero-filled day of the month, \
``hh`` is the zero-filled hours in twenty-four hour format, \
``mm`` is the zero-filled minutes, ``ss`` is the zero-filled seconds, and \
``uuuuuu`` is the zero-filled microseconds",
"Note the space (ASCII 32) between the ``dd`` and ``hh`` components");
				break;
			case PCFF_FLD_TYPE_TIMESPEC_STR	:
				(*output_function)(output_control,
					"\t\t\t\t\t\t(..) %s %s. %s.\n\n",
					"This parameter is formatted as",
"``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``.``nnnnnnnnn`` \
where ``yyyy`` is the zero-filled year, ``mm`` is the zero-filled month, \
``dd`` is the zero-filled day of the month, \
``hh`` is the zero-filled hours in twenty-four hour format, \
``mm`` is the zero-filled minutes, ``ss`` is the zero-filled seconds, and \
``nnnnnnnnn`` is the zero-filled nanoseconds",
"Note the space (ASCII 32) between the ``dd`` and ``hh`` components");
				break;
			case PCFF_FLD_TYPE_PATH_NAME		:
			case PCFF_FLD_TYPE_PATH_NAME_PTR	:
				(*output_function)(output_control,
					"\t\t\t\t\t\t(..) %s. %s %s.\n\n",
					"This parameter is a directory or file name",
					"The parameter parser will attempt to expand it to its",
					"fully-qualified name");
				break;
			case PCFF_FLD_TYPE_FILE_NAME		:
			case PCFF_FLD_TYPE_FILE_NAME_PTR	:
				(*output_function)(output_control,
					"\t\t\t\t\t\t(..) %s. %s %s.\n\n",
					"This parameter is a file name of an existing file",
					"The parameter parser will attempt to expand it to its",
					"fully-qualified name");
				break;
			case PCFF_FLD_TYPE_HOST_SPEC		:
			case PCFF_FLD_TYPE_HOST_SPEC_PTR	:
				(*output_function)(output_control, "\t\t\t\t\t\t(..) %s %s.\n\n",
					"This parameter is an IP host specification (either a host name",
					"or an IP address)");
				break;
			case PCFF_FLD_TYPE_SERVICE			:
			case PCFF_FLD_TYPE_SERVICE_PTR	:
				(*output_function)(output_control, "\t\t\t\t\t\t(..) %s %s %s.\n\n",
					"This parameter is an IP service specification (either a",
					"service name such as ``telnet`` or a service number",
					"such as ``23``)");
				break;
			case PCFF_FLD_TYPE_PROTOCOL		:
			case PCFF_FLD_TYPE_PROTOCOL_PTR	:
				(*output_function)(output_control, "\t\t\t\t\t\t(..) %s %s %s.\n\n",
					"This parameter is an IP protocol specification (either a",
					"protocol name such as ``tcp`` or a protocol number",
					"such as ``6``)");
				break;
			default									:
				if (error_text != NULL)
					sprintf(error_text, "%s %u ('%s') %s (%d).",
						"Parameter element index", count_1, param_ptr->param_name,
						"has an invalid parameter field type", param_ptr->field_type);
				return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
				break;
		}
		if (param_ptr->field_type & PCFF_FLD_TYPE_STRING) {
			if (emit_flags & PCFF_EMIT_ADF_FLAG_STR_LEN)
				(*output_function)(output_control,
					"\t\t\t\t\t\t(..) %s %u character%s in length.\n\n",
					"The string length of this parameter must not exceed",
					param_ptr->field_length - 1,
					(param_ptr->field_length > 2) ? "s" : "");
			if ((data_ptr != NULL) && *((const char *) member_ptr) &&
				(emit_flags & PCFF_EMIT_ADF_FLAG_DEFAULT))
				(*output_function)(output_control,
					"\t\t\t\t\t\t(..) %s ''%s''.\n\n",
					"The default value for this parameter is",
					((const char *) member_ptr));
		}
		else if ((param_ptr->field_type & PCFF_FLD_TYPE_STRING_PTR) &&
			(emit_flags & PCFF_EMIT_ADF_FLAG_STR_PTR_LEN))
			(*output_function)(output_control,
				"\t\t\t\t\t\t(..) This parameter is a string, the length %s.\n\n",
				"of which is limited only by available memory");
		if ((parse_spec_ptr != NULL) &&
			(emit_flags & PCFF_EMIT_ADF_FLAG_OPT_REQ)) {
			if (PCFF_FindInList(param_ptr->param_name,
				parse_spec_ptr->required_count, parse_spec_ptr->required_list) ==
				PCFF_TRUE)
				(*output_function)(output_control,
					"\t\t\t\t\t\t(..) This is a required parameter.\n\n");
			else if (PCFF_FindInList(param_ptr->param_name,
				parse_spec_ptr->optional_count, parse_spec_ptr->optional_list) ==
				PCFF_TRUE)
				(*output_function)(output_control,
					"\t\t\t\t\t\t(..) This is an optional parameter.\n\n");
		}
	}

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_ENVIRON, adf_section_list))
		(*output_function)(output_control, "\tENVIRONMENT\t\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_ENVIRON, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NOTES, adf_section_list))
		(*output_function)(output_control, "\tNOTES\t\t\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NOTES, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_CAVEATS, adf_section_list))
		(*output_function)(output_control, "\tCAVEATS\t\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_CAVEATS, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_SEE_ALSO, adf_section_list))
		(*output_function)(output_control, "\tSEE ALSO\t\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_SEE_ALSO, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_EXAMPLES, adf_section_list))
		(*output_function)(output_control, "\tEXAMPLES\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_EXAMPLES, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_AUTHOR, adf_section_list))
		(*output_function)(output_control, "\tAUTHOR\t\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_AUTHOR, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_COPYRIGHT, adf_section_list))
		(*output_function)(output_control, "\tCOPYRIGHT\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_COPYRIGHT, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_OUT_INDEX, adf_section_list))
		(*output_function)(output_control, "\tOUTPUT INDEX:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_OUT_INDEX, adf_section_list));
	else if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NAME, adf_section_list))
		(*output_function)(output_control, "\tOUTPUT INDEX:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NAME, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_PUB_XREF, adf_section_list))
		(*output_function)(output_control, "\tPUBLISH XREF:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_PUB_XREF, adf_section_list));
	else if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NAME, adf_section_list))
		(*output_function)(output_control, "\tPUBLISH XREF:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NAME, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_PUB_NAME, adf_section_list))
		(*output_function)(output_control, "\tPUBLISH NAME:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_PUB_NAME, adf_section_list));
	else if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NAME, adf_section_list))
		(*output_function)(output_control, "\tPUBLISH NAME:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NAME, adf_section_list));

	if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_ENTRY_CLASS, adf_section_list))
		(*output_function)(output_control, "\tENTRY CLASS\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_ENTRY_CLASS, adf_section_list));
	else if (*PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NAME, adf_section_list))
		(*output_function)(output_control, "\tENTRY CLASS\t:\t%s\n\n",
			PCFF_EMIT_ADF_SECTION(PCFF_ADF_SECTION_NAME, adf_section_list));

	(*output_function)(output_control, "EOH */\n");
	STR_EMIT_CharLine('=', 78, output_function, output_control);
	(*output_function)(output_control, "\n");

EXIT_FUNCTION:

	PCFF_FreeParamSpec(&tmp_param_spec);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
static int PCFF_FindInList(const char *param_name, unsigned int in_count,
	char **in_list)
{
	int return_code = PCFF_FALSE;

	while (in_count) {
		if (!stricmp(param_name, in_list[--in_count])) {
			return_code = PCFF_TRUE;
			break;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

static char *PCFF_TEST_ADFList[PCFF_ADF_SECTION_COUNT] = {
	"PCFF Test Configuration Parameters",
	NULL,
	"The description.",
	"The valid parameters are as follow:",
	NULL,
	"Notes go here.",
	"Caveats and warnings go here.",
	NULL,
	NULL,
	"Michael L. Brock",
	"Copyright 2001 - 2016 Michael L. Brock",
	NULL,
	NULL,
	NULL,
	NULL
};

COMPAT_FN_DECL(int main, (void));

int main()
{
	int                     return_code = PCFF_SUCCESS;
	unsigned int            line_count;
	char                  **line_list;
	PCFF_CFG                cfg_data;
	PCFF_PARSE_SPEC         parse_spec;
	PCFF_PARAM_SPEC         param_spec;
	PCFF_PARAM_SPEC         tmp_param_spec;
	PCFF_TEST_TARGET_DATA   test_data;
	char                    error_text[PCFF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for 'PCFF_EmitADFParamSpec()'\n");
	fprintf(stderr, "---- ------- --- -------------------------\n\n");

	PCFF_InitCfg(&cfg_data);
	PCFF_InitParamSpec(&param_spec);
	PCFF_TEST_InitData(&test_data);

	PCFF_TEST_GetTestDataParam(&line_count, &line_list, &parse_spec,
		&tmp_param_spec);
	if ((return_code = PCFF_CreateParamSpec(tmp_param_spec.structure_size,
		tmp_param_spec.param_count, tmp_param_spec.param_list, &param_spec,
		error_text)) != PCFF_SUCCESS)
		goto EXIT_FUNCTION;

	PCFF_SortParamList(param_spec.param_count, param_spec.param_list);

	return_code = PCFF_EmitADFParamSpec(&param_spec, &parse_spec, &test_data,
		"PCFF_TEST_TARGET_DATA", PCFF_TEST_ADFList, PCFF_EMIT_ADF_FLAG_ALL,
		error_text);

EXIT_FUNCTION:

	PCFF_FreeParamSpec(&param_spec);
	PCFF_TEST_InitData(&test_data);

	if (return_code != PCFF_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */


